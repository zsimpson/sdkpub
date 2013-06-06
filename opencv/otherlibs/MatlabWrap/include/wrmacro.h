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

#ifndef CV_WRAP_MACRO
#define CV_WRAP_MACRO

#include "ipl.h"
#include "cv.h"
//----------------------------------- Classes ---------------------------------
template <class T>
class CArr
{
public:
	T *pData;
	bool ToClearData;
	
	CArr();
	~CArr();
	inline void  Create( int num, bool tocleardata);
	inline operator T*()
	{
		return pData;
	}

	inline operator void*()
	{
		return pData;
	}

	inline operator T()
	{
		return pData[0];
	}

	inline T operator[](int n) const
	{
		return pData[n];
	}
	
	inline T* operator+(int n) const
	{
		return pData + n;
	}
};

template <class T>
inline CArr<T>::CArr()  
{
	pData = NULL;
	ToClearData = false;
}

template <class T>
inline CArr<T>::~CArr() 
{
	if (ToClearData && pData)
		free(pData);
}

template <class T>
void  inline CArr<T>::Create( int num, bool tocleardata)
{
	pData = (T*) calloc(1,sizeof(T)*num);
	ToClearData = tocleardata;
}

//-------------------------------------------------
class CIplImage
{
public:
	IplImage *pHeader;
	void *pData;
	bool ToClearData;
	
	CIplImage();
	~CIplImage();
	void  CreateImageHeader( CvSize size, int depth, int channels );
	void  SetImageData( void* data, int step , bool tocleardata);
	inline operator IplImage*() const
	{
		return pHeader;
	}
};

inline CIplImage::CIplImage() 
{
	pHeader = NULL;
	pData = NULL;
	ToClearData = false;
}

inline CIplImage::~CIplImage() 
{
	if (ToClearData && pData)
		free(pData);
	
	if (pHeader)
		cvReleaseImageHeader(&pHeader);
}

inline void CIplImage::CreateImageHeader( CvSize size, int depth, int channels )
{
	if (!pHeader)
		pHeader = cvCreateImageHeader( size, depth, channels );
	return;
}

inline void CIplImage::SetImageData( void* data, int step, bool tocleardata )
{
	if (pHeader && !pData)
	{
		pData = data;
		ToClearData = tocleardata;
		cvSetImageData( pHeader, data, step );
	}
	return;
}

//----------------------------------- Macroses---------------------------------

/*#define WRAPPER( nargin , nargout, wrapper_name ) \
void  wrapper_name (const CV::FrontEnd::ArgValType& arginhandle, CV::FrontEnd::ReturnValType& argouthandle){ \
		arginhandle.verify_nargin(nargin); \
		argouthandle.verify_nargout(nargout)*/

#define WRAPPER( nargin , nargout, wrapper_name ) \
void  wrapper_name (int nlhs, mxArray* plhs[], int nrhs, mxArray* prhs[]) { \
	if (nrhs != nargin) \
	{ \
	std::ostringstream ostr; \
		ostr << "Function expected " << nargin << " input argument"; \
		if (nargin != 1) \
			ostr << "s"; \
		CV::throw_error(ostr.str()); \
	} \
	if (nlhs != nargout) \
	{ \
	std::ostringstream ostr; \
		ostr << "Function expected " << nargout << " output argument"; \
		if (nargout != 1) \
			ostr << "s"; \
		CV::throw_error(ostr.str()); \
	} 

#define IMAGE_IN( n ) \
	int argin##n##_mrows, argin##n##_ncols,  argin##n##_channels, argin##n##_depth, argin##n##_channel_size; \
	void *argin##n##_data,*argin##n##_psrc; \
	IplImage  *argin##n##_planeR, *argin##n##_planeG, *argin##n##_planeB; \
	mxClassID argin##n##_class; \
	CIplImage argin##n##; \
	\
	verify_image(prhs, n,"Function", argin##n##_mrows, argin##n##_ncols, \
	argin##n##_channels, argin##n##_depth, argin##n##_class, &argin##n##_data); \
	\
	int argin##n##_type_size = (argin##n##_depth & 0x7FFFFFFF) / 8; \
	CvSize argin##n##_sz = {argin##n##_mrows, argin##n##_ncols}; \
	argin##n##_channel_size = argin##n##_mrows * argin##n##_ncols; \
	\
	if (argin##n##_channels == 3) \
{ \
	argin##n##_planeR = cvCreateImageHeader(argin##n##_sz, argin##n##_depth, 1); \
	cvSetImageData(argin##n##_planeR, argin##n##_data, argin##n##_mrows*argin##n##_type_size); \
	\
	argin##n##_planeG = cvCreateImageHeader(argin##n##_sz, argin##n##_depth, 1); \
	cvSetImageData(argin##n##_planeG, ((char*)argin##n##_data) + argin##n##_channel_size, argin##n##_mrows*argin##n##_type_size); \
	\
	argin##n##_planeB = cvCreateImageHeader(argin##n##_sz, argin##n##_depth, 1); \
	cvSetImageData(argin##n##_planeB, ((char*)argin##n##_data) + argin##n##_channel_size*2, argin##n##_mrows*argin##n##_type_size); \
	\
	argin##n##.CreateImageHeader(argin##n##_sz, argin##n##_depth, 3); \
	argin##n##_psrc = calloc(1,argin##n##_channel_size*3); \
	argin##n##.SetImageData(argin##n##_psrc, argin##n##_mrows*argin##n##_type_size*3, true); \
	\
	cvCvtPlaneToPix(argin##n##_planeR,argin##n##_planeG,argin##n##_planeB,NULL,argin##n##); \
	\
	cvReleaseImageHeader( &argin##n##_planeR ); \
	cvReleaseImageHeader( &argin##n##_planeG ); \
	cvReleaseImageHeader( &argin##n##_planeB ); \
	\
} else \
	{\
	argin##n##.CreateImageHeader(argin##n##_sz, argin##n##_depth, 1); \
	argin##n##.SetImageData(argin##n##_data, argin##n##_mrows*argin##n##_type_size, false); \
}

#define NUMERIC_IN( n, type ) \
	verify_numeric(prhs, n, "Function",1,1); \
	type argin##n## = get_numeric< type >(prhs[n],0)

#define NUMERICARRAY_IN( n , nelems, type) \
	int argin##n##_nelems = nelems; \
	verify_numeric(prhs, n,"Function",1,argin##n##_nelems); \
	CArr< type > argin##n##; \
	argin##n##.Create(argin##n##_nelems, true); \
	get_numeric_array< type >(prhs[n], argin##n##_nelems, argin##n##)

#define ENUMWITHDATA_IN( n, nelems, type, defaultval) \
	int argin##n##_nelems  = verify_numeric_array(prhs, n,"Function"); \
	int argin##n##_enum_value; \
	CArr< type > argin##n##_enum_data; \
	if (argin##n##_nelems == 1) \
	{ \
		argin##n##_enum_value = get_numeric< int >(prhs[n],0); \
	} else \
	{ \
		argin##n##_enum_value = defaultval; \
		argin##n##_enum_data.Create(nelems,true); \
		get_numeric_array<type>(prhs[n], nelems, argin##n##_enum_data); \
	}



#define NUMERICARRAY_OUT( n , nelems, type, cond, callfun) \
	mxClassID argout##n##_class; \
	int argout##n##_nelems = nelems; \
\
	##cond##;\
\
	int argout##n##_dims[] = {argout##n##_nelems}; \
	plhs[n] = mxCreateNumericArray(1, argout##n##_dims, argout##n##_class, mxREAL); \
	CArr< type > argout##n##; \
	argout##n##.Create(argout##n##_nelems, false); \
\
	##callfun##;


#define PUT_OUTARRAY( n ) \
	put_numeric_array(plhs[n], argout##n##_nelems, argout##n##)

#define RET \
	return;	\
	}

#define IMAGE_OUT( n, cond, callfun) \
	void *argout##n##_pdst, *argout##n##_data; \
	IplImage *argout##n##_dstplaneR, *argout##n##_dstplaneG, *argout##n##_dstplaneB; \
	int argout##n##_depth, argout##n##_type_size; \
	int argout##n##_mrows, argout##n##_ncols, argout##n##_channels; \
	mxClassID argout##n##_class; \
	CIplImage argout##n##; \
\
	##cond##;\
\
	CvSize argout##n##_sz = {argout##n##_mrows, argout##n##_ncols}; \
	int argout##n##_channel_size = argout##n##_mrows * argout##n##_ncols; \
	if (argout##n##_channels == 3) \
	{ \
		int dims[] = {argout##n##_mrows, argout##n##_ncols, 3}; \
		plhs[n] = mxCreateNumericArray(3, dims, argout##n##_class, mxREAL); \
		argout##n##_data = mxGetPr(plhs[n]); \
\
		verify_image(plhs, n,"Function", argout##n##_mrows, argout##n##_ncols, \
		argout##n##_channels, argout##n##_depth, argout##n##_class, &argout##n##_data); \
\
		argout##n##_type_size = (argout##n##_depth & 0x7FFFFFFF) / 8; \
\
		argout##n##.CreateImageHeader(argout##n##_sz, argout##n##_depth, 3); \
		argout##n##_pdst = calloc(1,argout##n##_channel_size * 3); \
		argout##n##.SetImageData(argout##n##_pdst, argout##n##_mrows*argout##n##_type_size*3, true); \
\
		##callfun##; \
\
		argout##n##_dstplaneR = cvCreateImageHeader(argout##n##_sz, argout##n##_depth, 1); \
		cvSetImageData(argout##n##_dstplaneR, argout##n##_data, argout##n##_mrows*argout##n##_type_size); \
		argout##n##_dstplaneG = cvCreateImageHeader(argout##n##_sz, argout##n##_depth, 1); \
		cvSetImageData(argout##n##_dstplaneG, ((char*)argout##n##_data) + argout##n##_channel_size, argout##n##_mrows*argout##n##_type_size); \
		argout##n##_dstplaneB = cvCreateImageHeader(argout##n##_sz, argout##n##_depth, 1); \
		cvSetImageData(argout##n##_dstplaneB, ((char*)argout##n##_data) + argout##n##_channel_size*2, argout##n##_mrows*argout##n##_type_size); \
		cvCvtPixToPlane(argout##n##,argout##n##_dstplaneR,argout##n##_dstplaneG,argout##n##_dstplaneB,NULL); \
		\
		cvReleaseImageHeader( &argout##n##_dstplaneR ); \
		cvReleaseImageHeader( &argout##n##_dstplaneG ); \
		cvReleaseImageHeader( &argout##n##_dstplaneB ); \
		\
	} else \
	{ \
		int dims[] = {argout##n##_mrows, argout##n##_ncols}; \
		plhs[n] = mxCreateNumericArray(2, dims, argout##n##_class, mxREAL); \
		argout##n##_data = mxGetPr(plhs[n]); \
 \
		verify_image(plhs, n,"Function", argout##n##_mrows, argout##n##_ncols, \
		argout##n##_channels, argout##n##_depth, argout##n##_class, &argout##n##_data); \
 \
		argout##n##_type_size = (argout##n##_depth & 0x7FFFFFFF) / 8; \
		argout##n##.CreateImageHeader(argout##n##_sz, argout##n##_depth, 1); \
		argout##n##.SetImageData(argout##n##_data, argout##n##_mrows*argout##n##_type_size, false); \
 \
		##callfun##; \
	}

#define IN_PARAM(n, property) argin##n##_##property
#define OUT_PARAM(n, property) argout##n##_##property

#define SEQARRAY_IN( n, first, maxLevel, recursive )\
	CSeqArray argin##n##; \
	argin##n##.get( prhs[n], first, maxLevel, recursive ); \

#define SEQARRAY_OUT( n, callfun )\
	CSeqArray argout##n##; \
	argout##n##.createStorage(); \
	##callfun##; \
	argout##n##.put( plhs[n] );
			
// for 1 by num numeric vector
#define NUMARRAY_IN( n, type, num ) \
	CElemArr< type > argin##n##( prhs[n], \
		( num > 0 ) ? num : mxGetN( prhs[n] ) );

#define NUMARRAY_OUT( n, type, num, callfun ) \
	CElemArr< type > argout##n##( num ); \
	\
	##callfun##; \

#define PUTOUT_NUMARRAY( n, class ) argout##n##.put( plhs[n], class );

// for num by numfields(type) matrices
#define ELEMARRAY_IN( n, type, num ) \
	CElemArr< type > argin##n##( prhs[n], \
		( num > 0 ) ? num : mxGetM( prhs[n] ) );

#define ELEMARRAY_OUT( n, type, num, callfun ) \
	CElemArr< type > argout##n##( num ); \
	\
	##callfun##; \

#define PUTOUT_ELEMARRAY( n, class ) argout##n##.put( plhs[n], class );

#endif // CV_WRAP_MACRO