// ==============================================================================
//
//  File:                         ULAO02.CS
//  Library Call Demonstrated:    Mccdaq.MccBoard.AOutScan()
//
//  Purpose:                      Writes to a range of D/A Output Channels.
//
//  Demonstration:                Sends a digital output to the D/A channels
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have 2 or more D/A converters.
//                                This function is designed for boards that
//                                support timed analog output.  It can be used
//                                for polled output boards but only for values
//                                of NumPoints up to the number of channels
//                                that the board supports (i.e., NumPoints =
//                                6 maximum for the six channel CIO-DDA06).
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

namespace ULAO02
{
	public class frmSendAData : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public Button cmdSendData;
		public Label Label1;
		public Label _lblAOutData_1;
		public Label _lblAOutData_0;
		public Label lblChan1;
		public Label lblChan0;
		public Label lblDemoFunction;

		public Label[] lblAOutData;

		const int NumPoints = 2;
		const int Count = NumPoints;

		private MccDaq.MccBoard DaqBoard;
		private ushort[] DAData = new ushort[NumPoints];
		private int MemHandle = 0;	//  define a variable to contain the handle for
									//  memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		private int FirstPoint;


		public frmSendAData()
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

			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); //  set aside memory to hold data
			

			//generate waveform
			ushort FScale =0;
			DaqBoard.FromEngUnits(MccDaq.Range.Bip5Volts, 5.0f, out FScale);
			for (int i=0; i<=NumPoints - 1; ++i)
				DAData[i] = Convert.ToUInt16((i * FScale)/NumPoints);

			//move waveform to buffer
			FirstPoint = 0;
			ULStat = MccDaq.MccService.WinArrayToBuf( ref DAData[0], MemHandle, FirstPoint, NumPoints);


			lblAOutData = (new Label[]{_lblAOutData_0, _lblAOutData_1});
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
			this.cmdEndProgram = new System.Windows.Forms.Button();
			this.cmdSendData = new System.Windows.Forms.Button();
			this.Label1 = new System.Windows.Forms.Label();
			this._lblAOutData_1 = new System.Windows.Forms.Label();
			this._lblAOutData_0 = new System.Windows.Forms.Label();
			this.lblChan1 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdEndProgram
			//
			this.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control;
			this.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdEndProgram.Location = new System.Drawing.Point(264, 168);
			this.cmdEndProgram.Name = "cmdEndProgram";
			this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdEndProgram.Size = new System.Drawing.Size(55, 26);
			this.cmdEndProgram.TabIndex = 1;
			this.cmdEndProgram.Text = "Quit";
			this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
			//
			// cmdSendData
			//
			this.cmdSendData.BackColor = System.Drawing.SystemColors.Control;
			this.cmdSendData.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdSendData.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdSendData.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdSendData.Location = new System.Drawing.Point(128, 48);
			this.cmdSendData.Name = "cmdSendData";
			this.cmdSendData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdSendData.Size = new System.Drawing.Size(81, 33);
			this.cmdSendData.TabIndex = 2;
			this.cmdSendData.Text = "Send Data";
			this.cmdSendData.Click += new System.EventHandler(this.cmdSendData_Click);
			//
			// Label1
			//
			this.Label1.BackColor = System.Drawing.SystemColors.Window;
			this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label1.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label1.ForeColor = System.Drawing.SystemColors.ControlText;
			this.Label1.Location = new System.Drawing.Point(40, 120);
			this.Label1.Name = "Label1";
			this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label1.Size = new System.Drawing.Size(57, 25);
			this.Label1.TabIndex = 7;
			this.Label1.Text = "Raw Data";
			this.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			//
			// _lblAOutData_1
			//
			this._lblAOutData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblAOutData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblAOutData_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblAOutData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblAOutData_1.Location = new System.Drawing.Point(176, 128);
			this._lblAOutData_1.Name = "_lblAOutData_1";
			this._lblAOutData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblAOutData_1.Size = new System.Drawing.Size(65, 17);
			this._lblAOutData_1.TabIndex = 6;
			this._lblAOutData_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblAOutData_0
			//
			this._lblAOutData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblAOutData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblAOutData_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblAOutData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblAOutData_0.Location = new System.Drawing.Point(96, 128);
			this._lblAOutData_0.Name = "_lblAOutData_0";
			this._lblAOutData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblAOutData_0.Size = new System.Drawing.Size(65, 17);
			this._lblAOutData_0.TabIndex = 3;
			this._lblAOutData_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan1
			//
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan1.Location = new System.Drawing.Point(176, 104);
			this.lblChan1.Name = "lblChan1";
			this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1.Size = new System.Drawing.Size(65, 17);
			this.lblChan1.TabIndex = 5;
			this.lblChan1.Text = "Channel 1";
			this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblChan0
			//
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan0.Location = new System.Drawing.Point(96, 104);
			this.lblChan0.Name = "lblChan0";
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.Size = new System.Drawing.Size(65, 17);
			this.lblChan0.TabIndex = 4;
			this.lblChan0.Text = "Channel 0";
			this.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(24, 16);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(281, 25);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AOutScan()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmSendAData
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(337, 212);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdEndProgram, this.cmdSendData, this.Label1, this._lblAOutData_1, this._lblAOutData_0, this.lblChan1, this.lblChan0, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmSendAData";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Analog Output ";
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmSendAData());
		}
	    

	    

		private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
		{
			//  Free up memory for use by other programs
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			
			MemHandle = 0;

			Application.Exit();
		}


		private void cmdSendData_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdSendData.Click */
		{
			//  Parameters:
			//    LowChan    :the lower channel of the scan
			//    HighChan   :the upper channel of the scan
			//    Count      :the number of D/A values to send
			//    Rate       :per channel sampling rate ((samples per second) per channel)
			//    DAData     :array of values to send to the scanned channels
			//    Options    :data send options
			FirstPoint = 0;
			int LowChan = 0;	// First analog output channel
			int HighChan = 1;	// Last analog output channel
			int Rate = 100;	// Rate of data update (ignored if board does not support timed analog output)
			MccDaq.Range Gain = MccDaq.Range.Bip5Volts; // Ignored if gain is not programmable
			MccDaq.ScanOptions Options = MccDaq.ScanOptions.Default;  // foreground mode scan
			MccDaq.ErrorInfo ULStat = DaqBoard.AOutScan( LowChan, HighChan, Count, ref Rate, Gain, MemHandle, Options);

			for (int i=0; i<=NumPoints - 1; ++i)
				lblAOutData[i].Text = DAData[i].ToString("0");
	       
		}

	}
}