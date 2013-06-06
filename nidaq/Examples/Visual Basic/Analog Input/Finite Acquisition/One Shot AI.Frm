VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form AI1 
   Caption         =   "One Shot Analog Input"
   ClientHeight    =   3975
   ClientLeft      =   1470
   ClientTop       =   1425
   ClientWidth     =   6495
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3975
   ScaleWidth      =   6495
   Begin VB.TextBox ChannelStringTextBox 
      Height          =   285
      Left            =   1800
      TabIndex        =   5
      Text            =   "1"
      Top             =   3600
      Width           =   1215
   End
   Begin VB.CommandButton Quit 
      Caption         =   "Quit"
      Height          =   495
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   495
      Left            =   240
      TabIndex        =   1
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton Configure 
      Caption         =   "Configure"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Width           =   1215
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   2280
      Top             =   0
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   1800
      Top             =   0
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
      TotalScansToAcquire_1=   1000
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      ClockType_2     =   1
      Frequency_2     =   10000
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
      Editor_5        =   6
      ClassName_6     =   "CCWAIChannelsArrayEditor"
      Owner_6         =   1
      StartCond_1     =   7
      ClassName_7     =   "CCWAICondition"
      WhichCondition_7=   1
      PauseCond_1     =   8
      ClassName_8     =   "CCWAICondition"
      WhichCondition_8=   2
      TrigPauseMode_8 =   7
      StopCond_1      =   9
      ClassName_9     =   "CCWAICondition"
      WhichCondition_9=   3
      HoldoffClock_1  =   10
      ClassName_10    =   "CCWAIClock"
      ClockType_10    =   3
      Frequency_10    =   100
      Period_10       =   0.01
      InternalClockMode_10=   1
   End
   Begin CWUIControlsLib.CWNumEdit DeviceNumEdit 
      Height          =   285
      Left            =   240
      TabIndex        =   12
      Top             =   3600
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
   Begin CWUIControlsLib.CWNumEdit FrequencyNumEdit 
      Height          =   285
      Left            =   5040
      TabIndex        =   11
      Top             =   3600
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
   Begin CWUIControlsLib.CWNumEdit NScansNumEdit 
      Height          =   285
      Left            =   3480
      TabIndex        =   10
      Top             =   3600
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
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   240
      TabIndex        =   4
      Top             =   2040
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
      ContextID       =   15060
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   2655
      Left            =   1800
      TabIndex        =   3
      Top             =   480
      Width           =   4455
      _Version        =   196609
      _ExtentX        =   7858
      _ExtentY        =   4683
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
      Array_3         =   1
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
      rMin_8          =   28
      rMax_8          =   286
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
      opts_11         =   8254
      C[0]_11         =   -2147483640
      Image_11        =   12
      ClassName_12    =   "CCWTextImage"
      style_12        =   590246714
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
      rMax_15         =   150
      dMin_15         =   -10
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
      major_13        =   5
      minor_13        =   2.5
      Caption_13      =   18
      ClassName_18    =   "CCWDrawObj"
      opts_18         =   8254
      C[0]_18         =   -2147483640
      Image_18        =   19
      ClassName_19    =   "CCWTextImage"
      style_19        =   590246714
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
      opts_22         =   4194319
      Name_22         =   "Template"
      C[0]_22         =   16777215
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
      Cursors_1       =   23
      ClassName_23    =   "CCWCursors"
      Editor_23       =   24
      ClassName_24    =   "CCWGFCursorArrayEditor"
      Owner_24        =   1
      TrackMode_1     =   2
      GraphBackground_1=   0
      GraphFrame_1    =   25
      ClassName_25    =   "CCWDrawObj"
      opts_25         =   14
      Image_25        =   26
      ClassName_26    =   "CCWPictImage"
      opts_26         =   1024
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
      opts_27         =   14
      Image_27        =   28
      ClassName_28    =   "CCWPictImage"
      opts_28         =   1024
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
   Begin VB.Label Label9 
      Caption         =   "Frequency:"
      Height          =   255
      Left            =   5040
      TabIndex        =   9
      Top             =   3360
      Width           =   975
   End
   Begin VB.Label Label8 
      Caption         =   "Number of scans:"
      Height          =   255
      Left            =   3360
      TabIndex        =   8
      Top             =   3360
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Channel string:"
      Height          =   255
      Left            =   1800
      TabIndex        =   7
      Top             =   3360
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Device:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   3360
      Width           =   975
   End
End
Attribute VB_Name = "AI1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Configure_Click()
    CWAI1.Device = DeviceNumEdit.Value
    CWAI1.Channels.RemoveAll
    CWAI1.Channels.Add ChannelStringTextBox.Text
    CWAI1.NScans = NScansNumEdit.Value
    CWAI1.ScanClock.Frequency = FrequencyNumEdit.Value
    
    CWAI1.Configure
End Sub

Private Sub Start_Click()
    CWAI1.Start
End Sub

Private Sub CWAI1_AcquiredData(ScaledData As Variant, BinaryCodes As Variant)
    CWGraph1.PlotY ScaledData
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

