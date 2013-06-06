/*   PI controller DLLs external defintion and define file frame counter
*    $Logfile: /WinX32 V2.5/INCLUDE/PIINTDEF.H $
*       $Date: 2/26/03 14:41 $
******************************************************************
*
*       piintdef.h
*
******************************************************************
*
*  contains the Declarations & Enumerators for the frame counter
*  Interrupt frame counter.
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Skatsumata $    $Date: 2/26/03 14:41 $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/PIINTDEF.H $
*  
*  11    2/26/03 14:41 Skatsumata
*  put #ifdef to prevent multiple #include
*  
*  6     8/14/96 6:39a Dan
*  fixed a lack of a comma in an enum list
*  
*  5     8/09/96 7:46p Charlie
*  Added new old end of frame for PentaMax version older then 5 and also
*  to keep EDT working and not change any timing.
*  
*  4     7/18/96 2:02p Dan
 * 
 * 3     2/02/96 3:29p Charlie
 * Added new BEGIN_END_FRAME DEFINE FOR MicroMax and PentaMax.
 * 
 * 2     10/16/95 9:46a Dan
 * Moved from $/WinX/PRODUCT/COMMON
 * 
 * 1     10/13/95 3:28p Admin
 * Latest source from PVCS
*  
*
*
******************************************************************
*/
#if !defined(PIINTDEF_H)
#define PIINTDEF_H

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
/*                  LEVEL 7 DLLs  interrupt frame counter      */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Enable_Interrupt_FrameCnt        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function enables the interrupt for frame counter,              */
/* it also set when the interrupt will occur at the beginning of       */
/* transfer frame or at the end.                                       */
/* int PICM_Enable_Interrupt_FrameCnt                                  */
/*         int mode_setting  :: type of action, count start frame, end */
/*                              frame, or none                         */

/* For ST138 and ST133 (ver 3), DC131 (ver 4), you can set beginning &      */
/* ending of frame interrupts. These can be retrieved by framecnt functions.*/
enum frame_int
{
    NO_FRAME_INT = 0,    /* Don't generate any interrupt.                   */
    BEGIN_FRAME_INT,     /* Generate interrupt at beginning of frame trans  */
    END_FRAME_INT,       /* Generate interrupt at end of frame trans.       */
    BEGIN_END_FRAME_INT, /* PentaMax,MicroMax (still need to do for ST138)  */
    OLD_END_FRAME_INT    /* Used by PentaMax to generate old style eof, this*/
                         /* is needed for SYSV Sun/EDT. This is need for    */
                         /* verions 5 and greater PentaMaxs.                */
};


#endif // #if !defined(PIINTDEF_H)
/*
        end of piintdef.h
*********************************************************************
*/
