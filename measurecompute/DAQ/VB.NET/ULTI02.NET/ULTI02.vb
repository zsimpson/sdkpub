'==============================================================================

' File:                         ULTI02.VB

' Library Call Demonstrated:    MccDaq.MccBoard.TInScan()

' Purpose:                      Scans multiplexor input channels.

' Demonstration:                Displays the temperature inputs on a
'                               range of channels.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Unless the board at BoardNum(=0) does not use
'                               EXP boards for temperature measurements(the
'                               CIO-DAS-TC,for example), it must
'                               have an A/D converter with an attached EXP
'                               board.  Thermocouples must be wired to EXP
'                               channels selected.
'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)


    Public lblShowData As System.Windows.Forms.Label()

    Dim UsesEXPs As Integer
    Dim DataBuffer(16) As Single ' dimension an array to hold
    ' the temperatures

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click

        cmdStartConvert.Visible = False
        cmdStopConvert.Visible = True
        tmrConvert.Enabled = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        End

    End Sub

    Private Sub hsbHiChan_Change(ByVal newScrollValue As Integer)

        If newScrollValue < hsbLoChan.Value Then
            hsbLoChan.Value = newScrollValue
            lblLoChan.Text = newScrollValue.ToString("0")
        End If

        lblHiChan.Text = newScrollValue.ToString("0")

    End Sub

    Private Sub hsbLoChan_Change(ByVal newScrollValue As Integer)

        If hsbHiChan.Value < newScrollValue Then
            hsbHiChan.Value = newScrollValue
            lblHiChan.Text = newScrollValue.ToString("0")
        End If

        lblLoChan.Text = newScrollValue.ToString("0")

    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim i As Integer
        Dim Element As Integer
        Dim j As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim HighChan As Integer
        Dim LowChan As Integer
        Dim Options As MccDaq.ThermocoupleOptions
        Dim HighMux As Integer
        Dim LowMux As Integer
        Dim ADChan As Integer
        Dim AvgCount As Short
        Dim MccScale As MccDaq.TempScale

        ' Collect the data with MccDaq.MccBoard.TInScan()
        '  Input values will be collected from a range of thermocouples.
        '  The data value will be updated and displayed until a key is pressed.
        '  Parameters:
        '    LowChan       :the starting channel of the scan
        '    HighChan      :the ending channel of the scan
        '    MccScale       :temperature scale (Celsius, Fahrenheit, Kelvin)
        '    AvgCount      :the number of samples to average to reduce noise
        '    DataBuffer!()  :the array where the temperature values are collected

        MccScale = MccDaq.TempScale.Fahrenheit
        AvgCount = 50
        ADChan = 0 'the channel on the A/D

        LowMux = hsbLoChan.Value
        HighMux = hsbHiChan.Value
        Options = 0
        If UsesEXPs > 0 Then
            LowChan = (ADChan + 1) * 16 + LowMux
            HighChan = (ADChan + 1) * 16 + HighMux
        Else
            LowChan = LowMux
            HighChan = HighMux
        End If

        tmrConvert.Stop()

        ULStat = DaqBoard.TInScan(LowChan, HighChan, MccScale, DataBuffer(0), Options)
        ' If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        If LowMux <> 0 Then
            For j = 0 To LowMux - 1
                lblShowData(j).Text = ""
            Next j
        End If
        If HighMux <> 15 Then
            For j = HighMux + 1 To 15
                lblShowData(j).Text = ""
            Next j
        End If

        Element = 0

        For i = LowMux To HighMux
            lblShowData(i).Text = DataBuffer(Element).ToString("0") + "°F" ' print the value
            Element = Element + 1
        Next i
        
        tmrConvert.Start()

    End Sub
    Private Sub hsbHiChan_Scroll(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.ScrollEventArgs) Handles hsbHiChan.Scroll
        Select Case eventArgs.Type
            Case System.Windows.Forms.ScrollEventType.EndScroll
                hsbHiChan_Change(eventArgs.NewValue)
        End Select
    End Sub
    Private Sub hsbLoChan_Scroll(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.ScrollEventArgs) Handles hsbLoChan.Scroll
        Select Case eventArgs.Type
            Case System.Windows.Forms.ScrollEventType.EndScroll
                hsbLoChan_Change(eventArgs.NewValue)
        End Select
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
    Public WithEvents cmdStartConvert As System.Windows.Forms.Button
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents hsbHiChan As System.Windows.Forms.HScrollBar
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
    Public WithEvents hsbLoChan As System.Windows.Forms.HScrollBar
    Public WithEvents _lblShowData_15 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_15 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_7 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_7 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_14 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_14 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_6 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_6 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_13 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_13 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_5 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_5 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_12 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_12 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_4 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_4 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_11 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_11 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_3 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_3 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_10 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_10 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_2 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_2 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_9 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_9 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_1 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_1 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_8 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_8 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_0 As System.Windows.Forms.Label
    Public WithEvents _lblChanNum_0 As System.Windows.Forms.Label
    Public WithEvents lblTemp2 As System.Windows.Forms.Label
    Public WithEvents lblChan2 As System.Windows.Forms.Label
    Public WithEvents lblTemp1 As System.Windows.Forms.Label
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents lblLastChan As System.Windows.Forms.Label
    Public WithEvents lblHiChan As System.Windows.Forms.Label
    Public WithEvents lblFirstChan As System.Windows.Forms.Label
    Public WithEvents lblLoChan As System.Windows.Forms.Label
    Public WithEvents lblChanPrompt As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.hsbHiChan = New System.Windows.Forms.HScrollBar()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
        Me.hsbLoChan = New System.Windows.Forms.HScrollBar()
        Me._lblShowData_15 = New System.Windows.Forms.Label()
        Me._lblChanNum_15 = New System.Windows.Forms.Label()
        Me._lblShowData_7 = New System.Windows.Forms.Label()
        Me._lblChanNum_7 = New System.Windows.Forms.Label()
        Me._lblShowData_14 = New System.Windows.Forms.Label()
        Me._lblChanNum_14 = New System.Windows.Forms.Label()
        Me._lblShowData_6 = New System.Windows.Forms.Label()
        Me._lblChanNum_6 = New System.Windows.Forms.Label()
        Me._lblShowData_13 = New System.Windows.Forms.Label()
        Me._lblChanNum_13 = New System.Windows.Forms.Label()
        Me._lblShowData_5 = New System.Windows.Forms.Label()
        Me._lblChanNum_5 = New System.Windows.Forms.Label()
        Me._lblShowData_12 = New System.Windows.Forms.Label()
        Me._lblChanNum_12 = New System.Windows.Forms.Label()
        Me._lblShowData_4 = New System.Windows.Forms.Label()
        Me._lblChanNum_4 = New System.Windows.Forms.Label()
        Me._lblShowData_11 = New System.Windows.Forms.Label()
        Me._lblChanNum_11 = New System.Windows.Forms.Label()
        Me._lblShowData_3 = New System.Windows.Forms.Label()
        Me._lblChanNum_3 = New System.Windows.Forms.Label()
        Me._lblShowData_10 = New System.Windows.Forms.Label()
        Me._lblChanNum_10 = New System.Windows.Forms.Label()
        Me._lblShowData_2 = New System.Windows.Forms.Label()
        Me._lblChanNum_2 = New System.Windows.Forms.Label()
        Me._lblShowData_9 = New System.Windows.Forms.Label()
        Me._lblChanNum_9 = New System.Windows.Forms.Label()
        Me._lblShowData_1 = New System.Windows.Forms.Label()
        Me._lblChanNum_1 = New System.Windows.Forms.Label()
        Me._lblShowData_8 = New System.Windows.Forms.Label()
        Me._lblChanNum_8 = New System.Windows.Forms.Label()
        Me._lblShowData_0 = New System.Windows.Forms.Label()
        Me._lblChanNum_0 = New System.Windows.Forms.Label()
        Me.lblTemp2 = New System.Windows.Forms.Label()
        Me.lblChan2 = New System.Windows.Forms.Label()
        Me.lblTemp1 = New System.Windows.Forms.Label()
        Me.lblChan1 = New System.Windows.Forms.Label()
        Me.lblLastChan = New System.Windows.Forms.Label()
        Me.lblHiChan = New System.Windows.Forms.Label()
        Me.lblFirstChan = New System.Windows.Forms.Label()
        Me.lblLoChan = New System.Windows.Forms.Label()
        Me.lblChanPrompt = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(304, 312)
        Me.cmdStartConvert.Name = "cmdStartConvert"
        Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartConvert.Size = New System.Drawing.Size(57, 25)
        Me.cmdStartConvert.TabIndex = 3
        Me.cmdStartConvert.Text = "Start"
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(304, 312)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(57, 25)
        Me.cmdStopConvert.TabIndex = 4
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Visible = False
        '
        'hsbHiChan
        '
        Me.hsbHiChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.hsbHiChan.LargeChange = 1
        Me.hsbHiChan.Location = New System.Drawing.Point(32, 88)
        Me.hsbHiChan.Maximum = 15
        Me.hsbHiChan.Name = "hsbHiChan"
        Me.hsbHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.hsbHiChan.Size = New System.Drawing.Size(169, 17)
        Me.hsbHiChan.TabIndex = 6
        Me.hsbHiChan.TabStop = True
        '
        'tmrConvert
        '
        Me.tmrConvert.Interval = 250
        '
        'hsbLoChan
        '
        Me.hsbLoChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.hsbLoChan.LargeChange = 1
        Me.hsbLoChan.Location = New System.Drawing.Point(32, 64)
        Me.hsbLoChan.Maximum = 15
        Me.hsbLoChan.Name = "hsbLoChan"
        Me.hsbLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.hsbLoChan.Size = New System.Drawing.Size(169, 17)
        Me.hsbLoChan.TabIndex = 5
        Me.hsbLoChan.TabStop = True
        '
        '_lblShowData_15
        '
        Me._lblShowData_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_15.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_15.Location = New System.Drawing.Point(280, 280)
        Me._lblShowData_15.Name = "_lblShowData_15"
        Me._lblShowData_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_15.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_15.TabIndex = 23
        Me._lblShowData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_15
        '
        Me._lblChanNum_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_15.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_15.Location = New System.Drawing.Point(224, 280)
        Me._lblChanNum_15.Name = "_lblChanNum_15"
        Me._lblChanNum_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_15.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_15.TabIndex = 43
        Me._lblChanNum_15.Text = "15"
        Me._lblChanNum_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_7
        '
        Me._lblShowData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_7.Location = New System.Drawing.Point(112, 280)
        Me._lblShowData_7.Name = "_lblShowData_7"
        Me._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_7.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_7.TabIndex = 15
        Me._lblShowData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_7
        '
        Me._lblChanNum_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_7.Location = New System.Drawing.Point(56, 280)
        Me._lblChanNum_7.Name = "_lblChanNum_7"
        Me._lblChanNum_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_7.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_7.TabIndex = 35
        Me._lblChanNum_7.Text = "7"
        Me._lblChanNum_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_14
        '
        Me._lblShowData_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_14.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_14.Location = New System.Drawing.Point(280, 264)
        Me._lblShowData_14.Name = "_lblShowData_14"
        Me._lblShowData_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_14.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_14.TabIndex = 22
        Me._lblShowData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_14
        '
        Me._lblChanNum_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_14.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_14.Location = New System.Drawing.Point(224, 264)
        Me._lblChanNum_14.Name = "_lblChanNum_14"
        Me._lblChanNum_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_14.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_14.TabIndex = 42
        Me._lblChanNum_14.Text = "14"
        Me._lblChanNum_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_6
        '
        Me._lblShowData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_6.Location = New System.Drawing.Point(112, 264)
        Me._lblShowData_6.Name = "_lblShowData_6"
        Me._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_6.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_6.TabIndex = 14
        Me._lblShowData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_6
        '
        Me._lblChanNum_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_6.Location = New System.Drawing.Point(56, 264)
        Me._lblChanNum_6.Name = "_lblChanNum_6"
        Me._lblChanNum_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_6.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_6.TabIndex = 34
        Me._lblChanNum_6.Text = "6"
        Me._lblChanNum_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_13
        '
        Me._lblShowData_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_13.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_13.Location = New System.Drawing.Point(280, 248)
        Me._lblShowData_13.Name = "_lblShowData_13"
        Me._lblShowData_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_13.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_13.TabIndex = 21
        Me._lblShowData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_13
        '
        Me._lblChanNum_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_13.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_13.Location = New System.Drawing.Point(224, 248)
        Me._lblChanNum_13.Name = "_lblChanNum_13"
        Me._lblChanNum_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_13.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_13.TabIndex = 41
        Me._lblChanNum_13.Text = "13"
        Me._lblChanNum_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_5
        '
        Me._lblShowData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_5.Location = New System.Drawing.Point(112, 248)
        Me._lblShowData_5.Name = "_lblShowData_5"
        Me._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_5.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_5.TabIndex = 13
        Me._lblShowData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_5
        '
        Me._lblChanNum_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_5.Location = New System.Drawing.Point(56, 248)
        Me._lblChanNum_5.Name = "_lblChanNum_5"
        Me._lblChanNum_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_5.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_5.TabIndex = 33
        Me._lblChanNum_5.Text = "5"
        Me._lblChanNum_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_12
        '
        Me._lblShowData_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_12.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_12.Location = New System.Drawing.Point(280, 232)
        Me._lblShowData_12.Name = "_lblShowData_12"
        Me._lblShowData_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_12.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_12.TabIndex = 20
        Me._lblShowData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_12
        '
        Me._lblChanNum_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_12.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_12.Location = New System.Drawing.Point(224, 232)
        Me._lblChanNum_12.Name = "_lblChanNum_12"
        Me._lblChanNum_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_12.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_12.TabIndex = 40
        Me._lblChanNum_12.Text = "12"
        Me._lblChanNum_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_4
        '
        Me._lblShowData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_4.Location = New System.Drawing.Point(112, 232)
        Me._lblShowData_4.Name = "_lblShowData_4"
        Me._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_4.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_4.TabIndex = 12
        Me._lblShowData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_4
        '
        Me._lblChanNum_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_4.Location = New System.Drawing.Point(56, 232)
        Me._lblChanNum_4.Name = "_lblChanNum_4"
        Me._lblChanNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_4.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_4.TabIndex = 32
        Me._lblChanNum_4.Text = "4"
        Me._lblChanNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_11
        '
        Me._lblShowData_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_11.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_11.Location = New System.Drawing.Point(280, 216)
        Me._lblShowData_11.Name = "_lblShowData_11"
        Me._lblShowData_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_11.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_11.TabIndex = 19
        Me._lblShowData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_11
        '
        Me._lblChanNum_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_11.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_11.Location = New System.Drawing.Point(224, 216)
        Me._lblChanNum_11.Name = "_lblChanNum_11"
        Me._lblChanNum_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_11.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_11.TabIndex = 39
        Me._lblChanNum_11.Text = "11"
        Me._lblChanNum_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_3
        '
        Me._lblShowData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_3.Location = New System.Drawing.Point(112, 216)
        Me._lblShowData_3.Name = "_lblShowData_3"
        Me._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_3.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_3.TabIndex = 11
        Me._lblShowData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_3
        '
        Me._lblChanNum_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_3.Location = New System.Drawing.Point(56, 216)
        Me._lblChanNum_3.Name = "_lblChanNum_3"
        Me._lblChanNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_3.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_3.TabIndex = 31
        Me._lblChanNum_3.Text = "3"
        Me._lblChanNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_10
        '
        Me._lblShowData_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_10.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_10.Location = New System.Drawing.Point(280, 200)
        Me._lblShowData_10.Name = "_lblShowData_10"
        Me._lblShowData_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_10.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_10.TabIndex = 18
        Me._lblShowData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_10
        '
        Me._lblChanNum_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_10.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_10.Location = New System.Drawing.Point(224, 200)
        Me._lblChanNum_10.Name = "_lblChanNum_10"
        Me._lblChanNum_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_10.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_10.TabIndex = 38
        Me._lblChanNum_10.Text = "10"
        Me._lblChanNum_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_2
        '
        Me._lblShowData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_2.Location = New System.Drawing.Point(112, 200)
        Me._lblShowData_2.Name = "_lblShowData_2"
        Me._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_2.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_2.TabIndex = 10
        Me._lblShowData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_2
        '
        Me._lblChanNum_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_2.Location = New System.Drawing.Point(56, 200)
        Me._lblChanNum_2.Name = "_lblChanNum_2"
        Me._lblChanNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_2.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_2.TabIndex = 30
        Me._lblChanNum_2.Text = "2"
        Me._lblChanNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_9
        '
        Me._lblShowData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_9.Location = New System.Drawing.Point(280, 184)
        Me._lblShowData_9.Name = "_lblShowData_9"
        Me._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_9.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_9.TabIndex = 17
        Me._lblShowData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_9
        '
        Me._lblChanNum_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_9.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_9.Location = New System.Drawing.Point(224, 184)
        Me._lblChanNum_9.Name = "_lblChanNum_9"
        Me._lblChanNum_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_9.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_9.TabIndex = 37
        Me._lblChanNum_9.Text = "9"
        Me._lblChanNum_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_1
        '
        Me._lblShowData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_1.Location = New System.Drawing.Point(112, 184)
        Me._lblShowData_1.Name = "_lblShowData_1"
        Me._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_1.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_1.TabIndex = 9
        Me._lblShowData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_1
        '
        Me._lblChanNum_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_1.Location = New System.Drawing.Point(56, 184)
        Me._lblChanNum_1.Name = "_lblChanNum_1"
        Me._lblChanNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_1.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_1.TabIndex = 29
        Me._lblChanNum_1.Text = "1"
        Me._lblChanNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_8
        '
        Me._lblShowData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_8.Location = New System.Drawing.Point(280, 168)
        Me._lblShowData_8.Name = "_lblShowData_8"
        Me._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_8.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_8.TabIndex = 16
        Me._lblShowData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_8
        '
        Me._lblChanNum_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_8.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_8.Location = New System.Drawing.Point(224, 168)
        Me._lblChanNum_8.Name = "_lblChanNum_8"
        Me._lblChanNum_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_8.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_8.TabIndex = 36
        Me._lblChanNum_8.Text = "8"
        Me._lblChanNum_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowData_0
        '
        Me._lblShowData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_0.Location = New System.Drawing.Point(112, 168)
        Me._lblShowData_0.Name = "_lblShowData_0"
        Me._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_0.Size = New System.Drawing.Size(65, 17)
        Me._lblShowData_0.TabIndex = 2
        Me._lblShowData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblChanNum_0
        '
        Me._lblChanNum_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblChanNum_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblChanNum_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblChanNum_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblChanNum_0.Location = New System.Drawing.Point(56, 168)
        Me._lblChanNum_0.Name = "_lblChanNum_0"
        Me._lblChanNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblChanNum_0.Size = New System.Drawing.Size(41, 17)
        Me._lblChanNum_0.TabIndex = 28
        Me._lblChanNum_0.Text = "0"
        Me._lblChanNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblTemp2
        '
        Me.lblTemp2.BackColor = System.Drawing.SystemColors.Window
        Me.lblTemp2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblTemp2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblTemp2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblTemp2.Location = New System.Drawing.Point(272, 136)
        Me.lblTemp2.Name = "lblTemp2"
        Me.lblTemp2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblTemp2.Size = New System.Drawing.Size(81, 17)
        Me.lblTemp2.TabIndex = 25
        Me.lblTemp2.Text = "Temperature"
        Me.lblTemp2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan2
        '
        Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan2.Location = New System.Drawing.Point(216, 136)
        Me.lblChan2.Name = "lblChan2"
        Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan2.Size = New System.Drawing.Size(49, 17)
        Me.lblChan2.TabIndex = 27
        Me.lblChan2.Text = "Channel"
        Me.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblTemp1
        '
        Me.lblTemp1.BackColor = System.Drawing.SystemColors.Window
        Me.lblTemp1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblTemp1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblTemp1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblTemp1.Location = New System.Drawing.Point(104, 136)
        Me.lblTemp1.Name = "lblTemp1"
        Me.lblTemp1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblTemp1.Size = New System.Drawing.Size(81, 17)
        Me.lblTemp1.TabIndex = 24
        Me.lblTemp1.Text = "Temperature"
        Me.lblTemp1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan1
        '
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan1.Location = New System.Drawing.Point(48, 136)
        Me.lblChan1.Name = "lblChan1"
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.Size = New System.Drawing.Size(57, 17)
        Me.lblChan1.TabIndex = 26
        Me.lblChan1.Text = "Channel"
        Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblLastChan
        '
        Me.lblLastChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblLastChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblLastChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblLastChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblLastChan.Location = New System.Drawing.Point(272, 88)
        Me.lblLastChan.Name = "lblLastChan"
        Me.lblLastChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblLastChan.Size = New System.Drawing.Size(89, 17)
        Me.lblLastChan.TabIndex = 45
        Me.lblLastChan.Text = "Last Channel"
        '
        'lblHiChan
        '
        Me.lblHiChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblHiChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.lblHiChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblHiChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblHiChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblHiChan.Location = New System.Drawing.Point(200, 88)
        Me.lblHiChan.Name = "lblHiChan"
        Me.lblHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblHiChan.Size = New System.Drawing.Size(32, 17)
        Me.lblHiChan.TabIndex = 8
        Me.lblHiChan.Text = "0"
        '
        'lblFirstChan
        '
        Me.lblFirstChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblFirstChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFirstChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFirstChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFirstChan.Location = New System.Drawing.Point(272, 64)
        Me.lblFirstChan.Name = "lblFirstChan"
        Me.lblFirstChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFirstChan.Size = New System.Drawing.Size(89, 17)
        Me.lblFirstChan.TabIndex = 44
        Me.lblFirstChan.Text = "First Channel"
        '
        'lblLoChan
        '
        Me.lblLoChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblLoChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.lblLoChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblLoChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblLoChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblLoChan.Location = New System.Drawing.Point(200, 64)
        Me.lblLoChan.Name = "lblLoChan"
        Me.lblLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblLoChan.Size = New System.Drawing.Size(32, 17)
        Me.lblLoChan.TabIndex = 7
        Me.lblLoChan.Text = "0"
        '
        'lblChanPrompt
        '
        Me.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window
        Me.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChanPrompt.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChanPrompt.Location = New System.Drawing.Point(32, 40)
        Me.lblChanPrompt.Name = "lblChanPrompt"
        Me.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChanPrompt.Size = New System.Drawing.Size(297, 17)
        Me.lblChanPrompt.TabIndex = 0
        Me.lblChanPrompt.Text = "Select the range of multiplexor channels to display"
        Me.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.TopRight
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
        Me.lblDemoFunction.Size = New System.Drawing.Size(345, 25)
        Me.lblDemoFunction.TabIndex = 1
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.TInScan()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AcceptButton = Me.cmdStartConvert
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(370, 345)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStartConvert, Me.cmdStopConvert, Me.hsbHiChan, Me.hsbLoChan, Me._lblShowData_15, Me._lblChanNum_15, Me._lblShowData_7, Me._lblChanNum_7, Me._lblShowData_14, Me._lblChanNum_14, Me._lblShowData_6, Me._lblChanNum_6, Me._lblShowData_13, Me._lblChanNum_13, Me._lblShowData_5, Me._lblChanNum_5, Me._lblShowData_12, Me._lblChanNum_12, Me._lblShowData_4, Me._lblChanNum_4, Me._lblShowData_11, Me._lblChanNum_11, Me._lblShowData_3, Me._lblChanNum_3, Me._lblShowData_10, Me._lblChanNum_10, Me._lblShowData_2, Me._lblChanNum_2, Me._lblShowData_9, Me._lblChanNum_9, Me._lblShowData_1, Me._lblChanNum_1, Me._lblShowData_8, Me._lblChanNum_8, Me._lblShowData_0, Me._lblChanNum_0, Me.lblTemp2, Me.lblChan2, Me.lblTemp1, Me.lblChan1, Me.lblLastChan, Me.lblHiChan, Me.lblFirstChan, Me.lblLoChan, Me.lblChanPrompt, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Temperature Measurement"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim DevNum As Short

        Dim ULStat As MccDaq.ErrorInfo

        lblShowData = New System.Windows.Forms.Label(16) {}
        Me.lblShowData.SetValue(_lblShowData_15, 15)
        Me.lblShowData.SetValue(_lblShowData_7, 7)
        Me.lblShowData.SetValue(_lblShowData_14, 14)
        Me.lblShowData.SetValue(_lblShowData_6, 6)
        Me.lblShowData.SetValue(_lblShowData_13, 13)
        Me.lblShowData.SetValue(_lblShowData_5, 5)
        Me.lblShowData.SetValue(_lblShowData_12, 12)
        Me.lblShowData.SetValue(_lblShowData_4, 4)
        Me.lblShowData.SetValue(_lblShowData_11, 11)
        Me.lblShowData.SetValue(_lblShowData_3, 3)
        Me.lblShowData.SetValue(_lblShowData_10, 10)
        Me.lblShowData.SetValue(_lblShowData_2, 2)
        Me.lblShowData.SetValue(_lblShowData_9, 9)
        Me.lblShowData.SetValue(_lblShowData_1, 1)
        Me.lblShowData.SetValue(_lblShowData_8, 8)
        Me.lblShowData.SetValue(_lblShowData_0, 0)

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

        ' Determine if the board uses EXP boards for temperature measurements
        UsesEXPs = 0
        ULStat = DaqBoard.BoardConfig.GetUsesExps(UsesEXPs)
        If (ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then UsesEXPs = 0

    End Sub
#End Region

End Class