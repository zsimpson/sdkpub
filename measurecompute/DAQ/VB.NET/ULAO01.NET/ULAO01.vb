'==============================================================================

' File:                         ULAO01.VB

' Library Call Demonstrated:    MccDaq.MccBoard.AOut()

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

    Const Chan As Integer = 0 ' output channel
    Const Range As MccDaq.Range = MccDaq.Range.Bip5Volts

    Private Sub UpdateButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UpdateButton.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16
        Dim EngUnits As Single
        Dim i As Integer
        Dim IsValidNumber As Boolean = True


        ' send the digital output value to D/A 0 with MccDaq.MccBoard.AOut()

        Try
            EngUnits = Single.Parse(txtVoltsToSet.Text)

        Catch ex As Exception
            MessageBox.Show(txtVoltsToSet.Text + " is not a valid voltage value", "Invalid Voltage ", MessageBoxButtons.OK, MessageBoxIcon.Error)
            IsValidNumber = False
        End Try

        If (IsValidNumber) Then
            ' Parameters:
            '   Chan       :the D/A output channel
            '   Range      :ignored if board does not have programmable rage
            '   DataValue  :the value to send to Chan


            ULStat = DaqBoard.FromEngUnits(Range, EngUnits, DataValue)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            ULStat = DaqBoard.AOut(Chan, Range, DataValue)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            lblValueSent.Text = "The count sent to DAC channel " & Chan.ToString("0") & " was:"
            lblVoltage.Text = "The voltage at DAC channel " & Chan.ToString("0") & " is:"
            lblShowValue.Text = DataValue.ToString("0")
            lblShowVoltage.Text = EngUnits.ToString("0.0##") & " Volts"
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
    Public WithEvents lblShowVoltage As System.Windows.Forms.Label
    Public WithEvents lblVoltage As System.Windows.Forms.Label
    Public WithEvents lblShowValue As System.Windows.Forms.Label
    Public WithEvents lblValueSent As System.Windows.Forms.Label
    Public WithEvents lblUseScroll As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Friend WithEvents UpdateButton As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me.txtVoltsToSet = New System.Windows.Forms.TextBox()
        Me.lblShowVoltage = New System.Windows.Forms.Label()
        Me.lblVoltage = New System.Windows.Forms.Label()
        Me.lblShowValue = New System.Windows.Forms.Label()
        Me.lblValueSent = New System.Windows.Forms.Label()
        Me.lblUseScroll = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.UpdateButton = New System.Windows.Forms.Button()
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
        'txtVoltsToSet
        '
        Me.txtVoltsToSet.AcceptsReturn = True
        Me.txtVoltsToSet.AutoSize = False
        Me.txtVoltsToSet.BackColor = System.Drawing.SystemColors.Window
        Me.txtVoltsToSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtVoltsToSet.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtVoltsToSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtVoltsToSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtVoltsToSet.Location = New System.Drawing.Point(120, 104)
        Me.txtVoltsToSet.MaxLength = 0
        Me.txtVoltsToSet.Name = "txtVoltsToSet"
        Me.txtVoltsToSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtVoltsToSet.Size = New System.Drawing.Size(81, 25)
        Me.txtVoltsToSet.TabIndex = 0
        Me.txtVoltsToSet.Text = ""
        '
        'lblShowVoltage
        '
        Me.lblShowVoltage.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowVoltage.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowVoltage.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowVoltage.ForeColor = System.Drawing.Color.Blue
        Me.lblShowVoltage.Location = New System.Drawing.Point(240, 176)
        Me.lblShowVoltage.Name = "lblShowVoltage"
        Me.lblShowVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowVoltage.Size = New System.Drawing.Size(81, 17)
        Me.lblShowVoltage.TabIndex = 6
        '
        'lblVoltage
        '
        Me.lblVoltage.BackColor = System.Drawing.SystemColors.Window
        Me.lblVoltage.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblVoltage.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblVoltage.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblVoltage.Location = New System.Drawing.Point(32, 176)
        Me.lblVoltage.Name = "lblVoltage"
        Me.lblVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblVoltage.Size = New System.Drawing.Size(201, 17)
        Me.lblVoltage.TabIndex = 7
        '
        'lblShowValue
        '
        Me.lblShowValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowValue.ForeColor = System.Drawing.Color.Blue
        Me.lblShowValue.Location = New System.Drawing.Point(264, 159)
        Me.lblShowValue.Name = "lblShowValue"
        Me.lblShowValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowValue.Size = New System.Drawing.Size(57, 17)
        Me.lblShowValue.TabIndex = 4
        '
        'lblValueSent
        '
        Me.lblValueSent.BackColor = System.Drawing.SystemColors.Window
        Me.lblValueSent.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValueSent.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValueSent.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValueSent.Location = New System.Drawing.Point(32, 159)
        Me.lblValueSent.Name = "lblValueSent"
        Me.lblValueSent.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValueSent.Size = New System.Drawing.Size(225, 17)
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
        Me.lblUseScroll.Text = "Enter a voltage within the DACs range Hit Update Button when done"
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(40, 24)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(241, 25)
        Me.lblDemoFunction.TabIndex = 1
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AOut()"
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
        'frmSendAData
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(332, 251)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.UpdateButton, Me.cmdEndProgram, Me.txtVoltsToSet, Me.lblShowVoltage, Me.lblVoltage, Me.lblShowValue, Me.lblValueSent, Me.lblUseScroll, Me.lblDemoFunction})
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
End Class