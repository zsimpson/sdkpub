'==============================================================================

' File:                         ULCT06.VB

' Library Call Demonstrated:    7266 Counter Functions
'                               Mccdaq.MccBoard.C7266Config()
'                               Mccdaq.MccBoard.CLoad32()
'                               Mccdaq.MccBoard.CIn32()

' Purpose:                      Operate the counter.

' Demonstration:                Configures, loads and checks
'                               the counter

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a 7266 Counter.
'
'                               These functions are only supported in the
'                               32 bit version of the Universal Library
'
'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frm7266Ctr
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Const CounterNum As Short = 1 ' Counter number

    Private Sub tmrReadCounter_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadCounter.Tick
        Dim StatusBits As MccDaq.StatusBits
        Dim ULStat As MccDaq.ErrorInfo
        Dim Count As UInt32

        tmrReadCounter.Stop()

        ' Parameters:
        '   CounterNum :the counter to be read
        '   Count    :the count value in the counter

        
        ULStat = DaqBoard.CIn32(CounterNum, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        lblShowReadVal.Text = Count.ToString("0")

        ULStat = DaqBoard.CStatus(CounterNum, StatusBits)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        If ((StatusBits And MccDaq.StatusBits.Updown) <> 0) Then
            lblShowDirection.Text = "UP"
        Else
            lblShowDirection.Text = "DOWN"
        End If

        tmrReadCounter.Start()


    End Sub

    Private Sub lblDemoFunction_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles lblDemoFunction.Click

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
    Public WithEvents lblShowDirection As System.Windows.Forms.Label
    Public WithEvents lblDirection As System.Windows.Forms.Label
    Public WithEvents lblShowLoadVal As System.Windows.Forms.Label
    Public WithEvents lblShowMaxVal As System.Windows.Forms.Label
    Public WithEvents lblMaxCount As System.Windows.Forms.Label
    Public WithEvents lblShowReadVal As System.Windows.Forms.Label
    Public WithEvents lblReadValue As System.Windows.Forms.Label
    Public WithEvents lblLoadValue As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadCounter = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowDirection = New System.Windows.Forms.Label()
        Me.lblDirection = New System.Windows.Forms.Label()
        Me.lblShowLoadVal = New System.Windows.Forms.Label()
        Me.lblShowMaxVal = New System.Windows.Forms.Label()
        Me.lblMaxCount = New System.Windows.Forms.Label()
        Me.lblShowReadVal = New System.Windows.Forms.Label()
        Me.lblReadValue = New System.Windows.Forms.Label()
        Me.lblLoadValue = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopRead
        '
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Location = New System.Drawing.Point(240, 264)
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.Size = New System.Drawing.Size(54, 27)
        Me.cmdStopRead.TabIndex = 4
        Me.cmdStopRead.Text = "Quit"
        '
        'tmrReadCounter
        '
        '
        'lblShowDirection
        '
        Me.lblShowDirection.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowDirection.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowDirection.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowDirection.ForeColor = System.Drawing.Color.Blue
        Me.lblShowDirection.Location = New System.Drawing.Point(232, 216)
        Me.lblShowDirection.Name = "lblShowDirection"
        Me.lblShowDirection.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowDirection.Size = New System.Drawing.Size(73, 17)
        Me.lblShowDirection.TabIndex = 9
        '
        'lblDirection
        '
        Me.lblDirection.BackColor = System.Drawing.SystemColors.Window
        Me.lblDirection.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDirection.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDirection.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDirection.Location = New System.Drawing.Point(64, 216)
        Me.lblDirection.Name = "lblDirection"
        Me.lblDirection.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDirection.Size = New System.Drawing.Size(161, 17)
        Me.lblDirection.TabIndex = 8
        Me.lblDirection.Text = "Direction = "
        Me.lblDirection.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowLoadVal
        '
        Me.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowLoadVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowLoadVal.Location = New System.Drawing.Point(232, 88)
        Me.lblShowLoadVal.Name = "lblShowLoadVal"
        Me.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowLoadVal.Size = New System.Drawing.Size(73, 17)
        Me.lblShowLoadVal.TabIndex = 7
        '
        'lblShowMaxVal
        '
        Me.lblShowMaxVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowMaxVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowMaxVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowMaxVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowMaxVal.Location = New System.Drawing.Point(232, 120)
        Me.lblShowMaxVal.Name = "lblShowMaxVal"
        Me.lblShowMaxVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowMaxVal.Size = New System.Drawing.Size(73, 17)
        Me.lblShowMaxVal.TabIndex = 6
        '
        'lblMaxCount
        '
        Me.lblMaxCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblMaxCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblMaxCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblMaxCount.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblMaxCount.Location = New System.Drawing.Point(56, 120)
        Me.lblMaxCount.Name = "lblMaxCount"
        Me.lblMaxCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblMaxCount.Size = New System.Drawing.Size(161, 17)
        Me.lblMaxCount.TabIndex = 5
        Me.lblMaxCount.Text = "Maximum count:"
        Me.lblMaxCount.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowReadVal
        '
        Me.lblShowReadVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowReadVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowReadVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowReadVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowReadVal.Location = New System.Drawing.Point(232, 184)
        Me.lblShowReadVal.Name = "lblShowReadVal"
        Me.lblShowReadVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowReadVal.Size = New System.Drawing.Size(73, 17)
        Me.lblShowReadVal.TabIndex = 1
        '
        'lblReadValue
        '
        Me.lblReadValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblReadValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblReadValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblReadValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblReadValue.Location = New System.Drawing.Point(56, 184)
        Me.lblReadValue.Name = "lblReadValue"
        Me.lblReadValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblReadValue.Size = New System.Drawing.Size(161, 17)
        Me.lblReadValue.TabIndex = 3
        Me.lblReadValue.Text = "Value read from counter:"
        Me.lblReadValue.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblLoadValue
        '
        Me.lblLoadValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblLoadValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblLoadValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblLoadValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblLoadValue.Location = New System.Drawing.Point(56, 88)
        Me.lblLoadValue.Name = "lblLoadValue"
        Me.lblLoadValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblLoadValue.Size = New System.Drawing.Size(161, 17)
        Me.lblLoadValue.TabIndex = 2
        Me.lblLoadValue.Text = "Initial count for counter:"
        Me.lblLoadValue.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(48, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(225, 41)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of 7266 Counter Functions."
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frm7266Ctr
        '
        Me.AcceptButton = Me.cmdStopRead
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(339, 296)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopRead, Me.lblShowDirection, Me.lblDirection, Me.lblShowLoadVal, Me.lblShowMaxVal, Me.lblMaxCount, Me.lblShowReadVal, Me.lblReadValue, Me.lblLoadValue, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frm7266Ctr"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library 7266Counter Demo"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim RegName As MccDaq.CounterRegister
        Dim LoadValue As UInt32
        Dim GateEnable As MccDaq.OptionState
        Dim FlagPins As MccDaq.FlagPins
        Dim InvertIndex As MccDaq.OptionState
        Dim DISABLED As Object
        Dim IndexMode As MccDaq.IndexMode
        Dim DataEncoding As MccDaq.DataEncoding
        Dim CountingMode As MccDaq.CountingMode
        Dim Quadrature As MccDaq.Quadrature
        Dim ULStat As MccDaq.ErrorInfo

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

        ' set the configurable operations of the counter
        ' Parameters:
        '         CounterNum     :the counter to be configured (0-5)
        '         Quadrature     :Select type of counter input
        '         CountingMode   :Slects how counter will operate
        '         IndexMode      :Selects what index signal will control
        '         InvertIndex    :Set to ENABLED id index signal is inverted
        '         FlagPins       :Select which signals will drive Flag pins
        '         GateEnable     :Set to ENABLED to use external gating signal */
        Quadrature = MccDaq.Quadrature.X1Quad
        CountingMode = MccDaq.CountingMode.ModuloN
        DataEncoding = MccDaq.DataEncoding.BinaryEncoding
        IndexMode = MccDaq.IndexMode.IndexDisabled
        InvertIndex = MccDaq.OptionState.Disabled
        FlagPins = MccDaq.FlagPins.CarryBorrow
        GateEnable = MccDaq.OptionState.Disabled
        ULStat = DaqBoard.C7266Config(CounterNum, Quadrature, CountingMode, DataEncoding, IndexMode, InvertIndex, FlagPins, GateEnable)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Send a starting value to the counter with Mccdaq.MccBoard.CLoad32()
        '  Parameters:
        '    RegName    :the counter to be loaded with the starting value
        '    LoadValue  :the starting value to place in the counter

        LoadValue = Convert.ToUInt32(1000)

        Dim TmpRegName As MccDaq.CounterRegister

        ' Convert the value of the counter number to MccDaq.CounterRegister
        TmpRegName = CType(CounterNum - 1, MccDaq.CounterRegister)


        RegName = CType((MccDaq.CounterRegister.QuadCount1 + TmpRegName), MccDaq.CounterRegister)

        ULStat = DaqBoard.CLoad32(RegName, LoadValue)
        lblShowLoadVal.Text = LoadValue.ToString("0")

        LoadValue = Convert.ToUInt32(2000)
        RegName = CType((MccDaq.CounterRegister.QuadPreset1 + TmpRegName), MccDaq.CounterRegister)

        ULStat = DaqBoard.CLoad32(RegName, LoadValue)
        lblShowMaxVal.Text = LoadValue.ToString("0")

        tmrReadCounter.Enabled = True

    End Sub
#End Region

End Class