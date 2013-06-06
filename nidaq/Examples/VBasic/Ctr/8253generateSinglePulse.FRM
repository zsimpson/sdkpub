VERSION 4.00
Begin VB.Form Form1
  Caption = "8253generateSinglePulse"
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
'     8253generateSinglePulse.FRM
' 
'  Description:
'     Generates a single digital pulse from counter 0 (Mode 0, for
'      devices with the 8253 interval counter/timer)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     PLSTRN
' 
'  List of key parameters:
'     iCtr, iMode
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     ICTR_Setup, NIDAQErrorHandler, NIDAQDelay, ICTR_Reset
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Your digital pulse (active LOW) will be on the OUT0 or OUTB0 pin.
'      Connect the ground reference to the DIG GND pin. You can "gate"
'      the pulse train off if you connect a digital logic LOW signal to
'      the GATE0 or GATB0 pin. NOTE: not all devices with the 8253 have
'      a counter 0.
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
    Dim iCtr As Integer
    Dim iMode As Integer
    Dim uCount As Integer
    Dim iBinBCD As Integer
    Dim iIgnoreWarnings As Integer

    iDevice% = 1
    uCount% = 10000
    iBinBCD% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Setup the counter for mode 0 - toggle output on Terminal Count.
'      Since counter 0 has an internal timebase connected (either 1MHz
'      or 2MHz depending on device), this will produce a logic LOW pulse
'      of duration 'uCount' multiplied by a single period of the input
'      clock (either 1uSec or 0.5uSec).

    Call PrintText(txtStatusBox, "Outputting a single pulse... ")

    iStatus% = ICTR_Setup(iDevice%, iCtr%, iMode%, uCount%, iBinBCD%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "ICTR_Setup", iIgnoreWarnings%)

'     After the pulse is generated, counter must be reset so that the
'      continuously incoming clock signal will not generate more output
'      pulses. To reset the counter, call ICTR_Reset.

    iRetVal% = NIDAQDelay(2.0)

    Call PrintText(txtStatusBox, "Single pulse has been generated! ")

'     CLEANUP - Don't check for errors on purpose.

'     Reset counter to a logic high state.

    iStatus% = ICTR_Reset(iDevice%, iCtr%, 1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


