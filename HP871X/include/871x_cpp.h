/*****************************************************************************/
/*  871x_cpp.h                                                                 */
/*  Copyright (C) 1998 Hewlett-Packard Company                               */
/*---------------------------------------------------------------------------*/
/*  Driver for hp871x, $instrument desc$                                     */
/*  Driver Version: A.01.00                                                  */
/*****************************************************************************/

#ifndef hp871x_INCLUDE 
#define hp871x_INCLUDE
#include "vpptype.h"

/* Used for "C" externs in C++ */
#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************/
/*  STANDARD SECTION                                                         */
/*  Constants and function prototypes for HP standard functions.             */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* DEVELOPER: Remove what you don't need from this standard function         */
/*              section, with the exception that VPP required functions      */
/*              may not be removed.                                          */
/*            Don't add to this section - add to the instrument specific     */
/*              section below.                                               */
/*            Don't change section - if you need to "change" the prototype   */
/*              of a standard function, delete it from this section and      */
/*              add a new function (named differently) in the instrument     */
/*              specific section.                                            */
/*---------------------------------------------------------------------------*/

        /***************************************************/
        /*  Standard constant error conditions returned    */
        /*  by driver functions.                           */
        /*    HP Common Error numbers start at BFFC0D00    */
        /*    The parameter errors extend the number of    */
        /*      errors over the eight defined in VPP 3.4   */
        /***************************************************/

#define hp871x_INSTR_ERROR_NULL_PTR      (_VI_ERROR+0x3FFC0D02L) /* 0xBFFC0D02 */
#define hp871x_INSTR_ERROR_RESET_FAILED  (_VI_ERROR+0x3FFC0D03L) /* 0xBFFC0D03 */
#define hp871x_INSTR_ERROR_UNEXPECTED    (_VI_ERROR+0x3FFC0D04L) /* 0xBFFC0D04 */
#define hp871x_INSTR_ERROR_INV_SESSION   (_VI_ERROR+0x3FFC0D05L) /* 0xBFFC0D05 */
#define hp871x_INSTR_ERROR_LOOKUP        (_VI_ERROR+0x3FFC0D06L) /* 0xBFFC0D06 */
#define hp871x_INSTR_ERROR_DETECTED      (_VI_ERROR+0x3FFC0D07L) /* 0xBFFC0D07 */
#define hp871x_INSTR_NO_LAST_COMMA       (_VI_ERROR+0x3FFC0D08L) /* 0xBFFC0D08 */ 

#define hp871x_INSTR_ERROR_PARAMETER9    (_VI_ERROR+0x3FFC0D20L) /* 0xBFFC0D20 */
#define hp871x_INSTR_ERROR_PARAMETER10   (_VI_ERROR+0x3FFC0D21L) /* 0xBFFC0D21 */
#define hp871x_INSTR_ERROR_PARAMETER11   (_VI_ERROR+0x3FFC0D22L) /* 0xBFFC0D22 */
#define hp871x_INSTR_ERROR_PARAMETER12   (_VI_ERROR+0x3FFC0D23L) /* 0xBFFC0D23 */
#define hp871x_INSTR_ERROR_PARAMETER13   (_VI_ERROR+0x3FFC0D24L) /* 0xBFFC0D24 */
#define hp871x_INSTR_ERROR_PARAMETER14   (_VI_ERROR+0x3FFC0D25L) /* 0xBFFC0D25 */
#define hp871x_INSTR_ERROR_PARAMETER15   (_VI_ERROR+0x3FFC0D26L) /* 0xBFFC0D26 */
#define hp871x_INSTR_ERROR_PARAMETER16   (_VI_ERROR+0x3FFC0D27L) /* 0xBFFC0D27 */
#define hp871x_INSTR_ERROR_PARAMETER17   (_VI_ERROR+0x3FFC0D28L) /* 0xBFFC0D28 */
#define hp871x_INSTR_ERROR_PARAMETER18   (_VI_ERROR+0x3FFC0D29L) /* 0xBFFC0D29 */

        /***************************************************/
        /*  Constants used by system status functions      */
        /*    These defines are bit numbers which define   */
        /*    the operation and questionable registers.    */
        /*    They are instrument specific.                */
        /***************************************************/

/*---------------------------------------------------------------------------*/
/* DEVELOPER: Modify these bit values to reflect the meanings of the         */
/*            operation and questionable status registers for your           */
/*              instrument.                                                  */
/*---------------------------------------------------------------------------*/

#define hp871x_QUES_BIT0          1
#define hp871x_QUES_BIT1          2
#define hp871x_QUES_BIT2          4
#define hp871x_QUES_BIT3          8
#define hp871x_QUES_BIT4         16
#define hp871x_QUES_BIT5         32
#define hp871x_QUES_BIT6         64
#define hp871x_QUES_BIT7        128
#define hp871x_QUES_BIT8        256
#define hp871x_QUES_BIT9        512
#define hp871x_QUES_BIT10      1024
#define hp871x_QUES_BIT11      2048
#define hp871x_QUES_BIT12      4096
#define hp871x_QUES_BIT13      8192
#define hp871x_QUES_BIT14     16384
#define hp871x_QUES_BIT15     32768

#define hp871x_OPER_BIT0          1
#define hp871x_OPER_BIT1          2
#define hp871x_OPER_BIT2          4
#define hp871x_OPER_BIT3          8
#define hp871x_OPER_BIT4         16
#define hp871x_OPER_BIT5         32
#define hp871x_OPER_BIT6         64
#define hp871x_OPER_BIT7        128
#define hp871x_OPER_BIT8        256
#define hp871x_OPER_BIT9        512
#define hp871x_OPER_BIT10      1024
#define hp871x_OPER_BIT11      2048
#define hp871x_OPER_BIT12      4096
#define hp871x_OPER_BIT13      8192
#define hp871x_OPER_BIT14     16384
#define hp871x_OPER_BIT15     32768

        /***************************************************/
        /*  Constants used by function hp871x_timeOut      */
        /***************************************************/

#define hp871x_TIMEOUT_MAX         2147483647L
#define hp871x_TIMEOUT_MIN         0L

        /***************************************************/
        /*  Required plug and play functions from VPP-3.1  */
        /***************************************************/

ViStatus _VI_FUNC hp871x_init
                        (ViRsrc     resourceName,
                         ViBoolean  IDQuery,
                         ViBoolean  resetDevice,
                         ViPSession instrumentHandle);

ViStatus _VI_FUNC hp871x_close
                        (ViSession  instrumentHandle);

ViStatus _VI_FUNC hp871x_reset
                        (ViSession  instrumentHandle);

ViStatus _VI_FUNC hp871x_self_test
                        (ViSession  instrumentHandle,
                         ViPInt32   selfTestResult,
                         ViPString  selfTestMessage);

ViStatus _VI_FUNC hp871x_error_query
                        (ViSession  instrumentHandle,
                         ViPInt32   errorCode,
                         ViPString  errorMessage);

ViStatus _VI_FUNC hp871x_error_message
                        (ViSession  instrumentHandle,
                         ViStatus   statusCode,
                         ViPString  message);

ViStatus _VI_FUNC hp871x_revision_query
                        (ViSession  instrumentHandle,
                         ViPString  instrumentDriverRevision,
                         ViPString  firmwareRevision);


        /***************************************************/
        /*  HP standard utility functions                  */
        /***************************************************/

ViStatus _VI_FUNC hp871x_timeOut
                        (ViSession  instrumentHandle,
                         ViInt32    setTimeOut);

ViStatus _VI_FUNC hp871x_timeOut_Q
                        (ViSession  instrumentHandle,
                         ViPInt32   timeOut);

ViStatus _VI_FUNC hp871x_errorQueryDetect
                        (ViSession  instrumentHandle,
                         ViBoolean  setErrorQueryDetect);

ViStatus _VI_FUNC hp871x_errorQueryDetect_Q
                        (ViSession  instrumentHandle,
                         ViPBoolean errorQueryDetect);

ViStatus _VI_FUNC hp871x_dcl
                        (ViSession  instrumentHandle);

ViStatus _VI_FUNC hp871x_opc_Q
                        (ViSession  instrumentHandle,
                         ViPBoolean instrumentReady);


        /***************************************************/
        /*  HP standard status functions                   */
        /***************************************************/

ViStatus _VI_FUNC hp871x_readStatusByte_Q
                        (ViSession  instrumentHandle,
                         ViPInt32   statusByte);

ViStatus _VI_FUNC hp871x_operEvent_Q
                        (ViSession  instrumentHandle,
                         ViPInt32   operationEventRegister);

ViStatus _VI_FUNC hp871x_operCond_Q
                        (ViSession  instrumentHandle,
                         ViPInt32   operationConditionRegister );

ViStatus _VI_FUNC hp871x_quesEvent_Q
                        (ViSession  instrumentHandle,
                         ViPInt32   questionableEventRegister );

ViStatus _VI_FUNC hp871x_quesCond_Q
                        (ViSession  instrumentHandle,
                         ViPInt32   questionableConditionRegister );


        /***************************************************/
        /*  HP standard command passthrough functions      */
        /***************************************************/

ViStatus _VI_FUNC hp871x_cmd
                        (ViSession  instrumentHandle,
                         ViString   sendStringCommand);

ViStatus _VI_FUNC hp871x_cmdString_Q
                        (ViSession  instrumentHandle,
                         ViString   queryStringCommand, 
	                     ViInt32    stringSize,
                         ViPString  stringResult);
	
ViStatus _VI_FUNC hp871x_cmdInt
                        (ViSession  instrumentHandle,
                         ViString   sendIntegerCommand,
                         ViInt32    sendInteger);

ViStatus _VI_FUNC hp871x_cmdInt16_Q
                        (ViSession  instrumentHandle,
                         ViString   queryI16Command,
                         ViPInt16   i16Result);

ViStatus _VI_FUNC hp871x_cmdInt32_Q
                        (ViSession  instrumentHandle,
                         ViString   queryI32Command,
                         ViPInt32   i32Result);

ViStatus _VI_FUNC hp871x_cmdReal
                        (ViSession  instrumentHandle,
                         ViString   sendRealCommand,
                         ViReal64   sendReal);

ViStatus _VI_FUNC hp871x_cmdReal64_Q
                        (ViSession  instrumentHandle,
                         ViString   queryRealCommand,
                         ViPReal64  realResult);

/* End of HP standard declarations */
/*---------------------------------------------------------------------------*/


/*****************************************************************************/
/*  INSTRUMENT SPECIFIC SECTION                                              */
/*  Constants and function prototypes for instrument specific functions.     */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* DEVELOPER: Add constants and function prototypes here.                    */
/*            As a matter of style, add the constant #define's first,        */
/*              followed by function prototypes.                             */
/*            Remember that function prototypes must be consistent with      */
/*              the driver's function panel prototypes.                      */
/*---------------------------------------------------------------------------*/

        /***************************************************/
        /*  Instrument specific constants                  */
        /***************************************************/

#define hp871x_NO_MATCH_ERROR     		(_VI_ERROR+0x3FFC0D30L) /* 0xBFFC0D30 */
#define hp871x_MASS_STORAGE_ERROR  		(_VI_ERROR+0x3FFC0D31L) /* 0xBFFC0D31 */
#define hp871x_MEAS_CONFLICT_ERROR 		(_VI_ERROR+0x3FFC0D32L) /* 0xBFFC0D32 */
#define hp871x_READ_MATCH_ERROR 		(_VI_ERROR+0x3FFC0D33L) /* 0xBFFC0D33 */
#define hp871x_PROG_LOAD_ERROR  		(_VI_ERROR+0x3FFC0D34L) /* 0xBFFC0D34 */
#define hp871x_FILE_NOT_FOUND_ERROR		(_VI_ERROR+0x3FFC0D35L) /* 0xBFFC0D35 */
#define hp871x_INVALID_CHANNEL_ERROR	(_VI_ERROR+0x3FFC0D36L) /* 0xBFFC0D36 */
#define hp871x_CHANNEL_OFF_ERROR		(_VI_ERROR+0x3FFC0D37L) /* 0xBFFC0D37 */

/******   Used by Function hp871x_preset   *****/
#define hp871x_PRESET_DEFAULT  "DEFAULT"
#define hp871x_PRESET_FACTORY  "FACTORY"

/******   Used by Function hp871x_power   *****/
#define hp871x_CH_1         1
#define hp871x_CH_2         2
#define hp871x_POW_LVL      "LEVEL"
#define hp871x_POW_LVL_Q    "LEVEL?"
#define hp871x_PRESET_LVL   "PRESET"
#define hp871x_PRESET_LVL_Q "PRESET?"
#define hp871x_OFF          "OFF"     /* Turn RF power off */
#define hp871x_ON           "ON"      /* Turn RF power on */
#define hp871x_RF_Q         "RF?"

/******   Used by Function hp871x_frequency   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_START_STOP    "START/STOP"
#define hp871x_START_STOP_Q  "START/STOP?"
#define hp871x_CW            "CW"
#define hp871x_CW_Q          "CW?"

/******   Used by Function hp871x_points   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_PTS_3         3
#define hp871x_PTS_5         5
#define hp871x_PTS_11        11
#define hp871x_PTS_21        21
#define hp871x_PTS_51        51
#define hp871x_PTS_101       101
#define hp871x_PTS_201       201
#define hp871x_PTS_401       401
#define hp871x_PTS_801       801
#define hp871x_PTS_1601      1601
#define hp871x_SET           "SET"
#define hp871x_Q             "?"

/******   Used by Function hp871x_average   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_AVGFACT_0     0
#define hp871x_AVGFACT_1     1
#define hp871x_AVGFACT_2     2
#define hp871x_AVGFACT_4     4
#define hp871x_AVGFACT_8     8
#define hp871x_AVGFACT_16    16
#define hp871x_AVGFACT_32    32
#define hp871x_AVGFACT_64    64
#define hp871x_AVG_FACTOR    "FACTOR"
#define hp871x_AVG_FACTOR_Q  "FACTOR?"
#define hp871x_AVG_STATUS_Q  "STATUS?"
#define hp871x_AVG_RESTART   "RESTART"

/******   Used by Function hp871x_trigger   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_TRIG_HOLD     "HOLD"
#define hp871x_TRIG_IMM      "IMMEDIATE"
#define hp871x_TRIG_SINGLE   "SINGLE"
#define hp871x_TRIG_CONT     "CONTINUOUS"
/* #define hp871x_Q          "?"          */ /* Query continuous mode status */

/******   Used by Function hp871x_measure   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_A             "A"
#define hp871x_B             "B"
#define hp871x_R             "R"
#define hp871x_AR            "A/R"
#define hp871x_BR            "B/R"
#define hp871x_B_STAR        "B*"
#define hp871x_R_STAR        "R*"
#define hp871x_B_STAR_R_STAR "B*/R*"
#define hp871x_X             "X"
#define hp871x_Y             "Y"
#define hp871x_XY            "X/Y"
#define hp871x_YX            "Y/X"
#define hp871x_YR_STAR       "Y/R*"
#define hp871x_AUX           "AUX"
#define hp871x_FAULT         "FAULT"
#define hp871x_FAULT_REV     "FAULT_REV"
#define hp871x_SRL           "SRL"
#define hp871x_SRL_REV       "SRL_REV"
#define hp871x_AM_DELAY      "AM_DELAY"
#define hp871x_S11           "S11" 
#define hp871x_S12           "S12" 
#define hp871x_S21           "S21" 
#define hp871x_S22           "S22"
#define hp871x_A_REV         "A_REV"
#define hp871x_B_REV         "B_REV"
#define hp871x_R_REV         "R_REV" 
/* #define hp871x_Q          "?"   */ 

/******   Used by Function hp871x_channel   *****/
/* #define hp871x_CH_1       1 */
/* #define hp871x_CH_2       2 */
/* #define hp871x_OFF        "OFF" */ 
/* #define hp871x_ON         "ON"  */
#define hp871x_CH_STATUS_Q   "STATUS?"
#define hp871x_CH_ACTIVE_Q   "ACTIVE?"

/******   Used by Function hp871x_bandwidth   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_BW_15         15 
#define hp871x_BW_250        250 
#define hp871x_BW_1200       1200 
#define hp871x_BW_3700       3700 
#define hp871x_BW_4000       4000 
#define hp871x_BW_6500       6500 
/* #define hp871x_SET        "SET" */ 
/* #define hp871x_Q          "?"   */ 

/******   Used by Function hp871x_scale   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_SCALE_DIV          "SCALE" 
#define hp871x_SCALE_POSN         "POSITION" 
#define hp871x_SCALE_REF          "REFERENCE" 
#define hp871x_SCALE_AUTO         "AUTOSCALE" 
#define hp871x_SCALE_DELAY        "DELAY" 
#define hp871x_SCALE_PHASE_OFFS   "PHASE_OFFSET" 
#define hp871x_SCALE_DIV_Q        "SCALE?" 
#define hp871x_SCALE_POSN_Q       "POSITION?" 
#define hp871x_SCALE_REF_Q        "REFERENCE?" 
#define hp871x_SCALE_DELAY_Q      "DELAY?" 
#define hp871x_SCALE_PHASE_OFFS_Q "PHASE_OFFSET?" 

/******   Used by Function hp871x_format   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
/* #define hp871x_Q               "?" */
#define hp871x_FMT_LOG            "LOG"
#define hp871x_FMT_LINEAR         "LINEAR"
#define hp871x_FMT_SWR            "SWR"
#define hp871x_FMT_DELAY          "DELAY"
#define hp871x_FMT_PHASE          "PHASE" 
#define hp871x_FMT_SMITH          "SMITH"
#define hp871x_FMT_POLAR          "POLAR"
#define hp871x_FMT_REAL           "REAL"
#define hp871x_FMT_IMAG           "IMAG"
#define hp871x_FMT_IMP            "IMPEDANCE"

/******   Used by Function hp871x_sweepTime   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_SWPTIME_SET        "SWEEPTIME"
#define hp871x_SWPTIME_AUTO       "AUTO"
#define hp871x_SWPTIME_MAN        "MANUAL"
#define hp871x_SWPTIME_Q          "SWEEPTIME?"
#define hp871x_SWPTIME_AUTO_Q     "AUTO?"

/******   Used by Function hp871x_sweepAlt   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_powerSweep   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
/* #define hp871x_ON               "ON"  */
/* #define hp871x_OFF              "OFF" */
#define hp871x_PWRSWP_START_STOP   "START/STOP"
#define hp871x_PWRSWP_RANGE        "RANGE"
#define hp871x_PWRSWP_STATUS_Q     "STATUS?"
#define hp871x_PWRSWP_START_STOP_Q "S/S?"
#define hp871x_PWRSWP_RANGE_Q      "RANGE?"

/******   Used by Function hp871x_markerSet   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
/* #define hp871x_ON               "ON"  */
/* #define hp871x_OFF              "OFF" */
#define hp871x_MKR_FREQ            "FREQUENCY"
#define hp871x_MKR_POINT           "POINT"
#define hp871x_MKR_MIN             "MINIMUM" 
#define hp871x_MKR_MAX             "MAXIMUM"
#define hp871x_MKR_MINLEFT         "MINLEFT"
#define hp871x_MKR_MINRIGHT        "MINRIGHT"
#define hp871x_MKR_MAXLEFT         "MAXLEFT"
#define hp871x_MKR_MAXRIGHT        "MAXRIGHT"
#define hp871x_MKR_ALL_OFF         "ALL_OFF"
#define hp871x_MKR_BW              "BANDWIDTH"
#define hp871x_MKR_DELTA_ON        "DELTA_ON"
#define hp871x_MKR_DELTA_OFF       "DELTA_OFF"
#define hp871x_MKR_STATS           "STATISTICS"
#define hp871x_MKR_FLATNESS        "FLATNESS"
#define hp871x_MKR_FSTAT           "FST"
#define hp871x_MKR_TO_CENTER       "TO_CENTER"
#define hp871x_MKR_TO_REF          "TO_REF"
#define hp871x_MKR_TO_DELAY        "TO_DELAY"
#define hp871x_MKR_SET_ABS         "SET_ABS"
#define hp871x_MKR_TRACK_ON        "TRACK_ON"
#define hp871x_MKR_TRACK_OFF       "TRACK_OFF"

/******   Used by Function hp871x_markerRead   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_MKR_AMPL_Q          "AMPLITUDE?"
#define hp871x_MKR_POSN_Q          "POSITION?"
#define hp871x_MKR_REF_X_Q         "REF_X?"
#define hp871x_MKR_REF_Y_Q         "REF_Y?"
#define hp871x_MKR_INDUCT_Q        "INDUCTANCE?"
#define hp871x_MKR_REACT_Q         "REACTANCE?"
#define hp871x_MKR_RESIST_Q        "RESISTANCE?"
#define hp871x_MKR_PHASE_Q         "PHASE?"
#define hp871x_MKR_MAGN_Q          "MAGNITUDE?"
#define hp871x_MKR_DELAY_Q         "DELAY?"
#define hp871x_MKR_FUNCTION_Q      "FUNCTION?"

/******   Used by Function hp871x_screen   *****/
#define hp871x_IBASIC_OFF		"IBASIC_OFF"  
#define hp871x_UPPER			"UPPER"  
#define hp871x_LOWER			"LOWER"  
#define hp871x_FULL			"FULL"  
#define hp871x_IBASIC_Q			"IBASIC?"  
#define hp871x_SPLIT_OFF		"SPLIT_OFF"  
#define hp871x_SPLIT_ON			"SPLIT_ON"  
#define hp871x_SPLIT_Q			"SPLIT?"  
#define hp871x_EXPAND_OFF		"EXPAND_OFF"  
#define hp871x_EXPAND_ON		"EXPAND_ON"  
#define hp871x_EXPAND_Q			"EXPAND?"  


/******   Used by Function hp871x_triggerSource   *****/
#define hp871x_TRIG_INTERNAL      "INTERNAL"  
#define hp871x_TRIG_SWEEP         "SWEEP"  
#define hp871x_TRIG_POINT         "POINT"  
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_display   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_NORMALIZE          "NORMALIZE"
#define hp871x_DISP_DATA          "DATA"
#define hp871x_DATA_TO_MEM        "DATA_TO_MEM"
#define hp871x_DISP_MEMORY        "MEMORY"
#define hp871x_DISP_DATA_DIV_MEM  "DATA/MEM"
#define hp871x_DISP_DATA_AND_MEM  "DATA&MEM"

/******   Used by Function hp871x_message   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_MSG_ALL_OFF        "ALL_OFF"
#define hp871x_MSG_CLEAR          "CLEAR"
#define hp871x_MSG_SHOW           "SHOW"
#define hp871x_MSG_SHOW_3         "SHOW3"
#define hp871x_MSG_SHOW_5         "SHOW5"
#define hp871x_MSG_SHOW_8         "SHOW8"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_spurAvoid   *****/
#define hp871x_NONE               "NONE"
#define hp871x_AVOID              "AVOID"
#define hp871x_DITHER             "DITHER"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_softkey   *****/
#define hp871x_ERASE_SOFTKEYS     "ERASE_SOFTKEYS"

/******   Used by Function hp871x_refOscillator   *****/
#define hp871x_REF_OSC_INT        "INTERNAL"
#define hp871x_REF_OSC_EXT        "EXTERNAL"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_title   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_TITLE_1            "TITLE1"
#define hp871x_TITLE_2            "TITLE2"
#define hp871x_CLOCK_OFF          "CLOCK_OFF"
#define hp871x_CLOCK_1            "CLOCK1"
#define hp871x_CLOCK_2            "CLOCK2"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_keyQueue   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_QUEUE_CLEAR        "CLEAR"
#define hp871x_QUEUE_COUNT_Q      "COUNT?"
#define hp871x_QUEUE_MAX_Q        "MAX?"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_autozero   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_AUTOZERO_ONCE      "ONCE"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_calkit   *****/
#define hp871x_CALKIT_N50F        "N50F"
#define hp871x_CALKIT_N50M        "N50M"
#define hp871x_CALKIT_3_5         "3.5"
#define hp871x_CALKIT_USER        "USER"
#define hp871x_CALKIT_N75F        "N75F"
#define hp871x_CALKIT_N75M        "N75M"
#define hp871x_CALKIT_F75         "F75"
#define hp871x_CALKIT_APC7        "APC-7"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_calMeasure   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_CAL_STAN_1         "1"
#define hp871x_CAL_STAN_2         "2"
#define hp871x_CAL_STAN_3         "3"
#define hp871x_CAL_STAN_4         "4"
#define hp871x_CAL_STAN_5         "5"
#define hp871x_CAL_STAN_6         "6"
#define hp871x_CAL_STAN_7         "7"

/******   Used by Function hp871x_calType   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_CAL_RESPONSE       "RESPONSE"
#define hp871x_CAL_RESP_ISOL      "RESP_&_ISOL"
#define hp871x_CAL_ENH_RESP       "ENH_RESP"
#define hp871x_CAL_REFLECTION     "REFLECTION"
#define hp871x_CAL_TWO_PORT		  "TWOPORT"
/* #define hp871x_NORMALIZE       "NORMALIZE" */

/******   Used by Function hp871x_calControl   *****/
/* #define hp871x_CH_1		    1 */
/* #define hp871x_CH_2		    2 */
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_CAL_FULL           "FULL"
#define hp871x_CAL_USER           "USER"
#define hp871x_CAL_DEFAULT        "DEFAULT"
#define hp871x_CAL_DEFAULT1       "DEFAULT1"
#define hp871x_CAL_DEFAULT2       "DEFAULT2"
#define hp871x_CAL_SAVE           "SAVE"
#define hp871x_CAL_ABORT          "ABORT"
#define hp871x_CAL_REFL           "REFL3"
#define hp871x_CAL_TRANS_1        "TRAN1"
#define hp871x_CAL_TRANS_2        "TRAN2"
#define hp871x_CAL_TRANS_3        "TRAN3"
#define hp871x_CAL_TEST_1         "TEST1"
#define hp871x_CAL_CLASS_Q		  "CLASS?"
#define hp871x_CAL_STATUS_Q		  "STATUS?"
#define hp871x_CAL_TYPE_Q		  "TYPE?"
/* #define hp871x_CAL_TWO_PORT	  "TWOPORT"  */

/******   Used by Function hp871x_aperture   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_APERTURE_SET       "SET"
#define hp871x_APERTURE_HZ_Q      "SPAN?"
#define hp871x_APERTURE_PCT_Q     "PERCENT?"

/******   Used by Function hp871x_traceRead   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_TRC_RD_FDATA_Q     "FDATA?"
#define hp871x_TRC_RD_FMEM_Q      "FMEM?"
#define hp871x_TRC_RD_RI_Q        "R&I?"
#define hp871x_TRC_RD_RI_MEM_Q    "R&I_MEM?"
#define hp871x_TRC_RD_A_RAW_Q     "A_RAW?"
#define hp871x_TRC_RD_B_RAW_Q     "B_RAW?"
#define hp871x_TRC_RD_R_RAW_Q     "R_RAW?"
#define hp871x_TRC_RD_CORR1_Q     "CORR1?"
#define hp871x_TRC_RD_CORR2_Q     "CORR2?"
#define hp871x_TRC_RD_CORR3_Q     "CORR3?"
#define hp871x_TRC_RD_CORR4_Q     "CORR4?"
#define hp871x_TRC_RD_CORR5_Q     "CORR5?"
#define hp871x_TRC_RD_CORR6_Q     "CORR6?"
#define hp871x_TRC_RD_CORR7_Q     "CORR7?"
#define hp871x_TRC_RD_CORR8_Q     "CORR8?"
#define hp871x_TRC_RD_CORR9_Q     "CORR9?"
#define hp871x_TRC_RD_CORR10_Q    "CORR10?"
#define hp871x_TRC_RD_CORR11_Q    "CORR11?"
#define hp871x_TRC_RD_CORR12_Q    "CORR12?"


/******   Used by Function hp871x_traceAvgRead   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */

/******   Used by Function hp871x_userTTL   *****/
#define hp871x_TTL_DEFAULT        "DEFAULT"
#define hp871x_TTL_KEY            "KEY"
#define hp871x_TTL_SWEEP          "SWEEP"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_Z0   *****/
#define hp871x_SYSTEM_Z0          "SYSTEM"
#define hp871x_SMITH_Z0           "SMITH"
#define hp871x_SYSTEM_Z0_Q        "SYSTEM?"
#define hp871x_SMITH_Z0_Q         "SMITH?"

/******   Used by Function hp871x_labelsFreq   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_LABELS_MHZ         "MHZ"
#define hp871x_LABELS_KHZ         "KHZ"
#define hp871x_LABELS_HZ          "HZ"
#define hp871x_LABELS_PRIVATE     "PRIVATE"
#define hp871x_LABELS_START_STOP  "S/S"
#define hp871x_LABELS_CW          "CW"
#define hp871x_LABELS_CSPAN       "CSPAN"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_labelsUser   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_USER_LABEL         "LABEL"
#define hp871x_USER_SUFFIX        "SUFFIX"
#define hp871x_USER_START         "START"
#define hp871x_USER_STOP          "STOP"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_extensions   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_EXTNSN_REFL        "REFL"
#define hp871x_EXTNSN_REFL_Q      "REFL?"
#define hp871x_EXTNSN_TRANS       "TRANS"
#define hp871x_EXTNSN_TRANS_Q     "TRANS?"
#define hp871x_VELOCITY           "VELOCITY"
#define hp871x_VELOCITY_Q         "VELOCITY?"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_faultSetup   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_FAULT_FEET         "FEET"
#define hp871x_FAULT_METERS       "METERS"
#define hp871x_FAULT_UNITS_Q      "UNITS?"
#define hp871x_FAULT_LOWPASS      "LOWPASS"
#define hp871x_FAULT_BANDPASS     "BANDPASS"
#define hp871x_FAULT_MODE_Q       "MODE?"
#define hp871x_FAULT_MIN          "MINIMUM"
#define hp871x_FAULT_MED          "MEDIUM"
#define hp871x_FAULT_MAX          "MAXIMUM"
#define hp871x_FAULT_WINDOW_Q     "WINDOW?"

/******   Used by Function hp871x_faultMeas   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_FAULT_START        "START"
#define hp871x_FAULT_START_Q      "START?"
#define hp871x_FAULT_STOP         "STOP"
#define hp871x_FAULT_STOP_Q       "STOP?"
#define hp871x_FAULT_CENTER       "CENTER"
#define hp871x_FAULT_CENTER_Q     "CENTER?"
#define hp871x_FAULT_MAXSPAN      "MAXSPAN"
#define hp871x_FAULT_MAXSPAN_Q    "MAXSPAN?"

/******   Used by Function hp871x_faultCal   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_FAULT_LOSS          "LOSS"
#define hp871x_FAULT_LOSS_Q        "LOSS?"
#define hp871x_FAULT_CAL_LENGTH    "CAL_LENGTH"
#define hp871x_FAULT_CAL_LENGTH_Q  "CAL_LENGTH?"
#define hp871x_FAULT_CAL_MEASURE   "MEASURE"
#define hp871x_FAULT_MULTIPEAK     "MULTIPEAK"
#define hp871x_FAULT_MULTIPEAK_Q   "MULTIPEAK?"
#define hp871x_FAULT_THRESHOLD     "THRESHOLD"
#define hp871x_FAULT_THRESHOLD_Q   "THRESHOLD?"
#define hp871x_FAULT_CONN_LENGTH   "CONN_LENGTH"
#define hp871x_FAULT_CONN_LENGTH_Q "CONN_LENGTH?"
/* #define hp871x_VELOCITY         "VELOCITY"  */
/* #define hp871x_VELOCITY_Q       "VELOCITY?" */

/******   Used by Function hp871x_traceWrite   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_TRC_WRT_FDATA      "FDATA"
#define hp871x_TRC_WRT_FMEM       "FMEM"
#define hp871x_TRC_WRT_RI         "R&I"
#define hp871x_TRC_WRT_RI_MEM     "R&I_MEM"
#define hp871x_TRC_WRT_A_RAW      "A_RAW"
#define hp871x_TRC_WRT_B_RAW      "B_RAW"
#define hp871x_TRC_WRT_R_RAW      "R_RAW"
#define hp871x_TRC_WRT_CORR1      "CORR1"
#define hp871x_TRC_WRT_CORR2      "CORR2"
#define hp871x_TRC_WRT_CORR3      "CORR3"
#define hp871x_TRC_WRT_CORR4      "CORR4"
#define hp871x_TRC_WRT_CORR5      "CORR5"
#define hp871x_TRC_WRT_CORR6      "CORR6"
#define hp871x_TRC_WRT_CORR7      "CORR7"
#define hp871x_TRC_WRT_CORR8      "CORR8"
#define hp871x_TRC_WRT_CORR9      "CORR9"
#define hp871x_TRC_WRT_CORR10     "CORR10"
#define hp871x_TRC_WRT_CORR11     "CORR11"
#define hp871x_TRC_WRT_CORR12     "CORR12"

/******   Used by Function hp871x_multiport   *****/
/* #define hp871x_CH_1			  1 */
/* #define hp871x_CH_2			  2 */
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_MP_SELFCAL_ON      "SELFCAL_ON"
#define hp871x_MP_SELFCAL_OFF     "SELFCAL_OFF"
#define hp871x_MP_SELFCAL_Q       "SELFCAL?"
#define hp871x_MP_CAL_ONCE        "ONCE"
#define hp871x_MP_CAL_ALL         "CAL_ALL"
#define hp871x_MP_PORTS           "PORTS"
#define hp871x_MP_PORTS_Q         "PORTS?"
#define hp871x_MP_CAL_TIMER       "TIMER"
#define hp871x_MP_CAL_TIMER_Q     "TIMER?"
#define hp871x_MP_STATUS_Q        "STATUS?"
#define hp871x_MP_MAXPORTS_Q      "MAXPORTS?"

/******   Used by Function hp871x_print   *****/
#define hp871x_PRINT_NOW          "PRINT"
#define hp871x_PRINT_ABORT        "ABORT"
#define hp871x_PRINT_ADDR         "ADDRESS"
#define hp871x_PRINT_DEST         "DESTINATION"
#define hp871x_PRINT_LANG_Q       "LANGUAGE?"
#define hp871x_PRINT_PORT_Q       "PORT?"
#define hp871x_PRINT_COLOR        "COLOR"
#define hp871x_PRINT_MODE         "MODE"
#define hp871x_PRINT_ORIENT       "ORIENTATION"
#define hp871x_PRINT_RES          "RESOLUTION"
#define hp871x_PRINT_FF           "FORMFEED"
#define hp871x_PRINT_RES_75       "75"
#define hp871x_PRINT_RES_90       "90"
#define hp871x_PRINT_RES_96       "96"
#define hp871x_PRINT_RES_100      "100"
#define hp871x_PRINT_RES_150      "150"
#define hp871x_PRINT_RES_300      "300"
#define hp871x_PRINT_RES_600      "600"

/******   Used by Function hp871x_limits   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
#define hp871x_LIMIT_ON				 "LIMITS_ON"
#define hp871x_LIMIT_OFF			 "LIMITS_OFF"
#define hp871x_LIMIT_DISPLAY_ON		 "DISPLAY_ON"
#define hp871x_LIMIT_DISPLAY_OFF     "DISPLAY_OFF"
#define hp871x_LIMIT_TEXT_ON         "TEXT_ON"
#define hp871x_LIMIT_TEXT_OFF        "TEXT_OFF"
#define hp871x_LIMIT_ICON_ON         "ICON_ON"
#define hp871x_LIMIT_ICON_OFF        "ICON_OFF"
#define hp871x_LIMIT_DELETE			 "DELETE"
#define hp871x_LIMIT_STATUS_Q	 	 "STATUS?"
#define hp871x_LIMIT_RESULT_Q		 "RESULT?"


/******   Used by Function hp871x_limitSet   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */

/******   Used by Function hp871x_softkeyBegin   *****/
/* #define hp871x_ERASE_SOFTKEYS   "ERASE_SOFTKEYS" */

/******   Used by Function hp871x_dataPorts   *****/
#define hp871x_DATA_PARALLEL      "PARALLEL"
#define hp871x_DATA_PARALLEL_Q    "PARALLEL?"
#define hp871x_DATA_SERIAL        "SERIAL"
#define hp871x_DATA_SERIAL_Q      "SERIAL?"
#define hp871x_DATA_USER          "USER"
#define hp871x_DATA_USER_Q        "USER?"
#define hp871x_DATA_LIMIT         "LIMIT"
#define hp871x_DATA_LIMIT_Q       "LIMIT?"
#define hp871x_DATA_STATUS_Q      "STATUS?"

/******   Used by Function hp871x_beep   *****/
#define hp871x_BEEP_DEFAULT       "DEFAULT" 
#define hp871x_BEEP_PROMPT        "PROMPT" 
#define hp871x_BEEP_DOUBLE        "DOUBLE" 
#define hp871x_BEEP_ERROR         "ERROR" 
#define hp871x_BEEP_FATAL         "FATAL" 
#define hp871x_BEEP_CHIRP         "CHIRP" 
#define hp871x_BEEP_OK            "OK" 
#define hp871x_BEEP_ALERT         "ALERT" 

/******   Used by Function hp871x_memory   *****/
#define hp871x_CHANGE_DIR         "CD" 
#define hp871x_COPY_FILE          "COPY" 
#define hp871x_DELETE_FILE        "DELETE" 
#define hp871x_INIT_MEM           "INIT_MEM" 
#define hp871x_INIT_DISK          "INIT_DISK" 
#define hp871x_MAKE_DIR           "MKDIR" 
#define hp871x_REMOVE_DIR         "RMDIR" 
#define hp871x_MOVE_FILE          "MOVE" 
#define hp871x_DIR_UP             "UP" 
#define hp871x_RAM                "RAM" 
#define hp871x_NONVOL             "NONVOL" 
#define hp871x_DISK               "DISK" 
#define hp871x_FILE_TO_RFNA       "TO_RFNA" 
#define hp871x_FILE_FROM_RFNA     "FROM_RFNA" 

/******   Used by Function hp871x_save   *****/
#define hp871x_SAVE_LIST1         "LIST1"
#define hp871x_SAVE_LIST2         "LIST2"
#define hp871x_SAVE_STATE         "STATE"

/******   Used by Function hp871x_recall   *****/
#define hp871x_RECALL_STATE       "RECALL"
#define hp871x_FAST_ON            "FAST_ON"
#define hp871x_FAST_OFF           "FAST_OFF"
/* #define hp871x_Q               "?"   */

/******   Used by Function hp871x_dir   *****/
#define hp871x_DIR_DEFAULT        "DEFAULT"
/* #define hp871x_DISK               "DISK"   */
/* #define hp871x_RAM                "RAM"    */
/* #define hp871x_NONVOL             "NONVOL" */

/******   Used by Function hp871x_dirInfo   *****/
/* #define hp871x_DIR_DEFAULT        "DEFAULT" */
/* #define hp871x_DISK               "DISK"   */
/* #define hp871x_RAM                "RAM"    */
/* #define hp871x_NONVOL             "NONVOL" */

/******   Used by Function hp871x_clock   *****/
#define hp871x_CLK_YMD            "YMD"
#define hp871x_CLK_MDY            "MDY"
#define hp871x_CLK_DMY            "DMY"
#define hp871x_CLK_ALPHA          "ALPHA"
#define hp871x_CLK_NUMERIC        "NUMERIC"
#define hp871x_CLK_DATE           "DATE"
#define hp871x_CLK_DATE_Q         "DATE?"
#define hp871x_CLK_TIME           "TIME"
#define hp871x_CLK_TIME_Q         "TIME?"
#define hp871x_CLK_SYNC           "SYNC"

/******   Used by Function hp871x_progControl   *****/
#define hp871x_PROG_DELETE        "DELETE"
#define hp871x_PROG_COMMAND       "COMMAND"
#define hp871x_PROG_STOP          "STOP"
#define hp871x_PROG_PAUSE         "PAUSE"
#define hp871x_PROG_RUN           "RUN"
#define hp871x_PROG_CONT          "CONTINUE"
#define hp871x_PROG_WAIT          "WAIT"
#define hp871x_PROG_STATE_Q       "STATE?"

/******   Used by Function hp871x_doCal   *****/
/* #define hp871x_CH_1      1 */
/* #define hp871x_CH_2      2 */
/* #define hp871x_CAL_RESPONSE       "RESPONSE"    */
/* #define hp871x_CAL_RESP_ISOL      "RESP_&_ISOL" */
/* #define hp871x_CAL_ENH_RESP       "ENH_RESP"    */
/* #define hp871x_CAL_REFLECTION     "REFLECTION"  */
/* #define hp871x_CAL_TWO_PORT		 "TWOPORT"     */

/******   Used by Function hp871x_readID   *****/
#define hp871x_MODEL_Q          "MODEL?"
#define hp871x_SERIAL_Q         "SERIAL?"
#define hp871x_REVISION_Q       "REVISION?"
#define hp871x_REV_VALUE_Q      "REV_VALUE?"
#define hp871x_MP_ID_Q          "MP_ID?"
#define hp871x_MAXFREQ_Q	  "MAXFREQ?"
#define hp871x_MINFREQ_Q        "MINFREQ?"
#define hp871x_ATTEN_Q		  "ATTEN?"
#define hp871x_LAN_Q		  "LAN?"
#define hp871x_FAULT_Q		  "FAULT?"
#define hp871x_SRL_Q		  "SRL?"
#define hp871x_50_Q		  "50?"
#define hp871x_75_Q		  "75?"
#define hp871x_IBASIC_Q		  "IBASIC?"
#define hp871x_AM_Q		  "AM?"


/******   Used by Function hp871x_saveDefine   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
#define hp871x_SAVE_CORR          "CORR"
#define hp871x_SAVE_CORR_Q        "CORR?"
#define hp871x_SAVE_ISTATE        "ISTATE"
#define hp871x_SAVE_ISTATE_Q      "ISTATE?"
#define hp871x_SAVE_TRACE         "TRACE"
#define hp871x_SAVE_TRACE_Q       "TRACE?"
#define hp871x_SAVE_FORMAT        "FORMAT"
#define hp871x_TOUCHSTONE         "TOUCHSTONE"
#define hp871x_LOTUS123           "LOTUS123"

/******   Used by Function hp871x_sweepStep   *****/
/* #define hp871x_ON              "ON"  */
/* #define hp871x_OFF             "OFF" */
/* #define hp871x_Q               "?"   */


        /***************************************************/
        /*  Instrument specific functions                  */
        /***************************************************/

ViStatus _VI_FUNC hp871x_preset( 
        ViSession vi, 
		ViString request = "DEFAULT");

ViStatus _VI_FUNC hp871x_power( 
        ViSession vi, 
		ViReal64 power,
		ViString request = "LEVEL",
		ViInt32 channel = 1,
		ViPReal64 cur_power = 0);

ViStatus _VI_FUNC hp871x_frequency( 
        ViSession vi, 
		ViReal64 freq1,
		ViReal64 freq2,
		ViString request = "S/S",
		ViInt32 channel = 1,
		ViPReal64 cur_freq1 = 0,
		ViPReal64 cur_freq2 = 0);

ViStatus _VI_FUNC hp871x_points( 
        ViSession vi, 
		ViInt32 points,
		ViString request = "SET",
		ViInt32 channel = 1,
		ViPInt32 cur_points = 0);

ViStatus _VI_FUNC hp871x_average( 
        ViSession vi, 
		ViInt32 avg_set,
		ViString request = "FACTOR",
		ViInt32 channel = 1,
		ViPInt32 cur_avg = 0);

ViStatus _VI_FUNC hp871x_trigger( 
        ViSession vi, 
		ViString request = "IMMEDIATE",
		ViInt32 channel = 1,
		ViPInt32 trig_status = 0);

ViStatus _VI_FUNC hp871x_measure( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1,
		ViPString cur_meas = "");

ViStatus _VI_FUNC hp871x_channel( 
        ViSession vi, 
		ViInt32 channel,
		ViString request = "ON",
		ViPInt32 chan_status = 0);

ViStatus _VI_FUNC hp871x_bandwidth( 
        ViSession vi, 
		ViReal64 bandwidth,
		ViString request = "SET",
		ViInt32 channel = 1,
		ViPReal64 cur_bw = 0);

ViStatus _VI_FUNC hp871x_scale( 
        ViSession vi, 
		ViReal64 value,
		ViString request= "SCALE",
		ViInt32 channel = 1,
		ViPReal64 cur_value = 0);

ViStatus _VI_FUNC hp871x_format( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1,
		ViPString cur_format = "");

ViStatus _VI_FUNC hp871x_sweepTime( 
        ViSession vi, 
		ViReal64 swptime,
		ViString request = "SET",
		ViInt32 channel = 1,
		ViPReal64 cur_sweep = 0);

ViStatus _VI_FUNC hp871x_sweepAlt( 
        ViSession vi, 
		ViString request,
		ViPInt32 swpAlt_status = 0);

ViStatus _VI_FUNC hp871x_powerSweep( 
        ViSession vi, 
		ViString request,
		ViReal64 pwrSwp_val1 = 0,
		ViReal64 pwrSwp_val2 = 0,
		ViInt32 channel = 1,
		ViPReal64 cur_pwrSwp1 = 0,
		ViPReal64 cur_pwrSwp2 = 0);

ViStatus _VI_FUNC hp871x_markerSet( 
        ViSession vi, 
		ViString request = "ON",
		ViInt32 marker = 1,
		ViReal64 mkr_val = 0,
		ViInt32 channel = 1);

ViStatus _VI_FUNC hp871x_markerRead( 
        ViSession vi, 
		ViPReal64 mkr_result,
		ViString request = "AMPL?",
		ViInt32 marker = 1,
		ViInt32 channel = 1,
		ViPReal64 mkr_result2= 0,
		ViPReal64 mkr_result3 = 0,
		ViPReal64 mkr_result4 = 0);

ViStatus _VI_FUNC hp871x_screen( 
        ViSession vi, 
		ViString request,
		ViPString screen_status = "");

ViStatus _VI_FUNC hp871x_triggerSource( 
        ViSession vi, 
		ViString request,
		ViPString trig_status = "");

ViStatus _VI_FUNC hp871x_display( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1);

ViStatus _VI_FUNC hp871x_message( 
        ViSession vi, 
		ViString request = "CLEAR",
		ViString msg = "Message Not Specified",
		ViPInt32 msg_status = 0);

// declaration of string processing function (word wrap)
int wordWrap(ViPString msg);

ViStatus _VI_FUNC hp871x_spurAvoid( 
        ViSession vi, 
		ViString request,
		ViPString spur_status = "");

ViStatus _VI_FUNC hp871x_softkey( 
        ViSession vi, 
		ViString key= "ERASE_SOFTKEYS",
		ViInt32 sfky_number = 0);

ViStatus _VI_FUNC hp871x_refOscillator( 
        ViSession vi, 
		ViString request,
		ViPInt32 refOsc_status = 0);

ViStatus _VI_FUNC hp871x_title( 
        ViSession vi, 
		ViString request,
		ViString title = "Not Specified",
		ViPInt32 title_status =0);

ViStatus _VI_FUNC hp871x_keyQueue( 
        ViSession vi, 
		ViString request = "CLEAR",
		ViPInt32 queue_status = 0);

ViStatus _VI_FUNC hp871x_keyRead( 
        ViSession vi, 
		ViPString keytype,
		ViPInt32 keycode);

ViStatus _VI_FUNC hp871x_autozero( 
        ViSession vi, 
		ViString request = "ONCE",
		ViPInt32 az_status = 0);

ViStatus _VI_FUNC hp871x_calkit( 
        ViSession vi, 
		ViString request,
		ViInt32 port_num = 1,
		ViPString cur_kit= "");

ViStatus _VI_FUNC hp871x_calMeasure( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1);

ViStatus _VI_FUNC hp871x_calType( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1);

ViStatus _VI_FUNC hp871x_calControl( 
        ViSession vi, 
		ViString request,
		ViInt32 channel= 1,
		ViPString cal_type = "");

ViStatus _VI_FUNC hp871x_aperture( 
        ViSession vi,
		ViReal64 aperture,
		ViString request = "SET",
		ViInt32 channel = 1,
		ViPReal64 cur_aperture = 0);

ViStatus _VI_FUNC hp871x_takeSweep( 
        ViSession vi, 
		ViInt32 sweeps=0);

ViStatus _VI_FUNC hp871x_traceRead( 
        ViSession vi, 
		ViReal64 _VI_FAR traceRd[],
		ViString request = "FDATA?",
		ViInt32 channel = 1,
		ViReal64 _VI_FAR traceRd2[] = 0);

ViStatus _VI_FUNC hp871x_traceAvgRead( 
        ViSession vi, 
		ViPReal64 trace_avg,
		ViInt32 channel = 1);

ViStatus _VI_FUNC hp871x_userTTL( 
        ViSession vi, 
		ViString request,
		ViPString TTL_status = "");

int RI_to_MagPhase(
		int points,
		double *val1,
		double *val2);

int MagPhase_to_RI(
		int points,
		double *val_1,
		double *val_2);

ViStatus _VI_FUNC hp871x_Z0( 
        ViSession vi, 
		ViReal64 impedance,
		ViString request = "SYSTEM",
		ViPReal64 cur_imp = 0);

ViStatus _VI_FUNC hp871x_labelsFreq( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1,
		ViPInt32 lblFreq_status = 0);

ViStatus _VI_FUNC hp871x_labelsUser( 
        ViSession vi, 
		ViString request,
		ViReal64 lbl_value= 0,
		ViString label = "",
		ViInt32 channel = 1,
		ViPInt32 lblUser_status= 0);

ViStatus _VI_FUNC hp871x_extensions( 
        ViSession vi, 
		ViString request,
		ViReal64 value = 0,
		ViPReal64 cur_extension = 0);

ViStatus _VI_FUNC hp871x_faultSetup( 
        ViSession vi, 
		ViString request,		
		ViInt32 channel = 1,
		ViPString cur_fltSetup = "");

ViStatus _VI_FUNC hp871x_faultMeas( 
        ViSession vi, 
		ViString request,
		ViReal64 fltMeas_value,
		ViInt32 channel = 1,
		ViPReal64 cur_fltMeas = 0);

ViStatus _VI_FUNC hp871x_faultCal( 
        ViSession vi, 
		ViString request,
		ViReal64 fltCal_value=0,
		ViInt32 channel = 1,
		ViPReal64 cur_fltCal = 0);

 ViStatus _VI_FUNC hp871x_traceWrite( 
         ViSession vi, 
		ViReal64 _VI_FAR traceWr[],
		ViString request = "FDATA",
		ViInt32 channel = 1,
		ViReal64 _VI_FAR traceWr2[] = 0);

 ViStatus _VI_FUNC hp871x_multiport( 
        ViSession vi, 
		ViString request,
		ViInt32 mp1 =1,
		ViInt32 mp2 =2,
		ViInt32 channel = 1,
		ViPInt32 cur_mp1=0,
	  	ViPInt32 cur_mp2=0);
	

 ViStatus _VI_FUNC hp871x_print( 
        ViSession vi, 
		ViString request= "PRINT",
		ViString data = "",
		ViPString cur_print = "");

 ViStatus _VI_FUNC hp871x_limits( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1,
		ViPInt32 limit_status = 0);

 ViStatus _VI_FUNC hp871x_limitSet( 
        ViSession vi, 
		ViInt32 segments,
		ViReal64 _VI_FAR limits[],
		ViInt32 channel =1);

ViStatus _VI_FUNC hp871x_softkeyBegin( 
        ViSession vi, 
		ViString key= "ERASE_SOFTKEYS",
		ViInt32 key_number = 0);

ViStatus _VI_FUNC hp871x_dataPorts( 
        ViSession vi,
		ViInt32 port_data,
		ViString request,
		ViPInt32 cur_data = 0);

ViStatus _VI_FUNC hp871x_beep( 
        ViSession vi, 
		ViString request = "DEFAULT");

int getChoice(
		ViSession vi,
		ViString request,
		ViInt32 size,
		ViString arr[],
		ViPInt32 choice);

int checkChannel(
       ViSession vi, 
	   ViInt32 channel);

ViStatus _VI_FUNC hp871x_memory( 
        ViSession vi, 
		ViString request,
		ViString name="",
		ViString dest="");

ViStatus _VI_FUNC hp871x_save( 
        ViSession vi, 
		ViString save_name,
		ViString request="STATE");

ViStatus _VI_FUNC hp871x_recall( 
        ViSession vi, 
		ViString recall_name,
		ViString request= "RECALL",
		ViPInt32 recall_status = 0);

ViStatus _VI_FUNC hp871x_dir(
		ViSession vi,
		ViPInt32 files,
		ViPString dir,
		ViString drive = "DEFAULT");

ViStatus _VI_FUNC hp871x_dirInfo(
		   ViSession vi,
		   ViString info_name,
		   ViPString info = "NOT FOUND",
		   ViString drive = "DEFAULT");

ViStatus _VI_FUNC hp871x_clock(
		   ViSession vi,
		   ViString request,
		   ViString clock_data = "",
		   ViPString cur_clock= "");

ViStatus _VI_FUNC hp871x_progControl( 
        ViSession vi, 
		ViString request,
		ViString command="",
		ViPString prog_status="");

ViStatus _VI_FUNC hp871x_progVariable( 
        ViSession vi, 
		ViString name,
		ViString str_data = "",
		ViPString cur_str = "",
		ViReal64 number_data = 0,
		ViPReal64 cur_number = 0);

ViStatus _VI_FUNC hp871x_progLoad( 
        ViSession vi, 
		ViString progfile);

int getLine(
		char *s, 
		int n, 
		FILE *f);

ViStatus _VI_FUNC hp871x_outputf(
        ViSession vi,
		ViInt32 opc_mode,
       	ViString fmtStr,
        ...);

ViStatus _VI_FUNC hp871x_doCal( 
        ViSession vi,
		ViString request,
		ViPInt32 abortcal,
		ViInt32 channel = 1,
		ViString prompt = "");

ViStatus _VI_FUNC hp871x_readID( 
        ViSession vi, 
		ViPString cur_ID,
		ViString request = "MODEL?",
		ViPReal64 ID_status = 0);

ViStatus _VI_FUNC hp871x_saveDefine( 
        ViSession vi,
		ViString request,
		ViString define,
		ViPInt32 define_status = 0);

ViStatus _VI_FUNC hp871x_stringParse(
		   ViSession vi,
		   ViChar _VI_FAR in_out[],
		   ViPString parsed,
           	   ViPInt32 not_done,
		   ViString delimiter = ",");

ViStatus _VI_FUNC hp871x_sweepStep( 
        ViSession vi, 
		ViString request,
		ViInt32 channel = 1,
		ViPInt32 step_status = 0);

int strip(ViString request,
		  ViPString selection);

ViStatus _VI_FUNC hp871x_checkChanStatus( 
        ViSession vi, 
		ViInt32 channel);




/* End of instrument specific declarations */
/*---------------------------------------------------------------------------*/

/* Used for "C" externs in C++ */
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif 

#endif /* hp871x_INCLUDE */

