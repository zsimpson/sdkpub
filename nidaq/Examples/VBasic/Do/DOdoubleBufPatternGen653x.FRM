VERSION 4.00
Begin VB.Form Form1
  Caption = "DOdoubleBufPatternGen653x"
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
'     DOdoubleBufPatternGen653x.FRM
' 
'  Description:
'     Outputs digital data continuously into a buffer from a group of
'      two digital ports using internal timing (pattern generation, for
'      DIO-32 series devices)
' 
'  Example Category:
'     DO
' 
'  Example Task Types:
'     BUF, NCH, INTTIM, CONT, ASYNC
' 
'  List of key parameters:
'     iGroup, iGroupSize, iDir, iDBModeON, iOldDataStop, ulCount,
'      iHalfReady, ulBufferSize, iResource, iIgnoreWarning, ulAlignIndex
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     Timeout_Config, NIDAQErrorHandler, NIDAQMakeBuffer,
'      DIG_Grp_Config, DIG_Block_PG_Config, DIG_DB_Config,
'      Align_DMA_Buffer, DIG_Block_Out, DIG_DB_HalfReady,
'      DIG_DB_Transfer, NIDAQYield, DIG_Block_Clear
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The digital signals will be on ports 0 and 1. Connect the ground
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
    Dim iGroup As Integer
    Dim iGroupSize As Integer
    Dim iPort As Integer
    Dim iDir As Integer
    Dim iPgConfig As Integer
    Dim iReqSource As Integer
    Dim iPgTB As Integer
    Dim iReqInt As Integer
    Dim iExtGate As Integer
    Dim iDBModeON As Integer
    Dim iDBModeOFF As Integer
    Dim iOldDataStop As Integer
    Dim iPartialTransfer As Integer
    Static piBuffer(400) As Integer
    Static piHalfBuffer(100) As Integer
    Dim ulCount As Long
    Dim iHalfReady As Integer
    Dim ulPtsTfr As Long
    Dim iLoopCount As Integer
    Dim iHalfBufsToRead As Integer
    Dim ulBufferSize As Long
    Dim iResource As Integer
    Dim iIgnoreWarning As Integer
    Dim ulAlignIndex As Long
    Dim lTimeout As Long
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iGroup% = 1
    iGroupSize% = 2
    iDir% = 1
    iPgConfig% = 1
    iPgTB% = 4
    iReqInt% = 10
    iDBModeON% = 1
    iOldDataStop% = 1
    ulCount& = 200
    ulPtsTfr& = 100
    iHalfBufsToRead% = 10
    ulBufferSize& = 400
    iResource% = 11
    iIgnoreWarning% = 1
    lTimeout& = 180
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the DIG_DB_Transfer
'      call.

    iStatus% = Timeout_Config(iDevice%, lTimeout&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

    iStatus% = NIDAQMakeBuffer(piBuffer%(0), ulCount&, WFM_DATA_I16)

    If (iStatus% =  0) Then

'         Configure group of ports as output, with handshaking.

        iStatus% = DIG_Grp_Config(iDevice%, iGroup%, iGroupSize%, iPort%, iDir%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

'         Configure internally timed pattern generation with timebase 4,
'          interval 10, and no external gating.

        iStatus% = DIG_Block_PG_Config(iDevice%, iGroup%, iPgConfig%, iReqSource%, iPgTB%, iReqInt%, iExtGate%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_PG_Config", iIgnoreWarning%)

'         Turn ON software double-buffered mode, with half-buffer
'          overwrite protection (iOldDataStop).

        iStatus% = DIG_DB_Config(iDevice%, iGroup%, iDBModeON%, iOldDataStop%, iPartialTransfer%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_DB_Config", iIgnoreWarning%)

'         Align the DMA buffer so that it does not cross a page boundary
'          for AT bus computers. (It is a good idea to keep your buffers
'          smaller than 4kBytes in size.) NOTE: If you change 'iGroup'
'          or 'iGroupSize', make sure 'iResource' is changed
'          accordingly.

'         The alignment is only needed on the generation buffer, since
'          the write buffer gets filled up with DIG_DB_Transfer is
'          called. Also, please note that piBuffer is actually twice as
'          large as needed, due to a possible alignment.

        iStatus% = Align_DMA_Buffer(iDevice%, iResource%, piBuffer%(0), ulCount&, ulBufferSize&, ulAlignIndex&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "Align_DMA_Buffer", iIgnoreWarning%)

'         Start the double-buffered pattern generation output. The
'          'piBuffer' here is the circular acquisition buffer.

        iStatus% = DIG_Block_Out(iDevice%, iGroup%, piBuffer%(0), ulCount&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Out", iIgnoreWarning%)

'         Write 10 half-buffers.  Normally, 'piHalfBuffer' here would be
'          updated with the latest data, but the first half of the
'          buffer is used to ensure the simplicity of the source code.

        While ((iLoopCount% <  iHalfBufsToRead%) And (iStatus% =  0))

            iStatus% = DIG_DB_HalfReady(iDevice%, iGroup%, iHalfReady%)

            If (iStatus% >=  0) Then

                If (iHalfReady% =  1) Then

'                     Half-buffer of data will be placed in
'                      'piHalfBuffer'.

                    iStatus% = DIG_DB_Transfer(iDevice%, iGroup%, piHalfBuffer%(0), ulPtsTfr&)

                    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_DB_Transfer", iIgnoreWarning%)

                    iLoopCount = iLoopCount+ 1

                    Call PrintText(txtStatusBox,  Trim$(Str$(iLoopCount%)) + "Half buffers generated. ")

                End If

            Else

                iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_DB_HalfReady", iIgnoreWarning%)

            End If

            DoEvents

        Wend

        Call PrintText(txtStatusBox, "All 10 half-buffers done! ")

'         CLEANUP - Don't check for errors on purpose.

'         Clear the block operation.

        iStatus% = DIG_Block_Clear(iDevice%, iGroup%)

'         Turn off DB mode for device.

        iStatus% = DIG_DB_Config(iDevice%, iGroup%, iDBModeOFF%, iOldDataStop%, iPartialTransfer%)

'         Unconfigure group.

        iStatus% = DIG_Grp_Config(iDevice%, iGroup%, 0, 0, 0)

        Call PrintText(txtStatusBox, "Digital double-buffered pattern generation output is done! ")

    Else

        Call PrintText(txtStatusBox, "The buffer was not made correctly. " + "Check the parameters for NIDAQMakeBuffer. ")

    End If

'     Disable timeouts.

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


