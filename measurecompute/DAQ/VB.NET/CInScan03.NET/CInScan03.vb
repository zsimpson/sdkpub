'==============================================================================

' File:                         CInScan03.VB

' Library Call Demonstrated:    MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan() 

' Purpose:                      Scans a Counter Input in encoder mode and stores
'                               the sample data in an array.

' Demonstration:                Displays counts from encoder as phase A, phase B,
'                               and totalizes the index on Z.

' Other Library Calls:          MccDaq.MccService.ErrHandling()
'                               MccDaq.MccService.WinBufAlloc32()
'                               MccDaq.MccService.WinBufToArray32()
'                               MccDaq.MccService.WinBufFree()

' Special Requirements:         Board 0 must support counter scans in encoder mode.
'                               Phase A from encode connected to counter 0 input.
'                               Phase B from encode connected to counter 1 input.
'                               Index Z from encode connected to counter 2 input.

'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmDataDisplay

   Inherits System.Windows.Forms.Form

  Const NumPoints As Integer = 50  ' Number of data points to collect
   Const FirstPoint As Integer = 0  ' set first element in buffer to transfer to array

   'Create a new MccBoard object for Board 0
   Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

   Private CounterData(NumPoints) As UInt32 ' dimension an array to hold the input values

   ' define a variable to contain the handle for memory allocated by Windows through
   ' MccDaq.MccService.WinBufAlloc32() 
   Private MemHandle As Integer

   Public lblCounterData As System.Windows.Forms.Label()

   Private Sub cmdStart_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStart.Click

      Dim ULStat As MccDaq.ErrorInfo
      Dim Rate As Integer
      Dim Count As Integer
      Dim FirstCtr As Integer
      Dim LastCtr As Integer
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

    ' Counter 0
      CounterNum = FirstCtr
      Mode = MccDaq.CounterMode.Encoder Or MccDaq.CounterMode.EncoderModeX1 Or MccDaq.CounterMode.ClearOnZOn
      DebounceTime = MccDaq.CounterDebounceTime.DebounceNone
      DebounceMode = 0
      EdgeDetection = MccDaq.CounterEdgeDetection.RisingEdge
      TickSize = 0
      MapCounter = 2

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
      Rate = 10 ' per channel sampling rate ((samples per second) per channel)
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
      Dim Element As Long

      Me.txtEncoderValues.Text = " Counter Data" & vbCrLf & vbCrLf
      For Element = 0 To NumPoints - 1
        Me.txtEncoderValues.Text = Me.txtEncoderValues.Text & _
          CounterData(Element).ToString("D").PadLeft(6) & vbCrLf
      Next

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
   'NOTE: The following procedure is required by the Windows Form Designer
   'It can be modified using the Windows Form Designer.
   'Do not modify it using the code editor.
   Public WithEvents Label1 As System.Windows.Forms.Label
   Friend WithEvents txtEncoderValues As System.Windows.Forms.TextBox
   <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
      Me.components = New System.ComponentModel.Container
      Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
      Me.cmdStopConvert = New System.Windows.Forms.Button
      Me.cmdStart = New System.Windows.Forms.Button
      Me.Label1 = New System.Windows.Forms.Label
      Me.txtEncoderValues = New System.Windows.Forms.TextBox
      Me.SuspendLayout()
      '
      'cmdStopConvert
      '
      Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
      Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
      Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
      Me.cmdStopConvert.Location = New System.Drawing.Point(304, 368)
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
      Me.cmdStart.Location = New System.Drawing.Point(232, 368)
      Me.cmdStart.Name = "cmdStart"
      Me.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.cmdStart.Size = New System.Drawing.Size(58, 26)
      Me.cmdStart.TabIndex = 18
      Me.cmdStart.Text = "Start"
      '
      'Label1
      '
      Me.Label1.BackColor = System.Drawing.SystemColors.Window
      Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
      Me.Label1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label1.ForeColor = System.Drawing.SystemColors.WindowText
      Me.Label1.Location = New System.Drawing.Point(16, 8)
      Me.Label1.Name = "Label1"
      Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.Label1.Size = New System.Drawing.Size(352, 40)
      Me.Label1.TabIndex = 44
      Me.Label1.Text = "Demonstration of MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan() used with enc" & _
      "oders"
      Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopCenter
      '
      'txtEncoderValues
      '
      Me.txtEncoderValues.Font = New System.Drawing.Font("Courier New", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.txtEncoderValues.ForeColor = System.Drawing.Color.FromArgb(CType(0, Byte), CType(0, Byte), CType(192, Byte))
      Me.txtEncoderValues.Location = New System.Drawing.Point(16, 56)
      Me.txtEncoderValues.Multiline = True
      Me.txtEncoderValues.Name = "txtEncoderValues"
      Me.txtEncoderValues.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
      Me.txtEncoderValues.Size = New System.Drawing.Size(352, 304)
      Me.txtEncoderValues.TabIndex = 45
      Me.txtEncoderValues.Text = ""
      '
      'frmDataDisplay
      '
      Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
      Me.BackColor = System.Drawing.SystemColors.Window
      Me.ClientSize = New System.Drawing.Size(384, 404)
      Me.Controls.Add(Me.txtEncoderValues)
      Me.Controls.Add(Me.Label1)
      Me.Controls.Add(Me.cmdStopConvert)
      Me.Controls.Add(Me.cmdStart)
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

      Me.lblCounterData = New System.Windows.Forms.Label(15) {}

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