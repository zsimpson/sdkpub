'==============================================================================

' File:                         ULAI11.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AIn()
'                               Mccdaq.MccBoard.ToEngUnits()

' Purpose:                      Convert a raw data value to a voltage.

' Demonstration:                Displays a voltage on a user-specified
'                               channel.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on specified input channel.
'                               
'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmManualConvert
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)


    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click

        tmrConvert.Enabled = True
        cmdStartConvert.Visible = False
        cmdStopConvert.Visible = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        tmrConvert.Enabled = False
        End

    End Sub

    Private Sub opt10VBip_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles opt10VBip.CheckedChanged
        If opt10VBip.Checked Then

            lblGainCode.Text = "BIP10VOLTS"
            lblGainCodeVal.Text = MccDaq.Range.Bip10Volts.ToString("D")
            lblMinVal.Text = "-10"
            lblMaxVal.Text = "10"

        End If
    End Sub

    Private Sub opt10VUni_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles opt10VUni.CheckedChanged
        If opt10VUni.Checked Then

            lblGainCode.Text = "UNI10VOLTS"
            lblGainCodeVal.Text = MccDaq.Range.Uni10Volts.ToString("D")
            lblMinVal.Text = "0"
            lblMaxVal.Text = "10"

        End If
    End Sub

    Private Sub opt5VBip_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles opt5VBip.CheckedChanged
        If opt5VBip.Checked Then

            lblGainCode.Text = "BIP5VOLTS"
            lblGainCodeVal.Text = MccDaq.Range.Bip5Volts.ToString("D")
            lblMinVal.Text = "-5"
            lblMaxVal.Text = "5"

        End If
    End Sub

    Private Sub opt5VUni_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles opt5VUni.CheckedChanged
        If opt5VUni.Checked Then

            lblGainCode.Text = "UNI5VOLTS"
            lblGainCodeVal.Text = MccDaq.Range.Uni5Volts.ToString("D")
            lblMinVal.Text = "0"
            lblMaxVal.Text = "5"

        End If
    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim EngUnits As Single
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16
        Dim MinVal As Object
        Dim MaxVal As Object
        Dim Range As MccDaq.Range
        Dim Chan As Integer

        ' Parameters:
        '   Chan       :the input channel number
        '   Range       :the range for the board.
        '   DataValue  :the name for the value collected

        Chan = Integer.Parse(txtNumChan.Text)

        Range = CType(Integer.Parse(lblGainCodeVal.Text), MccDaq.Range)

        tmrConvert.Stop()

        ULStat = DaqBoard.AIn(Chan, Range, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        tmrConvert.Start()

        '******* CONVERT RAW DATA VALUES TO VOLTAGES ********

        ULStat = DaqBoard.ToEngUnits(Range, DataValue, EngUnits)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If
        lblShowData.Text = DataValue.ToString("D")
        lblShowCalcResults.Text = EngUnits.ToString("0.000") + " Volts"

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
    Public WithEvents opt10VUni As System.Windows.Forms.RadioButton
    Public WithEvents opt10VBip As System.Windows.Forms.RadioButton
    Public WithEvents opt5VUni As System.Windows.Forms.RadioButton
    Public WithEvents opt5VBip As System.Windows.Forms.RadioButton
    Public WithEvents fraGainSel As System.Windows.Forms.GroupBox
    Public WithEvents txtNumChan As System.Windows.Forms.TextBox
    Public WithEvents lblChanPrompt As System.Windows.Forms.Label
    Public WithEvents fraChanSelect As System.Windows.Forms.GroupBox
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
    Public WithEvents lblShowCalcResults As System.Windows.Forms.Label
    Public WithEvents lblCalcResult As System.Windows.Forms.Label
    Public WithEvents lblShowData As System.Windows.Forms.Label
    Public WithEvents lblValueRead As System.Windows.Forms.Label
    Public WithEvents lblGainCodeVal As System.Windows.Forms.Label
    Public WithEvents lblGainCode As System.Windows.Forms.Label
    Public WithEvents lblMinVal As System.Windows.Forms.Label
    Public WithEvents lblFullScaleNeg As System.Windows.Forms.Label
    Public WithEvents lblMaxVal As System.Windows.Forms.Label
    Public WithEvents lblFullScalePos As System.Windows.Forms.Label
    Public WithEvents lblCVLabel As System.Windows.Forms.Label
    Public WithEvents lblGCLabel As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.fraGainSel = New System.Windows.Forms.GroupBox()
        Me.opt10VUni = New System.Windows.Forms.RadioButton()
        Me.opt10VBip = New System.Windows.Forms.RadioButton()
        Me.opt5VUni = New System.Windows.Forms.RadioButton()
        Me.opt5VBip = New System.Windows.Forms.RadioButton()
        Me.fraChanSelect = New System.Windows.Forms.GroupBox()
        Me.txtNumChan = New System.Windows.Forms.TextBox()
        Me.lblChanPrompt = New System.Windows.Forms.Label()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowCalcResults = New System.Windows.Forms.Label()
        Me.lblCalcResult = New System.Windows.Forms.Label()
        Me.lblShowData = New System.Windows.Forms.Label()
        Me.lblValueRead = New System.Windows.Forms.Label()
        Me.lblGainCodeVal = New System.Windows.Forms.Label()
        Me.lblGainCode = New System.Windows.Forms.Label()
        Me.lblMinVal = New System.Windows.Forms.Label()
        Me.lblFullScaleNeg = New System.Windows.Forms.Label()
        Me.lblMaxVal = New System.Windows.Forms.Label()
        Me.lblFullScalePos = New System.Windows.Forms.Label()
        Me.lblCVLabel = New System.Windows.Forms.Label()
        Me.lblGCLabel = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.fraGainSel.SuspendLayout()
        Me.fraChanSelect.SuspendLayout()
        Me.SuspendLayout()
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(352, 256)
        Me.cmdStartConvert.Name = "cmdStartConvert"
        Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartConvert.Size = New System.Drawing.Size(52, 27)
        Me.cmdStartConvert.TabIndex = 3
        Me.cmdStartConvert.Text = "Start"
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(352, 256)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(52, 27)
        Me.cmdStopConvert.TabIndex = 4
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Visible = False
        '
        'fraGainSel
        '
        Me.fraGainSel.BackColor = System.Drawing.SystemColors.Window
        Me.fraGainSel.Controls.AddRange(New System.Windows.Forms.Control() {Me.opt10VUni, Me.opt10VBip, Me.opt5VUni, Me.opt5VBip})
        Me.fraGainSel.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.fraGainSel.ForeColor = System.Drawing.SystemColors.WindowText
        Me.fraGainSel.Location = New System.Drawing.Point(208, 104)
        Me.fraGainSel.Name = "fraGainSel"
        Me.fraGainSel.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fraGainSel.Size = New System.Drawing.Size(217, 57)
        Me.fraGainSel.TabIndex = 16
        Me.fraGainSel.TabStop = False
        Me.fraGainSel.Text = "Select Range"
        '
        'opt10VUni
        '
        Me.opt10VUni.BackColor = System.Drawing.SystemColors.Window
        Me.opt10VUni.Cursor = System.Windows.Forms.Cursors.Default
        Me.opt10VUni.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.opt10VUni.ForeColor = System.Drawing.SystemColors.WindowText
        Me.opt10VUni.Location = New System.Drawing.Point(112, 32)
        Me.opt10VUni.Name = "opt10VUni"
        Me.opt10VUni.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.opt10VUni.Size = New System.Drawing.Size(97, 17)
        Me.opt10VUni.TabIndex = 20
        Me.opt10VUni.TabStop = True
        Me.opt10VUni.Text = "10V Unipolar"
        '
        'opt10VBip
        '
        Me.opt10VBip.BackColor = System.Drawing.SystemColors.Window
        Me.opt10VBip.Cursor = System.Windows.Forms.Cursors.Default
        Me.opt10VBip.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.opt10VBip.ForeColor = System.Drawing.SystemColors.WindowText
        Me.opt10VBip.Location = New System.Drawing.Point(16, 32)
        Me.opt10VBip.Name = "opt10VBip"
        Me.opt10VBip.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.opt10VBip.Size = New System.Drawing.Size(89, 17)
        Me.opt10VBip.TabIndex = 18
        Me.opt10VBip.TabStop = True
        Me.opt10VBip.Text = "10V Bipolar"
        '
        'opt5VUni
        '
        Me.opt5VUni.BackColor = System.Drawing.SystemColors.Window
        Me.opt5VUni.Cursor = System.Windows.Forms.Cursors.Default
        Me.opt5VUni.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.opt5VUni.ForeColor = System.Drawing.SystemColors.WindowText
        Me.opt5VUni.Location = New System.Drawing.Point(112, 16)
        Me.opt5VUni.Name = "opt5VUni"
        Me.opt5VUni.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.opt5VUni.Size = New System.Drawing.Size(97, 17)
        Me.opt5VUni.TabIndex = 19
        Me.opt5VUni.TabStop = True
        Me.opt5VUni.Text = "5V Unipolar"
        '
        'opt5VBip
        '
        Me.opt5VBip.BackColor = System.Drawing.SystemColors.Window
        Me.opt5VBip.Checked = True
        Me.opt5VBip.Cursor = System.Windows.Forms.Cursors.Default
        Me.opt5VBip.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.opt5VBip.ForeColor = System.Drawing.SystemColors.WindowText
        Me.opt5VBip.Location = New System.Drawing.Point(16, 16)
        Me.opt5VBip.Name = "opt5VBip"
        Me.opt5VBip.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.opt5VBip.Size = New System.Drawing.Size(89, 17)
        Me.opt5VBip.TabIndex = 17
        Me.opt5VBip.TabStop = True
        Me.opt5VBip.Text = "5V Bipolar"
        '
        'fraChanSelect
        '
        Me.fraChanSelect.BackColor = System.Drawing.SystemColors.Window
        Me.fraChanSelect.Controls.AddRange(New System.Windows.Forms.Control() {Me.txtNumChan, Me.lblChanPrompt})
        Me.fraChanSelect.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.fraChanSelect.ForeColor = System.Drawing.SystemColors.WindowText
        Me.fraChanSelect.Location = New System.Drawing.Point(8, 104)
        Me.fraChanSelect.Name = "fraChanSelect"
        Me.fraChanSelect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fraChanSelect.Size = New System.Drawing.Size(185, 57)
        Me.fraChanSelect.TabIndex = 21
        Me.fraChanSelect.TabStop = False
        Me.fraChanSelect.Text = "Channel Select"
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
        Me.txtNumChan.Location = New System.Drawing.Point(144, 24)
        Me.txtNumChan.MaxLength = 0
        Me.txtNumChan.Name = "txtNumChan"
        Me.txtNumChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtNumChan.Size = New System.Drawing.Size(25, 25)
        Me.txtNumChan.TabIndex = 23
        Me.txtNumChan.Text = "0"
        '
        'lblChanPrompt
        '
        Me.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window
        Me.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChanPrompt.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChanPrompt.Location = New System.Drawing.Point(16, 24)
        Me.lblChanPrompt.Name = "lblChanPrompt"
        Me.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChanPrompt.Size = New System.Drawing.Size(121, 17)
        Me.lblChanPrompt.TabIndex = 22
        Me.lblChanPrompt.Text = "Channel to display: "
        Me.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'tmrConvert
        '
        Me.tmrConvert.Interval = 300
        '
        'lblShowCalcResults
        '
        Me.lblShowCalcResults.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowCalcResults.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowCalcResults.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowCalcResults.ForeColor = System.Drawing.Color.Blue
        Me.lblShowCalcResults.Location = New System.Drawing.Point(224, 274)
        Me.lblShowCalcResults.Name = "lblShowCalcResults"
        Me.lblShowCalcResults.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowCalcResults.Size = New System.Drawing.Size(81, 17)
        Me.lblShowCalcResults.TabIndex = 11
        '
        'lblCalcResult
        '
        Me.lblCalcResult.BackColor = System.Drawing.SystemColors.Window
        Me.lblCalcResult.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCalcResult.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCalcResult.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCalcResult.Location = New System.Drawing.Point(8, 274)
        Me.lblCalcResult.Name = "lblCalcResult"
        Me.lblCalcResult.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCalcResult.Size = New System.Drawing.Size(209, 17)
        Me.lblCalcResult.TabIndex = 10
        Me.lblCalcResult.Text = "Value after conversion to voltage:"
        Me.lblCalcResult.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblShowData
        '
        Me.lblShowData.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowData.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowData.ForeColor = System.Drawing.Color.Blue
        Me.lblShowData.Location = New System.Drawing.Point(224, 256)
        Me.lblShowData.Name = "lblShowData"
        Me.lblShowData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowData.Size = New System.Drawing.Size(65, 17)
        Me.lblShowData.TabIndex = 2
        '
        'lblValueRead
        '
        Me.lblValueRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblValueRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValueRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValueRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValueRead.Location = New System.Drawing.Point(8, 256)
        Me.lblValueRead.Name = "lblValueRead"
        Me.lblValueRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValueRead.Size = New System.Drawing.Size(209, 17)
        Me.lblValueRead.TabIndex = 1
        Me.lblValueRead.Text = "Value read from selected channel:"
        Me.lblValueRead.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblGainCodeVal
        '
        Me.lblGainCodeVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblGainCodeVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblGainCodeVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblGainCodeVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblGainCodeVal.Location = New System.Drawing.Point(360, 208)
        Me.lblGainCodeVal.Name = "lblGainCodeVal"
        Me.lblGainCodeVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblGainCodeVal.Size = New System.Drawing.Size(33, 17)
        Me.lblGainCodeVal.TabIndex = 7
        Me.lblGainCodeVal.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblGainCode
        '
        Me.lblGainCode.BackColor = System.Drawing.SystemColors.Window
        Me.lblGainCode.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblGainCode.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblGainCode.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblGainCode.Location = New System.Drawing.Point(240, 208)
        Me.lblGainCode.Name = "lblGainCode"
        Me.lblGainCode.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblGainCode.Size = New System.Drawing.Size(89, 17)
        Me.lblGainCode.TabIndex = 6
        Me.lblGainCode.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblMinVal
        '
        Me.lblMinVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblMinVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblMinVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblMinVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblMinVal.Location = New System.Drawing.Point(176, 208)
        Me.lblMinVal.Name = "lblMinVal"
        Me.lblMinVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblMinVal.Size = New System.Drawing.Size(33, 17)
        Me.lblMinVal.TabIndex = 8
        Me.lblMinVal.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblFullScaleNeg
        '
        Me.lblFullScaleNeg.BackColor = System.Drawing.SystemColors.Window
        Me.lblFullScaleNeg.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFullScaleNeg.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFullScaleNeg.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFullScaleNeg.Location = New System.Drawing.Point(8, 208)
        Me.lblFullScaleNeg.Name = "lblFullScaleNeg"
        Me.lblFullScaleNeg.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFullScaleNeg.Size = New System.Drawing.Size(161, 17)
        Me.lblFullScaleNeg.TabIndex = 13
        Me.lblFullScaleNeg.Text = "Negative full scale voltage:"
        Me.lblFullScaleNeg.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblMaxVal
        '
        Me.lblMaxVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblMaxVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblMaxVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblMaxVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblMaxVal.Location = New System.Drawing.Point(176, 192)
        Me.lblMaxVal.Name = "lblMaxVal"
        Me.lblMaxVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblMaxVal.Size = New System.Drawing.Size(33, 17)
        Me.lblMaxVal.TabIndex = 9
        Me.lblMaxVal.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblFullScalePos
        '
        Me.lblFullScalePos.BackColor = System.Drawing.SystemColors.Window
        Me.lblFullScalePos.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFullScalePos.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblFullScalePos.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblFullScalePos.Location = New System.Drawing.Point(8, 192)
        Me.lblFullScalePos.Name = "lblFullScalePos"
        Me.lblFullScalePos.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFullScalePos.Size = New System.Drawing.Size(161, 17)
        Me.lblFullScalePos.TabIndex = 12
        Me.lblFullScalePos.Text = "Positive full scale voltage:"
        Me.lblFullScalePos.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblCVLabel
        '
        Me.lblCVLabel.BackColor = System.Drawing.SystemColors.Window
        Me.lblCVLabel.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCVLabel.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCVLabel.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCVLabel.Location = New System.Drawing.Point(344, 184)
        Me.lblCVLabel.Name = "lblCVLabel"
        Me.lblCVLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCVLabel.Size = New System.Drawing.Size(81, 17)
        Me.lblCVLabel.TabIndex = 15
        Me.lblCVLabel.Text = "Code Value"
        Me.lblCVLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblGCLabel
        '
        Me.lblGCLabel.BackColor = System.Drawing.SystemColors.Window
        Me.lblGCLabel.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblGCLabel.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblGCLabel.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblGCLabel.Location = New System.Drawing.Point(248, 184)
        Me.lblGCLabel.Name = "lblGCLabel"
        Me.lblGCLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblGCLabel.Size = New System.Drawing.Size(73, 17)
        Me.lblGCLabel.TabIndex = 14
        Me.lblGCLabel.Text = "Range Code"
        Me.lblGCLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblInstruct
        '
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Location = New System.Drawing.Point(16, 48)
        Me.lblInstruct.Name = "lblInstruct"
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.Size = New System.Drawing.Size(393, 41)
        Me.lblInstruct.TabIndex = 5
        Me.lblInstruct.Text = "NOTE: Please be certain that the board you are using supports the gain you are ch" & _
        "oosing and, if gain is not programmable, that the switches on the board are set " & _
        "correctly."
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 8)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(414, 17)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of raw data conversion."
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmManualConvert
        '
        Me.AcceptButton = Me.cmdStartConvert
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(433, 309)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStartConvert, Me.cmdStopConvert, Me.fraGainSel, Me.fraChanSelect, Me.lblShowCalcResults, Me.lblCalcResult, Me.lblShowData, Me.lblValueRead, Me.lblGainCodeVal, Me.lblGainCode, Me.lblMinVal, Me.lblFullScaleNeg, Me.lblMaxVal, Me.lblFullScalePos, Me.lblCVLabel, Me.lblGCLabel, Me.lblInstruct, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(110, 101)
        Me.Name = "frmManualConvert"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Data Convert"
        Me.fraGainSel.ResumeLayout(False)
        Me.fraChanSelect.ResumeLayout(False)
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


        lblGainCode.Text = "BIP5VOLTS" 'initialize gain
        lblGainCodeVal.Text = MccDaq.Range.Bip5Volts.ToString("D")
        lblMinVal.Text = "-5"
        lblMaxVal.Text = "5"

    End Sub

#End Region

End Class