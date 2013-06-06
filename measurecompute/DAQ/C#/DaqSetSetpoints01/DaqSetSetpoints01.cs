//=====================================================================================

// File:                         DaqSetSetpoints01.CS

// Library Call Demonstrated:    Mccdaq.MccBoard.DaqSetSetpoints()

// Purpose:                      Demonstrate the configuration and usage of setpoints
//                               Including Adding the setpoint status to the scanlist and
//                               asynchronous reads of the setpoint status

// Demonstration:                Displays the input channels data.
//                               Calls cbGetStatus to determine the status
//                               of the background operation. Updates the
//                               display until Stop Background button is pressed.

// Other Library Calls:          Mccdaq.MccBoard.DaqInScan()
//								 MccDaq.MccService.ErrHandling()
//                               Mccdaq.MccBoard.GetStatus()
//                               Mccdaq.MccBoard.StopBackground()
//                               Mccdaq.MccBoard.DConfigPort()


// Special Requirements:         Board 0 must support DaqSetSetpoints.
//

// (c) Copyright 1995-2007, Measurement Computing Corp.
// All rights reserved.
//========================================================================================

using System.Diagnostics;
using Microsoft.VisualBasic;
using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Collections;


namespace DaqSetSetpoints01
{
	public class frmStatusDisplay : System.Windows.Forms.Form
	{
		const int BoardNum = 0; // Board number
		const int ChanCount = 4; // Number of channels in scan
		const int NumPoints = 1000; // Number of data points to collect
		const int NumElements = ChanCount * NumPoints;

	    const int SetpointCount = 3;         // Number of setpoints
		
		private MccDaq.MccBoard DaqBoard;
		
		private ushort[] ADData = new ushort[NumElements]; // dimension an array to hold the input values
		private int MemHandle; // define a variable to contain the handle for
		// memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		private short[] ChanArray = new short[ChanCount]; // array to hold channel queue information
		private MccDaq.ChannelType[] ChanTypeArray = new MccDaq.ChannelType[ChanCount]; // array to hold channel type information
		private MccDaq.Range[] GainArray = new MccDaq.Range[ChanCount]; // array to hold gain queue information
		
		private float[] LimitAArray = new float[SetpointCount];
		private float[] LimitBArray = new float[SetpointCount];
		private float[] Reserved = new float[0];
		private MccDaq.SetpointFlag[] SetpointFlagsArray = new MccDaq.SetpointFlag[SetpointCount];
		private MccDaq.SetpointOutput[] SetpointOutputArray = new MccDaq.SetpointOutput[SetpointCount];
		private float[] Output1Array = new float[SetpointCount];
		private float[] Output2Array = new float[SetpointCount];
		private float[] OutputMask1Array = new float[SetpointCount];
		private float[] OutputMask2Array = new float[SetpointCount];

		private short UserTerm;
		public System.Windows.Forms.Label[] lblADData;

		public frmStatusDisplay()
		{
			
			//This call is required by the Windows Form Designer.
			InitializeComponent();

			// Note: Any change to label names requires a change to the corresponding array element
			lblADData = new System.Windows.Forms.Label[] { this._lblADData_0, this._lblADData_1, this._lblADData_2, this._lblADData_3 };
			
			InitUL();
		}
		//Form overrides dispose to clean up the component list.
		protected override void Dispose(bool Disposing)
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
			ChanTypeArray[0] = MccDaq.ChannelType.Analog | MccDaq.ChannelType.SetpointEnable;
			GainArray[0] = MccDaq.Range.Bip10Volts;
			
			ChanArray[1] = 1;
			ChanTypeArray[1] = MccDaq.ChannelType.Analog | MccDaq.ChannelType.SetpointEnable;
			GainArray[1] = MccDaq.Range.Bip10Volts;
			
			ChanArray[2] = System.Convert.ToInt16(MccDaq.DigitalPortType.FirstPortA);
			ChanTypeArray[2] = MccDaq.ChannelType.Digital8 | MccDaq.ChannelType.SetpointEnable;
			GainArray[2] = MccDaq.Range.NotUsed;
			
			ChanArray[3] = 0;
			ChanTypeArray[3] = MccDaq.ChannelType.SetpointStatus;
			GainArray[3] = MccDaq.Range.NotUsed;

		    /* setpoint configurations for ChanArray[0]  (CH0)*/
			SetpointFlagsArray[0] = MccDaq.SetpointFlag.LessThanLimitA | MccDaq.SetpointFlag.UpdateOnTrueAndFalse;	
			SetpointOutputArray[0] = MccDaq.SetpointOutput.DAC0;   // setpoint result outputs a value to Analog Out 0
			LimitAArray[0] = 3;					// if CH0 less than 3.0 volts apply output1, else apply output2
			LimitBArray[0] = 0;					// ignored when LessThanLimitA flag is used
			Output1Array[0] = 5;				// output 5.0 volts on Analog Out 0
			Output2Array[0] = -5;				// output -5.0 volts on Analog Out 0
			OutputMask1Array[0] = 0;			// ignored for DAC0 output type 
			OutputMask2Array[0] = 0;			// ignored for DAC0 output type 

			/* setpoint configurations for ChanArray[1] (CH1)*/
			SetpointFlagsArray[1] = MccDaq.SetpointFlag.GreaterThanLimitB | MccDaq.SetpointFlag.UpdateOnTrueAndFalse;	
			SetpointOutputArray[1] = MccDaq.SetpointOutput.FirstPortC;	// setpoint result outputs a value to digital port C	
			LimitAArray[1] = 0;						// ignored when GreaterThanLimitB flag is used				
			LimitBArray[1] = 2;						// if CH1 greater than 2.0 volts apply output1
			Output1Array[1] = 0x55;              	// output a bit pattern of 01010101 to digital port C
			Output2Array[1] = 0xAA;	                // output a bit pattern of 10101010 to digital port C
			OutputMask1Array[1] = 0x0F;            	// output the value of 'out1' on low nibble only
			OutputMask2Array[1] = 0x0F;           	// output the value of 'out2' on low nibble only 

			/* setpoint configurations for ChanArray[2] (FIRSTPORTA)*/
			SetpointFlagsArray[2] = MccDaq.SetpointFlag.EqualLimitA | MccDaq.SetpointFlag.UpdateOnTrueOnly;	
			SetpointOutputArray[2] = MccDaq.SetpointOutput.TMR0;	// setpoint result outputs a value to Timer 0	
			LimitAArray[2] = 0x0F;				// if FirstPortA equal 00001111 bit pattern apply output1				
			LimitBArray[2] = 2;					// ignored when EqualLimitA flag is used
			Output1Array[2] = 100;				// output a 100Hz square wave on Timer 0
			Output2Array[2] = 0;				// ignored when SF_UPDATEON_TRUEONLY flag is used
			OutputMask1Array[2] = 0;			// ignored for 'TMR0' output type 
			OutputMask2Array[2] = 0;			// ignored for 'TMR0' output type 
		
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
			int Rate;
			MccDaq.ScanOptions Options;
			int Count;
			int PretrigCount;
			
			cmdStartBgnd.Enabled = false;
			cmdStartBgnd.Visible = false;
			cmdStopConvert.Enabled = true;
			cmdStopConvert.Visible = true;
			cmdQuit.Enabled = false;
			UserTerm = 0; // initialize user terminate flag

		  /* configure setpoints with cbDaqSetSetpoints()
			Parameters:
				BoardNum				:the number used by CB.CFG to describe this board
				LimitAArray[]			:array of LimitA values
				LimitBArray[]			:array of LimitB values
				SetpointFlagsArray[]	:array of Setpoint flags
				SetpointOutputArray[]   :array of output channels
				Output1Array[]			:array of output1 values
				Output2Array[]			:array of output2 values
				OutputMask1Array[]		:array of output masks for output1
				OutputMask2Array[]      :array of output masks for output2 
				SetpointCount           :Number of setpoints  */
	
		    ULStat =DaqBoard.DaqSetSetpoints (LimitAArray, LimitBArray, Reserved, SetpointFlagsArray, SetpointOutputArray,
											  Output1Array, Output2Array, OutputMask1Array, OutputMask2Array, SetpointCount);
			

			MccDaq.DigitalPortDirection Direction;
			MccDaq.DigitalPortType PortNum;

			//configure FirstPortA for digital input
			PortNum = (MccDaq.DigitalPortType) ChanArray[2];
			Direction = MccDaq.DigitalPortDirection.DigitalIn;
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);
			
			// Collect the values with cbDaqInScan()
			//  Parameters:
			//    BoardNum        :the number used by CB.CFG to describe this board
			//    ChanArray[]     :array of channel values
			//    ChanTypeArray[] : array of channel types
			//    GainArray[]     :array of gain values
			//    ChanCount       :the number of elements in the arrays (0=disable queue)
			//    PretrigCount    :number of pre-trigger A/D samples to collect
			//    Count			  :the total number of A/D samples to collect
			//    Rate			  :sample rate in samples per second
			//    ADData[]        :the array for the collected data values
			//    Options         :data collection options
			
			PretrigCount = 0;
			Count = NumElements; // Number of data points to collect
			Options =MccDaq.ScanOptions.ConvertData |MccDaq.ScanOptions.Background | MccDaq.ScanOptions.Continuous;
			Rate = 100; // Acquire data at 100 Hz		
			
			ULStat = DaqBoard.DaqInScan(ChanArray, ChanTypeArray, GainArray, ChanCount, ref Rate, ref PretrigCount, ref Count, MemHandle, Options);
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqiFunction);
			
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
			int FirstPoint;
			MccDaq.ErrorInfo ULStat;
			int CurIndex;
			int CurCount;
			short Status;
		    float EngUnits = 0;
			
			tmrCheckStatus.Stop();
			
			// This timer will check the status of the background data collection
			
			// Parameters:
			//   BoardNum   :the number used by CB.CFG to describe this board
			//   Status     :current status of the background data collection
			//   CurCount   :current number of samples collected
			//   CurIndex   :index to the data buffer pointing to the start of the
			//                most recently collected scan
			//   FunctionType: A/D operation (DAQIFUNCTION)
			
			ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqiFunction);
					
			lblShowCount.Text = CurCount.ToString("D");
			lblShowIndex.Text = CurIndex.ToString("D");
			
			// Check if the background operation has finished. If it has, then
			// transfer the data from the memory buffer set up by Windows to an
			// array for use by Visual Basic
			// The BACKGROUND operation must be explicitly stopped
			
			if (Status == MccDaq.MccBoard.Running && UserTerm == 0)
			{
				lblShowStat.Text = "Running";
				ULStat = DaqBoard.GetStatus(out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DaqiFunction);
				
				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
				
				FirstPoint = CurIndex;
				if (FirstPoint >= 0)
				{
					ULStat = MccDaq.MccService.WinBufToArray(MemHandle, out ADData[0], FirstPoint, ChanCount);
					
				    DaqBoard.ToEngUnits(GainArray[0], ADData[0], out EngUnits);
					lblADData[0].Text = String.Format("{0:f4}",EngUnits) + " Volts";
				    DaqBoard.ToEngUnits(GainArray[1], ADData[1], out EngUnits);
					lblADData[1].Text = String.Format("{0:f4}",EngUnits) + " Volts";
					lblADData[2].Text = "0x" + String.Format("{0:X2}",ADData[2]);
				    lblADData[3].Text = "0x" + String.Format("{0:X4}",ADData[3]);
				}
				tmrCheckStatus.Start();
			}
			else if (Status == MccDaq.MccBoard.Idle || UserTerm == 1)
			{
				lblShowStat.Text = "Idle";
				tmrCheckStatus.Stop();
				
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
			MccDaq.ErrorInfo ULStat;
			
			ULStat = MccDaq.MccService.WinBufFree(MemHandle); // Free up memory for use by

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
		public System.Windows.Forms.Label _lblADData_2;
		public System.Windows.Forms.Label lblChan2;
		public System.Windows.Forms.Label _lblADData_1;
		public System.Windows.Forms.Label lblChan1;
		public System.Windows.Forms.Label _lblADData_0;
		public System.Windows.Forms.Label lblChan0;
		public System.Windows.Forms.Label lblDemoFunction;
		public System.Windows.Forms.Label lblChan3;
		public System.Windows.Forms.Label _lblADData_3;
		
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
		  this.lblChan3 = new System.Windows.Forms.Label();
		  this._lblADData_3 = new System.Windows.Forms.Label();
		  this.SuspendLayout();
		  // 
		  // cmdQuit
		  // 
		  this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
		  this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
		  this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.cmdQuit.Location = new System.Drawing.Point(280, 248);
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
		  this.cmdStopConvert.Location = new System.Drawing.Point(83, 48);
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
		  this.cmdStartBgnd.Location = new System.Drawing.Point(83, 48);
		  this.cmdStartBgnd.Name = "cmdStartBgnd";
		  this.cmdStartBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdStartBgnd.Size = new System.Drawing.Size(180, 27);
		  this.cmdStartBgnd.TabIndex = 8;
		  this.cmdStartBgnd.Text = "Start Background Operation";
		  this.cmdStartBgnd.Click += new System.EventHandler(this.cmdStartBgnd_Click);
		  // 
		  // lblShowCount
		  // 
		  this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowCount.Location = new System.Drawing.Point(199, 264);
		  this.lblShowCount.Name = "lblShowCount";
		  this.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowCount.Size = new System.Drawing.Size(59, 14);
		  this.lblShowCount.TabIndex = 15;
		  // 
		  // lblCount
		  // 
		  this.lblCount.BackColor = System.Drawing.SystemColors.Window;
		  this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblCount.Location = new System.Drawing.Point(84, 264);
		  this.lblCount.Name = "lblCount";
		  this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblCount.Size = new System.Drawing.Size(104, 14);
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
		  this.lblShowIndex.Location = new System.Drawing.Point(199, 240);
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
		  this.lblIndex.Location = new System.Drawing.Point(84, 240);
		  this.lblIndex.Name = "lblIndex";
		  this.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblIndex.Size = new System.Drawing.Size(104, 14);
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
		  this.lblShowStat.Location = new System.Drawing.Point(224, 224);
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
		  this.lblStatus.Location = new System.Drawing.Point(6, 224);
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
		  this._lblADData_2.Location = new System.Drawing.Point(144, 155);
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
		  this.lblChan2.Location = new System.Drawing.Point(55, 155);
		  this.lblChan2.Name = "lblChan2";
		  this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan2.Size = new System.Drawing.Size(81, 17);
		  this.lblChan2.TabIndex = 3;
		  this.lblChan2.Text = "FIRSTPORTA:";
		  this.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblADData_1
		  // 
		  this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
		  this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblADData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
		  this._lblADData_1.Location = new System.Drawing.Point(144, 128);
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
		  this.lblChan1.Location = new System.Drawing.Point(39, 128);
		  this.lblChan1.Name = "lblChan1";
		  this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan1.Size = new System.Drawing.Size(97, 17);
		  this.lblChan1.TabIndex = 2;
		  this.lblChan1.Text = "Channel 1:";
		  this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblADData_0
		  // 
		  this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
		  this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblADData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
		  this._lblADData_0.Location = new System.Drawing.Point(144, 101);
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
		  this.lblChan0.Location = new System.Drawing.Point(55, 101);
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
		  this.lblDemoFunction.Size = new System.Drawing.Size(337, 41);
		  this.lblDemoFunction.TabIndex = 0;
		  this.lblDemoFunction.Text = "Demonstration of MccBoard.DaqSetSetpoints()";
		  this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // lblChan3
		  // 
		  this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan3.Location = new System.Drawing.Point(8, 184);
		  this.lblChan3.Name = "lblChan3";
		  this.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan3.Size = new System.Drawing.Size(128, 17);
		  this.lblChan3.TabIndex = 16;
		  this.lblChan3.Text = "Setpoint Status Register:";
		  this.lblChan3.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblADData_3
		  // 
		  this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
		  this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblADData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
		  this._lblADData_3.Location = new System.Drawing.Point(144, 184);
		  this._lblADData_3.Name = "_lblADData_3";
		  this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblADData_3.Size = new System.Drawing.Size(105, 17);
		  this._lblADData_3.TabIndex = 17;
		  // 
		  // frmStatusDisplay
		  // 
		  this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		  this.BackColor = System.Drawing.SystemColors.Window;
		  this.ClientSize = new System.Drawing.Size(350, 285);
		  this.Controls.AddRange(new System.Windows.Forms.Control[] {
																	  this._lblADData_3,
																	  this.lblChan3,
																	  this.cmdQuit,
																	  this.cmdStopConvert,
																	  this.cmdStartBgnd,
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
		  this.Text = "Universal Library DaqSetSetpoints()";
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

			DaqBoard = new MccDaq.MccBoard(BoardNum);
			
			MemHandle = MccDaq.MccService.WinBufAlloc(NumElements); // set aside memory to hold data
			if (MemHandle == 0) 
				Application.Exit();
		}
		#endregion
	}
}
