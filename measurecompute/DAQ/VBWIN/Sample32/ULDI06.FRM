VERSION 2.00
Begin Form frmDigIn 
   Caption         =   "Universal Library Digital Bit Input"
   ClientHeight    =   3480
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4890
   Height          =   5460
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3480
   ScaleWidth      =   4890
   Begin  CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   495
      Left            =   3720
      TabIndex        =   1
      Top             =   2760
      Width           =   855
   End
   Begin  Timer tmrReadInputs 
      Interval        =   200
      Left            =   4320
      Top             =   840
   End
   Begin  Label lblBitNum 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Caption         =   "Bit Number"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   968
      TabIndex        =   4
      Top             =   2040
      Width           =   2955
   End
   Begin  Label lblInstruct 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Caption         =   "You may change the bit state by applying a TTL high or a TTL low to the corresponding pin on the port"
      ForeColor       =   &H000000FF&
      Height          =   735
      Left            =   878
      TabIndex        =   3
      Top             =   840
      Width           =   3135
   End
   Begin Label lblShowBitNum 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   2415
      TabIndex        =   2
      Top             =   2070
      Width           =   135
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbDConfigBit()"
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   878
      TabIndex        =   0
      Top             =   240
      Width           =   3135
   End
End
'ULDI06.MAK================================================================

' File:                         ULDI06.MAK

' Library Call Demonstrated:    cbDConfigBit%()

' Purpose:                      Reads the status of a single bit within a digital
'                               port.

' Demonstration:                configures a single bit (within a digital port)
'                               for input and reads the bit status

' Other Library Calls:          cbDBitIn%()
'                               cbErrHandling%()
'                               cbGetConfig() using DIGITALINFO

' Special Requirements:         Board 0 must have a digital port that supports
'                               cbDConfigBit function.

' (c) Copyright 2001-2003, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const PortType% = AUXPORT       ' use first digital port
Const BitNum% = 0               ' test bit zero
Const Direction% = DIGITALIN    ' program port for input mode

Private Sub cmdStopRead_Click()

   End

End Sub

Private Sub Form_Load()
   Dim devNum as Long
   Dim PortType as Long
   Dim inmask, outmask as Long
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

   lblShowBitNum(0).Caption = Format$(BitNum% + 1, "0")
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.


   ' Determine if board has AUXPORT 
   '  Parameters:
   '      DIGITALINFO : information about digital devices on the board 
   '      BoardNum    : the number used by CB.CFG to describe this board
   '      devNum      : 0-based digital device index
   '      DIDEVTYPE   : retrieve type of digital device - AUXPORT, FIRSTPORTA, ...
   '      PortType    : return value for type of device
   devNum = 0        ' AUXPORT, if exists, is always first digital device
   PortType = 0
   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIDEVTYPE, PortType)
   If ULStat% <> NOERRORS Then Stop

   If (PortType <> AUXPORT) Then
      ' ERROR: This board does NOT have an AUXPORT
      tmrReadInputs.Enabled = False
      Stop
      End
   EndIf


   ' Check if AUXPORT needs configuring 
   '  Parameters:
   '      DIGITALINFO : information about digital devices on the board 
   '      BoardNum    : the number used by CB.CFG to describe this board
   '      devNum      : 0-based digital device index
   '      DIINMASK/DIOUTMASK   : get input/output bitmask configuration for port
   '      mask    : bitmask indicating corresponding bit is in direction of ConfigItem(DIINMASk or DIOUTMASK)
   inmask = 0
   outmask = 0
   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIINMASK, inmask)
   If ULStat% <> NOERRORS Then Stop

   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, outmask)
   If ULStat% <> NOERRORS Then Stop

   ' Only non-configurable AUXPORT's have overlapping input and output bitmasks 
   If (0 = (inmask and outmask))  Then 
   
      ' configure a single bit for input or output
      '  Parameters:
      '    BoardNum    :the number used by CB.CFG to describe this board
      '    PortType%   :the port for which to configure the bit
      '    BitNum%     :the bit to configure
      '    Direction%  :sets the bit for input or output   
      ULStat% = cbDConfigBit(BoardNum, PortType, BitNum%, Direction%)
      If ULStat% <> 0 Then Stop

      tmrReadInputs.Enabled = True
   Else
      ' Error : AUXPORT is NOT bitwise-configurable
      Stop
      End
   EndIf

End Sub

Private Sub tmrReadInputs_Timer()

   ' read a single bit status from the digital port
   
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    PortType    :the digital I/O port type
   '    BitNum%     :the bit to read
   '    BitValue%   :the value read from the port

      ULStat% = cbDBitIn(BoardNum, PortType%, BitNum%, BitValue%)
      If ULStat% <> 0 Then Stop

      lblBitNum.Caption = "Bit number " & BitNum% & " state is " & Format$(BitValue%, "0")
   
End Sub

