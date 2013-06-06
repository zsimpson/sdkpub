'==============================================================================

' File:                         TimerOut01.VB

'  Library Call Demonstrated:    MccDaq.MccBoard.TimerOutStart()
'								 MccDaq.MccBoard.TimerOutStop()

'  Purpose:                      Controls an Output Timer Channel.

'  Demonstration:                Sends a frequency output to Timer 0.

'  Other Library Calls:          MccDaq.MccService.ErrHandling()

'  Special Requirements:         Board 0 must have a Timer output.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmTimerOutput
  Inherits System.Windows.Forms.Form


    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

  Private Sub UpdateButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UpdateButton.Click
    Dim ULStat As MccDaq.ErrorInfo
    Dim Frequency As Double
    Dim IsValidNumber As Boolean = True

    lblShowValue.Text = ""
    lblShowFrequency.Text = ""

    Try
      Frequency = Double.Parse(txtFrequencyToSet.Text)
    Catch ex As Exception
      MessageBox.Show(txtFrequencyToSet.Text + " is not a valid frequency value", "Invalid Frequency ", MessageBoxButtons.OK, MessageBoxIcon.Error)
      IsValidNumber = False
    End Try

    If (IsValidNumber) Then
      Dim FrequencySet As Double = Frequency
      ' Parameters:
      '   TimerNum       :the timer output channel
      '   Frequency      :the frequency to output
      ULStat = DaqBoard.TimerOutStart(0, Frequency)
      If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

      lblValueSent.Text = "The frequency sent to timer 0 was:"
      lblFrequency.Text = "The frequency output from timer channel 0 is:"
      lblShowValue.Text = FrequencySet.ToString("0.0##") + " Hz"
      lblShowFrequency.Text = Frequency.ToString("0.0##") + " Hz"
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
  <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
    Me.components = New System.ComponentModel.Container
    Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
    Me.cmdEndProgram = New System.Windows.Forms.Button
    Me.txtFrequencyToSet = New System.Windows.Forms.TextBox
    Me.lblShowFrequency = New System.Windows.Forms.Label
    Me.lblFrequency = New System.Windows.Forms.Label
    Me.lblShowValue = New System.Windows.Forms.Label
    Me.lblValueSent = New System.Windows.Forms.Label
    Me.lblUseScroll = New System.Windows.Forms.Label
    Me.lblDemoFunction = New System.Windows.Forms.Label
    Me.UpdateButton = New System.Windows.Forms.Button
    Me.SuspendLayout()
    '
    'cmdEndProgram
    '
    Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
    Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
    Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
    Me.cmdEndProgram.Location = New System.Drawing.Point(248, 216)
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
    Me.txtFrequencyToSet.Location = New System.Drawing.Point(120, 104)
    Me.txtFrequencyToSet.MaxLength = 0
    Me.txtFrequencyToSet.Name = "txtFrequencyToSet"
    Me.txtFrequencyToSet.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.txtFrequencyToSet.Size = New System.Drawing.Size(81, 25)
    Me.txtFrequencyToSet.TabIndex = 0
    Me.txtFrequencyToSet.Text = "100000"
    '
    'lblShowFrequency
    '
    Me.lblShowFrequency.BackColor = System.Drawing.SystemColors.Window
    Me.lblShowFrequency.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblShowFrequency.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblShowFrequency.ForeColor = System.Drawing.Color.Blue
    Me.lblShowFrequency.Location = New System.Drawing.Point(248, 176)
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
    Me.lblFrequency.Location = New System.Drawing.Point(8, 176)
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
    Me.lblShowValue.Location = New System.Drawing.Point(248, 159)
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
    Me.lblValueSent.Location = New System.Drawing.Point(8, 159)
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
    Me.lblUseScroll.Size = New System.Drawing.Size(225, 32)
    Me.lblUseScroll.TabIndex = 2
    Me.lblUseScroll.Text = "Enter a frequency within the timer's range and click Update Button when done"
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
    Me.lblDemoFunction.Size = New System.Drawing.Size(256, 25)
    Me.lblDemoFunction.TabIndex = 1
    Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.TimerStart() and MccDaq.MccBoard.TimerStop()"
    Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
    '
    'UpdateButton
    '
    Me.UpdateButton.BackColor = System.Drawing.SystemColors.Control
    Me.UpdateButton.Location = New System.Drawing.Point(224, 104)
    Me.UpdateButton.Name = "UpdateButton"
    Me.UpdateButton.TabIndex = 8
    Me.UpdateButton.Text = "Update"
    '
    'frmTimerOutput
    '
    Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
    Me.BackColor = System.Drawing.SystemColors.Window
    Me.ClientSize = New System.Drawing.Size(332, 251)
    Me.Controls.Add(Me.UpdateButton)
    Me.Controls.Add(Me.cmdEndProgram)
    Me.Controls.Add(Me.txtFrequencyToSet)
    Me.Controls.Add(Me.lblShowFrequency)
    Me.Controls.Add(Me.lblFrequency)
    Me.Controls.Add(Me.lblShowValue)
    Me.Controls.Add(Me.lblValueSent)
    Me.Controls.Add(Me.lblUseScroll)
    Me.Controls.Add(Me.lblDemoFunction)
    Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.ForeColor = System.Drawing.SystemColors.WindowText
    Me.Location = New System.Drawing.Point(7, 103)
    Me.Name = "frmTimerOutput"
    Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
    Me.Text = "Universal Library Timer Output "
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
    DaqBoard.TimerOutStop(0)
    Me.Close()
  End Sub
End Class