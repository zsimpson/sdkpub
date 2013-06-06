'==============================================================================

' File:                         ULDO05.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DBitOut()

' Purpose:                      Sets the state of a single digital output bit.

' Demonstration:                Writes bit values to AuxPort.

' Other Library Calls:          MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccService.ErrHandling()
'                               MccDaq.MccBoard.DioConfig.GetDevType()
'                               MccDaq.MccBoard.DioConfig.GetDInMask()
'                               MccDaq.MccBoard.DioConfig.GetDOutMask()

' Special Requirements:         Board 0 must have a digital output port.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmSetBitOut
    Inherits System.Windows.Forms.Form


    Const PortNum As MccDaq.DigitalPortType = MccDaq.DigitalPortType.AuxPort ' use first digital port
    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalOut ' program first digital port for output mode

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Public chkSetBit As System.Windows.Forms.CheckBox()

    Private Sub chkSetBit_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs)
        Dim ULStat As MccDaq.ErrorInfo
        Dim BitValue As MccDaq.DigitalLogicState
        Dim BitNum As Short
        Dim PortType As MccDaq.DigitalPortType
        Dim Index As Integer = chkSetBit.IndexOf(chkSetBit, eventSender)

        BitNum = CShort(Index)
        PortType = PortNum

        If (chkSetBit(Index).Checked) Then
            BitValue = MccDaq.DigitalLogicState.High
        Else
            BitValue = MccDaq.DigitalLogicState.Low
        End If

        ULStat = DaqBoard.DBitOut(PortType, BitNum, BitValue)
        If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadBitNumber Then
            MsgBox("Boards only supports bit numbers less than " & BitNum.ToString("0"), 0, "Bit value too high")
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If
        End If
    End Sub

    Private Sub cmdEndProgram_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdEndProgram.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        DataValue = Convert.ToUInt16(0)

        ULStat = DaqBoard.DOut(PortNum, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

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
    Public WithEvents cmdEndProgram As System.Windows.Forms.Button
    Public WithEvents _chkSetBit_7 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_3 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_6 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_2 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_5 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_1 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_4 As System.Windows.Forms.CheckBox
    Public WithEvents _chkSetBit_0 As System.Windows.Forms.CheckBox
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmSetBitOut))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me._chkSetBit_7 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_3 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_6 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_2 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_5 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_1 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_4 = New System.Windows.Forms.CheckBox()
        Me._chkSetBit_0 = New System.Windows.Forms.CheckBox()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library Digital Bit Out"
        Me.ClientSize = New System.Drawing.Size(339, 222)
        Me.Location = New System.Drawing.Point(7, 103)
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
        Me.Name = "frmSetBitOut"
        Me.cmdEndProgram.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdEndProgram.Text = "Quit"
        Me.AcceptButton = Me.cmdEndProgram
        Me.cmdEndProgram.Size = New System.Drawing.Size(57, 25)
        Me.cmdEndProgram.Location = New System.Drawing.Point(240, 184)
        Me.cmdEndProgram.TabIndex = 9
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.CausesValidation = True
        Me.cmdEndProgram.Enabled = True
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.TabStop = True
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me._chkSetBit_7.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_7.Text = "Set bit 7"
        Me._chkSetBit_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_7.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_7.Location = New System.Drawing.Point(192, 152)
        Me._chkSetBit_7.TabIndex = 2
        Me._chkSetBit_7.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_7.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_7.CausesValidation = True
        Me._chkSetBit_7.Enabled = True
        Me._chkSetBit_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_7.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_7.TabStop = True
        Me._chkSetBit_7.Visible = True
        Me._chkSetBit_7.Name = "_chkSetBit_7"
        Me._chkSetBit_3.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_3.Text = "Set bit 3"
        Me._chkSetBit_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_3.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_3.Location = New System.Drawing.Point(48, 152)
        Me._chkSetBit_3.TabIndex = 6
        Me._chkSetBit_3.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_3.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_3.CausesValidation = True
        Me._chkSetBit_3.Enabled = True
        Me._chkSetBit_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_3.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_3.TabStop = True
        Me._chkSetBit_3.Visible = True
        Me._chkSetBit_3.Name = "_chkSetBit_3"
        Me._chkSetBit_6.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_6.Text = "Set bit 6"
        Me._chkSetBit_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_6.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_6.Location = New System.Drawing.Point(192, 128)
        Me._chkSetBit_6.TabIndex = 3
        Me._chkSetBit_6.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_6.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_6.CausesValidation = True
        Me._chkSetBit_6.Enabled = True
        Me._chkSetBit_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_6.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_6.TabStop = True
        Me._chkSetBit_6.Visible = True
        Me._chkSetBit_6.Name = "_chkSetBit_6"
        Me._chkSetBit_2.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_2.Text = "Set bit 2"
        Me._chkSetBit_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_2.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_2.Location = New System.Drawing.Point(48, 128)
        Me._chkSetBit_2.TabIndex = 7
        Me._chkSetBit_2.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_2.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_2.CausesValidation = True
        Me._chkSetBit_2.Enabled = True
        Me._chkSetBit_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_2.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_2.TabStop = True
        Me._chkSetBit_2.Visible = True
        Me._chkSetBit_2.Name = "_chkSetBit_2"
        Me._chkSetBit_5.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_5.Text = "Set bit 5"
        Me._chkSetBit_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_5.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_5.Location = New System.Drawing.Point(192, 104)
        Me._chkSetBit_5.TabIndex = 4
        Me._chkSetBit_5.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_5.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_5.CausesValidation = True
        Me._chkSetBit_5.Enabled = True
        Me._chkSetBit_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_5.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_5.TabStop = True
        Me._chkSetBit_5.Visible = True
        Me._chkSetBit_5.Name = "_chkSetBit_5"
        Me._chkSetBit_1.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_1.Text = "Set bit 1"
        Me._chkSetBit_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_1.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_1.Location = New System.Drawing.Point(48, 104)
        Me._chkSetBit_1.TabIndex = 8
        Me._chkSetBit_1.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_1.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_1.CausesValidation = True
        Me._chkSetBit_1.Enabled = True
        Me._chkSetBit_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_1.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_1.TabStop = True
        Me._chkSetBit_1.Visible = True
        Me._chkSetBit_1.Name = "_chkSetBit_1"
        Me._chkSetBit_4.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_4.Text = "Set bit 4"
        Me._chkSetBit_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_4.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_4.Location = New System.Drawing.Point(192, 80)
        Me._chkSetBit_4.TabIndex = 5
        Me._chkSetBit_4.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_4.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_4.CausesValidation = True
        Me._chkSetBit_4.Enabled = True
        Me._chkSetBit_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_4.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_4.TabStop = True
        Me._chkSetBit_4.Visible = True
        Me._chkSetBit_4.Name = "_chkSetBit_4"
        Me._chkSetBit_0.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_0.Text = "Set bit 0"
        Me._chkSetBit_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_0.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_0.Location = New System.Drawing.Point(48, 80)
        Me._chkSetBit_0.TabIndex = 1
        Me._chkSetBit_0.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_0.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me._chkSetBit_0.CausesValidation = True
        Me._chkSetBit_0.Enabled = True
        Me._chkSetBit_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_0.Appearance = System.Windows.Forms.Appearance.Normal
        Me._chkSetBit_0.TabStop = True
        Me._chkSetBit_0.Visible = True
        Me._chkSetBit_0.Name = "_chkSetBit_0"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DBitOut() with AuxPort"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(249, 41)
        Me.lblDemoFunction.Location = New System.Drawing.Point(40, 16)
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
        Me.Controls.Add(cmdEndProgram)
        Me.Controls.Add(_chkSetBit_7)
        Me.Controls.Add(_chkSetBit_3)
        Me.Controls.Add(_chkSetBit_6)
        Me.Controls.Add(_chkSetBit_2)
        Me.Controls.Add(_chkSetBit_5)
        Me.Controls.Add(_chkSetBit_1)
        Me.Controls.Add(_chkSetBit_4)
        Me.Controls.Add(_chkSetBit_0)
        Me.Controls.Add(lblDemoFunction)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo
        Dim devNum As Integer
        Dim inmask, outmask As Integer
        Dim PortType As MccDaq.DigitalPortType

        chkSetBit = New System.Windows.Forms.CheckBox(8) {}
        Me.chkSetBit.SetValue(_chkSetBit_7, 7)
        Me.chkSetBit.SetValue(_chkSetBit_3, 3)
        Me.chkSetBit.SetValue(_chkSetBit_6, 6)
        Me.chkSetBit.SetValue(_chkSetBit_2, 2)
        Me.chkSetBit.SetValue(_chkSetBit_5, 5)
        Me.chkSetBit.SetValue(_chkSetBit_1, 1)
        Me.chkSetBit.SetValue(_chkSetBit_4, 4)
        Me.chkSetBit.SetValue(_chkSetBit_0, 0)

        AddHandler _chkSetBit_7.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_6.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_5.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_4.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_3.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_2.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_1.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_0.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged



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

        ' Determine if board has AuxPort
        '  Parameters:
        '      devNum      : 0-based digital device index
        '      PortType    : return value for type of device
        devNum = 0
        PortType = 0
        ULStat = DaqBoard.DioConfig.GetDevType(devNum, PortType)
        If (PortType <> MccDaq.DigitalPortType.AuxPort) Then
            Stop
            End
        End If


        ' Check if AuxPort needs configuring 
        '  Parameters:
        '      devNum  : 0-based digital device index
        '      mask    : bitmask indicating corresponding bit is in direction of ConfigItem(DIINMASk or DIOUTMASK)
        inmask = 0
        outmask = 0
        ULStat = DaqBoard.DioConfig.GetDInMask(devNum, inmask)
        If (ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then Stop

        ULStat = DaqBoard.DioConfig.GetDOutMask(devNum, outmask)
        If (ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then Stop

        ' Only non-configurable AuxPort's have overlapping input and output bitmasks 
        If (0 = (inmask And outmask)) Then ULStat = DaqBoard.DConfigPort(PortType, MccDaq.DigitalPortDirection.DigitalOut)


    End Sub
#End Region

End Class