/*   PI controller DLLs external defintion timing modes
*    workfile:   s:\xsma\xdll\pitimfcn.h
*    $Logfile: /WinX32 V2.3/INCLUDE/pitimfcn.h $
*       $Date: 9/09/98 10:45a $
******************************************************************
*
*       pitimfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll Timing Modes
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 9/09/98 10:45a $
*
******************************************************************
*
*  $Log: /WinX32 V2.3/INCLUDE/pitimfcn.h $
*  
*  5     9/09/98 10:45a Bob
*  Removed all double slash comments for macintosh...
*  
*  2     7/18/96 2:02p Dan
*  
*  1     5/27/96 6:19p Charlie
*  Added user trigger for PentaMax
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
/*                  LEVEL 2 DLLs TIMING MODES                  */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Set_acqmode                    */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* acquisition mode (timing mode) : FREERUN, ...       */
/* see CTRL_ACQMODE definitions                        */
PREHEAD int PISTDAPI  PICM_Set_acqmode(int acqmode);
PREHEAD int PISTDAPI  PICM_Get_acqmode(void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_software_trigger              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* software trigger, if hardware is setup for ext-sync, this function will
   do the same thing as a hardware ext-sync but via software. */
PREHEAD int PISTDAPI  PICM_Set_software_trigger ( int trigger );
PREHEAD     int PISTDAPI PICM_Get_software_trigger(void);
/* for dc131 clears interupt trigger counter. */
PREHEAD int PISTDAPI PICM_Clear_software_trigger( void );
/* for dc131 returns the interupt counter for triggers. */
PREHEAD unsigned long PISTDAPI PICM_Check_software_trigger( void );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_Inq_TimingModeSupport              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* inquires whether the controller supports a particular timing mode */
/*   purpose: In the dialog, to eliminate (or at least gray out) any */
/*            irrelavant timing mode.                                */
PREHEAD int PISTDAPI  PICM_Inq_TimingModeSupport(int tmode);

/*
        end of pitimfcn.h
*********************************************************************
*/
