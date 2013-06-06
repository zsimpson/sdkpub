VERSION 5.00
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "Equivalent Time Sampling"
   ClientHeight    =   5670
   ClientLeft      =   2310
   ClientTop       =   2565
   ClientWidth     =   7260
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5670
   ScaleWidth      =   7260
   Begin VB.CommandButton Start 
      Caption         =   "Acquire"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   3000
      Width           =   1215
   End
   Begin CWUIControlsLib.CWNumEdit numDevice 
      Height          =   255
      Left            =   1920
      TabIndex        =   12
      Top             =   3600
      Width           =   1095
      _Version        =   196608
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
      CompatibleVers_0=   196608
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   458782
      Bindings_1      =   2
      ClassName_2     =   "CCWBindingHolderArray"
      Editor_2        =   3
      ClassName_3     =   "CCWBindingHolderArrayEditor"
      Owner_3         =   1
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   4
      ClassName_4     =   "CCWFormat"
      scale_1         =   5
      ClassName_5     =   "CCWScale"
      Bindings_5      =   0
      dMax_5          =   10
      discInterval_5  =   1
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
   End
   Begin CWDAQControlsLib.CWDAQTools CWDAQTools1 
      Left            =   2640
      Top             =   3000
      _Version        =   65540
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   5880
      TabIndex        =   9
      Top             =   4800
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
      ContextID       =   15053
   End
   Begin CWUIControlsLib.CWNumEdit SampleRateNumEdit 
      Height          =   255
      Left            =   1920
      TabIndex        =   4
      Top             =   4680
      Width           =   1095
      _Version        =   196608
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
      CompatibleVers_0=   196608
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   131102
      Bindings_1      =   2
      ClassName_2     =   "CCWBindingHolderArray"
      Editor_2        =   3
      ClassName_3     =   "CCWBindingHolderArrayEditor"
      Owner_3         =   1
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      Mode_1          =   1
      format_1        =   4
      ClassName_4     =   "CCWFormat"
      Format_4        =   ".## k""Hz"""
      scale_1         =   5
      ClassName_5     =   "CCWScale"
      opts_5          =   65536
      Bindings_5      =   0
      dMax_5          =   10
      discInterval_5  =   1
      ValueVarType_1  =   5
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   100
   End
   Begin CWUIControlsLib.CWNumEdit IncrementNumEdit 
      Height          =   255
      Left            =   1920
      TabIndex        =   3
      Top             =   4320
      Width           =   1095
      _Version        =   196608
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
      CompatibleVers_0=   196608
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   458782
      Bindings_1      =   2
      ClassName_2     =   "CCWBindingHolderArray"
      Editor_2        =   3
      ClassName_3     =   "CCWBindingHolderArrayEditor"
      Owner_3         =   1
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   4
      ClassName_4     =   "CCWFormat"
      scale_1         =   5
      ClassName_5     =   "CCWScale"
      opts_5          =   65536
      Bindings_5      =   0
      dMax_5          =   10
      discInterval_5  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   1
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMin_Val_1  =   1
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   255
   End
   Begin CWUIControlsLib.CWNumEdit SamplesNumEdit 
      Height          =   255
      Left            =   1920
      TabIndex        =   2
      Top             =   3960
      Width           =   1095
      _Version        =   196608
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
      CompatibleVers_0=   196608
      NumEdit_0       =   1
      ClassName_1     =   "CCWNumEdit"
      opts_1          =   458782
      Bindings_1      =   2
      ClassName_2     =   "CCWBindingHolderArray"
      Editor_2        =   3
      ClassName_3     =   "CCWBindingHolderArrayEditor"
      Owner_3         =   1
      C[0]_1          =   -2147483643
      C[1]_1          =   -2147483640
      format_1        =   4
      ClassName_4     =   "CCWFormat"
      scale_1         =   5
      ClassName_5     =   "CCWScale"
      opts_5          =   65536
      Bindings_5      =   0
      dMax_5          =   10
      discInterval_5  =   1
      ValueVarType_1  =   5
      Value_Val_1     =   1000
      IncValueVarType_1=   5
      IncValue_Val_1  =   1
      AccelIncVarType_1=   5
      AccelInc_Val_1  =   5
      RangeMinVarType_1=   5
      RangeMin_Val_1  =   10
      RangeMaxVarType_1=   5
      RangeMax_Val_1  =   10000
   End
   Begin CWUIControlsLib.CWGraph CWGraph1 
      Height          =   2775
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6975
      _Version        =   196608
      _ExtentX        =   12303
      _ExtentY        =   4895
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
      CompatibleVers_0=   196608
      Graph_0         =   1
      ClassName_1     =   "CCWGraphFrame"
      opts_1          =   14
      Bindings_1      =   2
      ClassName_2     =   "CCWBindingHolderArray"
      Editor_2        =   3
      ClassName_3     =   "CCWBindingHolderArrayEditor"
      Owner_3         =   1
      C[0]_1          =   0
      Event_1         =   4
      ClassName_4     =   "CCWGFPlotEvent"
      Owner_4         =   1
      Plots_1         =   5
      ClassName_5     =   "CCWDataPlots"
      Array_5         =   1
      Editor_5        =   6
      ClassName_6     =   "CCWGFPlotArrayEditor"
      Owner_6         =   1
      Array[0]_5      =   7
      ClassName_7     =   "CCWDataPlot"
      opts_7          =   4194335
      Name_7          =   "Plot-1"
      Bindings_7      =   0
      C[0]_7          =   65280
      C[1]_7          =   255
      C[2]_7          =   16711680
      C[3]_7          =   16776960
      Event_7         =   4
      X_7             =   8
      ClassName_8     =   "CCWAxis"
      opts_8          =   543
      Name_8          =   "XAxis"
      Bindings_8      =   0
      Orientation_8   =   2944
      format_8        =   9
      ClassName_9     =   "CCWFormat"
      Format_9        =   " k""s"""
      Scale_8         =   10
      ClassName_10    =   "CCWScale"
      opts_10         =   90112
      Bindings_10     =   0
      rMin_10         =   35
      rMax_10         =   450
      dMax_10         =   10
      discInterval_10 =   1
      Radial_8        =   0
      Enum_8          =   11
      ClassName_11    =   "CCWEnum"
      Editor_11       =   12
      ClassName_12    =   "CCWEnumArrayEditor"
      Owner_12        =   8
      Font_8          =   0
      tickopts_8      =   2711
      major_8         =   2
      minor_8         =   1
      Caption_8       =   13
      ClassName_13    =   "CCWDrawObj"
      opts_13         =   30
      Bindings_13     =   0
      C[0]_13         =   -2147483640
      Image_13        =   14
      ClassName_14    =   "CCWTextImage"
      Bindings_14     =   0
      font_14         =   0
      Animator_13     =   0
      Blinker_13      =   0
      Y_7             =   15
      ClassName_15    =   "CCWAxis"
      opts_15         =   1567
      Name_15         =   "YAxis-1"
      Bindings_15     =   0
      Orientation_15  =   2067
      format_15       =   16
      ClassName_16    =   "CCWFormat"
      Format_16       =   """ V"""
      Scale_15        =   17
      ClassName_17    =   "CCWScale"
      opts_17         =   122880
      Bindings_17     =   0
      rMin_17         =   11
      rMax_17         =   158
      dMax_17         =   10
      discInterval_17 =   1
      Radial_15       =   0
      Enum_15         =   18
      ClassName_18    =   "CCWEnum"
      Editor_18       =   19
      ClassName_19    =   "CCWEnumArrayEditor"
      Owner_19        =   15
      Font_15         =   0
      tickopts_15     =   2711
      major_15        =   2
      minor_15        =   1
      Caption_15      =   20
      ClassName_20    =   "CCWDrawObj"
      opts_20         =   30
      Bindings_20     =   0
      C[0]_20         =   -2147483640
      Image_20        =   21
      ClassName_21    =   "CCWTextImage"
      Bindings_21     =   0
      font_21         =   0
      Animator_20     =   0
      Blinker_20      =   0
      LineStyle_7     =   1
      LineWidth_7     =   1
      BasePlot_7      =   0
      DefaultXInc_7   =   1
      DefaultPlotPerRow_7=   -1  'True
      Axes_1          =   22
      ClassName_22    =   "CCWAxes"
      Array_22        =   2
      Editor_22       =   23
      ClassName_23    =   "CCWGFAxisArrayEditor"
      Owner_23        =   1
      Array[0]_22     =   8
      Array[1]_22     =   15
      DefaultPlot_1   =   24
      ClassName_24    =   "CCWDataPlot"
      opts_24         =   4194335
      Name_24         =   "[Template]"
      Bindings_24     =   0
      C[0]_24         =   65280
      C[1]_24         =   255
      C[2]_24         =   16711680
      C[3]_24         =   16776960
      Event_24        =   4
      X_24            =   8
      Y_24            =   15
      LineStyle_24    =   1
      LineWidth_24    =   1
      BasePlot_24     =   0
      DefaultXInc_24  =   1
      DefaultPlotPerRow_24=   -1  'True
      Cursors_1       =   25
      ClassName_25    =   "CCWCursors"
      Editor_25       =   26
      ClassName_26    =   "CCWGFCursorArrayEditor"
      Owner_26        =   1
      TrackMode_1     =   2
      GraphBackground_1=   0
      GraphFrame_1    =   27
      ClassName_27    =   "CCWDrawObj"
      opts_27         =   30
      Bindings_27     =   0
      Image_27        =   28
      ClassName_28    =   "CCWPictImage"
      opts_28         =   1280
      Bindings_28     =   0
      Rows_28         =   1
      Cols_28         =   1
      F_28            =   -2147483633
      B_28            =   -2147483633
      ColorReplaceWith_28=   8421504
      ColorReplace_28 =   8421504
      Tolerance_28    =   2
      Animator_27     =   0
      Blinker_27      =   0
      PlotFrame_1     =   29
      ClassName_29    =   "CCWDrawObj"
      opts_29         =   30
      Bindings_29     =   0
      C[1]_29         =   0
      Image_29        =   30
      ClassName_30    =   "CCWPictImage"
      opts_30         =   1280
      Bindings_30     =   0
      Rows_30         =   1
      Cols_30         =   1
      Pict_30         =   1
      F_30            =   -2147483633
      B_30            =   0
      ColorReplaceWith_30=   8421504
      ColorReplace_30 =   8421504
      Tolerance_30    =   2
      Animator_29     =   0
      Blinker_29      =   0
      Caption_1       =   31
      ClassName_31    =   "CCWDrawObj"
      opts_31         =   30
      Bindings_31     =   0
      C[0]_31         =   -2147483640
      Image_31        =   32
      ClassName_32    =   "CCWTextImage"
      Bindings_32     =   0
      font_32         =   0
      Animator_31     =   0
      Blinker_31      =   0
      DefaultXInc_1   =   1
      DefaultPlotPerRow_1=   -1  'True
   End
   Begin CWDAQControlsLib.CWPulse CWPulse1 
      Left            =   2040
      Top             =   3000
      _Version        =   196608
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196608
      CWPulse_0       =   1
      ClassName_1     =   "CCWPulse"
      opts_1          =   2
      Bindings_1      =   0
      Counter_1       =   0
      GateMode_1      =   4
      GateSource_1    =   9
      PulseType_1     =   4
      InternalClockMode_1=   2
      Phase1_1        =   2
      Phase2_1        =   2
      Phase1Inc_1     =   1
   End
   Begin CWDAQControlsLib.CWAI CWAI1 
      Left            =   1440
      Top             =   3000
      _Version        =   196608
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196608
      AITask_0        =   1
      ClassName_1     =   "CCWAITask"
      opts_1          =   2
      Bindings_1      =   0
      ErrorEventMask_1=   14336
      Device_1        =   1
      TotalScansToAcquire_1=   100
      ScanClock_1     =   2
      ClassName_2     =   "CCWAIClock"
      Bindings_2      =   0
      ClockType_2     =   1
      Frequency_2     =   5.00000e5
      Period_2        =   0.01
      TimebaseSource_2=   3
      ClockSourceType_2=   8
      ClockSourceSignal_2=   "0"
      InternalClockMode_2=   2
      ChannelClock_1  =   3
      ClassName_3     =   "CCWAIClock"
      Bindings_3      =   0
      ClockType_3     =   2
      Frequency_3     =   100
      Period_3        =   0.01
      InternalClockMode_3=   1
      Buffer_1        =   4
      ClassName_4     =   "CCWAIBuffer"
      Bindings_4      =   0
      Channels_1      =   5
      ClassName_5     =   "CCWAIChannelArray"
      Array_5         =   1
      Editor_5        =   6
      ClassName_6     =   "CCWAIChannelsArrayEditor"
      Owner_6         =   1
      Array[0]_5      =   7
      ClassName_7     =   "CCWAIChannel"
      Bindings_7      =   0
      Channels_7      =   "1"
      StartCond_1     =   8
      ClassName_8     =   "CCWAICondition"
      Bindings_8      =   0
      WhichCondition_8=   1
      Type_8          =   2
      Source_8        =   "1"
      Hysteresis_8    =   0.05
      PreTriggerScans_8=   3
      PauseCond_1     =   9
      ClassName_9     =   "CCWAICondition"
      Bindings_9      =   0
      WhichCondition_9=   2
      TrigPauseMode_9 =   7
      PreTriggerScans_9=   3
      StopCond_1      =   10
      ClassName_10    =   "CCWAICondition"
      Bindings_10     =   0
      WhichCondition_10=   3
      PreTriggerScans_10=   3
      HoldoffClock_1  =   11
      ClassName_11    =   "CCWAIClock"
      Bindings_11     =   0
      ClockType_11    =   3
      Frequency_11    =   100
      Period_11       =   0.01
      InternalClockMode_11=   1
   End
   Begin VB.Label Label6 
      Caption         =   "Device"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   3600
      Width           =   1455
   End
   Begin VB.Label Label5 
      Caption         =   "Acquisition channel is set in the AI property pages."
      Height          =   495
      Left            =   120
      TabIndex        =   10
      Top             =   5040
      Visible         =   0   'False
      Width           =   2895
   End
   Begin VB.Label Label3 
      Caption         =   $"EquivalentTimeSampling.frx":0000
      Height          =   975
      Left            =   3240
      TabIndex        =   8
      Top             =   3000
      Width           =   3855
   End
   Begin VB.Label Label4 
      Caption         =   "Note: This program requires an E-series data acquisition card with analog trigger circuitry (E-1, E-2, E-3, or E-4)."
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
      Left            =   3240
      TabIndex        =   7
      Top             =   4080
      Visible         =   0   'False
      Width           =   3855
   End
   Begin VB.Label Label2 
      Caption         =   "Incremental Delay (select effective sample rate)"
      Height          =   615
      Left            =   120
      TabIndex        =   6
      Top             =   4320
      Width           =   1575
   End
   Begin VB.Label Label1 
      Caption         =   "Number of Samples"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   3960
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    'Calculate effective sample rate based on 20MHz clock of E-Series DAQ device
    
    'On the form you specify the number of clock cycles to increment the pulse generation.
    'This is used to calculate the effective sampling rate of the ETS acquisition. The pulse
    'increment becomes the effective sampling rate. On the E series DAQ device the clock runs
    'at 20Mhz.
    SampleRateNumEdit.Value = 20000000 / IncrementNumEdit.Value
End Sub

Private Sub IncrementNumEdit_ValueChanged(Value As Variant, PreviousValue As Variant, ByVal OutOfRange As Boolean)
    'Recalculate effective sample rate based on 20MHz clock on E-Series DAQ device
    
    'On the form you specify the number of clock cycles to increment the pulse generation.
    'This is used to calculate the effective sampling rate of the ETS acquisition. The pulse
    'increment becomes the effective sampling rate. On the E series DAQ device the clock runs
    'at 20Mhz.
    SampleRateNumEdit = 20000000 / Value
End Sub

Private Sub Start_Click()
    CWPulse1.Device = numDevice
    CWAI1.Device = numDevice
    
    ' Configure and start counter for incremental delay pulses. Indivisual pulse are
    ' triggerd by the ATC.
    CWPulse1.PulseType = cwpulseIncrementalDelay
    CWPulse1.Phase1Inc = IncrementNumEdit.Value
    CWPulse1.GateSource = cwpulseATCOutGS
    CWPulse1.GateMode = cwpulseRisingEdgeGate
    CWPulse1.Configure
    CWPulse1.Start
    
    ' Configure AI for analog trigger. This programs the analog trigger circuitry (ATC).
    ' The output from the ATC is used by counter to perform the incremental pulse.
    CWAI1.StartCondition.Type = cwaiHWAnalog
        
    ' Connect output from counter to scan clock
    CWAI1.ScanClock.ClockSourceType = cwaiGPCTRLoToHiCS
    CWAI1.NScans = SamplesNumEdit.Value
    CWAI1.Configure
    CWAI1.Start
End Sub

Private Sub CWAI1_AcquiredData(ScaledData As Variant, BinaryCodes As Variant)
    'First value on X-axis is 0, increment on X-axis is the effective period (i.e. 1/effective sample rate)
    CWGraph1.PlotY ScaledData, 0, 1 / SampleRateNumEdit.Value
    
    CWGraph1.Axes(1).Maximum = SamplesNumEdit.Value / SampleRateNumEdit.Value
End Sub

Private Sub CWAI1_DAQError(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Error: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub

Private Sub CWAI1_DAQWarning(ByVal StatusCode As Long, ByVal ContextID As Long, ByVal ContextDescription As String)
    MsgBox "Warning: " & StatusCode & vbCrLf & "Context: " & ContextDescription & vbCrLf & CWDAQTools1.GetErrorText(StatusCode)
End Sub


