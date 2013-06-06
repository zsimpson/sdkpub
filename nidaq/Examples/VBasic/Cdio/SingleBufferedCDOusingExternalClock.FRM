VERSION 4.00
Begin VB.Form Form1
  Caption = "SingleBufferedCDOusingExternalClock"
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
'     SingleBufferedCDOusingExternalClock.FRM
' 
'  Description:
'     Writes a buffer of digital data to the digital output lines at the
'      rate of the external clock.
' 
'  Example Category:
'     CDIO
' 
'  Example Task Types:
'     BUF, NCH, EXTTIM, BURST
' 
'  List of key parameters:
'     ulCount, iNumLines, iDOReqSource
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     DIG_Line_Config, NIDAQErrorHandler, NIDAQMakeBuffer,
'      DIG_Grp_Config, DIG_Grp_Mode, DIG_Block_PG_Config, DIG_Block_Out,
'      DIG_Block_Check, NIDAQYield
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The digital output signals will be available at pins DIO0-DIO7.
'      Connect the ground reference to the DIG GND pin. Connect the
'      external clock signal to the GPCTR0 Out pin. (please refer to
'      your hardware user manual for details)
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
    Dim iLineCount As Integer
    Dim iGroupSize As Integer
    Dim iPort As Integer
    Dim iNumLines As Integer
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Static iDOBuffer(500) As Integer
    Dim iDOGroup As Integer
    Dim iDOReqSource As Integer
    Dim iOutLineDirection As Integer
    Dim iOutGroupDirection As Integer
    Dim iDOEdge As Integer
    Dim ulRemaining As Long
    Dim i As Long

    iDevice% = 1
    iDBmodeON% = 1
    iPGmodeOn% = 1
    ulCount& = 1000
    iGroupSize% = 1
    iNumLines% = 8
    iYieldON% = 1
    iDOGroup% = 2
    iDOReqSource% = 1
    iOutLineDirection% = 5
    iOutGroupDirection% = 1
    ulRemaining& = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Configure the digital lines for the correct direction.

    While (iLineCount% <  iNumLines%)

        iStatus% = DIG_Line_Config(iDevice%, iPort%, iLineCount%, iOutLineDirection%)

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

'     Correlate the output to the external clock.  Note, you will not be
'      able to use GPCTR0 for pulse train generation when using an
'      external clock.

    iStatus% = DIG_Block_PG_Config(iDevice%, iDOGroup%, iPGmodeOn%, iDOReqSource%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Dig_Block_PG_Config", iIgnoreWarning%)

'     Start generating data.

    iStatus% = DIG_Block_Out(iDevice%, iDOGroup%, iDOBuffer%(0), ulCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Out", iIgnoreWarning%)

    While ((ulRemaining& >  0) And (iStatus% =  0))

'         Wait until the data is finished outputting.

        iStatus% = DIG_Block_Check(iDevice%, iDOGroup%, ulRemaining&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Block_Check", iIgnoreWarning%)

        DoEvents

    Wend

'     Clear all operations and reset the board to its default state

    iStatus% = DIG_Grp_Config(iDevice%, iDOGroup%, 0, 0, 0)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DIG_Grp_Config", iIgnoreWarning%)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


