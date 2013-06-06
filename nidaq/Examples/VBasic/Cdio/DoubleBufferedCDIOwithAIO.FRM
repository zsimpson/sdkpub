VERSION 4.00
Begin VB.Form Form1
  Caption = "DoubleBufferedCDIOwithAIO"
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
'     DoubleBufferedCDIOwithAIO.FRM
' 
'  Description:
'     Continuously correlates digital input with analog input and
'      digital output with analog output.
' 
'  Example Category:
'     CDIO
' 
'  Example Task Types:
'     BUF, NCH, INTTIM, CONT, ASYNC
' 
'  List of key parameters:
'     ulCount, ulHalfCount, iHalfBufsToRead, iAIChan, dSampRate,
'      iAOChan, dUpdateRate, iDIReqSource, iDOReqSource, iNumOutputLines
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     Timeout_Config, NIDAQErrorHandler, DIG_Line_Config,
'      NIDAQMakeBuffer, DIG_Grp_Config, DIG_Grp_Mode,
'      DIG_Block_PG_Config, DIG_DB_Config, Set_DAQ_Device_Info,
'      WFM_DB_Config, WFM_Group_Setup, WFM_Scale, WFM_Load, WFM_Rate,
'      WFM_ClockRate, DAQ_Rate, DAQ_DB_Config, DIG_Block_Out,
'      DIG_Block_In, WFM_Group_Control, DAQ_Start, DAQ_DB_HalfReady,
'      DAQ_DB_Transfer, DIG_DB_HalfReady, DIG_DB_Transfer, NIDAQYield,
'      DAQ_Clear, AO_VWrite
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital input signals to pins DIO4, DIO5, DIO6, and
'      DIO7 . The digital output signals will be available at pins DIO0,
'      DIO1, DIO2, and DIO3. Connect the ground reference to the DIG GND
'      pin. The analog output signal will be available at AO channel 0.
'      Connect your analog signals to the AI channel 0 I/O pin. (please
'      refer to your hardware user manual for details)
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
    Dim iDBmodeON As Integer
    Dim iDBmodeOFF As Integer
    Dim iPGmodeOn As Integer
    Dim ulCount As Long
    Dim ulHalfCount As Long
    Dim iLoopCount As Integer
    Dim iLineCount As Integer
    Dim iHalfBufsToRead As Integer
    Dim iGroupSize As Integer
    Dim iPort As Integer
    Dim iNumLines As Integer
    Dim iRegenAllowed As Integer
    Dim iNoRegen As Integer
    Dim iPartialTransferAllowed As Integer
    Dim iNoPartialTransfer As Integer
    Dim iIgnoreWarning As Integer
    Dim lTimeout As Long
    Dim iYieldON As Integer
    Dim iAIChan As Integer
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim iAIUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Static piAIBuffer(1000) As Integer
    Static piAIHalfBuffer(500) As Integer
    Dim iHalfReady As Integer
    Dim iDAQStopped As Integer
    Dim ulPtsTfr As Long
    Dim iGroup As Integer
    Dim iNumChans As Integer
    Dim iAOChan As Integer
    Dim dUpdateRate As Double
    Dim iAOUnits As Integer
    Dim iUpdateTB As Integer
    Dim ulUpdateInt As Long
    Dim iWhichClock As Integer
    Dim iDelayMode As Integer
    Static piAOChanVect(1) As Integer
    Static pdAOBuffer(1000) As Double
    Static piAOBuffer(1000) As Integer
    Dim ulIterations As Long
    Dim iFIFOMode As Integer
    Dim iOpSTART As Integer
    Dim iOpCLEAR As Integer
    Static iDIBuffer(500) As Integer
    Static iDIHalfBuffer(250) As Integer
    Dim iDIGroup As Integer
    Dim iDIReqSource As Integer
    Dim iInLineDirection As Integer
    Dim iInGroupDirection As Integer
    Dim iDIEdge As Integer
    Static iDOBuffer(500) As Integer
    Dim iDOGroup As Integer
    Dim iDOReqSource As Integer
    Dim iOutLineDirection As Integer
    Dim iOutGroupDirection As Integer
    Dim iDOEdge As Integer
    Dim iNumOutputLines As Integer
    Dim i As Long

    iDevice% = 1
    iDBmodeON% = 1
    iPGmodeOn% = 1
    ulCount& = 1000
    ulHalfCount& = 500
    iHalfBufsToRead% = 20
    iGroupSize% = 1
    iNumLines% = 8
    iNoRegen% = 1
    iPartialTransferAllowed% = 1
    lTimeout& = 180
    iYieldON% = 1
    iGain% = 1
    dSampRate# = 1000
    iGroup% = 1
    iNumChans% = 1
    dUpdateRate# = 1000
    iOpSTART% = 1
    iDIGroup% = 1
    iDIReqSource% = 9
    iInLineDirection% = 4
    iDOGroup% = 2
    iDOReqSource% = 10
    iOutLineDirection% = 5
    iOutGroupDirection% = 1
    iNumOutputLines% = 4

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the DAQ_DB_Transfer or
'      DIG_DB_Transfer call.

    iStatus% = Timeout_Config(iDevice%, lTimeout&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

'     Configure the digital lines for the correct direction.  Lines 0-3
'      will be output lines and 4-7 input lines.

    While (iLineCount% <  iNumLines%)

        If (iLineCount% <  iNumOutputLines%) Then

            iStatus% = DIG_Line_Config(iDevice%, iPort%, iLineCount%, iOutLineDirection%)

        Else

            iStatus% = DIG_Line_Config(iDevice%, iPort%, iLineCount%, iInLineDirection%)

        End If

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Line_Config", iIgnoreWarning%)

        iLineCount = iLineCount+ 1

    Wend

'     Configure Digital Output

'     Create a sawtooth waveform.

    iStatus% = NIDAQMakeBuffer(iDOBuffer%(0), ulCount&, WFM_DATA_U8)

    iRetVal% = NIDAQErrorHandler(iStatus%, "NIDAQMakeBuffer", iIgnoreWarning%)

    iStatus% = DIG_Grp_Config(iDevice%, iDOGroup%, iGroupSize%, iPort%, iOutGroupDirection%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Grp_Config", iIgnoreWarning%)

    iStatus% = DIG_Grp_Mode(iDevice%, iDOGroup%, 0, iDOEdge%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Grp_Mode", iIgnoreWarning%)

'     Correlate the output to the Analog Output Update clock.

    iStatus% = DIG_Block_PG_Config(iDevice%, iDOGroup%, iPGmodeOn%, iDOReqSource%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Block_PG_Config", iIgnoreWarning%)

'     The buffer will be written once and then regenerated.

    iStatus% = DIG_DB_Config(iDevice%, iDOGroup%, iDBmodeON%, iRegenAllowed%, iNoPartialTransfer%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_DB_Config", iIgnoreWarning%)

'     Since there are only 3 DMA channels available for a board and we
'      are doing analog input, analog output, digital input, and digital
'      output, one of the operations must be set to perform transfers by
'      interrupts.

    iStatus% = Set_DAQ_Device_Info(iDevice%, ND_DATA_XFER_MODE_DIO_GR2, ND_INTERRUPTS)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Set_DAQ_Device_Info", iIgnoreWarning%)

'     Configure Digital Input

    iStatus% = DIG_Grp_Config(iDevice%, iDIGroup%, iGroupSize%, iPort%, iInGroupDirection%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Grp_Config", iIgnoreWarning%)

    iStatus% = DIG_Grp_Mode(iDevice%, iDIGroup%, 0, iDIEdge%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Grp_Mode", iIgnoreWarning%)

'     Correlate the input to the Analog Input Scan Clock.

    iStatus% = DIG_Block_PG_Config(iDevice%, iDIGroup%, iPGmodeOn%, iDIReqSource%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Block_PG_Config", iIgnoreWarning%)

    iStatus% = DIG_DB_Config(iDevice%, iDIGroup%, iDBmodeON%, iNoRegen%, iNoPartialTransfer%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_DB_Config", iIgnoreWarning%)

'     Configure Analog Output

    iStatus% = NIDAQMakeBuffer(pdAOBuffer#(0), ulCount&, WFM_DATA_F64)

    iRetVal% = NIDAQErrorHandler(iStatus%, "NIDAQMakeBuffer", iIgnoreWarning%)

    iStatus% = WFM_DB_Config(iDevice%, iNumChans%, piAOChanVect%(0), iDBmodeON%, iRegenAllowed%, iNoPartialTransfer%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_DB_Config", iIgnoreWarning%)

    iStatus% = WFM_Group_Setup(iDevice%, iNumChans%, piAOChanVect%(0), iGroup%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Group_Setup", iIgnoreWarning%)

    iStatus% = WFM_Scale(iDevice%, iAOChan%, ulCount&, 1.0, pdAOBuffer#(0), piAOBuffer%(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Scale", iIgnoreWarning%)

    iStatus% = WFM_Load(iDevice%, iNumChans%, piAOChanVect%(0), piAOBuffer%(0), ulCount&, ulIterations&, iFIFOMode%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Load", iIgnoreWarning%)

    iStatus% = WFM_Rate(dUpdateRate#, iAOUnits%, iUpdateTB%, ulUpdateInt&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Rate", iIgnoreWarning%)

    iStatus% = WFM_ClockRate(iDevice%, iGroup%, iWhichClock%, iUpdateTB%, ulUpdateInt&, iDelayMode%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_ClockRate", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "The digital and analog waveforms should be output at a rate of " +  Trim$(Str$(dUpdateRate#)) + "updates/sec. ")

'     Configure Analog Input

    iStatus% = DAQ_Rate(dSampRate#, iAIUnits%, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Rate", iIgnoreWarning%)

    iStatus% = DAQ_DB_Config(iDevice%, iDBmodeON%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_Config", iIgnoreWarning%)

'     Start acquiring and generating data.

    iStatus% = DIG_Block_Out(iDevice%, iDOGroup%, iDOBuffer%(0), ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Out", iIgnoreWarning%)

    iStatus% = DIG_Block_In(iDevice%, iDIGroup%, iDIBuffer%(0), ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_In", iIgnoreWarning%)

    iStatus% = WFM_Group_Control(iDevice%, iGroup%, iOpSTART%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_Group_Control", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Continuous generations have started. ")

    iStatus% = DAQ_Start(iDevice%, iAIChan%, iGain%, piAIBuffer%(0), ulCount&, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Start", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Continuous acquisitions have started. ")

'     Loop until 'iHalfBufsToRead' half buffers are acquired. HINT:  You
'      can be doing other foreground tasks during this time.

    Call PrintText(txtStatusBox, "HINT: You can add your own graphing calls in the while loop. ")

    While ((iLoopCount% <  iHalfBufsToRead%) And (iStatus% =  0))

        iStatus% = DAQ_DB_HalfReady(iDevice%, iHalfReady%, iDAQStopped%)

        If ((iHalfReady% =  1) And (iStatus% =  0)) Then

            iStatus% = DAQ_DB_Transfer(iDevice%, piAIHalfBuffer%(0), ulPtsTfr&, iDAQStopped%)

            iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_Transfer", 0)

            iLoopCount; = iLoopCount;+ 1

            Call PrintText(txtStatusBox,  Trim$(Str$(iLoopCount%)) + "Half buffers acquired. ")

        Else

            iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_HalfReady", 0)

        End If

        iStatus% = DIG_DB_HalfReady(iDevice%, iDIGroup%, iHalfReady%)

        If ((iHalfReady% =  1) And (iStatus% =  0)) Then

            iStatus% = DIG_DB_Transfer(iDevice%, iDIGroup%, iDIHalfBuffer%(0), ulHalfCount&)

            iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_DB_Transfer", 0)

        Else

            iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_DB_HalfReady", 0)

        End If

        DoEvents

    Wend

    Call PrintText(txtStatusBox, "Continuous acquisitions are done. ")

'     Clear all operations and reset the board to its default state

    iStatus% = DAQ_Clear(iDevice%)

    iStatus% = DAQ_DB_Config(iDevice%, iDBmodeOFF%)

    iStatus% = WFM_Group_Control(iDevice%, iGroup%, iOpCLEAR%)

    iStatus% = WFM_DB_Config(iDevice%, iNumChans%, piAOChanVect%(0), iDBmodeOFF%, 0, 0)

    iStatus% = AO_VWrite(iDevice%, iAOChan%, 0.0)

    iStatus% = DIG_Grp_Config(iDevice%, iDOGroup%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

    iStatus% = DIG_Grp_Config(iDevice%, iDIGroup%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

'     Disable timeouts

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


