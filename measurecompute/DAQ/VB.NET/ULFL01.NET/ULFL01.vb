'==============================================================================

' File:                         ULFL01.VB

' Library Call Demonstrated:    LED Functions
'                               Mccdaq.MccBoard.FlashLED()

' Purpose:                      Operate the LED.

' Demonstration:                Flashes onboard LED for visual identification

' Other Library Calls:          MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have an external LED, 
'                               such as the miniLAB 1008 and PMD-1208LS.                 
'
'==============================================================================
Option Strict Off
Option Explicit On 
Public Class frmLEDTest
    Inherits Form

    'Create a new MccBoard object for Board 0
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)


#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        InitUL()

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
    Friend WithEvents btnFlashLED As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.btnFlashLED = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'btnFlashLED
        '
        Me.btnFlashLED.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnFlashLED.Location = New System.Drawing.Point(104, 64)
        Me.btnFlashLED.Name = "btnFlashLED"
        Me.btnFlashLED.Size = New System.Drawing.Size(120, 48)
        Me.btnFlashLED.TabIndex = 0
        Me.btnFlashLED.Text = "Flash LED"
        '
        'frmLEDTest
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(328, 197)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.btnFlashLED})
        Me.Name = "frmLEDTest"
        Me.Text = "Universal LibraryLED Test"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub btnFlashLED_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnFlashLED.Click
        Dim ULStat As MccDaq.ErrorInfo

        'Flash the onboard LED
        ULStat = DaqBoard.FlashLED()
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If

    End Sub


#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

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

    End Sub
#End Region

End Class
