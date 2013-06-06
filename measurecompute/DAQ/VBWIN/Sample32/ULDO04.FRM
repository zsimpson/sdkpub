VERSION 2.00
Begin Form frmDigAuxOut 
   Caption         =   "Universal Library Digital Out (AUXPORT)"
   ClientHeight    =   4215
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5655
   Height          =   4620
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4215
   ScaleWidth      =   4965
   Top             =   1200
   Width           =   5085
   Begin CommandButton cmdEndProgram 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   495
      Left            =   3480
      TabIndex        =   6
      Top             =   3360
      Width           =   975
   End
   Begin HScrollBar hsbSetPortVal 
      Height          =   255
      LargeChange     =   3
      Left            =   360
      Max             =   15
      TabIndex        =   1
      Top             =   2160
      Width           =   3135
   End
   Begin TextBox txtShowSetVal 
      Height          =   375
      Left            =   3720
      TabIndex        =   7
      Top             =   2040
      Width           =   735
   End
   Begin OptionButton opt8Bit 
      Caption         =   "8 Bit Port"
      Height          =   255
      Left            =   3360
      TabIndex        =   3
      Top             =   1320
      Width           =   1935
   End
   Begin OptionButton opt4Bit 
      Caption         =   "4 Bit Port"
      Height          =   255
      Left            =   3360
      TabIndex        =   2
      Top             =   1080
      Value           =   -1  'True
      Width           =   1935
   End
   Begin Label lblShowWriteVal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3720
      TabIndex        =   5
      Top             =   2760
      Width           =   615
   End
   Begin Label lblWriteVal 
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   2760
      Width           =   3135
   End
   Begin Label lblInstruct 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Select 4 or 8 bit port and use the scoll bar or the text box to set output data value."
      ForeColor       =   &H000000FF&
      Height          =   735
      Left            =   360
      TabIndex        =   8
      Top             =   1080
      Width           =   2535
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDOut%() and AUXPORT"
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
      Width           =   3375
   End
End
'ULDO04.MAK================================================================

' File:                         ULDO04.MAK

' Library Call Demonstrated:    cbDOut%()

' Purpose:                      Writes a byte to AUXPORT.

' Demonstration:                Writes a selected value to AUXPORT.

' Other Library Calls:          cbErrHandling%()
'                               cbGetConfig using DIGITALINFO
'                               cbDConfigPort()

' Special Requirements:         Board 0 must have a digital port.

' (c) Copyright 1995-2003, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const PortNum% = AUXPORT        ' set port type to auxilliary

Sub cmdEndProgram_Click ()
   
   DataValue% = 0
   ULStat% = cbDOut(BoardNum, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop
  
   End

End Sub

Sub Form_Load ()
   Dim devNum as Long
   Dim PortType as Long
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
   devNum = 0     ' AUXPORT, if exists, is always first digital device
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
   If ULStat% <> NOERRORS Then Stop

   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, outmask)
   If ULStat% <> NOERRORS Then Stop

   ' Only non-configurable AUXPORT's have overlapping input and output bitmasks 
   If (0 = (inmask and outmask))  Then ULStat% = cbDConfigPort(BoardNum, AUXPORT, DIGITALOUT)

End Sub

Sub hsbSetPortVal_Change ()

   ' write the value to AUXPORT
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    PortNum%    :the output port
   '    DataValue%  :the value written to the port

   DataValue% = hsbSetPortVal.Value
   txtShowSetVal.Text = Format$(DataValue%, "0")

   ULStat% = cbDOut(BoardNum, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop
  
   lblWriteVal.Caption = "The value written to AUXPORT was:"
   lblShowWriteVal.Caption = Format$(DataValue%, "0")

End Sub

Sub opt4Bit_Click ()

   hsbSetPortVal.Max = 15
   hsbSetPortVal.LargeChange = 3

End Sub

Sub opt8Bit_Click ()

   hsbSetPortVal.Max = 255
   hsbSetPortVal.LargeChange = 51

End Sub

Sub txtShowSetVal_Change ()

   If Val(txtShowSetVal.Text) > hsbSetPortVal.Max Then
      txtShowSetVal.Text = Format$(hsbSetPortVal.Max, "0")
   End If
   hsbSetPortVal.Value = Val(txtShowSetVal.Text)

End Sub

