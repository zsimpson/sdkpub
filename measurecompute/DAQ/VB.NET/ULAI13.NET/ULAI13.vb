'==============================================================================

' File:                         ULAI13.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AInScan(), sampling mode options.

' Purpose:                      Scans a range of A/D Input Channels and stores
'                               the sample data in an array using a user
'                               specified sampling mode.

' Demonstration:                Displays the analog input on up to 8 channels.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signals on up to 8 input channels.
'                               Board must support the mode selected.

'==========================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 2048 ' Number of data points to collect
    Const FirstPoint As Integer = 0 ' set first element in buffer to transfer to array

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ADData(NumPoints) As UInt16 ' dimension an array to hold the input values
    Dim MemHandle As Integer    ' define a variable to contain the handle for
    '                             memory allocated by Windows through MccDaq.MccServices.WinBufAlloc()
    Dim Options As MccDaq.ScanOptions ' define AInScan Options as Module level variable
    Dim HighChan As Integer

    Public lblADData As System.Windows.Forms.Label()

    Private Sub cmdStart_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStart.Click

        cmdStart.Visible = False
        cmdStopConvert.Visible = True
        tmrConvert.Enabled = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop ' other programs
        End

    End Sub

    Private Sub optDefault_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles optDefault.CheckedChanged
        If optDefault.Checked Then

            Options = MccDaq.ScanOptions.ConvertData

        End If
    End Sub

    Private Sub optModeBlock_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles optModeBlock.CheckedChanged
        If optModeBlock.Checked Then

            Options = MccDaq.ScanOptions.ConvertData Or MccDaq.ScanOptions.BlockIo

        End If
    End Sub

    Private Sub optModeDMA_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles optModeDMA.CheckedChanged
        If optModeDMA.Checked Then

            Options = MccDaq.ScanOptions.ConvertData Or MccDaq.ScanOptions.DmaIo

        End If
    End Sub

    Private Sub optModeSing_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles optModeSing.CheckedChanged
        If optModeSing.Checked Then

            Options = MccDaq.ScanOptions.ConvertData Or MccDaq.ScanOptions.SingleIo

        End If
    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim i As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim Range As MccDaq.Range
        Dim Rate As Integer
        Dim Count As Integer
        Dim LowChan As Integer

        tmrConvert.Stop()

        ' Collect the values with MccDaq.MccBoard.AInScan()
        '  Parameters:
        '    LowChan    :the first channel of the scan
        '    HighChan   :the last channel of the scan
        '    Count      :the total number of A/D samples to collect
        '    Rate       :sample rate
        '    Range      :the range for the board
        '    MemHandle  :Handle for Windows buffer to store data in
        '    Options    :data collection options (determined by
        '                Set Mode option buttons in this program)

        LowChan = 0                                 ' first channel to acquire
        HighChan = Integer.Parse(txtHighChan.Text) ' last channel to acquire
        If HighChan > 7 Then HighChan = 7
        txtHighChan.Text = Str(HighChan)

        Count = NumPoints ' total number of data points to collect
        Rate = 290 ' per channel sampling rate ((samples per second) per channel)
        Range = MccDaq.Range.Bip5Volts 'set the range

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.AInScan(LowChan, HighChan, Count, Rate, Range, MemHandle, Options)

        If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.FreeRunning Then
            ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.DontPrint, MccDaq.ErrorHandling.StopAll)
            'Turn off library error handling for subsequent calls
        ElseIf ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If

        ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

        ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        For i = 0 To HighChan
            lblADData(i).Text = ADData(i).ToString("0")
        Next i
        
        tmrConvert.Start()

    End Sub

    Private Sub txtHighChan_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtHighChan.TextChanged

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
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents cmdStart As System.Windows.Forms.Button
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
    Public WithEvents optModeBlock As System.Windows.Forms.RadioButton
    Public WithEvents optModeDMA As System.Windows.Forms.RadioButton
    Public WithEvents optModeSing As System.Windows.Forms.RadioButton
    Public WithEvents optDefault As System.Windows.Forms.RadioButton
    Public WithEvents fraMode As System.Windows.Forms.GroupBox
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents _lblADData_7 As System.Windows.Forms.Label
    Public WithEvents lblChan7 As System.Windows.Forms.Label
    Public WithEvents _lblADData_3 As System.Windows.Forms.Label
    Public WithEvents lblChan3 As System.Windows.Forms.Label
    Public WithEvents _lblADData_6 As System.Windows.Forms.Label
    Public WithEvents lblChan6 As System.Windows.Forms.Label
    Public WithEvents _lblADData_2 As System.Windows.Forms.Label
    Public WithEvents lblChan2 As System.Windows.Forms.Label
    Public WithEvents _lblADData_5 As System.Windows.Forms.Label
    Public WithEvents lblChan5 As System.Windows.Forms.Label
    Public WithEvents _lblADData_1 As System.Windows.Forms.Label
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents _lblADData_4 As System.Windows.Forms.Label
    Public WithEvents lblChan4 As System.Windows.Forms.Label
    Public WithEvents _lblADData_0 As System.Windows.Forms.Label
    Public WithEvents lblChan0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.txtHighChan = New System.Windows.Forms.TextBox()
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdStart = New System.Windows.Forms.Button()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
        Me.fraMode = New System.Windows.Forms.GroupBox()
        Me.optModeBlock = New System.Windows.Forms.RadioButton()
        Me.optModeDMA = New System.Windows.Forms.RadioButton()
        Me.optModeSing = New System.Windows.Forms.RadioButton()
        Me.optDefault = New System.Windows.Forms.RadioButton()
        Me.Label1 = New System.Windows.Forms.Label()
        Me._lblADData_7 = New System.Windows.Forms.Label()
        Me.lblChan7 = New System.Windows.Forms.Label()
        Me._lblADData_3 = New System.Windows.Forms.Label()
        Me.lblChan3 = New System.Windows.Forms.Label()
        Me._lblADData_6 = New System.Windows.Forms.Label()
        Me.lblChan6 = New System.Windows.Forms.Label()
        Me._lblADData_2 = New System.Windows.Forms.Label()
        Me.lblChan2 = New System.Windows.Forms.Label()
        Me._lblADData_5 = New System.Windows.Forms.Label()
        Me.lblChan5 = New System.Windows.Forms.Label()
        Me._lblADData_1 = New System.Windows.Forms.Label()
        Me.lblChan1 = New System.Windows.Forms.Label()
        Me._lblADData_4 = New System.Windows.Forms.Label()
        Me.lblChan4 = New System.Windows.Forms.Label()
        Me._lblADData_0 = New System.Windows.Forms.Label()
        Me.lblChan0 = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.fraMode.SuspendLayout()
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
        Me.txtHighChan.Location = New System.Drawing.Point(192, 176)
        Me.txtHighChan.MaxLength = 0
        Me.txtHighChan.Name = "txtHighChan"
        Me.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtHighChan.Size = New System.Drawing.Size(25, 19)
        Me.txtHighChan.TabIndex = 25
        Me.txtHighChan.Text = "3"
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(272, 272)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(50, 26)
        Me.cmdStopConvert.TabIndex = 17
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Visible = False
        '
        'cmdStart
        '
        Me.cmdStart.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStart.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStart.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStart.Location = New System.Drawing.Point(272, 272)
        Me.cmdStart.Name = "cmdStart"
        Me.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStart.Size = New System.Drawing.Size(50, 26)
        Me.cmdStart.TabIndex = 23
        Me.cmdStart.Text = "Start"
        '
        'tmrConvert
        '
        Me.tmrConvert.Interval = 500
        '
        'fraMode
        '
        Me.fraMode.BackColor = System.Drawing.SystemColors.Window
        Me.fraMode.Controls.AddRange(New System.Windows.Forms.Control() {Me.optModeBlock, Me.optModeDMA, Me.optModeSing, Me.optDefault})
        Me.fraMode.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.fraMode.ForeColor = System.Drawing.SystemColors.WindowText
        Me.fraMode.Location = New System.Drawing.Point(117, 56)
        Me.fraMode.Name = "fraMode"
        Me.fraMode.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fraMode.Size = New System.Drawing.Size(104, 112)
        Me.fraMode.TabIndex = 18
        Me.fraMode.TabStop = False
        Me.fraMode.Text = "Select Mode"
        '
        'optModeBlock
        '
        Me.optModeBlock.BackColor = System.Drawing.SystemColors.Window
        Me.optModeBlock.Cursor = System.Windows.Forms.Cursors.Default
        Me.optModeBlock.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.optModeBlock.ForeColor = System.Drawing.SystemColors.WindowText
        Me.optModeBlock.Location = New System.Drawing.Point(13, 84)
        Me.optModeBlock.Name = "optModeBlock"
        Me.optModeBlock.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.optModeBlock.Size = New System.Drawing.Size(84, 20)
        Me.optModeBlock.TabIndex = 21
        Me.optModeBlock.TabStop = True
        Me.optModeBlock.Text = "Block IO"
        '
        'optModeDMA
        '
        Me.optModeDMA.BackColor = System.Drawing.SystemColors.Window
        Me.optModeDMA.Cursor = System.Windows.Forms.Cursors.Default
        Me.optModeDMA.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.optModeDMA.ForeColor = System.Drawing.SystemColors.WindowText
        Me.optModeDMA.Location = New System.Drawing.Point(13, 64)
        Me.optModeDMA.Name = "optModeDMA"
        Me.optModeDMA.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.optModeDMA.Size = New System.Drawing.Size(84, 20)
        Me.optModeDMA.TabIndex = 20
        Me.optModeDMA.TabStop = True
        Me.optModeDMA.Text = "DMA IO"
        '
        'optModeSing
        '
        Me.optModeSing.BackColor = System.Drawing.SystemColors.Window
        Me.optModeSing.Cursor = System.Windows.Forms.Cursors.Default
        Me.optModeSing.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.optModeSing.ForeColor = System.Drawing.SystemColors.WindowText
        Me.optModeSing.Location = New System.Drawing.Point(13, 45)
        Me.optModeSing.Name = "optModeSing"
        Me.optModeSing.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.optModeSing.Size = New System.Drawing.Size(84, 20)
        Me.optModeSing.TabIndex = 19
        Me.optModeSing.TabStop = True
        Me.optModeSing.Text = "Single IO"
        '
        'optDefault
        '
        Me.optDefault.BackColor = System.Drawing.SystemColors.Window
        Me.optDefault.Checked = True
        Me.optDefault.Cursor = System.Windows.Forms.Cursors.Default
        Me.optDefault.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.optDefault.ForeColor = System.Drawing.SystemColors.WindowText
        Me.optDefault.Location = New System.Drawing.Point(13, 26)
        Me.optDefault.Name = "optDefault"
        Me.optDefault.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.optDefault.Size = New System.Drawing.Size(84, 20)
        Me.optDefault.TabIndex = 22
        Me.optDefault.TabStop = True
        Me.optDefault.Text = "Default"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Window
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Label1.Location = New System.Drawing.Point(64, 177)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(128, 16)
        Me.Label1.TabIndex = 24
        Me.Label1.Text = "Measure Channels 0 to "
        '
        '_lblADData_7
        '
        Me._lblADData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_7.Location = New System.Drawing.Point(264, 246)
        Me._lblADData_7.Name = "_lblADData_7"
        Me._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_7.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_7.TabIndex = 16
        '
        'lblChan7
        '
        Me.lblChan7.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan7.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan7.Location = New System.Drawing.Point(192, 246)
        Me.lblChan7.Name = "lblChan7"
        Me.lblChan7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan7.Size = New System.Drawing.Size(65, 17)
        Me.lblChan7.TabIndex = 8
        Me.lblChan7.Text = "Channel 7:"
        '
        '_lblADData_3
        '
        Me._lblADData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_3.Location = New System.Drawing.Point(96, 246)
        Me._lblADData_3.Name = "_lblADData_3"
        Me._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_3.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_3.TabIndex = 12
        '
        'lblChan3
        '
        Me.lblChan3.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan3.Location = New System.Drawing.Point(24, 246)
        Me.lblChan3.Name = "lblChan3"
        Me.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan3.Size = New System.Drawing.Size(65, 17)
        Me.lblChan3.TabIndex = 4
        Me.lblChan3.Text = "Channel 3:"
        '
        '_lblADData_6
        '
        Me._lblADData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_6.Location = New System.Drawing.Point(264, 230)
        Me._lblADData_6.Name = "_lblADData_6"
        Me._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_6.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_6.TabIndex = 15
        '
        'lblChan6
        '
        Me.lblChan6.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan6.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan6.Location = New System.Drawing.Point(192, 230)
        Me.lblChan6.Name = "lblChan6"
        Me.lblChan6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan6.Size = New System.Drawing.Size(65, 17)
        Me.lblChan6.TabIndex = 7
        Me.lblChan6.Text = "Channel 6:"
        '
        '_lblADData_2
        '
        Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_2.Location = New System.Drawing.Point(96, 230)
        Me._lblADData_2.Name = "_lblADData_2"
        Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_2.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_2.TabIndex = 11
        '
        'lblChan2
        '
        Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan2.Location = New System.Drawing.Point(24, 230)
        Me.lblChan2.Name = "lblChan2"
        Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan2.Size = New System.Drawing.Size(65, 17)
        Me.lblChan2.TabIndex = 3
        Me.lblChan2.Text = "Channel 2:"
        '
        '_lblADData_5
        '
        Me._lblADData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_5.Location = New System.Drawing.Point(264, 214)
        Me._lblADData_5.Name = "_lblADData_5"
        Me._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_5.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_5.TabIndex = 14
        '
        'lblChan5
        '
        Me.lblChan5.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan5.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan5.Location = New System.Drawing.Point(192, 214)
        Me.lblChan5.Name = "lblChan5"
        Me.lblChan5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan5.Size = New System.Drawing.Size(65, 17)
        Me.lblChan5.TabIndex = 6
        Me.lblChan5.Text = "Channel 5:"
        '
        '_lblADData_1
        '
        Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_1.Location = New System.Drawing.Point(96, 214)
        Me._lblADData_1.Name = "_lblADData_1"
        Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_1.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_1.TabIndex = 10
        '
        'lblChan1
        '
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan1.Location = New System.Drawing.Point(24, 214)
        Me.lblChan1.Name = "lblChan1"
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.Size = New System.Drawing.Size(65, 17)
        Me.lblChan1.TabIndex = 2
        Me.lblChan1.Text = "Channel 1:"
        '
        '_lblADData_4
        '
        Me._lblADData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_4.Location = New System.Drawing.Point(264, 198)
        Me._lblADData_4.Name = "_lblADData_4"
        Me._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_4.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_4.TabIndex = 13
        '
        'lblChan4
        '
        Me.lblChan4.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan4.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan4.Location = New System.Drawing.Point(192, 198)
        Me.lblChan4.Name = "lblChan4"
        Me.lblChan4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan4.Size = New System.Drawing.Size(65, 17)
        Me.lblChan4.TabIndex = 5
        Me.lblChan4.Text = "Channel 4:"
        '
        '_lblADData_0
        '
        Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_0.Location = New System.Drawing.Point(96, 198)
        Me._lblADData_0.Name = "_lblADData_0"
        Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_0.Size = New System.Drawing.Size(46, 17)
        Me._lblADData_0.TabIndex = 9
        '
        'lblChan0
        '
        Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan0.Location = New System.Drawing.Point(24, 198)
        Me.lblChan0.Name = "lblChan0"
        Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0.Size = New System.Drawing.Size(65, 17)
        Me.lblChan0.TabIndex = 1
        Me.lblChan0.Text = "Channel 0:"
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(13, 13)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(313, 41)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AInScan() with user selected scan mode"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(339, 315)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.txtHighChan, Me.cmdStopConvert, Me.cmdStart, Me.fraMode, Me.Label1, Me._lblADData_7, Me.lblChan7, Me._lblADData_3, Me.lblChan3, Me._lblADData_6, Me.lblChan6, Me._lblADData_2, Me.lblChan2, Me._lblADData_5, Me.lblChan5, Me._lblADData_1, Me.lblChan1, Me._lblADData_4, Me.lblChan4, Me._lblADData_0, Me.lblChan0, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(144, 131)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Input Scan"
        Me.fraMode.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        lblADData = New System.Windows.Forms.Label(8) {}

        Me.lblADData.SetValue(_lblADData_7, 7)
        Me.lblADData.SetValue(_lblADData_3, 3)
        Me.lblADData.SetValue(_lblADData_6, 6)
        Me.lblADData.SetValue(_lblADData_2, 2)
        Me.lblADData.SetValue(_lblADData_5, 5)
        Me.lblADData.SetValue(_lblADData_1, 1)
        Me.lblADData.SetValue(_lblADData_4, 4)
        Me.lblADData.SetValue(_lblADData_0, 0)


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

        Options = MccDaq.ScanOptions.ConvertData


    End Sub
#End Region

End Class