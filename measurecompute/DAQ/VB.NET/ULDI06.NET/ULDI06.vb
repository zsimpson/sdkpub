'==============================================================================
'
' File:                         ULDI06.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DConfigBit()

' Purpose:                      Reads the status of a single bit within a digital
'                               port.

' Demonstration:                configures a single bit (within a digital port)
'                               for input and reads the bit status

' Other Library Calls:          MccDaq.MccBoard.DBitIn()
'                               MccDaq.MccService.ErrHandling()
'                               MccDaq.MccBoard.DioConfig.GetDevType()
'                               MccDaq.MccBoard.DioConfig.GetDInMask()
'                               MccDaq.MccBoard.DioConfig.GetDOutMask()


' Special Requirements:         Board 0 must have a digital port that supports
'                               MccDaq.MccBoard.DConfigBit function.

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDigIn
    Inherits System.Windows.Forms.Form

    Const PortType As MccDaq.DigitalPortType = MccDaq.DigitalPortType.AuxPort ' set port type to programmable
    Const BitNum As Short = 0 ' test bit zero
    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalIn ' program port for input mode
    
    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Public lblShowBitNum As System.Windows.Forms.Label()

    Private Sub cmdStopRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopRead.Click

        End

    End Sub

    Private Sub tmrReadInputs_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadInputs.Tick
        Dim ULStat As MccDaq.ErrorInfo
        Dim BitValue As MccDaq.DigitalLogicState

        tmrReadInputs.Stop()
        
        ' read a single bit status from the digital port

        '  Parameters:
        '    PortType   :the digital I/O port type
        '    BitNum     :the bit to read
        '    BitValue   :the value read from the port

        ULStat = DaqBoard.DBitIn(PortType, BitNum, BitValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblBitNum.Text = "Bit number " & BitNum & " state is " & Convert.ToInt32(BitValue).ToString()
        
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
    Public WithEvents lblBitNum As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents _lblShowBitNum_0 As System.Windows.Forms.Label
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
        Me.lblBitNum = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me._lblShowBitNum_0 = New System.Windows.Forms.Label()
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
        Me.cmdStopRead.TabIndex = 1
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
        Me.lblBitNum.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblBitNum.BackColor = System.Drawing.SystemColors.Window
        Me.lblBitNum.Text = "Bit Number"
        Me.lblBitNum.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblBitNum.Size = New System.Drawing.Size(197, 17)
        Me.lblBitNum.Location = New System.Drawing.Point(65, 136)
        Me.lblBitNum.TabIndex = 4
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
        Me.lblInstruct.Text = "You may change the bit state by applying a TTL high or a TTL low to the corresponding pin on the port"
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Size = New System.Drawing.Size(209, 49)
        Me.lblInstruct.Location = New System.Drawing.Point(59, 56)
        Me.lblInstruct.TabIndex = 3
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.Enabled = True
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.UseMnemonic = True
        Me.lblInstruct.Visible = True
        Me.lblInstruct.AutoSize = False
        Me.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblInstruct.Name = "lblInstruct"
        Me._lblShowBitNum_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowBitNum_0.ForeColor = System.Drawing.SystemColors.WindowText
        Me._lblShowBitNum_0.Size = New System.Drawing.Size(9, 17)
        Me._lblShowBitNum_0.Location = New System.Drawing.Point(161, 138)
        Me._lblShowBitNum_0.TabIndex = 2
        Me._lblShowBitNum_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowBitNum_0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblShowBitNum_0.Enabled = True
        Me._lblShowBitNum_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowBitNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowBitNum_0.UseMnemonic = True
        Me._lblShowBitNum_0.Visible = True
        Me._lblShowBitNum_0.AutoSize = False
        Me._lblShowBitNum_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowBitNum_0.Name = "_lblShowBitNum_0"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DConfigBit()"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(209, 25)
        Me.lblDemoFunction.Location = New System.Drawing.Point(59, 16)
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
        Me.Controls.Add(cmdStopRead)
        Me.Controls.Add(lblBitNum)
        Me.Controls.Add(lblInstruct)
        Me.Controls.Add(_lblShowBitNum_0)
        Me.Controls.Add(lblDemoFunction)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo
        Dim devNum As Integer
        Dim inmask, outmask As Integer
        Dim PortType As MccDaq.DigitalPortType

        lblShowBitNum = New System.Windows.Forms.Label(8) {}
        Me.lblShowBitNum.SetValue(_lblShowBitNum_0, 0)


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
        If (0 = (inmask And outmask)) Then
            ' configure a single bit for input or output
            '  Parameters:
            '    PortType   :the port for which to configure the bit
            '    BitNum     :the bit to configure
            '    Direction  :sets the bit for input or output
            ULStat = DaqBoard.DConfigBit(PortType, BitNum, Direction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        End If

    End Sub
#End Region

End Class