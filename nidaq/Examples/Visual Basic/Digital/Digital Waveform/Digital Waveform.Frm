VERSION 5.00
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{E7BC3920-33D4-11D0-8B73-0020AF31CEF9}#1.4#0"; "CWANALYSIS.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Digital Waveform Example"
   ClientHeight    =   7665
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   6750
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   7665
   ScaleWidth      =   6750
   Begin VB.CommandButton btnStop 
      Caption         =   "Stop"
      Height          =   495
      Left            =   4320
      TabIndex        =   17
      Top             =   7080
      Width           =   1095
   End
   Begin VB.CommandButton btnClearGraph 
      Caption         =   "Clear Graph"
      Height          =   495
      Left            =   120
      TabIndex        =   15
      Top             =   7080
      Width           =   1215
   End
   Begin VB.CommandButton btnReadAsync 
      Caption         =   "Read Async"
      Height          =   495
      Left            =   3720
      TabIndex        =   14
      Top             =   2760
      Width           =   1335
   End
   Begin VB.CommandButton btnWrite 
      Caption         =   "Write"
      Height          =   495
      Left            =   5280
      TabIndex        =   13
      Top             =   2760
      Width           =   1335
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   2160
      TabIndex        =   3
      Text            =   "0:1"
      Top             =   480
      Width           =   1335
   End
   Begin VB.CommandButton btnRead 
      Caption         =   "Read"
      Height          =   495
      Left            =   2160
      TabIndex        =   2
      Top             =   2760
      Width           =   1335
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   5520
      TabIndex        =   16
      Top             =   7080
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
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
      ContextID       =   15079
   End
   Begin CWDAQControlsLib.CWDO CWDO1 
      Left            =   720
      Top             =   1560
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      DO_0            =   1
      ClassName_1     =   "CCWDOTask"
      opts_1          =   33810
      ErrorEventMask_1=   511114
      Mode_1          =   1
      EventInterval_1 =   1000
      Clock_1         =   2
      ClassName_2     =   "CCWDioClock"
      Frequency_2     =   100
      Period_2        =   0.01
      TimebaseSource_2=   1
      ClockSourceType_2=   2
   End
   Begin CWUIControlsLib.CWButton cwSimulateData 
      Height          =   375
      Left            =   600
      TabIndex        =   11
      Top             =   3000
      Width           =   375
      _Version        =   196609
      _ExtentX        =   661
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
      opts_1          =   10814
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
      opts_5          =   8254
      C[0]_5          =   -2147483640
      C[1]_5          =   -2147483640
      Image_5         =   6
      ClassName_6     =   "CCWTextImage"
      style_6         =   -842150451
      font_6          =   0
      Animator_5      =   0
      Blinker_5       =   0
      list[3]_4       =   7
      ClassName_7     =   "CCWDrawObj"
      opts_7          =   8252
      C[0]_7          =   -2147483640
      C[1]_7          =   -2147483640
      Image_7         =   8
      ClassName_8     =   "CCWTextImage"
      style_8         =   -842150451
      font_8          =   0
      Animator_7      =   0
      Blinker_7       =   0
      list[2]_4       =   9
      ClassName_9     =   "CCWDrawObj"
      opts_9          =   8252
      C[0]_9          =   -2147483640
      C[1]_9          =   -2147483640
      Image_9         =   10
      ClassName_10    =   "CCWTextImage"
      style_10        =   -842150451
      font_10         =   0
      Animator_9      =   0
      Blinker_9       =   0
      list[1]_4       =   11
      ClassName_11    =   "CCWDrawObj"
      opts_11         =   8254
      Image_11        =   12
      ClassName_12    =   "CCWPictImage"
      opts_12         =   1280
      Rows_12         =   1
      Cols_12         =   1
      Pict_12         =   58
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
      opts_15         =   8254
      C[0]_15         =   -2147483640
      C[1]_15         =   -2147483640
      Image_15        =   6
      Animator_15     =   0
      Blinker_15      =   0
      list[3]_14      =   16
      ClassName_16    =   "CCWDrawObj"
      opts_16         =   8252
      C[0]_16         =   -2147483640
      C[1]_16         =   -2147483640
      Image_16        =   8
      Animator_16     =   0
      Blinker_16      =   0
      list[2]_14      =   17
      ClassName_17    =   "CCWDrawObj"
      opts_17         =   8252
      C[0]_17         =   -2147483640
      C[1]_17         =   -2147483640
      Image_17        =   10
      Animator_17     =   0
      Blinker_17      =   0
      list[1]_14      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   8254
      Image_18        =   19
      ClassName_19    =   "CCWPictImage"
      opts_19         =   1280
      Rows_19         =   1
      Cols_19         =   1
      Pict_19         =   57
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
      mechAction_1    =   1
      BGImg_1         =   22
      ClassName_22    =   "CCWDrawObj"
      opts_22         =   8254
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
      opts_24         =   8254
      Image_24        =   8
      Animator_24     =   0
      Blinker_24      =   0
      Array[5]_1      =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   8254
      Image_25        =   10
      Animator_25     =   0
      Blinker_25      =   0
      Label_1         =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   8254
      C[0]_26         =   -2147483640
      Image_26        =   6
      Animator_26     =   0
      Blinker_26      =   0
   End
   Begin CWAnalysisControlsLib.CWArray CWArray1 
      Left            =   1200
      Top             =   1560
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit3 
      Height          =   375
      Left            =   2160
      TabIndex        =   10
      Top             =   1680
      Width           =   1335
      _Version        =   196609
      _ExtentX        =   2355
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
      opts_1          =   401438
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
      RangeMin_Val_1  =   1
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   16
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit2 
      Height          =   375
      Left            =   4200
      TabIndex        =   8
      Top             =   1680
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
      opts_1          =   270366
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   "k""Hz"""
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
      RangeMin_Val_1  =   1
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   16
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWSlide CWSlide1 
      Height          =   855
      Left            =   4200
      TabIndex        =   6
      Top             =   120
      Width           =   1455
      _Version        =   196609
      _ExtentX        =   2566
      _ExtentY        =   1508
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
      opts_1          =   10302
      C[0]_1          =   -2147483643
      BGImg_1         =   2
      ClassName_2     =   "CCWDrawObj"
      opts_2          =   8254
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
      Label_1         =   6
      ClassName_6     =   "CCWDrawObj"
      opts_6          =   8254
      C[0]_6          =   -2147483640
      Image_6         =   7
      ClassName_7     =   "CCWTextImage"
      szText_7        =   "Handshake Source"
      style_7         =   -842150451
      font_7          =   0
      Animator_6      =   0
      Blinker_6       =   0
      Border_1        =   8
      ClassName_8     =   "CCWDrawObj"
      opts_8          =   8252
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
      opts_10         =   8252
      FillTok_1       =   11
      ClassName_11    =   "CCWGuiObject"
      opts_11         =   8254
      Axis_1          =   12
      ClassName_12    =   "CCWAxis"
      opts_12         =   9279
      Name_12         =   "Axis"
      Orientation_12  =   133244
      format_12       =   13
      ClassName_13    =   "CCWFormat"
      Scale_12        =   14
      ClassName_14    =   "CCWScale"
      opts_14         =   57344
      rMin_14         =   23
      rMax_14         =   46
      dMin_14         =   1
      dMax_14         =   2
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Array_15        =   2
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Array[0]_15     =   17
      ClassName_17    =   "CCWEnumElt"
      opts_17         =   1
      Name_17         =   "IO Connection"
      DrawList_17     =   0
      varVarType_17   =   5
      Array[1]_15     =   18
      ClassName_18    =   "CCWEnumElt"
      opts_18         =   1
      Name_18         =   "Internal Clock"
      DrawList_18     =   0
      varVarType_18   =   5
      Font_12         =   0
      tickopts_12     =   2718
      Caption_12      =   19
      ClassName_19    =   "CCWDrawObj"
      opts_19         =   8254
      C[0]_19         =   -2147483640
      Image_19        =   20
      ClassName_20    =   "CCWTextImage"
      style_20        =   -842150451
      font_20         =   0
      Animator_19     =   0
      Blinker_19      =   0
      DrawLst_1       =   21
      ClassName_21    =   "CDrawList"
      count_21        =   10
      list[10]_21     =   8
      list[9]_21      =   22
      ClassName_22    =   "CCWThumb"
      opts_22         =   1056831
      Name_22         =   "Pointer-1"
      C[2]_22         =   -2147483635
      Image_22        =   23
      ClassName_23    =   "CCWPictImage"
      opts_23         =   1280
      Rows_23         =   1
      Cols_23         =   1
      Pict_23         =   213
      F_23            =   -2147483633
      B_23            =   -2147483633
      ColorReplaceWith_23=   8421504
      ColorReplace_23 =   8421504
      Tolerance_23    =   2
      Animator_22     =   0
      Blinker_22      =   0
      style_22        =   1
      Value_22        =   1
      FillStyle_22    =   1
      list[8]_21      =   12
      list[7]_21      =   6
      list[6]_21      =   11
      list[5]_21      =   4
      list[4]_21      =   24
      ClassName_24    =   "CCWDrawObj"
      opts_24         =   8254
      Image_24        =   25
      ClassName_25    =   "CCWPictImage"
      opts_25         =   1280
      Rows_25         =   1
      Cols_25         =   1
      Pict_25         =   7
      F_25            =   -2147483633
      B_25            =   -2147483633
      ColorReplaceWith_25=   8421504
      ColorReplace_25 =   8421504
      Tolerance_25    =   2
      Animator_24     =   0
      Blinker_24      =   0
      list[3]_21      =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   8254
      Image_26        =   27
      ClassName_27    =   "CCWPictImage"
      opts_27         =   1280
      Rows_27         =   1
      Cols_27         =   1
      Pict_27         =   96
      F_27            =   -2147483633
      B_27            =   -2147483633
      ColorReplaceWith_27=   8421504
      ColorReplace_27 =   8421504
      Tolerance_27    =   2
      Animator_26     =   0
      Blinker_26      =   0
      list[2]_21      =   28
      ClassName_28    =   "CCWDrawObj"
      opts_28         =   8254
      Image_28        =   29
      ClassName_29    =   "CCWPictImage"
      opts_29         =   1280
      Rows_29         =   1
      Cols_29         =   1
      Pict_29         =   95
      F_29            =   -2147483633
      B_29            =   -2147483633
      ColorReplaceWith_29=   8421504
      ColorReplace_29 =   8421504
      Tolerance_29    =   2
      Animator_28     =   0
      Blinker_28      =   0
      list[1]_21      =   2
      Ptrs_1          =   30
      ClassName_30    =   "CCWPointerArray"
      Array_30        =   1
      Editor_30       =   31
      ClassName_31    =   "CCWPointerArrayEditor"
      Owner_31        =   1
      Array[0]_30     =   22
      Bindings_1      =   32
      ClassName_32    =   "CCWBindingHolderArray"
      Editor_32       =   33
      ClassName_33    =   "CCWBindingHolderArrayEditor"
      Owner_33        =   1
      Stats_1         =   34
      ClassName_34    =   "CCWStats"
      doInc_1         =   28
      doDec_1         =   26
      doFrame_1       =   24
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   3375
      Left            =   120
      TabIndex        =   5
      Top             =   3480
      Width           =   6495
      _Version        =   196609
      _ExtentX        =   11456
      _ExtentY        =   5953
      _StockProps     =   71
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      Graph_0         =   1
      ClassName_1     =   "CCWGraphFrame"
      opts_1          =   8254
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
      opts_5          =   4202559
      Name_5          =   "Plot-1"
      C[0]_5          =   65280
      C[1]_5          =   255
      C[2]_5          =   16711680
      C[3]_5          =   16776960
      Event_5         =   2
      X_5             =   6
      ClassName_6     =   "CCWAxis"
      opts_6          =   9791
      Name_6          =   "XAxis"
      Orientation_6   =   2944
      format_6        =   7
      ClassName_7     =   "CCWFormat"
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   38
      rMax_8          =   422
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
      opts_11         =   8254
      C[0]_11         =   -2147483640
      Image_11        =   12
      ClassName_12    =   "CCWTextImage"
      szText_12       =   "Pattern Number"
      style_12        =   -842150451
      font_12         =   0
      Animator_11     =   0
      Blinker_11      =   0
      Y_5             =   13
      ClassName_13    =   "CCWAxis"
      opts_13         =   9791
      Name_13         =   "YAxis-1"
      Orientation_13  =   2451
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   24
      rMax_15         =   185
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
      opts_18         =   8254
      C[0]_18         =   -2147483640
      Image_18        =   19
      ClassName_19    =   "CCWTextImage"
      szText_19       =   "Digital Line Number"
      style_19        =   -842150451
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
      opts_22         =   4202559
      Name_22         =   "[Template]"
      C[0]_22         =   65280
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
      opts_25         =   8254
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
      opts_27         =   8254
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
      opts_29         =   8254
      C[0]_29         =   -2147483640
      Image_29        =   30
      ClassName_30    =   "CCWTextImage"
      szText_30       =   "Waveform Data"
      style_30        =   -842150451
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
   Begin CWDAQControlsLib.CWDI CWDI1 
      Left            =   240
      Top             =   1560
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      DI_0            =   1
      ClassName_1     =   "CCWDITask"
      opts_1          =   36882
      ErrorEventMask_1=   511114
      Clock_1         =   2
      ClassName_2     =   "CCWDioClock"
      Frequency_2     =   1000
      Period_2        =   0.01
      TimebaseSource_2=   1
      ClockSourceType_2=   1
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit1 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Width           =   1335
      _Version        =   196609
      _ExtentX        =   2355
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
      opts_1          =   466974
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
   Begin VB.Label Label5 
      Caption         =   "Simulate Read Data"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   2640
      Width           =   1455
   End
   Begin VB.Shape Shape1 
      Height          =   2415
      Left            =   120
      Top             =   0
      Width           =   6495
   End
   Begin VB.Label Label4 
      Caption         =   "Number of Points:"
      Height          =   255
      Left            =   2160
      TabIndex        =   9
      Top             =   1320
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Internal Clock Frequency:"
      Enabled         =   0   'False
      Height          =   255
      Left            =   4200
      TabIndex        =   7
      Top             =   1320
      Width           =   2055
   End
   Begin VB.Label Label2 
      Caption         =   "Channel String:"
      Height          =   255
      Left            =   2160
      TabIndex        =   4
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Device:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Function BuildDIOData(cPoints As Long, cPorts As Long)
    ' build an array of random data
    ' The array will be of the form returned by a CWDI
    '  read or used for CWDO.Write
    Dim port, pattern, data
        
    If cPorts > 1 Then
        ' 2-d array (multiple DIO ports)
        ReDim data(0 To cPorts - 1, 1 To cPoints) As Byte
        For port = 0 To cPorts - 1
            For pattern = 1 To cPoints
                data(port, pattern) = Rnd * 255
            Next
        Next
    Else
        ' 1-d array (single dio port)
        ReDim data(1 To cPoints) As Byte
        For pattern = 1 To cPoints
            data(pattern) = Rnd * 255
        Next
    End If
    
    BuildDIOData = data
End Function

Private Sub btnClearGraph_Click()
    CWGraph1.ClearData
End Sub

Private Sub btnRead_Click()
    PerformRead False ' not async (synchronous)
End Sub

Private Sub btnReadAsync_Click()
    PerformRead True ' async
End Sub
Sub PerformRead(Async As Boolean)
    ' set properties into CWDI control
    CWDI1.Device = CWNumEdit1
    CWDI1.ChannelString = Text1.Text
    CWDI1.NPatterns = CWNumEdit3
    CWDI1.UpdateClock.Frequency = CWNumEdit2
    CWDI1.UpdateClock.ClockSourceType = IIf(CWSlide1.ValuePairIndex = 1, cwdioCSIOConnector, cwdioCSInternalClock)
    
    Dim data
    
    If Not cwSimulateData Then
        ' Reset the digital output control so we can configure
        '  the ports for input
        CWDO1.Reset
    
        ' configure the hardware for digital input
        CWDI1.Configure
        
        If Async Then
            ' start an asynchronous read
            ' An AcquiredData event will fire when the read
            '  has completed.
            CWDI1.Start
        Else
            ' synchronous read
            CWDI1.AcquireData data
        End If
    Else
        ' simulate data
        
        ' set a small number of patterns
        '  so the data will be easier to see on the graph
        CWDI1.NPatterns = 20
        
        ' build a random array of data
        ' 1 port
        data = BuildDIOData(CWDI1.NPatterns, 1)
        
    End If
    
    ' output what we read if we're doing a synchronous read
    If Not Async Then
        Beep
        PlotIndividualDigitalLines CWGraph1, data
    End If
End Sub

Private Sub btnStop_Click()
    CWDO1.Reset
    CWDI1.Reset
End Sub

Private Sub btnWrite_Click()
    ' set properties into CWDO control
    CWDO1.Device = CWNumEdit1
    CWDO1.ChannelString = Text1.Text
    CWDO1.NPatterns = CWNumEdit3
    CWDO1.UpdateClock.Frequency = CWNumEdit2
    CWDO1.UpdateClock.ClockSourceType = IIf(CWSlide1.ValuePairIndex = 1, cwdioCSIOConnector, cwdioCSInternalClock)
    
    Dim data
    
    ' Reset the digital input control so we can configure
    '  the ports for output
    CWDI1.Reset

    ' configure the hardware for digital output
    CWDO1.Configure
    
    ' build a random array of data
    ' 1 port
    data = BuildDIOData(CWDO1.NPatterns, CWDO1.NPorts)
    
    ' plot the data we're going to write
    PlotIndividualDigitalLines CWGraph1, data
    
    ' write the data to the CWDO control
    CWDO1.Write data
    
    ' start the output operation
    CWDO1.Start
End Sub



Private Sub CWDI1_AcquiredData(Waveform As Variant)
    ' this event is fired when the CWDI control has received som
    '  data
    Beep
    PlotIndividualDigitalLines CWGraph1, Waveform
    MsgBox "Asynchronous Read operation completed.", Title:="Digital Input"
End Sub
Private Sub CWDO1_Progress(PatternCount As Variant)
    ' this event is fired when the CWDO write operation is complete
    Beep
    MsgBox "Write operation completed.", Title:="Digital Output"
End Sub

Private Sub CWSlide1_PointerValueChanged(ByVal Pointer As Long, Value As Variant)
    Dim bInternalClock As Boolean
    bInternalClock = CWSlide1.ValuePairIndex > 1
    
    ' enable/disable the internal clock frequency numedit control
    '  depending on the clock source chosen
    CWNumEdit2.Enabled = bInternalClock
    Label3.Enabled = bInternalClock
End Sub
Sub PlotIndividualDigitalLines(oGraph As CWGraph, data As Variant)
    ' data can be either 1-d or 2-d
    ' for 2-d arrays, each row is a digital port and a column
    '  represents the patterns from a port
    Dim row As Long
    Dim bit As Long
    Dim bitValue As Long
    Dim pattern As Long
    Dim cRows As Long, cPatterns As Long
    Dim offset As Long
    Dim arrayDimSizes
    
    ' how many rows of data returned
    arrayDimSizes = CWArray1.arrayDimSizes(data)
    
    If CWArray1.ArrayDims(data) = 1 Then
        ' 1-d array
        cRows = 1
        
        ' how many patterns
        cPatterns = arrayDimSizes(0)
    Else
        ' 2-d array
        ' the first size is the number of rows
        cRows = arrayDimSizes(0)
    
        ' how many patterns
        cPatterns = arrayDimSizes(1)
    End If
    
    ReDim outputdata(0 To cRows * 8 - 1, 0 To cPatterns - 1)
    
    offset = 0
    
    Dim data2
    For row = 0 To cRows - 1
        If cRows > 1 Then
            ' pull out a single column of the array
            data2 = CWArray1.IndexArray(data, Array(row, Null))
        Else
            ' only one row
            data2 = data
        End If
        
        bitValue = 1
        
        For bit = 0 To 7
            For pattern = 0 To cPatterns - 1
                Dim thisBitValue
                thisBitValue = offset
                
                ' if this bit is true in this pattern, then add .5
                '  to thisBitValue
                If data2(pattern + LBound(data2)) And bitValue Then
                    thisBitValue = thisBitValue + 0.5
                End If
                
                ' thisBitValue will either be offset or offset + .5
                outputdata(row * 8 + bit, pattern) = thisBitValue
                
            Next
            
            ' powers of 2
            bitValue = bitValue * 2
            
            ' separate each bit trace by 2 on the y-axis
            offset = offset + 1
        Next
    Next
    
    oGraph.PlotY outputdata
End Sub


