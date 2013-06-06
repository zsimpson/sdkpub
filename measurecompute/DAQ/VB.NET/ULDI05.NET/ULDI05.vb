'==============================================================================

' File:                         ULDI05.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DBitIn()

' Purpose:                      Reads the status of single digital input bit.

' Demonstration:                Reads bit values from AuxPort.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccBoard.DioConfig.GetDevType()
'                               MccDaq.MccBoard.DioConfig.GetDInMask()
'                               MccDaq.MccBoard.DioConfig.GetDOutMask()

' Special Requirements:         Board 0 must have a digital input port.
'                               Digital value on digital inputs.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDigIn
    Inherits System.Windows.Forms.Form

    Const PortType As MccDaq.DigitalPortType = MccDaq.DigitalPortType.AuxPort ' set port type to programmable
    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalIn ' program port for input mode

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Public lblShowBitNum As System.Windows.Forms.Label()
    Public lblShowBitVal As System.Windows.Forms.Label()

    Private Sub cmdStopRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopRead.Click

        End

    End Sub

    Private Sub tmrReadInputs_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadInputs.Tick
        Dim BitValue As MccDaq.DigitalLogicState
        Dim BitNum As Integer
        Dim i As Short
        Dim ULStat As MccDaq.ErrorInfo

        tmrReadInputs.Stop()

        ' read the bits of AuxPort digital input and display

        '  Parameters:
        '    PortType    :the type of port
        '    BitNum     :the number of the bit to read from the port
        '    BitValue   :the value read from the port

        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.DontPrint, MccDaq.ErrorHandling.StopAll)
        'so invalid bit numbers can
        'be handled locally.
        For i = 0 To 7
            BitNum = i
            ULStat = DaqBoard.DBitIn(PortType, BitNum, BitValue)
            If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                lblShowBitVal(i).Text = Convert.ToInt32(BitValue).ToString("0")
            ElseIf ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadBitNumber Then
                lblShowBitVal(i).Text = "X" 'Trap invalid bit numbers
            Else
                Stop
            End If
        Next i
        
        tmrReadInputs.Start()

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
    Public WithEvents cmdStopRead As System.Windows.Forms.Button
    Public WithEvents tmrReadInputs As System.Windows.Forms.Timer
    Public WithEvents _lblShowBitVal_0 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_1 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_2 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_3 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_4 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_5 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_6 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitVal_7 As System.Windows.Forms.Label
    Public WithEvents lblBitVal As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_7 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_6 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_5 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_4 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_3 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_2 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_1 As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_0 As System.Windows.Forms.Label
    Public WithEvents lblBitNum As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmDigIn))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadInputs = New System.Windows.Forms.Timer(components)
        Me._lblShowBitVal_0 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_1 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_2 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_3 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_4 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_5 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_6 = New System.Windows.Forms.Label()
        Me._lblShowBitVal_7 = New System.Windows.Forms.Label()
        Me.lblBitVal = New System.Windows.Forms.Label()
        Me._lblShowBitNum_7 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_6 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_5 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_4 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_3 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_2 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_1 = New System.Windows.Forms.Label()
        Me._lblShowBitNum_0 = New System.Windows.Forms.Label()
        Me.lblBitNum = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library Digital Bit Input"
        Me.ClientSize = New System.Drawing.Size(326, 232)
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
        Me.Name = "frmDigIn"
        Me.cmdStopRead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStopRead.Text = "Quit"
        Me.AcceptButton = Me.cmdStopRead
        Me.cmdStopRead.Size = New System.Drawing.Size(57, 33)
        Me.cmdStopRead.Location = New System.Drawing.Point(248, 184)
        Me.cmdStopRead.TabIndex = 20
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.CausesValidation = True
        Me.cmdStopRead.Enabled = True
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.TabStop = True
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.tmrReadInputs.Interval = 200
        Me.tmrReadInputs.Enabled = True
        Me._lblShowBitVal_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_0.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_0.Location = New System.Drawing.Point(288, 144)
        Me._lblShowBitVal_0.TabIndex = 1
        Me._lblShowBitVal_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_0.Enabled = True
        Me._lblShowBitVal_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_0.UseMnemonic = True
        Me._lblShowBitVal_0.Visible = True
        Me._lblShowBitVal_0.AutoSize = False
        Me._lblShowBitVal_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_0.Name = "_lblShowBitVal_0"
        Me._lblShowBitVal_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_1.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_1.Location = New System.Drawing.Point(264, 144)
        Me._lblShowBitVal_1.TabIndex = 2
        Me._lblShowBitVal_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_1.Enabled = True
        Me._lblShowBitVal_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_1.UseMnemonic = True
        Me._lblShowBitVal_1.Visible = True
        Me._lblShowBitVal_1.AutoSize = False
        Me._lblShowBitVal_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_1.Name = "_lblShowBitVal_1"
        Me._lblShowBitVal_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_2.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_2.Location = New System.Drawing.Point(240, 144)
        Me._lblShowBitVal_2.TabIndex = 3
        Me._lblShowBitVal_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_2.Enabled = True
        Me._lblShowBitVal_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_2.UseMnemonic = True
        Me._lblShowBitVal_2.Visible = True
        Me._lblShowBitVal_2.AutoSize = False
        Me._lblShowBitVal_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_2.Name = "_lblShowBitVal_2"
        Me._lblShowBitVal_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_3.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_3.Location = New System.Drawing.Point(216, 144)
        Me._lblShowBitVal_3.TabIndex = 4
        Me._lblShowBitVal_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_3.Enabled = True
        Me._lblShowBitVal_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_3.UseMnemonic = True
        Me._lblShowBitVal_3.Visible = True
        Me._lblShowBitVal_3.AutoSize = False
        Me._lblShowBitVal_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_3.Name = "_lblShowBitVal_3"
        Me._lblShowBitVal_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_4.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_4.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_4.Location = New System.Drawing.Point(168, 144)
        Me._lblShowBitVal_4.TabIndex = 5
        Me._lblShowBitVal_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_4.Enabled = True
        Me._lblShowBitVal_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_4.UseMnemonic = True
        Me._lblShowBitVal_4.Visible = True
        Me._lblShowBitVal_4.AutoSize = False
        Me._lblShowBitVal_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_4.Name = "_lblShowBitVal_4"
        Me._lblShowBitVal_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_5.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_5.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_5.Location = New System.Drawing.Point(144, 144)
        Me._lblShowBitVal_5.TabIndex = 6
        Me._lblShowBitVal_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_5.Enabled = True
        Me._lblShowBitVal_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_5.UseMnemonic = True
        Me._lblShowBitVal_5.Visible = True
        Me._lblShowBitVal_5.AutoSize = False
        Me._lblShowBitVal_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_5.Name = "_lblShowBitVal_5"
        Me._lblShowBitVal_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_6.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_6.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_6.Location = New System.Drawing.Point(120, 144)
        Me._lblShowBitVal_6.TabIndex = 7
        Me._lblShowBitVal_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_6.Enabled = True
        Me._lblShowBitVal_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_6.UseMnemonic = True
        Me._lblShowBitVal_6.Visible = True
        Me._lblShowBitVal_6.AutoSize = False
        Me._lblShowBitVal_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_6.Name = "_lblShowBitVal_6"
        Me._lblShowBitVal_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitVal_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitVal_7.ForeColor = System.Drawing.Color.Blue
        Me._lblShowBitVal_7.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitVal_7.Location = New System.Drawing.Point(96, 144)
        Me._lblShowBitVal_7.TabIndex = 0
        Me._lblShowBitVal_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitVal_7.Enabled = True
        Me._lblShowBitVal_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitVal_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitVal_7.UseMnemonic = True
        Me._lblShowBitVal_7.Visible = True
        Me._lblShowBitVal_7.AutoSize = False
        Me._lblShowBitVal_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitVal_7.Name = "_lblShowBitVal_7"
        Me.lblBitVal.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblBitVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblBitVal.Text = "Bit Value:"
        Me.lblBitVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblBitVal.Size = New System.Drawing.Size(65, 17)
        Me.lblBitVal.Location = New System.Drawing.Point(16, 144)
        Me.lblBitVal.TabIndex = 8
        Me.lblBitVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblBitVal.Enabled = True
        Me.lblBitVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblBitVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblBitVal.UseMnemonic = True
        Me.lblBitVal.Visible = True
        Me.lblBitVal.AutoSize = False
        Me.lblBitVal.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblBitVal.Name = "lblBitVal"
        Me._lblShowBitNum_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_7.Text = "0"
        Me._lblShowBitNum_7.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_7.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_7.Location = New System.Drawing.Point(288, 120)
        Me._lblShowBitNum_7.TabIndex = 17
        Me._lblShowBitNum_7.Enabled = True
        Me._lblShowBitNum_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_7.UseMnemonic = True
        Me._lblShowBitNum_7.Visible = True
        Me._lblShowBitNum_7.AutoSize = False
        Me._lblShowBitNum_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_7.Name = "_lblShowBitNum_7"
        Me._lblShowBitNum_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_6.Text = "1"
        Me._lblShowBitNum_6.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_6.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_6.Location = New System.Drawing.Point(264, 120)
        Me._lblShowBitNum_6.TabIndex = 16
        Me._lblShowBitNum_6.Enabled = True
        Me._lblShowBitNum_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_6.UseMnemonic = True
        Me._lblShowBitNum_6.Visible = True
        Me._lblShowBitNum_6.AutoSize = False
        Me._lblShowBitNum_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_6.Name = "_lblShowBitNum_6"
        Me._lblShowBitNum_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_5.Text = "2"
        Me._lblShowBitNum_5.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_5.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_5.Location = New System.Drawing.Point(240, 120)
        Me._lblShowBitNum_5.TabIndex = 15
        Me._lblShowBitNum_5.Enabled = True
        Me._lblShowBitNum_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_5.UseMnemonic = True
        Me._lblShowBitNum_5.Visible = True
        Me._lblShowBitNum_5.AutoSize = False
        Me._lblShowBitNum_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_5.Name = "_lblShowBitNum_5"
        Me._lblShowBitNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_4.Text = "3"
        Me._lblShowBitNum_4.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_4.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_4.Location = New System.Drawing.Point(216, 120)
        Me._lblShowBitNum_4.TabIndex = 14
        Me._lblShowBitNum_4.Enabled = True
        Me._lblShowBitNum_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_4.UseMnemonic = True
        Me._lblShowBitNum_4.Visible = True
        Me._lblShowBitNum_4.AutoSize = False
        Me._lblShowBitNum_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_4.Name = "_lblShowBitNum_4"
        Me._lblShowBitNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_3.Text = "4"
        Me._lblShowBitNum_3.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_3.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_3.Location = New System.Drawing.Point(168, 120)
        Me._lblShowBitNum_3.TabIndex = 13
        Me._lblShowBitNum_3.Enabled = True
        Me._lblShowBitNum_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_3.UseMnemonic = True
        Me._lblShowBitNum_3.Visible = True
        Me._lblShowBitNum_3.AutoSize = False
        Me._lblShowBitNum_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_3.Name = "_lblShowBitNum_3"
        Me._lblShowBitNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_2.Text = "5"
        Me._lblShowBitNum_2.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_2.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_2.Location = New System.Drawing.Point(144, 120)
        Me._lblShowBitNum_2.TabIndex = 12
        Me._lblShowBitNum_2.Enabled = True
        Me._lblShowBitNum_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_2.UseMnemonic = True
        Me._lblShowBitNum_2.Visible = True
        Me._lblShowBitNum_2.AutoSize = False
        Me._lblShowBitNum_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_2.Name = "_lblShowBitNum_2"
        Me._lblShowBitNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_1.Text = "6"
        Me._lblShowBitNum_1.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_1.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_1.Location = New System.Drawing.Point(120, 120)
        Me._lblShowBitNum_1.TabIndex = 11
        Me._lblShowBitNum_1.Enabled = True
        Me._lblShowBitNum_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_1.UseMnemonic = True
        Me._lblShowBitNum_1.Visible = True
        Me._lblShowBitNum_1.AutoSize = False
        Me._lblShowBitNum_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_1.Name = "_lblShowBitNum_1"
        Me._lblShowBitNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowBitNum_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_0.Text = "7"
        Me._lblShowBitNum_0.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_0.Size = New System.Drawing.Size(17, 17)
        Me._lblShowBitNum_0.Location = New System.Drawing.Point(96, 120)
        Me._lblShowBitNum_0.TabIndex = 10
        Me._lblShowBitNum_0.Enabled = True
        Me._lblShowBitNum_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_0.UseMnemonic = True
        Me._lblShowBitNum_0.Visible = True
        Me._lblShowBitNum_0.AutoSize = False
        Me._lblShowBitNum_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_0.Name = "_lblShowBitNum_0"
        Me.lblBitNum.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblBitNum.BackColor = System.Drawing.SystemColors.Window
        Me.lblBitNum.Text = "Bit Number:"
        Me.lblBitNum.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblBitNum.Size = New System.Drawing.Size(73, 17)
        Me.lblBitNum.Location = New System.Drawing.Point(8, 120)
        Me.lblBitNum.TabIndex = 9
        Me.lblBitNum.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblBitNum.Enabled = True
        Me.lblBitNum.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblBitNum.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblBitNum.UseMnemonic = True
        Me.lblBitNum.Visible = True
        Me.lblBitNum.AutoSize = False
        Me.lblBitNum.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblBitNum.Name = "lblBitNum"
        Me.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.Text = "Input a TTL logic level at Port A inputs to change Bit Value:"
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Size = New System.Drawing.Size(209, 33)
        Me.lblInstruct.Location = New System.Drawing.Point(56, 72)
        Me.lblInstruct.TabIndex = 19
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.Enabled = True
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.UseMnemonic = True
        Me.lblInstruct.Visible = True
        Me.lblInstruct.AutoSize = False
        Me.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblInstruct.Name = "lblInstruct"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DBitIn() Reading AuxPort"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(241, 41)
        Me.lblDemoFunction.Location = New System.Drawing.Point(40, 16)
        Me.lblDemoFunction.TabIndex = 18
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.Enabled = True
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.UseMnemonic = True
        Me.lblDemoFunction.Visible = True
        Me.lblDemoFunction.AutoSize = False
        Me.lblDemoFunction.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.Controls.Add(cmdStopRead)
        Me.Controls.Add(_lblShowBitVal_0)
        Me.Controls.Add(_lblShowBitVal_1)
        Me.Controls.Add(_lblShowBitVal_2)
        Me.Controls.Add(_lblShowBitVal_3)
        Me.Controls.Add(_lblShowBitVal_4)
        Me.Controls.Add(_lblShowBitVal_5)
        Me.Controls.Add(_lblShowBitVal_6)
        Me.Controls.Add(_lblShowBitVal_7)
        Me.Controls.Add(lblBitVal)
        Me.Controls.Add(_lblShowBitNum_7)
        Me.Controls.Add(_lblShowBitNum_6)
        Me.Controls.Add(_lblShowBitNum_5)
        Me.Controls.Add(_lblShowBitNum_4)
        Me.Controls.Add(_lblShowBitNum_3)
        Me.Controls.Add(_lblShowBitNum_2)
        Me.Controls.Add(_lblShowBitNum_1)
        Me.Controls.Add(_lblShowBitNum_0)
        Me.Controls.Add(lblBitNum)
        Me.Controls.Add(lblInstruct)
        Me.Controls.Add(lblDemoFunction)
    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo
		  Dim PortType as MccDaq.DigitalPortType
		  Dim devNum as Integer
		  Dim inmask, outmask as Integer

        lblShowBitNum = New System.Windows.Forms.Label(8) {}
        Me.lblShowBitNum.SetValue(_lblShowBitNum_7, 7)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_6, 6)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_5, 5)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_4, 4)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_3, 3)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_2, 2)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_1, 1)
        Me.lblShowBitNum.SetValue(_lblShowBitNum_0, 0)


        lblShowBitVal = New System.Windows.Forms.Label(8) {}

        Me.lblShowBitVal.SetValue(_lblShowBitVal_0, 0)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_1, 1)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_2, 2)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_3, 3)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_4, 4)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_5, 5)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_6, 6)
        Me.lblShowBitVal.SetValue(_lblShowBitVal_7, 7)


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
            ' ERROR: This board does NOT have an AuxPort
            tmrReadInputs.Stop()
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
        If (0 = (inmask And outmask)) Then ULStat = DaqBoard.DConfigPort(PortType, MccDaq.DigitalPortDirection.DigitalIn)

    End Sub
#End Region

End Class