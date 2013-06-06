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

#ifndef _CVTEST_H_
#define _CVTEST_H_

#ifdef WIN32
#include <windows.h>
#endif

#include "cv.hpp"
#include "cvaux.h"
#include "ats.h"
#include "highgui.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef min
#define min(a,b) (a) > (b) ? (b) : (a)
#endif

#ifndef max
#define max(a,b) (a) < (b) ? (b) : (a)
#endif

#define IPPI_CHECK( cvFun )                                                  \
  {                                                                          \
    CvStatus  result = cvFun;                                                \
    if( result != CV_NO_ERR )                                                 \
    {                                                                         \
      trsWrite(ATS_LST,                                                       \
               "The error code %d was returned by the function call\n"        \
               "%s\n"                                                         \
               "in file %s, line %d",                                         \
               result, #cvFun, __FILE__, __LINE__ );                          \
      return trsResult( TRS_FAIL,                                             \
                        "A function from OpenCV library returns error status" ); \
    }                                                                         \
  }

#define ATS_CHECK( atsFun )                                                   \
  {                                                                           \
    CvStatus  result = (CvStatus)atsFun;                                  \
    if( result != IPP_NO_ERR )                                                \
    {                                                                         \
      trsWrite(ATS_LST,                                                       \
               "The error code %d was returned by the function call\n"        \
               "%s\n"                                                         \
               "in file %s, line %d",                                         \
               result, #atsFun, __FILE__, __LINE__ );                         \
      return trsResult( TRS_FAIL,                                             \
                        "A function from ATS library returns error status" ); \
    }                                                                         \
  }

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare1Db, atsCompare1Dc, atsCompare1Dfl
//    Purpose:
//      Comparing two 1D array and writing results to SUM & LST files
//    Context:
//    Parameters:
//      ArrayAct - actual array
//      ArrayExp - expected array
//      lLen     - length of this arrays
//      Tol      - tolerable limit
//    Returns:
//      Number of differents elements
//    Notes:
//F*/
long atsCompare1Db(  uchar* ArrayAct, uchar* ArrayExp, long  lLen, int    Tol );
long atsCompare1Dc(  char*  ArrayAct, char*  ArrayExp, long  lLen, int    Tol );
long atsCompare1Dfl( float* ArrayAct, float* ArrayExp, long  lLen, double Tol );

long atsCompare2Db( uchar* ArrayAct, uchar* ArrayExp, CvSize size, int stride, int Tol );
long atsCompare2Dc( char* ArrayAct, char* ArrayExp, CvSize size, int stride, int Tol );
long atsCompare2Dfl( float* ArrayAct, float* ArrayExp, CvSize size, int stride, double Tol );



/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsConvert
//    Purpose: Converts one IPL image to another.
//             It is similar to iplConvert but supports 32F depth
//    Context:
//    Parameters:
//    Returns:
//    Notes:
//F*/
void atsConvert( IplImage* src, IplImage* dst );


/*
   Fills the whole image or selected ROI by random numbers.
   Supports only 8u, 8s and 32f formats
*/
void       atsFillRandomImage( IplImage *img, double low, double high );

CvPoint atsRandPoint( AtsRandState* rng_state, CvSize size );
CvPoint2D32f atsRandPoint2D32f( AtsRandState* rng_state, CvSize size );

/* Allocates/Deallocates the IPL image and (may be) clears it */
IplImage*  atsCreateImage( int w, int h, int depth, int nch, int clear_flag );
void atsReleaseImage( IplImage* img );

/* Extracts ROI data from the image and writes it in a single row */
void       atsGetDataFromImage( IplImage *img, void *data );

/* Writes linear data to the image ROI */
void       atsPutDataToImage( IplImage *img, void *data );


typedef void (*AtsBinArithmMaskFunc)( const CvArr* src1, const CvArr* src2,
                                     CvArr* dst, const CvArr* mask );

typedef void (*AtsUnArithmMaskFunc)( const CvArr* src, CvScalar scalar,
                                     CvArr* dst, const CvArr* mask );

typedef void (*AtsBinArithmFunc)( const CvArr* src1, const CvArr* src2, CvArr* dst );

void atsLinearFunc( const CvArr* src1arr, CvScalar alpha,
                    const CvArr* src2arr, CvScalar beta,
                    CvScalar gamma, CvArr* dstarr );

void atsMul( const CvArr* src1arr, const CvArr* src2arr, CvArr* dstarr );

#define ATS_LOGIC_AND  0
#define ATS_LOGIC_OR   1
#define ATS_LOGIC_XOR  2

void atsLogic( const CvArr* src1arr, const CvArr* src2arr, CvArr* dstarr, int op );
void atsLogicS( const CvArr* src1arr, CvScalar scalar, CvArr* dstarr, int op );

/*
   Retrieves various information about the image:
   *pData     - pointer to the whole image or ROI (if presents)
   *pStep     - distance between rows in bytes
   *pSz       - width and height of the whole image or ROI (if presents)
   *pDepth    - depth of image (in the IPL format: IPL_DEPTH_xxxx )
   *pChannels - number of channels
   *pBtPix    - bytes per pixel = ((depth & 255)>>3)*channels;

   Any of the destination pointers may be 0 if the appropriate parameter is'nt needed.
*/
void       atsGetImageInfo( IplImage* img, void** pData, int* pStep,
                            CvSize*  pSz, int*  pDepth, int* pChannels,
                            int* pBtPix );

/*
   The function applies min filter using specified structuring element.
*/
void       atsMinFilterEx( IplImage* src, IplImage* dst, IplConvKernel* B );

/*
   The function applies max filter using specified structuring element.
*/
void       atsMaxFilterEx( IplImage* src, IplImage* dst, IplConvKernel* B );


/*
   Create IplConvKernelFP for calclulating derivative
*/
IplConvKernelFP* atsCalcDervConvKernel( int Xorder, int Yorder, int apertureSize, int origin );

/*
   Replicates left and right ROI borders dx times,
   top and bottom ROI borders dy times.
*/
void atsReplicateBorders( IplImage* img, int dx, int dy );


/*
   The convolution function.
   Supports only 32fC1 images
*/
void atsConvolve( IplImage* src, IplImage* dst, IplConvKernelFP* ker );

/* This function calculates  kernels for Sobel operators */ 
void atsCalcKernel( int   datatype,
                 int   Xorder,
                 int   Yorder,
                 int   apertureSize,
                 char* KerX,
                 char* KerY,
                 CvSize* kerLens,
                 int origin);

/*
   Fills the whole image or selected ROI by random numbers.
   Supports only 8u, 8s and 32f formats
*/
void       atsFillRandomImageEx( IplImage *img, AtsRandState* state );

/* dst(x,y) = scale*src(x,y) + shift */
void  atsScaleAddImage( IplImage* src, IplImage* dst, double scale, double shift );
/* dst(x,y) = abs(scale*src(x,y) + shift) */
void  atsScaleAddAbsImage( IplImage* src, IplImage* dst, double scale, double shift );

/******************************************************************************/
/*                             Image statistics                               */
/******************************************************************************/
void       atsCalcImageStatistics( 
                    IplImage* img, IplImage* mask,
                    double* _min_val, double* _max_val,
                    CvPoint* _min_loc, CvPoint* _max_loc,
                    int* _non_zero, double* _sum,
                    double* _mean, double* _sdv,
                    double* _c_norm, double* _l1_norm, double* _l2_norm,
                    int* _mask_pix );

int       atsCannyStatistics(uchar* src,
                             CvSize roi,
                             int srcStep,
                             uchar* dst,
                             int dstStep,
                             int Sobord,
                             float lowThreshold,
                             float highThreshold,
                             int* zero_mag,
                             int* under_low,
                             int* above_high,
                             int* edges_in_nms,
                             int* components,
                             int* in_edges);


typedef struct
{
    /* spatial moments */
    double  m00;
    double  m10, m01;
    double  m20, m11, m02;
    double  m30, m21, m12, m03;

    /* central moments */
    double  mu20, mu11, mu02;
    double  mu30, mu21, mu12, mu03;

    /* normalized central moments */
    double  nu20, nu11, nu02;
    double  nu30, nu21, nu12, nu03;
}
AtsMomentState;


/*
  Function calculates spatial and central moments up to third order.
  <binary> mode means that pixels values treated as 1 if they are non zero and 0 if zero.
*/
void    atsCalcMoments( IplImage* img, AtsMomentState* state, int binary );

/*
  Convert internal representation to explicit form
*/
void  atsGetMoments( CvMoments* istate, AtsMomentState* astate );

/* calculates  sum (imgA(x,y) - deltaA)*(imgB(x,y) - deltaB) */
double atsCrossCorr( IplImage* imgA, IplImage* imgB, double deltaA, double deltaB );

/* creates contour which consist of convex hull vertices */
/* hull is CvSeq<CvPoint*>                               */
CvSeq* atsCvtHullToContour( CvSeq* hull, CvMemStorage* storage );


/******************************************************************************/
/*                                 Drawing                                    */
/******************************************************************************/

/* The function draws line in 8uC1/C3 image */
void  atsDrawLine( IplImage* img, float x1, float y1, float x2, float y2, int color );

/* The function draws ellipse arc in 8uC1/C3 image */
void  atsDrawEllipse( IplImage* img, float xc, float yc, float a, float b,
                      float angle, float arc0, float arc1, int color );

/* The function draws conic arc in 8uC1/C3 image */
void  atsDrawConic( IplImage* img, float xc, float yc, float mag, float e,
                    float angle, float arc0, float arc1, int color );

int   atsCalcQuadricCoeffs( double xc, double yc, double mag, double e,
                            double angle, double arc0, double arc1,
                            double* A, double* B, double* C, double* D, double* E,
                            CvPoint* pt1, CvPoint* pt2 );

/* make zero border in the image */
void  atsClearBorder( IplImage* img );

/* fills an 8uC1 image with blobs - rotated ellipses */
void  atsGenerateBlobImage( IplImage* img, int min_blob_size, int max_blob_size,
                            int blob_count, int min_brightness, int max_brightness,
                            AtsRandState* rng_state );

/******************************************************************************/
/*                             Display routines                               */ 
/******************************************************************************/

int   atsCreateWindow( const char* name, CvPoint wnd_org, CvSize wnd_size );
void  atsDisplayImage( IplImage* img, int window, CvPoint dst_org, CvSize dst_size );
void  atsDestroyWindow( int window );

/******************************************************************************/
/*                     Reading images from file                               */
/******************************************************************************/

/* Reads image from the disk and creates IplImage from it */  
IplImage* atsCreateImageFromFile( const char* filename );


/******************************************************************************/
/*                     Helper contour processing functions                    */
/******************************************************************************/

CvSeq* atsCreateRandomContours( IplImage* img, CvMemStorage* storage,
                                CvContourRetrievalMode mode,
                                CvChainApproxMethod approx,
                                AtsRandState* rng_state );

/******************************************************************************/
/*                                 Set of contours                            */
/******************************************************************************/

typedef CvSeq* ( *Contour )( CvMemStorage* storage );

/******************************************************************************/
/*                                 Defines                                    */
/******************************************************************************/

#define ATS_SWAP( a, b, temp )  ((temp) = (a), (a) = (b), (b) = temp)
#define ATS_RANGE( x, a, b )  ((a) <= (x) && (x) < (b))

/* min & max without jumps */
#define ATS_MIN(a, b)  ((a) ^ (((a)^(b)) & (((a) < (b)) - 1)))
#define ATS_MAX(a, b)  ((a) ^ (((a)^(b)) & (((a) > (b)) - 1)))

/* Converts float to 2-complement representation for integer comparing */
#define ATS_TOGGLE_FLT(x)  (((x)&0x7fffffff)^(((int)(x))>>31))

#define ATS_DIM(a)         (sizeof(a)/sizeof((a)[0]))


/* Increases the <value> by adding or multiplying by the <delta> */
#define ATS_INCREASE( value, delta_type, delta ) \
    ((value) = (delta_type) == 0 ? (value)+(delta) : (value)*(delta))


#ifndef ATS_TIC_MAX
#ifdef WIN32
#define ATS_TIC_MAX  0x7fffffffffffffffI64
#else
#define ATS_TIC_MAX  0x7fffffffffffffffLL
#endif
#endif

#define ATS_START_TIMING() int64 temp = atsGetTickCount();
#define ATS_END_TIMING()   temp = atsGetTickCount() - temp; tics = ATS_MIN( tics, temp );

#define ATS_MEASURE( act ) \
    ATS_START_TIMING()     \
    (act);                 \
    ATS_END_TIMING()


/* patch */
typedef enum {
   cv1u,
   cv8u, cv8s,
   cv16u, cv16s, cv16sc,
   cv32u, cv32s, cv32sc,
   cv32f, cv32fc,
   cv64u, cv64s, cv64sc,
   cv64f, cv64fc
} CvDataType;

#define _CV_C            1
#define _CV_L1           2
#define _CV_L2           4
#define _CV_RELATIVE     8

#define _CV_RELATIVE_C   (_CV_RELATIVE | _CV_C)
#define _CV_RELATIVE_L1  (_CV_RELATIVE | _CV_L1)
#define _CV_RELATIVE_L2  (_CV_RELATIVE | _CV_L2)

#define _CV_DIFF        16

#define _CV_DIFF_C   (_CV_DIFF | _CV_C)
#define _CV_DIFF_L1  (_CV_DIFF | _CV_L1)
#define _CV_DIFF_L2  (_CV_DIFF | _CV_L2)


#define CV_ORIGIN_TL  0
#define CV_ORIGIN_BL  1

void* icvAlloc_( int lSize );
void  icvFree_( void** ptr );

void* _dbgAlloc_( int size, const char* file, int line);
void  _dbgFree_( void** pptr,const char* file, int line);

#define icvAlloc( size ) icvAlloc_( size )
#define icvFree( ptr ) icvFree_( (void**)(ptr) )


#ifdef __cplusplus
}
#endif

#endif /* _CVTEST_H_ */

/* End of file. */
