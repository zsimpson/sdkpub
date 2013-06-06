'==============================================================================

' File:                         ULAI07.VB

' Library Call Demonstrated:    MccDaq.MccBoard.ATrig()

' Purpose:                      Waits for a specified analog input channel to
'                               go above or below a specified value.

' Demonstration:                Displays the digital value of a user-specified
'                               analog input channel when the user-specifed
'                               value is detected.

' Other Library Calls:          Mccdaq.MccBoard.ErrHandling()

' Special Requirements:         Board 0 must have an A/D converter.
'                               Analog signal on an input channel.

'==============================================================================

' Initialize variables
Option Strict Off
Option Explicit On 
Friend Class frmAnalogTrig
    Inherits System.Windows.Forms.Form

    Const Range As MccDaq.Range = MccDaq.Range.Bip5Volts

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Private Sub cmdStartConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartConvert.Click

        tmrStartConvert.Enabled = True
        cmdStartConvert.Visible = False
        cmdStopConvert.Visible = True
        lblTrigStatus.Text = "Waiting for trigger..."

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        End

    End Sub

    Private Function GetTrigCounts(ByRef range As MccDaq.Range, ByRef EngUnits As Single) As UInt16

        Dim fCounts As Single
        Dim iFSCounts As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim FSCounts As Integer
        Dim FSEngUnits As Single
        Dim FSCount As Integer


        'check if range is bipolar or unipolar
        FSCount = 0
        FSEngUnits = 0.0#
        ULStat = DaqBoard.ToEngUnits(range, System.Convert.ToUInt16(FSCounts), FSEngUnits)
        If (FSEngUnits < 0) Then
            'range is bipolar
            'check bitness
            FSCounts = &HFFFS 'max 12-bit value
            ULStat = DaqBoard.ToEngUnits(range, System.Convert.ToUInt16(FSCounts), FSEngUnits)
            If (FSEngUnits < 0) Then
                'must be 16-bit A/D
                FSCounts = 65535
                iFSCounts = &HFFFF
                ULStat = DaqBoard.ToEngUnits(range, System.Convert.ToUInt16(iFSCounts), FSEngUnits)
            End If

            fCounts = CSng((FSCounts / 2.0#) * (1.0# + EngUnits / FSEngUnits))
        Else
            'range is unipolar
            'check bitness
            FSCounts = &HFFFS 'max 12-bit value
            ULStat = DaqBoard.ToEngUnits(range, System.Convert.ToUInt16(FSCounts), FSEngUnits)
            ULStat = DaqBoard.ToEngUnits(range, System.Convert.ToUInt16(FSCounts + &H1000S), fCounts)
            If (fCounts >= 2.0# * FSEngUnits) Then
                'must be 16-bit A/D
                FSCounts = 65535
                iFSCounts = &HFFFFS
                ULStat = DaqBoard.ToEngUnits(range, System.Convert.ToUInt16(iFSCounts), FSEngUnits)
            End If

            fCounts = FSCounts * EngUnits / FSEngUnits
        End If

        If fCounts > FSCounts Then fCounts = FSCounts
        If fCounts < 0 Then fCounts = 0

        GetTrigCounts = Convert.ToUInt16(fCounts)
    End Function

    Private Sub tmrStartConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrStartConvert.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16
        Dim TrigType As MccDaq.TriggerType
        Dim TrigValue As UInt16

        Dim EngUnits As Single
        Dim Chan As Integer
        ' Monitor the channel with MccDaq.MccBoard.ATrig
        '  The input value that meets the threshold will become DataValue
        '  The data value will be updated and displayed until a Stop event occurs.
        '  Parameters:
        '    Chan       :the input channel number
        '    TrigType   :specifies whether the trigger is to be above
        '                or below TrigValue
        '    TrigValue  :the threshold value that will cause the trigger
        '    Range      :the range for the board
        '    DataValue  :the input value read from Chan

        Chan = Integer.Parse(txtShowChannel.Text)
        EngUnits = Single.Parse(txtShowTrigSet.Text)

        TrigValue = GetTrigCounts(Range, EngUnits)

        If chkNegTrigger.Checked = True Then
            TrigType = MccDaq.TriggerType.TrigBelow
        Else
            TrigType = MccDaq.TriggerType.TrigAbove
        End If

        tmrStartConvert.Stop()
        ULStat = DaqBoard.ATrig(Chan, TrigType, TrigValue, Range, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        tmrStartConvert.Start()

        ' print the value that meets the threshold

        lblTrigStatus.Text = "The value that caused the last trigger was:"
        lblShowTrigValue.Text = DataValue.ToString("D")

        ULStat = DaqBoard.ToEngUnits(Range, DataValue, EngUnits)
        lblShowVolts.Text = EngUnits.ToString("0.00###") + "V"

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
    Public WithEvents txtShowTrigSet As System.Windows.Forms.TextBox
    Public WithEvents chkPosTrigger As System.Windows.Forms.RadioButton
    Public WithEvents chkNegTrigger As System.Windows.Forms.RadioButton
    Public WithEvents txtShowChannel As System.Windows.Forms.TextBox
    Public WithEvents tmrStartConvert As System.Windows.Forms.Timer
    Public WithEvents lblShowVolts As System.Windows.Forms.Label
    Public WithEvents lblShowTrigValue As System.Windows.Forms.Label
    Public WithEvents lblTrigStatus As System.Windows.Forms.Label
    Public WithEvents lblEnterVal As System.Windows.Forms.Label
    Public WithEvents lblWarn As System.Windows.Forms.Label
    Public WithEvents lblTriggerChan As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdStartConvert = New System.Windows.Forms.Button()
        Me.txtShowTrigSet = New System.Windows.Forms.TextBox()
        Me.chkPosTrigger = New System.Windows.Forms.RadioButton()
        Me.chkNegTrigger = New System.Windows.Forms.RadioButton()
        Me.txtShowChannel = New System.Windows.Forms.TextBox()
        Me.tmrStartConvert = New System.Windows.Forms.Timer(Me.components)
        Me.lblShowVolts = New System.Windows.Forms.Label()
        Me.lblShowTrigValue = New System.Windows.Forms.Label()
        Me.lblTrigStatus = New System.Windows.Forms.Label()
        Me.lblEnterVal = New System.Windows.Forms.Label()
        Me.lblWarn = New System.Windows.Forms.Label()
        Me.lblTriggerChan = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopConvert
        '
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Location = New System.Drawing.Point(264, 256)
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.Size = New System.Drawing.Size(60, 26)
        Me.cmdStopConvert.TabIndex = 7
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Visible = False
        '
        'cmdStartConvert
        '
        Me.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartConvert.Location = New System.Drawing.Point(264, 256)
        Me.cmdStartConvert.Name = "cmdStartConvert"
        Me.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartConvert.Size = New System.Drawing.Size(60, 26)
        Me.cmdStartConvert.TabIndex = 2
        Me.cmdStartConvert.Text = "Start"
        '
        'txtShowTrigSet
        '
        Me.txtShowTrigSet.AcceptsReturn = True
        Me.txtShowTrigSet.AutoSize = False
        Me.txtShowTrigSet.BackColor = System.Drawing.SystemColors.Window
        Me.txtShowTrigSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtShowTrigSet.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtShowTrigSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtShowTrigSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtShowTrigSet.Location = New System.Drawing.Point(248, 160)
        Me.txtShowTrigSet.MaxLength = 0
        Me.txtShowTrigSet.Name = "txtShowTrigSet"
        Me.txtShowTrigSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtShowTrigSet.Size = New System.Drawing.Size(81, 25)
        Me.txtShowTrigSet.TabIndex = 10
        Me.txtShowTrigSet.Text = "1.25"
        '
        'chkPosTrigger
        '
        Me.chkPosTrigger.BackColor = System.Drawing.SystemColors.Window
        Me.chkPosTrigger.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkPosTrigger.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.chkPosTrigger.ForeColor = System.Drawing.SystemColors.WindowText
        Me.chkPosTrigger.Location = New System.Drawing.Point(64, 134)
        Me.chkPosTrigger.Name = "chkPosTrigger"
        Me.chkPosTrigger.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkPosTrigger.Size = New System.Drawing.Size(201, 20)
        Me.chkPosTrigger.TabIndex = 4
        Me.chkPosTrigger.TabStop = True
        Me.chkPosTrigger.Text = "Trigger above trigger value"
        '
        'chkNegTrigger
        '
        Me.chkNegTrigger.BackColor = System.Drawing.SystemColors.Window
        Me.chkNegTrigger.Checked = True
        Me.chkNegTrigger.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkNegTrigger.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.chkNegTrigger.ForeColor = System.Drawing.SystemColors.WindowText
        Me.chkNegTrigger.Location = New System.Drawing.Point(64, 115)
        Me.chkNegTrigger.Name = "chkNegTrigger"
        Me.chkNegTrigger.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkNegTrigger.Size = New System.Drawing.Size(201, 20)
        Me.chkNegTrigger.TabIndex = 3
        Me.chkNegTrigger.TabStop = True
        Me.chkNegTrigger.Text = "Trigger below trigger value"
        '
        'txtShowChannel
        '
        Me.txtShowChannel.AcceptsReturn = True
        Me.txtShowChannel.AutoSize = False
        Me.txtShowChannel.BackColor = System.Drawing.SystemColors.Window
        Me.txtShowChannel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtShowChannel.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtShowChannel.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtShowChannel.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtShowChannel.Location = New System.Drawing.Point(237, 39)
        Me.txtShowChannel.MaxLength = 0
        Me.txtShowChannel.Name = "txtShowChannel"
        Me.txtShowChannel.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtShowChannel.Size = New System.Drawing.Size(25, 25)
        Me.txtShowChannel.TabIndex = 0
        Me.txtShowChannel.Text = "0"
        '
        'tmrStartConvert
        '
        Me.tmrStartConvert.Interval = 200
        '
        'lblShowVolts
        '
        Me.lblShowVolts.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowVolts.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowVolts.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowVolts.ForeColor = System.Drawing.Color.Blue
        Me.lblShowVolts.Location = New System.Drawing.Point(248, 224)
        Me.lblShowVolts.Name = "lblShowVolts"
        Me.lblShowVolts.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowVolts.Size = New System.Drawing.Size(81, 17)
        Me.lblShowVolts.TabIndex = 11
        Me.lblShowVolts.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblShowTrigValue
        '
        Me.lblShowTrigValue.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowTrigValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowTrigValue.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowTrigValue.ForeColor = System.Drawing.Color.Blue
        Me.lblShowTrigValue.Location = New System.Drawing.Point(264, 200)
        Me.lblShowTrigValue.Name = "lblShowTrigValue"
        Me.lblShowTrigValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowTrigValue.Size = New System.Drawing.Size(49, 17)
        Me.lblShowTrigValue.TabIndex = 5
        Me.lblShowTrigValue.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblTrigStatus
        '
        Me.lblTrigStatus.BackColor = System.Drawing.SystemColors.Window
        Me.lblTrigStatus.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblTrigStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblTrigStatus.ForeColor = System.Drawing.Color.Blue
        Me.lblTrigStatus.Location = New System.Drawing.Point(8, 200)
        Me.lblTrigStatus.Name = "lblTrigStatus"
        Me.lblTrigStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblTrigStatus.Size = New System.Drawing.Size(249, 17)
        Me.lblTrigStatus.TabIndex = 6
        Me.lblTrigStatus.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblEnterVal
        '
        Me.lblEnterVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblEnterVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblEnterVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblEnterVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblEnterVal.Location = New System.Drawing.Point(32, 168)
        Me.lblEnterVal.Name = "lblEnterVal"
        Me.lblEnterVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblEnterVal.Size = New System.Drawing.Size(209, 17)
        Me.lblEnterVal.TabIndex = 12
        Me.lblEnterVal.Text = "Enter a trigger value in volts: "
        Me.lblEnterVal.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblWarn
        '
        Me.lblWarn.BackColor = System.Drawing.SystemColors.Window
        Me.lblWarn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.lblWarn.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblWarn.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblWarn.ForeColor = System.Drawing.Color.Red
        Me.lblWarn.Location = New System.Drawing.Point(8, 72)
        Me.lblWarn.Name = "lblWarn"
        Me.lblWarn.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblWarn.Size = New System.Drawing.Size(316, 33)
        Me.lblWarn.TabIndex = 8
        Me.lblWarn.Text = "Note: Channel above must have an input that meets the trigger conditions or progr" & _
        "am will appear to hang."
        Me.lblWarn.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblTriggerChan
        '
        Me.lblTriggerChan.BackColor = System.Drawing.SystemColors.Window
        Me.lblTriggerChan.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblTriggerChan.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblTriggerChan.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblTriggerChan.Location = New System.Drawing.Point(16, 40)
        Me.lblTriggerChan.Name = "lblTriggerChan"
        Me.lblTriggerChan.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblTriggerChan.Size = New System.Drawing.Size(212, 17)
        Me.lblTriggerChan.TabIndex = 1
        Me.lblTriggerChan.Text = "Enter the trigger input channel:"
        Me.lblTriggerChan.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(8, 0)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(313, 25)
        Me.lblDemoFunction.TabIndex = 9
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.ATrig()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmAnalogTrig
        '
        Me.AcceptButton = Me.cmdStartConvert
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(333, 289)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopConvert, Me.cmdStartConvert, Me.txtShowTrigSet, Me.chkPosTrigger, Me.chkNegTrigger, Me.txtShowChannel, Me.lblShowVolts, Me.lblShowTrigValue, Me.lblTrigStatus, Me.lblEnterVal, Me.lblWarn, Me.lblTriggerChan, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(221, 99)
        Me.Name = "frmAnalogTrig"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Trigger"
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

End Class