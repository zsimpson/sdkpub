'==============================================================================

' File:                         ULAI10.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.ALoadQueue()
'
' Purpose:                      Loads an A/D board's channel/gain queue.
'
' Demonstration:                Prepares a channel/gain queue and loads it
'                               to the board. An analog input function
'                               is then called to show how the queue
'                               values work.
'
' Other Library Calls:          MccDaq.MccService.ErrHandling()
'
' Special Requirements:         Board 0 must have an A/D converter and 
'                               channel gain queue hardware.
'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmDataDisplay
    Inherits System.Windows.Forms.Form
    
    Const NumChans As Short = 4 ' Number of channels in scan
    Const NumPoints As Integer = 10 ' Number of data points to collect
    Const NumElements As Integer = NumChans * NumPoints

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ADData(NumElements) As UInt16 ' dimension an array to hold the input values
    Dim MemHandle As Integer ' define a variable to contain the handle for

    ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
    Dim ChanArray(NumChans) As Short ' array to hold channel queue information
    Dim GainArray(NumChans) As MccDaq.Range ' array to hold gain queue information

    Public lblADData As System.Windows.Forms.Label()
    Public lblShowRange As System.Windows.Forms.Label()

    Private Sub cmdLoadQueue_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdLoadQueue.Click
        Dim ULStat As MccDaq.ErrorInfo

        cmdLoadQueue.Enabled = False
        cmdLoadQueue.Visible = False
        cmdUnloadQ.Enabled = True
        cmdUnloadQ.Visible = True

        ' Set up the channel/gain queue for 4 channels - each one set to
        ' different A/D ranges. Note: Do not mix Bipolar/Unipolar ranges
        ' We need to cast the named constants to short integers
        ChanArray(0) = 0
        GainArray(0) = MccDaq.Range.Bip5Volts
        lblShowRange(0).Text = "±5 Volts"

        ChanArray(1) = 1
        GainArray(1) = MccDaq.Range.Bip10Volts
        lblShowRange(1).Text = "±10 Volts"

        ChanArray(2) = 2
        GainArray(2) = MccDaq.Range.Bip5Volts
        lblShowRange(2).Text = "±5 Volts"

        ChanArray(3) = 3
        GainArray(3) = MccDaq.Range.BipPt5Volts
        lblShowRange(3).Text = "±02.5 Volts"

        ' Load the channel/gain values into the queue
        '  Parameters:
        '    ChanArray[] :array of channel values
        '    GainArray[] :array of gain values
        '    NumChans    :the number of elements in the arrays (0=disable queue)

        ULStat = DaqBoard.ALoadQueue(ChanArray, GainArray, NumChans)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    End Sub

    Private Sub cmdUnloadQ_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdUnloadQ.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim NoChans As Short
        Dim i As Short

        cmdUnloadQ.Enabled = False
        cmdUnloadQ.Visible = False
        cmdLoadQueue.Enabled = True
        cmdLoadQueue.Visible = True
        For i = 0 To 3
            lblShowRange(i).Text = "±5 Volts"
        Next i

        NoChans = 0 ' set to zero to disable queue

        ULStat = DaqBoard.ALoadQueue(ChanArray, GainArray, NoChans)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim ChannelNum As Short
        Dim SampleNum As Short
        Dim i As Integer
        Dim FirstPoint As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim Rate As Integer
        Dim Range As MccDaq.Range
        Dim Options As MccDaq.ScanOptions
        Dim Count As Integer
        Dim HighChan As Short
        Dim LowChan As Short

        ' Call an analog input function to show how the gain queue values
        ' supercede those passed to the function.

        '' Collect the values by calling MccDaq.MccBoard.AInScan function
        '  Parameters:
        '    LowChan    :the first channel of the scan
        '    HighChan   :the last channel of the scan
        '    Count      :the total number of A/D samples to collect
        '    Rate       :sample rate in samples per second
        '    Range      :the gain for the board
        '    MemHandle  :Handle for Windows buffer to store data in 
        '    Options    :data collection options

        tmrConvert.Stop()

        LowChan = 0             ' This is ignored
        HighChan = 3            ' This is ignored
        Count = NumElements   ' Number of data points to collect
        Options = MccDaq.ScanOptions.ConvertData   ' Return data as 12-bit values
        Range = MccDaq.Range.Bip5Volts ' This is ignored
        Rate = 1000 ' Acquire data at 1000 Hz

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.AInScan(LowChan, HighChan, Count, Rate, Range, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

        ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        i = 0
        For SampleNum = 0 To NumPoints - 1
            For ChannelNum = 0 To NumChans - 1
                lblADData(i).Text = ADData(i).ToString("D")
                i = i + 1
            Next ChannelNum
        Next SampleNum
        
        tmrConvert.Start()

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
    Public WithEvents cmdUnloadQ As System.Windows.Forms.Button
    Public WithEvents cmdLoadQueue As System.Windows.Forms.Button
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
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
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdUnloadQ = New System.Windows.Forms.Button()
        Me.cmdLoadQueue = New System.Windows.Forms.Button()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
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
        Me.cmdStopConvert.Location = New System.Drawing.Point(288, 272)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(57, 33)
        Me.cmdStopConvert.TabIndex = 13
        Me.cmdStopConvert.Text = "Quit"
        '
        'cmdUnloadQ
        '
        Me.cmdUnloadQ.BackColor = System.Drawing.SystemColors.Control
        Me.cmdUnloadQ.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdUnloadQ.Enabled = False
        Me.cmdUnloadQ.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdUnloadQ.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdUnloadQ.Location = New System.Drawing.Point(152, 272)
        Me.cmdUnloadQ.Name = "cmdUnloadQ"
        Me.cmdUnloadQ.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdUnloadQ.Size = New System.Drawing.Size(97, 33)
        Me.cmdUnloadQ.TabIndex = 47
        Me.cmdUnloadQ.Text = "Unload Queue"
        Me.cmdUnloadQ.Visible = False
        '
        'cmdLoadQueue
        '
        Me.cmdLoadQueue.BackColor = System.Drawing.SystemColors.Control
        Me.cmdLoadQueue.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdLoadQueue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdLoadQueue.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdLoadQueue.Location = New System.Drawing.Point(152, 272)
        Me.cmdLoadQueue.Name = "cmdLoadQueue"
        Me.cmdLoadQueue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdLoadQueue.Size = New System.Drawing.Size(97, 33)
        Me.cmdLoadQueue.TabIndex = 14
        Me.cmdLoadQueue.Text = "Load Queue"
        '
        'tmrConvert
        '
        Me.tmrConvert.Interval = 1000
        '
        '_lblADData_39
        '
        Me._lblADData_39.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_39.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_39.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_39.ForeColor = System.Drawing.Color.Blue

        Me._lblADData_39.Location = New System.Drawing.Point(280, 240)
        Me._lblADData_39.Name = "_lblADData_39"
        Me._lblADData_39.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_39.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_39.TabIndex = 46
        Me._lblADData_39.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_38
        '
        Me._lblADData_38.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_38.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_38.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_38.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_38.Location = New System.Drawing.Point(208, 240)
        Me._lblADData_38.Name = "_lblADData_38"
        Me._lblADData_38.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_38.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_38.TabIndex = 45
        Me._lblADData_38.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_37
        '
        Me._lblADData_37.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_37.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_37.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_37.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_37.Location = New System.Drawing.Point(136, 240)
        Me._lblADData_37.Name = "_lblADData_37"
        Me._lblADData_37.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_37.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_37.TabIndex = 44
        Me._lblADData_37.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_36
        '
        Me._lblADData_36.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_36.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_36.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_36.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_36.Location = New System.Drawing.Point(64, 240)
        Me._lblADData_36.Name = "_lblADData_36"
        Me._lblADData_36.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_36.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_36.TabIndex = 43
        Me._lblADData_36.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_35
        '
        Me._lblADData_35.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_35.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_35.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_35.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_35.Location = New System.Drawing.Point(280, 224)
        Me._lblADData_35.Name = "_lblADData_35"
        Me._lblADData_35.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_35.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_35.TabIndex = 42
        Me._lblADData_35.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_34
        '
        Me._lblADData_34.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_34.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_34.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_34.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_34.Location = New System.Drawing.Point(208, 224)
        Me._lblADData_34.Name = "_lblADData_34"
        Me._lblADData_34.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_34.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_34.TabIndex = 41
        Me._lblADData_34.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_33
        '
        Me._lblADData_33.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_33.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_33.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_33.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_33.Location = New System.Drawing.Point(136, 224)
        Me._lblADData_33.Name = "_lblADData_33"
        Me._lblADData_33.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_33.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_33.TabIndex = 40
        Me._lblADData_33.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_32
        '
        Me._lblADData_32.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_32.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_32.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_32.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_32.Location = New System.Drawing.Point(64, 224)
        Me._lblADData_32.Name = "_lblADData_32"
        Me._lblADData_32.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_32.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_32.TabIndex = 39
        Me._lblADData_32.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_31
        '
        Me._lblADData_31.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_31.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_31.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_31.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_31.Location = New System.Drawing.Point(280, 208)
        Me._lblADData_31.Name = "_lblADData_31"
        Me._lblADData_31.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_31.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_31.TabIndex = 38
        Me._lblADData_31.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_30
        '
        Me._lblADData_30.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_30.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_30.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_30.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_30.Location = New System.Drawing.Point(208, 208)
        Me._lblADData_30.Name = "_lblADData_30"
        Me._lblADData_30.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_30.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_30.TabIndex = 37
        Me._lblADData_30.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_29
        '
        Me._lblADData_29.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_29.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_29.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_29.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_29.Location = New System.Drawing.Point(136, 208)
        Me._lblADData_29.Name = "_lblADData_29"
        Me._lblADData_29.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_29.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_29.TabIndex = 36
        Me._lblADData_29.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_28
        '
        Me._lblADData_28.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_28.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_28.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_28.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_28.Location = New System.Drawing.Point(64, 208)
        Me._lblADData_28.Name = "_lblADData_28"
        Me._lblADData_28.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_28.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_28.TabIndex = 35
        Me._lblADData_28.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_27
        '
        Me._lblADData_27.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_27.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_27.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_27.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_27.Location = New System.Drawing.Point(280, 192)
        Me._lblADData_27.Name = "_lblADData_27"
        Me._lblADData_27.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_27.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_27.TabIndex = 34
        Me._lblADData_27.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_26
        '
        Me._lblADData_26.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_26.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_26.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_26.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_26.Location = New System.Drawing.Point(208, 192)
        Me._lblADData_26.Name = "_lblADData_26"
        Me._lblADData_26.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_26.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_26.TabIndex = 33
        Me._lblADData_26.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_25
        '
        Me._lblADData_25.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_25.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_25.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_25.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_25.Location = New System.Drawing.Point(136, 192)
        Me._lblADData_25.Name = "_lblADData_25"
        Me._lblADData_25.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_25.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_25.TabIndex = 32
        Me._lblADData_25.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_24
        '
        Me._lblADData_24.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_24.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_24.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_24.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_24.Location = New System.Drawing.Point(64, 192)
        Me._lblADData_24.Name = "_lblADData_24"
        Me._lblADData_24.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_24.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_24.TabIndex = 31
        Me._lblADData_24.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_23
        '
        Me._lblADData_23.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_23.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_23.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_23.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_23.Location = New System.Drawing.Point(280, 176)
        Me._lblADData_23.Name = "_lblADData_23"
        Me._lblADData_23.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_23.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_23.TabIndex = 30
        Me._lblADData_23.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_22
        '
        Me._lblADData_22.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_22.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_22.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_22.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_22.Location = New System.Drawing.Point(208, 176)
        Me._lblADData_22.Name = "_lblADData_22"
        Me._lblADData_22.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_22.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_22.TabIndex = 29
        Me._lblADData_22.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_21
        '
        Me._lblADData_21.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_21.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_21.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_21.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_21.Location = New System.Drawing.Point(136, 176)
        Me._lblADData_21.Name = "_lblADData_21"
        Me._lblADData_21.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_21.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_21.TabIndex = 28
        Me._lblADData_21.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_20
        '
        Me._lblADData_20.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_20.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_20.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_20.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_20.Location = New System.Drawing.Point(64, 176)
        Me._lblADData_20.Name = "_lblADData_20"
        Me._lblADData_20.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_20.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_20.TabIndex = 27
        Me._lblADData_20.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_11
        '
        Me._lblADData_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_11.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_11.Location = New System.Drawing.Point(280, 160)
        Me._lblADData_11.Name = "_lblADData_11"
        Me._lblADData_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_11.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_11.TabIndex = 18
        Me._lblADData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_10
        '
        Me._lblADData_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_10.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_10.Location = New System.Drawing.Point(208, 160)
        Me._lblADData_10.Name = "_lblADData_10"
        Me._lblADData_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_10.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_10.TabIndex = 17
        Me._lblADData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_9
        '
        Me._lblADData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_9.Location = New System.Drawing.Point(136, 160)
        Me._lblADData_9.Name = "_lblADData_9"
        Me._lblADData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_9.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_9.TabIndex = 16
        Me._lblADData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_8
        '
        Me._lblADData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_8.Location = New System.Drawing.Point(64, 160)
        Me._lblADData_8.Name = "_lblADData_8"
        Me._lblADData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_8.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_8.TabIndex = 15
        Me._lblADData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_19
        '
        Me._lblADData_19.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_19.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_19.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_19.Location = New System.Drawing.Point(280, 144)
        Me._lblADData_19.Name = "_lblADData_19"
        Me._lblADData_19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_19.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_19.TabIndex = 26
        Me._lblADData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_18
        '
        Me._lblADData_18.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_18.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_18.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_18.Location = New System.Drawing.Point(208, 144)
        Me._lblADData_18.Name = "_lblADData_18"
        Me._lblADData_18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_18.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_18.TabIndex = 25
        Me._lblADData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_17
        '
        Me._lblADData_17.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_17.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_17.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_17.Location = New System.Drawing.Point(136, 144)
        Me._lblADData_17.Name = "_lblADData_17"
        Me._lblADData_17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_17.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_17.TabIndex = 24
        Me._lblADData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_16
        '
        Me._lblADData_16.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_16.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_16.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_16.Location = New System.Drawing.Point(64, 144)
        Me._lblADData_16.Name = "_lblADData_16"
        Me._lblADData_16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_16.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_16.TabIndex = 23
        Me._lblADData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_15
        '
        Me._lblADData_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_15.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_15.Location = New System.Drawing.Point(280, 128)
        Me._lblADData_15.Name = "_lblADData_15"
        Me._lblADData_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_15.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_15.TabIndex = 22
        Me._lblADData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_14
        '
        Me._lblADData_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_14.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_14.Location = New System.Drawing.Point(208, 128)
        Me._lblADData_14.Name = "_lblADData_14"
        Me._lblADData_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_14.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_14.TabIndex = 21
        Me._lblADData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_13
        '
        Me._lblADData_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_13.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_13.Location = New System.Drawing.Point(136, 128)
        Me._lblADData_13.Name = "_lblADData_13"
        Me._lblADData_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_13.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_13.TabIndex = 20
        Me._lblADData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_12
        '
        Me._lblADData_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_12.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_12.Location = New System.Drawing.Point(64, 128)
        Me._lblADData_12.Name = "_lblADData_12"
        Me._lblADData_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_12.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_12.TabIndex = 19
        Me._lblADData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_7
        '
        Me._lblADData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_7.Location = New System.Drawing.Point(280, 112)
        Me._lblADData_7.Name = "_lblADData_7"
        Me._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_7.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_7.TabIndex = 12
        Me._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_6
        '
        Me._lblADData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_6.Location = New System.Drawing.Point(208, 112)
        Me._lblADData_6.Name = "_lblADData_6"
        Me._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_6.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_6.TabIndex = 11
        Me._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_5
        '
        Me._lblADData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_5.Location = New System.Drawing.Point(136, 112)
        Me._lblADData_5.Name = "_lblADData_5"
        Me._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_5.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_5.TabIndex = 10
        Me._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_4
        '
        Me._lblADData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_4.Location = New System.Drawing.Point(64, 112)
        Me._lblADData_4.Name = "_lblADData_4"
        Me._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_4.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_4.TabIndex = 9
        Me._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_3
        '
        Me._lblADData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_3.Location = New System.Drawing.Point(280, 96)
        Me._lblADData_3.Name = "_lblADData_3"
        Me._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_3.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_3.TabIndex = 8
        Me._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_2
        '
        Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_2.Location = New System.Drawing.Point(208, 96)
        Me._lblADData_2.Name = "_lblADData_2"
        Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_2.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_2.TabIndex = 7
        Me._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_1
        '
        Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_1.Location = New System.Drawing.Point(136, 96)
        Me._lblADData_1.Name = "_lblADData_1"
        Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_1.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_1.TabIndex = 6
        Me._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_0
        '
        Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_0.Location = New System.Drawing.Point(64, 96)
        Me._lblADData_0.Name = "_lblADData_0"
        Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_0.Size = New System.Drawing.Size(65, 17)
        Me._lblADData_0.TabIndex = 5
        Me._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_3
        '
        Me._lblShowRange_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_3.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_3.Location = New System.Drawing.Point(280, 64)
        Me._lblShowRange_3.Name = "_lblShowRange_3"
        Me._lblShowRange_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_3.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRange_3.TabIndex = 52
        Me._lblShowRange_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_2
        '
        Me._lblShowRange_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_2.Location = New System.Drawing.Point(208, 64)
        Me._lblShowRange_2.Name = "_lblShowRange_2"
        Me._lblShowRange_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_2.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRange_2.TabIndex = 51
        Me._lblShowRange_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_1
        '
        Me._lblShowRange_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_1.Location = New System.Drawing.Point(136, 64)
        Me._lblShowRange_1.Name = "_lblShowRange_1"
        Me._lblShowRange_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_1.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRange_1.TabIndex = 50
        Me._lblShowRange_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblShowRange_0
        '
        Me._lblShowRange_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowRange_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowRange_0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowRange_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowRange_0.Location = New System.Drawing.Point(64, 64)
        Me._lblShowRange_0.Name = "_lblShowRange_0"
        Me._lblShowRange_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowRange_0.Size = New System.Drawing.Size(65, 17)
        Me._lblShowRange_0.TabIndex = 49
        Me._lblShowRange_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblRange
        '
        Me.lblRange.BackColor = System.Drawing.SystemColors.Window
        Me.lblRange.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblRange.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblRange.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblRange.Location = New System.Drawing.Point(8, 64)
        Me.lblRange.Name = "lblRange"
        Me.lblRange.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblRange.Size = New System.Drawing.Size(49, 17)
        Me.lblRange.TabIndex = 48
        Me.lblRange.Text = "Range:"
        '
        'lblChan3
        '
        Me.lblChan3.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan3.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan3.Location = New System.Drawing.Point(280, 40)
        Me.lblChan3.Name = "lblChan3"
        Me.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan3.Size = New System.Drawing.Size(65, 17)
        Me.lblChan3.TabIndex = 4
        Me.lblChan3.Text = "Channel 3:"
        '
        'lblChan2
        '
        Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan2.Location = New System.Drawing.Point(208, 40)
        Me.lblChan2.Name = "lblChan2"
        Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan2.Size = New System.Drawing.Size(65, 17)
        Me.lblChan2.TabIndex = 3
        Me.lblChan2.Text = "Channel 2:"
        '
        'lblChan1
        '
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan1.Location = New System.Drawing.Point(136, 40)
        Me.lblChan1.Name = "lblChan1"
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.Size = New System.Drawing.Size(65, 17)
        Me.lblChan1.TabIndex = 2
        Me.lblChan1.Text = "Channel 1:"
        '
        'lblChan0
        '
        Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan0.Location = New System.Drawing.Point(64, 40)
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
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 8)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(351, 25)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard..ALoadQueue()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(366, 316)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopConvert, Me.cmdUnloadQ, Me.cmdLoadQueue, Me._lblADData_39, Me._lblADData_38, Me._lblADData_37, Me._lblADData_36, Me._lblADData_35, Me._lblADData_34, Me._lblADData_33, Me._lblADData_32, Me._lblADData_31, Me._lblADData_30, Me._lblADData_29, Me._lblADData_28, Me._lblADData_27, Me._lblADData_26, Me._lblADData_25, Me._lblADData_24, Me._lblADData_23, Me._lblADData_22, Me._lblADData_21, Me._lblADData_20, Me._lblADData_11, Me._lblADData_10, Me._lblADData_9, Me._lblADData_8, Me._lblADData_19, Me._lblADData_18, Me._lblADData_17, Me._lblADData_16, Me._lblADData_15, Me._lblADData_14, Me._lblADData_13, Me._lblADData_12, Me._lblADData_7, Me._lblADData_6, Me._lblADData_5, Me._lblADData_4, Me._lblADData_3, Me._lblADData_2, Me._lblADData_1, Me._lblADData_0, Me._lblShowRange_3, Me._lblShowRange_2, Me._lblShowRange_1, Me._lblShowRange_0, Me.lblRange, Me.lblChan3, Me.lblChan2, Me.lblChan1, Me.lblChan0, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Gain Queue"
        Me.ResumeLayout(False)

    End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim i As Short
        Dim ULStat As MccDaq.ErrorInfo

        ' Note: Any change to label names requires a change to the corresponding array element
        lblADData = New System.Windows.Forms.Label(40) {}
        lblShowRange = New System.Windows.Forms.Label(3) {}

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

        For i = 0 To 3
            lblShowRange(i).Text = "±5 Volts"
        Next i

        tmrConvert.Enabled = True


    End Sub
#End Region

End Class