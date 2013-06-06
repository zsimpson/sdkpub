'==============================================================================

' File:                         ULCT07.VB

' Library Call Demonstrated:    Event Counter Functions
'                               Mccdaq.MccBoard.CLoad32()
'                               Mccdaq.MccBoard.CIn32()

' Purpose:                      Operate the counter.

' Demonstration:                Resets and reads the event counter.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have an Event Counter, such as 
'                               the miniLAB 1008 or the PMD01208LS boards.

'==============================================================================
Public Class frmCounterTest
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)
    Const CounterNum As Short = 1 ' number of counter used
    Dim RegName As MccDaq.CounterRegister = MccDaq.CounterRegister.LoadReg1 ' register name of counter 1

    Private Sub tmrReadCounter_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tmrReadCounter.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim Count As System.UInt32

        tmrReadCounter.Stop()

        ULStat = DaqBoard.CIn32(RegName, Count)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblShowCountRead.Text = Count.ToString("0")

        tmrReadCounter.Start()

    End Sub

    Private Sub cmdStopRead_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStopRead.Click
        End
    End Sub

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        InitUL()

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Public WithEvents cmdStopRead As System.Windows.Forms.Button
    Friend WithEvents tmrReadCounter As System.Windows.Forms.Timer
    Public WithEvents lblShowCountRead As System.Windows.Forms.Label
    Public WithEvents lblCountRead As System.Windows.Forms.Label
    Public WithEvents lblShowLoadVal As System.Windows.Forms.Label
    Public WithEvents lblCountLoaded As System.Windows.Forms.Label
    Public WithEvents lblNoteFreqIn As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadCounter = New System.Windows.Forms.Timer(Me.components)
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
        Me.cmdStopRead.Location = New System.Drawing.Point(232, 261)
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.Size = New System.Drawing.Size(54, 27)
        Me.cmdStopRead.TabIndex = 14
        Me.cmdStopRead.Text = "Quit"
        '
        'lblShowCountRead
        '
        Me.lblShowCountRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCountRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCountRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCountRead.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCountRead.Location = New System.Drawing.Point(232, 168)
        Me.lblShowCountRead.Name = "lblShowCountRead"
        Me.lblShowCountRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCountRead.Size = New System.Drawing.Size(65, 17)
        Me.lblShowCountRead.TabIndex = 20
        '
        'lblCountRead
        '
        Me.lblCountRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblCountRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCountRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCountRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCountRead.ImageAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblCountRead.Location = New System.Drawing.Point(80, 168)
        Me.lblCountRead.Name = "lblCountRead"
        Me.lblCountRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCountRead.Size = New System.Drawing.Size(145, 17)
        Me.lblCountRead.TabIndex = 18
        Me.lblCountRead.Text = "Value read from counter:"
        '
        'lblShowLoadVal
        '
        Me.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowLoadVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowLoadVal.Location = New System.Drawing.Point(232, 136)
        Me.lblShowLoadVal.Name = "lblShowLoadVal"
        Me.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowLoadVal.Size = New System.Drawing.Size(65, 17)
        Me.lblShowLoadVal.TabIndex = 19
        '
        'lblCountLoaded
        '
        Me.lblCountLoaded.BackColor = System.Drawing.SystemColors.Window
        Me.lblCountLoaded.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCountLoaded.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCountLoaded.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCountLoaded.ImageAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblCountLoaded.Location = New System.Drawing.Point(48, 136)
        Me.lblCountLoaded.Name = "lblCountLoaded"
        Me.lblCountLoaded.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCountLoaded.Size = New System.Drawing.Size(177, 17)
        Me.lblCountLoaded.TabIndex = 17
        '
        'lblNoteFreqIn
        '
        Me.lblNoteFreqIn.BackColor = System.Drawing.SystemColors.Window
        Me.lblNoteFreqIn.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblNoteFreqIn.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblNoteFreqIn.ForeColor = System.Drawing.Color.Red
        Me.lblNoteFreqIn.Location = New System.Drawing.Point(56, 80)
        Me.lblNoteFreqIn.Name = "lblNoteFreqIn"
        Me.lblNoteFreqIn.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblNoteFreqIn.Size = New System.Drawing.Size(233, 33)
        Me.lblNoteFreqIn.TabIndex = 16
        Me.lblNoteFreqIn.Text = "NOTE: There must be a TTL frequency at the counter 1 input."
        Me.lblNoteFreqIn.TextAlign = System.Drawing.ContentAlignment.TopCenter
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
        Me.lblDemoFunction.Size = New System.Drawing.Size(249, 41)
        Me.lblDemoFunction.TabIndex = 15
        Me.lblDemoFunction.Text = "Demonstration of Event Counter Functions"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmCounterTest
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(336, 301)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblShowCountRead, Me.lblCountRead, Me.lblShowLoadVal, Me.lblCountLoaded, Me.lblNoteFreqIn, Me.lblDemoFunction, Me.cmdStopRead})
        Me.Name = "frmCounterTest"
        Me.Text = "Universal Library Counter Test"
        Me.ResumeLayout(False)

    End Sub

#End Region





#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim RegName As MccDaq.CounterRegister
        Dim LoadValue As UInt32
        Dim ULStat As MccDaq.ErrorInfo

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


        ' Reset the event counter with Mccdaq.MccBoard.CLoad32()
        '  Parameters:
        '    RegName    :the counter to be loaded with the starting value
        '    LoadValue  :the starting value to place in the counter
        RegName = MccDaq.CounterRegister.LoadReg1
        LoadValue = Convert.ToUInt32(0) ' Event counters can only be reset to 0
        ULStat = DaqBoard.CLoad32(RegName, LoadValue)
        lblShowLoadVal.Text = LoadValue.ToString("0")

        tmrReadCounter.Enabled = True
    End Sub

#End Region


End Class
