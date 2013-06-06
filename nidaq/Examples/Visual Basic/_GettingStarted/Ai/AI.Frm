VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4350
   ClientLeft      =   1575
   ClientTop       =   7845
   ClientWidth     =   4470
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4350
   ScaleWidth      =   4470
   Begin VB.CommandButton Stop 
      Caption         =   "Stop Acquisition"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   1575
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start Acquisition"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1575
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   3720
      Top             =   480
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   120
      TabIndex        =   5
      Top             =   1080
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
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
      ContextID       =   15043
   End
   Begin CWUIControlsLib.CWButton CWButton1 
      Height          =   735
      Left            =   2040
      TabIndex        =   3
      Top             =   120
      Width           =   1575
      _Version        =   196609
      _ExtentX        =   2778
      _ExtentY        =   1296
      _StockProps     =   68
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
      Boolean_0       =   1
      ClassName_1     =   "CCWBoolean"
      opts_1          =   2582
      SclRef_1.l      =   2
      SclRef_1.t      =   2
      SclRef_1.r      =   91
      SclRef_1.b      =   51
      Scl_1.l         =   2
      Scl_1.t         =   17
      Scl_1.r         =   20
      Scl_1.b         =   51
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
      opts_5          =   30
      C[0]_5          =   -2147483640
      C[1]_5          =   -2147483640
      Image_5         =   6
      ClassName_6     =   "CCWTextImage"
      szText_6        =   "Acquisition Mode"
      font_6          =   7
      ClassName_7     =   "CCWFont"
      bFont_7         =   -1  'True
      BeginProperty Font_7 {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Animator_5      =   0
      Blinker_5       =   0
      list[3]_4       =   8
      ClassName_8     =   "CCWDrawObj"
      opts_8          =   22
      SclRef_8.l      =   2
      SclRef_8.t      =   17
      SclRef_8.r      =   23
      SclRef_8.b      =   51
      Scl_8.l         =   31
      Scl_8.t         =   17
      Scl_8.r         =   84
      Scl_8.b         =   30
      C[0]_8          =   -2147483640
      C[1]_8          =   -2147483640
      Image_8         =   9
      ClassName_9     =   "CCWTextImage"
      szText_9        =   "Continuous"
      style_9         =   16538496
      font_9          =   0
      Animator_8      =   0
      Blinker_8       =   0
      list[2]_4       =   10
      ClassName_10    =   "CCWDrawObj"
      opts_10         =   22
      SclRef_10.l     =   2
      SclRef_10.t     =   17
      SclRef_10.r     =   23
      SclRef_10.b     =   51
      Scl_10.l        =   32
      Scl_10.t        =   35
      Scl_10.r        =   75
      Scl_10.b        =   48
      C[0]_10         =   -2147483640
      C[1]_10         =   -2147483640
      Image_10        =   11
      ClassName_11    =   "CCWTextImage"
      szText_11       =   "One shot"
      style_11        =   1294816321
      font_11         =   0
      Animator_10     =   0
      Blinker_10      =   0
      list[1]_4       =   12
      ClassName_12    =   "CCWDrawObj"
      opts_12         =   30
      Image_12        =   13
      ClassName_13    =   "CCWPictImage"
      opts_13         =   1280
      Rows_13         =   1
      Cols_13         =   1
      Pict_13         =   58
      F_13            =   -2147483633
      B_13            =   -2147483633
      ColorReplaceWith_13=   8421504
      ColorReplace_13 =   8421504
      Tolerance_13    =   2
      Animator_12     =   0
      Blinker_12      =   0
      varVarType_3    =   5
      Array[1]_2      =   14
      ClassName_14    =   "CCWEnumElt"
      opts_14         =   1
      Name_14         =   "On"
      frame_14        =   286
      DrawList_14     =   15
      ClassName_15    =   "CDrawList"
      count_15        =   4
      list[4]_15      =   16
      ClassName_16    =   "CCWDrawObj"
      opts_16         =   30
      C[0]_16         =   -2147483640
      C[1]_16         =   -2147483640
      Image_16        =   6
      Animator_16     =   0
      Blinker_16      =   0
      list[3]_15      =   17
      ClassName_17    =   "CCWDrawObj"
      opts_17         =   22
      SclRef_17.l     =   2
      SclRef_17.t     =   17
      SclRef_17.r     =   23
      SclRef_17.b     =   51
      Scl_17.l        =   31
      Scl_17.t        =   17
      Scl_17.r        =   84
      Scl_17.b        =   30
      C[0]_17         =   -2147483640
      C[1]_17         =   -2147483640
      Image_17        =   9
      Animator_17     =   0
      Blinker_17      =   0
      list[2]_15      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   22
      SclRef_18.l     =   2
      SclRef_18.t     =   17
      SclRef_18.r     =   23
      SclRef_18.b     =   51
      Scl_18.l        =   32
      Scl_18.t        =   35
      Scl_18.r        =   75
      Scl_18.b        =   48
      C[0]_18         =   -2147483640
      C[1]_18         =   -2147483640
      Image_18        =   11
      Animator_18     =   0
      Blinker_18      =   0
      list[1]_15      =   19
      ClassName_19    =   "CCWDrawObj"
      opts_19         =   30
      Image_19        =   20
      ClassName_20    =   "CCWPictImage"
      opts_20         =   1280
      Rows_20         =   1
      Cols_20         =   1
      Pict_20         =   57
      F_20            =   -2147483633
      B_20            =   -2147483633
      ColorReplaceWith_20=   8421504
      ColorReplace_20 =   8421504
      Tolerance_20    =   2
      Animator_19     =   0
      Blinker_19      =   0
      varVarType_14   =   5
      Bindings_1      =   21
      ClassName_21    =   "CCWBindingHolderArray"
      Editor_21       =   22
      ClassName_22    =   "CCWBindingHolderArrayEditor"
      Owner_22        =   1
      drawState_1     =   1
      mechAction_1    =   1
      BGImg_1         =   23
      ClassName_23    =   "CCWDrawObj"
      opts_23         =   30
      Image_23        =   24
      ClassName_24    =   "CCWPictImage"
      opts_24         =   1280
      Rows_24         =   1
      Cols_24         =   1
      Pict_24         =   286
      F_24            =   -2147483633
      B_24            =   -2147483633
      ColorReplaceWith_24=   8421504
      ColorReplace_24 =   8421504
      Tolerance_24    =   2
      Animator_23     =   0
      Blinker_23      =   0
      Array_1         =   6
      Editor_1        =   0
      Array[0]_1      =   12
      Array[1]_1      =   19
      Array[2]_1      =   0
      Array[3]_1      =   0
      Array[4]_1      =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   30
      Image_25        =   9
      Animator_25     =   0
      Blinker_25      =   0
      Array[5]_1      =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   30
      Image_26        =   11
      Animator_26     =   0
      Blinker_26      =   0
      Label_1         =   27
      ClassName_27    =   "CCWDrawObj"
      opts_27         =   30
      C[0]_27         =   -2147483640
      Image_27        =   6
      Animator_27     =   0
      Blinker_27      =   0
   End
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   3720
      Top             =   0
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      opts_1          =   2
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   1000
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      Frequency_2     =   10000
      Period_2        =   0.01
      ClockSourceType_2=   1
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      Frequency_3     =   100
      Period_3        =   0.01
      InternalClockMode_3=   1
      Buffer_1        =   4
      ClassName_4     =   "CCWAIBuffer"
      Channels_1      =   5
      ClassName_5     =   "CCWAIChannelArray"
      Array_5         =   1
      Editor_5        =   6
      ClassName_6     =   "CCWAIChannelsArrayEditor"
      Owner_6         =   1
      Array[0]_5      =   7
      ClassName_7     =   "CCWAIChannel"
      Channels_7      =   "1"
      StartCond_1     =   8
      ClassName_8     =   "CCWAICondition"
      WhichCondition_8=   1
      PauseCond_1     =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   2
      TrigPauseMode_9 =   7
      StopCond_1      =   10
      ClassName_10    =   "CCWAICondition"
      WhichCondition_10=   3
      HoldoffClock_1  =   11
      ClassName_11    =   "CCWAIClock"
      Frequency_11    =   100
      Period_11       =   0.01
      InternalClockMode_11=   1
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   2415
      Left            =   120
      TabIndex        =   0
      Top             =   1680
      Width           =   4215
      _Version        =   196609
      _ExtentX        =   7435
      _ExtentY        =   4260
      _StockProps     =   71
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
      Graph_0         =   1
      ClassName_1     =   "CCWGraphFrame"
      opts_1          =   30
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
      opts_5          =   4194335
      Name_5          =   "Plot-1"
      C[0]_5          =   65280
      C[1]_5          =   255
      C[2]_5          =   16711680
      C[3]_5          =   16776960
      Event_5         =   2
      X_5             =   6
      ClassName_6     =   "CCWAxis"
      opts_6          =   1567
      Name_6          =   "XAxis"
      Orientation_6   =   2944
      format_6        =   7
      ClassName_7     =   "CCWFormat"
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   25
      rMax_8          =   270
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
      opts_11         =   30
      C[0]_11         =   -2147483640
      Image_11        =   12
      ClassName_12    =   "CCWTextImage"
      font_12         =   0
      Animator_11     =   0
      Blinker_11      =   0
      Y_5             =   13
      ClassName_13    =   "CCWAxis"
      opts_13         =   1567
      Name_13         =   "YAxis-1"
      Orientation_13  =   2067
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   134
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
      major_13        =   2
      minor_13        =   1
      Caption_13      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   30
      C[0]_18         =   -2147483640
      Image_18        =   19
      ClassName_19    =   "CCWTextImage"
      font_19         =   0
      Animator_18     =   0
      Blinker_18      =   0
      LineStyle_5     =   1
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
      opts_22         =   4194335
      Name_22         =   "[Template]"
      C[0]_22         =   65280
      C[1]_22         =   255
      C[2]_22         =   16711680
      C[3]_22         =   16776960
      Event_22        =   2
      X_22            =   6
      Y_22            =   13
      LineStyle_22    =   1
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
      opts_25         =   30
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
      opts_27         =   30
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
      opts_29         =   30
      C[0]_29         =   -2147483640
      Image_29        =   30
      ClassName_30    =   "CCWTextImage"
      style_30        =   1852797037
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
   Begin VB.Label Label1 
      Caption         =   "Select the device and channel in the property pages of the AI control."
      Height          =   495
      Left            =   1800
      TabIndex        =   4
      Top             =   960
      Width           =   2535
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Start_Click()
    If CWButton1.Value Then
        CWAI1.StopCondition.Type = cwaiContinuous
    Else
        CWAI1.StopCondition.Type = cwaiNoActiveCondition
    End If
    
    CWAI1.Configure
    CWAI1.Start
End Sub

Private Sub Stop_Click()
    CWAI1.Stop
    ' Only need to call Reset to free up
    ' resource if you don't plan to run
    ' another acquisition
    CWAI1.Reset
End Sub

Private Sub CWAI1_AcquiredData(ScaledData As Variant, BinaryCodes As Variant)
    CWGraph1.PlotY ScaledData
End Sub

Private Sub CWButton1_ValueChanged(ByVal Value As Boolean)
    If Value Then
        CWAI1.StopCondition.Type = cwaiContinuous
    Else
        CWAI1.StopCondition.Type = cwaiNoActiveCondition
    End If
End Sub

Private Sub CWAI1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

Private Sub CWAI1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Warning: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub


