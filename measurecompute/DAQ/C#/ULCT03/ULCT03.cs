// ==============================================================================
//
//  File:                         ULCT03.CS
//
//  Library Call Demonstrated:    9513 Counter Functions
//                                Mccdaq.MccBoard.C9513Config()
//                                Mccdaq.MccBoard.CStoreOnInt()
//
//  Purpose:                      Operate the counter
//
//  Demonstration:                Sets up 2 counters to store values in
//                                response to an interrupt
//
//
//  Other Library Calls:          Mccdaq.MccBoard.C9513Init()
//                                Mccdaq.MccBoard.CLoad()
//                                Mccdaq.MccBoard.StopBackground()
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a 9513 counter.
//                                IR enable must be tied low (Pin 2).
//                                User must generate an interrupt (Pin1).
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

namespace ULCT03
{
	public class frm9513Int : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStartInt;
		public Button cmdStopRead;
		public Timer tmrReadStatus;
		public Label lblShowTotal;
		public Label lblIntTotal;
		public Label _lblCount_4;
		public Label _lblIntStatus_4;
		public Label _lblCounterNum_4;
		public Label _lblCount_3;
		public Label _lblIntStatus_3;
		public Label _lblCounterNum_3;
		public Label _lblCount_2;
		public Label _lblIntStatus_2;
		public Label _lblCounterNum_2;
		public Label _lblCount_1;
		public Label _lblIntStatus_1;
		public Label _lblCounterNum_1;
		public Label _lblCount_0;
		public Label _lblIntStatus_0;
		public Label _lblCounterNum_0;
		public Label lblData;
		public Label lblStatCol;
		public Label lblCountCol;
		public Label lblDemoFunction;

		public Label[] lblCount;
		public Label[] lblCounterNum;
		public Label[] lblIntStatus;

		private MccDaq.MccBoard DaqBoard;
		const int ChipNum = 1;			// use chip 1 for CTR05 or for first chip on CTR10
		const short ControlSize = 20;	
		const int MaxNumCntrs = 20;		// maximum number of 9513 counters onboard(CTR20)

		//    UPDATE THIS VALUE TO REFLECT THE NUMBER COUNTERS
		//        FOR SPECIFIC MODEL INSTALLED!!!
		const int NumCntrs = 10;		// actual number of counters onboard the CTR10
		const int IntCount = 100;		//  the windows buffer pointed to by MemHandle will hold enough
										//  data for IntCount interrupts

		private ushort[] DataBuffer = new ushort[MaxNumCntrs]; //  array to hold latest readings from each of the counters
		private MccDaq.CounterControl[] CntrControl = new MccDaq.CounterControl[MaxNumCntrs]; //  array to control whether or not each counter is enabled
		private int MemHandle;	// handle to windows data buffer that is large enough to hold
								// IntCount readings from each of the NumCntrs counters
		private int FirstPoint;


		public frm9513Int()
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
			

			lblCount = (new Label[]{_lblCount_0, _lblCount_1, _lblCount_3, _lblCount_4});
			lblCounterNum = (new Label[]{_lblCounterNum_0, _lblCounterNum_1, _lblCounterNum_3, _lblCounterNum_4});
			lblIntStatus = (new Label[]{_lblIntStatus_0, _lblIntStatus_1, _lblIntStatus_3, _lblIntStatus_4});
	      

			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);
			
			// Set aside enough memory to hold the data from all counters (whether enable or not)
			//   IntCount interrupts. We use MaxNumCntrs here in case actual NumCntrs had not been 
			//   updated; while allocating too much memory is harmless, not enough could crash system.
			MemHandle = MccDaq.MccService.WinBufAlloc(IntCount * MaxNumCntrs); 
			

			//  Initialize the board level features
			//   Parameters:
			//     ChipNum    :chip to be initialized (1 for CTR5, 1 or 2 for CTR10)
			//     FOutDivider:the F-Out divider (0-15)
			//     Source     :the signal source for F-Out
			//     Compare1   :status of comparator 1
			//     Compare2   :status of comparator 2
			//     TimeOfDayCounting  :time of day mode control
			int FOutDivider = 10; //  sets up OSC OUT for 10Hz signal which can
			MccDaq.CounterSource Source = MccDaq.CounterSource.Freq5; //  be used as interrupt source for this example
			MccDaq.CompareValue Compare1 = MccDaq.CompareValue.Disabled;
			MccDaq.CompareValue Compare2 = MccDaq.CompareValue.Disabled;
			MccDaq.TimeOfDay TimeOfDayCounting = MccDaq.TimeOfDay.Disabled;
			ULStat = DaqBoard.C9513Init(ChipNum, FOutDivider, Source, Compare1, Compare2, TimeOfDayCounting);
			

			//  Set the configurable operations of the counter
			//   Parameters:
			//     CounterNum     :the counter to be configured (1 to 5)
			//     GateControl    :gate control value
			//     CounterEdge    :which edge to count
			//     CountSource    :signal source
			//     SpecialGate    :status of special gate
			//     Reload         :method of reloading
			//     RecyleMode     :recyle mode
			//     BCDMode        :counting mode, Binary or BCD
			//     CountDirection :direction for the counting operation (COUNTUP or COUNTDOWN)
			//     OutputControl  :output signal type and level

			//  Initialize variables for the first of two counters
			int CounterNum = 1; //  number of counter used
			MccDaq.GateControl GateControl = MccDaq.GateControl.NoGate;
			MccDaq.CountEdge CounterEdge = MccDaq.CountEdge.PositiveEdge;
			MccDaq.CounterSource CountSource = MccDaq.CounterSource.Freq3;
			MccDaq.OptionState SpecialGate = MccDaq.OptionState.Disabled;
			MccDaq.Reload Reload = MccDaq.Reload.LoadReg;
			MccDaq.RecycleMode RecycleMode = MccDaq.RecycleMode.Recycle;
			MccDaq.BCDMode BCDMode = MccDaq.BCDMode.Disabled;
			MccDaq.CountDirection CountDirection = MccDaq.CountDirection.CountUp;
			MccDaq.C9513OutputControl OutputControl = MccDaq.C9513OutputControl.AlwaysLow;
			ULStat = DaqBoard.C9513Config(CounterNum, GateControl, CounterEdge, CountSource, SpecialGate, Reload, RecycleMode, BCDMode, CountDirection, OutputControl);
			

			//  Initialize variables for the second counter
			CounterNum = 2; //  number of counter used
			ULStat = DaqBoard.C9513Config(CounterNum, GateControl, CounterEdge, CountSource, SpecialGate, Reload, RecycleMode, BCDMode, CountDirection, OutputControl);
			


			//  Load the 2 counters with starting values of zero with MccDaq.MccBoard.CLoad()
			//   Parameters:
			//     RegName    :the register for loading the counter with the starting value
			//     LoadValue  :the starting value to place in the counter
			int LoadValue = 0;
			MccDaq.CounterRegister RegName = MccDaq.CounterRegister.LoadReg1; //  name of register in counter 1
			ULStat = DaqBoard.CLoad(RegName, LoadValue);
			

			RegName = MccDaq.CounterRegister.LoadReg2; //  name of register in counter 2
			ULStat = DaqBoard.CLoad(RegName, LoadValue);
			
		}


		private void cmdStartInt_Click(object eventSender, System.EventArgs eventArgs) 
		{
			cmdStartInt.Enabled = false;
			cmdStartInt.Visible = false;
			cmdStopRead.Enabled = true;
			cmdStopRead.Visible = true;

			//  Set the counters to store their values upon an interrupt
			//   Parameters:
			//     IntCount      :maximum number of interrupts
			//     CntrControl() :array which indicates the channels to be read
			//     DataBuffer()  :array that receives the count values for enabled
			//                     channels each time an interrupt occur
			//  Set all channels to MccDaq.CounterControl.Disabled and init DataBuffer
			for (int i=0; i<=NumCntrs - 1; ++i)
			{
				CntrControl[i] = MccDaq.CounterControl.Disabled;
				DataBuffer[i] = 0;
			}

			//  Enable the channels to be monitored
			CntrControl[0] = MccDaq.CounterControl.Enabled;
			CntrControl[1] = MccDaq.CounterControl.Enabled;

			// Start acquisition of counter values
			MccDaq.ErrorInfo ULStat = DaqBoard.CStoreOnInt( IntCount, ref CntrControl[0], MemHandle);
			

			tmrReadStatus.Enabled = true;
			FirstPoint = 0;
		}

		private void tmrReadStatus_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrReadStatus.Tick */
		{
			int CurIndex = 0;
			int CurCount = 0;
			short Status = 0;
			
			tmrReadStatus.Stop();

			// Retrieve the status of the acquisition
			//   Parameters:
			//		Status	: current status of the operation, RUNNING or IDLE.
			//		CurCount: the current number of interrupts 
			//		CurIndex  : scan index into buffer to the last counter set read 
            //		CtrFunction: Counter Function Type for operation
			MccDaq.ErrorInfo ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.CtrFunction);
			

			// The calculation below requires that NumCntrs accurately reflects the number
			//   of counters onboard whether or not they are enabled or active.
			FirstPoint = 0;
			if (CurIndex > 0)
			{
				FirstPoint = NumCntrs * CurIndex;
			}

			// Transfer latest set of measurements from the buffer into an array
			// Parameters:
			//   MemHandle	: handle to buffer allocated by MccService.WinBufAlloc
			//   DataBuffer	: array to store latest counter values into
			//	 FirstPoint : sample index into buffer of first sample in last set of counter values read
			//   NumCntrs	: total number counters on the device
			ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out DataBuffer[0], FirstPoint, NumCntrs);

			ushort RealCount = 0;
			String IntStatus = "DISABLED";
			for (int i=0; i<=4; ++i)
			{
				if (CntrControl[i] == MccDaq.CounterControl.Enabled)
					IntStatus = "ENABLED ";
				else
					IntStatus = "DISABLED";

				//  convert type int to type long
				RealCount = DataBuffer[i];

				lblCounterNum[i].Text = (i + 1).ToString("0");
				lblIntStatus[i].Text = IntStatus;
				lblCount[i].Text = RealCount.ToString("0");
			}

			lblShowTotal.Text = CurCount.ToString("0");

			tmrReadStatus.Start();
		}


		private void cmdStopRead_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopRead.Click */
		{
			//  The BACKGROUND operation must be explicitly stopped
			//  Parameters:
			//    FunctionType:counter operation (MccDaq.FunctionType.CtrFunction)
			MccDaq.ErrorInfo ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.CtrFunction);
			

			//  Free up memory for use by other programs
			ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			
			MemHandle = 0;

			Application.Exit();
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

	    
	         
	    
		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
	    
		private void InitializeComponent()
		{
		this.components = new System.ComponentModel.Container();
		this.ToolTip1 = new System.Windows.Forms.ToolTip(this.components);
		this.cmdStartInt = new System.Windows.Forms.Button();
		this.cmdStopRead = new System.Windows.Forms.Button();
		this.tmrReadStatus = new System.Windows.Forms.Timer(this.components);
		this.lblShowTotal = new System.Windows.Forms.Label();
		this.lblIntTotal = new System.Windows.Forms.Label();
		this._lblCount_4 = new System.Windows.Forms.Label();
		this._lblIntStatus_4 = new System.Windows.Forms.Label();
		this._lblCounterNum_4 = new System.Windows.Forms.Label();
		this._lblCount_3 = new System.Windows.Forms.Label();
		this._lblIntStatus_3 = new System.Windows.Forms.Label();
		this._lblCounterNum_3 = new System.Windows.Forms.Label();
		this._lblCount_2 = new System.Windows.Forms.Label();
		this._lblIntStatus_2 = new System.Windows.Forms.Label();
		this._lblCounterNum_2 = new System.Windows.Forms.Label();
		this._lblCount_1 = new System.Windows.Forms.Label();
		this._lblIntStatus_1 = new System.Windows.Forms.Label();
		this._lblCounterNum_1 = new System.Windows.Forms.Label();
		this._lblCount_0 = new System.Windows.Forms.Label();
		this._lblIntStatus_0 = new System.Windows.Forms.Label();
		this._lblCounterNum_0 = new System.Windows.Forms.Label();
		this.lblData = new System.Windows.Forms.Label();
		this.lblStatCol = new System.Windows.Forms.Label();
		this.lblCountCol = new System.Windows.Forms.Label();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.SuspendLayout();
		// 
		// cmdStartInt
		// 
		this.cmdStartInt.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStartInt.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStartInt.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStartInt.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStartInt.Location = new System.Drawing.Point(272, 248);
		this.cmdStartInt.Name = "cmdStartInt";
		this.cmdStartInt.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStartInt.Size = new System.Drawing.Size(57, 25);
		this.cmdStartInt.TabIndex = 4;
		this.cmdStartInt.Text = "Start";
		this.cmdStartInt.Click += new System.EventHandler(this.cmdStartInt_Click);
		// 
		// cmdStopRead
		// 
		this.cmdStopRead.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStopRead.Enabled = false;
		this.cmdStopRead.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStopRead.Location = new System.Drawing.Point(272, 248);
		this.cmdStopRead.Name = "cmdStopRead";
		this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStopRead.Size = new System.Drawing.Size(57, 25);
		this.cmdStopRead.TabIndex = 3;
		this.cmdStopRead.Text = "Quit";
		this.cmdStopRead.Visible = false;
		this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
		// 
		// tmrReadStatus
		// 
		this.tmrReadStatus.Interval = 200;
		this.tmrReadStatus.Tick += new System.EventHandler(this.tmrReadStatus_Tick);
		// 
		// lblShowTotal
		// 
		this.lblShowTotal.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowTotal.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowTotal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowTotal.ForeColor = System.Drawing.Color.Blue;
		this.lblShowTotal.Location = new System.Drawing.Point(168, 256);
		this.lblShowTotal.Name = "lblShowTotal";
		this.lblShowTotal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowTotal.Size = new System.Drawing.Size(65, 17);
		this.lblShowTotal.TabIndex = 18;
		// 
		// lblIntTotal
		// 
		this.lblIntTotal.BackColor = System.Drawing.SystemColors.Window;
		this.lblIntTotal.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblIntTotal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblIntTotal.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblIntTotal.Location = new System.Drawing.Point(56, 256);
		this.lblIntTotal.Name = "lblIntTotal";
		this.lblIntTotal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblIntTotal.Size = new System.Drawing.Size(105, 17);
		this.lblIntTotal.TabIndex = 22;
		this.lblIntTotal.Text = "Total Interrupts:";
		this.lblIntTotal.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblCount_4
		// 
		this._lblCount_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblCount_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCount_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCount_4.ForeColor = System.Drawing.Color.Blue;
		this._lblCount_4.Location = new System.Drawing.Point(216, 208);
		this._lblCount_4.Name = "_lblCount_4";
		this._lblCount_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCount_4.Size = new System.Drawing.Size(65, 17);
		this._lblCount_4.TabIndex = 17;
		this._lblCount_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblIntStatus_4
		// 
		this._lblIntStatus_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblIntStatus_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblIntStatus_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblIntStatus_4.ForeColor = System.Drawing.Color.Blue;
		this._lblIntStatus_4.Location = new System.Drawing.Point(120, 208);
		this._lblIntStatus_4.Name = "_lblIntStatus_4";
		this._lblIntStatus_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblIntStatus_4.Size = new System.Drawing.Size(73, 17);
		this._lblIntStatus_4.TabIndex = 12;
		// 
		// _lblCounterNum_4
		// 
		this._lblCounterNum_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblCounterNum_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCounterNum_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCounterNum_4.ForeColor = System.Drawing.Color.Black;
		this._lblCounterNum_4.Location = new System.Drawing.Point(72, 208);
		this._lblCounterNum_4.Name = "_lblCounterNum_4";
		this._lblCounterNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCounterNum_4.Size = new System.Drawing.Size(25, 17);
		this._lblCounterNum_4.TabIndex = 8;
		this._lblCounterNum_4.Text = "5";
		this._lblCounterNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblCount_3
		// 
		this._lblCount_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblCount_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCount_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCount_3.ForeColor = System.Drawing.Color.Blue;
		this._lblCount_3.Location = new System.Drawing.Point(216, 184);
		this._lblCount_3.Name = "_lblCount_3";
		this._lblCount_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCount_3.Size = new System.Drawing.Size(65, 17);
		this._lblCount_3.TabIndex = 16;
		this._lblCount_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblIntStatus_3
		// 
		this._lblIntStatus_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblIntStatus_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblIntStatus_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblIntStatus_3.ForeColor = System.Drawing.Color.Blue;
		this._lblIntStatus_3.Location = new System.Drawing.Point(120, 184);
		this._lblIntStatus_3.Name = "_lblIntStatus_3";
		this._lblIntStatus_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblIntStatus_3.Size = new System.Drawing.Size(73, 17);
		this._lblIntStatus_3.TabIndex = 11;
		// 
		// _lblCounterNum_3
		// 
		this._lblCounterNum_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblCounterNum_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCounterNum_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCounterNum_3.ForeColor = System.Drawing.Color.Black;
		this._lblCounterNum_3.Location = new System.Drawing.Point(72, 184);
		this._lblCounterNum_3.Name = "_lblCounterNum_3";
		this._lblCounterNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCounterNum_3.Size = new System.Drawing.Size(25, 17);
		this._lblCounterNum_3.TabIndex = 7;
		this._lblCounterNum_3.Text = "4";
		this._lblCounterNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblCount_2
		// 
		this._lblCount_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblCount_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCount_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCount_2.ForeColor = System.Drawing.Color.Blue;
		this._lblCount_2.Location = new System.Drawing.Point(216, 160);
		this._lblCount_2.Name = "_lblCount_2";
		this._lblCount_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCount_2.Size = new System.Drawing.Size(65, 17);
		this._lblCount_2.TabIndex = 15;
		this._lblCount_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblIntStatus_2
		// 
		this._lblIntStatus_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblIntStatus_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblIntStatus_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblIntStatus_2.ForeColor = System.Drawing.Color.Blue;
		this._lblIntStatus_2.Location = new System.Drawing.Point(120, 160);
		this._lblIntStatus_2.Name = "_lblIntStatus_2";
		this._lblIntStatus_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblIntStatus_2.Size = new System.Drawing.Size(73, 17);
		this._lblIntStatus_2.TabIndex = 10;
		// 
		// _lblCounterNum_2
		// 
		this._lblCounterNum_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblCounterNum_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCounterNum_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCounterNum_2.ForeColor = System.Drawing.Color.Black;
		this._lblCounterNum_2.Location = new System.Drawing.Point(72, 160);
		this._lblCounterNum_2.Name = "_lblCounterNum_2";
		this._lblCounterNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCounterNum_2.Size = new System.Drawing.Size(25, 17);
		this._lblCounterNum_2.TabIndex = 6;
		this._lblCounterNum_2.Text = "3";
		this._lblCounterNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblCount_1
		// 
		this._lblCount_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblCount_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCount_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCount_1.ForeColor = System.Drawing.Color.Blue;
		this._lblCount_1.Location = new System.Drawing.Point(216, 136);
		this._lblCount_1.Name = "_lblCount_1";
		this._lblCount_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCount_1.Size = new System.Drawing.Size(65, 17);
		this._lblCount_1.TabIndex = 14;
		this._lblCount_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblIntStatus_1
		// 
		this._lblIntStatus_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblIntStatus_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblIntStatus_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblIntStatus_1.ForeColor = System.Drawing.Color.Blue;
		this._lblIntStatus_1.Location = new System.Drawing.Point(120, 136);
		this._lblIntStatus_1.Name = "_lblIntStatus_1";
		this._lblIntStatus_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblIntStatus_1.Size = new System.Drawing.Size(73, 17);
		this._lblIntStatus_1.TabIndex = 9;
		// 
		// _lblCounterNum_1
		// 
		this._lblCounterNum_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblCounterNum_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCounterNum_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCounterNum_1.ForeColor = System.Drawing.Color.Black;
		this._lblCounterNum_1.Location = new System.Drawing.Point(72, 136);
		this._lblCounterNum_1.Name = "_lblCounterNum_1";
		this._lblCounterNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCounterNum_1.Size = new System.Drawing.Size(25, 17);
		this._lblCounterNum_1.TabIndex = 5;
		this._lblCounterNum_1.Text = "2";
		this._lblCounterNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblCount_0
		// 
		this._lblCount_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblCount_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCount_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCount_0.ForeColor = System.Drawing.Color.Blue;
		this._lblCount_0.Location = new System.Drawing.Point(216, 112);
		this._lblCount_0.Name = "_lblCount_0";
		this._lblCount_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCount_0.Size = new System.Drawing.Size(65, 17);
		this._lblCount_0.TabIndex = 13;
		this._lblCount_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblIntStatus_0
		// 
		this._lblIntStatus_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblIntStatus_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblIntStatus_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblIntStatus_0.ForeColor = System.Drawing.Color.Blue;
		this._lblIntStatus_0.Location = new System.Drawing.Point(120, 112);
		this._lblIntStatus_0.Name = "_lblIntStatus_0";
		this._lblIntStatus_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblIntStatus_0.Size = new System.Drawing.Size(73, 17);
		this._lblIntStatus_0.TabIndex = 2;
		// 
		// _lblCounterNum_0
		// 
		this._lblCounterNum_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblCounterNum_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblCounterNum_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblCounterNum_0.ForeColor = System.Drawing.Color.Black;
		this._lblCounterNum_0.Location = new System.Drawing.Point(72, 112);
		this._lblCounterNum_0.Name = "_lblCounterNum_0";
		this._lblCounterNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblCounterNum_0.Size = new System.Drawing.Size(25, 17);
		this._lblCounterNum_0.TabIndex = 1;
		this._lblCounterNum_0.Text = "1";
		this._lblCounterNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData
		// 
		this.lblData.BackColor = System.Drawing.SystemColors.Window;
		this.lblData.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData.Location = new System.Drawing.Point(208, 80);
		this.lblData.Name = "lblData";
		this.lblData.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData.Size = new System.Drawing.Size(81, 17);
		this.lblData.TabIndex = 21;
		this.lblData.Text = "Data Value";
		this.lblData.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblStatCol
		// 
		this.lblStatCol.BackColor = System.Drawing.SystemColors.Window;
		this.lblStatCol.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblStatCol.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblStatCol.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblStatCol.Location = new System.Drawing.Point(128, 80);
		this.lblStatCol.Name = "lblStatCol";
		this.lblStatCol.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblStatCol.Size = new System.Drawing.Size(57, 17);
		this.lblStatCol.TabIndex = 20;
		this.lblStatCol.Text = "Status";
		this.lblStatCol.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblCountCol
		// 
		this.lblCountCol.BackColor = System.Drawing.SystemColors.Window;
		this.lblCountCol.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblCountCol.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblCountCol.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblCountCol.Location = new System.Drawing.Point(56, 80);
		this.lblCountCol.Name = "lblCountCol";
		this.lblCountCol.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblCountCol.Size = new System.Drawing.Size(57, 17);
		this.lblCountCol.TabIndex = 19;
		this.lblCountCol.Text = "Counter";
		this.lblCountCol.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(32, 16);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(281, 41);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of 9513 Counter using Interrupts";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frm9513Int
		// 
		this.AcceptButton = this.cmdStopRead;
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(350, 296);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdStartInt,
																		this.cmdStopRead,
																		this.lblShowTotal,
																		this.lblIntTotal,
																		this._lblCount_4,
																		this._lblIntStatus_4,
																		this._lblCounterNum_4,
																		this._lblCount_3,
																		this._lblIntStatus_3,
																		this._lblCounterNum_3,
																		this._lblCount_2,
																		this._lblIntStatus_2,
																		this._lblCounterNum_2,
																		this._lblCount_1,
																		this._lblIntStatus_1,
																		this._lblCounterNum_1,
																		this._lblCount_0,
																		this._lblIntStatus_0,
																		this._lblCounterNum_0,
																		this.lblData,
																		this.lblStatCol,
																		this.lblCountCol,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frm9513Int";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library 9513 Counter Demo";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frm9513Int());
		}
	    

	    
		

		


		

	}
}