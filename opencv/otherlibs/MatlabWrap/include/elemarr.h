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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _ELEMARR_H_
#define _ELEMARR_H_

#include "qfrontend.h"

using namespace CV;
using namespace CV::FrontEnd;

#define FUNC_GET_SIMPLE( type ) \
void _get( mxArray *mxArr, type *arr, int num ) { \
	int _m = mxGetM( mxArr ); \
	int _n = mxGetN( mxArr ); \
	if( num == 0 && _m == 0 && _n == 0 ) \
	{ \
		return; \
	} \
	if( mxGetNumberOfDimensions( mxArr ) != 2 || \
		_m != 1 || \
		_n != num ) \
	{ \
		throw_error("Invalid one of the input parameters."); \
		return; \
	} \
	_getSimpleType( mxArr, 0, arr, num ); \
}

#define FUNC_PUT_SIMPLE( type ) \
void _put( mxArray *&mxArr, type *arr, int num, mxClassID mxClass ) { \
	mxArr = mxCreateNumericMatrix( ( num == 0 ) ? 0 : 1, num, \
		mxClass, mxREAL ); \
	if( num > 0 ) \
	{ \
		_putSimpleType( mxArr, 0, arr, num ); \
	} \
}

#define FUNC_GET( type, nFields, decl, param, assign ) \
void _get( mxArray *mxArr, type *arr, int num ) { \
	const int numFields = nFields; /* number of fields */ \
	int _m = mxGetM( mxArr ); \
	int _n = mxGetN( mxArr ); \
	if( num == 0 && _m == 0 && _n == 0 ) \
	{ \
		return; \
	} \
	if( mxGetNumberOfDimensions( mxArr ) != 2 || \
		_m != num || \
		_n != numFields ) \
	{ \
		throw_error("Invalid one of the input parameters."); \
		return; \
	} \
	\
	##decl##; \
	\
	int nelem = 0; \
	for( nelem = 0; nelem < num; nelem++ ) \
	{ \
		_getSimpleType( mxArr, nelem, ##param##, numFields ); \
		\
		##assign##; \
		\
	} /* for each elem in arr */ \
}

#define FUNC_PUT( type, nFields, decl, assign, param ) \
void _put( mxArray *&mxArr, type *arr, int num, mxClassID mxClass ) { \
	const int numFields = nFields; /* number of fields */ \
	mxArr = mxCreateNumericMatrix( num, ( num > 0 ) ? numFields : 0, \
		mxClass, mxREAL ); \
	\
	##decl##; \
	\
	int nelem = 0; \
	for( nelem = 0; nelem < num; nelem++ ) \
	{ \
		\
		##assign##; \
		\
		_putSimpleType( mxArr, nelem, ##param##, numFields ); \
	} /* for each elem in arr */ \
}

template< class T >
class CElemArr
{
public:
	// array of type T
	T *arr;

	// number of elements in array
	int num;

	// input constructor
	CElemArr( mxArray *mxArr, int _num = 1 )
		: arr( 0 ), num( 0 )
	{
		create( _num );
		_get( mxArr, arr, num );
	}

	// output constructor
	CElemArr( int _num = 1 )
		: arr( 0 ), num( 0 )
	{
		create( _num );
	}
	
	~CElemArr()
	{
		destroy();
	}

	void put( mxArray *&mxArr,  mxClassID mxClass = mxDOUBLE_CLASS )
	{
		mxDestroyArray( mxArr );
		_put( mxArr, arr, num, mxClass );
	}

	operator T *() { return( arr ); }
	operator T()   { return( arr[0] ); }
	
	T operator=( T val ) { arr[0] = val; return( val ); }
	
private:

	CElemArr &operator=( const CElemArr &ea );
	
	void create( int _num )
	{
		destroy();
		if( _num > 0 )
		{
			arr = new T[_num];
			num = _num;
		}
	}

	void destroy()
	{
		if( arr )
		{
			delete[] arr;
			arr = 0;
		}
		num = 0;
	}
};

/*F/////////////////////////////////////////////////////////////////////////////
// get for simple types
// startIdx - number of first element in mxArr
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
template< class T >
void _getSimpleType( mxArray *mxArr, int startIdx, T *arr, int num )
{
	int step = mxGetM( mxArr );

	if( !mxIsNumeric( mxArr ) ||
		mxGetNumberOfElements( mxArr ) <= startIdx + (num - 1) * step )
	{
		throw_error("Invalid one of the input parameters.");
		return;
	}
		
	if( mxIsInt32( mxArr ) || mxIsUint32( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((T*)arr)[i] = static_cast<T>(
				((int *)mxGetData( mxArr ))[i * step + startIdx] );
		}
	}
	else if( mxIsDouble( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((T*)arr)[i] = static_cast<T>(
				((double *)mxGetData( mxArr ))[i * step + startIdx] );
		}
	} else if( mxIsInt8( mxArr ) || mxIsUint8( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((T*)arr)[i] = static_cast<T>(
				((char *)mxGetData( mxArr ))[i * step + startIdx] );
		}
	} else if( mxIsInt16( mxArr ) || mxIsUint16( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((T*)arr)[i] = static_cast<T>(
				((short *)mxGetData( mxArr ))[i * step + startIdx] );
		}
	} else if( mxIsSingle( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((T*)arr)[i] = static_cast<T>(
				((float *)mxGetData( mxArr ))[i * step + startIdx] );
		}
	}
	else
	{
		throw_error("Unknown type of matlab data.");
	}
}

/*F/////////////////////////////////////////////////////////////////////////////
// put for simple types
// startIdx - number of first element in mxArr
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
template< class T >
void _putSimpleType( mxArray *mxArr, int startIdx, T *arr, int num )
{
	int step = mxGetM( mxArr );
	
	if( !mxIsNumeric( mxArr ) ||
		mxGetNumberOfElements( mxArr ) <= startIdx + (num - 1) * step )
	{
		throw_error("Invalid one of the output parameters.");
		return;
	}
	
	if( mxIsInt32( mxArr ) || mxIsUint32( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((int *)mxGetData( mxArr ))[i * step + startIdx] = 
				static_cast< int >( ((T*)arr)[i] );
		}
	}
	else if( mxIsDouble( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((double *)mxGetData( mxArr ))[i * step + startIdx] = 
				static_cast< double >( ((T*)arr)[i] );
		}
	} else if( mxIsInt8( mxArr ) || mxIsUint8( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((char *)mxGetData( mxArr ))[i * step + startIdx] = 
				static_cast< char >( ((T*)arr)[i] );
		}
	} else if( mxIsInt16( mxArr ) || mxIsUint16( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((short *)mxGetData( mxArr ))[i * step + startIdx] = 
				static_cast< short >( ((T*)arr)[i] );
		}
	} else if( mxIsSingle( mxArr ) )
	{
		for( int i = 0; i < num; i++ )
		{
			((float *)mxGetData( mxArr ))[i * step + startIdx] = 
				static_cast< float >( ((T*)arr)[i] );
		}
	}
	else
	{
		throw_error("Unknown type of matlab data.");
	}
}

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for simple types
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, char *arr, int num );
void _put( mxArray *&mxArr, char *arr, int num, mxClassID mxClass );

void _get( mxArray *mxArr, int *arr, int num );
void _put( mxArray *&mxArr, int *arr, int num, mxClassID mxClass );

void _get( mxArray *mxArr, float *arr, int num );
void _put( mxArray *&mxArr, float *arr, int num, mxClassID mxClass );

void _get( mxArray *mxArr, double *arr, int num );
void _put( mxArray *&mxArr, double *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for double
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr,  double *arr, int num );
void _put( mxArray *&mxArr, double *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for CvPoint
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, CvPoint *arr, int num );
void _put( mxArray *&mxArr, CvPoint *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for CvSlice
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, CvSlice *arr, int num );
void _put( mxArray *&mxArr, CvSlice *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for CvRect
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, CvRect *arr, int num );
void _put( mxArray *&mxArr, CvRect *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for CvSize
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, CvSize *arr, int num );
void _put( mxArray *&mxArr, CvSize *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for CvPoint2D32f
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, CvPoint2D32f *arr, int num );
void _put( mxArray *&mxArr, CvPoint2D32f *arr, int num, mxClassID mxClass );

/*F/////////////////////////////////////////////////////////////////////////////
// get / put for CvTermCriteria
// arr      - array of simple types
// num      - number of elements in arr
//F*/		
void _get( mxArray *mxArr, CvTermCriteria *arr, int num );
void _put( mxArray *&mxArr, CvTermCriteria *arr, int num, mxClassID mxClass );

#endif /* _ELEMARR_H_ */