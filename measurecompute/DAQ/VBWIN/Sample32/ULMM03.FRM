VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   3825
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5760
   ForeColor       =   &H00FF0000&
   Height          =   4230
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3825
   ScaleWidth      =   5760
   Top             =   1200
   Width           =   5880
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   396
      Left            =   3744
      TabIndex        =   10
      Top             =   3264
      Width           =   876
   End
   Begin CommandButton cmdReadMemBoard 
      Caption         =   "Read "
      Enabled         =   0   'False
      Height          =   396
      Left            =   2400
      TabIndex        =   12
      Top             =   3264
      Width           =   972
   End
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start"
      Height          =   396
      Left            =   1056
      TabIndex        =   11
      Top             =   3264
      Width           =   972
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   19
      Left            =   4800
      TabIndex        =   43
      Top             =   2496
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "19"
      Height          =   204
      Index           =   19
      Left            =   4320
      TabIndex        =   42
      Top             =   2496
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   14
      Left            =   3456
      TabIndex        =   33
      Top             =   2496
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "14"
      Height          =   204
      Index           =   14
      Left            =   2976
      TabIndex        =   32
      Top             =   2496
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   9
      Left            =   2112
      TabIndex        =   14
      Top             =   2496
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "9"
      Height          =   204
      Index           =   9
      Left            =   1632
      TabIndex        =   23
      Top             =   2496
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   4
      Left            =   768
      TabIndex        =   6
      Top             =   2496
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "4"
      Height          =   204
      Index           =   4
      Left            =   288
      TabIndex        =   18
      Top             =   2496
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   18
      Left            =   4800
      TabIndex        =   41
      Top             =   2208
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "18"
      Height          =   204
      Index           =   18
      Left            =   4320
      TabIndex        =   40
      Top             =   2208
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   13
      Left            =   3456
      TabIndex        =   31
      Top             =   2208
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "13"
      Height          =   204
      Index           =   13
      Left            =   2976
      TabIndex        =   30
      Top             =   2208
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   8
      Left            =   2112
      TabIndex        =   13
      Top             =   2208
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "8"
      Height          =   204
      Index           =   8
      Left            =   1632
      TabIndex        =   22
      Top             =   2208
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   3
      Left            =   768
      TabIndex        =   5
      Top             =   2208
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "3"
      Height          =   204
      Index           =   3
      Left            =   288
      TabIndex        =   17
      Top             =   2208
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   17
      Left            =   4800
      TabIndex        =   39
      Top             =   1920
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "17"
      Height          =   204
      Index           =   17
      Left            =   4320
      TabIndex        =   38
      Top             =   1920
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   12
      Left            =   3456
      TabIndex        =   29
      Top             =   1920
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "12"
      Height          =   204
      Index           =   12
      Left            =   2976
      TabIndex        =   28
      Top             =   1920
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   7
      Left            =   2112
      TabIndex        =   9
      Top             =   1920
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "7"
      Height          =   204
      Index           =   7
      Left            =   1632
      TabIndex        =   21
      Top             =   1920
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   2
      Left            =   768
      TabIndex        =   4
      Top             =   1920
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "2"
      Height          =   204
      Index           =   2
      Left            =   288
      TabIndex        =   16
      Top             =   1920
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   16
      Left            =   4800
      TabIndex        =   37
      Top             =   1632
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "16"
      Height          =   204
      Index           =   16
      Left            =   4320
      TabIndex        =   36
      Top             =   1632
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   11
      Left            =   3456
      TabIndex        =   27
      Top             =   1632
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "11"
      Height          =   204
      Index           =   11
      Left            =   2976
      TabIndex        =   26
      Top             =   1632
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   6
      Left            =   2112
      TabIndex        =   8
      Top             =   1632
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "6"
      Height          =   204
      Index           =   6
      Left            =   1632
      TabIndex        =   20
      Top             =   1632
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   1
      Left            =   768
      TabIndex        =   3
      Top             =   1632
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "1"
      Height          =   204
      Index           =   1
      Left            =   288
      TabIndex        =   15
      Top             =   1632
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   15
      Left            =   4800
      TabIndex        =   35
      Top             =   1344
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "15"
      Height          =   204
      Index           =   15
      Left            =   4320
      TabIndex        =   34
      Top             =   1344
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   10
      Left            =   3456
      TabIndex        =   25
      Top             =   1344
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "10"
      Height          =   204
      Index           =   10
      Left            =   2976
      TabIndex        =   24
      Top             =   1344
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   5
      Left            =   2112
      TabIndex        =   7
      Top             =   1344
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "5"
      Height          =   204
      Index           =   5
      Left            =   1632
      TabIndex        =   19
      Top             =   1344
      Width           =   492
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   0
      Left            =   768
      TabIndex        =   2
      Top             =   1344
      Width           =   588
   End
   Begin Label lblDataPoint 
      Alignment       =   2  'Center
      Caption         =   "0"
      Height          =   204
      Index           =   0
      Left            =   288
      TabIndex        =   1
      Top             =   1344
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Value"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   7
      Left            =   4896
      TabIndex        =   51
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Data"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   6
      Left            =   4320
      TabIndex        =   50
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Value"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   5
      Left            =   3552
      TabIndex        =   49
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Data"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   4
      Left            =   2976
      TabIndex        =   48
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Value"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   3
      Left            =   2208
      TabIndex        =   47
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Data"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   2
      Left            =   1632
      TabIndex        =   46
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Value"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   1
      Left            =   864
      TabIndex        =   45
      Top             =   1056
      Width           =   492
   End
   Begin Label lblColTitle 
      Alignment       =   2  'Center
      Caption         =   "Data"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Index           =   0
      Left            =   288
      TabIndex        =   44
      Top             =   1056
      Width           =   492
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAInScan() with EXTMEMORY option"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5055
   End
End
'ULMM03.MAK================================================================

' File:                         ULMM03.MAK

' Library Call Demonstrated:    cbAInScan() with EXTMEMORY option
'
' Purpose:                      Collect data from A/D to memory board
'
' Demonstrates:                 How to use the EXTMEMORY option to
'                               send data to a memory board and how to
'                               read the data back again.
'
' Other Library Calls:          cbMemRead(), cbErrHandling()
'
' Special Requirements:         Board0 must be an A/D board.
'                               Board 5 must be a memory board.
'                               A/D and memory boards must be connected
'                               together via a DT-Connect cable.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const ADBoard% = 0              ' Board number of A/D board
Const MemBoard% = 5             ' Board number of memory board
Const NumPoints% = 1000         ' Number of points to collect from A/D
Const BufSize% = 20             ' Size of buffer used with cbMemRead()

Dim DataBuffer%(BufSize%)
Dim PointNum%
Dim FirstPoint&

Sub cmdReadMemBoard_Click ()
      
   ' Read the data back from the memory board in blocks.
   ' Print each block of data on the screen.
       
   '  BoardNum% - Board number of the memory board
   '  DataBuffer% - Array of data to read data into
   '  FirstPoint& - Address to read first point (or FROMHERE)
   '  CBCount& - Number of points to read

   CBCount& = BufSize%
   BoardNum% = MemBoard%
   ULStat% = cbMemRead(BoardNum%, DataBuffer%(0), FirstPoint&, CBCount&)
   If ULStat% <> 0 Then Stop
   FirstPoint& = FROMHERE

   For i% = 0 To BufSize% - 1
    
      ' Raw data from memory board contains a 4 bit channel number (LSB's)
      ' and a 12 bit A/D value (MSB's).  The following code strips out the
      ' channel tags from the A/D data.
    
      DataPoint% = DataBuffer%(i%) / 16 And &HFFF
    
      lblDataPoint(i%).Caption = Format$(PointNum% + i%, "0")
      lblADData(i%).Caption = Format$(DataPoint%, "0")
   Next i%

   PointNum% = PointNum% + BufSize%
   If PointNum% >= NumPoints% Then
      PointNum% = 0
      BoardNum% = MemBoard%
      ULStat% = cbMemReset(MemBoard%)
      If ULStat% <> 0 Then Stop
   End If

End Sub

Sub cmdStartConvert_Click ()

   cmdStartConvert.Enabled = 0
   cmdReadMemBoard.Enabled = 0

   ' Collect data to memory with cbAInScan() and the EXTMEMORY option
   '   Parameters:
   '     BoardNum%     :the number used by CB.CFG to describe this board
   '     LowChan%      :the first channel of the scan
   '     HighChan%     :the last channel of the scan
   '     CBCount&      :the total number of A/D samples to collect
   '     CBRate&       :sample rate in samples per second
   '     Gain%         :the gain for the board
   '     DataBuffer%[] :the array for the collected data values
   '     Options%      :data collection options

   BoardNum% = MemBoard%
   ULStat% = cbMemReset(MemBoard%)
   If ULStat% <> 0 Then Stop
 
   BoardNum% = ADBoard%              ' Board number
   LowChan% = 0                      ' Low channel of A/D scan
   HighChan% = 0                     ' High channel of A/D scan
   CBCount& = NumPoints              ' Number of data points to collect
   CBRate& = 5000                    ' Sampling rate (samples per second)
   Gain% = BIP5VOLTS                 ' A/D voltage range
   Dummy% = 0                        ' Placeholder (ignored)
   Options% = EXTMEMORY              ' Send data to memory board
  
   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain%, Dummy%, Options%)
   If ULStat% <> 0 Then Stop
   cmdStartConvert.Enabled = -1
   cmdReadMemBoard.Enabled = -1

End Sub

Sub cmdStopConvert_Click ()
   
   If ULStat% <> 0 Then Stop
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

   PointNum% = 0
   FirstPoint& = 0          ' Set address of first point to read

End Sub

