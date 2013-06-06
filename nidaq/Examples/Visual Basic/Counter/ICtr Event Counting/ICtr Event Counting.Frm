VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Count Events"
   ClientHeight    =   3195
   ClientLeft      =   1905
   ClientTop       =   1560
   ClientWidth     =   3570
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3195
   ScaleWidth      =   3570
   Begin VB.TextBox Text1 
      BackColor       =   &H8000000F&
      Height          =   1155
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   9
      Text            =   "ICtr Event Counting.frx":0000
      Top             =   1920
      Width           =   3315
   End
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
      Left            =   2160
      Top             =   1320
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start Counting"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1215
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEditDevice 
      Height          =   255
      Left            =   1560
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
   Begin CWUIControlsLib.CWNumEdit CWNumEditCtr 
      Height          =   255
      Left            =   2280
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
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   120
      TabIndex        =   4
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
      ContextID       =   15164
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   1560
      Top             =   1320
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit1 
      Height          =   255
      Left            =   1560
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
   Begin VB.Label Label3 
      Caption         =   "Device"
      Height          =   255
      Left            =   1560
      TabIndex        =   8
      Top             =   120
      Width           =   555
   End
   Begin VB.Label Label2 
      Caption         =   "Counter (0,1,2)"
      Height          =   255
      Left            =   2280
      TabIndex        =   5
      Top             =   120
      Width           =   1395
   End
   Begin VB.Label Label1 
      Caption         =   "Number of Events"
      Height          =   255
      Left            =   1560
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

'Connect signal to count to Source input of the counter being used
Dim gDevice As Long
Dim gCounter As Long

Private Sub Start_Click()
    gDevice = CWNumEditDevice.Value
    gCounter = CWNumEditCtr.Value
    
    ' Start counting events, connect signal to counter source specified
    ' Counter counts down from maximum, compensate when displaying value
    CWDAQTools1.StartICtr gDevice, gCounter, 0, 65535
    ' CWDAQTools1.StartICtr Device:=1, Counter:=1, Mode:=0, Count:=0
    
    Timer1.Enabled = True
End Sub

Private Sub Stop_Click()
    ' Read number of events and stop counter
    Timer1.Enabled = False
    Read_Now
    
    CWDAQTools1.ResetICtr gDevice, gCounter, 0
    ' CWDAQTools1.ResetICtr Device:=1, Counter:=1, OutputState:=0
End Sub

Private Sub Timer1_Timer()
    Read_Now
End Sub

Private Sub Read_Now()
    ' Read number of events counted so far
    Dim valCount As Long
    CWDAQTools1.ReadICtr gDevice, gCounter, valCount
    ' CWDAQTools1.ReadICtr Device:=1, Counter:=1, Count:=valCount
    
    ' Compensate for down counter
    If valCount = 0 Then
        CWNumEdit1 = 1
    Else
        CWNumEdit1 = 65536 - valCount
    End If
End Sub


