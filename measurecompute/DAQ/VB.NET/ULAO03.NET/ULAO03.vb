'ULAO03================================================================
'
' File:                         ULAO03.VB
'
' Library Call Demonstrated:    MccBoard.AOut()
'                               MccBoard.BoardConfig.SetDACUpdateMode()
'                               MccBoard.BoardConfig.DACUpdate()
'
' Purpose:                      Demonstrates difference between DACUpdate.Immediate
'                               and DACUpdate.OnCommand D/A Update modes
'
' Demonstration:                Delays outputs until user issues update command 
'                               DACUpdate().
'
' Other Library Calls:          MccService.ErrHandling()
'                               MccBoard.FromEngUnits()
'
' Special Requirements:         Board 0 must support BIDACUPDATEMODE settings,
'                               such as the PCI-DAC6700's.
'
'
' (c) Copyright 2003, Measurement Computing Corp.
' All rights reserved.
'==========================================================================
Option Strict Off
Option Explicit On 
Public Class frmAOut
    Inherits System.Windows.Forms.Form

    'Create a new MccBoard object for Board 0
    Private _bd As MccDaq.MccBoard = New MccDaq.MccBoard(0)
    Private _range As MccDaq.Range = MccDaq.Range.Bip10Volts
    Public txtAOVolts As System.Windows.Forms.TextBox()

    Const AllChannels As Integer = -1


    Private Sub rdioOnCommand_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rdioOnCommand.CheckedChanged
        Dim channel As Integer

        If (rdioOnCommand.Checked) Then
            ' Set DAC Update mode to hold off updating D/A's until command is sent
            ' Parameters
            '	 channel	: D/A channel whose update mode is to be configured. Note
            '				  that negative values selects all channels
            '   DACUpdate.OnCommand : delay D/A output updates from AOut or AOutScan until
            '                         DACUpdate command is issued.
            channel = AllChannels
            _bd.BoardConfig.SetDACUpdateMode(channel, MccDaq.DACUpdate.OnCommand)
        End If

    End Sub



    Private Sub rdioImmediate_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rdioImmediate.CheckedChanged
        Dim channel As Integer

        If (rdioImmediate.Checked) Then
            ' Set DAC Update mode to update immediately upon cbAOut or cbAOutScan
            ' Parameters
            '	 channel	: D/A channel whose update mode is to be configured. Note
            '				  that negative values selects all channels
            '   DACUpdate.Immediate : update D/A outputs immediately upon AOut or AOutScan
            channel = AllChannels
            _bd.BoardConfig.SetDACUpdateMode(channel, MccDaq.DACUpdate.Immediate)
        End If

    End Sub



    Private Sub btnSendData_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSendData.Click
        Dim volts As Single = 0.0F
        Dim daCounts As Integer = 0
        Dim chan As Integer

        For chan = 0 To 3
            'get voltage to output
            volts = Val(txtAOVolts(chan).Text)

            ' convert from voltage to binary counts
            _bd.FromEngUnits(_range, volts, daCounts)

            ' load D/A
            _bd.AOut(chan, _range, daCounts)
        Next chan



    End Sub



    Private Sub btnUpdateDACs_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnUpdateDACs.Click

        ' Issue D/A update command
        _bd.BoardConfig.DACUpdate()

    End Sub



    Private Sub frmAOut_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim ULStat As MccDaq.ErrorInfo
        Dim channel As Integer

        ' Initiate error handling
        '  activating error handling will trap errors like
        '  bad channel numbers and non-configured conditions.
        '  Parameters:
        '    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
        '    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop
        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)


        ' Set DAC Update mode to hold off updating D/A's until command is sent
        ' Parameters
        '	 channel	: D/A channel whose update mode is to be configured. Note
        '				  that negative values selects all channels
        '   DACUpdate.OnCommand : delay D/A output updates from AOut or AOutScan until
        '                         DACUpdate command is issued.
        channel = AllChannels
        _bd.BoardConfig.SetDACUpdateMode(channel, MccDaq.DACUpdate.OnCommand)


        ' Attach references of voltage textboxes to array for easier access
        txtAOVolts = New System.Windows.Forms.TextBox(4) {}
        
        txtAOVolts.SetValue(txtAOVolts3, 3)
        txtAOVolts.SetValue(txtAOVolts2, 2)
        txtAOVolts.SetValue(txtAOVolts1, 1)
        txtAOVolts.SetValue(txtAOVolts0, 0)
        
    End Sub


#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

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
    Friend WithEvents label5 As System.Windows.Forms.Label
    Friend WithEvents label4 As System.Windows.Forms.Label
    Friend WithEvents label3 As System.Windows.Forms.Label
    Friend WithEvents label2 As System.Windows.Forms.Label
    Friend WithEvents btnSendData As System.Windows.Forms.Button
    Friend WithEvents btnUpdateDACs As System.Windows.Forms.Button
    Friend WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents rdioImmediate As System.Windows.Forms.RadioButton
    Friend WithEvents rdioOnCommand As System.Windows.Forms.RadioButton
    Friend WithEvents txtAOVolts3 As System.Windows.Forms.TextBox
    Friend WithEvents txtAOVolts2 As System.Windows.Forms.TextBox
    Friend WithEvents txtAOVolts1 As System.Windows.Forms.TextBox
    Friend WithEvents txtAOVolts0 As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.label5 = New System.Windows.Forms.Label()
        Me.label4 = New System.Windows.Forms.Label()
        Me.label3 = New System.Windows.Forms.Label()
        Me.label2 = New System.Windows.Forms.Label()
        Me.btnSendData = New System.Windows.Forms.Button()
        Me.btnUpdateDACs = New System.Windows.Forms.Button()
        Me.label1 = New System.Windows.Forms.Label()
        Me.rdioImmediate = New System.Windows.Forms.RadioButton()
        Me.rdioOnCommand = New System.Windows.Forms.RadioButton()
        Me.txtAOVolts3 = New System.Windows.Forms.TextBox()
        Me.txtAOVolts2 = New System.Windows.Forms.TextBox()
        Me.txtAOVolts1 = New System.Windows.Forms.TextBox()
        Me.txtAOVolts0 = New System.Windows.Forms.TextBox()
        Me.SuspendLayout()
        '
        'label5
        '
        Me.label5.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label5.ForeColor = System.Drawing.SystemColors.HotTrack
        Me.label5.Location = New System.Drawing.Point(288, 104)
        Me.label5.Name = "label5"
        Me.label5.Size = New System.Drawing.Size(80, 16)
        Me.label5.TabIndex = 13
        Me.label5.Text = "Channel 3"
        '
        'label4
        '
        Me.label4.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label4.ForeColor = System.Drawing.SystemColors.HotTrack
        Me.label4.Location = New System.Drawing.Point(200, 104)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(80, 16)
        Me.label4.TabIndex = 12
        Me.label4.Text = "Channel 2"
        '
        'label3
        '
        Me.label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label3.ForeColor = System.Drawing.SystemColors.HotTrack
        Me.label3.Location = New System.Drawing.Point(112, 104)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(80, 16)
        Me.label3.TabIndex = 11
        Me.label3.Text = "Channel 1"
        '
        'label2
        '
        Me.label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label2.ForeColor = System.Drawing.SystemColors.HotTrack
        Me.label2.Location = New System.Drawing.Point(24, 104)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(80, 16)
        Me.label2.TabIndex = 10
        Me.label2.Text = "Channel 0"
        '
        'btnSendData
        '
        Me.btnSendData.Location = New System.Drawing.Point(48, 64)
        Me.btnSendData.Name = "btnSendData"
        Me.btnSendData.Size = New System.Drawing.Size(136, 32)
        Me.btnSendData.TabIndex = 9
        Me.btnSendData.Text = "Send Data"
        '
        'btnUpdateDACs
        '
        Me.btnUpdateDACs.Location = New System.Drawing.Point(208, 64)
        Me.btnUpdateDACs.Name = "btnUpdateDACs"
        Me.btnUpdateDACs.Size = New System.Drawing.Size(136, 32)
        Me.btnUpdateDACs.TabIndex = 8
        Me.btnUpdateDACs.Text = "Update Outputs"
        '
        'label1
        '
        Me.label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label1.Location = New System.Drawing.Point(40, 8)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(296, 48)
        Me.label1.TabIndex = 7
        Me.label1.Text = "Demonstrates DAC Update Modes using AOut"
        Me.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'rdioImmediate
        '
        Me.rdioImmediate.Location = New System.Drawing.Point(104, 200)
        Me.rdioImmediate.Name = "rdioImmediate"
        Me.rdioImmediate.Size = New System.Drawing.Size(168, 24)
        Me.rdioImmediate.TabIndex = 15
        Me.rdioImmediate.Text = "Update Immediately"
        '
        'rdioOnCommand
        '
        Me.rdioOnCommand.Checked = True
        Me.rdioOnCommand.Location = New System.Drawing.Point(104, 168)
        Me.rdioOnCommand.Name = "rdioOnCommand"
        Me.rdioOnCommand.Size = New System.Drawing.Size(168, 24)
        Me.rdioOnCommand.TabIndex = 14
        Me.rdioOnCommand.TabStop = True
        Me.rdioOnCommand.Text = "Update On Command"
        '
        'txtAOVolts3
        '
        Me.txtAOVolts3.Location = New System.Drawing.Point(292, 128)
        Me.txtAOVolts3.Name = "txtAOVolts3"
        Me.txtAOVolts3.Size = New System.Drawing.Size(72, 20)
        Me.txtAOVolts3.TabIndex = 19
        Me.txtAOVolts3.Text = "0.00"
        '
        'txtAOVolts2
        '
        Me.txtAOVolts2.Location = New System.Drawing.Point(204, 128)
        Me.txtAOVolts2.Name = "txtAOVolts2"
        Me.txtAOVolts2.Size = New System.Drawing.Size(72, 20)
        Me.txtAOVolts2.TabIndex = 18
        Me.txtAOVolts2.Text = "0.00"
        '
        'txtAOVolts1
        '
        Me.txtAOVolts1.Location = New System.Drawing.Point(116, 128)
        Me.txtAOVolts1.Name = "txtAOVolts1"
        Me.txtAOVolts1.Size = New System.Drawing.Size(72, 20)
        Me.txtAOVolts1.TabIndex = 17
        Me.txtAOVolts1.Text = "0.00"
        '
        'txtAOVolts0
        '
        Me.txtAOVolts0.Location = New System.Drawing.Point(28, 128)
        Me.txtAOVolts0.Name = "txtAOVolts0"
        Me.txtAOVolts0.Size = New System.Drawing.Size(72, 20)
        Me.txtAOVolts0.TabIndex = 16
        Me.txtAOVolts0.Text = "0.00"
        '
        'frmAOut
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(392, 237)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.txtAOVolts3, Me.txtAOVolts2, Me.txtAOVolts1, Me.txtAOVolts0, Me.rdioImmediate, Me.rdioOnCommand, Me.label5, Me.label4, Me.label3, Me.label2, Me.btnSendData, Me.btnUpdateDACs, Me.label1})
        Me.Name = "frmAOut"
        Me.Text = "Universal Library Analog Output"
        Me.ResumeLayout(False)

    End Sub

#End Region


End Class
