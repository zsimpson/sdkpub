/*   PI controller kinetics DLLs external defintion 
*    workfile:   s:\xsma\xdll\pikinfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/PIKINFCN.H $
*       $Date: 11/08/96 9:12a $
******************************************************************
*
*       pikinfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 11/08/96 9:12a $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/PIKINFCN.H $
*  
*  2     11/08/96 9:12a Bob
*  
*  1     11/08/96 8:19a Charlie
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
/*                  LEVEL 2 DLLs                               */
/* EASY CONTROLLER DLLS : ADC FUNCTION PROTOTYPES              */
/* ########################################################### */



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_ContSetup_KinWinSize              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Set kinetics window size.                           */
PREHEAD int PISTDAPI PICM_Set_ContSetup_KinWinSize( int wsize );
PREHEAD int PISTDAPI PICM_Get_ContSetup_KinWinSize( void );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_Set_Kinetics_TriggerMode           */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Set the triggering mode for kinetics This can be FreeRun, Single, */
/* or multiple. Note : Single and Multiple can be ext-sync, pre-open */
/* and normal (i.e. so that there are 5 combinations that are legal). */
/* this routine just sets the none,single, and multiple setting. */
/* Set kinetics trigger mode                           */
/* See pikindef.h enumerated type Kinetics_Trigger_Values */
PREHEAD int PISTDAPI PICM_Set_Kinetics_TriggerMode( int trigger_mode );
PREHEAD int PISTDAPI PICM_Get_Kinetics_TriggerMode( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*    PICM_Set_Current_VTCLK (change factory default at your own risk)  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* To set vertical clock use values between 1 - 16. Look at WinX for */
/* real values.                                                      */
PREHEAD int PISTDAPI PICM_Set_Current_VTCLK( unsigned char clock_number );


/*
        end of pikinfcn.h
*********************************************************************
*/
