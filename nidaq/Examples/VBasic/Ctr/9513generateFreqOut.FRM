VERSION 4.00
Begin VB.Form Form1
  Caption = "9513generateFreqOut"
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
'     9513generateFreqOut.FRM
' 
'  Description:
'     Generates a square wave (digital pulse train) with 1kHz frequency
'      (fixed 50% duty cycle) using the 4-bit frequency divider, FOUT,
'      and an internal timebase (for devices with the Am9513
'      counter/timer)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     PULSTRN, INTTIM
' 
'  List of key parameters:
'     iModeON, iTimeBase, iDivision
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     CTR_FOUT_Config, NIDAQErrorHandler, NIDAQWaitForKey
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Your digital pulse train will be on the FOUT (or FOUT1, if using
'      TIO-10) pin. Connect the ground reference to the DIG GND pin.
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
    Dim iFOUTport As Integer
    Dim iModeON As Integer
    Dim iModeOFF As Integer
    Dim iTimeBase As Integer
    Dim iDivision As Integer
    Dim iIgnoreWarnings As Integer

    iDevice% = 1
    iFOUTport% = 1
    iModeON% = 1
    iTimeBase% = 4
    iDivision% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Start FOUT square wave.

    iStatus% = CTR_FOUT_Config(iDevice%, iFOUTport%, iModeON%, iTimeBase%, iDivision%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_FOUT_Config", iIgnoreWarnings%)

    Call PrintText(txtStatusBox, "Hit any key to stop the squarewave. ")

    iRetVal% = NIDAQWaitForKey(0.0)

    Call PrintText(txtStatusBox, "FOUT square wave generation done! ")

'     CLEANUP - Don't check for errors on purpose.

'     Turn off FOUT square wave.

    iStatus% = CTR_FOUT_Config(iDevice%, iFOUTport%, iModeOFF%, iTimeBase%, iDivision%)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


