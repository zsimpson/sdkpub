VERSION 2.00
Begin Form frmInfoDisplay 
   Caption         =   "Universal Library Configuration Info"
   ClientHeight    =   5055
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   6480
   Height          =   5460
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   5055
   ScaleWidth      =   6480
   Top             =   1200
   Width           =   6600
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Height          =   375
      Left            =   5400
      TabIndex        =   1
      Top             =   4560
      Width           =   855
   End
   Begin CommandButton cmdPrintInfo 
      Caption         =   "Print Info"
      Default         =   -1  'True
      Height          =   390
      Left            =   2400
      TabIndex        =   0
      Top             =   4560
      Width           =   1140
   End
   Begin TextBox txtBoardInfo 
      Height          =   4335
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   2
      Top             =   120
      Width           =   6015
   End
End
'ULGT03.MAK****************************************************************

'File:                         ULGT03.MAK

'Library Call Demonstrated:    cbGetConfig()

'Purpose:                      Prints a list of all boards installed in
'                              the system and their base addresses.  Also
'                              prints the addresses of each digital and
'                              counter device on each board and any EXP
'                              boards that are connected to A/D channels.

'Other Library Calls:          cbErrHandling(), cbGetBoardName()

'Special Requirements:         ---

'(c) Copyright 1995-2002, Measurement Computing Corp.
'All rights reserved.
'***************************************************************************
Dim MaxNumBoards%, CurrentBoard%, NumBoards%
Dim NumADChans%()
Dim BoardName$
Dim LineFeed$, Info$

Private Sub cmdPrintInfo_Click()
   
   Info$ = ""
   While (Len(Info$) < 1 And CurrentBoard% < MaxNumBoards)
        PrintGenInfo CurrentBoard%
        PrintADInfo CurrentBoard%
        PrintDAInfo CurrentBoard%
        PrintDigInfo CurrentBoard%
        PrintCtrInfo CurrentBoard%
        PrintExpInfo CurrentBoard%
   
        CurrentBoard% = CurrentBoard% + 1
   Wend
   
   If CurrentBoard% > MaxNumBoards% - 1 Then
      If NumBoards% = 0 Then
         Info$ = LineFeed$ + LineFeed$ + Space$(22) + "There are no boards installed." + LineFeed$ + LineFeed$
         Info$ = Info$ + Space$(12) + "You must run InstaCal to install the desired" + LineFeed$
         Info$ = Info$ + Space$(18) + "boards before running this program."
      Else
         Info$ = LineFeed$ + LineFeed$ + Space$(16) + "There are no additional boards installed."
      End If
      cmdPrintInfo.Caption = "Print Info"
      CurrentBoard% = 0
      NumBoards% = 0
   ElseIf Len(Info$) > 0 Then
      cmdPrintInfo.Caption = "Print Next"
      NumBoards% = NumBoards% + 1
   End If
   txtBoardInfo.Text = Info$

End Sub

Private Sub cmdQuit_Click()

    End

End Sub

Private Sub Form_Load()
   
   ' declare revision level of Universal Library

   ULStat% = cbDeclareRevision(CURRENTREVNUM)
   
   LineFeed$ = Chr$(13) + Chr$(10)
   InfoType% = GLOBALINFO
   BoardNum% = 0
   DevNum& = 0
   ConfigItem% = GINUMBOARDS

   'Get the number of boards installed in system
   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
   MaxNumBoards% = ConfigVal&
   CurrentBoard% = 0
   txtBoardInfo.Text = LineFeed$ + LineFeed$ + Space$(12) + "Click on 'Print Info' to display board information."

   ReDim NumADChans%(MaxNumBoards%)
   NumBoards% = 0
   
End Sub

Private Sub PrintADInfo(BoardNum%)
      
   InfoType% = BOARDINFO
   DevNum& = 0
   ConfigItem% = BINUMADCHANS

   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
   'If ULStat% Then Stop
    
   NumADChans%(BoardNum%) = ConfigVal&
   If ConfigVal& Then Info$ = Info$ + Space$(5) + "Number of A/D channels: " + Format$(ConfigVal&, "0") + LineFeed$ + LineFeed$

End Sub

Private Sub PrintCtrInfo(BoardNum%)

   'Get the number of counter devices for this board
   
   InfoType% = BOARDINFO
   DevNum& = 0
   ConfigItem% = BICINUMDEVS
   
   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
   NumDevs& = ConfigVal&
   
   If NumDevs& > 0 Then Info$ = Info$ + Space$(5) + "Counters : " + Format$(NumDevs&, "0") + LineFeed$

   If Len(Info$) Then Info$ = Info$ + LineFeed$
   
End Sub

Private Sub PrintDAInfo(BoardNum%)
   
   InfoType% = BOARDINFO
   DevNum& = 0
   ConfigItem% = BINUMDACHANS
   
   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
   'If ULStat% Then Stop
    
   NumDAChans% = ConfigVal&
   If ConfigVal& > 0 Then Info$ = Info$ + Space$(5) + "Number of D/A channels: " + Format$(ConfigVal&, "0") + LineFeed$ + LineFeed$

End Sub

Private Sub PrintDigInfo(BoardNum%)

   'get the number of digital devices for this board
   InfoType% = BOARDINFO
   DevNum& = 0
   ConfigItem% = BIDINUMDEVS

   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
   
   NumDevs& = ConfigVal&
   
   For DevNum& = 0 To NumDevs& - 1
      'For each digital device, get the base address and number of bits
      
      InfoType% = DIGITALINFO
      ConfigItem% = DINUMBITS
      ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
      
      NumBits% = ConfigVal&
      Info$ = Info$ + Space$(5) + "Digital Device #" + Format$(DevNum&, "0") + " : " + Format$(NumBits%, "0") + " bits" + LineFeed$
   Next
   If Len(Info$) Then Info$ = Info$ + LineFeed$
   
End Sub

Private Sub PrintExpInfo(BoardNum%)

   ' Get the number of Exps attached to BoardNum%
   InfoType% = BOARDINFO
   DevNum& = 0
   ConfigItem% = BINUMEXPS
   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
   NumDevs& = ConfigVal&
         
   For DevNum& = 0 To NumDevs& - 1
      ConfigItem% = XIBOARDTYPE
      InfoType% = EXPANSIONINFO
      ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
      BoardType& = ConfigVal&

      ConfigItem% = XIMUXADCHAN1
      ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
      ADChan1% = ConfigVal&
      If BoardType& = 770 Then
         'it's a CIO-EXP32
         ConfigItem% = XIMUXADCHAN2
         ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
         ADChan2% = ConfigVal&
         Info$ = Info$ + Space$(5) + "A/D channels " + Format$(ADChan1%, "0") + " and " + Format$(ADChan2%, "0") + " connected to EXP(devID=" + Format$(BoardType, 0) + ")." + LineFeed$
      Else
         Info$ = Info$ + Space$(5) + "A/D channel " + Format$(ADChan1%, "0") + " connected to EXP(devID=" + Format$(BoardType, 0) + ")." + LineFeed$
      End If

      
   Next
   If Len(Info$) Then Info$ = Info$ + LineFeed$
   
End Sub

Private Sub PrintGenInfo(BoardNum%)

   InfoType% = BOARDINFO
   DevNum& = 0
   ConfigItem% = BIBOARDTYPE
   
   'Get board type of each board
   
   ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
      
   If (ConfigVal& > 0) Then      'If a board is installed
                                 'Get the board's name
      BoardName$ = Space$(BOARDNAMELEN)
      ULStat% = cbGetBoardName(BoardNum%, BoardName$)
      BoardName$ = RTrim$(BoardName$)   'Drop the space characters
      StringSize% = Len(BoardName$) - 1 'Drop the null character at end of string
      BoardName$ = Left$(BoardName$, StringSize%)
      Info$ = Info$ + "Board #" + Format$(BoardNum%, "0") + " = " + BoardName$ + " at "
             
      'Get the board's base address
      
      ConfigItem% = BIBASEADR
    
      ULStat% = cbGetConfig(InfoType%, BoardNum%, DevNum&, ConfigItem%, ConfigVal&)
             
      BaseAdrStr$ = Hex$(ConfigVal&)
      Info$ = Info$ + "Base Address = " + BaseAdrStr$ + " hex." + LineFeed$ + LineFeed$
   End If
   
End Sub

