/*   PI controller DLLs external defintion fuctions for PI variables.
*    workfile:   s:\xsma\xdll\pivardef.h
*    $Logfile: /WinX32 V2.5/INCLUDE/pivardef.h $
*       $Date: 02/10/10 11:07 $
******************************************************************
*   Copyright (C) 1997, Princeton Instruments Inc.
*   All Rights Reserved.
*
*       pivardef.h
*
******************************************************************
*
*  contains the Declarations for PI variables functions 
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Skatsumata $    $Date: 02/10/10 11:07 $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/pivardef.h $
*  
*  168   02/10/10 11:07 Skatsumata
*  Added TITAN_SPECIAL to HW_FIXES
*  
*  167   02/07/12 13:06 Skatsumata
*  Added CMP_VSHIFT_TIME (vertical shift time in USEC)
*  
*  166   6/07/02 12:57p Hgrannis
*  Added subframe control.
*  
*  165   5/01/02 11:50a Croberts
*  Added serial params for detector head and system/controller.
*  
*  164   4/26/02 1:48p Croberts
*  added CMP_PV_CONT_CLEARS for PvCam
*  
*  163   4/19/02 4:54p Bob
*  Added Stuff for BOF/EOF Events!
*  
*  162   3/18/02 11:06a Bob
*  Added/Fixed Values for CMP_PV_SHTR_CLOSE_DELAY, CMP_PV_SHTR_OPEN_DELAY
*  
*  161   3/12/02 4:31p Croberts
*  Added CMP_PV_SHTR_CLOSE_DELAY for PvCam close shutter comp
*  
*  160   2/28/02 4:13a Croberts
*  added CMP_RESET_DATACOLLECTION to reset data collection for serial
*  violations.
*  
*  159   1/16/02 3:12p Dknouse
*  added enums for Continuous Cleans Instruction Available
*  
*  158   1/05/02 2:28a Croberts
*  Added enum type for CMP_FORCE_READOUT_MODE
*  
*  157   11/27/01 2:18p Croberts
*  Added CMP_FORCE_READOUT_MODE for CCD57 and CCD47.
*  
*  156   10/12/01 4:46p Hgrannis
*  Added avalanche gain setpoint and 'not used' status.
*  
*  155   01/10/10 16:46 Skatsumata
*  Added avalanche gain parameters and enum.
*  
*  154   10/09/01 12:56p Hgrannis
*  Added avalanche gain settings.
*  
*  153   9/17/01 4:21p Dknouse
*   the 'enum timing_style' was moved from CMENUM.h to here
*  
*  152   9/13/01 2:21p Croberts
*  Added CMP_SKIP_AT_ONCE_BLK for skips.
*  
*  151   8/21/01 3:03p Dbaker
*  Changed comments for CMP_CELL_X_SIZE, CMP_CELL_Y_SIZE, CMP_X_GAP_SIZE,
*  and CMP_Y_GAP_SIZE to reflect the fact that they are now type DOUBLE.
*  
*  150   4/24/01 3:37p Bob
*  Added some stuff for the CCD100 camera at acton!
*  
*  149   4/10/01 1:49p Terry
*  Add CMP_FIRMWAREVERSION
*  
*  148   2/27/01 1:47p Bob
*  Removed some CMPs that are never used and wont screw up the order...
*  
*  147   12/04/00 3:43p Bob
*  Added some stuff for use with pvcam...
*  
*  146   10/04/00 11:29a Charlie
*  Added var for display all possible ADCs for ST133.
*  
*  145   9/08/00 2:25p Charlie
*  Added anti-blooming and pre horizontal delay.
*  
*  144   6/23/00 9:48p Charlie
*  Added shutter comp pre, PvCam possible, and alt timing CMPs for PvCAm.
*  
*  143   5/12/00 3:55p Bob
*  Migrating Tons of Stuff From Contrman to Experiment Class
*  
*  142   5/11/00 2:45p Charlie
*  added CMP_FIRST_ACQUIRE_FLAG for ST133 online exposure problem crossing
*  readout time.
*  
*  141   5/04/00 10:13a Bob
*  Added Some PVcam stuff
*  
*  140   3/02/00 2:36p Charlie
*  Took out include for platform in the middle of the file. This should be
*  done outside this file.
*  
*  139   2/01/00 4:46p Charlie
*  Added CMP_CONT_CLNS_INST to determine if software should download the
*  special continous clean instruction. Also added CMP_TEMP_STATUS for
*  temperature status.
*  
*  138   12/10/99 3:22p Charlie
*  Took include out of the middle of the file
*  
*  137   12/09/99 7:50p Charlie
*  Added CMP_CIRC_BUFFER to isavail to determine if user can use circular
*  buffer feature.
*  
*  136   99/12/07 13:40 Shige
*  include "platform.h" to use the custom data type 
*  
*  135   99/11/23 10:55 Shige
*  Added the demo pattern parameter
*  
*  134   10/09/99 6:06p Charlie
*  upgraded from V2.4
*  
*  133   9/22/99 12:00p Terry
*  Add CMP_USE_HEADCALIB
*  
*  132   9/02/99 4:35p Terry
*  Update for CGR's 2.4 changes
*  
*  131   8/30/99 1:36p Terry
*  Add #define MAX_HDGAINS 4
*  
*  130   7/26/99 10:44a Terry
*  Add AntiBloom and additional Gain enum
*  
*  129   7/14/99 10:18a Bob
*  added event type..
*  
*  128   4/15/99 12:40p Bob
*  Added stuff to allow dmaing into the users buffer....
*  
*  127   3/24/99 4:22p Maynard
*  Fix error with parameter number for SKIPFRAMES
*  
*  126   3/12/99 5:09p Terry
*  Add CMPs for St143 board addresses
*  
*  125   3/05/99 4:57p Terry
*  Add CMP_BOARDS_WITH_NVRAM
*  
*  123   2/09/99 1:09p Charlie
*  Replaced  old data type constants with new RS_
*  
*  122   2/08/99 11:55a Charlie
*  Added RS_ for constants
*  
*  121   2/01/99 7:39p Charlie
*  Added CMP_ELEC_SHT for turning on electronic shutter.
*  
*  120   12/15/98 3:56p Terry
*  Add CMP_PTG_PRESENT
*  
*  119   12/11/98 1:26p Dan
*  added 'CMP_SW_EXTSYNC'
*  
*  118   12/10/98 3:19p Terry
*  Add  CMP_INTERNAL_SYNC_SRC
*  
*  117   11/20/98 5:05p Maynard
*  Implement CMP_OLD_ENDOFLIST fix for future backward compabibility
*  
*  116   11/20/98 3:49p Maynard
*  Cosmetic cleanup, fix some spelling (just inthe comments!)
*  
*  115   11/17/98 4:03p Charlie
*  Added BOF/EOF set/get params.
*  
*  114   10/30/98 9:00a Terry
*  Bring forward Harry's 2.3 changes
*  
*  113   10/27/98 11:59a Terry
*  Add FIXED_TEMPERATURE define
*  
*  
*  112   10/17/98 1:22p Charlie
*  Added CMP_AMP_DIALOG for heads that use horz dir for changing
*  amplifiers.
*  
*  110   10/12/98 5:39p Charlie
*  Added CMP_FORCE_NVRAM_FLAG to override previous settings and force new
*  settings, don't always want to do this because you could loss customers
*  settings.
*  
*  109   10/09/98 2:39p Charlie
*  fixed numbers
*  
*  108   10/08/98 12:20p Charlie
*  Added CMP_NVRAM_PROGRAM to allow isavails and set params to work
*  without working hardware. Also added CMP_BOARD_SET for Iccd-Max
*  detectors to control dg535 different.
*  
*  107   9/23/98 4:55p Charlie
*   Added CMP_SENSOR_TYPE.
*  
*  106   9/21/98 3:24p Charlie
*  Added number of analog gains for NvRam program.
*  
*  105   9/21/98 3:11p Bob
*  Added RESET_INTERFACE, to get the ST143 controller out of read and
*  write limbo...
*  
*  104   9/09/98 10:50a Bob
*  Removed final comma from enumerated types for mac...
*  
*  103   9/09/98 10:45a Bob
*  Removed all double slash comments for macintosh...
*  
*  102   9/02/98 9:07p Charlie
*  Added var for if nvram is available for controller.
*  
*  101   8/06/98 11:43a Charlie
*  source compensation
*  
*  100   8/04/98 8:00p Charlie
*  
*  99    8/04/98 7:49p Charlie
*  Added data collection type, and generic reading and writing to the
*  preamp board in the head and the i2c in the head.
*  
*  98    7/30/98 3:29p Charlie
*  experiment vars and more fast gscc vars.
*  
*  97    7/29/98 11:55a Charlie
*  High speed additions.
*  
*  96    7/24/98 4:07p Charlie
*  Added wait for TTL line and fast clock.
*  
*  95    7/19/98 7:21p Charlie
*  added CMP_CALIN for LED calibration for ST143.
*  
*  94    6/19/98 8:50a Terry
*  Make this conform to CMP order in 2.2
*  
*  93    6/17/98 10:47a Charlie
*  Added fast gating.
*  
*  92    6/17/98 9:55a Charlie
*  Added read from pulsar board and high voltage board on the I-Max. Also
*  added write to reset control board.
*  
*  91    6/15/98 4:30p Bob
*  Added CMP_REORG_FLAG for reorganizing data ...
*  
*  90    5/29/98 4:31p Bob
*  Added CMP_XY_GROUPING
*  
*  89    5/26/98 6:57p Charlie
*  Moved LN_COOLED and TE_COOLED here from cmenum
*  
*  87    5/10/98 3:07p Bob
*  Added Head Information Group to save and restore...
*  
*  86    5/08/98 2:39p Charlie
*  Added not used for pre-amp vars.
*  
*  85    5/04/98 8:25p Charlie
*  Added CMP_XDIM AND CMP_YDIM to get size of data.
*  
*  84    4/30/98 8:35p Charlie
*  Added more head types.
*  
*  83    4/29/98 6:22p Charlie
*  Added nvram routine to read control board and head of ST133.
*  
*  82    4/27/98 9:38p Charlie
*  Added control board.
*  
*  81    4/27/98 3:18p Charlie
*  new nvram vars. added.
*  
*  80    4/26/98 12:46p Charlie
*  Added Dual frame mask and two specials for Chad Dac0 and Dac1 writes
*  via i2c.
*  
*  79    4/20/98 1:31p Bob
*  Added NTPCI_TIMERFLAG to the enumerations list...
*  
*  78    4/19/98 6:15p Charlie
*  Added Imax variables and enums.
*  
*  77    4/17/98 9:15a Bob
*  Added CMP_PCI_CARDS for multiple cards...
*  
*  76    4/09/98 8:56a Terry
*  OOPS
*  
*  75    4/09/98 8:39a Terry
*  Add enums for  CMP_ANALOG_GAIN
*  
*  74    4/08/98 1:13p Charlie
*  Added Imax vars.
*  
*  73    4/01/98 1:55p Dan
*  inserted 'CMP_SPECIAL_VENTURE_ALLIANCE' for Special SetParam
*  
*  72    3/26/98 2:50p Terry
*  Add CMP_AMP and AMP_LOWNOISE & AMP_HIGHCAP enums
*  
*  71    3/22/98 4:11p Charlie
*  New Imax vars added.
*  
*  70    2/18/98 1:03p Charlie
*  Added CMP_COOL_TYPE.
*  
*  69    2/17/98 1:04p Bob
*  Added BOF Stuff for Visitron..
*  
*  68    2/11/98 9:28a Baker
*  I screwed up the commenton last check-in.
*  
*  67    2/11/98 9:12a Baker
*  Added enum CMP_AUTOCLEAN_FLAG, Flag to set or skip the
*  continuous cleaning
*  
*  66    2/02/98 3:13p Charlie
*  Added hooks to physical port and SCC object. Also added numbers every
*  25 values.
*  
*  65    2/02/98 9:53a Bob
*  Added way to group frames per interrupt through the controller...
*  
*  64    1/06/98 4:38p Terry
*  Add  CMP_EXPSETUPSTATUS
*  
*  62    11/13/97 10:56a Bob
*  Added Stuff for DT3152 Environment Dialog
*  
*  61    10/22/97 12:56p Bob
*  Added CMP_USE_MANUAL_IP for manual intrapixel pattern loading
*  
*  60    9/22/97 10:08a Charlie
*  added CMP_LUT_BANK for 5Mhz ST133
*  
*  59    9/12/97 4:07p Charlie
*  ADDED CMP_BANK_ADD FOR SETTING DC131 BANK.
*  
*  58    8/26/97 4:53p Dan
*  added conditionals for the MIDL compiler to skip enums
*      currently not supported in the Visual Basic Interface(VBI)
*  
*  57    8/18/97 6:12p Charlie
*  added CMP_CURRENT_READOUT_MODE to return to user frame transfer or full
*  frame.
*  
*  56    8/12/97 11:15a Charlie
*  Added custom shutter and ADC offset.
*  
*  55    6/04/97 3:40p Bob
*  Added CMP_ECPDMA_CHANNEL for ECP Port
*  
*  54    6/03/97 12:29p Bob
*  Added CMP_DRIVERVERSION, CMP_NUMDEVICES, and CMP_DMA_BUFFER
*  
*  53    6/02/97 1:16p Bob
*  Added stuff for absorbance, CMP_ABSORBANCE_xxx and Get and Set
*  absorbfilename.
*  
*  52    5/08/97 10:30a Bob
*  Added CMP_AorB_GROUP for the Viccd group setting.
*  
*  51    5/07/97 10:21a Charlie
*  Added diag variables.
*  
*  50    5/05/97 5:05p Terry
*  Add CMP_SW_DIAG
*  
*  49    4/25/97 1:11p Charlie
*  Added CMP_DELAY_TIME (for delay ability in async. mode) and
*  CMP_READOUT_TIME (for enable the readout time dialog).
*  
*  48    4/23/97 11:51a Charlie
*  Added ret source comp for ST130.
*  
*  47    4/18/97 3:22p Bob
*  Added White and Black Clamp Levels for Frame Grabber.
*  
*  46    4/11/97 12:15p Dan
*  added CMP_5X_GAIN_ENABLE (ST133's  X5 Gain)
*  
*  45    3/28/97 4:12p Charlie
*  Added INIT_HW_ACCUM to initialize the hardware accum on the ST138.
*  
*  44    3/26/97 1:15p Dan
*  added CMP_'s for Interline CCD Focusing parameters
*  
*  
*  43    3/25/97 1:59p Dan
*  implementing 'CMP_GATING_MODE'
*  
*  42    3/16/97 8:08p Charlie
*  Added CMP_VERIFY_GOOD_VALUES for setparam to test params and if bad try
*  to correct.
*  
*  41    3/12/97 10:24p Charlie
*  Added CMP_TIMEOUT, CMP_TIMEOUT_DEFAULT, CMP_USE_INTERUPTS, and
*  CMP_DATA_ACQ_STATE.
*  
*  40    3/11/97 5:21p Dan
*  added 'CMP_FOCUS_FAN'
*  
*  39    3/11/97 3:47p Dan
*  added 'CMP_FOCUS_TYPE' & 'CMP_FOCUS_ZOOM'
*  
*  38    3/07/97 12:37p Dan
*  renamed the Interline CMDs
*  
*  37    3/04/97 3:29p Charlie
*   added IsAvail define for if the controller is hooked up to the
*  computer and talking. CMP_CONTROLLER_ALIVE.
*  
*  36    3/01/97 11:17p Charlie
*  Added intensity/offset check for ST133 dialog.
*  
*  35    2/24/97 5:53p Maynard
*  Add CMP_HW_AUTOSTOP enum for IsAvail
*  
*  34    2/24/97 4:02p Bob
*  Added CMP_TIMEOUT to the list
*  
*  33    2/24/97 3:57p Charlie
*  Added IsAvail for sync/Async  and focus/nframe.
*  
*  32    2/20/97 9:24p Charlie
*  Got rid of unique _set and _get for IsAvail function.
*  
*  31    2/20/97 1:08p Bob
*  Added SR stuff
*  
*  30    2/18/97 12:57p Bob
*  Save And Restore Functions Added For TVR
*  
*  29    2/17/97 10:45a Bob
*  
*  28    2/13/97 7:16p Charlie
*  Added error code enum for save and restore functions, also added ids
*  for time unit params.
*  
*  27    2/13/97 7:11a Bob
*  Yet another CMP_ Value
*  
*  26    2/12/97 12:25p Bob
*  Add Gate Vs CW mode
*  
*  25    2/11/97 9:09p Charlie
*  More IsAvail bug fixes.
*  
*  24    2/11/97 3:47p Dan
*  re-order CM_CMD enum to stay compatible with WinX V1.6
*  
*  23    2/10/97 11:25a Charlie
*  Added CurrentValue and RdWrType to VALID_RANGE structure.
*  
*  22    2/07/97 3:14p Bob
*  
*  21    2/05/97 4:03p Charlie
*  Added CMP_GET_CONTROLER_VER that returns true if the controller version
*  can be read from the controller.
*  
*  20    2/05/97 1:07p Bob
*  Bunch of enums specific to viccd and control box..
*  
*  19    2/04/97 6:50a Dan
*  added 'CMP_CONTROLLER_NAME' & 'CMP_CCD_CHIP_NAME'  enums
*  
*  18    1/30/97 9:58p Charlie
*  took out some duplication of names.
*  
*  17    1/30/97 11:36a Charlie
*  Added CMP_VTCLK & CMP_HZCLK.
*  
*  16    1/29/97 2:04p Terry
*  Delete CM_BNC_CHANGE define; Add #ifdef for the header
*  
*  15    1/28/97 3:50p Charlie
*  More IsAvail and GetEnumParam additions.
*  
*  14    1/27/97 9:15p Charlie
*  More IsAvail fixes.
*  
*  13    1/24/97 8:15p Charlie
*  More IsAvail items.
*  
*  12    1/24/97 2:37p Dan
*  implemented V1.6.2 mods
*  
*  
*        1/07/97 8:36a Dan
*  add to CM_CMD enum, Special Collection Shutter Modes
*  
*  11    1/20/97 8:03p Charlie
*  Added isavail defines.
*  
*  10    1/20/97 9:51a Charlie
*  Added new functions isavail, and support functions to determine what is
*  supported by a certain hardware.
*  
*  9     1/16/97 8:04a Bob
*  Added event handle to pidc.h , and pivardef.h
*  
*  8     11/01/96 8:31a Bob
*  CMP_DISABLE_LASER moved up from 1.6
*  
*  7     8/14/96 6:40a Dan
*  fixed a lack of a comma in an enum list
*  
*  6     8/09/96 7:52p Charlie
*  Added new params for v5 pentamaxs.
*  
*  5     7/31/96 6:07p Charlie
*  Added custom chip enums for speed and size. 
*  
*  4     7/18/96 6:05p Charlie
*  Added CMP_FORCE_AUTOSTOP for ST133 to force autostop while it is
*  running.
*  Added CMP_NOP_ADC for both ST133 and ST138 so that nop can be done
*  manually.
*  Added CMP_ACTUAL_TEMP for st133 to get actual temperature from the
*  ST133.
*  
*  3     7/18/96 2:02p Dan
*  
*  2     7/11/96 9:35p Charlie
*  Added scsi vars.
*  
*  1     6/14/96 11:43a Charlie
*  Set param enums.
*  
*
*
*
******************************************************************
*/

#ifndef PIVARDEF_H
#define PIVARDEF_H  1


/*
******************************************************************************
        include files
*/

/*
******************************************************************************
        defines
*/


/* ########################################################### */
/*                  LEVEL 3 DLLs  PI variables.                */
/* ########################################################### */


#if !defined(__midl)    /* skip on MIDL compilier */

/* SetParam / GetParam stuff --- */
enum CM_CAPS {
    CMC_CANIDDETECT = 1,
    CMC_LCIPULSER
    };

enum CM_STRINGS {
    CMS_CLASSNAME,     /* name of controller object     */
    CMS_FLATFLDNAME,   /* flat field data file name     */
    CMS_DARKNAME,      /* background data file name     */
    CMS_SETUPNAME,     /* setup file name               */
    CMS_ACCESSNAME,    /* pixel access filename         */
    CMS_DATFILENAME,   /* data file name                */
    CMS_YTNAME,        /* YT / cross-section file name  */
    CMS_DEVNAME        /* (IEEE) device name            */
    };

#endif      /* !__midl */


enum CM_ERR {
   CM_ERR_BADCMD=0,    /* no such command                                   */
   CM_ERR_NONE,        /* status = OK                                       */
   CM_ERR_BADPARAM,    /* bad value for this command, if possible           */
               /* nearest legal value will be used.                         */
   CM_ERR_READONLY     /* Variable is read only.                            */
   };

enum CM_CMD {
  CMP_NOCMD = 0,         /* place holder                                   */
  CMP_ETACTUAL,          /* expose time set                                */
  CMP_SEQUENTS,          /* sequentials set                                */
  CMP_ERROR,             /* error status                                   */
  CMP_GETCAPS,           /* get controller/detector capability             */
  CMP_GETPLSR,           /* get controller's pulser type if any            */
  CMP_PULSERIMODE,       /* pulser intensifier mode                        */
  CMP_PULSEWIDTH,        /* pulser pulse width                             */
  CMP_PULSEDELAY,        /* pulser start delay                             */
  CMP_PULSEDELINC,       /* pulser delay increment                         */
  CMP_PULSERTSRC,  /*10*//* pulser trigger source                          */
  CMP_PULSETCOUNT,       /* pulser trigger count                           */
  CMP_PULSERBEEP,        /* pulser beeper on/off                           */
  CMP_MEM_ADDRESS,       /* Sets mem add for scan code (DC131 & ST133)     */
  CMP_MEM_PAGE,          /* Sets mem page (DC131 & ST133)                  */
  CMP_INIT_FLAG,         /* Controller initilized bit (ST133).             */
  CMP_DETECTOR_BIT,      /* Detector setting in hardware (ST133).          */
  CMP_PHOTON_MAXTIME,    /* Photon Estimation - Max Total Time     (ST138) */
  CMP_PHOTON_MAXTIMEUNIT,/* Photon Estimation - Max Total TimeUnit (ST138) */
  CMP_PHOTON_OFFSET,     /* Photon Estimation - Offset             (ST138) */
  CMP_PHOTON_RMS_NOISE, /* 20 */ /* Photon Estimation - RMS read-noise     (ST138) */
  CMP_PHOTON_ICCD_GAIN,  /* Photon Estimation - ICCD Gain          (ST138) */
  CMP_PHOTON_MAX_PHOTONS,/* Photon Estimation - Max # Photons      (ST138) */
  CMP_RUNNING_APP,       /* Application Being Run By Controller Object     */
  CMP_VIDEO_TYPE,        /* Video type NTSC, Pal or Custom. (DC131&ST133)  */
  CMP_CUSTOM_VIDEO_X,    /* custom video x dimension.                      */
  CMP_CUSTOM_VIDEO_Y,    /* custom video y dimension.                      */
  CMP_CUSTOM_VIDEO_FSTWIDTH, /* custom fast video x dimension.             */
  CMP_CUSTOM_VIDEO_LSTWIDTH, /* custom fast video y dimension.             */
  /* The following two VIDEO_XDIM and YDIM are gets only, they are set     */
  /* when a Video type is selected. They are information only.             */
  CMP_VIDEO_XDIM,         /* X dimension of video.                         */
  CMP_VIDEO_YDIM,    /* 30 */     /* Y dimension of video.                 */
  /*  the following interfaces with 'ValidFocusConditions' function        */
  /*  these are get only commands                                          */
  CMP_VIDEO_MAX_ZOOM,     /* max zoom allowed for selected chip            */
  CMP_VIDEO_HORZ_PAN,     /* true if zoom panning enabled for horz         */
  CMP_VIDEO_VERT_PAN,     /* true if zoom panning enabled for vert         */
  CMP_WORD_MULTIPLIER,    /* Factor for Doing Small ROI's With PCI         */
  CMP_TARGET_ID,          /* Set/Get SCSI Target ID. (LONG)                */
  CMP_ADAPTER_ID,         /* Set/Get SCSI Adapter ID. (LONG)               */
  CMP_NUMADAPTORS,        /* Get number of SCSI adapters. (LONG)           */
  CMP_FORCE_PP_INIT,      /* Force an init in physical port.               */
  CMP_NOP_ADC,            /* var. to slow up Transfer speed. Set/Get (long)*/
  CMP_ACTUAL_TEMP,   /* 40 */  /* Detector actual temperture (ST133). Get only  */
  CMP_FORCE_AUTOSTOP,     /* for ST133 force the autostop, for live DC value is a double.                            */
  CMP_DEFAULT_VTCLK,      /* LONG default vertical clock.                  */
  CMP_MIN_VTCLK,          /* DOUBLE min value of vertical clock.           */
  CMP_MAX_VTCLK,          /* DOUBLE max value of vertical clock.           */
  CMP_DEFAULT_HTCLK,      /* LONG default horizontal clock.                */
  CMP_MIN_HTCLK,          /* DOUBLE min value of horizontal clock.         */
  CMP_MAX_HTCLK,          /* DOUBLE max value of horizontal clock.         */
  CMP_TIMING_STYLE,       /* LONG either Thomson or EEV.                   */
  CMP_HEADSELECT,         /* LONG Head Select setting.                     */
  CMP_HORZPHASE,  /*50*/  /* LONG horizontal phase.                        */
  CMP_VERTPHASE,          /* LONG vertical phase.                          */
  CMP_SPECIAL_SPEED,      /* LONG special speed setting for st138.         */
  CMP_PRE_STRIPS,         /* LONG pre (dummies) strips.                    */
  CMP_POST_STRIPS,        /* LONG post (dummies) strips.                   */
  CMP_PRE_LINES,          /* LONG pre (dummies) lines.                     */
  CMP_POST_LINES,         /* LONG post (dummies) lines.                    */
  CMP_ACTIVE_LINES,       /* LONG avtive lines.                            */
  CMP_ACTIVE_STRIPS,      /* LONG actvie strips.                           */
  CMP_XFER_EXTRA,         /* LONG frame transfer extra dummies in middle.  */
  CMP_MIN_BLOCK,   /* 60 */       /* LONG minimum block for skips.         */
  CMP_NUM_MIN_BLOCK,      /* LONG number of min blocks to skip.            */
  CMP_CELL_X_SIZE,        /* DOUBLE x dimension of pixel.                  */
  CMP_CELL_Y_SIZE,        /* DOUBLE y dimension of pixel.                  */
  CMP_X_GAP_SIZE,         /* DOUBLE x gap between pixels.                  */
  CMP_Y_GAP_SIZE,         /* DOUBLE y gap between pixels.                  */
  CMP_LOGIC_OUTPUT,       /* LONG for PentaMax >= V5 BNC output            */
  CMP_VIDEO_BLANK,        /* LONG for PentaMax >= V5 video blanking on/off */
  CMP_ZOOM_MODE_VIDEO,    /* LONG for PentaMax >= V5, zoom by 2 test.      */
  CMP_LEVEL_SYNC,         /* LONG for PentaMax >= V5, level synchronization*/
  CMP_DISABLE_LASER,   /* 70 */   /* LONG for MicroMax special.            */
  CMP_ACQBACK_SHUTTER,    /* Acquire Background Shutter Mode               */
  CMP_ACQFLAT_SHUTTER,    /* Acquire Flat Field Shutter Mode               */
  CMP_SMALL_CCD_MINEXP,   /* Interline CCD PID_582x782   min exposure      */
  CMP_LARGE_CCD_MINEXP,   /* Interline CCD PID_1030x1300 min exposure      */
  CMP_GATING_MODE,  /*75*//* Interline CCD Gating Mode Enable              */
  CMP_ILME_B1X,           /* Interline Focusing Min Exp - X1 Binning       */
  CMP_ILME_B2X,           /* Interline Focusing Min Exp - X2 Binning       */
  CMP_ILME_D1X,           /* Interline Focusing Min Exp - X1 Decimation    */
  CMP_ILME_D2X,           /* Interline Focusing Min Exp - X2 Decimation    */
  CMP_ILME_D4X,        /* 80 */   /* Interline Focusing Min Exp - X4 Decimation    */
  CMP_INIT_HW_ACCUM,      /* Initialize hardware accum (st138).         81 */
  CMP_5X_GAIN_ENABLE,     /* Enable 5X Gain on ST133s                   82 */
  CMP_RET_SRCCMP,         /* st130 only, return source comp with data.  83 */
  /***************************************************/
  /*  any enums from WinX/16 must be inserted above  */
  /***************************************************/
  CMP_EVENT_HANDLE,       /* HANDLE for an EVENT                           */
  CMP_READOUT_MODE,       /* IsAvail readout mode.                         */
  CMP_SHUTTER_TYPE,       /* IsAvail Shutter type.                         */
  CMP_USER_DEFINED_CHIP,  /* IsAvail user defined chip.                    */
  CMP_USER_DEFINED_TIMING,/* IsAvail user defined timing.                  */
  CMP_CONTROLLER_VERSION, /* IsAvail controller version is writable.       */
  CMP_GET_CONTROLLER_VER, /* 90 *//* IsAvail if controller ver is readable.*/
  CMP_TTL_LINES,          /* IsAvail TTL control lines (in and out).       */
  CMP_BIT_ADJUST,         /* IsAvail Bit adjust                            */
  CMP_RESOLUTION,         /* IsAvail bit resolution                        */
  CMP_GAIN,               /* IsAvail ADC gain.                             */
  CMP_ADC_RATE,           /* IsAvail can AEC Rate be retrieved.            */
  CMP_ADC_TYPE,           /* IsAvail can you pick an ADC.                  */
  CMP_NUMBER_OF_CLEANS,   /* IsAvail number of cleans.                     */
  CMP_NUM_OF_STRIPS_PER_CLN, /* IsAvail number of strips per clean.        */
  CMP_INTERFACE_CARD,     /* IsAvail interface card.                       */
  CMP_INTERRUPT,  /*100*/ /* IsAvail Can you get what the interrupt is.    */
  CMP_IO_ADDRESS1,        /* IsAvail Can the IO address be read/write.     */
  CMP_IO_ADDRESS2,        /* IsAvail Can the IO address be read/write.     */
  CMP_IO_ADDRESS3,        /* IsAvail Can the IO address be read/write.     */
  CMP_HW_ROI,             /* IsAvail Can an ROI be set by hardware.        */
  CMP_HW_BINNING,         /* IsAvail can hw binning be done.               */
  CMP_EDGE_TRIGGER,       /* IsAvail can you set the edge of trigger.      */
  CMP_SHUTTER_CONTROL,    /* IsAvail Shuter control (open/closed/etc.).    */
  CMP_RS170,              /* IsAvail is Rs170 available?                   */
  CMP_RS170_COMPLEX,      /* IsAvail is complex (panning/zooming) Rs170 avail */
  CMP_HW_RS170_LUT,    /* 110 */   /* IsAvail is there a hardware Lut for RS170.    */
  CMP_RS170_INTENSITY_SCALING, /* IsAvail intensity scaling for RS170.     */
  CMP_RS170_OFFSET,       /* IsAvail Offset for RS170.                     */
  CMP_RS170_PAN,          /* IsAvail panning ability in RS170.             */
  CMP_RS170_ZOOM2X,       /* IsAvail zoom 2x. depends on controller & chip */
  CMP_RS170_ZOOM4X,       /* IsAvail zoom 4x. depends on controller & chip */
  CMP_RS170_BINNING,      /* IsAvail binning depends on controller & zoom. */
  CMP_RS170_DECIMATION,   /* IsAvail decimation depends on controller & zoom */
  CMP_HW_ACCUM,           /* IsAvail hardware accumulation.                */
  CMP_SHT_PREOPEN,        /* IsAvail Shutter preopen (1) or normal (0).    */
  CMP_STORE_STROBE,    /* 120 */   /* IsAvail Store strobe, timing mode.   */
  CMP_CONT_CLNS,          /* IsAvail continous cleans                      */
  CMP_TIMING_MODE,        /* IsAvail timing mode.(freerun, ext-sync, line-sync). */
  CMP_EXT_TRIGGER,        /* IsAvail external trigger enable.              */
  CMP_EVENT_COUNTER,      /* IsAvail event counter for ST121.              */
  CMP_SW_TRIGGER,  /*125*//* IsAvail software trigger                      */
  CMP_KINETICS_WINDOWSIZE,/* IsAvail kinetics windows size settings.       */
  CMP_EXPOSURE,           /* IsAvail exposure and range.                   */
  CMP_CONTROLLER_NAME,    /* Controller Name                               */
  CMP_CCD_CHIP_NAME,      /* CCD Chip Name                                 */
  CMP_EDGEENHANCE,    /* 130 */    /* Control Box Parameter                */
  CMP_BOXVIDEOGAIN,       /* Control Box Parameter                         */
  CMP_HSHADING_VALUE,     /* Control Box Parameter                         */
  CMP_VSHADING_VALUE,     /* Control Box Parameter                         */
  CMP_EDGEENHANCE_FLAG,   /* Control Box Parameter                         */
  CMP_SHADING_FLAG,       /* Control Box Parameter                         */
  CMP_GRAYSCALE,          /* Control Box Parameter                         */
  CMP_OFFSET,             /* Control Box Parameter                         */
  CMP_CCDGAIN,            /* Control Box Parameter                         */
  CMP_TEMPERATURE,        /* Controller Temperature                        */
  CMP_MCPVOLTAGE,       /* 140 */  /* Control Box Parameter                */
  CMP_BOXEXPOSURE,        /* Control Box Parameter                         */
  CMP_ABC_FLAG,           /* Control Box Parameter                         */
  CMP_GAMMA_FLAG,         /* Control Box Parameter                         */
  CMP_AUTOBLACK_FLAG,     /* Control Box Parameter                         */
  CMP_AGC_FLAG,           /* Control Box Parameter                         */
  CMP_ODD_FIELD,          /* Control Box Parameter                         */
  CMP_FIELD_SELECT,       /* Control Box Parameter                         */
  CMP_RESET,              /* Control Box Parameter                         */
  CMP_EXTERN_ENABLE,      /* Control Box Parameter                         */
  CMP_CONTROLLERS_SUPPORTED, /*150*/ /* controllers supported.             */
  CMP_VTCLK,              /* LONG Vertical Clock.                          */
  CMP_HTCLK,              /* LONG Horizontoal Clock.                       */
  CMP_GATE_VS_CW,         /* Viccd Mode                                    */
  CMP_COM_PORT,
  CMP_TIME_UNITS,         /* Returns valid time units for controller.      */
  CMP_US_UNITS,           /* IsAvail good defaults for exp if in micro sec.*/
  CMP_MS_UNITS,           /* IsAvail good defaults for exp if in milli sec.*/
  CMP_SEC_UNITS,          /* IsAvail good defaults for exp if in sec.      */
  CMP_MIN_UNITS,          /* IsAvail good defaults for exposure if in min. */
  CMP_HRS_UNITS,        /* 160 */  /* IsAvail good defaults for exposure if in hrs. */
  CMP_FRAME_UNITS,        /* Only the Viccd & ControlBox Support this unit */
  CMP_SYNC_ASYNC,         /* Is the controller able to do sync and/or async*/
  CMP_FOCUS_NFRAME,       /* Does the controller support focus &/or nframe.*/
  CMP_TIMEOUT,            /* Time Out For Run Sequencer (Viccd) Mainly     */
  CMP_TIMEOUT_DEFAULT,    /* Time Out for holding old Run Seq timeout.     */
  CMP_HW_AUTOSTOP,        /* IsAvail for hardware autostop capability      */
  CMP_RS170_INTEN_OFFSET, /* Use Intensity/offset allowed.                 */
  CMP_CONTROLLER_ALIVE,   /* Is the controller alvie? This command will try*/
                          /* to read from the controller to determine it is*/
                          /* up and running, if True is returned as param, */
                          /* then controller is hooked up, if false is ret.*/
                          /* then controller is not hooked up, if the fcn. */
                          /* return False then this command is not supported*/
                          /* by the controller.                            */
  CMP_FOCUS_TYPE,         /* Focusing - Binning or Decimation              */
  CMP_FOCUS_ZOOM,       /* 170 */  /* Focusing - X1, X2 or X4              */
  CMP_FOCUS_PAN,          /* Focusing - pan position                       */
  CMP_MULTI_TAP_ROI,      /* Isavail for multi-tap ROI dialog available.   */
  CMP_USE_INTERUPTS,      /* IsAvail for if data collection should use eof */
  CMP_DATA_ACQ_STATE,     /* Holds Data Acquistion state.(run sequencer)   */
  CMP_VERIFY_GOOD_VALUES,/*175*/ /* SetParam, checks that good values being used*/
  CMP_WHITE_CLAMP,        /* Frame Grabber White Clamping Level            */
  CMP_BLACK_CLAMP,        /* Frame Grabber Black Clamping Level            */
  CMP_DELAY_TIME,         /* Delay between aquistions.                     */
  CMP_READOUT_TIME,       /* Readout time of experiment.                   */
  CMP_SW_DIAG,          /* 180 */  /* Flag for SW Diagnostics. Set by DLL  */
  CMP_DIAG1,              /* Set paramater for diagnostics and testing.    */
  CMP_DIAG2,              /* Set paramater for diagnostics and testing.    */
  CMP_DIAG3,              /* Set paramater for diagnostics and testing.    */
  CMP_DIAG4,              /* Set paramater for diagnostics and testing.    */
  CMP_DIAG5,              /* Set paramater for diagnostics and testing.    */
  CMP_AorB_GROUP,         /* Viccd Group Selected                          */
  CMP_ABSORBANCE_FLAG,    /* Absorbance Flag                               */
  CMP_ABSORBANCE_METHOD,  /* Current Method of which to do absorbtion      */
  CMP_ABSORBANCE_STRIPNUM,/* If stripmode Absorb than this is current strip*/
  CMP_DMASIZE_VIA_DRIVER, /* 190 *//* Amount of Memory Actually Allocated Via Driver*/
  CMP_DRIVERVERSION,      /* Version of the Driver                         */
  CMP_NUM_DEVICES,        /* PCI - Number Cards Found                      */
  CMP_ECPDMA_CHANNEL,     /* DMA Channel for ECP 0 - 3                     */
  CMP_CUSTOM_SHUTTER,     /* Custom shutter time                           */
  CMP_ADC_OFFSET,         /* ADC offset for head.                          */
  CMP_CURRENT_READOUT_MODE, /* The Current Readout mode                    */
  CMP_BANK_ADD,           /* SETS BANK TO USE FOR SCAN PATTERNS.           */
  CMP_LUT_BANK,           /* Lut bank to use (ST133).                      */

  CMP_USE_MANUAL_IP,      /* Use the manually programmed intrapixel        */
  CMP_DT3152_DRIVER_DMA,  /*200*//* DMA Buffer for the DT3152              */
  CMP_EXPSETUPSTATUS,     /* ExpSetupStatus Bits                           */
  CMP_GET_SCC,            /* Get SCC object for EE testing.                */
  CMP_GET_PHYPORT,        /* Get physical port of controller for ee testing*/
  CMP_NUMBERFRAMES_IRQ,   /* Packing for 1000 frames/per/sec               */
  CMP_AUTOCLEAN_FLAG,     /* Flag to set or skip the continuous cleaning   */
  CMP_BOF_BASEADDRESS,    /* Visitron's Base Address IO Card               */
  CMP_BOF_ODD_LSB,        /* Visitron's Odd Lsb for IO Card                */
  CMP_BOF_ODD_MSB,        /* Visitron's Odd Msb for IO Card                */
  CMP_BOF_EVEN_LSB,       /* Visitron's Even Lsb for IO Card               */
  CMP_BOF_EVEN_MSB,       /* 210 *//* Visitron's Even Msb for IO Card      */
  CMP_BOF_STATUS,         /* Visitron's Bof status                         */
  CMP_BOF_DOWNLOAD,       /* Causes Above Bof Params to be sent to driver  */
  CMP_SPECIAL_VENTURE_ALLIANCE,  /* Special Multiple SetParams             */
  CMP_COOL_TYPE,          /* cooling type LN_COOLED (1) or TE_COOLED (2)   */
  CMP_HD_TYPE,            /* status if there is an head on system.         */
  CMP_INTENSIFER_GAIN,    /* IMax intensifier gain.                        */
  CMP_SHT_GATE_MODE,      /* IMax mode, gate, shutter, safe.               */
  CMP_HD_CHECK,           /* Is the head (i.e. Imax, ingas, nbyte, etc.) talking? */
  CMP_AMP_MODE,           /* Amplifier Mode (Low Noise or High Capacity)   */
  CMP_ANALOG_GAIN,      /* 220 *//* pre-amp analog gain.                   */
  CMP_HW_FIXES,           /* bit settings for temp hw problems.            */
  CMP_PCI_CARDS,          /* Access to number of PCI cards through isavail */
  CMP_NOT_REVERSE,        /* Do opposite of reverse flag, needed for IMax. */
  CMP_MPP,                /* Set to 1 if MPP device otherwise 0 non-MPP.   */
  CMP_VCLK_OVERLAP_PHZ,   /* 225 *//* Vertical clocks overlap phases.      */
  CMP_ILLUMINATION,       /* Front Illumination is 1, back is 0.           */
  CMP_VERT_DIR,           /* Vertical direction 1 is normal, 0 is reveresed*/
  CMP_HORZ_DIR,           /* Horizontal direction, 0-nml, 1-rev, 2-split   */
  CMP_REV_IMAGE_SHIFT,    /* Reverse Image Shift 1 - Active, 0 - Inactive. */
  CMP_NTPCI_TIMERFLAG,  /* 230 */  /* Whether or not the NT Timer is engaged */
  CMP_SPECIAL_DAC0,       /* Special one of a kind Dac write (Chad)        */
  CMP_SPECIAL_DAC1,       /* Special one of a kind Dac write (Chad)        */
  CMP_FAST_PULSE_ENABLE,  /* Imax fast pulse option board enable.          */
  CMP_LOAD_NVRAM_DEFAULTS,/* Load Nvram and set as defaults.               */
  CMP_CNTR_BRD,           /* control board value.                          */
  CMP_GET_BRD_HD_NVRAM,   /* get nvram checks (head, control brd, hw fixes.*/
  CMP_XDIM,               /* X dimension of data coming back to computer.  */
  CMP_YDIM,               /* Y dimension of data coming back to computer.  */
  CMP_XY_GROUPING,        /* If Binning Must Be Even                       */
  CMP_MESSAGES_FLAG,    /* 240 */  /* 1-MessageBoxes On 0-MessageBoxes Off */
  CMP_REORG_FLAG,         /* Data Reorganize 1-On 0-Off                    */
  CMP_RD_PULSER_BRD,      /* Read Pulser board status register EPLD.       */
  CMP_RD_HV_BRD,          /* Read High Voltage board status register EPLD. */
  CMP_PULSER_RESET,       /* Reset for pulser board, 1 for reset, else 0   */
  CMP_CALIN,              /* Calibration LEDs for the ST143.               */
  CMP_FAST_CLOCK,         /* Use fast clock for ST133 and 5Mhz ST133.      */
  CMP_AMP_DIALOG,         /* set if amp dialog is valid for detector.      */
  CMP_TESTFIX_RAMP,       /* used for test fixture ramp setting.           */
  CMP_TESTFIX_DAC_INC,    /* used for test fixture dac increments.        */
  CMP_TESTFIX_18OR16,     /*250*//* set 18-bit dac or 16-bit dac on test fixture  */
  CMP_TESTFIX_OFFSET,     /* used for test fixture to set offset.          */
  CMP_TESTFIX_H_PHASES,   /* used for test fixture to set h phases         */
  CMP_TTL_LINE_TO_WAIT,   /* TTL line to wait for for "CMP_SW_TRIGGER"     */
  CMP_SPECIAL_FAST_RDOUT, /* Isavail for special high speed (FT only)      */
  CMP_SPCL_FAST_Y_DIM,    /* y dimensions allowed for Fast mode.           */
  CMP_SPCL_FAST_X_DIM,    /* x dimension 1 to chip size.                   */
  CMP_SPCL_FAST_Y_INDEX,  /* special fast index.                           */
  CMP_DATA_COLLECTION_MODE,/* Set to auto, manual, zoom, or highspeed.     */
  CMP_AUTO_FRAMES_IRQ,    /* Let software take best guess.                 */
  CMP_EXP_REPEAT,       /* 260 */  /* Repeat whole experiment (WinX only). */
  CMP_EXP_ACCUM,          /* Accumulates whole expriments.                 */
  CMP_DATA_COLLECTION_TYPE,/* NFRAME, FOCUS, ETC.                          */
  CMP_PREAMP_HEAD,        /* Generic read/write to preamp in head.         */
  CMP_I2C_HEAD_ADD,       /* Address to write to on i2c.                   */
  CMP_I2C_HEAD_VAL,       /* Generic read/write to i2c in head.            */
  CMP_SHUTTER_COMP_TIME_MS,/* Get actual shutter compnesation time in ms.  */
  CMP_NVRAM_AVAIL,         /* does hardware support nvram (may not be prog.)*/
  CMP_RESET_INTERFACE,     /* Rreset the interface board for st143 contrllr */
  CMP_NUMBER_AGAIN_AVAIL,  /* number of analog gains available in head.     */
  CMP_SENSOR_TYPE,      /* 270 */   /* Set CCD/PDA sensor type.             */
  CMP_BOARD_SET,           /* many used Iccd-Max systems, brd set in head   */
  CMP_NVRAM_PROGRAM,       /* flag for nvram program to allow programming   */
  CMP_FORCE_NVRAM_FLAG,    /* When loading nvram values, if this is set over ride previous settings.                       */
  CMP_SKIPFRAMES,          /* number of frames to skip at start, just holderframes are skipped in application.*/
  CMP_OLD_ENDOFLIST,       /*275 Insert !!!after!!! this item               */
  CMP_CLR_INT_CNTR,        /* clear interupt frame counter.                 */
  CMP_ENABLE_INT_CNTR,     /* enable interrupt frame couning.               */
  CMP_INT_CNTR,            /* Get interrupt frame counter.                  */
  CMP_INTERNAL_SYNC_SRC,   /* 0=Normal Ext Sync, 1=Use Internal Bus Sync. Used with PTG */
  CMP_SW_EXTSYNC,       /* 280 */   /* Software External Sync               */
  CMP_PTG_PRESENT,         /* T = PTG Exists, F = Not                       */
  CMP_ELEC_SHT,            /* Electronic shutter available (1), not avail (0) */
  CMP_BOARDS_WITH_NVRAM,   /* Boards available which MAY have NVRAM         */
  CMP_ANLGMASTER_ST143,		/* Address of the analog board 1                */
  CMP_ANLGSLAVE_ST143,		/* Address of the analog board 2                */	
  CMP_DISPLAY_ST143,		/* Address of the dispaly board                 */
  CMP_INTRFACE_ST143,		/* Address of the interface board               */
  CMP_SCANCONTROL_ST143,	/* Address of the scan control board            */
  CMP_USERDMA_FLAG,			
  CMP_USERDMA_ADDRESS,  /* 290 */
  CMP_USERDMA_SIZE,
  CMP_EVENT_TYPE,			/* Event Style Bof/Eof etc...					*/
  CMP_ANTI_BLOOMING,        /* Anti-blooming (currently only Thm 5Mhz).     */
  CMP_PE,                   /* 5Mhz ST133 , Fast reset Pulse Enable.        */
  CMP_POWERDOWN_DETECT,     /* ST133 only force the power down detect bit.  */
  CMP_USE_HEADCALIB,        /* Use Calibration Info from the Head NVRAM     */
  CMP_BSWBINNING,           /* (bool) Software binning flag, place holder for app */
  CMP_DEMO_PATTERN,         /* specify the demo pattern */
  CMP_CIRC_BUFFER,          /* IsAvail for if we can do circular buffer.    */
  CMP_CONT_CLNS_INST,       /* 300 */ /* Use Continous Cleans Instruction. Not  */
                            /* available on all controllers and versions.       */
  CMP_TEMP_STATUS,          /* Temperature locked (1) or unlocked (0)           */
  CMP_MULTIPLE_READMODES_LIVE, /*More than one readout mode during acqs         */
  CMP_FIRST_ACQUIRE_FLAG,   /* Clears readout cross over problem with online exp*/
  CMP_ANTI_BLOOMING_CONTROL,/* Level of anti blooming to use.               */
  CMP_PRE_HORZ_DELAY,       /* New for some hardware fixes.                 */
  CMP_NVRAM_TRIES,			/* Number of Tries to commit before failing         */
  CMP_XASCEND, 
  CMP_YASCEND,
  CMP_ALT_TIMING,           /* Used by PvCam in WinX only. */
  CMP_SHUTTER_PRE_COMP,   /* 310 */ /* Tucson cameras have a Pre shutter comp time too.*/
  CMP_PVCAM_POSSIBLE,       /* Is the PvCam interface possible in system?      */
  CMP_ADC_IN_NVRAM,         /* Used only for NvRam Standalone, false if ADC    */
                            /* done by resisters, true if ADCs should be stored*/
                            /* in the NvRam.       */
  CMP_PASSTHRU_MODE,		/* Allow Pass Through Writing for systems that can do it */
  CMP_FIRMWAREVERSION,      /* Firmware Version (get only) */
  CMP_IMMEDIATE_SHUTTER,	/* Immediate Shutter Controls... */
  CMP_STAGE2_TEMP,
  CMP_AVGAIN_ENABLED,       /* TRUE to use Avalanche Gain */
  CMP_AVGAIN_SETPOINT,      /* Avalanche Gain set point */
  CMP_AVGAIN,               /* Download Avalanche Gain value */
  CMP_AVGAIN_CALIB_TEMP,   /* 320 */ /* Avalanche Gain Calibration temperature   */
  CMP_AVGAIN_CALIB_COEFF1,  /* Avalanche Gain Calibration Coefficient 1 */
  CMP_AVGAIN_CALIB_COEFF2,  /* Avalanche Gain Calibration Coefficient 2 */
  CMP_AVGAIN_CALIB_COEFF3,  /* Avalanche Gain Calibration Coefficient 3 */
  CMP_AVGAIN_CALIB_COEFF4,  /* Avalanche Gain Calibration Coefficient 4 */
  CMP_AVGAIN_CALIB_COEFF5,  /* Avalanche Gain Calibration Coefficient 5 */
  CMP_FORCE_READOUT_MODE,   /* Force readout mode for CCD 57 and CCD 47 */
  CMP_RESET_DATACOLLECTION, /* Reset the data collection interface, used */
							/* in serial violation problems.			*/
  CMP_ACTIVE_SUBFRAME,      /* one-based index of active subframe        */
                            /* (zero indicates all subframes are active) */

  CMP_VSHIFT_TIME,          /* 329 */ /* vertical shift time in usec */


  /*-------------------------------------BEGIN OF PVCAM------------------------*/
  CMP_PV_FRAME_CAPABLE	= 509,
  CMP_PV_CCS_STATUS		= 510,
  CMP_PV_BIT_DEPTH		= 511,    
  CMP_PV_GAIN_INDEX		= 512,
  CMP_PV_SPDTAB_INDEX	= 513,
  CMP_PV_READOUT_PORT	= 514,
  CMP_PV_SHTR_CLOSE_DELAY= 519,
  CMP_PV_SHTR_OPEN_DELAY= 520,
  CMP_PV_SHTR_OPEN_MODE = 521,
  CMP_PV_CLEAR_MODE		= 523,
  CMP_PV_TEMP_INT		= 525, 
  CMP_PV_TEMP_SET_INT	= 526,
  CMP_PV_DET_HD_SER_NUM = 533,	/* Detector head serial number from NvRam */
  CMP_SKIP_AT_ONCE_BLK  = 536,
  CMP_PV_BOFEVENT       = 537,
  CMP_PV_EOFEVENT       = 538,
  CMP_PV_CONT_CLEARS    = 540,  /* continous cleans for PvCam, can't use Cont_clns */
  CMP_PV_SYSTEM_SER_NUM = 542,	/* Controller/System serial number from NvRam */

  /*-------------------------------------END PVCAM-----------------------------*/

  CMP_END_OF_LIST           /* Insert !!!before!!! this item.                */
};                          /*  SetParam / GetParam stuff --- end            */
                            




                            

#if !defined(__midl)    /* skip on MIDL compilier */

/* Defines for types of applications being run by a controller object */
/* ( Use set/get of CMP_RUNNING_APP for this value )                  */
enum CM_APP_TYPES {
    CMAPP_STANDARD = 1,     /* "Normal" Runs    */
    CMAPP_STEP_AND_GLUE    /* Step & Glue Runs */
    };


enum RDWRTYPE {
  CM_BAD,                   /* something is wrong.                                       */
  CM_READ_ONLY,             /* Value can be read only, not written to.                   */
  CM_READ_N_WRITE,          /* Value can be written to and read from.                    */
  CM_EXIST_CHECK            /* Value is only a "does it exist" check. Not read or Write  */
    };                      /* End RDWRTYPE.                                             */
    
struct VALID_RANGE 
{
   RS_UINT32 NumberOfItems;        /* number of items for id, ie number of valid enum types */
   RS_UINT32 DataType;             /* normal data type of variable.                         */
   double MinValue;             /* minimum value of range.                               */
   double MaxValue;             /* minimum value of range.                               */
   double DefaultValue;         /* default for double value.                             */ 
   double CurrentValue;         /* Current value.                                        */
   double Increment;            /* increment for value, 0 if non-linear or no increment. */
   RS_UINT32 RdWrType;             /* Read/write check. uses enum RDWRTYPE.                 */
}; 

/* error codes for Save and Restore functions. */
enum SaveRestrErr 
{
  RESTR_OK,            /*  Restore worked.                           */
  RESTR_INVALID_STATE, /*  State given to restore doesn't exist.     */
  RESTR_FAILED,        /*  A failure occured during restoring.       */
  RESTR_NOT_SAVED      /*  Restore state was not previously saved.   */
};

/* Save and Restore Groups */
enum Save_N_Restore
{
  RS_CONTROLLER,
  RS_INTERFACE,
  RS_CLEANS,
  RS_ADC,
  RS_EXPOSURE,
  RS_TIMING,
  RS_FOCUS,
  RS_ROI,
  RS_CUSTOM_TIMING,
  RS_CUSTOM_CHIP,
  RS_RATSOS_GARBAGE,
  RS_HEAD_INFORMATION
};

/* for CMP_HW_FIXES var (bit settings) */
#define NUM_OF_HW_FIXES     6

#define IMAX_NO_FIXES     0x0 /* no problem                          */
#define IMAX_CD_BRACKET   0x1 /* some early Imaxs have C&D match A&B */
#define DUAL_FRAME        0x2 /* ST133 Dual frame high speed.        */
#define FAST_GATING       0x4 /* fast gating */
#define FIXED_TEMPERATURE 0x8 /* Fixed Temperature (i.e. InGAs = -50)*/
#define BOEING_SPECIAL    0x10 /* Boeing Special */
#define TITAN_SPECIAL     0x20 /* Titan special: Set Mid gain when Low Gain is selected */

                        /* Imax only                */
enum sht_gating_values  /* for CMP_SHT_GATE_MODE var*/
{
    IMAX_SAFE,          /* head is turned off       */
    IMAX_GATING,        /* gating mode              */
    IMAX_SHUTTER        /* Shutter mode             */
};

                        /* ST133 smart-head and 326 board. */
enum amplifier_values   /* for CMP_AMP_MODE var.    */
{
    AMP_NOTUSED=0,
    AMP_LOWNOISE,
    AMP_HIGHCAP
};


enum hd_check       /* Result of CMP_HD_CHECK                             */
{
    HD_CANT_TALK,   /* system head has no ability to communiate to it.    */
    HD_TALKED_OK,   /* system head is alive and is who we think he is.    */
    HD_TALKED_DIF,  /* system head is alive but isn't who we think he is. */
    HD_NO_TALK      /* system head should be able to talk but isn't.      */
};


enum hd_type        /* For CMP_HD_TYPE */
{
    HD_DUMB,        /* Doesn't talk.                                                    */
    HD_IMAX,        /* head is an Imax head. (needs 326 pre-amp to talk) (st133)        */
    HD_NBYTE,       /* head is an Nbtye style head. (needs 326 pre-amp to talk) (st133) */
    HD_INGAAS,      /* head is InGaAs head (needs 326 pre-amp to talk) (ST133)          */
    HD_5MHZ_SONY,   /* Head is 5Mhz Sony head.                                          */
    HD_SMART_UNKNOWN /* Head is smart but unidentified head.                            */
};
                    /* ST133 smart-head and 326 board. */

#define MAX_HDGAINS 4   /* Revise this if any new gains added below */
enum hd_analog_gain /* CMP_ANALOG_GAIN (IMAX only) */
{
    HD_NOTUSED=0,
    HD_LOW,
    HD_MEDIUM,
    HD_HIGH,
    HD_HIGHER
};

enum hd_mpp         /* CMP_MPP */
{
    MPP_NOTUSED=0,
    NON_MPP_DEVICE, /* Head is not an MPP device. */
    MPP_DEVICE      /* Head is an MPP device.     */
};

                    /* CMP_VCLK_OVERLAP_PHZ. */
enum hd_phz_ol      /* ST133 smart-head and 326 board. */
{
    PHZ_NOTUSED = 0,
    PHZ_OVERLAPPED,     /* Phases overlapped.           */
    PHZ_NON_OVERLAPPED  /* phases not overlapped.       */
};

                        /* CMP_ILLUMINATION.   */
enum hd_illumination    /* ST133 smart-head and 326 board. */
{
    ILL_NOTUSED = 0,
    ILL_FRONT,      /* Front illuminated.           */
    ILL_BACK        /* Back illuminated.            */
};
                
                    /* ST133 smart-head and 326 board. */
enum hd_shift_direction /* CMP_VERT_DIR & CMP_HORZ_DIR */
{
    DIR_NOTUSED = 0,
    DIR_NORMAL,     /* Shift in normal direction horz&vert */
    DIR_REVERSE,    /* Shift in reverse direction horz & vert */
    DIR_SPLIT       /* Shift in two directions horz only.   */
};

            
enum active_setting /* CMP_REV_IMAGE_SHIFT. */
{
   REV_SFT_NOTUSED = 0,
   REV_SFT_INACTIVE,/* no set.                              */
   REV_SFT_ACTIVE   /* Set.                                 */
};

enum anti_blooming /* CMP_ANTI_BLOOMING. */
{
    ANTI_BLOOM_NOTUSED = 0,
    ANTI_BLOOM_INACTIVE,
    ANTI_BLOOM_ACTIVE
};

enum immediate_shutter
{
	IMMEDIATE_OPEN = 0,
	IMMEDIATE_CLOSE
};

/* timing style for ST138s and MicroMax */
/* MUST BE KEPT IN ORDER - EVEN THOUGH "NOT USED" ISN'T FIRST */
enum timing_style   /* CMP_TIMING_STYLE */
{
    TIMING_STYLE_EEV=0,     /* EEV STYLE     */
    TIMING_STYLE_THX,       /* THOMSON STYLE */
    TIMING_STYLE_NOT_USED   /* FOR SETUP OF CONTROL REGISTER W/O TIMING */
};


enum llccd_avalanche_gain
{
  AVALANCHE_NOTUSED = 0,
  AVALANCHE_OFF,      /* Avalanche gain off, i.e., use uni-gain */
  AVALANCHE_ON        /* Avalanche gain on. */
};

/* used for the CCD 57 and CCD 47 to determine which why the chip should */
/* be read out. This is set by the parameter CMP_FORCE_READOUT_MODE      */
enum FourceReadOut {
    ALWAYS_CHECK_EXP,
    MAKE_FULL,
    MAKE_FRAME_TRANSFER,
    MAKE_AUTOMATIC
};


/*  Continuous Cleans Instruction  */
enum CCI_State
{
    CCI_NOTAVAILABLE = 0,
    CCI_AVAILABLE,
    CCI_ENABLED
};


/* cooling types */
#define LN_COOLED       1     /* controller switch is set to LN cooled   */
#define TE_COOLED       2     /*                             TE          */

#define RESET_HW        1
#define UNDO_RESET_HW   0

#endif      /*  !__midl */

#endif

/*
        end of pivardef.h
*********************************************************************
*/
