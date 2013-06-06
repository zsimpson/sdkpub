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

#include "wrmacro.h"

using namespace CV::FrontEnd;
using namespace CV;

/*void wrCopyImage(const CV::FrontEnd::ArgValType& argvalhandle,
			CV::FrontEnd::ReturnValType& returnvalhandle) {

	int mrows, ncols, orig_size, channels, depth;
	void* data;

	argvalhandle.verify_nargin(2);
	argvalhandle.verify_image(1,"cvCopyImage", mrows, ncols,
							  orig_size, channels, depth, &data);

	returnvalhandle.plhs_[0] = mxDuplicateArray(argvalhandle.prhs_[1]);

	return;
}*/

/*void wrErode(const CV::FrontEnd::ArgValType& argvalhandle,
				 CV::FrontEnd::ReturnValType& returnvalhandle) {
	
	int mrows, ncols, orig_size, channels, depth, orig_step;
	void *data,*kern_arr,*psrc,*pdst;
	IplConvKernel *kernel;
	CvElementShape shape;

	IplImage *src, *dst,
		*planeR, *planeG, *planeB,
		*dstplaneR,*dstplaneG,*dstplaneB;
	
	argvalhandle.verify_nargin(5);
	
	argvalhandle.verify_image(1,"cvErode", mrows, ncols,
		orig_size, channels, depth, &data);

	argvalhandle.verify_numeric(2,"cvErode",1,4);
	int nx = argvalhandle.get_numeric(2,0);
	int ny = argvalhandle.get_numeric(2,1);
	int nx0 = argvalhandle.get_numeric(2,2);
	int ny0 = argvalhandle.get_numeric(2,3);

	Object_Type_Code type = argvalhandle.verify_numeric_or_char(3,"cvErode",nx,ny);

	if (type == NUMERIC)
	{
		shape = CV_SHAPE_CUSTOM;
		kern_arr = mxMalloc(4*nx*ny);
		argvalhandle.get_numeric_array(3,nx*ny,(int*)kern_arr);

		kernel = cvCreateStructuringElementEx( nx, ny, nx0, ny0, shape, (int*)kern_arr);
		mxFree(kern_arr);

	} else
	{
		char ch = argvalhandle.get_char(3,0);

		switch (ch)
		{
		case 'r':
			shape = CV_SHAPE_RECT;
		break;
		case 'c':
			shape = CV_SHAPE_CROSS;
		break;
		case 'e':
			shape = CV_SHAPE_ELLIPSE;
		break;
		default :
			ostringstream ostr;
			ostr << "CvErode" << " must have a defined char - 'r', 'c'  or 'e' in " 
				<< 3 << " argument";
			throw_error(ostr.str());
		break;
		}

		kern_arr = (void*)0;
		kernel = cvCreateStructuringElementEx( nx, ny, nx0, ny0, shape, (int*)kern_arr);
	}

	argvalhandle.verify_numeric(4,"cvErode",1,1);
	int n = argvalhandle.get_numeric(4,0);

	returnvalhandle.verify_nargout(1);

	//-----------------------------------------------------------------

	returnvalhandle.plhs_[0] = mxDuplicateArray(argvalhandle.prhs_[1]);
		
	void *DstData = mxGetPr(returnvalhandle.plhs_[0]);
	CvSize sz = {mrows, ncols};
	orig_step = orig_size / sz.height;

	if (channels == 3)
	{
		orig_step/=3;
		planeR = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(planeR, data, orig_step);
		
		planeG = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(planeG, ((char*)data) + orig_size / 3, orig_step);
		
		planeB = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(planeB, ((char*)data) + 2 * orig_size / 3, orig_step);
		
		src = cvCreateImageHeader(sz, depth, 3);
		psrc = calloc(1,orig_size);
		cvSetImageData(src, psrc, orig_step*3);
		
		cvCvtPlaneToPix(planeR,planeG,planeB,NULL,src);
		
		//pt1.x = 0; pt1.y = 0;
		//pt2.x = 3; pt2.y = 4;
		//cvRectangle( src, pt1, pt2, RGB(255,0,0), 1 );
		
		dst = cvCreateImageHeader(sz, depth, 3);
		pdst = calloc(1,orig_size);
		cvSetImageData(dst, pdst, orig_step*3);
		
		//-----------------------------------
		
		//cvDilate(src, dst,kernel, n);
		//cvErode(src, dst, &ker, n);
		cvErode(src, dst, kernel, n);
		
		//-----------------------------------
		
		dstplaneR = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dstplaneR, DstData, orig_step);
		
		dstplaneG = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dstplaneG, ((char*)DstData) + orig_size / 3, orig_step);
		
		dstplaneB = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dstplaneB, ((char*)DstData) + 2 * orig_size / 3, orig_step);
		
		//dst = cvCreateImageHeader(sz, depth, 3);
		//cvSetImageData(dst, DstData, orig_step*3);
		
		cvCvtPixToPlane(dst,dstplaneR,dstplaneG,dstplaneB,NULL);
		
		//cvvNamedWindow( "dst",  0);
		//cvvShowImage( "dst", dst );
		//cvvWaitKey("dst");
		
		free(psrc);
		free(pdst);
	} else 
	{
		src = cvCreateImageHeader(sz, depth, 1);
		psrc = calloc(1,orig_size);
		cvSetImageData(src, psrc, orig_step);
		
		dst = cvCreateImageHeader(sz, depth, 1);
		pdst = calloc(1,orig_size);
		cvSetImageData(dst, pdst, orig_step);
		
		//-----------------------------------
		
		cvErode(src, dst,kernel, n);
		
		//-----------------------------------
		
		//cvvNamedWindow( "dst",  0);
		//cvvShowImage( "dst", dst );
		//cvvWaitKey("dst");
	}
	
	cvReleaseStructuringElement(&kernel);
	cvReleaseImageHeader(&src);
	cvReleaseImageHeader(&dst);
	

	return;	
}

void wrDilate(const CV::FrontEnd::ArgValType& argvalhandle,
				 CV::FrontEnd::ReturnValType& returnvalhandle) {
int mrows, ncols, orig_size, channels, depth, orig_step;
	void *data,*kern_arr,*psrc,*pdst;
	IplConvKernel *kernel;
	CvElementShape shape;

	IplImage *src, *dst,
		*planeR, *planeG, *planeB,
		*dstplaneR,*dstplaneG,*dstplaneB;
	
	argvalhandle.verify_nargin(5);
	
	argvalhandle.verify_image(1,"cvDilate", mrows, ncols,
		orig_size, channels, depth, &data);

	argvalhandle.verify_numeric(2,"cvDilate",1,4);
	int nx = argvalhandle.get_numeric(2,0);
	int ny = argvalhandle.get_numeric(2,1);
	int nx0 = argvalhandle.get_numeric(2,2);
	int ny0 = argvalhandle.get_numeric(2,3);

	Object_Type_Code type = argvalhandle.verify_numeric_or_char(3,"cvDilate",nx,ny);

	if (type == NUMERIC)
	{
		shape = CV_SHAPE_CUSTOM;
		kern_arr = mxMalloc(4*nx*ny);
		argvalhandle.get_numeric_array(3,nx*ny,(int*)kern_arr);

		kernel = cvCreateStructuringElementEx( nx, ny, nx0, ny0, shape, (int*)kern_arr);
		mxFree(kern_arr);

	} else
	{
		char ch = argvalhandle.get_char(3,0);

		switch (ch)
		{
		case 'r':
			shape = CV_SHAPE_RECT;
		break;
		case 'c':
			shape = CV_SHAPE_CROSS;
		break;
		case 'e':
			shape = CV_SHAPE_ELLIPSE;
		break;
		default :
			ostringstream ostr;
			ostr << "cvDilate" << " must have a defined char - 'r', 'c'  or 'e' in " 
				<< 3 << " argument";
			throw_error(ostr.str());
		break;
		}

		kern_arr = (void*)0;
		kernel = cvCreateStructuringElementEx( nx, ny, nx0, ny0, shape, (int*)kern_arr);
	}

	argvalhandle.verify_numeric(4,"cvDilate",1,1);
	int n = argvalhandle.get_numeric(4,0);

	returnvalhandle.verify_nargout(1);

	//-----------------------------------------------------------------

	returnvalhandle.plhs_[0] = mxDuplicateArray(argvalhandle.prhs_[1]);
		
	void *DstData = mxGetPr(returnvalhandle.plhs_[0]);
	CvSize sz = {mrows, ncols};
	orig_step = orig_size / sz.height;

	if (channels == 3)
	{
		orig_step/=3;
		planeR = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(planeR, data, orig_step);
		
		planeG = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(planeG, ((char*)data) + orig_size / 3, orig_step);
		
		planeB = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(planeB, ((char*)data) + 2 * orig_size / 3, orig_step);
		
		src = cvCreateImageHeader(sz, depth, 3);
		psrc = calloc(1,orig_size);
		cvSetImageData(src, psrc, orig_step*3);
		
		cvCvtPlaneToPix(planeR,planeG,planeB,NULL,src);
		
		//pt1.x = 0; pt1.y = 0;
		//pt2.x = 3; pt2.y = 4;
		//cvRectangle( src, pt1, pt2, RGB(255,0,0), 1 );
		
		dst = cvCreateImageHeader(sz, depth, 3);
		pdst = calloc(1,orig_size);
		cvSetImageData(dst, pdst, orig_step*3);
		
		//-----------------------------------
		
		cvDilate(src, dst, kernel, n);
		
		//-----------------------------------
		
		dstplaneR = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dstplaneR, DstData, orig_step);
		
		dstplaneG = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dstplaneG, ((char*)DstData) + orig_size / 3, orig_step);
		
		dstplaneB = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dstplaneB, ((char*)DstData) + 2 * orig_size / 3, orig_step);
		
		//dst = cvCreateImageHeader(sz, depth, 3);
		//cvSetImageData(dst, DstData, orig_step*3);
		
		cvCvtPixToPlane(dst,dstplaneR,dstplaneG,dstplaneB,NULL);
		
		//cvvNamedWindow( "dst",  0);
		//cvvShowImage( "dst", dst );
		//cvvWaitKey("dst");
		
		free(psrc);
		free(pdst);
	} else 
	{
		src = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(src, data, orig_step);
		
		dst = cvCreateImageHeader(sz, depth, 1);
		cvSetImageData(dst, DstData, orig_step);
		
		//-----------------------------------
		
		cvDilate(src, dst,kernel, n);
		
		//-----------------------------------
		
		cvvNamedWindow( "dst",  0);
		cvvShowImage( "dst", dst );
		cvvWaitKey("dst");

	}
	
	cvReleaseStructuringElement(&kernel);
	cvReleaseImageHeader(&src);
	cvReleaseImageHeader(&dst);
	

	return;	
}*/


/*
void wrErode(const CV::FrontEnd::ArgValType& arginhandle,
				 CV::FrontEnd::ReturnValType& argouthandle) {
	arginhandle.verify_nargin(5);
	argouthandle.verify_nargout(1);
//---------------------------------------------------------
//--------------------------------------------------------- IMAGE("in",1)
	int argin1_mrows, argin1_ncols,  argin1_channels, argin1_depth, argin1_channel_size;
	void *argin1_SrcData,*argin1_psrc;
	IplImage  *argin1_planeR, *argin1_planeG, *argin1_planeB;
	mxClassID argin1_class;
	CIplImage argin1;
	
	arginhandle.verify_image(1,"cvLaplace", argin1_mrows, argin1_ncols,
				argin1_channels, argin1_depth, argin1_class, &argin1_SrcData);

	int argin1_type_size = (argin1_depth & 0x7FFFFFFF) / 8;
	CvSize argin1_sz = {argin1_mrows, argin1_ncols};
	argin1_channel_size = argin1_mrows * argin1_ncols;
	
	if (argin1_channels == 3)
	{
		argin1_planeR = cvCreateImageHeader(argin1_sz, argin1_depth, 1);
		cvSetImageData(argin1_planeR, argin1_SrcData, argin1_mrows*argin1_type_size);
		
		argin1_planeG = cvCreateImageHeader(argin1_sz, argin1_depth, 1);
		cvSetImageData(argin1_planeG, ((char*)argin1_SrcData) + argin1_channel_size, argin1_mrows*argin1_type_size);
		
		argin1_planeB = cvCreateImageHeader(argin1_sz, argin1_depth, 1);
		cvSetImageData(argin1_planeB, ((char*)argin1_SrcData) + argin1_channel_size*2, argin1_mrows*argin1_type_size);
		
		argin1.CreateImageHeader(argin1_sz, argin1_depth, 3);
		argin1_psrc = calloc(1,argin1_channel_size*3);
		argin1.SetImageData(argin1_psrc, argin1_mrows*argin1_type_size*3, true);
		
		cvCvtPlaneToPix(argin1_planeR,argin1_planeG,argin1_planeB,NULL,argin1);
	} else 
	{
		argin1.CreateImageHeader(argin1_sz, argin1_depth, 1);
		argin1.SetImageData(argin1_SrcData, argin1_mrows*argin1_type_size, false);
	}
//---------------------------------------------------------
//--------------------------------------------------------- NUMERICARRAY_IN(2,4)
	arginhandle.verify_numeric(2,"Function",1,4);
	CArr<int> argin2;
	argin2.Create(4,true);
	arginhandle.get_numeric_array(2,4, argin2);
//---------------------------------------------------------
//---------------------------------------------------------	ENUMWITHDATA_IN (3, argin2[0]*argin2[1], CV_SHAPE_CUSTOM);
	int argin3_nelems  = arginhandle.verify_numeric_array(2,"Function");
	int argin3_enum_value;
	CArr<int> argin3_enum_data;

	if (argin3_nelems == 1)
	{
		argin3_enum_value = arginhandle.get_numeric(4,0);
	} else
	{
		argin3_enum_value = CV_SHAPE_CUSTOM;
		argin3_enum_data.Create(argin2[0]*argin2[1],true);
		arginhandle.get_numeric_array(3,argin2[0]*argin2[1], argin3_enum_data);
	}
//---------------------------------------------------------
//--------------------------------------------------------- NUMERIC_IN(4)
	arginhandle.verify_numeric(4,"Function",1,1);
	int argin4 = arginhandle.get_numeric(4,0);
//---------------------------------------------------------
	


//--------------------------------------------------------- IMAGE_OUT('0')
	void *argout0_pdst, *argout0_DstData;
	IplImage  *argout0_dstplaneR, *argout0_dstplaneG, *argout0_dstplaneB;
	int argout0_depth, argout0_type_size;
	int argout0_mrows, argout0_ncols, argout0_channels;
	mxClassID argout0_class;
	CIplImage argout0;

	//----------- CLASS_IMAGE_COPY ('0','1')
	argout0_class = argin1_class;
	//----------------------------------- CLASS_IMAGE_OF ('0','1')

	argout0_mrows = argin1_mrows;
	argout0_ncols = argin1_ncols;
	argout0_channels = argin1_channels;
	
		
	CvSize argout0_sz = {argout0_mrows, argout0_ncols};
	int argout0_channel_size = argout0_mrows * argout0_ncols;

	if (argout0_channels == 3)
	{
		int dims[] = {argout0_mrows, argout0_ncols, 3};
		argouthandle.plhs_[0] = mxCreateNumericArray(3, dims, argout0_class, mxREAL);
		argout0_DstData = mxGetPr(argouthandle.plhs_[0]);

		argouthandle.verify_image(0,"cvLaplace", argout0_mrows, argout0_ncols,
			argout0_channels, argout0_depth, argout0_class, &argout0_DstData);

		argout0_type_size = (argout0_depth & 0x7FFFFFFF) / 8;
		
		argout0.CreateImageHeader(argout0_sz, argout0_depth, 3);
		argout0_pdst = calloc(1,argout0_channel_size * 3);
		argout0.SetImageData(argout0_pdst, argout0_mrows*argout0_type_size*3, true);

		IplConvKernel *kernel = cvCreateStructuringElementEx( argin2[0], argin2[1], argin2[2], argin2[3],
			(CvElementShape)((int)argin3_enum_value), argin3_enum_data);
		cvErode(argin1, argout0, kernel, argin4);
		cvReleaseStructuringElement(&kernel);

		argout0_dstplaneR = cvCreateImageHeader(argout0_sz, argout0_depth, 1);
		cvSetImageData(argout0_dstplaneR, argout0_DstData, argout0_mrows*argout0_type_size);
		
		argout0_dstplaneG = cvCreateImageHeader(argout0_sz, argout0_depth, 1);
		cvSetImageData(argout0_dstplaneG, ((char*)argout0_DstData) + argout0_channel_size, argout0_mrows*argout0_type_size);
		
		argout0_dstplaneB = cvCreateImageHeader(argout0_sz, argout0_depth, 1);
		cvSetImageData(argout0_dstplaneB, ((char*)argout0_DstData) + argout0_channel_size*2, argout0_mrows*argout0_type_size);
		
		cvCvtPixToPlane(argout0,argout0_dstplaneR,argout0_dstplaneG,argout0_dstplaneB,NULL);
	} else
	{
		int dims[] = {argout0_mrows, argout0_ncols};
		argouthandle.plhs_[0] = mxCreateNumericArray(2, dims, argout0_class, mxREAL);
		argout0_DstData = mxGetPr(argouthandle.plhs_[0]);
		
		argouthandle.verify_image(0,"cvLaplace", argout0_mrows, argout0_ncols,
			argout0_channels, argout0_depth, argout0_class, &argout0_DstData);

		argout0_type_size = (argout0_depth & 0x7FFFFFFF) / 8;

		argout0.CreateImageHeader(argout0_sz, argout0_depth, 1);
		argout0.SetImageData(argout0_DstData, argout0_mrows*argout0_type_size, false);

		IplConvKernel *kernel = cvCreateStructuringElementEx( argin2[0], argin2[1], argin2[2], argin2[3],
			(CvElementShape)((int)argin3_enum_value), argin3_enum_data);
		cvErode(argin1, argout0, kernel, argin4);
		cvReleaseStructuringElement(&kernel);
	}
	
	return;	
}*/

///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('PyrUp', IMAGE, NUMERIC filter_type);
//
WRAPPER (3, 1, wrPyrUp);	
IMAGE_IN (1);
NUMERIC_IN (2, int);
IMAGE_OUT (	0 ,
		   OUT_PARAM(0,mrows) = IN_PARAM(1,mrows) * 2;
		   OUT_PARAM(0,ncols) = IN_PARAM(1,ncols) * 2;
		   OUT_PARAM(0,channels) = IN_PARAM(1,channels);
		   if ( IN_PARAM(1,class) == mxSINGLE_CLASS)
			   OUT_PARAM(0,class) = mxSINGLE_CLASS;
		   else OUT_PARAM(0,class) = mxINT16_CLASS ,
		   cvPyrUp(argin1, argout0, (IplFilter) argin2) );
RET
		   
///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('PyrDown', IMAGE, NUMERIC filter_type);
//
WRAPPER (3, 1, wrPyrDown);	
IMAGE_IN (1);
NUMERIC_IN (2, int);
IMAGE_OUT (	0 ,
			OUT_PARAM(0,mrows) = IN_PARAM(1,mrows) / 2;
			OUT_PARAM(0,ncols) = IN_PARAM(1,ncols) / 2;
			OUT_PARAM(0,channels) = IN_PARAM(1,channels);
			if ( IN_PARAM(1,class) == mxSINGLE_CLASS)
				OUT_PARAM(0,class) = mxSINGLE_CLASS;
			else OUT_PARAM(0,class) = mxINT16_CLASS ,
			cvPyrDown(argin1, argout0, (IplFilter) argin2) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('Laplace', IMAGE, NUMERIC);
//
WRAPPER (3, 1, wrLaplace);	
IMAGE_IN (1);
NUMERIC_IN (2, int);
IMAGE_OUT (	0 ,
			OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
			OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
			OUT_PARAM(0,channels) = IN_PARAM(1,channels);
			if ( IN_PARAM(1,class) == mxSINGLE_CLASS)
				OUT_PARAM(0,class) = mxSINGLE_CLASS;
			else OUT_PARAM(0,class) = mxINT16_CLASS ,
			cvLaplace(argin1, argout0, argin2) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('Sobel', IMAGE, NUMERIC, NUMERIC, NUMERIC);
//
WRAPPER (5, 1, wrSobel);	
IMAGE_IN (1);
NUMERIC_IN (2, int);
NUMERIC_IN (3, int);
NUMERIC_IN (4, int);
IMAGE_OUT (	0 ,
		   OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
		   OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
		   OUT_PARAM(0,channels) = IN_PARAM(1,channels);
		   if ( IN_PARAM(1,class) == mxSINGLE_CLASS)
			   OUT_PARAM(0,class) = mxSINGLE_CLASS;
		   else OUT_PARAM(0,class) = mxINT16_CLASS ,
		   cvSobel(argin1, argout0, argin2, argin3, argin4) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('Erode', IMAGE, NUMERICARRAY(4), ENUMWITHDATA, NUMERIC);
//
WRAPPER (5, 1, wrErode);	
IMAGE_IN (1);
NUMERICARRAY_IN (2, 4, int);
ENUMWITHDATA_IN (3, argin2[0]*argin2[1], int, CV_SHAPE_CUSTOM);
NUMERIC_IN (4, int);
IMAGE_OUT (	0 ,
		   OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
		   OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
		   OUT_PARAM(0,channels) = IN_PARAM(1,channels);
		   OUT_PARAM(0,class) = IN_PARAM(1,class) ,
		   IplConvKernel *kernel = cvCreateStructuringElementEx( argin2[0], argin2[1], argin2[2], argin2[3],
			   (CvElementShape)((int)argin3_enum_value), argin3_enum_data);
		   cvErode(argin1, argout0, kernel, argin4);
		   cvReleaseStructuringElement(&kernel) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('Dilate', IMAGE, NUMERICARRAY(4), ENUMWITHDATA, NUMERIC);
//
WRAPPER (5, 1, wrDilate);	
IMAGE_IN (1);
NUMERICARRAY_IN (2, 4, int);
ENUMWITHDATA_IN (3, argin2[0]*argin2[1], int, CV_SHAPE_CUSTOM);
NUMERIC_IN (4, int);
IMAGE_OUT (	0 ,
		   OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
		   OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
		   OUT_PARAM(0,channels) = IN_PARAM(1,channels);
		   OUT_PARAM(0,class) = IN_PARAM(1,class) ,
		   IplConvKernel *kernel = cvCreateStructuringElementEx( argin2[0], argin2[1], argin2[2], argin2[3],
			   (CvElementShape)((int)argin3_enum_value), argin3_enum_data);
		   cvDilate(argin1, argout0, kernel, argin4);
		   cvReleaseStructuringElement(&kernel) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('DistTransform', IMAGE, NUMERIC mask_size, ENUMWITHDATA mask_type);
//
WRAPPER (4, 1, wrDistTransform);	
IMAGE_IN (1);
NUMERIC_IN (2, int);
ENUMWITHDATA_IN (3, (argin2 / 2) + 1, float, CV_DIST_USER);
IMAGE_OUT (	0 ,
		   OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
		   OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
		   OUT_PARAM(0,channels) = IN_PARAM(1,channels);
		   OUT_PARAM(0,class) = IN_PARAM(1,class) ,
		   cvDistTransform(argin1, argout0, (CvDisType)((int)argin3_enum_value), argin2, (float*)argin3_enum_data) );
RET

/*///////////////////////////////////////////////////////////////////////////////
// IMAGE = dllname('AdaptiveThreshold', IMAGE, DOUBLE maxVal, ENUM type, NUMERIC);
//
WRAPPER (4, 1, wrAdaptiveThreshold);	
IMAGE_IN (1);
NUMERIC_IN (2, double);
NUMERICARRAY_IN (2, 4, int);
ENUMWITHDATA_IN (3, argin2[0]*argin2[1], int, CV_SHAPE_CUSTOM);
NUMERIC_IN (4);
IMAGE_OUT (	0 ,
		   OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
		   OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
		   OUT_PARAM(0,channels) = IN_PARAM(1,channels);
		   OUT_PARAM(0,class) = IN_PARAM(1,class) ,
		   IplConvKernel *kernel = cvCreateStructuringElementEx( argin2[0], argin2[1], argin2[2], argin2[3],
			   (CvElementShape)((int)argin3_enum_value), argin3_enum_data);
		   cvDilate(argin1, argout0, kernel, argin4); cvAdaptiveThreshold
		   cvReleaseStructuringElement(&kernel) );*/

///////////////////////////////////////////////////////////////////////////////
// IMAGE dst = dllname('Canny', IMAGE 8U src, DOUBLE low_thresh,
//		   DOUBLE high_thresh, INT aperture);
//
WRAPPER (5, 1, wrCanny);
IMAGE_IN (1);
NUMERIC_IN (2, double);
NUMERIC_IN (3, double);
NUMERIC_IN (4, int);
IMAGE_OUT (	0 ,
			OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
			OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
			OUT_PARAM(0,channels) = IN_PARAM(1,channels);
			OUT_PARAM(0,class) = IN_PARAM(1,class) ,
			cvCanny(argin1, argout0, argin2, argin3, argin4) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE dst = dllname('PreCornerDetect', IMAGE 32F src, INT aperture);
//
WRAPPER (3, 1, wrPreCornerDetect);
IMAGE_IN (1);
NUMERIC_IN (2, int);
IMAGE_OUT (	0 ,
			OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
			OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
			OUT_PARAM(0,channels) = IN_PARAM(1,channels);
			OUT_PARAM(0,class) = IN_PARAM(1,class) ,
			cvPreCornerDetect(argin1, argout0, argin2) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE dst = dllname('MatchTemplate', IMAGE src, IMAGE template, ENUM method);
//
WRAPPER (4, 1, wrMatchTemplate);
IMAGE_IN (1);
IMAGE_IN (2);
NUMERIC_IN (3, int);
IMAGE_OUT (	0 ,
			OUT_PARAM(0,mrows) = IN_PARAM(1,mrows) - IN_PARAM(2,mrows) + 1;
			OUT_PARAM(0,ncols) = IN_PARAM(1,ncols) - IN_PARAM(2,ncols) + 1;
			OUT_PARAM(0,channels) = IN_PARAM(1,channels);
			OUT_PARAM(0,class) = mxSINGLE_CLASS ,
			cvMatchTemplate(argin1, argin2, argout0, (CvTemplMatchMethod)((int)argin3)) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE dst = dllname('UpdateMotionHistory', IMAGE src, DOUBLE timestamp,
//			   DOUBLE mhiduration );
//
WRAPPER (4, 1, wrUpdateMotionHistory);
IMAGE_IN (1);
NUMERIC_IN (2, double);
NUMERIC_IN (3, double);
IMAGE_OUT (	0 ,
			OUT_PARAM(0,mrows) = IN_PARAM(1,mrows);
			OUT_PARAM(0,ncols) = IN_PARAM(1,ncols);
			OUT_PARAM(0,channels) = IN_PARAM(1,channels);
			OUT_PARAM(0,class) = mxSINGLE_CLASS ,
			cvUpdateMotionHistory(argin1, argout0, argin2, argin3) );
RET

///////////////////////////////////////////////////////////////////////////////
// [DOUBLE min,DOUBLE max,[DOUBLE Xmin,DOUBLE Ymin],[DOUBLE Xmax,DOUBLE Ymax]]=
//			dllname('MinMaxLoc', IMAGE src, IMAGE mask);
//
WRAPPER (3, 4, wrMinMaxLoc);
IMAGE_IN (1);
IMAGE_IN (2);
NUMERICARRAY_OUT( 0 , 1, double, OUT_PARAM(0,class) = mxDOUBLE_CLASS, ; ); // min
NUMERICARRAY_OUT( 1 , 1, double, OUT_PARAM(1,class) = mxDOUBLE_CLASS, ; ); // max
NUMERICARRAY_OUT( 2 , 2, int, OUT_PARAM(2,class) = mxINT32_CLASS, ; ); // Xmin, Ymin
NUMERICARRAY_OUT( 3 , 2, int, OUT_PARAM(3,class) = mxINT32_CLASS,
				 cvMinMaxLoc( argin1, (double*) (argout0),
									  (double*) (argout1),
									  (CvPoint*) ((int*)argout2),
									  (CvPoint*) ((int*)argout3));
				 PUT_OUTARRAY( 0 );
				 PUT_OUTARRAY( 1 );
				 PUT_OUTARRAY( 2 );
				 PUT_OUTARRAY( 3 )
				 ); // Xmax, Ymax 
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE dst = dllname( 'Threshold', IMAGE src, DOUBLE thresh, DOUBLE maxValue,
//     ENUM type );
//
WRAPPER( 5, 1, wrThreshold );
IMAGE_IN( 1 );
NUMERIC_IN( 2, double);
NUMERIC_IN( 3, double);
NUMERIC_IN( 4, int);
IMAGE_OUT(	0,
			OUT_PARAM( 0, mrows ) = IN_PARAM( 1, mrows );
			OUT_PARAM( 0, ncols ) = IN_PARAM( 1, ncols );
			OUT_PARAM( 0, channels ) = IN_PARAM( 1, channels );
			OUT_PARAM( 0, class ) = IN_PARAM( 1, class ),
			cvThreshold( argin1, argout0, argin2, argin3, 
			    (CvThreshType)((int)argin4)) );
RET

///////////////////////////////////////////////////////////////////////////////
// SEQARRAY dst = dllname( 'FindContours', IMAGE src, ENUM mode, ENUM method );
//
WRAPPER( 4, 1, wrFindContours );
IMAGE_IN( 1 );
NUMERIC_IN( 2, int );
NUMERIC_IN( 3, int );
SEQARRAY_OUT( 0,
			  argout0.num = cvFindContours( argin1, argout0.storage, argout0,
				  argout0.headerSize, (CvContourRetrievalMode)((int)argin2),
				  (CvChainApproxMethod)((int)argin3) ) );
RET

///////////////////////////////////////////////////////////////////////////////
// IMAGE dst = dllname( 'DrawContours',
//     IMAGE img,            // image
//     SEQARRAY seqArray,    // array of sequences
//	   INT first,            // index of the first sequence
//     DOUBLE externalColor 
//     DOUBLE holeColor
//     INT maxLevel,
//     INT thickness,
//     INT connectivity );
//
WRAPPER( 9, 1, wrDrawContours );
IMAGE_IN( 1 );
NUMERIC_IN( 3, int );    // first
NUMERIC_IN( 4, double ); // externalColor
NUMERIC_IN( 5, double ); // holeColor
NUMERIC_IN( 6, int );    // maxLevel
NUMERIC_IN( 7, int );    // thickness
NUMERIC_IN( 8, int );    // connectivity

SEQARRAY_IN( 2, argin3, argin6, 0 );

IMAGE_OUT(	0,
			OUT_PARAM( 0, mrows ) = IN_PARAM( 1, mrows );
			OUT_PARAM( 0, ncols ) = IN_PARAM( 1, ncols );
			OUT_PARAM( 0, channels ) = IN_PARAM( 1, channels );
			OUT_PARAM( 0, class ) = IN_PARAM( 1, class ),
			
			cvCopy( argin1, argout0 );
			if( (CvSeq *)argin2 )
			{
				cvDrawContours( argout0, argin2, argin4, argin5, argin6,
					argin7, argin8 );
			} );
RET

///////////////////////////////////////////////////////////////////////////////
// SEQARRAY dst = dllname( 'ApproxPoly',
//     SEQARRAY seqArray,    // array of sequences
//	   INT first,            // index of the first sequence
//     ENUM method,          // method
//     DOUBLE parameter,     // parameter
//     INT recursive );
//
WRAPPER( 6, 1, wrApproxPoly );
NUMERIC_IN( 2, int );    // first
NUMERIC_IN( 3, int );    // method
NUMERIC_IN( 4, double ); // parameter
NUMERIC_IN( 5, int );    // recursive

SEQARRAY_IN( 1, argin2, 0, argin5 );

SEQARRAY_OUT( 0,
			  if( (CvSeq *)argin1 )
			  {
				  argout0.num = argin1.num;
				  argout0.seq = cvApproxPoly( argin1, argin1.headerSize,
					  argout0.storage, (CvPolyApproxMethod)((int)argin3),
					  argin4, argin5 ); );
			  }
RET

///////////////////////////////////////////////////////////////////////////////
// perimeter = dllname( 'ContourPerimeter',
//     points,    // n by 2 array of points
//	   slice );   // [firstIdx lastIdx]
//
WRAPPER( 3, 1, wrContourPerimeter );
ELEMARRAY_IN( 1, CvPoint, -1 ); // array of points
ELEMARRAY_IN( 2, CvSlice, 1 );  // slice

NUMARRAY_OUT( 0, double, 1,
			  if( argin1.num > 0 )
			  {
				  CvSeq seq;
				  CvSeqBlock block;
				  cvMakeSeqHeaderForArray( CV_SEQ_CONTOUR, sizeof( seq ),
					  sizeof( CvPoint ),
					  (CvArr *)((CvPoint *)argin1), argin1.num, &seq, &block );
				  ((CvSlice *)argin2)->startIndex--;
				  ((CvSlice *)argin2)->endIndex--;
				  argout0 = cvContourPerimeter( &seq, argin2 );
			  }
			  PUTOUT_NUMARRAY( 0, mxDOUBLE_CLASS );
			);
RET

///////////////////////////////////////////////////////////////////////////////
// perimeter = dllname( 'ContourArea',
//     points,    // n by 2 array of points
//	   slice );   // [firstIdx lastIdx]
//
WRAPPER( 3, 1, wrContourArea );
ELEMARRAY_IN( 1, CvPoint, -1 ); // array of points
ELEMARRAY_IN( 2, CvSlice, 1 );  // slice

NUMARRAY_OUT( 0, double, 1,
			  if( argin1.num > 0 )
			  {
				  CvSeq seq;
				  CvSeqBlock block;
				  cvMakeSeqHeaderForArray( CV_SEQ_CONTOUR, sizeof( seq ),
					  sizeof( CvPoint ),
					  (CvArr *)((CvPoint *)argin1), argin1.num, &seq, &block );
				  ((CvSlice *)argin2)->startIndex--;
				  ((CvSlice *)argin2)->endIndex--;
				  argout0 = cvContourArea( &seq, argin2 );
			  }
			  PUTOUT_NUMARRAY( 0, mxDOUBLE_CLASS );
			);
RET

///////////////////////////////////////////////////////////////////////////////
// [IMAGE dst, DOUBLE area, DOUBLE value, [x y width height]] = 
//   dllname( 'FloodFill',
//            IMAGE src,
//            seedPoint,
//            DOUBLE newVal,
//            DOUBLE loDiff,
//            DOUBLE upDiff,
//            INT connectivity );
//
WRAPPER( 7, 4, wrFloodFill );
IMAGE_IN( 1 );
ELEMARRAY_IN( 2, CvPoint, 1 );  // seedPoint
NUMARRAY_IN( 3, double, 1 );    // newVal
NUMARRAY_IN( 4, double, 1 );    // loDiff
NUMARRAY_IN( 5, double, 1 );    // upDiff
NUMARRAY_IN( 6, int, 1 );       // connectivity

NUMARRAY_OUT( 1, double, 1, ; ); // area
NUMARRAY_OUT( 2, double, 1, ; ); // value
ELEMARRAY_OUT( 3, CvRect, 1, ; );    // rect
IMAGE_OUT( 0, 
			OUT_PARAM( 0, mrows ) = IN_PARAM( 1, mrows );
			OUT_PARAM( 0, ncols ) = IN_PARAM( 1, ncols );
			OUT_PARAM( 0, channels ) = IN_PARAM( 1, channels );
			OUT_PARAM( 0, class ) = IN_PARAM( 1, class ),

			cvCopy( argin1, argout0 );
			CvConnectedComp comp;
			cvFloodFill( (IplImage *)argout0, *((CvPoint *)argin2), 
				*((double *)argin3), *((double *)argin4), *((double *)argin5),
				&comp, *((int *)argin6) );
			argout1 = (double)comp.area;
			argout2 = (double)comp.value;
			*((CvRect *)argout3) = comp.rect;

			PUTOUT_NUMARRAY( 1, mxDOUBLE_CLASS );
			PUTOUT_NUMARRAY( 2, mxDOUBLE_CLASS );
			PUTOUT_ELEMARRAY( 3, mxDOUBLE_CLASS );
		 );
RET

///////////////////////////////////////////////////////////////////////////////
// [featuresB, error] = 
//   dllname( 'CalcOpticalFlowPyrLK',
//            IMAGE imgA, IMAGE imgB, featuresA, featuresB, winSize, INT level,
//            [maxIter epsilon] );
//
WRAPPER( 8, 2, wrCalcOpticalFlowPyrLK );
IMAGE_IN( 1 );                        // imgA
IMAGE_IN( 2 );                        // imgB
ELEMARRAY_IN( 3, CvPoint2D32f, -1 );  // featuresA
ELEMARRAY_IN( 4, CvPoint2D32f, -1 );  // initial guessess
ELEMARRAY_IN( 5, CvSize, 1 );         // winSize
NUMARRAY_IN( 6, int, 1 );             // level
ELEMARRAY_IN( 7, CvTermCriteria, 1 ); // criteria

ELEMARRAY_OUT( 0, CvPoint2D32f, argin3.num, ; ); // featuresB
ELEMARRAY_OUT( 1, float, argin3.num,             // error
			   CElemArr< char > status( argin3.num );
			   if( argin3.num > 0 )
			   {
				   int flags = 0;
				   if( argin4.num == argin3.num )
				   {
					   // initial guessess
					   memcpy( (void *)((CvPoint2D32f *)argout0),
						   (void *)((CvPoint2D32f *)argin4),
						   sizeof( CvPoint2D32f ) * argin3.num );
					   flags |= CV_LKFLOW_INITIAL_GUESSES;
				   }
				   cvCalcOpticalFlowPyrLK(
					   (IplImage *)argin1, (IplImage *)argin2,
					   0, 0,
					   (CvPoint2D32f *)argin3, (CvPoint2D32f *)argout0,
					   argin3.num,
					   *((CvSize *)argin5), *((int *)argin6),
					   (char *)status, (float *)argout1,
					   *((CvTermCriteria *)argin7), flags );
				   
			   }
			   PUTOUT_ELEMARRAY( 0, mxDOUBLE_CLASS );
			   PUTOUT_ELEMARRAY( 1, mxDOUBLE_CLASS );
			   
			   // fill points for which flow was not found with NaN value 
			   double NaN = mxGetNaN();
			   double *data0 = (double *)mxGetData( plhs[0] );
			   double *data1 = (double *)mxGetData( plhs[1] );
			   int step0 = mxGetM( plhs[0] );
			   for( int i = 0; i < argin3.num; i++ )
			   {
				   if( *((char *)status + i) == 0 )
				   {
					   data0[i] = NaN;
					   data0[i + step0] = NaN;
					   data1[i] = NaN;
				   }
			   }
			 );

RET

///////////////////////////////////////////////////////////////////////////////
// corners = dllname( 'GoodFeaturesToTrack',
//             IMAGE image, INT corner_count,
//             DOUBLE quality_level, DOUBLE min_distance, 
//             IMAGE mask // may be empty matrix
//           );
//
WRAPPER( 6, 1, wrGoodFeaturesToTrack );
IMAGE_IN( 1 );               // image
NUMARRAY_IN( 2, int, 1 );    // corner_count
NUMARRAY_IN( 3, double, 1 ); // quality_level
NUMARRAY_IN( 4, double, 1 ); // min_distance
int corner_count = *((int *)argin2);
if( !mxIsEmpty( prhs[5] ) )
{
	IMAGE_IN( 5 );           // mask
	CIplImage eigImage;
	CIplImage tempImage;
	eigImage.CreateImageHeader(
		cvSize( IN_PARAM( 1, mrows ), IN_PARAM( 1, ncols ) ), 
		IPL_DEPTH_32F, 1 );
	eigImage.SetImageData(
		(void *)calloc( IN_PARAM( 1, mrows ) * IN_PARAM( 1, ncols ),
		sizeof( float ) ),
		IN_PARAM( 1, mrows ) * sizeof( float ), true );
	tempImage.CreateImageHeader(
		cvSize( IN_PARAM( 1, mrows ), IN_PARAM( 1, ncols ) ), 
		IPL_DEPTH_32F, 1 );
	tempImage.SetImageData(
		(void *)calloc( IN_PARAM( 1, mrows ) * IN_PARAM( 1, ncols ),
		sizeof( float ) ),
		IN_PARAM( 1, mrows ) * sizeof( float ), true );
	ELEMARRAY_OUT( 0, CvPoint2D32f, corner_count,
				   cvGoodFeaturesToTrack( (IplImage *)argin1, 
				   (IplImage *)eigImage, (IplImage *)tempImage,
				   (CvPoint2D32f *)argout0, &corner_count, *((double *)argin3),
				   *((double *)argin4), (IplImage *)argin5 );
				   argout0.num = corner_count;
				   PUTOUT_ELEMARRAY( 0, mxDOUBLE_CLASS );
		         );

}
else
{
	CIplImage eigImage;
	CIplImage tempImage;
	eigImage.CreateImageHeader(
		cvSize( IN_PARAM( 1, mrows ), IN_PARAM( 1, ncols ) ), 
		IPL_DEPTH_32F, 1 );
	eigImage.SetImageData(
		(void *)calloc( IN_PARAM( 1, mrows ) * IN_PARAM( 1, ncols ),
		sizeof( float ) ),
		IN_PARAM( 1, mrows ) * sizeof( float ), true );
	tempImage.CreateImageHeader(
		cvSize( IN_PARAM( 1, mrows ), IN_PARAM( 1, ncols ) ), 
		IPL_DEPTH_32F, 1 );
	tempImage.SetImageData(
		(void *)calloc( IN_PARAM( 1, mrows ) * IN_PARAM( 1, ncols ),
		sizeof( float ) ),
		IN_PARAM( 1, mrows ) * sizeof( float ), true );
	ELEMARRAY_OUT( 0, CvPoint2D32f, corner_count,
				   cvGoodFeaturesToTrack( (IplImage *)argin1, 
				   (IplImage *)eigImage, (IplImage *)tempImage,
				   (CvPoint2D32f *)argout0, &corner_count, *((double *)argin3),
				   *((double *)argin4), 0 );
				   argout0.num = corner_count;
				   PUTOUT_ELEMARRAY( 0, mxDOUBLE_CLASS );
		         );
}
RET
