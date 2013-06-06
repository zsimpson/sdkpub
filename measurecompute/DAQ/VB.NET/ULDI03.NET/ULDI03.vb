'==============================================================================

' File:                         ULDI03.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DInScan()

' Purpose:                      Reads a digital input port
'                               at specified rate and number
'                               of samples.

' Demonstration:                Configures FirstPortA and
'                               FirstPortB for input and
'                               reads the value on the port.

' Other Library Calls:          MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must support paced Digital input

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmDScan
    Inherits System.Windows.Forms.Form

    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalIn ' set direction of port to input
    Const NumPoints As Integer = 500
    Const FirstPoint As Integer = 0

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim DataBuffer(NumPoints) As UInt16
    Dim MemHandle, Count As Integer
    Dim PortNum As MccDaq.DigitalPortType
    Dim Force As Short

    Public lblDataRead As System.Windows.Forms.Label()

    Private Sub cmdReadDIn_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdReadDIn.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim Options As MccDaq.ScanOptions
        Dim Rate As Integer

        'read the digital input and display
        '  Parameters:
        '     PortNum      :the input port
        '     Count      :number of times to read digital input
        '     Rate       :sample rate in samples/second
        '     DataBuffer() :the array for the digital input values read from the port
        '     Options      :data collection options

        Count = NumPoints
        Rate = 100

        Options = MccDaq.ScanOptions.WordXfer Or MccDaq.ScanOptions.Background

        ULStat = DaqBoard.DInScan(PortNum, Count, Rate, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        tmrCheckStatus.Enabled = True

    End Sub

    Private Sub cmdTemp_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdTemp.Click

        Force = 1


    End Sub

    Private Sub ShowData()
        Dim I As Short
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufToArray(MemHandle, DataBuffer(0), FirstPoint, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        For I = 0 To 9
            lblDataRead(I).Text = Hex(Convert.ToInt32(DataBuffer(I)))
        Next I

    End Sub

    Private Sub tmrCheckStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrCheckStatus.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short

        tmrCheckStatus.Stop()

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        lblShowStat.Text = Status.ToString("0")
        lblShowCount.Text = CurCount.ToString("0")
        lblShowIndex.Text = CurIndex.ToString("0")
        If Status = MccDaq.MccBoard.Running Then
            lblBGStat.Text = "Background operation running"
            tmrCheckStatus.Start()
        Else
            lblBGStat.Text = "Background operation idle"
        End If
        If CurCount = NumPoints Or Status = 0 Or Force = 1 Then
            tmrCheckStatus.Enabled = False
            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DiFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
            ShowData()
        End If

    End Sub

    Private Sub cmdStopRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopRead.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        ULStat = MccDaq.MccService.WinBufFree(MemHandle)
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
    Public WithEvents cmdStopRead As System.Windows.Forms.Button
    Public WithEvents cmdReadDIn As System.Windows.Forms.Button
    Public WithEvents cmdTemp As System.Windows.Forms.Button
    Public WithEvents tmrCheckStatus As System.Windows.Forms.Timer
    Public WithEvents _lblDataRead_9 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_4 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_8 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_3 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_7 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_2 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_6 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_1 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_5 As System.Windows.Forms.Label
    Public WithEvents _lblDataRead_0 As System.Windows.Forms.Label
    Public WithEvents lblBGStat As System.Windows.Forms.Label
    Public WithEvents lblShowIndex As System.Windows.Forms.Label
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblShowStat As System.Windows.Forms.Label
    Public WithEvents lblIndex As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents lblFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.cmdReadDIn = New System.Windows.Forms.Button()
        Me.cmdTemp = New System.Windows.Forms.Button()
        Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
        Me._lblDataRead_9 = New System.Windows.Forms.Label()
        Me._lblDataRead_4 = New System.Windows.Forms.Label()
        Me._lblDataRead_8 = New System.Windows.Forms.Label()
        Me._lblDataRead_3 = New System.Windows.Forms.Label()
        Me._lblDataRead_7 = New System.Windows.Forms.Label()
        Me._lblDataRead_2 = New System.Windows.Forms.Label()
        Me._lblDataRead_6 = New System.Windows.Forms.Label()
        Me._lblDataRead_1 = New System.Windows.Forms.Label()
        Me._lblDataRead_5 = New System.Windows.Forms.Label()
        Me._lblDataRead_0 = New System.Windows.Forms.Label()
        Me.lblBGStat = New System.Windows.Forms.Label()
        Me.lblShowIndex = New System.Windows.Forms.Label()
        Me.lblShowCount = New System.Windows.Forms.Label()
        Me.lblShowStat = New System.Windows.Forms.Label()
        Me.lblIndex = New System.Windows.Forms.Label()
        Me.lblCount = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me.lblFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopRead
        '
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Location = New System.Drawing.Point(232, 280)
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.Size = New System.Drawing.Size(81, 33)
        Me.cmdStopRead.TabIndex = 1
        Me.cmdStopRead.Text = "Quit"
        '
        'cmdReadDIn
        '
        Me.cmdReadDIn.BackColor = System.Drawing.SystemColors.Control
        Me.cmdReadDIn.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdReadDIn.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdReadDIn.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdReadDIn.Location = New System.Drawing.Point(128, 280)
        Me.cmdReadDIn.Name = "cmdReadDIn"
        Me.cmdReadDIn.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdReadDIn.Size = New System.Drawing.Size(81, 33)
        Me.cmdReadDIn.TabIndex = 0
        Me.cmdReadDIn.Text = "Read"
        '
        'cmdTemp
        '
        Me.cmdTemp.BackColor = System.Drawing.SystemColors.Control
        Me.cmdTemp.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdTemp.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdTemp.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdTemp.Location = New System.Drawing.Point(32, 280)
        Me.cmdTemp.Name = "cmdTemp"
        Me.cmdTemp.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdTemp.Size = New System.Drawing.Size(81, 33)
        Me.cmdTemp.TabIndex = 2
        Me.cmdTemp.Text = "Force"
        '
        'tmrCheckStatus
        '
        Me.tmrCheckStatus.Interval = 300
        '
        '_lblDataRead_9
        '
        Me._lblDataRead_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_9.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_9.Location = New System.Drawing.Point(240, 248)
        Me._lblDataRead_9.Name = "_lblDataRead_9"
        Me._lblDataRead_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_9.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_9.TabIndex = 7
        Me._lblDataRead_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_4
        '
        Me._lblDataRead_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_4.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_4.Location = New System.Drawing.Point(112, 248)
        Me._lblDataRead_4.Name = "_lblDataRead_4"
        Me._lblDataRead_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_4.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_4.TabIndex = 12
        Me._lblDataRead_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_8
        '
        Me._lblDataRead_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_8.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_8.Location = New System.Drawing.Point(240, 224)
        Me._lblDataRead_8.Name = "_lblDataRead_8"
        Me._lblDataRead_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_8.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_8.TabIndex = 8
        Me._lblDataRead_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_3
        '
        Me._lblDataRead_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_3.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_3.Location = New System.Drawing.Point(112, 224)
        Me._lblDataRead_3.Name = "_lblDataRead_3"
        Me._lblDataRead_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_3.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_3.TabIndex = 13
        Me._lblDataRead_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_7
        '
        Me._lblDataRead_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_7.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_7.Location = New System.Drawing.Point(240, 200)
        Me._lblDataRead_7.Name = "_lblDataRead_7"
        Me._lblDataRead_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_7.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_7.TabIndex = 9
        Me._lblDataRead_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_2
        '
        Me._lblDataRead_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_2.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_2.Location = New System.Drawing.Point(112, 200)
        Me._lblDataRead_2.Name = "_lblDataRead_2"
        Me._lblDataRead_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_2.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_2.TabIndex = 14
        Me._lblDataRead_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_6
        '
        Me._lblDataRead_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_6.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_6.Location = New System.Drawing.Point(240, 176)
        Me._lblDataRead_6.Name = "_lblDataRead_6"
        Me._lblDataRead_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_6.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_6.TabIndex = 10
        Me._lblDataRead_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_1
        '
        Me._lblDataRead_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_1.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_1.Location = New System.Drawing.Point(112, 176)
        Me._lblDataRead_1.Name = "_lblDataRead_1"
        Me._lblDataRead_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_1.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_1.TabIndex = 15
        Me._lblDataRead_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_5
        '
        Me._lblDataRead_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_5.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_5.Location = New System.Drawing.Point(240, 152)
        Me._lblDataRead_5.Name = "_lblDataRead_5"
        Me._lblDataRead_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_5.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_5.TabIndex = 11
        Me._lblDataRead_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataRead_0
        '
        Me._lblDataRead_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataRead_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataRead_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataRead_0.ForeColor = System.Drawing.Color.Blue
        Me._lblDataRead_0.Location = New System.Drawing.Point(112, 152)
        Me._lblDataRead_0.Name = "_lblDataRead_0"
        Me._lblDataRead_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataRead_0.Size = New System.Drawing.Size(57, 17)
        Me._lblDataRead_0.TabIndex = 16
        Me._lblDataRead_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblBGStat
        '
        Me.lblBGStat.BackColor = System.Drawing.SystemColors.Window
        Me.lblBGStat.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblBGStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblBGStat.ForeColor = System.Drawing.Color.Blue
        Me.lblBGStat.Location = New System.Drawing.Point(84, 124)
        Me.lblBGStat.Name = "lblBGStat"
        Me.lblBGStat.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblBGStat.Size = New System.Drawing.Size(189, 17)
        Me.lblBGStat.TabIndex = 3
        '
        'lblShowIndex
        '
        Me.lblShowIndex.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowIndex.ForeColor = System.Drawing.Color.Blue
        Me.lblShowIndex.Location = New System.Drawing.Point(232, 88)
        Me.lblShowIndex.Name = "lblShowIndex"
        Me.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowIndex.Size = New System.Drawing.Size(81, 17)
        Me.lblShowIndex.TabIndex = 4
        Me.lblShowIndex.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblShowCount
        '
        Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCount.Location = New System.Drawing.Point(136, 88)
        Me.lblShowCount.Name = "lblShowCount"
        Me.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCount.Size = New System.Drawing.Size(81, 17)
        Me.lblShowCount.TabIndex = 5
        Me.lblShowCount.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblShowStat
        '
        Me.lblShowStat.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowStat.ForeColor = System.Drawing.Color.Blue
        Me.lblShowStat.Location = New System.Drawing.Point(40, 88)
        Me.lblShowStat.Name = "lblShowStat"
        Me.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowStat.Size = New System.Drawing.Size(81, 17)
        Me.lblShowStat.TabIndex = 6
        Me.lblShowStat.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblIndex
        '
        Me.lblIndex.BackColor = System.Drawing.SystemColors.Window
        Me.lblIndex.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblIndex.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblIndex.Location = New System.Drawing.Point(232, 64)
        Me.lblIndex.Name = "lblIndex"
        Me.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblIndex.Size = New System.Drawing.Size(81, 17)
        Me.lblIndex.TabIndex = 20
        Me.lblIndex.Text = "Index"
        Me.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblCount
        '
        Me.lblCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCount.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCount.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCount.Location = New System.Drawing.Point(136, 64)
        Me.lblCount.Name = "lblCount"
        Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCount.Size = New System.Drawing.Size(81, 17)
        Me.lblCount.TabIndex = 19
        Me.lblCount.Text = "Count"
        Me.lblCount.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblStatus
        '
        Me.lblStatus.BackColor = System.Drawing.SystemColors.Window
        Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatus.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblStatus.Location = New System.Drawing.Point(40, 64)
        Me.lblStatus.Name = "lblStatus"
        Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatus.Size = New System.Drawing.Size(81, 17)
        Me.lblStatus.TabIndex = 18
        Me.lblStatus.Text = "Status"
        Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblFunction
        '
        Me.lblFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFunction.Location = New System.Drawing.Point(24, 16)
        Me.lblFunction.Name = "lblFunction"
        Me.lblFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFunction.Size = New System.Drawing.Size(281, 25)
        Me.lblFunction.TabIndex = 17
        Me.lblFunction.Text = "Mccdaq.MccBoard.DInScan() Example Program"
        Me.lblFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDScan
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(361, 322)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopRead, Me.cmdReadDIn, Me.cmdTemp, Me._lblDataRead_9, Me._lblDataRead_4, Me._lblDataRead_8, Me._lblDataRead_3, Me._lblDataRead_7, Me._lblDataRead_2, Me._lblDataRead_6, Me._lblDataRead_1, Me._lblDataRead_5, Me._lblDataRead_0, Me.lblBGStat, Me.lblShowIndex, Me.lblShowCount, Me.lblShowStat, Me.lblIndex, Me.lblCount, Me.lblStatus, Me.lblFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDScan"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Digital Input"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ULStat As MccDaq.ErrorInfo

        lblDataRead = New System.Windows.Forms.Label(10) {}
        Me.lblDataRead.SetValue(_lblDataRead_9, 9)
        Me.lblDataRead.SetValue(_lblDataRead_8, 8)
        Me.lblDataRead.SetValue(_lblDataRead_7, 7)
        Me.lblDataRead.SetValue(_lblDataRead_6, 6)
        Me.lblDataRead.SetValue(_lblDataRead_5, 5)
        Me.lblDataRead.SetValue(_lblDataRead_4, 4)
        Me.lblDataRead.SetValue(_lblDataRead_3, 3)
        Me.lblDataRead.SetValue(_lblDataRead_2, 2)
        Me.lblDataRead.SetValue(_lblDataRead_1, 1)
        Me.lblDataRead.SetValue(_lblDataRead_0, 0)

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


        ' configure FirstPortA for digital input
        '  Parameters:
        '    PortNum    :the input port
        '    Direction  :sets the port for input or output


        'configure FirstPortA & FirstPortB for digital input
        '  Parameters:
        '     PortNum    :the input port
        '     Direction  :sets the port for input or output

        MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

        PortNum = MccDaq.DigitalPortType.FirstPortB
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        PortNum = MccDaq.DigitalPortType.FirstPortA
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        Force = 0

    End Sub
#End Region

End Class