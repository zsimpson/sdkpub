'=========================================================================

' File:                         DaqSetTrigger01.VB

' Library Call Demonstrated:    cbDaqSetTrigger()

' Purpose:                      Sets start and stop triggers. These triggers are
'                               used to initiate and terminate A/D conversion using
'                               Mccdaq.MccBoard.DaqInScan, with MccDaq.ScanOptions.ExtTrigger selected.

' Demonstration:                Sets start and stop triggers
'                               and displays the input channels data.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               Mccdaq.MccBoard.GetStatus()
'                               Mccdaq.MccBoard.StopBackground()
'                               Mccdaq.MccBoard.DConfigPort()

' Special Requirements:         Board 0 must support cbDaqInScan.
'                               Channel 0 should have a signal that transitions from below 2V to above applied.
'                               Counter 0 should have a TTL signal applied.

' (c) Copyright 1995-2006, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Option Strict Off
Option Explicit On
Friend Class frmStatusDisplay
	Inherits System.Windows.Forms.Form

    Const BoardNum As Short = 0 ' Board number
    Const ChanCount As Integer = 3 ' Number of channels in scan
    Const NumPoints As Integer = 1000 ' Number of data points to collect
    Const NumElements As Integer = ChanCount * NumPoints

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ADData(NumElements) As UInt16 ' dimension an array to hold the input values
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
    Dim ChanArray(ChanCount) As Short ' array to hold channel queue information
    Dim ChanTypeArray(ChanCount) As MccDaq.ChannelType ' array to hold channel type information
    Dim GainArray(ChanCount) As MccDaq.Range ' array to hold gain queue information

    Dim UserTerm As Short
    Public lblADData As System.Windows.Forms.Label()

    Private Sub frmStatusDisplay_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load

        'load the arrays with values
        ChanArray(0) = 0
        ChanTypeArray(0) = MccDaq.ChannelType.Analog
        GainArray(0) = MccDaq.Range.Bip10Volts

        ChanArray(1) = MccDaq.DigitalPortType.FirstPortA
        ChanTypeArray(1) = MccDaq.ChannelType.Digital8
        GainArray(1) = MccDaq.Range.NotUsed

        ChanArray(2) = 0
        ChanTypeArray(2) = MccDaq.ChannelType.Ctr16
        GainArray(2) = MccDaq.Range.NotUsed

    End Sub

    Private Sub cmdStartBgnd_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartBgnd.Click
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim CBRate As Integer
        Dim Options As Object
        Dim CBCount As Integer
        Dim PretrigCount As Integer

        Dim Direction As Integer
        Dim PortNum As Integer

        Dim TrigSource As MccDaq.TriggerSource
        Dim TrigSense As MccDaq.TriggerSensitivity
        Dim TrigChan As Integer
        Dim ChanType As MccDaq.ChannelType
        Dim Gain As MccDaq.Range
        Dim Variance As Single
        Dim Level As Single
        Dim TrigEvent As MccDaq.TriggerEvent

        cmdStartBgnd.Enabled = 0
        cmdStartBgnd.Visible = 0
        cmdStopConvert.Enabled = 1
        cmdStopConvert.Visible = 1
        cmdQuit.Enabled = 0
        UserTerm = 0 ' initialize user terminate flag

        lblADData(0).Text = ""
        lblADData(1).Text = ""
        lblADData(2).Text = ""

           'configure FirstPortA for digital input
        PortNum = ChanArray(1)
        Direction = MccDaq.DigitalPortDirection.DigitalIn
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        'Set Triggers
        'Parameters:
        'BoardNum    :the number used by CB.CFG to describe this board
        'TrigSource  :trigger source
        'TrigSense   :trigger sensitivity
        'TrigChan    :trigger channel
        'ChanType    :trigger channel type
        'Gain        :trigger channel gain
        'Level       :trigger Level
        'Variance    :trigger Variance
        'TrigEvent   :trigger event type

        'Start trigger settings
        '     AD conversions are enabled when analog channel 0 makes a transition from below 2 V to above.*/
        TrigSource = MccDaq.TriggerSource.TrigAnalogSW
        TrigSense = MccDaq.TriggerSensitivity.RisingEdge
        TrigChan = ChanArray(0)
        ChanType = ChanTypeArray(0)
        Gain = GainArray(0)
        Level = 2
        Variance = 0
        TrigEvent = MccDaq.TriggerEvent.Start

        'Set start trigger
        ULStat = DaqBoard.DaqSetTrigger(TrigSource, TrigSense, TrigChan, ChanType, Gain, Level, Variance, TrigEvent)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        'Stop trigger settings
        '  AD conversions are terminated when counter 0 reaches 100 counts.*/
        TrigSource = MccDaq.TriggerSource.TrigCounter
        TrigSense = MccDaq.TriggerSensitivity.AboveLevel
        TrigChan = ChanArray(2)
        ChanType = ChanTypeArray(2)
        Gain = GainArray(2)
        Level = 100
        Variance = 0
        TrigEvent = MccDaq.TriggerEvent.Stop

        'Set stop trigger
        ULStat = DaqBoard.DaqSetTrigger(TrigSource, TrigSense, TrigChan, ChanType, Gain, Level, Variance, TrigEvent)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop



        ' Collect the values with cbDaqInScan()
        '  Parameters:
        '    BoardNum        :the number used by CB.CFG to describe this board
        '    ChanArray[]     :array of channel values
        '    ChanTypeArray[] : array of channel types
        '    GainArra[]      :array of gain values
        '    ChansCount      :the number of elements in the arrays (0=disable queue)
        '    PretrigCount    :number of pre-trigger A/D samples to collect
        '    CBCount         :the total number of A/D samples to collect
        '    CBRate          :sample rate in samples per second
        '    ADData[]        :the array for the collected data values
        '    Options         :data collection options

        PretrigCount = 0
        CBCount = NumElements ' Number of data points to collect

        Options = MccDaq.ScanOptions.ConvertData + MccDaq.ScanOptions.Background + MccDaq.ScanOptions.Continuous + MccDaq.ScanOptions.ExtTrigger
        CBRate = 100 ' Acquire data at 100 Hz

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.DaqInScan(ChanArray, ChanTypeArray, GainArray, ChanCount, CBRate, PretrigCount, CBCount, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        If Status = MccDaq.MccBoard.Running Then
            lblShowStartTrig.Text = "Waiting for trigger..."
            lblShowStopTrig.Text = ""
            lblShowStat.Text = "Running"
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")
        End If

        tmrCheckStatus.Enabled = 1

    End Sub


    Private Sub tmrCheckStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrCheckStatus.Tick
        Dim FirstPoint As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short

        ' This timer will check the status of the background data collection

        ' Parameters:
        '   BoardNum    :the number used by CB.CFG to describe this board
        '   Status     :current status of the background data collection
        '   CurCount   :current number of samples collected
        '   CurIndex   :index to the data buffer pointing to the start of the
        '                most recently collected scan
        '   FunctionType: A/D operation (MccDaq.FunctionType.DaqiFunction)

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


        lblShowCount.Text = CurCount.ToString("D")
        lblShowIndex.Text = CurIndex.ToString("D")

        ' Check if the background operation has finished. If it has, then
        ' transfer the data from the memory buffer set up by Windows to an
        ' array for use by Visual Basic
        ' The BACKGROUND operation must be explicitly stopped

        If UserTerm = 0 Then
            lblShowStat.Text = "Running"
            ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqiFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")

            FirstPoint = CurIndex
            If FirstPoint >= 0 Then
              lblShowStartTrig.Text = "Triggered!"
              lblShowStopTrig.Text = "Waiting for trigger..."
              If MemHandle = 0 Then Stop
              ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, ChanCount)
              If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

              If Status = MccDaq.MccBoard.Idle Then
                lblShowStopTrig.Text = "Triggered!"
              End If

              lblADData(0).Text = ADData(0).ToString("D")
              lblADData(1).Text = ADData(1).ToString("D")
              lblADData(2).Text = ADData(2).ToString("D")
           End If
        End If
        If Status = MccDaq.MccBoard.Idle Or UserTerm = 1 Then
            lblShowStat.Text = "Idle"
            tmrCheckStatus.Enabled = 0

            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DaqiFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
            cmdStartBgnd.Enabled = 1
            cmdStartBgnd.Visible = 1
            cmdStopConvert.Enabled = 0
            cmdStopConvert.Visible = 0
            cmdQuit.Enabled = 1
        End If

    End Sub

    Private Sub cmdQuit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdQuit.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by
        ' other programs
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        End

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        UserTerm = 1

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
    Public WithEvents cmdQuit As System.Windows.Forms.Button
    Public WithEvents tmrCheckStatus As System.Windows.Forms.Timer
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents cmdStartBgnd As System.Windows.Forms.Button
    Public WithEvents lblShowStopTrig As System.Windows.Forms.Label
    Public WithEvents lblShowStartTrig As System.Windows.Forms.Label
    Public WithEvents lblStopTrig As System.Windows.Forms.Label
    Public WithEvents lblStartTrig As System.Windows.Forms.Label
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblShowIndex As System.Windows.Forms.Label
    Public WithEvents lblIndex As System.Windows.Forms.Label
    Public WithEvents lblShowStat As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents _lblADData_2 As System.Windows.Forms.Label
    Public WithEvents lblChan2 As System.Windows.Forms.Label
    Public WithEvents _lblADData_1 As System.Windows.Forms.Label
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents _lblADData_0 As System.Windows.Forms.Label
    Public WithEvents lblChan0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
Friend WithEvents Label1 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
Me.components = New System.ComponentModel.Container()
Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
Me.cmdQuit = New System.Windows.Forms.Button()
Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
Me.cmdStopConvert = New System.Windows.Forms.Button()
Me.cmdStartBgnd = New System.Windows.Forms.Button()
Me.lblShowStopTrig = New System.Windows.Forms.Label()
Me.lblShowStartTrig = New System.Windows.Forms.Label()
Me.lblStopTrig = New System.Windows.Forms.Label()
Me.lblStartTrig = New System.Windows.Forms.Label()
Me.lblShowCount = New System.Windows.Forms.Label()
Me.lblCount = New System.Windows.Forms.Label()
Me.lblShowIndex = New System.Windows.Forms.Label()
Me.lblIndex = New System.Windows.Forms.Label()
Me.lblShowStat = New System.Windows.Forms.Label()
Me.lblStatus = New System.Windows.Forms.Label()
Me._lblADData_2 = New System.Windows.Forms.Label()
Me.lblChan2 = New System.Windows.Forms.Label()
Me._lblADData_1 = New System.Windows.Forms.Label()
Me.lblChan1 = New System.Windows.Forms.Label()
Me._lblADData_0 = New System.Windows.Forms.Label()
Me.lblChan0 = New System.Windows.Forms.Label()
Me.lblDemoFunction = New System.Windows.Forms.Label()
Me.Label1 = New System.Windows.Forms.Label()
Me.SuspendLayout()
'
'cmdQuit
'
Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdQuit.Location = New System.Drawing.Point(280, 304)
Me.cmdQuit.Name = "cmdQuit"
Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdQuit.Size = New System.Drawing.Size(52, 26)
Me.cmdQuit.TabIndex = 9
Me.cmdQuit.Text = "Quit"
'
'tmrCheckStatus
'
Me.tmrCheckStatus.Interval = 200
'
'cmdStopConvert
'
Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdStopConvert.Enabled = False
Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdStopConvert.Location = New System.Drawing.Point(80, 88)
Me.cmdStopConvert.Name = "cmdStopConvert"
Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdStopConvert.Size = New System.Drawing.Size(180, 27)
Me.cmdStopConvert.TabIndex = 7
Me.cmdStopConvert.Text = "Stop Background Operation"
Me.cmdStopConvert.Visible = False
'
'cmdStartBgnd
'
Me.cmdStartBgnd.BackColor = System.Drawing.SystemColors.Control
Me.cmdStartBgnd.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdStartBgnd.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdStartBgnd.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdStartBgnd.Location = New System.Drawing.Point(80, 88)
Me.cmdStartBgnd.Name = "cmdStartBgnd"
Me.cmdStartBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdStartBgnd.Size = New System.Drawing.Size(180, 27)
Me.cmdStartBgnd.TabIndex = 8
Me.cmdStartBgnd.Text = "Start Background Operation"
'
'lblShowStopTrig
'
Me.lblShowStopTrig.BackColor = System.Drawing.SystemColors.Window
Me.lblShowStopTrig.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowStopTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowStopTrig.ForeColor = System.Drawing.Color.Blue
Me.lblShowStopTrig.Location = New System.Drawing.Point(144, 240)
Me.lblShowStopTrig.Name = "lblShowStopTrig"
Me.lblShowStopTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowStopTrig.Size = New System.Drawing.Size(185, 25)
Me.lblShowStopTrig.TabIndex = 19
'
'lblShowStartTrig
'
Me.lblShowStartTrig.BackColor = System.Drawing.SystemColors.Window
Me.lblShowStartTrig.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowStartTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowStartTrig.ForeColor = System.Drawing.Color.Blue
Me.lblShowStartTrig.Location = New System.Drawing.Point(144, 216)
Me.lblShowStartTrig.Name = "lblShowStartTrig"
Me.lblShowStartTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowStartTrig.Size = New System.Drawing.Size(177, 25)
Me.lblShowStartTrig.TabIndex = 18
'
'lblStopTrig
'
Me.lblStopTrig.BackColor = System.Drawing.SystemColors.Window
Me.lblStopTrig.Cursor = System.Windows.Forms.Cursors.Default
Me.lblStopTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblStopTrig.ForeColor = System.Drawing.SystemColors.ControlText
Me.lblStopTrig.Location = New System.Drawing.Point(16, 240)
Me.lblStopTrig.Name = "lblStopTrig"
Me.lblStopTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblStopTrig.Size = New System.Drawing.Size(121, 25)
Me.lblStopTrig.TabIndex = 17
Me.lblStopTrig.Text = "Stop Trigger Status:"
Me.lblStopTrig.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblStartTrig
'
Me.lblStartTrig.BackColor = System.Drawing.SystemColors.Window
Me.lblStartTrig.Cursor = System.Windows.Forms.Cursors.Default
Me.lblStartTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblStartTrig.ForeColor = System.Drawing.SystemColors.ControlText
Me.lblStartTrig.Location = New System.Drawing.Point(16, 216)
Me.lblStartTrig.Name = "lblStartTrig"
Me.lblStartTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblStartTrig.Size = New System.Drawing.Size(121, 25)
Me.lblStartTrig.TabIndex = 16
Me.lblStartTrig.Text = "Start Trigger Status:"
Me.lblStartTrig.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblShowCount
'
Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
Me.lblShowCount.Location = New System.Drawing.Point(200, 320)
Me.lblShowCount.Name = "lblShowCount"
Me.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowCount.Size = New System.Drawing.Size(58, 14)
Me.lblShowCount.TabIndex = 15
'
'lblCount
'
Me.lblCount.BackColor = System.Drawing.SystemColors.Window
Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
Me.lblCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblCount.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblCount.Location = New System.Drawing.Point(80, 320)
Me.lblCount.Name = "lblCount"
Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblCount.Size = New System.Drawing.Size(103, 14)
Me.lblCount.TabIndex = 13
Me.lblCount.Text = "Current Count:"
Me.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblShowIndex
'
Me.lblShowIndex.BackColor = System.Drawing.SystemColors.Window
Me.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowIndex.ForeColor = System.Drawing.Color.Blue
Me.lblShowIndex.Location = New System.Drawing.Point(200, 296)
Me.lblShowIndex.Name = "lblShowIndex"
Me.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowIndex.Size = New System.Drawing.Size(52, 14)
Me.lblShowIndex.TabIndex = 14
'
'lblIndex
'
Me.lblIndex.BackColor = System.Drawing.SystemColors.Window
Me.lblIndex.Cursor = System.Windows.Forms.Cursors.Default
Me.lblIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblIndex.Location = New System.Drawing.Point(80, 296)
Me.lblIndex.Name = "lblIndex"
Me.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblIndex.Size = New System.Drawing.Size(103, 14)
Me.lblIndex.TabIndex = 12
Me.lblIndex.Text = "Current Index:"
Me.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblShowStat
'
Me.lblShowStat.BackColor = System.Drawing.SystemColors.Window
Me.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowStat.ForeColor = System.Drawing.Color.Blue
Me.lblShowStat.Location = New System.Drawing.Point(224, 280)
Me.lblShowStat.Name = "lblShowStat"
Me.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowStat.Size = New System.Drawing.Size(66, 14)
Me.lblShowStat.TabIndex = 11
'
'lblStatus
'
Me.lblStatus.BackColor = System.Drawing.SystemColors.Window
Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
Me.lblStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblStatus.Location = New System.Drawing.Point(8, 280)
Me.lblStatus.Name = "lblStatus"
Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblStatus.Size = New System.Drawing.Size(212, 14)
Me.lblStatus.TabIndex = 10
Me.lblStatus.Text = "Status of Background Operation:"
Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'_lblADData_2
'
Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
Me._lblADData_2.Location = New System.Drawing.Point(152, 176)
Me._lblADData_2.Name = "_lblADData_2"
Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_2.Size = New System.Drawing.Size(105, 17)
Me._lblADData_2.TabIndex = 6
'
'lblChan2
'
Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan2.Location = New System.Drawing.Point(56, 176)
Me.lblChan2.Name = "lblChan2"
Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan2.Size = New System.Drawing.Size(81, 17)
Me.lblChan2.TabIndex = 3
Me.lblChan2.Text = "Counter 0:"
Me.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'_lblADData_1
'
Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
Me._lblADData_1.Location = New System.Drawing.Point(152, 152)
Me._lblADData_1.Name = "_lblADData_1"
Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_1.Size = New System.Drawing.Size(105, 17)
Me._lblADData_1.TabIndex = 5
'
'lblChan1
'
Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan1.Location = New System.Drawing.Point(40, 152)
Me.lblChan1.Name = "lblChan1"
Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan1.Size = New System.Drawing.Size(97, 17)
Me.lblChan1.TabIndex = 2
Me.lblChan1.Text = "FIRSTPORTA:"
Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'_lblADData_0
'
Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
Me._lblADData_0.Location = New System.Drawing.Point(152, 128)
Me._lblADData_0.Name = "_lblADData_0"
Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_0.Size = New System.Drawing.Size(105, 17)
Me._lblADData_0.TabIndex = 4
'
'lblChan0
'
Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan0.Location = New System.Drawing.Point(56, 128)
Me.lblChan0.Name = "lblChan0"
Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan0.Size = New System.Drawing.Size(81, 17)
Me.lblChan0.TabIndex = 1
Me.lblChan0.Text = "Channel 0:"
Me.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblDemoFunction
'
Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblDemoFunction.Location = New System.Drawing.Point(6, 6)
Me.lblDemoFunction.Name = "lblDemoFunction"
Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblDemoFunction.Size = New System.Drawing.Size(337, 18)
Me.lblDemoFunction.TabIndex = 0
Me.lblDemoFunction.Text = "Demonstration of  MccBoard.DaqSetTrigger()"
Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
'
'Label1
'
Me.Label1.ForeColor = System.Drawing.Color.Red
Me.Label1.Location = New System.Drawing.Point(16, 32)
Me.Label1.Name = "Label1"
Me.Label1.Size = New System.Drawing.Size(328, 40)
Me.Label1.TabIndex = 20
Me.Label1.Text = "Trigger signals are needed for this sample. Signals required: ACH0 - signal that " & _
"transitions from below 2V to above. CNT0 should have a TTL signal applied."
'
'frmStatusDisplay
'
Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
Me.BackColor = System.Drawing.SystemColors.Window
Me.ClientSize = New System.Drawing.Size(350, 349)
Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Label1, Me.cmdQuit, Me.cmdStopConvert, Me.cmdStartBgnd, Me.lblShowStopTrig, Me.lblShowStartTrig, Me.lblStopTrig, Me.lblStartTrig, Me.lblShowCount, Me.lblCount, Me.lblShowIndex, Me.lblIndex, Me.lblShowStat, Me.lblStatus, Me._lblADData_2, Me.lblChan2, Me._lblADData_1, Me.lblChan1, Me._lblADData_0, Me.lblChan0, Me.lblDemoFunction})
Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.ForeColor = System.Drawing.Color.Blue
Me.Location = New System.Drawing.Point(188, 108)
Me.Name = "frmStatusDisplay"
Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
Me.Text = "Universal Library DaqSetTrigger()"
Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        ' Note: Any change to label names requires a change to the corresponding array element
        lblADData = (New System.Windows.Forms.Label() {Me._lblADData_0, Me._lblADData_1, Me._lblADData_2})

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