// ==============================================================================
//
//  File:                         ULMM03.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.AInScan() with
//                                MccDaq.MccBoar.ExtMemory option
//
//  Purpose:                      Collect data from A/D to memory board
//
//  Demonstrates:                 How to use the MccDaq.MccBoard.ExtMemory option to
//                                send data to a memory board and how to
//                                read the data back again.
//
//  Other Library Calls:          MccDaq.MccBoard.MemRead(),
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         DaqBoard must be an A/D board.
//                                Board 5 must be a memory board.
//                                A/D and memory boards must be connected
//                                together via a DT-Connect cable.
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

namespace ULMM03
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;
		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdReadMemBoard;
		public Button cmdStartConvert;
		public Label _lblADData_19;
		public Label _lblDataPoint_19;
		public Label _lblADData_14;
		public Label _lblDataPoint_14;
		public Label _lblADData_9;
		public Label _lblDataPoint_9;
		public Label _lblADData_4;
		public Label _lblDataPoint_4;
		public Label _lblADData_18;
		public Label _lblDataPoint_18;
		public Label _lblADData_13;
		public Label _lblDataPoint_13;
		public Label _lblADData_8;
		public Label _lblDataPoint_8;
		public Label _lblADData_3;
		public Label _lblDataPoint_3;
		public Label _lblADData_17;
		public Label _lblDataPoint_17;
		public Label _lblADData_12;
		public Label _lblDataPoint_12;
		public Label _lblADData_7;
		public Label _lblDataPoint_7;
		public Label _lblADData_2;
		public Label _lblDataPoint_2;
		public Label _lblADData_16;
		public Label _lblDataPoint_16;
		public Label _lblADData_11;
		public Label _lblDataPoint_11;
		public Label _lblADData_6;
		public Label _lblDataPoint_6;
		public Label _lblADData_1;
		public Label _lblDataPoint_1;
		public Label _lblADData_15;
		public Label _lblDataPoint_15;
		public Label _lblADData_10;
		public Label _lblDataPoint_10;
		public Label _lblADData_5;
		public Label _lblDataPoint_5;
		public Label _lblADData_0;
		public Label _lblDataPoint_0;
		public Label _lblColTitle_7;
		public Label _lblColTitle_6;
		public Label _lblColTitle_5;
		public Label _lblColTitle_4;
		public Label _lblColTitle_3;
		public Label _lblColTitle_2;
		public Label _lblColTitle_1;
		public Label _lblColTitle_0;
		public Label lblDemoFunction;

		public Label[] lblADData;
		public Label[] lblDataPoint;

		private MccDaq.MccBoard ADBoard;
		private MccDaq.MccBoard MemBoard;

		const short ADBoardNumber = 0; //  Board number of A/D board
		const short MemBoardNumber = 5; //  Board number of memory board
		const short NumPoints = 1000; //  Number of points to collect from A/D
		const int BufSize = 20; //  Size of buffer used with MccDaq.MccBoard.MemRead()

		private ushort[] DataBuffer = new ushort[BufSize];
		private int PointNum = 0;
		private int FirstPoint = 0;


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
			


			ADBoard = new MccDaq.MccBoard(ADBoardNumber);
			MemBoard = new MccDaq.MccBoard(MemBoardNumber);

			lblADData = (new Label[]{_lblADData_0, _lblADData_1, _lblADData_2, _lblADData_3, _lblADData_4,
									_lblADData_5, _lblADData_6, _lblADData_7, _lblADData_8, _lblADData_9,
									_lblADData_10, _lblADData_11, _lblADData_12, _lblADData_13, _lblADData_14,
									_lblADData_15, _lblADData_16, _lblADData_17, _lblADData_18, _lblADData_19});

			lblDataPoint = (new Label[]{_lblDataPoint_0, _lblDataPoint_1, _lblDataPoint_2, _lblDataPoint_3, _lblDataPoint_4,
										_lblDataPoint_5, _lblDataPoint_6, _lblDataPoint_7, _lblDataPoint_8, _lblDataPoint_9,
										_lblDataPoint_10, _lblDataPoint_11, _lblDataPoint_12, _lblDataPoint_13, _lblDataPoint_14, 
										_lblDataPoint_15, _lblDataPoint_16, _lblDataPoint_17, _lblDataPoint_18, _lblDataPoint_19});
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
			this.cmdReadMemBoard = new System.Windows.Forms.Button();
			this.cmdStartConvert = new System.Windows.Forms.Button();
			this._lblADData_19 = new System.Windows.Forms.Label();
			this._lblDataPoint_19 = new System.Windows.Forms.Label();
			this._lblADData_14 = new System.Windows.Forms.Label();
			this._lblDataPoint_14 = new System.Windows.Forms.Label();
			this._lblADData_9 = new System.Windows.Forms.Label();
			this._lblDataPoint_9 = new System.Windows.Forms.Label();
			this._lblADData_4 = new System.Windows.Forms.Label();
			this._lblDataPoint_4 = new System.Windows.Forms.Label();
			this._lblADData_18 = new System.Windows.Forms.Label();
			this._lblDataPoint_18 = new System.Windows.Forms.Label();
			this._lblADData_13 = new System.Windows.Forms.Label();
			this._lblDataPoint_13 = new System.Windows.Forms.Label();
			this._lblADData_8 = new System.Windows.Forms.Label();
			this._lblDataPoint_8 = new System.Windows.Forms.Label();
			this._lblADData_3 = new System.Windows.Forms.Label();
			this._lblDataPoint_3 = new System.Windows.Forms.Label();
			this._lblADData_17 = new System.Windows.Forms.Label();
			this._lblDataPoint_17 = new System.Windows.Forms.Label();
			this._lblADData_12 = new System.Windows.Forms.Label();
			this._lblDataPoint_12 = new System.Windows.Forms.Label();
			this._lblADData_7 = new System.Windows.Forms.Label();
			this._lblDataPoint_7 = new System.Windows.Forms.Label();
			this._lblADData_2 = new System.Windows.Forms.Label();
			this._lblDataPoint_2 = new System.Windows.Forms.Label();
			this._lblADData_16 = new System.Windows.Forms.Label();
			this._lblDataPoint_16 = new System.Windows.Forms.Label();
			this._lblADData_11 = new System.Windows.Forms.Label();
			this._lblDataPoint_11 = new System.Windows.Forms.Label();
			this._lblADData_6 = new System.Windows.Forms.Label();
			this._lblDataPoint_6 = new System.Windows.Forms.Label();
			this._lblADData_1 = new System.Windows.Forms.Label();
			this._lblDataPoint_1 = new System.Windows.Forms.Label();
			this._lblADData_15 = new System.Windows.Forms.Label();
			this._lblDataPoint_15 = new System.Windows.Forms.Label();
			this._lblADData_10 = new System.Windows.Forms.Label();
			this._lblDataPoint_10 = new System.Windows.Forms.Label();
			this._lblADData_5 = new System.Windows.Forms.Label();
			this._lblDataPoint_5 = new System.Windows.Forms.Label();
			this._lblADData_0 = new System.Windows.Forms.Label();
			this._lblDataPoint_0 = new System.Windows.Forms.Label();
			this._lblColTitle_7 = new System.Windows.Forms.Label();
			this._lblColTitle_6 = new System.Windows.Forms.Label();
			this._lblColTitle_5 = new System.Windows.Forms.Label();
			this._lblColTitle_4 = new System.Windows.Forms.Label();
			this._lblColTitle_3 = new System.Windows.Forms.Label();
			this._lblColTitle_2 = new System.Windows.Forms.Label();
			this._lblColTitle_1 = new System.Windows.Forms.Label();
			this._lblColTitle_0 = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// cmdStopConvert
			// 
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(250, 218);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(59, 27);
			this.cmdStopConvert.TabIndex = 10;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			// 
			// cmdReadMemBoard
			// 
			this.cmdReadMemBoard.BackColor = System.Drawing.SystemColors.Control;
			this.cmdReadMemBoard.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdReadMemBoard.Enabled = false;
			this.cmdReadMemBoard.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdReadMemBoard.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdReadMemBoard.Location = new System.Drawing.Point(160, 218);
			this.cmdReadMemBoard.Name = "cmdReadMemBoard";
			this.cmdReadMemBoard.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdReadMemBoard.Size = new System.Drawing.Size(65, 27);
			this.cmdReadMemBoard.TabIndex = 12;
			this.cmdReadMemBoard.Text = "Read ";
			this.cmdReadMemBoard.Click += new System.EventHandler(this.cmdReadMemBoard_Click);
			// 
			// cmdStartConvert
			// 
			this.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartConvert.Location = new System.Drawing.Point(71, 218);
			this.cmdStartConvert.Name = "cmdStartConvert";
			this.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartConvert.Size = new System.Drawing.Size(65, 27);
			this.cmdStartConvert.TabIndex = 11;
			this.cmdStartConvert.Text = "Start";
			this.cmdStartConvert.Click += new System.EventHandler(this.cmdStartConvert_Click);
			// 
			// _lblADData_19
			// 
			this._lblADData_19.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_19.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_19.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_19.Location = new System.Drawing.Point(320, 167);
			this._lblADData_19.Name = "_lblADData_19";
			this._lblADData_19.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_19.Size = new System.Drawing.Size(40, 14);
			this._lblADData_19.TabIndex = 43;
			this._lblADData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_19
			// 
			this._lblDataPoint_19.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_19.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_19.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_19.Location = new System.Drawing.Point(288, 167);
			this._lblDataPoint_19.Name = "_lblDataPoint_19";
			this._lblDataPoint_19.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_19.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_19.TabIndex = 42;
			this._lblDataPoint_19.Text = "19";
			this._lblDataPoint_19.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_14
			// 
			this._lblADData_14.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_14.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_14.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_14.Location = new System.Drawing.Point(231, 167);
			this._lblADData_14.Name = "_lblADData_14";
			this._lblADData_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_14.Size = new System.Drawing.Size(40, 14);
			this._lblADData_14.TabIndex = 33;
			this._lblADData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_14
			// 
			this._lblDataPoint_14.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_14.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_14.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_14.Location = new System.Drawing.Point(199, 167);
			this._lblDataPoint_14.Name = "_lblDataPoint_14";
			this._lblDataPoint_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_14.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_14.TabIndex = 32;
			this._lblDataPoint_14.Text = "14";
			this._lblDataPoint_14.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_9
			// 
			this._lblADData_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_9.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_9.Location = new System.Drawing.Point(141, 167);
			this._lblADData_9.Name = "_lblADData_9";
			this._lblADData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_9.Size = new System.Drawing.Size(40, 14);
			this._lblADData_9.TabIndex = 14;
			this._lblADData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_9
			// 
			this._lblDataPoint_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_9.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_9.Location = new System.Drawing.Point(109, 167);
			this._lblDataPoint_9.Name = "_lblDataPoint_9";
			this._lblDataPoint_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_9.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_9.TabIndex = 23;
			this._lblDataPoint_9.Text = "9";
			this._lblDataPoint_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_4
			// 
			this._lblADData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_4.Location = new System.Drawing.Point(52, 167);
			this._lblADData_4.Name = "_lblADData_4";
			this._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_4.Size = new System.Drawing.Size(40, 14);
			this._lblADData_4.TabIndex = 6;
			this._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_4
			// 
			this._lblDataPoint_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_4.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_4.Location = new System.Drawing.Point(20, 167);
			this._lblDataPoint_4.Name = "_lblDataPoint_4";
			this._lblDataPoint_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_4.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_4.TabIndex = 18;
			this._lblDataPoint_4.Text = "4";
			this._lblDataPoint_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_18
			// 
			this._lblADData_18.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_18.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_18.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_18.Location = new System.Drawing.Point(320, 148);
			this._lblADData_18.Name = "_lblADData_18";
			this._lblADData_18.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_18.Size = new System.Drawing.Size(40, 14);
			this._lblADData_18.TabIndex = 41;
			this._lblADData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_18
			// 
			this._lblDataPoint_18.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_18.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_18.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_18.Location = new System.Drawing.Point(288, 148);
			this._lblDataPoint_18.Name = "_lblDataPoint_18";
			this._lblDataPoint_18.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_18.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_18.TabIndex = 40;
			this._lblDataPoint_18.Text = "18";
			this._lblDataPoint_18.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_13
			// 
			this._lblADData_13.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_13.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_13.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_13.Location = new System.Drawing.Point(231, 148);
			this._lblADData_13.Name = "_lblADData_13";
			this._lblADData_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_13.Size = new System.Drawing.Size(40, 14);
			this._lblADData_13.TabIndex = 31;
			this._lblADData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_13
			// 
			this._lblDataPoint_13.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_13.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_13.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_13.Location = new System.Drawing.Point(199, 148);
			this._lblDataPoint_13.Name = "_lblDataPoint_13";
			this._lblDataPoint_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_13.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_13.TabIndex = 30;
			this._lblDataPoint_13.Text = "13";
			this._lblDataPoint_13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_8
			// 
			this._lblADData_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_8.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_8.Location = new System.Drawing.Point(141, 148);
			this._lblADData_8.Name = "_lblADData_8";
			this._lblADData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_8.Size = new System.Drawing.Size(40, 14);
			this._lblADData_8.TabIndex = 13;
			this._lblADData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_8
			// 
			this._lblDataPoint_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_8.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_8.Location = new System.Drawing.Point(109, 148);
			this._lblDataPoint_8.Name = "_lblDataPoint_8";
			this._lblDataPoint_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_8.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_8.TabIndex = 22;
			this._lblDataPoint_8.Text = "8";
			this._lblDataPoint_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_3
			// 
			this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_3.Location = new System.Drawing.Point(52, 148);
			this._lblADData_3.Name = "_lblADData_3";
			this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_3.Size = new System.Drawing.Size(40, 14);
			this._lblADData_3.TabIndex = 5;
			this._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_3
			// 
			this._lblDataPoint_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_3.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_3.Location = new System.Drawing.Point(20, 148);
			this._lblDataPoint_3.Name = "_lblDataPoint_3";
			this._lblDataPoint_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_3.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_3.TabIndex = 17;
			this._lblDataPoint_3.Text = "3";
			this._lblDataPoint_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_17
			// 
			this._lblADData_17.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_17.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_17.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_17.Location = new System.Drawing.Point(320, 128);
			this._lblADData_17.Name = "_lblADData_17";
			this._lblADData_17.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_17.Size = new System.Drawing.Size(40, 14);
			this._lblADData_17.TabIndex = 39;
			this._lblADData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_17
			// 
			this._lblDataPoint_17.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_17.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_17.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_17.Location = new System.Drawing.Point(288, 128);
			this._lblDataPoint_17.Name = "_lblDataPoint_17";
			this._lblDataPoint_17.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_17.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_17.TabIndex = 38;
			this._lblDataPoint_17.Text = "17";
			this._lblDataPoint_17.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_12
			// 
			this._lblADData_12.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_12.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_12.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_12.Location = new System.Drawing.Point(231, 128);
			this._lblADData_12.Name = "_lblADData_12";
			this._lblADData_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_12.Size = new System.Drawing.Size(40, 14);
			this._lblADData_12.TabIndex = 29;
			this._lblADData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_12
			// 
			this._lblDataPoint_12.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_12.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_12.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_12.Location = new System.Drawing.Point(199, 128);
			this._lblDataPoint_12.Name = "_lblDataPoint_12";
			this._lblDataPoint_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_12.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_12.TabIndex = 28;
			this._lblDataPoint_12.Text = "12";
			this._lblDataPoint_12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_7
			// 
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Location = new System.Drawing.Point(141, 128);
			this._lblADData_7.Name = "_lblADData_7";
			this._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_7.Size = new System.Drawing.Size(40, 14);
			this._lblADData_7.TabIndex = 9;
			this._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_7
			// 
			this._lblDataPoint_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_7.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_7.Location = new System.Drawing.Point(109, 128);
			this._lblDataPoint_7.Name = "_lblDataPoint_7";
			this._lblDataPoint_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_7.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_7.TabIndex = 21;
			this._lblDataPoint_7.Text = "7";
			this._lblDataPoint_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_2
			// 
			this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_2.Location = new System.Drawing.Point(52, 128);
			this._lblADData_2.Name = "_lblADData_2";
			this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_2.Size = new System.Drawing.Size(40, 14);
			this._lblADData_2.TabIndex = 4;
			this._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_2
			// 
			this._lblDataPoint_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_2.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_2.Location = new System.Drawing.Point(20, 128);
			this._lblDataPoint_2.Name = "_lblDataPoint_2";
			this._lblDataPoint_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_2.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_2.TabIndex = 16;
			this._lblDataPoint_2.Text = "2";
			this._lblDataPoint_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_16
			// 
			this._lblADData_16.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_16.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_16.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_16.Location = new System.Drawing.Point(320, 109);
			this._lblADData_16.Name = "_lblADData_16";
			this._lblADData_16.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_16.Size = new System.Drawing.Size(40, 14);
			this._lblADData_16.TabIndex = 37;
			this._lblADData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_16
			// 
			this._lblDataPoint_16.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_16.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_16.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_16.Location = new System.Drawing.Point(288, 109);
			this._lblDataPoint_16.Name = "_lblDataPoint_16";
			this._lblDataPoint_16.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_16.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_16.TabIndex = 36;
			this._lblDataPoint_16.Text = "16";
			this._lblDataPoint_16.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_11
			// 
			this._lblADData_11.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_11.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_11.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_11.Location = new System.Drawing.Point(231, 109);
			this._lblADData_11.Name = "_lblADData_11";
			this._lblADData_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_11.Size = new System.Drawing.Size(40, 14);
			this._lblADData_11.TabIndex = 27;
			this._lblADData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_11
			// 
			this._lblDataPoint_11.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_11.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_11.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_11.Location = new System.Drawing.Point(199, 109);
			this._lblDataPoint_11.Name = "_lblDataPoint_11";
			this._lblDataPoint_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_11.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_11.TabIndex = 26;
			this._lblDataPoint_11.Text = "11";
			this._lblDataPoint_11.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_6
			// 
			this._lblADData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_6.Location = new System.Drawing.Point(141, 109);
			this._lblADData_6.Name = "_lblADData_6";
			this._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_6.Size = new System.Drawing.Size(40, 14);
			this._lblADData_6.TabIndex = 8;
			this._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_6
			// 
			this._lblDataPoint_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_6.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_6.Location = new System.Drawing.Point(109, 109);
			this._lblDataPoint_6.Name = "_lblDataPoint_6";
			this._lblDataPoint_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_6.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_6.TabIndex = 20;
			this._lblDataPoint_6.Text = "6";
			this._lblDataPoint_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_1
			// 
			this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_1.Location = new System.Drawing.Point(52, 109);
			this._lblADData_1.Name = "_lblADData_1";
			this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_1.Size = new System.Drawing.Size(40, 14);
			this._lblADData_1.TabIndex = 3;
			this._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_1
			// 
			this._lblDataPoint_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_1.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_1.Location = new System.Drawing.Point(20, 109);
			this._lblDataPoint_1.Name = "_lblDataPoint_1";
			this._lblDataPoint_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_1.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_1.TabIndex = 15;
			this._lblDataPoint_1.Text = "1";
			this._lblDataPoint_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_15
			// 
			this._lblADData_15.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_15.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_15.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_15.Location = new System.Drawing.Point(320, 90);
			this._lblADData_15.Name = "_lblADData_15";
			this._lblADData_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_15.Size = new System.Drawing.Size(40, 14);
			this._lblADData_15.TabIndex = 35;
			this._lblADData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_15
			// 
			this._lblDataPoint_15.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_15.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_15.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_15.Location = new System.Drawing.Point(288, 90);
			this._lblDataPoint_15.Name = "_lblDataPoint_15";
			this._lblDataPoint_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_15.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_15.TabIndex = 34;
			this._lblDataPoint_15.Text = "15";
			this._lblDataPoint_15.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_10
			// 
			this._lblADData_10.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_10.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_10.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_10.Location = new System.Drawing.Point(231, 90);
			this._lblADData_10.Name = "_lblADData_10";
			this._lblADData_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_10.Size = new System.Drawing.Size(40, 14);
			this._lblADData_10.TabIndex = 25;
			this._lblADData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_10
			// 
			this._lblDataPoint_10.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_10.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_10.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_10.Location = new System.Drawing.Point(199, 90);
			this._lblDataPoint_10.Name = "_lblDataPoint_10";
			this._lblDataPoint_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_10.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_10.TabIndex = 24;
			this._lblDataPoint_10.Text = "10";
			this._lblDataPoint_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_5
			// 
			this._lblADData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_5.Location = new System.Drawing.Point(141, 90);
			this._lblADData_5.Name = "_lblADData_5";
			this._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_5.Size = new System.Drawing.Size(40, 14);
			this._lblADData_5.TabIndex = 7;
			this._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_5
			// 
			this._lblDataPoint_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_5.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_5.Location = new System.Drawing.Point(109, 90);
			this._lblDataPoint_5.Name = "_lblDataPoint_5";
			this._lblDataPoint_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_5.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_5.TabIndex = 19;
			this._lblDataPoint_5.Text = "5";
			this._lblDataPoint_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblADData_0
			// 
			this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_0.Location = new System.Drawing.Point(52, 90);
			this._lblADData_0.Name = "_lblADData_0";
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.Size = new System.Drawing.Size(40, 14);
			this._lblADData_0.TabIndex = 2;
			this._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblDataPoint_0
			// 
			this._lblDataPoint_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataPoint_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataPoint_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblDataPoint_0.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblDataPoint_0.Location = new System.Drawing.Point(20, 90);
			this._lblDataPoint_0.Name = "_lblDataPoint_0";
			this._lblDataPoint_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataPoint_0.Size = new System.Drawing.Size(33, 14);
			this._lblDataPoint_0.TabIndex = 1;
			this._lblDataPoint_0.Text = "0";
			this._lblDataPoint_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_7
			// 
			this._lblColTitle_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_7.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_7.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_7.Location = new System.Drawing.Point(327, 71);
			this._lblColTitle_7.Name = "_lblColTitle_7";
			this._lblColTitle_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_7.Size = new System.Drawing.Size(41, 14);
			this._lblColTitle_7.TabIndex = 51;
			this._lblColTitle_7.Text = "Value";
			this._lblColTitle_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_6
			// 
			this._lblColTitle_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_6.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_6.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_6.Location = new System.Drawing.Point(288, 71);
			this._lblColTitle_6.Name = "_lblColTitle_6";
			this._lblColTitle_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_6.Size = new System.Drawing.Size(33, 14);
			this._lblColTitle_6.TabIndex = 50;
			this._lblColTitle_6.Text = "Data";
			this._lblColTitle_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_5
			// 
			this._lblColTitle_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_5.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_5.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_5.Location = new System.Drawing.Point(237, 71);
			this._lblColTitle_5.Name = "_lblColTitle_5";
			this._lblColTitle_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_5.Size = new System.Drawing.Size(35, 14);
			this._lblColTitle_5.TabIndex = 49;
			this._lblColTitle_5.Text = "Value";
			this._lblColTitle_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_4
			// 
			this._lblColTitle_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_4.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_4.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_4.Location = new System.Drawing.Point(199, 71);
			this._lblColTitle_4.Name = "_lblColTitle_4";
			this._lblColTitle_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_4.Size = new System.Drawing.Size(33, 14);
			this._lblColTitle_4.TabIndex = 48;
			this._lblColTitle_4.Text = "Data";
			this._lblColTitle_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_3
			// 
			this._lblColTitle_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_3.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_3.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_3.Location = new System.Drawing.Point(148, 71);
			this._lblColTitle_3.Name = "_lblColTitle_3";
			this._lblColTitle_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_3.Size = new System.Drawing.Size(36, 14);
			this._lblColTitle_3.TabIndex = 47;
			this._lblColTitle_3.Text = "Value";
			this._lblColTitle_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_2
			// 
			this._lblColTitle_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_2.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_2.Location = new System.Drawing.Point(109, 71);
			this._lblColTitle_2.Name = "_lblColTitle_2";
			this._lblColTitle_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_2.Size = new System.Drawing.Size(33, 14);
			this._lblColTitle_2.TabIndex = 46;
			this._lblColTitle_2.Text = "Data";
			this._lblColTitle_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_1
			// 
			this._lblColTitle_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_1.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_1.Location = new System.Drawing.Point(58, 71);
			this._lblColTitle_1.Name = "_lblColTitle_1";
			this._lblColTitle_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_1.Size = new System.Drawing.Size(38, 14);
			this._lblColTitle_1.TabIndex = 45;
			this._lblColTitle_1.Text = "Value";
			this._lblColTitle_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// _lblColTitle_0
			// 
			this._lblColTitle_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblColTitle_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblColTitle_0.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this._lblColTitle_0.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblColTitle_0.Location = new System.Drawing.Point(20, 71);
			this._lblColTitle_0.Name = "_lblColTitle_0";
			this._lblColTitle_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblColTitle_0.Size = new System.Drawing.Size(33, 14);
			this._lblColTitle_0.TabIndex = 44;
			this._lblColTitle_0.Text = "Data";
			this._lblColTitle_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
			this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.AInScan() with MccDaq.MccBoar.ExtMemory option";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// frmDataDisplay
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(384, 255);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																							 this.cmdStopConvert,
																							 this.cmdReadMemBoard,
																							 this.cmdStartConvert,
																							 this._lblADData_19,
																							 this._lblDataPoint_19,
																							 this._lblADData_14,
																							 this._lblDataPoint_14,
																							 this._lblADData_9,
																							 this._lblDataPoint_9,
																							 this._lblADData_4,
																							 this._lblDataPoint_4,
																							 this._lblADData_18,
																							 this._lblDataPoint_18,
																							 this._lblADData_13,
																							 this._lblDataPoint_13,
																							 this._lblADData_8,
																							 this._lblDataPoint_8,
																							 this._lblADData_3,
																							 this._lblDataPoint_3,
																							 this._lblADData_17,
																							 this._lblDataPoint_17,
																							 this._lblADData_12,
																							 this._lblDataPoint_12,
																							 this._lblADData_7,
																							 this._lblDataPoint_7,
																							 this._lblADData_2,
																							 this._lblDataPoint_2,
																							 this._lblADData_16,
																							 this._lblDataPoint_16,
																							 this._lblADData_11,
																							 this._lblDataPoint_11,
																							 this._lblADData_6,
																							 this._lblDataPoint_6,
																							 this._lblADData_1,
																							 this._lblDataPoint_1,
																							 this._lblADData_15,
																							 this._lblDataPoint_15,
																							 this._lblADData_10,
																							 this._lblDataPoint_10,
																							 this._lblADData_5,
																							 this._lblDataPoint_5,
																							 this._lblADData_0,
																							 this._lblDataPoint_0,
																							 this._lblColTitle_7,
																							 this._lblColTitle_6,
																							 this._lblColTitle_5,
																							 this._lblColTitle_4,
																							 this._lblColTitle_3,
																							 this._lblColTitle_2,
																							 this._lblColTitle_1,
																							 this._lblColTitle_0,
																							 this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(7, 103);
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
	  

		private void cmdReadMemBoard_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdReadMemBoard.Click */
		{
			UInt16 DataPoint;

			int CurDataValue;

			//  Read the data back from the memory board in blocks.
			//  Print each block of data on the screen.
			//   DataBuffer - Array of data to read data into
			//   FirstPoint - Address to read first point (or FROMHERE)
			//   Count - Number of points to read
			int Count = BufSize;
			MccDaq.ErrorInfo ULStat = MemBoard.MemRead( out DataBuffer[0], FirstPoint, Count);
			

			FirstPoint = MccDaq.MccBoard.FromHere;

			for (int i=0; i < BufSize; ++i)
			{
				//  Raw data from memory board contains a 4 bit channel number (LSB's)
				//  and a 12 bit A/D value (MSB's).  The following code strips out the
				//  channel tags from the A/D data.
				DataBuffer[i] >>= 4;
				DataBuffer[i] &= 0x0fff;
			

				lblDataPoint[i].Text = (PointNum + i).ToString("0");
				lblADData[i].Text = DataBuffer[i].ToString("0");
			}

			PointNum = PointNum + BufSize;
			if (PointNum >= NumPoints)
			{
				PointNum = 0;
				ULStat = MemBoard.MemReset();
				

			}

		}


		private void cmdStartConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartConvert.Click */
		{

			MccDaq.ScanOptions Options;
			short Dummy;
			MccDaq.Range Range;
			int Rate;
			int Count;
			int HighChan;
			int LowChan;
			MccDaq.ErrorInfo ULStat;
	        
			cmdStartConvert.Enabled = false;
			cmdReadMemBoard.Enabled = false;

			//  Collect data to memory with MccDaq.MccBoard.AInScan() and the EXTMEMORY option
			//    Parameters:
			//      LowChan      :the first channel of the scan
			//      HighChan     :the last channel of the scan
			//      Count        :the total number of A/D samples to collect
			//      Rate         :per channel sampling rate ((samples per second) per channel)
			//      Range        :the Range for the board
			//      DataBuffer[] :the array for the collected data values
			//      Options      :data collection options

			ULStat = MemBoard.MemReset();
			


			LowChan = 0; //  Low channel of A/D scan
			HighChan = 0; //  High channel of A/D scan
			Count = NumPoints; //  Number of data points to collect
			Rate = 5000; //  per channel sampling rate ((samples per second) per channel)
			Range = MccDaq.Range.Bip5Volts;
			Dummy = 0; //  Placeholder (ignored)
			Options = MccDaq.ScanOptions.ExtMemory; //  Send data to memory board

			ULStat = ADBoard.AInScan( LowChan, HighChan, Count, ref Rate, Range, Dummy, Options);

			cmdStartConvert.Enabled = true;
			cmdReadMemBoard.Enabled = true;

		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			short ULStat;
			Application.Exit();
		}

		
	}
}