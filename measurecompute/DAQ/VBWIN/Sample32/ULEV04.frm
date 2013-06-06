VERSION 5.00
Begin VB.Form frmEventDisplay 
   Caption         =   "Universal Library ULEV04"
   ClientHeight    =   2340
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5670
   LinkTopic       =   "Form1"
   ScaleHeight     =   2340
   ScaleWidth      =   5670
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkAutoRestart 
      Caption         =   "Auto Restart"
      Height          =   315
      Left            =   2700
      TabIndex        =   4
      Top             =   1440
      Width           =   1425
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Height          =   495
      Left            =   150
      TabIndex        =   3
      Top             =   1680
      Width           =   1725
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   495
      Left            =   150
      TabIndex        =   2
      Top             =   1170
      Width           =   1725
   End
   Begin VB.CommandButton cmdDisableEvent 
      Caption         =   "cbDisableEvent"
      Height          =   495
      Left            =   150
      TabIndex        =   1
      Top             =   600
      Width           =   1725
   End
   Begin VB.CommandButton cmdEnableEvent 
      Caption         =   "cbEnableEvent"
      Height          =   495
      Left            =   150
      TabIndex        =   0
      Top             =   90
      Width           =   1725
   End
   Begin VB.Label lblSampleCount 
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   315
      Left            =   3420
      TabIndex        =   8
      Top             =   615
      Width           =   2115
   End
   Begin VB.Label lblStatus 
      Caption         =   "IDLE"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   315
      Left            =   3420
      TabIndex        =   7
      Top             =   270
      Width           =   2115
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Status:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   2040
      TabIndex        =   6
      Top             =   270
      Width           =   1335
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Total Count:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   2040
      TabIndex        =   5
      Top             =   615
      Width           =   1335
   End
End
Attribute VB_Name = "frmEventDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'ULEV04================================================================

' File:                         ULEV04

' Library Call Demonstrated:    cbEnableEvent - ON_SCAN_ERROR
'                                             - ON_END_OF_AO_SCAN
'                               cbDisableEvent()
'

' Purpose:                      Paces a waveform out channel 0 using cbAOutScan.
'                               At scan start, it sets the digital output high, and
'                               upon scan completion, it sets the digital output low.
'                               Fatal errors such as UNDERRUN errors, cause the scan
'                               to be aborted.
'
' Demonstration:                Shows how to enable and respond to events.

' Other Library Calls:          cbAOutScan()
'                               cbErrHandling()
'                               cbDOut()

' Special Requirements:         Board 0 must support event handling, paced analog outputs,
'                               and cbDOut.
'
' (c) Copyright 2001-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================
Option Explicit

Const PI = 3.14159265

Const BoardNum = 0                    ' Board number
Const Channel = 0                     ' The D/A channel to output waveform.
Const NumPoints = 2000                ' Number of values in waveform.
Const SampleRate = 1000               ' Sample rate for updating each DAC.
Const Range = BIP5VOLTS               ' Gain for the D/A
Const Options = BACKGROUND            ' Analog output options.

Dim Rate As Long                      ' Sample rate for updating each DAC.
Dim hDataBuffer As Long               ' Defines a variable to contain the handle for
                                      '   memory allocated by Windows through cbWinBufAlloc%()



                                      

' This gets called by MyCallback in mycallback.bas for each ON_END_OF_AO_SCAN events.
' The EventData supplied curresponds to the total number of samples output since the
' start of the cbAOutScan.
Public Sub OnEvent(bd As Integer, EventType As Long, SampleCount As Long)
  Dim ULStat As Integer
    
  ' Give the library a chance to clean up
  ULStat = cbStopBackground(bd, AOFUNCTION)
  
  ' Update how many samples were actually output
  lblSampleCount.Caption = Str(SampleCount)
  lblStatus.Caption = "IDLE"
  
  ' Deassert external device signal
  ULStat = cbDOut(bd, FIRSTPORTA, 0)
      
  If (chkAutoRestart.Value) Then
    ' Start a new scan
    Rate = SampleRate
    ULStat = cbAOutScan(bd, Channel, Channel, NumPoints, Rate, Range, hDataBuffer, Options)
   
    ' signal external device that there's an active scan in progress
    ULStat = cbDOut(bd, FIRSTPORTA, &HFF&)
    lblStatus.Caption = "RUNNING"
  End If
 
   
End Sub

' A scan error occurred; abort and reset the controls.
Public Sub OnScanError(bd As Integer, EventType As Long, ErrorNo As Long)
  Dim ULStat As Integer
     
  ' clean up scan
  ULStat = cbStopBackground(bd, AOFUNCTION)

  ' Reset the bAutoRestart such that the ON_END_OF_AO_SCAN event does
  ' not automatically start a new scan
  chkAutoRestart.Value = 0
  
End Sub




Private Sub cmdDisableEvent_Click()
  Dim ULStat As Integer
  Dim EventTypes As Long
  
  ' we should stop any active scans before disabling events
  ULStat = cbStopBackground(BoardNum, AOFUNCTION)
  
  ' Disconnect and uninstall event handlers
  '   We can disable all the events at once, and disabling events
  '   that were never enabled is harmless
  '
  ' Parameters:
  '   BoardNum          : board for which scan conditions produce events.
  '   EventTypes        : the event types which are being disabled.
  EventTypes = ALL_EVENT_TYPES
  ULStat = cbDisableEvent(BoardNum, EventTypes)
  
End Sub



Private Sub cmdEnableEvent_Click()
  Dim ULStat As Integer
  Dim EventType As Long           ' Type of event to enable
  
  ' Install event handlers for event conditions.
  '
  ' Parameters:
  '    BoardNum                       : The board for which the EventType conditions
  '                                     will generate an event.
  '    EventType = ON_END_OF_AO_SCAN  : Generate an event upon scan completion or end
  '
  '   AddressOf MyCallback  :the address of the user function or event handler
  '                          to call when above event type occurs.
  '                          Note that we can't provide the address of OnEvent directly
  '                          since Microsoft's calling convention for callback functions
  '                          requires that such functions be defined in a standard module
  '                          for Visual Basic. 'MyCallback' will forward the call to OnEvent.
  '   frmEventDisplay        :to make sure that this form handles the event that it set,
  '                          we supply a reference to it by name and dereference
  '                          it in the event handler. Note that the UserData type
  '                          in the event handler must match.
  EventType = ON_END_OF_AO_SCAN
  ULStat = cbEnableEvent(BoardNum, EventType, 0, AddressOf MyCallback, frmEventDisplay)
  If (ULStat = ALREADYACTIVE) Then
    Exit Sub
  End If
  
  ' Since ON_SCAN_ERROR event doesn't use the EventSize, we can set it to anything
  ' we choose without affecting the ON_DATA_AVAILABLE setting.
  ULStat = cbEnableEvent(BoardNum, ON_SCAN_ERROR, 0, AddressOf OnErrorCallback, frmEventDisplay)

  
End Sub



Private Sub cmdStart_Click()
  Dim ULStat As Integer
  
  Rate = SampleRate
  ULStat = cbAOutScan(BoardNum, Channel, Channel, NumPoints, Rate, Range, hDataBuffer, Options)
  If (ULStat = NOERRORS) Then
    ' signal external device that scan is in progress
    ULStat = cbDOut(BoardNum, FIRSTPORTA, &HFF&)
   
    lblStatus.Caption = "RUNNING"
    lblSampleCount.Caption = Str(0)
  End If
  
End Sub



Private Sub cmdStop_Click()
  Dim ULStat As Integer
  
  ' make sure we don't restart the scan ON_END_OF_AO_SCAN
  chkAutoRestart.Value = 0
  
  ULStat = cbStopBackground(BoardNum, AOFUNCTION)

  lblStatus.Caption = "IDLE"
  
  
End Sub



Private Sub Form_Load()
  Dim ULStat As Integer
  Dim index As Long
  Dim VOLTS As Single
  Dim Data(NumPoints) As Integer
   
  ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.

   '  Parameters:
   '     PRINTALL    :all warnings and errors encountered will be printed
   '     DONTSTOP    :if an error is encountered, the program will not stop,
   '                  errors must be handled locally
  ULStat = cbErrHandling(PRINTALL, DONTSTOP)
  
  ' allocate the data buffer
  hDataBuffer = cbWinBufAlloc(NumPoints)
  
  ' create waveform
  For index = 0 To NumPoints - 1
     VOLTS = 4.995 * Sin(2 * PI * index / NumPoints)
     ULStat = cbFromEngUnits(BoardNum, Range, VOLTS, Data(index))
  Next index
  
  ' and store in buffer
  ULStat = cbWinArrayToBuf(Data(0), hDataBuffer, 0, NumPoints)
  
  Rate = SampleRate
  
  ' Prepare FIRSTPORTA for signalling external device
  ULStat = cbDConfigPort(BoardNum, FIRSTPORTA, DIGITALOUT)
  
End Sub

Private Sub Form_Unload(Cancel As Integer)
   Dim ULStat As Integer
   
   ' make sure to shut down
   ULStat = cbStopBackground(BoardNum, AOFUNCTION)
   
   ' and diable any active events
   ULStat = cbDisableEvent(BoardNum, &HFFFF&)
   
   If (hDataBuffer <> 0) Then cbWinBufFree (hDataBuffer)
   hDataBuffer = 0
   
End Sub
