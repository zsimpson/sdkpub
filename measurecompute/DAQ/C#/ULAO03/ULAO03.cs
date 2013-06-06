using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

//ULAO03================================================================
//
// File:                         ULAO03.CS
//
// Library Call Demonstrated:    MccBoard.AOut()
//                               MccBoard.BoardConfig.DACUpdateMode()
//                               MccBoard.BoardConfig.DACUpdate()
//
// Purpose:                      Demonstrates difference between DACUpdate.Immdediate
//                               and DACUpdate.OnCommand D/A Update modes
//
// Demonstration:                Delays outputs until user issues update command DACUpdate()
//
// Other Library Calls:          MccService.ErrHandling()
//                               MccBoard.FromEngUnits()
//
// Special Requirements:         Board 0 must support BIDACUPDATEMODE settings,
//                               such as the PCI-DAC6700's.
//
//
// (c) Copyright 2003, Measurement Computing Corp.
// All rights reserved.
//==========================================================================
namespace ULAO03
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmAOut : Form
	{
		private Label label1;
		private Button btnUpdateDACs;
		private Button btnSendData;
		private Label label2;
		private Label label3;
		private Label label4;
		private Label label5;
		private TextBox txtAOVolts0;
		private TextBox txtAOVolts1;
		private TextBox txtAOVolts2;
		private TextBox txtAOVolts3;
		private TextBox[] _txtAOVolts;
		private RadioButton rdioOnCommand;
		private RadioButton rdioImmediate;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		MccDaq.MccBoard _bd;
		MccDaq.Range _range = MccDaq.Range.Bip10Volts;
		const int AllChannels = -1;  //negative values specify all available devices/channels

		public frmAOut()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//  Initiate error handling
			//   activating error handling will trap errors like
			//   bad channel numbers and non-configured conditions.
			//   Parameters:
			//     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
		
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
		

			// Create a new MccBoard object for Board 0
			_bd = new MccDaq.MccBoard(0);

			// Initialize outputs to update on command
			// Parameters
			//	 channel	: D/A channel whose update mode is to be configured. Note
			//				  that negative values selects all channels
			//   DACUpdate.OnCommand : delay D/A output updates from AOut or AOutScan until
			//                         DACUpdate command is issued.
			int channel = AllChannels;
			_bd.BoardConfig.SetDACUpdateMode(channel, (int)MccDaq.DACUpdate.OnCommand);

			//  This gives us access to text boxes via an indexed array
			_txtAOVolts = (new TextBox[] {this.txtAOVolts0, this.txtAOVolts1, this.txtAOVolts2, this.txtAOVolts3});  
		}


		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}




		private void rdioOnCommand_CheckedChanged(object sender, System.EventArgs e)
		{
			if (rdioOnCommand.Checked)
			{
				// Set DAC Update mode to hold off updating D/A's until command is sent
				// Parameters
				//	 channel	: D/A channel whose update mode is to be configured. Note
				//				  that negative values selects all channels
				//   DACUpdate.OnCommand : delay D/A output updates from AOut or AOutScan until
				//                         DACUpdate command is issued.
				int channel = AllChannels;
				_bd.BoardConfig.SetDACUpdateMode(channel, (int)MccDaq.DACUpdate.OnCommand);
			}
		}



		private void rdioImmediate_CheckedChanged(object sender, System.EventArgs e)
		{
			if (rdioImmediate.Checked)
			{
				// Set DAC Update mode to update immediately upon cbAOut or cbAOutScan
				// Parameters
				//	 channel	: D/A channel whose update mode is to be configured. Note
				//				  that negative values selects all channels
				//   DACUpdate.Immediate : update D/A outputs immediately upon AOut or AOutScan
				int channel = AllChannels;
				_bd.BoardConfig.SetDACUpdateMode(channel, (int)MccDaq.DACUpdate.Immediate);
			}
		}


		private void btnSendData_Click(object sender, System.EventArgs e)
		{
			float volts=0.0F;
			ushort daCounts = 0;
			int chan = 0;
			foreach(TextBox box in _txtAOVolts)
			{
				//get voltage to output
				volts = float.Parse(box.Text);	

				// convert from voltage to binary counts
				_bd.FromEngUnits(_range, volts, out daCounts);

				// load D/A
				_bd.AOut(chan, _range, daCounts);
				++chan;
			}
		}



		private void btnUpdateDACs_Click(object sender, System.EventArgs e)
		{
			// Issue D/A Update command
			_bd.BoardConfig.DACUpdate();
		}



		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.btnUpdateDACs = new System.Windows.Forms.Button();
			this.btnSendData = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.txtAOVolts0 = new System.Windows.Forms.TextBox();
			this.txtAOVolts1 = new System.Windows.Forms.TextBox();
			this.txtAOVolts2 = new System.Windows.Forms.TextBox();
			this.txtAOVolts3 = new System.Windows.Forms.TextBox();
			this.rdioOnCommand = new System.Windows.Forms.RadioButton();
			this.rdioImmediate = new System.Windows.Forms.RadioButton();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label1.Location = new System.Drawing.Point(24, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(296, 48);
			this.label1.TabIndex = 0;
			this.label1.Text = "Demonstrates DAC Update Modes using AOut";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// btnUpdateDACs
			// 
			this.btnUpdateDACs.Location = new System.Drawing.Point(192, 72);
			this.btnUpdateDACs.Name = "btnUpdateDACs";
			this.btnUpdateDACs.Size = new System.Drawing.Size(136, 32);
			this.btnUpdateDACs.TabIndex = 1;
			this.btnUpdateDACs.Text = "Update Outputs";
			this.btnUpdateDACs.Click += new System.EventHandler(this.btnUpdateDACs_Click);
			// 
			// btnSendData
			// 
			this.btnSendData.Location = new System.Drawing.Point(32, 72);
			this.btnSendData.Name = "btnSendData";
			this.btnSendData.Size = new System.Drawing.Size(136, 32);
			this.btnSendData.TabIndex = 2;
			this.btnSendData.Text = "Send Data";
			this.btnSendData.Click += new System.EventHandler(this.btnSendData_Click);
			// 
			// label2
			// 
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label2.ForeColor = System.Drawing.SystemColors.HotTrack;
			this.label2.Location = new System.Drawing.Point(8, 112);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(80, 16);
			this.label2.TabIndex = 3;
			this.label2.Text = "Channel 0";
			// 
			// label3
			// 
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label3.ForeColor = System.Drawing.SystemColors.HotTrack;
			this.label3.Location = new System.Drawing.Point(96, 112);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(80, 16);
			this.label3.TabIndex = 4;
			this.label3.Text = "Channel 1";
			// 
			// label4
			// 
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label4.ForeColor = System.Drawing.SystemColors.HotTrack;
			this.label4.Location = new System.Drawing.Point(184, 112);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(80, 16);
			this.label4.TabIndex = 5;
			this.label4.Text = "Channel 2";
			// 
			// label5
			// 
			this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label5.ForeColor = System.Drawing.SystemColors.HotTrack;
			this.label5.Location = new System.Drawing.Point(272, 112);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(80, 16);
			this.label5.TabIndex = 6;
			this.label5.Text = "Channel 3";
			// 
			// txtAOVolts0
			// 
			this.txtAOVolts0.Location = new System.Drawing.Point(8, 136);
			this.txtAOVolts0.Name = "txtAOVolts0";
			this.txtAOVolts0.Size = new System.Drawing.Size(72, 20);
			this.txtAOVolts0.TabIndex = 7;
			this.txtAOVolts0.Text = "0.00";
			// 
			// txtAOVolts1
			// 
			this.txtAOVolts1.Location = new System.Drawing.Point(96, 136);
			this.txtAOVolts1.Name = "txtAOVolts1";
			this.txtAOVolts1.Size = new System.Drawing.Size(72, 20);
			this.txtAOVolts1.TabIndex = 8;
			this.txtAOVolts1.Text = "0.00";
			// 
			// txtAOVolts2
			// 
			this.txtAOVolts2.Location = new System.Drawing.Point(184, 136);
			this.txtAOVolts2.Name = "txtAOVolts2";
			this.txtAOVolts2.Size = new System.Drawing.Size(72, 20);
			this.txtAOVolts2.TabIndex = 9;
			this.txtAOVolts2.Text = "0.00";
			// 
			// txtAOVolts3
			// 
			this.txtAOVolts3.Location = new System.Drawing.Point(272, 136);
			this.txtAOVolts3.Name = "txtAOVolts3";
			this.txtAOVolts3.Size = new System.Drawing.Size(72, 20);
			this.txtAOVolts3.TabIndex = 10;
			this.txtAOVolts3.Text = "0.00";
			// 
			// rdioOnCommand
			// 
			this.rdioOnCommand.Checked = true;
			this.rdioOnCommand.Location = new System.Drawing.Point(96, 176);
			this.rdioOnCommand.Name = "rdioOnCommand";
			this.rdioOnCommand.Size = new System.Drawing.Size(168, 24);
			this.rdioOnCommand.TabIndex = 11;
			this.rdioOnCommand.TabStop = true;
			this.rdioOnCommand.Text = "Update On Command";
			this.rdioOnCommand.CheckedChanged += new System.EventHandler(this.rdioOnCommand_CheckedChanged);
			// 
			// rdioImmediate
			// 
			this.rdioImmediate.Location = new System.Drawing.Point(96, 208);
			this.rdioImmediate.Name = "rdioImmediate";
			this.rdioImmediate.Size = new System.Drawing.Size(168, 24);
			this.rdioImmediate.TabIndex = 12;
			this.rdioImmediate.Text = "Update Immediately";
			this.rdioImmediate.CheckedChanged += new System.EventHandler(this.rdioImmediate_CheckedChanged);
			// 
			// frmAOut
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(360, 245);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.rdioImmediate,
																		  this.rdioOnCommand,
																		  this.txtAOVolts3,
																		  this.txtAOVolts2,
																		  this.txtAOVolts1,
																		  this.txtAOVolts0,
																		  this.label5,
																		  this.label4,
																		  this.label3,
																		  this.label2,
																		  this.btnSendData,
																		  this.btnUpdateDACs,
																		  this.label1});
			this.Name = "frmAOut";
			this.Text = "Universal Library Analog Output";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmAOut());
		}

		
	}
}
