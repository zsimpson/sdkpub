VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form AI1 
   Caption         =   "SCXI Continuous Acquisition"
   ClientHeight    =   4830
   ClientLeft      =   1920
   ClientTop       =   1995
   ClientWidth     =   6285
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4830
   ScaleWidth      =   6285
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   495
      Left            =   120
      TabIndex        =   12
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox Channel 
      Height          =   375
      Left            =   1680
      TabIndex        =   3
      Text            =   "ob0!sc1!md1!0:3"
      Top             =   3240
      Width           =   1335
   End
   Begin VB.TextBox Device 
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Text            =   "1"
      Top             =   3240
      Width           =   1335
   End
   Begin VB.CommandButton Quit 
      Caption         =   "Quit"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin CWUIControlsLib.CWNumEdit ScanRate 
      Height          =   375
      Left            =   4800
      TabIndex        =   17
      Top             =   3240
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
   Begin CWUIControlsLib.CWNumEdit NumScans 
      Height          =   375
      Left            =   3240
      TabIndex        =   16
      Top             =   3240
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
      Value_Val_1     =   500
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
   Begin CWUIControlsLib.CWNumEdit UpperLimit 
      Height          =   255
      Left            =   1800
      TabIndex        =   15
      Top             =   3840
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
      opts_1          =   458814
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   " ""V"""
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
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   10
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWUIControlsLib.CWNumEdit LowerLimit 
      Height          =   255
      Left            =   1800
      TabIndex        =   14
      Top             =   4200
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
      opts_1          =   458814
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   2
      ClassName_2     =   "CCWFormat"
      Format_2        =   " ""V"""
      scale_1         =   3
      ClassName_3     =   "CCWScale"
      opts_3          =   65536
      dMax_3          =   10
      discInterval_3  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   -10
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMin_Val_1  =   -10
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   10
      Bindings_1      =   4
      ClassName_4     =   "CCWBindingHolderArray"
      Editor_4        =   5
      ClassName_5     =   "CCWBindingHolderArrayEditor"
      Owner_5         =   1
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   495
      Left            =   120
      TabIndex        =   13
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
      ContextID       =   15062
   End
   Begin CWUIControlsLib.CWGraph Graph 
      Height          =   2655
      Left            =   1680
      TabIndex        =   8
      Top             =   120
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
      opts_32         =   8254
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
   Begin CWDAQControlsLib.CWAI AI 
      Left            =   120
      Top             =   3960
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
   Begin VB.Label Label7 
      Caption         =   "Specify the upper limit and lower limit of your expected measurement."
      Height          =   495
      Left            =   3240
      TabIndex        =   11
      Top             =   3960
      Width           =   2895
   End
   Begin VB.Label Label6 
      Caption         =   "Lower Limit"
      Height          =   255
      Left            =   840
      TabIndex        =   10
      Top             =   4200
      Width           =   855
   End
   Begin VB.Label Label5 
      Caption         =   "Upper Limit"
      Height          =   255
      Left            =   840
      TabIndex        =   9
      Top             =   3840
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Scan Rate"
      Height          =   255
      Left            =   4800
      TabIndex        =   7
      Top             =   2880
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Number of Scans"
      Height          =   255
      Left            =   3240
      TabIndex        =   6
      Top             =   2880
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Channel"
      Height          =   255
      Left            =   1680
      TabIndex        =   5
      Top             =   2880
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Device"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   2880
      Width           =   1215
   End
End
Attribute VB_Name = "AI1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub AI_AcquiredData(Voltages As Variant, BinaryCodes As Variant)
    Graph.PlotY Voltages
End Sub

Private Sub Start_Click()
    Dim lerr As Long
    
    Graph.ClearData
    ' Configure DAQ control with settings from the form
    AI.Device = Device
    AI.Channels.RemoveAll
    AI.Channels.Add Channel, UpperLimit, LowerLimit
    AI.NScans = NumScans
    AI.ScanClock.Frequency = ScanRate.Text
    
    ' Configure and Start Acquisition
    lerr = AI.Configure
    If lerr <> 0 Then MsgBox "DAQ Configure: " + CStr(lerr)
    lerr = AI.Start
    If lerr <> 0 Then MsgBox "DAQ Start: " + CStr(lerr)
End Sub

Private Sub Quit_Click()
    End
End Sub

Private Sub Stop_Click()
    AI.Stop
End Sub
