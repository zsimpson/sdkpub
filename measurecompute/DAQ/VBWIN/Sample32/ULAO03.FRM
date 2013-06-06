VERSION 5.00
Begin VB.Form frmSendAData 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Universal Library Analog Output "
   ClientHeight    =   3180
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5055
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
   LinkTopic       =   "Form2"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3180
   ScaleWidth      =   5055
   Begin VB.TextBox txtAOutVolts 
      Alignment       =   2  'Center
		BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3840
      TabIndex        =   13
      Text            =   "0.00"
      Top             =   1770
      Width           =   1005
   End
   Begin VB.TextBox txtAOutVolts 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   2640
      TabIndex        =   12
      Text            =   "0.00"
      Top             =   1770
      Width           =   1005
   End
   Begin VB.TextBox txtAOutVolts 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1440
      TabIndex        =   11
      Text            =   "0.00"
      Top             =   1770
      Width           =   1005
   End
   Begin VB.TextBox txtAOutVolts 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   10
      Text            =   "0.00"
      Top             =   1770
      Width           =   1005
   End
   Begin VB.OptionButton optUpdateOnCommand 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Update On Command"
      Height          =   345
      Left            =   750
      TabIndex        =   9
      Top             =   2700
      Value           =   -1  'True
      Width           =   2595
   End
   Begin VB.OptionButton optUpdateImmediate 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Update Immediatelty"
      Height          =   345
      Left            =   750
      TabIndex        =   8
      Top             =   2280
      Width           =   2595
   End
   Begin VB.CommandButton cmdUpdateDACs 
      Caption         =   "Update D/A's"
      Height          =   495
      Left            =   2670
      TabIndex        =   7
      Top             =   810
      Width           =   1695
   End
   Begin VB.CommandButton cmdEndProgram 
      Appearance      =   0  'Flat
      Caption         =   "Quit"
      Height          =   390
      Left            =   3960
      TabIndex        =   1
      Top             =   2520
      Width           =   825
   End
   Begin VB.CommandButton cmdSendData 
      Appearance      =   0  'Flat
      Caption         =   "Send Data"
      Height          =   495
      Left            =   660
      TabIndex        =   2
      Top             =   810
      Width           =   1695
   End
   Begin VB.Label lblChan3 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel 3"
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
      Left            =   3840
      TabIndex        =   6
      Top             =   1440
      Width           =   975
   End
   Begin VB.Label lblChan2 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel 2"
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
      Left            =   2640
      TabIndex        =   5
      Top             =   1440
      Width           =   975
   End
   Begin VB.Label lblChan1 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel 1"
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
      Left            =   1440
      TabIndex        =   4
      Top             =   1440
      Width           =   975
   End
   Begin VB.Label lblChan0 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Channel 0"
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
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Width           =   975
   End
   Begin VB.Label lblDemoFunction 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Demonstration of DAC Update Modes with cbAOut"
      ForeColor       =   &H80000008&
      Height          =   525
      Left            =   840
      TabIndex        =   0
      Top             =   150
      Width           =   3315
   End
End
Attribute VB_Name = "frmSendAData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'ULAO03================================================================

' File:                         ULAO03.FRM

' Library Call Demonstrated:    cbAOut()
'                               cbSetConfig() using BIDACUPDATEMODE and
'                                   BIDACUPDATECMD

' Purpose:                      Demonstrates difference between UPDATEIMMEDIATE
'                               and UPDATEONCOMMAND D/A Update modes

' Demonstration:                Delays outputs until user sends BIDACUPDATECMD

' Other Library Calls:          cbErrHandling()
'                               cbFromEng()

' Special Requirements:         Board 0 must support BIDACUPDATEMODE settings,
'                               such as the PCI-DAC6700's.


' (c) Copyright 2003, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0            ' Board number
Const Range = BIP10VOLTS
Const NumChans = 4
Const DontCare = 0             ' Place-holder for variables not used in particular
                              ' function call
Const AllDacs = -1            ' For BIDACUPDATEMODE, non-negative DevNum specifies
                              ' the D/A whose mode is to be set; negative DevNum
                              ' set the mode for all onboard D/A's
                              
Dim ULStat As Long
                             

Private Sub optUpdateImmediate_Click()
   Dim DevNum As Long
   
   ' Set DAC Update mode to update immediately upon cbAOut or cbAOutScan
   ' Parameters
   '   BOARDINFO   : General information about the board
   '   BoardNum    : Number used by CB.CFG to describe this board
   '   DevNum      : Selects device; in this case, selects D/A channel to configure
   '                 Note that -1 selects all D/A channels
   '   BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
   '                     or cbAOutScan) or upon issuing BIDACUPDATECMD
   '   UPDATEIMMEDIATE : Update D/A outputs immediately upon cbAOut or cbAOutScan
   DevNum = AllDacs
   ULStat = cbSetConfig(BOARDINFO, BoardNum, DevNum, BIDACUPDATEMODE, UPDATEIMMEDIATE)
   
End Sub

Private Sub optUpdateOnCommand_Click()
  
   ' Set DAC Update mode to hold off updating D/A's until command is sent
   ' Parameters
   '   BOARDINFO   : General information about the board
   '   BoardNum    : Number used by CB.CFG to describe this board
   '   DevNum      : Selects device; in this case, selects D/A channel to configure
   '                 Note that -1 selects all D/A channels
   '   BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
   '                     or cbAOutScan) or upon issuing BIDACUPDATECMD
   '   UPDATEONCOMMAND : Delay D/A output updates from cbAOut or cbAOutScan until
   '                     BIDACUPDATECMD is issued.
   DevNum = AllDacs
   ULStat = cbSetConfig(BOARDINFO, BoardNum, AllDacs, BIDACUPDATEMODE, UPDATEONCOMMAND)
   If ULStat<>NOERRORS Then Stop
   
End Sub

Private Sub cmdEndProgram_Click()

   End

End Sub


Private Sub cmdSendData_Click()
   Dim Chan As Integer
   Dim VOLTS As Single
   Dim dadata As Integer

   For Chan = 0 To NumChans - 1
      VOLTS = Val(txtAOutVolts(Chan).Text)
      
      ' Convert from volts to D/A counts
      ' Parameters:
      '   BoardNum    :the number used by CB.CFG to describe this board
      '   Range       :voltage range to be used by cbAOut
      '   volts       :value in engineering units to be converted
      '   dadata      :the value in binary counts corresponding to volts
      ULStat = cbFromEngUnits(BoardNum, Range, VOLTS, dadata)
      If (ULStat <> NOERRORS) Then Stop
      
      ' Load D/A value
      ' Parameters:
      '   BoardNum    :the number used by CB.CFG to describe this board
      '   Chan        :the D/A output channel
      '   Range       :voltage range
      '   dadata      :the value in binary counts to send to Chan
      ULStat = cbAOut(BoardNum, Chan, Range, dadata)
      If (ULStat <> NOERRORS) Then Stop
      
   Next Chan


End Sub


Private Sub cmdUpdateDACs_Click()
   Dim DevNum As Long
   Dim ConfigVal As Long
   
   ' Issue command to update all the D/A's with the last value written
   ' to them via cbAOut or cbAOutScan
   ' Parameters
   '   BOARDINFO   : General information about the board
   '   BoardNum    : Number used by CB.CFG to describe this board
   '   DevNum      : Not used for BIDACUPDATECMD
   '   BIDACUPDATECMD : Update D/A outputs with last value written
   '   ConfigVal   : Note used for BIDACUPDATECMD
   DevNum = DontCare
   ConfigVal = DontCare
   ULStat = cbSetConfig(BOARDINFO, BoardNum, DevNum, BIDACUPDATECMD, ConfigVal)
   If ULStat<>NOERRORS Then Stop
   
End Sub

Private Sub Form_Load()

   ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.
   '  Parameters:
   '    PRINTALL    :all warnings and errors encountered will be printed
   '    DONTSTOP    :if an error is encountered, the program will not stop,
   '                 errors must be handled locally
   ULStat = cbErrHandling(PRINTALL, DONTSTOP)
    
   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
   
   ' Set default mode for updating D/A's on command
   ' Parameters
   '   BOARDINFO   : General information about the board
   '   BoardNum    : Number used by CB.CFG to describe this board
   '   DevNum      : Selects device; in this case, selects D/A channel to configure
   '                 Note that -1 selects all D/A channels
   '   BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
   '                     or cbAOutScan) or upon issuing BIDACUPDATECMD
   '   UPDATEONCOMMAND : Delay D/A output updates from cbAOut or cbAOutScan until
   '                     BIDACUPDATECMD is issued.
   DevNum = AllDacs
   ULStat = cbSetConfig(BOARDINFO, BoardNum, DevNum, BIDACUPDATEMODE, UPDATEONCOMMAND)
   If ULStat<>NOERRORS Then Stop

End Sub

