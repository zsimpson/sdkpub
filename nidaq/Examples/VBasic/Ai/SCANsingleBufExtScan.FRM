VERSION 4.00
Begin VB.Form Form1
  Caption = "SCANsingleBufExtScan"
  ClientHeight = 3195
  ClientLeft = 1140
  ClientTop = 1515
  ClientWidth = 6360
  Height = 3600
  Left = 1080
  LinkTopic = "Form1"
  ScaleHeight = 3195
  ScaleWidth = 6360
  Top = 1170
  Width = 6480
  Begin VB.CommandButton cmdExit
    Caption = "E&xit"
     Height = 615
     Left = 4680
     TabIndex = 2
     Top = 2520
     Width = 1575
  End
  Begin VB.CommandButton cmdDoOperation
     Caption = "&Do Operation"
     Height = 615
     Left = 2880
     TabIndex = 1
     Top = 2520
     Width = 1575
  End
  Begin VB.TextBox txtStatusBox
     Height = 2295
     Left = 120
     MultiLine = -1          'True
     ScrollBars = 2         'vertical
     TabIndex = 0
     Top = 120
     Width = 6135
  End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
' ********************************************************************
' 
'  Example Program:
'     SCANsingleBufExtScan.FRM
' 
'  Description:
'     Read a waveform from two analog input channels using external scan
'      interval timing but with internal sample timing (uses low-level
'      NI-DAQ functions)
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     BUF, NCH, BURST, EXTTIM, ASYNC, INTTRIG
' 
'  List of key parameters:
'     iExtScan, iScanTB, uScanInt
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DAQ_Config, NIDAQErrorHandler, DAQ_Rate, SCAN_Setup, SCAN_Start,
'      DAQ_Check, NIDAQYield, SCAN_Demux, DAQ_VScale, DAQ_Clear,
'      NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signals to AI channels 1 and 2. The default
'      analog input mode for the DAQ device will be used. Also, connect
'      a digital pulse train to the 'external scan clock' pin. (NOTE:
'      This is NOT the pin labelled "SCANCLK" but instead is a counter
'      output pin.)
' 
'     [For further I/O connection details, please refer to your hardware
'      User Manual.]
' 
'     [For further details on how to run this example, please refer to
'      the NI-DAQ Examples On-Line Help (NIDAQEx.HLP).]
' 
' ********************************************************************
Option Explicit
Option Base 0
' 
' Constant for PrintText 
' 
Const LEN_PRINTTEXT = 4096 


' ************************************************************************
' SUBROUTINE:  PrintText
' DESCRIPTION: PrintText to desired TextBox (upto 4096 characters)
' INPUTS:      txtBox - TextBox to print on
'              strText - Text to print
' ************************************************************************
Sub PrintText(txtBox as TextBox, strText as string)

    txtBox.Text = Right$(txtBox.Text + strText$ + Chr$(13) + Chr$(10), LEN_PRINTTEXT)

    txtBox.SelStart = Len(CStr(txtBox.Text))

    DoEvents

End Sub


' ************************************************************************
' SUBROUTINE:  cmdExit_Click
' DESCRIPTION: Clean up and exit
' ************************************************************************
Sub cmdExit_Click()

    End

End Sub

' ************************************************************************
' SUBROUTINE:  Form_Load
' DESCRIPTION: Gets automatically called at startup
' ************************************************************************
Sub Form_Load()


End Sub


' ************************************************************************
' SUBROUTINE:  cmdDoOperation_Click
' DESCRIPTION: The main NI-DAQ operations are here
' ************************************************************************
Sub cmdDoOperation_Click()

    ' 
    '  Local Variable Declarations: 
    

    Dim iStatus As Integer
    Dim iRetVal As Integer
    Dim iDevice As Integer
    Dim iChan As Integer
    Dim iStartTrig As Integer
    Dim iExtScan As Integer
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim ulCount As Long
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Dim iUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Dim iScanTB As Integer
    Dim uScanInt As Integer
    Static piBuffer(200) As Integer
    Static pdVoltBuffer(200) As Double
    Dim iDAQstopped As Integer
    Dim ulRetrieved As Long
    Dim iNumChans As Integer
    Static piChanVect(2) As Integer
    Static piGainVect(2) As Integer
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iChan% = 1
    iExtScan% = 2
    iGain% = 1
    dSampRate# = 1000.0
    ulCount& = 200
    dGainAdjust# = 1.0
    dOffset# = 0.0
    iNumChans% = 2
    piChanVect%(0) = 1
    piChanVect%(1) = 2
    piGainVect%(0) = 1
    piGainVect%(1) = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Setup for external scan timing with iExtScan = 2.

    iStatus% = DAQ_Config(iDevice%, iStartTrig%, iExtScan%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Config", iIgnoreWarning%)

'     Convert sample rate (S/sec) to appropriate timebase and sample
'      interval values. (NOT scan interval values)

    iStatus% = DAQ_Rate(dSampRate#, iUnits%, iSampTB%, uSampInt%)

    iStatus% = SCAN_Setup(iDevice%, iNumChans%, piChanVect%(0), piGainVect%(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Setup", iIgnoreWarning%)

'     Acquire data

    iStatus% = SCAN_Start(iDevice%, piBuffer%(0), ulCount&, iSampTB%, uSampInt%, iScanTB%, uScanInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Start", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply your external scan timing pulses to the 'external scan clock' pin. ")

    While ((iDAQstopped% <>  1) And (iStatus% =  0))

'         Loop until all acquisition is complete.  HINT: You can be
'          doing other foreground tasks during this time.

        iStatus% = DAQ_Check(iDevice%, iDAQstopped%, ulRetrieved&)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Check", iIgnoreWarning%)

    iStatus% = SCAN_Demux(piBuffer%(0), ulCount&, iNumChans%, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Demux", iIgnoreWarning%)

    iStatus% = DAQ_VScale(iDevice%, iChan%, iGain%, dGainAdjust#, dOffset#, ulCount&, piBuffer%(0), pdVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_VScale", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Set scan timing back to initial state.

    iStatus% = DAQ_Config(iDevice%, 0, 0)

    iStatus% = DAQ_Clear(iDevice%)

    Call PrintText(txtStatusBox, "The plot shows Channel 1 data then Channel 2 data. ")

'     Plot acquired data

    iRetVal% = NIDAQPlotWaveform(pdVoltBuffer#(0), ulCount&, WFM_DATA_F64)

    Call PrintText(txtStatusBox, "The data is available in 'pdVoltBuffer'. ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


