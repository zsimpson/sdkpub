VERSION 2.00
Begin Form frmSendAData 
   Caption         =   "Universal Library Analog Output "
   ClientHeight    =   3765
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4980
   Height          =   4170
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form2"
   ScaleHeight     =   3765
   ScaleWidth      =   4980
   Top             =   1200
   Width           =   5100
   Begin CommandButton cmdEndProgram 
      Caption         =   "Quit"
      Height          =   390
      Left            =   3720
      TabIndex        =   5
      Top             =   3240
      Width           =   825
   End
   Begin TextBox txtVoltsToSet 
      Height          =   375
      Left            =   1800
      TabIndex        =   0
      Top             =   1560
      Width           =   1215
   End
   Begin Label lblShowVoltage 
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3600
      TabIndex        =   6
      Top             =   2640
      Width           =   1215
   End
   Begin Label lblVoltage 
      Height          =   255
      Left            =   480
      TabIndex        =   7
      Top             =   2640
      Width           =   3015
   End
   Begin Label lblShowValue 
      ForeColor       =   &H00FF0000&
      Height          =   252
      Left            =   3960
      TabIndex        =   4
      Top             =   2376
      Width           =   852
   End
   Begin Label lblValueSent 
      Height          =   252
      Left            =   480
      TabIndex        =   3
      Top             =   2376
      Width           =   3372
   End
   Begin Label lblUseScroll 
      Caption         =   "Enter a voltage within the DACs range:"
      Height          =   255
      Left            =   840
      TabIndex        =   2
      Top             =   1200
      Width           =   3375
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAOut%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Top             =   360
      Width           =   3615
   End
End
'ULAO01.MAK================================================================

' File:                         ULAO01.MAK

' Library Call Demonstrated:    cbAOut%()

' Purpose:                      Writes to a D/A Output Channel.

' Demonstration:                Sends a digital output to D/A 0.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have a D/A converter.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0          ' Board number
Const Chan% = 0             ' output channel
Const Range% = BIP5VOLTS

Sub cmdEndProgram_Click ()
   
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

Sub txtVoltsToSet_Change ()

   ' send the digital output value to D/A 0 with cbAOut%()

   EngUnits! = Val(txtVoltsToSet.Text)

   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   Chan%       :the D/A output channel
   '   Range%      :ignored if board does not have programmable rage
   '   DataValue%  :the value to send to Chan%
   
   
   ULStat% = cbFromEngUnits(BoardNum%, Range%, EngUnits!, DataValue%)
   If ULStat% <> 0 Then Stop
         
   ULStat% = cbAOut(BoardNum%, Chan%, Range%, DataValue%)
   If ULStat% <> 0 Then Stop
  
   lblValueSent.Caption = "The count sent to DAC channel " + Format$(Chan%, "0") + " was:"
   lblVoltage.Caption = "The voltage at DAC channel " + Format$(Chan%, "0") + " is:"
   lblShowValue.Caption = Format$(DataValue%, "0")
   lblShowVoltage.Caption = Format$(EngUnits!, "0.0##") + " Volts"

End Sub

