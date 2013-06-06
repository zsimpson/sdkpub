VERSION 4.00
Begin VB.Form Form1
  Caption = "TIOgenSquareWaveStartTrig"
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
'     TIOgenSquareWaveStartTrig.FRM
' 
'  Description:
'     Generates a 1kHz squarewave (digital pulse train) using general
'      purpose counter 0 and an internal 100kHz timebase upon a digital
'      start trigger (for NI-TIO based devices)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     PLSTRN, INTTIM, EXTTRIG
' 
'  List of key parameters:
'     ulLineNum, ulGpctrNum, ulGpctrOutput, ulLOWcount, ulHIGHcount
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, Select_Signal, NIDAQDelay
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your start trigger on PFI 37. Connect the ground reference
'      to the DIG GND pin. Your digital pulse train will be on the
'      counter's default output pin (PFI 36).
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
    Dim ulLineNum As Long
    Dim ulGpctrNum As Long
    Dim ulGpctrOutput As Long
    Dim ulLOWcount As Long
    Dim ulHIGHcount As Long
    Dim ulLoopCount As Long
    Dim iIgnoreWarning As Integer

    iDevice% = 1
    ulLineNum& = ND_PFI_37
    ulGpctrNum& = ND_COUNTER_0
    ulGpctrOutput& = ND_GPCTR0_OUTPUT
    ulLOWcount& = 50
    ulHIGHcount& = 50

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_PULSE_TRAIN_GNR)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

'     If you want to use a different GPCTR source, change the last
'      parameter in the following function.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SOURCE, ND_INTERNAL_100_KHZ)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning%)

'     Load the low count for the square wave.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNT_1, ulLOWcount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/COUNT1", iIgnoreWarning%)

'     Load the high count for the square wave.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNT_2, ulHIGHcount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning%)

'     Connect the IO Connector line PFI 37 to the internal start
'      trigger.

    iStatus% = Select_Signal(iDevice%, ND_START_TRIGGER, ulLineNum&, ND_LOW_TO_HIGH)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal/START_TRIGGER", iIgnoreWarning%)

'     Enable the start trigger for the counter.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_START_TRIGGER, ND_ENABLED)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/START_TRIGGER", iIgnoreWarning%)

'     Enable GPCTR output.

    iStatus% = Select_Signal(iDevice%, ulGpctrOutput&, ulGpctrOutput&, ND_LOW_TO_HIGH)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal/GpctrOutput", iIgnoreWarning%)

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Enable your start trigger on PFI 37 within the next 10 seconds. ")

    Call PrintText(txtStatusBox, "Watch the counter's output pin (PFI 36) for the squarewave. ")

'     Wait for 10 seconds.

'     HINT... You can replace this with a loop around GPCTR_Watch,
'      checking for the counter's ND_COUNT value.  If it stays at the
'      initial ND_COUNT_1, then the counter has not started yet.

    iRetVal% = NIDAQDelay(10.0)

'     CLEANUP - Don't check for errors on purpose.

'     Disable the start trigger for the counter.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_START_TRIGGER, ND_AUTOMATIC)

'     Disconnect the IO Connector line PFI 37 from the internal start
'      trigger.

    iStatus% = Select_Signal(iDevice%, ND_START_TRIGGER, ND_NONE, ND_DONT_CARE)

'     Disconnect the GPCTR output from the IO Connector.

    iStatus% = Select_Signal(iDevice%, ulGpctrOutput&, ND_NONE, ND_DONT_CARE)

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    Call PrintText(txtStatusBox, "Squarewave generation done! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


