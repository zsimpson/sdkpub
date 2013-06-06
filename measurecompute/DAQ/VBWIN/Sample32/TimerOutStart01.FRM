VERSION 5.00
Begin VB.Form frmSendData 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Timer Output "
   ClientHeight    =   3765
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5820
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
   ScaleHeight     =   3765
   ScaleWidth      =   5820
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "Update"
      Height          =   375
      Left            =   3023
      TabIndex        =   8
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton cmdEndProgram 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   4800
      TabIndex        =   5
      Top             =   3240
      Width           =   825
   End
   Begin VB.TextBox txtFrequencyToSet 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   1583
      TabIndex        =   0
      Text            =   "10000"
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Label lblShowFrequency 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4200
      TabIndex        =   6
      Top             =   2640
      Width           =   1575
   End
   Begin VB.Label lblFrequency 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   2640
      Width           =   3975
   End
   Begin VB.Label lblShowValue 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4200
      TabIndex        =   4
      Top             =   2370
      Width           =   1575
   End
   Begin VB.Label lblValueSent 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2370
      Width           =   3975
   End
   Begin VB.Label lblUseScroll 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Enter a frequency within the timer's range and click Update Button when done"
      ForeColor       =   &H80000008&
      Height          =   495
      Left            =   863
      TabIndex        =   2
      Top             =   960
      Width           =   4095
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbTimerStart() and cbTimerStop()"
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   1103
      TabIndex        =   1
      Top             =   360
      Width           =   3615
   End
End
Attribute VB_Name = "frmSendData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'TimerOutStart01.frm================================================================

' File:                          TimerOutStart01.frm

'  Library Call Demonstrated:    cbTimerStart()
'                                cbTimerStop()

'  Purpose:                      Controls an Output Timer Channel.

'  Demonstration:                Sends a frequency output to Timer 0.

'  Other Library Calls:          MccDaq.MccService.ErrHandling()

'  Special Requirements:         Board 0 must have a Timer output.

' (c) Copyright 1995-2006, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0          ' Board number
Const TimerNum& = 0             ' output channel

Private Sub cmdEndProgram_Click()
  cbTimerOutStop BoardNum, TimerNum&
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

End Sub

Private Sub cmdUpdate_Click()
    Dim Frequency As Double
    lblShowValue.Caption = ""
    lblShowFrequency.Caption = ""

    Frequency = Val(txtFrequencyToSet.Text)
    If (Frequency > 0) Then
      Dim FrequencySet As Double
      FrequencySet = Frequency
      ' Parameters:
      '   TimerNum       :the timer output channel
      '   Frequency      :the frequency to output
      ULStat% = cbTimerOutStart(BoardNum, TimerNum&, Frequency)
      If ULStat% = 0 Then
        lblValueSent.Caption = "The frequency sent to timer 0 was:"
        lblFrequency.Caption = "The frequency output from timer channel 0 is:"
        lblShowValue.Caption = Format$(FrequencySet, "0.0##") & " Hz"
        lblShowFrequency.Caption = Format$(Frequency, "0.0##") & " Hz"
      Else
        Stop
      End If
    End If

End Sub



