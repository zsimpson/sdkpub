VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4185
   ClientLeft      =   1710
   ClientTop       =   1665
   ClientWidth     =   6165
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4185
   ScaleWidth      =   6165
   Begin VB.CommandButton Command2 
      Caption         =   "Reset Device"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   1440
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   360
      Width           =   2175
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   7
      Top             =   1200
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
      ContextID       =   15048
   End
   Begin CWUIControlsLib.CWNumEdit CWNumEdit1 
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   360
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
   Begin CWUIControlsLib.CWSlide CWSlide1 
      Height          =   3615
      Left            =   3000
      TabIndex        =   1
      Top             =   480
      Width           =   2535
      _Version        =   196609
      _ExtentX        =   4471
      _ExtentY        =   6376
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
      style_7         =   1701016175
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
      rMax_14         =   230
      dMin_14         =   1
      dMax_14         =   19
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Array_15        =   19
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Array[0]_15     =   17
      ClassName_17    =   "CCWEnumElt"
      opts_17         =   1
      Name_17         =   "NI-DAQ Version"
      DrawList_17     =   0
      varVarType_17   =   2
      Array[1]_15     =   18
      ClassName_18    =   "CCWEnumElt"
      opts_18         =   1
      Name_18         =   "Device Name"
      DrawList_18     =   0
      varVarType_18   =   2
      var_Val_18      =   1
      Array[2]_15     =   19
      ClassName_19    =   "CCWEnumElt"
      opts_19         =   1
      Name_19         =   "Device Type Code"
      DrawList_19     =   0
      varVarType_19   =   2
      var_Val_19      =   10
      Array[3]_15     =   20
      ClassName_20    =   "CCWEnumElt"
      opts_20         =   1
      Name_20         =   "Base Address"
      DrawList_20     =   0
      varVarType_20   =   2
      var_Val_20      =   2
      Array[4]_15     =   21
      ClassName_21    =   "CCWEnumElt"
      opts_21         =   1
      Name_21         =   "DMA A"
      DrawList_21     =   0
      varVarType_21   =   2
      var_Val_21      =   11
      Array[5]_15     =   22
      ClassName_22    =   "CCWEnumElt"
      opts_22         =   1
      Name_22         =   "DMA B"
      DrawList_22     =   0
      varVarType_22   =   2
      var_Val_22      =   12
      Array[6]_15     =   23
      ClassName_23    =   "CCWEnumElt"
      opts_23         =   1
      Name_23         =   "DMA C"
      DrawList_23     =   0
      varVarType_23   =   2
      var_Val_23      =   13
      Array[7]_15     =   24
      ClassName_24    =   "CCWEnumElt"
      opts_24         =   1
      Name_24         =   "IRQ A"
      DrawList_24     =   0
      varVarType_24   =   2
      var_Val_24      =   14
      Array[8]_15     =   25
      ClassName_25    =   "CCWEnumElt"
      opts_25         =   1
      Name_25         =   "IRQ B"
      DrawList_25     =   0
      varVarType_25   =   2
      var_Val_25      =   15
      Array[9]_15     =   26
      ClassName_26    =   "CCWEnumElt"
      opts_26         =   1
      Name_26         =   "AI Transfer Mode"
      DrawList_26     =   0
      varVarType_26   =   2
      var_Val_26      =   3
      Array[10]_15    =   27
      ClassName_27    =   "CCWEnumElt"
      opts_27         =   1
      Name_27         =   "AO Group1 Transfer Mode"
      DrawList_27     =   0
      varVarType_27   =   2
      var_Val_27      =   4
      Array[11]_15    =   28
      ClassName_28    =   "CCWEnumElt"
      opts_28         =   1
      Name_28         =   "AO Group2 Transfer Mode"
      DrawList_28     =   0
      varVarType_28   =   2
      var_Val_28      =   5
      Array[12]_15    =   29
      ClassName_29    =   "CCWEnumElt"
      opts_29         =   1
      Name_29         =   "GPCTR1 Transfer Mode"
      DrawList_29     =   0
      varVarType_29   =   2
      var_Val_29      =   6
      Array[13]_15    =   30
      ClassName_30    =   "CCWEnumElt"
      opts_30         =   1
      Name_30         =   "GPCTR2 Transfer Mode"
      DrawList_30     =   0
      varVarType_30   =   2
      var_Val_30      =   7
      Array[14]_15    =   31
      ClassName_31    =   "CCWEnumElt"
      opts_31         =   1
      Name_31         =   "DIO Group1 Transfer Mode"
      DrawList_31     =   0
      varVarType_31   =   2
      var_Val_31      =   8
      Array[15]_15    =   32
      ClassName_32    =   "CCWEnumElt"
      opts_32         =   1
      Name_32         =   "DIO Group2 Transfer Mode"
      DrawList_32     =   0
      varVarType_32   =   2
      var_Val_32      =   9
      Array[16]_15    =   33
      ClassName_33    =   "CCWEnumElt"
      opts_33         =   1
      Name_33         =   "LPT device Mode"
      DrawList_33     =   0
      varVarType_33   =   2
      var_Val_33      =   17
      Array[17]_15    =   34
      ClassName_34    =   "CCWEnumElt"
      opts_34         =   1
      Name_34         =   "DAQCard-700 Counter Source"
      DrawList_34     =   0
      varVarType_34   =   2
      var_Val_34      =   18
      Array[18]_15    =   35
      ClassName_35    =   "CCWEnumElt"
      opts_35         =   1
      Name_35         =   "IRQ Generation Mode"
      DrawList_35     =   0
      varVarType_35   =   2
      var_Val_35      =   19
      Font_12         =   0
      tickopts_12     =   2718
      Caption_12      =   36
      ClassName_36    =   "CCWDrawObj"
      opts_36         =   30
      C[0]_36         =   -2147483640
      Image_36        =   37
      ClassName_37    =   "CCWTextImage"
      font_37         =   0
      Animator_36     =   0
      Blinker_36      =   0
      DrawLst_1       =   38
      ClassName_38    =   "CDrawList"
      count_38        =   10
      list[10]_38     =   8
      list[9]_38      =   39
      ClassName_39    =   "CCWThumb"
      opts_39         =   31
      Name_39         =   "Pointer-1"
      C[0]_39         =   8388608
      C[1]_39         =   8388608
      C[2]_39         =   -2147483635
      Image_39        =   40
      ClassName_40    =   "CCWPictImage"
      opts_40         =   1280
      Rows_40         =   1
      Cols_40         =   1
      Pict_40         =   93
      F_40            =   8388608
      B_40            =   8388608
      ColorReplaceWith_40=   8421504
      ColorReplace_40 =   8421504
      Tolerance_40    =   2
      Animator_39     =   0
      Blinker_39      =   0
      style_39        =   2
      Value_39        =   1
      list[8]_38      =   12
      list[7]_38      =   6
      list[6]_38      =   11
      list[5]_38      =   4
      list[4]_38      =   41
      ClassName_41    =   "CCWDrawObj"
      opts_41         =   30
      Image_41        =   42
      ClassName_42    =   "CCWPictImage"
      opts_42         =   1280
      Rows_42         =   1
      Cols_42         =   1
      Pict_42         =   7
      F_42            =   -2147483633
      B_42            =   -2147483633
      ColorReplaceWith_42=   8421504
      ColorReplace_42 =   8421504
      Tolerance_42    =   2
      Animator_41     =   0
      Blinker_41      =   0
      list[3]_38      =   43
      ClassName_43    =   "CCWDrawObj"
      opts_43         =   30
      Image_43        =   44
      ClassName_44    =   "CCWPictImage"
      opts_44         =   1280
      Rows_44         =   1
      Cols_44         =   1
      Pict_44         =   96
      F_44            =   -2147483633
      B_44            =   -2147483633
      ColorReplaceWith_44=   8421504
      ColorReplace_44 =   8421504
      Tolerance_44    =   2
      Animator_43     =   0
      Blinker_43      =   0
      list[2]_38      =   45
      ClassName_45    =   "CCWDrawObj"
      opts_45         =   30
      Image_45        =   46
      ClassName_46    =   "CCWPictImage"
      opts_46         =   1280
      Rows_46         =   1
      Cols_46         =   1
      Pict_46         =   95
      F_46            =   -2147483633
      B_46            =   -2147483633
      ColorReplaceWith_46=   8421504
      ColorReplace_46 =   8421504
      Tolerance_46    =   2
      Animator_45     =   0
      Blinker_45      =   0
      list[1]_38      =   2
      IncDec_1        =   0
      Ptrs_1          =   47
      ClassName_47    =   "CCWPointerArray"
      Array_47        =   1
      Editor_47       =   48
      ClassName_48    =   "CCWPointerArrayEditor"
      Owner_48        =   1
      Array[0]_47     =   39
      Bindings_1      =   49
      ClassName_49    =   "CCWBindingHolderArray"
      Editor_49       =   50
      ClassName_50    =   "CCWBindingHolderArrayEditor"
      Owner_50        =   1
      Stats_1         =   51
      ClassName_51    =   "CCWStats"
      doInc_1         =   45
      doDec_1         =   43
      doFrame_1       =   41
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   1440
      Top             =   720
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin VB.Label Label3 
      Caption         =   "Information Type"
      Height          =   255
      Left            =   4320
      TabIndex        =   6
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Information"
      Height          =   255
      Left            =   1440
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Device"
      Height          =   255
      Left            =   120
      TabIndex        =   4
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

Private Sub Command2_Click()
    CWDAQTools1.ResetDAQDevice CWNumEdit1.Value
End Sub

Private Sub GetInformation()
    On Error GoTo ErrorHandler
    
    Dim info
    CWDAQTools1.GetDAQDeviceInfo CWNumEdit1.Value, CWSlide1.Value, info
    Text1 = info
    Exit Sub
    
ErrorHandler:
    MsgBox "DAQ Error: " + CWDAQTools1.GetErrorText(Err.Number)
End Sub

Private Sub CWNumEdit1_ValueChanged(Value As Variant, PreviousValue As Variant, ByVal OutOfRange As Boolean)
    GetInformation
End Sub

Private Sub CWSlide1_PointerValueChanged(ByVal Pointer As Long, Value As Variant)
    GetInformation
End Sub

Private Sub Form_Load()
    GetInformation
End Sub

