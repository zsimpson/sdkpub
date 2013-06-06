VERSION 5.00
Begin VB.Form frmSendAData 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Analog Output "
   ClientHeight    =   3960
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5475
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkMode        =   1  'Source
   LinkTopic       =   "Form2"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3960
   ScaleWidth      =   5475
   Begin VB.ComboBox cmbRange 
      Height          =   315
      ItemData        =   "VOut01.frx":0000
      Left            =   3600
      List            =   "VOut01.frx":0010
      TabIndex        =   6
      Text            =   "BIP5VOLTS"
      Top             =   1860
      Width           =   1515
   End
   Begin VB.CommandButton cmdEndProgram 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   3720
      TabIndex        =   3
      Top             =   3360
      Width           =   825
   End
   Begin VB.TextBox txtVoltsToSet 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3600
      TabIndex        =   0
      Top             =   2400
      Width           =   1455
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Range:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   2880
      TabIndex        =   8
      Top             =   1920
      Width           =   735
   End
   Begin VB.Label lblPrompt 
      BackColor       =   &H80000009&
      Caption         =   $"VOut01.frx":0042
      Height          =   795
      Left            =   480
      TabIndex        =   7
      Top             =   780
      Width           =   4695
   End
   Begin VB.Label lblShowVoltage 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3720
      TabIndex        =   4
      Top             =   2940
      Width           =   1215
   End
   Begin VB.Label lblVoltage 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   2940
      Width           =   3015
   End
   Begin VB.Label lblUseScroll 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Enter a voltage within the DACs range:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   2460
      Width           =   3375
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbVOut%()"
      ForeColor       =   &H80000008&
      Height          =   315
      Left            =   600
      TabIndex        =   1
      Top             =   120
      Width           =   3615
   End
End
Attribute VB_Name = "frmSendAData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'VOut01.MAK================================================================

' File:                         VOut01.MAK

' Library Call Demonstrated:    cbVOut%()

' Purpose:                      Writes to a D/A Output Channel.

' Demonstration:                Sends a digital output to D/A 0.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have a D/A converter.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0          ' Board number
Const Chan% = 0             ' output channel
Dim RangeSelected As Long

Private Sub cmbRange_Click()

   RangeSelected = Choose(cmbRange.ListIndex + 1, BIP10VOLTS, BIP5VOLTS, UNI10VOLTS, UNI5VOLTS)
   
End Sub

Private Sub cmdEndProgram_Click()
   
   End

End Sub

Private Sub Form_Load()

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
   Me.cmbRange.ListIndex = 1

End Sub

Private Sub txtVoltsToSet_Change()

   ' send the digital output value to D/A 0 with cbVOut%()

   DataValue! = Val(txtVoltsToSet.Text)
   Options& = DEFAULTOPTION

   ' Parameters:
   '   BoardNum    :the number used by CB.CFG to describe this board
   '   Chan%       :the D/A output channel
   '   Range%      :ignored if board does not have programmable rage
   '   DataValue%  :the value to send to Chan%
   
   ULStat% = cbVOut(BoardNum%, Chan%, RangeSelected, DataValue!, Options&)
   If ULStat% <> 0 Then Stop
  
   lblVoltage.Caption = "The voltage at DAC channel " + Format$(Chan%, "0") + " is:"
   lblShowVoltage.Caption = Format$(DataValue!, "0.0##") + " Volts"

End Sub

