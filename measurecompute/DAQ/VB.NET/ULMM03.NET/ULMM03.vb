'==============================================================================

' File:                         ULMM03.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AInScan() with 
'                               MccDaq.MccBoar.ExtMemory option
'
' Purpose:                      Collect data from A/D to memory board
'
' Demonstrates:                 How to use the MccDaq.MccBoard.ExtMemory option to
'                               send data to a memory board and how to
'                               read the data back again.
'
' Other Library Calls:          MccDaq.MccBoard.MemRead(), 
'                               MccDaq.MccService.ErrHandling()
'
' Special Requirements:         Board 0 must be an A/D board.
'                               Board 5 must be a memory board.
'                               A/D and memory boards must be connected
'                               together via a DT-Connect cable.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    Const ADBoardNumber As Short = 0 ' Board number of A/D board
    Const MemBoardNumber As Short = 5 ' Board number of memory board
    Const NumPoints As Short = 1000 ' Number of points to collect from A/D
    Const BufSize As Short = 20 ' Size of buffer used with MccDaq.MccBoard.MemRead()


    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(ADBoardNumber)

    Private MemBoard As MccDaq.MccBoard = New MccDaq.MccBoard(MemBoardNumber)

    Dim DataBuffer(BufSize) As UInt16
    Dim PointNum As Short
    Dim FirstPoint As Integer

    Public lblADData As System.Windows.Forms.Label()
    Public lblDataPoint As System.Windows.Forms.Label()

    Private Sub cmdReadMemBoard_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdReadMemBoard.Click
        Dim DataPoint As UInt16
        Dim i As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim Count As Integer
        Dim CurDataValue As Integer

        ' Read the data back from the memory board in blocks.
        ' Print each block of data on the screen.

        '  DataBuffer - Array of data to read data into
        '  FirstPoint - Address to read first point (or FROMHERE)
        '  Count - Number of points to read

        Count = BufSize

        ULStat = MemBoard.MemRead(DataBuffer(0), FirstPoint, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        FirstPoint = MccDaq.MccBoard.FromHere

        For i = 0 To BufSize - 1

            ' Raw data from memory board contains a 4 bit channel number (LSB's)
            ' and a 12 bit A/D value (MSB's).  The following code strips out the
            ' channel tags from the A/D data.
            CurDataValue = System.Convert.ToInt32(DataBuffer(i))
            DataPoint = System.Convert.ToUInt16((CurDataValue \ 16) And &HFFFS)

            lblDataPoint(i).Text = (PointNum + i).ToString("0")
            lblADData(i).Text = DataPoint.ToString("0")
        Next i

        PointNum = PointNum + BufSize
        If PointNum >= NumPoints Then
            PointNum = 0
            ULStat = MemBoard.MemReset()
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        End If

    End Sub

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click
        Dim Options As MccDaq.ScanOptions
        Dim Dummy As Short
        Dim Range As MccDaq.Range
        Dim Rate As Integer
        Dim Count As Integer
        Dim HighChan As Integer
        Dim LowChan As Integer
        Dim ULStat As MccDaq.ErrorInfo

        cmdStartConvert.Enabled = False
        cmdReadMemBoard.Enabled = False

        ' Collect data to memory with MccDaq.MccBoard.AInScan() and the EXTMEMORY option
        '   Parameters:
        '     LowChan      :the first channel of the scan
        '     HighChan    :the last channel of the scan
        '     Count      :the total number of A/D samples to collect
        '     Rate       :sample rate in samples per second
        '     Range         :the Range for the board
        '     DataBuffer[] :the array for the collected data values
        '     Options      :data collection options

        ULStat = MemBoard.MemReset()
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        LowChan = 0 ' Low channel of A/D scan
        HighChan = 0 ' High channel of A/D scan
        Count = NumPoints ' Number of data points to collect
        Rate = 5000 ' Sampling rate (samples per second)
        Range = MccDaq.Range.Bip5Volts
        Dummy = 0 ' Placeholder (ignored)
        Options = MccDaq.ScanOptions.ExtMemory ' Send data to memory board

        ULStat = DaqBoard.AInScan(LowChan, HighChan, Count, Rate, Range, Dummy, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        cmdStartConvert.Enabled = True
        cmdReadMemBoard.Enabled = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click
        Dim ULStat As Short

        If ULStat <> 0 Then Stop
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
    Public WithEvents cmdReadMemBoard As System.Windows.Forms.Button
    Public WithEvents cmdStartConvert As System.Windows.Forms.Button
    Public WithEvents _lblADData_19 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_19 As System.Windows.Forms.Label
    Public WithEvents _lblADData_14 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_14 As System.Windows.Forms.Label
    Public WithEvents _lblADData_9 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_9 As System.Windows.Forms.Label
    Public WithEvents _lblADData_4 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_4 As System.Windows.Forms.Label
    Public WithEvents _lblADData_18 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_18 As System.Windows.Forms.Label
    Public WithEvents _lblADData_13 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_13 As System.Windows.Forms.Label
    Public WithEvents _lblADData_8 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_8 As System.Windows.Forms.Label
    Public WithEvents _lblADData_3 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_3 As System.Windows.Forms.Label
    Public WithEvents _lblADData_17 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_17 As System.Windows.Forms.Label
    Public WithEvents _lblADData_12 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_12 As System.Windows.Forms.Label
    Public WithEvents _lblADData_7 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_7 As System.Windows.Forms.Label
    Public WithEvents _lblADData_2 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_2 As System.Windows.Forms.Label
    Public WithEvents _lblADData_16 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_16 As System.Windows.Forms.Label
    Public WithEvents _lblADData_11 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_11 As System.Windows.Forms.Label
    Public WithEvents _lblADData_6 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_6 As System.Windows.Forms.Label
    Public WithEvents _lblADData_1 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_1 As System.Windows.Forms.Label
    Public WithEvents _lblADData_15 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_15 As System.Windows.Forms.Label
    Public WithEvents _lblADData_10 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_10 As System.Windows.Forms.Label
    Public WithEvents _lblADData_5 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_5 As System.Windows.Forms.Label
    Public WithEvents _lblADData_0 As System.Windows.Forms.Label
    Public WithEvents _lblDataPoint_0 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_7 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_6 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_5 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_4 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_3 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_2 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_1 As System.Windows.Forms.Label
    Public WithEvents _lblColTitle_0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdReadMemBoard = New System.Windows.Forms.Button()
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me._lblADData_19 = New System.Windows.Forms.Label()
        Me._lblDataPoint_19 = New System.Windows.Forms.Label()
        Me._lblADData_14 = New System.Windows.Forms.Label()
        Me._lblDataPoint_14 = New System.Windows.Forms.Label()
        Me._lblADData_9 = New System.Windows.Forms.Label()
        Me._lblDataPoint_9 = New System.Windows.Forms.Label()
        Me._lblADData_4 = New System.Windows.Forms.Label()
        Me._lblDataPoint_4 = New System.Windows.Forms.Label()
        Me._lblADData_18 = New System.Windows.Forms.Label()
        Me._lblDataPoint_18 = New System.Windows.Forms.Label()
        Me._lblADData_13 = New System.Windows.Forms.Label()
        Me._lblDataPoint_13 = New System.Windows.Forms.Label()
        Me._lblADData_8 = New System.Windows.Forms.Label()
        Me._lblDataPoint_8 = New System.Windows.Forms.Label()
        Me._lblADData_3 = New System.Windows.Forms.Label()
        Me._lblDataPoint_3 = New System.Windows.Forms.Label()
        Me._lblADData_17 = New System.Windows.Forms.Label()
        Me._lblDataPoint_17 = New System.Windows.Forms.Label()
        Me._lblADData_12 = New System.Windows.Forms.Label()
        Me._lblDataPoint_12 = New System.Windows.Forms.Label()
        Me._lblADData_7 = New System.Windows.Forms.Label()
        Me._lblDataPoint_7 = New System.Windows.Forms.Label()
        Me._lblADData_2 = New System.Windows.Forms.Label()
        Me._lblDataPoint_2 = New System.Windows.Forms.Label()
        Me._lblADData_16 = New System.Windows.Forms.Label()
        Me._lblDataPoint_16 = New System.Windows.Forms.Label()
        Me._lblADData_11 = New System.Windows.Forms.Label()
        Me._lblDataPoint_11 = New System.Windows.Forms.Label()
        Me._lblADData_6 = New System.Windows.Forms.Label()
        Me._lblDataPoint_6 = New System.Windows.Forms.Label()
        Me._lblADData_1 = New System.Windows.Forms.Label()
        Me._lblDataPoint_1 = New System.Windows.Forms.Label()
        Me._lblADData_15 = New System.Windows.Forms.Label()
        Me._lblDataPoint_15 = New System.Windows.Forms.Label()
        Me._lblADData_10 = New System.Windows.Forms.Label()
        Me._lblDataPoint_10 = New System.Windows.Forms.Label()
        Me._lblADData_5 = New System.Windows.Forms.Label()
        Me._lblDataPoint_5 = New System.Windows.Forms.Label()
        Me._lblADData_0 = New System.Windows.Forms.Label()
        Me._lblDataPoint_0 = New System.Windows.Forms.Label()
        Me._lblColTitle_7 = New System.Windows.Forms.Label()
        Me._lblColTitle_6 = New System.Windows.Forms.Label()
        Me._lblColTitle_5 = New System.Windows.Forms.Label()
        Me._lblColTitle_4 = New System.Windows.Forms.Label()
        Me._lblColTitle_3 = New System.Windows.Forms.Label()
        Me._lblColTitle_2 = New System.Windows.Forms.Label()
        Me._lblColTitle_1 = New System.Windows.Forms.Label()
        Me._lblColTitle_0 = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(250, 218)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(59, 27)
        Me.cmdStopConvert.TabIndex = 10
        Me.cmdStopConvert.Text = "Quit"
        '
        'cmdReadMemBoard
        '
        Me.cmdReadMemBoard.BackColor = System.Drawing.SystemColors.Control
        Me.cmdReadMemBoard.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdReadMemBoard.Enabled = False
        Me.cmdReadMemBoard.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdReadMemBoard.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdReadMemBoard.Location = New System.Drawing.Point(160, 218)
        Me.cmdReadMemBoard.Name = "cmdReadMemBoard"
        Me.cmdReadMemBoard.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdReadMemBoard.Size = New System.Drawing.Size(65, 27)
        Me.cmdReadMemBoard.TabIndex = 12
        Me.cmdReadMemBoard.Text = "Read "
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(71, 218)
        Me.cmdStartConvert.Name = "cmdStartConvert"
        Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartConvert.Size = New System.Drawing.Size(65, 27)
        Me.cmdStartConvert.TabIndex = 11
        Me.cmdStartConvert.Text = "Start"
        '
        '_lblADData_19
        '
        Me._lblADData_19.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_19.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_19.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_19.Location = New System.Drawing.Point(320, 167)
        Me._lblADData_19.Name = "_lblADData_19"
        Me._lblADData_19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_19.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_19.TabIndex = 43
        Me._lblADData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_19
        '
        Me._lblDataPoint_19.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_19.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_19.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_19.Location = New System.Drawing.Point(288, 167)
        Me._lblDataPoint_19.Name = "_lblDataPoint_19"
        Me._lblDataPoint_19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_19.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_19.TabIndex = 42
        Me._lblDataPoint_19.Text = "19"
        Me._lblDataPoint_19.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_14
        '
        Me._lblADData_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_14.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_14.Location = New System.Drawing.Point(231, 167)
        Me._lblADData_14.Name = "_lblADData_14"
        Me._lblADData_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_14.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_14.TabIndex = 33
        Me._lblADData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_14
        '
        Me._lblDataPoint_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_14.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_14.Location = New System.Drawing.Point(199, 167)
        Me._lblDataPoint_14.Name = "_lblDataPoint_14"
        Me._lblDataPoint_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_14.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_14.TabIndex = 32
        Me._lblDataPoint_14.Text = "14"
        Me._lblDataPoint_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_9
        '
        Me._lblADData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_9.Location = New System.Drawing.Point(141, 167)
        Me._lblADData_9.Name = "_lblADData_9"
        Me._lblADData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_9.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_9.TabIndex = 14
        Me._lblADData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_9
        '
        Me._lblDataPoint_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_9.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_9.Location = New System.Drawing.Point(109, 167)
        Me._lblDataPoint_9.Name = "_lblDataPoint_9"
        Me._lblDataPoint_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_9.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_9.TabIndex = 23
        Me._lblDataPoint_9.Text = "9"
        Me._lblDataPoint_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_4
        '
        Me._lblADData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_4.Location = New System.Drawing.Point(52, 167)
        Me._lblADData_4.Name = "_lblADData_4"
        Me._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_4.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_4.TabIndex = 6
        Me._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_4
        '
        Me._lblDataPoint_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_4.Location = New System.Drawing.Point(20, 167)
        Me._lblDataPoint_4.Name = "_lblDataPoint_4"
        Me._lblDataPoint_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_4.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_4.TabIndex = 18
        Me._lblDataPoint_4.Text = "4"
        Me._lblDataPoint_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_18
        '
        Me._lblADData_18.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_18.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_18.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_18.Location = New System.Drawing.Point(320, 148)
        Me._lblADData_18.Name = "_lblADData_18"
        Me._lblADData_18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_18.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_18.TabIndex = 41
        Me._lblADData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_18
        '
        Me._lblDataPoint_18.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_18.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_18.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_18.Location = New System.Drawing.Point(288, 148)
        Me._lblDataPoint_18.Name = "_lblDataPoint_18"
        Me._lblDataPoint_18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_18.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_18.TabIndex = 40
        Me._lblDataPoint_18.Text = "18"
        Me._lblDataPoint_18.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_13
        '
        Me._lblADData_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_13.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_13.Location = New System.Drawing.Point(231, 148)
        Me._lblADData_13.Name = "_lblADData_13"
        Me._lblADData_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_13.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_13.TabIndex = 31
        Me._lblADData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_13
        '
        Me._lblDataPoint_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_13.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_13.Location = New System.Drawing.Point(199, 148)
        Me._lblDataPoint_13.Name = "_lblDataPoint_13"
        Me._lblDataPoint_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_13.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_13.TabIndex = 30
        Me._lblDataPoint_13.Text = "13"
        Me._lblDataPoint_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_8
        '
        Me._lblADData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_8.Location = New System.Drawing.Point(141, 148)
        Me._lblADData_8.Name = "_lblADData_8"
        Me._lblADData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_8.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_8.TabIndex = 13
        Me._lblADData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_8
        '
        Me._lblDataPoint_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_8.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_8.Location = New System.Drawing.Point(109, 148)
        Me._lblDataPoint_8.Name = "_lblDataPoint_8"
        Me._lblDataPoint_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_8.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_8.TabIndex = 22
        Me._lblDataPoint_8.Text = "8"
        Me._lblDataPoint_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_3
        '
        Me._lblADData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_3.Location = New System.Drawing.Point(52, 148)
        Me._lblADData_3.Name = "_lblADData_3"
        Me._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_3.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_3.TabIndex = 5
        Me._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_3
        '
        Me._lblDataPoint_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_3.Location = New System.Drawing.Point(20, 148)
        Me._lblDataPoint_3.Name = "_lblDataPoint_3"
        Me._lblDataPoint_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_3.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_3.TabIndex = 17
        Me._lblDataPoint_3.Text = "3"
        Me._lblDataPoint_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_17
        '
        Me._lblADData_17.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_17.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_17.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_17.Location = New System.Drawing.Point(320, 128)
        Me._lblADData_17.Name = "_lblADData_17"
        Me._lblADData_17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_17.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_17.TabIndex = 39
        Me._lblADData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_17
        '
        Me._lblDataPoint_17.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_17.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_17.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_17.Location = New System.Drawing.Point(288, 128)
        Me._lblDataPoint_17.Name = "_lblDataPoint_17"
        Me._lblDataPoint_17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_17.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_17.TabIndex = 38
        Me._lblDataPoint_17.Text = "17"
        Me._lblDataPoint_17.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_12
        '
        Me._lblADData_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_12.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_12.Location = New System.Drawing.Point(231, 128)
        Me._lblADData_12.Name = "_lblADData_12"
        Me._lblADData_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_12.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_12.TabIndex = 29
        Me._lblADData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_12
        '
        Me._lblDataPoint_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_12.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_12.Location = New System.Drawing.Point(199, 128)
        Me._lblDataPoint_12.Name = "_lblDataPoint_12"
        Me._lblDataPoint_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_12.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_12.TabIndex = 28
        Me._lblDataPoint_12.Text = "12"
        Me._lblDataPoint_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_7
        '
        Me._lblADData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_7.Location = New System.Drawing.Point(141, 128)
        Me._lblADData_7.Name = "_lblADData_7"
        Me._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_7.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_7.TabIndex = 9
        Me._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_7
        '
        Me._lblDataPoint_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_7.Location = New System.Drawing.Point(109, 128)
        Me._lblDataPoint_7.Name = "_lblDataPoint_7"
        Me._lblDataPoint_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_7.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_7.TabIndex = 21
        Me._lblDataPoint_7.Text = "7"
        Me._lblDataPoint_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_2
        '
        Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_2.Location = New System.Drawing.Point(52, 128)
        Me._lblADData_2.Name = "_lblADData_2"
        Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_2.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_2.TabIndex = 4
        Me._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_2
        '
        Me._lblDataPoint_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_2.Location = New System.Drawing.Point(20, 128)
        Me._lblDataPoint_2.Name = "_lblDataPoint_2"
        Me._lblDataPoint_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_2.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_2.TabIndex = 16
        Me._lblDataPoint_2.Text = "2"
        Me._lblDataPoint_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_16
        '
        Me._lblADData_16.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_16.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_16.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_16.Location = New System.Drawing.Point(320, 109)
        Me._lblADData_16.Name = "_lblADData_16"
        Me._lblADData_16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_16.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_16.TabIndex = 37
        Me._lblADData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_16
        '
        Me._lblDataPoint_16.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_16.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_16.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_16.Location = New System.Drawing.Point(288, 109)
        Me._lblDataPoint_16.Name = "_lblDataPoint_16"
        Me._lblDataPoint_16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_16.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_16.TabIndex = 36
        Me._lblDataPoint_16.Text = "16"
        Me._lblDataPoint_16.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_11
        '
        Me._lblADData_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_11.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_11.Location = New System.Drawing.Point(231, 109)
        Me._lblADData_11.Name = "_lblADData_11"
        Me._lblADData_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_11.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_11.TabIndex = 27
        Me._lblADData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_11
        '
        Me._lblDataPoint_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_11.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_11.Location = New System.Drawing.Point(199, 109)
        Me._lblDataPoint_11.Name = "_lblDataPoint_11"
        Me._lblDataPoint_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_11.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_11.TabIndex = 26
        Me._lblDataPoint_11.Text = "11"
        Me._lblDataPoint_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_6
        '
        Me._lblADData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_6.Location = New System.Drawing.Point(141, 109)
        Me._lblADData_6.Name = "_lblADData_6"
        Me._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_6.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_6.TabIndex = 8
        Me._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_6
        '
        Me._lblDataPoint_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_6.Location = New System.Drawing.Point(109, 109)
        Me._lblDataPoint_6.Name = "_lblDataPoint_6"
        Me._lblDataPoint_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_6.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_6.TabIndex = 20
        Me._lblDataPoint_6.Text = "6"
        Me._lblDataPoint_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_1
        '
        Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_1.Location = New System.Drawing.Point(52, 109)
        Me._lblADData_1.Name = "_lblADData_1"
        Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_1.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_1.TabIndex = 3
        Me._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_1
        '
        Me._lblDataPoint_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_1.Location = New System.Drawing.Point(20, 109)
        Me._lblDataPoint_1.Name = "_lblDataPoint_1"
        Me._lblDataPoint_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_1.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_1.TabIndex = 15
        Me._lblDataPoint_1.Text = "1"
        Me._lblDataPoint_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_15
        '
        Me._lblADData_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_15.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_15.Location = New System.Drawing.Point(320, 90)
        Me._lblADData_15.Name = "_lblADData_15"
        Me._lblADData_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_15.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_15.TabIndex = 35
        Me._lblADData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_15
        '
        Me._lblDataPoint_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_15.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_15.Location = New System.Drawing.Point(288, 90)
        Me._lblDataPoint_15.Name = "_lblDataPoint_15"
        Me._lblDataPoint_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_15.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_15.TabIndex = 34
        Me._lblDataPoint_15.Text = "15"
        Me._lblDataPoint_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_10
        '
        Me._lblADData_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_10.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_10.Location = New System.Drawing.Point(231, 90)
        Me._lblADData_10.Name = "_lblADData_10"
        Me._lblADData_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_10.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_10.TabIndex = 25
        Me._lblADData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_10
        '
        Me._lblDataPoint_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_10.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_10.Location = New System.Drawing.Point(199, 90)
        Me._lblDataPoint_10.Name = "_lblDataPoint_10"
        Me._lblDataPoint_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_10.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_10.TabIndex = 24
        Me._lblDataPoint_10.Text = "10"
        Me._lblDataPoint_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_5
        '
        Me._lblADData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_5.Location = New System.Drawing.Point(141, 90)
        Me._lblADData_5.Name = "_lblADData_5"
        Me._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_5.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_5.TabIndex = 7
        Me._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_5
        '
        Me._lblDataPoint_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_5.Location = New System.Drawing.Point(109, 90)
        Me._lblDataPoint_5.Name = "_lblDataPoint_5"
        Me._lblDataPoint_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_5.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_5.TabIndex = 19
        Me._lblDataPoint_5.Text = "5"
        Me._lblDataPoint_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblADData_0
        '
        Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblADData_0.Location = New System.Drawing.Point(52, 90)
        Me._lblADData_0.Name = "_lblADData_0"
        Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblADData_0.Size = New System.Drawing.Size(40, 14)
        Me._lblADData_0.TabIndex = 2
        Me._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblDataPoint_0
        '
        Me._lblDataPoint_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblDataPoint_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblDataPoint_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblDataPoint_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblDataPoint_0.Location = New System.Drawing.Point(20, 90)
        Me._lblDataPoint_0.Name = "_lblDataPoint_0"
        Me._lblDataPoint_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblDataPoint_0.Size = New System.Drawing.Size(33, 14)
        Me._lblDataPoint_0.TabIndex = 1
        Me._lblDataPoint_0.Text = "0"
        Me._lblDataPoint_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_7
        '
        Me._lblColTitle_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_7.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_7.Location = New System.Drawing.Point(327, 71)
        Me._lblColTitle_7.Name = "_lblColTitle_7"
        Me._lblColTitle_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_7.Size = New System.Drawing.Size(41, 14)
        Me._lblColTitle_7.TabIndex = 51
        Me._lblColTitle_7.Text = "Value"
        Me._lblColTitle_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_6
        '
        Me._lblColTitle_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_6.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_6.Location = New System.Drawing.Point(288, 71)
        Me._lblColTitle_6.Name = "_lblColTitle_6"
        Me._lblColTitle_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_6.Size = New System.Drawing.Size(33, 14)
        Me._lblColTitle_6.TabIndex = 50
        Me._lblColTitle_6.Text = "Data"
        Me._lblColTitle_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_5
        '
        Me._lblColTitle_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_5.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_5.Location = New System.Drawing.Point(237, 71)
        Me._lblColTitle_5.Name = "_lblColTitle_5"
        Me._lblColTitle_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_5.Size = New System.Drawing.Size(35, 14)
        Me._lblColTitle_5.TabIndex = 49
        Me._lblColTitle_5.Text = "Value"
        Me._lblColTitle_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_4
        '
        Me._lblColTitle_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_4.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_4.Location = New System.Drawing.Point(199, 71)
        Me._lblColTitle_4.Name = "_lblColTitle_4"
        Me._lblColTitle_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_4.Size = New System.Drawing.Size(33, 14)
        Me._lblColTitle_4.TabIndex = 48
        Me._lblColTitle_4.Text = "Data"
        Me._lblColTitle_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_3
        '
        Me._lblColTitle_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_3.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_3.Location = New System.Drawing.Point(148, 71)
        Me._lblColTitle_3.Name = "_lblColTitle_3"
        Me._lblColTitle_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_3.Size = New System.Drawing.Size(36, 14)
        Me._lblColTitle_3.TabIndex = 47
        Me._lblColTitle_3.Text = "Value"
        Me._lblColTitle_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_2
        '
        Me._lblColTitle_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_2.Location = New System.Drawing.Point(109, 71)
        Me._lblColTitle_2.Name = "_lblColTitle_2"
        Me._lblColTitle_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_2.Size = New System.Drawing.Size(33, 14)
        Me._lblColTitle_2.TabIndex = 46
        Me._lblColTitle_2.Text = "Data"
        Me._lblColTitle_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_1
        '
        Me._lblColTitle_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_1.Location = New System.Drawing.Point(58, 71)
        Me._lblColTitle_1.Name = "_lblColTitle_1"
        Me._lblColTitle_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_1.Size = New System.Drawing.Size(38, 14)
        Me._lblColTitle_1.TabIndex = 45
        Me._lblColTitle_1.Text = "Value"
        Me._lblColTitle_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblColTitle_0
        '
        Me._lblColTitle_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblColTitle_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblColTitle_0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblColTitle_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblColTitle_0.Location = New System.Drawing.Point(20, 71)
        Me._lblColTitle_0.Name = "_lblColTitle_0"
        Me._lblColTitle_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblColTitle_0.Size = New System.Drawing.Size(33, 14)
        Me._lblColTitle_0.TabIndex = 44
        Me._lblColTitle_0.Text = "Data"
        Me._lblColTitle_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
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
        Me.lblDemoFunction.Size = New System.Drawing.Size(337, 41)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.AInScan() with MccDaq.MccBoar.ExtMemory option"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(384, 255)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopConvert, Me.cmdReadMemBoard, Me.cmdStartConvert, Me._lblADData_19, Me._lblDataPoint_19, Me._lblADData_14, Me._lblDataPoint_14, Me._lblADData_9, Me._lblDataPoint_9, Me._lblADData_4, Me._lblDataPoint_4, Me._lblADData_18, Me._lblDataPoint_18, Me._lblADData_13, Me._lblDataPoint_13, Me._lblADData_8, Me._lblDataPoint_8, Me._lblADData_3, Me._lblDataPoint_3, Me._lblADData_17, Me._lblDataPoint_17, Me._lblADData_12, Me._lblDataPoint_12, Me._lblADData_7, Me._lblDataPoint_7, Me._lblADData_2, Me._lblDataPoint_2, Me._lblADData_16, Me._lblDataPoint_16, Me._lblADData_11, Me._lblDataPoint_11, Me._lblADData_6, Me._lblDataPoint_6, Me._lblADData_1, Me._lblDataPoint_1, Me._lblADData_15, Me._lblDataPoint_15, Me._lblADData_10, Me._lblDataPoint_10, Me._lblADData_5, Me._lblDataPoint_5, Me._lblADData_0, Me._lblDataPoint_0, Me._lblColTitle_7, Me._lblColTitle_6, Me._lblColTitle_5, Me._lblColTitle_4, Me._lblColTitle_3, Me._lblColTitle_2, Me._lblColTitle_1, Me._lblColTitle_0, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Input Scan"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ULStat As MccDaq.ErrorInfo

        lblADData = New System.Windows.Forms.Label(20) {}
        lblDataPoint = New System.Windows.Forms.Label(20) {}

        Me.lblADData.SetValue(_lblADData_19, 19)
        Me.lblADData.SetValue(_lblADData_14, 14)
        Me.lblADData.SetValue(_lblADData_9, 9)
        Me.lblADData.SetValue(_lblADData_4, 4)
        Me.lblADData.SetValue(_lblADData_18, 18)
        Me.lblADData.SetValue(_lblADData_13, 13)
        Me.lblADData.SetValue(_lblADData_8, 8)
        Me.lblADData.SetValue(_lblADData_3, 3)
        Me.lblADData.SetValue(_lblADData_17, 17)
        Me.lblADData.SetValue(_lblADData_12, 12)
        Me.lblADData.SetValue(_lblADData_7, 7)
        Me.lblADData.SetValue(_lblADData_2, 2)
        Me.lblADData.SetValue(_lblADData_16, 16)
        Me.lblADData.SetValue(_lblADData_11, 11)
        Me.lblADData.SetValue(_lblADData_6, 6)
        Me.lblADData.SetValue(_lblADData_1, 1)
        Me.lblADData.SetValue(_lblADData_15, 15)
        Me.lblADData.SetValue(_lblADData_10, 10)
        Me.lblADData.SetValue(_lblADData_5, 5)
        Me.lblADData.SetValue(_lblADData_0, 0)
        Me.lblDataPoint.SetValue(_lblDataPoint_19, 19)
        Me.lblDataPoint.SetValue(_lblDataPoint_14, 14)
        Me.lblDataPoint.SetValue(_lblDataPoint_9, 9)
        Me.lblDataPoint.SetValue(_lblDataPoint_4, 4)
        Me.lblDataPoint.SetValue(_lblDataPoint_18, 18)
        Me.lblDataPoint.SetValue(_lblDataPoint_13, 13)
        Me.lblDataPoint.SetValue(_lblDataPoint_8, 8)
        Me.lblDataPoint.SetValue(_lblDataPoint_3, 3)
        Me.lblDataPoint.SetValue(_lblDataPoint_17, 17)
        Me.lblDataPoint.SetValue(_lblDataPoint_12, 12)
        Me.lblDataPoint.SetValue(_lblDataPoint_7, 7)
        Me.lblDataPoint.SetValue(_lblDataPoint_2, 2)
        Me.lblDataPoint.SetValue(_lblDataPoint_16, 16)
        Me.lblDataPoint.SetValue(_lblDataPoint_11, 11)
        Me.lblDataPoint.SetValue(_lblDataPoint_6, 6)
        Me.lblDataPoint.SetValue(_lblDataPoint_1, 1)
        Me.lblDataPoint.SetValue(_lblDataPoint_15, 15)
        Me.lblDataPoint.SetValue(_lblDataPoint_10, 10)
        Me.lblDataPoint.SetValue(_lblDataPoint_5, 5)
        Me.lblDataPoint.SetValue(_lblDataPoint_0, 0)

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

        PointNum = 0
        FirstPoint = 0 ' Set address of first point to read


    End Sub
#End Region

End Class