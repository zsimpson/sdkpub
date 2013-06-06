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
    "cvCountNonZero",
    "cvSumPixels",
    "cvMinMaxLoc, cvMinMaxLocMask",
    "cvMean, cvMeanMask",
    "cvMean_StdDev, cvMean_StdDevMask",
};

static char *test_desc = "Comparing with the simple algorithm";
static const double ATS_SUCCESS_ERROR_LEVEL_FLT = 3e-5;

#define IMGSTAT_COUNT_NON_ZERO   0
#define IMGSTAT_SUM_PIXELS       1
#define IMGSTAT_MIN_MAX_LOC      2
#define IMGSTAT_MEAN             3
#define IMGSTAT_MEAN_STDDEV      4

/* actual parameters */
static int min_img_size, max_img_size;
static int img_size_delta_type, img_size_delta;
static int base_iters;

/* which tests have to run */
static int fn_l = 0, fn_h = ATS_DIM(funcs)-1,
           dt_l = 0, dt_h = 2,
           ch_l = 0, ch_h = 1;

static int init_img_stat_params = 0;

static const int mask_depth = IPL_DEPTH_8U;
static const int img8u_range = 255;
static const int img8s_range = 128;
static const float img32f_range = 1000.f;
static const int img32f_bits = 23;
static const int mask_mask = 0x80;

static double rel_err( double a, double b )
{
    return fabs(a - b)/(fabs(a) + 1e-10);
}

static double rel_err2( double a, double b, double abs_a )
{
    return fabs(a - b)/(abs_a + 1e-10);
}


static void read_img_stat_params( void )
{
    if( !init_img_stat_params )
    {
        int func, data_types, channels;

        /* Determine which tests are needed to run */
        trsCaseRead( &func, "/a/cnz/sum/mml/mn/md", "a",
                     "Function type: \n"
                     "a - all\n"
                     "cnz - CountNonZero\n"
                     "sum - SumPixels\n"
                     "mml - MinMaxLoc\n"
                     "mn  - Mean\n"
                     "md  - Mean_StdDev\n" );
        if( func != 0 ) fn_l = fn_h = func - 1;

        trsCaseRead( &data_types,"/a/8u/8s/32f", "a",
            "a - all, 8u - unsigned char, 8s - signed char, 32f - float" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        trsCaseRead( &channels, "/a/1/3", "a", "a - all, 1 - single channel, 3 - three channels" );
        if( channels != 0 ) ch_l = ch_h = channels - 1;

        /* read tests params */
        trsiRead( &min_img_size, "1", "Minimal width or height of image" );
        trsiRead( &max_img_size, "1000", "Maximal width or height of image" );
        trsCaseRead( &img_size_delta_type,"/a/m", "m", "a - add, m - multiply" );
        trsiRead( &img_size_delta, "3", "Image size step(factor)" );
        trsiRead( &base_iters, "1000", "Base number of iterations" );

        init_img_stat_params = 1;
    }
}


/* ///////////////////// count_non_zero_test ///////////////////////// */

static int count_non_zero_test( void* arg )
{
    const int success_error_level = 0;
    static const int img8u_range = 3;
    static const int img8s_range = 3;
    static const float img32f_range = 10.f;
    static const int img32f_bits = 4;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed      = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0, merr_c = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       roi;
    IplImage    *img, *img2;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_img_stat_params();

    if( !(ATS_RANGE( IMGSTAT_COUNT_NON_ZERO, fn_l, fn_h+1 ) &&
          ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 2 ? IPL_DEPTH_32F : depth == 1 ? IPL_DEPTH_8S : IPL_DEPTH_8U;
    channels = channels*2 + 1;

    img  = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    img2 = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, channels, 0 );

    roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;

    img->roi = img2->roi = &roi;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = w;
            roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                int etalon_result[3];

                switch( depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_32F:
                    atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                    atsRandSetFloatBits( &rng_state, img32f_bits );
                    break;
                }

                roi.coi = 0;
                atsFillRandomImageEx( img, &rng_state );

                if( depth != IPL_DEPTH_32F ) atsConvert( img, img2 );

                for( c = 1; c <= channels; c++ )
                {
                    roi.coi = c;
                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, 0,
                        0, 0, /* min & max vals */
                        0, 0, /* min & max locs */
                        &etalon_result[c-1], /* non_zero */
                        0, /* sum */
                        0, 0, /* mean & stddev */
                        0, 0, 0, 0 ); /* c_norm, l1_norm, l2_norm */
                }

                for( c = 1; c <= channels; c++ )
                {
                    double err0;
                    int result;

                    roi.coi = c;

                    /* //// ROI version /////// */
                    result = cvCountNonZero( img );
                    err0 = fabs( result - etalon_result[c-1] );

                    if( err0 > max_err )
                    {
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        merr_c    = c;
                        max_err   = err0;
                        if( max_err > success_error_level ) goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    img->roi = img2->roi = 0;

    atsReleaseImage( img );
    atsReleaseImage( img2 );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, merr_c, seed );

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


/* ///////////////////// sum_pixels_test ///////////////////////// */

static int sum_pixels_test( void* arg )
{
    double success_error_level = 0;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed     = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0, merr_c = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       roi;
    IplImage    *img, *img2;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_img_stat_params();

    if( !(ATS_RANGE( IMGSTAT_SUM_PIXELS, fn_l, fn_h+1 ) &&
          ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 2 ? IPL_DEPTH_32F : depth == 1 ? IPL_DEPTH_8S : IPL_DEPTH_8U;
    channels = channels*2 + 1;

    img  = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    img2 = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, channels, 0 );

    roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;

    img->roi = img2->roi = &roi;

    if( depth == IPL_DEPTH_32F ) success_error_level = ATS_SUCCESS_ERROR_LEVEL_FLT;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = w;
            roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double  etalon_result[3];
                double  etalon_norm[3];

                switch( depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_32F:
                    atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                    atsRandSetFloatBits( &rng_state, img32f_bits );
                    break;
                }

                roi.coi = 0;
                atsFillRandomImageEx( img, &rng_state );

                if( depth != IPL_DEPTH_32F ) atsConvert( img, img2 );

                for( c = 1; c <= channels; c++ )
                {
                    roi.coi = c;
                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, 0,
                        0, 0, /* min & max vals */
                        0, 0, /* min & max locs */
                        0, /* non_zero */
                        &etalon_result[c-1], /* sum */
                        0, 0, /* mean & stddev */
                        0, 0, &etalon_norm[c-1], 0 ); /* c_norm, l1_norm, l2_norm */
                }

                for( c = 1; c <= channels; c++ )
                {
                    double  err0;
                    double  result;

                    roi.coi = c;

                    /* //// ROI version /////// */
                    result = cvSumPixels( img );
                    err0 = rel_err2( etalon_result[c-1], result, etalon_norm[c-1]);

                    if( err0 > max_err )
                    {
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        merr_c    = c;
                        max_err   = err0;
                        if( max_err > success_error_level )
                            goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    img->roi = img2->roi = 0;

    atsReleaseImage( img );
    atsReleaseImage( img2 );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, merr_c, seed );

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


/* ///////////////////// mean_test ///////////////////////// */

static int mean_test( void* arg )
{
    double  success_error_level = ATS_SUCCESS_ERROR_LEVEL_FLT;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0, merr_c = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       roi, mask_roi;
    IplImage    *img, *img2, *mask, *mask2;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_img_stat_params();

    if( !(ATS_RANGE( IMGSTAT_MEAN, fn_l, fn_h+1 ) &&
          ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 2 ? IPL_DEPTH_32F : depth == 1 ? IPL_DEPTH_8S : IPL_DEPTH_8U;
    channels = channels*2 + 1;

    img  = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    img2 = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, channels, 0 );
    mask = atsCreateImage( max_img_size, max_img_size, mask_depth, 1, 0 );
    mask2 = atsCreateImage( max_img_size, max_img_size, mask_depth, 1, 0 );

    roi.coi = mask_roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;
    mask_roi.xOffset = mask_roi.yOffset = 0;

    img->roi = img2->roi = &roi;
    mask->roi = &mask_roi;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = mask_roi.width = w;
            roi.height = mask_roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double  etalon_result[3];
                double  etalon_mask_result[3];
                double  etalon_norm[3];
                double  etalon_mask_norm[3];
                int     mask_pix;

                switch( depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_32F:
                    atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                    atsRandSetFloatBits( &rng_state, img32f_bits );
                    break;
                }

                roi.coi = 0;
                atsFillRandomImageEx( img, &rng_state );

                atsRandSetBounds( &rng_state, 0, 255 );
                atsFillRandomImageEx( mask, &rng_state );
                iplAndS( mask, mask, mask_mask );

                if( depth != IPL_DEPTH_32F ) atsConvert( img, img2 );

                for( c = 1; c <= channels; c++ )
                {
                    roi.coi = c;
                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, 0,
                        0, 0, /* min & max vals */
                        0, 0, /* min & max locs */
                        0, /* non_zero */
                        0, /* sum */
                        &etalon_result[c-1], 0, /* mean & stddev */
                        0, &etalon_norm[c-1], 0, 0 ); /* c_norm, l1_norm, l2_norm */

                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, mask,
                        0, 0, /* min & max vals */
                        0, 0, /* min & max locs */
                        0, /* non_zero */
                        0, /* sum */
                        &etalon_mask_result[c-1], 0, /* mean & stddev */
                        0, &etalon_mask_norm[c-1], 0, &mask_pix ); /* c_norm, l1_norm, l2_norm */
                    etalon_norm[c-1] /= (w*h);
                    etalon_mask_norm[c-1] /= MAX(mask_pix,1);
                }

                for( c = 1; c <= channels; c++ )
                {
                    double  err0, err1;
                    double  result;

                    roi.coi = c;

                    /* //// ROI version /////// */
                    result = cvMean( img );
                    err0 = rel_err2( etalon_result[c-1], result, etalon_norm[c-1] );

                    /* //// ROI Mask version /////// */
                    result = cvMeanMask( img, mask );

                    err1 = rel_err2( etalon_mask_result[c-1], result,
                                     etalon_mask_norm[c-1] );
                    err0 = MAX( err0, err1 );

                    if( err0 > max_err )
                    {
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        merr_c    = c;
                        max_err   = err0;
                        if( max_err > success_error_level ) goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    img->roi = img2->roi = mask->roi = 0;

    atsReleaseImage( img );
    atsReleaseImage( img2 );
    atsReleaseImage( mask );
    atsReleaseImage( mask2 );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, merr_c, seed );

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


/* ///////////////////// mean_test ///////////////////////// */

static int mean_stddev_test( void* arg )
{
    double  success_error_level = ATS_SUCCESS_ERROR_LEVEL_FLT;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0, merr_c = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       roi, mask_roi;
    IplImage    *img, *img2, *mask, *mask2;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_img_stat_params();

    if( !(ATS_RANGE( IMGSTAT_MEAN_STDDEV, fn_l, fn_h+1 ) &&
          ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 2 ? IPL_DEPTH_32F : depth == 1 ? IPL_DEPTH_8S : IPL_DEPTH_8U;
    channels = channels*2 + 1;

    img  = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    img2 = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, channels, 0 );
    mask = atsCreateImage( max_img_size, max_img_size, mask_depth, 1, 0 );
    mask2 = atsCreateImage( max_img_size, max_img_size, mask_depth, 1, 0 );

    roi.coi = mask_roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;
    mask_roi.xOffset = mask_roi.yOffset = 0;

    img->roi = img2->roi = &roi;
    mask->roi = &mask_roi;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = mask_roi.width = w;
            roi.height = mask_roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double  etalon_result[6];
                double  etalon_mask_result[6];

                switch( depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_32F:
                    atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                    atsRandSetFloatBits( &rng_state, img32f_bits );
                    break;
                }

                roi.coi = 0;
                atsFillRandomImageEx( img, &rng_state );

                atsRandSetBounds( &rng_state, 0, 255 );
                atsFillRandomImageEx( mask, &rng_state );
                iplAndS( mask, mask, mask_mask );

                if( depth != IPL_DEPTH_32F ) atsConvert( img, img2 );

                for( c = 1; c <= channels; c++ )
                {
                    roi.coi = c;
                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, 0,
                        0, 0, /* min & max vals */
                        0, 0, /* min & max locs */
                        0, /* non_zero */
                        0, /* sum */
                        &etalon_result[2*c-2], &etalon_result[2*c-1], /* mean & stddev */
                        0, 0, 0, 0 ); /* c_norm, l1_norm, l2_norm */

                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, mask,
                        0, 0, /* min & max vals */
                        0, 0, /* min & max locs */
                        0, /* non_zero */
                        0, /* sum */
                        &etalon_mask_result[2*c-2],
                        &etalon_mask_result[2*c-1], /* mean & stddev */
                        0, 0, 0, 0 ); /* c_norm, l1_norm, l2_norm */
                }

                for( c = 1; c <= channels; c++ )
                {
                    double  mean_err0, stddev_err0, err1;
                    double  result[2];

                    roi.coi = c;

                    /* //// ROI version /////// */
                    cvMean_StdDev( img, result+0, result+1 );

                    mean_err0 = rel_err( etalon_result[2*c-2], result[0] );
                    stddev_err0 = rel_err( etalon_result[2*c-1], result[1] );

                    cvMean_StdDevMask( img, mask, result+0, result+1 );
                    err1 = rel_err( etalon_mask_result[2*c-2], result[0] );
                    mean_err0 = MAX( mean_err0, err1 );
                    err1 = rel_err( etalon_mask_result[2*c-1], result[1] );
                    stddev_err0 = MAX( stddev_err0, err1 );

                    if( mean_err0 > max_err )
                    {
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        merr_c    = c;
                        max_err   = mean_err0;
                        if( max_err > success_error_level ) goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    img->roi = img2->roi = mask->roi = 0;

    iplDeallocate( img, IPL_IMAGE_ALL );
    iplDeallocate( img2, IPL_IMAGE_ALL );
    iplDeallocate( mask, IPL_IMAGE_ALL );
    iplDeallocate( mask2, IPL_IMAGE_ALL );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, merr_c, seed );

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


/* ///////////////////// min_max_loc_test ///////////////////////// */

static double check_extr_point( IplImage* img, IplImage* mask, CvPoint pt,
                                double etalon_value )
{
    double val = 0;
    int ch, nch;

    if( mask && mask->imageData[pt.y*mask->widthStep + pt.x] == 0 ) return 1e30;

    ch = img->roi->coi;
    ch = ch == 0 ? 0 : ch - 1;
    nch = img->nChannels;

    switch( img->depth )
    {
    case IPL_DEPTH_8U:
        val = ((uchar*)img->imageData)[pt.y*img->widthStep + pt.x*nch + ch];
        break;
    case IPL_DEPTH_8S:
        val = ((char*)img->imageData)[pt.y*img->widthStep + pt.x*nch + ch];
        break;
    case IPL_DEPTH_32F:
        val = ((float*)img->imageData)[pt.y*(img->widthStep/4) + pt.x*nch + ch];
        break;
    default:
        assert(0);
        return 1e30;
    }

    return fabs( etalon_value - val );
}


static int min_max_loc_test( void* arg )
{
    const float success_error_level = 0;

    int   param     = (int)arg;
    int   depth     = param/2;
    int   channels  = (param & 1);

    int   seed     = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0, merr_c = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0, c = 0;
    double  max_err = 0.;
    int     code = TRS_OK;

    IplROI       roi, mask_roi;
    IplImage    *img, *img2, *mask, *mask2;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_img_stat_params();

    if( !(ATS_RANGE( IMGSTAT_MIN_MAX_LOC, fn_l, fn_h+1 ) &&
          ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    depth = depth == 2 ? IPL_DEPTH_32F : depth == 1 ? IPL_DEPTH_8S : IPL_DEPTH_8U;
    channels = channels*2 + 1;

    img  = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    img2 = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, channels, 0 );
    mask = atsCreateImage( max_img_size, max_img_size, mask_depth, 1, 0 );
    mask2 = atsCreateImage( max_img_size, max_img_size, mask_depth, 1, 0 );

    roi.coi = mask_roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;
    mask_roi.xOffset = mask_roi.yOffset = 0;

    img->roi = img2->roi = &roi;
    mask->roi = &mask_roi;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1)*channels;
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = mask_roi.width = w;
            roi.height = mask_roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double  etalon_result[6];
                double  etalon_mask_result[6];
                CvPoint etalon_loc[6];
                CvPoint etalon_mask_loc[6];
                int      mask_pix = 0;

                switch( depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    break;
                case IPL_DEPTH_8S:
                    atsRandSetBounds( &rng_state, -img8s_range, img8s_range );
                    break;
                case IPL_DEPTH_32F:
                    atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                    atsRandSetFloatBits( &rng_state, img32f_bits );
                    break;
                }

                roi.coi = 0;
                atsFillRandomImageEx( img, &rng_state );

                atsRandSetBounds( &rng_state, 0, 255 );
                atsFillRandomImageEx( mask, &rng_state );
                iplAndS( mask, mask, mask_mask );

                if( depth != IPL_DEPTH_32F ) atsConvert( img, img2 );

                for( c = 1; c <= channels; c++ )
                {
                    roi.coi = c;
                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, 0,
                        &etalon_result[2*c-2], &etalon_result[2*c-1],  /* min & max vals */
                        &etalon_loc[2*c-2], &etalon_loc[2*c-1],  /* min & max locs */
                        0, /* non_zero */
                        0, /* sum */
                        0, 0, /* mean & stddev */
                        0, 0, 0, 0 ); /* c_norm, l1_norm, l2_norm */

                    atsCalcImageStatistics(
                        depth == IPL_DEPTH_32F ? img : img2, mask,
                        &etalon_mask_result[2*c-2], &etalon_mask_result[2*c-1],  /* min & max vals */
                        &etalon_mask_loc[2*c-2], &etalon_mask_loc[2*c-1],  /* min & max locs */
                        0, /* non_zero */
                        0, /* sum */
                        0, 0, /* mean & stddev */
                        0, 0, 0, &mask_pix ); /* c_norm, l1_norm, l2_norm */
                }

                for( c = 1; c <= channels; c++ )
                {
                    double  minmax_err0 = 0, dist_err0 = 0, err1 = 0;
                    double  result[2];
                    CvPoint loc[2];

                    roi.coi = c;

                    //printf("\r%5d%5d%6d%3d", h, w, i, c );

                    /* //// ROI version /////// */
                    cvMinMaxLoc( img, result+0, result+1, loc+0, loc+1 );
                    
                    minmax_err0 = rel_err( etalon_result[2*c-2], result[0] );
                    err1 = rel_err( etalon_result[2*c-1], result[1] );
                    minmax_err0 = MAX( minmax_err0, err1 );
                    dist_err0 = check_extr_point( img, 0, loc[0], etalon_result[2*c-2] );
                    err1 = check_extr_point( img, 0, loc[1], etalon_result[2*c-1] );
                    dist_err0 = MAX( dist_err0, err1 );

                    /* //// ROI Mask version /////// */
                    cvMinMaxLocMask( img, mask, result+0, result+1, loc+0, loc+1 );

                    if( mask_pix == 0 )
                    {
                        if( loc[0].x != 0 || loc[0].y != 0 ||
                            loc[1].x != 0 || loc[1].y != 0 ||
                            result[0] != 0 || result[1] != 0 )
                        {
                            code = TRS_FAIL;
                            goto test_exit;
                        }
                    }
                    else
                    {
                        err1 = rel_err( etalon_mask_result[2*c-2], result[0] );
                        minmax_err0 = MAX( minmax_err0, err1 );
                        err1 = rel_err( etalon_mask_result[2*c-1], result[1] );
                        minmax_err0 = MAX( minmax_err0, err1 );
                        err1 = check_extr_point( img, mask, loc[0], etalon_mask_result[2*c-2] );
                        dist_err0 = MAX( dist_err0, err1 );
                        err1 = check_extr_point( img, mask, loc[1], etalon_mask_result[2*c-1] );
                        dist_err0 = MAX( dist_err0, err1 );
                    }

                    if( minmax_err0 > max_err || dist_err0 != 0 )
                    {
                        merr_w    = w;
                        merr_h    = h;
                        merr_iter = i;
                        merr_c    = c;
                        max_err   = minmax_err0;
                        if( dist_err0 != 0 )
                        {
                            max_err = 1e30;
                            goto test_exit;
                        }

                        if( max_err > success_error_level )
                            goto test_exit;
                    }
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    img->roi = img2->roi = mask->roi = 0;

    iplDeallocate( img, IPL_IMAGE_ALL );
    iplDeallocate( img2, IPL_IMAGE_ALL );
    iplDeallocate( mask, IPL_IMAGE_ALL );
    iplDeallocate( mask2, IPL_IMAGE_ALL );

    if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, merr_c, seed );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
    else
    {
        trsWrite( ATS_LST, "Fatal error at w = %d, h = %d, "
                           "iter = %d, c = %d, seed = %08x",
                           w, h, i, c, seed );
        return trsResult( TRS_FAIL, "Function returns error code" );
    }
}


#define _8U_C1     0
#define _8U_C3     1
#define _8S_C1     2
#define _8S_C3     3
#define _32F_C1    4
#define _32F_C3    5

void InitAImageStatistics( void )
{
    /* Register test functions */
    trsRegArg( funcs[0], test_desc, atsAlgoClass, count_non_zero_test, _8U_C1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, count_non_zero_test, _8U_C3 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, count_non_zero_test, _8S_C1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, count_non_zero_test, _8S_C3 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, count_non_zero_test, _32F_C1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, count_non_zero_test, _32F_C3 );

    trsRegArg( funcs[1], test_desc, atsAlgoClass, sum_pixels_test, _8U_C1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, sum_pixels_test, _8U_C3 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, sum_pixels_test, _8S_C1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, sum_pixels_test, _8S_C3 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, sum_pixels_test, _32F_C1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, sum_pixels_test, _32F_C3 );

    trsRegArg( funcs[2], test_desc, atsAlgoClass, min_max_loc_test, _8U_C1 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, min_max_loc_test, _8U_C3 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, min_max_loc_test, _8S_C1 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, min_max_loc_test, _8S_C3 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, min_max_loc_test, _32F_C1 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, min_max_loc_test, _32F_C3 );

    trsRegArg( funcs[3], test_desc, atsAlgoClass, mean_test, _8U_C1 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, mean_test, _8U_C3 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, mean_test, _8S_C1 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, mean_test, _8S_C3 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, mean_test, _32F_C1 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, mean_test, _32F_C3 );

    trsRegArg( funcs[4], test_desc, atsAlgoClass, mean_stddev_test, _8U_C1 );
    trsRegArg( funcs[4], test_desc, atsAlgoClass, mean_stddev_test, _8U_C3 );
    trsRegArg( funcs[4], test_desc, atsAlgoClass, mean_stddev_test, _8S_C1 );
    trsRegArg( funcs[4], test_desc, atsAlgoClass, mean_stddev_test, _8S_C3 );
    trsRegArg( funcs[4], test_desc, atsAlgoClass, mean_stddev_test, _32F_C1 );
    trsRegArg( funcs[4], test_desc, atsAlgoClass, mean_stddev_test, _32F_C3 );

} /* InitAImageStatistics */

/* End of file. */
