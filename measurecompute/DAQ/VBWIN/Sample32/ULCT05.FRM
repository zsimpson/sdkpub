VERSION 2.00
Begin Form frm8536Count 
   Caption         =   "Universal Library 8536 Counter Demo"
   ClientHeight    =   3630
   ClientLeft      =   1095
   ClientTop       =   1500
   ClientWidth     =   5130
   Height          =   4035
   Left            =   1035
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3630
   ScaleWidth      =   5130
   Top             =   1155
   Width           =   5250
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   495
      Left            =   3960
      TabIndex        =   2
      Top             =   3000
      Width           =   975
   End
   Begin CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   495
      Left            =   2640
      TabIndex        =   0
      Top             =   3000
      Width           =   975
   End
   Begin Timer tmrReadCounter 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   4560
      Top             =   120
   End
   Begin Label lblCount 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3840
      TabIndex        =   1
      Top             =   2280
      Width           =   975
   End
   Begin Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Value read from Counter 1: "
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   2280
      Width           =   3615
   End
   Begin Label lblShowLoadVal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3840
      TabIndex        =   6
      Top             =   1800
      Width           =   975
   End
   Begin Label lblCountLoaded 
      Alignment       =   1  'Right Justify
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1800
      Width           =   3615
   End
   Begin Label lblNoteFreqIn 
      Alignment       =   2  'Center
      Caption         =   "NOTE: There must be a TTL frequency at the counter 1 input."
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   480
      TabIndex        =   4
      Top             =   1080
      Width           =   3495
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of 8536 Counter Functions"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   615
      Left            =   360
      TabIndex        =   3
      Top             =   120
      Width           =   3735
   End
End
'ULCT05.MAK================================================================

' File:                         ULCT05.MAK

' Library Call Demonstrated:    8536 Counter Functions
'                               cbC8536Init%()
'                               cbC8536Config%()
'                               cbCLoad%()
'                               cbCIn%()

' Purpose:                      Operate the counter.

' Demonstration:                Configures, loads and reads the counter.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an 8536 Counter.
'                               There must be a TTL freq. at cntr. 1 input.
'                               Gate line must be tied high.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0           ' Board number

Dim CounterNum%

Sub cmdQuit_Click ()

   End

End Sub

Sub cmdStart_Click ()
   
   'Send a starting value to the counter with cbCLoad%()
   '  Parameters:
   '     BoardNum    :the number used by CB.CFG to describe this board
   '     RegName%    :the counter to be loading with the starting value
   '     LoadValue%  :the starting value to place in the counter

   LoadValue% = 1000
   RegName% = LOADREG1

   ULStat% = cbCLoad(BoardNum, RegName%, LoadValue%)
   If ULStat% <> 0 Then Stop

   'Start a timer to read counter at 500ms interval

   lblCountLoaded.Caption = "The value loaded into LOADREG1 was: "
   lblShowLoadVal.Caption = Format$(LoadValue%, "0")

   tmrReadCounter.Enabled = -1

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
   
   
   'Init the counter for desired operation
   '  Parameters:
   '     BoardNum    :the number used by CB.CFG to describe this board
   '     ChipNum     :the chip to be setup
   '     Ctr1Output  :how the counter output is used

   ChipNum% = 1
   Ctr1Output% = NOTLINKED

   ULStat% = cbC8536Init(BoardNum, ChipNum%, Ctr1Output%)
   If ULStat% <> 0 Then Stop

   'Configure the counter for desired operation
   '  Parameters:
   '     BoardNum      :the number used by CB.CFG to describe this board
   '     CounterNum    :which counter
   '     OutputControl :which counter output signal is used
   '     RecycleMode   :reload at 0 ?
   '     TrigType      :trigger type

   CounterNum% = 1
   OutputControl% = TOGGLEONTC
   RecycleMode% = RECYCLE
   TrigType% = HW_START_TRIG

   ULStat% = cbC8536Config(BoardNum, CounterNum%, OutputControl%, RecycleMode%, TrigType%)
   If ULStat% <> 0 Then Stop

End Sub

Sub tmrReadCounter_Timer ()

   'use this timer to keep checking the counter value with cbCIn%()
   
   '  Parameters:
   '     BoardNum    :the number used by CB.CFG to describe this board
   '     CounterNum% :the counter to be setup
   '     CBCount%      :the count value in the counter

   ULStat% = cbCIn(BoardNum, CounterNum%, CBCount%)
   If ULStat% <> 0 Then Stop

   lblCount.Caption = Format$(CBCount%, "0")

End Sub

