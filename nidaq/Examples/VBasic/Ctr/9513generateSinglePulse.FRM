VERSION 4.00
Begin VB.Form Form1
  Caption = "9513generateSinglePulse"
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
'     9513generateSinglePulse.FRM
' 
'  Description:
'     Generates a single digital pulse 1 ms LOW and 100 ms HIGH using
'      counter 1 and an internal timebase (for devices with the Am9513
'      counter/timer)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     PULSTRN, INTTIM
' 
'  List of key parameters:
'     iOutType, iTimeBase, uDelay, uPulseWidth
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     CTR_Config, NIDAQErrorHandler, CTR_Pulse, NIDAQDelay, CTR_State,
'      NIDAQYield, CTR_Reset
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Your digital pulse will be on the OUT1 pin. Connect the ground
'      reference to the DIG GND pin.
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
    Dim iEdgeMode As Integer
    Dim iGateMode As Integer
    Dim iOutType As Integer
    Dim iOutPolarity As Integer
    Dim iTimeBase As Integer
    Dim uDelay As Integer
    Dim uPulseWidth As Integer
    Dim iOutState As Integer
    Dim iIgnoreWarnings As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    iCtr% = 1
    iTimeBase% = 3
    uDelay% = 10
    uPulseWidth% = 1000
    iOutState% = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Setup counter for counting rising edges with no gating.

    iStatus% = CTR_Config(iDevice%, iCtr%, iEdgeMode%, iGateMode%, iOutType%, iOutPolarity%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Config", iIgnoreWarnings%)

'     Output a 1 sec logic HIGH pulse from counter.

    iStatus% = CTR_Pulse(iDevice%, iCtr%, iTimeBase%, uDelay%, uPulseWidth%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Pulse", iIgnoreWarnings%)

'     The delay here is to ensure that the first time CTR_State is
'      called, it will sense a HIGH state. Some faster computers may get
'      to the CTR_State call while the output pulse is still low.

    iRetVal% = NIDAQDelay(0.05)

    Call PrintText(txtStatusBox, "Wait until the output of counter goes LOW. ")

    While ((iOutState% <>  0) And (iStatus% =  0))

        iStatus% = CTR_State(iDevice%, iCtr%, iOutState%)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_State", iIgnoreWarnings%)

    Call PrintText(txtStatusBox, "The counter pulse has been generated. ")

'     CLEANUP - Don't check for errors on purpose.

'     Reset counter to initial state.

    iStatus% = CTR_Reset(iDevice%, iCtr%, 0)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


