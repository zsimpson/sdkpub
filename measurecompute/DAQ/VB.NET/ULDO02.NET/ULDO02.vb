'==============================================================================

' File:                         ULDO02.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DBitOut()

' Purpose:                      Sets the state of a single digital output bit.

' Demonstration:                Configures FirstPortA for output and writes
'                               the bit values.

' Other Library Calls:          MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a digital output port.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmSetBitOut
    Inherits System.Windows.Forms.Form

    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalOut ' program first digital port for output mode

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Public chkSetBit As System.Windows.Forms.CheckBox()
    Private PortNum As MccDaq.DigitalPortType
    Private FirstBit As Short

    Private Sub chkSetBit_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs)

        Dim Index As Integer = chkSetBit.IndexOf(chkSetBit, eventSender)

        Dim ULStat As MccDaq.ErrorInfo
        Dim BitValue As MccDaq.DigitalLogicState
        Dim BitNum As Short
        Dim PortType As MccDaq.DigitalPortType

        BitNum = CShort(Index)

        ' For boards whose first port is not FIRSTPORTA (such as the USB-ERB08
        ' and the USB-SSR08) offset the BitNum by FirstBit

        If PortNum = MccDaq.DigitalPortType.AuxPort Then
          PortType = MccDaq.DigitalPortType.AuxPort
        Else
          PortType = MccDaq.DigitalPortType.FirstPortA
        End If

        If (chkSetBit(Index).Checked) Then
            BitValue = MccDaq.DigitalLogicState.High
        Else
            BitValue = MccDaq.DigitalLogicState.Low
        End If

        ULStat = DaqBoard.DBitOut(PortType, FirstBit + BitNum, BitValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

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
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
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
        Me.SuspendLayout()
        '
        'cmdEndProgram
        '
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Location = New System.Drawing.Point(240, 184)
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.Size = New System.Drawing.Size(57, 25)
        Me.cmdEndProgram.TabIndex = 9
        Me.cmdEndProgram.Text = "Quit"
        '
        '_chkSetBit_7
        '
        Me._chkSetBit_7.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_7.Checked = True
        Me._chkSetBit_7.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_7.Location = New System.Drawing.Point(192, 136)
        Me._chkSetBit_7.Name = "_chkSetBit_7"
        Me._chkSetBit_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_7.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_7.TabIndex = 2
        Me._chkSetBit_7.Text = "Set bit 7"
        '
        '_chkSetBit_3
        '
        Me._chkSetBit_3.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_3.Checked = True
        Me._chkSetBit_3.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_3.Location = New System.Drawing.Point(48, 136)
        Me._chkSetBit_3.Name = "_chkSetBit_3"
        Me._chkSetBit_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_3.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_3.TabIndex = 6
        Me._chkSetBit_3.Text = "Set bit 3"
        '
        '_chkSetBit_6
        '
        Me._chkSetBit_6.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_6.Checked = True
        Me._chkSetBit_6.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_6.Location = New System.Drawing.Point(192, 112)
        Me._chkSetBit_6.Name = "_chkSetBit_6"
        Me._chkSetBit_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_6.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_6.TabIndex = 3
        Me._chkSetBit_6.Text = "Set bit 6"
        '
        '_chkSetBit_2
        '
        Me._chkSetBit_2.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_2.Checked = True
        Me._chkSetBit_2.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_2.Location = New System.Drawing.Point(48, 112)
        Me._chkSetBit_2.Name = "_chkSetBit_2"
        Me._chkSetBit_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_2.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_2.TabIndex = 7
        Me._chkSetBit_2.Text = "Set bit 2"
        '
        '_chkSetBit_5
        '
        Me._chkSetBit_5.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_5.Checked = True
        Me._chkSetBit_5.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_5.Location = New System.Drawing.Point(192, 88)
        Me._chkSetBit_5.Name = "_chkSetBit_5"
        Me._chkSetBit_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_5.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_5.TabIndex = 4
        Me._chkSetBit_5.Text = "Set bit 5"
        '
        '_chkSetBit_1
        '
        Me._chkSetBit_1.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_1.Checked = True
        Me._chkSetBit_1.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_1.Location = New System.Drawing.Point(48, 88)
        Me._chkSetBit_1.Name = "_chkSetBit_1"
        Me._chkSetBit_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_1.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_1.TabIndex = 8
        Me._chkSetBit_1.Text = "Set bit 1"
        '
        '_chkSetBit_4
        '
        Me._chkSetBit_4.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_4.Checked = True
        Me._chkSetBit_4.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_4.Location = New System.Drawing.Point(192, 64)
        Me._chkSetBit_4.Name = "_chkSetBit_4"
        Me._chkSetBit_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_4.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_4.TabIndex = 5
        Me._chkSetBit_4.Text = "Set bit 4"
        '
        '_chkSetBit_0
        '
        Me._chkSetBit_0.BackColor = System.Drawing.SystemColors.Window
        Me._chkSetBit_0.Checked = True
        Me._chkSetBit_0.CheckState = System.Windows.Forms.CheckState.Indeterminate
        Me._chkSetBit_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._chkSetBit_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._chkSetBit_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._chkSetBit_0.Location = New System.Drawing.Point(48, 64)
        Me._chkSetBit_0.Name = "_chkSetBit_0"
        Me._chkSetBit_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._chkSetBit_0.Size = New System.Drawing.Size(81, 17)
        Me._chkSetBit_0.TabIndex = 1
        Me._chkSetBit_0.Text = "Set bit 0"
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(16, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(305, 25)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DBitOut()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmSetBitOut
        '
        Me.AcceptButton = Me.cmdEndProgram
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(339, 222)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdEndProgram, Me._chkSetBit_7, Me._chkSetBit_3, Me._chkSetBit_6, Me._chkSetBit_2, Me._chkSetBit_5, Me._chkSetBit_1, Me._chkSetBit_4, Me._chkSetBit_0, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmSetBitOut"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Digital Bit Out"
        Me.ResumeLayout(False)

    End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        AddHandler _chkSetBit_7.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_6.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_5.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_4.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_3.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_2.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_1.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged
        AddHandler _chkSetBit_0.CheckStateChanged, AddressOf chkSetBit_CheckStateChanged

        chkSetBit = New System.Windows.Forms.CheckBox(8) {}
        Me.chkSetBit.SetValue(_chkSetBit_7, 7)
        Me.chkSetBit.SetValue(_chkSetBit_3, 3)
        Me.chkSetBit.SetValue(_chkSetBit_6, 6)
        Me.chkSetBit.SetValue(_chkSetBit_2, 2)
        Me.chkSetBit.SetValue(_chkSetBit_5, 5)
        Me.chkSetBit.SetValue(_chkSetBit_1, 1)
        Me.chkSetBit.SetValue(_chkSetBit_4, 4)
        Me.chkSetBit.SetValue(_chkSetBit_0, 0)

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

         'get the first port on the device - some devices (such as the
        'USB-ERB08 and USB-SSR08) don't have FirstPortA, but do have
        'FirstPortCL.

        'Parameters:
        '      DevNum      : 0-based digital device index
        '      FirstPort   : return value for type of device

        Dim DevNum As Integer = 0
        Dim FirstPort As Integer
        ULStat = DaqBoard.DioConfig.GetDevType(0, FirstPort)

        Select Case FirstPort
            Case MccDaq.DigitalPortType.FirstPortA
                FirstBit = 0

            Case MccDaq.DigitalPortType.FirstPortB
                FirstBit = 8

            Case MccDaq.DigitalPortType.FirstPortCL
                FirstBit = 16

            Case MccDaq.DigitalPortType.FirstPortCH
                FirstBit = 20

            Case Else
                FirstBit = 0

          End Select

        ' configure FirstPortA for digital input
        '  Parameters:
        '    PortNum    :the input port
        '    Direction  :sets the port for input or output

        PortNum = FirstPort

        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' if the first port is FIRSTPORTCL, configure FIRSTPORTCH, too
        If FirstPort = MccDaq.DigitalPortType.FirstPortCL Then
            ULStat = DaqBoard.DConfigPort(PortNum + 1, Direction)
        End If

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    End Sub
#End Region

End Class