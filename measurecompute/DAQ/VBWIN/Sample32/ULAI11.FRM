VERSION 2.00
Begin Form frmManualConvert 
   Caption         =   "Universal Library Analog Data Convert"
   ClientHeight    =   4635
   ClientLeft      =   1650
   ClientTop       =   1515
   ClientWidth     =   6495
   Height          =   5040
   Left            =   1590
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4635
   ScaleWidth      =   6495
   Top             =   1170
   Width           =   6615
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   396
      Left            =   5280
      TabIndex        =   3
      Top             =   3840
      Width           =   780
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   396
      Left            =   5280
      TabIndex        =   4
      Top             =   3840
      Visible         =   0   'False
      Width           =   780
   End
   Begin Frame fraGainSel 
      Caption         =   "Select Gain"
      Height          =   855
      Left            =   3120
      TabIndex        =   16
      Top             =   1560
      Width           =   3255
      Begin OptionButton opt10VUni 
         Caption         =   "10V Unipolar"
         Height          =   255
         Left            =   1680
         TabIndex        =   20
         Top             =   480
         Width           =   1455
      End
      Begin OptionButton opt10VBip 
         Caption         =   "10V Bipolar"
         Height          =   255
         Left            =   240
         TabIndex        =   18
         Top             =   480
         Width           =   1335
      End
      Begin OptionButton opt5VUni 
         Caption         =   "5V Unipolar"
         Height          =   255
         Left            =   1680
         TabIndex        =   19
         Top             =   240
         Width           =   1455
      End
      Begin OptionButton opt5VBip 
         Caption         =   "5V Bipolar"
         Height          =   255
         Left            =   240
         TabIndex        =   17
         Top             =   240
         Value           =   -1  'True
         Width           =   1335
      End
   End
   Begin Frame fraChanSelect 
      Caption         =   "Channel Select"
      Height          =   855
      Left            =   120
      TabIndex        =   21
      Top             =   1560
      Width           =   2775
      Begin TextBox txtNumChan 
         Height          =   375
         Left            =   2160
         TabIndex        =   23
         Text            =   "0"
         Top             =   360
         Width           =   375
      End
      Begin Label lblChanPrompt 
         Alignment       =   1  'Right Justify
         Caption         =   "Channel to display: "
         Height          =   255
         Left            =   240
         TabIndex        =   22
         Top             =   360
         Width           =   1815
      End
   End
   Begin Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   300
      Left            =   6000
      Top             =   840
   End
   Begin Label lblShowCalcResults 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Left            =   3360
      TabIndex        =   11
      Top             =   4104
      Width           =   1212
   End
   Begin Label lblCalcResult 
      Alignment       =   1  'Right Justify
      Caption         =   "Value after conversion to voltage:"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   4110
      Width           =   3135
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3360
      TabIndex        =   2
      Top             =   3840
      Width           =   975
   End
   Begin Label lblValueRead 
      Alignment       =   1  'Right Justify
      Caption         =   "Value read from selected channel:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   3840
      Width           =   3135
   End
   Begin Label lblGainCodeVal 
      Alignment       =   2  'Center
      Height          =   255
      Left            =   5400
      TabIndex        =   7
      Top             =   3120
      Width           =   495
   End
   Begin Label lblGainCode 
      Alignment       =   2  'Center
      Height          =   255
      Left            =   3600
      TabIndex        =   6
      Top             =   3120
      Width           =   1335
   End
   Begin Label lblMinVal 
      Alignment       =   1  'Right Justify
      Height          =   255
      Left            =   2640
      TabIndex        =   8
      Top             =   3120
      Width           =   495
   End
   Begin Label lblFullScaleNeg 
      Alignment       =   1  'Right Justify
      Caption         =   "Negative full scale voltage:"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   3120
      Width           =   2415
   End
   Begin Label lblMaxVal 
      Alignment       =   1  'Right Justify
      Height          =   255
      Left            =   2640
      TabIndex        =   9
      Top             =   2880
      Width           =   495
   End
   Begin Label lblFullScalePos 
      Alignment       =   1  'Right Justify
      Caption         =   "Positive full scale voltage:"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   2880
      Width           =   2415
   End
   Begin Label lblCVLabel 
      Alignment       =   2  'Center
      Caption         =   "Code Value"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   5160
      TabIndex        =   15
      Top             =   2760
      Width           =   1215
   End
   Begin Label lblGCLabel 
      Alignment       =   2  'Center
      Caption         =   "Gain Code"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3720
      TabIndex        =   14
      Top             =   2760
      Width           =   1095
   End
   Begin Label lblInstruct 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "NOTE: Please be certain that the board you are using supports the gain you are choosing and, if gain is not programmable, that the switches on the board are set correctly."
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   240
      TabIndex        =   5
      Top             =   720
      Width           =   5895
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of raw data conversion."
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6210
   End
End
'ULAI11.MAK================================================================

' File:                         ULAI11.MAK

' Library Call Demonstrated:    cbAIn%()
'                               cbToEngUnits()

' Purpose:                      Convert a raw data value to a voltage.

' Demonstration:                Displays a voltage on a user-specified
'                               channel.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on specified input channel.
'                               If you are using a 16 bit board, see the
'                               CONVERT RAW DATA VALUES section for the
'                               correct lines of code to be used.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0           ' Board number

Sub cmdStartConvert_Click ()

   tmrConvert.Enabled = -1
   cmdStartConvert.Visible = 0
   cmdStartConvert.Default = 0
   cmdStopConvert.Visible = -1
   cmdStopConvert.Default = -1

End Sub

Sub cmdStopConvert_Click ()

   tmrConvert.Enabled = 0
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


   lblGainCode.Caption = "BIP5VOLTS"  'initialize gain
   lblGainCodeVal.Caption = Format$(BIP5VOLTS, "0")
   lblMinVal.Caption = "-5"
   lblMaxVal.Caption = "5"

End Sub

Sub opt10VBip_Click ()

   lblGainCode.Caption = "BIP10VOLTS"
   lblGainCodeVal.Caption = Format$(BIP10VOLTS, "0")
   lblMinVal.Caption = "-10"
   lblMaxVal.Caption = "10"

End Sub

Sub opt10VUni_Click ()

   lblGainCode.Caption = "UNI10VOLTS"
   lblGainCodeVal.Caption = Format$(UNI10VOLTS, "0")
   lblMinVal.Caption = "0"
   lblMaxVal.Caption = "10"

End Sub

Sub opt5VBip_Click ()

   lblGainCode.Caption = "BIP5VOLTS"
   lblGainCodeVal.Caption = Format$(BIP5VOLTS, "0")
   lblMinVal.Caption = "-5"
   lblMaxVal.Caption = "5"

End Sub

Sub opt5VUni_Click ()

   lblGainCode.Caption = "UNI5VOLTS"
   lblGainCodeVal.Caption = Format$(UNI5VOLTS, "0")
   lblMinVal.Caption = "0"
   lblMaxVal.Caption = "5"

End Sub

Sub tmrConvert_Timer ()
        
   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   Chan%       :the input channel number
   '   Gain       :the gain for the board.
   '   DataValue%  :the name for the value collected
        
   Chan% = Val(txtNumChan.Text)
   Gain = Val(lblGainCodeVal.Caption)
   MaxVal = Val(lblMaxVal.Caption)
   MinVal = Val(lblMinVal.Caption)

   ULStat% = cbAIn(BoardNum, Chan%, Gain, DataValue%)
   If ULStat% <> 0 Then Stop
   
   '******* CONVERT RAW DATA VALUES TO VOLTAGES ********

   ULStat% = cbToEngUnits(BoardNum, Gain, DataValue%, EngUnits!)
   If ULStat% <> 0 Then Stop

   lblShowData.Caption = Format$(DataValue%, "0")
   lblShowCalcResults.Caption = Format$(EngUnits!, "0.000 \V\o\l\t\s")

End Sub

