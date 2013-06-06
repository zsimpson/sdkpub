/*   PI controller Video routines (RS170)
*    $Logfile: /WinX32 V2.5/INCLUDE/pividdef.h $
*       $Date: 5/05/00 7:45a $
******************************************************************
*
*       pividdef.h
*
******************************************************************
*
*  contains the Declarations & Enumerators for the simple dll
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Terry $    $Date: 5/05/00 7:45a $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/pividdef.h $
*  
*  9     5/05/00 7:45a Terry
*  Add  RS170_NONE
*  
*  8     99/04/09 12:19 Shige
*  Added a new RS170 dimensions 
*  
*  3     7/18/96 2:02p Dan
*  
*  2     5/06/96 2:14p Dan
*  added the nodup switch PIVIDDEF_H
*  
*  1     4/23/96 3:29p Charlie
*  video specific functions.
*  
*
*
******************************************************************
*/
#if !defined PIVIDDEF_H
#define      PIVIDDEF_H


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


/*----------------------------------------------------------------------------+
|  Kind of RS170 standard                                                     |
+-----------------------------------------------------------------------------+
*/
enum RS170_STANDARD_SPECIFIER
{
  RS170_NONE = 0,             /* No RS170 available */
  RS170_NTSC,                 /* W:756    H:486    F:301    L:301            */
  RS170_PAL,                  /* W:741    H:576    F:287    L:287            */

  RS170_CUSTOM,			          /* Custom dimension which is set by:           */
									/*	CMSetLongParam( CMP_CUSTOM_VIDEO_X, Width)						 */
									/*	CMSetLongParam( CMP_CUSTOM_VIDEO_Y, Height)						 */
									/*	CMSetLongParam( CMP_CUSTOM_VIDEO_FSTWIDTH, FirstWidth) */
									/*	CMSetLongParam( CMP_CUSTOM_VIDEO_LSTWIDTH, LastWidth)	 */

	/* RS170 video generated with 12.5MHz clock:  added on 4/9/99 */
  RS170_NTSC_12P5MHZ,         /* W:640    H:482    F:244    L:244            */
  RS170_PAL_12P5MHZ           /* W:640    H:482    F:244    L:244            */

};

#endif  /* PIVVIDEF_H */
/*
        end of pikindef.h
*********************************************************************
*/
