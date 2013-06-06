// ==============================================================================

//  File:                         CInScan02.CS
//
//  Library Call Demonstrated:    MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan()
//
//  Purpose:                      Scans a Counter Input in decrement mode and stores
//                                the sample data in an array.
//
//  Demonstration:                Displays counts on counter 0.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//                                MccDaq.MccService.WinBufAlloc32
//                                MccDaq.MccService.WinBufToArray32()
//                                MccDaq.MccService.WinBufFree()
//
//  Special Requirements:         Board 0 must support counter scan function.
//                                TTL signals on selected counter inputs.
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

namespace CounterInScan
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdStart;
	    public Label _lblCounterData_4;
		public Label _lblCounterData_3;
		public Label _lblCounterData_2;
		public Label _lblCounterData_1;
		public Label _lblCounterData_0;
		public Label lblChan0;
		public Label lblDemoFunction;
		public Label[] lblCounterData;


		const int NumPoints = 100;    //  Number of data points to collect
		const int FirstPoint = 0;     //  set first element in buffer to transfer to array

		private MccDaq.MccBoard DaqBoard;
		private int LastCtr;
		private uint[] CounterData = new uint[NumPoints];
	  private System.Windows.Forms.Label label1; //  dimension an array to hold the input values
		private int MemHandle = 0;	//  define a variable to contain the handle for memory allocated 
		//  by Windows through MccDaq.MccService.WinBufAlloc()
 
		public frmDataDisplay()
		{
			MccDaq.ErrorInfo ULStat;

			// This call is required by the Windows Form Designer.
			InitializeComponent();

			//  Initiate error handling
			//   activating error handling will trap errors like
			//   bad channel numbers and non-configured conditions.
			//   Parameters:
			//     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
		
			ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
		

			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);

			// Allocate memory buffer to hold data..
			MemHandle = MccDaq.MccService.WinBufAlloc32(NumPoints); //  set aside memory to hold data
		

			//  This gives us access to labels via an indexed array
			lblCounterData = (new Label[] {this._lblCounterData_0, this._lblCounterData_1, this._lblCounterData_2, this._lblCounterData_3, this._lblCounterData_4});  

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

				// be sure to release the memory buffer... 
				if ( MemHandle != 0)
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
		  this.cmdStopConvert = new System.Windows.Forms.Button();
		  this.cmdStart = new System.Windows.Forms.Button();
		  this._lblCounterData_4 = new System.Windows.Forms.Label();
		  this._lblCounterData_3 = new System.Windows.Forms.Label();
		  this._lblCounterData_2 = new System.Windows.Forms.Label();
		  this._lblCounterData_1 = new System.Windows.Forms.Label();
		  this._lblCounterData_0 = new System.Windows.Forms.Label();
		  this.lblChan0 = new System.Windows.Forms.Label();
		  this.lblDemoFunction = new System.Windows.Forms.Label();
		  this.label1 = new System.Windows.Forms.Label();
		  this.SuspendLayout();
		  // 
		  // cmdStopConvert
		  // 
		  this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
		  this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
		  this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.cmdStopConvert.Location = new System.Drawing.Point(280, 272);
		  this.cmdStopConvert.Name = "cmdStopConvert";
		  this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdStopConvert.Size = new System.Drawing.Size(58, 26);
		  this.cmdStopConvert.TabIndex = 17;
		  this.cmdStopConvert.Text = "Quit";
		  this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
		  // 
		  // cmdStart
		  // 
		  this.cmdStart.BackColor = System.Drawing.SystemColors.Control;
		  this.cmdStart.Cursor = System.Windows.Forms.Cursors.Default;
		  this.cmdStart.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.cmdStart.Location = new System.Drawing.Point(208, 272);
		  this.cmdStart.Name = "cmdStart";
		  this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdStart.Size = new System.Drawing.Size(58, 26);
		  this.cmdStart.TabIndex = 18;
		  this.cmdStart.Text = "Start";
		  this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
		  // 
		  // _lblCounterData_4
		  // 
		  this._lblCounterData_4.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_4.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_4.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_4.Location = new System.Drawing.Point(136, 184);
		  this._lblCounterData_4.Name = "_lblCounterData_4";
		  this._lblCounterData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_4.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_4.TabIndex = 12;
		  this._lblCounterData_4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		  // 
		  // _lblCounterData_3
		  // 
		  this._lblCounterData_3.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_3.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_3.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_3.Location = new System.Drawing.Point(136, 160);
		  this._lblCounterData_3.Name = "_lblCounterData_3";
		  this._lblCounterData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_3.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_3.TabIndex = 12;
		  this._lblCounterData_3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		  // 
		  // _lblCounterData_2
		  // 
		  this._lblCounterData_2.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_2.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_2.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_2.Location = new System.Drawing.Point(136, 136);
		  this._lblCounterData_2.Name = "_lblCounterData_2";
		  this._lblCounterData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_2.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_2.TabIndex = 11;
		  this._lblCounterData_2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		  // 
		  // _lblCounterData_1
		  // 
		  this._lblCounterData_1.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_1.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_1.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_1.Location = new System.Drawing.Point(136, 112);
		  this._lblCounterData_1.Name = "_lblCounterData_1";
		  this._lblCounterData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_1.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_1.TabIndex = 10;
		  this._lblCounterData_1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		  // 
		  // _lblCounterData_0
		  // 
		  this._lblCounterData_0.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_0.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_0.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_0.Location = new System.Drawing.Point(136, 90);
		  this._lblCounterData_0.Name = "_lblCounterData_0";
		  this._lblCounterData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_0.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_0.TabIndex = 9;
		  this._lblCounterData_0.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		  // 
		  // lblChan0
		  // 
		  this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan0.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan0.Location = new System.Drawing.Point(136, 64);
		  this.lblChan0.Name = "lblChan0";
		  this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan0.Size = new System.Drawing.Size(65, 17);
		  this.lblChan0.TabIndex = 1;
		  this.lblChan0.Text = "Counter 0";
		  this.lblChan0.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		  // 
		  // lblDemoFunction
		  // 
		  this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		  this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblDemoFunction.Location = new System.Drawing.Point(8, 8);
		  this.lblDemoFunction.Name = "lblDemoFunction";
		  this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblDemoFunction.Size = new System.Drawing.Size(337, 41);
		  this.lblDemoFunction.TabIndex = 0;
		  this.lblDemoFunction.Text = "Demonstration of MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan()";
		  this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // label1
		  // 
		  this.label1.Location = new System.Drawing.Point(8, 216);
		  this.label1.Name = "label1";
		  this.label1.Size = new System.Drawing.Size(328, 40);
		  this.label1.TabIndex = 19;
		  this.label1.Text = "Note: Pulse source must be connected to the mapped counter (Counter 1) to decreme" +
			"nt. Pulses on Counter 0 input will increment the count.";
		  // 
		  // frmDataDisplay
		  // 
		  this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		  this.BackColor = System.Drawing.SystemColors.Window;
		  this.ClientSize = new System.Drawing.Size(349, 309);
		  this.Controls.AddRange(new System.Windows.Forms.Control[] {
																	  this.label1,
																	  this.cmdStopConvert,
																	  this.cmdStart,
																	  this._lblCounterData_4,
																	  this._lblCounterData_3,
																	  this._lblCounterData_2,
																	  this._lblCounterData_1,
																	  this._lblCounterData_0,
																	  this.lblChan0,
																	  this.lblDemoFunction});
		  this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.ForeColor = System.Drawing.Color.Blue;
		  this.Location = new System.Drawing.Point(190, 108);
		  this.Name = "frmDataDisplay";
		  this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		  this.Text = "Universal Library Counter Input Scan";
		  this.ResumeLayout(false);

		}

		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmDataDisplay());
		}
    

		private void cmdStart_Click(object eventSender, System.EventArgs eventArgs) 
		{
			int i;
			MccDaq.ErrorInfo ULStat;
			int Rate;
			int Count;
			int FirstCtr;
			MccDaq.ScanOptions Options;

		    int CounterNum;
			MccDaq.CounterMode Mode;
			MccDaq.CounterDebounceTime DebounceTime;
			MccDaq.CounterDebounceMode DebounceMode;
			MccDaq.CounterEdgeDetection EdgeDetection;
			MccDaq.CounterTickSize TickSize;
			int MapCounter;

			cmdStart.Enabled = false;

			FirstCtr = 0; //  first channel to acquire
			LastCtr = 0;
		    
		    // Setup Counter 0 for decrement mode mapped in from counter 1
			// Parameters:
			//   BoardNum       :the number used by CB.CFG to describe this board
			//   CounterNum     :counter to set up
			//   Mode           :counter Mode
			//   DebounceTime   :debounce Time
			//   DebounceMode   :debounce Mode
			//   EdgeDetection  :determines whether the rising edge or falling edge is to be detected
			//   TickSize       :reserved.
			//   MapCounter     :mapped counter


			CounterNum = FirstCtr;
			Mode = MccDaq.CounterMode.DecrementOn;
			DebounceTime = MccDaq.CounterDebounceTime.DebounceNone;
			DebounceMode = 0;
			EdgeDetection = MccDaq.CounterEdgeDetection.FallingEdge;
			TickSize = 0;
			MapCounter = 1;

			ULStat = DaqBoard.CConfigScan(CounterNum, Mode, DebounceTime, DebounceMode, EdgeDetection, TickSize, MapCounter);

			//  Collect the values by calling MccDaq.MccBoard.CInScan function
			//  Parameters:
			//    FirstCtr   :the first counter of the scan
			//    LastCtr    :the last counter of the scan
			//    Count      :the total number of counter samples to collect
			//    Rate       :sample rate
			//    MemHandle  :Handle for Windows buffer to store data in
			//    Options    :data collection options

			Count = NumPoints;	//  total number of data points to collect
			Rate = 390;			//  per channel sampling rate ((samples per second) per channel)
			Options = MccDaq.ScanOptions.Ctr32Bit;

			ULStat = DaqBoard.CInScan( FirstCtr, LastCtr, Count, ref Rate, MemHandle, Options);

			//  Transfer the data from the memory buffer set up by Windows to an array
			ULStat = MccDaq.MccService.WinBufToArray32( MemHandle, out CounterData[0], FirstPoint, Count);

			for (i=0; i<=4; ++i)
				lblCounterData[i].Text = CounterData[i].ToString("D");
       
			cmdStart.Enabled = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs)
		{
			MccDaq.ErrorInfo ULStat;

			ULStat = MccDaq.MccService.WinBufFree(MemHandle); //  Free up memory for use by
			//  other programs
			MemHandle = 0;

			Application.Exit();
		}

	}
}