// ==============================================================================

//  File:                         CInScan03.CS
//
//  Library Call Demonstrated:    MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan()
//
//  Purpose:                      Scans a Counter Input in encoder mode and stores
//                                the sample data in an array.
//
//  Demonstration:                Displays counts from encoder as phase A, phase B,
//                                and totalizes the index on Z.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//                                MccDaq.MccService.WinBufAlloc32
//                                MccDaq.MccService.WinBufToArray32()
//                                MccDaq.MccService.WinBufFree()
//
//  Special Requirements:         Board 0 must support counter scans in encoder mode.
//                                Phase A from encode connected to counter 0 input.
//                                Phase B from encode connected to counter 1 input.
//                                Index Z from encode connected to counter 2 input.
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

		const int NumPoints = 50;    //  Number of data points to collect
		const int FirstPoint = 0;     //  set first element in buffer to transfer to array

		private MccDaq.MccBoard DaqBoard;
		private int LastCtr;
		private uint[] CounterData = new uint[NumPoints];
        internal System.Windows.Forms.TextBox txtEncoderValues;
        public System.Windows.Forms.Label label2;
      
      //  dimension an array to hold the input values
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
         this.txtEncoderValues = new System.Windows.Forms.TextBox();
         this.label2 = new System.Windows.Forms.Label();
         this.SuspendLayout();
         // 
         // cmdStopConvert
         // 
         this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
         this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdStopConvert.Location = new System.Drawing.Point(296, 360);
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
         this.cmdStart.Location = new System.Drawing.Point(224, 360);
         this.cmdStart.Name = "cmdStart";
         this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdStart.Size = new System.Drawing.Size(58, 26);
         this.cmdStart.TabIndex = 18;
         this.cmdStart.Text = "Start";
         this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
         // 
         // txtEncoderValues
         // 
         this.txtEncoderValues.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.txtEncoderValues.ForeColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(0)), ((System.Byte)(192)));
         this.txtEncoderValues.Location = new System.Drawing.Point(12, 48);
         this.txtEncoderValues.Multiline = true;
         this.txtEncoderValues.Name = "txtEncoderValues";
         this.txtEncoderValues.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
         this.txtEncoderValues.Size = new System.Drawing.Size(352, 304);
         this.txtEncoderValues.TabIndex = 46;
         this.txtEncoderValues.Text = "";
         // 
         // label2
         // 
         this.label2.BackColor = System.Drawing.SystemColors.Window;
         this.label2.Cursor = System.Windows.Forms.Cursors.Default;
         this.label2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.label2.ForeColor = System.Drawing.SystemColors.WindowText;
         this.label2.Location = new System.Drawing.Point(12, 0);
         this.label2.Name = "label2";
         this.label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.label2.Size = new System.Drawing.Size(352, 40);
         this.label2.TabIndex = 47;
         this.label2.Text = "Demonstration of MccDaq.CConfigScan() and Mccdaq.MccBoard.CInScan() used with enc" +
            "oders";
         this.label2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
         // 
         // frmDataDisplay
         // 
         this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
         this.BackColor = System.Drawing.SystemColors.Window;
         this.ClientSize = new System.Drawing.Size(376, 397);
         this.Controls.Add(this.txtEncoderValues);
         this.Controls.Add(this.cmdStopConvert);
         this.Controls.Add(this.cmdStart);
         this.Controls.Add(this.label2);
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
			int MapChannel;

			cmdStart.Enabled = false;

			FirstCtr = 0; //  first channel to acquire
			LastCtr = 0;
		    
		    // Setup Counter 0 
			// Parameters:
			//   BoardNum       :the number used by CB.CFG to describe this board
			//   CounterNum     :counter to set up
			//   Mode           :counter Mode
			//   DebounceTime   :debounce Time
			//   DebounceMode   :debounce Mode
			//   EdgeDetection  :determines whether the rising edge or falling edge is to be detected
			//   TickSize       :reserved.
			//   MapChannel     :mapped channel

            // Counter 0
		    CounterNum = 0;
		    Mode = MccDaq.CounterMode.Encoder|MccDaq.CounterMode.EncoderModeX1|MccDaq.CounterMode.ClearOnZOn;
		    DebounceTime = MccDaq.CounterDebounceTime.DebounceNone;
		    DebounceMode = 0;
		    EdgeDetection = MccDaq.CounterEdgeDetection.RisingEdge;
		    TickSize = 0;
		    MapChannel = 2;

		    ULStat = DaqBoard.CConfigScan(CounterNum, Mode, DebounceTime, DebounceMode, EdgeDetection, TickSize, MapChannel);

		    //  Collect the values by calling MccDaq.MccBoard.CInScan function
		    //  Parameters:
		    //    FirstCtr   :the first counter of the scan
		    //    LastCtr    :the last counter of the scan
		    //    Count      :the total number of counter samples to collect
		    //    Rate       :sample rate
		    //    MemHandle  :Handle for Windows buffer to store data in
		    //    Options    :data collection options

		    Count = NumPoints;	//  total number of data points to collect
		    Rate = 10;			//  per channel sampling rate ((samples per second) per channel)
		    Options = MccDaq.ScanOptions.Ctr32Bit;

		    ULStat = DaqBoard.CInScan( FirstCtr, LastCtr, Count, ref Rate, MemHandle, Options);

		    //  Transfer the data from the memory buffer set up by Windows to an array
		    ULStat = MccDaq.MccService.WinBufToArray32( MemHandle, out CounterData[0], FirstPoint, Count);

             string NL = Environment.NewLine;
             txtEncoderValues.Text = " Counter Data" + NL + NL;
             
             for (int sample=0; sample<Count; sample++)
             {
                txtEncoderValues.Text += CounterData[sample].ToString("d").PadLeft(6) +NL;
             }
         
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