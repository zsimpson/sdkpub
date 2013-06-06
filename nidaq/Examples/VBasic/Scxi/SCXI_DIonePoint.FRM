VERSION 4.00
Begin VB.Form Form1
  Caption = "SCXI_DIonePoint"
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
'     SCXI_DIonePoint.FRM
' 
'  Description:
'     Reads the state of a single digital line/relay on an SCXI digital
'      input module, immediately
' 
'  Example Category:
'     SCXI
' 
'  Example Task Types:
'     1PT, 1CH, IMMED
' 
'  List of key parameters:
'     iChassisID, iModuleSlot, iChan
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     SCXI_Load_Config, NIDAQErrorHandler, SCXI_Get_State
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital signal to the SCXI digital input module in
'      chassis 1, slot 1.  Connect your ground reference as well.  Make
'      sure the connection to your DAQ device is setup correctly.  Note
'      that some digital input modules may require an external voltage
'      source for Vcc.
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
    Dim iChassisID As Integer
    Dim iModuleSlot As Integer
    Dim iPort As Integer
    Dim iChan As Integer
    Dim ulData As Long
    Dim iIgnoreWarning As Integer

    iChassisID% = 1
    iModuleSlot% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = SCXI_Load_Config(iChassisID%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Load_Config", iIgnoreWarning%)

'     Get the state of the digital line.  If you set 'iChan' to -1, you
'      can read the entire port.

    iStatus% = SCXI_Get_State(iChassisID%, iModuleSlot%, iPort%, iChan%, ulData&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Get_State", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Data at line " +  Trim$(Str$(iChan%)) + "is " +  Trim$(Str$(ulData&)))


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


