/*   PI controller DLLs external defintion for online functions
*    workfile: \winx32\include\pionldef.h
*    $Logfile: /WinX32 V2.2/INCLUDE/pionldef.h $
*       $Date: 3/06/98 3:07p $
*
* Copyright (C) 1997-1998 Princeton Instruments
* All rights reserved
******************************************************************
*
*       pionldef.h
*
******************************************************************
*
*  Functions that can be called without reinitializing controller.
*  Note :: may not work for all controllers.
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Terry $    $Date: 3/06/98 3:07p $
*
******************************************************************
*
*  $Log: /WinX32 V2.2/INCLUDE/pionldef.h $
*  
*  3     3/06/98 3:07p Terry
*  Add TimeUnit_NSEC and TimeUnit_PSEC
*  
*  1     4/14/97 3:45p Charlie
*  Def for online exposure
*  
*
*
*
******************************************************************
*/


/*
******************************************************************************
        include files
*/

/*
******************************************************************************
        defines
*/

#ifndef _PIONLDEF_H
#define _PIONLDEF_H


/* ########################################################### */
/*                  LEVEL 3 DLLs           OPERATIONS.         */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              ExposureTimeUnit                       */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* enum for the fcn PICM_Set_Exposure_Online, expoTUnit */
/* Exposure time unit */
enum ExposureTimeUnit
{
    ControllerDefault=0,      /* Scan unit?? */
    TimeUnit_USEC,
    TimeUnit_MSEC,
    TimeUnit_SEC,
    TimeUnit_MIN,
    TimeUnit_HOUR,
    TimeUnit_FRAMES,
    TimeUnit_NSEC,
    TimeUnit_PSEC
};

#endif

/*
        end of pionldef.h
*********************************************************************
*/
