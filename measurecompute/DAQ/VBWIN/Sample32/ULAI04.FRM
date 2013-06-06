VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Analog Input Scan"
   ClientHeight    =   3795
   ClientLeft      =   2520
   ClientTop       =   1545
   ClientWidth     =   5235
   ForeColor       =   &H00FF0000&
   Height          =   4200
   Left            =   2460
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3795
   ScaleWidth      =   5235
   Top             =   1200
   Width           =   5355
   Begin TextBox txtHighChan 
      Alignment       =   2  'Center
      Height          =   285
      Left            =   2760
      TabIndex        =   34
      Text            =   "3"
      Top             =   1320
      Width           =   495
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   396
      Left            =   4032
      TabIndex        =   17
      Top             =   3264
      Width           =   780
   End
   Begin CommandButton cmdConvData 
      Caption         =   "Convert Data"
      Enabled         =   0   'False
      Height          =   396
      Left            =   2976
      TabIndex        =   19
      Top             =   768
      Width           =   1260
   End
   Begin CommandButton cmdStartAcq 
      Caption         =   "Acquire Data"
      Height          =   396
      Left            =   1152
      TabIndex        =   18
      Top             =   768
      Width           =   1260
   End
   Begin Timer tmrCheckStatus 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   4680
      Top             =   720
   End
   Begin Label Label1 
      Caption         =   "Measure Channels 0 to"
      Height          =   255
      Left            =   600
      TabIndex        =   35
      Top             =   1320
      Width           =   2055
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   4080
      TabIndex        =   16
      Top             =   2880
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   3720
      TabIndex        =   27
      Top             =   2880
      Width           =   255
   End
   Begin Label lblChan7 
      Caption         =   "Channel 7:"
      Height          =   255
      Left            =   2640
      TabIndex        =   8
      Top             =   2880
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1560
      TabIndex        =   12
      Top             =   2880
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   1080
      TabIndex        =   23
      Top             =   2880
      Width           =   255
   End
   Begin Label lblChan3 
      Caption         =   "Channel 3:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   2880
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   4080
      TabIndex        =   15
      Top             =   2640
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3720
      TabIndex        =   26
      Top             =   2640
      Width           =   255
   End
   Begin Label lblChan6 
      Caption         =   "Channel 6:"
      Height          =   255
      Left            =   2640
      TabIndex        =   7
      Top             =   2640
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1560
      TabIndex        =   11
      Top             =   2640
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   1080
      TabIndex        =   22
      Top             =   2640
      Width           =   255
   End
   Begin Label lblChan2 
      Caption         =   "Channel 2:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2640
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   4080
      TabIndex        =   14
      Top             =   2400
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   3720
      TabIndex        =   25
      Top             =   2400
      Width           =   255
   End
   Begin Label lblChan5 
      Caption         =   "Channel 5:"
      Height          =   255
      Left            =   2640
      TabIndex        =   6
      Top             =   2400
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1560
      TabIndex        =   10
      Top             =   2400
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   1080
      TabIndex        =   21
      Top             =   2400
      Width           =   255
   End
   Begin Label lblChan1 
      Caption         =   "Channel 1:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   2400
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   4080
      TabIndex        =   13
      Top             =   2160
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   3720
      TabIndex        =   24
      Top             =   2160
      Width           =   255
   End
   Begin Label lblChan4 
      Caption         =   "Channel 4:"
      Height          =   255
      Left            =   2640
      TabIndex        =   5
      Top             =   2160
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1560
      TabIndex        =   9
      Top             =   2160
      Width           =   975
   End
   Begin Label lblShowTag 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   1080
      TabIndex        =   20
      Top             =   2160
      Width           =   255
   End
   Begin Label lblChan0 
      Caption         =   "Channel 0:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   2160
      Width           =   975
   End
   Begin Label lblData2 
      Alignment       =   2  'Center
      Caption         =   "Data"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   210
      Left            =   4290
      TabIndex        =   33
      Top             =   1875
      Width           =   585
   End
   Begin Label lblTag4 
      Alignment       =   2  'Center
      Caption         =   "Tags"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   210
      Left            =   3525
      TabIndex        =   32
      Top             =   1875
      Width           =   690
   End
   Begin Label lblData1 
      Alignment       =   2  'Center
      Caption         =   "Data"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   210
      Left            =   1800
      TabIndex        =   29
      Top             =   1875
      Width           =   585
   End
   Begin Label lblTag2 
      Alignment       =   2  'Center
      Caption         =   "Tags"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   210
      Left            =   930
      TabIndex        =   28
      Top             =   1875
      Width           =   690
   End
   Begin Label lblTag3 
      Alignment       =   2  'Center
      Caption         =   "Channel"
      Height          =   210
      Left            =   3435
      TabIndex        =   31
      Top             =   1680
      Width           =   870
   End
   Begin Label lblTag1 
      Alignment       =   2  'Center
      Caption         =   "Channel"
      Height          =   210
      Left            =   840
      TabIndex        =   30
      Top             =   1680
      Width           =   870
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbAConvertData()"
      Height          =   330
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   4785
   End
End
'ULAI04.MAK================================================================

' File:                         ULAI04.MAK

' Library Call Demonstrated:    cbAInScan%() with cbAConvertData()

' Purpose:                      Demonstrate the conversion of data values
'                               after they have been collected.

' Demonstration:                Collects 10 data points from eight analog inputs.
'                               Data are collected as 16-bit values and
'                               are converted to channel numbers and
'                               12-bit data values using cbAConvertData.

' Other Library Calls:          cbAConvertData%()
'                               cbGetStatus%()
'                               cbStopBackground%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a 12 bit A/D converter
'                               that stores channel tags with data.
'                               Analog signals on eight input channels.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum% = 0              ' Board number
Const NumPoints& = 8            ' Number of data points to collect
Const FirstPoint& = 0           ' set first element in buffer to transfer to array

Dim ADData%(NumPoints&)         ' dimension an array to hold the input values

Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ChanTags%(NumPoints&)       ' dimension an array to hold the channel tags
Dim HighChan%

Sub cmdConvData_Click ()
        
   ' Use cbAConvertData%() to convert the 16-bit values
   ' in ADData%() to 12-bit values
   '  Parameters:
   '    NumPoints&     :the number of data values to convert
   '    ADData%        :the array holding the 16-bit data values to be converted
        
   ULStat% = cbAConvertData(BoardNum%, NumPoints&, ADData%(0), ChanTags%(0))
   If ULStat% <> 0 Then Stop
  
   For i% = 0 To HighChan%
      lblADData(i%).Caption = Format$(ADData%(i%), "0")
      lblShowTag(i%).Caption = Format$(ChanTags%(i%), "0")
   Next i%
   cmdConvData.Enabled = 0

End Sub

Sub cmdStartAcq_Click ()

   ' Collect the values with cbAInScan%()
   '  Parameters:
   '    BoardNum%   :the number used by CB.CFG to describe this board
   '    LowChan%    :the first channel of the scan
   '    HighChan%   :the last channel of the scan
   '    CBCount&    :the total number of A/D samples to collect
   '    CBRate&     :sample rate
   '    Gain        :the gain for the board
   '    ADData%     :the array for the collected data values
   '    Options     :data collection options

   For i% = 0 To NumPoints& - 1
      lblShowTag(i%).Caption = ""
   Next i%

   LowChan% = 0                     ' first channel to acquire
   HighChan% = Val(txtHighChan.Text)' last channel to acquire
   If HighChan% > 7 Then HighChan% = 7
   txtHighChan.Text = Str(HighChan%)

   CBCount& = NumPoints&            ' total number of data points to collect
   CBRate& = 390                    ' sampling rate (samples per second)
   Options = NOCONVERTDATA + BACKGROUND
                                    ' collect data in BACKGROUND mode
                                    ' as 16-bit values (no conversion)
   Gain = BIP5VOLTS                ' set the gain

   If MemHandle& = 0 Then Stop      ' check that a handle to a memory buffer exists

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options)
   If ULStat% <> 0 Then Stop
  
   tmrCheckStatus.Enabled = 1

End Sub

Sub cmdStopConvert_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
                                            ' other programs
   If ULStat% <> 0 Then Stop
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

   MemHandle& = cbWinBufAlloc(NumPoints&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

End Sub

Sub tmrCheckStatus_Timer ()

   ' Check the current status of the background data collection
   '  Parameters:
   '    BoardNum%    :the number used by CB.CFG to describe this board
   '    Status%     :current status of the background data collection
   '    CurCount&   :current number of samples collected
   '    CurIndex&   :index to the data buffer pointing to the last value transferred
   '   FunctionType: A/D operation (AIFUNCTIOM)

   ' Transfer the data from the memory buffer set up by Windows
   ' to an array for use by Visual Basic
    
     
   ULStat% = cbGetStatus(BoardNum%, Status%, CurCount&, CurIndex&,AIFUNCTION)
   If ULStat% <> 0 Then Stop

   If Status% = IDLE Then
      ULStat% = cbStopBackground(BoardNum%,AIFUNCTION)
      If ULStat% <> 0 Then Stop

      ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, NumPoints&)
      If ULStat% <> 0 Then Stop

      For i% = 0 To HighChan%
         lblADData(i%).Caption = Format$(ADData%(i%), "0")
      Next i%

	  For j% = HighChan% + 1 To 7
        lblADData(j%).Caption = Format$("", "0")
      Next j%
      cmdConvData.Enabled = 1
      tmrCheckStatus.Enabled = 0
   End If

End Sub

