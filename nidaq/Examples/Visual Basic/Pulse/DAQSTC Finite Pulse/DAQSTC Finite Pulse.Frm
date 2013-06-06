VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Generate Finite Pulse"
   ClientHeight    =   2205
   ClientLeft      =   2220
   ClientTop       =   2445
   ClientWidth     =   4155
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2205
   ScaleWidth      =   4155
   Begin VB.CommandButton Stop 
      Caption         =   "Stop Pulses"
      Height          =   495
      Left            =   120
      TabIndex        =   5
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start Pulses"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   2760
      TabIndex        =   8
      Top             =   1320
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
      ContextID       =   15123
   End
   Begin CWUIControlsLib.CWNumEdit cwnumPulseCount 
      Height          =   255
      Left            =   1440
      TabIndex        =   7
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
      Format_2        =   "."
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   100
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   20000
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit cwnumFreq 
      Height          =   255
      Left            =   1440
      TabIndex        =   3
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
      Format_2        =   " k""Hz"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   100
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   20000
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit cwnumDutyCycle 
      Height          =   255
      Left            =   1440
      TabIndex        =   1
      Top             =   1560
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
      Format_2        =   ".##"
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   0.5
      IncValueVarType_1=   5
      IncValue_Val_1  =   0.1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMin_Val_1  =   0.01
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   0.99
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   2880
      Top             =   120
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
      PulseType_1     =   2
      Count_1         =   10
      Frequency_1     =   100
      Delay_1         =   0
      Width_1         =   1
   End
   Begin VB.Label Label4 
      Caption         =   "DAQ device and counter set in property pages."
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   1920
      Visible         =   0   'False
      Width           =   3855
   End
   Begin VB.Label Label3 
      Caption         =   "Number of Pulses"
      Height          =   255
      Left            =   1440
      TabIndex        =   6
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Frequency"
      Height          =   255
      Left            =   1440
      TabIndex        =   4
      Top             =   720
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Duty Cycle (0-1)"
      Height          =   255
      Left            =   1440
      TabIndex        =   2
      Top             =   1320
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Start_Click()
    ' Generate finite pulse train with number of pulses,
    ' frequency and duty cycle specified on the front panel
    ' This operation requires both counters on the DAQ board
    CWPulse1.Count = cwnumPulseCount
    CWPulse1.Frequency = cwnumFreq
    CWPulse1.DutyCycle = cwnumDutyCycle
    CWPulse1.Configure
    CWPulse1.Start
End Sub

Private Sub Stop_Click()
    CWPulse1.Stop
End Sub
