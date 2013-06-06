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
        '     MccDaq.GetFileOptions.GetFirst :first file
        '     m_Path						  :path to search
        '	   filename						  :receives name of file
        errorInfo = MccDaq.DataLogger.GetFileName(MccDaq.GetFileOptions.GetFirst, m_Path, filename)


		' create an instance of the data logger
        Dim logger As MccDaq.DataLogger = New MccDaq.DataLogger(filename)


        '  Set the preferences 
        '    Parameters
        '      timeFormat					  :specifies times are 12 or 24 hour format
        '      timeZone					  :specifies local time of GMT
        '      units						  :specifies Fahrenheit, Celsius, or Kelvin
        Dim timeFormat As MccDaq.TimeFormat = MccDaq.TimeFormat.TwelveHour
        Dim timeZone As MccDaq.TimeZone = MccDaq.TimeZone.Local
        Dim units As MccDaq.TempScale = MccDaq.TempScale.Fahrenheit
        logger.SetPreferences(timeFormat, timeZone, units)


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
        End If


        '  Get the ANALOG info for the first file in the directory
        '   Parameters:
        '     channelMask						:receives the channel mask to specify which channels were logged
        '     unitMask							:receives the unit mask to specify temp or raw data
        '	   aiChannelCount					:receives the number of AI chennels logged
        Dim channelMask As Integer = 0
        Dim unitMask As Integer = 0
        Dim aiChannelCount As Integer = 0
        Dim aiChannelData() As Single
        If (errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            errorInfo = logger.GetAIChannelCount(aiChannelCount)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                ReDim aiChannelData(sampleCount * aiChannelCount)
            End If
        End If

        '  Get the CJC info for the first file in the directory
        '   Parameters:
        '	   cjcChannelCount					:receives the number of CJC chennels logged
        Dim cjcChannelCount As Integer = 0
        Dim cjcChannelData() As Single
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetCJCInfo(cjcChannelCount)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                ReDim cjcChannelData(sampleCount * cjcChannelCount)
            End If
        End If

        '  Get the DIO info for the first file in the directory
        '   Parameters:
        '	   dioChannelCount					:receives the number of DIO chennels logged
        Dim dioChannelCount As Integer = 0
        Dim dioChannelData() As Integer
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.GetDIOInfo(dioChannelCount)
            If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                ReDim dioChannelData(sampleCount * dioChannelCount)
            End If
        End If

        '  Read the time tag information
        '   Parameters:
        '	   startSample						:first sample to read
        '	   sampleCount						:number of samples to read
        '      dateTags							:receives the date tag information
        '      timeTags							:receives the time tag information
        Dim startSample As Integer = 0
        Dim DateTags() As Integer
        Dim TimeTags() As Integer
        ReDim DateTags(sampleCount)
        ReDim TimeTags(sampleCount)
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.ReadTimeTags(startSample, sampleCount, DateTags, TimeTags)
        End If

        '  Read the Analog data
        '   Parameters:
        '	   startSample						:first sample to read
        '	   sampleCount						:number of samples to read
        '      aiChannelData					:receives the analog data
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.ReadAIChannels(startSample, sampleCount, aiChannelData)
        End If

        '  Read the CJC data
        '   Parameters:
        '	   startSample						:first sample to read
        '	   sampleCount						:number of samples to read
        '      cjcChannelData					:receives the cjc data
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.ReadCJCChannels(startSample, sampleCount, cjcChannelData)
        End If

        '  Read the DIO data
        '   Parameters:
        '	   startSample						:first sample to read
        '	   sampleCount						:number of samples to read
        '      dioChannelData					:receives the dio data
        If errorInfo.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            errorInfo = logger.ReadDIOChannels(startSample, sampleCount, dioChannelData)
        End If

        ' display the data in teh list box
        Dim displayStr As String
        Dim dateStr As String
        Dim timeStr As String
        Dim index As Integer

        Dim hour As Long
        Dim minute As Long
        Dim second As Long
        Dim month As Long
        Dim day As Long
        Dim year As Long
        Dim postfix As Long
        Dim postfixStr As String
        Dim i As Integer
        Dim j As Integer
        Dim lbDataStr As String

        For i = 0 To sampleCount - 1
            lbDataStr = ""

            month = (DateTags(i) / 256) And 255
            day = DateTags(i) And 255
            year = (DateTags(i) / 65536) And 65535

            hour = (TimeTags(i) / 65536) And 255
            minute = (TimeTags(i) / 256) And 255
            second = TimeTags(i) And 255

            postfix = (TimeTags(i) / 16777216) And 255
            If postfix = 0 Then
                postfixStr = " AM"
            ElseIf postfix = 1 Then
                postfixStr = " PM"
            Else
                postfixStr = ""
            End If

            lbDataStr = month & "/" & day & "/" & year & "   " & hour & ":" & minute & ":" & second & postfixStr

            index = i * aiChannelCount
            For j = 0 To aiChannelCount - 1
                lbDataStr = lbDataStr & "   " & aiChannelData!(index + j)
            Next j

            index = i * cjcChannelCount
            For j = 0 To cjcChannelCount - 1
                lbDataStr = lbDataStr & "   " & cjcChannelData!(index + j)
            Next j

            index = i * dioChannelCount
            For j = 0 To dioChannelCount - 1
                lbDataStr = lbDataStr & "   " & dioChannelData%(index + j)
            Next j

            lbData.Items.Add(lbDataStr)

        Next i


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
    Friend WithEvents btnOK As System.Windows.Forms.Button
    Friend WithEvents lbData As System.Windows.Forms.ListBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.btnOK = New System.Windows.Forms.Button()
        Me.lbData = New System.Windows.Forms.ListBox()
        Me.SuspendLayout()
        '
        'btnOK
        '
        Me.btnOK.Location = New System.Drawing.Point(443, 392)
        Me.btnOK.Name = "btnOK"
        Me.btnOK.TabIndex = 3
        Me.btnOK.Text = "OK"
        '
        'lbData
        '
        Me.lbData.Location = New System.Drawing.Point(8, 16)
        Me.lbData.Name = "lbData"
        Me.lbData.Size = New System.Drawing.Size(944, 355)
        Me.lbData.TabIndex = 2
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(960, 429)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.btnOK, Me.lbData})
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub btnOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnOK.Click
        End
    End Sub
End Class
