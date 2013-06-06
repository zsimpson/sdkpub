VERSION 5.00
Begin VB.Form frmStatusDisplay 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Daq Input Scan"
   ClientHeight    =   3735
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
   ScaleHeight     =   3735
   ScaleWidth      =   5250
   Begin VB.CommandButton cmdQuit 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   4200
      TabIndex        =   9
      Top             =   3240
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
   Begin VB.Label lblShowCount 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   2976
      TabIndex        =   15
      Top             =   3456
      Width           =   876
   End
   Begin VB.Label lblCount 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Current Count:"
      ForeColor       =   &H80000008&
      Height          =   204
      Left            =   1248
      TabIndex        =   13
      Top             =   3456
      Width           =   1548
   End
   Begin VB.Label lblShowIndex 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   2976
      TabIndex        =   14
      Top             =   3168
      Width           =   780
   End
   Begin VB.Label lblIndex 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Current Index:"
      ForeColor       =   &H80000008&
      Height          =   204
      Left            =   1248
      TabIndex        =   12
      Top             =   3168
      Width           =   1548
   End
   Begin VB.Label lblShowStat 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3360
      TabIndex        =   11
      Top             =   2880
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
      Top             =   2880
      Width           =   3180
   End
   Begin VB.Label lblADData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   2040
      TabIndex        =   6
      Top             =   2325
      Width           =   1575
   End
   Begin VB.Label lblChan2 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Counter 0:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   600
      TabIndex        =   3
      Top             =   2325
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   2040
      TabIndex        =   5
      Top             =   1920
      Width           =   1575
   End
   Begin VB.Label lblChan1 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "FIRSTPORTA:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   360
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
      Left            =   2040
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
      Left            =   600
      TabIndex        =   1
      Top             =   1515
      Width           =   1215
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbDaqInScan() in BACKGROUND mode"
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
'DaqInScan02.MAK================================================================

' File:                         DaqInScan02

' Library Call Demonstrated:    cbDaqInScan(), BACKGROUND mode

' Purpose:                      Synchronously scans Analog channels, Digital ports and Counters
'                               in the background.

' Demonstration:                Collects data on Analog Channel 0,
'                               FirstPortA and Counter 0 and
'                               Displays the input data.
'                               Calls cbGetStatus to determine the status
'                               of the background operation. Updates the
'                               display until a key is pressed.

' Other Library Calls:          cbGetStatus()
'                               cbStopBackground()
'                               cbCConfigScan()
'                               cbDConfigPort()
'                               cbErrHandling()

' Special Requirements:         Board 0 must support cbDaqInScan.
'

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const ChanCount& = 4            ' Number of channels in scan
Const NumPoints& = 100          ' Number of data points to collect
Const NumElements& = ChanCount& * NumPoints&

Dim ADData%(NumElements&)       ' dimension an array to hold the input values
Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ChanArray%(ChanCount&)       ' array to hold channel queue information
Dim ChanTypeArray%(ChanCount&)   ' array to hold channel type information
Dim GainArray%(ChanCount&)       ' array to hold gain queue information
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
   ChanTypeArray%(0) = ANALOG
   GainArray%(0) = BIP10VOLTS

   ChanArray%(1) = FIRSTPORTA
   ChanTypeArray%(1) = DIGITAL8
   GainArray%(1) = NotUsed

   ChanArray%(2) = 0
   ChanTypeArray%(2) = CTR32LOW
   GainArray%(2) = NotUsed

   ChanArray%(3) = 0
   ChanTypeArray%(3) = CTR32HIGH
   GainArray%(3) = NotUsed

End Sub

Private Sub cmdStartBgnd_Click()

   cmdStartBgnd.Enabled = 0
   cmdStartBgnd.Visible = 0
   cmdStopConvert.Enabled = 1
   cmdStopConvert.Visible = 1
   cmdQuit.Enabled = 0
   UserTerm% = False                    ' initialize user terminate flag
   
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
   '    ChansCount&        :the number of elements in the arrays (0=disable queue)
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
   '   FunctionType: A/D operation (AIFUNCTIOM)

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
        
        lblADData(0).Caption = Format$(ADData%(0), "0")
        lblADData(1).Caption = Format$(ADData%(1), "0")
        lblADData(2).Caption = Format$(ADData%(2) + ADData%(3) * (2 ^ 16), "0")     ' 32-bit counter
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

