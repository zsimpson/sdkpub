/*   PI controller DLLs external defintion fuctions for OEMs
*    workfile:   s:\xsma\xdll\pioemfcn.h
*    $Logfile: /WinX32 V2.2/INCLUDE/pioemfcn.h $
*       $Date: 5/07/98 10:26a $
******************************************************************
*
*       pioemfcn.h
*
******************************************************************
*
*  contains the Declarations for OEM functions 
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Charlie $    $Date: 5/07/98 10:26a $
*
******************************************************************
*
*  $Log: /WinX32 V2.2/INCLUDE/pioemfcn.h $
*  
*  12    5/07/98 10:26a Charlie
*  Moved PICM_LockCurrentFrame and Unlock to PIGENFCN.H
*  
*  10    1/21/97 11:22a Bob
*  Added PICM_Set_EasyDLL_DC to the h - file
*  
*  9     1/07/97 9:03a Bob
*  PICM_GetLinear_Base will now return size as well as address
*  
*  8     11/29/96 1:14p Charlie
*  Added PICM_LockCurrentFrame and PICM_UnlockCurrentFrame for OEMs.
*  
*  7     8/30/96 5:46p Bob
*  
*  6     7/18/96 2:02p Dan
*  
*  5     6/07/96 11:00a Charlie
*  took out run seq function, put in piseqfcn 
*  
*  4     6/07/96 10:24a Charlie
*  added new data collection mode.
*  
*  3     6/06/96 4:09p Charlie
*  Changed structure of run sequencer to avoid conflicts between WinX and
*  Easy DLLs.
*  
*  2     6/06/96 12:03p Charlie
*  Oem addtions.
*  
*  1     6/05/96 6:14p Charlie
*  OEM functions.
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
/*              PICM_Get_controller_objptr             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD PIXCMHNDLE PISTDAPI PICM_Get_controller_objptr(int controller_num );

/* Temp until tested, then will become standard ChkData. */
PREHEAD int PISTDAPI PICM_ChkData_new(unsigned int *status_code);


/* Set/Get data collection mode. see pigendef.h for enum */
PREHEAD int PISTDAPI PICM_Get_data_collection_mode( void );
PREHEAD int PISTDAPI PICM_Set_data_collection_mode(int mode);

/* Get the dma buffer starting linear address */
/* returns success or failure and by reference the */
/* starting address which should be in the 0xC0000000 */
/* range */
PREHEAD int PISTDAPI PICM_GetLinear_Base( void **address, unsigned long *size );


/* Set the data acquisition mode enumerated modes are in pigendef.h */
PREHEAD int PISTDAPI PICM_Set_EasyDLL_DC(int mode);

/*
        end of pioemfcn.h
*********************************************************************
*/
