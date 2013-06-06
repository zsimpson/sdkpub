// ==============================================================================
//
//  File:                         ULAI06.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.AInScan(), continuous background mode
//
//  Purpose:                      Scans a range of A/D Input Channels continuously
//                                in the background and stores the data in an array.
//
//  Demonstration:                Continuously collects data on up to eight channels.
//
//  Other Library Calls:          Mccdaq.MccBoard.GetStatus()
//                                Mccdaq.MccBoard.StopBackground()
//                                Mccdaq.MccBoard.ErrHandling()
//
//  Special Requirements:         Board 0 must have an A/D converter.
//                                Analog signals on up to eight input channels.
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

namespace ULAI06
{
	public class frmStatusDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public TextBox txtHighChan;
		public Button cmdQuit;
		public Timer tmrCheckStatus;
		public Button cmdStartBgnd;
		public Button cmdStopConvert;
		public Label Label1;
		public Label lblShowCount;
		public Label lblCount;
		public Label lblShowIndex;
		public Label lblIndex;
		public Label lblShowStat;
		public Label lblStatus;
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
		public Label lblDemoFunction;

		public Label[] lblADData;

		const int NumPoints = 10000;  //  Number of data points to collect
		private MccDaq.MccBoard DaqBoard;
		private int HighChan;
		private ushort[] ADData = new ushort[NumPoints];  
		private ushort[] ChanTags = new ushort[NumPoints];
		private int MemHandle;
		
	 
		public frmStatusDisplay()
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

			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); //  set aside memory to hold data
			

			//  Note: Any change to label names requires a change to the corresponding array element below
			lblADData = (new Label[] {_lblADData_0, _lblADData_1, _lblADData_2, _lblADData_3, 
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

				DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
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
			this.cmdQuit = new System.Windows.Forms.Button();
			this.tmrCheckStatus = new System.Windows.Forms.Timer(this.components);
			this.cmdStartBgnd = new System.Windows.Forms.Button();
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this.Label1 = new System.Windows.Forms.Label();
			this.lblShowCount = new System.Windows.Forms.Label();
			this.lblCount = new System.Windows.Forms.Label();
			this.lblShowIndex = new System.Windows.Forms.Label();
			this.lblIndex = new System.Windows.Forms.Label();
			this.lblShowStat = new System.Windows.Forms.Label();
			this.lblStatus = new System.Windows.Forms.Label();
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
			this.txtHighChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.txtHighChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtHighChan.Location = new System.Drawing.Point(192, 80);
			this.txtHighChan.MaxLength = 0;
			this.txtHighChan.Name = "txtHighChan";
			this.txtHighChan.Size = new System.Drawing.Size(25, 19);
			this.txtHighChan.TabIndex = 27;
			this.txtHighChan.Text = "3";
			this.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// cmdQuit
			// 
			this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
			this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdQuit.Location = new System.Drawing.Point(272, 224);
			this.cmdQuit.Name = "cmdQuit";
			this.cmdQuit.Size = new System.Drawing.Size(65, 26);
			this.cmdQuit.TabIndex = 19;
			this.cmdQuit.Text = "Quit";
			this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
			// 
			// tmrCheckStatus
			// 
			this.tmrCheckStatus.Interval = 200;
			this.tmrCheckStatus.Tick += new System.EventHandler(this.tmrCheckStatus_Tick);
			// 
			// cmdStartBgnd
			// 
			this.cmdStartBgnd.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartBgnd.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartBgnd.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStartBgnd.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartBgnd.Location = new System.Drawing.Point(83, 48);
			this.cmdStartBgnd.Name = "cmdStartBgnd";
			this.cmdStartBgnd.Size = new System.Drawing.Size(180, 27);
			this.cmdStartBgnd.TabIndex = 18;
			this.cmdStartBgnd.Text = "Start Background Operation";
			this.cmdStartBgnd.Click += new System.EventHandler(this.cmdStartBgnd_Click);
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
			this.cmdStopConvert.Size = new System.Drawing.Size(180, 27);
			this.cmdStopConvert.TabIndex = 17;
			this.cmdStopConvert.Text = "Stop Background Operation";
			this.cmdStopConvert.Visible = false;
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			// 
			// Label1
			// 
			this.Label1.BackColor = System.Drawing.SystemColors.Window;
			this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label1.Location = new System.Drawing.Point(48, 80);
			this.Label1.Name = "Label1";
			this.Label1.Size = new System.Drawing.Size(137, 17);
			this.Label1.TabIndex = 26;
			this.Label1.Text = "Measure Channels 0 to";
			// 
			// lblShowCount
			// 
			this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCount.Location = new System.Drawing.Point(198, 238);
			this.lblShowCount.Name = "lblShowCount";
			this.lblShowCount.Size = new System.Drawing.Size(58, 14);
			this.lblShowCount.TabIndex = 25;
			// 
			// lblCount
			// 
			this.lblCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCount.Location = new System.Drawing.Point(83, 238);
			this.lblCount.Name = "lblCount";
			this.lblCount.Size = new System.Drawing.Size(103, 14);
			this.lblCount.TabIndex = 23;
			this.lblCount.Text = "Current Count:";
			this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblShowIndex
			// 
			this.lblShowIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowIndex.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowIndex.ForeColor = System.Drawing.Color.Blue;
			this.lblShowIndex.Location = new System.Drawing.Point(198, 219);
			this.lblShowIndex.Name = "lblShowIndex";
			this.lblShowIndex.Size = new System.Drawing.Size(52, 14);
			this.lblShowIndex.TabIndex = 24;
			// 
			// lblIndex
			// 
			this.lblIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblIndex.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblIndex.Location = new System.Drawing.Point(83, 219);
			this.lblIndex.Name = "lblIndex";
			this.lblIndex.Size = new System.Drawing.Size(103, 14);
			this.lblIndex.TabIndex = 22;
			this.lblIndex.Text = "Current Index:";
			this.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblShowStat
			// 
			this.lblShowStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowStat.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowStat.ForeColor = System.Drawing.Color.Blue;
			this.lblShowStat.Location = new System.Drawing.Point(240, 192);
			this.lblShowStat.Name = "lblShowStat";
			this.lblShowStat.Size = new System.Drawing.Size(65, 17);
			this.lblShowStat.TabIndex = 21;
			// 
			// lblStatus
			// 
			this.lblStatus.BackColor = System.Drawing.SystemColors.Window;
			this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblStatus.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblStatus.Location = new System.Drawing.Point(8, 192);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.Size = new System.Drawing.Size(217, 17);
			this.lblStatus.TabIndex = 20;
			this.lblStatus.Text = "Status of Background Operation:";
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// _lblADData_7
			// 
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Location = new System.Drawing.Point(264, 166);
			this._lblADData_7.Name = "_lblADData_7";
			this._lblADData_7.Size = new System.Drawing.Size(65, 17);
			this._lblADData_7.TabIndex = 16;
			// 
			// lblChan7
			// 
			this.lblChan7.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan7.Location = new System.Drawing.Point(192, 166);
			this.lblChan7.Name = "lblChan7";
			this.lblChan7.Size = new System.Drawing.Size(65, 17);
			this.lblChan7.TabIndex = 8;
			this.lblChan7.Text = "Channel 7:";
			// 
			// _lblADData_3
			// 
			this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_3.Location = new System.Drawing.Point(96, 166);
			this._lblADData_3.Name = "_lblADData_3";
			this._lblADData_3.Size = new System.Drawing.Size(65, 17);
			this._lblADData_3.TabIndex = 12;
			// 
			// lblChan3
			// 
			this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan3.Location = new System.Drawing.Point(24, 166);
			this.lblChan3.Name = "lblChan3";
			this.lblChan3.Size = new System.Drawing.Size(65, 17);
			this.lblChan3.TabIndex = 4;
			this.lblChan3.Text = "Channel 3:";
			// 
			// _lblADData_6
			// 
			this._lblADData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_6.Location = new System.Drawing.Point(264, 147);
			this._lblADData_6.Name = "_lblADData_6";
			this._lblADData_6.Size = new System.Drawing.Size(65, 17);
			this._lblADData_6.TabIndex = 15;
			// 
			// lblChan6
			// 
			this.lblChan6.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan6.Location = new System.Drawing.Point(192, 147);
			this.lblChan6.Name = "lblChan6";
			this.lblChan6.Size = new System.Drawing.Size(65, 17);
			this.lblChan6.TabIndex = 7;
			this.lblChan6.Text = "Channel 6:";
			// 
			// _lblADData_2
			// 
			this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_2.Location = new System.Drawing.Point(96, 147);
			this._lblADData_2.Name = "_lblADData_2";
			this._lblADData_2.Size = new System.Drawing.Size(65, 17);
			this._lblADData_2.TabIndex = 11;
			// 
			// lblChan2
			// 
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan2.Location = new System.Drawing.Point(24, 147);
			this.lblChan2.Name = "lblChan2";
			this.lblChan2.Size = new System.Drawing.Size(65, 17);
			this.lblChan2.TabIndex = 3;
			this.lblChan2.Text = "Channel 2:";
			// 
			// _lblADData_5
			// 
			this._lblADData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_5.Location = new System.Drawing.Point(264, 128);
			this._lblADData_5.Name = "_lblADData_5";
			this._lblADData_5.Size = new System.Drawing.Size(65, 17);
			this._lblADData_5.TabIndex = 14;
			// 
			// lblChan5
			// 
			this.lblChan5.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan5.Location = new System.Drawing.Point(192, 128);
			this.lblChan5.Name = "lblChan5";
			this.lblChan5.Size = new System.Drawing.Size(65, 17);
			this.lblChan5.TabIndex = 6;
			this.lblChan5.Text = "Channel 5:";
			// 
			// _lblADData_1
			// 
			this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_1.Location = new System.Drawing.Point(96, 128);
			this._lblADData_1.Name = "_lblADData_1";
			this._lblADData_1.Size = new System.Drawing.Size(65, 17);
			this._lblADData_1.TabIndex = 10;
			// 
			// lblChan1
			// 
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan1.Location = new System.Drawing.Point(24, 128);
			this.lblChan1.Name = "lblChan1";
			this.lblChan1.Size = new System.Drawing.Size(65, 17);
			this.lblChan1.TabIndex = 2;
			this.lblChan1.Text = "Channel 1:";
			// 
			// _lblADData_4
			// 
			this._lblADData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_4.Location = new System.Drawing.Point(264, 109);
			this._lblADData_4.Name = "_lblADData_4";
			this._lblADData_4.Size = new System.Drawing.Size(65, 17);
			this._lblADData_4.TabIndex = 13;
			// 
			// lblChan4
			// 
			this.lblChan4.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan4.Location = new System.Drawing.Point(192, 109);
			this.lblChan4.Name = "lblChan4";
			this.lblChan4.Size = new System.Drawing.Size(65, 17);
			this.lblChan4.TabIndex = 5;
			this.lblChan4.Text = "Channel 4:";
			// 
			// _lblADData_0
			// 
			this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_0.Location = new System.Drawing.Point(96, 109);
			this._lblADData_0.Name = "_lblADData_0";
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.Size = new System.Drawing.Size(65, 17);
			this._lblADData_0.TabIndex = 9;
			// 
			// lblChan0
			// 
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan0.Location = new System.Drawing.Point(24, 109);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.Size = new System.Drawing.Size(65, 17);
			this.lblChan0.TabIndex = 1;
			this.lblChan0.Text = "Channel 0:";
			// 
			// lblDemoFunction
			// 
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(8, 8);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.Size = new System.Drawing.Size(337, 33);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.AInScan() in Continuous Background mode";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// frmStatusDisplay
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(350, 254);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																							 this.txtHighChan,
																							 this.cmdQuit,
																							 this.cmdStartBgnd,
																							 this.cmdStopConvert,
																							 this.Label1,
																							 this.lblShowCount,
																							 this.lblCount,
																							 this.lblShowIndex,
																							 this.lblIndex,
																							 this.lblShowStat,
																							 this.lblStatus,
																							 this._lblADData_7,
																							 this.lblChan7,
																							 this._lblADData_3,
																							 this.lblChan3,
																							 this._lblADData_6,
																							 this.lblChan6,
																							 this._lblADData_2,
																							 this.lblChan2,
																							 this._lblADData_5,
																							 this.lblChan5,
																							 this._lblADData_1,
																							 this.lblChan1,
																							 this._lblADData_4,
																							 this.lblChan4,
																							 this._lblADData_0,
																							 this.lblChan0,
																							 this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(168, 104);
			this.Name = "frmStatusDisplay";
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
			Application.Run(new frmStatusDisplay());
		}
	    

		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) 
		{
			//  Free up memory for use by other programs
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			
			MemHandle = 0;

			Application.Exit();

		}


		private void cmdStartBgnd_Click(object eventSender, System.EventArgs eventArgs) 
		{
			int CurIndex;
			int CurCount;
			short Status;
			MccDaq.ErrorInfo ULStat;
			MccDaq.Range Range;
			MccDaq.ScanOptions Options;
			int Rate;
			int Count;
			short LowChan;
			double Test;

			cmdStartBgnd.Enabled = false;
			cmdStartBgnd.Visible = false;
			cmdStopConvert.Enabled = true;
			cmdStopConvert.Visible = true;
			cmdQuit.Enabled = false;

			//  Collect the values by calling MccDaq.MccBoard.AInScan
			//   Parameters:
			//     LowChan    :the first channel of the scan
			//     HighChan   :the last channel of the scan
			//     Count      :the total number of A/D samples to collect
			//     Rate       :sample rate
			//     Range      :the range for the board
			//     MemHandle  :Handle for Windows buffer to store data in
			//     Options    :data collection options

			LowChan = 0; //  first channel to acquire
			HighChan = int.Parse(txtHighChan.Text); //  last channel to acquire
			if (HighChan > 7) HighChan = 7;
			txtHighChan.Text = HighChan.ToString();

			Count = NumPoints;     //  total number of data points to collect
			Rate = 390;            //  per channel sampling rate ((samples per second) per channel)
			Options = MccDaq.ScanOptions.Background 
					| MccDaq.ScanOptions.SingleIo	
					| MccDaq.ScanOptions.Continuous;

			//  collect data in background continuously
			Range = MccDaq.Range.Bip5Volts; //  set the range
			ULStat = DaqBoard.AInScan( LowChan, HighChan, Count, ref Rate, Range, MemHandle, Options);
			

			ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AiFunction);
			

			if (Status == MccDaq.MccBoard.Running)
			{
				lblShowStat.Text = "Running";
				lblShowCount.Text = CurCount.ToString("D");
				lblShowIndex.Text = CurIndex.ToString("D");
			}

			tmrCheckStatus.Enabled = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) 
		{
			int CurIndex;
			int CurCount;
			short Status;
			MccDaq.ErrorInfo ULStat;

			ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
			

			cmdStartBgnd.Enabled = true; 
			cmdStartBgnd.Visible = true;
			cmdStopConvert.Enabled = false;
			cmdStopConvert.Visible = false;
			cmdQuit.Enabled = true;
			tmrCheckStatus.Enabled = false;

			ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AiFunction);
			

			if (Status == MccDaq.MccBoard.Idle) lblShowStat.Text = "Idle";
			lblShowCount.Text = CurCount.ToString("D");
			lblShowIndex.Text = CurIndex.ToString("D");

		}


		private void tmrCheckStatus_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrCheckStatus.Tick */
		{
			int j;
			int i;
			int FirstPoint;
			MccDaq.ErrorInfo ULStat;
			int CurIndex;
			int CurCount;
			short Status;

			tmrCheckStatus.Stop();
			
			//  Check the status of the background data collection

			//  Parameters:
			//    Status      :current status of the background data collection
			//    CurCount    :current number of samples collected
			//    CurIndex    :index to the data buffer pointing to the start of the
			//                 most recently collected scan
			//    FunctionType: A/D operation (MccDaq.FunctionType.AiFunction)
			ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AiFunction);
			

			if (Status == MccDaq.MccBoard.Running) lblShowStat.Text = "Running";
			lblShowCount.Text = CurCount.ToString("D");
			lblShowIndex.Text = CurIndex.ToString("D");
			if (CurCount > HighChan)
			{
				FirstPoint = CurIndex; // start of latest channel scan in MemHandle buffer
				ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out ADData[0], FirstPoint, 8);
				


				//  Use MccDaq.MccBoard.AConvertData() to convert the 16-bit values
				//  in ADData() to 12-bit values
				//  Parameters:
				//    NumPoints   :the number of data values to convert
				//    ADData     :the array holding the 16-bit data values to be converted
				//    ChanTags   :the array in which the channel information will be stored
				//ULStat = DaqBoard.AConvertData( NumPoints, ref ADData[0], out ChanTags[0]);
				

				for (i=0; i<=HighChan; ++i)
					lblADData[i].Text = ADData[i].ToString("D");
				
				for (j=HighChan + 1; j<=7; ++j)
					lblADData[j].Text = "";
			}
			
			tmrCheckStatus.Start();

		}

	}
}