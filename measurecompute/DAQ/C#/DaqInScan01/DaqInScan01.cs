// ==============================================================================
//
//  File:                         DaqInScan01.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.DaqInScan()
//
//  Purpose:                      Synchronously scans Analog channels, Digital ports and Counters
//                                in the foreground.
//
//  Demonstration:                Collects data on Analog Channels 0 and 1,
//                                FirstPortA and Counter 0.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//                                Mccdaq.MccBoard.DConfigPort()
//                                Mccdaq.MccBoard.CConfigScan()
//  Special Requirements:         Board 0 must support MccDaq.MccService.DaqInScan.

// ==============================================================================
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Diagnostics;

using MccDaq;

namespace DaqInScan01
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdRead;
		public Label _lblADData_39;
		public Label _lblADData_38;
		public Label _lblADData_37;
		public Label _lblADData_36;
		public Label _lblADData_35;
		public Label _lblADData_34;
		public Label _lblADData_33;
		public Label _lblADData_32;
		public Label _lblADData_31;
		public Label _lblADData_30;
		public Label _lblADData_29;
		public Label _lblADData_28;
		public Label _lblADData_27;
		public Label _lblADData_26;
		public Label _lblADData_25;
		public Label _lblADData_24;
		public Label _lblADData_23;
		public Label _lblADData_22;
		public Label _lblADData_21;
		public Label _lblADData_20;
		public Label _lblADData_11;
		public Label _lblADData_10;
		public Label _lblADData_9;
		public Label _lblADData_8;
		public Label _lblADData_19;
		public Label _lblADData_18;
		public Label _lblADData_17;
		public Label _lblADData_16;
		public Label _lblADData_15;
		public Label _lblADData_14;
		public Label _lblADData_13;
		public Label _lblADData_12;
		public Label _lblADData_7;
		public Label _lblADData_6;
		public Label _lblADData_5;
		public Label _lblADData_4;
		public Label _lblADData_3;
		public Label _lblADData_2;
		public Label _lblADData_1;
		public Label _lblADData_0;
		public Label _lblShowRange_3;
		public Label _lblShowRange_2;
		public Label _lblShowRange_1;
		public Label _lblShowRange_0;
		public Label _lblShowChanType_0;
		public Label _lblShowChanType_1;
		public Label _lblShowChanType_2;
		public Label _lblShowChanType_3;
		public Label lblRange;
		public Label lblChan3;
		public Label lblChan2;
		public Label lblChan1;
		public Label lblChan0;
		public Label lblDemoFunction;

		public Label[] lblADData;
		public Label[] lblShowChanType;
		public Label[] lblShowRange;

		const int ChanCount = 4; //  Number of channels in scan
		const int NumPoints = 10; //  Number of data points to collect
		const int NumElements = ChanCount * NumPoints;

		private MccDaq.MccBoard DaqBoard;
		private ushort[] ADData = new ushort[NumElements]; //  array to hold the input values
		private int MemHandle;				//  define a variable to contain the handle for
											//  memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		private short[] ChanArray = new short[ChanCount];
		private MccDaq.ChannelType[] ChanTypeArray = new MccDaq.ChannelType[ChanCount];
		public System.Windows.Forms.Label lblChan;
		public System.Windows.Forms.Label lblChanType;	
		private MccDaq.Range[] GainArray = new MccDaq.Range[ChanCount]; //  array to hold gain queue information
	 

		public frmDataDisplay()
		{
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			InitUL();
		
			//  Note: Any change to label names requires a change to the corresponding array element
			lblADData = (new Label[]{_lblADData_0,_lblADData_1, _lblADData_2, _lblADData_3, _lblADData_4,
									_lblADData_5, _lblADData_6, _lblADData_7, _lblADData_8, _lblADData_9,
									_lblADData_10,_lblADData_11, _lblADData_12, _lblADData_13, _lblADData_14,
									_lblADData_15, _lblADData_16, _lblADData_17, _lblADData_18, _lblADData_19,
									_lblADData_20,_lblADData_21, _lblADData_22, _lblADData_23, _lblADData_24,
									_lblADData_25, _lblADData_26, _lblADData_27, _lblADData_28, _lblADData_29,
									_lblADData_30,_lblADData_31, _lblADData_32, _lblADData_33, _lblADData_34,
									_lblADData_35, _lblADData_36, _lblADData_37, _lblADData_38, _lblADData_39,});

			lblShowChanType = (new Label[]{_lblShowChanType_0, _lblShowChanType_1,_lblShowChanType_2, _lblShowChanType_3});
			lblShowRange = (new Label[]{_lblShowRange_0, _lblShowRange_1,_lblShowRange_2, _lblShowRange_3});
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

				if (MemHandle!=0)
					MccDaq.MccService.WinBufFree(MemHandle);
			}
			base.Dispose(Disposing);
		}

		private void frmDataDisplay_Load(object sender, System.EventArgs e)
		{	
			//load the arrays with values
			ChanArray[0] = 0;
			ChanTypeArray[0] = MccDaq.ChannelType.Analog;
			GainArray[0] = MccDaq.Range.Bip10Volts;
			
			lblChan0.Text = "0";
			lblShowChanType[0].Text = "Analog";
			lblShowRange[0].Text = "±10 Volts";

			ChanArray[1] = System.Convert.ToInt16(MccDaq.DigitalPortType.FirstPortA);
			ChanTypeArray[1] = MccDaq.ChannelType.Digital8;
			GainArray[1] = MccDaq.Range.NotUsed;

			lblChan1.Text = "FirstPortA";
			lblShowChanType[1].Text = "Digital8";
			lblShowRange[1].Text = "NotUsed";

			ChanArray[2] = 0;
			ChanTypeArray[2] = MccDaq.ChannelType.Ctr16;
			GainArray[2] = MccDaq.Range.NotUsed;

			lblChan2.Text = "0";
			lblShowChanType[2].Text = "Ctr16";
			lblShowRange[2].Text = "NotUsed";

			ChanArray[3] = 5;
			ChanTypeArray[3] = MccDaq.ChannelType.Analog;
			GainArray[3] = MccDaq.Range.Bip5Volts;

			lblChan3.Text = "5";
			lblShowChanType[3].Text = "Analog";
			lblShowRange[3].Text = "±5 Volts";	
		}

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmDataDisplay());
		}

		private void cmdRead_Click(object sender, System.EventArgs e)
		{
			int ChannelNum;
			int  SampleNum;
			int  i;
			int FirstPoint;
			MccDaq.ErrorInfo ULStat;
			int Rate;
			MccDaq.ScanOptions Options; 
			int Count;
			int PretrigCount;

			MccDaq.DigitalPortDirection Direction;
			MccDaq.DigitalPortType PortNum;
			int CounterNum;
			
			//configure FirstPortA  for digital input;
			PortNum = (MccDaq.DigitalPortType) ChanArray[1];
			Direction = MccDaq.DigitalPortDirection.DigitalIn;
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);

			// configure counter 0
			CounterNum = ChanArray[2];
			ULStat = DaqBoard.CConfigScan(CounterNum, MccDaq.CounterMode.StopAtMax, MccDaq.CounterDebounceTime.DebounceNone, 0, MccDaq.CounterEdgeDetection.RisingEdge, 0, CounterNum);
			// Collect the values with cbDaqInScan()
			//  Parameters:
			//    BoardNum        :the number used by CB.CFG to describe this board
			//    ChanArray[]     :array of channel values
			//    ChanTypeArray[] : array of channel types
			//    GainArray[]     :array of gain values
			//    ChansCount      :the number of elements in the arrays (0=disable queue)
			//    PretrigCount    :number of pre-trigger A/D samples to collect
			//    Count         :the total number of A/D samples to collect
			//    Rate            :sample rate in samples per second
			//    ADData[]        :the array for the collected data values
			//    Options         :data collection options

			PretrigCount = 0;
			Count = NumElements; // Number of data points to collect
			Options = MccDaq.ScanOptions.ConvertData;
			Rate = 100; // Acquire data at 100 Hz

			if(MemHandle == 0)          // check that a handle to a memory buffer exists
				Application.Exit();

			ULStat = DaqBoard.DaqInScan(ChanArray, ChanTypeArray, GainArray, ChanCount, ref Rate, ref PretrigCount, ref Count, MemHandle, Options);
			
			// Transfer the data from the memory buffer set up by Windows to an array
			FirstPoint = 0;
			ULStat = MccDaq.MccService.WinBufToArray(MemHandle, out ADData[0], FirstPoint, Count);

			i = 0;
			for (SampleNum = 0; SampleNum <NumPoints;SampleNum++)
			{
				for(ChannelNum = 0; ChannelNum<ChanCount; ChannelNum++)
				{
					lblADData[i].Text = ADData[i].ToString("D");
					i = i + 1;
				}
			}
		
		}

		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			//  Free up memory for use by other programs
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			
			Application.Exit();
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
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this._lblADData_39 = new System.Windows.Forms.Label();
			this._lblADData_38 = new System.Windows.Forms.Label();
			this._lblADData_37 = new System.Windows.Forms.Label();
			this._lblADData_36 = new System.Windows.Forms.Label();
			this._lblADData_35 = new System.Windows.Forms.Label();
			this._lblADData_34 = new System.Windows.Forms.Label();
			this._lblADData_33 = new System.Windows.Forms.Label();
			this._lblADData_32 = new System.Windows.Forms.Label();
			this._lblADData_31 = new System.Windows.Forms.Label();
			this._lblADData_30 = new System.Windows.Forms.Label();
			this._lblADData_29 = new System.Windows.Forms.Label();
			this._lblADData_28 = new System.Windows.Forms.Label();
			this._lblADData_27 = new System.Windows.Forms.Label();
			this._lblADData_26 = new System.Windows.Forms.Label();
			this._lblADData_25 = new System.Windows.Forms.Label();
			this._lblADData_24 = new System.Windows.Forms.Label();
			this._lblADData_23 = new System.Windows.Forms.Label();
			this._lblADData_22 = new System.Windows.Forms.Label();
			this._lblADData_21 = new System.Windows.Forms.Label();
			this._lblADData_20 = new System.Windows.Forms.Label();
			this._lblADData_11 = new System.Windows.Forms.Label();
			this._lblADData_10 = new System.Windows.Forms.Label();
			this._lblADData_9 = new System.Windows.Forms.Label();
			this._lblADData_8 = new System.Windows.Forms.Label();
			this._lblADData_19 = new System.Windows.Forms.Label();
			this._lblADData_18 = new System.Windows.Forms.Label();
			this._lblADData_17 = new System.Windows.Forms.Label();
			this._lblADData_16 = new System.Windows.Forms.Label();
			this._lblADData_15 = new System.Windows.Forms.Label();
			this._lblADData_14 = new System.Windows.Forms.Label();
			this._lblADData_13 = new System.Windows.Forms.Label();
			this._lblADData_12 = new System.Windows.Forms.Label();
			this._lblADData_7 = new System.Windows.Forms.Label();
			this._lblADData_6 = new System.Windows.Forms.Label();
			this._lblADData_5 = new System.Windows.Forms.Label();
			this._lblADData_4 = new System.Windows.Forms.Label();
			this._lblADData_3 = new System.Windows.Forms.Label();
			this._lblADData_2 = new System.Windows.Forms.Label();
			this._lblADData_1 = new System.Windows.Forms.Label();
			this._lblADData_0 = new System.Windows.Forms.Label();
			this._lblShowRange_3 = new System.Windows.Forms.Label();
			this._lblShowRange_2 = new System.Windows.Forms.Label();
			this._lblShowRange_1 = new System.Windows.Forms.Label();
			this._lblShowRange_0 = new System.Windows.Forms.Label();
			this.lblRange = new System.Windows.Forms.Label();
			this.lblChan3 = new System.Windows.Forms.Label();
			this.lblChan2 = new System.Windows.Forms.Label();
			this.lblChan1 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this._lblShowChanType_0 = new System.Windows.Forms.Label();
			this._lblShowChanType_1 = new System.Windows.Forms.Label();
			this._lblShowChanType_2 = new System.Windows.Forms.Label();
			this._lblShowChanType_3 = new System.Windows.Forms.Label();
			this.cmdRead = new System.Windows.Forms.Button();
			this.lblChan = new System.Windows.Forms.Label();
			this.lblChanType = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// cmdStopConvert
			// 
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(208, 296);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(57, 33);
			this.cmdStopConvert.TabIndex = 13;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			// 
			// _lblADData_39
			// 
			this._lblADData_39.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_39.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_39.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_39.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_39.Location = new System.Drawing.Point(288, 264);
			this._lblADData_39.Name = "_lblADData_39";
			this._lblADData_39.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_39.Size = new System.Drawing.Size(65, 17);
			this._lblADData_39.TabIndex = 46;
			this._lblADData_39.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_38
			// 
			this._lblADData_38.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_38.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_38.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_38.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_38.Location = new System.Drawing.Point(216, 264);
			this._lblADData_38.Name = "_lblADData_38";
			this._lblADData_38.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_38.Size = new System.Drawing.Size(65, 17);
			this._lblADData_38.TabIndex = 45;
			this._lblADData_38.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_37
			// 
			this._lblADData_37.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_37.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_37.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_37.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_37.Location = new System.Drawing.Point(144, 264);
			this._lblADData_37.Name = "_lblADData_37";
			this._lblADData_37.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_37.Size = new System.Drawing.Size(65, 17);
			this._lblADData_37.TabIndex = 44;
			this._lblADData_37.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_36
			// 
			this._lblADData_36.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_36.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_36.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_36.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_36.Location = new System.Drawing.Point(72, 264);
			this._lblADData_36.Name = "_lblADData_36";
			this._lblADData_36.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_36.Size = new System.Drawing.Size(65, 17);
			this._lblADData_36.TabIndex = 43;
			this._lblADData_36.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_35
			// 
			this._lblADData_35.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_35.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_35.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_35.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_35.Location = new System.Drawing.Point(288, 248);
			this._lblADData_35.Name = "_lblADData_35";
			this._lblADData_35.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_35.Size = new System.Drawing.Size(65, 17);
			this._lblADData_35.TabIndex = 42;
			this._lblADData_35.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_34
			// 
			this._lblADData_34.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_34.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_34.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_34.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_34.Location = new System.Drawing.Point(216, 248);
			this._lblADData_34.Name = "_lblADData_34";
			this._lblADData_34.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_34.Size = new System.Drawing.Size(65, 17);
			this._lblADData_34.TabIndex = 41;
			this._lblADData_34.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_33
			// 
			this._lblADData_33.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_33.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_33.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_33.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_33.Location = new System.Drawing.Point(144, 248);
			this._lblADData_33.Name = "_lblADData_33";
			this._lblADData_33.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_33.Size = new System.Drawing.Size(65, 17);
			this._lblADData_33.TabIndex = 40;
			this._lblADData_33.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_32
			// 
			this._lblADData_32.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_32.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_32.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_32.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_32.Location = new System.Drawing.Point(72, 248);
			this._lblADData_32.Name = "_lblADData_32";
			this._lblADData_32.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_32.Size = new System.Drawing.Size(65, 17);
			this._lblADData_32.TabIndex = 39;
			this._lblADData_32.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_31
			// 
			this._lblADData_31.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_31.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_31.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_31.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_31.Location = new System.Drawing.Point(288, 232);
			this._lblADData_31.Name = "_lblADData_31";
			this._lblADData_31.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_31.Size = new System.Drawing.Size(65, 17);
			this._lblADData_31.TabIndex = 38;
			this._lblADData_31.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_30
			// 
			this._lblADData_30.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_30.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_30.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_30.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_30.Location = new System.Drawing.Point(216, 232);
			this._lblADData_30.Name = "_lblADData_30";
			this._lblADData_30.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_30.Size = new System.Drawing.Size(65, 17);
			this._lblADData_30.TabIndex = 37;
			this._lblADData_30.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_29
			// 
			this._lblADData_29.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_29.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_29.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_29.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_29.Location = new System.Drawing.Point(144, 232);
			this._lblADData_29.Name = "_lblADData_29";
			this._lblADData_29.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_29.Size = new System.Drawing.Size(65, 17);
			this._lblADData_29.TabIndex = 36;
			this._lblADData_29.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_28
			// 
			this._lblADData_28.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_28.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_28.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_28.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_28.Location = new System.Drawing.Point(72, 232);
			this._lblADData_28.Name = "_lblADData_28";
			this._lblADData_28.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_28.Size = new System.Drawing.Size(65, 17);
			this._lblADData_28.TabIndex = 35;
			this._lblADData_28.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_27
			// 
			this._lblADData_27.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_27.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_27.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_27.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_27.Location = new System.Drawing.Point(288, 216);
			this._lblADData_27.Name = "_lblADData_27";
			this._lblADData_27.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_27.Size = new System.Drawing.Size(65, 17);
			this._lblADData_27.TabIndex = 34;
			this._lblADData_27.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_26
			// 
			this._lblADData_26.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_26.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_26.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_26.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_26.Location = new System.Drawing.Point(216, 216);
			this._lblADData_26.Name = "_lblADData_26";
			this._lblADData_26.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_26.Size = new System.Drawing.Size(65, 17);
			this._lblADData_26.TabIndex = 33;
			this._lblADData_26.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_25
			// 
			this._lblADData_25.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_25.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_25.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_25.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_25.Location = new System.Drawing.Point(144, 216);
			this._lblADData_25.Name = "_lblADData_25";
			this._lblADData_25.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_25.Size = new System.Drawing.Size(65, 17);
			this._lblADData_25.TabIndex = 32;
			this._lblADData_25.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_24
			// 
			this._lblADData_24.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_24.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_24.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_24.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_24.Location = new System.Drawing.Point(72, 216);
			this._lblADData_24.Name = "_lblADData_24";
			this._lblADData_24.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_24.Size = new System.Drawing.Size(65, 17);
			this._lblADData_24.TabIndex = 31;
			this._lblADData_24.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_23
			// 
			this._lblADData_23.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_23.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_23.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_23.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_23.Location = new System.Drawing.Point(288, 200);
			this._lblADData_23.Name = "_lblADData_23";
			this._lblADData_23.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_23.Size = new System.Drawing.Size(65, 17);
			this._lblADData_23.TabIndex = 30;
			this._lblADData_23.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_22
			// 
			this._lblADData_22.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_22.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_22.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_22.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_22.Location = new System.Drawing.Point(216, 200);
			this._lblADData_22.Name = "_lblADData_22";
			this._lblADData_22.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_22.Size = new System.Drawing.Size(65, 17);
			this._lblADData_22.TabIndex = 29;
			this._lblADData_22.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_21
			// 
			this._lblADData_21.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_21.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_21.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_21.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_21.Location = new System.Drawing.Point(144, 200);
			this._lblADData_21.Name = "_lblADData_21";
			this._lblADData_21.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_21.Size = new System.Drawing.Size(65, 17);
			this._lblADData_21.TabIndex = 28;
			this._lblADData_21.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_20
			// 
			this._lblADData_20.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_20.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_20.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_20.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_20.Location = new System.Drawing.Point(72, 200);
			this._lblADData_20.Name = "_lblADData_20";
			this._lblADData_20.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_20.Size = new System.Drawing.Size(65, 17);
			this._lblADData_20.TabIndex = 27;
			this._lblADData_20.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_11
			// 
			this._lblADData_11.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_11.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_11.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_11.Location = new System.Drawing.Point(288, 184);
			this._lblADData_11.Name = "_lblADData_11";
			this._lblADData_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_11.Size = new System.Drawing.Size(65, 17);
			this._lblADData_11.TabIndex = 18;
			this._lblADData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_10
			// 
			this._lblADData_10.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_10.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_10.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_10.Location = new System.Drawing.Point(216, 184);
			this._lblADData_10.Name = "_lblADData_10";
			this._lblADData_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_10.Size = new System.Drawing.Size(65, 17);
			this._lblADData_10.TabIndex = 17;
			this._lblADData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_9
			// 
			this._lblADData_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_9.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_9.Location = new System.Drawing.Point(144, 184);
			this._lblADData_9.Name = "_lblADData_9";
			this._lblADData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_9.Size = new System.Drawing.Size(65, 17);
			this._lblADData_9.TabIndex = 16;
			this._lblADData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_8
			// 
			this._lblADData_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_8.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_8.Location = new System.Drawing.Point(72, 184);
			this._lblADData_8.Name = "_lblADData_8";
			this._lblADData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_8.Size = new System.Drawing.Size(65, 17);
			this._lblADData_8.TabIndex = 15;
			this._lblADData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_19
			// 
			this._lblADData_19.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_19.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_19.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_19.Location = new System.Drawing.Point(288, 168);
			this._lblADData_19.Name = "_lblADData_19";
			this._lblADData_19.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_19.Size = new System.Drawing.Size(65, 17);
			this._lblADData_19.TabIndex = 26;
			this._lblADData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_18
			// 
			this._lblADData_18.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_18.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_18.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_18.Location = new System.Drawing.Point(216, 168);
			this._lblADData_18.Name = "_lblADData_18";
			this._lblADData_18.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_18.Size = new System.Drawing.Size(65, 17);
			this._lblADData_18.TabIndex = 25;
			this._lblADData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_17
			// 
			this._lblADData_17.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_17.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_17.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_17.Location = new System.Drawing.Point(144, 168);
			this._lblADData_17.Name = "_lblADData_17";
			this._lblADData_17.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_17.Size = new System.Drawing.Size(65, 17);
			this._lblADData_17.TabIndex = 24;
			this._lblADData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_16
			// 
			this._lblADData_16.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_16.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_16.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_16.Location = new System.Drawing.Point(72, 168);
			this._lblADData_16.Name = "_lblADData_16";
			this._lblADData_16.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_16.Size = new System.Drawing.Size(65, 17);
			this._lblADData_16.TabIndex = 23;
			this._lblADData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_15
			// 
			this._lblADData_15.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_15.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_15.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_15.Location = new System.Drawing.Point(288, 152);
			this._lblADData_15.Name = "_lblADData_15";
			this._lblADData_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_15.Size = new System.Drawing.Size(65, 17);
			this._lblADData_15.TabIndex = 22;
			this._lblADData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_14
			// 
			this._lblADData_14.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_14.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_14.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_14.Location = new System.Drawing.Point(216, 152);
			this._lblADData_14.Name = "_lblADData_14";
			this._lblADData_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_14.Size = new System.Drawing.Size(65, 17);
			this._lblADData_14.TabIndex = 21;
			this._lblADData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_13
			// 
			this._lblADData_13.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_13.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_13.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_13.Location = new System.Drawing.Point(144, 152);
			this._lblADData_13.Name = "_lblADData_13";
			this._lblADData_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_13.Size = new System.Drawing.Size(65, 17);
			this._lblADData_13.TabIndex = 20;
			this._lblADData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_12
			// 
			this._lblADData_12.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_12.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_12.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_12.Location = new System.Drawing.Point(72, 152);
			this._lblADData_12.Name = "_lblADData_12";
			this._lblADData_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_12.Size = new System.Drawing.Size(65, 17);
			this._lblADData_12.TabIndex = 19;
			this._lblADData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_7
			// 
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Location = new System.Drawing.Point(288, 136);
			this._lblADData_7.Name = "_lblADData_7";
			this._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_7.Size = new System.Drawing.Size(65, 17);
			this._lblADData_7.TabIndex = 12;
			this._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_6
			// 
			this._lblADData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_6.Location = new System.Drawing.Point(216, 136);
			this._lblADData_6.Name = "_lblADData_6";
			this._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_6.Size = new System.Drawing.Size(65, 17);
			this._lblADData_6.TabIndex = 11;
			this._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_5
			// 
			this._lblADData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_5.Location = new System.Drawing.Point(144, 136);
			this._lblADData_5.Name = "_lblADData_5";
			this._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_5.Size = new System.Drawing.Size(65, 17);
			this._lblADData_5.TabIndex = 10;
			this._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_4
			// 
			this._lblADData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_4.Location = new System.Drawing.Point(72, 136);
			this._lblADData_4.Name = "_lblADData_4";
			this._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_4.Size = new System.Drawing.Size(65, 17);
			this._lblADData_4.TabIndex = 9;
			this._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_3
			// 
			this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_3.Location = new System.Drawing.Point(288, 120);
			this._lblADData_3.Name = "_lblADData_3";
			this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_3.Size = new System.Drawing.Size(65, 17);
			this._lblADData_3.TabIndex = 8;
			this._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_2
			// 
			this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_2.Location = new System.Drawing.Point(216, 120);
			this._lblADData_2.Name = "_lblADData_2";
			this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_2.Size = new System.Drawing.Size(65, 17);
			this._lblADData_2.TabIndex = 7;
			this._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_1
			// 
			this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_1.Location = new System.Drawing.Point(144, 120);
			this._lblADData_1.Name = "_lblADData_1";
			this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_1.Size = new System.Drawing.Size(65, 17);
			this._lblADData_1.TabIndex = 6;
			this._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_0
			// 
			this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_0.Location = new System.Drawing.Point(72, 120);
			this._lblADData_0.Name = "_lblADData_0";
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.Size = new System.Drawing.Size(65, 17);
			this._lblADData_0.TabIndex = 5;
			this._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblShowRange_3
			// 
			this._lblShowRange_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRange_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRange_3.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblShowRange_3.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRange_3.Location = new System.Drawing.Point(288, 88);
			this._lblShowRange_3.Name = "_lblShowRange_3";
			this._lblShowRange_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRange_3.Size = new System.Drawing.Size(65, 17);
			this._lblShowRange_3.TabIndex = 52;
			this._lblShowRange_3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// _lblShowRange_2
			// 
			this._lblShowRange_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRange_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRange_2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblShowRange_2.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRange_2.Location = new System.Drawing.Point(216, 88);
			this._lblShowRange_2.Name = "_lblShowRange_2";
			this._lblShowRange_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRange_2.Size = new System.Drawing.Size(65, 17);
			this._lblShowRange_2.TabIndex = 51;
			this._lblShowRange_2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// _lblShowRange_1
			// 
			this._lblShowRange_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRange_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRange_1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblShowRange_1.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRange_1.Location = new System.Drawing.Point(144, 88);
			this._lblShowRange_1.Name = "_lblShowRange_1";
			this._lblShowRange_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRange_1.Size = new System.Drawing.Size(65, 17);
			this._lblShowRange_1.TabIndex = 50;
			this._lblShowRange_1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// _lblShowRange_0
			// 
			this._lblShowRange_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRange_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRange_0.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblShowRange_0.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRange_0.Location = new System.Drawing.Point(72, 88);
			this._lblShowRange_0.Name = "_lblShowRange_0";
			this._lblShowRange_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRange_0.Size = new System.Drawing.Size(65, 17);
			this._lblShowRange_0.TabIndex = 49;
			this._lblShowRange_0.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// lblRange
			// 
			this.lblRange.BackColor = System.Drawing.SystemColors.Window;
			this.lblRange.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblRange.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblRange.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblRange.Location = new System.Drawing.Point(8, 88);
			this.lblRange.Name = "lblRange";
			this.lblRange.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblRange.Size = new System.Drawing.Size(56, 16);
			this.lblRange.TabIndex = 48;
			this.lblRange.Text = "Range:";
			this.lblRange.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// lblChan3
			// 
			this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan3.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan3.ForeColor = System.Drawing.Color.Blue;
			this.lblChan3.Location = new System.Drawing.Point(288, 40);
			this.lblChan3.Name = "lblChan3";
			this.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan3.Size = new System.Drawing.Size(65, 17);
			this.lblChan3.TabIndex = 4;
			this.lblChan3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// lblChan2
			// 
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan2.ForeColor = System.Drawing.Color.Blue;
			this.lblChan2.Location = new System.Drawing.Point(216, 40);
			this.lblChan2.Name = "lblChan2";
			this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan2.Size = new System.Drawing.Size(65, 17);
			this.lblChan2.TabIndex = 3;
			this.lblChan2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// lblChan1
			// 
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.Color.Blue;
			this.lblChan1.Location = new System.Drawing.Point(144, 40);
			this.lblChan1.Name = "lblChan1";
			this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1.Size = new System.Drawing.Size(65, 17);
			this.lblChan1.TabIndex = 2;
			this.lblChan1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// lblChan0
			// 
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.Color.Blue;
			this.lblChan0.Location = new System.Drawing.Point(72, 40);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.Size = new System.Drawing.Size(65, 17);
			this.lblChan0.TabIndex = 1;
			this.lblChan0.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// lblDemoFunction
			// 
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(32, 8);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(351, 25);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DaqInScan()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblShowChanType_0
			// 
			this._lblShowChanType_0.Location = new System.Drawing.Point(72, 64);
			this._lblShowChanType_0.Name = "_lblShowChanType_0";
			this._lblShowChanType_0.Size = new System.Drawing.Size(65, 17);
			this._lblShowChanType_0.TabIndex = 55;
			this._lblShowChanType_0.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// _lblShowChanType_1
			// 
			this._lblShowChanType_1.Location = new System.Drawing.Point(144, 64);
			this._lblShowChanType_1.Name = "_lblShowChanType_1";
			this._lblShowChanType_1.Size = new System.Drawing.Size(65, 17);
			this._lblShowChanType_1.TabIndex = 56;
			this._lblShowChanType_1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// _lblShowChanType_2
			// 
			this._lblShowChanType_2.Location = new System.Drawing.Point(216, 64);
			this._lblShowChanType_2.Name = "_lblShowChanType_2";
			this._lblShowChanType_2.Size = new System.Drawing.Size(65, 17);
			this._lblShowChanType_2.TabIndex = 57;
			this._lblShowChanType_2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// _lblShowChanType_3
			// 
			this._lblShowChanType_3.Location = new System.Drawing.Point(288, 64);
			this._lblShowChanType_3.Name = "_lblShowChanType_3";
			this._lblShowChanType_3.Size = new System.Drawing.Size(65, 17);
			this._lblShowChanType_3.TabIndex = 58;
			this._lblShowChanType_3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// cmdRead
			// 
			this.cmdRead.BackColor = System.Drawing.SystemColors.Control;
			this.cmdRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdRead.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdRead.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdRead.Location = new System.Drawing.Point(144, 296);
			this.cmdRead.Name = "cmdRead";
			this.cmdRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdRead.Size = new System.Drawing.Size(57, 33);
			this.cmdRead.TabIndex = 59;
			this.cmdRead.Text = "Read";
			this.cmdRead.Click += new System.EventHandler(this.cmdRead_Click);
			// 
			// lblChan
			// 
			this.lblChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan.Location = new System.Drawing.Point(8, 40);
			this.lblChan.Name = "lblChan";
			this.lblChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan.Size = new System.Drawing.Size(56, 16);
			this.lblChan.TabIndex = 60;
			this.lblChan.Text = "Channel:";
			this.lblChan.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// lblChanType
			// 
			this.lblChanType.BackColor = System.Drawing.SystemColors.Window;
			this.lblChanType.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChanType.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChanType.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChanType.Location = new System.Drawing.Point(8, 64);
			this.lblChanType.Name = "lblChanType";
			this.lblChanType.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChanType.Size = new System.Drawing.Size(56, 16);
			this.lblChanType.TabIndex = 61;
			this.lblChanType.Text = "Type:";
			this.lblChanType.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// frmDataDisplay
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(408, 341);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.lblChanType,
																		  this.lblChan,
																		  this.cmdRead,
																		  this._lblShowChanType_3,
																		  this._lblShowChanType_2,
																		  this._lblShowChanType_1,
																		  this._lblShowChanType_0,
																		  this.cmdStopConvert,
																		  this._lblADData_39,
																		  this._lblADData_38,
																		  this._lblADData_37,
																		  this._lblADData_36,
																		  this._lblADData_35,
																		  this._lblADData_34,
																		  this._lblADData_33,
																		  this._lblADData_32,
																		  this._lblADData_31,
																		  this._lblADData_30,
																		  this._lblADData_29,
																		  this._lblADData_28,
																		  this._lblADData_27,
																		  this._lblADData_26,
																		  this._lblADData_25,
																		  this._lblADData_24,
																		  this._lblADData_23,
																		  this._lblADData_22,
																		  this._lblADData_21,
																		  this._lblADData_20,
																		  this._lblADData_11,
																		  this._lblADData_10,
																		  this._lblADData_9,
																		  this._lblADData_8,
																		  this._lblADData_19,
																		  this._lblADData_18,
																		  this._lblADData_17,
																		  this._lblADData_16,
																		  this._lblADData_15,
																		  this._lblADData_14,
																		  this._lblADData_13,
																		  this._lblADData_12,
																		  this._lblADData_7,
																		  this._lblADData_6,
																		  this._lblADData_5,
																		  this._lblADData_4,
																		  this._lblADData_3,
																		  this._lblADData_2,
																		  this._lblADData_1,
																		  this._lblADData_0,
																		  this._lblShowRange_3,
																		  this._lblShowRange_2,
																		  this._lblShowRange_1,
																		  this._lblShowRange_0,
																		  this.lblRange,
																		  this.lblChan3,
																		  this.lblChan2,
																		  this.lblChan1,
																		  this.lblChan0,
																		  this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmDataDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library DaqInScan()";
			this.Load += new System.EventHandler(this.frmDataDisplay_Load);
			this.ResumeLayout(false);

		}

	#endregion

		#region "Universal Library Initialization - Expand this region to change error handling, etc."
		
		private void InitUL()
		{
			MccDaq.ErrorInfo ULStat;		
			
			// Initiate error handling
			//  activating error handling will trap errors like
			//  bad channel numbers and non-configured conditions.
			//  Parameters:
			//    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop
			
			ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);

			DaqBoard = new MccDaq.MccBoard(0);
			
			MemHandle = MccDaq.MccService.WinBufAlloc(NumElements); // set aside memory to hold data
			if (MemHandle == 0) 
				Application.Exit();
		}
		#endregion

	}
}