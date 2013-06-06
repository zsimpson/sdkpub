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
static int  Sobord;

static int  read_param = 0;
static int  data_types = 0;
static double EPSILON = 0.1;

static int fcaSobel( void )
{
    int* KerX;
    int* KerY;
	CvSize KerLens;
    int dx,dy;
    AtsRandState state; 
    double Error = 0;

    IplImage* src8u;
	IplImage* src8s;
	IplImage* src32f;
    IplImage* src16;
    IplImage* dst16;
	IplImage* test16;
	IplImage* dst32f;
	IplImage* test32f;
	IplImage* buf;
    IplConvKernel* KernelXD;
    IplConvKernel* KernelYD;
	IplConvKernel* KernelXG;
    IplConvKernel* KernelYG;
	
	IplConvKernelFP* KXD;
	IplConvKernelFP* KYD;
	IplConvKernelFP* KXG;
	IplConvKernelFP* KYG;


    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Determining which test are needed to run */
        trsCaseRead( &data_types,"/u/s/f/a", "a",
                    "u - unsigned char, s - signed char, f - float, a - all" );
        /* Reading test-parameters */
        trsiRead( &lImageHeight, "45", "Image height" );
        trsiRead( &lImageWidth, "34", "Image width" );
        trsiRead( &Sobord,"7","Size of operator");
    }
    if( data_types != 3 && data_types != 0 ) return TRS_UNDEF;

    KerX =  (int*)icvAlloc((Sobord+2) * sizeof(int));
    KerY =  (int*)icvAlloc((Sobord+2) * sizeof(int));
    
    /* Creating images for testing */
    src8u= cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
	src8s= cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
	src32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
	src16 = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_16S, 1);
    dst16 = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_16S, 1);
	test16 = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_16S, 1);
	buf = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
	dst32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
	test32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
	atsRandInit(&state,0,32,127);
	atsFillRandomImageEx(src8u, &state );
	atsFillRandomImageEx(src8s, &state );
	atsFillRandomImageEx(src32f, &state );

    /* Calculating the kernels */
    dx = 2;
    dy = 0;
	atsCalcKernel(cv8u,dx,dy,Sobord,(char*)KerX,(char*)KerY,&KerLens,CV_ORIGIN_TL);
	KernelXD = iplCreateConvKernel(KerLens.width,1,KerLens.width/2,0,KerX,0);
    KernelYG = iplCreateConvKernel(1,KerLens.height,0,KerLens.height/2,KerY,0);
	KernelXG = iplCreateConvKernel(KerLens.width,1,KerLens.width/2,0,KerY,0);
    KernelYD = iplCreateConvKernel(1,KerLens.height,0,KerLens.height/2,KerX,0);

	    
    /* Calculating the convolution */
	atsConvert(src8u,src16);
	iplSetBorderMode(src16,
                     IPL_BORDER_REPLICATE,
                     IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
                     0);
    iplConvolveSep2D(src16,dst16,KernelXD,KernelYG);
	iplConvolveSep2D(src16,test16,KernelXG,KernelYD);
	iplAdd(test16,dst16,dst16);
	cvLaplace(src8u,test16,Sobord);
	Error += iplNorm(dst16,test16,IPL_C);
	long err =0;
	for(int i=0; i<lImageHeight; i++)
		for(int j=0; j<lImageWidth; j++)
		{
			short a = ((short*)dst16->imageData)[i*dst16->widthStep/2+j];
			short b = ((short*)test16->imageData)[i*test16->widthStep/2+j];
			if(a!=b)
			{
				err++;
			}

		}
	atsConvert(src8s,src16);
	iplSetBorderMode(src16,
                     IPL_BORDER_REPLICATE,
                     IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
                     0);
	
    iplConvolveSep2D(src16,dst16,KernelXD,KernelYG);
	iplConvolveSep2D(src16,test16,KernelXG,KernelYD);
	iplAdd(test16,dst16,dst16);
	cvLaplace(src8s,test16,Sobord);
	Error += iplNorm(dst16,test16,IPL_C);

	atsCalcKernel(IPL_DEPTH_32F,dx,dy,Sobord,(char*)KerX,(char*)KerY,&KerLens,CV_ORIGIN_TL);
	KXD = iplCreateConvKernelFP(KerLens.width,1,KerLens.width/2,0,(float*)KerX);
    KYD = iplCreateConvKernelFP(1,KerLens.width,0,KerLens.width/2,(float*)KerX);
	KXG = iplCreateConvKernelFP(KerLens.width,1,KerLens.width/2,0,(float*)KerY);
    KYG = iplCreateConvKernelFP(1,KerLens.width,0,KerLens.width/2,(float*)KerY);


    iplSetBorderMode(src32f,
                     IPL_BORDER_REPLICATE,
                     IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
                     0);
	
    /* Calculating the convolution */

    iplConvolveSep2DFP(src32f,buf,KXD,KYG);
	iplConvolveSep2DFP(src32f,dst32f,KXG,KYD);
	iplAdd(buf,dst32f,dst32f);
      
	cvLaplace(src32f,test32f,Sobord);
	Error += iplNorm(test32f,dst32f,IPL_C);
	


    /* Free Memory */
    cvReleaseImage( &src8u );
    cvReleaseImage( &src8s );
    cvReleaseImage( &src32f );
    cvReleaseImage( &src16 );
    cvReleaseImage( &dst16 );
    cvReleaseImage( &test16 );
    cvReleaseImage( &dst32f );
    cvReleaseImage( &test32f );
    cvReleaseImage( &buf);

    if(Error>=EPSILON)return TRS_FAIL;
    return TRS_OK;
} /* fcaSobel8uC1R */





void InitALaplace (void)
{
    trsReg( "cvLaplace", TestName, TestClass, fcaSobel );
 
} /* InitASobel */

/* End of file. */
