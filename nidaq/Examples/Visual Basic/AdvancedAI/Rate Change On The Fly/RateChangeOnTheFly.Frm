VERSION 5.00
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{E7BC3920-33D4-11D0-8B73-0020AF31CEF9}#1.4#0"; "CWANALYSIS.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Rate-Change-On-The-Fly"
   ClientHeight    =   6930
   ClientLeft      =   3480
   ClientTop       =   2520
   ClientWidth     =   6915
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6930
   ScaleWidth      =   6915
   Begin VB.CommandButton Start 
      Caption         =   "Acquire"
      Height          =   315
      Left            =   4860
      TabIndex        =   3
      Top             =   3720
      Width           =   1215
   End
   Begin CWUIControlsLib.CWNumEdit DeviceNumEdit 
      Height          =   285
      Left            =   4800
      TabIndex        =   21
      Top             =   480
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
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   315
      Left            =   4860
      TabIndex        =   20
      Top             =   4080
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   556
      _StockProps     =   6
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.26
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      HelpFile        =   "cwdaq.hlp"
      ContextID       =   15054
   End
   Begin CWUIControlsLib.CWButton ModeSelect 
      Height          =   975
      Left            =   3600
      TabIndex        =   15
      Top             =   5160
      Width           =   375
      _Version        =   196609
      _ExtentX        =   661
      _ExtentY        =   1720
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
      opts_1          =   2590
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
      font_6          =   0
      Animator_5      =   0
      Blinker_5       =   0
      list[3]_4       =   7
      ClassName_7     =   "CCWDrawObj"
      opts_7          =   28
      C[0]_7          =   -2147483640
      C[1]_7          =   -2147483640
      Image_7         =   8
      ClassName_8     =   "CCWTextImage"
      style_8         =   -2147483640
      font_8          =   0
      Animator_7      =   0
      Blinker_7       =   0
      list[2]_4       =   9
      ClassName_9     =   "CCWDrawObj"
      opts_9          =   28
      C[0]_9          =   -2147483640
      C[1]_9          =   -2147483640
      Image_9         =   10
      ClassName_10    =   "CCWTextImage"
      style_10        =   19829728
      font_10         =   0
      Animator_9      =   0
      Blinker_9       =   0
      list[1]_4       =   11
      ClassName_11    =   "CCWDrawObj"
      opts_11         =   30
      C[0]_11         =   8421504
      C[1]_11         =   8421504
      Image_11        =   12
      ClassName_12    =   "CCWPictImage"
      opts_12         =   1280
      Rows_12         =   1
      Cols_12         =   1
      Pict_12         =   64
      F_12            =   8421504
      B_12            =   8421504
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
      opts_15         =   30
      C[0]_15         =   -2147483640
      C[1]_15         =   -2147483640
      Image_15        =   6
      Animator_15     =   0
      Blinker_15      =   0
      list[3]_14      =   16
      ClassName_16    =   "CCWDrawObj"
      opts_16         =   28
      C[0]_16         =   -2147483640
      C[1]_16         =   -2147483640
      Image_16        =   8
      Animator_16     =   0
      Blinker_16      =   0
      list[2]_14      =   17
      ClassName_17    =   "CCWDrawObj"
      opts_17         =   28
      C[0]_17         =   -2147483640
      C[1]_17         =   -2147483640
      Image_17        =   10
      Animator_17     =   0
      Blinker_17      =   0
      list[1]_14      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   30
      C[0]_18         =   8421504
      C[1]_18         =   8421504
      Image_18        =   19
      ClassName_19    =   "CCWPictImage"
      opts_19         =   1280
      Rows_19         =   1
      Cols_19         =   1
      Pict_19         =   63
      F_19            =   8421504
      B_19            =   8421504
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
      Style_1         =   8
      mechAction_1    =   1
      BGImg_1         =   22
      ClassName_22    =   "CCWDrawObj"
      opts_22         =   30
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
      opts_24         =   30
      Image_24        =   8
      Animator_24     =   0
      Blinker_24      =   0
      Array[5]_1      =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   30
      Image_25        =   10
      Animator_25     =   0
      Blinker_25      =   0
      Label_1         =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   30
      C[0]_26         =   -2147483640
      Image_26        =   6
      Animator_26     =   0
      Blinker_26      =   0
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   3600
      Top             =   1440
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWNumEdit numSamples 
      Height          =   255
      Left            =   4800
      TabIndex        =   14
      Top             =   3360
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
      opts_1          =   393246
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
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   100
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit RateBelow 
      Height          =   255
      Left            =   4800
      TabIndex        =   9
      Top             =   1920
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
      opts_1          =   393246
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   """ Hz"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   1000
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
   Begin CWUIControlsLib.CWNumEdit RateAbove 
      Height          =   255
      Left            =   4800
      TabIndex        =   8
      Top             =   2640
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
      opts_1          =   393246
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   """ Hz"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   10000
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
   Begin CWUIControlsLib.CWNumEdit VoltageThreshold 
      Height          =   255
      Left            =   4800
      TabIndex        =   7
      Top             =   1200
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
      opts_1          =   393246
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   """ V"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   0.5
      IncValueVarType_1=   5
      IncValue_Val_1  =   0.5
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
   Begin CWAnalysisControlsLib.CWArray CWArray1 
      Left            =   3600
      Top             =   960
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWGraph CWGraph3 
      Height          =   1935
      Left            =   120
      TabIndex        =   2
      Top             =   4200
      Width           =   3375
      _Version        =   196609
      _ExtentX        =   5953
      _ExtentY        =   3413
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
      C[0]_1          =   0
      Event_1         =   2
      ClassName_2     =   "CCWGFPlotEvent"
      Owner_2         =   1
      Plots_1         =   3
      ClassName_3     =   "CCWDataPlots"
      Array_3         =   2
      Editor_3        =   4
      ClassName_4     =   "CCWGFPlotArrayEditor"
      Owner_4         =   1
      Array[0]_3      =   5
      ClassName_5     =   "CCWDataPlot"
      opts_5          =   4194335
      Name_5          =   "Plot-1"
      C[0]_5          =   65535
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
      Format_7        =   """ s"""
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   35
      rMax_8          =   210
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
      major_6         =   5
      minor_6         =   2.5
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
      Format_14       =   """ V"""
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   102
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
      major_13        =   5
      minor_13        =   2.5
      Caption_13      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   30
      C[0]_18         =   -2147483640
      Image_18        =   19
      ClassName_19    =   "CCWTextImage"
      font_19         =   0
      Animator_18     =   0
      Blinker_18      =   0
      PointStyle_5    =   18
      LineStyle_5     =   1
      LineWidth_5     =   1
      BasePlot_5      =   0
      DefaultXInc_5   =   1
      DefaultPlotPerRow_5=   -1  'True
      Array[1]_3      =   20
      ClassName_20    =   "CCWDataPlot"
      opts_20         =   4194335
      Name_20         =   "Plot-2"
      C[0]_20         =   16776960
      C[1]_20         =   255
      C[2]_20         =   16711680
      C[3]_20         =   16776960
      Event_20        =   2
      X_20            =   6
      Y_20            =   13
      LineStyle_20    =   4
      LineWidth_20    =   1
      BasePlot_20     =   0
      DefaultXInc_20  =   1
      DefaultPlotPerRow_20=   -1  'True
      Axes_1          =   21
      ClassName_21    =   "CCWAxes"
      Array_21        =   2
      Editor_21       =   22
      ClassName_22    =   "CCWGFAxisArrayEditor"
      Owner_22        =   1
      Array[0]_21     =   6
      Array[1]_21     =   13
      DefaultPlot_1   =   23
      ClassName_23    =   "CCWDataPlot"
      opts_23         =   4194335
      Name_23         =   "[Template]"
      C[0]_23         =   65280
      C[1]_23         =   255
      C[2]_23         =   16711680
      C[3]_23         =   16776960
      Event_23        =   2
      X_23            =   6
      Y_23            =   13
      LineStyle_23    =   1
      LineWidth_23    =   1
      BasePlot_23     =   0
      DefaultXInc_23  =   1
      DefaultPlotPerRow_23=   -1  'True
      Cursors_1       =   24
      ClassName_24    =   "CCWCursors"
      Editor_24       =   25
      ClassName_25    =   "CCWGFCursorArrayEditor"
      Owner_25        =   1
      TrackMode_1     =   2
      GraphBackground_1=   0
      GraphFrame_1    =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   30
      Image_26        =   27
      ClassName_27    =   "CCWPictImage"
      opts_27         =   1280
      Rows_27         =   1
      Cols_27         =   1
      F_27            =   -2147483633
      B_27            =   -2147483633
      ColorReplaceWith_27=   8421504
      ColorReplace_27 =   8421504
      Tolerance_27    =   2
      Animator_26     =   0
      Blinker_26      =   0
      PlotFrame_1     =   28
      ClassName_28    =   "CCWDrawObj"
      opts_28         =   30
      C[1]_28         =   0
      Image_28        =   29
      ClassName_29    =   "CCWPictImage"
      opts_29         =   1280
      Rows_29         =   1
      Cols_29         =   1
      Pict_29         =   1
      F_29            =   -2147483633
      B_29            =   0
      ColorReplaceWith_29=   8421504
      ColorReplace_29 =   8421504
      Tolerance_29    =   2
      Animator_28     =   0
      Blinker_28      =   0
      Caption_1       =   30
      ClassName_30    =   "CCWDrawObj"
      opts_30         =   30
      C[0]_30         =   -2147483640
      Image_30        =   31
      ClassName_31    =   "CCWTextImage"
      style_31        =   36914383
      font_31         =   0
      Animator_30     =   0
      Blinker_30      =   0
      DefaultXInc_1   =   1
      DefaultPlotPerRow_1=   -1  'True
      Bindings_1      =   32
      ClassName_32    =   "CCWBindingHolderArray"
      Editor_32       =   33
      ClassName_33    =   "CCWBindingHolderArrayEditor"
      Owner_33        =   1
   End
   Begin CWUIControlsLib.CWGraph CWGraph2 
      Height          =   1935
      Left            =   120
      TabIndex        =   1
      Top             =   2160
      Width           =   3375
      _Version        =   196609
      _ExtentX        =   5953
      _ExtentY        =   3413
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
      rMin_8          =   33
      rMax_8          =   214
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
      Format_14       =   """ s"""
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   102
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
      major_13        =   5
      minor_13        =   2.5
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
      style_30        =   36914383
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
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   1935
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3375
      _Version        =   196609
      _ExtentX        =   5953
      _ExtentY        =   3413
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
      rMin_8          =   35
      rMax_8          =   214
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
      Format_14       =   """ V"""
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   102
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
      major_13        =   5
      minor_13        =   2.5
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
      style_30        =   36914383
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
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   4080
      Top             =   960
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWPulse_0       =   1
      ClassName_1     =   "CCWPulse"
      opts_1          =   2
      Counter_1       =   0
      GateMode_1      =   1
      GateSource_1    =   9
      PulseType_1     =   3
      Frequency_1     =   1000
      Frequency2_1    =   10000
   End
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   3600
      Top             =   480
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWCounter_0     =   1
      ClassName_1     =   "CCWCounter"
      opts_1          =   2
      GateMode_1      =   4
      GateSource_1    =   4
      Timebase_1      =   1.00000e5
      InternalClockMode_1=   8995
      MeasurementType_1=   1
      NMeasurements_1 =   100
      Buffering_1     =   -1  'True
   End
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   4080
      Top             =   480
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
      TotalScansToAcquire_1=   100
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      ClockType_2     =   1
      Frequency_2     =   100
      Period_2        =   0.01
      ClockSourceType_2=   8
      ClockSourceSignal_2=   "0"
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      ClockType_3     =   2
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
      Source_8        =   "1"
      Level_8         =   0.5
      Hysteresis_8    =   0.05
      PreTriggerScans_8=   3
      PauseCond_1     =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   2
      TrigPauseMode_9 =   7
      PreTriggerScans_9=   3
      StopCond_1      =   10
      ClassName_10    =   "CCWAICondition"
      WhichCondition_10=   3
      PreTriggerScans_10=   3
      HoldoffClock_1  =   11
      ClassName_11    =   "CCWAIClock"
      ClockType_11    =   3
      Frequency_11    =   100
      Period_11       =   0.01
      InternalClockMode_11=   1
   End
   Begin VB.Label Label11 
      Caption         =   "Device:"
      Height          =   255
      Left            =   4800
      TabIndex        =   22
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label12 
      Caption         =   $"RateChangeOnTheFly.frx":0000
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   19
      Top             =   6240
      Visible         =   0   'False
      Width           =   5865
   End
   Begin VB.Label Label10 
      Caption         =   "Signal Connections"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3600
      TabIndex        =   18
      Top             =   4920
      Width           =   1815
   End
   Begin VB.Label Label9 
      Caption         =   "External Connections - connect analog signal to PFI0"
      Height          =   495
      Left            =   4080
      TabIndex        =   17
      Top             =   5760
      Width           =   2175
   End
   Begin VB.Label Label5 
      Caption         =   "Demo Box Connection - may not work on every acquisition"
      Height          =   615
      Left            =   4080
      TabIndex        =   16
      Top             =   5160
      Width           =   2175
   End
   Begin VB.Label Label8 
      Caption         =   "Rate below limit:"
      Height          =   255
      Left            =   4860
      TabIndex        =   13
      Top             =   1620
      Width           =   1215
   End
   Begin VB.Label Label7 
      Caption         =   "Rate above limit:"
      Height          =   255
      Left            =   4800
      TabIndex        =   12
      Top             =   2340
      Width           =   1215
   End
   Begin VB.Label Label6 
      Caption         =   "Number of samples:"
      Height          =   255
      Left            =   4800
      TabIndex        =   11
      Top             =   3060
      Width           =   1455
   End
   Begin VB.Label Label4 
      Caption         =   "Threshold:"
      Height          =   255
      Left            =   4800
      TabIndex        =   10
      Top             =   900
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "Time Data"
      Height          =   255
      Left            =   3600
      TabIndex        =   6
      Top             =   2160
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "Time Waveform"
      Height          =   495
      Left            =   3600
      TabIndex        =   5
      Top             =   4200
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Voltage Data"
      Height          =   255
      Left            =   3600
      TabIndex        =   4
      Top             =   120
      Width           =   975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim ydata As Variant
Dim xdata As Variant
Dim CounterDone As Boolean
Dim AIDone As Boolean


Private Sub Start_Click()
   
   'flags to indicate each operation has completed.  Only graph when both are true
    CounterDone = False
    AIDone = False
    
    CWAI1.Device = DeviceNumEdit.Value
    CWCounter1.Device = DeviceNumEdit.Value
    CWPulse1.Device = DeviceNumEdit.Value
    
    CWAI1.NScans = numSamples
    CWCounter1.NMeasurements = numSamples
    CWPulse1.Frequency = RateBelow
    CWPulse1.Frequency2 = RateAbove
    
    CWDAQTools1.ResetDAQDevice DeviceNumEdit.Value
    
    If ModeSelect = False Then
        ' proper use of rate change on the fly
        ' requires external connection of analog signal to
        ' AI channel and PFI0
        CWAI1.StartCondition.Type = cwaiNoActiveCondition
        
        Dim ActualLevel, ActualHysteresis 'Return values for ConfigureATCOut, but not used in program
        CWDAQTools1.ConfigureATCOut DeviceNumEdit.Value, True, cwdaqRising, VoltageThreshold, 0.05, "PFI0", ActualLevel, ActualHysteresis
    Else
        ' work around solution for demo box
        ' connect analog signal to AI channel only
        ' this does not work properly for every acquisition
        CWAI1.StartCondition.Type = cwaiHWAnalog
        CWAI1.StartCondition.Level = VoltageThreshold
    End If
    
    CWAI1.Configure
    CWCounter1.Configure
    CWPulse1.Configure
    
    CWAI1.Start
   
    ' add delay in demo box case to allow AI operation
    ' to trigger before Pulse start
    If ModeSelect = True Then
        Sleep (100)
    End If
    
    CWCounter1.Start
    CWPulse1.Start
End Sub

Private Sub CWAI1_AcquiredData(Voltages As Variant, BinaryCodes As Variant)
    ydata = CWArray1.CopyArray(Voltages)
    AIDone = True
    If CounterDone Then DisplayData
End Sub

Private Sub CWCounter1_AcquiredData(Measurement As Variant, ByVal Overflow As Boolean)
    xdata = CWArray1.CopyArray(Measurement)
    xdata = CWArray1.LinEvArray(xdata, 1, -xdata(0))
    CounterDone = True
    If AIDone Then DisplayData
End Sub

Private Sub DisplayData()
    Dim x(1), y(1)

    CWGraph1.PlotY ydata
    CWGraph2.PlotY xdata
    CWGraph3.PlotXvsY xdata, ydata
    CWGraph3.Axes(1).Maximum = xdata(CWCounter1.NMeasurements - 1)
    'plot threshold on graph
    x(0) = 0
    x(1) = xdata(CWCounter1.NMeasurements - 1)
    y(0) = VoltageThreshold
    y(1) = VoltageThreshold
    CWGraph3.Plots(2).PlotXvsY x, y
    
    'reset controls
    CWPulse1.Reset
    CWCounter1.Reset
    CWAI1.Reset
End Sub

Private Sub CWAI1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

Private Sub CWAI1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Warning: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

