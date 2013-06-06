'=====================================================================================

' File:                         DaqSetSetpoints01.VB

' Library Call Demonstrated:    Mccdaq.MccBoard.DaqSetSetpoints()
'                               

' Purpose:                      Demonstrate the configuration and usage of setpoints
'                               Including Adding the setpoint status to the scanlist and
'                               asynchronous reads of the setpoint status

' Demonstration:                Displays the input channels data.
'                               Calls cbGetStatus to determine the status
'                               of the background operation. Updates the
'                               display until Stop Background button is pressed.


' Other Library Calls:          Mccdaq.MccBoard.DaqInScan()
'                               MccDaq.MccService.ErrHandling()
'                               Mccdaq.MccBoard.GetStatus()
'                               Mccdaq.MccBoard.StopBackground()
'                               Mccdaq.MccBoard.DConfigPort()


' Special Requirements:         Board 0 must support cbDaqInScan.
'

' (c) Copyright 1995-2007, Measurement Computing Corp.
' All rights reserved.
'========================================================================================
Option Strict Off
Option Explicit On
Friend Class frmStatusDisplay
	Inherits System.Windows.Forms.Form

    Const BoardNum As Integer = 0 ' Board number
    Const ChanCount As Integer = 4 ' Number of channels in scan
    Const NumPoints As Integer = 1000 ' Number of data points to collect
    Const NumElements As Integer = ChanCount * NumPoints

    Const SetpointCount As Integer = 3        ' Number of setpoints

    'Create a new MccBoard object
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(BoardNum)

    Dim ADData(NumElements) As UInt16 ' dimension an array to hold the input values
    Dim MemHandle As Integer ' define a variable to contain the handle for
    ' memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
    Dim ChanArray(ChanCount) As Short ' array to hold channel queue information
    Dim ChanTypeArray(ChanCount) As MccDaq.ChannelType ' array to hold channel type information
    Dim GainArray(ChanCount) As MccDaq.Range ' array to hold gain queue information

    Dim LimitAArray(SetpointCount) As Single
    Dim LimitBArray(SetpointCount) As Single
    Dim Reserved(0) As Single
    Dim SetpointFlagsArray(SetpointCount) As MccDaq.SetpointFlag
    Dim SetpointOutputArray(SetpointCount) As MccDaq.SetpointOutput
    Dim Output1Array(SetpointCount) As Single
    Dim Output2Array(SetpointCount) As Single
    Dim OutputMask1Array(SetpointCount) As Single
    Dim OutputMask2Array(SetpointCount) As Single

    Dim UserTerm As Short
    Public lblADData As System.Windows.Forms.Label()

    Private Sub frmStatusDisplay_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        
        'load the arrays with values
        ChanArray(0) = 0
        ChanTypeArray(0) = MccDaq.ChannelType.Analog + MccDaq.ChannelType.SetpointEnable
        GainArray(0) = MccDaq.Range.Bip10Volts

        ChanArray(1) = 1
        ChanTypeArray(1) = MccDaq.ChannelType.Analog + MccDaq.ChannelType.SetpointEnable
        GainArray(1) = MccDaq.Range.Bip10Volts

        ChanArray(2) = MccDaq.DigitalPortType.FirstPortA
        ChanTypeArray(2) = MccDaq.ChannelType.Digital8 + MccDaq.ChannelType.SetpointEnable
        GainArray(2) = MccDaq.Range.NotUsed

        ChanArray(3) = 0
        ChanTypeArray(3) = MccDaq.ChannelType.SetpointStatus
        GainArray(3) = MccDaq.Range.NotUsed

        ' setpoint configurations for ChanArray[0]  (CH0)
        SetpointFlagsArray(0) = MccDaq.SetpointFlag.LessThanLimitA + MccDaq.SetpointFlag.UpdateOnTrueAndFalse
        SetpointOutputArray(0) = MccDaq.SetpointOutput.DAC0   ' setpoint result outputs a value to Analog Out 0
        LimitAArray(0) = 3          ' if CH0 less than 3.0 volts apply output1, else apply output2
        LimitBArray(0) = 0          ' ignored when LessThanLimitA flag is used
        Output1Array(0) = 5         ' output 5.0 volts on Analog Out 0
        Output2Array(0) = -5        ' output -5.0 volts on Analog Out 0
        OutputMask1Array(0) = 0     ' ignored for DAC0 output type 
        OutputMask2Array(0) = 0     ' ignored for DAC0 output type 

        ' setpoint configurations for ChanArray(1) (CH1)*/
        SetpointFlagsArray(1) = MccDaq.SetpointFlag.GreaterThanLimitB + MccDaq.SetpointFlag.UpdateOnTrueAndFalse
        SetpointOutputArray(1) = MccDaq.SetpointOutput.FirstPortC ' setpoint result outputs a value to digital port C	
        LimitAArray(1) = 0            ' ignored when GreaterThanLimitB flag is used				
        LimitBArray(1) = 2            ' if CH1 greater than 2.0 volts apply output1
        Output1Array(1) = &H55        ' output a bit pattern of 01010101 to digital port C
        Output2Array(1) = &HAA        ' output a bit pattern of 10101010 to digital port C
        OutputMask1Array(1) = &HF     ' output the value of 'out1' on low nibble only
        OutputMask2Array(1) = &HF    ' output the value of 'out2' on low nibble only 

        ' setpoint configurations for ChanArray(2) (FIRSTPORTA)*/
        SetpointFlagsArray(2) = MccDaq.SetpointFlag.EqualLimitA + MccDaq.SetpointFlag.UpdateOnTrueOnly
        SetpointOutputArray(2) = MccDaq.SetpointOutput.TMR0 ' setpoint result outputs a value to Timer 0	
        LimitAArray(2) = &HF        ' if FirstPortA equal 00001111 bit pattern apply output1				
        LimitBArray(2) = 2          ' ignored when EqualLimitA flag is used
        Output1Array(2) = 100       ' output a 100Hz square wave on Timer 0
        Output2Array(2) = 0         ' ignored when SF_UPDATEON_TRUEONLY flag is used
        OutputMask1Array(2) = 0     ' ignored for 'TMR0' output type 
        OutputMask2Array(2) = 0     ' ignored for 'TMR0' output type 

    End Sub

    Private Sub cmdStartBgnd_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStartBgnd.Click
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short
        Dim ULStat As MccDaq.ErrorInfo
        Dim Rate As Integer
        Dim Options As MccDaq.ScanOptions
        Dim Count As Integer
        Dim PretrigCount As Integer

        Dim Direction As MccDaq.DigitalPortDirection
        Dim PortNum As MccDaq.DigitalPortType

        cmdStartBgnd.Enabled = 0
        cmdStartBgnd.Visible = 0
        cmdStopConvert.Enabled = 1
        cmdStopConvert.Visible = 1
        cmdQuit.Enabled = 0
        UserTerm = 0 ' initialize user terminate flag

        ' configure setpoints with cbDaqSetSetpoints()
        ' Parameters:
		'		BoardNum				:the number used by CB.CFG to describe this board
        '		LimitAArray[]			:array of LimitA values
        '		LimitBArray[]			:array of LimitB values
        '		SetpointFlagsArray[]	:array of Setpoint flags
        '		SetpointOutputArray[]   :array of output channels
        '		Output1Array[]			:array of output1 values
        '		Output2Array[]			:array of output2 values
        '		OutputMask1Array[]		:array of output masks for output1
        '		OutputMask2Array[]      :array of output masks for output2 
        '		SetpointCount           :Number of setpoints

  ULStat = DaqBoard.DaqSetSetpoints(LimitAArray, LimitBArray, Reserved, SetpointFlagsArray, SetpointOutputArray, Output1Array, Output2Array, OutputMask1Array, OutputMask2Array, SetpointCount)

          'configure FirstPortA for digital input
        PortNum = ChanArray(2)
        Direction = MccDaq.DigitalPortDirection.DigitalIn
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
          Stop
        End If

        ' Collect the values with cbDaqInScan()
        '  Parameters:
        '    BoardNum        :the number used by CB.CFG to describe this board
        '    ChanArray[]     :array of channel values
        '    ChanTypeArray[] : array of channel types
        '    GainArray[]     :array of gain values
        '    ChanCount        :the number of elements in the arrays (0=disable queue)
        '    PretrigCount    :number of pre-trigger A/D samples to collect
        '    Count         :the total number of A/D samples to collect
        '    Rate          :sample rate in samples per second
        '    ADData[]        :the array for the collected data values
        '    Options          :data collection options

        PretrigCount = 0
        Count = NumElements ' Number of data points to collect
        Options = MccDaq.ScanOptions.ConvertData + MccDaq.ScanOptions.Background + MccDaq.ScanOptions.Continuous
        Rate = 100 ' Acquire data at 100 Hz

        If MemHandle = 0 Then Stop ' check that a handle to a memory buffer exists

        ULStat = DaqBoard.DaqInScan(ChanArray, ChanTypeArray, GainArray, ChanCount, Rate, PretrigCount, Count, MemHandle, Options)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        If Status = MccDaq.MccBoard.Running Then
            lblShowStat.Text = "Running"
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")
        End If

        tmrCheckStatus.Enabled = True

    End Sub


    Private Sub tmrCheckStatus_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrCheckStatus.Tick
        Dim FirstPoint As Integer
        Dim ULStat As MccDaq.ErrorInfo
        Dim CurIndex As Integer
        Dim CurCount As Integer
        Dim Status As Short
        Dim EngUnits As Single

        tmrCheckStatus.Stop()

        ' This timer will check the status of the background data collection

        ' Parameters:
        '   BoardNum    :the number used by CB.CFG to describe this board
        '   Status     :current status of the background data collection
        '   CurCount   :current number of samples collected
        '   CurIndex   :index to the data buffer pointing to the start of the
        '                most recently collected scan
        '   FunctionType: A/D operation (DAQIFUNCTION)

        ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqiFunction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


        lblShowCount.Text = CurCount.ToString("D")
        lblShowIndex.Text = CurIndex.ToString("D")

        ' Check if the background operation has finished. If it has, then
        ' transfer the data from the memory buffer set up by Windows to an
        ' array for use by Visual Basic
        ' The BACKGROUND operation must be explicitly stopped

        If Status = MccDaq.MccBoard.Running And UserTerm = 0 Then
            lblShowStat.Text = "Running"
            ULStat = DaqBoard.GetStatus(Status, CurCount, CurIndex, MccDaq.FunctionType.DaqiFunction)

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
            lblShowCount.Text = CurCount.ToString("D")
            lblShowIndex.Text = CurIndex.ToString("D")

            FirstPoint = CurIndex
            If FirstPoint >= 0 Then
                If MemHandle = 0 Then Stop
                ULStat = MccDaq.MccService.WinBufToArray(MemHandle, ADData(0), FirstPoint, ChanCount)
                If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

                DaqBoard.ToEngUnits(GainArray(0), ADData(0), EngUnits)
                lblADData(0).Text = String.Format("{0:f4}", EngUnits) + " Volts"
                DaqBoard.ToEngUnits(GainArray(1), ADData(1), EngUnits)
                lblADData(1).Text = String.Format("{0:f4}", EngUnits) + " Volts"
                lblADData(2).Text = "0x" + String.Format("{0:X2}", ADData(2))
                lblADData(3).Text = "0x" + String.Format("{0:X4}", ADData(3))
            End If
            tmrCheckStatus.Start()
        ElseIf Status = MccDaq.MccBoard.Idle Or UserTerm = 1 Then
            lblShowStat.Text = "Idle"
            tmrCheckStatus.Stop()

            ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DaqiFunction)
            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

            cmdStartBgnd.Enabled = 1
            cmdStartBgnd.Visible = 1
            cmdStopConvert.Enabled = 0
            cmdStopConvert.Visible = 0
            cmdQuit.Enabled = 1
        End If

    End Sub

    Private Sub cmdQuit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdQuit.Click
        Dim ULStat As MccDaq.ErrorInfo

        ULStat = MccDaq.MccService.WinBufFree(MemHandle) ' Free up memory for use by
        ' other programs
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop
        End

    End Sub

    Private Sub cmdStopConvert_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdStopConvert.Click

        UserTerm = 1

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
    Public WithEvents tmrCheckStatus As System.Windows.Forms.Timer
    Public WithEvents cmdStopConvert As System.Windows.Forms.Button
    Public WithEvents cmdStartBgnd As System.Windows.Forms.Button
    Public WithEvents lblShowCount As System.Windows.Forms.Label
    Public WithEvents lblCount As System.Windows.Forms.Label
    Public WithEvents lblShowIndex As System.Windows.Forms.Label
    Public WithEvents lblIndex As System.Windows.Forms.Label
    Public WithEvents lblShowStat As System.Windows.Forms.Label
    Public WithEvents lblStatus As System.Windows.Forms.Label
    Public WithEvents _lblADData_2 As System.Windows.Forms.Label
    Public WithEvents lblChan2 As System.Windows.Forms.Label
    Public WithEvents _lblADData_1 As System.Windows.Forms.Label
    Public WithEvents lblChan1 As System.Windows.Forms.Label
    Public WithEvents _lblADData_0 As System.Windows.Forms.Label
    Public WithEvents lblChan0 As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
Public WithEvents _lblADData_3 As System.Windows.Forms.Label
Public WithEvents lblChan3 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
Me.components = New System.ComponentModel.Container()
Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
Me.cmdQuit = New System.Windows.Forms.Button()
Me.tmrCheckStatus = New System.Windows.Forms.Timer(Me.components)
Me.cmdStopConvert = New System.Windows.Forms.Button()
Me.cmdStartBgnd = New System.Windows.Forms.Button()
Me.lblShowCount = New System.Windows.Forms.Label()
Me.lblCount = New System.Windows.Forms.Label()
Me.lblShowIndex = New System.Windows.Forms.Label()
Me.lblIndex = New System.Windows.Forms.Label()
Me.lblShowStat = New System.Windows.Forms.Label()
Me.lblStatus = New System.Windows.Forms.Label()
Me._lblADData_2 = New System.Windows.Forms.Label()
Me.lblChan2 = New System.Windows.Forms.Label()
Me._lblADData_1 = New System.Windows.Forms.Label()
Me.lblChan1 = New System.Windows.Forms.Label()
Me._lblADData_0 = New System.Windows.Forms.Label()
Me.lblChan0 = New System.Windows.Forms.Label()
Me.lblDemoFunction = New System.Windows.Forms.Label()
Me._lblADData_3 = New System.Windows.Forms.Label()
Me.lblChan3 = New System.Windows.Forms.Label()
Me.SuspendLayout()
'
'cmdQuit
'
Me.cmdQuit.BackColor = System.Drawing.SystemColors.Control
Me.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdQuit.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdQuit.Location = New System.Drawing.Point(280, 248)
Me.cmdQuit.Name = "cmdQuit"
Me.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdQuit.Size = New System.Drawing.Size(52, 26)
Me.cmdQuit.TabIndex = 9
Me.cmdQuit.Text = "Quit"
'
'tmrCheckStatus
'
Me.tmrCheckStatus.Interval = 200
'
'cmdStopConvert
'
Me.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control
Me.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdStopConvert.Enabled = False
Me.cmdStopConvert.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdStopConvert.Location = New System.Drawing.Point(83, 48)
Me.cmdStopConvert.Name = "cmdStopConvert"
Me.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdStopConvert.Size = New System.Drawing.Size(180, 27)
Me.cmdStopConvert.TabIndex = 7
Me.cmdStopConvert.Text = "Stop Background Operation"
Me.cmdStopConvert.Visible = False
'
'cmdStartBgnd
'
Me.cmdStartBgnd.BackColor = System.Drawing.SystemColors.Control
Me.cmdStartBgnd.Cursor = System.Windows.Forms.Cursors.Default
Me.cmdStartBgnd.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.cmdStartBgnd.ForeColor = System.Drawing.SystemColors.ControlText
Me.cmdStartBgnd.Location = New System.Drawing.Point(83, 48)
Me.cmdStartBgnd.Name = "cmdStartBgnd"
Me.cmdStartBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.cmdStartBgnd.Size = New System.Drawing.Size(180, 27)
Me.cmdStartBgnd.TabIndex = 8
Me.cmdStartBgnd.Text = "Start Background Operation"
'
'lblShowCount
'
Me.lblShowCount.BackColor = System.Drawing.SystemColors.Window
Me.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowCount.ForeColor = System.Drawing.Color.Blue
Me.lblShowCount.Location = New System.Drawing.Point(199, 264)
Me.lblShowCount.Name = "lblShowCount"
Me.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowCount.Size = New System.Drawing.Size(59, 14)
Me.lblShowCount.TabIndex = 15
'
'lblCount
'
Me.lblCount.BackColor = System.Drawing.SystemColors.Window
Me.lblCount.Cursor = System.Windows.Forms.Cursors.Default
Me.lblCount.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblCount.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblCount.Location = New System.Drawing.Point(84, 264)
Me.lblCount.Name = "lblCount"
Me.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblCount.Size = New System.Drawing.Size(104, 14)
Me.lblCount.TabIndex = 13
Me.lblCount.Text = "Current Count:"
Me.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblShowIndex
'
Me.lblShowIndex.BackColor = System.Drawing.SystemColors.Window
Me.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowIndex.ForeColor = System.Drawing.Color.Blue
Me.lblShowIndex.Location = New System.Drawing.Point(199, 240)
Me.lblShowIndex.Name = "lblShowIndex"
Me.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowIndex.Size = New System.Drawing.Size(52, 14)
Me.lblShowIndex.TabIndex = 14
'
'lblIndex
'
Me.lblIndex.BackColor = System.Drawing.SystemColors.Window
Me.lblIndex.Cursor = System.Windows.Forms.Cursors.Default
Me.lblIndex.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblIndex.Location = New System.Drawing.Point(84, 240)
Me.lblIndex.Name = "lblIndex"
Me.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblIndex.Size = New System.Drawing.Size(104, 14)
Me.lblIndex.TabIndex = 12
Me.lblIndex.Text = "Current Index:"
Me.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblShowStat
'
Me.lblShowStat.BackColor = System.Drawing.SystemColors.Window
Me.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default
Me.lblShowStat.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblShowStat.ForeColor = System.Drawing.Color.Blue
Me.lblShowStat.Location = New System.Drawing.Point(224, 224)
Me.lblShowStat.Name = "lblShowStat"
Me.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblShowStat.Size = New System.Drawing.Size(66, 14)
Me.lblShowStat.TabIndex = 11
'
'lblStatus
'
Me.lblStatus.BackColor = System.Drawing.SystemColors.Window
Me.lblStatus.Cursor = System.Windows.Forms.Cursors.Default
Me.lblStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblStatus.Location = New System.Drawing.Point(6, 224)
Me.lblStatus.Name = "lblStatus"
Me.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblStatus.Size = New System.Drawing.Size(212, 14)
Me.lblStatus.TabIndex = 10
Me.lblStatus.Text = "Status of Background Operation:"
Me.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'_lblADData_2
'
Me._lblADData_2.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_2.ForeColor = System.Drawing.Color.Blue
Me._lblADData_2.Location = New System.Drawing.Point(144, 155)
Me._lblADData_2.Name = "_lblADData_2"
Me._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_2.Size = New System.Drawing.Size(105, 17)
Me._lblADData_2.TabIndex = 6
'
'lblChan2
'
Me.lblChan2.BackColor = System.Drawing.SystemColors.Window
Me.lblChan2.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan2.Location = New System.Drawing.Point(55, 155)
Me.lblChan2.Name = "lblChan2"
Me.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan2.Size = New System.Drawing.Size(81, 17)
Me.lblChan2.TabIndex = 3
Me.lblChan2.Text = "FIRSTPORTA:"
Me.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'_lblADData_1
'
Me._lblADData_1.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_1.ForeColor = System.Drawing.Color.Blue
Me._lblADData_1.Location = New System.Drawing.Point(144, 128)
Me._lblADData_1.Name = "_lblADData_1"
Me._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_1.Size = New System.Drawing.Size(105, 17)
Me._lblADData_1.TabIndex = 5
'
'lblChan1
'
Me.lblChan1.BackColor = System.Drawing.SystemColors.Window
Me.lblChan1.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan1.Location = New System.Drawing.Point(39, 128)
Me.lblChan1.Name = "lblChan1"
Me.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan1.Size = New System.Drawing.Size(97, 17)
Me.lblChan1.TabIndex = 2
Me.lblChan1.Text = "Channel 1:"
Me.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'_lblADData_0
'
Me._lblADData_0.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_0.ForeColor = System.Drawing.Color.Blue
Me._lblADData_0.Location = New System.Drawing.Point(144, 101)
Me._lblADData_0.Name = "_lblADData_0"
Me._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_0.Size = New System.Drawing.Size(105, 17)
Me._lblADData_0.TabIndex = 4
'
'lblChan0
'
Me.lblChan0.BackColor = System.Drawing.SystemColors.Window
Me.lblChan0.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan0.Location = New System.Drawing.Point(55, 101)
Me.lblChan0.Name = "lblChan0"
Me.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan0.Size = New System.Drawing.Size(81, 17)
Me.lblChan0.TabIndex = 1
Me.lblChan0.Text = "Channel 0:"
Me.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'lblDemoFunction
'
Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblDemoFunction.Location = New System.Drawing.Point(6, 6)
Me.lblDemoFunction.Name = "lblDemoFunction"
Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblDemoFunction.Size = New System.Drawing.Size(337, 41)
Me.lblDemoFunction.TabIndex = 0
Me.lblDemoFunction.Text = "Demonstration of MccBoard.DaqSetSetpoints()"
Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
'
'_lblADData_3
'
Me._lblADData_3.BackColor = System.Drawing.SystemColors.Window
Me._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default
Me._lblADData_3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me._lblADData_3.ForeColor = System.Drawing.Color.Blue
Me._lblADData_3.Location = New System.Drawing.Point(144, 184)
Me._lblADData_3.Name = "_lblADData_3"
Me._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No
Me._lblADData_3.Size = New System.Drawing.Size(105, 17)
Me._lblADData_3.TabIndex = 19
'
'lblChan3
'
Me.lblChan3.BackColor = System.Drawing.SystemColors.Window
Me.lblChan3.Cursor = System.Windows.Forms.Cursors.Default
Me.lblChan3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText
Me.lblChan3.Location = New System.Drawing.Point(8, 184)
Me.lblChan3.Name = "lblChan3"
Me.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No
Me.lblChan3.Size = New System.Drawing.Size(128, 17)
Me.lblChan3.TabIndex = 18
Me.lblChan3.Text = "Setpoint Status Register:"
Me.lblChan3.TextAlign = System.Drawing.ContentAlignment.TopRight
'
'frmStatusDisplay
'
Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
Me.BackColor = System.Drawing.SystemColors.Window
Me.ClientSize = New System.Drawing.Size(350, 285)
Me.Controls.AddRange(New System.Windows.Forms.Control() {Me._lblADData_3, Me.lblChan3, Me.cmdQuit, Me.cmdStopConvert, Me.cmdStartBgnd, Me.lblShowCount, Me.lblCount, Me.lblShowIndex, Me.lblIndex, Me.lblShowStat, Me.lblStatus, Me._lblADData_2, Me.lblChan2, Me._lblADData_1, Me.lblChan1, Me._lblADData_0, Me.lblChan0, Me.lblDemoFunction})
Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
Me.ForeColor = System.Drawing.Color.Blue
Me.Location = New System.Drawing.Point(188, 108)
Me.Name = "frmStatusDisplay"
Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
Me.Text = "Universal Library DaqSetSetpoints()"
Me.ResumeLayout(False)

    End Sub
#End Region

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        ' Note: Any change to label names requires a change to the corresponding array element
        lblADData = (New System.Windows.Forms.Label() {Me._lblADData_0, Me._lblADData_1, Me._lblADData_2, Me._lblADData_3})

        ' declare revision level of Universal Library

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

        MemHandle = MccDaq.MccService.WinBufAlloc(NumElements) ' set aside memory to hold data
        If MemHandle = 0 Then Stop

    End Sub
#End Region
End Class