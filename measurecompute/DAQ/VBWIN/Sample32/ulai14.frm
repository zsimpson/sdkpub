VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   3480
   ClientLeft      =   2835
   ClientTop       =   1560
   ClientWidth     =   5235
   ForeColor       =   &H00FF0000&
   Height          =   3885
   Left            =   2775
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3480
   ScaleWidth      =   5235
   Top             =   1215
   Width           =   5355
   Begin TextBox txtHighChan 
      Alignment       =   2  'Center
      Height          =   285
      Left            =   3240
      TabIndex        =   20
      Text            =   "3"
      Top             =   990
      Width           =   375
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4200
      TabIndex        =   17
      Top             =   2880
      Width           =   870
   End
   Begin CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   390
      Left            =   3120
      TabIndex        =   18
      Top             =   2880
      Width           =   870
   End
   Begin Label Label1 
      Caption         =   "Measure Channels 0 to "
      Height          =   240
      Left            =   1080
      TabIndex        =   19
      Top             =   990
      Width           =   2055
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   3960
      TabIndex        =   16
      Top             =   2550
      Width           =   975
   End
   Begin Label lblChan7 
      Caption         =   "Channel 7:"
      Height          =   255
      Left            =   2880
      TabIndex        =   8
      Top             =   2550
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1440
      TabIndex        =   12
      Top             =   2550
      Width           =   975
   End
   Begin Label lblChan3 
      Caption         =   "Channel 3:"
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   2550
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3960
      TabIndex        =   15
      Top             =   2175
      Width           =   975
   End
   Begin Label lblChan6 
      Caption         =   "Channel 6:"
      Height          =   255
      Left            =   2880
      TabIndex        =   7
      Top             =   2175
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1440
      TabIndex        =   11
      Top             =   2175
      Width           =   975
   End
   Begin Label lblChan2 
      Caption         =   "Channel 2:"
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   2175
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   3960
      TabIndex        =   14
      Top             =   1785
      Width           =   975
   End
   Begin Label lblChan5 
      Caption         =   "Channel 5:"
      Height          =   255
      Left            =   2880
      TabIndex        =   6
      Top             =   1785
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1440
      TabIndex        =   10
      Top             =   1785
      Width           =   975
   End
   Begin Label lblChan1 
      Caption         =   "Channel 1:"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   1785
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   3960
      TabIndex        =   13
      Top             =   1410
      Width           =   975
   End
   Begin Label lblChan4 
      Caption         =   "Channel 4:"
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   1410
      Width           =   975
   End
   Begin Label lblADData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1440
      TabIndex        =   9
      Top             =   1410
      Width           =   975
   End
   Begin Label lblChan0 
      Caption         =   "Channel 0:"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   1410
      Width           =   975
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbSetTrigger%() "
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5055
   End
End
'ULAI14.MAK================================================================

' File:                         ULAI14.MAK

' Library Call Demonstrated:    cbSetTrigger%()

' Purpose:                      Selects the Trigger source. This trigger is
'                               used to initiate A/D conversion using
'                               cbAinScan, with EXTTRIGGER selected.

' Demonstration:                Selects the trigger source
'                               Displays the analog input on eight channels.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have software selectable
'                               triggering source and type.
'                               Board 0 must have an A/D converter.
'                               Analog signals on eight input channels.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0          ' Board number
Const NumPoints& = 600       ' Number of data points to collect
Const FirstPoint& = 0        ' set first element in buffer to transfer to array
Dim ADData%(NumPoints&)      ' dimension an array to hold the input values
Dim MemHandle&               ' define a variable to contain the handle for
			     ' memory allocated by Windows through cbWinBufAlloc%()
Dim HighChan%

Sub cmdStart_Click ()
   Dim highVal As Single        'high threshold in volts
   Dim lowVal As Single 'low threshold in volts

   cmdStart.Enabled = 0
   
   
   ' Select the trigger source using cbSetTrigger()
   ' Parameters:
   '   BoardNum%      :the number used by CB.CFG to describe this board
   '   TrigType%      :the type of triggering based on external trigger source
   '   LowThreshold%  :Low threshold when the trigger input is analog
   '   HighThreshold% :High threshold when the trigger input is analog
	
   highVal = 1#
   Gain = BIP10VOLTS    'analog trigger range
   ULStat% = cbFromEngUnits(BoardNum%, Gain, highVal, HighThreshold%)
   lowVal = .1
   ULStat% = cbFromEngUnits(BoardNum%, Gain, lowVal, LowThreshold%)
   TrigType% = TRIGABOVE
   
   
   ULStat% = cbSetTrigger(BoardNum%, TrigType%, LowThreshold%, HighThreshold%)
   If ULStat% <> NOERRORS Then 
		Stop
	Else

      ' Collect the values with cbAInScan%()
      ' Parameters:
      '   BoardNum%   :the number used by CB.CFG to describe this board
      '   LowChan%    :the first channel of the scan
      '   HighChan%   :the last channel of the scan
      '   CBCount&    :the total number of A/D samples to collect
      '   CBRate&     :sample rate
      '   Gain       :the gain for the board
      '   ADData%     :the array for the collected data values
      '   Options%    :data collection options
   
      LowChan% = 0                     ' first channel to acquire
      HighChan% = Val(txtHighChan.Text)' last channel to acquire
      If HighChan% > 7 Then HighChan% = 7
      txtHighChan.Text = Str(HighChan%)

      CBCount& = NumPoints&            ' total number of data points to collect
      CBRate& = 390                    ' sampling rate (samples per second) per channel
      Gain = BIP5VOLTS                ' set the gain
      Options% = CONVERTDATA Or EXTTRIGGER  ' return data as 12-bit values
   
   
      If MemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists
      ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options%)
   
      If ULStat% = 30 Then MsgBox "Change the Gain argument to one supported by this board.", 0, "Unsupported Gain"
      If ULStat% <> 0 And ULStat% <> 91 Then Stop
   
      ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic
   
      ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, CBCount&)
      If ULStat% <> 0 Then Stop
   
      For i% = 0 To HighChan%
         lblADData(i%).Caption = Format$(ADData%(i%), "0")
      Next i%

      For j% = HighChan% + 1 To 7
           lblADData(j%).Caption = Format$("", "0")
      Next j%
	End If
   cmdStart.Enabled = -1

End Sub

Sub cmdStopConvert_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
					    ' other programs
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

   MemHandle& = cbWinBufAlloc(NumPoints&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

End Sub

