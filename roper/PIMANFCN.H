/*   PI controller DLLs external defintion manual prog
*    workfile:   s:\xsma\xdll\pimanfcn.h
*    $Logfile: /WinX32 V2.1/INCLUDE/PIMANFCN.H $
*       $Date: 12/09/97 10:38a $
******************************************************************
*
*       pimanfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll not so simple dll
*  Manual programming of the controller.
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Charlie $    $Date: 12/09/97 10:38a $
*
******************************************************************
*
*  $Log: /WinX32 V2.1/INCLUDE/PIMANFCN.H $
*  
*  4     12/09/97 10:38a Charlie
*  Fixed documentation bug (x and y where reversed).
*  
*  3     6/17/97 7:56a Bob
*  Added Read And WriteByte controller functions.
*  
*  2     3/28/97 4:14p Charlie
*  Added PREHEAD and PISTDAPI defines to functions, also added
*  WriteToController & ReadFromController.
*  
*  1     2/13/97 6:17p Charlie
*  Manual override.
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
/*                  LEVEL 5 DLLs MANUAL PROGRAMMING            */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_manual_scan_patterns              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function allows the user to set the x-y scan pattern manually */
/* for the ST133 (MicroMax) only the *y_pattern and size are used, */
/* the y_pattern holds the scan pattern and the size is the size of */
/* of the scan pattern.                                             */
/* For the ST138 the y pattern (parallel to shift register) is given */
/* 1st and the x pattern (perpendicular) 2nd. (Note: these where    */
/* incorrectly documented as reverse previous to 12/9/97.           */
PREHEAD int PISTDAPI PICM_Set_manual_scan_patterns
(
 int *y_pattern,         /* Y scan pattern                       */
 long y_size,            /* y dimension size                     */
 int *x_pattern,         /* X scan pattern                       */
 long x_size             /* x dimension size                     */
 );

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
PREHEAD int PISTDAPI PICM_Set_Collection_Mode           
(
 int mode_flag	/* mode auto or manual see enum type scan_program_mode */
);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_Collection_Mode              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Return mode of programing scan pattern (auto-manual). */
PREHEAD int PISTDAPI PICM_Get_Collection_Mode (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                    PICM_Set_Xdim                    */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function sets the x dimension of data coming back */
/* from controller when using manual mode.                */
PREHEAD int PISTDAPI PICM_Set_Xdim
(
 long size_of_data       /* size of x dim. of data coming from controller. */
  );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                    PICM_Set_Ydim                    */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function sets the x dimension of data coming back */
/* from controller when using manual mode.                */
PREHEAD int PISTDAPI PICM_Set_Ydim
( 
 long size_of_data       /* size of y dim. of data coming from controller. */
);


/*****************************************************************************
*
*       PICM_WriteToController : Write a value to a controllers offset
*
*-----------------------------------------------------------------------------
*/
PREHEAD int PISTDAPI PICM_WriteToController
(unsigned int addrOffset,           /* Offset of register into controller   */
 unsigned int value                 /* value to write to register.          */
 );

/*****************************************************************************
*
*       PICM_ReadFromController : Read register from controller.
*
*-----------------------------------------------------------------------------
*/
PREHEAD unsigned int PISTDAPI PICM_ReadFromController
                                    (unsigned int addrOffset  );

/*****************************************************************************
*
*       PICM_WriteByteToController : Write a value to a controllers offset
*
*-----------------------------------------------------------------------------
*/
PREHEAD int PISTDAPI PICM_WriteByteToController
(unsigned int addrOffset,           /* Offset of register into controller   */
 unsigned int value                 /* value to write to register.          */
 );

/*****************************************************************************
*
*       PICM_ReadFromController : Read register from controller.
*
*-----------------------------------------------------------------------------
*/
PREHEAD unsigned int PISTDAPI PICM_ReadByteFromController
                                    (unsigned int addrOffset  );

/*
        end of pimanfcn.h
*********************************************************************
*/
