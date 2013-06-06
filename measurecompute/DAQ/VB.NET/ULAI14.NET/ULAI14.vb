'==============================================================================

' File:                         ULAI14.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.SetTrigger()

' Purpose:                      Selects the Trigger source. This trigger is
'                               used to initiate A/D conversion using
'                               Mccdaq.MccBoard.AInScan(), with 
'                               MccDaq.ScanOptions.ExtTrigger Option.

' Demonstration:                Selects the trigger source
'                               Displays the analog input on up to eight channels.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have software selectable
'                               triggering source and type.
'                               Board 0 must have an A/D converter.
'                               Analog signals on up to eight input channels.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 600 ' Number of data points to collect
    Const FirstPoint As Integer = 0 ' set first element in buffer to transfer to array

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ADData(NumPoints) As UInt16 ' dimension an array to hold the input values
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
    Dim HighChan As Integer

    Public lblADData As System.Windows.Forms.Label()

    Private Sub cmdStart_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStart.Click
        Dim j As Integer
        Dim i As Integer
        Dim Options As MccDaq.ScanOptions
        Dim Rate As Integer
        Dim Count As Integer
        Dim LowChan As Integer
        Dim TrigType As MccDaq.TriggerType
        Dim LowThreshold As UInt16
        Dim ULStat As MccDaq.ErrorInfo
        Dim HighThreshold As UInt16
        Dim Range As MccDaq.Range
        Dim highVal As Single 'high threshold in volts
        Dim lowVal As Single 'low threshold in volts

        cmdStart.Enabled = False


        ' Select the trigger source using Mccdaq.MccBoard.SetTrigger()
        ' Parameters:
        '   TrigType       :the type of triggering based on external trigger source
        '   LowThreshold   :Low threshold when the trigger input is analog
        '   HighThreshold  :High threshold when the trigger input is analog

        highVal = 1.0#
        Range = MccDaq.Range.Bip10Volts 'analog trigger range
        ULStat = DaqBoard.FromEngUnits(Range, highVal, HighThreshold)
        lowVal = 0.1
        ULStat = DaqBoard.FromEngUnits(Range, lowVal, LowThreshold)
        TrigType = MccDaq.TriggerType.TrigAbove


        ULStat = DaqBoard.SetTrigger(TrigType, LowThreshold, HighThreshold)
        If (ULStat.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            ' Collect the values with MccDaq.MccBoard.AInScan()
            ' Parameters:
            '   LowChan    :the first channel of the scan
            '   HighChan   :the last channel of the scan
            '   Count      :the total number of A/D samples to collect
            '   Rate       :sample rate
            '   Range      :the range for the board
            '   MemHandle  :Handle for Windows buffer to store data in
            '   Options    :data collection options

            LowChan = 0 ' first channel to acquire
            HighChan = Integer.Parse(txtHighChan.Text) ' last channel to acquire
            If HighChan > 7 Then HighChan = 7
            txtHighChan.Text = Str(HighChan)

            Count = NumPoints ' total number of data points to collect
            Rate = 390 ' per channel sampling rate ((samples per second) per channel)
            Range = MccDaq.Range.Bip5Volts 'set the range
            Options = MccDaq.ScanOptions.ConvertData Or MccDaq.ScanOptions.ExtTrigger ' return data as 12-bit values


            If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

            ULStat = DaqBoard.AInScan(LowChan, HighChan, Count, Rate, Range, MemHandle, Options)

            If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadRange Then MsgBox("Change the Range argument to one supported by this board.", 0, "Unsupported Range")
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors And ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.FreeRunning Then Stop

            ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

            ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, Count)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            For i = 0 To HighChan
                lblADData(i).Text = ADData(i).ToString("0")
            Next i

            For j = HighChan + 1 To 7
                lblADData(j).Text = ""
            Next j
        End If

        cmdStart.Enabled = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop ' other programs

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
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents cmdStart As System.Windows.Forms.Button
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
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmDataDisplay))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.txtHighChan = New System.Windows.Forms.TextBox()
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdStart = New System.Windows.Forms.Button()
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
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library Analog Input Scan"
        Me.ClientSize = New System.Drawing.Size(349, 232)
        Me.Location = New System.Drawing.Point(189, 104)
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable
        Me.ControlBox = True
        Me.Enabled = True
        Me.KeyPreview = False
        Me.MaximizeBox = True
        Me.MinimizeBox = True
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ShowInTaskbar = True
        Me.HelpButton = False
        Me.WindowState = System.Windows.Forms.FormWindowState.Normal
        Me.Name = "frmDataDisplay"
        Me.txtHighChan.AutoSize = False
        Me.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        Me.txtHighChan.Size = New System.Drawing.Size(25, 19)
        Me.txtHighChan.Location = New System.Drawing.Point(216, 66)
        Me.txtHighChan.TabIndex = 20
        Me.txtHighChan.Text = "3"
        Me.txtHighChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtHighChan.AcceptsReturn = True
        Me.txtHighChan.BackColor = System.Drawing.SystemColors.Window
        Me.txtHighChan.CausesValidation = True
        Me.txtHighChan.Enabled = True
        Me.txtHighChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtHighChan.HideSelection = True
        Me.txtHighChan.ReadOnly = False
        Me.txtHighChan.MaxLength = 0
        Me.txtHighChan.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtHighChan.Multiline = False
        Me.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtHighChan.ScrollBars = System.Windows.Forms.ScrollBars.None
        Me.txtHighChan.TabStop = True
        Me.txtHighChan.Visible = True
        Me.txtHighChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtHighChan.Name = "txtHighChan"
        Me.cmdStopConvert.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Size = New System.Drawing.Size(58, 26)
        Me.cmdStopConvert.Location = New System.Drawing.Point(280, 192)
        Me.cmdStopConvert.TabIndex = 17
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.CausesValidation = True
        Me.cmdStopConvert.Enabled = True
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.TabStop = True
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStart.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStart.Text = "Start"
        Me.cmdStart.Size = New System.Drawing.Size(58, 26)
        Me.cmdStart.Location = New System.Drawing.Point(208, 192)
        Me.cmdStart.TabIndex = 18
        Me.cmdStart.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStart.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStart.CausesValidation = True
        Me.cmdStart.Enabled = True
        Me.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStart.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStart.TabStop = True
        Me.cmdStart.Name = "cmdStart"
        Me.Label1.BackColor = System.Drawing.SystemColors.Window
        Me.Label1.Text = "Measure Channels 0 to "
        Me.Label1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Label1.Size = New System.Drawing.Size(137, 16)
        Me.Label1.Location = New System.Drawing.Point(72, 66)
        Me.Label1.TabIndex = 19
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.Label1.Enabled = True
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.UseMnemonic = True
        Me.Label1.Visible = True
        Me.Label1.AutoSize = False
        Me.Label1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label1.Name = "Label1"
        Me._lblADData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_7.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_7.Location = New System.Drawing.Point(264, 170)
        Me._lblADData_7.TabIndex = 16
        Me._lblADData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_7.Enabled = True
        Me._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_7.UseMnemonic = True
        Me._lblADData_7.Visible = True
        Me._lblADData_7.AutoSize = False
        Me._lblADData_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_7.Name = "_lblADData_7"
        Me.lblChan7.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan7.Text = "Channel 7:"
        Me.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan7.Size = New System.Drawing.Size(65, 17)
        Me.lblChan7.Location = New System.Drawing.Point(192, 170)
        Me.lblChan7.TabIndex = 8
        Me.lblChan7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan7.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan7.Enabled = True
        Me.lblChan7.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan7.UseMnemonic = True
        Me.lblChan7.Visible = True
        Me.lblChan7.AutoSize = False
        Me.lblChan7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan7.Name = "lblChan7"
        Me._lblADData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_3.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_3.Location = New System.Drawing.Point(96, 170)
        Me._lblADData_3.TabIndex = 12
        Me._lblADData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_3.Enabled = True
        Me._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_3.UseMnemonic = True
        Me._lblADData_3.Visible = True
        Me._lblADData_3.AutoSize = False
        Me._lblADData_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_3.Name = "_lblADData_3"
        Me.lblChan3.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan3.Text = "Channel 3:"
        Me.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan3.Size = New System.Drawing.Size(65, 17)
        Me.lblChan3.Location = New System.Drawing.Point(24, 170)
        Me.lblChan3.TabIndex = 4
        Me.lblChan3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan3.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan3.Enabled = True
        Me.lblChan3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan3.UseMnemonic = True
        Me.lblChan3.Visible = True
        Me.lblChan3.AutoSize = False
        Me.lblChan3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan3.Name = "lblChan3"
        Me._lblADData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_6.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_6.Location = New System.Drawing.Point(264, 145)
        Me._lblADData_6.TabIndex = 15
        Me._lblADData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_6.Enabled = True
        Me._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_6.UseMnemonic = True
        Me._lblADData_6.Visible = True
        Me._lblADData_6.AutoSize = False
        Me._lblADData_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_6.Name = "_lblADData_6"
        Me.lblChan6.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan6.Text = "Channel 6:"
        Me.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan6.Size = New System.Drawing.Size(65, 17)
        Me.lblChan6.Location = New System.Drawing.Point(192, 145)
        Me.lblChan6.TabIndex = 7
        Me.lblChan6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan6.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan6.Enabled = True
        Me.lblChan6.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan6.UseMnemonic = True
        Me.lblChan6.Visible = True
        Me.lblChan6.AutoSize = False
        Me.lblChan6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan6.Name = "lblChan6"
        Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_2.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_2.Location = New System.Drawing.Point(96, 145)
        Me._lblADData_2.TabIndex = 11
        Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_2.Enabled = True
        Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_2.UseMnemonic = True
        Me._lblADData_2.Visible = True
        Me._lblADData_2.AutoSize = False
        Me._lblADData_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_2.Name = "_lblADData_2"
        Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan2.Text = "Channel 2:"
        Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan2.Size = New System.Drawing.Size(65, 17)
        Me.lblChan2.Location = New System.Drawing.Point(24, 145)
        Me.lblChan2.TabIndex = 3
        Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan2.Enabled = True
        Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan2.UseMnemonic = True
        Me.lblChan2.Visible = True
        Me.lblChan2.AutoSize = False
        Me.lblChan2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan2.Name = "lblChan2"
        Me._lblADData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_5.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_5.Location = New System.Drawing.Point(264, 119)
        Me._lblADData_5.TabIndex = 14
        Me._lblADData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_5.Enabled = True
        Me._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_5.UseMnemonic = True
        Me._lblADData_5.Visible = True
        Me._lblADData_5.AutoSize = False
        Me._lblADData_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_5.Name = "_lblADData_5"
        Me.lblChan5.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan5.Text = "Channel 5:"
        Me.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan5.Size = New System.Drawing.Size(65, 17)
        Me.lblChan5.Location = New System.Drawing.Point(192, 119)
        Me.lblChan5.TabIndex = 6
        Me.lblChan5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan5.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan5.Enabled = True
        Me.lblChan5.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan5.UseMnemonic = True
        Me.lblChan5.Visible = True
        Me.lblChan5.AutoSize = False
        Me.lblChan5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan5.Name = "lblChan5"
        Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_1.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_1.Location = New System.Drawing.Point(96, 119)
        Me._lblADData_1.TabIndex = 10
        Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_1.Enabled = True
        Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_1.UseMnemonic = True
        Me._lblADData_1.Visible = True
        Me._lblADData_1.AutoSize = False
        Me._lblADData_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_1.Name = "_lblADData_1"
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Text = "Channel 1:"
        Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan1.Size = New System.Drawing.Size(65, 17)
        Me.lblChan1.Location = New System.Drawing.Point(24, 119)
        Me.lblChan1.TabIndex = 2
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan1.Enabled = True
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.UseMnemonic = True
        Me.lblChan1.Visible = True
        Me.lblChan1.AutoSize = False
        Me.lblChan1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan1.Name = "lblChan1"
        Me._lblADData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_4.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_4.Location = New System.Drawing.Point(264, 94)
        Me._lblADData_4.TabIndex = 13
        Me._lblADData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_4.Enabled = True
        Me._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_4.UseMnemonic = True
        Me._lblADData_4.Visible = True
        Me._lblADData_4.AutoSize = False
        Me._lblADData_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_4.Name = "_lblADData_4"
        Me.lblChan4.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan4.Text = "Channel 4:"
        Me.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan4.Size = New System.Drawing.Size(65, 17)
        Me.lblChan4.Location = New System.Drawing.Point(192, 94)
        Me.lblChan4.TabIndex = 5
        Me.lblChan4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan4.Enabled = True
        Me.lblChan4.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan4.UseMnemonic = True
        Me.lblChan4.Visible = True
        Me.lblChan4.AutoSize = False
        Me.lblChan4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan4.Name = "lblChan4"
        Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_0.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_0.Location = New System.Drawing.Point(96, 94)
        Me._lblADData_0.TabIndex = 9
        Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblADData_0.Enabled = True
        Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_0.UseMnemonic = True
        Me._lblADData_0.Visible = True
        Me._lblADData_0.AutoSize = False
        Me._lblADData_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblADData_0.Name = "_lblADData_0"
        Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0.Text = "Channel 0:"
        Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan0.Size = New System.Drawing.Size(65, 17)
        Me.lblChan0.Location = New System.Drawing.Point(24, 94)
        Me.lblChan0.TabIndex = 1
        Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblChan0.Enabled = True
        Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0.UseMnemonic = True
        Me.lblChan0.Visible = True
        Me.lblChan0.AutoSize = False
        Me.lblChan0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblChan0.Name = "lblChan0"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.SetTrigger() "
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(337, 41)
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 8)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.Enabled = True
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.UseMnemonic = True
        Me.lblDemoFunction.Visible = True
        Me.lblDemoFunction.AutoSize = False
        Me.lblDemoFunction.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.Controls.Add(txtHighChan)
        Me.Controls.Add(cmdStopConvert)
        Me.Controls.Add(cmdStart)
        Me.Controls.Add(Label1)
        Me.Controls.Add(_lblADData_7)
        Me.Controls.Add(lblChan7)
        Me.Controls.Add(_lblADData_3)
        Me.Controls.Add(lblChan3)
        Me.Controls.Add(_lblADData_6)
        Me.Controls.Add(lblChan6)
        Me.Controls.Add(_lblADData_2)
        Me.Controls.Add(lblChan2)
        Me.Controls.Add(_lblADData_5)
        Me.Controls.Add(lblChan5)
        Me.Controls.Add(_lblADData_1)
        Me.Controls.Add(lblChan1)
        Me.Controls.Add(_lblADData_4)
        Me.Controls.Add(lblChan4)
        Me.Controls.Add(_lblADData_0)
        Me.Controls.Add(lblChan0)
        Me.Controls.Add(lblDemoFunction)

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

    End Sub
#End Region
End Class