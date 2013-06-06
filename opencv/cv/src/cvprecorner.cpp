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

#define BUFF_SIZE  4096
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     icvPreCornerDetect8sC1R
//    Purpose:  Calculating _CvConvStatetraint image for corner detection
//             Dx^2 * Dyy + Dxx * Dy^2 - 2 * Dx * Dy * Dxy
//    Context:
//    Parameters:
//              pSrc       - pointer to the source image
//              srcStep    - width of the full Src image in bytes
//              corner     - pointer to the image to be filled using expr. (1)
//              cornerStep - it's step in bytes
//              roi        - roi size in pixels
//              opSize     - Sobel operator aperture size - 1
//    Returns:
//              CV_NO_ERR if all ok or error code
//F*/
IPCVAPI_IMPL( CvStatus, icvPreCornerDetect_8u32f_C1R, ( const uchar *pSrc, int SrcStep,
                                                        float *corner, int cornerStep,
                                                        CvSize roi, int kerSize) )
{
    /* Some Variables */
    int BufStep = roi.width;
    int BufByteStep = roi.width * sizeof( short );
    int i, j;


    /* Buffers for storing resultant convolutions */
    short *ShBufX;
    short *ShBufY;
    short *ShBufXX;
    short *ShBufXY;
    short *ShBufYY;
	float denom = 1;
    CvSize curROI = roi;

    /* convolution structures */
    _CvConvState *ConvSX;
    _CvConvState *ConvSY;
    _CvConvState *ConvSXX;
    _CvConvState *ConvSXY;
    _CvConvState *ConvSYY;



    /* Check Bad Arguments */
    if( (pSrc == NULL) || (corner == NULL) )
        return CV_NULLPTR_ERR;
    if( (SrcStep <= 0) || (cornerStep <= 0) )
        return CV_BADSIZE_ERR;
    if( (roi.width <= 0) || (roi.height <= 0) )
        return CV_BADSIZE_ERR;
    if( (kerSize <= 0) && (kerSize != -1) )
        return CV_BADFACTOR_ERR;
    if( (cornerStep & 3) )
        return CV_BADFACTOR_ERR;


	for(i = 0; i < kerSize-1;i++)denom *= 2;
    denom = denom*denom * denom *255*255;
    denom=1.0f/denom;
    /* Buffers for storing resultant convolutions */
    ShBufX = (short *) icvAlloc( BufByteStep * roi.height);
    ShBufY = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufXX = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufXY = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufYY = (short *) icvAlloc( BufByteStep * roi.height );

    icvSobelInitAlloc( roi.width, cv8u, kerSize, CV_ORIGIN_TL, 1, 0, &ConvSX );
    icvSobelInitAlloc( roi.width, cv8u, kerSize, CV_ORIGIN_TL, 0, 1, &ConvSY );
    icvSobelInitAlloc( roi.width, cv8u, kerSize, CV_ORIGIN_TL, 2, 0, &ConvSXX );
    icvSobelInitAlloc( roi.width, cv8u, kerSize, CV_ORIGIN_TL, 1, 1, &ConvSXY );
    icvSobelInitAlloc( roi.width, cv8u, kerSize, CV_ORIGIN_TL, 0, 2, &ConvSYY );
    icvSobel_8u16s_C1R( pSrc, SrcStep, (short *) ShBufX, BufByteStep, &curROI, ConvSX, 0 );
    icvSobel_8u16s_C1R( pSrc, SrcStep, (short *) ShBufY, BufByteStep, &curROI, ConvSY, 0 );
    icvSobel_8u16s_C1R( pSrc, SrcStep, (short *) ShBufXX, BufByteStep, &curROI, ConvSXX, 0 );
    icvSobel_8u16s_C1R( pSrc, SrcStep, (short *) ShBufXY, BufByteStep, &curROI, ConvSXY, 0 );
    icvSobel_8u16s_C1R( pSrc, SrcStep, (short *) ShBufYY, BufByteStep, &curROI, ConvSYY, 0 );
    icvConvolFree( &ConvSX );
    icvConvolFree( &ConvSY );
    icvConvolFree( &ConvSXX );
    icvConvolFree( &ConvSXY );
    icvConvolFree( &ConvSYY );


    /* Main Loop */
    cornerStep >>= 2;

    int ind = 0;

    for( i = 0; i < roi.height; i++ )
    {
        for( j = 0; j < roi.width; j++ )
        {

            float dx = ShBufX[ind + j];
            float dx2 = dx * dx;
            float dy = ShBufY[ind + j];
            float dy2 = dy * dy;

            corner[j] = denom*(dx2 * ShBufYY[ind + j] +
                dy2 * ShBufXX[ind + j] - 2 * dx * dy * ShBufXY[ind + j]);
            /* _CvConvStatetraint computed */

        }
        corner += cornerStep;
        ind += BufStep;
    }

    icvFree( &ShBufX );
    icvFree( &ShBufY );
    icvFree( &ShBufXX );
    icvFree( &ShBufXY );
    icvFree( &ShBufYY );

    return CV_NO_ERR;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     icvPreCornerDetect8sC1R
//    Purpose:  Calculating _CvConvStatetraint image for corner detection
//             Dx^2 * Dyy + Dxx * Dy^2 - 2 * Dx * Dy * Dxy
//    Context:
//    Parameters:
//              pSrc       - pointer to the source image
//              srcStep    - width of the full Src image in bytes
//              corner     - pointer to the image to be filled using expr. (1)
//              cornerStep - it's step in bytes
//              roi        - roi size in pixels
//              opSize     - Sobel operator aperture size - 1
//    Returns:
//              CV_NO_ERR if all ok or error code
//F*/
IPCVAPI_IMPL( CvStatus, icvPreCornerDetect_8s32f_C1R, ( const char *pSrc, int SrcStep,
                                                        float *corner, int cornerStep,
                                                        CvSize roi, int kerSize) )
{
    /* Some Variables */
    int BufStep = roi.width;
    int BufByteStep = roi.width * sizeof( short );
    int i, j;


    /* Buffers for storing resultant convolutions */
    short *ShBufX;
    short *ShBufY;
    short *ShBufXX;
    short *ShBufXY;
    short *ShBufYY;
	float denom = 1;
    CvSize curROI = roi;

    /* convolution structures */
    _CvConvState *ConvSX;
    _CvConvState *ConvSY;
    _CvConvState *ConvSXX;
    _CvConvState *ConvSXY;
    _CvConvState *ConvSYY;



    /* Check Bad Arguments */
    if( (pSrc == NULL) || (corner == NULL) )
        return CV_NULLPTR_ERR;
    if( (SrcStep <= 0) || (cornerStep <= 0) )
        return CV_BADSIZE_ERR;
    if( (roi.width <= 0) || (roi.height <= 0) )
        return CV_BADSIZE_ERR;
    if( (kerSize <= 0) && (kerSize != -1) )
        return CV_BADFACTOR_ERR;
    if( (cornerStep & 3) )
        return CV_BADFACTOR_ERR;


	for(i = 0; i < kerSize-1;i++)denom *= 2;
    denom = denom*denom * denom *255*255;
    denom=1.0f/denom;
    /* Buffers for storing resultant convolutions */
    ShBufX = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufY = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufXX = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufXY = (short *) icvAlloc( BufByteStep * roi.height );
    ShBufYY = (short *) icvAlloc( BufByteStep * roi.height );

    icvSobelInitAlloc( roi.width, cv8s, kerSize, CV_ORIGIN_TL, 1, 0, &ConvSX );
    icvSobelInitAlloc( roi.width, cv8s, kerSize, CV_ORIGIN_TL, 0, 1, &ConvSY );
    icvSobelInitAlloc( roi.width, cv8s, kerSize, CV_ORIGIN_TL, 2, 0, &ConvSXX );
    icvSobelInitAlloc( roi.width, cv8s, kerSize, CV_ORIGIN_TL, 1, 1, &ConvSXY );
    icvSobelInitAlloc( roi.width, cv8s, kerSize, CV_ORIGIN_TL, 0, 2, &ConvSYY );
    icvSobel_8s16s_C1R( pSrc, SrcStep, (short *) ShBufX, BufByteStep, &curROI, ConvSX, 0 );
    icvSobel_8s16s_C1R( pSrc, SrcStep, (short *) ShBufY, BufByteStep, &curROI, ConvSY, 0 );
    icvSobel_8s16s_C1R( pSrc, SrcStep, (short *) ShBufXX, BufByteStep, &curROI, ConvSXX, 0 );
    icvSobel_8s16s_C1R( pSrc, SrcStep, (short *) ShBufXY, BufByteStep, &curROI, ConvSXY, 0 );
    icvSobel_8s16s_C1R( pSrc, SrcStep, (short *) ShBufYY, BufByteStep, &curROI, ConvSYY, 0 );
    icvConvolFree( &ConvSX );
    icvConvolFree( &ConvSY );
    icvConvolFree( &ConvSXX );
    icvConvolFree( &ConvSXY );
    icvConvolFree( &ConvSYY );


    /* Main Loop */
    cornerStep >>= 2;

    int ind = 0;

    for( i = 0; i < roi.height; i++ )
    {
        for( j = 0; j < roi.width; j++ )
        {

            float dx = ShBufX[ind + j];
            float dx2 = dx * dx;
            float dy = ShBufY[ind + j];
            float dy2 = dy * dy;

            corner[j] = denom*(dx2 * ShBufYY[ind + j] +
                dy2 * ShBufXX[ind + j] - 2 * dx * dy * ShBufXY[ind + j]);
            /* _CvConvStatetraint computed */

        }
        corner += cornerStep;
        ind += BufStep;
    }

    icvFree( &ShBufX );
    icvFree( &ShBufY );
    icvFree( &ShBufXX );
    icvFree( &ShBufXY );
    icvFree( &ShBufYY );

    return CV_NO_ERR;
}


IPCVAPI_IMPL( CvStatus, icvPreCornerDetect_32f_C1R, ( const float *pSrc, int SrcStep,
                                                      float *corner, int cornerStep,
                                                      CvSize roi, int kerSize ))
{
    /* Some Variables */
    int BufStep = roi.width;
    int BufByteStep = roi.width * sizeof( float );
    int i, j;


    /* Buffers for storing resultant convolutions */
    float *ShBufX;
    float *ShBufY;
    float *ShBufXX;
    float *ShBufXY;
    float *ShBufYY;
	float denom = 1;
    CvSize curROI = roi;

    /* convolution structures */
    _CvConvState *ConvSX;
    _CvConvState *ConvSY;
    _CvConvState *ConvSXX;
    _CvConvState *ConvSXY;
    _CvConvState *ConvSYY;

    /* Check Bad Arguments */
    if( (pSrc == NULL) || (corner == NULL) )
        return CV_NULLPTR_ERR;
    if( (SrcStep <= 0) || (cornerStep <= 0) )
        return CV_BADSIZE_ERR;
    if( (roi.width <= 0) || (roi.height <= 0) )
        return CV_BADSIZE_ERR;
    if( (kerSize <= 0) && (kerSize != -1) )
        return CV_BADFACTOR_ERR;
    if( (cornerStep & 3) )
        return CV_BADFACTOR_ERR;
	for(i = 0; i < kerSize-1;i++)denom *= 2;
    denom = denom*denom * denom *255*255;
    denom=1.0f/denom;



    /* Buffers for storing resultant convolutions */
    ShBufX = (float *) icvAlloc( BufByteStep * roi.height );
    ShBufY = (float *) icvAlloc( BufByteStep * roi.height );
    ShBufXX = (float *) icvAlloc( BufByteStep * roi.height );
    ShBufXY = (float *) icvAlloc( BufByteStep * roi.height );
    ShBufYY = (float *) icvAlloc( BufByteStep * roi.height );

    icvSobelInitAlloc( roi.width, cv32f, kerSize, CV_ORIGIN_TL, 1, 0, &ConvSX );
    icvSobelInitAlloc( roi.width, cv32f, kerSize, CV_ORIGIN_TL, 0, 1, &ConvSY );
    icvSobelInitAlloc( roi.width, cv32f, kerSize, CV_ORIGIN_TL, 2, 0, &ConvSXX );
    icvSobelInitAlloc( roi.width, cv32f, kerSize, CV_ORIGIN_TL, 1, 1, &ConvSXY );
    icvSobelInitAlloc( roi.width, cv32f, kerSize, CV_ORIGIN_TL, 0, 2, &ConvSYY );
    icvSobel_32f_C1R( pSrc, SrcStep, (float *) ShBufX, BufByteStep, &curROI, ConvSX, 0 );
    icvSobel_32f_C1R( pSrc, SrcStep, (float *) ShBufY, BufByteStep, &curROI, ConvSY, 0 );
    icvSobel_32f_C1R( pSrc, SrcStep, (float *) ShBufXX, BufByteStep, &curROI, ConvSXX, 0 );
    icvSobel_32f_C1R( pSrc, SrcStep, (float *) ShBufXY, BufByteStep, &curROI, ConvSXY, 0 );
    icvSobel_32f_C1R( pSrc, SrcStep, (float *) ShBufYY, BufByteStep, &curROI, ConvSYY, 0 );
    icvConvolFree( &ConvSX );
    icvConvolFree( &ConvSY );
    icvConvolFree( &ConvSXX );
    icvConvolFree( &ConvSXY );
    icvConvolFree( &ConvSYY );


    /* Main Loop */
    cornerStep >>= 2;

    int ind = 0;

    for( i = 0; i < roi.height; i++ )
    {
        for( j = 0; j < roi.width; j++ )
        {

            float dx = ShBufX[ind + j];
            float dx2 = dx * dx;
            float dy = ShBufY[ind + j];
            float dy2 = dy * dy;

            corner[j] = denom*(dx2 * ShBufYY[ind + j] +
                dy2 * ShBufXX[ind + j] - 2 * dx * dy * ShBufXY[ind + j]);
            /* _CvConvStatetraint computed */

        }
        corner += cornerStep;
        ind += BufStep;
    }

    icvFree( &ShBufX );
    icvFree( &ShBufY );
    icvFree( &ShBufXX );
    icvFree( &ShBufXY );
    icvFree( &ShBufYY );

    return CV_NO_ERR;
}
