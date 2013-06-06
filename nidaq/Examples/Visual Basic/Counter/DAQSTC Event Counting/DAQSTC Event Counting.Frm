VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1665
   ClientLeft      =   3825
   ClientTop       =   3735
   ClientWidth     =   4380
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1665
   ScaleWidth      =   4380
   Begin VB.CommandButton Stop 
      Caption         =   "Stop Counting"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   2400
      Top             =   720
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start Counting"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1215
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   3000
      TabIndex        =   4
      Top             =   720
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
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
      ContextID       =   15122
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit1 
      Height          =   255
      Left            =   1560
      TabIndex        =   0
      Top             =   360
      Width           =   1335
      _Version        =   196609
      _ExtentX        =   2355
      _ExtentY        =   450
      _StockProps     =   4
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   131102
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      Mode_1          =   1
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   100
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   1560
      Top             =   720
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
      Counter_1       =   0
      GateMode_1      =   1
      GateSource_1    =   1
      TBSource_1      =   0
      InternalClockMode_1=   -31648
   End
   Begin VB.Label Label2 
      Caption         =   "DAQ device and counter set in property pages."
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1320
      Visible         =   0   'False
      Width           =   4095
   End
   Begin VB.Label Label1 
      Caption         =   "Number of Events"
      Height          =   255
      Left            =   1560
      TabIndex        =   3
      Top             =   120
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Connect your signal to count to the source of the counter
' being used.

Private Sub Start_Click()
    ' Start counting events
    CWCounter1.Configure
    CWCounter1.Start
    Timer1.Enabled = True
End Sub

Private Sub Stop_Click()
    ' Read number of events and stop counter
    Dim valCount As Variant
    Dim overflow As Boolean
    Timer1.Enabled = False
    CWCounter1.ReadMeasurement valCount, overflow
    CWNumEdit1 = valCount
    CWCounter1.Stop
End Sub

Private Sub Timer1_Timer()
    ' Read number of events counted so far
    Dim valCount As Variant
    Dim overflow As Boolean
    CWCounter1.ReadMeasurement valCount, overflow
    CWNumEdit1 = valCount
End Sub


