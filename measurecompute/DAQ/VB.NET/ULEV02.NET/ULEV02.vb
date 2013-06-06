'==============================================================================


' File:                         ULEV02.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.EnableEvent with event types:
'                                           - MccDaq.EventType.OnScanError
'                                           - MccDaq.EventType.OnDataAvailable
'                                           - MccDaq.EventType.OnEndOfAiScan
'                               Mccdaq.MccBoard.DisableEvent()
'

' Purpose:                      Scans a single channel and displays the latest
'                               sample acquired every EventSize or more samples.
'                               Also updates the latest sample upon scan completion
'                               or end. Fatal errors such as Overrun errors, cause
'                               the scan to be aborted.

' Demonstration:                Shows how to enable and respond to events.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               Mccdaq.MccBoard.AInScan()
'
' Special Requirements:         Board 0 must support event handling and have
'                               paced analog inputs.
'
'==============================================================================
Option Strict Off
Option Explicit On 
Imports System.Runtime.InteropServices

<StructLayout(LayoutKind.Sequential)> _
Public Structure UserData
    Public ThisObj As Object
End Structure

Public Class frmEventDisplay
    Inherits System.Windows.Forms.Form

    Const Channel As Integer = 0        ' the channel to be sampled.
    Const NumPoints As Short = 1000     ' number of data points to collect
    Const Range As MccDaq.Range = MccDaq.Range.Bip5Volts ' gain for the channel sampled.
    Const SampleRate As Short = 1000    ' rate at which to sample each channel

    ' Data collection options
    Const Options As MccDaq.ScanOptions = MccDaq.ScanOptions.Background Or MccDaq.ScanOptions.ConvertData

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Dim ptrMyCallback, ptrOnErrorCallback As MccDaq.EventCallback

    Dim userData As userData
    Dim ptrUserData As IntPtr

    Dim Rate As Integer                 ' sample rate for acquiring data.
    Dim hDataBuffer As Integer          ' defines a variable to contain the handle for

    Dim WithEvents frmEventDisplay As System.Windows.Forms.Form

    ' This gets called by MyCallback in mycallback.vb for each MccDaq.EventType.OnDataAvailable and
    ' MccDaq.EventType.OnEndOfAiScan events. For these event types, the EventData supplied curresponds
    ' to the number of samples collected since the start of MccDaq.MccBoard.AInScan.
    Public Sub OnEvent(ByVal bd As Short, ByVal EventType As MccDaq.EventType, ByVal SampleCount As Long)
        Dim ULStat As MccDaq.ErrorInfo
        Dim SampleIndex As Long
        Dim Data(1) As Short
        Dim Value As Single

        ' Get the latest sample from the buffer and convert to volts
        SampleIndex = SampleCount - 1
        SampleIndex = SampleIndex Mod NumPoints
        ULStat = MccDaq.MccService.WinBufToArray(hDataBuffer, Data(0), SampleIndex, 1)
        ULStat = DaqBoard.ToEngUnits(Range, Data(0), Value)

        ' Update the display
        lblSampleCount.Text = (SampleCount).ToString()
        lblLatestSample.Text = Value.ToString("#0.0000") + "V"


        If (MccDaq.EventType.OnEndOfAiScan = EventType) Then
            ' Give the library a chance to clean up
            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)

            If (chkAutoRestart.CheckState = CheckState.Checked) Then
                ' Start a new scan
                Rate = SampleRate
                ULStat = DaqBoard.AInScan(Channel, Channel, NumPoints, Rate, Range, hDataBuffer, Options)
            Else
                ' Reset the status display
                lblStatus.Text = "IDLE"
            End If
        End If

    End Sub

    ' A scan error occurred; so, abort and reset the controls.
    Public Sub OnScanError(ByVal bd As Short, ByVal EventType As Integer, ByVal ErrorNo As Long)
        Dim ULStat As MccDaq.ErrorInfo

        ' We don't need to update the display here since that will happen during
        ' the MccDaq.EventType.OnEndOfAiScan and/or MccDaq.EventType.OnDataAvailable events to follow this event
        ' -- yes, this event is handled before any others and this event should be
        ' accompanied by a MccDaq.EventType.OnEndOfAiScan
        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)

        ' Reset the bAutoRestart such that the MccDaq.EventType.OnEndOfAiScan event does
        ' not automatically start a new scan
        chkAutoRestart.CheckState = System.Windows.Forms.CheckState.Unchecked


    End Sub

    Private Sub cmdDisableEvent_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdDisableEvent.Click
        Dim ULStat As MccDaq.ErrorInfo

        ' Disable and disconnect all event types with MccDaq.MccBoar.DisableEvent()
        '
        ' Since disabling events that were never enabled is harmless,
        ' we can disable all the events at once.
        '
        ' Parameters:
        '   MccDaq.EventType.AllEventTypes  :all event types will be disabled
        ULStat = DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes)


    End Sub

    Private Sub cmdEnableEvent_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdEnableEvent.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim EventSize As Integer ' Minimum number of samples to collect
        ' between MccDaq.EventType.OnDataAvailable events.

        Dim EventType As MccDaq.EventType ' Type of event to enable

        ' Enable and connect one or more event types to a single user callback
        ' function using MccDaq.MccBoard.EnableEvent().
        '
        ' If we want to attach a single callback function to more than one event
        ' type, we can do it in a single call to MccDaq.MccBoard.EnableEvent, or we can do this in
        ' separate calls for each event type. The main disadvantage of doing this in a
        ' single call is that if the call generates an error, we will not know which
        ' event type caused the error. In addition, the same error condition could
        ' generate multiple error messages.
        '
        ' Parameters:
        '   EventType   :the condition that will cause an event to fire
        '   EventSize   :only used for MccDaq.EventType.OnDataAvailable to determine how
        '                many samples to collect before firing an event
        '   AddressOf MyCallback  :the address of the user function or event handler
        '                          to call when above event type occurs.
        '                          Note that we can't provide the address of OnEvent directly
        '                          since Microsoft's calling convention for callback functions
        '                          requires that such functions be defined in a standard module
        '                          for Visual Basic. 'MyCallback' will forward the call to OnEvent.
        '   frmEventDisplay        :to make sure that this form handles the event that it set,
        '                          we supply a reference to it by name and dereference
        '                          it in the event handler. Note that the UserData type
        '                          in the event handler must match.



        userData.ThisObj = frmEventDisplay

        ptrUserData = Marshal.AllocCoTaskMem(Marshal.SizeOf(userData))
        Marshal.StructureToPtr(userData, ptrUserData, False)


        EventType = MccDaq.EventType.OnEndOfAiScan Or MccDaq.EventType.OnDataAvailable
        EventSize = Integer.Parse(txtEventSize.Text)
        ULStat = DaqBoard.EnableEvent(EventType, EventSize, ptrMyCallback, ptrUserData)
        If (ULStat.Value = MccDaq.ErrorInfo.ErrorCode.AlreadyActive) Then
            Exit Sub
        End If

        ' Since MccDaq.EventType.OnScanError event doesn't use the EventSize, we can set it to anything
        ' we choose without affecting the MccDaq.EventType.OnDataAvailable setting.
        EventType = MccDaq.EventType.OnScanError
        EventSize = 0
        ULStat = DaqBoard.EnableEvent(EventType, EventSize, ptrOnErrorCallback, ptrUserData)

    End Sub

    Private Sub cmdStart_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStart.Click
        Dim ULStat As MccDaq.ErrorInfo

        ' Collect the values with MccDaq.MccBoard.AInScan
        ' Parameters:
        '   Channel     :the channel of the scan
        '   NumPoints   :the total number of A/D samples to collect
        '   Rate        :sample rate
        '   Range       :the gain for the board
        '   hDataBuffer :the handle to the buffer to hold the data
        '   Options     :data collection options
        Rate = SampleRate

        ULStat = DaqBoard.AInScan(Channel, Channel, NumPoints, Rate, Range, hDataBuffer, Options)
        If (ULStat.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            lblStatus.Text = "RUNNING"
        Else
            Stop
        End If

    End Sub

    Private Sub cmdStop_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStop.Click
        Dim ULStat As MccDaq.ErrorInfo

        ' make sure we don't restart the scan MccDaq.EventType.OnEndOfAiScan
        chkAutoRestart.CheckState = System.Windows.Forms.CheckState.Unchecked

        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)


    End Sub

    Private Sub frmEventDisplay_Closed(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Closed
        Dim ULStat As MccDaq.ErrorInfo

        ' make sure to shut down
        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)

        ' disable any active events
        ULStat = DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes)

        ' and free the data buffer
        If (hDataBuffer <> 0) Then MccDaq.MccService.WinBufFree(hDataBuffer)
        hDataBuffer = 0

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
    Public WithEvents txtEventSize As System.Windows.Forms.TextBox
    Public WithEvents cmdStop As System.Windows.Forms.Button
    Public WithEvents chkAutoRestart As System.Windows.Forms.CheckBox
    Public WithEvents cmdStart As System.Windows.Forms.Button
    Public WithEvents cmdDisableEvent As System.Windows.Forms.Button
    Public WithEvents cmdEnableEvent As System.Windows.Forms.Button
    Public WithEvents Label4 As System.Windows.Forms.Label
    Public WithEvents Label3 As System.Windows.Forms.Label
    Public WithEvents Label2 As System.Windows.Forms.Label
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents lblLatestSample As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents lblSampleCount As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmEventDisplay))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.txtEventSize = New System.Windows.Forms.TextBox()
        Me.cmdStop = New System.Windows.Forms.Button()
        Me.chkAutoRestart = New System.Windows.Forms.CheckBox()
        Me.cmdStart = New System.Windows.Forms.Button()
        Me.cmdDisableEvent = New System.Windows.Forms.Button()
        Me.cmdEnableEvent = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.lblLatestSample = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me.lblSampleCount = New System.Windows.Forms.Label()
        Me.Text = "Universal Library ULEV02"
        Me.ClientSize = New System.Drawing.Size(380, 164)
        Me.Location = New System.Drawing.Point(4, 23)
        Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
        Me.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.BackColor = System.Drawing.SystemColors.Control
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
        Me.Name = "frmEventDisplay"
        Me.txtEventSize.AutoSize = False
        Me.txtEventSize.Size = New System.Drawing.Size(141, 21)
        Me.txtEventSize.Location = New System.Drawing.Point(222, 10)
        Me.txtEventSize.TabIndex = 12
        Me.txtEventSize.Text = "100"
        Me.txtEventSize.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtEventSize.AcceptsReturn = True
        Me.txtEventSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtEventSize.BackColor = System.Drawing.SystemColors.Window
        Me.txtEventSize.CausesValidation = True
        Me.txtEventSize.Enabled = True
        Me.txtEventSize.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtEventSize.HideSelection = True
        Me.txtEventSize.ReadOnly = False
        Me.txtEventSize.MaxLength = 0
        Me.txtEventSize.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtEventSize.Multiline = False
        Me.txtEventSize.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtEventSize.ScrollBars = System.Windows.Forms.ScrollBars.None
        Me.txtEventSize.TabStop = True
        Me.txtEventSize.Visible = True
        Me.txtEventSize.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.txtEventSize.Name = "txtEventSize"
        Me.cmdStop.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStop.Text = "Stop"
        Me.cmdStop.Size = New System.Drawing.Size(115, 33)
        Me.cmdStop.Location = New System.Drawing.Point(10, 120)
        Me.cmdStop.TabIndex = 7
        Me.cmdStop.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStop.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStop.CausesValidation = True
        Me.cmdStop.Enabled = True
        Me.cmdStop.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStop.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStop.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStop.TabStop = True
        Me.cmdStop.Name = "cmdStop"
        Me.chkAutoRestart.Text = "Auto Restart"
        Me.chkAutoRestart.Size = New System.Drawing.Size(95, 21)
        Me.chkAutoRestart.Location = New System.Drawing.Point(192, 116)
        Me.chkAutoRestart.TabIndex = 3
        Me.chkAutoRestart.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.chkAutoRestart.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.chkAutoRestart.BackColor = System.Drawing.SystemColors.Control
        Me.chkAutoRestart.CausesValidation = True
        Me.chkAutoRestart.Enabled = True
        Me.chkAutoRestart.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkAutoRestart.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkAutoRestart.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkAutoRestart.Appearance = System.Windows.Forms.Appearance.Normal
        Me.chkAutoRestart.TabStop = True
        Me.chkAutoRestart.CheckState = System.Windows.Forms.CheckState.Unchecked
        Me.chkAutoRestart.Visible = True
        Me.chkAutoRestart.Name = "chkAutoRestart"
        Me.cmdStart.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStart.Text = "Start"
        Me.cmdStart.Size = New System.Drawing.Size(115, 33)
        Me.cmdStart.Location = New System.Drawing.Point(10, 86)
        Me.cmdStart.TabIndex = 2
        Me.cmdStart.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStart.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStart.CausesValidation = True
        Me.cmdStart.Enabled = True
        Me.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStart.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStart.TabStop = True
        Me.cmdStart.Name = "cmdStart"
        Me.cmdDisableEvent.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdDisableEvent.Text = "DisableEvent"
        Me.cmdDisableEvent.Size = New System.Drawing.Size(115, 33)
        Me.cmdDisableEvent.Location = New System.Drawing.Point(10, 44)
        Me.cmdDisableEvent.TabIndex = 1
        Me.cmdDisableEvent.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdDisableEvent.BackColor = System.Drawing.SystemColors.Control
        Me.cmdDisableEvent.CausesValidation = True
        Me.cmdDisableEvent.Enabled = True
        Me.cmdDisableEvent.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdDisableEvent.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdDisableEvent.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdDisableEvent.TabStop = True
        Me.cmdDisableEvent.Name = "cmdDisableEvent"
        Me.cmdEnableEvent.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdEnableEvent.Text = "EnableEvent"
        Me.cmdEnableEvent.Size = New System.Drawing.Size(115, 33)
        Me.cmdEnableEvent.Location = New System.Drawing.Point(10, 10)
        Me.cmdEnableEvent.TabIndex = 0
        Me.cmdEnableEvent.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEnableEvent.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEnableEvent.CausesValidation = True
        Me.cmdEnableEvent.Enabled = True
        Me.cmdEnableEvent.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEnableEvent.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEnableEvent.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEnableEvent.TabStop = True
        Me.cmdEnableEvent.Name = "cmdEnableEvent"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.Label4.Text = "Event Size:"
        Me.Label4.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.Size = New System.Drawing.Size(89, 21)
        Me.Label4.Location = New System.Drawing.Point(130, 12)
        Me.Label4.TabIndex = 11
        Me.Label4.BackColor = System.Drawing.SystemColors.Control
        Me.Label4.Enabled = True
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label4.UseMnemonic = True
        Me.Label4.Visible = True
        Me.Label4.AutoSize = False
        Me.Label4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label4.Name = "Label4"
        Me.Label3.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.Label3.Text = "Latest Sample:"
        Me.Label3.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.Size = New System.Drawing.Size(89, 21)
        Me.Label3.Location = New System.Drawing.Point(130, 80)
        Me.Label3.TabIndex = 10
        Me.Label3.BackColor = System.Drawing.SystemColors.Control
        Me.Label3.Enabled = True
        Me.Label3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label3.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label3.UseMnemonic = True
        Me.Label3.Visible = True
        Me.Label3.AutoSize = False
        Me.Label3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label3.Name = "Label3"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.Label2.Text = "Total Count:"
        Me.Label2.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Size = New System.Drawing.Size(89, 21)
        Me.Label2.Location = New System.Drawing.Point(130, 58)
        Me.Label2.TabIndex = 9
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Enabled = True
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.UseMnemonic = True
        Me.Label2.Visible = True
        Me.Label2.AutoSize = False
        Me.Label2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label2.Name = "Label2"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.Label1.Text = "Status:"
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Size = New System.Drawing.Size(89, 21)
        Me.Label1.Location = New System.Drawing.Point(130, 35)
        Me.Label1.TabIndex = 8
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Enabled = True
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.UseMnemonic = True
        Me.Label1.Visible = True
        Me.Label1.AutoSize = False
        Me.Label1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label1.Name = "Label1"
        Me.lblLatestSample.Text = "NA"
        Me.lblLatestSample.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblLatestSample.ForeColor = System.Drawing.Color.Blue
        Me.lblLatestSample.Size = New System.Drawing.Size(141, 21)
        Me.lblLatestSample.Location = New System.Drawing.Point(222, 80)
        Me.lblLatestSample.TabIndex = 6
        Me.lblLatestSample.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblLatestSample.BackColor = System.Drawing.SystemColors.Control
        Me.lblLatestSample.Enabled = True
        Me.lblLatestSample.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblLatestSample.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblLatestSample.UseMnemonic = True
        Me.lblLatestSample.Visible = True
        Me.lblLatestSample.AutoSize = False
        Me.lblLatestSample.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblLatestSample.Name = "lblLatestSample"
        Me.lblStatus.Text = "IDLE"
        Me.lblStatus.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatus.ForeColor = System.Drawing.Color.Blue
        Me.lblStatus.Size = New System.Drawing.Size(141, 21)
        Me.lblStatus.Location = New System.Drawing.Point(222, 35)
        Me.lblStatus.TabIndex = 5
        Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblStatus.BackColor = System.Drawing.SystemColors.Control
        Me.lblStatus.Enabled = True
        Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatus.UseMnemonic = True
        Me.lblStatus.Visible = True
        Me.lblStatus.AutoSize = False
        Me.lblStatus.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblStatus.Name = "lblStatus"
        Me.lblSampleCount.Text = "0"
        Me.lblSampleCount.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblSampleCount.ForeColor = System.Drawing.Color.Blue
        Me.lblSampleCount.Size = New System.Drawing.Size(141, 21)
        Me.lblSampleCount.Location = New System.Drawing.Point(222, 58)
        Me.lblSampleCount.TabIndex = 4
        Me.lblSampleCount.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblSampleCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblSampleCount.Enabled = True
        Me.lblSampleCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblSampleCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblSampleCount.UseMnemonic = True
        Me.lblSampleCount.Visible = True
        Me.lblSampleCount.AutoSize = False
        Me.lblSampleCount.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblSampleCount.Name = "lblSampleCount"
        Me.Controls.Add(txtEventSize)
        Me.Controls.Add(cmdStop)
        Me.Controls.Add(chkAutoRestart)
        Me.Controls.Add(cmdStart)
        Me.Controls.Add(cmdDisableEvent)
        Me.Controls.Add(cmdEnableEvent)
        Me.Controls.Add(Label4)
        Me.Controls.Add(Label3)
        Me.Controls.Add(Label2)
        Me.Controls.Add(Label1)
        Me.Controls.Add(lblLatestSample)
        Me.Controls.Add(lblStatus)
        Me.Controls.Add(lblSampleCount)
    End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        frmEventDisplay = Me

        ptrMyCallback = New MccDaq.EventCallback(AddressOf MyCallback)
        ptrOnErrorCallback = New MccDaq.EventCallback(AddressOf OnErrorCallback)

        ' Initiate error handling
        '  activating error handling will trap errors like
        '  bad channel numbers and non-configured conditions.
        '  Parameters:
        '    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
        '    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop


        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)


        ' initialize MccDaq.MccBoard.AInScan parameters
        hDataBuffer = MccDaq.MccService.WinBufAlloc(NumPoints)
        If hDataBuffer = 0 Then End

        Rate = SampleRate


    End Sub
#End Region

End Class