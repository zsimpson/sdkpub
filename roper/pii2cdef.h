/*   PI controller DLLs external defintion for storing info into hw memory
*    $Logfile: /WinX32 V2.5/INCLUDE/pii2cdef.h $
*       $Date: 10/10/01 10:59a $
******************************************************************
*
*       pii2cdef.h
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
*  $Author: Dknouse $    $Date: 10/10/01 10:59a $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/pii2cdef.h $
*  
*  20    10/10/01 10:59a Dknouse
*  initial implementation of "FTG"
*   
*  
*  19    8/30/99 1:30p Terry
*  Add define ALL_CONTROLLER_BOARDS
*  
*  17    2/08/99 1:30p Terry
*  Add LOW_COST_MAIN_BRD & LOW_COST_ANALOG_HD
*  
*  16    2/03/99 4:19p Terry
*  Add defines for MSP-100 NVRAM
*  
*  15    1/13/99 1:28p Terry
*  Add  PTG_BRD define
*  
*  13    5/26/98 6:58p Charlie
*  took out i2c start address.
*  
*  11    5/04/98 11:18a Terry
*  Add IMAX_OPTION_HD
*  
*  10    4/27/98 10:59p Charlie
*  consolidated all auto nvram routines.
*  
*  9     4/27/98 9:37p Charlie
*  Added defines for functions that work with Nvram in automatic way.
*  
*  8     4/20/98 8:19p Charlie
*  Added new IMax Nvram boards.
*  
*  7     4/08/98 7:39p Charlie
*  Added imax vars.
*  
*  6     2/04/98 3:30p Charlie
*  Added 5Mhz start address's
*  
*  4     8/18/97 6:09p Charlie
*  changed sysid functions to use platform.h datatypes.
*  
*  3     7/31/96 6:00p Charlie
*  Added starting address of boards, changed enum to defines.
*  
*  2     7/18/96 2:02p Dan
*  
*  1     5/24/96 11:17a Charlie
*  read and writeing enums for system ram. 
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

#define PCI_START_ADD 0x200


/* ########################################################### */
/*                  LEVEL 7 DLLs  HW mem read/write            */
/*                  OEMs only.                                 */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

#define NO_BRD 0

/* ######################### */
/* Controllers range 1 - 500 */
/* ######################### */
#define CONTROL_BRD 1        /* ST133 control board, PentaMax.       */
#define INTERFACE_BRD 2      /* ST133 interface board.               */
#define LOW_COST_MAIN_BRD 3  /* MSP-100 Main Board                   */
#define ALL_CONTROLLER_BOARDS 4  /* Access All Boards On a Controller (needed for NVRAM32) */

/* ######################## */
/* Interface cards 501-1000 */
/* ######################## */
#define PCI_BRD 501          /* PCI interface card.                  */

/* ################### */
/* Detectors 1001-3000 */
/* ################### */
        /* Use HEAD_BRD to generally read the st133 pre-amp head.         */
#define HEAD_BRD 1001           /* ST133 5Mhz detector head.              */
#define LOW_COST_ANALOG_HD 1002 /* MSP-100 Analog Board                   */
#define IMAX_HD 1003            /* Imax head. (Pre-Amp)                   */
#define NBYTE_HD 1004           /* n-byte head (Pre-Amp)                  */
#define INGAS_HD 1005           /* In gas head. (Pre-Amp)                 */
#define IMAX_HV_HD 1006         /* High voltage board in Imax head.       */
#define IMAX_PULSER_HD 1007     /* pulser board in Imax head.             */
#define IMAX_OPTION_HD 1008     /* Option board in Imax head.             */

/* #################################### */
/* Optional Controller Boards 3001-4000 */
/* #################################### */
#define PTG_BRD 3001          /* PTG Timing Generator card.               */
#define FTG_BRD 3002          /* FTG Timing Generator card.               */


/* ############################ */
/* Open (not assigned) 3001-64K */
/* ############################ */




/* Error code for PICM_FindController,  PICM_LoadNvramDefaults, and */
/* PICM_CreateControllerNvram.                                      */

#define PI_NO_CONTROLLER_FOUND          0x0001
#define PI_CONTROLLER_ALREADY_DEFINED   0x0002
#define PI_CONTROLLER_FOUND             0x0004
#define PI_NO_CONTROLLER                0x0008
#define PI_NO_NVRAM_IN_CONTROLLER       0x0010
#define PI_NO_READ_NVRAM                0x0020
#define PI_INVALID_NVRAM                0x0040
#define PI_CHECKSUM_ERROR               0x0080
#define PI_NO_PCI_CARD_FOUND            0x0100  /* PICM_CreateControllerNvram only */
#define PI_CREATE_CONTROLLER_ERROR      0x0200  /* PICM_CreateControllerNvram only */
/*
        end of pii2cdef.h
*********************************************************************
*/
