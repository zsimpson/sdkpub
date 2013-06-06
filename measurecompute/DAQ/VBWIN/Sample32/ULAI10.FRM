VERSION 2.00
Begin Form frmDataDisplay 
   Caption         =   "Universal Library Gain Queue"
   ClientHeight    =   4740
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   5490
   ForeColor       =   &H00FF0000&
   Height          =   5145
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4740
   ScaleWidth      =   5490
   Top             =   1200
   Width           =   5610
   Begin CommandButton cmdStopConvert 
      Caption         =   "Quit"
      Height          =   495
      Left            =   4320
      TabIndex        =   13
      Top             =   4080
      Width           =   855
   End
   Begin CommandButton cmdUnloadQ 
      Caption         =   "Unload Queue"
      Enabled         =   0   'False
      Height          =   495
      Left            =   2280
      TabIndex        =   47
      Top             =   4080
      Visible         =   0   'False
      Width           =   1455
   End
   Begin CommandButton cmdLoadQueue 
      Caption         =   "Load Queue"
      Height          =   495
      Left            =   2280
      TabIndex        =   14
      Top             =   4080
      Width           =   1455
   End
   Begin Timer tmrConvert 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   240
      Top             =   1680
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   39
      Left            =   4200
      TabIndex        =   46
      Top             =   3600
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   38
      Left            =   3120
      TabIndex        =   45
      Top             =   3600
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   37
      Left            =   2040
      TabIndex        =   44
      Top             =   3600
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   36
      Left            =   960
      TabIndex        =   43
      Top             =   3600
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   35
      Left            =   4200
      TabIndex        =   42
      Top             =   3360
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   34
      Left            =   3120
      TabIndex        =   41
      Top             =   3360
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   33
      Left            =   2040
      TabIndex        =   40
      Top             =   3360
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   32
      Left            =   960
      TabIndex        =   39
      Top             =   3360
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   31
      Left            =   4200
      TabIndex        =   38
      Top             =   3120
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   30
      Left            =   3120
      TabIndex        =   37
      Top             =   3120
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   29
      Left            =   2040
      TabIndex        =   36
      Top             =   3120
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   28
      Left            =   960
      TabIndex        =   35
      Top             =   3120
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   27
      Left            =   4200
      TabIndex        =   34
      Top             =   2880
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   26
      Left            =   3120
      TabIndex        =   33
      Top             =   2880
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   25
      Left            =   2040
      TabIndex        =   32
      Top             =   2880
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   24
      Left            =   960
      TabIndex        =   31
      Top             =   2880
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   23
      Left            =   4200
      TabIndex        =   30
      Top             =   2640
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   22
      Left            =   3120
      TabIndex        =   29
      Top             =   2640
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   21
      Left            =   2040
      TabIndex        =   28
      Top             =   2640
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   20
      Left            =   960
      TabIndex        =   27
      Top             =   2640
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   11
      Left            =   4200
      TabIndex        =   18
      Top             =   2400
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   10
      Left            =   3120
      TabIndex        =   17
      Top             =   2400
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   9
      Left            =   2040
      TabIndex        =   16
      Top             =   2400
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   8
      Left            =   960
      TabIndex        =   15
      Top             =   2400
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   19
      Left            =   4200
      TabIndex        =   26
      Top             =   2160
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   18
      Left            =   3120
      TabIndex        =   25
      Top             =   2160
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   17
      Left            =   2040
      TabIndex        =   24
      Top             =   2160
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   16
      Left            =   960
      TabIndex        =   23
      Top             =   2160
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   15
      Left            =   4200
      TabIndex        =   22
      Top             =   1920
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   14
      Left            =   3120
      TabIndex        =   21
      Top             =   1920
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   13
      Left            =   2040
      TabIndex        =   20
      Top             =   1920
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   12
      Left            =   960
      TabIndex        =   19
      Top             =   1920
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   4200
      TabIndex        =   12
      Top             =   1680
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   3120
      TabIndex        =   11
      Top             =   1680
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   2040
      TabIndex        =   10
      Top             =   1680
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   960
      TabIndex        =   9
      Top             =   1680
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   4200
      TabIndex        =   8
      Top             =   1440
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3120
      TabIndex        =   7
      Top             =   1440
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   2040
      TabIndex        =   6
      Top             =   1440
      Width           =   975
   End
   Begin Label lblADData 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   960
      TabIndex        =   5
      Top             =   1440
      Width           =   975
   End
   Begin Label lblShowRange 
      Alignment       =   2  'Center
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   4200
      TabIndex        =   52
      Top             =   960
      Width           =   975
   End
   Begin Label lblShowRange 
      Alignment       =   2  'Center
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3120
      TabIndex        =   51
      Top             =   960
      Width           =   975
   End
   Begin Label lblShowRange 
      Alignment       =   2  'Center
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   2040
      TabIndex        =   50
      Top             =   960
      Width           =   975
   End
   Begin Label lblShowRange 
      Alignment       =   2  'Center
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   960
      TabIndex        =   49
      Top             =   960
      Width           =   975
   End
   Begin Label lblRange 
      Caption         =   "Range:"
      Height          =   255
      Left            =   120
      TabIndex        =   48
      Top             =   960
      Width           =   735
   End
   Begin Label lblChan3 
      Caption         =   "Channel 3:"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   4200
      TabIndex        =   4
      Top             =   600
      Width           =   975
   End
   Begin Label lblChan2 
      Caption         =   "Channel 2:"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   3120
      TabIndex        =   3
      Top             =   600
      Width           =   975
   End
   Begin Label lblChan1 
      Caption         =   "Channel 1:"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   2040
      TabIndex        =   2
      Top             =   600
      Width           =   975
   End
   Begin Label lblChan0 
      Caption         =   "Channel 0:"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Left            =   960
      TabIndex        =   1
      Top             =   600
      Width           =   975
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbALoadQueue()"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5265
   End
End
'ULAI10.MAK================================================================

' File:                         ULAI10.MAK

' Library Call Demonstrated:    cbALoadQueue%()
'
' Purpose:                      Loads an A/D board's channel/gain queue.
'
' Demonstration:                Prepares a channel/gain queue and loads it
'                               to the board. An analog input function
'                               is then called to show how the queue
'                               values work.
'
' Other Library Calls:          cbErrHandling()
'
' Special Requirements:         Board 0 must have an A/D converter and
'                               channel gain queue hardware.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const NumChans% = 4             ' Number of channels in scan
Const NumPoints& = 10           ' Number of data points to collect
Const NumElements& = NumChans% * NumPoints&

Dim ADData%(NumElements&)       ' dimension an array to hold the input values
Dim MemHandle&                  ' define a variable to contain the handle for
                                ' memory allocated by Windows through cbWinBufAlloc%()
Dim ChanArray%(NumChans%)       ' array to hold channel queue information
Dim GainArray%(NumChans%)       ' array to hold gain queue information

Sub cmdLoadQueue_Click ()

   cmdLoadQueue.Enabled = 0
   cmdLoadQueue.Visible = 0
   cmdUnloadQ.Enabled = 1
   cmdUnloadQ.Visible = 1

   ' Set up the channel/gain queue for 4 channels - each one set to
   ' different A/D ranges. Note: Do not mix Bipolar/Unipolar ranges
        
   ChanArray%(0) = 0
   GainArray%(0) = BIP5VOLTS
   lblShowRange(0).Caption = "±5 Volts"

   ChanArray%(1) = 1
   GainArray%(1) = BIP10VOLTS
   lblShowRange(1).Caption = "±10 Volts"

   ChanArray%(2) = 2
   GainArray%(2) = BIP5VOLTS
   lblShowRange(2).Caption = "±5 Volts"

   ChanArray%(3) = 3
   GainArray%(3) = BIP2PT5VOLTS
   lblShowRange(3).Caption = "±2.5 Volts"

   ' Load the channel/gain values into the queue
   '  Parameters:
   '    BoardNum%    :the number used by CB.CFG to describe this board
   '    ChanArray%[] :array of channel values
   '    GainArray%[] :array of gain values
   '    NumChans%    :the number of elements in the arrays (0=disable queue)
        
   ULStat% = cbALoadQueue(BoardNum%, ChanArray%(0), GainArray%(0), NumChans%)
   If ULStat% <> 0 Then Stop

End Sub

Sub cmdStopConvert_Click ()
   
   ULStat% = cbWinBufFree(MemHandle&)      ' Free up memory for use by
   If ULStat% <> 0 Then Stop                ' other programs
   End
   
End Sub

Sub cmdUnloadQ_Click ()

   cmdUnloadQ.Enabled = 0
   cmdUnloadQ.Visible = 0
   cmdLoadQueue.Enabled = 1
   cmdLoadQueue.Visible = 1
   For i% = 0 To 3
      lblShowRange(i%).Caption = "±5 Volts"
   Next i%

   NoChans% = 0      ' set to zero to disable queue
        
   ULStat% = cbALoadQueue(BoardNum%, ChanArray%(0), GainArray%(0), NoChans%)
   If ULStat% <> 0 Then Stop

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
    
   MemHandle& = cbWinBufAlloc(NumElements&)      ' set aside memory to hold data
   If MemHandle& = 0 Then Stop

   For i% = 0 To 3
      lblShowRange(i%).Caption = "±5 Volts"
   Next i%

   tmrConvert.Enabled = True

End Sub

Sub tmrConvert_Timer ()

   ' Call an analog input function to show how the gain queue values
   ' supercede those passed to the function.
   
   ' Collect the values with cbAInScan()
   '  Parameters:
   '    BoardNum%    :the number used by CB.CFG to describe this board
   '    LowChan%     :the first channel of the scan
   '    HighChan%    :the last channel of the scan
   '    CBCount&     :the total number of A/D samples to collect
   '    CBRate&      :sample rate in samples per second
   '    Gain         :the gain for the board
   '    ADData%[]    :the array for the collected data values
   '    Options      :data collection options

   LowChan% = 0                      ' This is ignored
   HighChan% = 3                     ' This is ignored
   CBCount& = NumElements&           ' Number of data points to collect
   Options = CONVERTDATA             ' Return data as 12-bit values
   Gain = BIP5VOLTS                 ' This is ignored
   CBRate& = 1000                    ' Acquire data at 1000 Hz

   If MemHandle& = 0 Then Stop       ' check that a handle to a memory buffer exists

   ULStat% = cbAInScan(BoardNum%, LowChan%, HighChan%, CBCount&, CBRate&, Gain, MemHandle&, Options)
   If ULStat% <> 0 Then Stop

   ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

   ULStat% = cbWinBufToArray(MemHandle&, ADData%(0), FirstPoint&, CBCount&)
   If ULStat% <> 0 Then Stop

   i% = 0
   For SampleNum% = 0 To NumPoints& - 1
      For ChannelNum% = 0 To NumChans - 1
         lblADData(i%).Caption = Format$(ADData%(i%), "0")
         i% = i% + 1
      Next ChannelNum%
   Next SampleNum%

End Sub

