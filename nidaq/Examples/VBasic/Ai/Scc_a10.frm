VERSION 4.00
Begin VB.Form Form1
  Caption = "SCC_A10"
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
'     SCC_A10.FRM
' 
'  Description:
'     Use the SCC-A10 module with an E-series device to measure a
'      voltage signal attenuated by a factor of 10. (Requires an SCC
'      carrier, such as the SC-2345, and the SCC-A10 signal conditioning
'      component)
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     BUF, 1CH, SYNC, INTTIM, ESER
' 
'  List of key parameters:
'     lTimeout, iInputMode, iInputRange, iPolarity, dSampRate
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     Timeout_Config, NIDAQErrorHandler, AI_Configure, DAQ_Op,
'      DAQ_VScale, NIDAQMean, NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect the signal to the SCC-A10 in the channel 0 slot.
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
    Dim iInputMode As Integer
    Dim iInputRange As Integer
    Dim iPolarity As Integer
    Dim iDriveAIS As Integer
    Dim iChan As Integer
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim ulCount As Long
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Static piBuffer(30) As Integer
    Static pdVoltBuffer(30) As Double
    Dim dAvgVoltage As Double
    Dim iIgnoreWarning As Integer
    Dim i As Long

    iDevice% = 1
    lTimeout& = 180
    iInputMode% = 2
    iInputRange% = 20
    iGain% = 1
    dSampRate# = 300.0
    ulCount& = 30
    dGainAdjust# = 1.0
    dOffset# = 0.0
    dAvgVoltage# = 0.0

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the DAQ_Op call.

    iStatus% = Timeout_Config(iDevice%, lTimeout&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

    iStatus% = AI_Configure(iDevice%, iChan%, iInputMode%, iInputRange%, iPolarity%, iDriveAIS%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AI_Configure", iIgnoreWarning%)

'     Acquire data from a single channel.

    iStatus% = DAQ_Op(iDevice%, iChan%, iGain%, piBuffer%(0), ulCount&, dSampRate#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Op", iIgnoreWarning%)

'     The attenuation on the SCC-A10 is compensated internally in
'      DAQ_VScale, provided that you have configured your SCC-A10 in the
'      NI-DAQ Configuration Utility. If you have not configured your
'      SCC-A10 in the NI-DAQ Configuration Utility, the scaled data will
'      be off by a factor of 10.

    iStatus% = DAQ_VScale(iDevice%, iChan%, iGain%, dGainAdjust#, dOffset#, ulCount&, piBuffer%(0), pdVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_VScale", iIgnoreWarning%)

    iRetVal% = NIDAQMean(pdVoltBuffer#(0), ulCount&, WFM_DATA_F64, dAvgVoltage#)

    Call PrintText(txtStatusBox, "The plot shows all channel data in order. ")

'     Plot acquired data

    iRetVal% = NIDAQPlotWaveform(pdVoltBuffer#(0), ulCount&, WFM_DATA_F64)

    Call PrintText(txtStatusBox, "The average voltage reading is " +  Trim$(Str$(dAvgVoltage#)) + "V. ")

'     Disable timeouts.

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


