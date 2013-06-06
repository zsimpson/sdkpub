VERSION 4.00
Begin VB.Form Form1
  Caption = "Calibrate_Eseries"
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
'     Calibrate_Eseries.FRM
' 
'  Description:
'     Calibrate an E-series board using internal voltage reference
'      (SELF_CALIBRATE) and store calibration constants in
'      USER_EEPROM_AREA. (E-series only)  This example also takes
'      measurements over 50/60Hz sinewave periods and averages the data
'      before and after calibration, so you can compare.
' 
'  Example Category:
'     CALIB
' 
'  Example Task Types:
'     ESER, BUF, 1CH, SYNC, INTTIM
' 
'  List of key parameters:
'     piBuffer, dSampRate, ulCalOp, ulSetOfCalConst
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DAQ_Op, NIDAQErrorHandler, NIDAQMean, Calibrate_E_Series
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Ground the inputs to AI channel 1.  If the device is in
'      differential mode, tie both the + and - inputs to AIGND. If the
'      device is in single-ended mode, tie the input to AIGND.
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
    Static piBuffer(600) As Integer
    Dim ulCount As Long
    Dim dSampRate As Double
    Dim ulCalOp As Long
    Dim ulSetOfCalConst As Long
    Dim dMean As Double
    Dim iIgnoreWarning As Integer
    Dim i As Long

    iDevice% = 1
    iChan% = 1
    iGain% = 1
    ulCount& = 100
    dSampRate# = 600.0
    ulCalOp& = ND_SELF_CALIBRATE
    ulSetOfCalConst& = ND_USER_EEPROM_AREA
    dMean# = 0.0
    iIgnoreWarning% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Acquire data before calibration.

    Call PrintText(txtStatusBox, "... ")

    Call PrintText(txtStatusBox, "Measuring offset at AI channel " +  Trim$(Str$(iChan%)) + "before calibration. ")

    Call PrintText(txtStatusBox, "NOTE: Make sure the inputs are grounded. ")

    iStatus% = DAQ_Op(iDevice%, iChan%, iGain%, piBuffer%(0), ulCount&, dSampRate#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Op", iIgnoreWarning%)

    iRetVal% = NIDAQMean(piBuffer%(0), ulCount&, WFM_DATA_I16, dMean#)

    Call PrintText(txtStatusBox, "The offset at AI channel " +  Trim$(Str$(iChan%)) + "before calibration is " +  Trim$(Str$(dMean#)) + "ADC units binary. ")

'     Calibrate E-series device.

    Call PrintText(txtStatusBox, "...Starting E-series calibration...this may take a while. ")

    iStatus% = Calibrate_E_Series(iDevice%, ulCalOp&, ulSetOfCalConst&, 0.0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Calibrate_E_Series", iIgnoreWarning%)

    If (iStatus% =  0) Then

        Call PrintText(txtStatusBox, "...E-series calibration completed! ")

'         Acquire data AFTER calibration.

        Call PrintText(txtStatusBox, "Measuring offset at AI channel " +  Trim$(Str$(iChan%)) + "AFTER calibration. ")

        Call PrintText(txtStatusBox, "NOTE: Make sure the inputs are grounded. ")

        iStatus% = DAQ_Op(iDevice%, iChan%, iGain%, piBuffer%(0), ulCount&, dSampRate#)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Op", iIgnoreWarning%)

        iRetVal% = NIDAQMean(piBuffer%(0), ulCount&, WFM_DATA_I16, dMean#)

        Call PrintText(txtStatusBox, "The offset at AI channel " +  Trim$(Str$(iChan%)) + "AFTER calibration is " +  Trim$(Str$(dMean#)) + "ADC units binary. ")

    Else

        Call PrintText(txtStatusBox, "An error occurred during calibration. Please check errors. ")

    End If


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


