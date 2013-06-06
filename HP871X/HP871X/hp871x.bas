Attribute VB_Name = "Module1"
'*****************************************************************************
'*  hp871x.bas                                                               *
'*  Copyright (C) 1998 Hewlett-Packard Company                               *
'*---------------------------------------------------------------------------*
'*  Driver for hp871x, $instrument desc$                                     *
'*  Driver Version: A.01.00                                                  *
'*****************************************************************************

'*****************************************************************************
'*  STANDARD SECTION                                                         *
'*  Constants and function prototypes for HP standard functions.             *
'*****************************************************************************

'*---------------------------------------------------------------------------*
'* DEVELOPER: Remove what you don't need from this standard function         *
'*              section, with the exception that VPP required functions      *
'*              may not be removed.                                          *
'*            Don't add to this section - add to the instrument specific     *
'*              section below.                                               *
'*            Don't change section - if you need to "change" the prototype   *
'*              of a standard function, delete it from this section and      *
'*              add a new function (named differently) in the instrument     *
'*              specific section.                                            *
'*---------------------------------------------------------------------------*

'        ***************************************************
'        *  Standard constant error conditions returned    *
'        *  by driver functions.                           *
'        *    HP Common Error numbers start at BFFC0D00    *
'        *    The parameter errors extend the number of    *
'        *      errors over the eight defined in VPP 3.4   *
'        ***************************************************

Global Const hp871x_INSTR_ERROR_NULL_PTR = &HBFFC0D02
Global Const hp871x_INSTR_ERROR_RESET_FAILED = &HBFFC0D03
Global Const hp871x_INSTR_ERROR_UNEXPECTED = &HBFFC0D04
Global Const hp871x_INSTR_ERROR_INV_SESSION = &HBFFC0D05
Global Const hp871x_INSTR_ERROR_LOOKUP = &HBFFC0D06
Global Const hp871x_INSTR_ERROR_DETECTED = &HBFFC0D07

Global Const hp871x_INSTR_ERROR_PARAMETER9 = &HBFFC0D20
Global Const hp871x_INSTR_ERROR_PARAMETER10 = &HBFFC0D21
Global Const hp871x_INSTR_ERROR_PARAMETER11 = &HBFFC0D22
Global Const hp871x_INSTR_ERROR_PARAMETER12 = &HBFFC0D23
Global Const hp871x_INSTR_ERROR_PARAMETER13 = &HBFFC0D24
Global Const hp871x_INSTR_ERROR_PARAMETER14 = &HBFFC0D25
Global Const hp871x_INSTR_ERROR_PARAMETER15 = &HBFFC0D26
Global Const hp871x_INSTR_ERROR_PARAMETER16 = &HBFFC0D27
Global Const hp871x_INSTR_ERROR_PARAMETER17 = &HBFFC0D28
Global Const hp871x_INSTR_ERROR_PARAMETER18 = &HBFFC0D29

'        ***************************************************
'        *  Constants used by system status functions      *
'        *    These defines are bit numbers which define   *
'        *    the operation and questionable registers.    *
'        *    They are instrument specific.                *
'        ***************************************************

'*---------------------------------------------------------------------------*
'* DEVELOPER: Modify these bit values to reflect the meanings of the         *
'*            operation and questionable status registers for your           *
'*              instrument.                                                  *
'*---------------------------------------------------------------------------*

Global Const hp871x_QUES_BYTE0 = 1
Global Const hp871x_QUES_BYTE1 = 2
Global Const hp871x_QUES_BYTE2 = 4
Global Const hp871x_QUES_BYTE3 = 8
Global Const hp871x_QUES_BYTE4 = 16
Global Const hp871x_QUES_BYTE5 = 32
Global Const hp871x_QUES_BYTE6 = 64
Global Const hp871x_QUES_BYTE7 = 128
Global Const hp871x_QUES_BYTE8 = 256
Global Const hp871x_QUES_BYTE9 = 512
Global Const hp871x_QUES_BYTE10 = 1024
Global Const hp871x_QUES_BYTE11 = 2048
Global Const hp871x_QUES_BYTE12 = 4096
Global Const hp871x_QUES_BYTE13 = 8192
Global Const hp871x_QUES_BYTE14 = 16384
Global Const hp871x_QUES_BYTE15 = 32768

Global Const hp871x_OPER_BYTE0 = 1
Global Const hp871x_OPER_BYTE1 = 2
Global Const hp871x_OPER_BYTE2 = 4
Global Const hp871x_OPER_BYTE3 = 8
Global Const hp871x_OPER_BYTE4 = 16
Global Const hp871x_OPER_BYTE5 = 32
Global Const hp871x_OPER_BYTE6 = 64
Global Const hp871x_OPER_BYTE7 = 128
Global Const hp871x_OPER_BYTE8 = 256
Global Const hp871x_OPER_BYTE9 = 512
Global Const hp871x_OPER_BYTE10 = 1024
Global Const hp871x_OPER_BYTE11 = 2048
Global Const hp871x_OPER_BYTE12 = 4096
Global Const hp871x_OPER_BYTE13 = 8192
Global Const hp871x_OPER_BYTE14 = 16384
Global Const hp871x_OPER_BYTE15 = 32768

'        ***************************************************
'        *  Constants used by function hp871x_timeOut      *
'        ***************************************************

Global Const hp871x_TIMEOUT_MAX = 2147483647
Global Const hp871x_TIMEOUT_MIN = 1&

'        ***************************************************
'        *  Required plug and play functions from VPP-3.1  *
'        ***************************************************

Declare Function hp871x_init Lib "hp871x_32.dll" _
        (ByVal resourceName As String, _
         ByVal IDQuery As Integer, _
         ByVal resetDevice As Integer, _
               instrumentHandle As Long) As Long

Declare Function hp871x_close Lib "hp871x_32.dll" _
        (ByVal instrumentHandle As Long) As Long

Declare Function hp871x_reset Lib "hp871x_32.dll" _
        (ByVal instrumentHandle As Long) As Long

Declare Function hp871x_self_test Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           selfTestResult As Integer, _
     ByVal selfTestMessage As String) As Long

Declare Function hp871x_error_query Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           errorCode As Long, _
     ByVal errorMessage As String) As Long

Declare Function hp871x_error_message Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal statusCode As Long, _
     ByVal message As String) As Long

Declare Function hp871x_revision_query Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal instrumentDriverRevision As String, _
     ByVal firmwareRevision As String) As Long


'        ***************************************************
'        *  HP standard utility functions                  *
'        ***************************************************

Declare Function hp871x_timeOut Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal setTimeOut As Long) As Long

Declare Function hp871x_timeOut_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           timeOut As Long) As Long

Declare Function hp871x_errorQueryDetect Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal setErrorQueryDetect As Integer) As Long

Declare Function hp871x_errorQueryDetect_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           errorQueryDetect As Integer) As Long

Declare Function hp871x_dcl Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long) As Long

Declare Function hp871x_opc_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           instrumentReady As Integer) As Long


'        ***************************************************
'        *  HP standard status functions                   *
'        ***************************************************

Declare Function hp871x_readStatusByte_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           statusByte As Integer) As Long

Declare Function hp871x_operEvent_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           operationEventRegister As Integer) As Long

Declare Function hp871x_operCond_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           operationConditionRegister As Integer) As Long

Declare Function hp871x_quesEvent_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           questionableEventRegister As Integer) As Long

Declare Function hp871x_quesCond_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
           questionableConditionRegister As Integer) As Long


'        ***************************************************
'        *  HP standard command passthrough functions      *
'        ***************************************************

Declare Function hp871x_cmd Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal sendStringCommand As String) As Long

Declare Function hp871x_cmdString_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal queryStringCommand As String, _
     ByVal stringSize As Long, _
     ByVal stringResult As String) As Long

Declare Function hp871x_cmdInt Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal sendIntegerCommand As String, _
     ByVal sendInteger As Long) As Long

Declare Function hp871x_cmdInt16_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal queryI16Command As String, _
           i16Result As Integer) As Long

Declare Function hp871x_cmdInt32_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal queryI32Command As String, _
           i32Result As Long) As Long

Declare Function hp871x_cmdReal Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal sendRealCommand As String, _
     ByVal sendReal As Double) As Long

Declare Function hp871x_cmdReal64_Q Lib "hp871x_32.dll" _
    (ByVal instrumentHandle As Long, _
     ByVal queryRealCommand As String, _
           realResult As Double) As Long

'* End of HP standard declarations */
'*---------------------------------------------------------------------------*


'*****************************************************************************
'*  INSTRUMENT SPECIFIC SECTION                                              *
'*  Constants and function prototypes for instrument specific functions.     *
'*****************************************************************************

'*---------------------------------------------------------------------------*
'* DEVELOPER: Add constants and function prototypes here.                    *
'*            As a matter of style, add the constant Global Const's first,        *
'*              followed by function prototypes.                             *
'*            Remember that function prototypes must be consistent with      *
'*              the driver's function panel prototypes.                      *
'*---------------------------------------------------------------------------*

'        ***************************************************
'        *  Instrument specific constants                  *
'        ***************************************************
Global Const hp871x_NO_MATCH_ERROR = &H3FFC0D30
Global Const hp871x_MASS_STORAGE_ERROR = &H3FFC0D31
Global Const hp871x_MEAS_CONFLICT_ERROR = &H3FFC0D32
Global Const hp871x_READ_MATCH_ERROR = &H3FFC0D33
Global Const hp871x_PROG_LOAD_ERROR = &H3FFC0D34
Global Const hp871x_FILE_NOT_FOUND_ERROR = &H3FFC0D35
Global Const hp871x_INVALID_CHANNEL_ERROR = &H3FFC0D36

' Used by Function hp871x_preset
Global Const hp871x_PRESET_DEFAULT = "DEFAULT"
Global Const hp871x_PRESET_FACTORY = "FACTORY"

' Used by Function hp871x_power
Global Const hp871x_CH_1 = 1
Global Const hp871x_CH_2 = 2
Global Const hp871x_POW_LVL = "LEVEL"
Global Const hp871x_POW_LVL_Q = "LEVEL?"
Global Const hp871x_PRESET_LVL = "PRESET"
Global Const hp871x_PRESET_LVL_Q = "PRESET?"
Global Const hp871x_OFF = "OFF"
Global Const hp871x_ON = "ON"
Global Const hp871x_RF_Q = "RF?"

' Used by Function hp871x_frequency
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_START_STOP = "START/STOP"
Global Const hp871x_START_STOP_Q = "START/STOP?"
Global Const hp871x_CW = "CW"
Global Const hp871x_CW_Q = "CW?"

' Used by Function hp871x_points
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_PTS_3 = 3
Global Const hp871x_PTS_5 = 5
Global Const hp871x_PTS_11 = 11
Global Const hp871x_PTS_21 = 21
Global Const hp871x_PTS_51 = 51
Global Const hp871x_PTS_101 = 101
Global Const hp871x_PTS_201 = 201
Global Const hp871x_PTS_401 = 401
Global Const hp871x_PTS_801 = 801
Global Const hp871x_PTS_1601 = 1601
Global Const hp871x_SET = "SET"
Global Const hp871x_Q = "?"

' Used by Function hp871x_average
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_AVGFACT_0 = 0
Global Const hp871x_AVGFACT_1 = 1
Global Const hp871x_AVGFACT_2 = 2
Global Const hp871x_AVGFACT_4 = 4
Global Const hp871x_AVGFACT_8 = 8
Global Const hp871x_AVGFACT_16 = 16
Global Const hp871x_AVGFACT_32 = 32
Global Const hp871x_AVGFACT_64 = 64
Global Const hp871x_AVG_FACTOR = "FACTOR"
Global Const hp871x_AVG_FACTOR_Q = "FACTOR?"
Global Const hp871x_AVG_STATUS_Q = "STATUS?"
Global Const hp871x_AVG_RESTART = "RESTART"

' Used by Function hp871x_trigger
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_TRIG_HOLD = "HOLD"
Global Const hp871x_TRIG_IMM = "IMMEDIATE"
Global Const hp871x_TRIG_SINGLE = "SINGLE"
Global Const hp871x_TRIG_CONT = "CONTINUOUS"
' Global Const hp871x_Q = "?"

' Used by Function hp871x_measure
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_A = "A"
Global Const hp871x_B = "B"
Global Const hp871x_R = "R"
Global Const hp871x_AR = "A/R"
Global Const hp871x_BR = "B/R"
Global Const hp871x_B_STAR = "B*"
Global Const hp871x_R_STAR = "R*"
Global Const hp871x_B_STAR_R_STAR = "B*/R*"
Global Const hp871x_X = "X"
Global Const hp871x_Y = "Y"
Global Const hp871x_XY = "X/Y"
Global Const hp871x_YX = "Y/X"
Global Const hp871x_YR_STAR = "Y/R*"
Global Const hp871x_AUX = "AUX"
Global Const hp871x_FAULT = "FAULT"
Global Const hp871x_FAULT_REV = "FAULT_REV"
Global Const hp871x_SRL = "SRL"
Global Const hp871x_SRL_REV = "SRL_REV"
Global Const hp871x_AM_DELAY = "AM_DELAY"
Global Const hp871x_S11 = "S11"
Global Const hp871x_S12 = "S12"
Global Const hp871x_S21 = "S21"
Global Const hp871x_S22 = "S22"
Global Const hp871x_A_REV = "A_REV"
Global Const hp871x_B_REV = "B_REV"
Global Const hp871x_R_REV = "R_REV"
' hp871x_Q

' Used by Function hp871x_channel
' hp871x_CH_1
' hp871x_CH_2
' hp871x_OFF
' hp871x_ON
Global Const hp871x_CH_STATUS_Q = "STATUS?"
Global Const hp871x_CH_ACTIVE_Q = "ACTIVE?"

' Used by Function hp871x_bandwidth
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_BW_15 = 15
Global Const hp871x_BW_250 = 250
Global Const hp871x_BW_1200 = 1200
Global Const hp871x_BW_3700 = 3700
Global Const hp871x_BW_4000 = 4000
Global Const hp871x_BW_6500 = 6500
' hp871x_SET
' hp871x_Q

' Used by Function hp871x_scale
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_SCALE_DIV = "SCALE"
Global Const hp871x_SCALE_POSN = "POSITION"
Global Const hp871x_SCALE_REF = "REFERENCE"
Global Const hp871x_SCALE_AUTO = "AUTOSCALE"
Global Const hp871x_SCALE_DELAY = "DELAY"
Global Const hp871x_SCALE_PHASE_OFFS = "PHASE_OFFSET"
Global Const hp871x_SCALE_DIV_Q = "SCALE?"
Global Const hp871x_SCALE_POSN_Q = "POSITION?"
Global Const hp871x_SCALE_REF_Q = "REFERENCE?"
Global Const hp871x_SCALE_DELAY_Q = "DELAY?"
Global Const hp871x_SCALE_PHASE_OFFS_Q = "PHASE_OFFSET?"

' Used by Function hp871x_format
' hp871x_CH_1
' hp871x_CH_2
' hp871x_Q
Global Const hp871x_FMT_LOG = "LOG"
Global Const hp871x_FMT_LINEAR = "LINEAR"
Global Const hp871x_FMT_SWR = "SWR"
Global Const hp871x_FMT_DELAY = "DELAY"
Global Const hp871x_FMT_PHASE = "PHASE"
Global Const hp871x_FMT_SMITH = "SMITH"
Global Const hp871x_FMT_POLAR = "POLAR"
Global Const hp871x_FMT_REAL = "real"
Global Const hp871x_FMT_IMAG = "IMAG"
Global Const hp871x_FMT_IMP = "IMPEDANCE"

' Used by Function hp871x_sweepTime
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_SWPTIME_SET = "SWEEPTIME"
Global Const hp871x_SWPTIME_AUTO = "AUTO"
Global Const hp871x_SWPTIME_MAN = "MANUAL"
Global Const hp871x_SWPTIME_Q = "SWEEPTIME?"
Global Const hp871x_SWPTIME_AUTO_Q = "AUTO?"

' Used by Function hp871x_sweepAlt
'hp871x_ON = "ON"
'hp871x_OFF = "OFF"
'hp871x_Q = "?"

' Used by Function hp871x_powerSweep
' hp871x_CH_1
' hp871x_CH_2
' hp871x_ON = "ON"
' hp871x_OFF = "OFF"
Global Const hp871x_PWRSWP_START_STOP = "START/STOP"
Global Const hp871x_PWRSWP_RANGE = "RANGE"
Global Const hp871x_PWRSWP_STATUS_Q = "STATUS?"
Global Const hp871x_PWRSWP_START_STOP_Q = "S/S?"
Global Const hp871x_PWRSWP_RANGE_Q = "RANGE?"

'    Used by Function hp871x_markerSet
' hp871x_CH_1
' hp871x_CH_2
' hp871x_ON
' hp871x_OFF
Global Const hp871x_MKR_FREQ = "FREQUENCY"
Global Const hp871x_MKR_POINT = "POINT"
Global Const hp871x_MKR_MIN = "MINIMUM"
Global Const hp871x_MKR_MAX = "MAXIMUM"
Global Const hp871x_MKR_MINLEFT = "MINLEFT"
Global Const hp871x_MKR_MINRIGHT = "MINRIGHT"
Global Const hp871x_MKR_MAXLEFT = "MAXLEFT"
Global Const hp871x_MKR_MAXRIGHT = "MAXRIGHT"
Global Const hp871x_MKR_ALL_OFF = "ALL_OFF"
Global Const hp871x_MKR_BW = "BANDWIDTH"
Global Const hp871x_MKR_DELTA_ON = "DELTA_ON"
Global Const hp871x_MKR_DELTA_OFF = "DELTA_OFF"
Global Const hp871x_MKR_STATS = "STATISTICS"
Global Const hp871x_MKR_FLATNESS = "FLATNESS"
Global Const hp871x_MKR_FSTAT = "FST"
Global Const hp871x_MKR_TO_CENTER = "TO_CENTER"
Global Const hp871x_MKR_TO_REF = "TO_REF"
Global Const hp871x_MKR_TO_DELAY = "TO_DELAY"
Global Const hp871x_MKR_SET_ABS = "SET_ABS"
Global Const hp871x_MKR_TRACK_ON = "TRACK_ON"
Global Const hp871x_MKR_TRACK_OFF = "TRACK_OFF"

'    Used by Function hp871x_markerRead
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_MKR_AMPL_Q = "AMPLITUDE?"
Global Const hp871x_MKR_POSN_Q = "POSITION?"
Global Const hp871x_MKR_REF_X_Q = "REF_X?"
Global Const hp871x_MKR_REF_Y_Q = "REF_Y?"
Global Const hp871x_MKR_INDUCT_Q = "INDUCTANCE?"
Global Const hp871x_MKR_REACT_Q = "REACTANCE?"
Global Const hp871x_MKR_RESIST_Q = "RESISTANCE?"
Global Const hp871x_MKR_PHASE_Q = "PHASE?"
Global Const hp871x_MKR_MAGN_Q = "MAGNITUDE?"
Global Const hp871x_MKR_DELAY_Q = "DELAY?"
Global Const hp871x_MKR_FUNCTION_Q = "FUNCTION?"

' Used by Function hp871x_screen
Global Const hp871x_IBASIC_OFF = "IBASIC_OFF"
Global Const hp871x_UPPER = "UPPER"
Global Const hp871x_LOWER = "LOWER"
Global Const hp871x_FULL = "FULL"
' hp871x_IBASIC_Q = "IBASIC?"
Global Const hp871x_SPLIT_OFF = "SPLIT_OFF"
Global Const hp871x_SPLIT_ON = "SPLIT_ON"
Global Const hp871x_SPLIT_Q = "SPLIT?"
Global Const hp871x_EXPAND_OFF = "EXPAND_OFF"
Global Const hp871x_EXPAND_ON = "EXPAND_ON"
Global Const hp871x_EXPAND_Q = "EXPAND?"


' Used by Function hp871x_triggerSource
Global Const hp871x_TRIG_INTERNAL = "INTERNAL"
Global Const hp871x_TRIG_SWEEP = "SWEEP"
Global Const hp871x_TRIG_POINT = "POINT"
' hp871x_Q

' Used by Function hp871x_display
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_NORMALIZE = "NORMALIZE"
Global Const hp871x_DISP_DATA = "DATA"
Global Const hp871x_DATA_TO_MEM = "DATA_TO_MEM"
Global Const hp871x_DISP_MEMORY = "MEMORY"
Global Const hp871x_DISP_DATA_DIV_MEM = "DATA/MEM"
Global Const hp871x_DISP_DATA_AND_MEM = "DATA&MEM"

' Used by Function hp871x_message
' hp871x_ON
' hp871x_OFF
Global Const hp871x_MSG_ALL_OFF = "ALL_OFF"
Global Const hp871x_MSG_CLEAR = "CLEAR"
Global Const hp871x_MSG_SHOW = "SHOW"
Global Const hp871x_MSG_SHOW_3 = "SHOW3"
Global Const hp871x_MSG_SHOW_5 = "SHOW5"
Global Const hp871x_MSG_SHOW_8 = "SHOW8"
' hp871x_Q

' Used by Function hp871x_spurAvoid
Global Const hp871x_NONE = "NONE"
Global Const hp871x_AVOID = "AVOID"
Global Const hp871x_DITHER = "DITHER"
' hp871x_Q

' Used by Function hp871x_softkey
Global Const hp871x_ERASE_SOFTKEYS = "ERASE_SOFTKEYS"

' Used by Function hp871x_refOscillator
Global Const hp871x_REF_OSC_INT = "internal"
Global Const hp871x_REF_OSC_EXT = "external"
' hp871x_Q

' Used by Function hp871x_title
' hp871x_ON
' hp871x_OFF
Global Const hp871x_TITLE_1 = "TITLE1"
Global Const hp871x_TITLE_2 = "TITLE2"
Global Const hp871x_CLOCK_OFF = "CLOCK_OFF"
Global Const hp871x_CLOCK_1 = "CLOCK1"
Global Const hp871x_CLOCK_2 = "CLOCK2"
' hp871x_Q

' Used by Function hp871x_keyQueue
' hp871x_ON
' hp871x_OFF
Global Const hp871x_QUEUE_CLEAR = "CLEAR"
Global Const hp871x_QUEUE_COUNT_Q = "COUNT?"
Global Const hp871x_QUEUE_MAX_Q = "MAX?"
' hp871x_Q

' Used by Function hp871x_autozero
' hp871x_ON
' hp871x_OFF
Global Const hp871x_AUTOZERO_ONCE = "ONCE"
' hp871x_Q

' Used by Function hp871x_calkit
Global Const hp871x_CALKIT_N50F = "N50F"
Global Const hp871x_CALKIT_N50M = "N50M"
Global Const hp871x_CALKIT_3_5 = "3.5"
Global Const hp871x_CALKIT_USER = "USER"
Global Const hp871x_CALKIT_N75F = "N75F"
Global Const hp871x_CALKIT_N75M = "N75M"
Global Const hp871x_CALKIT_F75 = "F75"
Global Const hp871x_CALKIT_APC7 = "APC-7"
' hp871x_Q

' Used by Function hp871x_calMeasure
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_CAL_STAN_1 = "1"
Global Const hp871x_CAL_STAN_2 = "2"
Global Const hp871x_CAL_STAN_3 = "3"
Global Const hp871x_CAL_STAN_4 = "4"
Global Const hp871x_CAL_STAN_5 = "5"
Global Const hp871x_CAL_STAN_6 = "6"
Global Const hp871x_CAL_STAN_7 = "7"

' Used by Function hp871x_calType
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_CAL_RESPONSE = "RESPONSE"
Global Const hp871x_CAL_RESP_ISOL = "resp_&_isol"
Global Const hp871x_CAL_ENH_RESP = "ENH_RESP"
Global Const hp871x_CAL_REFLECTION = "REFLECTION"
Global Const hp871x_CAL_TWO_PORT = "TWOPORT"
' hp871x_NORMALIZE

' Used by Function hp871x_calControl
' hp871x_CH_1
' hp871x_CH_2
' hp871x_ON
' hp871x_OFF
Global Const hp871x_CAL_FULL = "full"
Global Const hp871x_CAL_USER = "USER"
Global Const hp871x_CAL_DEFAULT = "DEFAULT"
Global Const hp871x_CAL_DEFAULT1 = "DEFAULT1"
Global Const hp871x_CAL_DEFAULT2 = "DEFAULT2"
Global Const hp871x_CAL_SAVE = "SAVE"
Global Const hp871x_CAL_ABORT = "ABORT"
Global Const hp871x_CAL_REFL = "REFL3"
Global Const hp871x_CAL_TRANS_1 = "TRAN1"
Global Const hp871x_CAL_TRANS_2 = "TRAN2"
Global Const hp871x_CAL_TRANS_3 = "TRAN3"
Global Const hp871x_CAL_TEST_1 = "TEST1"
Global Const hp871x_CAL_CLASS_Q = "CLASS?"
Global Const hp871x_CAL_STATUS_Q = "STATUS?"
Global Const hp871x_CAL_TYPE_Q = "TYPE?"
'hp871x_CAL_TWO_PORT

' Used by Function hp871x_aperture
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_APERTURE_SET = "SET"
Global Const hp871x_APERTURE_HZ_Q = "SPAN?"
Global Const hp871x_APERTURE_PCT_Q = "PERCENT?"

' Used by Function hp871x_traceRead
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_TRC_RD_FDATA_Q = "FDATA?"
Global Const hp871x_TRC_RD_FMEM_Q = "FMEM?"
Global Const hp871x_TRC_RD_RI_Q = "R&I?"
Global Const hp871x_TRC_RD_RI_MEM_Q = "R&I_MEM?"
Global Const hp871x_TRC_RD_A_RAW_Q = "A_RAW?"
Global Const hp871x_TRC_RD_B_RAW_Q = "B_RAW?"
Global Const hp871x_TRC_RD_R_RAW_Q = "R_RAW?"
Global Const hp871x_TRC_RD_CORR1_Q = "CORR1?"
Global Const hp871x_TRC_RD_CORR2_Q = "CORR2?"
Global Const hp871x_TRC_RD_CORR3_Q = "CORR3?"
Global Const hp871x_TRC_RD_CORR4_Q = "CORR4?"
Global Const hp871x_TRC_RD_CORR5_Q = "CORR5?"
Global Const hp871x_TRC_RD_CORR6_Q = "CORR6?"
Global Const hp871x_TRC_RD_CORR7_Q = "CORR7?"
Global Const hp871x_TRC_RD_CORR8_Q = "CORR8?"
Global Const hp871x_TRC_RD_CORR9_Q = "CORR9?"
Global Const hp871x_TRC_RD_CORR10_Q = "CORR10?"
Global Const hp871x_TRC_RD_CORR11_Q = "CORR11?"
Global Const hp871x_TRC_RD_CORR12_Q = "CORR12?"

' Used by Function hp871x_traceAvgRead
' hp871x_CH_1
' hp871x_CH_2

' Used by Function hp871x_userTTL
Global Const hp871x_TTL_DEFAULT = "DEFAULT"
Global Const hp871x_TTL_KEY = "KEY"
Global Const hp871x_TTL_SWEEP = "SWEEP"
' hp871x_Q

' Used by Function hp871x_Z0
Global Const hp871x_SYSTEM_Z0 = "SYSTEM"
Global Const hp871x_SMITH_Z0 = "SMITH"
Global Const hp871x_SYSTEM_Z0_Q = "SYSTEM?"
Global Const hp871x_SMITH_Z0_Q = "SMITH?"

' Used by Function hp871x_labelsFreq
' hp871x_ON
' hp871x_OFF
Global Const hp871x_LABELS_MHZ = "MHZ"
Global Const hp871x_LABELS_KHZ = "KHZ"
Global Const hp871x_LABELS_HZ = "HZ"
Global Const hp871x_LABELS_PRIVATE = "PRIVATE"
Global Const hp871x_LABELS_START_STOP = "S/S"
Global Const hp871x_LABELS_CW = "CW"
Global Const hp871x_LABELS_CSPAN = "CSPAN"
' hp871x_Q               "?"

' Used by Function hp871x_labelsUser
' hp871x_ON
' hp871x_OFF
Global Const hp871x_USER_LABEL = "label"
Global Const hp871x_USER_SUFFIX = "SUFFIX"
Global Const hp871x_USER_START = "START"
Global Const hp871x_USER_STOP = "STOP"
' hp871x_Q

' Used by Function hp871x_extensions
' hp871x_ON
' hp871x_OFF
Global Const hp871x_EXTNSN_REFL = "refl"
Global Const hp871x_EXTNSN_REFL_Q = "REFL?"
Global Const hp871x_EXTNSN_TRANS = "TRANS"
Global Const hp871x_EXTNSN_TRANS_Q = "TRANS?"
Global Const hp871x_VELOCITY = "VELOCITY"
Global Const hp871x_VELOCITY_Q = "VELOCITY?"
' hp871x_Q

' Used by Function hp871x_faultSetup
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_FAULT_FEET = "FEET"
Global Const hp871x_FAULT_METERS = "METERS"
Global Const hp871x_FAULT_UNITS_Q = "UNITS?"
Global Const hp871x_FAULT_LOWPASS = "LOWPASS"
Global Const hp871x_FAULT_BANDPASS = "BANDPASS"
Global Const hp871x_FAULT_MODE_Q = "MODE?"
Global Const hp871x_FAULT_MIN = "MINIMUM"
Global Const hp871x_FAULT_MED = "MEDIUM"
Global Const hp871x_FAULT_MAX = "MAXIMUM"
Global Const hp871x_FAULT_WINDOW_Q = "WINDOW?"

' Used by Function hp871x_faultMeas
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_FAULT_START = "START"
Global Const hp871x_FAULT_START_Q = "START?"
Global Const hp871x_FAULT_STOP = "STOP"
Global Const hp871x_FAULT_STOP_Q = "STOP?"
Global Const hp871x_FAULT_CENTER = "CENTER"
Global Const hp871x_FAULT_CENTER_Q = "CENTER?"
Global Const hp871x_FAULT_MAXSPAN = "MAXSPAN"
Global Const hp871x_FAULT_MAXSPAN_Q = "MAXSPAN?"

' Used by Function hp871x_faultCal
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_FAULT_LOSS = "LOSS"
Global Const hp871x_FAULT_LOSS_Q = "LOSS?"
Global Const hp871x_FAULT_CAL_LENGTH = "CAL_LENGTH"
Global Const hp871x_FAULT_CAL_LENGTH_Q = "CAL_LENGTH?"
Global Const hp871x_FAULT_CAL_MEASURE = "MEASURE"
Global Const hp871x_FAULT_MULTIPEAK = "MULTIPEAK"
Global Const hp871x_FAULT_MULTIPEAK_Q = "MULTIPEAK?"
Global Const hp871x_FAULT_THRESHOLD = "THRESHOLD"
Global Const hp871x_FAULT_THRESHOLD_Q = "THRESHOLD?"
Global Const hp871x_FAULT_CONN_LENGTH = "CONN_LENGTH"
Global Const hp871x_FAULT_CONN_LENGTH_Q = "CONN_LENGTH?"
' hp871x_VELOCITY
' hp871x_VELOCITY_Q

' Used by Function hp871x_traceWrite
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_TRC_WRT_FDATA = "FDATA"
Global Const hp871x_TRC_WRT_FMEM = "FMEM"
Global Const hp871x_TRC_WRT_RI = "R&I"
Global Const hp871x_TRC_WRT_RI_MEM = "R&I_MEM"
Global Const hp871x_TRC_WRT_A_RAW = "A_RAW"
Global Const hp871x_TRC_WRT_B_RAW = "B_RAW"
Global Const hp871x_TRC_WRT_R_RAW = "R_RAW"
Global Const hp871x_TRC_WRT_CORR1 = "CORR1"
Global Const hp871x_TRC_WRT_CORR2 = "CORR2"
Global Const hp871x_TRC_WRT_CORR3 = "CORR3"
Global Const hp871x_TRC_WRT_CORR4 = "CORR4"
Global Const hp871x_TRC_WRT_CORR5 = "CORR5"
Global Const hp871x_TRC_WRT_CORR6 = "CORR6"
Global Const hp871x_TRC_WRT_CORR7 = "CORR7"
Global Const hp871x_TRC_WRT_CORR8 = "CORR8"
Global Const hp871x_TRC_WRT_CORR9 = "CORR9"
Global Const hp871x_TRC_WRT_CORR10 = "CORR10"
Global Const hp871x_TRC_WRT_CORR11 = "CORR11"
Global Const hp871x_TRC_WRT_CORR12 = "CORR12"


' Used by Function hp871x_multiport
' hp871x_CH_1
' hp871x_CH_2
' hp871x_ON
' hp871x_OFF
Global Const hp871x_MP_SELFCAL_ON = "SELFCAL_ON"
Global Const hp871x_MP_SELFCAL_OFF = "SELFCAL_OFF"
Global Const hp871x_MP_SELFCAL_Q = "SELFCAL?"
Global Const hp871x_MP_CAL_ONCE = "ONCE"
Global Const hp871x_MP_CAL_ALL = "cal_all"
Global Const hp871x_MP_PORTS = "PORTS"
Global Const hp871x_MP_PORTS_Q = "PORTS?"
Global Const hp871x_MP_CAL_TIMER = "TIMER"
Global Const hp871x_MP_CAL_TIMER_Q = "TIMER?"
Global Const hp871x_MP_STATUS_Q = "STATUS?"
Global Const hp871x_MP_MAXPORTS_Q = "MAXPORTS?"

' Used by Function hp871x_print
Global Const hp871x_PRINT_NOW = "PRINT"
Global Const hp871x_PRINT_ABORT = "ABORT"
Global Const hp871x_PRINT_ADDR = "ADDRESS"
Global Const hp871x_PRINT_DEST = "DESTINATION"
Global Const hp871x_PRINT_LANG_Q = "LANGUAGE?"
Global Const hp871x_PRINT_PORT_Q = "PORT?"
Global Const hp871x_PRINT_COLOR = "COLOR"
Global Const hp871x_PRINT_MODE = "MODE"
Global Const hp871x_PRINT_ORIENT = "ORIENTATION"
Global Const hp871x_PRINT_RES = "RESOLUTION"
Global Const hp871x_PRINT_FF = "FORMFEED"
Global Const hp871x_PRINT_RES_75 = "75"
Global Const hp871x_PRINT_RES_90 = "90"
Global Const hp871x_PRINT_RES_96 = "96"
Global Const hp871x_PRINT_RES_100 = "100"
Global Const hp871x_PRINT_RES_150 = "150"
Global Const hp871x_PRINT_RES_300 = "300"
Global Const hp871x_PRINT_RES_600 = "600"

' Used by Function hp871x_limits
' hp871x_CH_1
' hp871x_CH_2
Global Const hp871x_LIMIT_ON = "LIMITS_ON"
Global Const hp871x_LIMIT_OFF = "LIMITS_OFF"
Global Const hp871x_LIMIT_DISPLAY_ON = "DISPLAY_ON"
Global Const hp871x_LIMIT_DISPLAY_OFF = "DISPLAY_OFF"
Global Const hp871x_LIMIT_TEXT_ON = "TEXT_ON"
Global Const hp871x_LIMIT_TEXT_OFF = "TEXT_OFF"
Global Const hp871x_LIMIT_ICON_ON = "ICON_ON"
Global Const hp871x_LIMIT_ICON_OFF = "ICON_OFF"
Global Const hp871x_LIMIT_DELETE = "DELETE"
Global Const hp871x_LIMIT_STATUS_Q = "STATUS?"
Global Const hp871x_LIMIT_RESULT_Q = "RESULT?"

' Used by Function hp871x_limitSet
' hp871x_CH_1
' hp871x_CH_2

' Used by Function hp871x_softkeyBegin
' Global Const hp871x_ERASE_SOFTKEYS   "ERASE_SOFTKEYS"

' Used by Function hp871x_dataPorts
Global Const hp871x_DATA_PARALLEL = "parallel"
Global Const hp871x_DATA_PARALLEL_Q = "parallel?"
Global Const hp871x_DATA_SERIAL = "serial"
Global Const hp871x_DATA_SERIAL_Q = "serial?"
Global Const hp871x_DATA_USER = "USER"
Global Const hp871x_DATA_USER_Q = "USER?"
Global Const hp871x_DATA_LIMIT = "LIMIT"
Global Const hp871x_DATA_LIMIT_Q = "LIMIT?"
Global Const hp871x_DATA_STATUS_Q = "STATUS?"

' Used by Function hp871x_beep
Global Const hp871x_BEEP_DEFAULT = "DEFAULT"
Global Const hp871x_BEEP_PROMPT = "PROMPT"
Global Const hp871x_BEEP_DOUBLE = "DOUBLE"
Global Const hp871x_BEEP_ERROR = "ERROR"
Global Const hp871x_BEEP_FATAL = "fatal"
Global Const hp871x_BEEP_CHIRP = "CHIRP"
Global Const hp871x_BEEP_OK = "OK"
Global Const hp871x_BEEP_ALERT = "ALERT"

' Used by Function hp871x_memory
Global Const hp871x_CHANGE_DIR = "CD"
Global Const hp871x_COPY_FILE = "COPY"
Global Const hp871x_DELETE_FILE = "DELETE"
Global Const hp871x_INIT_MEM = "INIT_MEM"
Global Const hp871x_INIT_DISK = "INIT_DISK"
Global Const hp871x_MAKE_DIR = "MKDIR"
Global Const hp871x_REMOVE_DIR = "RMDIR"
Global Const hp871x_MOVE_FILE = "MOVE"
Global Const hp871x_DIR_UP = "UP"
Global Const hp871x_MSI_RAM = "RAM"
Global Const hp871x_MSI_NONVOL = "nonvol"
Global Const hp871x_MSI_DISK = "DISK"
Global Const hp871x_FILE_TO_RFNA = "TO_RFNA"
Global Const hp871x_FILE_FROM_RFNA = "FROM_RFNA"

' Used by Function hp871x_save
Global Const hp871x_SAVE_LIST1 = "LIST1"
Global Const hp871x_SAVE_LIST2 = "LIST2"
Global Const hp871x_SAVE_STATE = "STATE"

' Used by Function hp871x_recall
Global Const hp871x_RECALL_STATE = "recall"
Global Const hp871x_FAST_ON = "FAST_ON"
Global Const hp871x_FAST_OFF = "FAST_OFF"
' Global Const hp871x_Q = "?"

' Used by Function hp871x_dir
Global Const hp871x_DIR_DEFAULT = "DEFAULT"
Global Const hp871x_DIR_DISK = "DISK"
Global Const hp871x_DIR_RAM = "RAM"
Global Const hp871x_DIR_NONVOL = "nonvol"

' Used by Function hp871x_dirInfo
' Global Const hp871x_DIR_DEFAULT = "DEFAULT"
' Global Const hp871x_DIR_DISK = "DISK"
' Global Const hp871x_DIR_RAM = "RAM"
' Global Const hp871x_DIR_NONVOL = "nonvol"

' Used by Function hp871x_clock
Global Const hp871x_CLK_YMD = "YMD"
Global Const hp871x_CLK_MDY = "MDY"
Global Const hp871x_CLK_DMY = "DMY"
Global Const hp871x_CLK_ALPHA = "ALPHA"
Global Const hp871x_CLK_NUMERIC = "NUMERIC"
Global Const hp871x_CLK_DATE = "DATE"
Global Const hp871x_CLK_DATE_Q = "DATE?"
Global Const hp871x_CLK_TIME = "TIME"
Global Const hp871x_CLK_TIME_Q = "TIME?"
Global Const hp871x_CLK_SYNC = "SYNC"

' Used by Function hp871x_progControl
Global Const hp871x_PROG_DELETE = "DELETE"
Global Const hp871x_PROG_COMMAND = "COMMAND"
Global Const hp871x_PROG_STOP = "STOP"
Global Const hp871x_PROG_PAUSE = "PAUSE"
Global Const hp871x_PROG_RUN = "RUN"
Global Const hp871x_PROG_CONT = "CONTINUE"
Global Const hp871x_PROG_WAIT = "WAIT"
Global Const hp871x_PROG_STATE_Q = "STATE?"

' Used by Function hp871x_doCal
' hp871x_CH_1
' hp871x_CH_2
' Global Const hp871x_CAL_RESPONSE
' Global Const hp871x_CAL_RESP_ISOL
' Global Const hp871x_CAL_ENH_RESP
' Global Const hp871x_CAL_REFLECTION
' Global Const hp871x_CAL_TWO_PORT

' Used by Function hp871x_readID
Global Const hp871x_MODEL_Q = "MODEL?"
Global Const hp871x_SERIAL_Q = "SERIAL?"
Global Const hp871x_REVISION_Q = "REVISION?"
Global Const hp871x_REV_VALUE_Q = "REV_VALUE?"
Global Const hp871x_MP_ID_Q = "MP_ID?"
Global Const hp871x_MAXFREQ_Q = "MAXFREQ?"
Global Const hp871x_MINFREQ_Q = "MINFREQ?"
Global Const hp871x_ATTEN_Q = "ATTEN?"
Global Const hp871x_LAN_Q = "LAN?"
Global Const hp871x_FAULT_Q = "FAULT?"
Global Const hp871x_SRL_Q = "SRL?"
Global Const hp871x_50_Q = "50?"
Global Const hp871x_75_Q = "75?"
Global Const hp871x_IBASIC_Q = "IBASIC?"
Global Const hp871x_AM_Q = "AM?"


' Used by Function hp871x_saveDefine
' hp871x_ON
' hp871x_OFF
Global Const hp871x_SAVE_CORR = "CORR"
Global Const hp871x_SAVE_CORR_Q = "CORR?"
Global Const hp871x_SAVE_ISTATE = "ISTATE"
Global Const hp871x_SAVE_ISTATE_Q = "ISTATE?"
Global Const hp871x_SAVE_TRACE = "TRACE"
Global Const hp871x_SAVE_TRACE_Q = "TRACE?"
Global Const hp871x_SAVE_FORMAT = "FORMAT"
Global Const hp871x_TOUCHSTONE = "TOUCHSTONE"
Global Const hp871x_LOTUS123 = "LOTUS123"

'   Used by Function hp871x_sweepStep   *****/
' Global Const hp871x_ON
' Global Const hp871x_OFF
' Global Const hp871x_Q


'        ***************************************************
'        *  Instrument specific functions                  *
'        ***************************************************
Declare Function hp871x_preset Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal preset_type As String = "DEFAULT") As Long

Declare Function hp871x_power Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal power As Double, _
     Optional ByVal request As String = "LEVEL", _
     Optional ByVal channel As Long = 1, _
     Optional cur_power As Double = 0) As Long

Declare Function hp871x_frequency Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal freq1 As Double, _
     ByVal freq2 As Double, _
     Optional ByVal request As String = "S/S", _
     Optional ByVal channel As Long = 1, _
     Optional cur_freq1 As Double = 0, _
     Optional cur_freq2 As Double = 0) As Long

Declare Function hp871x_points Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal points As Long, _
     Optional ByVal request As String = "SET", _
     Optional ByVal channel As Long = 1, _
     Optional cur_points As Long = 0) As Long

Declare Function hp871x_average Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal avg_set As Long, _
     Optional ByVal request As String = "FACTOR", _
     Optional ByVal channel As Long = 1, _
     Optional cur_avg As Long = 0) As Long

Declare Function hp871x_trigger Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal request As String = "IMMEDIATE", _
     Optional ByVal channel As Long = 1, _
     Optional trig_status As Long = 0) As Long

Declare Function hp871x_measure Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1, _
     Optional ByVal cur_meas As String = "") As Long

Declare Function hp871x_channel Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal channel As Long, _
     Optional ByVal request As String = "ON", _
     Optional chan_status As Long = 0) As Long
        
Declare Function hp871x_bandwidth Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal bandwidth As Double, _
     Optional ByVal request As String = "SET", _
     Optional ByVal channel As Long = 1, _
     Optional cur_bw As Double = 0) As Long

Declare Function hp871x_scale Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal value As Double, _
     Optional ByVal request As String = "SCALE", _
     Optional ByVal channel As Long = 1, _
     Optional cur_value As Double = 0) As Long

Declare Function hp871x_format Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1, _
     Optional ByVal cur_format As String = "") As Long

Declare Function hp871x_sweepTime Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal swptime As Double, _
     Optional ByVal request As String = "SET", _
     Optional ByVal channel As Long = 1, _
     Optional cur_sweep As Double = 0) As Long

Declare Function hp871x_sweepAlt Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional swpAlt_status As Long = 0) As Long

Declare Function hp871x_powerSweep Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal pwrSwp_val1 As Double = 0, _
     Optional ByVal pwrSwp_val2 As Double = 0, _
     Optional ByVal channel As Long = 1, _
     Optional cur_pwrSwp1 As Double = 0, _
     Optional cur_pwrSwp2 As Double = 0) As Long

Declare Function hp871x_markerSet Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal request As String = "ON", _
     Optional ByVal marker As Long = 1, _
     Optional ByVal mkr_val As Double = 0, _
     Optional ByVal channel As Long = 1) As Long

Declare Function hp871x_markerRead Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     mkr_result As Double, _
     Optional ByVal request As String = "AMPL?", _
     Optional ByVal marker As Long = 1, _
     Optional ByVal channel As Long = 1, _
     Optional mkr_result2 As Double = 0, _
     Optional mkr_result3 As Double = 0, _
     Optional mkr_result4 As Double = 0) As Long

Declare Function hp871x_screen Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal screen_status As String = "") As Long

Declare Function hp871x_triggerSource Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal trig_status As String = "") As Long

Declare Function hp871x_display Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1) As Long

Declare Function hp871x_message Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal request As String = "CLEAR", _
     Optional ByVal msg As String = "Message Not Specified", _
     Optional msg_status As Long = 0) As Long

Declare Function hp871x_spurAvoid Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal spur_status As String = "") As Long

Declare Function hp871x_softkey Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal key As String = "ERASE_SOFTKEYS", _
     Optional ByVal sfky_number As Long = 0) As Long

Declare Function hp871x_refOscillator Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional refOsc_status As Long = 0) As Long

Declare Function hp871x_title Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal title As String = "Not Specified", _
     Optional title_status As Long = 0) As Long

Declare Function hp871x_keyQueue Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal request As String = "CLEAR", _
     Optional queue_status As Long = 0) As Long

Declare Function hp871x_keyRead Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal keytype As String, _
     keycode As Long) As Long

Declare Function hp871x_autozero Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal request As String = "ONCE", _
     Optional az_status As Long = 0) As Long

Declare Function hp871x_calkit Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal port_num As Long = 1, _
     Optional ByVal cur_kit As String = "") As Long

Declare Function hp871x_calMeasure Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1) As Long

Declare Function hp871x_calType Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1) As Long

Declare Function hp871x_calControl Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1, _
     Optional ByVal cal_type As String = "") As Long

Declare Function hp871x_aperture Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal aperture As Double, _
     Optional ByVal request As String = "SET", _
     Optional ByVal channel As Long = 1, _
     Optional cur_aperture As Double = 0) As Long

Declare Function hp871x_takeSweep Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal sweeps As Long = 0) As Long

Declare Function hp871x_traceRead Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     trace As Double, _
     Optional ByVal request As String = "FDATA?", _
     Optional ByVal channel As Long = 1, _
     Optional trace2 As Double = 0) As Long

Declare Function hp871x_traceAvgRead Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     trace_avg As Double, _
     Optional ByVal channel As Long = 1) As Long

Declare Function hp871x_userTTL Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal TTL_status As String = "") As Long

Declare Function hp871x_Z0 Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal impedance As Double, _
     Optional ByVal request As String = "SYSTEM", _
     Optional cur_imp As Double = 0) As Long

Declare Function hp871x_labelsFreq Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1, _
     Optional lblFreq_status As Long = 0) As Long

Declare Function hp871x_labelsUser Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal lbl_value As Double = 0, _
     Optional ByVal label As String = "", _
     Optional ByVal channel As Long = 1, _
     Optional lblUser_status As Long = 0) As Long

Declare Function hp871x_extensions Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal value As Double = 0, _
     Optional cur_extension As Double = 0) As Long

Declare Function hp871x_faultSetup Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1, _
     Optional ByVal cur_fltSetup As String = "") As Long

Declare Function hp871x_faultMeas Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     ByVal fltMeas_value As Double, _
     Optional ByVal channel As Long = 1, _
     Optional cur_fltMeas As Double = 0) As Long

Declare Function hp871x_faultCal Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal fltCal_value As Double = 0, _
     Optional ByVal channel As Long = 1, _
     Optional cur_fltCal As Double = 0) As Long
 
Declare Function hp871x_traceWrite Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     trace As Double, _
     Optional ByVal request As String = "FDATA", _
     Optional ByVal channel As Long = 1, _
     Optional trace2 As Double) As Long

Declare Function hp871x_multiport Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal request As String, _
    Optional ByVal mp1 As Long = 1, _
    Optional ByVal mp2 As Long = 2, _
    Optional ByVal channel As Long = 1, _
    Optional cur_mp1 As Long = 0, _
    Optional cur_mp2 As Long = 0) As Long
    
Declare Function hp871x_print Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    Optional ByVal request As String = "PRINT", _
    Optional ByVal data As String = "", _
    Optional ByVal cur_print As String = "") As Long

Declare Function hp871x_limits Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal request As String, _
    Optional ByVal channel As Long = 1, _
    Optional limit_status As Long = 0) As Long

Declare Function hp871x_limitSet Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal segments As Long, _
    limits As Double, _
    Optional ByVal channel As Long = 1) As Long

Declare Function hp871x_softkeyBegin Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     Optional ByVal key As String = "ERASE_SOFTKEYS", _
     Optional ByVal key_number As Long = 0) As Long
    
Declare Function hp871x_dataPorts Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal port_data As Long, _
    ByVal request As String, _
    Optional cur_data As Long = 0) As Long

Declare Function hp871x_beep Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    Optional ByVal request As String = "DEFAULT") As Long

Declare Function hp871x_memory Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal request As String, _
    Optional ByVal name As String = "", _
    Optional ByVal dest As String = "") As Long

Declare Function hp871x_save Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal save_name As String, _
    Optional ByVal request As String = "STATE") As Long

Declare Function hp871x_recall Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal recall_name As String, _
    Optional ByVal request As String = "RECALL", _
    Optional recall_status As Long = 0) As Long

Declare Function hp871x_dir Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    files As Long, _
    ByVal dir As String, _
    Optional ByVal drive As String = "DEFAULT") As Long

Declare Function hp871x_dirInfo Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal info_name As String, _
    Optional ByVal info As String = "NOT FOUND", _
    Optional ByVal drive As String = "DEFAULT") As Long

Declare Function hp871x_clock Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal request As String, _
    Optional ByVal clock_data As String = "", _
    Optional ByVal cur_clock As String = "") As Long

Declare Function hp871x_progControl Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal request As String, _
    Optional ByVal command As String = "", _
    Optional ByVal prog_status As String = "") As Long

Declare Function hp871x_progVariable Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal name As String, _
    ByVal str_data As String, _
    Optional ByVal cur_str As String = "", _
    Optional ByVal number_data As Double = 0, _
    Optional cur_number As Double = 0) As Long

Declare Function hp871x_progLoad Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal progfile As String) As Long

Declare Function hp871x_doCal Lib "hp871x_32.dll" _
   (ByVal vi As Long, _
    ByVal request As String, _
    abortcal As Long, _
    Optional ByVal channel As Long = 1, _
    Optional ByVal prompt As String = "") As Long

Declare Function hp871x_readID Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal cur_ID As String, _
     Optional ByVal request As String = "MODEL?", _
     Optional ID_status As Double = 0) As Long

Declare Function hp871x_saveDefine Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     ByVal define As String, _
     Optional define_status As Long = 0) As Long

 Declare Function hp871x_stringParse Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal in_out As String, _
     ByVal parsed As String, _
     not_done As Long, _
     Optional ByVal delimiter As String = ",") As Long

Declare Function hp871x_sweepStep Lib "hp871x_32.dll" _
    (ByVal vi As Long, _
     ByVal request As String, _
     Optional ByVal channel As Long = 1, _
     Optional step_status As Long = 0) As Long



'* End of instrument specific declarations *
'*---------------------------------------------------------------------------*

