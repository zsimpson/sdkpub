'==============================================================================

' File:                         ULAI09.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AConvertPretrigData()

' Purpose:                      Waits for a trigger with Mccdaq.MccBoard.APretrig(), then
'                               uses Mccdaq.MccBoard.AConvertPretrigData() to convert
'                               the data.

' Demonstration:                Displays the analog input on one channel and
'                               waits for the trigger.

' Other Library Calls:          Mccdaq.MccBoard.APretrig()
'                               Mccdaq.MccBoard.GetStatus()
'                               Mccdaq.MccBoard.StopBackground()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must support pre/post triggering

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmPreTrig
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 600 ' Number of data points to collect
    Const FirstPoint As Integer = 0 ' set first element in buffer to transfer to array
    Const PretrigCount As Integer = 10 ' number of data points before the trigger to store
    Const TotalCount As Integer = NumPoints ' total number of data points to collect
    Const BufSize As Integer = 1112 ' buffer must be large enough to hold all data

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

  
    Dim MemHandle As Integer ' define a variable to contain the handle for
                             ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()

    Dim ADData(BufSize) As UInt16 ' dimension an array to hold the input values

    ' size must be TotalCount + 512 minimum
    Dim ChanTags(BufSize) As UInt16 ' dimension an array to hold the channel tag values

    Public lblPostTrig As System.Windows.Forms.Label()
    Public lblPreTrig As System.Windows.Forms.Label()

    Private Sub tmrCheckStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrCheckStatus.Tick
        Dim i As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short

        tmrCheckStatus.Stop()
        ' This timer will check the status of the background data collection

        ' Parameters:
        '   Status     :current status of the background data collection
        '   CurCount   :current number of samples collected
        '   CurIndex   :index to the data buffer pointing to the start of the
        '                most recently collected scan
        '   FunctionType:A/D operation (MccDaq.FunctionType.AiFunction)

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.AiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblShowCount.Text = CurCount.ToString("D")
        lblShowIndex.Text = CurIndex.ToString("D")

        ' Check if the background operation has finished. If it has, then
        ' transfer the data from the memory buffer set up by Windows to an
        ' array for use by Visual Basic
        ' The BACKGROUND operation must be explicitly stopped

        If Status = MccDaq.MccBoard.Running Then
            lblShowStat.Text = "Running"
            tmrCheckStatus.Start()
        ElseIf Status = MccDaq.MccBoard.Idle Then
            lblShowStat.Text = "Idle"

            ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.AiFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")

            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            If MemHandle = 0 Then Stop

            ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

            ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, NumPoints)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            ' convert the data using MccDaq.MccBoard.AConvertPretrigData()

            ' Parameters:
            '   PretrigCount  :number of pre-trigger A/D samples collected
            '                   actual value is returned by Mccdaq.MccBoard.APretrig()
            '   TotalCount    :total number of A/D samples collected
            '                   actual value is returned by Mccdaq.MccBoard.APretrig()
            '   ADData        :the array containing the raw data values
            '   ChanTags      :array that chan tags will be returned to

            ULStat = DaqBoard.AConvertPretrigData(PretrigCount, TotalCount, ADData(0), ChanTags(0))
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            For i = 0 To PretrigCount - 1
                lblPreTrig(i).Text = ADData(i).ToString("D")
            Next i
            For i = 1 To 10
                lblPostTrig(i).Text = ADData(PretrigCount + i).ToString("D")
            Next i
            
        End If


    End Sub

    Private Sub cmdStartPrePostTrig_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartPrePostTrig.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim Options As MccDaq.ScanOptions
        Dim Range As MccDaq.Range
        Dim Rate As Integer
        Dim HighChan As Integer
        Dim LowChan As Integer

        ' Monitor a range of channels for a trigger then collect the values
        ' with MccDaq.MccBoard.APretrig()

        ' Parameters:
        '   LowChan       :first A/D channel of the scan
        '   HighChan      :last A/D channel of the scan
        '   PretrigCount  :number of pre-trigger A/D samples to collect
        '   TotalCount    :total number of A/D samples to collect
        '   Rate          :sample rate in samples per second
        '   Range         :the range for the board
        '   MemHandle     :Handle for Windows buffer to store data in 
        '   Options       :data collection options

        LowChan = 0       ' first channel
        HighChan = 0      ' last channel
        Rate = 200        ' per channel sampling rate ((samples per second) per channel)
        Range = MccDaq.Range.Bip5Volts ' set the range
        Options = MccDaq.ScanOptions.Background ' collect data in the background

        ULStat = DaqBoard.APretrig(LowChan, HighChan, PretrigCount, TotalCount, Rate, Range, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        Else
            tmrCheckStatus.Enabled = True
            cmdStartPrePostTrig.Enabled = False
        End If



    End Sub

    Private Sub cmdQuit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdQuit.Click
        Dim ULStat As MccDaq.ErrorInfo

        ' The BACKGROUND operation must be explicitly stopped
        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

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
    Public WithEvents cmdQuit As System.Windows.Forms.Button
    Public WithEvents tmrCheckStatus As System.Windows.Forms.Timer
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblShowIndex As System.Windows.Forms.Label
    Public WithEvents lblIndex As System.Windows.Forms.Label
    Public WithEvents lblShowStat As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_10 As System.Windows.Forms.Label
    Public WithEvents lblPost10 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_9 As System.Windows.Forms.Label
    Public WithEvents lblPre1 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_9 As System.Windows.Forms.Label
    Public WithEvents lblPost9 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_8 As System.Windows.Forms.Label
    Public WithEvents lblPre2 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_8 As System.Windows.Forms.Label
    Public WithEvents lblPost8 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_7 As System.Windows.Forms.Label
    Public WithEvents lblPre3 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_7 As System.Windows.Forms.Label
    Public WithEvents lblPost7 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_6 As System.Windows.Forms.Label
    Public WithEvents lblPre4 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_6 As System.Windows.Forms.Label
    Public WithEvents lblPost6 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_5 As System.Windows.Forms.Label
    Public WithEvents lblPre5 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_5 As System.Windows.Forms.Label
    Public WithEvents lblPost5 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_4 As System.Windows.Forms.Label
    Public WithEvents lblPre6 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_4 As System.Windows.Forms.Label
    Public WithEvents lblPost4 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_3 As System.Windows.Forms.Label
    Public WithEvents lblPre7 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_3 As System.Windows.Forms.Label
    Public WithEvents lblPost3 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_2 As System.Windows.Forms.Label
    Public WithEvents lblPre8 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_2 As System.Windows.Forms.Label
    Public WithEvents lblPost2 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_1 As System.Windows.Forms.Label
    Public WithEvents lblPre9 As System.Windows.Forms.Label
    Public WithEvents _lblPostTrig_1 As System.Windows.Forms.Label
    Public WithEvents lblPost1 As System.Windows.Forms.Label
    Public WithEvents _lblPreTrig_0 As System.Windows.Forms.Label
    Public WithEvents lblPre10 As System.Windows.Forms.Label
    Public WithEvents lblPostTrigData As System.Windows.Forms.Label
    Public WithEvents lblPreTrigData As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Public WithEvents cmdStartPrePostTrig As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdQuit = New System.Windows.Forms.Button()
        Me.cmdStartPrePostTrig = New System.Windows.Forms.Button()
        Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowCount = New System.Windows.Forms.Label()
        Me.lblCount = New System.Windows.Forms.Label()
        Me.lblShowIndex = New System.Windows.Forms.Label()
        Me.lblIndex = New System.Windows.Forms.Label()
        Me.lblShowStat = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me._lblPostTrig_10 = New System.Windows.Forms.Label()
        Me.lblPost10 = New System.Windows.Forms.Label()
        Me._lblPreTrig_9 = New System.Windows.Forms.Label()
        Me.lblPre1 = New System.Windows.Forms.Label()
        Me._lblPostTrig_9 = New System.Windows.Forms.Label()
        Me.lblPost9 = New System.Windows.Forms.Label()
        Me._lblPreTrig_8 = New System.Windows.Forms.Label()
        Me.lblPre2 = New System.Windows.Forms.Label()
        Me._lblPostTrig_8 = New System.Windows.Forms.Label()
        Me.lblPost8 = New System.Windows.Forms.Label()
        Me._lblPreTrig_7 = New System.Windows.Forms.Label()
        Me.lblPre3 = New System.Windows.Forms.Label()
        Me._lblPostTrig_7 = New System.Windows.Forms.Label()
        Me.lblPost7 = New System.Windows.Forms.Label()
        Me._lblPreTrig_6 = New System.Windows.Forms.Label()
        Me.lblPre4 = New System.Windows.Forms.Label()
        Me._lblPostTrig_6 = New System.Windows.Forms.Label()
        Me.lblPost6 = New System.Windows.Forms.Label()
        Me._lblPreTrig_5 = New System.Windows.Forms.Label()
        Me.lblPre5 = New System.Windows.Forms.Label()
        Me._lblPostTrig_5 = New System.Windows.Forms.Label()
        Me.lblPost5 = New System.Windows.Forms.Label()
        Me._lblPreTrig_4 = New System.Windows.Forms.Label()
        Me.lblPre6 = New System.Windows.Forms.Label()
        Me._lblPostTrig_4 = New System.Windows.Forms.Label()
        Me.lblPost4 = New System.Windows.Forms.Label()
        Me._lblPreTrig_3 = New System.Windows.Forms.Label()
        Me.lblPre7 = New System.Windows.Forms.Label()
        Me._lblPostTrig_3 = New System.Windows.Forms.Label()
        Me.lblPost3 = New System.Windows.Forms.Label()
        Me._lblPreTrig_2 = New System.Windows.Forms.Label()
        Me.lblPre8 = New System.Windows.Forms.Label()
        Me._lblPostTrig_2 = New System.Windows.Forms.Label()
        Me.lblPost2 = New System.Windows.Forms.Label()
        Me._lblPreTrig_1 = New System.Windows.Forms.Label()
        Me.lblPre9 = New System.Windows.Forms.Label()
        Me._lblPostTrig_1 = New System.Windows.Forms.Label()
        Me.lblPost1 = New System.Windows.Forms.Label()
        Me._lblPreTrig_0 = New System.Windows.Forms.Label()
        Me.lblPre10 = New System.Windows.Forms.Label()
        Me.lblPostTrigData = New System.Windows.Forms.Label()
        Me.lblPreTrigData = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdQuit
        '
        Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
        Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdQuit.Location = New System.Drawing.Point(288, 288)
        Me.cmdQuit.Name = "cmdQuit"
        Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdQuit.Size = New System.Drawing.Size(52, 26)
        Me.cmdQuit.TabIndex = 17
        Me.cmdQuit.Text = "Quit"
        '
        'cmdStartPrePostTrig
        '
        Me.cmdStartPrePostTrig.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartPrePostTrig.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartPrePostTrig.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartPrePostTrig.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartPrePostTrig.Location = New System.Drawing.Point(92, 56)
        Me.cmdStartPrePostTrig.Name = "cmdStartPrePostTrig"
        Me.cmdStartPrePostTrig.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartPrePostTrig.Size = New System.Drawing.Size(200, 32)
        Me.cmdStartPrePostTrig.TabIndex = 18
        Me.cmdStartPrePostTrig.Text = "Start Pre/Post Trigger background operation"
        '
        'tmrCheckStatus
        '
        Me.tmrCheckStatus.Interval = 200
        '
        'lblShowCount
        '
        Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCount.Location = New System.Drawing.Point(200, 304)
        Me.lblShowCount.Name = "lblShowCount"
        Me.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCount.Size = New System.Drawing.Size(34, 14)
        Me.lblShowCount.TabIndex = 52
        '
        'lblCount
        '
        Me.lblCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCount.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCount.Location = New System.Drawing.Point(142, 304)
        Me.lblCount.Name = "lblCount"
        Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCount.Size = New System.Drawing.Size(55, 14)
        Me.lblCount.TabIndex = 49
        Me.lblCount.Text = "Count:"
        '
        'lblShowIndex
        '
        Me.lblShowIndex.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowIndex.ForeColor = System.Drawing.Color.Blue
        Me.lblShowIndex.Location = New System.Drawing.Point(198, 288)
        Me.lblShowIndex.Name = "lblShowIndex"
        Me.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowIndex.Size = New System.Drawing.Size(41, 14)
        Me.lblShowIndex.TabIndex = 53
        '
        'lblIndex
        '
        Me.lblIndex.BackColor = System.Drawing.SystemColors.Window
        Me.lblIndex.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblIndex.Location = New System.Drawing.Point(144, 288)
        Me.lblIndex.Name = "lblIndex"
        Me.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblIndex.Size = New System.Drawing.Size(55, 14)
        Me.lblIndex.TabIndex = 51
        Me.lblIndex.Text = "Index:"
        '
        'lblShowStat
        '
        Me.lblShowStat.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowStat.ForeColor = System.Drawing.Color.Blue
        Me.lblShowStat.Location = New System.Drawing.Point(64, 288)
        Me.lblShowStat.Name = "lblShowStat"
        Me.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowStat.Size = New System.Drawing.Size(70, 14)
        Me.lblShowStat.TabIndex = 50
        '
        'lblStatus
        '
        Me.lblStatus.BackColor = System.Drawing.SystemColors.Window
        Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblStatus.Location = New System.Drawing.Point(16, 288)
        Me.lblStatus.Name = "lblStatus"
        Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatus.Size = New System.Drawing.Size(47, 14)
        Me.lblStatus.TabIndex = 48
        Me.lblStatus.Text = "Status:"
        '
        '_lblPostTrig_10
        '
        Me._lblPostTrig_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_10.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_10.Location = New System.Drawing.Point(277, 254)
        Me._lblPostTrig_10.Name = "_lblPostTrig_10"
        Me._lblPostTrig_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_10.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_10.TabIndex = 42
        Me._lblPostTrig_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost10
        '
        Me.lblPost10.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost10.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost10.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost10.Location = New System.Drawing.Point(206, 254)
        Me.lblPost10.Name = "lblPost10"
        Me.lblPost10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost10.Size = New System.Drawing.Size(73, 14)
        Me.lblPost10.TabIndex = 40
        Me.lblPost10.Text = "Trigger +10"
        '
        '_lblPreTrig_9
        '
        Me._lblPreTrig_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_9.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_9.Location = New System.Drawing.Point(96, 254)
        Me._lblPreTrig_9.Name = "_lblPreTrig_9"
        Me._lblPreTrig_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_9.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_9.TabIndex = 22
        Me._lblPreTrig_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre1
        '
        Me.lblPre1.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre1.Location = New System.Drawing.Point(18, 254)
        Me.lblPre1.Name = "lblPre1"
        Me.lblPre1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre1.Size = New System.Drawing.Size(73, 14)
        Me.lblPre1.TabIndex = 20
        Me.lblPre1.Text = "Trigger -1"
        '
        '_lblPostTrig_9
        '
        Me._lblPostTrig_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_9.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_9.Location = New System.Drawing.Point(277, 242)
        Me._lblPostTrig_9.Name = "_lblPostTrig_9"
        Me._lblPostTrig_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_9.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_9.TabIndex = 41
        Me._lblPostTrig_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost9
        '
        Me.lblPost9.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost9.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost9.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost9.Location = New System.Drawing.Point(206, 242)
        Me.lblPost9.Name = "lblPost9"
        Me.lblPost9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost9.Size = New System.Drawing.Size(73, 14)
        Me.lblPost9.TabIndex = 39
        Me.lblPost9.Text = "Trigger +9"
        '
        '_lblPreTrig_8
        '
        Me._lblPreTrig_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_8.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_8.Location = New System.Drawing.Point(96, 242)
        Me._lblPreTrig_8.Name = "_lblPreTrig_8"
        Me._lblPreTrig_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_8.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_8.TabIndex = 21
        Me._lblPreTrig_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre2
        '
        Me.lblPre2.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre2.Location = New System.Drawing.Point(18, 242)
        Me.lblPre2.Name = "lblPre2"
        Me.lblPre2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre2.Size = New System.Drawing.Size(73, 14)
        Me.lblPre2.TabIndex = 19
        Me.lblPre2.Text = "Trigger -2"
        '
        '_lblPostTrig_8
        '
        Me._lblPostTrig_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_8.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_8.Location = New System.Drawing.Point(277, 229)
        Me._lblPostTrig_8.Name = "_lblPostTrig_8"
        Me._lblPostTrig_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_8.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_8.TabIndex = 38
        Me._lblPostTrig_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost8
        '
        Me.lblPost8.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost8.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost8.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost8.Location = New System.Drawing.Point(206, 229)
        Me.lblPost8.Name = "lblPost8"
        Me.lblPost8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost8.Size = New System.Drawing.Size(73, 14)
        Me.lblPost8.TabIndex = 37
        Me.lblPost8.Text = "Trigger +8"
        '
        '_lblPreTrig_7
        '
        Me._lblPreTrig_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_7.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_7.Location = New System.Drawing.Point(96, 229)
        Me._lblPreTrig_7.Name = "_lblPreTrig_7"
        Me._lblPreTrig_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_7.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_7.TabIndex = 16
        Me._lblPreTrig_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre3
        '
        Me.lblPre3.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre3.Location = New System.Drawing.Point(18, 229)
        Me.lblPre3.Name = "lblPre3"
        Me.lblPre3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre3.Size = New System.Drawing.Size(73, 14)
        Me.lblPre3.TabIndex = 8
        Me.lblPre3.Text = "Trigger -3"
        '
        '_lblPostTrig_7
        '
        Me._lblPostTrig_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_7.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_7.Location = New System.Drawing.Point(277, 216)
        Me._lblPostTrig_7.Name = "_lblPostTrig_7"
        Me._lblPostTrig_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_7.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_7.TabIndex = 34
        Me._lblPostTrig_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost7
        '
        Me.lblPost7.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost7.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost7.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost7.Location = New System.Drawing.Point(206, 216)
        Me.lblPost7.Name = "lblPost7"
        Me.lblPost7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost7.Size = New System.Drawing.Size(73, 14)
        Me.lblPost7.TabIndex = 33
        Me.lblPost7.Text = "Trigger +7"
        '
        '_lblPreTrig_6
        '
        Me._lblPreTrig_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_6.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_6.Location = New System.Drawing.Point(96, 216)
        Me._lblPreTrig_6.Name = "_lblPreTrig_6"
        Me._lblPreTrig_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_6.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_6.TabIndex = 15
        Me._lblPreTrig_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre4
        '
        Me.lblPre4.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre4.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre4.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre4.Location = New System.Drawing.Point(18, 216)
        Me.lblPre4.Name = "lblPre4"
        Me.lblPre4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre4.Size = New System.Drawing.Size(73, 14)
        Me.lblPre4.TabIndex = 7
        Me.lblPre4.Text = "Trigger -4"
        '
        '_lblPostTrig_6
        '
        Me._lblPostTrig_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_6.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_6.Location = New System.Drawing.Point(277, 203)
        Me._lblPostTrig_6.Name = "_lblPostTrig_6"
        Me._lblPostTrig_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_6.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_6.TabIndex = 30
        Me._lblPostTrig_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost6
        '
        Me.lblPost6.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost6.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost6.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost6.Location = New System.Drawing.Point(206, 203)
        Me.lblPost6.Name = "lblPost6"
        Me.lblPost6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost6.Size = New System.Drawing.Size(73, 14)
        Me.lblPost6.TabIndex = 29
        Me.lblPost6.Text = "Trigger +6"
        '
        '_lblPreTrig_5
        '
        Me._lblPreTrig_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_5.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_5.Location = New System.Drawing.Point(96, 203)
        Me._lblPreTrig_5.Name = "_lblPreTrig_5"
        Me._lblPreTrig_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_5.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_5.TabIndex = 14
        Me._lblPreTrig_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre5
        '
        Me.lblPre5.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre5.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre5.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre5.Location = New System.Drawing.Point(18, 203)
        Me.lblPre5.Name = "lblPre5"
        Me.lblPre5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre5.Size = New System.Drawing.Size(73, 14)
        Me.lblPre5.TabIndex = 6
        Me.lblPre5.Text = "Trigger -5"
        '
        '_lblPostTrig_5
        '
        Me._lblPostTrig_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_5.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_5.Location = New System.Drawing.Point(277, 190)
        Me._lblPostTrig_5.Name = "_lblPostTrig_5"
        Me._lblPostTrig_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_5.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_5.TabIndex = 26
        Me._lblPostTrig_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost5
        '
        Me.lblPost5.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost5.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost5.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost5.Location = New System.Drawing.Point(206, 190)
        Me.lblPost5.Name = "lblPost5"
        Me.lblPost5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost5.Size = New System.Drawing.Size(73, 14)
        Me.lblPost5.TabIndex = 25
        Me.lblPost5.Text = "Trigger +5"
        '
        '_lblPreTrig_4
        '
        Me._lblPreTrig_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_4.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_4.Location = New System.Drawing.Point(96, 190)
        Me._lblPreTrig_4.Name = "_lblPreTrig_4"
        Me._lblPreTrig_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_4.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_4.TabIndex = 13
        Me._lblPreTrig_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre6
        '
        Me.lblPre6.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre6.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre6.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre6.Location = New System.Drawing.Point(18, 190)
        Me.lblPre6.Name = "lblPre6"
        Me.lblPre6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre6.Size = New System.Drawing.Size(73, 14)
        Me.lblPre6.TabIndex = 5
        Me.lblPre6.Text = "Trigger -6"
        '
        '_lblPostTrig_4
        '
        Me._lblPostTrig_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_4.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_4.Location = New System.Drawing.Point(277, 178)
        Me._lblPostTrig_4.Name = "_lblPostTrig_4"
        Me._lblPostTrig_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_4.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_4.TabIndex = 36
        Me._lblPostTrig_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost4
        '
        Me.lblPost4.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost4.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost4.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost4.Location = New System.Drawing.Point(206, 178)
        Me.lblPost4.Name = "lblPost4"
        Me.lblPost4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost4.Size = New System.Drawing.Size(73, 14)
        Me.lblPost4.TabIndex = 35
        Me.lblPost4.Text = "Trigger +4"
        '
        '_lblPreTrig_3
        '
        Me._lblPreTrig_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_3.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_3.Location = New System.Drawing.Point(96, 178)
        Me._lblPreTrig_3.Name = "_lblPreTrig_3"
        Me._lblPreTrig_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_3.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_3.TabIndex = 12
        Me._lblPreTrig_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre7
        '
        Me.lblPre7.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre7.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre7.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre7.Location = New System.Drawing.Point(18, 178)
        Me.lblPre7.Name = "lblPre7"
        Me.lblPre7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre7.Size = New System.Drawing.Size(73, 14)
        Me.lblPre7.TabIndex = 4
        Me.lblPre7.Text = "Trigger -7"
        '
        '_lblPostTrig_3
        '
        Me._lblPostTrig_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_3.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_3.Location = New System.Drawing.Point(277, 165)
        Me._lblPostTrig_3.Name = "_lblPostTrig_3"
        Me._lblPostTrig_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_3.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_3.TabIndex = 32
        Me._lblPostTrig_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost3
        '
        Me.lblPost3.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost3.Location = New System.Drawing.Point(206, 165)
        Me.lblPost3.Name = "lblPost3"
        Me.lblPost3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost3.Size = New System.Drawing.Size(73, 14)
        Me.lblPost3.TabIndex = 31
        Me.lblPost3.Text = "Trigger +3"
        '
        '_lblPreTrig_2
        '
        Me._lblPreTrig_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_2.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_2.Location = New System.Drawing.Point(96, 165)
        Me._lblPreTrig_2.Name = "_lblPreTrig_2"
        Me._lblPreTrig_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_2.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_2.TabIndex = 11
        Me._lblPreTrig_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre8
        '
        Me.lblPre8.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre8.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre8.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre8.Location = New System.Drawing.Point(18, 165)
        Me.lblPre8.Name = "lblPre8"
        Me.lblPre8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre8.Size = New System.Drawing.Size(73, 14)
        Me.lblPre8.TabIndex = 3
        Me.lblPre8.Text = "Trigger -8"
        '
        '_lblPostTrig_2
        '
        Me._lblPostTrig_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_2.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_2.Location = New System.Drawing.Point(277, 152)
        Me._lblPostTrig_2.Name = "_lblPostTrig_2"
        Me._lblPostTrig_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_2.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_2.TabIndex = 28
        Me._lblPostTrig_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost2
        '
        Me.lblPost2.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost2.Location = New System.Drawing.Point(206, 152)
        Me.lblPost2.Name = "lblPost2"
        Me.lblPost2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost2.Size = New System.Drawing.Size(73, 14)
        Me.lblPost2.TabIndex = 27
        Me.lblPost2.Text = "Trigger +2"
        '
        '_lblPreTrig_1
        '
        Me._lblPreTrig_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_1.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_1.Location = New System.Drawing.Point(96, 152)
        Me._lblPreTrig_1.Name = "_lblPreTrig_1"
        Me._lblPreTrig_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_1.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_1.TabIndex = 10
        Me._lblPreTrig_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre9
        '
        Me.lblPre9.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre9.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre9.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre9.Location = New System.Drawing.Point(18, 152)
        Me.lblPre9.Name = "lblPre9"
        Me.lblPre9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre9.Size = New System.Drawing.Size(73, 14)
        Me.lblPre9.TabIndex = 2
        Me.lblPre9.Text = "Trigger -9"
        '
        '_lblPostTrig_1
        '
        Me._lblPostTrig_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblPostTrig_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPostTrig_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPostTrig_1.ForeColor = System.Drawing.Color.Blue
        Me._lblPostTrig_1.Location = New System.Drawing.Point(277, 139)
        Me._lblPostTrig_1.Name = "_lblPostTrig_1"
        Me._lblPostTrig_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPostTrig_1.Size = New System.Drawing.Size(65, 14)
        Me._lblPostTrig_1.TabIndex = 24
        Me._lblPostTrig_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPost1
        '
        Me.lblPost1.BackColor = System.Drawing.SystemColors.Window
        Me.lblPost1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPost1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPost1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPost1.Location = New System.Drawing.Point(206, 139)
        Me.lblPost1.Name = "lblPost1"
        Me.lblPost1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPost1.Size = New System.Drawing.Size(73, 14)
        Me.lblPost1.TabIndex = 23
        Me.lblPost1.Text = "Trigger +1"
        '
        '_lblPreTrig_0
        '
        Me._lblPreTrig_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblPreTrig_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPreTrig_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPreTrig_0.ForeColor = System.Drawing.Color.Blue
        Me._lblPreTrig_0.Location = New System.Drawing.Point(96, 139)
        Me._lblPreTrig_0.Name = "_lblPreTrig_0"
        Me._lblPreTrig_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPreTrig_0.Size = New System.Drawing.Size(65, 14)
        Me._lblPreTrig_0.TabIndex = 9
        Me._lblPreTrig_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblPre10
        '
        Me.lblPre10.BackColor = System.Drawing.SystemColors.Window
        Me.lblPre10.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPre10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPre10.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPre10.Location = New System.Drawing.Point(18, 139)
        Me.lblPre10.Name = "lblPre10"
        Me.lblPre10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPre10.Size = New System.Drawing.Size(73, 14)
        Me.lblPre10.TabIndex = 1
        Me.lblPre10.Text = "Trigger -10"
        '
        'lblPostTrigData
        '
        Me.lblPostTrigData.BackColor = System.Drawing.SystemColors.Window
        Me.lblPostTrigData.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPostTrigData.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPostTrigData.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPostTrigData.Location = New System.Drawing.Point(200, 120)
        Me.lblPostTrigData.Name = "lblPostTrigData"
        Me.lblPostTrigData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPostTrigData.Size = New System.Drawing.Size(172, 14)
        Me.lblPostTrigData.TabIndex = 44
        Me.lblPostTrigData.Text = "Data acquired after trigger"
        '
        'lblPreTrigData
        '
        Me.lblPreTrigData.BackColor = System.Drawing.SystemColors.Window
        Me.lblPreTrigData.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPreTrigData.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPreTrigData.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPreTrigData.Location = New System.Drawing.Point(13, 120)
        Me.lblPreTrigData.Name = "lblPreTrigData"
        Me.lblPreTrigData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPreTrigData.Size = New System.Drawing.Size(177, 14)
        Me.lblPreTrigData.TabIndex = 43
        Me.lblPreTrigData.Text = "Data acquired before trigger"
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(11, 6)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(367, 42)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.APreTrig() in Background mode"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmPreTrig
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(384, 332)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdQuit, Me.cmdStartPrePostTrig, Me.lblShowCount, Me.lblCount, Me.lblShowIndex, Me.lblIndex, Me.lblShowStat, Me.lblStatus, Me._lblPostTrig_10, Me.lblPost10, Me._lblPreTrig_9, Me.lblPre1, Me._lblPostTrig_9, Me.lblPost9, Me._lblPreTrig_8, Me.lblPre2, Me._lblPostTrig_8, Me.lblPost8, Me._lblPreTrig_7, Me.lblPre3, Me._lblPostTrig_7, Me.lblPost7, Me._lblPreTrig_6, Me.lblPre4, Me._lblPostTrig_6, Me.lblPost6, Me._lblPreTrig_5, Me.lblPre5, Me._lblPostTrig_5, Me.lblPost5, Me._lblPreTrig_4, Me.lblPre6, Me._lblPostTrig_4, Me.lblPost4, Me._lblPreTrig_3, Me.lblPre7, Me._lblPostTrig_3, Me.lblPost3, Me._lblPreTrig_2, Me.lblPre8, Me._lblPostTrig_2, Me.lblPost2, Me._lblPreTrig_1, Me.lblPre9, Me._lblPostTrig_1, Me.lblPost1, Me._lblPreTrig_0, Me.lblPre10, Me.lblPostTrigData, Me.lblPreTrigData, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmPreTrig"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Input Scan"
        Me.ResumeLayout(False)

    End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ULStat As MccDaq.ErrorInfo

        lblPostTrig = New System.Windows.Forms.Label(10) {}
        lblPreTrig = New System.Windows.Forms.Label(10) {}

        Me.lblPostTrig.SetValue(Me._lblPostTrig_10, 10)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_9, 9)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_8, 8)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_7, 7)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_6, 6)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_5, 5)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_4, 4)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_3, 3)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_2, 2)
        Me.lblPostTrig.SetValue(Me._lblPostTrig_1, 1)

        Me.lblPreTrig.SetValue(Me._lblPreTrig_9, 9)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_8, 8)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_7, 7)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_6, 6)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_5, 5)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_4, 4)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_3, 3)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_2, 2)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_1, 1)
        Me.lblPreTrig.SetValue(Me._lblPreTrig_0, 0)

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


        MemHandle = MccDaq.MccService.WinBufAlloc(BufSize) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

    End Sub
#End Region


End Class