// ==============================================================================
//
//  File:                         ULCT02.CS
//
//  Library Call Demonstrated:    9513 Counter Functions
//                                Mccdaq.MccBoard.C9513Init()
//                                Mccdaq.MccBoard.C9513Config()
//                                Mccdaq.MccBoard.CLoad()
//                                Mccdaq.MccBoard.CIn()
//
//  Purpose:                      Operate the counter.
//
//  Demonstration:                Initializes, configures, loads and checks
//                                the counter
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a 9513 Counter.
//                                Program uses internal clock to count.
//
// ==============================================================================
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Diagnostics;

using MccDaq;

namespace ULCT02
{
public class frm9513Ctr : System.Windows.Forms.Form
{
	// Required by the Windows Form Designer
	private System.ComponentModel.IContainer components;

	public ToolTip ToolTip1;
	public Button cmdStopRead;
	public Timer tmrReadCounter;
	public Label lblShowReadVal;
	public Label lblReadValue;
	public Label lblShowLoadVal;
	public Label lblLoadValue;
	public Label lblDemoFunction;

	private MccDaq.MccBoard DaqBoard;
	const int CounterNum = 1;	//  number of the counter used
	const short ChipNum = 1;	//  use chip 1 for CTR05 or for first
								//  chip on CTR10
 
    public frm9513Ctr()
    {
        
        // This call is required by the Windows Form Designer.
        InitializeComponent();


		//  Initiate error handling
		//   activating error handling will trap errors like
		//   bad channel numbers and non-configured conditions.
		//   Parameters:
		//     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
		//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
		MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
		

		// Create a new MccBoard object for Board 0
		DaqBoard = new MccDaq.MccBoard(0);


		//  Initialize the board level features
		//   Parameters:
		//     ChipNum       :Chip to be initialized (1 for CTR05, 1 or 2 for CTR10)
		//     FOutDivider   :the F-Out divider (0-15)
		//     FOutSource    :the signal source for F-Out
		//     Compare1      :status of comparator 1
		//     Compare2      :status of comparator 2
		//     TimeOfDay     :time of day mode control
		short FOutDivider = 0;
		MccDaq.CounterSource FOutSource = MccDaq.CounterSource.Freq4;
		MccDaq.CompareValue Compare1 = MccDaq.CompareValue.Disabled;
		MccDaq.CompareValue Compare2 = MccDaq.CompareValue.Disabled;
		MccDaq.TimeOfDay TimeOfDayCounting = MccDaq.TimeOfDay.Disabled;
		ULStat = DaqBoard.C9513Init(ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDayCounting);
		

		//  Set the configurable operations of the counter
		//   Parameters:
		//     CounterNum     :the counter to be configured (1 to 5 for CTR05)
		//     GateControl    :gate control value
		//     CounterEdge    :which edge to count
		//     CountSource    :signal source
		//     SpecialGate    :status of special gate
		//     Reload         :method of reloading
		//     RecyleMode     :recyle mode
		//     BCDMode        :counting mode, Binary or BCD
		//     CountDirection :direction for the counting operation (COUNTUP or COUNTDOWN)
		//     OutputControl  :output signal type and level
		MccDaq.GateControl GateControl = MccDaq.GateControl.NoGate;
		MccDaq.CountEdge CounterEdge = MccDaq.CountEdge.PositiveEdge;
		MccDaq.CounterSource CountSource = MccDaq.CounterSource.Freq4;
		MccDaq.OptionState SpecialGate = MccDaq.OptionState.Disabled;
		MccDaq.Reload Reload = MccDaq.Reload.LoadReg;
		MccDaq.RecycleMode RecycleMode = MccDaq.RecycleMode.Recycle;
		MccDaq.BCDMode BCDMode = MccDaq.BCDMode.Disabled;
		MccDaq.CountDirection CountDirection = MccDaq.CountDirection.CountUp;
		MccDaq.C9513OutputControl OutputControl = MccDaq.C9513OutputControl.AlwaysLow;
		ULStat = DaqBoard.C9513Config(CounterNum, GateControl, CounterEdge, CountSource, SpecialGate, Reload, RecycleMode, BCDMode, CountDirection, OutputControl);
		

		//  Send a starting value to the counter with MccDaq.MccBoard.CLoad()
		//   Parameters:
		//     RegName    :the register for loading the counter with the starting value
		//     LoadValue  :the starting value to place in the counter
		MccDaq.CounterRegister RegName = MccDaq.CounterRegister.LoadReg1; //  name of register in counter 1
		int LoadValue = 1000;
		ULStat = DaqBoard.CLoad(RegName, LoadValue);
		

		lblLoadValue.Text = "Value loaded to counter:";
		lblShowLoadVal.Text = LoadValue.ToString("0");
    }


	private void tmrReadCounter_Tick(object eventSender, System.EventArgs eventArgs) 
    {
				
		tmrReadCounter.Stop();
		
		// Read the counter value 
		//  Parameters:
        //    CounterNum	:the counter to be read
        //    Count			:the count value in the counter
		ushort Count = 0;
        MccDaq.ErrorInfo ULStat = DaqBoard.CIn( CounterNum, out Count);

        lblReadValue.Text = "Value read from counter:";
        lblShowReadVal.Text = Count.ToString("0");

		tmrReadCounter.Start();
    }


    // Form overrides dispose to clean up the component list.
    protected override void  Dispose(bool Disposing)
    {
        if (Disposing)
        {
            if (components != null)
            {
                components.Dispose();
            }
        }
        base.Dispose(Disposing);
    }

    
         
    
    #region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    
    private void InitializeComponent()
    {

        //System.Resources.ResourceManager resources; = new System.Resources.ResourceManager(GetType(frm9513Ctr));
        this.components = new System.ComponentModel.Container();
        this.ToolTip1 = new System.Windows.Forms.ToolTip(components);
        this.ToolTip1.Active = true;
        this.cmdStopRead = new System.Windows.Forms.Button();
        this.tmrReadCounter = new System.Windows.Forms.Timer(components);
        this.lblShowReadVal = new System.Windows.Forms.Label();
        this.lblReadValue = new System.Windows.Forms.Label();
        this.lblShowLoadVal = new System.Windows.Forms.Label();
        this.lblLoadValue = new System.Windows.Forms.Label();
        this.lblDemoFunction = new System.Windows.Forms.Label();
        this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
        this.BackColor = System.Drawing.SystemColors.Window;
        this.Text = "Universal Library 9513 Counter Demo";
        this.ClientSize = new System.Drawing.Size(339, 243);
        this.Location = new System.Drawing.Point(7, 103);
        this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.ForeColor = System.Drawing.SystemColors.WindowText;
        this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
        this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
        this.ControlBox = true;
        this.Enabled = true;
        this.KeyPreview = false;
        this.MaximizeBox = true;
        this.MinimizeBox = true;
        this.Cursor = System.Windows.Forms.Cursors.Default;
        this.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.ShowInTaskbar = true;
        this.HelpButton = false;
        this.WindowState = System.Windows.Forms.FormWindowState.Normal;
        this.Name = "frm9513Ctr";

        this.cmdStopRead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        this.cmdStopRead.Text = "Quit";
        this.AcceptButton = this.cmdStopRead;
        this.cmdStopRead.Size = new System.Drawing.Size(54, 27);
        this.cmdStopRead.Location = new System.Drawing.Point(232, 184);
        this.cmdStopRead.TabIndex = 5;
        this.cmdStopRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.cmdStopRead.BackColor = System.Drawing.SystemColors.Control;
        this.cmdStopRead.CausesValidation = true;
        this.cmdStopRead.Enabled = true;
        this.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText;
        this.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default;
        this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.cmdStopRead.TabStop = true;
        this.cmdStopRead.Name = "cmdStopRead";
        this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
       //
       // tmrReadCounter
       //
        this.tmrReadCounter.Interval = 500;
        this.tmrReadCounter.Enabled = true;
        this.tmrReadCounter.Tick += new System.EventHandler(this.tmrReadCounter_Tick);

        this.lblShowReadVal.BackColor = System.Drawing.SystemColors.Window;
        this.lblShowReadVal.ForeColor = System.Drawing.Color.Blue;
        this.lblShowReadVal.Size = new System.Drawing.Size(73, 17);
        this.lblShowReadVal.Location = new System.Drawing.Point(232, 120);
        this.lblShowReadVal.TabIndex = 2;
        this.lblShowReadVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.lblShowReadVal.TextAlign = System.Drawing.ContentAlignment.TopLeft;
        this.lblShowReadVal.Enabled = true;
        this.lblShowReadVal.Cursor = System.Windows.Forms.Cursors.Default;
        this.lblShowReadVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.lblShowReadVal.UseMnemonic = true;
        this.lblShowReadVal.Visible = true;
        this.lblShowReadVal.AutoSize = false;
        this.lblShowReadVal.BorderStyle = System.Windows.Forms.BorderStyle.None;
        this.lblShowReadVal.Name = "lblShowReadVal";
        this.lblReadValue.BackColor = System.Drawing.SystemColors.Window;
        this.lblReadValue.ForeColor = System.Drawing.SystemColors.WindowText;
        this.lblReadValue.Size = new System.Drawing.Size(161, 17);
        this.lblReadValue.Location = new System.Drawing.Point(56, 120);
        this.lblReadValue.TabIndex = 4;
        this.lblReadValue.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.lblReadValue.TextAlign = System.Drawing.ContentAlignment.TopLeft;
        this.lblReadValue.Enabled = true;
        this.lblReadValue.Cursor = System.Windows.Forms.Cursors.Default;
        this.lblReadValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.lblReadValue.UseMnemonic = true;
        this.lblReadValue.Visible = true;
        this.lblReadValue.AutoSize = false;
        this.lblReadValue.BorderStyle = System.Windows.Forms.BorderStyle.None;
        this.lblReadValue.Name = "lblReadValue";
        this.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window;
        this.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue;
        this.lblShowLoadVal.Size = new System.Drawing.Size(73, 17);
        this.lblShowLoadVal.Location = new System.Drawing.Point(232, 88);
        this.lblShowLoadVal.TabIndex = 1;
        this.lblShowLoadVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.lblShowLoadVal.TextAlign = System.Drawing.ContentAlignment.TopLeft;
        this.lblShowLoadVal.Enabled = true;
        this.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default;
        this.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.lblShowLoadVal.UseMnemonic = true;
        this.lblShowLoadVal.Visible = true;
        this.lblShowLoadVal.AutoSize = false;
        this.lblShowLoadVal.BorderStyle = System.Windows.Forms.BorderStyle.None;
        this.lblShowLoadVal.Name = "lblShowLoadVal";
        this.lblLoadValue.BackColor = System.Drawing.SystemColors.Window;
        this.lblLoadValue.ForeColor = System.Drawing.SystemColors.WindowText;
        this.lblLoadValue.Size = new System.Drawing.Size(161, 17);
        this.lblLoadValue.Location = new System.Drawing.Point(56, 88);
        this.lblLoadValue.TabIndex = 3;
        this.lblLoadValue.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.lblLoadValue.TextAlign = System.Drawing.ContentAlignment.TopLeft;
        this.lblLoadValue.Enabled = true;
        this.lblLoadValue.Cursor = System.Windows.Forms.Cursors.Default;
        this.lblLoadValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.lblLoadValue.UseMnemonic = true;
        this.lblLoadValue.Visible = true;
        this.lblLoadValue.AutoSize = false;
        this.lblLoadValue.BorderStyle = System.Windows.Forms.BorderStyle.None;
        this.lblLoadValue.Name = "lblLoadValue";
        this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
        this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
        this.lblDemoFunction.Text = "Demonstration of 9513 Counter Functions.";
        this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
        this.lblDemoFunction.Size = new System.Drawing.Size(225, 41);
        this.lblDemoFunction.Location = new System.Drawing.Point(48, 16);
        this.lblDemoFunction.TabIndex = 0;
        this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.lblDemoFunction.Enabled = true;
        this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
        this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
        this.lblDemoFunction.UseMnemonic = true;
        this.lblDemoFunction.Visible = true;
        this.lblDemoFunction.AutoSize = false;
        this.lblDemoFunction.BorderStyle = System.Windows.Forms.BorderStyle.None;
        this.lblDemoFunction.Name = "lblDemoFunction";
        this.Controls.Add(cmdStopRead);
        this.Controls.Add(lblShowReadVal);
        this.Controls.Add(lblReadValue);
        this.Controls.Add(lblShowLoadVal);
        this.Controls.Add(lblLoadValue);
        this.Controls.Add(lblDemoFunction);
    }

#endregion

    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main() 
    {
        Application.Run(new frm9513Ctr());
    }
    

    private void cmdStopRead_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopRead.Click */
    {
        Application.Exit();
    }


    

}
}