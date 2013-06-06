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
//  CvMat basic operations: cvCopy, cvSet
//
// */

#include "_cv.h"

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                                  L/L COPY & SET FUNCTIONS                           //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////


IPCVAPI_IMPL( CvStatus, icvCopy_8u_C1R, ( const uchar* src, int src_step,
                                          uchar* dst, int dst_step, CvSize size ))
{
    for( ; size.height--; src += src_step, dst += dst_step )
        memcpy( dst, src, size.width );

    return  CV_OK;
}


IPCVAPI_IMPL( CvStatus, icvSet_8u_C1R, ( uchar* dst, int dst_step, CvSize size,
                                         const void* scalar, int pix_size ))
{
    int copy_len = 12*pix_size;

    for( ; size.height--; )
    {
        uchar* dst_limit = dst + size.width;

        while( dst + copy_len <= dst_limit )
        {
            memcpy( dst, scalar, copy_len );
            dst += copy_len;
        }

        memcpy( dst, scalar, dst_limit - dst );
        dst = dst_limit - size.width + dst_step;
    }

    return CV_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                                L/L COPY WITH MASK FUNCTIONS                         //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////


#define ICV_DEF_COPY_MASK_C1_CASE( type, worktype, src, dst, mask, len )\
{                                                                       \
    int i;                                                              \
                                                                        \
    for( i = 0; i <= (len) - 4; i += 4 )                                \
    {                                                                   \
        worktype m0 = (mask)[i] ? -1 : 0;                               \
        worktype m1 = (mask)[i+1] ? -1 : 0;                             \
        worktype t0 = (dst)[i];                                         \
        worktype t1 = (dst)[i+1];                                       \
                                                                        \
        t0 ^= (t0 ^ (src)[i]) & m0;                                     \
        t1 ^= (t1 ^ (src)[i+1]) & m1;                                   \
                                                                        \
        (dst)[i] = (type)t0;                                            \
        (dst)[i+1] = (type)t1;                                          \
                                                                        \
        m0 = (mask)[i+2] ? -1 : 0;                                      \
        m1 = (mask)[i+3] ? -1 : 0;                                      \
        t0 = (dst)[i+2];                                                \
        t1 = (dst)[i+3];                                                \
                                                                        \
        t0 ^= (t0 ^ (src)[i+2]) & m0;                                   \
        t1 ^= (t1 ^ (src)[i+3]) & m1;                                   \
                                                                        \
        (dst)[i+2] = (type)t0;                                          \
        (dst)[i+3] = (type)t1;                                          \
    }                                                                   \
                                                                        \
    for( ; i < (len); i++ )                                             \
    {                                                                   \
        worktype m = (mask)[i] ? -1 : 0;                                \
        worktype t = (dst)[i];                                          \
                                                                        \
        t ^= (t ^ (src)[i]) & m;                                        \
                                                                        \
        (dst)[i] = (type)t;                                             \
    }                                                                   \
}


#define ICV_DEF_COPY_MASK_C3_CASE( type, worktype, src, dst, mask, len )\
{                                                                       \
    int i;                                                              \
                                                                        \
    for( i = 0; i < (len); i++ )                                        \
    {                                                                   \
        worktype m  = (mask)[i] ? -1 : 0;                               \
        worktype t0 = (dst)[i*3];                                       \
        worktype t1 = (dst)[i*3+1];                                     \
        worktype t2 = (dst)[i*3+2];                                     \
                                                                        \
        t0 ^= (t0 ^ (src)[i*3]) & m;                                    \
        t1 ^= (t1 ^ (src)[i*3+1]) & m;                                  \
        t2 ^= (t2 ^ (src)[i*3+2]) & m;                                  \
                                                                        \
        (dst)[i*3] = (type)t0;                                          \
        (dst)[i*3+1] = (type)t1;                                        \
        (dst)[i*3+2] = (type)t2;                                        \
    }                                                                   \
}


#define ICV_DEF_COPY_MASK_C4_CASE( type, worktype, src, dst, mask, len )\
{                                                                       \
    int i;                                                              \
                                                                        \
    for( i = 0; i < (len); i++ )                                        \
    {                                                                   \
        worktype m  = (mask)[i] ? -1 : 0;                               \
        worktype t0 = (dst)[i*4];                                       \
        worktype t1 = (dst)[i*4+1];                                     \
                                                                        \
        t0 ^= (t0 ^ (src)[i*4]) & m;                                    \
        t1 ^= (t1 ^ (src)[i*4+1]) & m;                                  \
                                                                        \
        (dst)[i*4] = (type)t0;                                          \
        (dst)[i*4+1] = (type)t1;                                        \
                                                                        \
        t0 = (dst)[i*4+2];                                              \
        t1 = (dst)[i*4+3];                                              \
                                                                        \
        t0 ^= (t0 ^ (src)[i*4+2]) & m;                                  \
        t1 ^= (t1 ^ (src)[i*4+3]) & m;                                  \
                                                                        \
        (dst)[i*4+2] = (type)t0;                                        \
        (dst)[i*4+3] = (type)t1;                                        \
    }                                                                   \
}


#define ICV_DEF_COPY_MASK_2D( name, type, worktype, cn )                \
IPCVAPI_IMPL( CvStatus,                                                 \
name,( const type* src, int step1, type* dst, int step,                 \
       const uchar* mask, int step2, CvSize size ))                     \
{                                                                       \
    for( ; size.height--; (char*&)src += step1,                         \
                          (char*&)dst += step,                          \
                          mask += step2 )                               \
    {                                                                   \
        ICV_DEF_COPY_MASK_C##cn##_CASE( type, worktype, src,            \
                                        dst, mask, size.width )         \
    }                                                                   \
                                                                        \
    return  CV_OK;                                                      \
}



#define ICV_DEF_SET_MASK_C1_CASE( type, worktype, src, dst, mask, len ) \
{                                                                       \
    int i;                                                              \
                                                                        \
    for( i = 0; i <= (len) - 4; i += 4 )                                \
    {                                                                   \
        worktype m0 = (mask)[i] ? -1 : 0;                               \
        worktype m1 = (mask)[i+1] ? -1 : 0;                             \
        worktype t0 = (dst)[i];                                         \
        worktype t1 = (dst)[i+1];                                       \
                                                                        \
        t0 ^= (t0 ^ s0) & m0;                                           \
        t1 ^= (t1 ^ s0) & m1;                                           \
                                                                        \
        (dst)[i] = (type)t0;                                            \
        (dst)[i+1] = (type)t1;                                          \
                                                                        \
        m0 = (mask)[i+2] ? -1 : 0;                                      \
        m1 = (mask)[i+3] ? -1 : 0;                                      \
        t0 = (dst)[i+2];                                                \
        t1 = (dst)[i+3];                                                \
                                                                        \
        t0 ^= (t0 ^ s0) & m0;                                           \
        t1 ^= (t1 ^ s0) & m1;                                           \
                                                                        \
        (dst)[i+2] = (type)t0;                                          \
        (dst)[i+3] = (type)t1;                                          \
    }                                                                   \
                                                                        \
    for( ; i < (len); i++ )                                             \
    {                                                                   \
        worktype m = (mask)[i] ? -1 : 0;                                \
        worktype t = (dst)[i];                                          \
                                                                        \
        t ^= (t ^ s0) & m;                                              \
                                                                        \
        (dst)[i] = (type)t;                                             \
    }                                                                   \
}


#define ICV_DEF_SET_MASK_C3_CASE( type, worktype, src, dst, mask, len ) \
{                                                                       \
    int i;                                                              \
                                                                        \
    for( i = 0; i < (len); i++ )                                        \
    {                                                                   \
        worktype m  = (mask)[i] ? -1 : 0;                               \
        worktype t0 = (dst)[i*3];                                       \
        worktype t1 = (dst)[i*3+1];                                     \
        worktype t2 = (dst)[i*3+2];                                     \
                                                                        \
        t0 ^= (t0 ^ s0) & m;                                            \
        t1 ^= (t1 ^ s1) & m;                                            \
        t2 ^= (t2 ^ s2) & m;                                            \
                                                                        \
        (dst)[i*3] = (type)t0;                                          \
        (dst)[i*3+1] = (type)t1;                                        \
        (dst)[i*3+2] = (type)t2;                                        \
    }                                                                   \
}


#define ICV_DEF_SET_MASK_C4_CASE( type, worktype, src, dst, mask, len ) \
{                                                                       \
    int i;                                                              \
                                                                        \
    for( i = 0; i < (len); i++ )                                        \
    {                                                                   \
        worktype m  = (mask)[i] ? -1 : 0;                               \
        worktype t0 = (dst)[i*4];                                       \
        worktype t1 = (dst)[i*4+1];                                     \
                                                                        \
        t0 ^= (t0 ^ s0) & m;                                            \
        t1 ^= (t1 ^ s1) & m;                                            \
                                                                        \
        (dst)[i*4] = (type)t0;                                          \
        (dst)[i*4+1] = (type)t1;                                        \
                                                                        \
        t0 = (dst)[i*4+2];                                              \
        t1 = (dst)[i*4+3];                                              \
                                                                        \
        t0 ^= (t0 ^ s2) & m;                                            \
        t1 ^= (t1 ^ s3) & m;                                            \
                                                                        \
        (dst)[i*4+2] = (type)t0;                                        \
        (dst)[i*4+3] = (type)t1;                                        \
    }                                                                   \
}


#define ICV_DEF_SET_MASK_2D( name, type, worktype, cn )                 \
IPCVAPI_IMPL( CvStatus,                                                 \
name,( type* dst, int step, const uchar* mask, int step2,               \
       CvSize size, const worktype* scalar ))                           \
{                                                                       \
    ICV_UN_ENTRY_C##cn( worktype );                                     \
                                                                        \
    for( ; size.height--; mask += step2, dst += step )                  \
    {                                                                   \
        ICV_DEF_SET_MASK_C##cn##_CASE( type, worktype, buf,             \
                                       dst, mask, size.width )          \
    }                                                                   \
                                                                        \
    return CV_OK;                                                       \
}


ICV_DEF_SET_MASK_2D( icvSet_8u_C1MR, uchar, int, 1 )
ICV_DEF_SET_MASK_2D( icvSet_8u_C2MR, ushort, int, 1 )
ICV_DEF_SET_MASK_2D( icvSet_8u_C3MR, uchar, int, 3 )
ICV_DEF_SET_MASK_2D( icvSet_16u_C2MR, int, int, 1 )
ICV_DEF_SET_MASK_2D( icvSet_16u_C3MR, ushort, int, 3 )
ICV_DEF_SET_MASK_2D( icvSet_32s_C2MR, int64, int64, 1 )
ICV_DEF_SET_MASK_2D( icvSet_32s_C3MR, int, int, 3 )
ICV_DEF_SET_MASK_2D( icvSet_64s_C2MR, int, int, 4 )
ICV_DEF_SET_MASK_2D( icvSet_64s_C3MR, int64, int64, 3 )
ICV_DEF_SET_MASK_2D( icvSet_64s_C4MR, int64, int64, 4 )

ICV_DEF_COPY_MASK_2D( icvCopy_8u_C1MR, uchar, int, 1  )
ICV_DEF_COPY_MASK_2D( icvCopy_8u_C2MR, ushort, int, 1 )
ICV_DEF_COPY_MASK_2D( icvCopy_8u_C3MR, uchar, int, 3 )
ICV_DEF_COPY_MASK_2D( icvCopy_16u_C2MR, int, int, 1 )
ICV_DEF_COPY_MASK_2D( icvCopy_16u_C3MR, ushort, int, 3 )
ICV_DEF_COPY_MASK_2D( icvCopy_32s_C2MR, int64, int64, 1 )
ICV_DEF_COPY_MASK_2D( icvCopy_32s_C3MR, int, int, 3 )
ICV_DEF_COPY_MASK_2D( icvCopy_64s_C2MR, int, int, 4 )
ICV_DEF_COPY_MASK_2D( icvCopy_64s_C3MR, int64, int64, 3 )
ICV_DEF_COPY_MASK_2D( icvCopy_64s_C4MR, int64, int64, 4 )


CV_DEF_INIT_PIXSIZE_TAB_2D( Set, MR )
CV_DEF_INIT_PIXSIZE_TAB_2D( Copy, MR )


/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                           H/L COPY & CONVERT & SET FUNCTIONS                        //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

/* dst = src */
CV_IMPL void
cvCopy( const void* srcarr, void* dstarr, const void* maskarr )
{
    static CvBtFuncTable copym_tab;
    static int inittab = 0;
    
    CV_FUNCNAME( "cvCopy" );
    
    __BEGIN__;

    int pix_size;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    int src_step, dst_step;
    CvSize size;

    if( !CV_IS_ARR(src) )
    {
        int coi = 0;
        
        CV_CALL( src = cvGetMat( src, &srcstub, &coi ));

        if( coi )
        {
            if( maskarr )
                CV_ERROR( CV_StsBadArg,
                "Both source image COI selected and non-null mask are not supported" );

            switch( coi )
            {
            case 1:
                CV_CALL( cvCvtPixToPlane( src, dst, 0, 0, 0 ));
                EXIT;
            case 2:
                CV_CALL( cvCvtPixToPlane( src, 0, dst, 0, 0 ));
                EXIT;
            case 3:
                CV_CALL( cvCvtPixToPlane( src, 0, 0, dst, 0 ));
                EXIT;
            case 4:
                CV_CALL( cvCvtPixToPlane( src, 0, 0, 0, dst ));
                EXIT;
            }
        }
    }


    if( !CV_IS_ARR(dst) )
    {
        int coi = 0;
        
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi ));

        if( coi )
        {
            if( maskarr )
                CV_ERROR( CV_StsBadArg,
                "Both destination image COI selected and non-null mask are not supported" );

            switch( coi )
            {
            case 1:
                CV_CALL( cvCvtPlaneToPix( src, 0, 0, 0, dst ));
                EXIT;
            case 2:
                CV_CALL( cvCvtPlaneToPix( 0, src, 0, 0, dst ));
                EXIT;
            case 3:
                CV_CALL( cvCvtPlaneToPix( 0, 0, src, 0, dst ));
                EXIT;
            case 4:
                CV_CALL( cvCvtPlaneToPix( 0, 0, 0, src, dst ));
                EXIT;
            }
        }
    }

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    size = icvGetMatSize( src );
    pix_size = icvPixSize[CV_ARR_TYPE(src->type)];
    src_step = src->step;
    dst_step = dst->step;

    if( !maskarr )
    {
        size.width *= pix_size;

        if( CV_IS_ARR_CONT( src->type & dst->type ))
        {
            size.width *= size.height;

            if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE*(int)sizeof(double))
            {
                memcpy( dst->data.ptr, src->data.ptr, size.width );
                EXIT;
            }

            src_step = dst_step = CV_STUB_STEP;
            size.height = 1;
        }

        icvCopy_8u_C1R( src->data.ptr, src_step,
                        dst->data.ptr, dst_step, size );
    }
    else
    {
        CvFunc2D_3A func;
        CvMat maskstub, *mask = (CvMat*)maskarr;
        int mask_step = mask->step;

        if( mask )
        {
            if( !CV_IS_ARR( mask ))
                CV_CALL( mask = cvGetMat( mask, &maskstub ));
            if( !CV_IS_MASK_ARR( mask ))
                CV_ERROR( CV_StsBadMask, "" );
        }

        if( !inittab )
        {
            icvInitCopyMRTable( &copym_tab );
            inittab = 1;
        }

        if( !CV_ARE_SIZES_EQ( src, mask ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );

        if( CV_IS_ARR_CONT( src->type & dst->type & mask->type ))
        {
            size.width *= size.height;
            src_step = dst_step = mask_step = CV_STUB_STEP;
            size.height = 1;
        }

        func = (CvFunc2D_3A)(copym_tab.fn_2d[pix_size]);
        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src->data.ptr, src_step, dst->data.ptr, dst_step,
                         mask->data.ptr, mask_step, size ));
    }

    __END__;
}


/* dst(idx) = value */
CV_IMPL void cvSet( void* arr, CvScalar value, const void* maskarr )
{
    static CvBtFuncTable setm_tab;
    static int inittab = 0;
    
    CV_FUNCNAME( "cvSet" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;
    int pix_size, type;
    double buf[12];
    int mat_step;
    CvSize size;

    if( !CV_IS_ARR(mat))
    {
        int coi = 0;
        CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    type = CV_ARR_TYPE( mat->type );
    pix_size = icvPixSize[type];
    size = icvGetMatSize( mat );
    mat_step = mat->step;

    if( !maskarr )
    {
        if( CV_IS_ARR_CONT( mat->type ))
        {
            size.width *= size.height;
        
            if( size.width <= (int)(CV_MAX_INLINE_MAT_OP_SIZE*sizeof(double)))
            {
                if( type == CV_32FC1 )
                {
                    int* dstdata = (int*)(mat->data.ptr);
                    float val = (float)value.val[0];
                    int ival = (int&)val;

                    do
                    {
                        dstdata[size.width-1] = ival;
                    }
                    while( --size.width );

                    EXIT;
                }

                if( type == CV_64FC1 )
                {
                    int64* dstdata = (int64*)(mat->data.ptr);
                    int64 ival = (int64&)(value.val[0]);

                    do
                    {
                        dstdata[size.width-1] = ival;
                    }
                    while( --size.width );

                    EXIT;
                }
            }

            mat_step = CV_STUB_STEP;
            size.height = 1;
        }
        
        size.width *= pix_size;
        CV_CALL( cvScalarToRawData( &value, type, buf, 1 ));

        IPPI_CALL( icvSet_8u_C1R( mat->data.ptr, mat_step, size, buf,
                                  icvPixSize[type & ~CV_ARR_CN_MASK]));
    }
    else
    {
        CvFunc2D_2A1P func;
        CvMat maskstub, *mask = (CvMat*)maskarr;
        int mask_step;

        CV_CALL( mask = cvGetMat( mask, &maskstub ));

        if( !CV_IS_MASK_ARR( mask ))
            CV_ERROR( CV_StsBadMask, "" );

        if( !inittab )
        {
            icvInitSetMRTable( &setm_tab );
            inittab = 1;
        }

        if( !CV_ARE_SIZES_EQ( mat, mask ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );

        mask_step = mask->step;

        if( CV_IS_ARR_CONT( mat->type & mask->type ))
        {
            size.width *= size.height;
            mat_step = mask_step = CV_STUB_STEP;
            size.height = 1;
        }

        func = (CvFunc2D_2A1P)(setm_tab.fn_2d[pix_size]);
        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        CV_CALL( cvScalarToRawData( &value, type, buf, 0 ));

        IPPI_CALL( func( mat->data.ptr, mat_step, mask->data.ptr,
                         mask_step, size, buf ));
    }

    __END__;
}


/****************************************************************************************\
*                                          Clearing                                      *
\****************************************************************************************/

IPCVAPI_IMPL( CvStatus,
icvSetZero_8u_C1R, ( uchar* dst, int dststep, CvSize size ))
{
    for( ; size.height--; dst += dststep )
    {
        memset( dst, 0, size.width );
    }

    return CV_OK;
}

CV_IMPL void
cvSetZero( CvArr* arr )
{
    CV_FUNCNAME( "cvSetZero" );
    
    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;
    CvSize size;
    int mat_step;

    if( !CV_IS_ARR( mat ))
    {
        int coi = 0;
        CV_CALL( mat = cvGetMat( mat, &stub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
    }

    size = icvGetMatSize( mat );
    size.width *= icvPixSize[CV_ARR_TYPE(mat->type)];
    mat_step = mat->step;

    if( CV_IS_ARR_CONT( mat->type ))
    {
        size.width *= size.height;

        if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE*(int)sizeof(double) )
        {
            memset( mat->data.ptr, 0, size.width );
            EXIT;
        }

        mat_step = CV_STUB_STEP;
        size.height = 1;
    }

    IPPI_CALL( icvSetZero_8u_C1R( mat->data.ptr, mat_step, size ));

    __END__;
}


/****************************************************************************************\
*                                          Flipping                                      *
\****************************************************************************************/

#define ICV_DEF_FLIP_HZ_CASE_C1( arrtype, src, dst, len )           \
    for( i = 0; i < (len)/2; i++ )                                  \
    {                                                               \
        arrtype t0 = (src)[i];                                      \
        arrtype t1 = (src)[(len) - i - 1];                          \
        (dst)[i] = t1;                                              \
        (dst)[(len) - i - 1] = t0;                                  \
    }


#define ICV_DEF_FLIP_HZ_CASE_C3( arrtype, src, dst, len )           \
    for( i = 0; i < (len)/2; i++ )                                  \
    {                                                               \
        arrtype t0 = (src)[i*3];                                    \
        arrtype t1 = (src)[((len) - i)*3 - 3];                      \
        (dst)[i*3] = t1;                                            \
        (dst)[((len) - i)*3 - 3] = t0;                              \
        t0 = (src)[i*3 + 1];                                        \
        t1 = (src)[((len) - i)*3 - 2];                              \
        (dst)[i*3 + 1] = t1;                                        \
        (dst)[((len) - i)*3 - 2] = t0;                              \
        t0 = (src)[i*3 + 2];                                        \
        t1 = (src)[((len) - i)*3 - 1];                              \
        (dst)[i*3 + 2] = t1;                                        \
        (dst)[((len) - i)*3 - 1] = t0;                              \
    }


#define ICV_DEF_FLIP_HZ_CASE_C4( arrtype, src, dst, len )           \
    for( i = 0; i < (len)/2; i++ )                                  \
    {                                                               \
        arrtype t0 = (src)[i*4];                                    \
        arrtype t1 = (src)[((len) - i)*4 - 3];                      \
        (dst)[i*4] = t1;                                            \
        (dst)[((len) - i)*4 - 3] = t0;                              \
        t0 = (src)[i*4];                                            \
        t1 = (src)[((len) - i)*4 - 3];                              \
        (dst)[i*4] = t1;                                            \
        (dst)[((len) - i)*4 - 3] = t0;                              \
        t0 = (src)[i*4 + 1];                                        \
        t1 = (src)[((len) - i)*4 - 2];                              \
        (dst)[i*4 + 1] = t1;                                        \
        (dst)[((len) - i)*4 - 2] = t0;                              \
        t0 = (src)[i*4 + 2];                                        \
        t1 = (src)[((len) - i)*4 - 1];                              \
        (dst)[i*4 + 2] = t1;                                        \
        (dst)[((len) - i)*4 - 1] = t0;                              \
    }


#define ICV_DEF_FLIP_HZ_FUNC( flavor, arrtype, cn )                 \
static CvStatus                                                     \
icvFlipHorz_##flavor( const arrtype* src, int srcstep,              \
                      arrtype* dst, int dststep, CvSize size )      \
{                                                                   \
    int y, i;                                                       \
    for( y = 0; y < size.height; y++, (char*&)src += srcstep,       \
                                      (char*&)dst += dststep )      \
    {                                                               \
        ICV_DEF_FLIP_HZ_CASE_C##cn( arrtype, src, dst, size.width ) \
    }                                                               \
                                                                    \
    return CV_OK;                                                   \
}


ICV_DEF_FLIP_HZ_FUNC( 8u_C1R, uchar, 1 )
ICV_DEF_FLIP_HZ_FUNC( 8u_C2R, ushort, 1 )
ICV_DEF_FLIP_HZ_FUNC( 8u_C3R, uchar, 3 )
ICV_DEF_FLIP_HZ_FUNC( 16u_C2R, int, 1 )
ICV_DEF_FLIP_HZ_FUNC( 16u_C3R, ushort, 3 )
ICV_DEF_FLIP_HZ_FUNC( 32s_C2R, int64, 1 )
ICV_DEF_FLIP_HZ_FUNC( 32s_C3R, int, 3 )
ICV_DEF_FLIP_HZ_FUNC( 64s_C2R, int, 4 )
ICV_DEF_FLIP_HZ_FUNC( 64s_C3R, int64, 3 )
ICV_DEF_FLIP_HZ_FUNC( 64s_C4R, int64, 4 )

CV_DEF_INIT_PIXSIZE_TAB_2D( FlipHorz, R )


static CvStatus
icvFlipVert_8u_C1R( const uchar* src, int srcstep,
                    uchar* dst, int dststep, CvSize size )
{
    int y, i;
    const uchar* src1 = src + (size.height - 1)*srcstep;
    uchar* dst1 = dst + (size.height - 1)*dststep;

    for( y = 0; y < (size.height + 1)/2; y++, src += srcstep, src1 -= srcstep,
                                              dst += dststep, dst1 -= dststep )
    {
        for( i = 0; i <= size.width - 16; i += 16 )
        {
            int t0 = ((int*)(src + i))[0];
            int t1 = ((int*)(src1 + i))[0];

            ((int*)(dst + i))[0] = t1;
            ((int*)(dst1 + i))[0] = t0;

            t0 = ((int*)(src + i))[1];
            t1 = ((int*)(src1 + i))[1];

            ((int*)(dst + i))[1] = t1;
            ((int*)(dst1 + i))[1] = t0;

            t0 = ((int*)(src + i))[2];
            t1 = ((int*)(src1 + i))[2];

            ((int*)(dst + i))[2] = t1;
            ((int*)(dst1 + i))[2] = t0;

            t0 = ((int*)(src + i))[3];
            t1 = ((int*)(src1 + i))[3];

            ((int*)(dst + i))[3] = t1;
            ((int*)(dst1 + i))[3] = t0;
        }

        for( ; i <= size.width - 4; i += 4 )
        {
            int t0 = ((int*)(src + i))[0];
            int t1 = ((int*)(src1 + i))[0];

            ((int*)(dst + i))[0] = t1;
            ((int*)(dst1 + i))[0] = t0;
        }

        for( ; i < size.width; i++ )
        {
            uchar t0 = src[0];
            uchar t1 = src1[0];

            dst[0] = t1;
            dst1[0] = t0;
        }
    }

    return CV_OK;
}


CV_IMPL void
cvFlip( const CvArr* srcarr, CvArr* dstarr, int flip_mode )
{
    static CvBtFuncTable tab;
    static int inittab = 0;
    
    CV_FUNCNAME( "cvFlip" );
    
    __BEGIN__;

    CvMat sstub, *src = (CvMat*)srcarr;
    CvMat dstub, *dst = (CvMat*)dstarr;
    CvSize size;
    CvFunc2D_2A func = 0;
    int pix_size;

    if( !inittab )
    {
        icvInitFlipHorzRTable( &tab );
        inittab = 1;
    }

    if( !CV_IS_ARR( src ))
    {
        int coi = 0;
        CV_CALL( src = cvGetMat( src, &sstub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
    }

    if( !CV_IS_ARR( dst ))
    {
        int coi = 0;
        CV_CALL( dst = cvGetMat( dst, &dstub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
    }


    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    size = icvGetMatSize( src );
    pix_size = icvPixSize[CV_ARR_TYPE( src->type )];

    if( flip_mode == 0 )
    {
        size.width *= pix_size;
        
        IPPI_CALL( icvFlipVert_8u_C1R( src->data.ptr, src->step,
                                       dst->data.ptr, dst->step, size ));
    }
    else
    {
        int inplace = src->data.ptr == dst->data.ptr;
        uchar* dst_data = dst->data.ptr;
        int dst_step = dst->step;

        func = (CvFunc2D_2A)(tab.fn_2d[pix_size]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        if( flip_mode < 0 && !inplace )
        {
            dst_data += dst_step * (dst->height - 1);
            dst_step = -dst_step;
        }

        IPPI_CALL( func( src->data.ptr, src->step, dst_data, dst_step, size ));
        
        if( flip_mode < 0 && inplace )
        {
            size.width *= pix_size;
            IPPI_CALL( icvFlipVert_8u_C1R( dst->data.ptr, dst->step,
                                           dst->data.ptr, dst->step, size ));
        }
    }

    __END__;
}


/* End of file. */

