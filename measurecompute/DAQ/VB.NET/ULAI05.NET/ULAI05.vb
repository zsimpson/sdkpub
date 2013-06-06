'==============================================================================

' File:                         ULAI05.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AInScan() with manual data conversion

' Purpose:                      Demonstrate the manual conversion of data
'                               values after they have been collected.

' Demonstration:                Collects 10 data points from up to five analog
'                               input channels. Data are collected
'                               as 16-bit values and are converted to
'                               channel numbers and 12-bit data values
'                               using BASIC code.

' Other Library Calls:          Mccdaq.MccBoard.GetStatus()
'                               Mccdaq.MccBoard.StopBackground()
'                               Mccdaq.MccBoard.ErrHandling()

' Special Requirements:         Analog signal on up to 5 input channels.
'                               This example supports CIO-DAS16 and CIO-DAS08
'                               board families only.

'==============================================================================
Option Strict Off
Option Explicit On
Friend Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 10     ' Number of data points to collect
    Const FirstPoint As Integer = 0

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ADData(NumPoints) As UInt16     'dimension an array to hold the input values
    Dim ConvData(NumPoints) As UInt16   'dimension an array to hold the converted

    Dim HighChan As Integer
    Dim MemHandle As Integer
    Dim UserTerm As Short

    Public lblConvData As System.Windows.Forms.Label()
    Public lblShowRaw As System.Windows.Forms.Label()

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim Range As MccDaq.Range
        Dim Options As MccDaq.ScanOptions
        Dim Rate As Integer
        Dim Count As Integer
        Dim LowChan As Integer

        cmdStartConvert.Enabled = False
        cmdQuit.Enabled = False
        cmdStopBackground.Enabled = True

        'Collect the values by calling MccDaq.MccBoard.AInScan function in background mode
        '  Parameters:
        '     LowChan   :the first channel of the scan
        '     HighChan  :the last channel of the scan
        '     Count     :the total number of A/D samples to collect
        '     Rate      :sample rate in samples per second
        '     Range     :the range for the board
        '     MemHandle :Handle for Windows buffer to store data in
        '     Options   :data collection options

        LowChan = 0
        HighChan = Integer.Parse(txtHighChan.Text)
        If HighChan > 7 Then HighChan = 7
        txtHighChan.Text = Str(HighChan)

        Count = NumPoints   ' total number of data points to collect
        Rate = 3125     ' per channel sampling rate ((samples per second) per channel)
        Options = MccDaq.ScanOptions.Background ' collect data in BACKGROUND mode
        '                                         as 16-bit values (no conversion)

        Range = MccDaq.Range.Bip5Volts ' set the range

        ULStat = DaqBoard.AInScan(LowChan, HighChan, Count, Rate, Range, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        'during the background operation, check the status using a timer, then print the values

        tmrCheckStatus.Enabled = True

    End Sub

    Private Sub tmrCheckStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrCheckStatus.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short

        tmrCheckStatus.Stop()

        'Check the current status of the background data collection
        '  Parameters:
        '     Status     :current status of the background data collection
        '     CurCount   :current number of samples collected
        '     CurIndex   :index to the data buffer pointing to the last value transferred
        '     FunctionType: A/D operation (MccDaq.FunctionType.AiFunction)

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.AiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' check if the background operation has finished
        If Status = MccDaq.MccBoard.Idle Or UserTerm = 1 Then
            lblStatus.Text = "Data collection finished."

            'the background operation must be explicitly stopped
            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            If MemHandle = 0 Then Stop

            ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, NumPoints)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            cmdStartConvert.Enabled = True
            cmdQuit.Enabled = True
            cmdStopBackground.Enabled = False
            Convert()
        Else
            tmrCheckStatus.Start()

            lblStatus.Text = "Background operation in progress."
        End If

        If UserTerm = 1 Then
            lblStatus.Text = "Data collection terminated by user."
            UserTerm = 0
        End If

    End Sub

    Private Sub Convert()
        Dim channel As Integer
        Dim K As Short
        Dim CurDataValue As Integer

        'Show the data that were collected
        For K = 0 To NumPoints - 1
            lblShowRaw(K).Text = ADData(K).ToString("D")
        Next

        'Manually convert the 16-bit values to 12-bit values

        For K = 0 To NumPoints - 1
            CurDataValue = System.Convert.ToInt32(ADData(K))

            'find the channel number in the first 4-bits
            channel = CurDataValue And 15 'AND Mask with 15

            'retrieve the data value from the next 12-bits
            ' and put them into ConvData() array
            ConvData(K) = System.Convert.ToUInt16(CurDataValue \ 16) 'div by 16 shifts 4 places to right

            lblConvData(K).Text = channel.ToString("0") + "," + ConvData(K).ToString("D")
        Next

    End Sub

    Private Sub cmdStopBackground_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopBackground.Click

        cmdQuit.Enabled = True
        cmdStopBackground.Enabled = False
        UserTerm = 1

    End Sub

    Private Sub cmdQuit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdQuit.Click
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
    Public WithEvents txtHighChan As System.Windows.Forms.TextBox
    Public WithEvents cmdQuit As System.Windows.Forms.Button
    Public WithEvents cmdStartConvert As System.Windows.Forms.Button
    Public WithEvents cmdStopBackground As System.Windows.Forms.Button
    Public WithEvents tmrCheckStatus As System.Windows.Forms.Timer
    Public WithEvents lbl As System.Windows.Forms.Label
    Public WithEvents _lblConvData_9 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_8 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_7 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_6 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_5 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_4 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_3 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_2 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_1 As System.Windows.Forms.Label
    Public WithEvents _lblConvData_0 As System.Windows.Forms.Label
    Public WithEvents lblVoltsRead As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_9 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_8 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_7 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_6 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_5 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_4 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_3 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_2 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_1 As System.Windows.Forms.Label
    Public WithEvents _lblShowRaw_0 As System.Windows.Forms.Label
    Public WithEvents lblRawData As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.txtHighChan = New System.Windows.Forms.TextBox()
        Me.cmdQuit = New System.Windows.Forms.Button()
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me.cmdStopBackground = New System.Windows.Forms.Button()
        Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
        Me.lbl = New System.Windows.Forms.Label()
        Me._lblConvData_9 = New System.Windows.Forms.Label()
        Me._lblConvData_8 = New System.Windows.Forms.Label()
        Me._lblConvData_7 = New System.Windows.Forms.Label()
        Me._lblConvData_6 = New System.Windows.Forms.Label()
        Me._lblConvData_5 = New System.Windows.Forms.Label()
        Me._lblConvData_4 = New System.Windows.Forms.Label()
        Me._lblConvData_3 = New System.Windows.Forms.Label()
        Me._lblConvData_2 = New System.Windows.Forms.Label()
        Me._lblConvData_1 = New System.Windows.Forms.Label()
        Me._lblConvData_0 = New System.Windows.Forms.Label()
        Me.lblVoltsRead = New System.Windows.Forms.Label()
        Me._lblShowRaw_9 = New System.Windows.Forms.Label()
        Me._lblShowRaw_8 = New System.Windows.Forms.Label()
        Me._lblShowRaw_7 = New System.Windows.Forms.Label()
        Me._lblShowRaw_6 = New System.Windows.Forms.Label()
        Me._lblShowRaw_5 = New System.Windows.Forms.Label()
        Me._lblShowRaw_4 = New System.Windows.Forms.Label()
        Me._lblShowRaw_3 = New System.Windows.Forms.Label()
        Me._lblShowRaw_2 = New System.Windows.Forms.Label()
        Me._lblShowRaw_1 = New System.Windows.Forms.Label()
        Me._lblShowRaw_0 = New System.Windows.Forms.Label()
        Me.lblRawData = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'txtHighChan
        '
        Me.txtHighChan.AcceptsReturn = True
        Me.txtHighChan.AutoSize = False
        Me.txtHighChan.BackColor = System.Drawing.SystemColors.Window
        Me.txtHighChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtHighChan.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtHighChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtHighChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtHighChan.Location = New System.Drawing.Point(224, 238)
        Me.txtHighChan.MaxLength = 0
        Me.txtHighChan.Name = "txtHighChan"
        Me.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtHighChan.Size = New System.Drawing.Size(25, 19)
        Me.txtHighChan.TabIndex = 28
        Me.txtHighChan.Text = "3"
        Me.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'cmdQuit
        '
        Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
        Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdQuit.Location = New System.Drawing.Point(312, 264)
        Me.cmdQuit.Name = "cmdQuit"
        Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdQuit.Size = New System.Drawing.Size(52, 26)
        Me.cmdQuit.TabIndex = 4
        Me.cmdQuit.Text = "Quit"
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(248, 264)
        Me.cmdStartConvert.Name = "cmdStartConvert"
        Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartConvert.Size = New System.Drawing.Size(52, 26)
        Me.cmdStartConvert.TabIndex = 3
        Me.cmdStartConvert.Text = "Start"
        '
        'cmdStopBackground
        '
        Me.cmdStopBackground.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopBackground.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopBackground.Enabled = False
        Me.cmdStopBackground.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopBackground.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopBackground.Location = New System.Drawing.Point(64, 264)
        Me.cmdStopBackground.Name = "cmdStopBackground"
        Me.cmdStopBackground.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopBackground.Size = New System.Drawing.Size(137, 25)
        Me.cmdStopBackground.TabIndex = 26
        Me.cmdStopBackground.Text = "Stop Background"
        '
        'tmrCheckStatus
        '
        Me.tmrCheckStatus.Interval = 300
        '
        'lbl
        '
        Me.lbl.BackColor = System.Drawing.SystemColors.Window
        Me.lbl.Cursor = System.Windows.Forms.Cursors.Default
        Me.lbl.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lbl.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lbl.Location = New System.Drawing.Point(96, 240)
        Me.lbl.Name = "lbl"
        Me.lbl.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lbl.Size = New System.Drawing.Size(120, 17)
        Me.lbl.TabIndex = 27
        Me.lbl.Text = "Measure Channels 0 to"
        '
        '_lblConvData_9
        '
        Me._lblConvData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_9.Location = New System.Drawing.Point(296, 208)
        Me._lblConvData_9.Name = "_lblConvData_9"
        Me._lblConvData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_9.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_9.TabIndex = 24
        Me._lblConvData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_8
        '
        Me._lblConvData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_8.Location = New System.Drawing.Point(224, 208)
        Me._lblConvData_8.Name = "_lblConvData_8"
        Me._lblConvData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_8.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_8.TabIndex = 23
        Me._lblConvData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_7
        '
        Me._lblConvData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_7.Location = New System.Drawing.Point(152, 208)
        Me._lblConvData_7.Name = "_lblConvData_7"
        Me._lblConvData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_7.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_7.TabIndex = 22
        Me._lblConvData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_6
        '
        Me._lblConvData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_6.Location = New System.Drawing.Point(80, 208)
        Me._lblConvData_6.Name = "_lblConvData_6"
        Me._lblConvData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_6.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_6.TabIndex = 21
        Me._lblConvData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_5
        '
        Me._lblConvData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_5.Location = New System.Drawing.Point(8, 208)
        Me._lblConvData_5.Name = "_lblConvData_5"
        Me._lblConvData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_5.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_5.TabIndex = 20
        Me._lblConvData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_4
        '
        Me._lblConvData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_4.Location = New System.Drawing.Point(296, 184)
        Me._lblConvData_4.Name = "_lblConvData_4"
        Me._lblConvData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_4.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_4.TabIndex = 19
        Me._lblConvData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_3
        '
        Me._lblConvData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_3.Location = New System.Drawing.Point(224, 184)
        Me._lblConvData_3.Name = "_lblConvData_3"
        Me._lblConvData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_3.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_3.TabIndex = 18
        Me._lblConvData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_2
        '
        Me._lblConvData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_2.Location = New System.Drawing.Point(152, 184)
        Me._lblConvData_2.Name = "_lblConvData_2"
        Me._lblConvData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_2.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_2.TabIndex = 17
        Me._lblConvData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_1
        '
        Me._lblConvData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_1.Location = New System.Drawing.Point(80, 184)
        Me._lblConvData_1.Name = "_lblConvData_1"
        Me._lblConvData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_1.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_1.TabIndex = 16
        Me._lblConvData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblConvData_0
        '
        Me._lblConvData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblConvData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblConvData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblConvData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblConvData_0.Location = New System.Drawing.Point(8, 184)
        Me._lblConvData_0.Name = "_lblConvData_0"
        Me._lblConvData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblConvData_0.Size = New System.Drawing.Size(65, 17)
        Me._lblConvData_0.TabIndex = 6
        Me._lblConvData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblVoltsRead
        '
        Me.lblVoltsRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblVoltsRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblVoltsRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblVoltsRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblVoltsRead.Location = New System.Drawing.Point(8, 144)
        Me.lblVoltsRead.Name = "lblVoltsRead"
        Me.lblVoltsRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblVoltsRead.Size = New System.Drawing.Size(321, 33)
        Me.lblVoltsRead.TabIndex = 5
        Me.lblVoltsRead.Text = "Converted Value: the channel number and the 12-bit value after separation of chan" & _
        "nel bits from data bits:"
        '
        '_lblShowRaw_9
        '
        Me._lblShowRaw_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_9.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_9.Location = New System.Drawing.Point(296, 112)
        Me._lblShowRaw_9.Name = "_lblShowRaw_9"
        Me._lblShowRaw_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_9.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_9.TabIndex = 15
        Me._lblShowRaw_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_8
        '
        Me._lblShowRaw_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_8.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_8.Location = New System.Drawing.Point(224, 112)
        Me._lblShowRaw_8.Name = "_lblShowRaw_8"
        Me._lblShowRaw_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_8.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_8.TabIndex = 14
        Me._lblShowRaw_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_7
        '
        Me._lblShowRaw_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_7.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_7.Location = New System.Drawing.Point(152, 112)
        Me._lblShowRaw_7.Name = "_lblShowRaw_7"
        Me._lblShowRaw_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_7.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_7.TabIndex = 13
        Me._lblShowRaw_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_6
        '
        Me._lblShowRaw_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_6.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_6.Location = New System.Drawing.Point(80, 112)
        Me._lblShowRaw_6.Name = "_lblShowRaw_6"
        Me._lblShowRaw_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_6.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_6.TabIndex = 12
        Me._lblShowRaw_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_5
        '
        Me._lblShowRaw_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_5.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_5.Location = New System.Drawing.Point(8, 112)
        Me._lblShowRaw_5.Name = "_lblShowRaw_5"
        Me._lblShowRaw_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_5.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_5.TabIndex = 11
        Me._lblShowRaw_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_4
        '
        Me._lblShowRaw_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_4.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_4.Location = New System.Drawing.Point(296, 88)
        Me._lblShowRaw_4.Name = "_lblShowRaw_4"
        Me._lblShowRaw_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_4.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_4.TabIndex = 10
        Me._lblShowRaw_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_3
        '
        Me._lblShowRaw_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_3.Location = New System.Drawing.Point(224, 88)
        Me._lblShowRaw_3.Name = "_lblShowRaw_3"
        Me._lblShowRaw_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_3.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_3.TabIndex = 9
        Me._lblShowRaw_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_2
        '
        Me._lblShowRaw_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_2.Location = New System.Drawing.Point(152, 88)
        Me._lblShowRaw_2.Name = "_lblShowRaw_2"
        Me._lblShowRaw_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_2.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_2.TabIndex = 8
        Me._lblShowRaw_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_1
        '
        Me._lblShowRaw_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_1.Location = New System.Drawing.Point(80, 88)
        Me._lblShowRaw_1.Name = "_lblShowRaw_1"
        Me._lblShowRaw_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_1.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_1.TabIndex = 7
        Me._lblShowRaw_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRaw_0
        '
        Me._lblShowRaw_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRaw_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRaw_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRaw_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRaw_0.Location = New System.Drawing.Point(8, 88)
        Me._lblShowRaw_0.Name = "_lblShowRaw_0"
        Me._lblShowRaw_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRaw_0.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRaw_0.TabIndex = 2
        Me._lblShowRaw_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblRawData
        '
        Me.lblRawData.BackColor = System.Drawing.SystemColors.Window
        Me.lblRawData.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblRawData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblRawData.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblRawData.Location = New System.Drawing.Point(8, 64)
        Me.lblRawData.Name = "lblRawData"
        Me.lblRawData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblRawData.Size = New System.Drawing.Size(265, 17)
        Me.lblRawData.TabIndex = 0
        Me.lblRawData.Text = "Value: the 16-bit integer read from the board:"
        '
        'lblStatus
        '
        Me.lblStatus.BackColor = System.Drawing.SystemColors.Window
        Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatus.ForeColor = System.Drawing.Color.Blue
        Me.lblStatus.Location = New System.Drawing.Point(16, 40)
        Me.lblStatus.Name = "lblStatus"
        Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatus.Size = New System.Drawing.Size(337, 17)
        Me.lblStatus.TabIndex = 25
        Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 8)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(382, 25)
        Me.lblDemoFunction.TabIndex = 1
        Me.lblDemoFunction.Text = "Demonstration of manual conversion of data"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AcceptButton = Me.cmdStartConvert
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(400, 299)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.txtHighChan, Me.cmdQuit, Me.cmdStartConvert, Me.cmdStopBackground, Me.lbl, Me._lblConvData_9, Me._lblConvData_8, Me._lblConvData_7, Me._lblConvData_6, Me._lblConvData_5, Me._lblConvData_4, Me._lblConvData_3, Me._lblConvData_2, Me._lblConvData_1, Me._lblConvData_0, Me.lblVoltsRead, Me._lblShowRaw_9, Me._lblShowRaw_8, Me._lblShowRaw_7, Me._lblShowRaw_6, Me._lblShowRaw_5, Me._lblShowRaw_4, Me._lblShowRaw_3, Me._lblShowRaw_2, Me._lblShowRaw_1, Me._lblShowRaw_0, Me.lblRawData, Me.lblStatus, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(155, 101)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Manual Conversion"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ULStat As MccDaq.ErrorInfo

        ' Note: Any change to label names requires a change to the corresponding array element
        lblConvData = (New System.Windows.Forms.Label() {Me._lblConvData_0, Me._lblConvData_1, Me._lblConvData_2, Me._lblConvData_3, Me._lblConvData_4, Me._lblConvData_5, Me._lblConvData_6, Me._lblConvData_7, Me._lblConvData_8, Me._lblConvData_9})

        lblShowRaw = (New System.Windows.Forms.Label() {Me._lblShowRaw_0, Me._lblShowRaw_1, Me._lblShowRaw_2, Me._lblShowRaw_3, Me._lblShowRaw_4, Me._lblShowRaw_5, Me._lblShowRaw_6, Me._lblShowRaw_7, Me._lblShowRaw_8, Me._lblShowRaw_9})


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

        MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

        UserTerm = 0

    End Sub

#End Region

End Class