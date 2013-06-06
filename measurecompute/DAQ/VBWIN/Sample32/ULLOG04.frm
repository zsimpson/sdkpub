VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3750
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6945
   LinkTopic       =   "Form1"
   ScaleHeight     =   3750
   ScaleWidth      =   6945
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4920
      TabIndex        =   9
      Top             =   3120
      Width           =   1335
   End
   Begin VB.CommandButton btnConvertFile 
      Caption         =   "Convert File"
      Enabled         =   0   'False
      Height          =   375
      Left            =   3360
      TabIndex        =   8
      Top             =   3120
      Width           =   1335
   End
   Begin VB.FileListBox File1 
      Height          =   2430
      Left            =   3240
      TabIndex        =   7
      Top             =   240
      Width           =   3495
   End
   Begin VB.DirListBox Dir1 
      Height          =   1665
      Left            =   240
      TabIndex        =   6
      Top             =   1920
      Width           =   2655
   End
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   240
      TabIndex        =   5
      Top             =   1440
      Width           =   2655
   End
   Begin VB.Frame Frame1 
      Caption         =   "Delimiter"
      Height          =   1095
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   2895
      Begin VB.OptionButton rbTab 
         Caption         =   "Tab"
         Height          =   255
         Left            =   1680
         TabIndex        =   4
         Top             =   720
         Width           =   1095
      End
      Begin VB.OptionButton rbSpace 
         Caption         =   "Space"
         Height          =   255
         Left            =   1680
         TabIndex        =   3
         Top             =   360
         Width           =   1095
      End
      Begin VB.OptionButton rbSemicolon 
         Caption         =   "Semicolon"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   720
         Width           =   1095
      End
      Begin VB.OptionButton rbComma 
         Caption         =   "Comma"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1095
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Filename As String
Dim Delimiter As Integer


Private Sub btnCancel_Click()
    End
End Sub

Private Sub btnConvertFile_Click()
    Dim Version As Long
    Dim Size As Long
    Dim SampleInterval As Long
    Dim SampleCount As Long
    Dim StartDate As Long
    Dim StartTime As Long
    Dim ChannelMask As Long
    Dim UnitMask As Long
    Dim DestFilename As String
   
   
    Dim StartSample As Long
    Dim startCount As Long
    Dim DateTags() As Long
    Dim TimeTags() As Long
    
   ' Get the file information
   '  Parameters:
   '    Filename    :name of file to get information from
   '    Version     :version of the file
   '    Size        :size of the file
    
   ULStat% = cbLogGetFileInfo(Filename, Version, Size)
    
    
   ' Get the sample information
   '  Parameters:
   '    Filename            :name of file to get information from
   '    SampleInterval      :time between samples
   '    SampleCount         :number of samples in the file
   '    StartDate           :date of first sample
   '    StartTime           :time of first sample
    
    ULStat% = cbLogGetSampleInfo(Filename, SampleInterval, SampleCount, StartDate, StartTime)

   ' convert the file
   '  Parameters:
   '    Filename            :name of file to get information from
   '    File1.Path          :where to put the converted file
   '    FileType            :type of file to convert to
   '    startSample         :first sample to convert
   '    SampleCount         :number of samples to convert
   '    Delimiter           :field seperator
    
    StartSample = 0
    DestFilename = Replace(UCase(Filename), ".BIN", ".CSV")
    ULStat% = cbLogConvertFile(Filename, DestFilename, StartSample, SampleCount, Delimiter)

            
    If ULStat% <> NOERRORS Then
        MsgBox "cbLogConvertFile failed with error code:  " & ULStat
    End If
        

End Sub

Private Sub Dir1_Change()
    File1.Path = Dir1.Path
End Sub

Private Sub Drive1_Change()
    Dir1.Path = Drive1.Drive
End Sub

Private Sub File1_Click()
    Filename = File1.Path & "\" & File1.Filename
    btnConvertFile.Enabled = True
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
   '                  errors must be handled locally
  
   
   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop


   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
    
    
    rbComma.Value = True
    Delimiter = DELIMITER_COMMA

End Sub

Private Sub rbComma_Click()
    Delimiter = DELIMITER_COMMA
End Sub

Private Sub rbSemicolon_Click()
    Delimiter = DELIMITER_SEMICOLON
End Sub

Private Sub rbSpace_Click()
    Delimiter = DELIMITER_SPACE
End Sub

Private Sub rbTab_Click()
    Delimiter = DELIMITER_TAB
End Sub
