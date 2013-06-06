'==============================================================================

' File:                         ULAI01.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AIn()

' Purpose:                      Reads an A/D Input Channel.

' Demonstration:                Displays the analog input on a user-specified
'                               channel.

' Other Library Calls:          Mccdaq.MccBoard.ToEngUnits()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on an input channel.

'==============================================================================

Option Strict Off
Option Explicit On 

Public Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    ' Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click

        cmdStartConvert.Visible = False
        cmdStopConvert.Visible = True
        tmrConvert.Enabled = True

    End Sub

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick
        Dim EngUnits As Single
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As System.UInt16
        Dim Chan As Integer

        Dim Range As MccDaq.Range

        tmrConvert.Stop()


        ' Collect the data by calling AIn memeber function of MccBoard object

        '  Parameters:
        '    Chan       :the input channel number
        '    Range      :the Range for the board.
        '    DataValue  :the name for the value collected

        Range = Range.Bip5Volts   ' select Bip5Volts (member of Range enumeration)
        Chan = Integer.Parse(txtNumChan.Text) ' set input channel

        ULStat = DaqBoard.AIn(Chan, Range, DataValue)
        If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadRange Then
            MsgBox("Change the Range argument to one supported by this board.", 0, "Unsupported Range")
        End If

        If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            ' Convert raw data to Volts by calling ToEngUnits (member function of MccBoard class)  
            ULStat = DaqBoard.ToEngUnits(Range, DataValue, EngUnits)
        Else
            Stop
        End If

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        Else
            lblShowData.Text = DataValue.ToString()                ' print the counts
            lblShowVolts.Text = EngUnits.ToString("F4") + " Volts" ' print the voltage

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
    Public WithEvents lblShowVolts As System.Windows.Forms.Label
    Public WithEvents lblVoltsRead As System.Windows.Forms.Label
    Public WithEvents lblValueRead As System.Windows.Forms.Label
    Public WithEvents lblChanPrompt As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Friend WithEvents lblShowData As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.txtNumChan = New System.Windows.Forms.TextBox()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowVolts = New System.Windows.Forms.Label()
        Me.lblVoltsRead = New System.Windows.Forms.Label()
        Me.lblValueRead = New System.Windows.Forms.Label()
        Me.lblChanPrompt = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.lblShowData = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(232, 176)
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
        Me.cmdStopConvert.Location = New System.Drawing.Point(232, 176)
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
        Me.txtNumChan.Location = New System.Drawing.Point(224, 56)
        Me.txtNumChan.MaxLength = 0
        Me.txtNumChan.Name = "txtNumChan"
        Me.txtNumChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtNumChan.Size = New System.Drawing.Size(33, 25)
        Me.txtNumChan.TabIndex = 0
        Me.txtNumChan.Text = "0"
        Me.txtNumChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'tmrConvert
        '
        '
        'lblShowVolts
        '
        Me.lblShowVolts.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowVolts.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowVolts.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowVolts.ForeColor = System.Drawing.Color.Blue
        Me.lblShowVolts.Location = New System.Drawing.Point(208, 136)
        Me.lblShowVolts.Name = "lblShowVolts"
        Me.lblShowVolts.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowVolts.Size = New System.Drawing.Size(80, 16)
        Me.lblShowVolts.TabIndex = 8
        Me.lblShowVolts.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'lblVoltsRead
        '
        Me.lblVoltsRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblVoltsRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblVoltsRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblVoltsRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblVoltsRead.Location = New System.Drawing.Point(8, 136)
        Me.lblVoltsRead.Name = "lblVoltsRead"
        Me.lblVoltsRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblVoltsRead.Size = New System.Drawing.Size(184, 16)
        Me.lblVoltsRead.TabIndex = 7
        Me.lblVoltsRead.Text = "Value converted to voltage:"
        Me.lblVoltsRead.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'lblValueRead
        '
        Me.lblValueRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblValueRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValueRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValueRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValueRead.Location = New System.Drawing.Point(16, 104)
        Me.lblValueRead.Name = "lblValueRead"
        Me.lblValueRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValueRead.Size = New System.Drawing.Size(184, 16)
        Me.lblValueRead.TabIndex = 3
        Me.lblValueRead.Text = "Value read from selected channel:"
        Me.lblValueRead.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'lblChanPrompt
        '
        Me.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window
        Me.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChanPrompt.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChanPrompt.Location = New System.Drawing.Point(16, 65)
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
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(286, 25)
        Me.lblDemoFunction.TabIndex = 2
        Me.lblDemoFunction.Text = "Demonstration of MccBoard.AIn"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblShowData
        '
        Me.lblShowData.Font = New System.Drawing.Font("Arial", 8.0!)
        Me.lblShowData.ForeColor = System.Drawing.Color.Blue
        Me.lblShowData.Location = New System.Drawing.Point(208, 104)
        Me.lblShowData.Name = "lblShowData"
        Me.lblShowData.Size = New System.Drawing.Size(80, 16)
        Me.lblShowData.TabIndex = 9
        Me.lblShowData.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'frmDataDisplay
        '
        Me.AcceptButton = Me.cmdStartConvert
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(304, 220)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblShowData, Me.cmdStartConvert, Me.cmdStopConvert, Me.txtNumChan, Me.lblShowVolts, Me.lblVoltsRead, Me.lblValueRead, Me.lblChanPrompt, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(182, 100)
        Me.Name = "frmDataDisplay"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Input"
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


End Class