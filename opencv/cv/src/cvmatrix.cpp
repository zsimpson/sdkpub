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

#include "_cv.h"
#include "_cvwrap.h"

/****************************************************************************************\
*                                         cvSetIdentity                                  *
\****************************************************************************************/

CV_IMPL void
cvSetIdentity( CvArr* array )
{
    CV_FUNCNAME( "cvSetIdentity" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)array;
    CvSize size;
    int i, len, step, pix_size;
    uchar* data = 0;

    if( !CV_IS_ARR( mat ))
    {
        int coi = 0;
        CV_CALL( mat = cvGetMat( mat, &stub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
    }

    size = icvGetMatSize( mat );
    len = CV_IMIN( size.width, size.height );

    pix_size = icvPixSize[CV_ARR_TYPE(mat->type)];
    size.width *= pix_size;

    if( CV_IS_ARR_CONT( mat->type ))
    {
        size.width *= size.height;
        size.height = 1;
    }

    data = mat->data.ptr;
    step = mat->step;
    IPPI_CALL( icvSetZero_8u_C1R( data, step, size ));
    step += pix_size;

    switch( CV_ARR_DEPTH( mat->type ))
    {
    case CV_32F:
        for( i = 0; i < len; i++, (char*&)data += step )
        {
            ((float*)data)[0] = 1.f;
        }
        break;
    case CV_64F:
        for( i = 0; i < len; i++, (char*&)data += step )
        {
            ((double*)data)[0] = 1.;
        }
        break;
    case CV_8U:
    case CV_8S:
        for( i = 0; i < len; i++, (char*&)data += step )
        {
            // !!! Big endian will cause problem here: replace 0 with
            // sizeof(array_data_type) - 1 then
            data[0] = 1;
        }
        break;
    case CV_16S:
        for( i = 0; i < len; i++, (char*&)data += step )
        {
            // !!! Big endian will cause problem here: replace 0 with
            // sizeof(array_data_type) - 1 then
            ((short*)data)[0] = 1;
        }
        break;
    case CV_32S:
        for( i = 0; i < len; i++, (char*&)data += step )
        {
            // !!! Big endian will cause problem here: replace 0 with
            // sizeof(array_data_type) - 1 then
            ((int*)data)[0] = 1;
        }
        break;
    default:
        assert(0);
        break;
    }

    CV_CHECK_NANS( mat );

    __END__;
}


/****************************************************************************************\
*                                          cvTrace                                       *
\****************************************************************************************/

CV_IMPL CvScalar
cvTrace( const CvArr* array )
{
    CvScalar sum = {{ 0, 0, 0, 0 }};
    
    CV_FUNCNAME( "cvTrace" );

    __BEGIN__;

    CvMat stub, *mat = 0;

    CV_CALL( mat = cvGetDiag( array, &stub ));
    CV_CALL( sum = cvSum( mat ));

    icvCheckVector_64f( sum.val, 4 );

    __END__;

    return sum;
}


/****************************************************************************************\
*                                        cvTranspose                                     *
\****************************************************************************************/

/////////////////// macros for inplace transposition of square matrix ////////////////////

#define ICV_DEF_TRANSP_INP_CASE_C1( arrtype, arr, step, len )   \
{                                                               \
    arrtype* arr1 = arr;                                        \
                                                                \
    while( --len )                                              \
    {                                                           \
        (char*&)arr += step, arr1++;                            \
        arrtype* arr2 = arr;                                    \
        arrtype* arr3 = arr1;                                   \
                                                                \
        do                                                      \
        {                                                       \
            arrtype t0 = arr2[0];                               \
            arrtype t1 = arr3[0];                               \
            arr2[0] = t1;                                       \
            arr3[0] = t0;                                       \
                                                                \
            arr2++;                                             \
            (char*&)arr3 += step;                               \
        }                                                       \
        while( arr2 != arr3  );                                 \
    }                                                           \
}


#define ICV_DEF_TRANSP_INP_CASE_C3( arrtype, arr, step, len )   \
{                                                               \
    arrtype* arr1 = arr;                                        \
    int y;                                                      \
                                                                \
    for( y = 1; y < len; y++ )                                  \
    {                                                           \
        (char*&)arr += step, arr1 += 3;                         \
        arrtype* arr2 = arr;                                    \
        arrtype* arr3 = arr1;                                   \
                                                                \
        for( ; arr2 != arr3; arr2 += 3, (char*&)arr3 += step )  \
        {                                                       \
            arrtype t0 = arr2[0];                               \
            arrtype t1 = arr3[0];                               \
            arr2[0] = t1;                                       \
            arr3[0] = t0;                                       \
            t0 = arr2[1];                                       \
            t1 = arr3[1];                                       \
            arr2[1] = t1;                                       \
            arr3[1] = t0;                                       \
            t0 = arr2[2];                                       \
            t1 = arr3[2];                                       \
            arr2[2] = t1;                                       \
            arr3[2] = t0;                                       \
        }                                                       \
    }                                                           \
}


#define ICV_DEF_TRANSP_INP_CASE_C4( arrtype, arr, step, len )   \
{                                                               \
    arrtype* arr1 = arr;                                        \
    int y;                                                      \
                                                                \
    for( y = 1; y < len; y++ )                                  \
    {                                                           \
        (char*&)arr += step, arr1 += 4;                         \
        arrtype* arr2 = arr;                                    \
        arrtype* arr3 = arr1;                                   \
                                                                \
        for( ; arr2 != arr3; arr2 += 4, (char*&)arr3 += step )  \
        {                                                       \
            arrtype t0 = arr2[0];                               \
            arrtype t1 = arr3[0];                               \
            arr2[0] = t1;                                       \
            arr3[0] = t0;                                       \
            t0 = arr2[1];                                       \
            t1 = arr3[1];                                       \
            arr2[1] = t1;                                       \
            arr3[1] = t0;                                       \
            t0 = arr2[2];                                       \
            t1 = arr3[2];                                       \
            arr2[2] = t1;                                       \
            arr3[2] = t0;                                       \
            t0 = arr2[3];                                       \
            t1 = arr3[3];                                       \
            arr2[3] = t1;                                       \
            arr3[3] = t0;                                       \
        }                                                       \
    }                                                           \
}


//////////////// macros for non-inplace transposition of rectangular matrix //////////////

#define ICV_DEF_TRANSP_CASE_C1( arrtype, src, srcstep,                              \
                                dst, dststep, size )                                \
{                                                                                   \
    int x, y;                                                                       \
                                                                                    \
    for( y = 0; y <= size.height - 2; y += 2, (char*&)src += 2*srcstep, dst += 2 )  \
    {                                                                               \
        const arrtype* src1 = (const arrtype*)((char*)src + srcstep);               \
        uchar* dst1 = (uchar*)dst;                                                  \
                                                                                    \
        for( x = 0; x <= size.width - 2; x += 2, dst1 += dststep )                  \
        {                                                                           \
            arrtype t0 = src[x];                                                    \
            arrtype t1 = src1[x];                                                   \
            ((arrtype*)dst1)[0] = t0;                                               \
            ((arrtype*)dst1)[1] = t1;                                               \
                                                                                    \
            dst1 += dststep;                                                        \
                                                                                    \
            t0 = src[x + 1];                                                        \
            t1 = src1[x + 1];                                                       \
            ((arrtype*)dst1)[0] = t0;                                               \
            ((arrtype*)dst1)[1] = t1;                                               \
        }                                                                           \
                                                                                    \
        if( x < size.width )                                                        \
        {                                                                           \
            arrtype t0 = src[x];                                                    \
            arrtype t1 = src1[x];                                                   \
            ((arrtype*)dst1)[0] = t0;                                               \
            ((arrtype*)dst1)[1] = t1;                                               \
        }                                                                           \
    }                                                                               \
                                                                                    \
    if( y < size.height )                                                           \
    {                                                                               \
        uchar* dst1 = (uchar*)dst;                                                  \
        for( x = 0; x <= size.width - 2; x += 2, dst1 += 2*dststep )                \
        {                                                                           \
            arrtype t0 = src[x];                                                    \
            arrtype t1 = src[x + 1];                                                \
            ((arrtype*)dst1)[0] = t0;                                               \
            ((arrtype*)(dst1 + dststep))[0] = t1;                                   \
        }                                                                           \
                                                                                    \
        if( x < size.width )                                                        \
        {                                                                           \
            arrtype t0 = src[x];                                                    \
            ((arrtype*)dst1)[0] = t0;                                               \
        }                                                                           \
    }                                                                               \
}


#define ICV_DEF_TRANSP_CASE_C3( arrtype, src, srcstep,                              \
                                dst, dststep, size )                                \
{                                                                                   \
    size.width *= 3;                                                                \
                                                                                    \
    for( ; size.height--; (char*&)src += srcstep, dst++ )                           \
    {                                                                               \
        int x;                                                                      \
        arrtype* dst1 = dst;                                                        \
                                                                                    \
        for( x = 0; x < size.width; x += 3, (char*&)dst1 += dststep )               \
        {                                                                           \
            arrtype t0 = src[x];                                                    \
            arrtype t1 = src[x + 1];                                                \
            arrtype t2 = src[x + 2];                                                \
                                                                                    \
            dst1[0] = t0;                                                           \
            dst1[1] = t1;                                                           \
            dst1[2] = t2;                                                           \
        }                                                                           \
    }                                                                               \
}


#define ICV_DEF_TRANSP_CASE_C4( arrtype, src, srcstep,                              \
                                dst, dststep, size )                                \
{                                                                                   \
    size.width *= 4;                                                                \
                                                                                    \
    for( ; size.height--; (char*&)src += srcstep, dst++ )                           \
    {                                                                               \
        int x;                                                                      \
        arrtype* dst1 = dst;                                                        \
                                                                                    \
        for( x = 0; x < size.width; x += 4, (char*&)dst1 += dststep )               \
        {                                                                           \
            arrtype t0 = src[x];                                                    \
            arrtype t1 = src[x + 1];                                                \
                                                                                    \
            dst1[0] = t0;                                                           \
            dst1[1] = t1;                                                           \
                                                                                    \
            t0 = src[x + 2];                                                        \
            t1 = src[x + 3];                                                        \
                                                                                    \
            dst1[2] = t0;                                                           \
            dst1[3] = t1;                                                           \
        }                                                                           \
    }                                                                               \
}


#define ICV_DEF_TRANSP_INP_FUNC( flavor, arrtype, cn )      \
static CvStatus CV_STDCALL                                  \
icvTranspose_##flavor( arrtype* arr, int step, CvSize size )\
{                                                           \
    assert( size.width == size.height );                    \
                                                            \
    ICV_DEF_TRANSP_INP_CASE_C##cn( arrtype, arr,            \
                                   step, size.width )       \
                                                            \
    return CV_OK;                                           \
}


#define ICV_DEF_TRANSP_FUNC( flavor, arrtype, cn )          \
static CvStatus CV_STDCALL                                  \
icvTranspose_##flavor( const arrtype* src, int srcstep,     \
                    arrtype* dst, int dststep, CvSize size )\
{                                                           \
    ICV_DEF_TRANSP_CASE_C##cn( arrtype, src, srcstep,       \
                               dst, dststep, size )         \
                                                            \
    return CV_OK;                                           \
}


ICV_DEF_TRANSP_INP_FUNC( 8u_C1IR, uchar, 1 )
ICV_DEF_TRANSP_INP_FUNC( 8u_C2IR, ushort, 1 )
ICV_DEF_TRANSP_INP_FUNC( 8u_C3IR, uchar, 3 )
ICV_DEF_TRANSP_INP_FUNC( 16u_C2IR, int, 1 )
ICV_DEF_TRANSP_INP_FUNC( 16u_C3IR, ushort, 3 )
ICV_DEF_TRANSP_INP_FUNC( 32s_C2IR, int64, 1 )
ICV_DEF_TRANSP_INP_FUNC( 32s_C3IR, int, 3 )
ICV_DEF_TRANSP_INP_FUNC( 64s_C2IR, int, 4 )
ICV_DEF_TRANSP_INP_FUNC( 64s_C3IR, int64, 3 )
ICV_DEF_TRANSP_INP_FUNC( 64s_C4IR, int64, 4 )


ICV_DEF_TRANSP_FUNC( 8u_C1R, uchar, 1 )
ICV_DEF_TRANSP_FUNC( 8u_C2R, ushort, 1 )
ICV_DEF_TRANSP_FUNC( 8u_C3R, uchar, 3 )
ICV_DEF_TRANSP_FUNC( 16u_C2R, int, 1 )
ICV_DEF_TRANSP_FUNC( 16u_C3R, ushort, 3 )
ICV_DEF_TRANSP_FUNC( 32s_C2R, int64, 1 )
ICV_DEF_TRANSP_FUNC( 32s_C3R, int, 3 )
ICV_DEF_TRANSP_FUNC( 64s_C2R, int, 4 )
ICV_DEF_TRANSP_FUNC( 64s_C3R, int64, 3 )
ICV_DEF_TRANSP_FUNC( 64s_C4R, int64, 4 )


CV_DEF_INIT_PIXSIZE_TAB_2D( Transpose, R )
CV_DEF_INIT_PIXSIZE_TAB_2D( Transpose, IR )


CV_IMPL void
cvTranspose( const CvArr* srcarr, CvArr* dstarr )
{
    static CvBtFuncTable tab, inp_tab;
    static int inittab = 0;
    
    CV_FUNCNAME( "cvTranspose" );

    __BEGIN__;

    CvMat sstub, *src = (CvMat*)srcarr;
    CvMat dstub, *dst = (CvMat*)dstarr;
    CvSize size;
    int type, pix_size;

    if( !inittab )
    {
        icvInitTransposeIRTable( &inp_tab );
        icvInitTransposeRTable( &tab );
        inittab = 1;
    }

    if( !CV_IS_ARR( src ))
    {
        int coi = 0;
        CV_CALL( src = cvGetMat( src, &sstub, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
    }

    type = CV_ARR_TYPE( src->type );
    pix_size = icvPixSize[type];
    size = icvGetMatSize( src );

    if( dstarr == srcarr )
    {
        dst = src; 
    }
    else
    {
        if( !CV_IS_ARR( dst ))
        {
            int coi = 0;
            CV_CALL( dst = cvGetMat( dst, &dstub, &coi ));

            if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
        }

        if( !CV_ARE_TYPES_EQ( src, dst ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( size.width != dst->height || size.height != dst->width )
            CV_ERROR( CV_StsUnmatchedSizes, "" );
    }

    if( src->data.ptr == dst->data.ptr )
    {
        if( size.width == size.height )
        {
            CvFunc2D_1A func = (CvFunc2D_1A)(inp_tab.fn_2d[pix_size]);

            if( !func )
                CV_ERROR( CV_StsUnsupportedFormat, "" );

            IPPI_CALL( func( src->data.ptr, src->step, size ));
        }
        else
        {
            if( size.width != 1 && size.height != 1 )
                CV_ERROR( CV_StsBadSize,
                    "Rectangular matrix can not be transposed inplace" );
            
            if( !CV_IS_ARR_CONT( src->type & dst->type ))
                CV_ERROR( CV_StsBadFlag, "In case of inplace column/row transposition "
                                       "both source and destination must be continuous" );

            if( dst == src )
            {
                int t;
                CV_SWAP( dst->width, dst->height, t );
                dst->step = dst->height == 1 ? 0 : pix_size;
            }
        }
    }
    else
    {
        CvFunc2D_2A func = (CvFunc2D_2A)(tab.fn_2d[pix_size]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src->data.ptr, src->step,
                         dst->data.ptr, dst->step, size ));
    }

    CV_CHECK_NANS( dst );

    __END__;
}


/****************************************************************************************\
*              Linear system solution via LU decomposition and related functions         *
\****************************************************************************************/

#define arrtype float
#define temptype double

typedef  CvStatus (CV_STDCALL * CvLUDecompFunc)( void* src, int srcstep, CvSize srcsize,
                                                 void* dst, int dststep, CvSize dstsize,
                                                 double* det );

typedef  CvStatus (CV_STDCALL * CvLUBackFunc)( void* src, int srcstep, CvSize srcsize,
                                               void* dst, int dststep, CvSize dstsize );


#define ICV_DEF_LU_DECOMP_FUNC( flavor, arrtype )                               \
IPCVAPI_IMPL( CvStatus,                                                         \
icvLUDecomp_##flavor, ( arrtype* A, int stepA, CvSize sizeA,                    \
                        arrtype* B, int stepB, CvSize sizeB,                    \
                        double* _det ))                                         \
{                                                                               \
    int n = sizeA.width;                                                        \
    int m = 0, i;                                                               \
    double det = 1;                                                             \
                                                                                \
    assert( sizeA.width == sizeA.height );                                      \
                                                                                \
    if( B )                                                                     \
    {                                                                           \
        assert( sizeA.height == sizeB.height );                                 \
        m = sizeB.width;                                                        \
    }                                                                           \
                                                                                \
    for( i = 0; i < n; i++, (char*&)A += stepA, (char*&)B += stepB )            \
    {                                                                           \
        int j, k = i;                                                           \
        arrtype *tA = A, *tB = 0;                                               \
        arrtype kval = (arrtype)fabs(A[i]);                                     \
        double inv_val;                                                         \
                                                                                \
        /* find the pivot element */                                            \
        for( j = i + 1; j < n; j++ )                                            \
        {                                                                       \
            arrtype tval;                                                       \
            (char*&)tA += stepA;                                                \
                                                                                \
            tval = (arrtype)fabs(tA[i]);                                        \
            if( tval > kval )                                                   \
            {                                                                   \
                kval = tval;                                                    \
                k = j;                                                          \
            }                                                                   \
        }                                                                       \
                                                                                \
        if( kval == 0 )                                                         \
        {                                                                       \
            det = 0;                                                            \
            break;                                                              \
        }                                                                       \
                                                                                \
        /* swap rows */                                                         \
        if( k != i )                                                            \
        {                                                                       \
            tA = (arrtype*)((char*)A + stepA*(k - i));                          \
            det = -det;                                                         \
                                                                                \
            for( j = i; j < n; j++ )                                            \
            {                                                                   \
                arrtype t;                                                      \
                CV_SWAP( A[j], tA[j], t );                                      \
            }                                                                   \
                                                                                \
            if( m > 0 )                                                         \
            {                                                                   \
                tB = (arrtype*)((char*)B + stepB*(k - i));                      \
                                                                                \
                for( j = 0; j < m; j++ )                                        \
                {                                                               \
                    arrtype t = B[j];                                           \
                    CV_SWAP( B[j], tB[j], t );                                  \
                }                                                               \
            }                                                                   \
        }                                                                       \
                                                                                \
        inv_val = 1./A[i];                                                      \
        det *= A[i];                                                            \
        tA = A;                                                                 \
        tB = B;                                                                 \
        A[i] = (arrtype)inv_val;                                                \
                                                                                \
        /* update matrix and the right side of the system */                    \
        for( j = i + 1; j < n; j++ )                                            \
        {                                                                       \
            double alpha;                                                       \
                                                                                \
            (char*&)tA += stepA;                                                \
            (char*&)tB += stepB;                                                \
                                                                                \
            alpha = -tA[i]*inv_val;                                             \
                                                                                \
            for( k = i + 1; k < n; k++ )                                        \
                tA[k] = (arrtype)(tA[k] + alpha*A[k]);                          \
                                                                                \
            if( m > 0 )                                                         \
                for( k = 0; k < m; k++ )                                        \
                    tB[k] = (arrtype)(tB[k] + alpha*B[k]);                      \
        }                                                                       \
    }                                                                           \
                                                                                \
    if( _det )                                                                  \
        *_det = det;                                                            \
                                                                                \
    return CV_OK;                                                               \
}


ICV_DEF_LU_DECOMP_FUNC( 32f, float )
ICV_DEF_LU_DECOMP_FUNC( 64f, double )


#define ICV_DEF_LU_BACK_FUNC( flavor, arrtype )                                 \
IPCVAPI_IMPL( CvStatus,                                                         \
icvLUBack_##flavor, ( arrtype* A, int stepA, CvSize sizeA,                      \
                      arrtype* B, int stepB, CvSize sizeB ))                    \
{                                                                               \
    int n = sizeA.width;                                                        \
    int m = sizeB.width, i;                                                     \
                                                                                \
    assert( m > 0 && sizeA.width == sizeA.height &&                             \
            sizeA.height == sizeB.height );                                     \
                                                                                \
    (char*&)A += stepA*(n - 1);                                                 \
    (char*&)B += stepB*(n - 1);                                                 \
                                                                                \
    for( i = n - 1; i >= 0; i--, (char*&)A -= stepA )                           \
    {                                                                           \
        int j, k;                                                               \
                                                                                \
        for( j = 0; j < m; j++ )                                                \
        {                                                                       \
            arrtype* tB = B + j;                                                \
            double x = 0;                                                       \
                                                                                \
            for( k = n - 1; k > i; k--, (char*&)tB -= stepB )                   \
                x += A[k]*tB[0];                                                \
                                                                                \
            tB[0] = (arrtype)((tB[0] - x)*A[i]);                                \
        }                                                                       \
    }                                                                           \
                                                                                \
    return CV_OK;                                                               \
}


ICV_DEF_LU_BACK_FUNC( 32f, float )
ICV_DEF_LU_BACK_FUNC( 64f, double )

static CvFuncTable lu_decomp_tab, lu_back_tab;
static int lu_inittab = 0;

static void icvInitLUTable( CvFuncTable* decomp_tab,
                            CvFuncTable* back_tab )
{
    decomp_tab->fn_2d[0] = (void*)icvLUDecomp_32f;
    decomp_tab->fn_2d[1] = (void*)icvLUDecomp_64f;
    back_tab->fn_2d[0] = (void*)icvLUBack_32f;
    back_tab->fn_2d[1] = (void*)icvLUBack_64f;
}



/****************************************************************************************\
*                                     Determinant                                        *
\****************************************************************************************/

#define det2(m)   (m(0,0)*m(1,1) - m(0,1)*m(1,0))
#define det3(m)   (m(0,0)*(m(1,1)*m(2,2) - m(1,2)*m(2,1)) -  \
                   m(0,1)*(m(1,0)*m(2,2) - m(1,2)*m(2,0)) +  \
                   m(0,2)*(m(1,0)*m(2,1) - m(1,1)*m(2,0)))


CV_IMPL double
cvDet( const CvArr* arr )
{
    double result = 0;
    uchar* buffer = 0;
    int local_alloc = 0;
    
    CV_FUNCNAME( "cvDet" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;
    int type;

    if( !CV_IS_ARR( mat ))
    {
        CV_CALL( mat = cvGetMat( mat, &stub ));
    }

    type = CV_ARR_TYPE( mat->type );

    if( mat->width != mat->height )
        CV_ERROR( CV_StsBadSize, "The matrix must be square" );

    #define Mf( y, x ) ((float*)(m + y*step))[x]
    #define Md( y, x ) ((double*)(m + y*step))[x]

    if( mat->width == 2 )
    {
        uchar* m = mat->data.ptr;
        int step = mat->step;

        if( type == CV_32FC1 )
        {
            result = det2(Mf);
        }
        else if( type == CV_64FC1 )
        {
            result = det2(Md);
        }
        else
        {
            CV_ERROR( CV_StsUnsupportedFormat, "" );
        }
    }
    else if( mat->width == 3 )
    {
        uchar* m = mat->data.ptr;
        int step = mat->step;
        
        if( type == CV_32FC1 )
        {
            result = det3(Mf);
        }
        else if( type == CV_64FC1 )
        {
            result = det3(Md);
        }
        else
        {
            CV_ERROR( CV_StsUnsupportedFormat, "" );
        }
    }
    else if( mat->width == 1 )
    {
        if( type == CV_32FC1 )
        {
            result = mat->data.fl[0];
        }
        else if( type == CV_64FC1 )
        {
            result = mat->data.db[0];
        }
        else
        {
            CV_ERROR( CV_StsUnsupportedFormat, "" );
        }
    }
    else
    {
        CvLUDecompFunc decomp_func;
        CvSize size = icvGetMatSize( mat );
        int buf_size = size.width*size.height*icvPixSize[type];
        CvMat tmat;
        
        if( !lu_inittab )
        {
            icvInitLUTable( &lu_decomp_tab, &lu_back_tab );
            lu_inittab = 1;
        }

        if( CV_ARR_CN( type ) != 1 || CV_ARR_DEPTH( type ) < CV_32F )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        if( size.width <= CV_MAX_LOCAL_MAT_SIZE )
        {
            buffer = (uchar*)alloca( buf_size );
            buffer = (uchar*)icvAlignPtr( buffer, 8 );
            local_alloc = 1;
        }
        else
        {
            CV_CALL( buffer = (uchar*)cvAlloc( buf_size ));
        }

        CV_CALL( cvInitMatHeader( &tmat, size.height, size.width, type, buffer ));
        CV_CALL( cvCopy( mat, &tmat ));
        
        decomp_func = (CvLUDecompFunc)(lu_decomp_tab.fn_2d[CV_ARR_DEPTH(type)-CV_32F]);
        assert( decomp_func );

        IPPI_CALL( decomp_func( tmat.data.ptr, tmat.step, size, 0, 0, size, &result ));
    }

    #undef Mf
    #undef Md

    icvCheckVector_64f( &result, 1 );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );

    return result;
}



/****************************************************************************************\
*                                     Inverse Matrix                                     *
\****************************************************************************************/

#define Sf( y, x ) ((float*)(srcdata + y*srcstep))[x]
#define Sd( y, x ) ((double*)(srcdata + y*srcstep))[x]
#define Df( y, x ) ((float*)(dstdata + y*dststep))[x]
#define Dd( y, x ) ((double*)(dstdata + y*dststep))[x]

CV_IMPL int
cvInvert( const CvArr* srcarr, CvArr* dstarr )
{
    uchar* buffer = 0;
    int local_alloc = 0;
    bool ok = true;
    
    CV_FUNCNAME( "cvInv" );

    __BEGIN__;

    CvMat sstub, *src = (CvMat*)srcarr;
    CvMat dstub, *dst = (CvMat*)dstarr;
    int type;

    if( !CV_IS_ARR( src ))
    {
        CV_CALL( src = cvGetMat( src, &sstub ));
    }

    if( !CV_IS_ARR( dst ))
    {
        CV_CALL( dst = cvGetMat( dst, &dstub ));
    }

    type = CV_ARR_TYPE( src->type );

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( src->width != src->height )
        CV_ERROR( CV_StsBadSize, "The matrix must be square" );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    if( type != CV_32FC1 && type != CV_64FC1 )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    if( src->width <= 3 )
    {
        uchar* srcdata = src->data.ptr;
        uchar* dstdata = dst->data.ptr;
        int srcstep = src->step;
        int dststep = dst->step;

        if( src->width == 2 )
        {
            if( type == CV_32FC1 )
            {
                double d = det2(Sf);
                if( d != 0. )
                {
                    double t0, t1;
                    d = 1./d;
                    t0 = Sf(0,0)*d;
                    t1 = Sf(1,1)*d;
                    Df(1,1) = (float)t0;
                    Df(0,0) = (float)t1;
                    t0 = -Sf(0,1)*d;
                    t1 = -Sf(1,0)*d;
                    Df(0,1) = (float)t0;
                    Df(1,0) = (float)t1;
                }
                else
                    ok = false;
            }
            else
            {
                double d = det2(Sd);
                if( d != 0. )
                {
                    double t0, t1;
                    d = 1./d;
                    t0 = Sd(0,0)*d;
                    t1 = Sd(1,1)*d;
                    Dd(1,1) = t0;
                    Dd(0,0) = t1;
                    t0 = -Sd(0,1)*d;
                    t1 = -Sd(1,0)*d;
                    Dd(0,1) = t0;
                    Dd(1,0) = t1;
                }
                else
                    ok = false;
            }
        }
        else if( src->width == 3 )
        {
            if( type == CV_32FC1 )
            {
                double d = det3(Sf);
                if( d != 0. )
                {
                    d = 1./d;
                    float t[9];

                    t[0] = (float)((Sf(1,1) * Sf(2,2) - Sf(1,2) * Sf(2,1)) * d);
                    t[1] = (float)((Sf(0,2) * Sf(2,1) - Sf(0,1) * Sf(2,2)) * d);
                    t[2] = (float)((Sf(0,1) * Sf(1,2) - Sf(0,2) * Sf(1,1)) * d);
                                  
                    t[3] = (float)((Sf(1,2) * Sf(2,0) - Sf(1,0) * Sf(2,2)) * d);
                    t[4] = (float)((Sf(0,0) * Sf(2,2) - Sf(0,2) * Sf(2,0)) * d);
                    t[5] = (float)((Sf(0,2) * Sf(1,0) - Sf(0,0) * Sf(1,2)) * d);
                                  
                    t[6] = (float)((Sf(1,0) * Sf(2,1) - Sf(1,1) * Sf(2,0)) * d);
                    t[7] = (float)((Sf(0,1) * Sf(2,0) - Sf(0,0) * Sf(2,1)) * d);
                    t[8] = (float)((Sf(0,0) * Sf(1,1) - Sf(0,1) * Sf(1,0)) * d);

                    Df(0,0) = t[0]; Df(0,1) = t[1]; Df(0,2) = t[2];
                    Df(1,0) = t[3]; Df(1,1) = t[4]; Df(1,2) = t[5];
                    Df(2,0) = t[6]; Df(2,1) = t[7]; Df(2,2) = t[8];
                }
                else
                    ok = false;
            }
            else
            {
                double d = det3(Sd);
                if( d != 0. )
                {
                    double t[9];

                    d = 1./d;
                    t[0] = (float)((Sd(1,1) * Sd(2,2) - Sd(1,2) * Sd(2,1)) * d);
                    t[1] = (float)((Sd(0,2) * Sd(2,1) - Sd(0,1) * Sd(2,2)) * d);
                    t[2] = (float)((Sd(0,1) * Sd(1,2) - Sd(0,2) * Sd(1,1)) * d);
                                  
                    t[3] = (float)((Sd(1,2) * Sd(2,0) - Sd(1,0) * Sd(2,2)) * d);
                    t[4] = (float)((Sd(0,0) * Sd(2,2) - Sd(0,2) * Sd(2,0)) * d);
                    t[5] = (float)((Sd(0,2) * Sd(1,0) - Sd(0,0) * Sd(1,2)) * d);
                                  
                    t[6] = (float)((Sd(1,0) * Sd(2,1) - Sd(1,1) * Sd(2,0)) * d);
                    t[7] = (float)((Sd(0,1) * Sd(2,0) - Sd(0,0) * Sd(2,1)) * d);
                    t[8] = (float)((Sd(0,0) * Sd(1,1) - Sd(0,1) * Sd(1,0)) * d);

                    Dd(0,0) = t[0]; Dd(0,1) = t[1]; Dd(0,2) = t[2];
                    Dd(1,0) = t[3]; Dd(1,1) = t[4]; Dd(1,2) = t[5];
                    Dd(2,0) = t[6]; Dd(2,1) = t[7]; Dd(2,2) = t[8];
                }
                else
                    ok = false;
            }
        }
        else
        {
            assert( src->width == 1 );

            if( type == CV_32FC1 )
            {
                double d = Sf(0,0);
                if( d != 0. )
                    Df(0,0) = (float)(1./d);
                else
                    ok = false;
            }
            else
            {
                double d = Sd(0,0);
                if( d != 0. )
                    Dd(0,0) = 1./d;
                else
                    ok = false;
            }
        }
    }
    else
    {
        CvLUDecompFunc decomp_func;
        CvLUBackFunc back_func;
        CvSize size = icvGetMatSize( src );
        int buf_size = size.width*size.height*icvPixSize[type];
        double d = 0;
        CvMat tmat;
        
        if( !lu_inittab )
        {
            icvInitLUTable( &lu_decomp_tab, &lu_back_tab );
            lu_inittab = 1;
        }

        if( size.width <= CV_MAX_LOCAL_MAT_SIZE )
        {
            buffer = (uchar*)alloca( buf_size );
            buffer = (uchar*)icvAlignPtr( buffer, 8 );
            local_alloc = 1;
        }
        else
        {
            CV_CALL( buffer = (uchar*)cvAlloc( buf_size ));
        }

        CV_CALL( cvInitMatHeader( &tmat, size.height, size.width, type, buffer ));
        CV_CALL( cvCopy( src, &tmat ));
        CV_CALL( cvSetIdentity( dst ));

        decomp_func = (CvLUDecompFunc)(lu_decomp_tab.fn_2d[CV_ARR_DEPTH(type)-CV_32F]);
        back_func = (CvLUBackFunc)(lu_back_tab.fn_2d[CV_ARR_DEPTH(type)-CV_32F]);
        assert( decomp_func && back_func );

        IPPI_CALL( decomp_func( tmat.data.ptr, tmat.step, size,
                                dst->data.ptr, dst->step, size, &d ));

        if( d != 0 )
        {
            IPPI_CALL( back_func( tmat.data.ptr, tmat.step, size,
                                  dst->data.ptr, dst->step, size ));
        }
        else
            ok = false;
    }

    if( !ok )
        CV_CALL( cvSetZero( dst ));

    CV_CHECK_NANS( dst );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );

    return ok;
}


IPCVAPI_IMPL( CvStatus, icvInvertMatrix_32f, ( const float* src, int w, float* dst ))
{
    CvMat tsrc, tdst;

    cvInitMatHeader( &tsrc, w, w, CV_32FC1, (void*)src );
    cvInitMatHeader( &tdst, w, w, CV_32FC1, dst );
    cvInv( &tsrc, &tdst );

    return CV_OK;
}


IPCVAPI_IMPL( CvStatus, icvInvertMatrix_64d, ( const double* src, int w, double* dst ))
{
    CvMat tsrc, tdst;

    cvInitMatHeader( &tsrc, w, w, CV_64FC1, (void*)src );
    cvInitMatHeader( &tdst, w, w, CV_64FC1, dst );
    cvInv( &tsrc, &tdst );

    return CV_OK;
}


/****************************************************************************************\
*                                  Solving Linear Systems                                *
\****************************************************************************************/

CV_IMPL int
cvSolve( const CvArr* A, const CvArr* b, CvArr* x )
{
    uchar* buffer = 0;
    int local_alloc = 0;
    bool ok = true;
    
    CV_FUNCNAME( "cvInv" );

    __BEGIN__;

    CvMat sstub, *src = (CvMat*)A;
    CvMat dstub, *dst = (CvMat*)x;
    CvMat bstub, *src2 = (CvMat*)b;
    int type;

    if( !CV_IS_ARR( src ))
    {
        CV_CALL( src = cvGetMat( src, &sstub ));
    }

    if( !CV_IS_ARR( src2 ))
    {
        CV_CALL( src2 = cvGetMat( src2, &bstub ));
    }

    if( !CV_IS_ARR( dst ))
    {
        CV_CALL( dst = cvGetMat( dst, &dstub ));
    }

    type = CV_ARR_TYPE( src->type );

    if( !CV_ARE_TYPES_EQ( src, dst ) || !CV_ARE_TYPES_EQ( src, src2 ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( src->width != src->height )
        CV_ERROR( CV_StsBadSize, "The matrix must be square" );

    if( !CV_ARE_SIZES_EQ( src2, dst ) || src->width != src2->height )
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    if( type != CV_32FC1 && type != CV_64FC1 )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    // check case of a single equation and small matrix
    if( src->width <= 3 && src2->width == 1 )
    {
        #define bf(y) ((float*)(srcdata + y*srcstep))[0]
        #define bd(y) ((double*)(srcdata + y*srcstep))[0]

        uchar* srcdata = src->data.ptr;
        uchar* dstdata = dst->data.ptr;
        int srcstep = src->step;
        int dststep = dst->step;

        if( src->width == 2 )
        {
            if( type == CV_32FC1 )
            {
                double d = det2(Sf);
                if( d != 0. )
                {
                    float t;
                    d = 1./d;
                    t = (float)((bf(0)*Sf(1,1) - bf(1)*Sf(0,1))*d);
                    Df(0,1) = (float)((bf(1)*Sf(0,0) - bf(0)*Sf(1,0))*d);
                    Df(0,0) = t;
                }
                else
                    ok = false;
            }
            else
            {
                double d = det2(Sd);
                if( d != 0. )
                {
                    double t;
                    d = 1./d;
                    t = (float)((bd(0)*Sd(1,1) - bd(1)*Sd(0,1))*d);
                    Dd(1,0) = (float)((bd(1)*Sd(0,0) - bd(0)*Sd(1,0))*d);
                    Dd(0,0) = t;
                }
                else
                    ok = false;
            }
        }
        else if( src->width == 3 )
        {
            if( type == CV_32FC1 )
            {
                double d = det3(Sf);
                if( d != 0. )
                {
                    float t[3];
                    d = 1./d;

                    t[0] = (float)(d*
                           (bf(0)*(Sf(1,1)*Sf(2,2) - Sf(1,2)*Sf(2,1)) -
                            Sf(0,1)*(bf(1)*Sf(2,2) - Sf(1,2)*bf(2)) +
                            Sf(0,2)*(bf(1)*Sf(2,1) - Sf(1,1)*bf(2))));

                    t[1] = (float)(d*
                           (Sf(0,0)*(bf(1)*Sf(2,2) - Sf(1,2)*bf(2)) -
                            bf(0)*(Sf(1,0)*Sf(2,2) - Sf(1,2)*Sf(2,0)) +
                            Sf(0,2)*(Sf(1,0)*bf(2) - bf(1)*Sf(2,0))));

                    t[2] = (float)(d*
                           (Sf(0,0)*(Sf(1,1)*bf(2) - bf(1)*Sf(2,1)) -
                            Sf(0,1)*(Sf(1,0)*bf(2) - bf(1)*Sf(2,0)) +
                            bf(0)*(Sf(1,0)*Sf(2,1) - Sf(1,1)*Sf(2,0))));

                    Df(0,0) = t[0];
                    Df(1,0) = t[1];
                    Df(2,0) = t[2];
                }
                else
                    ok = false;
            }
            else
            {
                double d = det3(Sd);
                if( d != 0. )
                {
                    double t[9];

                    d = 1./d;
                    t[0] = (float)(d*
                           (bd(0)*(Sd(1,1)*Sd(2,2) - Sd(1,2)*Sd(2,1)) -
                            Sd(0,1)*(bd(1)*Sd(2,2) - Sd(1,2)*bd(2)) +
                            Sd(0,2)*(bd(1)*Sd(2,1) - Sd(1,1)*bd(2))));

                    t[1] = (float)(d*
                           (Sd(0,0)*(bd(1)*Sd(2,2) - Sd(1,2)*bd(2)) -
                            bd(0)*(Sd(1,0)*Sd(2,2) - Sd(1,2)*Sd(2,0)) +
                            Sd(0,2)*(Sd(1,0)*bd(2) - bd(1)*Sd(2,0))));

                    t[2] = (float)(d*
                           (Sd(0,0)*(Sd(1,1)*bd(2) - bd(1)*Sd(2,1)) -
                            Sd(0,1)*(Sd(1,0)*bd(2) - bd(1)*Sd(2,0)) +
                            bd(0)*(Sd(1,0)*Sd(2,1) - Sd(1,1)*Sd(2,0))));

                    Dd(0,0) = t[0];
                    Dd(1,0) = t[1];
                    Dd(2,0) = t[2];
                }
                else
                    ok = false;
            }
        }
        else
        {
            assert( src->width == 1 );

            if( type == CV_32FC1 )
            {
                double d = Sf(0,0);
                if( d != 0. )
                    Df(0,0) = (float)(bf(0)/d);
                else
                    ok = false;
            }
            else
            {
                double d = Sd(0,0);
                if( d != 0. )
                    Dd(0,0) = (bd(0)/d);
                else
                    ok = false;
            }
        }
    }
    else
    {
        CvLUDecompFunc decomp_func;
        CvLUBackFunc back_func;
        CvSize size = icvGetMatSize( src );
        CvSize dstsize = icvGetMatSize( dst );
        int buf_size = size.width*size.height*icvPixSize[type];
        double d = 0;
        CvMat tmat;
        
        if( !lu_inittab )
        {
            icvInitLUTable( &lu_decomp_tab, &lu_back_tab );
            lu_inittab = 1;
        }

        if( size.width <= CV_MAX_LOCAL_MAT_SIZE )
        {
            buffer = (uchar*)alloca( buf_size );
            buffer = (uchar*)icvAlignPtr( buffer, 8 );
            local_alloc = 1;
        }
        else
        {
            CV_CALL( buffer = (uchar*)cvAlloc( buf_size ));
        }

        CV_CALL( cvInitMatHeader( &tmat, size.height, size.width, type, buffer ));
        CV_CALL( cvCopy( src, &tmat ));
        
        if( src2->data.ptr != dst->data.ptr )
        {
            CV_CALL( cvCopy( src2, dst ));
        }

        decomp_func = (CvLUDecompFunc)(lu_decomp_tab.fn_2d[CV_ARR_DEPTH(type)-CV_32F]);
        back_func = (CvLUBackFunc)(lu_back_tab.fn_2d[CV_ARR_DEPTH(type)-CV_32F]);
        assert( decomp_func && back_func );

        IPPI_CALL( decomp_func( tmat.data.ptr, tmat.step, size,
                                dst->data.ptr, dst->step, dstsize, &d ));

        if( d != 0 )
        {
            IPPI_CALL( back_func( tmat.data.ptr, tmat.step, size,
                                  dst->data.ptr, dst->step, dstsize ));
        }
        else
            ok = false;
    }

    if( !ok )
        CV_CALL( cvSetZero( dst ));

    CV_CHECK_NANS( dst );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );

    return ok;
}


#define ICV_DEF_CROSS_PRODUCT_FUNC( flavor, arrtype )                                   \
IPCVAPI_IMPL( CvStatus,                                                                 \
icvCrossProduct2L_##flavor, ( const arrtype* src1, const arrtype* src2, arrtype* dst )) \
{                                                                                       \
    dst[2] = src1[0] * src2[1] - src1[1] * src2[0];                                     \
    dst[0] = src1[1] * src2[2] - src1[2] * src2[1];                                     \
    dst[1] = src1[2] * src2[0] - src1[0] * src2[2];                                     \
                                                                                        \
    return CV_NO_ERR;                                                                   \
}

ICV_DEF_CROSS_PRODUCT_FUNC( 32f, float )
ICV_DEF_CROSS_PRODUCT_FUNC( 64d, double )

CV_IMPL void
cvCrossProduct( const CvArr* srcAarr, const CvArr* srcBarr, CvArr* dstarr )
{
    CV_FUNCNAME( "cvCrossProduct" );
    
    __BEGIN__;

    CvMat stubA, *srcA = (CvMat*)srcAarr;
    CvMat stubB, *srcB = (CvMat*)srcBarr;
    CvMat dstub, *dst = (CvMat*)dstarr;
    int type;

    if( !CV_IS_ARR(srcA))
        CV_CALL( srcA = cvGetMat( srcA, &stubA ));

    type = CV_ARR_TYPE( srcA->type );

    if( !CV_IS_ARR_CONT(srcA->type) || srcA->width*srcA->height*CV_ARR_CN(type) != 3 )
        CV_ERROR( CV_StsBadArg, "All the input arrays must be continuous 3-vectors" );

    if( !srcB || !dst )
        CV_ERROR( CV_StsNullPtr, "" );

    if( srcA->type == srcB->type && srcA->type == dst->type )
    {
        if( !srcB->data.ptr || !dst->data.ptr )
            CV_ERROR( CV_StsNullPtr, "" );
    }
    else
    {
        if( !CV_IS_ARR(srcB))
            CV_CALL( srcB = cvGetMat( srcB, &stubB ));

        if( !CV_IS_ARR(dst))
            CV_CALL( dst = cvGetMat( dst, &dstub ));

        if( !CV_ARE_TYPES_EQ( srcA, srcB ) ||
            !CV_ARE_TYPES_EQ( srcB, dst ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( !CV_IS_ARR_CONT( srcB->type & dst->type ))
            CV_ERROR( CV_StsBadArg, "All the input arrays must be continuous 3-vectors" );
    }

    if( !CV_ARE_SIZES_EQ( srcA, srcB ) || !CV_ARE_SIZES_EQ( srcB, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    if( CV_ARR_DEPTH(type) == CV_32F )
    {
        float* dstdata = (float*)(dst->data.ptr);
        const float* src1data = (float*)(srcA->data.ptr);
        const float* src2data = (float*)(srcB->data.ptr);
        
        dstdata[2] = src1data[0] * src2data[1] - src1data[1] * src2data[0];
        dstdata[0] = src1data[1] * src2data[2] - src1data[2] * src2data[1];
        dstdata[1] = src1data[2] * src2data[0] - src1data[0] * src2data[2];
    }
    else if( CV_ARR_DEPTH(type) == CV_64F )
    {
        double* dstdata = (double*)(dst->data.ptr);
        const double* src1data = (double*)(srcA->data.ptr);
        const double* src2data = (double*)(srcB->data.ptr);
        
        dstdata[2] = src1data[0] * src2data[1] - src1data[1] * src2data[0];
        dstdata[0] = src1data[1] * src2data[2] - src1data[2] * src2data[1];
        dstdata[1] = src1data[2] * src2data[0] - src1data[0] * src2data[2];
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "" );
    }

    CV_CHECK_NANS( srcA );
    CV_CHECK_NANS( srcB );
    CV_CHECK_NANS( dst );

    __END__;
}


CV_IMPL void
cvRodrigues( CvMat* mat, CvMat* vec, CvMat* jacobian,
             CvRodriguesType convType )
{
    CV_FUNCNAME( "cvRodrigues" );

    __BEGIN__;

    if( !CV_IS_ARR( mat ) || !CV_IS_ARR( vec ))
        CV_ERROR( CV_StsBadArg, "" );

    if( !CV_ARE_DEPTHS_EQ( mat, vec ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( mat->width != 3 || mat->height != 3 )
        CV_ERROR( CV_StsBadSize, "" );

    if( vec->width*vec->height*CV_ARR_CN(vec->type) != 3 )
        CV_ERROR( CV_StsBadSize, "" );

    if( !CV_IS_ARR_CONT( mat->type & vec->type ))
        CV_ERROR( CV_BadStep, "All the input/output arrays must be conitnuous" );

    if( jacobian )
    {
        if( !CV_IS_ARR( jacobian ))
            CV_ERROR( CV_StsBadArg, "" );

        if( !CV_ARE_TYPES_EQ( mat, jacobian ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( jacobian->width != 9 || jacobian->height != 3 )
            CV_ERROR( CV_StsBadSize, "" );

        if( !CV_IS_ARR_CONT( jacobian->type ))
            CV_ERROR( CV_BadStep, "All the input/output arrays must be conitnuous" );
    }

    if( CV_ARR_TYPE( mat->type ) == CV_64FC1 )
    {
        IPPI_CALL( icvRodrigues_64d( mat->data.db, vec->data.db,
                                     jacobian ? jacobian->data.db : 0, convType ));
    }
    else if( CV_ARR_TYPE( mat->type ) == CV_32FC1 )
    {
        IPPI_CALL( icvRodrigues( mat->data.fl, vec->data.fl,
                                 jacobian ? jacobian->data.fl : 0, convType ));
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "" );
    }

    CV_CHECK_NANS( mat );
    CV_CHECK_NANS( vec );
    
#ifdef  CV_CHECK_FOR_NANS    
    if( jacobian )
        CV_CHECK_NANS( jacobian );
#endif

    __END__;
}

/* End of file. */
