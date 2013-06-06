/*   PI controller DLLs external defintion and define file timing modes
*    $Logfile: /WinX32 V2.5/INCLUDE/PITIMDEF.H $
*       $Date: 6/23/00 2:23p $
******************************************************************
*
*       pitimdef.h
*
* Copyright (C) 1997, 1998 Princeton Instruments
* All rights reserved
*
*
******************************************************************
*
*  contains the Declarations & Enumerators for the simple dll
*  timing modes
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Charlie $    $Date: 6/23/00 2:23p $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/PITIMDEF.H $
*  
*  16    6/23/00 2:23p Charlie
*  Added CTRL_TRIGGER_FIRST AND CTRL_BULB for PvCam
*  
*  14    12/15/98 3:59p Terry
*  Add CTRL_INTERNAL_SYNC
*  
*  11    4/22/98 5:23p Charlie
*  Added dual frame (Chad).
*  
*  10    2/17/98 4:43p Terry
*  Add ifdef to avoid duplication
*  
*  9     1/14/98 8:17p Charlie
*  Added kinetics for ST138 timing.
*  
*  7     5/29/97 11:23a Bob
*  Added CTRL_SWTRIGGER 
*  
*  6     1/26/97 5:19p Charlie
*  Took out duplication of RESERVED define.
*  
*  5     1/24/97 8:13p Charlie
*  Added BNC out defines for the PentaMax.
*  
*  4     7/18/96 2:02p Dan
*  
*  3     5/27/96 6:19p Charlie
*  Added PentaMax specific user trigger functions and enums.
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

#ifndef PITIMDEF_H
#define PITIMDEF_H

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
/*                  LEVEL 2 DLLs  TIMING MODES                 */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Set_acqmode                    */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* acquisition mode (timing mode) : FREERUN, ...       */
/* int PICM_Set_acqmode(int acqmode);                  */
/* Get acquisition mode set (timing mode)              */
/* int PICM_Get_acqmode(void);                         */


/* acquisition mode definitions   */
enum ctrl_acqmode
{
    CTRL_FREERUN = 1,
    CTRL_LINESYNC,
    CTRL_EXTSYNC,        /* same as extsync normal. */
    CTRL_EXTSYNC_NORMAL,
    CTRL_EXTSYNC_PREOPEN,
    CTRL_EXTTRIG,        /* same as exttrig normal. */
    CTRL_EXTTRIG_NORMAL,
    CTRL_EXTTRIG_PREOPEN,
    CTRL_FR_STORE_TRIG,      /* Free run with Store Trigger Enable        */
    CTRL_SN_STORE_TRIG,      /* ExtSync Normal with Store Trigger Enable  */
    CTRL_SP_STORE_TRIG,      /* ExtSync Preopen with Store Trigger Enable.*/
    CTRL_TN_STORE_TRIG,      /* ExtTrig Normal with Store Trigger Enable. */
    CTRL_TP_STORE_TRIG,      /* ExtTrig Preopen with Store Trigger Enable */
    CTRL_EXTSHUTTER_CONTROL, /* DC131 only external shutter control.      */
    CTRL_EVENT_COUNTER,      /* Event counter, only for ST121             */
    CTRL_LINE_SYNC_EXT_TRIG, /* Line sync and ext trigger.                */
    CTRL_LINE_SYNC_STR_ENA,  /* Line sync and stroe enable.               */
    CTRL_EXT_SYNC_EXT_TRIG,  /* Ext sync and ext trig.                    */
    CTRL_SWTRIGGER,          /* Pentamax Single Trigger Multiple Frames   */
    CTRL_KINETICS_NO_TRIGGER,/* Kinetics only, freerun.                   */
    CTRL_KINETICS_SINGLE,    /* Kinetics only, single trigger.            */
    CTRL_KINETICS_MULTIPLE,  /* Kinetics only, multiple trigger.          */
    CTRL_IEC,                /* Internal exposure control.                */
    CTRL_EEC,                /* External exposure control.                */
    CTRL_ESABI,              /* Electronic shutter action between images. */
    CTRL_INTERNAL_SYNC,       /* Sync come from backplane - only PTG      */
    CTRL_TRIGGER_FIRST,       /* Single trigger, continous data.          */
    CTRL_BULB                 /* Bulb trigger (pvcam)                     */
};

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set/Get_software_trigger          */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* ST138 software trigger, if hardware is setup for ext-sync, this function */
/* will do the same thing as a hardware ext-sync but via software.          */
/* DC131 : this enables the user interupt.                                  */
/*      SWT_DONT_USE            :: General use, (ST138)                     */
/*      SWT_WAIT_FOR_TRIGGER    :: Tells software to wait for trigger before*/
/*                                  start controller.                       */
/*      SWT_USER_DEFINED        :: interrupt used other then for triggering */
/*      SWT_GENERAL             :: ST138 ext-sync equivelent.               */

enum ctrl_swt
{
    SWT_DONT_USE = 0,
    SWT_WAIT_FOR_TRIGGER,
    SWT_USER_DEFINED,
    SWT_GENERAL
};                               /* end ctrl_swt */

/* output settings for the Pentamax V5 BNC. */
#define NOT_SCAN           0
#define SHUTTER            1
#define NOT_RDY            2
#define LOGIC0             3
#define CLEANING           4
#define NOT_FT_IMAGE_SHIFT 5        /* Low when shifting ft image to storage area. */
#define BNC_RESERVED       6        /* NOT AVAILABLE.                              */
#define LOGIC1             7

#endif

/*        end of pitimdef.h
*********************************************************************
*/
