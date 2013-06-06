VERSION 2.00
Begin Form frmSetBitOut 
   Caption         =   "Universal Library Digital Bit Out"
   ClientHeight    =   3330
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5085
   Height          =   3735
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3330
   ScaleWidth      =   5085
   Top             =   1200
   Width           =   5205
   Begin CommandButton cmdEndProgram 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   375
      Left            =   3600
      TabIndex        =   9
      Top             =   2760
      Width           =   855
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 7"
      Height          =   255
      Index           =   7
      Left            =   2880
      TabIndex        =   2
      Top             =   2280
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 3"
      Height          =   255
      Index           =   3
      Left            =   720
      TabIndex        =   6
      Top             =   2280
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 6"
      Height          =   255
      Index           =   6
      Left            =   2880
      TabIndex        =   3
      Top             =   1920
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 2"
      Height          =   255
      Index           =   2
      Left            =   720
      TabIndex        =   7
      Top             =   1920
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 5"
      Height          =   255
      Index           =   5
      Left            =   2880
      TabIndex        =   4
      Top             =   1560
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 1"
      Height          =   255
      Index           =   1
      Left            =   720
      TabIndex        =   8
      Top             =   1560
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 4"
      Height          =   255
      Index           =   4
      Left            =   2880
      TabIndex        =   5
      Top             =   1200
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 0"
      Height          =   255
      Index           =   0
      Left            =   720
      TabIndex        =   1
      Top             =   1200
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDBitOut%() with AUXPORT"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   615
      Left            =   600
      TabIndex        =   0
      Top             =   240
      Width           =   3735
   End
End
'ULDO05.MAK================================================================

' File:                         ULDO05.MAK

' Library Call Demonstrated:    cbDBitOut%()

' Purpose:                      Sets the state of a single digital output bit.

' Demonstration:                Writes bit values to AUXPORT.

' Other Library Calls:          cbDConfigPort%()
'                               cbErrHandling%()
'                               cbGetConfig() using DIGITALINFO

' Special Requirements:         Board 0 must have a digital output port.

' (c) Copyright 1995-2003, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number

Dim PortType as Long   
Const Direction% = DIGITALOUT   ' program first digital port for output mode

Sub chkSetBit_Click (Index As Integer)

   BitNum% = Index
   BitValue% = chkSetBit(BitNum%).Value
   
   ULStat% = cbDBitOut(BoardNum, PortType, BitNum%, BitValue%)
   If ULStat% = 68 Then
      MsgBox "Boards only supports bit numbers less than " + Format$(BitNum%, "0"), 0, "Bit value too high"
   ElseIf ULStat% <> 0 Then
      Stop
   End If

End Sub

Sub cmdEndProgram_Click ()

   DataValue% = 0
  
   ULStat% = cbDOut(BoardNum, PortType, DataValue%)
   If ULStat% <> 0 Then Stop
  
   End

End Sub

Sub Form_Load ()
   Dim devNum as Long
   Dim inmask, outmask as Long
   
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
   If (ULStat% <> NOERRORS) Then Stop

   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, outmask)
   If (ULStat% <> NOERRORS) Then Stop

   ' Only non-configurable AUXPORT's have overlapping input and output bitmasks 
   If (0 = (inmask and outmask))  Then ULStat% = cbDConfigPort(BoardNum, AUXPORT, DIGITALOUT)
   
End Sub

