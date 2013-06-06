'==============================================================================

' File:                         ULDI01.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DIn()

' Purpose:                      Reads a digital input port.

' Demonstration:                Configures FirstPortA for input and reads
'                               the value on the port.

' Other Library Calls:          MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a digital input port.
'                               Board 0 must have programmable digital ports.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDigIn
    Inherits System.Windows.Forms.Form

    Const PortNum As MccDaq.DigitalPortType = MccDaq.DigitalPortType.FirstPortA ' set port to use
    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalIn ' set direction of port to input

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Public lblBitNum As System.Windows.Forms.Label()
    Public lblBitVal As System.Windows.Forms.Label()

    Private Sub tmrReadInputs_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadInputs.Tick
        Dim I As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        tmrReadInputs.Stop()
        ' read FirstPortA digital input and display

        ' Parameters:
        '   PortNum    :the input port
        '   DataValue  :the value read from the port

        ULStat = DaqBoard.DIn(PortNum, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' display the value collected from the port

        lblPortRead.Text = DataValue.ToString("0")

        ' parse DataValue into bit values to indicate on/off status

        For I = 0 To 7
            If (Convert.ToInt32(DataValue) And CInt((2 ^ I))) <> 0 Then
                lblBitVal(I).Text = "1"
            Else
                lblBitVal(I).Text = "0"
            End If
        Next I
        
        tmrReadInputs.Start()

    End Sub

    Private Sub cmdStopRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopRead.Click

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
    Public WithEvents cmdStopRead As System.Windows.Forms.Button
    Public WithEvents tmrReadInputs As System.Windows.Forms.Timer
    Public WithEvents lblPortRead As System.Windows.Forms.Label
    Public WithEvents lblPortsRead As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_0 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_1 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_2 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_3 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_4 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_5 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_6 As System.Windows.Forms.Label
    Public WithEvents _lblBitVal_7 As System.Windows.Forms.Label
    Public WithEvents lblBitsRead As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_7 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_6 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_5 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_4 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_3 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_2 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_1 As System.Windows.Forms.Label
    Public WithEvents _lblBitNum_0 As System.Windows.Forms.Label
    Public WithEvents lblBitList As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadInputs = New System.Windows.Forms.Timer(Me.components)
        Me.lblPortRead = New System.Windows.Forms.Label()
        Me.lblPortsRead = New System.Windows.Forms.Label()
        Me._lblBitVal_0 = New System.Windows.Forms.Label()
        Me._lblBitVal_1 = New System.Windows.Forms.Label()
        Me._lblBitVal_2 = New System.Windows.Forms.Label()
        Me._lblBitVal_3 = New System.Windows.Forms.Label()
        Me._lblBitVal_4 = New System.Windows.Forms.Label()
        Me._lblBitVal_5 = New System.Windows.Forms.Label()
        Me._lblBitVal_6 = New System.Windows.Forms.Label()
        Me._lblBitVal_7 = New System.Windows.Forms.Label()
        Me.lblBitsRead = New System.Windows.Forms.Label()
        Me._lblBitNum_7 = New System.Windows.Forms.Label()
        Me._lblBitNum_6 = New System.Windows.Forms.Label()
        Me._lblBitNum_5 = New System.Windows.Forms.Label()
        Me._lblBitNum_4 = New System.Windows.Forms.Label()
        Me._lblBitNum_3 = New System.Windows.Forms.Label()
        Me._lblBitNum_2 = New System.Windows.Forms.Label()
        Me._lblBitNum_1 = New System.Windows.Forms.Label()
        Me._lblBitNum_0 = New System.Windows.Forms.Label()
        Me.lblBitList = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdStopRead
        '
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Location = New System.Drawing.Point(256, 192)
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.Size = New System.Drawing.Size(57, 33)
        Me.cmdStopRead.TabIndex = 14
        Me.cmdStopRead.Text = "Quit"
        '
        'tmrReadInputs
        '
        Me.tmrReadInputs.Enabled = True
        Me.tmrReadInputs.Interval = 500
        '
        'lblPortRead
        '
        Me.lblPortRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblPortRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPortRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPortRead.ForeColor = System.Drawing.Color.Blue
        Me.lblPortRead.Location = New System.Drawing.Point(136, 184)
        Me.lblPortRead.Name = "lblPortRead"
        Me.lblPortRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPortRead.Size = New System.Drawing.Size(33, 17)
        Me.lblPortRead.TabIndex = 13
        '
        'lblPortsRead
        '
        Me.lblPortsRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblPortsRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPortsRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPortsRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblPortsRead.Location = New System.Drawing.Point(24, 184)
        Me.lblPortsRead.Name = "lblPortsRead"
        Me.lblPortsRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPortsRead.Size = New System.Drawing.Size(98, 17)
        Me.lblPortsRead.TabIndex = 12
        Me.lblPortsRead.Text = "Port value read:"
        Me.lblPortsRead.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblBitVal_0
        '
        Me._lblBitVal_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_0.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_0.Location = New System.Drawing.Point(296, 136)
        Me._lblBitVal_0.Name = "_lblBitVal_0"
        Me._lblBitVal_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_0.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_0.TabIndex = 3
        Me._lblBitVal_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_1
        '
        Me._lblBitVal_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_1.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_1.Location = New System.Drawing.Point(272, 136)
        Me._lblBitVal_1.Name = "_lblBitVal_1"
        Me._lblBitVal_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_1.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_1.TabIndex = 4
        Me._lblBitVal_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_2
        '
        Me._lblBitVal_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_2.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_2.Location = New System.Drawing.Point(248, 136)
        Me._lblBitVal_2.Name = "_lblBitVal_2"
        Me._lblBitVal_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_2.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_2.TabIndex = 5
        Me._lblBitVal_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_3
        '
        Me._lblBitVal_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_3.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_3.Location = New System.Drawing.Point(224, 136)
        Me._lblBitVal_3.Name = "_lblBitVal_3"
        Me._lblBitVal_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_3.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_3.TabIndex = 6
        Me._lblBitVal_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_4
        '
        Me._lblBitVal_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_4.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_4.Location = New System.Drawing.Point(200, 136)
        Me._lblBitVal_4.Name = "_lblBitVal_4"
        Me._lblBitVal_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_4.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_4.TabIndex = 7
        Me._lblBitVal_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_5
        '
        Me._lblBitVal_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_5.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_5.Location = New System.Drawing.Point(176, 136)
        Me._lblBitVal_5.Name = "_lblBitVal_5"
        Me._lblBitVal_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_5.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_5.TabIndex = 8
        Me._lblBitVal_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_6
        '
        Me._lblBitVal_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_6.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_6.Location = New System.Drawing.Point(152, 136)
        Me._lblBitVal_6.Name = "_lblBitVal_6"
        Me._lblBitVal_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_6.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_6.TabIndex = 9
        Me._lblBitVal_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitVal_7
        '
        Me._lblBitVal_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitVal_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitVal_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitVal_7.ForeColor = System.Drawing.Color.Blue
        Me._lblBitVal_7.Location = New System.Drawing.Point(128, 136)
        Me._lblBitVal_7.Name = "_lblBitVal_7"
        Me._lblBitVal_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitVal_7.Size = New System.Drawing.Size(17, 17)
        Me._lblBitVal_7.TabIndex = 10
        Me._lblBitVal_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblBitsRead
        '
        Me.lblBitsRead.BackColor = System.Drawing.SystemColors.Window
        Me.lblBitsRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblBitsRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblBitsRead.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblBitsRead.Location = New System.Drawing.Point(24, 136)
        Me.lblBitsRead.Name = "lblBitsRead"
        Me.lblBitsRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblBitsRead.Size = New System.Drawing.Size(97, 17)
        Me.lblBitsRead.TabIndex = 11
        Me.lblBitsRead.Text = "Bit values read:"
        Me.lblBitsRead.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        '_lblBitNum_7
        '
        Me._lblBitNum_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_7.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_7.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_7.Location = New System.Drawing.Point(296, 112)
        Me._lblBitNum_7.Name = "_lblBitNum_7"
        Me._lblBitNum_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_7.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_7.TabIndex = 22
        Me._lblBitNum_7.Text = "0"
        Me._lblBitNum_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_6
        '
        Me._lblBitNum_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_6.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_6.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_6.Location = New System.Drawing.Point(272, 112)
        Me._lblBitNum_6.Name = "_lblBitNum_6"
        Me._lblBitNum_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_6.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_6.TabIndex = 21
        Me._lblBitNum_6.Text = "1"
        Me._lblBitNum_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_5
        '
        Me._lblBitNum_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_5.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_5.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_5.Location = New System.Drawing.Point(248, 112)
        Me._lblBitNum_5.Name = "_lblBitNum_5"
        Me._lblBitNum_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_5.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_5.TabIndex = 20
        Me._lblBitNum_5.Text = "2"
        Me._lblBitNum_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_4
        '
        Me._lblBitNum_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_4.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_4.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_4.Location = New System.Drawing.Point(224, 112)
        Me._lblBitNum_4.Name = "_lblBitNum_4"
        Me._lblBitNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_4.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_4.TabIndex = 19
        Me._lblBitNum_4.Text = "3"
        Me._lblBitNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_3
        '
        Me._lblBitNum_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_3.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_3.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_3.Location = New System.Drawing.Point(200, 112)
        Me._lblBitNum_3.Name = "_lblBitNum_3"
        Me._lblBitNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_3.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_3.TabIndex = 18
        Me._lblBitNum_3.Text = "4"
        Me._lblBitNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_2
        '
        Me._lblBitNum_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_2.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_2.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_2.Location = New System.Drawing.Point(176, 112)
        Me._lblBitNum_2.Name = "_lblBitNum_2"
        Me._lblBitNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_2.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_2.TabIndex = 17
        Me._lblBitNum_2.Text = "5"
        Me._lblBitNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_1
        '
        Me._lblBitNum_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_1.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_1.Location = New System.Drawing.Point(152, 112)
        Me._lblBitNum_1.Name = "_lblBitNum_1"
        Me._lblBitNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_1.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_1.TabIndex = 16
        Me._lblBitNum_1.Text = "6"
        Me._lblBitNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblBitNum_0
        '
        Me._lblBitNum_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblBitNum_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblBitNum_0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblBitNum_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblBitNum_0.Location = New System.Drawing.Point(128, 112)
        Me._lblBitNum_0.Name = "_lblBitNum_0"
        Me._lblBitNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblBitNum_0.Size = New System.Drawing.Size(17, 17)
        Me._lblBitNum_0.TabIndex = 15
        Me._lblBitNum_0.Text = "7"
        Me._lblBitNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblBitList
        '
        Me.lblBitList.BackColor = System.Drawing.SystemColors.Window
        Me.lblBitList.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblBitList.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblBitList.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblBitList.Location = New System.Drawing.Point(8, 112)
        Me.lblBitList.Name = "lblBitList"
        Me.lblBitList.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblBitList.Size = New System.Drawing.Size(113, 17)
        Me.lblBitList.TabIndex = 2
        Me.lblBitList.Text = "The first 7 bits are:"
        Me.lblBitList.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblInstruct
        '
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Location = New System.Drawing.Point(32, 56)
        Me.lblInstruct.Name = "lblInstruct"
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.Size = New System.Drawing.Size(265, 33)
        Me.lblInstruct.TabIndex = 1
        Me.lblInstruct.Text = "You may change a bit by applying a TTL high or TTL low to digital inputs on First" & _
        "PortA."
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(32, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(265, 25)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DIn()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDigIn
        '
        Me.AcceptButton = Me.cmdStopRead
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(339, 242)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdStopRead, Me.lblPortRead, Me.lblPortsRead, Me._lblBitVal_0, Me._lblBitVal_1, Me._lblBitVal_2, Me._lblBitVal_3, Me._lblBitVal_4, Me._lblBitVal_5, Me._lblBitVal_6, Me._lblBitVal_7, Me.lblBitsRead, Me._lblBitNum_7, Me._lblBitNum_6, Me._lblBitNum_5, Me._lblBitNum_4, Me._lblBitNum_3, Me._lblBitNum_2, Me._lblBitNum_1, Me._lblBitNum_0, Me.lblBitList, Me.lblInstruct, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDigIn"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Digital Input"
        Me.ResumeLayout(False)

    End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ULStat As MccDaq.ErrorInfo

        lblBitNum = New System.Windows.Forms.Label(8) {}
        Me.lblBitNum.SetValue(Me._lblBitNum_7, 7)
        Me.lblBitNum.SetValue(Me._lblBitNum_6, 6)
        Me.lblBitNum.SetValue(Me._lblBitNum_5, 5)
        Me.lblBitNum.SetValue(Me._lblBitNum_4, 4)
        Me.lblBitNum.SetValue(Me._lblBitNum_3, 3)
        Me.lblBitNum.SetValue(Me._lblBitNum_2, 2)
        Me.lblBitNum.SetValue(Me._lblBitNum_1, 1)
        Me.lblBitNum.SetValue(Me._lblBitNum_0, 0)


        lblBitVal = New System.Windows.Forms.Label(8) {}
        Me.lblBitVal.SetValue(Me._lblBitVal_0, 0)
        Me.lblBitVal.SetValue(Me._lblBitVal_1, 1)
        Me.lblBitVal.SetValue(Me._lblBitVal_2, 2)
        Me.lblBitVal.SetValue(Me._lblBitVal_3, 3)
        Me.lblBitVal.SetValue(Me._lblBitVal_4, 4)
        Me.lblBitVal.SetValue(Me._lblBitVal_5, 5)
        Me.lblBitVal.SetValue(Me._lblBitVal_6, 6)
        Me.lblBitVal.SetValue(Me._lblBitVal_7, 7)


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

        ' configure FirstPortA for digital input
        '  Parameters:
        '    PortNum    :the input port
        '    Direction :sets the port for input or output


        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    End Sub
#End Region

End Class