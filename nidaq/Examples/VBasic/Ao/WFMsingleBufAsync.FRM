VERSION 4.00
Begin VB.Form Form1
  Caption = "WFMsingleBufAsync"
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
'     WFMsingleBufAsync.FRM
' 
'  Description:
'     Output a waveform from one analog output channel, using internal
'      timing (uses low-level NI-DAQ functions)
' 
'  Example Category:
'     AO
' 
'  Example Task Types:
'     BUF, 1CH, BURST, ASYNC, INTTIM, INTTRIG
' 
'  List of key parameters:
'     iGroup, ulIterations, iWFMstopped, iOpSTART, iOpCLEAR
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     NIDAQMakeBuffer, WFM_Group_Setup, NIDAQErrorHandler, WFM_Scale,
'      WFM_Load, WFM_Rate, WFM_ClockRate, WFM_Group_Control, WFM_Check,
'      NIDAQYield, AO_VWrite
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The analog output signal will be available at AO channel 0. The
'      default analog output mode for the DAQ device will be used.
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
    Dim iNumChans As Integer
    Dim iChan As Integer
    Static piChanVect(1) As Integer
    Dim iGroup As Integer
    Static pdBuffer(5000) As Double
    Static piBuffer(5000) As Integer
    Dim ulCount As Long
    Dim ulIterations As Long
    Dim iFIFOMode As Integer
    Dim iDelayMode As Integer
    Dim dUpdateRate As Double
    Dim iUpdateTB As Integer
    Dim ulUpdateInt As Long
    Dim iWhichClock As Integer
    Dim iUnits As Integer
    Dim iWFMstopped As Integer
    Dim ulItersDone As Long
    Dim ulPtsDone As Long
    Dim iOpSTART As Integer
    Dim iOpCLEAR As Integer
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iNumChans% = 1
    iGroup% = 1
    ulCount& = 5000
    ulIterations& = 1
    dUpdateRate# = 1000.0
    iOpSTART% = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = NIDAQMakeBuffer(pdBuffer#(0), ulCount&, WFM_DATA_F64)

    If (iStatus% =  0) Then

'         If buffer was made correctly, then output it.

        iStatus% = WFM_Group_Setup(iDevice%, iNumChans%, piChanVect%(0), iGroup%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Group_Setup", iIgnoreWarning%)

        iStatus% = WFM_Scale(iDevice%, iChan%, ulCount&, 1.0, pdBuffer#(0), piBuffer%(0))

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Scale", iIgnoreWarning%)

'         NOTE FOR DSA devices... DSA devices can format samples in a
'          left-justified format in 32-bit data words. This means that
'          the most significant bits of the data word contain the bits
'          generated by the converter. When allocating data buffers, be
'          sure to account for the 32-bit data width. Even though a
'          number of DAQ/SCAN/WFM functions are declared to accept
'          pointers to 16-bit data buffers, you should pass pointers to
'          32-bit data buffers.

'         Also for DSA devices, remember to call AO_Change_Parameter to
'          enable the analog output.

        iStatus% = WFM_Load(iDevice%, iNumChans%, piChanVect%(0), piBuffer%(0), ulCount&, ulIterations&, iFIFOMode%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Load", iIgnoreWarning%)

'         NOTE: If you are using a DSA device, call WFM_Set_Clock
'          instead.  Refer to NI-DAQ Function Reference Manual for
'          details.

        iStatus% = WFM_Rate(dUpdateRate#, iUnits%, iUpdateTB%, ulUpdateInt&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Rate", iIgnoreWarning%)

        iStatus% = WFM_ClockRate(iDevice%, iGroup%, iWhichClock%, iUpdateTB%, ulUpdateInt&, iDelayMode%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_ClockRate", iIgnoreWarning%)

        Call PrintText(txtStatusBox, "A " +  Trim$(Str$(ulCount&)) + "point waveform should be output at a rate of " +  Trim$(Str$(dUpdateRate#)) + "updates/sec. ")

        iStatus% = WFM_Group_Control(iDevice%, iGroup%, iOpSTART%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Group_Control/START", iIgnoreWarning%)

        While ((iWFMstopped% =  0) And (iStatus% =  0))

            iStatus% = WFM_Check(iDevice%, iChan%, iWFMstopped%, ulItersDone&, ulPtsDone&)

            DoEvents

        Wend

        iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Check", iIgnoreWarning%)

'         CLEANUP - Don't check for errors on purpose.

'         Set group back to initial state.

        iStatus% = WFM_Group_Control(iDevice%, iGroup%, iOpCLEAR%)

'         Set output at 0 volts.

        iStatus% = AO_VWrite(iDevice%, iChan%, 0.0)

        Call PrintText(txtStatusBox, "The waveform generation is done! ")

    Else

        Call PrintText(txtStatusBox, "The buffer was not made correctly. " + "Check the parameters for NIDAQMakeBuffer. ")

    End If


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


