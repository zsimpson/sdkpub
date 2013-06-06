// ==============================================================================
//
//  File:                         ULTI01.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.TIn()
//
//  Purpose:                      Reads a multiplexer input channel.
//
//  Demonstration:                Displays the temperature input on a MUX
//                                channel.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Unless the board at BoardNum(=0) does not use
//                                EXP boards for temperature measurements(the
//                                CIO-DAS-TC,for example), it must
//                                have an A/D converter with an attached EXP
//                                board.  Thermocouples must be wired to EXP
//                               channels selected.
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

namespace ULTI01
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopConvert;
		public Button cmdStartConvert;
		public TextBox txtExpChan;
		public Timer tmrConvert;
		public Label lblShowData;
		public Label lblValueRead;
		public Label lblChanPrompt;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		private int UsesEXPs;

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
			

			//  Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);

			//  Determine if the board uses EXP boards for temperature measurements
			UsesEXPs = 0;
			ULStat = DaqBoard.BoardConfig.GetUsesExps(out UsesEXPs);
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
			this.cmdStartConvert = new System.Windows.Forms.Button();
			this.txtExpChan = new System.Windows.Forms.TextBox();
			this.tmrConvert = new System.Windows.Forms.Timer(this.components);
			this.lblShowData = new System.Windows.Forms.Label();
			this.lblValueRead = new System.Windows.Forms.Label();
			this.lblChanPrompt = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopConvert
			//
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(288, 152);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.Size = new System.Drawing.Size(57, 25);
			this.cmdStopConvert.TabIndex = 6;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Visible = false;
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			//
			// cmdStartConvert
			//
			this.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartConvert.Location = new System.Drawing.Point(288, 152);
			this.cmdStartConvert.Name = "cmdStartConvert";
			this.cmdStartConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStartConvert.Size = new System.Drawing.Size(57, 25);
			this.cmdStartConvert.TabIndex = 5;
			this.cmdStartConvert.Text = "Start";
			this.cmdStartConvert.Click += new System.EventHandler(this.cmdStartConvert_Click);
			//
			// txtExpChan
			//
			this.txtExpChan.AcceptsReturn = true;
			this.txtExpChan.AutoSize = false;
			this.txtExpChan.BackColor = System.Drawing.SystemColors.Window;
			this.txtExpChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtExpChan.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtExpChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtExpChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtExpChan.Location = new System.Drawing.Point(312, 56);
			this.txtExpChan.MaxLength = 0;
			this.txtExpChan.Name = "txtExpChan";
			this.txtExpChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtExpChan.Size = new System.Drawing.Size(33, 25);
			this.txtExpChan.TabIndex = 0;
			this.txtExpChan.Text = "0";
			//
			// tmrConvert
			//
			this.tmrConvert.Interval = 250;
			this.tmrConvert.Tick += new System.EventHandler(this.tmrConvert_Tick);
			//
			// lblShowData
			//
			this.lblShowData.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowData.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowData.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowData.ForeColor = System.Drawing.Color.Blue;
			this.lblShowData.Location = new System.Drawing.Point(280, 104);
			this.lblShowData.Name = "lblShowData";
			this.lblShowData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowData.Size = new System.Drawing.Size(65, 17);
			this.lblShowData.TabIndex = 4;
			//
			// lblValueRead
			//
			this.lblValueRead.BackColor = System.Drawing.SystemColors.Window;
			this.lblValueRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblValueRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblValueRead.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblValueRead.Location = new System.Drawing.Point(24, 104);
			this.lblValueRead.Name = "lblValueRead";
			this.lblValueRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblValueRead.Size = new System.Drawing.Size(241, 17);
			this.lblValueRead.TabIndex = 3;
			this.lblValueRead.Text = "Temperature read from selected channel:";
			//
			// lblChanPrompt
			//
			this.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window;
			this.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChanPrompt.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChanPrompt.Location = new System.Drawing.Point(8, 64);
			this.lblChanPrompt.Name = "lblChanPrompt";
			this.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChanPrompt.Size = new System.Drawing.Size(297, 17);
			this.lblChanPrompt.TabIndex = 1;
			this.lblChanPrompt.Text = "Enter the multiplexor channel to display (0 to 15): ";
			this.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(40, 16);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(273, 25);
			this.lblDemoFunction.TabIndex = 2;
			this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.TIn()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDataDisplay
			//
			this.AcceptButton = this.cmdStartConvert;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(360, 190);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopConvert, this.cmdStartConvert, this.txtExpChan, this.lblShowData, this.lblValueRead, this.lblChanPrompt, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmDataDisplay";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Temperature Measurement";
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
	    	

		private void cmdStartConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartConvert.Click */
		{
			if (int.Parse(txtExpChan.Text) < 0) 
				txtExpChan.Text = "0";

			if (int.Parse(txtExpChan.Text) > 15) 
				txtExpChan.Text = "15";

			cmdStartConvert.Visible = false;
			cmdStopConvert.Visible = true;
			tmrConvert.Enabled = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			Application.Exit();
		}


		private void tmrConvert_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrConvert.Tick */
		{
			tmrConvert.Stop();

			//  Collect the data with Mccdaq.MccBoard.TIn()

			//  Parameters:
			//    Chan       :the A/D and channel number; starts at 16
			//                 calculated by (ADChan + 1) * 16 + EXPChan%
			//    MccScale    :the temperature scale (F, C or K)
			//    DataValue  :the name for the value collected
			//    ADChan     :usually channel 0 for CIO-EXP16
			short ADChan = 0; //  allows access to 16 channels on the EXP board

			//  increasing this number allows access to upper
			//  bank on EXP32 and additional EXP boards
			MccDaq.TempScale MccScale = MccDaq.TempScale.Celsius;
			int Chan = 0;
			if (UsesEXPs > 0)
				Chan = int.Parse(txtExpChan.Text) + (ADChan + 1) * 16;
			else
				Chan = int.Parse(txtExpChan.Text);

			float TempValue = 0.0f;
			MccDaq.ThermocoupleOptions Options = MccDaq.ThermocoupleOptions.Filter;
			MccDaq.ErrorInfo ULStat = DaqBoard.TIn( Chan, MccScale, out TempValue, Options);

			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				tmrConvert.Start();

			lblShowData.Text = TempValue.ToString("0") + "°C"; //  print the value    
		}


		private void txtExpChan_TextChanged(object eventSender, System.EventArgs eventArgs) /* Handles txtExpChan.TextChanged */
		{
			tmrConvert.Enabled = false;
			cmdStartConvert.Visible = true;
			cmdStopConvert.Visible = false;
		}

	}
}