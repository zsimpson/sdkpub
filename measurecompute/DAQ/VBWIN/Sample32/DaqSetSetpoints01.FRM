VERSION 5.00
Begin VB.Form frmStatusDisplay 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library DaqSetSetpoints"
   ClientHeight    =   4275
   ClientLeft      =   2820
   ClientTop       =   1620
   ClientWidth     =   5250
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00FF0000&
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4275
   ScaleWidth      =   5250
   Begin VB.CommandButton cmdQuit 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   4200
      TabIndex        =   9
      Top             =   3720
      Width           =   780
   End
   Begin VB.Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4440
      Top             =   840
   End
   Begin VB.CommandButton cmdStopConvert 
      Appearance      =   0  'Flat
      Caption         =   "Stop Background Operation"
      Enabled         =   0   'False
      Height          =   396
      Left            =   1245
      TabIndex        =   7
      Top             =   720
      Visible         =   0   'False
      Width           =   2700
   End
   Begin VB.CommandButton cmdStartBgnd 
      Appearance      =   0  'Flat
      Caption         =   "Start Background Operation"
      Height          =   396
      Left            =   1245
      TabIndex        =   8
      Top             =   720
      Width           =   2700
   End
   Begin VB.Label lblChan3 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Setpoint Status Register:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   17
      Top             =   2760
      Width           =   2295
   End
   Begin VB.Label lblADData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   2520
      TabIndex        =   16
      Top             =   2760
      Width           =   1575
   End
   Begin VB.Label lblShowCount 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2970
      TabIndex        =   15
      Top             =   3930
      Width           =   870
   End
   Begin VB.Label lblCount 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Current Count:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   1245
      TabIndex        =   13
      Top             =   3930
      Width           =   1545
   End
   Begin VB.Label lblShowIndex 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2970
      TabIndex        =   14
      Top             =   3645
      Width           =   780
   End
   Begin VB.Label lblIndex 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Current Index:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   1245
      TabIndex        =   12
      Top             =   3645
      Width           =   1545
   End
   Begin VB.Label lblShowStat 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3360
      TabIndex        =   11
      Top             =   3360
      Width           =   990
   End
   Begin VB.Label lblStatus 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Status of Background Operation:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   90
      TabIndex        =   10
      Top             =   3360
      Width           =   3180
   End
   Begin VB.Label lblADData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   2520
      TabIndex        =   6
      Top             =   2325
      Width           =   1575
   End
   Begin VB.Label lblChan2 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "FIRSTPORTA:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1080
      TabIndex        =   3
      Top             =   2325
      Width           =   1335
   End
   Begin VB.Label lblADData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   2520
      TabIndex        =   5
      Top             =   1920
      Width           =   1575
   End
   Begin VB.Label lblChan1 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel 1:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   960
      TabIndex        =   2
      Top             =   1920
      Width           =   1455
   End
   Begin VB.Label lblADData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   2520
      TabIndex        =   4
      Top             =   1515
      Width           =   1575
   End
   Begin VB.Label lblChan0 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel 0:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1200
      TabIndex        =   1
      Top             =   1515
      Width           =   1215
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbDaqSetSetpoints()"
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   90
      TabIndex        =   0
      Top             =   90
      Width           =   5055
   End
End
Attribute VB_Name = "frmStatusDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'DaqSetSetpoints01.MAK================================================================

' File:                         DaqSetSetpoints01

' Library Call Demonstrated:    cbDaqSetSetpoints()

' Purpose:                      Demonstrate the configuration and usage of setpoints
'                               Including Adding the setpoint status to the scanlist and
'                               asynchronous reads of the setpoint status

' Demonstration:                Displays the input channels data.
'                               Calls cbGetStatus to determine the status
'                               of the background operation. Updates the
'                               display until Stop Background button is pressed.

' Other Library Calls:          cbDaqInScan()
'                               cbGetStatus()
'                               cbStopBackground()
'                               cbDConfigPort()
'                               cbErrHandling()

' Special Requirements:         Board 0 must support cbDaqInScan.
'

' (c) Copyright 1995-2007, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const ChanCount& = 4            ' Number of channels in scan
Const NumPoints& = 100          ' Number of data points to collect
Const NumElements& = ChanCount& * NumPoints&

Const SetpointCount& = 3         ' Number of setpoints

Dim ADData%(NumElements&)       ' dimension an array to hold the input values
Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ChanArray%(ChanCount&)       ' array to hold channel queue information
Dim ChanTypeArray%(ChanCount&)   ' array to hold channel type information
Dim GainArray%(ChanCount&)       ' array to hold gain queue information

Dim LimitAArray!(SetpointCount&)  ' array to hold LimitA Values
Dim LimitBArray!(SetpointCount&)  ' array to hold LimitB Values
Dim SetpointFlagsArray&(SetpointCount&)    'array to hold Setpoint flags
Dim SetpointOutputArray&(SetpointCount&)   'array to hold  output channels
Dim Output1Array!(SetpointCount&)          'array to hold output1 values
Dim Output2Array!(SetpointCount&)          'array to hold output2 values
Dim OutputMask1Array!(SetpointCount&)      'array to hold output masks for output1
Dim OutputMask2Array!(SetpointCount&)      'array to hold output masks for output2

Dim UserTerm%

Private Sub cmdQuit_Click()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
                                            ' other programs
   If ULStat% <> 0 Then Stop
   End
   
End Sub

Private Sub cmdStopConvert_Click()

   UserTerm% = True

End Sub

Private Sub Form_Load()
   
   ' declare revision level of Universal Library

   ULStat% = cbDeclareRevision(CURRENTREVNUM)

   ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.
   '  Parameters:
   '    PRINTALL    :all warnings and errors encountered will be printed
   '    DONTSTOP    :if an error is encountered, the program will not stop,
   '                  errors must be handled locally
  
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop

   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.

   MemHandle& = cbWinBufAlloc(NumElements&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop
   
   'load the arrays with values
   ChanArray%(0) = 0
   ChanTypeArray%(0) = ANALOG + SETPOINT_ENABLE
   GainArray%(0) = BIP10VOLTS

   ChanArray%(1) = 1
   ChanTypeArray%(1) = ANALOG + SETPOINT_ENABLE
   GainArray%(1) = BIP10VOLTS

   ChanArray%(2) = FIRSTPORTA
   ChanTypeArray%(2) = DIGITAL8 + SETPOINT_ENABLE
   GainArray%(2) = NOTUSED

   ChanArray%(3) = 0
   ChanTypeArray%(3) = SETPOINTSTATUS
   GainArray%(3) = NOTUSED
   
   ' load the setpoint configuration array with values
   ' For each channel that has the SETPOINT_ENABLE flag
   ' included, a setpoint entry must exist

   ' setpoint configurations for ChanArray(0)  (CH0)*/
   SetpointFlagsArray&(0) = SF_LESSTHAN_LIMITA + SF_UPDATEON_TRUEANDFALSE
   SetpointOutputArray&(0) = SO_DAC0    'setpoint result outputs a value to Analog Out 0
   LimitAArray!(0) = 3                  'if CH0 less than 3.0 volts apply output1, else apply output2
   LimitBArray!(0) = 0                  'ignored when SF_LESSTHAN_LIMITA flag is used
   Output1Array!(0) = 5                 'output 5.0 volts on Analog Out 0
   Output2Array!(0) = -5                'output -5.0 volts on Analog Out 0
   OutputMask1Array!(0) = 0             'ignored for 'SO_DAC0' output type
   OutputMask2Array!(0) = 0             'ignored for 'SO_DAC0' output type

   'setpoint configurations for ChanArray(1) (CH1)
    SetpointFlagsArray&(1) = SF_GREATERTHAN_LIMITB + SF_UPDATEON_TRUEANDFALSE
    SetpointOutputArray&(1) = SO_FIRSTPORTC  'setpoint result outputs a value to digital port C
    LimitAArray!(1) = 0                      'ignored when SF_GREATERTHAN_LIMITB flag is used
    LimitBArray!(1) = 2                      'if CH1 greater than 2.0 volts apply output1
    Output1Array!(1) = &H55                  'output a bit pattern of 01010101 to digital port C
    Output2Array!(1) = &HAA                  'output a bit pattern of 10101010 to digital port C
    OutputMask1Array!(1) = &HF               'output the value of 'out1' on low nibble only
    OutputMask2Array!(1) = &HF               'output the value of 'out2' on low nibble only

    ' setpoint configurations for ChanArray(2) (FIRSTPORTA)
    SetpointFlagsArray&(2) = SF_EQUAL_LIMITA + SF_UPDATEON_TRUEONLY
    SetpointOutputArray&(2) = SO_TMR0   ' setpoint result outputs a value to Timer 0
    LimitAArray!(2) = &HF               ' if FIRSTPORTA equal 00001111 bit pattern apply output1
    LimitBArray!(2) = 2                 ' ignored when SF_EQUAL_LIMITA flag is used
    Output1Array!(2) = 100              ' output a 100Hz square wave on Timer 0
    Output2Array!(2) = 0                ' ignored when SF_UPDATEON_TRUEONLY flag is used
    OutputMask1Array!(2) = 0            ' ignored for 'SO_TMR0' output type
    OutputMask2Array!(2) = 0            ' ignored for 'SO_TMR0' output type

End Sub

Private Sub cmdStartBgnd_Click()

   cmdStartBgnd.Enabled = 0
   cmdStartBgnd.Visible = 0
   cmdStopConvert.Enabled = 1
   cmdStopConvert.Visible = 1
   cmdQuit.Enabled = 0
   UserTerm% = False                    ' initialize user terminate flag
   
' configure setpoints with cbDaqSetSetpoints()
    '  Parameters:
    '        BoardNum                :the number used by CB.CFG to describe this board
    '        LimitAArray![]           :array of LimitA values
    '        LimitBArray![]           :array of LimitB values
    '        SetpointFlagsArray&[]    :array of Setpoint flags
    '        SetpointOutputArray&[]   :array of output channels
    '        Output1Array![]          :array of output1 values
    '        Output2Array![]          :array of output2 values
    '        OutputMask1Array![]      :array of output masks for output1
    '        OutputMask2Array![]      :array of output masks for output2
    '        SetpointCount&           :Number of setpoints
    
    ULStat% = cbDaqSetSetpoints(BoardNum%, LimitAArray!(0), LimitBArray!(0), Reserved!, SetpointFlagsArray&(0), SetpointOutputArray&(0), Output1Array!(0), Output2Array!(0), OutputMask1Array!(0), OutputMask2Array!(0), SetpointCount&)
   
   'configure FIRSTPORTA for digital input
   PortNum& = FIRSTPORTA
   Direction& = DIGITALIN
   ULStat% = cbDConfigPort(BoardNum%, PortNum, Direction)
   If ULStat% <> 0 Then Stop
   
' Collect the values with cbDaqInScan()
   '  Parameters:
   '    BoardNum%        :the number used by CB.CFG to describe this board
   '    ChanArray%[]     :array of channel values
   '    ChanTypeArray%[] : array of channel types
   '    GainArray%[]     :array of gain values
   '    ChanCount&        :the number of elements in the arrays (0=disable queue)
   '    PretrigCount&    :number of pre-trigger A/D samples to collect
   '    CBCount&         :the total number of A/D samples to collect
   '    CBRate&          :sample rate in samples per second
   '    ADData%[]        :the array for the collected data values
   '    Options          :data collection options

   PretrigCount& = 0
   CBCount& = NumElements&           ' Number of data points to collect
   Options = CONVERTDATA + BACKGROUND + CONTINUOUS
   CBRate& = 100                    ' Acquire data at 100 Hz

   If MemHandle& = 0 Then Stop       ' check that a handle to a memory buffer exists

   ULStat% = cbDaqInScan(BoardNum%, ChanArray%(0), ChanTypeArray%(0), GainArray%(0), ChanCount&, CBRate&, PretrigCount&, CBCount&, MemHandle&, Options)
   If ULStat% <> 0 Then Stop

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, DAQIFUNCTION)
   If ULStat% <> 0 Then Stop

   If Status% = RUNNING Then
      lblShowStat.Caption = "Running"
      lblShowCount.Caption = Format$(CurCount&, "0")
      lblShowIndex.Caption = Format$(CurIndex&, "0")
   End If

   tmrCheckStatus.Enabled = 1

End Sub




Private Sub tmrCheckStatus_Timer()

   ' This timer will check the status of the background data collection
   
   ' Parameters:
   '   BoardNum%    :the number used by CB.CFG to describe this board
   '   Status%     :current status of the background data collection
   '   CurCount&   :current number of samples collected
   '   CurIndex&   :index to the data buffer pointing to the start of the
   '                most recently collected scan
   '   FunctionType: A/D operation (DAQIFUNCTION)

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, DAQIFUNCTION)
   If ULStat% <> 0 Then Stop

   lblShowCount.Caption = Format$(CurCount&, "0")
   lblShowIndex.Caption = Format$(CurIndex&, "0")

   ' Check if the background operation has finished. If it has, then
   ' transfer the data from the memory buffer set up by Windows to an
   ' array for use by Visual Basic
   ' The BACKGROUND operation must be explicitly stopped

   If Status% = RUNNING And Not UserTerm% Then
      lblShowStat.Caption = "Running"
      ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, DAQIFUNCTION)
      If ULStat% <> 0 Then Stop
      lblShowCount.Caption = Format$(CurCount&, "0")
      lblShowIndex.Caption = Format$(CurIndex&, "0")
      
      FirstPoint& = CurIndex& - (CurIndex& Mod ChanCount&) - ChanCount&
      If FirstPoint& > 0 Then
        If MemHandle& = 0 Then Stop
        ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, ChanCount&)
        If ULStat% <> 0 Then Stop
        
        ULStat% = cbToEngUnits(BoardNum, GainArray%(0), ADData%(0), EngUnits!)
        lblADData(0).Caption = Format$(EngUnits!, "0.000 Volts")
        ULStat% = cbToEngUnits(BoardNum, GainArray%(1), ADData%(1), EngUnits!)
        lblADData(1).Caption = Format$(EngUnits!, "0.000 Volts")
        lblADData(2).Caption = "0x" + Hex$(ADData%(2))
        lblADData(3).Caption = "0x" + Hex$(ADData%(3))
      End If
     ElseIf Status% = IDLE Or UserTerm% Then
      lblShowStat.Caption = "Idle"
      tmrCheckStatus.Enabled = 0

      ULStat% = cbStopBackground(BoardNum%, DAQIFUNCTION)
      If ULStat% <> 0 Then Stop
      cmdStartBgnd.Enabled = 1
      cmdStartBgnd.Visible = 1
      cmdStopConvert.Enabled = 0
      cmdStopConvert.Visible = 0
      cmdQuit.Enabled = 1
   End If

End Sub

