VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "TIO Edge Separation"
   ClientHeight    =   4155
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4530
   LinkTopic       =   "Form1"
   ScaleHeight     =   4155
   ScaleWidth      =   4530
   StartUpPosition =   3  'Windows Default
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   840
      Top             =   3480
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   3000
      TabIndex        =   6
      Top             =   3600
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
      ContextID       =   15221
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Enabled         =   0   'False
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   720
      Width           =   1215
   End
   Begin CWUIControlsLib.CWNumEdit counts 
      Height          =   255
      Left            =   2640
      TabIndex        =   3
      Top             =   1320
      Width           =   1455
      _Version        =   196609
      _ExtentX        =   2566
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
      opts_1          =   131134
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      Mode_1          =   1
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   ".#"
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
   Begin VB.CheckBox ckBuffered 
      Caption         =   "Buffered Measurement"
      Height          =   255
      Left            =   2160
      TabIndex        =   1
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   360
      Top             =   3480
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
      GateSignal_1    =   30
      Timebase_1      =   2e7
      InternalClockMode_1=   -12851
      MeasurementType_1=   11
      NMeasurements_1 =   200
      Buffering_1     =   -1  'True
      BufferSize_1    =   1000
      UseDefBuf_1     =   0   'False
   End
   Begin CWUIControlsLib.CWNumEdit time 
      Height          =   255
      Left            =   2640
      TabIndex        =   8
      Top             =   1680
      Width           =   1455
      _Version        =   196609
      _ExtentX        =   2566
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
      opts_1          =   131134
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      Mode_1          =   1
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   ".######"" s"""
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
   Begin VB.Label Label4 
      Caption         =   "Elapsed time between signals:"
      Height          =   255
      Left            =   360
      TabIndex        =   9
      Top             =   1695
      Width           =   2175
   End
   Begin VB.Label Label3 
      Caption         =   "For buffered measurements, the average is displayed."
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   2040
      Width           =   3855
   End
   Begin VB.Label Label2 
      Caption         =   $"TIO Edge Separation.frx":0000
      Height          =   975
      Left            =   360
      TabIndex        =   5
      Top             =   2475
      Width           =   3855
   End
   Begin VB.Label Label1 
      Caption         =   "Source edges between signals:"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   1335
      Width           =   2295
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdStart_Click()
CWCounter1.MeasurementType = cwctrTwoEdgeSeparation
CWCounter1.UseBuffering = ckBuffered
CWCounter1.Configure
CWCounter1.Start

cmdStop.Enabled = True
End Sub

Private Sub cmdStop_Click()
CWCounter1.Stop
cmdStop.Enabled = False
End Sub

Private Sub CWCounter1_AcquiredData(Measurement As Variant, ByVal Overflow As Boolean)
Dim num As Long
Dim total As Single

total = 0
If IsArray(Measurement) Then
    num = UBound(Measurement)
    For i = 0 To num
        total = total + Measurement(i)
    Next
    counts = total / (num + 1)
Else
    counts = Measurement
End If
'to determine the time between signals, divide the measurement by the source frequency
Time = counts.Value / CWCounter1.TimebaseSignal

'signal that measurement is complete
Beep

If Not (CWCounter1.BufferMode = cwctrContinuous) Then
    cmdStop.Enabled = False
End If

End Sub

Private Sub CWCounter1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

Private Sub CWCounter1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Warning: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub
