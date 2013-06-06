VERSION 2.00
Begin Form frmDigAuxIn 
   Caption         =   "Universal Library Digital In (AUXPORT)"
   ClientHeight    =   3690
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4965
   Height          =   4095
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3690
   ScaleWidth      =   4965
   Top             =   1200
   Width           =   5085
   Begin CommandButton cmdEndProgram 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   495
      Left            =   3840
      TabIndex        =   3
      Top             =   3000
      Width           =   855
   End
   Begin Timer tmrReadInputs 
      Interval        =   200
      Left            =   4440
      Top             =   360
   End
   Begin Label lblShowPortVal 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4080
      TabIndex        =   2
      Top             =   2280
      Width           =   495
   End
   Begin Label lblPortVal 
      Height          =   255
      Left            =   720
      TabIndex        =   1
      Top             =   2280
      Width           =   3135
   End
   Begin Label lblInstruct 
      Alignment       =   2  'Center
      Caption         =   "Input a TTL high or low level to auxillary digital inputs to change Data Value."
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   720
      TabIndex        =   4
      Top             =   1080
      Width           =   3495
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDIn%() and AUXPORT"
      Height          =   615
      Left            =   600
      TabIndex        =   0
      Top             =   240
      Width           =   3615
   End
End
'ULDI04===============================================================

' File:                         ULDI04.FRM

' Library Call Demonstrated:    cbDIn%()

' Purpose:                      Reads a value from AUXPORT.

' Demonstration:                Select number of bits and read AUXPORT.

' Other Library Calls:          cbErrHandling%()
'                               cbGetConfig() using DIGITALINFO
'                               cbDConfigPort()

' Special Requirements:         Board 0 must have a digital port.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const PortNum% = AUXPORT        ' set type of port to auxilliary

Sub cmdEndProgram_Click ()
   
   End

End Sub

Sub Form_Load ()
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
   devNum = 0  ' AUXPORT, if exists, is always first digital device
   PortType = 0
   ULStat% = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIDEVTYPE, PortType)
   If ULStat%<>NOERRORS Then Stop

   If (PortType <> AUXPORT) Then
      ' ERROR: This board does NOT have an AUXPORT
      tmrReadInputs.Enabled = False
      Stop
      End
   Else
      tmrReadInputs.Enabled = True
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
   If ULStat%<>NOERRORS Then Stop

   ' Only non-configurable AUXPORT's have overlapping input and output bitmasks 
   If (0 = (inmask and outmask))  Then ULStat% = cbDConfigPort(BoardNum, AUXPORT, DIGITALIN)

End Sub

Sub tmrReadInputs_Timer ()

   ULStat% = cbDIn(BoardNum, PortNum%, DataValue%)
   If ULStat% <> 0 Then Stop
   
   lblPortVal.Caption = "Value read at auxillary digital inputs:"
   lblShowPortVal.Caption = Format$(DataValue%, "0")

End Sub

