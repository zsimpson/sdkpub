VERSION 4.00
Begin VB.Form Form1
  Caption = "AOonePointExtUpdate_Eseries"
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
'     AOonePointExtUpdate_Eseries.FRM
' 
'  Description:
'     Output one channel, one point at a time, using external timing
'      (for E-series devices)
' 
'  Example Category:
'     AO
' 
'  Example Task Types:
'     1PT, 1CH, EXTTIM, ESER
' 
'  List of key parameters:
'     iUpdateModeEXT
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     AO_VWrite, AO_Configure, NIDAQErrorHandler, Select_Signal,
'      NIDAQWaitForKey
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The analog output signal will be available at AO channel 0. The
'      default analog output mode for the DAQ device will be used. Also,
'      connect a digital pulse to the PFI5/UPDATE* pin.
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
    Dim iOutputPolarity As Integer
    Dim iIntOrExtRef As Integer
    Dim iUpdateModeEXT As Integer
    Dim iUpdateModeINT As Integer
    Dim dRefVolts As Double
    Dim dVoltage As Double
    Dim iIgnoreWarning As Integer

    iDevice% = 1
    iUpdateModeEXT% = 2
    dRefVolts# = 10.0
    dVoltage# = 2.5

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     For best results, look at the output with a scope.

'     Set output at 0 volts.

    iStatus% = AO_VWrite(iDevice%, iChan%, 0.0)

'     Configure for bipolar mode, internal reference, and external
'      updates. (The 'dRefVolts' is ignored since this is internally
'      referenced.)

    iStatus% = AO_Configure(iDevice%, iChan%, iOutputPolarity%, iIntOrExtRef%, dRefVolts#, iUpdateModeEXT%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AO_Configure/ExternalUpdate", iIgnoreWarning%)

'     Setup PFI line for external updates. (PFI5 is setup by default
'      with AO_Configure.)

    iStatus% = Select_Signal(iDevice%, ND_OUT_UPDATE, ND_PFI_5, ND_HIGH_TO_LOW)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply the 'external update' pulse to output " +  Trim$(Str$(dVoltage#)) + "volts and hit any key. ")

    iStatus% = AO_VWrite(iDevice%, iChan%, dVoltage#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AO_VWrite", iIgnoreWarning%)

    iRetVal% = NIDAQWaitForKey(0.0)

    Call PrintText(txtStatusBox, "Did you see the voltage appear on analog output channel " +  Trim$(Str$(iChan%)) + "? ")

'     Don't check for errors on purose.

'     Set update mode back to initial state.

    iStatus% = AO_Configure(iDevice%, iChan%, iOutputPolarity%, iIntOrExtRef%, dRefVolts#, iUpdateModeINT%)

'     Set PFI line back to initial state.

    iStatus% = Select_Signal(iDevice%, ND_OUT_UPDATE, ND_INTERNAL_TIMER, ND_LOW_TO_HIGH)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


