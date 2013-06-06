VERSION 2.00
Begin Form frm9513Int 
   Caption         =   "Universal Library 9513 Counter Demo"
   ClientHeight    =   4440
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5250
   Height          =   4845
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4440
   ScaleWidth      =   5250
   Top             =   1200
   Width           =   5370
   Begin CommandButton cmdStartInt 
      Caption         =   "Start"
      Height          =   375
      Left            =   4080
      TabIndex        =   4
      Top             =   3720
      Width           =   855
   End
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   4080
      TabIndex        =   3
      Top             =   3720
      Visible         =   0   'False
      Width           =   855
   End
   Begin Timer tmrReadStatus 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4800
      Top             =   360
   End
   Begin Label lblShowTotal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   2520
      TabIndex        =   18
      Top             =   3840
      Width           =   975
   End
   Begin Label lblIntTotal 
      Alignment       =   1  'Right Justify
      Caption         =   "Total Interrupts:"
      Height          =   255
      Left            =   840
      TabIndex        =   22
      Top             =   3840
      Width           =   1575
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   3240
      TabIndex        =   17
      Top             =   3120
      Width           =   975
   End
   Begin Label lblIntStatus 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   1800
      TabIndex        =   12
      Top             =   3120
      Width           =   1095
   End
   Begin Label lblCounterNum 
      Alignment       =   2  'Center
      Caption         =   "5"
      ForeColor       =   &H00000000&
      Height          =   255
      Index           =   4
      Left            =   1080
      TabIndex        =   8
      Top             =   3120
      Width           =   375
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3240
      TabIndex        =   16
      Top             =   2760
      Width           =   975
   End
   Begin Label lblIntStatus 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1800
      TabIndex        =   11
      Top             =   2760
      Width           =   1095
   End
   Begin Label lblCounterNum 
      Alignment       =   2  'Center
      Caption         =   "4"
      ForeColor       =   &H00000000&
      Height          =   255
      Index           =   3
      Left            =   1080
      TabIndex        =   7
      Top             =   2760
      Width           =   375
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3240
      TabIndex        =   15
      Top             =   2400
      Width           =   975
   End
   Begin Label lblIntStatus 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1800
      TabIndex        =   10
      Top             =   2400
      Width           =   1095
   End
   Begin Label lblCounterNum 
      Alignment       =   2  'Center
      Caption         =   "3"
      ForeColor       =   &H00000000&
      Height          =   255
      Index           =   2
      Left            =   1080
      TabIndex        =   6
      Top             =   2400
      Width           =   375
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   3240
      TabIndex        =   14
      Top             =   2040
      Width           =   975
   End
   Begin Label lblIntStatus 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1800
      TabIndex        =   9
      Top             =   2040
      Width           =   1095
   End
   Begin Label lblCounterNum 
      Alignment       =   2  'Center
      Caption         =   "2"
      ForeColor       =   &H00000000&
      Height          =   255
      Index           =   1
      Left            =   1080
      TabIndex        =   5
      Top             =   2040
      Width           =   375
   End
   Begin Label lblCount 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   3240
      TabIndex        =   13
      Top             =   1680
      Width           =   975
   End
   Begin Label lblIntStatus 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1800
      TabIndex        =   2
      Top             =   1680
      Width           =   1095
   End
   Begin Label lblCounterNum 
      Alignment       =   2  'Center
      Caption         =   "1"
      ForeColor       =   &H00000000&
      Height          =   255
      Index           =   0
      Left            =   1080
      TabIndex        =   1
      Top             =   1680
      Width           =   375
   End
   Begin Label lblData 
      Alignment       =   2  'Center
      Caption         =   "Data Value"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3120
      TabIndex        =   21
      Top             =   1200
      Width           =   1215
   End
   Begin Label lblStatCol 
      Alignment       =   2  'Center
      Caption         =   "Status"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   1920
      TabIndex        =   20
      Top             =   1200
      Width           =   855
   End
   Begin Label lblCountCol 
      Alignment       =   2  'Center
      Caption         =   "Counter"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   840
      TabIndex        =   19
      Top             =   1200
      Width           =   855
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of 9513 Counter using Interrupts"
      Height          =   615
      Left            =   480
      TabIndex        =   0
      Top             =   240
      Width           =   4215
   End
End
'ULCT03.MAK===============================================================

' File:                         ULCT03.MAK

' Library Call Demonstrated:    9513 Counter Functions
'                               cbC9513Config%()
'                               cbCStoreOnInt%()

' Purpose:                      Operate the counter

' Demonstration:                Sets up 2 counters to store values in
'                               response to an interrupt
'

' Other Library Calls:          cbC9513Init%()
'                               cbCLoad%()
'                               cbStopBackground%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a 9513 counter.
'                               IR enable must be tied low (Pin 2).
'                               User must generate an interrupt (Pin1).

' (c) Copyright 1994-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum& = 0         ' Board number
Const ChipNum& = 1			' use chip 1 for CIO-CTR05 or for first
Const ControlSize% = 20		' chip on CIO-CTR10
Const MaxNumCntrs& = 20		' maximum number of 9513 counters onboard(CIO-CTR20)
Const NumCntrs& = 10 		' actual number of counters onboard the CIO-CTR10
							'   UPDATE THIS VALUE TO REFLECT THE NUMBER COUNTERS 
							'	FOR SPECIFIC MODEL INSTALLED
Const IntCount& = 100		' the windows buffer pointed to by MemHandle will hold enough
							' data for IntCount interrupts

Dim DataBuffer%(MaxNumCntrs&)	' array to hold latest readings from each of the counters
Dim CntrControl%(MaxNumCntrs&)  ' array to control whether or not each counter is enabled
Dim MemHandle&				' handle to windows data buffer that is large enough to hold 
							' IntCount readings from each of the NumCntrs counters
Dim FirstPoint&

Sub cmdStartInt_Click ()

   cmdStartInt.Enabled = 0
   cmdStartInt.Visible = 0
   cmdStopRead.Enabled = 1
   cmdStopRead.Visible = 1

   ' set the counters to store their values upon an interrupt
   '  Parameters:
   '    BoardNum&       :the number used by CBCONFIG to describe this board
   '    IntCount%      :maximum number of interrupts
   '    CntrControl%() :array which indicates the channels to be read
   '    DataBuffer%()  :array that receives the count values for enabled
   '                    channels each time an interrupt occur

   ' set all channels to CBDISABLED  and init DataBuffer
   For I% = 0 To NumCntrs&-1
      CntrControl%(I%) = CBDISABLED
      DataBuffer%(I%) = 0
   Next I%

   ' enable the channels to be monitored
   CntrControl%(0) = CBEnabled
   CntrControl%(1) = CBEnabled

   ULStat% = cbCStoreOnInt(BoardNum&, IntCount&, CntrControl%(0), MemHandle&)
   If ULStat% <> 0 Then Stop

   tmrReadStatus.Enabled = 1
   FirstPoint& = 0

End Sub

Sub cmdStopRead_Click ()

   ' the BACKGROUND operation must be explicitly stopped

   ' Parameters:
   '   BoardNum&   :the number used by CBCONFIG to describe this board
   '   FunctionType:counter operation (CTRFUNCTION)
      
   ULStat% = cbStopBackground(BoardNum&,CTRFUNCTION)

   If ULStat% <> 0 Then Stop

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
   '                  errors must be handled locally
      
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop
    
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
    

   MemHandle& = cbWinBufAlloc(IntCount& * MaxNumCntrs&)    ' set aside memory to hold data
   If MemHandle& = 0 Then Stop								' we're allocating enough for
															' MaxNumCntrs in case actual NumCntrs
															' had not been updated      
   ' Initialize the board level features
   '  Parameters:
   '    BoardNum&    :the number used by CBCONFIG to describe this board
   '    ChipNum&    :chip to be initialized (1 for CTR5, 1 or 2 for CTR10)
   '    FOutDivider&:the F-Out divider (0-15)
   '    Source&     :the signal source for F-Out
   '    Compare1&   :status of comparator 1
   '    Compare2&   :status of comparator 2
   '    TimeOfDay&  :time of day mode control
    
   FOutDivider& = 10        ' sets up OSC OUT for 10Hz signal which can
   Source& = FREQ5          ' be used as interrupt source for this example
   Compare1& = CBDISABLED
   Compare2& = CBDISABLED
   TimeOfDay& = CBDISABLED
    
   ULStat% = cbC9513Init(BoardNum&, ChipNum&, FOutDivider&, Source&, Compare1&, Compare2&, TimeOfDay&)
   If ULStat% <> 0 Then Stop
    
   ' Set the configurable operations of the counter
   '  Parameters:
   '    BoardNum&        :the number used by CBCONFIG to describe this board
   '    CounterNum&     :the counter to be configured (1 to 5)
   '    GateControl&    :gate control value
   '    CounterEdge&    :which edge to count
   '    CountSource&    :signal source
   '    SpecialGate&    :status of special gate
   '    Reload&         :method of reloading
   '    RecyleMode&     :recyle mode
   '    BCDMode&        :counting mode, Binary or BCD
   '    CountDirection& :direction for the counting operation (COUNTUP or COUNTDOWN)
   '    OutputControl&  :output signal type and level
   
   ' Initialize variables for the first of two counters
    
   CounterNum& = 1           ' number of counter used
   GateControl& = NOGATE
   CounterEdge& = POSITIVEEDGE
   CountSource& = FREQ3
   SpecialGate& = CBDISABLED
   Reload& = LOADREG
   RecycleMode& = RECYCLE
   BCDMode& = CBDISABLED
   CountDirection& = COUNTUP
   OutputControl& = ALWAYSLOW
    
   ULStat% = cbC9513Config(BoardNum&, CounterNum&, GateControl&, CounterEdge&, CountSource&, SpecialGate&, Reload&, RecycleMode&, BCDMode&, CountDirection&, OutputControl&)
   If ULStat% <> 0 Then Stop
    
   ' Initialize variables for the second counter
   
   CounterNum& = 2           ' number of counter used
   ULStat% = cbC9513Config(BoardNum&, CounterNum&, GateControl&, CounterEdge&, CountSource&, SpecialGate&, Reload&, RecycleMode&, BCDMode&, CountDirection&, OutputControl&)
   If ULStat% <> 0 Then Stop
    
   ' Load the 2 counters with starting values of zero with cbCLoad%()
   '  Parameters:
   '    BoardNum&    :the number used by CBCONFIG to describe this board
   '    RegName&    :the counter to be loaded with the starting value
   '    LoadValue&  :the starting value to place in the counter
      
   LoadValue& = 0
   RegName& = LOADREG1       ' name of register in counter 1
      
   ULStat% = cbCLoad(BoardNum&, RegName&, LoadValue&)
   If ULStat% <> 0 Then Stop
      
   RegName& = LOADREG2       ' name of register in counter 2
      
   ULStat% = cbCLoad(BoardNum&, RegName&, LoadValue&)
   If ULStat% <> 0 Then Stop

End Sub

Sub tmrReadStatus_Timer ()

   ULStat% = cbGetStatus(BoardNum&, Status%, CurCount&, CurIndex&,CTRFUNCTION)
   If ULStat% <> 0 Then Stop

   FirstPoint&=0
   
   'The calculation below requires that NumCntrs accurately reflects the number
   '  of counters onboard whether or not they are enabled or active.					
   If CurIndex& >0 Then
	  FirstPoint& = NumCntrs&*CurIndex&
   End If

   ULStat% = cbWinBufToArray(MemHandle&, DataBuffer%(0), FirstPoint&, NumCntrs&)
   If ULStat% <> 0 Then Stop

   For I% = 0 To 4
      If CntrControl%(I%) = DISABLED Then
         IntStatus$ = "DISABLED"
      Else
         IntStatus$ = "ENABLED "
      End If

      ' convert type int to type long

      RealCount& = DataBuffer%(I%)
      If RealCount& < 0 Then RealCount& = RealCount& + 65536

      lblCounterNum(I%).Caption = Format$(I% + 1, "0")
      lblIntStatus(I%).Caption = IntStatus$
      lblCount(I%).Caption = Format$(RealCount&, "0")

   Next I%

 
   lblShowTotal.Caption = Format$(CurCount&, "0")

End Sub

