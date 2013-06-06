/* ////////////////////////////////////////////////////////////////////
//
//  CvMat internal interface file
//
// */

#ifndef __CVARR_H__
#define __CVARR_H__

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void cvCheckMatHeader( const CvMat* arr, const char* arrname,
                         const char* file, int line );

void  cvSetMatShapeFlags( CvMat* arr );
void  cvScalarToMat( CvScalar* scalar, int flags, CvMat* arr, void* data );
void  cvScalarToRawData( CvScalar* scalar, int flags, void* data, int extend = 0 );

#define CV_CHECK_ARR( arr ) CV_CALL( cvCheckMatHeader( (arr), #arr, __FILE__, __LINE__ ));

#define CV_DEPTH_MAX  5
#define CV_CN_MAX     4 

/* general-purpose saturation macros */ 
#define CV_CAST_8U(t)    (uchar)( !((t) & ~255) ? (t) : (t) > 0 ? 255 : 0)
#define CV_CAST_8S(t)    (char)( !(((t)+128) & ~255) ? (t) : (t) > 0 ? 127 : -128 )
#define CV_CAST_16S(t)   (short)( !(((t)+32768) & ~65535) ? (t) : (t) > 0 ? 32767 : -32768 )
#define CV_CAST_32S(t)   (int)(t)
#define CV_CAST_64S(t)   (int64)(t)
#define CV_CAST_32F(t)   (float)(t)
#define CV_CAST_64F(t)   (double)(t)

/* helper tables */
extern const int icvPixSize[];
extern const float icv8to32f[];

extern const uchar icvSaturate8u[];
extern const char  icvSaturate8s[];

#define CV_FAST_CAST_8U(t)   (assert(-256 <= (t) || (t) <= 512), icvSaturate8u[t+256])
#define CV_FAST_CAST_8S(t)   (assert(-256 <= (t) || (t) <= 256), icvSaturate8s[t+256])

#define CV_PASTE2(a,b) a##b
#define CV_PASTE(a,b) CV_PASTE2(a,b)

CV_INLINE  CvSize  icvGetMatSize( const CvMat* mat );
CV_INLINE  CvSize  icvGetMatSize( const CvMat* mat )
{
    CvSize size = { mat->width, mat->height };
    return size;
}

#include "_cvfuncn.h"

CV_INLINE  CvDataType icvDepthToDataType( int type );
CV_INLINE  CvDataType icvDepthToDataType( int type )
{
    return (CvDataType)(
            ((((int)cv8u)|((int)cv8s << 4)|((int)cv16s << 8)|
              ((int)cv32s << 12)|((int)cv32f << 16)|
              ((int)cv64f << 20)) >> CV_ARR_DEPTH(type)*4) & 15);
}

#endif/*__CVARR_H__*/
