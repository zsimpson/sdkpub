'==============================================================================

' File:                         ULCT04.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.CFreqIn()

' Purpose:                      Measure the frequency of a signal.

' Demonstration:                Initializes the counter and measures a frequency.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a 9513 Counter.
'                               External freq. at counter 1 input.
'                               (100Hz < freq < 330kHz)
'                               External connection from counter 4 output
'                               to counter 5 gate.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frm9513Freq
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)


    Const ChipNum As Short = 1 ' use chip 1 for CIO-CTR05 or for first
    ' chip on CIO-CTR10

    Private Sub cmdMeasureFreq_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdMeasureFreq.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim Freq As Integer
        Dim Count As UInt16
        Dim SigSource As MccDaq.SignalSource
        Dim GateInterval As Short

        ' Measure the frequency of the internally-generated signal
        '  Parameters:
        '    SigSource    :the counter to be measured (1 to 5)
        '    GateInterval :gating interval in millseconds
        '    Count     :the raw count during GateInterval is returned here
        '    Freq         :the calculated frequency (Hz) is returned here

        GateInterval = 100
        SigSource = MccDaq.SignalSource.CtrInput1

        ULStat = DaqBoard.CFreqIn(SigSource, GateInterval, Count, Freq)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblCount.Text = Count.ToString("0")
        lblFreq.Text = Freq.ToString("0") + "Hz"

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
    Public WithEvents cmdMeasureFreq As System.Windows.Forms.Button
    Public WithEvents lblFreq As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblFrequency As System.Windows.Forms.Label
    Public WithEvents lblCountNum As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frm9513Freq))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.cmdMeasureFreq = New System.Windows.Forms.Button()
        Me.lblFreq = New System.Windows.Forms.Label()
        Me.lblCount = New System.Windows.Forms.Label()
        Me.lblFrequency = New System.Windows.Forms.Label()
        Me.lblCountNum = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library 9513 Counter Demo"
        Me.ClientSize = New System.Drawing.Size(345, 250)
        Me.Location = New System.Drawing.Point(7, 96)
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
        Me.Name = "frm9513Freq"
        Me.cmdStopRead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStopRead.Text = "Quit"
        Me.AcceptButton = Me.cmdStopRead
        Me.cmdStopRead.Size = New System.Drawing.Size(52, 26)
        Me.cmdStopRead.Location = New System.Drawing.Point(264, 208)
        Me.cmdStopRead.TabIndex = 1
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.CausesValidation = True
        Me.cmdStopRead.Enabled = True
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.TabStop = True
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.cmdMeasureFreq.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdMeasureFreq.Text = "Measure Frequency"
        Me.cmdMeasureFreq.Size = New System.Drawing.Size(129, 25)
        Me.cmdMeasureFreq.Location = New System.Drawing.Point(96, 208)
        Me.cmdMeasureFreq.TabIndex = 7
        Me.cmdMeasureFreq.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdMeasureFreq.BackColor = System.Drawing.SystemColors.Control
        Me.cmdMeasureFreq.CausesValidation = True
        Me.cmdMeasureFreq.Enabled = True
        Me.cmdMeasureFreq.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdMeasureFreq.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdMeasureFreq.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdMeasureFreq.TabStop = True
        Me.cmdMeasureFreq.Name = "cmdMeasureFreq"
        Me.lblFreq.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblFreq.BackColor = System.Drawing.SystemColors.Window
        Me.lblFreq.ForeColor = System.Drawing.Color.Blue
        Me.lblFreq.Size = New System.Drawing.Size(65, 17)
        Me.lblFreq.Location = New System.Drawing.Point(200, 160)
        Me.lblFreq.TabIndex = 3
        Me.lblFreq.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFreq.Enabled = True
        Me.lblFreq.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFreq.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFreq.UseMnemonic = True
        Me.lblFreq.Visible = True
        Me.lblFreq.AutoSize = False
        Me.lblFreq.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblFreq.Name = "lblFreq"
        Me.lblCount.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblCount.BackColor = System.Drawing.SystemColors.Window
        Me.lblCount.ForeColor = System.Drawing.Color.Blue
        Me.lblCount.Size = New System.Drawing.Size(65, 17)
        Me.lblCount.Location = New System.Drawing.Point(88, 160)
        Me.lblCount.TabIndex = 2
        Me.lblCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCount.Enabled = True
        Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCount.UseMnemonic = True
        Me.lblCount.Visible = True
        Me.lblCount.AutoSize = False
        Me.lblCount.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblCount.Name = "lblCount"
        Me.lblFrequency.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblFrequency.BackColor = System.Drawing.SystemColors.Window
        Me.lblFrequency.Text = "Frequency"
        Me.lblFrequency.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFrequency.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFrequency.Size = New System.Drawing.Size(81, 17)
        Me.lblFrequency.Location = New System.Drawing.Point(192, 136)
        Me.lblFrequency.TabIndex = 5
        Me.lblFrequency.Enabled = True
        Me.lblFrequency.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFrequency.UseMnemonic = True
        Me.lblFrequency.Visible = True
        Me.lblFrequency.AutoSize = False
        Me.lblFrequency.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblFrequency.Name = "lblFrequency"
        Me.lblCountNum.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblCountNum.BackColor = System.Drawing.SystemColors.Window
        Me.lblCountNum.Text = "Number of Counts"
        Me.lblCountNum.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCountNum.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCountNum.Size = New System.Drawing.Size(113, 17)
        Me.lblCountNum.Location = New System.Drawing.Point(64, 136)
        Me.lblCountNum.TabIndex = 4
        Me.lblCountNum.Enabled = True
        Me.lblCountNum.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCountNum.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCountNum.UseMnemonic = True
        Me.lblCountNum.Visible = True
        Me.lblCountNum.AutoSize = False
        Me.lblCountNum.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblCountNum.Name = "lblCountNum"
        Me.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.Text = "There must be a TTL pulse at counter 1 input with a frequency between  100Hz and  600kHz. Also, connect the output of counter 4 to the gate of counter 5."
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Size = New System.Drawing.Size(329, 41)
        Me.lblInstruct.Location = New System.Drawing.Point(8, 72)
        Me.lblInstruct.TabIndex = 6
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.Enabled = True
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.UseMnemonic = True
        Me.lblInstruct.Visible = True
        Me.lblInstruct.AutoSize = False
        Me.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblInstruct.Name = "lblInstruct"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of Frequency Measurement using 9513 Counter"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(306, 44)
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 16)
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
        Me.Controls.Add(cmdMeasureFreq)
        Me.Controls.Add(lblFreq)
        Me.Controls.Add(lblCount)
        Me.Controls.Add(lblFrequency)
        Me.Controls.Add(lblCountNum)
        Me.Controls.Add(lblInstruct)
        Me.Controls.Add(lblDemoFunction)
    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim TimeOfDayCounting As MccDaq.TimeOfDay
        Dim Compare2 As MccDaq.CompareValue
        Dim Compare1 As MccDaq.CompareValue
        Dim Source As MccDaq.CounterSource
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
        '    ChipNum    :chip to be initialized (1 for CTR5, 1 or 2 for CTR10)
        '    FOutDivider:the F-Out divider (0-15)
        '    Source     :the signal source for F-Out
        '    Compare1   :status of comparator 1
        '    Compare2   :status of comparator 2
        '    TimeOfDay  :time of day mode control

        FOutDivider = 1 ' sets up OSC OUT for 10kHz signal which can
        Source = MccDaq.CounterSource.Freq3 ' be used as frequency source for this example
        Compare1 = MccDaq.CompareValue.Disabled
        Compare2 = MccDaq.CompareValue.Disabled
        TimeOfDayCounting = MccDaq.TimeOfDay.Disabled

        ULStat = DaqBoard.C9513Init(ChipNum, FOutDivider, Source, Compare1, Compare2, TimeOfDayCounting)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    End Sub
#End Region

End Class