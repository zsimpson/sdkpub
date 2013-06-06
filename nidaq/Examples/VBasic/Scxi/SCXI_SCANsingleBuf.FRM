VERSION 4.00
Begin VB.Form Form1
  Caption = "SCXI_SCANsingleBuf"
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
'     SCXI_SCANsingleBuf.FRM
' 
'  Description:
'     Read 4 channels at the SAME gain from an SCXI analog input module
'      into a buffer, using internal scan and sample timing. The DAQ
'      device must have a scan clock and a channel clock. NOTE: This
'      example is NOT suitable for the SCXI-1122 module, which uses a
'      relay multiplexer.  For the SCXI-1122 module, sample a buffer of
'      data on one channel, then call SCXI_Change_Chan to sample another
'      channel. Also, if you are using this example with an SCXI-1100,
'      make sure the filter setting is set to NO FILTER, so that the
'      signals can settle properly.
' 
'  Example Category:
'     SCXI
' 
'  Example Task Types:
'     BUF, NCH, INTTIM, SYNC
' 
'  List of key parameters:
'     iNumModules, piModuleList, piNumChans, piStartChans, iMuxCtrON,
'      uCtrValue
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     SCXI_Load_Config, NIDAQErrorHandler, SCXI_SCAN_Setup,
'      Timeout_Config, SCXI_MuxCtr_Setup, SCAN_Op, SCAN_Demux,
'      SCXI_Scale, NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your analog signals to channels 0 through 3 of your SCXI
'      module in chassis 1, slot 1. Make sure the connection to your DAQ
'      device is setup correctly.
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
    Dim iNumModules As Integer
    Static piModuleList(1) As Integer
    Dim iModuleSlot As Integer
    Dim iNumDevChans As Integer
    Static piNumChans(1) As Integer
    Dim iNumSCXIChans As Integer
    Static piStartChans(1) As Integer
    Dim iDevice As Integer
    Dim lTimeout As Integer
    Dim iMuxCtrON As Integer
    Dim iMuxCtrOFF As Integer
    Dim iScanDiv As Integer
    Dim uCtrValue As Integer
    Dim iOnDevChan As Integer
    Dim iOnDevGain As Integer
    Static piOnDevChan(1) As Integer
    Static piOnDevGain(1) As Integer
    Static piBuffer(100) As Integer
    Dim ulCount As Integer
    Dim dSampRate As Double
    Dim dScanRate As Double
    Dim dSCXIgain As Double
    Dim dTermBlockGain As Double
    Static pdVoltBuffer(100) As Double
    Dim iIgnoreWarning As Integer
    Dim i As Long

    iChassisID% = 1
    iNumModules% = 1
    For i& = 0 to (1 - 1)
        piModuleList%(i&) = 1
    Next
    iModuleSlot% = 1
    iNumDevChans% = 1
    For i& = 0 to (1 - 1)
        piNumChans%(i&) = 4
    Next
    iNumSCXIChans% = 4
    iDevice% = 1
    lTimeout% = 180
    iMuxCtrON% = 1
    iScanDiv% = 1
    uCtrValue% = 4
    iOnDevGain% = 1
    For i& = 0 to (1 - 1)
        piOnDevGain%(i&) = 1
    Next
    ulCount% = 100
    dSampRate# = 10000.0
    dScanRate# = 1000.0
    dSCXIgain# = 1.0
    dTermBlockGain# = 1.0

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = SCXI_Load_Config(iChassisID%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Load_Config", iIgnoreWarning%)

'     Setup hardware scanning on SCXI module.

'     NOTE: If you are using the SCXI-1140 module, you can call
'      SCXI_Track_Hold_Setup at this point to setup the track-and-hold
'      circuitry.

    iStatus% = SCXI_SCAN_Setup(iChassisID%, iNumModules%, piModuleList%(0), piNumChans%(0), piStartChans%(0), iDevice%, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_SCAN_Setup", iIgnoreWarning%)

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the SCAN_Op call.

    iStatus% = Timeout_Config(iDevice%, lTimeout%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

    iStatus% = SCXI_MuxCtr_Setup(iDevice%, iMuxCtrON%, iScanDiv%, uCtrValue%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_MuxCtr_Setup", iIgnoreWarning%)

'     Scan_Op is called to perform 'interval scanning'. You must use a
'      DAQ device that has a 'scan clock'. Some devices may require you
'      to use Lab_ISCAN_Op instead.

    iStatus% = SCAN_Op(iDevice%, iNumDevChans%, piOnDevChan%(0), piOnDevGain%(0), piBuffer%(0), ulCount%, dSampRate#, dScanRate#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Op", iIgnoreWarning%)

'     NOTE: If you are using the SCXI-1140 module, you can call
'      SCXI_Track_Hold_Setup at this point to disable the track-and-hold
'      circuitry.

    iStatus% = SCAN_Demux(piBuffer%(0), ulCount%, iNumSCXIChans%, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCAN_Demux", iIgnoreWarning%)

'     Since all channels have the same gain, the SCXI_Scale is called
'      for all channels.  If you have set different gains for different
'      channels, then scale them one channel at a time.

    iStatus% = SCXI_Scale(iChassisID%, iModuleSlot%, 0, dSCXIgain#, dTermBlockGain#, iDevice%, iOnDevChan%, iOnDevGain%, ulCount%, piBuffer%(0), pdVoltBuffer#(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "SCXI_Scale", iIgnoreWarning%)

    iStatus% = SCXI_MuxCtr_Setup(iDevice%, iMuxCtrOFF%, 0, 0)

    iRetVal% = NIDAQPlotWaveform(pdVoltBuffer#(0), ulCount%, WFM_DATA_F64)

    Call PrintText(txtStatusBox, "The data is available in 'pdVoltBuffer'. ")

'     Disable timeouts.

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


