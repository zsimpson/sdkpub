/*   PI controller DLLs external defintion for online functions
*    workfile:   s:\xsma\xdll\pionlfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/pionlfcn.h $
*       $Date: 4/29/97 12:16p $
******************************************************************
*
*       pionlfcn.h
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
*  $Author: Charlie $    $Date: 4/29/97 12:16p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/pionlfcn.h $
*  
*  2     4/29/97 12:16p Charlie
*  Took out old STDAPICALLTYPE define (not used anymore).
*  
*  1     4/07/97 4:09p Dan
*  used on the EasyDLL/32 examples
*  
*  1     11/04/96 10:23a Dan
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
/*                  LEVEL 3 DLLs           OPERATIONS.         */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_Exposure_Online               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* set exposure time online */
PREHEAD int PISTDAPI PICM_Set_Exposure_Online ( double exptime, int expoTUnit);

/*
        end of pionlfcn.h
*********************************************************************
*/
