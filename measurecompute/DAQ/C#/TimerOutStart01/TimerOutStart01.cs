// ==============================================================================
//
//  File:                         TimerOutStart01.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.TimerStart()
//																MccDaq.MccBoard.TimerStop()
//
//  Purpose:                      Controls an Output Timer Channel.
//
//  Demonstration:                Sends a frequency output to Timer 0.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a Timer output.
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

namespace TimerOutput
{
	public class frmTimerOutput : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public Label lblShowFrequency;
		public Label lblFrequency;
		public Label lblShowValue;
		public Label lblValueSent;
		public Label lblUseScroll;
		public Label lblDemoFunction;
		public Button UpdateButton;

		private MccDaq.MccBoard DaqBoard;
		const int Chan = 0;
		public System.Windows.Forms.TextBox txtFrequencyToSet;

		public frmTimerOutput()
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
			this.cmdEndProgram = new System.Windows.Forms.Button();
			this.txtFrequencyToSet = new System.Windows.Forms.TextBox();
			this.lblShowFrequency = new System.Windows.Forms.Label();
			this.lblFrequency = new System.Windows.Forms.Label();
			this.lblShowValue = new System.Windows.Forms.Label();
			this.lblValueSent = new System.Windows.Forms.Label();
			this.lblUseScroll = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.UpdateButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// cmdEndProgram
			// 
			this.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control;
			this.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdEndProgram.Location = new System.Drawing.Point(248, 216);
			this.cmdEndProgram.Name = "cmdEndProgram";
			this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdEndProgram.Size = new System.Drawing.Size(55, 26);
			this.cmdEndProgram.TabIndex = 5;
			this.cmdEndProgram.Text = "Quit";
			this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
			// 
			// txtFrequencyToSet
			// 
			this.txtFrequencyToSet.AcceptsReturn = true;
			this.txtFrequencyToSet.AutoSize = false;
			this.txtFrequencyToSet.BackColor = System.Drawing.SystemColors.Window;
			this.txtFrequencyToSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtFrequencyToSet.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtFrequencyToSet.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.txtFrequencyToSet.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtFrequencyToSet.Location = new System.Drawing.Point(120, 104);
			this.txtFrequencyToSet.MaxLength = 0;
			this.txtFrequencyToSet.Name = "txtFrequencyToSet";
			this.txtFrequencyToSet.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtFrequencyToSet.Size = new System.Drawing.Size(81, 25);
			this.txtFrequencyToSet.TabIndex = 0;
			this.txtFrequencyToSet.Text = "100000";
			// 
			// lblShowFrequency
			// 
			this.lblShowFrequency.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowFrequency.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowFrequency.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowFrequency.ForeColor = System.Drawing.Color.Blue;
			this.lblShowFrequency.Location = new System.Drawing.Point(248, 176);
			this.lblShowFrequency.Name = "lblShowFrequency";
			this.lblShowFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowFrequency.Size = new System.Drawing.Size(80, 17);
			this.lblShowFrequency.TabIndex = 6;
			// 
			// lblFrequency
			// 
			this.lblFrequency.BackColor = System.Drawing.SystemColors.Window;
			this.lblFrequency.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFrequency.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblFrequency.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFrequency.Location = new System.Drawing.Point(8, 176);
			this.lblFrequency.Name = "lblFrequency";
			this.lblFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFrequency.Size = new System.Drawing.Size(240, 17);
			this.lblFrequency.TabIndex = 7;
			// 
			// lblShowValue
			// 
			this.lblShowValue.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowValue.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowValue.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowValue.ForeColor = System.Drawing.Color.Blue;
			this.lblShowValue.Location = new System.Drawing.Point(248, 159);
			this.lblShowValue.Name = "lblShowValue";
			this.lblShowValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowValue.Size = new System.Drawing.Size(80, 17);
			this.lblShowValue.TabIndex = 4;
			// 
			// lblValueSent
			// 
			this.lblValueSent.BackColor = System.Drawing.SystemColors.Window;
			this.lblValueSent.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblValueSent.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblValueSent.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblValueSent.Location = new System.Drawing.Point(8, 159);
			this.lblValueSent.Name = "lblValueSent";
			this.lblValueSent.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblValueSent.Size = new System.Drawing.Size(240, 17);
			this.lblValueSent.TabIndex = 3;
			// 
			// lblUseScroll
			// 
			this.lblUseScroll.BackColor = System.Drawing.SystemColors.Window;
			this.lblUseScroll.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblUseScroll.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblUseScroll.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblUseScroll.Location = new System.Drawing.Point(56, 64);
			this.lblUseScroll.Name = "lblUseScroll";
			this.lblUseScroll.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblUseScroll.Size = new System.Drawing.Size(225, 32);
			this.lblUseScroll.TabIndex = 2;
			this.lblUseScroll.Text = "Enter a frequency within the timer\'s range and click Update Button when done";
			// 
			// lblDemoFunction
			// 
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(38, 24);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(256, 25);
			this.lblDemoFunction.TabIndex = 1;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.TimerStart() and MccDaq.MccBoard.TimerStop()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// UpdateButton
			// 
			this.UpdateButton.BackColor = System.Drawing.SystemColors.Control;
			this.UpdateButton.Location = new System.Drawing.Point(224, 104);
			this.UpdateButton.Name = "UpdateButton";
			this.UpdateButton.TabIndex = 8;
			this.UpdateButton.Text = "Update";
			this.UpdateButton.Click += new System.EventHandler(this.UpdateButton_Click);
			// 
			// frmTimerOutput
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(332, 251);
			this.Controls.Add(this.UpdateButton);
			this.Controls.Add(this.cmdEndProgram);
			this.Controls.Add(this.txtFrequencyToSet);
			this.Controls.Add(this.lblShowFrequency);
			this.Controls.Add(this.lblFrequency);
			this.Controls.Add(this.lblShowValue);
			this.Controls.Add(this.lblValueSent);
			this.Controls.Add(this.lblUseScroll);
			this.Controls.Add(this.lblDemoFunction);
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmTimerOutput";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Timer Output ";
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmTimerOutput());
		}


		private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
		{
			DaqBoard.TimerOutStop(0);
			Application.Exit();
		}


		private void UpdateButton_Click(object sender, System.EventArgs e) /* Handles UpdateButton.Click */
		{
			 bool IsValidNumber = true;
			 double frequency = 1000000.0;
			try
         {
				frequency = double.Parse(txtFrequencyToSet.Text);     
			}

        catch (Exception ex )
			{ 
				MessageBox.Show(txtFrequencyToSet.Text + " is not a valid frequency value", "Invalid Frequency ", MessageBoxButtons.OK, MessageBoxIcon.Error);
					IsValidNumber = false;
			}
        
			if (IsValidNumber)
			{
				double frequencySet = frequency;
				//  Parameters:
				//    TimerNum       :the timer output channel
				//    Frequency      :the frequency to output
				MccDaq.ErrorInfo ULStat = DaqBoard.TimerOutStart(0, ref frequency);
				if(ULStat.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
				  lblValueSent.Text = "The frequency sent to timer 0 was:";
				  lblFrequency.Text = "The frequency output from timer channel 0 is:";
				  lblShowValue.Text = frequencySet.ToString("0.0##") + " Hz";
				  lblShowFrequency.Text = frequency.ToString("0.0##") + " Hz";
				}
			}
		}

	}
}