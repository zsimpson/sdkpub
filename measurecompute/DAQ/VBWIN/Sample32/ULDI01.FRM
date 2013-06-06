VERSION 2.00
Begin Form frmDigIn 
   Caption         =   "Universal Library Digital Input"
   ClientHeight    =   3630
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5085
   Height          =   4035
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form2"
   ScaleHeight     =   3630
   ScaleWidth      =   5085
   Top             =   1200
   Width           =   5205
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   495
      Left            =   3840
      TabIndex        =   14
      Top             =   2880
      Width           =   855
   End
   Begin Timer tmrReadInputs 
      Interval        =   500
      Left            =   4560
      Top             =   240
   End
   Begin Label lblPortRead 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   2040
      TabIndex        =   13
      Top             =   2760
      Width           =   495
   End
   Begin Label lblPortsRead 
      Alignment       =   1  'Right Justify
      Caption         =   "Port value read:"
      Height          =   255
      Left            =   360
      TabIndex        =   12
      Top             =   2760
      Width           =   1470
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   4440
      TabIndex        =   3
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   4080
      TabIndex        =   4
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3720
      TabIndex        =   5
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3360
      TabIndex        =   6
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   3000
      TabIndex        =   7
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   2640
      TabIndex        =   8
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   2280
      TabIndex        =   9
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   1920
      TabIndex        =   10
      Top             =   2040
      Width           =   255
   End
   Begin Label lblBitsRead 
      Alignment       =   1  'Right Justify
      Caption         =   "Bit values read:"
      Height          =   255
      Left            =   360
      TabIndex        =   11
      Top             =   2040
      Width           =   1455
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "0"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   7
      Left            =   4440
      TabIndex        =   22
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "1"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   6
      Left            =   4080
      TabIndex        =   21
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "2"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   5
      Left            =   3720
      TabIndex        =   20
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "3"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   4
      Left            =   3360
      TabIndex        =   19
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "4"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   3
      Left            =   3000
      TabIndex        =   18
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "5"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   2
      Left            =   2640
      TabIndex        =   17
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "6"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   1
      Left            =   2280
      TabIndex        =   16
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   2  'Center
      Caption         =   "7"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   0
      Left            =   1920
      TabIndex        =   15
      Top             =   1680
      Width           =   255
   End
   Begin Label lblBitList 
      Alignment       =   1  'Right Justify
      Caption         =   "The first 7 bits are:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1680
      Width           =   1695
   End
   Begin Label lblInstruct 
      Caption         =   "You may change a bit by applying a TTL high or TTL low to digital inputs on FIRSTPORTA."
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   480
      TabIndex        =   1
      Top             =   840
      Width           =   3975
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDIn%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   240
      Width           =   3975
   End
End
'ULDI01.MAK================================================================

' File:                         ULDI01.MAK

' Library Call Demonstrated:    cbDIn%()

' Purpose:                      Reads a digital input port.

' Demonstration:                Configures FIRSTPORTA for input and reads
'                               the value on the port.

' Other Library Calls:          cbDConfigPort%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a digital input port.
'                               Board 0 must have programmable digital ports.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const One% = 1
Const Zero% = 0

Const PortNum% = FIRSTPORTA     ' set port to use
Const Direction% = DIGITALIN    ' set direction of port to input

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
   
   ' configure FIRSTPORTA for digital input
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board.
   '    PortNum%    :the input port
   '    Direction%  :sets the port for input or output
 
  
   ULStat% = cbDConfigPort(BoardNum, PortNum%, Direction%)
   If ULStat% <> 0 Then Stop

End Sub

Sub tmrReadInputs_Timer ()

   ' read FIRSTPORTA digital input and display
     
   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   PortNum%    :the input port
   '   DataValue%  :the value read from the port
    
   ULStat% = cbDIn(BoardNum, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop
      
   ' display the value collected from the port

   lblPortRead.Caption = Format$(DataValue%, "0")

   ' parse DataValue% into bit values to indicate on/off status
      
   For I% = 0 To 7
      If (DataValue% And (2 ^ I%)) Then
         lblBitVal(I%).Caption = Format$(One%, "0")
      Else
         lblBitVal(I%).Caption = Format$(Zero%, "0")
      End If
   Next I%

End Sub

