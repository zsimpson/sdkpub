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

/* ////////////////////////////////////////////////////////////////////
//
//  Filling CvMat/IplImage instances with random numbers
//
// */

#include "_cv.h"


///////////////////////////// Functions Declaration //////////////////////////////////////

#define IPCV_RAND_BITS( flavor, arrtype )                                               \
IPCVAPI( CvStatus, icvRandBits_##flavor##_C1R,( arrtype* arr, int step, CvSize size,    \
                                                uint64* state, const int* param ))

IPCV_RAND_BITS( 8u, uchar )
IPCV_RAND_BITS( 16s, short )
IPCV_RAND_BITS( 32s, int )


#define IPCV_RAND( flavor, arrtype )                                                    \
IPCVAPI( CvStatus, icvRand_##flavor##_C1R,( arrtype* arr, int step, CvSize size,        \
                                            uint64* state, const double* param ))

IPCV_RAND( 8u, uchar )
IPCV_RAND( 16s, short )
IPCV_RAND( 32s, int )
IPCV_RAND( 32f, float )
IPCV_RAND( 64f, double )


/*
   Multiply-with-carry generator is used here:
   temp = ( A*X(n) + carry )
   X(n+1) = temp mod (2^32)
   carry = temp / (2^32)
*/
#define  ICV_RNG_NEXT(x)    ((uint64)(unsigned)(x)*1554115554 + ((x) >> 32))
#define  ICV_CVT_FLT(x)     (((unsigned)(x) >> 9)|CV_1F)
#define  ICV_1D             CV_BIG_INT(0x3FF0000000000000)
#define  ICV_CVT_DBL(x)     (((uint64)(unsigned)(x) << 20)|((x) >> 44)|ICV_1D)

/***************************************************************************************\
*                           Pseudo-Random Number Generators (PRNGs)                     *
\***************************************************************************************/

CV_IMPL void
cvRandSetRange( CvRandState * state, double lower, double upper, int index  )
{
    CV_FUNCNAME( "cvRandSetRange" );

    __BEGIN__;

    if( !state )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( lower > upper )
        CV_ERROR( CV_StsOutOfRange,
        "lower boundary is greater than the upper one" );

    if( (unsigned)(index + 1) > 4 )
        CV_ERROR( CV_StsOutOfRange, "index is not in -1..3" );

    if( index < 0 )
    {
        state->param[0].val[0] = state->param[0].val[1] =
        state->param[0].val[2] = state->param[0].val[3] = lower;
        state->param[1].val[0] = state->param[1].val[1] = 
        state->param[1].val[2] = state->param[1].val[3] = upper;
    }
    else
    {
        state->param[0].val[index] = upper;
        state->param[1].val[index] = lower;
    }

    __END__;
}


CV_IMPL void
cvRandInit( CvRandState* state, double lower, double upper, int seed )
{
    CV_FUNCNAME( "cvRandInit" );

    __BEGIN__;

    if( !state )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    state->state = (uint64)(seed ? seed : UINT_MAX);
    CV_CALL( cvRandSetRange( state, lower, upper ));

    __END__;
}


CV_IMPL unsigned
cvRandNext( CvRandState * state )
{
    uint64 temp = 0;
    CV_FUNCNAME( "cvRandNext" );

    __BEGIN__;

    if( !state )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    temp = state->state;
    temp = ICV_RNG_NEXT(temp);
    state->state = temp;

    __END__;

    return (unsigned)temp;
}


#define ICV_IMPL_RAND_BITS( flavor, arrtype, cast_macro )               \
IPCVAPI_IMPL( CvStatus,                                                 \
icvRandBits_##flavor##_C1R,( arrtype* arr, int step, CvSize size,       \
                             uint64* state, const int* param ))         \
{                                                                       \
    uint64 temp = *state;                                               \
    int small_flag = (param[12]|param[13]|param[14]|param[15]) <= 255;  \
                                                                        \
    for( ; size.height--; (char*&)arr += step )                         \
    {                                                                   \
        int i, k = 3;                                                   \
        const int* p = param;                                           \
                                                                        \
        if( !small_flag )                                               \
        {                                                               \
            for( i = 0; i <= size.width - 4; i += 4 )                   \
            {                                                           \
                unsigned t0, t1;                                        \
                                                                        \
                temp = ICV_RNG_NEXT(temp);                              \
                t0 = ((unsigned)temp & p[i + 12]) + p[i];               \
                temp = ICV_RNG_NEXT(temp);                              \
                t1 = ((unsigned)temp & p[i + 13]) + p[i+1];             \
                arr[i] = cast_macro((int)t0);                           \
                arr[i+1] = cast_macro((int)t1);                         \
                                                                        \
                temp = ICV_RNG_NEXT(temp);                              \
                t0 = ((unsigned)temp & p[i + 14]) + p[i+2];             \
                temp = ICV_RNG_NEXT(temp);                              \
                t1 = ((unsigned)temp & p[i + 15]) + p[i+3];             \
                arr[i+2] = cast_macro((int)t0);                         \
                arr[i+3] = cast_macro((int)t1);                         \
                                                                        \
                if( !--k )                                              \
                {                                                       \
                    k = 3;                                              \
                    p -= 12;                                            \
                }                                                       \
            }                                                           \
        }                                                               \
        else                                                            \
        {                                                               \
            for( i = 0; i <= size.width - 4; i += 4 )                   \
            {                                                           \
                unsigned t0, t1, t;                                     \
                                                                        \
                temp = ICV_RNG_NEXT(temp);                              \
                t = (unsigned)temp;                                     \
                t0 = (t & p[i + 12]) + p[i];                            \
                t1 = ((t >> 8) & p[i + 13]) + p[i+1];                   \
                arr[i] = cast_macro((int)t0);                           \
                arr[i+1] = cast_macro((int)t1);                         \
                                                                        \
                t0 = ((t >> 16) & p[i + 14]) + p[i + 2];                \
                t1 = ((t >> 24) & p[i + 15]) + p[i + 3];                \
                arr[i+2] = cast_macro((int)t0);                         \
                arr[i+3] = cast_macro((int)t1);                         \
                                                                        \
                if( !--k )                                              \
                {                                                       \
                    k = 3;                                              \
                    p -= 12;                                            \
                }                                                       \
            }                                                           \
        }                                                               \
                                                                        \
        for( ; i < size.width; i++ )                                    \
        {                                                               \
            unsigned t0;                                                \
            temp = ICV_RNG_NEXT(temp);                                  \
                                                                        \
            t0 = ((unsigned)temp & p[i + 12]) + p[i];                   \
            arr[i] = cast_macro((int)t0);                               \
        }                                                               \
    }                                                                   \
                                                                        \
    *state = temp;                                                      \
    return CV_OK;                                                       \
}


#define ICV_IMPL_RAND( flavor, arrtype, worktype, cast_macro1, cast_macro2 )\
IPCVAPI_IMPL( CvStatus,                                                 \
icvRand_##flavor##_C1R,( arrtype* arr, int step, CvSize size,           \
                         uint64* state, const double* param ))          \
{                                                                       \
    uint64 temp = *state;                                               \
                                                                        \
    for( ; size.height--; (char*&)arr += step )                         \
    {                                                                   \
        int i, k = 3;                                                   \
        const double* p = param;                                        \
                                                                        \
        for( i = 0; i <= size.width - 4; i += 4 )                       \
        {                                                               \
            worktype f0, f1;                                            \
            unsigned t0, t1;                                            \
                                                                        \
            temp = ICV_RNG_NEXT(temp);                                  \
            t0 = ICV_CVT_FLT(temp);                                     \
            temp = ICV_RNG_NEXT(temp);                                  \
            t1 = ICV_CVT_FLT(temp);                                     \
            f0 = cast_macro1( (float&)t0 * p[i + 12] + p[i] );          \
            f1 = cast_macro1( (float&)t1 * p[i + 13] + p[i + 1] );      \
            arr[i] = cast_macro2(f0);                                   \
            arr[i+1] = cast_macro2(f1);                                 \
                                                                        \
            temp = ICV_RNG_NEXT(temp);                                  \
            t0 = ICV_CVT_FLT(temp);                                     \
            temp = ICV_RNG_NEXT(temp);                                  \
            t1 = ICV_CVT_FLT(temp);                                     \
            f0 = cast_macro1( (float&)t0 * p[i + 14] + p[i + 2] );      \
            f1 = cast_macro1( (float&)t1 * p[i + 15] + p[i + 3] );      \
            arr[i+2] = cast_macro2(f0);                                 \
            arr[i+3] = cast_macro2(f1);                                 \
                                                                        \
            if( !--k )                                                  \
            {                                                           \
                k = 3;                                                  \
                p -= 12;                                                \
            }                                                           \
        }                                                               \
                                                                        \
        for( ; i < size.width; i++ )                                    \
        {                                                               \
            worktype f0;                                                \
            unsigned t0;                                                \
                                                                        \
            temp = ICV_RNG_NEXT(temp);                                  \
            t0 = ICV_CVT_FLT(temp);                                     \
            f0 = cast_macro1( (float&)t0 * p[i + 12] + p[i] );          \
            arr[i] = cast_macro2(f0);                                   \
        }                                                               \
    }                                                                   \
                                                                        \
    *state = temp;                                                      \
    return CV_OK;                                                       \
}


IPCVAPI_IMPL( CvStatus,
icvRand_64f_C1R,( double* arr, int step, CvSize size,
                  uint64* state, const double* param ))
{
    uint64 temp = *state;

    for( ; size.height--; (char*&)arr += step )
    {
        int i, k = 3;
        const double* p = param;

        for( i = 0; i <= size.width - 4; i += 4 )
        {
            double f0, f1;
            uint64 t0, t1;

            temp = ICV_RNG_NEXT(temp);
            t0 = ICV_CVT_DBL(temp);
            temp = ICV_RNG_NEXT(temp);
            t1 = ICV_CVT_DBL(temp);
            f0 = (double&)t0 * p[i + 12] + p[i];
            f1 = (double&)t1 * p[i + 13] + p[i + 1];
            arr[i] = f0;
            arr[i+1] = f1;

            temp = ICV_RNG_NEXT(temp);
            t0 = ICV_CVT_DBL(temp);
            temp = ICV_RNG_NEXT(temp);
            t1 = ICV_CVT_DBL(temp);
            f0 = (double&)t0 * p[i + 14] + p[i + 2];
            f1 = (double&)t1 * p[i + 15] + p[i + 3];
            arr[i+2] = f0;
            arr[i+3] = f1;

            if( !--k )
            {
                k = 3;
                p -= 12;
            }
        }

        for( ; i < size.width; i++ )
        {
            double f0;
            uint64 t0;

            temp = ICV_RNG_NEXT(temp);
            t0 = ICV_CVT_DBL(temp);
            f0 = (double&)t0 * p[i + 12] + p[i];
            arr[i] = f0;
        }
    }

    *state = temp;
    return CV_OK;
}


ICV_IMPL_RAND_BITS( 8u, uchar, CV_CAST_8U )
ICV_IMPL_RAND_BITS( 16s, short, CV_CAST_16S )
ICV_IMPL_RAND_BITS( 32s, int, CV_CAST_32S )

ICV_IMPL_RAND( 8u, uchar, int, cvFloor, CV_CAST_8U )
ICV_IMPL_RAND( 16s, short, int, cvFloor, CV_CAST_16S )
ICV_IMPL_RAND( 32s, int, int, cvFloor, CV_CAST_32S )
ICV_IMPL_RAND( 32f, float, float, CV_CAST_32F, CV_NOP )
//ICV_IMPL_RAND( 64f, double, double, CV_CAST_64F, CV_NOP )


static void icvInitRandTable( CvFuncTable* rng_tab, CvFuncTable* fastrng_tab )
{
    rng_tab->fn_2d[CV_8U] = (void*)icvRand_8u_C1R;
    rng_tab->fn_2d[CV_16S] = (void*)icvRand_16s_C1R;
    rng_tab->fn_2d[CV_32S] = (void*)icvRand_32s_C1R;
    rng_tab->fn_2d[CV_32F] = (void*)icvRand_32f_C1R;
    rng_tab->fn_2d[CV_64F] = (void*)icvRand_64f_C1R;

    fastrng_tab->fn_2d[CV_8U] = (void*)icvRandBits_8u_C1R;
    fastrng_tab->fn_2d[CV_16S] = (void*)icvRandBits_16s_C1R;
    fastrng_tab->fn_2d[CV_32S] = (void*)icvRandBits_32s_C1R;
}


CV_IMPL void
cvbRand( CvRandState* state, float* dst, int len )
{
    CV_FUNCNAME( "cvbRand" );

    __BEGIN__;

    int i;
    uint64 temp;
    float factor, delta;

    if( !state || !dst )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( len < 0 )
        CV_ERROR( CV_StsBadSize, "Array length is negative" );

    temp = state->state;
    factor = (float)(state->param[1].val[0] - state->param[0].val[0]);
    delta = (float)(state->param[0].val[0] - factor);

    for( i = 0; i <= len - 4; i += 4 )
    {
        float x0, x1;
        unsigned t0, t1;

        temp = ICV_RNG_NEXT(temp);
        t0 = ICV_CVT_FLT(temp);
        temp = ICV_RNG_NEXT(temp);
        t1 = ICV_CVT_FLT(temp);
        x0 = (float&)t0 * factor + delta;
        x1 = (float&)t1 * factor + delta;
        dst[i] = x0;
        dst[i+1] = x1;

        temp = ICV_RNG_NEXT(temp);
        t0 = ICV_CVT_FLT(temp);
        temp = ICV_RNG_NEXT(temp);
        t1 = ICV_CVT_FLT(temp);
        x0 = (float&)t0 * factor + delta;
        x1 = (float&)t1 * factor + delta;
        dst[i+2] = x0;
        dst[i+3] = x1;
    }

    for( ; i < len; i++ )
    {
        float x0;
        unsigned t0;

        temp = ICV_RNG_NEXT(temp);
        t0 = ICV_CVT_FLT(temp);
        x0 = (float&)t0 * factor + delta;
        dst[i] = x0;
    }

    state->state = temp;

    __END__;
}


CV_IMPL void
cvRand( CvRandState* state, CvArr* arr )
{
    static CvFuncTable rng_tab, fastrng_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvRand" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;
    int type, depth, channels;
    double dparam[2][12];
    int iparam[2][12];
    int i, fast_int_mode = 0;
    int mat_step;
    CvSize size;
    CvFunc2D_1A2P func = 0;

    if( !inittab )
    {
        icvInitRandTable( &rng_tab, &fastrng_tab );
        inittab = 1;
    }

    if( !state )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( !CV_IS_ARR(mat))
    {
        int coi = 0;
        CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "COI is not supported" );
    }

    type = CV_ARR_TYPE( mat->type );
    size = icvGetMatSize( mat );
    mat_step = mat->step;

    if( CV_IS_ARR_CONT( mat->type ))
    {
        size.width *= size.height;

        if( type == CV_32FC1 )
        {
            CV_CALL( cvbRand( state, mat->data.fl, size.width ));
            EXIT;
        }

        mat_step = CV_STUB_STEP;
        size.height = 1;
    }

    depth = CV_ARR_DEPTH( type );
    channels = CV_ARR_CN( type );
    size.width *= channels;

    if( depth <= CV_32S )
    {
        for( i = 0, fast_int_mode = 1; i < channels; i++ )
        {
            int t0 = iparam[0][i] = cvCeil( state->param[0].val[i] );
            int t1 = iparam[1][i] = cvFloor( state->param[1].val[i] ) - t0;

            fast_int_mode &= (t1 & (t1 - 1)) == 0;
        }

        if( fast_int_mode )
        {
            for( i = 0; i < channels; i++ )
                iparam[1][i]--;
            
            for( ; i < 12; i++ )
            {
                int t0 = iparam[0][i - channels];
                int t1 = iparam[1][i - channels];

                iparam[0][i] = t0;
                iparam[1][i] = t1;
            }

            func = (CvFunc2D_1A2P)(fastrng_tab.fn_2d[depth]);

            if( !func )
                CV_ERROR_FROM_CODE( CV_StsUnsupportedFormat );

            IPPI_CALL( func( mat->data.ptr, mat_step, size, &(state->state), iparam ));
        }
    }

    for( i = 0; i < channels; i++ )
    {
        double t0 = state->param[0].val[i];
        double t1 = state->param[1].val[i];

        dparam[0][i] = t0 - (t1 - t0);
        dparam[1][i] = t1 - t0;
    }

    for( i = channels; i < 12; i++ )
    {
        double t0 = dparam[0][i - channels];
        double t1 = dparam[1][i - channels];

        dparam[0][i] = t0;
        dparam[1][i] = t1;
    }

    func = (CvFunc2D_1A2P)(rng_tab.fn_2d[depth]);

    if( !func )
        CV_ERROR_FROM_CODE( CV_StsUnsupportedFormat );

    IPPI_CALL( func( mat->data.ptr, mat_step, size, &(state->state), dparam ));

    __END__;
}


/* End of file. */





