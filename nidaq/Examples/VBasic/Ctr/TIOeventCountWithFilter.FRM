VERSION 4.00
Begin VB.Form Form1
  Caption = "TIOeventCountWithFilter"
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
'     TIOeventCountWithFilter.FRM
' 
'  Description:
'     Counts the number of digital pulses (or events) using a general
'      purpose counter 0 in a loop while using an internal filter set at
'      5uSec (for NI-TIO based devices)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     EVENTCNT, 1PT
' 
'  List of key parameters:
'     ulGpctrNum, ulLineNum, ulCount
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      Line_Change_Attribute, GPCTR_Change_Parameter, GPCTR_Watch,
'      NIDAQYield
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital pulse train to the default source pin (PFI
'      39). Connect the ground reference to the DIG GND pin.
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
    Dim ulLineNum As Long
    Dim ulCount As Long
    Dim ulTCReached As Long
    Dim iLoopCount As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    ulGpctrNum& = ND_COUNTER_0
    ulLineNum& = ND_PFI_39
    ulTCReached& = ND_NO
    iLoopCount& = 100
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

'     Setup for a simple event counting application.

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_SIMPLE_EVENT_CNT)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

'     Setup 5 usec filtering on the input line. You can change this to
'      other filter values.

    iStatus% = Line_Change_Attribute(iDevice%, ulLineNum&, ND_LINE_FILTER, ND_5_MICROSECONDS)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Line_Change_Attribute", iIgnoreWarning%)

'     Specify source input.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SOURCE, ulLineNum&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning%)

'     Load initial count.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_INITIAL_COUNT, ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply your digital pulse train to PFI 39. ")

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

'     Loop 100 times.

    Do 

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_COUNT, ulCount&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch/COUNT", iIgnoreWarning%)

        Call PrintText(txtStatusBox, "The current count is " +  Trim$(Str$(ulCount&)))

        iLoopCount = iLoopCount- 1

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_TC_REACHED, ulTCReached&)

        If (ulTCReached& =  ND_YES) Then

            Call PrintText(txtStatusBox, "Counter reached terminal count! " + "- The count may be incorrect. ")

        End If

        DoEvents

    Loop While ((iLoopCount& >  0) And (iStatus% =  0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Disable filtering.

    iStatus% = Line_Change_Attribute(iDevice%, ulLineNum&, ND_LINE_FILTER, ND_NONE)

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    Call PrintText(txtStatusBox, "Done with event counting with filtering!! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


