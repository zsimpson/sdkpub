'==============================================================================

' File:                         ULCT03.VB

' Library Call Demonstrated:    9513 Counter Functions
'                               Mccdaq.MccBoard.C9513Config()
'                               Mccdaq.MccBoard.CStoreOnInt()

' Purpose:                      Operate the counter

' Demonstration:                Sets up 2 counters to store values in
'                               response to an interrupt
'

' Other Library Calls:          Mccdaq.MccBoard.C9513Init()
'                               Mccdaq.MccBoard.CLoad()
'                               Mccdaq.MccBoard.StopBackground()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a 9513 counter.
'                               IR enable must be tied low (Pin 2).
'                               User must generate an interrupt (Pin1).

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frm9513Int
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Const ChipNum As Integer = 1 ' use chip 1 for CIO-CTR05 or for first
    Const ControlSize As Short = 20 ' chip on CIO-CTR10
    Const MaxNumCntrs As Integer = 20 ' maximum number of 9513 counters onboard(CIO-CTR20)
    Const NumCntrs As Integer = 10 ' actual number of counters onboard the CIO-CTR10
    '   UPDATE THIS VALUE TO REFLECT THE NUMBER COUNTERS
    '       FOR SPECIFIC MODEL INSTALLED
    Const IntCount As Integer = 100 ' the windows buffer pointed to by MemHandle will hold enough
    ' data for IntCount interrupts

    Dim DataBuffer(MaxNumCntrs) As UInt16 ' array to hold latest readings from each of the counters
    Dim CntrControl(MaxNumCntrs) As MccDaq.CounterControl ' array to control whether or not each counter is enabled
    Dim MemHandle As Integer ' handle to windows data buffer that is large enough to hold
    ' IntCount readings from each of the NumCntrs counters
    Dim FirstPoint As Integer

    Public lblCount As System.Windows.Forms.Label()
    Public lblCounterNum As System.Windows.Forms.Label()
    Public lblIntStatus As System.Windows.Forms.Label()

    Private Sub cmdStartInt_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartInt.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim I As Short

        cmdStartInt.Enabled = False
        cmdStartInt.Visible = False
        cmdStopRead.Enabled = True
        cmdStopRead.Visible = True

        ' set the counters to store their values upon an interrupt
        '  Parameters:
        '    IntCount      :maximum number of interrupts
        '    CntrControl() :array which indicates the channels to be read
        '    DataBuffer()  :array that receives the count values for enabled
        '                    channels each time an interrupt occur

        ' set all channels to MccDaq.CounterControl.Disabled  and init DataBuffer
        For I = 0 To NumCntrs - 1
            CntrControl(I) = MccDaq.CounterControl.Disabled
            DataBuffer(I) = Convert.ToUInt16(0)
        Next I

        ' enable the channels to be monitored
        CntrControl(0) = MccDaq.CounterControl.Enabled
        CntrControl(1) = MccDaq.CounterControl.Enabled

        ULStat = DaqBoard.CStoreOnInt(IntCount, CntrControl(0), MemHandle)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        tmrReadStatus.Enabled = True
        FirstPoint = 0

    End Sub

    Private Sub cmdStopRead_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopRead.Click
        Dim ULStat As MccDaq.ErrorInfo

        ' the BACKGROUND operation must be explicitly stopped

        ' Parameters:
        '   FunctionType:counter operation (MccDaq.FunctionType.CtrFunction)

        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.CtrFunction)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop ' other programs

        End

    End Sub

    Private Sub tmrReadStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrReadStatus.Tick
        Dim RealCount As UInt16
        Dim DISABLED As Object
        Dim IntStatus As String
        Dim I As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short

        tmrReadStatus.Stop()
        
        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.CtrFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        FirstPoint = 0
        'This line is NOT necessary for 32-bit library.
        CurIndex = (CurCount Mod IntCount) - 1

        'The calculation below requires that NumCntrs accurately reflects the number
        '  of counters onboard whether or not they are enabled or active.
        If CurIndex > 0 Then
            FirstPoint = NumCntrs * CurIndex
        End If

        ULStat = MccDaq.MccService.WinBufToArray(MemHandle, DataBuffer(0), FirstPoint, NumCntrs)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        For I = 0 To 4
            If CntrControl(I) = MccDaq.CounterControl.Disabled Then
                IntStatus = "DISABLED"
            Else
                IntStatus = "ENABLED "
            End If

            ' convert type int to type long

            RealCount = DataBuffer(I)

            lblCounterNum(I).Text = (I + 1).ToString("0")
            lblIntStatus(I).Text = IntStatus
            lblCount(I).Text = RealCount.ToString("0")

        Next I


        lblShowTotal.Text = CurCount.ToString("0")
        
        tmrReadStatus.Start()

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
    Public WithEvents cmdStartInt As System.Windows.Forms.Button
    Public WithEvents cmdStopRead As System.Windows.Forms.Button
    Public WithEvents tmrReadStatus As System.Windows.Forms.Timer
    Public WithEvents lblShowTotal As System.Windows.Forms.Label
    Public WithEvents lblIntTotal As System.Windows.Forms.Label
    Public WithEvents _lblCount_4 As System.Windows.Forms.Label
    Public WithEvents _lblIntStatus_4 As System.Windows.Forms.Label
    Public WithEvents _lblCounterNum_4 As System.Windows.Forms.Label
    Public WithEvents _lblCount_3 As System.Windows.Forms.Label
    Public WithEvents _lblIntStatus_3 As System.Windows.Forms.Label
    Public WithEvents _lblCounterNum_3 As System.Windows.Forms.Label
    Public WithEvents _lblCount_2 As System.Windows.Forms.Label
    Public WithEvents _lblIntStatus_2 As System.Windows.Forms.Label
    Public WithEvents _lblCounterNum_2 As System.Windows.Forms.Label
    Public WithEvents _lblCount_1 As System.Windows.Forms.Label
    Public WithEvents _lblIntStatus_1 As System.Windows.Forms.Label
    Public WithEvents _lblCounterNum_1 As System.Windows.Forms.Label
    Public WithEvents _lblCount_0 As System.Windows.Forms.Label
    Public WithEvents _lblIntStatus_0 As System.Windows.Forms.Label
    Public WithEvents _lblCounterNum_0 As System.Windows.Forms.Label
    Public WithEvents lblData As System.Windows.Forms.Label
    Public WithEvents lblStatCol As System.Windows.Forms.Label
    Public WithEvents lblCountCol As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frm9513Int))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdStartInt = New System.Windows.Forms.Button()
        Me.cmdStopRead = New System.Windows.Forms.Button()
        Me.tmrReadStatus = New System.Windows.Forms.Timer(components)
        Me.lblShowTotal = New System.Windows.Forms.Label()
        Me.lblIntTotal = New System.Windows.Forms.Label()
        Me._lblCount_4 = New System.Windows.Forms.Label()
        Me._lblIntStatus_4 = New System.Windows.Forms.Label()
        Me._lblCounterNum_4 = New System.Windows.Forms.Label()
        Me._lblCount_3 = New System.Windows.Forms.Label()
        Me._lblIntStatus_3 = New System.Windows.Forms.Label()
        Me._lblCounterNum_3 = New System.Windows.Forms.Label()
        Me._lblCount_2 = New System.Windows.Forms.Label()
        Me._lblIntStatus_2 = New System.Windows.Forms.Label()
        Me._lblCounterNum_2 = New System.Windows.Forms.Label()
        Me._lblCount_1 = New System.Windows.Forms.Label()
        Me._lblIntStatus_1 = New System.Windows.Forms.Label()
        Me._lblCounterNum_1 = New System.Windows.Forms.Label()
        Me._lblCount_0 = New System.Windows.Forms.Label()
        Me._lblIntStatus_0 = New System.Windows.Forms.Label()
        Me._lblCounterNum_0 = New System.Windows.Forms.Label()
        Me.lblData = New System.Windows.Forms.Label()
        Me.lblStatCol = New System.Windows.Forms.Label()
        Me.lblCountCol = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library 9513 Counter Demo"
        Me.ClientSize = New System.Drawing.Size(350, 296)
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
        Me.Name = "frm9513Int"
        Me.cmdStartInt.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStartInt.Text = "Start"
        Me.cmdStartInt.Size = New System.Drawing.Size(57, 25)
        Me.cmdStartInt.Location = New System.Drawing.Point(272, 248)
        Me.cmdStartInt.TabIndex = 4
        Me.cmdStartInt.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStartInt.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStartInt.CausesValidation = True
        Me.cmdStartInt.Enabled = True
        Me.cmdStartInt.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStartInt.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStartInt.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStartInt.TabStop = True
        Me.cmdStartInt.Name = "cmdStartInt"
        Me.cmdStopRead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStopRead.Text = "Quit"
        Me.AcceptButton = Me.cmdStopRead
        Me.cmdStopRead.Enabled = False
        Me.cmdStopRead.Size = New System.Drawing.Size(57, 25)
        Me.cmdStopRead.Location = New System.Drawing.Point(272, 248)
        Me.cmdStopRead.TabIndex = 3
        Me.cmdStopRead.Visible = False
        Me.cmdStopRead.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStopRead.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStopRead.CausesValidation = True
        Me.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStopRead.TabStop = True
        Me.cmdStopRead.Name = "cmdStopRead"
        Me.tmrReadStatus.Enabled = False
        Me.tmrReadStatus.Interval = 200
        Me.lblShowTotal.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowTotal.ForeColor = System.Drawing.Color.Blue
        Me.lblShowTotal.Size = New System.Drawing.Size(65, 17)
        Me.lblShowTotal.Location = New System.Drawing.Point(168, 256)
        Me.lblShowTotal.TabIndex = 18
        Me.lblShowTotal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowTotal.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblShowTotal.Enabled = True
        Me.lblShowTotal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowTotal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowTotal.UseMnemonic = True
        Me.lblShowTotal.Visible = True
        Me.lblShowTotal.AutoSize = False
        Me.lblShowTotal.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblShowTotal.Name = "lblShowTotal"
        Me.lblIntTotal.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.lblIntTotal.BackColor = System.Drawing.SystemColors.Window
        Me.lblIntTotal.Text = "Total Interrupts:"
        Me.lblIntTotal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblIntTotal.Size = New System.Drawing.Size(105, 17)
        Me.lblIntTotal.Location = New System.Drawing.Point(56, 256)
        Me.lblIntTotal.TabIndex = 22
        Me.lblIntTotal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblIntTotal.Enabled = True
        Me.lblIntTotal.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblIntTotal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblIntTotal.UseMnemonic = True
        Me.lblIntTotal.Visible = True
        Me.lblIntTotal.AutoSize = False
        Me.lblIntTotal.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblIntTotal.Name = "lblIntTotal"
        Me._lblCount_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCount_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblCount_4.ForeColor = System.Drawing.Color.Blue
        Me._lblCount_4.Size = New System.Drawing.Size(65, 17)
        Me._lblCount_4.Location = New System.Drawing.Point(216, 208)
        Me._lblCount_4.TabIndex = 17
        Me._lblCount_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCount_4.Enabled = True
        Me._lblCount_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCount_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCount_4.UseMnemonic = True
        Me._lblCount_4.Visible = True
        Me._lblCount_4.AutoSize = False
        Me._lblCount_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCount_4.Name = "_lblCount_4"
        Me._lblIntStatus_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblIntStatus_4.ForeColor = System.Drawing.Color.Blue
        Me._lblIntStatus_4.Size = New System.Drawing.Size(73, 17)
        Me._lblIntStatus_4.Location = New System.Drawing.Point(120, 208)
        Me._lblIntStatus_4.TabIndex = 12
        Me._lblIntStatus_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblIntStatus_4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblIntStatus_4.Enabled = True
        Me._lblIntStatus_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblIntStatus_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblIntStatus_4.UseMnemonic = True
        Me._lblIntStatus_4.Visible = True
        Me._lblIntStatus_4.AutoSize = False
        Me._lblIntStatus_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblIntStatus_4.Name = "_lblIntStatus_4"
        Me._lblCounterNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCounterNum_4.BackColor = System.Drawing.SystemColors.Window
        Me._lblCounterNum_4.Text = "5"
        Me._lblCounterNum_4.ForeColor = System.Drawing.Color.Black
        Me._lblCounterNum_4.Size = New System.Drawing.Size(25, 17)
        Me._lblCounterNum_4.Location = New System.Drawing.Point(72, 208)
        Me._lblCounterNum_4.TabIndex = 8
        Me._lblCounterNum_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCounterNum_4.Enabled = True
        Me._lblCounterNum_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCounterNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCounterNum_4.UseMnemonic = True
        Me._lblCounterNum_4.Visible = True
        Me._lblCounterNum_4.AutoSize = False
        Me._lblCounterNum_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCounterNum_4.Name = "_lblCounterNum_4"
        Me._lblCount_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCount_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblCount_3.ForeColor = System.Drawing.Color.Blue
        Me._lblCount_3.Size = New System.Drawing.Size(65, 17)
        Me._lblCount_3.Location = New System.Drawing.Point(216, 184)
        Me._lblCount_3.TabIndex = 16
        Me._lblCount_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCount_3.Enabled = True
        Me._lblCount_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCount_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCount_3.UseMnemonic = True
        Me._lblCount_3.Visible = True
        Me._lblCount_3.AutoSize = False
        Me._lblCount_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCount_3.Name = "_lblCount_3"
        Me._lblIntStatus_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblIntStatus_3.ForeColor = System.Drawing.Color.Blue
        Me._lblIntStatus_3.Size = New System.Drawing.Size(73, 17)
        Me._lblIntStatus_3.Location = New System.Drawing.Point(120, 184)
        Me._lblIntStatus_3.TabIndex = 11
        Me._lblIntStatus_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblIntStatus_3.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblIntStatus_3.Enabled = True
        Me._lblIntStatus_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblIntStatus_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblIntStatus_3.UseMnemonic = True
        Me._lblIntStatus_3.Visible = True
        Me._lblIntStatus_3.AutoSize = False
        Me._lblIntStatus_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblIntStatus_3.Name = "_lblIntStatus_3"
        Me._lblCounterNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCounterNum_3.BackColor = System.Drawing.SystemColors.Window
        Me._lblCounterNum_3.Text = "4"
        Me._lblCounterNum_3.ForeColor = System.Drawing.Color.Black
        Me._lblCounterNum_3.Size = New System.Drawing.Size(25, 17)
        Me._lblCounterNum_3.Location = New System.Drawing.Point(72, 184)
        Me._lblCounterNum_3.TabIndex = 7
        Me._lblCounterNum_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCounterNum_3.Enabled = True
        Me._lblCounterNum_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCounterNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCounterNum_3.UseMnemonic = True
        Me._lblCounterNum_3.Visible = True
        Me._lblCounterNum_3.AutoSize = False
        Me._lblCounterNum_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCounterNum_3.Name = "_lblCounterNum_3"
        Me._lblCount_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCount_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblCount_2.ForeColor = System.Drawing.Color.Blue
        Me._lblCount_2.Size = New System.Drawing.Size(65, 17)
        Me._lblCount_2.Location = New System.Drawing.Point(216, 160)
        Me._lblCount_2.TabIndex = 15
        Me._lblCount_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCount_2.Enabled = True
        Me._lblCount_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCount_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCount_2.UseMnemonic = True
        Me._lblCount_2.Visible = True
        Me._lblCount_2.AutoSize = False
        Me._lblCount_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCount_2.Name = "_lblCount_2"
        Me._lblIntStatus_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblIntStatus_2.ForeColor = System.Drawing.Color.Blue
        Me._lblIntStatus_2.Size = New System.Drawing.Size(73, 17)
        Me._lblIntStatus_2.Location = New System.Drawing.Point(120, 160)
        Me._lblIntStatus_2.TabIndex = 10
        Me._lblIntStatus_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblIntStatus_2.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblIntStatus_2.Enabled = True
        Me._lblIntStatus_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblIntStatus_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblIntStatus_2.UseMnemonic = True
        Me._lblIntStatus_2.Visible = True
        Me._lblIntStatus_2.AutoSize = False
        Me._lblIntStatus_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblIntStatus_2.Name = "_lblIntStatus_2"
        Me._lblCounterNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCounterNum_2.BackColor = System.Drawing.SystemColors.Window
        Me._lblCounterNum_2.Text = "3"
        Me._lblCounterNum_2.ForeColor = System.Drawing.Color.Black
        Me._lblCounterNum_2.Size = New System.Drawing.Size(25, 17)
        Me._lblCounterNum_2.Location = New System.Drawing.Point(72, 160)
        Me._lblCounterNum_2.TabIndex = 6
        Me._lblCounterNum_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCounterNum_2.Enabled = True
        Me._lblCounterNum_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCounterNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCounterNum_2.UseMnemonic = True
        Me._lblCounterNum_2.Visible = True
        Me._lblCounterNum_2.AutoSize = False
        Me._lblCounterNum_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCounterNum_2.Name = "_lblCounterNum_2"
        Me._lblCount_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCount_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblCount_1.ForeColor = System.Drawing.Color.Blue
        Me._lblCount_1.Size = New System.Drawing.Size(65, 17)
        Me._lblCount_1.Location = New System.Drawing.Point(216, 136)
        Me._lblCount_1.TabIndex = 14
        Me._lblCount_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCount_1.Enabled = True
        Me._lblCount_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCount_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCount_1.UseMnemonic = True
        Me._lblCount_1.Visible = True
        Me._lblCount_1.AutoSize = False
        Me._lblCount_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCount_1.Name = "_lblCount_1"
        Me._lblIntStatus_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblIntStatus_1.ForeColor = System.Drawing.Color.Blue
        Me._lblIntStatus_1.Size = New System.Drawing.Size(73, 17)
        Me._lblIntStatus_1.Location = New System.Drawing.Point(120, 136)
        Me._lblIntStatus_1.TabIndex = 9
        Me._lblIntStatus_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblIntStatus_1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblIntStatus_1.Enabled = True
        Me._lblIntStatus_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblIntStatus_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblIntStatus_1.UseMnemonic = True
        Me._lblIntStatus_1.Visible = True
        Me._lblIntStatus_1.AutoSize = False
        Me._lblIntStatus_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblIntStatus_1.Name = "_lblIntStatus_1"
        Me._lblCounterNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCounterNum_1.BackColor = System.Drawing.SystemColors.Window
        Me._lblCounterNum_1.Text = "2"
        Me._lblCounterNum_1.ForeColor = System.Drawing.Color.Black
        Me._lblCounterNum_1.Size = New System.Drawing.Size(25, 17)
        Me._lblCounterNum_1.Location = New System.Drawing.Point(72, 136)
        Me._lblCounterNum_1.TabIndex = 5
        Me._lblCounterNum_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCounterNum_1.Enabled = True
        Me._lblCounterNum_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCounterNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCounterNum_1.UseMnemonic = True
        Me._lblCounterNum_1.Visible = True
        Me._lblCounterNum_1.AutoSize = False
        Me._lblCounterNum_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCounterNum_1.Name = "_lblCounterNum_1"
        Me._lblCount_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCount_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblCount_0.ForeColor = System.Drawing.Color.Blue
        Me._lblCount_0.Size = New System.Drawing.Size(65, 17)
        Me._lblCount_0.Location = New System.Drawing.Point(216, 112)
        Me._lblCount_0.TabIndex = 13
        Me._lblCount_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCount_0.Enabled = True
        Me._lblCount_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCount_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCount_0.UseMnemonic = True
        Me._lblCount_0.Visible = True
        Me._lblCount_0.AutoSize = False
        Me._lblCount_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCount_0.Name = "_lblCount_0"
        Me._lblIntStatus_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblIntStatus_0.ForeColor = System.Drawing.Color.Blue
        Me._lblIntStatus_0.Size = New System.Drawing.Size(73, 17)
        Me._lblIntStatus_0.Location = New System.Drawing.Point(120, 112)
        Me._lblIntStatus_0.TabIndex = 2
        Me._lblIntStatus_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblIntStatus_0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblIntStatus_0.Enabled = True
        Me._lblIntStatus_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblIntStatus_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblIntStatus_0.UseMnemonic = True
        Me._lblIntStatus_0.Visible = True
        Me._lblIntStatus_0.AutoSize = False
        Me._lblIntStatus_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblIntStatus_0.Name = "_lblIntStatus_0"
        Me._lblCounterNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me._lblCounterNum_0.BackColor = System.Drawing.SystemColors.Window
        Me._lblCounterNum_0.Text = "1"
        Me._lblCounterNum_0.ForeColor = System.Drawing.Color.Black
        Me._lblCounterNum_0.Size = New System.Drawing.Size(25, 17)
        Me._lblCounterNum_0.Location = New System.Drawing.Point(72, 112)
        Me._lblCounterNum_0.TabIndex = 1
        Me._lblCounterNum_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblCounterNum_0.Enabled = True
        Me._lblCounterNum_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblCounterNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblCounterNum_0.UseMnemonic = True
        Me._lblCounterNum_0.Visible = True
        Me._lblCounterNum_0.AutoSize = False
        Me._lblCounterNum_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblCounterNum_0.Name = "_lblCounterNum_0"
        Me.lblData.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblData.BackColor = System.Drawing.SystemColors.Window
        Me.lblData.Text = "Data Value"
        Me.lblData.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblData.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblData.Size = New System.Drawing.Size(81, 17)
        Me.lblData.Location = New System.Drawing.Point(208, 80)
        Me.lblData.TabIndex = 21
        Me.lblData.Enabled = True
        Me.lblData.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblData.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblData.UseMnemonic = True
        Me.lblData.Visible = True
        Me.lblData.AutoSize = False
        Me.lblData.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblData.Name = "lblData"
        Me.lblStatCol.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblStatCol.BackColor = System.Drawing.SystemColors.Window
        Me.lblStatCol.Text = "Status"
        Me.lblStatCol.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatCol.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblStatCol.Size = New System.Drawing.Size(57, 17)
        Me.lblStatCol.Location = New System.Drawing.Point(128, 80)
        Me.lblStatCol.TabIndex = 20
        Me.lblStatCol.Enabled = True
        Me.lblStatCol.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatCol.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatCol.UseMnemonic = True
        Me.lblStatCol.Visible = True
        Me.lblStatCol.AutoSize = False
        Me.lblStatCol.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblStatCol.Name = "lblStatCol"
        Me.lblCountCol.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblCountCol.BackColor = System.Drawing.SystemColors.Window
        Me.lblCountCol.Text = "Counter"
        Me.lblCountCol.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblCountCol.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblCountCol.Size = New System.Drawing.Size(57, 17)
        Me.lblCountCol.Location = New System.Drawing.Point(56, 80)
        Me.lblCountCol.TabIndex = 19
        Me.lblCountCol.Enabled = True
        Me.lblCountCol.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblCountCol.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblCountCol.UseMnemonic = True
        Me.lblCountCol.Visible = True
        Me.lblCountCol.AutoSize = False
        Me.lblCountCol.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblCountCol.Name = "lblCountCol"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Text = "Demonstration of 9513 Counter using Interrupts"
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Size = New System.Drawing.Size(281, 41)
        Me.lblDemoFunction.Location = New System.Drawing.Point(32, 16)
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
        Me.Controls.Add(cmdStartInt)
        Me.Controls.Add(cmdStopRead)
        Me.Controls.Add(lblShowTotal)
        Me.Controls.Add(lblIntTotal)
        Me.Controls.Add(_lblCount_4)
        Me.Controls.Add(_lblIntStatus_4)
        Me.Controls.Add(_lblCounterNum_4)
        Me.Controls.Add(_lblCount_3)
        Me.Controls.Add(_lblIntStatus_3)
        Me.Controls.Add(_lblCounterNum_3)
        Me.Controls.Add(_lblCount_2)
        Me.Controls.Add(_lblIntStatus_2)
        Me.Controls.Add(_lblCounterNum_2)
        Me.Controls.Add(_lblCount_1)
        Me.Controls.Add(_lblIntStatus_1)
        Me.Controls.Add(_lblCounterNum_1)
        Me.Controls.Add(_lblCount_0)
        Me.Controls.Add(_lblIntStatus_0)
        Me.Controls.Add(_lblCounterNum_0)
        Me.Controls.Add(lblData)
        Me.Controls.Add(lblStatCol)
        Me.Controls.Add(lblCountCol)
        Me.Controls.Add(lblDemoFunction)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim RegName As MccDaq.CounterRegister
        Dim LoadValue As UInt32
        Dim OutputControl As MccDaq.C9513OutputControl
        Dim CountDirection As MccDaq.CountDirection
        Dim BCDMode As MccDaq.BCDMode
        Dim RecycleMode As MccDaq.RecycleMode
        Dim Reload As MccDaq.Reload
        Dim SpecialGate As MccDaq.OptionState
        Dim CountSource As MccDaq.CounterSource
        Dim CounterEdge As MccDaq.CountEdge
        Dim GateControl As MccDaq.GateControl
        Dim CounterNum As Integer
        Dim TimeOfDayCounting As MccDaq.TimeOfDay
        Dim Compare2 As MccDaq.CompareValue
        Dim Compare1 As MccDaq.CompareValue
        Dim Source As MccDaq.CounterSource
        Dim FOutDivider As Integer
        Dim ULStat As MccDaq.ErrorInfo


        Me.lblCount = New System.Windows.Forms.Label(5) {}
        Me.lblCount.SetValue(_lblCount_4, 4)
        Me.lblCount.SetValue(_lblCount_3, 3)
        Me.lblCount.SetValue(_lblCount_2, 2)
        Me.lblCount.SetValue(_lblCount_1, 1)
        Me.lblCount.SetValue(_lblCount_0, 0)

        Me.lblCounterNum = New System.Windows.Forms.Label(5) {}
        Me.lblCounterNum.SetValue(_lblCounterNum_4, 4)
        Me.lblCounterNum.SetValue(_lblCounterNum_3, 3)
        Me.lblCounterNum.SetValue(_lblCounterNum_2, 2)
        Me.lblCounterNum.SetValue(_lblCounterNum_1, 1)
        Me.lblCounterNum.SetValue(_lblCounterNum_0, 0)

        Me.lblIntStatus = New System.Windows.Forms.Label(5) {}
        Me.lblIntStatus.SetValue(_lblIntStatus_4, 4)
        Me.lblIntStatus.SetValue(_lblIntStatus_3, 3)
        Me.lblIntStatus.SetValue(_lblIntStatus_2, 2)
        Me.lblIntStatus.SetValue(_lblIntStatus_1, 1)
        Me.lblIntStatus.SetValue(_lblIntStatus_0, 0)


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


        MemHandle = MccDaq.MccService.WinBufAlloc(IntCount * MaxNumCntrs) ' set aside memory to hold data
        If MemHandle = 0 Then Stop ' we're allocating enough for
        ' MaxNumCntrs in case actual NumCntrs
        ' had not been updated
        ' Initialize the board level features
        '  Parameters:
        '    ChipNum    :chip to be initialized (1 for CTR5, 1 or 2 for CTR10)
        '    FOutDivider:the F-Out divider (0-15)
        '    Source     :the signal source for F-Out
        '    Compare1   :status of comparator 1
        '    Compare2   :status of comparator 2
        '    TimeOfDayCounting  :time of day mode control

        FOutDivider = 10 ' sets up OSC OUT for 10Hz signal which can
        Source = MccDaq.CounterSource.Freq5 ' be used as interrupt source for this example
        Compare1 = MccDaq.CompareValue.Disabled
        Compare2 = MccDaq.CompareValue.Disabled
        TimeOfDayCounting = MccDaq.TimeOfDay.Disabled

        ULStat = DaqBoard.C9513Init(ChipNum, FOutDivider, Source, Compare1, Compare2, TimeOfDayCounting)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Set the configurable operations of the counter
        '  Parameters:
        '    CounterNum     :the counter to be configured (1 to 5)
        '    GateControl    :gate control value
        '    CounterEdge    :which edge to count
        '    CountSource    :signal source
        '    SpecialGate    :status of special gate
        '    Reload         :method of reloading
        '    RecyleMode     :recyle mode
        '    BCDMode        :counting mode, Binary or BCD
        '    CountDirection :direction for the counting operation (COUNTUP or COUNTDOWN)
        '    OutputControl  :output signal type and level

        ' Initialize variables for the first of two counters

        CounterNum = 1 ' number of counter used
        GateControl = MccDaq.GateControl.NoGate
        CounterEdge = MccDaq.CountEdge.PositiveEdge
        CountSource = MccDaq.CounterSource.Freq3
        SpecialGate = MccDaq.OptionState.Disabled
        Reload = MccDaq.Reload.LoadReg
        RecycleMode = MccDaq.RecycleMode.Recycle
        BCDMode = MccDaq.BCDMode.Disabled
        CountDirection = MccDaq.CountDirection.CountUp
        OutputControl = MccDaq.C9513OutputControl.AlwaysLow

        ULStat = DaqBoard.C9513Config(CounterNum, GateControl, CounterEdge, CountSource, SpecialGate, Reload, RecycleMode, BCDMode, CountDirection, OutputControl)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Initialize variables for the second counter

        CounterNum = 2 ' number of counter used
        ULStat = DaqBoard.C9513Config(CounterNum, GateControl, CounterEdge, CountSource, SpecialGate, Reload, RecycleMode, BCDMode, CountDirection, OutputControl)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ' Load the 2 counters with starting values of zero with MccDaq.MccBoard.CLoad()
        '  Parameters:
        '    RegName    :the counter to be loaded with the starting value
        '    LoadValue  :the starting value to place in the counter

        LoadValue = Convert.ToUInt32(0)
        RegName = MccDaq.CounterRegister.LoadReg1 ' name of register in counter 1

        ULStat = DaqBoard.CLoad(RegName, LoadValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        RegName = MccDaq.CounterRegister.LoadReg2 ' name of register in counter 2

        ULStat = DaqBoard.CLoad(RegName, LoadValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


    End Sub
#End Region

End Class