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
   Begin VB.Label lblChan1ValH 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   15
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblChan0ValH 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1680
      TabIndex        =   14
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblChan1ValL 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   13
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label lblChan0ValL 
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
   Begin VB.Label lblOutputH 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Output(high):"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblOutputL 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Output(low):"
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
      Caption         =   "Demonstration of cbDaqInScan() with scan option set to SCALEDATA"
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
'ULAO0401.MAK================================================================

' File:                         ULAO04.MAK

' Library Call Demonstrated:    cbAOutScan() with SCALEDATA option

' Purpose:                      Synchronously writes to an  Analog channels
'                               in the background.

' Demonstration:                Sends output to the D/A channels
'                               until a key is pressed.

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

Dim DAData#(CBCount&)           ' dimension an array to hold the output values
Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
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

   MemHandle& = cbScaledWinBufAlloc(CBCount&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop
   
    ' output (low)
    DAData#(0) = 0
    DAData#(1) = 0

    ' output (high))
    DAData#(2) = 5
    DAData#(3) = 5
    
    lblChan0ValL.Caption = Format$(DAData#(0), "0.00000000")
    lblChan1ValL.Caption = Format$(DAData#(1), "0.00000000")
    lblChan0ValH.Caption = Format$(DAData#(2), "0.00000000")
    lblChan1ValH.Caption = Format$(DAData#(3), "0.00000000")
   
   FirstPoint& = 0
  
   ULStat% = cbScaledWinArrayToBuf(DAData#(0), MemHandle&, FirstPoint&, CBCount&)
   
End Sub

Private Sub cmdStartBgnd_Click()

   cmdStartBgnd.Enabled = 0
   cmdStartBgnd.Visible = 0
   cmdStopConvert.Enabled = 1
   cmdStopConvert.Visible = 1
   cmdQuit.Enabled = 0
   UserTerm% = False
   
   
   ' Collect the values with cbAOutScan()
   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   LowChan%    :the lower channel of the scan
   '   HighChan%   :the upper channel of the scan
   '   CBCount&    :the number of D/A values to send
   '   CBRate&     :send rate in values/second (if supported by BoardNum)
   '   DAData%     :array of values to send to the scanned channels
   '   Options%    :data send options

   LowChan% = 0         'First analog output channel
   HighChan% = 1        'Last analog output channel
   CBRate& = 1000       ' generate data at 1000 Hz
   Gain% = BIP5VOLTS    'Ignored if gain is not programmable
   Options% = BACKGROUND + CONTINUOUS + SCALEDATA

   If MemHandle& = 0 Then Stop       ' check that a handle to a memory buffer exists

   ULStat% = cbAOutScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain%, MemHandle&, Options%)
   If ULStat% <> 0 Then Stop

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, AOFUNCTION)
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
   '   FunctionType: A/D operation (AOFUNCTION)

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, AOFUNCTION)
   If ULStat% <> 0 Then Stop


   lblShowCount.Caption = Format$(CurCount&, "0")
   lblShowIndex.Caption = Format$(CurIndex&, "0")

   ' Check if the background operation has finished. If it has, then
   ' transfer the data from the memory buffer set up by Windows to an
   ' array for use by Visual Basic
   ' The BACKGROUND operation must be explicitly stopped

   If Status% = RUNNING And Not UserTerm% Then
      lblShowStat.Caption = "Running"
      ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, AOFUNCTION)
      If ULStat% <> 0 Then Stop
        lblShowCount.Caption = Format$(CurCount&, "0")
        lblShowIndex.Caption = Format$(CurIndex&, "0")
   ElseIf Status% = IDLE Or UserTerm% Then
      lblShowStat.Caption = "Idle"
      tmrCheckStatus.Enabled = 0

      ULStat% = cbStopBackground(BoardNum%, AOFUNCTION)
      If ULStat% <> 0 Then Stop
      cmdStartBgnd.Enabled = 1
      cmdStartBgnd.Visible = 1
      cmdStopConvert.Enabled = 0
      cmdStopConvert.Visible = 0
      cmdQuit.Enabled = 1
  End If

End Sub

