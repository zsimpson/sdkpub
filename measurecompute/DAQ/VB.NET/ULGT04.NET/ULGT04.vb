'==============================================================================

'File:                         ULGT04.VB

'Library Call Demonstrated:     MccDaq.MccService.GetBoardName()


'Purpose:                      Prints a list of all boards installed in
'                              the system.  Prints a list of all supported
'                              boards.

'Other Library Calls:          MccDaq.MccService.ErrHandling()
'                              MccDaq.MccBoard.BoardName property
'                              MccDaq.GlobalConfig.NumBoards property  

'==============================================================================
Option Strict Off
Option Explicit On 
Imports VB = Microsoft.VisualBasic
Public Class frmListBoards
    Inherits System.Windows.Forms.Form


    Dim NumBoards As Integer

    Private Sub cmdListInstalled_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdListInstalled.Click
        Dim x As Short
        Dim StringSize As Integer
        Dim BoardName As String
        Dim ULStat As MccDaq.ErrorInfo
        Dim BoardNum As Integer
        Dim LineFeed As String
        Dim typeVal As Integer
        Dim pBoard(NumBoards) As MccDaq.MccBoard

        'Get board type of each board currently installed
        LineFeed = Chr(13) & Chr(10)

        txtListBoards.Text = "Currently installed boards:" & LineFeed & LineFeed
        For BoardNum = 0 To NumBoards - 1

            pBoard(BoardNum) = New MccDaq.MccBoard(BoardNum)
            ULStat = pBoard(BoardNum).BoardConfig.GetBoardType(typeVal)
            If typeVal <> 0 Then

                ' Get the BoardName property from the MccBoard object
                BoardName = pBoard(BoardNum).BoardName
                BoardName = RTrim(BoardName) 'Drop the space characters
                StringSize = Len(BoardName) - 1 'Drop the null character at end of string
                BoardName = VB.Left(BoardName, StringSize)
                txtListBoards.Text = txtListBoards.Text & "Board #" & (BoardNum + x).ToString("0") & "= " & BoardName & LineFeed
            End If
        Next

    End Sub

    Private Sub cmdListSupported_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdListSupported.Click
        Dim BoardList As String
        Dim StringSize As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim BoardName As String
        Dim LineFeed As String

        txtListBoards.Text = ""
        LineFeed = Chr(13) & Chr(10)

        'Get the first board type in list of supported boards
        'The first string in the boardlist is "Not Supported"
        BoardName = Space(MccDaq.MccService.BoardNameLen)

        ULStat = MccDaq.MccService.GetBoardName(MccDaq.MccService.GetFirst, BoardName)
        BoardName = RTrim(BoardName) 'Drop the space characters
        StringSize = Len(BoardName) - 1 'Drop the null character at end of string
        BoardName = VB.Left(BoardName, StringSize)
        BoardList = "The first string in the board name list is:" & LineFeed & "'" & BoardName & "'" & LineFeed & LineFeed

        'Get each consecutive board type in list
        Do
            BoardName = Space(MccDaq.MccService.BoardNameLen)
            ULStat = MccDaq.MccService.GetBoardName(MccDaq.MccService.GetNext, BoardName)
            BoardList = BoardList & BoardName & LineFeed
        Loop While Len(BoardName) > 3
        txtListBoards.Text = BoardList

    End Sub

    Private Sub cmdQuit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdQuit.Click

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
    Public WithEvents cmdQuit As System.Windows.Forms.Button
    Public WithEvents cmdListSupported As System.Windows.Forms.Button
    Public WithEvents cmdListInstalled As System.Windows.Forms.Button
    Public WithEvents txtListBoards As System.Windows.Forms.TextBox
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmListBoards))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.cmdQuit = New System.Windows.Forms.Button()
        Me.cmdListSupported = New System.Windows.Forms.Button()
        Me.cmdListInstalled = New System.Windows.Forms.Button()
        Me.txtListBoards = New System.Windows.Forms.TextBox()
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.Text = "Universal Library List Boards"
        Me.ClientSize = New System.Drawing.Size(307, 316)
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
        Me.Name = "frmListBoards"
        Me.cmdQuit.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdQuit.Text = "&Quit"
        Me.cmdQuit.Size = New System.Drawing.Size(65, 25)
        Me.cmdQuit.Location = New System.Drawing.Point(232, 280)
        Me.cmdQuit.TabIndex = 2
        Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
        Me.cmdQuit.CausesValidation = True
        Me.cmdQuit.Enabled = True
        Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdQuit.TabStop = True
        Me.cmdQuit.Name = "cmdQuit"
        Me.cmdListSupported.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdListSupported.Text = "Supported Boards"
        Me.cmdListSupported.Size = New System.Drawing.Size(109, 25)
        Me.cmdListSupported.Location = New System.Drawing.Point(116, 280)
        Me.cmdListSupported.TabIndex = 1
        Me.cmdListSupported.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdListSupported.BackColor = System.Drawing.SystemColors.Control
        Me.cmdListSupported.CausesValidation = True
        Me.cmdListSupported.Enabled = True
        Me.cmdListSupported.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdListSupported.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdListSupported.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdListSupported.TabStop = True
        Me.cmdListSupported.Name = "cmdListSupported"
        Me.cmdListInstalled.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdListInstalled.Text = "Installed Boards"
        Me.cmdListInstalled.Size = New System.Drawing.Size(101, 25)
        Me.cmdListInstalled.Location = New System.Drawing.Point(8, 280)
        Me.cmdListInstalled.TabIndex = 0
        Me.cmdListInstalled.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdListInstalled.BackColor = System.Drawing.SystemColors.Control
        Me.cmdListInstalled.CausesValidation = True
        Me.cmdListInstalled.Enabled = True
        Me.cmdListInstalled.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdListInstalled.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdListInstalled.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdListInstalled.TabStop = True
        Me.cmdListInstalled.Name = "cmdListInstalled"
        Me.txtListBoards.AutoSize = False
        Me.txtListBoards.Size = New System.Drawing.Size(289, 257)
        Me.txtListBoards.Location = New System.Drawing.Point(8, 8)
        Me.txtListBoards.Multiline = True
        Me.txtListBoards.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtListBoards.TabIndex = 3
        Me.txtListBoards.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtListBoards.AcceptsReturn = True
        Me.txtListBoards.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtListBoards.BackColor = System.Drawing.SystemColors.Window
        Me.txtListBoards.CausesValidation = True
        Me.txtListBoards.Enabled = True
        Me.txtListBoards.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtListBoards.HideSelection = True
        Me.txtListBoards.ReadOnly = False
        Me.txtListBoards.MaxLength = 0
        Me.txtListBoards.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtListBoards.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtListBoards.TabStop = True
        Me.txtListBoards.Visible = True
        Me.txtListBoards.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtListBoards.Name = "txtListBoards"
        Me.Controls.Add(cmdQuit)
        Me.Controls.Add(cmdListSupported)
        Me.Controls.Add(cmdListInstalled)
        Me.Controls.Add(txtListBoards)
    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()

        Dim ConfigVal As Integer
        Dim ConfigItem As Short
        Dim DevNum As Short
        Dim InfoType As Short
        Dim ULStat As MccDaq.ErrorInfo

        ' declare revision level of Universal Library

        ULStat = MccDaq.MccService.DeclareRevision(MccDaq.MccService.CurrentRevNum)

        ' Initiate error handling
        '  activating error handling will trap errors like
        '  bad channel numbers and non-configured conditions.
        '  Parameters:
        '    MccDaq.ErrorReporting.PrintAll  :all warnings and errors encountered will be printed
        '    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop


        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        'Get the number of boards installed in system

        NumBoards = MccDaq.GlobalConfig.NumBoards

    End Sub
#End Region

End Class