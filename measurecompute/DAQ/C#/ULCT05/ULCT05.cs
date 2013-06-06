// ==============================================================================
//
//  File:                         ULCT05.CS
//
//  Library Call Demonstrated:    8536 Counter Functions
//                                Mccdaq.MccBoard.C8536Init()
//                                Mccdaq.MccBoard.C8536Config()
//                                Mccdaq.MccBoard.CLoad()
//                                Mccdaq.MccBoard.CIn()
//
//  Purpose:                      Operate the counter.
//
//  Demonstration:                Configures, loads and reads the counter.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have an 8536 Counter.
//                                There must be a TTL freq. at cntr. 1 input.
//                                Gate line must be tied high.
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

namespace ULCT05
{
	public class frm8536Count : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdQuit;
		public Button cmdStart;
		public Timer tmrReadCounter;
		public Label lblCount;
		public Label Label1;
		public Label lblShowLoadVal;
		public Label lblCountLoaded;
		public Label lblNoteFreqIn;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		private int CounterNum;
	 
		public frm8536Count()
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


			// Init the counter for desired operation
			//   Parameters:
			//      ChipNum     :the chip to be setup
			//      Ctr1Output  :how the counter output is used
			short ChipNum = 1;
			MccDaq.CtrlOutput Ctr1Output = MccDaq.CtrlOutput.NotLinked;
			ULStat = DaqBoard.C8536Init(ChipNum, Ctr1Output);
			

			// Configure the counter for desired operation
			//   Parameters:
			//      CounterNum    :which counter
			//      OutputControl :which counter output signal is used
			//      RecycleMode   :reload at 0 ?
			//      TrigType      :trigger type
			CounterNum = 1;
			MccDaq.C8536OutputControl OutputControl = MccDaq.C8536OutputControl.ToggleOnTc;
			MccDaq.RecycleMode RecycleMode = MccDaq.RecycleMode.Recycle;
			MccDaq.C8536TriggerType TrigType = MccDaq.C8536TriggerType.HWStartTrig;
			ULStat = DaqBoard.C8536Config(CounterNum, OutputControl, RecycleMode, TrigType);
			
		}


		private void cmdStart_Click(object eventSender, System.EventArgs eventArgs) 
		{
			// Send a starting value to the counter with MccDaq.MccBoard.CLoad()
			//   Parameters:
			//      RegName    :the counter to be loading with the starting value
			//      LoadValue  :the starting value to place in the counter
			int LoadValue = 1000;
			MccDaq.CounterRegister RegName = MccDaq.CounterRegister.LoadReg1;
			MccDaq.ErrorInfo ULStat = DaqBoard.CLoad(RegName, LoadValue);
			

			// Start a timer to read counter at 500ms interval
			lblCountLoaded.Text = "The value loaded into LOADREG1 was: ";
			lblShowLoadVal.Text = LoadValue.ToString("0");

			tmrReadCounter.Enabled = true;
		}


		private void tmrReadCounter_Tick(object eventSender, System.EventArgs eventArgs) 
		{
			
			tmrReadCounter.Stop();

			// Read the counter value
			//   Parameters:
			//      CounterNum :the counter to be read
			//      Count      :the count value in the counter
			ushort Count = 0;
			MccDaq.ErrorInfo ULStat = DaqBoard.CIn( CounterNum, out Count);

			lblCount.Text = Count.ToString("0");

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
		this.components = new System.ComponentModel.Container();
		this.ToolTip1 = new System.Windows.Forms.ToolTip(this.components);
		this.cmdQuit = new System.Windows.Forms.Button();
		this.cmdStart = new System.Windows.Forms.Button();
		this.tmrReadCounter = new System.Windows.Forms.Timer(this.components);
		this.lblCount = new System.Windows.Forms.Label();
		this.Label1 = new System.Windows.Forms.Label();
		this.lblShowLoadVal = new System.Windows.Forms.Label();
		this.lblCountLoaded = new System.Windows.Forms.Label();
		this.lblNoteFreqIn = new System.Windows.Forms.Label();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.SuspendLayout();
		// 
		// cmdQuit
		// 
		this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
		this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdQuit.Location = new System.Drawing.Point(264, 200);
		this.cmdQuit.Name = "cmdQuit";
		this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdQuit.Size = new System.Drawing.Size(65, 33);
		this.cmdQuit.TabIndex = 2;
		this.cmdQuit.Text = "Quit";
		this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
		// 
		// cmdStart
		// 
		this.cmdStart.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStart.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStart.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStart.Location = new System.Drawing.Point(176, 200);
		this.cmdStart.Name = "cmdStart";
		this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStart.Size = new System.Drawing.Size(65, 33);
		this.cmdStart.TabIndex = 0;
		this.cmdStart.Text = "Start";
		this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
		// 
		// tmrReadCounter
		// 
		this.tmrReadCounter.Interval = 500;
		this.tmrReadCounter.Tick += new System.EventHandler(this.tmrReadCounter_Tick);
		// 
		// lblCount
		// 
		this.lblCount.BackColor = System.Drawing.SystemColors.Window;
		this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblCount.ForeColor = System.Drawing.Color.Blue;
		this.lblCount.Location = new System.Drawing.Point(256, 152);
		this.lblCount.Name = "lblCount";
		this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblCount.Size = new System.Drawing.Size(65, 17);
		this.lblCount.TabIndex = 1;
		// 
		// Label1
		// 
		this.Label1.BackColor = System.Drawing.SystemColors.Window;
		this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
		this.Label1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Label1.Location = new System.Drawing.Point(8, 152);
		this.Label1.Name = "Label1";
		this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.Label1.Size = new System.Drawing.Size(241, 17);
		this.Label1.TabIndex = 7;
		this.Label1.Text = "Value read from Counter 1: ";
		this.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowLoadVal
		// 
		this.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowLoadVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue;
		this.lblShowLoadVal.Location = new System.Drawing.Point(256, 120);
		this.lblShowLoadVal.Name = "lblShowLoadVal";
		this.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowLoadVal.Size = new System.Drawing.Size(65, 17);
		this.lblShowLoadVal.TabIndex = 6;
		// 
		// lblCountLoaded
		// 
		this.lblCountLoaded.BackColor = System.Drawing.SystemColors.Window;
		this.lblCountLoaded.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblCountLoaded.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblCountLoaded.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblCountLoaded.Location = new System.Drawing.Point(8, 120);
		this.lblCountLoaded.Name = "lblCountLoaded";
		this.lblCountLoaded.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblCountLoaded.Size = new System.Drawing.Size(241, 17);
		this.lblCountLoaded.TabIndex = 5;
		this.lblCountLoaded.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblNoteFreqIn
		// 
		this.lblNoteFreqIn.BackColor = System.Drawing.SystemColors.Window;
		this.lblNoteFreqIn.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblNoteFreqIn.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblNoteFreqIn.ForeColor = System.Drawing.Color.Red;
		this.lblNoteFreqIn.Location = new System.Drawing.Point(32, 72);
		this.lblNoteFreqIn.Name = "lblNoteFreqIn";
		this.lblNoteFreqIn.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblNoteFreqIn.Size = new System.Drawing.Size(233, 33);
		this.lblNoteFreqIn.TabIndex = 4;
		this.lblNoteFreqIn.Text = "NOTE: There must be a TTL frequency at the counter 1 input.";
		this.lblNoteFreqIn.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(24, 8);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(249, 41);
		this.lblDemoFunction.TabIndex = 3;
		this.lblDemoFunction.Text = "Demonstration of 8536 Counter Functions";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frm8536Count
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(342, 242);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdQuit,
																		this.cmdStart,
																		this.lblCount,
																		this.Label1,
																		this.lblShowLoadVal,
																		this.lblCountLoaded,
																		this.lblNoteFreqIn,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(73, 100);
		this.Name = "frm8536Count";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library 8536 Counter Demo";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frm8536Count());
		}
	    
		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdQuit.Click */
		{
			Application.Exit();
		}

	}
}