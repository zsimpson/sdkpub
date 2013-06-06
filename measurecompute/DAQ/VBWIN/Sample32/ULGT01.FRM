VERSION 2.00
Begin Form frmShowError 
   Caption         =   "Universal Library Error Handling"
   ClientHeight    =   3855
   ClientLeft      =   1095
   ClientTop       =   1485
   ClientWidth     =   4965
   Height          =   4260
   Left            =   1035
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3855
   ScaleWidth      =   4965
   Top             =   1140
   Width           =   5085
   Begin CommandButton cmdQuit 
      Caption         =   "Quit"
      Enabled         =   0   'False
      Height          =   375
      Left            =   3600
      TabIndex        =   5
      Top             =   3120
      Visible         =   0   'False
      Width           =   855
   End
   Begin CommandButton cmdCallFunction 
      Caption         =   "Start"
      Default         =   -1  'True
      Height          =   375
      Left            =   3600
      TabIndex        =   1
      Top             =   3120
      Width           =   855
   End
   Begin Label lblShowErrMsg 
      Alignment       =   2  'Center
      Caption         =   "Error message Shown here."
      ForeColor       =   &H00808080&
      Height          =   855
      Left            =   720
      TabIndex        =   3
      Top             =   1920
      Width           =   3495
   End
   Begin Label lblShowErrCode 
      ForeColor       =   &H000000FF&
      Height          =   255
      Left            =   3240
      TabIndex        =   2
      Top             =   960
      Width           =   615
   End
   Begin Label lblErrorCode 
      Caption         =   "Error message code:"
      Height          =   255
      Left            =   1320
      TabIndex        =   4
      Top             =   960
      Width           =   1815
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbGetErrMsg%()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   4695
   End
End
'ULGT01.MAK================================================================

' File:                         ULGT01.MAK

' Library Call Demonstrated:    cbGetErrMsg%()

' Purpose:                      Returns the error message associated
'                               with an error code.

' Demonstration:                An invalid chan # is generated and the
'                               associated message is retrieved.

' Other Library Calls:          cbErrHandling%()


' (c) Copyright 1994-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Sub cmdCallFunction_Click ()

  cmdCallFunction.Visible = 0
  cmdCallFunction.Enabled = 0
  cmdQuit.Visible = 1
  cmdQuit.Enabled = 1

' generate an error by passing an invalid variable to a routine

  BoardNum = 0
  Gain = BIP5VOLTS
  Chan = -1
  ErrCode% = cbAIn(BoardNum, Chan, Gain, DataValue%)

' trap the error and determine the message to print
'  Parameters:
'    ErrCode%    :the error code returned by the invalid call statement
'    ErrMessage$ :the text of the error message associated with ErrCode%
'                 must be dimensioned to at least the length of the
'                 longest message using ERRSTRLEN

  ErrMessage$ = Space$(ERRSTRLEN)     ' fill ErrMessage$ with spaces

  ULStat% = cbGetErrMsg(ErrCode%, ErrMessage$)
  If ULStat% <> 0 Then End
  
  Beep
  lblShowErrMsg.ForeColor = &HFF&
  lblShowErrCode.Caption = Format$(ErrCode%, "0")
  lblShowErrMsg.Caption = ErrMessage$

End Sub

Sub cmdQuit_Click ()

  End

End Sub

Sub Form_Load ()
   
' declare revision level of Universal Library

   ULStat% = cbDeclareRevision(CURRENTREVNUM)

' Disable external error handling to demonstrate internal handling
   
  ULStat% = cbErrHandling(DONTPRINT, DONTSTOP)
  If ULStat% <> 0 Then Stop

End Sub

