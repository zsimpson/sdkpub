VERSION 2.00
Begin Form frmShowFileData 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   4485
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5565
   ForeColor       =   &H00FF0000&
   Height          =   4890
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4485
   ScaleWidth      =   5565
   Top             =   1200
   Width           =   5685
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   375
      Left            =   4680
      TabIndex        =   17
      Top             =   3960
      Width           =   735
   End
   Begin CommandButton cmdStartAcq 
      Caption         =   "Enable Trigger"
      Enabled         =   0   'False
      Height          =   375
      Left            =   3120
      TabIndex        =   18
      Top             =   3960
      Width           =   1455
   End
   Begin CommandButton cmdShowData 
      Caption         =   "Read Memory"
      Enabled         =   0   'False
      Height          =   375
      Left            =   3120
      TabIndex        =   20
      Top             =   3960
      Visible         =   0   'False
      Width           =   1455
   End
   Begin Frame fraInstruct 
      Height          =   735
      Left            =   840
      TabIndex        =   45
      Top             =   720
      Width           =   3855
      Begin CommandButton cmdLevelOK 
         Caption         =   "OK"
         Height          =   375
         Left            =   3240
         TabIndex        =   47
         Top             =   240
         Width           =   495
      End
      Begin Label lblInstruct 
         Alignment       =   2  'Center
         Caption         =   "Make sure that the trigger input is at a low level before starting."
         ForeColor       =   &H000000FF&
         Height          =   390
         Left            =   90
         TabIndex        =   46
         Top             =   195
         Width           =   2970
      End
   End
   Begin Label lblAcqStat 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   450
      Left            =   240
      TabIndex        =   19
      Top             =   3840
      Width           =   2535
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   19
      Left            =   4275
      TabIndex        =   44
      Top             =   3435
      Width           =   690
   End
   Begin Label lblData19 
      Caption         =   "Data Point 19:"
      Height          =   210
      Left            =   2835
      TabIndex        =   43
      Top             =   3435
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   9
      Left            =   1875
      TabIndex        =   24
      Top             =   3435
      Width           =   690
   End
   Begin Label lblData9 
      Caption         =   "Data Point 9:"
      Height          =   210
      Left            =   525
      TabIndex        =   22
      Top             =   3435
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   18
      Left            =   4275
      TabIndex        =   42
      Top             =   3240
      Width           =   690
   End
   Begin Label lblData18 
      Caption         =   "Data Point 18:"
      Height          =   210
      Left            =   2835
      TabIndex        =   41
      Top             =   3240
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   8
      Left            =   1875
      TabIndex        =   23
      Top             =   3240
      Width           =   690
   End
   Begin Label lblData8 
      Caption         =   "Data Point 8:"
      Height          =   210
      Left            =   525
      TabIndex        =   21
      Top             =   3240
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   17
      Left            =   4275
      TabIndex        =   40
      Top             =   3045
      Width           =   690
   End
   Begin Label lblData17 
      Caption         =   "Data Point 17:"
      Height          =   210
      Left            =   2835
      TabIndex        =   39
      Top             =   3045
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   7
      Left            =   1875
      TabIndex        =   16
      Top             =   3045
      Width           =   690
   End
   Begin Label lblData7 
      Caption         =   "Data Point 7:"
      Height          =   210
      Left            =   525
      TabIndex        =   8
      Top             =   3045
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   16
      Left            =   4275
      TabIndex        =   38
      Top             =   2850
      Width           =   690
   End
   Begin Label lblData16 
      Caption         =   "Data Point 16:"
      Height          =   210
      Left            =   2835
      TabIndex        =   37
      Top             =   2850
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   6
      Left            =   1875
      TabIndex        =   15
      Top             =   2850
      Width           =   690
   End
   Begin Label lblData6 
      Caption         =   "Data Point 6:"
      Height          =   210
      Left            =   525
      TabIndex        =   7
      Top             =   2850
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   15
      Left            =   4275
      TabIndex        =   36
      Top             =   2670
      Width           =   690
   End
   Begin Label lblData15 
      Caption         =   "Data Point 15:"
      Height          =   210
      Left            =   2835
      TabIndex        =   35
      Top             =   2670
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   5
      Left            =   1875
      TabIndex        =   14
      Top             =   2670
      Width           =   690
   End
   Begin Label lblData5 
      Caption         =   "Data Point 5:"
      Height          =   210
      Left            =   525
      TabIndex        =   6
      Top             =   2670
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   14
      Left            =   4275
      TabIndex        =   34
      Top             =   2475
      Width           =   690
   End
   Begin Label lblData14 
      Caption         =   "Data Point 14:"
      Height          =   210
      Left            =   2835
      TabIndex        =   33
      Top             =   2475
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   4
      Left            =   1875
      TabIndex        =   13
      Top             =   2475
      Width           =   690
   End
   Begin Label lblData4 
      Caption         =   "Data Point 4:"
      Height          =   210
      Left            =   525
      TabIndex        =   5
      Top             =   2475
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   13
      Left            =   4275
      TabIndex        =   32
      Top             =   2280
      Width           =   690
   End
   Begin Label lblData13 
      Caption         =   "Data Point 13:"
      Height          =   210
      Left            =   2835
      TabIndex        =   31
      Top             =   2280
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   3
      Left            =   1875
      TabIndex        =   12
      Top             =   2280
      Width           =   690
   End
   Begin Label lblData3 
      Caption         =   "Data Point 3:"
      Height          =   210
      Left            =   525
      TabIndex        =   4
      Top             =   2280
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   12
      Left            =   4275
      TabIndex        =   30
      Top             =   2085
      Width           =   690
   End
   Begin Label lblData12 
      Caption         =   "Data Point 12:"
      Height          =   210
      Left            =   2835
      TabIndex        =   29
      Top             =   2085
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   2
      Left            =   1875
      TabIndex        =   11
      Top             =   2085
      Width           =   690
   End
   Begin Label lblData2 
      Caption         =   "Data Point 2:"
      Height          =   210
      Left            =   525
      TabIndex        =   3
      Top             =   2085
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   11
      Left            =   4275
      TabIndex        =   28
      Top             =   1890
      Width           =   690
   End
   Begin Label lblData11 
      Caption         =   "Data Point 11:"
      Height          =   210
      Left            =   2835
      TabIndex        =   27
      Top             =   1890
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   1
      Left            =   1875
      TabIndex        =   10
      Top             =   1890
      Width           =   690
   End
   Begin Label lblData1 
      Caption         =   "Data Point 1:"
      Height          =   210
      Left            =   525
      TabIndex        =   2
      Top             =   1890
      Width           =   1170
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   10
      Left            =   4275
      TabIndex        =   26
      Top             =   1710
      Width           =   690
   End
   Begin Label lblData10 
      Caption         =   "Data Point 10:"
      Height          =   210
      Left            =   2835
      TabIndex        =   25
      Top             =   1710
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   0
      Left            =   1875
      TabIndex        =   9
      Top             =   1710
      Width           =   690
   End
   Begin Label lblData0 
      Caption         =   "Data Point 0:"
      Height          =   210
      Left            =   525
      TabIndex        =   1
      Top             =   1710
      Width           =   1170
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAPretrig() with External Memory"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   615
      Left            =   480
      TabIndex        =   0
      Top             =   120
      Width           =   4650
   End
End
'ULMM01.MAK================================================================

' Library Call Demonstrated:    cbAPretrig() with EXTMEMORY option and
'                               cbMemReadPretrig()

' Purpose:                      Collect pre-trig data from A/D to memory board

' Demonstrates:                 How to use the collect pre-trigger data
'                               to memory board and then retreive the data.

' Other Library Calls:          cbErrHandling()

' Special Requirements:         Board0 must be an A/D board.
'                               Board 5 must be a memory board.
'                               A/D and memory boards must be connected together
'                               via a DT-Connect cable.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const ADBoardNum% = 0       ' Board number for A/D board
Const MemBoardNum% = 5      ' Board number for memory board
Const BufSize% = 100        ' Size of buffer used with cbMemReadPretrig()

Dim DataBuffer%(BufSize%)   ' dimension Visual Basics data array to hold
                            ' data read from memory board

Sub cmdLevelOK_Click ()

   cmdStartAcq.Enabled = 1
   cmdLevelOK.Visible = 0
   lblInstruct.ForeColor = &HFF0000
   lblInstruct.Caption = "Click 'Enable Trigger' when ready..."

End Sub

Sub cmdShowData_Click ()
    
   ' Read the first block of data from the memory board.
   ' Read a block of data from  the memory board
   '  BoardNum - Board number of the memory board
   '  DataBuffer% - Array of data to read data into
   '  FirstPoint% - Address to read first point (or FROMHERE)
   '  CBCount& - Number of points to read

   CBCount& = BufSize%
   FirstPoint% = 0                     ' Set address of first point to read
   BoardNum% = MemBoardNum%
   ErrCode% = cbMemReadPretrig(BoardNum%, DataBuffer%(0), FirstPoint%, CBCount&)
 
   For i% = 0 To 19
      ' Raw data from memory board contains a 4 bit channel number (LSB's)
      ' and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value.
    
      DataPoint% = DataBuffer%(i%) / 16 And &HFFF
      lblShowData(i%).Caption = Format$(DataPoint%, "0")
   Next i%
  
   lblAcqStat.Caption = "Trigger occurred between points #9 and #10"

End Sub

Sub cmdStartAcq_Click ()

   cmdStartAcq.Enabled = 0
   cmdStartAcq.Visible = 0
   lblInstruct.Caption = "Acquiring data ..."
   Dummy% = DoEvents()

   ' Collect data to memory with cbAPretrig() and the EXTMEMORY option
   '  Parameters:
   '    BoardNum%     :the number used by CB.CFG to describe this board
   '    LowChan%      :the first channel of the scan
   '    HighChan%     :the last channel of the scan
   '    PretrigCount& :number of pre-trigger points
   '    TotalCount&   :the total number of A/D samples to collect
   '    CBRate&       :sample rate in samples per second
   '    Gain%         :the gain for the board
   '    Dummy%        :placeholder for integer value not used by this function
   '    Options%      :data collection options

   BoardNum% = ADBoardNum%           ' Board number
   LowChan% = 0                      ' Low channel of A/D scan
   HighChan% = 0                     ' High channel of A/D scan
   PretrigCount& = 10                ' Number of pre-trigger points
   TotalCount& = 10000               ' Number of data points to collect
   CBRate& = 10000                   ' Sampling rate (samples per second)
   Gain% = BIP5VOLT                  ' A/D voltage range
   Dummy% = 0                        ' Pass a dummy integer to cbATrig() (this is ignored)
   Options% = EXTMEMORY              ' Send data to memory board
    
   ULStat% = cbAPretrig(BoardNum%, LowChan%, HighChan%, PretrigCount&, TotalCount&, CBRate&, Gain%, Dummy%, Options%)
   If ULStat% <> 0 Then Stop

   cmdShowData.Enabled = 1
   cmdShowData.Visible = 1
   lblInstruct.Caption = "Click 'Read Memory' to read memory board and display data."

End Sub

Sub cmdStopConvert_Click ()
   
   End
   
End Sub

Sub Form_Load ()

   ' declare revision level of Universal Library

   ULStat% = cbDeclareRevision(CURRENTREVNUM)
   
   ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.
   
   '  Parameters:
   '     PRINTALL    :all warnings and errors encountered will be printed
   '     DONTSTOP    :if an error is encountered, the program will not stop,
   '                  errors must be handled locally
     
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop
   
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.

End Sub

