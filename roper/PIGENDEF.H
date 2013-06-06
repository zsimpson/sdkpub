/*   PI controller DLLs external defintion and define file
*    $Logfile: /WinX32 V2.5/INCLUDE/PIGENDEF.H $
*       $Date: 4/08/03 16:00 $
******************************************************************
*
*       pigendef.h
*
* Copyright (C) 1997, 1998 Princeton Instruments
* All rights reserved
*
*
******************************************************************
*
*  contains the Declarations & Enumerators for the simple dll
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Skatsumata $    $Date: 4/08/03 16:00 $
*
******************************************************************
*
*  $History: PIGENDEF.H $
*  
*  *****************  Version 101  *****************
*  User: Skatsumata   Date: 4/08/03    Time: 16:00
*  Updated in $/WinX32 V2.5/INCLUDE
*  Added InGaAs 1x1024
*  
*  *****************  Version 100  *****************
*  User: Skatsumata   Date: 02/07/25   Time: 17:53
*  Updated in $/WinX32 V2.5/INCLUDE
*  Added Fairchild 4K x 4K F at NOT_USED1 (enum val 39)
*  
*  *****************  Version 99  *****************
*  User: Dknouse      Date: 4/29/02    Time: 9:35a
*  Updated in $/WinX32 V2.5/INCLUDE
*  Added  EEV 512x2048B CCD42_10
*  
*  *****************  Version 98  *****************
*  User: Skatsumata   Date: 02/03/06   Time: 14:57
*  Updated in $/WinX32 V2.5/INCLUDE
*  added ST133_2MHZ into controller type enum.
*  
*  *****************  Version 97  *****************
*  User: Dknouse      Date: 2/12/02    Time: 10:13a
*  Updated in $/WinX32 V2.5/INCLUDE
*  added MAR_512x512_CCD77
*  
*  *****************  Version 96  *****************
*  User: Skatsumata   Date: 01/10/19   Time: 19:09
*  Updated in $/WinX32 V2.5/INCLUDE
*  Replaced NOT_USED6 to MIT_CCD_36 
*  
*  *****************  Version 95  *****************
*  User: Dknouse      Date: 10/10/01   Time: 12:46p
*  Updated in $/WinX32 V2.5/INCLUDE
*  final fixed - now MAR_576x576_FT_CCD65
*  
*  *****************  Version 94  *****************
*  User: Dknouse      Date: 10/10/01   Time: 12:33p
*  Updated in $/WinX32 V2.5/INCLUDE
*  fixed enum for MAR_288x576_FT_CCD65
*  
*  *****************  Version 93  *****************
*  User: Dknouse      Date: 10/08/01   Time: 4:34p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added MAR_288x576_CCD65 chip
*  
*  *****************  Version 92  *****************
*  User: Dknouse      Date: 8/21/01    Time: 1:55p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added to chip comments, a chip number
*  
*  *****************  Version 91  *****************
*  User: Dan          Date: 6/18/01    Time: 10:17a
*  Updated in $/WinX32 V2.5/INCLUDE
*  added KAF_2084x2084_SCX
*  
*  *****************  Version 90  *****************
*  User: Dan          Date: 5/08/01    Time: 11:16a
*  Updated in $/WinX32 V2.5/INCLUDE
*  added "HAM_2x2048"
*  
*  *****************  Version 89  *****************
*  User: Dan          Date: 3/30/01    Time: 4:36p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added "GATAN" special chips
*  
*  *****************  Version 88  *****************
*  User: Dan          Date: 2/27/01    Time: 8:42a
*  Updated in $/WinX32 V2.5/INCLUDE
*  added "KAF_2084x2084"
*  
*  *****************  Version 87  *****************
*  User: Terry        Date: 1/25/01    Time: 12:32p
*  Updated in $/WinX32 V2.5/INCLUDE
*  Rename LOW_COST_SPEC_USB to ARC_CCD_100
*  
*  *****************  Version 86  *****************
*  User: Bob          Date: 1/09/01    Time: 11:45a
*  Updated in $/WinX32 V2.5/INCLUDE
*  Added Low Cost USB Device
*  
*  *****************  Version 85  *****************
*  User: Dan          Date: 1/02/01    Time: 12:52p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added "RSS_1024x512_FT"
*  
*  *****************  Version 84  *****************
*  User: Terry        Date: 10/27/00   Time: 6:40a
*  Updated in $/WinX32 V2.5/INCLUDE
*  Add PID_330x1100_8phH_V2
*  
*  *****************  Version 83  *****************
*  User: Dan          Date: 10/05/00   Time: 9:53a
*  Updated in $/WinX32 V2.5/INCLUDE
*  added EEV 2048x2048 CCD42_40
*  
*  *****************  Version 82  *****************
*  User: Dan          Date: 7/13/00    Time: 9:50a
*  Updated in $/WinX32 V2.5/INCLUDE
*  added new chips - HAM_58x1024_B,  HAM_122x1024_B,  HAM_250x1024_B
*  
*  *****************  Version 81  *****************
*  User: Dan          Date: 3/08/00    Time: 4:36p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added EEV_256x1024_6ph_CCD30_B &  EEV_256x1024_6ph_CCD30_OE
*  
*  *****************  Version 80  *****************
*  User: Dan          Date: 9/01/99    Time: 2:55p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added EEV_400x1340_B_FT
*  
*  *****************  Version 79  *****************
*  User: Dan          Date: 6/16/99    Time: 12:52p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added 'EEV_2048x1024_FT_CCD47_20'
*  
*  *****************  Version 78  *****************
*  User: Terry        Date: 6/09/99    Time: 10:11a
*  Updated in $/WinX32 V2.5/INCLUDE
*  Add  ROM_DIF as a readout mode
*  
*  *****************  Version 77  *****************
*  User: Dan          Date: 5/13/99    Time: 4:14p
*  Updated in $/WinX32 V2.5/INCLUDE
*  added "EEV 512x2048 CCD42_10"
*  
*  *****************  Version 76  *****************
*  User: Dan          Date: 4/20/99    Time: 3:11p
*  Updated in $/WinX32 V2.5/INCLUDE
*  implemented PICHIPDB -- Dynamic Chip DLL
*  
*  *****************  Version 75  *****************
*  User: Terry        Date: 2/22/99    Time: 2:36p
*  Updated in $/WinX32 V2.5/INCLUDE
*  Add GENERIC controller
*  
*  *****************  Version 73  *****************
*  User: Charlie      Date: 2/09/99    Time: 1:09p
*  Updated in $/WinX32 V2.4/INCLUDE
*  Replaced  old data type constants with new RS_
*  
*  *****************  Version 72  *****************
*  User: Dan          Date: 11/17/98   Time: 3:21p
*  Updated in $/WinX32 V2.4/INCLUDE
*  renamed RSS1024x1024
*  
*  *****************  Version 71  *****************
*  User: Dan          Date: 11/12/98   Time: 2:02p
*  Updated in $/WinX32 V2.4/INCLUDE
*  changed 'EEV_100x1340_6ph_CCD36' to 'EEV_100x1340_F'
*  added 4 EEV 1340's Back chips
*  
*  *****************  Version 69  *****************
*  User: Dan          Date: 9/25/98    Time: 1:42p
*  Updated in $/WinX32 V2.3/INCLUDE
*  added chip "RSS_1024x1024_FT"
*  
*  *****************  Version 68  *****************
*  User: Val          Date: 9/18/98    Time: 4:46p
*  Updated in $/WinX32 V2.3/SUPPORT/ST133 Binary
*  
*  *****************  Version 67  *****************
*  User: Charlie      Date: 9/16/98    Time: 11:03p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Acton Changes.
*  
*  *****************  Version 66  *****************
*  User: Bob          Date: 9/09/98    Time: 10:45a
*  Updated in $/WinX32 V2.3/INCLUDE
*  Removed all double slash comments for macintosh...
*  
*  *****************  Version 65  *****************
*  User: Charlie      Date: 8/05/98    Time: 11:29a
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added pvcam.
*  
*  *****************  Version 64  *****************
*  User: Val          Date: 7/29/98    Time: 4:44p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added chips INGAAS_1x256 and INGAAS_1x512
*  
*  *****************  Version 61  *****************
*  User: Val          Date: 7/10/98    Time: 2:14p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Took out EEV_80x80.. test chip.
*  Took out OEEV_1203x1306_6ph, error..
*  
*  *****************  Version 60  *****************
*  User: Val          Date: 7/09/98    Time: 1:50p
*  Updated in $/WinX32 V2.3/INCLUDE
*  PID_1024x512_SFT was added twice.  Took out second add.
*  
*  *****************  Version 59  *****************
*  User: Val          Date: 7/09/98    Time: 1:05p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added chip OEEV_1203x1306_6ph
*  
*  *****************  Version 58  *****************
*  User: Val          Date: 7/09/98    Time: 11:17a
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added chips EEV_80x80 and PID_1024x512_SFT
*  
*  *****************  Version 57  *****************
*  User: Dan          Date: 7/01/98    Time: 1:12p
*  Updated in $/WinX32 V2.3/INCLUDE
*  implemented EEV 1024x512 FT CCD57 chip
*  
*  *****************  Version 56  *****************
*  User: Bob          Date: 6/22/98    Time: 11:59a
*  Updated in $/WinX32 V2.3/INCLUDE
*  Changed Name of multitap chip...
*  
*  *****************  Version 55  *****************
*  User: Baker        Date: 6/08/98    Time: 1:00p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added 3 chips, Hama 60, 124, and 252 x 1024.
*  
*  *****************  Version 54  *****************
*  User: Bob          Date: 5/29/98    Time: 4:31p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added Groupings
*  
*  *****************  Version 53  *****************
*  User: Bob          Date: 5/22/98    Time: 3:23p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added 2 Functions SetChannelGain and SetChannelOffset...
*  
*  *****************  Version 52  *****************
*  User: Bob          Date: 5/21/98    Time: 3:20p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Added New Chip For 16-Tap...
*  
*  *****************  Version 51  *****************
*  User: Terry        Date: 5/13/98    Time: 2:29p
*  Updated in $/WinX32 V2.3/INCLUDE
*  Add READOUT_NOTUSED enum
*  
*  *****************  Version 49  *****************
*  User: Bob          Date: 3/18/98    Time: 2:26p
*  Updated in $/WinX32 V2.2/INCLUDE
*  Added Stuff for Epix PCI Digital Interface...
*  
*  *****************  Version 48  *****************
*  User: Shige        Date: 98/02/20   Time: 15:17
*  Updated in $/WinX32 V2.2/INCLUDE
*  Rename THM_1024x1024 to THM_2048x1024FT  
*
*  *****************  Version 47  *****************
*  User: Shige        Date: 98/02/20   Time: 14:42
*  Updated in $/WinX32 V2.2/INCLUDE
*  Rename THM_1024x1024 to THM_2048x1024FT
*
*  *****************  Version 46  *****************
*  User: Charlie      Date: 2/02/98    Time: 3:05p
*  Updated in $/WinX32 V2.2/INCLUDE
*  Added empty controller.
*
*  *****************  Version 45  *****************
*  User: Dan          Date: 1/30/98    Time: 12:47p
*  Updated in $/WinX32 V2.2/INCLUDE
*  implemented  OEEV_1300x1340
*
*  *****************  Version 44  *****************
*  User: Charlie      Date: 1/29/98    Time: 9:20p
*  Updated in $/WinX32 V2.2/INCLUDE
*  re hooked some chips and added thm2048x2048
*
*  *****************  Version 43  *****************
*  User: Charlie      Date: 1/14/98    Time: 8:17p
*  Updated in $/WinX32 V2.2/INCLUDE
*  Added space holders for 4 EEV specials.
*
*  *****************  Version 41  *****************
*  User: Terry        Date: 12/22/97   Time: 4:47p
*  Updated in $/WinX32 V2.1/INCLUDE
*  Use Test Chips for unreleased chips
*
*  *****************  Version 40  *****************
*  User: Charlie      Date: 12/02/97   Time: 3:59p
*  Updated in $/WinX32 V2.1/INCLUDE
*  Added eev 80x80.
*
*  *****************  Version 39  *****************
*  User: Shige        Date: 97/11/28   Time: 14:51
*  Updated in $/WinX32 V2.1/INCLUDE
*  Eliminate a comma at the last entry in enum collection_type
*
*  *****************  Version 38  *****************
*  User: Dan          Date: 11/25/97   Time: 9:51a
*  Updated in $/WinX32 V2.1/INCLUDE
*  added SITe 2048x2048 Back&Front
*
*  *****************  Version 37  *****************
*  User: Charlie      Date: 9/17/97    Time: 2:35p
*  Updated in $/WinX32 V2.1/INCLUDE
*  Took out wrong comment
*
*  *****************  Version 36  *****************
*  User: Shige        Date: 97/08/14   Time: 12:40
*  Updated in $/WinX32 V2.1/INCLUDE
*  eliminate the last comma at enum ReadOutMode
*
*  *****************  Version 35  *****************
*  User: Dan          Date: 6/23/97    Time: 9:00a
*  Updated in $/WinX32 V2.0/INCLUDE
*  added new chips -- EEV400x1340, EEV700x1340, EEV1300x1340,
*      EEV1024x1024 and EEV1024x1024FT
*
*  *****************  Version 34  *****************
*  User: Charlie      Date: 6/20/97    Time: 2:21p
*  Updated in $/WinX32 V2.0/INCLUDE
*  Added low cost camera and 5Mhz camera.
*
*  *****************  Version 33  *****************
*  User: Charlie      Date: 6/05/97    Time: 1:58p
*  Updated in $/WinX32 V2.0/INCLUDE
*  Added new Sarnoff 512x512 chip, also added 3 new controllers.
*
*  *****************  Version 32  *****************
*  User: Bob          Date: 5/16/97    Time: 10:14a
*  Updated in $/WinX32 V2.0/INCLUDE
*  Added PCI_TIMER_Interface
*
*  *****************  Version 31  *****************
*  User: Terry        Date: 5/02/97    Time: 5:03p
*  Updated in $/WinX32 V2.0/INCLUDE
*  Add  PID_2500x600_B and  PID_2500x600_F chips
*
*  *****************  Version 30  *****************
*  User: Charlie      Date: 4/14/97    Time: 3:50p
*  Updated in $/WinX32 V2.0/INCLUDE
*  Changed comments for controllers.
*
*  *****************  Version 29  *****************
*  User: Bob          Date: 3/27/97    Time: 7:25a
*  Updated in $/WinX32 V2.0/INCLUDE
*  Added Fibre Channel Interface
*
*  *****************  Version 28  *****************
*  User: Dan          Date: 3/11/97    Time: 1:52p
*  Updated in $/WinX32 V2.0/Include
*  removed the duplicated ROM_INTERLINE enum
*
*  *****************  Version 27  *****************
*  User: Shige        Date: 97/03/11   Time: 12:38
*  Updated in $/WinX32 V2.0/INCLUDE
*  add INTERLINE to readout mode
*
*  *****************  Version 26  *****************
*  User: Terry        Date: 2/10/97    Time: 4:43p
*  Updated in $/WinX32 V2.0/INCLUDE
*  Change values for EDGE TRIGGER
*
*  *****************  Version 25  *****************
*  User: Dan          Date: 2/05/97    Time: 8:23a
*  Updated in $/WinX32 V2.0/INCLUDE
*  implement V1.6 changes
*
*
*        2/05/97 7:56a Dan
*  added PID_1030x1300 -- PI (Special) 1030x1300 chip
*
*  24    1/28/97 3:50p Charlie
*  More IsAvail and GetEnumParam additions.
*
*  23    1/27/97 9:15p Charlie
*  More IsAvail fixes.
*
*  22    1/27/97 9:21a Terry
*  Add new controllers, take out unsupported ones; Add some enums moved
*  from cmenum.h
*
*  21    1/03/97 9:41a Bob
*  added chips for viccd to bottom of detector list
*
*  20    1/02/97 5:11p Terry
*  Add new versions of ST133 as specific controllers
*
*  19    12/13/96 9:03a Bob
*
*  18    11/06/96 4:51p Terry
*  Add EEV 100x1340 6ph CCD36 & PI 1030x1300 (special) and
*  change define of SIT_800x1000_B to PID_ 800x1000_B
*
*  17    11/04/96 12:26p Charlie
*  Added ecp_interface (extended parallel) and changed interrupts enums to
*  more logical values.
*
*  16    10/07/96 7:42a Dan
*  implemented the V1.6 updates
*
*        9/13/96 6:58a Terry
*  Add new diode arrays: DA256S_INGAS, DA512S_INGAS, DA128S_GE,  &
*  DA256S_GE
*
*        9/04/96 12:23p Charlie
*  Added SIT 800x1000 and PI specials (hamma).
*
*  15    8/15/96 11:59a Maynard
*
*/

#if !defined PIGENDEF_H
#define      PIGENDEF_H     /* define indicates that include is done now */
                            /* allows multiple includes */

/* definitions of enumerated types */
/* ########################################################### */
/*                  LEVEL 1 DLLs                               */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_CreateController               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Create and Initialize controller object. Set some defaults. MUST be 1ST   */
/* function called.                                                          */
/* int PICM_CreateController                                                 */
/*  int Controller_type      :: controller to create, see ctrl_type          */
/*  int Detector_type        :: CCD/PDA to run, see ctrl_CCD_sensor          */
/*  int Data_Collection_Mode :: Data collection mode, see sensorReadoutMode  */
/*  int application_type     :: type of application, see Application_Type    */
/*  unsigned int *error_code :: Error code if, used if function returs false */


/* controller type definition */
/* #### used by PICM_CREATECONTROLLER param 1 #### */
enum ctrl_type
{
    NO_CONTROLLER = 0,                       /* PICM Support status      */
    ST143,                  /* ST143         =  1    Future - Supported  */
    ST130,                  /* ST130         =  2    Supported           */
    ST138,                  /* ST138         =  3    Supported           */
    VICCDBOX,               /* VICCD BOX     =  4    Supported           */
    DC131,                  /* PentaMax      =  5    Supported           */
    ST120_T1,               /* ST120(Type 1) =  6    Not supported       */
    ST120_T2,               /* ST120(Type 2) =  7    Not supported       */
    ST121,                  /* ST121         =  8    Supported           */
    ST135,                  /* ST135         =  9    Not supported       */
    ST133,                  /* ST133         = 10    Supported           */
    VICCD,                  /* VICCD         = 11    Supported           */
    ST116,                  /* ST116         = 12    Not supported       */
    OMA3,                   /* 1461, 1471    = 13    Not supported       */
    LOW_COST_SPEC,          /* Low cost spectroscopy controller. Future. */
    MICROMAX,               /* Ver of ST133  = 15    Supported           */
    SPECTROMAX,             /* Ver of ST133  = 16    Future - Supported  */
    MICROVIEW,              /* Ver of ST133  = 17    Supported           */
    ST133_5MHZ,             /* ST133 5Mhz system.    Future.             */
    EMPTY_5MHZ,             /* Doesn't write to controller.              */
    EPIX_CONTROLLER,        /* Epix Stuff                                */
    PVCAM,                  /* Photometrics controllers.                 */
    GENERIC,                /* Available for doing test controllers      */
    ARC_CCD_100,            /* Acton's MSP-100 + Spectrograph (USB)      */
    ST133_2MHZ,             /* ST133 2Mhz system.    Future.             */
    END_OF_CONTROLLER_LIST  /* END OF ENUMERATED CONTROLLER TYPES        */
};



/*********  ADD NEW DETECTORS TO END OF LIST!!  *********/
/*                                                      */
/******  Also add detector to 'ccd_resource_xref'  ******/
/* #### used by PICM_CREATECONTROLLER param 2 (if ccd) #### */
enum ctrl_CCD_sensor
{
                           /*             DLL/WinView        Y     X      */
    CUSTOM_CCD = -1,       /*  Custom User defined CCD chip           */
/*** CUSTOM_CCD AS A CHIP TYPE IS NO LONGER USED !!!! ***/

                               /* CCD	                                          */
    NO_CCD_SENSOR,             /* Enum       PN#  CCD                X     Y      */
    EEV_256x1024_3ph,          /*     EEV 256x1024 3-phase           256  1024    */
    EEV_576x384_3ph,           /*     EEV 576x384 3-phase            576   384    */
    EEV_1152x298_3ph,          /*     EEV 1152x298 3-phase          1152   298    */
    EEV_1152x1242_3ph,         /*     EEV 1152x1242                 1152  1242    */
    KDK_512x768,               /*   5 KODAK 512x768                  512   768    */
    KDK_1035x1317,             /*     KODAK 1035x1317               1035  1317    */
    KDK_1024x1280,             /*     KODAK 1024x1280               1024  1280    */
    KDK_2044x2033,             /*     KODAK 2044x2033               2044  2033    */
    KDK_2048x3072,             /*     KODAK 2048x3072               2048  3072    */
                               /*     Fast kodak special, will be removed in future */
    KODAKFAST1400,             /*  10 Use custom chip               1035  1317    */
                               /*     Overscan special, will be removed in future */
    OSTK1024B,                 /*     Use custom chip               1050  1050    */
    PID_330x1100_8phH,         /*     PI 330x1100 8 phase (horz)     330  1100    */
    PID_532x1752,              /*     PI 532x1752                    532  1752    */
    RET_400x1200,              /*     RET 400x1200                   400  1200    */
    RET_512x512,               /*  15 RET 512x512                    512   512    */
    NOT_USED2,                 /*     old EEV 576x384  (not used)    576   384    */
    RET_1024x1024,             /*     RET 1K x 1K                   1024  1024    */
    RET_2048x2048,             /*     RET 2K x 2K                   2048  2048    */
    TEK_512x512_B_100ns,       /*     TEK512x512B Back  [100ns]      512   512    */
    TEK_512x512_F_100ns,       /*  20 TEK512x512F Front [100ns]      512   512    */
    TEK_1024x1024_B_100ns,     /*     TEK1024x1024B Back [100ns]    1024  1024    */
    TEK_1024x1024_F_100ns,     /*     TEK1024x1024F Front[100ns]    1024  1024    */
    TEK_2048x2048,             /*     TEK 2K x 2K                   2048  2048    */
    THM_576x384,               /*     TH576x384                      576   384    */
    EEV_256x1024_6ph,          /*  25 EEV 256x1024  6 PHASE          256  1024    */
    EEV_1024x512_FT,           /*     EEV frame transfer            1024   512    */
    NOT_USED3,                 /*     Use custom chip                512  1024    */
    NOT_USED4,                 /*     Use custom chip                512  1024    */
    EEV_576x384_6ph,           /*     EEV576x384   6 PHASE           576   384    */
    EEV_1152x298_6ph,          /*  30 EEV1152x298  6 PHASE          1152   298    */
    EEV_1152x1242_6ph,         /*     EEV1152x1242 6 PHASE          1152  1242    */
    NOT_USED5,                 /*     Use custom chip               1024  2048    */
    MIT_CCD_36,                /*     MIT CCD 36 special chip       2048  1024    */
    TEK_1024x1024_B_200ns,     /*     TEK1024x1024B Back Illm       1024  1024    */
    TEK_1024x1024_F_200ns,     /*  35 TEK1024x1024F Front Illm      1024  1024    */
    KDK_1024x1536,             /*     KODAK 1024x1536               1024  1536    */
    TEK_512x512_B_200ns,       /*     TEK512x512B [200ns]            512   512    */
    TEK_512x512_F_200ns,       /*     TEK512x512F [200ns]            512   512    */
    FCD_4096x4096F,            /*     Fairchild 4096 x 4096         4091  4096    */
    TEK_512x512D_B,            /*  40 TEK512x512D Back Illm          512   512    */
    TEK_512x512D_F,            /*     TEK512x512D Front Illm         512   512    */
    HAM_64x1024,               /*     HAMMAMATSU   64 x 1024          64  1024    */
    HAM_128x1024,              /*     HAMMAMATSU  128 x 1024         128  1024    */
    HAM_256x1024,              /*     HAMMAMATSU  256 x 1024         256  1024    */
    EEV_256x1024_8ph,          /*  45 EEV 256 x 1024 8 PHASE         256  1024    */
    EEV_1152x770_3ph,          /*     EEV1152x770  3 PHASE          1152   770    */
    EEV_1152x770_6ph,          /*     EEV 1152x770 6 PHASE          1152   770    */
    TEK_1024x1024_B_42usV,     /*     TEK1024x1024B Back Illm       1024  1024    */
    PID_330x1100_6phH,         /*     PI 330x1100 6 PHASE (horz)     330  1100    */
    EEV_256x1024_6ph_CCD30,    /*  50 EEV 256x1024  Front   CCD30    256  1024    */
    TEK_1024x1024D_B,          /*     TEK1024x1024D Back Illm       1024  1024    */
    TEK_1024x1024D_F,          /*     TEK1024x1024D Front Illm      1024  1024    */
    TEK_1024x1024D_B_T3,       /*     TEK1024x1024D Back Illm       1024  1024    */
    THM_512x512,               /*     Thomson 512X512 Front Illum    512   512    */
    THM_256x1024,              /*  55 Thomson 256X1024 FI MPP        256  1024    */
    THM_2048x1024_FT,          /*     Thomson 2048X1024 FT          1024  1024    */
    SIT_800x2000_B,            /*     SIT 800x2000 Back Illm         800  2000    */
    SIT_800x2000_F,            /*     SIT 800x2000 Front Illm        800  2000    */
    PID_240x330_MCT,           /*     TEST CHIP # 1                               */
    OEEV_1203x1336_3ph,        /*  60 EEV 1203x1336                 1203  1336    */
    OEEV_1203x1336_6ph,        /*     EEV 1203x1336                 1203  1336    */
    PI_800x1000_B,             /*     PI 800x1000 back               800  1000    */
    PI_64x1024,                /*     PI special   64 x 1024          64  1024    */
    PI_128x1024,               /*     PI special  128 x 1024         128  1024    */
    PI_256x1024,               /*  65 PI special  256 x 1024         256  1024    */
    KDK_4096x4096,             /*     Kodak 4096x4096               4096  4096    */
    EEV_100x1340_F,            /*     EEV 100x1340  Front   CCD36    100  1340    */
    PID_1030x1300,             /*     PI Special 1030x1300          1030  1300    */
    VICCD_NTSC_480x640,        /*     Video Chip - N. American Std   480   640    */
    VICCD_CCIR_576x768,        /*  70 Video Chip - European Std      576   768    */
    PID_582x782,               /*     PI Special 582x782             582   782    */
    PID_2500x600_B,            /*     PI 2500x600 Back              2500   600    */
    PID_2500x600_F,            /*     PI 2500x600 Front             2500   600    */
    PID_1024x512_SFT,          /*     PI 512x512                     512   512    */    
    EEV_400x1340,              /*  75 EEV 400x1340 Front             400  1340    */
    EEV_700x1340,              /*     EEV 700x1340 Front             700  1340    */
    EEV_1024x1024,             /*     EEV                               */
    EEV_1024x1024_FT,          /*     EEV frame transfer            1024  1024    */
    EEV_1300x1340,             /*     EEV 1300x1340 Front           1300  1340    */
    SIT_2048x2048_B,           /*  80 SITE 2048x2048 Back           2048  2048    */
    SIT_2048x2048_F,           /*     SITE 2028x2048 Front          2048  2048    */
    EEV_80x80,                 /*     EEV 80x80 FT                                 */
    TEST_CCD36_00,             /*     Special ccd36 for EEV.         110  1356    */
    TEST_CCD36_10,             /*     Special ccd36 for EEV.         410  1356    */
    TEST_CCD36_20,             /*  85 Special ccd36 for EEV.         710  1356    */
    TEST_CCD36_40,             /*     Special ccd36 for EEV.        1330  1356    */
    THM_2048x2048,             /*     Thomson 2048x2048             2048  2048    */
    OEEV_1300x1340,            /*     EEV 1300x1340 [OverScan]      1300  1340    */
    EPIX_1300x1024,            /*     Epix Controller */    
    PIB_512x512_FT,            /*  90 PI Back 512x512 Frame Xfer(16-Tap)          */
    HAM_60x1024,               /*     HAMMAMATSU   60 x 1024          60  1024    */
    HAM_124x1024,              /*     HAMMAMATSU  124 x 1024         124  1024    */
    HAM_252x1024,              /*     HAMMAMATSU  252 x 1024         252  1024    */
    EEV_1024x512_FT_CCD57,     /*     EEV frame transfer CCD57      1024   512    */
    INGAAS_1x256,              /*  95 InGaAs chip                      1   256    */
    INGAAS_1x512,              /*     InGaAs chip Interleaving         1   512    */
    RSS_1024x1024,             /*     Roper Scientic Special FT     1024  1024    */  
    EEV_100x1340_B,            /*     EEV 100x1340  Back   CCD36     100  1340    */
    EEV_400x1340_B,            /*     EEV 400x1340  Back             400  1340    */
    EEV_700x1340_B,            /* 100 EEV 700x1340  Back             700  1340    */
    EEV_1300x1340_B,           /*     EEV 1300x1340 Back            1300  1340    */
    EEV_1024x1024_CCD47_10,    /*     EEV 1024x1024 CCD47-10        1024  1024    */
    EEV_512x2048_CCD42_10,     /*     EEV  512x2048 CCD42-10         512  2048    */
    EEV_2048x1024_FT_CCD47_20, /*     EEV2048x1024FT CCD47_20       2048  1024    */
    EEV_400x1340_B_FT,         /* 105 EEV 400x1340  Back Frame Xfer  400  1340    */
    EEV_256x1024_6ph_CCD30_B,  /*     EEV 256x1024  Back CCD30       256  1024    */
    EEV_256x1024_6ph_CCD30_OE, /*     EEV 256x1024  OE   CCD30       256  1024    */
    HAM_58x1024_B,             /*     HAMMAMATSU   58 x 1024 Back     58  1024    */
    HAM_122x1024_B,            /*     HAMMAMATSU  122 x 1024 Back    122  1024    */
    HAM_250x1024_B,            /* 110 HAMMAMATSU  250 x 1024 Back    250  1024    */
    EEV_2048x2048_CCD42_40,    /*     EEV 2048x2048 CCD42_40        2048  2048    */
    PID_330x1100_8phH_V2,      /*     PID  330x1100 [8ph] V2         330  1100    */
    RSS_1024x512_FT,           /*     Roper Scientic Special FT      512   512    */  
    KAF_2084x2084,             /*     Kodak 2084x2084 [KAF-4300E]   2084  2084    */
    EEV_100x1340_F_GATAN,      /* 115 EEV 100x1340  Front   CCD36    100  1340    */
    EEV_400x1340_F_GATAN,      /*     EEV 400x1340 Front             400  1340    */
    HAM_2x2048,                /*     HAM 2x2048 (CCD-PDA)             2  2048    */
    KAF_2084x2084_SCX,         /*     Kodak 2084x2084 [XRAY]        2084  2084    */
    MAR_576x576_FT_CCD65,      /*     Marconi 288x576 FT CCD65       576   576    */
    MAR_512x512_CCD77,         /* 120 Marconi 512x512 CCD77          512   512    */
    EEV_512x2048B_CCD42_10,    /*     EEV  512x2048 Back CCD42-10    512  2048    */
    INGAAS_1x1024,             /*     InGaAs chip Interleaving         1  1024    */
    END_OF_CCD_LIST            /* END OF ENUMERATED CCD TYPE,                 */
};

/* sensor type definition */
/* #### used by PICM_CREATECONTROLLER param 2 (if diode array) #### */
enum ctrl_PDA_sensor
{
    NO_PDA_SENSOR =1000,
    DA0128S,                /* single  128 */
    DA0256S,                /* single  256 */
    DA0512S,                /* single  512 */
    DA1024S,                /* single 1024 */
    DA2048S,                /* single 2048 */
    DA0128D,                /* dual    128 */
    DA0256D,                /* dual    256 */
    DA0512D,                /* dual    512 */
    DA1024D,                /* dual   1024 */
    DA2048D,                /* dual   2048 ! */
    DA256S_INGAS,           /* Single 256 INGAS */
    DA512S_INGAS,           /* Single 512 INGAS */
    DA128S_GE,              /* Single 128 GE    */
    DA256S_GE,              /* Single 256 GE    */
    PDA_DUMMY               /* indicates end of list  */
};


/* CCD chip frame readout mode  */
/* #### used by PICM_CREATECONTROLLER param 3  #### */
/* for normal data collection USE ReadFullFrame */
enum sensorReadoutMode
{
    READOUT_NOTUSED = 0,       /* Readout Mode not used               */
    ROM_FULL,                  /* normal data collection mode.        */
    ROM_FRAME_TRANSFER,        /* frame transfer mode (st138)         */
    ROM_KINETICS,              /* kinetics (st138)                    */
    ROM_INTERLINE,             /* interlined CCD mode                 */
    ODD_FRAME,                 /* viccd only                          */
    EVEN_FRAME,                /* viccd only                          */
    ANY_FRAME,                 /* viccd only                          */
    ROM_DIF                    /* ST133 5Mhz double image format.     */ 
};

/* VICCD: CW or Gate mode */
enum CW_GATE_MODE
{
    CW_MODE   = 1,
    GATE_MODE
};


/* trigger modes --- Used for Ext. Trig. mode settings  */
#define TRIGON  1
#define TRIGOFF 0


/*  EDGE TRIGGER Polarity enumerator type -- DC131 & VICCD  */
enum polarity_selections
{
    EDGE_TRIGGER_NOT_AVAILABLE = 1,
    EDGE_TRIGGER_POS,
    EDGE_TRIGGER_NEG
};


/* Definition of application */
/* #### used by PICM_CREATECONTROLLER param 4  #### */
enum Application_Type
{
    APP_NORMAL_IMAGING,         /* General case imaging                */
    APP_SPECTROSCOPY,           /* for single (few) strip spectroscopy */
    APP_MICROSCOPY              /* for cameras on microscopes.         */
};

/* ##### ERROR CODES for PICM_CreateController ##### */
#define CREATE_CONTROLLER_ERROR    0x0001 /* Controller object could not be  */
                                          /* created, no futher operation is */
                                          /* allowed.                        */

#define DETECTOR_TYPE_ERROR        0x0002 /* Error occured in seting given   */
                                          /* detector type (i.e. CCD or PDA  */
                                          /* illegal).                       */
                                          /* Check to see if detector and    */
                                          /* controller are legal combination*/

#define DATA_COLLECTION_MODE_ERROR 0x0004 /* Error occured in setting data   */
                                          /* collection mode, check to see   */
                                          /* if controller and/or detector   */
                                          /* can perform this data collection*/
                                          /* mode.                           */

#define DATA_GEOMETRY_ERROR        0x0008 /* error in default setting of     */
                                          /* flip/rotate/reverse             */

#define DATA_ACCESS_ERROR          0x0010 /* error in setting default data   */
                                          /* access type                     */

#define CLEANSCANS_ERROR           0x0020 /* error occured trying to set     */
                                          /* default clean scans.            */

#define X_SKIPPING_ERROR           0x0040 /* error occurred while trying to  */
                                          /* assign default x skip size      */

#define SHUTTER_ERROR              0x0080 /* error occured in either         */
                                          /* assigning a default shutter or  */
                                          /* shutter mode                    */

#define ACCESS_PATTERN_ERROR       0x0100 /* error occured in setting default*/
                                          /* access pattern.                 */

#define TIMING_MODE_ERROR          0x0200 /* error occured in setting default*/
                                          /* timing mode.                    */

#define EXPOSURE_ERROR             0x0400 /* error occured in setting up     */
                                          /* default exposure.               */

#define GENERAL_ERROR              0x8000 /* Other errors involving setting  */
                                          /* up controller object failed.    */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_SetInterfaceCard                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Set type of PC PI-interface card used. This will also set the ADC     */
/* defaults, for ST138 it will read what is available and set to fastest */
/* ADC available.                                                        */
/* int PICM_SetInterfaceCard                                                 */
/*   int Interface_Card       :: Interface card, see interfaceType enum      */
/*   unsigned int Base_Address:: base add. of interface card, not used eisa  */
/*   int Card_interrrupt      :: Interrupt to use, see interrupt_channel enum*/
/*   unsigned int *error_code :: Error code, used if function returs false.  */

/* Controller interface type */
/* #### used by PICM_SetInterface param 1  #### */
enum interfaceType
{
    NotConnected=0,
    DMA_Interface,       /* DMA  : fast! (ISA board)                      */
    TAXI_Interface,      /* TAXI : fast serial  (ISA board)               */
    EISA_Interface,      /* EISA : EISA computer board                    */
    TAXI_TypeB_Interface,/* TAXI : ISA board in EISA computer, Type B DMA */
    GPIB_Interface,      /* GPIB : OK but not fast...                     */
    SUN_EDT_Interface,   /* Sun computer, EDT interface card.             */
    SERIAL_Interface,    /* Serial RS170 interface (VICCD)                */
    TAXI_TypeF_Interface,/* TAXI : ISA board in PCI computer, Type F DMA  */
    SCSI_Interface,      /* SCSI : interface using apsi.                  */
    OMA4ISA_Interface,   /* OMA4 : Interface using memory-mapped ISA card */
    PCI_COMPLEX_PC_Interface, /* PCI scatter-gather, for IBM-PC card.     */
    PCI_SIMPLE_PC_Interface,  /* PCI simple sw does all the work, for IBM */
                              /* PC card.                                 */
    PCI_COMPLEX_MAC_Interface,/* PCI scatter-gather, for MAC card.        */
    PCI_SIMPLE_MAC_Interface, /* PCI simple sw does all the work, for Mac */
    DEMO_Interface,           /* for demo software and test software.     */
    EISA_Enhanced_Interface,  /* Eisa with new Datacollection object and  */
                              /* ring zero driver                         */
    ECP_Interface,            /* Extended Communication Parallel interface*/
    DT3152_Interface,     /* Data Translation PCI Frame Grabber(RS170)*/
    PCI_FibreChannel_Interface,/* PCI Fast Fibre Channel Interface      */
    PCI_TIMER_Interface,    /* PCI With timer no interrupts */
    EPIX_Interface,         /* Epix Interface */
    USB_Interface       /* Universal Serial Bus Interface */
};

/* interrupt channel definition */
/* #### used by PICM_SetInterface param 3  #### */
/* NOTE:This enumerated type changed values 10/4/96 for official 2.0 Easy  */
/* DLLs. Channels 10, 11, 12, and 15 where 0-3, now they are 10,11,12, and */
/* 15. and channels 0-15 added.                                            */
enum interrupt_channel
{
    CHANNEL_0=0,
    CHANNEL_1=1,
    CHANNEL_2=2,
    CHANNEL_3=3,
    CHANNEL_4=4,
    CHANNEL_5=5,
    CHANNEL_6=6,
    CHANNEL_7=7,
    CHANNEL_8=8,
    CHANNEL_9=9,
    CHANNEL_10=10,
    CHANNEL_11=11,
    CHANNEL_12=12,
    CHANNEL_13=13,
    CHANNEL_14=14,
    CHANNEL_15=15,
    CHANNEL_TIMER=30000,
    CHANNEL_NONE=31000
};

/* ############################################# */
/* ##### Groupings for 143 binning         ##### */
/* ############################################# */
enum xy_groupings
{
    GROUP1x1=0,
    GROUP2x2=1,
    GROUP4x4=2,
    GROUP8x8=3
};
/* ############################################# */
/* ##### ERROR CODES for PICM_SetInterface ##### */
/* ############################################# */

#define INTERFACE_TYPE_ERROR   0x0001 /* illegal interface                  */
#define BASE_ADDRESS_ERROR     0x0002 /* illegal base address               */
#define QUERY_CONTROLLER_ERROR 0x0004 /* error occured talking to controller*/
#define ATOD_CONVERTER_ERROR   0x0008 /* an illegal A to D converter was    */
                                      /* entered. */
#define GAIN_MULTIPLIER_ERROR  0x0010 /* an illegal gain mulitplier was set */
#define DATA_CLIP_ERROR        0x0020 /* an illegal data clip value was set */
#define CONTROLLER_SPEED_ERROR 0x0040 /* A illegal controller speed was     */
                                      /* entered (check valid speeds for    */
                                      /* ADCs).                             */
#define NEEDS_EISA_COMPUTER    0x0080 /* The fastest speeds this controller */
                                      /* can run need a EISA computer. If   */
                                      /* controller supports slower speeds  */
                                      /* you can try to set these manually  */
                                      /* this function will try defaulting  */
                                      /* to the slowest.                    */
                                      /* IF you have an EISA computer and a */
                                      /* PI ISA interface card and a 1 Mhz  */
                                      /* controller try interface type ::   */
                                      /* TAXI_TypeB_Interface (Note this is */
                                      /* only good on an EISA computer and  */
                                      /* only up to 1 Mhz).                 */
#define NEEDS_HIGH_SPEED_CARD  0x0100 /* Fastest speeds of controller need  */
                                      /* an EISA computer and a EISA PI     */
                                      /* interface card.                    */
#define IRQ_ERROR              0x0200 /* Error occured in IRQ setting.      */
/* if scsi interface being used the following error messages may occur.     */
#define BAD_TARGET_ID          0x0400 /* Error in setting target id.        */
#define BAD_ADAPTER_ID         0x0800 /* Error in setting adapter id.       */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Initialize_System                */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function down loads all information to controller It sets up the     */
/* dma buffers, ring buffer, and the users buffer. It Also hooks in the      */
/* interrupt routine used by data collection. All special settings (i.e      */
/* exposure, ROIs, etc) should be done before calling this function.         */
/* int PICM_Initialize_System                                                */
/*   void huge* big_buffer    :: Users data buf, Data collected stored here  */
/*   unsigned int *error_code :: Error code, used if function returs false.  */

/* ################################################## */
/* ##### ERROR CODES for PICM_Initialzie_System ##### */
/* ################################################## */

#define INITIALIZE_ERROR        0x0001 /* Error occured while trying to    */
                                       /* initialize the controller.       */

#define MEMORY_ALLOCATION_ERROR 0x0002 /* Error occured in trying to       */
                                       /* allocate ring buffer             */

#define INTERFACE_INIT_ERROR    0x0004 /* Error occured in initialize data */
                                       /* collection interface (check dma) */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                  PICM_SetExposure                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Set the camera exposure in seconds.                                       */
/* int PICM_SetExposure                                                      */
/*   double exposure          :: exposure time in seconds                    */
/*   unsigned int *error_code :: Error code, used if function returs false.  */

/* ############################################ */
/* ##### ERROR CODES for PICM_SetExposure ##### */
/* ############################################ */

#define EXPOSURE_SETTING_ERROR 0x0001 /* Exposure given was illegal       */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Chk_Data                       */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This routine checks if data has been collected. It returns TRUE if      */
/* either data has been successfully collected or if an error has occured. */
/* If data has been collected ok the status will set DONEDCOK (DONE Data   */
/* Collection OK) bit, otherwise check other bits for error see CTRL_STATUS*/
/* int PICM_Chk_Data                                                       */
/*   unsigned int *status_code   ::  status code                           */

/*  Status Returned as Paramater by PICM_Chk_Data                          */
/* CTRL_STATUS bit definitions                                           */
#define RUNNING         1   /* bit for "experiment running"              */
#define WAITING         2   /* bit for "waiting for start event"         */
#define CONERROR        4   /* bit for "controller error"                */
#define COMERROR        8   /* bit for "command error"                   */
#define NEWDATARDY     16   /* bit for "new data block received"         */
#define INITERROR      32   /* bit for "no initialization done"          */
#define NEWDATAFIXED   64   /* bit for "dma_copy_buffer -> to new data"  */
#define DATAOVERRUN   128   /* bit for "DMA data overrun"                */
#define VIOLATION     256   /* bit for "TAXI violation"                  */
#define MAILERROR     512   /* bit for                                   */
                            /* EISA :: mail box communication error      */
                            /* PCI :: mail box error (frame count)       */
#define XFERERRORCH0 1024   /* bit for Channel zero xfer not enabled.    */
#define XFERERRORCH1 2048   /* bit for Channel one  xfer not enabled.    */
#define DONEDCOK     4096   /* bit for done data collection.             */
#define INITIALIZED  8192   /* bit to say controller has been initialized*/

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*            PICM_SizeNeedToAllocate                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function returns the amount of memory the user should allocate to */
/* hold all of his data. NOTE : must have controller DLLs created after   */
/* 10/10/94 to use this function.                                         */
/* This function returns size needed for user buffer.                     */
/* long PICM_SizeNeedToAllocate (void);                                   */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                   PICM_CleanUp                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function should be called when data collection is complete (either */
/* through a successful data collection or an error condition).            */
/* This function deallocates all data collection buffers and unhooks the   */
/* data collection interrupt routine.                                      */
/* int PICM_CleanUp (void);                                                */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Start_controller                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*  Startup Controller to acquire data  */
/* int _export FAR PASCAL PICM_Start_controller(void);                     */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Stop_controller                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*  stops controller from acquireing data  */
/* int _export FAR PASCAL PICM_Stop_controller(void);                     */


/* ######################################################################## */
/* The following functions are extras, they don't need to be called but may */
/* be useful.                                                               */
/* ######################################################################## */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_sensor_x                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Get x dimension of chip.                            */
/* int _export FAR PASCAL PICM_Get_sensor_x(void);     */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_sensor_y                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Get y dimension of chip                             */
/* int _export FAR PASCAL PICM_Get_sensor_y(void);     */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_pixeldimension_x             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* read minimum x,y dimension for this access pattern  */
/* accessable pixel area: x value                      */
/* This is the actual x dimension of data coming back  */
/* from the controller. This function takes into account*/
/* ROIs and binning in the x and y dimension.          */
/* int PICM_Get_pixeldimension_x(void);                */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_pixeldimension_y             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* accessable pixel area: y value                      */
/* This is the actual y dimension of data coming back  */
/* from the controller. This function takes into account*/
/* ROIs and binning in the x and y dimension.          */
/* int PICM_Get_pixeldimension_y(void);                */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_TTL_pattern                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Send bit pattern to controller TTL_out port         */
/* this is supported by the ST12x, ST130, ST138, and ST133 controllers. */
/* int PICM_Set_TTL_pattern (int pattern);             */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_TTL_pattern                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* this is supported by the ST12x, ST130, ST138, and ST133 controllers. */
/* Read bit pattern from controller TTL_in port        */
/* int PICM_Get_TTL_pattern(void);                     */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_Fast_ADC                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function will set the fast ADC avaiable in controller. If */
/* controller only has one adc it will set it.                    */
/* int PICM_Set_Fast_ADC(void);                                   */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_Slow_ADC                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function will set the slow ADC avaiable in controller. If */
/* controller only has one adc it will set it.                    */
/* int PICM_Set_Slow_ADC(void);                                   */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*            PICM_Set_Data_Collection                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                                                     */
/* int PICM_Set/Get_Data_Collection                    */
/* int collection_type      :: type of data collection */



/* #### used by PICM_Set_Data_Collection      param 1 #### */
enum collection_type
{
    GENERIC_MODE = 1,
    FOCUS_MODE,          /* Return latest frame, skip old frames.            */
                         /* May not be implemented on all platforms/versions */
    NFRAME_MODE          /* Collect N-frames and then stop. auto stop mode   */
                         /* is n-frame with n being 1 (stop acq not called   */
                         /* if autostop true and n-frame > 0).               */
                         /* AutoStop may not be implemented on all platforms */
};

/* #### used by PICM_Set_EasyDLL_DC      param 1 #### */
enum easydll_collection_type
{
    EASYDLL_GENERIC_MODE = 1,
    STRIP_MODE,          /* ChkData returns after getting one strip.         */
    EASYDLL_FOCUS_MODE,  /* Only for Easy controller DLLs, should use this   */
                         /* should not use FOCUS_MODE (Internal use only).   */
    EASYDLL_NFRAME_MODE  /* Only for Easy controller DLLs, should use this   */
                         /* should not use FOCUS_MODE (Internal use only).   */
};

#endif 

/*
        end of pigendef.h
*********************************************************************
*/
