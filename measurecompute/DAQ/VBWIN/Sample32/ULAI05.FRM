VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Manual Conversion"
   ClientHeight    =   4485
   ClientLeft      =   2325
   ClientTop       =   1515
   ClientWidth     =   6000
   Height          =   4890
   Left            =   2265
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4485
   ScaleWidth      =   6000
   Top             =   1170
   Width           =   6120
   Begin TextBox txtHighChan 
      Alignment       =   2  'Center
      Height          =   285
      Left            =   3600
      TabIndex        =   28
      Text            =   "3"
      Top             =   3600
      Width           =   375
   End
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   390
      Left            =   4680
      TabIndex        =   4
      Top             =   3960
      Width           =   780
   End
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   390
      Left            =   3720
      TabIndex        =   3
      Top             =   3960
      Width           =   780
   End
   Begin CommandButton cmdStopBackground 
      Caption         =   "Stop Background"
      Enabled         =   0   'False
      Height          =   375
      Left            =   960
      TabIndex        =   26
      Top             =   3960
      Width           =   2055
   End
   Begin Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   300
      Left            =   240
      Top             =   3840
   End
   Begin Label lbl 
      Caption         =   "Measure Channels 0 to"
      Height          =   255
      Left            =   1440
      TabIndex        =   27
      Top             =   3600
      Width           =   2055
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   9
      Left            =   4440
      TabIndex        =   24
      Top             =   3120
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   8
      Left            =   3360
      TabIndex        =   23
      Top             =   3120
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   2280
      TabIndex        =   22
      Top             =   3120
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   1200
      TabIndex        =   21
      Top             =   3120
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   120
      TabIndex        =   20
      Top             =   3120
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   4440
      TabIndex        =   19
      Top             =   2760
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3360
      TabIndex        =   18
      Top             =   2760
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   2280
      TabIndex        =   17
      Top             =   2760
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1200
      TabIndex        =   16
      Top             =   2760
      Width           =   975
   End
   Begin Label lblConvData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   6
      Top             =   2760
      Width           =   975
   End
   Begin Label lblVoltsRead 
      Caption         =   "Converted Value: the channel number and the 12-bit value after separation of channel bits from data bits:"
      Height          =   495
      Left            =   120
      TabIndex        =   5
      Top             =   2160
      Width           =   4815
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   9
      Left            =   4440
      TabIndex        =   15
      Top             =   1680
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   8
      Left            =   3360
      TabIndex        =   14
      Top             =   1680
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   2280
      TabIndex        =   13
      Top             =   1680
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   1200
      TabIndex        =   12
      Top             =   1680
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   120
      TabIndex        =   11
      Top             =   1680
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   4440
      TabIndex        =   10
      Top             =   1320
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3360
      TabIndex        =   9
      Top             =   1320
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   2280
      TabIndex        =   8
      Top             =   1320
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1200
      TabIndex        =   7
      Top             =   1320
      Width           =   975
   End
   Begin Label lblShowRaw 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   2
      Top             =   1320
      Width           =   975
   End
   Begin Label lblRawData 
      Caption         =   "Value: the 16-bit integer read from the board:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   960
      Width           =   3975
   End
   Begin Label lblStatus 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   240
      TabIndex        =   25
      Top             =   600
      Width           =   5055
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of manual conversion of data"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   5730
   End
End
'ULAI05.MAK================================================================

' File:                         ULAI05.MAK

' Library Call Demonstrated:    cbAInScan%() with manual data conversion

' Purpose:                      Demonstrate the manual conversion of data
'                               values after they have been collected.

' Demonstration:                Collects 10 data points from five analog
'                               input channels.  Data are collected
'                               as 16-bit values and are converted to
'                               channel numbers and 12-bit data values
'                               using BASIC code.

' Other Library Calls:          cbGetStatus%()
'                               cbStopBackground%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a 12 bit A/D converter.
'                               Analog signal on input channels 0 - 4.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0         ' Board number
Const NumPoints& = 10       ' Number of data points to collect
Const FirstPoint& = 0

Dim ADData%(NumPoints&)     'dimension an array to hold the input values
Dim ConvData%(NumPoints&)   'dimension an array to hold the converted
                            'data values
Dim HighChan%
Dim MemHandle&
Dim UserTerm%

Sub cmdQuit_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
                                            ' other programs
   If ULStat% <> 0 Then Stop
   End

End Sub

Sub cmdStartConvert_Click ()
            
   cmdStartConvert.Enabled = 0
   cmdQuit.Enabled = 0
   cmdStopBackground.Enabled = -1

   'Collect the values with cbAInScan%() in BACKGROUND mode
   '  Parameters:
   '     BoardNum%   :the number used by CB.CFG to describe this board
   '     LowChan%    :the first channel of the scan
   '     HighChan%   :the last channel of the scan
   '     CBCount&    :the total number of A/D samples to collect
   '     CBRate&     :sample rate in samples per second
   '     Gain        :the gain for the board
   '     ADData%     :the array for the collected data values
   '     Options     :data collection options

   LowChan% = 0
   HighChan% = Val(txtHighChan.Text)
   If HighChan% > 7 Then HighChan% = 7
   txtHighChan.Text = Str(HighChan%)

   CBCount& = NumPoints&                  ' total number of data points to collect
   CBRate& = 3125                         ' sampling rate (samples per second)
   Options = NOCONVERTDATA + BACKGROUND   ' collect data in BACKGROUND mode
                                          ' as 16-bit values (no conversion)
   Gain = BIP5VOLTS                       'set the gain

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options)
   If ULStat% <> 0 Then Stop

   'during the BACKGROUND operation, check the status using a timer, then print the values

   tmrCheckStatus.Enabled = -1
   
End Sub

Sub cmdStopBackground_Click ()

   cmdQuit.Enabled = -1
   cmdStopBackground.Enabled = 0
   UserTerm% = 1

End Sub

Sub Convert ()

   'Show the data that were collected
   For K% = 0 To NumPoints& - 1
      lblShowRaw(K%).Caption = Format$(ADData%(K%), "0")
   Next

   'Manually convert the 16-bit values to 12-bit values

   For K% = 0 To NumPoints& - 1
      'find the channel number in the first 4-bits
      channel% = ADData%(K%) And 15   'AND Mask with 15

      'retrieve the data value from the next 12-bits
      ' and put them into ConvData%() array
      ConvData%(K%) = ADData%(K%) \ 16 'div by 16 shifts 4 places to right

      'if the original value was negative, then we need to replace
      ' the highbit, which BASIC thought was a sign, rather than part
      ' of the value. Add 4096 to replace the highbit.
      If ADData%(K%) < 0 Then
         ConvData%(K%) = ConvData%(K%) + 4096
      End If

      lblConvData(K%).Caption = Format$(channel%, "0\,\ ") + Format$(ConvData%(K%), "0")
   Next

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
   
   UserTerm% = 0

End Sub

Sub tmrCheckStatus_Timer ()

   'Check the current status of the background data collection
   '  Parameters:
   '     BoardNum%   :the number used by CB.CFG to describe this board
   '     Status%     :current status of the background data collection
   '     CurCount&   :current number of samples collected
   '     CurIndex&   :index to the data buffer pointing to the last value transferred
   '     FunctionType: A/D operation (AIFUNCTIOM)

   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
   If ULStat% <> 0 Then Stop

      ' check if the background operation has finished
   If Status% = IDLE Or UserTerm% = 1 Then
      lblStatus.Caption = "Data collection finished."
      
      'the BACKGROUND operation must be explicitly stopped
      ULStat% = cbStopBackground(BoardNum%,AIFUNCTION)
      If ULStat% <> 0 Then Stop
      If MemHandle& = 0 Then Stop
      ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, NumPoints&)
      If ULStat% <> 0 Then Stop
      cmdStartConvert.Enabled = -1
      cmdQuit.Enabled = -1
      cmdStopBackground.Enabled = 0
      tmrCheckStatus.Enabled = 0
      Convert
   Else
      lblStatus.Caption = "Background operation in progress."
   End If
   
   If UserTerm% = 1 Then
      lblStatus.Caption = "Data collection terminated by user."
      UserTerm% = 0
   End If
   
End Sub

