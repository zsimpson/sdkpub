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
static char TestName[] = "Calculating the Convolution with Scharr operators";
static char TestClass[] = "Algorithm";
static int lImageWidth;
static int lImageHeight;
static int lMaxImageSize;
static int lMinImageSize;
static int lTestNum;

static int  Sobord;

static int  read_param = 0;
static int  data_types = 0;
static double EPSILON = 0.1;

static int fcaScharr( void )
{
    int KerX[15];
    int KerY[15];
	CvSize KerLens;
    int dx,dy;
    AtsRandState state;
	AtsRandState sizegen;
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
    IplConvKernel* KernelX;
    IplConvKernel* KernelY;
	IplConvKernelFP* KX;
	IplConvKernelFP* KY;

    /* Initialization global parameters */
    if( !read_param )
    {
        read_param = 1;
        /* Determining which test are needed to run */
        trsCaseRead( &data_types,"/u/s/f/a", "a",
                    "u - unsigned char, s - signed char, f - float, a - all" );
        /* Reading test-parameters */
        trsiRead( &lMinImageSize, "16", "Image height" );
        trsiRead( &lMaxImageSize, "256", "Image width" );
		trsiRead( &lTestNum, "20", "Test count" );
    }
    if( data_types != 3 && data_types != 0 ) return TRS_UNDEF;
    atsRandInit(&sizegen,lMinImageSize,lMaxImageSize,0);
    /* Creating images for testing */
	for(int i = 0; i < lTestNum; i++)
	{
		lImageWidth = atsRand32s(&sizegen);
		lImageHeight = atsRand32s(&sizegen);
	    src8u= cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8U, 1);
		src8s= cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_8S, 1);
		src32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
		src16 = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_16S, 1);
		dst16 = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_16S, 1);
		test16 = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_16S, 1);
		buf = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
		dst32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
		test32f = cvCreateImage(cvSize(lImageWidth, lImageHeight), IPL_DEPTH_32F, 1);
		atsRandInit(&state,0,64,32);
		atsFillRandomImageEx(src8u, &state );
		atsFillRandomImageEx(src8s, &state );
		atsFillRandomImageEx(src32f, &state );
	

		/* Calculating the kernels */
		for(dx = 0; dx<=1; dx++)
		{
			dy=1-dx;
			atsCalcKernel(cv8u,dx,dy,CV_SCHARR,(char*)KerX,(char*)KerY,&KerLens,CV_ORIGIN_TL);
			KernelX = iplCreateConvKernel(KerLens.width,1,KerLens.width/2,0,KerX,0);
			KernelY = iplCreateConvKernel(1,KerLens.height,0,KerLens.height/2,KerY,0);

			/* Calculating the convolution */
			atsConvert(src8u,src16);
			iplSetBorderMode(src16,
			IPL_BORDER_REPLICATE,
			IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
			0);
			iplConvolveSep2D(src16,dst16,KernelX,KernelY);
			cvSobel(src8u,test16,dx,dy,CV_SCHARR);
			Error += iplNorm(dst16,test16,IPL_C);

			atsConvert(src8s,src16);
			iplSetBorderMode(src16,
			IPL_BORDER_REPLICATE,
			IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
			0);
			iplSetBorderMode(src16,
			IPL_BORDER_REPLICATE,
			IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
			0);
			iplConvolveSep2D(src16,dst16,KernelX,KernelY);
			cvSobel(src8s,test16,dx,dy,CV_SCHARR);
			Error += iplNorm(dst16,test16,IPL_C);

			atsCalcKernel(IPL_DEPTH_32F,dx,dy,CV_SCHARR,(char*)KerX,(char*)KerY,&KerLens,CV_ORIGIN_TL);
			KX = iplCreateConvKernelFP(KerLens.width,1,KerLens.width/2,0,(float*)KerX);
			KY = iplCreateConvKernelFP(1,KerLens.height,0,KerLens.height/2,(float*)KerY);
			iplSetBorderMode(src32f,
							IPL_BORDER_REPLICATE,
							IPL_SIDE_TOP|IPL_SIDE_BOTTOM|IPL_SIDE_RIGHT|IPL_SIDE_LEFT,
							0);


			/* Calculating the convolution */
			iplConvolveSep2DFP(src32f,dst32f,KX,KY);
			cvSobel(src32f,test32f,dx,dy,CV_SCHARR);
			/*for(i = 0; i<lImageHeight; i++)
				for(int j = 0; j<lImageWidth; j++)
					{
						float a = ((float*)(dst32f->imageData))[i*dst32f->widthStep/4+j];
						float b = ((float*)(test32f->imageData))[i*test32f->widthStep/4+j];
					}
				*/
			Error += iplNorm(test32f,dst32f,IPL_C);
			iplDeleteConvKernel(KernelX);
			iplDeleteConvKernel(KernelY);
			iplDeleteConvKernelFP(KX);
			iplDeleteConvKernelFP(KY);
		}
	 
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
	}

    if(Error/lTestNum>=EPSILON)return TRS_FAIL;
    return TRS_OK;
} /* fcaSobel8uC1R */





void InitAScharr(void)
{
    trsReg( "cvScharr", TestName, TestClass, fcaScharr);
 
} /* InitASobel */

/* End of file. */
