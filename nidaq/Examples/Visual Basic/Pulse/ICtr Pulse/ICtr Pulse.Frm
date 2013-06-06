VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Generate Continuous Pulse"
   ClientHeight    =   2280
   ClientLeft      =   8475
   ClientTop       =   3045
   ClientWidth     =   4080
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2280
   ScaleWidth      =   4080
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   120
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
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop Square Wave"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1815
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start Square Wave"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1815
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   2040
      Top             =   1320
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit1 
      Height          =   255
      Left            =   2040
      TabIndex        =   0
      Top             =   960
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
      opts_1          =   458782
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
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
      RangeMin_Val_1  =   15
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   600000
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEditCtr 
      Height          =   255
      Left            =   2760
      TabIndex        =   6
      Top             =   420
      Width           =   615
      _Version        =   196609
      _ExtentX        =   1085
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
      opts_1          =   458814
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
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
      RangeMax_Val_1  =   2
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEditDevice 
      Height          =   255
      Left            =   2040
      TabIndex        =   7
      Top             =   420
      Width           =   615
      _Version        =   196609
      _ExtentX        =   1085
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
      opts_1          =   458814
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
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
      RangeMin_Val_1  =   1
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   16
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin VB.Label Label4 
      Caption         =   "Counter (0,1,2)"
      Height          =   255
      Left            =   2760
      TabIndex        =   9
      Top             =   120
      Width           =   1155
   End
   Begin VB.Label Label3 
      Caption         =   "Device"
      Height          =   255
      Left            =   2040
      TabIndex        =   8
      Top             =   120
      Width           =   555
   End
   Begin VB.Label Label2 
      Caption         =   "Set device, counter, and frequency and press start."
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1920
      Width           =   3735
   End
   Begin VB.Label Label1 
      Caption         =   "Frequency"
      Height          =   255
      Left            =   2040
      TabIndex        =   3
      Top             =   720
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' example of how to use the ICtr to generate a continuous pulse

' Use counter 0 with internal clock source or counter 1 or 2 and
' supply your own clock source
Dim gDevice As Long
Dim gCounter As Long

Const BASECLOCK = 2000000
' set BASECLOCK to 2000000 for internal source on 1200/LAB-PC class boards
' set BASECLOCK to 1000000 for internal source on 500/700/LPM-16 class boards
' set BASECLOCK to frequency of external clock if using counter 1 or 2

Private Sub Start_Click()
    Dim Divisor
    
    gDevice = CWNumEditDevice.Value
    gCounter = CWNumEditCtr.Value
    
    Divisor = BASECLOCK / CWNumEdit1
    
    If Divisor < 3 Or Divisor > 65536 Then
        MsgBox "Cannot generate this frequency."
    Else
        ' Start pulse generation
        ' Counter divides clock source signal by specified divisor value
        CWDAQTools1.StartICtr gDevice, gCounter, 3, Divisor
        ' CWDAQTools1.StartICtr Device:=1, Counter:=0, Mode:=3 (square wave generator), Count:=divisor
    End If
End Sub

Private Sub Stop_Click()
    ' Read number of events and stop counter
       
    CWDAQTools1.ResetICtr gDevice, gCounter, 0
    ' CWDAQTools1.ResetICtr Device:=1, Counter:=1, OutputState:=0
End Sub


