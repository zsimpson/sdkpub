VERSION 2.00
Begin Form frmSetDigOut 
   Caption         =   "Universal Library Digital Output"
   ClientHeight    =   4005
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4965
   Height          =   4410
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4005
   ScaleWidth      =   4965
   Top             =   1200
   Width           =   5085
   Begin CommandButton cmdEndProgram 
      Caption         =   "Quit"
      Height          =   495
      Left            =   3720
      TabIndex        =   7
      Top             =   3240
      Width           =   855
   End
   Begin TextBox txtValSet 
      Height          =   375
      Left            =   3960
      TabIndex        =   4
      Text            =   "0"
      Top             =   1800
      Width           =   615
   End
   Begin HScrollBar hsbSetDOutVal 
      Height          =   255
      LargeChange     =   51
      Left            =   360
      Max             =   255
      TabIndex        =   1
      Top             =   1800
      Width           =   3375
   End
   Begin Label lblShowValOut 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3360
      TabIndex        =   3
      Top             =   2640
      Width           =   855
   End
   Begin Label lblDataValOut 
      Height          =   255
      Left            =   480
      TabIndex        =   2
      Top             =   2640
      Width           =   2775
   End
   Begin Label lblValSet 
      Caption         =   "Value set:"
      Height          =   255
      Left            =   3840
      TabIndex        =   6
      Top             =   1440
      Width           =   975
   End
   Begin Label lblInstruct 
      Alignment       =   2  'Center
      Caption         =   "Set output value using scroll bar or enter value in Value Set box:"
      ForeColor       =   &H000000FF&
      Height          =   375
      Left            =   840
      TabIndex        =   5
      Top             =   720
      Width           =   3015
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDOut%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   120
      Width           =   4335
   End
End
'ULDO01.MAK================================================================

' File:                         ULDO01.MAK

' Library Call Demonstrated:    cbDOut%()

' Purpose:                      Writes a byte to digital output ports.

' Demonstration:                Configures FIRSTPORTA for output and writes
'                               a value to the port.

' Other Library Calls:          cbDConfigPort%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a digital output port.
'                               Board 0 must have programmable digital ports.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number

Const PortNum% = FIRSTPORTA     ' use first digital port
Const Direction% = DIGITALOUT   ' program digital port A for output

Sub cmdEndProgram_Click ()
   
   DataValue% = 0
  
   ULStat% = cbDOut(BoardNum, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop

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
   '                 errors must be handled locally


   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop

   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
   
   
   ' configure FIRSTPORTA for digital output
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    PortNum%    :the output port
   '    Direction%  :sets the port for input or output

   ULStat% = cbDConfigPort(BoardNum, PortNum%, Direction%)
   If ULStat% <> 0 Then Stop

End Sub

Sub hsbSetDOutVal_Change ()

   ' get a value to write to the port

   DataValue% = hsbSetDOutVal.Value
   txtValSet.Text = Format$(DataValue%, "0")

   ' write the value to FIRSTPORTA
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    PortNum%    :the output port
   '    DataValue%  :the value written to the port
  
   ULStat% = cbDOut(BoardNum, PortNum%, DataValue%)

   If ULStat% <> 0 Then
      Stop
   Else
      lblDataValOut.Caption = "Value written to FIRSTPORTA:"
      lblShowValOut.Caption = Format$(DataValue%, "0")
   End If

End Sub

Sub txtValSet_Change ()
   
   If Val(txtValSet.Text) > 255 Then txtValSet.Text = "255"
   hsbSetDOutVal.Value = Val(txtValSet.Text)

End Sub

