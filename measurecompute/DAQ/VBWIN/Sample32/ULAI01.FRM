VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input"
   ClientHeight    =   3300
   ClientLeft      =   2730
   ClientTop       =   1500
   ClientWidth     =   4560
   Height          =   3705
   Left            =   2670
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3300
   ScaleWidth      =   4560
   Top             =   1155
   Width           =   4680
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   390
      Left            =   3480
      TabIndex        =   5
      Top             =   2640
      Width           =   780
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   390
      Left            =   3480
      TabIndex        =   6
      Top             =   2640
      Visible         =   0   'False
      Width           =   780
   End
   Begin TextBox txtNumChan 
      Height          =   375
      Left            =   3360
      TabIndex        =   0
      Text            =   "0"
      Top             =   840
      Width           =   495
   End
   Begin Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   120
      Top             =   840
   End
   Begin Label lblShowVolts 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   2880
      TabIndex        =   8
      Top             =   2040
      Width           =   1455
   End
   Begin Label lblVoltsRead 
      Alignment       =   1  'Right Justify
      Caption         =   "Value converted to voltage:"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   2040
      Width           =   2535
   End
   Begin Label lblShowData 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3360
      TabIndex        =   4
      Top             =   1560
      Width           =   975
   End
   Begin Label lblValueRead 
      Alignment       =   1  'Right Justify
      Caption         =   "Value read from selected channel:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1560
      Width           =   3135
   End
   Begin Label lblChanPrompt 
      Caption         =   "Enter the Channel to display: "
      Height          =   255
      Left            =   600
      TabIndex        =   1
      Top             =   960
      Width           =   2535
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAIn%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   4290
   End
End
'ULAI01.MAK================================================================

' File:                         ULAI01.MAK

' Library Call Demonstrated:    cbAIn%()

' Purpose:                      Reads an A/D Input Channel.

' Demonstration:                Displays the analog input on a user-specified
'                               channel.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on an input channel.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0              ' Board number

Sub cmdStartConvert_Click ()

   cmdStartConvert.Visible = false
   cmdStopConvert.Visible = true
   cmdStopConvert.Default = true
   tmrConvert.Enabled = true

End Sub

Sub cmdStopConvert_Click ()
   
   tmrConvert.Enabled = false
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

End Sub

Sub tmrConvert_Timer ()

   ' Collect the data with cbAIn%()

   '  Parameters:
   '    BoardNum%    :the number used by CB.CFG to describe this board
   '    Chan%       :the input channel number
   '    Gain       :the gain for the board.
   '    DataValue%  :the name for the value collected
    
   Gain = BIP5VOLTS             ' set the gain
   Chan% = Val(txtNumChan.Text)  ' set input channel

   ULStat% = cbAIn(BoardNum%, Chan%, Gain, DataValue%)
   If ULStat% = 30 Then MsgBox "Change the Gain argument to one supported by this board.", 0, "Unsupported Gain"
   If ULStat% <> 0 Then Stop

   ULStat% = cbToEngUnits(BoardNum%, Gain, DataValue%, EngUnits!)
   If ULStat% <> 0 Then Stop

   lblShowData.Caption = Format$(DataValue%, "0")   ' print the counts
   lblShowVolts.Caption = Format$(EngUnits!, "0.000") + " Volts"   ' print the voltage

End Sub

