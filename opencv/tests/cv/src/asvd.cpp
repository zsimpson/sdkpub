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
    "cvSVD, cvPseudoInv"
};

static char *test_desc = "Test of conversion functions using IPL";

/* actual parameters */
static int min_mat_size, max_mat_size;
static int base_iters;

/* which tests have to run */
static int dt_l = 0, dt_h = 1;

static int init_svd_params = 0;

static void read_svd_params( void )
{
    if( !init_svd_params )
    {
        int  data_types;

        /* Determine which tests are needed to run */
        trsCaseRead( &data_types,"/a/32f/64f", "a",
            "a - all, 32f - float, 64f - double" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        /* read tests params */
        trsiRead( &min_mat_size, "2", "Minimal matrix size" );
        trsiRead( &max_mat_size, "100", "Maximal matrix size" );
        trsiRead( &base_iters, "100", "Base number of iterations" );

        init_svd_params = 1;
    }
}


/* ///////////////////// cvt_pix_to_plane_test ///////////////////////// */

static int svd_test( void* arg )
{
    const double success_error_level = 1e-5;

    int   depth     = (int)arg;
    int   seed      = -1;//atsGetSeed();

    /* position where the maximum error occured */
    int   merr_w = 0, merr_h = 0, merr_iter = 0;

    /* test parameters */
    int     w = 0, h = 0, i = 0;
    double  max_err = 0.;

    CvMat       *src = 0, *W = 0, *U = 0, *V = 0, *dst = 0,
                *U2 = 0, *V2 = 0;
    AtsRandState rng_state;

    atsRandInit( &rng_state, 0, 1, seed );

    read_svd_params();

    if( !ATS_RANGE( depth, dt_l, dt_h+1 )) return TRS_UNDEF;

    depth = depth ? CV_64FC1 : CV_32FC1;

    for( i = 0; i < base_iters; i++ )
    {
        double normU, normV, normA, normInv = 0;
        
        w = atsRandPlain32s( &rng_state ) %
            (max_mat_size - min_mat_size) + min_mat_size;

        h = atsRandPlain32s( &rng_state ) %
            (max_mat_size - min_mat_size) + min_mat_size;

        if( w > h )
        {
            int t;
            CV_SWAP( w, h, t );
        }

        src = cvCreateMat( h, w, depth );
        dst = cvCreateMat( h, w, depth );
        U = cvCreateMat( h, h, depth );
        V = cvCreateMat( w, w, depth );
        U2 = cvCreateMat( h, h, depth );
        V2 = cvCreateMat( w, w, depth );
        W = cvCreateMat( h, w, depth );

        if( depth == CV_32FC1 )
        {
            atsbRand32f( &rng_state, src->data.fl, w*h );
        }
        else
        {
            atsbRand64d( &rng_state, src->data.db, w*h );
        }

        cvCopy( src, dst );
        cvSVD( src, W, U, V/*, CV_SVD_MODIFY_A | CV_SVD_U_T | CV_SVD_V_T*/ );

        cvMulTransposed( U, U2, 0 );
        cvMulTransposed( V, V2, 0 );

        //cvT( U, U );
        cvT( V, V );
        cvMatMul( U, W, src );
        cvMatMul( src, V, W );
        
        cvSetIdentity( U );
        cvSetIdentity( V );

        normU = cvNorm( U, U2, CV_C );
        normV = cvNorm( V, V2, CV_C );
        normA = cvNorm( W, dst, CV_C );

        /*cvPseudoInv( dst, inv );
        cvMatMul( dst, inv, U2 );
        normInv = cvNorm( U, U2, CV_L1 );*/

        cvReleaseMat( &src );
        cvReleaseMat( &dst );
        cvReleaseMat( &U );
        cvReleaseMat( &V );
        cvReleaseMat( &U2 );
        cvReleaseMat( &V2 );
        cvReleaseMat( &W );

        if( normU > success_error_level ||
            normV > success_error_level ||
            normA > success_error_level ||
            normInv > 3 )
        {
            max_err = normV;
            max_err = MAX( max_err, normU );
            max_err = MAX( max_err, normA );
            max_err = MAX( max_err, normInv );
            merr_w = w; merr_h = h; merr_iter = i;
            break;
        }
    }

    {
        trsWrite( ATS_LST, "Max err is %g at w = %d, h = %d, "
                           "iter = %d, seed = %08x",
                           max_err, merr_w, merr_h, merr_iter, seed );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
}

#define _32FC1  0
#define _64FC1  1

void InitASVD( void )
{
    /* Registering test functions */
    trsRegArg( funcs[0], test_desc, atsAlgoClass, svd_test, _32FC1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, svd_test, _64FC1 );

} /* InitASVD */


/* End of file. */
