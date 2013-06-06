// ==============================================================================
//
//  File:                         ULDI06.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DConfigBit()
//
//  Purpose:                      Reads the status of a single bit within a digital
//                                port.
//
//  Demonstration:                configures a single bit (within a digital port)
//                                for input and reads the bit status
//
//  Other Library Calls:          MccDaq.MccBoard.DBitIn()
//                                MccDaq.MccService.ErrHandling()
//                                MccDaq.MccBoard.DioConfig.GetDevType()
//                                MccDaq.MccBoard.DioConfig.GetDInMask()
//                                MccDaq.MccBoard.DioConfig.GetDOutMask()
//
//  Special Requirements:         Board 0 must have a digital port that supports
//                                MccDaq.MccBoard.DConfigBit function.
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

namespace ULDI06
{
	public class frmDigIn : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopRead;
		public Timer tmrReadInputs;
		public Label lblBitNum;
		public Label lblInstruct;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		const MccDaq.DigitalPortType PortType = MccDaq.DigitalPortType.AuxPort; //  set port type to programmable
		const short BitNum = 0; //  test bit zero
		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalIn; //  program port for input mode

		public frmDigIn()
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

				//  configure a single bit for input or output
				//   Parameters:
				//     PortType   :the port for which to configure the bit
				//     BitNum     :the bit to configure
				//     Direction  :sets the bit for input or output
				ULStat = DaqBoard.DConfigBit(PortType, BitNum, Direction);
			}
			
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
			this.tmrReadInputs = new System.Windows.Forms.Timer(this.components);
			this.lblBitNum = new System.Windows.Forms.Label();
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
			this.cmdStopRead.Location = new System.Drawing.Point(248, 184);
			this.cmdStopRead.Name = "cmdStopRead";
			this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopRead.Size = new System.Drawing.Size(57, 33);
			this.cmdStopRead.TabIndex = 1;
			this.cmdStopRead.Text = "Quit";
			this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
			// 
			// tmrReadInputs
			// 
			this.tmrReadInputs.Enabled = true;
			this.tmrReadInputs.Interval = 200;
			this.tmrReadInputs.Tick += new System.EventHandler(this.tmrReadInputs_Tick);
			// 
			// lblBitNum
			// 
			this.lblBitNum.BackColor = System.Drawing.SystemColors.Window;
			this.lblBitNum.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblBitNum.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblBitNum.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblBitNum.Location = new System.Drawing.Point(65, 136);
			this.lblBitNum.Name = "lblBitNum";
			this.lblBitNum.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblBitNum.Size = new System.Drawing.Size(197, 17);
			this.lblBitNum.TabIndex = 4;
			this.lblBitNum.Text = "Bit Number";
			this.lblBitNum.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblInstruct
			// 
			this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
			this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblInstruct.ForeColor = System.Drawing.Color.Red;
			this.lblInstruct.Location = new System.Drawing.Point(59, 56);
			this.lblInstruct.Name = "lblInstruct";
			this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInstruct.Size = new System.Drawing.Size(209, 49);
			this.lblInstruct.TabIndex = 3;
			this.lblInstruct.Text = "You may change the bit state by applying a TTL high or a TTL low to the correspon" +
				"ding pin on the port";
			this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblDemoFunction
			// 
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(59, 16);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(209, 25);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DConfigBit()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// frmDigIn
			// 
			this.AcceptButton = this.cmdStopRead;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(326, 232);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cmdStopRead,
																		  this.lblBitNum,
																		  this.lblInstruct,
																		  this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmDigIn";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Digital Bit Input";
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmDigIn());
		}
	   

		private void cmdStopRead_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopRead.Click */
		{
			Application.Exit();
		}


		private void tmrReadInputs_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrReadInputs.Tick */
		{
			
			tmrReadInputs.Stop();
				
			//  read a single bit status from the digital port

			//   Parameters:
			//     PortType   :the digital I/O port type
			//     BitNum     :the bit to read
			//     BitValue   :the value read from the port
			MccDaq.DigitalLogicState BitValue;
			MccDaq.ErrorInfo ULStat = DaqBoard.DBitIn( PortType, BitNum, out BitValue);

			lblBitNum.Text = "Bit number " + BitNum + " state is " + BitValue.ToString();

			tmrReadInputs.Start();

		}

	}
}