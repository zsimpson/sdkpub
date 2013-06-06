VERSION 5.00
Begin VB.Form frmEventDisplay 
   Caption         =   "Universal Library ULEV02"
   ClientHeight    =   2460
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5700
   LinkTopic       =   "Form1"
   ScaleHeight     =   2460
   ScaleWidth      =   5700
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtEventSize 
      Height          =   315
      Left            =   3330
      TabIndex        =   12
      Text            =   "100"
      Top             =   150
      Width           =   2115
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Height          =   495
      Left            =   150
      TabIndex        =   7
      Top             =   1800
      Width           =   1725
   End
   Begin VB.CheckBox chkAutoRestart 
      Caption         =   "Auto Restart"
      Height          =   315
      Left            =   2880
      TabIndex        =   3
      Top             =   1740
      Width           =   1425
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   495
      Left            =   150
      TabIndex        =   2
      Top             =   1290
      Width           =   1725
   End
   Begin VB.CommandButton cmdDisableEvent 
      Caption         =   "cbDisableEvent"
      Height          =   495
      Left            =   150
      TabIndex        =   1
      Top             =   660
      Width           =   1725
   End
   Begin VB.CommandButton cmdEnableEvent 
      Caption         =   "cbEnableEvent"
      Height          =   495
      Left            =   150
      TabIndex        =   0
      Top             =   150
      Width           =   1725
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Event Size:"
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
      Left            =   1950
      TabIndex        =   11
      Top             =   180
      Width           =   1335
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Latest Sample:"
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
      Left            =   1950
      TabIndex        =   10
      Top             =   1200
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
      Left            =   1950
      TabIndex        =   9
      Top             =   860
      Width           =   1335
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
      Left            =   1950
      TabIndex        =   8
      Top             =   520
      Width           =   1335
   End
   Begin VB.Label lblLatestSample 
      Caption         =   "NA"
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
      Left            =   3330
      TabIndex        =   6
      Top             =   1200
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
      Left            =   3330
      TabIndex        =   5
      Top             =   520
      Width           =   2115
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
      Left            =   3330
      TabIndex        =   4
      Top             =   860
      Width           =   2115
   End
End
Attribute VB_Name = "frmEventDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'ULEV02================================================================

' File:                         ULEV02

' Library Call Demonstrated:    cbEnableEvent - ON_SCAN_ERROR
'                                             - ON_DATA_AVAILABLE
'                                             - ON_END_OF_AI_SCAN
'                               cbDisableEvent()
'

' Purpose:                      Scans a single channel and displays the latest
'                               sample acquired every EventSize or more samples.
'                               Also updates the latest sample upon scan completion
'                               or end. Fatal errors such as OVERRUN errors, cause
'                               the scan to be aborted.

' Demonstration:                Shows how to enable and respond to events.

' Other Library Calls:          cbErrHandling()
'                               cbAInScan()
'
' Special Requirements:         Board 0 must support event handling and have
'                               paced analog inputs.
'

' (c) Copyright 2001-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================
Option Explicit

Const BoardNum = 0                    ' board number
Const Channel = 0                     ' the channel to be sampled.
Const NumPoints = 1000                ' number of data points to collect
Const Range = BIP5VOLTS               ' gain for the channel sampled.
Const SampleRate = 1000               ' rate at which to sample each channel

Dim Rate As Long                      ' sample rate for acquiring data.
Dim hDataBuffer As Long               ' defines a variable to contain the handle for
                                      ' memory allocated by Windows through cbWinBufAlloc%()
Const Options = BACKGROUND + CONVERTDATA  ' Data collection options



' This gets called by MyCallback in mycallback.bas for each ON_DATA_AVAILABLE and
' ON_END_OF_AI_SCAN events. For these event types, the EventData supplied curresponds
' to the number of samples collected since the start of cbAInScan.
Public Sub OnEvent(ByVal bd As Integer, ByVal EventType As Long, ByVal SampleCount As Long)
   Dim ULStat As Integer
   Dim SampleIndex As Long
   Dim Data(1) As Integer
   Dim Value As Single
   
   ' Get the latest sample from the buffer and convert to volts
   SampleIndex = SampleCount - 1
   ULStat = cbWinBufToArray(hDataBuffer, Data(0), SampleIndex, 1)
   ULStat = cbToEngUnits(bd, Range, Data(0), Value)
   
   ' Update the display
   lblSampleCount.Caption = Str(SampleCount)
   lblLatestSample.Caption = Format(Value, "#0.0000 V")
   
   
   If (ON_END_OF_AI_SCAN = EventType) Then
      ' Give the library a chance to clean up
      ULStat = cbStopBackground(bd, AIFUNCTION)
      
      If (chkAutoRestart.Value) Then
         ' Start a new scan
         Rate = SampleRate
         ULStat = cbAInScan(bd, Channel, Channel, NumPoints, Rate, Range, hDataBuffer, Options)
      Else
         ' Reset the status display
         lblStatus = "IDLE"
      End If
   End If
   
End Sub

' A scan error occurred; so, abort and reset the controls.
Public Sub OnScanError(ByVal bd As Integer, ByVal EventType As Long, ByVal ErrorNo As Long)
   Dim ULStat As Integer
   
   ' We don't need to update the display here since that will happen during
   ' the ON_END_OF_AI_SCAN and/or ON_DATA_AVAILABLE events to follow this event
   ' -- yes, this event is handled before any others and this event should be
   ' accompanied by a ON_END_OF_AI_SCAN
   ULStat = cbStopBackground(bd, AIFUNCTION)
   
   ' Reset the bAutoRestart such that the ON_END_OF_AI_SCAN event does
   ' not automatically start a new scan
   chkAutoRestart.Value = 0


End Sub



Private Sub cmdDisableEvent_Click()
  Dim ULStat As Integer

  ' Disable and disconnect all event types with cbDisableEvent()
  '
  ' Since disabling events that were never enabled is harmless,
  ' we can disable all the events at once.
  '
  ' Parameters:
  '   BoardNum         :the number used by CB.CFG to describe this board
  '   ALL_EVENT_TYPES  :all event types will be disabled
  ULStat = cbDisableEvent(BoardNum, ALL_EVENT_TYPES)
  
  
End Sub



Private Sub cmdEnableEvent_Click()
  Dim ULStat As Integer
  Dim EventSize As Long       ' Minimum number of samples to collect
                                  ' between ON_DATA_AVAILABLE events.
  Dim EventType As Long           ' Type of event to enable
  
   ' Enable and connect one or more event types to a single user callback
   ' function using cbEnableEvent().
   '
   ' If we want to attach a single callback function to more than one event
   ' type, we can do it in a single call to cbEnableEvent, or we can do this in
   ' separate calls for each event type. The main disadvantage of doing this in a
   ' single call is that if the call generates an error, we will not know which
   ' event type caused the error. In addition, the same error condition could
   ' generate multiple error messages.
   '
   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   EventType   :the condition that will cause an event to fire
   '   EventSize   :only used for ON_DATA_AVAILABLE to determine how
   '                many samples to collect before firing an event
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
  EventType = ON_DATA_AVAILABLE + ON_END_OF_AI_SCAN
  EventSize = Int(Val(txtEventSize.Text))
  ULStat = cbEnableEvent(BoardNum, EventType, EventSize, AddressOf MyCallback, frmEventDisplay)
  If (ULStat = ALREADYACTIVE) Then
    Exit Sub
  End If
  
  ' Since ON_SCAN_ERROR event doesn't use the EventSize, we can set it to anything
  ' we choose without affecting the ON_DATA_AVAILABLE setting.
  EventType = ON_SCAN_ERROR
  EventSize = 0
  ULStat = cbEnableEvent(BoardNum, EventType, EventSize, AddressOf OnErrorCallback, frmEventDisplay)
  
End Sub



Private Sub cmdStart_Click()
  Dim ULStat As Integer
  
  ' Collect the values with cbAInScan%()
  ' Parameters:
  '   BoardNum%   :the number used by CB.CFG to describe this board
  '   Channel     :the channel of the scan
  '   NumPoints   :the total number of A/D samples to collect
  '   Rate        :sample rate
  '   Range       :the gain for the board
  '   hDataBuffer :the handle to the buffer to hold the data
  '   Options     :data collection options
  Rate = SampleRate
  
  ULStat = cbAInScan(BoardNum, Channel, Channel, NumPoints, Rate, Range, hDataBuffer, Options)
  If (ULStat = NOERRORS) Then
    lblStatus.Caption = "RUNNING"
  Else
     Stop
  End If
  
End Sub



Private Sub cmdStop_Click()
  Dim ULStat As Integer
  
  ' make sure we don't restart the scan ON_END_OF_AI_SCAN
  chkAutoRestart.Value = 0
  
  ULStat = cbStopBackground(BoardNum, AIFUNCTION)
  
  
End Sub



Private Sub Form_Load()
  Dim ULStat As Integer
  
  ULStat = cbErrHandling(PRINTALL, DONTSTOP)
  
  ' initialize cbAInScan parameters
  hDataBuffer = cbWinBufAlloc(NumPoints)
  If hDataBuffer = 0 Then End

  Rate = SampleRate
  
  
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Dim ULStat As Integer
  
   ' make sure to shut down
  ULStat = cbStopBackground(BoardNum, AIFUNCTION)
   
   ' disable any active events
  ULStat = cbDisableEvent(BoardNum, ALL_EVENT_TYPES)
   
   ' and free the data buffer
  If (hDataBuffer <> 0) Then cbWinBufFree (hDataBuffer)
  hDataBuffer = 0
   
End Sub
