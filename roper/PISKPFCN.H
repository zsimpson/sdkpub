/*   PI controller DLLs external defintion skipping operations.
*    $Logfile: /WinX32 V2.0/INCLUDE/PISKPFCN.H $
*       $Date: 5/13/97 11:06a $
******************************************************************
*
*       piskpfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll skipping operations
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Charlie $    $Date: 5/13/97 11:06a $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/PISKPFCN.H $
*  
*  5     5/13/97 11:06a Charlie
*  Added win32 defines and took out old win3.1 defines for exported
*  functions. 
*  
*  4     1/02/97 5:22p Jenn
*  
*  3     7/18/96 2:02p Dan
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


/* ########################################################### */
/*                  LEVEL 2 DLLs  Skipping OPERATIONS.         */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Set/Get_cleanscans             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* clean scans */
PREHEAD int PISTDAPI PICM_Set_cleanscans(int cleans);
PREHEAD int PISTDAPI PICM_Get_cleanscans(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*         PICM_Set/Get_num_strips_per_clean           */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* set the number of strips that clean scan does per value */
PREHEAD int PISTDAPI PICM_Get_num_strips_per_clean (void);
PREHEAD int PISTDAPI PICM_Set_num_strips_per_clean (
    int number_strips_per_clean);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Get_MinBlk                        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD long PISTDAPI PICM_Get_MinBlk( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_MinBlk                        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Set_MinBlk( long minblk );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Get_NumMinBlk                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD long PISTDAPI PICM_Get_NumMinBlk( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_NumMinBlk                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Set_NumMinBlk( long minblk );



/*
        end of piskpfcn.h
*********************************************************************
*/
