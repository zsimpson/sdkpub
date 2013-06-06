'==============================================================================

' File:                         CInScan02.VB

' Library Call Demonstrated:    MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan() 

' Purpose:                       Scans a Counter Input in decrement mode and stores
'                                the sample data in an array.

' Demonstration:                Displays counts on counter 0.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               MccDaq.MccService.WinBufAlloc32()
'                               MccDaq.MccService.WinBufToArray32()
'                               MccDaq.MccService.WinBufFree()

' Special Requirements:         Board 0 must support counter scans.
'                               TTL signals on selected counter inputs.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmDataDisplay
    Inherits System.Windows.Forms.Form

    Const NumPoints As Integer = 100    ' Number of data points to collect
    Const FirstPoint As Integer = 0     ' set first element in buffer to transfer to array

    'Create a new MccBoard object for Board 0
  Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

  Private CounterData(NumPoints) As UInt32 ' dimension an array to hold the input values

  ' define a variable to contain the handle for memory allocated by Windows through
  ' MccDaq.MccService.WinBufAlloc() 
  Private MemHandle As Integer
  Private LastCtr As Integer

  Public lblCounterData As System.Windows.Forms.Label()


  Private Sub cmdStart_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStart.Click
    Dim i As Integer
    Dim ULStat As MccDaq.ErrorInfo
    Dim Rate As Integer
    Dim Count As Integer
    Dim FirstCtr As Integer
    Dim Options As MccDaq.ScanOptions

    Dim CounterNum As Integer
    Dim Mode As MccDaq.CounterMode
    Dim DebounceTime As MccDaq.CounterDebounceTime
    Dim DebounceMode As MccDaq.CounterDebounceMode
    Dim EdgeDetection As MccDaq.CounterEdgeDetection
    Dim TickSize As MccDaq.CounterTickSize
    Dim MapCounter As Integer

    FirstCtr = 0 ' first channel to acquire
    LastCtr = 0

    cmdStart.Enabled = False


    ' Setup Counter 0 for decrement mode mapped in from counter 1
    ' Parameters:
    '   BoardNum       :the number used by CB.CFG to describe this board
    '   CounterNum     :counter to set up
    '   Mode           :counter Mode
    '   DebounceTime   :debounce Time
    '   DebounceMode   :debounce Mode
    '   EdgeDetection  :determines whether the rising edge or falling edge is to be detected
    '   TickSize       :reserved.
    '   MapCounter     :mapped counter


    CounterNum = FirstCtr
    Mode = MccDaq.CounterMode.DecrementOn
    DebounceTime = MccDaq.CounterDebounceTime.DebounceNone
    DebounceMode = 0
    EdgeDetection = MccDaq.CounterEdgeDetection.FallingEdge
    TickSize = 0
    MapCounter = 1

    ULStat = DaqBoard.CConfigScan(CounterNum, Mode, DebounceTime, DebounceMode, EdgeDetection, TickSize, MapCounter)
    If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
      Stop
    End If


    ' Collect the values by calling MccDaq.MccBoard.CInScan function
    ' Parameters:
    '   FirstCtr   :the first counter of the scan
    '   LastCtr    :the last counter of the scan
    '   Count      :the total number of counter samples to collect
    '   Rate       :sample rate
    '   MemHandle  :Handle for Windows buffer to store data in
    '   Options    :data collection options


    Count = NumPoints ' total number of data points to collect
    Rate = 390 ' per channel sampling rate ((samples per second) per channel)
    Options = MccDaq.ScanOptions.Ctr32Bit

    If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

    ULStat = DaqBoard.CInScan(FirstCtr, LastCtr, Count, Rate, MemHandle, Options)

    If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors And _
       ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.FreeRunning Then
      Stop
    End If

    ' Transfer the data from the memory buffer set up by Windows to an array for use by Visual Basic

    ULStat = MccDaq.MccService.WinBufToArray32(MemHandle, CounterData(0), FirstPoint, Count)
    If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

    For i = 0 To 4
      lblCounterData(i).Text = CounterData(i).ToString("D")
    Next i

    cmdStart.Enabled = True

  End Sub

  Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click
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
  Public WithEvents cmdStopConvert As System.Windows.Forms.Button
  Public WithEvents cmdStart As System.Windows.Forms.Button
  Public WithEvents lblCounterData_4 As System.Windows.Forms.Label
  Public WithEvents lblCounterData_3 As System.Windows.Forms.Label
  Public WithEvents lblCounterData_2 As System.Windows.Forms.Label
  Public WithEvents lblCounterData_1 As System.Windows.Forms.Label
  Public WithEvents lblCounterData_0 As System.Windows.Forms.Label
  Public WithEvents lblChan0 As System.Windows.Forms.Label
  Public WithEvents lblDemoFunction As System.Windows.Forms.Label
  'NOTE: The following procedure is required by the Windows Form Designer
  'It can be modified using the Windows Form Designer.
  'Do not modify it using the code editor.
  Friend WithEvents lblNote As System.Windows.Forms.Label
  <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
    Me.components = New System.ComponentModel.Container()
    Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
    Me.cmdStopConvert = New System.Windows.Forms.Button()
    Me.cmdStart = New System.Windows.Forms.Button()
    Me.lblCounterData_4 = New System.Windows.Forms.Label()
    Me.lblCounterData_3 = New System.Windows.Forms.Label()
    Me.lblCounterData_2 = New System.Windows.Forms.Label()
    Me.lblCounterData_1 = New System.Windows.Forms.Label()
    Me.lblCounterData_0 = New System.Windows.Forms.Label()
    Me.lblChan0 = New System.Windows.Forms.Label()
    Me.lblDemoFunction = New System.Windows.Forms.Label()
    Me.lblNote = New System.Windows.Forms.Label()
    Me.SuspendLayout()
    '
    'cmdStopConvert
    '
    Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
    Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
    Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
    Me.cmdStopConvert.Location = New System.Drawing.Point(280, 232)
    Me.cmdStopConvert.Name = "cmdStopConvert"
    Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.cmdStopConvert.Size = New System.Drawing.Size(58, 26)
    Me.cmdStopConvert.TabIndex = 17
    Me.cmdStopConvert.Text = "Quit"
    '
    'cmdStart
    '
    Me.cmdStart.BackColor = System.Drawing.SystemColors.Control
    Me.cmdStart.Cursor = System.Windows.Forms.Cursors.Default
    Me.cmdStart.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText
    Me.cmdStart.Location = New System.Drawing.Point(208, 232)
    Me.cmdStart.Name = "cmdStart"
    Me.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.cmdStart.Size = New System.Drawing.Size(58, 26)
    Me.cmdStart.TabIndex = 18
    Me.cmdStart.Text = "Start"
    '
    'lblCounterData_4
    '
    Me.lblCounterData_4.BackColor = System.Drawing.SystemColors.Window
    Me.lblCounterData_4.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblCounterData_4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblCounterData_4.ForeColor = System.Drawing.Color.Blue
    Me.lblCounterData_4.Location = New System.Drawing.Point(136, 160)
    Me.lblCounterData_4.Name = "lblCounterData_4"
    Me.lblCounterData_4.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblCounterData_4.Size = New System.Drawing.Size(65, 17)
    Me.lblCounterData_4.TabIndex = 12
    Me.lblCounterData_4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
    '
    'lblCounterData_3
    '
    Me.lblCounterData_3.BackColor = System.Drawing.SystemColors.Window
    Me.lblCounterData_3.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblCounterData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblCounterData_3.ForeColor = System.Drawing.Color.Blue
    Me.lblCounterData_3.Location = New System.Drawing.Point(136, 136)
    Me.lblCounterData_3.Name = "lblCounterData_3"
    Me.lblCounterData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblCounterData_3.Size = New System.Drawing.Size(65, 17)
    Me.lblCounterData_3.TabIndex = 12
    Me.lblCounterData_3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
    '
    'lblCounterData_2
    '
    Me.lblCounterData_2.BackColor = System.Drawing.SystemColors.Window
    Me.lblCounterData_2.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblCounterData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblCounterData_2.ForeColor = System.Drawing.Color.Blue
    Me.lblCounterData_2.Location = New System.Drawing.Point(136, 112)
    Me.lblCounterData_2.Name = "lblCounterData_2"
    Me.lblCounterData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblCounterData_2.Size = New System.Drawing.Size(65, 17)
    Me.lblCounterData_2.TabIndex = 11
    Me.lblCounterData_2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
    '
    'lblCounterData_1
    '
    Me.lblCounterData_1.BackColor = System.Drawing.SystemColors.Window
    Me.lblCounterData_1.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblCounterData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblCounterData_1.ForeColor = System.Drawing.Color.Blue
    Me.lblCounterData_1.Location = New System.Drawing.Point(136, 88)
    Me.lblCounterData_1.Name = "lblCounterData_1"
    Me.lblCounterData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblCounterData_1.Size = New System.Drawing.Size(65, 17)
    Me.lblCounterData_1.TabIndex = 10
    Me.lblCounterData_1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
    '
    'lblCounterData_0
    '
    Me.lblCounterData_0.BackColor = System.Drawing.SystemColors.Window
    Me.lblCounterData_0.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblCounterData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblCounterData_0.ForeColor = System.Drawing.Color.Blue
    Me.lblCounterData_0.Location = New System.Drawing.Point(136, 64)
    Me.lblCounterData_0.Name = "lblCounterData_0"
    Me.lblCounterData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblCounterData_0.Size = New System.Drawing.Size(65, 17)
    Me.lblCounterData_0.TabIndex = 9
    Me.lblCounterData_0.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
    '
    'lblChan0
    '
    Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
    Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.25!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
    Me.lblChan0.Location = New System.Drawing.Point(136, 40)
    Me.lblChan0.Name = "lblChan0"
    Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblChan0.Size = New System.Drawing.Size(65, 17)
    Me.lblChan0.TabIndex = 1
    Me.lblChan0.Text = "Channel 0"
    '
    'lblDemoFunction
    '
    Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
    Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
    Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
    Me.lblDemoFunction.Location = New System.Drawing.Point(8, 8)
    Me.lblDemoFunction.Name = "lblDemoFunction"
    Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
    Me.lblDemoFunction.Size = New System.Drawing.Size(337, 24)
    Me.lblDemoFunction.TabIndex = 0
    Me.lblDemoFunction.Text = "Demonstration of  MccDaq.CConfigScan() and MccBoard.CInScan() "
    Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
    '
    'lblNote
    '
    Me.lblNote.Location = New System.Drawing.Point(8, 192)
    Me.lblNote.Name = "lblNote"
    Me.lblNote.Size = New System.Drawing.Size(328, 32)
    Me.lblNote.TabIndex = 19
    Me.lblNote.Text = "Note: Pulse source must be connected to the mapped counter in decrement mode"
    '
    'frmDataDisplay
    '
    Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
    Me.BackColor = System.Drawing.SystemColors.Window
    Me.ClientSize = New System.Drawing.Size(344, 269)
    Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.lblNote, Me.cmdStopConvert, Me.cmdStart, Me.lblCounterData_4, Me.lblCounterData_3, Me.lblCounterData_2, Me.lblCounterData_1, Me.lblCounterData_0, Me.lblChan0, Me.lblDemoFunction})
    Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
    Me.ForeColor = System.Drawing.Color.Blue
    Me.Location = New System.Drawing.Point(190, 108)
    Me.Name = "frmDataDisplay"
    Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
    Me.Text = "Universal Library Counter Input Scan"
    Me.ResumeLayout(False)

  End Sub
#End Region


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

  Private Sub InitUL()

    Dim ULStat As MccDaq.ErrorInfo

    Me.lblCounterData = New System.Windows.Forms.Label(5) {}

    Me.lblCounterData.SetValue(lblCounterData_4, 4)
    Me.lblCounterData.SetValue(lblCounterData_3, 3)
    Me.lblCounterData.SetValue(lblCounterData_2, 2)
    Me.lblCounterData.SetValue(lblCounterData_1, 1)
    Me.lblCounterData.SetValue(lblCounterData_0, 0)

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

    MemHandle = MccDaq.MccService.WinBufAlloc32(NumPoints) ' set aside memory to hold data
    If MemHandle = 0 Then Stop
  End Sub
#End Region

End Class