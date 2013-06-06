// ==============================================================================
//
//  File:                         ULFI02.CS
//
//  Library Call Demonstrated:    File Operations:
//                                MccDaq.MccService.FileRead()
//                                MccDaq.MccService.FileGetInfo()
//
//  Purpose:                      Read information & data from a streamer file.
//
//  Demonstration:                Creates a file and scans analog data to the
//                                file. Displays the data in the file and the
//                                information in the file header.
//
//  Other Library Calls:          Mccdaq.MccBoard.FileAInScan()
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must be capable of MccDaq.MccScanOpions.BlockIo
//                                MccDaq.MccScanOpions.BlockIo.
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

namespace ULFI02
{
	public class frmShowFileData : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdShowData;
		public Button cmdStartAcq;
		public TextBox txtFileName;
		public Label lblFileInstruct;
		public Label lblShowFile;
		public Label lblFileName;
		public Label _lblShowData_9;
		public Label lblData9;
		public Label _lblShowData_8;
		public Label lblData8;
		public Label lblShowPreTrig;
		public Label lblPreTrig;
		public Label _lblShowData_7;
		public Label lblData7;
		public Label lblShowTotal;
		public Label lblTotal;
		public Label _lblShowData_6;
		public Label lblData6;
		public Label lblShowCount;
		public Label lblCount;
		public Label _lblShowData_5;
		public Label lblData5;
		public Label lblShowGain;
		public Label lblGain;
		public Label _lblShowData_4;
		public Label lblData4;
		public Label lblShowOptions;
		public Label lblOptions;
		public Label _lblShowData_3;
		public Label lblData3;
		public Label lblShowHiChan;
		public Label lblHiChan;
		public Label _lblShowData_2;
		public Label lblData2;
		public Label lblShowLoChan;
		public Label lblLoChan;
		public Label _lblShowData_1;
		public Label lblData1;
		public Label lblShowRate;
		public Label lblRate;
		public Label _lblShowData_0;
		public Label lblData0;
		public Label lblAcqStat;
		public Label lblDemoFunction;

		public Label[] lblShowData;

		private MccDaq.MccBoard DaqBoard;
		const int NumPoints = 128000; //  Number of data points to collect
		const int ArraySize = 10; //  size of Visual Basics data array
		private ushort[] DataBuffer = new ushort[ArraySize]; //  dimension Visual Basics data array
		string FileName; //  name of file in which data will be stored

	 
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

			lblShowData = (new Label[]{_lblShowData_0, _lblShowData_1, _lblShowData_2, _lblShowData_3, _lblShowData_4,
									   _lblShowData_5, _lblShowData_6, _lblShowData_7, _lblShowData_8, _lblShowData_9});


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
			this.cmdShowData = new System.Windows.Forms.Button();
			this.cmdStartAcq = new System.Windows.Forms.Button();
			this.txtFileName = new System.Windows.Forms.TextBox();
			this.lblFileInstruct = new System.Windows.Forms.Label();
			this.lblShowFile = new System.Windows.Forms.Label();
			this.lblFileName = new System.Windows.Forms.Label();
			this._lblShowData_9 = new System.Windows.Forms.Label();
			this.lblData9 = new System.Windows.Forms.Label();
			this._lblShowData_8 = new System.Windows.Forms.Label();
			this.lblData8 = new System.Windows.Forms.Label();
			this.lblShowPreTrig = new System.Windows.Forms.Label();
			this.lblPreTrig = new System.Windows.Forms.Label();
			this._lblShowData_7 = new System.Windows.Forms.Label();
			this.lblData7 = new System.Windows.Forms.Label();
			this.lblShowTotal = new System.Windows.Forms.Label();
			this.lblTotal = new System.Windows.Forms.Label();
			this._lblShowData_6 = new System.Windows.Forms.Label();
			this.lblData6 = new System.Windows.Forms.Label();
			this.lblShowCount = new System.Windows.Forms.Label();
			this.lblCount = new System.Windows.Forms.Label();
			this._lblShowData_5 = new System.Windows.Forms.Label();
			this.lblData5 = new System.Windows.Forms.Label();
			this.lblShowGain = new System.Windows.Forms.Label();
			this.lblGain = new System.Windows.Forms.Label();
			this._lblShowData_4 = new System.Windows.Forms.Label();
			this.lblData4 = new System.Windows.Forms.Label();
			this.lblShowOptions = new System.Windows.Forms.Label();
			this.lblOptions = new System.Windows.Forms.Label();
			this._lblShowData_3 = new System.Windows.Forms.Label();
			this.lblData3 = new System.Windows.Forms.Label();
			this.lblShowHiChan = new System.Windows.Forms.Label();
			this.lblHiChan = new System.Windows.Forms.Label();
			this._lblShowData_2 = new System.Windows.Forms.Label();
			this.lblData2 = new System.Windows.Forms.Label();
			this.lblShowLoChan = new System.Windows.Forms.Label();
			this.lblLoChan = new System.Windows.Forms.Label();
			this._lblShowData_1 = new System.Windows.Forms.Label();
			this.lblData1 = new System.Windows.Forms.Label();
			this.lblShowRate = new System.Windows.Forms.Label();
			this.lblRate = new System.Windows.Forms.Label();
			this._lblShowData_0 = new System.Windows.Forms.Label();
			this.lblData0 = new System.Windows.Forms.Label();
			this.lblAcqStat = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopConvert
			//
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(288, 296);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(46, 26);
			this.cmdStopConvert.TabIndex = 17;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			//
			// cmdShowData
			//
			this.cmdShowData.BackColor = System.Drawing.SystemColors.Control;
			this.cmdShowData.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdShowData.Enabled = false;
			this.cmdShowData.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdShowData.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdShowData.Location = new System.Drawing.Point(184, 296);
			this.cmdShowData.Name = "cmdShowData";
			this.cmdShowData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdShowData.Size = new System.Drawing.Size(84, 26);
			this.cmdShowData.TabIndex = 29;
			this.cmdShowData.Text = "Display Data";
			this.cmdShowData.Visible = false;
			this.cmdShowData.Click += new System.EventHandler(this.cmdShowData_Click);
			//
			// cmdStartAcq
			//
			this.cmdStartAcq.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartAcq.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartAcq.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartAcq.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartAcq.Location = new System.Drawing.Point(184, 296);
			this.cmdStartAcq.Name = "cmdStartAcq";
			this.cmdStartAcq.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartAcq.Size = new System.Drawing.Size(84, 26);
			this.cmdStartAcq.TabIndex = 18;
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
			this.txtFileName.Location = new System.Drawing.Point(176, 256);
			this.txtFileName.MaxLength = 0;
			this.txtFileName.Name = "txtFileName";
			this.txtFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtFileName.Size = new System.Drawing.Size(161, 25);
			this.txtFileName.TabIndex = 44;
			this.txtFileName.Text = "DEMO.DAT";
			//
			// lblFileInstruct
			//
			this.lblFileInstruct.BackColor = System.Drawing.SystemColors.Window;
			this.lblFileInstruct.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFileInstruct.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblFileInstruct.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFileInstruct.Location = new System.Drawing.Point(0, 240);
			this.lblFileInstruct.Name = "lblFileInstruct";
			this.lblFileInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFileInstruct.Size = new System.Drawing.Size(169, 41);
			this.lblFileInstruct.TabIndex = 43;
			this.lblFileInstruct.Text = "Enter the name of the file that you have created using MAKESTRM.EXE";
			this.lblFileInstruct.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowFile
			//
			this.lblShowFile.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowFile.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowFile.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowFile.ForeColor = System.Drawing.Color.Blue;
			this.lblShowFile.Location = new System.Drawing.Point(109, 211);
			this.lblShowFile.Name = "lblShowFile";
			this.lblShowFile.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowFile.Size = new System.Drawing.Size(174, 18);
			this.lblShowFile.TabIndex = 25;
			//
			// lblFileName
			//
			this.lblFileName.BackColor = System.Drawing.SystemColors.Window;
			this.lblFileName.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFileName.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblFileName.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFileName.Location = new System.Drawing.Point(26, 212);
			this.lblFileName.Name = "lblFileName";
			this.lblFileName.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFileName.Size = new System.Drawing.Size(72, 14);
			this.lblFileName.TabIndex = 42;
			this.lblFileName.Text = "File Name:";
			this.lblFileName.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_9
			//
			this._lblShowData_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_9.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_9.Location = new System.Drawing.Point(288, 186);
			this._lblShowData_9.Name = "_lblShowData_9";
			this._lblShowData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_9.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_9.TabIndex = 33;
			//
			// lblData9
			//
			this.lblData9.BackColor = System.Drawing.SystemColors.Window;
			this.lblData9.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData9.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData9.Location = new System.Drawing.Point(189, 186);
			this.lblData9.Name = "lblData9";
			this.lblData9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData9.Size = new System.Drawing.Size(87, 14);
			this.lblData9.TabIndex = 31;
			this.lblData9.Text = "Data Point 9:";
			this.lblData9.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_8
			//
			this._lblShowData_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_8.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_8.Location = new System.Drawing.Point(288, 173);
			this._lblShowData_8.Name = "_lblShowData_8";
			this._lblShowData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_8.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_8.TabIndex = 32;
			//
			// lblData8
			//
			this.lblData8.BackColor = System.Drawing.SystemColors.Window;
			this.lblData8.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData8.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData8.Location = new System.Drawing.Point(189, 173);
			this.lblData8.Name = "lblData8";
			this.lblData8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData8.Size = new System.Drawing.Size(87, 14);
			this.lblData8.TabIndex = 30;
			this.lblData8.Text = "Data Point 8:";
			this.lblData8.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowPreTrig
			//
			this.lblShowPreTrig.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowPreTrig.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowPreTrig.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowPreTrig.ForeColor = System.Drawing.Color.Blue;
			this.lblShowPreTrig.Location = new System.Drawing.Point(109, 167);
			this.lblShowPreTrig.Name = "lblShowPreTrig";
			this.lblShowPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowPreTrig.Size = new System.Drawing.Size(46, 14);
			this.lblShowPreTrig.TabIndex = 28;
			//
			// lblPreTrig
			//
			this.lblPreTrig.BackColor = System.Drawing.SystemColors.Window;
			this.lblPreTrig.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPreTrig.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPreTrig.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPreTrig.Location = new System.Drawing.Point(13, 167);
			this.lblPreTrig.Name = "lblPreTrig";
			this.lblPreTrig.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPreTrig.Size = new System.Drawing.Size(84, 14);
			this.lblPreTrig.TabIndex = 41;
			this.lblPreTrig.Text = "PreTrig Count:";
			this.lblPreTrig.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_7
			//
			this._lblShowData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_7.Location = new System.Drawing.Point(288, 160);
			this._lblShowData_7.Name = "_lblShowData_7";
			this._lblShowData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_7.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_7.TabIndex = 16;
			//
			// lblData7
			//
			this.lblData7.BackColor = System.Drawing.SystemColors.Window;
			this.lblData7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData7.Location = new System.Drawing.Point(189, 160);
			this.lblData7.Name = "lblData7";
			this.lblData7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData7.Size = new System.Drawing.Size(87, 14);
			this.lblData7.TabIndex = 8;
			this.lblData7.Text = "Data Point 7:";
			this.lblData7.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowTotal
			//
			this.lblShowTotal.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowTotal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowTotal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowTotal.ForeColor = System.Drawing.Color.Blue;
			this.lblShowTotal.Location = new System.Drawing.Point(109, 154);
			this.lblShowTotal.Name = "lblShowTotal";
			this.lblShowTotal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowTotal.Size = new System.Drawing.Size(46, 18);
			this.lblShowTotal.TabIndex = 27;
			//
			// lblTotal
			//
			this.lblTotal.BackColor = System.Drawing.SystemColors.Window;
			this.lblTotal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblTotal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblTotal.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblTotal.Location = new System.Drawing.Point(26, 154);
			this.lblTotal.Name = "lblTotal";
			this.lblTotal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblTotal.Size = new System.Drawing.Size(72, 14);
			this.lblTotal.TabIndex = 40;
			this.lblTotal.Text = "Total Count:";
			this.lblTotal.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_6
			//
			this._lblShowData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_6.Location = new System.Drawing.Point(288, 148);
			this._lblShowData_6.Name = "_lblShowData_6";
			this._lblShowData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_6.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_6.TabIndex = 15;
			//
			// lblData6
			//
			this.lblData6.BackColor = System.Drawing.SystemColors.Window;
			this.lblData6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData6.Location = new System.Drawing.Point(189, 147);
			this.lblData6.Name = "lblData6";
			this.lblData6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData6.Size = new System.Drawing.Size(87, 14);
			this.lblData6.TabIndex = 7;
			this.lblData6.Text = "Data Point 6:";
			this.lblData6.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowCount
			//
			this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCount.Location = new System.Drawing.Point(109, 141);
			this.lblShowCount.Name = "lblShowCount";
			this.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowCount.Size = new System.Drawing.Size(46, 18);
			this.lblShowCount.TabIndex = 26;
			//
			// lblCount
			//
			this.lblCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCount.Location = new System.Drawing.Point(32, 141);
			this.lblCount.Name = "lblCount";
			this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCount.Size = new System.Drawing.Size(65, 14);
			this.lblCount.TabIndex = 39;
			this.lblCount.Text = "Count:";
			this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_5
			//
			this._lblShowData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_5.Location = new System.Drawing.Point(288, 135);
			this._lblShowData_5.Name = "_lblShowData_5";
			this._lblShowData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_5.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_5.TabIndex = 14;
			//
			// lblData5
			//
			this.lblData5.BackColor = System.Drawing.SystemColors.Window;
			this.lblData5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData5.Location = new System.Drawing.Point(189, 134);
			this.lblData5.Name = "lblData5";
			this.lblData5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData5.Size = new System.Drawing.Size(87, 14);
			this.lblData5.TabIndex = 6;
			this.lblData5.Text = "Data Point 5:";
			this.lblData5.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowGain
			//
			this.lblShowGain.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowGain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowGain.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowGain.ForeColor = System.Drawing.Color.Blue;
			this.lblShowGain.Location = new System.Drawing.Point(109, 128);
			this.lblShowGain.Name = "lblShowGain";
			this.lblShowGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowGain.Size = new System.Drawing.Size(46, 18);
			this.lblShowGain.TabIndex = 24;
			//
			// lblGain
			//
			this.lblGain.BackColor = System.Drawing.SystemColors.Window;
			this.lblGain.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblGain.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblGain.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblGain.Location = new System.Drawing.Point(32, 128);
			this.lblGain.Name = "lblGain";
			this.lblGain.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblGain.Size = new System.Drawing.Size(65, 14);
			this.lblGain.TabIndex = 38;
			this.lblGain.Text = "Gain:";
			this.lblGain.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_4
			//
			this._lblShowData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_4.Location = new System.Drawing.Point(288, 122);
			this._lblShowData_4.Name = "_lblShowData_4";
			this._lblShowData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_4.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_4.TabIndex = 13;
			//
			// lblData4
			//
			this.lblData4.BackColor = System.Drawing.SystemColors.Window;
			this.lblData4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData4.Location = new System.Drawing.Point(189, 122);
			this.lblData4.Name = "lblData4";
			this.lblData4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData4.Size = new System.Drawing.Size(87, 14);
			this.lblData4.TabIndex = 5;
			this.lblData4.Text = "Data Point 4:";
			this.lblData4.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowOptions
			//
			this.lblShowOptions.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowOptions.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowOptions.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowOptions.ForeColor = System.Drawing.Color.Blue;
			this.lblShowOptions.Location = new System.Drawing.Point(109, 115);
			this.lblShowOptions.Name = "lblShowOptions";
			this.lblShowOptions.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowOptions.Size = new System.Drawing.Size(46, 18);
			this.lblShowOptions.TabIndex = 23;
			//
			// lblOptions
			//
			this.lblOptions.BackColor = System.Drawing.SystemColors.Window;
			this.lblOptions.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblOptions.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblOptions.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblOptions.Location = new System.Drawing.Point(32, 116);
			this.lblOptions.Name = "lblOptions";
			this.lblOptions.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblOptions.Size = new System.Drawing.Size(65, 14);
			this.lblOptions.TabIndex = 37;
			this.lblOptions.Text = "Options:";
			this.lblOptions.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_3
			//
			this._lblShowData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_3.Location = new System.Drawing.Point(288, 109);
			this._lblShowData_3.Name = "_lblShowData_3";
			this._lblShowData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_3.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_3.TabIndex = 12;
			//
			// lblData3
			//
			this.lblData3.BackColor = System.Drawing.SystemColors.Window;
			this.lblData3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData3.Location = new System.Drawing.Point(189, 109);
			this.lblData3.Name = "lblData3";
			this.lblData3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData3.Size = new System.Drawing.Size(87, 14);
			this.lblData3.TabIndex = 4;
			this.lblData3.Text = "Data Point 3:";
			this.lblData3.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowHiChan
			//
			this.lblShowHiChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowHiChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowHiChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowHiChan.ForeColor = System.Drawing.Color.Blue;
			this.lblShowHiChan.Location = new System.Drawing.Point(109, 102);
			this.lblShowHiChan.Name = "lblShowHiChan";
			this.lblShowHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowHiChan.Size = new System.Drawing.Size(46, 18);
			this.lblShowHiChan.TabIndex = 22;
			//
			// lblHiChan
			//
			this.lblHiChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblHiChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblHiChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblHiChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblHiChan.Location = new System.Drawing.Point(13, 103);
			this.lblHiChan.Name = "lblHiChan";
			this.lblHiChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblHiChan.Size = new System.Drawing.Size(84, 14);
			this.lblHiChan.TabIndex = 36;
			this.lblHiChan.Text = "High Channel:";
			this.lblHiChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_2
			//
			this._lblShowData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_2.Location = new System.Drawing.Point(288, 96);
			this._lblShowData_2.Name = "_lblShowData_2";
			this._lblShowData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_2.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_2.TabIndex = 11;
			//
			// lblData2
			//
			this.lblData2.BackColor = System.Drawing.SystemColors.Window;
			this.lblData2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData2.Location = new System.Drawing.Point(189, 96);
			this.lblData2.Name = "lblData2";
			this.lblData2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData2.Size = new System.Drawing.Size(87, 14);
			this.lblData2.TabIndex = 3;
			this.lblData2.Text = "Data Point 2:";
			this.lblData2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowLoChan
			//
			this.lblShowLoChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowLoChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowLoChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowLoChan.ForeColor = System.Drawing.Color.Blue;
			this.lblShowLoChan.Location = new System.Drawing.Point(109, 90);
			this.lblShowLoChan.Name = "lblShowLoChan";
			this.lblShowLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowLoChan.Size = new System.Drawing.Size(46, 18);
			this.lblShowLoChan.TabIndex = 21;
			//
			// lblLoChan
			//
			this.lblLoChan.BackColor = System.Drawing.SystemColors.Window;
			this.lblLoChan.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblLoChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblLoChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblLoChan.Location = new System.Drawing.Point(13, 90);
			this.lblLoChan.Name = "lblLoChan";
			this.lblLoChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblLoChan.Size = new System.Drawing.Size(84, 14);
			this.lblLoChan.TabIndex = 35;
			this.lblLoChan.Text = "Low Channel:";
			this.lblLoChan.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_1
			//
			this._lblShowData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_1.Location = new System.Drawing.Point(288, 84);
			this._lblShowData_1.Name = "_lblShowData_1";
			this._lblShowData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_1.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_1.TabIndex = 10;
			//
			// lblData1
			//
			this.lblData1.BackColor = System.Drawing.SystemColors.Window;
			this.lblData1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData1.Location = new System.Drawing.Point(189, 83);
			this.lblData1.Name = "lblData1";
			this.lblData1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData1.Size = new System.Drawing.Size(87, 14);
			this.lblData1.TabIndex = 2;
			this.lblData1.Text = "Data Point 1:";
			this.lblData1.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowRate
			//
			this.lblShowRate.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowRate.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowRate.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowRate.ForeColor = System.Drawing.Color.Blue;
			this.lblShowRate.Location = new System.Drawing.Point(109, 77);
			this.lblShowRate.Name = "lblShowRate";
			this.lblShowRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowRate.Size = new System.Drawing.Size(46, 18);
			this.lblShowRate.TabIndex = 20;
			//
			// lblRate
			//
			this.lblRate.BackColor = System.Drawing.SystemColors.Window;
			this.lblRate.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblRate.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblRate.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblRate.Location = new System.Drawing.Point(32, 77);
			this.lblRate.Name = "lblRate";
			this.lblRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblRate.Size = new System.Drawing.Size(65, 14);
			this.lblRate.TabIndex = 34;
			this.lblRate.Text = "Rate:";
			this.lblRate.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblShowData_0
			//
			this._lblShowData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowData_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblShowData_0.Location = new System.Drawing.Point(288, 71);
			this._lblShowData_0.Name = "_lblShowData_0";
			this._lblShowData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowData_0.Size = new System.Drawing.Size(46, 14);
			this._lblShowData_0.TabIndex = 9;
			//
			// lblData0
			//
			this.lblData0.BackColor = System.Drawing.SystemColors.Window;
			this.lblData0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData0.Location = new System.Drawing.Point(189, 70);
			this.lblData0.Name = "lblData0";
			this.lblData0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData0.Size = new System.Drawing.Size(87, 14);
			this.lblData0.TabIndex = 1;
			this.lblData0.Text = "Data Point 0:";
			this.lblData0.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblAcqStat
			//
			this.lblAcqStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblAcqStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblAcqStat.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblAcqStat.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblAcqStat.Location = new System.Drawing.Point(71, 39);
			this.lblAcqStat.Name = "lblAcqStat";
			this.lblAcqStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblAcqStat.Size = new System.Drawing.Size(225, 14);
			this.lblAcqStat.TabIndex = 19;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(6, 6);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(335, 22);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.FileAInScan()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmShowFileData
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(349, 328);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopConvert, this.cmdShowData, this.cmdStartAcq, this.txtFileName, this.lblFileInstruct, this.lblShowFile, this.lblFileName, this._lblShowData_9, this.lblData9, this._lblShowData_8, this.lblData8, this.lblShowPreTrig, this.lblPreTrig, this._lblShowData_7, this.lblData7, this.lblShowTotal, this.lblTotal, this._lblShowData_6, this.lblData6, this.lblShowCount, this.lblCount, this._lblShowData_5, this.lblData5, this.lblShowGain, this.lblGain, this._lblShowData_4, this.lblData4, this.lblShowOptions, this.lblOptions, this._lblShowData_3, this.lblData3, this.lblShowHiChan, this.lblHiChan, this._lblShowData_2, this.lblData2, this.lblShowLoChan, this.lblLoChan, this._lblShowData_1, this.lblData1, this.lblShowRate, this.lblRate, this._lblShowData_0, this.lblData0, this.lblAcqStat, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmShowFileData";
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
			Application.Run(new frmShowFileData());
		}
	    

		private void cmdShowData_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdShowData.Click */
		{
			//  show the data using MccDaq.MccService.FileRead()
			//   Parameters:
			//     FileName      :the filename containing the data
			//     FirstPoint    :index of the first data value to read
			//     NumPoints     :the number of data values to read from the file
			//     DataBuffer()  :array to read data into
			int FirstPoint = 0; //  start at the first point
			int ReadPoints = ArraySize; //  specify number of data points to read
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.FileRead(FileName, FirstPoint, ref ReadPoints, out DataBuffer[0]);
			

			//  display the data values read from the file
			for (int i=FirstPoint; i<=ArraySize - 1; ++i)
			lblShowData[i].Text = DataBuffer[i].ToString("0");
		}


		private void cmdStartAcq_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartAcq.Click */
		{
			cmdStartAcq.Enabled = false;

			//  Collect the values with MccDaq.MccBoard.FileAInScan()
			//   Parameters:
			//     LowChan    :first A/D channel of the scan
			//     HighChan   :last A/D channel of the scan
			//     Count      :the total number of A/D samples to collect
			//     Rate       :per channel sampling rate ((samples per second) per channel)
			//     Range      :the gain for the board
			//     FileName   :the filename for the collected data values
			//     Options    :data collection options
			//  Parameters:
			int Count = NumPoints;
			//  it may be necessary to add path tofile name for data file to be found
			FileName = txtFileName.Text; 
			int Rate = 50000;				  
			int LowChan = 0;
			int HighChan = 0;
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.Default;
			MccDaq.Range Range = MccDaq.Range.Bip5Volts; // set the range

			//display the parameters
			string DataCount = NumPoints.ToString("0");
			lblAcqStat.Text = "Collecting " + DataCount + " data points";
			lblShowRate.Text = Rate.ToString("0");
			lblShowLoChan.Text = LowChan.ToString("0");
			lblShowHiChan.Text = HighChan.ToString("0");
			lblShowOptions.Text = Options.ToString();
			lblShowGain.Text = Range.ToString();
			lblShowFile.Text = FileName;
			lblShowCount.Text = Count.ToString("0");

			MccDaq.ErrorInfo ULStat = DaqBoard.FileAInScan( LowChan, HighChan, Count, ref Rate, Range, FileName, Options);
			
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.BadFileName)
			{
				MessageBox.Show( "Enter the name of the file to create or overwrite in text box.", "Bad File Name", 0);
				cmdStartAcq.Enabled = true;
				cmdStartAcq.Visible = true;
				txtFileName.Focus();
				return;
			}
		 


			//  show how many data points were collected
			short FileHighChan;
			short FileLowChan;
			int TotalCount;
			int PretrigCount;
			ULStat = MccDaq.MccService.FileGetInfo( FileName, out FileLowChan, out FileHighChan, out PretrigCount, out TotalCount, out Rate, out Range);


			lblShowRate.Text = Rate.ToString("0");
			lblShowLoChan.Text = FileLowChan.ToString("0");
			lblShowHiChan.Text = FileHighChan.ToString("0");
			lblShowOptions.Text = Options.ToString();
			lblShowGain.Text = Range.ToString();
			lblShowFile.Text = FileName;

			lblShowTotal.Text = TotalCount.ToString("0");
			lblShowPreTrig.Text = PretrigCount.ToString("0");

			cmdShowData.Enabled = true;
			cmdShowData.Visible = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			Application.Exit();
		}

	}
}