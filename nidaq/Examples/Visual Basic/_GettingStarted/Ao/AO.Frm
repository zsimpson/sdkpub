VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1875
   ClientLeft      =   2175
   ClientTop       =   3735
   ClientWidth     =   6585
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1875
   ScaleWidth      =   6585
   Begin VB.CheckBox ContinuousSelect 
      Caption         =   "Continuous"
      Height          =   255
      Left            =   1680
      TabIndex        =   4
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton btnStart 
      Caption         =   "Start"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton btnStop 
      Caption         =   "Stop"
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   1455
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   840
      Width           =   1455
      _Version        =   65536
      _ExtentX        =   2566
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
      ContextID       =   15045
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   855
      Left            =   5040
      TabIndex        =   8
      Top             =   240
      Width           =   1335
      _Version        =   196609
      _ExtentX        =   2355
      _ExtentY        =   1508
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
      opts_6          =   1565
      Name_6          =   "XAxis"
      Orientation_6   =   2944
      format_6        =   7
      ClassName_7     =   "CCWFormat"
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   4
      rMax_8          =   84
      dMax_8          =   10
      discInterval_8  =   1
      Radial_6        =   0
      Enum_6          =   9
      ClassName_9     =   "CCWEnum"
      Editor_9        =   10
      ClassName_10    =   "CCWEnumArrayEditor"
      Owner_10        =   6
      Font_6          =   0
      tickopts_6      =   663
      major_6         =   10
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
      opts_13         =   541
      Name_13         =   "YAxis-1"
      Orientation_13  =   2067
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   4
      rMax_15         =   52
      dMin_15         =   -1.25
      dMax_15         =   1.25
      discInterval_15 =   1
      Radial_13       =   0
      Enum_13         =   16
      ClassName_16    =   "CCWEnum"
      Editor_16       =   17
      ClassName_17    =   "CCWEnumArrayEditor"
      Owner_17        =   13
      Font_13         =   0
      tickopts_13     =   663
      major_13        =   10
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
   Begin CWUIControlsLib.CWSlide WaveformType 
      Height          =   1095
      Left            =   3960
      TabIndex        =   6
      Top             =   120
      Width           =   975
      _Version        =   196609
      _ExtentX        =   1720
      _ExtentY        =   1931
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
      Slider_0        =   1
      ClassName_1     =   "CCWSlider"
      opts_1          =   2078
      C[0]_1          =   -2147483643
      BGImg_1         =   2
      ClassName_2     =   "CCWDrawObj"
      opts_2          =   30
      Image_2         =   3
      ClassName_3     =   "CCWPictImage"
      opts_3          =   1280
      Rows_3          =   1
      Cols_3          =   1
      Pict_3          =   286
      F_3             =   -2147483633
      B_3             =   -2147483633
      ColorReplaceWith_3=   8421504
      ColorReplace_3  =   8421504
      Tolerance_3     =   2
      Animator_2      =   0
      Blinker_2       =   0
      BFImg_1         =   4
      ClassName_4     =   "CCWDrawObj"
      opts_4          =   62
      Image_4         =   5
      ClassName_5     =   "CCWPictImage"
      opts_5          =   1280
      Rows_5          =   1
      Cols_5          =   1
      Pict_5          =   286
      F_5             =   -2147483633
      B_5             =   -2147483633
      ColorReplaceWith_5=   8421504
      ColorReplace_5  =   8421504
      Tolerance_5     =   2
      Animator_4      =   0
      Blinker_4       =   0
      Label_1         =   6
      ClassName_6     =   "CCWDrawObj"
      opts_6          =   30
      C[0]_6          =   -2147483640
      Image_6         =   7
      ClassName_7     =   "CCWTextImage"
      font_7          =   0
      Animator_6      =   0
      Blinker_6       =   0
      Border_1        =   8
      ClassName_8     =   "CCWDrawObj"
      opts_8          =   28
      Image_8         =   9
      ClassName_9     =   "CCWPictImage"
      opts_9          =   1280
      Rows_9          =   1
      Cols_9          =   1
      Pict_9          =   25
      F_9             =   -2147483633
      B_9             =   -2147483633
      ColorReplaceWith_9=   8421504
      ColorReplace_9  =   8421504
      Tolerance_9     =   2
      Animator_8      =   0
      Blinker_8       =   0
      FillBound_1     =   10
      ClassName_10    =   "CCWGuiObject"
      opts_10         =   28
      FillTok_1       =   11
      ClassName_11    =   "CCWGuiObject"
      opts_11         =   30
      Axis_1          =   12
      ClassName_12    =   "CCWAxis"
      opts_12         =   1055
      Name_12         =   "Axis"
      Orientation_12  =   133523
      format_12       =   13
      ClassName_13    =   "CCWFormat"
      Scale_12        =   14
      ClassName_14    =   "CCWScale"
      opts_14         =   24576
      rMin_14         =   10
      rMax_14         =   62
      dMin_14         =   1
      dMax_14         =   3
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Array_15        =   3
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Array[0]_15     =   17
      ClassName_17    =   "CCWEnumElt"
      opts_17         =   1
      Name_17         =   "Sine"
      DrawList_17     =   0
      varVarType_17   =   2
      Array[1]_15     =   18
      ClassName_18    =   "CCWEnumElt"
      opts_18         =   1
      Name_18         =   "Square"
      DrawList_18     =   0
      varVarType_18   =   2
      var_Val_18      =   1
      Array[2]_15     =   19
      ClassName_19    =   "CCWEnumElt"
      opts_19         =   1
      Name_19         =   "Triangle"
      DrawList_19     =   0
      varVarType_19   =   2
      var_Val_19      =   2
      Font_12         =   0
      tickopts_12     =   2718
      Caption_12      =   20
      ClassName_20    =   "CCWDrawObj"
      opts_20         =   30
      C[0]_20         =   -2147483640
      Image_20        =   21
      ClassName_21    =   "CCWTextImage"
      style_21        =   16661984
      font_21         =   0
      Animator_20     =   0
      Blinker_20      =   0
      DrawLst_1       =   22
      ClassName_22    =   "CDrawList"
      count_22        =   10
      list[10]_22     =   8
      list[9]_22      =   23
      ClassName_23    =   "CCWThumb"
      opts_23         =   31
      Name_23         =   "Pointer-1"
      C[0]_23         =   8388608
      C[1]_23         =   8388608
      C[2]_23         =   -2147483635
      Image_23        =   24
      ClassName_24    =   "CCWPictImage"
      opts_24         =   1280
      Rows_24         =   1
      Cols_24         =   1
      Pict_24         =   213
      F_24            =   8388608
      B_24            =   8388608
      ColorReplaceWith_24=   8421504
      ColorReplace_24 =   8421504
      Tolerance_24    =   2
      Animator_23     =   0
      Blinker_23      =   0
      style_23        =   1
      Value_23        =   1
      list[8]_22      =   12
      list[7]_22      =   6
      list[6]_22      =   11
      list[5]_22      =   4
      list[4]_22      =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   30
      Image_25        =   26
      ClassName_26    =   "CCWPictImage"
      opts_26         =   1280
      Rows_26         =   1
      Cols_26         =   1
      Pict_26         =   7
      F_26            =   -2147483633
      B_26            =   -2147483633
      ColorReplaceWith_26=   8421504
      ColorReplace_26 =   8421504
      Tolerance_26    =   2
      Animator_25     =   0
      Blinker_25      =   0
      list[3]_22      =   27
      ClassName_27    =   "CCWDrawObj"
      opts_27         =   28
      Image_27        =   28
      ClassName_28    =   "CCWPictImage"
      opts_28         =   1280
      Rows_28         =   1
      Cols_28         =   1
      Pict_28         =   96
      F_28            =   -2147483633
      B_28            =   -2147483633
      ColorReplaceWith_28=   8421504
      ColorReplace_28 =   8421504
      Tolerance_28    =   2
      Animator_27     =   0
      Blinker_27      =   0
      list[2]_22      =   29
      ClassName_29    =   "CCWDrawObj"
      opts_29         =   28
      Image_29        =   30
      ClassName_30    =   "CCWPictImage"
      opts_30         =   1280
      Rows_30         =   1
      Cols_30         =   1
      Pict_30         =   95
      F_30            =   -2147483633
      B_30            =   -2147483633
      ColorReplaceWith_30=   8421504
      ColorReplace_30 =   8421504
      Tolerance_30    =   2
      Animator_29     =   0
      Blinker_29      =   0
      list[1]_22      =   2
      IncDec_1        =   0
      Ptrs_1          =   31
      ClassName_31    =   "CCWPointerArray"
      Array_31        =   1
      Editor_31       =   32
      ClassName_32    =   "CCWPointerArrayEditor"
      Owner_32        =   1
      Array[0]_31     =   23
      Bindings_1      =   33
      ClassName_33    =   "CCWBindingHolderArray"
      Editor_33       =   34
      ClassName_34    =   "CCWBindingHolderArrayEditor"
      Owner_34        =   1
      Stats_1         =   35
      ClassName_35    =   "CCWStats"
      doInc_1         =   29
      doDec_1         =   27
      doFrame_1       =   25
   End
   Begin CWUIControlsLib.CWNumEdit FreqVal 
      Height          =   255
      Left            =   2640
      TabIndex        =   5
      Top             =   120
      Width           =   1095
      _Version        =   196609
      _ExtentX        =   1931
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
      C[0]_1          =   16777215
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   ".#"" Hz"""
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
      RangeMax_Val_1  =   1000
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWDAQControlsLib.CWAO CWAO1 
      Left            =   3120
      Top             =   1200
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AOTask_0        =   1
      ClassName_1     =   "CCWAOTask"
      opts_1          =   6
      ErrorEventMask_1=   32768
      Device_1        =   1
      Interval_1      =   20
      UpdateClock_1   =   2
      ClassName_2     =   "CCWAOClock"
      ClockType_2     =   1
      Frequency_2     =   10000
      Period_2        =   0.01
      ClockSourceType_2=   1
      IntervalClock_1 =   3
      ClassName_3     =   "CCWAOClock"
      ClockType_3     =   2
      Frequency_3     =   100
      Period_3        =   0.01
      InternalClockMode_3=   1
      Channels_1      =   4
      ClassName_4     =   "CCWAOChannelArray"
      Array_4         =   1
      Editor_4        =   5
      ClassName_5     =   "CCWAOChannelsArrayEditor"
      Owner_5         =   1
      Array[0]_4      =   6
      ClassName_6     =   "CCWAOChannel"
      ChannelString_6 =   "0"
      Buffer_1        =   7
      ClassName_7     =   "CCWAOBuffer"
      UpdatesPerBuffer_7=   20
      StartCond_1     =   8
      ClassName_8     =   "CCWAOCondition"
      WhichCondition_8=   1
      Type_8          =   1
      Source_8        =   "PFI0"
   End
   Begin CWUIControlsLib.CWNumEdit IterationVal 
      Height          =   255
      Left            =   2640
      TabIndex        =   3
      Top             =   600
      Width           =   1095
      _Version        =   196609
      _ExtentX        =   1931
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
      C[0]_1          =   16777215
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   50
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
      Caption         =   "Select the device and  a single channel in the property pages of the AO control."
      Height          =   495
      Left            =   120
      TabIndex        =   9
      Top             =   1320
      Width           =   2895
   End
   Begin VB.Label Label1 
      Caption         =   "Frequency"
      Height          =   255
      Left            =   1680
      TabIndex        =   7
      Top             =   120
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Number of Cycles"
      Height          =   495
      Left            =   1680
      TabIndex        =   2
      Top             =   480
      Width           =   855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const PI2 = 6.2832
Dim data(0 To 20) As Double

Private Sub Form_Load()
    WaveformType_PointerValueChanged 0, 0
End Sub

Private Sub btnStart_Click()
    CWAO1.UpdateClock.Frequency = FreqVal * 20
    CWAO1.NIterations = IterationVal
    CWAO1.Infinite = ContinuousSelect
    
    CWAO1.Configure
    CWAO1.Write data
    CWAO1.Start
    If ContinuousSelect Then
        btnStop.Enabled = True
    Else
        btnStop.Enabled = False
    End If
End Sub

Private Sub btnStop_Click()
    CWAO1.Reset
    btnStop.Enabled = False
End Sub

Private Sub WaveformType_PointerValueChanged(ByVal Pointer As Long, Value As Variant)
'Create an array of waveform data for a single analog output channel.
    Dim i As Integer
    Select Case WaveformType
        Case 0
            For i = 0 To 19
                data(i) = Sin(i / 20 * PI2)
            Next i
        Case 1
            For i = 0 To 19
                data(i) = Int(i / 10) * 2 - 1
            Next i
        Case 2
            For i = 0 To 19
                data(i) = 1 - (Abs(i - 10) / 5)
            Next i
    End Select
    data(20) = data(0) ' for display purposes only
    CWGraph1.PlotY data
End Sub
