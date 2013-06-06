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

#ifndef _ATS_H_
#define _ATS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "trsapi.h"
#include "assert.h"

#include "cv.h"

/*#include "ippdefs.h"*/
/*#include "optcv.h"*/

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WIN32
typedef unsigned char       uchar;
typedef unsigned short      ushort;
#endif

/* define 64-bit integers */
#ifdef WIN32
#if _MSC_VER > 1000
    typedef __int64 int64;
#else
    typedef long long int64;
#endif
#endif


/****************************************************************************************/
/*                              Warnings Disabling                                      */
/****************************************************************************************/
#pragma warning(disable : 4514) /* unreferenced inline function has been */
                                /* removed                               */
#pragma warning(disable : 4127) /* conditional expression is constant    */
                                /* for no warnings in _ASSERT            */

/****************************************************************************************/
/*                              Finctions declaration                                   */
/****************************************************************************************/


/*F-------------------------------------------------------------------------------------*/
/*    Name:    atsInitRandom                                                            */
/*    Purpose:                                                                          */
/*      Initialazing by randomize value                                                 */
/*    Context:                                                                          */
/*    Parameters:                                                                       */
/*      Min - minimal bound                                                             */
/*      Max - maximum bound                                                             */
/*    Returns:                                                                          */
/*    Notes:                                                                            */
/*F-------------------------------------------------------------------------------------*/
double atsInitRandom( double Min, double Max );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1bInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1bInitRandom( double Min, double Max, unsigned char* pDst, long lLen );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1cInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1cInitRandom( double Min, double Max, char* pDst, long lLen );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1iInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1iInitRandom( double Min, double Max, int* pDst, long lLen );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1flInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1flInitRandom( double Min, double Max, float* pDst, long lLen );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1flInitGradRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1flInitGradRandom( double Min, double Max, float* pDst, long lLen );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsbInitEllipse
//    Purpose: filling the source 2D array by constant value
//    Context:
//    Parameters:
//      Src - source array
//      width - width of source array
//      height - height of source array
//      step - width step
//      x, y - center of ellipse
//      major - major axis of ellipse
//      minor - minor axis of ellipse
//      orientation - orientation of ellipse
//      value - the constant value which will be set within elipse
//    Returns:
//    Notes:
//      orientation is the angle from horisontal clockwise
//F*/
void atsbInitEllipse( uchar* Src,
                      int    width,
                      int    height,
                      int    step,
                      int    x,
                      int    y,
                      int    major,
                      int    minor,
                      float  orientation,
                      uchar  value );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsfInitEllipse
//    Purpose: filling the source 2D array by constant value
//    Context:
//    Parameters:
//      Src - source array
//      width - width of source array
//      height - height of source array
//      step - width step
//      x, y - center of ellipse
//      major - major axis of ellipse
//      minor - minor axis of ellipse
//      orientation - orientation of ellipse
//      value - the constant value which will be set within elipse
//    Returns:
//    Notes:
//      orientation is the angle from horisontal clockwise
//F*/
void atsfInitEllipse( float* Src,
                      int    width,
                      int    height,
                      int    step,
                      int    x,
                      int    y,
                      int    major,
                      int    minor,
                      float  orientation,
                      float  value );

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompSingle
//    Purpose:                                                                  
//      Detailed Comparing two float values      
//    Context:                                                                  
//    Parameters:                                                               
//      flFirst - first value                                               
//      flSecond- second value                                             
//      dbAcc - accuracy                                     
//                                                 
//    Returns:                                                                  
//      1 if not equal 
//      0 if equal                                           
//    Notes:                                                                    
//F*/
long atsCompSingle(float flFirst,
                   float flSecond,
                   double dbAcc);
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompSinglePrec
//    Purpose:
//      Detailed Comparing two float arrays
//    Context:
//    Parameters:
//      flFirstArray - first array
//      flSecondArray - second array
//      lLen       - lenght of this arrays
//      dbAcc      - precision
//    Returns:
//      Number of nonequal elements
//    Notes:
//F*/
long atsCompSinglePrec(float* flFirstArray, float* flSecondArray, long lLen, double dbAcc);
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompDoublePrec
//    Purpose:                                                                  
//      Detailed Comparing two double arrays      
//    Context:                                                                  
//    Parameters:                                                               
//      flFirstArray - first array                                               
//      flSecondArray - second array                                             
//      lLen       - lenght of this arrays                                      
//                                                 
//    Returns:                                                                  
//      Number of nonequal elements                                           
//    Notes:                                                                    
//F*/
long atsCompDoublePrec(double* flFirstArray,
                       double* flSecondArray,
                       long lLen,
                       double dbAcc);
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare1Db, atsCompare1Dc, atsCompare1Dfl
//    Purpose:
//      Comparing two 1D array and writing results to SUM & LST files
//    Context:
//    Parameters:
//      ArrayAct - actual array
//      ArrayExp - expected array
//      lLen     - lenght of this arrays
//      Tol      - tolerable limit
//    Returns:
//      Number of differents elements
//    Notes:
//F*/
long atsCompare1Db(  uchar* ArrayAct, uchar* ArrayExp, long  lLen, int    Tol );
long atsCompare1Dc(  char*  ArrayAct, char*  ArrayExp, long  lLen, int    Tol );
long atsCompare1Dfl( float* ArrayAct, float* ArrayExp, long  lLen, double Tol );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsFindFirstErr
//    Purpose:
//      Finds first point in the ROI where the images differs much
//    Context:
//    Parameters:
//      imgA - first image
//      imgB - second image
//      eps  - maximal allowed difference between images
//    Returns:
//      First "bad" point coordinates (they are counted from ROI origin).
//F*/
CvPoint  atsFindFirstErr( IplImage* imgA, IplImage* imgB, double eps );

#ifndef WIN32
#define __inline static
#endif

/* Compare two angles in (0..360) */
__inline double atsCompareAngles( double angle1, double angle2 )
{
    double err = fabs(angle1 - angle2);
    double err1 = fabs(err - 360);
    return err < err1 ? err : err1;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1flInitGrad
//    Purpose:
//      Initialazing float array by gradient randomize value (every previous
//      value least next value)
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1flInitGrad( double Min, double Max, float* pDst, long lLen );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ataGetTickCount
//    Purpose: Returns the number of processor tics from turn on the processor
//    Context:
//    Parameters:
//    Returns:
//    Notes:
//F*/

#if _MSC_VER >= 1200
#pragma warning(disable : 4035) /* conditional expression is constant    */
                                /* for no warnings in _ASSERT            */
#endif

CV_INLINE int64 atsGetTickCount()
{
#ifdef WIN32
    __asm{
        _emit 0fh;
        _emit 31h;
    }
#elif defined __GNUC__
    __asm("rdtsc\n\r");
#else
    return 0;
#endif
}

#if _MSC_VER >= 1200
#pragma warning(once : 4035) /* conditional expression is constant    */
                             /* for no warnings in _ASSERT            */
#endif

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsTimerStart
//    Purpose:   Setting privileges level for task highest
//    Context:
//    Parameters:
//    Returns:
//    Notes:
//F*/
void atsTimerStart( int timer );

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsTimerStop
//    Purpose:   Cleaning privileges level for task highest
//    Context:
//    Parameters:
//    Returns:   
//    Notes:     
//F*/
void atsTimerStop( int timer );


extern char* atsTimingClass;  /* string "Timing" */
extern char* atsAlgoClass;    /* string "Algorithm" */
extern int   atsCPUFreq;      /* CPU frequency (MHz) */

#define  ATS_TICS_TO_USECS(tics)    (((double)(tics))/atsCPUFreq)

/******************************************************************************/
/*                     Extended random number generation                      */
/******************************************************************************/

typedef struct
{
    unsigned  seed;
    int       ia, ib;  /* for integer random numbers */
    float     fa, fb;  /* for float random numbers */
    int       shift;   /* if (upper - lower) is power of two */
    int       mask;    /* float mask */
} AtsRandState;

unsigned  atsGetSeed( void );  /* get seed using processor tick counter */

/* will generate random numbers in [lower,upper) */
void  atsRandInit( AtsRandState* state, double lower, double upper, unsigned seed );
void  atsRandSetBounds( AtsRandState* state, double lower, double upper );
void  atsRandSetFloatBits( AtsRandState* state, int bits );
float atsRand32f( AtsRandState* state );
void  atsbRand32f( AtsRandState* state, float* vect, int len );
int   atsRand32s( AtsRandState* state );
void  atsbRand32s( AtsRandState* state, int* vect, int len );
void  atsbRand16s( AtsRandState* state, short* vect, int len );
void  atsbRand8u( AtsRandState* state, uchar* vect, int len );
void  atsbRand8s( AtsRandState* state, char* vect, int len );
void  atsbRand64d( AtsRandState* state, double* vect, int len );

/* simply returns seed */
int   atsRandPlain32s( AtsRandState* state );
/* return float: 0..1 */
float atsRandPlane32f( AtsRandState* state );

int   atsIsNaN( double x );

/******************************************************************************/
/*                                Data input/output                           */
/******************************************************************************/

float*  atsReadMatrix( const char* filename, int* m, int* n );
void    atsWriteMatrix( const char* filename, int m, int n, float* data );


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsInitModuleTestData
//    Purpose:   Init system path to test data
//    Context:   
//    Parameters:
//              module           - path to module (argv[0])
//              path_from_module - path from module
//    Returns:   
//    Notes:     
//F*/
void atsInitModuleTestData( char* module, char* path_from_module );

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsGetTestDataPath
//    Purpose:   Init buffer by path to test data file
//    Context:   
//    Parameters:
//              buffer    - buffer to init
//              folder    - test data folder (may be NULL)
//              filename  - data file (may be NULL)
//              extention - file extention (may be NULL)
//    Returns:
//              returns pointer to buffer
//    Notes:     
//F*/
char* atsGetTestDataPath( char* buffer, char* folder, char* filename, char* extention );

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsLoadPrimitives
//    Purpose:   loads ipp & opt primitives
//    Context:   
//    Parameters:
//    Returns:   
//    Notes:     
//F*/
int atsLoadPrimitives( int argc, char** argv );

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


#define ATS_TIC_MAX  0x7fffffffffffffffI64

#define ATS_START_TIMING() int64 temp = atsGetTickCount();
#define ATS_END_TIMING()   temp = atsGetTickCount() - temp; tics = ATS_MIN( tics, temp );

#define ATS_MEASURE( act ) \
    ATS_START_TIMING()     \
    (act);                 \
    ATS_END_TIMING()

#define ATS_COOLMEASURE(func)                       \
{                                                   \
    int i,j;                                        \
    int64 time_min = 0;                           \
                                                    \
    atsTimerStart( 0 );                             \
    for(j=0;j<10;j++)                              \
    {                                               \
        int64 temp = atsGetTickCount();           \
        for(i=0;i<10;i++) func;                     \
        temp = atsGetTickCount() - temp;            \
        if(!time_min) time_min = temp;              \
        else time_min = ATS_MIN( time_min, temp );  \
    }                                               \
    atsTimerStop( 0 );                              \
                                                    \
    tics = (time_min) / 10;                         \
}


#undef NULL
#define NULL 0

#define ATS_CON TW_CON | TW_RUN | TW_DEBUG | TW_RERUN
#define ATS_LST TW_LST | TW_RUN | TW_DEBUG | TW_RERUN
#define ATS_SUM TW_SUM | TW_RUN | TW_DEBUG | TW_RERUN

#define USECS 1000000
#define CPU   1000000


#ifdef __cplusplus
}
#endif



#endif /* _ATS_H_ */

/* End of file. */
