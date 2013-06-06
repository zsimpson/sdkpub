VERSION 2.00
Begin Form frmCountTest 
   Caption         =   "Universal Library 8254 Counter"
   ClientHeight    =   3915
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4200
   Height          =   4320
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3915
   ScaleWidth      =   4200
   Top             =   1200
   Width           =   4320
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   495
      Left            =   3000
      TabIndex        =   6
      Top             =   3120
      Width           =   855
   End
   Begin Timer tmrReadCount 
      Interval        =   500
      Left            =   1800
      Top             =   3120
   End
   Begin Label lblShowCountRead 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   5
      Top             =   2520
      Width           =   975
   End
   Begin Label lblCountRead 
      Caption         =   "Value read from counter:"
      Height          =   255
      Left            =   720
      TabIndex        =   3
      Top             =   2520
      Width           =   2175
   End
   Begin Label lblShowLoadVal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3000
      TabIndex        =   4
      Top             =   2040
      Width           =   975
   End
   Begin Label lblCountLoaded 
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2040
      Width           =   2655
   End
   Begin Label lblNoteFreqIn 
      Alignment       =   2  'Center
      Caption         =   "NOTE: There must be a TTL frequency at the counter 1 input."
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   1200
      Width           =   3495
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of 8254 Counter Functions"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   3735
   End
End
'ULCT01.MAK================================================================

' File:                         ULCT01.MAK

' Library Call Demonstrated:    8254 Counter Functions
'                               cbC8254Config%()
'                               cbCLoad%()
'                               cbCIn%()

' Purpose:                      Operate the counter.

' Demonstration:                Configures, loads and reads the counter.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an 8254 Counter.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number

Const CounterNum% = 1           ' number of counter used
Const RegName% = LOADREG1       ' register name of counter 1

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


   ' Configure the counter for desired operation
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    CounterNum% :the counter to be setup
   '    Config%     :the operation mode of counter to be configured
      
   
   Config% = HIGHONLASTCOUNT
   
   ULStat% = cbC8254Config(BoardNum, CounterNum%, Config%)
   If ULStat% <> 0 Then Stop

   ' Send a starting value to the counter with cbCLoad%()
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    RegName%    :the register of the counter to be loading with the starting value
   '    LoadValue%  :the starting value to place in the counter
   
   LoadValue% = 1000
    
   ULStat% = cbCLoad(BoardNum, RegName%, LoadValue%)
   If ULStat% <> 0 Then Stop

   lblCountLoaded.Caption = "Counter starting value loaded:"
   
   lblShowLoadVal.Caption = Format$(LoadValue%, "0")

End Sub

Sub tmrReadCount_Timer ()

   ' Parameters:
   '   BoardNum        :the number used by CB.CFG to describe this board
   '   CounterNum%     :the counter to be read
   '   CBCount%        :the value read from the counter
    
   ULStat% = cbCIn(BoardNum, CounterNum%, CBCount%)
   If ULStat% <> 0 Then Stop
     
   lblShowCountRead.Caption = Format$(CBCount%, "0")

End Sub

