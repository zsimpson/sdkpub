VERSION 2.00
Begin Form frmDataDisplay 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Universal Library Temperature Measurement"
   ClientHeight    =   5175
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5550
   Height          =   5580
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   5175
   ScaleWidth      =   5550
   Top             =   1200
   Width           =   5670
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   3
      Top             =   4680
      Width           =   855
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   375
      Left            =   4560
      TabIndex        =   4
      Top             =   4680
      Visible         =   0   'False
      Width           =   855
   End
   Begin HScrollBar hsbHiChan 
      Height          =   255
      Left            =   480
      Max             =   15
      TabIndex        =   6
      Top             =   1320
      Width           =   2535
   End
   Begin Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   250
      Left            =   5040
      Top             =   1080
   End
   Begin HScrollBar hsbLoChan 
      Height          =   255
      Left            =   480
      Max             =   15
      TabIndex        =   5
      Top             =   960
      Width           =   2535
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   15
      Left            =   4200
      TabIndex        =   23
      Top             =   4200
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "15"
      Height          =   255
      Index           =   15
      Left            =   3360
      TabIndex        =   43
      Top             =   4200
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   1680
      TabIndex        =   15
      Top             =   4200
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "7"
      Height          =   255
      Index           =   7
      Left            =   840
      TabIndex        =   35
      Top             =   4200
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   14
      Left            =   4200
      TabIndex        =   22
      Top             =   3960
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "14"
      Height          =   255
      Index           =   14
      Left            =   3360
      TabIndex        =   42
      Top             =   3960
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   1680
      TabIndex        =   14
      Top             =   3960
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "6"
      Height          =   255
      Index           =   6
      Left            =   840
      TabIndex        =   34
      Top             =   3960
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   13
      Left            =   4200
      TabIndex        =   21
      Top             =   3720
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "13"
      Height          =   255
      Index           =   13
      Left            =   3360
      TabIndex        =   41
      Top             =   3720
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   1680
      TabIndex        =   13
      Top             =   3720
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "5"
      Height          =   255
      Index           =   5
      Left            =   840
      TabIndex        =   33
      Top             =   3720
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   12
      Left            =   4200
      TabIndex        =   20
      Top             =   3480
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "12"
      Height          =   255
      Index           =   12
      Left            =   3360
      TabIndex        =   40
      Top             =   3480
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   1680
      TabIndex        =   12
      Top             =   3480
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "4"
      Height          =   255
      Index           =   4
      Left            =   840
      TabIndex        =   32
      Top             =   3480
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   11
      Left            =   4200
      TabIndex        =   19
      Top             =   3240
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "11"
      Height          =   255
      Index           =   11
      Left            =   3360
      TabIndex        =   39
      Top             =   3240
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1680
      TabIndex        =   11
      Top             =   3240
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "3"
      Height          =   255
      Index           =   3
      Left            =   840
      TabIndex        =   31
      Top             =   3240
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   10
      Left            =   4200
      TabIndex        =   18
      Top             =   3000
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "10"
      Height          =   255
      Index           =   10
      Left            =   3360
      TabIndex        =   38
      Top             =   3000
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1680
      TabIndex        =   10
      Top             =   3000
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "2"
      Height          =   255
      Index           =   2
      Left            =   840
      TabIndex        =   30
      Top             =   3000
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   9
      Left            =   4200
      TabIndex        =   17
      Top             =   2760
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "9"
      Height          =   255
      Index           =   9
      Left            =   3360
      TabIndex        =   37
      Top             =   2760
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1680
      TabIndex        =   9
      Top             =   2760
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "1"
      Height          =   255
      Index           =   1
      Left            =   840
      TabIndex        =   29
      Top             =   2760
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   8
      Left            =   4200
      TabIndex        =   16
      Top             =   2520
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "8"
      Height          =   255
      Index           =   8
      Left            =   3360
      TabIndex        =   36
      Top             =   2520
      Width           =   615
   End
   Begin Label lblShowData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1680
      TabIndex        =   2
      Top             =   2520
      Width           =   975
   End
   Begin Label lblChanNum 
      Alignment       =   2  'Center
      Caption         =   "0"
      Height          =   255
      Index           =   0
      Left            =   840
      TabIndex        =   28
      Top             =   2520
      Width           =   615
   End
   Begin Label lblTemp2 
      Alignment       =   2  'Center
      Caption         =   "Temperature"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   4080
      TabIndex        =   25
      Top             =   2040
      Width           =   1215
   End
   Begin Label lblChan2 
      Alignment       =   2  'Center
      Caption         =   "Channel"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3240
      TabIndex        =   27
      Top             =   2040
      Width           =   735
   End
   Begin Label lblTemp1 
      Alignment       =   2  'Center
      Caption         =   "Temperature"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   1560
      TabIndex        =   24
      Top             =   2040
      Width           =   1215
   End
   Begin Label lblChan1 
      Alignment       =   2  'Center
      Caption         =   "Channel"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   720
      TabIndex        =   26
      Top             =   2040
      Width           =   855
   End
   Begin Label lblLastChan 
      Caption         =   "Last Channel"
      Height          =   255
      Left            =   3480
      TabIndex        =   45
      Top             =   1320
      Width           =   1335
   End
   Begin Label lblHiChan 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "0"
      Height          =   255
      Left            =   3000
      TabIndex        =   8
      Top             =   1320
      Width           =   255
   End
   Begin Label lblFirstChan 
      Caption         =   "First Channel"
      Height          =   255
      Left            =   3480
      TabIndex        =   44
      Top             =   960
      Width           =   1335
   End
   Begin Label lblLoChan 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "0"
      Height          =   255
      Left            =   3000
      TabIndex        =   7
      Top             =   960
      Width           =   255
   End
   Begin Label lblChanPrompt 
      Alignment       =   1  'Right Justify
      Caption         =   "Select the range of multiplexor channels to display"
      Height          =   255
      Left            =   480
      TabIndex        =   0
      Top             =   600
      Width           =   4455
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbTInScan%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   5175
   End
End
'ULTI02.MAK================================================================

' File:                         ULTI02.MAK

' Library Call Demonstrated:    cbTInScan%()

' Purpose:                      Scans multiplexor input channels.

' Demonstration:                Displays the temperature inputs on a
'                               range of channels.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Unless the board at BoardNum(=0) does not use 
'								EXP boards for temperature measurements(the 
'								CIO-DAS-TC,for example), it must 
'								have an A/D converter with an attached EXP 
'								board.  Thermocouples must be wired to EXP 
'								channels selected.
' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0            ' Board number

Dim UsesEXPs&
Dim DataBuffer!(16)           ' dimension an array to hold
                              ' the temperatures

Sub cmdStartConvert_Click ()

   cmdStartConvert.Visible = 0
   cmdStartConvert.Default = 0
   cmdStopConvert.Visible = 1
   cmdStopConvert.Default = 1
   tmrConvert.Enabled = 1

End Sub

Sub cmdStopConvert_Click ()
   
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

   ' Determine if the board uses EXP boards for temperature measurements
   InfoType% = BOARDINFO
   DevNum% = 0
   ConfigItem% = BIUSESEXPS
   UsesEXPs = 0
   ULStat% = cbGetConfig(Infotype%, BoardNum, DevNum%, ConfigItem%, UsesEXPs)
   if (ULStat%<>0) then UsesEXPs = 0

End Sub

Sub hsbHiChan_Change ()

   If hsbHiChan.Value < hsbLoChan.Value Then hsbLoChan.Value = hsbHiChan.Value
   lblHiChan.Caption = Format$(hsbHiChan.Value, "0")

End Sub

Sub hsbLoChan_Change ()

   If hsbHiChan.Value < hsbLoChan.Value Then hsbHiChan.Value = hsbLoChan.Value
   lblLoChan.Caption = Format$(hsbLoChan.Value, "0")
    
End Sub

Sub tmrConvert_Timer ()

   ' Collect the data with cbTInScan%()
   '  Input values will be collected from a range of thermocouples.
   '  The data value will be updated and displayed until a key is pressed.
   '  Parameters:
   '    BoardNum       :the number used by CB.CFG to describe this board
   '    LowChan%       :the starting channel of the scan
   '    HighChan%      :the ending channel of the scan
   '    CBScale%       :temperature scale (Celsius, Fahrenheit, Kelvin)
   '    AvgCount%      :the number of samples to average to reduce noise
   '    DataBuffer!()  :the array where the temperature values are collected

   CBScale% = FAHRENHEIT
   AvgCount% = 50
   ADChan% = 0        'the channel on the A/D

   LowMux% = hsbLoChan.Value
   HighMux% = hsbHiChan.Value
   Options% = 0
   If UsesEXPs>0 Then
	LowChan% = (ADChan% + 1) * 16 + LowMux%
	HighChan% = (ADChan% + 1) * 16 + HighMux%
   Else
	LowChan% = LowMux%
	HighChan% = HighMux%
   End If

   NumChans% = HighMux% - LowMux% + 1

   ULStat% = cbTInScan(BoardNum, LowChan%, HighChan%, CBScale%, DataBuffer!(0), Options%)
   If ULStat% <> 0 Then Stop
  
   If LowMux% <> 0 Then
      For j% = 0 To LowMux% - 1
         lblShowData(j%).Caption = ""
      Next j%
   End If
   If HighMux% <> 15 Then
      For j% = HighMux% + 1 To 15
         lblShowData(j%).Caption = ""
      Next j%
   End If

   Element% = 0
  
   For i% = LowMux% To HighMux%
      lblShowData(i%).Caption = Format$(DataBuffer!(Element%), "0\°\F")       ' print the value
      Element% = Element% + 1
   Next i%

End Sub

