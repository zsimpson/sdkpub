VERSION 4.00
Begin VB.Form Form1
  Caption = "TIOcircularBufEventCount"
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
'     TIOcircularBufEventCount.FRM
' 
'  Description:
'     Counts the number of digital pulses (or events) in between gate
'      pulses continuously into a circular-buffer (or double-buffer)
'      using general purpose counter 0 (for NI-TIO based devices)
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     EVENTCNT, CONT, INTTIM, BUF
' 
'  List of key parameters:
'     ulGpctrNum, pulBuffer, pulReadBuf, ulCount, ulReadCount, ulArmed,
'      iGateFasterThanSource
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, GPCTR_Config_Buffer, GPCTR_Read_Buffer,
'      NIDAQYield
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect a gating pulse train to the GATE pin of your counter (PFI
'      38 for 660x devices). Connect the ground reference to the DIG GND
'      pin.
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
    Dim ulGpctrNum As Long
    Static pulBuffer(100) As Long
    Static pulReadBuf(50) As Long
    Dim ulCount As Long
    Dim ulReadCount As Long
    Dim iLoopCount As Integer
    Dim ulInitCount As Long
    Dim ulArmed As Long
    Dim iGateFasterThanSource As Integer
    Dim ulNumPtsToRead As Long
    Dim ulNumPtsRead As Long
    Dim ulReadOffset As Long
    Dim ulTimeOut As Long
    Dim iIgnoreWarning As Integer
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    ulGpctrNum& = ND_COUNTER_0
    ulCount& = 100
    ulReadCount& = 50
    iLoopCount% = 10
    ulArmed& = ND_YES
    ulNumPtsToRead& = 50
    ulTimeOut& = 5
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

'     Set up for a buffered event counting application.

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_BUFFERED_EVENT_CNT)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

'     If you want to use a different GPCTR source, change the last
'      parameter in the following function.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SOURCE, ND_INTERNAL_100_KHZ)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning%)

'     Each time a pulse arrives in the gate, a new value will be latched
'      into the counter and sent to the data buffer.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_GATE, ND_DEFAULT_PFI_LINE)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/GATE", iIgnoreWarning%)

'     Load initial count.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_INITIAL_COUNT, ulInitCount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning%)

'     Enable double-buffer mode.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_BUFFER_MODE, ND_DOUBLE)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/BUFFERMODE", iIgnoreWarning%)

'     Turn on synchronous counting mode if gate is faster than source.

    If (iGateFasterThanSource% =  1) Then

        iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNTING_SYNCHRONOUS, ND_YES)

        iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SYNCHRONOUS COUNTING", iIgnoreWarning%)

    End If

    iStatus% = GPCTR_Config_Buffer(iDevice%, ulGpctrNum&, 0, ulCount&, pulBuffer&(0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Config_Buffer", iIgnoreWarning%)

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Apply your gating pulse train to the GATE of your counter now. ")

'     Loop 10 times.

    Do 

        iStatus% = GPCTR_Read_Buffer(iDevice%, ulGpctrNum&, ND_READ_MARK, ulReadOffset&, ulNumPtsToRead&, ulTimeOut&, ulNumPtsRead&, pulReadBuf&(0))

        iLoopCount = iLoopCount- 1

        Call PrintText(txtStatusBox,  Trim$(Str$(ulNumPtsRead&)) + "points read into buffer 'pulReadBuf' (loop count " +  Trim$(Str$(iLoopCount%)) + "). ")

        DoEvents

    Loop While ((iLoopCount% >  0) And (iStatus% =  0))

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Read_Buffer", iIgnoreWarning%)

'     CLEANUP - Don't check for errors on purpose.

'     Restore buffer mode to SINGLE.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_BUFFER_MODE, ND_SINGLE)

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    Call PrintText(txtStatusBox, "GPCTR circular buffered event counting done! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


