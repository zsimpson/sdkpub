VERSION 4.00
Begin VB.Form Form1
  Caption = "TIOquadEncoderPosMeasure"
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
'     TIOquadEncoderPosMeasure.FRM
' 
'  Description:
'     Counts the number of quadrature encoded digital pulses using a
'      general purpose counter 0 in a loop. Also accepts a Z-index pulse
'      so that the counter initializes automatically (for NI-TIO based
'      devices)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     EVENTCNT, 1PT
' 
'  List of key parameters:
'     ulGpctrNum, ulZIndexCount, ulInitCount
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, Line_Change_Attribute, GPCTR_Watch,
'      NIDAQYield
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your encoder channel A signal to the default source pin
'      (PFI 39), the channel B signal to the default auxiliary line (PFI
'      37), and the Z-index pulse signal to the default gate pin (PFI
'      38).  Also, connect the ground reference to the DIG GND pin.
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
    Dim ulGpctrNum As Long
    Dim ulCount As Long
    Dim ulZIndexCount As Long
    Dim ulInitCount As Long
    Dim ulTCReached As Long
    Dim iLoopCount As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    ulGpctrNum& = ND_COUNTER_0
    ulTCReached& = ND_NO
    iLoopCount& = 100
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

'     Setup for a position measurement application.

'     NOTE: If you want to measure speed at the same time, you must
'      timestamp each reading at the exact moment you take a quadrature
'      encoded position measurement. By determining the position change
'      from the previous measurement and the time difference since the
'      previous measurement, you can calculate the speed.

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_POSITION_MSR)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

'     Setup the encoder type for Quadrature Encoder (X1) measurement.
'      You can change this to X2 or X4 if you wish.

    Call GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_ENCODER_TYPE, ND_QUADRATURE_ENCODER_X1)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/QUADRATURE_ENCODER_X1", iIgnoreWarning%)

'     Activate a Z-index pulse to reset the counter to an initial value,
'      specified by 'ulCount' later.

    Call GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_Z_INDEX_ACTIVE, ND_YES)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/Z_INDEX_PULSE", iIgnoreWarning%)

'     Specify the value that gets loaded when a Z-index pulse arrives.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_Z_INDEX_VALUE, ulZIndexCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/Z-INDEX_COUNT", iIgnoreWarning%)

'     Load initial count.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_INITIAL_COUNT, ulInitCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning%)

'     Signals from quadrature encoders often have noise and glitches
'      that result in measurement errors. Setup 5 usec filtering on each
'      input from the quadrature encoder.

'     Setup filter for Channel A.

    iStatus% = Line_Change_Attribute(iDevice%, ND_PFI_39, ND_LINE_FILTER, ND_5_MICROSECONDS)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Line_Change_Attribute/ND_PFI_39", iIgnoreWarning%)

'     Setup filter for Channel B.

    iStatus% = Line_Change_Attribute(iDevice%, ND_PFI_37, ND_LINE_FILTER, ND_5_MICROSECONDS)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Line_Change_Attribute/ND_PFI_37", iIgnoreWarning%)

'     Setup filter for Z-index Channel.

    iStatus% = Line_Change_Attribute(iDevice%, ND_PFI_38, ND_LINE_FILTER, ND_5_MICROSECONDS)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Line_Change_Attribute/ND_PFI_38", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Connect the encoder Channel A signal to PFI 39. ")

    Call PrintText(txtStatusBox, "Connect the encoder Channel B signal to PFI 37. ")

    Call PrintText(txtStatusBox, "Connect the Z-index signal to PFI 38. ")

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

'     Loop 100 times.

    Do 

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_COUNT, ulCount&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch/COUNT", iIgnoreWarning%)

        If (iStatus% =  0) Then

            Call PrintText(txtStatusBox, "Current encoder position is at " +  Trim$(Str$(ulCount&)))

        End If

        iLoopCount = iLoopCount- 1

        DoEvents

    Loop While ((iLoopCount& >  0) And (iStatus% =  0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Clear filter settings.

    iStatus% = Line_Change_Attribute(iDevice%, ND_PFI_39, ND_LINE_FILTER, ND_NONE)

    iStatus% = Line_Change_Attribute(iDevice%, ND_PFI_37, ND_LINE_FILTER, ND_NONE)

    iStatus% = Line_Change_Attribute(iDevice%, ND_PFI_38, ND_LINE_FILTER, ND_NONE)

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    Call PrintText(txtStatusBox, "Done with quadrature encoded position measurement! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


