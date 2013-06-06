VERSION 2.00
Begin Form frmShowFileData 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   5415
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5565
   ForeColor       =   &H00FF0000&
   Height          =   5820
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   5415
   ScaleWidth      =   5565
   Top             =   1200
   Width           =   5685
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   372
      Left            =   4512
      TabIndex        =   17
      Top             =   4704
      Width           =   732
   End
   Begin CommandButton cmdReadData 
      Caption         =   "Read Data"
      Height          =   372
      Left            =   3072
      TabIndex        =   19
      Top             =   768
      Width           =   1452
   End
   Begin CommandButton cmdWriteData 
      Caption         =   "Write Data"
      Height          =   372
      Left            =   864
      TabIndex        =   18
      Top             =   768
      Width           =   1452
   End
   Begin Label lblInstruct2 
      Alignment       =   2  'Center
      Caption         =   "So for example the value 203 is stored at address 203 in memory. Clicking Read Data reads the data back and displays it."
      ForeColor       =   &H00FF0000&
      Height          =   615
      Left            =   240
      TabIndex        =   44
      Top             =   4680
      Width           =   4095
   End
   Begin Label lblInstruct1 
      Alignment       =   2  'Center
      Caption         =   "This program writes 500 values to the memory board by writing 5 blocks of 100 values to consecutive locations in the memory board. The values that are written correspond to the memory board address in which they are stored."
      ForeColor       =   &H00FF0000&
      Height          =   855
      Left            =   240
      TabIndex        =   45
      Top             =   3840
      Width           =   5055
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   19
      Left            =   4944
      TabIndex        =   43
      Top             =   3432
      Width           =   408
   End
   Begin Label lblData19 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 304:"
      Height          =   210
      Left            =   2835
      TabIndex        =   42
      Top             =   3435
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   9
      Left            =   2160
      TabIndex        =   23
      Top             =   3432
      Width           =   504
   End
   Begin Label lblData9 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 104:"
      Height          =   216
      Left            =   144
      TabIndex        =   21
      Top             =   3432
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   18
      Left            =   4944
      TabIndex        =   41
      Top             =   3240
      Width           =   408
   End
   Begin Label lblData18 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 303:"
      Height          =   210
      Left            =   2835
      TabIndex        =   40
      Top             =   3240
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   8
      Left            =   2160
      TabIndex        =   22
      Top             =   3240
      Width           =   504
   End
   Begin Label lblData8 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 103:"
      Height          =   216
      Left            =   144
      TabIndex        =   20
      Top             =   3240
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   17
      Left            =   4944
      TabIndex        =   39
      Top             =   3048
      Width           =   408
   End
   Begin Label lblData17 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 302:"
      Height          =   210
      Left            =   2835
      TabIndex        =   38
      Top             =   3045
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   7
      Left            =   2160
      TabIndex        =   16
      Top             =   3048
      Width           =   504
   End
   Begin Label lblData7 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 102:"
      Height          =   216
      Left            =   144
      TabIndex        =   8
      Top             =   3048
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   16
      Left            =   4944
      TabIndex        =   37
      Top             =   2856
      Width           =   408
   End
   Begin Label lblData16 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 301:"
      Height          =   210
      Left            =   2835
      TabIndex        =   36
      Top             =   2850
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   6
      Left            =   2160
      TabIndex        =   15
      Top             =   2856
      Width           =   504
   End
   Begin Label lblData6 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 101:"
      Height          =   216
      Left            =   144
      TabIndex        =   7
      Top             =   2856
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   15
      Left            =   4944
      TabIndex        =   35
      Top             =   2676
      Width           =   408
   End
   Begin Label lblData15 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 300:"
      Height          =   210
      Left            =   2835
      TabIndex        =   34
      Top             =   2670
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   5
      Left            =   2160
      TabIndex        =   14
      Top             =   2676
      Width           =   504
   End
   Begin Label lblData5 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 100:"
      Height          =   216
      Left            =   144
      TabIndex        =   6
      Top             =   2676
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   14
      Left            =   4944
      TabIndex        =   33
      Top             =   2184
      Width           =   408
   End
   Begin Label lblData14 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 204:"
      Height          =   216
      Left            =   2832
      TabIndex        =   32
      Top             =   2184
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   4
      Left            =   2160
      TabIndex        =   13
      Top             =   2184
      Width           =   504
   End
   Begin Label lblData4 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 4:"
      Height          =   216
      Left            =   144
      TabIndex        =   5
      Top             =   2184
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   13
      Left            =   4944
      TabIndex        =   31
      Top             =   1992
      Width           =   408
   End
   Begin Label lblData13 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 203:"
      Height          =   216
      Left            =   2832
      TabIndex        =   30
      Top             =   1992
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   3
      Left            =   2160
      TabIndex        =   12
      Top             =   1992
      Width           =   504
   End
   Begin Label lblData3 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 3:"
      Height          =   216
      Left            =   144
      TabIndex        =   4
      Top             =   1992
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   12
      Left            =   4944
      TabIndex        =   29
      Top             =   1800
      Width           =   408
   End
   Begin Label lblData12 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 202:"
      Height          =   216
      Left            =   2832
      TabIndex        =   28
      Top             =   1800
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   2
      Left            =   2160
      TabIndex        =   11
      Top             =   1800
      Width           =   504
   End
   Begin Label lblData2 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 2:"
      Height          =   216
      Left            =   144
      TabIndex        =   3
      Top             =   1800
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   11
      Left            =   4944
      TabIndex        =   27
      Top             =   1608
      Width           =   408
   End
   Begin Label lblData11 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 201:"
      Height          =   216
      Left            =   2832
      TabIndex        =   26
      Top             =   1608
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   1
      Left            =   2160
      TabIndex        =   10
      Top             =   1608
      Width           =   504
   End
   Begin Label lblData1 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 1:"
      Height          =   216
      Left            =   144
      TabIndex        =   2
      Top             =   1608
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   10
      Left            =   4944
      TabIndex        =   25
      Top             =   1428
      Width           =   408
   End
   Begin Label lblData10 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 200:"
      Height          =   216
      Left            =   2832
      TabIndex        =   24
      Top             =   1428
      Width           =   1944
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   216
      Index           =   0
      Left            =   2160
      TabIndex        =   9
      Top             =   1428
      Width           =   504
   End
   Begin Label lblData0 
      Alignment       =   1  'Right Justify
      Caption         =   "Memory Location 0:"
      Height          =   216
      Left            =   144
      TabIndex        =   1
      Top             =   1428
      Width           =   1944
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbMemRead() and cbMemWrite()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   612
      Left            =   288
      TabIndex        =   0
      Top             =   96
      Width           =   4644
   End
End
'ULMM02.MAK================================================================

' File:                         ULMM02.MAK

' Library Call Demonstrated:    cbMemRead() and cbMemWrite()

' Purpose:                      Write data to a memory board and then read
'                               it back again

' Demonstrates:                 How to read and write to memory in blocks

' Other Library Calls:          cbErrHandling()

' Special Requirements:         Board 5 must be a memory board

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const MemBoardNum% = 5          ' Board number for memory board
Const NUMPOINTS% = 100          ' Number of points per block
Const NUMBLOCKS% = 4            ' Number of blocks to read/write

Dim DataBuffer1%(NUMPOINTS%)    ' dimension Visual Basics data array to hold
Dim DataBuffer2%(NUMPOINTS%)    ' data read from memory board

Sub cmdReadData_Click ()

   lblInstruct2.Caption = ""
   lblInstruct1.Caption = "The data read from the memory board is shown above."
  
   FirstPoint% = 0                       ' Set address of first point to read
  
   For BlockNum% = 0 To NUMBLOCKS% - 1   ' For each block

      ' Read a block of data from  the memory board
      ' MEMBOARD - Board number of the memory board
      ' DataBuffer2% - Array of data to read data into
      ' FirstPoint% - Address to read first point (or FROMHERE)
      ' CBCount& - Number of points to read

      CBCount& = NUMPOINTS%
      BoardNum = MemBoardNum%
  
      ULStat% = cbMemRead(BoardNum, DataBuffer2%(0), FirstPoint%, CBCount&)
      If ULStat% <> 0 Then Stop
    
      FirstPoint% = FROMHERE

      For i% = 0 To 4
         DataPoint% = BlockNum% * 5 + i%
         lblShowData(DataPoint%).Caption = Format$(DataBuffer2%(i%), "0")
      Next i%

   Next BlockNum%

End Sub

Sub cmdStopConvert_Click ()
   
   End
   
End Sub

Sub cmdWriteData_Click ()

   lblInstruct2.Caption = ""
   lblInstruct1.Caption = "A sample of the array written to the memory board is shown above. Press Read Data to verify."

   ' Create an array of data with known values to write to the memory board

   For BlockNum% = 0 To NUMBLOCKS% - 1
      For i% = 0 To NUMPOINTS%
         DataBuffer1%(i%) = BlockNum% * NUMPOINTS% + i%
      Next i%
    
      For i% = 0 To 4
         DataPoint% = 5 * BlockNum% + i%
         lblShowData(DataPoint%).Caption = Format$(DataBuffer1%(i%), "0")
      Next i%
    
      ' Write the block to the memory board
      ' MemBoardNum% - Board number of the memory board
      ' DataBuffer1% - Array of data to be written
      ' FirstPoint% - Address to write first point (or NEXTONE)
      ' CBCount& - Number of points to write

      CBCount& = NUMPOINTS%
      BoardNum = MemBoardNum%
      
      ULStat% = cbMemWrite(BoardNum, DataBuffer1%(0), FirstPoint%, CBCount&)
      If ULStat% <> 0 Then Stop

      FirstPoint% = FROMHERE
   Next BlockNum%
  
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

