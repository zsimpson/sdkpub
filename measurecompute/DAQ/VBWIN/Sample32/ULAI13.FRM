VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   4725
   ClientLeft      =   2160
   ClientTop       =   1965
   ClientWidth     =   5085
   ForeColor       =   &H00FF0000&
   Height          =   5130
   Left            =   2100
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4725
   ScaleWidth      =   5085
   Top             =   1620
   Width           =   5205
   Begin TextBox txtHighChan 
      Height          =   285
      Left            =   3120
      TabIndex        =   27
      Text            =   "3"
      Top             =   2655
      Width           =   375
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4080
      TabIndex        =   17
      Top             =   4080
      Visible         =   0   'False
      Width           =   750
   End
   Begin CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   390
      Left            =   4080
      TabIndex        =   25
      Top             =   4080
      Width           =   750
   End
   Begin Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   3240
      Top             =   1560
   End
   Begin Frame fraMode 
      Caption         =   "Select Mode"
      Height          =   1692
      Left            =   384
      TabIndex        =   18
      Top             =   864
      Width           =   1740
      Begin OptionButton optModeBlock 
         Caption         =   "Block IO"
         Height          =   300
         Left            =   192
         TabIndex        =   21
         Top             =   1248
         Width           =   1260
      End
      Begin OptionButton optModeDMA 
         Caption         =   "DMA IO"
         Height          =   300
         Left            =   192
         TabIndex        =   20
         Top             =   960
         Width           =   1260
      End
      Begin OptionButton optModeSing 
         Caption         =   "Single IO"
         Height          =   300
         Left            =   192
         TabIndex        =   19
         Top             =   672
         Width           =   1260
      End
      Begin OptionButton optDefault 
         Caption         =   "Default"
         Height          =   300
         Left            =   192
         TabIndex        =   24
         Top             =   384
         Value           =   -1  'True
         Width           =   1260
      End
   End
   Begin Label Label1 
      Caption         =   "Measure Channels 0 to "
      Height          =   240
      Left            =   960
      TabIndex        =   26
      Top             =   2655
      Width           =   2055
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   3960
      TabIndex        =   16
      Top             =   3690
      Width           =   690
   End
   Begin Label lblChan7 
      Caption         =   "Channel 7:"
      Height          =   255
      Left            =   2880
      TabIndex        =   8
      Top             =   3690
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   3690
      Width           =   690
   End
   Begin Label lblChan3 
      Caption         =   "Channel 3:"
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   3690
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3960
      TabIndex        =   15
      Top             =   3450
      Width           =   690
   End
   Begin Label lblChan6 
      Caption         =   "Channel 6:"
      Height          =   255
      Left            =   2880
      TabIndex        =   7
      Top             =   3450
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   3450
      Width           =   690
   End
   Begin Label lblChan2 
      Caption         =   "Channel 2:"
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   3450
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   3960
      TabIndex        =   14
      Top             =   3210
      Width           =   690
   End
   Begin Label lblChan5 
      Caption         =   "Channel 5:"
      Height          =   255
      Left            =   2880
      TabIndex        =   6
      Top             =   3210
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   3210
      Width           =   690
   End
   Begin Label lblChan1 
      Caption         =   "Channel 1:"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   3210
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   3960
      TabIndex        =   13
      Top             =   2970
      Width           =   690
   End
   Begin Label lblChan4 
      Caption         =   "Channel 4:"
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   2970
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   2970
      Width           =   690
   End
   Begin Label lblChan0 
      Caption         =   "Channel 0:"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   2970
      Width           =   975
   End
   Begin Label lblModeNo 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4440
      TabIndex        =   22
      Top             =   1080
      Width           =   375
   End
   Begin Label lblOptCode 
      Alignment       =   1  'Right Justify
      Caption         =   "Option code (in Hex):"
      Height          =   255
      Left            =   2280
      TabIndex        =   23
      Top             =   1080
      Width           =   2055
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAInScan%() with user selected mode"
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   195
      Width           =   4695
   End
End
'ULAI13.MAK================================================================

' File:                         ULAI13.MAK

' Library Call Demonstrated:    cbAInScan%(), sampling mode options.

' Purpose:                      Scans a range of A/D Input Channels and stores
'                               the sample data in an array using a user
'                               specified sampling mode.

' Demonstration:                Displays the analog input on 8 channels.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signals on two input channels.
'                               Board must support the mode selected.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0          ' Board number
Const NumPoints& = 2048     ' Number of data points to collect
Const FirstPoint& = 0       ' set first element in buffer to transfer to array

Dim ADData%(NumPoints&)     ' dimension an array to hold the input values
Dim MemHandle&              ' define a variable to contain the handle for
                            ' memory allocated by Windows through cbWinBufAlloc%()
Dim Options                 ' define cbAInScan() Options as Module level variable
Dim HighChan%

Sub cmdStart_Click ()

   cmdStart.Visible = 0
   cmdStopConvert.Visible = -1
   tmrConvert.Enabled = -1

End Sub

Sub cmdStopConvert_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat% <> 0 Then Stop                ' other programs
   End
   
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
   '                 errors must be handled locally
  
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop

   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.

   MemHandle& = cbWinBufAlloc(NumPoints&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

   Options = CONVERTDATA

End Sub

Sub optDefault_Click ()

   Options = CONVERTDATA

End Sub

Sub optModeBlock_Click ()

   Options = CONVERTDATA + BLOCKIO

End Sub

Sub optModeDMA_Click ()

   Options = CONVERTDATA + DMAIO

End Sub

Sub optModeSing_Click ()

   Options = CONVERTDATA + SINGLEIO

End Sub

Sub tmrConvert_Timer ()

   lblModeNo.Caption = Hex$(Options)

   ' Collect the values with cbAInScan%()
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    LowChan%    :the first channel of the scan
   '    HighChan%   :the last channel of the scan
   '    CBCount&    :the total number of A/D samples to collect
   '    CBRate&     :sample rate
   '    Gain        :the gain for the board
   '    ADData%     :the array for the collected data values
   '    Options     :data collection options (determined by
   '                 Set Mode option buttons in this program)

   LowChan% = 0                     ' first channel to acquire
   HighChan% = Val(txtHighChan.Text) ' last channel to acquire
   If HighChan% > 7 Then HighChan% = 7
   txtHighChan.Text = Str(HighChan%)

   CBCount& = NumPoints&            ' total number of data points to collect
   CBRate& = 290                    ' sampling rate (in Hz per channel)
   Gain = BIP5VOLTS                ' set the gain

   If MemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options)
   
   If ULStat% = 91 Then
      ULStat% = cbErrHandling(DONTPRINT, DONTSTOP)
      'Turn off library error handling for subsequent calls
   ElseIf ULStat% <> 0 Then
      Stop
   End If

   ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

   ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, CBCount&)
   If ULStat% <> 0 Then Stop

   For i% = 0 To HighChan%
      lblADData(i%).Caption = Format$(ADData%(i%), "0")
   Next i%

End Sub

