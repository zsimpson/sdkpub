// ==============================================================================
//
//  File:                         ULDO05.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DBitOut()
//
//  Purpose:                      Sets the state of a single digital output bit.
//
//  Demonstration:                Writes bit values to AuxPort.
//
//  Other Library Calls:          MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccService.ErrHandling()
//								  MccDaq.MccBoard.DioConfig.GetDevType()
//								  MccDaq.MccBoard.DioConfig.GetDInMask()
//								  MccDaq.MccBoard.DioConfig.GetDOutMask()
//
//  Special Requirements:         Board 0 must have a digital output port.
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

namespace ULDO05
{
	public class frmSetBitOut : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public CheckBox _chkSetBit_7;
		public CheckBox _chkSetBit_3;
		public CheckBox _chkSetBit_6;
		public CheckBox _chkSetBit_2;
		public CheckBox _chkSetBit_5;
		public CheckBox _chkSetBit_1;
		public CheckBox _chkSetBit_4;
		public CheckBox _chkSetBit_0;
		public Label lblDemoFunction;

		public CheckBox[] chkSetBit;

		private MccDaq.MccBoard DaqBoard;
		const MccDaq.DigitalPortType PortNum = MccDaq.DigitalPortType.AuxPort; //  use first digital port
		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalOut; //  program first digital port for output mode
	 

		public frmSetBitOut()
		{
	        
			// This call is required by the Windows Form Designer.
			InitializeComponent();


			//  Initiate error handling
			//   activating error handling will trap errors like
			//   bad channel numbers and non-configured conditions.
			//   Parameters:
			//     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
			MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);	

			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);

			// Determine if board has AuxPort 
			//Parameters:
			//  devNum      : 0-based digital device index
			//  portType    : return value for type of device
			int devNum =0;  //AuxPort is the 0th digital device, if present
			int portType = 0;
			DaqBoard.DioConfig.GetDevType(devNum, out portType);
			if (portType != (int)MccDaq.DigitalPortType.AuxPort)
			{
				// this board doesn't have an AuxPort!
				Application.Exit();
			}

			// Check if AuxPort needs configuring 
			// Parameters:
			//     devNum      : 0-based digital device index
			//      mask    : bitmask indicating corresponding bit is in respecitve direction
			int inmask=0, outmask=0;
			DaqBoard.DioConfig.GetDInMask(devNum, out inmask);
			DaqBoard.DioConfig.GetDOutMask(devNum, out outmask);
			// only non-configurable AuxPorts have overlapping input and output masks
			if (0 == (inmask & outmask))
			{
				DaqBoard.DConfigPort(PortNum, MccDaq.DigitalPortDirection.DigitalOut);
			}


			chkSetBit = (new CheckBox[]{_chkSetBit_0, _chkSetBit_1, _chkSetBit_2, _chkSetBit_3,
										   _chkSetBit_4, _chkSetBit_5, _chkSetBit_6, _chkSetBit_7});


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
		this._chkSetBit_7 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_3 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_6 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_2 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_5 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_1 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_4 = new System.Windows.Forms.CheckBox();
		this._chkSetBit_0 = new System.Windows.Forms.CheckBox();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.SuspendLayout();
		// 
		// cmdEndProgram
		// 
		this.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control;
		this.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdEndProgram.Location = new System.Drawing.Point(240, 184);
		this.cmdEndProgram.Name = "cmdEndProgram";
		this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdEndProgram.Size = new System.Drawing.Size(57, 25);
		this.cmdEndProgram.TabIndex = 9;
		this.cmdEndProgram.Text = "Quit";
		this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
		// 
		// _chkSetBit_7
		// 
		this._chkSetBit_7.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_7.Checked = true;
		this._chkSetBit_7.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_7.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_7.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_7.Location = new System.Drawing.Point(192, 152);
		this._chkSetBit_7.Name = "_chkSetBit_7";
		this._chkSetBit_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_7.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_7.TabIndex = 2;
		this._chkSetBit_7.Text = "Set bit 7";
		this._chkSetBit_7.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_3
		// 
		this._chkSetBit_3.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_3.Checked = true;
		this._chkSetBit_3.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_3.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_3.Location = new System.Drawing.Point(48, 152);
		this._chkSetBit_3.Name = "_chkSetBit_3";
		this._chkSetBit_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_3.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_3.TabIndex = 6;
		this._chkSetBit_3.Text = "Set bit 3";
		this._chkSetBit_3.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_6
		// 
		this._chkSetBit_6.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_6.Checked = true;
		this._chkSetBit_6.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_6.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_6.Location = new System.Drawing.Point(192, 128);
		this._chkSetBit_6.Name = "_chkSetBit_6";
		this._chkSetBit_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_6.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_6.TabIndex = 3;
		this._chkSetBit_6.Text = "Set bit 6";
		this._chkSetBit_6.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_2
		// 
		this._chkSetBit_2.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_2.Checked = true;
		this._chkSetBit_2.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_2.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_2.Location = new System.Drawing.Point(48, 128);
		this._chkSetBit_2.Name = "_chkSetBit_2";
		this._chkSetBit_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_2.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_2.TabIndex = 7;
		this._chkSetBit_2.Text = "Set bit 2";
		this._chkSetBit_2.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_5
		// 
		this._chkSetBit_5.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_5.Checked = true;
		this._chkSetBit_5.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_5.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_5.Location = new System.Drawing.Point(192, 104);
		this._chkSetBit_5.Name = "_chkSetBit_5";
		this._chkSetBit_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_5.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_5.TabIndex = 4;
		this._chkSetBit_5.Text = "Set bit 5";
		this._chkSetBit_5.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_1
		// 
		this._chkSetBit_1.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_1.Checked = true;
		this._chkSetBit_1.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_1.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_1.Location = new System.Drawing.Point(48, 104);
		this._chkSetBit_1.Name = "_chkSetBit_1";
		this._chkSetBit_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_1.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_1.TabIndex = 8;
		this._chkSetBit_1.Text = "Set bit 1";
		this._chkSetBit_1.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_4
		// 
		this._chkSetBit_4.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_4.Checked = true;
		this._chkSetBit_4.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_4.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_4.Location = new System.Drawing.Point(192, 80);
		this._chkSetBit_4.Name = "_chkSetBit_4";
		this._chkSetBit_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_4.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_4.TabIndex = 5;
		this._chkSetBit_4.Text = "Set bit 4";
		this._chkSetBit_4.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_0
		// 
		this._chkSetBit_0.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_0.Checked = true;
		this._chkSetBit_0.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_0.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_0.Location = new System.Drawing.Point(48, 80);
		this._chkSetBit_0.Name = "_chkSetBit_0";
		this._chkSetBit_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_0.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_0.TabIndex = 1;
		this._chkSetBit_0.Text = "Set bit 0";
		this._chkSetBit_0.CheckedChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(40, 16);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(249, 41);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DBitOut() with AuxPort";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmSetBitOut
		// 
		this.AcceptButton = this.cmdEndProgram;
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(339, 222);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdEndProgram,
																		this._chkSetBit_7,
																		this._chkSetBit_3,
																		this._chkSetBit_6,
																		this._chkSetBit_2,
																		this._chkSetBit_5,
																		this._chkSetBit_1,
																		this._chkSetBit_4,
																		this._chkSetBit_0,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmSetBitOut";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Digital Bit Out";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmSetBitOut());
		}
	    		

		private void chkSetBit_CheckStateChanged(object eventSender, System.EventArgs eventArgs) 
		{
			int BitNum = Array.IndexOf(chkSetBit, eventSender);
			MccDaq.DigitalLogicState BitValue = MccDaq.DigitalLogicState.Low;
			if (chkSetBit[BitNum].Checked)
				BitValue = MccDaq.DigitalLogicState.High;
			
			MccDaq.DigitalPortType PortType = PortNum;
			MccDaq.ErrorInfo ULStat = DaqBoard.DBitOut(PortType, BitNum, BitValue);
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.BadBitNumber)
			{
				MessageBox.Show("Boards only supports bit numbers less than " + BitNum.ToString("0"), "Bit value too high", 0);
				
			}
		}


		private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
		{
			short DataValue = 0;
			MccDaq.ErrorInfo ULStat = DaqBoard.DOut(PortNum, DataValue);
			


			Application.Exit();
		}

	}
}