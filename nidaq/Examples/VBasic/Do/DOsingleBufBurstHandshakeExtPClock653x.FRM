VERSION 4.00
Begin VB.Form Form1
  Caption = "DOsingleBufBurstHandshakeExtPClock653x"
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
'     DOsingleBufBurstHandshakeExtPClock653x.FRM
' 
'  Description:
'     Outputs digital data into a buffer from a group of two digital
'      ports using burst mode hanshaking protocol and external PCLK(for
'      DIO-32HS series devices)
' 
'  Example Category:
'     DO
' 
'  Example Task Types:
'     BUF, NCH, HANDSHK, BURST, ASYNC
' 
'  List of key parameters:
'     iGroup, iGroupSize, iDir, iSignal, iEdge, iReqPol, iAckPol,
'      iAckDelayTime, ulCount, ulRemaining
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     NIDAQMakeBuffer, DIG_Grp_Config, NIDAQErrorHandler, DIG_Grp_Mode,
'      DIG_Block_Out, DIG_Block_Check, NIDAQYield, DIG_Block_Clear
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The digital signals will be on ports 0 and 1. Connect the ground
'      reference to the DIG GND pin. Connect the handshaking signal to
'      the appropriate handshaking I/O pin (please refer to your
'      hardware user manual for details)
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
    Dim iSignal As Integer
    Dim iEdge As Integer
    Dim iReqPol As Integer
    Dim iAckPol As Integer
    Dim iAckDelayTime As Integer
    Static piBuffer(100) As Integer
    Dim ulCount As Long
    Dim ulRemaining As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iGroup% = 1
    iGroupSize% = 2
    iDir% = 1
    iSignal% = 3
    ulCount& = 100
    ulRemaining& = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = NIDAQMakeBuffer(piBuffer%(0), ulCount&, WFM_DATA_I16)

    If (iStatus% =  0) Then

'         Configure group of ports as output, with handshaking.

        iStatus% = DIG_Grp_Config(iDevice%, iGroup%, iGroupSize%, iPort%, iDir%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)

'         Configure handshaking parameters for pulsed, leading edge,
'          active high request and acknowledge with no delay

        iStatus% = DIG_Grp_Mode(iDevice%, iGroup%, iSignal%, iEdge%, iReqPol%, iAckPol%, iAckDelayTime%)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Mode", iIgnoreWarning%)

'         You may want to call 'Align_DMA_Buffer' at this point if you
'          have a buffer larger than 4kBytes in size and if your
'          handshaking signals occur at intervals faster than 50us.

'         Start the handshaked buffered output of 100 "items".

        iStatus% = DIG_Block_Out(iDevice%, iGroup%, piBuffer%(0), ulCount&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Out", iIgnoreWarning%)

        Call PrintText(txtStatusBox, "Apply your handshaking signals to the appropriate handshaking I/O pins. ")

        While ((ulRemaining& <>  0) And (iStatus% =  0))

            iStatus% = DIG_Block_Check(iDevice%, iGroup%, ulRemaining&)

            DoEvents

        Wend

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Check", iIgnoreWarning%)

'         CLEANUP - Don't check for errors on purpose.

'         Clear the block operation.

        iStatus% = DIG_Block_Clear(iDevice%, iGroup%)

'         Unconfigure group.

        iStatus% = DIG_Grp_Config(iDevice%, iGroup%, 0, 0, 0)

        Call PrintText(txtStatusBox, "Digital handshaked buffered output is done! ")

    Else

        Call PrintText(txtStatusBox, "The buffer was not made correctly. " + "Check the parameters for NIDAQMakeBuffer. ")

    End If


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


