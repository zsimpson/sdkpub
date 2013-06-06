VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1905
   ClientLeft      =   1605
   ClientTop       =   1485
   ClientWidth     =   5730
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1905
   ScaleWidth      =   5730
   Begin VB.CommandButton btnStop 
      Caption         =   "Stop"
      Enabled         =   0   'False
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1455
   End
   Begin VB.CommandButton btnStart 
      Caption         =   "Start"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   4200
      TabIndex        =   8
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
      ContextID       =   15052
   End
   Begin CWUIControlsLib.CWNumEdit CountVal 
      Height          =   255
      Left            =   2640
      TabIndex        =   4
      Top             =   360
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
      Value_Val_1     =   10
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMin_Val_1  =   1
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   100
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit FreqVal 
      Height          =   255
      Left            =   2640
      TabIndex        =   3
      Top             =   960
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
      Format_2        =   ".##"" Hz"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   10
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMin_Val_1  =   1
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   1000
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWSlide PulseMode 
      Height          =   975
      Left            =   3960
      TabIndex        =   1
      Top             =   240
      Width           =   1815
      _Version        =   196609
      _ExtentX        =   3201
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
      Slider_0        =   1
      ClassName_1     =   "CCWSlider"
      opts_1          =   2070
      SclRef_1.l      =   2
      SclRef_1.t      =   2
      SclRef_1.r      =   139
      SclRef_1.b      =   83
      Scl_1.l         =   2
      Scl_1.t         =   1
      Scl_1.r         =   139
      Scl_1.b         =   82
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
      style_1         =   2
      Label_1         =   6
      ClassName_6     =   "CCWDrawObj"
      opts_6          =   30
      C[0]_6          =   -2147483640
      Image_6         =   7
      ClassName_7     =   "CCWTextImage"
      style_7         =   36958126
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
      rMin_14         =   6
      rMax_14         =   56
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
      Name_17         =   "Continuous Pulse"
      DrawList_17     =   0
      varVarType_17   =   2
      Array[1]_15     =   18
      ClassName_18    =   "CCWEnumElt"
      opts_18         =   1
      Name_18         =   "Single Pulse"
      DrawList_18     =   0
      varVarType_18   =   2
      var_Val_18      =   1
      Array[2]_15     =   19
      ClassName_19    =   "CCWEnumElt"
      opts_19         =   1
      Name_19         =   "Finite Pulse Train"
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
      font_21         =   0
      Animator_20     =   0
      Blinker_20      =   0
      DrawLst_1       =   22
      ClassName_22    =   "CDrawList"
      count_22        =   10
      list[10]_22     =   8
      list[9]_22      =   23
      ClassName_23    =   "CCWThumb"
      opts_23         =   23
      Name_23         =   "Pointer-1"
      SclRef_23.t     =   1
      SclRef_23.r     =   121
      SclRef_23.b     =   82
      Scl_23.l        =   87
      Scl_23.t        =   67
      Scl_23.r        =   104
      Scl_23.b        =   81
      C[0]_23         =   8388608
      C[1]_23         =   8388608
      C[2]_23         =   -2147483635
      Image_23        =   24
      ClassName_24    =   "CCWPictImage"
      opts_24         =   1280
      Rows_24         =   1
      Cols_24         =   1
      Pict_24         =   93
      F_24            =   8388608
      B_24            =   8388608
      ColorReplaceWith_24=   8421504
      ColorReplace_24 =   8421504
      Tolerance_24    =   2
      Animator_23     =   0
      Blinker_23      =   0
      style_23        =   2
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
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   3240
      Top             =   1320
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWPulse_0       =   1
      ClassName_1     =   "CCWPulse"
      opts_1          =   2
      GateMode_1      =   1
      GateSource_1    =   1
   End
   Begin VB.Label Label3 
      Caption         =   "Select the device and counter in the property pages of the pulse control. "
      Height          =   495
      Left            =   120
      TabIndex        =   7
      Top             =   1320
      Width           =   2895
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Number of Pulses:"
      Height          =   375
      Left            =   1680
      TabIndex        =   6
      Top             =   240
      Width           =   855
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Frequency:"
      Height          =   255
      Left            =   1680
      TabIndex        =   5
      Top             =   960
      Width           =   855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim IsRunning As Boolean

Private Sub FreqVal_ValueChanged(Value As Variant, PreviousValue As Variant, ByVal OutOfRange As Boolean)
    CWPulse1.Frequency = FreqVal
    If IsRunning Then CWPulse1.Reconfigure
End Sub

Private Sub btnStart_Click()
    Select Case PulseMode
        Case 0
            CWPulse1.PulseType = cwpulseContinuous
        Case 1
            CWPulse1.PulseType = cwpulseSingle
        Case 2
            CWPulse1.PulseType = cwpulseFinite
    End Select
    CWPulse1.Frequency = FreqVal
    CWPulse1.Count = CountVal
    CWPulse1.Configure
    CWPulse1.Start
    If PulseMode = 0 Then
        IsRunning = True
        btnStop.Enabled = True
    Else
        IsRunning = False
        btnStop.Enabled = False
    End If
End Sub

Private Sub btnStop_Click()
    CWPulse1.Stop
    IsRunning = False
    btnStop.Enabled = False
End Sub
