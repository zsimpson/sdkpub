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

#include <math.h>
#include "_cv.h"
#include "_cvwrap.h"


/////////////////////////////// Functions Declaration ////////////////////////////////////

#define IPCV_MATMULADD( flavor, arrtype )                                               \
IPCVAPI( CvStatus,                                                                      \
icvMatMulAdd_##flavor,( const arrtype* src1, int step1, const arrtype* src2, int step2, \
                        const arrtype* src3, int step3, arrtype* dst, int dststep,      \
                        CvSize srcsize, CvSize dstsize ))


IPCV_MATMULADD( 32f_C1R, float )
IPCV_MATMULADD( 32f_C2R, float )
IPCV_MATMULADD( 64f_C1R, double )
IPCV_MATMULADD( 64f_C2R, double )


#undef IPCV_MATMULADD

#define IPCV_MATMULADD_CONST( flavor, arrtype, scalartype )                         \
IPCVAPI( CvStatus,                                                                  \
icvMatMulAddC_##flavor,( const arrtype* src, int step, arrtype* dst, int dststep,   \
                        CvSize size, const scalartype* mat ))

IPCV_MATMULADD_CONST( 8u_C2R, uchar, double )
IPCV_MATMULADD_CONST( 8u_C3R, uchar, double )
IPCV_MATMULADD_CONST( 8u_C4R, uchar, double )

IPCV_MATMULADD_CONST( 32s_C2R, int, double )
IPCV_MATMULADD_CONST( 32s_C3R, int, double )
IPCV_MATMULADD_CONST( 32s_C4R, int, double )

IPCV_MATMULADD_CONST( 32f_C2R, float, double )
IPCV_MATMULADD_CONST( 32f_C3R, float, double )
IPCV_MATMULADD_CONST( 32f_C4R, float, double )

IPCV_MATMULADD_CONST( 64f_C2R, double, double )
IPCV_MATMULADD_CONST( 64f_C3R, double, double )
IPCV_MATMULADD_CONST( 64f_C4R, double, double )

#undef IPCV_MATMULADD_CONST


#define IPCV_MULADD_CONST( flavor, arrtype, scalartype )                                \
IPCVAPI( CvStatus,                                                                      \
icvMulAddC_##flavor,( const arrtype* src1, int step1, const arrtype* src2, int step2,   \
                      arrtype* dst, int dststep, CvSize size, const scalartype* val ))

IPCV_MULADD_CONST( 32f_C1R, float, double )
IPCV_MULADD_CONST( 32f_C2R, float, double )
IPCV_MULADD_CONST( 64f_C1R, double, double )
IPCV_MULADD_CONST( 64f_C2R, double, double )

#undef IPCV_MULADD_CONST

/****************************************************************************************\
*                                        cvMatMulAdd                                     *
\****************************************************************************************/

#define _load_real_( temp, ptr, k )   \
    ((temp)[0] = (ptr) ? (ptr)[k] : 0)

#define _load_complex_( temp, ptr, k )\
    ((temp)[0] = (ptr) ? (ptr)[k] : 0, (temp)[1] = (ptr) ? (ptr)[(k)+1] : 0)

#define _mul_add_real_( a, b, s ) \
    ((s)[0] += (a)[0]*(b)[0])

#define _mul_add_complex_( a, b, s )            \
    ((s)[0] += (a)[0]*(b)[0] - (a)[1]*(b)[1],   \
    (s)[1] += (a)[0]*(b)[1] + (a)[1]*(b)[0])

#define _store_real_( temp, ptr, arrtype ) \
    ((ptr)[0] = (arrtype)(temp)[0])

#define _store_complex_( temp, ptr, arrtype ) \
    ((ptr)[0] = (arrtype)(temp)[0], (ptr)[1] = (arrtype)(temp)[1])


#define ICV_DEF_MATMULADD_FUNC( flavor, arrtype, temptype,                              \
                                _mul_add_macro_, _load_macro_, _store_macro_, cn )      \
IPCVAPI_IMPL( CvStatus,                                                                 \
icvMatMulAdd_##flavor,( const arrtype* src1, int step1, const arrtype* src2, int step2, \
                        const arrtype* src3, int step3, arrtype* dst, int step,         \
                        CvSize srcsize, CvSize dstsize ))                               \
{                                                                                       \
    for( ; dstsize.height--; (char*&)src1 += step1, (char*&)src3 += step3,              \
                             (char*&)dst += step )                                      \
    {                                                                                   \
        int i, j;                                                                       \
        for( i = 0; i < dstsize.width; i++ )                                            \
        {                                                                               \
            temptype sum[cn];                                                           \
            const arrtype* src2t = src2 + i*(cn);                                       \
                                                                                        \
            _load_macro_( sum, src3, i*(cn) );                                          \
                                                                                        \
            for( j = 0; j < srcsize.width; j++, (char*&)src2t += step2 )                \
            {                                                                           \
                _mul_add_macro_( (src1 + j*(cn)), src2t, sum );                         \
            }                                                                           \
                                                                                        \
            _store_macro_( sum, dst + i*(cn), arrtype );                                \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    return CV_OK;                                                                       \
}


ICV_DEF_MATMULADD_FUNC( 32f_C1R, float, double, _mul_add_real_,
                        _load_real_, _store_real_, 1)
ICV_DEF_MATMULADD_FUNC( 64f_C1R, double, double, _mul_add_real_,
                        _load_real_,_store_real_, 1)
ICV_DEF_MATMULADD_FUNC( 32f_C2R, float, double, _mul_add_real_,
                        _load_real_, _store_real_, 2)
ICV_DEF_MATMULADD_FUNC( 64f_C2R, double, double, _mul_add_complex_,
                        _load_complex_, _store_complex_, 2 )


typedef CvStatus (CV_STDCALL *CvMatMulAddFunc)( const void* src1, int step1,
                   const void* src2, int step2, const void* src3, int step3,
                   void* dst, int dststep, CvSize srcsize, CvSize dstsize );


#define ICV_DEF_INIT_MATMULADD_TAB( FUNCNAME )              \
static void icvInitMatMulAddTable( CvBigFuncTable* table )  \
{                                                           \
    table->fn_2d[CV_32FC1] = (void*)icv##FUNCNAME##_32f_C1R;\
    table->fn_2d[CV_32FC2] = (void*)icv##FUNCNAME##_32f_C2R;\
                                                            \
    table->fn_2d[CV_64FC1] = (void*)icv##FUNCNAME##_64f_C1R;\
    table->fn_2d[CV_64FC2] = (void*)icv##FUNCNAME##_64f_C2R;\
}


ICV_DEF_INIT_MATMULADD_TAB( MatMulAdd )


CV_IMPL  void
cvMatMulAdd( const CvArr* src1arr, const CvArr* src2arr,
             const CvArr* src3arr, CvArr* dstarr )
{
    static CvBigFuncTable mmuladd_tab;
    static int inittab = 0;
    
    uchar* buffer = 0;
    int local_alloc = 0;
    
    CV_FUNCNAME( "cvMatMulAdd" );

    __BEGIN__;

    CvMat stub1, *src1 = (CvMat*)src1arr;
    CvMat stub2, *src2 = (CvMat*)src2arr;
    CvMat stub3, *src3 = (CvMat*)src3arr;
    CvMat stub, *dst = (CvMat*)dstarr;
    int type;

    if( !CV_IS_ARR( src1 ))
    {
        int coi = 0;
        CV_CALL( src1 = cvGetMat( src1, &stub1, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR( src2 ))
    {
        int coi = 0;
        CV_CALL( src2 = cvGetMat( src2, &stub2, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR( dst ))
    {
        int coi = 0;
        CV_CALL( dst = cvGetMat( dst, &stub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( src3 )
    {
        if( !CV_IS_ARR( src3 ))
        {
            int coi = 0;
            CV_CALL( src3 = cvGetMat( src3, &stub3, &coi ));

            if( coi != 0 )
                CV_ERROR( CV_BadCOI, "" );
        }

        if( !CV_ARE_TYPES_EQ( src3, dst ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( !CV_ARE_SIZES_EQ( src3, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );
    }
    else
    {
        src3 = &stub3;
        src3->data.ptr = 0;
        src3->step = 0;
        src3->type = CV_ARR_CONT_FLAG;
    }

    if( !CV_ARE_TYPES_EQ( src1, src2 ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( !CV_ARE_TYPES_EQ( src1, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( src1->width != src2->height ||
        src1->height != dst->height ||
        src2->width != dst->width )
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_ARR_TYPE( src1->type );

    // check case of a single equation and small matrix
    if( src2->width == 1 && src1->width <= 3 && src1->width == src1->height &&
        CV_IS_ARR_CONT( src1->type & src2->type & src3->type & dst->type ))
    {
        uchar* data1 = src1->data.ptr;
        uchar* data2 = src2->data.ptr;
        uchar* data3 = src3->data.ptr;
        uchar* datad = dst->data.ptr;

        #undef A
        #undef X
        #undef B
        #undef Y
        #undef N
        #undef arrtype
        #define A(y,x)  ((arrtype*)data1)[(x)+(y)*N]
        #define X(y)    ((arrtype*)data2)[y]
        #define B(y)    ((arrtype*)data3)[y]
        #define Y(y)    ((arrtype*)datad)[y]

        if( type == CV_32FC1 )
        {
            if( src1->width == 2 )
            {
                #undef N
                #define N  2

                #undef arrtype                
                #define arrtype float

                float t[2];

                if( data3 )
                {
                    t[0] = (float)(A(0,0)*X(0) + A(0,1)*X(1) + B(0));
                    t[1] = (float)(A(1,0)*X(0) + A(1,1)*X(1) + B(1));
                }
                else
                {
                    t[0] = (float)(A(0,0)*X(0) + A(0,1)*X(1));
                    t[1] = (float)(A(1,0)*X(0) + A(1,1)*X(1));
                }

                Y(0) = t[0];
                Y(1) = t[1];
            }
            else if( src1->width == 3 )
            {
                #undef N
                #define N  3

                float t[3];

                if( data3 )
                {
                    t[0] = (float)(A(0,0)*X(0) + A(0,1)*X(1) + A(0,2)*X(2) + B(0));
                    t[1] = (float)(A(1,0)*X(0) + A(1,1)*X(1) + A(1,2)*X(2) + B(1));
                    t[2] = (float)(A(2,0)*X(0) + A(2,1)*X(1) + A(2,2)*X(2) + B(2));
                }
                else
                {
                    t[0] = (float)(A(0,0)*X(0) + A(0,1)*X(1) + A(0,2)*X(2));
                    t[1] = (float)(A(1,0)*X(0) + A(1,1)*X(1) + A(1,2)*X(2));
                    t[2] = (float)(A(2,0)*X(0) + A(2,1)*X(1) + A(2,2)*X(2));
                }

                Y(0) = t[0];
                Y(1) = t[1];
                Y(2) = t[2];
            }
            else
            {
                Y(0) = data3 ? (float)(A(0,0)*X(0) + B(0)) : (float)(A(0,0)*X(0));
            }
            EXIT;
        }
        
        if( type == CV_64FC1 )
        {
            if( src1->width == 2 )
            {
                #undef N
                #define N  2

                #undef arrtype                
                #define arrtype double

                double t[2];

                if( data3 )
                {
                    t[0] = A(0,0)*X(0) + A(0,1)*X(1) + B(0);
                    t[1] = A(1,0)*X(0) + A(1,1)*X(1) + B(1);
                }
                else
                {
                    t[0] = A(0,0)*X(0) + A(0,1)*X(1);
                    t[1] = A(1,0)*X(0) + A(1,1)*X(1);
                }

                Y(0) = t[0];
                Y(1) = t[1];
            }
            else if( src1->width == 3 )
            {
                #undef N
                #define N  3

                double t[3];

                if( data3 )
                {
                    t[0] = A(0,0)*X(0) + A(0,1)*X(1) + A(0,2)*X(2) + B(0);
                    t[1] = A(1,0)*X(0) + A(1,1)*X(1) + A(1,2)*X(2) + B(1);
                    t[2] = A(2,0)*X(0) + A(2,1)*X(1) + A(2,2)*X(2) + B(2);
                }
                else
                {
                    t[0] = A(0,0)*X(0) + A(0,1)*X(1) + A(0,2)*X(2);
                    t[1] = A(1,0)*X(0) + A(1,1)*X(1) + A(1,2)*X(2);
                    t[2] = A(2,0)*X(0) + A(2,1)*X(1) + A(2,2)*X(2);
                }

                Y(0) = t[0];
                Y(1) = t[1];
                Y(2) = t[2];
            }
            else
            {
                Y(0) = data3 ? A(0,0)*X(0) + B(0) : A(0,0)*X(0);
            }

            EXIT;
        }
    }

    // general case
    {
        CvMatMulAddFunc func;
        CvSize size = icvGetMatSize( src1 );
        CvSize dstsize = icvGetMatSize( dst );
        int buf_size = dstsize.width*dstsize.height*icvPixSize[type];
        CvMat tmat, *tdst = dst;
        
        if( !inittab )
        {
            icvInitMatMulAddTable( &mmuladd_tab );
            inittab = 1;
        }

        if( dst->data.ptr == src1->data.ptr || dst->data.ptr == src2->data.ptr )
        {
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

            CV_CALL( cvInitMatHeader( &tmat, dstsize.height,
                                      dstsize.width, type, buffer ));
            tdst = &tmat;
        }

        func = (CvMatMulAddFunc)(mmuladd_tab.fn_2d[type]);
        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src1->data.ptr, src1->step, src2->data.ptr, src2->step,
                         src3->data.ptr, src3->step, tdst->data.ptr, tdst->step,
                         size, dstsize ));

        if( tdst != dst )
        {
            CV_CALL( cvCopy( tdst, dst ));
        }
    }

    CV_CHECK_NANS( dst );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );
}


/****************************************************************************************\
*                                        cvMatMulAddS                                    *
\****************************************************************************************/


#define  ICV_DEF_MMULADDC_CASE_C2( arrtype, temptype, src, dst, mat,        \
                                  _cast_macro1_, _cast_macro2_ )            \
{                                                                           \
    temptype t0, t1;                                                        \
                                                                            \
    t0 = _cast_macro1_((mat)[0]*(src)[0] + (mat)[1]*(src)[1] + (mat)[2]);   \
    t1 = _cast_macro1_((mat)[3]*(src)[0] + (mat)[4]*(src)[1] + (mat)[5]);   \
                                                                            \
    (dst)[0] = _cast_macro2_(t0);                                           \
    (dst)[1] = _cast_macro2_(t1);                                           \
}


#define  ICV_DEF_MMULADDC_CASE_C3( arrtype, temptype, src, dst, mat,        \
                                  _cast_macro1_, _cast_macro2_ )            \
{                                                                           \
    temptype t0, t1, t2;                                                    \
                                                                            \
    t0 = _cast_macro1_((mat)[0]*(src)[0] + (mat)[1]*(src)[1] +              \
                       (mat)[2]*(src)[2] + (mat)[3]);                       \
    t1 = _cast_macro1_((mat)[4]*(src)[0] + (mat)[5]*(src)[1] +              \
                       (mat)[6]*(src)[2] + (mat)[7]);                       \
    t2 = _cast_macro1_((mat)[8]*(src)[0] + (mat)[9]*(src)[1] +              \
                       (mat)[10]*(src)[2] + (mat)[11]);                     \
                                                                            \
    (dst)[0] = _cast_macro2_(t0);                                           \
    (dst)[1] = _cast_macro2_(t1);                                           \
    (dst)[2] = _cast_macro2_(t2);                                           \
}


#define  ICV_DEF_MMULADDC_CASE_C4( arrtype, temptype, src, dst, mat,        \
                                  _cast_macro1_, _cast_macro2_ )            \
{                                                                           \
    temptype t0, t1, t2, t3;                                                \
                                                                            \
    t0 = _cast_macro1_((mat)[0]*(src)[0] + (mat)[1]*(src)[1] +              \
                       (mat)[2]*(src)[2] + (mat)[3]*(src)[3] + (mat)[4]);   \
    t1 = _cast_macro1_((mat)[5]*(src)[0] + (mat)[6]*(src)[1] +              \
                       (mat)[7]*(src)[2] + (mat)[8]*(src)[3] + (mat)[9]);   \
    t2 = _cast_macro1_((mat)[10]*(src)[0] + (mat)[11]*(src)[1] +            \
                       (mat)[12]*(src)[2] + (mat)[13]*(src)[3] + (mat)[14]);\
    t3 = _cast_macro1_((mat)[15]*(src)[0] + (mat)[16]*(src)[1] +            \
                       (mat)[17]*(src)[2] + (mat)[18]*(src)[3] + (mat)[19]);\
                                                                            \
    (dst)[0] = _cast_macro2_(t0);                                           \
    (dst)[1] = _cast_macro2_(t1);                                           \
    (dst)[2] = _cast_macro2_(t2);                                           \
    (dst)[3] = _cast_macro2_(t3);                                           \
}



#define  ICV_DEF_MATMULADDS_FUNC( flavor, arrtype, scalartype, temptype,    \
                                  _cast_macro1_, _cast_macro2_, cn  )       \
IPCVAPI_IMPL( CvStatus,                                                     \
icvMatMulAddC_##flavor,( const arrtype* src, int srcstep,                   \
                         arrtype* dst, int dststep, CvSize size,            \
                         const scalartype* mat ))                           \
{                                                                           \
    size.width *= (cn);                                                     \
                                                                            \
    for( ; size.height--; (char*&)src += srcstep, (char*&)dst += dststep )  \
    {                                                                       \
        int i;                                                              \
        for( i = 0; i < size.width; i += (cn) )                             \
        {                                                                   \
            ICV_DEF_MMULADDC_CASE_C##cn( arrtype, temptype, src + i,        \
                         dst + i, mat, _cast_macro1_, _cast_macro2_ )       \
        }                                                                   \
    }                                                                       \
                                                                            \
    return CV_OK;                                                           \
}


ICV_DEF_MATMULADDS_FUNC( 8u_C2R, uchar, double, int, cvRound, CV_CAST_8U, 2 )
ICV_DEF_MATMULADDS_FUNC( 8u_C3R, uchar, double, int, cvRound, CV_CAST_8U, 3 )
ICV_DEF_MATMULADDS_FUNC( 8u_C4R, uchar, double, int, cvRound, CV_CAST_8U, 4 )

ICV_DEF_MATMULADDS_FUNC( 32s_C2R, int, double, int, cvRound, CV_NOP, 2 )
ICV_DEF_MATMULADDS_FUNC( 32s_C3R, int, double, int, cvRound, CV_NOP, 3 )
ICV_DEF_MATMULADDS_FUNC( 32s_C4R, int, double, int, cvRound, CV_NOP, 4 )

ICV_DEF_MATMULADDS_FUNC( 32f_C2R, float, double, double, CV_NOP, CV_CAST_32F, 2 )
ICV_DEF_MATMULADDS_FUNC( 32f_C3R, float, double, double, CV_NOP, CV_CAST_32F, 3 )
ICV_DEF_MATMULADDS_FUNC( 32f_C4R, float, double, double, CV_NOP, CV_CAST_32F, 4 )

ICV_DEF_MATMULADDS_FUNC( 64f_C2R, double, double, double, CV_NOP, CV_CAST_64F, 2 )
ICV_DEF_MATMULADDS_FUNC( 64f_C3R, double, double, double, CV_NOP, CV_CAST_64F, 3 )
ICV_DEF_MATMULADDS_FUNC( 64f_C4R, double, double, double, CV_NOP, CV_CAST_64F, 4 )


static void
icvInitMatMulAddCTable( CvBigFuncTable* tab )
{
    tab->fn_2d[CV_8UC2] = (void*)icvMatMulAddC_8u_C2R;
    tab->fn_2d[CV_8UC3] = (void*)icvMatMulAddC_8u_C3R;
    tab->fn_2d[CV_8UC4] = (void*)icvMatMulAddC_8u_C4R;

    tab->fn_2d[CV_32SC2] = (void*)icvMatMulAddC_32s_C2R;
    tab->fn_2d[CV_32SC3] = (void*)icvMatMulAddC_32s_C3R;
    tab->fn_2d[CV_32SC4] = (void*)icvMatMulAddC_32s_C4R;

    tab->fn_2d[CV_32FC2] = (void*)icvMatMulAddC_32f_C2R;
    tab->fn_2d[CV_32FC3] = (void*)icvMatMulAddC_32f_C3R;
    tab->fn_2d[CV_32FC4] = (void*)icvMatMulAddC_32f_C4R;

    tab->fn_2d[CV_64FC2] = (void*)icvMatMulAddC_64f_C2R;
    tab->fn_2d[CV_64FC3] = (void*)icvMatMulAddC_64f_C3R;
    tab->fn_2d[CV_64FC4] = (void*)icvMatMulAddC_64f_C4R;
}


CV_IMPL void
cvMatMulAddS( const CvArr* srcarr, CvArr* dstarr,
              const CvArr* transform, const CvArr* shiftvec )
{
    static CvBigFuncTable mmuladds_tab;
    static int inittab = 0;
    
    double buffer[20];
    
    CV_FUNCNAME( "cvMatMulAddS" );

    __BEGIN__;

    CvMat stub1, *src = (CvMat*)srcarr;
    CvMat stub, *dst = (CvMat*)dstarr;
    CvMat rstub, *rot = (CvMat*)transform;
    CvMat sstub, *shift = (CvMat*)shiftvec;
    int i, j, type, cn;

    if( !inittab )
    {
        icvInitMatMulAddCTable( &mmuladds_tab );
        inittab = 1;
    }

    if( !CV_IS_ARR( src ))
    {
        int coi = 0;
        CV_CALL( src = cvGetMat( src, &stub1, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR( dst ))
    {
        int coi = 0;
        CV_CALL( dst = cvGetMat( dst, &stub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_ARR_TYPE( src->type );
    cn = CV_ARR_CN( type );

    if( !CV_IS_ARR( rot ))
    {
        int coi = 0;
        CV_CALL( rot = cvGetMat( rot, &rstub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( rot->height != cn )
        CV_ERROR( CV_StsBadSize,
        "The height of transform matrix must be equal to number of channels" );

    if( rot->width == cn + 1 || rot->width == cn )
    {
        if( CV_ARR_TYPE( rot->type ) == CV_64FC1 )
        {
            for( i = 0; i < cn; i++ )
            {
                buffer[i*cn + cn-1] = 0;

                for( j = 0; j < rot->width; j++ )
                    buffer[i*cn + j] = ((double*)(rot->data.ptr + rot->step*i))[j];
            }
        }
        else if( CV_ARR_TYPE( rot->type ) == CV_32FC1 )
        {
            for( i = 0; i < cn; i++ )
            {
                buffer[i*cn + cn-1] = 0;

                for( j = 0; j < rot->width; j++ )
                    buffer[i*cn + j] = ((float*)(rot->data.ptr + rot->step*i))[j];
            }
        }
        else
        {
            CV_ERROR( CV_StsUnsupportedFormat, "Rotation matrix must be 32fC1 or 64fC1" );
        }
    }
    else
    {
        CV_ERROR( CV_StsUnmatchedSizes, "If the source array has <cn> channels, "
           "the transformation matrix must have <cn> x <cn>+1 or <cn> x <cn> size" );
    }

    if( shift )
    {
        if( !CV_IS_ARR( shift ))
        {
            int coi = 0;
            CV_CALL( shift = cvGetMat( shift, &sstub, &coi ));

            if( coi != 0 )
                CV_ERROR( CV_BadCOI, "" );
        }

        if( shift->height == 1 && (CV_ARR_CN( shift->type ) != 1 ||
            CV_ARR_CN( shift->type ) * shift->width == cn) )
        {
            if( CV_ARR_DEPTH( shift->type ) == CV_64F )
            {
                for( i = 0; i < cn; i++ )
                    buffer[i*cn + cn-1] += shift->data.db[i];
            }
            else if( CV_ARR_DEPTH( shift->type ) == CV_32F )
            {
                for( i = 0; i < cn; i++ )
                    buffer[i*cn + cn-1] += shift->data.fl[i];
            }
            else
            {
                CV_ERROR( CV_StsUnsupportedFormat,
                    "Shift vector must be 32f or 64f" );
            }
        }
        else if( CV_ARR_CN( shift->type ) == 1 && shift->height == cn )
        {
            if( CV_ARR_DEPTH( shift->type ) == CV_64F )
            {
                for( i = 0; i < cn; i++ )
                    buffer[i*cn + cn-1] += *(double*)(shift->data.ptr + shift->step*i);
            }
            if( CV_ARR_DEPTH( shift->type ) == CV_32F )
            {
                for( i = 0; i < cn; i++ )
                    buffer[i*cn + cn-1] += *(float*)(shift->data.ptr + shift->step*i);
            }
            else
            {
                CV_ERROR( CV_StsUnsupportedFormat,
                    "Shift vector must be 32f or 64f" );
            }
        }
        else
        {
            CV_ERROR( CV_StsUnmatchedSizes,
                "Shift (if present) must have a total length equal to number "
                "of channels in the processed arrays" );
        }
    }

    if( cn > 1 )
    {
        CvFunc2D_2A1P func = (CvFunc2D_2A1P)(mmuladds_tab.fn_2d[type]);
        CvSize size = icvGetMatSize( src );

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        if( CV_IS_ARR_CONT( src->type & dst->type ))
        {
            size.width *= size.height;
            size.height = 1;
        }

        CV_CALL( func( src->data.ptr, src->step, dst->data.ptr, dst->step, size, buffer));
    }
    else // the simplest variant
    {
        CV_CALL( cvCvtScale( src, dst, buffer[0], buffer[1] ));
    }

    CV_CHECK_NANS( dst );

    __END__;
}


/****************************************************************************************\
*                                       cvMulAddS                                        *
\****************************************************************************************/

#define  ICV_DEF_MULADDC_CASE_C1( arrtype, temptype, src1, src2, dst, len )     \
{                                                                               \
    int i;                                                                      \
                                                                                \
    for( i = 0; i <= (len) - 4; i += 4 )                                        \
    {                                                                           \
        temptype t0 = (src1)[i]*s0 + (src2)[i];                                 \
        temptype t1 = (src1)[i+1]*s0 + (src2)[i+1];                             \
                                                                                \
        (dst)[i] = (arrtype)t0;                                                 \
        (dst)[i+1] = (arrtype)t1;                                               \
                                                                                \
        t0 = (src1)[i+2]*s0 + (src2)[i+2];                                      \
        t1 = (src1)[i+3]*s0 + (src2)[i+3];                                      \
                                                                                \
        (dst)[i+2] = (arrtype)t0;                                               \
        (dst)[i+3] = (arrtype)t1;                                               \
    }                                                                           \
                                                                                \
    for( ; i < (len); i++ )                                                     \
    {                                                                           \
        temptype t0 = (src1)[i]*s0 + (src2)[i];                                 \
        (dst)[i] = (arrtype)t0;                                                 \
    }                                                                           \
}


#define  ICV_DEF_MULADDC_CASE_C2( arrtype, temptype, src1, src2, dst, len )     \
{                                                                               \
    int i;                                                                      \
                                                                                \
    for( i = 0; i <= (len) - 4; i += 4 )                                        \
    {                                                                           \
        temptype t0 = (src1)[i]*s0 - (src1)[i+1]*s1 + (src2)[i];                \
        temptype t1 = (src1)[i]*s1 + (src1)[i+1]*s0 + (src2)[i+1];              \
                                                                                \
        (dst)[i] = (arrtype)t0;                                                 \
        (dst)[i+1] = (arrtype)t1;                                               \
                                                                                \
        t0 = (src1)[i+2]*s0 - (src1)[i+3]*s1 + (src2)[i+2];                     \
        t1 = (src1)[i+2]*s1 + (src1)[i+3]*s0 + (src2)[i+3];                     \
                                                                                \
        (dst)[i+2] = (arrtype)t0;                                               \
        (dst)[i+3] = (arrtype)t1;                                               \
    }                                                                           \
                                                                                \
    for( ; i < (len); i += 2 )                                                  \
    {                                                                           \
        temptype t0 = (src1)[i]*s0 - (src1)[i+1]*s1 + (src2)[i];                \
        temptype t1 = (src1)[i]*s1 + (src1)[i+1]*s0 + (src2)[i+1];              \
                                                                                \
        (dst)[i] = (arrtype)t0;                                                 \
        (dst)[i+1] = (arrtype)t1;                                               \
    }                                                                           \
}


#define  ICV_DEF_MULADDS_FUNC( flavor, arrtype, scalartype, entry, cn )     \
IPCVAPI_IMPL( CvStatus,                                                     \
icvMulAddC_##flavor,( const arrtype* src1, int srcstep1,                    \
                      const arrtype* src2, int srcstep2,                    \
                      arrtype* dst, int dststep, CvSize size,               \
                      const scalartype* scalar ))                           \
{                                                                           \
    entry(scalartype);                                                      \
    size.width *= (cn);                                                     \
                                                                            \
    for( ; size.height--; (char*&)src1 += srcstep1,                         \
                          (char*&)src2 += srcstep2,                         \
                          (char*&)dst += dststep )                          \
    {                                                                       \
        ICV_DEF_MULADDC_CASE_C##cn( arrtype, scalartype, src1, src2,        \
                                    dst, size.width )                       \
    }                                                                       \
                                                                            \
    return CV_OK;                                                           \
}


ICV_DEF_MULADDS_FUNC( 32f_C1R, float, double, ICV_UN_ENTRY_C1, 1 )
ICV_DEF_MULADDS_FUNC( 32f_C2R, float, double, ICV_UN_ENTRY_C2, 2 )
ICV_DEF_MULADDS_FUNC( 64f_C1R, double, double, ICV_UN_ENTRY_C1, 1 )
ICV_DEF_MULADDS_FUNC( 64f_C2R, double, double, ICV_UN_ENTRY_C2, 2 )


static void
icvInitMulAddCTable( CvBigFuncTable* tab )
{
    tab->fn_2d[CV_32FC1] = (void*)icvMulAddC_32f_C1R;
    tab->fn_2d[CV_32FC2] = (void*)icvMulAddC_32f_C2R;
    tab->fn_2d[CV_64FC1] = (void*)icvMulAddC_64f_C1R;
    tab->fn_2d[CV_64FC2] = (void*)icvMulAddC_64f_C2R;
}


CV_IMPL void
cvScaleAdd( const CvArr* srcarr1, CvScalar scale,
            const CvArr* srcarr2, CvArr* dstarr )
{
    static CvBigFuncTable muladds_tab;
    static int inittab = 0;
    
    CV_FUNCNAME( "cvScaleAdd" );

    __BEGIN__;

    CvMat stub1, *src1 = (CvMat*)srcarr1;
    CvMat stub2, *src2 = (CvMat*)srcarr2;
    CvMat stub, *dst = (CvMat*)dstarr;
    CvSize size;
    int type;

    if( !inittab )
    {
        icvInitMulAddCTable( &muladds_tab );
        inittab = 1;
    }

    if( !CV_IS_ARR( src1 ))
    {
        int coi = 0;
        CV_CALL( src1 = cvGetMat( src1, &stub1, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR( src2 ))
    {
        int coi = 0;
        CV_CALL( src2 = cvGetMat( src2, &stub2, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR( dst ))
    {
        int coi = 0;
        CV_CALL( dst = cvGetMat( dst, &stub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src1, dst ) || !CV_ARE_TYPES_EQ( src2, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( !CV_ARE_SIZES_EQ( src1, dst ) || !CV_ARE_SIZES_EQ( src2, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_ARR_TYPE( src1->type );

    size = icvGetMatSize( src1 );

    if( CV_IS_ARR_CONT( src1->type & src2->type & dst->type ))
    {
        size.width *= size.height;

        if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
        {
            if( type == CV_32FC1 )
            {
                float* mA = src1->data.fl;
                float* mB = src2->data.fl;
                float* mC = dst->data.fl;

                do
                {
                    mC[size.width - 1] = (float)(mA[size.width - 1]*scale.val[0] +
                                         mB[size.width - 1]);
                }
                while( --size.width );

                EXIT;
            }

            if( type == CV_64FC1 )
            {
                double* mA = src1->data.db;
                double* mB = src2->data.db;
                double* mC = dst->data.db;

                do
                {
                    mC[size.width - 1] = mA[size.width - 1]*scale.val[0] +
                                         mB[size.width - 1];
                }
                while( --size.width );

                EXIT;
            }
        }

        size.height = 1;
    }

    {
        CvFunc2D_3A1P func = (CvFunc2D_3A1P)(muladds_tab.fn_2d[type]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src1->data.ptr, src1->step, src2->data.ptr, src2->step,
                         dst->data.ptr, dst->step, size, scale.val ));
    }

    CV_CHECK_NANS( dst );

    __END__;
}


/****************************************************************************************\
*                                        cvMahalanobis                                   *
\****************************************************************************************/

CV_IMPL double
cvMahalanobis( const CvArr* srcAarr, const CvArr* srcB, CvArr* mat )
{
    uchar* buffer = 0;
    int local_alloc = 0;
    double dist = 0;

    CV_FUNCNAME( "cvMahalanobis" );

    __BEGIN__;

    int buf_size, pix_size;
    CvMat stubA, *srcA = (CvMat*)srcAarr;
    CvMat temp1, temp2;

    if( !CV_IS_ARR(srcA) )
        CV_CALL( srcA = cvGetMat( srcA, &stubA ));

    pix_size = icvPixSize[CV_ARR_TYPE(srcA->type)];
    buf_size = srcA->rows*2*pix_size;
    
    if( buf_size <= CV_MAX_LOCAL_SIZE )
    {
        buffer = (uchar*)alloca( buf_size );
        local_alloc = 1;
    }
    else
    {
        CV_CALL( buffer = (uchar*)cvAlloc( buf_size ));
    }

    cvInitMatHeader( &temp1, srcA->rows, 1, srcA->type, buffer );
    cvInitMatHeader( &temp2, srcA->rows, 1, srcA->type, buffer + buf_size/2);

    CV_CALL( cvSub( srcA, srcB, &temp1 ));
    CV_CALL( cvMatMulAdd( mat, &temp1, 0, &temp2 ));
    CV_CALL( dist = sqrt(cvDotProduct( &temp1, &temp2 )));

    icvCheckVector_64f( &dist, 1 );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );

    return  dist;
}


/****************************************************************************************\
*                                        cvMulTransposed                                 *
\****************************************************************************************/

#define ICV_DEF_MULTRANS_R_FUNC( flavor, arrtype )                      \
IPCVAPI_IMPL( CvStatus,                                                 \
icvMulTransposedR_##flavor, ( const arrtype* src, int srcstep,          \
                              arrtype* dst, int dststep, CvSize size )) \
{                                                                       \
    int i, j, k;                                                        \
    arrtype* tdst = dst;                                                \
    arrtype* col_buf = 0;                                               \
    int local_alloc = 0;                                                \
    int buf_size = size.height*sizeof(arrtype);                         \
                                                                        \
    if( buf_size <= CV_MAX_LOCAL_SIZE )                                 \
    {                                                                   \
        col_buf = (arrtype*)alloca( buf_size );                         \
        local_alloc = 1;                                                \
    }                                                                   \
    else                                                                \
    {                                                                   \
        col_buf = (arrtype*)icvAlloc( buf_size );                       \
        if( !col_buf )                                                  \
            return CV_OUTOFMEM_ERR;                                     \
    }                                                                   \
                                                                        \
    for( i = 0; i < size.width; i++, (char*&)tdst += dststep )          \
    {                                                                   \
        /* copy i-th column */                                          \
        for( j = 0; j < size.height; j++ )                              \
            col_buf[j] = ((arrtype*)((uchar*)src + j*srcstep))[i];      \
                                                                        \
        for( j = i; j < size.width; j++ )                               \
        {                                                               \
            double s = 0;                                               \
            const arrtype *tsrc = src + j;                              \
                                                                        \
            for( k = 0; k < size.height; k++, (char*&)tsrc += srcstep ) \
            {                                                           \
                s += col_buf[k] * tsrc[0];                              \
            }                                                           \
            tdst[j] = (arrtype)s;                                       \
        }                                                               \
    }                                                                   \
                                                                        \
    /* fill the lower part of the destination matrix */                 \
    for( i = 1; i < size.width; i++ )                                   \
        for( j = 0; j < i; j++ )                                        \
            ((arrtype*)((uchar*)dst + dststep*i))[j] =                  \
                ((arrtype*)((uchar*)dst + dststep*j))[i];               \
                                                                        \
    if( col_buf && !local_alloc )                                       \
        icvFree( (void**)&col_buf );                                    \
                                                                        \
    return CV_NO_ERR;                                                   \
}



#define ICV_DEF_MULTRANS_L_FUNC( flavor, arrtype )                              \
IPCVAPI_IMPL( CvStatus,                                                         \
icvMulTransposedL_##flavor, ( const arrtype* src, int srcstep,                  \
                              arrtype* dst, int dststep,                        \
                              CvSize size ))                                    \
{                                                                               \
    int i, j, k;                                                                \
    arrtype* tdst = dst;                                                        \
                                                                                \
    for( i = 0; i < size.height; i++, (char*&)tdst += dststep )                 \
    {                                                                           \
        for( j = i; j < size.height; j++ )                                      \
        {                                                                       \
            double s = 0;                                                       \
            const arrtype *tsrc1 = (const arrtype*)((uchar*)src + i*srcstep);   \
            const arrtype *tsrc2 = (const arrtype*)((uchar*)src + j*srcstep);   \
                                                                                \
            for( k = 0; k < size.width; k++ )                                   \
                s += tsrc1[k] * tsrc2[k];                                       \
            tdst[j] = (arrtype)s;                                               \
        }                                                                       \
    }                                                                           \
                                                                                \
    /* fill the lower part of the destination matrix */                         \
    for( j = 0; j < size.height - 1; j++ )                                      \
        for( i = j; i < size.height; i++ )                                      \
            ((arrtype*)((uchar*)dst + dststep*i))[j] =                          \
                ((arrtype*)((uchar*)dst + dststep*j))[i];                       \
                                                                                \
    return CV_NO_ERR;                                                           \
}


ICV_DEF_MULTRANS_R_FUNC( 32f, float )
ICV_DEF_MULTRANS_R_FUNC( 64f, double )
ICV_DEF_MULTRANS_L_FUNC( 32f, float )
ICV_DEF_MULTRANS_L_FUNC( 64f, double )

static void icvInitMulTransposedTable( CvFuncTable* tabL, CvFuncTable* tabR )   \
{                                                                               \
    tabL->fn_2d[CV_32F] = (void*)icvMulTransposedL_32f;                                \
    tabL->fn_2d[CV_64F] = (void*)icvMulTransposedL_64f;                                \
    tabR->fn_2d[CV_32F] = (void*)icvMulTransposedR_32f;                                \
    tabR->fn_2d[CV_64F] = (void*)icvMulTransposedR_64f;                                \
}


CV_IMPL void
cvMulTransposed( const CvArr* srcarr, CvArr* dstarr, int order )
{
    static CvFuncTable tab[2];
    static int inittab = 0;

    uchar* buffer = 0;
    int local_alloc = 0;

    CV_FUNCNAME( "cvMulTransposed" );

    __BEGIN__;

    CvMat sstub, *src = (CvMat*)srcarr;
    CvMat dstub, *dst = (CvMat*)dstarr;
    CvFunc2D_2A func = 0;
    int type;

    if( !inittab )
    {
        icvInitMulTransposedTable( tab + 0, tab + 1 );
        inittab = 1;
    }

    if( !CV_IS_ARR( src ))
        CV_CALL( src = cvGetMat( src, &sstub ));

    if( !CV_IS_ARR( dst ))
        CV_CALL( dst = cvGetMat( dst, &dstub ));

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    type = CV_ARR_TYPE( src->type );

    if( dst->width != dst->height )
        CV_ERROR( CV_StsBadSize, "The destination matrix must be square" );

    if( (order != 0 && src->width != dst->width) ||
        (order == 0 && src->height != dst->height))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    func = (CvFunc2D_2A)(tab[order != 0].fn_2d[CV_ARR_DEPTH(type)]);

    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    IPPI_CALL( func( src->data.ptr, src->step,
                     dst->data.ptr, dst->step, icvGetMatSize( src )));

    CV_CHECK_NANS( dst );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );
}


/****************************************************************************************\
*                                        cvDotProduct                                    *
\****************************************************************************************/

#define ICV_DEF_DOT_PROD_FUNC_2D( flavor, arrtype, temptype, sumtype )                  \
IPCVAPI_IMPL( CvStatus,                                                                 \
icvDotProduct_##flavor##_C1R, ( const arrtype* src1, int step1,                         \
                                const arrtype* src2, int step2,                         \
                                CvSize size, sumtype* _sum ))                           \
{                                                                                       \
    sumtype sum = 0;                                                                    \
                                                                                        \
    for( ; size.height--; (char*&)src1 += step1, (char*&)src2 += step2 )                \
    {                                                                                   \
        int i;                                                                          \
                                                                                        \
        for( i = 0; i <= size.width - 4; i += 4 )                                       \
        {                                                                               \
            (sum) += (temptype)src1[i]*src2[i] + (temptype)src1[i + 1]*src2[i + 1] +    \
                (temptype)src1[i + 2]*src2[i + 2] + (temptype)src1[i + 3]*src2[i + 3];  \
        }                                                                               \
                                                                                        \
        for( ; i < size.width; i++ )                                                    \
        {                                                                               \
            (sum) += (temptype)src1[i]*src2[i];                                         \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    *_sum = sum;                                                                        \
    return CV_OK;                                                                       \
}


ICV_DEF_DOT_PROD_FUNC_2D( 8u, uchar, int, int64 )
ICV_DEF_DOT_PROD_FUNC_2D( 8s, char, int, int64 )
ICV_DEF_DOT_PROD_FUNC_2D( 16s, short, int64, int64 )
ICV_DEF_DOT_PROD_FUNC_2D( 32s, int, double, double )
ICV_DEF_DOT_PROD_FUNC_2D( 32f, float, double, double )
ICV_DEF_DOT_PROD_FUNC_2D( 64f, double, double, double )

CV_DEF_INIT_FUNC_TAB_2D( DotProduct, C1R )

CV_IMPL double
cvDotProduct( const CvArr* srcAarr, const CvArr* srcBarr )
{
    static CvFuncTable tab_2d;
    static int inittab = 0;

    double result = 0;
    
    CV_FUNCNAME( "cvTranspose" );

    __BEGIN__;

    CvMat stubA, *srcA = (CvMat*)srcAarr;
    CvMat stubB, *srcB = (CvMat*)srcBarr;
    CvSize size;
    int type, depth;

    if( !inittab )
    {
        icvInitDotProductC1RTable( &tab_2d );
        inittab = 1;
    }

    if( !CV_IS_ARR( srcA ))
    {
        int coi = 0;
        CV_CALL( srcA = cvGetMat( srcA, &stubA, &coi ));
        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "coi is not supported" );
    }

    if( srcBarr == srcAarr )
    {
        srcB = srcA; 
    }
    else
    {
        if( !CV_IS_ARR( srcB ))
        {
            int coi = 0;
            CV_CALL( srcB = cvGetMat( srcB, &stubB, &coi ));

            if( coi != 0 )
                CV_ERROR( CV_BadCOI, "coi is not supported" );
        }

        if( !CV_ARE_TYPES_EQ( srcA, srcB ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( !CV_ARE_SIZES_EQ( srcA, srcB ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );
    }

    type = CV_ARR_TYPE( srcA->type );
    size = icvGetMatSize( srcA );

    size.width *= CV_ARR_CN( type );
    depth = CV_ARR_DEPTH( type );

    if( CV_IS_ARR_CONT( srcA->type & srcB->type ))
    {
        size.width *= size.height;

        if( size.width <= CV_MAX_INLINE_MAT_OP_SIZE )
        {
            if( depth == CV_32F )
            {
                float* mA = srcA->data.fl;
                float* mB = srcB->data.fl;

                do
                {
                    result += mA[size.width - 1]*mB[size.width - 1];
                }
                while( --size.width );

                EXIT;
            }
            
            if( depth == CV_64F )
            {
                double* mA = srcA->data.db;
                double* mB = srcB->data.db;

                do
                {
                    result += mA[size.width - 1]*mB[size.width - 1];
                }
                while( --size.width );

                EXIT;
            }
        }

        size.height = 1;
    }

    {
        CvFunc2D_2A1P func = (CvFunc2D_2A1P)(tab_2d.fn_2d[depth]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( srcA->data.ptr, srcA->step,
                         srcB->data.ptr, srcB->step,
                         size, &result ));
    }

    if( depth < CV_32S )
        result = (double)(int64&)result;

    icvCheckVector_64f( &result, 1 );

    __END__;

    return result;
}


/****************************************************************************************\
*                                        cvPerspectiveTransform                          *
\****************************************************************************************/

#define ICV_PERSPECTIVE_TRANSFORM_FUNC( flavor, arrtype, cn )                           \
CvStatus CV_STDCALL                                                                     \
icvPerspectiveTransform_##flavor##_C##cn##R( const arrtype* src, int srcstep,           \
                                             arrtype* dst, int dststep,                 \
                                             CvSize size, const double* mat )           \
{                                                                                       \
    float eps = FLT_EPSILON;                                                            \
    int i, ieps = (int&)eps;                                                            \
                                                                                        \
    size.width *= (cn);                                                                 \
                                                                                        \
    for( ; size.height--; (char*&)src += srcstep, (char*&)dst += dststep )              \
    {                                                                                   \
        for( i = 0; i < size.width; i += (cn) )                                         \
        {                                                                               \
            arrtype x = src[i], y = src[i + 1], z = src[i + 2];                         \
            double w = x*mat[12] + y*mat[13] + z*mat[14] + mat[15];                     \
            float tw = (float)w;                                                        \
                                                                                        \
            if( ((int&)tw & INT_MAX) > ieps )                                           \
            {                                                                           \
                w = 1./w;                                                               \
                dst[i] = (arrtype)((x*mat[0] + y*mat[1] + z*mat[2] + mat[3]) * w);      \
                dst[i+1] = (arrtype)((x*mat[4] + y*mat[5] + z*mat[6] + mat[7]) * w);    \
                dst[i+2] = (arrtype)((x*mat[8] + y*mat[9] + z*mat[10] + mat[11]) * w);  \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                dst[i] = (arrtype)0;                                                    \
                dst[i+1] = (arrtype)0;                                                  \
                dst[i+2] = (arrtype)0;                                                  \
            }                                                                           \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    return CV_OK;                                                                       \
}


ICV_PERSPECTIVE_TRANSFORM_FUNC( 32f, float, 3 )
ICV_PERSPECTIVE_TRANSFORM_FUNC( 64f, double, 3 )

static void icvInitPerspectiveTransformTable( CvFuncTable* tab )   \
{                                                                  \
    tab->fn_2d[CV_32F] = (void*)icvPerspectiveTransform_32f_C3R;          \
    tab->fn_2d[CV_64F] = (void*)icvPerspectiveTransform_64f_C3R;          \
}


CV_IMPL void
cvPerspectiveTransform( const CvArr* srcarr, CvArr* dstarr, const CvArr* matrix )
{
    static CvFuncTable tab;
    static int inittab = 0;
    double buffer[16];

    CV_FUNCNAME( "cvPerspectiveProject" );

    __BEGIN__;

    CvMat sstub, *src = (CvMat*)srcarr;
    CvMat dstub, *dst = (CvMat*)dstarr;
    CvMat mstub, *mat = (CvMat*)matrix;
    int i, j, type, cn;
    CvFunc2D_2A1P func = 0;
    CvSize size;

    if( !inittab )
    {
        icvInitPerspectiveTransformTable( &tab );
        inittab = 1;
    }

    if( !CV_IS_ARR( src ))
    {
        int coi = 0;
        CV_CALL( src = cvGetMat( src, &sstub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_IS_ARR( dst ))
    {
        int coi = 0;
        CV_CALL( dst = cvGetMat( dst, &dstub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_ARR_TYPE( src->type );
    cn = CV_ARR_CN( type );

    if( cn != 3 )
        CV_ERROR( CV_BadNumChannels, icvUnsupportedFormat );

    if( !CV_IS_ARR( mat ))
    {
        int coi = 0;
        CV_CALL( mat = cvGetMat( mat, &mstub, &coi ));

        if( coi != 0 )
            CV_ERROR( CV_BadCOI, "" );
    }

    if( mat->height != cn + 1 && mat->width != mat->height )
        CV_ERROR( CV_StsBadSize,
        "The size of transform matrix must be equal to number of channels" );

    if( CV_ARR_TYPE( mat->type ) == CV_64FC1 )
    {
        for( i = 0; i <= cn; i++ )
        {
            for( j = 0; j <= cn; j++ )
                buffer[i*(cn+1) + j] = ((double*)(mat->data.ptr + mat->step*i))[j];
        }
    }
    else if( CV_ARR_TYPE( mat->type ) == CV_32FC1 )
    {
        for( i = 0; i <= cn; i++ )
        {
            for( j = 0; j <= cn; j++ )
                buffer[i*(cn+1) + j] = ((float*)(mat->data.ptr + mat->step*i))[j];
        }
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "Rotation matrix must be 32fC1 or 64fC1" );
    }

    func = (CvFunc2D_2A1P)tab.fn_2d[CV_ARR_DEPTH(type)];

    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    size = icvGetMatSize( src );

    if( CV_IS_ARR_CONT( src->type & dst->type ))
    {
        size.width *= size.height;
        size.height = 1;
    }

    IPPI_CALL( func( src->data.ptr, src->step, dst->data.ptr, dst->step, size, buffer));

    CV_CHECK_NANS( dst );

    __END__;
}

/* End of file. */
