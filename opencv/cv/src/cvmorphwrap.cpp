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

CV_IMPL IplConvKernel *
cvCreateStructuringElementEx( int cols, int rows,
                              int anchorX, int anchorY,
                              CvElementShape shape, int *values )
{
    IplConvKernel *element = 0;
    int i, size = rows * cols;
    int *vals;
    int element_size = sizeof( *element ) + size * sizeof( element->values[0] );

    CV_FUNCNAME( "cvCreateStructuringElementEx" );

    __BEGIN__;

    if( !values && shape == CV_SHAPE_CUSTOM )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( cols <= 0 || rows <= 0 ||
        (unsigned) anchorX >= (unsigned) cols || (unsigned) anchorY >= (unsigned) rows )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    element_size = icvAlign(element_size,32);
    element = (IplConvKernel *) icvAlloc( element_size );
    if( !element )
        CV_ERROR_FROM_STATUS( CV_OUTOFMEM_ERR );

    element->nCols = cols;
    element->nRows = rows;
    element->anchorX = anchorX;
    element->anchorY = anchorY;
    element->nShiftR = shape < CV_SHAPE_ELLIPSE ? shape : CV_SHAPE_CUSTOM;
    element->values = vals = (int *) (element + 1);

    switch (shape)
    {
    case CV_SHAPE_RECT:
        memset( vals, -1, sizeof( vals[0] ) * cols * rows );
        break;
    case CV_SHAPE_CROSS:
        memset( vals, 0, sizeof( vals[0] ) * cols * rows );
        for( i = 0; i < cols; i++ )
        {
            vals[i + anchorY * cols] = -1;
        }

        for( i = 0; i < rows; i++ )
        {
            vals[anchorX + i * cols] = -1;
        }
        break;
    case CV_SHAPE_ELLIPSE:
        {
            int r = (rows + 1) / 2;
            int c = cols / 2;
            double inv_r2 = 1. / (((double) (r)) * (r));

            memset( vals, 0, sizeof( vals[0] ) * cols * rows );

            for( i = 0; i < r; i++ )
            {
                int y = r - i;
                int dx = cvRound( c * sqrt( (r * r - y * y) * inv_r2 ));
                int x1 = c - dx;
                int x2 = c + dx;

                if( x1 < 0 )
                    x1 = 0;
                if( x2 >= cols )
                    x2 = cols;
                x2 -= x1 - 1;
                memset( vals + i * cols + x1, -1, x2 * sizeof( int ));
                memset( vals + (rows - i - 1) * cols + x1, -1, x2 * sizeof( int ));
            }
        }
        break;
    case CV_SHAPE_CUSTOM:
        for( i = 0; i < size; i++ )
        {
            vals[i] = !values || values[i] ? -1 : 0;
        }
        break;
    default:
        icvFree( &element );
        CV_ERROR_FROM_STATUS( CV_BADFLAG_ERR );
    }

    __END__;

    return element;
}


CV_IMPL void
cvReleaseStructuringElement( IplConvKernel ** element )
{
    CV_FUNCNAME( "cvReleaseStructuringElement" );

    __BEGIN__;

    if( !element )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );
    icvFree( element );

    __END__;
}


typedef CvStatus( CV_STDCALL* CvMorphFunc )( const void* src, int src_step,
                                             void* dst, int dst_step,
                                             CvSize* size, struct CvMorphState * state,
                                             int stage );


static void icvInitMorphologyTab( CvBigFuncTable* rect_erode, CvBigFuncTable* rect_dilate,
                                CvBigFuncTable* cross_erode, CvBigFuncTable* cross_dilate,
                                CvBigFuncTable* arb_erode, CvBigFuncTable* arb_dilate )
{
    rect_erode->fn_2d[CV_8UC1] = (void*)icvErodeStrip_Rect_8u_C1R;
    rect_erode->fn_2d[CV_8UC3] = (void*)icvErodeStrip_Rect_8u_C3R;
    rect_erode->fn_2d[CV_8UC4] = (void*)icvErodeStrip_Rect_8u_C4R;

    rect_erode->fn_2d[CV_32FC1] = (void*)icvErodeStrip_Rect_32f_C1R;
    rect_erode->fn_2d[CV_32FC3] = (void*)icvErodeStrip_Rect_32f_C3R;
    rect_erode->fn_2d[CV_32FC4] = (void*)icvErodeStrip_Rect_32f_C4R;

    cross_erode->fn_2d[CV_8UC1] = (void*)icvErodeStrip_Cross_8u_C1R;
    cross_erode->fn_2d[CV_8UC3] = (void*)icvErodeStrip_Cross_8u_C3R;
    cross_erode->fn_2d[CV_8UC4] = (void*)icvErodeStrip_Cross_8u_C4R;

    cross_erode->fn_2d[CV_32FC1] = (void*)icvErodeStrip_Cross_32f_C1R;
    cross_erode->fn_2d[CV_32FC3] = (void*)icvErodeStrip_Cross_32f_C3R;
    cross_erode->fn_2d[CV_32FC4] = (void*)icvErodeStrip_Cross_32f_C4R;

    arb_erode->fn_2d[CV_8UC1] = (void*)icvErodeStrip_8u_C1R;
    arb_erode->fn_2d[CV_8UC3] = (void*)icvErodeStrip_8u_C3R;
    arb_erode->fn_2d[CV_8UC4] = (void*)icvErodeStrip_8u_C4R;

    arb_erode->fn_2d[CV_32FC1] = (void*)icvErodeStrip_32f_C1R;
    arb_erode->fn_2d[CV_32FC3] = (void*)icvErodeStrip_32f_C3R;
    arb_erode->fn_2d[CV_32FC4] = (void*)icvErodeStrip_32f_C4R;

    rect_dilate->fn_2d[CV_8UC1] = (void*)icvDilateStrip_Rect_8u_C1R;
    rect_dilate->fn_2d[CV_8UC3] = (void*)icvDilateStrip_Rect_8u_C3R;
    rect_dilate->fn_2d[CV_8UC4] = (void*)icvDilateStrip_Rect_8u_C4R;

    rect_dilate->fn_2d[CV_32FC1] = (void*)icvDilateStrip_Rect_32f_C1R;
    rect_dilate->fn_2d[CV_32FC3] = (void*)icvDilateStrip_Rect_32f_C3R;
    rect_dilate->fn_2d[CV_32FC4] = (void*)icvDilateStrip_Rect_32f_C4R;

    cross_dilate->fn_2d[CV_8UC1] = (void*)icvDilateStrip_Cross_8u_C1R;
    cross_dilate->fn_2d[CV_8UC3] = (void*)icvDilateStrip_Cross_8u_C3R;
    cross_dilate->fn_2d[CV_8UC4] = (void*)icvDilateStrip_Cross_8u_C4R;

    cross_dilate->fn_2d[CV_32FC1] = (void*)icvDilateStrip_Cross_32f_C1R;
    cross_dilate->fn_2d[CV_32FC3] = (void*)icvDilateStrip_Cross_32f_C3R;
    cross_dilate->fn_2d[CV_32FC4] = (void*)icvDilateStrip_Cross_32f_C4R;

    arb_dilate->fn_2d[CV_8UC1] = (void*)icvDilateStrip_8u_C1R;
    arb_dilate->fn_2d[CV_8UC3] = (void*)icvDilateStrip_8u_C3R;
    arb_dilate->fn_2d[CV_8UC4] = (void*)icvDilateStrip_8u_C4R;

    arb_dilate->fn_2d[CV_32FC1] = (void*)icvDilateStrip_32f_C1R;
    arb_dilate->fn_2d[CV_32FC3] = (void*)icvDilateStrip_32f_C3R;
    arb_dilate->fn_2d[CV_32FC4] = (void*)icvDilateStrip_32f_C4R;
}

static void
icvMorphOp( const void* srcarr, void* dstarr, IplConvKernel* element,
            int iterations, int mop )
{
    static CvBigFuncTable morph_tab[6];
    static int inittab = 0;
    CvMorphState *state = 0;

    CV_FUNCNAME( "icvMorphOp" );

    __BEGIN__;

    CvMorphFunc func = 0;
    CvElementShape shape;
    int i, coi1 = 0, coi2 = 0;
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    CvSize size;
    int type;
    int src_step, dst_step;

    if( !inittab )
    {
        icvInitMorphologyTab( morph_tab + 0, morph_tab + 1, morph_tab + 2,
                              morph_tab + 3, morph_tab + 4, morph_tab + 5 );
        inittab = 1;
    }

    CV_CALL( src = cvGetMat( src, &srcstub, &coi1 ));
    
    if( src != &srcstub )
    {
        srcstub = *src;
        src = &srcstub;
    }

    if( dstarr == srcarr )
    {
        dst = src;
    }
    else
    {
        CV_CALL( dst = cvGetMat( dst, &dststub, &coi2 ));

        if( !CV_ARE_TYPES_EQ( src, dst ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( !CV_ARE_SIZES_EQ( src, dst ))
            CV_ERROR( CV_StsUnmatchedSizes, "" );
    }

    if( dst != &dststub )
    {
        dststub = *dst;
        dst = &dststub;
    }

    if( coi1 != 0 || coi2 != 0 )
        CV_ERROR( CV_BadCOI, "" );

    type = CV_ARR_TYPE( src->type );

    if( element )
    {
        IPPI_CALL(
            icvMorphologyInitAlloc( src->width, CV_ARR_DEPTH(type) == CV_8U ? cv8u : cv32f,
                                 CV_ARR_CN(type), cvSize( element->nCols, element->nRows),
                                 cvPoint( element->anchorX, element->anchorY ),
                                 (CvElementShape) (element->nShiftR), element->values,
                                 &state ));
        shape = (CvElementShape) (element->nShiftR);
        shape = shape < CV_SHAPE_ELLIPSE ? shape : CV_SHAPE_CUSTOM;
    }
    else
    {
        IPPI_CALL(
            icvMorphologyInitAlloc( src->width, CV_ARR_DEPTH(type) == CV_8U ? cv8u : cv32f,
                                  CV_ARR_CN(type), cvSize( 3, 3 ), cvPoint( 1, 1 ),
                                  CV_SHAPE_RECT, 0, &state ));
        shape = CV_SHAPE_RECT;
    }

    func = (CvMorphFunc)(morph_tab[(shape == CV_SHAPE_RECT ? 0 :
                         shape == CV_SHAPE_CROSS ? 1 : 2) * 2 + mop].fn_2d[type]);

    if( !func )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    size = icvGetMatSize( src );

    src_step = src->step;
    dst_step = dst->step;

    if( src_step == 0 )
        src_step = dst_step = size.width * icvPixSize[type];

    for( i = 0; i < iterations; i++ )
    {
        IPPI_CALL( func( src->data.ptr, src_step, dst->data.ptr,
                         dst_step, &size, state, 0 ));
        src = dst;
    }

    __END__;

    icvMorphologyFree( &state );
}



CV_IMPL void
cvErode( const void* src, void* dst, IplConvKernel* element, int iterations )
{
    icvMorphOp( src, dst, element, iterations, 0 );
}


CV_IMPL void
cvDilate( const void* src, void* dst, IplConvKernel* element, int iterations )
{
    icvMorphOp( src, dst, element, iterations, 1 );
}


CV_IMPL void
cvMorphologyEx( const void* src, void* dst,
                void* temp, IplConvKernel* element, CvMorphOp op, int iterations )
{
    CV_FUNCNAME( "cvMorhologyEx" );

    __BEGIN__;

    if( (op == CV_MOP_GRADIENT ||
        (op == CV_MOP_TOPHAT || op == CV_MOP_BLACKHAT) && src == dst) && temp == 0 )
        CV_ERROR( CV_HeaderIsNull, "temp image required" );

    if( temp == src || temp == dst )
        CV_ERROR( CV_HeaderIsNull, "temp image is equal to src or dst" );

    switch (op)
    {
    case CV_MOP_OPEN:
        CV_CALL( cvErode( src, dst, element, iterations ));
        CV_CALL( cvDilate( dst, dst, element, iterations ));
        break;
    case CV_MOP_CLOSE:
        CV_CALL( cvDilate( src, dst, element, iterations ));
        CV_CALL( cvErode( dst, dst, element, iterations ));
        break;
    case CV_MOP_GRADIENT:
        CV_CALL( cvErode( src, temp, element, iterations ));
        CV_CALL( cvDilate( src, dst, element, iterations ));
        CV_CALL( cvSub( dst, temp, dst ));
        break;
    case CV_MOP_TOPHAT:
        CV_CALL( cvErode( src, src != dst ? dst : temp, element, iterations ));
        CV_CALL( cvSub( src, src != dst ? dst : temp, dst ));
        break;
    case CV_MOP_BLACKHAT:
        CV_CALL( cvDilate( src, src != dst ? dst : temp, element, iterations ));
        CV_CALL( cvSub( src != dst ? dst : temp, src, dst ));
        break;
    default:
        CV_ERROR( CV_StsBadArg, "unknown morphological operation" );
    }

    __END__;
}


/* End of file. */
