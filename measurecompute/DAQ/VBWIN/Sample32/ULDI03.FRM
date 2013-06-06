VERSION 2.00
Begin Form frmDScan 
   Caption         =   "Universal Library Digital Input"
   ClientHeight    =   4830
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5415
   Height          =   5235
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4830
   ScaleWidth      =   5415
   Top             =   1200
   Width           =   5535
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Height          =   495
      Left            =   3480
      TabIndex        =   1
      Top             =   4200
      Width           =   1215
   End
   Begin CommandButton cmdReadDIn 
      Caption         =   "Read"
      Height          =   495
      Left            =   1920
      TabIndex        =   0
      Top             =   4200
      Width           =   1215
   End
   Begin CommandButton cmdTemp 
      Caption         =   "Force"
      Height          =   495
      Left            =   480
      TabIndex        =   2
      Top             =   4200
      Width           =   1215
   End
   Begin Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   300
      Left            =   4800
      Top             =   3480
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   9
      Left            =   3600
      TabIndex        =   7
      Top             =   3720
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   1680
      TabIndex        =   12
      Top             =   3720
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   8
      Left            =   3600
      TabIndex        =   8
      Top             =   3360
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1680
      TabIndex        =   13
      Top             =   3360
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   3600
      TabIndex        =   9
      Top             =   3000
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1680
      TabIndex        =   14
      Top             =   3000
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3600
      TabIndex        =   10
      Top             =   2640
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1680
      TabIndex        =   15
      Top             =   2640
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   3600
      TabIndex        =   11
      Top             =   2280
      Width           =   855
   End
   Begin Label lblDataRead 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1680
      TabIndex        =   16
      Top             =   2280
      Width           =   855
   End
   Begin Label lblData 
      Alignment       =   2  'Center
      ForeColor       =   &H00000000&
      Height          =   255
      Index           =   10
      Left            =   720
      TabIndex        =   21
      Top             =   2280
      Width           =   855
   End
   Begin Label lblBGStat 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1260
      TabIndex        =   3
      Top             =   1860
      Width           =   2835
   End
   Begin Label lblShowIndex 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3480
      TabIndex        =   4
      Top             =   1320
      Width           =   1215
   End
   Begin Label lblShowCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   2040
      TabIndex        =   5
      Top             =   1320
      Width           =   1215
   End
   Begin Label lblShowStat 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   600
      TabIndex        =   6
      Top             =   1320
      Width           =   1215
   End
   Begin Label lblIndex 
      Alignment       =   2  'Center
      Caption         =   "Index"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3480
      TabIndex        =   20
      Top             =   960
      Width           =   1215
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      Caption         =   "Count"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   2040
      TabIndex        =   19
      Top             =   960
      Width           =   1215
   End
   Begin Label lblStatus 
      Alignment       =   2  'Center
      Caption         =   "Status"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   600
      TabIndex        =   18
      Top             =   960
      Width           =   1215
   End
   Begin Label lblFunction 
      Alignment       =   2  'Center
      Caption         =   "cbDInScan() Example Program"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   360
      TabIndex        =   17
      Top             =   240
      Width           =   4215
   End
End
'ULDI03.MAK================================================================

' File:                         ULDI03.MAK

' Library Call Demonstrated:    cbDInScan%()

' Purpose:                      Reads a digital input port
'                               at specified rate and number
'                               of samples.

' Demonstration:                Configures FIRSTPORTA and
'                               FIRSTPORTB for input and
'                               reads the value on the port.

' Other Library Calls:          cbDConfigPort%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must be a PDMA 16.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number

Const Direction% = DIGITALIN    ' set direction of port to input
Const NumPoints& = 500
Const FirstPoint& = 0

Dim DataBuffer%(NumPoints&)
Dim MemHandle&, CBCount&, PortNum%, Force%

Sub cmdReadDIn_Click ()

   'read the digital input and display
   '  Parameters:
   '     BoardNum      :the number used by CB.CFG to describe this board
   '     PortNum%      :the input port
   '     CBCount&      :number of times to read digital input
   '     CBRate&       :sample rate in samples/second
   '     DataBuffer%() :the array for the digital input values read from the port
   '     Options%      :data collection options

   CBCount& = NumPoints&
   CBRate& = 100
   
   Options% = WORDXFER + Background

   ULStat% = cbDInScan(BoardNum%, PortNum%, CBCount&, CBRate&, MemHandle&, Options%)
   If ULStat% <> 0 Then Stop
   tmrCheckStatus.Enabled = 1

End Sub

Sub cmdStopRead_Click ()

   ULStat% = cbStopBackground(BoardNum%,DIFUNCTION)
   If ULStat% <> 0 Then Stop
   ULStat% = cbWinBufFree(MemHandle&)
   If ULStat% <> 0 Then Stop
   End

End Sub

Sub cmdTemp_Click ()

   Force% = 1
   'For I% = 0 To 9' CBCount& - 1
   '   lblDataRead(I%).Caption = ""
   'Next I%

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
    
   ' configure FIRSTPORTA for digital input
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board.
   '    PortNum%    :the input port
   '    Direction%  :sets the port for input or output
     
    
   'configure FIRSTPORTA & FIRSTPORTB for digital input
   '  Parameters:
   '     BoardNum    :the number used by CB.CFG to describe this board
   '     PortNum%    :the input port
   '     Direction%  :sets the port for input or output

   MemHandle& = cbWinBufAlloc(NumPoints&)
   If MemHandle& = 0 Then Stop
   
   PortNum% = FIRSTPORTB
   ULStat% = cbDConfigPort(BoardNum, PortNum%, Direction%)
   If ULStat% <> 0 Then Stop

   PortNum% = FIRSTPORTA
   UDStat% = cbDConfigPort(BoardNum, PortNum%, Direction%)
   If ULStat% <> 0 Then Stop
   Force% = 0

End Sub

Sub ShowData ()
   
   ULStat% = cbWinBufToArray(MemHandle&, DataBuffer%(0), FirstPoint&, CBCount&)
   If ULStat% <> 0 Then Stop

   For I% = 0 To 9
      lblDataRead(I%).Caption = Hex$(DataBuffer%(I%))
   Next I%

End Sub

Sub tmrCheckStatus_Timer ()
   
   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,DIFUNCTION)
   If ULStat% <> 0 Then Stop
   lblShowStat.Caption = Format$(Status%, "0")
   lblShowCount.Caption = Format$(CurCount&, "0")
   lblShowIndex.Caption = Format$(CurIndex&, "0")
   If Status% = RUNNING Then
      lblBGStat.Caption = "Background operation running"
   Else
      lblBGStat.Caption = "Background operation idle"
   End If
   If CurCount& = NumPoints& Or Status% = 0 Or Force% = 1 Then
      tmrCheckStatus.Enabled = 0
      ULStat% = cbStopBackground(BoardNum%,DIFUNCTION)
      If ULStat% <> 0 Then Stop
      ShowData
   End If

End Sub

