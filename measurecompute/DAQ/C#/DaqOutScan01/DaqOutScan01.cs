using System.Diagnostics;
using Microsoft.VisualBasic;
using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Collections;
using Microsoft.VisualBasic.CompilerServices;

//==========================================================================

// File:                         DaqOutScan01.CS

// Library Call Demonstrated:    Mccdaq.MccBoard.DaqOutScan(), Background mode

// Purpose:                      Synchronously writes to an Analog channel and a Digital port in the background.
//

// Demonstration:                Sends output to the D/A channels
//                               until a key is pressed.

// Other Library Calls:          MccDaq.MccService.ErrHandling()
//                               Mccdaq.MccBoard.DConfigPort()

// Special Requirements:         Board 0 must support Mccdaq.MccBoard.DaqOutScan().
//

// (c) Copyright 1995-2006, Measurement Computing Corp.
// All rights reserved.
//==========================================================================

namespace DaqOutScan01
{
	internal class frmStatusDisplay : System.Windows.Forms.Form
	{
		const short BoardNum = 0; // Board number
		const int ChanCount = 2; // Number of channels in scan
		const int NumPoints = 2; // Number of data points to collect
		const int Count = ChanCount * NumPoints;
		
		//Create a new MccBoard object for Board 0
		private MccDaq.MccBoard DaqBoard;
		
		private ushort[] DAData = new ushort[Count]; // dimension an array to hold the output values
		private int MemHandle; // define a variable to contain the handle for
		private short[] ChanArray = new short[ChanCount]; // array to hold channel queue information
		private MccDaq.ChannelType[] ChanTypeArray = new MccDaq.ChannelType[ChanCount]; // array to hold channel type information
		private MccDaq.Range[] GainArray = new MccDaq.Range[ChanCount]; // array to hold gain queue information
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
				DaqBoard.StopBackground(MccDaq.FunctionType.DaqoFunction);
			
				// be sure to free the memory buffer
				if (MemHandle != 0) 
					MccDaq.MccService.WinBufFree(MemHandle);
			}
			base.Dispose(Disposing);
		}
		
		private void frmStatusDisplay_Load(System.Object eventSender, System.EventArgs eventArgs)
		{
			//load the arrays with values
			ChanArray[0] = 0;
			ChanTypeArray[0] = MccDaq.ChannelType.Analog;
			GainArray[0] = MccDaq.Range.Bip10Volts;
			
			lblChan0.Text = "0";
			lblChan0Type.Text = "Analog";
			lblChan0Gain.Text = "±10 Volts";
			
			ChanArray[1] = System.Convert.ToInt16(MccDaq.DigitalPortType.FirstPortA);
			ChanTypeArray[1] = MccDaq.ChannelType.Digital16;
			GainArray[1] = MccDaq.Range.NotUsed;
			
			lblChan1.Text = "FirstPortA";
			lblChan1Type.Text = "Digital16";
			lblChan1Gain.Text = "NotUsed";		
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
			int CBRate;
			MccDaq.ScanOptions Options;

			MccDaq.DigitalPortDirection Direction;
			MccDaq.DigitalPortType PortNum;
			
			cmdStartBgnd.Enabled = false;
			cmdStartBgnd.Visible = false;
			cmdStopConvert.Enabled = true;
			cmdStopConvert.Visible = true;
			cmdQuit.Enabled = false;
			UserTerm = 0; // initialize user terminate flag
				
			//FirstPortA is treated as a 16-bit port; therefore FirtstPortA and FirstPortB must be configured for digital output
			PortNum = MccDaq.DigitalPortType.FirstPortA;
			Direction = MccDaq.DigitalPortDirection.DigitalOut;
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);
  			
			PortNum = MccDaq.DigitalPortType.FirstPortB;
			Direction = MccDaq.DigitalPortDirection.DigitalOut;
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);

			// Collect the values with cbDaqInScan()
			//  Parameters:
			//    BoardNum        :the number used by CB.CFG to describe this board
			//    ChanArray[]     :array of channel values
			//    ChanTypeArray[] : array of channel types
			//    GainArray[]     :array of gain values
			//    ChansCount      :the number of elements in the arrays (0=disable queue)
			//    Count           :the total number of A/D samples to collect
			//    CBRate          :sample rate in samples per second
			//    ADData[]        :the array for the collected data values
			//    Options         :data collection options
			
			Options = MccDaq.ScanOptions.Background | MccDaq.ScanOptions.Continuous | MccDaq.ScanOptions.NonStreamedIO;
			CBRate = 1000; // Generate data at 1000 Hz
			
			ULStat = DaqBoard.DaqOutScan(ChanArray, ChanTypeArray, GainArray, ChanCount, ref CBRate, Count, MemHandle, Options);
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqoFunction);
			
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
			//   FunctionType: A/D operation (MccDaq.FunctionType.DaqoFunction)
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqoFunction);		
			
			lblShowCount.Text = CurCount.ToString("D");
			lblShowIndex.Text = CurIndex.ToString("D");
			
			// Check if the background operation has finished. If it has, then
			// transfer the data from the memory buffer set up by Windows to an
			// array for use by Visual Basic
			// The BACKGROUND operation must be explicitly stopped
			
			if (Status == MccDaq.MccBoard.Running && UserTerm == 0)
			{
				lblShowStat.Text = "Running";
				ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqoFunction);

				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
			}
			else if (Status == MccDaq.MccBoard.Idle || UserTerm == 1)
			{
				lblShowStat.Text = "Idle";
				tmrCheckStatus.Enabled = false;
				
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DaqoFunction);

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
		public System.Windows.Forms.Label lblChan1;
		public System.Windows.Forms.Label lblChan0;
		public System.Windows.Forms.Label lblChan;
		public System.Windows.Forms.Label lblChan1Gain;
		public System.Windows.Forms.Label lblChan0Gain;
		public System.Windows.Forms.Label lblChan1Type;
		public System.Windows.Forms.Label lblChan0Type;
		public System.Windows.Forms.Label lblShowCount;
		public System.Windows.Forms.Label lblCount;
		public System.Windows.Forms.Label lblShowIndex;
		public System.Windows.Forms.Label lblIndex;
		public System.Windows.Forms.Label lblShowStat;
		public System.Windows.Forms.Label lblStatus;
		public System.Windows.Forms.Label lblChan2;
		public System.Windows.Forms.Label lblType;
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
			this.lblChan1 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblChan = new System.Windows.Forms.Label();
			this.lblChan1Gain = new System.Windows.Forms.Label();
			this.lblChan0Gain = new System.Windows.Forms.Label();
			this.lblChan1Type = new System.Windows.Forms.Label();
			this.lblChan0Type = new System.Windows.Forms.Label();
			this.lblShowCount = new System.Windows.Forms.Label();
			this.lblCount = new System.Windows.Forms.Label();
			this.lblShowIndex = new System.Windows.Forms.Label();
			this.lblIndex = new System.Windows.Forms.Label();
			this.lblShowStat = new System.Windows.Forms.Label();
			this.lblStatus = new System.Windows.Forms.Label();
			this.lblChan2 = new System.Windows.Forms.Label();
			this.lblType = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// cmdQuit
			// 
			this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
			this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdQuit.Location = new System.Drawing.Point(280, 240);
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
			// lblChan1
			// 
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.Color.Blue;
			this.lblChan1.Location = new System.Drawing.Point(200, 112);
			this.lblChan1.Name = "lblChan1";
			this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1.Size = new System.Drawing.Size(81, 17);
			this.lblChan1.TabIndex = 18;
			this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan0
			// 
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.Color.Blue;
			this.lblChan0.Location = new System.Drawing.Point(112, 112);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.Size = new System.Drawing.Size(81, 17);
			this.lblChan0.TabIndex = 17;
			this.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan
			// 
			this.lblChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan.Location = new System.Drawing.Point(16, 112);
			this.lblChan.Name = "lblChan";
			this.lblChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan.Size = new System.Drawing.Size(81, 17);
			this.lblChan.TabIndex = 16;
			this.lblChan.Text = "Channel:";
			this.lblChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblChan1Gain
			// 
			this.lblChan1Gain.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1Gain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1Gain.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1Gain.ForeColor = System.Drawing.Color.Blue;
			this.lblChan1Gain.Location = new System.Drawing.Point(200, 160);
			this.lblChan1Gain.Name = "lblChan1Gain";
			this.lblChan1Gain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1Gain.Size = new System.Drawing.Size(81, 17);
			this.lblChan1Gain.TabIndex = 15;
			this.lblChan1Gain.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan0Gain
			// 
			this.lblChan0Gain.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0Gain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0Gain.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0Gain.ForeColor = System.Drawing.Color.Blue;
			this.lblChan0Gain.Location = new System.Drawing.Point(112, 160);
			this.lblChan0Gain.Name = "lblChan0Gain";
			this.lblChan0Gain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0Gain.Size = new System.Drawing.Size(81, 17);
			this.lblChan0Gain.TabIndex = 14;
			this.lblChan0Gain.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan1Type
			// 
			this.lblChan1Type.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1Type.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1Type.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1Type.ForeColor = System.Drawing.Color.Blue;
			this.lblChan1Type.Location = new System.Drawing.Point(200, 136);
			this.lblChan1Type.Name = "lblChan1Type";
			this.lblChan1Type.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1Type.Size = new System.Drawing.Size(81, 17);
			this.lblChan1Type.TabIndex = 13;
			this.lblChan1Type.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblChan0Type
			// 
			this.lblChan0Type.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0Type.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0Type.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0Type.ForeColor = System.Drawing.Color.Blue;
			this.lblChan0Type.Location = new System.Drawing.Point(112, 136);
			this.lblChan0Type.Name = "lblChan0Type";
			this.lblChan0Type.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0Type.Size = new System.Drawing.Size(81, 17);
			this.lblChan0Type.TabIndex = 12;
			this.lblChan0Type.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblShowCount
			// 
			this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCount.Location = new System.Drawing.Point(199, 256);
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
			this.lblCount.Location = new System.Drawing.Point(84, 256);
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
			this.lblShowIndex.Location = new System.Drawing.Point(199, 232);
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
			this.lblIndex.Location = new System.Drawing.Point(84, 232);
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
			this.lblShowStat.Location = new System.Drawing.Point(224, 216);
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
			this.lblStatus.Location = new System.Drawing.Point(6, 216);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblStatus.Size = new System.Drawing.Size(212, 14);
			this.lblStatus.TabIndex = 6;
			this.lblStatus.Text = "Status of Background Operation:";
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblChan2
			// 
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan2.Location = new System.Drawing.Point(16, 160);
			this.lblChan2.Name = "lblChan2";
			this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan2.Size = new System.Drawing.Size(81, 17);
			this.lblChan2.TabIndex = 2;
			this.lblChan2.Text = "Gain:";
			this.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblType
			// 
			this.lblType.BackColor = System.Drawing.SystemColors.Window;
			this.lblType.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblType.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblType.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblType.Location = new System.Drawing.Point(16, 136);
			this.lblType.Name = "lblType";
			this.lblType.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblType.Size = new System.Drawing.Size(81, 17);
			this.lblType.TabIndex = 1;
			this.lblType.Text = "Type:";
			this.lblType.TextAlign = System.Drawing.ContentAlignment.TopRight;
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
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DaqOutScan() with scan option set to MccDaq.Scan" +
				"Options.Background + MccDaq.ScanOptions.Continuous + MccDaq.ScanOptions.NonStrea" +
				"medIO";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// frmStatusDisplay
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(350, 284);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cmdQuit,
																		  this.cmdStopConvert,
																		  this.cmdStartBgnd,
																		  this.lblChan1,
																		  this.lblChan0,
																		  this.lblChan,
																		  this.lblChan1Gain,
																		  this.lblChan0Gain,
																		  this.lblChan1Type,
																		  this.lblChan0Type,
																		  this.lblShowCount,
																		  this.lblCount,
																		  this.lblShowIndex,
																		  this.lblIndex,
																		  this.lblShowStat,
																		  this.lblStatus,
																		  this.lblChan2,
																		  this.lblType,
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
			
			MemHandle = MccDaq.MccService.WinBufAlloc(Count); // set aside memory to hold data
			if (MemHandle == 0) 
				Application.Exit();

			DaqBoard = new MccDaq.MccBoard(0);
			
			// output (low)
			DAData[0] = 0;
			DAData[1] = 0;
			
			// output (high))
			DAData[2] = 65535;
			DAData[3] = 65535;
			
			FirstPoint = 0;
			
			ULStat = MccDaq.MccService.WinArrayToBuf(ref DAData[0], MemHandle, FirstPoint, Count);
			
		}
		#endregion
		
	}
}
