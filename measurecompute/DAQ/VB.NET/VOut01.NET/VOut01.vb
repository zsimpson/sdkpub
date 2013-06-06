'==============================================================================

' File:                         ULVOut01.VB

' Library Call Demonstrated:    MccDaq.MccBoard.VOut()

' Purpose:                      Writes to a D/A Output Channel.

' Demonstration:                Sends a digital output to D/A 0.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a D/A converter.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmSendAData
    Inherits System.Windows.Forms.Form


    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)
    Private RangeSelected As MccDaq.Range

    Const Chan As Integer = 0 ' output channel

    Private Sub UpdateButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UpdateButton.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As Single
        Dim Options As MccDaq.VOutOptions = MccDaq.VOutOptions.Default
        Dim i As Integer
        Dim IsValidNumber As Boolean = True


        ' send the digital output value to D/A 0 with MccDaq.MccBoard.VOut()

        Try
            DataValue = Single.Parse(txtVoltsToSet.Text)

        Catch ex As Exception
            MessageBox.Show(txtVoltsToSet.Text + " is not a valid voltage value", "Invalid Voltage ", MessageBoxButtons.OK, MessageBoxIcon.Error)
            IsValidNumber = False
        End Try

        If (IsValidNumber) Then
            ' Parameters:
            '   Chan       :the D/A output channel
            '   Range      :ignored if board does not have programmable rage
            '   DataValue  :the value to send to Chan

            ULStat = DaqBoard.VOut(Chan, RangeSelected, DataValue, Options)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            lblVoltage.Text = "The voltage at DAC channel " & Chan.ToString("0") & " is:"
            lblShowVoltage.Text = DataValue.ToString("0.0##") & " Volts"
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
    Public WithEvents txtVoltsToSet As System.Windows.Forms.TextBox
    Public WithEvents lblVoltage As System.Windows.Forms.Label
    Public WithEvents lblUseScroll As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Friend WithEvents UpdateButton As System.Windows.Forms.Button
    Friend WithEvents cmbRange As System.Windows.Forms.ComboBox
Public WithEvents lblRange As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
Me.components = New System.ComponentModel.Container()
Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
Me.cmdEndProgram = New System.Windows.Forms.Button()
Me.txtVoltsToSet = New System.Windows.Forms.TextBox()
Me.lblVoltage = New System.Windows.Forms.Label()
Me.lblUseScroll = New System.Windows.Forms.Label()
Me.lblDemoFunction = New System.Windows.Forms.Label()
Me.UpdateButton = New System.Windows.Forms.Button()
Me.lblShowVoltage = New System.Windows.Forms.Label()
Me.lblPrompt = New System.Windows.Forms.Label()
Me.cmbRange = New System.Windows.Forms.ComboBox()
Me.lblRange = New System.Windows.Forms.Label()
Me.SuspendLayout()
'
'cmdEndProgram
'
Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdEndProgram.Location = New System.Drawing.Point(256, 288)
Me.cmdEndProgram.Name = "cmdEndProgram"
Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdEndProgram.Size = New System.Drawing.Size(55, 26)
Me.cmdEndProgram.TabIndex = 5
Me.cmdEndProgram.Text = "Quit"
'
'txtVoltsToSet
'
Me.txtVoltsToSet.AcceptsReturn = True
Me.txtVoltsToSet.AutoSize = False
Me.txtVoltsToSet.BackColor = System.Drawing.SystemColors.Window
Me.txtVoltsToSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
Me.txtVoltsToSet.Cursor = System.Windows.Forms.Cursors.IBeam
Me.txtVoltsToSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.txtVoltsToSet.ForeColor = System.Drawing.SystemColors.WindowText
Me.txtVoltsToSet.Location = New System.Drawing.Point(232, 168)
Me.txtVoltsToSet.MaxLength = 0
Me.txtVoltsToSet.Name = "txtVoltsToSet"
Me.txtVoltsToSet.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.txtVoltsToSet.Size = New System.Drawing.Size(112, 24)
Me.txtVoltsToSet.TabIndex = 0
Me.txtVoltsToSet.Text = ""
'
'lblVoltage
'
Me.lblVoltage.BackColor = System.Drawing.SystemColors.Window
Me.lblVoltage.Cursor = System.Windows.Forms.Cursors.Default
Me.lblVoltage.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblVoltage.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblVoltage.Location = New System.Drawing.Point(52, 256)
Me.lblVoltage.Name = "lblVoltage"
Me.lblVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblVoltage.Size = New System.Drawing.Size(201, 17)
Me.lblVoltage.TabIndex = 7
'
'lblUseScroll
'
Me.lblUseScroll.BackColor = System.Drawing.SystemColors.Window
Me.lblUseScroll.Cursor = System.Windows.Forms.Cursors.Default
Me.lblUseScroll.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblUseScroll.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblUseScroll.Location = New System.Drawing.Point(28, 168)
Me.lblUseScroll.Name = "lblUseScroll"
Me.lblUseScroll.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblUseScroll.Size = New System.Drawing.Size(196, 24)
Me.lblUseScroll.TabIndex = 2
Me.lblUseScroll.Text = "Enter a voltage within the DACs range Hit Update Button when done"
'
'lblDemoFunction
'
Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblDemoFunction.Location = New System.Drawing.Point(68, 12)
Me.lblDemoFunction.Name = "lblDemoFunction"
Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblDemoFunction.Size = New System.Drawing.Size(241, 20)
Me.lblDemoFunction.TabIndex = 1
Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.VOut()"
Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
'
'UpdateButton
'
Me.UpdateButton.BackColor = System.Drawing.SystemColors.Control
Me.UpdateButton.Location = New System.Drawing.Point(248, 208)
Me.UpdateButton.Name = "UpdateButton"
Me.UpdateButton.TabIndex = 8
Me.UpdateButton.Text = "Update"
'
'lblShowVoltage
'
Me.lblShowVoltage.BackColor = System.Drawing.SystemColors.Window
Me.lblShowVoltage.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowVoltage.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowVoltage.ForeColor = System.Drawing.Color.Blue
Me.lblShowVoltage.Location = New System.Drawing.Point(260, 256)
Me.lblShowVoltage.Name = "lblShowVoltage"
Me.lblShowVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowVoltage.Size = New System.Drawing.Size(81, 17)
Me.lblShowVoltage.TabIndex = 6
'
'lblPrompt
'
Me.lblPrompt.Location = New System.Drawing.Point(12, 44)
Me.lblPrompt.Name = "lblPrompt"
Me.lblPrompt.Size = New System.Drawing.Size(364, 56)
Me.lblPrompt.TabIndex = 9
Me.lblPrompt.Text = "Using the combo box below, select a range supported by the device you are using. " & _
"If the device is not programmable, the range selected must match the range your " & _
"device is configured for."
'
'cmbRange
'
Me.cmbRange.Location = New System.Drawing.Point(232, 128)
Me.cmbRange.Name = "cmbRange"
Me.cmbRange.Size = New System.Drawing.Size(120, 22)
Me.cmbRange.TabIndex = 10
Me.cmbRange.Text = "Bip5Volts"
'
'lblRange
'
Me.lblRange.BackColor = System.Drawing.SystemColors.Window
Me.lblRange.Cursor = System.Windows.Forms.Cursors.Default
Me.lblRange.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblRange.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblRange.Location = New System.Drawing.Point(112, 128)
Me.lblRange.Name = "lblRange"
Me.lblRange.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblRange.Size = New System.Drawing.Size(104, 16)
Me.lblRange.TabIndex = 11
Me.lblRange.Text = "Range"
Me.lblRange.TextAlign = System.Drawing.ContentAlignment.MiddleRight
'
'frmSendAData
'
Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
Me.BackColor = System.Drawing.SystemColors.Window
Me.ClientSize = New System.Drawing.Size(384, 325)
Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblRange, Me.cmbRange, Me.lblPrompt, Me.UpdateButton, Me.cmdEndProgram, Me.txtVoltsToSet, Me.lblShowVoltage, Me.lblVoltage, Me.lblUseScroll, Me.lblDemoFunction})
Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.ForeColor = System.Drawing.SystemColors.WindowText
Me.Location = New System.Drawing.Point(7, 103)
Me.Name = "frmSendAData"
Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
Me.Text = "Universal Library Analog Output "
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
        Me.Close()
    End Sub
    Public WithEvents lblShowVoltage As System.Windows.Forms.Label

    Private Sub ComboBox1_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmbRange.SelectedIndexChanged

        RangeSelected = cmbRange.SelectedItem

    End Sub
    Friend WithEvents lblPrompt As System.Windows.Forms.Label

    Private Sub frmSendAData_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        cmbRange.Items.Insert(0, MccDaq.Range.Bip10Volts)
        cmbRange.Items.Insert(1, MccDaq.Range.Bip5Volts)
        cmbRange.Items.Insert(2, MccDaq.Range.Uni10Volts)
        cmbRange.Items.Insert(3, MccDaq.Range.Uni5Volts)
        cmbRange.SelectedIndex = 1
    End Sub
End Class