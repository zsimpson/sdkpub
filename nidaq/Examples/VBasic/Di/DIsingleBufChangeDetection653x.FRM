VERSION 4.00
Begin VB.Form Form1
  Caption = "DIsingleBufChangeDetection653x"
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
'     DIsingleBufChangeDetection653x.FRM
' 
'  Description:
'     Inputs digital data into a buffer from a group of two digital
'      ports. Data is latched in only when the input changes.
' 
'  Example Category:
'     DI
' 
'  Example Task Types:
'     BUF, NCH, EXTTIM, BURST, ASYNC
' 
'  List of key parameters:
'     iGroup, iGroupSize, iDir, iPgConfig, iReqSource, iPgTB, iReqInt,
'      ulPatternMask, ulCount, ulAlignIndex, iResource, ulRemaining
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DIG_Grp_Config, NIDAQErrorHandler, DIG_Block_PG_Config,
'      DIG_Trigger_Config, Align_DMA_Buffer, DIG_Block_In,
'      DIG_Block_Check, NIDAQYield, DIG_Block_Clear, NIDAQPlotWaveform
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital signals to ports 0 and 1. Connect the ground
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
    Dim iStartTrigON As Integer
    Dim iStartPol As Integer
    Dim iStopTrig As Integer
    Dim iStopPol As Integer
    Dim ulPtsAfterStopTrig As Long
    Dim ulPattern As Long
    Dim ulPatternMask As Long
    Static piBuffer(200) As Integer
    Dim ulCount As Long
    Dim ulBufferSize As Long
    Dim ulAlignIndex As Long
    Dim iResource As Integer
    Dim ulRemaining As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iGroup% = 1
    iGroupSize% = 2
    iPgConfig% = 1
    iReqSource% = 2
    iPgTB% = 3
    iReqInt% = 10
    ulPatternMask& = 2
    ulCount& = 100
    ulBufferSize& = 200
    iResource% = 11
    ulRemaining& = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Configure group of ports as input, with handshaking.

    iStatus% = DIG_Grp_Config(iDevice%, iGroup%, iGroupSize%, iPort%, iDir%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

'     Configure device for change detection mode.

    iStatus% = DIG_Block_PG_Config(iDevice%, iGroup%, iPgConfig%, iReqSource%, iPgTB%, iReqInt%, iExtGate%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_PG_Config", iIgnoreWarning%)

'     Set the mask to monitor only the significant lines. 			 		Note :
'      if all lines are significant, you do not need to call the 		
'     	following function.

    iStatus% = DIG_Trigger_Config(iDevice%, iGroup%, iStartTrigON%, iStartPol%, iStopTrig%, iStopPol%, ulPtsAfterStopTrig&, ulPattern&, ulPatternMask&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Trigger_Config", iIgnoreWarning%)

'     Align the DMA buffer so that it does not cross a page boundary for
'      AT bus computers. (It is a good idea to keep your buffers smaller
'      than 4kBytes in size.) NOTE: If you change 'iGroup' or
'      'iGroupSize', make sure 'iResource' is changed accordingly.

    iStatus% = Align_DMA_Buffer(iDevice%, iResource%, piBuffer%(0), ulCount&, ulBufferSize&, ulAlignIndex&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Align_DMA_Buffer", iIgnoreWarning%)

'     Start the pattern generation input of 100 "items".

    Call PrintText(txtStatusBox, "Data is read only when it changes on Port 0 Line 1 on I/O connector . ")

    iStatus% = DIG_Block_In(iDevice%, iGroup%, piBuffer%(0), ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_In", iIgnoreWarning%)

    While ((ulRemaining& <>  0) And (iStatus% =  0))

        iStatus% = DIG_Block_Check(iDevice%, iGroup%, ulRemaining&)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Check", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Clear the block operation.

    iStatus% = DIG_Block_Clear(iDevice%, iGroup%)

'     Unconfigure group.

    iStatus% = DIG_Grp_Config(iDevice%, iGroup%, 0, 0, 0)

    iStatus% = NIDAQPlotWaveform(piBuffer%(0), ulCount&, WFM_DATA_I16)

    Call PrintText(txtStatusBox, "The data is available in 'piBuffer'. ")

    If (iStatus% =  0) Then

        Call PrintText(txtStatusBox, "Digital pattern generation input is done! ")

    End If


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


