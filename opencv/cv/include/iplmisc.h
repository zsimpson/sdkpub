/*
//
//               INTeL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//
//  Purpose: IPL Misc Functions
//
*/

#if !defined (__IPLMISC_H__) || defined (_OWN_BLDPCS)
#define __IPLMISC_H__

#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
      Section: Memory Allocation Functions
 ==========================================================================*/

/*//////////////////////////////////////////////////////////////////////////
// Name:       iplMalloc, iplwMalloc, ipliMalloc, iplsMalloc, ipldMalloc
// Purpose:    Allocate memory aligned on 32 bytes  
// Returns:    a pointer to an aligned memory block or NULL if no memory. 
// Parameters: length - size of required memory block in elements. 
//             For iplMalloc length in bytes, for others a type of an 
//             element depends on behalf of function (see type of return). 
//
// Notes:     The only function to free the memory allocated by any of 
//            these functions is iplFree().
*/

IPLAPI(void*,  iplMalloc, (int length))
IPLAPI(short*, iplwMalloc,(int length))
IPLAPI(int*,   ipliMalloc,(int length))
IPLAPI(float*, iplsMalloc,(int length))
IPLAPI(double*,ipldMalloc,(int length))



/* /////////////////////////////////////////////////////////////////////////
// Name:       iplFree
// Purpose:    Frees memory allocated by one of the ipl?Malloc functions.
// Returns:    
// Parameters: 
//
// Notes:      The function iplFree() cannot be used to free memory 
//             allocated by standard functions like malloc() or calloc().
*/

IPLAPI(void, iplFree, (void* ptr))


/*==========================================================================
      Section: Misc macros and definitions
 ==========================================================================*/

#define IPL_EPS  (1.0E-12)
#define IPL_PI   (3.14159265358979324)  /* ANSI C does not support M_PI */
#define IPL_2PI  (6.28318530717958648)
#define IPL_PI_2 (1.57079632679489662)
#define IPL_PI_4 (0.785398163397448310)

#define IPL_DegToRad(deg) ((deg)/180.0 * IPL_PI)

#define IPLsDegToRad(deg) ((float) ((deg)/180.0 * IPL_PI))
#define IPLdDegToRad(deg) ((double)((deg)/180.0 * IPL_PI))

#ifndef MAX
# define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
# define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif
    
#ifndef FALSE
# define FALSE 0
# define TRUE  1
#endif


#define IPL_COPY_IMAGE_HEADER(src,dst,depth)\
    dst = iplCreateImageHeader( src->nChannels, src->alphaChannel, \
    depth, src->colorModel, src->channelSeq, src->dataOrder, \
    src->origin, src->align, src->width, src->height, NULL, NULL, NULL, NULL)

/*
   Notes: If you use macro definitions iplDecimateFit, 
   iplZoomFit, or iplResizeFit, Please make sure that SRC 
   and DST parameters aren't NULL
*/
#define iplResizeFit(SRC,DST,INTER)\
    iplResize( SRC, DST, \
    DST->roi ? DST->roi->width : DST->width, \
    SRC->roi ? SRC->roi->width : SRC->width, \
    DST->roi ? DST->roi->height : DST->height, \
    SRC->roi ? SRC->roi->height : SRC->height, INTER )

#define iplDecimateFit(SRC,DST,INTER)\
    iplDecimate( SRC, DST, \
    DST->roi ? DST->roi->width : DST->width, \
    SRC->roi ? SRC->roi->width : SRC->width, \
    DST->roi ? DST->roi->height : DST->height, \
    SRC->roi ? SRC->roi->height : SRC->height, INTER )

#define iplZoomFit(SRC,DST,INTER)\
    iplZoom( SRC, DST, \
    DST->roi ? DST->roi->width : DST->width, \
    SRC->roi ? SRC->roi->width : SRC->width, \
    DST->roi ? DST->roi->height : DST->height, \
    SRC->roi ? SRC->roi->height : SRC->height, INTER )




/*F*
//  Name:           iplRotateCenter
//  Purpose:        rotates image about (xCenter, yCenter) on angle.
//  Context:        macro
//  Returns:        
//  Parameters:
//      srcImage    The source image.
//      dstImage    The resultant image.
//      interpolate The type of interpolation to perform for resampling
//                  the input image. The following are currently supported.
//                  IPL_INTER_NN     Nearest neighbour interpolation.
//                  IPL_INTER_LINEAR Linear interpolation.
//                  IPL_INTER_CUBIC  Cubic convolution interpolation.
//                  IPL_SMOOTH_EDGE  Smooth edges. Can be added to
//                                   interpolation by using bitwise logical OR.
//      angle       The angle
//      xCenter     The x coordinate of center
//      yCenter     The y coordinate of center
//  Notes:
*F*/

#define iplRotateCenter(srcImage, dstImage, angle,                     \
                        xCenter, yCenter, interpolate)                 \
{                                                                      \
    double xShift = 0, yShift = 0;                                     \
    iplGetRotateShift(xCenter, yCenter, angle, &xShift, &yShift);      \
    iplRotate(srcImage, dstImage, angle, xShift, yShift, interpolate); \
}


/*----------------------  Code for channel sequence  ----------------------*/
#define IPL_CSEQ_G      0x00000047      /* "G"    */
#define IPL_CSEQ_GRAY   0x59415247      /* "GRAY" */
#define IPL_CSEQ_BGR    0x00524742      /* "BGR"  */
#define IPL_CSEQ_BGRA   0x41524742      /* "BGRA" */
#define IPL_CSEQ_RGB    0x00424752      /* "RGB"  */
#define IPL_CSEQ_RGBA   0x41424752      /* "RGBA" */



/*==========================================================================
      Section: Misc functions
 ==========================================================================*/

/* /////////////////////////////////////////////////////////////////////////
// Name:       iplCheckImageHeader
// Purpose:    Checks image header
// Returns:    returns IPL_StsOk if header is valid, 
//             else returns error status.
// Parameters: image header
//
// Notes:      
*/

IPLAPI ( IPLStatus, iplCheckImageHeader, ( const IplImage* hdr ) )


/*---------------------------  Library Version  ---------------------------*/
#if !defined _OWN_BLDPCS

typedef struct _IPLLibVersion {
  int    major;                         /* e.g. 1                          */
  int    minor;                         /* e.g. 00                         */
  int    build;                         /* e.g. 01                         */
  const char * Name;                    /* e.g. "ipl6l.lib","iplm5.dll"    */
  const char * Version;                 /* e.g. "v1.00"                    */
  const char * InternalVersion;         /* e.g. "[1.00.01, 07/25/96]"      */
  const char * BuildDate;               /* e.g. "Jun 1 96"                 */
  const char * CallConv;                /* e.g. "DLL","Microsoft*","Borland*"*/
} IPLLibVersion;

#endif


/* /////////////////////////////////////////////////////////////////////////
// Name:       iplGetLibVersion
// Purpose:    
// Returns:    the structure of information about  version of IPL library
// Parameters: 
//
// Notes:      
*/

IPLAPI(const IPLLibVersion*, iplGetLibVersion,(void))

#ifdef __cplusplus
}
#endif

#endif /* __IPLMISC_H__ */
