VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "DAQStart"
   ClientHeight    =   3195
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   6360
   Height          =   3600
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   6360
   Top             =   1170
   Width           =   6480
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   615
      Left            =   4680
      TabIndex        =   2
      Top             =   2520
      Width           =   1575
   End
   Begin VB.CommandButton cmdDoOperation 
      Caption         =   "&Do Operation"
      Height          =   615
      Left            =   2880
      TabIndex        =   1
      Top             =   2520
      Width           =   1575
   End
   Begin VB.TextBox txtStatusBox 
      Height          =   2295
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   6135
   End
   Begin GeneralDAQEventLib.GeneralDAQEvent GeneralDAQEvent1 
      Left            =   120
      Top             =   2520
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   64
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
' ********************************************************************
'
'  Example Program:
'     Event1.FRM
'
'  Description:
'     Read a waveform from one analog input channel using internal
'      timing (uses low-level NI-DAQ functions and DAQEvent custom
'      control)
'
'  Example Category:
'     EVENT
'
'  Example Task Types:
'     BUF, 1CH, BURST, IMMED, ASYNC, INTTRIG
'
'  List of key parameters:
'     iDAQstopped
'
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
'
'  List of NI-DAQ Functions used in this example:
'     DAQ_Rate, DAQ_Start, NIDAQErrorHandler, DAQ_Check, DAQ_VScale,
'      DAQ_Clear
'
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
'
'  Pin Connection Information:
'     Connect your analog signal to AI channel 1. The default analog
'      input mode for the DAQ device will be used.
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
Dim iDevice As Integer
Dim ulCount As Long


' ************************************************************************
' SUBROUTINE:  CleanUp
' DESCRIPTION: Cleans up the DAQ operation.
' INPUTS:      none
' ************************************************************************
Sub CleanUp()

'   Turn off DAQ Events
    GeneralDAQEvent1.Enabled = False
    GeneralDAQEvent1.Refresh

'   Don't check errors on purpose.
    Call DAQ_Clear(iDevice%)
    
End Sub

' ************************************************************************
' SUBROUTINE:  PrintText
' DESCRIPTION: PrintText to desired TextBox (upto 4096 characters)
' INPUTS:      txtBox - TextBox to print on
'              strText - Text to print
' ************************************************************************
Sub PrintText(txtBox As TextBox, strText As String)

    txtBox.Text = Right$(txtBox.Text + strText$ + Chr$(13) + Chr$(10), LEN_PRINTTEXT)

    txtBox.SelStart = Len(CStr(txtBox.Text))

End Sub


' ************************************************************************
' SUBROUTINE:  cmdExit_Click
' DESCRIPTION: Clean up and exit
' ************************************************************************
Sub cmdExit_Click()

    Call CleanUp
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
    Dim iChan As Integer
    Dim iGain As Integer
    Dim dSampRate As Double
    Dim dGainAdjust As Double
    Dim dOffset As Double
    Dim iUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Static piBuffer(5000) As Integer
    Dim iIgnoreWarning As Integer
    Dim i As Long

    iDevice% = 1
    iChan% = 1
    iGain% = 1
    dSampRate# = 1000#
    ulCount& = 5000
    dGainAdjust# = 1#
    dOffset# = 0#

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    ' Convert sample rate (S/sec) to appropriate timebase and sample
    ' interval values.

    iStatus% = DAQ_Rate(dSampRate#, iUnits%, iSampTB%, uSampInt%)
    
    ' setup the GeneralDAQEvent control
    ' - this is different from the DAQStart example
    GeneralDAQEvent1.Board = iDevice%
    GeneralDAQEvent1.DAQEvent = 1
    GeneralDAQEvent1.ChanStr = "AI" + Trim$(Str$(iChan%))
    GeneralDAQEvent1.DAQTrigVal0 = ulCount& / 10
    GeneralDAQEvent1.Enabled = True
    GeneralDAQEvent1.Refresh
    
    ' Acquire data from a single channel

    iStatus% = DAQ_Start(iDevice%, iChan%, iGain%, piBuffer%(0), ulCount&, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Start", iIgnoreWarning%)

    ' Also, there is no polling for completion.
    ' See the GeneralDAQEvent1_Fire() routine for the event handler.


End Sub


Private Sub GeneralDAQEvent1_Fire(DoneFlag As Integer, Scans As Long)

    If (DoneFlag Or Scans >= ulCount) Then
        Call CleanUp
        Call PrintText(txtStatusBox, "Acquisition is done!")

        ' Re-enable buttons
        cmdDoOperation.Enabled = True
        cmdExit.Enabled = True

    Else
        ' you can use DAQ_Monitor to index into the data, or you can
        ' index into the piBuffer yourself at this point.
        Call PrintText(txtStatusBox, Str$(Scans&) + " scans have been acquired.")
    End If

End Sub
