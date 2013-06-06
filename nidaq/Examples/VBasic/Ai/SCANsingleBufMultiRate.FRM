VERSION 4.00
Begin VB.Form Form1
  Caption = "SCANsingleBufMultiRate"
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
'     SCANsingleBufMultiRate.FRM
' 
'  Description:
'     Read a waveform from three analog input channels at per-channel
'      scan rate divisors of 1:2:4:8 (uses low-level NI-DAQ functions)
'      NOTE: There are quite a few hardware limitations depending on
'      devices when using this example.  Refer to the description for
'      the SCAN_Sequence_Setup function for details.
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     BUF, NCH, BURST, INTTIM, ASYNC, INTTRIG
' 
'  List of key parameters:
'     lTimeout, dSampRate, dScanRate, piScanRateDivVect,
'      pulSampsPerChanVect
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     SCAN_Sequence_Setup, NIDAQErrorHandler, SCAN_Sequence_Retrieve,
'      DAQ_Rate, SCAN_Start, DAQ_Check, SCAN_Sequence_Demux, DAQ_VScale,
'      NIDAQPlotWaveform, DAQ_Clear
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signals to AI channels 1,2,3 and 4. The
'      default analog input mode for the DAQ device will be used.
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
    Dim lTimeout As Long
    Dim iNumMUXBrds As Integer
    Dim iNumChans As Integer
    Dim iChan As Integer
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim dScanRate As Double
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Dim iScanTB As Integer
    Dim uScanInt As Integer
    Dim ulCount As Long
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Static piChanVect(4) As Integer
    Static piGainVect(4) As Integer
    Static piScanRateDivVect(4) As Integer
    Static piScanSeqVect(512) As Integer
    Static pulSampsPerChanVect(4) As Long
    Dim iScansPerSeq As Integer
    Dim iSampsPerSeq As Integer
    Dim iDAQstopped As Integer
    Dim ulNumPtsAcquired As Long
    Static piBuffer(1000) As Integer
    Static pdVoltBuffer(1000) As Double
    Dim iIgnoreWarning As Integer
    Dim i As Long

    iDevice% = 1
    lTimeout& = 180
    iNumChans% = 4
    iChan% = 1
    iGain% = 1
    dSampRate# = 20000.0
    dScanRate# = 1000.0
    ulCount& = 480
    dGainAdjust# = 1.0
    dOffset# = 0.0
    piChanVect%(0) = 1
    piChanVect%(1) = 2
    piChanVect%(2) = 3
    piChanVect%(3) = 4
    piGainVect%(0) = 1
    piGainVect%(1) = 1
    piGainVect%(2) = 1
    piGainVect%(3) = 1
    piScanRateDivVect%(0) = 1
    piScanRateDivVect%(1) = 2
    piScanRateDivVect%(2) = 4
    piScanRateDivVect%(3) = 8

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     HINT: if you want to change the parameters for this example,
'      please make sure that (1) the size of 'piScanSeqVect' is at least
'      'iSampsPerSeq', (2) 'ulCount' must be a multiple of
'      'iSampsPerSeq'. The size of 'piScanSeqVect' has been set to 512
'      in this example to accommodate the MuxGain memory on most DAQ
'      devices.

'     Setup for multiple rate scanning.

    iStatus% = SCAN_Sequence_Setup(iDevice%, iNumChans%, piChanVect%(0), piGainVect%(0), piScanRateDivVect%(0), iScansPerSeq%, iSampsPerSeq%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Sequence_Setup", iIgnoreWarning%)

'     Obtain the scan sequence vector sometime before de-multiplexing
'      acquired data.

    iStatus% = SCAN_Sequence_Retrieve(iDevice%, iSampsPerSeq%, piScanSeqVect%(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Sequence_Retrieve", iIgnoreWarning%)

    iStatus% = DAQ_Rate(dSampRate#, 0, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Rate/SampRate", iIgnoreWarning%)

    iStatus% = DAQ_Rate(dScanRate#, 0, iScanTB%, uScanInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Rate/ScanRate", iIgnoreWarning%)

'     Acquire data from multiple channels using interval scanning (both
'      'dSampRate' and 'dScanRate' are non-zero. NOTE: 'ulCount' must be
'      an integer multiple of 'iSampsPerSeq'.

    iStatus% = SCAN_Start(iDevice%, piBuffer%(0), ulCount&, iSampTB%, uSampInt%, iScanTB%, uScanInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Start", iIgnoreWarning%)

    While ((iDAQstopped% =  0) And (iStatus% =  0))

        iStatus% = DAQ_Check(iDevice%, iDAQstopped%, ulNumPtsAcquired&)

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Check", iIgnoreWarning%)

'     Demultiplex (re-order) acquired data.

    iStatus% = SCAN_Sequence_Demux(iNumChans%, piChanVect%(0), ulCount&, piBuffer%(0), iSampsPerSeq%, piScanSeqVect%(0), pulSampsPerChanVect&(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Sequence_Demux", iIgnoreWarning%)

'     If you have different gains for each channel, you must call this
'      for each channel as well.  The SCAN_Sequence_Demux function gives
'      information that will help you with scaling.  The
'      'pulSampsPerChanVector' array gives a hint as to how the data
'      from each scan is arranged. In this particular example of 4
'      channels (1,2,3,4) with scan rate divisors of 1, 2, 4, and 8, the
'      'pulSampsPerChanVector' array will contain the values 8, 4, 2,
'      and 1. That indicates that the first 8 samples are from chan 1,
'      the next 4 samples are from chan 2, the next 2 samples are from
'      chan 3, and the last sample is from chan 4.  Refer to the
'      SCAN_Sequence_Demux function description for more details.

    iStatus% = DAQ_VScale(iDevice%, iChan%, iGain%, dGainAdjust#, dOffset#, ulCount&, piBuffer%(0), pdVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_VScale", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "The plot shows all channel data in order. ")

'     Plot acquired data

    iRetVal% = NIDAQPlotWaveform(pdVoltBuffer#(0), ulCount&, WFM_DATA_F64)

    Call PrintText(txtStatusBox, "The data is available in 'pdVoltBuffer'. ")

'     CLEANUP - Don't check for errors on purpose.

    iStatus% = DAQ_Clear(iDevice%)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


