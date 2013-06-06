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
//  CvMat logical operations: &, |, ^ ...
//
// */

#include "_cv.h"

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                             Macros for logic operations                             //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

/* //////////////////////////////////////////////////////////////////////////////////////
                                Mat op Mat
////////////////////////////////////////////////////////////////////////////////////// */


#define ICV_DEF_BIN_LOG_OP_2D( __op__, name )                                       \
IPCVAPI_IMPL( CvStatus, icv##name##_8u_C1R,                                         \
( const uchar* src1, int step1, const uchar* src2, int step2,                       \
  uchar* dst, int step, CvSize size ))                                              \
{                                                                                   \
    for( ; size.height--; src1 += step1, src2 += step2, dst += step )               \
    {                                                                               \
        int i;                                                                      \
                                                                                    \
        for( i = 0; i <= size.width - 16; i += 16 )                                 \
        {                                                                           \
            int t0 = __op__(((const int*)(src1+i))[0], ((const int*)(src2+i))[0]);  \
            int t1 = __op__(((const int*)(src1+i))[1], ((const int*)(src2+i))[1]);  \
                                                                                    \
            ((int*)(dst+i))[0] = t0;                                                \
            ((int*)(dst+i))[1] = t1;                                                \
                                                                                    \
            t0 = __op__(((const int*)(src1+i))[2], ((const int*)(src2+i))[2]);      \
            t1 = __op__(((const int*)(src1+i))[3], ((const int*)(src2+i))[3]);      \
                                                                                    \
            ((int*)(dst+i))[2] = t0;                                                \
            ((int*)(dst+i))[3] = t1;                                                \
        }                                                                           \
                                                                                    \
        for( ; i <= size.width - 4; i += 4 )                                        \
        {                                                                           \
            int t = __op__(*(const int*)(src1+i), *(const int*)(src2+i));           \
            *(int*)(dst+i) = t;                                                     \
        }                                                                           \
                                                                                    \
        for( ; i < size.width; i++ )                                                \
        {                                                                           \
            int t = __op__(((const uchar*)src1)[i],((const uchar*)src2)[i]);        \
            dst[i] = (uchar)t;                                                      \
        }                                                                           \
    }                                                                               \
                                                                                    \
    return  CV_OK;                                                                  \
}


/* //////////////////////////////////////////////////////////////////////////////////////
                                     Mat op Scalar
////////////////////////////////////////////////////////////////////////////////////// */


#define ICV_DEF_UN_LOG_OP_2D( __op__, name )                                            \
IPCVAPI_IMPL( CvStatus, icv##name##_8u_C1R,                                             \
( const uchar* src0, int step1,                                                         \
  uchar* dst0, int step, CvSize size,                                                   \
  const uchar* scalar, int pix_size ))                                                  \
{                                                                                       \
    int delta = 12*pix_size;                                                            \
                                                                                        \
    for( ; size.height--; src0 += step1, dst0 += step )                                 \
    {                                                                                   \
        const uchar* src = (const uchar*)src0;                                          \
        uchar* dst = dst0;                                                              \
        int i, len = size.width;                                                        \
                                                                                        \
        while( (len -= delta) >= 0 )                                                    \
        {                                                                               \
            for( i = 0; i < (delta); i += 12 )                                          \
            {                                                                           \
                int t0 = __op__(((const int*)(src+i))[0], ((const int*)(scalar+i))[0]); \
                int t1 = __op__(((const int*)(src+i))[1], ((const int*)(scalar+i))[1]); \
                                                                                        \
                ((int*)(dst+i))[0] = t0;                                                \
                ((int*)(dst+i))[1] = t1;                                                \
                                                                                        \
                t0 = __op__(((const int*)(src+i))[2], ((const int*)(scalar+i))[2]);     \
                                                                                        \
                ((int*)(dst+i))[2] = t0;                                                \
            }                                                                           \
            src += delta;                                                               \
            dst += delta;                                                               \
        }                                                                               \
                                                                                        \
        for( len += delta, i = 0; i < len; i++ )                                        \
        {                                                                               \
            int t = __op__(src[i],scalar[i]);                                           \
            dst[i] = (uchar)t;                                                          \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    return CV_OK;                                                                       \
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                             Macros for logic operations with mask                   //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

#define IPCV_MASK_LOGIC( name )                                         \
IPCVAPI( CvStatus, icv##name##_8u_CnMR,                                 \
( const uchar* src1, int srcstep1, const uchar* mask, int maskstep,     \
  uchar* dst, int dststep, CvSize size, int pixSize ))                  \
IPCVAPI( CvStatus, icv##name##C_8u_CnMR,                                \
( uchar* dst, int dststep, const uchar* mask, int maskstep,             \
  CvSize size, const uchar* scalar, int pixSize ))

IPCV_MASK_LOGIC( And )
IPCV_MASK_LOGIC( Or )
IPCV_MASK_LOGIC( Xor )


/* //////////////////////////////////////////////////////////////////////////////////////
                                    Mat op Mat
////////////////////////////////////////////////////////////////////////////////////// */

#define ICV_DEF_BIN_LOG_OP_MASK( __op__, _mask_op_, arrtype, worktype,          \
                                 src, dst, mask, len, cn )                      \
{                                                                               \
    int i;                                                                      \
    for( i = 0; i <= (len) - 4; i += 4, src += 4*(cn), dst += 4*(cn) )          \
    {                                                                           \
        int k = cn - 1;                                                         \
        int m = 0;                                                              \
                                                                                \
        do                                                                      \
        {                                                                       \
            worktype t0 = (mask)[i] ? -1 : 0;                                   \
            worktype t1 = (mask)[i+1] ? -1 : 0;                                 \
                                                                                \
            t0 = _mask_op_( t0, (src)[k]);                                      \
            t1 = _mask_op_( t1, (src)[k+(cn)]);                                 \
                                                                                \
            t0 = __op__( t0, (dst)[k]);                                         \
            t1 = __op__( t1, (dst)[k+(cn)]);                                    \
                                                                                \
            (dst)[k] = (arrtype)t0;                                             \
            (dst)[k+(cn)] = (arrtype)t1;                                        \
                                                                                \
            t0 = (mask)[i+2] ? -1 : 0;                                          \
            t1 = (mask)[i+3] ? -1 : 0;                                          \
                                                                                \
            t0 = _mask_op_( t0, (src)[k+2*(cn)]);                               \
            t1 = _mask_op_( t1, (src)[k+3*(cn)]);                               \
                                                                                \
            t0 = __op__( t0, (dst)[k+2*(cn)]);                                  \
            t1 = __op__( t1, (dst)[k+3*(cn)]);                                  \
                                                                                \
            (dst)[k+2*(cn)] = (arrtype)t0;                                      \
            (dst)[k+3*(cn)] = (arrtype)t1;                                      \
        }                                                                       \
        while( k-- && (m || (m = (mask[i]|mask[i+1]|mask[i+2]|mask[i+3])) != 0));\
    }                                                                           \
                                                                                \
    for( ; i < (len); i++, src += cn, dst += cn )                               \
    {                                                                           \
        int k = cn - 1;                                                         \
        do                                                                      \
        {                                                                       \
            worktype t = (mask)[i] ? -1 : 0;                                    \
            t = _mask_op_( t, (src)[k] );                                       \
            t = __op__( t, (dst)[k] );                                          \
            (dst)[k] = (arrtype)t;                                              \
        }                                                                       \
        while( k-- && mask[i] != 0 );                                           \
    }                                                                           \
}

#define ICV_DEF_BIN_LOG_OP_MASK_2D( __op__, _mask_op_, name )                           \
IPCVAPI_IMPL( CvStatus,                                                                 \
icv##name##_8u_CnMR,( const uchar* src, int step1, const uchar* mask, int step2,        \
                      uchar* dst, int step, CvSize size, int cn ))                      \
{                                                                                       \
    for( ; size.height--; (char*&)src += step1, mask += step2, (char*&)dst += step )    \
    {                                                                                   \
        const uchar* tsrc = src;                                                        \
        uchar* tdst = dst;                                                              \
                                                                                        \
        ICV_DEF_BIN_LOG_OP_MASK( __op__, _mask_op_, uchar,                              \
                                 int, tsrc, tdst, mask, size.width, cn )                \
    }                                                                                   \
                                                                                        \
    return CV_OK;                                                                       \
}


/* //////////////////////////////////////////////////////////////////////////////////////
                                     Mat op Scalar
////////////////////////////////////////////////////////////////////////////////////// */


#define ICV_DEF_UN_LOG_OP_MASK( __op__, _mask_op_, arrtype, worktype,           \
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
            arrtype value = scalar[k];                                          \
            worktype t0 = (mask)[i] ? -1 : 0;                                   \
            worktype t1 = (mask)[i+1] ? -1 : 0;                                 \
                                                                                \
            t0 = _mask_op_( t0, value );                                        \
            t1 = _mask_op_( t1, value );                                        \
                                                                                \
            t0 = __op__( t0, (dst)[k]);                                         \
            t1 = __op__( t1, (dst)[k+(cn)]);                                    \
                                                                                \
            (dst)[k] = (arrtype)t0;                                             \
            (dst)[k+(cn)] = (arrtype)t1;                                        \
                                                                                \
            t0 = (mask)[i+2] ? -1 : 0;                                          \
            t1 = (mask)[i+3] ? -1 : 0;                                          \
                                                                                \
            t0 = _mask_op_( t0, value );                                        \
            t1 = _mask_op_( t1, value );                                        \
                                                                                \
            t0 = __op__( t0, (dst)[k+2*(cn)]);                                  \
            t1 = __op__( t1, (dst)[k+3*(cn)]);                                  \
                                                                                \
            (dst)[k+2*(cn)] = (arrtype)t0;                                      \
            (dst)[k+3*(cn)] = (arrtype)t1;                                      \
        }                                                                       \
        while( k-- && (m || (m = (mask[i]|mask[i+1]|mask[i+2]|mask[i+3])) != 0));\
    }                                                                           \
                                                                                \
    for( ; i < (len); i++, dst += cn )                                          \
    {                                                                           \
        int k = cn - 1;                                                         \
        do                                                                      \
        {                                                                       \
            worktype t = (mask)[i] ? -1 : 0;                                    \
            t = _mask_op_( t, scalar[k] );                                      \
            t = __op__( t, (dst)[k] );                                          \
            (dst)[k] = (arrtype)t;                                              \
        }                                                                       \
        while( k-- && mask[i] != 0 );                                           \
    }                                                                           \
}


#define ICV_DEF_UN_LOG_OP_MASK_2D( __op__, _mask_op_, name )                    \
IPCVAPI_IMPL( CvStatus,                                                         \
icv##name##C_8u_CnMR,( uchar* dst, int step, const uchar* mask, int maskstep,   \
                       CvSize size, const uchar* scalar, int cn ))              \
{                                                                               \
    for( ; size.height--; mask += maskstep, (char*&)dst += step )               \
    {                                                                           \
        uchar* tdst = dst;                                                      \
                                                                                \
        ICV_DEF_UN_LOG_OP_MASK( __op__, _mask_op_, uchar, int,                  \
                                tdst, mask, size.width, cn )                    \
    }                                                                           \
                                                                                \
    return  CV_OK;                                                              \
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                                LOGIC OPERATIONS                                     //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

static void
icvLogicS( const void* srcarr, CvScalar* scalar,
           void* dstarr, CvFunc2D_2A1P1I fn_2d )
{
    CV_FUNCNAME( "icvLogicS" );
    
    __BEGIN__;

    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    
    int coi1 = 0, coi2 = 0;
    int pix_size, type;
    double buf[12];
    CvSize size;
    int src_step, dst_step;

    if( !CV_IS_ARR(src))
        CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));

    if( !CV_IS_ARR(dst))
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi2 ));

    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( !CV_ARE_TYPES_EQ( src, dst ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src, dst ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    size = icvGetMatSize( src );
    src_step = src->step;
    dst_step = dst->step;

    if( CV_IS_ARR_CONT( src->type & dst->type ))
    {
        size.width *= size.height;
        src_step = dst_step = CV_STUB_STEP;
        size.height = 1;
    }

    type = CV_ARR_TYPE( src->type );
    size.width *= icvPixSize[type];
    pix_size = icvPixSize[type & CV_ARR_DEPTH_MASK];

    CV_CALL( cvScalarToRawData( scalar, type, buf, 1 ));

    IPPI_CALL( fn_2d( src->data.ptr, src_step, dst->data.ptr, dst_step,
                      size, buf, pix_size ));

    __END__;
}


static void
icvLogic( const void* srcimg1, const void* srcimg2,
          void* dstarr, CvFunc2D_3A fn_2d )
{
    CV_FUNCNAME( "icvLogic" );
    
    __BEGIN__;

    int coi1 = 0, coi2 = 0, coi3 = 0;
    CvMat  srcstub1, *src1 = (CvMat*)srcimg1;
    CvMat  srcstub2, *src2 = (CvMat*)srcimg2;
    CvMat  dststub,  *dst = (CvMat*)dstarr;
    int src1_step, src2_step, dst_step;
    CvSize size;

    CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi1 ));
    CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi2 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi3 ));

    if( coi1 != 0 || coi2 != 0 || coi3 != 0 )
        CV_ERROR_FROM_CODE( CV_BadCOI );

    if( !CV_ARE_TYPES_EQ( src1, src2 ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    size = icvGetMatSize( src1 );
        
    if( !CV_ARE_TYPES_EQ( src1, dst ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );
    
    if( !CV_ARE_SIZES_EQ( src1, dst ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    src1_step = src1->step;
    src2_step = src2->step;
    dst_step = dst->step;

    if( CV_IS_ARR_CONT( src1->type & src2->type & dst->type ))
    {
        size.width *= size.height;
        src1_step = src2_step = dst_step = CV_STUB_STEP;
        size.height = 1;
    }

    size.width *= icvPixSize[CV_ARR_TYPE(src1->type)];

    IPPI_CALL( fn_2d( src1->data.ptr, src1_step, src2->data.ptr, src2_step,
                      dst->data.ptr, dst_step, size ));

    __END__;
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                       LOGIC OPERATIONS WITH MASK SUPPORT                            //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

static void
icvLogicSM( const void* srcarr, CvScalar* scalar, void* dstarr,
            const void* maskarr, CvArithmUniMaskFunc2D func )
{
    CV_FUNCNAME( "icvLogicSM" );
    
    __BEGIN__;

    double buf[12];
    int coi1 = 0, coi2 = 0;
    CvMat  srcstub, *src = (CvMat*)srcarr;
    CvMat  dststub, *dst = (CvMat*)dstarr;
    CvMat  maskstub, *mask = (CvMat*)maskarr;
    int pix_size, type;
    int dst_step, mask_step;
    CvSize size;

    if( !CV_IS_ARR(src))
        CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));

    if( !CV_IS_ARR(dst))
        CV_CALL( dst = cvGetMat( dst, &dststub ));

    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    CV_CALL( mask = cvGetMat( mask, &maskstub ));

    if( !CV_IS_MASK_ARR(mask) )
        CV_ERROR_FROM_CODE( CV_StsBadMask );

    if( !CV_ARE_SIZES_EQ( mask, dst ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    if( src->data.ptr != dst->data.ptr )
    {
        CV_CALL( cvCopy( src, dst, mask ));
    }

    size = icvGetMatSize( dst );
    dst_step = dst->step;
    mask_step = mask->step;

    if( CV_IS_ARR_CONT( mask->type & dst->type ))
    {
        size.width *= size.height;
        dst_step = mask_step = CV_STUB_STEP;
        size.height = 1;
    }

    type = CV_ARR_TYPE( src->type );
    pix_size = icvPixSize[type];
    
    CV_CALL( cvScalarToRawData( scalar, type, buf, 0 ));
    IPPI_CALL( func( dst->data.ptr, dst_step, mask->data.ptr,
                     mask_step, size, buf, pix_size ));

    __END__;
}


CV_IMPL void
icvLogicM( const void* srcimg1, const void* srcimg2,
           void* dstarr, const void* maskarr,
           CvArithmBinMaskFunc2D func )
{
    CV_FUNCNAME( "icvLogicM" );
    
    __BEGIN__;

    int  coi1 = 0, coi2 = 0, coi3 = 0;
    CvMat  srcstub1, *src1 = (CvMat*)srcimg1;
    CvMat  srcstub2, *src2 = (CvMat*)srcimg2;
    CvMat  dststub, *dst = (CvMat*)dstarr;
    CvMat  maskstub, *mask = (CvMat*)maskarr;
    int src_step, dst_step, mask_step; 
    int pix_size;
    CvSize size;

    CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi1 ));
    CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi2 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi3 ));
    CV_CALL( mask = cvGetMat( mask, &maskstub ));

    if( coi1 != 0 || coi2 != 0 || coi3 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( !CV_IS_MASK_ARR(mask) )
        CV_ERROR_FROM_CODE( CV_StsBadMask );

    if( !CV_ARE_SIZES_EQ( mask, dst ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    size = icvGetMatSize( src1 );
    pix_size = icvPixSize[CV_ARR_TYPE(src1->type)];
        
    if( src2->data.ptr != dst->data.ptr )
    {
        if( src1->data.ptr != dst->data.ptr )
        {
            CV_CALL( cvCopy( src2, dst, mask ));
        }
        else
            src1 = src2;
    }
    
    if( !CV_ARE_TYPES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    src_step = src1->step;
    dst_step = dst->step;
    mask_step = mask->step;
    
    if( CV_IS_ARR_CONT( src1->type & dst->type & mask->type ))
    {
        size.width *= size.height;
        src_step = dst_step = mask_step = CV_STUB_STEP;
        size.height = 1;
    }

    IPPI_CALL( func( src1->data.ptr, src_step, mask->data.ptr, mask_step,
                     dst->data.ptr, dst_step, size, pix_size ));

    __END__;
}


#define ICV_DEF_LOG_OP_MASK_2D( __op__, _mask_op_, name )  \
    ICV_DEF_BIN_LOG_OP_MASK_2D( __op__, _mask_op_, name )  \
    ICV_DEF_UN_LOG_OP_MASK_2D( __op__, _mask_op_, name )

ICV_DEF_LOG_OP_MASK_2D( CV_XOR, CV_AND, Xor )
ICV_DEF_LOG_OP_MASK_2D( CV_AND, CV_ORN, And )
ICV_DEF_LOG_OP_MASK_2D( CV_OR,  CV_AND, Or )

ICV_DEF_BIN_LOG_OP_2D( CV_XOR, Xor )
ICV_DEF_UN_LOG_OP_2D( CV_XOR, XorC )

ICV_DEF_BIN_LOG_OP_2D( CV_AND, And )
ICV_DEF_UN_LOG_OP_2D( CV_AND, AndC )

ICV_DEF_BIN_LOG_OP_2D( CV_OR, Or )
ICV_DEF_UN_LOG_OP_2D( CV_OR, OrC )


/////////////////////////////////////////////////////////////////////////////////////////
//                                    X O R                                            //
/////////////////////////////////////////////////////////////////////////////////////////

CV_IMPL void
cvXorS( const void* src, CvScalar scalar, void* dst, const void* mask )
{
    CV_FUNCNAME( "cvXorS" );
    
    __BEGIN__;

    if( !mask )
    {
        CV_CALL( icvLogicS( src, &scalar, dst, (CvFunc2D_2A1P1I)icvXorC_8u_C1R ));
    }
    else
    {
        CV_CALL( icvLogicSM( src, &scalar, dst, mask,
                             (CvArithmUniMaskFunc2D)icvXorC_8u_CnMR ));
    }

    __END__;
}


CV_IMPL void
cvXor( const void* src1, const void* src2, void* dst, const void* mask )
{
    CV_FUNCNAME( "cvXor" );
    
    __BEGIN__;

    if( !mask )
    {
        CV_CALL( icvLogic( src1, src2, dst,
                           (CvFunc2D_3A)icvXor_8u_C1R ));
    }
    else
    {
        CV_CALL( icvLogicM( src1, src2, dst, mask,
                            (CvArithmBinMaskFunc2D)icvXor_8u_CnMR ));
    }

    __END__;
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                    A N D                                            //
/////////////////////////////////////////////////////////////////////////////////////////

CV_IMPL void
cvAndS( const void* src, CvScalar scalar, void* dst, const void* mask )
{
    CV_FUNCNAME( "cvAndS" );
    
    __BEGIN__;

    if( !mask )
    {
        CV_CALL( icvLogicS( src, &scalar, dst, (CvFunc2D_2A1P1I)icvAndC_8u_C1R ));
    }
    else
    {
        CV_CALL( icvLogicSM( src, &scalar, dst, mask,
                             (CvArithmUniMaskFunc2D)icvAndC_8u_CnMR ));
    }

    __END__;
}


CV_IMPL void
cvAnd( const void* src1, const void* src2, void* dst, const void* mask )
{
    CV_FUNCNAME( "cvAnd" );
    
    __BEGIN__;

    if( !mask )
    {
        CV_CALL( icvLogic( src1, src2, dst,
                           (CvFunc2D_3A)icvAnd_8u_C1R ));
    }
    else
    {
        CV_CALL( icvLogicM( src1, src2, dst, mask,
                            (CvArithmBinMaskFunc2D)icvAnd_8u_CnMR ));
    }

    __END__;
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                      O R                                            //
/////////////////////////////////////////////////////////////////////////////////////////

CV_IMPL void
cvOrS( const void* src, CvScalar scalar, void* dst, const void* mask )
{
    CV_FUNCNAME( "cvOrS" );
    
    __BEGIN__;

    if( !mask )
    {
        CV_CALL( icvLogicS( src, &scalar, dst, (CvFunc2D_2A1P1I)icvOrC_8u_C1R ));
    }
    else
    {
        CV_CALL( icvLogicSM( src, &scalar, dst, mask,
                             (CvArithmUniMaskFunc2D)icvOrC_8u_CnMR ));
    }

    __END__;
}


CV_IMPL void
cvOr( const void* src1, const void* src2, void* dst, const void* mask )
{
    CV_FUNCNAME( "cvOr" );
    
    __BEGIN__;

    if( !mask )
    {
        CV_CALL( icvLogic( src1, src2, dst,
                           (CvFunc2D_3A)icvOr_8u_C1R ));
    }
    else
    {
        CV_CALL( icvLogicM( src1, src2, dst, mask,
                            (CvArithmBinMaskFunc2D)icvOr_8u_CnMR ));
    }

    __END__;
}

/* End of file. */
