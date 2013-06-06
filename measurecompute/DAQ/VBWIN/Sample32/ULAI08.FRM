VERSION 2.00
Begin Form frmPreTrig 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   4080
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5625
   ForeColor       =   &H00FF0000&
   Height          =   4485
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4080
   ScaleWidth      =   5625
   Top             =   1200
   Width           =   5745
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4440
      TabIndex        =   17
      Top             =   3600
      Width           =   780
   End
   Begin CommandButton cmdTrigEnable 
      Caption         =   "Enable Trigger"
      Enabled         =   0   'False
      Height          =   375
      Left            =   4080
      TabIndex        =   18
      Top             =   600
      Width           =   1455
   End
   Begin Frame frmInstruct 
      Height          =   735
      Left            =   120
      TabIndex        =   45
      Top             =   360
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
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   10
      Left            =   4155
      TabIndex        =   42
      Top             =   3165
      Width           =   975
   End
   Begin Label lblPost10 
      Caption         =   "Trigger +10"
      Height          =   210
      Left            =   2970
      TabIndex        =   40
      Top             =   3165
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   9
      Left            =   1440
      TabIndex        =   22
      Top             =   3168
      Width           =   972
   End
   Begin Label lblPre1 
      Caption         =   "Trigger -1"
      Height          =   210
      Left            =   270
      TabIndex        =   20
      Top             =   3165
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   9
      Left            =   4155
      TabIndex        =   41
      Top             =   2970
      Width           =   975
   End
   Begin Label lblPost9 
      Caption         =   "Trigger +9"
      Height          =   210
      Left            =   2970
      TabIndex        =   39
      Top             =   2970
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   8
      Left            =   1440
      TabIndex        =   21
      Top             =   2976
      Width           =   972
   End
   Begin Label lblPre2 
      Caption         =   "Trigger -2"
      Height          =   210
      Left            =   270
      TabIndex        =   19
      Top             =   2970
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   8
      Left            =   4155
      TabIndex        =   38
      Top             =   2790
      Width           =   975
   End
   Begin Label lblPost8 
      Caption         =   "Trigger +8"
      Height          =   210
      Left            =   2970
      TabIndex        =   37
      Top             =   2790
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   7
      Left            =   1440
      TabIndex        =   16
      Top             =   2784
      Width           =   972
   End
   Begin Label lblPre3 
      Caption         =   "Trigger -3"
      Height          =   210
      Left            =   270
      TabIndex        =   8
      Top             =   2790
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   7
      Left            =   4155
      TabIndex        =   34
      Top             =   2595
      Width           =   975
   End
   Begin Label lblPost7 
      Caption         =   "Trigger +7"
      Height          =   210
      Left            =   2970
      TabIndex        =   33
      Top             =   2595
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   6
      Left            =   1440
      TabIndex        =   15
      Top             =   2592
      Width           =   972
   End
   Begin Label lblPre4 
      Caption         =   "Trigger -4"
      Height          =   210
      Left            =   270
      TabIndex        =   7
      Top             =   2595
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   6
      Left            =   4155
      TabIndex        =   30
      Top             =   2400
      Width           =   975
   End
   Begin Label lblPost6 
      Caption         =   "Trigger +6"
      Height          =   210
      Left            =   2970
      TabIndex        =   29
      Top             =   2400
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   5
      Left            =   1440
      TabIndex        =   14
      Top             =   2400
      Width           =   972
   End
   Begin Label lblPre5 
      Caption         =   "Trigger -5"
      Height          =   210
      Left            =   270
      TabIndex        =   6
      Top             =   2400
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   5
      Left            =   4155
      TabIndex        =   26
      Top             =   2205
      Width           =   975
   End
   Begin Label lblPost5 
      Caption         =   "Trigger +5"
      Height          =   210
      Left            =   2970
      TabIndex        =   25
      Top             =   2205
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   4
      Left            =   1440
      TabIndex        =   13
      Top             =   2208
      Width           =   972
   End
   Begin Label lblPre6 
      Caption         =   "Trigger -6"
      Height          =   210
      Left            =   270
      TabIndex        =   5
      Top             =   2205
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   4
      Left            =   4155
      TabIndex        =   36
      Top             =   2010
      Width           =   975
   End
   Begin Label lblPost4 
      Caption         =   "Trigger +4"
      Height          =   210
      Left            =   2970
      TabIndex        =   35
      Top             =   2010
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   2016
      Width           =   972
   End
   Begin Label lblPre7 
      Caption         =   "Trigger -7"
      Height          =   210
      Left            =   270
      TabIndex        =   4
      Top             =   2010
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   3
      Left            =   4155
      TabIndex        =   32
      Top             =   1830
      Width           =   975
   End
   Begin Label lblPost3 
      Caption         =   "Trigger +3"
      Height          =   210
      Left            =   2970
      TabIndex        =   31
      Top             =   1830
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   1824
      Width           =   972
   End
   Begin Label lblPre8 
      Caption         =   "Trigger -8"
      Height          =   210
      Left            =   270
      TabIndex        =   3
      Top             =   1830
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   2
      Left            =   4155
      TabIndex        =   28
      Top             =   1635
      Width           =   975
   End
   Begin Label lblPost2 
      Caption         =   "Trigger +2"
      Height          =   210
      Left            =   2970
      TabIndex        =   27
      Top             =   1635
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   1632
      Width           =   972
   End
   Begin Label lblPre9 
      Caption         =   "Trigger -9"
      Height          =   210
      Left            =   270
      TabIndex        =   2
      Top             =   1635
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   1
      Left            =   4155
      TabIndex        =   24
      Top             =   1440
      Width           =   975
   End
   Begin Label lblPost1 
      Caption         =   "Trigger +1"
      Height          =   210
      Left            =   2970
      TabIndex        =   23
      Top             =   1440
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   204
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   1440
      Width           =   972
   End
   Begin Label lblPre10 
      Caption         =   "Trigger -10"
      Height          =   210
      Left            =   270
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
      Height          =   330
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   5415
   End
End
'ULAI08.MAK================================================================

' File:                         ULAI08.MAK

' Library Call Demonstrated:    cbAPretrig%()

' Purpose:                      Waits for a trigger, then returns a specified
'                               number of analog samples before and after
'                               the trigger.

' Demonstration:                Displays the analog input on one channel and
'                               waits for the trigger.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must support cbAPretrig.
'                               Analog signal on an input channel.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const NumPoints& = 600          ' Number of data points to collect
Const FirstPoint& = 0           ' set first element in buffer to transfer to array
Const PretrigCount& = 10        ' number of data points before trigger to store
Const TotalCount& = NumPoints&  ' total number of data points to collect
Const BufSize& = 1112           ' set buffer size large enough to hold all data

Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ADData%(BufSize&)           ' dimension an array to hold the input values
                                ' size must be TotalCount + 512 minimum

Sub cmdLevelOK_Click ()

   cmdTrigEnable.Enabled = 1
   cmdLevelOK.Visible = 0
   lblInstruct.ForeColor = &HFF0000
   lblInstruct.Caption = "Click 'Enable Trigger' when ready..."

End Sub

Sub cmdQuit_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat% <> 0 Then End                 ' other programs
   End

End Sub

Sub cmdTrigEnable_Click ()

   lblInstruct.Caption = "Waiting for trigger."
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
   '   Gain           :the gain for the board
   '   ADData%        :the array for the collected data values
   '   Options        :data collection options

   LowChan% = 0
   HighChan% = 0
   CBRate& = 1000                     ' sampling rate (samples per second)
   Gain = BIP5VOLTS                  ' set the gain
   Options = CONVERTDATA             ' return data as 12-bit values

   ULStat% = cbAPretrig(BoardNum%, LowChan%, HighChan%, PretrigCount&, TotalCount&, CBRate&, Gain, MemHandle&, Options)
   If ULStat% <> 0 Then End

   ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

   ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, NumPoints&)
   If ULStat% <> 0 Then End

   For i% = 0 To PretrigCount& - 1
      lblPreTrig(i%).Caption = Format$(ADData%(i%), "0")
   Next i%
   For i% = 1 To 10
      lblPostTrig(i%).Caption = Format$(ADData%(PretrigCount& + i%), "0")
   Next i%
   cmdTrigEnable.Enabled = 0
   lblInstruct.Caption = "Make sure that the trigger input is at a low level before starting."
   lblInstruct.ForeColor = &HFF
   cmdLevelOK.Visible = 1

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
   If ULStat% <> 0 Then End
   
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
    
   MemHandle& = cbWinBufAlloc(BufSize&)      ' set aside memory to hold data
   If MemHandle& = 0 Then End

End Sub

