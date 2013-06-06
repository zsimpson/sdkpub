/*   PI controller DLLs external defintion shutter operations.
*    workfile:   s:\xsma\xdll\pishtfcn.h
*    $Logfile: /WinX32 V2.0/PRODUCT/INCLUDES/pishtfcn.h $
*       $Date: 7/18/96 2:02p $
******************************************************************
*
*       pishtfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll shutter operations
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
*  $Log: /WinX32 V2.0/PRODUCT/INCLUDES/pishtfcn.h $
*  
*  2     7/18/96 2:02p Dan
*  
*  1     6/05/96 6:14p Charlie
*  Shutter functions.
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


/* ########################################################### */
/*                  LEVEL 2 DLLs  SHUTTER OPERATIONS.          */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_shutter_type                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* shutter type, for shutter compensation time.        */
/* See pishtdef.h installed_shutter enum for legal values. */
/* shutter type */
PREHEAD int PISTDAPI  PICM_Set_shutter_type
                    (int shutter);
PREHEAD int PISTDAPI PICM_Get_shutter_type
                    (void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_shuttermode                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* shutter OPEN (NORMAL) or CLOSE.                     */
/* See pishtdef.h ctrl_shutter for legal values.       */
PREHEAD int PISTDAPI PICM_Set_shuttermode(int shuttermode);
PREHEAD int PISTDAPI PICM_Get_shuttermode(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_shutter                       */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* physically open or close shutter: condition may be OPEN or CLOSE */
PREHEAD int PISTDAPI PICM_Set_shutter(int condition);



/*
        end of pishtfcn.h
*********************************************************************
*/
