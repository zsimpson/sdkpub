VERSION 4.00
Begin VB.Form Form1
  Caption = "DoubleBufferedCDIwithAI"
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
'     DoubleBufferedCDIwithAI.FRM
' 
'  Description:
'     Continuously correlates digital input with analog input.
' 
'  Example Category:
'     CDIO
' 
'  Example Task Types:
'     BUF, NCH, INTTIM, CONT, ASYNC
' 
'  List of key parameters:
'     ulCount, ulHalfCount, iHalfBufsToRead, iNumLines, iAIChan,
'      dSampRate, iDIReqSource
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     Timeout_Config, NIDAQErrorHandler, DIG_Line_Config,
'      DIG_Grp_Config, DIG_Grp_Mode, DIG_Block_PG_Config, DIG_DB_Config,
'      DAQ_Rate, DAQ_DB_Config, DIG_Block_In, DAQ_Start,
'      DAQ_DB_HalfReady, DAQ_DB_Transfer, DIG_DB_HalfReady,
'      DIG_DB_Transfer, NIDAQYield, DAQ_Clear
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital input signals to pins DIO0-7. Connect the
'      ground reference to the DIG GND pin. Connect your analog signals
'      to the AI channel 0 I/O pin. (please refer to your hardware user
'      manual for details)
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
    Static iDIBuffer(500) As Integer
    Static iDIHalfBuffer(250) As Integer
    Dim iDIGroup As Integer
    Dim iDIReqSource As Integer
    Dim iInLineDirection As Integer
    Dim iInGroupDirection As Integer
    Dim iDIEdge As Integer
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
    iDIGroup% = 1
    iDIReqSource% = 9
    iInLineDirection% = 4

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the DAQ_DB_Transfer or
'      DIG_DB_Transfer call.

    iStatus% = Timeout_Config(iDevice%, lTimeout&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

'     Configure the digital lines for the correct direction., CONST

    While (iLineCount% <  iNumLines%)

        iStatus% = DIG_Line_Config(iDevice%, iPort%, iLineCount%, iInLineDirection%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Line_Config", iIgnoreWarning%)

        iLineCount = iLineCount+ 1

    Wend

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

'     Configure Analog Input

    iStatus% = DAQ_Rate(dSampRate#, iAIUnits%, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Rate", iIgnoreWarning%)

    iStatus% = DAQ_DB_Config(iDevice%, iDBmodeON%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_Config", iIgnoreWarning%)

'     Start acquiring data.

    iStatus% = DIG_Block_In(iDevice%, iDIGroup%, iDIBuffer%(0), ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_In", iIgnoreWarning%)

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

    iStatus% = DIG_Grp_Config(iDevice%, iDIGroup%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

'     Disable timeouts

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


