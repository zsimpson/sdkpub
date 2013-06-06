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
      Top             =   2040
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 3"
      Height          =   255
      Index           =   3
      Left            =   720
      TabIndex        =   6
      Top             =   2040
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 6"
      Height          =   255
      Index           =   6
      Left            =   2880
      TabIndex        =   3
      Top             =   1680
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 2"
      Height          =   255
      Index           =   2
      Left            =   720
      TabIndex        =   7
      Top             =   1680
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 5"
      Height          =   255
      Index           =   5
      Left            =   2880
      TabIndex        =   4
      Top             =   1320
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 1"
      Height          =   255
      Index           =   1
      Left            =   720
      TabIndex        =   8
      Top             =   1320
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 4"
      Height          =   255
      Index           =   4
      Left            =   2880
      TabIndex        =   5
      Top             =   960
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin CheckBox chkSetBit 
      Caption         =   "Set bit 0"
      Height          =   255
      Index           =   0
      Left            =   720
      TabIndex        =   1
      Top             =   960
      Value           =   2  'Grayed
      Width           =   1215
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDBitOut%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   4575
   End
End
'ULDO02.MAK================================================================

' File:                         ULDO02.MAK

' Library Call Demonstrated:    cbDBitOut%()

' Purpose:                      Sets the state of a single digital output bit.

' Demonstration:                Configures FIRSTPORTA for output and writes
'                               the bit values.

' Other Library Calls:          cbDConfigPort%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a digital output port.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number


Const Direction% = DIGITALOUT   ' program first digital port for output mode
Dim PortNum%
Dim PortType%
Dim FirstBit%

Private Sub chkSetBit_Click(Index As Integer)
         

   BitNum% = Index
   BitValue% = chkSetBit(Index).Value
   
   ' For boards whose first port is not FIRSTPORTA (such as the USB-ERB08
   ' and the USB-SSR08) offset the BitNum by FirstBit
   
   If PortNum% = AUXPORT Then
        PortType% = AUXPORT
   Else
        PortType% = FIRSTPORTA
   End If
   
   ULStat% = cbDBitOut(BoardNum, PortType%, FirstBit% + BitNum%, BitValue%)
   If ULStat% <> 0 Then Stop

End Sub

Private Sub cmdEndProgram_Click()

   DataValue% = 0
  
   ULStat% = cbDOut(BoardNum, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop
  
   End

End Sub

Private Sub Form_Load()
    
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
   
   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, 0, DIDEVTYPE, FirstPort&)
   If ULStat% <> 0 Then Stop
    
    Select Case FirstPort&
        Case FIRSTPORTA
            FirstBit% = 0
            
        Case FIRSTPORTB
            FirstBit% = 8
           
        Case FIRSTPORTCL
            FirstBit% = 16
               
        Case FIRSTPORTCH
            FirstBit% = 20
            
        Case Else
            FirstBit% = 0

        End Select
   
   ' configure the first port(usually FIRSTPORTA) for input
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board.
   '    PortNum%    :the input port
   '    Direction%  :sets the port for input or output
   PortNum% = FirstPort&

   ULStat% = cbDConfigPort(BoardNum, PortNum%, Direction%)
   If ULStat% <> 0 Then Stop

   ' if the first port is FIRSTPORTCL, configure FIRSTPORTCH, too
    If FirstPort& = FIRSTPORTCL Then
        ULStat% = cbDConfigPort (BoardNum, FirstPort&+1, Direction%)
    End If

    If ULStat% <> 0 Then Stop

End Sub

