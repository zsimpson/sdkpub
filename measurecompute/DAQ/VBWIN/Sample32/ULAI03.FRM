VERSION 2.00
Begin Form frmStatusDisplay 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   3735
   ClientLeft      =   2820
   ClientTop       =   1620
   ClientWidth     =   5250
   ForeColor       =   &H00FF0000&
   Height          =   4140
   Left            =   2760
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3735
   ScaleWidth      =   5250
   Top             =   1275
   Width           =   5370
   Begin TextBox txtHighChan 
      Height          =   285
      Left            =   3240
      TabIndex        =   27
      Text            =   "3"
      Top             =   1200
      Width           =   495
   End
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4200
      TabIndex        =   19
      Top             =   3240
      Width           =   780
   End
   Begin Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4440
      Top             =   840
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Stop Background Operation"
      Enabled         =   0   'False
      Height          =   396
      Left            =   1245
      TabIndex        =   17
      Top             =   720
      Visible         =   0   'False
      Width           =   2700
   End
   Begin CommandButton cmdStartBgnd 
      Caption         =   "Start Background Operation"
      Height          =   396
      Left            =   1245
      TabIndex        =   18
      Top             =   720
      Width           =   2700
   End
   Begin Label Label1 
      Caption         =   "Measure Channels 0 to"
      Height          =   255
      Left            =   1080
      TabIndex        =   26
      Top             =   1200
      Width           =   2055
   End
   Begin Label lblShowCount 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   2976
      TabIndex        =   25
      Top             =   3456
      Width           =   876
   End
   Begin Label lblCount 
      Alignment       =   1  'Right Justify
      Caption         =   "Current Count:"
      Height          =   204
      Left            =   1248
      TabIndex        =   23
      Top             =   3456
      Width           =   1548
   End
   Begin Label lblShowIndex 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   2976
      TabIndex        =   24
      Top             =   3168
      Width           =   780
   End
   Begin Label lblIndex 
      Alignment       =   1  'Right Justify
      Caption         =   "Current Index:"
      Height          =   204
      Left            =   1248
      TabIndex        =   22
      Top             =   3168
      Width           =   1548
   End
   Begin Label lblShowStat 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3360
      TabIndex        =   21
      Top             =   2880
      Width           =   990
   End
   Begin Label lblStatus 
      Alignment       =   1  'Right Justify
      Caption         =   "Status of Background Operation:"
      Height          =   210
      Left            =   90
      TabIndex        =   20
      Top             =   2880
      Width           =   3180
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   7
      Left            =   3960
      TabIndex        =   16
      Top             =   2376
      Width           =   972
   End
   Begin Label lblChan7 
      Caption         =   "Channel 7:"
      Height          =   252
      Left            =   2880
      TabIndex        =   8
      Top             =   2376
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   2376
      Width           =   972
   End
   Begin Label lblChan3 
      Caption         =   "Channel 3:"
      Height          =   252
      Left            =   360
      TabIndex        =   4
      Top             =   2376
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   6
      Left            =   3960
      TabIndex        =   15
      Top             =   2088
      Width           =   972
   End
   Begin Label lblChan6 
      Caption         =   "Channel 6:"
      Height          =   252
      Left            =   2880
      TabIndex        =   7
      Top             =   2088
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   2088
      Width           =   972
   End
   Begin Label lblChan2 
      Caption         =   "Channel 2:"
      Height          =   252
      Left            =   360
      TabIndex        =   3
      Top             =   2088
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   5
      Left            =   3960
      TabIndex        =   14
      Top             =   1800
      Width           =   972
   End
   Begin Label lblChan5 
      Caption         =   "Channel 5:"
      Height          =   252
      Left            =   2880
      TabIndex        =   6
      Top             =   1800
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   1800
      Width           =   972
   End
   Begin Label lblChan1 
      Caption         =   "Channel 1:"
      Height          =   252
      Left            =   360
      TabIndex        =   2
      Top             =   1800
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   4
      Left            =   3960
      TabIndex        =   13
      Top             =   1512
      Width           =   972
   End
   Begin Label lblChan4 
      Caption         =   "Channel 4:"
      Height          =   252
      Left            =   2880
      TabIndex        =   5
      Top             =   1512
      Width           =   972
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   1512
      Width           =   972
   End
   Begin Label lblChan0 
      Caption         =   "Channel 0:"
      Height          =   252
      Left            =   360
      TabIndex        =   1
      Top             =   1512
      Width           =   972
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAInScan%() in BACKGROUND mode"
      Height          =   615
      Left            =   90
      TabIndex        =   0
      Top             =   90
      Width           =   5055
   End
End
'ULAI03.MAK================================================================

' File:                         ULAI03.MAK

' Library Call Demonstrated:    cbAInScan%(), BACKGROUND mode

' Purpose:                      Scans a range of A/D Input Channels and stores
'                               the sample data in an array.

' Demonstration:                Displays the analog input on eight channels.

' Other Library Calls:          cbGetStatus%()
'                               cbStopBackground%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signals on eight input channels.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0              ' Board number
Const NumPoints& = 30000        ' Number of data points to collect
Const FirstPoint& = 0           ' set first element in buffer to transfer to array

Dim ADData%(NumPoints&)         ' dimension an array to hold the input values
Dim UserTerm%                   ' flag to stop acquisition manually
Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim HighChan%

Sub cmdQuit_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
                                            ' other programs
   If ULStat% <> 0 Then Stop
   End
   
End Sub

Sub cmdStartBgnd_Click ()

   cmdStartBgnd.Enabled = 0
   cmdStartBgnd.Visible = 0
   cmdStopConvert.Enabled = 1
   cmdStopConvert.Visible = 1
   cmdQuit.Enabled = 0
   UserTerm% = 0                     ' initialize user terminate flag

   ' Collect the values with cbAInScan%()
   '  Parameters:
   '    BoardNum%   :the number used by CB.CFG to describe this board
   '    LowChan%    :the first channel of the scan
   '    HighChan%   :the last channel of the scan
   '    CBCount&    :the total number of A/D samples to collect
   '    CBRate&     :sample rate
   '    Gain        :the gain for the board
   '    ADData%     :the array for the collected data values
   '    Options     :data collection options

   LowChan% = 0                     ' first channel to acquire
   HighChan% = Val(txtHighChan.Text)' last channel to acquire
   If (HighChan% > 7) Then HighChan% = 7
   txtHighChan.Text = Str(HighChan%)
   
   CBCount& = NumPoints&            ' total number of data points to collect
   CBRate& = 390                    ' sampling rate (samples per second)
   Options = CONVERTDATA + BACKGROUND + SINGLEIO
                                    ' return data as 12-bit values
                                    ' collect data in BACKGROUND mode
                                    ' use NOCONVERTDATA if using 16 bit board
   Gain = BIP5VOLTS                ' set the gain

   If MemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options)
   
   If ULStat% = 84 Then
      MsgBox "The CONVERT option cannot be used with 16 bit convertors. Set Options to NOCONVERTDATA."
      Stop   'Change CONVERTDATA in Options above to NOCONVERTDATA
   End If

   If ULStat% <> 0 Then Stop

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
   If ULStat% <> 0 Then Stop

   If Status% = RUNNING Then
      lblShowStat.Caption = "Running"
      lblShowCount.Caption = Format$(CurCount&, "0")
      lblShowIndex.Caption = Format$(CurIndex&, "0")
   End If

   tmrCheckStatus.Enabled = 1

End Sub

Sub cmdStopConvert_Click ()

   UserTerm% = 1

End Sub

Sub Form_Load ()
   
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

   MemHandle& = cbWinBufAlloc(NumPoints&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

End Sub

Sub tmrCheckStatus_Timer ()

   ' This timer will check the status of the background data collection
   
   ' Parameters:
   '   BoardNum%    :the number used by CB.CFG to describe this board
   '   Status%     :current status of the background data collection
   '   CurCount&   :current number of samples collected
   '   CurIndex&   :index to the data buffer pointing to the start of the
   '                most recently collected scan
   '   FunctionType: A/D operation (AIFUNCTIOM)

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
   If ULStat% <> 0 Then Stop


   lblShowCount.Caption = Format$(CurCount&, "0")
   lblShowIndex.Caption = Format$(CurIndex&, "0")

   ' Check if the background operation has finished. If it has, then
   ' transfer the data from the memory buffer set up by Windows to an
   ' array for use by Visual Basic
   ' The BACKGROUND operation must be explicitly stopped

   If Status% = RUNNING And UserTerm% = 0 Then
      lblShowStat.Caption = "Running"
   ElseIf Status% = 0 Or UserTerm% = 1 Then
      lblShowStat.Caption = "Idle"
   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
      If ULStat% <> 0 Then Stop
      lblShowCount.Caption = Format$(CurCount&, "0")
      lblShowIndex.Caption = Format$(CurIndex&, "0")
      tmrCheckStatus.Enabled = 0
      If MemHandle& = 0 Then Stop
      ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, NumPoints&)
      If ULStat% <> 0 Then Stop
      
      For i% = 0 To HighChan%
         lblADData(i%).Caption = Format$(ADData%(i%), "0")
      Next i%

	  For j% = HighChan% + 1 To 7
        lblADData(j%).Caption = Format$("", "0")
	  Next j%

      ULStat% = cbStopBackground(BoardNum%,AIFUNCTION)
      If ULStat% <> 0 Then Stop
      cmdStartBgnd.Enabled = 1
      cmdStartBgnd.Visible = 1
      cmdStopConvert.Enabled = 0
      cmdStopConvert.Visible = 0
      cmdQuit.Enabled = 1
   End If

End Sub

