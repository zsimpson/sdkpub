VERSION 5.00
Object = "{E7BC3920-33D4-11D0-8B73-0020AF31CEF9}#1.4#0"; "CWANALYSIS.OCX"
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Error Handling"
   ClientHeight    =   1920
   ClientLeft      =   1620
   ClientTop       =   3960
   ClientWidth     =   5430
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1920
   ScaleWidth      =   5430
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   3480
      TabIndex        =   5
      Top             =   1320
      Width           =   1815
      _Version        =   65536
      _ExtentX        =   3201
      _ExtentY        =   873
      _StockProps     =   6
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      HelpFile        =   "cwdaq.hlp"
      ContextID       =   15090
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Return Value Error handled in Subroutine"
      Height          =   495
      Left            =   3480
      TabIndex        =   4
      Top             =   720
      Width           =   1815
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Return Value Error handled in Process"
      Height          =   495
      Left            =   3480
      TabIndex        =   3
      Top             =   120
      Width           =   1815
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Exception handled with On Error GoTo ..."
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   1320
      Width           =   1815
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Exception handled with On Error Resume Next"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   1815
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Unhandled Exception from Analysis"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1815
   End
   Begin CWAnalysisControlsLib.CWDSP CWDSP1 
      Left            =   2160
      Top             =   120
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   2880
      Top             =   720
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWDAQControlsLib.CWAI CWAI2 
      Left            =   2880
      Top             =   120
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   100
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      Frequency_2     =   100
      Period_2        =   0.01
      ClockSourceType_2=   1
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      Frequency_3     =   100
      Period_3        =   0.01
      InternalClockMode_3=   1
      Buffer_1        =   4
      ClassName_4     =   "CCWAIBuffer"
      Channels_1      =   5
      ClassName_5     =   "CCWAIChannelArray"
      Editor_5        =   6
      ClassName_6     =   "CCWAIChannelsArrayEditor"
      Owner_6         =   1
      StartCond_1     =   7
      ClassName_7     =   "CCWAICondition"
      WhichCondition_7=   1
      PauseCond_1     =   8
      ClassName_8     =   "CCWAICondition"
      WhichCondition_8=   2
      TrigPauseMode_8 =   7
      StopCond_1      =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   3
      HoldoffClock_1  =   10
      ClassName_10    =   "CCWAIClock"
      Frequency_10    =   100
      Period_10       =   0.01
      InternalClockMode_10=   1
   End
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   2160
      Top             =   960
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      opts_1          =   2
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   100
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      Frequency_2     =   100
      Period_2        =   0.01
      ClockSourceType_2=   1
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      Frequency_3     =   100
      Period_3        =   0.01
      InternalClockMode_3=   1
      Buffer_1        =   4
      ClassName_4     =   "CCWAIBuffer"
      Channels_1      =   5
      ClassName_5     =   "CCWAIChannelArray"
      Editor_5        =   6
      ClassName_6     =   "CCWAIChannelsArrayEditor"
      Owner_6         =   1
      StartCond_1     =   7
      ClassName_7     =   "CCWAICondition"
      WhichCondition_7=   1
      PauseCond_1     =   8
      ClassName_8     =   "CCWAICondition"
      WhichCondition_8=   2
      TrigPauseMode_8 =   7
      StopCond_1      =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   3
      HoldoffClock_1  =   10
      ClassName_10    =   "CCWAIClock"
      Frequency_10    =   100
      Period_10       =   0.01
      InternalClockMode_10=   1
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
'default exception handler
    Dim data(1000) As Double
    Dim spectrumData As Variant
    spectrumData = CWDSP1.Spectrum(data)
End Sub

Private Sub Command2_Click()
'Do exception handling explicitly in code
On Error Resume Next
    CWAI1.Configure
    If Err.Number <> 0 Then MsgBox "Configure: " + CStr(Err.Number)
    CWAI1.Start
    If Err.Number <> 0 Then MsgBox "Start: " + CStr(Err.Number)
End Sub

Private Sub Command3_Click()
'Pass exception handling to common code
On Error GoTo ErrorHandler
    CWAI1.Configure
    CWAI1.Start
    Exit Sub
ErrorHandler:
    MsgBox "DAQ Error: " + CStr(Err.Number)
    Resume Next
End Sub

Private Sub Command4_Click()
'Check return value in code
    Dim lerr As Long
    lerr = CWAI2.Configure
    If lerr <> 0 Then
        MsgBox "DAQ Error: " + CStr(lerr)
        Exit Sub
    End If
    lerr = CWAI2.Start
    If lerr <> 0 Then
        MsgBox "DAQ Error: " + CStr(lerr)
        Exit Sub
    End If
End Sub

Private Sub Command5_Click()
'Check return value in subroutine
    LogError CWAI2.Configure
    LogError CWAI2.Start
End Sub
Private Sub LogError(Error As Long)
    If Error <> 0 Then MsgBox "DAQ Error: " + CStr(Error) + Chr$(13) + CWDAQTools1.GetErrorText(Error)
End Sub

