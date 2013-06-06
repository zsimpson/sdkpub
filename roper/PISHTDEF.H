/*   PI controller DLLs external defintion and define file shutter operations
*    $Logfile: /WinX32 V2.0/PRODUCT/INCLUDES/PISHTDEF.H $
*       $Date: 7/18/96 2:02p $
******************************************************************
*
*       pishtdef.h
*
******************************************************************
*
*  contains the Declarations & Enumerators for the simple dll
*  shutter functions.
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Dan $    $Date: 7/18/96 2:02p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/PRODUCT/INCLUDES/PISHTDEF.H $
*  
*  4     7/18/96 2:02p Dan
 * 
 * 3     10/25/95 7:08p Charlie
 * Changed order of enumerated type for shutter (nobody used yet
 * the two values so it should be alright to change order).
 * 
 * 2     10/16/95 9:46a Dan
 * Moved from $/WinX/PRODUCT/COMMON
 * 
 * 1     10/13/95 3:28p Admin
 * Latest source from PVCS
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

/* definitions of enumeration types */

/* ########################################################### */
/*                  LEVEL 2 DLLs  SHUTTER OPERATIONS           */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */




/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_shutter_type                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* shutter type, for shutter compensation time.        */
/* int PICM_Set_shutter_type (int shutter_type);       */
/* int PICM_Get_shutter_type (void);                   */

/* shutter type definition */
enum installed_shutter
{                         /* In dialog, they are appeared as: */
    NO_SHUTTER = 1,       /*   None                           */
    LARGE_SHUTTER,        /*   Large                          */
    REMOTE_SHUTTER,       /*   Remote                         */
    SMALL_SHUTTER,        /*   Small                          */
    ELECTRONIC_SHUTTER,   /*   Electronic                     */
    CUSTOM_SHUTTER        /*   CUSTOM Comp                    */       
};

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_shuttermode                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* shutter OPEN (NORMAL) or CLOSE.                     */
/* int PICM_Set_shuttermode(int shuttermode);          */
/* int PICM_Get_shuttermode(void);                     */

/* shutter mode of operation */
enum ctrl_shutter
{
    SHUTTER_NORMAL = 1,
    SHUTTER_CLOSE,
    SHUTTER_DISABLED_OPEN,   /* PentaMax and Oma 4 have this feature. */
/*  SHUTTER_OPEN is confusing; it meant NORMAL mode  */
    SHUTTER_AUTOBACK,  /* not supported in DLL */
    SHUTTER_OPEN = SHUTTER_NORMAL
};


/*
        end of pishtdef.h
*********************************************************************
*/
