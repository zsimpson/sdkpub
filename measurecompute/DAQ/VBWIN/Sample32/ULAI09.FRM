VERSION 2.00
Begin Form frmPreTrig 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   4980
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5760
   ForeColor       =   &H00FF0000&
   Height          =   5385
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4980
   ScaleWidth      =   5760
   Top             =   1200
   Width           =   5880
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4320
      TabIndex        =   17
      Top             =   4320
      Width           =   780
   End
   Begin CommandButton cmdTrigEnable 
      Caption         =   "Enable Trigger"
      Enabled         =   0   'False
      Height          =   390
      Left            =   4200
      TabIndex        =   18
      Top             =   960
      Width           =   1455
   End
   Begin Frame fraInstruct 
      Height          =   855
      Left            =   120
      TabIndex        =   45
      Top             =   720
      Width           =   3975
      Begin CommandButton cmdLevelOK 
         Caption         =   "OK"
         Height          =   495
         Left            =   3360
         TabIndex        =   47
         Top             =   240
         Width           =   495
      End
      Begin Label lblInstruct 
         Alignment       =   2  'Center
         Caption         =   "Make sure that the trigger input is at a low level before starting."
         ForeColor       =   &H000000FF&
         Height          =   495
         Left            =   120
         TabIndex        =   46
         Top             =   240
         Width           =   3135
      End
   End
   Begin Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4716
      Top             =   96
   End
   Begin Label lblShowCount 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3000
      TabIndex        =   52
      Top             =   4560
      Width           =   510
   End
   Begin Label lblCount 
      Caption         =   "Count:"
      Height          =   210
      Left            =   2130
      TabIndex        =   49
      Top             =   4560
      Width           =   825
   End
   Begin Label lblShowIndex 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   2970
      TabIndex        =   53
      Top             =   4320
      Width           =   615
   End
   Begin Label lblIndex 
      Caption         =   "Index:"
      Height          =   210
      Left            =   2160
      TabIndex        =   51
      Top             =   4320
      Width           =   825
   End
   Begin Label lblShowStat 
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   960
      TabIndex        =   50
      Top             =   4320
      Width           =   1050
   End
   Begin Label lblStatus 
      Caption         =   "Status:"
      Height          =   210
      Left            =   240
      TabIndex        =   48
      Top             =   4320
      Width           =   705
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   10
      Left            =   4155
      TabIndex        =   42
      Top             =   3810
      Width           =   975
   End
   Begin Label lblPost10 
      Caption         =   "Trigger +10"
      Height          =   210
      Left            =   3090
      TabIndex        =   40
      Top             =   3810
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   9
      Left            =   1440
      TabIndex        =   22
      Top             =   3810
      Width           =   975
   End
   Begin Label lblPre1 
      Caption         =   "Trigger -1"
      Height          =   210
      Left            =   270
      TabIndex        =   20
      Top             =   3810
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   9
      Left            =   4155
      TabIndex        =   41
      Top             =   3630
      Width           =   975
   End
   Begin Label lblPost9 
      Caption         =   "Trigger +9"
      Height          =   210
      Left            =   3090
      TabIndex        =   39
      Top             =   3630
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   8
      Left            =   1440
      TabIndex        =   21
      Top             =   3630
      Width           =   975
   End
   Begin Label lblPre2 
      Caption         =   "Trigger -2"
      Height          =   210
      Left            =   270
      TabIndex        =   19
      Top             =   3630
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   8
      Left            =   4155
      TabIndex        =   38
      Top             =   3435
      Width           =   975
   End
   Begin Label lblPost8 
      Caption         =   "Trigger +8"
      Height          =   210
      Left            =   3090
      TabIndex        =   37
      Top             =   3435
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   7
      Left            =   1440
      TabIndex        =   16
      Top             =   3435
      Width           =   975
   End
   Begin Label lblPre3 
      Caption         =   "Trigger -3"
      Height          =   210
      Left            =   270
      TabIndex        =   8
      Top             =   3435
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   7
      Left            =   4155
      TabIndex        =   34
      Top             =   3240
      Width           =   975
   End
   Begin Label lblPost7 
      Caption         =   "Trigger +7"
      Height          =   210
      Left            =   3090
      TabIndex        =   33
      Top             =   3240
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   6
      Left            =   1440
      TabIndex        =   15
      Top             =   3240
      Width           =   975
   End
   Begin Label lblPre4 
      Caption         =   "Trigger -4"
      Height          =   210
      Left            =   270
      TabIndex        =   7
      Top             =   3240
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   6
      Left            =   4155
      TabIndex        =   30
      Top             =   3045
      Width           =   975
   End
   Begin Label lblPost6 
      Caption         =   "Trigger +6"
      Height          =   210
      Left            =   3090
      TabIndex        =   29
      Top             =   3045
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   5
      Left            =   1440
      TabIndex        =   14
      Top             =   3045
      Width           =   975
   End
   Begin Label lblPre5 
      Caption         =   "Trigger -5"
      Height          =   210
      Left            =   270
      TabIndex        =   6
      Top             =   3045
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   5
      Left            =   4155
      TabIndex        =   26
      Top             =   2850
      Width           =   975
   End
   Begin Label lblPost5 
      Caption         =   "Trigger +5"
      Height          =   210
      Left            =   3090
      TabIndex        =   25
      Top             =   2850
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   4
      Left            =   1440
      TabIndex        =   13
      Top             =   2850
      Width           =   975
   End
   Begin Label lblPre6 
      Caption         =   "Trigger -6"
      Height          =   210
      Left            =   270
      TabIndex        =   5
      Top             =   2850
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   4
      Left            =   4155
      TabIndex        =   36
      Top             =   2670
      Width           =   975
   End
   Begin Label lblPost4 
      Caption         =   "Trigger +4"
      Height          =   210
      Left            =   3090
      TabIndex        =   35
      Top             =   2670
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   2670
      Width           =   975
   End
   Begin Label lblPre7 
      Caption         =   "Trigger -7"
      Height          =   210
      Left            =   270
      TabIndex        =   4
      Top             =   2670
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   3
      Left            =   4155
      TabIndex        =   32
      Top             =   2475
      Width           =   975
   End
   Begin Label lblPost3 
      Caption         =   "Trigger +3"
      Height          =   210
      Left            =   3090
      TabIndex        =   31
      Top             =   2475
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   2475
      Width           =   975
   End
   Begin Label lblPre8 
      Caption         =   "Trigger -8"
      Height          =   210
      Left            =   270
      TabIndex        =   3
      Top             =   2475
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   2
      Left            =   4155
      TabIndex        =   28
      Top             =   2280
      Width           =   975
   End
   Begin Label lblPost2 
      Caption         =   "Trigger +2"
      Height          =   210
      Left            =   3090
      TabIndex        =   27
      Top             =   2280
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   2280
      Width           =   975
   End
   Begin Label lblPre9 
      Caption         =   "Trigger -9"
      Height          =   210
      Left            =   270
      TabIndex        =   2
      Top             =   2280
      Width           =   1095
   End
   Begin Label lblPostTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   1
      Left            =   4155
      TabIndex        =   24
      Top             =   2085
      Width           =   975
   End
   Begin Label lblPost1 
      Caption         =   "Trigger +1"
      Height          =   210
      Left            =   3090
      TabIndex        =   23
      Top             =   2085
      Width           =   1095
   End
   Begin Label lblPreTrig 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   210
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   2085
      Width           =   975
   End
   Begin Label lblPre10 
      Caption         =   "Trigger -10"
      Height          =   210
      Left            =   270
      TabIndex        =   1
      Top             =   2085
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
      Left            =   3000
      TabIndex        =   44
      Top             =   1800
      Width           =   2580
   End
   Begin Label lblPreTrigData 
      Caption         =   "Data acquired before trigger"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   210
      Left            =   195
      TabIndex        =   43
      Top             =   1800
      Width           =   2655
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAPreTrig() in BACKGROUND mode"
      Height          =   630
      Left            =   165
      TabIndex        =   0
      Top             =   90
      Width           =   5505
   End
End
'ULAI09.MAK================================================================

' File:                         ULAI09.MAK

' Library Call Demonstrated:    cbAConvertPretrigData%()

' Purpose:                      Waits for a trigger with cbAPretrig%(), then
'                               uses cbAConvertPretrigData%() to convert
'                               the data.

' Demonstration:                Displays the analog input on one channel and
'                               waits for the trigger.

' Other Library Calls:          cbAPretrig%()
'                               cbGetStatus%()
'                               cbStopBackground%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must support cbAPretrig.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const NumPoints& = 600          ' Number of data points to collect
Const FirstPoint& = 0           ' set first element in buffer to transfer to array
Const PretrigCount& = 10        ' number of data points before the trigger to store
Const TotalCount& = NumPoints&  ' total number of data points to collect
Const BufSize& = 1112           ' buffer must be large enough to hold all data

Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ADData%(BufSize&)           ' dimension an array to hold the input values
                                ' size must be TotalCount + 512 minimum
Dim ChanTags%(BufSize&)         ' dimension an array to hold the channel tag values

Sub cmdLevelOK_Click ()

   cmdTrigEnable.Enabled = 1
   cmdLevelOK.Visible = 0
   lblInstruct.ForeColor = &HFF0000
   lblInstruct.Caption = "Click 'Enable Trigger' when ready..."

End Sub

Sub cmdQuit_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat% <> 0 Then Stop                ' other programs
  
   ' The BACKGROUND operation must be explicitly stopped
  
   ULStat% = cbStopBackground(BoardNum%,AIFUNCTION)
   If ULStat% <> 0 Then Stop
   End

End Sub

Sub cmdTrigEnable_Click ()

   lblInstruct.Caption = "Waiting for trigger."
  
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

   LowChan% = 0                  ' first channel
   HighChan% = 0                 ' last channel
   CBRate& = 100                 ' sampling rate (samples per second)
   Gain = BIP5VOLTS              ' set the gain
   Options = BACKGROUND          ' collect data in the background
 
   ULStat% = cbAPretrig(BoardNum%, LowChan%, HighChan%, PretrigCount&, TotalCount&, CBRate&, Gain, MemHandle&, Options)
   If ULStat% <> 0 Then Stop
   
   tmrCheckStatus.Enabled = 1

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

   MemHandle& = cbWinBufAlloc(BufSize&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

End Sub

Sub tmrCheckStatus_Timer ()

   ' This timer will check the status of the background data collection
   
   ' Parameters:
   '   BoardNum%   :the number used by CB.CFG to describe this board
   '   Status%     :current status of the background data collection
   '   CurCount&   :current number of samples collected
   '   CurIndex&   :index to the data buffer pointing to the start of the
   '                most recently collected scan
   '   FunctionType:A/D operation (AIFUNCTIOM)

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
   If ULStat% <> 0 Then Stop

   lblShowCount.Caption = Format$(CurCount&, "0")
   lblShowIndex.Caption = Format$(CurIndex&, "0")
   
   ' Check if the background operation has finished. If it has, then
   ' transfer the data from the memory buffer set up by Windows to an
   ' array for use by Visual Basic
   ' The BACKGROUND operation must be explicitly stopped
    
   If Status% = RUNNING Then
      lblShowStat.Caption = "Running"
   ElseIf Status% = 0 Then
      lblShowStat.Caption = "Idle"

      ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
      If ULStat% <> 0 Then Stop

      lblShowCount.Caption = Format$(CurCount&, "0")
      lblShowIndex.Caption = Format$(CurIndex&, "0")
     
      ULStat% = cbStopBackground(BoardNum%,AIFUNCTION)

      If ULStat% <> 0 Then Stop

      tmrCheckStatus.Enabled = 0
      If MemHandle& = 0 Then Stop

      ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

      ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, NumPoints&)
      If ULStat% <> 0 Then Stop
            
      ' convert the data using cbAConvertPretrigData%()

      ' Parameters:
      '   PretrigCount&  :number of pre-trigger A/D samples collected
      '                   actual value is returned by cbAPretrig%()
      '   TotalCount&    :total number of A/D samples collected
      '                   actual value is returned by cbAPretrig%()
      '   ADData%        :the array containing the raw data values
      '   ChanTags%      :array that chan tags will be returned to

      ULStat% = cbAConvertPretrigData(BoardNum%, PretrigCount&, TotalCount&, ADData%(0), ChanTags%(0))
      If ULStat% <> 0 Then Stop
      
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
   End If

End Sub

