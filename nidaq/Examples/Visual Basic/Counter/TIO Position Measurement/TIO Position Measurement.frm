VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "TIO Position Measurement"
   ClientHeight    =   2700
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4530
   LinkTopic       =   "Form1"
   ScaleHeight     =   2700
   ScaleWidth      =   4530
   StartUpPosition =   3  'Windows Default
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   5
      Top             =   1200
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
      ContextID       =   15222
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   3960
      Top             =   720
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   2520
      TabIndex        =   1
      Text            =   "0"
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   3960
      Top             =   240
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
      GateSource_1    =   5
      GateSignal_1    =   38
      TBSource_1      =   0
      InternalClockMode_1=   -12851
      MeasurementType_1=   10
      BufferSize_1    =   100
      BufferMode_1    =   1
      UseDefBuf_1     =   0   'False
      ZIndex_1        =   0   'False
   End
   Begin VB.Label Label2 
      Caption         =   $"TIO Position Measurement.frx":0000
      Height          =   855
      Left            =   120
      TabIndex        =   4
      Top             =   1800
      Width           =   4215
   End
   Begin VB.Label Label1 
      Caption         =   "Measured Position:"
      Height          =   255
      Left            =   2520
      TabIndex        =   3
      Top             =   480
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdStart_Click()

CWCounter1.Configure
CWCounter1.Start

Timer1.Enabled = True

End Sub

Private Sub cmdStop_Click()
Timer1.Enabled = False
End Sub


Private Sub Timer1_Timer()
Dim position
Dim overflow As Boolean

'Read the current position
CWCounter1.ReadMeasurement position, overflow
Text1.Text = position
End Sub
