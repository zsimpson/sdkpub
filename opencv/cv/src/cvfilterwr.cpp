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

#define ICV_DEF_INIT_DERV_TAB( FUNCNAME )           \
static void icvInit##FUNCNAME##Table( void** tab )  \
{                                                   \
    tab[0] = (void*)icv##FUNCNAME##_8u16s_C1R;      \
    tab[1] = (void*)icv##FUNCNAME##_8s16s_C1R;      \
    tab[2] = (void*)icv##FUNCNAME##_32f_C1R;        \
}


ICV_DEF_INIT_DERV_TAB( Sobel )
ICV_DEF_INIT_DERV_TAB( Scharr )
ICV_DEF_INIT_DERV_TAB( Laplace )

typedef CvStatus (CV_STDCALL *CvDervFunc)( const void* src, int srcstep, void* dst, int dststep,
                                           CvSize* size, CvConvState* convState, int stage );

static const CvDataType dataType[] = { cv8u, cv8s, cv32f };

CV_IMPL void
cvSobel( const void* srcarr, void* dstarr, int dx, int dy, int aperture_size )
{
    static void* sobel_func[3];
    static void* scharr_func[3];
    static int inittab = 0;

    CvConvState *conv_state = 0;
    CV_FUNCNAME( "cvSobel" );

    __BEGIN__;

    int origin = 0;
    int idx = 2;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    CvDervFunc func = 0;
    CvSize size;

    if( !inittab )
    {
        icvInitSobelTable( sobel_func );
        icvInitScharrTable( scharr_func );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( src, &srcstub ));
    CV_CALL( dst = cvGetMat( dst, &dststub ));

    if( _CV_IS_IMAGE( srcarr ))
    {
        origin = ((IplImage*)srcarr)->origin;
    }

    if( CV_ARR_CN( src->type ) != 1 || CV_ARR_CN( dst->type ) != 1 )
        CV_ERROR( CV_BadNumChannels, icvUnsupportedFormat );

    if( CV_ARR_DEPTH( src->type ) <= CV_8S )
    {
        if( CV_ARR_DEPTH( dst->type ) != CV_16S )
            CV_ERROR( CV_StsUnmatchedFormats, "Destination should have 16s format"
                                              " when source has 8u or 8s format" );
        idx = CV_ARR_DEPTH(src->type) == CV_8S;
    }
    else if( CV_ARR_DEPTH( src->type ) == CV_32F )
    {
        if( CV_ARR_DEPTH( dst->type ) != CV_32F )
            CV_ERROR( CV_StsUnmatchedFormats, "Destination should have 16s format"
                                              " when source has 8u or 8s format" );
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "Unsupported source array format" );
    }

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( IPL_StsBadArg, "src and dst have different sizes" );

    if( aperture_size == CV_SCHARR )
    {
        IPPI_CALL( icvScharrInitAlloc( src->width, dataType[idx], origin, dx, dy, &conv_state ));
        func = (CvDervFunc)(scharr_func[idx]);
    }
    else
    {
        IPPI_CALL( icvSobelInitAlloc( src->width, dataType[idx], aperture_size,
                                      origin, dx, dy, &conv_state ));
        func = (CvDervFunc)(sobel_func[idx]);
    }

    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    size = icvGetMatSize(src);
    IPPI_CALL( func( src->data.ptr, src->step, dst->data.ptr,
                     dst->step, &size, conv_state, 0 ));

    __END__;

    if( conv_state )
    {
        if( aperture_size == CV_SCHARR )
        {
            icvScharrFree( &conv_state );
        }
        else
        {
            icvConvolFree( &conv_state );
        }
    }
}


CV_IMPL void
cvLaplace( const void* srcarr, void* dstarr, int aperture_size )
{
    static void* laplace_func[3];
    static int inittab = 0;
    
    CV_FUNCNAME( "cvLaplace" );

    CvConvState *conv_state = 0;

    __BEGIN__;

    int idx = 2;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    CvDervFunc func = 0;
    CvSize size;

    if( !inittab )
    {
        icvInitLaplaceTable( laplace_func );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( src, &srcstub ));
    CV_CALL( dst = cvGetMat( dst, &dststub ));

    if( CV_ARR_CN( src->type ) != 1 || CV_ARR_CN( dst->type ) != 1 )
        CV_ERROR( CV_BadNumChannels, icvUnsupportedFormat );

    if( CV_ARR_DEPTH( src->type ) <= CV_8S )
    {
        if( CV_ARR_DEPTH( dst->type ) != CV_16S )
            CV_ERROR( CV_StsUnmatchedFormats, "Destination should have 16s format"
                                              " when source has 8u or 8s format" );
        idx = CV_ARR_DEPTH(src->type) == CV_8S;
    }
    else if( CV_ARR_DEPTH( src->type ) == CV_32F )
    {
        if( CV_ARR_DEPTH( dst->type ) != CV_32F )
            CV_ERROR( CV_StsUnmatchedFormats, "Destination should have 16s format"
                                              " when source has 8u or 8s format" );
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "Unsupported source array format" );
    }

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( IPL_StsBadArg, "src and dst have different sizes" );

    IPPI_CALL( icvLaplaceInitAlloc( src->width, dataType[idx], aperture_size, &conv_state ));
    func = (CvDervFunc)(laplace_func[idx]);

    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    size = icvGetMatSize(src);
    IPPI_CALL( func( src->data.ptr, src->step, dst->data.ptr,
                     dst->step, &size, conv_state, 0 ));

    __END__;

    if( conv_state )
    {
        icvConvolFree( &conv_state );
    }
}
