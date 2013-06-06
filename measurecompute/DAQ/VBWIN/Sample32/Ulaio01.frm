VERSION 2.00
Begin Form frmStatusDisplay 
   Caption         =   "Simultaneous cbAInScan%() and cbAoutScan%() "
   ClientHeight    =   5280
   ClientLeft      =   2820
   ClientTop       =   1620
   ClientWidth     =   9165
   Height          =   5685
   Left            =   2670
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   5280
   ScaleWidth      =   9165
   Top             =   1155
   Width           =   9285
   Begin CommandButton cmdStopADConvert 
      Caption         =   "Stop A/D Background Operation"
      Enabled         =   0   'False
      Height          =   396
      Left            =   840
      TabIndex        =   33
      Top             =   1800
      Visible         =   0   'False
      Width           =   3060
   End
   Begin CommandButton cmdStartDABgnd 
      Caption         =   "Start D/A Background Operation"
      Height          =   396
      Left            =   5280
      TabIndex        =   32
      Top             =   1800
      Width           =   3060
   End
   Begin CommandButton cmdStopDAConvert 
      Caption         =   "Stop D/A Background Operation"
      Enabled         =   0   'False
      Height          =   396
      Left            =   5280
      TabIndex        =   31
      Top             =   1800
      Visible         =   0   'False
      Width           =   3060
   End
   Begin TextBox txtHighChan 
      Height          =   285
      Left            =   3360
      TabIndex        =   25
      Text            =   "3"
      Top             =   2400
      Width           =   495
   End
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4320
      TabIndex        =   18
      Top             =   4440
      Width           =   780
   End
   Begin Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4380
      Top             =   2040
   End
   Begin CommandButton cmdStartADBgnd 
      Caption         =   "Start A/D Background Operation"
      Height          =   396
      Left            =   840
      TabIndex        =   17
      Top             =   1800
      Width           =   3060
   End
   Begin Label lblCount 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Current A/D Count:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   1050
      TabIndex        =   36
      Top             =   4650
      Width           =   1860
   End
   Begin Label Label2 
      Alignment       =   1  'Right Justify
      BackColor       =   &H80000005&
      Caption         =   "Current D/A Count:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   5400
      TabIndex        =   35
      Top             =   4650
      Width           =   2025
   End
   Begin Label Label5 
      Caption         =   "Board 0 must support simultaneous paced input and paced output. For more inforamtion, see hardware documentation."
      Height          =   495
      Left            =   1560
      TabIndex        =   34
      Top             =   720
      Width           =   5775
   End
   Begin Label Label4 
      Alignment       =   1  'Right Justify
      BackColor       =   &H80000005&
      Caption         =   "Status of D/A Background:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   4605
      TabIndex        =   30
      Top             =   4080
      Width           =   2820
   End
   Begin Label Label3 
      Alignment       =   1  'Right Justify
      BackColor       =   &H80000005&
      Caption         =   "Current D/A Index:"
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   5400
      TabIndex        =   29
      Top             =   4365
      Width           =   2025
   End
   Begin Label lblShowDACount 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   7560
      TabIndex        =   28
      Top             =   4680
      Width           =   975
   End
   Begin Label lblShowDAIndex 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   195
      Left            =   7440
      TabIndex        =   27
      Top             =   4380
      Width           =   1065
   End
   Begin Label lblShowDAStat 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   7440
      TabIndex        =   26
      Top             =   4080
      Width           =   990
   End
   Begin Label Label1 
      BackColor       =   &H80000005&
      Caption         =   "Measure Channels 0 to"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1200
      TabIndex        =   24
      Top             =   2400
      Width           =   2055
   End
   Begin Label lblShowADCount 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3090
      TabIndex        =   23
      Top             =   4680
      Width           =   1095
   End
   Begin Label lblShowADIndex 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   210
      Left            =   3090
      TabIndex        =   22
      Top             =   4365
      Width           =   1005
   End
   Begin Label lblIndex 
      Alignment       =   1  'Right Justify
      BackColor       =   &H80000005&
      Caption         =   "Current A/D Index:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   1005
      TabIndex        =   21
      Top             =   4365
      Width           =   1905
   End
   Begin Label lblShowADStat 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   330
      Left            =   3000
      TabIndex        =   20
      Top             =   4080
      Width           =   1215
   End
   Begin Label lblStatus 
      Alignment       =   1  'Right Justify
      BackColor       =   &H80000005&
      Caption         =   "Status of A/D Background:"
      ForeColor       =   &H80000008&
      Height          =   210
      Left            =   450
      TabIndex        =   19
      Top             =   4080
      Width           =   2460
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   4080
      TabIndex        =   16
      Top             =   3570
      Width           =   975
   End
   Begin Label lblChan7 
      BackColor       =   &H80000005&
      Caption         =   "Channel 7:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   3000
      TabIndex        =   8
      Top             =   3570
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1560
      TabIndex        =   12
      Top             =   3570
      Width           =   975
   End
   Begin Label lblChan3 
      BackColor       =   &H80000005&
      Caption         =   "Channel 3:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   4
      Top             =   3570
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   4080
      TabIndex        =   15
      Top             =   3285
      Width           =   975
   End
   Begin Label lblChan6 
      BackColor       =   &H80000005&
      Caption         =   "Channel 6:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   3000
      TabIndex        =   7
      Top             =   3285
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1560
      TabIndex        =   11
      Top             =   3285
      Width           =   975
   End
   Begin Label lblChan2 
      BackColor       =   &H80000005&
      Caption         =   "Channel 2:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   3
      Top             =   3285
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   4080
      TabIndex        =   14
      Top             =   3000
      Width           =   975
   End
   Begin Label lblChan5 
      BackColor       =   &H80000005&
      Caption         =   "Channel 5:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   3000
      TabIndex        =   6
      Top             =   3000
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1560
      TabIndex        =   10
      Top             =   3000
      Width           =   975
   End
   Begin Label lblChan1 
      BackColor       =   &H80000005&
      Caption         =   "Channel 1:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   2
      Top             =   3000
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   4080
      TabIndex        =   13
      Top             =   2715
      Width           =   975
   End
   Begin Label lblChan4 
      BackColor       =   &H80000005&
      Caption         =   "Channel 4:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   3000
      TabIndex        =   5
      Top             =   2715
      Width           =   975
   End
   Begin Label lblADData 
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1560
      TabIndex        =   9
      Top             =   2715
      Width           =   975
   End
   Begin Label lblChan0 
      BackColor       =   &H80000005&
      Caption         =   "Channel 0:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   1
      Top             =   2715
      Width           =   975
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of Simultaneous cbAInScan%() and cbAoutScan "
      ForeColor       =   &H80000008&
      Height          =   495
      Left            =   1200
      TabIndex        =   0
      Top             =   120
      Width           =   6255
   End
End
'ULAIO01.FRM================================================================

' File:                         ULAIO01.FRM

' Library Call Demonstrated:    cbGetStatus%()
'                               cbStopBackground%()

' Purpose:                      Run Simultaneous input/output functions using
'                               the same board.

' Demonstration:                cbAoutScan function generates a ramp signal
'                               while cbAinScan Displays the analog input on
'                               eight channels.

' Other Library Calls:          cbAinScan%()
'                               cbAoutScan%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must support simultaneous paced input
'                               and paced output. See hardware documentation.

' (c) Copyright 2000-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const NumPoints& = 30000        ' Number of data points to collect
Const FirstPoint& = 0           ' set first element in buffer to transfer to array

Dim ADData%(NumPoints&)         ' dimension an array to hold the input values
Dim ADUserTerm%                 ' flag to stop paced A/D manually
Dim ADMemHandle&                ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim DAMemHandle&                ' define a variable to contain the handle for
Dim DAData%(NumPoints&)         ' dimension an array to hold the output values
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim DAUserTerm%                 ' flag to stop paced D/A manually
Dim HighChan%

Private Sub cmdQuit_Click()
   
   ULStat% = cbWinBufFree(ADMemHandle&)     ' Free up memory for use by
                                            ' other programs
                                            
   ULStat% = cbWinBufFree(DAMemHandle&)
                                            
   If ULStat% <> 0 Then Stop
   End
   
End Sub

Private Sub cmdStartBgnd_Click()


End Sub

Private Sub cmdStopConvert_Click()

   ADUserTerm% = 1

End Sub

Private Sub cmdStartADBgnd_Click()
   cmdStartADBgnd.Enabled = 0
   cmdStartADBgnd.Visible = 0
   cmdStopADConvert.Enabled = 1
   cmdStopADConvert.Visible = 1
   cmdQuit.Enabled = 0
   ADUserTerm% = 0                     ' initialize user terminate flag

   ' Collect the values with cbAInScan%()
   '  Parameters:
   '    BoardNum%   :the number used by CB.CFG to describe this board
   '    LowChan%    :the first channel of the scan
   '    HighChan%   :the last channel of the scan
   '    CBCount&    :the total number of A/D samples to collect
   '    CBRate&     :sample rate
   '    Gain        :the gain for the board
   '    ADData%     :the array for the collected data values
   '    Options     :data collection options

   LowChan% = 0                     ' first channel to acquire
   HighChan% = Val(txtHighChan.Text) ' last channel to acquire
   If (HighChan% > 7) Then HighChan% = 7
   txtHighChan.Text = Str(HighChan%)
   
   CBADCount& = NumPoints&            ' total number of data points to collect
   CBADRate& = 500                    ' sampling rate (samples per second)
   ADOptions& = CONVERTDATA + BACKGROUND
                                    ' return data as 12-bit values
                                    ' collect data in BACKGROUND mode
                                    ' use NOCONVERTDATA if using 16 bit board
   Gain% = BIP5VOLTS                ' set the gain

   If ADMemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBADCount&, CBADRate&, Gain%, ADMemHandle&, ADOptions&)
   
   If ULStat% = 84 Then
      MsgBox "The CONVERT option cannot be used with 16 bit convertors. Set Options to NOCONVERTDATA."
      Stop   'Change CONVERTDATA in Options above to NOCONVERTDATA
   End If

   If ULStat% <> 0 Then Stop

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, AIFUNCTION)
   If ULStat% <> 0 Then Stop

   If Status% = RUNNING Then
      lblShowADStat.Caption = "Running"
      lblShowADCount.Caption = Format$(CurCount&, "0")
      lblShowADIndex.Caption = Format$(CurIndex&, "0")
   End If

   tmrCheckStatus.Enabled = 1


End Sub

Private Sub cmdStartDABgnd_Click()

   cmdStartDABgnd.Enabled = 0
   cmdStartDABgnd.Visible = 0
   cmdStopDAConvert.Enabled = 1
   cmdStopDAConvert.Visible = 1
   cmdQuit.Enabled = 0
   DAUserTerm% = 0                     ' initialize user terminate flag
  
   ' Collect the values with cbAoutnScan%()
   '  Parameters:
   '    BoardNum%   :the number used by CB.CFG to describe this board
   '    LowDAChan%    :the first channel of the scan
   '    HighDAChan%   :the last channel of the scan
   '    CBCount&    :the total number of D/A samples to output
   '    CBRate&     :sample rate
   '    Gain        :the gain for the board
   '   DAData%     :array of values to send to the scanned channels
   '    Options     :data output options

   LowDAChan% = 0                     ' first channel to output
   HighDAChan% = 0                    ' last channel to output
   
   CBDACount& = NumPoints&            ' total number of data points to output
   CBDARate& = 1000                   ' output rate (samples per second)
   DAOptions& = BACKGROUND                 
   Gain% = BIP5VOLTS                ' set the gain

   If DAMemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists

   ULStat% = cbAOutScan(BoardNum%, LowDAChan%, HighDAChan%, CBDACount&, CBDARate&, Gain%, DAMemHandle&, DAOptions&)
   
   If ULStat% <> 0 Then Stop

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&, AOFUNCTION)
   If ULStat% <> 0 Then Stop

   If Status% = RUNNING Then
      lblShowDAStat.Caption = "Running"
      lblShowDACount.Caption = Format$(CurCount&, "0")
      lblShowDAIndex.Caption = Format$(CurIndex&, "0")
   End If

   tmrCheckStatus.Enabled = 1


End Sub

Private Sub cmdStopADConvert_Click()
   ADUserTerm% = 1

End Sub

Private Sub cmdStopDAConvert_Click()
    DAUserTerm% = 1
End Sub

Private Sub Form_Load()
   
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

   ADMemHandle& = cbWinBufAlloc(NumPoints&) ' set aside memory to hold A/D data
   If ADMemHandle& = 0 Then Stop
   
   CBDACount& = NumPoints&
   DAMemHandle& = cbWinBufAlloc(NumPoints&) ' set aside memory to hold D/A data
   If DAMemHandle& = 0 Then Stop
   
   ' Generate D/A ramp data to be output via cbAoutScan function
   For i& = 0 To NumPoints& - 1
   LongVal& = 32768 + i& / NumPoints& * 32768 - 32768 / 2
     DAData%(i&) = ULongValToInt(LongVal&)
   Next i&
   
   
 
  
   ULStat% = cbWinArrayToBuf(DAData%(0), DAMemHandle&, FirstPoint&, CBDACount&)


End Sub

Private Sub tmrCheckStatus_Timer()

   ' This timer will check the status of the background data collection
   
   ' Parameters:
   '   BoardNum%    :the number used by CB.CFG to describe this board
   '   Status%     :current status of the background data collection
   '   CurCount&   :current number of samples collected
   '   CurIndex&   :index to the data buffer pointing to the start of the
   '                most recently collected scan

   ULStat% = cbGetStatus(BoardNum%, ADStatus%, ADCurCount&, ADCurIndex&, AIFUNCTION)
   If ULStat% <> 0 Then Stop

   lblShowADCount.Caption = Format$(ADCurCount&, "0")
   lblShowADIndex.Caption = Format$(ADCurIndex&, "0")

   ' Check if the background operation has finished. If it has, then
   ' transfer the data from the memory buffer set up by Windows to an
   ' array for use by Visual Basic
   ' The BACKGROUND operation must be explicitly stopped

   If ADStatus% = RUNNING And ADUserTerm% = 0 Then
      lblShowADStat.Caption = "Running"
      
      If ADCurIndex > 0 Then
        ULStat% = cbWinBufToArray(ADMemHandle&, ADData%(ADCurIndex&), ADCurIndex&, HighChan% - LowChan% + 1)
        If ULStat% <> 0 Then Stop
      
        For i% = 0 To HighChan%
            TempCount% = i% + ADCurIndex&
            CurrValue& = (ADData%(TempCount%) Xor &H8000) + 32768
            lblADData(i%).Caption = Format$(CurrValue&, "0")
        Next i%
      End If
      
   ElseIf ADStatus% = 0 Or ADUserTerm% = 1 Then
      lblShowADStat.Caption = "Idle"
      ADStatus% = IDLE
      ULStat% = cbGetStatus(BoardNum%, ADStatus%, ADCurCount&, ADCurIndex&, AIFUNCTION)
      If ULStat% <> 0 Then Stop
      lblShowADCount.Caption = Format$(ADCurCount&, "0")
      lblShowADIndex.Caption = Format$(ADCurIndex&, "0")
      If ADMemHandle& = 0 Then Stop
      ULStat% = cbWinBufToArray(ADMemHandle&, ADData%(0), FirstPoint&, NumPoints&)
      If ULStat% <> 0 Then Stop
      
      For i% = 0 To HighChan%
         lblADData(i%).Caption = Format$(ADData%(i%), "0")
      Next i%

      For j% = HighChan% + 1 To 7
        lblADData(j%).Caption = Format$("", "0")
      Next j%

      ULStat% = cbStopBackground(BoardNum%, AIFUNCTION)
      If ULStat% <> 0 Then Stop
      cmdStartADBgnd.Enabled = 1
      cmdStartADBgnd.Visible = 1
      cmdStopADConvert.Enabled = 0
      cmdStopADConvert.Visible = 0
   End If
   
   '==========================================================
   ULStat% = cbGetStatus(BoardNum%, DAStatus%, DACurCount&, DACurIndex&, AOFUNCTION)
   If ULStat% <> 0 Then Stop

   lblShowDACount.Caption = Format$(DACurCount&, "0")
   lblShowDAIndex.Caption = Format$(DACurIndex&, "0")

   ' Check if the background operation has finished.

   If DAStatus% = RUNNING And DAUserTerm% = 0 Then
      lblShowDAStat.Caption = "Running"
   ElseIf DAStatus% = 0 Or DAUserTerm% = 1 Then
      lblShowDAStat.Caption = "Idle"
      DAStatus% = IDLE
      ULStat% = cbGetStatus(BoardNum%, DAStatus%, DACurCount&, DACurIndex&, AOFUNCTION)
      If ULStat% <> 0 Then Stop
      lblShowDACount.Caption = Format$(DACurCount&, "0")
      lblShowDAIndex.Caption = Format$(DACurIndex&, "0")
      
      If DAMemHandle& = 0 Then Stop

      ULStat% = cbStopBackground(BoardNum%, AOFUNCTION)
      If ULStat% <> 0 Then Stop
      cmdStartDABgnd.Enabled = 1
      cmdStartDABgnd.Visible = 1
      cmdStopDAConvert.Enabled = 0
      cmdStopDAConvert.Visible = 0
   End If
   
    If ADStatus% = IDLE And DAStatus% = IDLE Then
       tmrCheckStatus.Enabled = 0
       cmdQuit.Enabled = 1

    End If

End Sub


Function ULongValToInt(LongVal As Long) As Integer

   Select Case LongVal
      Case Is > 65535
         ULongValToInt = -1
      Case Is < 0
         ULongValToInt = 0
      Case Else
         ULongValToInt = (LongVal - 32768) Xor &H8000
   End Select

End Function

