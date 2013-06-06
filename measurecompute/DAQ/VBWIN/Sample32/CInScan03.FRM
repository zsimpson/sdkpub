VERSION 5.00
Begin VB.Form frmDataDisplay 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Counter Input Scan"
   ClientHeight    =   6315
   ClientLeft      =   5400
   ClientTop       =   3495
   ClientWidth     =   4320
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
   ScaleHeight     =   6315
   ScaleWidth      =   4320
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtEncoderValues 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   5055
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Top             =   660
      Width           =   3975
   End
   Begin VB.CommandButton cmdStopConvert 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   2160
      TabIndex        =   1
      Top             =   5820
      Width           =   870
   End
   Begin VB.CommandButton cmdStart 
      Appearance      =   0  'Flat
      Caption         =   "Start"
      Height          =   390
      Left            =   1080
      TabIndex        =   2
      Top             =   5820
      Width           =   870
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbCConfigScan() and cbCInScan() used with encoders"
      ForeColor       =   &H80000008&
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   60
      Width           =   3555
   End
End
Attribute VB_Name = "frmDataDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'CInScan03.frm================================================================

' File:                         CInScan03.frm

' Library Call Demonstrated:    cbCConfigScan() and cbCInScan%(), FOREGROUND mode

' Purpose:                      Scans a Counter Input in encoder mode and stores
'                               the sample data in an array.

' Demonstration:                Displays counts from encoder as phase A, phase B,
'                               and totalizes the index on Z.

' Other Library Calls:          cbErrHandling%()
'                               MccDaq.MccService.WinBufAlloc32()
'                               MccDaq.MccService.WinBufToArray32()
'                               MccDaq.MccService.WinBufFree()

' Special Requirements:         Board 0 must support counter scans in encoder mode.
'                               Phase A from encode connected to counter 0 input.
'                               Phase B from encode connected to counter 1 input.
'                               Index Z from encode connected to counter 2 input.

' (c) Copyright 1995-2007, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0           ' Board number
Const NumPoints& = 50         ' Number of data points to collect
Const FirstPoint& = 0         ' set first element in buffer to transfer to array
Dim CounterData&(NumPoints&)  ' dimension an array to hold the input values
Dim MemHandle&                ' define a variable to contain the handle for
                              ' memory allocated by Windows through cbWinBufAlloc%()

Dim FirstCtr, LastCtr As Long

Private Sub cmdStart_Click()
   Dim NumCtrs As Integer
   
   
   cmdStart.Enabled = False
   FirstCtr = 0
   LastCtr = 0
   
   ' Setup Counters
   ' Parameters:
   '   BoardNum       :the number used by CB.CFG to describe this board
   '   CounterNum     :counter to set up
   '   Mode           :counter Mode
   '   DebounceTime   :debounce Time
   '   DebounceMode   :debounce Mode
   '   EdgeDetection  :determines whether the rising edge or falling edge is to be detected
   '   TickSize       :reserved.
   '   MapCounter     :mapped counter

    ' Setup Counter 0 (Phase A signal)
    CounterNum& = 0
    Mode& = ENCODER Or ENCODER_MODE_X1 Or CLEAR_ON_Z_ON
    DebounceTime& = CTR_DEBOUNCE_NONE
    DebounceMode& = 0
    EdgeDetection& = CTR_RISING_EDGE
    TickSize& = 0
    MapChannel& = 2

    ULStat& = cbCConfigScan(BoardNum%, CounterNum&, Mode&, DebounceTime&, DebounceMode&, EdgeDetection&, TickSize&, MapChannel&)
    If ULStat& <> 0 Then Stop
    
   ' Collect the values with cbCInScan%()
   ' Parameters:
   '   BoardNum%   :the number used by CB.CFG to describe this board
   '   FirstCtr&   :the first counter of the scan
   '   LastCtr&    :the last counter of the scan
   '   CBCount&    :the total number of counter samples to collect
   '   CBRate&     :sample rate
   '   CounterData&     :the array for the collected data values
   '   Options     :data collection options
   CBCount& = NumPoints&            ' total number of data points to collect
   CBRate& = 10                    ' sampling rate (samples per second)
   Options = CTR32BIT
   
   If MemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists
   
   ULStat& = cbCInScan(BoardNum%, FirstCtr, LastCtr, CBCount&, CBRate&, MemHandle&, Options)
   If ULStat& <> 0 Then Stop
   
   ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic
   ULStat& = cbWinBufToArray32(MemHandle&, CounterData&(0), FirstPoint&, CBCount&)
   If ULStat& <> 0 Then Stop
   
   ColString = vbTab
   Me.txtEncoderValues.Text = "   Counter Data" & ColString & vbCrLf & vbCrLf & ColString
   For Element = 0 To NumPoints - 1
      Me.txtEncoderValues.Text = Me.txtEncoderValues.Text & _
      Format(CounterData(Element), "0") & ColString & vbCrLf & ColString
   Next

   cmdStart.Enabled = True

End Sub

Private Sub cmdStopConvert_Click()
   
   ULStat& = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat& <> 0 Then Stop               ' other programs
   
   End
   
End Sub

Private Sub Form_Load()
   
   ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.

   '  Parameters:
   '     PRINTALL    :all warnings and errors encountered will be printed
   '     DONTSTOP    :if an error is encountered, the program will not stop,
   '                  errors must be handled locally
  
   ULStat& = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat& <> 0 Then Stop

   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat&
   ' after a call to the library. If it is not equal to 0, an error has occurred.

   MemHandle& = cbWinBufAlloc32(NumPoints&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

End Sub

