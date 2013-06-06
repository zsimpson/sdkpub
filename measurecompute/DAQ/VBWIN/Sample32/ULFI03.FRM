VERSION 2.00
Begin Form frmFilePreTrig 
   Caption         =   "Universal Library Analog Input to File"
   ClientHeight    =   5685
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5850
   ForeColor       =   &H00FF0000&
   Height          =   6090
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   5685
   ScaleWidth      =   5850
   Top             =   1200
   Width           =   5970
   Begin TextBox txtFileName 
      Height          =   375
      Left            =   2760
      TabIndex        =   63
      Text            =   "DEMO.DAT"
      Top             =   5220
      Width           =   2415
   End
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4680
      TabIndex        =   17
      Top             =   4440
      Width           =   780
   End
   Begin CommandButton cmdTrigEnable 
      Caption         =   "Enable Trigger"
      Enabled         =   0   'False
      Height          =   390
      Left            =   4320
      TabIndex        =   18
      Top             =   600
      Width           =   1455
   End
   Begin Frame fraInstruct 
      Height          =   735
      Left            =   120
      TabIndex        =   45
      Top             =   360
      Width           =   4095
      Begin CommandButton cmdLevelOK 
         Caption         =   "OK"
         Height          =   375
         Left            =   3480
         TabIndex        =   47
         Top             =   240
         Width           =   495
      End
      Begin Label lblInstruct 
         Alignment       =   2  'Center
         Caption         =   "Make sure that the trigger input is at a low level before starting."
         ForeColor       =   &H000000FF&
         Height          =   375
         Left            =   120
         TabIndex        =   46
         Top             =   240
         Width           =   3255
      End
   End
   Begin Label lblFileInstruct 
      Alignment       =   1  'Right Justify
      Caption         =   "Enter the name of the file in which to store the data."
      Height          =   615
      Left            =   120
      TabIndex        =   62
      Top             =   4980
      Width           =   2535
   End
   Begin Label lblShowGain 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   61
      Top             =   4710
      Width           =   780
   End
   Begin Label lblGain 
      Alignment       =   1  'Right Justify
      Caption         =   "Gain:"
      Height          =   210
      Left            =   690
      TabIndex        =   54
      Top             =   4710
      Width           =   1935
   End
   Begin Label lblShowRate 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   60
      Top             =   4515
      Width           =   780
   End
   Begin Label lblRate 
      Alignment       =   1  'Right Justify
      Caption         =   "Collection Rate:"
      Height          =   210
      Left            =   690
      TabIndex        =   53
      Top             =   4515
      Width           =   1935
   End
   Begin Label lblShowNumSam 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   59
      Top             =   4320
      Width           =   780
   End
   Begin Label lblNumSam 
      Alignment       =   1  'Right Justify
      Caption         =   "No. of Samples:"
      Height          =   210
      Left            =   690
      TabIndex        =   52
      Top             =   4320
      Width           =   1935
   End
   Begin Label lblShowPT 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   58
      Top             =   4125
      Width           =   780
   End
   Begin Label lblNumPTSam 
      Alignment       =   1  'Right Justify
      Caption         =   "No. of Pretrig Samples:"
      Height          =   210
      Left            =   450
      TabIndex        =   51
      Top             =   4125
      Width           =   2175
   End
   Begin Label lblShowHiChan 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   57
      Top             =   3930
      Width           =   780
   End
   Begin Label lblHiChan 
      Alignment       =   1  'Right Justify
      Caption         =   "High Channel:"
      Height          =   210
      Left            =   690
      TabIndex        =   50
      Top             =   3930
      Width           =   1935
   End
   Begin Label lblShowLoChan 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   56
      Top             =   3750
      Width           =   780
   End
   Begin Label lblLoChan 
      Alignment       =   1  'Right Justify
      Caption         =   "Low Channel:"
      Height          =   210
      Left            =   690
      TabIndex        =   49
      Top             =   3750
      Width           =   1935
   End
   Begin Label lblShowFileName 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2715
      TabIndex        =   55
      Top             =   3555
      Width           =   2745
   End
   Begin Label lblFileName 
      Alignment       =   1  'Right Justify
      Caption         =   "Streamer File Name:"
      Height          =   210
      Left            =   690
      TabIndex        =   48
      Top             =   3555
      Width           =   1935
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   10
      Left            =   4440
      TabIndex        =   42
      Top             =   3060
      Width           =   975
   End
   Begin Label lblPost10 
      Caption         =   "Trigger +10"
      Height          =   195
      Left            =   3240
      TabIndex        =   40
      Top             =   3060
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   9
      Left            =   1440
      TabIndex        =   22
      Top             =   3060
      Width           =   975
   End
   Begin Label lblPre1 
      Caption         =   "Trigger -1"
      Height          =   195
      Left            =   360
      TabIndex        =   20
      Top             =   3060
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   9
      Left            =   4440
      TabIndex        =   41
      Top             =   2880
      Width           =   975
   End
   Begin Label lblPost9 
      Caption         =   "Trigger +9"
      Height          =   255
      Left            =   3240
      TabIndex        =   39
      Top             =   2880
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   8
      Left            =   1440
      TabIndex        =   21
      Top             =   2880
      Width           =   975
   End
   Begin Label lblPre2 
      Caption         =   "Trigger -2"
      Height          =   195
      Left            =   360
      TabIndex        =   19
      Top             =   2880
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   8
      Left            =   4440
      TabIndex        =   38
      Top             =   2700
      Width           =   975
   End
   Begin Label lblPost8 
      Caption         =   "Trigger +8"
      Height          =   195
      Left            =   3240
      TabIndex        =   37
      Top             =   2700
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   7
      Left            =   1440
      TabIndex        =   16
      Top             =   2700
      Width           =   975
   End
   Begin Label lblPre3 
      Caption         =   "Trigger -3"
      Height          =   195
      Left            =   360
      TabIndex        =   8
      Top             =   2700
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   7
      Left            =   4440
      TabIndex        =   34
      Top             =   2520
      Width           =   975
   End
   Begin Label lblPost7 
      Caption         =   "Trigger +7"
      Height          =   210
      Left            =   3240
      TabIndex        =   33
      Top             =   2520
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   6
      Left            =   1440
      TabIndex        =   15
      Top             =   2520
      Width           =   975
   End
   Begin Label lblPre4 
      Caption         =   "Trigger -4"
      Height          =   195
      Left            =   360
      TabIndex        =   7
      Top             =   2520
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   6
      Left            =   4440
      TabIndex        =   30
      Top             =   2340
      Width           =   975
   End
   Begin Label lblPost6 
      Caption         =   "Trigger +6"
      Height          =   195
      Left            =   3240
      TabIndex        =   29
      Top             =   2340
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   5
      Left            =   1440
      TabIndex        =   14
      Top             =   2340
      Width           =   975
   End
   Begin Label lblPre5 
      Caption         =   "Trigger -5"
      Height          =   195
      Left            =   360
      TabIndex        =   6
      Top             =   2340
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   5
      Left            =   4440
      TabIndex        =   26
      Top             =   2160
      Width           =   975
   End
   Begin Label lblPost5 
      Caption         =   "Trigger +5"
      Height          =   195
      Left            =   3240
      TabIndex        =   25
      Top             =   2160
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   4
      Left            =   1440
      TabIndex        =   13
      Top             =   2160
      Width           =   975
   End
   Begin Label lblPre6 
      Caption         =   "Trigger -6"
      Height          =   195
      Left            =   360
      TabIndex        =   5
      Top             =   2160
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   4
      Left            =   4440
      TabIndex        =   36
      Top             =   1980
      Width           =   975
   End
   Begin Label lblPost4 
      Caption         =   "Trigger +4"
      Height          =   195
      Left            =   3240
      TabIndex        =   35
      Top             =   1980
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   1980
      Width           =   975
   End
   Begin Label lblPre7 
      Caption         =   "Trigger -7"
      Height          =   195
      Left            =   360
      TabIndex        =   4
      Top             =   1980
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   2
      Left            =   4440
      TabIndex        =   28
      Top             =   1800
      Width           =   975
   End
   Begin Label lblPost3 
      Caption         =   "Trigger +3"
      Height          =   195
      Left            =   3240
      TabIndex        =   31
      Top             =   1800
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   1800
      Width           =   975
   End
   Begin Label lblPre8 
      Caption         =   "Trigger -8"
      Height          =   195
      Left            =   360
      TabIndex        =   3
      Top             =   1800
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   3
      Left            =   4440
      TabIndex        =   32
      Top             =   1620
      Width           =   975
   End
   Begin Label lblPost2 
      Caption         =   "Trigger +2"
      Height          =   195
      Left            =   3240
      TabIndex        =   27
      Top             =   1620
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   1620
      Width           =   975
   End
   Begin Label lblPre9 
      Caption         =   "Trigger -9"
      Height          =   195
      Left            =   360
      TabIndex        =   2
      Top             =   1620
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   1
      Left            =   4440
      TabIndex        =   24
      Top             =   1440
      Width           =   975
   End
   Begin Label lblPost1 
      Caption         =   "Trigger +1"
      Height          =   195
      Left            =   3240
      TabIndex        =   23
      Top             =   1440
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   195
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   1440
      Width           =   975
   End
   Begin Label lblPre10 
      Caption         =   "Trigger -10"
      Height          =   195
      Left            =   360
      TabIndex        =   1
      Top             =   1440
      Width           =   1095
   End
   Begin Label lblPostTrigData 
      Caption         =   "Data acquired after trigger"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   210
      Left            =   2880
      TabIndex        =   44
      Top             =   1155
      Width           =   2460
   End
   Begin Label lblPreTrigData 
      Caption         =   "Data acquired before trigger"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   204
      Left            =   192
      TabIndex        =   43
      Top             =   1152
      Width           =   2412
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAPreTrig()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   330
      Left            =   330
      TabIndex        =   0
      Top             =   90
      Width           =   5175
   End
End
'ULFI03================================================================

' File:                         ULFI03.FRM

' Library Call Demonstrated:    File Operations:
'                               cbFilePretrig%()
'                               cbFileRead%()
'                               cbFileGetInfo%()

' Purpose:                      Stream data continuously to a streamer file
'                               until a trigger is received, continue data
'                               streaming until total number of samples minus
'                               the number of pretrigger samples is reached.

' Demonstration:                Creates a file and scans analog data to the
'                               file continuously, overwriting previous data.
'                               When a trigger is received, acquisition stops
'                               after (TotalCount& - PreTrigCount&) samples
'                               are stored. Displays the data in the file and
'                               the information in the file header. Prints
'                               data from PreTrigger-10 to PreTrigger+10.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter and support cbFilePretrig.
'                               Analog signal on an input channel.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0         ' Board number
Const TestPoints& = 128000  ' Number of data points to collect
Const BufSize& = TestPoints& + 512
                            ' set buffer size large enough to hold all data

Sub cmdLevelOK_Click ()

   cmdTrigEnable.Enabled = 1
   cmdLevelOK.Visible = 0
   lblInstruct.ForeColor = &HFF0000
   lblInstruct.Caption = "Click 'Enable Trigger' when ready..."

End Sub

Sub cmdQuit_Click ()
   End
End Sub

Sub cmdTrigEnable_Click ()

   lblInstruct.Caption = "Waiting for trigger."
   cmdTrigEnable.Enabled = 0
   Dummy% = DoEvents()
    
   ' Monitor a range of channels for a trigger then collect the values
   ' with cbAPretrig%()
   ' Parameters:
   '   BoardNum%      :the number used by CB.CFG to describe this board
   '   LowChan%       :first A/D channel of the scan
   '   HighChan%      :last A/D channel of the scan
   '   PretrigCount&  :number of pre-trigger A/D samples to collect
   '   TotalCount&    :total number of A/D samples to collect
   '   CBRate&        :sample rate in samples per second
   '   Gain%          :the gain for the board
   '   Options%       :data collection options

   TotalCount& = TestPoints&
   PretrigCount& = 200
   FileName$ = txtFileName.Text   ' it may be necessary to specify path here
   CBRate& = 50000
   LowChan% = 0
   HighChan% = 0
   Options% = TIMED + NODTCONNECT
   Gain% = BIP5VOLTS
 
   ULStat% = cbFilePretrig(BoardNum%, LowChan%, HighChan%, PretrigCount&, TotalCount&, CBRate&, Gain%, FileName$, Options%)
   If ULStat% = 502 Then
      MsgBox "Enter the name of the file to store the data in text box.", 0, "Bad File Name"
      cmdTrigEnable.Enabled = -1
      txtFileName.SetFocus
      Exit Sub
   ElseIf ULStat% <> 0 Then
      Stop
   End If

   ' show the information in the file header with cbFileGetInfo%()
   '  Parameters:
   '    FileName$      :the filename containing the data
   '    LowChan%       :first A/D channel of the scan
   '    HighChan%      :last A/D channel of the scan
   '    PreTrigCount&  :the number of pretrigger samples in the file
   '    CBCount&       :the total number of A/D samples in the file
   '    CBRate&        :sample rate in samples per second
   '    Gain%          :the gain at which the samples were collected

   ULStat% = cbFileGetInfo(FileName$, LowChan%, HighChan%, PretrigCount&, TotalCount&, CBRate&, Range&)
   If ULStat% <> 0 Then Stop

   lblShowFileName.Caption = FileName$
   lblShowLoChan.Caption = Format$(LowChan%, "0")
   lblShowHiChan.Caption = Format$(HighChan%, "0")
   lblShowPT.Caption = Format$(PretrigCount&, "0")
   lblShowNumSam.Caption = Format$(TotalCount&, "0")
   lblShowRate.Caption = Format$(CBRate&, "0")
   lblShowGain.Caption = Format$(Range&, "0")
 
   ' show the data using cbFileRead%()
   '  Parameters:
   '    FileName$      :the filename containing the data
   '    NumPoints&     :the number of data values to read from the file
   '    FirstPoint&    :index of the first data value to read
   '    DataBuffer%()  :array to read data into

   NumPoints& = 20                   ' read the first twenty data points
   FirstPoint& = PretrigCount& - 10  ' start at the trigger - 10
   ReDim DataBuffer%(NumPoints&)
 
   ULStat% = cbFileRead(FileName$, FirstPoint&, NumPoints&, DataBuffer%(0))
   If ULStat% <> 0 Then Stop
 
   For i% = 0 To 9
      lblPreTrig(i%).Caption = Format$(DataBuffer%(i%), "0")
   Next i%
   For i% = 1 To 10
      lblPostTrig(i%).Caption = Format$(DataBuffer%(9 + i%), "0")
   Next i%
   cmdTrigEnable.Enabled = 0
   lblInstruct.Caption = "Make sure that the trigger input is at a low level before starting."
   lblInstruct.ForeColor = &HFF
   cmdLevelOK.Visible = 1
   cmdTrigEnable.Enabled = -1

End Sub

Sub Form_Load ()

   ' declare revision level of Universal Library

   ULStat% = cbDeclareRevision(CURRENTREVNUM)
   
   ' Initiate error handling
   ' activating error handling will trap errors like
   ' bad channel numbers and non-configured conditions.
   ' Parameters:
   '   PRINTALL    :all warnings and errors encountered will be printed
   '   DONTSTOP    :if an error is encountered, the program will not stop,
   '                errors must be handled locally
     
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop
   
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.

End Sub

