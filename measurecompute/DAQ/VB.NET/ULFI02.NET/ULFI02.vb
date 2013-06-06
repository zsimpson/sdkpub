'==============================================================================

' File:                         ULFI02.VB

' Library Call Demonstrated:    File Operations:
'                               MccDaq.MccService.FileRead()
'                               MccDaq.MccService.FileGetInfo()

' Purpose:                      Read information & data from a streamer file.

' Demonstration:                Creates a file and scans analog data to the
'                               file. Displays the data in the file and the
'                               information in the file header.

' Other Library Calls:          Mccdaq.MccBoard.FileAInScan()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must be capable of MccDaq.MccScanOpions.BlockIo
'                               MccDaq.MccScanOpions.BlockIoDEMO.DAT file 
'                               should have been already created with MAKESTRM program.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmShowFileData
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 128000 ' Number of data points to collect
    Const ArraySize As Integer = 10 ' size of Visual Basics data array

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim DataBuffer(ArraySize) As UInt16 ' dimension Visual Basics data array
    Dim FileName As String ' name of file in which data will be stored

    Public lblShowData As System.Windows.Forms.Label()

    Private Sub cmdShowData_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdShowData.Click
        Dim I As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim ReadPoints As Integer
        Dim FirstPoint As Integer

        ' show the data using MccDaq.MccService.FileRead()
        '  Parameters:
        '    FileName      :the filename containing the data
        '    FirstPoint    :index of the first data value to read
        '    NumPoints     :the number of data values to read from the file
        '    DataBuffer()  :array to read data into

        FirstPoint = 0 ' start at the first point
        ReadPoints = ArraySize ' specify number of data points to read

        ULStat = MccDaq.MccService.FileRead(FileName, FirstPoint, ReadPoints, DataBuffer(0))
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' display the data values read from the file

        For I = FirstPoint To ArraySize - 1
            lblShowData(I).Text = DataBuffer(I).ToString("0")
        Next I

    End Sub

    Private Sub cmdStartAcq_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartAcq.Click
        Dim Range As MccDaq.Range
        Dim TotalCount As Integer
        Dim PretrigCount As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataCount As String
        Dim Options As MccDaq.ScanOptions
        Dim HighChan As Integer
        Dim LowChan As Integer
        Dim Rate As Integer
        Dim Count As Integer
        Dim FileHighChan As Short
        Dim FileLowChan As Short

        cmdStartAcq.Enabled = False

        ' Parameters:
        Count = NumPoints
        FileName = txtFileName.Text ' it may be necessary to add path to
        Rate = 50000 ' file name for data file to be found
        LowChan = 0
        HighChan = 0
        Options = MccDaq.ScanOptions.Default
        Range = MccDaq.Range.Bip5Volts 'set the range

        DataCount = NumPoints.ToString("0")
        lblAcqStat.Text = "Collecting " & DataCount & " data points"
        lblShowRate.Text = Rate.ToString("0")
        lblShowLoChan.Text = LowChan.ToString("0")
        lblShowHiChan.Text = HighChan.ToString("0")
        lblShowOptions.Text = Options.ToString()
        lblShowGain.Text = Range.ToString()
        lblShowFile.Text = FileName
        lblShowCount.Text = Count.ToString("0")

        ' Collect the values with MccDaq.MccBoard.FileAInScan()
        '  Parameters:
        '    LowChan    :first A/D channel of the scan
        '    HighChan   :last A/D channel of the scan
        '    Count    :the total number of A/D samples to collect
        '    Rate     :Sample rate
        '    Range       :the gain for the board
        '    FileName   :the filename for the collected data values
        '    Options    :data collection options

        ULStat = DaqBoard.FileAInScan(LowChan, HighChan, Count, Rate, Range, FileName, Options)
        If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadFileName Then
            MsgBox("Enter the name of the file you created with 'MAKESTRM.EXE' in text box.", 0, "Bad File Name")
            cmdStartAcq.Enabled = True
            cmdStartAcq.Visible = True
            txtFileName.Focus()
            Exit Sub
        ElseIf ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If

        ' show how many data points were collected

        ULStat = MccDaq.MccService.FileGetInfo(FileName, FileLowChan, FileHighChan, PretrigCount, TotalCount, Rate, Range)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblShowRate.Text = Rate.ToString("0")
        lblShowLoChan.Text = FileLowChan.ToString("0")
        lblShowHiChan.Text = FileHighChan.ToString("0")
        lblShowOptions.Text = Options.ToString()
        lblShowGain.Text = Range.ToString()
        lblShowFile.Text = FileName

        lblShowTotal.Text = TotalCount.ToString("0")
        lblShowPreTrig.Text = PretrigCount.ToString("0")

        cmdShowData.Enabled = True
        cmdShowData.Visible = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click
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
    Public WithEvents cmdShowData As System.Windows.Forms.Button
    Public WithEvents cmdStartAcq As System.Windows.Forms.Button
    Public WithEvents txtFileName As System.Windows.Forms.TextBox
    Public WithEvents lblFileInstruct As System.Windows.Forms.Label
    Public WithEvents lblShowFile As System.Windows.Forms.Label
    Public WithEvents lblFileName As System.Windows.Forms.Label
    Public WithEvents _lblShowData_9 As System.Windows.Forms.Label
    Public WithEvents lblData9 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_8 As System.Windows.Forms.Label
    Public WithEvents lblData8 As System.Windows.Forms.Label
    Public WithEvents lblShowPreTrig As System.Windows.Forms.Label
    Public WithEvents lblPreTrig As System.Windows.Forms.Label
    Public WithEvents _lblShowData_7 As System.Windows.Forms.Label
    Public WithEvents lblData7 As System.Windows.Forms.Label
    Public WithEvents lblShowTotal As System.Windows.Forms.Label
    Public WithEvents lblTotal As System.Windows.Forms.Label
    Public WithEvents _lblShowData_6 As System.Windows.Forms.Label
    Public WithEvents lblData6 As System.Windows.Forms.Label
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents _lblShowData_5 As System.Windows.Forms.Label
    Public WithEvents lblData5 As System.Windows.Forms.Label
    Public WithEvents lblShowGain As System.Windows.Forms.Label
    Public WithEvents lblGain As System.Windows.Forms.Label
    Public WithEvents _lblShowData_4 As System.Windows.Forms.Label
    Public WithEvents lblData4 As System.Windows.Forms.Label
    Public WithEvents lblShowOptions As System.Windows.Forms.Label
    Public WithEvents lblOptions As System.Windows.Forms.Label
    Public WithEvents _lblShowData_3 As System.Windows.Forms.Label
    Public WithEvents lblData3 As System.Windows.Forms.Label
    Public WithEvents lblShowHiChan As System.Windows.Forms.Label
    Public WithEvents lblHiChan As System.Windows.Forms.Label
    Public WithEvents _lblShowData_2 As System.Windows.Forms.Label
    Public WithEvents lblData2 As System.Windows.Forms.Label
    Public WithEvents lblShowLoChan As System.Windows.Forms.Label
    Public WithEvents lblLoChan As System.Windows.Forms.Label
    Public WithEvents _lblShowData_1 As System.Windows.Forms.Label
    Public WithEvents lblData1 As System.Windows.Forms.Label
    Public WithEvents lblShowRate As System.Windows.Forms.Label
    Public WithEvents lblRate As System.Windows.Forms.Label
    Public WithEvents _lblShowData_0 As System.Windows.Forms.Label
    Public WithEvents lblData0 As System.Windows.Forms.Label
    Public WithEvents lblAcqStat As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdShowData = New System.Windows.Forms.Button()
        Me.cmdStartAcq = New System.Windows.Forms.Button()
        Me.txtFileName = New System.Windows.Forms.TextBox()
        Me.lblFileInstruct = New System.Windows.Forms.Label()
        Me.lblShowFile = New System.Windows.Forms.Label()
        Me.lblFileName = New System.Windows.Forms.Label()
        Me._lblShowData_9 = New System.Windows.Forms.Label()
        Me.lblData9 = New System.Windows.Forms.Label()
        Me._lblShowData_8 = New System.Windows.Forms.Label()
        Me.lblData8 = New System.Windows.Forms.Label()
        Me.lblShowPreTrig = New System.Windows.Forms.Label()
        Me.lblPreTrig = New System.Windows.Forms.Label()
        Me._lblShowData_7 = New System.Windows.Forms.Label()
        Me.lblData7 = New System.Windows.Forms.Label()
        Me.lblShowTotal = New System.Windows.Forms.Label()
        Me.lblTotal = New System.Windows.Forms.Label()
        Me._lblShowData_6 = New System.Windows.Forms.Label()
        Me.lblData6 = New System.Windows.Forms.Label()
        Me.lblShowCount = New System.Windows.Forms.Label()
        Me.lblCount = New System.Windows.Forms.Label()
        Me._lblShowData_5 = New System.Windows.Forms.Label()
        Me.lblData5 = New System.Windows.Forms.Label()
        Me.lblShowGain = New System.Windows.Forms.Label()
        Me.lblGain = New System.Windows.Forms.Label()
        Me._lblShowData_4 = New System.Windows.Forms.Label()
        Me.lblData4 = New System.Windows.Forms.Label()
        Me.lblShowOptions = New System.Windows.Forms.Label()
        Me.lblOptions = New System.Windows.Forms.Label()
        Me._lblShowData_3 = New System.Windows.Forms.Label()
        Me.lblData3 = New System.Windows.Forms.Label()
        Me.lblShowHiChan = New System.Windows.Forms.Label()
        Me.lblHiChan = New System.Windows.Forms.Label()
        Me._lblShowData_2 = New System.Windows.Forms.Label()
        Me.lblData2 = New System.Windows.Forms.Label()
        Me.lblShowLoChan = New System.Windows.Forms.Label()
        Me.lblLoChan = New System.Windows.Forms.Label()
        Me._lblShowData_1 = New System.Windows.Forms.Label()
        Me.lblData1 = New System.Windows.Forms.Label()
        Me.lblShowRate = New System.Windows.Forms.Label()
        Me.lblRate = New System.Windows.Forms.Label()
        Me._lblShowData_0 = New System.Windows.Forms.Label()
        Me.lblData0 = New System.Windows.Forms.Label()
        Me.lblAcqStat = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(288, 296)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(46, 26)
        Me.cmdStopConvert.TabIndex = 17
        Me.cmdStopConvert.Text = "Quit"
        '
        'cmdShowData
        '
        Me.cmdShowData.BackColor = System.Drawing.SystemColors.Control
        Me.cmdShowData.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdShowData.Enabled = False
        Me.cmdShowData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdShowData.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdShowData.Location = New System.Drawing.Point(184, 296)
        Me.cmdShowData.Name = "cmdShowData"
        Me.cmdShowData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdShowData.Size = New System.Drawing.Size(84, 26)
        Me.cmdShowData.TabIndex = 29
        Me.cmdShowData.Text = "Display Data"
        Me.cmdShowData.Visible = False
        '
        'cmdStartAcq
        '
        Me.cmdStartAcq.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartAcq.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartAcq.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartAcq.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartAcq.Location = New System.Drawing.Point(184, 296)
        Me.cmdStartAcq.Name = "cmdStartAcq"
        Me.cmdStartAcq.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartAcq.Size = New System.Drawing.Size(84, 26)
        Me.cmdStartAcq.TabIndex = 18
        Me.cmdStartAcq.Text = "Start"
        '
        'txtFileName
        '
        Me.txtFileName.AcceptsReturn = True
        Me.txtFileName.AutoSize = False
        Me.txtFileName.BackColor = System.Drawing.SystemColors.Window
        Me.txtFileName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtFileName.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtFileName.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtFileName.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtFileName.Location = New System.Drawing.Point(176, 256)
        Me.txtFileName.MaxLength = 0
        Me.txtFileName.Name = "txtFileName"
        Me.txtFileName.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtFileName.Size = New System.Drawing.Size(161, 25)
        Me.txtFileName.TabIndex = 44
        Me.txtFileName.Text = "DEMO.DAT"
        '
        'lblFileInstruct
        '
        Me.lblFileInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblFileInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFileInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFileInstruct.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFileInstruct.Location = New System.Drawing.Point(0, 240)
        Me.lblFileInstruct.Name = "lblFileInstruct"
        Me.lblFileInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFileInstruct.Size = New System.Drawing.Size(169, 41)
        Me.lblFileInstruct.TabIndex = 43
        Me.lblFileInstruct.Text = "Enter the name of the file that you have created using MAKESTRM.EXE"
        Me.lblFileInstruct.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowFile
        '
        Me.lblShowFile.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowFile.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowFile.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowFile.ForeColor = System.Drawing.Color.Blue
        Me.lblShowFile.Location = New System.Drawing.Point(109, 211)
        Me.lblShowFile.Name = "lblShowFile"
        Me.lblShowFile.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowFile.Size = New System.Drawing.Size(174, 18)
        Me.lblShowFile.TabIndex = 25
        '
        'lblFileName
        '
        Me.lblFileName.BackColor = System.Drawing.SystemColors.Window
        Me.lblFileName.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFileName.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFileName.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFileName.Location = New System.Drawing.Point(26, 212)
        Me.lblFileName.Name = "lblFileName"
        Me.lblFileName.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFileName.Size = New System.Drawing.Size(72, 14)
        Me.lblFileName.TabIndex = 42
        Me.lblFileName.Text = "File Name:"
        Me.lblFileName.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_9
        '
        Me._lblShowData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_9.Location = New System.Drawing.Point(288, 186)
        Me._lblShowData_9.Name = "_lblShowData_9"
        Me._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_9.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_9.TabIndex = 33
        '
        'lblData9
        '
        Me.lblData9.BackColor = System.Drawing.SystemColors.Window
        Me.lblData9.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData9.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData9.Location = New System.Drawing.Point(189, 186)
        Me.lblData9.Name = "lblData9"
        Me.lblData9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData9.Size = New System.Drawing.Size(87, 14)
        Me.lblData9.TabIndex = 31
        Me.lblData9.Text = "Data Point 9:"
        Me.lblData9.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_8
        '
        Me._lblShowData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_8.Location = New System.Drawing.Point(288, 173)
        Me._lblShowData_8.Name = "_lblShowData_8"
        Me._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_8.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_8.TabIndex = 32
        '
        'lblData8
        '
        Me.lblData8.BackColor = System.Drawing.SystemColors.Window
        Me.lblData8.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData8.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData8.Location = New System.Drawing.Point(189, 173)
        Me.lblData8.Name = "lblData8"
        Me.lblData8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData8.Size = New System.Drawing.Size(87, 14)
        Me.lblData8.TabIndex = 30
        Me.lblData8.Text = "Data Point 8:"
        Me.lblData8.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowPreTrig
        '
        Me.lblShowPreTrig.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowPreTrig.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowPreTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowPreTrig.ForeColor = System.Drawing.Color.Blue
        Me.lblShowPreTrig.Location = New System.Drawing.Point(109, 167)
        Me.lblShowPreTrig.Name = "lblShowPreTrig"
        Me.lblShowPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowPreTrig.Size = New System.Drawing.Size(46, 14)
        Me.lblShowPreTrig.TabIndex = 28
        '
        'lblPreTrig
        '
        Me.lblPreTrig.BackColor = System.Drawing.SystemColors.Window
        Me.lblPreTrig.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPreTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPreTrig.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPreTrig.Location = New System.Drawing.Point(13, 167)
        Me.lblPreTrig.Name = "lblPreTrig"
        Me.lblPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPreTrig.Size = New System.Drawing.Size(84, 14)
        Me.lblPreTrig.TabIndex = 41
        Me.lblPreTrig.Text = "PreTrig Count:"
        Me.lblPreTrig.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_7
        '
        Me._lblShowData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_7.Location = New System.Drawing.Point(288, 160)
        Me._lblShowData_7.Name = "_lblShowData_7"
        Me._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_7.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_7.TabIndex = 16
        '
        'lblData7
        '
        Me.lblData7.BackColor = System.Drawing.SystemColors.Window
        Me.lblData7.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData7.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData7.Location = New System.Drawing.Point(189, 160)
        Me.lblData7.Name = "lblData7"
        Me.lblData7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData7.Size = New System.Drawing.Size(87, 14)
        Me.lblData7.TabIndex = 8
        Me.lblData7.Text = "Data Point 7:"
        Me.lblData7.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowTotal
        '
        Me.lblShowTotal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowTotal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowTotal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowTotal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowTotal.Location = New System.Drawing.Point(109, 154)
        Me.lblShowTotal.Name = "lblShowTotal"
        Me.lblShowTotal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowTotal.Size = New System.Drawing.Size(46, 18)
        Me.lblShowTotal.TabIndex = 27
        '
        'lblTotal
        '
        Me.lblTotal.BackColor = System.Drawing.SystemColors.Window
        Me.lblTotal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblTotal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblTotal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblTotal.Location = New System.Drawing.Point(26, 154)
        Me.lblTotal.Name = "lblTotal"
        Me.lblTotal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblTotal.Size = New System.Drawing.Size(72, 14)
        Me.lblTotal.TabIndex = 40
        Me.lblTotal.Text = "Total Count:"
        Me.lblTotal.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_6
        '
        Me._lblShowData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_6.Location = New System.Drawing.Point(288, 148)
        Me._lblShowData_6.Name = "_lblShowData_6"
        Me._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_6.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_6.TabIndex = 15
        '
        'lblData6
        '
        Me.lblData6.BackColor = System.Drawing.SystemColors.Window
        Me.lblData6.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData6.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData6.Location = New System.Drawing.Point(189, 147)
        Me.lblData6.Name = "lblData6"
        Me.lblData6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData6.Size = New System.Drawing.Size(87, 14)
        Me.lblData6.TabIndex = 7
        Me.lblData6.Text = "Data Point 6:"
        Me.lblData6.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowCount
        '
        Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCount.Location = New System.Drawing.Point(109, 141)
        Me.lblShowCount.Name = "lblShowCount"
        Me.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCount.Size = New System.Drawing.Size(46, 18)
        Me.lblShowCount.TabIndex = 26
        '
        'lblCount
        '
        Me.lblCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCount.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCount.Location = New System.Drawing.Point(32, 141)
        Me.lblCount.Name = "lblCount"
        Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCount.Size = New System.Drawing.Size(65, 14)
        Me.lblCount.TabIndex = 39
        Me.lblCount.Text = "Count:"
        Me.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_5
        '
        Me._lblShowData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_5.Location = New System.Drawing.Point(288, 135)
        Me._lblShowData_5.Name = "_lblShowData_5"
        Me._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_5.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_5.TabIndex = 14
        '
        'lblData5
        '
        Me.lblData5.BackColor = System.Drawing.SystemColors.Window
        Me.lblData5.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData5.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData5.Location = New System.Drawing.Point(189, 134)
        Me.lblData5.Name = "lblData5"
        Me.lblData5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData5.Size = New System.Drawing.Size(87, 14)
        Me.lblData5.TabIndex = 6
        Me.lblData5.Text = "Data Point 5:"
        Me.lblData5.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowGain
        '
        Me.lblShowGain.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowGain.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowGain.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowGain.ForeColor = System.Drawing.Color.Blue
        Me.lblShowGain.Location = New System.Drawing.Point(109, 128)
        Me.lblShowGain.Name = "lblShowGain"
        Me.lblShowGain.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowGain.Size = New System.Drawing.Size(46, 18)
        Me.lblShowGain.TabIndex = 24
        '
        'lblGain
        '
        Me.lblGain.BackColor = System.Drawing.SystemColors.Window
        Me.lblGain.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblGain.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblGain.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblGain.Location = New System.Drawing.Point(32, 128)
        Me.lblGain.Name = "lblGain"
        Me.lblGain.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblGain.Size = New System.Drawing.Size(65, 14)
        Me.lblGain.TabIndex = 38
        Me.lblGain.Text = "Gain:"
        Me.lblGain.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_4
        '
        Me._lblShowData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_4.Location = New System.Drawing.Point(288, 122)
        Me._lblShowData_4.Name = "_lblShowData_4"
        Me._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_4.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_4.TabIndex = 13
        '
        'lblData4
        '
        Me.lblData4.BackColor = System.Drawing.SystemColors.Window
        Me.lblData4.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData4.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData4.Location = New System.Drawing.Point(189, 122)
        Me.lblData4.Name = "lblData4"
        Me.lblData4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData4.Size = New System.Drawing.Size(87, 14)
        Me.lblData4.TabIndex = 5
        Me.lblData4.Text = "Data Point 4:"
        Me.lblData4.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowOptions
        '
        Me.lblShowOptions.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowOptions.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowOptions.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowOptions.ForeColor = System.Drawing.Color.Blue
        Me.lblShowOptions.Location = New System.Drawing.Point(109, 115)
        Me.lblShowOptions.Name = "lblShowOptions"
        Me.lblShowOptions.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowOptions.Size = New System.Drawing.Size(46, 18)
        Me.lblShowOptions.TabIndex = 23
        '
        'lblOptions
        '
        Me.lblOptions.BackColor = System.Drawing.SystemColors.Window
        Me.lblOptions.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblOptions.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblOptions.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblOptions.Location = New System.Drawing.Point(32, 116)
        Me.lblOptions.Name = "lblOptions"
        Me.lblOptions.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblOptions.Size = New System.Drawing.Size(65, 14)
        Me.lblOptions.TabIndex = 37
        Me.lblOptions.Text = "Options:"
        Me.lblOptions.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_3
        '
        Me._lblShowData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_3.Location = New System.Drawing.Point(288, 109)
        Me._lblShowData_3.Name = "_lblShowData_3"
        Me._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_3.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_3.TabIndex = 12
        '
        'lblData3
        '
        Me.lblData3.BackColor = System.Drawing.SystemColors.Window
        Me.lblData3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData3.Location = New System.Drawing.Point(189, 109)
        Me.lblData3.Name = "lblData3"
        Me.lblData3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData3.Size = New System.Drawing.Size(87, 14)
        Me.lblData3.TabIndex = 4
        Me.lblData3.Text = "Data Point 3:"
        Me.lblData3.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowHiChan
        '
        Me.lblShowHiChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowHiChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowHiChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowHiChan.ForeColor = System.Drawing.Color.Blue
        Me.lblShowHiChan.Location = New System.Drawing.Point(109, 102)
        Me.lblShowHiChan.Name = "lblShowHiChan"
        Me.lblShowHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowHiChan.Size = New System.Drawing.Size(46, 18)
        Me.lblShowHiChan.TabIndex = 22
        '
        'lblHiChan
        '
        Me.lblHiChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblHiChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblHiChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblHiChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblHiChan.Location = New System.Drawing.Point(13, 103)
        Me.lblHiChan.Name = "lblHiChan"
        Me.lblHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblHiChan.Size = New System.Drawing.Size(84, 14)
        Me.lblHiChan.TabIndex = 36
        Me.lblHiChan.Text = "High Channel:"
        Me.lblHiChan.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_2
        '
        Me._lblShowData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_2.Location = New System.Drawing.Point(288, 96)
        Me._lblShowData_2.Name = "_lblShowData_2"
        Me._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_2.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_2.TabIndex = 11
        '
        'lblData2
        '
        Me.lblData2.BackColor = System.Drawing.SystemColors.Window
        Me.lblData2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData2.Location = New System.Drawing.Point(189, 96)
        Me.lblData2.Name = "lblData2"
        Me.lblData2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData2.Size = New System.Drawing.Size(87, 14)
        Me.lblData2.TabIndex = 3
        Me.lblData2.Text = "Data Point 2:"
        Me.lblData2.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowLoChan
        '
        Me.lblShowLoChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowLoChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowLoChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowLoChan.ForeColor = System.Drawing.Color.Blue
        Me.lblShowLoChan.Location = New System.Drawing.Point(109, 90)
        Me.lblShowLoChan.Name = "lblShowLoChan"
        Me.lblShowLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowLoChan.Size = New System.Drawing.Size(46, 18)
        Me.lblShowLoChan.TabIndex = 21
        '
        'lblLoChan
        '
        Me.lblLoChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblLoChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblLoChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblLoChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblLoChan.Location = New System.Drawing.Point(13, 90)
        Me.lblLoChan.Name = "lblLoChan"
        Me.lblLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblLoChan.Size = New System.Drawing.Size(84, 14)
        Me.lblLoChan.TabIndex = 35
        Me.lblLoChan.Text = "Low Channel:"
        Me.lblLoChan.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_1
        '
        Me._lblShowData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_1.Location = New System.Drawing.Point(288, 84)
        Me._lblShowData_1.Name = "_lblShowData_1"
        Me._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_1.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_1.TabIndex = 10
        '
        'lblData1
        '
        Me.lblData1.BackColor = System.Drawing.SystemColors.Window
        Me.lblData1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData1.Location = New System.Drawing.Point(189, 83)
        Me.lblData1.Name = "lblData1"
        Me.lblData1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData1.Size = New System.Drawing.Size(87, 14)
        Me.lblData1.TabIndex = 2
        Me.lblData1.Text = "Data Point 1:"
        Me.lblData1.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowRate
        '
        Me.lblShowRate.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowRate.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowRate.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowRate.ForeColor = System.Drawing.Color.Blue
        Me.lblShowRate.Location = New System.Drawing.Point(109, 77)
        Me.lblShowRate.Name = "lblShowRate"
        Me.lblShowRate.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowRate.Size = New System.Drawing.Size(46, 18)
        Me.lblShowRate.TabIndex = 20
        '
        'lblRate
        '
        Me.lblRate.BackColor = System.Drawing.SystemColors.Window
        Me.lblRate.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblRate.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblRate.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblRate.Location = New System.Drawing.Point(32, 77)
        Me.lblRate.Name = "lblRate"
        Me.lblRate.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblRate.Size = New System.Drawing.Size(65, 14)
        Me.lblRate.TabIndex = 34
        Me.lblRate.Text = "Rate:"
        Me.lblRate.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblShowData_0
        '
        Me._lblShowData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_0.Location = New System.Drawing.Point(288, 71)
        Me._lblShowData_0.Name = "_lblShowData_0"
        Me._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_0.Size = New System.Drawing.Size(46, 14)
        Me._lblShowData_0.TabIndex = 9
        '
        'lblData0
        '
        Me.lblData0.BackColor = System.Drawing.SystemColors.Window
        Me.lblData0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData0.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData0.Location = New System.Drawing.Point(189, 70)
        Me.lblData0.Name = "lblData0"
        Me.lblData0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData0.Size = New System.Drawing.Size(87, 14)
        Me.lblData0.TabIndex = 1
        Me.lblData0.Text = "Data Point 0:"
        Me.lblData0.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblAcqStat
        '
        Me.lblAcqStat.BackColor = System.Drawing.SystemColors.Window
        Me.lblAcqStat.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblAcqStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblAcqStat.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblAcqStat.Location = New System.Drawing.Point(71, 39)
        Me.lblAcqStat.Name = "lblAcqStat"
        Me.lblAcqStat.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblAcqStat.Size = New System.Drawing.Size(225, 14)
        Me.lblAcqStat.TabIndex = 19
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
        Me.lblDemoFunction.Size = New System.Drawing.Size(335, 22)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.FileAInScan()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmShowFileData
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(349, 328)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopConvert, Me.cmdShowData, Me.cmdStartAcq, Me.txtFileName, Me.lblFileInstruct, Me.lblShowFile, Me.lblFileName, Me._lblShowData_9, Me.lblData9, Me._lblShowData_8, Me.lblData8, Me.lblShowPreTrig, Me.lblPreTrig, Me._lblShowData_7, Me.lblData7, Me.lblShowTotal, Me.lblTotal, Me._lblShowData_6, Me.lblData6, Me.lblShowCount, Me.lblCount, Me._lblShowData_5, Me.lblData5, Me.lblShowGain, Me.lblGain, Me._lblShowData_4, Me.lblData4, Me.lblShowOptions, Me.lblOptions, Me._lblShowData_3, Me.lblData3, Me.lblShowHiChan, Me.lblHiChan, Me._lblShowData_2, Me.lblData2, Me.lblShowLoChan, Me.lblLoChan, Me._lblShowData_1, Me.lblData1, Me.lblShowRate, Me.lblRate, Me._lblShowData_0, Me.lblData0, Me.lblAcqStat, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmShowFileData"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Input to File"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        Me.lblShowData = New System.Windows.Forms.Label(10) {}
        Me.lblShowData.SetValue(_lblShowData_9, 9)
        Me.lblShowData.SetValue(_lblShowData_8, 8)
        Me.lblShowData.SetValue(_lblShowData_7, 7)
        Me.lblShowData.SetValue(_lblShowData_6, 6)
        Me.lblShowData.SetValue(_lblShowData_5, 5)
        Me.lblShowData.SetValue(_lblShowData_4, 4)
        Me.lblShowData.SetValue(_lblShowData_3, 3)
        Me.lblShowData.SetValue(_lblShowData_2, 2)
        Me.lblShowData.SetValue(_lblShowData_1, 1)
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

    End Sub
#End Region

End Class