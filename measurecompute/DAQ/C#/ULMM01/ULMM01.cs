// ==============================================================================
//
//  File:                         ULMM01.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.APretrig() with
//                                MccDaq.ScanOptions.ExtMemory option and
//                                Mccdaq.MccBoard.MemReadPretrig()
//
//  Purpose:                      Collect pre-trig data from A/D to memory board
//
//  Demonstrates:                 How to use the collect pre-trigger data
//                                to memory board and then retreive the data.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         DaqBoard must be an A/D board.
//                                Board 5 must be a memory board.
//                                A/D and memory boards must be connected together
//                                via a DT-Connect cable.
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

namespace ULMM01
{
	public class frmShowFileData : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdStartAcq;
		public Button cmdShowData;
		public Button cmdLevelOK;
		public Label lblInstruct;
		public GroupBox fraInstruct;
		public Label lblAcqStat;
		public Label _lblShowData_19;
		public Label lblData19;
		public Label _lblShowData_9;
		public Label lblData9;
		public Label _lblShowData_18;
		public Label lblData18;
		public Label _lblShowData_8;
		public Label lblData8;
		public Label _lblShowData_17;
		public Label lblData17;
		public Label _lblShowData_7;
		public Label lblData7;
		public Label _lblShowData_16;
		public Label lblData16;
		public Label _lblShowData_6;
		public Label lblData6;
		public Label _lblShowData_15;
		public Label lblData15;
		public Label _lblShowData_5;
		public Label lblData5;
		public Label _lblShowData_14;
		public Label lblData14;
		public Label _lblShowData_4;
		public Label lblData4;
		public Label _lblShowData_13;
		public Label lblData13;
		public Label _lblShowData_3;
		public Label lblData3;
		public Label _lblShowData_12;
		public Label lblData12;
		public Label _lblShowData_2;
		public Label lblData2;
		public Label _lblShowData_11;
		public Label lblData11;
		public Label _lblShowData_1;
		public Label lblData1;
		public Label _lblShowData_10;
		public Label lblData10;
		public Label _lblShowData_0;
		public Label lblData0;
		public Label lblDemoFunction;

		public Label[] lblShowData;

		private MccDaq.MccBoard DaqBoard;
		private MccDaq.MccBoard MemBoard;

		const short MemBoardNum = 5; //  Board number for memory board
		const short BufSize = 100; //  Size of buffer used with Mccdaq.MccBoard.MemReadPretrig()

		private ushort[] DataBuffer = new ushort[BufSize]; //  array to hold data read from memory board
	 
		public frmShowFileData()
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
			MemBoard = new MccDaq.MccBoard(MemBoardNum);

			lblShowData = (new Label[]{_lblShowData_0, _lblShowData_1, _lblShowData_2, _lblShowData_3, _lblShowData_4,
										  _lblShowData_5, _lblShowData_6, _lblShowData_7, _lblShowData_8, _lblShowData_9,
										  _lblShowData_10, _lblShowData_11, _lblShowData_12, _lblShowData_13, _lblShowData_14,
										  _lblShowData_15, _lblShowData_16, _lblShowData_17, _lblShowData_18, _lblShowData_19});
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
		this.cmdStopConvert = new System.Windows.Forms.Button();
		this.cmdStartAcq = new System.Windows.Forms.Button();
		this.cmdShowData = new System.Windows.Forms.Button();
		this.fraInstruct = new System.Windows.Forms.GroupBox();
		this.cmdLevelOK = new System.Windows.Forms.Button();
		this.lblInstruct = new System.Windows.Forms.Label();
		this.lblAcqStat = new System.Windows.Forms.Label();
		this._lblShowData_19 = new System.Windows.Forms.Label();
		this.lblData19 = new System.Windows.Forms.Label();
		this._lblShowData_9 = new System.Windows.Forms.Label();
		this.lblData9 = new System.Windows.Forms.Label();
		this._lblShowData_18 = new System.Windows.Forms.Label();
		this.lblData18 = new System.Windows.Forms.Label();
		this._lblShowData_8 = new System.Windows.Forms.Label();
		this.lblData8 = new System.Windows.Forms.Label();
		this._lblShowData_17 = new System.Windows.Forms.Label();
		this.lblData17 = new System.Windows.Forms.Label();
		this._lblShowData_7 = new System.Windows.Forms.Label();
		this.lblData7 = new System.Windows.Forms.Label();
		this._lblShowData_16 = new System.Windows.Forms.Label();
		this.lblData16 = new System.Windows.Forms.Label();
		this._lblShowData_6 = new System.Windows.Forms.Label();
		this.lblData6 = new System.Windows.Forms.Label();
		this._lblShowData_15 = new System.Windows.Forms.Label();
		this.lblData15 = new System.Windows.Forms.Label();
		this._lblShowData_5 = new System.Windows.Forms.Label();
		this.lblData5 = new System.Windows.Forms.Label();
		this._lblShowData_14 = new System.Windows.Forms.Label();
		this.lblData14 = new System.Windows.Forms.Label();
		this._lblShowData_4 = new System.Windows.Forms.Label();
		this.lblData4 = new System.Windows.Forms.Label();
		this._lblShowData_13 = new System.Windows.Forms.Label();
		this.lblData13 = new System.Windows.Forms.Label();
		this._lblShowData_3 = new System.Windows.Forms.Label();
		this.lblData3 = new System.Windows.Forms.Label();
		this._lblShowData_12 = new System.Windows.Forms.Label();
		this.lblData12 = new System.Windows.Forms.Label();
		this._lblShowData_2 = new System.Windows.Forms.Label();
		this.lblData2 = new System.Windows.Forms.Label();
		this._lblShowData_11 = new System.Windows.Forms.Label();
		this.lblData11 = new System.Windows.Forms.Label();
		this._lblShowData_1 = new System.Windows.Forms.Label();
		this.lblData1 = new System.Windows.Forms.Label();
		this._lblShowData_10 = new System.Windows.Forms.Label();
		this.lblData10 = new System.Windows.Forms.Label();
		this._lblShowData_0 = new System.Windows.Forms.Label();
		this.lblData0 = new System.Windows.Forms.Label();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.fraInstruct.SuspendLayout();
		this.SuspendLayout();
		// 
		// cmdStopConvert
		// 
		this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStopConvert.Location = new System.Drawing.Point(312, 264);
		this.cmdStopConvert.Name = "cmdStopConvert";
		this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStopConvert.Size = new System.Drawing.Size(49, 25);
		this.cmdStopConvert.TabIndex = 17;
		this.cmdStopConvert.Text = "Quit";
		this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
		// 
		// cmdStartAcq
		// 
		this.cmdStartAcq.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStartAcq.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStartAcq.Enabled = false;
		this.cmdStartAcq.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStartAcq.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStartAcq.Location = new System.Drawing.Point(208, 264);
		this.cmdStartAcq.Name = "cmdStartAcq";
		this.cmdStartAcq.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStartAcq.Size = new System.Drawing.Size(97, 25);
		this.cmdStartAcq.TabIndex = 18;
		this.cmdStartAcq.Text = "Enable Trigger";
		this.cmdStartAcq.Click += new System.EventHandler(this.cmdStartAcq_Click);
		// 
		// cmdShowData
		// 
		this.cmdShowData.BackColor = System.Drawing.SystemColors.Control;
		this.cmdShowData.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdShowData.Enabled = false;
		this.cmdShowData.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdShowData.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdShowData.Location = new System.Drawing.Point(208, 264);
		this.cmdShowData.Name = "cmdShowData";
		this.cmdShowData.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdShowData.Size = new System.Drawing.Size(97, 25);
		this.cmdShowData.TabIndex = 20;
		this.cmdShowData.Text = "Read Memory";
		this.cmdShowData.Visible = false;
		this.cmdShowData.Click += new System.EventHandler(this.cmdShowData_Click);
		// 
		// fraInstruct
		// 
		this.fraInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.fraInstruct.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.cmdLevelOK,
																					this.lblInstruct});
		this.fraInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.fraInstruct.ForeColor = System.Drawing.SystemColors.WindowText;
		this.fraInstruct.Location = new System.Drawing.Point(56, 48);
		this.fraInstruct.Name = "fraInstruct";
		this.fraInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.fraInstruct.Size = new System.Drawing.Size(257, 49);
		this.fraInstruct.TabIndex = 45;
		this.fraInstruct.TabStop = false;
		// 
		// cmdLevelOK
		// 
		this.cmdLevelOK.BackColor = System.Drawing.SystemColors.Control;
		this.cmdLevelOK.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdLevelOK.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdLevelOK.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdLevelOK.Location = new System.Drawing.Point(216, 16);
		this.cmdLevelOK.Name = "cmdLevelOK";
		this.cmdLevelOK.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdLevelOK.Size = new System.Drawing.Size(33, 25);
		this.cmdLevelOK.TabIndex = 47;
		this.cmdLevelOK.Text = "OK";
		this.cmdLevelOK.Click += new System.EventHandler(this.cmdLevelOK_Click);
		// 
		// lblInstruct
		// 
		this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblInstruct.ForeColor = System.Drawing.Color.Red;
		this.lblInstruct.Location = new System.Drawing.Point(6, 13);
		this.lblInstruct.Name = "lblInstruct";
		this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct.Size = new System.Drawing.Size(198, 26);
		this.lblInstruct.TabIndex = 46;
		this.lblInstruct.Text = "Make sure that the trigger input is at a low level before starting.";
		this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblAcqStat
		// 
		this.lblAcqStat.BackColor = System.Drawing.SystemColors.Window;
		this.lblAcqStat.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblAcqStat.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblAcqStat.ForeColor = System.Drawing.Color.Blue;
		this.lblAcqStat.Location = new System.Drawing.Point(16, 256);
		this.lblAcqStat.Name = "lblAcqStat";
		this.lblAcqStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblAcqStat.Size = new System.Drawing.Size(169, 30);
		this.lblAcqStat.TabIndex = 19;
		this.lblAcqStat.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_19
		// 
		this._lblShowData_19.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_19.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_19.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_19.Location = new System.Drawing.Point(285, 229);
		this._lblShowData_19.Name = "_lblShowData_19";
		this._lblShowData_19.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_19.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_19.TabIndex = 44;
		// 
		// lblData19
		// 
		this.lblData19.BackColor = System.Drawing.SystemColors.Window;
		this.lblData19.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData19.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData19.Location = new System.Drawing.Point(189, 229);
		this.lblData19.Name = "lblData19";
		this.lblData19.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData19.Size = new System.Drawing.Size(84, 14);
		this.lblData19.TabIndex = 43;
		this.lblData19.Text = "Data Point 19:";
		// 
		// _lblShowData_9
		// 
		this._lblShowData_9.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_9.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_9.Location = new System.Drawing.Point(125, 229);
		this._lblShowData_9.Name = "_lblShowData_9";
		this._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_9.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_9.TabIndex = 24;
		// 
		// lblData9
		// 
		this.lblData9.BackColor = System.Drawing.SystemColors.Window;
		this.lblData9.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData9.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData9.Location = new System.Drawing.Point(35, 229);
		this.lblData9.Name = "lblData9";
		this.lblData9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData9.Size = new System.Drawing.Size(78, 14);
		this.lblData9.TabIndex = 22;
		this.lblData9.Text = "Data Point 9:";
		// 
		// _lblShowData_18
		// 
		this._lblShowData_18.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_18.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_18.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_18.Location = new System.Drawing.Point(285, 216);
		this._lblShowData_18.Name = "_lblShowData_18";
		this._lblShowData_18.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_18.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_18.TabIndex = 42;
		// 
		// lblData18
		// 
		this.lblData18.BackColor = System.Drawing.SystemColors.Window;
		this.lblData18.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData18.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData18.Location = new System.Drawing.Point(189, 216);
		this.lblData18.Name = "lblData18";
		this.lblData18.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData18.Size = new System.Drawing.Size(84, 14);
		this.lblData18.TabIndex = 41;
		this.lblData18.Text = "Data Point 18:";
		// 
		// _lblShowData_8
		// 
		this._lblShowData_8.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_8.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_8.Location = new System.Drawing.Point(125, 216);
		this._lblShowData_8.Name = "_lblShowData_8";
		this._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_8.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_8.TabIndex = 23;
		// 
		// lblData8
		// 
		this.lblData8.BackColor = System.Drawing.SystemColors.Window;
		this.lblData8.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData8.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData8.Location = new System.Drawing.Point(35, 216);
		this.lblData8.Name = "lblData8";
		this.lblData8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData8.Size = new System.Drawing.Size(78, 14);
		this.lblData8.TabIndex = 21;
		this.lblData8.Text = "Data Point 8:";
		// 
		// _lblShowData_17
		// 
		this._lblShowData_17.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_17.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_17.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_17.Location = new System.Drawing.Point(285, 203);
		this._lblShowData_17.Name = "_lblShowData_17";
		this._lblShowData_17.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_17.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_17.TabIndex = 40;
		// 
		// lblData17
		// 
		this.lblData17.BackColor = System.Drawing.SystemColors.Window;
		this.lblData17.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData17.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData17.Location = new System.Drawing.Point(189, 203);
		this.lblData17.Name = "lblData17";
		this.lblData17.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData17.Size = new System.Drawing.Size(84, 14);
		this.lblData17.TabIndex = 39;
		this.lblData17.Text = "Data Point 17:";
		// 
		// _lblShowData_7
		// 
		this._lblShowData_7.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_7.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_7.Location = new System.Drawing.Point(125, 203);
		this._lblShowData_7.Name = "_lblShowData_7";
		this._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_7.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_7.TabIndex = 16;
		// 
		// lblData7
		// 
		this.lblData7.BackColor = System.Drawing.SystemColors.Window;
		this.lblData7.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData7.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData7.Location = new System.Drawing.Point(35, 203);
		this.lblData7.Name = "lblData7";
		this.lblData7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData7.Size = new System.Drawing.Size(78, 14);
		this.lblData7.TabIndex = 8;
		this.lblData7.Text = "Data Point 7:";
		// 
		// _lblShowData_16
		// 
		this._lblShowData_16.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_16.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_16.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_16.Location = new System.Drawing.Point(285, 190);
		this._lblShowData_16.Name = "_lblShowData_16";
		this._lblShowData_16.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_16.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_16.TabIndex = 38;
		// 
		// lblData16
		// 
		this.lblData16.BackColor = System.Drawing.SystemColors.Window;
		this.lblData16.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData16.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData16.Location = new System.Drawing.Point(189, 190);
		this.lblData16.Name = "lblData16";
		this.lblData16.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData16.Size = new System.Drawing.Size(84, 14);
		this.lblData16.TabIndex = 37;
		this.lblData16.Text = "Data Point 16:";
		// 
		// _lblShowData_6
		// 
		this._lblShowData_6.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_6.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_6.Location = new System.Drawing.Point(125, 190);
		this._lblShowData_6.Name = "_lblShowData_6";
		this._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_6.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_6.TabIndex = 15;
		// 
		// lblData6
		// 
		this.lblData6.BackColor = System.Drawing.SystemColors.Window;
		this.lblData6.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData6.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData6.Location = new System.Drawing.Point(35, 190);
		this.lblData6.Name = "lblData6";
		this.lblData6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData6.Size = new System.Drawing.Size(78, 14);
		this.lblData6.TabIndex = 7;
		this.lblData6.Text = "Data Point 6:";
		// 
		// _lblShowData_15
		// 
		this._lblShowData_15.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_15.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_15.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_15.Location = new System.Drawing.Point(285, 178);
		this._lblShowData_15.Name = "_lblShowData_15";
		this._lblShowData_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_15.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_15.TabIndex = 36;
		// 
		// lblData15
		// 
		this.lblData15.BackColor = System.Drawing.SystemColors.Window;
		this.lblData15.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData15.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData15.Location = new System.Drawing.Point(189, 178);
		this.lblData15.Name = "lblData15";
		this.lblData15.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData15.Size = new System.Drawing.Size(84, 14);
		this.lblData15.TabIndex = 35;
		this.lblData15.Text = "Data Point 15:";
		// 
		// _lblShowData_5
		// 
		this._lblShowData_5.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_5.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_5.Location = new System.Drawing.Point(125, 178);
		this._lblShowData_5.Name = "_lblShowData_5";
		this._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_5.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_5.TabIndex = 14;
		// 
		// lblData5
		// 
		this.lblData5.BackColor = System.Drawing.SystemColors.Window;
		this.lblData5.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData5.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData5.Location = new System.Drawing.Point(35, 178);
		this.lblData5.Name = "lblData5";
		this.lblData5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData5.Size = new System.Drawing.Size(78, 14);
		this.lblData5.TabIndex = 6;
		this.lblData5.Text = "Data Point 5:";
		// 
		// _lblShowData_14
		// 
		this._lblShowData_14.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_14.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_14.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_14.Location = new System.Drawing.Point(285, 165);
		this._lblShowData_14.Name = "_lblShowData_14";
		this._lblShowData_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_14.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_14.TabIndex = 34;
		// 
		// lblData14
		// 
		this.lblData14.BackColor = System.Drawing.SystemColors.Window;
		this.lblData14.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData14.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData14.Location = new System.Drawing.Point(189, 165);
		this.lblData14.Name = "lblData14";
		this.lblData14.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData14.Size = new System.Drawing.Size(84, 14);
		this.lblData14.TabIndex = 33;
		this.lblData14.Text = "Data Point 14:";
		// 
		// _lblShowData_4
		// 
		this._lblShowData_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_4.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_4.Location = new System.Drawing.Point(125, 165);
		this._lblShowData_4.Name = "_lblShowData_4";
		this._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_4.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_4.TabIndex = 13;
		// 
		// lblData4
		// 
		this.lblData4.BackColor = System.Drawing.SystemColors.Window;
		this.lblData4.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData4.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData4.Location = new System.Drawing.Point(35, 165);
		this.lblData4.Name = "lblData4";
		this.lblData4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData4.Size = new System.Drawing.Size(78, 14);
		this.lblData4.TabIndex = 5;
		this.lblData4.Text = "Data Point 4:";
		// 
		// _lblShowData_13
		// 
		this._lblShowData_13.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_13.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_13.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_13.Location = new System.Drawing.Point(285, 152);
		this._lblShowData_13.Name = "_lblShowData_13";
		this._lblShowData_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_13.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_13.TabIndex = 32;
		// 
		// lblData13
		// 
		this.lblData13.BackColor = System.Drawing.SystemColors.Window;
		this.lblData13.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData13.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData13.Location = new System.Drawing.Point(189, 152);
		this.lblData13.Name = "lblData13";
		this.lblData13.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData13.Size = new System.Drawing.Size(84, 14);
		this.lblData13.TabIndex = 31;
		this.lblData13.Text = "Data Point 13:";
		// 
		// _lblShowData_3
		// 
		this._lblShowData_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_3.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_3.Location = new System.Drawing.Point(125, 152);
		this._lblShowData_3.Name = "_lblShowData_3";
		this._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_3.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_3.TabIndex = 12;
		// 
		// lblData3
		// 
		this.lblData3.BackColor = System.Drawing.SystemColors.Window;
		this.lblData3.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData3.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData3.Location = new System.Drawing.Point(35, 152);
		this.lblData3.Name = "lblData3";
		this.lblData3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData3.Size = new System.Drawing.Size(78, 14);
		this.lblData3.TabIndex = 4;
		this.lblData3.Text = "Data Point 3:";
		// 
		// _lblShowData_12
		// 
		this._lblShowData_12.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_12.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_12.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_12.Location = new System.Drawing.Point(285, 139);
		this._lblShowData_12.Name = "_lblShowData_12";
		this._lblShowData_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_12.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_12.TabIndex = 30;
		// 
		// lblData12
		// 
		this.lblData12.BackColor = System.Drawing.SystemColors.Window;
		this.lblData12.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData12.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData12.Location = new System.Drawing.Point(189, 139);
		this.lblData12.Name = "lblData12";
		this.lblData12.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData12.Size = new System.Drawing.Size(84, 14);
		this.lblData12.TabIndex = 29;
		this.lblData12.Text = "Data Point 12:";
		// 
		// _lblShowData_2
		// 
		this._lblShowData_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_2.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_2.Location = new System.Drawing.Point(125, 139);
		this._lblShowData_2.Name = "_lblShowData_2";
		this._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_2.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_2.TabIndex = 11;
		// 
		// lblData2
		// 
		this.lblData2.BackColor = System.Drawing.SystemColors.Window;
		this.lblData2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData2.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData2.Location = new System.Drawing.Point(35, 139);
		this.lblData2.Name = "lblData2";
		this.lblData2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData2.Size = new System.Drawing.Size(78, 14);
		this.lblData2.TabIndex = 3;
		this.lblData2.Text = "Data Point 2:";
		// 
		// _lblShowData_11
		// 
		this._lblShowData_11.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_11.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_11.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_11.Location = new System.Drawing.Point(285, 126);
		this._lblShowData_11.Name = "_lblShowData_11";
		this._lblShowData_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_11.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_11.TabIndex = 28;
		// 
		// lblData11
		// 
		this.lblData11.BackColor = System.Drawing.SystemColors.Window;
		this.lblData11.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData11.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData11.Location = new System.Drawing.Point(189, 126);
		this.lblData11.Name = "lblData11";
		this.lblData11.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData11.Size = new System.Drawing.Size(84, 14);
		this.lblData11.TabIndex = 27;
		this.lblData11.Text = "Data Point 11:";
		// 
		// _lblShowData_1
		// 
		this._lblShowData_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_1.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_1.Location = new System.Drawing.Point(125, 126);
		this._lblShowData_1.Name = "_lblShowData_1";
		this._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_1.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_1.TabIndex = 10;
		// 
		// lblData1
		// 
		this.lblData1.BackColor = System.Drawing.SystemColors.Window;
		this.lblData1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData1.Location = new System.Drawing.Point(35, 126);
		this.lblData1.Name = "lblData1";
		this.lblData1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData1.Size = new System.Drawing.Size(78, 14);
		this.lblData1.TabIndex = 2;
		this.lblData1.Text = "Data Point 1:";
		// 
		// _lblShowData_10
		// 
		this._lblShowData_10.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_10.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_10.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_10.Location = new System.Drawing.Point(285, 114);
		this._lblShowData_10.Name = "_lblShowData_10";
		this._lblShowData_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_10.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_10.TabIndex = 26;
		// 
		// lblData10
		// 
		this.lblData10.BackColor = System.Drawing.SystemColors.Window;
		this.lblData10.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData10.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData10.Location = new System.Drawing.Point(189, 114);
		this.lblData10.Name = "lblData10";
		this.lblData10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData10.Size = new System.Drawing.Size(84, 14);
		this.lblData10.TabIndex = 25;
		this.lblData10.Text = "Data Point 10:";
		// 
		// _lblShowData_0
		// 
		this._lblShowData_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_0.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_0.Location = new System.Drawing.Point(125, 114);
		this._lblShowData_0.Name = "_lblShowData_0";
		this._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_0.Size = new System.Drawing.Size(46, 14);
		this._lblShowData_0.TabIndex = 9;
		// 
		// lblData0
		// 
		this.lblData0.BackColor = System.Drawing.SystemColors.Window;
		this.lblData0.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData0.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData0.Location = new System.Drawing.Point(35, 114);
		this.lblData0.Name = "lblData0";
		this.lblData0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData0.Size = new System.Drawing.Size(78, 14);
		this.lblData0.TabIndex = 1;
		this.lblData0.Text = "Data Point 0:";
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
		this.lblDemoFunction.Size = new System.Drawing.Size(310, 41);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.APretrig() with External Memory";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmShowFileData
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(371, 299);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdStopConvert,
																		this.cmdStartAcq,
																		this.cmdShowData,
																		this.fraInstruct,
																		this.lblAcqStat,
																		this._lblShowData_19,
																		this.lblData19,
																		this._lblShowData_9,
																		this.lblData9,
																		this._lblShowData_18,
																		this.lblData18,
																		this._lblShowData_8,
																		this.lblData8,
																		this._lblShowData_17,
																		this.lblData17,
																		this._lblShowData_7,
																		this.lblData7,
																		this._lblShowData_16,
																		this.lblData16,
																		this._lblShowData_6,
																		this.lblData6,
																		this._lblShowData_15,
																		this.lblData15,
																		this._lblShowData_5,
																		this.lblData5,
																		this._lblShowData_14,
																		this.lblData14,
																		this._lblShowData_4,
																		this.lblData4,
																		this._lblShowData_13,
																		this.lblData13,
																		this._lblShowData_3,
																		this.lblData3,
																		this._lblShowData_12,
																		this.lblData12,
																		this._lblShowData_2,
																		this.lblData2,
																		this._lblShowData_11,
																		this.lblData11,
																		this._lblShowData_1,
																		this.lblData1,
																		this._lblShowData_10,
																		this.lblData10,
																		this._lblShowData_0,
																		this.lblData0,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.Color.Blue;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmShowFileData";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Analog Input Scan";
		this.fraInstruct.ResumeLayout(false);
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmShowFileData());
		}
	    	

		private void cmdLevelOK_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdLevelOK.Click */
		{
			cmdStartAcq.Enabled = true;
			cmdLevelOK.Visible = false;
			lblInstruct.ForeColor = System.Drawing.ColorTranslator.FromOle(0XFF0000);
			lblInstruct.Text = "Click 'Enable Trigger' when ready...";
		}


		private void cmdShowData_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdShowData.Click */
		{
			//  Read the first block of data from the memory board.
			//  Read a block of data from  the memory board
			//   DataBuffer - Array of data to read data into
			//   FirstPoint - Address to read first point (or FROMHERE)
			//   Count - Number of points to read
			int Count = BufSize;
			short FirstPoint = 0; //  Set address of first point to read
			MccDaq.ErrorInfo ULStat = MemBoard.MemReadPretrig( out DataBuffer[0], FirstPoint, Count);

			for (int i=0; i<=19; ++i)
			{
				// Raw data from memory board contains a 4 bit channel number (LSB's)
				// and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value.
				DataBuffer[i] >>= 4;
				DataBuffer[i] &= 0x0fff;
				
				lblShowData[i].Text = DataBuffer[i].ToString("0");
			}

			lblAcqStat.Text = "Trigger occurred between points #9 and #10";
		}


		private void cmdStartAcq_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartAcq.Click */
		{
			cmdStartAcq.Enabled = false;
			cmdStartAcq.Visible = false;
			lblInstruct.Text = "Acquiring data ...";
			Application.DoEvents();

			//  Collect data to memory with MccDaq.MccBoard.APretrig() and
			//  the MccDaq.ScanOptions.ExtMemory option
			//   Parameters:
			//     LowChan      :the first channel of the scan
			//     HighChan     :the last channel of the scan
			//     PretrigCount :number of pre-trigger points
			//     TotalCount   :the total number of A/D samples to collect
			//     Rate         :per channel sampling rate ((samples per second) per channel)
			//     Range        :the gain for the board
			//     Options      :data collection options
			int LowChan = 0;         //  Low channel of A/D scan
			int HighChan = 0;        //  High channel of A/D scan
			int PretrigCount = 10;   //  Number of pre-trigger points
			int TotalCount = 10000;  //  Number of data points to collect
			int Rate = 10000;      //  per channel sampling rate ((samples per second) per channel)
			MccDaq.Range Range = MccDaq.Range.Bip5Volts; //  set the range
			int Dummy = 0;           //  Pass a dummy integer to MccDaq.MccBoard.ATrig() (this is ignored)
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.ExtMemory; //  Send data to memory board
			MccDaq.ErrorInfo ULStat = DaqBoard.APretrig( LowChan, HighChan, ref PretrigCount, ref TotalCount, ref Rate, Range, Dummy, Options);
			if (ULStat.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors) 
				Application.Exit();

			cmdShowData.Enabled = true;
			cmdShowData.Visible = true;
			lblInstruct.Text = "Click 'Read Memory' to read memory board and display data.";

		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			Application.Exit();
		}

	}
}