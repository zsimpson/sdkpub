'==============================================================================

' File:                         ULAO02.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.AOutScan()

' Purpose:                      Writes to a range of D/A Output Channels.

' Demonstration:                Sends a digital output to the D/A channels

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have 2 or more D/A converters.
'                               This function is designed for boards that
'                               support timed analog output.  It can be used
'                               for polled output boards but only for values
'                               of NumPoints up to the number of channels
'                               that the board supports (i.e., NumPoints =
'                               6 maximum for the six channel CIO-DDA06).

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmSendAData
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 2
    Const Count As Integer = NumPoints

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim DAData(NumPoints) As UInt16
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
    Dim FirstPoint As Integer

    Public lblAOutData As System.Windows.Forms.Label()


    Private Sub cmdSendData_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdSendData.Click
        Dim i As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim Options As MccDaq.ScanOptions
        Dim Gain As MccDaq.Range
        Dim Rate As Integer
        Dim HighChan As Integer
        Dim LowChan As Integer

        ' Parameters:
        '   LowChan    :the lower channel of the scan
        '   HighChan   :the upper channel of the scan
        '   Count      :the number of D/A values to send
        '   Rate       :send rate in values/second (if supported by BoardNum)
        '   MemHandle  :Handle for Windows buffer from which data will be output
        '   Options    :data send options

        FirstPoint = 0
        LowChan = 0 'First analog output channel
        HighChan = 1 'Last analog output channel
        Rate = 100 'Rate of data update (ignored if board does not
        Gain = MccDaq.Range.Bip5Volts 'Ignored if gain is not programmable
        Options = MccDaq.ScanOptions.Default 'support timed analog output)

        ULStat = DaqBoard.AOutScan(LowChan, HighChan, Count, Rate, Gain, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        For i = 0 To NumPoints - 1
            lblAOutData(i).Text = DAData(i).ToString("0")
        Next i

    End Sub

    Private Sub cmdEndProgram_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdEndProgram.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by
        ' other programs
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
    Public WithEvents cmdSendData As System.Windows.Forms.Button
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents _lblAOutData_1 As System.Windows.Forms.Label
    Public WithEvents _lblAOutData_0 As System.Windows.Forms.Label
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents lblChan0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me.cmdSendData = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me._lblAOutData_1 = New System.Windows.Forms.Label()
        Me._lblAOutData_0 = New System.Windows.Forms.Label()
        Me.lblChan1 = New System.Windows.Forms.Label()
        Me.lblChan0 = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdEndProgram
        '
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Location = New System.Drawing.Point(264, 168)
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.Size = New System.Drawing.Size(55, 26)
        Me.cmdEndProgram.TabIndex = 1
        Me.cmdEndProgram.Text = "Quit"
        '
        'cmdSendData
        '
        Me.cmdSendData.BackColor = System.Drawing.SystemColors.Control
        Me.cmdSendData.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdSendData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdSendData.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdSendData.Location = New System.Drawing.Point(128, 48)
        Me.cmdSendData.Name = "cmdSendData"
        Me.cmdSendData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdSendData.Size = New System.Drawing.Size(81, 33)
        Me.cmdSendData.TabIndex = 2
        Me.cmdSendData.Text = "Send Data"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Window
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(40, 120)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(57, 25)
        Me.Label1.TabIndex = 7
        Me.Label1.Text = "Raw Data"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        '_lblAOutData_1
        '
        Me._lblAOutData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblAOutData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblAOutData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblAOutData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblAOutData_1.Location = New System.Drawing.Point(176, 128)
        Me._lblAOutData_1.Name = "_lblAOutData_1"
        Me._lblAOutData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblAOutData_1.Size = New System.Drawing.Size(65, 17)
        Me._lblAOutData_1.TabIndex = 6
        Me._lblAOutData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        '_lblAOutData_0
        '
        Me._lblAOutData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblAOutData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblAOutData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblAOutData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblAOutData_0.Location = New System.Drawing.Point(96, 128)
        Me._lblAOutData_0.Name = "_lblAOutData_0"
        Me._lblAOutData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblAOutData_0.Size = New System.Drawing.Size(65, 17)
        Me._lblAOutData_0.TabIndex = 3
        Me._lblAOutData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan1
        '
        Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan1.Location = New System.Drawing.Point(176, 104)
        Me.lblChan1.Name = "lblChan1"
        Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan1.Size = New System.Drawing.Size(65, 17)
        Me.lblChan1.TabIndex = 5
        Me.lblChan1.Text = "Channel 1"
        Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblChan0
        '
        Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
        Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblChan0.Location = New System.Drawing.Point(96, 104)
        Me.lblChan0.Name = "lblChan0"
        Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblChan0.Size = New System.Drawing.Size(65, 17)
        Me.lblChan0.TabIndex = 4
        Me.lblChan0.Text = "Channel 0"
        Me.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(24, 16)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(281, 25)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AOutScan()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmSendAData
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(337, 212)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdEndProgram, Me.cmdSendData, Me.Label1, Me._lblAOutData_1, Me._lblAOutData_0, Me.lblChan1, Me.lblChan0, Me.lblDemoFunction})
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmSendAData"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Analog Output "
        Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim i As Short
        Dim ULStat As MccDaq.ErrorInfo

        Me.lblAOutData = New System.Windows.Forms.Label(2) {}
        Me.lblAOutData.SetValue(Me._lblAOutData_1, 1)
        Me.lblAOutData.SetValue(Me._lblAOutData_0, 0)

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

        MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

        For i = 0 To NumPoints - 1
            DAData(i) = Convert.ToUInt16(i * 1365)
        Next i

        FirstPoint = 0

        ULStat = MccDaq.MccService.WinArrayToBuf(DAData(0), MemHandle, FirstPoint, Count)


    End Sub
#End Region

End Class