VERSION 4.00
Begin VB.Form Form1
  Caption = "WFMsingleBufFromDisk"
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
'     WFMsingleBufFromDisk.FRM
' 
'  Description:
'     Outputs a waveform from one analog output channel, using data on a
'      disk file (DAQdata.DAT). You can use the datafile from the
'      'DAQsingleBuftoDisk' example program. (uses high-level NI-DAQ
'      functions)
' 
'  Example Category:
'     AO
' 
'  Example Task Types:
'     BUF, 1CH, BURST, SYNC, INTTIM, INTTRIG, DISK
' 
'  List of key parameters:
'     ulStartPt, ulEndPt, ulIterations
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     Timeout_Config, NIDAQErrorHandler, WFM_from_Disk
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     The analog output signal will be available at AO channel 0. The
'      default analog output mode for the DAQ device will be used.
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
    Dim iNumChans As Integer
    Static piChanVect(1) As Integer
    Dim strFilename As String
    Dim ulStartPt As Long
    Dim ulEndPt As Long
    Dim ulIterations As Long
    Dim dUpdateRate As Double
    Dim iIgnoreWarning As Integer
    Dim lTimeout As Long
    Dim i As Long

    iDevice% = 1
    iNumChans% = 1
    strFilename$ = "DAQdata.dat"
    ulStartPt& = 1
    ulIterations& = 1
    dUpdateRate# = 1000.0
    lTimeout& = 180

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

'     This sets a timeout limit (#Sec * 18ticks/Sec) so that if there is
'      something wrong, the program won't hang on the WFM_from_Disk
'      call.  You may want to change the value of lTimeout if your data
'      file is large.

    iStatus% = Timeout_Config(iDevice%, lTimeout&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Timeout_Config", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "This program will read data from a file called DAQdata.dat. ")

    Call PrintText(txtStatusBox, "It will output the waveform data at a rate of " +  Trim$(Str$(dUpdateRate#)) + "updates/sec. ")

'     Generate data from the entire file, by setting ulEndPt to 0.

'     WARNING: Make sure you have the data file from the DAQtoDSK
'      example program first!

    iStatus% = WFM_from_Disk(iDevice%, iNumChans%, piChanVect%(0), strFilename$, ulStartPt&, ulEndPt&, ulIterations&, dUpdateRate#)

    iRetVal% = NIDAQErrorHandler(iStatus%, "WFM_from_Disk", iIgnoreWarning%)

    If (iStatus% =  0) Then

        Call PrintText(txtStatusBox, "The waveform generation is done! ")

    End If

'     Disable timeouts.

    iStatus% = Timeout_Config(iDevice%, -1)


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


