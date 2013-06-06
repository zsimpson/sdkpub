// ==============================================================================
//
//  File:                         ULCT06.CS
//
//  Library Call Demonstrated:    7266 Counter Functions
//                                Mccdaq.MccBoard.C7266Config()
//                                Mccdaq.MccBoard.CLoad32()
//                                Mccdaq.MccBoard.CIn32()
//
//  Purpose:                      Operate the counter.
//
//  Demonstration:                Configures, loads and checks
//                                the counter
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a 7266 Counter.
//
//                                These functions are only supported in the
//                                32 bit version of the Universal Library
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

namespace ULCT06
{
	public class frm7266Ctr : System.Windows.Forms.Form
	{	
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopRead;
		public Timer tmrReadCounter;
		public Label lblShowDirection;
		public Label lblDirection;
		public Label lblShowLoadVal;
		public Label lblShowMaxVal;
		public Label lblMaxCount;
		public Label lblShowReadVal;
		public Label lblReadValue;
		public Label lblLoadValue;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		const short CounterNum = 1; //  Counter number
	 
		public frm7266Ctr()
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

			
			//  Set the configurable operations of the counter
			//  Parameters:
			//          CounterNum     :the counter to be configured (0-5)
			//          Quadrature     :Select type of counter input
			//          CountingMode   :Slects how counter will operate
			//          IndexMode      :Selects what index signal will control
			//          InvertIndex    :Set to ENABLED id index signal is inverted
			//          FlagPins       :Select which signals will drive Flag pins
			//          GateEnable     :Set to ENABLED to use external gating signal */
			MccDaq.Quadrature Quadrature = MccDaq.Quadrature.X1Quad;
			MccDaq.CountingMode CountingMode = MccDaq.CountingMode.ModuloN;
			MccDaq.DataEncoding DataEncoding = MccDaq.DataEncoding.BinaryEncoding;
			MccDaq.IndexMode IndexMode = MccDaq.IndexMode.IndexDisabled;
			MccDaq.OptionState InvertIndex = MccDaq.OptionState.Disabled;
			MccDaq.FlagPins FlagPins = MccDaq.FlagPins.CarryBorrow;
			MccDaq.OptionState GateEnable = MccDaq.OptionState.Disabled;
			ULStat = DaqBoard.C7266Config(CounterNum, Quadrature, CountingMode, DataEncoding, IndexMode, InvertIndex, FlagPins, GateEnable);
			


			//  Send a starting value to the counter with Mccdaq.MccBoard.CLoad32()
			//   Parameters:
			//     RegName    :the counter to be loaded with the starting value
			//     LoadValue  :the starting value to place in the counter
			int LoadValue = 1000;

			//  Convert the value of the counter number to MccDaq.CounterRegister
			MccDaq.CounterRegister RegName = (MccDaq.CounterRegister)(MccDaq.CounterRegister.QuadCount1 + CounterNum -1);
			ULStat = DaqBoard.CLoad32(RegName, LoadValue);

			lblShowLoadVal.Text = LoadValue.ToString("0");

			LoadValue = 2000;
			RegName = (MccDaq.CounterRegister)(MccDaq.CounterRegister.QuadPreset1 + CounterNum - 1);

			ULStat = DaqBoard.CLoad32(RegName, LoadValue);
			lblShowMaxVal.Text = LoadValue.ToString("0");

			tmrReadCounter.Enabled = true;
		}

		private void tmrReadCounter_Tick(object eventSender, System.EventArgs eventArgs) 
		{
			
			tmrReadCounter.Stop();
			
			//  Read the counter value
			//  Parameters:
			//    CounterNum :the counter to be read
			//    Count    :the count value in the counter
			int Count = 0;
			MccDaq.ErrorInfo ULStat = DaqBoard.CIn32( CounterNum, out Count);
			

			lblShowReadVal.Text = Count.ToString("0");

			// Get the status information about the counter
			// Parameters:
			//		CounterNum	: the counter whose status we need
			//		StatusBits	: status information include direction of counter, as well as error and other information
			MccDaq.StatusBits StatusBits = 0;
			ULStat = DaqBoard.CStatus( CounterNum, out StatusBits);

			if ((StatusBits & MccDaq.StatusBits.Updown) != 0)
				lblShowDirection.Text = "UP";
			else
				lblShowDirection.Text = "DOWN";

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
			this.cmdStopRead = new System.Windows.Forms.Button();
			this.tmrReadCounter = new System.Windows.Forms.Timer(this.components);
			this.lblShowDirection = new System.Windows.Forms.Label();
			this.lblDirection = new System.Windows.Forms.Label();
			this.lblShowLoadVal = new System.Windows.Forms.Label();
			this.lblShowMaxVal = new System.Windows.Forms.Label();
			this.lblMaxCount = new System.Windows.Forms.Label();
			this.lblShowReadVal = new System.Windows.Forms.Label();
			this.lblReadValue = new System.Windows.Forms.Label();
			this.lblLoadValue = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopRead
			//
			this.cmdStopRead.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopRead.Location = new System.Drawing.Point(240, 264);
			this.cmdStopRead.Name = "cmdStopRead";
			this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopRead.Size = new System.Drawing.Size(54, 27);
			this.cmdStopRead.TabIndex = 4;
			this.cmdStopRead.Text = "Quit";
			this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
			//
			// tmrReadCounter
			//
			this.tmrReadCounter.Tick += new System.EventHandler(this.tmrReadCounter_Tick);
			//
			// lblShowDirection
			//
			this.lblShowDirection.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowDirection.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowDirection.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowDirection.ForeColor = System.Drawing.Color.Blue;
			this.lblShowDirection.Location = new System.Drawing.Point(232, 216);
			this.lblShowDirection.Name = "lblShowDirection";
			this.lblShowDirection.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowDirection.Size = new System.Drawing.Size(73, 17);
			this.lblShowDirection.TabIndex = 9;
			//
			// lblDirection
			//
			this.lblDirection.BackColor = System.Drawing.SystemColors.Window;
			this.lblDirection.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDirection.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDirection.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDirection.Location = new System.Drawing.Point(64, 216);
			this.lblDirection.Name = "lblDirection";
			this.lblDirection.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDirection.Size = new System.Drawing.Size(161, 17);
			this.lblDirection.TabIndex = 8;
			this.lblDirection.Text = "Direction = ";
			this.lblDirection.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowLoadVal
			//
			this.lblShowLoadVal.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowLoadVal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowLoadVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowLoadVal.ForeColor = System.Drawing.Color.Blue;
			this.lblShowLoadVal.Location = new System.Drawing.Point(232, 88);
			this.lblShowLoadVal.Name = "lblShowLoadVal";
			this.lblShowLoadVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowLoadVal.Size = new System.Drawing.Size(73, 17);
			this.lblShowLoadVal.TabIndex = 7;
			//
			// lblShowMaxVal
			//
			this.lblShowMaxVal.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowMaxVal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowMaxVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowMaxVal.ForeColor = System.Drawing.Color.Blue;
			this.lblShowMaxVal.Location = new System.Drawing.Point(232, 120);
			this.lblShowMaxVal.Name = "lblShowMaxVal";
			this.lblShowMaxVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowMaxVal.Size = new System.Drawing.Size(73, 17);
			this.lblShowMaxVal.TabIndex = 6;
			//
			// lblMaxCount
			//
			this.lblMaxCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblMaxCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblMaxCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblMaxCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblMaxCount.Location = new System.Drawing.Point(56, 120);
			this.lblMaxCount.Name = "lblMaxCount";
			this.lblMaxCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblMaxCount.Size = new System.Drawing.Size(161, 17);
			this.lblMaxCount.TabIndex = 5;
			this.lblMaxCount.Text = "Maximum count:";
			this.lblMaxCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowReadVal
			//
			this.lblShowReadVal.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowReadVal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowReadVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowReadVal.ForeColor = System.Drawing.Color.Blue;
			this.lblShowReadVal.Location = new System.Drawing.Point(232, 184);
			this.lblShowReadVal.Name = "lblShowReadVal";
			this.lblShowReadVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowReadVal.Size = new System.Drawing.Size(73, 17);
			this.lblShowReadVal.TabIndex = 1;
			//
			// lblReadValue
			//
			this.lblReadValue.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadValue.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadValue.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadValue.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblReadValue.Location = new System.Drawing.Point(56, 184);
			this.lblReadValue.Name = "lblReadValue";
			this.lblReadValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadValue.Size = new System.Drawing.Size(161, 17);
			this.lblReadValue.TabIndex = 3;
			this.lblReadValue.Text = "Value read from counter:";
			this.lblReadValue.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblLoadValue
			//
			this.lblLoadValue.BackColor = System.Drawing.SystemColors.Window;
			this.lblLoadValue.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblLoadValue.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblLoadValue.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblLoadValue.Location = new System.Drawing.Point(56, 88);
			this.lblLoadValue.Name = "lblLoadValue";
			this.lblLoadValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblLoadValue.Size = new System.Drawing.Size(161, 17);
			this.lblLoadValue.TabIndex = 2;
			this.lblLoadValue.Text = "Initial count for counter:";
			this.lblLoadValue.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(48, 16);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(225, 41);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of 7266 Counter Functions.";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			this.lblDemoFunction.Click += new System.EventHandler(this.lblDemoFunction_Click);
			//
			// frm7266Ctr
			//
			this.AcceptButton = this.cmdStopRead;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(339, 296);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopRead, this.lblShowDirection, this.lblDirection, this.lblShowLoadVal, this.lblShowMaxVal, this.lblMaxCount, this.lblShowReadVal, this.lblReadValue, this.lblLoadValue, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frm7266Ctr";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library 7266Counter Demo";
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frm7266Ctr());
		}
	    

		
		private void cmdStopRead_Click(object eventSender, System.EventArgs eventArgs) 
		{
			Application.Exit();
		}


		
		private void lblDemoFunction_Click(object sender, System.EventArgs e) 
		{


		}

	}
}