VERSION 4.00
Begin VB.Form Form1
  Caption = "CDISinglePointClockedByCounter"
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
'     CDISinglePointClockedByCounter.FRM
' 
'  Description:
'     Reads digital data from the input FIFO one point at a time at a
'      rate of 100 Hz.  The 100 Hz clock used here is supplied by
'      general purpose counter 0.
' 
'  Example Category:
'     CDIO
' 
'  Example Task Types:
'     1PT, NCH
' 
'  List of key parameters:
'     ulCount, iDIReqSource, ulGpctrNum, ulGpctrOutput, ulLOWcount,
'      ulHIGHcount
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DIG_Line_Config, NIDAQErrorHandler, DIG_Grp_Config, DIG_Grp_Mode,
'      DIG_Block_PG_Config, Select_Signal, GPCTR_Control,
'      GPCTR_Set_Application, GPCTR_Change_Parameter, DIG_Grp_Status,
'      DIG_In_Grp
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital input signals to pins DIO0-7. Connect the
'      ground reference to the DIG GND pin. (please refer to your
'      hardware user manual for details)
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
    Dim ulCount As Long
    Dim ulLoopCount As Long
    Dim iLineCount As Integer
    Dim iGroupSize As Integer
    Dim iPort As Integer
    Dim iNumLines As Integer
    Dim iIgnoreWarning As Integer
    Dim iReady As Integer
    Dim iPGmodeOn As Integer
    Dim iDIGroup As Integer
    Dim iDIReqSource As Integer
    Dim iInLineDirection As Integer
    Dim iInGroupDirection As Integer
    Dim iDIEdge As Integer
    Dim iDataPoint As Integer
    Dim ulGpctrNum As Long
    Dim ulGpctrOutput As Long
    Dim ulLOWcount As Long
    Dim ulHIGHcount As Long

    iDevice% = 1
    ulCount& = 500
    iGroupSize% = 1
    iNumLines% = 8
    iPGmodeOn% = 1
    iDIGroup% = 1
    iDIReqSource% = 3
    iInLineDirection% = 4
    ulGpctrNum& = ND_COUNTER_0
    ulGpctrOutput& = ND_GPCTR0_OUTPUT
    ulLOWcount& = 500
    ulHIGHcount& = 500

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

'     Correlate the input to the signal coming across the RTSI 0 line.

    iStatus% = DIG_Block_PG_Config(iDevice%, iDIGroup%, iPGmodeOn%, iDIReqSource%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Block_PG_Config", iIgnoreWarning%)

'     Route the output of GPCTR0 to RTSI 0

    iStatus% = Select_Signal(iDevice%, ND_RTSI_0, ND_GPCTR0_OUTPUT, ND_DONT_CARE)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal", iIgnoreWarning%)

'     Setup counter 0 to output a 100 Hz square wave.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_PULSE_TRAIN_GNR)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SOURCE, ND_INTERNAL_100_KHZ)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNT_1, ulLOWcount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/COUNT1", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNT_2, ulHIGHcount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning%)

'     To output a counter pulse, you must call Select_Signal.

    iStatus% = Select_Signal(iDevice%, ulGpctrOutput&, ulGpctrOutput&, ND_LOW_TO_HIGH)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal/GpctrOutput", iIgnoreWarning%)

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Square wave generation started... ")

'     Input ulCount number of points.

    While ((ulLoopCount& <  ulCount&) And (iStatus% =  0))

        iStatus% = DIG_Grp_Status(iDevice%, iDIGroup%, iReady%)

        If ((iReady% =  1) And (iStatus% =  0)) Then

            iStatus% = DIG_In_Grp(iDevice%, iDIGroup%, iDataPoint%)

            iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_In_Grp", 0)

            ulLoopCount; = ulLoopCount;+ 1

        End If

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Status", 0)

    Wend

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

'     Disconnect GPCTR0_OUTPUT.

    iStatus% = Select_Signal(iDevice%, ND_GPCTR0_OUTPUT, ND_NONE, ND_DONT_CARE)

'     Remove any signal from RTSI 0.

    iStatus% = Select_Signal(iDevice%, ND_RTSI_0, ND_NONE, ND_DONT_CARE)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal", iIgnoreWarning%)

'     Clear all operations and reset the board to its default state

    iStatus% = DIG_Grp_Config(iDevice%, iDIGroup%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


