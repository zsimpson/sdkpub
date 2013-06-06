VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input to File"
   ClientHeight    =   4620
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   6165
   ForeColor       =   &H00FF0000&
   Height          =   5025
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4620
   ScaleWidth      =   6165
   Top             =   1200
   Width           =   6285
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Enabled         =   0   'False
      Height          =   390
      Left            =   5280
      TabIndex        =   1
      Top             =   4080
      Visible         =   0   'False
      Width           =   690
   End
   Begin CommandButton cmdStartAcq 
      Caption         =   "Start"
      Height          =   390
      Left            =   5280
      TabIndex        =   2
      Top             =   4080
      Width           =   690
   End
   Begin TextBox txtFileName 
      Height          =   375
      Left            =   2760
      TabIndex        =   30
      Text            =   "DEMO.DAT"
      Top             =   4080
      Width           =   2415
   End
   Begin Label lblFileInstruct 
      Alignment       =   1  'Right Justify
      Caption         =   "Enter the name of the file in which to store the data."
      Height          =   615
      Left            =   120
      TabIndex        =   31
      Top             =   3720
      Width           =   2535
   End
   Begin Label lblReadFile 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   18
      Top             =   3240
      Width           =   1785
   End
   Begin Label lblShowFile 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   9
      Top             =   3240
      Width           =   1665
   End
   Begin Label lblFileName 
      Alignment       =   1  'Right Justify
      Caption         =   "File Name:"
      Height          =   255
      Left            =   480
      TabIndex        =   25
      Top             =   3240
      Width           =   975
   End
   Begin Label lblReadPreTrig 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   12
      Top             =   2760
      Width           =   750
   End
   Begin Label lblShowPreTrig 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1680
      TabIndex        =   29
      Top             =   2760
      Width           =   1815
   End
   Begin Label lblPreTrig 
      Alignment       =   1  'Right Justify
      Caption         =   "Pre-Trig Count:"
      Height          =   255
      Left            =   0
      TabIndex        =   28
      Top             =   2760
      Width           =   1455
   End
   Begin Label lblReadTotal 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   11
      Top             =   2400
      Width           =   750
   End
   Begin Label lblShowCount 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   10
      Top             =   2400
      Width           =   945
   End
   Begin Label lblCount 
      Alignment       =   1  'Right Justify
      Caption         =   "Count:"
      Height          =   255
      Left            =   480
      TabIndex        =   24
      Top             =   2400
      Width           =   975
   End
   Begin Label lblReadGain 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   17
      Top             =   2160
      Width           =   825
   End
   Begin Label lblShowGain 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   8
      Top             =   2160
      Width           =   945
   End
   Begin Label lblGain 
      Alignment       =   1  'Right Justify
      Caption         =   "Gain:"
      Height          =   255
      Left            =   480
      TabIndex        =   23
      Top             =   2160
      Width           =   975
   End
   Begin Label lblReadOptions 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   16
      Top             =   1920
      Width           =   825
   End
   Begin Label lblShowOptions 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   7
      Top             =   1920
      Width           =   945
   End
   Begin Label lblOptions 
      Alignment       =   1  'Right Justify
      Caption         =   "Options:"
      Height          =   255
      Left            =   480
      TabIndex        =   22
      Top             =   1920
      Width           =   975
   End
   Begin Label lblReadHiChan 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   15
      Top             =   1680
      Width           =   825
   End
   Begin Label lblShowHiChan 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   6
      Top             =   1680
      Width           =   945
   End
   Begin Label lblHiChan 
      Alignment       =   1  'Right Justify
      Caption         =   "High Channel:"
      Height          =   255
      Left            =   120
      TabIndex        =   21
      Top             =   1680
      Width           =   1335
   End
   Begin Label lblReadLoChan 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   14
      Top             =   1440
      Width           =   825
   End
   Begin Label lblShowLoChan 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   5
      Top             =   1440
      Width           =   945
   End
   Begin Label lblLoChan 
      Alignment       =   1  'Right Justify
      Caption         =   "Low Channel:"
      Height          =   255
      Left            =   120
      TabIndex        =   20
      Top             =   1440
      Width           =   1335
   End
   Begin Label lblReadRate 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   3840
      TabIndex        =   13
      Top             =   1200
      Width           =   825
   End
   Begin Label lblShowRate 
      ForeColor       =   &H00FF0000&
      Height          =   270
      Left            =   1680
      TabIndex        =   4
      Top             =   1200
      Width           =   945
   End
   Begin Label lblRate 
      Alignment       =   1  'Right Justify
      Caption         =   "Rate:"
      Height          =   255
      Left            =   480
      TabIndex        =   19
      Top             =   1200
      Width           =   975
   End
   Begin Label lblInCol 
      Alignment       =   2  'Center
      Caption         =   "Params Read from File"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3360
      TabIndex        =   27
      Top             =   840
      Width           =   2175
   End
   Begin Label lblOutCol 
      Alignment       =   2  'Center
      Caption         =   "Params to Function"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   1320
      TabIndex        =   26
      Top             =   840
      Width           =   1815
   End
   Begin Label lblAcqStat 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   1200
      TabIndex        =   3
      Top             =   480
      Width           =   3375
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbFileAInScan%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   330
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5385
   End
End
'ULFI01================================================================

' File:                         ULFI01.FRM

' Library Call Demonstrated:    cbFileAInScan%()

' Purpose:                      Scan a range of A/D channels and store the
'                               data in a disk file.

' Demonstration:                Collects data points from one analog input
'                               channel and stores them in a file.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter and support cbFileAInScan.
'                               Analog signal on an input channel.
'                               

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0           ' Board number
Const NumPoints& = 128000    ' Number of data points to collect

Sub cmdStartAcq_Click ()

   cmdStartAcq.Enabled = 0
   cmdStartAcq.Visible = 0
   cmdStopConvert.Enabled = 1
   cmdStopConvert.Visible = 1

   ' Parameters:
   '   BoardNum%   :the number used by CB.CFG to describe this board
   '   LowChan%    :first A/D channel of the scan
   '   HighChan%   :last A/D channel of the scan
   '   CBCount&      :the total number of A/D samples to collect
   '   CBRate&     :Sample rate in samples per second
   '   Gain%       :the gain for the board
   '   FileName$   :the filename for the collected data values
   '   Options%    :data collection options


   CBCount& = NumPoints&
   FileName$ = txtFileName.Text    ' a full path may be required here
   CBRate& = 50000
   LowChan% = 0
   HighChan% = 1
   Options% = TIMED + NODTCONNECT
   Gain% = BIP5VOLTS

   DataCount$ = Format$(NumPoints&, "0")
   lblAcqStat.Caption = "Collecting " + DataCount$ + " data points"
   lblShowRate.Caption = Format$(CBRate&, "0")
   lblShowLoChan.Caption = Format$(LowChan%, "0")
   lblShowHiChan.Caption = Format$(HighChan%, "0")
   lblShowOptions.Caption = Format$(Options%, "0")
   lblShowGain.Caption = Format$(Gain%, "0")
   lblShowFile.Caption = FileName$
   lblShowCount.Caption = Format$(CBCount&, "0")
   lblShowPreTrig.Caption = "Not Applicable"
   Dummy% = DoEvents()

   ' Collect the values with cbFileAInScan%()

   ULStat% = cbFileAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain%, FileName$, Options%)
   If ULStat% = 502 Then
      MsgBox "Enter the name of the file to store the data in text box.", 0, "Bad File Name"
      cmdStopConvert.Enabled = 0
      cmdStopConvert.Visible = 0
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

   lblReadRate.Caption = Format$(CBRate&, "0")
   lblReadLoChan.Caption = Format$(LowChan%, "0")
   lblReadHiChan.Caption = Format$(HighChan%, "0")
   lblReadOptions.Caption = Format$(Options%, "0")
   lblReadGain.Caption = Format$(Range&, "0")
   lblReadFile.Caption = FileName$
   
   lblReadTotal.Caption = Format$(TotalCount&, "0")
   lblReadPreTrig.Caption = Format$(PreTrigCount&, "0")
  
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

