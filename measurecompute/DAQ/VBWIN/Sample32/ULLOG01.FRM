VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3285
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3285
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox List1 
      Height          =   1815
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   4335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Get Files"
      Height          =   495
      Left            =   1680
      TabIndex        =   0
      Top             =   2520
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Dim Path As String
    Dim Filename As String * 256
    Dim FileNumber As Long
    
    
   ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.
   '  Parameters:
   '    PRINTALL    :all warnings and errors encountered will be printed
   '    DONTSTOP    :if an error is encountered, the program will not stop,
   '                  errors must be handled locally
  
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop
        
    Path = "..\.."
    
    FileNumber = GETFIRST
    ULStat% = cbLogGetFileName(FileNumber, Path, Filename)
    If ULStat% <> 0 Then Stop

    List1.Clear
    List1.AddItem (Filename)
    
        
    FileNumber = GETNEXT
    While ULStat% <> NOMOREFILES
        ULStat% = cbLogGetFileName(FileNumber, Path, Filename)
        If ULStat% <> 0 And ULStat% <> NOMOREFILES Then Stop

        If ULStat% <> NOMOREFILES Then List1.AddItem (Filename)
   Wend
    
    
End Sub

