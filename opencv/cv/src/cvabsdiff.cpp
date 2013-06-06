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
#include <assert.h>

#define  ICV_DEF_BIN_ABS_DIFF_2D(name, arrtype, temptype, abs_macro, cast_macro)\
IPCVAPI_IMPL( CvStatus,                                                         \
name,( const arrtype* src1, int step1, const arrtype* src2, int step2,          \
      arrtype* dst, int step, CvSize size ))                                    \
{                                                                               \
    for( ; size.height--; (char*&)src1 += step1, (char*&)src2 += step2,         \
                          (char*&)dst += step )                                 \
    {                                                                           \
        int i;                                                                  \
                                                                                \
        for( i = 0; i <= size.width - 4; i += 4 )                               \
        {                                                                       \
            temptype t0 = src1[i] - src2[i];                                    \
            temptype t1 = src1[i+1] - src2[i+1];                                \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[i] = cast_macro(t0);                                            \
            dst[i+1] = cast_macro(t1);                                          \
                                                                                \
            t0 = src1[i+2] - src2[i+2];                                         \
            t1 = src1[i+3] - src2[i+3];                                         \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[i+2] = cast_macro(t0);                                          \
            dst[i+3] = cast_macro(t1);                                          \
        }                                                                       \
                                                                                \
        for( ; i < size.width; i++ )                                            \
        {                                                                       \
            temptype t0 = src1[i] - src2[i];                                    \
            t0 = (temptype)abs_macro(t0);                                       \
            dst[i] = cast_macro(t0);                                            \
        }                                                                       \
    }                                                                           \
                                                                                \
    return  CV_OK;                                                              \
}


#define  ICV_DEF_UN_ABS_DIFF_2D( name, arrtype, temptype, abs_macro, cast_macro)\
IPCVAPI_IMPL( CvStatus,                                                         \
name,( const arrtype* src0, int step1, arrtype* dst0, int step,                 \
      CvSize size, const temptype* scalar ))                                    \
{                                                                               \
    for( ; size.height--; (char*&)src0 += step1, (char*&)dst0 += step )         \
    {                                                                           \
        int i, len = size.width;                                                \
        const arrtype* src = src0;                                              \
        arrtype* dst = dst0;                                                    \
                                                                                \
        for( ; (len -= 12) >= 0; dst += 12, src += 12 )                         \
        {                                                                       \
            temptype t0 = src[0] - scalar[0];                                   \
            temptype t1 = src[1] - scalar[1];                                   \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[0] = cast_macro( t0 );                                          \
            dst[1] = cast_macro( t1 );                                          \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            t0 = src[2] - scalar[2];                                            \
            t1 = src[3] - scalar[3];                                            \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[2] = cast_macro( t0 );                                          \
            dst[3] = cast_macro( t1 );                                          \
                                                                                \
            t0 = src[4] - scalar[4];                                            \
            t1 = src[5] - scalar[5];                                            \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[4] = cast_macro( t0 );                                          \
            dst[5] = cast_macro( t1 );                                          \
                                                                                \
            t0 = src[6] - scalar[6];                                            \
            t1 = src[7] - scalar[7];                                            \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[6] = cast_macro( t0 );                                          \
            dst[7] = cast_macro( t1 );                                          \
                                                                                \
            t0 = src[8] - scalar[8];                                            \
            t1 = src[9] - scalar[9];                                            \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[8] = cast_macro( t0 );                                          \
            dst[9] = cast_macro( t1 );                                          \
                                                                                \
            t0 = src[10] - scalar[10];                                          \
            t1 = src[11] - scalar[11];                                          \
                                                                                \
            t0 = (temptype)abs_macro(t0);                                       \
            t1 = (temptype)abs_macro(t1);                                       \
                                                                                \
            dst[10] = cast_macro( t0 );                                         \
            dst[11] = cast_macro( t1 );                                         \
        }                                                                       \
                                                                                \
        for( (len) += 12, i = 0; i < (len); i++ )                               \
        {                                                                       \
            temptype t0 = src[i] - scalar[i];                                   \
            t0 = (temptype)abs_macro(t0);                                       \
            dst[i] = cast_macro( t0 );                                          \
        }                                                                       \
    }                                                                           \
                                                                                \
    return CV_OK;                                                               \
}


#define  ICV_TO_8U(x)  ((uchar)(x))

ICV_DEF_BIN_ABS_DIFF_2D( icvAbsDiff_8u_C1R, uchar, int, CV_IABS, ICV_TO_8U )
ICV_DEF_BIN_ABS_DIFF_2D( icvAbsDiff_32f_C1R, float, float, fabs, CV_CAST_32F )
ICV_DEF_BIN_ABS_DIFF_2D( icvAbsDiff_64f_C1R, double, double, fabs, CV_CAST_64F )

ICV_DEF_UN_ABS_DIFF_2D( icvAbsDiffC_8u_C1R, uchar, int, CV_IABS, CV_CAST_8U )
ICV_DEF_UN_ABS_DIFF_2D( icvAbsDiffC_32f_C1R, float, float, fabs, CV_CAST_32F )
ICV_DEF_UN_ABS_DIFF_2D( icvAbsDiffC_64f_C1R, double, double, fabs, CV_CAST_64F )


#define  ICV_INIT_MINI_FUNC_TAB_2D( FUNCNAME )          \
static void icvInit##FUNCNAME##Table( CvFuncTable* tab )\
{                                                       \
    tab->fn_2d[CV_8U] = (void*)icv##FUNCNAME##_8u_C1R;         \
    tab->fn_2d[CV_32F] = (void*)icv##FUNCNAME##_32f_C1R;       \
    tab->fn_2d[CV_64F] = (void*)icv##FUNCNAME##_64f_C1R;       \
}


ICV_INIT_MINI_FUNC_TAB_2D( AbsDiff )
ICV_INIT_MINI_FUNC_TAB_2D( AbsDiffC )


CV_IMPL  void
cvAbsDiff( const void* srcarr1, const void* srcarr2, void* dstarr )
{
    static CvFuncTable adiff_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvAbsDiff" );

    __BEGIN__;

    int coi1 = 0, coi2 = 0, coi3 = 0;
    CvMat srcstub1, *src1 = (CvMat*)srcarr1;
    CvMat srcstub2, *src2 = (CvMat*)srcarr2;
    CvMat dststub,  *dst = (CvMat*)dstarr;
    int src1_step, src2_step, dst_step;
    CvSize size;
    int type;

    if( !inittab )
    {
        icvInitAbsDiffTable( &adiff_tab );
        inittab = 1;
    }

    CV_CALL( src1 = cvGetMat( src1, &srcstub1, &coi1 ));
    CV_CALL( src2 = cvGetMat( src2, &srcstub2, &coi2 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi3 ));

    if( coi1 != 0 || coi2 != 0 || coi3 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( !CV_ARE_SIZES_EQ( src1, src2 ) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    size = icvGetMatSize( src1 );
    type = CV_ARR_TYPE(src1->type);

    if( !CV_ARE_SIZES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );
    
    if( !CV_ARE_TYPES_EQ( src1, src2 ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_TYPES_EQ( src1, dst ))
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    size.width *= CV_ARR_CN( type );

    src1_step = src1->step;
    src2_step = src2->step;
    dst_step = dst->step;

    if( CV_IS_ARR_CONT( src1->type & src2->type & dst->type ))
    {
        size.width *= size.height;
        size.height = 1;
        src1_step = src2_step = dst_step = CV_STUB_STEP;
    }

    {
        CvFunc2D_3A func = (CvFunc2D_3A)
            (adiff_tab.fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src1->data.ptr, src1_step, src2->data.ptr, src2_step,
                         dst->data.ptr, dst_step, size ));
    }

    __END__;
}


CV_IMPL void
cvAbsDiffS( const void* srcarr, void* dstarr, CvScalar scalar )
{
    static CvFuncTable adiffs_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvAbsDiffS" );

    __BEGIN__;

    int coi1 = 0, coi2 = 0;
    int type, sctype;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    int src_step = src->step;
    int dst_step = dst->step;
    double buf[12];
    CvSize size;

    if( !inittab )
    {
        icvInitAbsDiffCTable( &adiffs_tab );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));
    CV_CALL( dst = cvGetMat( dst, &dststub, &coi2 ));

    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    if( !CV_ARE_TYPES_EQ(src, dst) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedFormats );

    if( !CV_ARE_SIZES_EQ(src, dst) )
        CV_ERROR_FROM_CODE( CV_StsUnmatchedSizes );

    sctype = type = CV_ARR_TYPE( src->type );
    if( CV_ARR_DEPTH(type) < CV_32S )
        sctype = (type & CV_ARR_CN_MASK) | CV_32SC1;
 
    size = icvGetMatSize( src );
    size.width *= CV_ARR_CN( type );

    src_step = src->step;
    dst_step = dst->step;

    if( CV_IS_ARR_CONT( src->type & dst->type ))
    {
        size.width *= size.height;
        size.height = 1;
        src_step = dst_step = CV_STUB_STEP;
    }

    CV_CALL( cvScalarToRawData( &scalar, sctype, buf, 1 ));

    {
        CvFunc2D_2A1P func = (CvFunc2D_2A1P)
            (adiffs_tab.fn_2d[CV_ARR_DEPTH(type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src->data.ptr, src_step, dst->data.ptr,
                         dst_step, size, buf ));
    }

    __END__;
}



/* 
   Finds L1 norm between two blocks.
*/
int
icvCmpBlocksL1_8u_C1( const uchar * vec1, const uchar * vec2, int len )
{
    int i, sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        int t0 = vec1[i] - vec2[i];
        int t1 = vec1[i + 1] - vec2[i + 1];
        int t2 = vec1[i + 2] - vec2[i + 2];
        int t3 = vec1[i + 3] - vec2[i + 3];

        sum += CV_IABS( t0 ) + CV_IABS( t1 ) + CV_IABS( t2 ) + CV_IABS( t3 );
    }

    for( ; i < len; i++ )
    {
        int t0 = vec1[i] - vec2[i];

        sum += CV_IABS( t0 );
    }

    return sum;
}


int64
icvCmpBlocksL2_8u_C1( const uchar * vec1, const uchar * vec2, int len )
{
    int i, s = 0;
    int64 sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        int v = vec1[i] - vec2[i];
        int e = v * v;

        v = vec1[i + 1] - vec2[i + 1];
        e += v * v;
        v = vec1[i + 2] - vec2[i + 2];
        e += v * v;
        v = vec1[i + 3] - vec2[i + 3];
        e += v * v;
        sum += e;
    }

    for( ; i < len; i++ )
    {
        int v = vec1[i] - vec2[i];

        s += v * v;
    }

    return sum + s;
}


int64
icvCmpBlocksL2_8s_C1( const char *vec1, const char *vec2, int len )
{
    int i, s = 0;
    int64 sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        int v = vec1[i] - vec2[i];
        int e = v * v;

        v = vec1[i + 1] - vec2[i + 1];
        e += v * v;
        v = vec1[i + 2] - vec2[i + 2];
        e += v * v;
        v = vec1[i + 3] - vec2[i + 3];
        e += v * v;
        sum += e;
    }

    for( ; i < len; i++ )
    {
        int v = vec1[i] - vec2[i];

        s += v * v;
    }

    return sum + s;
}


double
icvCmpBlocksL2_32f_C1( const float *vec1, const float *vec2, int len )
{
    double sum = 0;
    int i;

    for( i = 0; i <= len - 4; i += 4 )
    {
        double v0 = vec1[i] - vec2[i];
        double v1 = vec1[i + 1] - vec2[i + 1];
        double v2 = vec1[i + 2] - vec2[i + 2];
        double v3 = vec1[i + 3] - vec2[i + 3];

        sum += v0 * v0 + v1 * v1 + v2 * v2 + v3 * v3;
    }
    for( ; i < len; i++ )
    {
        double v = vec1[i] - vec2[i];

        sum += v * v;
    }
    return sum;
}


/* 
   Calculates cross correlation for two blocks.
*/
int64
icvCrossCorr_8u_C1( const uchar * vec1, const uchar * vec2, int len )
{
    int i, s = 0;
    int64 sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        int e = vec1[i] * vec2[i];
        int v = vec1[i + 1] * vec2[i + 1];

        e += v;
        v = vec1[i + 2] * vec2[i + 2];
        e += v;
        v = vec1[i + 3] * vec2[i + 3];
        e += v;
        sum += e;
    }

    for( ; i < len; i++ )
    {
        s += vec1[i] * vec2[i];
    }

    return sum + s;
}


int64
icvCrossCorr_8s_C1( const char *vec1, const char *vec2, int len )
{
    int i, s = 0;
    int64 sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        int e = vec1[i] * vec2[i];
        int v = vec1[i + 1] * vec2[i + 1];

        e += v;
        v = vec1[i + 2] * vec2[i + 2];
        e += v;
        v = vec1[i + 3] * vec2[i + 3];
        e += v;
        sum += e;
    }

    for( ; i < len; i++ )
    {
        s += vec1[i] * vec2[i];
    }

    return sum + s;
}


double
icvCrossCorr_32f_C1( const float *vec1, const float *vec2, int len )
{
    double sum = 0;
    int i;

    for( i = 0; i <= len - 4; i += 4 )
    {
        double v0 = vec1[i] * vec2[i];
        double v1 = vec1[i + 1] * vec2[i + 1];
        double v2 = vec1[i + 2] * vec2[i + 2];
        double v3 = vec1[i + 3] * vec2[i + 3];

        sum += v0 + v1 + v2 + v3;
    }
    for( ; i < len; i++ )
    {
        double v = vec1[i] * vec2[i];

        sum += v;
    }
    return sum;
}


/* 
   Calculates cross correlation for two blocks.
*/
int64
icvSumPixels_8u_C1( const uchar * vec, int len )
{
    int i, s = 0;
    int64 sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        sum += vec[i] + vec[i + 1] + vec[i + 2] + vec[i + 3];
    }

    for( ; i < len; i++ )
    {
        s += vec[i];
    }

    return sum + s;
}


int64
icvSumPixels_8s_C1( const char *vec, int len )
{
    int i, s = 0;
    int64 sum = 0;

    for( i = 0; i <= len - 4; i += 4 )
    {
        sum += vec[i] + vec[i + 1] + vec[i + 2] + vec[i + 3];
    }

    for( ; i < len; i++ )
    {
        s += vec[i];
    }

    return sum + s;
}


double
icvSumPixels_32f_C1( const float *vec, int len )
{
    double sum = 0;
    int i;

    for( i = 0; i <= len - 4; i += 4 )
    {
        sum += vec[i] + vec[i + 1] + vec[i + 2] + vec[i + 3];
    }

    for( ; i < len; i++ )
    {
        sum += vec[i];
    }
    return sum;
}


/* End of file. */
