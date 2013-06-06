VERSION 2.00
Begin Form frmAnalogTrig 
   Caption         =   "Universal Library Analog Trigger"
   ClientHeight    =   4335
   ClientLeft      =   3315
   ClientTop       =   1485
   ClientWidth     =   4995
   Height          =   4740
   Left            =   3255
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4335
   ScaleWidth      =   4995
   Top             =   1140
   Width           =   5115
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   390
      Left            =   3960
      TabIndex        =   7
      Top             =   3840
      Visible         =   0   'False
      Width           =   900
   End
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   390
      Left            =   3960
      TabIndex        =   2
      Top             =   3840
      Width           =   900
   End
   Begin TextBox txtShowTrigSet 
      Height          =   375
      Left            =   3720
      TabIndex        =   10
      Text            =   "1.25"
      Top             =   2400
      Width           =   1215
   End
   Begin OptionButton chkPosTrigger 
      Caption         =   "Trigger above trigger value"
      Height          =   300
      Left            =   960
      TabIndex        =   4
      Top             =   2010
      Width           =   3015
   End
   Begin OptionButton chkNegTrigger 
      Caption         =   "Trigger below trigger value"
      Height          =   300
      Left            =   960
      TabIndex        =   3
      Top             =   1725
      Value           =   -1  'True
      Width           =   3015
   End
   Begin TextBox txtShowChannel 
      Height          =   372
      Left            =   3552
      TabIndex        =   0
      Text            =   "0"
      Top             =   576
      Width           =   372
   End
   Begin Timer tmrStartConvert 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4320
      Top             =   480
   End
   Begin Label lblShowVolts 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3720
      TabIndex        =   11
      Top             =   3360
      Width           =   1215
   End
   Begin Label lblShowTrigValue 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3960
      TabIndex        =   5
      Top             =   3000
      Width           =   735
   End
   Begin Label lblTrigStatus 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   3000
      Width           =   3735
   End
   Begin Label lblEnterVal 
      Alignment       =   1  'Right Justify
      Caption         =   "Enter a trigger value in volts: "
      Height          =   255
      Left            =   480
      TabIndex        =   12
      Top             =   2520
      Width           =   3135
   End
   Begin Label lblWarn 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Note: Channel above must have an input that meets the trigger conditions or program will appear to hang."
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   120
      TabIndex        =   8
      Top             =   1080
      Width           =   4740
   End
   Begin Label lblTriggerChan 
      Alignment       =   1  'Right Justify
      Caption         =   "Enter the trigger input channel:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   3180
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbATrig%()"
      Height          =   375
      Left            =   120
      TabIndex        =   9
      Top             =   0
      Width           =   4695
   End
End
'ULAI07.FRM ============================================================

' File:                         ULAI07.FRM

' Library Call Demonstrated:    cbATrig%()

' Purpose:                      Waits for a specified analog input channel to
'                               go above or below a specified value.

' Demonstration:                Displays the digital value of a user-specified
'                               analog input channel when the user-specifed
'                               value is detected.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on an input channel.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

' Initialize variables

Const BoardNum% = 0              ' Board number
Const Gain% = BIP5VOLTS

Sub cmdStartConvert_Click ()

   tmrStartConvert.Enabled = -1
   cmdStartConvert.Visible = 0
   cmdStopConvert.Visible = -1
   cmdStopConvert.Default = -1
   lblTrigStatus.Caption = "Waiting for trigger..."

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
   '                  errors must be handled locally
    
      
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop
    
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.

End Sub


Function GetTrigCounts(bd%, range%, val!) as Integer

   'check if gain is bipolar or unipolar
   FSCount& = 0
   FSEngUnits! = 0.0
   ulstat% = cbToEngUnits(bd%, range%, FSCounts&, FSEngUnits!)
   If (FSEngUnits! < 0 ) Then
      'range is bipolar
      'check bitness
      FSCounts& = &H0FFF  'max 12-bit value
      ulstat% = cbToEngUnits(bd%, range%, FSCounts&, FSEngUnits!)
      If (FSEngUnits! < 0 ) Then
         'must be 16-bit A/D
         FSCounts& = 65535  
         iFSCounts% = &HFFFF
         ulstat% = cbToEngUnits(bd%, range%, iFSCounts%, FSEngUnits!)
      End if

      fCounts! = (FSCounts&/2.0)*(1.0 + val!/FSEngUnits!)
   Else
      'range is unipolar
      'check bitness
      FSCounts& = &H0FFF  'max 12-bit value
      ulstat% = cbToEngUnits(bd%, range%, FSCounts&, FSEngUnits!)
      ulstat% = cbToEngUnits(bd%, range%, FSCounts&+&H1000, fCounts!)
      If (fCounts!>=2.0*FSEngUnits!) Then
         'must be 16-bit A/D
         FSCounts& = 65535
         iFSCounts% = &HFFFF
         ulstat% = cbToEngUnits(bd%, range%, iFSCounts%, FSEngUnits!)
      End if

      fCounts! = FSCounts& * val!/FSEngUnits!
   End if

   If fCounts!>FSCounts& Then fCounts! = FSCounts&
   If fCounts!>32767 Then fCounts! = fCounts! - 65536

   GetTrigCounts% = Int(fCounts!)
End Function



Sub tmrStartConvert_Timer ()
   ' Monitor the channel with cbATrig%()
   '  The input value that meets the threshold will become DataValue%
   '  The data value will be updated and displayed until a Stop event occurs.
   '  Parameters:
   '    BoardNum%   :the number used by CB.CFG to describe this board
   '    Chan%       :the input channel number
   '    TrigType%   :specifies whether the trigger is to be above
   '                 or below TrigValue%
   '    TrigValue%  :the threshold value that will cause the trigger
   '    Gain    :the gain for the board
   '    DataValue%  :the input value read from Chan%

   Chan% = Val(txtShowChannel.Text)
   EngUnits! = Val(txtShowTrigSet.Text)

   TrigValue% = GetTrigCounts(BoardNum%, Gain%, EngUnits!)
   TrigType% = Abs(chkNegTrigger.Value)
   
   ULStat% = cbATrig(BoardNum%, Chan%, TrigType%, TrigValue%, Gain%, DataValue%)
   If ULStat% <> 0 Then Stop
   
   ' print the value that meets the threshold
  
   lblTrigStatus.Caption = "The value that caused the last trigger was:"
   lblShowTrigValue.Caption = Format$(DataValue%, "0")

   ULStat% = cbToEngUnits(BoardNum%, Gain%, DataValue%, EngUnits!)
   lblShowVolts.Caption = Format$(EngUnits!, "0.00###\V")

End Sub

