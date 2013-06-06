'==============================================================================

' File:                         ULDO01.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DOut()

' Purpose:                      Writes a byte to digital output ports.

' Demonstration:                Configures FirstPortA for output and writes
'                               a value to the port.

' Other Library Calls:          MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a digital output port.
'                               Board 0 must have programmable digital ports.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmSetDigOut
    Inherits System.Windows.Forms.Form

    Const PortNum As MccDaq.DigitalPortType = MccDaq.DigitalPortType.FirstPortA ' set port to use
    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalOut ' program digital port A for output

    'Create a new MccBoard object for Board 0 
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Private Sub cmdEndProgram_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdEndProgram.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        DataValue = Convert.ToUInt16(0)

        ULStat = DaqBoard.DOut(PortNum, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        End

    End Sub

    Private Sub hsbSetDOutVal_Change(ByVal newScrollValue As Integer)
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        ' get a value to write to the port

        DataValue = Convert.ToUInt16(newScrollValue)
        txtValSet.Text = DataValue.ToString("0")

        ' write the value to FirstPortA
        '  Parameters:
        '    PortNum    :the output port
        '    DataValue  :the value written to the port

        ULStat = DaqBoard.DOut(PortNum, DataValue)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        Else
            lblDataValOut.Text = "Value written to FirstPortA:"
            lblShowValOut.Text = DataValue.ToString("0")
        End If

    End Sub

    Private Sub txtValSet_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtValSet.TextChanged

        If Val(txtValSet.Text) > 255 Then txtValSet.Text = "255"
        hsbSetDOutVal.Value = Integer.Parse(txtValSet.Text)

    End Sub
    Private Sub hsbSetDOutVal_Scroll(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.ScrollEventArgs) Handles hsbSetDOutVal.Scroll
        Select Case eventArgs.Type
            Case System.Windows.Forms.ScrollEventType.EndScroll
                hsbSetDOutVal_Change(eventArgs.NewValue)
        End Select
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
    Public WithEvents txtValSet As System.Windows.Forms.TextBox
    Public WithEvents hsbSetDOutVal As System.Windows.Forms.HScrollBar
    Public WithEvents lblShowValOut As System.Windows.Forms.Label
    Public WithEvents lblDataValOut As System.Windows.Forms.Label
    Public WithEvents lblValSet As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmSetDigOut))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me.txtValSet = New System.Windows.Forms.TextBox()
        Me.hsbSetDOutVal = New System.Windows.Forms.HScrollBar()
        Me.lblShowValOut = New System.Windows.Forms.Label()
        Me.lblDataValOut = New System.Windows.Forms.Label()
        Me.lblValSet = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library Digital Output"
        Me.ClientSize = New System.Drawing.Size(331, 267)
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
        Me.Name = "frmSetDigOut"
        Me.cmdEndProgram.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdEndProgram.Text = "Quit"
        Me.cmdEndProgram.Size = New System.Drawing.Size(57, 33)
        Me.cmdEndProgram.Location = New System.Drawing.Point(248, 216)
        Me.cmdEndProgram.TabIndex = 7
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.CausesValidation = True
        Me.cmdEndProgram.Enabled = True
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.TabStop = True
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me.txtValSet.AutoSize = False
        Me.txtValSet.Size = New System.Drawing.Size(41, 25)
        Me.txtValSet.Location = New System.Drawing.Point(264, 120)
        Me.txtValSet.TabIndex = 4
        Me.txtValSet.Text = "0"
        Me.txtValSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtValSet.AcceptsReturn = True
        Me.txtValSet.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtValSet.BackColor = System.Drawing.SystemColors.Window
        Me.txtValSet.CausesValidation = True
        Me.txtValSet.Enabled = True
        Me.txtValSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtValSet.HideSelection = True
        Me.txtValSet.ReadOnly = False
        Me.txtValSet.MaxLength = 0
        Me.txtValSet.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtValSet.Multiline = False
        Me.txtValSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtValSet.ScrollBars = System.Windows.Forms.ScrollBars.None
        Me.txtValSet.TabStop = True
        Me.txtValSet.Visible = True
        Me.txtValSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtValSet.Name = "txtValSet"
        Me.hsbSetDOutVal.Size = New System.Drawing.Size(225, 17)
        Me.hsbSetDOutVal.LargeChange = 51
        Me.hsbSetDOutVal.Location = New System.Drawing.Point(24, 120)
        Me.hsbSetDOutVal.Maximum = 305
        Me.hsbSetDOutVal.TabIndex = 1
        Me.hsbSetDOutVal.CausesValidation = True
        Me.hsbSetDOutVal.Enabled = True
        Me.hsbSetDOutVal.Minimum = 0
        Me.hsbSetDOutVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.hsbSetDOutVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.hsbSetDOutVal.SmallChange = 1
        Me.hsbSetDOutVal.TabStop = True
        Me.hsbSetDOutVal.Value = 0
        Me.hsbSetDOutVal.Visible = True
        Me.hsbSetDOutVal.Name = "hsbSetDOutVal"
        Me.lblShowValOut.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowValOut.ForeColor = System.Drawing.Color.Blue
        Me.lblShowValOut.Size = New System.Drawing.Size(57, 17)
        Me.lblShowValOut.Location = New System.Drawing.Point(224, 176)
        Me.lblShowValOut.TabIndex = 3
        Me.lblShowValOut.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowValOut.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblShowValOut.Enabled = True
        Me.lblShowValOut.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowValOut.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowValOut.UseMnemonic = True
        Me.lblShowValOut.Visible = True
        Me.lblShowValOut.AutoSize = False
        Me.lblShowValOut.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblShowValOut.Name = "lblShowValOut"
        Me.lblDataValOut.BackColor = System.Drawing.SystemColors.Window
        Me.lblDataValOut.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDataValOut.Size = New System.Drawing.Size(185, 17)
        Me.lblDataValOut.Location = New System.Drawing.Point(32, 176)
        Me.lblDataValOut.TabIndex = 2
        Me.lblDataValOut.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDataValOut.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblDataValOut.Enabled = True
        Me.lblDataValOut.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDataValOut.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDataValOut.UseMnemonic = True
        Me.lblDataValOut.Visible = True
        Me.lblDataValOut.AutoSize = False
        Me.lblDataValOut.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblDataValOut.Name = "lblDataValOut"
        Me.lblValSet.BackColor = System.Drawing.SystemColors.Window
        Me.lblValSet.Text = "Value set:"
        Me.lblValSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValSet.Size = New System.Drawing.Size(65, 17)
        Me.lblValSet.Location = New System.Drawing.Point(256, 96)
        Me.lblValSet.TabIndex = 6
        Me.lblValSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValSet.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblValSet.Enabled = True
        Me.lblValSet.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValSet.UseMnemonic = True
        Me.lblValSet.Visible = True
        Me.lblValSet.AutoSize = False
        Me.lblValSet.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblValSet.Name = "lblValSet"
        Me.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.Text = "Set output value using scroll bar or enter value in Value Set box:"
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Size = New System.Drawing.Size(201, 25)
        Me.lblInstruct.Location = New System.Drawing.Point(56, 48)
        Me.lblInstruct.TabIndex = 5
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
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DOut()"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(289, 25)
        Me.lblDemoFunction.Location = New System.Drawing.Point(24, 8)
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
        Me.Controls.Add(txtValSet)
        Me.Controls.Add(hsbSetDOutVal)
        Me.Controls.Add(lblShowValOut)
        Me.Controls.Add(lblDataValOut)
        Me.Controls.Add(lblValSet)
        Me.Controls.Add(lblInstruct)
        Me.Controls.Add(lblDemoFunction)
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


        ' configure FirstPortA for digital output
        '  Parameters:
        '    PortNum    :the output port
        '    Direction  :sets the port for input or output

        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    End Sub
#End Region

End Class