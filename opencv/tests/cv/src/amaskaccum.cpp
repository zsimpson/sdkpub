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

#include "cvtest.h"

/* Testing parameters */
static char* FuncName[] = 
{
    "cvAccMask",
    "cvSquareAccMask",
    "cvMultiplyAccMask",
    "cvRunningAvgMask"
};
static char* TestName[]    = 
{
    "Linear Accumulating with Mask",
    "Accumulating of Squares with Mask",
    "Accumulating of Products with Mask",
    "Running Average with Mask"
};
static char TestClass[]   = "Algorithm";


static long lImageWidth;
static long lImageHeight;

#define EPSILON 0.00001

static int fcaLinAcc( void )
{
    /* Some Variables */
    
    AtsRandState      state;
    IplImage*         pSrc8u;
    IplImage*         pSrc8s;
    IplImage*         pSrc32f;
    
    IplImage*         pDst;
    IplImage*         pTest;
    IplImage*         pTemp; 
    IplImage*         Mask;
    IplImage*         BitMask;
    
    double Error;
    
    static int  read_param = 0;
    
    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Reading test-parameters */
        trslRead( &lImageHeight, "4", "Image Height" );
        trslRead( &lImageWidth, "4", "Image width" );
    }
    atsRandInit(&state,0,255,127);
    pSrc8u         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
    pSrc8s         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
    pSrc32f        = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pDst           = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTest          = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTemp          = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    Mask           = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U,  1);
    BitMask        = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_1U, 1);
    atsFillRandomImageEx(pSrc8u, &state );
    atsFillRandomImageEx(pSrc8s, &state );
    atsFillRandomImageEx(pSrc32f, &state );
    atsFillRandomImageEx(pDst, &state );
    atsFillRandomImageEx(Mask, &state );
    iplCopy( pDst, pTest );
    iplThreshold(Mask,Mask,125);
    iplGreaterS(Mask,124,BitMask);
    pTemp->maskROI = BitMask;
    
    
    cvAccMask(pSrc8u,pTest,Mask);
    atsConvert(pSrc8u,pTemp);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvAccMask(pSrc8s,pTest,Mask);
    atsConvert(pSrc8s,pTemp);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvAccMask(pSrc32f,pTest,Mask);
    pSrc32f->maskROI = BitMask;
    iplAdd(pDst,pSrc32f,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    
    trsWrite(ATS_SUM, "\nAccuracy   %e\n",EPSILON);
    /*************************************************************************************/
    /*    check 8u                                                                       */
    /*************************************************************************************/
    
    cvReleaseImage( &pSrc8u );
    cvReleaseImage( &pSrc8s );
    cvReleaseImage( &pSrc32f );
    cvReleaseImage( &pDst );
    cvReleaseImage( &pTest);
    cvReleaseImage( &pTemp );
    cvReleaseImage( &Mask );
    
    
    if( Error < EPSILON  ) return trsResult( TRS_OK, "No errors fixed for this text" );
    else return trsResult( TRS_FAIL,"Total fixed %d errors", 1);
} /* fmaAcc */

static int fcaSqrAcc( void )
{
    AtsRandState   	  state;
    IplImage*         pSrc8u;
    IplImage*         pSrc8s;
    IplImage*         pSrc32f;
    
    IplImage*         pDst;
    IplImage*         pTest;
    IplImage*         pTemp; 
    IplImage*         Mask;
    IplImage*         BitMask;
    
    double Error;
    
    static int  read_param = 0;
    
    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Reading test-parameters */
        trslRead( &lImageHeight, "80", "Image Height" );
        trslRead( &lImageWidth, "80", "Image width" );
    }
    atsRandInit(&state,0,255,127);
    pSrc8u   = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
    pSrc8s   = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
    pSrc32f  = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pDst     = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTemp    = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTest    = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    Mask     = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U,  1);
    BitMask  = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_1U, 1);
    atsFillRandomImageEx(pSrc8u, &state );
    atsFillRandomImageEx(pSrc8s, &state );
    atsFillRandomImageEx(pSrc32f, &state );
    atsFillRandomImageEx(pDst, &state );
    atsFillRandomImageEx(Mask, &state );
    iplCopy( pDst, pTest );
    iplThreshold(Mask,Mask,125);
    iplGreaterS(Mask,124,BitMask);
    pTemp->maskROI = BitMask;
    
    cvSquareAccMask(pSrc8u,pTest,Mask);
    atsConvert(pSrc8u,pTemp);
    iplMultiply(pTemp,pTemp,pTemp);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvSquareAccMask(pSrc8s,pTest,Mask);
    atsConvert(pSrc8s,pTemp);
    iplMultiply(pTemp,pTemp,pTemp);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvSquareAccMask(pSrc32f,pTest,Mask);
    pSrc32f->maskROI = BitMask;
    iplMultiply(pSrc32f,pSrc32f,pSrc32f);
    iplAdd(pDst,pSrc32f,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    
    trsWrite(ATS_SUM, "\nAccuracy   %e\n",EPSILON);
    /*************************************************************************************/
    /*    check 8u                                                                       */
    /*************************************************************************************/
    
    cvReleaseImage( &pSrc8u );
    cvReleaseImage( &pSrc8s );
    cvReleaseImage( &pSrc32f );
    cvReleaseImage( &pDst );
    cvReleaseImage( &pTest);
    cvReleaseImage( &pTemp );
    cvReleaseImage( &Mask );
        
    if( Error < EPSILON  ) return trsResult( TRS_OK, "No errors fixed for this text" );
    else return trsResult( TRS_FAIL,"Total fixed %d errors", 1);
} /* fmaAcc */

static int fcaMultAcc( void )
{
    /* Some Variables */
    
    AtsRandState      state;
    IplImage*         pSrcA8u;
    IplImage*         pSrcA8s;
    IplImage*         pSrcA32f;
    IplImage*         pSrcB8u;
    IplImage*         pSrcB8s;
    IplImage*         pSrcB32f;
    
    IplImage*         pDst;
    IplImage*         pTest;
    IplImage*         pTempA;
    IplImage*         pTempB;
    IplImage*         Mask;
    IplImage*         BitMask;
    
    double Error;
    
    static int  read_param = 0;
    
    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Reading test-parameters */
        trslRead( &lImageHeight, "80", "Image Height" );
        trslRead( &lImageWidth, "80", "Image width" );
    }
    atsRandInit(&state,0,255,127);
    pSrcA8u         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
    pSrcA8s         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
    pSrcA32f        = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pSrcB8u         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
    pSrcB8s         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
    pSrcB32f        = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pDst            = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTempA          = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTempB          = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    Mask            = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U,  1);
    BitMask         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_1U, 1);
    
    atsFillRandomImageEx(pSrcA8u, &state );
    atsFillRandomImageEx(pSrcA8s, &state );
    atsFillRandomImageEx(pSrcA32f, &state );
    atsFillRandomImageEx(pSrcB8u, &state );
    atsFillRandomImageEx(pSrcB8s, &state );
    atsFillRandomImageEx(pSrcB32f, &state );
    atsFillRandomImageEx(pDst, &state );
    atsFillRandomImageEx(Mask,&state);
    pTest = cvCloneImage(pDst);
    iplThreshold(Mask,Mask,125);
    iplGreaterS(Mask,124,BitMask);
    pTempA->maskROI = BitMask;
    pTempB->maskROI = BitMask;
    
    cvMultiplyAccMask(pSrcA8u,pSrcB8u,pTest,Mask);
    atsConvert(pSrcA8u,pTempA);
    atsConvert(pSrcB8u,pTempB);
    iplMultiply(pTempA,pTempB,pTempA);
    iplAdd(pDst,pTempA,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvMultiplyAccMask(pSrcA8s,pSrcB8s,pTest,Mask);
    atsConvert(pSrcA8s,pTempA);
    atsConvert(pSrcB8s,pTempB);
    iplMultiply(pTempA,pTempB,pTempA);
    iplAdd(pDst,pTempA,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvMultiplyAccMask(pSrcA32f,pSrcB32f,pTest,Mask);
    iplMultiply(pSrcA32f,pSrcB32f,pTempA);
    iplAdd(pDst,pTempA,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    
    trsWrite(ATS_SUM, "\nAccuracy   %e\n",EPSILON);
    /*************************************************************************************/
    /*    check 8u                                                                       */
    /*************************************************************************************/
    
    
        
    cvReleaseImage( &pSrcA8u );
    cvReleaseImage( &pSrcA8s );
    cvReleaseImage( &pSrcA32f );
    cvReleaseImage( &pSrcB8u );
    cvReleaseImage( &pSrcB8s );
    cvReleaseImage( &pSrcB32f );
    cvReleaseImage( &pDst );
    cvReleaseImage( &pTest);
    cvReleaseImage( &pTempA );
    cvReleaseImage( &pTempB );
    cvReleaseImage( &Mask );
        
    if( Error < EPSILON  ) return trsResult( TRS_OK, "No errors fixed for this text" );
    else return trsResult( TRS_FAIL,"Total fixed %d errors", 1);
} /* fmaAcc */

static int fcaRunAvg( void )
{
    /* Some Variables */
    
    AtsRandState   	  state;
    IplImage*         pSrc8u;
    IplImage*         pSrc8s;
    IplImage*         pSrc32f;
    
    IplImage*         pDst;
    IplImage*         pTest;
    IplImage*		  pTemp;
    IplImage*		  Mask;
    IplImage*	      BitMask;
    
    float alpha =0.05f; 
    double Error;
    
    static int  read_param = 0;
    
    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Reading test-parameters */
        trslRead( &lImageHeight, "80", "Image Height" );
        trslRead( &lImageWidth, "80", "Image width" );
    }
    atsRandInit(&state,0,255,127);
    pSrc8u         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
    pSrc8s         = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
    pSrc32f        = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pDst           = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    pTemp          = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    Mask           = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U,  1);
    BitMask        = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_1U, 1);
    atsFillRandomImageEx(pSrc8u, &state );
    atsFillRandomImageEx(pSrc8s, &state );
    atsFillRandomImageEx(pSrc32f, &state );
    atsFillRandomImageEx(pDst, &state );
    atsFillRandomImageEx(Mask, &state );
    
    pTest = cvCloneImage(pDst);
    iplThreshold(Mask,Mask,125);
    iplGreaterS(Mask,125,BitMask);
    pTemp->maskROI = BitMask;
    pDst->maskROI = BitMask;
    cvRunningAvgMask(pSrc8u,pTest,Mask,alpha);
    atsConvert(pSrc8u,pTemp);
    iplMultiplySFP(pDst,pDst,(1.f-alpha));
    iplMultiplySFP(pTemp,pTemp,alpha);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvRunningAvgMask(pSrc8s,pTest,Mask,alpha);
    atsConvert(pSrc8s,pTemp);
    iplMultiplySFP(pDst,pDst,(1.f-alpha));
    iplMultiplySFP(pTemp,pTemp,alpha);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    cvRunningAvgMask(pSrc32f,pTest,Mask,alpha);
    iplMultiplySFP(pDst,pDst,(1.f-alpha));
    iplMultiplySFP(pSrc32f,pTemp,alpha);
    iplAdd(pDst,pTemp,pDst);
    Error = (long)iplNorm(pTest,pDst,IPL_C);
    
    trsWrite(ATS_SUM, "\nAccuracy   %e\n",EPSILON);
    /*************************************************************************************/
    /*    check 8u                                                                       */
    /*************************************************************************************/
    
    pTemp->maskROI = 0;
    pDst->maskROI = 0;
    
    cvReleaseImage( &pSrc8u );
    cvReleaseImage( &pSrc8s );
    cvReleaseImage( &pSrc32f );
    cvReleaseImage( &pDst );
    cvReleaseImage( &pTest);
    cvReleaseImage( &pTemp );
    cvReleaseImage( &Mask );
    cvReleaseImage( &BitMask );
    
    
    if( Error < EPSILON  ) return trsResult( TRS_OK, "No errors fixed for this text" );
    else return trsResult( TRS_FAIL,"Total fixed %d errors", 1);
} /* fmaAcc */





void InitAMaskAcc( void )
{
    /* Registering test function */
    trsReg( FuncName[0], TestName[0], TestClass, fcaLinAcc );
    trsReg( FuncName[1], TestName[1], TestClass, fcaSqrAcc );
    trsReg( FuncName[2], TestName[2], TestClass, fcaMultAcc );
    trsReg( FuncName[3], TestName[3], TestClass, fcaRunAvg );
} /* InitAAcc */


/* End of file. */
