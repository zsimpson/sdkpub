// ==============================================================================
//
//  File:                         ULTI02.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.TInScan()
//
//  Purpose:                      Scans multiplexor input channels.
//
//  Demonstration:                Displays the temperature inputs on a
//                                range of channels.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Unless the board at BoardNum(=0) does not use
//                                EXP boards for temperature measurements(the
//                                CIO-DAS-TC,for example), it must
//                                have an A/D converter with an attached EXP
//                                board.  Thermocouples must be wired to EXP
//                                channels selected.
// ==============================================================================
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Diagnostics;

using MccDaq;

namespace ULTI02
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStartConvert;
		public Button cmdStopConvert;
		public HScrollBar hsbHiChan;
		public Timer tmrConvert;
		public HScrollBar hsbLoChan;
		public Label _lblShowData_15;
		public Label _lblChanNum_15;
		public Label _lblShowData_7;
		public Label _lblChanNum_7;
		public Label _lblShowData_14;
		public Label _lblChanNum_14;
		public Label _lblShowData_6;
		public Label _lblChanNum_6;
		public Label _lblShowData_13;
		public Label _lblChanNum_13;
		public Label _lblShowData_5;
		public Label _lblChanNum_5;
		public Label _lblShowData_12;
		public Label _lblChanNum_12;
		public Label _lblShowData_4;
		public Label _lblChanNum_4;
		public Label _lblShowData_11;
		public Label _lblChanNum_11;
		public Label _lblShowData_3;
		public Label _lblChanNum_3;
		public Label _lblShowData_10;
		public Label _lblChanNum_10;
		public Label _lblShowData_2;
		public Label _lblChanNum_2;
		public Label _lblShowData_9;
		public Label _lblChanNum_9;
		public Label _lblShowData_1;
		public Label _lblChanNum_1;
		public Label _lblShowData_8;
		public Label _lblChanNum_8;
		public Label _lblShowData_0;
		public Label _lblChanNum_0;
		public Label lblTemp2;
		public Label lblChan2;
		public Label lblTemp1;
		public Label lblChan1;
		public Label lblLastChan;
		public Label lblHiChan;
		public Label lblFirstChan;
		public Label lblLoChan;
		public Label lblChanPrompt;
		public Label lblDemoFunction;

		public Label[] lblShowData;

		private MccDaq.MccBoard DaqBoard;
		private int UsesEXPs=0;
		private float[] DataBuffer = new float[16]; // array to hold  the temperatures


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
			
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.DontPrint, MccDaq.ErrorHandling.StopAll);
			

			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);

			// Determine if the board uses EXP boards for temperature measurements
			UsesEXPs = 0;
			ULStat = DaqBoard.BoardConfig.GetUsesExps(out UsesEXPs);

			lblShowData = (new Label[]{_lblShowData_0, _lblShowData_1, _lblShowData_2, _lblShowData_3,
									   _lblShowData_4, _lblShowData_5, _lblShowData_6, _lblShowData_7,
									   _lblShowData_8, _lblShowData_9, _lblShowData_10, _lblShowData_11,
									   _lblShowData_12, _lblShowData_13, _lblShowData_14, _lblShowData_15});
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
		this.cmdStartConvert = new System.Windows.Forms.Button();
		this.cmdStopConvert = new System.Windows.Forms.Button();
		this.hsbHiChan = new System.Windows.Forms.HScrollBar();
		this.tmrConvert = new System.Windows.Forms.Timer(this.components);
		this.hsbLoChan = new System.Windows.Forms.HScrollBar();
		this._lblShowData_15 = new System.Windows.Forms.Label();
		this._lblChanNum_15 = new System.Windows.Forms.Label();
		this._lblShowData_7 = new System.Windows.Forms.Label();
		this._lblChanNum_7 = new System.Windows.Forms.Label();
		this._lblShowData_14 = new System.Windows.Forms.Label();
		this._lblChanNum_14 = new System.Windows.Forms.Label();
		this._lblShowData_6 = new System.Windows.Forms.Label();
		this._lblChanNum_6 = new System.Windows.Forms.Label();
		this._lblShowData_13 = new System.Windows.Forms.Label();
		this._lblChanNum_13 = new System.Windows.Forms.Label();
		this._lblShowData_5 = new System.Windows.Forms.Label();
		this._lblChanNum_5 = new System.Windows.Forms.Label();
		this._lblShowData_12 = new System.Windows.Forms.Label();
		this._lblChanNum_12 = new System.Windows.Forms.Label();
		this._lblShowData_4 = new System.Windows.Forms.Label();
		this._lblChanNum_4 = new System.Windows.Forms.Label();
		this._lblShowData_11 = new System.Windows.Forms.Label();
		this._lblChanNum_11 = new System.Windows.Forms.Label();
		this._lblShowData_3 = new System.Windows.Forms.Label();
		this._lblChanNum_3 = new System.Windows.Forms.Label();
		this._lblShowData_10 = new System.Windows.Forms.Label();
		this._lblChanNum_10 = new System.Windows.Forms.Label();
		this._lblShowData_2 = new System.Windows.Forms.Label();
		this._lblChanNum_2 = new System.Windows.Forms.Label();
		this._lblShowData_9 = new System.Windows.Forms.Label();
		this._lblChanNum_9 = new System.Windows.Forms.Label();
		this._lblShowData_1 = new System.Windows.Forms.Label();
		this._lblChanNum_1 = new System.Windows.Forms.Label();
		this._lblShowData_8 = new System.Windows.Forms.Label();
		this._lblChanNum_8 = new System.Windows.Forms.Label();
		this._lblShowData_0 = new System.Windows.Forms.Label();
		this._lblChanNum_0 = new System.Windows.Forms.Label();
		this.lblTemp2 = new System.Windows.Forms.Label();
		this.lblChan2 = new System.Windows.Forms.Label();
		this.lblTemp1 = new System.Windows.Forms.Label();
		this.lblChan1 = new System.Windows.Forms.Label();
		this.lblLastChan = new System.Windows.Forms.Label();
		this.lblHiChan = new System.Windows.Forms.Label();
		this.lblFirstChan = new System.Windows.Forms.Label();
		this.lblLoChan = new System.Windows.Forms.Label();
		this.lblChanPrompt = new System.Windows.Forms.Label();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.SuspendLayout();
		// 
		// cmdStartConvert
		// 
		this.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStartConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStartConvert.Location = new System.Drawing.Point(304, 312);
		this.cmdStartConvert.Name = "cmdStartConvert";
		this.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStartConvert.Size = new System.Drawing.Size(57, 25);
		this.cmdStartConvert.TabIndex = 3;
		this.cmdStartConvert.Text = "Start";
		this.cmdStartConvert.Click += new System.EventHandler(this.cmdStartConvert_Click);
		// 
		// cmdStopConvert
		// 
		this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStopConvert.Location = new System.Drawing.Point(304, 312);
		this.cmdStopConvert.Name = "cmdStopConvert";
		this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStopConvert.Size = new System.Drawing.Size(57, 25);
		this.cmdStopConvert.TabIndex = 4;
		this.cmdStopConvert.Text = "Quit";
		this.cmdStopConvert.Visible = false;
		this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
		// 
		// hsbHiChan
		// 
		this.hsbHiChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.hsbHiChan.LargeChange = 1;
		this.hsbHiChan.Location = new System.Drawing.Point(32, 88);
		this.hsbHiChan.Maximum = 15;
		this.hsbHiChan.Name = "hsbHiChan";
		this.hsbHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.hsbHiChan.Size = new System.Drawing.Size(169, 17);
		this.hsbHiChan.TabIndex = 6;
		this.hsbHiChan.TabStop = true;
		this.hsbHiChan.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hsbHiChan_Scroll);
		// 
		// tmrConvert
		// 
		this.tmrConvert.Interval = 250;
		this.tmrConvert.Tick += new System.EventHandler(this.tmrConvert_Tick);
		// 
		// hsbLoChan
		// 
		this.hsbLoChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.hsbLoChan.LargeChange = 1;
		this.hsbLoChan.Location = new System.Drawing.Point(32, 64);
		this.hsbLoChan.Maximum = 15;
		this.hsbLoChan.Name = "hsbLoChan";
		this.hsbLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.hsbLoChan.Size = new System.Drawing.Size(169, 17);
		this.hsbLoChan.TabIndex = 5;
		this.hsbLoChan.TabStop = true;
		this.hsbLoChan.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hsbLoChan_Scroll);
		// 
		// _lblShowData_15
		// 
		this._lblShowData_15.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_15.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_15.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_15.Location = new System.Drawing.Point(280, 280);
		this._lblShowData_15.Name = "_lblShowData_15";
		this._lblShowData_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_15.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_15.TabIndex = 23;
		this._lblShowData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_15
		// 
		this._lblChanNum_15.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_15.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_15.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_15.Location = new System.Drawing.Point(224, 280);
		this._lblChanNum_15.Name = "_lblChanNum_15";
		this._lblChanNum_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_15.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_15.TabIndex = 43;
		this._lblChanNum_15.Text = "15";
		this._lblChanNum_15.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_7
		// 
		this._lblShowData_7.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_7.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_7.Location = new System.Drawing.Point(112, 280);
		this._lblShowData_7.Name = "_lblShowData_7";
		this._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_7.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_7.TabIndex = 15;
		this._lblShowData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_7
		// 
		this._lblChanNum_7.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_7.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_7.Location = new System.Drawing.Point(56, 280);
		this._lblChanNum_7.Name = "_lblChanNum_7";
		this._lblChanNum_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_7.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_7.TabIndex = 35;
		this._lblChanNum_7.Text = "7";
		this._lblChanNum_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_14
		// 
		this._lblShowData_14.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_14.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_14.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_14.Location = new System.Drawing.Point(280, 264);
		this._lblShowData_14.Name = "_lblShowData_14";
		this._lblShowData_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_14.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_14.TabIndex = 22;
		this._lblShowData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_14
		// 
		this._lblChanNum_14.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_14.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_14.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_14.Location = new System.Drawing.Point(224, 264);
		this._lblChanNum_14.Name = "_lblChanNum_14";
		this._lblChanNum_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_14.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_14.TabIndex = 42;
		this._lblChanNum_14.Text = "14";
		this._lblChanNum_14.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_6
		// 
		this._lblShowData_6.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_6.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_6.Location = new System.Drawing.Point(112, 264);
		this._lblShowData_6.Name = "_lblShowData_6";
		this._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_6.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_6.TabIndex = 14;
		this._lblShowData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_6
		// 
		this._lblChanNum_6.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_6.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_6.Location = new System.Drawing.Point(56, 264);
		this._lblChanNum_6.Name = "_lblChanNum_6";
		this._lblChanNum_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_6.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_6.TabIndex = 34;
		this._lblChanNum_6.Text = "6";
		this._lblChanNum_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_13
		// 
		this._lblShowData_13.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_13.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_13.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_13.Location = new System.Drawing.Point(280, 248);
		this._lblShowData_13.Name = "_lblShowData_13";
		this._lblShowData_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_13.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_13.TabIndex = 21;
		this._lblShowData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_13
		// 
		this._lblChanNum_13.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_13.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_13.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_13.Location = new System.Drawing.Point(224, 248);
		this._lblChanNum_13.Name = "_lblChanNum_13";
		this._lblChanNum_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_13.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_13.TabIndex = 41;
		this._lblChanNum_13.Text = "13";
		this._lblChanNum_13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_5
		// 
		this._lblShowData_5.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_5.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_5.Location = new System.Drawing.Point(112, 248);
		this._lblShowData_5.Name = "_lblShowData_5";
		this._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_5.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_5.TabIndex = 13;
		this._lblShowData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_5
		// 
		this._lblChanNum_5.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_5.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_5.Location = new System.Drawing.Point(56, 248);
		this._lblChanNum_5.Name = "_lblChanNum_5";
		this._lblChanNum_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_5.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_5.TabIndex = 33;
		this._lblChanNum_5.Text = "5";
		this._lblChanNum_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_12
		// 
		this._lblShowData_12.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_12.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_12.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_12.Location = new System.Drawing.Point(280, 232);
		this._lblShowData_12.Name = "_lblShowData_12";
		this._lblShowData_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_12.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_12.TabIndex = 20;
		this._lblShowData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_12
		// 
		this._lblChanNum_12.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_12.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_12.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_12.Location = new System.Drawing.Point(224, 232);
		this._lblChanNum_12.Name = "_lblChanNum_12";
		this._lblChanNum_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_12.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_12.TabIndex = 40;
		this._lblChanNum_12.Text = "12";
		this._lblChanNum_12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_4
		// 
		this._lblShowData_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_4.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_4.Location = new System.Drawing.Point(112, 232);
		this._lblShowData_4.Name = "_lblShowData_4";
		this._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_4.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_4.TabIndex = 12;
		this._lblShowData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_4
		// 
		this._lblChanNum_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_4.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_4.Location = new System.Drawing.Point(56, 232);
		this._lblChanNum_4.Name = "_lblChanNum_4";
		this._lblChanNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_4.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_4.TabIndex = 32;
		this._lblChanNum_4.Text = "4";
		this._lblChanNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_11
		// 
		this._lblShowData_11.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_11.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_11.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_11.Location = new System.Drawing.Point(280, 216);
		this._lblShowData_11.Name = "_lblShowData_11";
		this._lblShowData_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_11.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_11.TabIndex = 19;
		this._lblShowData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_11
		// 
		this._lblChanNum_11.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_11.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_11.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_11.Location = new System.Drawing.Point(224, 216);
		this._lblChanNum_11.Name = "_lblChanNum_11";
		this._lblChanNum_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_11.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_11.TabIndex = 39;
		this._lblChanNum_11.Text = "11";
		this._lblChanNum_11.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_3
		// 
		this._lblShowData_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_3.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_3.Location = new System.Drawing.Point(112, 216);
		this._lblShowData_3.Name = "_lblShowData_3";
		this._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_3.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_3.TabIndex = 11;
		this._lblShowData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_3
		// 
		this._lblChanNum_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_3.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_3.Location = new System.Drawing.Point(56, 216);
		this._lblChanNum_3.Name = "_lblChanNum_3";
		this._lblChanNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_3.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_3.TabIndex = 31;
		this._lblChanNum_3.Text = "3";
		this._lblChanNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_10
		// 
		this._lblShowData_10.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_10.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_10.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_10.Location = new System.Drawing.Point(280, 200);
		this._lblShowData_10.Name = "_lblShowData_10";
		this._lblShowData_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_10.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_10.TabIndex = 18;
		this._lblShowData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_10
		// 
		this._lblChanNum_10.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_10.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_10.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_10.Location = new System.Drawing.Point(224, 200);
		this._lblChanNum_10.Name = "_lblChanNum_10";
		this._lblChanNum_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_10.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_10.TabIndex = 38;
		this._lblChanNum_10.Text = "10";
		this._lblChanNum_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_2
		// 
		this._lblShowData_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_2.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_2.Location = new System.Drawing.Point(112, 200);
		this._lblShowData_2.Name = "_lblShowData_2";
		this._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_2.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_2.TabIndex = 10;
		this._lblShowData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_2
		// 
		this._lblChanNum_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_2.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_2.Location = new System.Drawing.Point(56, 200);
		this._lblChanNum_2.Name = "_lblChanNum_2";
		this._lblChanNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_2.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_2.TabIndex = 30;
		this._lblChanNum_2.Text = "2";
		this._lblChanNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_9
		// 
		this._lblShowData_9.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_9.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_9.Location = new System.Drawing.Point(280, 184);
		this._lblShowData_9.Name = "_lblShowData_9";
		this._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_9.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_9.TabIndex = 17;
		this._lblShowData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_9
		// 
		this._lblChanNum_9.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_9.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_9.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_9.Location = new System.Drawing.Point(224, 184);
		this._lblChanNum_9.Name = "_lblChanNum_9";
		this._lblChanNum_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_9.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_9.TabIndex = 37;
		this._lblChanNum_9.Text = "9";
		this._lblChanNum_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_1
		// 
		this._lblShowData_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_1.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_1.Location = new System.Drawing.Point(112, 184);
		this._lblShowData_1.Name = "_lblShowData_1";
		this._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_1.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_1.TabIndex = 9;
		this._lblShowData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_1
		// 
		this._lblChanNum_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_1.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_1.Location = new System.Drawing.Point(56, 184);
		this._lblChanNum_1.Name = "_lblChanNum_1";
		this._lblChanNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_1.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_1.TabIndex = 29;
		this._lblChanNum_1.Text = "1";
		this._lblChanNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_8
		// 
		this._lblShowData_8.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_8.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_8.Location = new System.Drawing.Point(280, 168);
		this._lblShowData_8.Name = "_lblShowData_8";
		this._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_8.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_8.TabIndex = 16;
		this._lblShowData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_8
		// 
		this._lblChanNum_8.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_8.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_8.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_8.Location = new System.Drawing.Point(224, 168);
		this._lblChanNum_8.Name = "_lblChanNum_8";
		this._lblChanNum_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_8.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_8.TabIndex = 36;
		this._lblChanNum_8.Text = "8";
		this._lblChanNum_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_0
		// 
		this._lblShowData_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_0.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_0.Location = new System.Drawing.Point(112, 168);
		this._lblShowData_0.Name = "_lblShowData_0";
		this._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_0.Size = new System.Drawing.Size(65, 17);
		this._lblShowData_0.TabIndex = 2;
		this._lblShowData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblChanNum_0
		// 
		this._lblChanNum_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblChanNum_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblChanNum_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblChanNum_0.ForeColor = System.Drawing.SystemColors.WindowText;
		this._lblChanNum_0.Location = new System.Drawing.Point(56, 168);
		this._lblChanNum_0.Name = "_lblChanNum_0";
		this._lblChanNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblChanNum_0.Size = new System.Drawing.Size(41, 17);
		this._lblChanNum_0.TabIndex = 28;
		this._lblChanNum_0.Text = "0";
		this._lblChanNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblTemp2
		// 
		this.lblTemp2.BackColor = System.Drawing.SystemColors.Window;
		this.lblTemp2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblTemp2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblTemp2.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblTemp2.Location = new System.Drawing.Point(272, 136);
		this.lblTemp2.Name = "lblTemp2";
		this.lblTemp2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblTemp2.Size = new System.Drawing.Size(81, 17);
		this.lblTemp2.TabIndex = 25;
		this.lblTemp2.Text = "Temperature";
		this.lblTemp2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblChan2
		// 
		this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
		this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblChan2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblChan2.Location = new System.Drawing.Point(216, 136);
		this.lblChan2.Name = "lblChan2";
		this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblChan2.Size = new System.Drawing.Size(49, 17);
		this.lblChan2.TabIndex = 27;
		this.lblChan2.Text = "Channel";
		this.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblTemp1
		// 
		this.lblTemp1.BackColor = System.Drawing.SystemColors.Window;
		this.lblTemp1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblTemp1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblTemp1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblTemp1.Location = new System.Drawing.Point(104, 136);
		this.lblTemp1.Name = "lblTemp1";
		this.lblTemp1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblTemp1.Size = new System.Drawing.Size(81, 17);
		this.lblTemp1.TabIndex = 24;
		this.lblTemp1.Text = "Temperature";
		this.lblTemp1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblChan1
		// 
		this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
		this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblChan1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblChan1.Location = new System.Drawing.Point(48, 136);
		this.lblChan1.Name = "lblChan1";
		this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblChan1.Size = new System.Drawing.Size(57, 17);
		this.lblChan1.TabIndex = 26;
		this.lblChan1.Text = "Channel";
		this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblLastChan
		// 
		this.lblLastChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblLastChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblLastChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblLastChan.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblLastChan.Location = new System.Drawing.Point(272, 88);
		this.lblLastChan.Name = "lblLastChan";
		this.lblLastChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblLastChan.Size = new System.Drawing.Size(89, 17);
		this.lblLastChan.TabIndex = 45;
		this.lblLastChan.Text = "Last Channel";
		// 
		// lblHiChan
		// 
		this.lblHiChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblHiChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.lblHiChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblHiChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblHiChan.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblHiChan.Location = new System.Drawing.Point(200, 88);
		this.lblHiChan.Name = "lblHiChan";
		this.lblHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblHiChan.Size = new System.Drawing.Size(32, 17);
		this.lblHiChan.TabIndex = 8;
		this.lblHiChan.Text = "0";
		// 
		// lblFirstChan
		// 
		this.lblFirstChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblFirstChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblFirstChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblFirstChan.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblFirstChan.Location = new System.Drawing.Point(272, 64);
		this.lblFirstChan.Name = "lblFirstChan";
		this.lblFirstChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblFirstChan.Size = new System.Drawing.Size(89, 17);
		this.lblFirstChan.TabIndex = 44;
		this.lblFirstChan.Text = "First Channel";
		// 
		// lblLoChan
		// 
		this.lblLoChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblLoChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.lblLoChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblLoChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblLoChan.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblLoChan.Location = new System.Drawing.Point(200, 64);
		this.lblLoChan.Name = "lblLoChan";
		this.lblLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblLoChan.Size = new System.Drawing.Size(32, 17);
		this.lblLoChan.TabIndex = 7;
		this.lblLoChan.Text = "0";
		// 
		// lblChanPrompt
		// 
		this.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window;
		this.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblChanPrompt.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblChanPrompt.Location = new System.Drawing.Point(32, 40);
		this.lblChanPrompt.Name = "lblChanPrompt";
		this.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblChanPrompt.Size = new System.Drawing.Size(297, 17);
		this.lblChanPrompt.TabIndex = 0;
		this.lblChanPrompt.Text = "Select the range of multiplexor channels to display";
		this.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.TopRight;
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
		this.lblDemoFunction.Size = new System.Drawing.Size(345, 25);
		this.lblDemoFunction.TabIndex = 1;
		this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.TInScan()";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmDataDisplay
		// 
		this.AcceptButton = this.cmdStartConvert;
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(370, 345);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdStartConvert,
																		this.cmdStopConvert,
																		this.hsbHiChan,
																		this.hsbLoChan,
																		this._lblShowData_15,
																		this._lblChanNum_15,
																		this._lblShowData_7,
																		this._lblChanNum_7,
																		this._lblShowData_14,
																		this._lblChanNum_14,
																		this._lblShowData_6,
																		this._lblChanNum_6,
																		this._lblShowData_13,
																		this._lblChanNum_13,
																		this._lblShowData_5,
																		this._lblChanNum_5,
																		this._lblShowData_12,
																		this._lblChanNum_12,
																		this._lblShowData_4,
																		this._lblChanNum_4,
																		this._lblShowData_11,
																		this._lblChanNum_11,
																		this._lblShowData_3,
																		this._lblChanNum_3,
																		this._lblShowData_10,
																		this._lblChanNum_10,
																		this._lblShowData_2,
																		this._lblChanNum_2,
																		this._lblShowData_9,
																		this._lblChanNum_9,
																		this._lblShowData_1,
																		this._lblChanNum_1,
																		this._lblShowData_8,
																		this._lblChanNum_8,
																		this._lblShowData_0,
																		this._lblChanNum_0,
																		this.lblTemp2,
																		this.lblChan2,
																		this.lblTemp1,
																		this.lblChan1,
																		this.lblLastChan,
																		this.lblHiChan,
																		this.lblFirstChan,
																		this.lblLoChan,
																		this.lblChanPrompt,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmDataDisplay";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Temperature Measurement";
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
	    

		

		private void cmdStartConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartConvert.Click */
		{
			cmdStartConvert.Visible = false;
			cmdStopConvert.Visible = true;
			tmrConvert.Enabled = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			Application.Exit();
		}


		private void hsbHiChan_Change(int newScrollValue)
		{
			if (newScrollValue < hsbLoChan.Value)
			{
				hsbLoChan.Value = newScrollValue;
				lblLoChan.Text = newScrollValue.ToString("0");
			}

			lblHiChan.Text = newScrollValue.ToString("0");
		}


		private void hsbLoChan_Change(int newScrollValue)
		{
			if (hsbHiChan.Value < newScrollValue)
			{
				hsbHiChan.Value = newScrollValue;
				lblHiChan.Text = newScrollValue.ToString("0");
			}

			lblLoChan.Text = newScrollValue.ToString("0");

		}


		private void tmrConvert_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrConvert.Tick */
		{
			
			tmrConvert.Stop();

			//  Collect the data with MccDaq.MccBoard.TInScan()
			//   Input values will be collected from a range of thermocouples.
			//   The data value will be updated and displayed until a key is pressed.
			//   Parameters:
			//     LowChan       :the starting channel of the scan
			//     HighChan      :the ending channel of the scan
			//     MccScale       :temperature scale (Celsius, Fahrenheit, Kelvin)
			//     AvgCount      :the number of samples to average to reduce noise
			//     DataBuffer!()  :the array where the temperature values are collected
			MccDaq.TempScale MccScale = MccDaq.TempScale.Fahrenheit;
			int ADChan = 0; // the channel on the A/D
			int LowMux = hsbLoChan.Value, LowChan=0;
			int HighMux = hsbHiChan.Value, HighChan=0;
			MccDaq.ThermocoupleOptions Options = 0;
			if (UsesEXPs > 0)
			{
				LowChan = (ADChan + 1) * 16 + LowMux;
				HighChan = (ADChan + 1) * 16 + HighMux;
			}
			else
			{
				LowChan = LowMux;
				HighChan = HighMux;
			}

			MccDaq.ErrorInfo ULStat = DaqBoard.TInScan( LowChan, HighChan, MccScale, out DataBuffer[0], Options);

			for (int j=0; j<=LowMux - 1; ++j)
				lblShowData[j].Text = "";
		
			for (int j=HighMux + 1; j< 16; ++j)
				lblShowData[j].Text = "";
			
			for (int i=LowMux, Element=0; i<=HighMux; ++i, ++Element)
				lblShowData[i].Text = DataBuffer[Element].ToString("0") + "°F"; //  print the value
			
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				tmrConvert.Start();
		}

		private void hsbHiChan_Scroll(object eventSender, System.Windows.Forms.ScrollEventArgs eventArgs) /* Handles hsbHiChan.Scroll */
		{

			if (eventArgs.Type == System.Windows.Forms.ScrollEventType.EndScroll)
				hsbHiChan_Change(eventArgs.NewValue);
	        
		}

		private void hsbLoChan_Scroll(object eventSender, System.Windows.Forms.ScrollEventArgs eventArgs) /* Handles hsbLoChan.Scroll */
		{
			if (eventArgs.Type == System.Windows.Forms.ScrollEventType.EndScroll)
				hsbLoChan_Change(eventArgs.NewValue);
		}

	}
}