VERSION 4.00
Begin VB.Form Form1
  Caption = "AIonePointExtConv_Eseries"
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
'     AIonePointExtConv_Eseries.FRM
' 
'  Description:
'     Read one channel, one point at a time, using external timing (for
'      E-series devices)
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     1PT, 1CH, EXTTIM, ESER
' 
'  List of key parameters:
'     iChan, iReadingAvail
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     AI_Clear, NIDAQErrorHandler, Select_Signal, AI_Setup, AI_Check,
'      NIDAQYield, AI_VScale
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signal to AI channel 1. The default analog
'      input mode for the DAQ device will be used. Also, connect a
'      digital pulse (falling edge) to the PFI2/CONVERT* pin.
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
    Dim iChan As Integer
    Dim iGain As Integer
    Dim dVoltage As Double
    Dim iReadingAvail As Integer
    Dim iReading As Integer
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    iChan% = 1
    iGain% = 1
    dVoltage# = 0.0
    dGainAdjust# = 1.0
    dOffset# = 0.0
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This clears the AI FIFO.

    iStatus% = AI_Clear(iDevice%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AI_Clear", iIgnoreWarning%)

    iStatus% = Select_Signal(iDevice%, ND_IN_CONVERT, ND_PFI_2, ND_HIGH_TO_LOW)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal", iIgnoreWarning%)

'     Setup for external conversions.

    iStatus% = AI_Setup(iDevice%, iChan%, iGain%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AI_Setup", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply a pulse to the 'external conversion' pin when ready to read a voltage. ")

    While ((iReadingAvail% <>  1) And (iStatus% =  0))

'         Wait until reading is available.

        iStatus% = AI_Check(iDevice%, iReadingAvail%, iReading%)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "AI_Check", iIgnoreWarning%)

    iStatus% = AI_VScale(iDevice%, iChan%, iGain%, dGainAdjust#, dOffset#, iReading%, dVoltage#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AI_VScale", iIgnoreWarning%)

'     Set PFI line back to initial state.

    iStatus% = Select_Signal(iDevice%, ND_IN_CONVERT, ND_INTERNAL_TIMER, ND_LOW_TO_HIGH)

    Call PrintText(txtStatusBox, "The voltage at AI channel " +  Trim$(Str$(iChan%)) + "is " +  Trim$(Str$(dVoltage#)) + "volts. ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


