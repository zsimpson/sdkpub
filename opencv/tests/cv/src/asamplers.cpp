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

#include "cvtest.h"

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>

static char* funcs[] =
{
    "cvInitLineIterator, cvSampleLine",
    "cvGetRectSubPix"
};

static char *test_desc = "Test of sampler functions";

/* actual parameters */
static int img_size, base_iters;

/* which tests have to run */
static int dt_l = 0,  dt_h = 1,
           ch_l = 0,  ch_h = 1;

static int init_smp_params = 0;

static const int   img8u_range  = 256;
static const int   img8s_range  = 128;
static const float img32f_range = 1000.f;
static const int   img32f_bits  = 23;

static void read_smp_params( void )
{
    if( !init_smp_params )
    {
        int  data_types, channels;

        /* Determine which tests are needed to run */
        trsCaseRead( &data_types,"/a/8u/32f", "a",
            "a - all, 8u - unsigned char, 32f - float" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        trsCaseRead( &channels, "/a/1/3", "a",
            "a - all, 1 - single channel, 3 - three channels" );
        if( channels != 0 ) ch_l = ch_h = channels - 1;

        /* read tests params */
        trsiRead( &img_size, "537", "width or height of image" );
        trsiRead( &base_iters, "100", "Base number of iterations" );

        init_smp_params = 1;
    }
}


typedef CvStatus  (*AtsInitLineIteratorR)( void* img, int step, CvSize size,
                                            CvPoint pt1, CvPoint pt2,
                                            CvLineIterator* iterator );

typedef CvStatus  (*AtsSampleLineR)( void* img, int step, CvSize size,
                                     CvPoint pt1, CvPoint pt2, void* buffer );

static CvPoint get_coordinates( void* ptr, IplImage* img )
{
    CvPoint pt;
    int ofs = (char*)ptr - img->imageData;
    
    pt.y = ofs / img->widthStep;
    pt.x = (ofs - pt.y * img->widthStep)/(img->nChannels * ((img->depth & 255)>>3));

    return pt;
}


/* ///////////////////// line_smp_test ///////////////////////// */

static int line_smp_test( void* arg )
{
    const int success_error_level = 0;
    const char* message = "No errors";

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed      = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_iter = 0;

    /* test parameters */
    int     i = 0, count;
    double  max_err = 0.;
    int     code = TRS_OK;

    IplROI       img_roi;
    IplImage    *img;
    AtsRandState rng_state;
    uchar*       src_buf = 0;
    uchar*       dst_buf = 0;
    uchar*       ptr = 0;

    read_smp_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 0 ? IPL_DEPTH_8U : IPL_DEPTH_32F;
    channels = channels ? 3 : 1;

    img = atsCreateImage( img_size, img_size, depth, channels, 1 );
    img->roi = &img_roi;

    img_roi.coi = 0;
    img_roi.xOffset = img_roi.yOffset = 0;
    img_roi.width = img_size;
    img_roi.height = img_size;

    src_buf = (uchar*)icvAlloc( img_size * ((depth & 255)>>3) * channels );
    dst_buf = (uchar*)icvAlloc( img_size * ((depth & 255)>>3) * channels );
    assert( src_buf != 0 && dst_buf != 0 );

    atsRandInit( &rng_state, 0, 1, seed );

    switch( depth )
    {
    case IPL_DEPTH_8U:
        atsRandSetBounds( &rng_state, 0, img8u_range );
        break;
    case IPL_DEPTH_32F:
        atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
        atsRandSetFloatBits( &rng_state, img32f_bits );
        break;
    }

    atsFillRandomImageEx( img, &rng_state );

    for( i = 0; i < base_iters; i++ )
    {
        double err = 0;
        CvPoint pt1, pt2;
        CvPoint start_pt, end_pt;
        int color = (atsRandPlain32s( &rng_state )|1) 
                    & (channels == 1 ? 0xff : 0xffffff);
        int j;
        int64 result;
        CvLineIterator iterator;

        pt1.x = atsRandPlain32s( &rng_state ) % img_roi.width;
        pt1.y = atsRandPlain32s( &rng_state ) % img_roi.height;

        pt2.x = atsRandPlain32s( &rng_state ) % img_roi.width;
        pt2.y = atsRandPlain32s( &rng_state ) % img_roi.height;

        count = cvInitLineIterator( img, pt1, pt2, &iterator );
        if( count != MAX( abs(pt1.x - pt2.x), abs(pt1.y - pt2.y)) + 1 )
        {
            message = "InitLineIterator returns wrong value";
            code = TRS_FAIL;
            goto test_exit;
        }

        start_pt = get_coordinates( iterator.ptr, img );

        if( start_pt.x != pt1.x || start_pt.y != pt1.y )
        {
            message = "Staring point of the iterator is wrong";
            code = TRS_FAIL;
            goto test_exit;
        }

        switch( depth )
        {
        case IPL_DEPTH_8U:
            {
                uchar* buf = src_buf;

                cvLine( img, pt1, pt2, color );

                for( j = 0; j < count; j++ )
                {
                    int clr = 0;
                    memcpy( &clr, iterator.ptr, channels );
                    if( clr != color ) break;
                    CV_NEXT_LINE_POINT( iterator );
                }

                if( j < count )
                {
                    CvPoint temp = pt1;
                    pt1 = pt2;
                    pt2 = temp;
                }

                atsbRand8u( &rng_state, buf, count*channels );

                count = cvInitLineIterator( img, pt1, pt2, &iterator );
                if( count != MAX( abs(pt1.x - pt2.x), abs(pt1.y - pt2.y)) + 1 )
                {
                    message = "InitLineIterator returns wrong value";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                for( j = 0; j < count; j++, buf += channels )
                {
                    int clr = 0;
                    ptr = iterator.ptr;

                    memcpy( &clr, iterator.ptr, channels );
                    if( clr != color )
                    {
                        message = "Iteration for 8u doesn't match line drawing function";
                        code = TRS_FAIL;
                        goto test_exit;
                    }

                    memcpy( iterator.ptr, buf, channels );
                    CV_NEXT_LINE_POINT( iterator );
                }

                if( err > success_error_level ) break;

                result = cvSampleLine( img, pt1, pt2, dst_buf );
                if( (int)result != count )
                {
                    message = "SampleLine fails";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                count *= channels;
                for( j = 0; j < count; j++ )
                {
                    double t = fabs(src_buf[j] - dst_buf[j]);
                    err = MAX( err, t );
                }
            }
            break;
        case IPL_DEPTH_32F:
            {
                float* buf = (float*)src_buf;
                CvLineIterator byte_iterator;
                int count_byte;

                img->depth = IPL_DEPTH_8U;
                count_byte = cvInitLineIterator( img, pt1, pt2, &byte_iterator );
                img->depth = IPL_DEPTH_32F;

                if( count_byte != count )
                {
                    message = "Line iterator for 8u images differs from 32f";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                atsbRand32f( &rng_state, buf, count*channels );
                for( j = 0; j < count; j++, buf += channels )
                {
                    CvPoint t0 = get_coordinates( iterator.ptr, img );
                    CvPoint t1;

                    ptr = iterator.ptr;

                    img->depth = IPL_DEPTH_8U;
                    t1 = get_coordinates( byte_iterator.ptr, img );
                    img->depth = IPL_DEPTH_32F;
                    
                    if( t0.x != t1.x || t0.y != t1.y )
                    {
                        message = "32f iterator differs from 8u";
                        code = TRS_FAIL;
                        goto test_exit;
                    }

                    memcpy( iterator.ptr, buf, channels * sizeof(float) );
                    CV_NEXT_LINE_POINT( iterator );
                    CV_NEXT_LINE_POINT( byte_iterator );
                }

                if( err > success_error_level ) break;

                result = cvSampleLine( img, pt1, pt2, dst_buf );
                if( (int)result != count )
                {
                    message = "SampleLine fails";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                count *= channels;
                for( j = 0; j < count; j++ )
                {
                    double t = fabs(((float*)src_buf)[j] - ((float*)dst_buf)[j]);
                    err = MAX( err, t );
                }
            }
            break;
        }

        end_pt = get_coordinates( ptr, img );
        if( end_pt.x != pt2.x || end_pt.y != pt2.y )
        {
            message = "Ending point of the iterator is wrong";
            code = TRS_FAIL;
            goto test_exit;
        }

        if( err > max_err )
        {
            merr_iter = i;
            max_err   = err;
            if( max_err > success_error_level ) goto test_exit;
        }
    } /* end of the testing loop */

test_exit:

    img->roi = 0;
    atsReleaseImage( img );

    if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at i = %d, seed = %08x",
                  max_err, merr_iter, seed );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
    else
    {
        trsWrite( ATS_LST, "Fatal error at i = %d, seed = %08x", i, seed );
        return trsResult( TRS_FAIL, message );
    }
}



static void samp_rect_etalon( IplImage* src, IplImage* dst, CvPoint2D32f center )
{
    float* src_data = 0;
    float* dst_data = 0;
    int  src_step = 0;
    int  dst_step = 0;
    int  x, y;
    int  sx, sy;
    CvSize src_size, dst_size;
    float a, b;

    cvGetImageRawData( src, (uchar**)&src_data, &src_step, &src_size );
    cvGetImageRawData( dst, (uchar**)&dst_data, &dst_step, &dst_size );

    src_step /= 4;
    dst_step /= 4;

    sx = cvFloor( center.x );
    sy = cvFloor( center.y );

    a = center.x - sx;
    b = center.y - sy;

    sx -= dst_size.width/2;
    sy -= dst_size.height/2;

    #define normalize( v, high )    \
        if( v < 0 ) v = 0;          \
        if( v >= high ) v = high - 1;

    for( y = 0; y < dst_size.height; y++ )
        for( x = 0; x < dst_size.width; x++ )
        {
            int x1 = sx + x;
            int y1 = sy + y;
            int x2 = x1 + 1;
            int y2 = y1 + 1;
            
            normalize( x1, src_size.width  );
            normalize( x2, src_size.width  );
            normalize( y1, src_size.height );
            normalize( y2, src_size.height );

            float p0 = src_data[y1*src_step + x1];
            float p1 = src_data[y1*src_step + x2];
            float p2 = src_data[y2*src_step + x1];
            float p3 = src_data[y2*src_step + x2];

            p0 = p0 + a*(p1 - p0);
            p2 = p2 + a*(p3 - p2);
            p0 = p0 + b*(p2 - p0);

            dst_data[y*dst_step + x] = p0;
        }
}

static int rect_smp_test( void* arg )
{
    const int min_img_size = 3;
    const double success_error_level_base = 5e-5;

    int   param = (int)arg;
    int   channels  = 1;
    int   depth = param/2;

    int   seed = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_iter = 0;

    /* test parameters */
    int     i = 0;
    double  max_err = 0.;
    int     w = 0, h = 0, rw = 0, rh = 0;
    double  success_error_level = success_error_level_base;

    AtsRandState rng_state;
    IplImage*  src    = 0;
    IplImage*  src2   = 0;
    IplImage*  dst    = 0;
    IplImage*  dst2   = 0;
    IplImage*  srcptr = 0;
    CvPoint    err_pt = { 0, 0 };

    read_smp_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ))) return TRS_UNDEF;

    depth = depth == 0 ? IPL_DEPTH_8U : IPL_DEPTH_32F;

    src  = cvCreateImage( cvSize( img_size, img_size ), depth,         channels );
    dst  = cvCreateImage( cvSize( img_size, img_size ), IPL_DEPTH_32F, channels );
    dst2 = cvCreateImage( cvSize( img_size, img_size ), IPL_DEPTH_32F, channels );

    atsRandInit( &rng_state, 0, 1, seed );

    switch( depth )
    {
    case IPL_DEPTH_8U:
        atsRandSetBounds( &rng_state, 0, img8u_range );
        success_error_level *= img8u_range;
        break;
    case IPL_DEPTH_8S:
        atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
        success_error_level *=img8s_range;
        break;
    case IPL_DEPTH_32F:
        atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
        atsRandSetFloatBits( &rng_state, img32f_bits );
        success_error_level *=img32f_range;
        break;
    }

    atsFillRandomImageEx( src, &rng_state );

    srcptr = src;
    if( depth != IPL_DEPTH_32F )
    {
        src2   = cvCreateImage( cvSize( img_size, img_size ), IPL_DEPTH_32F, channels );
        srcptr = src2;
        atsConvert( src, src2 );
    }

    for( i = 0; i < base_iters; i++ )
    {
        w  = atsRandPlain32s(&rng_state) % (img_size - min_img_size + 1) + min_img_size;
        h  = atsRandPlain32s(&rng_state) % (img_size - min_img_size + 1) + min_img_size;
        rw = atsRandPlain32s(&rng_state) % w + 1;
        rh = atsRandPlain32s(&rng_state) % h + 1;
        if( rw % 2 == 0 ) rw--;
        if( rh % 2 == 0 ) rh--;

        CvPoint2D32f center;
        center.x = atsRandPlane32f(&rng_state) * (w + rw*1.5f) - rw*0.7f;
        center.y = atsRandPlane32f(&rng_state) * (h + rh*1.5f) - rh*0.7f;
        //center.x = w*0.5f;
        //center.y = h*0.5f;

        cvSetImageROI( src, cvRect(0,0,w,h));
        cvSetImageROI( dst, cvRect(0,0,rw,rh));
        cvSetImageROI( dst2, cvRect(0,0,rw,rh));

        if( depth != IPL_DEPTH_32F )
        {
            cvSetImageROI( src2, cvRect(0,0,w,h));
        }

        samp_rect_etalon( srcptr, dst2, center );

        cvGetRectSubPix( src, dst, center );
        iplSubtract( dst, dst2, dst );

        double err = iplNorm( dst, 0, IPL_C );
        if( err > max_err )
        {
            max_err   = err;
            merr_iter = i;

            if( max_err > success_error_level )
            {
                err_pt = atsFindFirstErr( dst, dst2, success_error_level );
                goto test_exit;
            }
        }
    }

test_exit:

    cvReleaseImage( &src );
    cvReleaseImage( &src2 );
    cvReleaseImage( &dst );
    cvReleaseImage( &dst2 );

    trsWrite( ATS_LST, "Max err is %g at i = %d, first \"bad\" pt = (%d,%d), seed = %08x",
              max_err, merr_iter, err_pt.x, err_pt.y, seed );

    return max_err <= success_error_level ?
        trsResult( TRS_OK, "No errors" ) :
        trsResult( TRS_FAIL, "Bad accuracy" );
}



#define _8U_C1    0
#define _8U_C3    1
#define _32F_C1   2
#define _32F_C3   3


void InitASamplers( void )
{
    /* Registering test functions */
    trsRegArg( funcs[0], test_desc, atsAlgoClass, line_smp_test, _8U_C1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, line_smp_test, _8U_C3 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, line_smp_test, _32F_C1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, line_smp_test, _32F_C3 );

    trsRegArg( funcs[1], test_desc, atsAlgoClass, rect_smp_test, _8U_C1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, rect_smp_test, _32F_C1 );

} /* InitASamplers */


/* End of file. */
