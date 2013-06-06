Public Class Form1
    Inherits System.Windows.Forms.Form

    Private Const MAX_PATH As Integer = 260
    Private Const m_Path As String = "c:\"

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        Dim filename As String = New String(ChrW(&H20), MAX_PATH)
        Dim errorInfo As MccDaq.ErrorInfo

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

        '  Initiate error handling
        '   activating error handling will trap errors like
        '   bad channel numbers and non-configured conditions.
        '   Parameters:
        '     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
        '     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
        errorInfo = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)


        '  Get the first file in the directory
        '   Parameters:
        '     MccDaq.GetFileOptions.GetFirst  :first file
        '     m_Path						  :path to search
        '	  filename						  :receives name of file
        errorInfo = MccDaq.DataLogger.GetFileName(MccDaq.GetFileOptions.GetFirst, m_Path, filename)


        ' create an instance of the data logger
        Dim logger As MccDaq.DataLogger = New MccDaq.DataLogger(filename)


        '  Get the file info for the first file in the directory
        '   Parameters:
        '     filename						  :file to retrieve information from
        '     version						  :receives the version of the file
        '	   size							  :receives the size of file
        Dim version As Integer = 0
        Dim size As Integer = 0
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetFileInfo(version, size)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                lblFilename.Text = filename
                lblFileVersion.Text = version.ToString()
                lblFileSize.Text = size.ToString()
            End If
        End If

        '  Get the sample info for the first file in the directory
        '   Parameters:
        '     sampleInterval					 :receives the sample interval (time between samples)
        '     sampleCount						 :receives the sample count
        '	   startDate						 :receives the start date
        '	   startTime						 :receives the start time
        Dim sampleInterval As Integer = 0
        Dim sampleCount As Integer = 0
        Dim startDate As Integer = 0
        Dim startTime As Integer = 0
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetSampleInfo(sampleInterval, sampleCount, startDate, startTime)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                lblSampleInterval.Text = sampleInterval.ToString()
                lblSampleCount.Text = sampleCount.ToString()

                Dim day As Integer = startDate And 255
                Dim month As Integer = (startDate / 256) And 255
                Dim year As Integer = (startDate / 65536) And 65535
                Dim dateStr As String = month.ToString() & "/" & day.ToString() & "/" & year.ToString()
                lblStartDate.Text = dateStr

                Dim postfix As String
                Dim val As Integer

                Dim hours As Integer = (startTime / 65536) And 255
                Dim minutes As Integer = (startTime / 256) And 255
                Dim seconds As Integer = startTime And 255

                postfix = (startTime / 16777216) And 255
                val = (startTime / 166777216) And 255
                If val = 0 Then
                    postfix = " AM"
                ElseIf val = 1 Then
                    postfix = " PM"
                ElseIf val = -1 Then
                    postfix = ""
                Else
                    postfix = ""
                End If

                Dim timeStr As String = hours.ToString() & ":" & minutes.ToString() & ":" & seconds.ToString() & ":" & postfix
                lblStartTime.Text = timeStr
            End If
        End If


        '  Get the ANALOG info for the first file in the directory
        '   Parameters:
        '     channelMask						:receives the channel mask to specify which channels were logged
        '     unitMask							:receives the unit mask to specify temp or raw data
        '	   aiChannelCount					:receives the number of AI chennels logged
        Dim channelMask As Integer = 0
        Dim unitMask As Integer = 0
        Dim aiChannelCount As Integer = 0
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetAIChannelCount(aiChannelCount)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                lblChannelMask.Text = "0x" + channelMask.ToString("x")
                lblUnitMask.Text = "0x" + unitMask.ToString("x")
                lblAIChannelCount.Text = aiChannelCount.ToString()
            End If
        End If




        '  Get the CJC info for the first file in the directory
        '   Parameters:
        '	   cjcChannelCount					:receives the number of CJC chennels logged
        Dim cjcChannelCount As Integer = 0
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetCJCInfo(cjcChannelCount)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                lblCJCChannelCount.Text = cjcChannelCount.ToString()
            End If
        End If


        '  Get the DIO info for the first file in the directory
        '   Parameters:
        '	   dioChannelCount					:receives the number of DIO chennels logged
        Dim dioChannelCount As Integer = 0
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetDIOInfo(dioChannelCount)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                lblDIOChannelCount.Text = dioChannelCount.ToString()
            End If
        End If

        If errorInfo.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            MessageBox.Show(errorInfo.Message)
            Return
        End If

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
    Friend WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents lblFilename As System.Windows.Forms.Label
    Friend WithEvents label3 As System.Windows.Forms.Label
    Friend WithEvents lblFileVersion As System.Windows.Forms.Label
    Friend WithEvents label5 As System.Windows.Forms.Label
    Friend WithEvents lblFileSize As System.Windows.Forms.Label
    Friend WithEvents label7 As System.Windows.Forms.Label
    Friend WithEvents lblSampleInterval As System.Windows.Forms.Label
    Friend WithEvents label9 As System.Windows.Forms.Label
    Friend WithEvents lblSampleCount As System.Windows.Forms.Label
    Friend WithEvents label11 As System.Windows.Forms.Label
    Friend WithEvents lblStartDate As System.Windows.Forms.Label
    Friend WithEvents label13 As System.Windows.Forms.Label
    Friend WithEvents lblStartTime As System.Windows.Forms.Label
    Friend WithEvents label15 As System.Windows.Forms.Label
    Friend WithEvents lblChannelMask As System.Windows.Forms.Label
    Friend WithEvents label17 As System.Windows.Forms.Label
    Friend WithEvents lblUnitMask As System.Windows.Forms.Label
    Friend WithEvents label19 As System.Windows.Forms.Label
    Friend WithEvents lblAIChannelCount As System.Windows.Forms.Label
    Friend WithEvents label21 As System.Windows.Forms.Label
    Friend WithEvents lblCJCChannelCount As System.Windows.Forms.Label
    Friend WithEvents label23 As System.Windows.Forms.Label
    Friend WithEvents lblDIOChannelCount As System.Windows.Forms.Label
    Friend WithEvents label25 As System.Windows.Forms.Label
    Friend WithEvents label26 As System.Windows.Forms.Label
    Friend WithEvents label27 As System.Windows.Forms.Label
    Friend WithEvents label28 As System.Windows.Forms.Label
    Friend WithEvents label29 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.label29 = New System.Windows.Forms.Label()
        Me.label28 = New System.Windows.Forms.Label()
        Me.label27 = New System.Windows.Forms.Label()
        Me.label26 = New System.Windows.Forms.Label()
        Me.label25 = New System.Windows.Forms.Label()
        Me.btnOK = New System.Windows.Forms.Button()
        Me.lblDIOChannelCount = New System.Windows.Forms.Label()
        Me.label23 = New System.Windows.Forms.Label()
        Me.lblCJCChannelCount = New System.Windows.Forms.Label()
        Me.label21 = New System.Windows.Forms.Label()
        Me.lblAIChannelCount = New System.Windows.Forms.Label()
        Me.label19 = New System.Windows.Forms.Label()
        Me.lblUnitMask = New System.Windows.Forms.Label()
        Me.label17 = New System.Windows.Forms.Label()
        Me.lblChannelMask = New System.Windows.Forms.Label()
        Me.label15 = New System.Windows.Forms.Label()
        Me.lblStartTime = New System.Windows.Forms.Label()
        Me.label13 = New System.Windows.Forms.Label()
        Me.lblStartDate = New System.Windows.Forms.Label()
        Me.label11 = New System.Windows.Forms.Label()
        Me.lblSampleCount = New System.Windows.Forms.Label()
        Me.label9 = New System.Windows.Forms.Label()
        Me.lblSampleInterval = New System.Windows.Forms.Label()
        Me.label7 = New System.Windows.Forms.Label()
        Me.lblFileSize = New System.Windows.Forms.Label()
        Me.label5 = New System.Windows.Forms.Label()
        Me.lblFileVersion = New System.Windows.Forms.Label()
        Me.label3 = New System.Windows.Forms.Label()
        Me.lblFilename = New System.Windows.Forms.Label()
        Me.label1 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'label29
        '
        Me.label29.Location = New System.Drawing.Point(8, 472)
        Me.label29.Name = "label29"
        Me.label29.Size = New System.Drawing.Size(128, 23)
        Me.label29.TabIndex = 84
        Me.label29.Text = "Results of cbGetDIOInfo"
        '
        'label28
        '
        Me.label28.Location = New System.Drawing.Point(8, 400)
        Me.label28.Name = "label28"
        Me.label28.Size = New System.Drawing.Size(136, 23)
        Me.label28.TabIndex = 83
        Me.label28.Text = "Results of cbGetCJCInfo"
        '
        'label27
        '
        Me.label27.Location = New System.Drawing.Point(8, 280)
        Me.label27.Name = "label27"
        Me.label27.Size = New System.Drawing.Size(128, 23)
        Me.label27.TabIndex = 82
        Me.label27.Text = "Results of cbGetAIInfo"
        '
        'label26
        '
        Me.label26.Location = New System.Drawing.Point(8, 136)
        Me.label26.Name = "label26"
        Me.label26.Size = New System.Drawing.Size(160, 23)
        Me.label26.TabIndex = 81
        Me.label26.Text = "Results of cbGetSampleInfo"
        '
        'label25
        '
        Me.label25.Location = New System.Drawing.Point(8, 16)
        Me.label25.Name = "label25"
        Me.label25.Size = New System.Drawing.Size(136, 23)
        Me.label25.TabIndex = 80
        Me.label25.Text = "Results of cbGetFileInfo"
        '
        'btnOK
        '
        Me.btnOK.Location = New System.Drawing.Point(144, 544)
        Me.btnOK.Name = "btnOK"
        Me.btnOK.TabIndex = 79
        Me.btnOK.Text = "OK"
        '
        'lblDIOChannelCount
        '
        Me.lblDIOChannelCount.Location = New System.Drawing.Point(184, 504)
        Me.lblDIOChannelCount.Name = "lblDIOChannelCount"
        Me.lblDIOChannelCount.Size = New System.Drawing.Size(160, 23)
        Me.lblDIOChannelCount.TabIndex = 78
        Me.lblDIOChannelCount.Text = "label24"
        '
        'label23
        '
        Me.label23.Location = New System.Drawing.Point(40, 504)
        Me.label23.Name = "label23"
        Me.label23.Size = New System.Drawing.Size(104, 23)
        Me.label23.TabIndex = 77
        Me.label23.Text = "DIO channel count:"
        '
        'lblCJCChannelCount
        '
        Me.lblCJCChannelCount.Location = New System.Drawing.Point(184, 432)
        Me.lblCJCChannelCount.Name = "lblCJCChannelCount"
        Me.lblCJCChannelCount.Size = New System.Drawing.Size(160, 23)
        Me.lblCJCChannelCount.TabIndex = 76
        Me.lblCJCChannelCount.Text = "label22"
        '
        'label21
        '
        Me.label21.Location = New System.Drawing.Point(40, 432)
        Me.label21.Name = "label21"
        Me.label21.Size = New System.Drawing.Size(104, 23)
        Me.label21.TabIndex = 75
        Me.label21.Text = "CJC channel count:"
        '
        'lblAIChannelCount
        '
        Me.lblAIChannelCount.Location = New System.Drawing.Point(184, 360)
        Me.lblAIChannelCount.Name = "lblAIChannelCount"
        Me.lblAIChannelCount.Size = New System.Drawing.Size(160, 23)
        Me.lblAIChannelCount.TabIndex = 74
        Me.lblAIChannelCount.Text = "label20"
        '
        'label19
        '
        Me.label19.Location = New System.Drawing.Point(40, 360)
        Me.label19.Name = "label19"
        Me.label19.Size = New System.Drawing.Size(104, 23)
        Me.label19.TabIndex = 73
        Me.label19.Text = "AI channel count:"
        '
        'lblUnitMask
        '
        Me.lblUnitMask.Location = New System.Drawing.Point(184, 336)
        Me.lblUnitMask.Name = "lblUnitMask"
        Me.lblUnitMask.Size = New System.Drawing.Size(160, 23)
        Me.lblUnitMask.TabIndex = 72
        Me.lblUnitMask.Text = "label18"
        '
        'label17
        '
        Me.label17.Location = New System.Drawing.Point(40, 336)
        Me.label17.Name = "label17"
        Me.label17.Size = New System.Drawing.Size(104, 23)
        Me.label17.TabIndex = 71
        Me.label17.Text = "Unit mask:"
        '
        'lblChannelMask
        '
        Me.lblChannelMask.Location = New System.Drawing.Point(184, 312)
        Me.lblChannelMask.Name = "lblChannelMask"
        Me.lblChannelMask.Size = New System.Drawing.Size(160, 23)
        Me.lblChannelMask.TabIndex = 70
        Me.lblChannelMask.Text = "label16"
        '
        'label15
        '
        Me.label15.Location = New System.Drawing.Point(40, 312)
        Me.label15.Name = "label15"
        Me.label15.Size = New System.Drawing.Size(104, 23)
        Me.label15.TabIndex = 69
        Me.label15.Text = "Channel mask:"
        '
        'lblStartTime
        '
        Me.lblStartTime.Location = New System.Drawing.Point(184, 240)
        Me.lblStartTime.Name = "lblStartTime"
        Me.lblStartTime.Size = New System.Drawing.Size(160, 23)
        Me.lblStartTime.TabIndex = 68
        Me.lblStartTime.Text = "label14"
        '
        'label13
        '
        Me.label13.Location = New System.Drawing.Point(40, 240)
        Me.label13.Name = "label13"
        Me.label13.Size = New System.Drawing.Size(104, 23)
        Me.label13.TabIndex = 67
        Me.label13.Text = "Start time:"
        '
        'lblStartDate
        '
        Me.lblStartDate.Location = New System.Drawing.Point(184, 216)
        Me.lblStartDate.Name = "lblStartDate"
        Me.lblStartDate.Size = New System.Drawing.Size(160, 23)
        Me.lblStartDate.TabIndex = 66
        Me.lblStartDate.Text = "label12"
        '
        'label11
        '
        Me.label11.Location = New System.Drawing.Point(40, 216)
        Me.label11.Name = "label11"
        Me.label11.Size = New System.Drawing.Size(104, 23)
        Me.label11.TabIndex = 65
        Me.label11.Text = "Start date:"
        '
        'lblSampleCount
        '
        Me.lblSampleCount.Location = New System.Drawing.Point(184, 192)
        Me.lblSampleCount.Name = "lblSampleCount"
        Me.lblSampleCount.Size = New System.Drawing.Size(160, 23)
        Me.lblSampleCount.TabIndex = 64
        Me.lblSampleCount.Text = "label10"
        '
        'label9
        '
        Me.label9.Location = New System.Drawing.Point(40, 192)
        Me.label9.Name = "label9"
        Me.label9.Size = New System.Drawing.Size(104, 23)
        Me.label9.TabIndex = 63
        Me.label9.Text = "Sample count:"
        '
        'lblSampleInterval
        '
        Me.lblSampleInterval.Location = New System.Drawing.Point(184, 168)
        Me.lblSampleInterval.Name = "lblSampleInterval"
        Me.lblSampleInterval.Size = New System.Drawing.Size(160, 23)
        Me.lblSampleInterval.TabIndex = 62
        Me.lblSampleInterval.Text = "label8"
        '
        'label7
        '
        Me.label7.Location = New System.Drawing.Point(40, 168)
        Me.label7.Name = "label7"
        Me.label7.Size = New System.Drawing.Size(104, 23)
        Me.label7.TabIndex = 61
        Me.label7.Text = "Sample interval:"
        '
        'lblFileSize
        '
        Me.lblFileSize.Location = New System.Drawing.Point(184, 96)
        Me.lblFileSize.Name = "lblFileSize"
        Me.lblFileSize.Size = New System.Drawing.Size(160, 23)
        Me.lblFileSize.TabIndex = 60
        Me.lblFileSize.Text = "label6"
        '
        'label5
        '
        Me.label5.Location = New System.Drawing.Point(40, 96)
        Me.label5.Name = "label5"
        Me.label5.Size = New System.Drawing.Size(104, 23)
        Me.label5.TabIndex = 59
        Me.label5.Text = "File size:"
        '
        'lblFileVersion
        '
        Me.lblFileVersion.Location = New System.Drawing.Point(184, 72)
        Me.lblFileVersion.Name = "lblFileVersion"
        Me.lblFileVersion.Size = New System.Drawing.Size(160, 23)
        Me.lblFileVersion.TabIndex = 58
        Me.lblFileVersion.Text = "label4"
        '
        'label3
        '
        Me.label3.Location = New System.Drawing.Point(40, 72)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(104, 23)
        Me.label3.TabIndex = 57
        Me.label3.Text = "File version:"
        '
        'lblFilename
        '
        Me.lblFilename.Location = New System.Drawing.Point(184, 48)
        Me.lblFilename.Name = "lblFilename"
        Me.lblFilename.Size = New System.Drawing.Size(160, 23)
        Me.lblFilename.TabIndex = 56
        Me.lblFilename.Text = "label2"
        '
        'label1
        '
        Me.label1.Location = New System.Drawing.Point(40, 48)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(104, 23)
        Me.label1.TabIndex = 55
        Me.label1.Text = "Filename:"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(376, 589)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.label29, Me.label28, Me.label27, Me.label26, Me.label25, Me.btnOK, Me.lblDIOChannelCount, Me.label23, Me.lblCJCChannelCount, Me.label21, Me.lblAIChannelCount, Me.label19, Me.lblUnitMask, Me.label17, Me.lblChannelMask, Me.label15, Me.lblStartTime, Me.label13, Me.lblStartDate, Me.label11, Me.lblSampleCount, Me.label9, Me.lblSampleInterval, Me.label7, Me.lblFileSize, Me.label5, Me.lblFileVersion, Me.label3, Me.lblFilename, Me.label1})
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

#End Region


    Private Sub btnOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnOK.Click
        End
    End Sub
    Friend WithEvents btnOK As System.Windows.Forms.Button
End Class
