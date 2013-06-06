VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2340
   ClientLeft      =   1605
   ClientTop       =   1485
   ClientWidth     =   5490
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2340
   ScaleWidth      =   5490
   Begin VB.Frame Frame1 
      Caption         =   "Signal Input"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2040
      TabIndex        =   7
      Top             =   720
      Width           =   1455
      Begin VB.Label Label2 
         Caption         =   "Connect signal to counter source."
         Height          =   615
         Left            =   120
         TabIndex        =   8
         Top             =   240
         Width           =   1215
      End
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   1695
   End
   Begin VB.CommandButton Read 
      Caption         =   "Read Measurement (Events and Time)"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   1695
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1695
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   9
      Top             =   1320
      Width           =   1695
      _Version        =   65536
      _ExtentX        =   2990
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
      ContextID       =   15047
   End
   Begin CWUIControlsLib.CWSlide CWSlide1 
      Height          =   1455
      Left            =   3600
      TabIndex        =   5
      Top             =   240
      Width           =   1335
      _Version        =   196609
      _ExtentX        =   2355
      _ExtentY        =   2566
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
      SclRef_1.r      =   91
      SclRef_1.b      =   91
      Scl_1.l         =   2
      Scl_1.t         =   2
      Scl_1.r         =   82
      Scl_1.b         =   91
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
      rMax_14         =   86
      dMin_14         =   1
      dMax_14         =   4
      discInterval_14 =   1
      Radial_12       =   0
      Enum_12         =   15
      ClassName_15    =   "CCWEnum"
      Array_15        =   4
      Editor_15       =   16
      ClassName_16    =   "CCWEnumArrayEditor"
      Owner_16        =   12
      Array[0]_15     =   17
      ClassName_17    =   "CCWEnumElt"
      opts_17         =   1
      Name_17         =   "Count Events"
      DrawList_17     =   0
      varVarType_17   =   2
      Array[1]_15     =   18
      ClassName_18    =   "CCWEnumElt"
      opts_18         =   1
      Name_18         =   "Time"
      DrawList_18     =   0
      varVarType_18   =   2
      var_Val_18      =   1
      Array[2]_15     =   19
      ClassName_19    =   "CCWEnumElt"
      opts_19         =   1
      Name_19         =   "Period"
      DrawList_19     =   0
      varVarType_19   =   2
      var_Val_19      =   3
      Array[3]_15     =   20
      ClassName_20    =   "CCWEnumElt"
      opts_20         =   1
      Name_20         =   "Pulse Width"
      DrawList_20     =   0
      varVarType_20   =   2
      var_Val_20      =   4
      Font_12         =   0
      tickopts_12     =   2718
      Caption_12      =   21
      ClassName_21    =   "CCWDrawObj"
      opts_21         =   30
      C[0]_21         =   -2147483640
      Image_21        =   22
      ClassName_22    =   "CCWTextImage"
      style_22        =   8205894
      font_22         =   0
      Animator_21     =   0
      Blinker_21      =   0
      DrawLst_1       =   23
      ClassName_23    =   "CDrawList"
      count_23        =   10
      list[10]_23     =   8
      list[9]_23      =   24
      ClassName_24    =   "CCWThumb"
      opts_24         =   23
      Name_24         =   "Pointer-1"
      SclRef_24.l     =   2
      SclRef_24.t     =   2
      SclRef_24.r     =   82
      SclRef_24.b     =   91
      Scl_24.l        =   70
      Scl_24.t        =   7
      Scl_24.r        =   84
      Scl_24.b        =   17
      C[0]_24         =   8388608
      C[1]_24         =   8388608
      C[2]_24         =   -2147483635
      Image_24        =   25
      ClassName_25    =   "CCWPictImage"
      opts_25         =   1280
      Rows_25         =   1
      Cols_25         =   1
      Pict_25         =   93
      F_25            =   8388608
      B_25            =   8388608
      ColorReplaceWith_25=   8421504
      ColorReplace_25 =   8421504
      Tolerance_25    =   2
      Animator_24     =   0
      Blinker_24      =   0
      style_24        =   2
      Value_24        =   1
      list[8]_23      =   12
      list[7]_23      =   6
      list[6]_23      =   11
      list[5]_23      =   4
      list[4]_23      =   26
      ClassName_26    =   "CCWDrawObj"
      opts_26         =   30
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
      IncDec_1        =   0
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
   Begin CWUIControlsLib.CWNumEdit CWNumEdit1 
      Height          =   255
      Left            =   2160
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
      opts_1          =   131102
      C[0]_1          =   16777215
      C[1]_1          =   -2147483640
      Mode_1          =   1
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
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
   Begin CWDAQControlsLib.CWCounter CWCounter1 
      Left            =   3600
      Top             =   1800
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      CWCounter_0     =   1
      ClassName_1     =   "CCWCounter"
      opts_1          =   2
      GateMode_1      =   1
      GateSource_1    =   1
      TBSource_1      =   0
      MeasurementType_1=   1
   End
   Begin VB.Label Label3 
      Caption         =   "Select the device and counter in the property pages of the Counter control. "
      Height          =   495
      Left            =   120
      TabIndex        =   6
      Top             =   1800
      Width           =   3255
   End
   Begin VB.Label Label1 
      Caption         =   "Measurement"
      Height          =   255
      Left            =   2160
      TabIndex        =   3
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
Dim IsRunning As Boolean

Private Sub CWCounter1_AcquiredData(Measurement As Variant, ByVal Overflow As Boolean)
    CWNumEdit1 = Measurement
    IsRunning = False
End Sub

Private Sub CWSlide1_PointerValueChanged(ByVal Pointer As Long, Value As Variant)
    Select Case Value
        Case 0
            Label2.Caption = "Connect signal to counter source."
            CWNumEdit1.FormatString = ""
        Case 1
            Label2.Caption = "No connection needed."
            CWNumEdit1.FormatString = ".0##"" s"""
        Case 3
            Label2.Caption = "Connect signal to counter gate."
            CWNumEdit1.FormatString = ".0# k""s"""
        Case 4
            Label2.Caption = "Connect signal to counter gate."
            CWNumEdit1.FormatString = ".0# k""s"""
    End Select
End Sub

Private Sub Read_Click()
    Dim data As Variant, Overflow As Boolean
    CWCounter1.ReadMeasurement data, Overflow
    CWNumEdit1 = data
End Sub

Private Sub Start_Click()
    On Error GoTo ErrHandler
    CWCounter1.Reset
    With CWCounter1
        Select Case CWSlide1
            Case 0
                .MeasurementType = cwctrEvents
                .TimebaseSource = cwctrNIDAQChoosesTB
            Case 1
                .MeasurementType = cwctrTime
                .TimebaseSource = cwctrFrequencyTB
                .TimebaseSignal = 100000
            Case 3
                .MeasurementType = cwctrPulsePeriodRisingEdge
                .TimebaseSource = cwctrNIDAQChoosesTB
            Case 4
                .MeasurementType = cwctrHiPulseWidth
                .TimebaseSource = cwctrNIDAQChoosesTB
        End Select
    End With
    CWCounter1.Configure
    CWCounter1.Start
    IsRunning = True
    Exit Sub
ErrHandler:
    MsgBox "DAQ Error:  " + Err.Description
End Sub

Private Sub Stop_Click()
    If IsRunning Then
        CWCounter1.Stop
    End If
End Sub
