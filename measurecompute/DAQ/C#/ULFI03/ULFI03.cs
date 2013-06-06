// ==============================================================================
//
//  File:                         ULFI03.CS
//
//  Library Call Demonstrated:    File Operations:
//                                Mccdaq.MccBoard.FilePretrig()
//                                MccDaq.MccService.FileRead()
//                                MccDaq.MccService.FileGetInfo()
//
//  Purpose:                      Stream data continuously to a streamer file
//                                until a trigger is received, continue data
//                                streaming until total number of samples minus
//                                the number of pretrigger samples is reached.
//
//  Demonstration:                Creates a file and scans analog data to the
//                                file continuously, overwriting previous data.
//                                When a trigger is received, acquisition stops
//                                after (TotalCount& - PreTrigCount&) samples
//                                are stored. Displays the data in the file and
//                                the information in the file header. Prints
//                                data from PreTrigger-10 to PreTrigger+10.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must be capable of MccDaq.ScanOption.BlockIo.
//                                
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

namespace ULFI03
{
	public class frmFilePreTrig : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public TextBox txtFileName;
		public Button cmdQuit;
		public Button cmdTrigEnable;
		public Button cmdLevelOK;
		public Label lblInstruct;
		public GroupBox fraInstruct;
		public Label lblFileInstruct;
		public Label lblShowGain;
		public Label lblGain;
		public Label lblShowRate;
		public Label lblRate;
		public Label lblShowNumSam;
		public Label lblNumSam;
		public Label lblShowPT;
		public Label lblNumPTSam;
		public Label lblShowHiChan;
		public Label lblHiChan;
		public Label lblShowLoChan;
		public Label lblLoChan;
		public Label lblShowFileName;
		public Label lblFileName;
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
		public Label _lblPostTrig_2;
		public Label lblPost3;
		public Label _lblPreTrig_2;
		public Label lblPre8;
		public Label _lblPostTrig_3;
		public Label lblPost2;
		public Label _lblPreTrig_1;
		public Label lblPre9;
		public Label _lblPostTrig_1;
		public Label lblPost1;
		public Label _lblPreTrig_0;
		public Label lblPre10;
		public Label _lblPostTrig_0;
		public Label lblPostTrigData;
		public Label lblPreTrigData;
		public Label lblDemoFunction;

		public Label[] lblPreTrig;
		public Label[] lblPostTrig;

		private MccDaq.MccBoard DaqBoard;
		const int TestPoints = 128000; //  Number of data points to collect
		const int BufSize = TestPoints + 512; //  set buffer size large enough to hold all data
	 
		public frmFilePreTrig()
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

			lblPreTrig = (new Label[]{_lblPreTrig_0, _lblPreTrig_1, _lblPreTrig_2, _lblPreTrig_3, _lblPreTrig_4,
									  _lblPreTrig_5, _lblPreTrig_6, _lblPreTrig_7, _lblPreTrig_8, _lblPreTrig_9});

			lblPostTrig = (new Label[]{_lblPostTrig_0, _lblPostTrig_1, _lblPostTrig_2, _lblPostTrig_3, _lblPostTrig_4, 
										  _lblPostTrig_5, _lblPostTrig_6, _lblPostTrig_7, _lblPostTrig_8, _lblPostTrig_9,
										_lblPostTrig_10});

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
		this.txtFileName = new System.Windows.Forms.TextBox();
		this.cmdQuit = new System.Windows.Forms.Button();
		this.cmdTrigEnable = new System.Windows.Forms.Button();
		this.fraInstruct = new System.Windows.Forms.GroupBox();
		this.cmdLevelOK = new System.Windows.Forms.Button();
		this.lblInstruct = new System.Windows.Forms.Label();
		this.lblFileInstruct = new System.Windows.Forms.Label();
		this.lblShowGain = new System.Windows.Forms.Label();
		this.lblGain = new System.Windows.Forms.Label();
		this.lblShowRate = new System.Windows.Forms.Label();
		this.lblRate = new System.Windows.Forms.Label();
		this.lblShowNumSam = new System.Windows.Forms.Label();
		this.lblNumSam = new System.Windows.Forms.Label();
		this.lblShowPT = new System.Windows.Forms.Label();
		this.lblNumPTSam = new System.Windows.Forms.Label();
		this.lblShowHiChan = new System.Windows.Forms.Label();
		this.lblHiChan = new System.Windows.Forms.Label();
		this.lblShowLoChan = new System.Windows.Forms.Label();
		this.lblLoChan = new System.Windows.Forms.Label();
		this.lblShowFileName = new System.Windows.Forms.Label();
		this.lblFileName = new System.Windows.Forms.Label();
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
		this._lblPostTrig_2 = new System.Windows.Forms.Label();
		this.lblPost3 = new System.Windows.Forms.Label();
		this._lblPreTrig_2 = new System.Windows.Forms.Label();
		this.lblPre8 = new System.Windows.Forms.Label();
		this._lblPostTrig_3 = new System.Windows.Forms.Label();
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
		this.fraInstruct.SuspendLayout();
		this.SuspendLayout();
		// 
		// txtFileName
		// 
		this.txtFileName.AcceptsReturn = true;
		this.txtFileName.AutoSize = false;
		this.txtFileName.BackColor = System.Drawing.SystemColors.Window;
		this.txtFileName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.txtFileName.Cursor = System.Windows.Forms.Cursors.IBeam;
		this.txtFileName.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.txtFileName.ForeColor = System.Drawing.SystemColors.WindowText;
		this.txtFileName.Location = new System.Drawing.Point(184, 348);
		this.txtFileName.MaxLength = 0;
		this.txtFileName.Name = "txtFileName";
		this.txtFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.txtFileName.Size = new System.Drawing.Size(161, 25);
		this.txtFileName.TabIndex = 63;
		this.txtFileName.Text = "DEMO.DAT";
		// 
		// cmdQuit
		// 
		this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
		this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdQuit.Location = new System.Drawing.Point(312, 296);
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
		this.cmdTrigEnable.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdTrigEnable.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdTrigEnable.Location = new System.Drawing.Point(288, 40);
		this.cmdTrigEnable.Name = "cmdTrigEnable";
		this.cmdTrigEnable.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdTrigEnable.Size = new System.Drawing.Size(97, 26);
		this.cmdTrigEnable.TabIndex = 18;
		this.cmdTrigEnable.Text = "Enable Trigger";
		this.cmdTrigEnable.Click += new System.EventHandler(this.cmdTrigEnable_Click);
		// 
		// fraInstruct
		// 
		this.fraInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.fraInstruct.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.cmdLevelOK,
																					this.lblInstruct});
		this.fraInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.fraInstruct.ForeColor = System.Drawing.SystemColors.WindowText;
		this.fraInstruct.Location = new System.Drawing.Point(8, 24);
		this.fraInstruct.Name = "fraInstruct";
		this.fraInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.fraInstruct.Size = new System.Drawing.Size(273, 49);
		this.fraInstruct.TabIndex = 45;
		this.fraInstruct.TabStop = false;
		// 
		// cmdLevelOK
		// 
		this.cmdLevelOK.BackColor = System.Drawing.SystemColors.Control;
		this.cmdLevelOK.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdLevelOK.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdLevelOK.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdLevelOK.Location = new System.Drawing.Point(232, 16);
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
		this.lblInstruct.Location = new System.Drawing.Point(8, 16);
		this.lblInstruct.Name = "lblInstruct";
		this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct.Size = new System.Drawing.Size(217, 25);
		this.lblInstruct.TabIndex = 46;
		this.lblInstruct.Text = "Make sure that the trigger input is at a low level before starting.";
		this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblFileInstruct
		// 
		this.lblFileInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.lblFileInstruct.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblFileInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblFileInstruct.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblFileInstruct.Location = new System.Drawing.Point(8, 332);
		this.lblFileInstruct.Name = "lblFileInstruct";
		this.lblFileInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblFileInstruct.Size = new System.Drawing.Size(169, 41);
		this.lblFileInstruct.TabIndex = 62;
		this.lblFileInstruct.Text = "Enter the name of the file that you have created using MAKESTRM.EXE";
		this.lblFileInstruct.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowGain
		// 
		this.lblShowGain.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowGain.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowGain.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowGain.ForeColor = System.Drawing.Color.Blue;
		this.lblShowGain.Location = new System.Drawing.Point(181, 314);
		this.lblShowGain.Name = "lblShowGain";
		this.lblShowGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowGain.Size = new System.Drawing.Size(52, 14);
		this.lblShowGain.TabIndex = 61;
		// 
		// lblGain
		// 
		this.lblGain.BackColor = System.Drawing.SystemColors.Window;
		this.lblGain.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblGain.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblGain.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblGain.Location = new System.Drawing.Point(46, 314);
		this.lblGain.Name = "lblGain";
		this.lblGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblGain.Size = new System.Drawing.Size(129, 14);
		this.lblGain.TabIndex = 54;
		this.lblGain.Text = "Gain:";
		this.lblGain.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowRate
		// 
		this.lblShowRate.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowRate.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowRate.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowRate.ForeColor = System.Drawing.Color.Blue;
		this.lblShowRate.Location = new System.Drawing.Point(181, 301);
		this.lblShowRate.Name = "lblShowRate";
		this.lblShowRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowRate.Size = new System.Drawing.Size(52, 14);
		this.lblShowRate.TabIndex = 60;
		// 
		// lblRate
		// 
		this.lblRate.BackColor = System.Drawing.SystemColors.Window;
		this.lblRate.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblRate.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblRate.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblRate.Location = new System.Drawing.Point(46, 301);
		this.lblRate.Name = "lblRate";
		this.lblRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblRate.Size = new System.Drawing.Size(129, 14);
		this.lblRate.TabIndex = 53;
		this.lblRate.Text = "Collection Rate:";
		this.lblRate.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowNumSam
		// 
		this.lblShowNumSam.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowNumSam.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowNumSam.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowNumSam.ForeColor = System.Drawing.Color.Blue;
		this.lblShowNumSam.Location = new System.Drawing.Point(181, 288);
		this.lblShowNumSam.Name = "lblShowNumSam";
		this.lblShowNumSam.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowNumSam.Size = new System.Drawing.Size(52, 14);
		this.lblShowNumSam.TabIndex = 59;
		// 
		// lblNumSam
		// 
		this.lblNumSam.BackColor = System.Drawing.SystemColors.Window;
		this.lblNumSam.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblNumSam.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblNumSam.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblNumSam.Location = new System.Drawing.Point(46, 288);
		this.lblNumSam.Name = "lblNumSam";
		this.lblNumSam.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblNumSam.Size = new System.Drawing.Size(129, 14);
		this.lblNumSam.TabIndex = 52;
		this.lblNumSam.Text = "No. of Samples:";
		this.lblNumSam.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowPT
		// 
		this.lblShowPT.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowPT.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowPT.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowPT.ForeColor = System.Drawing.Color.Blue;
		this.lblShowPT.Location = new System.Drawing.Point(181, 275);
		this.lblShowPT.Name = "lblShowPT";
		this.lblShowPT.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowPT.Size = new System.Drawing.Size(52, 14);
		this.lblShowPT.TabIndex = 58;
		// 
		// lblNumPTSam
		// 
		this.lblNumPTSam.BackColor = System.Drawing.SystemColors.Window;
		this.lblNumPTSam.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblNumPTSam.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblNumPTSam.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblNumPTSam.Location = new System.Drawing.Point(30, 275);
		this.lblNumPTSam.Name = "lblNumPTSam";
		this.lblNumPTSam.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblNumPTSam.Size = new System.Drawing.Size(145, 14);
		this.lblNumPTSam.TabIndex = 51;
		this.lblNumPTSam.Text = "No. of Pretrig Samples:";
		this.lblNumPTSam.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowHiChan
		// 
		this.lblShowHiChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowHiChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowHiChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowHiChan.ForeColor = System.Drawing.Color.Blue;
		this.lblShowHiChan.Location = new System.Drawing.Point(181, 262);
		this.lblShowHiChan.Name = "lblShowHiChan";
		this.lblShowHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowHiChan.Size = new System.Drawing.Size(52, 14);
		this.lblShowHiChan.TabIndex = 57;
		// 
		// lblHiChan
		// 
		this.lblHiChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblHiChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblHiChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblHiChan.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblHiChan.Location = new System.Drawing.Point(46, 262);
		this.lblHiChan.Name = "lblHiChan";
		this.lblHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblHiChan.Size = new System.Drawing.Size(129, 14);
		this.lblHiChan.TabIndex = 50;
		this.lblHiChan.Text = "High Channel:";
		this.lblHiChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowLoChan
		// 
		this.lblShowLoChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowLoChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowLoChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowLoChan.ForeColor = System.Drawing.Color.Blue;
		this.lblShowLoChan.Location = new System.Drawing.Point(181, 250);
		this.lblShowLoChan.Name = "lblShowLoChan";
		this.lblShowLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowLoChan.Size = new System.Drawing.Size(52, 14);
		this.lblShowLoChan.TabIndex = 56;
		// 
		// lblLoChan
		// 
		this.lblLoChan.BackColor = System.Drawing.SystemColors.Window;
		this.lblLoChan.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblLoChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblLoChan.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblLoChan.Location = new System.Drawing.Point(46, 250);
		this.lblLoChan.Name = "lblLoChan";
		this.lblLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblLoChan.Size = new System.Drawing.Size(129, 14);
		this.lblLoChan.TabIndex = 49;
		this.lblLoChan.Text = "Low Channel:";
		this.lblLoChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// lblShowFileName
		// 
		this.lblShowFileName.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowFileName.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowFileName.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowFileName.ForeColor = System.Drawing.Color.Blue;
		this.lblShowFileName.Location = new System.Drawing.Point(181, 237);
		this.lblShowFileName.Name = "lblShowFileName";
		this.lblShowFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowFileName.Size = new System.Drawing.Size(183, 14);
		this.lblShowFileName.TabIndex = 55;
		// 
		// lblFileName
		// 
		this.lblFileName.BackColor = System.Drawing.SystemColors.Window;
		this.lblFileName.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblFileName.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblFileName.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblFileName.Location = new System.Drawing.Point(46, 237);
		this.lblFileName.Name = "lblFileName";
		this.lblFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblFileName.Size = new System.Drawing.Size(129, 14);
		this.lblFileName.TabIndex = 48;
		this.lblFileName.Text = "Streamer File Name:";
		this.lblFileName.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// _lblPostTrig_10
		// 
		this._lblPostTrig_10.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_10.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_10.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_10.Location = new System.Drawing.Point(296, 204);
		this._lblPostTrig_10.Name = "_lblPostTrig_10";
		this._lblPostTrig_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_10.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_10.TabIndex = 42;
		this._lblPostTrig_10.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost10
		// 
		this.lblPost10.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost10.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost10.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost10.Location = new System.Drawing.Point(216, 204);
		this.lblPost10.Name = "lblPost10";
		this.lblPost10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost10.Size = new System.Drawing.Size(73, 13);
		this.lblPost10.TabIndex = 40;
		this.lblPost10.Text = "Trigger +10";
		// 
		// _lblPreTrig_9
		// 
		this._lblPreTrig_9.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_9.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_9.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_9.Location = new System.Drawing.Point(96, 204);
		this._lblPreTrig_9.Name = "_lblPreTrig_9";
		this._lblPreTrig_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_9.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_9.TabIndex = 22;
		this._lblPreTrig_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre1
		// 
		this.lblPre1.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre1.Location = new System.Drawing.Point(24, 204);
		this.lblPre1.Name = "lblPre1";
		this.lblPre1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre1.Size = new System.Drawing.Size(73, 13);
		this.lblPre1.TabIndex = 20;
		this.lblPre1.Text = "Trigger -1";
		// 
		// _lblPostTrig_9
		// 
		this._lblPostTrig_9.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_9.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_9.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_9.Location = new System.Drawing.Point(296, 192);
		this._lblPostTrig_9.Name = "_lblPostTrig_9";
		this._lblPostTrig_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_9.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_9.TabIndex = 41;
		this._lblPostTrig_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost9
		// 
		this.lblPost9.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost9.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost9.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost9.Location = new System.Drawing.Point(216, 192);
		this.lblPost9.Name = "lblPost9";
		this.lblPost9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost9.Size = new System.Drawing.Size(73, 17);
		this.lblPost9.TabIndex = 39;
		this.lblPost9.Text = "Trigger +9";
		// 
		// _lblPreTrig_8
		// 
		this._lblPreTrig_8.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_8.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_8.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_8.Location = new System.Drawing.Point(96, 192);
		this._lblPreTrig_8.Name = "_lblPreTrig_8";
		this._lblPreTrig_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_8.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_8.TabIndex = 21;
		this._lblPreTrig_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre2
		// 
		this.lblPre2.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre2.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre2.Location = new System.Drawing.Point(24, 192);
		this.lblPre2.Name = "lblPre2";
		this.lblPre2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre2.Size = new System.Drawing.Size(73, 13);
		this.lblPre2.TabIndex = 19;
		this.lblPre2.Text = "Trigger -2";
		// 
		// _lblPostTrig_8
		// 
		this._lblPostTrig_8.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_8.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_8.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_8.Location = new System.Drawing.Point(296, 180);
		this._lblPostTrig_8.Name = "_lblPostTrig_8";
		this._lblPostTrig_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_8.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_8.TabIndex = 38;
		this._lblPostTrig_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost8
		// 
		this.lblPost8.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost8.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost8.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost8.Location = new System.Drawing.Point(216, 180);
		this.lblPost8.Name = "lblPost8";
		this.lblPost8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost8.Size = new System.Drawing.Size(73, 13);
		this.lblPost8.TabIndex = 37;
		this.lblPost8.Text = "Trigger +8";
		// 
		// _lblPreTrig_7
		// 
		this._lblPreTrig_7.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_7.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_7.Location = new System.Drawing.Point(96, 180);
		this._lblPreTrig_7.Name = "_lblPreTrig_7";
		this._lblPreTrig_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_7.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_7.TabIndex = 16;
		this._lblPreTrig_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre3
		// 
		this.lblPre3.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre3.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre3.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre3.Location = new System.Drawing.Point(24, 180);
		this.lblPre3.Name = "lblPre3";
		this.lblPre3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre3.Size = new System.Drawing.Size(73, 13);
		this.lblPre3.TabIndex = 8;
		this.lblPre3.Text = "Trigger -3";
		// 
		// _lblPostTrig_7
		// 
		this._lblPostTrig_7.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_7.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_7.Location = new System.Drawing.Point(296, 168);
		this._lblPostTrig_7.Name = "_lblPostTrig_7";
		this._lblPostTrig_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_7.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_7.TabIndex = 34;
		this._lblPostTrig_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost7
		// 
		this.lblPost7.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost7.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost7.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost7.Location = new System.Drawing.Point(216, 168);
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
		this._lblPreTrig_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_6.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_6.Location = new System.Drawing.Point(96, 168);
		this._lblPreTrig_6.Name = "_lblPreTrig_6";
		this._lblPreTrig_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_6.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_6.TabIndex = 15;
		this._lblPreTrig_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre4
		// 
		this.lblPre4.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre4.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre4.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre4.Location = new System.Drawing.Point(24, 168);
		this.lblPre4.Name = "lblPre4";
		this.lblPre4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre4.Size = new System.Drawing.Size(73, 13);
		this.lblPre4.TabIndex = 7;
		this.lblPre4.Text = "Trigger -4";
		// 
		// _lblPostTrig_6
		// 
		this._lblPostTrig_6.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_6.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_6.Location = new System.Drawing.Point(296, 156);
		this._lblPostTrig_6.Name = "_lblPostTrig_6";
		this._lblPostTrig_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_6.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_6.TabIndex = 30;
		this._lblPostTrig_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost6
		// 
		this.lblPost6.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost6.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost6.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost6.Location = new System.Drawing.Point(216, 156);
		this.lblPost6.Name = "lblPost6";
		this.lblPost6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost6.Size = new System.Drawing.Size(73, 13);
		this.lblPost6.TabIndex = 29;
		this.lblPost6.Text = "Trigger +6";
		// 
		// _lblPreTrig_5
		// 
		this._lblPreTrig_5.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_5.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_5.Location = new System.Drawing.Point(96, 156);
		this._lblPreTrig_5.Name = "_lblPreTrig_5";
		this._lblPreTrig_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_5.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_5.TabIndex = 14;
		this._lblPreTrig_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre5
		// 
		this.lblPre5.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre5.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre5.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre5.Location = new System.Drawing.Point(24, 156);
		this.lblPre5.Name = "lblPre5";
		this.lblPre5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre5.Size = new System.Drawing.Size(73, 13);
		this.lblPre5.TabIndex = 6;
		this.lblPre5.Text = "Trigger -5";
		// 
		// _lblPostTrig_5
		// 
		this._lblPostTrig_5.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_5.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_5.Location = new System.Drawing.Point(296, 144);
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
		this.lblPost5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost5.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost5.Location = new System.Drawing.Point(216, 144);
		this.lblPost5.Name = "lblPost5";
		this.lblPost5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost5.Size = new System.Drawing.Size(73, 13);
		this.lblPost5.TabIndex = 25;
		this.lblPost5.Text = "Trigger +5";
		// 
		// _lblPreTrig_4
		// 
		this._lblPreTrig_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_4.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_4.Location = new System.Drawing.Point(96, 144);
		this._lblPreTrig_4.Name = "_lblPreTrig_4";
		this._lblPreTrig_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_4.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_4.TabIndex = 13;
		this._lblPreTrig_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre6
		// 
		this.lblPre6.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre6.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre6.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre6.Location = new System.Drawing.Point(24, 144);
		this.lblPre6.Name = "lblPre6";
		this.lblPre6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre6.Size = new System.Drawing.Size(73, 13);
		this.lblPre6.TabIndex = 5;
		this.lblPre6.Text = "Trigger -6";
		// 
		// _lblPostTrig_4
		// 
		this._lblPostTrig_4.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_4.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_4.Location = new System.Drawing.Point(296, 132);
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
		this.lblPost4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost4.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost4.Location = new System.Drawing.Point(216, 132);
		this.lblPost4.Name = "lblPost4";
		this.lblPost4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost4.Size = new System.Drawing.Size(73, 13);
		this.lblPost4.TabIndex = 35;
		this.lblPost4.Text = "Trigger +4";
		// 
		// _lblPreTrig_3
		// 
		this._lblPreTrig_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_3.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_3.Location = new System.Drawing.Point(96, 132);
		this._lblPreTrig_3.Name = "_lblPreTrig_3";
		this._lblPreTrig_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_3.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_3.TabIndex = 12;
		this._lblPreTrig_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre7
		// 
		this.lblPre7.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre7.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre7.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre7.Location = new System.Drawing.Point(24, 132);
		this.lblPre7.Name = "lblPre7";
		this.lblPre7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre7.Size = new System.Drawing.Size(73, 13);
		this.lblPre7.TabIndex = 4;
		this.lblPre7.Text = "Trigger -7";
		// 
		// _lblPostTrig_2
		// 
		this._lblPostTrig_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_2.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_2.Location = new System.Drawing.Point(296, 120);
		this._lblPostTrig_2.Name = "_lblPostTrig_2";
		this._lblPostTrig_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_2.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_2.TabIndex = 28;
		this._lblPostTrig_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost3
		// 
		this.lblPost3.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost3.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost3.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost3.Location = new System.Drawing.Point(216, 120);
		this.lblPost3.Name = "lblPost3";
		this.lblPost3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost3.Size = new System.Drawing.Size(73, 13);
		this.lblPost3.TabIndex = 31;
		this.lblPost3.Text = "Trigger +3";
		// 
		// _lblPreTrig_2
		// 
		this._lblPreTrig_2.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_2.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_2.Location = new System.Drawing.Point(96, 120);
		this._lblPreTrig_2.Name = "_lblPreTrig_2";
		this._lblPreTrig_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_2.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_2.TabIndex = 11;
		this._lblPreTrig_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre8
		// 
		this.lblPre8.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre8.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre8.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre8.Location = new System.Drawing.Point(24, 120);
		this.lblPre8.Name = "lblPre8";
		this.lblPre8.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre8.Size = new System.Drawing.Size(73, 13);
		this.lblPre8.TabIndex = 3;
		this.lblPre8.Text = "Trigger -8";
		// 
		// _lblPostTrig_3
		// 
		this._lblPostTrig_3.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_3.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_3.Location = new System.Drawing.Point(296, 108);
		this._lblPostTrig_3.Name = "_lblPostTrig_3";
		this._lblPostTrig_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_3.Size = new System.Drawing.Size(65, 14);
		this._lblPostTrig_3.TabIndex = 32;
		this._lblPostTrig_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost2
		// 
		this.lblPost2.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost2.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost2.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost2.Location = new System.Drawing.Point(216, 108);
		this.lblPost2.Name = "lblPost2";
		this.lblPost2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost2.Size = new System.Drawing.Size(73, 13);
		this.lblPost2.TabIndex = 27;
		this.lblPost2.Text = "Trigger +2";
		// 
		// _lblPreTrig_1
		// 
		this._lblPreTrig_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_1.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_1.Location = new System.Drawing.Point(96, 108);
		this._lblPreTrig_1.Name = "_lblPreTrig_1";
		this._lblPreTrig_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_1.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_1.TabIndex = 10;
		this._lblPreTrig_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre9
		// 
		this.lblPre9.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre9.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre9.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre9.Location = new System.Drawing.Point(24, 108);
		this.lblPre9.Name = "lblPre9";
		this.lblPre9.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre9.Size = new System.Drawing.Size(73, 13);
		this.lblPre9.TabIndex = 2;
		this.lblPre9.Text = "Trigger -9";
		// 
		// _lblPostTrig_1
		// 
		this._lblPostTrig_1.BackColor = System.Drawing.SystemColors.Window;
		this._lblPostTrig_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPostTrig_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPostTrig_1.ForeColor = System.Drawing.Color.Blue;
		this._lblPostTrig_1.Location = new System.Drawing.Point(296, 96);
		this._lblPostTrig_1.Name = "_lblPostTrig_1";
		this._lblPostTrig_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPostTrig_1.Size = new System.Drawing.Size(65, 13);
		this._lblPostTrig_1.TabIndex = 24;
		this._lblPostTrig_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPost1
		// 
		this.lblPost1.BackColor = System.Drawing.SystemColors.Window;
		this.lblPost1.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPost1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPost1.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPost1.Location = new System.Drawing.Point(216, 96);
		this.lblPost1.Name = "lblPost1";
		this.lblPost1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPost1.Size = new System.Drawing.Size(73, 13);
		this.lblPost1.TabIndex = 23;
		this.lblPost1.Text = "Trigger +1";
		// 
		// _lblPreTrig_0
		// 
		this._lblPreTrig_0.BackColor = System.Drawing.SystemColors.Window;
		this._lblPreTrig_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._lblPreTrig_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._lblPreTrig_0.ForeColor = System.Drawing.Color.Blue;
		this._lblPreTrig_0.Location = new System.Drawing.Point(96, 96);
		this._lblPreTrig_0.Name = "_lblPreTrig_0";
		this._lblPreTrig_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._lblPreTrig_0.Size = new System.Drawing.Size(65, 13);
		this._lblPreTrig_0.TabIndex = 9;
		this._lblPreTrig_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblPre10
		// 
		this.lblPre10.BackColor = System.Drawing.SystemColors.Window;
		this.lblPre10.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPre10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblPre10.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblPre10.Location = new System.Drawing.Point(24, 96);
		this.lblPre10.Name = "lblPre10";
		this.lblPre10.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblPre10.Size = new System.Drawing.Size(73, 13);
		this.lblPre10.TabIndex = 1;
		this.lblPre10.Text = "Trigger -10";
		// 
		// lblPostTrigData
		// 
		this.lblPostTrigData.BackColor = System.Drawing.SystemColors.Window;
		this.lblPostTrigData.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblPostTrigData.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
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
		this.lblPreTrigData.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
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
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(22, 6);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(345, 22);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.FilePretrig()";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmFilePreTrig
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(390, 379);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.txtFileName,
																		this.cmdQuit,
																		this.cmdTrigEnable,
																		this.fraInstruct,
																		this.lblFileInstruct,
																		this.lblShowGain,
																		this.lblGain,
																		this.lblShowRate,
																		this.lblRate,
																		this.lblShowNumSam,
																		this.lblNumSam,
																		this.lblShowPT,
																		this.lblNumPTSam,
																		this.lblShowHiChan,
																		this.lblHiChan,
																		this.lblShowLoChan,
																		this.lblLoChan,
																		this.lblShowFileName,
																		this.lblFileName,
																		this._lblPostTrig_10,
																		this.lblPost10,
																		this._lblPreTrig_9,
																		this.lblPre1,
																		this._lblPostTrig_9,
																		this.lblPost9,
																		this._lblPreTrig_8,
																		this.lblPre2,
																		this._lblPostTrig_8,
																		this.lblPost8,
																		this._lblPreTrig_7,
																		this.lblPre3,
																		this._lblPostTrig_7,
																		this.lblPost7,
																		this._lblPreTrig_6,
																		this.lblPre4,
																		this._lblPostTrig_6,
																		this.lblPost6,
																		this._lblPreTrig_5,
																		this.lblPre5,
																		this._lblPostTrig_5,
																		this.lblPost5,
																		this._lblPreTrig_4,
																		this.lblPre6,
																		this._lblPostTrig_4,
																		this.lblPost4,
																		this._lblPreTrig_3,
																		this.lblPre7,
																		this._lblPostTrig_2,
																		this.lblPost3,
																		this._lblPreTrig_2,
																		this.lblPre8,
																		this._lblPostTrig_3,
																		this.lblPost2,
																		this._lblPreTrig_1,
																		this.lblPre9,
																		this._lblPostTrig_1,
																		this.lblPost1,
																		this._lblPreTrig_0,
																		this.lblPre10,
																		this.lblPostTrigData,
																		this.lblPreTrigData,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.Color.Blue;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmFilePreTrig";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Analog Input to File";
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
			Application.Run(new frmFilePreTrig());
		}
	   

		private void cmdLevelOK_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdLevelOK.Click */
		{
			cmdTrigEnable.Enabled = true;
			cmdLevelOK.Visible = false;
			lblInstruct.ForeColor = System.Drawing.ColorTranslator.FromOle(0XFF0000);
			lblInstruct.Text = "Click 'Enable Trigger' when ready...";
		}


		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdQuit.Click */
		{
			Application.Exit();
		}


		private void cmdTrigEnable_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdTrigEnable.Click */
		{
			lblInstruct.Text = "Waiting for trigger.";
			cmdTrigEnable.Enabled = false;
			Application.DoEvents();

			//  Monitor a range of channels for a trigger then collect the values
			//  with MccDaq.MccBoard.APretrig()
			//  Parameters:
			//    LowChan       :first A/D channel of the scan
			//    HighChan      :last A/D channel of the scan
			//    PretrigCount  :number of pre-trigger A/D samples to collect
			//    TotalCount    :total number of A/D samples to collect
			//    Rate          :per channel sampling rate ((samples per second) per channel)
			//    Gain          :the gain for the board
			//    Options       :data collection options
			int TotalCount = TestPoints;
			int PretrigCount = 200;
			string FileName = txtFileName.Text; //  it may be necessary to specify path here
			int Rate = 50000;
			short LowChan = 0;
			short HighChan = 0;
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.Default;
			MccDaq.Range Range = MccDaq.Range.Bip5Volts;			// set the range

			MccDaq.ErrorInfo ULStat = DaqBoard.FilePretrig( LowChan, HighChan, ref PretrigCount, ref TotalCount, ref Rate, Range, FileName, Options);
			
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.BadFileName)
			{
				MessageBox.Show( "Enter the name of the file to create or overwrite in text box.", "Bad File Name", 0);
				cmdTrigEnable.Enabled = true;
				txtFileName.Focus();
				return ;
			}
			

			//  show the information in the file header with MccDaq.MccService.FileGetInfo
			//   Parameters:
			//     FileName      :the filename containing the data
			//     LowChan       :first A/D channel of the scan
			//     HighChan      :last A/D channel of the scan
			//     PreTrigCount  :the number of pretrigger samples in the file
			//     Count         :the total number of A/D samples in the file
			//     Rate          :per channel sampling rate ((samples per second) per channel)
			//     Range         :the gain at which the samples were collected
			ULStat = MccDaq.MccService.FileGetInfo( FileName, out LowChan, out HighChan, out PretrigCount, out TotalCount, out Rate, out Range);
			


			lblShowFileName.Text = FileName;
			lblShowLoChan.Text = LowChan.ToString("0");
			lblShowHiChan.Text = HighChan.ToString("0");
			lblShowPT.Text = PretrigCount.ToString("0");
			lblShowNumSam.Text = TotalCount.ToString("0");
			lblShowRate.Text = Rate.ToString("0");
			lblShowGain.Text = Range.ToString();

			//  show the data using MccDaq.MccService.FileRead()
			//   Parameters:
			//     FileName      :the filename containing the data
			//     NumPoints     :the number of data values to read from the file
			//     FirstPoint    :index of the first data value to read
			//     DataBuffer()  :array to read data into
			int NumPoints = 20; //  read the first twenty data points
			int FirstPoint = PretrigCount - 10; //  start at the trigger - 10
			ushort[] DataBuffer = new ushort[NumPoints];
			ULStat = MccDaq.MccService.FileRead(FileName, FirstPoint,ref NumPoints,out DataBuffer[0]);

			for (int i=0; i<10; ++i)
				lblPreTrig[i].Text = DataBuffer[i].ToString("0");
		
			for (int i=1; i<=10; ++i)
				lblPostTrig[i].Text = DataBuffer[9 + i].ToString("0");
			
			cmdTrigEnable.Enabled = false;
			lblInstruct.Text = "Make sure that the trigger input is at a low level before starting.";
			lblInstruct.ForeColor = System.Drawing.ColorTranslator.FromOle(0XFF);
			cmdLevelOK.Visible = true;
			cmdTrigEnable.Enabled = true;

		}

	}
}