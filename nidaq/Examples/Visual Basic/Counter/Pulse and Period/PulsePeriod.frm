VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Pulse and Period Measurements"
   ClientHeight    =   4035
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5535
   LinkTopic       =   "Form1"
   ScaleHeight     =   4035
   ScaleWidth      =   5535
   StartUpPosition =   3  'Windows Default
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   16
      Top             =   2880
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   6
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      HelpFile        =   "cwdaq.hlp"
      ContextID       =   15223
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   4800
      Top             =   2520
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin VB.Frame Frame2 
      Caption         =   "Buffer Settings"
      Height          =   1695
      Left            =   2760
      TabIndex        =   9
      Top             =   120
      Width           =   2535
      Begin VB.TextBox numMeasurements 
         Height          =   285
         Left            =   1680
         TabIndex        =   15
         Text            =   "20"
         Top             =   1320
         Width           =   615
      End
      Begin VB.OptionButton Buffer 
         Caption         =   "Continuous Buffer"
         Height          =   195
         Index           =   2
         Left            =   120
         TabIndex        =   12
         Top             =   1005
         Width           =   2175
      End
      Begin VB.OptionButton Buffer 
         Caption         =   "Single Buffer"
         Height          =   195
         Index           =   1
         Left            =   120
         TabIndex        =   11
         Top             =   675
         Width           =   2175
      End
      Begin VB.OptionButton Buffer 
         Caption         =   "Single Measurement"
         Height          =   195
         Index           =   0
         Left            =   120
         TabIndex        =   10
         Top             =   360
         Width           =   2175
      End
      Begin VB.Label Label2 
         Caption         =   "# Measurements:"
         Height          =   255
         Left            =   360
         TabIndex        =   13
         Top             =   1320
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Measurement"
      Height          =   1695
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   2535
      Begin VB.OptionButton Measurement 
         Caption         =   "Period, Falling Edge"
         Height          =   195
         Index           =   3
         Left            =   120
         TabIndex        =   8
         Top             =   1320
         Width           =   2175
      End
      Begin VB.OptionButton Measurement 
         Caption         =   "Period, Rising Edge"
         Height          =   195
         Index           =   2
         Left            =   120
         TabIndex        =   7
         Top             =   1005
         Width           =   2175
      End
      Begin VB.OptionButton Measurement 
         Caption         =   "Pulse Width, High"
         Height          =   195
         Index           =   0
         Left            =   120
         TabIndex        =   6
         Top             =   360
         Width           =   2175
      End
      Begin VB.OptionButton Measurement 
         Caption         =   "Pulse Width, Low"
         Height          =   195
         Index           =   1
         Left            =   120
         TabIndex        =   5
         Top             =   675
         Width           =   2175
      End
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   2400
      Width           =   1215
   End
   Begin VB.TextBox txtMeasurement 
      Height          =   285
      Left            =   2760
      TabIndex        =   1
      Top             =   2280
      Width           =   1335
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   1920
      Width           =   1215
   End
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   4800
      Top             =   2040
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWCounter_0     =   1
      ClassName_1     =   "CCWCounter"
      opts_1          =   18
      ErrorEventMask_1=   871426
      GateMode_1      =   1
      GateSource_1    =   1
      GateSignal_1    =   38
      Timebase_1      =   1.00000e5
      ALSource_1      =   1
      InternalClockMode_1=   -12851
      MeasurementType_1=   3
      NMeasurements_1 =   30
      BufferSize_1    =   5000
      BufferMode_1    =   1
      UseDefBuf_1     =   0   'False
   End
   Begin VB.Label Label4 
      Caption         =   $"PulsePeriod.frx":0000
      Height          =   615
      Left            =   120
      TabIndex        =   14
      Top             =   3360
      Width           =   5415
   End
   Begin VB.Label Label1 
      Caption         =   "Measurement:"
      Height          =   255
      Left            =   2760
      TabIndex        =   3
      Top             =   2040
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Load()
'Initial Values - Single Hi Pulse Width Measurement
Measurement(0).Value = True
Buffer(0).Value = True
End Sub

Private Sub Measurement_Click(Index As Integer)
Select Case Index
Case 0
    CWCounter1.MeasurementType = cwctrHiPulseWidth
Case 1
    CWCounter1.MeasurementType = cwctrLoPulseWidth
Case 2
    CWCounter1.MeasurementType = cwctrPulsePeriodRisingEdge
Case 3
    CWCounter1.MeasurementType = cwctrPulsePeriodFallingEdge
End Select

End Sub
Private Sub Buffer_Click(Index As Integer)
Select Case Index
Case 0
    'Single measurement
    CWCounter1.UseBuffering = False
Case 1 To 2
    'Buffered measurements
    CWCounter1.UseBuffering = True
    If Index = 1 Then
        CWCounter1.BufferMode = cwctrFinite
    Else
        CWCounter1.BufferMode = cwctrContinuous
    End If
End Select
End Sub

Private Sub Start_Click()
'if buffered measurement is selected, numMeasurements will be taken
CWCounter1.NMeasurements = numMeasurements
CWCounter1.Configure
CWCounter1.Start

End Sub

Private Sub Stop_Click()
CWCounter1.Stop
End Sub

Private Sub CWCounter1_AcquiredData(Measurement As Variant, ByVal Overflow As Boolean)
If IsArray(Measurement) Then
    'Buffered measurements return an array.  Display just one element.
    txtMeasurement.Text = Measurement(1)
Else
    'Display the measured value
    txtMeasurement.Text = Measurement
End If
Beep
End Sub

Private Sub CWCounter1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

