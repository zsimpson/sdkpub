VERSION 5.00
Begin VB.Form frmDataDisplay 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Daq Input Scan"
   ClientHeight    =   5010
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   6450
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00FF0000&
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5010
   ScaleWidth      =   6450
   Begin VB.CommandButton cmdStopConvert 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   495
      Left            =   3240
      TabIndex        =   13
      Top             =   4440
      Width           =   855
   End
   Begin VB.CommandButton cmdStart 
      Appearance      =   0  'Flat
      Caption         =   "Read"
      Height          =   495
      Left            =   2280
      TabIndex        =   46
      Top             =   4440
      Width           =   855
   End
   Begin VB.Label Label1 
      BackColor       =   &H80000005&
      Caption         =   "Channel:"
      Height          =   255
      Left            =   120
      TabIndex        =   57
      Top             =   600
      Width           =   855
   End
   Begin VB.Label lblShowChanType 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Height          =   255
      Index           =   3
      Left            =   4920
      TabIndex        =   56
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblShowChanType 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Height          =   255
      Index           =   2
      Left            =   3720
      TabIndex        =   55
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblShowChanType 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Height          =   255
      Index           =   1
      Left            =   2400
      TabIndex        =   54
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblShowChanType 
      Alignment       =   2  'Center
      BackColor       =   &H80000005&
      Height          =   255
      Index           =   0
      Left            =   1080
      TabIndex        =   53
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblChanType 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Type:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   52
      Top             =   960
      Width           =   615
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   39
      Left            =   4920
      TabIndex        =   45
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   38
      Left            =   3720
      TabIndex        =   44
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   37
      Left            =   2400
      TabIndex        =   43
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   36
      Left            =   1080
      TabIndex        =   42
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   35
      Left            =   4920
      TabIndex        =   41
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   34
      Left            =   3720
      TabIndex        =   40
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   33
      Left            =   2400
      TabIndex        =   39
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   32
      Left            =   1080
      TabIndex        =   38
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   31
      Left            =   4920
      TabIndex        =   37
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   30
      Left            =   3720
      TabIndex        =   36
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   29
      Left            =   2400
      TabIndex        =   35
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   28
      Left            =   1080
      TabIndex        =   34
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   27
      Left            =   4920
      TabIndex        =   33
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   26
      Left            =   3720
      TabIndex        =   32
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   25
      Left            =   2400
      TabIndex        =   31
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   24
      Left            =   1080
      TabIndex        =   30
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   23
      Left            =   4920
      TabIndex        =   29
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   22
      Left            =   3720
      TabIndex        =   28
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   21
      Left            =   2400
      TabIndex        =   27
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   20
      Left            =   1080
      TabIndex        =   26
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   11
      Left            =   4920
      TabIndex        =   17
      Top             =   2280
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   10
      Left            =   3720
      TabIndex        =   16
      Top             =   2280
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   9
      Left            =   2400
      TabIndex        =   15
      Top             =   2280
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   8
      Left            =   1080
      TabIndex        =   14
      Top             =   2280
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   19
      Left            =   4920
      TabIndex        =   25
      Top             =   2760
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   18
      Left            =   3720
      TabIndex        =   24
      Top             =   2760
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   17
      Left            =   2400
      TabIndex        =   23
      Top             =   2760
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   16
      Left            =   1080
      TabIndex        =   22
      Top             =   2760
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   15
      Left            =   4920
      TabIndex        =   21
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   14
      Left            =   3720
      TabIndex        =   20
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   13
      Left            =   2400
      TabIndex        =   19
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   12
      Left            =   1080
      TabIndex        =   18
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   4920
      TabIndex        =   12
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3720
      TabIndex        =   11
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   2400
      TabIndex        =   10
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   1080
      TabIndex        =   9
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   4920
      TabIndex        =   8
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3720
      TabIndex        =   7
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   2400
      TabIndex        =   6
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label lblADData 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1080
      TabIndex        =   5
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label lblShowRange 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   4920
      TabIndex        =   51
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblShowRange 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3720
      TabIndex        =   50
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblShowRange 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   2400
      TabIndex        =   49
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblShowRange 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1080
      TabIndex        =   48
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblRange 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Range:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   47
      Top             =   1320
      Width           =   735
   End
   Begin VB.Label lblChan3 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   4920
      TabIndex        =   4
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label lblChan2 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   3720
      TabIndex        =   3
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label lblChan1 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   2400
      TabIndex        =   2
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label lblChan0 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1080
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of cbDaqInScan()"
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   600
      TabIndex        =   0
      Top             =   120
      Width           =   5265
   End
End
Attribute VB_Name = "frmDataDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'DaqInScan01.MAK================================================================

' File:                         DaqInScan01.MAK

' Library Call Demonstrated:    cbDaqInScan()
'
' Purpose:                      Synchronously scans Analog channels, Digital ports and Counters
'                               in the foreground.
'
' Demonstration:                Collects data on Analog Channels 0 and 1,
'                               FirstPortA and Counter 0.
'
' Other Library Calls:          cbErrHandling()
'                               cbDConfigPort()
'                               cbCConfigScan()
'
' Special Requirements:         Board 0 must support cbDaqInScan.

' (c) Copyright 1995-2006, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0             ' Board number
Const ChanCount& = 4            ' Number of channels in scan
Const NumPoints& = 10           ' Number of data points to collect
Const NumElements& = ChanCount& * NumPoints&

Dim ADData%(NumElements&)       ' dimension an array to hold the input values
Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ChanArray%(ChanCount&)       ' array to hold channel queue information
Dim ChanTypeArray%(ChanCount&)   ' array to hold channel type information
Dim GainArray%(ChanCount&)       ' array to hold gain queue information



Private Sub cmdStopConvert_Click()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat% <> 0 Then Stop                ' other programs
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
    
   MemHandle& = cbWinBufAlloc(NumElements&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

  'load the arrays with values
   ChanArray%(0) = 0
   ChanTypeArray%(0) = ANALOG
   GainArray%(0) = BIP10VOLTS
   
   lblChan0.Caption = "0"
   lblShowChanType(0).Caption = "ANALOG"
   lblShowRange(0).Caption = "±10 Volts"

   ChanArray%(1) = FIRSTPORTA
   ChanTypeArray%(1) = DIGITAL8
   GainArray%(1) = NotUsed
   
   lblChan1.Caption = "FIRSTPORTA"
   lblShowChanType(1).Caption = "DIGITAL8"
   lblShowRange(1).Caption = "NotUsed"

   ChanArray%(2) = 0
   ChanTypeArray%(2) = CTR16
   GainArray%(2) = NotUsed
   
   lblChan2.Caption = "0"
   lblShowChanType(2).Caption = "CTR16"
   lblShowRange(2).Caption = "NotUsed"

   ChanArray%(3) = 5
   ChanTypeArray%(3) = ANALOG
   GainArray%(3) = BIP5VOLTS
   
   lblChan3.Caption = "5"
   lblShowChanType(3).Caption = "ANALOG"
   lblShowRange(3).Caption = "±5 Volts"

End Sub

Private Sub cmdStart_Click()

    'configure FIRSTPORTA  for digital input
   PortNum& = ChanArray(1)
   Direction& = DIGITALIN
   ULStat% = cbDConfigPort(BoardNum%, PortNum, Direction)
   If ULStat% <> 0 Then Stop

   ' configure counter 0
   CounterNum& = ChanArray(2)
   ULStat% = cbCConfigScan(BoardNum%, CounterNum&, STOP_AT_MAX, CTR_DEBOUNCE_NONE, 0, CTR_RISING_EDGE, 0, CounterNum&)
   If ULStat% <> 0 Then Stop

   ' Collect the values with cbDaqInScan()
   '  Parameters:
   '    BoardNum%        :the number used by CB.CFG to describe this board
   '    ChanArray%[]     :array of channel values
   '    ChanTypeArray%[] : array of channel types
   '    GainArray%[]     :array of gain values
   '    ChansCount&        :the number of elements in the arrays (0=disable queue)
   '    PretrigCount&    :number of pre-trigger A/D samples to collect
   '    CBCount&         :the total number of A/D samples to collect
   '    CBRate&          :sample rate in samples per second
   '    ADData%[]        :the array for the collected data values
   '    Options          :data collection options

   PretrigCount& = 0
   CBCount& = NumElements&           ' Number of data points to collect
   Options = CONVERTDATA
   CBRate& = 100                    ' Acquire data at 100 Hz

   If MemHandle& = 0 Then Stop       ' check that a handle to a memory buffer exists

   ULStat% = cbDaqInScan(BoardNum%, ChanArray%(0), ChanTypeArray%(0), GainArray%(0), ChanCount&, CBRate&, PretrigCount&, CBCount&, MemHandle&, Options)
   If ULStat% <> 0 Then Stop

   ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

   ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, CBCount&)
   If ULStat% <> 0 Then Stop

   i% = 0
   For SampleNum% = 0 To NumPoints& - 1
      For ChannelNum% = 0 To ChanCount& - 1
         lblADData(i%).Caption = Format$(ADData%(i%), "0")
         i% = i% + 1
      Next ChannelNum%
   Next SampleNum%
End Sub

