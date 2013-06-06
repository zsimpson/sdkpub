VERSION 4.00
Begin VB.Form Form1
  Caption = "SCXI_FREQonePoint"
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
'     SCXI_FREQonePoint.FRM
' 
'  Description:
'     Read one channel, one point at a time, immediately from an
'      SCXI-1126 frequency input module.  This example adds special
'      function calls to set input frequency range, cutoff frequency and
'      voltage threshold (2.1V for TTL). (Only for the SCXI-1126 module)
' 
'  Example Category:
'     SCXI
' 
'  Example Task Types:
'     BUF, 1CH, IMMED, FREQM
' 
'  List of key parameters:
'     iOnDevChan, iChassisID, iModuleSlot, iModuleChan, dSCXIfreqRange,
'      dThreshHold, dHysteresis, iFilterMode, dFilterFreq
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     SCXI_Load_Config, NIDAQErrorHandler, SCXI_Single_Chan_Setup,
'      SCXI_Set_Gain, SCXI_Configure_Filter, SCXI_Set_Threshold, DAQ_Op,
'      SCXI_Scale, NIDAQPlotWaveform, NIDAQMean
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signal to channel 0 of your SCXI module in
'      chassis 1, slot 1.  Make sure the connection to your DAQ device
'      is setup correctly.
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
    Dim iOnDevChan As Integer
    Dim iOnDevGain As Integer
    Dim ulCount As Long
    Static piReadings(100) As Integer
    Dim iChassisID As Integer
    Dim iModuleSlot As Integer
    Dim iModuleChan As Integer
    Dim dSCXIfreqRange As Double
    Dim dTermBlockGain As Double
    Static pdSCXIfrequencies(100) As Double
    Dim dSCXIavgFrequency As Double
    Dim dThreshHold As Double
    Dim dHysteresis As Double
    Dim iIgnoreWarning As Integer
    Dim iFilterMode As Integer
    Dim dFilterFreq As Double
    Dim uCutoffDivDown As Integer
    Dim uOutClkDivDown As Integer
    Dim dActualFilterFreq As Double
    Dim dSampRate As Double
    Dim i As Long

    iDevice% = 1
    iOnDevGain% = 1
    ulCount& = 100
    iChassisID% = 1
    iModuleSlot% = 1
    dSCXIfreqRange# = 1000.0
    dTermBlockGain# = 1.0
    dSCXIavgFrequency# = 0.0
    dThreshHold# = 2.1
    dHysteresis# = 0.1
    iFilterMode% = 1
    dFilterFreq# = 1.0
    dSampRate# = 1000.0

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = SCXI_Load_Config(iChassisID%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Load_Config", iIgnoreWarning%)

'     Specify SCXI module and channel to sample.

    iStatus% = SCXI_Single_Chan_Setup(iChassisID%, iModuleSlot%, iModuleChan%, iDevice%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Single_Chan_Setup", iIgnoreWarning%)

'     Specify input frequency range using SCXI_Set_Gain.

    iStatus% = SCXI_Set_Gain(iChassisID%, iModuleSlot%, iModuleChan%, dSCXIfreqRange#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Set_Gain", iIgnoreWarning%)

'     Set up cutoff frequency for the filter on the freq-to-voltage
'      module.  You can only use iFilterMode = 1.

    iStatus% = SCXI_Configure_Filter(iChassisID%, iModuleSlot%, iModuleChan%, iFilterMode%, dFilterFreq#, uCutoffDivDown%, uOutClkDivDown%, dActualFilterFreq#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Configure_Filter", iIgnoreWarning%)

'     Specify voltage threshold for freq-to-voltage converter. The
'      threshold setting determines what the freq-to-voltage converter
'      regards as another pulse.

    iStatus% = SCXI_Set_Threshold(iChassisID%, iModuleSlot%, iModuleChan%, dThreshHold#, dHysteresis#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Set_Threshold", iIgnoreWarning%)

'     Acquire data into binary array.

    iStatus% = DAQ_Op(iDevice%, iOnDevChan%, iOnDevGain%, piReadings%(0), ulCount&, dSampRate#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Op", iIgnoreWarning%)

'     Scale binary data to frequency values.

    iStatus% = SCXI_Scale(iChassisID%, iModuleSlot%, iModuleChan%, dSCXIfreqRange#, dTermBlockGain#, iDevice%, iOnDevChan%, iOnDevGain%, ulCount&, piReadings%(0), pdSCXIfrequencies#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Scale", iIgnoreWarning%)

    iRetVal% = NIDAQPlotWaveform(pdSCXIfrequencies#(0), ulCount&, WFM_DATA_F64)

    Call NIDAQMean(pdSCXIfrequencies#(0), ulCount&, WFM_DATA_F64, dSCXIavgFrequency#)

    Call PrintText(txtStatusBox, "The average frequency " + "is " +  Trim$(Str$(dSCXIavgFrequency#)) + "Hz. ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


