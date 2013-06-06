VERSION 4.00
Begin VB.Form Form1
  Caption = "DIonePortHandshake"
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
'     DIonePortHandshake.FRM
' 
'  Description:
'     Inputs digital data from a single digital port upon a handshaking
'      signal. Please note that some DAQ devices have predetermined port
'      directions for each digital port.
' 
'  Example Category:
'     DI
' 
'  Example Task Types:
'     1PT, 1CH, HANDSHK
' 
'  List of key parameters:
'     iMode, iDir, iLatched
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DIG_Prt_Config, NIDAQErrorHandler, DIG_Prt_Status, NIDAQYield,
'      DIG_In_Prt
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital signals to port 0. Connect the ground
'      reference to the DIG GND pin. Connect the handshaking signal to
'      the appropriate handshaking I/O pin (please refer to your
'      hardware user manual for details)
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
    Dim iMode As Integer
    Dim iDir As Integer
    Dim iPattern As Long
    Dim iLatched As Integer
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    iMode% = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Configure port as input, handshaking (latched mode).

    iStatus% = DIG_Prt_Config(iDevice%, iPort%, iMode%, iDir%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Prt_Config", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply your handshaking signal to the appropriate handshaking I/O pin for input. ")

'     Loop until data is latched in.

    While ((iLatched% =  0) And (iStatus% =  0))

        iStatus% = DIG_Prt_Status(iDevice%, iPort%, iLatched%)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Prt_Status", iIgnoreWarning%)

    iStatus% = DIG_In_Prt(iDevice%, iPort%, iPattern&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_In_Prt", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "The digital pattern on port " +  Trim$(Str$(iPort%)) + "is (DECIMAL) " +  Trim$(Str$(iPattern&)))


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


