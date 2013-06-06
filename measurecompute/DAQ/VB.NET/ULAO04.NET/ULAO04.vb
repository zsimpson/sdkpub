'==========================================================================

' File:                         ULAO04.vb

' Library Call Demonstrated:    Mccdaq.MccBoard.AOutScan()
'                               with scan options = MccDaq.ScanOptions.ScaleData

' Purpose:                      Synchronously writes to Analog channels in the background.
'                               

' Demonstration:                Sends output to the D/A channels
'                               until a key is pressed.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must support Mccdaq.MccBoard.AOutScan().
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

    Dim DAData(Count) As Double ' dimension an array to hold the output values
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through cbWinBufAlloc%()
    Dim UserTerm As Short

    Private Sub frmStatusDisplay_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        lblChan0ValL.Text = DAData(0).ToString("0.00000000")
        lblChan1ValL.Text = DAData(1).ToString("0.00000000")
        lblChan0ValH.Text = DAData(2).ToString("0.00000000")
        lblChan1ValH.Text = DAData(3).ToString("0.00000000")
    End Sub

    Private Sub cmdStartBgnd_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartBgnd.Click
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim Rate As Integer
        Dim Options As MccDaq.ScanOptions
        Dim Gain As MccDaq.Range

        Dim HighChan As Integer
        Dim LowChan As Integer

        cmdStartBgnd.Enabled = 0
        cmdStartBgnd.Visible = 0
        cmdStopConvert.Enabled = 1
        cmdStopConvert.Visible = 1
        cmdQuit.Enabled = 0
        UserTerm = 0 ' initialize user terminate flag

        ' Parameters:
        '   LowChan    :the lower channel of the scan
        '   HighChan   :the upper channel of the scan
        '   Count      :the number of D/A values to send
        '   Rate       :send rate in values/second (if supported by BoardNum)
        '   MemHandle  :Handle for Windows buffer from which data will be output
        '   Options    :data send options

        LowChan = 0 'First analog output channel
        HighChan = 1 'Last analog output channel
        Rate = 100 'Rate of data update (ignored if board does not
        Gain = MccDaq.Range.Bip5Volts 'Ignored if gain is not programmable
        Options = MccDaq.ScanOptions.Background + MccDaq.ScanOptions.Continuous + MccDaq.ScanOptions.ScaleData
        Rate = 1000 ' Generate data at 1000 Hz

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.AOutScan(LowChan, HighChan, Count, Rate, Gain, MemHandle, Options)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.AoFunction)
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
        '   FunctionType: A/D operation (MccDaq.FunctionType.AoFunction)

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.AoFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


        lblShowCount.Text = CurCount.ToString("D")
        lblShowIndex.Text = CurIndex.ToString("D")

        ' Check if the background operation has finished. If it has, then
        ' transfer the data from the memory buffer set up by Windows to an
        ' array for use by Visual Basic
        ' The BACKGROUND operation must be explicitly stopped

        If Status = MccDaq.MccBoard.Running And UserTerm = 0 Then
            lblShowStat.Text = "Running"
            ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.AoFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")
        ElseIf Status = MccDaq.MccBoard.Idle Or UserTerm = 1 Then
            lblShowStat.Text = "Idle"
            tmrCheckStatus.Enabled = 0

            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AoFunction)
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
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblShowIndex As System.Windows.Forms.Label
    Public WithEvents lblIndex As System.Windows.Forms.Label
    Public WithEvents lblShowStat As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Public WithEvents lblChan1ValH As System.Windows.Forms.Label
    Public WithEvents lblChan0ValH As System.Windows.Forms.Label
    Public WithEvents lblChan1ValL As System.Windows.Forms.Label
    Public WithEvents lblChan0ValL As System.Windows.Forms.Label
    Public WithEvents lblOutputH As System.Windows.Forms.Label
    Public WithEvents lblOutputL As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdQuit = New System.Windows.Forms.Button()
        Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdStartBgnd = New System.Windows.Forms.Button()
        Me.lblChan1ValH = New System.Windows.Forms.Label()
        Me.lblChan0ValH = New System.Windows.Forms.Label()
        Me.lblChan1ValL = New System.Windows.Forms.Label()
        Me.lblChan0ValL = New System.Windows.Forms.Label()
        Me.lblShowCount = New System.Windows.Forms.Label()
        Me.lblCount = New System.Windows.Forms.Label()
        Me.lblShowIndex = New System.Windows.Forms.Label()
        Me.lblIndex = New System.Windows.Forms.Label()
        Me.lblShowStat = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me.lblOutputH = New System.Windows.Forms.Label()
        Me.lblOutputL = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdQuit
        '
        Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
        Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdQuit.Location = New System.Drawing.Point(280, 200)
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
        'lblChan1ValH
        '
        Me.lblChan1ValH.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1ValH.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1ValH.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1ValH.ForeColor = System.Drawing.Color.Blue
        Me.lblChan1ValH.Location = New System.Drawing.Point(200, 136)
        Me.lblChan1ValH.Name = "lblChan1ValH"
        Me.lblChan1ValH.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1ValH.Size = New System.Drawing.Size(81, 17)
        Me.lblChan1ValH.TabIndex = 15
        Me.lblChan1ValH.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0ValH
        '
        Me.lblChan0ValH.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0ValH.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0ValH.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0ValH.ForeColor = System.Drawing.Color.Blue
        Me.lblChan0ValH.Location = New System.Drawing.Point(112, 136)
        Me.lblChan0ValH.Name = "lblChan0ValH"
        Me.lblChan0ValH.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0ValH.Size = New System.Drawing.Size(81, 17)
        Me.lblChan0ValH.TabIndex = 14
        Me.lblChan0ValH.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan1ValL
        '
        Me.lblChan1ValL.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1ValL.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1ValL.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1ValL.ForeColor = System.Drawing.Color.Blue
        Me.lblChan1ValL.Location = New System.Drawing.Point(200, 112)
        Me.lblChan1ValL.Name = "lblChan1ValL"
        Me.lblChan1ValL.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1ValL.Size = New System.Drawing.Size(81, 17)
        Me.lblChan1ValL.TabIndex = 13
        Me.lblChan1ValL.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0ValL
        '
        Me.lblChan0ValL.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0ValL.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0ValL.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0ValL.ForeColor = System.Drawing.Color.Blue
        Me.lblChan0ValL.Location = New System.Drawing.Point(112, 112)
        Me.lblChan0ValL.Name = "lblChan0ValL"
        Me.lblChan0ValL.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0ValL.Size = New System.Drawing.Size(81, 17)
        Me.lblChan0ValL.TabIndex = 12
        Me.lblChan0ValL.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblShowCount
        '
        Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCount.Location = New System.Drawing.Point(192, 216)
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
        Me.lblCount.Location = New System.Drawing.Point(80, 216)
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
        Me.lblShowIndex.Location = New System.Drawing.Point(192, 192)
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
        Me.lblIndex.Location = New System.Drawing.Point(80, 192)
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
        Me.lblShowStat.Location = New System.Drawing.Point(224, 176)
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
        Me.lblStatus.Location = New System.Drawing.Point(0, 176)
        Me.lblStatus.Name = "lblStatus"
        Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatus.Size = New System.Drawing.Size(212, 14)
        Me.lblStatus.TabIndex = 6
        Me.lblStatus.Text = "Status of Background Operation:"
        Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblOutputH
        '
        Me.lblOutputH.BackColor = System.Drawing.SystemColors.Window
        Me.lblOutputH.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblOutputH.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblOutputH.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblOutputH.Location = New System.Drawing.Point(16, 136)
        Me.lblOutputH.Name = "lblOutputH"
        Me.lblOutputH.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblOutputH.Size = New System.Drawing.Size(81, 17)
        Me.lblOutputH.TabIndex = 2
        Me.lblOutputH.Text = "Output(high):"
        Me.lblOutputH.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblOutputL
        '
        Me.lblOutputL.BackColor = System.Drawing.SystemColors.Window
        Me.lblOutputL.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblOutputL.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblOutputL.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblOutputL.Location = New System.Drawing.Point(16, 112)
        Me.lblOutputL.Name = "lblOutputL"
        Me.lblOutputL.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblOutputL.Size = New System.Drawing.Size(81, 17)
        Me.lblOutputL.TabIndex = 1
        Me.lblOutputL.Text = "Output(low):"
        Me.lblOutputL.TextAlign = System.Drawing.ContentAlignment.TopRight
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
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AOutScan() with scan option set to MccDaq.ScanOp" & _
        "tions.ScaleData"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmStatusDisplay
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(350, 238)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdQuit, Me.cmdStopConvert, Me.cmdStartBgnd, Me.lblChan1ValH, Me.lblChan0ValH, Me.lblChan1ValL, Me.lblChan0ValL, Me.lblShowCount, Me.lblCount, Me.lblShowIndex, Me.lblIndex, Me.lblShowStat, Me.lblStatus, Me.lblOutputH, Me.lblOutputL, Me.lblDemoFunction})
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

        MemHandle = MccDaq.MccService.ScaledWinBufAlloc(Count) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

        ' output (low)
        DAData(0) = 0
        DAData(1) = 0

        ' output (high))
        DAData(2) = 5
        DAData(3) = 5

        FirstPoint = 0

        ULStat = MccDaq.MccService.ScaledWinArrayToBuf(DAData(0), MemHandle, FirstPoint, Count)

    End Sub
#End Region

End Class