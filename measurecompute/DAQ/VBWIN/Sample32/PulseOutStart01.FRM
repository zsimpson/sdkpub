VERSION 5.00
Begin VB.Form frmSendData 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Pulse Output "
   ClientHeight    =   4530
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
   ScaleHeight     =   4530
   ScaleWidth      =   5820
   Begin VB.TextBox txtDutyCycleToSet 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1590
      TabIndex        =   10
      Text            =   ".5"
      Top             =   2040
      Width           =   1215
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "Update"
      Height          =   375
      Left            =   3023
      TabIndex        =   8
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton cmdEndProgram 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   4800
      TabIndex        =   5
      Top             =   3960
      Width           =   825
   End
   Begin VB.TextBox txtFrequencyToSet 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1583
      TabIndex        =   0
      Text            =   "10000"
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label lblDutyCycle 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   15
      Top             =   3480
      Width           =   3975
   End
   Begin VB.Label lblShowDutyCycle 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4200
      TabIndex        =   14
      Top             =   3480
      Width           =   1575
   End
   Begin VB.Label lblDCValueSent 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   3240
      Width           =   3975
   End
   Begin VB.Label lblDCShowValue 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4200
      TabIndex        =   12
      Top             =   3240
      Width           =   1575
   End
   Begin VB.Label lblDC 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Duty Cycle:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   11
      Top             =   2040
      Width           =   1095
   End
   Begin VB.Label lblFreq 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Frequency:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   9
      Top             =   1680
      Width           =   1095
   End
   Begin VB.Label lblShowFrequency 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4200
      TabIndex        =   6
      Top             =   2880
      Width           =   1575
   End
   Begin VB.Label lblFrequency 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   2880
      Width           =   3975
   End
   Begin VB.Label lblFreqShowValue 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4200
      TabIndex        =   4
      Top             =   2610
      Width           =   1575
   End
   Begin VB.Label lblFreqValueSent 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2610
      Width           =   3975
   End
   Begin VB.Label lblUseScroll 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Enter a frequency and duty cycle within the timer's range and click Update Button when done"
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   960
      TabIndex        =   2
      Top             =   840
      Width           =   4095
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbPulseOutStart() and cbPulseOutStop()"
      ForeColor       =   &H80000008&
      Height          =   495
      Left            =   1110
      TabIndex        =   1
      Top             =   240
      Width           =   3615
   End
End
Attribute VB_Name = "frmSendData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'PulseOutStart01.frm================================================================

' File:                          PulseOutStart01.frm

'  Library Call Demonstrated:    cbPulseOutStart()
'                                cbPulseOutStop()

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
  cbPulseOutStop BoardNum, TimerNum&
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
    lblFreqShowValue.Caption = ""
    lblShowFrequency.Caption = ""
    lblDCShowValue.Caption = ""
    lblShowDutyCycle.Caption = ""

    Frequency = Val(txtFrequencyToSet.Text)
    DutyCycle = Val(txtDutyCycleToSet.Text)
    
    If (Frequency > 0) Then
      Dim FrequencySet As Double
      Dim DutyCycleSet As Double
      Dim PulseCount As Long
      Dim InitialDelay As Double
      Dim IdleState As Long
      Dim Options As Long
      
      PulseCount = 0
      InitialDelay = 0
      IdleState = IDLE_LOW
      Options = 0
      
      FrequencySet = Frequency
      DutyCycleSet = DutyCycle
      
      ' Parameters:
      '   TimerNum       :the timer output channel
      '   Frequency      :the frequency to output
      '   DutyCycle      :the duty cycle
      ULStat% = cbPulseOutStart(BoardNum, TimerNum&, Frequency, DutyCycle, PulseCount&, InitialDelay, IdleState&, Options&)
      If ULStat% = 0 Then
        lblFreqValueSent.Caption = "The frequency sent to timer 0 was:"
        lblFrequency.Caption = "The frequency output from timer channel 0 is:"
        lblFreqShowValue.Caption = Format$(FrequencySet, "0.0#####") & " Hz"
        lblShowFrequency.Caption = Format$(Frequency, "0.0#####") & " Hz"
        
        lblDCValueSent.Caption = "The duty dycle sent to timer 0 was:"
        lblDutyCycle.Caption = "The duty cycle output from timer channel 0 is:"
        lblDCShowValue.Caption = Format$(DutyCycleSet, "0.0#####")
        lblShowDutyCycle.Caption = Format$(DutyCycle, "0.0#####")
      Else
        Stop
      End If
    End If

End Sub
