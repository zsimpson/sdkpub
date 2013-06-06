VERSION 4.00
Begin VB.Form frmLEDTest 
   Caption         =   "Universal Library LED Test"
   ClientHeight    =   3030
   ClientLeft      =   1140
   ClientTop       =   1380
   ClientWidth     =   5025
   Height          =   3390
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   3030
   ScaleWidth      =   5025
   Top             =   1080
   Width           =   5145
   Begin VB.CommandButton cmdFlashBtn 
      Caption         =   "Flash LED"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   795
      Left            =   1320
      TabIndex        =   0
      Top             =   840
      Width           =   2235
   End
End
Attribute VB_Name = "frmLEDTest"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

'ULFL01================================================================

' File:                         ULFL01.FRM

' Library Call Demonstrated:    cbFlashLED%()

' Purpose:                      Flashes onboard LED for visual identification.

' Other Library Calls:          cbErrHandling%()

' Special Requirements:         Board 0 must have an external LED,
'										  such as the miniLAB 1008 and PMD-1208LS.
'                  

' (c) Copyright 2003, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0              ' Board number

Sub Form_Load ()

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

Private Sub cmdFlashBtn_Click()
   Dim ULStat As Integer
   
   ULStat = cbFlashLED(BoardNum)
End Sub
