
'===============================================================================

' File:                         DaqInScan01.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.DaqInScan()
'
' Purpose:                      Synchronously scans Analog channels, Digital ports and Counters
'                               in the foreground.
'
' Demonstration:                Collects data on Analog Channels 0 and 1,
'                               FirstPortA and Counter 0.
'
' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               Mccdaq.MccBoard.DConfigPort()
'                               Mccdaq.MccBoard.CConfigScan()
'
' Special Requirements:         Board 0 must support MccDaq.MccService.DaqInScan.

' (c) Copyright 1995-2006, Measurement Computing Corp.
' All rights reserved.
'==========================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    Const BoardNum As Integer = 0 ' Board number
    Const ChanCount As Integer = 4 ' Number of channels in scan
    Const NumPoints As Integer = 10 ' Number of data points to collect
    Const NumElements As Integer = ChanCount * NumPoints

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ADData(NumElements) As UInt16 ' dimension an array to hold the input values
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
    Dim ChanArray(ChanCount) As Short ' array to hold channel queue information
    Dim ChanTypeArray(ChanCount) As MccDaq.ChannelType ' array to hold channel type information
    Dim GainArray(ChanCount) As MccDaq.Range ' array to hold gain queue information

    Public lblADData As System.Windows.Forms.Label()
    Public lblShowRange As System.Windows.Forms.Label()
    Public lblShowChanType As System.Windows.Forms.Label()

    Private Sub frmDataDisplay_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load

        'load the arrays with values
        ChanArray(0) = 0
        ChanTypeArray(0) = MccDaq.ChannelType.Analog
        GainArray(0) = MccDaq.Range.Bip10Volts

        lblChan0.Text = "0"
        lblShowChanType(0).Text = "Analog"
        lblShowRange(0).Text = "±10 Volts"

        ChanArray(1) = MccDaq.DigitalPortType.FirstPortA
        ChanTypeArray(1) = MccDaq.ChannelType.Digital8
        GainArray(1) = MccDaq.Range.NotUsed

        lblChan1.Text = "FirstPortA"
        lblShowChanType(1).Text = "Digital8"
        lblShowRange(1).Text = "NotUsed"

        ChanArray(2) = 0
        ChanTypeArray(2) = MccDaq.ChannelType.Ctr16
        GainArray(2) = MccDaq.Range.NotUsed

        lblChan2.Text = "0"
        lblShowChanType(2).Text = "Ctr16"
        lblShowRange(2).Text = "NotUsed"

        ChanArray(3) = 5
        ChanTypeArray(3) = MccDaq.ChannelType.Analog
        GainArray(3) = MccDaq.Range.Bip5Volts

        lblChan3.Text = "5"
        lblShowChanType(3).Text = "Analog"
        lblShowRange(3).Text = "±5 Volts"

    End Sub

    Private Sub cmdRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdRead.Click
        Dim ChannelNum As Short
        Dim SampleNum As Short
        Dim i As Short
        Dim FirstPoint As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim Rate As Integer
        Dim Options As MccDaq.ScanOptions
        Dim Count As Integer
        Dim PretrigCount As Integer

        Dim CounterNum As Integer
        Dim Direction As MccDaq.DigitalPortDirection
        Dim PortNum As MccDaq.DigitalPortType

         'configure FirstPortA  for digital input
        PortNum = ChanArray(1)
        Direction = MccDaq.DigitalPortDirection.DigitalIn
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
          Stop
        End If

        ' configure counter 0
        CounterNum = ChanArray(2)
        ULStat = DaqBoard.CConfigScan(CounterNum, MccDaq.CounterMode.StopAtMax, MccDaq.CounterDebounceTime.DebounceNone, 0, MccDaq.CounterEdgeDetection.RisingEdge, 0, CounterNum)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
          Stop
        End If

        ' Collect the values with cbDaqInScan()
        '  Parameters:
        '    BoardNum        :the number used by CB.CFG to describe this board
        '    ChanArray[]     :array of channel values
        '    ChanTypeArray[] : array of channel types
        '    GainArray[]     :array of gain values
        '    ChansCount      :the number of elements in the arrays (0=disable queue)
        '    PretrigCount    :number of pre-trigger A/D samples to collect
        '    Count         :the total number of A/D samples to collect
        '    Rate            :sample rate in samples per second
        '    ADData[]        :the array for the collected data values
        '    Options         :data collection options

        PretrigCount = 0
        Count = NumElements ' Number of data points to collect
        Options = MccDaq.ScanOptions.ConvertData
        Rate = 100 ' Acquire data at 100 Hz

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.DaqInScan(ChanArray, ChanTypeArray, GainArray, ChanCount, Rate, PretrigCount, Count, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic
        FirstPoint = 0
        ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        i = 0
        For SampleNum = 0 To NumPoints - 1
            For ChannelNum = 0 To ChanCount - 1
                lblADData(i).Text = ADData(i).ToString("D")
                i = i + 1
            Next ChannelNum
        Next SampleNum
    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by other programs
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        End

    End Sub

#Region "Windows Form Designer generated code "
    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        InitUL()
    End Sub
    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
        If Disposing Then
            If Not components Is Nothing Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(Disposing)
    End Sub
    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer
    Public ToolTip1 As System.Windows.Forms.ToolTip
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents _lblShowChanType_3 As System.Windows.Forms.Label
    Public WithEvents _lblShowChanType_2 As System.Windows.Forms.Label
    Public WithEvents _lblShowChanType_1 As System.Windows.Forms.Label
    Public WithEvents _lblShowChanType_0 As System.Windows.Forms.Label
    Public WithEvents lblChanType As System.Windows.Forms.Label
    Public WithEvents _lblADData_39 As System.Windows.Forms.Label
    Public WithEvents _lblADData_38 As System.Windows.Forms.Label
    Public WithEvents _lblADData_37 As System.Windows.Forms.Label
    Public WithEvents _lblADData_36 As System.Windows.Forms.Label
    Public WithEvents _lblADData_35 As System.Windows.Forms.Label
    Public WithEvents _lblADData_34 As System.Windows.Forms.Label
    Public WithEvents _lblADData_33 As System.Windows.Forms.Label
    Public WithEvents _lblADData_32 As System.Windows.Forms.Label
    Public WithEvents _lblADData_31 As System.Windows.Forms.Label
    Public WithEvents _lblADData_30 As System.Windows.Forms.Label
    Public WithEvents _lblADData_29 As System.Windows.Forms.Label
    Public WithEvents _lblADData_28 As System.Windows.Forms.Label
    Public WithEvents _lblADData_27 As System.Windows.Forms.Label
    Public WithEvents _lblADData_26 As System.Windows.Forms.Label
    Public WithEvents _lblADData_25 As System.Windows.Forms.Label
    Public WithEvents _lblADData_24 As System.Windows.Forms.Label
    Public WithEvents _lblADData_23 As System.Windows.Forms.Label
    Public WithEvents _lblADData_22 As System.Windows.Forms.Label
    Public WithEvents _lblADData_21 As System.Windows.Forms.Label
    Public WithEvents _lblADData_20 As System.Windows.Forms.Label
    Public WithEvents _lblADData_11 As System.Windows.Forms.Label
    Public WithEvents _lblADData_10 As System.Windows.Forms.Label
    Public WithEvents _lblADData_9 As System.Windows.Forms.Label
    Public WithEvents _lblADData_8 As System.Windows.Forms.Label
    Public WithEvents _lblADData_19 As System.Windows.Forms.Label
    Public WithEvents _lblADData_18 As System.Windows.Forms.Label
    Public WithEvents _lblADData_17 As System.Windows.Forms.Label
    Public WithEvents _lblADData_16 As System.Windows.Forms.Label
    Public WithEvents _lblADData_15 As System.Windows.Forms.Label
    Public WithEvents _lblADData_14 As System.Windows.Forms.Label
    Public WithEvents _lblADData_13 As System.Windows.Forms.Label
    Public WithEvents _lblADData_12 As System.Windows.Forms.Label
    Public WithEvents _lblADData_7 As System.Windows.Forms.Label
    Public WithEvents _lblADData_6 As System.Windows.Forms.Label
    Public WithEvents _lblADData_5 As System.Windows.Forms.Label
    Public WithEvents _lblADData_4 As System.Windows.Forms.Label
    Public WithEvents _lblADData_3 As System.Windows.Forms.Label
    Public WithEvents _lblADData_2 As System.Windows.Forms.Label
    Public WithEvents _lblADData_1 As System.Windows.Forms.Label
    Public WithEvents _lblADData_0 As System.Windows.Forms.Label
    Public WithEvents _lblShowRange_3 As System.Windows.Forms.Label
    Public WithEvents _lblShowRange_2 As System.Windows.Forms.Label
    Public WithEvents _lblShowRange_1 As System.Windows.Forms.Label
    Public WithEvents _lblShowRange_0 As System.Windows.Forms.Label
    Public WithEvents lblRange As System.Windows.Forms.Label
    Public WithEvents lblChan3 As System.Windows.Forms.Label
    Public WithEvents lblChan2 As System.Windows.Forms.Label
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents lblChan0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Public WithEvents cmdRead As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdRead = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me._lblShowChanType_3 = New System.Windows.Forms.Label()
        Me._lblShowChanType_2 = New System.Windows.Forms.Label()
        Me._lblShowChanType_1 = New System.Windows.Forms.Label()
        Me._lblShowChanType_0 = New System.Windows.Forms.Label()
        Me.lblChanType = New System.Windows.Forms.Label()
        Me._lblADData_39 = New System.Windows.Forms.Label()
        Me._lblADData_38 = New System.Windows.Forms.Label()
        Me._lblADData_37 = New System.Windows.Forms.Label()
        Me._lblADData_36 = New System.Windows.Forms.Label()
        Me._lblADData_35 = New System.Windows.Forms.Label()
        Me._lblADData_34 = New System.Windows.Forms.Label()
        Me._lblADData_33 = New System.Windows.Forms.Label()
        Me._lblADData_32 = New System.Windows.Forms.Label()
        Me._lblADData_31 = New System.Windows.Forms.Label()
        Me._lblADData_30 = New System.Windows.Forms.Label()
        Me._lblADData_29 = New System.Windows.Forms.Label()
        Me._lblADData_28 = New System.Windows.Forms.Label()
        Me._lblADData_27 = New System.Windows.Forms.Label()
        Me._lblADData_26 = New System.Windows.Forms.Label()
        Me._lblADData_25 = New System.Windows.Forms.Label()
        Me._lblADData_24 = New System.Windows.Forms.Label()
        Me._lblADData_23 = New System.Windows.Forms.Label()
        Me._lblADData_22 = New System.Windows.Forms.Label()
        Me._lblADData_21 = New System.Windows.Forms.Label()
        Me._lblADData_20 = New System.Windows.Forms.Label()
        Me._lblADData_11 = New System.Windows.Forms.Label()
        Me._lblADData_10 = New System.Windows.Forms.Label()
        Me._lblADData_9 = New System.Windows.Forms.Label()
        Me._lblADData_8 = New System.Windows.Forms.Label()
        Me._lblADData_19 = New System.Windows.Forms.Label()
        Me._lblADData_18 = New System.Windows.Forms.Label()
        Me._lblADData_17 = New System.Windows.Forms.Label()
        Me._lblADData_16 = New System.Windows.Forms.Label()
        Me._lblADData_15 = New System.Windows.Forms.Label()
        Me._lblADData_14 = New System.Windows.Forms.Label()
        Me._lblADData_13 = New System.Windows.Forms.Label()
        Me._lblADData_12 = New System.Windows.Forms.Label()
        Me._lblADData_7 = New System.Windows.Forms.Label()
        Me._lblADData_6 = New System.Windows.Forms.Label()
        Me._lblADData_5 = New System.Windows.Forms.Label()
        Me._lblADData_4 = New System.Windows.Forms.Label()
        Me._lblADData_3 = New System.Windows.Forms.Label()
        Me._lblADData_2 = New System.Windows.Forms.Label()
        Me._lblADData_1 = New System.Windows.Forms.Label()
        Me._lblADData_0 = New System.Windows.Forms.Label()
        Me._lblShowRange_3 = New System.Windows.Forms.Label()
        Me._lblShowRange_2 = New System.Windows.Forms.Label()
        Me._lblShowRange_1 = New System.Windows.Forms.Label()
        Me._lblShowRange_0 = New System.Windows.Forms.Label()
        Me.lblRange = New System.Windows.Forms.Label()
        Me.lblChan3 = New System.Windows.Forms.Label()
        Me.lblChan2 = New System.Windows.Forms.Label()
        Me.lblChan1 = New System.Windows.Forms.Label()
        Me.lblChan0 = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(216, 296)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(57, 33)
        Me.cmdStopConvert.TabIndex = 13
        Me.cmdStopConvert.Text = "Quit"
        '
        'cmdRead
        '
        Me.cmdRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdRead.Location = New System.Drawing.Point(152, 296)
        Me.cmdRead.Name = "cmdRead"
        Me.cmdRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdRead.Size = New System.Drawing.Size(57, 33)
        Me.cmdRead.TabIndex = 46
        Me.cmdRead.Text = "Read"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Window
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(8, 40)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(57, 17)
        Me.Label1.TabIndex = 57
        Me.Label1.Text = "Channel:"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        '_lblShowChanType_3
        '
        Me._lblShowChanType_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowChanType_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowChanType_3.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowChanType_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowChanType_3.Location = New System.Drawing.Point(328, 64)
        Me._lblShowChanType_3.Name = "_lblShowChanType_3"
        Me._lblShowChanType_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowChanType_3.Size = New System.Drawing.Size(81, 17)
        Me._lblShowChanType_3.TabIndex = 56
        Me._lblShowChanType_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowChanType_2
        '
        Me._lblShowChanType_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowChanType_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowChanType_2.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowChanType_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowChanType_2.Location = New System.Drawing.Point(248, 64)
        Me._lblShowChanType_2.Name = "_lblShowChanType_2"
        Me._lblShowChanType_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowChanType_2.Size = New System.Drawing.Size(81, 17)
        Me._lblShowChanType_2.TabIndex = 55
        Me._lblShowChanType_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowChanType_1
        '
        Me._lblShowChanType_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowChanType_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowChanType_1.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowChanType_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowChanType_1.Location = New System.Drawing.Point(160, 64)
        Me._lblShowChanType_1.Name = "_lblShowChanType_1"
        Me._lblShowChanType_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowChanType_1.Size = New System.Drawing.Size(81, 17)
        Me._lblShowChanType_1.TabIndex = 54
        Me._lblShowChanType_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowChanType_0
        '
        Me._lblShowChanType_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowChanType_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowChanType_0.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowChanType_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowChanType_0.Location = New System.Drawing.Point(72, 64)
        Me._lblShowChanType_0.Name = "_lblShowChanType_0"
        Me._lblShowChanType_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowChanType_0.Size = New System.Drawing.Size(81, 17)
        Me._lblShowChanType_0.TabIndex = 53
        Me._lblShowChanType_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChanType
        '
        Me.lblChanType.BackColor = System.Drawing.SystemColors.Window
        Me.lblChanType.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChanType.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChanType.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChanType.Location = New System.Drawing.Point(24, 64)
        Me.lblChanType.Name = "lblChanType"
        Me.lblChanType.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChanType.Size = New System.Drawing.Size(41, 17)
        Me.lblChanType.TabIndex = 52
        Me.lblChanType.Text = "Type:"
        Me.lblChanType.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        '_lblADData_39
        '
        Me._lblADData_39.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_39.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_39.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_39.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_39.Location = New System.Drawing.Point(328, 264)
        Me._lblADData_39.Name = "_lblADData_39"
        Me._lblADData_39.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_39.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_39.TabIndex = 45
        Me._lblADData_39.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_38
        '
        Me._lblADData_38.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_38.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_38.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_38.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_38.Location = New System.Drawing.Point(248, 264)
        Me._lblADData_38.Name = "_lblADData_38"
        Me._lblADData_38.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_38.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_38.TabIndex = 44
        Me._lblADData_38.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_37
        '
        Me._lblADData_37.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_37.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_37.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_37.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_37.Location = New System.Drawing.Point(160, 264)
        Me._lblADData_37.Name = "_lblADData_37"
        Me._lblADData_37.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_37.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_37.TabIndex = 43
        Me._lblADData_37.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_36
        '
        Me._lblADData_36.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_36.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_36.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_36.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_36.Location = New System.Drawing.Point(72, 264)
        Me._lblADData_36.Name = "_lblADData_36"
        Me._lblADData_36.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_36.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_36.TabIndex = 42
        Me._lblADData_36.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_35
        '
        Me._lblADData_35.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_35.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_35.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_35.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_35.Location = New System.Drawing.Point(328, 248)
        Me._lblADData_35.Name = "_lblADData_35"
        Me._lblADData_35.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_35.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_35.TabIndex = 41
        Me._lblADData_35.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_34
        '
        Me._lblADData_34.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_34.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_34.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_34.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_34.Location = New System.Drawing.Point(248, 248)
        Me._lblADData_34.Name = "_lblADData_34"
        Me._lblADData_34.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_34.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_34.TabIndex = 40
        Me._lblADData_34.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_33
        '
        Me._lblADData_33.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_33.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_33.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_33.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_33.Location = New System.Drawing.Point(160, 248)
        Me._lblADData_33.Name = "_lblADData_33"
        Me._lblADData_33.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_33.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_33.TabIndex = 39
        Me._lblADData_33.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_32
        '
        Me._lblADData_32.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_32.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_32.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_32.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_32.Location = New System.Drawing.Point(72, 248)
        Me._lblADData_32.Name = "_lblADData_32"
        Me._lblADData_32.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_32.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_32.TabIndex = 38
        Me._lblADData_32.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_31
        '
        Me._lblADData_31.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_31.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_31.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_31.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_31.Location = New System.Drawing.Point(328, 232)
        Me._lblADData_31.Name = "_lblADData_31"
        Me._lblADData_31.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_31.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_31.TabIndex = 37
        Me._lblADData_31.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_30
        '
        Me._lblADData_30.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_30.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_30.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_30.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_30.Location = New System.Drawing.Point(248, 232)
        Me._lblADData_30.Name = "_lblADData_30"
        Me._lblADData_30.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_30.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_30.TabIndex = 36
        Me._lblADData_30.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_29
        '
        Me._lblADData_29.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_29.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_29.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_29.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_29.Location = New System.Drawing.Point(160, 232)
        Me._lblADData_29.Name = "_lblADData_29"
        Me._lblADData_29.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_29.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_29.TabIndex = 35
        Me._lblADData_29.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_28
        '
        Me._lblADData_28.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_28.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_28.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_28.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_28.Location = New System.Drawing.Point(72, 232)
        Me._lblADData_28.Name = "_lblADData_28"
        Me._lblADData_28.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_28.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_28.TabIndex = 34
        Me._lblADData_28.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_27
        '
        Me._lblADData_27.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_27.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_27.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_27.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_27.Location = New System.Drawing.Point(328, 216)
        Me._lblADData_27.Name = "_lblADData_27"
        Me._lblADData_27.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_27.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_27.TabIndex = 33
        Me._lblADData_27.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_26
        '
        Me._lblADData_26.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_26.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_26.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_26.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_26.Location = New System.Drawing.Point(248, 216)
        Me._lblADData_26.Name = "_lblADData_26"
        Me._lblADData_26.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_26.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_26.TabIndex = 32
        Me._lblADData_26.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_25
        '
        Me._lblADData_25.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_25.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_25.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_25.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_25.Location = New System.Drawing.Point(160, 216)
        Me._lblADData_25.Name = "_lblADData_25"
        Me._lblADData_25.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_25.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_25.TabIndex = 31
        Me._lblADData_25.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_24
        '
        Me._lblADData_24.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_24.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_24.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_24.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_24.Location = New System.Drawing.Point(72, 216)
        Me._lblADData_24.Name = "_lblADData_24"
        Me._lblADData_24.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_24.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_24.TabIndex = 30
        Me._lblADData_24.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_23
        '
        Me._lblADData_23.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_23.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_23.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_23.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_23.Location = New System.Drawing.Point(328, 200)
        Me._lblADData_23.Name = "_lblADData_23"
        Me._lblADData_23.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_23.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_23.TabIndex = 29
        Me._lblADData_23.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_22
        '
        Me._lblADData_22.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_22.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_22.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_22.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_22.Location = New System.Drawing.Point(248, 200)
        Me._lblADData_22.Name = "_lblADData_22"
        Me._lblADData_22.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_22.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_22.TabIndex = 28
        Me._lblADData_22.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_21
        '
        Me._lblADData_21.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_21.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_21.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_21.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_21.Location = New System.Drawing.Point(160, 200)
        Me._lblADData_21.Name = "_lblADData_21"
        Me._lblADData_21.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_21.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_21.TabIndex = 27
        Me._lblADData_21.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_20
        '
        Me._lblADData_20.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_20.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_20.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_20.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_20.Location = New System.Drawing.Point(72, 200)
        Me._lblADData_20.Name = "_lblADData_20"
        Me._lblADData_20.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_20.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_20.TabIndex = 26
        Me._lblADData_20.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_11
        '
        Me._lblADData_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_11.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_11.Location = New System.Drawing.Point(328, 152)
        Me._lblADData_11.Name = "_lblADData_11"
        Me._lblADData_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_11.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_11.TabIndex = 17
        Me._lblADData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_10
        '
        Me._lblADData_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_10.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_10.Location = New System.Drawing.Point(248, 152)
        Me._lblADData_10.Name = "_lblADData_10"
        Me._lblADData_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_10.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_10.TabIndex = 16
        Me._lblADData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_9
        '
        Me._lblADData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_9.Location = New System.Drawing.Point(160, 152)
        Me._lblADData_9.Name = "_lblADData_9"
        Me._lblADData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_9.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_9.TabIndex = 15
        Me._lblADData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_8
        '
        Me._lblADData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_8.Location = New System.Drawing.Point(72, 152)
        Me._lblADData_8.Name = "_lblADData_8"
        Me._lblADData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_8.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_8.TabIndex = 14
        Me._lblADData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_19
        '
        Me._lblADData_19.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_19.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_19.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_19.Location = New System.Drawing.Point(328, 184)
        Me._lblADData_19.Name = "_lblADData_19"
        Me._lblADData_19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_19.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_19.TabIndex = 25
        Me._lblADData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_18
        '
        Me._lblADData_18.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_18.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_18.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_18.Location = New System.Drawing.Point(248, 184)
        Me._lblADData_18.Name = "_lblADData_18"
        Me._lblADData_18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_18.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_18.TabIndex = 24
        Me._lblADData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_17
        '
        Me._lblADData_17.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_17.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_17.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_17.Location = New System.Drawing.Point(160, 184)
        Me._lblADData_17.Name = "_lblADData_17"
        Me._lblADData_17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_17.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_17.TabIndex = 23
        Me._lblADData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_16
        '
        Me._lblADData_16.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_16.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_16.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_16.Location = New System.Drawing.Point(72, 184)
        Me._lblADData_16.Name = "_lblADData_16"
        Me._lblADData_16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_16.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_16.TabIndex = 22
        Me._lblADData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_15
        '
        Me._lblADData_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_15.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_15.Location = New System.Drawing.Point(328, 168)
        Me._lblADData_15.Name = "_lblADData_15"
        Me._lblADData_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_15.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_15.TabIndex = 21
        Me._lblADData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_14
        '
        Me._lblADData_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_14.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_14.Location = New System.Drawing.Point(248, 168)
        Me._lblADData_14.Name = "_lblADData_14"
        Me._lblADData_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_14.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_14.TabIndex = 20
        Me._lblADData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_13
        '
        Me._lblADData_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_13.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_13.Location = New System.Drawing.Point(160, 168)
        Me._lblADData_13.Name = "_lblADData_13"
        Me._lblADData_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_13.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_13.TabIndex = 19
        Me._lblADData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_12
        '
        Me._lblADData_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_12.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_12.Location = New System.Drawing.Point(72, 168)
        Me._lblADData_12.Name = "_lblADData_12"
        Me._lblADData_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_12.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_12.TabIndex = 18
        Me._lblADData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_7
        '
        Me._lblADData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_7.Location = New System.Drawing.Point(328, 136)
        Me._lblADData_7.Name = "_lblADData_7"
        Me._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_7.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_7.TabIndex = 12
        Me._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_6
        '
        Me._lblADData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_6.Location = New System.Drawing.Point(248, 136)
        Me._lblADData_6.Name = "_lblADData_6"
        Me._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_6.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_6.TabIndex = 11
        Me._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_5
        '
        Me._lblADData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_5.Location = New System.Drawing.Point(160, 136)
        Me._lblADData_5.Name = "_lblADData_5"
        Me._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_5.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_5.TabIndex = 10
        Me._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_4
        '
        Me._lblADData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_4.Location = New System.Drawing.Point(72, 136)
        Me._lblADData_4.Name = "_lblADData_4"
        Me._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_4.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_4.TabIndex = 9
        Me._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_3
        '
        Me._lblADData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_3.Location = New System.Drawing.Point(328, 120)
        Me._lblADData_3.Name = "_lblADData_3"
        Me._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_3.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_3.TabIndex = 8
        Me._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_2
        '
        Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_2.Location = New System.Drawing.Point(248, 120)
        Me._lblADData_2.Name = "_lblADData_2"
        Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_2.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_2.TabIndex = 7
        Me._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_1
        '
        Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_1.Location = New System.Drawing.Point(160, 120)
        Me._lblADData_1.Name = "_lblADData_1"
        Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_1.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_1.TabIndex = 6
        Me._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_0
        '
        Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_0.Location = New System.Drawing.Point(72, 120)
        Me._lblADData_0.Name = "_lblADData_0"
        Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_0.Size = New System.Drawing.Size(81, 17)
        Me._lblADData_0.TabIndex = 5
        Me._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_3
        '
        Me._lblShowRange_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_3.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_3.Location = New System.Drawing.Point(328, 88)
        Me._lblShowRange_3.Name = "_lblShowRange_3"
        Me._lblShowRange_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_3.Size = New System.Drawing.Size(81, 17)
        Me._lblShowRange_3.TabIndex = 51
        Me._lblShowRange_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_2
        '
        Me._lblShowRange_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_2.Location = New System.Drawing.Point(248, 88)
        Me._lblShowRange_2.Name = "_lblShowRange_2"
        Me._lblShowRange_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_2.Size = New System.Drawing.Size(81, 17)
        Me._lblShowRange_2.TabIndex = 50
        Me._lblShowRange_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_1
        '
        Me._lblShowRange_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_1.Location = New System.Drawing.Point(160, 88)
        Me._lblShowRange_1.Name = "_lblShowRange_1"
        Me._lblShowRange_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_1.Size = New System.Drawing.Size(81, 17)
        Me._lblShowRange_1.TabIndex = 49
        Me._lblShowRange_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_0
        '
        Me._lblShowRange_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_0.Location = New System.Drawing.Point(72, 88)
        Me._lblShowRange_0.Name = "_lblShowRange_0"
        Me._lblShowRange_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_0.Size = New System.Drawing.Size(81, 17)
        Me._lblShowRange_0.TabIndex = 48
        Me._lblShowRange_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblRange
        '
        Me.lblRange.BackColor = System.Drawing.SystemColors.Window
        Me.lblRange.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblRange.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblRange.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblRange.Location = New System.Drawing.Point(16, 88)
        Me.lblRange.Name = "lblRange"
        Me.lblRange.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblRange.Size = New System.Drawing.Size(49, 17)
        Me.lblRange.TabIndex = 47
        Me.lblRange.Text = "Range:"
        Me.lblRange.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'lblChan3
        '
        Me.lblChan3.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan3.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan3.ForeColor = System.Drawing.Color.Blue
        Me.lblChan3.Location = New System.Drawing.Point(328, 40)
        Me.lblChan3.Name = "lblChan3"
        Me.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan3.Size = New System.Drawing.Size(81, 17)
        Me.lblChan3.TabIndex = 4
        Me.lblChan3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan2
        '
        Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan2.ForeColor = System.Drawing.Color.Blue
        Me.lblChan2.Location = New System.Drawing.Point(248, 40)
        Me.lblChan2.Name = "lblChan2"
        Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan2.Size = New System.Drawing.Size(81, 17)
        Me.lblChan2.TabIndex = 3
        Me.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan1
        '
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.ForeColor = System.Drawing.Color.Blue
        Me.lblChan1.Location = New System.Drawing.Point(160, 40)
        Me.lblChan1.Name = "lblChan1"
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.Size = New System.Drawing.Size(81, 17)
        Me.lblChan1.TabIndex = 2
        Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0
        '
        Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0.ForeColor = System.Drawing.Color.Blue
        Me.lblChan0.Location = New System.Drawing.Point(72, 40)
        Me.lblChan0.Name = "lblChan0"
        Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0.Size = New System.Drawing.Size(81, 17)
        Me.lblChan0.TabIndex = 1
        Me.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(40, 8)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(351, 25)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DaqInScan()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(430, 334)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopConvert, Me.cmdRead, Me.Label1, Me._lblShowChanType_3, Me._lblShowChanType_2, Me._lblShowChanType_1, Me._lblShowChanType_0, Me.lblChanType, Me._lblADData_39, Me._lblADData_38, Me._lblADData_37, Me._lblADData_36, Me._lblADData_35, Me._lblADData_34, Me._lblADData_33, Me._lblADData_32, Me._lblADData_31, Me._lblADData_30, Me._lblADData_29, Me._lblADData_28, Me._lblADData_27, Me._lblADData_26, Me._lblADData_25, Me._lblADData_24, Me._lblADData_23, Me._lblADData_22, Me._lblADData_21, Me._lblADData_20, Me._lblADData_11, Me._lblADData_10, Me._lblADData_9, Me._lblADData_8, Me._lblADData_19, Me._lblADData_18, Me._lblADData_17, Me._lblADData_16, Me._lblADData_15, Me._lblADData_14, Me._lblADData_13, Me._lblADData_12, Me._lblADData_7, Me._lblADData_6, Me._lblADData_5, Me._lblADData_4, Me._lblADData_3, Me._lblADData_2, Me._lblADData_1, Me._lblADData_0, Me._lblShowRange_3, Me._lblShowRange_2, Me._lblShowRange_1, Me._lblShowRange_0, Me.lblRange, Me.lblChan3, Me.lblChan2, Me.lblChan1, Me.lblChan0, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library DaqInScan()"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        lblADData = New System.Windows.Forms.Label(40) {}
        lblShowRange = New System.Windows.Forms.Label(4) {}
        lblShowChanType = New System.Windows.Forms.Label(4) {}

        Me.lblADData.SetValue(Me._lblADData_39, 39)
        Me.lblADData.SetValue(Me._lblADData_38, 38)
        Me.lblADData.SetValue(Me._lblADData_37, 37)
        Me.lblADData.SetValue(Me._lblADData_36, 36)
        Me.lblADData.SetValue(Me._lblADData_35, 35)
        Me.lblADData.SetValue(Me._lblADData_34, 34)
        Me.lblADData.SetValue(Me._lblADData_33, 33)
        Me.lblADData.SetValue(Me._lblADData_32, 32)
        Me.lblADData.SetValue(Me._lblADData_31, 31)
        Me.lblADData.SetValue(Me._lblADData_30, 30)
        Me.lblADData.SetValue(Me._lblADData_29, 29)
        Me.lblADData.SetValue(Me._lblADData_28, 28)
        Me.lblADData.SetValue(Me._lblADData_27, 27)
        Me.lblADData.SetValue(Me._lblADData_26, 26)
        Me.lblADData.SetValue(Me._lblADData_25, 25)
        Me.lblADData.SetValue(Me._lblADData_24, 24)
        Me.lblADData.SetValue(Me._lblADData_23, 23)
        Me.lblADData.SetValue(Me._lblADData_22, 22)
        Me.lblADData.SetValue(Me._lblADData_21, 21)
        Me.lblADData.SetValue(Me._lblADData_20, 20)
        Me.lblADData.SetValue(Me._lblADData_11, 11)
        Me.lblADData.SetValue(Me._lblADData_10, 10)
        Me.lblADData.SetValue(Me._lblADData_9, 9)
        Me.lblADData.SetValue(Me._lblADData_8, 8)
        Me.lblADData.SetValue(Me._lblADData_19, 19)
        Me.lblADData.SetValue(Me._lblADData_18, 18)
        Me.lblADData.SetValue(Me._lblADData_17, 17)
        Me.lblADData.SetValue(Me._lblADData_16, 16)
        Me.lblADData.SetValue(Me._lblADData_15, 15)
        Me.lblADData.SetValue(Me._lblADData_14, 14)
        Me.lblADData.SetValue(Me._lblADData_13, 13)
        Me.lblADData.SetValue(Me._lblADData_12, 12)
        Me.lblADData.SetValue(Me._lblADData_7, 7)
        Me.lblADData.SetValue(Me._lblADData_6, 6)
        Me.lblADData.SetValue(Me._lblADData_5, 5)
        Me.lblADData.SetValue(Me._lblADData_4, 4)
        Me.lblADData.SetValue(Me._lblADData_3, 3)
        Me.lblADData.SetValue(Me._lblADData_2, 2)
        Me.lblADData.SetValue(Me._lblADData_1, 1)
        Me.lblADData.SetValue(Me._lblADData_0, 0)

        Me.lblShowRange.SetValue(Me._lblShowRange_3, 3)
        Me.lblShowRange.SetValue(Me._lblShowRange_2, 2)
        Me.lblShowRange.SetValue(Me._lblShowRange_1, 1)
        Me.lblShowRange.SetValue(Me._lblShowRange_0, 0)

        Me.lblShowChanType.SetValue(Me._lblShowChanType_3, 3)
        Me.lblShowChanType.SetValue(Me._lblShowChanType_2, 2)
        Me.lblShowChanType.SetValue(Me._lblShowChanType_1, 1)
        Me.lblShowChanType.SetValue(Me._lblShowChanType_0, 0)

        ' declare revision level of Universal Library

        ULStat = MccDaq.MccService.DeclareRevision(MccDaq.MccService.CurrentRevNum)

        ' Initiate error handling
        '  activating error handling will trap errors like
        '  bad channel numbers and non-configured conditions.
        '  Parameters:
        '    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
        '    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop

        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If

        MemHandle = MccDaq.MccService.WinBufAlloc(NumElements) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

    End Sub
#End Region
End Class