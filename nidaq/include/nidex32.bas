'************************************************************************
'* TITLE:       NIDEx32.bas
'*              Header for supporting code module for NI-DAQ Examples
'*              (32-bit Visual Basic version)
'*
'* DESCR:       This header file is to be used with any NI-DAQ example
'*              program.
'*
'* Copyright (c) 1997, National Instruments Corp.  All rights reserved.
'************************************************************************/

' NOTE: must also use nidaq32.bas
'       and nidaqcns.bas

'*
'* Constants
'*

'* for 'lType'
Global Const WFM_DATA_U8 = 0
Global Const WFM_DATA_I16 = 2
Global Const WFM_DATA_F64 = 4
Global Const WFM_DATA_U32 = 7

'* internal constants - change if needed...
Global Const WFM_PERIODS = 10
Global Const WFM_MIN_PTS_IN_PERIOD = 2
Global Const WFM_U8_MODULO = 256
Global Const WFM_I16_AMPL = 2047
Global Const WFM_F64_AMPL = 4.99


'* error return codes for NIDAQPlotWaveform and NIDAQMakeBuffer
'* these error codes are consistent with CVI error codes
Global Const NIDAQEX_INVALID_BUFFER = -12
Global Const NIDAQEX_INVALID_NUMPTS = -14
Global Const NIDAQEX_INVALID_TYPE = -53


'*
'* Function prototypes
'*

Declare Function NIDAQPlotWaveform Lib "nidex32.dll" (pvBuffer as Any, ByVal lNumPts&, ByVal lType&) as Integer
Declare Function NIDAQMakeBuffer Lib "nidex32.dll" (pvBuffer as Any, ByVal lNumPts&, ByVal lType&) as Integer
Declare Function NIDAQErrorHandler Lib "nidex32.dll" (ByVal iStatus%, ByVal strFuncName$, ByVal iIgnoreWarning%) as Integer
Declare Function NIDAQDelay Lib "nidex32.dll" (ByVal dSec#) as Integer
Declare Function NIDAQYield Lib "nidex32.dll" (ByVal iYieldMode%) as Integer
Declare Function NIDAQMean Lib "nidex32.dll" (pvBuffer as Any, ByVal lNumPts&, ByVal lType&, dMean#) as Integer
Declare Function NIDAQWaitForKey Lib "nidex32.dll" (ByVal dTimeLimit#) as Integer

