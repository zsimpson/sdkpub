VERSION 5.00
Begin VB.Form frmDataDisplay 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Voltage Input"
   ClientHeight    =   3735
   ClientLeft      =   2730
   ClientTop       =   1500
   ClientWidth     =   6390
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
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3735
   ScaleWidth      =   6390
   Begin VB.ComboBox cmbRange 
      Height          =   315
      ItemData        =   "VIn01.frx":0000
      Left            =   2880
      List            =   "VIn01.frx":0010
      TabIndex        =   7
      Text            =   "BIP5VOLTS"
      Top             =   1440
      Width           =   1935
   End
   Begin VB.CommandButton cmdStartConvert 
      Appearance      =   0  'Flat
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   390
      Left            =   5340
      TabIndex        =   5
      Top             =   3060
      Width           =   780
   End
   Begin VB.CommandButton cmdStopConvert 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   5340
      TabIndex        =   6
      Top             =   3060
      Visible         =   0   'False
      Width           =   780
   End
   Begin VB.TextBox txtNumChan 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   2880
      TabIndex        =   0
      Text            =   "0"
      Top             =   1860
      Width           =   495
   End
   Begin VB.Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   5460
      Top             =   60
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Range:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1920
      TabIndex        =   9
      Top             =   1440
      Width           =   615
   End
   Begin VB.Label lblPrompt 
      BackColor       =   &H80000009&
      Caption         =   $"VIn01.frx":0042
      Height          =   675
      Left            =   120
      TabIndex        =   8
      Top             =   660
      Width           =   6075
   End
   Begin VB.Label lblShowData 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   3540
      TabIndex        =   4
      Top             =   2460
      Width           =   2175
   End
   Begin VB.Label lblValueRead 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Voltage read from selected channel:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   180
      TabIndex        =   3
      Top             =   2460
      Width           =   3135
   End
   Begin VB.Label lblChanPrompt 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Enter the Channel to display: "
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   1920
      Width           =   2535
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbVIn%()"
      ForeColor       =   &H80000008&
      Height          =   315
      Left            =   1560
      TabIndex        =   2
      Top             =   120
      Width           =   2490
   End
End
Attribute VB_Name = "frmDataDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'ULAI01.MAK================================================================

' File:                         VIn01.MAK

' Library Call Demonstrated:    cbVIn%()

' Purpose:                      Reads an A/D Input Channel.

' Demonstration:                Displays the analog input on a user-specified
'                               channel.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on an input channel.

' (c) Copyright 1995-2007, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0              ' Board number
Dim RangeSelected As Long

Private Sub cmbRange_Click()

   RangeSelected = Choose(cmbRange.ListIndex + 1, BIP10VOLTS, BIP5VOLTS, UNI10VOLTS, UNI5VOLTS)
   
End Sub

Private Sub cmdStartConvert_Click()

   cmdStartConvert.Visible = False
   cmdStopConvert.Visible = True
   cmdStopConvert.Default = True
   tmrConvert.Enabled = True

End Sub

Private Sub cmdStopConvert_Click()
   
   tmrConvert.Enabled = False
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

Private Sub tmrConvert_Timer()

   ' Collect the data with cbVIn%()

   '  Parameters:
   '    BoardNum%    :the number used by CB.CFG to describe this board
   '    Chan%       :the input channel number
   '    Gain       :the gain for the board.
   '    DataValue%  :the name for the value collected
    
   Chan% = Val(txtNumChan.Text)  ' set input channel
   Options% = DEFAULTOPTION

   ULStat% = cbVIn(BoardNum%, Chan%, RangeSelected, DataValue!, Options%)
   If ULStat% = 30 Then MsgBox "Change the Gain argument to one supported by this board.", 0, "Unsupported Gain"
   If ULStat% <> 0 Then Stop

   lblShowData.Caption = DataValue!

End Sub

