'==============================================================================
' File:                         ULMM02.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.MemRead() and 
'                               Mccdaq.MccBoard.MemWrite()

' Purpose:                      Write data to a memory board and then read
'                               it back again

' Demonstrates:                 How to read and write to memory in blocks

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 5 must be a memory board

'==============================================================================
Option Strict Off
Option Explicit On 
Friend Class frmShowFileData
    Inherits System.Windows.Forms.Form


    Const MemBoardNum As Short = 5 ' Board number for memory board
    Const NUMPOINTS As Short = 100 ' Number of points per block
    Const NUMBLOCKS As Short = 4 ' Number of blocks to read/write

    
    'Create a new MccBoard object for Board 5
    Private MemBoard As MccDaq.MccBoard = New MccDaq.MccBoard(MemBoardNum)

    
    Dim DataBuffer1(NUMPOINTS) As UInt16 ' dimension Visual Basics data array to hold
    Dim DataBuffer2(NUMPOINTS) As UInt16 ' data read from memory board

    Public lblShowData As System.Windows.Forms.Label()

    Private Sub cmdReadData_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdReadData.Click
        Dim DataPoint As Short
        Dim i As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim Count As Integer
        Dim BlockNum As Integer
        Dim FirstPoint As Short

        lblInstruct2.Text = ""
        lblInstruct1.Text = "The data read from the memory board is shown above."

        FirstPoint = 0 ' Set address of first point to read

        For BlockNum = 0 To NUMBLOCKS - 1 ' For each block

            ' Read a block of data from  the memory board
            ' DataBuffer2 - Array of data to read data into
            ' FirstPoint - Address to read first point (or FROMHERE)
            ' Count - Number of points to read

            Count = NUMPOINTS

            ULStat = MemBoard.MemRead(DataBuffer2(0), FirstPoint, Count)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            FirstPoint = MccDaq.MccBoard.FromHere

            For i = 0 To 4
                DataPoint = CShort(BlockNum * 5 + i)
                lblShowData(DataPoint).Text = DataBuffer2(i).ToString("0")
            Next i

        Next BlockNum

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        End

    End Sub

    Private Sub cmdWriteData_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdWriteData.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim FirstPoint As Integer
        Dim Count As Integer
        Dim DataPoint As Short
        Dim i As Short
        Dim BlockNum As Integer

        lblInstruct2.Text = ""
        lblInstruct1.Text = "A sample of the array written to the memory board is shown above. Press Read Data to verify."

        ' Create an array of data with known values to write to the memory board

        For BlockNum = 0 To NUMBLOCKS - 1
            For i = 0 To NUMPOINTS
                DataBuffer1(i) = Convert.ToUInt16(BlockNum * NUMPOINTS + i)
            Next i

            For i = 0 To 4
                DataPoint = CShort(5 * BlockNum + i)
                lblShowData(DataPoint).Text = DataBuffer1(i).ToString("0")
            Next i

            ' Write the block to the memory board
            ' DataBuffer1 - Array of data to be written
            ' FirstPoint - Address to write first point (or NEXTONE)
            ' Count - Number of points to write

            Count = NUMPOINTS

            ULStat = MemBoard.MemWrite(DataBuffer1(0), FirstPoint, Count)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            FirstPoint = MccDaq.MccBoard.FromHere
        Next BlockNum

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
    Public WithEvents cmdReadData As System.Windows.Forms.Button
    Public WithEvents cmdWriteData As System.Windows.Forms.Button
    Public WithEvents lblInstruct2 As System.Windows.Forms.Label
    Public WithEvents lblInstruct1 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_19 As System.Windows.Forms.Label
    Public WithEvents lblData19 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_9 As System.Windows.Forms.Label
    Public WithEvents lblData9 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_18 As System.Windows.Forms.Label
    Public WithEvents lblData18 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_8 As System.Windows.Forms.Label
    Public WithEvents lblData8 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_17 As System.Windows.Forms.Label
    Public WithEvents lblData17 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_7 As System.Windows.Forms.Label
    Public WithEvents lblData7 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_16 As System.Windows.Forms.Label
    Public WithEvents lblData16 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_6 As System.Windows.Forms.Label
    Public WithEvents lblData6 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_15 As System.Windows.Forms.Label
    Public WithEvents lblData15 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_5 As System.Windows.Forms.Label
    Public WithEvents lblData5 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_14 As System.Windows.Forms.Label
    Public WithEvents lblData14 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_4 As System.Windows.Forms.Label
    Public WithEvents lblData4 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_13 As System.Windows.Forms.Label
    Public WithEvents lblData13 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_3 As System.Windows.Forms.Label
    Public WithEvents lblData3 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_12 As System.Windows.Forms.Label
    Public WithEvents lblData12 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_2 As System.Windows.Forms.Label
    Public WithEvents lblData2 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_11 As System.Windows.Forms.Label
    Public WithEvents lblData11 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_1 As System.Windows.Forms.Label
    Public WithEvents lblData1 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_10 As System.Windows.Forms.Label
    Public WithEvents lblData10 As System.Windows.Forms.Label
    Public WithEvents _lblShowData_0 As System.Windows.Forms.Label
    Public WithEvents lblData0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmShowFileData))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdStopConvert = New System.Windows.Forms.Button()
        Me.cmdReadData = New System.Windows.Forms.Button()
        Me.cmdWriteData = New System.Windows.Forms.Button()
        Me.lblInstruct2 = New System.Windows.Forms.Label()
        Me.lblInstruct1 = New System.Windows.Forms.Label()
        Me._lblShowData_19 = New System.Windows.Forms.Label()
        Me.lblData19 = New System.Windows.Forms.Label()
        Me._lblShowData_9 = New System.Windows.Forms.Label()
        Me.lblData9 = New System.Windows.Forms.Label()
        Me._lblShowData_18 = New System.Windows.Forms.Label()
        Me.lblData18 = New System.Windows.Forms.Label()
        Me._lblShowData_8 = New System.Windows.Forms.Label()
        Me.lblData8 = New System.Windows.Forms.Label()
        Me._lblShowData_17 = New System.Windows.Forms.Label()
        Me.lblData17 = New System.Windows.Forms.Label()
        Me._lblShowData_7 = New System.Windows.Forms.Label()
        Me.lblData7 = New System.Windows.Forms.Label()
        Me._lblShowData_16 = New System.Windows.Forms.Label()
        Me.lblData16 = New System.Windows.Forms.Label()
        Me._lblShowData_6 = New System.Windows.Forms.Label()
        Me.lblData6 = New System.Windows.Forms.Label()
        Me._lblShowData_15 = New System.Windows.Forms.Label()
        Me.lblData15 = New System.Windows.Forms.Label()
        Me._lblShowData_5 = New System.Windows.Forms.Label()
        Me.lblData5 = New System.Windows.Forms.Label()
        Me._lblShowData_14 = New System.Windows.Forms.Label()
        Me.lblData14 = New System.Windows.Forms.Label()
        Me._lblShowData_4 = New System.Windows.Forms.Label()
        Me.lblData4 = New System.Windows.Forms.Label()
        Me._lblShowData_13 = New System.Windows.Forms.Label()
        Me.lblData13 = New System.Windows.Forms.Label()
        Me._lblShowData_3 = New System.Windows.Forms.Label()
        Me.lblData3 = New System.Windows.Forms.Label()
        Me._lblShowData_12 = New System.Windows.Forms.Label()
        Me.lblData12 = New System.Windows.Forms.Label()
        Me._lblShowData_2 = New System.Windows.Forms.Label()
        Me.lblData2 = New System.Windows.Forms.Label()
        Me._lblShowData_11 = New System.Windows.Forms.Label()
        Me.lblData11 = New System.Windows.Forms.Label()
        Me._lblShowData_1 = New System.Windows.Forms.Label()
        Me.lblData1 = New System.Windows.Forms.Label()
        Me._lblShowData_10 = New System.Windows.Forms.Label()
        Me.lblData10 = New System.Windows.Forms.Label()
        Me._lblShowData_0 = New System.Windows.Forms.Label()
        Me.lblData0 = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library Analog Input Scan"
        Me.ClientSize = New System.Drawing.Size(371, 361)
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Blue
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
        Me.Name = "frmShowFileData"
        Me.cmdStopConvert.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStopConvert.Text = "Quit"
        Me.cmdStopConvert.Size = New System.Drawing.Size(49, 25)
        Me.cmdStopConvert.Location = New System.Drawing.Point(301, 314)
        Me.cmdStopConvert.TabIndex = 17
        Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopConvert.CausesValidation = True
        Me.cmdStopConvert.Enabled = True
        Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopConvert.TabStop = True
        Me.cmdStopConvert.Name = "cmdStopConvert"
        Me.cmdReadData.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdReadData.Text = "Read Data"
        Me.cmdReadData.Size = New System.Drawing.Size(97, 25)
        Me.cmdReadData.Location = New System.Drawing.Point(205, 52)
        Me.cmdReadData.TabIndex = 19
        Me.cmdReadData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdReadData.BackColor = System.Drawing.SystemColors.Control
        Me.cmdReadData.CausesValidation = True
        Me.cmdReadData.Enabled = True
        Me.cmdReadData.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdReadData.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdReadData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdReadData.TabStop = True
        Me.cmdReadData.Name = "cmdReadData"
        Me.cmdWriteData.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdWriteData.Text = "Write Data"
        Me.cmdWriteData.Size = New System.Drawing.Size(97, 25)
        Me.cmdWriteData.Location = New System.Drawing.Point(58, 52)
        Me.cmdWriteData.TabIndex = 18
        Me.cmdWriteData.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdWriteData.BackColor = System.Drawing.SystemColors.Control
        Me.cmdWriteData.CausesValidation = True
        Me.cmdWriteData.Enabled = True
        Me.cmdWriteData.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdWriteData.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdWriteData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdWriteData.TabStop = True
        Me.cmdWriteData.Name = "cmdWriteData"
        Me.lblInstruct2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblInstruct2.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct2.Text = "So for example the value 203 is stored at address 203 in memory. Clicking Read Data reads the data back and displays it."
        Me.lblInstruct2.ForeColor = System.Drawing.Color.Blue
        Me.lblInstruct2.Size = New System.Drawing.Size(273, 41)
        Me.lblInstruct2.Location = New System.Drawing.Point(16, 312)
        Me.lblInstruct2.TabIndex = 44
        Me.lblInstruct2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct2.Enabled = True
        Me.lblInstruct2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct2.UseMnemonic = True
        Me.lblInstruct2.Visible = True
        Me.lblInstruct2.AutoSize = False
        Me.lblInstruct2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblInstruct2.Name = "lblInstruct2"
        Me.lblInstruct1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblInstruct1.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct1.Text = "This program writes 500 values to the memory board by writing 5 blocks of 100 values to consecutive locations in the memory board. The values that are written correspond to the memory board address in which they are stored."
        Me.lblInstruct1.ForeColor = System.Drawing.Color.Blue
        Me.lblInstruct1.Size = New System.Drawing.Size(337, 57)
        Me.lblInstruct1.Location = New System.Drawing.Point(16, 256)
        Me.lblInstruct1.TabIndex = 45
        Me.lblInstruct1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct1.Enabled = True
        Me.lblInstruct1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct1.UseMnemonic = True
        Me.lblInstruct1.Visible = True
        Me.lblInstruct1.AutoSize = False
        Me.lblInstruct1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblInstruct1.Name = "lblInstruct1"
        Me._lblShowData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_19.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_19.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_19.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_19.Location = New System.Drawing.Point(330, 229)
        Me._lblShowData_19.TabIndex = 43
        Me._lblShowData_19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_19.Enabled = True
        Me._lblShowData_19.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_19.UseMnemonic = True
        Me._lblShowData_19.Visible = True
        Me._lblShowData_19.AutoSize = False
        Me._lblShowData_19.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_19.Name = "_lblShowData_19"
        Me.lblData19.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData19.BackColor = System.Drawing.SystemColors.Window
        Me.lblData19.Text = "Memory Location 304:"
        Me.lblData19.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData19.Size = New System.Drawing.Size(130, 14)
        Me.lblData19.Location = New System.Drawing.Point(189, 229)
        Me.lblData19.TabIndex = 42
        Me.lblData19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData19.Enabled = True
        Me.lblData19.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData19.UseMnemonic = True
        Me.lblData19.Visible = True
        Me.lblData19.AutoSize = False
        Me.lblData19.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData19.Name = "lblData19"
        Me._lblShowData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_9.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_9.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_9.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_9.Location = New System.Drawing.Point(144, 229)
        Me._lblShowData_9.TabIndex = 23
        Me._lblShowData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_9.Enabled = True
        Me._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_9.UseMnemonic = True
        Me._lblShowData_9.Visible = True
        Me._lblShowData_9.AutoSize = False
        Me._lblShowData_9.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_9.Name = "_lblShowData_9"
        Me.lblData9.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData9.BackColor = System.Drawing.SystemColors.Window
        Me.lblData9.Text = "Memory Location 104:"
        Me.lblData9.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData9.Size = New System.Drawing.Size(130, 15)
        Me.lblData9.Location = New System.Drawing.Point(10, 229)
        Me.lblData9.TabIndex = 21
        Me.lblData9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData9.Enabled = True
        Me.lblData9.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData9.UseMnemonic = True
        Me.lblData9.Visible = True
        Me.lblData9.AutoSize = False
        Me.lblData9.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData9.Name = "lblData9"
        Me._lblShowData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_18.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_18.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_18.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_18.Location = New System.Drawing.Point(330, 216)
        Me._lblShowData_18.TabIndex = 41
        Me._lblShowData_18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_18.Enabled = True
        Me._lblShowData_18.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_18.UseMnemonic = True
        Me._lblShowData_18.Visible = True
        Me._lblShowData_18.AutoSize = False
        Me._lblShowData_18.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_18.Name = "_lblShowData_18"
        Me.lblData18.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData18.BackColor = System.Drawing.SystemColors.Window
        Me.lblData18.Text = "Memory Location 303:"
        Me.lblData18.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData18.Size = New System.Drawing.Size(130, 14)
        Me.lblData18.Location = New System.Drawing.Point(189, 216)
        Me.lblData18.TabIndex = 40
        Me.lblData18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData18.Enabled = True
        Me.lblData18.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData18.UseMnemonic = True
        Me.lblData18.Visible = True
        Me.lblData18.AutoSize = False
        Me.lblData18.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData18.Name = "lblData18"
        Me._lblShowData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_8.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_8.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_8.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_8.Location = New System.Drawing.Point(144, 216)
        Me._lblShowData_8.TabIndex = 22
        Me._lblShowData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_8.Enabled = True
        Me._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_8.UseMnemonic = True
        Me._lblShowData_8.Visible = True
        Me._lblShowData_8.AutoSize = False
        Me._lblShowData_8.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_8.Name = "_lblShowData_8"
        Me.lblData8.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData8.BackColor = System.Drawing.SystemColors.Window
        Me.lblData8.Text = "Memory Location 103:"
        Me.lblData8.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData8.Size = New System.Drawing.Size(130, 15)
        Me.lblData8.Location = New System.Drawing.Point(10, 216)
        Me.lblData8.TabIndex = 20
        Me.lblData8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData8.Enabled = True
        Me.lblData8.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData8.UseMnemonic = True
        Me.lblData8.Visible = True
        Me.lblData8.AutoSize = False
        Me.lblData8.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData8.Name = "lblData8"
        Me._lblShowData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_17.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_17.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_17.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_17.Location = New System.Drawing.Point(330, 204)
        Me._lblShowData_17.TabIndex = 39
        Me._lblShowData_17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_17.Enabled = True
        Me._lblShowData_17.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_17.UseMnemonic = True
        Me._lblShowData_17.Visible = True
        Me._lblShowData_17.AutoSize = False
        Me._lblShowData_17.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_17.Name = "_lblShowData_17"
        Me.lblData17.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData17.BackColor = System.Drawing.SystemColors.Window
        Me.lblData17.Text = "Memory Location 302:"
        Me.lblData17.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData17.Size = New System.Drawing.Size(130, 14)
        Me.lblData17.Location = New System.Drawing.Point(189, 203)
        Me.lblData17.TabIndex = 38
        Me.lblData17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData17.Enabled = True
        Me.lblData17.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData17.UseMnemonic = True
        Me.lblData17.Visible = True
        Me.lblData17.AutoSize = False
        Me.lblData17.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData17.Name = "lblData17"
        Me._lblShowData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_7.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_7.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_7.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_7.Location = New System.Drawing.Point(144, 204)
        Me._lblShowData_7.TabIndex = 16
        Me._lblShowData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_7.Enabled = True
        Me._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_7.UseMnemonic = True
        Me._lblShowData_7.Visible = True
        Me._lblShowData_7.AutoSize = False
        Me._lblShowData_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_7.Name = "_lblShowData_7"
        Me.lblData7.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData7.BackColor = System.Drawing.SystemColors.Window
        Me.lblData7.Text = "Memory Location 102:"
        Me.lblData7.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData7.Size = New System.Drawing.Size(130, 15)
        Me.lblData7.Location = New System.Drawing.Point(10, 204)
        Me.lblData7.TabIndex = 8
        Me.lblData7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData7.Enabled = True
        Me.lblData7.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData7.UseMnemonic = True
        Me.lblData7.Visible = True
        Me.lblData7.AutoSize = False
        Me.lblData7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData7.Name = "lblData7"
        Me._lblShowData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_16.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_16.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_16.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_16.Location = New System.Drawing.Point(330, 191)
        Me._lblShowData_16.TabIndex = 37
        Me._lblShowData_16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_16.Enabled = True
        Me._lblShowData_16.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_16.UseMnemonic = True
        Me._lblShowData_16.Visible = True
        Me._lblShowData_16.AutoSize = False
        Me._lblShowData_16.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_16.Name = "_lblShowData_16"
        Me.lblData16.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData16.BackColor = System.Drawing.SystemColors.Window
        Me.lblData16.Text = "Memory Location 301:"
        Me.lblData16.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData16.Size = New System.Drawing.Size(130, 14)
        Me.lblData16.Location = New System.Drawing.Point(189, 190)
        Me.lblData16.TabIndex = 36
        Me.lblData16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData16.Enabled = True
        Me.lblData16.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData16.UseMnemonic = True
        Me.lblData16.Visible = True
        Me.lblData16.AutoSize = False
        Me.lblData16.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData16.Name = "lblData16"
        Me._lblShowData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_6.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_6.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_6.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_6.Location = New System.Drawing.Point(144, 191)
        Me._lblShowData_6.TabIndex = 15
        Me._lblShowData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_6.Enabled = True
        Me._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_6.UseMnemonic = True
        Me._lblShowData_6.Visible = True
        Me._lblShowData_6.AutoSize = False
        Me._lblShowData_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_6.Name = "_lblShowData_6"
        Me.lblData6.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData6.BackColor = System.Drawing.SystemColors.Window
        Me.lblData6.Text = "Memory Location 101:"
        Me.lblData6.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData6.Size = New System.Drawing.Size(130, 15)
        Me.lblData6.Location = New System.Drawing.Point(10, 191)
        Me.lblData6.TabIndex = 7
        Me.lblData6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData6.Enabled = True
        Me.lblData6.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData6.UseMnemonic = True
        Me.lblData6.Visible = True
        Me.lblData6.AutoSize = False
        Me.lblData6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData6.Name = "lblData6"
        Me._lblShowData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_15.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_15.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_15.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_15.Location = New System.Drawing.Point(330, 179)
        Me._lblShowData_15.TabIndex = 35
        Me._lblShowData_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_15.Enabled = True
        Me._lblShowData_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_15.UseMnemonic = True
        Me._lblShowData_15.Visible = True
        Me._lblShowData_15.AutoSize = False
        Me._lblShowData_15.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_15.Name = "_lblShowData_15"
        Me.lblData15.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData15.BackColor = System.Drawing.SystemColors.Window
        Me.lblData15.Text = "Memory Location 300:"
        Me.lblData15.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData15.Size = New System.Drawing.Size(130, 14)
        Me.lblData15.Location = New System.Drawing.Point(189, 178)
        Me.lblData15.TabIndex = 34
        Me.lblData15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData15.Enabled = True
        Me.lblData15.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData15.UseMnemonic = True
        Me.lblData15.Visible = True
        Me.lblData15.AutoSize = False
        Me.lblData15.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData15.Name = "lblData15"
        Me._lblShowData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_5.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_5.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_5.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_5.Location = New System.Drawing.Point(144, 179)
        Me._lblShowData_5.TabIndex = 14
        Me._lblShowData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_5.Enabled = True
        Me._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_5.UseMnemonic = True
        Me._lblShowData_5.Visible = True
        Me._lblShowData_5.AutoSize = False
        Me._lblShowData_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_5.Name = "_lblShowData_5"
        Me.lblData5.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData5.BackColor = System.Drawing.SystemColors.Window
        Me.lblData5.Text = "Memory Location 100:"
        Me.lblData5.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData5.Size = New System.Drawing.Size(130, 15)
        Me.lblData5.Location = New System.Drawing.Point(10, 179)
        Me.lblData5.TabIndex = 6
        Me.lblData5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData5.Enabled = True
        Me.lblData5.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData5.UseMnemonic = True
        Me.lblData5.Visible = True
        Me.lblData5.AutoSize = False
        Me.lblData5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData5.Name = "lblData5"
        Me._lblShowData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_14.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_14.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_14.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_14.Location = New System.Drawing.Point(330, 146)
        Me._lblShowData_14.TabIndex = 33
        Me._lblShowData_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_14.Enabled = True
        Me._lblShowData_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_14.UseMnemonic = True
        Me._lblShowData_14.Visible = True
        Me._lblShowData_14.AutoSize = False
        Me._lblShowData_14.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_14.Name = "_lblShowData_14"
        Me.lblData14.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData14.BackColor = System.Drawing.SystemColors.Window
        Me.lblData14.Text = "Memory Location 204:"
        Me.lblData14.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData14.Size = New System.Drawing.Size(130, 15)
        Me.lblData14.Location = New System.Drawing.Point(189, 146)
        Me.lblData14.TabIndex = 32
        Me.lblData14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData14.Enabled = True
        Me.lblData14.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData14.UseMnemonic = True
        Me.lblData14.Visible = True
        Me.lblData14.AutoSize = False
        Me.lblData14.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData14.Name = "lblData14"
        Me._lblShowData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_4.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_4.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_4.Location = New System.Drawing.Point(144, 146)
        Me._lblShowData_4.TabIndex = 13
        Me._lblShowData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_4.Enabled = True
        Me._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_4.UseMnemonic = True
        Me._lblShowData_4.Visible = True
        Me._lblShowData_4.AutoSize = False
        Me._lblShowData_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_4.Name = "_lblShowData_4"
        Me.lblData4.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData4.BackColor = System.Drawing.SystemColors.Window
        Me.lblData4.Text = "Memory Location 4:"
        Me.lblData4.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData4.Size = New System.Drawing.Size(130, 15)
        Me.lblData4.Location = New System.Drawing.Point(10, 146)
        Me.lblData4.TabIndex = 5
        Me.lblData4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData4.Enabled = True
        Me.lblData4.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData4.UseMnemonic = True
        Me.lblData4.Visible = True
        Me.lblData4.AutoSize = False
        Me.lblData4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData4.Name = "lblData4"
        Me._lblShowData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_13.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_13.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_13.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_13.Location = New System.Drawing.Point(330, 133)
        Me._lblShowData_13.TabIndex = 31
        Me._lblShowData_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_13.Enabled = True
        Me._lblShowData_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_13.UseMnemonic = True
        Me._lblShowData_13.Visible = True
        Me._lblShowData_13.AutoSize = False
        Me._lblShowData_13.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_13.Name = "_lblShowData_13"
        Me.lblData13.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData13.BackColor = System.Drawing.SystemColors.Window
        Me.lblData13.Text = "Memory Location 203:"
        Me.lblData13.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData13.Size = New System.Drawing.Size(130, 15)
        Me.lblData13.Location = New System.Drawing.Point(189, 133)
        Me.lblData13.TabIndex = 30
        Me.lblData13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData13.Enabled = True
        Me.lblData13.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData13.UseMnemonic = True
        Me.lblData13.Visible = True
        Me.lblData13.AutoSize = False
        Me.lblData13.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData13.Name = "lblData13"
        Me._lblShowData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_3.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_3.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_3.Location = New System.Drawing.Point(144, 133)
        Me._lblShowData_3.TabIndex = 12
        Me._lblShowData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_3.Enabled = True
        Me._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_3.UseMnemonic = True
        Me._lblShowData_3.Visible = True
        Me._lblShowData_3.AutoSize = False
        Me._lblShowData_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_3.Name = "_lblShowData_3"
        Me.lblData3.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData3.BackColor = System.Drawing.SystemColors.Window
        Me.lblData3.Text = "Memory Location 3:"
        Me.lblData3.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData3.Size = New System.Drawing.Size(130, 15)
        Me.lblData3.Location = New System.Drawing.Point(10, 133)
        Me.lblData3.TabIndex = 4
        Me.lblData3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData3.Enabled = True
        Me.lblData3.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData3.UseMnemonic = True
        Me.lblData3.Visible = True
        Me.lblData3.AutoSize = False
        Me.lblData3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData3.Name = "lblData3"
        Me._lblShowData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_12.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_12.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_12.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_12.Location = New System.Drawing.Point(330, 120)
        Me._lblShowData_12.TabIndex = 29
        Me._lblShowData_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_12.Enabled = True
        Me._lblShowData_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_12.UseMnemonic = True
        Me._lblShowData_12.Visible = True
        Me._lblShowData_12.AutoSize = False
        Me._lblShowData_12.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_12.Name = "_lblShowData_12"
        Me.lblData12.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData12.BackColor = System.Drawing.SystemColors.Window
        Me.lblData12.Text = "Memory Location 202:"
        Me.lblData12.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData12.Size = New System.Drawing.Size(130, 15)
        Me.lblData12.Location = New System.Drawing.Point(189, 120)
        Me.lblData12.TabIndex = 28
        Me.lblData12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData12.Enabled = True
        Me.lblData12.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData12.UseMnemonic = True
        Me.lblData12.Visible = True
        Me.lblData12.AutoSize = False
        Me.lblData12.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData12.Name = "lblData12"
        Me._lblShowData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_2.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_2.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_2.Location = New System.Drawing.Point(144, 120)
        Me._lblShowData_2.TabIndex = 11
        Me._lblShowData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_2.Enabled = True
        Me._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_2.UseMnemonic = True
        Me._lblShowData_2.Visible = True
        Me._lblShowData_2.AutoSize = False
        Me._lblShowData_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_2.Name = "_lblShowData_2"
        Me.lblData2.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData2.BackColor = System.Drawing.SystemColors.Window
        Me.lblData2.Text = "Memory Location 2:"
        Me.lblData2.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData2.Size = New System.Drawing.Size(130, 15)
        Me.lblData2.Location = New System.Drawing.Point(10, 120)
        Me.lblData2.TabIndex = 3
        Me.lblData2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData2.Enabled = True
        Me.lblData2.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData2.UseMnemonic = True
        Me.lblData2.Visible = True
        Me.lblData2.AutoSize = False
        Me.lblData2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData2.Name = "lblData2"
        Me._lblShowData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_11.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_11.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_11.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_11.Location = New System.Drawing.Point(330, 108)
        Me._lblShowData_11.TabIndex = 27
        Me._lblShowData_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_11.Enabled = True
        Me._lblShowData_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_11.UseMnemonic = True
        Me._lblShowData_11.Visible = True
        Me._lblShowData_11.AutoSize = False
        Me._lblShowData_11.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_11.Name = "_lblShowData_11"
        Me.lblData11.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData11.BackColor = System.Drawing.SystemColors.Window
        Me.lblData11.Text = "Memory Location 201:"
        Me.lblData11.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData11.Size = New System.Drawing.Size(130, 15)
        Me.lblData11.Location = New System.Drawing.Point(189, 108)
        Me.lblData11.TabIndex = 26
        Me.lblData11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData11.Enabled = True
        Me.lblData11.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData11.UseMnemonic = True
        Me.lblData11.Visible = True
        Me.lblData11.AutoSize = False
        Me.lblData11.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData11.Name = "lblData11"
        Me._lblShowData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_1.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_1.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_1.Location = New System.Drawing.Point(144, 108)
        Me._lblShowData_1.TabIndex = 10
        Me._lblShowData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_1.Enabled = True
        Me._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_1.UseMnemonic = True
        Me._lblShowData_1.Visible = True
        Me._lblShowData_1.AutoSize = False
        Me._lblShowData_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_1.Name = "_lblShowData_1"
        Me.lblData1.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData1.BackColor = System.Drawing.SystemColors.Window
        Me.lblData1.Text = "Memory Location 1:"
        Me.lblData1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData1.Size = New System.Drawing.Size(130, 15)
        Me.lblData1.Location = New System.Drawing.Point(10, 108)
        Me.lblData1.TabIndex = 2
        Me.lblData1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData1.Enabled = True
        Me.lblData1.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData1.UseMnemonic = True
        Me.lblData1.Visible = True
        Me.lblData1.AutoSize = False
        Me.lblData1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData1.Name = "lblData1"
        Me._lblShowData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_10.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_10.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_10.Size = New System.Drawing.Size(28, 15)
        Me._lblShowData_10.Location = New System.Drawing.Point(330, 96)
        Me._lblShowData_10.TabIndex = 25
        Me._lblShowData_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_10.Enabled = True
        Me._lblShowData_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_10.UseMnemonic = True
        Me._lblShowData_10.Visible = True
        Me._lblShowData_10.AutoSize = False
        Me._lblShowData_10.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_10.Name = "_lblShowData_10"
        Me.lblData10.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData10.BackColor = System.Drawing.SystemColors.Window
        Me.lblData10.Text = "Memory Location 200:"
        Me.lblData10.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData10.Size = New System.Drawing.Size(130, 15)
        Me.lblData10.Location = New System.Drawing.Point(189, 96)
        Me.lblData10.TabIndex = 24
        Me.lblData10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData10.Enabled = True
        Me.lblData10.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData10.UseMnemonic = True
        Me.lblData10.Visible = True
        Me.lblData10.AutoSize = False
        Me.lblData10.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData10.Name = "lblData10"
        Me._lblShowData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblShowData_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblShowData_0.ForeColor = System.Drawing.Color.Blue
        Me._lblShowData_0.Size = New System.Drawing.Size(34, 15)
        Me._lblShowData_0.Location = New System.Drawing.Point(144, 96)
        Me._lblShowData_0.TabIndex = 9
        Me._lblShowData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblShowData_0.Enabled = True
        Me._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblShowData_0.UseMnemonic = True
        Me._lblShowData_0.Visible = True
        Me._lblShowData_0.AutoSize = False
        Me._lblShowData_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblShowData_0.Name = "_lblShowData_0"
        Me.lblData0.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblData0.BackColor = System.Drawing.SystemColors.Window
        Me.lblData0.Text = "Memory Location 0:"
        Me.lblData0.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData0.Size = New System.Drawing.Size(130, 15)
        Me.lblData0.Location = New System.Drawing.Point(10, 96)
        Me.lblData0.TabIndex = 1
        Me.lblData0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData0.Enabled = True
        Me.lblData0.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData0.UseMnemonic = True
        Me.lblData0.Visible = True
        Me.lblData0.AutoSize = False
        Me.lblData0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData0.Name = "lblData0"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.MemRead() and Mccdaq.MccBoard.MemWrite()"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(310, 41)
        Me.lblDemoFunction.Location = New System.Drawing.Point(20, 7)
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
        Me.Controls.Add(cmdStopConvert)
        Me.Controls.Add(cmdReadData)
        Me.Controls.Add(cmdWriteData)
        Me.Controls.Add(lblInstruct2)
        Me.Controls.Add(lblInstruct1)
        Me.Controls.Add(_lblShowData_19)
        Me.Controls.Add(lblData19)
        Me.Controls.Add(_lblShowData_9)
        Me.Controls.Add(lblData9)
        Me.Controls.Add(_lblShowData_18)
        Me.Controls.Add(lblData18)
        Me.Controls.Add(_lblShowData_8)
        Me.Controls.Add(lblData8)
        Me.Controls.Add(_lblShowData_17)
        Me.Controls.Add(lblData17)
        Me.Controls.Add(_lblShowData_7)
        Me.Controls.Add(lblData7)
        Me.Controls.Add(_lblShowData_16)
        Me.Controls.Add(lblData16)
        Me.Controls.Add(_lblShowData_6)
        Me.Controls.Add(lblData6)
        Me.Controls.Add(_lblShowData_15)
        Me.Controls.Add(lblData15)
        Me.Controls.Add(_lblShowData_5)
        Me.Controls.Add(lblData5)
        Me.Controls.Add(_lblShowData_14)
        Me.Controls.Add(lblData14)
        Me.Controls.Add(_lblShowData_4)
        Me.Controls.Add(lblData4)
        Me.Controls.Add(_lblShowData_13)
        Me.Controls.Add(lblData13)
        Me.Controls.Add(_lblShowData_3)
        Me.Controls.Add(lblData3)
        Me.Controls.Add(_lblShowData_12)
        Me.Controls.Add(lblData12)
        Me.Controls.Add(_lblShowData_2)
        Me.Controls.Add(lblData2)
        Me.Controls.Add(_lblShowData_11)
        Me.Controls.Add(lblData11)
        Me.Controls.Add(_lblShowData_1)
        Me.Controls.Add(lblData1)
        Me.Controls.Add(_lblShowData_10)
        Me.Controls.Add(lblData10)
        Me.Controls.Add(_lblShowData_0)
        Me.Controls.Add(lblData0)
        Me.Controls.Add(lblDemoFunction)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        lblShowData = New System.Windows.Forms.Label(20) {}
        Me.lblShowData.SetValue(_lblShowData_0, 0)
        Me.lblShowData.SetValue(_lblShowData_1, 1)
        Me.lblShowData.SetValue(_lblShowData_2, 2)
        Me.lblShowData.SetValue(_lblShowData_3, 3)
        Me.lblShowData.SetValue(_lblShowData_4, 4)
        Me.lblShowData.SetValue(_lblShowData_5, 5)
        Me.lblShowData.SetValue(_lblShowData_6, 6)
        Me.lblShowData.SetValue(_lblShowData_7, 7)
        Me.lblShowData.SetValue(_lblShowData_8, 8)
        Me.lblShowData.SetValue(_lblShowData_9, 9)
        Me.lblShowData.SetValue(_lblShowData_10, 10)
        Me.lblShowData.SetValue(_lblShowData_11, 11)
        Me.lblShowData.SetValue(_lblShowData_12, 12)
        Me.lblShowData.SetValue(_lblShowData_13, 13)
        Me.lblShowData.SetValue(_lblShowData_14, 14)
        Me.lblShowData.SetValue(_lblShowData_15, 15)
        Me.lblShowData.SetValue(_lblShowData_16, 16)
        Me.lblShowData.SetValue(_lblShowData_17, 17)
        Me.lblShowData.SetValue(_lblShowData_18, 18)
        Me.lblShowData.SetValue(_lblShowData_19, 19)


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