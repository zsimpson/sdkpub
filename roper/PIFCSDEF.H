/*   PI controller FOCUSING external definition and define file 
*    $Logfile: /WinX32 V2.3/INCLUDE/PIFCSDEF.H $
*       $Date: 9/09/98 10:50a $
******************************************************************
*
*       pifcsdef.h
*
* Copyright (C) 1997, 1998 Princeton Instruments
* All rights reserved
*
*
******************************************************************
*
*  contains the Declarations & Enumerators for the simple dll
*
*                               written by djk
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 9/09/98 10:50a $
*
******************************************************************
*
*  $Log: /WinX32 V2.3/INCLUDE/PIFCSDEF.H $
*  
*  10    9/09/98 10:50a Bob
*  Removed final comma from enumerated types for mac...
*  
*  8     1/22/98 2:35p Charlie
*  Added 0 to 48 lut for 5Mhz camera.
*  
*  7     1/14/98 8:16p Charlie
*  Added new Lut bit ranges for 5Mhz camera.
*  
*  5     8/29/96 10:51a Terry
*  Add #ifndef
*  
*  4     7/18/96 2:02p Dan
*  
*  3     5/08/96 8:59a Dan
*  changed enums ZOOM_ID & PAN_ID to start at 1
 * 
 * 2     10/16/95 9:46a Dan
 * Moved from $/WinX/PRODUCT/COMMON
 * 
 * 1     10/13/95 3:28p Admin
 * Latest source from PVCS
*  
*  
*
******************************************************************
*/

#if !defined  PIFCSDEF_H
#define       PIFCSDEF_H


/*
******************************************************************************
        include files
*/

/*
******************************************************************************
        defines
*/

/* definitions of enumeration types */

/* ########################################################### */
/*                  LEVEL 2 DLLs                               */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Easy_Focus                            */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Controller Easy Focus setup                                               */
/* int PICM_Easy_Focus                                                       */
/*   int type                 ::  focus mode, see enum FOCUS_TYPE            */
/*   double nominal_exposure  ::  nominal exposure                           */
/*   int zoom                 ::  zoom multiplier, see enum ZOOM_ID          */
/*   int pan                  ::  relative pan position, see enum PAN_ID     */
/*   double *actual_exposure  ::  return calculated, but set exposure        */
/*   int *zoom_pattern        ::  return calculated, but set zoom pattern    */
/*   unsigned int *error_code ::  Error code if function returns false       */
/*   

/*  desired Focus type */
/*  #### used by PICM_Easy_Focus  param 1  #### */

enum FOCUS_TYPE        /*  focus type  */
{
    OPTIMIZED_FOCUS = 1,    
    BINNING_FOCUS,
    DECIMATION_FOCUS
};

enum ZOOM_ID        /*  Zoom values  */
{
    ZX1 = 1,       /*  Zoom x1 - no   Pan  */
    ZX2,           /*  Zoom x2 - with Pan  */
    ZX4           /*  Zoom x4 - with Pan  */
};

enum PAN_ID         /*  Pan values   */
{
    PAN_TL = 1,     /*  Top Left       */
    PAN_TC,         /*  Top Center     */
    PAN_TR,         /*  Top Right      */
    PAN_CL,         /*  Center Left    */
    PAN_CC,         /*  Center Center  */
    PAN_CR,         /*  Center Right   */
    PAN_BL,         /*  Bottom Left    */
    PAN_BC,         /*  Bottom Center  */
    PAN_BR         /*  Bottom Right   */
};


/* ##### ERROR CODES for PICM_Easy_Focusing ##### */

#define FOCUS_UNKNOWN_ERROR         0x0001  /* unknown error occurred        */

#define CONTROLLER_NO_SUPPORT_ERROR 0x0002  /* controller not supported      */

#define CCD_NOT_SUPPORTED_ERROR     0x0004  /* requested CCD not supported   */

#define BAD_NOMINAL_EXPOSURE_ERROR  0x0008  /* requested nominal exposure    */                                        
                                            /* less than supported minimun   */
                                            /* shutter speed                 */

#define KAF1400_MIN_SHUTTER  0.020  /*  Kodak 1035x1317 minimum shutter ms   */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_lut_type                          */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* PICM_Set_lut_type (lut_type) */
enum ctrl_lookuptype
{
    USER_LUT = 0,
    LOOKUP_LINEAR = 1,
    LOOKUP_INVERSE_LINEAR,
    LOOKUP_LOG,
    LOOKUP_INVERSE_LOG,
    LOOKUP_EXPONENTIAL,
    LOOKUP_SQUARE,
    LOOKUP_SQRT,
    LOOKUP_2_THRESH_BINARY,
    LOOKUP_THRESH_BINARY,
    LOOKUP_GAMMA,
    BIT_RANGE_0_64,      /* PentaMax & 5MHz ST133 */
    BIT_RANGE_0_128,     /* PentaMax & 5MHz ST133 */
    BIT_RANGE_0_256,     /* PentaMax & 5MHz ST133 */
    BIT_RANGE_2_512,     /* PentaMax & 5MHz ST133 */
    BIT_RANGE_4_1024,    /* PentaMax & 5MHz ST133 */
    BIT_RANGE_8_2048,    /* PentaMax & 5MHz ST133 */
    BIT_RANGE_16_4096,   /* PentaMax & 5MHz ST133 */
    BIT_RANGE_0_32,      /* 5MHz ST133 only */
    BIT_RANGE_0_48,      /* 5MHz ST133 only */
    BIT_RANGE_0_96,      /* 5MHz ST133 only */
    BIT_RANGE_0_192,     /* 5MHz ST133 only */
    BIT_RANGE_1_384,     /* 5MHz ST133 only */
    BIT_RANGE_3_768,     /* 5MHz ST133 only */
    BIT_RANGE_6_1536,    /* 5MHz ST133 only */
    BIT_RANGE_12_3072    /* 5MHz ST133 only */
                    
};


#endif

/*
        end of pifcsdef.h
*********************************************************************
*/
