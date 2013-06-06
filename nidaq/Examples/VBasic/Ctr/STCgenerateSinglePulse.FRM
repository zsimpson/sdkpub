VERSION 4.00
Begin VB.Form Form1
  Caption = "STCgenerateSinglePulse"
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
'     STCgenerateSinglePulse.FRM
' 
'  Description:
'     Generates a single digital pulse 100 ms wide (output HIGH) delayed
'      1 ms after the trigger using general purpose counter 0 and an
'      internal 100kHz timebase (for devices with the DAQ-STC
'      counter/timer)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     PLSTRN, 1PT
' 
'  List of key parameters:
'     ulGpctrNum, ulGpctrOutput, ulLOWcount, ulHIGHcount
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, Select_Signal, GPCTR_Watch, NIDAQYield
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Your digital pulse will be on the OUT pin of your counter. Connect
'      the ground reference to the DIG GND pin.
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
    Dim ulGpctrOutput As Long
    Dim ulLOWcount As Long
    Dim ulHIGHcount As Long
    Dim ulArmed As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    ulGpctrNum& = ND_COUNTER_0
    ulGpctrOutput& = ND_GPCTR0_OUTPUT
    ulLOWcount& = 100
    ulHIGHcount& = 10000
    ulArmed& = ND_YES
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_SINGLE_PULSE_GNR)

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

'     NOTE: On USB devices, this call takes longer than normal, so you
'      may not be able to output a pulse as short as 1ms.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

'     Loop until 'ulGpctrNum' is no longer armed.

    Do 

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_ARMED, ulArmed&)

        DoEvents

    Loop While ((ulArmed& =  ND_YES) And (iStatus% =  0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Watch/ARMED", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

'     Disconnect GPCTR0_OUTPUT.

'     Note that this will cause the output to be high impedance which
'      will most likely bring the logic level HIGH if there is a pull-up
'      resistor on this pin.  (Check your hardware user manual.)  If you
'      do not want this behavior, comment out the next line.

    iStatus% = Select_Signal(iDevice%, ND_GPCTR0_OUTPUT, ND_NONE, ND_DONT_CARE)

    Call PrintText(txtStatusBox, "Single pulse has been generated at GPCTR0_OUTPUT! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


