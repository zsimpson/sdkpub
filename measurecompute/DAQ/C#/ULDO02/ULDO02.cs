// ==============================================================================
//
//  File:                         ULDO02.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DBitOut()
//
//  Purpose:                      Sets the state of a single digital output bit.
//
//  Demonstration:                Configures FirstPortA for output and writes
//                                the bit values.
//
//  Other Library Calls:          MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccService.ErrHandling()
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

namespace ULDO02
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
	    private MccDaq.DigitalPortType PortNum;
	    private short FirstBit;

		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalOut; //  program first digital port for output mode


		public frmSetBitOut()
		{
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			chkSetBit = (new CheckBox[]{_chkSetBit_0, _chkSetBit_1, _chkSetBit_2, _chkSetBit_3,
										_chkSetBit_4, _chkSetBit_5, _chkSetBit_6, _chkSetBit_7});

			//  Initiate error handling
			//   activating error handling will trap errors like
			//   bad channel numbers and non-configured conditions.
			//   Parameters:
			//     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
			//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
			
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
			


			// Create a new MccBoard object for Board 0
			DaqBoard = new MccDaq.MccBoard(0);


		  //Get the first port on the device - some devices (such as the
		  //USB-ERB08 and USB-SSR08) don't have FirstPortA, but do have
		  //FirstPortCL.

		  //Parameters:
		  //      DevNum      : 0-based digital device index
		  //      FirstPort   : return value for type of device

		  int DevNum = 0;
		  int FirstPort = 0;
		  ULStat = DaqBoard.DioConfig.GetDevType(0, out FirstPort);

		  switch(FirstPort)
		  {
			case (int) MccDaq.DigitalPortType.FirstPortA:
			  FirstBit = 0;
			  break;

			case (int) MccDaq.DigitalPortType.FirstPortB:
			  FirstBit = 8;
			  break;

			case (int) MccDaq.DigitalPortType.FirstPortCL:
			  FirstBit = 16; 
			  break;

			case (int) MccDaq.DigitalPortType.FirstPortCH:
			  FirstBit = 20;
			  break;

			default:
			  FirstBit = 0;
			  break;
		  }

		  //  configure the first port for digital input
		  //   Parameters:
		  //     PortNum    :the input port
		  //     Direction  :sets the port for input or output
		    
		  PortNum = (MccDaq.DigitalPortType) FirstPort;
		  ULStat = DaqBoard.DConfigPort(PortNum, Direction);

		  // if the first port is FIRSTPORTCL, configure FIRSTPORTCH, too
          if(PortNum == MccDaq.DigitalPortType.FirstPortCL)
            ULStat = DaqBoard.DConfigPort(PortNum + 1, Direction);
			
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
		this._chkSetBit_7.Location = new System.Drawing.Point(192, 136);
		this._chkSetBit_7.Name = "_chkSetBit_7";
		this._chkSetBit_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_7.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_7.TabIndex = 2;
		this._chkSetBit_7.Text = "Set bit 7";
		this._chkSetBit_7.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_3
		// 
		this._chkSetBit_3.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_3.Checked = true;
		this._chkSetBit_3.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_3.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_3.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_3.Location = new System.Drawing.Point(48, 136);
		this._chkSetBit_3.Name = "_chkSetBit_3";
		this._chkSetBit_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_3.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_3.TabIndex = 6;
		this._chkSetBit_3.Text = "Set bit 3";
		this._chkSetBit_3.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_6
		// 
		this._chkSetBit_6.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_6.Checked = true;
		this._chkSetBit_6.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_6.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_6.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_6.Location = new System.Drawing.Point(192, 112);
		this._chkSetBit_6.Name = "_chkSetBit_6";
		this._chkSetBit_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_6.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_6.TabIndex = 3;
		this._chkSetBit_6.Text = "Set bit 6";
		this._chkSetBit_6.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_2
		// 
		this._chkSetBit_2.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_2.Checked = true;
		this._chkSetBit_2.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_2.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_2.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_2.Location = new System.Drawing.Point(48, 112);
		this._chkSetBit_2.Name = "_chkSetBit_2";
		this._chkSetBit_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_2.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_2.TabIndex = 7;
		this._chkSetBit_2.Text = "Set bit 2";
		this._chkSetBit_2.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_5
		// 
		this._chkSetBit_5.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_5.Checked = true;
		this._chkSetBit_5.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_5.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_5.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_5.Location = new System.Drawing.Point(192, 88);
		this._chkSetBit_5.Name = "_chkSetBit_5";
		this._chkSetBit_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_5.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_5.TabIndex = 4;
		this._chkSetBit_5.Text = "Set bit 5";
		this._chkSetBit_5.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_1
		// 
		this._chkSetBit_1.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_1.Checked = true;
		this._chkSetBit_1.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_1.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_1.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_1.Location = new System.Drawing.Point(48, 88);
		this._chkSetBit_1.Name = "_chkSetBit_1";
		this._chkSetBit_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_1.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_1.TabIndex = 8;
		this._chkSetBit_1.Text = "Set bit 1";
		this._chkSetBit_1.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_4
		// 
		this._chkSetBit_4.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_4.Checked = true;
		this._chkSetBit_4.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_4.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_4.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_4.Location = new System.Drawing.Point(192, 64);
		this._chkSetBit_4.Name = "_chkSetBit_4";
		this._chkSetBit_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_4.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_4.TabIndex = 5;
		this._chkSetBit_4.Text = "Set bit 4";
		this._chkSetBit_4.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// _chkSetBit_0
		// 
		this._chkSetBit_0.BackColor = System.Drawing.SystemColors.Window;
		this._chkSetBit_0.Checked = true;
		this._chkSetBit_0.CheckState = System.Windows.Forms.CheckState.Indeterminate;
		this._chkSetBit_0.Cursor = System.Windows.Forms.Cursors.Default;
		this._chkSetBit_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this._chkSetBit_0.ForeColor = System.Drawing.SystemColors.WindowText;
		this._chkSetBit_0.Location = new System.Drawing.Point(48, 64);
		this._chkSetBit_0.Name = "_chkSetBit_0";
		this._chkSetBit_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this._chkSetBit_0.Size = new System.Drawing.Size(81, 17);
		this._chkSetBit_0.TabIndex = 1;
		this._chkSetBit_0.Text = "Set bit 0";
		this._chkSetBit_0.CheckStateChanged += new System.EventHandler(this.chkSetBit_CheckStateChanged);
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(16, 16);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(305, 25);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DBitOut()";
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
		    MccDaq.DigitalPortType PortType;

			int BitNum = Array.IndexOf(chkSetBit, eventSender);

		    // For boards whose first port is not FIRSTPORTA (such as the USB-ERB08
            // and the USB-SSR08) offset the BitNum by FirstBit

			if (PortNum == MccDaq.DigitalPortType.AuxPort)
			  PortType = MccDaq.DigitalPortType.AuxPort;
			else
			  PortType = MccDaq.DigitalPortType.FirstPortA;
 
			MccDaq.DigitalLogicState BitValue = MccDaq.DigitalLogicState.Low;
			if (chkSetBit[BitNum].Checked)
				BitValue = MccDaq.DigitalLogicState.High;

			MccDaq.ErrorInfo ULStat = DaqBoard.DBitOut(PortType, FirstBit + BitNum, BitValue);
			
		}


		private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
		{
			ushort DataValue = 0;
			MccDaq.ErrorInfo ULStat = DaqBoard.DOut(PortNum, DataValue);


			Application.Exit();
		}

	}
}