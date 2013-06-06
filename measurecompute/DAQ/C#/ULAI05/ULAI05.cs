// ==============================================================================

//  File:                         ULAI05.CS

//  Library Call Demonstrated:    Mccdaq.MccBoard.AInScan() with manual data conversion

//  Purpose:                      Demonstrate the manual conversion of data
//                                values after they have been collected.

//  Demonstration:                Collects 10 data points from five analog
//                                input channels.  Data are collected
//                                as 16-bit values and are converted to
//                                channel numbers and 12-bit data values.
//                                

//  Other Library Calls:          Mccdaq.MccBoard.GetStatus()
//                                Mccdaq.MccBoard.StopBackground()
//                                Mccdaq.MccBoard.ErrHandling()

//  Special Requirements:         Board 0 must have a 12 bit A/D converter.
//                                Analog signal on input channels 0 - 4.

// ==============================================================================
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Diagnostics;

using MccDaq;

namespace ULAI05
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;
		public ToolTip ToolTip1;
		public TextBox txtHighChan;
		public Button cmdQuit;
		public Button cmdStartConvert;
		public Button cmdStopBackground;
		public Timer tmrCheckStatus;
		public Label lbl;
		public Label _lblConvData_9;
		public Label _lblConvData_8;
		public Label _lblConvData_7;
		public Label _lblConvData_6;
		public Label _lblConvData_5;
		public Label _lblConvData_4;
		public Label _lblConvData_3;
		public Label _lblConvData_2;
		public Label _lblConvData_1;
		public Label _lblConvData_0;
		public Label lblVoltsRead;
		public Label _lblShowRaw_9;
		public Label _lblShowRaw_8;
		public Label _lblShowRaw_7;
		public Label _lblShowRaw_6;
		public Label _lblShowRaw_5;
		public Label _lblShowRaw_4;
		public Label _lblShowRaw_3;
		public Label _lblShowRaw_2;
		public Label _lblShowRaw_1;
		public Label _lblShowRaw_0;
		public Label lblRawData;
		public Label lblStatus;
		public Label lblDemoFunction;
	    
		public Label[] lblConvData;
		public Label[] lblShowRaw;

		private MccDaq.MccBoard DaqBoard;
		const int NumPoints = 10;     //  Number of data points to collect
		private int FirstPoint = 0;

		private ushort[] ADData = new ushort[NumPoints];     // holds the data values
		private ushort[] ConvData = new ushort[NumPoints];   // holds the channel tag values
		private int HighChan;
		private int MemHandle;
		private short UserTerm;

	 
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

			//  set aside memory to hold data
			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			

			UserTerm = 0;

			//  Note: Any change to label names requires a change to the corresponding array element
			lblConvData = (new Label[] {_lblConvData_0, _lblConvData_1, _lblConvData_2, _lblConvData_3, _lblConvData_4, _lblConvData_5, _lblConvData_6, _lblConvData_7, _lblConvData_8, _lblConvData_9});
			lblShowRaw = (new Label[] {_lblShowRaw_0, _lblShowRaw_1, _lblShowRaw_2, _lblShowRaw_3, _lblShowRaw_4, _lblShowRaw_5, _lblShowRaw_6, _lblShowRaw_7, _lblShowRaw_8, _lblShowRaw_9});

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
			this.cmdStartConvert = new System.Windows.Forms.Button();
			this.cmdStopBackground = new System.Windows.Forms.Button();
			this.tmrCheckStatus = new System.Windows.Forms.Timer(this.components);
			this.lbl = new System.Windows.Forms.Label();
			this._lblConvData_9 = new System.Windows.Forms.Label();
			this._lblConvData_8 = new System.Windows.Forms.Label();
			this._lblConvData_7 = new System.Windows.Forms.Label();
			this._lblConvData_6 = new System.Windows.Forms.Label();
			this._lblConvData_5 = new System.Windows.Forms.Label();
			this._lblConvData_4 = new System.Windows.Forms.Label();
			this._lblConvData_3 = new System.Windows.Forms.Label();
			this._lblConvData_2 = new System.Windows.Forms.Label();
			this._lblConvData_1 = new System.Windows.Forms.Label();
			this._lblConvData_0 = new System.Windows.Forms.Label();
			this.lblVoltsRead = new System.Windows.Forms.Label();
			this._lblShowRaw_9 = new System.Windows.Forms.Label();
			this._lblShowRaw_8 = new System.Windows.Forms.Label();
			this._lblShowRaw_7 = new System.Windows.Forms.Label();
			this._lblShowRaw_6 = new System.Windows.Forms.Label();
			this._lblShowRaw_5 = new System.Windows.Forms.Label();
			this._lblShowRaw_4 = new System.Windows.Forms.Label();
			this._lblShowRaw_3 = new System.Windows.Forms.Label();
			this._lblShowRaw_2 = new System.Windows.Forms.Label();
			this._lblShowRaw_1 = new System.Windows.Forms.Label();
			this._lblShowRaw_0 = new System.Windows.Forms.Label();
			this.lblRawData = new System.Windows.Forms.Label();
			this.lblStatus = new System.Windows.Forms.Label();
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
			this.txtHighChan.Location = new System.Drawing.Point(224, 238);
			this.txtHighChan.MaxLength = 0;
			this.txtHighChan.Name = "txtHighChan";
			this.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtHighChan.Size = new System.Drawing.Size(25, 19);
			this.txtHighChan.TabIndex = 28;
			this.txtHighChan.Text = "3";
			this.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			//
			// cmdQuit
			//
			this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
			this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdQuit.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdQuit.Location = new System.Drawing.Point(312, 264);
			this.cmdQuit.Name = "cmdQuit";
			this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdQuit.Size = new System.Drawing.Size(52, 26);
			this.cmdQuit.TabIndex = 4;
			this.cmdQuit.Text = "Quit";
			this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
			//
			// cmdStartConvert
			//
			this.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartConvert.Location = new System.Drawing.Point(248, 264);
			this.cmdStartConvert.Name = "cmdStartConvert";
			this.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartConvert.Size = new System.Drawing.Size(52, 26);
			this.cmdStartConvert.TabIndex = 3;
			this.cmdStartConvert.Text = "Start";
			this.cmdStartConvert.Click += new System.EventHandler(this.cmdStartConvert_Click);
			//
			// cmdStopBackground
			//
			this.cmdStopBackground.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopBackground.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopBackground.Enabled = false;
			this.cmdStopBackground.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopBackground.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopBackground.Location = new System.Drawing.Point(64, 264);
			this.cmdStopBackground.Name = "cmdStopBackground";
			this.cmdStopBackground.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopBackground.Size = new System.Drawing.Size(137, 25);
			this.cmdStopBackground.TabIndex = 26;
			this.cmdStopBackground.Text = "Stop Background";
			this.cmdStopBackground.Click += new System.EventHandler(this.cmdStopBackground_Click);
			//
			// tmrCheckStatus
			//
			this.tmrCheckStatus.Interval = 300;
			this.tmrCheckStatus.Tick += new System.EventHandler(this.tmrCheckStatus_Tick);
			//
			// lbl
			//
			this.lbl.BackColor = System.Drawing.SystemColors.Window;
			this.lbl.Cursor = System.Windows.Forms.Cursors.Default;
			this.lbl.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lbl.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lbl.Location = new System.Drawing.Point(96, 240);
			this.lbl.Name = "lbl";
			this.lbl.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lbl.Size = new System.Drawing.Size(120, 17);
			this.lbl.TabIndex = 27;
			this.lbl.Text = "Measure Channels 0 to";
			//
			// _lblConvData_9
			//
			this._lblConvData_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_9.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_9.Location = new System.Drawing.Point(296, 208);
			this._lblConvData_9.Name = "_lblConvData_9";
			this._lblConvData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_9.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_9.TabIndex = 24;
			this._lblConvData_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_8
			//
			this._lblConvData_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_8.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_8.Location = new System.Drawing.Point(224, 208);
			this._lblConvData_8.Name = "_lblConvData_8";
			this._lblConvData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_8.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_8.TabIndex = 23;
			this._lblConvData_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_7
			//
			this._lblConvData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_7.Location = new System.Drawing.Point(152, 208);
			this._lblConvData_7.Name = "_lblConvData_7";
			this._lblConvData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_7.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_7.TabIndex = 22;
			this._lblConvData_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_6
			//
			this._lblConvData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_6.Location = new System.Drawing.Point(80, 208);
			this._lblConvData_6.Name = "_lblConvData_6";
			this._lblConvData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_6.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_6.TabIndex = 21;
			this._lblConvData_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_5
			//
			this._lblConvData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_5.Location = new System.Drawing.Point(8, 208);
			this._lblConvData_5.Name = "_lblConvData_5";
			this._lblConvData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_5.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_5.TabIndex = 20;
			this._lblConvData_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_4
			//
			this._lblConvData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_4.Location = new System.Drawing.Point(296, 184);
			this._lblConvData_4.Name = "_lblConvData_4";
			this._lblConvData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_4.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_4.TabIndex = 19;
			this._lblConvData_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_3
			//
			this._lblConvData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_3.Location = new System.Drawing.Point(224, 184);
			this._lblConvData_3.Name = "_lblConvData_3";
			this._lblConvData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_3.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_3.TabIndex = 18;
			this._lblConvData_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_2
			//
			this._lblConvData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_2.Location = new System.Drawing.Point(152, 184);
			this._lblConvData_2.Name = "_lblConvData_2";
			this._lblConvData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_2.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_2.TabIndex = 17;
			this._lblConvData_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_1
			//
			this._lblConvData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_1.Location = new System.Drawing.Point(80, 184);
			this._lblConvData_1.Name = "_lblConvData_1";
			this._lblConvData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_1.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_1.TabIndex = 16;
			this._lblConvData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblConvData_0
			//
			this._lblConvData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblConvData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblConvData_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblConvData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblConvData_0.Location = new System.Drawing.Point(8, 184);
			this._lblConvData_0.Name = "_lblConvData_0";
			this._lblConvData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblConvData_0.Size = new System.Drawing.Size(65, 17);
			this._lblConvData_0.TabIndex = 6;
			this._lblConvData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblVoltsRead
			//
			this.lblVoltsRead.BackColor = System.Drawing.SystemColors.Window;
			this.lblVoltsRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblVoltsRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblVoltsRead.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblVoltsRead.Location = new System.Drawing.Point(8, 144);
			this.lblVoltsRead.Name = "lblVoltsRead";
			this.lblVoltsRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblVoltsRead.Size = new System.Drawing.Size(321, 33);
			this.lblVoltsRead.TabIndex = 5;
			this.lblVoltsRead.Text = "Converted Value: the channel number and the 12-bit value after separation of channel bits from data bits:";
			//
			// _lblShowRaw_9
			//
			this._lblShowRaw_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_9.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_9.Location = new System.Drawing.Point(296, 112);
			this._lblShowRaw_9.Name = "_lblShowRaw_9";
			this._lblShowRaw_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_9.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_9.TabIndex = 15;
			this._lblShowRaw_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_8
			//
			this._lblShowRaw_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_8.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_8.Location = new System.Drawing.Point(224, 112);
			this._lblShowRaw_8.Name = "_lblShowRaw_8";
			this._lblShowRaw_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_8.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_8.TabIndex = 14;
			this._lblShowRaw_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_7
			//
			this._lblShowRaw_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_7.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_7.Location = new System.Drawing.Point(152, 112);
			this._lblShowRaw_7.Name = "_lblShowRaw_7";
			this._lblShowRaw_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_7.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_7.TabIndex = 13;
			this._lblShowRaw_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_6
			//
			this._lblShowRaw_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_6.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_6.Location = new System.Drawing.Point(80, 112);
			this._lblShowRaw_6.Name = "_lblShowRaw_6";
			this._lblShowRaw_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_6.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_6.TabIndex = 12;
			this._lblShowRaw_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_5
			//
			this._lblShowRaw_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_5.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_5.Location = new System.Drawing.Point(8, 112);
			this._lblShowRaw_5.Name = "_lblShowRaw_5";
			this._lblShowRaw_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_5.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_5.TabIndex = 11;
			this._lblShowRaw_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_4
			//
			this._lblShowRaw_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_4.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_4.Location = new System.Drawing.Point(296, 88);
			this._lblShowRaw_4.Name = "_lblShowRaw_4";
			this._lblShowRaw_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_4.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_4.TabIndex = 10;
			this._lblShowRaw_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_3
			//
			this._lblShowRaw_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_3.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_3.Location = new System.Drawing.Point(224, 88);
			this._lblShowRaw_3.Name = "_lblShowRaw_3";
			this._lblShowRaw_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_3.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_3.TabIndex = 9;
			this._lblShowRaw_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_2
			//
			this._lblShowRaw_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_2.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_2.Location = new System.Drawing.Point(152, 88);
			this._lblShowRaw_2.Name = "_lblShowRaw_2";
			this._lblShowRaw_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_2.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_2.TabIndex = 8;
			this._lblShowRaw_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_1
			//
			this._lblShowRaw_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_1.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_1.Location = new System.Drawing.Point(80, 88);
			this._lblShowRaw_1.Name = "_lblShowRaw_1";
			this._lblShowRaw_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_1.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_1.TabIndex = 7;
			this._lblShowRaw_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblShowRaw_0
			//
			this._lblShowRaw_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblShowRaw_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblShowRaw_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblShowRaw_0.ForeColor = System.Drawing.Color.Blue;
			this._lblShowRaw_0.Location = new System.Drawing.Point(8, 88);
			this._lblShowRaw_0.Name = "_lblShowRaw_0";
			this._lblShowRaw_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblShowRaw_0.Size = new System.Drawing.Size(65, 17);
			this._lblShowRaw_0.TabIndex = 2;
			this._lblShowRaw_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblRawData
			//
			this.lblRawData.BackColor = System.Drawing.SystemColors.Window;
			this.lblRawData.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblRawData.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblRawData.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblRawData.Location = new System.Drawing.Point(8, 64);
			this.lblRawData.Name = "lblRawData";
			this.lblRawData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblRawData.Size = new System.Drawing.Size(265, 17);
			this.lblRawData.TabIndex = 0;
			this.lblRawData.Text = "Value: the 16-bit integer read from the board:";
			//
			// lblStatus
			//
			this.lblStatus.BackColor = System.Drawing.SystemColors.Window;
			this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblStatus.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblStatus.ForeColor = System.Drawing.Color.Blue;
			this.lblStatus.Location = new System.Drawing.Point(16, 40);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblStatus.Size = new System.Drawing.Size(337, 17);
			this.lblStatus.TabIndex = 25;
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
			this.lblDemoFunction.Size = new System.Drawing.Size(382, 25);
			this.lblDemoFunction.TabIndex = 1;
			this.lblDemoFunction.Text = "Demonstration of manual conversion of data";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDataDisplay
			//
			this.AcceptButton = this.cmdStartConvert;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(400, 299);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.txtHighChan, this.cmdQuit, this.cmdStartConvert, this.cmdStopBackground, this.lbl, this._lblConvData_9, this._lblConvData_8, this._lblConvData_7, this._lblConvData_6, this._lblConvData_5, this._lblConvData_4, this._lblConvData_3, this._lblConvData_2, this._lblConvData_1, this._lblConvData_0, this.lblVoltsRead, this._lblShowRaw_9, this._lblShowRaw_8, this._lblShowRaw_7, this._lblShowRaw_6, this._lblShowRaw_5, this._lblShowRaw_4, this._lblShowRaw_3, this._lblShowRaw_2, this._lblShowRaw_1, this._lblShowRaw_0, this.lblRawData, this.lblStatus, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(155, 101);
			this.Name = "frmDataDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Manual Conversion";
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
	     


		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdQuit.Click */
		{
			MccDaq.ErrorInfo ULStat;

			ULStat = MccDaq.MccService.WinBufFree(MemHandle); //  Free up memory for use by other programs
			

			Application.Exit();
		}


		private void cmdStartConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartConvert.Click */
		{
			MccDaq.ErrorInfo ULStat;
			MccDaq.Range Range;
			MccDaq.ScanOptions Options;
			int Rate;
			int Count;
			int LowChan;

			cmdStartConvert.Enabled = false;
			cmdQuit.Enabled = false;
			cmdStopBackground.Enabled = true;

			// Collect the values by calling MccDaq.MccBoard.AInScan function in background mode
			//   Parameters:
			//      LowChan    :the first channel of the scan
			//      HighChan   :the last channel of the scan
			//      Count      :the total number of A/D samples to collect
			//      Rate       :sample rate in samples per second
			//      Range      :the range for the board
			//      MemHandle  :Handle for Windows buffer to store data in
			//      Options    :data collection options
			LowChan = 0;
			HighChan = int.Parse(txtHighChan.Text);
			if (HighChan > 7) HighChan = 7;
			txtHighChan.Text = HighChan.ToString();

			Count = NumPoints;						//  total number of data points to collect
			Rate = 3125;								//  per channel sampling rate ((samples per second) per channel)
			Options = MccDaq.ScanOptions.Background;	//  collect data in BACKGROUND mode
														// as 16-bit values (no conversion)
			Range = MccDaq.Range.Bip5Volts; //  set the range

			ULStat = DaqBoard.AInScan( LowChan, HighChan, Count, ref Rate, Range, MemHandle, Options);
			

			// during the background operation, check the status using a timer, then print the values
			tmrCheckStatus.Enabled = true;
		}


		private void cmdStopBackground_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopBackground.Click */
		{
			cmdQuit.Enabled = true;
			cmdStopBackground.Enabled = false;
			UserTerm = 1;
		}


		private void Convert()
		{
			int channel;
			short K;
			int CurDataValue;

			// Show the data that were collected
			for(K=0; K<=NumPoints - 1; ++K)
			lblShowRaw[K].Text = ADData[K].ToString("D");

			// Manually convert the 16-bit values to 12-bit values
			for (K=0; K<=NumPoints - 1; ++K)
			{
			CurDataValue = System.Convert.ToInt32(ADData[K]);

				// find the channel number in the first 4-bits
				channel = CurDataValue  & 0x0f; // AND Mask with 15

				// retrieve the data value from the next 12-bits
				//  and put them into ConvData() array
				ConvData[K] = System.Convert.ToUInt16(CurDataValue>>4); 

				lblConvData[K].Text = channel.ToString("0") + "," + ConvData[K].ToString("D");
			}

		}




		private void tmrCheckStatus_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrCheckStatus.Tick */
		{
			int CurIndex;
			int CurCount;
			short Status;

			tmrCheckStatus.Stop();

			// Check the current status of the background data collection
			//   Parameters:
			//      Status     :current status of the background data collection
			//      CurCount   :current number of samples collected
			//      CurIndex   :index to the data buffer pointing to the last value transferred
			//      FunctionType: A/D operation (MccDaq.FunctionType.AiFunction)
			MccDaq.ErrorInfo ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AiFunction);
			


			//  check if the background operation has finished
			if ((Status == MccDaq.MccBoard.Idle ) || (UserTerm == 1))
			{
				lblStatus.Text = "Data collection finished.";

				// the background operation must be explicitly stopped
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
				

				ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out ADData[0], FirstPoint, NumPoints);


				cmdStartConvert.Enabled = true;
				cmdQuit.Enabled = true;
				cmdStopBackground.Enabled = false;
				Convert();
			}
			else
			{
				lblStatus.Text = "Background operation in progress.";
				tmrCheckStatus.Start();
			}

			if (UserTerm == 1)
			{
				lblStatus.Text = "Data collection terminated by user.";
				UserTerm = 0;
			}

		}

	}
}