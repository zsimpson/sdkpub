// ==============================================================================
//
//  File:                         ULAO01.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.AOut()
//
//  Purpose:                      Writes to a D/A Output Channel.
//
//  Demonstration:                Sends a digital output to D/A 0.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a D/A converter.
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

namespace ULAO01
{
	public class frmSendAData : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public TextBox txtVoltsToSet;
		public Label lblShowVoltage;
		public Label lblVoltage;
		public Label lblShowValue;
		public Label lblValueSent;
		public Label lblUseScroll;
		public Label lblDemoFunction;
		public Button UpdateButton;

		private MccDaq.MccBoard DaqBoard;
		const int Chan = 0;				//  output channel
		const MccDaq.Range Range = MccDaq.Range.Bip5Volts;

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
			this.txtVoltsToSet = new System.Windows.Forms.TextBox();
			this.lblShowVoltage = new System.Windows.Forms.Label();
			this.lblVoltage = new System.Windows.Forms.Label();
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
			this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdEndProgram.Location = new System.Drawing.Point(248, 216);
			this.cmdEndProgram.Name = "cmdEndProgram";
			this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdEndProgram.Size = new System.Drawing.Size(55, 26);
			this.cmdEndProgram.TabIndex = 5;
			this.cmdEndProgram.Text = "Quit";
			this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
			//
			// txtVoltsToSet
			//
			this.txtVoltsToSet.AcceptsReturn = true;
			this.txtVoltsToSet.AutoSize = false;
			this.txtVoltsToSet.BackColor = System.Drawing.SystemColors.Window;
			this.txtVoltsToSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtVoltsToSet.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtVoltsToSet.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtVoltsToSet.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtVoltsToSet.Location = new System.Drawing.Point(120, 104);
			this.txtVoltsToSet.MaxLength = 0;
			this.txtVoltsToSet.Name = "txtVoltsToSet";
			this.txtVoltsToSet.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtVoltsToSet.Size = new System.Drawing.Size(81, 25);
			this.txtVoltsToSet.TabIndex = 0;
			this.txtVoltsToSet.Text = "";
			//
			// lblShowVoltage
			//
			this.lblShowVoltage.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowVoltage.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowVoltage.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowVoltage.ForeColor = System.Drawing.Color.Blue;
			this.lblShowVoltage.Location = new System.Drawing.Point(240, 176);
			this.lblShowVoltage.Name = "lblShowVoltage";
			this.lblShowVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowVoltage.Size = new System.Drawing.Size(81, 17);
			this.lblShowVoltage.TabIndex = 6;
			//
			// lblVoltage
			//
			this.lblVoltage.BackColor = System.Drawing.SystemColors.Window;
			this.lblVoltage.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblVoltage.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblVoltage.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblVoltage.Location = new System.Drawing.Point(32, 176);
			this.lblVoltage.Name = "lblVoltage";
			this.lblVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblVoltage.Size = new System.Drawing.Size(201, 17);
			this.lblVoltage.TabIndex = 7;
			//
			// lblShowValue
			//
			this.lblShowValue.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowValue.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowValue.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblShowValue.ForeColor = System.Drawing.Color.Blue;
			this.lblShowValue.Location = new System.Drawing.Point(264, 159);
			this.lblShowValue.Name = "lblShowValue";
			this.lblShowValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowValue.Size = new System.Drawing.Size(57, 17);
			this.lblShowValue.TabIndex = 4;
			//
			// lblValueSent
			//
			this.lblValueSent.BackColor = System.Drawing.SystemColors.Window;
			this.lblValueSent.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblValueSent.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblValueSent.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblValueSent.Location = new System.Drawing.Point(32, 159);
			this.lblValueSent.Name = "lblValueSent";
			this.lblValueSent.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblValueSent.Size = new System.Drawing.Size(225, 17);
			this.lblValueSent.TabIndex = 3;
			//
			// lblUseScroll
			//
			this.lblUseScroll.BackColor = System.Drawing.SystemColors.Window;
			this.lblUseScroll.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblUseScroll.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblUseScroll.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblUseScroll.Location = new System.Drawing.Point(56, 64);
			this.lblUseScroll.Name = "lblUseScroll";
			this.lblUseScroll.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblUseScroll.Size = new System.Drawing.Size(225, 32);
			this.lblUseScroll.TabIndex = 2;
			this.lblUseScroll.Text = "Enter a voltage within the DACs range Hit Update Button when done";
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(40, 24);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(241, 25);
			this.lblDemoFunction.TabIndex = 1;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.AOut()";
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
			// frmSendAData
			//
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(332, 251);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.UpdateButton, this.cmdEndProgram, this.txtVoltsToSet, this.lblShowVoltage, this.lblVoltage, this.lblShowValue, this.lblValueSent, this.lblUseScroll, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
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
			Application.Exit();
		}


		private void UpdateButton_Click(object sender, System.EventArgs e) /* Handles UpdateButton.Click */
		{
			 bool IsValidNumber = true;
			 float EngUnits = 0.0f;
			try
         {
				EngUnits = float.Parse(txtVoltsToSet.Text);     
			}

        catch (Exception ex )
			{ 
				MessageBox.Show(txtVoltsToSet.Text + " is not a valid voltage value", "Invalid Voltage ", MessageBoxButtons.OK, MessageBoxIcon.Error);
					IsValidNumber = false;
			}
        
			if (IsValidNumber)
			{
				//  Parameters:
				//    Chan       :the D/A output channel
				//    Range      :ignored if board does not have programmable rage
				//    DataValue  :the value to send to Chan
				ushort DataValue = 0;
				MccDaq.ErrorInfo ULStat = DaqBoard.FromEngUnits( Range, EngUnits, out DataValue);
				

				ULStat = DaqBoard.AOut(Chan, Range, DataValue);

				lblValueSent.Text = "The count sent to DAC channel " + Chan.ToString("0") + " was:";
				lblVoltage.Text = "The voltage at DAC channel " + Chan.ToString("0") + " is:";
				lblShowValue.Text = DataValue.ToString("0");
				lblShowVoltage.Text = EngUnits.ToString("0.0##") + " Volts";
			}
		}

	}
}