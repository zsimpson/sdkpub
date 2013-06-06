VERSION 4.00
Begin VB.Form Form1
  Caption = "9513freqMeasure"
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
'     9513freqMeasure.FRM
' 
'  Description:
'     Measures the frequency of a digital pulse train using counter 5
'      and a 1 second pulse generated from counter 1 (for devices with
'      the Am9513 counter/timer). See NOTE below about measuring
'      frequencies above 65535Hz.
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     FREQM, INTTIM
' 
'  List of key parameters:
'     iCtr2, iGateMode2, iTimeBase1, iTimeBase2, uPulseWidth
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     CTR_Config, NIDAQErrorHandler, CTR_Period, CTR_Pulse, NIDAQDelay,
'      CTR_State, NIDAQYield, CTR_EvRead, CTR_Reset
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Connect your digital pulse train to the SOURCE5 pin. Also, connect
'      OUT1 to GATE5. Connect the ground reference to the DIG GND pin.
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
    Dim iCtr1 As Integer
    Dim iEdgeMode As Integer
    Dim iGateMode1 As Integer
    Dim iCtr2 As Integer
    Dim iGateMode2 As Integer
    Dim iOutType As Integer
    Dim iOutPolarity As Integer
    Dim iTimeBase1 As Integer
    Dim iTimeBase2 As Integer
    Dim uDelay As Integer
    Dim uPulseWidth As Integer
    Dim iOutState1 As Integer
    Dim iOverFlow As Integer
    Dim uCount As Integer
    Dim iIgnoreWarnings As Integer
    Dim iYieldON As Integer

    iDevice% = 1
    iCtr1% = 1
    iCtr2% = 5
    iGateMode2% = 1
    iTimeBase1% = 3
    iTimeBase2% = 10
    uDelay% = 3
    uPulseWidth% = 10000
    iOutState1% = 1
    iYieldON% = 1

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     Setup iCtr1 for counting rising edges with no gating.

    iStatus% = CTR_Config(iDevice%, iCtr1%, iEdgeMode%, iGateMode1%, iOutType%, iOutPolarity%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Config/CTR1", iIgnoreWarnings%)

'     If you are using a PC-TIO-10 which as a hardwired 5MHz timebase
'      connected to SOURCE5, you will need to use a counter other than
'      counter 5 for 'iCtr2' and change 'iTimebase2' accordingly.

'     Setup iCtr2 for counting rising edges with level-HIGH gating.

    iStatus% = CTR_Config(iDevice%, iCtr2%, iEdgeMode%, iGateMode2%, iOutType%, iOutPolarity%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Config/CTR2", iIgnoreWarnings%)

'     Setup iCtr2 to do period measurement using its SOURCE as timebase.

    iStatus% = CTR_Period(iDevice%, iCtr2%, iTimeBase2%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Period", iIgnoreWarnings%)

'     Output a 1 sec logic HIGH pulse from iCtr1.

    iStatus% = CTR_Pulse(iDevice%, iCtr1%, iTimeBase1%, uDelay%, uPulseWidth%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Pulse", iIgnoreWarnings%)

'     Make sure the first pulse has started, then the second pulse will
'      occur after the first is completed.

    iRetVal% = NIDAQDelay(0.05)

'     This second pulse is needed to move the data from the first pulse
'      to the HOLD register where it can be read.

    iStatus% = CTR_Pulse(iDevice%, iCtr1%, iTimeBase1%, uDelay%, uPulseWidth%)

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_Pulse", iIgnoreWarnings%)

'     The delay here is to ensure that the first time CTR_State is
'      called, it will sense a HIGH state. Some faster computers may get
'      to the CTR_State call while the output pulse is still low.

    iRetVal% = NIDAQDelay(0.05)

    Call PrintText(txtStatusBox, "Wait until the output of iCtr1 goes LOW. ")

    While ((iOutState1% <>  0) And (iStatus% =  0))

        iStatus% = CTR_State(iDevice%, iCtr1%, iOutState1%)

        DoEvents

    Wend

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_State", iIgnoreWarnings%)

    Call PrintText(txtStatusBox, "Gate pulse should be complete - now read iCtr2. ")

'     NOTE: If you connect a signal with a frequency greater than
'      65535Hz or get more than 65535 pulses during the read period,
'      this will return incorrect data. If you want to read frequencies
'      greater than 65535Hz, you can setup CTR_Pulse on iCtr1 to
'      generate a pulse for a fraction of a second.  See HINT below.

    iStatus% = CTR_EvRead(iDevice%, iCtr2%, iOverFlow%, uCount%)

    If ((uCount% >=  3) And (iStatus% =  0)) Then

'         'uCount' must be greater than 3 for valid count. the count
'          corresponds to the number of microsecond ticks read by the
'          counter while the gate was high. HINT: If you use a shorter
'          gate pulse, you can measure the frequency with higher
'          accuracy. The equation is: (freq in Hz) = (count) / (length
'          of gate pulse in seconds).

        Call PrintText(txtStatusBox, "The frequency is " +  Trim$(Str$(uCount%)) + "Hz. ")

    Else

        Call PrintText(txtStatusBox, "WARNING- The counter was read prematurely. ")

    End If

    iRetVal% = NIDAQErrorHandler(iStatus%, "CTR_EvRead", iIgnoreWarnings%)

'     CLEANUP - Don't check for errors on purpose.

'     Reset counters to initial state.

    iStatus% = CTR_Reset(iDevice%, iCtr1%, 1)

    iStatus% = CTR_Reset(iDevice%, iCtr2%, 1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


