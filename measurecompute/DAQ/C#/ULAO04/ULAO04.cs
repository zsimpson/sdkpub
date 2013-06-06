using System.Diagnostics;
using Microsoft.VisualBasic;
using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Collections;
using Microsoft.VisualBasic.CompilerServices;

//==========================================================================

// File:                         ULAO04.CS

// Library Call Demonstrated:    Mccdaq.MccBoard.AOutScan()
//								 with scan options = MccDaq.ScanOptions.ScaleData

// Purpose:                      Synchronously writes to Analog channels in the background.
//

// Demonstration:                Sends output to the D/A channels
//                               until a key is pressed.

// Other Library Calls:          MccDaq.MccService.ErrHandling()

// Special Requirements:         Board 0 must support Mccdaq.MccBoard.AOutScan().
//

// (c) Copyright 1995-2006, Measurement Computing Corp.
// All rights reserved.
//==========================================================================

namespace ULAO04
{
	internal class frmStatusDisplay : System.Windows.Forms.Form
	{
		const short BoardNum = 0; // Board number
		const int ChanCount = 2; // Number of channels in scan
		const int NumPoints = 2; // Number of data points to collect
		const int Count = ChanCount * NumPoints;
		
		//Create a new MccBoard object for Board 0
		private MccDaq.MccBoard DaqBoard;
		
		private double[] DAData = new double[Count]; // dimension an array to hold the output values
		private int MemHandle;
		public System.Windows.Forms.Label lblChan1ValH;
		public System.Windows.Forms.Label lblChan0ValH;
		public System.Windows.Forms.Label lblChan1ValL;
		public System.Windows.Forms.Label lblChan0ValL;
		public System.Windows.Forms.Label lblOutputH;
		public System.Windows.Forms.Label lblOutputL; // define a variable to contain the handle for
		private short UserTerm;

		public frmStatusDisplay()
		{	
			//This call is required by the Windows Form Designer.
			InitializeComponent();
			
			InitUL();
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

				// make sure the scan has stopped..
				DaqBoard.StopBackground(MccDaq.FunctionType.AoFunction);
			
				// be sure to free the memory buffer
				if (MemHandle != 0) 
					MccDaq.MccService.WinBufFree(MemHandle);
			}
			base.Dispose(Disposing);
		}
		
		private void frmStatusDisplay_Load(System.Object eventSender, System.EventArgs eventArgs)
		{
			lblChan0ValL.Text = DAData[0].ToString("0.00000000");
			lblChan1ValL.Text = DAData[1].ToString("0.00000000");
			lblChan0ValH.Text = DAData[2].ToString("0.00000000");
			lblChan1ValH.Text = DAData[3].ToString("0.00000000");
		}

		[STAThread]
		static void Main()
		{
			Application.Run(new frmStatusDisplay());
		}
		
		private void cmdStartBgnd_Click(System.Object eventSender, System.EventArgs eventArgs)
		{
			int CurIndex;
			int CurCount;
			short Status;
			MccDaq.ErrorInfo ULStat;
			MccDaq.ScanOptions Options;
			
			cmdStartBgnd.Enabled = false;
			cmdStartBgnd.Visible = false;
			cmdStopConvert.Enabled = true;
			cmdStopConvert.Visible = true;
			cmdQuit.Enabled = false;
			UserTerm = 0; // initialize user terminate flag

			//  Parameters:
			//    LowChan    :the lower channel of the scan
			//    HighChan   :the upper channel of the scan
			//    Count      :the number of D/A values to send
			//    Rate       :per channel sampling rate ((samples per second) per channel)
			//    DAData     :array of values to send to the scanned channels
			//    Options    :data send options
			FirstPoint = 0;
			int LowChan = 0;	// First analog output channel
			int HighChan = 1;	// Last analog output channel
			int Rate = 1000;	// Rate of data update (ignored if board does not support timed analog output)
			MccDaq.Range Gain = MccDaq.Range.Bip5Volts; // Ignored if gain is not programmable
			Options = MccDaq.ScanOptions.Background | MccDaq.ScanOptions.Continuous | MccDaq.ScanOptions.ScaleData;
			ULStat = DaqBoard.AOutScan( LowChan, HighChan, Count, ref Rate, Gain, MemHandle, Options);
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AoFunction);
			
			if (Status == MccDaq.MccBoard.Running)
			{
				lblShowStat.Text = "Running";
				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
			}
			
			tmrCheckStatus.Enabled = true;
			
		}
		
		private void tmrCheckStatus_Tick(System.Object eventSender, System.EventArgs eventArgs)
		{
			MccDaq.ErrorInfo ULStat;
			int CurIndex;
			int CurCount;
			short Status;
			
			// This timer will check the status of the background data collection
			
			// Parameters:
			//   BoardNum    :the number used by CB.CFG to describe this board
			//   Status     :current status of the background data collection
			//   CurCount   :current number of samples collected
			//   CurIndex   :index to the data buffer pointing to the start of the
			//                most recently collected scan
			//   FunctionType: A/D operation (MccDaq.FunctionType.AoFunction)
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AoFunction);		
			
			lblShowCount.Text = CurCount.ToString("D");
			lblShowIndex.Text = CurIndex.ToString("D");
			
			// Check if the background operation has finished. If it has, then
			// transfer the data from the memory buffer set up by Windows to an
			// array for use by Visual Basic
			// The BACKGROUND operation must be explicitly stopped
			
			if (Status == MccDaq.MccBoard.Running && UserTerm == 0)
			{
				lblShowStat.Text = "Running";
				ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AoFunction);

				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
			}
			else if (Status == MccDaq.MccBoard.Idle || UserTerm == 1)
			{
				lblShowStat.Text = "Idle";
				tmrCheckStatus.Enabled = false;
				
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AoFunction);

				cmdStartBgnd.Enabled = true;
				cmdStartBgnd.Visible = true;
				cmdStopConvert.Enabled = false;
				cmdStopConvert.Visible = false;
				cmdQuit.Enabled = true;
			}
			
		}
		
		private void cmdQuit_Click(System.Object eventSender, System.EventArgs eventArgs)
		{
			MccDaq.ErrorInfo ULStat;
			
			ULStat = MccDaq.MccService.WinBufFree(MemHandle); // Free up memory for use by
			// other programs

			Application.Exit();		
		}
		
		private void cmdStopConvert_Click(System.Object eventSender, System.EventArgs eventArgs)
		{
			
			UserTerm = 1;
			
		}
		
		#region "Windows Form Designer generated code "

		private System.ComponentModel.IContainer components;
		public System.Windows.Forms.ToolTip ToolTip1;
		public System.Windows.Forms.Button cmdQuit;
		public System.Windows.Forms.Timer tmrCheckStatus;
		public System.Windows.Forms.Button cmdStopConvert;
		public System.Windows.Forms.Button cmdStartBgnd;
		public System.Windows.Forms.Label lblShowCount;
		public System.Windows.Forms.Label lblCount;
		public System.Windows.Forms.Label lblShowIndex;
		public System.Windows.Forms.Label lblIndex;
		public System.Windows.Forms.Label lblShowStat;
		public System.Windows.Forms.Label lblStatus;
		public System.Windows.Forms.Label lblDemoFunction;
		//NOTE: The following procedure is required by the Windows Form Designer
		//It can be modified using the Windows Form Designer.
		//Do not modify it using the code editor.
		[System.Diagnostics.DebuggerStepThrough()]private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.ToolTip1 = new System.Windows.Forms.ToolTip(this.components);
			this.cmdQuit = new System.Windows.Forms.Button();
			this.tmrCheckStatus = new System.Windows.Forms.Timer(this.components);
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this.cmdStartBgnd = new System.Windows.Forms.Button();
			this.lblChan1ValH = new System.Windows.Forms.Label();
			this.lblChan0ValH = new System.Windows.Forms.Label();
			this.lblChan1ValL = new System.Windows.Forms.Label();
			this.lblChan0ValL = new System.Windows.Forms.Label();
			this.lblShowCount = new System.Windows.Forms.Label();
			this.lblCount = new System.Windows.Forms.Label();
			this.lblShowIndex = new System.Windows.Forms.Label();
			this.lblIndex = new System.Windows.Forms.Label();
			this.lblShowStat = new System.Windows.Forms.Label();
			this.lblStatus = new System.Windows.Forms.Label();
			this.lblOutputH = new System.Windows.Forms.Label();
			this.lblOutputL = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// cmdQuit
			// 
			this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
			this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdQuit.Location = new System.Drawing.Point(280, 208);
			this.cmdQuit.Name = "cmdQuit";
			this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdQuit.Size = new System.Drawing.Size(52, 26);
			this.cmdQuit.TabIndex = 5;
			this.cmdQuit.Text = "Quit";
			this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
			// 
			// tmrCheckStatus
			// 
			this.tmrCheckStatus.Interval = 200;
			this.tmrCheckStatus.Tick += new System.EventHandler(this.tmrCheckStatus_Tick);
			// 
			// cmdStopConvert
			// 
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Enabled = false;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(83, 72);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(180, 27);
			this.cmdStopConvert.TabIndex = 3;
			this.cmdStopConvert.Text = "Stop Background Operation";
			this.cmdStopConvert.Visible = false;
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			// 
			// cmdStartBgnd
			// 
			this.cmdStartBgnd.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartBgnd.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartBgnd.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStartBgnd.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartBgnd.Location = new System.Drawing.Point(83, 72);
			this.cmdStartBgnd.Name = "cmdStartBgnd";
			this.cmdStartBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartBgnd.Size = new System.Drawing.Size(180, 27);
			this.cmdStartBgnd.TabIndex = 4;
			this.cmdStartBgnd.Text = "Start Background Operation";
			this.cmdStartBgnd.Click += new System.EventHandler(this.cmdStartBgnd_Click);
			// 
			// lblChan1ValH
			// 
			this.lblChan1ValH.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1ValH.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1ValH.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1ValH.ForeColor = System.Drawing.Color.Blue;
			this.lblChan1ValH.Location = new System.Drawing.Point(200, 144);
			this.lblChan1ValH.Name = "lblChan1ValH";
			this.lblChan1ValH.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1ValH.Size = new System.Drawing.Size(81, 17);
			this.lblChan1ValH.TabIndex = 15;
			this.lblChan1ValH.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan0ValH
			// 
			this.lblChan0ValH.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0ValH.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0ValH.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0ValH.ForeColor = System.Drawing.Color.Blue;
			this.lblChan0ValH.Location = new System.Drawing.Point(112, 144);
			this.lblChan0ValH.Name = "lblChan0ValH";
			this.lblChan0ValH.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0ValH.Size = new System.Drawing.Size(81, 17);
			this.lblChan0ValH.TabIndex = 14;
			this.lblChan0ValH.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan1ValL
			// 
			this.lblChan1ValL.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1ValL.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1ValL.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1ValL.ForeColor = System.Drawing.Color.Blue;
			this.lblChan1ValL.Location = new System.Drawing.Point(200, 120);
			this.lblChan1ValL.Name = "lblChan1ValL";
			this.lblChan1ValL.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1ValL.Size = new System.Drawing.Size(81, 17);
			this.lblChan1ValL.TabIndex = 13;
			this.lblChan1ValL.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan0ValL
			// 
			this.lblChan0ValL.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0ValL.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0ValL.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0ValL.ForeColor = System.Drawing.Color.Blue;
			this.lblChan0ValL.Location = new System.Drawing.Point(112, 120);
			this.lblChan0ValL.Name = "lblChan0ValL";
			this.lblChan0ValL.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0ValL.Size = new System.Drawing.Size(81, 17);
			this.lblChan0ValL.TabIndex = 12;
			this.lblChan0ValL.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblShowCount
			// 
			this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCount.Location = new System.Drawing.Point(199, 224);
			this.lblShowCount.Name = "lblShowCount";
			this.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowCount.Size = new System.Drawing.Size(59, 14);
			this.lblShowCount.TabIndex = 11;
			// 
			// lblCount
			// 
			this.lblCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCount.Location = new System.Drawing.Point(84, 224);
			this.lblCount.Name = "lblCount";
			this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCount.Size = new System.Drawing.Size(104, 14);
			this.lblCount.TabIndex = 9;
			this.lblCount.Text = "Current Count:";
			this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblShowIndex
			// 
			this.lblShowIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowIndex.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowIndex.ForeColor = System.Drawing.Color.Blue;
			this.lblShowIndex.Location = new System.Drawing.Point(199, 200);
			this.lblShowIndex.Name = "lblShowIndex";
			this.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowIndex.Size = new System.Drawing.Size(52, 14);
			this.lblShowIndex.TabIndex = 10;
			// 
			// lblIndex
			// 
			this.lblIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblIndex.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblIndex.Location = new System.Drawing.Point(84, 200);
			this.lblIndex.Name = "lblIndex";
			this.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblIndex.Size = new System.Drawing.Size(104, 14);
			this.lblIndex.TabIndex = 8;
			this.lblIndex.Text = "Current Index:";
			this.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblShowStat
			// 
			this.lblShowStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowStat.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowStat.ForeColor = System.Drawing.Color.Blue;
			this.lblShowStat.Location = new System.Drawing.Point(224, 184);
			this.lblShowStat.Name = "lblShowStat";
			this.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowStat.Size = new System.Drawing.Size(66, 14);
			this.lblShowStat.TabIndex = 7;
			// 
			// lblStatus
			// 
			this.lblStatus.BackColor = System.Drawing.SystemColors.Window;
			this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblStatus.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblStatus.Location = new System.Drawing.Point(6, 184);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblStatus.Size = new System.Drawing.Size(212, 14);
			this.lblStatus.TabIndex = 6;
			this.lblStatus.Text = "Status of Background Operation:";
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblOutputH
			// 
			this.lblOutputH.BackColor = System.Drawing.SystemColors.Window;
			this.lblOutputH.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblOutputH.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblOutputH.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblOutputH.Location = new System.Drawing.Point(16, 144);
			this.lblOutputH.Name = "lblOutputH";
			this.lblOutputH.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblOutputH.Size = new System.Drawing.Size(81, 17);
			this.lblOutputH.TabIndex = 2;
			this.lblOutputH.Text = "Output(high):";
			this.lblOutputH.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblOutputL
			// 
			this.lblOutputL.BackColor = System.Drawing.SystemColors.Window;
			this.lblOutputL.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblOutputL.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblOutputL.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblOutputL.Location = new System.Drawing.Point(16, 120);
			this.lblOutputL.Name = "lblOutputL";
			this.lblOutputL.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblOutputL.Size = new System.Drawing.Size(81, 17);
			this.lblOutputL.TabIndex = 1;
			this.lblOutputL.Text = "Output(low):";
			this.lblOutputL.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblDemoFunction
			// 
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(6, 6);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(337, 50);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AOutScan() with scan option set to MccDaq.ScanOp" +
				"tions.ScaleData";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// frmStatusDisplay
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(350, 254);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cmdQuit,
																		  this.cmdStopConvert,
																		  this.cmdStartBgnd,
																		  this.lblChan1ValH,
																		  this.lblChan0ValH,
																		  this.lblChan1ValL,
																		  this.lblChan0ValL,
																		  this.lblShowCount,
																		  this.lblCount,
																		  this.lblShowIndex,
																		  this.lblIndex,
																		  this.lblShowStat,
																		  this.lblStatus,
																		  this.lblOutputH,
																		  this.lblOutputL,
																		  this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(188, 108);
			this.Name = "frmStatusDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library DaqOutScan()";
			this.Load += new System.EventHandler(this.frmStatusDisplay_Load);
			this.ResumeLayout(false);

		}
		#endregion
		
		#region "Universal Library Initialization - Expand this region to change error handling, etc."
		
		private void InitUL()
		{
			int FirstPoint;
			MccDaq.ErrorInfo ULStat;
			
			// Initiate error handling
			//  activating error handling will trap errors like
			//  bad channel numbers and non-configured conditions.
			//  Parameters:
			//    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop
			
			ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
			
			MemHandle = MccDaq.MccService.ScaledWinBufAlloc(Count); // set aside memory to hold data
			if (MemHandle == 0) 
				Application.Exit();

			DaqBoard = new MccDaq.MccBoard(0);
			
			// output (low)
			DAData[0] = 0;
			DAData[1] = 0;
			
			// output (high))
			DAData[2] = 5;
			DAData[3] = 5;
			
			FirstPoint = 0;
			
			ULStat = MccDaq.MccService.ScaledWinArrayToBuf(ref DAData[0], MemHandle, FirstPoint, Count);
			
		}
		#endregion
		
	}
}
