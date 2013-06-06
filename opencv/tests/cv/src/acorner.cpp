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
static char TestName[] = "Calculating the Convolution with Sobel operators";
static char TestClass[] = "Algorithm";
static int lImageWidth;
static int lImageHeight;
static int  kerSize;
static int  lBlockSize;

static int  read_param = 0;
static int  data_types = 0;
static double EPSILON = 0.01;

static  void calcVals(IplImage* src32f, IplImage* eigenv32f, int kerSize, int lBlockSize)
{

    int* GaussKer;
    int* DiffKer;
	CvSize KerLens;
       
	IplImage* fldstX;
    IplImage* fldstY;
    IplImage* fldstXX;
    IplImage* fldstYY;
    IplImage* fldstXY;

    IplImage* flBluredXX;
    IplImage* flBluredYY;
    IplImage* flBluredXY;
        
    IplConvKernelFP* DiffKernelX;
    IplConvKernelFP* DiffKernelY;
    IplConvKernelFP* GaussKerX;
    IplConvKernelFP* GaussKerY;
    GaussKer =  (int*)icvAlloc((kerSize+2) * sizeof(int));
    DiffKer =  (int*)icvAlloc((kerSize+2) * sizeof(int));
    KerLens.width = kerSize;
    KerLens.height = kerSize;

    /* Creating images for testing */
	fldstX = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    fldstY = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    fldstXX = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    fldstXY = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    fldstYY = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    flBluredXX = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    flBluredXY = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    flBluredYY = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);

	atsCalcKernel(IPL_DEPTH_32F,0,1,kerSize,(char*)GaussKer,(char*)DiffKer,&KerLens,IPL_ORIGIN_TL);
    GaussKerX = iplCreateConvKernelFP(kerSize,1,kerSize/2,0,(float*)GaussKer);
    GaussKerY = iplCreateConvKernelFP(1,kerSize,0,kerSize/2,(float*)GaussKer);

    DiffKernelX = iplCreateConvKernelFP(KerLens.height,1,KerLens.height/2,0,(float*)DiffKer);
    DiffKernelY = iplCreateConvKernelFP(1,KerLens.height,0,KerLens.height/2,(float*)DiffKer);
    iplSetBorderMode(src32f,
                     IPL_BORDER_REPLICATE,
                     IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
                     0);

    iplConvolveSep2DFP(src32f,fldstX,DiffKernelX,GaussKerY);
    iplConvolveSep2DFP(src32f,fldstY,GaussKerX,DiffKernelY);
    iplDeleteConvKernelFP(DiffKernelX);
    iplDeleteConvKernelFP(DiffKernelY);
    iplDeleteConvKernelFP(GaussKerX);
    iplDeleteConvKernelFP(GaussKerY);
    iplMultiply(fldstX, fldstX, fldstXX);
    iplMultiply(fldstY, fldstY, fldstYY);
    iplMultiply(fldstX, fldstY, fldstXY);
    iplSetBorderMode(fldstXX,
        IPL_BORDER_REPLICATE,
        IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
        0);
    iplSetBorderMode(fldstXY,
        IPL_BORDER_REPLICATE,
        IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
        0);
    iplSetBorderMode(fldstYY,
        IPL_BORDER_REPLICATE,
        IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
        0);
    iplBlur( fldstXX, flBluredXX, lBlockSize,lBlockSize,
        (lBlockSize - 1) /2, (lBlockSize - 1) /2);
    iplBlur( fldstXY, flBluredXY, lBlockSize,lBlockSize,
        (lBlockSize - 1) /2, (lBlockSize - 1) /2);
    iplBlur( fldstYY, flBluredYY, lBlockSize,lBlockSize,
        (lBlockSize - 1) /2, (lBlockSize - 1) /2);
    float denom = 1;
    int i;
    for(i = 0; i < kerSize-1;i++)denom *= 2;
    denom = denom*denom * 255;
    denom=1.0f/denom;
    iplMultiplySFP (flBluredXX, flBluredXX, denom );
    iplMultiplySFP (flBluredXY, flBluredXY, denom );
    iplMultiplySFP (flBluredYY, flBluredYY, denom );
     
    for ( i = 0 ; i < lImageHeight; i++ )
    {
        for ( int j = 0; j < lImageWidth ; j++ )
        {
            /* finding eigenvalues of |a b|
                                      |b c|   */
            float a = ((float*)flBluredXX->imageData)[i*flBluredXX->widthStep/4 + j];
            float b = ((float*)flBluredXY->imageData)[i*flBluredXY->widthStep/4 + j];
            float c = ((float*)flBluredYY->imageData)[i*flBluredYY->widthStep/4 + j];
            float l1,l2;
            float det;
            float dmax  = MAX( a , c);
            float dmin  = MIN( a , c);
            dmax *= 0.01f;
            /* if singular matrix  - don't process it */
            if ( dmin < dmax )
            {
                memset(((float*)(eigenv32f->imageData))+i*eigenv32f->widthStep/4 + j, 0, 24); continue;
            }
            if ( fabs(b) < dmax )
            {
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j] = a;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j + 1] = c;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j + 2] = 1.0f;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j + 3] = 0;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j + 4] = 0;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j + 5] = 1.0f;
                continue;
            }
            det = a * c - b * b;
            if ( det < dmax )
            {
                memset(((float*)(eigenv32f->imageData))+i*eigenv32f->widthStep/4 + j, 0, 24); continue;
            }

                float apc = a + c;
                float discr = apc * apc - 4 * det;
                float Sqrt  = (float)sqrt( discr );
                float Inorm1,Inorm2,x1,x2,y1,y2;

                l1 = (apc + Sqrt)/2;
                l2 = (apc - Sqrt)/2;

                x1 = b;
                x2 = (-( a - l1 ));

                y1 = b;
                y2 = (-( a - l2 ));

                Inorm1 = 1.f/(float)sqrt(x1*x1 + x2*x2);
                Inorm2 = 1.f/(float)sqrt(y1*y1 + y2*y2);

                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j] = l1;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j+1] = l2;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j+2] = x1 * Inorm1;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j+3] = x2 * Inorm1;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j+4] = y1 * Inorm2;
                ((float*)(eigenv32f->imageData))[i*eigenv32f->widthStep/4 + 6*j+5] = y2 * Inorm2;
    
            }
        }
      
    cvReleaseImage(&fldstX);
    cvReleaseImage(&fldstY);
    cvReleaseImage(&fldstXX);
    cvReleaseImage(&fldstXY);
    cvReleaseImage(&fldstYY);
    cvReleaseImage(&flBluredXX);
    cvReleaseImage(&flBluredXY);
    cvReleaseImage(&flBluredYY);
    return;
}

static int fcaCorner( void )
{
    long lErrors = 0;
    IplImage* src8u;
    IplImage* src8s;
    IplImage* src32f;
    IplImage* tmpsrc;
    IplImage* eigenv32f;
    IplImage* testdst;

    
    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Determining which test are needed to run */
        trsCaseRead( &data_types,"/u/s/f/a", "a",
                    "u - unsigned char, s - signed char, f - float, a - all" );
        /* Reading test-parameters */
        trsiRead( &lImageHeight, "30", "Image height");
        trsiRead( &lImageWidth, "30", "Image width");
        trsiRead( &kerSize,"5","Size of operator");
        trsiRead( &lBlockSize,"5","Size of average window");
    }
    if( data_types != 3 && data_types != 0 ) return TRS_UNDEF;

    
    /* Creating images for testing */
    src8u = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
    src8s = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
	src32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    tmpsrc = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
	eigenv32f = cvCreateImage(cvSize(6*lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
    testdst = cvCreateImage(cvSize(6*lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);

    atsFillRandomImage(src8u,0, 255);
    atsFillRandomImage(src8s,-128, 127);
	atsFillRandomImage(src32f,-255, 255);

    atsConvert(src8u,tmpsrc);
    calcVals(tmpsrc,eigenv32f,kerSize,lBlockSize);
    cvCornerEigenValsAndVecs(src8u,testdst,kerSize,lBlockSize);
    lErrors += (long)iplNorm(eigenv32f,testdst,IPL_C);
    atsConvert(src8s,tmpsrc);
    calcVals(tmpsrc,eigenv32f,kerSize,lBlockSize);
    cvCornerEigenValsAndVecs(src8s,testdst,kerSize,lBlockSize);
    int err =0;
    int i;
    for(i = 0; i< lImageHeight; i++)
        for(int j = 0; j< 6 * lImageWidth; j++)
        {
            float a  = ((float*)eigenv32f->imageData)[i*eigenv32f->widthStep/4+j];
            float b  = ((float*)testdst->imageData)[i*testdst->widthStep/4+j];
            if(fabs(a-b)>0.01)
            err++;
            
        }
    lErrors += (long)iplNorm(eigenv32f,testdst,IPL_C);
    calcVals(src32f,eigenv32f,kerSize,lBlockSize);
    cvCornerEigenValsAndVecs(src32f,testdst,kerSize,lBlockSize);
    err=0;
    for( i = 0; i< lImageHeight; i++)
        for(int j = 0; j< 6 * lImageWidth; j++)
        {
            float a  = ((float*)eigenv32f->imageData)[i*eigenv32f->widthStep/4+j];
            float b  = ((float*)testdst->imageData)[i*testdst->widthStep/4+j];
            if(fabs(a-b)>0.01)
            err++;
            
        }
   lErrors += (long)iplNorm(eigenv32f,testdst,IPL_C);
   if(lErrors)return TRS_FAIL;
   return TRS_OK;
} /* fcaSobel8uC1R */

void InitACorner(void)
{
    trsReg( "cvCorner", TestName, TestClass, fcaCorner );

} /* InitASobel */








