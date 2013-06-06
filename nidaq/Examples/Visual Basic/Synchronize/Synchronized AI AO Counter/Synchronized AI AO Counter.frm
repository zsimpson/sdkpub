VERSION 5.00
Object = "{E7BC3920-33D4-11D0-8B73-0020AF31CEF9}#1.4#0"; "CWANALYSIS.OCX"
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Synchronized AI AO Counter"
   ClientHeight    =   7755
   ClientLeft      =   1425
   ClientTop       =   630
   ClientWidth     =   7650
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   7755
   ScaleWidth      =   7650
   Begin VB.CheckBox bnDelay 
      Caption         =   "Holdoff acquisition"
      Height          =   315
      Left            =   4920
      TabIndex        =   3
      Top             =   5760
      Width           =   2295
   End
   Begin VB.CheckBox bnRegenerate 
      Caption         =   "Allow Regeneration"
      Height          =   375
      Left            =   4920
      TabIndex        =   2
      Top             =   5280
      Value           =   1  'Checked
      Width           =   2415
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      HelpContextID   =   15162
      Left            =   6240
      TabIndex        =   15
      Top             =   7080
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
      ContextID       =   15162
   End
   Begin CWUIControlsLib.CWSlide ProgressSlide 
      Height          =   375
      Left            =   360
      TabIndex        =   14
      Top             =   4560
      Width           =   6975
      _Version        =   196609
      _ExtentX        =   12303
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.74
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
      opts_1          =   2110
      C[0]_1          =   -2147483643
      BGImg_1         =   2
      ClassName_2     =   "CCWDrawObj"
      opts_2          =   62
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
      style_1         =   7
      Label_1         =   6
      ClassName_6     =   "CCWDrawObj"
      opts_6          =   54
      SclRef_6.l      =   2
      SclRef_6.t      =   2
      SclRef_6.r      =   467
      SclRef_6.b      =   27
      Scl_6.l         =   216
      Scl_6.t         =   7
      Scl_6.r         =   242
      Scl_6.b         =   23
      C[0]_6          =   -2147483640
      Image_6         =   7
      ClassName_7     =   "CCWTextImage"
      font_7          =   0
      Animator_6      =   0
      Blinker_6       =   0
      Border_1        =   8
      ClassName_8     =   "CCWDrawObj"
      opts_8          =   54
      SclRef_8.l      =   2
      SclRef_8.t      =   2
      SclRef_8.r      =   467
      SclRef_8.b      =   27
      Scl_8.l         =   2
      Scl_8.t         =   2
      Scl_8.r         =   467
      Scl_8.b         =   27
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
      opts_10         =   60
      FillTok_1       =   11
      ClassName_11    =   "CCWGuiObject"
      opts_11         =   62
      Axis_1          =   12
      ClassName_12    =   "CCWAxis"
      opts_12         =   575
      Name_12         =   "Axis"
      Orientation_12  =   2560
      format_12       =   13
      ClassName_13    =   "CCWFormat"
      Scale_12        =   14
      ClassName_14    =   "CCWScale"
      opts_14         =   90112
      rMax_14         =   464
      dMax_14         =   10
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Font_12         =   0
      tickopts_12     =   2718
      major_12        =   2
      minor_12        =   1
      Caption_12      =   17
      ClassName_17    =   "CCWDrawObj"
      opts_17         =   62
      C[0]_17         =   -2147483640
      Image_17        =   18
      ClassName_18    =   "CCWTextImage"
      font_18         =   0
      Animator_17     =   0
      Blinker_17      =   0
      DrawLst_1       =   19
      ClassName_19    =   "CDrawList"
      count_19        =   10
      list[10]_19     =   8
      list[9]_19      =   20
      ClassName_20    =   "CCWThumb"
      opts_20         =   1048637
      Name_20         =   "Pointer-1"
      C[2]_20         =   -2147483635
      Image_20        =   21
      ClassName_21    =   "CCWPictImage"
      opts_21         =   1280
      Rows_21         =   1
      Cols_21         =   1
      Pict_21         =   286
      F_21            =   -2147483633
      B_21            =   -2147483633
      ColorReplaceWith_21=   8421504
      ColorReplace_21 =   8421504
      Tolerance_21    =   2
      Animator_20     =   0
      Blinker_20      =   0
      Value_20        =   6.46551724137931E-02
      FillStyle_20    =   1
      list[8]_19      =   12
      list[7]_19      =   6
      list[6]_19      =   11
      list[5]_19      =   4
      list[4]_19      =   22
      ClassName_22    =   "CCWDrawObj"
      opts_22         =   62
      C[0]_22         =   -2147483640
      Image_22        =   23
      ClassName_23    =   "CCWPictImage"
      opts_23         =   1280
      Rows_23         =   1
      Cols_23         =   1
      Pict_23         =   2
      B_23            =   -2147483633
      ColorReplaceWith_23=   8421504
      ColorReplace_23 =   8421504
      Tolerance_23    =   2
      Animator_22     =   0
      Blinker_22      =   0
      list[3]_19      =   24
      ClassName_24    =   "CCWDrawObj"
      opts_24         =   60
      Image_24        =   25
      ClassName_25    =   "CCWPictImage"
      opts_25         =   1280
      Rows_25         =   1
      Cols_25         =   1
      Pict_25         =   93
      F_25            =   -2147483633
      B_25            =   -2147483633
      ColorReplaceWith_25=   8421504
      ColorReplace_25 =   8421504
      Tolerance_25    =   2
      Animator_24     =   0
      Blinker_24      =   0
      list[2]_19      =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   60
      Image_26        =   27
      ClassName_27    =   "CCWPictImage"
      opts_27         =   1280
      Rows_27         =   1
      Cols_27         =   1
      Pict_27         =   94
      F_27            =   -2147483633
      B_27            =   -2147483633
      ColorReplaceWith_27=   8421504
      ColorReplace_27 =   8421504
      Tolerance_27    =   2
      Animator_26     =   0
      Blinker_26      =   0
      list[1]_19      =   2
      Ptrs_1          =   28
      ClassName_28    =   "CCWPointerArray"
      Array_28        =   1
      Editor_28       =   29
      ClassName_29    =   "CCWPointerArrayEditor"
      Owner_29        =   1
      Array[0]_28     =   20
      Bindings_1      =   30
      ClassName_30    =   "CCWBindingHolderArray"
      Editor_30       =   31
      ClassName_31    =   "CCWBindingHolderArrayEditor"
      Owner_31        =   1
      Stats_1         =   32
      ClassName_32    =   "CCWStats"
      doInc_1         =   26
      doDec_1         =   24
      doFrame_1       =   22
   End
   Begin CWUIControlsLib.CWNumEdit SecondsPerWfmNumEdit 
      Height          =   375
      Left            =   2400
      TabIndex        =   7
      Top             =   6120
      Width           =   1455
      _Version        =   196609
      _ExtentX        =   2566
      _ExtentY        =   661
      _StockProps     =   4
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
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   393246
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
      Value_Val_1     =   1
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
   Begin CWUIControlsLib.CWNumEdit NPointsPerWfmNumEdit 
      Height          =   375
      Left            =   2400
      TabIndex        =   4
      Top             =   5400
      Width           =   1455
      _Version        =   196609
      _ExtentX        =   2566
      _ExtentY        =   661
      _StockProps     =   4
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
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   393246
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
      Value_Val_1     =   2000
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
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   2400
      Top             =   7080
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   2880
      Top             =   7080
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
      GateMode_1      =   4
      GateSource_1    =   6
      PulseType_1     =   0
      InternalClockMode_1=   3
   End
   Begin CWUIControlsLib.CWButton CWButton1 
      Height          =   1575
      Left            =   480
      TabIndex        =   1
      Top             =   5760
      Width           =   1095
      _Version        =   196609
      _ExtentX        =   1931
      _ExtentY        =   2778
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
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
      szText_6        =   "Begin Test"
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
      style_8         =   1097168481
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
      style_10        =   1936876886
      font_10         =   0
      Animator_9      =   0
      Blinker_9       =   0
      list[1]_4       =   11
      ClassName_11    =   "CCWDrawObj"
      opts_11         =   30
      C[0]_11         =   255
      C[1]_11         =   255
      Image_11        =   12
      ClassName_12    =   "CCWPictImage"
      opts_12         =   1280
      Rows_12         =   1
      Cols_12         =   1
      Pict_12         =   58
      F_12            =   255
      B_12            =   255
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
      C[0]_18         =   65280
      C[1]_18         =   65280
      Image_18        =   19
      ClassName_19    =   "CCWPictImage"
      opts_19         =   1280
      Rows_19         =   1
      Cols_19         =   1
      Pict_19         =   57
      F_19            =   65280
      B_19            =   65280
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
   Begin CWAnalysisControlsLib.CWDSP CWDSP1 
      Left            =   3360
      Top             =   7080
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   4455
      Left            =   360
      TabIndex        =   0
      Top             =   120
      Width           =   6975
      _Version        =   196609
      _ExtentX        =   12303
      _ExtentY        =   7858
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
      rMin_8          =   22
      rMax_8          =   454
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
      major_6         =   1
      minor_6         =   0.5
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
      opts_13         =   543
      Name_13         =   "YAxis-1"
      Orientation_13  =   2067
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   270
      dMin_15         =   -5
      dMax_15         =   5
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
   Begin CWUIControlsLib.CWNumEdit nedDelay 
      Height          =   375
      Left            =   6600
      TabIndex        =   9
      Top             =   6120
      Width           =   735
      _Version        =   196609
      _ExtentX        =   1296
      _ExtentY        =   661
      _StockProps     =   4
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
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   393246
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
      Value_Val_1     =   1
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
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   4320
      Top             =   7080
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      opts_1          =   8
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   6000
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      Frequency_2     =   2000
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
      Type_8          =   1
      Source_8        =   "RTSI0"
      PauseCond_1     =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   2
      Source_9        =   "RTSI0"
      TrigPauseMode_9 =   7
      StopCond_1      =   10
      ClassName_10    =   "CCWAICondition"
      WhichCondition_10=   3
      ProgressReturnDataType_1=   1
      HoldoffClock_1  =   11
      ClassName_11    =   "CCWAIClock"
      Frequency_11    =   100
      Period_11       =   0.01
      InternalClockMode_11=   1
   End
   Begin CWDAQControlsLib.CWAO CWAO1 
      Left            =   3840
      Top             =   7080
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AOTask_0        =   1
      ClassName_1     =   "CCWAOTask"
      ErrorEventMask_1=   32768
      Device_1        =   1
      Iterations_1    =   3
      Interval_1      =   1000
      UpdateClock_1   =   2
      ClassName_2     =   "CCWAOClock"
      ClockType_2     =   1
      Frequency_2     =   2000
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
      UpdatesPerBuffer_7=   2000
      StartCond_1     =   8
      ClassName_8     =   "CCWAOCondition"
      WhichCondition_8=   1
      Type_8          =   1
      Source_8        =   "PFI0"
      Regeneration_1  =   0   'False
   End
   Begin CWUIControlsLib.CWNumEdit DeviceNumEdit 
      Height          =   375
      Left            =   1080
      TabIndex        =   11
      Top             =   5160
      Width           =   615
      _Version        =   196609
      _ExtentX        =   1085
      _ExtentY        =   661
      _StockProps     =   4
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
   Begin VB.Label Label7 
      Caption         =   "Device"
      Height          =   375
      Left            =   360
      TabIndex        =   13
      Top             =   5160
      Width           =   735
   End
   Begin VB.Label Label6 
      Caption         =   "Label6"
      Height          =   495
      Left            =   3360
      TabIndex        =   12
      Top             =   3600
      Width           =   1215
   End
   Begin VB.Label Label5 
      Caption         =   "Delay (seconds)"
      Height          =   255
      Left            =   5280
      TabIndex        =   10
      Top             =   6240
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "# Seconds per Waveform"
      Height          =   255
      Left            =   2400
      TabIndex        =   8
      Top             =   5880
      Width           =   2175
   End
   Begin VB.Label Label2 
      Caption         =   "# Points per Waveform"
      Height          =   255
      Left            =   2400
      TabIndex        =   6
      Top             =   5160
      Width           =   1935
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   495
      Left            =   3360
      TabIndex        =   5
      Top             =   3240
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const kNumWfmsPerBuf = 2
Dim m_vWfm1 As Variant, m_vWfm2 As Variant, m_vWfm3 As Variant

Private Sub CWButton1_ValueChanged(ByVal Value As Boolean)
    Dim lTotalNSeconds As Long
    
    CWDAQTools1.ResetDAQDevice DeviceNumEdit.Value
    CWAI1.Device = DeviceNumEdit.Value
    CWAO1.Device = DeviceNumEdit.Value
    CWPulse1.Device = DeviceNumEdit.Value
    
'If turning switch on
    If Value Then
             
'Configure waveform generation
        lTotalNSeconds = CWAO1.NIterations * kNumWfmsPerBuf * SecondsPerWfmNumEdit.Value
            
        m_vWfm1 = CWDSP1.SinePattern(NPointsPerWfmNumEdit.Value, 4.5, 0, 10)
        m_vWfm2 = CWDSP1.SinePattern(NPointsPerWfmNumEdit.Value, 3, 0, 4)
        m_vWfm3 = CWDSP1.SinePattern(NPointsPerWfmNumEdit.Value, 2, 0, 2)
            
        CWAO1.AllowRegeneration = (bnRegenerate = vbChecked)
        CWAO1.NUpdates = NPointsPerWfmNumEdit.Value * kNumWfmsPerBuf
        CWAO1.UpdateClock.Frequency = NPointsPerWfmNumEdit.Value / SecondsPerWfmNumEdit.Value
                
        'Route the AO Start Trigger signal to the RTSI 0 pin
        CWDAQTools1.RouteSignal CWAO1.Device, cwrsPinRTSI0, cwrsSourceAOStartTrigger
                
        CWAO1.Configure
        
        CWAO1.Write m_vWfm1
        CWAO1.Write m_vWfm2
        
'Configure acquisition
        CWAI1.NScans = 10000
        CWAI1.ScanClock.Frequency = CWAI1.NScans / lTotalNSeconds
        CWAI1.ProgressInterval = 1000
        ProgressSlide.Axis.Minimum = 0
        ProgressSlide.Axis.Maximum = CWAI1.NScans
        
        If bnDelay = vbChecked Then
            CWAI1.StartCondition.Source = "GPCTR0"  'Start acquisition after pulse has completed
        Else
            CWAI1.StartCondition.Source = "RTSI0"   'Start acquisition as soon as waveform starts
        End If
        
        CWAI1.Configure
        
'Configure graph so that the X-Axis displays the time value of the acquired point that is plotted
        With CWGraph1.Axes.Item("XAxis")
            .Maximum = CWAI1.NScans
            .FormatString = "*" & lTotalNSeconds / .Maximum & Chr(34) & " s" & Chr(34)
            .Ticks.MajorDivisions = lTotalNSeconds
        End With
                         
'Configure counter
        CWPulse1.PulseDelay = nedDelay.Value
        CWPulse1.Configure
        
'Start the acquisition
        CWPulse1.Start
        CWAI1.Start
        CWAO1.Start
        
    Else 'turning switch off
        CWAO1.Reset
        CWAI1.Reset
        CWPulse1.Reset
        ProgressSlide.Value = 0
        CWGraph1.ClearData

    End If
End Sub

Private Sub CWAI1_AcquiredData(Voltages As Variant, BinaryCodes As Variant)
    CWGraph1.PlotY Voltages
End Sub

Private Sub CWAI1_Progress(ScanCount As Variant, ScaledData As Variant, BinaryCodes As Variant)
    ProgressSlide.Value = ScanCount
End Sub

Private Sub CWAO1_Progress(UpdateCount As Variant)
    CWAO1.Write m_vWfm3
    'Debug.Print "Scans generated: " & UpdateCount
End Sub

Private Sub CWAO1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    ErrorDialog "AO error", StatusCode, ContextDescription
End Sub

Private Sub CWAO1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    ErrorDialog "AO warning", StatusCode, ContextDescription
End Sub

Private Sub CWAI1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    ErrorDialog "AI error", StatusCode, ContextDescription
End Sub

Private Sub CWAI1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    ErrorDialog "AI warning", StatusCode, ContextDescription
End Sub

Private Sub CWPulse1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    ErrorDialog "Pulse error", StatusCode, ContextDescription
End Sub

Private Sub CWPulse1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    ErrorDialog "Pulse warning", StatusCode, ContextDescription
End Sub

Private Sub ErrorDialog(MsgPrefix As String, ByVal StatusCode As Long, ByVal ContextDescription As String)
    MsgBox MsgPrefix & " " & StatusCode & vbCrLf & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

