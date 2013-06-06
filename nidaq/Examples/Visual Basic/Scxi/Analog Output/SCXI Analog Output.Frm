VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3525
   ClientLeft      =   2520
   ClientTop       =   1785
   ClientWidth     =   4170
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3525
   ScaleWidth      =   4170
   Begin VB.Frame Frame2 
      Caption         =   "Analog Output"
      Height          =   2655
      Left            =   2220
      TabIndex        =   1
      Top             =   240
      Width           =   1695
      Begin VB.TextBox AOError 
         BackColor       =   &H00C0C0C0&
         Height          =   285
         Left            =   240
         TabIndex        =   13
         Top             =   2280
         Width           =   1215
      End
      Begin VB.CommandButton AOUpdate 
         Caption         =   "Update"
         Height          =   375
         Left            =   240
         TabIndex        =   12
         Top             =   1560
         Width           =   1215
      End
      Begin VB.TextBox AOVoltage 
         Height          =   285
         Left            =   240
         TabIndex        =   10
         Text            =   "0"
         Top             =   1200
         Width           =   1215
      End
      Begin VB.TextBox AOChannel 
         Height          =   285
         Left            =   240
         TabIndex        =   8
         Text            =   "sc1!md2!0"
         Top             =   600
         Width           =   1215
      End
      Begin VB.Label Label6 
         Caption         =   "Error"
         Height          =   255
         Left            =   240
         TabIndex        =   14
         Top             =   2040
         Width           =   975
      End
      Begin VB.Label Label5 
         Caption         =   "Voltage"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   960
         Width           =   975
      End
      Begin VB.Label Label4 
         Caption         =   "Channel"
         Height          =   255
         Left            =   240
         TabIndex        =   9
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Analog Input"
      Height          =   2655
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1695
      Begin VB.TextBox AIChannel 
         Height          =   285
         Left            =   240
         TabIndex        =   15
         Text            =   "sc1!md1!0"
         Top             =   600
         Width           =   1215
      End
      Begin VB.TextBox AIError 
         BackColor       =   &H00C0C0C0&
         Height          =   285
         Left            =   240
         TabIndex        =   4
         Top             =   2280
         Width           =   1215
      End
      Begin VB.TextBox AIVoltage 
         BackColor       =   &H00C0C0C0&
         ForeColor       =   &H00000000&
         Height          =   285
         Left            =   240
         TabIndex        =   3
         Top             =   1680
         Width           =   1215
      End
      Begin VB.CommandButton AIUpdate 
         Caption         =   "Acquire"
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   960
         Width           =   1215
      End
      Begin VB.Label Label3 
         Caption         =   "Reading"
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   1440
         Width           =   735
      End
      Begin VB.Label Label2 
         Caption         =   "Error"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   2040
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "Channel"
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   360
         Width           =   855
      End
   End
   Begin CWDAQControlsLib.CWAIPoint CWAIPoint1 
      Left            =   240
      Top             =   3000
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AIPoint_0       =   1
      ClassName_1     =   "CCWAIPoint"
      opts_1          =   2
      Device_1        =   1
      TotalScansToAcquire_1=   100
      ScanClock_1     =   0
      ChannelClock_1  =   2
      ClassName_2     =   "CCWAIClock"
      ClockType_2     =   2
      Frequency_2     =   100
      Period_2        =   0.01
      InternalClockMode_2=   1
      Buffer_1        =   0
      Channels_1      =   3
      ClassName_3     =   "CCWAIChannelArray"
      Editor_3        =   4
      ClassName_4     =   "CCWAIChannelsArrayEditor"
      Owner_4         =   1
      StartCond_1     =   0
      PauseCond_1     =   0
      StopCond_1      =   0
      HoldoffClock_1  =   0
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   2880
      TabIndex        =   16
      Top             =   3000
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
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
      ContextID       =   15061
   End
   Begin CWDAQControlsLib.CWAOPoint CWAOPoint1 
      Left            =   2220
      Top             =   2940
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AOPointTask_0   =   1
      ClassName_1     =   "CCWAOPointTask"
      opts_1          =   2
      ChannelString_1 =   "sc1!md2!0"
      ChannelType_1   =   1
      ReferenceSource_1=   1
      UpperLimit_1    =   10
      LowerLimit_1    =   -10
   End
   Begin VB.Label Label7 
      Caption         =   "Device value set in property pages."
      Height          =   495
      Left            =   840
      TabIndex        =   17
      Top             =   3000
      Visible         =   0   'False
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim lErr As Long

Private Sub AIUpdate_Click()
    Dim data
    CWAIPoint1.Channels.RemoveAll
    CWAIPoint1.Channels.Add AIChannel
    lErr = CWAIPoint1.SingleRead(data, 1)
    AIError.Text = lErr
    AIVoltage.Text = Format(data, "0.0000")
End Sub

Private Sub AOUpdate_Click()
    ' *** Analog Output Subroutine ***
    ' Pass your desired analog output voltage to the
    ' SingleWrite method after setting the proper AO
    ' channel in the property page or programatically
    CWAOPoint1.ChannelString = AOChannel
    lErr = CWAOPoint1.SingleWrite(AOVoltage, True)
    AOError.Text = lErr
End Sub

Private Sub Form_Terminate()
    lErr = CWAOPoint1.SingleWrite(0, True)
    End
End Sub
