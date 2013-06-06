// ==============================================================================
//
//  File:                         VOut01.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.VOut()
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

namespace VOut01
{
	public class frmSendAData : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public TextBox txtVoltsToSet;
		public Label lblVoltage;
		public Label lblShowValue;
		public Label lblUseScroll;
		public Label lblDemoFunction;
		public Button UpdateButton;

		private MccDaq.MccBoard DaqBoard;
		const int Chan = 0;
	  internal System.Windows.Forms.Label lblPrompt;
	  public System.Windows.Forms.Label lblRange;
	  internal System.Windows.Forms.ComboBox cmbRange;				//  output channel
		public MccDaq.Range RangeSelected;

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

			cmbRange.Items.Insert(0,MccDaq.Range.Bip10Volts);
			cmbRange.Items.Insert(1,MccDaq.Range.Bip5Volts);
			cmbRange.Items.Insert(2,MccDaq.Range.Uni10Volts);
			cmbRange.Items.Insert(3,MccDaq.Range.Uni5Volts);
			cmbRange.SelectedIndex = 1;
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
		  this.lblVoltage = new System.Windows.Forms.Label();
		  this.lblShowValue = new System.Windows.Forms.Label();
		  this.lblUseScroll = new System.Windows.Forms.Label();
		  this.lblDemoFunction = new System.Windows.Forms.Label();
		  this.UpdateButton = new System.Windows.Forms.Button();
		  this.lblPrompt = new System.Windows.Forms.Label();
		  this.lblRange = new System.Windows.Forms.Label();
		  this.cmbRange = new System.Windows.Forms.ComboBox();
		  this.SuspendLayout();
		  // 
		  // cmdEndProgram
		  // 
		  this.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control;
		  this.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default;
		  this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
		  this.cmdEndProgram.Location = new System.Drawing.Point(232, 264);
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
		  this.txtVoltsToSet.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.txtVoltsToSet.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.txtVoltsToSet.Location = new System.Drawing.Point(224, 152);
		  this.txtVoltsToSet.MaxLength = 0;
		  this.txtVoltsToSet.Name = "txtVoltsToSet";
		  this.txtVoltsToSet.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.txtVoltsToSet.Size = new System.Drawing.Size(112, 25);
		  this.txtVoltsToSet.TabIndex = 0;
		  this.txtVoltsToSet.Text = "";
		  // 
		  // lblVoltage
		  // 
		  this.lblVoltage.BackColor = System.Drawing.SystemColors.Window;
		  this.lblVoltage.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblVoltage.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblVoltage.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblVoltage.Location = new System.Drawing.Point(16, 232);
		  this.lblVoltage.Name = "lblVoltage";
		  this.lblVoltage.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblVoltage.Size = new System.Drawing.Size(201, 17);
		  this.lblVoltage.TabIndex = 7;
		  this.lblVoltage.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
		  // 
		  // lblShowValue
		  // 
		  this.lblShowValue.BackColor = System.Drawing.SystemColors.Window;
		  this.lblShowValue.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblShowValue.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblShowValue.ForeColor = System.Drawing.Color.Blue;
		  this.lblShowValue.Location = new System.Drawing.Point(232, 232);
		  this.lblShowValue.Name = "lblShowValue";
		  this.lblShowValue.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblShowValue.Size = new System.Drawing.Size(57, 17);
		  this.lblShowValue.TabIndex = 4;
		  this.lblShowValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
		  // 
		  // lblUseScroll
		  // 
		  this.lblUseScroll.BackColor = System.Drawing.SystemColors.Window;
		  this.lblUseScroll.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblUseScroll.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblUseScroll.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblUseScroll.Location = new System.Drawing.Point(16, 152);
		  this.lblUseScroll.Name = "lblUseScroll";
		  this.lblUseScroll.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblUseScroll.Size = new System.Drawing.Size(200, 32);
		  this.lblUseScroll.TabIndex = 2;
		  this.lblUseScroll.Text = "Enter a voltage within the DACs range Hit Update Button when done";
		  // 
		  // lblDemoFunction
		  // 
		  this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		  this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblDemoFunction.Location = new System.Drawing.Point(72, 24);
		  this.lblDemoFunction.Name = "lblDemoFunction";
		  this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblDemoFunction.Size = new System.Drawing.Size(241, 25);
		  this.lblDemoFunction.TabIndex = 1;
		  this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.VOut()";
		  this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // UpdateButton
		  // 
		  this.UpdateButton.BackColor = System.Drawing.SystemColors.Control;
		  this.UpdateButton.Location = new System.Drawing.Point(224, 192);
		  this.UpdateButton.Name = "UpdateButton";
		  this.UpdateButton.TabIndex = 8;
		  this.UpdateButton.Text = "Update";
		  this.UpdateButton.Click += new System.EventHandler(this.UpdateButton_Click);
		  // 
		  // lblPrompt
		  // 
		  this.lblPrompt.Location = new System.Drawing.Point(8, 56);
		  this.lblPrompt.Name = "lblPrompt";
		  this.lblPrompt.Size = new System.Drawing.Size(364, 56);
		  this.lblPrompt.TabIndex = 10;
		  this.lblPrompt.Text = "Using the combo box below, select a range supported by the device you are using. " +
			"If the device is not programmable, the range selected must match the range your " +
			"device is configured for.";
		  // 
		  // lblRange
		  // 
		  this.lblRange.BackColor = System.Drawing.SystemColors.Window;
		  this.lblRange.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblRange.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblRange.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblRange.Location = new System.Drawing.Point(112, 120);
		  this.lblRange.Name = "lblRange";
		  this.lblRange.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblRange.Size = new System.Drawing.Size(104, 16);
		  this.lblRange.TabIndex = 13;
		  this.lblRange.Text = "Range";
		  this.lblRange.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
		  // 
		  // cmbRange
		  // 
		  this.cmbRange.Location = new System.Drawing.Point(224, 120);
		  this.cmbRange.Name = "cmbRange";
		  this.cmbRange.Size = new System.Drawing.Size(120, 22);
		  this.cmbRange.TabIndex = 12;
		  this.cmbRange.Text = "Bip5Volts";
		  this.cmbRange.SelectedIndexChanged += new System.EventHandler(this.cmbRange_SelectedIndexChanged);
		  // 
		  // frmSendAData
		  // 
		  this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		  this.BackColor = System.Drawing.SystemColors.Window;
		  this.ClientSize = new System.Drawing.Size(384, 309);
		  this.Controls.AddRange(new System.Windows.Forms.Control[] {
																	  this.lblRange,
																	  this.cmbRange,
																	  this.lblPrompt,
																	  this.UpdateButton,
																	  this.cmdEndProgram,
																	  this.txtVoltsToSet,
																	  this.lblVoltage,
																	  this.lblShowValue,
																	  this.lblUseScroll,
																	  this.lblDemoFunction});
		  this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
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
			float DataValue = 0.0f;
		    VOutOptions Options = VOutOptions.Default;

			try
			{
				DataValue = float.Parse(txtVoltsToSet.Text);     
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
				
				MccDaq.ErrorInfo ULStat = DaqBoard.VOut(Chan, RangeSelected, DataValue, Options);

				lblVoltage.Text = "The voltage at DAC channel " + Chan.ToString("0") + " is:";
				lblShowValue.Text = DataValue.ToString("0.0##") + " Volts";
			}
		}

	  private void cmbRange_SelectedIndexChanged(object sender, System.EventArgs e)
	  {
		   RangeSelected = (MccDaq.Range)(cmbRange.SelectedItem);
	  }

	}
}