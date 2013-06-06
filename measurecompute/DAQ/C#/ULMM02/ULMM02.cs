// ==============================================================================
//
//  File:                         ULMM02.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.MemRead() and
//                                Mccdaq.MccBoard.MemWrite()
//
//  Purpose:                      Write data to a memory board and then read
//                                it back again
//
//  Demonstrates:                 How to read and write to memory in blocks
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 5 must be a memory board
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

namespace ULMM02
{
	public class frmShowFileData : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdReadData;
		public Button cmdWriteData;
		public Label lblInstruct2;
		public Label lblInstruct1;
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

		private MccDaq.MccBoard MemBoard;
		const short MemBoardNum = 5; //  Board number for memory board
		const short NUMPOINTS = 100; //  Number of points per block
		const short NUMBLOCKS = 4; //  Number of blocks to read/write

		ushort[] DataBuffer1 = new ushort[NUMPOINTS]; //  dimension Visual Basics data array to hold
		ushort[] DataBuffer2 = new ushort[NUMPOINTS]; //  data read from memory board

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
			

			// Create a new MccBoard object for Board 5
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
		this.cmdReadData = new System.Windows.Forms.Button();
		this.cmdWriteData = new System.Windows.Forms.Button();
		this.lblInstruct2 = new System.Windows.Forms.Label();
		this.lblInstruct1 = new System.Windows.Forms.Label();
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
		this.SuspendLayout();
		// 
		// cmdStopConvert
		// 
		this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStopConvert.Location = new System.Drawing.Point(301, 314);
		this.cmdStopConvert.Name = "cmdStopConvert";
		this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStopConvert.Size = new System.Drawing.Size(49, 25);
		this.cmdStopConvert.TabIndex = 17;
		this.cmdStopConvert.Text = "Quit";
		this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
		// 
		// cmdReadData
		// 
		this.cmdReadData.BackColor = System.Drawing.SystemColors.Control;
		this.cmdReadData.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdReadData.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdReadData.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdReadData.Location = new System.Drawing.Point(205, 52);
		this.cmdReadData.Name = "cmdReadData";
		this.cmdReadData.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdReadData.Size = new System.Drawing.Size(97, 25);
		this.cmdReadData.TabIndex = 19;
		this.cmdReadData.Text = "Read Data";
		this.cmdReadData.Click += new System.EventHandler(this.cmdReadData_Click);
		// 
		// cmdWriteData
		// 
		this.cmdWriteData.BackColor = System.Drawing.SystemColors.Control;
		this.cmdWriteData.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdWriteData.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdWriteData.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdWriteData.Location = new System.Drawing.Point(58, 52);
		this.cmdWriteData.Name = "cmdWriteData";
		this.cmdWriteData.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdWriteData.Size = new System.Drawing.Size(97, 25);
		this.cmdWriteData.TabIndex = 18;
		this.cmdWriteData.Text = "Write Data";
		this.cmdWriteData.Click += new System.EventHandler(this.cmdWriteData_Click);
		// 
		// lblInstruct2
		// 
		this.lblInstruct2.BackColor = System.Drawing.SystemColors.Window;
		this.lblInstruct2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblInstruct2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblInstruct2.ForeColor = System.Drawing.Color.Blue;
		this.lblInstruct2.Location = new System.Drawing.Point(16, 312);
		this.lblInstruct2.Name = "lblInstruct2";
		this.lblInstruct2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct2.Size = new System.Drawing.Size(273, 41);
		this.lblInstruct2.TabIndex = 44;
		this.lblInstruct2.Text = "So for example the value 203 is stored at address 203 in memory. Clicking Read Da" +
			"ta reads the data back and displays it.";
		this.lblInstruct2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblInstruct1
		// 
		this.lblInstruct1.BackColor = System.Drawing.SystemColors.Window;
		this.lblInstruct1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblInstruct1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblInstruct1.ForeColor = System.Drawing.Color.Blue;
		this.lblInstruct1.Location = new System.Drawing.Point(16, 256);
		this.lblInstruct1.Name = "lblInstruct1";
		this.lblInstruct1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct1.Size = new System.Drawing.Size(337, 57);
		this.lblInstruct1.TabIndex = 45;
		this.lblInstruct1.Text = "This program writes 500 values to the memory board by writing 5 blocks of 100 val" +
			"ues to consecutive locations in the memory board. The values that are written co" +
			"rrespond to the memory board address in which they are stored.";
		this.lblInstruct1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// _lblShowData_19
		// 
		this._lblShowData_19.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_19.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_19.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_19.Location = new System.Drawing.Point(330, 229);
		this._lblShowData_19.Name = "_lblShowData_19";
		this._lblShowData_19.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_19.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_19.TabIndex = 43;
		this._lblShowData_19.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		this.lblData19.Size = new System.Drawing.Size(130, 14);
		this.lblData19.TabIndex = 42;
		this.lblData19.Text = "Memory Location 304:";
		this.lblData19.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_9
		// 
		this._lblShowData_9.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_9.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_9.Location = new System.Drawing.Point(144, 229);
		this._lblShowData_9.Name = "_lblShowData_9";
		this._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_9.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_9.TabIndex = 23;
		this._lblShowData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData9
		// 
		this.lblData9.BackColor = System.Drawing.SystemColors.Window;
		this.lblData9.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData9.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData9.Location = new System.Drawing.Point(10, 229);
		this.lblData9.Name = "lblData9";
		this.lblData9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData9.Size = new System.Drawing.Size(130, 15);
		this.lblData9.TabIndex = 21;
		this.lblData9.Text = "Memory Location 104:";
		this.lblData9.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_18
		// 
		this._lblShowData_18.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_18.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_18.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_18.Location = new System.Drawing.Point(330, 216);
		this._lblShowData_18.Name = "_lblShowData_18";
		this._lblShowData_18.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_18.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_18.TabIndex = 41;
		this._lblShowData_18.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		this.lblData18.Size = new System.Drawing.Size(130, 14);
		this.lblData18.TabIndex = 40;
		this.lblData18.Text = "Memory Location 303:";
		this.lblData18.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_8
		// 
		this._lblShowData_8.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_8.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_8.Location = new System.Drawing.Point(144, 216);
		this._lblShowData_8.Name = "_lblShowData_8";
		this._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_8.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_8.TabIndex = 22;
		this._lblShowData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData8
		// 
		this.lblData8.BackColor = System.Drawing.SystemColors.Window;
		this.lblData8.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData8.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData8.Location = new System.Drawing.Point(10, 216);
		this.lblData8.Name = "lblData8";
		this.lblData8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData8.Size = new System.Drawing.Size(130, 15);
		this.lblData8.TabIndex = 20;
		this.lblData8.Text = "Memory Location 103:";
		this.lblData8.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_17
		// 
		this._lblShowData_17.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_17.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_17.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_17.Location = new System.Drawing.Point(330, 204);
		this._lblShowData_17.Name = "_lblShowData_17";
		this._lblShowData_17.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_17.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_17.TabIndex = 39;
		this._lblShowData_17.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		this.lblData17.Size = new System.Drawing.Size(130, 14);
		this.lblData17.TabIndex = 38;
		this.lblData17.Text = "Memory Location 302:";
		this.lblData17.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_7
		// 
		this._lblShowData_7.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_7.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_7.Location = new System.Drawing.Point(144, 204);
		this._lblShowData_7.Name = "_lblShowData_7";
		this._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_7.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_7.TabIndex = 16;
		this._lblShowData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData7
		// 
		this.lblData7.BackColor = System.Drawing.SystemColors.Window;
		this.lblData7.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData7.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData7.Location = new System.Drawing.Point(10, 204);
		this.lblData7.Name = "lblData7";
		this.lblData7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData7.Size = new System.Drawing.Size(130, 15);
		this.lblData7.TabIndex = 8;
		this.lblData7.Text = "Memory Location 102:";
		this.lblData7.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_16
		// 
		this._lblShowData_16.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_16.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_16.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_16.Location = new System.Drawing.Point(330, 191);
		this._lblShowData_16.Name = "_lblShowData_16";
		this._lblShowData_16.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_16.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_16.TabIndex = 37;
		this._lblShowData_16.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		this.lblData16.Size = new System.Drawing.Size(130, 14);
		this.lblData16.TabIndex = 36;
		this.lblData16.Text = "Memory Location 301:";
		this.lblData16.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_6
		// 
		this._lblShowData_6.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_6.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_6.Location = new System.Drawing.Point(144, 191);
		this._lblShowData_6.Name = "_lblShowData_6";
		this._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_6.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_6.TabIndex = 15;
		this._lblShowData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData6
		// 
		this.lblData6.BackColor = System.Drawing.SystemColors.Window;
		this.lblData6.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData6.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData6.Location = new System.Drawing.Point(10, 191);
		this.lblData6.Name = "lblData6";
		this.lblData6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData6.Size = new System.Drawing.Size(130, 15);
		this.lblData6.TabIndex = 7;
		this.lblData6.Text = "Memory Location 101:";
		this.lblData6.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_15
		// 
		this._lblShowData_15.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_15.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_15.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_15.Location = new System.Drawing.Point(330, 179);
		this._lblShowData_15.Name = "_lblShowData_15";
		this._lblShowData_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_15.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_15.TabIndex = 35;
		this._lblShowData_15.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		this.lblData15.Size = new System.Drawing.Size(130, 14);
		this.lblData15.TabIndex = 34;
		this.lblData15.Text = "Memory Location 300:";
		this.lblData15.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_5
		// 
		this._lblShowData_5.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_5.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_5.Location = new System.Drawing.Point(144, 179);
		this._lblShowData_5.Name = "_lblShowData_5";
		this._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_5.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_5.TabIndex = 14;
		this._lblShowData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData5
		// 
		this.lblData5.BackColor = System.Drawing.SystemColors.Window;
		this.lblData5.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData5.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData5.Location = new System.Drawing.Point(10, 179);
		this.lblData5.Name = "lblData5";
		this.lblData5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData5.Size = new System.Drawing.Size(130, 15);
		this.lblData5.TabIndex = 6;
		this.lblData5.Text = "Memory Location 100:";
		this.lblData5.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_14
		// 
		this._lblShowData_14.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_14.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_14.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_14.Location = new System.Drawing.Point(330, 146);
		this._lblShowData_14.Name = "_lblShowData_14";
		this._lblShowData_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_14.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_14.TabIndex = 33;
		this._lblShowData_14.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData14
		// 
		this.lblData14.BackColor = System.Drawing.SystemColors.Window;
		this.lblData14.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData14.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData14.Location = new System.Drawing.Point(189, 146);
		this.lblData14.Name = "lblData14";
		this.lblData14.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData14.Size = new System.Drawing.Size(130, 15);
		this.lblData14.TabIndex = 32;
		this.lblData14.Text = "Memory Location 204:";
		this.lblData14.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_4
		// 
		this._lblShowData_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_4.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_4.Location = new System.Drawing.Point(144, 146);
		this._lblShowData_4.Name = "_lblShowData_4";
		this._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_4.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_4.TabIndex = 13;
		this._lblShowData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData4
		// 
		this.lblData4.BackColor = System.Drawing.SystemColors.Window;
		this.lblData4.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData4.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData4.Location = new System.Drawing.Point(10, 146);
		this.lblData4.Name = "lblData4";
		this.lblData4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData4.Size = new System.Drawing.Size(130, 15);
		this.lblData4.TabIndex = 5;
		this.lblData4.Text = "Memory Location 4:";
		this.lblData4.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_13
		// 
		this._lblShowData_13.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_13.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_13.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_13.Location = new System.Drawing.Point(330, 133);
		this._lblShowData_13.Name = "_lblShowData_13";
		this._lblShowData_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_13.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_13.TabIndex = 31;
		this._lblShowData_13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData13
		// 
		this.lblData13.BackColor = System.Drawing.SystemColors.Window;
		this.lblData13.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData13.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData13.Location = new System.Drawing.Point(189, 133);
		this.lblData13.Name = "lblData13";
		this.lblData13.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData13.Size = new System.Drawing.Size(130, 15);
		this.lblData13.TabIndex = 30;
		this.lblData13.Text = "Memory Location 203:";
		this.lblData13.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_3
		// 
		this._lblShowData_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_3.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_3.Location = new System.Drawing.Point(144, 133);
		this._lblShowData_3.Name = "_lblShowData_3";
		this._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_3.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_3.TabIndex = 12;
		this._lblShowData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData3
		// 
		this.lblData3.BackColor = System.Drawing.SystemColors.Window;
		this.lblData3.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData3.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData3.Location = new System.Drawing.Point(10, 133);
		this.lblData3.Name = "lblData3";
		this.lblData3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData3.Size = new System.Drawing.Size(130, 15);
		this.lblData3.TabIndex = 4;
		this.lblData3.Text = "Memory Location 3:";
		this.lblData3.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_12
		// 
		this._lblShowData_12.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_12.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_12.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_12.Location = new System.Drawing.Point(330, 120);
		this._lblShowData_12.Name = "_lblShowData_12";
		this._lblShowData_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_12.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_12.TabIndex = 29;
		this._lblShowData_12.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData12
		// 
		this.lblData12.BackColor = System.Drawing.SystemColors.Window;
		this.lblData12.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData12.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData12.Location = new System.Drawing.Point(189, 120);
		this.lblData12.Name = "lblData12";
		this.lblData12.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData12.Size = new System.Drawing.Size(130, 15);
		this.lblData12.TabIndex = 28;
		this.lblData12.Text = "Memory Location 202:";
		this.lblData12.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_2
		// 
		this._lblShowData_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_2.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_2.Location = new System.Drawing.Point(144, 120);
		this._lblShowData_2.Name = "_lblShowData_2";
		this._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_2.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_2.TabIndex = 11;
		this._lblShowData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData2
		// 
		this.lblData2.BackColor = System.Drawing.SystemColors.Window;
		this.lblData2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData2.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData2.Location = new System.Drawing.Point(10, 120);
		this.lblData2.Name = "lblData2";
		this.lblData2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData2.Size = new System.Drawing.Size(130, 15);
		this.lblData2.TabIndex = 3;
		this.lblData2.Text = "Memory Location 2:";
		this.lblData2.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_11
		// 
		this._lblShowData_11.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_11.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_11.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_11.Location = new System.Drawing.Point(330, 108);
		this._lblShowData_11.Name = "_lblShowData_11";
		this._lblShowData_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_11.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_11.TabIndex = 27;
		this._lblShowData_11.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData11
		// 
		this.lblData11.BackColor = System.Drawing.SystemColors.Window;
		this.lblData11.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData11.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData11.Location = new System.Drawing.Point(189, 108);
		this.lblData11.Name = "lblData11";
		this.lblData11.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData11.Size = new System.Drawing.Size(130, 15);
		this.lblData11.TabIndex = 26;
		this.lblData11.Text = "Memory Location 201:";
		this.lblData11.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_1
		// 
		this._lblShowData_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_1.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_1.Location = new System.Drawing.Point(144, 108);
		this._lblShowData_1.Name = "_lblShowData_1";
		this._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_1.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_1.TabIndex = 10;
		this._lblShowData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData1
		// 
		this.lblData1.BackColor = System.Drawing.SystemColors.Window;
		this.lblData1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData1.Location = new System.Drawing.Point(10, 108);
		this.lblData1.Name = "lblData1";
		this.lblData1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData1.Size = new System.Drawing.Size(130, 15);
		this.lblData1.TabIndex = 2;
		this.lblData1.Text = "Memory Location 1:";
		this.lblData1.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_10
		// 
		this._lblShowData_10.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_10.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_10.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_10.Location = new System.Drawing.Point(330, 96);
		this._lblShowData_10.Name = "_lblShowData_10";
		this._lblShowData_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_10.Size = new System.Drawing.Size(28, 15);
		this._lblShowData_10.TabIndex = 25;
		this._lblShowData_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData10
		// 
		this.lblData10.BackColor = System.Drawing.SystemColors.Window;
		this.lblData10.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData10.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData10.Location = new System.Drawing.Point(189, 96);
		this.lblData10.Name = "lblData10";
		this.lblData10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData10.Size = new System.Drawing.Size(130, 15);
		this.lblData10.TabIndex = 24;
		this.lblData10.Text = "Memory Location 200:";
		this.lblData10.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblShowData_0
		// 
		this._lblShowData_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblShowData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblShowData_0.ForeColor = System.Drawing.Color.Blue;
		this._lblShowData_0.Location = new System.Drawing.Point(144, 96);
		this._lblShowData_0.Name = "_lblShowData_0";
		this._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblShowData_0.Size = new System.Drawing.Size(34, 15);
		this._lblShowData_0.TabIndex = 9;
		this._lblShowData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblData0
		// 
		this.lblData0.BackColor = System.Drawing.SystemColors.Window;
		this.lblData0.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblData0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblData0.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblData0.Location = new System.Drawing.Point(10, 96);
		this.lblData0.Name = "lblData0";
		this.lblData0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblData0.Size = new System.Drawing.Size(130, 15);
		this.lblData0.TabIndex = 1;
		this.lblData0.Text = "Memory Location 0:";
		this.lblData0.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(20, 7);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(310, 41);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.MemRead() and Mccdaq.MccBoard.MemWrite()";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmShowFileData
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(371, 361);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdStopConvert,
																		this.cmdReadData,
																		this.cmdWriteData,
																		this.lblInstruct2,
																		this.lblInstruct1,
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
	    

		private void cmdReadData_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdReadData.Click */
		{
			short DataPoint;
			
			lblInstruct2.Text = "";
			lblInstruct1.Text = "The data read from the memory board is shown above.";

			int FirstPoint = 0; //  Set address of first point to read
			for (ushort BlockNum=0; BlockNum < NUMBLOCKS; ++BlockNum)
			{
				//  For each block

				//  Read a block of data from  the memory board
				//  DataBuffer2 - Array of data to read data into
				//  FirstPoint - Address to read first point (or FROMHERE)
				//  Count - Number of points to read
				int Count = NUMPOINTS;
				MccDaq.ErrorInfo ULStat = MemBoard.MemRead( out DataBuffer2[0], FirstPoint, Count);
				
				
				for (int i=0; i < 5; ++i)
				{
					DataPoint = (short)(BlockNum * 5 + i);
					lblShowData[DataPoint].Text = DataBuffer2[i].ToString("0");
				}

				FirstPoint = MccDaq.MccBoard.FromHere;
			}

		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			Application.Exit();
		}


		private void cmdWriteData_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdWriteData.Click */
		{
			int DataPoint = 0;
			
			lblInstruct2.Text = "";
			lblInstruct1.Text = "A sample of the array written to the memory board is shown above. Press Read Data to verify.";

			//  Create an array of data with known values to write to the memory board
			int FirstPoint = 0;
			MccDaq.ErrorInfo ULStat;
			for (ushort BlockNum=0; BlockNum < NUMBLOCKS; ++BlockNum)
			{
				for (int i=0; i < NUMPOINTS; ++i)
					DataBuffer1[i] = (ushort)(BlockNum * NUMPOINTS + i);
			

				for (int i=0; i < 5; ++i)
				{
					DataPoint = (short)(5 * BlockNum + i);
					lblShowData[DataPoint].Text = DataBuffer1[i].ToString("0");
				} 

				//  Write the block to the memory board
				//  DataBuffer1 - Array of data to be written
				//  FirstPoint - Address to write first point (or NEXTONE)
				//  Count - Number of points to write
				int Count = NUMPOINTS;
				ULStat = MemBoard.MemWrite( ref DataBuffer1[0], FirstPoint, Count);

				FirstPoint = MccDaq.MccBoard.FromHere;
			}

		}

	}
}