'==============================================================================

' File:                         ULTI01.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.TIn()

' Purpose:                      Reads a multiplexer input channel.

' Demonstration:                Displays the temperature input on a MUX
'                               channel.

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Unless the board at BoardNum(=0) does not use
'                               EXP boards for temperature measurements(the
'                               CIO-DAS-TC,for example), it must
'                               have an A/D converter with an attached EXP
'                               board.  Thermocouples must be wired to EXP
'                              channels selected.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmDataDisplay
    Inherits System.Windows.Forms.Form


    ' Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)
    Dim UsesEXPs As Integer

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click

        If Val(txtExpChan.Text) < 0 Then txtExpChan.Text = "0"
        If Val(txtExpChan.Text) > 15 Then txtExpChan.Text = "15"

        cmdStartConvert.Visible = False
        cmdStopConvert.Visible = True
        tmrConvert.Enabled = True

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        End

    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim TempValue As Single
        Dim Options As MccDaq.ThermocoupleOptions
        Dim Chan As Integer
        Dim MccScale As MccDaq.TempScale
        Dim ADChan As Short

        ' Collect the data with Mccdaq.MccBoard.TIn()

        ' Parameters:
        '   Chan       :the A/D and channel number; starts at 16
        '                calculated by (ADChan + 1) * 16 + EXPChan%
        '   MccScale    :the temperature scale (F, C or K)
        '   DataValue  :the name for the value collected
        '   ADChan     :usually channel 0 for CIO-EXP16

        ADChan = 0 ' allows access to 16 channels on the EXP board
        ' increasing this number allows access to upper
        ' bank on EXP32 and additional EXP boards

        MccScale = MccDaq.TempScale.Celsius
        If UsesEXPs > 0 Then
            Chan = Integer.Parse(txtExpChan.Text) + (ADChan + 1) * 16
        Else
            Chan = Integer.Parse(txtExpChan.Text)
        End If

        lblShowData.Text = TempValue.ToString("0") + "C" ' print the value
        Options = MccDaq.ThermocoupleOptions.Filter

        tmrConvert.Stop()

        ULStat = DaqBoard.TIn(Chan, MccScale, TempValue, Options)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblShowData.Text = TempValue.ToString("0") + "°C" ' print the value
        
        tmrConvert.Start()

    End Sub

    Private Sub txtExpChan_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtExpChan.TextChanged

        tmrConvert.Enabled = False
        cmdStartConvert.Visible = True
        cmdStopConvert.Visible = False


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
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents cmdStartConvert As System.Windows.Forms.Button
    Public WithEvents txtExpChan As System.Windows.Forms.TextBox
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
    Public WithEvents lblShowData As System.Windows.Forms.Label
    Public WithEvents lblValueRead As System.Windows.Forms.Label
    Public WithEvents lblChanPrompt As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me.txtExpChan = New System.Windows.Forms.TextBox()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowData = New System.Windows.Forms.Label()
        Me.lblValueRead = New System.Windows.Forms.Label()
        Me.lblChanPrompt = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(288, 152)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(57, 25)
        Me.cmdStopConvert.TabIndex = 6
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Visible = False
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(288, 152)
        Me.cmdStartConvert.Name = "cmdStartConvert"
        Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartConvert.Size = New System.Drawing.Size(57, 25)
        Me.cmdStartConvert.TabIndex = 5
        Me.cmdStartConvert.Text = "Start"
        '
        'txtExpChan
        '
        Me.txtExpChan.AcceptsReturn = True
        Me.txtExpChan.AutoSize = False
        Me.txtExpChan.BackColor = System.Drawing.SystemColors.Window
        Me.txtExpChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtExpChan.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtExpChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtExpChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtExpChan.Location = New System.Drawing.Point(312, 56)
        Me.txtExpChan.MaxLength = 0
        Me.txtExpChan.Name = "txtExpChan"
        Me.txtExpChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtExpChan.Size = New System.Drawing.Size(33, 25)
        Me.txtExpChan.TabIndex = 0
        Me.txtExpChan.Text = "0"
        '
        'tmrConvert
        '
        Me.tmrConvert.Interval = 250
        '
        'lblShowData
        '
        Me.lblShowData.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowData.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowData.ForeColor = System.Drawing.Color.Blue
        Me.lblShowData.Location = New System.Drawing.Point(280, 104)
        Me.lblShowData.Name = "lblShowData"
        Me.lblShowData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowData.Size = New System.Drawing.Size(65, 17)
        Me.lblShowData.TabIndex = 4
        '
        'lblValueRead
        '
        Me.lblValueRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblValueRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValueRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValueRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValueRead.Location = New System.Drawing.Point(24, 104)
        Me.lblValueRead.Name = "lblValueRead"
        Me.lblValueRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValueRead.Size = New System.Drawing.Size(241, 17)
        Me.lblValueRead.TabIndex = 3
        Me.lblValueRead.Text = "Temperature read from selected channel:"
        '
        'lblChanPrompt
        '
        Me.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window
        Me.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChanPrompt.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChanPrompt.Location = New System.Drawing.Point(8, 64)
        Me.lblChanPrompt.Name = "lblChanPrompt"
        Me.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChanPrompt.Size = New System.Drawing.Size(297, 17)
        Me.lblChanPrompt.TabIndex = 1
        Me.lblChanPrompt.Text = "Enter the multiplexor channel to display (0 to 15): "
        Me.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(40, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(273, 25)
        Me.lblDemoFunction.TabIndex = 2
        Me.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.TIn()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDataDisplay
        '
        Me.AcceptButton = Me.cmdStartConvert
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(360, 190)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopConvert, Me.cmdStartConvert, Me.txtExpChan, Me.lblShowData, Me.lblValueRead, Me.lblChanPrompt, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Temperature Measurement"
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ConfigItem As Short
        Dim DevNum As Short
        Dim InfoType As Short
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

        ' Determine if the board uses EXP boards for temperature measurements
        DevNum = 0
        UsesEXPs = 0
        ULStat = DaqBoard.BoardConfig.GetUsesExps(UsesEXPs)
        If (ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then UsesEXPs = 0

    End Sub
#End Region

End Class