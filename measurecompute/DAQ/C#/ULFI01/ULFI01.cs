// ==============================================================================
//
//  File:                         ULFI01.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.FileAInScan()
//
//  Purpose:                      Scan a range of A/D channels and store the
//                                data in a disk file.
//
//  Demonstration:                Collects data points from one analog input
//                                channel and stores them in a file.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have an A/D converter.
//                                Analog signal on an input channel.
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

namespace ULFI01
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdStartAcq;
		public TextBox txtFileName;
		public Label lblFileInstruct;
		public Label lblReadFile;
		public Label lblShowFile;
		public Label lblFileName;
		public Label lblReadPreTrig;
		public Label lblShowPreTrig;
		public Label lblPreTrig;
		public Label lblReadTotal;
		public Label lblShowCount;
		public Label lblCount;
		public Label lblReadGain;
		public Label lblShowGain;
		public Label lblGain;
		public Label lblReadOptions;
		public Label lblShowOptions;
		public Label lblOptions;
		public Label lblReadHiChan;
		public Label lblShowHiChan;
		public Label lblHiChan;
		public Label lblReadLoChan;
		public Label lblShowLoChan;
		public Label lblLoChan;
		public Label lblReadRate;
		public Label lblShowRate;
		public Label lblRate;
		public Label lblInCol;
		public Label lblOutCol;
		public Label lblAcqStat;
		public Label lblDemoFunction;
		
		private MccDaq.MccBoard DaqBoard;
		const int NumPoints = 128000; //  Number of data points to collect


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
			this.txtFileName = new System.Windows.Forms.TextBox();
			this.lblFileInstruct = new System.Windows.Forms.Label();
			this.lblReadFile = new System.Windows.Forms.Label();
			this.lblShowFile = new System.Windows.Forms.Label();
			this.lblFileName = new System.Windows.Forms.Label();
			this.lblReadPreTrig = new System.Windows.Forms.Label();
			this.lblShowPreTrig = new System.Windows.Forms.Label();
			this.lblPreTrig = new System.Windows.Forms.Label();
			this.lblReadTotal = new System.Windows.Forms.Label();
			this.lblShowCount = new System.Windows.Forms.Label();
			this.lblCount = new System.Windows.Forms.Label();
			this.lblReadGain = new System.Windows.Forms.Label();
			this.lblShowGain = new System.Windows.Forms.Label();
			this.lblGain = new System.Windows.Forms.Label();
			this.lblReadOptions = new System.Windows.Forms.Label();
			this.lblShowOptions = new System.Windows.Forms.Label();
			this.lblOptions = new System.Windows.Forms.Label();
			this.lblReadHiChan = new System.Windows.Forms.Label();
			this.lblShowHiChan = new System.Windows.Forms.Label();
			this.lblHiChan = new System.Windows.Forms.Label();
			this.lblReadLoChan = new System.Windows.Forms.Label();
			this.lblShowLoChan = new System.Windows.Forms.Label();
			this.lblLoChan = new System.Windows.Forms.Label();
			this.lblReadRate = new System.Windows.Forms.Label();
			this.lblShowRate = new System.Windows.Forms.Label();
			this.lblRate = new System.Windows.Forms.Label();
			this.lblInCol = new System.Windows.Forms.Label();
			this.lblOutCol = new System.Windows.Forms.Label();
			this.lblAcqStat = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopConvert
			//
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Enabled = false;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(352, 272);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(46, 26);
			this.cmdStopConvert.TabIndex = 1;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Visible = false;
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			//
			// cmdStartAcq
			//
			this.cmdStartAcq.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartAcq.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartAcq.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartAcq.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartAcq.Location = new System.Drawing.Point(352, 272);
			this.cmdStartAcq.Name = "cmdStartAcq";
			this.cmdStartAcq.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartAcq.Size = new System.Drawing.Size(46, 26);
			this.cmdStartAcq.TabIndex = 2;
			this.cmdStartAcq.Text = "Start";
			this.cmdStartAcq.Click += new System.EventHandler(this.cmdStartAcq_Click);
			//
			// txtFileName
			//
			this.txtFileName.AcceptsReturn = true;
			this.txtFileName.AutoSize = false;
			this.txtFileName.BackColor = System.Drawing.SystemColors.Window;
			this.txtFileName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtFileName.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtFileName.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtFileName.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtFileName.Location = new System.Drawing.Point(184, 272);
			this.txtFileName.MaxLength = 0;
			this.txtFileName.Name = "txtFileName";
			this.txtFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtFileName.Size = new System.Drawing.Size(161, 25);
			this.txtFileName.TabIndex = 30;
			this.txtFileName.Text = "DEMO.DAT";
			//
			// lblFileInstruct
			//
			this.lblFileInstruct.BackColor = System.Drawing.SystemColors.Window;
			this.lblFileInstruct.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFileInstruct.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblFileInstruct.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFileInstruct.Location = new System.Drawing.Point(8, 248);
			this.lblFileInstruct.Name = "lblFileInstruct";
			this.lblFileInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFileInstruct.Size = new System.Drawing.Size(169, 41);
			this.lblFileInstruct.TabIndex = 31;
			this.lblFileInstruct.Text = "Enter the name of the file that you have created using MAKESTRM.EXE";
			this.lblFileInstruct.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadFile
			//
			this.lblReadFile.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadFile.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadFile.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadFile.ForeColor = System.Drawing.Color.Blue;
			this.lblReadFile.Location = new System.Drawing.Point(256, 216);
			this.lblReadFile.Name = "lblReadFile";
			this.lblReadFile.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadFile.Size = new System.Drawing.Size(119, 18);
			this.lblReadFile.TabIndex = 18;
			//
			// lblShowFile
			//
			this.lblShowFile.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowFile.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowFile.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowFile.ForeColor = System.Drawing.Color.Blue;
			this.lblShowFile.Location = new System.Drawing.Point(112, 216);
			this.lblShowFile.Name = "lblShowFile";
			this.lblShowFile.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowFile.Size = new System.Drawing.Size(111, 18);
			this.lblShowFile.TabIndex = 9;
			//
			// lblFileName
			//
			this.lblFileName.BackColor = System.Drawing.SystemColors.Window;
			this.lblFileName.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFileName.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblFileName.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFileName.Location = new System.Drawing.Point(32, 216);
			this.lblFileName.Name = "lblFileName";
			this.lblFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFileName.Size = new System.Drawing.Size(65, 17);
			this.lblFileName.TabIndex = 25;
			this.lblFileName.Text = "File Name:";
			this.lblFileName.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadPreTrig
			//
			this.lblReadPreTrig.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadPreTrig.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadPreTrig.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadPreTrig.ForeColor = System.Drawing.Color.Blue;
			this.lblReadPreTrig.Location = new System.Drawing.Point(256, 184);
			this.lblReadPreTrig.Name = "lblReadPreTrig";
			this.lblReadPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadPreTrig.Size = new System.Drawing.Size(63, 18);
			this.lblReadPreTrig.TabIndex = 12;
			//
			// lblShowPreTrig
			//
			this.lblShowPreTrig.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowPreTrig.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowPreTrig.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowPreTrig.ForeColor = System.Drawing.Color.Blue;
			this.lblShowPreTrig.Location = new System.Drawing.Point(112, 184);
			this.lblShowPreTrig.Name = "lblShowPreTrig";
			this.lblShowPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowPreTrig.Size = new System.Drawing.Size(121, 17);
			this.lblShowPreTrig.TabIndex = 29;
			//
			// lblPreTrig
			//
			this.lblPreTrig.BackColor = System.Drawing.SystemColors.Window;
			this.lblPreTrig.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPreTrig.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPreTrig.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPreTrig.Location = new System.Drawing.Point(0, 184);
			this.lblPreTrig.Name = "lblPreTrig";
			this.lblPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPreTrig.Size = new System.Drawing.Size(97, 17);
			this.lblPreTrig.TabIndex = 28;
			this.lblPreTrig.Text = "Pre-Trig Count:";
			this.lblPreTrig.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadTotal
			//
			this.lblReadTotal.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadTotal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadTotal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadTotal.ForeColor = System.Drawing.Color.Blue;
			this.lblReadTotal.Location = new System.Drawing.Point(256, 160);
			this.lblReadTotal.Name = "lblReadTotal";
			this.lblReadTotal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadTotal.Size = new System.Drawing.Size(63, 18);
			this.lblReadTotal.TabIndex = 11;
			//
			// lblShowCount
			//
			this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCount.Location = new System.Drawing.Point(112, 160);
			this.lblShowCount.Name = "lblShowCount";
			this.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowCount.Size = new System.Drawing.Size(63, 18);
			this.lblShowCount.TabIndex = 10;
			//
			// lblCount
			//
			this.lblCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCount.Location = new System.Drawing.Point(32, 160);
			this.lblCount.Name = "lblCount";
			this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCount.Size = new System.Drawing.Size(65, 17);
			this.lblCount.TabIndex = 24;
			this.lblCount.Text = "Count:";
			this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadGain
			//
			this.lblReadGain.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadGain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadGain.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadGain.ForeColor = System.Drawing.Color.Blue;
			this.lblReadGain.Location = new System.Drawing.Point(256, 144);
			this.lblReadGain.Name = "lblReadGain";
			this.lblReadGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadGain.Size = new System.Drawing.Size(55, 18);
			this.lblReadGain.TabIndex = 17;
			//
			// lblShowGain
			//
			this.lblShowGain.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowGain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowGain.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowGain.ForeColor = System.Drawing.Color.Blue;
			this.lblShowGain.Location = new System.Drawing.Point(112, 144);
			this.lblShowGain.Name = "lblShowGain";
			this.lblShowGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowGain.Size = new System.Drawing.Size(63, 18);
			this.lblShowGain.TabIndex = 8;
			//
			// lblGain
			//
			this.lblGain.BackColor = System.Drawing.SystemColors.Window;
			this.lblGain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblGain.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblGain.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblGain.Location = new System.Drawing.Point(32, 144);
			this.lblGain.Name = "lblGain";
			this.lblGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblGain.Size = new System.Drawing.Size(65, 17);
			this.lblGain.TabIndex = 23;
			this.lblGain.Text = "Gain:";
			this.lblGain.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadOptions
			//
			this.lblReadOptions.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadOptions.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadOptions.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadOptions.ForeColor = System.Drawing.Color.Blue;
			this.lblReadOptions.Location = new System.Drawing.Point(256, 128);
			this.lblReadOptions.Name = "lblReadOptions";
			this.lblReadOptions.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadOptions.Size = new System.Drawing.Size(63, 18);
			this.lblReadOptions.TabIndex = 16;
			//
			// lblShowOptions
			//
			this.lblShowOptions.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowOptions.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowOptions.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowOptions.ForeColor = System.Drawing.Color.Blue;
			this.lblShowOptions.Location = new System.Drawing.Point(112, 128);
			this.lblShowOptions.Name = "lblShowOptions";
			this.lblShowOptions.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowOptions.Size = new System.Drawing.Size(63, 18);
			this.lblShowOptions.TabIndex = 7;
			//
			// lblOptions
			//
			this.lblOptions.BackColor = System.Drawing.SystemColors.Window;
			this.lblOptions.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblOptions.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblOptions.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblOptions.Location = new System.Drawing.Point(32, 128);
			this.lblOptions.Name = "lblOptions";
			this.lblOptions.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblOptions.Size = new System.Drawing.Size(65, 17);
			this.lblOptions.TabIndex = 22;
			this.lblOptions.Text = "Options:";
			this.lblOptions.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadHiChan
			//
			this.lblReadHiChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadHiChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadHiChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadHiChan.ForeColor = System.Drawing.Color.Blue;
			this.lblReadHiChan.Location = new System.Drawing.Point(256, 112);
			this.lblReadHiChan.Name = "lblReadHiChan";
			this.lblReadHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadHiChan.Size = new System.Drawing.Size(55, 18);
			this.lblReadHiChan.TabIndex = 15;
			//
			// lblShowHiChan
			//
			this.lblShowHiChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowHiChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowHiChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowHiChan.ForeColor = System.Drawing.Color.Blue;
			this.lblShowHiChan.Location = new System.Drawing.Point(112, 112);
			this.lblShowHiChan.Name = "lblShowHiChan";
			this.lblShowHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowHiChan.Size = new System.Drawing.Size(63, 18);
			this.lblShowHiChan.TabIndex = 6;
			//
			// lblHiChan
			//
			this.lblHiChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblHiChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblHiChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblHiChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblHiChan.Location = new System.Drawing.Point(8, 112);
			this.lblHiChan.Name = "lblHiChan";
			this.lblHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblHiChan.Size = new System.Drawing.Size(89, 17);
			this.lblHiChan.TabIndex = 21;
			this.lblHiChan.Text = "High Channel:";
			this.lblHiChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadLoChan
			//
			this.lblReadLoChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadLoChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadLoChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadLoChan.ForeColor = System.Drawing.Color.Blue;
			this.lblReadLoChan.Location = new System.Drawing.Point(256, 96);
			this.lblReadLoChan.Name = "lblReadLoChan";
			this.lblReadLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadLoChan.Size = new System.Drawing.Size(63, 18);
			this.lblReadLoChan.TabIndex = 14;
			//
			// lblShowLoChan
			//
			this.lblShowLoChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowLoChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowLoChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowLoChan.ForeColor = System.Drawing.Color.Blue;
			this.lblShowLoChan.Location = new System.Drawing.Point(112, 96);
			this.lblShowLoChan.Name = "lblShowLoChan";
			this.lblShowLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowLoChan.Size = new System.Drawing.Size(63, 18);
			this.lblShowLoChan.TabIndex = 5;
			//
			// lblLoChan
			//
			this.lblLoChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblLoChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblLoChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblLoChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblLoChan.Location = new System.Drawing.Point(8, 96);
			this.lblLoChan.Name = "lblLoChan";
			this.lblLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblLoChan.Size = new System.Drawing.Size(89, 17);
			this.lblLoChan.TabIndex = 20;
			this.lblLoChan.Text = "Low Channel:";
			this.lblLoChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblReadRate
			//
			this.lblReadRate.BackColor = System.Drawing.SystemColors.Window;
			this.lblReadRate.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblReadRate.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblReadRate.ForeColor = System.Drawing.Color.Blue;
			this.lblReadRate.Location = new System.Drawing.Point(256, 80);
			this.lblReadRate.Name = "lblReadRate";
			this.lblReadRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblReadRate.Size = new System.Drawing.Size(63, 18);
			this.lblReadRate.TabIndex = 13;
			//
			// lblShowRate
			//
			this.lblShowRate.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowRate.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowRate.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowRate.ForeColor = System.Drawing.Color.Blue;
			this.lblShowRate.Location = new System.Drawing.Point(112, 80);
			this.lblShowRate.Name = "lblShowRate";
			this.lblShowRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowRate.Size = new System.Drawing.Size(63, 18);
			this.lblShowRate.TabIndex = 4;
			//
			// lblRate
			//
			this.lblRate.BackColor = System.Drawing.SystemColors.Window;
			this.lblRate.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblRate.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblRate.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblRate.Location = new System.Drawing.Point(32, 80);
			this.lblRate.Name = "lblRate";
			this.lblRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblRate.Size = new System.Drawing.Size(65, 17);
			this.lblRate.TabIndex = 19;
			this.lblRate.Text = "Rate:";
			this.lblRate.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblInCol
			//
			this.lblInCol.BackColor = System.Drawing.SystemColors.Window;
			this.lblInCol.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblInCol.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblInCol.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblInCol.Location = new System.Drawing.Point(224, 56);
			this.lblInCol.Name = "lblInCol";
			this.lblInCol.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInCol.Size = new System.Drawing.Size(145, 17);
			this.lblInCol.TabIndex = 27;
			this.lblInCol.Text = "Params Read from File";
			this.lblInCol.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblOutCol
			//
			this.lblOutCol.BackColor = System.Drawing.SystemColors.Window;
			this.lblOutCol.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblOutCol.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblOutCol.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblOutCol.Location = new System.Drawing.Point(88, 56);
			this.lblOutCol.Name = "lblOutCol";
			this.lblOutCol.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblOutCol.Size = new System.Drawing.Size(121, 17);
			this.lblOutCol.TabIndex = 26;
			this.lblOutCol.Text = "Params to Function";
			this.lblOutCol.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblAcqStat
			//
			this.lblAcqStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblAcqStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblAcqStat.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblAcqStat.ForeColor = System.Drawing.Color.Blue;
			this.lblAcqStat.Location = new System.Drawing.Point(80, 32);
			this.lblAcqStat.Name = "lblAcqStat";
			this.lblAcqStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblAcqStat.Size = new System.Drawing.Size(225, 14);
			this.lblAcqStat.TabIndex = 3;
			this.lblAcqStat.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(8, 8);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(359, 22);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.FileAInScan()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDataDisplay
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(411, 308);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopConvert, this.cmdStartAcq, this.txtFileName, this.lblFileInstruct, this.lblReadFile, this.lblShowFile, this.lblFileName, this.lblReadPreTrig, this.lblShowPreTrig, this.lblPreTrig, this.lblReadTotal, this.lblShowCount, this.lblCount, this.lblReadGain, this.lblShowGain, this.lblGain, this.lblReadOptions, this.lblShowOptions, this.lblOptions, this.lblReadHiChan, this.lblShowHiChan, this.lblHiChan, this.lblReadLoChan, this.lblShowLoChan, this.lblLoChan, this.lblReadRate, this.lblShowRate, this.lblRate, this.lblInCol, this.lblOutCol, this.lblAcqStat, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmDataDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Analog Input to File";
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
	    

		private void cmdStartAcq_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartAcq.Click */
		{
			cmdStartAcq.Enabled = false;
			cmdStartAcq.Visible = false;
			cmdStopConvert.Enabled = true;
			cmdStopConvert.Visible = true;

			//  Parameters:
			//    LowChan    :first A/D channel of the scan
			//    HighChan   :last A/D channel of the scan
			//    Count      :the total number of A/D samples to collect
			//    Rate       :per channel sampling rate ((samples per second) per channel)
			//    Range      :the gain for the board
			//    FileName   :the filename for the collected data values
			//    Options    :data collection options
			int Count = NumPoints;
			string FileName = txtFileName.Text; //  a full path may be required here
			int Rate = 50000;
			int LowChan = 0;
			int HighChan = 1;
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.Default;
			MccDaq.Range Range = MccDaq.Range.Bip5Volts; // set the range

			string DataCount = NumPoints.ToString("0");
			lblAcqStat.Text = "Collecting " + DataCount + " data points";
			lblShowRate.Text = Rate.ToString("0");
			lblShowLoChan.Text = LowChan.ToString("0");
			lblShowHiChan.Text = HighChan.ToString("0");
			lblShowOptions.Text = Options.ToString();
			lblShowGain.Text = Range.ToString();
			lblShowFile.Text = FileName;
			lblShowCount.Text = Count.ToString("0");
			lblShowPreTrig.Text = "Not Applicable";
			Application.DoEvents();

			//  Collect the values with Collect the values by calling MccDaq.MccBoard.FileAInScan()

			MccDaq.ErrorInfo ULStat = DaqBoard.FileAInScan( LowChan, HighChan, Count, ref Rate, Range, FileName, Options);
			
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.BadFileName)
			{
				MessageBox.Show( "Enter the name of the file to create in text box.", "Bad File Name", 0);
				cmdStopConvert.Enabled = false;
				cmdStopConvert.Visible = false;
				cmdStartAcq.Enabled = true;
				cmdStartAcq.Visible = true;
				txtFileName.Focus();
				return ;
			}
	
			
			//  show how many data points were collected
			short FileLowChan;
			short FileHighChan;
			int TotalCount;
			int PretrigCount;
			ULStat = MccDaq.MccService.FileGetInfo( FileName, out FileLowChan, out FileHighChan, out PretrigCount, out TotalCount, out Rate, out Range);
			


			lblReadRate.Text = Rate.ToString("0");
			lblReadLoChan.Text = FileLowChan.ToString("0");
			lblReadHiChan.Text = FileHighChan.ToString("0");
			lblReadOptions.Text = Options.ToString();
			lblReadGain.Text = Range.ToString();
			lblReadFile.Text = FileName;

			lblReadTotal.Text = TotalCount.ToString("0");
			lblReadPreTrig.Text = PretrigCount.ToString("0");

		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			Application.Exit();
		}

	}
}