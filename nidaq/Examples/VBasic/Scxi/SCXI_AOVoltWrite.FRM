VERSION 4.00
Begin VB.Form Form1
  Caption = "SCXI_AOVoltWrite"
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
'     SCXI_AOVoltWrite.FRM
' 
'  Description:
'     Output a single analog voltage from an SCXI analog output module,
'      immediately (5 Volts, then 0 volts)
' 
'  Example Category:
'     SCXI
' 
'  Example Task Types:
'     1PT, 1CH, IMMED
' 
'  List of key parameters:
'     iChassisID, iModuleSlot, iChan, iOpCode, iRangeCode
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     SCXI_Load_Config, NIDAQErrorHandler, SCXI_AO_Write
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Your analog output voltage signal will be on channel 0 of the SCXI
'      analog output module in chassis 1, slot 1.  Connect your ground
'      reference as well. Make sure the connection to your DAQ device is
'      setup correctly.
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
    Dim iChan As Integer
    Dim iOpCode As Integer
    Dim iRangeCode As Integer
    Dim dVoltData1 As Double
    Dim dVoltData2 As Double
    Dim iBinWritten As Integer
    Dim iIgnoreWarning As Integer

    iChassisID% = 1
    iModuleSlot% = 1
    iRangeCode% = 2
    dVoltData1# = 5.0
    dVoltData2# = 0.0

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = SCXI_Load_Config(iChassisID%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Load_Config", iIgnoreWarning%)

'     First, set the voltage to dVoltData1.

    iStatus% = SCXI_AO_Write(iChassisID%, iModuleSlot%, iChan%, iOpCode%, iRangeCode%, dVoltData1#, 0, iBinWritten%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_AO_Write", iIgnoreWarning%)

'     Then, set the voltage to dVoltData2.

    iStatus% = SCXI_AO_Write(iChassisID%, iModuleSlot%, iChan%, iOpCode%, iRangeCode%, dVoltData2#, 0, iBinWritten%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_AO_Write", iIgnoreWarning%)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


