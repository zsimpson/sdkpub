// ==============================================================================
//
//  File:                         ULDO01.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DOut()
//
//  Purpose:                      Writes a byte to digital output ports.
//
//  Demonstration:                Configures FirstPortA for output and writes
//                                a value to the port.
//
//  Other Library Calls:          MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a digital output port.
//                                Board 0 must have programmable digital ports.
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

namespace ULDO01
{
	public class frmSetDigOut : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdEndProgram;
		public TextBox txtValSet;
		public HScrollBar hsbSetDOutVal;
		public Label lblShowValOut;
		public Label lblDataValOut;
		public Label lblValSet;
		public Label lblInstruct;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;
		const MccDaq.DigitalPortType PortNum = MccDaq.DigitalPortType.FirstPortA; //  set port to use
		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalOut; //  program digital port A for output

	 
		public frmSetDigOut()
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

			//  configure FirstPortA for digital output
			//   Parameters:
			//     PortNum    :the output port
			//     Direction  :sets the port for input or output
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);
			
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
		this.txtValSet = new System.Windows.Forms.TextBox();
		this.hsbSetDOutVal = new System.Windows.Forms.HScrollBar();
		this.lblShowValOut = new System.Windows.Forms.Label();
		this.lblDataValOut = new System.Windows.Forms.Label();
		this.lblValSet = new System.Windows.Forms.Label();
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
		this.cmdEndProgram.Location = new System.Drawing.Point(248, 216);
		this.cmdEndProgram.Name = "cmdEndProgram";
		this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdEndProgram.Size = new System.Drawing.Size(57, 33);
		this.cmdEndProgram.TabIndex = 7;
		this.cmdEndProgram.Text = "Quit";
		this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
		// 
		// txtValSet
		// 
		this.txtValSet.AcceptsReturn = true;
		this.txtValSet.AutoSize = false;
		this.txtValSet.BackColor = System.Drawing.SystemColors.Window;
		this.txtValSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.txtValSet.Cursor = System.Windows.Forms.Cursors.IBeam;
		this.txtValSet.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.txtValSet.ForeColor = System.Drawing.SystemColors.WindowText;
		this.txtValSet.Location = new System.Drawing.Point(264, 120);
		this.txtValSet.MaxLength = 0;
		this.txtValSet.Name = "txtValSet";
		this.txtValSet.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.txtValSet.Size = new System.Drawing.Size(41, 25);
		this.txtValSet.TabIndex = 4;
		this.txtValSet.Text = "0";
		this.txtValSet.TextChanged += new System.EventHandler(this.txtValSet_TextChanged);
		// 
		// hsbSetDOutVal
		// 
		this.hsbSetDOutVal.Cursor = System.Windows.Forms.Cursors.Default;
		this.hsbSetDOutVal.LargeChange = 51;
		this.hsbSetDOutVal.Location = new System.Drawing.Point(24, 120);
		this.hsbSetDOutVal.Maximum = 305;
		this.hsbSetDOutVal.Name = "hsbSetDOutVal";
		this.hsbSetDOutVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.hsbSetDOutVal.Size = new System.Drawing.Size(225, 17);
		this.hsbSetDOutVal.TabIndex = 1;
		this.hsbSetDOutVal.TabStop = true;
		this.hsbSetDOutVal.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hsbSetDOutVal_Scroll);
		// 
		// lblShowValOut
		// 
		this.lblShowValOut.BackColor = System.Drawing.SystemColors.Window;
		this.lblShowValOut.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblShowValOut.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblShowValOut.ForeColor = System.Drawing.Color.Blue;
		this.lblShowValOut.Location = new System.Drawing.Point(224, 176);
		this.lblShowValOut.Name = "lblShowValOut";
		this.lblShowValOut.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblShowValOut.Size = new System.Drawing.Size(57, 17);
		this.lblShowValOut.TabIndex = 3;
		// 
		// lblDataValOut
		// 
		this.lblDataValOut.BackColor = System.Drawing.SystemColors.Window;
		this.lblDataValOut.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDataValOut.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDataValOut.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDataValOut.Location = new System.Drawing.Point(32, 176);
		this.lblDataValOut.Name = "lblDataValOut";
		this.lblDataValOut.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDataValOut.Size = new System.Drawing.Size(185, 17);
		this.lblDataValOut.TabIndex = 2;
		// 
		// lblValSet
		// 
		this.lblValSet.BackColor = System.Drawing.SystemColors.Window;
		this.lblValSet.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblValSet.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblValSet.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblValSet.Location = new System.Drawing.Point(256, 96);
		this.lblValSet.Name = "lblValSet";
		this.lblValSet.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblValSet.Size = new System.Drawing.Size(65, 17);
		this.lblValSet.TabIndex = 6;
		this.lblValSet.Text = "Value set:";
		// 
		// lblInstruct
		// 
		this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
		this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblInstruct.ForeColor = System.Drawing.Color.Red;
		this.lblInstruct.Location = new System.Drawing.Point(56, 48);
		this.lblInstruct.Name = "lblInstruct";
		this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblInstruct.Size = new System.Drawing.Size(201, 25);
		this.lblInstruct.TabIndex = 5;
		this.lblInstruct.Text = "Set output value using scroll bar or enter value in Value Set box:";
		this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// lblDemoFunction
		// 
		this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
		this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
		this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
		this.lblDemoFunction.Location = new System.Drawing.Point(24, 8);
		this.lblDemoFunction.Name = "lblDemoFunction";
		this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.lblDemoFunction.Size = new System.Drawing.Size(289, 25);
		this.lblDemoFunction.TabIndex = 0;
		this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DOut()";
		this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// frmSetDigOut
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(331, 267);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdEndProgram,
																		this.txtValSet,
																		this.hsbSetDOutVal,
																		this.lblShowValOut,
																		this.lblDataValOut,
																		this.lblValSet,
																		this.lblInstruct,
																		this.lblDemoFunction});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmSetDigOut";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Digital Output";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmSetDigOut());
		}
	    

		private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
		{
			ushort DataValue=0;
			MccDaq.ErrorInfo ULStat = DaqBoard.DOut(PortNum, DataValue);
			

			Application.Exit();
		}


		private void hsbSetDOutVal_Change(int newScrollValue)
		{
			//  get a value to write to the port
			ushort DataValue = (ushort)newScrollValue;
			txtValSet.Text = DataValue.ToString("0");

			//  write the value to FirstPortA
			//   Parameters:
			//     PortNum    :the output port
			//     DataValue  :the value written to the port
			MccDaq.ErrorInfo ULStat = DaqBoard.DOut(PortNum, DataValue);

			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				lblDataValOut.Text = "Value written to FirstPortA:";
				lblShowValOut.Text = DataValue.ToString("0");
			}

		}


		private void txtValSet_TextChanged(object eventSender, System.EventArgs eventArgs) /* Handles txtValSet.TextChanged */
		{
			if (Convert.ToInt16(txtValSet.Text) > 255) 
				txtValSet.Text = "255";

			hsbSetDOutVal.Value = int.Parse(txtValSet.Text);
			hsbSetDOutVal_Change(hsbSetDOutVal.Value);
		}

		private void hsbSetDOutVal_Scroll(object eventSender, System.Windows.Forms.ScrollEventArgs eventArgs) /* Handles hsbSetDOutVal.Scroll */
		{
			if (eventArgs.Type == System.Windows.Forms.ScrollEventType.EndScroll)
				hsbSetDOutVal_Change(eventArgs.NewValue);
		}

	}
}