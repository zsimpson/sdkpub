/*   PI controller DLLs external defintion and define file manual prog
*    $Logfile: /WinX32 V2.3/INCLUDE/PIMANDEF.H $
*       $Date: 9/09/98 10:50a $
******************************************************************
*
*       pimandef.h
*
******************************************************************
*
*  contains the Declarations & Enumerators for the not so simple dll
*  Manual programming of the controller.
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 9/09/98 10:50a $
*
******************************************************************
*
*  $Log: /WinX32 V2.3/INCLUDE/PIMANDEF.H $
*  
*  7     9/09/98 10:50a Bob
*  Removed final comma from enumerated types for mac...
*  
*  6     7/30/98 3:48p Charlie
*  Added new Fast acq mode.
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

/* definitions of enumeration types */

/* ########################################################### */
/*                  LEVEL 5 DLLs  MANAUL PROGRAMMING           */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_Set_Collection_Mode                */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function set whether the scan control program to                 */
/* the controller is to be calculated and sent by the controller         */
/* functions (auto) or whether the user wishes to override these         */
/* functions and program the controller themselves (manual). If manaul   */
/* remember to PICM_Set_Xdim and PICM_Set_Ydim to tell the software      */
/* the size of the pattern programmed. Also the program has to be sent   */
/* for the ST138 you must call PICM_Set_manual_scan_patterns, for the    */
/* DC131 you must call PICM_Set_manual_scan_patterns but only with       */
/* one array and size. (NOTE : CURRENTLY ONLY DC131 & ST138 IMPLEMENTED).*/
/* int PICM_Set_Collection_Mode                                          */
/*     int mode_flag :: mode auto or manual see enum type scan_program_mode */

/* flag to set if controller should be set by menus (AUTO_PROGRAM) or by */
/* basic (MANUAL_PROGRAM) */
enum scan_program_mode
{
    AUTO_PROGRAM = 0,    /* Normal operation                               */
    MANUAL_PROGRAM,      /* special user override of scan pattern          */
    ZOOM_PROGRAM,        /* ST133 only special                             */
    ZOOM_STORE_PROGRAM,  /* ST133 only special                             */
    HIGH_SPEED_PROGRAM  /* only for dc131, st133, frame transfer ccds.    */
};



/*
        end of pimandef.h
*********************************************************************
*/
