/*
//
//               INTeL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//
//  Purpose: IPL Error Handling Module
//
*/

#if !defined (__IPLERROR_H__) || defined (_OWN_BLDPCS)
#define __IPLERROR_H__

#ifdef __cplusplus
extern "C" {
#endif


/*==========================================================================
      Section: Error Handling Functions
 ==========================================================================*/
 
/*------------------------  Error Call definition  ------------------------*/

#if !defined _OWN_BLDPCS

typedef IPLStatus (__STDCALL *IPLErrorCallBack)(IPLStatus status,    
                                          const char *funcname,
                                          const char *context, 
                                          const char *file,
                                          int   line);
#endif /* _OWN_BLDPCS */

/*----------------------  IPLErrStatus Declaration  -----------------------*/

#define _StsMaskImg_ (-100)

#define IPL_StsOk                    0  /* everithing is ok                */
#define IPL_StsBackTrace            -1  /* pseudo error for back trace     */
#define IPL_StsError                -2  /* unknown /uiplecified error      */
#define IPL_StsInternal             -3  /* internal error (bad state)      */
#define IPL_StsNoMem                -4  /* Insufficient memory             */
#define IPL_StsBadArg               -5  /* function arg/param is bad       */
#define IPL_StsBadFunc              -6  /* unsupported function            */
#define IPL_StsNoConv               -7  /* iter. didn't converge           */
#define IPL_StsAutoTrace            -8  /* Tracing                         */

#define IPL_HeaderIsNull            -9  /* image header is NULL            */
#define IPL_BadImageSize            -10 /* Image size is invalid           */
#define IPL_BadOffset               -11 /* Offset is invalid               */
#define IPL_BadDataPtr              -12 /* Image must be tiled or must have nonzero data pointer */
#define IPL_BadStep                 -13 /**/
#define IPL_BadModelOrChSeq         -14 /**/
#define IPL_BadNumChannels          -15 /**/
#define IPL_BadNumChannel1U         -16 /**/
#define IPL_BadDepth                -17 /**/
#define IPL_BadAlphaChannel         -18 /**/
#define IPL_BadOrder                -19 /**/
#define IPL_BadOrigin               -20 /**/
#define IPL_BadAlign                -21 /**/
#define IPL_BadCallBack             -22 /**/
#define IPL_BadTileSize             -23 /**/
#define IPL_BadCOI                  -24 /**/
#define IPL_BadROISize              -25 /**/

#define IPL_MaskIsTiled             -26 /**/

#define IPL_StsNullPtr                -27 /* Null pointer */
#define IPL_StsVecLengthErr           -28 /* Incorrect vector length */
#define IPL_StsFilterStructContentErr -29 /* Incorr. filter structure content */
#define IPL_StsKernelStructContentErr -30 /* Incorr. transform kernel content */
#define IPL_StsFilterOffsetErr        -31 /* Incorrect filter ofset value */

#define IPL_MaskBadImageSize        IPL_BadImageSize   + _StsMaskImg_
#define IPL_MaskBadOffset           IPL_BadOffset      + _StsMaskImg_
#define IPL_MaskBadDataPtr          IPL_BadDataPtr     + _StsMaskImg_
#define IPL_MaskBadStep             IPL_BadStep        + _StsMaskImg_
#define IPL_MaskBadModelOrChSeq     IPL_BadModelOrChSeq+ _StsMaskImg_
#define IPL_MaskBadNumChannels      IPL_BadNumChannels + _StsMaskImg_
#define IPL_MaskBadDepth            IPL_BadDepth       + _StsMaskImg_
#define IPL_MaskBadAlphaChannel     IPL_BadAlphaChannel+ _StsMaskImg_
#define IPL_MaskBadOrder            IPL_BadOrder       + _StsMaskImg_
#define IPL_MaskBadOrigin           IPL_BadOrigin      + _StsMaskImg_
#define IPL_MaskBadAlign            IPL_BadAlign       + _StsMaskImg_
#define IPL_MaskBadCOI              IPL_BadCOI         + _StsMaskImg_
#define IPL_MaskBadROISize          IPL_BadROISize     + _StsMaskImg_


/* /////////////////////////////////////////////////////////////////////////
// Name:       iplGetErrStatus
// Purpose:    Gets last error status
// Returns:    
// Parameters: 
//
// Notes:      
*/

IPLAPI(IPLStatus, iplGetErrStatus,(void))


/* /////////////////////////////////////////////////////////////////////////
// Name:       iplSetErrStatus
// Purpose:    Sets error status    
// Returns:    
// Parameters: 
//
// Notes:      
*/

IPLAPI(void, iplSetErrStatus,(IPLStatus status))


/*----------------------  IPLStdErrMode Declaration  -----------------------*/

#define IPL_ErrModeLeaf     0           /* Print error and exit program     */
#define IPL_ErrModeParent   1           /* Print error and continue         */
#define IPL_ErrModeSilent   2           /* Don't print and continue         */


/* /////////////////////////////////////////////////////////////////////////
// Name:       iplGetErrMode, iplSetErrMode
// Purpose:    gets/sets error mode
// Returns:    
// Parameters: 
//
// Notes:      
*/

IPLAPI(int,  iplGetErrMode,(void))
IPLAPI(void, iplSetErrMode,(int mode))



/* /////////////////////////////////////////////////////////////////////////
// Name:       iplError
// Purpose:    performs basic error handling
// Returns:    last status
// Parameters: 
//
// Notes:      
*/

IPLAPI(IPLStatus,   iplError,(IPLStatus status, const char *func,
                             const char *context, const char *file,int line))


/* /////////////////////////////////////////////////////////////////////////
// Name:       iplErrorStr
// Purpose:    translates an error status code into a textual description
// Returns:    
// Parameters: 
//
// Notes:      
*/

IPLAPI(const char*, iplErrorStr,(IPLStatus status))


/* /////////////////////////////////////////////////////////////////////////
// Name:       iplRedirectError
// Purpose:    assigns a new error-handling function
// Returns:    old error-handling function
// Parameters: new error-handling function
//
// Notes:      
*/

IPLAPI(IPLErrorCallBack, iplRedirectError,(IPLErrorCallBack iplErrorFunc))

/*-----------------  Predefined error-handling functions  -----------------*/

/*  
    Output to:
        iplNulDevReport - nothing
        iplStdErrReport - console (printf)
        iplGuiBoxReport - MessageBox (_WIN32)
*/
IPLAPI(IPLStatus, iplNulDevReport,(IPLStatus   status, const char *funcname,
                                  const char *context,const char *file,
                                        int   line))

IPLAPI(IPLStatus, iplStdErrReport,(IPLStatus   status, const char *funcname,
                                  const char *context,const char *file,
                                        int   line))

IPLAPI(IPLStatus, iplGuiBoxReport,(IPLStatus   status, const char *funcname,
                                  const char *context,const char *file,
                                        int   line))



/*-------------------------------  Macros  --------------------------------*/
#define IPL_ERROR(status,func,context)\
                iplError((status),(func),(context),__FILE__,__LINE__)

#define IPL_ERRCHK(func,context)\
                ((iplGetErrStatus() >= 0) ? IPL_StsOk \
                : IPL_ERROR(IPL_StsBackTrace,(func),(context)))

#define IPL_ASSERT(expr,func,context)\
                ((expr) ? IPL_StsOk \
                : IPL_ERROR(IPL_StsInternal,(func),(context)))

#define IPL_RSTERR() (iplSetErrStatus(IPL_StsOk))


#ifdef __cplusplus
}
#endif

#endif /* __IPLERROR_H__ */
