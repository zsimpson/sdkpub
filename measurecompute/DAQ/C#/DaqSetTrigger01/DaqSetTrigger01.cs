//=========================================================================

// File:                         DaqSetTrigger01.CS

// Library Call Demonstrated:    cbDaqSetTrigger()

// Purpose:                      Sets start and stop triggers. These triggers are
//                               used to initiate and terminate A/D conversion using
//                               Mccdaq.MccBoard.DaqInScan, with MccDaq.ScanOptions.ExtTrigger selected.

// Demonstration:                Sets start and stop triggers
//                               and displays the input channels data.

// Other Library Calls:          MccDaq.MccService.ErrHandling()
//                               Mccdaq.MccBoard.GetStatus()
//                               Mccdaq.MccBoard.StopBackground()
//                               Mccdaq.MccBoard.DConfigPort()

// Special Requirements:         Board 0 must support cbDaqInScan.
//								 Channel 0 should have a signal that
//								 transitions from below 2V to above applied.
//                               Counter 0 should have a TTL signal applied.

// (c) Copyright 1995-2006, Measurement Computing Corp.
// All rights reserved.
//==========================================================================



using System.Diagnostics;
using Microsoft.VisualBasic;
using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Collections;


namespace DaqSetTrigger01
{
	internal class frmStatusDisplay : System.Windows.Forms.Form
	{	
		const short BoardNum = 0; // Board number
		const int ChanCount = 3; // Number of channels in scan
		const int NumPoints = 1000; // Number of data points to collect
		const int NumElements = ChanCount * NumPoints;
		
		//Create a new MccBoard object for Board 0
		private MccDaq.MccBoard DaqBoard;
		
		private ushort[] ADData = new ushort[NumElements]; // dimension an array to hold the input values
		private int MemHandle; // define a variable to contain the handle for
		private short[] ChanArray = new short[ChanCount]; // array to hold channel queue information
		private MccDaq.ChannelType[] ChanTypeArray = new MccDaq.ChannelType[ChanCount]; // array to hold channel type information
		private MccDaq.Range[] GainArray = new MccDaq.Range[ChanCount]; // array to hold gain queue information
		
		private short UserTerm;
	    private System.Windows.Forms.Label label1;
		public System.Windows.Forms.Label[] lblADData;

		public frmStatusDisplay()
		{	
			//This call is required by the Windows Form Designer.
			InitializeComponent();

			// Note: Any change to label names requires a change to the corresponding array element
			lblADData = new System.Windows.Forms.Label[] { this._lblADData_0, this._lblADData_1, this._lblADData_2 };
			
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
				DaqBoard.StopBackground(MccDaq.FunctionType.DaqiFunction);
			
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
			
			ChanArray[1] = System.Convert.ToInt16(MccDaq.DigitalPortType.FirstPortA);
			ChanTypeArray[1] = MccDaq.ChannelType.Digital8;
			GainArray[1] = MccDaq.Range.NotUsed;
			
			ChanArray[2] = 0;
			ChanTypeArray[2] = MccDaq.ChannelType.Ctr16;
			GainArray[2] = MccDaq.Range.NotUsed;	
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
			object Options;
			int CBCount;
			int PretrigCount;

			MccDaq.TriggerSource TrigSource;
			MccDaq.TriggerSensitivity TrigSense;
			int TrigChan;
			MccDaq.ChannelType ChanType;
			MccDaq.Range Gain;
			float Variance;
			float Level;
			MccDaq.TriggerEvent TrigEvent;

			int Direction;
			int PortNum;
			
			cmdStartBgnd.Enabled = false;
			cmdStartBgnd.Visible = false;
			cmdStopConvert.Enabled = true;
			cmdStopConvert.Visible = true;
			cmdQuit.Enabled = false;
			UserTerm = 0; // initialize user terminate flag

			lblADData[0].Text = "";
			lblADData[1].Text = "";
			lblADData[2].Text = "";

			//configure FirstPortA for digital input
			PortNum = ChanArray[1];
			Direction = System.Convert.ToInt32(MccDaq.DigitalPortDirection.DigitalIn);
			ULStat = DaqBoard.DConfigPort((MccDaq.DigitalPortType) PortNum, (MccDaq.DigitalPortDirection) Direction);

 
			//Set Triggers
			//Parameters:
			//BoardNum    :the number used by CB.CFG to describe this board
			//TrigSource  :trigger source
			//TrigSense   :trigger sensitivity
			//TrigChan    :trigger channel
			//ChanType    :trigger channel type
			//Gain        :trigger channel gain
			//Level       :trigger Level
			//Variance    :trigger Variance
			//TrigEvent   :trigger event type
  			
			//Start trigger settings
			//     AD conversions are enabled when analog channel 0 makes a transition from below 2 V to above.*/
			TrigSource = MccDaq.TriggerSource.TrigAnalogSW;
			TrigSense = MccDaq.TriggerSensitivity.RisingEdge;
			TrigChan = ChanArray[0];
			ChanType = ChanTypeArray[0];
			Gain = GainArray[0];
			Level = 2;
			Variance = 0;
			TrigEvent = MccDaq.TriggerEvent.Start;
  			
			//Set start trigger
			ULStat = DaqBoard.DaqSetTrigger(TrigSource, TrigSense, TrigChan, ChanType, Gain, Level, Variance, TrigEvent);
  			
			//Stop trigger settings
			//  AD conversions are terminated when counter 0 reaches 100 counts.*/
			TrigSource = MccDaq.TriggerSource.TrigCounter;
			TrigSense = MccDaq.TriggerSensitivity.AboveLevel;
			TrigChan = ChanArray[2];
			ChanType = ChanTypeArray[2];
			Gain = GainArray[2];
			Level = 100;
			Variance = 0;
			TrigEvent = MccDaq.TriggerEvent.Stop;
  			
			//Set stop trigger
			ULStat = DaqBoard.DaqSetTrigger(TrigSource, TrigSense, TrigChan, ChanType, Gain, Level, Variance, TrigEvent);

			// Collect the values with cbDaqInScan()
			//  Parameters:
			//    BoardNum        :the number used by CB.CFG to describe this board
			//    ChanArray[]     :array of channel values
			//    ChanTypeArray[] : array of channel types
			//    GainArra[]      :array of gain values
			//    ChansCount      :the number of elements in the arrays (0=disable queue)
			//    PretrigCount    :number of pre-trigger A/D samples to collect
			//    CBCount         :the total number of A/D samples to collect
			//    CBRate          :sample rate in samples per second
			//    ADData[]        :the array for the collected data values
			//    Options         :data collection options
			
			PretrigCount = 0;
			CBCount = NumElements; // Number of data points to collect
			
			Options = MccDaq.ScanOptions.ConvertData | MccDaq.ScanOptions.Background | MccDaq.ScanOptions.Continuous | MccDaq.ScanOptions.ExtTrigger;
			CBRate = 100; // Acquire data at 100 Hz
			
			ULStat = DaqBoard.DaqInScan(ChanArray, ChanTypeArray, GainArray, ChanCount, ref CBRate, ref PretrigCount, ref CBCount, MemHandle, (MccDaq.ScanOptions) Options);
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqiFunction);
			
			if (Status == MccDaq.MccBoard.Running)
			{
				lblShowStartTrig.Text = "Waiting for trigger...";
				lblShowStopTrig.Text = "";
				lblShowStat.Text = "Running";
				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
			}
			
			tmrCheckStatus.Enabled = true;
			
		}
		
		
		private void tmrCheckStatus_Tick(System.Object eventSender, System.EventArgs eventArgs)
		{
			int FirstPoint;
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
			//   FunctionType: A/D operation (MccDaq.FunctionType.DaqiFunction)
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqiFunction);		
			
			lblShowCount.Text = CurCount.ToString("D");
			lblShowIndex.Text = CurIndex.ToString("D");
			
			// Check if the background operation has finished. If it has, then
			// transfer the data from the memory buffer set up by Windows to an
			// array for use by Visual Basic
			// The BACKGROUND operation must be explicitly stopped
			
			if (UserTerm == 0)
			{
				lblShowStat.Text = "Running";
				ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqiFunction);
				
				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
				
				FirstPoint = CurIndex;
				if (FirstPoint >= 0)
				{
					lblShowStartTrig.Text = "Triggered!";
					lblShowStopTrig.Text = "Waiting for trigger...";

					ULStat = MccDaq.MccService.WinBufToArray(MemHandle, out ADData[0], FirstPoint, ChanCount);
					
					if (Status == MccDaq.MccBoard.Idle)
					{
						lblShowStopTrig.Text = "Triggered!";
					}
					
					lblADData[0].Text = ADData[0].ToString("D");
					lblADData[1].Text = ADData[1].ToString("D");
					lblADData[2].Text = ADData[2].ToString("D");
				}
			}
			if (Status == MccDaq.MccBoard.Idle || UserTerm == 1)
			{
				lblShowStat.Text = "Idle";
				tmrCheckStatus.Enabled = false;
				
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DaqiFunction);
			
				cmdStartBgnd.Enabled = true;
				cmdStartBgnd.Visible = true;
				cmdStopConvert.Enabled = false;
				cmdStopConvert.Visible = false;
				cmdQuit.Enabled = true;
			}
			
		}
		
		private void cmdQuit_Click(System.Object eventSender, System.EventArgs eventArgs)
		{	
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); //  Free up memory for use by other programs
        
			MemHandle =0;

			Application.Exit();
			
		}
		
		private void cmdStopConvert_Click(System.Object eventSender, System.EventArgs eventArgs)
		{		
			UserTerm = 1;		
		}

	  private System.ComponentModel.IContainer components;
		#region "Windows Form Designer generated code "

		public System.Windows.Forms.ToolTip ToolTip1;
		public System.Windows.Forms.Button cmdQuit;
		public System.Windows.Forms.Timer tmrCheckStatus;
		public System.Windows.Forms.Button cmdStopConvert;
		public System.Windows.Forms.Button cmdStartBgnd;
		public System.Windows.Forms.Label lblShowStopTrig;
		public System.Windows.Forms.Label lblShowStartTrig;
		public System.Windows.Forms.Label lblStopTrig;
		public System.Windows.Forms.Label lblStartTrig;
		public System.Windows.Forms.Label lblShowCount;
		public System.Windows.Forms.Label lblCount;
		public System.Windows.Forms.Label lblShowIndex;
		public System.Windows.Forms.Label lblIndex;
		public System.Windows.Forms.Label lblShowStat;
		public System.Windows.Forms.Label lblStatus;
		public System.Windows.Forms.Label _lblADData_2;
		public System.Windows.Forms.Label lblChan2;
		public System.Windows.Forms.Label _lblADData_1;
		public System.Windows.Forms.Label lblChan1;
		public System.Windows.Forms.Label _lblADData_0;
		public System.Windows.Forms.Label lblChan0;
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
		  this.lblShowStopTrig = new System.Windows.Forms.Label();
		  this.lblShowStartTrig = new System.Windows.Forms.Label();
		  this.lblStopTrig = new System.Windows.Forms.Label();
		  this.lblStartTrig = new System.Windows.Forms.Label();
		  this.lblShowCount = new System.Windows.Forms.Label();
		  this.lblCount = new System.Windows.Forms.Label();
		  this.lblShowIndex = new System.Windows.Forms.Label();
		  this.lblIndex = new System.Windows.Forms.Label();
		  this.lblShowStat = new System.Windows.Forms.Label();
		  this.lblStatus = new System.Windows.Forms.Label();
		  this._lblADData_2 = new System.Windows.Forms.Label();
		  this.lblChan2 = new System.Windows.Forms.Label();
		  this._lblADData_1 = new System.Windows.Forms.Label();
		  this.lblChan1 = new System.Windows.Forms.Label();
		  this._lblADData_0 = new System.Windows.Forms.Label();
		  this.lblChan0 = new System.Windows.Forms.Label();
		  this.lblDemoFunction = new System.Windows.Forms.Label();
		  this.label1 = new System.Windows.Forms.Label();
		  this.SuspendLayout();
		  // 
		  // cmdQuit
		  // 
		  this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
		  this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
		  this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.cmdQuit.Location = new System.Drawing.Point(280, 320);
		  this.cmdQuit.Name = "cmdQuit";
		  this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdQuit.Size = new System.Drawing.Size(52, 26);
		  this.cmdQuit.TabIndex = 9;
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
		  this.cmdStopConvert.Location = new System.Drawing.Point(80, 88);
		  this.cmdStopConvert.Name = "cmdStopConvert";
		  this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdStopConvert.Size = new System.Drawing.Size(180, 27);
		  this.cmdStopConvert.TabIndex = 7;
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
		  this.cmdStartBgnd.Location = new System.Drawing.Point(80, 88);
		  this.cmdStartBgnd.Name = "cmdStartBgnd";
		  this.cmdStartBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdStartBgnd.Size = new System.Drawing.Size(180, 27);
		  this.cmdStartBgnd.TabIndex = 8;
		  this.cmdStartBgnd.Text = "Start Background Operation";
		  this.cmdStartBgnd.Click += new System.EventHandler(this.cmdStartBgnd_Click);
		  // 
		  // lblShowStopTrig
		  // 
		  this.lblShowStopTrig.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowStopTrig.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowStopTrig.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowStopTrig.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowStopTrig.Location = new System.Drawing.Point(144, 256);
		  this.lblShowStopTrig.Name = "lblShowStopTrig";
		  this.lblShowStopTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowStopTrig.Size = new System.Drawing.Size(185, 25);
		  this.lblShowStopTrig.TabIndex = 19;
		  // 
		  // lblShowStartTrig
		  // 
		  this.lblShowStartTrig.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowStartTrig.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowStartTrig.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowStartTrig.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowStartTrig.Location = new System.Drawing.Point(144, 232);
		  this.lblShowStartTrig.Name = "lblShowStartTrig";
		  this.lblShowStartTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowStartTrig.Size = new System.Drawing.Size(177, 25);
		  this.lblShowStartTrig.TabIndex = 18;
		  // 
		  // lblStopTrig
		  // 
		  this.lblStopTrig.BackColor = System.Drawing.SystemColors.Window;
		  this.lblStopTrig.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblStopTrig.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblStopTrig.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.lblStopTrig.Location = new System.Drawing.Point(16, 256);
		  this.lblStopTrig.Name = "lblStopTrig";
		  this.lblStopTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblStopTrig.Size = new System.Drawing.Size(121, 25);
		  this.lblStopTrig.TabIndex = 17;
		  this.lblStopTrig.Text = "Stop Trigger Status:";
		  this.lblStopTrig.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // lblStartTrig
		  // 
		  this.lblStartTrig.BackColor = System.Drawing.SystemColors.Window;
		  this.lblStartTrig.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblStartTrig.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblStartTrig.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.lblStartTrig.Location = new System.Drawing.Point(16, 232);
		  this.lblStartTrig.Name = "lblStartTrig";
		  this.lblStartTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblStartTrig.Size = new System.Drawing.Size(121, 25);
		  this.lblStartTrig.TabIndex = 16;
		  this.lblStartTrig.Text = "Start Trigger Status:";
		  this.lblStartTrig.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // lblShowCount
		  // 
		  this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowCount.Location = new System.Drawing.Point(200, 336);
		  this.lblShowCount.Name = "lblShowCount";
		  this.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowCount.Size = new System.Drawing.Size(58, 14);
		  this.lblShowCount.TabIndex = 15;
		  // 
		  // lblCount
		  // 
		  this.lblCount.BackColor = System.Drawing.SystemColors.Window;
		  this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblCount.Location = new System.Drawing.Point(80, 336);
		  this.lblCount.Name = "lblCount";
		  this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblCount.Size = new System.Drawing.Size(103, 14);
		  this.lblCount.TabIndex = 13;
		  this.lblCount.Text = "Current Count:";
		  this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // lblShowIndex
		  // 
		  this.lblShowIndex.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowIndex.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowIndex.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowIndex.Location = new System.Drawing.Point(200, 320);
		  this.lblShowIndex.Name = "lblShowIndex";
		  this.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowIndex.Size = new System.Drawing.Size(52, 14);
		  this.lblShowIndex.TabIndex = 14;
		  // 
		  // lblIndex
		  // 
		  this.lblIndex.BackColor = System.Drawing.SystemColors.Window;
		  this.lblIndex.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblIndex.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblIndex.Location = new System.Drawing.Point(80, 320);
		  this.lblIndex.Name = "lblIndex";
		  this.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblIndex.Size = new System.Drawing.Size(103, 14);
		  this.lblIndex.TabIndex = 12;
		  this.lblIndex.Text = "Current Index:";
		  this.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // lblShowStat
		  // 
		  this.lblShowStat.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowStat.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowStat.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowStat.Location = new System.Drawing.Point(224, 296);
		  this.lblShowStat.Name = "lblShowStat";
		  this.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowStat.Size = new System.Drawing.Size(66, 14);
		  this.lblShowStat.TabIndex = 11;
		  // 
		  // lblStatus
		  // 
		  this.lblStatus.BackColor = System.Drawing.SystemColors.Window;
		  this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblStatus.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblStatus.Location = new System.Drawing.Point(8, 296);
		  this.lblStatus.Name = "lblStatus";
		  this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblStatus.Size = new System.Drawing.Size(212, 14);
		  this.lblStatus.TabIndex = 10;
		  this.lblStatus.Text = "Status of Background Operation:";
		  this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblADData_2
		  // 
		  this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
		  this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblADData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
		  this._lblADData_2.Location = new System.Drawing.Point(152, 200);
		  this._lblADData_2.Name = "_lblADData_2";
		  this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblADData_2.Size = new System.Drawing.Size(105, 17);
		  this._lblADData_2.TabIndex = 6;
		  // 
		  // lblChan2
		  // 
		  this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan2.Location = new System.Drawing.Point(56, 200);
		  this.lblChan2.Name = "lblChan2";
		  this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan2.Size = new System.Drawing.Size(81, 17);
		  this.lblChan2.TabIndex = 3;
		  this.lblChan2.Text = "Counter 0:";
		  this.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblADData_1
		  // 
		  this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
		  this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblADData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
		  this._lblADData_1.Location = new System.Drawing.Point(152, 168);
		  this._lblADData_1.Name = "_lblADData_1";
		  this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblADData_1.Size = new System.Drawing.Size(105, 17);
		  this._lblADData_1.TabIndex = 5;
		  // 
		  // lblChan1
		  // 
		  this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan1.Location = new System.Drawing.Point(40, 168);
		  this.lblChan1.Name = "lblChan1";
		  this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan1.Size = new System.Drawing.Size(97, 17);
		  this.lblChan1.TabIndex = 2;
		  this.lblChan1.Text = "FIRSTPORTA:";
		  this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblADData_0
		  // 
		  this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
		  this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblADData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
		  this._lblADData_0.Location = new System.Drawing.Point(152, 144);
		  this._lblADData_0.Name = "_lblADData_0";
		  this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblADData_0.Size = new System.Drawing.Size(105, 17);
		  this._lblADData_0.TabIndex = 4;
		  // 
		  // lblChan0
		  // 
		  this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan0.Location = new System.Drawing.Point(56, 144);
		  this.lblChan0.Name = "lblChan0";
		  this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan0.Size = new System.Drawing.Size(81, 17);
		  this.lblChan0.TabIndex = 1;
		  this.lblChan0.Text = "Channel 0:";
		  this.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopRight;
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
		  this.lblDemoFunction.Size = new System.Drawing.Size(337, 26);
		  this.lblDemoFunction.TabIndex = 0;
		  this.lblDemoFunction.Text = "Demonstration of  MccBoard.DaqSetTrigger()";
		  this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // label1
		  // 
		  this.label1.ForeColor = System.Drawing.Color.Red;
		  this.label1.Location = new System.Drawing.Point(16, 32);
		  this.label1.Name = "label1";
		  this.label1.Size = new System.Drawing.Size(328, 48);
		  this.label1.TabIndex = 20;
		  this.label1.Text = "Trigger signals are needed for this sample. Signals required: ACH0 - signal that " +
			"transitions from below 2V to above. CNT0 should have a TTL signal applied.";
		  // 
		  // frmStatusDisplay
		  // 
		  this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		  this.BackColor = System.Drawing.SystemColors.Window;
		  this.ClientSize = new System.Drawing.Size(350, 365);
		  this.Controls.AddRange(new System.Windows.Forms.Control[] {
																	  this.label1,
																	  this.cmdQuit,
																	  this.cmdStopConvert,
																	  this.cmdStartBgnd,
																	  this.lblShowStopTrig,
																	  this.lblShowStartTrig,
																	  this.lblStopTrig,
																	  this.lblStartTrig,
																	  this.lblShowCount,
																	  this.lblCount,
																	  this.lblShowIndex,
																	  this.lblIndex,
																	  this.lblShowStat,
																	  this.lblStatus,
																	  this._lblADData_2,
																	  this.lblChan2,
																	  this._lblADData_1,
																	  this.lblChan1,
																	  this._lblADData_0,
																	  this.lblChan0,
																	  this.lblDemoFunction});
		  this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.ForeColor = System.Drawing.Color.Blue;
		  this.Location = new System.Drawing.Point(188, 108);
		  this.Name = "frmStatusDisplay";
		  this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		  this.Text = "Universal Library DaqSetTrigger()";
		  this.Load += new System.EventHandler(this.frmStatusDisplay_Load);
		  this.ResumeLayout(false);

		}
		#endregion
		
		#region "Universal Library Initialization - Expand this region to change error handling, etc."
		
		private void InitUL()
		{
			//			short i;
			MccDaq.ErrorInfo ULStat;
			
			// Initiate error handling
			//  activating error handling will trap errors like
			//  bad channel numbers and non-configured conditions.
			//  Parameters:
			//    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop
			
			ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
			
			MemHandle = MccDaq.MccService.WinBufAlloc(NumElements); // set aside memory to hold data
			if (MemHandle == 0) 
				Application.Exit();

			DaqBoard = new MccDaq.MccBoard(0);
			
		}
		#endregion
		
	}
}
