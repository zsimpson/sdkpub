VERSION 4.00
Begin VB.Form Form1
  Caption = "9513eventCount"
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
'     9513eventCount.FRM
' 
'  Description:
'     Counts the number of digital pulses (or events) going into the
'      clock input of counter 1 in a loop (for devices with the Am9513
'      counter/timer)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     EVENTCNT
' 
'  List of key parameters:
'     iCtr, iEdgeMode, iTimeBase
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     CTR_Config, NIDAQErrorHandler, CTR_EvCount, CTR_EvRead,
'      NIDAQDelay, NIDAQYield, CTR_Reset
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital pulse train to the SOURCE1 pin. Connect the
'      ground reference to the DIG GND pin.
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
    Dim iCont As Integer
    Dim iNumReads As Integer
    Dim iLoopCount As Integer
    Dim iOverFlow As Integer
    Dim uCount As Integer
    Dim iIgnoreWarnings As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    iCtr% = 1
    iTimeBase% = 6
    iNumReads% = 10
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Setup counter for counting rising edges (no gating).

    iStatus% = CTR_Config(iDevice%, iCtr%, iEdgeMode%, iGateMode%, iOutType%, iOutPolarity%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Config", iIgnoreWarnings%)

'     Setup counter to do event counting from SOURCE1, and don't allow
'      rollovers.

    iStatus% = CTR_EvCount(iDevice%, iCtr%, iTimeBase%, iCont%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_EvCount", iIgnoreWarnings%)

    While ((iLoopCount% <  iNumReads%) And (iStatus% =  0))

        iStatus% = CTR_EvRead(iDevice%, iCtr%, iOverFlow%, uCount%)

        If (iStatus% =  0) Then

            Call PrintText(txtStatusBox, "The reading from counter " +  Trim$(Str$(iCtr%)) + "is " +  Trim$(Str$(uCount%)))

            iLoopCount = iLoopCount+ 1

            iRetVal% = NIDAQDelay(1.0)

        End If

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_EvRead", iIgnoreWarnings%)

'     CLEANUP - Don't check for errors on purpose.

'     Reset counter to initial state.

    iStatus% = CTR_Reset(iDevice%, iCtr%, 0)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


