VERSION 4.00
Begin VB.Form Form1
  Caption = "AOonePointCurrent"
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
'     AOonePointCurrent.FRM
' 
'  Description:
'     Output one channel, one current value point at a time, immediately
'      (first output 5mA then 0A)
' 
'  Example Category:
'     AO
' 
'  Example Task Types:
'     1PT, 1CH, IMMED, INTTIM
' 
'  List of key parameters:
'     iChan
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     AO_Change_Parameter, NIDAQErrorHandler, NIDAQWaitForKey, AO_VWrite
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The analog output current signal will be available at AO current
'      channel 0.  Please note that on some devices, the current output
'      and the voltage output may be on different I/O connector pins.
'      Also, some devices may require an external power source to drive
'      the current.
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
    Dim dCurrent1 As Double
    Dim dCurrent2 As Double
    Dim iIgnoreWarning As Integer

    iDevice% = 1
    dCurrent1# = 5.0
    dCurrent2# = 0.0

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     IMPORTANT... For the 6704 devices, set 'iChan' to any channel
'      between 16 and 31. For the VXI-AO-48XDC, set 'iChan' to any
'      channel between 0 and 47. Please refer to the hardware user
'      manual for more information.

'     Change output type to current.

    iStatus% = AO_Change_Parameter(iDevice%, iChan%, ND_OUTPUT_TYPE, ND_CURRENT_OUTPUT)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AO_Change_Parameter", iIgnoreWarning%)

'     For best results, look at the output with an ammeter.

'     First output 'dCurrent1' mA.

    Call PrintText(txtStatusBox, "Hit any key to output " +  Trim$(Str$(dCurrent1#)) + "mA. ")

    iRetVal% = NIDAQWaitForKey(0.0)

'     For AO-2DC devices, the current value must be in units of Amps,
'      and for AO-6/10 devices, the current value must be the voltage
'      value that will produce the desired current (given the external
'      supply and shunt resistor).

    iStatus% = AO_VWrite(iDevice%, iChan%, dCurrent1#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AO_VWrite", iIgnoreWarning%)

'     Then output 'dCurrent2' mA.

    Call PrintText(txtStatusBox, "Hit any key to output " +  Trim$(Str$(dCurrent2#)) + "mA. ")

    iRetVal% = NIDAQWaitForKey(0.0)

    iStatus% = AO_VWrite(iDevice%, iChan%, dCurrent2#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AO_VWrite", iIgnoreWarning%)

'     Change output type back to voltage. (Ignore errors)

    iStatus% = AO_Change_Parameter(iDevice%, iChan%, ND_OUTPUT_TYPE, ND_VOLTAGE_OUTPUT)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


