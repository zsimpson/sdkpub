// ==============================================================================
//
//  File:                         ULCT04.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.CFreqIn()
//
//  Purpose:                      Measure the frequency of a signal.
//
//  Demonstration:                Initializes the counter and measures a frequency.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a 9513 Counter.
//                                External freq. at counter 1 input.
//                                (100Hz < freq < 330kHz)
//                                External connection from counter 4 output
//                                to counter 5 gate.
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

namespace ULCT04
{
	public class frm9513Freq : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopRead;
		public Button cmdMeasureFreq;
		public Label lblFreq;
		public Label lblCount;
		public Label lblFrequency;
		public Label lblCountNum;
		public Label lblInstruct;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		const short ChipNum = 1;	// use chip 1 for CIO-CTR05 or for first
									// chip on CIO-CTR10

		public frm9513Freq()
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
			

			//  Initialize the board level features
			//   Parameters:
			//     ChipNum    :chip to be initialized (1 for CTR5, 1 or 2 for CTR10)
			//     FOutDivider:the F-Out divider (0-15)
			//     Source     :the signal source for F-Out
			//     Compare1   :status of comparator 1
			//     Compare2   :status of comparator 2
			//     TimeOfDay  :time of day mode control
			short FOutDivider = 1; //  sets up OSC OUT for 10kHz signal which can
			MccDaq.CounterSource Source = MccDaq.CounterSource.Freq3; //  be used as frequency source for this example
			MccDaq.CompareValue Compare1 = MccDaq.CompareValue.Disabled;
			MccDaq.CompareValue Compare2 = MccDaq.CompareValue.Disabled;
			MccDaq.TimeOfDay TimeOfDayCounting = MccDaq.TimeOfDay.Disabled;
			ULStat = DaqBoard.C9513Init(ChipNum, FOutDivider, Source, Compare1, Compare2, TimeOfDayCounting);
			
		}


		private void cmdMeasureFreq_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdMeasureFreq.Click */
		{
			//  Measure the frequency of the internally-generated signal
			//   Parameters:
			//     SigSource    :the counter to be measured (1 to 5)
			//     GateInterval :gating interval in millseconds
			//     Count		:the raw count during GateInterval is returned here
			//     Freq         :the calculated frequency (Hz) is returned here
			MccDaq.SignalSource SigSource = MccDaq.SignalSource.CtrInput1;
			short GateInterval = 100;
			ushort Count = 0;
			int Freq =0;
			MccDaq.ErrorInfo ULStat = DaqBoard.CFreqIn( SigSource, GateInterval, out Count, out Freq);

			lblCount.Text = Count.ToString("0");
			lblFreq.Text = Freq.ToString("0") + "Hz";
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
		this.cmdStopRead = new System.Windows.Forms.Button();
		this.cmdMeasureFreq = new System.Windows.Forms.Button();
		this.lblFreq = new System.Windows.Forms.Label();
		this.lblCount = new System.Windows.Forms.Label();
		this.lblFrequency = new System.Windows.Forms.Label();
		this.lblCountNum = new System.Windows.Forms.Label();
		this.lblInstruct = new System.Windows.Forms.Label();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.SuspendLayout();
		// 
		// cmdStopRead
		// 
		this.cmdStopRead.BackColor = System.Drawing.SystemColors.Control;
		this.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdStopRead.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdStopRead.Location = new System.Drawing.Point(264, 208);
		this.cmdStopRead.Name = "cmdStopRead";
		this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdStopRead.Size = new System.Drawing.Size(52, 26);
		this.cmdStopRead.TabIndex = 1;
		this.cmdStopRead.Text = "Quit";
		this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
		// 
		// cmdMeasureFreq
		// 
		this.cmdMeasureFreq.BackColor = System.Drawing.SystemColors.Control;
		this.cmdMeasureFreq.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdMeasureFreq.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdMeasureFreq.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdMeasureFreq.Location = new System.Drawing.Point(96, 208);
		this.cmdMeasureFreq.Name = "cmdMeasureFreq";
		this.cmdMeasureFreq.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdMeasureFreq.Size = new System.Drawing.Size(129, 25);
		this.cmdMeasureFreq.TabIndex = 7;
		this.cmdMeasureFreq.Text = "Measure Frequency";
		this.cmdMeasureFreq.Click += new System.EventHandler(this.cmdMeasureFreq_Click);
		// 
		// lblFreq
		// 
		this.lblFreq.BackColor = System.Drawing.SystemColors.Window;
		this.lblFreq.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblFreq.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblFreq.ForeColor = System.Drawing.Color.Blue;
		this.lblFreq.Location = new System.Drawing.Point(200, 160);
		this.lblFreq.Name = "lblFreq";
		this.lblFreq.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblFreq.Size = new System.Drawing.Size(65, 17);
		this.lblFreq.TabIndex = 3;
		this.lblFreq.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblCount
		// 
		this.lblCount.BackColor = System.Drawing.SystemColors.Window;
		this.lblCount.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblCount.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblCount.ForeColor = System.Drawing.Color.Blue;
		this.lblCount.Location = new System.Drawing.Point(88, 160);
		this.lblCount.Name = "lblCount";
		this.lblCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblCount.Size = new System.Drawing.Size(65, 17);
		this.lblCount.TabIndex = 2;
		this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblFrequency
		// 
		this.lblFrequency.BackColor = System.Drawing.SystemColors.Window;
		this.lblFrequency.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblFrequency.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblFrequency.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblFrequency.Location = new System.Drawing.Point(192, 136);
		this.lblFrequency.Name = "lblFrequency";
		this.lblFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblFrequency.Size = new System.Drawing.Size(81, 17);
		this.lblFrequency.TabIndex = 5;
		this.lblFrequency.Text = "Frequency";
		this.lblFrequency.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblCountNum
		// 
		this.lblCountNum.BackColor = System.Drawing.SystemColors.Window;
		this.lblCountNum.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblCountNum.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblCountNum.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblCountNum.Location = new System.Drawing.Point(64, 136);
		this.lblCountNum.Name = "lblCountNum";
		this.lblCountNum.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblCountNum.Size = new System.Drawing.Size(113, 17);
		this.lblCountNum.TabIndex = 4;
		this.lblCountNum.Text = "Number of Counts";
		this.lblCountNum.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblInstruct
		// 
		this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblInstruct.ForeColor = System.Drawing.Color.Red;
		this.lblInstruct.Location = new System.Drawing.Point(8, 72);
		this.lblInstruct.Name = "lblInstruct";
		this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct.Size = new System.Drawing.Size(329, 41);
		this.lblInstruct.TabIndex = 6;
		this.lblInstruct.Text = "There must be a TTL pulse at counter 1 input with a frequency between  100Hz and " +
			" 600kHz. Also, connect the output of counter 4 to the gate of counter 5.";
		this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(8, 16);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(306, 44);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of Frequency Measurement using 9513 Counter";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frm9513Freq
		// 
		this.AcceptButton = this.cmdStopRead;
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(345, 250);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdStopRead,
																		this.cmdMeasureFreq,
																		this.lblFreq,
																		this.lblCount,
																		this.lblFrequency,
																		this.lblCountNum,
																		this.lblInstruct,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 96);
		this.Name = "frm9513Freq";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library 9513 Counter Demo";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frm9513Freq());
		}
	    

		


		private void cmdStopRead_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopRead.Click */
		{
			Application.Exit();
		}

	}
}