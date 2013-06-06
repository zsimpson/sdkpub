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
/* 
extern "C"{
	#include "HighGUI.h"
}
*/

static char cTestName[] = "Histogram of contrast calculation";

static char cTestClass[] = "Algorithm";

static char cFuncName[] = "cvCalcContrastHist";

static int aCalcContrastHist()
{

    CvPoint *cp;
	CvPoint *cp2;

	CvHistogram *hist;
	int hdim[2] = {256, 256};
	float *thresh[2];

	int idx_min, idx_max;
	float value_min, value_max; 

/*    CvPoint cp[] ={0,0, 5,5, 5,0, 0,5};*/
/*    CvPoint cp[] ={5,0, 10,5, 5,10, 0,5};*/
/*	CvPoint cp[] ={0,0, 5,5, 5,0, 10,5, 10,0, 15,5, 15,0};*/

    int width = 128;
    int height = 128;
    int kp = 5;
    int nPoints2 = 20;

    int fi = 0;
    int a2 = 15;
    int b2 = 15;
	int xc,yc, xc2, yc2;
	
    double pi = 3.1415926;

	double lower, upper;
   	unsigned seed;
    char rand;
	AtsRandState state;

    int l,i,j;

    IplImage *imInput, *imThresh;
    CvSize size;

    int code = TRS_OK;

/* read tests params */
    if(!trsiRead( &width, "128", "image width" ))
        return TRS_UNDEF;
    if(!trsiRead( &height, "128", "image height" ))
        return TRS_UNDEF;

/*  initialized image*/
    l = width*height*sizeof(uchar);

    cp = (CvPoint*) trsmAlloc(nPoints2*sizeof(CvPoint));
	cp2 = (CvPoint*) trsmAlloc(nPoints2*sizeof(CvPoint));

    xc = (int)( width/4.);
    yc = (int)( height/4.);

	xc2 = (int)( 3*width/4.);
    yc2 = (int)( 3*height/4.);

    kp = nPoints2;

    size.width = width;
    size.height = height;

    int xmin = width;
    int ymin = height;
    int xmax = 0;
    int ymax = 0;
	
	
    for(i=0;i<nPoints2;i++)
    {
        cp[i].x = (int)(a2*cos(2*pi*i/nPoints2)*cos(2*pi*fi/360.))-
        (int)(b2*sin(2*pi*i/nPoints2)*sin(2*pi*fi/360.))+xc;
        if(xmin> cp[i].x) xmin = cp[i].x;
        if(xmax< cp[i].x) xmax = cp[i].x;
        cp[i].y = (int)(a2*cos(2*pi*i/nPoints2)*sin(2*pi*fi/360.))+
                    (int)(b2*sin(2*pi*i/nPoints2)*cos(2*pi*fi/360.))+yc;
        if(ymin> cp[i].y) ymin = cp[i].y;
        if(ymax< cp[i].y) ymax = cp[i].y;

		cp2[i].x = (int)(a2*cos(2*pi*i/nPoints2)*cos(2*pi*fi/360.))-
        (int)(b2*sin(2*pi*i/nPoints2)*sin(2*pi*fi/360.))+xc2;
        if(xmin> cp2[i].x) xmin = cp2[i].x;
        if(xmax< cp2[i].x) xmax = cp2[i].x;
        cp2[i].y = (int)(a2*cos(2*pi*i/nPoints2)*sin(2*pi*fi/360.))+
                    (int)(b2*sin(2*pi*i/nPoints2)*cos(2*pi*fi/360.))+yc2;
        if(ymin> cp2[i].y) ymin = cp2[i].y;
        if(ymax< cp2[i].y) ymax = cp2[i].y;

    }

    if(xmax>width||xmin<0||ymax>height||ymin<0) return TRS_FAIL;
    
/*  IPL image moment calculation  */
/*  create image  */
    imInput = atsCreateImage( size.width,  size.height,   IPL_DEPTH_8U, 1, 0 );
	imThresh = atsCreateImage( size.width,  size.height,   IPL_DEPTH_8U, 1, 0 );

	int bgrn = 30;
	int signal = 130;
	int signal2 = 210;
	
    memset(imInput->imageData,bgrn,l);

    cvFillPoly(imInput, &cp, &kp, 1, signal);
	cvFillPoly(imInput, &cp2, &kp, 1, signal2);
/*
	named_window("input image", 1);
	named_window("binary image", 1);
*/

/*  do noise   */
    upper = 20;
    lower = -upper;
    seed = 345753;
    atsRandInit( &state, lower, upper, seed );

	uchar *input = (uchar*)imInput->imageData;

	int step = imInput->widthStep;

    for(i = 0; i<size.height; i++, input+=step)
    {
		 for(j = 0; j<size.width; j++)
         {
			    atsbRand8s( &state, &rand, 1);   
//				rand = 0;
				input[j] = (uchar)(input[j] + rand);
         }
    }

	hist = cvCreateHist ( 1, hdim, CV_HIST_ARRAY );

	thresh[0] = (float *) trsmAlloc(2*sizeof(float));

	thresh[0][0]  = -0.5;
	thresh[0][1]  = 255.5;

	cvSetHistThresh( hist, thresh, 1);

	cvCalcContrastHist( &imInput, hist, 0, 0);

	cvGetMinMaxHistValue( hist, &value_min, &value_max, &idx_min, &idx_max );

	if(abs(idx_max - 150) > 6) code = TRS_FAIL;  

	trsWrite( ATS_CON | ATS_LST | ATS_SUM, "idx_max =%d  value_max =%f\n", idx_max, value_max); 

	double threshold = (double)idx_max;
	cvThreshold( imInput, imThresh, threshold, (double)255, CV_THRESH_BINARY_INV); 
/*
	show_iplimage("input image", imInput);
	show_iplimage("binary image", imThresh);
    wait_key(0);
*/


	cvCalcContrastHist( &imInput, hist, 0, imThresh);

	idx_max = 0;
	value_max = 0;

	cvGetMinMaxHistValue( hist, &value_min, &value_max, &idx_min, &idx_max );

	if(abs(idx_max - 75) > 6) code = TRS_FAIL;  

/*
	threshold = (double)idx_max;
	cvThreshold( imInput, imThresh, threshold, (double)255, CV_THRESH_BINARY_INV); 

	show_iplimage("binary image", imThresh);
    wait_key(0);
*/

	atsReleaseImage(imInput);
	atsReleaseImage(imThresh);
    cvReleaseHist( &hist );

	trsWrite( ATS_CON | ATS_LST | ATS_SUM, "idx_max =%d  value_max =%f\n", idx_max, value_max); 
/*
	destroy_window("input image");
	destroy_window("binary image");
*/		
    trsFree(thresh[0]);
	trsFree(cp);
//    _getch();    
    return code;
}


void InitACalcContrastHist( void )
{
/* Test Registartion */
    trsReg(cFuncName,cTestName,cTestClass,aCalcContrastHist); 
} /* InitACalcContrastHist */

/* End of file. */