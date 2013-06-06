// ==============================================================================
//
//  File:                         ULAIO01.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.GetStatus()
//                                Mccdaq.MccBoard.StopBackground()
//
//  Purpose:                      Run Simultaneous input/output functions using
//                                the same board.
//
//  Demonstration:                Mccdaq.MccBoard.AoutScan function generates a ramp signal
//                                while Mccdaq.MccBoard.AinScan Displays the analog input on
//                                up to eight channels.
//
//  Other Library Calls:          Mccdaq.MccBoard.AinScan()
//                                Mccdaq.MccBoard.AoutScan()
//                                Mccdaq.MccBoard.ErrHandling()
//
//  Special Requirements:         Board 0 must support simultaneous paced input
//                                and paced output. See hardware documentation.
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

namespace ULAIO01
{
	public class frmStatusDisplay : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopADConvert;
		public Button cmdStartDABgnd;
		public Button cmdStopDAConvert;
		public TextBox txtHighChan;
		public Button cmdQuit;
		public Timer tmrCheckStatus;
		public Button cmdStartADBgnd;
		public Label lblCount;
		public Label Label2;
		public Label Label5;
		public Label Label4;
		public Label Label3;
		public Label lblShowDACount;
		public Label lblShowDAIndex;
		public Label lblShowDAStat;
		public Label Label1;
		public Label lblShowADCount;
		public Label lblShowADIndex;
		public Label lblIndex;
		public Label lblShowADStat;
		public Label lblStatus;
		public Label _lblADData_7;
		public Label lblChan7;
		public Label _lblADData_3;
		public Label lblChan3;
		public Label _lblADData_6;
		public Label lblChan6;
		public Label _lblADData_2;
		public Label lblChan2;
		public Label _lblADData_5;
		public Label lblChan5;
		public Label _lblADData_1;
		public Label lblChan1;
		public Label _lblADData_4;
		public Label lblChan4;
		public Label _lblADData_0;
		public Label lblChan0;
		public Label lblDemoFunction;
		
		public Label[] lblADData;

		const int NumPoints = 30000; //  Number of data points to collect
		const int FirstPoint = 0; //  set first element in buffer to transfer to array

		private MccDaq.MccBoard DaqBoard;
		private int HighChan;
		private ushort[] ADData = new ushort[NumPoints]; // array to hold the input values
		
		private int ADMemHandle;								 //  define a variable to contain the handle for
														//  memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		private int DAMemHandle;								 //  define a variable to contain the handle for 
														//  memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		private ushort[] DAData = new ushort[NumPoints];		 // array to hold the output values
		private short ADUserTerm;								 //  flag to stop paced A/D manually	
		private short DAUserTerm;								 //  flag to stop paced D/A manually
		


		public frmStatusDisplay()
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

			//  set aside memory to hold A/D data
			ADMemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			
		
			//  set aside memory to hold D/A data
			DAMemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			

			//  Generate D/A ramp data to be output via MccDaq.MccBoard.AOutScan function
			ushort FScale =0;
			DaqBoard.FromEngUnits(MccDaq.Range.Bip5Volts, 5.00f, out FScale);
			for (int i=0; i<=NumPoints - 1; ++i)
				DAData[i] = (ushort)((FScale*i)/NumPoints);
		

			// transfer the DAData to the DA buffer 
			ULStat = MccDaq.MccService.WinArrayToBuf( ref DAData[0], DAMemHandle, FirstPoint, NumPoints);

			lblADData = (new Label[] {_lblADData_0, _lblADData_1, _lblADData_2, _lblADData_3,
									_lblADData_4, _lblADData_5, _lblADData_6, _lblADData_7});


		}

		// Form overrides dispose to clean up the component list.
		protected override void  Dispose(bool Disposing)
		{
			if (Disposing)
			{
				//make sure everything is shustdown
				DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
				DaqBoard.StopBackground(MccDaq.FunctionType.AoFunction);

				if (components != null)
				{
					components.Dispose();
				}

				if (ADMemHandle!=0)
					MccDaq.MccService.WinBufFree(ADMemHandle);

				if (DAMemHandle!=0)
					MccDaq.MccService.WinBufFree(DAMemHandle);

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
			this.cmdStopADConvert = new System.Windows.Forms.Button();
			this.cmdStartDABgnd = new System.Windows.Forms.Button();
			this.cmdStopDAConvert = new System.Windows.Forms.Button();
			this.txtHighChan = new System.Windows.Forms.TextBox();
			this.cmdQuit = new System.Windows.Forms.Button();
			this.tmrCheckStatus = new System.Windows.Forms.Timer(this.components);
			this.cmdStartADBgnd = new System.Windows.Forms.Button();
			this.lblCount = new System.Windows.Forms.Label();
			this.Label2 = new System.Windows.Forms.Label();
			this.Label5 = new System.Windows.Forms.Label();
			this.Label4 = new System.Windows.Forms.Label();
			this.Label3 = new System.Windows.Forms.Label();
			this.lblShowDACount = new System.Windows.Forms.Label();
			this.lblShowDAIndex = new System.Windows.Forms.Label();
			this.lblShowDAStat = new System.Windows.Forms.Label();
			this.Label1 = new System.Windows.Forms.Label();
			this.lblShowADCount = new System.Windows.Forms.Label();
			this.lblShowADIndex = new System.Windows.Forms.Label();
			this.lblIndex = new System.Windows.Forms.Label();
			this.lblShowADStat = new System.Windows.Forms.Label();
			this.lblStatus = new System.Windows.Forms.Label();
			this._lblADData_7 = new System.Windows.Forms.Label();
			this.lblChan7 = new System.Windows.Forms.Label();
			this._lblADData_3 = new System.Windows.Forms.Label();
			this.lblChan3 = new System.Windows.Forms.Label();
			this._lblADData_6 = new System.Windows.Forms.Label();
			this.lblChan6 = new System.Windows.Forms.Label();
			this._lblADData_2 = new System.Windows.Forms.Label();
			this.lblChan2 = new System.Windows.Forms.Label();
			this._lblADData_5 = new System.Windows.Forms.Label();
			this.lblChan5 = new System.Windows.Forms.Label();
			this._lblADData_1 = new System.Windows.Forms.Label();
			this.lblChan1 = new System.Windows.Forms.Label();
			this._lblADData_4 = new System.Windows.Forms.Label();
			this.lblChan4 = new System.Windows.Forms.Label();
			this._lblADData_0 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopADConvert
			//
			this.cmdStopADConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopADConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopADConvert.Enabled = false;
			this.cmdStopADConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopADConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopADConvert.Location = new System.Drawing.Point(56, 120);
			this.cmdStopADConvert.Name = "cmdStopADConvert";
			this.cmdStopADConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopADConvert.Size = new System.Drawing.Size(204, 27);
			this.cmdStopADConvert.TabIndex = 33;
			this.cmdStopADConvert.Text = "Stop A/D Background Operation";
			this.cmdStopADConvert.Visible = false;
			this.cmdStopADConvert.Click += new System.EventHandler(this.cmdStopADConvert_Click);
			//
			// cmdStartDABgnd
			//
			this.cmdStartDABgnd.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartDABgnd.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartDABgnd.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartDABgnd.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartDABgnd.Location = new System.Drawing.Point(352, 120);
			this.cmdStartDABgnd.Name = "cmdStartDABgnd";
			this.cmdStartDABgnd.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartDABgnd.Size = new System.Drawing.Size(204, 27);
			this.cmdStartDABgnd.TabIndex = 32;
			this.cmdStartDABgnd.Text = "Start D/A Background Operation";
			this.cmdStartDABgnd.Click += new System.EventHandler(this.cmdStartDABgnd_Click);
			//
			// cmdStopDAConvert
			//
			this.cmdStopDAConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopDAConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopDAConvert.Enabled = false;
			this.cmdStopDAConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopDAConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopDAConvert.Location = new System.Drawing.Point(352, 120);
			this.cmdStopDAConvert.Name = "cmdStopDAConvert";
			this.cmdStopDAConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopDAConvert.Size = new System.Drawing.Size(204, 27);
			this.cmdStopDAConvert.TabIndex = 31;
			this.cmdStopDAConvert.Text = "Stop D/A Background Operation";
			this.cmdStopDAConvert.Visible = false;
			this.cmdStopDAConvert.Click += new System.EventHandler(this.cmdStopDAConvert_Click);
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
			this.txtHighChan.Location = new System.Drawing.Point(208, 160);
			this.txtHighChan.MaxLength = 0;
			this.txtHighChan.Name = "txtHighChan";
			this.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtHighChan.Size = new System.Drawing.Size(33, 17);
			this.txtHighChan.TabIndex = 25;
			this.txtHighChan.Text = "3";
			//
			// cmdQuit
			//
			this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
			this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdQuit.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdQuit.Location = new System.Drawing.Point(288, 296);
			this.cmdQuit.Name = "cmdQuit";
			this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdQuit.Size = new System.Drawing.Size(52, 26);
			this.cmdQuit.TabIndex = 18;
			this.cmdQuit.Text = "Quit";
			this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
			//
			// tmrCheckStatus
			//
			this.tmrCheckStatus.Interval = 200;
			this.tmrCheckStatus.Tick += new System.EventHandler(this.tmrCheckStatus_Tick);
			//
			// cmdStartADBgnd
			//
			this.cmdStartADBgnd.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartADBgnd.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartADBgnd.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartADBgnd.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartADBgnd.Location = new System.Drawing.Point(56, 120);
			this.cmdStartADBgnd.Name = "cmdStartADBgnd";
			this.cmdStartADBgnd.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartADBgnd.Size = new System.Drawing.Size(204, 27);
			this.cmdStartADBgnd.TabIndex = 17;
			this.cmdStartADBgnd.Text = "Start A/D Background Operation";
			this.cmdStartADBgnd.Click += new System.EventHandler(this.cmdStartADBgnd_Click);
			//
			// lblCount
			//
			this.lblCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCount.Location = new System.Drawing.Point(70, 310);
			this.lblCount.Name = "lblCount";
			this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCount.Size = new System.Drawing.Size(124, 14);
			this.lblCount.TabIndex = 36;
			this.lblCount.Text = "Current A/D Count:";
			this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// Label2
			//
			this.Label2.BackColor = System.Drawing.SystemColors.Window;
			this.Label2.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label2.Location = new System.Drawing.Point(360, 310);
			this.Label2.Name = "Label2";
			this.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label2.Size = new System.Drawing.Size(135, 14);
			this.Label2.TabIndex = 35;
			this.Label2.Text = "Current D/A Count:";
			this.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// Label5
			//
			this.Label5.BackColor = System.Drawing.SystemColors.Window;
			this.Label5.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label5.Location = new System.Drawing.Point(104, 48);
			this.Label5.Name = "Label5";
			this.Label5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label5.Size = new System.Drawing.Size(385, 33);
			this.Label5.TabIndex = 34;
			this.Label5.Text = "Board 0 must support simultaneous paced input and paced output. For more inforamtion, see hardware documentation.";
			//
			// Label4
			//
			this.Label4.BackColor = System.Drawing.SystemColors.Window;
			this.Label4.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label4.Location = new System.Drawing.Point(307, 272);
			this.Label4.Name = "Label4";
			this.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label4.Size = new System.Drawing.Size(188, 14);
			this.Label4.TabIndex = 30;
			this.Label4.Text = "Status of D/A Background:";
			this.Label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// Label3
			//
			this.Label3.BackColor = System.Drawing.SystemColors.Window;
			this.Label3.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label3.Location = new System.Drawing.Point(360, 291);
			this.Label3.Name = "Label3";
			this.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label3.Size = new System.Drawing.Size(135, 19);
			this.Label3.TabIndex = 29;
			this.Label3.Text = "Current D/A Index:";
			this.Label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowDACount
			//
			this.lblShowDACount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowDACount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowDACount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowDACount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowDACount.Location = new System.Drawing.Point(504, 312);
			this.lblShowDACount.Name = "lblShowDACount";
			this.lblShowDACount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowDACount.Size = new System.Drawing.Size(65, 14);
			this.lblShowDACount.TabIndex = 28;
			//
			// lblShowDAIndex
			//
			this.lblShowDAIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowDAIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowDAIndex.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowDAIndex.ForeColor = System.Drawing.Color.Blue;
			this.lblShowDAIndex.Location = new System.Drawing.Point(496, 292);
			this.lblShowDAIndex.Name = "lblShowDAIndex";
			this.lblShowDAIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowDAIndex.Size = new System.Drawing.Size(71, 13);
			this.lblShowDAIndex.TabIndex = 27;
			//
			// lblShowDAStat
			//
			this.lblShowDAStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowDAStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowDAStat.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowDAStat.ForeColor = System.Drawing.Color.Blue;
			this.lblShowDAStat.Location = new System.Drawing.Point(496, 272);
			this.lblShowDAStat.Name = "lblShowDAStat";
			this.lblShowDAStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowDAStat.Size = new System.Drawing.Size(66, 14);
			this.lblShowDAStat.TabIndex = 26;
			//
			// Label1
			//
			this.Label1.BackColor = System.Drawing.SystemColors.Window;
			this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label1.Location = new System.Drawing.Point(80, 160);
			this.Label1.Name = "Label1";
			this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label1.Size = new System.Drawing.Size(120, 16);
			this.Label1.TabIndex = 24;
			this.Label1.Text = "Measure Channels 0 to";
			//
			// lblShowADCount
			//
			this.lblShowADCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowADCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowADCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowADCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowADCount.Location = new System.Drawing.Point(206, 312);
			this.lblShowADCount.Name = "lblShowADCount";
			this.lblShowADCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowADCount.Size = new System.Drawing.Size(73, 14);
			this.lblShowADCount.TabIndex = 23;
			//
			// lblShowADIndex
			//
			this.lblShowADIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowADIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowADIndex.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowADIndex.ForeColor = System.Drawing.Color.Blue;
			this.lblShowADIndex.Location = new System.Drawing.Point(206, 291);
			this.lblShowADIndex.Name = "lblShowADIndex";
			this.lblShowADIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowADIndex.Size = new System.Drawing.Size(67, 14);
			this.lblShowADIndex.TabIndex = 22;
			//
			// lblIndex
			//
			this.lblIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblIndex.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblIndex.Location = new System.Drawing.Point(67, 291);
			this.lblIndex.Name = "lblIndex";
			this.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblIndex.Size = new System.Drawing.Size(127, 14);
			this.lblIndex.TabIndex = 21;
			this.lblIndex.Text = "Current A/D Index:";
			this.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblShowADStat
			//
			this.lblShowADStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowADStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowADStat.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowADStat.ForeColor = System.Drawing.Color.Blue;
			this.lblShowADStat.Location = new System.Drawing.Point(200, 272);
			this.lblShowADStat.Name = "lblShowADStat";
			this.lblShowADStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowADStat.Size = new System.Drawing.Size(81, 22);
			this.lblShowADStat.TabIndex = 20;
			//
			// lblStatus
			//
			this.lblStatus.BackColor = System.Drawing.SystemColors.Window;
			this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblStatus.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblStatus.Location = new System.Drawing.Point(30, 272);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblStatus.Size = new System.Drawing.Size(164, 14);
			this.lblStatus.TabIndex = 19;
			this.lblStatus.Text = "Status of A/D Background:";
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblADData_7
			//
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Location = new System.Drawing.Point(272, 238);
			this._lblADData_7.Name = "_lblADData_7";
			this._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_7.Size = new System.Drawing.Size(65, 17);
			this._lblADData_7.TabIndex = 16;
			//
			// lblChan7
			//
			this.lblChan7.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan7.Location = new System.Drawing.Point(200, 238);
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
			this._lblADData_3.Location = new System.Drawing.Point(104, 238);
			this._lblADData_3.Name = "_lblADData_3";
			this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_3.Size = new System.Drawing.Size(65, 17);
			this._lblADData_3.TabIndex = 12;
			//
			// lblChan3
			//
			this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan3.Location = new System.Drawing.Point(32, 238);
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
			this._lblADData_6.Location = new System.Drawing.Point(272, 219);
			this._lblADData_6.Name = "_lblADData_6";
			this._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_6.Size = new System.Drawing.Size(65, 17);
			this._lblADData_6.TabIndex = 15;
			//
			// lblChan6
			//
			this.lblChan6.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan6.Location = new System.Drawing.Point(200, 219);
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
			this._lblADData_2.Location = new System.Drawing.Point(104, 219);
			this._lblADData_2.Name = "_lblADData_2";
			this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_2.Size = new System.Drawing.Size(65, 17);
			this._lblADData_2.TabIndex = 11;
			//
			// lblChan2
			//
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan2.Location = new System.Drawing.Point(32, 219);
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
			this._lblADData_5.Location = new System.Drawing.Point(272, 200);
			this._lblADData_5.Name = "_lblADData_5";
			this._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_5.Size = new System.Drawing.Size(65, 17);
			this._lblADData_5.TabIndex = 14;
			//
			// lblChan5
			//
			this.lblChan5.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan5.Location = new System.Drawing.Point(200, 200);
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
			this._lblADData_1.Location = new System.Drawing.Point(104, 200);
			this._lblADData_1.Name = "_lblADData_1";
			this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_1.Size = new System.Drawing.Size(65, 17);
			this._lblADData_1.TabIndex = 10;
			//
			// lblChan1
			//
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan1.Location = new System.Drawing.Point(32, 200);
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
			this._lblADData_4.Location = new System.Drawing.Point(272, 181);
			this._lblADData_4.Name = "_lblADData_4";
			this._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_4.Size = new System.Drawing.Size(65, 17);
			this._lblADData_4.TabIndex = 13;
			//
			// lblChan4
			//
			this.lblChan4.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan4.Location = new System.Drawing.Point(200, 181);
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
			this._lblADData_0.Location = new System.Drawing.Point(104, 181);
			this._lblADData_0.Name = "_lblADData_0";
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.Size = new System.Drawing.Size(65, 17);
			this._lblADData_0.TabIndex = 9;
			//
			// lblChan0
			//
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan0.Location = new System.Drawing.Point(32, 181);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.Size = new System.Drawing.Size(65, 17);
			this.lblChan0.TabIndex = 1;
			this.lblChan0.Text = "Channel 0:";
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(80, 8);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(417, 33);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of Simultaneous MccDaq.MccBoard.AInScan() and MccDaq.MccBoard.AoutScan ";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmStatusDisplay
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(611, 352);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopADConvert, this.cmdStartDABgnd, this.cmdStopDAConvert, this.txtHighChan, this.cmdQuit, this.cmdStartADBgnd, this.lblCount, this.Label2, this.Label5, this.Label4, this.Label3, this.lblShowDACount, this.lblShowDAIndex, this.lblShowDAStat, this.Label1, this.lblShowADCount, this.lblShowADIndex, this.lblIndex, this.lblShowADStat, this.lblStatus, this._lblADData_7, this.lblChan7, this._lblADData_3, this.lblChan3, this._lblADData_6, this.lblChan6, this._lblADData_2, this.lblChan2, this._lblADData_5, this.lblChan5, this._lblADData_1, this.lblChan1, this._lblADData_4, this.lblChan4, this._lblADData_0, this.lblChan0, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(188, 108);
			this.Name = "frmStatusDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Simultaneous AInScan() and AoutScan() ";
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmStatusDisplay());
		}
	    

	    

		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdQuit.Click */
		{
			// make sure all processes are shut down
			MccDaq.ErrorInfo ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
			

			ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AoFunction);
			

			//  Free up memory for use by other programs
			ULStat = MccDaq.MccService.WinBufFree(ADMemHandle); 
			
			ADMemHandle = 0;

			ULStat = MccDaq.MccService.WinBufFree(DAMemHandle);
			
			DAMemHandle = 0;

			Application.Exit();
		}


		private void cmdStopConvert_Click()
		{
			ADUserTerm = 1;
		}


		private void cmdStartADBgnd_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartADBgnd.Click */
		{
			cmdStartADBgnd.Enabled = false;
			cmdStartADBgnd.Visible = false;
			cmdStopADConvert.Enabled = true;
			cmdStopADConvert.Visible = true;
			cmdQuit.Enabled = false;
			ADUserTerm = 0; //  initialize user terminate flag

			//  Collect the values with MccDaq.MccBoard.AInScan()
			//   Parameters:
			//     LowChan    :the first channel of the scan
			//     HighChan   :the last channel of the scan
			//     Count      :the total number of A/D samples to collect
			//     Rate       :sample rate
			//     Range      :the range for the board
			//     MemHandle  :Handle for Windows buffer to store data in
			//     Options    :data collection options
			int LowChan = 0; //  first channel to acquire
			HighChan = int.Parse(txtHighChan.Text); //  last channel to acquire
			if ((HighChan > 7)) HighChan = 7;
			txtHighChan.Text = HighChan.ToString();

			int MccADCount = NumPoints; //  total number of data points to collect
			int MccADRate = 500; //  sampling rate (samples per second)
			MccDaq.Range Range = MccDaq.Range.Bip5Volts; //  set the range
			MccDaq.ScanOptions ADOptions = MccDaq.ScanOptions.ConvertData  //  return data as 12-bit values
										| MccDaq.ScanOptions.Background;  //  collect data in Background mode

			MccDaq.ErrorInfo ULStat = DaqBoard.AInScan( LowChan, HighChan, MccADCount, ref MccADRate, Range, ADMemHandle, ADOptions);
			

			int CurIndex = 0;
			int CurCount = 0;
			short Status = MccDaq.MccBoard.Idle;
			ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AiFunction);
			

			if (Status == MccDaq.MccBoard.Running)
			{
				lblShowADStat.Text = "Running";
				lblShowADCount.Text = CurCount.ToString("0");
				lblShowADIndex.Text = CurIndex.ToString("0");
			}

			tmrCheckStatus.Enabled = true;
		}


		private void cmdStartDABgnd_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartDABgnd.Click */
		{
			cmdStartDABgnd.Enabled = false;
			cmdStartDABgnd.Visible = false;
			cmdStopDAConvert.Enabled = true;
			cmdStopDAConvert.Visible = true;
			cmdQuit.Enabled = false;
			DAUserTerm = 0; //  initialize user terminate flag

			//  Collect the values with MccDaq.MccBoard.AOutScan()
			//   Parameters:
			//     LowDAChan  :the first channel of the scan
			//     HighDAChan :the last channel of the scan
			//     Count      :the total number of D/A samples to output
			//     Rate       :sample rate
			//     Range      :the range for the board
			//     DAData     :array of values to send to the scanned channels
			//     Options    :data output options
			int LowDAChan = 0; //  first channel to output
			int HighDAChan = 0; //  last channel to output
			int MccDACount = NumPoints; //  total number of data points to output
			int MccDARate = 1000; //  output rate (samples per second)
			MccDaq.ScanOptions DAOptions = MccDaq.ScanOptions.Background;
			MccDaq.Range Range = MccDaq.Range.Bip5Volts; //  set the range
			MccDaq.ErrorInfo ULStat = DaqBoard.AOutScan( LowDAChan, HighDAChan, MccDACount, ref MccDARate, Range, DAMemHandle, DAOptions);
			


			int CurIndex = 0;
			int CurCount = 0;
			short Status = MccDaq.MccBoard.Idle;
			ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.AoFunction);
			


			if (Status == MccDaq.MccBoard.Running)
			{
				lblShowDAStat.Text = "Running";
				lblShowDACount.Text = CurCount.ToString("0");
				lblShowDAIndex.Text = CurIndex.ToString("0");
			}

			tmrCheckStatus.Enabled = true;
		}


		private void cmdStopADConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopADConvert.Click */
		{
			ADUserTerm = 1;
		}


		private void cmdStopDAConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopDAConvert.Click */
		{
			DAUserTerm = 1;
		}



		private void tmrCheckStatus_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrCheckStatus.Tick */
		{
			int CurrValue;
			int TempCount;
	        
			tmrCheckStatus.Stop();
			
			//  This timer will check the status of the background data collection

			//  Parameters:
			//    Status     :current status of the background data collection
			//    CurCount   :current number of samples collected
			//    CurIndex   :index to the data buffer pointing to the start of the
			//                 most recently collected scan
			int ADCurIndex = 0;
			int ADCurCount = 0;
			short ADStatus = MccDaq.MccBoard.Idle;
			MccDaq.ErrorInfo ULStat = DaqBoard.GetStatus( out ADStatus, out ADCurCount, out ADCurIndex, MccDaq.FunctionType.AiFunction);
			
			lblShowADCount.Text = ADCurCount.ToString("0");
			lblShowADIndex.Text = ADCurIndex.ToString("0");

			//  Check if the background operation has finished. If it has, then
			//  transfer the data from the memory buffer set up by Windows to an
			//  array for use by Visual Basic
			//  The BACKGROUND operation must be explicitly stopped
			int LowChan=0;
			if ((ADStatus == MccDaq.MccBoard.Running ) && (ADUserTerm == 0))
			{
				lblShowADStat.Text = "Running";

				if (ADCurIndex > 0)
				{
					
					ULStat = MccDaq.MccService.WinBufToArray(ADMemHandle, out ADData[ADCurIndex], ADCurIndex, HighChan - LowChan + 1);
					


					for (int i=0; i<=HighChan; ++i)
					{
					TempCount = i + ADCurIndex;
					CurrValue = Convert.ToInt32(ADData[TempCount]);
					lblADData[i].Text = CurrValue.ToString("0");
					}
				}

			}
			else if ((ADStatus == MccDaq.MccBoard.Idle ) || (ADUserTerm == 1))
			{
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
				

				lblShowADStat.Text = "Idle";
				ADStatus = MccDaq.MccBoard.Idle;

				ULStat = MccDaq.MccService.WinBufToArray( ADMemHandle, out ADData[0], FirstPoint, NumPoints);
				


				for (int i=0; i<=HighChan; ++i)
				lblADData[i].Text = ADData[i].ToString("0");
	        

				for (int j=HighChan + 1; j<=7; ++j)
				lblADData[j].Text = "";

				cmdStartADBgnd.Enabled = true;
				cmdStartADBgnd.Visible = true;
				cmdStopADConvert.Enabled = false;
				cmdStopADConvert.Visible = false;
			}

			// ==========================================================
			int DACurIndex= 0;
			int DACurCount = 0;
			short DAStatus = MccDaq.MccBoard.Idle;
			ULStat = DaqBoard.GetStatus( out DAStatus, out DACurCount, out DACurIndex, MccDaq.FunctionType.AoFunction);
			

			lblShowDACount.Text = DACurCount.ToString("0");
			lblShowDAIndex.Text = DACurIndex.ToString("0");

			//  Check if the background operation has finished.
			if ((DAStatus == MccDaq.MccBoard.Running ) && (DAUserTerm == 0))
			{
				lblShowDAStat.Text = "Running";
			}
			else if ((DAStatus == 0 ) || (DAUserTerm == 1))
			{
				lblShowDAStat.Text = "Idle";
				DAStatus = MccDaq.MccBoard.Idle;
	            
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.AoFunction);

				cmdStartDABgnd.Enabled = true;
				cmdStartDABgnd.Visible = true;
				cmdStopDAConvert.Enabled = false;
				cmdStopDAConvert.Visible = false;
			}

			if ((ADStatus == MccDaq.MccBoard.Idle ) && (DAStatus == MccDaq.MccBoard.Idle))
			{
				cmdQuit.Enabled = true;
			}
			else
				tmrCheckStatus.Start();

		}

	}
}