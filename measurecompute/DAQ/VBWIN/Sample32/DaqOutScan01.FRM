VERSION 5.00
Begin VB.Form frmStatusDisplay 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Daq Input Scan"
   ClientHeight    =   4260
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
   ScaleHeight     =   4260
   ScaleWidth      =   5250
   Begin VB.CommandButton cmdQuit 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   4200
      TabIndex        =   5
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
      TabIndex        =   3
      Top             =   720
      Visible         =   0   'False
      Width           =   2700
   End
   Begin VB.CommandButton cmdStartBgnd 
      Appearance      =   0  'Flat
      Caption         =   "Start Background Operation"
      Height          =   396
      Left            =   1245
      TabIndex        =   4
      Top             =   720
      Width           =   2700
   End
   Begin VB.Label lblChan1 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   18
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblChan0 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1680
      TabIndex        =   17
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblChan 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   16
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblChan1Gain 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   15
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblChan0Gain 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1680
      TabIndex        =   14
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblChan1Type 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   13
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label lblChan0Type 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1680
      TabIndex        =   12
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label lblShowCount 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   2976
      TabIndex        =   11
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
      TabIndex        =   9
      Top             =   3456
      Width           =   1548
   End
   Begin VB.Label lblShowIndex 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   2976
      TabIndex        =   10
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
      TabIndex        =   8
      Top             =   3168
      Width           =   1548
   End
   Begin VB.Label lblShowStat 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3360
      TabIndex        =   7
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
      TabIndex        =   6
      Top             =   2880
      Width           =   3180
   End
   Begin VB.Label lblChan2 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Gain:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblType 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Type:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   1680
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
'DaqOutScan01.MAK================================================================

' File:                         DaqOutScan01.MAK

' Library Call Demonstrated:    cbDaqOutScan(), BACKGROUND mode

' Purpose:                      Synchronously writes to an  Analog channel and
'                               a Digital port in the background.

' Demonstration:                Sends output to the D/A channels
'                               until a key is pressed.

' Other Library Calls:          cbDConfigPort()
'                               cbErrHandling()

' Special Requirements:         Board 0 must support cbDaqOutScan.
'

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const ChanCount& = 2            ' Number of channels in scan
Const NumPoints& = 2            ' Number of data points to collect
Const CBCount& = ChanCount& * NumPoints&

Dim DAData%(CBCount&)           ' dimension an array to hold the output values
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

   MemHandle& = cbWinBufAlloc(CBCount&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop
   
    ' output (low)
    DAData%(0) = 0
    DAData%(1) = 0

    ' output (high))
    DAData%(2) = -1   'signed value equivalent to 65535 (unsigned)
    DAData%(3) = -1
   
   FirstPoint& = 0
  
   ULStat% = cbWinArrayToBuf(DAData%(0), MemHandle&, FirstPoint&, CBCount&)
   
   'load the arrays with values
   ChanArray%(0) = 0
   ChanTypeArray%(0) = ANALOG
   GainArray%(0) = BIP10VOLTS
   
   lblChan0.Caption = "0"
   lblChan0Type = "ANALOG"
   lblChan0Gain = "±10 Volts"

   ChanArray%(1) = FIRSTPORTA
   ChanTypeArray%(1) = DIGITAL16
   GainArray%(1) = NotUsed
   
   lblChan1.Caption = "FIRSTPORTA"
   lblChan1Type = "DIGITAL16"
   lblChan1Gain = "NotUsed"
   
End Sub

Private Sub cmdStartBgnd_Click()

   cmdStartBgnd.Enabled = 0
   cmdStartBgnd.Visible = 0
   cmdStopConvert.Enabled = 1
   cmdStopConvert.Visible = 1
   cmdQuit.Enabled = 0
   UserTerm% = False
   ' initialize user terminate flag
   
   'FIRSTPORTA is treated as a 16-bit port; therefore FIRSTPORTA and FIRSTPORTB must be configured for digital output
   PortNum& = FIRSTPORTA
   Direction& = DIGITALOUT
   ULStat% = cbDConfigPort(BoardNum%, PortNum, Direction)
   
   PortNum& = FIRSTPORTB
   Direction& = DIGITALOUT
   ULStat% = cbDConfigPort(BoardNum%, PortNum, Direction)
   
   ' Collect the values with cbDaqInScan()
   '  Parameters:
   '    BoardNum%        :the number used by CB.CFG to describe this board
   '    ChanArray%[]     :array of channel values
   '    ChanTypeArray%[] : array of channel types
   '    GainArray%[]     :array of gain values
   '    ChansCount&        :the number of elements in the arrays (0=disable queue)
   '    CBCount&         :the total number of A/D samples to collect
   '    CBRate&          :sample rate in samples per second
   '    ADData%[]        :the array for the collected data values
   '    Options          :data collection options

   Options = BACKGROUND + CONTINUOUS + NONSTREAMEDIO
   CBRate& = 1000                    ' Acquire data at 1000 Hz

   If MemHandle& = 0 Then Stop       ' check that a handle to a memory buffer exists

   ULStat% = cbDaqOutScan(BoardNum%, ChanArray%(0), ChanTypeArray%(0), GainArray%(0), ChanCount&, CBRate&, CBCount&, MemHandle&, Options)
   If ULStat% <> 0 Then Stop

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, DAQOFUNCTION)
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
   '   FunctionType: A/D operation (DAQOFUNCTION)

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, DAQOFUNCTION)
   If ULStat% <> 0 Then Stop


   lblShowCount.Caption = Format$(CurCount&, "0")
   lblShowIndex.Caption = Format$(CurIndex&, "0")

   ' Check if the background operation has finished. If it has, then
   ' transfer the data from the memory buffer set up by Windows to an
   ' array for use by Visual Basic
   ' The BACKGROUND operation must be explicitly stopped

   If Status% = RUNNING And Not UserTerm% Then
      lblShowStat.Caption = "Running"
      ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, DAQOFUNCTION)
      If ULStat% <> 0 Then Stop
        lblShowCount.Caption = Format$(CurCount&, "0")
        lblShowIndex.Caption = Format$(CurIndex&, "0")
   ElseIf Status% = IDLE Or UserTerm% Then
      lblShowStat.Caption = "Idle"
      tmrCheckStatus.Enabled = 0

      ULStat% = cbStopBackground(BoardNum%, DAQOFUNCTION)
      If ULStat% <> 0 Then Stop
      cmdStartBgnd.Enabled = 1
      cmdStartBgnd.Visible = 1
      cmdStopConvert.Enabled = 0
      cmdStopConvert.Visible = 0
      cmdQuit.Enabled = 1
  End If

End Sub

