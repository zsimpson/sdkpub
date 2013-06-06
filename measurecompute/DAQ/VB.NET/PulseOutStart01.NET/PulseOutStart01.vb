'==============================================================================

' File:                         PulseOut01.VB

'  Library Call Demonstrated:    MccDaq.MccBoard.PulseOutStart()
'								 MccDaq.MccBoard.PulseOutStop()

'  Purpose:                      Controls an Output Timer Channel.

'  Demonstration:                Sends a frequency output to Timer 0.

'  Other Library Calls:          MccDaq.MccService.ErrHandling()

'  Special Requirements:         Board 0 must have a Timer output.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmPulseOutput
    Inherits System.Windows.Forms.Form


    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Private Sub UpdateButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UpdateButton.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim Frequency As Double
        Dim DutyCycle As Double
        Dim PulseCount As Integer
        Dim InitialDelay As Double
        Dim IdleState As MccDaq.IdleState
        Dim Options As MccDaq.PulseOutOptions

        PulseCount = 0
        InitialDelay = 0
        IdleState = MccDaq.IdleState.Low
        Options = MccDaq.PulseOutOptions.Default

        Dim IsValidNumber As Boolean = True

        lblShowValue.Text = ""
        lblShowFrequency.Text = ""

        Try
            Frequency = Double.Parse(txtFrequencyToSet.Text)
        Catch ex As Exception
            MessageBox.Show(txtFrequencyToSet.Text + " is not a valid frequency value", "Invalid Frequency ", MessageBoxButtons.OK, MessageBoxIcon.Error)
            IsValidNumber = False
        End Try

        Try
            DutyCycle = Double.Parse(txtDutyCycleToSet.Text)
        Catch ex As Exception
            MessageBox.Show(txtDutyCycleToSet.Text + " is not a valid duty cycle value", "Invalid Duty Cycle ", MessageBoxButtons.OK, MessageBoxIcon.Error)
            IsValidNumber = False
        End Try

        If (IsValidNumber) Then
            Dim FrequencySet As Double = Frequency
            Dim DutyCycleSet As Double = DutyCycle
            ' Parameters:
            '   TimerNum       :the timer output channel
            '   Frequency      :the frequency to output
            '   DutyCycle      :the duty cycle
            ULStat = DaqBoard.PulseOutStart(0, Frequency, DutyCycle, PulseCount, InitialDelay, IdleState, Options)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            lblValueSent.Text = "The frequency sent to timer 0 was:"
            lblFrequency.Text = "The frequency output from timer channel 0 is:"
            lblShowValue.Text = FrequencySet.ToString("0.0#####") + " Hz"
            lblShowFrequency.Text = Frequency.ToString("0.0#####") + " Hz"

            lblDCValueSent.Text = "The duty cycle sent to timer 0 was:"
            lblDutyCycle.Text = "The duty cycle output from timer channel 0 is:"
            lblDCShowValue.Text = DutyCycleSet.ToString("0.0#####")
            lblShowDutyCycle.Text = DutyCycle.ToString("0.0#####")
        End If

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
    Public WithEvents cmdEndProgram As System.Windows.Forms.Button
    Public WithEvents lblShowValue As System.Windows.Forms.Label
    Public WithEvents lblValueSent As System.Windows.Forms.Label
    Public WithEvents lblUseScroll As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Friend WithEvents UpdateButton As System.Windows.Forms.Button
    Public WithEvents lblShowFrequency As System.Windows.Forms.Label
    Public WithEvents lblFrequency As System.Windows.Forms.Label
    Public WithEvents txtFrequencyToSet As System.Windows.Forms.TextBox
    Friend WithEvents lblFreq As System.Windows.Forms.Label
    Friend WithEvents lblDC As System.Windows.Forms.Label
    Public WithEvents txtDutyCycleToSet As System.Windows.Forms.TextBox
    Public WithEvents lblShowDutyCycle As System.Windows.Forms.Label
    Public WithEvents lblDutyCycle As System.Windows.Forms.Label
    Public WithEvents lblDCShowValue As System.Windows.Forms.Label
    Public WithEvents lblDCValueSent As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me.txtFrequencyToSet = New System.Windows.Forms.TextBox()
        Me.lblShowFrequency = New System.Windows.Forms.Label()
        Me.lblFrequency = New System.Windows.Forms.Label()
        Me.lblShowValue = New System.Windows.Forms.Label()
        Me.lblValueSent = New System.Windows.Forms.Label()
        Me.lblUseScroll = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.UpdateButton = New System.Windows.Forms.Button()
        Me.lblFreq = New System.Windows.Forms.Label()
        Me.lblDC = New System.Windows.Forms.Label()
        Me.txtDutyCycleToSet = New System.Windows.Forms.TextBox()
        Me.lblShowDutyCycle = New System.Windows.Forms.Label()
        Me.lblDutyCycle = New System.Windows.Forms.Label()
        Me.lblDCShowValue = New System.Windows.Forms.Label()
        Me.lblDCValueSent = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdEndProgram
        '
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Location = New System.Drawing.Point(256, 304)
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.Size = New System.Drawing.Size(55, 26)
        Me.cmdEndProgram.TabIndex = 5
        Me.cmdEndProgram.Text = "Quit"
        '
        'txtFrequencyToSet
        '
        Me.txtFrequencyToSet.AcceptsReturn = True
        Me.txtFrequencyToSet.AutoSize = False
        Me.txtFrequencyToSet.BackColor = System.Drawing.SystemColors.Window
        Me.txtFrequencyToSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtFrequencyToSet.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtFrequencyToSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtFrequencyToSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtFrequencyToSet.Location = New System.Drawing.Point(104, 128)
        Me.txtFrequencyToSet.MaxLength = 0
        Me.txtFrequencyToSet.Name = "txtFrequencyToSet"
        Me.txtFrequencyToSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtFrequencyToSet.Size = New System.Drawing.Size(81, 24)
        Me.txtFrequencyToSet.TabIndex = 0
        Me.txtFrequencyToSet.Text = "100000"
        '
        'lblShowFrequency
        '
        Me.lblShowFrequency.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowFrequency.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowFrequency.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowFrequency.ForeColor = System.Drawing.Color.Blue
        Me.lblShowFrequency.Location = New System.Drawing.Point(248, 224)
        Me.lblShowFrequency.Name = "lblShowFrequency"
        Me.lblShowFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowFrequency.Size = New System.Drawing.Size(80, 17)
        Me.lblShowFrequency.TabIndex = 6
        '
        'lblFrequency
        '
        Me.lblFrequency.BackColor = System.Drawing.SystemColors.Window
        Me.lblFrequency.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFrequency.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFrequency.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFrequency.Location = New System.Drawing.Point(8, 224)
        Me.lblFrequency.Name = "lblFrequency"
        Me.lblFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFrequency.Size = New System.Drawing.Size(240, 17)
        Me.lblFrequency.TabIndex = 7
        '
        'lblShowValue
        '
        Me.lblShowValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowValue.ForeColor = System.Drawing.Color.Blue
        Me.lblShowValue.Location = New System.Drawing.Point(248, 208)
        Me.lblShowValue.Name = "lblShowValue"
        Me.lblShowValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowValue.Size = New System.Drawing.Size(80, 17)
        Me.lblShowValue.TabIndex = 4
        '
        'lblValueSent
        '
        Me.lblValueSent.BackColor = System.Drawing.SystemColors.Window
        Me.lblValueSent.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValueSent.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValueSent.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValueSent.Location = New System.Drawing.Point(8, 208)
        Me.lblValueSent.Name = "lblValueSent"
        Me.lblValueSent.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValueSent.Size = New System.Drawing.Size(240, 17)
        Me.lblValueSent.TabIndex = 3
        '
        'lblUseScroll
        '
        Me.lblUseScroll.BackColor = System.Drawing.SystemColors.Window
        Me.lblUseScroll.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblUseScroll.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblUseScroll.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblUseScroll.Location = New System.Drawing.Point(56, 64)
        Me.lblUseScroll.Name = "lblUseScroll"
        Me.lblUseScroll.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblUseScroll.Size = New System.Drawing.Size(225, 40)
        Me.lblUseScroll.TabIndex = 2
        Me.lblUseScroll.Text = "Enter a frequency and a duty cycle within the timer's range and click Update Butt" & _
        "on when done"
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(38, 24)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(266, 25)
        Me.lblDemoFunction.TabIndex = 1
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.PulseOutStart() and MccDaq.MccBoard.PulseOutStop" & _
        "()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'UpdateButton
        '
        Me.UpdateButton.BackColor = System.Drawing.SystemColors.Control
        Me.UpdateButton.Location = New System.Drawing.Point(200, 144)
        Me.UpdateButton.Name = "UpdateButton"
        Me.UpdateButton.TabIndex = 8
        Me.UpdateButton.Text = "Update"
        '
        'lblFreq
        '
        Me.lblFreq.Location = New System.Drawing.Point(32, 128)
        Me.lblFreq.Name = "lblFreq"
        Me.lblFreq.Size = New System.Drawing.Size(72, 16)
        Me.lblFreq.TabIndex = 9
        Me.lblFreq.Text = "Frequency:"
        '
        'lblDC
        '
        Me.lblDC.Location = New System.Drawing.Point(32, 160)
        Me.lblDC.Name = "lblDC"
        Me.lblDC.Size = New System.Drawing.Size(72, 16)
        Me.lblDC.TabIndex = 10
        Me.lblDC.Text = "Duty Cycle:"
        '
        'txtDutyCycleToSet
        '
        Me.txtDutyCycleToSet.AcceptsReturn = True
        Me.txtDutyCycleToSet.AutoSize = False
        Me.txtDutyCycleToSet.BackColor = System.Drawing.SystemColors.Window
        Me.txtDutyCycleToSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtDutyCycleToSet.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtDutyCycleToSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtDutyCycleToSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtDutyCycleToSet.Location = New System.Drawing.Point(104, 160)
        Me.txtDutyCycleToSet.MaxLength = 0
        Me.txtDutyCycleToSet.Name = "txtDutyCycleToSet"
        Me.txtDutyCycleToSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtDutyCycleToSet.Size = New System.Drawing.Size(81, 24)
        Me.txtDutyCycleToSet.TabIndex = 11
        Me.txtDutyCycleToSet.Text = ".5"
        '
        'lblShowDutyCycle
        '
        Me.lblShowDutyCycle.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowDutyCycle.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowDutyCycle.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowDutyCycle.ForeColor = System.Drawing.Color.Blue
        Me.lblShowDutyCycle.Location = New System.Drawing.Point(248, 272)
        Me.lblShowDutyCycle.Name = "lblShowDutyCycle"
        Me.lblShowDutyCycle.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowDutyCycle.Size = New System.Drawing.Size(80, 17)
        Me.lblShowDutyCycle.TabIndex = 14
        '
        'lblDutyCycle
        '
        Me.lblDutyCycle.BackColor = System.Drawing.SystemColors.Window
        Me.lblDutyCycle.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDutyCycle.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDutyCycle.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDutyCycle.Location = New System.Drawing.Point(8, 272)
        Me.lblDutyCycle.Name = "lblDutyCycle"
        Me.lblDutyCycle.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDutyCycle.Size = New System.Drawing.Size(240, 17)
        Me.lblDutyCycle.TabIndex = 15
        '
        'lblDCShowValue
        '
        Me.lblDCShowValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblDCShowValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDCShowValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDCShowValue.ForeColor = System.Drawing.Color.Blue
        Me.lblDCShowValue.Location = New System.Drawing.Point(248, 256)
        Me.lblDCShowValue.Name = "lblDCShowValue"
        Me.lblDCShowValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDCShowValue.Size = New System.Drawing.Size(80, 17)
        Me.lblDCShowValue.TabIndex = 13
        '
        'lblDCValueSent
        '
        Me.lblDCValueSent.BackColor = System.Drawing.SystemColors.Window
        Me.lblDCValueSent.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDCValueSent.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDCValueSent.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDCValueSent.Location = New System.Drawing.Point(8, 256)
        Me.lblDCValueSent.Name = "lblDCValueSent"
        Me.lblDCValueSent.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDCValueSent.Size = New System.Drawing.Size(240, 17)
        Me.lblDCValueSent.TabIndex = 12
        '
        'frmPulseOutput
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(332, 334)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblShowDutyCycle, Me.lblDutyCycle, Me.lblDCShowValue, Me.lblDCValueSent, Me.txtDutyCycleToSet, Me.lblDC, Me.lblFreq, Me.UpdateButton, Me.cmdEndProgram, Me.txtFrequencyToSet, Me.lblShowFrequency, Me.lblFrequency, Me.lblShowValue, Me.lblValueSent, Me.lblUseScroll, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmPulseOutput"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Pulse Output "
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
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


    End Sub
#End Region

    Private Sub cmdEndProgram_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdEndProgram.Click
        DaqBoard.PulseOutStop(0)
        Me.Close()
    End Sub
End Class