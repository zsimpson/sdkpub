VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6075
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   12780
   LinkTopic       =   "Form1"
   ScaleHeight     =   6075
   ScaleWidth      =   12780
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   5843
      TabIndex        =   1
      Top             =   5520
      Width           =   1095
   End
   Begin VB.ListBox lbData 
      Height          =   4935
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   12495
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
 '  Dim Version As Long
 '  Dim Size As Long
   Dim SampleInterval As Long
   Dim SampleCount As Long
   Dim StartDate As Long
   Dim StartTime As Long
   Dim ChannelNumbers() As Long
   Dim Units() As Long
   
   
   Dim StartSample As Long
   Dim DateTags() As Long
   Dim TimeTags() As Long
   Dim AIChannelData() As Single
   Dim CJCChannelData() As Single
   Dim DIOChannelData() As Long
   
    Dim Hour As Long
    Dim Minute As Long
    Dim Second As Long
    Dim Month As Long
    Dim Day As Long
    Dim Year As Long
    Dim Postfix As Long
    Dim PostfixStr As String
    Dim i As Long
    Dim lbDataStr As String
    
    

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
    
    
   ' Get the file information
   '  Parameters:
   '    Filename    :name of file to get information from
   '    Version     :version of the file
   '    Size        :size of the file
    
    ULStat% = cbLogGetFileInfo(Filename, Version, Size)
    If ULStat% <> 0 Then Stop

    
    
   ' Get the sample information
   '  Parameters:
   '    Filename            :name of file to get information from
   '    SampleInterval      :time between samples
   '    SampleCount         :number of samples in the file
   '    StartDate           :date of first sample
   '    StartTime           :time of first sample
    
    ULStat% = cbLogGetSampleInfo(Filename, SampleInterval, SampleCount, StartDate, StartTime)
    If ULStat% <> 0 Then Stop

    
    
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

    
    
   ' Get the CJC information
   '  Parameters:
   '    Filename                :name of file to get information from
   '    CJCChannelCount         :number of CJC channels logged
    
    ULStat% = cbLogGetCJCInfo(Filename, CJCChannelCount)
    If ULStat% <> 0 Then Stop

     
    
   ' Get the DIO information
   '  Parameters:
   '    Filename                :name of file to get information from
   '    DIOChannelCount         :number of DIO channels logged
   
    ULStat% = cbLogGetDIOInfo(Filename, DIOChannelCount)
    If ULStat% <> 0 Then Stop

    
   ' Read the time tag information
   '  Parameters:
   '    startSample                      :first sample to read
   '    sampleCount                      :number of samples to read
   '    dateTags                         :receives the date tag information
   '    timeTags                         :receives the time tag information
   
    ReDim DateTags(SampleCount)
    ReDim TimeTags(SampleCount)
    ULStat% = cbLogReadTimeTags(Filename, StartSample, SampleCount, DateTags&(0), TimeTags&(0))
    If ULStat% <> 0 Then Stop



   ' Read the Analog data
   '  Parameters:
   '    startSample                      :first sample to read
   '    sampleCount                      :number of samples to read
   '    aiChannelData                    :receives the analog data
   ReDim AIChannelData(SampleCount * AIChannelCount)
   ULStat% = cbLogReadAIChannels(Filename, StartSample, SampleCount, AIChannelData!(0))
   If ULStat% <> 0 Then Stop



   ' Read the CJC data
   '  Parameters:
   '    startSample                      :first sample to read
   '    sampleCount                      :number of samples to read
   '    cjcChannelData                   :receives the CJC data
   ReDim CJCChannelData(SampleCount * CJCChannelCount)
   ULStat% = cbLogReadCJCChannels(Filename, StartSample, SampleCount, CJCChannelData!(0))
   If ULStat% <> 0 Then Stop



   ' Read the DIO data
   '  Parameters:
   '    startSample                      :first sample to read
   '    sampleCount                      :number of samples to read
   '    DIOChannelData                   :receives the DIO data
   ReDim DIOChannelData(SampleCount * DIOChannelCount)
   ULStat% = cbLogReadDIOChannels(Filename, StartSample, SampleCount, DIOChannelData&(0))
   If ULStat% <> 0 Then Stop

  
  For i = 0 To SampleCount - 1
    lbDataStr = ""
  
    Month = (DateTags&(i) / 256) And 255
    Day = DateTags&(i) And 255
    Year = (DateTags&(i) / 65536) And 65535
    
    Hour = (TimeTags&(i) / 65536) And 255
    Minute = (TimeTags&(i) / 256) And 255
    Second = TimeTags&(i) And 255
    
    Postfix = (TimeTags&(i) / 16777216) And 255
    If Postfix = 0 Then
        PostfixStr = " AM"
    ElseIf Postfix = 1 Then
        PostfixStr = " PM"
    Else
        PostfixStr = ""
    End If
    
    lbDataStr = Month & "/" & Day & "/" & Year & "   " & Hour & ":" & Minute & ":" & Second & PostfixStr
    
    Index = i * AIChannelCount
    For j = 0 To AIChannelCount - 1
        lbDataStr = lbDataStr & "   " & AIChannelData!(Index + j)
    Next j
    
    Index = i * CJCChannelCount
    For j = 0 To CJCIChannelCount - 1
        lbDataStr = lbDataStr & "   " & CJCChannelData!(Index + j)
    Next j
    
    Index = i * DIOChannelCount
    For j = 0 To DIOChannelCount - 1
        lbDataStr = lbDataStr & "   " & DIOChannelData&(Index + j)
    Next j

    lbData.AddItem (lbDataStr)
    
  Next i

End Sub
