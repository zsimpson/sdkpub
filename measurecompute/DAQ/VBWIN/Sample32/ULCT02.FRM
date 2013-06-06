VERSION 2.00
Begin Form frm9513Ctr 
   Caption         =   "Universal Library 9513 Counter Demo"
   ClientHeight    =   3645
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5085
   Height          =   4050
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3645
   ScaleWidth      =   5085
   Top             =   1200
   Width           =   5205
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   396
      Left            =   3480
      TabIndex        =   5
      Top             =   2760
      Width           =   804
   End
   Begin Timer tmrReadCounter 
      Interval        =   500
      Left            =   4320
      Top             =   360
   End
   Begin Label lblShowReadVal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3480
      TabIndex        =   2
      Top             =   1800
      Width           =   1095
   End
   Begin Label lblReadValue 
      Height          =   255
      Left            =   840
      TabIndex        =   4
      Top             =   1800
      Width           =   2415
   End
   Begin Label lblShowLoadVal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3480
      TabIndex        =   1
      Top             =   1320
      Width           =   1095
   End
   Begin Label lblLoadValue 
      Height          =   255
      Left            =   840
      TabIndex        =   3
      Top             =   1320
      Width           =   2415
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of 9513 Counter Functions."
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   615
      Left            =   720
      TabIndex        =   0
      Top             =   240
      Width           =   3375
   End
End
'ULCT02.MAK===============================================================

' File:                         ULCT02.MAK

' Library Call Demonstrated:    9513 Counter Functions
'                               cbC9513Init%()
'                               cbC9513Config()
'                               cbCLoad%()
'                               cbCIn%()

' Purpose:                      Operate the counter.

' Demonstration:                Initializes, configures, loads and checks
'                               the counter

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have a 9513 Counter.
'                               Program uses internal clock to count.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const CounterNum% = 1           ' number of counter used
Const ChipNum% = 1              ' use chip 1 for CIO-CTR05 or for first
                                ' chip on CIO-CTR10

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
   '    BoardNum       :the number used by CBCONFIG to describe this board
   '    ChipNum%       :Chip to be initialized (1 for CTR05, 1 or 2 for CTR10)
   '    FOutDivider%   :the F-Out divider (0-15)
   '    FOutSource%    :the signal source for F-Out
   '    Compare1%      :status of comparator 1
   '    Compare2%      :status of comparator 2
   '    TimeOfDay%     :time of day mode control

   FOutDivider% = 0
   FOutSource% = FREQ4
   Compare1% = DISABLED
   Compare2% = DISABLED
   TimeOfDay% = DISABLED

   ULStat% = cbC9513Init(BoardNum, ChipNum%, FOutDivider%, FOutSource%, Compare1%, Compare2%, TimeOfDay%)
   If ULStat% <> 0 Then Stop

   ' Set the configurable operations of the counter
   '  Parameters:
   '    BoardNum        :the number used by CBCONFIG to describe this board
   '    CounterNum%     :the counter to be configured (1 to 5)
   '    GateControl%    :gate control value
   '    CounterEdge%    :which edge to count
   '    CountSource%    :signal source
   '    SpecialGate%    :status of special gate
   '    Reload%         :method of reloading
   '    RecyleMode%     :recyle mode
   '    BCDMode%        :counting mode, Binary or BCD
   '    CountDirection% :direction for the counting operation (COUNTUP or COUNTDOWN)
   '    OutputControl%  :output signal type and level
    
   GateControl% = NOGATE
   CounterEdge% = POSITIVEEDGE
   CountSource% = FREQ4
   SpecialGate% = DISABLED
   Reload% = LOADREG
   RecycleMode% = RECYCLE
   BCDMode% = DISABLED
   CountDirection% = COUNTUP
   OutputControl% = ALWAYSLOW

   ULStat% = cbC9513Config(BoardNum, CounterNum%, GateControl%, CounterEdge%, CountSource%, SpecialGate%, Reload%, RecycleMode%, BCDMode%, CountDirection%, OutputControl%)
   If ULStat% <> 0 Then Stop

   ' Send a starting value to the counter with cbCLoad%()
   '  Parameters:
   '    BoardNum    :the number used by CBCONFIG to describe this board
   '    RegName%    :the counter to be loaded with the starting value
   '    LoadValue%  :the starting value to place in the counter
    
   RegName% = LOADREG1       ' name of register in counter 1
   LoadValue% = 1000
  
   ULStat% = cbCLoad(BoardNum, RegName%, LoadValue%)
   If ULStat% <> 0 Then Stop

   lblLoadValue.Caption = "Value loaded to counter:"
   lblShowLoadVal.Caption = Format$(LoadValue%, "0")

End Sub

Sub tmrReadCounter_Timer ()

   ' Parameters:
   '   BoardNum    :the number used by CBCONFIG to describe this board
   '   CounterNum% :the counter to be read
   '   CBCount%    :the count value in the counter
    
   ULStat% = cbCIn(BoardNum, CounterNum%, CBCount%)
   If ULStat% <> 0 Then Stop

   lblReadValue.Caption = "Value read from counter:"
   lblShowReadVal.Caption = Format$(CBCount%, "0")

End Sub

