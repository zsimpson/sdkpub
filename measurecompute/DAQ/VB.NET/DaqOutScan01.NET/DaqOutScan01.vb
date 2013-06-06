'==========================================================================

' File:                         DaqOutScan01

' Library Call Demonstrated:    Mccdaq.MccBoard.DaqOutScan(), Background mode

' Purpose:                      Synchronously writes to an Analog channel and a Digital port in the background.
'                               

' Demonstration:                Sends output to the D/A channels
'                               until a key is pressed.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               Mccdaq.MccBoard.DConfigPort()

' Special Requirements:         Board 0 must support Mccdaq.MccBoard.DaqOutScan().
'

' (c) Copyright 1995-2006, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Option Strict Off
Option Explicit On
Friend Class frmStatusDisplay
    Inherits System.Windows.Forms.Form

    Const BoardNum As Short = 0 ' Board number
    Const ChanCount As Integer = 2 ' Number of channels in scan
    Const NumPoints As Integer = 2 ' Number of data points to collect
    Const Count As Integer = ChanCount * NumPoints

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim DAData(Count) As UInt16 ' dimension an array to hold the output values
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through cbWinBufAlloc%()
    Dim ChanArray(ChanCount) As Short ' array to hold channel queue information
    Dim ChanTypeArray(ChanCount) As MccDaq.ChannelType ' array to hold channel type information
    Dim GainArray(ChanCount) As MccDaq.Range ' array to hold gain queue information
    Dim UserTerm As Short

    Private Sub frmStatusDisplay_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load

        'load the arrays with values
        ChanArray(0) = 0
        ChanTypeArray(0) = MccDaq.ChannelType.Analog
        GainArray(0) = MccDaq.Range.Bip10Volts

        lblChan0.Text = "0"
        lblChan0Type.Text = "Analog"
        lblChan0Gain.Text = "±10 Volts"

        ChanArray(1) = MccDaq.DigitalPortType.FirstPortA
        ChanTypeArray(1) = MccDaq.ChannelType.Digital16
        GainArray(1) = MccDaq.Range.NotUsed

        lblChan1.Text = "FirstPortA"
        lblChan1Type.Text = "Digital16"
        lblChan1Gain.Text = "NotUsed"

    End Sub

    Private Sub cmdStartBgnd_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartBgnd.Click
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim CBRate As Integer
        Dim Options As MccDaq.ScanOptions

        Dim Direction As MccDaq.DigitalPortDirection
        Dim PortNum As MccDaq.DigitalPortType

        cmdStartBgnd.Enabled = 0
        cmdStartBgnd.Visible = 0
        cmdStopConvert.Enabled = 1
        cmdStopConvert.Visible = 1
        cmdQuit.Enabled = 0
        UserTerm = 0 ' initialize user terminate flag

         'FirstPortA is treated as a 16-bit port; therefore FirtstPortA and FirstPortB must be configured for digital output
        PortNum = MccDaq.DigitalPortType.FirstPortA
        Direction = MccDaq.DigitalPortDirection.DigitalOut
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)

        PortNum = MccDaq.DigitalPortType.FirstPortB
        Direction = MccDaq.DigitalPortDirection.DigitalOut
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        ' Collect the values with cbDaqInScan()
        '  Parameters:
        '    BoardNum        :the number used by CB.CFG to describe this board
        '    ChanArray[]     :array of channel values
        '    ChanTypeArray[] : array of channel types
        '    GainArray[]     :array of gain values
        '    ChansCount      :the number of elements in the arrays (0=disable queue)
        '    Count           :the total number of A/D samples to collect
        '    CBRate          :sample rate in samples per second
        '    ADData[]        :the array for the collected data values
        '    Options         :data collection options

        Options = MccDaq.ScanOptions.Background + MccDaq.ScanOptions.Continuous + MccDaq.ScanOptions.NonStreamedIO
        CBRate = 1000 ' Acquire data at 1000 Hz

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.DaqOutScan(ChanArray, ChanTypeArray, GainArray, ChanCount, CBRate, Count, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqoFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        If Status = MccDaq.MccBoard.Running Then
            lblShowStat.Text = "Running"
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")
        End If

        tmrCheckStatus.Enabled = 1

    End Sub

    Private Sub tmrCheckStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrCheckStatus.Tick
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
        '   FunctionType: A/D operation (MccDaq.FunctionType.DaqoFunction)

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqoFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


        lblShowCount.Text = CurCount.ToString("D")
        lblShowIndex.Text = CurIndex.ToString("D")

        ' Check if the background operation has finished. If it has, then
        ' transfer the data from the memory buffer set up by Windows to an
        ' array for use by Visual Basic
        ' The BACKGROUND operation must be explicitly stopped

        If Status = MccDaq.MccBoard.Running And UserTerm = 0 Then
            lblShowStat.Text = "Running"
            ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqoFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")
        ElseIf Status = MccDaq.MccBoard.Idle Or UserTerm = 1 Then
            lblShowStat.Text = "Idle"
            tmrCheckStatus.Enabled = 0

            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DaqoFunction)
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
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents lblChan0 As System.Windows.Forms.Label
    Public WithEvents lblChan As System.Windows.Forms.Label
    Public WithEvents lblChan1Gain As System.Windows.Forms.Label
    Public WithEvents lblChan0Gain As System.Windows.Forms.Label
    Public WithEvents lblChan1Type As System.Windows.Forms.Label
    Public WithEvents lblChan0Type As System.Windows.Forms.Label
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblShowIndex As System.Windows.Forms.Label
    Public WithEvents lblIndex As System.Windows.Forms.Label
    Public WithEvents lblShowStat As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents lblChan2 As System.Windows.Forms.Label
    Public WithEvents lblType As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdQuit = New System.Windows.Forms.Button()
        Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdStartBgnd = New System.Windows.Forms.Button()
        Me.lblChan1 = New System.Windows.Forms.Label()
        Me.lblChan0 = New System.Windows.Forms.Label()
        Me.lblChan = New System.Windows.Forms.Label()
        Me.lblChan1Gain = New System.Windows.Forms.Label()
        Me.lblChan0Gain = New System.Windows.Forms.Label()
        Me.lblChan1Type = New System.Windows.Forms.Label()
        Me.lblChan0Type = New System.Windows.Forms.Label()
        Me.lblShowCount = New System.Windows.Forms.Label()
        Me.lblCount = New System.Windows.Forms.Label()
        Me.lblShowIndex = New System.Windows.Forms.Label()
        Me.lblIndex = New System.Windows.Forms.Label()
        Me.lblShowStat = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me.lblChan2 = New System.Windows.Forms.Label()
        Me.lblType = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdQuit
        '
        Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
        Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdQuit.Location = New System.Drawing.Point(280, 240)
        Me.cmdQuit.Name = "cmdQuit"
        Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdQuit.Size = New System.Drawing.Size(52, 26)
        Me.cmdQuit.TabIndex = 5
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
        Me.cmdStopConvert.Location = New System.Drawing.Point(83, 72)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(180, 27)
        Me.cmdStopConvert.TabIndex = 3
        Me.cmdStopConvert.Text = "Stop Background Operation"
        Me.cmdStopConvert.Visible = False
        '
        'cmdStartBgnd
        '
        Me.cmdStartBgnd.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartBgnd.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartBgnd.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartBgnd.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartBgnd.Location = New System.Drawing.Point(83, 72)
        Me.cmdStartBgnd.Name = "cmdStartBgnd"
        Me.cmdStartBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartBgnd.Size = New System.Drawing.Size(180, 27)
        Me.cmdStartBgnd.TabIndex = 4
        Me.cmdStartBgnd.Text = "Start Background Operation"
        '
        'lblChan1
        '
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.ForeColor = System.Drawing.Color.Blue
        Me.lblChan1.Location = New System.Drawing.Point(200, 112)
        Me.lblChan1.Name = "lblChan1"
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.Size = New System.Drawing.Size(81, 17)
        Me.lblChan1.TabIndex = 18
        Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0
        '
        Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0.ForeColor = System.Drawing.Color.Blue
        Me.lblChan0.Location = New System.Drawing.Point(112, 112)
        Me.lblChan0.Name = "lblChan0"
        Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0.Size = New System.Drawing.Size(81, 17)
        Me.lblChan0.TabIndex = 17
        Me.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan
        '
        Me.lblChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan.Location = New System.Drawing.Point(16, 112)
        Me.lblChan.Name = "lblChan"
        Me.lblChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan.Size = New System.Drawing.Size(81, 17)
        Me.lblChan.TabIndex = 16
        Me.lblChan.Text = "Channel:"
        Me.lblChan.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblChan1Gain
        '
        Me.lblChan1Gain.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1Gain.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1Gain.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1Gain.ForeColor = System.Drawing.Color.Blue
        Me.lblChan1Gain.Location = New System.Drawing.Point(200, 160)
        Me.lblChan1Gain.Name = "lblChan1Gain"
        Me.lblChan1Gain.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1Gain.Size = New System.Drawing.Size(81, 17)
        Me.lblChan1Gain.TabIndex = 15
        Me.lblChan1Gain.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0Gain
        '
        Me.lblChan0Gain.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0Gain.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0Gain.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0Gain.ForeColor = System.Drawing.Color.Blue
        Me.lblChan0Gain.Location = New System.Drawing.Point(112, 160)
        Me.lblChan0Gain.Name = "lblChan0Gain"
        Me.lblChan0Gain.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0Gain.Size = New System.Drawing.Size(81, 17)
        Me.lblChan0Gain.TabIndex = 14
        Me.lblChan0Gain.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan1Type
        '
        Me.lblChan1Type.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1Type.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1Type.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1Type.ForeColor = System.Drawing.Color.Blue
        Me.lblChan1Type.Location = New System.Drawing.Point(200, 136)
        Me.lblChan1Type.Name = "lblChan1Type"
        Me.lblChan1Type.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1Type.Size = New System.Drawing.Size(81, 17)
        Me.lblChan1Type.TabIndex = 13
        Me.lblChan1Type.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0Type
        '
        Me.lblChan0Type.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0Type.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0Type.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0Type.ForeColor = System.Drawing.Color.Blue
        Me.lblChan0Type.Location = New System.Drawing.Point(112, 136)
        Me.lblChan0Type.Name = "lblChan0Type"
        Me.lblChan0Type.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0Type.Size = New System.Drawing.Size(81, 17)
        Me.lblChan0Type.TabIndex = 12
        Me.lblChan0Type.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblShowCount
        '
        Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCount.Location = New System.Drawing.Point(199, 256)
        Me.lblShowCount.Name = "lblShowCount"
        Me.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCount.Size = New System.Drawing.Size(59, 14)
        Me.lblShowCount.TabIndex = 11
        '
        'lblCount
        '
        Me.lblCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCount.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCount.Location = New System.Drawing.Point(84, 256)
        Me.lblCount.Name = "lblCount"
        Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCount.Size = New System.Drawing.Size(104, 14)
        Me.lblCount.TabIndex = 9
        Me.lblCount.Text = "Current Count:"
        Me.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowIndex
        '
        Me.lblShowIndex.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowIndex.ForeColor = System.Drawing.Color.Blue
        Me.lblShowIndex.Location = New System.Drawing.Point(199, 232)
        Me.lblShowIndex.Name = "lblShowIndex"
        Me.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowIndex.Size = New System.Drawing.Size(52, 14)
        Me.lblShowIndex.TabIndex = 10
        '
        'lblIndex
        '
        Me.lblIndex.BackColor = System.Drawing.SystemColors.Window
        Me.lblIndex.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblIndex.Location = New System.Drawing.Point(84, 232)
        Me.lblIndex.Name = "lblIndex"
        Me.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblIndex.Size = New System.Drawing.Size(104, 14)
        Me.lblIndex.TabIndex = 8
        Me.lblIndex.Text = "Current Index:"
        Me.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowStat
        '
        Me.lblShowStat.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowStat.ForeColor = System.Drawing.Color.Blue
        Me.lblShowStat.Location = New System.Drawing.Point(224, 216)
        Me.lblShowStat.Name = "lblShowStat"
        Me.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowStat.Size = New System.Drawing.Size(66, 14)
        Me.lblShowStat.TabIndex = 7
        '
        'lblStatus
        '
        Me.lblStatus.BackColor = System.Drawing.SystemColors.Window
        Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblStatus.Location = New System.Drawing.Point(6, 216)
        Me.lblStatus.Name = "lblStatus"
        Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatus.Size = New System.Drawing.Size(212, 14)
        Me.lblStatus.TabIndex = 6
        Me.lblStatus.Text = "Status of Background Operation:"
        Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblChan2
        '
        Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan2.Location = New System.Drawing.Point(16, 160)
        Me.lblChan2.Name = "lblChan2"
        Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan2.Size = New System.Drawing.Size(81, 17)
        Me.lblChan2.TabIndex = 2
        Me.lblChan2.Text = "Gain:"
        Me.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblType
        '
        Me.lblType.BackColor = System.Drawing.SystemColors.Window
        Me.lblType.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblType.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblType.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblType.Location = New System.Drawing.Point(16, 136)
        Me.lblType.Name = "lblType"
        Me.lblType.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblType.Size = New System.Drawing.Size(81, 17)
        Me.lblType.TabIndex = 1
        Me.lblType.Text = "Type:"
        Me.lblType.TextAlign = System.Drawing.ContentAlignment.TopRight
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
        Me.lblDemoFunction.Size = New System.Drawing.Size(337, 50)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DaqOutScan() with scan option set to MccDaq.Scan" & _
        "Options.Background + MccDaq.ScanOptions.Continuous + MccDaq.ScanOptions.NonStrea" & _
        "medIO"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmStatusDisplay
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(350, 284)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdQuit, Me.cmdStopConvert, Me.cmdStartBgnd, Me.lblChan1, Me.lblChan0, Me.lblChan, Me.lblChan1Gain, Me.lblChan0Gain, Me.lblChan1Type, Me.lblChan0Type, Me.lblShowCount, Me.lblCount, Me.lblShowIndex, Me.lblIndex, Me.lblShowStat, Me.lblStatus, Me.lblChan2, Me.lblType, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(188, 108)
        Me.Name = "frmStatusDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library DaqOutScan()"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim FirstPoint As Integer
        Dim ULStat As MccDaq.ErrorInfo

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

        MemHandle = MccDaq.MccService.WinBufAlloc(Count) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

        ' output (low)
        DAData(0) = Convert.ToUInt16(0)
        DAData(1) = Convert.ToUInt16(0)

        ' output (high))
        DAData(2) = Convert.ToUInt16(65535)
        DAData(3) = Convert.ToUInt16(65535)

        FirstPoint = 0

        ULStat = MccDaq.MccService.WinArrayToBuf(DAData(0), MemHandle, FirstPoint, Count)

    End Sub
#End Region

End Class