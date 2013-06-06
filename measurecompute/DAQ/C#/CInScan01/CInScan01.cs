// ==============================================================================

//  File:                         CInScan01.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.CInScan()in Foreground mode
//                                with scan options = MccDaq.ScanOptions.ConvertData
//
//  Purpose:                      Scans a range of Counter Input Channels and stores
//                                the sample data in an array.
//
//  Demonstration:                Displays the counter input on up to four channels.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//                                MccDaq.MccService.WinBufAlloc32
//                                MccDaq.MccService.WinBufToArray32()
//                                MccDaq.MccService.WinBufFree()
//
//  Special Requirements:         Board 0 must support counter scan function.
//								  TTL signals on selected counter inputs.
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
		public TextBox txtLastCtr;
		public Button cmdStopConvert;
		public Button cmdStart;
		public Label Label1;
		public Label _lblCounterData_3;
		public Label lblChan3;
		public Label _lblCounterData_2;
		public Label lblChan2;
		public Label _lblCounterData_1;
		public Label lblChan1;
		public Label _lblCounterData_0;
		public Label lblChan0;
		public Label lblDemoFunction;
		public Label[] lblCounterData;


		const int NumPoints = 600;    //  Number of data points to collect
		const int FirstPoint = 0;     //  set first element in buffer to transfer to array

		private MccDaq.MccBoard DaqBoard;
		private int LastCtr;
		private uint[] CounterData = new uint[NumPoints]; //  dimension an array to hold the input values
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
			lblCounterData = (new Label[] {this._lblCounterData_0, this._lblCounterData_1, this._lblCounterData_2, this._lblCounterData_3});  

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
		  this.txtLastCtr = new System.Windows.Forms.TextBox();
		  this.cmdStopConvert = new System.Windows.Forms.Button();
		  this.cmdStart = new System.Windows.Forms.Button();
		  this.Label1 = new System.Windows.Forms.Label();
		  this._lblCounterData_3 = new System.Windows.Forms.Label();
		  this.lblChan3 = new System.Windows.Forms.Label();
		  this._lblCounterData_2 = new System.Windows.Forms.Label();
		  this.lblChan2 = new System.Windows.Forms.Label();
		  this._lblCounterData_1 = new System.Windows.Forms.Label();
		  this.lblChan1 = new System.Windows.Forms.Label();
		  this._lblCounterData_0 = new System.Windows.Forms.Label();
		  this.lblChan0 = new System.Windows.Forms.Label();
		  this.lblDemoFunction = new System.Windows.Forms.Label();
		  this.SuspendLayout();
		  // 
		  // txtLastCtr
		  // 
		  this.txtLastCtr.AcceptsReturn = true;
		  this.txtLastCtr.AutoSize = false;
		  this.txtLastCtr.BackColor = System.Drawing.SystemColors.Window;
		  this.txtLastCtr.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		  this.txtLastCtr.Cursor = System.Windows.Forms.Cursors.IBeam;
		  this.txtLastCtr.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.txtLastCtr.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.txtLastCtr.Location = new System.Drawing.Point(222, 64);
		  this.txtLastCtr.MaxLength = 0;
		  this.txtLastCtr.Name = "txtLastCtr";
		  this.txtLastCtr.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.txtLastCtr.Size = new System.Drawing.Size(33, 19);
		  this.txtLastCtr.TabIndex = 20;
		  this.txtLastCtr.Text = "3";
		  this.txtLastCtr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
		  // 
		  // cmdStopConvert
		  // 
		  this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
		  this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
		  this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.cmdStopConvert.Location = new System.Drawing.Point(280, 192);
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
		  this.cmdStart.Location = new System.Drawing.Point(208, 192);
		  this.cmdStart.Name = "cmdStart";
		  this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.cmdStart.Size = new System.Drawing.Size(58, 26);
		  this.cmdStart.TabIndex = 18;
		  this.cmdStart.Text = "Start";
		  this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
		  // 
		  // Label1
		  // 
		  this.Label1.BackColor = System.Drawing.SystemColors.Window;
		  this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
		  this.Label1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.Label1.Location = new System.Drawing.Point(94, 66);
		  this.Label1.Name = "Label1";
		  this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.Label1.Size = new System.Drawing.Size(120, 17);
		  this.Label1.TabIndex = 19;
		  this.Label1.Text = "Measure Counter 0 to";
		  // 
		  // _lblCounterData_3
		  // 
		  this._lblCounterData_3.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_3.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_3.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_3.Location = new System.Drawing.Point(178, 166);
		  this._lblCounterData_3.Name = "_lblCounterData_3";
		  this._lblCounterData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_3.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_3.TabIndex = 12;
		  // 
		  // lblChan3
		  // 
		  this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan3.Location = new System.Drawing.Point(106, 166);
		  this.lblChan3.Name = "lblChan3";
		  this.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan3.Size = new System.Drawing.Size(65, 17);
		  this.lblChan3.TabIndex = 4;
		  this.lblChan3.Text = "Counter 3:";
		  // 
		  // _lblCounterData_2
		  // 
		  this._lblCounterData_2.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_2.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_2.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_2.Location = new System.Drawing.Point(178, 141);
		  this._lblCounterData_2.Name = "_lblCounterData_2";
		  this._lblCounterData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_2.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_2.TabIndex = 11;
		  // 
		  // lblChan2
		  // 
		  this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan2.Location = new System.Drawing.Point(106, 141);
		  this.lblChan2.Name = "lblChan2";
		  this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan2.Size = new System.Drawing.Size(65, 17);
		  this.lblChan2.TabIndex = 3;
		  this.lblChan2.Text = "Counter 2:";
		  // 
		  // _lblCounterData_1
		  // 
		  this._lblCounterData_1.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_1.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_1.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_1.Location = new System.Drawing.Point(178, 115);
		  this._lblCounterData_1.Name = "_lblCounterData_1";
		  this._lblCounterData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_1.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_1.TabIndex = 10;
		  // 
		  // lblChan1
		  // 
		  this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan1.Location = new System.Drawing.Point(106, 115);
		  this.lblChan1.Name = "lblChan1";
		  this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan1.Size = new System.Drawing.Size(65, 17);
		  this.lblChan1.TabIndex = 2;
		  this.lblChan1.Text = "Counter 1:";
		  // 
		  // _lblCounterData_0
		  // 
		  this._lblCounterData_0.BackColor = System.Drawing.SystemColors.Window;
		  this._lblCounterData_0.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblCounterData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblCounterData_0.ForeColor = System.Drawing.Color.Blue;
		  this._lblCounterData_0.Location = new System.Drawing.Point(178, 90);
		  this._lblCounterData_0.Name = "_lblCounterData_0";
		  this._lblCounterData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblCounterData_0.Size = new System.Drawing.Size(65, 17);
		  this._lblCounterData_0.TabIndex = 9;
		  // 
		  // lblChan0
		  // 
		  this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
		  this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblChan0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblChan0.Location = new System.Drawing.Point(106, 90);
		  this.lblChan0.Name = "lblChan0";
		  this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblChan0.Size = new System.Drawing.Size(65, 17);
		  this.lblChan0.TabIndex = 1;
		  this.lblChan0.Text = "Counter 0:";
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
		  this.lblDemoFunction.Text = "Demonstration of MccBoard.CInScan() with scan option set to MccDaq.ScanOptions.Fo" +
			"reground";
		  this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // frmDataDisplay
		  // 
		  this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		  this.BackColor = System.Drawing.SystemColors.Window;
		  this.ClientSize = new System.Drawing.Size(349, 232);
		  this.Controls.AddRange(new System.Windows.Forms.Control[] {
																	  this.txtLastCtr,
																	  this.cmdStopConvert,
																	  this.cmdStart,
																	  this.Label1,
																	  this._lblCounterData_3,
																	  this.lblChan3,
																	  this._lblCounterData_2,
																	  this.lblChan2,
																	  this._lblCounterData_1,
																	  this.lblChan1,
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
			int j;
			int i;
			MccDaq.ErrorInfo ULStat;
			int Rate;
			int Count;
			int FirstCtr;
			MccDaq.ScanOptions Options;

			cmdStart.Enabled = false;

			//  Collect the values by calling MccDaq.MccBoard.CInScan function
			//  Parameters:
			//    FirstCtr   :the first counter of the scan
			//    LastCtr    :the last counter of the scan
			//    Count      :the total number of counter samples to collect
			//    Rate       :sample rate
			//    MemHandle  :Handle for Windows buffer to store data in
			//    Options    :data collection options
			FirstCtr = 0; //  first channel to acquire
			LastCtr = int.Parse(txtLastCtr.Text); //  last channel to acquire
			if ((LastCtr > 3)) LastCtr = 3;
			txtLastCtr.Text = LastCtr.ToString();

			Count = NumPoints;	//  total number of data points to collect
			Rate = 390;			//  per channel sampling rate ((samples per second) per channel)
			Options = MccDaq.ScanOptions.Ctr32Bit;

			ULStat = DaqBoard.CInScan( FirstCtr, LastCtr, Count, ref Rate, MemHandle, Options);

			//  Transfer the data from the memory buffer set up by Windows to an array
			ULStat = MccDaq.MccService.WinBufToArray32( MemHandle, out CounterData[0], FirstPoint, Count);

			for (i=0; i<=LastCtr; ++i)
				lblCounterData[i].Text = CounterData[Count-1-LastCtr+i].ToString("D");
        
			for (j=LastCtr + 1; j<=3; ++j)
				lblCounterData[j].Text = "0";
       
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