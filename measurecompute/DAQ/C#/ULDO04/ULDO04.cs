// ==============================================================================
//
//  File:                         ULDO04.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DOut()
//
//  Purpose:                      Writes a byte to AuxPort.
//
//  Demonstration:                Writes a selected value to AuxPort.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//                                MccDaq.MccBoard.DioConfig.GetDevType()
//                                MccDaq.MccBoard.DioConfig.GetDInMask()
//                                MccDaq.MccBoard.DioConfig.GetDOutMask()
//								  MccDaq.MccBoard.DConfigPort()
//
//  Special Requirements:         Board 0 must have a digital port.
//
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

namespace ULDO04
{
	public class frmDigAuxOut : System.Windows.Forms.Form
	{
	 
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public HScrollBar hsbSetPortVal;
		public TextBox txtShowSetVal;
		public RadioButton opt8Bit;
		public RadioButton opt4Bit;
		public Label lblShowWriteVal;
		public Label lblWriteVal;
		public Label lblInstruct;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		const MccDaq.DigitalPortType PortNum = MccDaq.DigitalPortType.AuxPort; //  set port type to auxilliary

		public frmDigAuxOut()
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
		this.hsbSetPortVal = new System.Windows.Forms.HScrollBar();
		this.txtShowSetVal = new System.Windows.Forms.TextBox();
		this.opt8Bit = new System.Windows.Forms.RadioButton();
		this.opt4Bit = new System.Windows.Forms.RadioButton();
		this.lblShowWriteVal = new System.Windows.Forms.Label();
		this.lblWriteVal = new System.Windows.Forms.Label();
		this.lblInstruct = new System.Windows.Forms.Label();
		this.lblDemoFunction = new System.Windows.Forms.Label();
		this.SuspendLayout();
		// 
		// cmdEndProgram
		// 
		this.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control;
		this.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdEndProgram.Location = new System.Drawing.Point(232, 224);
		this.cmdEndProgram.Name = "cmdEndProgram";
		this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdEndProgram.Size = new System.Drawing.Size(65, 33);
		this.cmdEndProgram.TabIndex = 6;
		this.cmdEndProgram.Text = "Quit";
		this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
		// 
		// hsbSetPortVal
		// 
		this.hsbSetPortVal.Cursor = System.Windows.Forms.Cursors.Default;
		this.hsbSetPortVal.LargeChange = 3;
		this.hsbSetPortVal.Location = new System.Drawing.Point(24, 144);
		this.hsbSetPortVal.Maximum = 17;
		this.hsbSetPortVal.Name = "hsbSetPortVal";
		this.hsbSetPortVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.hsbSetPortVal.Size = new System.Drawing.Size(209, 17);
		this.hsbSetPortVal.TabIndex = 1;
		this.hsbSetPortVal.TabStop = true;
		this.hsbSetPortVal.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hsbSetPortVal_Scroll);
		// 
		// txtShowSetVal
		// 
		this.txtShowSetVal.AcceptsReturn = true;
		this.txtShowSetVal.AutoSize = false;
		this.txtShowSetVal.BackColor = System.Drawing.SystemColors.Window;
		this.txtShowSetVal.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.txtShowSetVal.Cursor = System.Windows.Forms.Cursors.IBeam;
		this.txtShowSetVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.txtShowSetVal.ForeColor = System.Drawing.SystemColors.WindowText;
		this.txtShowSetVal.Location = new System.Drawing.Point(248, 136);
		this.txtShowSetVal.MaxLength = 0;
		this.txtShowSetVal.Name = "txtShowSetVal";
		this.txtShowSetVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.txtShowSetVal.Size = new System.Drawing.Size(49, 25);
		this.txtShowSetVal.TabIndex = 7;
		this.txtShowSetVal.Text = "";
		this.txtShowSetVal.TextChanged += new System.EventHandler(this.txtShowSetVal_TextChanged);
		// 
		// opt8Bit
		// 
		this.opt8Bit.BackColor = System.Drawing.SystemColors.Window;
		this.opt8Bit.Cursor = System.Windows.Forms.Cursors.Default;
		this.opt8Bit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.opt8Bit.ForeColor = System.Drawing.SystemColors.WindowText;
		this.opt8Bit.Location = new System.Drawing.Point(224, 88);
		this.opt8Bit.Name = "opt8Bit";
		this.opt8Bit.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.opt8Bit.Size = new System.Drawing.Size(73, 17);
		this.opt8Bit.TabIndex = 3;
		this.opt8Bit.TabStop = true;
		this.opt8Bit.Text = "8 Bit Port";
		this.opt8Bit.CheckedChanged += new System.EventHandler(this.opt8Bit_CheckedChanged);
		// 
		// opt4Bit
		// 
		this.opt4Bit.BackColor = System.Drawing.SystemColors.Window;
		this.opt4Bit.Checked = true;
		this.opt4Bit.Cursor = System.Windows.Forms.Cursors.Default;
		this.opt4Bit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.opt4Bit.ForeColor = System.Drawing.SystemColors.WindowText;
		this.opt4Bit.Location = new System.Drawing.Point(224, 72);
		this.opt4Bit.Name = "opt4Bit";
		this.opt4Bit.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.opt4Bit.Size = new System.Drawing.Size(73, 17);
		this.opt4Bit.TabIndex = 2;
		this.opt4Bit.TabStop = true;
		this.opt4Bit.Text = "4 Bit Port";
		this.opt4Bit.CheckedChanged += new System.EventHandler(this.opt4Bit_CheckedChanged);
		// 
		// lblShowWriteVal
		// 
		this.lblShowWriteVal.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowWriteVal.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowWriteVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowWriteVal.ForeColor = System.Drawing.Color.Blue;
		this.lblShowWriteVal.Location = new System.Drawing.Point(248, 184);
		this.lblShowWriteVal.Name = "lblShowWriteVal";
		this.lblShowWriteVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowWriteVal.Size = new System.Drawing.Size(41, 17);
		this.lblShowWriteVal.TabIndex = 5;
		// 
		// lblWriteVal
		// 
		this.lblWriteVal.BackColor = System.Drawing.SystemColors.Window;
		this.lblWriteVal.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblWriteVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblWriteVal.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblWriteVal.Location = new System.Drawing.Point(24, 184);
		this.lblWriteVal.Name = "lblWriteVal";
		this.lblWriteVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblWriteVal.Size = new System.Drawing.Size(209, 17);
		this.lblWriteVal.TabIndex = 4;
		// 
		// lblInstruct
		// 
		this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblInstruct.ForeColor = System.Drawing.Color.Red;
		this.lblInstruct.Location = new System.Drawing.Point(24, 72);
		this.lblInstruct.Name = "lblInstruct";
		this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct.Size = new System.Drawing.Size(169, 49);
		this.lblInstruct.TabIndex = 8;
		this.lblInstruct.Text = "Select 4 or 8 bit port and use the scoll bar or the text box to set output data v" +
			"alue.";
		this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		this.lblDemoFunction.Size = new System.Drawing.Size(225, 41);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DOut() and AuxPort";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmDigAuxOut
		// 
		this.AcceptButton = this.cmdEndProgram;
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(331, 281);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdEndProgram,
																		this.hsbSetPortVal,
																		this.txtShowSetVal,
																		this.opt8Bit,
																		this.opt4Bit,
																		this.lblShowWriteVal,
																		this.lblWriteVal,
																		this.lblInstruct,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmDigAuxOut";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Digital Out (AUXPORT)";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmDigAuxOut());
		}
	    

		
		private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
		{
			short  DataValue = 0;
			MccDaq.ErrorInfo ULStat = DaqBoard.DOut(PortNum, DataValue);
			

			Application.Exit();
		}


		private void hsbSetPortVal_Change(int newScrollValue)
		{
			//  write the value to AuxPort
			//   Parameters:
			//     PortNum    :the output port
			//     DataValue  :the value written to the port
			short DataValue = (short)newScrollValue;
			txtShowSetVal.Text = DataValue.ToString("0");
			MccDaq.ErrorInfo ULStat = DaqBoard.DOut(PortNum, DataValue);

			lblWriteVal.Text = "The value written to AuxPort was:";
			lblShowWriteVal.Text = DataValue.ToString("0");
		}



		private void opt4Bit_CheckedChanged(object eventSender, System.EventArgs eventArgs) /* Handles opt4Bit.CheckedChanged */
		{

			if (opt4Bit.Checked)
			{
				short NewLargeChange;

				hsbSetPortVal.Maximum = (15 + hsbSetPortVal.LargeChange - 1);
				NewLargeChange = 3;
				hsbSetPortVal.Maximum = hsbSetPortVal.Maximum + NewLargeChange - hsbSetPortVal.LargeChange;
				hsbSetPortVal.LargeChange = NewLargeChange;
			}
		}


		private void opt8Bit_CheckedChanged(object eventSender, System.EventArgs eventArgs) /* Handles opt8Bit.CheckedChanged */
		{
			if (opt8Bit.Checked)
			{
				short NewLargeChange;

				hsbSetPortVal.Maximum = (255 + hsbSetPortVal.LargeChange - 1);
				NewLargeChange = 51;
				hsbSetPortVal.Maximum = hsbSetPortVal.Maximum + NewLargeChange - hsbSetPortVal.LargeChange;
				hsbSetPortVal.LargeChange = NewLargeChange;
			}
		}


		private void txtShowSetVal_TextChanged(object eventSender, System.EventArgs eventArgs) /* Handles txtShowSetVal.TextChanged */
		{

			if (Convert.ToInt16(txtShowSetVal.Text) > (hsbSetPortVal.Maximum - hsbSetPortVal.LargeChange + 1))
				txtShowSetVal.Text = (hsbSetPortVal.Maximum - hsbSetPortVal.LargeChange + 1).ToString("0");

			hsbSetPortVal.Value = int.Parse(txtShowSetVal.Text);

		}

		private void hsbSetPortVal_Scroll(object eventSender, ScrollEventArgs eventArgs) /* Handles hsbSetPortVal.Scroll */
		{

			if(eventArgs.Type == ScrollEventType.EndScroll)
				hsbSetPortVal_Change(eventArgs.NewValue);
			
		}



	}
}