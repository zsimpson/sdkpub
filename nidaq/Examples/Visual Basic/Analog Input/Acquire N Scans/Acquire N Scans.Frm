VERSION 5.00
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Acquire N Scans"
   ClientHeight    =   6810
   ClientLeft      =   6945
   ClientTop       =   2835
   ClientWidth     =   7410
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6810
   ScaleWidth      =   7410
   Begin VB.Frame Frame1 
      Caption         =   "Acquisition Settings"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3135
      Left            =   120
      TabIndex        =   4
      Top             =   3480
      Width           =   7095
      Begin VB.TextBox ChannelStringTextBox 
         Height          =   285
         Left            =   120
         TabIndex        =   16
         Text            =   "1"
         Top             =   1200
         Width           =   1215
      End
      Begin VB.TextBox TrigSourceStartCond 
         Height          =   285
         Left            =   4680
         TabIndex        =   12
         Top             =   1200
         Width           =   855
      End
      Begin VB.TextBox TrigSourceStopCond 
         Height          =   285
         Left            =   4680
         TabIndex        =   5
         Top             =   2640
         Width           =   855
      End
      Begin CWUIControlsLib.CWNumEdit NScansNumEdit 
         Height          =   285
         Left            =   120
         TabIndex        =   19
         Top             =   1800
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
         opts_3          =   65536
         dMax_3          =   10
         discInterval_3  =   1
         ValueVarType_1  =   5
         Value_Val_1     =   1000
         IncValueVarType_1=   5
         IncValue_Val_1  =   1000
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
      Begin CWUIControlsLib.CWNumEdit FrequencyNumEdit 
         Height          =   285
         Left            =   120
         TabIndex        =   18
         Top             =   2400
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
         Format_2        =   " k""Hz"""
         scale_1         =   3
         ClassName_3     =   "CCWScale"
         opts_3          =   65536
         dMax_3          =   10
         discInterval_3  =   1
         ValueVarType_1  =   5
         Value_Val_1     =   10000
         IncValueVarType_1=   5
         IncValue_Val_1  =   1000
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
      Begin CWUIControlsLib.CWNumEdit DeviceNumEdit 
         Height          =   285
         Left            =   120
         TabIndex        =   17
         Top             =   600
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
      Begin CWUIControlsLib.CWNumEdit TrigLevelStartCond 
         Height          =   255
         Left            =   6000
         TabIndex        =   15
         Top             =   1200
         Width           =   855
         _Version        =   196609
         _ExtentX        =   1508
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
         Value_Val_1     =   0.5
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
      Begin CWUIControlsLib.CWSlide StopCondSlide 
         Height          =   1095
         Left            =   1800
         TabIndex        =   11
         Top             =   1800
         Width           =   2655
         _Version        =   196609
         _ExtentX        =   4683
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
         opts_6          =   22
         SclRef_6.l      =   2
         SclRef_6.t      =   2
         SclRef_6.r      =   179
         SclRef_6.b      =   75
         Scl_6.l         =   2
         Scl_6.t         =   2
         Scl_6.r         =   86
         Scl_6.b         =   15
         C[0]_6          =   -2147483640
         Image_6         =   7
         ClassName_7     =   "CCWTextImage"
         szText_7        =   "Stop Condition"
         font_7          =   8
         ClassName_8     =   "CCWFont"
         bFont_8         =   -1  'True
         BeginProperty Font_8 {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Animator_6      =   0
         Blinker_6       =   0
         Border_1        =   9
         ClassName_9     =   "CCWDrawObj"
         opts_9          =   28
         Image_9         =   10
         ClassName_10    =   "CCWPictImage"
         opts_10         =   1280
         Rows_10         =   1
         Cols_10         =   1
         Pict_10         =   25
         F_10            =   -2147483633
         B_10            =   -2147483633
         ColorReplaceWith_10=   8421504
         ColorReplace_10 =   8421504
         Tolerance_10    =   2
         Animator_9      =   0
         Blinker_9       =   0
         FillBound_1     =   11
         ClassName_11    =   "CCWGuiObject"
         opts_11         =   28
         FillTok_1       =   12
         ClassName_12    =   "CCWGuiObject"
         opts_12         =   30
         Axis_1          =   13
         ClassName_13    =   "CCWAxis"
         opts_13         =   1047
         Name_13         =   "Axis"
         SclRef_13.l     =   2
         SclRef_13.t     =   15
         SclRef_13.r     =   211
         SclRef_13.b     =   75
         Scl_13.l        =   21
         Scl_13.t        =   26
         Scl_13.r        =   151
         Scl_13.b        =   66
         Orientation_13  =   131124
         format_13       =   14
         ClassName_14    =   "CCWFormat"
         Scale_13        =   15
         ClassName_15    =   "CCWScale"
         opts_15         =   24576
         rMin_15         =   24
         rMax_15         =   63
         dMin_15         =   1
         dMax_15         =   3
         discInterval_15 =   1
         Radial_13       =   0
         Enum_13         =   16
         ClassName_16    =   "CCWEnum"
         Array_16        =   3
         Editor_16       =   17
         ClassName_17    =   "CCWEnumArrayEditor"
         Owner_17        =   13
         Array[0]_16     =   18
         ClassName_18    =   "CCWEnumElt"
         opts_18         =   1
         Name_18         =   "All scans acquired"
         DrawList_18     =   0
         varVarType_18   =   2
         Array[1]_16     =   19
         ClassName_19    =   "CCWEnumElt"
         opts_19         =   1
         Name_19         =   "Continuous"
         DrawList_19     =   0
         varVarType_19   =   2
         var_Val_19      =   4
         Array[2]_16     =   20
         ClassName_20    =   "CCWEnumElt"
         opts_20         =   1
         Name_20         =   "Continuous with software trigger"
         DrawList_20     =   0
         varVarType_20   =   2
         var_Val_20      =   3
         Font_13         =   0
         tickopts_13     =   2718
         Caption_13      =   21
         ClassName_21    =   "CCWDrawObj"
         opts_21         =   30
         C[0]_21         =   -2147483640
         Image_21        =   22
         ClassName_22    =   "CCWTextImage"
         font_22         =   0
         Animator_21     =   0
         Blinker_21      =   0
         DrawLst_1       =   23
         ClassName_23    =   "CDrawList"
         count_23        =   10
         list[10]_23     =   9
         list[9]_23      =   24
         ClassName_24    =   "CCWThumb"
         opts_24         =   1048599
         Name_24         =   "Pointer-1"
         SclRef_24.l     =   2
         SclRef_24.t     =   15
         SclRef_24.r     =   179
         SclRef_24.b     =   75
         Scl_24.l        =   3
         Scl_24.t        =   41
         Scl_24.r        =   17
         Scl_24.b        =   51
         C[0]_24         =   16711680
         C[1]_24         =   16711680
         C[2]_24         =   -2147483635
         Image_24        =   25
         ClassName_25    =   "CCWPictImage"
         opts_25         =   1280
         Rows_25         =   1
         Cols_25         =   1
         Pict_25         =   94
         F_25            =   16711680
         B_25            =   16711680
         ColorReplaceWith_25=   8421504
         ColorReplace_25 =   8421504
         Tolerance_25    =   2
         Animator_24     =   0
         Blinker_24      =   0
         style_24        =   3
         Value_24        =   1
         list[8]_23      =   13
         list[7]_23      =   6
         list[6]_23      =   12
         list[5]_23      =   4
         list[4]_23      =   26
         ClassName_26    =   "CCWDrawObj"
         opts_26         =   20
         SclRef_26.l     =   2
         SclRef_26.t     =   15
         SclRef_26.r     =   211
         SclRef_26.b     =   75
         Scl_26.l        =   2
         Scl_26.t        =   25
         Scl_26.r        =   19
         Scl_26.b        =   65
         Image_26        =   27
         ClassName_27    =   "CCWPictImage"
         opts_27         =   1280
         Rows_27         =   1
         Cols_27         =   1
         Pict_27         =   7
         F_27            =   -2147483633
         B_27            =   -2147483633
         ColorReplaceWith_27=   8421504
         ColorReplace_27 =   8421504
         Tolerance_27    =   2
         Animator_26     =   0
         Blinker_26      =   0
         list[3]_23      =   28
         ClassName_28    =   "CCWDrawObj"
         opts_28         =   28
         Image_28        =   29
         ClassName_29    =   "CCWPictImage"
         opts_29         =   1280
         Rows_29         =   1
         Cols_29         =   1
         Pict_29         =   96
         F_29            =   -2147483633
         B_29            =   -2147483633
         ColorReplaceWith_29=   8421504
         ColorReplace_29 =   8421504
         Tolerance_29    =   2
         Animator_28     =   0
         Blinker_28      =   0
         list[2]_23      =   30
         ClassName_30    =   "CCWDrawObj"
         opts_30         =   28
         Image_30        =   31
         ClassName_31    =   "CCWPictImage"
         opts_31         =   1280
         Rows_31         =   1
         Cols_31         =   1
         Pict_31         =   95
         F_31            =   -2147483633
         B_31            =   -2147483633
         ColorReplaceWith_31=   8421504
         ColorReplace_31 =   8421504
         Tolerance_31    =   2
         Animator_30     =   0
         Blinker_30      =   0
         list[1]_23      =   2
         Ptrs_1          =   32
         ClassName_32    =   "CCWPointerArray"
         Array_32        =   1
         Editor_32       =   33
         ClassName_33    =   "CCWPointerArrayEditor"
         Owner_33        =   1
         Array[0]_32     =   24
         Bindings_1      =   34
         ClassName_34    =   "CCWBindingHolderArray"
         Editor_34       =   35
         ClassName_35    =   "CCWBindingHolderArrayEditor"
         Owner_35        =   1
         Stats_1         =   36
         ClassName_36    =   "CCWStats"
         doInc_1         =   30
         doDec_1         =   28
         doFrame_1       =   26
      End
      Begin CWUIControlsLib.CWSlide StartCondSlide 
         Height          =   1095
         Left            =   1800
         TabIndex        =   10
         Top             =   360
         Width           =   1395
         _Version        =   196609
         _ExtentX        =   2461
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
         opts_6          =   22
         SclRef_6.l      =   2
         SclRef_6.t      =   2
         SclRef_6.r      =   95
         SclRef_6.b      =   75
         Scl_6.l         =   1
         Scl_6.t         =   2
         Scl_6.r         =   86
         Scl_6.b         =   15
         C[0]_6          =   -2147483640
         Image_6         =   7
         ClassName_7     =   "CCWTextImage"
         szText_7        =   "Start Condition"
         font_7          =   8
         ClassName_8     =   "CCWFont"
         bFont_8         =   -1  'True
         BeginProperty Font_8 {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Animator_6      =   0
         Blinker_6       =   0
         Border_1        =   9
         ClassName_9     =   "CCWDrawObj"
         opts_9          =   28
         Image_9         =   10
         ClassName_10    =   "CCWPictImage"
         opts_10         =   1280
         Rows_10         =   1
         Cols_10         =   1
         Pict_10         =   25
         F_10            =   -2147483633
         B_10            =   -2147483633
         ColorReplaceWith_10=   8421504
         ColorReplace_10 =   8421504
         Tolerance_10    =   2
         Animator_9      =   0
         Blinker_9       =   0
         FillBound_1     =   11
         ClassName_11    =   "CCWGuiObject"
         opts_11         =   28
         FillTok_1       =   12
         ClassName_12    =   "CCWGuiObject"
         opts_12         =   30
         Axis_1          =   13
         ClassName_13    =   "CCWAxis"
         opts_13         =   1047
         Name_13         =   "Axis"
         SclRef_13.l     =   2
         SclRef_13.t     =   15
         SclRef_13.r     =   95
         SclRef_13.b     =   75
         Scl_13.l        =   21
         Scl_13.t        =   27
         Scl_13.r        =   79
         Scl_13.b        =   67
         Orientation_13  =   131124
         format_13       =   14
         ClassName_14    =   "CCWFormat"
         Scale_13        =   15
         ClassName_15    =   "CCWScale"
         opts_15         =   24576
         rMin_15         =   25
         rMax_15         =   64
         dMin_15         =   1
         dMax_15         =   3
         discInterval_15 =   1
         Radial_13       =   0
         Enum_13         =   16
         ClassName_16    =   "CCWEnum"
         Array_16        =   3
         Editor_16       =   17
         ClassName_17    =   "CCWEnumArrayEditor"
         Owner_17        =   13
         Array[0]_16     =   18
         ClassName_18    =   "CCWEnumElt"
         opts_18         =   1
         Name_18         =   "Immediate"
         DrawList_18     =   0
         varVarType_18   =   2
         Array[1]_16     =   19
         ClassName_19    =   "CCWEnumElt"
         opts_19         =   1
         Name_19         =   "Digital trigger"
         DrawList_19     =   0
         varVarType_19   =   2
         var_Val_19      =   1
         Array[2]_16     =   20
         ClassName_20    =   "CCWEnumElt"
         opts_20         =   1
         Name_20         =   "Analog trigger"
         DrawList_20     =   0
         varVarType_20   =   2
         var_Val_20      =   2
         Font_13         =   0
         tickopts_13     =   2718
         Caption_13      =   21
         ClassName_21    =   "CCWDrawObj"
         opts_21         =   30
         C[0]_21         =   -2147483640
         Image_21        =   22
         ClassName_22    =   "CCWTextImage"
         font_22         =   0
         Animator_21     =   0
         Blinker_21      =   0
         DrawLst_1       =   23
         ClassName_23    =   "CDrawList"
         count_23        =   10
         list[10]_23     =   9
         list[9]_23      =   24
         ClassName_24    =   "CCWThumb"
         opts_24         =   1048599
         Name_24         =   "Pointer-1"
         SclRef_24.l     =   2
         SclRef_24.t     =   15
         SclRef_24.r     =   95
         SclRef_24.b     =   75
         Scl_24.l        =   2
         Scl_24.t        =   59
         Scl_24.r        =   17
         Scl_24.b        =   69
         C[0]_24         =   16711680
         C[1]_24         =   16711680
         C[2]_24         =   -2147483635
         Image_24        =   25
         ClassName_25    =   "CCWPictImage"
         opts_25         =   1280
         Rows_25         =   1
         Cols_25         =   1
         Pict_25         =   94
         F_25            =   16711680
         B_25            =   16711680
         ColorReplaceWith_25=   8421504
         ColorReplace_25 =   8421504
         Tolerance_25    =   2
         Animator_24     =   0
         Blinker_24      =   0
         style_24        =   3
         Value_24        =   1
         list[8]_23      =   13
         list[7]_23      =   6
         list[6]_23      =   12
         list[5]_23      =   4
         list[4]_23      =   26
         ClassName_26    =   "CCWDrawObj"
         opts_26         =   20
         SclRef_26.l     =   2
         SclRef_26.t     =   15
         SclRef_26.r     =   95
         SclRef_26.b     =   75
         Scl_26.l        =   2
         Scl_26.t        =   25
         Scl_26.r        =   20
         Scl_26.b        =   65
         Image_26        =   27
         ClassName_27    =   "CCWPictImage"
         opts_27         =   1280
         Rows_27         =   1
         Cols_27         =   1
         Pict_27         =   7
         F_27            =   -2147483633
         B_27            =   -2147483633
         ColorReplaceWith_27=   8421504
         ColorReplace_27 =   8421504
         Tolerance_27    =   2
         Animator_26     =   0
         Blinker_26      =   0
         list[3]_23      =   28
         ClassName_28    =   "CCWDrawObj"
         opts_28         =   28
         Image_28        =   29
         ClassName_29    =   "CCWPictImage"
         opts_29         =   1280
         Rows_29         =   1
         Cols_29         =   1
         Pict_29         =   96
         F_29            =   -2147483633
         B_29            =   -2147483633
         ColorReplaceWith_29=   8421504
         ColorReplace_29 =   8421504
         Tolerance_29    =   2
         Animator_28     =   0
         Blinker_28      =   0
         list[2]_23      =   30
         ClassName_30    =   "CCWDrawObj"
         opts_30         =   28
         Image_30        =   31
         ClassName_31    =   "CCWPictImage"
         opts_31         =   1280
         Rows_31         =   1
         Cols_31         =   1
         Pict_31         =   95
         F_31            =   -2147483633
         B_31            =   -2147483633
         ColorReplaceWith_31=   8421504
         ColorReplace_31 =   8421504
         Tolerance_31    =   2
         Animator_30     =   0
         Blinker_30      =   0
         list[1]_23      =   2
         Ptrs_1          =   32
         ClassName_32    =   "CCWPointerArray"
         Array_32        =   1
         Editor_32       =   33
         ClassName_33    =   "CCWPointerArrayEditor"
         Owner_33        =   1
         Array[0]_32     =   24
         Bindings_1      =   34
         ClassName_34    =   "CCWBindingHolderArray"
         Editor_34       =   35
         ClassName_35    =   "CCWBindingHolderArrayEditor"
         Owner_35        =   1
         Stats_1         =   36
         ClassName_36    =   "CCWStats"
         doInc_1         =   30
         doDec_1         =   28
         doFrame_1       =   26
      End
      Begin CWUIControlsLib.CWNumEdit TrigLevelStopCond 
         Height          =   255
         Left            =   6000
         TabIndex        =   8
         Top             =   2640
         Width           =   855
         _Version        =   196609
         _ExtentX        =   1508
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
         Value_Val_1     =   0.5
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
      Begin VB.Label Label1 
         Caption         =   "Device:"
         Height          =   255
         Left            =   120
         TabIndex        =   23
         Top             =   360
         Width           =   975
      End
      Begin VB.Label Label2 
         Caption         =   "Channel string:"
         Height          =   255
         Left            =   120
         TabIndex        =   22
         Top             =   960
         Width           =   1335
      End
      Begin VB.Label Label3 
         Caption         =   "Number of scans:"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   1560
         Width           =   1575
      End
      Begin VB.Label Label4 
         Caption         =   "Frequency:"
         Height          =   255
         Left            =   120
         TabIndex        =   20
         Top             =   2160
         Width           =   975
      End
      Begin VB.Label Label6 
         Caption         =   "Trigger level"
         Height          =   255
         Left            =   6000
         TabIndex        =   14
         Top             =   960
         Width           =   975
      End
      Begin VB.Label Label5 
         Caption         =   "Trigger source"
         Height          =   255
         Left            =   4680
         TabIndex        =   13
         Top             =   960
         Width           =   1215
      End
      Begin VB.Label lblTSource 
         Caption         =   "Trigger source"
         Height          =   255
         Left            =   4680
         TabIndex        =   7
         Top             =   2400
         Width           =   1095
      End
      Begin VB.Label lblTLevel 
         Caption         =   "Trigger level"
         Height          =   255
         Left            =   6000
         TabIndex        =   6
         Top             =   2400
         Width           =   975
      End
   End
   Begin VB.CommandButton Quit 
      Caption         =   "Quit"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   1080
      Width           =   975
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   975
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   975
   End
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   120
      Top             =   2160
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      opts_1          =   18
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   100
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
      InternalClockMode_3=   1
      Buffer_1        =   4
      ClassName_4     =   "CCWAIBuffer"
      Channels_1      =   5
      ClassName_5     =   "CCWAIChannelArray"
      Editor_5        =   6
      ClassName_6     =   "CCWAIChannelsArrayEditor"
      Owner_6         =   1
      StartCond_1     =   7
      ClassName_7     =   "CCWAICondition"
      WhichCondition_7=   1
      PreTriggerScans_7=   3
      PauseCond_1     =   8
      ClassName_8     =   "CCWAICondition"
      WhichCondition_8=   2
      TrigPauseMode_8 =   7
      PreTriggerScans_8=   3
      StopCond_1      =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   3
      PreTriggerScans_9=   3
      HoldoffClock_1  =   10
      ClassName_10    =   "CCWAIClock"
      ClockType_10    =   3
      Frequency_10    =   100
      Period_10       =   0.01
      InternalClockMode_10=   1
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   9
      Top             =   1560
      Width           =   975
      _Version        =   65536
      _ExtentX        =   1720
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
      ContextID       =   15056
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   720
      Top             =   2160
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   3255
      Left            =   1560
      TabIndex        =   0
      Top             =   120
      Width           =   5655
      _Version        =   196609
      _ExtentX        =   9975
      _ExtentY        =   5741
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
      opts_6          =   1551
      Name_6          =   "X-Axis"
      C[0]_6          =   8
      C[1]_6          =   8
      C[2]_6          =   8
      C[4]_6          =   -2147483640
      Orientation_6   =   2944
      format_6        =   7
      ClassName_7     =   "CCWFormat"
      Scale_6         =   8
      ClassName_8     =   "CCWScale"
      opts_8          =   90112
      rMin_8          =   25
      rMax_8          =   366
      dMax_8          =   10
      discInterval_8  =   1
      Radial_6        =   0
      Enum_6          =   9
      ClassName_9     =   "CCWEnum"
      Editor_9        =   10
      ClassName_10    =   "CCWEnumArrayEditor"
      Owner_10        =   6
      Font_6          =   0
      tickopts_6      =   2071
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
      opts_13         =   1551
      Name_13         =   "Y-Axis"
      C[0]_13         =   8
      C[1]_13         =   8
      C[2]_13         =   8
      C[4]_13         =   -2147483640
      Orientation_13  =   2067
      format_13       =   14
      ClassName_14    =   "CCWFormat"
      Scale_13        =   15
      ClassName_15    =   "CCWScale"
      opts_15         =   122880
      rMin_15         =   11
      rMax_15         =   190
      dMax_15         =   10
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
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Start_Click()
    CWGraph1.ClearData
    
    CWAI1.Device = DeviceNumEdit.Value
    
    'Clear the channel list and add a new channel
    CWAI1.Channels.RemoveAll
    CWAI1.Channels.Add ChannelStringTextBox.Text
    
    'Specify the number of scans to acquire, or, in the case of a continuous acquisition,
    'the number of scans to return with each AcquiredData event.
    CWAI1.NScans = NScansNumEdit.Value
    
    'Specify the scan rate (i.e. # of scans to acquire per second)
    CWAI1.ScanClock.Frequency = FrequencyNumEdit.Value
    
    'Specify the start condition.
    'If "immediate" then the acquisition begins as soon as the Start method is called.
    'If Digital Trigger or Analog Trigger, then DAQ device waits for a trigger
    'after the Start method is called. When the trigger occurs, the acquisition begins.
    CWAI1.StartCondition.Type = StartCondSlide.Value
    CWAI1.StartCondition.Level = TrigLevelStartCond.Value
    
    'For E Series boards, you can specify a PFI line, RTSI line, or the GPCTR0 signal as the trigger.
    'For all other boards, the trigger signal is fixed. Leave the TrigSourceStartCond text box blank.
    'For more information, place your cursor on "Source" in the next line, and press F1.
    CWAI1.StartCondition.Source = TrigSourceStartCond.Text
    
    'Specify the stop condition
    'If "Continuous", then the acquisition doesn't stop until the user presses the Stop button.
    'If "Continuous with software trigger", then the acquisition returns data every time the
    'the trigger conditions are met. The acquisition continues until the user presses the Stop button.
    CWAI1.StopCondition.Type = StopCondSlide.Value
    CWAI1.StopCondition.Level = TrigLevelStopCond.Value
    
    'The trigger source for a Continuous Software trigger
    'must be one of the channels that you specified in the channel string.
    CWAI1.StopCondition.Source = TrigSourceStopCond.Text
    
    'Configure the DAQ device and begin the acquisition
    CWAI1.Configure
    CWAI1.Start
End Sub

Private Sub CWAI1_AcquiredData(ScaledData As Variant, BinaryCodes As Variant)
    CWGraph1.PlotY ScaledData
End Sub

Private Sub Stop_Click()
    CWAI1.Stop
End Sub

Private Sub Quit_Click()
    End
End Sub

Private Sub CWAI1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

Private Sub CWAI1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Warning: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub


