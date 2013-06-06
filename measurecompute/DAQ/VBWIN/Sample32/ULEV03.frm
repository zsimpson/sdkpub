VERSION 5.00
Begin VB.Form frmEventDisplay 
   Caption         =   "Universal Library ULEV03"
   ClientHeight    =   3630
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6510
   LinkTopic       =   "Form1"
   ScaleHeight     =   3630
   ScaleWidth      =   6510
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkAutoRestart 
      Caption         =   "Auto Restart"
      Height          =   315
      Left            =   330
      TabIndex        =   4
      Top             =   3060
      Width           =   1425
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   1620
      Width           =   1725
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   1110
      Width           =   1725
   End
   Begin VB.CommandButton cmdDisableEvent 
      Caption         =   "cbDisableEvent"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   1725
   End
   Begin VB.CommandButton cmdEnableEvent 
      Caption         =   "cbEnableEvent"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   90
      Width           =   1725
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "PreCount"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   30
      TabIndex        =   48
      Top             =   2640
      Width           =   795
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Satus:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   240
      TabIndex        =   47
      Top             =   2235
      Width           =   555
   End
   Begin VB.Label lblPreCount 
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
      Height          =   285
      Left            =   900
      TabIndex        =   46
      Top             =   2580
      Width           =   1155
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
      Height          =   285
      Left            =   900
      TabIndex        =   45
      Top             =   2190
      Width           =   1155
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   9
      Left            =   5370
      TabIndex        =   44
      Top             =   3225
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   8
      Left            =   5370
      TabIndex        =   43
      Top             =   2874
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   7
      Left            =   5370
      TabIndex        =   42
      Top             =   2526
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   6
      Left            =   5370
      TabIndex        =   41
      Top             =   2178
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   5
      Left            =   5370
      TabIndex        =   40
      Top             =   1830
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   4
      Left            =   5370
      TabIndex        =   39
      Top             =   1482
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   3
      Left            =   5370
      TabIndex        =   38
      Top             =   1134
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   2
      Left            =   5370
      TabIndex        =   37
      Top             =   786
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   1
      Left            =   5370
      TabIndex        =   36
      Top             =   438
      Width           =   945
   End
   Begin VB.Label lblPosttriggerData 
      Height          =   255
      Index           =   0
      Left            =   5370
      TabIndex        =   35
      Top             =   90
      Width           =   945
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   9
      Left            =   3120
      TabIndex        =   34
      Top             =   3195
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   8
      Left            =   3120
      TabIndex        =   33
      Top             =   2843
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   7
      Left            =   3120
      TabIndex        =   32
      Top             =   2497
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   6
      Left            =   3120
      TabIndex        =   31
      Top             =   2151
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   5
      Left            =   3120
      TabIndex        =   30
      Top             =   1805
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   4
      Left            =   3120
      TabIndex        =   29
      Top             =   1459
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   3
      Left            =   3120
      TabIndex        =   28
      Top             =   1113
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   2
      Left            =   3120
      TabIndex        =   27
      Top             =   767
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   1
      Left            =   3120
      TabIndex        =   26
      Top             =   421
      Width           =   915
   End
   Begin VB.Label lblPretriggerData 
      Height          =   285
      Index           =   0
      Left            =   3120
      TabIndex        =   25
      Top             =   75
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +9"
      Height          =   255
      Index           =   19
      Left            =   4410
      TabIndex        =   24
      Top             =   3225
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +8"
      Height          =   255
      Index           =   18
      Left            =   4410
      TabIndex        =   23
      Top             =   2874
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +7"
      Height          =   255
      Index           =   17
      Left            =   4410
      TabIndex        =   22
      Top             =   2526
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +6"
      Height          =   255
      Index           =   16
      Left            =   4410
      TabIndex        =   21
      Top             =   2178
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +5"
      Height          =   255
      Index           =   15
      Left            =   4410
      TabIndex        =   20
      Top             =   1830
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +4"
      Height          =   255
      Index           =   14
      Left            =   4410
      TabIndex        =   19
      Top             =   1482
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +3"
      Height          =   255
      Index           =   13
      Left            =   4410
      TabIndex        =   18
      Top             =   1134
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +2"
      Height          =   255
      Index           =   12
      Left            =   4410
      TabIndex        =   17
      Top             =   786
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +1"
      Height          =   255
      Index           =   11
      Left            =   4410
      TabIndex        =   16
      Top             =   438
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger +0"
      Height          =   255
      Index           =   10
      Left            =   4410
      TabIndex        =   15
      Top             =   90
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -1"
      Height          =   255
      Index           =   9
      Left            =   2130
      TabIndex        =   14
      Top             =   3210
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -2"
      Height          =   255
      Index           =   8
      Left            =   2130
      TabIndex        =   13
      Top             =   2858
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -3"
      Height          =   255
      Index           =   7
      Left            =   2130
      TabIndex        =   12
      Top             =   2512
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -4"
      Height          =   255
      Index           =   6
      Left            =   2130
      TabIndex        =   11
      Top             =   2166
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -5"
      Height          =   255
      Index           =   5
      Left            =   2130
      TabIndex        =   10
      Top             =   1820
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -6"
      Height          =   255
      Index           =   4
      Left            =   2130
      TabIndex        =   9
      Top             =   1474
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -7"
      Height          =   255
      Index           =   3
      Left            =   2130
      TabIndex        =   8
      Top             =   1128
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -8"
      Height          =   255
      Index           =   2
      Left            =   2130
      TabIndex        =   7
      Top             =   782
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -9"
      Height          =   255
      Index           =   1
      Left            =   2130
      TabIndex        =   6
      Top             =   436
      Width           =   915
   End
   Begin VB.Label lbl 
      Caption         =   "Trigger -10"
      Height          =   255
      Index           =   0
      Left            =   2130
      TabIndex        =   5
      Top             =   90
      Width           =   915
   End
End
Attribute VB_Name = "frmEventDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'ULEV03================================================================

' File:                         ULEV03

' Library Call Demonstrated:    cbEnableEvent - ON_SCAN_ERROR
'                                             - ON_PRETRIGGER
'                                             - ON_END_OF_AI_SCAN
'                               cbDisableEvent()
'                               cbAPretrig()

' Purpose:                      Scans a single channel with cbAPretrig and sets
'                               digital outputs high upon first trigger event.
'                               Upon scan completion, it displays immediate points
'                               before and after the trigger. Fatal errors such as
'                               OVERRUN errors, cause the scan to be aborted, but TOOFEW
'                               errors are ignored.
'
' Demonstration:                Shows how to enable and respond to events.

' Other Library Calls:          cbErrHandling()
'                               cbDOut()

' Special Requirements:         Board 0 must support event handling, cbAPretrig,
'                               and cbDOut.
'

' (c) Copyright 2001-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================
Option Explicit

Const BoardNum = 0                    ' Board number
Const CHANNEL = 0                     ' The channel to be sampled.
Const NumPoints = 5000               ' Number of data points to collect
Const BUFFERSIZE = 5512              ' Buffer needs to be big enough to hold NumPoints plus
                                      '   up to 1 full blocksize of data -- 512 is sufficient
                                      '   for most boards.
Const PRECOUNT = 1000                 ' Number of samples to acquire before the trigger
Const SAMPLERATE = 2000               ' Sample rate for acquiring data.
Const Range = BIP5VOLTS               ' Gain for the channel sampled.
Const Options = BACKGROUND            ' Data collection options

Dim VarPreCount As Long
Dim TotalCount As Long
Dim Rate As Long                      ' Sample rate for acquiring data.
Dim hDataBuffer As Long               ' Defines a variable to contain the handle for
                                      '   memory allocated by Windows through cbWinBufAlloc%()


Dim Data(BUFFERSIZE) As Integer
Dim ChanTag(BUFFERSIZE) As Integer
Dim ActualPreCount As Long            ' Actual number of samples acquired at time of trigger
                                

' This gets called by MyCallback in mycallback.bas for each ON_PRETRIGGER and
' ON_END_OF_AI_SCAN events. For the ON_PRETRIGGER event, the EventData supplied
' corresponds to the number of pretrigger samples available in the buffer. For the
' ON_END_OF_AI_SCAN event, the EventData supplied corresponds to the number of samples
' aquired since the start of cbAPretrig.
Public Sub OnEvent(bd As Integer, EventType As Long, SampleCount As Long)
  Dim ULStat As Integer
  Dim Value As Single
  Dim PreTriggerIndex As Long
  Dim PostTriggerIndex As Long
  Dim Offset As Long
  
  If (ON_PRETRIGGER = EventType) Then
   
    ' store actual number of pre-trigger samples collected
    ActualPreCount = SampleCount
    lblPreCount.Caption = Str(SampleCount)
    
    ' signal external device that trigger has been detected
    ULStat = cbDOut(bd, FIRSTPORTA, &HFF&)
    
  ElseIf (ON_END_OF_AI_SCAN = EventType) Then
      ' Give the library a chance to clean up
      ULStat = cbStopBackground(bd, AIFUNCTION)
      lblStatus.Caption = "IDLE"
      
      ' Get the data and align it so that oldest data is first
      ULStat = cbWinBufToArray(hDataBuffer, Data(0), 0, BUFFERSIZE - 1)
      ULStat = cbAConvertPretrigData(bd, VarPreCount, TotalCount, Data(0), ChanTag(0))
      
      ' Update the Pre- and Post- Trigger data displays
      For Offset = 0 To 9
         ' Determine the data index with respect to the trigger index
         PreTriggerIndex = VarPreCount - 10 + Offset
         PostTriggerIndex = VarPreCount + Offset
         
         ' Avoid indexing invalid pretrigger data
         If (10 - Offset < ActualPreCount) Then
           ULStat = cbToEngUnits(bd, Range, Data(PreTriggerIndex), Value)
           lblPretriggerData(Offset).Caption = Format(Value, "#0.0000 V")
         Else ' this index doesn't point to valid data
           lblPretriggerData(Offset).Caption = "NA"
         End If
         
         ULStat = cbToEngUnits(bd, Range, Data(PostTriggerIndex), Value)
         lblPosttriggerData(Offset).Caption = Format(Value, "#0.0000 V")
         
      Next Offset
      
      
      If (chkAutoRestart.Value) Then
         ' Start a new scan
         Rate = SAMPLERATE
         VarPreCount = PRECOUNT
         TotalCount = NumPoints
         ULStat = cbAPretrig(bd, CHANNEL, CHANNEL, VarPreCount, TotalCount, _
                                             Rate, Range, hDataBuffer, Options)
         lblStatus.ForeColor = &HFF0000
         lblStatus.Caption = "RUNNING"
         lblPreCount.Caption = "NA"
      End If
      
      ' Deassert external device signal
      ULStat = cbDOut(bd, FIRSTPORTA, 0)
      
   End If
   
End Sub

' A scan error occurred; if fatal(not TOOFEW), abort and reset the controls.
Public Sub OnScanError(bd As Integer, EventType As Long, ErrorNo As Long)
   Dim ULStat As Integer
     
   ' We don't need to update the display here since that will happen during
   ' the ON_END_OF_AI_SCAN  event to follow this event -- yes, this event is
   ' handled before any others, and if fatal, this event should be accompanied
   ' by an ON_END_OF_AI_SCAN event.
   If (ErrorNo <> TOOFEW) Then
      ULStat = cbStopBackground(bd, AIFUNCTION)
      
     ' Reset the chkAutoRestart such that the ON_END_OF_AI_SCAN event does
     ' not automatically start a new scan
     chkAutoRestart.Value = 0
     
     lblStatus.ForeColor = &HFF&
      lblStatus.Caption = "FATAL ERROR!"
   Else
      lblStatus.ForeColor = &HFF&
      lblStatus.Caption = "TOOFEW"
   End If

End Sub




Private Sub cmdDisableEvent_Click()
  Dim ULStat As Integer
  Dim EventTypes As Long
  
  ' we should stop any active scans before disabling events
  ULStat = cbStopBackground(BoardNum, AIFUNCTION)
  
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
  '   If we want to attach a single callback function to more than one event
  '   type, we can do it in a single call to cbEnableEvent, or we can do it in
  '   separate calls for each event type. A disadvantage of doing it in a
  '   single call is that if the call generates an error, we will not know which
  '   event type caused the error. In addition, the same error condition could
  '   generate multiple error messages.
  '
  ' Parameters:
  '    BoardNum                       : The board for which the EventType conditions
  '                                     will generate an event.
  '    EventType = ON_PRETRIGGER+_    : Generate an event upon first trigger during a cbAPretrig scan
  '                ON_END_OF_AI_SCAN  : Generate an event upon scan completion or end
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
  EventType = ON_PRETRIGGER + ON_END_OF_AI_SCAN
  ULStat = cbEnableEvent(BoardNum, EventType, 0, AddressOf MyCallback, frmEventDisplay)
  
  
  ' Since ON_SCAN_ERROR event doesn't use the EventSize, we can set it to anything
  ' we choose without affecting the ON_DATA_AVAILABLE setting.
  ULStat = cbEnableEvent(BoardNum, ON_SCAN_ERROR, 0, AddressOf OnErrorCallback, frmEventDisplay)
  If (ULStat <> NOERRORS) Then
    cmdEnableEvent.Enabled = True
  End If

  
End Sub



Private Sub cmdStart_Click()
  Dim ULStat As Integer
  
  'start the scan
  ActualPreCount = 0
  VarPreCount = PRECOUNT
  TotalCount = NumPoints
  Rate = SAMPLERATE
  ULStat = cbAPretrig(BoardNum, CHANNEL, CHANNEL, VarPreCount, TotalCount, _
                                          Rate, Range, hDataBuffer, Options)
  If (ULStat = NOERRORS) Then
   lblStatus.ForeColor = &HFF0000
    lblStatus.Caption = "RUNNING"
    lblPreCount.Caption = "NA"
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
  
  ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.

   '  Parameters:
   '     PRINTALL    :all warnings and errors encountered will be printed
   '     DONTSTOP    :if an error is encountered, the program will not stop,
   '                  errors must be handled locally
  ULStat = cbErrHandling(PRINTALL, DONTSTOP)
  
  ' Prepare FIRSTPORTA for signalling external device
  ULStat = cbDConfigPort(BoardNum, FIRSTPORTA, DIGITALOUT)
  
  ' initialize cbAInScan parameters
  hDataBuffer = cbWinBufAlloc(BUFFERSIZE)
  Rate = SAMPLERATE
  
End Sub



Private Sub Form_Unload(Cancel As Integer)
   Dim ULStat As Integer
   
   ' make sure to shut down
   ULStat = cbStopBackground(BoardNum, AIFUNCTION)
   
   ' and diable any active events
   ULStat = cbDisableEvent(BoardNum, ALL_EVENT_TYPES)
   
   If (hDataBuffer <> 0) Then cbWinBufFree (hDataBuffer)
   hDataBuffer = 0
   
End Sub
