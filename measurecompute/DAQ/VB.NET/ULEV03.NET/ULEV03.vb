'==============================================================================

' File:                         ULEV03

' Library Call Demonstrated:    Mccdaq.MccBoard.EnableEvent with event types:
'                                       - MccDaq.EventType.OnScanError
'                                       - MccDaq.EventType.OnDataAvailable
'                                       - MccDaq.EventType.OnEndOfAiScan
'                               Mccdaq.MccBoard.DisableEvent()
'                               Mccdaq.MccBoard.APretrig()

' Purpose:                      Scans a single channel with Mccdaq.MccBoard.APretrig() and sets
'                               digital outputs high upon first trigger event.
'                               Upon scan completion, it displays immediate points
'                               before and after the trigger. Fatal errors such as
'                               MccDaq.ErrorInfo.Overrun errors, cause the scan to be aborted, but 
'                               MccDaq.ErrorInfo.ErrorCode.TooFew
'                               errors are ignored.
'
' Demonstration:                Shows how to enable and respond to events.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               Mccdaq.MccBoard.DOut()

' Special Requirements:         Board 0 must support event handling, Mccdaq.MccBoard.APretrig(),
'                               and Mccdaq.MccBoard.DOut()
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
    Const NumPoints As Short = 5000 ' Number of data points to collect
    Const BUFFERSIZE As Short = 5512 ' Buffer needs to be big enough to hold NumPoints plus

    '   up to 1 full blocksize of data -- 512 is sufficient
    '   for most boards.
    Const PreCount As Short = 1000 ' Number of samples to acquire before the trigger
    Const SAMPLE_RATE As Short = 2000 ' Sample rate for acquiring data.
    Const Range As MccDaq.Range = MccDaq.Range.Bip5Volts ' Gain for the channel sampled.
    Const Options As MccDaq.ScanOptions = MccDaq.ScanOptions.Background ' Data collection options

    'Create a new MccBoard object for Board 0 
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Public lblPosttriggerData As System.Windows.Forms.Label()
    Public lblPretriggerData As System.Windows.Forms.Label()

    Dim WithEvents frmEventDisplay As System.Windows.Forms.Form

    Dim ptrMyCallback, ptrOnErrorCallback As MccDaq.EventCallback

    Dim userData As userData
    Dim ptrUserData As IntPtr


    Dim VarPreCount As Integer
    Dim TotalCount As Integer
    Dim SampleRate As Integer ' Sample rate for acquiring data.
    Dim hDataBuffer As Integer ' Defines a variable to contain the handle for
    '   memory allocated by Windows through MccDaq.MccService.WinBufAlloc()


    Dim Data(BUFFERSIZE) As Short
    Dim ChanTag(BUFFERSIZE) As Short
    Dim ActualPreCount As Long ' Actual number of samples acquired at time of trigger


    ' This gets called by MyCallback in mycallback.bas for each MccDaq.EventType.OnPretrigger and
    ' MccDaq.EventType.OnEndOfAiScan events. For the MccDaq.EventType.OnPretrigger event, the EventData supplied
    ' corresponds to the number of pretrigger samples available in the buffer. For the
    ' MccDaq.EventType.OnEndOfAiScan event, the EventData supplied corresponds to the number of samples
    ' aquired since the start of Mccdaq.MccBoard.APretrig().

    Public Sub OnEvent(ByVal bd As Short, ByVal EventType As MccDaq.EventType, ByVal SampleCount As Long)
        Dim ULStat As MccDaq.ErrorInfo
        Dim Value As Single
        Dim PreTriggerIndex As Integer
        Dim PostTriggerIndex As Integer
        Dim Offset As Integer

        If (MccDaq.EventType.OnPretrigger = EventType) Then

            ' store actual number of pre-trigger samples collected
            ActualPreCount = SampleCount
            lblPreCount.Text = SampleCount.ToString()

            ' signal external device that trigger has been detected
            ULStat = DaqBoard.DOut(MccDaq.DigitalPortType.FirstPortA, &HFF)

        ElseIf (MccDaq.EventType.OnEndOfAiScan = EventType) Then
            ' Give the library a chance to clean up
            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)
            lblStatus.Text = "IDLE"

            ' Get the data and align it so that oldest data is first
            ULStat = MccDaq.MccService.WinBufToArray(hDataBuffer, Data(0), 0, BUFFERSIZE - 1)
            ULStat = DaqBoard.AConvertPretrigData(VarPreCount, TotalCount, Data(0), ChanTag(0))

            ' Update the Pre- and Post- Trigger data displays
            For Offset = 0 To 9
                ' Determine the data index with respect to the trigger index
                PreTriggerIndex = VarPreCount - 10 + Offset
                PostTriggerIndex = VarPreCount + Offset

                ' Avoid indexing invalid pretrigger data
                If (10 - Offset < System.Convert.ToInt32(ActualPreCount)) Then
                    ULStat = DaqBoard.ToEngUnits(Range, Data(PreTriggerIndex), Value)
                    lblPretriggerData(Offset).Text = Value.ToString("#0.0000") + "V"
                Else ' this index doesn't point to valid data
                    lblPretriggerData(Offset).Text = "NA"
                End If

                ULStat = DaqBoard.ToEngUnits(Range, Data(PostTriggerIndex), Value)
                lblPosttriggerData(Offset).Text = Value.ToString("#0.0000") + "V"

            Next Offset


            If (chkAutoRestart.CheckState = CheckState.Checked) Then
                ' Start a new scan
                SampleRate = SAMPLE_RATE
                VarPreCount = PreCount
                TotalCount = NumPoints
                ULStat = DaqBoard.APretrig(Channel, Channel, VarPreCount, TotalCount, SampleRate, Range, hDataBuffer, Options)
                lblStatus.ForeColor = System.Drawing.ColorTranslator.FromOle(&HFF0000)
                lblStatus.Text = "RUNNING"
                lblPreCount.Text = "NA"
            End If

            ' Deassert external device signal
            ULStat = DaqBoard.DOut(MccDaq.DigitalPortType.FirstPortA, 0)

        End If

    End Sub

    ' A scan error occurred; if fatal(not TOOFEW), abort and reset the controls.
    Public Sub OnScanError(ByVal bd As Short, ByVal EventType As MccDaq.EventType, ByVal ErrorNo As Long)
        Dim ULStat As MccDaq.ErrorInfo

        ' We don't need to update the display here since that will happen during
        ' the MccDaq.EventType.OnEndOfAiScan  event to follow this event -- yes, this event is
        ' handled before any others, and if fatal, this event should be accompanied
        ' by an MccDaq.EventType.OnEndOfAiScan event.
        If (Convert.ToInt32(ErrorNo) <> MccDaq.ErrorInfo.ErrorCode.TooFew) Then
            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)

            ' Reset the chkAutoRestart such that the MccDaq.EventType.OnEndOfAiScan event does
            ' not automatically start a new scan
            chkAutoRestart.CheckState = System.Windows.Forms.CheckState.Unchecked

            lblStatus.ForeColor = System.Drawing.ColorTranslator.FromOle(&HFF)
            lblStatus.Text = "FATAL ERROR!"
        Else
            lblStatus.ForeColor = System.Drawing.ColorTranslator.FromOle(&HFF)
            lblStatus.Text = "TOOFEW"
        End If

    End Sub

    Private Sub cmdDisableEvent_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdDisableEvent.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim EventTypes As MccDaq.EventType

        ' we should stop any active scans before disabling events
        ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction)

        ' Disconnect and uninstall event handlers
        '   We can disable all the events at once, and disabling events
        '   that were never enabled is harmless
        '
        ' Parameters:
        '   EventTypes        : the event types which are being disabled.
        EventTypes = MccDaq.EventType.AllEventTypes
        ULStat = DaqBoard.DisableEvent(EventTypes)

    End Sub

    Private Sub cmdEnableEvent_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdEnableEvent.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim EventType As MccDaq.EventType ' Type of event to enable

        ' Install event handlers for event conditions.
        '   If we want to attach a single callback function to more than one event
        '   type, we can do it in a single call to MccDaq.MccBoard.EnableEvent, or we can do it in
        '   separate calls for each event type. A disadvantage of doing it in a
        '   single call is that if the call generates an error, we will not know which
        '   event type caused the error. In addition, the same error condition could
        '   generate multiple error messages.
        '
        ' Parameters:
        '    EventType = MccDaq.EventType.OnPretrigger+_    : Generate an event upon first trigger during 
        '                                                     Mccdaq.MccBoard.APretrig() scan
        '                MccDaq.EventType.OnEndOfAiScan  : Generate an event upon scan completion or end
        '
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

        EventType = MccDaq.EventType.OnPretrigger Or MccDaq.EventType.OnEndOfAiScan
        ULStat = DaqBoard.EnableEvent(EventType, 0, ptrMyCallback, ptrUserData)


        ' Since MccDaq.EventType.OnScanError event doesn't use the EventSize, we can set it to anything
        ' we choose without affecting the MccDaq.EventType.OnDataAvailable setting.
        DaqBoard.EnableEvent(MccDaq.EventType.OnScanError, 0, ptrOnErrorCallback, ptrUserData)
        If (ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            cmdEnableEvent.Enabled = True
        End If


    End Sub

    Private Sub cmdStart_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStart.Click
        Dim ULStat As MccDaq.ErrorInfo

        'start the scan
        ActualPreCount = 0
        VarPreCount = PreCount
        TotalCount = NumPoints
        SampleRate = SAMPLE_RATE

        ULStat = DaqBoard.APretrig(Channel, Channel, VarPreCount, TotalCount, SampleRate, Range, hDataBuffer, Options)
        If (ULStat.Value = MccDaq.ErrorInfo.ErrorCode.NoErrors) Then
            lblStatus.ForeColor = System.Drawing.ColorTranslator.FromOle(&HFF0000)
            lblStatus.Text = "RUNNING"
            lblPreCount.Text = "NA"
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

        ' and diable any active events
        ULStat = DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes)

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
    Public WithEvents chkAutoRestart As System.Windows.Forms.CheckBox
    Public WithEvents cmdStop As System.Windows.Forms.Button
    Public WithEvents cmdStart As System.Windows.Forms.Button
    Public WithEvents cmdDisableEvent As System.Windows.Forms.Button
    Public WithEvents cmdEnableEvent As System.Windows.Forms.Button
    Public WithEvents Label2 As System.Windows.Forms.Label
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents lblPreCount As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_9 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_8 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_7 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_6 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_5 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_4 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_3 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_2 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_1 As System.Windows.Forms.Label
    Public WithEvents _lblPosttriggerData_0 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_9 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_8 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_7 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_6 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_5 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_4 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_3 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_2 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_1 As System.Windows.Forms.Label
    Public WithEvents _lblPretriggerData_0 As System.Windows.Forms.Label
    Public WithEvents _lbl_19 As System.Windows.Forms.Label
    Public WithEvents _lbl_18 As System.Windows.Forms.Label
    Public WithEvents _lbl_17 As System.Windows.Forms.Label
    Public WithEvents _lbl_16 As System.Windows.Forms.Label
    Public WithEvents _lbl_15 As System.Windows.Forms.Label
    Public WithEvents _lbl_14 As System.Windows.Forms.Label
    Public WithEvents _lbl_13 As System.Windows.Forms.Label
    Public WithEvents _lbl_12 As System.Windows.Forms.Label
    Public WithEvents _lbl_11 As System.Windows.Forms.Label
    Public WithEvents _lbl_10 As System.Windows.Forms.Label
    Public WithEvents _lbl_9 As System.Windows.Forms.Label
    Public WithEvents _lbl_8 As System.Windows.Forms.Label
    Public WithEvents _lbl_7 As System.Windows.Forms.Label
    Public WithEvents _lbl_6 As System.Windows.Forms.Label
    Public WithEvents _lbl_5 As System.Windows.Forms.Label
    Public WithEvents _lbl_4 As System.Windows.Forms.Label
    Public WithEvents _lbl_3 As System.Windows.Forms.Label
    Public WithEvents _lbl_2 As System.Windows.Forms.Label
    Public WithEvents _lbl_1 As System.Windows.Forms.Label
    Public WithEvents _lbl_0 As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmEventDisplay))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.ToolTip1.Active = True
        Me.chkAutoRestart = New System.Windows.Forms.CheckBox()
        Me.cmdStop = New System.Windows.Forms.Button()
        Me.cmdStart = New System.Windows.Forms.Button()
        Me.cmdDisableEvent = New System.Windows.Forms.Button()
        Me.cmdEnableEvent = New System.Windows.Forms.Button()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.lblPreCount = New System.Windows.Forms.Label()
        Me.lblStatus = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_9 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_8 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_7 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_6 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_5 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_4 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_3 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_2 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_1 = New System.Windows.Forms.Label()
        Me._lblPosttriggerData_0 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_9 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_8 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_7 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_6 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_5 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_4 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_3 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_2 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_1 = New System.Windows.Forms.Label()
        Me._lblPretriggerData_0 = New System.Windows.Forms.Label()
        Me._lbl_19 = New System.Windows.Forms.Label()
        Me._lbl_18 = New System.Windows.Forms.Label()
        Me._lbl_17 = New System.Windows.Forms.Label()
        Me._lbl_16 = New System.Windows.Forms.Label()
        Me._lbl_15 = New System.Windows.Forms.Label()
        Me._lbl_14 = New System.Windows.Forms.Label()
        Me._lbl_13 = New System.Windows.Forms.Label()
        Me._lbl_12 = New System.Windows.Forms.Label()
        Me._lbl_11 = New System.Windows.Forms.Label()
        Me._lbl_10 = New System.Windows.Forms.Label()
        Me._lbl_9 = New System.Windows.Forms.Label()
        Me._lbl_8 = New System.Windows.Forms.Label()
        Me._lbl_7 = New System.Windows.Forms.Label()
        Me._lbl_6 = New System.Windows.Forms.Label()
        Me._lbl_5 = New System.Windows.Forms.Label()
        Me._lbl_4 = New System.Windows.Forms.Label()
        Me._lbl_3 = New System.Windows.Forms.Label()
        Me._lbl_2 = New System.Windows.Forms.Label()
        Me._lbl_1 = New System.Windows.Forms.Label()
        Me._lbl_0 = New System.Windows.Forms.Label()
        Me.Text = "Universal Library ULEV03"
        Me.ClientSize = New System.Drawing.Size(434, 242)
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
        Me.chkAutoRestart.Text = "Auto Restart"
        Me.chkAutoRestart.Size = New System.Drawing.Size(95, 21)
        Me.chkAutoRestart.Location = New System.Drawing.Point(22, 204)
        Me.chkAutoRestart.TabIndex = 4
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
        Me.cmdStop.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStop.Text = "Stop"
        Me.cmdStop.Size = New System.Drawing.Size(115, 33)
        Me.cmdStop.Location = New System.Drawing.Point(8, 108)
        Me.cmdStop.TabIndex = 3
        Me.cmdStop.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdStop.BackColor = System.Drawing.SystemColors.Control
        Me.cmdStop.CausesValidation = True
        Me.cmdStop.Enabled = True
        Me.cmdStop.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdStop.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdStop.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdStop.TabStop = True
        Me.cmdStop.Name = "cmdStop"
        Me.cmdStart.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdStart.Text = "Start"
        Me.cmdStart.Size = New System.Drawing.Size(115, 33)
        Me.cmdStart.Location = New System.Drawing.Point(8, 74)
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
        Me.cmdDisableEvent.Location = New System.Drawing.Point(8, 40)
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
        Me.cmdEnableEvent.Location = New System.Drawing.Point(8, 6)
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
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.Label2.Text = "PreCount"
        Me.Label2.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Size = New System.Drawing.Size(53, 13)
        Me.Label2.Location = New System.Drawing.Point(2, 176)
        Me.Label2.TabIndex = 48
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Enabled = True
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.UseMnemonic = True
        Me.Label2.Visible = True
        Me.Label2.AutoSize = True
        Me.Label2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label2.Name = "Label2"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight
        Me.Label1.Text = "Satus:"
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Size = New System.Drawing.Size(37, 13)
        Me.Label1.Location = New System.Drawing.Point(16, 149)
        Me.Label1.TabIndex = 47
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Enabled = True
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.UseMnemonic = True
        Me.Label1.Visible = True
        Me.Label1.AutoSize = True
        Me.Label1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label1.Name = "Label1"
        Me.lblPreCount.Text = "NA"
        Me.lblPreCount.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblPreCount.ForeColor = System.Drawing.Color.Blue
        Me.lblPreCount.Size = New System.Drawing.Size(77, 19)
        Me.lblPreCount.Location = New System.Drawing.Point(60, 172)
        Me.lblPreCount.TabIndex = 46
        Me.lblPreCount.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblPreCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblPreCount.Enabled = True
        Me.lblPreCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblPreCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblPreCount.UseMnemonic = True
        Me.lblPreCount.Visible = True
        Me.lblPreCount.AutoSize = False
        Me.lblPreCount.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblPreCount.Name = "lblPreCount"
        Me.lblStatus.Text = "IDLE"
        Me.lblStatus.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatus.ForeColor = System.Drawing.Color.Blue
        Me.lblStatus.Size = New System.Drawing.Size(77, 19)
        Me.lblStatus.Location = New System.Drawing.Point(60, 146)
        Me.lblStatus.TabIndex = 45
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
        Me._lblPosttriggerData_9.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_9.Location = New System.Drawing.Point(358, 215)
        Me._lblPosttriggerData_9.TabIndex = 44
        Me._lblPosttriggerData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_9.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_9.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_9.Enabled = True
        Me._lblPosttriggerData_9.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_9.UseMnemonic = True
        Me._lblPosttriggerData_9.Visible = True
        Me._lblPosttriggerData_9.AutoSize = False
        Me._lblPosttriggerData_9.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_9.Name = "_lblPosttriggerData_9"
        Me._lblPosttriggerData_8.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_8.Location = New System.Drawing.Point(358, 192)
        Me._lblPosttriggerData_8.TabIndex = 43
        Me._lblPosttriggerData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_8.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_8.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_8.Enabled = True
        Me._lblPosttriggerData_8.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_8.UseMnemonic = True
        Me._lblPosttriggerData_8.Visible = True
        Me._lblPosttriggerData_8.AutoSize = False
        Me._lblPosttriggerData_8.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_8.Name = "_lblPosttriggerData_8"
        Me._lblPosttriggerData_7.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_7.Location = New System.Drawing.Point(358, 169)
        Me._lblPosttriggerData_7.TabIndex = 42
        Me._lblPosttriggerData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_7.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_7.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_7.Enabled = True
        Me._lblPosttriggerData_7.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_7.UseMnemonic = True
        Me._lblPosttriggerData_7.Visible = True
        Me._lblPosttriggerData_7.AutoSize = False
        Me._lblPosttriggerData_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_7.Name = "_lblPosttriggerData_7"
        Me._lblPosttriggerData_6.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_6.Location = New System.Drawing.Point(358, 146)
        Me._lblPosttriggerData_6.TabIndex = 41
        Me._lblPosttriggerData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_6.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_6.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_6.Enabled = True
        Me._lblPosttriggerData_6.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_6.UseMnemonic = True
        Me._lblPosttriggerData_6.Visible = True
        Me._lblPosttriggerData_6.AutoSize = False
        Me._lblPosttriggerData_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_6.Name = "_lblPosttriggerData_6"
        Me._lblPosttriggerData_5.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_5.Location = New System.Drawing.Point(358, 122)
        Me._lblPosttriggerData_5.TabIndex = 40
        Me._lblPosttriggerData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_5.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_5.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_5.Enabled = True
        Me._lblPosttriggerData_5.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_5.UseMnemonic = True
        Me._lblPosttriggerData_5.Visible = True
        Me._lblPosttriggerData_5.AutoSize = False
        Me._lblPosttriggerData_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_5.Name = "_lblPosttriggerData_5"
        Me._lblPosttriggerData_4.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_4.Location = New System.Drawing.Point(358, 99)
        Me._lblPosttriggerData_4.TabIndex = 39
        Me._lblPosttriggerData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_4.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_4.Enabled = True
        Me._lblPosttriggerData_4.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_4.UseMnemonic = True
        Me._lblPosttriggerData_4.Visible = True
        Me._lblPosttriggerData_4.AutoSize = False
        Me._lblPosttriggerData_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_4.Name = "_lblPosttriggerData_4"
        Me._lblPosttriggerData_3.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_3.Location = New System.Drawing.Point(358, 76)
        Me._lblPosttriggerData_3.TabIndex = 38
        Me._lblPosttriggerData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_3.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_3.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_3.Enabled = True
        Me._lblPosttriggerData_3.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_3.UseMnemonic = True
        Me._lblPosttriggerData_3.Visible = True
        Me._lblPosttriggerData_3.AutoSize = False
        Me._lblPosttriggerData_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_3.Name = "_lblPosttriggerData_3"
        Me._lblPosttriggerData_2.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_2.Location = New System.Drawing.Point(358, 53)
        Me._lblPosttriggerData_2.TabIndex = 37
        Me._lblPosttriggerData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_2.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_2.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_2.Enabled = True
        Me._lblPosttriggerData_2.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_2.UseMnemonic = True
        Me._lblPosttriggerData_2.Visible = True
        Me._lblPosttriggerData_2.AutoSize = False
        Me._lblPosttriggerData_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_2.Name = "_lblPosttriggerData_2"
        Me._lblPosttriggerData_1.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_1.Location = New System.Drawing.Point(358, 30)
        Me._lblPosttriggerData_1.TabIndex = 36
        Me._lblPosttriggerData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_1.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_1.Enabled = True
        Me._lblPosttriggerData_1.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_1.UseMnemonic = True
        Me._lblPosttriggerData_1.Visible = True
        Me._lblPosttriggerData_1.AutoSize = False
        Me._lblPosttriggerData_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_1.Name = "_lblPosttriggerData_1"
        Me._lblPosttriggerData_0.Size = New System.Drawing.Size(63, 17)
        Me._lblPosttriggerData_0.Location = New System.Drawing.Point(358, 6)
        Me._lblPosttriggerData_0.TabIndex = 35
        Me._lblPosttriggerData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPosttriggerData_0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPosttriggerData_0.BackColor = System.Drawing.SystemColors.Control
        Me._lblPosttriggerData_0.Enabled = True
        Me._lblPosttriggerData_0.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPosttriggerData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPosttriggerData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPosttriggerData_0.UseMnemonic = True
        Me._lblPosttriggerData_0.Visible = True
        Me._lblPosttriggerData_0.AutoSize = False
        Me._lblPosttriggerData_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPosttriggerData_0.Name = "_lblPosttriggerData_0"
        Me._lblPretriggerData_9.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_9.Location = New System.Drawing.Point(208, 213)
        Me._lblPretriggerData_9.TabIndex = 34
        Me._lblPretriggerData_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_9.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_9.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_9.Enabled = True
        Me._lblPretriggerData_9.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_9.UseMnemonic = True
        Me._lblPretriggerData_9.Visible = True
        Me._lblPretriggerData_9.AutoSize = False
        Me._lblPretriggerData_9.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_9.Name = "_lblPretriggerData_9"
        Me._lblPretriggerData_8.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_8.Location = New System.Drawing.Point(208, 190)
        Me._lblPretriggerData_8.TabIndex = 33
        Me._lblPretriggerData_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_8.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_8.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_8.Enabled = True
        Me._lblPretriggerData_8.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_8.UseMnemonic = True
        Me._lblPretriggerData_8.Visible = True
        Me._lblPretriggerData_8.AutoSize = False
        Me._lblPretriggerData_8.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_8.Name = "_lblPretriggerData_8"
        Me._lblPretriggerData_7.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_7.Location = New System.Drawing.Point(208, 167)
        Me._lblPretriggerData_7.TabIndex = 32
        Me._lblPretriggerData_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_7.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_7.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_7.Enabled = True
        Me._lblPretriggerData_7.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_7.UseMnemonic = True
        Me._lblPretriggerData_7.Visible = True
        Me._lblPretriggerData_7.AutoSize = False
        Me._lblPretriggerData_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_7.Name = "_lblPretriggerData_7"
        Me._lblPretriggerData_6.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_6.Location = New System.Drawing.Point(208, 144)
        Me._lblPretriggerData_6.TabIndex = 31
        Me._lblPretriggerData_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_6.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_6.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_6.Enabled = True
        Me._lblPretriggerData_6.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_6.UseMnemonic = True
        Me._lblPretriggerData_6.Visible = True
        Me._lblPretriggerData_6.AutoSize = False
        Me._lblPretriggerData_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_6.Name = "_lblPretriggerData_6"
        Me._lblPretriggerData_5.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_5.Location = New System.Drawing.Point(208, 121)
        Me._lblPretriggerData_5.TabIndex = 30
        Me._lblPretriggerData_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_5.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_5.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_5.Enabled = True
        Me._lblPretriggerData_5.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_5.UseMnemonic = True
        Me._lblPretriggerData_5.Visible = True
        Me._lblPretriggerData_5.AutoSize = False
        Me._lblPretriggerData_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_5.Name = "_lblPretriggerData_5"
        Me._lblPretriggerData_4.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_4.Location = New System.Drawing.Point(208, 98)
        Me._lblPretriggerData_4.TabIndex = 29
        Me._lblPretriggerData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_4.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_4.Enabled = True
        Me._lblPretriggerData_4.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_4.UseMnemonic = True
        Me._lblPretriggerData_4.Visible = True
        Me._lblPretriggerData_4.AutoSize = False
        Me._lblPretriggerData_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_4.Name = "_lblPretriggerData_4"
        Me._lblPretriggerData_3.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_3.Location = New System.Drawing.Point(208, 75)
        Me._lblPretriggerData_3.TabIndex = 28
        Me._lblPretriggerData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_3.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_3.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_3.Enabled = True
        Me._lblPretriggerData_3.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_3.UseMnemonic = True
        Me._lblPretriggerData_3.Visible = True
        Me._lblPretriggerData_3.AutoSize = False
        Me._lblPretriggerData_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_3.Name = "_lblPretriggerData_3"
        Me._lblPretriggerData_2.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_2.Location = New System.Drawing.Point(208, 52)
        Me._lblPretriggerData_2.TabIndex = 27
        Me._lblPretriggerData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_2.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_2.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_2.Enabled = True
        Me._lblPretriggerData_2.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_2.UseMnemonic = True
        Me._lblPretriggerData_2.Visible = True
        Me._lblPretriggerData_2.AutoSize = False
        Me._lblPretriggerData_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_2.Name = "_lblPretriggerData_2"
        Me._lblPretriggerData_1.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_1.Location = New System.Drawing.Point(208, 29)
        Me._lblPretriggerData_1.TabIndex = 26
        Me._lblPretriggerData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_1.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_1.Enabled = True
        Me._lblPretriggerData_1.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_1.UseMnemonic = True
        Me._lblPretriggerData_1.Visible = True
        Me._lblPretriggerData_1.AutoSize = False
        Me._lblPretriggerData_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_1.Name = "_lblPretriggerData_1"
        Me._lblPretriggerData_0.Size = New System.Drawing.Size(61, 19)
        Me._lblPretriggerData_0.Location = New System.Drawing.Point(208, 5)
        Me._lblPretriggerData_0.TabIndex = 25
        Me._lblPretriggerData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lblPretriggerData_0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lblPretriggerData_0.BackColor = System.Drawing.SystemColors.Control
        Me._lblPretriggerData_0.Enabled = True
        Me._lblPretriggerData_0.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lblPretriggerData_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lblPretriggerData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lblPretriggerData_0.UseMnemonic = True
        Me._lblPretriggerData_0.Visible = True
        Me._lblPretriggerData_0.AutoSize = False
        Me._lblPretriggerData_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lblPretriggerData_0.Name = "_lblPretriggerData_0"
        Me._lbl_19.Text = "Trigger +9"
        Me._lbl_19.Size = New System.Drawing.Size(61, 17)
        Me._lbl_19.Location = New System.Drawing.Point(294, 215)
        Me._lbl_19.TabIndex = 24
        Me._lbl_19.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_19.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_19.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_19.Enabled = True
        Me._lbl_19.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_19.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_19.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_19.UseMnemonic = True
        Me._lbl_19.Visible = True
        Me._lbl_19.AutoSize = False
        Me._lbl_19.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_19.Name = "_lbl_19"
        Me._lbl_18.Text = "Trigger +8"
        Me._lbl_18.Size = New System.Drawing.Size(61, 17)
        Me._lbl_18.Location = New System.Drawing.Point(294, 192)
        Me._lbl_18.TabIndex = 23
        Me._lbl_18.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_18.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_18.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_18.Enabled = True
        Me._lbl_18.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_18.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_18.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_18.UseMnemonic = True
        Me._lbl_18.Visible = True
        Me._lbl_18.AutoSize = False
        Me._lbl_18.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_18.Name = "_lbl_18"
        Me._lbl_17.Text = "Trigger +7"
        Me._lbl_17.Size = New System.Drawing.Size(61, 17)
        Me._lbl_17.Location = New System.Drawing.Point(294, 169)
        Me._lbl_17.TabIndex = 22
        Me._lbl_17.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_17.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_17.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_17.Enabled = True
        Me._lbl_17.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_17.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_17.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_17.UseMnemonic = True
        Me._lbl_17.Visible = True
        Me._lbl_17.AutoSize = False
        Me._lbl_17.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_17.Name = "_lbl_17"
        Me._lbl_16.Text = "Trigger +6"
        Me._lbl_16.Size = New System.Drawing.Size(61, 17)
        Me._lbl_16.Location = New System.Drawing.Point(294, 146)
        Me._lbl_16.TabIndex = 21
        Me._lbl_16.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_16.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_16.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_16.Enabled = True
        Me._lbl_16.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_16.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_16.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_16.UseMnemonic = True
        Me._lbl_16.Visible = True
        Me._lbl_16.AutoSize = False
        Me._lbl_16.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_16.Name = "_lbl_16"
        Me._lbl_15.Text = "Trigger +5"
        Me._lbl_15.Size = New System.Drawing.Size(61, 17)
        Me._lbl_15.Location = New System.Drawing.Point(294, 122)
        Me._lbl_15.TabIndex = 20
        Me._lbl_15.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_15.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_15.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_15.Enabled = True
        Me._lbl_15.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_15.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_15.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_15.UseMnemonic = True
        Me._lbl_15.Visible = True
        Me._lbl_15.AutoSize = False
        Me._lbl_15.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_15.Name = "_lbl_15"
        Me._lbl_14.Text = "Trigger +4"
        Me._lbl_14.Size = New System.Drawing.Size(61, 17)
        Me._lbl_14.Location = New System.Drawing.Point(294, 99)
        Me._lbl_14.TabIndex = 19
        Me._lbl_14.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_14.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_14.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_14.Enabled = True
        Me._lbl_14.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_14.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_14.UseMnemonic = True
        Me._lbl_14.Visible = True
        Me._lbl_14.AutoSize = False
        Me._lbl_14.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_14.Name = "_lbl_14"
        Me._lbl_13.Text = "Trigger +3"
        Me._lbl_13.Size = New System.Drawing.Size(61, 17)
        Me._lbl_13.Location = New System.Drawing.Point(294, 76)
        Me._lbl_13.TabIndex = 18
        Me._lbl_13.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_13.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_13.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_13.Enabled = True
        Me._lbl_13.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_13.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_13.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_13.UseMnemonic = True
        Me._lbl_13.Visible = True
        Me._lbl_13.AutoSize = False
        Me._lbl_13.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_13.Name = "_lbl_13"
        Me._lbl_12.Text = "Trigger +2"
        Me._lbl_12.Size = New System.Drawing.Size(61, 17)
        Me._lbl_12.Location = New System.Drawing.Point(294, 53)
        Me._lbl_12.TabIndex = 17
        Me._lbl_12.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_12.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_12.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_12.Enabled = True
        Me._lbl_12.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_12.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_12.UseMnemonic = True
        Me._lbl_12.Visible = True
        Me._lbl_12.AutoSize = False
        Me._lbl_12.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_12.Name = "_lbl_12"
        Me._lbl_11.Text = "Trigger +1"
        Me._lbl_11.Size = New System.Drawing.Size(61, 17)
        Me._lbl_11.Location = New System.Drawing.Point(294, 30)
        Me._lbl_11.TabIndex = 16
        Me._lbl_11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_11.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_11.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_11.Enabled = True
        Me._lbl_11.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_11.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_11.UseMnemonic = True
        Me._lbl_11.Visible = True
        Me._lbl_11.AutoSize = False
        Me._lbl_11.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_11.Name = "_lbl_11"
        Me._lbl_10.Text = "Trigger +0"
        Me._lbl_10.Size = New System.Drawing.Size(61, 17)
        Me._lbl_10.Location = New System.Drawing.Point(294, 6)
        Me._lbl_10.TabIndex = 15
        Me._lbl_10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_10.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_10.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_10.Enabled = True
        Me._lbl_10.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_10.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_10.UseMnemonic = True
        Me._lbl_10.Visible = True
        Me._lbl_10.AutoSize = False
        Me._lbl_10.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_10.Name = "_lbl_10"
        Me._lbl_9.Text = "Trigger -1"
        Me._lbl_9.Size = New System.Drawing.Size(61, 17)
        Me._lbl_9.Location = New System.Drawing.Point(142, 214)
        Me._lbl_9.TabIndex = 14
        Me._lbl_9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_9.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_9.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_9.Enabled = True
        Me._lbl_9.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_9.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_9.UseMnemonic = True
        Me._lbl_9.Visible = True
        Me._lbl_9.AutoSize = False
        Me._lbl_9.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_9.Name = "_lbl_9"
        Me._lbl_8.Text = "Trigger -2"
        Me._lbl_8.Size = New System.Drawing.Size(61, 17)
        Me._lbl_8.Location = New System.Drawing.Point(142, 191)
        Me._lbl_8.TabIndex = 13
        Me._lbl_8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_8.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_8.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_8.Enabled = True
        Me._lbl_8.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_8.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_8.UseMnemonic = True
        Me._lbl_8.Visible = True
        Me._lbl_8.AutoSize = False
        Me._lbl_8.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_8.Name = "_lbl_8"
        Me._lbl_7.Text = "Trigger -3"
        Me._lbl_7.Size = New System.Drawing.Size(61, 17)
        Me._lbl_7.Location = New System.Drawing.Point(142, 168)
        Me._lbl_7.TabIndex = 12
        Me._lbl_7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_7.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_7.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_7.Enabled = True
        Me._lbl_7.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_7.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_7.UseMnemonic = True
        Me._lbl_7.Visible = True
        Me._lbl_7.AutoSize = False
        Me._lbl_7.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_7.Name = "_lbl_7"
        Me._lbl_6.Text = "Trigger -4"
        Me._lbl_6.Size = New System.Drawing.Size(61, 17)
        Me._lbl_6.Location = New System.Drawing.Point(142, 145)
        Me._lbl_6.TabIndex = 11
        Me._lbl_6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_6.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_6.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_6.Enabled = True
        Me._lbl_6.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_6.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_6.UseMnemonic = True
        Me._lbl_6.Visible = True
        Me._lbl_6.AutoSize = False
        Me._lbl_6.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_6.Name = "_lbl_6"
        Me._lbl_5.Text = "Trigger -5"
        Me._lbl_5.Size = New System.Drawing.Size(61, 17)
        Me._lbl_5.Location = New System.Drawing.Point(142, 122)
        Me._lbl_5.TabIndex = 10
        Me._lbl_5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_5.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_5.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_5.Enabled = True
        Me._lbl_5.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_5.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_5.UseMnemonic = True
        Me._lbl_5.Visible = True
        Me._lbl_5.AutoSize = False
        Me._lbl_5.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_5.Name = "_lbl_5"
        Me._lbl_4.Text = "Trigger -6"
        Me._lbl_4.Size = New System.Drawing.Size(61, 17)
        Me._lbl_4.Location = New System.Drawing.Point(142, 99)
        Me._lbl_4.TabIndex = 9
        Me._lbl_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_4.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_4.Enabled = True
        Me._lbl_4.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_4.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_4.UseMnemonic = True
        Me._lbl_4.Visible = True
        Me._lbl_4.AutoSize = False
        Me._lbl_4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_4.Name = "_lbl_4"
        Me._lbl_3.Text = "Trigger -7"
        Me._lbl_3.Size = New System.Drawing.Size(61, 17)
        Me._lbl_3.Location = New System.Drawing.Point(142, 76)
        Me._lbl_3.TabIndex = 8
        Me._lbl_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_3.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_3.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_3.Enabled = True
        Me._lbl_3.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_3.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_3.UseMnemonic = True
        Me._lbl_3.Visible = True
        Me._lbl_3.AutoSize = False
        Me._lbl_3.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_3.Name = "_lbl_3"
        Me._lbl_2.Text = "Trigger -8"
        Me._lbl_2.Size = New System.Drawing.Size(61, 17)
        Me._lbl_2.Location = New System.Drawing.Point(142, 53)
        Me._lbl_2.TabIndex = 7
        Me._lbl_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_2.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_2.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_2.Enabled = True
        Me._lbl_2.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_2.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_2.UseMnemonic = True
        Me._lbl_2.Visible = True
        Me._lbl_2.AutoSize = False
        Me._lbl_2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_2.Name = "_lbl_2"
        Me._lbl_1.Text = "Trigger -9"
        Me._lbl_1.Size = New System.Drawing.Size(61, 17)
        Me._lbl_1.Location = New System.Drawing.Point(142, 30)
        Me._lbl_1.TabIndex = 6
        Me._lbl_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_1.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_1.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_1.Enabled = True
        Me._lbl_1.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_1.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_1.UseMnemonic = True
        Me._lbl_1.Visible = True
        Me._lbl_1.AutoSize = False
        Me._lbl_1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_1.Name = "_lbl_1"
        Me._lbl_0.Text = "Trigger -10"
        Me._lbl_0.Size = New System.Drawing.Size(61, 17)
        Me._lbl_0.Location = New System.Drawing.Point(142, 6)
        Me._lbl_0.TabIndex = 5
        Me._lbl_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._lbl_0.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me._lbl_0.BackColor = System.Drawing.SystemColors.Control
        Me._lbl_0.Enabled = True
        Me._lbl_0.ForeColor = System.Drawing.SystemColors.ControlText
        Me._lbl_0.Cursor = System.Windows.Forms.Cursors.Default
        Me._lbl_0.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me._lbl_0.UseMnemonic = True
        Me._lbl_0.Visible = True
        Me._lbl_0.AutoSize = False
        Me._lbl_0.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me._lbl_0.Name = "_lbl_0"
        Me.Controls.Add(chkAutoRestart)
        Me.Controls.Add(cmdStop)
        Me.Controls.Add(cmdStart)
        Me.Controls.Add(cmdDisableEvent)
        Me.Controls.Add(cmdEnableEvent)
        Me.Controls.Add(Label2)
        Me.Controls.Add(Label1)
        Me.Controls.Add(lblPreCount)
        Me.Controls.Add(lblStatus)
        Me.Controls.Add(_lblPosttriggerData_9)
        Me.Controls.Add(_lblPosttriggerData_8)
        Me.Controls.Add(_lblPosttriggerData_7)
        Me.Controls.Add(_lblPosttriggerData_6)
        Me.Controls.Add(_lblPosttriggerData_5)
        Me.Controls.Add(_lblPosttriggerData_4)
        Me.Controls.Add(_lblPosttriggerData_3)
        Me.Controls.Add(_lblPosttriggerData_2)
        Me.Controls.Add(_lblPosttriggerData_1)
        Me.Controls.Add(_lblPosttriggerData_0)
        Me.Controls.Add(_lblPretriggerData_9)
        Me.Controls.Add(_lblPretriggerData_8)
        Me.Controls.Add(_lblPretriggerData_7)
        Me.Controls.Add(_lblPretriggerData_6)
        Me.Controls.Add(_lblPretriggerData_5)
        Me.Controls.Add(_lblPretriggerData_4)
        Me.Controls.Add(_lblPretriggerData_3)
        Me.Controls.Add(_lblPretriggerData_2)
        Me.Controls.Add(_lblPretriggerData_1)
        Me.Controls.Add(_lblPretriggerData_0)
        Me.Controls.Add(_lbl_19)
        Me.Controls.Add(_lbl_18)
        Me.Controls.Add(_lbl_17)
        Me.Controls.Add(_lbl_16)
        Me.Controls.Add(_lbl_15)
        Me.Controls.Add(_lbl_14)
        Me.Controls.Add(_lbl_13)
        Me.Controls.Add(_lbl_12)
        Me.Controls.Add(_lbl_11)
        Me.Controls.Add(_lbl_10)
        Me.Controls.Add(_lbl_9)
        Me.Controls.Add(_lbl_8)
        Me.Controls.Add(_lbl_7)
        Me.Controls.Add(_lbl_6)
        Me.Controls.Add(_lbl_5)
        Me.Controls.Add(_lbl_4)
        Me.Controls.Add(_lbl_3)
        Me.Controls.Add(_lbl_2)
        Me.Controls.Add(_lbl_1)
        Me.Controls.Add(_lbl_0)
    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        lblPosttriggerData = New System.Windows.Forms.Label(10) {}
        lblPretriggerData = New System.Windows.Forms.Label(10) {}

        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_9, 9)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_8, 8)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_7, 7)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_6, 6)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_5, 5)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_4, 4)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_3, 3)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_2, 2)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_1, 1)
        Me.lblPosttriggerData.SetValue(_lblPosttriggerData_0, 0)

        Me.lblPretriggerData.SetValue(_lblPretriggerData_9, 9)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_8, 8)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_7, 7)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_6, 6)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_5, 5)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_4, 4)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_3, 3)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_2, 2)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_1, 1)
        Me.lblPretriggerData.SetValue(_lblPretriggerData_0, 0)

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


        ' Prepare FIRSTPORTA for signalling external device
        ULStat = DaqBoard.DConfigPort(MccDaq.DigitalPortType.FirstPortA, MccDaq.DigitalPortDirection.DigitalOut)

        ' initialize MccDaq.MccBoard.AInScan parameters
        hDataBuffer = MccDaq.MccService.WinBufAlloc(BUFFERSIZE)
        SampleRate = SAMPLE_RATE


    End Sub
#End Region

End Class