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
    "cvCvtPixToPlane",
    "cvCvtPlaneToPix",

    "cvConvertScale",
    "cvConvertScaleAbs"
};

static char *test_desc = "Test of conversion functions using IPL";

/* actual parameters */
static int min_img_size, max_img_size;
static int img_size_delta_type, img_size_delta;
static int base_iters;

/* which tests have to run */
static int dt_l = 0, dt_h = 1,
           ch_l = 0, ch_h = 1;

static int init_cvt_params = 0;

static const int img8u_range = 256;
static const int img8s_range = 128;
static const int img16s_range = 32768;
static const float img32f_range = 1000.f;
static const int img32f_bits = 23;

static void read_cvt_params( void )
{
    if( !init_cvt_params )
    {
        int  data_types, channels;

        /* Determine which tests are needed to run */
        trsCaseRead( &data_types,"/a/8u/32f", "a",
            "a - all, 8u - unsigned char, 32f - float" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        trsCaseRead( &channels, "/a/3/4", "a", "a - all, 3 - three channels, 4 - four channels" );
        if( channels != 0 ) ch_l = ch_h = channels - 1;

        /* read tests params */
        trsiRead( &min_img_size, "1", "Minimal width or height of image" );
        trsiRead( &max_img_size, "1000", "Maximal width or height of image" );
        trsCaseRead( &img_size_delta_type,"/a/m", "m", "a - add, m - multiply" );
        trsiRead( &img_size_delta, "3", "Image size step(factor)" );
        trsiRead( &base_iters, "1000", "Base number of iterations" );

        init_cvt_params = 1;
    }
}


/* ///////////////////// cvt_pix_to_plane_test ///////////////////////// */

static int cvt_pix_to_plane_test( void* arg )
{
    const int success_error_level = 0;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed      = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       src_roi, dst_roi;
    IplImage    *src_img, *dst_img[8];
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_cvt_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 1 ? IPL_DEPTH_32F : IPL_DEPTH_8U;
    channels += 3;

    src_img = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    src_img->roi = &src_roi;

    for( i = 0; i < channels*2; i++ )
    {
        dst_img[i] = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );
        dst_img[i]->roi = &dst_roi;
    }

    src_roi.coi = dst_roi.coi = 0;
    src_roi.xOffset = src_roi.yOffset = 
    dst_roi.xOffset = dst_roi.yOffset = 0;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int      denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int      iters = (base_iters*2 + denom)/(2*denom);

            src_roi.width = dst_roi.width = w;
            src_roi.height = dst_roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double err0 = 0, err;

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

                src_roi.coi = 0;
                atsFillRandomImageEx( src_img, &rng_state );

                /* convert to planar repr. via IPL and via IPPICVL (single plane mode) */
                for( c = 1; c <= channels; c++ )
                {

                    IplImage* dst[4];
                    src_roi.coi = c;
                    iplCopy( src_img, dst_img[c-1] );

                    memset( dst, 0, sizeof(dst));
                    dst[c-1] = dst_img[channels];

                    cvCvtPixToPlane( src_img, dst[0], dst[1], dst[2], dst[3] );

                    err = iplNorm( dst_img[c-1], dst_img[channels], IPL_C );
                    err0 = MAX( err0, err );
                }

                /* convert all */
                cvCvtPixToPlane( src_img, dst_img[channels], dst_img[channels + 1],
                                 dst_img[channels + 2], channels == 4 ? 
                                 dst_img[channels + 3] : 0 );

                for( c = 1; c <= channels; c++ )
                {
                    err = iplNorm( dst_img[c-1], dst_img[channels + c - 1], IPL_C );
                    err0 = MAX( err0, err );
                }

                if( err0 > max_err )
                {
                    merr_w    = w;
                    merr_h    = h;
                    merr_iter = i;
                    max_err   = err0;
                    if( max_err > success_error_level ) goto test_exit;
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    for( i = 0; i < 2*channels; i++ )
    {
        dst_img[i]->roi = 0;
        atsReleaseImage( dst_img[i] );
    }
    
    src_img->roi = 0;
    atsReleaseImage( src_img );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, seed );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
    /*else
    {
        trsWrite( ATS_LST, "Fatal error at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           w, h, i, c, seed );
        return trsResult( TRS_FAIL, "Function returns error code" );
    }*/
}


/* ///////////////////// cvt_plane_to_pix_test ///////////////////////// */

static int cvt_plane_to_pix_test( void* arg )
{
    const int success_error_level = 0;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = param & 1;

    int   seed      = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       src_roi, dst_roi;
    IplImage    *dst_img, *dst2_img, *src_img[4];
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_cvt_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 1 ? IPL_DEPTH_32F : IPL_DEPTH_8U;
    channels += 3;

    dst_img  = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    dst2_img = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    dst_img->roi = dst2_img->roi = &dst_roi;

    for( i = 0; i < channels; i++ )
    {
        src_img[i] = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );
        src_img[i]->roi = &src_roi;
    }

    src_roi.coi = dst_roi.coi = 0;
    src_roi.xOffset = src_roi.yOffset = 
    dst_roi.xOffset = dst_roi.yOffset = 0;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int      denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int      iters = (base_iters*2 + denom)/(2*denom);

            src_roi.width = dst_roi.width = w;
            src_roi.height = dst_roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double err0 = 0;

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

                src_roi.coi = 0;
                for( c = 1; c <= channels; c++ )
                {
                    atsFillRandomImageEx( src_img[c-1], &rng_state );
                }

                /* convert to pix. via IPL (single plane mode) */
                for( c = 1; c <= channels; c++ )
                {
                    dst_roi.coi = c;
                    iplCopy( src_img[c-1], dst_img );
                }

                dst_roi.coi = 0;
                cvCvtPlaneToPix( src_img[0], src_img[1], src_img[2],
                                 channels == 4 ? src_img[3] : 0, dst2_img );

                err0 = iplNorm( dst_img, dst2_img, IPL_C );

                if( err0 > max_err )
                {
                    merr_w    = w;
                    merr_h    = h;
                    merr_iter = i;
                    max_err   = err0;
                    if( max_err > success_error_level ) goto test_exit;
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    for( i = 0; i < channels; i++ )
    {
        src_img[i]->roi = 0;
        atsReleaseImage( src_img[i] );
    }
    
    dst_img->roi = dst2_img->roi = 0;
    atsReleaseImage( dst_img );
    atsReleaseImage( dst2_img );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, seed );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
    /*else
    {
        trsWrite( ATS_LST, "Fatal error at w = %d, h = %d, "
                           "iter = %d, seed = %08x",
                           w, h, i, seed );
        return trsResult( TRS_FAIL, "Function returns error code" );
    }*/
}


/* ///////////////////// cvt_scale_test ///////////////////////// */

static int cvt_scale_test( void* arg )
{
    static const int depths[] = { IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16S,
                                  IPL_DEPTH_32S, IPL_DEPTH_32F };
    
    double success_error_level = 1;

    int   param     = (int)arg;
    int   src_depth = depths[param / 5];
    int   dst_depth = depths[param % 5];
    int   seed     = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  err = 0, max_err = 0.;
    int     code = TRS_OK;

    IplImage    *dst_img, *dst2_img, *dst3_img, *src_img;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_cvt_params();

    CvSize img_size = cvSize( max_img_size, max_img_size );

    src_img  = cvCreateImage( img_size, src_depth, 1 );
    dst_img  = cvCreateImage( img_size, dst_depth, 1 );
    dst2_img = cvCreateImage( img_size, IPL_DEPTH_32F, 1 );
    dst3_img = cvCreateImage( img_size, IPL_DEPTH_32F, 1 );

    if( dst_depth == IPL_DEPTH_32F )
    {
        success_error_level = 1e-5;
    }

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1);
            int  iters = (base_iters*2 + denom)/(2*denom);
            CvRect roi = cvRect(0,0,w,h);

            cvSetImageROI( src_img, roi );
            cvSetImageROI( dst_img, roi );
            cvSetImageROI( dst2_img, roi );
            cvSetImageROI( dst3_img, roi );

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double err0 = 0;

                switch( src_depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_16S:
                    atsRandSetBounds( &rng_state, -img16s_range, img16s_range );
                    break;
                case IPL_DEPTH_32S:
                    atsRandSetBounds( &rng_state, -img16s_range*2, img16s_range*2 );
                    break;
                }

                atsFillRandomImageEx( src_img, &rng_state );

                for( c = 0; c < 2; c++ )
                {
                    double scale = 1, shift = 0;
                    
                    if( c == 1 )
                    {
                        scale = atsRandPlane32f( &rng_state )*4 - 2;
                        shift = atsRandPlane32f( &rng_state )*200 - 100;
                    }

                    if( scale == 0 ) scale = 0.001;

                    atsScaleAddImage( src_img, dst2_img, scale, shift );
                    if( dst_depth != IPL_DEPTH_32F )
                    {
                        atsConvert( dst2_img, dst_img );
                        atsConvert( dst_img, dst2_img );
                    }

                    cvConvertScale( src_img, dst_img, scale, shift );
                    atsConvert( dst_img, dst3_img );

                    err0 = iplNorm( dst2_img, dst3_img, IPL_C );

                    if( err > max_err )
                    {
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        max_err   = err;
                        if( max_err > success_error_level )
                            goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

    code = TRS_OK;

test_exit:

    cvReleaseImage( &dst_img );
    cvReleaseImage( &dst2_img );
    cvReleaseImage( &dst3_img );
    cvReleaseImage( &src_img );

    trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                       "iter = %d, seed = %08x",
                       max_err, merr_w, merr_h, merr_iter, seed );

    return max_err <= success_error_level ?
        trsResult( TRS_OK, "No errors" ) :
        trsResult( TRS_FAIL, "Bad accuracy" );
}

static int cvt_scale_abs_test( void* arg )
{
    static const int depths[] = { IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16S,
                                  IPL_DEPTH_32S, IPL_DEPTH_32F };
    
    double success_error_level = 1.00001;

    int   param     = (int)arg;
    int   src_depth = depths[param / 5];
    int   dst_depth = depths[param % 5];
    int   seed     = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  err = 0, max_err = 0.;
    int     code = TRS_OK;

    IplImage    *dst_img, *dst2_img, *dst3_img, *src_img;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_cvt_params();

    CvSize img_size = cvSize( max_img_size, max_img_size );

    src_img  = cvCreateImage( img_size, src_depth, 1 );
    dst_img  = cvCreateImage( img_size, dst_depth, 1 );
    dst2_img = cvCreateImage( img_size, IPL_DEPTH_32F, 1 );
    dst3_img = cvCreateImage( img_size, IPL_DEPTH_32F, 1 );

    if( dst_depth == IPL_DEPTH_32F )
    {
        success_error_level = 1e-5;
    }

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1);
            int  iters = (base_iters*2 + denom)/(2*denom);
            CvRect roi = cvRect(0,0,w,h);

            cvSetImageROI( src_img, roi );
            cvSetImageROI( dst_img, roi );
            cvSetImageROI( dst2_img, roi );
            cvSetImageROI( dst3_img, roi );

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                switch( src_depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_16S:
                    atsRandSetBounds( &rng_state, -img16s_range, img16s_range );
                    break;
                case IPL_DEPTH_32S:
                    atsRandSetBounds( &rng_state, -img16s_range*2, img16s_range*2 );
                    break;
                }

                atsFillRandomImageEx( src_img, &rng_state );

                for( c = 0; c < 2; c++ )
                {
                    double scale = 1, shift = 0;
                    
                    if( c == 1 )
                    {
                        scale = atsRandPlane32f( &rng_state )*4 - 2;
                        shift = atsRandPlane32f( &rng_state )*200 - 100;
                    }

                    if( scale == 0 ) scale = 0.001;

                    atsScaleAddAbsImage( src_img, dst2_img, scale, shift );
                    if( dst_depth != IPL_DEPTH_32F )
                    {
                        atsConvert( dst2_img, dst_img );
                        atsConvert( dst_img, dst2_img );
                    }

                    cvConvertScaleAbs( src_img, dst_img, scale, shift );
                    atsConvert( dst_img, dst3_img );

                    err = iplNorm( dst2_img, dst3_img, IPL_C );

                    if( err > max_err )
                    {
                        printf("%f %f\n", *(float*)dst3_img->imageData,
                                          *(float*)dst2_img->imageData);
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        max_err   = err;
                        if( max_err > success_error_level )
                            goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

    code = TRS_OK;

test_exit:

    cvReleaseImage( &dst_img );
    cvReleaseImage( &dst2_img );
    cvReleaseImage( &dst3_img );
    cvReleaseImage( &src_img );

    trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                       "iter = %d, seed = %08x",
                       max_err, merr_w, merr_h, merr_iter, seed );

    return max_err <= success_error_level ?
        trsResult( TRS_OK, "No errors" ) :
        trsResult( TRS_FAIL, "Bad accuracy" );
}

#if 0
static int deinterlace_prob(void)
{
    IplImage* src = cvvLoadImage("OAK.bmp");

    if( src )
    {
        IplImage* f0 = cvCreateImage( cvSize( src->width, src->height/2), 8, 3 );
        IplImage* f1 = cvCreateImage( cvSize( src->width, src->height/2), 8, 3 );

        cvDeInterlace( src, f0, f1 );

        cvvNamedWindow( "source", 1 );
        cvvNamedWindow( "even", 1 );
        cvvNamedWindow( "odd", 1 );

        cvvShowImage( "source", src );
        cvvShowImage( "even", f0 );
        cvvShowImage( "odd", f1 );

        cvvWaitKey(0);

        cvvDestroyWindow( "source" );
        cvvDestroyWindow( "even" );
        cvvDestroyWindow( "odd" );

        cvReleaseImage( &src );
        cvReleaseImage( &f0 );
        cvReleaseImage( &f1 );
    }

    return TRS_OK;
}

static int try_load_save_tiff(void)
{
    IplImage* src = cvvLoadImage("tigr.tif");

    if( src )
    {
        cvvSaveImage( "test2.tif", src );
        IplImage* dst = cvvLoadImage( "test2.tif" );

        cvvNamedWindow( "source", 1 );
        cvvNamedWindow( "dst", 1 );

        cvvShowImage( "source", src );
        cvvShowImage( "dst", dst );

        cvvWaitKey(0);

        cvvDestroyWindow( "source" );
        cvvDestroyWindow( "dst" );

        cvReleaseImage( &src );
        cvReleaseImage( &dst );
    }

    return TRS_OK;
}
#endif

#define CVT_PIX2PLANE_8UC3     0
#define CVT_PIX2PLANE_8UAC4    1
#define CVT_PIX2PLANE_32FC3    2
#define CVT_PIX2PLANE_32FAC4   3

#define CVT_PLANE2PIX_8UC3     0
#define CVT_PLANE2PIX_8UAC4    1
#define CVT_PLANE2PIX_32FC3    2
#define CVT_PLANE2PIX_32FAC4   3


#define CVT_8U16S      2
#define CVT_8U32F      4
#define CVT_8S16S      7
#define CVT_8S32F      9
#define CVT_16S8U      10
#define CVT_16S8S      11
#define CVT_16S32F     14
#define CVT_32S32F     19
#define CVT_32F8U      20
#define CVT_32F8S      21
#define CVT_32F16S     22
#define CVT_32F32S     23

void InitAConvert( void )
{
    /* Registering test functions */
    trsRegArg( funcs[0], test_desc, atsAlgoClass, cvt_pix_to_plane_test, CVT_PIX2PLANE_8UC3 );

    trsRegArg( funcs[0], test_desc, atsAlgoClass, cvt_pix_to_plane_test, CVT_PIX2PLANE_8UAC4 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, cvt_pix_to_plane_test, CVT_PIX2PLANE_32FC3 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, cvt_pix_to_plane_test, CVT_PIX2PLANE_32FAC4 );

    trsRegArg( funcs[1], test_desc, atsAlgoClass, cvt_plane_to_pix_test, CVT_PLANE2PIX_8UC3 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, cvt_plane_to_pix_test, CVT_PLANE2PIX_8UAC4 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, cvt_plane_to_pix_test, CVT_PLANE2PIX_32FC3 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, cvt_plane_to_pix_test, CVT_PLANE2PIX_32FAC4 );

    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_8U32F );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_32F8U );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_8S32F );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_32F8S );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_16S32F );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_32F16S );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_32S32F );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_32F32S );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_8U16S );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_16S8U );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_8S16S );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, cvt_scale_test, CVT_16S8S );

    trsRegArg( funcs[3], test_desc, atsAlgoClass, cvt_scale_abs_test, CVT_32F8U );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, cvt_scale_abs_test, CVT_16S8U );

    //trsReg( "cvDeInterface", "", atsAlgoClass, deinterlace_prob );
    //trsReg( "cvvLoadImage, cvvSaveImage (tif)", "", atsAlgoClass, try_load_save_tiff );

} /* InitAConvert */


/* End of file. */
