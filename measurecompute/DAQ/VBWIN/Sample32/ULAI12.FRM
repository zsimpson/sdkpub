VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   3645
   ClientLeft      =   3075
   ClientTop       =   2025
   ClientWidth     =   5235
   ForeColor       =   &H00FF0000&
   Height          =   4050
   Left            =   3015
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3645
   ScaleWidth      =   5235
   Top             =   1680
   Width           =   5355
   Begin TextBox txtHighChan 
      Alignment       =   2  'Center
      Height          =   285
      Left            =   3120
      TabIndex        =   21
      Text            =   "3"
      Top             =   1260
      Width           =   375
   End
   Begin CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   375
      Left            =   3960
      TabIndex        =   19
      Top             =   3120
      Width           =   975
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   375
      Left            =   3960
      TabIndex        =   17
      Top             =   3120
      Visible         =   0   'False
      Width           =   975
   End
   Begin Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   360
      Top             =   3120
   End
   Begin Label Label1 
      Caption         =   "Measure Channels 0 to"
      Height          =   240
      Left            =   960
      TabIndex        =   20
      Top             =   1305
      Width           =   2055
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   3960
      TabIndex        =   16
      Top             =   2805
      Width           =   975
   End
   Begin Label lblChan7 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 7:"
      Height          =   255
      Left            =   2760
      TabIndex        =   8
      Top             =   2805
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   2805
      Width           =   975
   End
   Begin Label lblChan3 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 3:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   2805
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3960
      TabIndex        =   15
      Top             =   2415
      Width           =   975
   End
   Begin Label lblChan6 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 6:"
      Height          =   255
      Left            =   2760
      TabIndex        =   7
      Top             =   2415
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   2415
      Width           =   975
   End
   Begin Label lblChan2 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 2:"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   2415
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   3960
      TabIndex        =   14
      Top             =   2025
      Width           =   975
   End
   Begin Label lblChan5 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 5:"
      Height          =   255
      Left            =   2760
      TabIndex        =   6
      Top             =   2025
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   2025
      Width           =   975
   End
   Begin Label lblChan1 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 1:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2025
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   3960
      TabIndex        =   13
      Top             =   1650
      Width           =   975
   End
   Begin Label lblChan4 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 4:"
      Height          =   255
      Left            =   2760
      TabIndex        =   5
      Top             =   1650
      Width           =   1095
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   1650
      Width           =   975
   End
   Begin Label lblChan0 
      Alignment       =   1  'Right Justify
      Caption         =   "Channel 0:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   1665
      Width           =   1095
   End
   Begin Label lblWarn 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "There must be a clock signal present at trigger input.  Otherwise, program will hang."
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   195
      TabIndex        =   18
      Top             =   720
      Width           =   4830
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAInScan() with EXTERNAL CLOCK"
      Height          =   615
      Left            =   195
      TabIndex        =   0
      Top             =   90
      Width           =   4665
   End
End
'ULAI12.MAK================================================================

' File:                         ULAI12.MAK

' Library Call Demonstrated:    cbAInScan%(), EXTCLOCK option

' Purpose:                      Scans a range of A/D Input Channels and stores
'                               the sample data in an array at a sample rate
'                               specified by an external clock.

' Demonstration:                Displays the analog input on two channels.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter and
'                               support the EXTCLOCK option.
'                               Analog signals on two input channels.
'                               Freq. on trigger 0 input.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0          ' Board number
Const NumPoints& = 8        ' Number of data points to collect
Const FirstPoint& = 0       ' set first element in buffer to transfer to array

Dim ADData%(NumPoints&)     ' dimension an array to hold the input values
Dim MemHandle&              ' define a variable to contain the handle for
                            ' memory allocated by Windows through cbWinBufAlloc%()
Dim HighChan%

Sub cmdStart_Click ()

   tmrConvert.Enabled = -1
   cmdStopConvert.Visible = -1
   cmdStart.Visible = 0

End Sub

Sub cmdStopConvert_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat% <> 0 Then Stop                ' other programs
   tmrConvert.Enabled = 0
   End
   
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
   '                 errors must be handled locally
     
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

Sub tmrConvert_Timer ()

   ' Collect the values with cbAInScan%()
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    LowChan%    :the first channel of the scan
   '    HighChan%   :the last channel of the scan
   '    CBCount&    :the total number of A/D samples to collect
   '    CBRate&     :sample rate
   '    Gain        :the gain for the board
   '    ADData%     :the array for the collected data values
   '    Options     :data collection options

   LowChan% = 0                     ' first channel to acquire
   HighChan% = Val(txtHighChan.Text)' last channel to acquire
   If HighChan% > 7 Then HighChan% = 7
   txtHighChan.Text = Str(HighChan%)

   CBCount& = NumPoints&            ' total number of data points to collect
   CBRate& = 100                      ' sampling rate is ignored
   Options = CONVERTDATA + EXTCLOCK
                                    ' return data as 12-bit values & use external clock
   Gain = BIP5VOLTS                ' set the gain
 
   If MemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options)
   If ULStat% <> 0 Then Stop

   ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic
  
   ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, CBCount&)
   If ULStat% <> 0 Then Stop

   For i% = 0 To HighChan%
      lblADData(i%).Caption = Format$(ADData%(i%), "0")
   Next i%

   For j% = HighChan% + 1 To 7
        lblADData(j%).Caption = Format$("", "0")
   Next j%

End Sub

