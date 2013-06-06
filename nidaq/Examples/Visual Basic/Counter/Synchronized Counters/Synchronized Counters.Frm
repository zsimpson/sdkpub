VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Synchronized Counters"
   ClientHeight    =   2700
   ClientLeft      =   1935
   ClientTop       =   1515
   ClientWidth     =   3645
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2700
   ScaleWidth      =   3645
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   120
      TabIndex        =   8
      Top             =   1920
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
      ContextID       =   15086
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   3000
      Top             =   2040
   End
   Begin VB.CommandButton StartCounter 
      Caption         =   "Start Counter"
      Height          =   495
      Left            =   2280
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton ConfigurePulse 
      Caption         =   "Configure Pulse"
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton ReadCounter 
      Caption         =   "Read Counter"
      Height          =   495
      Left            =   2280
      TabIndex        =   3
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   2280
      TabIndex        =   2
      Text            =   "0"
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton StopPulse 
      Caption         =   "Stop Pulse"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   1095
   End
   Begin VB.CommandButton StartPulse 
      Caption         =   "Start Pulse"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   720
      Width           =   1095
   End
   Begin CWUIControlsLib.CWSlide Frequency 
      Height          =   1695
      Left            =   1320
      TabIndex        =   6
      Top             =   120
      Width           =   615
      _Version        =   196609
      _ExtentX        =   1085
      _ExtentY        =   2990
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
      opts_12         =   543
      Name_12         =   "Axis"
      Orientation_12  =   2451
      format_12       =   13
      ClassName_13    =   "CCWFormat"
      Scale_12        =   14
      ClassName_14    =   "CCWScale"
      opts_14         =   126976
      rMin_14         =   10
      rMax_14         =   102
      dMin_14         =   1
      dMax_14         =   100
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Font_12         =   0
      tickopts_12     =   1694
      major_12        =   2
      minor_12        =   9
      Caption_12      =   17
      ClassName_17    =   "CCWDrawObj"
      opts_17         =   30
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
      opts_20         =   31
      Name_20         =   "Pointer-1"
      C[2]_20         =   -2147483635
      Image_20        =   21
      ClassName_21    =   "CCWPictImage"
      opts_21         =   1280
      Rows_21         =   1
      Cols_21         =   1
      Pict_21         =   213
      F_21            =   -2147483633
      B_21            =   -2147483633
      ColorReplaceWith_21=   8421504
      ColorReplace_21 =   8421504
      Tolerance_21    =   2
      Animator_20     =   0
      Blinker_20      =   0
      style_20        =   1
      Value_20        =   1
      FillStyle_20    =   1
      list[8]_19      =   12
      list[7]_19      =   6
      list[6]_19      =   11
      list[5]_19      =   4
      list[4]_19      =   22
      ClassName_22    =   "CCWDrawObj"
      opts_22         =   30
      Image_22        =   23
      ClassName_23    =   "CCWPictImage"
      opts_23         =   1280
      Rows_23         =   1
      Cols_23         =   1
      Pict_23         =   7
      F_23            =   -2147483633
      B_23            =   -2147483633
      ColorReplaceWith_23=   8421504
      ColorReplace_23 =   8421504
      Tolerance_23    =   2
      Animator_22     =   0
      Blinker_22      =   0
      list[3]_19      =   24
      ClassName_24    =   "CCWDrawObj"
      opts_24         =   30
      Image_24        =   25
      ClassName_25    =   "CCWPictImage"
      opts_25         =   1280
      Rows_25         =   1
      Cols_25         =   1
      Pict_25         =   96
      F_25            =   -2147483633
      B_25            =   -2147483633
      ColorReplaceWith_25=   8421504
      ColorReplace_25 =   8421504
      Tolerance_25    =   2
      Animator_24     =   0
      Blinker_24      =   0
      list[2]_19      =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   30
      Image_26        =   27
      ClassName_27    =   "CCWPictImage"
      opts_27         =   1280
      Rows_27         =   1
      Cols_27         =   1
      Pict_27         =   95
      F_27            =   -2147483633
      B_27            =   -2147483633
      ColorReplaceWith_27=   8421504
      ColorReplace_27 =   8421504
      Tolerance_27    =   2
      Animator_26     =   0
      Blinker_26      =   0
      list[1]_19      =   2
      IncDec_1        =   0
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
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   2280
      Top             =   2040
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWCounter_0     =   1
      ClassName_1     =   "CCWCounter"
      opts_1          =   2
      Device_1        =   2
      GateMode_1      =   1
      GateSource_1    =   1
      TBSource_1      =   4
      Timebase_1      =   0
      InternalClockMode_1=   14915
   End
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   1680
      Top             =   2040
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWPulse_0       =   1
      ClassName_1     =   "CCWPulse"
      opts_1          =   2
      Device_1        =   2
      Counter_1       =   0
      GateMode_1      =   1
      GateSource_1    =   1
   End
   Begin VB.Label Label1 
      Caption         =   "Number of Pulses"
      Height          =   255
      Left            =   2280
      TabIndex        =   7
      Top             =   1320
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim Running As Boolean

Private Sub ConfigurePulse_Click()
    CWPulse1.Configure
End Sub

Private Sub StartPulse_Click()
    CWPulse1.Start
    Running = True
End Sub

Private Sub StopPulse_Click()
    CWPulse1.Stop
    Running = False
End Sub

Private Sub Frequency_PointerValueChanged(ByVal Pointer As Long, Value As Variant)
    CWPulse1.Frequency = Value
    If Running Then
        CWPulse1.Reconfigure
    Else
        CWPulse1.Configure
    End If
End Sub

Private Sub StartCounter_Click()
    CWCounter1.Configure
    CWCounter1.Start
    Timer1.Enabled = True
End Sub

Private Sub ReadCounter_Click()
    Dim CountValue As Long
    Dim Overflow As Boolean
    CWCounter1.ReadCounter CountValue, Overflow
    Text1 = CountValue
End Sub


Private Sub Timer1_Timer()
    ReadCounter_Click
End Sub
