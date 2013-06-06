'==============================================================================

' File:                         ULDO04.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DOut()

' Purpose:                      Writes a byte to AuxPort.

' Demonstration:                Writes a selected value to AuxPort.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccBoard.DioConfig.GetDevType()
'                               MccDaq.MccBoard.DioConfig.GetDInMask()
'                               MccDaq.MccBoard.DioConfig.GetDOutMask()

' Special Requirements:         Board 0 must have a digital port.

'
'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmDigAuxOut
    Inherits System.Windows.Forms.Form

    Const PortNum As MccDaq.DigitalPortType = MccDaq.DigitalPortType.AuxPort ' set port type to auxilliary

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

    Private Sub hsbSetPortVal_Change(ByVal newScrollValue As Integer)
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        ' write the value to AuxPort
        '  Parameters:
        '    PortNum    :the output port
        '    DataValue  :the value written to the port

        DataValue = Convert.ToUInt16(newScrollValue)
        txtShowSetVal.Text = DataValue.ToString("0")

        ULStat = DaqBoard.DOut(PortNum, DataValue)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        lblWriteVal.Text = "The value written to AuxPort was:"
        lblShowWriteVal.Text = DataValue.ToString("0")

    End Sub


    Private Sub opt4Bit_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles opt4Bit.CheckedChanged
        If opt4Bit.Checked Then
            Dim NewLargeChange As Short

            hsbSetPortVal.Maximum = (15 + hsbSetPortVal.LargeChange - 1)
            NewLargeChange = 3
            hsbSetPortVal.Maximum = hsbSetPortVal.Maximum + NewLargeChange - hsbSetPortVal.LargeChange
            hsbSetPortVal.LargeChange = NewLargeChange

        End If
    End Sub

    Private Sub opt8Bit_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles opt8Bit.CheckedChanged
        If opt8Bit.Checked Then
            Dim NewLargeChange As Short

            hsbSetPortVal.Maximum = (255 + hsbSetPortVal.LargeChange - 1)
            NewLargeChange = 51
            hsbSetPortVal.Maximum = hsbSetPortVal.Maximum + NewLargeChange - hsbSetPortVal.LargeChange
            hsbSetPortVal.LargeChange = NewLargeChange

        End If
    End Sub

    Private Sub txtShowSetVal_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtShowSetVal.TextChanged

        If Val(txtShowSetVal.Text) > (hsbSetPortVal.Maximum - hsbSetPortVal.LargeChange + 1) Then
            txtShowSetVal.Text = (hsbSetPortVal.Maximum - hsbSetPortVal.LargeChange + 1).ToString("0")
        End If
        hsbSetPortVal.Value = Integer.Parse(txtShowSetVal.Text)

    End Sub
    Private Sub hsbSetPortVal_Scroll(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.ScrollEventArgs) Handles hsbSetPortVal.Scroll
        Select Case eventArgs.Type
            Case System.Windows.Forms.ScrollEventType.EndScroll
                hsbSetPortVal_Change(eventArgs.NewValue)
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
    Public WithEvents hsbSetPortVal As System.Windows.Forms.HScrollBar
    Public WithEvents txtShowSetVal As System.Windows.Forms.TextBox
    Public WithEvents opt8Bit As System.Windows.Forms.RadioButton
    Public WithEvents opt4Bit As System.Windows.Forms.RadioButton
    Public WithEvents lblShowWriteVal As System.Windows.Forms.Label
    Public WithEvents lblWriteVal As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me.hsbSetPortVal = New System.Windows.Forms.HScrollBar()
        Me.txtShowSetVal = New System.Windows.Forms.TextBox()
        Me.opt8Bit = New System.Windows.Forms.RadioButton()
        Me.opt4Bit = New System.Windows.Forms.RadioButton()
        Me.lblShowWriteVal = New System.Windows.Forms.Label()
        Me.lblWriteVal = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdEndProgram
        '
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Location = New System.Drawing.Point(232, 224)
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.Size = New System.Drawing.Size(65, 33)
        Me.cmdEndProgram.TabIndex = 6
        Me.cmdEndProgram.Text = "Quit"
        '
        'hsbSetPortVal
        '
        Me.hsbSetPortVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.hsbSetPortVal.LargeChange = 3
        Me.hsbSetPortVal.Location = New System.Drawing.Point(24, 144)
        Me.hsbSetPortVal.Maximum = 17
        Me.hsbSetPortVal.Name = "hsbSetPortVal"
        Me.hsbSetPortVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.hsbSetPortVal.Size = New System.Drawing.Size(209, 17)
        Me.hsbSetPortVal.TabIndex = 1
        Me.hsbSetPortVal.TabStop = True
        '
        'txtShowSetVal
        '
        Me.txtShowSetVal.AcceptsReturn = True
        Me.txtShowSetVal.AutoSize = False
        Me.txtShowSetVal.BackColor = System.Drawing.SystemColors.Window
        Me.txtShowSetVal.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtShowSetVal.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtShowSetVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtShowSetVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtShowSetVal.Location = New System.Drawing.Point(248, 136)
        Me.txtShowSetVal.MaxLength = 0
        Me.txtShowSetVal.Name = "txtShowSetVal"
        Me.txtShowSetVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtShowSetVal.Size = New System.Drawing.Size(49, 25)
        Me.txtShowSetVal.TabIndex = 7
        Me.txtShowSetVal.Text = ""
        '
        'opt8Bit
        '
        Me.opt8Bit.BackColor = System.Drawing.SystemColors.Window
        Me.opt8Bit.Cursor = System.Windows.Forms.Cursors.Default
        Me.opt8Bit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.opt8Bit.ForeColor = System.Drawing.SystemColors.WindowText
        Me.opt8Bit.Location = New System.Drawing.Point(224, 88)
        Me.opt8Bit.Name = "opt8Bit"
        Me.opt8Bit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.opt8Bit.Size = New System.Drawing.Size(73, 17)
        Me.opt8Bit.TabIndex = 3
        Me.opt8Bit.TabStop = True
        Me.opt8Bit.Text = "8 Bit Port"
        '
        'opt4Bit
        '
        Me.opt4Bit.BackColor = System.Drawing.SystemColors.Window
        Me.opt4Bit.Checked = True
        Me.opt4Bit.Cursor = System.Windows.Forms.Cursors.Default
        Me.opt4Bit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.opt4Bit.ForeColor = System.Drawing.SystemColors.WindowText
        Me.opt4Bit.Location = New System.Drawing.Point(224, 72)
        Me.opt4Bit.Name = "opt4Bit"
        Me.opt4Bit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.opt4Bit.Size = New System.Drawing.Size(73, 17)
        Me.opt4Bit.TabIndex = 2
        Me.opt4Bit.TabStop = True
        Me.opt4Bit.Text = "4 Bit Port"
        '
        'lblShowWriteVal
        '
        Me.lblShowWriteVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowWriteVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowWriteVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowWriteVal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowWriteVal.Location = New System.Drawing.Point(248, 184)
        Me.lblShowWriteVal.Name = "lblShowWriteVal"
        Me.lblShowWriteVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowWriteVal.Size = New System.Drawing.Size(41, 17)
        Me.lblShowWriteVal.TabIndex = 5
        '
        'lblWriteVal
        '
        Me.lblWriteVal.BackColor = System.Drawing.SystemColors.Window
        Me.lblWriteVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblWriteVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblWriteVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblWriteVal.Location = New System.Drawing.Point(24, 184)
        Me.lblWriteVal.Name = "lblWriteVal"
        Me.lblWriteVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblWriteVal.Size = New System.Drawing.Size(209, 17)
        Me.lblWriteVal.TabIndex = 4
        '
        'lblInstruct
        '
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Location = New System.Drawing.Point(24, 72)
        Me.lblInstruct.Name = "lblInstruct"
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.Size = New System.Drawing.Size(169, 49)
        Me.lblInstruct.TabIndex = 8
        Me.lblInstruct.Text = "Select 4 or 8 bit port and use the scoll bar or the text box to set output data v" & _
        "alue."
        Me.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter
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
        Me.lblDemoFunction.Size = New System.Drawing.Size(225, 41)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DOut() and AuxPort"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmDigAuxOut
        '
        Me.AcceptButton = Me.cmdEndProgram
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(331, 281)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdEndProgram, Me.hsbSetPortVal, Me.txtShowSetVal, Me.opt8Bit, Me.opt4Bit, Me.lblShowWriteVal, Me.lblWriteVal, Me.lblInstruct, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmDigAuxOut"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Digital Out (AUXPORT)"
        Me.ResumeLayout(False)

    End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo
        Dim devNum As Integer
        Dim inmask, outmask As Integer
        Dim PortType As MccDaq.DigitalPortType

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