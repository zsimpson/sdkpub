'==============================================================================

'File:                         ULGT03.VB

'Library Call Demonstrated:    MccDaq.MccBoard.BoardConfig property
'                              MccDaq.MccBoard.DioConfig  property 
'                              MccDaq.MccBoard.ExpansionConfig property
'
'Purpose:                      Prints a list of all boards installed in
'                              the system and their base addresses.  Also
'                              prints the addresses of each digital and
'                              counter device on each board and any EXP
'                              boards that are connected to A/D channels.

'Other Library Calls:          MccDaq.MccBoard.GetBoardName()

'==============================================================================
Option Strict Off
Option Explicit On 
Imports VB = Microsoft.VisualBasic
Friend Class frmInfoDisplay
    Inherits System.Windows.Forms.Form

    Dim CurrentBoard As Integer
    Dim MaxNumBoards, NumBoards As Integer
    Dim NumADChans() As Integer
    Dim BoardName As String
    Dim LineFeed, Info As String

    Private Sub cmdPrintInfo_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdPrintInfo.Click

        Info = ""
        While (Len(Info) < 1 And CurrentBoard < MaxNumBoards)
            Dim pCurrentBoard As MccDaq.MccBoard = New MccDaq.MccBoard(CurrentBoard)
            PrintGenInfo(pCurrentBoard)
            PrintADInfo(pCurrentBoard)
            PrintDAInfo(pCurrentBoard)
            PrintDigInfo(pCurrentBoard)
            PrintCtrInfo(pCurrentBoard)
            PrintExpInfo(pCurrentBoard)

            CurrentBoard = CurrentBoard + 1
        End While

        If CurrentBoard > MaxNumBoards - 1 Then
            If NumBoards = 0 Then
                Info = LineFeed & LineFeed & Space(22) & "There are no boards installed." & LineFeed & LineFeed
                Info = Info & Space(12) & "You must run InstaCal to install the desired" & LineFeed
                Info = Info & Space(18) & "boards before running this program."
            Else
                Info = LineFeed & LineFeed & Space(16) & "There are no additional boards installed."
            End If
            cmdPrintInfo.Text = "Print Info"
            CurrentBoard = 0
            NumBoards = 0
        ElseIf Len(Info) > 0 Then
            cmdPrintInfo.Text = "Print Next"
            NumBoards = NumBoards + 1
        End If
        txtBoardInfo.Text = Info

    End Sub

    Private Sub cmdQuit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdQuit.Click

        End

    End Sub

    Private Sub PrintADInfo(ByRef pBoard As MccDaq.MccBoard)
        Dim ULStat As MccDaq.ErrorInfo
        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short

        DevNum = 0

        ULStat = pBoard.BoardConfig.GetNumAdChans(ConfigVal)

        NumADChans(pBoard.BoardNum) = ConfigVal
        If ConfigVal <> 0 Then Info = Info & Space(5) & "Number of A/D channels: " & ConfigVal.ToString("0") & LineFeed & LineFeed

    End Sub

    Private Sub PrintCtrInfo(ByRef pBoard As MccDaq.MccBoard)
        Dim NumDevs As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short

        'Get the number of counter devices for this board

        DevNum = 0

        ULStat = pBoard.BoardConfig.GetCiNumDevs(ConfigVal)

        NumDevs = ConfigVal

        If NumDevs > 0 Then Info = Info & Space(5) & "Counters : " & NumDevs.ToString("0") & LineFeed

        If Len(Info) <> 0 Then Info = Info & LineFeed

    End Sub

    Private Sub PrintDAInfo(ByRef pBoard As MccDaq.MccBoard)
        Dim NumDAChans As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short

        DevNum = 0

        ULStat = pBoard.BoardConfig.GetNumDaChans(ConfigVal)

        NumDAChans = ConfigVal
        If ConfigVal > 0 Then Info = Info & Space(5) & "Number of D/A channels: " & ConfigVal.ToString("0") & LineFeed & LineFeed

    End Sub

    Private Sub PrintDigInfo(ByVal pBoard As MccDaq.MccBoard)
        Dim NumBits As Integer
        Dim NumDevs As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short

        'get the number of digital devices for this board
        DevNum = 0

        ULStat = pBoard.BoardConfig.GetDiNumDevs(ConfigVal)

        NumDevs = ConfigVal

        For DevNum = 0 To NumDevs - 1
            'For each digital device, get the base address and number of bits

            ULStat = pBoard.DioConfig.GetNumBits(DevNum, ConfigVal)


            NumBits = ConfigVal
            Info = Info & Space(5) & "Digital Device #" & DevNum.ToString("0") & " : " & NumBits.ToString("0") & " bits" & LineFeed
        Next
        If Len(Info) <> 0 Then Info = Info & LineFeed

    End Sub

    Private Sub PrintExpInfo(ByRef pBoard As MccDaq.MccBoard)
        Dim ADChan2 As Integer
        Dim ADChan1 As Integer
        Dim BoardType As Integer
        Dim NumDevs As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short

        ' Get the number of Exps attached to pBoard
        DevNum = 0

        ULStat = pBoard.BoardConfig.GetNumExps(ConfigVal)
        NumDevs = ConfigVal

        For DevNum = 0 To NumDevs - 1

            pBoard.ExpansionConfig.GetBoardType(DevNum, ConfigVal)

            BoardType = ConfigVal

            pBoard.ExpansionConfig.GetMuxAdChan1(DevNum, ConfigVal)
            ADChan1 = ConfigVal
            If BoardType = 770 Then
                'it's a CIO-EXP32
                pBoard.ExpansionConfig.GetMuxAdChan2(DevNum, ConfigVal)
                ADChan2 = ConfigVal
                Info = Info & Space(5) & "A/D channels " & ADChan1.ToString("0") & " and " & ADChan2.ToString("0") & " connected to EXP(devID=" & BoardType.ToString("0") & ")." & LineFeed
            Else
                Info = Info & Space(5) & "A/D channel " & ADChan1.ToString("0") & " connected to EXP(devID=" & BoardType.ToString("0") & ")." & LineFeed
            End If


        Next
        If Len(Info) <> 0 Then Info = Info & LineFeed

    End Sub

    Private Sub PrintGenInfo(ByRef pBoard As MccDaq.MccBoard)
        Dim BaseAdrStr As String
        Dim StringSize As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short

        DevNum = 0

        'Get board type of each board
        ULStat = pBoard.BoardConfig.GetBoardType(ConfigVal)

        If (ConfigVal > 0) Then 'If a board is installed

            'Get the board's name
            BoardName = pBoard.BoardName

            BoardName = RTrim(BoardName) 'Drop the space characters
            StringSize = Len(BoardName) - 1 'Drop the null character at end of string
            BoardName = VB.Left(BoardName, StringSize)
            Info = Info & "Board #" & pBoard.BoardNum.ToString("0") & " = " & BoardName & " at "

            'Get the board's base address
            ULStat = pBoard.BoardConfig.GetBaseAdr(DevNum, ConfigVal)

            BaseAdrStr = Hex(ConfigVal)
            Info = Info & "Base Address = " & BaseAdrStr & " hex." & LineFeed & LineFeed
        End If

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
    Public WithEvents cmdQuit As System.Windows.Forms.Button
    Public WithEvents cmdPrintInfo As System.Windows.Forms.Button
    Public WithEvents txtBoardInfo As System.Windows.Forms.TextBox
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmInfoDisplay))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdQuit = New System.Windows.Forms.Button()
        Me.cmdPrintInfo = New System.Windows.Forms.Button()
        Me.txtBoardInfo = New System.Windows.Forms.TextBox()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library Configuration Info"
        Me.ClientSize = New System.Drawing.Size(432, 337)
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
        Me.Name = "frmInfoDisplay"
        Me.cmdQuit.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdQuit.Text = "Quit"
        Me.cmdQuit.Size = New System.Drawing.Size(57, 25)
        Me.cmdQuit.Location = New System.Drawing.Point(360, 304)
        Me.cmdQuit.TabIndex = 1
        Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
        Me.cmdQuit.CausesValidation = True
        Me.cmdQuit.Enabled = True
        Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdQuit.TabStop = True
        Me.cmdQuit.Name = "cmdQuit"
        Me.cmdPrintInfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdPrintInfo.Text = "Print Info"
        Me.AcceptButton = Me.cmdPrintInfo
        Me.cmdPrintInfo.Size = New System.Drawing.Size(76, 26)
        Me.cmdPrintInfo.Location = New System.Drawing.Point(160, 304)
        Me.cmdPrintInfo.TabIndex = 0
        Me.cmdPrintInfo.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdPrintInfo.BackColor = System.Drawing.SystemColors.Control
        Me.cmdPrintInfo.CausesValidation = True
        Me.cmdPrintInfo.Enabled = True
        Me.cmdPrintInfo.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdPrintInfo.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdPrintInfo.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdPrintInfo.TabStop = True
        Me.cmdPrintInfo.Name = "cmdPrintInfo"
        Me.txtBoardInfo.AutoSize = False
        Me.txtBoardInfo.Size = New System.Drawing.Size(401, 289)
        Me.txtBoardInfo.Location = New System.Drawing.Point(16, 8)
        Me.txtBoardInfo.Multiline = True
        Me.txtBoardInfo.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtBoardInfo.TabIndex = 2
        Me.txtBoardInfo.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtBoardInfo.AcceptsReturn = True
        Me.txtBoardInfo.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtBoardInfo.BackColor = System.Drawing.SystemColors.Window
        Me.txtBoardInfo.CausesValidation = True
        Me.txtBoardInfo.Enabled = True
        Me.txtBoardInfo.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtBoardInfo.HideSelection = True
        Me.txtBoardInfo.ReadOnly = False
        Me.txtBoardInfo.MaxLength = 0
        Me.txtBoardInfo.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtBoardInfo.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtBoardInfo.TabStop = True
        Me.txtBoardInfo.Visible = True
        Me.txtBoardInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtBoardInfo.Name = "txtBoardInfo"
        Me.Controls.Add(cmdQuit)
        Me.Controls.Add(cmdPrintInfo)
        Me.Controls.Add(txtBoardInfo)
    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Integer
        Dim InfoType As Short
        Dim ULStat As MccDaq.ErrorInfo

        ' declare revision level of Universal Library

        ULStat = MccDaq.MccService.DeclareRevision(MccDaq.MccService.CurrentRevNum)

        LineFeed = Chr(13) & Chr(10)
        DevNum = 0

        'Get the number of boards installed in system
        ConfigVal = MccDaq.GlobalConfig.NumBoards()
        MaxNumBoards = ConfigVal
        CurrentBoard = 0
        txtBoardInfo.Text = LineFeed & LineFeed & Space(12) & "Click on 'Print Info' to display board information."

        ReDim NumADChans(MaxNumBoards)
        NumBoards = 0
    End Sub
#End Region

End Class