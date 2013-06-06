VERSION 2.00
Begin Form frmListBoards 
   Caption         =   "Universal Library List Boards"
   ClientHeight    =   4740
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4605
   Height          =   5145
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   19.75
   ScaleMode       =   4  'Character
   ScaleWidth      =   38.375
   Top             =   1200
   Width           =   4725
   Begin CommandButton cmdQuit 
      Caption         =   "&Quit"
      Height          =   375
      Left            =   3480
      TabIndex        =   2
      Top             =   4200
      Width           =   975
   End
   Begin CommandButton cmdListSupported 
      Caption         =   "Supported Boards"
      Height          =   372
      Left            =   1740
      TabIndex        =   1
      Top             =   4200
      Width           =   1632
   End
   Begin CommandButton cmdListInstalled 
      Caption         =   "Installed Boards"
      Height          =   372
      Left            =   120
      TabIndex        =   0
      Top             =   4200
      Width           =   1512
   End
   Begin TextBox txtListBoards 
      Height          =   3852
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Top             =   120
      Width           =   4332
   End
End
'ULGT04.MAK*****************************************************************

'File:                         ULGT04.MAK

'Library Call Demonstrated:    cbGetBoardName()

'Purpose:                      Prints a list of all boards installed in
'                              the system.  Prints a list of all supported
'                              boards.

'Other Library Calls:          cbErrHandling(), cbGetConfig()

'Special Requirements:         ---

'(c) Copyright 1995-2002, Measurement Computing Corp.
'All rights reserved.
'***************************************************************************

Dim NumBoards&

Sub cmdListInstalled_Click ()
   Dim typeVal as Long

   'Get board type of each board currently installed
   LineFeed$ = Chr$(13) + Chr$(10)

   txtListBoards.Text = "Currently installed boards:" + LineFeed$ + LineFeed$
   For BoardNum& = 0 To NumBoards& - 1
      ULStat% = cbGetConfig(BOARDINFO, BoardNum&, 0, BIBOARDTYPE, typeVal)
	  If typeVal<>0 Then
		BoardName$ = Space$(BOARDNAMELEN)
		ULStat% = cbGetBoardName(BoardNum&, BoardName$)
		BoardName$ = RTrim$(BoardName$)   'Drop the space characters
		StringSize% = Len(BoardName$) - 1 'Drop the null character at end of string
		BoardName$ = Left$(BoardName$, StringSize%)
		txtListBoards.Text = txtListBoards.Text + "Board #" + Format$(BoardNum& + x%, "0") + "= " + BoardName$ + LineFeed$
	  End If
   Next

End Sub

Sub cmdListSupported_Click ()
   
   txtListBoards.Text = ""
   LineFeed$ = Chr$(13) + Chr$(10)
   
   'Get the first board type in list of supported boards
   'The first string in the boardlist is "Not Supported"
   BoardName$ = Space$(BOARDNAMELEN)
   
   BoardNum& = GETFIRST
   ULStat% = cbGetBoardName(BoardNum&, BoardName$)
   BoardName$ = RTrim$(BoardName$)   'Drop the space characters
   StringSize% = Len(BoardName$) - 1 'Drop the null character at end of string
   BoardName$ = Left$(BoardName$, StringSize%)
   BoardList$ = "The first string in the board name list is:" + LineFeed$ + "'" + BoardName$ + "'" + LineFeed$ + LineFeed$

   'Get each consecutive board type in list
   Do
      BoardName$ = Space$(BOARDNAMELEN)
      BoardNum& = GETNEXT
      ULStat% = cbGetBoardName(BoardNum&, BoardName$)
      BoardName$ = RTrim$(BoardName$)   'Drop the space characters
      StringSize% = Len(BoardName$) - 1 'Drop the null character at end of string
      BoardName$ = Left$(BoardName$, StringSize%)
      If StringSize% Then BoardName$ = BoardName$ + Space$(BOARDNAMELEN - StringSize%)
      BoardList$ = BoardList$ + BoardName$ + LineFeed$
   Loop While Len(BoardName$) > 3
   txtListBoards.Text = BoardList$

End Sub

Sub cmdQuit_Click ()

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

   'Get the number of boards installed in system
   
   InfoType% = GLOBALINFO
   BoardNum& = 0
   DevNum% = 0
   ConfigItem% = GINUMBOARDS

   ULStat% = cbGetConfig(InfoType%, BoardNum&, DevNum%, ConfigItem%, ConfigVal&)
   NumBoards& = ConfigVal&
   
End Sub

