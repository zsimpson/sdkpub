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
   Begin TextBox TextBoardNum 
      Height          =   375
      Left            =   1680
      TabIndex        =   10
      Text            =   "1"
      Top             =   2640
      Width           =   615
   End
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
   Begin Label LabelBoardNum 
      BackColor       =   &H80000009&
      Caption         =   "Board Number"
      Height          =   495
      Left            =   840
      TabIndex        =   11
      Top             =   2640
      Width           =   735
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
'ULMBDO02.MAK================================================================

' File:                         ULMBDO02.MAK

' Library Call Demonstrated:    cbDBitOut%()

' Purpose:                      Sets the state of a single digital output bit for MetraBus cards

' Demonstration:                Configures FIRSTPORTA for output and writes
'                               the bit values.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 1 must have a digital output port.

' (c) Copyright 2000-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Dim BoardNum%					' Board number

Const PortNum% = FIRSTPORTA     ' use first digital port
Const Direction% = DIGITALOUT   ' program first digital port for output mode

Private Sub chkSetBit_Click(Index As Integer)
         
   PortType% = PortNum%
   BitNum% = Index
   BitValue% = chkSetBit(Index).Value
   
   ULStat% = cbDBitOut(BoardNum%, PortType%, BitNum%, BitValue%)
   If ULStat% <> 0 Then Stop

End Sub

Private Sub cmdEndProgram_Click()

   DataValue% = 0
  
   ULStat% = cbDOut(BoardNum%, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop
  
   End

End Sub

Private Sub Form_Load()
    
    BoardNum% = 1
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
   

End Sub

Private Sub TextBoardNum_Change()
    
    x% = Val(TextBoardNum.Text)
    If (x% < 1) Or (x% > 15) Then TextBoardNum.Text = "1"
    BoardNum = Val(TextBoardNum.Text)
    
End Sub
