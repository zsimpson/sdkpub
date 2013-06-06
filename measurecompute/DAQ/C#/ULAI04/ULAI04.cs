// ==============================================================================

//  File:                         ULAI04.CS

//  Library Call Demonstrated:    Mccdaq.MccBoard.AInScan() with Mccdaq.MccBoard.AConvertData()

//  Purpose:                      Demonstrates the conversion of data values
//                                after they have been collected.

//  Demonstration:                Collects data points from up to 8 analog inputs.
//											 Data points are collected as 16-bit values and
//                                are converted to channel numbers and
//                                12-bit data values using Mccdaq.MccBoard.AConvertData

//  Other Library Calls:          Mccdaq.MccBoard.GetStatus()
//                                Mccdaq.MccBoard.StopBackground()
//                                Mccdaq.MccBoard.ErrHandling()

//  Special Requirements:         Analog signals on up to eight input channels.

// ==============================================================================
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Diagnostics;

using MccDaq;

namespace ULAI04
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public TextBox txtHighChan;
		public Button cmdStopConvert;
		public Button cmdConvData;
		public Button cmdStartAcq;
		public Timer tmrCheckStatus;
		public Label Label1;
		public Label _lblADData_7;
		public Label _lblShowTag_7;
		public Label lblChan7;
		public Label _lblADData_3;
		public Label _lblShowTag_3;
		public Label lblChan3;
		public Label _lblADData_6;
		public Label _lblShowTag_6;
		public Label lblChan6;
		public Label _lblADData_2;
		public Label _lblShowTag_2;
		public Label lblChan2;
		public Label _lblADData_5;
		public Label _lblShowTag_5;
		public Label lblChan5;
		public Label _lblADData_1;
		public Label _lblShowTag_1;
		public Label lblChan1;
		public Label _lblADData_4;
		public Label _lblShowTag_4;
		public Label lblChan4;
		public Label _lblADData_0;
		public Label _lblShowTag_0;
		public Label lblChan0;
		public Label lblData2;
		public Label lblTag4;
		public Label lblData1;
		public Label lblTag2;
		public Label lblTag3;
		public Label lblTag1;
		public Label lblDemoFunction;
		public Label[] lblADData;
		public Label[] lblShowTag;

		const int NumPoints = 8;  //  Number of data points to collect

		private MccDaq.MccBoard DaqBoard;
		private int FirstPoint = 0; //  set first element in buffer to transfer to array
		private ushort[] ADData = new ushort[NumPoints];	//holds the data values
		private ushort[] ChanTags = new ushort[NumPoints];  // holds the channel tag values
		private int MemHandle;	//  define a variable to contain the handle for
								//  memory allocated by Windows through Mccdaq.MccBoard.WinBufAlloc()
		int HighChan;

	 
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
			

			// this allows us to index into the labels
			lblADData = (new Label[] {_lblADData_0, _lblADData_1, _lblADData_2, _lblADData_3, _lblADData_4, _lblADData_5, _lblADData_6, _lblADData_7});  
			lblShowTag = (new Label[] {_lblShowTag_0, _lblShowTag_1, _lblShowTag_2, _lblShowTag_3, _lblShowTag_4, _lblShowTag_5, _lblShowTag_6, _lblShowTag_7});  

	        
			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);

			//  set aside memory to hold data
			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			


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
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this.cmdConvData = new System.Windows.Forms.Button();
			this.cmdStartAcq = new System.Windows.Forms.Button();
			this.tmrCheckStatus = new System.Windows.Forms.Timer(this.components);
			this.Label1 = new System.Windows.Forms.Label();
			this._lblADData_7 = new System.Windows.Forms.Label();
			this._lblShowTag_7 = new System.Windows.Forms.Label();
			this.lblChan7 = new System.Windows.Forms.Label();
			this._lblADData_3 = new System.Windows.Forms.Label();
			this._lblShowTag_3 = new System.Windows.Forms.Label();
			this.lblChan3 = new System.Windows.Forms.Label();
			this._lblADData_6 = new System.Windows.Forms.Label();
			this._lblShowTag_6 = new System.Windows.Forms.Label();
			this.lblChan6 = new System.Windows.Forms.Label();
			this._lblADData_2 = new System.Windows.Forms.Label();
			this._lblShowTag_2 = new System.Windows.Forms.Label();
			this.lblChan2 = new System.Windows.Forms.Label();
			this._lblADData_5 = new System.Windows.Forms.Label();
			this._lblShowTag_5 = new System.Windows.Forms.Label();
			this.lblChan5 = new System.Windows.Forms.Label();
			this._lblADData_1 = new System.Windows.Forms.Label();
			this._lblShowTag_1 = new System.Windows.Forms.Label();
			this.lblChan1 = new System.Windows.Forms.Label();
			this._lblADData_4 = new System.Windows.Forms.Label();
			this._lblShowTag_4 = new System.Windows.Forms.Label();
			this.lblChan4 = new System.Windows.Forms.Label();
			this._lblADData_0 = new System.Windows.Forms.Label();
			this._lblShowTag_0 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblData2 = new System.Windows.Forms.Label();
			this.lblTag4 = new System.Windows.Forms.Label();
			this.lblData1 = new System.Windows.Forms.Label();
			this.lblTag2 = new System.Windows.Forms.Label();
			this.lblTag3 = new System.Windows.Forms.Label();
			this.lblTag1 = new System.Windows.Forms.Label();
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
			this.txtHighChan.Location = new System.Drawing.Point(184, 88);
			this.txtHighChan.MaxLength = 0;
			this.txtHighChan.Name = "txtHighChan";
			this.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtHighChan.Size = new System.Drawing.Size(33, 19);
			this.txtHighChan.TabIndex = 34;
			this.txtHighChan.Text = "3";
			this.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			//
			// cmdStopConvert
			//
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(269, 218);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(52, 27);
			this.cmdStopConvert.TabIndex = 17;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			//
			// cmdConvData
			//
			this.cmdConvData.BackColor = System.Drawing.SystemColors.Control;
			this.cmdConvData.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdConvData.Enabled = false;
			this.cmdConvData.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdConvData.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdConvData.Location = new System.Drawing.Point(199, 52);
			this.cmdConvData.Name = "cmdConvData";
			this.cmdConvData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdConvData.Size = new System.Drawing.Size(84, 27);
			this.cmdConvData.TabIndex = 19;
			this.cmdConvData.Text = "Convert Data";
			this.cmdConvData.Click += new System.EventHandler(this.cmdConvData_Click);
			//
			// cmdStartAcq
			//
			this.cmdStartAcq.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartAcq.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartAcq.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartAcq.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartAcq.Location = new System.Drawing.Point(77, 52);
			this.cmdStartAcq.Name = "cmdStartAcq";
			this.cmdStartAcq.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartAcq.Size = new System.Drawing.Size(84, 27);
			this.cmdStartAcq.TabIndex = 18;
			this.cmdStartAcq.Text = "Acquire Data";
			this.cmdStartAcq.Click += new System.EventHandler(this.cmdStartAcq_Click);
			//
			// tmrCheckStatus
			//
			this.tmrCheckStatus.Interval = 200;
			this.tmrCheckStatus.Tick += new System.EventHandler(this.tmrCheckStatus_Tick);
			//
			// Label1
			//
			this.Label1.BackColor = System.Drawing.SystemColors.Window;
			this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label1.Location = new System.Drawing.Point(40, 88);
			this.Label1.Name = "Label1";
			this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label1.Size = new System.Drawing.Size(137, 17);
			this.Label1.TabIndex = 35;
			this.Label1.Text = "Measure Channels 0 to";
			//
			// _lblADData_7
			//
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Location = new System.Drawing.Point(272, 192);
			this._lblADData_7.Name = "_lblADData_7";
			this._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_7.Size = new System.Drawing.Size(65, 17);
			this._lblADData_7.TabIndex = 16;
			this._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_7
			//
			this._lblShowTag_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_7.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_7.Location = new System.Drawing.Point(248, 192);
			this._lblShowTag_7.Name = "_lblShowTag_7";
			this._lblShowTag_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_7.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_7.TabIndex = 27;
			this._lblShowTag_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan7
			//
			this.lblChan7.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan7.Location = new System.Drawing.Point(176, 192);
			this.lblChan7.Name = "lblChan7";
			this.lblChan7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan7.Size = new System.Drawing.Size(65, 17);
			this.lblChan7.TabIndex = 8;
			this.lblChan7.Text = "Channel 7:";
			//
			// _lblADData_3
			//
			this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_3.Location = new System.Drawing.Point(104, 192);
			this._lblADData_3.Name = "_lblADData_3";
			this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_3.Size = new System.Drawing.Size(65, 17);
			this._lblADData_3.TabIndex = 12;
			this._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_3
			//
			this._lblShowTag_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_3.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_3.Location = new System.Drawing.Point(72, 192);
			this._lblShowTag_3.Name = "_lblShowTag_3";
			this._lblShowTag_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_3.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_3.TabIndex = 23;
			this._lblShowTag_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan3
			//
			this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan3.Location = new System.Drawing.Point(8, 192);
			this.lblChan3.Name = "lblChan3";
			this.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan3.Size = new System.Drawing.Size(65, 17);
			this.lblChan3.TabIndex = 4;
			this.lblChan3.Text = "Channel 3:";
			//
			// _lblADData_6
			//
			this._lblADData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_6.Location = new System.Drawing.Point(272, 176);
			this._lblADData_6.Name = "_lblADData_6";
			this._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_6.Size = new System.Drawing.Size(65, 17);
			this._lblADData_6.TabIndex = 15;
			this._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_6
			//
			this._lblShowTag_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_6.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_6.Location = new System.Drawing.Point(248, 176);
			this._lblShowTag_6.Name = "_lblShowTag_6";
			this._lblShowTag_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_6.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_6.TabIndex = 26;
			this._lblShowTag_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan6
			//
			this.lblChan6.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan6.Location = new System.Drawing.Point(176, 176);
			this.lblChan6.Name = "lblChan6";
			this.lblChan6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan6.Size = new System.Drawing.Size(65, 17);
			this.lblChan6.TabIndex = 7;
			this.lblChan6.Text = "Channel 6:";
			//
			// _lblADData_2
			//
			this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_2.Location = new System.Drawing.Point(104, 176);
			this._lblADData_2.Name = "_lblADData_2";
			this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_2.Size = new System.Drawing.Size(65, 17);
			this._lblADData_2.TabIndex = 11;
			this._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_2
			//
			this._lblShowTag_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_2.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_2.Location = new System.Drawing.Point(72, 176);
			this._lblShowTag_2.Name = "_lblShowTag_2";
			this._lblShowTag_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_2.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_2.TabIndex = 22;
			this._lblShowTag_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan2
			//
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan2.Location = new System.Drawing.Point(8, 176);
			this.lblChan2.Name = "lblChan2";
			this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan2.Size = new System.Drawing.Size(65, 17);
			this.lblChan2.TabIndex = 3;
			this.lblChan2.Text = "Channel 2:";
			//
			// _lblADData_5
			//
			this._lblADData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_5.Location = new System.Drawing.Point(272, 160);
			this._lblADData_5.Name = "_lblADData_5";
			this._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_5.Size = new System.Drawing.Size(65, 17);
			this._lblADData_5.TabIndex = 14;
			this._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_5
			//
			this._lblShowTag_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_5.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_5.Location = new System.Drawing.Point(248, 160);
			this._lblShowTag_5.Name = "_lblShowTag_5";
			this._lblShowTag_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_5.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_5.TabIndex = 25;
			this._lblShowTag_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan5
			//
			this.lblChan5.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan5.Location = new System.Drawing.Point(176, 160);
			this.lblChan5.Name = "lblChan5";
			this.lblChan5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan5.Size = new System.Drawing.Size(65, 17);
			this.lblChan5.TabIndex = 6;
			this.lblChan5.Text = "Channel 5:";
			//
			// _lblADData_1
			//
			this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_1.Location = new System.Drawing.Point(104, 160);
			this._lblADData_1.Name = "_lblADData_1";
			this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_1.Size = new System.Drawing.Size(65, 17);
			this._lblADData_1.TabIndex = 10;
			this._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_1
			//
			this._lblShowTag_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_1.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_1.Location = new System.Drawing.Point(72, 160);
			this._lblShowTag_1.Name = "_lblShowTag_1";
			this._lblShowTag_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_1.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_1.TabIndex = 21;
			this._lblShowTag_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan1
			//
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan1.Location = new System.Drawing.Point(8, 160);
			this.lblChan1.Name = "lblChan1";
			this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1.Size = new System.Drawing.Size(65, 17);
			this.lblChan1.TabIndex = 2;
			this.lblChan1.Text = "Channel 1:";
			//
			// _lblADData_4
			//
			this._lblADData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_4.Location = new System.Drawing.Point(272, 144);
			this._lblADData_4.Name = "_lblADData_4";
			this._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_4.Size = new System.Drawing.Size(65, 17);
			this._lblADData_4.TabIndex = 13;
			this._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_4
			//
			this._lblShowTag_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_4.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_4.Location = new System.Drawing.Point(248, 144);
			this._lblShowTag_4.Name = "_lblShowTag_4";
			this._lblShowTag_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_4.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_4.TabIndex = 24;
			this._lblShowTag_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan4
			//
			this.lblChan4.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan4.Location = new System.Drawing.Point(176, 144);
			this.lblChan4.Name = "lblChan4";
			this.lblChan4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan4.Size = new System.Drawing.Size(65, 17);
			this.lblChan4.TabIndex = 5;
			this.lblChan4.Text = "Channel 4:";
			//
			// _lblADData_0
			//
			this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_0.Location = new System.Drawing.Point(104, 144);
			this._lblADData_0.Name = "_lblADData_0";
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.Size = new System.Drawing.Size(65, 17);
			this._lblADData_0.TabIndex = 9;
			this._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowTag_0
			//
			this._lblShowTag_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowTag_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowTag_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowTag_0.ForeColor = System.Drawing.Color.Blue;
			this._lblShowTag_0.Location = new System.Drawing.Point(72, 144);
			this._lblShowTag_0.Name = "_lblShowTag_0";
			this._lblShowTag_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowTag_0.Size = new System.Drawing.Size(17, 17);
			this._lblShowTag_0.TabIndex = 20;
			this._lblShowTag_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan0
			//
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan0.Location = new System.Drawing.Point(8, 144);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.Size = new System.Drawing.Size(65, 17);
			this.lblChan0.TabIndex = 1;
			this.lblChan0.Text = "Channel 0:";
			//
			// lblData2
			//
			this.lblData2.BackColor = System.Drawing.SystemColors.Window;
			this.lblData2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData2.Location = new System.Drawing.Point(286, 125);
			this.lblData2.Name = "lblData2";
			this.lblData2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData2.Size = new System.Drawing.Size(39, 14);
			this.lblData2.TabIndex = 33;
			this.lblData2.Text = "Data";
			this.lblData2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblTag4
			//
			this.lblTag4.BackColor = System.Drawing.SystemColors.Window;
			this.lblTag4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblTag4.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblTag4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblTag4.Location = new System.Drawing.Point(235, 125);
			this.lblTag4.Name = "lblTag4";
			this.lblTag4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblTag4.Size = new System.Drawing.Size(46, 14);
			this.lblTag4.TabIndex = 32;
			this.lblTag4.Text = "Tags";
			this.lblTag4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblData1
			//
			this.lblData1.BackColor = System.Drawing.SystemColors.Window;
			this.lblData1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblData1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblData1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblData1.Location = new System.Drawing.Point(120, 125);
			this.lblData1.Name = "lblData1";
			this.lblData1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblData1.Size = new System.Drawing.Size(39, 14);
			this.lblData1.TabIndex = 29;
			this.lblData1.Text = "Data";
			this.lblData1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblTag2
			//
			this.lblTag2.BackColor = System.Drawing.SystemColors.Window;
			this.lblTag2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblTag2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblTag2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblTag2.Location = new System.Drawing.Point(62, 125);
			this.lblTag2.Name = "lblTag2";
			this.lblTag2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblTag2.Size = new System.Drawing.Size(46, 14);
			this.lblTag2.TabIndex = 28;
			this.lblTag2.Text = "Tags";
			this.lblTag2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblTag3
			//
			this.lblTag3.BackColor = System.Drawing.SystemColors.Window;
			this.lblTag3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblTag3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblTag3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblTag3.Location = new System.Drawing.Point(229, 112);
			this.lblTag3.Name = "lblTag3";
			this.lblTag3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblTag3.Size = new System.Drawing.Size(58, 14);
			this.lblTag3.TabIndex = 31;
			this.lblTag3.Text = "Channel";
			this.lblTag3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblTag1
			//
			this.lblTag1.BackColor = System.Drawing.SystemColors.Window;
			this.lblTag1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblTag1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblTag1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblTag1.Location = new System.Drawing.Point(56, 112);
			this.lblTag1.Name = "lblTag1";
			this.lblTag1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblTag1.Size = new System.Drawing.Size(58, 14);
			this.lblTag1.TabIndex = 30;
			this.lblTag1.Text = "Channel";
			this.lblTag1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(16, 16);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(319, 22);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AConvertData()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDataDisplay
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(349, 253);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.txtHighChan, this.cmdStopConvert, this.cmdConvData, this.cmdStartAcq, this.Label1, this._lblADData_7, this._lblShowTag_7, this.lblChan7, this._lblADData_3, this._lblShowTag_3, this.lblChan3, this._lblADData_6, this._lblShowTag_6, this.lblChan6, this._lblADData_2, this._lblShowTag_2, this.lblChan2, this._lblADData_5, this._lblShowTag_5, this.lblChan5, this._lblADData_1, this._lblShowTag_1, this.lblChan1, this._lblADData_4, this._lblShowTag_4, this.lblChan4, this._lblADData_0, this._lblShowTag_0, this.lblChan0, this.lblData2, this.lblTag4, this.lblData1, this.lblTag2, this.lblTag3, this.lblTag1, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(168, 103);
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
	    
	   
		private void cmdConvData_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdConvData.Click */
		{
			int i;
			MccDaq.ErrorInfo ULStat;

			//  Use MccDaq.MccBoard.AConvertData() to convert the 16-bit values
			//  in ADData() to 12-bit values
			//   Parameters:
			//     NumPoints     :the number of data values to convert
			//     ADData        :the array holding the 16-bit data values to be converted
			//     ChanTags      : the arrey that will hold the channel tags
			ULStat = DaqBoard.AConvertData( NumPoints, ref ADData[0], out ChanTags[0]);
			


			for (i=0; i<=HighChan; ++i)
			{
				lblADData[i].Text = ADData[i].ToString("D");
				lblShowTag[i].Text = ChanTags[i].ToString("D");
			}
			cmdConvData.Enabled = false;

		}


		private void cmdStartAcq_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartAcq.Click */
		{

			MccDaq.ErrorInfo ULStat;
			MccDaq.Range Range;
			MccDaq.ScanOptions Options;
			int Rate;
			int Count;
			int LowChan;
			short i;

			foreach(Label l in lblShowTag) l.Text = "";
			

			//  Collect the values by calling MccDaq.MccBoard.AInScan function
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

			Count = NumPoints; //  total number of data points to collect
			Rate = 390; //  per channel sampling rate ((samples per second) per channel)
			Options = MccDaq.ScanOptions.Background;	//  collect data in background mode 
														//  as 16-bit values (no conversion)
			Range = MccDaq.Range.Bip5Volts; //  set the range

			ULStat = DaqBoard.AInScan( LowChan, HighChan, Count, ref Rate, Range, MemHandle, Options);
			

			tmrCheckStatus.Enabled = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			
			MccDaq.ErrorInfo ULStat= DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
			
			
			ULStat = MccDaq.MccService.WinBufFree(MemHandle);	//  Free up memory for use by
																//  other programs
			
			MemHandle = 0;

			Application.Exit();

		}


		private void tmrCheckStatus_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrCheckStatus.Tick */
		{

			int j;
			int i;
			MccDaq.ErrorInfo ULStat;
			int CurIndex;
			int CurCount;
			short Status;

			tmrCheckStatus.Stop();

			//  Check the current status of the background data collection
			//   Parameters:
			//     Status     :current status of the background data collection
			//     CurCount   :current number of samples collected
			//     CurIndex   :index to the data buffer pointing to the last value transferred
			//    FunctionType: A/D operation (MccDaq.FunctionType.AiFunction)
			//
			//  Transfer the data from the memory buffer set up by Windows
			//  to an array for use by Visual Basic
			ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AiFunction);
			


			if (Status == MccDaq.MccBoard.Idle)
			{
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
				

				ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out ADData[0], FirstPoint, NumPoints);


				for (i=0; i<=HighChan; ++i)
					lblADData[i].Text = ADData[i].ToString("D");
				
				for (j=HighChan + 1; j<=7; ++j)
					lblADData[j].Text = "0";
				
				cmdConvData.Enabled = true;
				tmrCheckStatus.Enabled = false;
			}
			else
				tmrCheckStatus.Start();
		}

	}
}