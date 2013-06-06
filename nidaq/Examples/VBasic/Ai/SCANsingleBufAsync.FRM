VERSION 4.00
Begin VB.Form Form1
  Caption = "SCANsingleBufAsync"
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
'     SCANsingleBufAsync.FRM
' 
'  Description:
'     Read a waveform from two analog input channels using internal
'      timing (uses low-level NI-DAQ functions)
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     BUF, NCH, BURST, ASYNC, INTTRIG
' 
'  List of key parameters:
'     iScanTB, uScanInt
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DAQ_Rate, SCAN_Setup, NIDAQErrorHandler, SCAN_Start, DAQ_Check,
'      NIDAQYield, SCAN_Demux, DAQ_VScale, DAQ_Clear, NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signals to AI channels 1 and 2. The default
'      analog input mode for the DAQ device will be used.
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
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim dScanRate As Double
    Dim ulCount As Long
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Dim iUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Dim iScanTB As Integer
    Dim uScanInt As Integer
    Static piBuffer(1000) As Integer
    Static pdVoltBuffer(1000) As Double
    Dim iDAQstopped As Integer
    Dim ulRetrieved As Long
    Dim iNumMUXBrds As Integer
    Dim iNumChans As Integer
    Static piChanVect(2) As Integer
    Static piGainVect(2) As Integer
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iChan% = 1
    iGain% = 1
    dSampRate# = 10000.0
    dScanRate# = 1000.0
    ulCount& = 1000
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

'     Convert sample rate (S/sec) to appropriate timebase and sample
'      interval values. (NOT scan interval values)

'     NOTE: If you are using a DSA device, call DAQ_Set_Clock instead.
'      Refer to NI-DAQ Function Reference Manual for details.

    iStatus% = DAQ_Rate(dSampRate#, iUnits%, iSampTB%, uSampInt%)

'     Convert scan rate rate (S/sec) to appropriate timebase and sample
'      interval values. (NOT scan interval values)

'     NOTE: If you are using a DSA device, call DAQ_Set_Clock instead.
'      Refer to NI-DAQ Function Reference Manual for details.

    iStatus% = DAQ_Rate(dScanRate#, iUnits%, iScanTB%, uScanInt%)

'     HINT: If you are using a Lab or 1200 series device, skip the
'      SCAN_Setup function.

'     NOTE FOR DSA devices... Modify the elements in piGainVect to be in
'      units of dB. Refer to NI-DAQ Function Reference Manual for
'      details.

    iStatus% = SCAN_Setup(iDevice%, iNumChans%, piChanVect%(0), piGainVect%(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Setup", iIgnoreWarning%)

'     Acquire data from multiple channels.

'     HINT: If you are using a Lab or 1200 series device, replace this
'      function with Lab_ISCAN_Start.

'     NOTE FOR DSA devices... DSA devices can format samples in a
'      left-justified format in 32-bit data words. This means that the
'      most significant bits of the data word contain the bits generated
'      by the converter. When allocating data buffers, be sure to
'      account for the 32-bit data width. Even though a number of
'      DAQ/SCAN/WFM functions are declared to accept pointers to 16-bit
'      data buffers, you should pass pointers to 32-bit data buffers.

    iStatus% = SCAN_Start(iDevice%, piBuffer%(0), ulCount&, iSampTB%, uSampInt%, iScanTB%, uScanInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Start", iIgnoreWarning%)

    While ((iDAQstopped% <>  1) And (iStatus% =  0))

'         Loop until all acquisition is complete.  HINT: You can be
'          doing other foreground tasks during this time.

'         HINT: If you are using a Lab or 1200 series device, replace
'          this with the Lab_ISCAN_Check function.

        iStatus% = DAQ_Check(iDevice%, iDAQstopped%, ulRetrieved&)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Check", iIgnoreWarning%)

'     NOTE FOR DSA devices... The SCAN_Demux function is not supported
'      for DSA devices. If you are using a DSA device, skip the
'      SCAN_Demux function and please index into the data array
'      manually.

    iStatus% = SCAN_Demux(piBuffer%(0), ulCount&, iNumChans%, iNumMUXBrds%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Demux", iIgnoreWarning%)

    iStatus% = DAQ_VScale(iDevice%, iChan%, iGain%, dGainAdjust#, dOffset#, ulCount&, piBuffer%(0), pdVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_VScale", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

    iStatus% = DAQ_Clear(iDevice%)

    Call PrintText(txtStatusBox, "The plot shows Channel 1 data then Channel 2 data. ")

'     Plot acquired data

    iRetVal% = NIDAQPlotWaveform(pdVoltBuffer#(0), ulCount&, WFM_DATA_F64)

    Call PrintText(txtStatusBox, "The data is available in 'pdVoltBuffer'. ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


