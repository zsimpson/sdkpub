/*   PI controller DLLs external defintion interrupt frame counting
*    workfile:   s:\xsma\xdll\piintfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/PIINTFCN.H $
*       $Date: 5/12/97 9:01a $
******************************************************************
*
*       piintfcn.h
*
******************************************************************
*
*  contains the Declarations for the interrupt frame counting dll
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 5/12/97 9:01a $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/PIINTFCN.H $
*  
*  2     5/12/97 9:01a Bob
*  Fixed Old _export far pascal definitions to PISTDAPI...
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
/*                  LEVEL 7 DLLs INTERRUPT FRAME COUNTING      */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*           PICM_Clear_Interrupt_FrameCnt             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
// Clear interrupt frame counter to zero. This counter is
// set by the interrupt routine on end of frame or beginning of frame.
PREHEAD int PISTDAPI PICM_Clear_Interrupt_FrameCnt (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Get_Interrupt_FrameCnt            */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
// Returns frame count set by interrupt routine on beginning
// and ending of frame.
PREHEAD long PISTDAPI PICM_Get_Interrupt_FrameCnt (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Enable_Interrupt_FrameCnt        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
// This function enables the interrupt for frame counter,
// it also set when the interrupt will occur at the beginning of
// transfer frame or at the end.
PREHEAD int PISTDAPI PICM_Enable_Interrupt_FrameCnt
(
 int mode_setting  /* type of action, count start frame, end frame, or none */
);


/*
        end of piintfcn.h
*********************************************************************
*/
