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
//  CvMat arithmetic operations: +, - ...
//
// */

#include "_cv.h"

/****************************************************************************************\
*                      Arithmetic operations (+, -) without mask                         *
\****************************************************************************************/

#define ICV_DEF_BIN_ARI_OP_CASE( __op__, worktype, cast_macro, len )\
{                                                                   \
    int i;                                                          \
                                                                    \
    for( i = 0; i <= (len) - 4; i += 4 )                            \
    {                                                               \
        worktype t0 = __op__((src1)[i], (src2)[i]);                 \
        worktype t1 = __op__((src1)[i+1], (src2)[i+1]);             \
                                                                    \
        (dst)[i] = cast_macro( t0 );                                \
        (dst)[i+1] = cast_macro( t1 );                              \
                                                                    \
        t0 = __op__((src1)[i+2],(src2)[i+2]);                       \
        t1 = __op__((src1)[i+3],(src2)[i+3]);                       \
                                                                    \
        (dst)[i+2] = cast_macro( t0 );                              \
        (dst)[i+3] = cast_macro( t1 );                              \
    }                                                               \
                                                                    \
    for( ; i < (len); i++ )                                         \
    {                                                               \
        worktype t0 = __op__((src1)[i],(src2)[i]);                  \
        (dst)[i] = cast_macro( t0 );                                \
    }                                                               \
}


#define ICV_DEF_BIN_ARI_OP_2D( __op__, name, type, worktype, cast_macro )   \
IPCVAPI_IMPL( CvStatus, name, ( const type* src1, int step1,                \
                                const type* src2, int step2,                \
                                type* dst, int step, CvSize size ))         \
{                                                                           \
    if( size.width == 1 )                                                   \
    {                                                                       \
        for( ; size.height--; (char*&)src1 += step1,                        \
                              (char*&)src2 += step2,                        \
                              (char*&)dst += step )                         \
        {                                                                   \
            worktype t0 = __op__((src1)[0],(src2)[0]);                      \
            (dst)[0] = cast_macro( t0 );                                    \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        for( ; size.height--; (char*&)src1 += step1,                        \
                              (char*&)src2 += step2,                        \
                              (char*&)dst += step )                         \
        {                                                                   \
            ICV_DEF_BIN_ARI_OP_CASE( __op__, worktype,                      \
                                     cast_macro, size.width );              \
        }                                                                   \
    }                                                                       \
                                                                            \
    return CV_OK;                                                           \
}


#define ICV_DEF_UN_ARI_OP_CASE( __op__, worktype, cast_macro,               \
                                src, scalar, dst, len )                     \
{                                                                           \
    int i;                                                                  \
                                                                            \
    for( ; ((len) -= 12) >= 0; (dst) += 12, (src) += 12 )                   \
    {                                                                       \
        worktype t0 = __op__((scalar)[0], (src)[0]);                        \
        worktype t1 = __op__((scalar)[1], (src)[1]);                        \
                                                                            \
        (dst)[0] = cast_macro( t0 );                                        \
        (dst)[1] = cast_macro( t1 );                                        \
                                                                            \
        t0 = __op__((scalar)[2], (src)[2]);                                 \
        t1 = __op__((scalar)[3], (src)[3]);                                 \
                                                                            \
        (dst)[2] = cast_macro( t0 );                                        \
        (dst)[3] = cast_macro( t1 );                                        \
                                                                            \
        t0 = __op__((scalar)[4], (src)[4]);                                 \
        t1 = __op__((scalar)[5], (src)[5]);                                 \
                                                                            \
        (dst)[4] = cast_macro( t0 );                                        \
        (dst)[5] = cast_macro( t1 );                                        \
                                                                            \
        t0 = __op__((scalar)[6], (src)[6]);                                 \
        t1 = __op__((scalar)[7], (src)[7]);                                 \
                                                                            \
        (dst)[6] = cast_macro( t0 );                                        \
        (dst)[7] = cast_macro( t1 );                                        \
                                                                            \
        t0 = __op__((scalar)[8], (src)[8]);                                 \
        t1 = __op__((scalar)[9], (src)[9]);                                 \
                                                                            \
        (dst)[8] = cast_macro( t0 );                                        \
        (dst)[9] = cast_macro( t1 );                                        \
                                                                            \
        t0 = __op__((scalar)[10], (src)[10]);                               \
        t1 = __op__((scalar)[11], (src)[11]);                               \
                                                                            \
        (dst)[10] = cast_macro( t0 );                                       \
        (dst)[11] = cast_macro( t1 );                                       \
    }                                                                       \
                                                                            \
    for( (len) += 12, i = 0; i < (len); i++ )                               \
    {                                                                       \
        worktype t0 = __op__((scalar)[i],(src)[i]);                         \
        (dst)[i] = cast_macro( t0 );                                        \
    }                                                                       \
}


#define ICV_DEF_UN_ARI_OP_2D( __op__, name, type, worktype, cast_macro )    \
IPCVAPI_IMPL( CvStatus,                                                     \
name,( const type* src, int step1, type* dst, int step,                     \
      CvSize size, const worktype* scalar ))                                \
{                                                                           \
    if( size.width == 1 )                                                   \
    {                                                                       \
        for( ; size.height--; (char*&)src += step1,                         \
                              (char*&)dst += step )                         \
        {                                                                   \
            worktype t0 = __op__(*(scalar),*(src));                         \
            *(dst) = cast_macro( t0 );                                      \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        for( ; size.height--; (char*&)src += step1,                         \
                              (char*&)dst += step )                         \
        {                                                                   \
            const type *tsrc = src;                                         \
            type *tdst = dst;                                               \
            int width = size.width;                                         \
                                                                            \
            ICV_DEF_UN_ARI_OP_CASE( __op__, worktype, cast_macro,           \
                                    tsrc, scalar, tdst, width );            \
        }                                                                   \
    }                                                                       \
                                                                            \
    return CV_OK;                                                           \
}


#define ICV_DEF_BIN_ARI_ALL( __op__, name, cast_8u )                                \
ICV_DEF_BIN_ARI_OP_2D( __op__, icv##name##_8u_C1R, uchar, int, cast_8u )            \
ICV_DEF_BIN_ARI_OP_2D( __op__, icv##name##_16s_C1R, short, int, CV_CAST_16S )       \
ICV_DEF_BIN_ARI_OP_2D( __op__, icv##name##_32s_C1R, int, int, CV_CAST_32S )         \
ICV_DEF_BIN_ARI_OP_2D( __op__, icv##name##_32f_C1R, float, float, CV_CAST_32F )     \
ICV_DEF_BIN_ARI_OP_2D( __op__, icv##name##_64f_C1R, double, double, CV_CAST_64F )

#define ICV_DEF_UN_ARI_ALL( __op__, name )                                          \
ICV_DEF_UN_ARI_OP_2D( __op__, icv##name##_8u_C1R, uchar, int, CV_CAST_8U )          \
ICV_DEF_UN_ARI_OP_2D( __op__, icv##name##_16s_C1R, short, int, CV_CAST_16S )        \
ICV_DEF_UN_ARI_OP_2D( __op__, icv##name##_32s_C1R, int, int, CV_CAST_32S )          \
ICV_DEF_UN_ARI_OP_2D( __op__, icv##name##_32f_C1R, float, float, CV_CAST_32F )      \
ICV_DEF_UN_ARI_OP_2D( __op__, icv##name##_64f_C1R, double, double, CV_CAST_64F )

ICV_DEF_BIN_ARI_ALL( CV_ADD, Add, CV_FAST_CAST_8U )
ICV_DEF_BIN_ARI_ALL( CV_SUB, Sub, CV_FAST_CAST_8U )
ICV_DEF_BIN_ARI_ALL( CV_MUL, Mul, CV_CAST_8U )

ICV_DEF_UN_ARI_ALL( CV_ADD, AddC )
ICV_DEF_UN_ARI_ALL( CV_SUB, SubRC )

#define ICV_DEF_INIT_ARITHM_FUNC_TAB( FUNCNAME, FLAG )          \
static  void  icvInit##FUNCNAME##FLAG##Table( CvFuncTable* tab )\
{                                                               \
    tab->fn_2d[CV_8U] = (void*)icv##FUNCNAME##_8u_##FLAG;       \
    tab->fn_2d[CV_16S] = (void*)icv##FUNCNAME##_16s_##FLAG;     \
    tab->fn_2d[CV_32S] = (void*)icv##FUNCNAME##_32s_##FLAG;     \
    tab->fn_2d[CV_32F] = (void*)icv##FUNCNAME##_32f_##FLAG;     \
    tab->fn_2d[CV_64F] = (void*)icv##FUNCNAME##_64f_##FLAG;     \
}

ICV_DEF_INIT_ARITHM_FUNC_TAB( Sub, C1R );
ICV_DEF_INIT_ARITHM_FUNC_TAB( SubRC, C1R );
ICV_DEF_INIT_ARITHM_FUNC_TAB( Add, C1R );
ICV_DEF_INIT_ARITHM_FUNC_TAB( AddC, C1R );
ICV_DEF_INIT_ARITHM_FUNC_TAB( Mul, C1R );

/****************************************************************************************\
*                      Arithmetic operations (+, -, *) with mask                         *
\****************************************************************************************/

#define IPCV_ARITHM_MASK( name, flavor, arrtype, scalartype )                   \
IPCVAPI( CvStatus, icv##name##_##flavor##_CnMR,                                 \
( const arrtype* src1, int srcstep1, const uchar* mask, int maskstep,           \
  arrtype* dst, int dststep, CvSize size, int cn ))                             \
IPCVAPI( CvStatus, icv##name##C_##flavor##_CnMR,                                \
( arrtype* dst, int dststep, const uchar* mask, int maskstep,                   \
  CvSize size, const scalartype* scalar, int cn ))

IPCV_ARITHM_MASK( Add, 8u, uchar, int )
IPCV_ARITHM_MASK( Add, 16s, short, int )
IPCV_ARITHM_MASK( Add, 32s, int, int )
IPCV_ARITHM_MASK( Add, 32f, float, float )
IPCV_ARITHM_MASK( Add, 64f, double, double )

IPCV_ARITHM_MASK( Sub, 8u, uchar, int )
IPCV_ARITHM_MASK( Sub, 16s, short, int )
IPCV_ARITHM_MASK( Sub, 32s, int, int )
IPCV_ARITHM_MASK( Sub, 32f, float, float )
IPCV_ARITHM_MASK( Sub, 64f, double, double )

IPCV_ARITHM_MASK( SubR, 8u, uchar, int )
IPCV_ARITHM_MASK( SubR, 16s, short, int )
IPCV_ARITHM_MASK( SubR, 32s, int, int )
IPCV_ARITHM_MASK( SubR, 32f, float, float )
IPCV_ARITHM_MASK( SubR, 64f, double, double )

#undef IPCV_ARITHM_MASK

//////////////////////////////////////////////////////////////////////////////////////////


#define ICV_INT_MASK(m)  (((m) == 0) - 1)
#define ICV_FLT_MASK(m)  maskTab[(m) != 0]

/////////////////////////// Binary operations ////////////////////////////////

#define ICV_DEF_BIN_ARI_OP_MASK( __op__, _mask_op_, _process_mask_,             \
                             cast_macro, worktype,                              \
                             src, dst, mask, len, cn )                          \
{                                                                               \
    int i;                                                                      \
    for( i = 0; i <= (len) - 4; i += 4, src += 4*(cn), dst += 4*(cn) )          \
    {                                                                           \
        int k = cn - 1;                                                         \
        int m = 0;                                                              \
                                                                                \
        do                                                                      \
        {                                                                       \
            worktype t0 = _process_mask_((mask)[i]);                            \
            worktype t1 = _process_mask_((mask)[i+1]);                          \
                                                                                \
            t0 = _mask_op_( t0, (src)[k]);                                      \
            t1 = _mask_op_( t1, (src)[k+(cn)]);                                 \
                                                                                \
            t0 = __op__( (dst)[k], t0 );                                        \
            t1 = __op__( (dst)[k+(cn)], t1 );                                   \
                                                                                \
            (dst)[k] = cast_macro( t0 );                                        \
            (dst)[k+(cn)] = cast_macro( t1 );                                   \
                                                                                \
            t0 = _process_mask_((mask)[i+2]);                                   \
            t1 = _process_mask_((mask)[i+3]);                                   \
                                                                                \
            t0 = _mask_op_( t0, (src)[k+2*(cn)]);                               \
            t1 = _mask_op_( t1, (src)[k+3*(cn)]);                               \
                                                                                \
            t0 = __op__( (dst)[k+2*(cn)], t0 );                                 \
            t1 = __op__( (dst)[k+3*(cn)], t1 );                                 \
                                                                                \
            (dst)[k+2*(cn)] = cast_macro( t0 );                                 \
            (dst)[k+3*(cn)] = cast_macro( t1 );                                 \
        }                                                                       \
        while( k-- && (m || (m = (mask[i]|mask[i+1]|mask[i+2]|mask[i+3])) != 0));\
    }                                                                           \
                                                                                \
    for( ; i < (len); i++, src += cn, dst += cn )                               \
    {                                                                           \
        int k = cn - 1;                                                         \
        do                                                                      \
        {                                                                       \
            worktype t = _process_mask_((mask)[i]);                             \
            t = _mask_op_( t, (src)[k] );                                       \
            t = __op__( (dst)[k], t );                                          \
            (dst)[k] = cast_macro( t );                                         \
        }                                                                       \
        while( k-- && mask[i] != 0 );                                           \
    }                                                                           \
}


// dst = src - dst
#define ICV_DEF_BIN_ARI_OP_REV_MASK( __op__, _mask_op_, _process_mask_,         \
                                 cast_macro,worktype,                           \
                                 src, dst, mask, len, cn )                      \
{                                                                               \
    int i;                                                                      \
    for( i = 0; i <= (len) - 4; i += 4, src += 4*cn, dst += 4*cn )              \
    {                                                                           \
        int k = cn - 1;                                                         \
        int m = 0;                                                              \
                                                                                \
        do                                                                      \
        {                                                                       \
            worktype t0 = _process_mask_( (mask)[i] );                          \
            worktype t1 = _process_mask_( (mask)[i+1] );                        \
            worktype t2 = (dst)[k];                                             \
            worktype t3 = (dst)[k+(cn)];                                        \
                                                                                \
            t2 += _mask_op_( t0, (src)[k] - t2 - t2 );                          \
            t3 += _mask_op_( t1, (src)[k+(cn)] - t3 - t3 );                     \
                                                                                \
            (dst)[k] = cast_macro(t2);                                          \
            (dst)[k+(cn)] = cast_macro(t3);                                     \
                                                                                \
            t0 = _process_mask_( (mask)[i+2] );                                 \
            t1 = _process_mask_( (mask)[i+3] );                                 \
            t2 = (dst)[k+(cn)*2];                                               \
            t3 = (dst)[k+(cn)*3];                                               \
                                                                                \
            t2 += _mask_op_( t0, (src)[k+(cn)*2] - t2 - t2 );                   \
            t3 += _mask_op_( t1, (src)[k+(cn)*3] - t3 - t3 );                   \
                                                                                \
            (dst)[k+(cn)*2] = cast_macro(t2);                                   \
            (dst)[k+(cn)*3] = cast_macro(t3);                                   \
        }                                                                       \
        while( k-- && (m || (m = (mask[i]|mask[i+1]|mask[i+2]|mask[i+3])) != 0));\
    }                                                                           \
                                                                                \
    for( ; i < (len); i++, src += cn, dst += cn )                               \
    {                                                                           \
        int k = cn - 1;                                                         \
        do                                                                      \
        {                                                                       \
            worktype t0 = _process_mask_( (mask)[i] );                          \
            worktype t1 = (dst)[k];                                             \
                                                                                \
            t1 += _mask_op_( t0, (src)[k] - t1 - t1 );                          \
            (dst)[k] = cast_macro(t1);                                          \
        }                                                                       \
        while( k-- && mask[i] != 0 );                                           \
    }                                                                           \
}


#define ICV_DEF_BIN_ARI_OP_MASK_2D( __op__, name, _mask_op_, _process_mask_,\
                              entry, arrtype, worktype, cast_macro, flag )  \
                                                                            \
IPCVAPI_IMPL( CvStatus,                                                     \
name,( const arrtype* src, int srcstep, const uchar* mask, int maskstep,    \
       arrtype* dst, int dststep, CvSize size, int cn ))                    \
{                                                                           \
    entry;                                                                  \
                                                                            \
    for( ; size.height--; (char*&)src += srcstep,                           \
                          (char*&)dst += dststep,                           \
                          mask += maskstep )                                \
    {                                                                       \
        const arrtype* tsrc = src;                                          \
        arrtype* tdst = dst;                                                \
                                                                            \
        ICV_DEF_BIN_ARI_OP_##flag( __op__, _mask_op_, _process_mask_,       \
                 cast_macro, worktype, tsrc, tdst, mask, size.width, cn );  \
    }                                                                       \
                                                                            \
    return CV_OK;                                                           \
}


/////////////////////////// Unary operations ////////////////////////////////


#define ICV_DEF_UN_ARI_OP_MASK( __op__, _mask_op_, _process_mask_,              \
                                cast_macro, worktype,                           \
                                dst, mask, len, cn )                            \
{                                                                               \
    int i;                                                                      \
    for( i = 0; i <= (len) - 4; i += 4, dst += 4*(cn) )                         \
    {                                                                           \
        int k = cn - 1;                                                         \
        int m = 0;                                                              \
                                                                                \
        do                                                                      \
        {                                                                       \
            worktype value = scalar[k];                                         \
            worktype t0 = _process_mask_((mask)[i]);                            \
            worktype t1 = _process_mask_((mask)[i+1]);                          \
                                                                                \
            t0 = _mask_op_( t0, value );                                        \
            t1 = _mask_op_( t1, value );                                        \
                                                                                \
            t0 = __op__( (dst)[k], t0 );                                        \
            t1 = __op__( (dst)[k+(cn)], t1 );                                   \
                                                                                \
            (dst)[k] = cast_macro( t0 );                                        \
            (dst)[k+(cn)] = cast_macro( t1 );                                   \
                                                                                \
            t0 = _process_mask_((mask)[i+2]);                                   \
            t1 = _process_mask_((mask)[i+3]);                                   \
                                                                                \
            t0 = _mask_op_( t0, value );                                        \
            t1 = _mask_op_( t1, value );                                        \
                                                                                \
            t0 = __op__( (dst)[k+2*(cn)], t0 );                                 \
            t1 = __op__( (dst)[k+3*(cn)], t1 );                                 \
                                                                                \
            (dst)[k+2*(cn)] = cast_macro( t0 );                                 \
            (dst)[k+3*(cn)] = cast_macro( t1 );                                 \
        }                                                                       \
        while( k-- && (m || (m = (mask[i]|mask[i+1]|mask[i+2]|mask[i+3])) != 0));\
    }                                                                           \
                                                                                \
    for( ; i < (len); i++, dst += cn )                                          \
    {                                                                           \
        int k = cn - 1;                                                         \
        do                                                                      \
        {                                                                       \
            worktype t = _process_mask_((mask)[i]);                             \
            t = _mask_op_( t, scalar[k] );                                      \
            t = __op__( (dst)[k], t );                                          \
            (dst)[k] = cast_macro( t );                                         \
        }                                                                       \
        while( k-- && mask[i] != 0 );                                           \
    }                                                                           \
}


// dst = src - dst
#define ICV_DEF_UN_ARI_OP_REV_MASK( __op__, _mask_op_, _process_mask_,          \
                                    cast_macro,worktype,                        \
                                    dst, mask, len, cn )                        \
{                                                                               \
    int i;                                                                      \
    for( i = 0; i <= (len) - 4; i += 4, dst += 4*cn )                           \
    {                                                                           \
        int k = cn - 1;                                                         \
        int m = 0;                                                              \
                                                                                \
        do                                                                      \
        {                                                                       \
            worktype value = scalar[k];                                         \
            worktype t0 = _process_mask_( (mask)[i] );                          \
            worktype t1 = _process_mask_( (mask)[i+1] );                        \
            worktype t2 = (dst)[k];                                             \
            worktype t3 = (dst)[k+(cn)];                                        \
                                                                                \
            t2 += _mask_op_( t0, value - t2 - t2 );                             \
            t3 += _mask_op_( t1, value - t3 - t3 );                             \
                                                                                \
            (dst)[k] = cast_macro(t2);                                          \
            (dst)[k+(cn)] = cast_macro(t3);                                     \
                                                                                \
            t0 = _process_mask_( (mask)[i+2] );                                 \
            t1 = _process_mask_( (mask)[i+3] );                                 \
            t2 = (dst)[k+(cn)*2];                                               \
            t3 = (dst)[k+(cn)*3];                                               \
                                                                                \
            t2 += _mask_op_( t0, value - t2 - t2 );                             \
            t3 += _mask_op_( t1, value - t3 - t3 );                             \
                                                                                \
            (dst)[k+(cn)*2] = cast_macro(t2);                                   \
            (dst)[k+(cn)*3] = cast_macro(t3);                                   \
        }                                                                       \
        while( k-- && (m || (m = (mask[i]|mask[i+1]|mask[i+2]|mask[i+3])) != 0));\
    }                                                                           \
                                                                                \
    for( ; i < (len); i++, dst += cn )                                          \
    {                                                                           \
        int k = cn - 1;                                                         \
        do                                                                      \
        {                                                                       \
            worktype t0 = _process_mask_( (mask)[i] );                          \
            worktype t1 = (dst)[k];                                             \
                                                                                \
            t1 += _mask_op_( t0, scalar[k] - t1 - t1 );                         \
            (dst)[k] = cast_macro(t1);                                          \
        }                                                                       \
        while( k-- && mask[i] != 0 );                                           \
    }                                                                           \
}

#define ICV_DEF_UN_ARI_OP_MASK_2D( __op__, name, _mask_op_, _process_mask_, \
                                entry, arrtype, worktype, cast_macro, flag )\
                                                                            \
IPCVAPI_IMPL( CvStatus,                                                     \
name, ( arrtype* dst, int dststep, const uchar* mask, int maskstep,         \
        CvSize size, const worktype* scalar, int cn ))                      \
{                                                                           \
    entry;                                                                  \
                                                                            \
    for( ; size.height--; (char*&)dst += dststep,                           \
                          mask += maskstep )                                \
    {                                                                       \
        arrtype* tdst = dst;                                                \
                                                                            \
        ICV_DEF_UN_ARI_OP_##flag( __op__, _mask_op_, _process_mask_,        \
                       cast_macro, worktype, tdst, mask, size.width, cn );  \
    }                                                                       \
                                                                            \
    return CV_OK;                                                           \
}


#define  ICV_STUB_ENTRY      dst = dst
#define  ICV_BIN_ENTRY_FLT   CV_DEFINE_MASK


#define ICV_DEF_ALL_BIN_MASK( __op__, name, flag )                                  \
ICV_DEF_BIN_ARI_OP_MASK_2D( __op__, icv##name##_8u_CnMR, CV_AND, ICV_INT_MASK,      \
                            ICV_STUB_ENTRY, uchar, int, CV_FAST_CAST_8U, flag )     \
ICV_DEF_BIN_ARI_OP_MASK_2D( __op__, icv##name##_16s_CnMR, CV_AND, ICV_INT_MASK,     \
                            ICV_STUB_ENTRY, short, int, CV_CAST_16S, flag )         \
ICV_DEF_BIN_ARI_OP_MASK_2D( __op__, icv##name##_32s_CnMR, CV_AND, ICV_INT_MASK,     \
                            ICV_STUB_ENTRY, int, int, CV_CAST_32S, flag )           \
ICV_DEF_BIN_ARI_OP_MASK_2D( __op__, icv##name##_32f_CnMR, CV_MUL, ICV_FLT_MASK,     \
                            ICV_BIN_ENTRY_FLT, float, float, CV_CAST_32F, flag )    \
ICV_DEF_BIN_ARI_OP_MASK_2D( __op__, icv##name##_64f_CnMR, CV_MUL, ICV_FLT_MASK,     \
                            ICV_BIN_ENTRY_FLT, double, double, CV_CAST_32F, flag )

#define ICV_DEF_ALL_UN_MASK( __op__, name, flag )                                   \
ICV_DEF_UN_ARI_OP_MASK_2D( __op__, icv##name##_8u_CnMR, CV_AND, ICV_INT_MASK,       \
                            ICV_STUB_ENTRY, uchar, int, CV_CAST_8U, flag )          \
ICV_DEF_UN_ARI_OP_MASK_2D( __op__, icv##name##_16s_CnMR, CV_AND, ICV_INT_MASK,      \
                            ICV_STUB_ENTRY, short, int, CV_CAST_16S, flag )         \
ICV_DEF_UN_ARI_OP_MASK_2D( __op__, icv##name##_32s_CnMR, CV_AND, ICV_INT_MASK,      \
                            ICV_STUB_ENTRY, int, int, CV_CAST_32S, flag )           \
ICV_DEF_UN_ARI_OP_MASK_2D( __op__, icv##name##_32f_CnMR, CV_MUL, ICV_FLT_MASK,      \
                            CV_DEFINE_MASK, float, float, CV_CAST_32F, flag )       \
ICV_DEF_UN_ARI_OP_MASK_2D( __op__, icv##name##_64f_CnMR, CV_MUL, ICV_FLT_MASK,      \
                            CV_DEFINE_MASK, double, double, CV_CAST_32F, flag )


ICV_DEF_ALL_BIN_MASK( CV_ADD, Add, MASK )
ICV_DEF_ALL_BIN_MASK( CV_SUB, Sub, MASK )
ICV_DEF_ALL_BIN_MASK( CV_SUB, SubR, REV_MASK )

ICV_DEF_ALL_UN_MASK( CV_ADD, AddC, MASK )
ICV_DEF_ALL_UN_MASK( CV_SUB, SubRC, REV_MASK )


#define ICV_DEF_INIT_ARITHM_MASK_FUNC_TAB ICV_DEF_INIT_ARITHM_FUNC_TAB

ICV_DEF_INIT_ARITHM_MASK_FUNC_TAB( Add, CnMR )
ICV_DEF_INIT_ARITHM_MASK_FUNC_TAB( AddC, CnMR )
ICV_DEF_INIT_ARITHM_MASK_FUNC_TAB( Sub, CnMR )
ICV_DEF_INIT_ARITHM_MASK_FUNC_TAB( SubR, CnMR )
ICV_DEF_INIT_ARITHM_MASK_FUNC_TAB( SubRC, CnMR )

/****************************************************************************************\
*                       External Functions for Arithmetic Operations                     *
\****************************************************************************************/


/*************************************** S U B ******************************************/

CV_IMPL void
cvSub( const void* srcarr1, const void* srcarr2,
       void* dstarr, const void* maskarr )
{
    static CvFuncTable submask_tab[2];
    static CvFuncTable sub_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvSub" );

    __BEGIN__;

    int type, coi = 0;
    int src1_step, src2_step, dst_step;
    CvMat srcstub1, *src1 = (CvMat*)srcarr1;
    CvMat srcstub2, *src2 = (CvMat*)srcarr2;
    CvMat dststub,  *dst = (CvMat*)dstarr;
    CvSize size; 

    if( !inittab )
    {
        icvInitSubC1RTable( &sub_tab );
        icvInitSubCnMRTable( &submask_tab[0] );
        icvInitSubRCnMRTable( &submask_tab[1] );
        inittab = 1;
    }

    if( !CV_IS_ARR(src1) )
    {
        CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(src2) )
    {
        CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(dst) )
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src1, src2 ) || !CV_ARE_TYPES_EQ( src1, dst ))
            CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) || !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    type = CV_ARR_TYPE(src1->type);
    size = icvGetMatSize( src1 );

    if( !maskarr )
    {
        int depth = CV_ARR_DEPTH(type);
        size.width *= CV_ARR_CN( type );

        if( CV_IS_ARR_CONT( src1->type & src2->type & dst->type ))
        {
            size.width *= size.height;
            if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
            {
                if( depth == CV_32F )
                {
                    const float* src1data = (const float*)(src1->data.ptr);
                    const float* src2data = (const float*)(src2->data.ptr);
                    float* dstdata = (float*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] = (float)
                            (src1data[size.width-1] - src2data[size.width-1]);
                    }
                    while( --size.width );

                    EXIT;
                }

                if( depth == CV_64F )
                {
                    const double* src1data = (const double*)(src1->data.ptr);
                    const double* src2data = (const double*)(src2->data.ptr);
                    double* dstdata = (double*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] =
                            src1data[size.width-1] - src2data[size.width-1];
                    }
                    while( --size.width );

                    EXIT;
                }
            }

            src1_step = src2_step = dst_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            src1_step = src1->step;
            src2_step = src2->step;
            dst_step = dst->step;
        }

        {
            CvFunc2D_3A func = (CvFunc2D_3A)(sub_tab.fn_2d[depth]);

            if( !func )
                CV_ERROR( CV_StsUnsupportedFormat, "" );

            IPPI_CALL( func( src1->data.ptr, src1_step, src2->data.ptr, src2_step,
                             dst->data.ptr, dst_step, size ));
        }
    }
    else
    {
        CvMat maskstub, *mask = (CvMat*)maskarr;
        CvArithmBinMaskFunc2D func;
        int inv = 0;
        int mask_step;

        if( !CV_IS_ARR(mask) )
            CV_CALL( mask = cvGetMat( mask, &maskstub ));

        if( !CV_IS_MASK_ARR(mask))
            CV_ERROR( CV_StsBadMask, "" );

        if( !CV_ARE_SIZES_EQ( mask, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );

        if( dst->data.ptr == src1->data.ptr )
            ;
        else if( dst->data.ptr == src2->data.ptr )
        {
            inv = 1;
            src2 = src1;
        }
        else
        {
            CV_CALL( cvCopy( src1, dst, mask ));
        }

        if( CV_IS_ARR_CONT( src2->type & dst->type & mask->type ))
        {
            size.width *= size.height;
            src2_step = dst_step = mask_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            src2_step = src2->step;
            dst_step = dst->step;
            mask_step = mask->step;
        }
        
        func = (CvArithmBinMaskFunc2D)
                (submask_tab[inv].fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src2->data.ptr, src2_step,
                         mask->data.ptr, mask_step,
                         dst->data.ptr, dst_step, size, CV_ARR_CN(type) ));
    }

    __END__;
}


CV_IMPL void
cvSubRS( const void* srcarr, CvScalar scalar, void* dstarr, const void* maskarr )
{
    static CvFuncTable subrmask_tab;
    static CvFuncTable subr_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvSubRS" );

    __BEGIN__;

    int sctype, type, coi = 0;
    int src_step, dst_step;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    double buf[12];
    CvSize size; 

    if( !inittab )
    {
        icvInitSubRCC1RTable( &subr_tab );
        icvInitSubRCCnMRTable( &subrmask_tab );
        inittab = 1;
    }

    if( !CV_IS_ARR(src) )
    {
        CV_CALL( src = cvGetMat( src, &srcstub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(dst) )
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    sctype = type = CV_ARR_TYPE(src->type);
    if( CV_ARR_DEPTH(sctype) < CV_32S )
        sctype = (type & CV_ARR_CN_MASK) | CV_32SC1;

    size = icvGetMatSize( src );

    if( !maskarr )
    {
        if( CV_IS_ARR_CONT( src->type & dst->type ))
        {
            size.width *= size.height;
            if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
            {
                if( type == CV_32FC1 )
                {
                    const float* srcdata = (const float*)(src->data.ptr);
                    float* dstdata = (float*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] = (float)
                            (scalar.val[0] - srcdata[size.width-1]);
                    }
                    while( --size.width );

                    EXIT;
                }

                if( type == CV_64FC1 )
                {
                    const double* srcdata = (const double*)(src->data.ptr);
                    double* dstdata = (double*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] =
                            scalar.val[0] - srcdata[size.width-1];
                    }
                    while( --size.width );

                    EXIT;
                }
            }

            src_step = dst_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            src_step = src->step;
            dst_step = dst->step;
        }

        {
            size.width *= CV_ARR_CN( type );
            CvFunc2D_2A1P func = (CvFunc2D_2A1P)(subr_tab.fn_2d[CV_ARR_DEPTH(type)]);

            if( !func )
                CV_ERROR( CV_StsUnsupportedFormat, "" );

            CV_CALL( cvScalarToRawData( &scalar, sctype, buf, 1 ));

            IPPI_CALL( func( src->data.ptr, src_step,
                             dst->data.ptr, dst_step, size, buf ));
        }
    }
    else
    {
        CvMat maskstub, *mask = (CvMat*)maskarr;
        CvArithmUniMaskFunc2D func;
        int mask_step;

        if( !CV_IS_ARR(mask) )
            CV_CALL( mask = cvGetMat( mask, &maskstub ));

        if( !CV_IS_MASK_ARR(mask))
            CV_ERROR( CV_StsBadMask, "" );

        if( !CV_ARE_SIZES_EQ( mask, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );

        if( src->data.ptr != dst->data.ptr )
        {
            CV_CALL( cvCopy( src, dst, mask ));
        }

        if( CV_IS_ARR_CONT( dst->type & mask->type ))
        {
            size.width *= size.height;
            dst_step = mask_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            dst_step = dst->step;
            mask_step = mask->step;
        }
        
        func = (CvArithmUniMaskFunc2D)(subrmask_tab.fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        CV_CALL( cvScalarToRawData( &scalar, sctype, buf, 0 ));

        IPPI_CALL( func( dst->data.ptr, dst_step, mask->data.ptr,
                         mask_step, size, buf, CV_ARR_CN(type) ));
    }

    __END__;
}


/******************************* A D D ********************************/

CV_IMPL void
cvAdd( const void* srcarr1, const void* srcarr2,
       void* dstarr, const void* maskarr )
{
    static CvFuncTable addmask_tab;
    static CvFuncTable add_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvAdd" );

    __BEGIN__;

    int type, coi = 0;
    int src1_step, src2_step, dst_step;
    CvMat srcstub1, *src1 = (CvMat*)srcarr1;
    CvMat srcstub2, *src2 = (CvMat*)srcarr2;
    CvMat dststub,  *dst = (CvMat*)dstarr;
    CvSize size; 

    if( !inittab )
    {
        icvInitAddC1RTable( &add_tab );
        icvInitAddCnMRTable( &addmask_tab );
        inittab = 1;
    }

    if( !CV_IS_ARR(src1) )
    {
        CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(src2) )
    {
        CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(dst) )
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src1, src2 ) || !CV_ARE_TYPES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) || !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    type = CV_ARR_TYPE(src1->type);
    size = icvGetMatSize( src1 );

    if( !maskarr )
    {
        int depth = CV_ARR_DEPTH(type);
        size.width *= CV_ARR_CN( type );

        if( CV_IS_ARR_CONT( src1->type & src2->type & dst->type ))
        {
            size.width *= size.height;
            if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
            {
                if( depth == CV_32F )
                {
                    const float* src1data = (const float*)(src1->data.ptr);
                    const float* src2data = (const float*)(src2->data.ptr);
                    float* dstdata = (float*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] = (float)
                            (src1data[size.width-1] + src2data[size.width-1]);
                    }
                    while( --size.width );

                    EXIT;
                }

                if( depth == CV_64F )
                {
                    const double* src1data = (const double*)(src1->data.ptr);
                    const double* src2data = (const double*)(src2->data.ptr);
                    double* dstdata = (double*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] =
                            src1data[size.width-1] + src2data[size.width-1];
                    }
                    while( --size.width );

                    EXIT;
                }
            }

            src1_step = src2_step = dst_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            src1_step = src1->step;
            src2_step = src2->step;
            dst_step = dst->step;
        }

        {
            CvFunc2D_3A func = (CvFunc2D_3A)(add_tab.fn_2d[depth]);

            if( !func )
                CV_ERROR( CV_StsUnsupportedFormat, "" );

            IPPI_CALL( func( src1->data.ptr, src1_step, src2->data.ptr, src2_step,
                             dst->data.ptr, dst_step, size ));
        }
    }
    else
    {
        CvMat maskstub, *mask = (CvMat*)maskarr;
        CvArithmBinMaskFunc2D func;
        int mask_step;

        if( !CV_IS_ARR(mask) )
            CV_CALL( mask = cvGetMat( mask, &maskstub ));

        if( !CV_IS_MASK_ARR(mask))
            CV_ERROR( CV_StsBadMask, "" );

        if( !CV_ARE_SIZES_EQ( mask, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );

        if( dst->data.ptr == src1->data.ptr )
            ;
        else if( dst->data.ptr == src2->data.ptr )
        {
            src2 = src1;
        }
        else
        {
            CV_CALL( cvCopy( src1, dst, mask ));
        }

        if( CV_IS_ARR_CONT( src2->type & dst->type & mask->type ))
        {
            size.width *= size.height;
            src2_step = dst_step = mask_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            src2_step = src2->step;
            dst_step = dst->step;
            mask_step = mask->step;
        }
        
        func = (CvArithmBinMaskFunc2D)
                (addmask_tab.fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src2->data.ptr, src2_step,
                         mask->data.ptr, mask_step,
                         dst->data.ptr, dst_step, size, CV_ARR_CN(type) ));
    }

    __END__;
}


CV_IMPL void
cvAddS( const void* srcarr, CvScalar scalar, void* dstarr, const void* maskarr )
{
    static CvFuncTable addmask_tab;
    static CvFuncTable add_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvAddS" );

    __BEGIN__;

    int sctype, type, coi = 0;
    int src_step, dst_step;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    double buf[12];
    CvSize size;

    if( !inittab )
    {
        icvInitAddCC1RTable( &add_tab );
        icvInitAddCCnMRTable( &addmask_tab );
        inittab = 1;
    }

    if( !CV_IS_ARR(src) )
    {
        CV_CALL( src = cvGetMat( src, &srcstub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(dst) )
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src, dst ))
            CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    sctype = type = CV_ARR_TYPE(src->type);
    if( CV_ARR_DEPTH(sctype) < CV_32S )
        sctype = (type & CV_ARR_CN_MASK) | CV_32SC1;

    size = icvGetMatSize( src );

    if( !maskarr )
    {
        if( CV_IS_ARR_CONT( src->type & dst->type ))
        {
            size.width *= size.height;
            if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
            {
                if( type == CV_32FC1 )
                {
                    const float* srcdata = (const float*)(src->data.ptr);
                    float* dstdata = (float*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] = (float)
                            (scalar.val[0] + srcdata[size.width-1]);
                    }
                    while( --size.width );

                    EXIT;
                }

                if( type == CV_64FC1 )
                {
                    const double* srcdata = (const double*)(src->data.ptr);
                    double* dstdata = (double*)(dst->data.ptr);
                
                    do
                    {
                        dstdata[size.width-1] =
                            scalar.val[0] + srcdata[size.width-1];
                    }
                    while( --size.width );

                    EXIT;
                }
            }

            src_step = dst_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            src_step = src->step;
            dst_step = dst->step;
        }

        {
            size.width *= CV_ARR_CN( type );
            CvFunc2D_2A1P func = (CvFunc2D_2A1P)(add_tab.fn_2d[CV_ARR_DEPTH(type)]);

            if( !func )
                CV_ERROR( CV_StsUnsupportedFormat, "" );

            CV_CALL( cvScalarToRawData( &scalar, sctype, buf, 1 ));

            IPPI_CALL( func( src->data.ptr, src_step,
                             dst->data.ptr, dst_step, size, buf ));
        }
    }
    else
    {
        CvMat maskstub, *mask = (CvMat*)maskarr;
        CvArithmUniMaskFunc2D func;
        int mask_step;

        if( !CV_IS_ARR(mask) )
            CV_CALL( mask = cvGetMat( mask, &maskstub ));

        if( !CV_IS_MASK_ARR(mask))
            CV_ERROR( CV_StsBadMask, "" );

        if( !CV_ARE_SIZES_EQ( mask, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );

        if( src->data.ptr != dst->data.ptr )
        {
            CV_CALL( cvCopy( src, dst, mask ));
        }

        if( CV_IS_ARR_CONT( dst->type & mask->type ))
        {
            size.width *= size.height;
            dst_step = mask_step = CV_STUB_STEP;
            size.height = 1;
        }
        else
        {
            dst_step = dst->step;
            mask_step = mask->step;
        }
        
        func = (CvArithmUniMaskFunc2D)(addmask_tab.fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        CV_CALL( cvScalarToRawData( &scalar, sctype, buf, 0 ));

        IPPI_CALL( func( dst->data.ptr, dst_step, mask->data.ptr,
                         mask_step, size, buf, CV_ARR_CN(type) ));
    }

    __END__;
}


/***************************************** M U L ****************************************/

CV_IMPL void
cvMul( const void* srcarr1, const void* srcarr2, void* dstarr )
{
    static CvFuncTable mul_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvMul" );

    __BEGIN__;

    int type, depth, coi = 0;
    int src1_step, src2_step, dst_step;
    CvMat srcstub1, *src1 = (CvMat*)srcarr1;
    CvMat srcstub2, *src2 = (CvMat*)srcarr2;
    CvMat dststub,  *dst = (CvMat*)dstarr;
    CvSize size;

    if( !inittab )
    {
        icvInitMulC1RTable( &mul_tab );
        inittab = 1;
    }

    if( !CV_IS_ARR(src1) )
    {
        CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(src2) )
    {
        CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR(dst) )
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src1, src2 ) || !CV_ARE_TYPES_EQ( src1, dst ))
            CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) || !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    type = CV_ARR_TYPE(src1->type);
    size = icvGetMatSize( src1 );

    depth = CV_ARR_DEPTH(type);
    size.width *= CV_ARR_CN( type );

    if( CV_IS_ARR_CONT( src1->type & src2->type & dst->type ))
    {
        size.width *= size.height;

        if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
        {
            if( depth == CV_32F )
            {
                const float* src1data = (const float*)(src1->data.ptr);
                const float* src2data = (const float*)(src2->data.ptr);
                float* dstdata = (float*)(dst->data.ptr);
            
                do
                {
                    dstdata[size.width-1] = (float)
                        (src1data[size.width-1] + src2data[size.width-1]);
                }
                while( --size.width );

                EXIT;
            }

            if( depth == CV_64F )
            {
                const double* src1data = (const double*)(src1->data.ptr);
                const double* src2data = (const double*)(src2->data.ptr);
                double* dstdata = (double*)(dst->data.ptr);
            
                do
                {
                    dstdata[size.width-1] =
                        src1data[size.width-1] + src2data[size.width-1];
                }
                while( --size.width );

                EXIT;
            }
        }

        src1_step = src2_step = dst_step = CV_STUB_STEP;
        size.height = 1;
    }
    else
    {
        src1_step = src1->step;
        src2_step = src2->step;
        dst_step = dst->step;
    }

    {
        CvFunc2D_3A func = (CvFunc2D_3A)(mul_tab.fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src1->data.ptr, src1_step, src2->data.ptr, src2_step,
                         dst->data.ptr, dst_step, size ));
    }

    __END__;
}

/* End of file. */
