// ==============================================================================
//
//  File:                         ULAI12.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.AInScan()
//                                with scan options = MccDaq.ScanOptions.ExtClock
//
//  Purpose:                      Scans a range of A/D Input Channels and stores
//                                the sample data in an array at a sample rate
//                                specified by an external clock.
//
//  Demonstration:                Displays the analog input on two channels.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have an A/D converter and
//                                support the EXTCLOCK option.
//                                Analog signals on two input channels.
//                                Freq. on trigger 0 input.
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

namespace ULAI12
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public TextBox txtHighChan;
		public Button cmdStart;
		public Button cmdStopConvert;
		public Timer tmrConvert;
		public Label Label1;
		public Label _lblADData_7;
		public Label lblChan7;
		public Label _lblADData_3;
		public Label lblChan3;
		public Label _lblADData_6;
		public Label lblChan6;
		public Label _lblADData_2;
		public Label lblChan2;
		public Label _lblADData_5;
		public Label lblChan5;
		public Label _lblADData_1;
		public Label lblChan1;
		public Label _lblADData_4;
		public Label lblChan4;
		public Label _lblADData_0;
		public Label lblChan0;
		public Label lblWarn;
		public Label lblDemoFunction;

		public Label[] lblADData;

		const int NumPoints = 8;  //  Number of data points to collect
		const int FirstPoint = 0; //  set first element in buffer to transfer to array

		private MccDaq.MccBoard DaqBoard;
		private int HighChan;
		private ushort[] ADData = new ushort[NumPoints];  // array to hold the input values
		private int MemHandle=0;    //  define a variable to contain the handle for
									// memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		


		public frmDataDisplay()
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

			//  set aside memory to hold data
			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			

			lblADData = (new Label[]{_lblADData_0, _lblADData_1, _lblADData_2, _lblADData_3,
									_lblADData_4, _lblADData_5, _lblADData_6, _lblADData_7});
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
			this.txtHighChan = new System.Windows.Forms.TextBox();
			this.cmdStart = new System.Windows.Forms.Button();
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this.tmrConvert = new System.Windows.Forms.Timer(this.components);
			this.Label1 = new System.Windows.Forms.Label();
			this._lblADData_7 = new System.Windows.Forms.Label();
			this.lblChan7 = new System.Windows.Forms.Label();
			this._lblADData_3 = new System.Windows.Forms.Label();
			this.lblChan3 = new System.Windows.Forms.Label();
			this._lblADData_6 = new System.Windows.Forms.Label();
			this.lblChan6 = new System.Windows.Forms.Label();
			this._lblADData_2 = new System.Windows.Forms.Label();
			this.lblChan2 = new System.Windows.Forms.Label();
			this._lblADData_5 = new System.Windows.Forms.Label();
			this.lblChan5 = new System.Windows.Forms.Label();
			this._lblADData_1 = new System.Windows.Forms.Label();
			this.lblChan1 = new System.Windows.Forms.Label();
			this._lblADData_4 = new System.Windows.Forms.Label();
			this.lblChan4 = new System.Windows.Forms.Label();
			this._lblADData_0 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblWarn = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// txtHighChan
			//
			this.txtHighChan.AcceptsReturn = true;
			this.txtHighChan.AutoSize = false;
			this.txtHighChan.BackColor = System.Drawing.SystemColors.Window;
			this.txtHighChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtHighChan.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtHighChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtHighChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtHighChan.Location = new System.Drawing.Point(208, 84);
			this.txtHighChan.MaxLength = 0;
			this.txtHighChan.Name = "txtHighChan";
			this.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtHighChan.Size = new System.Drawing.Size(25, 19);
			this.txtHighChan.TabIndex = 21;
			this.txtHighChan.Text = "3";
			this.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			//
			// cmdStart
			//
			this.cmdStart.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStart.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStart.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStart.Location = new System.Drawing.Point(264, 208);
			this.cmdStart.Name = "cmdStart";
			this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStart.Size = new System.Drawing.Size(65, 25);
			this.cmdStart.TabIndex = 19;
			this.cmdStart.Text = "Start";
			this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
			//
			// cmdStopConvert
			//
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(264, 208);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(65, 25);
			this.cmdStopConvert.TabIndex = 17;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Visible = false;
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			//
			// tmrConvert
			//
			this.tmrConvert.Interval = 500;
			this.tmrConvert.Tick += new System.EventHandler(this.tmrConvert_Tick);
			//
			// Label1
			//
			this.Label1.BackColor = System.Drawing.SystemColors.Window;
			this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label1.Location = new System.Drawing.Point(64, 87);
			this.Label1.Name = "Label1";
			this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label1.Size = new System.Drawing.Size(137, 16);
			this.Label1.TabIndex = 20;
			this.Label1.Text = "Measure Channels 0 to";
			//
			// _lblADData_7
			//
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Location = new System.Drawing.Point(264, 187);
			this._lblADData_7.Name = "_lblADData_7";
			this._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_7.Size = new System.Drawing.Size(65, 17);
			this._lblADData_7.TabIndex = 16;
			//
			// lblChan7
			//
			this.lblChan7.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan7.Location = new System.Drawing.Point(184, 187);
			this.lblChan7.Name = "lblChan7";
			this.lblChan7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan7.Size = new System.Drawing.Size(73, 17);
			this.lblChan7.TabIndex = 8;
			this.lblChan7.Text = "Channel 7:";
			this.lblChan7.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_3
			//
			this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_3.Location = new System.Drawing.Point(96, 187);
			this._lblADData_3.Name = "_lblADData_3";
			this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_3.Size = new System.Drawing.Size(65, 17);
			this._lblADData_3.TabIndex = 12;
			//
			// lblChan3
			//
			this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan3.Location = new System.Drawing.Point(16, 187);
			this.lblChan3.Name = "lblChan3";
			this.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan3.Size = new System.Drawing.Size(73, 17);
			this.lblChan3.TabIndex = 4;
			this.lblChan3.Text = "Channel 3:";
			this.lblChan3.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_6
			//
			this._lblADData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_6.Location = new System.Drawing.Point(264, 161);
			this._lblADData_6.Name = "_lblADData_6";
			this._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_6.Size = new System.Drawing.Size(65, 17);
			this._lblADData_6.TabIndex = 15;
			//
			// lblChan6
			//
			this.lblChan6.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan6.Location = new System.Drawing.Point(184, 161);
			this.lblChan6.Name = "lblChan6";
			this.lblChan6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan6.Size = new System.Drawing.Size(73, 17);
			this.lblChan6.TabIndex = 7;
			this.lblChan6.Text = "Channel 6:";
			this.lblChan6.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_2
			//
			this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_2.Location = new System.Drawing.Point(96, 161);
			this._lblADData_2.Name = "_lblADData_2";
			this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_2.Size = new System.Drawing.Size(65, 17);
			this._lblADData_2.TabIndex = 11;
			//
			// lblChan2
			//
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan2.Location = new System.Drawing.Point(16, 161);
			this.lblChan2.Name = "lblChan2";
			this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan2.Size = new System.Drawing.Size(73, 17);
			this.lblChan2.TabIndex = 3;
			this.lblChan2.Text = "Channel 2:";
			this.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_5
			//
			this._lblADData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_5.Location = new System.Drawing.Point(264, 135);
			this._lblADData_5.Name = "_lblADData_5";
			this._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_5.Size = new System.Drawing.Size(65, 17);
			this._lblADData_5.TabIndex = 14;
			//
			// lblChan5
			//
			this.lblChan5.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan5.Location = new System.Drawing.Point(184, 135);
			this.lblChan5.Name = "lblChan5";
			this.lblChan5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan5.Size = new System.Drawing.Size(73, 17);
			this.lblChan5.TabIndex = 6;
			this.lblChan5.Text = "Channel 5:";
			this.lblChan5.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_1
			//
			this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_1.Location = new System.Drawing.Point(96, 135);
			this._lblADData_1.Name = "_lblADData_1";
			this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_1.Size = new System.Drawing.Size(65, 17);
			this._lblADData_1.TabIndex = 10;
			//
			// lblChan1
			//
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan1.Location = new System.Drawing.Point(16, 135);
			this.lblChan1.Name = "lblChan1";
			this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1.Size = new System.Drawing.Size(73, 17);
			this.lblChan1.TabIndex = 2;
			this.lblChan1.Text = "Channel 1:";
			this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_4
			//
			this._lblADData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_4.Location = new System.Drawing.Point(264, 110);
			this._lblADData_4.Name = "_lblADData_4";
			this._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_4.Size = new System.Drawing.Size(65, 17);
			this._lblADData_4.TabIndex = 13;
			//
			// lblChan4
			//
			this.lblChan4.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan4.Location = new System.Drawing.Point(184, 110);
			this.lblChan4.Name = "lblChan4";
			this.lblChan4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan4.Size = new System.Drawing.Size(73, 17);
			this.lblChan4.TabIndex = 5;
			this.lblChan4.Text = "Channel 4:";
			this.lblChan4.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_0
			//
			this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_0.Location = new System.Drawing.Point(96, 110);
			this._lblADData_0.Name = "_lblADData_0";
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.Size = new System.Drawing.Size(65, 17);
			this._lblADData_0.TabIndex = 9;
			//
			// lblChan0
			//
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan0.Location = new System.Drawing.Point(16, 111);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.Size = new System.Drawing.Size(73, 17);
			this.lblChan0.TabIndex = 1;
			this.lblChan0.Text = "Channel 0:";
			this.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblWarn
			//
			this.lblWarn.BackColor = System.Drawing.SystemColors.Window;
			this.lblWarn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.lblWarn.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblWarn.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblWarn.ForeColor = System.Drawing.Color.Red;
			this.lblWarn.Location = new System.Drawing.Point(13, 48);
			this.lblWarn.Name = "lblWarn";
			this.lblWarn.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblWarn.Size = new System.Drawing.Size(322, 33);
			this.lblWarn.TabIndex = 18;
			this.lblWarn.Text = "There must be a clock signal present at trigger input.  Otherwise, program will hang.";
			this.lblWarn.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(13, 6);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(311, 41);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AInScan() with External Clock";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDataDisplay
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(349, 243);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.txtHighChan, this.cmdStart, this.cmdStopConvert, this.Label1, this._lblADData_7, this.lblChan7, this._lblADData_3, this.lblChan3, this._lblADData_6, this.lblChan6, this._lblADData_2, this.lblChan2, this._lblADData_5, this.lblChan5, this._lblADData_1, this.lblChan1, this._lblADData_4, this.lblChan4, this._lblADData_0, this.lblChan0, this.lblWarn, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(205, 135);
			this.Name = "frmDataDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Analog Input Scan";
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
	    

		private void cmdStart_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStart.Click */
		{
			tmrConvert.Enabled = true;
			cmdStopConvert.Visible = true;
			cmdStart.Visible = false;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			//  Free up memory for use by other programs
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			
			MemHandle = 0;

			tmrConvert.Enabled = false;
			Application.Exit();
		}


		private void tmrConvert_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrConvert.Tick */
		{
			
			tmrConvert.Stop();

			//  Collect the values by calling MccDaq.MccBoard.AInScan function
			//  Parameters:
			//    LowChan    :the first channel of the scan
			//    HighChan   :the last channel of the scan
			//    Count      :the total number of A/D samples to collect
			//    Rate       :sample rate
			//    Range      :the range for the board
			//    MemHandle  :Handle for Windows buffer to store data in
			//    Options    :data collection options
			int LowChan = 0;     //  first channel to acquire
			HighChan = int.Parse(txtHighChan.Text); //  last channel to acquire
			if (HighChan > 7) HighChan = 7;
			txtHighChan.Text = HighChan.ToString();

			int Count = NumPoints; //  total number of data points to collect
			int Rate = 100; //  sampling rate is ignored
			MccDaq.Range Range = MccDaq.Range.Bip5Volts; // set the range
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.ConvertData  
										| MccDaq.ScanOptions.ExtClock;
			MccDaq.ErrorInfo ULStat = DaqBoard.AInScan( LowChan, HighChan, Count, ref Rate, Range, MemHandle, Options);
			

			//  Transfer the data from the memory buffer set up by Windows to an array 
			ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out ADData[0], FirstPoint, Count);


			for (int i=0; i<=HighChan; ++i)
				lblADData[i].Text = ADData[i].ToString("0");

			for (int j=HighChan + 1; j<=7; ++j)
				lblADData[j].Text = ("");
	  
			tmrConvert.Start();
		}

	}
}