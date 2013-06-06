'==============================================================================

' File:                         ULCT02.VB

' Library Call Demonstrated:    9513 Counter Functions
'                               Mccdaq.MccBoard.C9513Init()
'                               Mccdaq.MccBoard.C9513Config()
'                               Mccdaq.MccBoard.CLoad()
'                               Mccdaq.MccBoard.CIn()

' Purpose:                      Operate the counter.

' Demonstration:                Initializes, configures, loads and checks
'                               the counter

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a 9513 Counter.
'                               Program uses internal clock to count.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frm9513Ctr
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)


    Const CounterNum As Integer = 1 ' number of counter used
    Const ChipNum As Short = 1 ' use chip 1 for CIO-CTR05 or for first
    ' chip on CIO-CTR10

    Private Sub tmrReadCounter_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadCounter.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim Count As UInt16

        ' Parameters:
        '   CounterNum :the counter to be read
        '   Count    :the count value in the counter

        tmrReadCounter.Stop()

        ULStat = DaqBoard.CIn(CounterNum, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        tmrReadCounter.Start()

        lblReadValue.Text = "Value read from counter:"
        lblShowReadVal.Text = Count.ToString("0")

    End Sub

    Private Sub cmdStopRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopRead.Click

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
    Public WithEvents tmrReadCounter As System.Windows.Forms.Timer
    Public WithEvents lblShowReadVal As System.Windows.Forms.Label
    Public WithEvents lblReadValue As System.Windows.Forms.Label
    Public WithEvents lblShowLoadVal As System.Windows.Forms.Label
    Public WithEvents lblLoadValue As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frm9513Ctr))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadCounter = New System.Windows.Forms.Timer(components)
        Me.lblShowReadVal = New System.Windows.Forms.Label()
        Me.lblReadValue = New System.Windows.Forms.Label()
        Me.lblShowLoadVal = New System.Windows.Forms.Label()
        Me.lblLoadValue = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library 9513 Counter Demo"
        Me.ClientSize = New System.Drawing.Size(339, 243)
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
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
        Me.Name = "frm9513Ctr"
        Me.cmdStopRead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStopRead.Text = "Quit"
        Me.AcceptButton = Me.cmdStopRead
        Me.cmdStopRead.Size = New System.Drawing.Size(54, 27)
        Me.cmdStopRead.Location = New System.Drawing.Point(232, 184)
        Me.cmdStopRead.TabIndex = 5
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.CausesValidation = True
        Me.cmdStopRead.Enabled = True
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.TabStop = True
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.tmrReadCounter.Interval = 500
        Me.tmrReadCounter.Enabled = True
        Me.lblShowReadVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowReadVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowReadVal.Size = New System.Drawing.Size(73, 17)
        Me.lblShowReadVal.Location = New System.Drawing.Point(232, 120)
        Me.lblShowReadVal.TabIndex = 2
        Me.lblShowReadVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowReadVal.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblShowReadVal.Enabled = True
        Me.lblShowReadVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowReadVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowReadVal.UseMnemonic = True
        Me.lblShowReadVal.Visible = True
        Me.lblShowReadVal.AutoSize = False
        Me.lblShowReadVal.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblShowReadVal.Name = "lblShowReadVal"
        Me.lblReadValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblReadValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblReadValue.Size = New System.Drawing.Size(161, 17)
        Me.lblReadValue.Location = New System.Drawing.Point(56, 120)
        Me.lblReadValue.TabIndex = 4
        Me.lblReadValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblReadValue.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblReadValue.Enabled = True
        Me.lblReadValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblReadValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblReadValue.UseMnemonic = True
        Me.lblReadValue.Visible = True
        Me.lblReadValue.AutoSize = False
        Me.lblReadValue.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblReadValue.Name = "lblReadValue"
        Me.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowLoadVal.Size = New System.Drawing.Size(73, 17)
        Me.lblShowLoadVal.Location = New System.Drawing.Point(232, 88)
        Me.lblShowLoadVal.TabIndex = 1
        Me.lblShowLoadVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowLoadVal.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblShowLoadVal.Enabled = True
        Me.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowLoadVal.UseMnemonic = True
        Me.lblShowLoadVal.Visible = True
        Me.lblShowLoadVal.AutoSize = False
        Me.lblShowLoadVal.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblShowLoadVal.Name = "lblShowLoadVal"
        Me.lblLoadValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblLoadValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblLoadValue.Size = New System.Drawing.Size(161, 17)
        Me.lblLoadValue.Location = New System.Drawing.Point(56, 88)
        Me.lblLoadValue.TabIndex = 3
        Me.lblLoadValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblLoadValue.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblLoadValue.Enabled = True
        Me.lblLoadValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblLoadValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblLoadValue.UseMnemonic = True
        Me.lblLoadValue.Visible = True
        Me.lblLoadValue.AutoSize = False
        Me.lblLoadValue.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblLoadValue.Name = "lblLoadValue"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of 9513 Counter Functions."
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(225, 41)
        Me.lblDemoFunction.Location = New System.Drawing.Point(48, 16)
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
        Me.Controls.Add(cmdStopRead)
        Me.Controls.Add(lblShowReadVal)
        Me.Controls.Add(lblReadValue)
        Me.Controls.Add(lblShowLoadVal)
        Me.Controls.Add(lblLoadValue)
        Me.Controls.Add(lblDemoFunction)
    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim LoadValue As UInt32
        Dim RegName As MccDaq.CounterRegister
        Dim OutputControl As MccDaq.C9513OutputControl
        Dim CountDirection As MccDaq.CountDirection
        Dim BCDMode As MccDaq.BCDMode
        Dim RecycleMode As MccDaq.RecycleMode
        Dim Reload As MccDaq.Reload
        Dim SpecialGate As MccDaq.OptionState
        Dim CountSource As MccDaq.CounterSource
        Dim CounterEdge As MccDaq.CountEdge
        Dim GateControl As MccDaq.GateControl
        Dim TimeOfDayCounting As MccDaq.TimeOfDay
        Dim Compare2 As MccDaq.CompareValue
        Dim Compare1 As MccDaq.CompareValue
        Dim FOutSource As MccDaq.CounterSource
        Dim FOutDivider As Short
        Dim ULStat As MccDaq.ErrorInfo

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


        ' Initialize the board level features
        '  Parameters:
        '    ChipNum       :Chip to be initialized (1 for CTR05, 1 or 2 for CTR10)
        '    FOutDivider   :the F-Out divider (0-15)
        '    FOutSource    :the signal source for F-Out
        '    Compare1      :status of comparator 1
        '    Compare2      :status of comparator 2
        '    TimeOfDay     :time of day mode control

        FOutDivider = 0
        FOutSource = MccDaq.CounterSource.Freq4
        Compare1 = MccDaq.CompareValue.Disabled
        Compare2 = MccDaq.CompareValue.Disabled
        TimeOfDayCounting = MccDaq.TimeOfDay.Disabled

        ULStat = DaqBoard.C9513Init(ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDayCounting)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Set the configurable operations of the counter
        '  Parameters:
        '    CounterNum     :the counter to be configured (1 to 5)
        '    GateControl    :gate control value
        '    CounterEdge    :which edge to count
        '    CountSource    :signal source
        '    SpecialGate    :status of special gate
        '    Reload         :method of reloading
        '    RecyleMode     :recyle mode
        '    BCDMode        :counting mode, Binary or BCD
        '    CountDirection :direction for the counting operation (COUNTUP or COUNTDOWN)
        '    OutputControl  :output signal type and level

        GateControl = MccDaq.GateControl.NoGate
        CounterEdge = MccDaq.CountEdge.PositiveEdge
        CountSource = MccDaq.CounterSource.Freq4
        SpecialGate = MccDaq.OptionState.Disabled
        Reload = MccDaq.Reload.LoadReg
        RecycleMode = MccDaq.RecycleMode.Recycle
        BCDMode = MccDaq.BCDMode.Disabled

        CountDirection = MccDaq.CountDirection.CountUp
        OutputControl = MccDaq.C9513OutputControl.AlwaysLow

        ULStat = DaqBoard.C9513Config(CounterNum, GateControl, CounterEdge, CountSource, SpecialGate, Reload, RecycleMode, BCDMode, CountDirection, OutputControl)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Send a starting value to the counter with MccDaq.MccBoard.CLoad()
        '  Parameters:
        '    RegName    :the counter to be loaded with the starting value
        '    LoadValue  :the starting value to place in the counter

        RegName = MccDaq.CounterRegister.LoadReg1 ' name of register in counter 1
        LoadValue = Convert.ToUInt32(1000)

        ULStat = DaqBoard.CLoad(RegName, LoadValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblLoadValue.Text = "Value loaded to counter:"
        lblShowLoadVal.Text = LoadValue.ToString("0")


    End Sub
#End Region

End Class