VERSION 4.00
Begin VB.Form Form1
  Caption = "SCXI_AIonePoint"
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
'     SCXI_AIonePoint.FRM
' 
'  Description:
'     Read one channel, one point at a time, immediately from an SCXI
'      analog input module.  This example can easily be extended to be
'      useable with an SCXI-1140 module, utilizing the Track-and-Hold
'      capabilities.
' 
'  Example Category:
'     SCXI
' 
'  Example Task Types:
'     1PT, 1CH, IMMED
' 
'  List of key parameters:
'     iOnDevChan, iChassisID, iModuleSlot, iModuleChan
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     SCXI_Load_Config, NIDAQErrorHandler, SCXI_Single_Chan_Setup,
'      NIDAQDelay, AI_Read, SCXI_Scale
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signal to channel 0 of your SCXI module in
'      chassis 1, slot 1.  Make sure the connection to your DAQ device
'      is setup correctly.
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
    Dim iOnDevChan As Integer
    Dim iOnDevGain As Integer
    Dim iReading As Integer
    Dim iChassisID As Integer
    Dim iModuleSlot As Integer
    Dim iModuleChan As Integer
    Dim dSCXIgain As Double
    Dim dTermBlockGain As Double
    Dim dSCXIvoltage As Double
    Dim iIgnoreWarning As Integer

    iDevice% = 1
    iOnDevGain% = 1
    iChassisID% = 1
    iModuleSlot% = 1
    dSCXIgain# = 1.0
    dTermBlockGain# = 1.0
    dSCXIvoltage# = 0.0

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = SCXI_Load_Config(iChassisID%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Load_Config", iIgnoreWarning%)

'     Specify SCXI module and channel to sample.

    iStatus% = SCXI_Single_Chan_Setup(iChassisID%, iModuleSlot%, iModuleChan%, iDevice%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Single_Chan_Setup", iIgnoreWarning%)

'     You can call SCXI_Set_Gain before AI_Read to change the gain on
'      the SCXI module or SCXI channel, depending on what the module
'      allows.  Otherwise, SCXIgain is assumed to be 1.0.

'     Some modules require that you call SCXI_Get_Status after changing
'      gain but before taking a reading to make sure the gain has
'      switched.  The delay call below should then be replaced with
'      SCXI_Get_Status.

    iRetVal% = NIDAQDelay(1.0)

'     If you are using an SCXI-1140 module, call SCXI_Track_Hold_Control
'      to put the module in 'Hold' mode at this point.

    iStatus% = AI_Read(iDevice%, iOnDevChan%, iOnDevGain%, iReading%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "AI_Read", iIgnoreWarning%)

'     If you are using an SCXI-1140 module, call SCXI_Track_Hold_Control
'      to put the module in 'Track' mode at this point.

'     If you call SCXI_Set_Gain before AI_Read, make sure to change the
'      'dSCXIgain' in SCXI_Scale.

    iStatus% = SCXI_Scale(iChassisID%, iModuleSlot%, iModuleChan%, dSCXIgain#, dTermBlockGain#, iDevice%, iOnDevChan%, iOnDevGain%, 1, iReading%, dSCXIvoltage#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Scale", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "The SCXI voltage " + "is " +  Trim$(Str$(dSCXIvoltage#)) + "volts. ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


