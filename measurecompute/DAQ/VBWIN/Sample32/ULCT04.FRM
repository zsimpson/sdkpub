VERSION 2.00
Begin Form frm9513Freq 
   Caption         =   "Universal Library 9513 Counter Demo"
   ClientHeight    =   3750
   ClientLeft      =   105
   ClientTop       =   1440
   ClientWidth     =   5175
   Height          =   4155
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3750
   ScaleWidth      =   5175
   Top             =   1095
   Width           =   5295
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   390
      Left            =   3960
      TabIndex        =   1
      Top             =   3120
      Width           =   780
   End
   Begin CommandButton cmdMeasureFreq 
      Caption         =   "Measure Frequency"
      Height          =   375
      Left            =   1440
      TabIndex        =   7
      Top             =   3120
      Width           =   1935
   End
   Begin Label lblFreq 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   3
      Top             =   2400
      Width           =   975
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   1320
      TabIndex        =   2
      Top             =   2400
      Width           =   975
   End
   Begin Label lblFrequency 
      Alignment       =   2  'Center
      Caption         =   "Frequency"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   2040
      Width           =   1215
   End
   Begin Label lblCountNum 
      Alignment       =   2  'Center
      Caption         =   "Number of Counts"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   960
      TabIndex        =   4
      Top             =   2040
      Width           =   1695
   End
   Begin Label lblInstruct 
      Alignment       =   2  'Center
      Caption         =   "There must be a TTL pulse at counter 1 input with a frequency between  100Hz and  600kHz. Also, connect the output of counter 4 to the gate of counter 5."
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   120
      TabIndex        =   6
      Top             =   1080
      Width           =   4935
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of Frequency Measurement using 9513 Counter"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   660
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   4590
   End
End
'ULCT04.MAK===============================================================

' File:                         ULCT04.MAK

' Library Call Demonstrated:    cbCFreqIn%()

' Purpose:                      Measure the frequency of a signal.

' Demonstration:                Initializes the counter and measures a frequency.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have a 9513 Counter.
'                               External freq. at counter 1 input.
'                               (100Hz < freq < 330kHz)
'                               External connection from counter 4 output
'                               to counter 5 gate.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const ChipNum% = 1              ' use chip 1 for CIO-CTR05 or for first
                                ' chip on CIO-CTR10

Sub cmdMeasureFreq_Click ()

   ' Measure the frequency of the internally-generated signal
   '  Parameters:
   '    BoardNum      :the number used by CB.CFG to describe this board
   '    SigSource%    :the counter to be measured (1 to 5)
   '    GateInterval% :gating interval in millseconds
   '    CBCount%      :the raw count during GateInterval% is returned here
   '    Freq&         :the calculated frequency (Hz) is returned here

   GateInterval% = 100
   SigSource% = CTRINPUT1
  
   ULStat% = cbCFreqIn(BoardNum, SigSource%, GateInterval%, CBCount%, Freq&)
   If ULStat% <> 0 Then Stop

   If CBCount% < 0 Then
      ActualCounts& = 65535 + CBCount%
   Else
      ActualCounts& = CBCount%
   End If

   lblCount.Caption = Format$(ActualCounts&, "0")
   lblFreq.Caption = Format$(Freq&, "0\H\z")

End Sub

Sub cmdStopRead_Click ()

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
   '                  errors must be handled locally
      
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop
    
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
    
    
   ' Initialize the board level features
   '  Parameters:
   '    BoardNum    :the number used by CBCONFIG to describe this board
   '    ChipNum%    :chip to be initialized (1 for CTR5, 1 or 2 for CTR10)
   '    FOutDivider%:the F-Out divider (0-15)
   '    Source%     :the signal source for F-Out
   '    Compare1%   :status of comparator 1
   '    Compare2%   :status of comparator 2
   '    TimeOfDay%  :time of day mode control

   FOutDivider% = 1         ' sets up OSC OUT for 10kHz signal which can
   Source% = FREQ3          ' be used as frequency source for this example
   Compare1% = DISABLED
   Compare2% = DISABLED
   TimeOfDay% = DISABLED

   ULStat% = cbC9513Init(BoardNum, ChipNum%, FOutDivider%, Source%, Compare1%, Compare2%, TimeOfDay%)
   If ULStat% <> 0 Then Stop

End Sub

