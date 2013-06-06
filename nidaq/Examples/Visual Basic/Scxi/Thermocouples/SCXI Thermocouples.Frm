VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{E7BC3920-33D4-11D0-8B73-0020AF31CEF9}#1.4#0"; "CWANALYSIS.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form AI1 
   Caption         =   "SCXI Thermocouple Acquisition"
   ClientHeight    =   5880
   ClientLeft      =   3570
   ClientTop       =   2130
   ClientWidth     =   6285
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5880
   ScaleWidth      =   6285
   Begin VB.CommandButton Command1 
      Caption         =   "About CJC"
      Height          =   315
      Left            =   3900
      TabIndex        =   21
      Top             =   5460
      Width           =   1515
   End
   Begin VB.ComboBox CJCType 
      Height          =   315
      ItemData        =   "SCXI Thermocouples.frx":0000
      Left            =   1680
      List            =   "SCXI Thermocouples.frx":000D
      TabIndex        =   20
      Text            =   "IC Sensor"
      Top             =   5460
      Width           =   1695
   End
   Begin VB.TextBox CJCSensor 
      Height          =   285
      Left            =   1680
      TabIndex        =   18
      Text            =   "ob0!sc1!md1!mtemp"
      Top             =   5160
      Width           =   1695
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   120
      TabIndex        =   15
      Top             =   600
      Width           =   1215
   End
   Begin VB.TextBox LowerLimit 
      Height          =   285
      Left            =   1680
      TabIndex        =   12
      Text            =   "-0.01"
      Top             =   4800
      Width           =   1335
   End
   Begin VB.TextBox UpperLimit 
      Height          =   285
      Left            =   1680
      TabIndex        =   11
      Text            =   "0.01"
      Top             =   4440
      Width           =   1335
   End
   Begin VB.TextBox ChartRate 
      Height          =   375
      Left            =   3240
      TabIndex        =   5
      Text            =   "6"
      Top             =   3840
      Width           =   1335
   End
   Begin VB.TextBox NumAvg 
      Height          =   375
      Left            =   4800
      TabIndex        =   4
      Text            =   "100"
      Top             =   3840
      Width           =   1335
   End
   Begin VB.TextBox Channel 
      Height          =   375
      Left            =   1680
      TabIndex        =   3
      Text            =   "ob0!sc1!md1!0:3"
      Top             =   3840
      Width           =   1335
   End
   Begin VB.TextBox Device 
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Text            =   "1"
      Top             =   3840
      Width           =   1335
   End
   Begin VB.CommandButton Quit 
      Caption         =   "Quit"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   23
      Top             =   1440
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
      ContextID       =   15065
   End
   Begin CWAnalysisControlsLib.CWStat CWStat1 
      Left            =   1080
      Top             =   2040
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   600
      Top             =   2640
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWAnalysisControlsLib.CWArray CWArray1 
      Left            =   600
      Top             =   2040
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWDAQControlsLib.CWAI DAQTemp 
      Left            =   120
      Top             =   2640
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   1
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      ClockType_2     =   1
      Frequency_2     =   100
      Period_2        =   0.01
      ClockSourceType_2=   1
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      ClockType_3     =   2
      Frequency_3     =   100
      Period_3        =   0.01
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
      Channels_7      =   "ob0!sc1!md1!mtemp"
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
      ClockType_11    =   3
      Frequency_11    =   100
      Period_11       =   0.01
      InternalClockMode_11=   1
   End
   Begin CWUIControlsLib.CWSlide TCType 
      Height          =   735
      Left            =   3960
      TabIndex        =   16
      Top             =   4560
      Width           =   1455
      _Version        =   196609
      _ExtentX        =   2566
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
      Slider_0        =   1
      ClassName_1     =   "CCWSlider"
      opts_1          =   2078
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
      opts_4          =   8254
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
      style_1         =   5
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
      Orientation_12  =   134019
      format_12       =   13
      ClassName_13    =   "CCWFormat"
      Scale_12        =   14
      ClassName_14    =   "CCWScale"
      opts_14         =   24576
      rMin_14         =   4
      rMax_14         =   92
      dMin_14         =   1
      dMax_14         =   7
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Array_15        =   7
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Array[0]_15     =   17
      ClassName_17    =   "CCWEnumElt"
      opts_17         =   1
      Name_17         =   "B"
      DrawList_17     =   0
      varVarType_17   =   2
      var_Val_17      =   7
      Array[1]_15     =   18
      ClassName_18    =   "CCWEnumElt"
      opts_18         =   1
      Name_18         =   "E"
      DrawList_18     =   0
      varVarType_18   =   2
      var_Val_18      =   1
      Array[2]_15     =   19
      ClassName_19    =   "CCWEnumElt"
      opts_19         =   1
      Name_19         =   "J"
      DrawList_19     =   0
      varVarType_19   =   2
      var_Val_19      =   2
      Array[3]_15     =   20
      ClassName_20    =   "CCWEnumElt"
      opts_20         =   1
      Name_20         =   "K"
      DrawList_20     =   0
      varVarType_20   =   2
      var_Val_20      =   3
      Array[4]_15     =   21
      ClassName_21    =   "CCWEnumElt"
      opts_21         =   1
      Name_21         =   "R"
      DrawList_21     =   0
      varVarType_21   =   2
      var_Val_21      =   4
      Array[5]_15     =   22
      ClassName_22    =   "CCWEnumElt"
      opts_22         =   1
      Name_22         =   "S"
      DrawList_22     =   0
      varVarType_22   =   2
      var_Val_22      =   5
      Array[6]_15     =   23
      ClassName_23    =   "CCWEnumElt"
      opts_23         =   1
      Name_23         =   "T"
      DrawList_23     =   0
      varVarType_23   =   2
      var_Val_23      =   6
      Font_12         =   0
      tickopts_12     =   2718
      Caption_12      =   24
      ClassName_24    =   "CCWDrawObj"
      opts_24         =   30
      C[0]_24         =   -2147483640
      Image_24        =   25
      ClassName_25    =   "CCWTextImage"
      style_25        =   -2147483633
      font_25         =   0
      Animator_24     =   0
      Blinker_24      =   0
      DrawLst_1       =   26
      ClassName_26    =   "CDrawList"
      count_26        =   10
      list[10]_26     =   8
      list[9]_26      =   27
      ClassName_27    =   "CCWThumb"
      opts_27         =   23
      Name_27         =   "Pointer-1"
      SclRef_27.l     =   2
      SclRef_27.t     =   2
      SclRef_27.r     =   139
      SclRef_27.b     =   51
      Scl_27.l        =   108
      Scl_27.t        =   19
      Scl_27.r        =   118
      Scl_27.b        =   31
      C[0]_27         =   255
      C[1]_27         =   255
      C[2]_27         =   -2147483635
      Image_27        =   28
      ClassName_28    =   "CCWPictImage"
      opts_28         =   1280
      Rows_28         =   1
      Cols_28         =   1
      Pict_28         =   218
      F_28            =   255
      B_28            =   255
      ColorReplaceWith_28=   8421504
      ColorReplace_28 =   8421504
      Tolerance_28    =   2
      Animator_27     =   0
      Blinker_27      =   0
      style_27        =   1
      Value_27        =   3
      list[8]_26      =   12
      list[7]_26      =   6
      list[6]_26      =   11
      list[5]_26      =   4
      list[4]_26      =   29
      ClassName_29    =   "CCWDrawObj"
      opts_29         =   30
      Image_29        =   30
      ClassName_30    =   "CCWPictImage"
      opts_30         =   1280
      Rows_30         =   1
      Cols_30         =   1
      Pict_30         =   7
      F_30            =   -2147483633
      B_30            =   -2147483633
      ColorReplaceWith_30=   8421504
      ColorReplace_30 =   8421504
      Tolerance_30    =   2
      Animator_29     =   0
      Blinker_29      =   0
      list[3]_26      =   31
      ClassName_31    =   "CCWDrawObj"
      opts_31         =   30
      Image_31        =   32
      ClassName_32    =   "CCWPictImage"
      opts_32         =   1280
      Rows_32         =   1
      Cols_32         =   1
      Pict_32         =   93
      F_32            =   -2147483633
      B_32            =   -2147483633
      ColorReplaceWith_32=   8421504
      ColorReplace_32 =   8421504
      Tolerance_32    =   2
      Animator_31     =   0
      Blinker_31      =   0
      list[2]_26      =   33
      ClassName_33    =   "CCWDrawObj"
      opts_33         =   30
      Image_33        =   34
      ClassName_34    =   "CCWPictImage"
      opts_34         =   1280
      Rows_34         =   1
      Cols_34         =   1
      Pict_34         =   94
      F_34            =   -2147483633
      B_34            =   -2147483633
      ColorReplaceWith_34=   8421504
      ColorReplace_34 =   8421504
      Tolerance_34    =   2
      Animator_33     =   0
      Blinker_33      =   0
      list[1]_26      =   2
      IncDec_1        =   0
      Ptrs_1          =   35
      ClassName_35    =   "CCWPointerArray"
      Array_35        =   1
      Editor_35       =   36
      ClassName_36    =   "CCWPointerArrayEditor"
      Owner_36        =   1
      Array[0]_35     =   27
      Bindings_1      =   37
      ClassName_37    =   "CCWBindingHolderArray"
      Editor_37       =   38
      ClassName_38    =   "CCWBindingHolderArrayEditor"
      Owner_38        =   1
      Stats_1         =   39
      ClassName_39    =   "CCWStats"
      doInc_1         =   33
      doDec_1         =   31
      doFrame_1       =   29
   End
   Begin CWUIControlsLib.CWGraph Graph 
      Height          =   2955
      Left            =   1680
      TabIndex        =   10
      Top             =   240
      Width           =   4455
      _Version        =   196609
      _ExtentX        =   7858
      _ExtentY        =   5212
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
      opts_1          =   14
      Event_1         =   2
      ClassName_2     =   "CCWGFPlotEvent"
      Owner_2         =   1
      Plots_1         =   3
      ClassName_3     =   "CCWDataPlots"
      Array_3         =   4
      Editor_3        =   4
      ClassName_4     =   "CCWGFPlotArrayEditor"
      Owner_4         =   1
      Array[0]_3      =   5
      ClassName_5     =   "CCWDataPlot"
      opts_5          =   4194319
      Name_5          =   "Plot 1"
      C[0]_5          =   65280
      C[1]_5          =   65535
      C[2]_5          =   16711680
      C[3]_5          =   65535
      Event_5         =   2
      X_5             =   6
      ClassName_6     =   "CCWAxis"
      opts_6          =   527
      Name_6          =   "X-Axis"
      C[0]_6          =   8
      C[1]_6          =   8
      C[2]_6          =   8
      C[4]_6          =   -2147483640
      Orientation_6   =   2560
      format_6        =   7
      ClassName_7     =   "CCWFormat"
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   39
      rMax_8          =   292
      dMax_8          =   50
      discInterval_8  =   1
      Radial_6        =   0
      Enum_6          =   9
      ClassName_9     =   "CCWEnum"
      Editor_9        =   10
      ClassName_10    =   "CCWEnumArrayEditor"
      Owner_10        =   6
      Font_6          =   0
      tickopts_6      =   2071
      major_6         =   10
      minor_6         =   5
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
      opts_13         =   1551
      Name_13         =   "Y-Axis"
      C[0]_13         =   8
      C[1]_13         =   8
      C[2]_13         =   8
      C[4]_13         =   -2147483640
      Orientation_13  =   2067
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Format_14       =   """ °C"""
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   185
      dMin_15         =   15
      dMax_15         =   30
      discInterval_15 =   1
      Radial_13       =   0
      Enum_13         =   16
      ClassName_16    =   "CCWEnum"
      Editor_16       =   17
      ClassName_17    =   "CCWEnumArrayEditor"
      Owner_17        =   13
      Font_13         =   0
      tickopts_13     =   2071
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
      Array[1]_3      =   20
      ClassName_20    =   "CCWDataPlot"
      opts_20         =   4194319
      Name_20         =   "Plot-2"
      C[0]_20         =   255
      C[1]_20         =   65535
      C[2]_20         =   16711680
      C[3]_20         =   65535
      Event_20        =   2
      X_20            =   6
      Y_20            =   13
      LineStyle_20    =   1
      LineWidth_20    =   1
      BasePlot_20     =   0
      DefaultXInc_20  =   1
      DefaultPlotPerRow_20=   -1  'True
      Array[2]_3      =   21
      ClassName_21    =   "CCWDataPlot"
      opts_21         =   4194319
      Name_21         =   "Plot-3"
      C[0]_21         =   65535
      C[1]_21         =   65535
      C[2]_21         =   16711680
      C[3]_21         =   65535
      Event_21        =   2
      X_21            =   6
      Y_21            =   13
      LineStyle_21    =   1
      LineWidth_21    =   1
      BasePlot_21     =   0
      DefaultXInc_21  =   1
      DefaultPlotPerRow_21=   -1  'True
      Array[3]_3      =   22
      ClassName_22    =   "CCWDataPlot"
      opts_22         =   4194319
      Name_22         =   "Plot-4"
      C[0]_22         =   16776960
      C[1]_22         =   65535
      C[2]_22         =   16711680
      C[3]_22         =   65535
      Event_22        =   2
      X_22            =   6
      Y_22            =   13
      LineStyle_22    =   1
      LineWidth_22    =   1
      BasePlot_22     =   0
      DefaultXInc_22  =   1
      DefaultPlotPerRow_22=   -1  'True
      Axes_1          =   23
      ClassName_23    =   "CCWAxes"
      Array_23        =   2
      Editor_23       =   24
      ClassName_24    =   "CCWGFAxisArrayEditor"
      Owner_24        =   1
      Array[0]_23     =   6
      Array[1]_23     =   13
      DefaultPlot_1   =   25
      ClassName_25    =   "CCWDataPlot"
      opts_25         =   4194319
      Name_25         =   "Template"
      C[0]_25         =   16777215
      C[1]_25         =   65535
      C[2]_25         =   16711680
      C[3]_25         =   65535
      Event_25        =   2
      X_25            =   6
      Y_25            =   13
      LineStyle_25    =   1
      LineWidth_25    =   1
      BasePlot_25     =   0
      DefaultXInc_25  =   1
      DefaultPlotPerRow_25=   -1  'True
      Cursors_1       =   26
      ClassName_26    =   "CCWCursors"
      Editor_26       =   27
      ClassName_27    =   "CCWGFCursorArrayEditor"
      Owner_27        =   1
      TrackMode_1     =   2
      GraphBackground_1=   0
      GraphFrame_1    =   28
      ClassName_28    =   "CCWDrawObj"
      opts_28         =   14
      Image_28        =   29
      ClassName_29    =   "CCWPictImage"
      opts_29         =   1024
      Rows_29         =   1
      Cols_29         =   1
      F_29            =   -2147483633
      B_29            =   -2147483633
      ColorReplaceWith_29=   8421504
      ColorReplace_29 =   8421504
      Tolerance_29    =   2
      Animator_28     =   0
      Blinker_28      =   0
      PlotFrame_1     =   30
      ClassName_30    =   "CCWDrawObj"
      opts_30         =   14
      Image_30        =   31
      ClassName_31    =   "CCWPictImage"
      opts_31         =   1024
      Rows_31         =   1
      Cols_31         =   1
      Pict_31         =   1
      F_31            =   -2147483633
      B_31            =   0
      ColorReplaceWith_31=   8421504
      ColorReplace_31 =   8421504
      Tolerance_31    =   2
      Animator_30     =   0
      Blinker_30      =   0
      Caption_1       =   32
      ClassName_32    =   "CCWDrawObj"
      opts_32         =   30
      C[0]_32         =   -2147483640
      Image_32        =   33
      ClassName_33    =   "CCWTextImage"
      style_33        =   24847552
      font_33         =   0
      Animator_32     =   0
      Blinker_32      =   0
      DefaultXInc_1   =   1
      DefaultPlotPerRow_1=   -1  'True
      Bindings_1      =   34
      ClassName_34    =   "CCWBindingHolderArray"
      Editor_34       =   35
      ClassName_35    =   "CCWBindingHolderArrayEditor"
      Owner_35        =   1
   End
   Begin CWDAQControlsLib.CWAI AI 
      Left            =   120
      Top             =   2040
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   100
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      ClockType_2     =   1
      Frequency_2     =   600
      Period_2        =   0.01
      ClockSourceType_2=   1
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      ClockType_3     =   2
      Frequency_3     =   100
      Period_3        =   0.01
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
      Channels_7      =   "sc1!md1!0:3"
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
      Type_10         =   4
      HoldoffClock_1  =   11
      ClassName_11    =   "CCWAIClock"
      ClockType_11    =   3
      Frequency_11    =   100
      Period_11       =   0.01
      InternalClockMode_11=   1
   End
   Begin VB.Label Label10 
      Alignment       =   1  'Right Justify
      Caption         =   "CJC Sensor Type"
      Height          =   255
      Left            =   120
      TabIndex        =   22
      Top             =   5460
      Width           =   1455
   End
   Begin VB.Label Label9 
      Alignment       =   1  'Right Justify
      Caption         =   "CJC Sensor Channel"
      Height          =   255
      Left            =   120
      TabIndex        =   19
      Top             =   5160
      Width           =   1455
   End
   Begin VB.Label Label7 
      Caption         =   "Thermocouple Type"
      Height          =   255
      Left            =   3960
      TabIndex        =   17
      Top             =   4320
      Width           =   1455
   End
   Begin VB.Label Label6 
      Alignment       =   1  'Right Justify
      Caption         =   "Lower Limit"
      Height          =   255
      Left            =   720
      TabIndex        =   14
      Top             =   4800
      Width           =   855
   End
   Begin VB.Label Label5 
      Alignment       =   1  'Right Justify
      Caption         =   "Upper Limit"
      Height          =   255
      Left            =   720
      TabIndex        =   13
      Top             =   4440
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Chart Update Rate"
      Height          =   255
      Left            =   3240
      TabIndex        =   9
      Top             =   3480
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Number of Points to Average"
      Height          =   375
      Left            =   4800
      TabIndex        =   8
      Top             =   3360
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Channel"
      Height          =   255
      Left            =   1680
      TabIndex        =   7
      Top             =   3480
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Device"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   3480
      Width           =   1215
   End
End
Attribute VB_Name = "AI1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim CJCTemp As Double
Dim lErr As Long

Private Sub AI_AcquiredData(Voltages As Variant, BinaryCodes As Variant)
    
    Dim i, lErr
    Dim nChans As Double
    Dim chanVolts As Variant
    Dim chanTemps As Variant
    Dim avgTemp() As Double
    Dim AIChan As CWAIChannel
    
    ' determine number of channels in array
    nChans = AI.Channels.NChannels
    
    ReDim avgTemp(0 To nChans - 1) As Double
    
    ' Loop on each channel
    For i = 0 To nChans - 1
        'Copy data from one channel into chanVolts
        If nChans > 1 Then
            chanVolts = CWArray1.IndexArray(Voltages, Array(i, Null))
        Else
            chanVolts = CWArray1.CopyArray(Voltages)
        End If
        
        'Convert chanVolts into chanTemp
        lErr = CWDAQTools1.ConvertTC(TCType, CJCTemp, cwCelsius, chanVolts, chanTemps)
        If lErr <> 0 Then
            MsgBox "Conversion Error: " + CStr(Err)
            AI.Stop
        End If
        
        'Calculate average temperature of channel (AvgTemp)
        avgTemp(i) = CWStat1.Mean(chanTemps)
        If Err <> 0 Then
            MsgBox "Averaging Error: " + CStr(Err)
            AI.Stop
        End If
    Next i
    'Chart Average Temperatures
    Graph.ChartY avgTemp, , False
End Sub

Private Sub Command1_Click()
    CJCInfo.Show
End Sub

Private Sub AI_DAQError(ByVal ErrorCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "DAQ Error: " + CStr(ErrorCode)
End Sub

Private Sub Start_Click()
    Dim lErr As Long
    
    Graph.ClearData
    Graph.Axes(1).SetMinMax 0, 50
    Measure_CJCTemp
    
    AI.Device = Device
    AI.Channels.RemoveAll
    If UpperLimit = "" Or LowerLimit = "" Then
        AI.Channels.Add Channel
    Else
        AI.Channels.Add Channel, UpperLimit, LowerLimit
    End If
    
    AI.NScans = Val(NumAvg.Text)
    AI.ScanClock.Frequency = Val(NumAvg) * Val(ChartRate)
    
    AI.Reset
    lErr = AI.Configure
    If lErr <> 0 Then MsgBox "DAQ Configure: " + CStr(lErr)
    
    lErr = AI.Start
    If lErr <> 0 Then MsgBox "DAQ Start: " + CStr(lErr)
    
End Sub

Private Sub Quit_Click()
    End
End Sub

Private Sub Stop_Click()
    AI.Stop
End Sub
Private Sub Measure_CJCTemp()
    Dim volts As Variant
    Dim binaries As Variant
    Dim TempCJC As Variant
    DAQTemp.Device = Device
    DAQTemp.Channels.RemoveAll
    DAQTemp.Channels.Add CJCSensor, 2, 0
    DAQTemp.NScans = 1
    DAQTemp.ScanClock.Frequency = 100
    DAQTemp.Reset
    DAQTemp.Configure
    Err = DAQTemp.AcquireData(volts, binaries)
    If Err <> 0 Then
        MsgBox "CJC Acquire: " + CStr(Err)
    Else
        Select Case CJCType.ListIndex
            Case 1
                lErr = CWDAQTools1.ConvertThermistor(cwVoltRef, 2.5, 5000, cwCelsius, volts(0), TempCJC)
                CJCTemp = TempCJC
            Case 2
                lErr = CWDAQTools1.ConvertThermistor(cwThermCurrent, 0.0001, 5000, cwCelsius, volts(0), TempCJC)
                CJCTemp = TempCJC
            Case Else
                CJCTemp = volts(0) * 100
        End Select
        DAQTemp.Reset
    End If
End Sub
