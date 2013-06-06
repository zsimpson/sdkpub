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
    "cvAbsDiff",
    "cvAbsDiffS"
};

static char *test_desc = "Test for absolute difference functions";

/* actual parameters */
static int min_img_size, max_img_size;
static int img_size_delta_type, img_size_delta;
static int base_iters;

/* which tests have to run */
static int dt_l = 0, dt_h = 1;

static int init_absdiff_params = 0;

static const int img8u_range = 255;
static const float img32f_range = 1000.f;
static const int img32f_bits = 23;

static void read_absdiff_params( void )
{
    if( !init_absdiff_params )
    {
        int  data_types;

        /* Determine which tests are needed to run */
        trsCaseRead( &data_types,"/a/8u/32f", "a",
            "a - all, 8u - unsigned char, 32f - float" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        /* read tests params */
        trsiRead( &min_img_size, "3", "Minimal width or height of image" );
        trsiRead( &max_img_size, "1000", "Maximal width or height of image" );
        trsCaseRead( &img_size_delta_type,"/a/m", "m", "a - add, m - multiply" );
        trsiRead( &img_size_delta, "3", "Image size step(factor)" );
        trsiRead( &base_iters, "1000", "Base number of iterations" );

        init_absdiff_params = 1;
    }
}


/* ///////////////////// absdiff_test ///////////////////////// */

static int absdiff_test( void* arg )
{
    const double success_error_level = 1e-6;

    int   param     = (int)arg;
    int   depth     = param;

    int   seed      = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       roi;
    IplImage    *src1_img, *src2_img, *dst_img;
    IplImage    *srcfl1_img, *srcfl2_img, *dstfl_img;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_absdiff_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ))) return TRS_UNDEF;

    depth = depth == 1 ? IPL_DEPTH_32F : IPL_DEPTH_8U;

    src1_img = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );
    src2_img = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );
    dst_img = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );

    srcfl1_img = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, 1, 0 );
    srcfl2_img = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, 1, 0 );
    dstfl_img = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, 1, 0 );

    src1_img->roi = src2_img->roi = dst_img->roi =
    srcfl1_img->roi = srcfl2_img->roi = dstfl_img->roi = &roi;

    roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1);
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = w;
            roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double err;

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

                atsFillRandomImageEx( src1_img, &rng_state );
                atsFillRandomImageEx( src2_img, &rng_state );

                atsConvert( src1_img, srcfl1_img );
                atsConvert( src2_img, srcfl2_img );
                
                iplSubtract( srcfl1_img, srcfl2_img, dstfl_img );
                iplAbs( dstfl_img, dstfl_img );

                cvAbsDiff( src1_img, src2_img, dst_img );

                atsConvert( dst_img, srcfl1_img );

                err = iplNorm( srcfl1_img, dstfl_img, IPL_C );

                if( err > max_err )
                {
                    merr_w    = w;
                    merr_h    = h;
                    merr_iter = i;
                    max_err   = err;
                    if( max_err > success_error_level ) goto test_exit;
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    src1_img->roi = src2_img->roi = dst_img->roi =
    srcfl1_img->roi = srcfl2_img->roi = dstfl_img->roi = 0;
    
    iplDeallocate( src1_img, IPL_IMAGE_ALL );
    iplDeallocate( src2_img, IPL_IMAGE_ALL );
    iplDeallocate( dst_img, IPL_IMAGE_ALL );

    iplDeallocate( srcfl1_img, IPL_IMAGE_ALL );
    iplDeallocate( srcfl2_img, IPL_IMAGE_ALL );
    iplDeallocate( dstfl_img, IPL_IMAGE_ALL );

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


/* ///////////////////// absdiff_scalar_test ///////////////////////// */

static int absdiff_scalar_test( void* arg )
{
    const double success_error_level = 1e-6;

    int   param     = (int)arg;
    int   depth     = param - 2;

    int   seed      = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0;
    double  max_err = 0.;
    //int     code = TRS_OK;

    IplROI       roi;
    IplImage    *src_img, *dst_img;
    IplImage    *srcfl_img, *dstfl_img;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_absdiff_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ))) return TRS_UNDEF;

    depth = depth == 1 ? IPL_DEPTH_32F : IPL_DEPTH_8U;

    src_img = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );
    dst_img = atsCreateImage( max_img_size, max_img_size, depth, 1, 0 );

    srcfl_img = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, 1, 0 );
    dstfl_img = atsCreateImage( max_img_size, max_img_size, IPL_DEPTH_32F, 1, 0 );

    src_img->roi = dst_img->roi = srcfl_img->roi = dstfl_img->roi = &roi;

    roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            int  denom = (w - min_img_size + 1)*(h - min_img_size + 1);
            int  iters = (base_iters*2 + denom)/(2*denom);

            roi.width = w;
            roi.height = h;

            if( iters < 1 ) iters = 1;

            for( i = 0; i < iters; i++ )
            {
                double err;
                double value = 0;

                switch( depth )
                {
                case IPL_DEPTH_8U:
                    atsRandSetBounds( &rng_state, 0, img8u_range );
                    value = atsRand32s( &rng_state );
                    break;
                case IPL_DEPTH_32F:
                    atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                    atsRandSetFloatBits( &rng_state, img32f_bits );
                    value = atsRand32f( &rng_state );
                    break;
                }

                atsFillRandomImageEx( src_img, &rng_state );
                atsFillRandomImageEx( dst_img, &rng_state );

                atsConvert( src_img, srcfl_img );
                atsConvert( dst_img, dstfl_img );
                
                iplSubtractSFP( srcfl_img, dstfl_img, (float)value, 0 );
                iplAbs( dstfl_img, dstfl_img );

                cvAbsDiffS( src_img, dst_img, cvScalar(value) );

                atsConvert( dst_img, srcfl_img );

                err = iplNorm( srcfl_img, dstfl_img, IPL_C );

                if( err > max_err )
                {
                    merr_w    = w;
                    merr_h    = h;
                    merr_iter = i;
                    max_err   = err;
                    if( max_err > success_error_level ) goto test_exit;
                }
            }
            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    src_img->roi = dst_img->roi = srcfl_img->roi = dstfl_img->roi = 0;
    
    iplDeallocate( src_img, IPL_IMAGE_ALL );
    iplDeallocate( dst_img, IPL_IMAGE_ALL );

    iplDeallocate( srcfl_img, IPL_IMAGE_ALL );
    iplDeallocate( dstfl_img, IPL_IMAGE_ALL );

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


#define ABSDIFF_8UC1      0
#define ABSDIFF_32FC1     1

#define ABSDIFFS_8UC1     2
#define ABSDIFFS_32FC1    3

void InitAAbsDiff( void )
{
    /* Registering test functions */
    trsRegArg( funcs[0], test_desc, atsAlgoClass, absdiff_test, ABSDIFF_8UC1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, absdiff_test, ABSDIFF_32FC1 );

    trsRegArg( funcs[1], test_desc, atsAlgoClass, absdiff_scalar_test, ABSDIFFS_8UC1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, absdiff_scalar_test, ABSDIFFS_32FC1 );

} /* InitAAbsDiff */

/* End of file. */
