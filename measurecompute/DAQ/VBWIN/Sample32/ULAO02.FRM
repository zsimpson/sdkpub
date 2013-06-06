VERSION 2.00
Begin Form frmSendAData 
   Caption         =   "Universal Library Analog Output "
   ClientHeight    =   3180
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5055
   ForeColor       =   &H00FF0000&
   Height          =   3585
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form2"
   ScaleHeight     =   3180
   ScaleWidth      =   5055
   Top             =   1200
   Width           =   5175
   Begin CommandButton cmdEndProgram 
      Caption         =   "Quit"
      Height          =   390
      Left            =   3960
      TabIndex        =   1
      Top             =   2520
      Width           =   825
   End
   Begin CommandButton cmdSendData 
      Caption         =   "Send Data"
      Height          =   495
      Left            =   1920
      TabIndex        =   2
      Top             =   720
      Width           =   1215
   End
   Begin Label lblAOutData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3840
      TabIndex        =   10
      Top             =   1800
      Width           =   975
   End
   Begin Label lblAOutData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   2640
      TabIndex        =   9
      Top             =   1800
      Width           =   975
   End
   Begin Label lblAOutData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1440
      TabIndex        =   8
      Top             =   1800
      Width           =   975
   End
   Begin Label lblAOutData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   3
      Top             =   1800
      Width           =   975
   End
   Begin Label lblChan3 
      Alignment       =   2  'Center
      Caption         =   "Channel 3"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3840
      TabIndex        =   7
      Top             =   1440
      Width           =   975
   End
   Begin Label lblChan2 
      Alignment       =   2  'Center
      Caption         =   "Channel 2"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   2640
      TabIndex        =   6
      Top             =   1440
      Width           =   975
   End
   Begin Label lblChan1 
      Alignment       =   2  'Center
      Caption         =   "Channel 1"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   1440
      TabIndex        =   5
      Top             =   1440
      Width           =   975
   End
   Begin Label lblChan0 
      Alignment       =   2  'Center
      Caption         =   "Channel 0"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   1440
      Width           =   975
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAOutScan%()"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   4215
   End
End
'ULAO02.MAK================================================================

' File:                         ULAO02.MAK

' Library Call Demonstrated:    cbAOutScan%()

' Purpose:                      Writes to a range of D/A Output Channels.

' Demonstration:                Sends a digital output to the D/A channels

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have 4 or more D/A converters.
'                               This function is designed for boards that
'                               support timed analog output.  It can be used
'                               for polled output boards but only for values
'                               of NumPoints& up to the number of channels
'                               that the board supports (i.e., NumPoints& =
'                               6 maximum for the six channel CIO-DDA06).


' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0           ' Board number
Const NumPoints& = 4
Const CBCount& = NumPoints&

Dim DAData%(NumPoints&)
Dim MemHandle&               ' define a variable to contain the handle for
                             ' memory allocated by Windows through cbWinBufAlloc%()
Dim FirstPoint&

Sub cmdEndProgram_Click ()

   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
                                            ' other programs
   End

End Sub

Sub cmdSendData_Click ()

   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   LowChan%    :the lower channel of the scan
   '   HighChan%   :the upper channel of the scan
   '   CBCount&    :the number of D/A values to send
   '   CBRate&     :send rate in values/second (if supported by BoardNum)
   '   DAData%     :array of values to send to the scanned channels
   '   Options%    :data send options
  
   FirstPoint& = 0
   LowChan% = 0         'First analog output channel
   HighChan% = 3        'Last analog output channel
   CBRate& = 100        'Rate of data update (ignored if board does not
   Gain% = BIP5VOLTS    'Ignored if gain is not programmable
   Options% = 0         'support timed analog output)

   ULStat% = cbAOutScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain%, MemHandle&, Options%)
   If ULStat% <> 0 Then Stop

   For i% = 0 To NumPoints& - 1
      lblAOutData(i%).Caption = Format$(DAData%(i%), "0")
   Next i%

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
    
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.

   MemHandle& = cbWinBufAlloc(NumPoints&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop
   
   For i% = 0 To NumPoints& - 1
      DAData%(i%) = i% * 1365
   Next i%
  
   FirstPoint& = 0
  
   ULStat% = cbWinArrayToBuf(DAData%(0), MemHandle&, FirstPoint&, CBCount&)

End Sub

