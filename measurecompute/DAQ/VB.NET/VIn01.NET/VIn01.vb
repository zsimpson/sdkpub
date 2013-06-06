'==============================================================================

' File:                         VIn01.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.VIn()

' Purpose:                      Reads an A/D Input Channel.

' Demonstration:                Displays the analog input on a user-specified
'                               channel.

' Other Library Calls:          MccDaq.MccService.ErrHandling()                              

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on an input channel.

'==============================================================================

Option Strict Off
Option Explicit On 

Public Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    ' Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)
    Private RangeSelected As MccDaq.Range

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click

        cmdStartConvert.Visible = False
        cmdStopConvert.Visible = True
        tmrConvert.Enabled = True

    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As System.Single
        Dim Chan As Integer

        Dim Options As MccDaq.VInOptions

        tmrConvert.Stop()


        ' Collect the data by calling VIn memeber function of MccBoard object

        '  Parameters:
        '    Chan       :the input channel number
        '    Range      :the Range for the board.
        '    DataValue  :the name for the value collected

        Chan = Integer.Parse(txtNumChan.Text) ' set input channel
        Options = MccDaq.VInOptions.Default

        ULStat = DaqBoard.VIn(Chan, RangeSelected, DataValue, Options)
        If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadRange Then
            MsgBox("Change the Range argument to one supported by this board.", 0, "Unsupported Range")
        End If

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        Else
            lblShowData.Text = DataValue.ToString()                ' print the counts

            tmrConvert.Start()
        End If

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        tmrConvert.Enabled = False
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
    Public WithEvents cmdStartConvert As System.Windows.Forms.Button
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents txtNumChan As System.Windows.Forms.TextBox
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
    Public WithEvents lblValueRead As System.Windows.Forms.Label
    Public WithEvents lblChanPrompt As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Friend WithEvents lblShowData As System.Windows.Forms.Label
    Friend WithEvents cmbRange As System.Windows.Forms.ComboBox
    Friend WithEvents lblPrompt As System.Windows.Forms.Label
Public WithEvents lblRange As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
Me.components = New System.ComponentModel.Container()
Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
Me.cmdStartConvert = New System.Windows.Forms.Button()
Me.cmdStopConvert = New System.Windows.Forms.Button()
Me.txtNumChan = New System.Windows.Forms.TextBox()
Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
Me.lblValueRead = New System.Windows.Forms.Label()
Me.lblChanPrompt = New System.Windows.Forms.Label()
Me.lblDemoFunction = New System.Windows.Forms.Label()
Me.lblShowData = New System.Windows.Forms.Label()
Me.cmbRange = New System.Windows.Forms.ComboBox()
Me.lblPrompt = New System.Windows.Forms.Label()
Me.lblRange = New System.Windows.Forms.Label()
Me.SuspendLayout()
'
'cmdStartConvert
'
Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdStartConvert.Location = New System.Drawing.Point(328, 224)
Me.cmdStartConvert.Name = "cmdStartConvert"
Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdStartConvert.Size = New System.Drawing.Size(52, 26)
Me.cmdStartConvert.TabIndex = 5
Me.cmdStartConvert.Text = "Start"
'
'cmdStopConvert
'
Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdStopConvert.Location = New System.Drawing.Point(328, 224)
Me.cmdStopConvert.Name = "cmdStopConvert"
Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdStopConvert.Size = New System.Drawing.Size(52, 26)
Me.cmdStopConvert.TabIndex = 6
Me.cmdStopConvert.Text = "Quit"
Me.cmdStopConvert.Visible = False
'
'txtNumChan
'
Me.txtNumChan.AcceptsReturn = True
Me.txtNumChan.AutoSize = False
Me.txtNumChan.BackColor = System.Drawing.SystemColors.Window
Me.txtNumChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
Me.txtNumChan.Cursor = System.Windows.Forms.Cursors.IBeam
Me.txtNumChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.txtNumChan.ForeColor = System.Drawing.SystemColors.WindowText
Me.txtNumChan.Location = New System.Drawing.Point(208, 144)
Me.txtNumChan.MaxLength = 0
Me.txtNumChan.Name = "txtNumChan"
Me.txtNumChan.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.txtNumChan.Size = New System.Drawing.Size(33, 24)
Me.txtNumChan.TabIndex = 0
Me.txtNumChan.Text = "0"
Me.txtNumChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
'
'tmrConvert
'
'
'lblValueRead
'
Me.lblValueRead.BackColor = System.Drawing.SystemColors.Window
Me.lblValueRead.Cursor = System.Windows.Forms.Cursors.Default
Me.lblValueRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblValueRead.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblValueRead.Location = New System.Drawing.Point(16, 184)
Me.lblValueRead.Name = "lblValueRead"
Me.lblValueRead.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblValueRead.Size = New System.Drawing.Size(184, 16)
Me.lblValueRead.TabIndex = 3
Me.lblValueRead.Text = "Voltage read from selected channel:"
Me.lblValueRead.TextAlign = System.Drawing.ContentAlignment.MiddleRight
'
'lblChanPrompt
'
Me.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window
Me.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChanPrompt.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChanPrompt.Location = New System.Drawing.Point(16, 144)
Me.lblChanPrompt.Name = "lblChanPrompt"
Me.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChanPrompt.Size = New System.Drawing.Size(184, 16)
Me.lblChanPrompt.TabIndex = 1
Me.lblChanPrompt.Text = "Enter the Channel to display: "
Me.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.MiddleRight
'
'lblDemoFunction
'
Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblDemoFunction.Location = New System.Drawing.Point(52, 12)
Me.lblDemoFunction.Name = "lblDemoFunction"
Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblDemoFunction.Size = New System.Drawing.Size(286, 20)
Me.lblDemoFunction.TabIndex = 2
Me.lblDemoFunction.Text = "Demonstration of MccBoard.VIn"
Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
'
'lblShowData
'
Me.lblShowData.Font = New System.Drawing.Font("Arial", 8.0!)
Me.lblShowData.ForeColor = System.Drawing.Color.Blue
Me.lblShowData.Location = New System.Drawing.Point(208, 184)
Me.lblShowData.Name = "lblShowData"
Me.lblShowData.Size = New System.Drawing.Size(164, 16)
Me.lblShowData.TabIndex = 9
Me.lblShowData.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
'
'cmbRange
'
Me.cmbRange.Location = New System.Drawing.Point(208, 112)
Me.cmbRange.Name = "cmbRange"
Me.cmbRange.Size = New System.Drawing.Size(136, 22)
Me.cmbRange.TabIndex = 10
Me.cmbRange.Text = "Bip5Volts"
'
'lblPrompt
'
Me.lblPrompt.Location = New System.Drawing.Point(16, 44)
Me.lblPrompt.Name = "lblPrompt"
Me.lblPrompt.Size = New System.Drawing.Size(368, 52)
Me.lblPrompt.TabIndex = 11
Me.lblPrompt.Text = "Using the combo box below, select a range supported by the device you are using. " & _
"If the device is not programmable, the range selected must match the range your " & _
"device is configured for."
'
'lblRange
'
Me.lblRange.BackColor = System.Drawing.SystemColors.Window
Me.lblRange.Cursor = System.Windows.Forms.Cursors.Default
Me.lblRange.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblRange.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblRange.Location = New System.Drawing.Point(56, 112)
Me.lblRange.Name = "lblRange"
Me.lblRange.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblRange.Size = New System.Drawing.Size(144, 16)
Me.lblRange.TabIndex = 12
Me.lblRange.Text = "Range: "
Me.lblRange.TextAlign = System.Drawing.ContentAlignment.MiddleRight
'
'frmDataDisplay
'
Me.AcceptButton = Me.cmdStartConvert
Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
Me.BackColor = System.Drawing.SystemColors.Window
Me.ClientSize = New System.Drawing.Size(408, 277)
Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblRange, Me.lblPrompt, Me.cmbRange, Me.lblShowData, Me.cmdStartConvert, Me.cmdStopConvert, Me.txtNumChan, Me.lblValueRead, Me.lblChanPrompt, Me.lblDemoFunction})
Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.ForeColor = System.Drawing.SystemColors.WindowText
Me.Location = New System.Drawing.Point(182, 100)
Me.Name = "frmDataDisplay"
Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
Me.Text = "Universal Library Voltage Input"
Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand to change error handling, etc."

    Private Sub InitUL()

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

    End Sub

#End Region


    Private Sub frmDataDisplay_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        cmbRange.Items.Insert(0, MccDaq.Range.Bip10Volts)
        cmbRange.Items.Insert(1, MccDaq.Range.Bip5Volts)
        cmbRange.Items.Insert(2, MccDaq.Range.Uni10Volts)
        cmbRange.Items.Insert(3, MccDaq.Range.Uni5Volts)
        cmbRange.SelectedIndex = 1
    End Sub

    Private Sub cmbRange_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmbRange.SelectedIndexChanged
         RangeSelected = cmbRange.SelectedItem
    End Sub
End Class