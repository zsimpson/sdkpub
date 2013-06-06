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

#define ICV_DEF_INIT_TAB_DETECTION( FUNCNAME )              \
static void icvInit##FUNCNAME##Table( CvFuncTable* table )  \
{                                                           \
    table->fn_2d[CV_8U] = (void*)icv##FUNCNAME##_8u32f_C1R; \
    table->fn_2d[CV_8S] = (void*)icv##FUNCNAME##_8s32f_C1R; \
    table->fn_2d[CV_32F] = (void*)icv##FUNCNAME##_32f_C1R;  \
}


ICV_DEF_INIT_TAB_DETECTION( MinEigenVal )
ICV_DEF_INIT_TAB_DETECTION( EigenValsVecs )
ICV_DEF_INIT_TAB_DETECTION( PreCornerDetect )

typedef CvStatus (CV_STDCALL * CvEigFunc)( const void* src, int srcstep,
                                           void* dst, int dststep,
                                           CvSize size, int aperture_size,
                                           int block_size, void* buffer );

CV_IMPL void
cvCornerMinEigenVal( const void* srcarr, void* eigenvarr,
                     int block_size, int aperture_size )
{
    static CvFuncTable eig_tab;
    static int inittab = 0;
    void *buffer = 0;

    CV_FUNCNAME( "cvCornerMinEigenVal" );

    __BEGIN__;

    CvSize src_size;
    int buf_size;
    CvEigFunc func = 0;

    CvMat stub, *src = (CvMat*)srcarr;
    CvMat eigstub, *eigenv = (CvMat*)eigenvarr;

    if( !inittab )
    {
        icvInitMinEigenValTable( &eig_tab );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( srcarr, &stub ));
    CV_CALL( eigenv = cvGetMat( eigenv, &eigstub ));

    if( CV_ARR_CN(src->type) != 1 || CV_ARR_CN(eigenv->type) != 1 )
        CV_ERROR(CV_StsBadArg, "Source or min-eigen-val images have more than 1 channel");

    if( CV_ARR_DEPTH(eigenv->type) != CV_32F )
        CV_ERROR( CV_BadDepth, "min-eigen-val image does not have IPL_DEPTH_32F depth" );

    if( !CV_ARE_SIZES_EQ( src, eigenv ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    func = (CvEigFunc)(eig_tab.fn_2d[CV_ARR_DEPTH(src->type)]);
    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    src_size = icvGetMatSize( src );

    IPPI_CALL( icvMinEigenValGetSize( src_size.width, aperture_size, block_size, &buf_size ));
    CV_CALL( buffer = cvAlloc( buf_size ));

    IPPI_CALL( func( src->data.ptr, src->step, eigenv->data.ptr, eigenv->step,
                     src_size, aperture_size, block_size, buffer ));

    __END__;

    cvFree( &buffer );
}


CV_IMPL void
cvCornerEigenValsAndVecs( const void* srcarr, void* eigenvarr,
                          int block_size, int aperture_size )
{
    static CvFuncTable eig_tab;
    static int inittab = 0;
    void *buffer = 0;

    CV_FUNCNAME( "cvCornerEigenValsAndVecs" );

    __BEGIN__;

    CvSize src_size;
    int buf_size;
    CvEigFunc func = 0;

    CvMat stub, *src = (CvMat*)srcarr;
    CvMat eigstub, *eigenv = (CvMat*)eigenvarr;

    if( !inittab )
    {
        icvInitEigenValsVecsTable( &eig_tab );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( srcarr, &stub ));
    CV_CALL( eigenv = cvGetMat( eigenv, &eigstub ));

    if( CV_ARR_CN(src->type) != 1 )
        CV_ERROR(CV_StsBadArg, "Source image has more than 1 channel");

    if( CV_ARR_CN(eigenv->type)*eigenv->width != src->width*6 )
        CV_ERROR(CV_StsBadArg, "Eigen-vals&vecs image should be 6 times "
                               "wider than the source image");

    if( src->height != eigenv->height )
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    if( CV_ARR_DEPTH(eigenv->type) != CV_32F )
        CV_ERROR( CV_BadDepth, "Eigen-vals&vecs image does not have IPL_DEPTH_32F depth" );

    func = (CvEigFunc)(eig_tab.fn_2d[CV_ARR_DEPTH(src->type)]);
    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    src_size = icvGetMatSize( src );

    IPPI_CALL( icvEigenValsVecsGetSize( src_size.width, aperture_size,
                                        block_size, &buf_size ));
    CV_CALL( buffer = cvAlloc( buf_size ));

    IPPI_CALL( func( src->data.ptr, src->step, eigenv->data.ptr, eigenv->step,
                     src_size, aperture_size, block_size, buffer ));

    __END__;

    cvFree( &buffer );
}


typedef CvStatus (CV_STDCALL * CvPreCornerFunc)( const void* src, int srcstep,
                                                 void* dst, int dststep,
                                                 CvSize size, int aperture_size );

CV_IMPL void
cvPreCornerDetect( const void* srcarr, void* dstarr, int aperture_size )
{
    static CvFuncTable pre_tab;
    static int inittab = 0;

    CV_FUNCNAME( "cvPreCornerDetect" );

    __BEGIN__;

    CvSize src_size;
    CvPreCornerFunc func = 0;

    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;

    if( !inittab )
    {
        icvInitPreCornerDetectTable( &pre_tab );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( srcarr, &srcstub ));
    CV_CALL( dst = cvGetMat( dstarr, &dststub ));

    if( CV_ARR_CN(src->type) != 1 || CV_ARR_CN(dst->type) != 1 )
        CV_ERROR(CV_StsBadArg, "Source or min-eigen-val images have more than 1 channel");

    if( CV_ARR_DEPTH(dst->type) != CV_32F )
        CV_ERROR( CV_BadDepth, "min-eigen-val image does not have IPL_DEPTH_32F depth" );

    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    func = (CvPreCornerFunc)(pre_tab.fn_2d[CV_ARR_DEPTH(src->type)]);
    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    src_size = icvGetMatSize( src );

    IPPI_CALL( func( src->data.ptr, src->step, dst->data.ptr, dst->step,
                     src_size, aperture_size ));

    __END__;
}

/* End of file. */
