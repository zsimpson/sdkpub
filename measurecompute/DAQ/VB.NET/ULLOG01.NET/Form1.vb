Public Class Form1
    Inherits System.Windows.Forms.Form

    Private Const MAX_PATH As Integer = 260
    Private Const m_Path As String = "..\\..\\.."
    Private Const m_FileNumber As Integer = 0

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        Dim ULStat As MccDaq.ErrorInfo

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

        '  Initiate error handling
        '   activating error handling will trap errors like
        '   bad channel numbers and non-configured conditions.
        '   Parameters:
        '     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
        '     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents lblComment As System.Windows.Forms.Label
    Friend WithEvents btnOK As System.Windows.Forms.Button
    Friend WithEvents lbFileList As System.Windows.Forms.ListBox
    Friend WithEvents btnAllFiles As System.Windows.Forms.Button
    Friend WithEvents btnFileNumber As System.Windows.Forms.Button
    Friend WithEvents btnNextFile As System.Windows.Forms.Button
    Friend WithEvents btnFirstFile As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.lblComment = New System.Windows.Forms.Label()
        Me.btnOK = New System.Windows.Forms.Button()
        Me.lbFileList = New System.Windows.Forms.ListBox()
        Me.btnAllFiles = New System.Windows.Forms.Button()
        Me.btnFileNumber = New System.Windows.Forms.Button()
        Me.btnNextFile = New System.Windows.Forms.Button()
        Me.btnFirstFile = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'lblComment
        '
        Me.lblComment.Location = New System.Drawing.Point(16, 160)
        Me.lblComment.Name = "lblComment"
        Me.lblComment.Size = New System.Drawing.Size(424, 23)
        Me.lblComment.TabIndex = 13
        '
        'btnOK
        '
        Me.btnOK.Location = New System.Drawing.Point(360, 16)
        Me.btnOK.Name = "btnOK"
        Me.btnOK.TabIndex = 12
        Me.btnOK.Text = "OK"
        '
        'lbFileList
        '
        Me.lbFileList.Location = New System.Drawing.Point(104, 16)
        Me.lbFileList.Name = "lbFileList"
        Me.lbFileList.Size = New System.Drawing.Size(232, 121)
        Me.lbFileList.TabIndex = 11
        '
        'btnAllFiles
        '
        Me.btnAllFiles.Location = New System.Drawing.Point(8, 112)
        Me.btnAllFiles.Name = "btnAllFiles"
        Me.btnAllFiles.TabIndex = 10
        Me.btnAllFiles.Text = "All Files"
        '
        'btnFileNumber
        '
        Me.btnFileNumber.Location = New System.Drawing.Point(8, 80)
        Me.btnFileNumber.Name = "btnFileNumber"
        Me.btnFileNumber.TabIndex = 9
        Me.btnFileNumber.Text = "File Number"
        '
        'btnNextFile
        '
        Me.btnNextFile.Location = New System.Drawing.Point(8, 48)
        Me.btnNextFile.Name = "btnNextFile"
        Me.btnNextFile.TabIndex = 8
        Me.btnNextFile.Text = "Next File"
        '
        'btnFirstFile
        '
        Me.btnFirstFile.Location = New System.Drawing.Point(8, 16)
        Me.btnFirstFile.Name = "btnFirstFile"
        Me.btnFirstFile.TabIndex = 7
        Me.btnFirstFile.Text = "First File"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(448, 205)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblComment, Me.btnOK, Me.lbFileList, Me.btnAllFiles, Me.btnFileNumber, Me.btnNextFile, Me.btnFirstFile})
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub btnOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnOK.Click
        Close()
    End Sub

    Private Sub btnFirstFile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnFirstFile.Click
        Dim filename As String = New String(ChrW(&H20), MAX_PATH)
        Dim errorInfo As MccDaq.ErrorInfo


        lblComment.Text = "Get first file from directory " & m_Path

        '  Get the first file in the directory
        '   Parameters:
        '     MccDaq.GetFileOptions.GetFirst :first file
        '     m_Path						 :path to search
        '	  filename						 :receives name of file
        errorInfo = MccDaq.DataLogger.GetFileName(MccDaq.GetFileOptions.GetFirst, m_Path, filename)

        If (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            MessageBox.Show(errorInfo.Message)
        Else
            lbFileList.Items.Clear()
            lbFileList.Items.Add(filename)
        End If

    End Sub

    Private Sub btnNextFile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnNextFile.Click
        Dim filename As String = New String(ChrW(&H20), MAX_PATH)
        Dim errorInfo As MccDaq.ErrorInfo

        lblComment.Text = "Get next file from directory " + m_Path

        '  Get the next file in the directory
        '   Parameters:
        '     MccDaq.GetFileOptions.GetNext :next file
        '     m_Path						  :path to search
        '	   filename						  :receives name of file
        errorInfo = MccDaq.DataLogger.GetFileName(MccDaq.GetFileOptions.GetNext, m_Path, filename)

        If (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            MessageBox.Show(errorInfo.Message)
        Else
            lbFileList.Items.Add(filename)
        End If

    End Sub

    Private Sub btnFileNumber_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnFileNumber.Click
        Dim filename As String = New String(ChrW(&H20), MAX_PATH)
        Dim errorInfo As MccDaq.ErrorInfo

        lblComment.Text = "Get file number " & m_FileNumber & " from directory " & m_Path

        '  Get the Nth file in the directory
        '   Parameters:
        '     m_FileNumber					  :Nth file in the directory 
        '     m_Path						  :path to search
        '	   filename						  :receives name of file
        errorInfo = MccDaq.DataLogger.GetFileName(m_FileNumber, m_Path, filename)

        If (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            MessageBox.Show(errorInfo.Message)
        Else
            lbFileList.Items.Add(filename)
        End If

    End Sub

    Private Sub btnAllFiles_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnAllFiles.Click
        Dim filename As String = New String(ChrW(&H20), MAX_PATH)
        Dim errorInfo As MccDaq.ErrorInfo

        lblComment.Text = "Get all files from directory " + m_Path

        '  Get the first file in the directory
        '   Parameters:
        '     MccDaq.GetFileOptions.GetFirst :first file
        '     m_Path						  :path to search
        '	   filename						  :receives name of file
        errorInfo = MccDaq.DataLogger.GetFileName(MccDaq.GetFileOptions.GetFirst, m_Path, filename)

        If (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            MessageBox.Show(errorInfo.Message)
            Return
        Else
            lbFileList.Items.Clear()
            lbFileList.Items.Add(filename)
        End If

        While (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoMoreFiles)
            '  Get the next file in the directory
            '   Parameters:
            '     MccDaq.GetFileOptions.GetNext :next file
            '     m_Path						  :path to search
            '	   filename						  :receives name of file
            errorInfo = MccDaq.DataLogger.GetFileName(MccDaq.GetFileOptions.GetNext, m_Path, filename)

            If (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
                If (errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoMoreFiles) Then
                    MessageBox.Show(errorInfo.Message)
                    Return
                End If
            Else
                lbFileList.Items.Add(filename)
            End If
        End While

    End Sub
End Class
