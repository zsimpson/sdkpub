VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   9000
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5460
   LinkTopic       =   "Form1"
   ScaleHeight     =   9000
   ScaleWidth      =   5460
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   2063
      TabIndex        =   17
      Top             =   8400
      Width           =   1335
   End
   Begin VB.Label lblDIOChannelCount 
      Height          =   255
      Left            =   2880
      TabIndex        =   29
      Top             =   7560
      Width           =   1935
   End
   Begin VB.Label lblCJCChannelCount 
      Height          =   255
      Left            =   2880
      TabIndex        =   28
      Top             =   6480
      Width           =   1935
   End
   Begin VB.Label lblAIChannelCount 
      Height          =   255
      Left            =   2880
      TabIndex        =   27
      Top             =   4440
      Width           =   1935
   End
   Begin VB.Label lblUnits 
      Height          =   855
      Left            =   2880
      TabIndex        =   26
      Top             =   5160
      Width           =   1935
   End
   Begin VB.Label lblChannelNumbers 
      Height          =   255
      Left            =   2880
      TabIndex        =   25
      Top             =   4800
      Width           =   1935
   End
   Begin VB.Label lblStartTime 
      Height          =   255
      Left            =   2880
      TabIndex        =   24
      Top             =   3480
      Width           =   1935
   End
   Begin VB.Label lblStartDate 
      Height          =   255
      Left            =   2880
      TabIndex        =   23
      Top             =   3120
      Width           =   1935
   End
   Begin VB.Label lblSampleCount 
      Height          =   255
      Left            =   2880
      TabIndex        =   22
      Top             =   2760
      Width           =   1935
   End
   Begin VB.Label lblSampleInterval 
      Height          =   255
      Left            =   2880
      TabIndex        =   21
      Top             =   2400
      Width           =   1935
   End
   Begin VB.Label lblSize 
      Height          =   255
      Left            =   2880
      TabIndex        =   20
      Top             =   1320
      Width           =   1935
   End
   Begin VB.Label lblVersion 
      Height          =   255
      Left            =   2880
      TabIndex        =   19
      Top             =   960
      Width           =   1935
   End
   Begin VB.Label lblFilename 
      Height          =   255
      Left            =   2880
      TabIndex        =   18
      Top             =   600
      Width           =   1935
   End
   Begin VB.Label Label17 
      Caption         =   "DIOchannel count:"
      Height          =   255
      Left            =   480
      TabIndex        =   16
      Top             =   7680
      Width           =   1935
   End
   Begin VB.Label Label16 
      Caption         =   "Results of cbGetDIOInfo"
      Height          =   255
      Left            =   120
      TabIndex        =   15
      Top             =   7320
      Width           =   1935
   End
   Begin VB.Label Label15 
      Caption         =   "CJC channel count:"
      Height          =   255
      Left            =   480
      TabIndex        =   14
      Top             =   6480
      Width           =   1935
   End
   Begin VB.Label Label14 
      Caption         =   "Results of cbGetCJCInfo"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   6120
      Width           =   1935
   End
   Begin VB.Label Label13 
      Caption         =   "AI channel count:"
      Height          =   255
      Left            =   480
      TabIndex        =   12
      Top             =   4560
      Width           =   1935
   End
   Begin VB.Label Label12 
      Caption         =   "Units:"
      Height          =   255
      Left            =   480
      TabIndex        =   11
      Top             =   5280
      Width           =   1935
   End
   Begin VB.Label Label11 
      Caption         =   "Channel Numbers:"
      Height          =   255
      Left            =   480
      TabIndex        =   10
      Top             =   4920
      Width           =   1935
   End
   Begin VB.Label Label10 
      Caption         =   "Results of cbGetAIInfo"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   4200
      Width           =   1935
   End
   Begin VB.Label Label9 
      Caption         =   "Start time:"
      Height          =   255
      Left            =   480
      TabIndex        =   8
      Top             =   3480
      Width           =   1935
   End
   Begin VB.Label Label8 
      Caption         =   "Start date:"
      Height          =   255
      Left            =   480
      TabIndex        =   7
      Top             =   3120
      Width           =   1935
   End
   Begin VB.Label Label7 
      Caption         =   "Sample count:"
      Height          =   255
      Left            =   480
      TabIndex        =   6
      Top             =   2760
      Width           =   1935
   End
   Begin VB.Label Label6 
      Caption         =   "Sample interval:"
      Height          =   255
      Left            =   480
      TabIndex        =   5
      Top             =   2400
      Width           =   1935
   End
   Begin VB.Label Label5 
      Caption         =   "Results of cbGetSampleInfo"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   2040
      Width           =   2175
   End
   Begin VB.Label Label4 
      Caption         =   "Size:"
      Height          =   255
      Left            =   480
      TabIndex        =   3
      Top             =   1320
      Width           =   1935
   End
   Begin VB.Label Label3 
      Caption         =   "Version:"
      Height          =   255
      Left            =   480
      TabIndex        =   2
      Top             =   960
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "Filename:"
      Height          =   255
      Left            =   480
      TabIndex        =   1
      Top             =   600
      Width           =   1935
   End
   Begin VB.Label Label1 
      Caption         =   "Results of cbGetFileInfo"
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1935
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub btnOK_Click()
    End
End Sub

Private Sub Form_Load()
    Dim Path As String
    Dim Filename As String * 256
    Dim FileNumber As Integer
    Dim SampleInterval As Long
    Dim SampleCount As Long
    Dim StartDate As Long
    Dim StartTime As Long
    Dim ChannelNumbers() As Long
    Dim Units() As Long
    Dim AIChannelCount As Long
    Dim CJCChannelCount As Long
    Dim DIOChannelCount As Long

    Dim Hour As Long
    Dim Minute As Long
    Dim Second As Long
    Dim Month As Long
    Dim Day As Long
    Dim Year As Long
    Dim Postfix As Long
    Dim PostfixStr As String

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


    FileNumber = GETFIRST
    Path = "..\\.."
    ULStat% = cbLogGetFileName(FileNumber, Path, Filename)
    If ULStat% <> 0 Then Stop
   
    
   ' Get the file information
   '  Parameters:
   '    Filename    :name of file to get information from
   '    Version     :version of the file
   '    Size        :size of the file
    
    ULStat% = cbLogGetFileInfo(Filename, Version, Size)
    If ULStat% <> 0 Then Stop
   
    lblFilename.Caption = Filename
    lblVersion.Caption = Version
    lblSize.Caption = Size
    
    
   ' Get the sample information
   '  Parameters:
   '    Filename            :name of file to get information from
   '    SampleInterval      :time between samples
   '    SampleCount         :number of samples in the file
   '    StartDate           :date of first sample
   '    StartTime           :time of first sample
    
    ULStat% = cbLogGetSampleInfo(Filename, SampleInterval, SampleCount, StartDate, StartTime)
    If ULStat% <> 0 Then Stop
   
    lblSampleInterval.Caption = SampleInterval
    lblSampleCount.Caption = SampleCount
    
    Month = (StartDate / 256) And 255
    Day = StartDate And 255
    Year = (StartDate / 65536) And 65535
    lblStartDate.Caption = Month & "/" & Day & "/" & Year
    
    Hour = (StartTime / 65536) And 255
    Minute = (StartTime / 256) And 255
    Second = StartTime And 255
    Postfix = (StartTime / 16777216) And 255
    If Postfix = 0 Then
        PostfixStr = " AM"
    ElseIf Postfix = 1 Then
        PostfixStr = " PM"
    Else
        PostfixStr = ""
    End If
    lblStartTime.Caption = Hour & ":" & Minute & ":" & Second & PostfixStr
    
    
   ' Get the Analog channel count
   '  Parameters:
   '    Filename                :name of file to get information from
   '    AIChannelCount          :number of analog channels logged
    
    ULStat% = cbLogGetAIChannelCount(Filename, AIChannelCount)
    If ULStat% <> 0 Then Stop


   ' Get the Analog information
   '  Parameters:
   '    Filename                :name of file to get information from
   '    ChannelNumbers          :array containing channel numbers that were logged
   '    Units                   :array containing the units for each channel that was logged
   '    AIChannelCount          :number of analog channels logged
    
    ReDim ChannelNumbers(AIChannelCount - 1)
    ReDim Units(AIChannelCount - 1)
    
    ULStat% = cbLogGetAIInfo(Filename, ChannelNumbers&(0), Units&(0))
    If ULStat% <> 0 Then Stop
   
    lblAIChannelCount = AIChannelCount
    
    For i = 0 To AIChannelCount - 1
        lblChannelNumbers = lblChannelNumbers & ChannelNumbers(i)
        If Units(i) = UNITS_RAW Then
            lblUnits = lblUnits & "Raw"
        Else
            lblUnits = lblUnits & "Temperature"
        End If
        
        
        If i < AIChannelCount - 1 Then
            lblChannelNumbers = lblChannelNumbers & ", "
            lblUnits = lblUnits & ", "
        End If
            
   Next i
    
    
   ' Get the CJC information
   '  Parameters:
   '    Filename                :name of file to get information from
   '    CJCChannelCount         :number of CJC channels logged
    
    ULStat% = cbLogGetCJCInfo(Filename, CJCChannelCount)
    If ULStat% <> 0 Then Stop
   
    lblCJCChannelCount = CJCChannelCount
     
    
   ' Get the DIO information
   '  Parameters:
   '    Filename                :name of file to get information from
   '    DIOChannelCount         :number of DIO channels logged
   
    ULStat% = cbLogGetDIOInfo(Filename, DIOChannelCount)
    If ULStat% <> 0 Then Stop
   
    lblDIOChannelCount = DIOChannelCount

End Sub
