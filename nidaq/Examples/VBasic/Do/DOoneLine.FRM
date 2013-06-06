VERSION 4.00
Begin VB.Form Form1
  Caption = "DOoneLine"
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
'     DOoneLine.FRM
' 
'  Description:
'     Outputs digital data from a single digital line
' 
'  Example Category:
'     DO
' 
'  Example Task Types:
'     1PT, 1CH, IMMED
' 
'  List of key parameters:
'     iPort, iLine, iDir
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DIG_Line_Config, NIDAQErrorHandler, DIG_Out_Line, NIDAQWaitForKey
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The digital signal will be on port 0, line 0. Connect the ground
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
    Dim iPort As Integer
    Dim iLine As Integer
    Dim iDir As Integer
    Dim iStateON As Integer
    Dim iStateOFF As Integer
    Dim iIgnoreWarning As Integer

    iDevice% = 1
    iDir% = 1
    iStateON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Configure line as output.

'     NOTE: Some devices do not support DIG_Line_Config.  Use
'      DIG_Prt_Config instead.

    iStatus% = DIG_Line_Config(iDevice%, iPort%, iLine%, iDir%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Line_Config", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "The digital state on port " +  Trim$(Str$(iPort%)) + "line " +  Trim$(Str$(iLine%)) + "is set to " +  Trim$(Str$(iStateON%)))

    iStatus% = DIG_Out_Line(iDevice%, iPort%, iLine%, iStateON%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Out_Line", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Hit any key to change it to " +  Trim$(Str$(iStateOFF%)))

    iRetVal% = NIDAQWaitForKey(0.0)

    Call PrintText(txtStatusBox, "The digital state on port " +  Trim$(Str$(iPort%)) + "line " +  Trim$(Str$(iLine%)) + "is set to " +  Trim$(Str$(iStateOFF%)))

    iStatus% = DIG_Out_Line(iDevice%, iPort%, iLine%, iStateOFF%)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


