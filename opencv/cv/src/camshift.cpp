/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "_cv.h"

// GNU compiler can't build this code
//#ifdef WIN32

#include "cv.hpp"
#include <math.h>
#include <assert.h>
#include <memory.h>

CV_DLL_ENTRY
CvCamShiftTracker::CvCamShiftTracker()
{
    length = 0;
    width = 0;
    orientation = 0;
    window = cvRect( 0, 0, 0, 0 );
    int i;
    
    for( i = 0; i < CvImageGroup::max_count; i++ )
        thresh[i] = 0;
    threshold = 0;

    shift = 0;

    for( i = 0; i < 6; i++ )
    {
        min_ch_val[i] = 0;
        max_ch_val[i] = 255;
        thresh[i] = thresh_buf + i * 2;
    }

    hist = 0;
}


CV_DLL_ENTRY
CvCamShiftTracker::~CvCamShiftTracker()
{
    cvReleaseHist( &hist );
}


#define SHIFT 12

static const int div_table[] = {
    0, 1044480, 522240, 348160, 261120, 208896, 174080, 149211,
    130560, 116053, 104448, 94953, 87040, 80345, 74606, 69632,
    65280, 61440, 58027, 54973, 52224, 49737, 47476, 45412,
    43520, 41779, 40172, 38684, 37303, 36017, 34816, 33693,
    32640, 31651, 30720, 29842, 29013, 28229, 27486, 26782,
    26112, 25475, 24869, 24290, 23738, 23211, 22706, 22223,
    21760, 21316, 20890, 20480, 20086, 19707, 19342, 18991,
    18651, 18324, 18008, 17703, 17408, 17123, 16846, 16579,
    16320, 16069, 15825, 15589, 15360, 15137, 14921, 14711,
    14507, 14308, 14115, 13926, 13743, 13565, 13391, 13221,
    13056, 12895, 12738, 12584, 12434, 12288, 12145, 12006,
    11869, 11736, 11605, 11478, 11353, 11231, 11111, 10995,
    10880, 10768, 10658, 10550, 10445, 10341, 10240, 10141,
    10043, 9947, 9854, 9761, 9671, 9582, 9495, 9410,
    9326, 9243, 9162, 9082, 9004, 8927, 8852, 8777,
    8704, 8632, 8561, 8492, 8423, 8356, 8290, 8224,
    8160, 8097, 8034, 7973, 7913, 7853, 7795, 7737,
    7680, 7624, 7569, 7514, 7461, 7408, 7355, 7304,
    7253, 7203, 7154, 7105, 7057, 7010, 6963, 6917,
    6872, 6827, 6782, 6739, 6695, 6653, 6611, 6569,
    6528, 6487, 6447, 6408, 6369, 6330, 6292, 6254,
    6217, 6180, 6144, 6108, 6073, 6037, 6003, 5968,
    5935, 5901, 5868, 5835, 5803, 5771, 5739, 5708,
    5677, 5646, 5615, 5585, 5556, 5526, 5497, 5468,
    5440, 5412, 5384, 5356, 5329, 5302, 5275, 5249,
    5222, 5196, 5171, 5145, 5120, 5095, 5070, 5046,
    5022, 4998, 4974, 4950, 4927, 4904, 4881, 4858,
    4836, 4813, 4791, 4769, 4748, 4726, 4705, 4684,
    4663, 4642, 4622, 4601, 4581, 4561, 4541, 4522,
    4502, 4483, 4464, 4445, 4426, 4407, 4389, 4370,
    4352, 4334, 4316, 4298, 4281, 4263, 4246, 4229,
    4212, 4195, 4178, 4161, 4145, 4128, 4112, 4096
};

#define mmax(a,b)    ((b) + (((a)-(b))&((a)>(b)?-1:0)))
#define mmin(a,b)    ((a) - (((a)-(b))&((a)>(b)?-1:0)))


CV_DLL_ENTRY CvImageGroup *
CvCamShiftTracker::color_transform( CvImage * image )
{
    const int planes = 3;
    int x, y, x1;

    uchar *src = (uchar *) image->imageData;
    int src_pitch = image->widthStep;

    color_transform_image_group = 1;
    color_transform_image_group.copy( *image );

    CvImage *im = &color_transform_image_group[0];
    uchar *dst = (uchar *) im->imageData;       //color_transform_image_group[0].data;
    int dst_pitch = color_transform_image_group[0].widthStep;

    assert( src );
    assert( dst );

    for( y = 0; y < image->height; y++, src += src_pitch, dst += dst_pitch )
        for( x = 0, x1 = 0; x < image->width * planes; x += planes, x1++ )
        {
            int b, g, r;

            b = src[x];
            g = src[x + 1];
            r = src[x + 2];

            // convert rgb->hsv
            int h, s, v;

            {
                int vmin, diff;
                int vr, vg;

                v = mmax( r, g );
                v = mmax( v, b );
                vmin = mmin( r, g );
                vmin = mmin( vmin, b );

                diff = v - vmin;
                vr = v == r ? -1 : 0;
                vg = v == g ? -1 : 0;

                s = diff * div_table[v] >> SHIFT;
                h =
                    (vr & (g - b)) +
                    (~vr & ((vg & (b - r + 2 * diff)) + ((~vg) & (r - g + 4 * diff))));
                h =
                    ((h * div_table[diff] * 15 + (1 << (SHIFT + 6))) >> (7 + SHIFT)) + (h <
                                                                                        0 ? 30
                                                                                        *
                                                                                        6 : 0);
            }

            if( s >= min_ch_val[1] && v >= min_ch_val[2] && v <= max_ch_val[2] )
                dst[x1] = (uchar) h;
            else
                dst[x1] = 0;
        }
    return &color_transform_image_group;
}


CV_DLL_ENTRY CvImage *
CvCamShiftTracker::trackobj_pre_color( CvImage * image )
{
    if( !shift )
        return image;

    trackobj_pre_color_image.copy( *image );

    cvPyrDown( image, &trackobj_pre_color_image, (IplFilter) CV_GAUSSIAN_5x5 );

    trackobj_pre_color_image.width >>= 1;
    trackobj_pre_color_image.height >>= 1;

    for( int j = 1; j < shift; j++ )
    {
        cvPyrDown( &trackobj_pre_color_image, &trackobj_pre_color_image,
                   (IplFilter) CV_GAUSSIAN_5x5 );

        trackobj_pre_color_image.width >>= 1;
        trackobj_pre_color_image.height >>= 1;
    }

    return &trackobj_pre_color_image;
}


CV_DLL_ENTRY CvImageGroup *
CvCamShiftTracker::trackobj_post_color( CvImageGroup * image )
{
    return image;
}


CV_DLL_ENTRY void
CvCamShiftTracker::trackobj_find( CvImage * image )
{
    assert( image );
    assert( image->imageData );

    CvConnectedComp comp;
    CvBox2D box;
    CvRect _window = { window.x >> shift,
        window.y >> shift,
        window.width >> shift,
        window.height >> shift
    };

    if( _window.x < 0 )
    {
        _window.width += _window.x;
        _window.x = 0;
    }
    if( _window.y < 0 )
    {
        _window.height += _window.y;
        _window.y = 0;
    }
    if( _window.x + _window.width > image->width )
        _window.width = image->width - _window.x;
    if( _window.y + _window.height > image->height )
        _window.height = image->height - _window.y;

    assert( _window.x < image->width && _window.y < image->height );
    cvCamShift( image, _window,
                cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ),
                &comp, &box );

    _window = comp.rect;
    assert( _window.x >= 0 && _window.y >= 0 && _window.width > 0 && _window.height > 0 );

    window.x = _window.x << shift;
    window.y = _window.y << shift;
    window.width = _window.width << shift;
    window.height = _window.height << shift;
    orientation = box.angle;
    length = box.size.height * (1 << shift);
    width = box.size.width * (1 << shift);
    assert( window.x >= 0 && window.y >= 0 && window.width > 0 && window.height > 0 );
}


CV_DLL_ENTRY CvImage *
CvCamShiftTracker::calc_back_project( CvImageGroup * image )
{
    calc_back_project_image.copy( (*image)[0] );

    cvCalcBackProject( image->get_group(), &calc_back_project_image, hist );

    return &calc_back_project_image;
}


CV_DLL_ENTRY void
CvCamShiftTracker::calc_histogram( CvImageGroup * image )
{
    IplROI roi = { 0, window.x >> shift, window.y >> shift,
        window.width >> shift, window.height >> shift
    };
    int i, count = image->get_count();
    int hist_size;
    float scale;

    assert( image );

    for( i = 0; i < count; i++ )
    {
        (*image)[i].roi = &roi;
    }

    cvCalcHist( image->get_group(), hist, 0 );

    for( i = 0; i < count; i++ )
    {
        (*image)[i].roi = 0;
    }

    float max_val = 0;

    cvGetMinMaxHistValue( hist, 0, &max_val );

    hist_size = hist->dims[0] * hist->mdims[0];
    scale = (float)( 255 / max_val );

    for( i = 0; i < hist_size; i++ )
    {
        hist->array[i] *= (float)scale;
    }
}


CV_DLL_ENTRY int
CvCamShiftTracker::get_hist_dims( int *dims )
{
    if( dims )
        for( int i = 0; i < hist->c_dims; i++ )
            dims[i] = hist->dims[i];
    return hist->c_dims;
}


CV_DLL_ENTRY bool
CvCamShiftTracker::set_hist_dims( int c_dims, int *dims )
{
    int i;

    if( c_dims > 6 || c_dims <= 0 )
        return false;

    if( hist )
    {
        if( hist->c_dims == c_dims )
        {
            for( i = 0; i < c_dims; i++ )
            {
                if( hist->dims[i] != dims[i] )
                    break;
            }
            if( i == c_dims )
                return true;
        }
        cvReleaseHist( &hist );
    }

    hist = cvCreateHist( c_dims, dims, CV_HIST_ARRAY );

    for( i = 0; i < c_dims; i++ )
    {
        thresh[i][0] = 0.f;
        thresh[i][1] = 255.f;
    }

    cvSetHistThresh( hist, &thresh[0], 1 );

    return hist != 0;
}


CV_DLL_ENTRY bool
CvCamShiftTracker::set_thresh( int channel, int min_val, int max_val )
{
    thresh[channel][0] = (float) min_val;
    thresh[channel][1] = (float) max_val;

    cvSetHistThresh( hist, &thresh[0], 1 );

    return true;
}

//#endif

/* End of file. */
