VERSION 4.00
Begin VB.Form Form1
  Caption = "TIOtwoEdgeSeparationMeasure"
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
'     TIOtwoEdgeSeparationMeasure.FRM
' 
'  Description:
'     Counts the number of digital pulses (or events) between two
'      independent gate pulses (gate and auxiliary line) using an
'      internal 100kHz timebase (for NI-TIO based devices)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     EVENTCNT, 1PT
' 
'  List of key parameters:
'     ulGpctrNum, ulCount, ulArmed, ulTCReached
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, GPCTR_Watch, NIDAQYield
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital START pulse to the default AUXILIARY line
'      (PFI 37 for 660x devices) and your digital STOP pulse to default
'      GATE pin (PFI 38 for 660x devices). Connect the ground reference
'      to the DIG GND pin.
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
    Dim iLoopCount As Integer
    Dim ulInitCount As Long
    Dim ulArmed As Long
    Dim ulTCReached As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    ulGpctrNum& = ND_COUNTER_0
    iLoopCount% = 10
    ulArmed& = ND_YES
    ulTCReached& = ND_NO
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

'     Setup for a two-signal (non-buffered) edge separation measurement
'      application.

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_TWO_SIGNAL_EDGE_SEPARATION_MSR)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

'     If you want to use a different GPCTR source, change the last
'      parameter in the following function.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SOURCE, ND_INTERNAL_100_KHZ)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning%)

'     Setup the START pulse input.  You must change the last parameter
'      if you use a counter other than 0.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_AUX_LINE, ND_PFI_37)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/AUXLINE", iIgnoreWarning%)

'     Setup the STOP pulse input.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_GATE, ND_DEFAULT_PFI_LINE)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/GATE", iIgnoreWarning%)

'     Load initial count.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_INITIAL_COUNT, ulInitCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply your digital START pulse to PFI 37. ")

    Call PrintText(txtStatusBox, "And then apply your digital STOP pulse to PFI 38. ")

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

'     Loop until 'ulGpctrNum' is no longer armed.

    Do 

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_ARMED, ulArmed&)

        DoEvents

    Loop While ((ulArmed& =  ND_YES) And (iStatus% =  0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch/ARMED", iIgnoreWarning%)

    iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_COUNT, ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch/COUNT", iIgnoreWarning%)

    iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_TC_REACHED, ulTCReached&)

    If (ulTCReached& =  ND_YES) Then

        Call PrintText(txtStatusBox, "Counter reached terminal count! " + "- The count may be incorrect. ")

    Else

        Call PrintText(txtStatusBox, "The period in between the two gate pulses (in 10uSec ticks) was " +  Trim$(Str$(ulCount&)))

    End If

'     CLEANUP - Don't check for errors on purpose.

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


