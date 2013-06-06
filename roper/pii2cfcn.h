/*   PI controller DLLs external defintion for storing info into hw memory
*    $Logfile: /WinX32 V2.4/INCLUDE/pii2cfcn.h $
*       $Date: 1/30/99 1:20p $
******************************************************************
*
*       pii2cfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll hw mem read/write
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 1/30/99 1:20p $
*
******************************************************************
*
*  $Log: /WinX32 V2.4/INCLUDE/pii2cfcn.h $
*  
*  10    1/30/99 1:20p Bob
*  Added RS_ 
*  
*  7     4/27/98 10:58p Charlie
*  Added PICM_CreateControllerNvram
*  
*  6     4/27/98 9:37p Charlie
*  Added findpcicards and findcontrollers and load nvram defaults.
*  
*  4     8/18/97 6:09p Charlie
*  changed sysid functions to use platform.h datatypes.
*  
*  3     7/18/96 2:02p Dan
*  
*  2     5/24/96 11:15a Charlie
*  Added location to system ram.
*  
*  1     5/19/96 8:08p Charlie
*  Routines to read and write to hardware memory.
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
/*                  LEVEL 7 DLLs  HW mem read/write            */
/*                  OEMs only.                                 */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Send_SysID                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Send down array of bytes to system memory. */
PREHEAD RS_INT32 PISTDAPI PICM_Send_SysID 
(
 RS_UINT32 Location,				/* location to write to (control card   */
                                /* interface card, head, etc.)          */
 RS_UINT32 id_add,                 /* EEProm addr to begin write			*/
 RS_UINT8 *id_array,               /* ptr to array to write				*/
 RS_UINT32 id_size);               /* num bytes to write.					*/

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Read_SysID                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* read array of bytes from system memory. */
PREHEAD RS_INT32 PISTDAPI PICM_Read_SysID 
(
 RS_UINT32 Location,			/* location to read from (control card  */
                            /* interface card, head, etc.)          */
 RS_UINT32 id_add,             /* EEProm addr to begin write			*/
 RS_UINT8 *id_array,           /* ptr to array to write				*/
 RS_UINT32 id_size);           /* num bytes to write.					*/



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_FindPCICards                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function returns the number of PI PCI cards in */
/* the system.                                         */
PREHEAD RS_UINT32   PISTDAPI PICM_FindPCICards(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_FindController                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This routine tries to read nvram on each controller */
/* it returns the controller that it finds, this will  */
/* not work for systems without nvram.                 */
PREHEAD RS_UINT32 PISTDAPI PICM_FindController (RS_UINT32 pci_number, RS_UINT32 *error_code);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_LoadNvramDefaults              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Load good defaults from nvram (system must have     */
/* nvram for this to work.                             */
PREHEAD RS_UINT32   PISTDAPI PICM_LoadNvramDefaults(RS_UINT32 *error_code);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_CreateControllerNvram          */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Create controller and load good defaults if pci in  */
/* the computer and controller has nvram in it.        */
PREHEAD RS_UINT32 PISTDAPI PICM_CreateControllerNvram
(
 RS_UINT32 pci_card,     /* for future use, set to one now. */
 RS_UINT32 *error_code   /* Erro code if, used if function returs false. */
 );

/*
        end of pii2cfcn.h
*********************************************************************
*/
