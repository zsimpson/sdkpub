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
    "cvAdd",
    "cvSub",
    "cvMul",
    "cvAddS",
    "cvSubRS"
};

static char *test_desc = "Comparing with the simple algorithm";
static const double ATS_SUCCESS_ERROR_LEVEL_FLT = 1e-6;

/* actual parameters */
static int min_img_size, max_img_size;
static int base_iters;

static int init_arithm_params = 0;

static const int img8u_range = 255;
static const int img8s_range = 128;
static const int img16s_range = 32768;
static const int img32s_range = INT_MAX;
static const float img32f_range = 1000.f;

/* which tests have to run */
static int fn_l = 0, fn_h = ATS_DIM(funcs)-1,
           dt_l = 0, dt_h = 5,
           ch_l = 0, ch_h = 3;

static void read_arithm_params( void )
{
    if( !init_arithm_params )
    {
        int data_types, channels;

        trsCaseRead( &data_types,"/a/8u/8s/16s/32s/32f/64f", "a",
            "a - all, 8u - uchar, 8s - char, 16s - short, 32s - int, 32f - float, 64f - float" );
        if( data_types != 0 ) dt_l = dt_h = data_types - 1;

        trsCaseRead( &channels, "/a/1/2/3/4", "a", "a - all, 1 - 1, 2 - 2, 3 - 3, 4 - 4" );
        if( channels != 0 ) ch_l = ch_h = channels - 1;

        /* read tests params */
        trsiRead( &min_img_size, "1", "Minimal width or height of image" );
        trsiRead( &max_img_size, "100", "Maximal width or height of image" );
        trsiRead( &base_iters, "300", "Base number of iterations" );

        init_arithm_params = 1;
    }
}


typedef void (*AtsBinArithmMaskFunc)( const CvArr* src1, const CvArr* src2,
                                 CvArr* dst, const CvArr* mask );

typedef void (*AtsUnArithmMaskFunc)( const CvArr* src, CvScalar scalar,
                                    CvArr* dst, const CvArr* mask );

typedef void (*AtsBinArithmFunc)( const CvArr* src1, const CvArr* src2,
                                  CvArr* dst );


/* ///////////////////// arithm_test ///////////////////////// */

static int arithm_test( void* arg )
{
    double success_error_level = 0;

    int   param = (int)arg;
    int   func = param / 256;
    int   depth = (param % 256) % 8;
    int   channels = (param % 256) / 8;
    int   mattype;
    int   seed = -1;//atsGetSeed();

    int   btpix, max_img_bytes;

    int     merr_i = 0, i;
    double  max_err = 0.;

    uchar *src1data, *src2data, *dstdata, *dstdbdata, *maskdata;
    CvRandState rng_state;
    AtsBinArithmMaskFunc bin_func = 0;
    AtsUnArithmMaskFunc un_func = 0;
    AtsBinArithmFunc mul_func = 0;

    CvScalar alpha, beta, gamma;
    CvMat gammaarr;

    alpha = beta = gamma = cvScalarAll(0);

    read_arithm_params();

    if( !(ATS_RANGE( depth, dt_l, dt_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    cvInitMatHeader( &gammaarr, 1, 1, CV_64FC4, gamma.val );

    switch( func )
    {
    case 0:
        bin_func = cvAdd;
        alpha = beta = cvScalarAll(1);
        break;
    case 1:
        bin_func = cvSub;
        alpha = cvScalarAll(1);
        beta = cvScalarAll(-1);
        break;
    case 2:
        mul_func = cvMul;
        break;
    case 3:
        un_func = cvAddS;
        alpha = cvScalarAll(1);
        break;
    case 4:
        un_func = cvSubRS;
        alpha = cvScalarAll(-1);
        break;
    default:
        assert(0);
        return TRS_FAIL;
    }

    mattype = depth + channels*8;
    depth = depth == 0 ? IPL_DEPTH_8U : depth == 1 ? IPL_DEPTH_8S :
            depth == 2 ? IPL_DEPTH_16S : depth == 3 ? IPL_DEPTH_32S :
            depth == 4 ? IPL_DEPTH_32F : IPL_DEPTH_64F;

    channels = channels + 1;

    cvRandInit( &rng_state, 0, 1, seed );

    max_img_bytes = (max_img_size + 32) * (max_img_size + 2) * cvPixSize(mattype);

    src1data = (uchar*)cvAlloc( max_img_bytes );
    src2data = (uchar*)cvAlloc( max_img_bytes );
    dstdata = (uchar*)cvAlloc( max_img_bytes );
    dstdbdata = (uchar*)cvAlloc( max_img_bytes );
    maskdata = (uchar*)cvAlloc( max_img_bytes / cvPixSize(mattype));

    btpix = ((depth & 255)/8)*channels;
    
    if( depth == IPL_DEPTH_32F )
        success_error_level = FLT_EPSILON * img32f_range * (mul_func ? img32f_range : 2.f);
    else if( depth == IPL_DEPTH_64F )
        success_error_level = DBL_EPSILON * img32f_range * (mul_func ? img32f_range : 2.f);

    for( i = 0; i < base_iters; i++ )
    {
        int continuous = (cvRandNext( &rng_state ) % 3) == 0;
        int is_mask_op = mul_func ? 0 : ((cvRandNext( &rng_state ) % 3) == 0);
        int step1, step2, step, mstep;
        CvMat  src1, src2, dst1, dst2, mask, dst;
        double err;
        int w, h;
                
        w = cvRandNext( &rng_state ) % (max_img_size - min_img_size) + min_img_size;
        h = cvRandNext( &rng_state ) % (max_img_size - min_img_size) + min_img_size;

        step1 = step2 = step = w*btpix;
        mstep = w;

        if( !continuous )
        {
            step1 += (cvRandNext( &rng_state ) % 4)*(btpix/channels);
            step2 += (cvRandNext( &rng_state ) % 4)*(btpix/channels);
            step += (cvRandNext( &rng_state ) % 4)*(btpix/channels);
            mstep += (cvRandNext( &rng_state ) % 4);
        }

        switch( depth )
        {
        case IPL_DEPTH_8U:
            cvRandSetRange( &rng_state, 0, img8u_range );
            break;
        case IPL_DEPTH_8S:
            cvRandSetRange( &rng_state, -img8s_range, img8s_range );
            break;
        case IPL_DEPTH_16S:
            cvRandSetRange( &rng_state, -img16s_range, img16s_range );
            break;
        case IPL_DEPTH_32S:
            cvRandSetRange( &rng_state, -img32s_range, img32s_range );
            break;
        case IPL_DEPTH_32F:
        case IPL_DEPTH_64F:
            cvRandSetRange( &rng_state, -img32f_range, img32f_range );
            break;
        }

        cvInitMatHeader( &src1, h, w, mattype, src1data, step1 );
        cvInitMatHeader( &src2, h, w, mattype, src2data, step2 );
        cvInitMatHeader( &dst1, h, w, mattype, dstdata, step );
        cvInitMatHeader( &dst2, h, w, mattype, dstdbdata, step );

        cvInitMatHeader( &mask, h, w, CV_8UC1, maskdata, mstep );

        cvRand( &rng_state, &src1 );

        switch( cvRandNext(&rng_state) % 3 )
        {
        case 0:
            memcpy( &dst, &src1, sizeof(dst));
            break;
        case 1:
            if( un_func )
                memcpy( &dst, &src1, sizeof(dst));
            else
                memcpy( &dst, &src2, sizeof(dst));
            break;
        default:
            memcpy( &dst, &dst1, sizeof(dst));
            break;
        }

        if( un_func )
        {
            if( depth == IPL_DEPTH_8U )
                cvRandSetRange( &rng_state, -img8u_range, img8u_range );
            
            cvRand( &rng_state, &gammaarr );
        }
        else
        {
            cvRand( &rng_state, &src2 );
        }

        if( is_mask_op )
        {
            const int upper = 4;
            
            if( dst.data.ptr == dst1.data.ptr )
                cvRand( &rng_state, &dst );

            cvRandSetRange( &rng_state, 0, upper );
            cvRand( &rng_state, &mask );
            atsLinearFunc( &mask, cvScalarAll(1), 0, cvScalarAll(0),
                           cvScalarAll(2-upper), &mask );
        }

        if( !mul_func )
        {
            atsLinearFunc( &src1, alpha, un_func ? 0 : &src2, beta, gamma, &dst2 );
            if( is_mask_op )
            {
                cvXorS( &mask, cvScalarAll(1), &mask );
                cvCopy( &dst, &dst2, &mask );
                cvXorS( &mask, cvScalarAll(1), &mask );
            }

            if( un_func )
                un_func( &src1, gamma, &dst, is_mask_op ? &mask : 0 );
            else
                bin_func( &src1, &src2, &dst, is_mask_op ? &mask : 0 );
        }
        else
        {
            atsMul( &src1, &src2, &dst2 );
            mul_func( &src1, &src2, &dst );
        }

        /*if( i == 9 )
        {
            putchar('.');
        }*/

        //cvXor( &dst2, &dst, &dst2 );
        err = cvNorm( &dst2, &dst, CV_C );

        if( err > max_err )
        {
            max_err = err;
            merr_i = i;

            if( max_err > success_error_level )
                goto test_exit;
        }
    }

test_exit:
    cvFree( (void**)&src1data );
    cvFree( (void**)&src2data );
    cvFree( (void**)&dstdata );
    cvFree( (void**)&dstdbdata );
    cvFree( (void**)&maskdata );

    trsWrite( ATS_LST, "Max err is %g at iter = %d, seed = %08x",
                       max_err, merr_i, seed );

    return max_err <= success_error_level ?
        trsResult( TRS_OK, "No errors" ) :
        trsResult( TRS_FAIL, "Bad accuracy" );
}

void InitAArithmetic( void )
{
    int depth, channels, i;
    
    /* Register test functions */
    for( i = 0; i < ATS_DIM(funcs); i++ )
        for( depth = CV_8U; depth <= CV_64F; depth++ )
        {
            for( channels = 1;  channels <= 4; channels++ )
            {
                int mattype = depth + (channels - 1)*8;

                //if( i < 3 )
                //    continue;
            
                if( depth == CV_8S )
                    continue;

                switch( mattype )
                {
                case CV_8UC1:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_8UC1 );
                    break;
                case CV_8UC2:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_8UC2 );
                    break;
                case CV_8UC3:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_8UC3 );
                    break;
                case CV_8UC4:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_8UC4 );
                    break;

                case CV_16SC1:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_16SC1 );
                    break;
                case CV_16SC2:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_16SC2 );
                    break;
                case CV_16SC3:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_16SC3 );
                    break;
                case CV_16SC4:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_16SC4 );
                    break;

                case CV_32SC1:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32SC1 );
                    break;
                case CV_32SC2:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32SC2 );
                    break;
                case CV_32SC3:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32SC3 );
                    break;
                case CV_32SC4:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32SC4 );
                    break;

                case CV_32FC1:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32FC1 );
                    break;
                case CV_32FC2:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32FC2 );
                    break;
                case CV_32FC3:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32FC3 );
                    break;
                case CV_32FC4:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_32FC4 );
                    break;

                case CV_64FC1:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_64FC1 );
                    break;
                case CV_64FC2:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_64FC2 );
                    break;
                case CV_64FC3:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_64FC3 );
                    break;
                case CV_64FC4:
                    trsRegArg( funcs[i], test_desc, atsAlgoClass, arithm_test,
                               i*256 + CV_64FC4 );
                    break;
                default:
                    assert(0);
                    return;
                }
            }
        }

} /* InitAArithmetic */

/* End of file. */
