VERSION 4.00
Begin VB.Form Form1
  Caption = "DAQdoubleBuf"
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
'     DAQdoubleBuf.FRM
' 
'  Description:
'     Read a waveform from one analog input channel continuously using
'      internal timing (uses low-level NI-DAQ functions)
' 
'  Example Category:
'     AI
' 
'  Example Task Types:
'     BUF, 1CH, CONT, INTTIM, ASYNC, INTTRIG
' 
'  List of key parameters:
'     iDBmodeON, ulCount, iSampTB, iHalfReady, lTimeout
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     Timeout_Config, NIDAQErrorHandler, DAQ_Rate, DAQ_DB_Config,
'      DAQ_Start, DAQ_DB_HalfReady, DAQ_DB_Transfer, NIDAQYield,
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
    Dim iChan As Integer
    Dim iGain As Integer
    Dim ulCount As Long
    Dim iLoopCount As Integer
    Dim iHalfBufsToRead As Integer
    Dim dSampRate As Double
    Dim iUnits As Integer
    Dim iSampTB As Integer
    Dim uSampInt As Integer
    Static piBuffer(1000) As Integer
    Static piHalfBuffer(500) As Integer
    Dim iHalfReady As Integer
    Dim iDAQstopped As Integer
    Dim ulPtsTfr As Long
    Dim iIgnoreWarning As Integer
    Dim lTimeout As Long
    Dim iYieldON As Integer
    Dim i As Long

    iDevice% = 1
    iDBmodeON% = 1
    iChan% = 1
    iGain% = 1
    ulCount& = 1000
    iHalfBufsToRead% = 20
    dSampRate# = 1000.0
    lTimeout& = 180
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the DAQ_DB_Transfer
'      call.

    iStatus% = Timeout_Config(iDevice%, lTimeout&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

'     Convert sample rate (S/sec) to appropriate timebase and sample
'      interval values.

'     NOTE: If you are using a DSA device, call DAQ_Set_Clock instead.
'      Refer to NI-DAQ Function Reference Manual for details.

    iStatus% = DAQ_Rate(dSampRate#, iUnits%, iSampTB%, uSampInt%)

'     Turn ON software double-buffered mode.

    iStatus% = DAQ_DB_Config(iDevice%, iDBmodeON%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_Config", iIgnoreWarning%)

'     Acquire data indefinitely into circular buffer from a single
'      channel. If you want to acquire from multiple channels, use
'      SCAN_Start of Lab_ISCAN_Start.

'     NOTE FOR DSA devices... DSA devices can format samples in a
'      left-justified format in 32-bit data words. This means that the
'      most significant bits of the data word contain the bits generated
'      by the converter. When allocating data buffers, be sure to
'      account for the 32-bit data width. Even though a number of
'      DAQ/SCAN/WFM functions are declared to accept pointers to 16-bit
'      data buffers, you should pass pointers to 32-bit data buffers.
'      Also, modify the iGain parameter to be in units of dB.

    iStatus% = DAQ_Start(iDevice%, iChan%, iGain%, piBuffer%(0), ulCount&, iSampTB%, uSampInt%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_Start", iIgnoreWarning%)

'     Loop until 'iHalfBufsToRead' half buffers are acquired. HINT: You
'      can be doing other foreground tasks during this time.

    Call PrintText(txtStatusBox, "Continuous acquisition has started. ")

    Call PrintText(txtStatusBox, "HINT: You can add your own graphing calls in the while loop. ")

    While ((iLoopCount% <  iHalfBufsToRead%) And (iStatus% =  0))

        iStatus% = DAQ_DB_HalfReady(iDevice%, iHalfReady%, iDAQstopped%)

        If ((iHalfReady% =  1) And (iStatus% =  0)) Then

'             Grab half-buffer of data into 'piHalfBuffer'. You can
'              scale the data with DAQ_VScale, or store it to disk using
'              your own file I/O calls.

'             NOTE FOR DSA devices... DSA devices can format samples in
'              a left-justified format in 32-bit data words. This means
'              that the most significant bits of the data word contain
'              the bits generated by the converter. When allocating data
'              buffers, be sure to account for the 32-bit data width.
'              Even though a number of DAQ/SCAN/WFM functions are
'              declared to accept pointers to 16-bit data buffers, you
'              should pass pointers to 32-bit data buffers.

            iStatus% = DAQ_DB_Transfer(iDevice%, piHalfBuffer%(0), ulPtsTfr&, iDAQstopped%)

            iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_Transfer", 0)

            iLoopCount = iLoopCount+ 1

            Call PrintText(txtStatusBox,  Trim$(Str$(iLoopCount%)) + "Half buffers acquired. ")

        Else

            iRetVal% = NIDAQErrorHandler(iStatus%, "DAQ_DB_HalfReady", 0)

        End If

        DoEvents

    Wend

    Call PrintText(txtStatusBox, "Continuous acquisition is done! ")

'     CLEANUP - Don't check for errors on purpose.

    iStatus% = DAQ_Clear(iDevice%)

'     Set DB mode back to initial state.

    iStatus% = DAQ_DB_Config(iDevice%, iDBmodeOFF%)

'     Disable timeouts.

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


