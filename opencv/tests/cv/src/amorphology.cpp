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

static char *test_desc = "Comparing with the simple algorithm";

/* actual parameters */
static int min_img_size, max_img_size;
static int img_size_delta_type, img_size_delta;
static int min_el_size, max_el_size;
static int el_size_delta_type, el_size_delta;
static int base_iters;

/* which tests have to run */
static int mop_l = 0, mop_h = 1,
           dt_l = 0, dt_h = 1,
           ch_l = 0, ch_h = 2;

static int init_morph_params = 0;

static const int img8u_range = 255;
static const int img8s_range = 128;
static const float img32f_range = 1000.f;
static const int img32f_bits  = 23;

static char* funcs[] =
{
    "cvErode",
    "cvDilate"
};

static void read_moprh_params( void )
{
    if( !init_morph_params )
    {
        int morph_op, data_types, channels;

        /* Determine which tests are needed to run */
        trsCaseRead( &morph_op, "/a/e/d", "a", "a - all, e - erode, d - dilate" );
        if( morph_op != 0 ) mop_l = mop_h = morph_op - 1;

        trsCaseRead( &data_types,"/a/8u/32f", "a",
            "a - all, 8u - unsigned char, 32f - float" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        trsCaseRead( &channels, "/a/1/3/4", "a",
            "a - all, 1-single channel, 3-three channels, 4-three channels and alpha");
        if( channels != 0 ) ch_l = ch_h = channels - 1;

        /* read test params */
        trsiRead( &min_img_size, "1", "Minimal linear size of the image" );
        trsiRead( &max_img_size, "27", "Maximal linear size of the image" );
        trsCaseRead( &img_size_delta_type,"/a/m", "m", "a - add, m - multiply" );
        trsiRead( &img_size_delta, "3", "Image size step(factor)" );

        trsiRead( &min_el_size, "1", "Minimal linear size of the element" );
        trsiRead( &max_el_size, "10", "Maximal linear size of the element" );
        trsCaseRead( &el_size_delta_type,"/a/m", "a", "a - add, m - multiply" );
        trsiRead( &el_size_delta, "1", "Element size delta" );

        trsiRead( &base_iters, "100", "Base number of iterations" );

        init_morph_params = 1;
    }
}

#define amoErode   0
#define amoDilate  1

static int MorphTest( void* arg )
{
    int   param    = (int)arg;
    int   mop      = param < 6 ? amoErode : amoDilate;
    int   depth    = (param % 6) >= 3 ? IPL_DEPTH_32F : IPL_DEPTH_8U;
    int   ch_idx   = (param % 3);
    int   channels = ch_idx == 2 ? 4 : ch_idx == 1 ? 3 : 1;
    int   w = 0, h = 0, rows = 0, cols = 0, i = 0, ax = 0, ay = 0;
    int   merr_w = 0, merr_h = 0, merr_rows = 0,
          merr_cols = 0, merr_ax = 0, merr_ay = 0, merr_iter = 0;
    double      max_err = 0.;

    int         seed = atsGetSeed();

    int*        element_vals = 0;
    IplConvKernel  *element = 0;
    double      success_error_level;
    int         code = TRS_OK;
    IplROI      roi;
    IplImage    *src, *dst, *dst2;
    AtsRandState    rng_state;
    atsRandInit( &rng_state, 0, 1, seed );

    read_moprh_params();

    if( !(ATS_RANGE((int)(param >= 6), mop_l, mop_h+1) &&
          ATS_RANGE((int)((param % 6) >= 3), dt_l, dt_h+1) &&
          ATS_RANGE((int)((param % 3)), ch_l, ch_h+1)))
          return TRS_UNDEF;

    src = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    dst = atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );
    dst2= atsCreateImage( max_img_size, max_img_size, depth, channels, 0 );

    element_vals = (int*)malloc( max_el_size*max_el_size*sizeof(int));

    roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;

    src->roi = dst->roi = dst2->roi = &roi;

    if( depth == IPL_DEPTH_32F )
    {
        success_error_level = 1e-6;
    }
    else
    {
        assert( depth == IPL_DEPTH_8U );
        success_error_level = 0.;
    }

    for( h = min_img_size; h <= max_img_size; )
    {
        for( w = min_img_size; w <= max_img_size; )
        {
            roi.width  = w;
            roi.height = h;

            for( rows = min_el_size; rows < max_el_size; )
            {
                for( cols = min_el_size; cols < max_el_size; )
                {
                    int  denom = (w - min_img_size+1)*(h - min_img_size+1)*
                                 (rows - min_el_size+1)*(cols - min_el_size+1)*
                                 channels;
                    int  iters = (base_iters*2+denom)/(2*denom);

                    switch( depth )
                    {
                    case IPL_DEPTH_8U:
                        atsRandSetBounds( &rng_state, 0, img8u_range );
                        break;
                    case IPL_DEPTH_32F:
                        atsRandSetBounds( &rng_state, -img32f_range, img32f_range );
                        atsRandSetFloatBits( &rng_state, img32f_bits );
                        break;
                    default:
                        assert(0);
                        code = TRS_FAIL;
                        goto test_exit;
                    }
                    atsFillRandomImageEx( src, &rng_state );

                    if( iters < 3 ) iters = 3;

                    for( i = 0; i < iters; i++ )
                    {
                        double err0;
                        CvElementShape shape = i == 0 ? CV_SHAPE_RECT :
                                               i == 1 ? CV_SHAPE_CROSS :
                                               CV_SHAPE_CUSTOM;

                        atsRandSetBounds( &rng_state, 0, 1 << 16 );
                        ax = atsRand32s( &rng_state ) % cols;
                        ay = atsRand32s( &rng_state ) % rows;

                        if( shape == CV_SHAPE_CUSTOM )
                        {
                            atsRandSetBounds( &rng_state, 0, 2 );
                            atsbRand32s( &rng_state, element_vals, rows*cols );
                            int idx = atsRandPlain32s( &rng_state );
                            element_vals[idx % (rows*cols)] = 1;
                        }

                        element = cvCreateStructuringElementEx( cols, rows, ax, ay,
                                                                shape, element_vals );

                        if( mop == amoErode )
                            atsMinFilterEx( src, dst, (IplConvKernel*)element );
                        else
                            atsMaxFilterEx( src, dst, (IplConvKernel*)element );

                        if( mop == amoErode )
                            cvErode( src, dst2, element, 1 );
                        else
                            cvDilate( src, dst2, element, 1 );

                        err0 = iplNorm( dst, dst2, IPL_C );

                        roi.xOffset = 0;
                        roi.width = w;

                        cvReleaseStructuringElement( &element );

                        if( err0 > max_err )
                        {
                            merr_w    = w;
                            merr_h    = h;
                            merr_rows = rows;
                            merr_cols = cols;
                            merr_ax   = ax;
                            merr_ay   = ay;
                            merr_iter = i;
                            max_err   = err0;
                            if( max_err > success_error_level ) goto test_exit;
                        }
                    }
                    ATS_INCREASE( cols, el_size_delta_type, el_size_delta );
                }  /* end of the loop by cols */
                ATS_INCREASE( rows, el_size_delta_type, el_size_delta );
            } /* end of the loop by rows */

            ATS_INCREASE( w, img_size_delta_type, img_size_delta );
        } /* end of the loop by w */

        ATS_INCREASE( h, img_size_delta_type, img_size_delta );
    }  /* end of the loop by h */

test_exit:

    src->roi = dst->roi = dst2->roi = 0;

    atsReleaseImage( src );
    atsReleaseImage( dst );
    atsReleaseImage( dst2 );

    cvReleaseStructuringElement( &element );
    free( element_vals );

    if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "cols = %d, rows = %d, ax = %d, ay = %d, iter = %d",
                           max_err, merr_w, merr_h, merr_cols, merr_rows,
                           merr_ax, merr_ay, merr_iter );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
    else
    {
        trsWrite( ATS_LST, "Fatal error at w = %d, "
                           "h = %d, rows = %d, cols = %d, "
                           "ax = %d, ay = %d, iter = %d",
                           w, h, rows, cols, ax, ay, i );
        return trsResult( TRS_FAIL, "Function returns error code" );
    }
}

#define  ERODE_8U_C1       0
#define  ERODE_8U_C3       1
#define  ERODE_8U_AC4      2
#define  ERODE_32F_C1      3
#define  ERODE_32F_C3      4
#define  ERODE_32F_AC4     5

#define  DILATE_8U_C1      6
#define  DILATE_8U_C3      7
#define  DILATE_8U_AC4     8
#define  DILATE_32F_C1     9
#define  DILATE_32F_C3    10
#define  DILATE_32F_AC4   11

void InitAMorphology( void )
{
    /* Registering test functions */
    trsRegArg( funcs[0],  test_desc, atsAlgoClass, MorphTest, ERODE_8U_C1 );
    trsRegArg( funcs[0],  test_desc, atsAlgoClass, MorphTest, ERODE_8U_C3 );
    trsRegArg( funcs[0],  test_desc, atsAlgoClass, MorphTest, ERODE_8U_AC4 );
    trsRegArg( funcs[0],  test_desc, atsAlgoClass, MorphTest, ERODE_32F_C1 );
    trsRegArg( funcs[0],  test_desc, atsAlgoClass, MorphTest, ERODE_32F_C3 );
    trsRegArg( funcs[0],  test_desc, atsAlgoClass, MorphTest, ERODE_32F_AC4 );
    
    trsRegArg( funcs[1],  test_desc, atsAlgoClass, MorphTest, DILATE_8U_C1 );
    trsRegArg( funcs[1],  test_desc, atsAlgoClass, MorphTest, DILATE_8U_C3 );
    trsRegArg( funcs[1],  test_desc, atsAlgoClass, MorphTest, DILATE_8U_AC4 );
    trsRegArg( funcs[1],  test_desc, atsAlgoClass, MorphTest, DILATE_32F_C1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, MorphTest, DILATE_32F_C3 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, MorphTest, DILATE_32F_AC4 );
} /* InitAMorphology */

/* End of file. */
