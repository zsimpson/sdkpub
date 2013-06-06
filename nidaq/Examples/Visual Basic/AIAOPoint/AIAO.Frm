VERSION 5.00
Object = "{8C7A5A52-105F-11CF-9BE5-0020AF6845F6}#1.4#0"; "CWDAQ.OCX"
Object = "{D940E4E4-6079-11CE-88CB-0020AF6845F6}#1.4#0"; "CWUI.OCX"
Object = "{2B8CD944-AE08-11D1-B366-006097B77FF4}#1.0#0"; "CWHLPBTN.OCX"
Begin VB.Form Form1 
   Caption         =   "AI AO"
   ClientHeight    =   3510
   ClientLeft      =   3180
   ClientTop       =   4005
   ClientWidth     =   3765
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3510
   ScaleWidth      =   3765
   Begin VB.Frame Frame2 
      Caption         =   "Analog Output"
      Height          =   2655
      Left            =   1920
      TabIndex        =   1
      Top             =   240
      Width           =   1695
      Begin VB.CommandButton GenerateButton 
         Caption         =   "Generate"
         Height          =   375
         Left            =   240
         TabIndex        =   8
         Top             =   2160
         Width           =   1215
      End
      Begin VB.TextBox AOChannel 
         Height          =   285
         Left            =   240
         TabIndex        =   5
         Text            =   "0"
         Top             =   1200
         Width           =   1215
      End
      Begin CWUIControlsLib.CWNumEdit AODeviceNumEdit 
         Height          =   255
         Left            =   240
         TabIndex        =   16
         Top             =   600
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
      Begin CWUIControlsLib.CWNumEdit AOVoltageNumEdit 
         Height          =   255
         Left            =   240
         TabIndex        =   10
         Top             =   1800
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
         opts_1          =   393246
         C[0]_1          =   16777215
         C[1]_1          =   -2147483640
         format_1        =   2
         ClassName_2     =   "CCWFormat"
         Format_2        =   " k""V"""
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
      Begin VB.Label Label6 
         Caption         =   "Device:"
         Height          =   255
         Left            =   240
         TabIndex        =   15
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Label5 
         Caption         =   "Voltage:"
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   1560
         Width           =   975
      End
      Begin VB.Label Label4 
         Caption         =   "Channel string:"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   960
         Width           =   1215
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Analog Input"
      Height          =   2655
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1695
      Begin VB.TextBox AIChannel 
         Height          =   285
         Left            =   240
         TabIndex        =   9
         Text            =   "0"
         Top             =   1200
         Width           =   1215
      End
      Begin VB.CommandButton AcquireButton 
         Caption         =   "Acquire"
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   1560
         Width           =   1215
      End
      Begin CWUIControlsLib.CWNumEdit AIDeviceNumEdit 
         Height          =   255
         Left            =   240
         TabIndex        =   14
         Top             =   600
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
      Begin CWUIControlsLib.CWNumEdit MeasurementNumEdit 
         Height          =   255
         Left            =   240
         TabIndex        =   12
         Top             =   2280
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
         opts_1          =   131134
         C[0]_1          =   -2147483638
         C[1]_1          =   -2147483640
         Mode_1          =   1
         format_1        =   2
         ClassName_2     =   "CCWFormat"
         Format_2        =   " k""V"""
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
      Begin VB.Label Label2 
         Caption         =   "Device:"
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Label3 
         Caption         =   "Measurement:"
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   2040
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "Channel string:"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   960
         Width           =   1215
      End
   End
   Begin CWHelpButtonLib.CWHelpButton CWHelpButton1 
      Height          =   375
      Left            =   1320
      TabIndex        =   11
      Top             =   3000
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
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
      ContextID       =   15055
   End
   Begin CWDAQControlsLib.CWAIPoint CWAIPoint1 
      Left            =   120
      Top             =   3000
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AIPoint_0       =   1
      ClassName_1     =   "CCWAIPoint"
      opts_1          =   2
      Device_1        =   1
      TotalScansToAcquire_1=   100
      ScanClock_1     =   0
      ChannelClock_1  =   2
      ClassName_2     =   "CCWAIClock"
      ClockType_2     =   2
      Frequency_2     =   100
      Period_2        =   0.01
      InternalClockMode_2=   1
      Buffer_1        =   0
      Channels_1      =   3
      ClassName_3     =   "CCWAIChannelArray"
      Array_3         =   1
      Editor_3        =   4
      ClassName_4     =   "CCWAIChannelsArrayEditor"
      Owner_4         =   1
      Array[0]_3      =   5
      ClassName_5     =   "CCWAIChannel"
      StartCond_1     =   0
      PauseCond_1     =   0
      StopCond_1      =   0
      HoldoffClock_1  =   0
   End
   Begin CWDAQControlsLib.CWAOPoint CWAOPoint1 
      Left            =   3120
      Top             =   3000
      _Version        =   196609
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      Reset_0         =   0   'False
      CompatibleVers_0=   196609
      AOPointTask_0   =   1
      ClassName_1     =   "CCWAOPointTask"
      opts_1          =   2
      ChannelType_1   =   1
      ReferenceSource_1=   1
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub AcquireButton_Click()
    CWAIPoint1.Device = AIDeviceNumEdit.Value
    'The CWAIPoint1 control's Channel collection already has 1 channel
    'that was added from the property pages. Update the channel string
    'to what the user specifies.
    CWAIPoint1.Channels(1).ChannelString = AIChannel.Text
    
    Dim Measurement
    CWAIPoint1.SingleRead Measurement
    MeasurementNumEdit.Value = Measurement
End Sub

Private Sub GenerateButton_Click()
    CWAOPoint1.Device = AODeviceNumEdit.Value
    CWAOPoint1.ChannelString = AOChannel.Text
    CWAOPoint1.SingleWrite AOVoltageNumEdit.Value
End Sub

Private Sub Form_Terminate()
    CWAOPoint1.Reset
End Sub
