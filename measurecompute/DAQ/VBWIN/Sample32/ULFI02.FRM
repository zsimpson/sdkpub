VERSION 2.00
Begin Form frmShowFileData 
   Caption         =   "Universal Library Analog Input to File"
   ClientHeight    =   4920
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5235
   ForeColor       =   &H00FF0000&
   Height          =   5325
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4920
   ScaleWidth      =   5235
   Top             =   1200
   Width           =   5355
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4320
      TabIndex        =   17
      Top             =   4440
      Width           =   690
   End
   Begin CommandButton cmdShowData 
      Caption         =   "Display Data"
      Enabled         =   0   'False
      Height          =   390
      Left            =   2760
      TabIndex        =   29
      Top             =   4440
      Visible         =   0   'False
      Width           =   1260
   End
   Begin CommandButton cmdStartAcq 
      Caption         =   "Start"
      Height          =   390
      Left            =   2760
      TabIndex        =   18
      Top             =   4440
      Width           =   1260
   End
   Begin TextBox txtFileName 
      Height          =   375
      Left            =   2640
      TabIndex        =   44
      Text            =   "DEMO.DAT"
      Top             =   3840
      Width           =   2415
   End
   Begin Label lblFileInstruct 
      Alignment       =   1  'Right Justify
      Caption         =   "Enter the name of the file in which to store the data."
      Height          =   615
      Left            =   0
      TabIndex        =   43
      Top             =   3600
      Width           =   2535
   End
   Begin Label lblShowFile 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   25
      Top             =   3165
      Width           =   2610
   End
   Begin Label lblFileName 
      Alignment       =   1  'Right Justify
      Caption         =   "File Name:"
      Height          =   204
      Left            =   384
      TabIndex        =   42
      Top             =   3168
      Width           =   1068
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   9
      Left            =   4320
      TabIndex        =   33
      Top             =   2784
      Width           =   684
   End
   Begin Label lblData9 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 9:"
      Height          =   210
      Left            =   2835
      TabIndex        =   31
      Top             =   2790
      Width           =   1305
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   8
      Left            =   4320
      TabIndex        =   32
      Top             =   2592
      Width           =   684
   End
   Begin Label lblData8 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 8:"
      Height          =   210
      Left            =   2835
      TabIndex        =   30
      Top             =   2595
      Width           =   1305
   End
   Begin Label lblShowPreTrig 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Left            =   1632
      TabIndex        =   28
      Top             =   2496
      Width           =   684
   End
   Begin Label lblPreTrig 
      Alignment       =   1  'Right Justify
      Caption         =   "PreTrig Count:"
      Height          =   204
      Left            =   192
      TabIndex        =   41
      Top             =   2496
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   7
      Left            =   4320
      TabIndex        =   16
      Top             =   2400
      Width           =   684
   End
   Begin Label lblData7 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 7:"
      Height          =   210
      Left            =   2835
      TabIndex        =   8
      Top             =   2400
      Width           =   1305
   End
   Begin Label lblShowTotal 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   27
      Top             =   2310
      Width           =   690
   End
   Begin Label lblTotal 
      Alignment       =   1  'Right Justify
      Caption         =   "Total Count:"
      Height          =   204
      Left            =   384
      TabIndex        =   40
      Top             =   2304
      Width           =   1068
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   6
      Left            =   4320
      TabIndex        =   15
      Top             =   2208
      Width           =   684
   End
   Begin Label lblData6 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 6:"
      Height          =   210
      Left            =   2835
      TabIndex        =   7
      Top             =   2205
      Width           =   1305
   End
   Begin Label lblShowCount 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   26
      Top             =   2115
      Width           =   690
   End
   Begin Label lblCount 
      Alignment       =   1  'Right Justify
      Caption         =   "Count:"
      Height          =   204
      Left            =   480
      TabIndex        =   39
      Top             =   2112
      Width           =   972
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   5
      Left            =   4320
      TabIndex        =   14
      Top             =   2016
      Width           =   684
   End
   Begin Label lblData5 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 5:"
      Height          =   210
      Left            =   2835
      TabIndex        =   6
      Top             =   2010
      Width           =   1305
   End
   Begin Label lblShowGain 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   24
      Top             =   1920
      Width           =   690
   End
   Begin Label lblGain 
      Alignment       =   1  'Right Justify
      Caption         =   "Gain:"
      Height          =   204
      Left            =   480
      TabIndex        =   38
      Top             =   1920
      Width           =   972
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   4
      Left            =   4320
      TabIndex        =   13
      Top             =   1824
      Width           =   684
   End
   Begin Label lblData4 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 4:"
      Height          =   210
      Left            =   2835
      TabIndex        =   5
      Top             =   1830
      Width           =   1305
   End
   Begin Label lblShowOptions 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   23
      Top             =   1725
      Width           =   690
   End
   Begin Label lblOptions 
      Alignment       =   1  'Right Justify
      Caption         =   "Options:"
      Height          =   204
      Left            =   480
      TabIndex        =   37
      Top             =   1728
      Width           =   972
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   3
      Left            =   4320
      TabIndex        =   12
      Top             =   1632
      Width           =   684
   End
   Begin Label lblData3 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 3:"
      Height          =   210
      Left            =   2835
      TabIndex        =   4
      Top             =   1635
      Width           =   1305
   End
   Begin Label lblShowHiChan 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   22
      Top             =   1530
      Width           =   690
   End
   Begin Label lblHiChan 
      Alignment       =   1  'Right Justify
      Caption         =   "High Channel:"
      Height          =   204
      Left            =   192
      TabIndex        =   36
      Top             =   1536
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   2
      Left            =   4320
      TabIndex        =   11
      Top             =   1440
      Width           =   684
   End
   Begin Label lblData2 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 2:"
      Height          =   210
      Left            =   2835
      TabIndex        =   3
      Top             =   1440
      Width           =   1305
   End
   Begin Label lblShowLoChan 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   21
      Top             =   1350
      Width           =   690
   End
   Begin Label lblLoChan 
      Alignment       =   1  'Right Justify
      Caption         =   "Low Channel:"
      Height          =   204
      Left            =   192
      TabIndex        =   35
      Top             =   1344
      Width           =   1260
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   1
      Left            =   4320
      TabIndex        =   10
      Top             =   1248
      Width           =   684
   End
   Begin Label lblData1 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 1:"
      Height          =   210
      Left            =   2835
      TabIndex        =   2
      Top             =   1245
      Width           =   1305
   End
   Begin Label lblShowRate 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1635
      TabIndex        =   20
      Top             =   1155
      Width           =   690
   End
   Begin Label lblRate 
      Alignment       =   1  'Right Justify
      Caption         =   "Rate:"
      Height          =   204
      Left            =   480
      TabIndex        =   34
      Top             =   1152
      Width           =   972
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   0
      Left            =   4320
      TabIndex        =   9
      Top             =   1056
      Width           =   684
   End
   Begin Label lblData0 
      Alignment       =   1  'Right Justify
      Caption         =   "Data Point 0:"
      Height          =   210
      Left            =   2835
      TabIndex        =   1
      Top             =   1050
      Width           =   1305
   End
   Begin Label lblAcqStat 
      Height          =   204
      Left            =   1056
      TabIndex        =   19
      Top             =   576
      Width           =   3372
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbFileAInScan%()"
      Height          =   330
      Left            =   90
      TabIndex        =   0
      Top             =   90
      Width           =   5025
   End
End
'ULFI02================================================================

' File:                         ULFI02.FRM

' Library Call Demonstrated:    File Operations:
'                               cbFileRead%()
'                               cbFileGetInfo%()

' Purpose:                      Read information & data from a streamer file.

' Demonstration:                Creates a file and scans analog data to the
'                               file. Displays the data in the file and the
'                               information in the file header.

' Other Library Calls:          cbFileAInScan%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter and support cbFileAInScan.
'                               Analog signal on an input channel.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0           ' Board number
Const NumPoints& = 128000    ' Number of data points to collect
Const ArraySize& = 10        ' size of Visual Basics data array

Dim DataBuffer%(ArraySize&)  ' dimension Visual Basics data array
Dim FileName$                ' name of file in which data will be stored

Sub cmdShowData_Click ()

   ' show the data using cbFileRead%()
   '  Parameters:
   '    FileName$      :the filename containing the data
   '    FirstPoint&    :index of the first data value to read
   '    NumPoints&     :the number of data values to read from the file
   '    DataBuffer%()  :array to read data into

   FirstPoint& = 0                   ' start at the first point
   ReadPoints& = ArraySize&          ' specify number of data points to read
  
   ULStat% = cbFileRead(FileName$, FirstPoint&, ReadPoints&, DataBuffer%(0))
   If ULStat% <> 0 Then Stop
  
   ' display the data values read from the file
  
   For I% = FirstPoint& To ArraySize& - 1
      lblShowData(I%).Caption = Format$(DataBuffer%(I%), "0")
   Next I%

End Sub

Sub cmdStartAcq_Click ()

   cmdStartAcq.Enabled = 0
   
   ' Parameters:
   CBCount& = NumPoints
   FileName$ = txtFileName.Text     ' it may be necessary to add path to
   CBRate& = 50000                  ' file name for data file to be found
   LowChan% = 0
   HighChan% = 0
   Options% = TIMED + NODTCONNECT
   Gain% = BIP5VOLTS

   DataCount$ = Format$(NumPoints, "0")
   lblAcqStat.Caption = "Collecting " + DataCount$ + " data points"
   lblShowRate.Caption = Format$(CBRate&, "0")
   lblShowLoChan.Caption = Format$(LowChan%, "0")
   lblShowHiChan.Caption = Format$(HighChan%, "0")
   lblShowOptions.Caption = Format$(Options%, "0")
   lblShowGain.Caption = Format$(Gain%, "0")
   lblShowFile.Caption = FileName$
   lblShowCount.Caption = Format$(CBCount&, "0")

   ' Collect the values with cbFileAInScan%()
   '  Parameters:
   '    BoardNum%   :the number used by CB.CFG to describe this board
   '    LowChan%    :first A/D channel of the scan
   '    HighChan%   :last A/D channel of the scan
   '    CBCount&    :the total number of A/D samples to collect
   '    CBRate&     :Sample rate in samples per second
   '    Gain%       :the gain for the board
   '    FileName$   :the filename for the collected data values
   '    Options%    :data collection options

   ULStat% = cbFileAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain%, FileName$, Options%)
   If ULStat% = 502 Then
      MsgBox "Enter the name of the file to store the data in text box.", 0, "Bad File Name"
      cmdStartAcq.Enabled = -1
      cmdStartAcq.Visible = -1
      txtFileName.SetFocus
      Exit Sub
   ElseIf ULStat% <> 0 Then
      Stop
   End If

   ' show how many data points were collected
   
   ULStat% = cbFileGetInfo(FileName$, LowChan%, HighChan%, PreTrigCount&, TotalCount&, CBRate&, Range&)
   If ULStat% <> 0 Then Stop

   lblShowRate.Caption = Format$(CBRate&, "0")
   lblShowLoChan.Caption = Format$(LowChan%, "0")
   lblShowHiChan.Caption = Format$(HighChan%, "0")
   lblShowOptions.Caption = Format$(Options%, "0")
   lblShowGain.Caption = Format$(Range&, "0")
   lblShowFile.Caption = FileName$
   
   lblShowTotal.Caption = Format$(TotalCount&, "0")
   lblShowPreTrig.Caption = Format$(PreTrigCount&, "0")
  
   cmdShowData.Enabled = 1
   cmdShowData.Visible = 1

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

