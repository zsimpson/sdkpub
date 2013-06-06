VERSION 4.00
Begin VB.Form Form1
  Caption = "TIOGPStimeNsoftwareEvents"
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
'     TIOGPStimeNsoftwareEvents.FRM
' 
'  Description:
'     This example measures time, using a real time clock found in the
'      6608 timing devices.  By default, the real time clock increments
'      based upon the internal 20 Mhz clock.  Also, the real time clock
'      can be synchronized by a DC TTL IRIG-B or a pulse per second
'      (PPS) signal by attaching the synchronization signal to the
'      synchronization line of the real time clock. The current time of
'      the real time clock is read 100 times in a loop or until an error
'      occurs.
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     TIMING
' 
'  List of key parameters:
'     iDevice, ulGpctrNum, ulGpctrSynchronizationLine, ulInitialSeconds,
'      ulSeconds, ulNanoSeconds
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, NIDAQDelay, GPCTR_Watch
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Apply the synchronization source to PFI 6.
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
    Dim ulGpctrSynchronizationLine As Long
    Dim ulInitialSeconds As Long
    Dim ulLoopCount As Long
    Dim iIgnoreWarning As Integer
    Dim ulSeconds As Long
    Dim ulNanoSeconds As Long

    iDevice% = 1
    ulGpctrNum& = ND_CLOCK_0
    ulGpctrSynchronizationLine& = ND_PFI_6

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/RESET", iIgnoreWarning%)

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_SIMPLE_TIME_MSR)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

'     To change the synchronization line, change the
'      ulGpctrSynchronizationLine variable in the variable declarations.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SYNCHRONIZATION_LINE, ulGpctrSynchronizationLine&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SYNCHRONIZATION", iIgnoreWarning%)

'     To use a different GPCTR synchronization method, change the last
'      parameter in the following function.

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SYNCHRONIZATION_METHOD, ND_IRIG_B)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SYNCHRONIZATION_METHOD", iIgnoreWarning%)

'     To use the time previously stored in the real time clock, change
'      the ND_INITIAL_SECONDS_ENABLE parameter to ND_NO

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_INITIAL_SECONDS_ENABLE, ND_YES)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/INITIAL_SECONDS_ENABLE", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_INITIAL_SECONDS, ulInitialSeconds&)

'     NOTE - It is only necessary to program the initial seconds if you
'      are not using IRIG synchronization. In the IRIG synchronization
'      case the real time clock will recieve its time information from
'      the data stream.

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/INITIAL_SECONDS", iIgnoreWarning%)

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

'     Delay for two seconds to ensure the clock is synchronized.

    Call NIDAQDelay(2)

    Call PrintText(txtStatusBox, "Time N Software Events started... ")

    Do 

'         A Snapshot call locks in the current time.

        iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_SNAPSHOT)

        iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/SNAPSHOT", iIgnoreWarning%)

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_SECONDS, ulSeconds&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/SECONDS", iIgnoreWarning%)

        iStatus% = GPCTR_Watch(iDevice%, ulGpctrNum&, ND_NANO_SECONDS, ulNanoSeconds&)

        iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/NANO_SECONDS", iIgnoreWarning%)

        Call PrintText(txtStatusBox, "Software trigger occurred at time " +  Trim$(Str$(ulSeconds&)) + "seconds " +  Trim$(Str$(ulNanoSeconds&)) + "nanoseconds ")

        ulLoopCount = ulLoopCount+ 1

'         change the following comparison value to record more times.

    Loop While ((ulLoopCount& <  100) And (iStatus% =  0))

'     CLEANUP - Don't check for errors on purpose.

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    Call PrintText(txtStatusBox, "Time N Software Events done! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


