'==============================================================================

' File:                         ULCT01.VB

' Library Call Demonstrated:    8254 Counter Functions
'                               Mccdaq.MccBoard.C8254Config()
'                               Mccdaq.MccBoard.CLoad()
'                               Mccdaq.MccBoard.CIn()

' Purpose:                      Operate the counter.

' Demonstration:                Configures, loads and reads the counter.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have an 8254 Counter.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmCountTest
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Const CounterNum As Short = 1 ' number of counter used
    Dim RegName As MccDaq.CounterRegister = MccDaq.CounterRegister.LoadReg1 ' register name of counter 1

    Private Sub tmrReadCount_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadCount.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim Count As UInt16

        tmrReadCount.Stop()

        ' Parameters:
        '   CounterNum     :the counter to be read
        '   Count        :the value read from the counter

        ULStat = DaqBoard.CIn(CounterNum, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        tmrReadCount.Start()

        lblShowCountRead.Text = Count.ToString("0")

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
    Public WithEvents tmrReadCount As System.Windows.Forms.Timer
    Public WithEvents lblShowCountRead As System.Windows.Forms.Label
    Public WithEvents lblCountRead As System.Windows.Forms.Label
    Public WithEvents lblShowLoadVal As System.Windows.Forms.Label
    Public WithEvents lblCountLoaded As System.Windows.Forms.Label
    Public WithEvents lblNoteFreqIn As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadCount = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowCountRead = New System.Windows.Forms.Label()
        Me.lblCountRead = New System.Windows.Forms.Label()
        Me.lblShowLoadVal = New System.Windows.Forms.Label()
        Me.lblCountLoaded = New System.Windows.Forms.Label()
        Me.lblNoteFreqIn = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopRead
        '
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Location = New System.Drawing.Point(200, 208)
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.Size = New System.Drawing.Size(57, 33)
        Me.cmdStopRead.TabIndex = 6
        Me.cmdStopRead.Text = "Quit"
        '
        'tmrReadCount
        '
        Me.tmrReadCount.Enabled = True
        Me.tmrReadCount.Interval = 500
        '
        'lblShowCountRead
        '
        Me.lblShowCountRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCountRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCountRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCountRead.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCountRead.Location = New System.Drawing.Point(200, 168)
        Me.lblShowCountRead.Name = "lblShowCountRead"
        Me.lblShowCountRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCountRead.Size = New System.Drawing.Size(65, 17)
        Me.lblShowCountRead.TabIndex = 5
        '
        'lblCountRead
        '
        Me.lblCountRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblCountRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCountRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCountRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCountRead.ImageAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblCountRead.Location = New System.Drawing.Point(48, 168)
        Me.lblCountRead.Name = "lblCountRead"
        Me.lblCountRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCountRead.Size = New System.Drawing.Size(145, 17)
        Me.lblCountRead.TabIndex = 3
        Me.lblCountRead.Text = "Value read from counter:"
        '
        'lblShowLoadVal
        '
        Me.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowLoadVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowLoadVal.Location = New System.Drawing.Point(200, 136)
        Me.lblShowLoadVal.Name = "lblShowLoadVal"
        Me.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowLoadVal.Size = New System.Drawing.Size(65, 17)
        Me.lblShowLoadVal.TabIndex = 4
        '
        'lblCountLoaded
        '
        Me.lblCountLoaded.BackColor = System.Drawing.SystemColors.Window
        Me.lblCountLoaded.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCountLoaded.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCountLoaded.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCountLoaded.ImageAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblCountLoaded.Location = New System.Drawing.Point(16, 136)
        Me.lblCountLoaded.Name = "lblCountLoaded"
        Me.lblCountLoaded.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCountLoaded.Size = New System.Drawing.Size(177, 17)
        Me.lblCountLoaded.TabIndex = 2
        '
        'lblNoteFreqIn
        '
        Me.lblNoteFreqIn.BackColor = System.Drawing.SystemColors.Window
        Me.lblNoteFreqIn.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblNoteFreqIn.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblNoteFreqIn.ForeColor = System.Drawing.Color.Red
        Me.lblNoteFreqIn.Location = New System.Drawing.Point(24, 80)
        Me.lblNoteFreqIn.Name = "lblNoteFreqIn"
        Me.lblNoteFreqIn.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblNoteFreqIn.Size = New System.Drawing.Size(233, 33)
        Me.lblNoteFreqIn.TabIndex = 1
        Me.lblNoteFreqIn.Text = "NOTE: There must be a TTL frequency at the counter 1 input."
        Me.lblNoteFreqIn.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(16, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(249, 41)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of 8254 Counter Functions"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmCountTest
        '
        Me.AcceptButton = Me.cmdStopRead
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(280, 261)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopRead, Me.lblShowCountRead, Me.lblCountRead, Me.lblShowLoadVal, Me.lblCountLoaded, Me.lblNoteFreqIn, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmCountTest"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library 8254 Counter"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim LoadValue As UInt32
        Dim Config As MccDaq.C8254Mode
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


        ' Configure the counter for desired operation
        '  Parameters:
        '    CounterNum :the counter to be setup
        '    Config     :the operation mode of counter to be configured


        Config = MccDaq.C8254Mode.HighOnLastCount

        ULStat = DaqBoard.C8254Config(CounterNum, Config)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Send a starting value to the counter with MccDaq.MccBoard.CLoad()
        '  Parameters:
        '    RegName    :the counter to be loading with the starting value
        '    LoadValue  :the starting value to place in the counter

        LoadValue = Convert.ToUInt32(1000)
        ULStat = DaqBoard.CLoad(RegName, LoadValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblCountLoaded.Text = "Counter starting value loaded:"

        lblShowLoadVal.Text = LoadValue.ToString("0")
    End Sub
#End Region

End Class