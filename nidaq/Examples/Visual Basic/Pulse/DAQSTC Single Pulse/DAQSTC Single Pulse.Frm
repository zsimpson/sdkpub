VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Generate Single Pulse"
   ClientHeight    =   1680
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   4140
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1680
   ScaleWidth      =   4140
   Begin VB.CommandButton Generate 
      Caption         =   "Generate Pulse"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   2760
      TabIndex        =   5
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
      ContextID       =   15128
   End
   Begin CWUIControlsLib.CWNumEdit cwnumDelay 
      Height          =   255
      Left            =   1440
      TabIndex        =   3
      Top             =   360
      Width           =   1215
      _Version        =   196609
      _ExtentX        =   2143
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
      opts_1          =   458782
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   ".000 ""s"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   0.5
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   10
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit cwnumWidth 
      Height          =   255
      Left            =   1440
      TabIndex        =   1
      Top             =   960
      Width           =   1215
      _Version        =   196609
      _ExtentX        =   2143
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
      opts_1          =   458782
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   ".000 ""s"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   1
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   10
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   120
      Top             =   720
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWPulse_0       =   1
      ClassName_1     =   "CCWPulse"
      opts_1          =   18
      ErrorEventMask_1=   871426
      Counter_1       =   0
      GateMode_1      =   1
      GateSource_1    =   1
      PulseType_1     =   0
      InternalClockMode_1=   3
      Delay_1         =   0
      Width_1         =   1
   End
   Begin VB.Label Label3 
      Caption         =   "DAQ device and counter set in property pages."
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   1320
      Visible         =   0   'False
      Width           =   3855
   End
   Begin VB.Label Label2 
      Caption         =   "Pulse Delay"
      Height          =   255
      Left            =   1440
      TabIndex        =   4
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Pulse Width"
      Height          =   255
      Left            =   1440
      TabIndex        =   2
      Top             =   720
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Generate_Click()
    ' Generate a single pulse of delay and width
    ' specified on the front panel
    CWPulse1.PulseDelay = cwnumDelay
    CWPulse1.PulseWidth = cwnumWidth
    CWPulse1.Configure
    CWPulse1.Start
End Sub
