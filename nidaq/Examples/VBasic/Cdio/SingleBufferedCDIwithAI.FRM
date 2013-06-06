VERSION 4.00
Begin VB.Form Form1
  Caption = "SingleBufferedCDIwithAI"
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
'     SingleBufferedCDIwithAI.FRM
' 
'  Description:
'     Correlates a single buffer of digital input with analog input.
' 
'  Example Category:
'     CDIO
' 
'  Example Task Types:
'     BUF, NCH, INTTIM
' 
'  List of key parameters:
'     ulCount, iAIChan, dSampRate, iDIReqSource
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DIG_Line_Config, NIDAQErrorHandler, DIG_Grp_Config, DIG_Grp_Mode,
'      DIG_Block_PG_Config, DAQ_Rate, DIG_Block_In, DAQ_Start,
'      DAQ_Check, NIDAQYield, DAQ_VScale, DAQ_Clear, NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital input signals to pins DIO0-7. Connect the
'      ground reference to the DIG GND pin. Connect your analog signal
'      to the AI channel 0 I/O pin. (please refer to your hardware user
'      manual for details)
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
    Dim iPGmodeOn As Integer
    Dim ulCount As Long
    Dim iLineCount As Integer
    Dim iGroupSize As Integer
    Dim iPort As Integer
    Dim iNumLines As Integer
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim iAIChan As Integer
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim iAIUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Static piAIBuffer(1000) As Integer
    Static pdAIVoltBuffer(1000) As Double
    Dim iDAQStopped As Integer
    Dim ulPtsTfr As Long
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Static iDIBuffer(500) As Integer
    Dim iDIGroup As Integer
    Dim iDIReqSource As Integer
    Dim iInLineDirection As Integer
    Dim iInGroupDirection As Integer
    Dim iDIEdge As Integer
    Dim i As Long

    iDevice% = 1
    iPGmodeOn% = 1
    ulCount& = 1000
    iGroupSize% = 1
    iNumLines% = 8
    iYieldON% = 1
    iGain% = 1
    dSampRate# = 1000
    dGainAdjust# = 1.0
    dOffset# = 0.0
    iDIGroup% = 1
    iDIReqSource% = 9
    iInLineDirection% = 4

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Configure the digital lines for the correct direction.

    While (iLineCount% <  iNumLines%)

        iStatus% = DIG_Line_Config(iDevice%, iPort%, iLineCount%, iInLineDirection%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Line_Config", iIgnoreWarning%)

        iLineCount = iLineCount+ 1

    Wend

'     Configure Digital Input

    iStatus% = DIG_Grp_Config(iDevice%, iDIGroup%, iGroupSize%, iPort%, iInGroupDirection%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Grp_Config", iIgnoreWarning%)

    iStatus% = DIG_Grp_Mode(iDevice%, iDIGroup%, 0, iDIEdge%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Grp_Mode", iIgnoreWarning%)

'     Correlate the input to the Analog Input Scan Clock.

    iStatus% = DIG_Block_PG_Config(iDevice%, iDIGroup%, iPGmodeOn%, iDIReqSource%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Block_PG_Config", iIgnoreWarning%)

'     Configure Analog Input

    iStatus% = DAQ_Rate(dSampRate#, iAIUnits%, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Rate", iIgnoreWarning%)

'     Start acquiring data.

    iStatus% = DIG_Block_In(iDevice%, iDIGroup%, iDIBuffer%(0), ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_In", iIgnoreWarning%)

    iStatus% = DAQ_Start(iDevice%, iAIChan%, iGain%, piAIBuffer%(0), ulCount&, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Start", iIgnoreWarning%)

    While ((iDAQStopped% <>  1) And (iStatus% =  0))

'         Loop until the acquisition is complete.  HINT: You can be
'          doing other foreground tasks during this time.

        iStatus% = DAQ_Check(iDevice%, iDAQStopped%, ulPtsTfr&)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Check", iIgnoreWarning%)

    iStatus% = DAQ_VScale(iDevice%, iAIChan%, iGain%, dGainAdjust#, dOffset#, ulCount&, piAIBuffer%(0), pdAIVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_VScale", iIgnoreWarning%)

'     Clear all operations and reset the board to its default state

    iStatus% = DAQ_Clear(iDevice%)

    iStatus% = DIG_Grp_Config(iDevice%, iDIGroup%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Digital data available in iDIBuffer. ")

    Call PrintText(txtStatusBox, "Analog data available in pdAIVoltBuffer. ")

    iRetVal% = NIDAQPlotWaveform(pdAIVoltBuffer#(0), ulCount&, WFM_DATA_F64)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


