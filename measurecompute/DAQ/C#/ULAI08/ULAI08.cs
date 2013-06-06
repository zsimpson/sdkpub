// ==============================================================================
//
//  File:                         ULAI08.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.APretrig()
//
//  Purpose:                      Waits for a trigger, then returns a specified
//                                number of analog samples before and after
//                                the trigger.
//
//  Demonstration:                Displays the analog input on one channel and
//                                waits for the trigger.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must support pre/post triggering
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

namespace ULAI08
{
	public class frmPreTrig : System.Windows.Forms.Form
	{

		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdQuit;
		public Button cmdTrigEnable;
		public Button cmdLevelOK;
		public Label lblInstruct;
		public GroupBox frmInstruct;
		public Label _lblPostTrig_10;
		public Label lblPost10;
		public Label _lblPreTrig_9;
		public Label lblPre1;
		public Label _lblPostTrig_9;
		public Label lblPost9;
		public Label _lblPreTrig_8;
		public Label lblPre2;
		public Label _lblPostTrig_8;
		public Label lblPost8;
		public Label _lblPreTrig_7;
		public Label lblPre3;
		public Label _lblPostTrig_7;
		public Label lblPost7;
		public Label _lblPreTrig_6;
		public Label lblPre4;
		public Label _lblPostTrig_6;
		public Label lblPost6;
		public Label _lblPreTrig_5;
		public Label lblPre5;
		public Label _lblPostTrig_5;
		public Label lblPost5;
		public Label _lblPreTrig_4;
		public Label lblPre6;
		public Label _lblPostTrig_4;
		public Label lblPost4;
		public Label _lblPreTrig_3;
		public Label lblPre7;
		public Label _lblPostTrig_3;
		public Label lblPost3;
		public Label _lblPreTrig_2;
		public Label lblPre8;
		public Label _lblPostTrig_2;
		public Label lblPost2;
		public Label _lblPreTrig_1;
		public Label lblPre9;
		public Label _lblPostTrig_1;
		public Label lblPost1;
		public Label _lblPreTrig_0;
		public Label lblPre10;
		public Label lblPostTrigData;
		public Label lblPreTrigData;
		public Label lblDemoFunction;

		public Label[] lblPostTrig;
		public Label[] lblPreTrig;

		const int NumPoints = 600;        //  Number of data points to collect
		const int FirstPoint = 0;         //  set first element in buffer to transfer to array
		const int PretrigCount = 10;      //  number of data points before trigger to store
		const int TotalCount = NumPoints; //  total number of data points to collect
		const int BufSize = 1112;         //  set buffer size large enough to hold all data

		private MccDaq.MccBoard DaqBoard;
		private int MemHandle =  0;		  //  define a variable to contain the handle for
									      // memory allocated by Windows through MccService.WinBufAlloc()
		private ushort[] ADData = new ushort[BufSize];  // size must be TotalCount + 512 minimum


		public frmPreTrig()
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
			MemHandle = MccDaq.MccService.WinBufAlloc(BufSize); 
			if (MemHandle == 0) 
				Application.Exit();

			lblPostTrig = (new Label[] {_lblPostTrig_1, _lblPostTrig_2, _lblPostTrig_3, _lblPostTrig_4, _lblPostTrig_5,
									_lblPostTrig_6, _lblPostTrig_7, _lblPostTrig_8, _lblPostTrig_9, _lblPostTrig_10});
			lblPreTrig =  (new Label[] {_lblPreTrig_0, _lblPreTrig_1, _lblPreTrig_2, _lblPreTrig_3, _lblPreTrig_4, 
										_lblPreTrig_5, _lblPreTrig_6, _lblPreTrig_7, _lblPreTrig_8, _lblPreTrig_9});

			
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
			this.cmdQuit = new System.Windows.Forms.Button();
			this.cmdTrigEnable = new System.Windows.Forms.Button();
			this.frmInstruct = new System.Windows.Forms.GroupBox();
			this.cmdLevelOK = new System.Windows.Forms.Button();
			this.lblInstruct = new System.Windows.Forms.Label();
			this._lblPostTrig_10 = new System.Windows.Forms.Label();
			this.lblPost10 = new System.Windows.Forms.Label();
			this._lblPreTrig_9 = new System.Windows.Forms.Label();
			this.lblPre1 = new System.Windows.Forms.Label();
			this._lblPostTrig_9 = new System.Windows.Forms.Label();
			this.lblPost9 = new System.Windows.Forms.Label();
			this._lblPreTrig_8 = new System.Windows.Forms.Label();
			this.lblPre2 = new System.Windows.Forms.Label();
			this._lblPostTrig_8 = new System.Windows.Forms.Label();
			this.lblPost8 = new System.Windows.Forms.Label();
			this._lblPreTrig_7 = new System.Windows.Forms.Label();
			this.lblPre3 = new System.Windows.Forms.Label();
			this._lblPostTrig_7 = new System.Windows.Forms.Label();
			this.lblPost7 = new System.Windows.Forms.Label();
			this._lblPreTrig_6 = new System.Windows.Forms.Label();
			this.lblPre4 = new System.Windows.Forms.Label();
			this._lblPostTrig_6 = new System.Windows.Forms.Label();
			this.lblPost6 = new System.Windows.Forms.Label();
			this._lblPreTrig_5 = new System.Windows.Forms.Label();
			this.lblPre5 = new System.Windows.Forms.Label();
			this._lblPostTrig_5 = new System.Windows.Forms.Label();
			this.lblPost5 = new System.Windows.Forms.Label();
			this._lblPreTrig_4 = new System.Windows.Forms.Label();
			this.lblPre6 = new System.Windows.Forms.Label();
			this._lblPostTrig_4 = new System.Windows.Forms.Label();
			this.lblPost4 = new System.Windows.Forms.Label();
			this._lblPreTrig_3 = new System.Windows.Forms.Label();
			this.lblPre7 = new System.Windows.Forms.Label();
			this._lblPostTrig_3 = new System.Windows.Forms.Label();
			this.lblPost3 = new System.Windows.Forms.Label();
			this._lblPreTrig_2 = new System.Windows.Forms.Label();
			this.lblPre8 = new System.Windows.Forms.Label();
			this._lblPostTrig_2 = new System.Windows.Forms.Label();
			this.lblPost2 = new System.Windows.Forms.Label();
			this._lblPreTrig_1 = new System.Windows.Forms.Label();
			this.lblPre9 = new System.Windows.Forms.Label();
			this._lblPostTrig_1 = new System.Windows.Forms.Label();
			this.lblPost1 = new System.Windows.Forms.Label();
			this._lblPreTrig_0 = new System.Windows.Forms.Label();
			this.lblPre10 = new System.Windows.Forms.Label();
			this.lblPostTrigData = new System.Windows.Forms.Label();
			this.lblPreTrigData = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.frmInstruct.SuspendLayout();
			this.SuspendLayout();
			//
			// cmdQuit
			//
			this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
			this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdQuit.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdQuit.Location = new System.Drawing.Point(296, 240);
			this.cmdQuit.Name = "cmdQuit";
			this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdQuit.Size = new System.Drawing.Size(52, 26);
			this.cmdQuit.TabIndex = 17;
			this.cmdQuit.Text = "Quit";
			this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
			//
			// cmdTrigEnable
			//
			this.cmdTrigEnable.BackColor = System.Drawing.SystemColors.Control;
			this.cmdTrigEnable.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdTrigEnable.Enabled = false;
			this.cmdTrigEnable.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdTrigEnable.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdTrigEnable.Location = new System.Drawing.Point(272, 40);
			this.cmdTrigEnable.Name = "cmdTrigEnable";
			this.cmdTrigEnable.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdTrigEnable.Size = new System.Drawing.Size(97, 25);
			this.cmdTrigEnable.TabIndex = 18;
			this.cmdTrigEnable.Text = "Enable Trigger";
			this.cmdTrigEnable.Click += new System.EventHandler(this.cmdTrigEnable_Click);
			//
			// frmInstruct
			//
			this.frmInstruct.BackColor = System.Drawing.SystemColors.Window;
			this.frmInstruct.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdLevelOK, this.lblInstruct});
			this.frmInstruct.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.frmInstruct.ForeColor = System.Drawing.SystemColors.WindowText;
			this.frmInstruct.Location = new System.Drawing.Point(8, 24);
			this.frmInstruct.Name = "frmInstruct";
			this.frmInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.frmInstruct.Size = new System.Drawing.Size(257, 49);
			this.frmInstruct.TabIndex = 45;
			this.frmInstruct.TabStop = false;
			//
			// cmdLevelOK
			//
			this.cmdLevelOK.BackColor = System.Drawing.SystemColors.Control;
			this.cmdLevelOK.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdLevelOK.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
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
			this.lblInstruct.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblInstruct.ForeColor = System.Drawing.Color.Red;
			this.lblInstruct.Location = new System.Drawing.Point(6, 13);
			this.lblInstruct.Name = "lblInstruct";
			this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInstruct.Size = new System.Drawing.Size(198, 26);
			this.lblInstruct.TabIndex = 46;
			this.lblInstruct.Text = "Make sure that the trigger input is at a low level before starting.";
			this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblPostTrig_10
			//
			this._lblPostTrig_10.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_10.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_10.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_10.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_10.Location = new System.Drawing.Point(277, 211);
			this._lblPostTrig_10.Name = "_lblPostTrig_10";
			this._lblPostTrig_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_10.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_10.TabIndex = 42;
			this._lblPostTrig_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost10
			//
			this.lblPost10.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost10.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost10.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost10.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost10.Location = new System.Drawing.Point(198, 211);
			this.lblPost10.Name = "lblPost10";
			this.lblPost10.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost10.Size = new System.Drawing.Size(73, 14);
			this.lblPost10.TabIndex = 40;
			this.lblPost10.Text = "Trigger +10";
			//
			// _lblPreTrig_9
			//
			this._lblPreTrig_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_9.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_9.Location = new System.Drawing.Point(96, 212);
			this._lblPreTrig_9.Name = "_lblPreTrig_9";
			this._lblPreTrig_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_9.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_9.TabIndex = 22;
			this._lblPreTrig_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre1
			//
			this.lblPre1.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre1.Location = new System.Drawing.Point(18, 211);
			this.lblPre1.Name = "lblPre1";
			this.lblPre1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre1.Size = new System.Drawing.Size(73, 14);
			this.lblPre1.TabIndex = 20;
			this.lblPre1.Text = "Trigger -1";
			//
			// _lblPostTrig_9
			//
			this._lblPostTrig_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_9.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_9.Location = new System.Drawing.Point(277, 198);
			this._lblPostTrig_9.Name = "_lblPostTrig_9";
			this._lblPostTrig_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_9.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_9.TabIndex = 41;
			this._lblPostTrig_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost9
			//
			this.lblPost9.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost9.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost9.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost9.Location = new System.Drawing.Point(198, 198);
			this.lblPost9.Name = "lblPost9";
			this.lblPost9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost9.Size = new System.Drawing.Size(73, 14);
			this.lblPost9.TabIndex = 39;
			this.lblPost9.Text = "Trigger +9";
			//
			// _lblPreTrig_8
			//
			this._lblPreTrig_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_8.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_8.Location = new System.Drawing.Point(96, 199);
			this._lblPreTrig_8.Name = "_lblPreTrig_8";
			this._lblPreTrig_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_8.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_8.TabIndex = 21;
			this._lblPreTrig_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre2
			//
			this.lblPre2.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre2.Location = new System.Drawing.Point(18, 198);
			this.lblPre2.Name = "lblPre2";
			this.lblPre2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre2.Size = new System.Drawing.Size(73, 14);
			this.lblPre2.TabIndex = 19;
			this.lblPre2.Text = "Trigger -2";
			//
			// _lblPostTrig_8
			//
			this._lblPostTrig_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_8.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_8.Location = new System.Drawing.Point(277, 186);
			this._lblPostTrig_8.Name = "_lblPostTrig_8";
			this._lblPostTrig_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_8.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_8.TabIndex = 38;
			this._lblPostTrig_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost8
			//
			this.lblPost8.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost8.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost8.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost8.Location = new System.Drawing.Point(198, 186);
			this.lblPost8.Name = "lblPost8";
			this.lblPost8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost8.Size = new System.Drawing.Size(73, 14);
			this.lblPost8.TabIndex = 37;
			this.lblPost8.Text = "Trigger +8";
			//
			// _lblPreTrig_7
			//
			this._lblPreTrig_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_7.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_7.Location = new System.Drawing.Point(96, 186);
			this._lblPreTrig_7.Name = "_lblPreTrig_7";
			this._lblPreTrig_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_7.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_7.TabIndex = 16;
			this._lblPreTrig_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre3
			//
			this.lblPre3.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre3.Location = new System.Drawing.Point(18, 186);
			this.lblPre3.Name = "lblPre3";
			this.lblPre3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre3.Size = new System.Drawing.Size(73, 14);
			this.lblPre3.TabIndex = 8;
			this.lblPre3.Text = "Trigger -3";
			//
			// _lblPostTrig_7
			//
			this._lblPostTrig_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_7.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_7.Location = new System.Drawing.Point(277, 173);
			this._lblPostTrig_7.Name = "_lblPostTrig_7";
			this._lblPostTrig_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_7.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_7.TabIndex = 34;
			this._lblPostTrig_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost7
			//
			this.lblPost7.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost7.Location = new System.Drawing.Point(198, 173);
			this.lblPost7.Name = "lblPost7";
			this.lblPost7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost7.Size = new System.Drawing.Size(73, 14);
			this.lblPost7.TabIndex = 33;
			this.lblPost7.Text = "Trigger +7";
			//
			// _lblPreTrig_6
			//
			this._lblPreTrig_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_6.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_6.Location = new System.Drawing.Point(96, 173);
			this._lblPreTrig_6.Name = "_lblPreTrig_6";
			this._lblPreTrig_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_6.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_6.TabIndex = 15;
			this._lblPreTrig_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre4
			//
			this.lblPre4.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre4.Location = new System.Drawing.Point(18, 173);
			this.lblPre4.Name = "lblPre4";
			this.lblPre4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre4.Size = new System.Drawing.Size(73, 14);
			this.lblPre4.TabIndex = 7;
			this.lblPre4.Text = "Trigger -4";
			//
			// _lblPostTrig_6
			//
			this._lblPostTrig_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_6.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_6.Location = new System.Drawing.Point(277, 160);
			this._lblPostTrig_6.Name = "_lblPostTrig_6";
			this._lblPostTrig_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_6.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_6.TabIndex = 30;
			this._lblPostTrig_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost6
			//
			this.lblPost6.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost6.Location = new System.Drawing.Point(198, 160);
			this.lblPost6.Name = "lblPost6";
			this.lblPost6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost6.Size = new System.Drawing.Size(73, 14);
			this.lblPost6.TabIndex = 29;
			this.lblPost6.Text = "Trigger +6";
			//
			// _lblPreTrig_5
			//
			this._lblPreTrig_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_5.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_5.Location = new System.Drawing.Point(96, 160);
			this._lblPreTrig_5.Name = "_lblPreTrig_5";
			this._lblPreTrig_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_5.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_5.TabIndex = 14;
			this._lblPreTrig_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre5
			//
			this.lblPre5.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre5.Location = new System.Drawing.Point(18, 160);
			this.lblPre5.Name = "lblPre5";
			this.lblPre5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre5.Size = new System.Drawing.Size(73, 14);
			this.lblPre5.TabIndex = 6;
			this.lblPre5.Text = "Trigger -5";
			//
			// _lblPostTrig_5
			//
			this._lblPostTrig_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_5.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_5.Location = new System.Drawing.Point(277, 147);
			this._lblPostTrig_5.Name = "_lblPostTrig_5";
			this._lblPostTrig_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_5.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_5.TabIndex = 26;
			this._lblPostTrig_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost5
			//
			this.lblPost5.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost5.Location = new System.Drawing.Point(198, 147);
			this.lblPost5.Name = "lblPost5";
			this.lblPost5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost5.Size = new System.Drawing.Size(73, 14);
			this.lblPost5.TabIndex = 25;
			this.lblPost5.Text = "Trigger +5";
			//
			// _lblPreTrig_4
			//
			this._lblPreTrig_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_4.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_4.Location = new System.Drawing.Point(96, 148);
			this._lblPreTrig_4.Name = "_lblPreTrig_4";
			this._lblPreTrig_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_4.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_4.TabIndex = 13;
			this._lblPreTrig_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre6
			//
			this.lblPre6.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre6.Location = new System.Drawing.Point(18, 147);
			this.lblPre6.Name = "lblPre6";
			this.lblPre6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre6.Size = new System.Drawing.Size(73, 14);
			this.lblPre6.TabIndex = 5;
			this.lblPre6.Text = "Trigger -6";
			//
			// _lblPostTrig_4
			//
			this._lblPostTrig_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_4.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_4.Location = new System.Drawing.Point(277, 134);
			this._lblPostTrig_4.Name = "_lblPostTrig_4";
			this._lblPostTrig_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_4.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_4.TabIndex = 36;
			this._lblPostTrig_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost4
			//
			this.lblPost4.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost4.Location = new System.Drawing.Point(198, 134);
			this.lblPost4.Name = "lblPost4";
			this.lblPost4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost4.Size = new System.Drawing.Size(73, 14);
			this.lblPost4.TabIndex = 35;
			this.lblPost4.Text = "Trigger +4";
			//
			// _lblPreTrig_3
			//
			this._lblPreTrig_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_3.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_3.Location = new System.Drawing.Point(96, 135);
			this._lblPreTrig_3.Name = "_lblPreTrig_3";
			this._lblPreTrig_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_3.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_3.TabIndex = 12;
			this._lblPreTrig_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre7
			//
			this.lblPre7.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre7.Location = new System.Drawing.Point(18, 134);
			this.lblPre7.Name = "lblPre7";
			this.lblPre7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre7.Size = new System.Drawing.Size(73, 14);
			this.lblPre7.TabIndex = 4;
			this.lblPre7.Text = "Trigger -7";
			//
			// _lblPostTrig_3
			//
			this._lblPostTrig_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_3.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_3.Location = new System.Drawing.Point(277, 122);
			this._lblPostTrig_3.Name = "_lblPostTrig_3";
			this._lblPostTrig_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_3.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_3.TabIndex = 32;
			this._lblPostTrig_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost3
			//
			this.lblPost3.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost3.Location = new System.Drawing.Point(198, 122);
			this.lblPost3.Name = "lblPost3";
			this.lblPost3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost3.Size = new System.Drawing.Size(73, 14);
			this.lblPost3.TabIndex = 31;
			this.lblPost3.Text = "Trigger +3";
			//
			// _lblPreTrig_2
			//
			this._lblPreTrig_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_2.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_2.Location = new System.Drawing.Point(96, 122);
			this._lblPreTrig_2.Name = "_lblPreTrig_2";
			this._lblPreTrig_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_2.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_2.TabIndex = 11;
			this._lblPreTrig_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre8
			//
			this.lblPre8.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre8.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre8.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre8.Location = new System.Drawing.Point(18, 122);
			this.lblPre8.Name = "lblPre8";
			this.lblPre8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre8.Size = new System.Drawing.Size(73, 14);
			this.lblPre8.TabIndex = 3;
			this.lblPre8.Text = "Trigger -8";
			//
			// _lblPostTrig_2
			//
			this._lblPostTrig_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_2.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_2.Location = new System.Drawing.Point(277, 109);
			this._lblPostTrig_2.Name = "_lblPostTrig_2";
			this._lblPostTrig_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_2.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_2.TabIndex = 28;
			this._lblPostTrig_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost2
			//
			this.lblPost2.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost2.Location = new System.Drawing.Point(198, 109);
			this.lblPost2.Name = "lblPost2";
			this.lblPost2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost2.Size = new System.Drawing.Size(73, 14);
			this.lblPost2.TabIndex = 27;
			this.lblPost2.Text = "Trigger +2";
			//
			// _lblPreTrig_1
			//
			this._lblPreTrig_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_1.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_1.Location = new System.Drawing.Point(96, 109);
			this._lblPreTrig_1.Name = "_lblPreTrig_1";
			this._lblPreTrig_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_1.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_1.TabIndex = 10;
			this._lblPreTrig_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre9
			//
			this.lblPre9.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre9.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre9.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre9.Location = new System.Drawing.Point(18, 109);
			this.lblPre9.Name = "lblPre9";
			this.lblPre9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre9.Size = new System.Drawing.Size(73, 14);
			this.lblPre9.TabIndex = 2;
			this.lblPre9.Text = "Trigger -9";
			//
			// _lblPostTrig_1
			//
			this._lblPostTrig_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblPostTrig_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPostTrig_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPostTrig_1.ForeColor = System.Drawing.Color.Blue;
			this._lblPostTrig_1.Location = new System.Drawing.Point(277, 96);
			this._lblPostTrig_1.Name = "_lblPostTrig_1";
			this._lblPostTrig_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPostTrig_1.Size = new System.Drawing.Size(65, 14);
			this._lblPostTrig_1.TabIndex = 24;
			this._lblPostTrig_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPost1
			//
			this.lblPost1.BackColor = System.Drawing.SystemColors.Window;
			this.lblPost1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPost1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPost1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPost1.Location = new System.Drawing.Point(198, 96);
			this.lblPost1.Name = "lblPost1";
			this.lblPost1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPost1.Size = new System.Drawing.Size(73, 14);
			this.lblPost1.TabIndex = 23;
			this.lblPost1.Text = "Trigger +1";
			//
			// _lblPreTrig_0
			//
			this._lblPreTrig_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblPreTrig_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblPreTrig_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblPreTrig_0.ForeColor = System.Drawing.Color.Blue;
			this._lblPreTrig_0.Location = new System.Drawing.Point(96, 96);
			this._lblPreTrig_0.Name = "_lblPreTrig_0";
			this._lblPreTrig_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblPreTrig_0.Size = new System.Drawing.Size(65, 14);
			this._lblPreTrig_0.TabIndex = 9;
			this._lblPreTrig_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblPre10
			//
			this.lblPre10.BackColor = System.Drawing.SystemColors.Window;
			this.lblPre10.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPre10.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPre10.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPre10.Location = new System.Drawing.Point(18, 96);
			this.lblPre10.Name = "lblPre10";
			this.lblPre10.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPre10.Size = new System.Drawing.Size(73, 14);
			this.lblPre10.TabIndex = 1;
			this.lblPre10.Text = "Trigger -10";
			//
			// lblPostTrigData
			//
			this.lblPostTrigData.BackColor = System.Drawing.SystemColors.Window;
			this.lblPostTrigData.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPostTrigData.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPostTrigData.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPostTrigData.Location = new System.Drawing.Point(192, 77);
			this.lblPostTrigData.Name = "lblPostTrigData";
			this.lblPostTrigData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPostTrigData.Size = new System.Drawing.Size(164, 14);
			this.lblPostTrigData.TabIndex = 44;
			this.lblPostTrigData.Text = "Data acquired after trigger";
			//
			// lblPreTrigData
			//
			this.lblPreTrigData.BackColor = System.Drawing.SystemColors.Window;
			this.lblPreTrigData.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPreTrigData.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPreTrigData.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPreTrigData.Location = new System.Drawing.Point(13, 77);
			this.lblPreTrigData.Name = "lblPreTrigData";
			this.lblPreTrigData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPreTrigData.Size = new System.Drawing.Size(161, 14);
			this.lblPreTrigData.TabIndex = 43;
			this.lblPreTrigData.Text = "Data acquired before trigger";
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(8, 0);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(361, 22);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.APreTrig()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmPreTrig
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(375, 272);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdQuit, this.cmdTrigEnable, this.frmInstruct, this._lblPostTrig_10, this.lblPost10, this._lblPreTrig_9, this.lblPre1, this._lblPostTrig_9, this.lblPost9, this._lblPreTrig_8, this.lblPre2, this._lblPostTrig_8, this.lblPost8, this._lblPreTrig_7, this.lblPre3, this._lblPostTrig_7, this.lblPost7, this._lblPreTrig_6, this.lblPre4, this._lblPostTrig_6, this.lblPost6, this._lblPreTrig_5, this.lblPre5, this._lblPostTrig_5, this.lblPost5, this._lblPreTrig_4, this.lblPre6, this._lblPostTrig_4, this.lblPost4, this._lblPreTrig_3, this.lblPre7, this._lblPostTrig_3, this.lblPost3, this._lblPreTrig_2, this.lblPre8, this._lblPostTrig_2, this.lblPost2, this._lblPreTrig_1, this.lblPre9, this._lblPostTrig_1, this.lblPost1, this._lblPreTrig_0, this.lblPre10, this.lblPostTrigData, this.lblPreTrigData, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmPreTrig";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Analog Input Scan";
			this.frmInstruct.ResumeLayout(false);
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmPreTrig());
		}
	    
    

		private void cmdLevelOK_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdLevelOK.Click */
		{
			cmdTrigEnable.Enabled = true;
			cmdLevelOK.Visible = false;
			lblInstruct.ForeColor = System.Drawing.ColorTranslator.FromOle(0XFF0000);
			lblInstruct.Text = "Click 'Enable Trigger' when ready...";
		}


		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) 
		{
			//  Free up memory for use by other applications
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			MemHandle = 0;

			Application.Exit();
		}


		private void cmdTrigEnable_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdTrigEnable.Click */
		{
			short i;
			MccDaq.ErrorInfo ULStat;
			MccDaq.ScanOptions Options;
			MccDaq.Range Range;
			int Rate;
			int HighChan;
			int LowChan;

			lblInstruct.Text = "Waiting for trigger.";
			Application.DoEvents();

			//  Monitor a range of channels for a trigger then collect the values
			//  with MccDaq.MccBoard.APretrig()
			//  Parameters:
			//    LowChan       :first A/D channel of the scan
			//    HighChan      :last A/D channel of the scan
			//    PretrigCount  :number of pre-trigger A/D samples to collect
			//    TotalCount    :total number of A/D samples to collect
			//    Rate          :sample rate in samples per second
			//    Range         :the range for the board
			//    MemHandle     :Handle for Windows buffer to store data in
			//    Options       :data collection options
			LowChan = 0;
			HighChan = 0;
			int preCount = PretrigCount;
			int totCount = TotalCount;
			Rate = 1000;								//  per channel sampling rate ((samples per second) per channel)
			Range = MccDaq.Range.Bip5Volts;				//  set the range
			Options = MccDaq.ScanOptions.ConvertData;	//  return data as 12-bit values aligned with oldest 
														//  data first
			ULStat = DaqBoard.APretrig( LowChan, HighChan, ref preCount, ref totCount, ref Rate, Range, MemHandle, Options);
			

			//  Transfer the data from the memory buffer set up by Windows to an array
			ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out ADData[0], FirstPoint, NumPoints);
			

			for (i=0; i<=PretrigCount - 1; ++i)
				lblPreTrig[i].Text = ADData[i].ToString("D");
	      
			for (i=0; i<=9; ++i)
				lblPostTrig[i].Text = ADData[PretrigCount + i].ToString("D");
	   
			cmdTrigEnable.Enabled = false;
			lblInstruct.Text = "Make sure that the trigger input is at a low level before starting.";
			lblInstruct.ForeColor = System.Drawing.ColorTranslator.FromOle(0XFF);
			cmdLevelOK.Visible = true;
		}

	}
}