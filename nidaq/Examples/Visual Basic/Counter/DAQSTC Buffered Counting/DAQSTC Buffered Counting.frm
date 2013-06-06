VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Buffered Event Counting"
   ClientHeight    =   7575
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5310
   LinkTopic       =   "Form1"
   ScaleHeight     =   7575
   ScaleWidth      =   5310
   StartUpPosition =   3  'Windows Default
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   3840
      TabIndex        =   15
      Top             =   6720
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
      ContextID       =   15120
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   720
      Top             =   7080
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWButton Continuous 
      Height          =   375
      Left            =   2040
      TabIndex        =   5
      Top             =   1080
      Width           =   1215
      _Version        =   196609
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      Boolean_0       =   1
      ClassName_1     =   "CCWBoolean"
      opts_1          =   2622
      C[0]_1          =   -2147483643
      Enum_1          =   2
      ClassName_2     =   "CCWEnum"
      Array_2         =   2
      Editor_2        =   0
      Array[0]_2      =   3
      ClassName_3     =   "CCWEnumElt"
      opts_3          =   1
      Name_3          =   "Off"
      frame_3         =   286
      DrawList_3      =   4
      ClassName_4     =   "CDrawList"
      count_4         =   4
      list[4]_4       =   5
      ClassName_5     =   "CCWDrawObj"
      opts_5          =   62
      C[0]_5          =   -2147483640
      C[1]_5          =   -2147483640
      Image_5         =   6
      ClassName_6     =   "CCWTextImage"
      style_6         =   604391443
      font_6          =   0
      Animator_5      =   0
      Blinker_5       =   0
      list[3]_4       =   7
      ClassName_7     =   "CCWDrawObj"
      opts_7          =   60
      C[0]_7          =   -2147483640
      C[1]_7          =   -2147483640
      Image_7         =   8
      ClassName_8     =   "CCWTextImage"
      font_8          =   0
      Animator_7      =   0
      Blinker_7       =   0
      list[2]_4       =   9
      ClassName_9     =   "CCWDrawObj"
      opts_9          =   60
      C[0]_9          =   -2147483640
      C[1]_9          =   -2147483640
      Image_9         =   10
      ClassName_10    =   "CCWTextImage"
      style_10        =   7
      font_10         =   0
      Animator_9      =   0
      Blinker_9       =   0
      list[1]_4       =   11
      ClassName_11    =   "CCWDrawObj"
      opts_11         =   62
      Image_11        =   12
      ClassName_12    =   "CCWPictImage"
      opts_12         =   1280
      Rows_12         =   1
      Cols_12         =   1
      Pict_12         =   61
      F_12            =   -2147483633
      B_12            =   -2147483633
      ColorReplaceWith_12=   8421504
      ColorReplace_12 =   8421504
      Tolerance_12    =   2
      Animator_11     =   0
      Blinker_11      =   0
      varVarType_3    =   5
      Array[1]_2      =   13
      ClassName_13    =   "CCWEnumElt"
      opts_13         =   1
      Name_13         =   "On"
      frame_13        =   286
      DrawList_13     =   14
      ClassName_14    =   "CDrawList"
      count_14        =   4
      list[4]_14      =   15
      ClassName_15    =   "CCWDrawObj"
      opts_15         =   62
      C[0]_15         =   -2147483640
      C[1]_15         =   -2147483640
      Image_15        =   6
      Animator_15     =   0
      Blinker_15      =   0
      list[3]_14      =   16
      ClassName_16    =   "CCWDrawObj"
      opts_16         =   60
      C[0]_16         =   -2147483640
      C[1]_16         =   -2147483640
      Image_16        =   8
      Animator_16     =   0
      Blinker_16      =   0
      list[2]_14      =   17
      ClassName_17    =   "CCWDrawObj"
      opts_17         =   60
      C[0]_17         =   -2147483640
      C[1]_17         =   -2147483640
      Image_17        =   10
      Animator_17     =   0
      Blinker_17      =   0
      list[1]_14      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   62
      Image_18        =   19
      ClassName_19    =   "CCWPictImage"
      opts_19         =   1280
      Rows_19         =   1
      Cols_19         =   1
      Pict_19         =   62
      F_19            =   -2147483633
      B_19            =   -2147483633
      ColorReplaceWith_19=   8421504
      ColorReplace_19 =   8421504
      Tolerance_19    =   2
      Animator_18     =   0
      Blinker_18      =   0
      varVarType_13   =   5
      Bindings_1      =   20
      ClassName_20    =   "CCWBindingHolderArray"
      Editor_20       =   21
      ClassName_21    =   "CCWBindingHolderArrayEditor"
      Owner_21        =   1
      Style_1         =   9
      mechAction_1    =   1
      BGImg_1         =   22
      ClassName_22    =   "CCWDrawObj"
      opts_22         =   62
      Image_22        =   23
      ClassName_23    =   "CCWPictImage"
      opts_23         =   1280
      Rows_23         =   1
      Cols_23         =   1
      Pict_23         =   286
      F_23            =   -2147483633
      B_23            =   -2147483633
      ColorReplaceWith_23=   8421504
      ColorReplace_23 =   8421504
      Tolerance_23    =   2
      Animator_22     =   0
      Blinker_22      =   0
      Array_1         =   6
      Editor_1        =   0
      Array[0]_1      =   11
      Array[1]_1      =   18
      Array[2]_1      =   0
      Array[3]_1      =   0
      Array[4]_1      =   24
      ClassName_24    =   "CCWDrawObj"
      opts_24         =   62
      Image_24        =   8
      Animator_24     =   0
      Blinker_24      =   0
      Array[5]_1      =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   62
      Image_25        =   10
      Animator_25     =   0
      Blinker_25      =   0
      Label_1         =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   62
      C[0]_26         =   -2147483640
      Image_26        =   6
      Animator_26     =   0
      Blinker_26      =   0
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   4455
      Left            =   240
      TabIndex        =   4
      Top             =   1575
      Width           =   4815
      _Version        =   196609
      _ExtentX        =   8493
      _ExtentY        =   7858
      _StockProps     =   71
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      Graph_0         =   1
      ClassName_1     =   "CCWGraphFrame"
      opts_1          =   62
      C[0]_1          =   0
      Event_1         =   2
      ClassName_2     =   "CCWGFPlotEvent"
      Owner_2         =   1
      Plots_1         =   3
      ClassName_3     =   "CCWDataPlots"
      Array_3         =   1
      Editor_3        =   4
      ClassName_4     =   "CCWGFPlotArrayEditor"
      Owner_4         =   1
      Array[0]_3      =   5
      ClassName_5     =   "CCWDataPlot"
      opts_5          =   7340095
      Name_5          =   "Plot-1"
      C[0]_5          =   16776960
      C[1]_5          =   255
      C[2]_5          =   16711680
      C[3]_5          =   16776960
      Event_5         =   2
      X_5             =   6
      ClassName_6     =   "CCWAxis"
      opts_6          =   1599
      Name_6          =   "XAxis"
      Orientation_6   =   2944
      format_6        =   7
      ClassName_7     =   "CCWFormat"
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   38
      rMax_8          =   310
      dMax_8          =   10
      discInterval_8  =   1
      Radial_6        =   0
      Enum_6          =   9
      ClassName_9     =   "CCWEnum"
      Editor_9        =   10
      ClassName_10    =   "CCWEnumArrayEditor"
      Owner_10        =   6
      Font_6          =   0
      tickopts_6      =   2711
      major_6         =   2
      minor_6         =   1
      Caption_6       =   11
      ClassName_11    =   "CCWDrawObj"
      opts_11         =   62
      C[0]_11         =   -2147483640
      Image_11        =   12
      ClassName_12    =   "CCWTextImage"
      font_12         =   0
      Animator_11     =   0
      Blinker_11      =   0
      Y_5             =   13
      ClassName_13    =   "CCWAxis"
      opts_13         =   1599
      Name_13         =   "YAxis-1"
      Orientation_13  =   2067
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   24
      rMax_15         =   270
      dMax_15         =   10
      discInterval_15 =   1
      Radial_13       =   0
      Enum_13         =   16
      ClassName_16    =   "CCWEnum"
      Editor_16       =   17
      ClassName_17    =   "CCWEnumArrayEditor"
      Owner_17        =   13
      Font_13         =   0
      tickopts_13     =   2711
      major_13        =   1
      minor_13        =   0.5
      Caption_13      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   62
      C[0]_18         =   -2147483640
      Image_18        =   19
      ClassName_19    =   "CCWTextImage"
      szText_19       =   "Cumulative Events"
      font_19         =   0
      Animator_18     =   0
      Blinker_18      =   0
      LineStyle_5     =   2
      LineWidth_5     =   1
      BasePlot_5      =   0
      DefaultXInc_5   =   1
      DefaultPlotPerRow_5=   -1  'True
      Axes_1          =   20
      ClassName_20    =   "CCWAxes"
      Array_20        =   2
      Editor_20       =   21
      ClassName_21    =   "CCWGFAxisArrayEditor"
      Owner_21        =   1
      Array[0]_20     =   6
      Array[1]_20     =   13
      DefaultPlot_1   =   22
      ClassName_22    =   "CCWDataPlot"
      opts_22         =   7340095
      Name_22         =   "[Template]"
      C[0]_22         =   16776960
      C[1]_22         =   255
      C[2]_22         =   16711680
      C[3]_22         =   16776960
      Event_22        =   2
      X_22            =   6
      Y_22            =   13
      LineStyle_22    =   2
      LineWidth_22    =   1
      BasePlot_22     =   0
      DefaultXInc_22  =   1
      DefaultPlotPerRow_22=   -1  'True
      Cursors_1       =   23
      ClassName_23    =   "CCWCursors"
      Editor_23       =   24
      ClassName_24    =   "CCWGFCursorArrayEditor"
      Owner_24        =   1
      TrackMode_1     =   2
      GraphBackground_1=   0
      GraphFrame_1    =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   62
      Image_25        =   26
      ClassName_26    =   "CCWPictImage"
      opts_26         =   1280
      Rows_26         =   1
      Cols_26         =   1
      F_26            =   -2147483633
      B_26            =   -2147483633
      ColorReplaceWith_26=   8421504
      ColorReplace_26 =   8421504
      Tolerance_26    =   2
      Animator_25     =   0
      Blinker_25      =   0
      PlotFrame_1     =   27
      ClassName_27    =   "CCWDrawObj"
      opts_27         =   62
      C[1]_27         =   0
      Image_27        =   28
      ClassName_28    =   "CCWPictImage"
      opts_28         =   1280
      Rows_28         =   1
      Cols_28         =   1
      Pict_28         =   1
      F_28            =   -2147483633
      B_28            =   0
      ColorReplaceWith_28=   8421504
      ColorReplace_28 =   8421504
      Tolerance_28    =   2
      Animator_27     =   0
      Blinker_27      =   0
      Caption_1       =   29
      ClassName_29    =   "CCWDrawObj"
      opts_29         =   62
      C[0]_29         =   -2147483640
      Image_29        =   30
      ClassName_30    =   "CCWTextImage"
      szText_30       =   "Count Buffer"
      font_30         =   0
      Animator_29     =   0
      Blinker_29      =   0
      DefaultXInc_1   =   1
      DefaultPlotPerRow_1=   -1  'True
      Bindings_1      =   31
      ClassName_31    =   "CCWBindingHolderArray"
      Editor_31       =   32
      ClassName_32    =   "CCWBindingHolderArrayEditor"
      Owner_32        =   1
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   3840
      TabIndex        =   3
      Top             =   1080
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   3480
      TabIndex        =   1
      Text            =   "0"
      Top             =   6120
      Width           =   1575
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Start"
      Height          =   375
      Left            =   3840
      TabIndex        =   0
      Top             =   360
      Width           =   1215
   End
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   240
      Top             =   7080
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
      GateSource_1    =   1
      Timebase_1      =   1.00000e5
      InternalClockMode_1=   -12851
      NMeasurements_1 =   20
      Buffering_1     =   -1  'True
      BufferMode_1    =   1
   End
   Begin CWUIControlsLib.CWNumEdit DeviceNum 
      Height          =   285
      Left            =   240
      TabIndex        =   7
      Top             =   360
      Width           =   1215
      _Version        =   196609
      _ExtentX        =   2143
      _ExtentY        =   503
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
      dMax_3          =   10
      discInterval_3  =   1
      discBase_3      =   1
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
   Begin CWUIControlsLib.CWNumEdit CounterNum 
      Height          =   285
      Left            =   240
      TabIndex        =   9
      Top             =   1080
      Width           =   1215
      _Version        =   196609
      _ExtentX        =   2143
      _ExtentY        =   503
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
      opts_1          =   393278
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      dMax_3          =   10
      discInterval_3  =   1
      discBase_3      =   1
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
   Begin CWUIControlsLib.CWNumEdit Measurements 
      Height          =   285
      Left            =   2040
      TabIndex        =   12
      Top             =   360
      Width           =   1215
      _Version        =   196609
      _ExtentX        =   2143
      _ExtentY        =   503
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
      opts_1          =   393278
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      dMax_3          =   10
      discInterval_3  =   1
      discBase_3      =   1
      ValueVarType_1  =   5
      Value_Val_1     =   20
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
   Begin VB.Label Label7 
      Caption         =   "Note:  You must connect a gate signal to perform buffered event counting.  Specify the gate signal in the property pages."
      Height          =   615
      Left            =   240
      TabIndex        =   14
      Top             =   6480
      Width           =   3015
   End
   Begin VB.Label Label1 
      Caption         =   "Measurements:"
      Height          =   255
      Left            =   2040
      TabIndex        =   13
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label6 
      Alignment       =   1  'Right Justify
      Caption         =   "Finite"
      Height          =   255
      Left            =   2040
      TabIndex        =   11
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label5 
      Alignment       =   1  'Right Justify
      Caption         =   "Continuous"
      Height          =   255
      Left            =   2520
      TabIndex        =   10
      Top             =   840
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Counter:"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   840
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "Device:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "Average # of events between gate signals:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   6130
      Width           =   3135
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim IsCounting As Boolean

Private Sub cmdStop_Click()
If IsCounting And CWCounter1.BufferMode = cwctrContinuous Then
    CWCounter1.Stop
    IsCounting = False
End If
End Sub

Private Sub Command1_Click()

CWCounter1.Device = DeviceNum
CWCounter1.Counter = CounterNum
CWCounter1.NMeasurements = Measurements
If Continuous Then
    CWCounter1.BufferMode = cwctrContinuous
Else
    CWCounter1.BufferMode = cwctrFinite
End If

CWCounter1.Configure
CWCounter1.Start

IsCounting = True
End Sub

Private Sub CWCounter1_AcquiredData(Measurement As Variant, ByVal Overflow As Boolean)
Dim counts
If IsArray(Measurement) Then
    counts = UBound(Measurement) - LBound(Measurement) + 1
    Avg = (Measurement(counts - 1) - Measurement(0)) / counts
    Text1.Text = Str(Avg)
 End If
CWGraph1.PlotY Measurement
End Sub

Private Sub CWCounter1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub
