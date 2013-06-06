// ==============================================================================
//
//  File:                         ULDI03.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DInScan()
//
//  Purpose:                      Reads a digital input port
//                                at specified rate and number
//                                of samples.
//
//  Demonstration:                Configures FirstPortA and
//                                FirstPortB for input and
//                                reads the value on the port.
//
//  Other Library Calls:          MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must support paced Digital input
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

namespace ULDI03
{
	public class frmDScan : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopRead;
		public Button cmdReadDIn;
		public Button cmdTemp;
		public Timer tmrCheckStatus;
		public Label _lblDataRead_9;
		public Label _lblDataRead_4;
		public Label _lblDataRead_8;
		public Label _lblDataRead_3;
		public Label _lblDataRead_7;
		public Label _lblDataRead_2;
		public Label _lblDataRead_6;
		public Label _lblDataRead_1;
		public Label _lblDataRead_5;
		public Label _lblDataRead_0;
		public Label lblBGStat;
		public Label lblShowIndex;
		public Label lblShowCount;
		public Label lblShowStat;
		public Label lblIndex;
		public Label lblCount;
		public Label lblStatus;
		public Label lblFunction;

		public Label[] lblDataRead;


		private MccDaq.MccBoard DaqBoard;

		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalIn; //  set direction of port to input
		const int NumPoints = 500;
		const int FirstPoint = 0;

		private ushort[] DataBuffer = new ushort[NumPoints];
		private int MemHandle;
		private int Count;
		private MccDaq.DigitalPortType PortNum;
		private short Force;

	 
		public frmDScan()
		{
	        
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			lblDataRead = (new Label[]{_lblDataRead_0, _lblDataRead_1, _lblDataRead_2, _lblDataRead_3, _lblDataRead_4,
									_lblDataRead_5, _lblDataRead_6, _lblDataRead_7, _lblDataRead_8, _lblDataRead_9});

			//  Initiate error handling
			//   activating error handling will trap errors like
			//   bad channel numbers and non-configured conditions.
			//   Parameters:
			//     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
			
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
			

			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);

			// set aside memory to hold data
			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			

			//  configure FirstPortA for digital input
			//   Parameters:
			//     PortNum    :the input port
			//     Direction  :sets the port for input or output
			PortNum = MccDaq.DigitalPortType.FirstPortA;
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);
			

			// configure FirstPortA & FirstPortB for digital input
			//   Parameters:
			//      PortNum    :the input port
			//      Direction  :sets the port for input or output
			PortNum = MccDaq.DigitalPortType.FirstPortB;
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);
			

			Force = 0;
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
				
				// make sure bacground operation is stopped and all memory 
				//  is freed
				DaqBoard.StopBackground(MccDaq.FunctionType.DiFunction);
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
			this.cmdStopRead = new System.Windows.Forms.Button();
			this.cmdReadDIn = new System.Windows.Forms.Button();
			this.cmdTemp = new System.Windows.Forms.Button();
			this.tmrCheckStatus = new System.Windows.Forms.Timer(this.components);
			this._lblDataRead_9 = new System.Windows.Forms.Label();
			this._lblDataRead_4 = new System.Windows.Forms.Label();
			this._lblDataRead_8 = new System.Windows.Forms.Label();
			this._lblDataRead_3 = new System.Windows.Forms.Label();
			this._lblDataRead_7 = new System.Windows.Forms.Label();
			this._lblDataRead_2 = new System.Windows.Forms.Label();
			this._lblDataRead_6 = new System.Windows.Forms.Label();
			this._lblDataRead_1 = new System.Windows.Forms.Label();
			this._lblDataRead_5 = new System.Windows.Forms.Label();
			this._lblDataRead_0 = new System.Windows.Forms.Label();
			this.lblBGStat = new System.Windows.Forms.Label();
			this.lblShowIndex = new System.Windows.Forms.Label();
			this.lblShowCount = new System.Windows.Forms.Label();
			this.lblShowStat = new System.Windows.Forms.Label();
			this.lblIndex = new System.Windows.Forms.Label();
			this.lblCount = new System.Windows.Forms.Label();
			this.lblStatus = new System.Windows.Forms.Label();
			this.lblFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopRead
			//
			this.cmdStopRead.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopRead.Location = new System.Drawing.Point(232, 280);
			this.cmdStopRead.Name = "cmdStopRead";
			this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopRead.Size = new System.Drawing.Size(81, 33);
			this.cmdStopRead.TabIndex = 1;
			this.cmdStopRead.Text = "Quit";
			this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
			//
			// cmdReadDIn
			//
			this.cmdReadDIn.BackColor = System.Drawing.SystemColors.Control;
			this.cmdReadDIn.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdReadDIn.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdReadDIn.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdReadDIn.Location = new System.Drawing.Point(128, 280);
			this.cmdReadDIn.Name = "cmdReadDIn";
			this.cmdReadDIn.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdReadDIn.Size = new System.Drawing.Size(81, 33);
			this.cmdReadDIn.TabIndex = 0;
			this.cmdReadDIn.Text = "Read";
			this.cmdReadDIn.Click += new System.EventHandler(this.cmdReadDIn_Click);
			//
			// cmdTemp
			//
			this.cmdTemp.BackColor = System.Drawing.SystemColors.Control;
			this.cmdTemp.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdTemp.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdTemp.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdTemp.Location = new System.Drawing.Point(32, 280);
			this.cmdTemp.Name = "cmdTemp";
			this.cmdTemp.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdTemp.Size = new System.Drawing.Size(81, 33);
			this.cmdTemp.TabIndex = 2;
			this.cmdTemp.Text = "Force";
			this.cmdTemp.Click += new System.EventHandler(this.cmdTemp_Click);
			//
			// tmrCheckStatus
			//
			this.tmrCheckStatus.Interval = 300;
			this.tmrCheckStatus.Tick += new System.EventHandler(this.tmrCheckStatus_Tick);
			//
			// _lblDataRead_9
			//
			this._lblDataRead_9.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_9.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_9.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_9.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_9.Location = new System.Drawing.Point(240, 248);
			this._lblDataRead_9.Name = "_lblDataRead_9";
			this._lblDataRead_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_9.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_9.TabIndex = 7;
			this._lblDataRead_9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_4
			//
			this._lblDataRead_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_4.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_4.Location = new System.Drawing.Point(112, 248);
			this._lblDataRead_4.Name = "_lblDataRead_4";
			this._lblDataRead_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_4.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_4.TabIndex = 12;
			this._lblDataRead_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_8
			//
			this._lblDataRead_8.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_8.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_8.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_8.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_8.Location = new System.Drawing.Point(240, 224);
			this._lblDataRead_8.Name = "_lblDataRead_8";
			this._lblDataRead_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_8.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_8.TabIndex = 8;
			this._lblDataRead_8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_3
			//
			this._lblDataRead_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_3.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_3.Location = new System.Drawing.Point(112, 224);
			this._lblDataRead_3.Name = "_lblDataRead_3";
			this._lblDataRead_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_3.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_3.TabIndex = 13;
			this._lblDataRead_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_7
			//
			this._lblDataRead_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_7.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_7.Location = new System.Drawing.Point(240, 200);
			this._lblDataRead_7.Name = "_lblDataRead_7";
			this._lblDataRead_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_7.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_7.TabIndex = 9;
			this._lblDataRead_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_2
			//
			this._lblDataRead_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_2.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_2.Location = new System.Drawing.Point(112, 200);
			this._lblDataRead_2.Name = "_lblDataRead_2";
			this._lblDataRead_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_2.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_2.TabIndex = 14;
			this._lblDataRead_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_6
			//
			this._lblDataRead_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_6.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_6.Location = new System.Drawing.Point(240, 176);
			this._lblDataRead_6.Name = "_lblDataRead_6";
			this._lblDataRead_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_6.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_6.TabIndex = 10;
			this._lblDataRead_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_1
			//
			this._lblDataRead_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_1.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_1.Location = new System.Drawing.Point(112, 176);
			this._lblDataRead_1.Name = "_lblDataRead_1";
			this._lblDataRead_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_1.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_1.TabIndex = 15;
			this._lblDataRead_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_5
			//
			this._lblDataRead_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_5.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_5.Location = new System.Drawing.Point(240, 152);
			this._lblDataRead_5.Name = "_lblDataRead_5";
			this._lblDataRead_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_5.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_5.TabIndex = 11;
			this._lblDataRead_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblDataRead_0
			//
			this._lblDataRead_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblDataRead_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblDataRead_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblDataRead_0.ForeColor = System.Drawing.Color.Blue;
			this._lblDataRead_0.Location = new System.Drawing.Point(112, 152);
			this._lblDataRead_0.Name = "_lblDataRead_0";
			this._lblDataRead_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblDataRead_0.Size = new System.Drawing.Size(57, 17);
			this._lblDataRead_0.TabIndex = 16;
			this._lblDataRead_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblBGStat
			//
			this.lblBGStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblBGStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblBGStat.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblBGStat.ForeColor = System.Drawing.Color.Blue;
			this.lblBGStat.Location = new System.Drawing.Point(84, 124);
			this.lblBGStat.Name = "lblBGStat";
			this.lblBGStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblBGStat.Size = new System.Drawing.Size(189, 17);
			this.lblBGStat.TabIndex = 3;
			//
			// lblShowIndex
			//
			this.lblShowIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowIndex.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowIndex.ForeColor = System.Drawing.Color.Blue;
			this.lblShowIndex.Location = new System.Drawing.Point(232, 88);
			this.lblShowIndex.Name = "lblShowIndex";
			this.lblShowIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowIndex.Size = new System.Drawing.Size(81, 17);
			this.lblShowIndex.TabIndex = 4;
			this.lblShowIndex.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblShowCount
			//
			this.lblShowCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCount.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowCount.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCount.Location = new System.Drawing.Point(136, 88);
			this.lblShowCount.Name = "lblShowCount";
			this.lblShowCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowCount.Size = new System.Drawing.Size(81, 17);
			this.lblShowCount.TabIndex = 5;
			this.lblShowCount.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblShowStat
			//
			this.lblShowStat.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowStat.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowStat.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowStat.ForeColor = System.Drawing.Color.Blue;
			this.lblShowStat.Location = new System.Drawing.Point(40, 88);
			this.lblShowStat.Name = "lblShowStat";
			this.lblShowStat.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowStat.Size = new System.Drawing.Size(81, 17);
			this.lblShowStat.TabIndex = 6;
			this.lblShowStat.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblIndex
			//
			this.lblIndex.BackColor = System.Drawing.SystemColors.Window;
			this.lblIndex.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblIndex.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblIndex.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblIndex.Location = new System.Drawing.Point(232, 64);
			this.lblIndex.Name = "lblIndex";
			this.lblIndex.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblIndex.Size = new System.Drawing.Size(81, 17);
			this.lblIndex.TabIndex = 20;
			this.lblIndex.Text = "Index";
			this.lblIndex.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblCount
			//
			this.lblCount.BackColor = System.Drawing.SystemColors.Window;
			this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCount.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblCount.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCount.Location = new System.Drawing.Point(136, 64);
			this.lblCount.Name = "lblCount";
			this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCount.Size = new System.Drawing.Size(81, 17);
			this.lblCount.TabIndex = 19;
			this.lblCount.Text = "Count";
			this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblStatus
			//
			this.lblStatus.BackColor = System.Drawing.SystemColors.Window;
			this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblStatus.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblStatus.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblStatus.Location = new System.Drawing.Point(40, 64);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblStatus.Size = new System.Drawing.Size(81, 17);
			this.lblStatus.TabIndex = 18;
			this.lblStatus.Text = "Status";
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblFunction
			//
			this.lblFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFunction.Location = new System.Drawing.Point(24, 16);
			this.lblFunction.Name = "lblFunction";
			this.lblFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFunction.Size = new System.Drawing.Size(281, 25);
			this.lblFunction.TabIndex = 17;
			this.lblFunction.Text = "Mccdaq.MccBoard.DInScan() Example Program";
			this.lblFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDScan
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(361, 322);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopRead, this.cmdReadDIn, this.cmdTemp, this._lblDataRead_9, this._lblDataRead_4, this._lblDataRead_8, this._lblDataRead_3, this._lblDataRead_7, this._lblDataRead_2, this._lblDataRead_6, this._lblDataRead_1, this._lblDataRead_5, this._lblDataRead_0, this.lblBGStat, this.lblShowIndex, this.lblShowCount, this.lblShowStat, this.lblIndex, this.lblCount, this.lblStatus, this.lblFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmDScan";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Digital Input";
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmDScan());
		}
	    

		
		private void cmdReadDIn_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdReadDIn.Click */
		{
			// read the digital input and display
			//   Parameters:
			//      PortNum      :the input port
			//      Count        :number of times to read digital input
			//      Rate         :sample rate in samples/second
			//      DataBuffer() :the array for the digital input values read from the port
			//      Options      :data collection options
			Count = NumPoints;
			int Rate = 100;
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.WordXfer  
										| MccDaq.ScanOptions.Background;
			MccDaq.ErrorInfo ULStat = DaqBoard.DInScan( PortNum, Count, ref Rate, MemHandle, Options);
			

			tmrCheckStatus.Enabled = true;
		}


		private void cmdStopRead_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopRead.Click */
		{

			MccDaq.ErrorInfo ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DiFunction);
			

			ULStat = MccDaq.MccService.WinBufFree(MemHandle);
			
			MemHandle = 0;

			Application.Exit();

		}


		private void cmdTemp_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdTemp.Click */
		{
			Force = 1;
		}


		private void ShowData()
		{
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out DataBuffer[0], FirstPoint, Count);
			

			for (int i=0; i<10; ++i)
				lblDataRead[i].Text = "0x"+DataBuffer[i].ToString("x");
		}


		private void tmrCheckStatus_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrCheckStatus.Tick */
		{
			
			tmrCheckStatus.Stop();

			int CurIndex;
			int CurCount;
			short Status;
			MccDaq.ErrorInfo ULStat = DaqBoard.GetStatus( out Status, out CurCount, out CurIndex, MccDaq.FunctionType.DiFunction);
			

			lblShowStat.Text = Status.ToString("0");
			lblShowCount.Text = CurCount.ToString("0");
			lblShowIndex.Text = CurIndex.ToString("0");
			if (Status == MccDaq.MccBoard.Running)
				lblBGStat.Text = "Background operation running";
			else
				lblBGStat.Text = "Background operation idle";
	
			if ((CurCount == NumPoints || Status == 0 ) || (Force == 1))
			{
				ULStat = DaqBoard.StopBackground(MccDaq.FunctionType.DiFunction);

				ShowData();
			}
			else
				tmrCheckStatus.Start();
		}

	}
}