VERSION 4.00
Begin VB.Form Form1
  Caption = "DAQsingleBufExtTrig"
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
'     DAQsingleBufExtTrig.FRM
' 
'  Description:
'     Read a waveform from one analog input channel upon an external
'      digital trigger using internal timing (uses low-level NI-DAQ
'      functions)
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     BUF, 1CH, BURST, INTTIM, ASYNC, EXTTRIG
' 
'  List of key parameters:
'     iStartTrig, iSampTB
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DAQ_Config, NIDAQErrorHandler, DAQ_Rate, DAQ_Start, DAQ_Check,
'      NIDAQYield, DAQ_VScale, DAQ_Clear, NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signal to AI channel 1. The default analog
'      input mode for the DAQ device will be used. Also, connect a
'      digital pulse (falling edge for most DAQ devices) to the
'      'external start trigger' pin, and the ground reference to DIG
'      GND.
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
    Dim iExtConv As Integer
    Dim iGain As Integer
    Dim ulCount As Long
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Dim dSampRate As Double
    Dim iUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Static piBuffer(100) As Integer
    Static pdVoltBuffer(100) As Double
    Dim iDAQstopped As Integer
    Dim ulRetrieved As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iChan% = 1
    iStartTrig% = 1
    iGain% = 1
    ulCount& = 100
    dGainAdjust# = 1.0
    dOffset# = 0.0
    dSampRate# = 1000.0
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Setup for external start trigger with iStartTrig = 1.

    iStatus% = DAQ_Config(iDevice%, iStartTrig%, iExtConv%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Config", iIgnoreWarning%)

'     Convert sample rate (S/sec) to appropriate timebase and sample
'      interval values.

'     NOTE: If you are using a DSA device, call DAQ_Set_Clock instead.
'      Refer to NI-DAQ Function Reference Manual for details.

    iStatus% = DAQ_Rate(dSampRate#, iUnits%, iSampTB%, uSampInt%)

'     Acquire data from a single channel upon a digital start trigger

'     NOTE FOR DSA devices... DSA devices can format samples in a
'      left-justified format in 32-bit data words. This means that the
'      most significant bits of the data word contain the bits generated
'      by the converter. When allocating data buffers, be sure to
'      account for the 32-bit data width. Even though a number of
'      DAQ/SCAN/WFM functions are declared to accept pointers to 16-bit
'      data buffers, you should pass pointers to 32-bit data buffers.
'      Also, modify the iGain parameter to be in units of dB.

    iStatus% = DAQ_Start(iDevice%, iChan%, iGain%, piBuffer%(0), ulCount&, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Start", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply your external trigger pulse to the 'external trigger' pin. ")

    While ((iDAQstopped% <>  1) And (iStatus% =  0))

'         Loop until all acquisition is complete.  HINT: You can be
'          doing other foreground tasks during this time.

        iStatus% = DAQ_Check(iDevice%, iDAQstopped%, ulRetrieved&)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Check", iIgnoreWarning%)

    iStatus% = DAQ_VScale(iDevice%, iChan%, iGain%, dGainAdjust#, dOffset#, ulCount&, piBuffer%(0), pdVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_VScale", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Set triggering mode back to initial state.

    iStatus% = DAQ_Config(iDevice%, 0, 0)

    iStatus% = DAQ_Clear(iDevice%)

'     Plot acquired data

    iRetVal% = NIDAQPlotWaveform(pdVoltBuffer#(0), ulCount&, WFM_DATA_F64)

    Call PrintText(txtStatusBox, "The data is available in 'pdVoltBuffer'. ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


