// ==============================================================================
//
//  File:                         ULDI01.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DIn()
//
//  Purpose:                      Reads a digital input port.
//
//  Demonstration:                Configures FirstPortA for input and reads
//                                the value on the port.
//
//  Other Library Calls:          MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a digital input port.
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

namespace ULDI01
{
	public class frmDigIn : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopRead;
		public Timer tmrReadInputs;
		public Label lblPortRead;
		public Label lblPortsRead;
		public Label _lblBitVal_0;
		public Label _lblBitVal_1;
		public Label _lblBitVal_2;
		public Label _lblBitVal_3;
		public Label _lblBitVal_4;
		public Label _lblBitVal_5;
		public Label _lblBitVal_6;
		public Label _lblBitVal_7;
		public Label lblBitsRead;
		public Label _lblBitNum_7;
		public Label _lblBitNum_6;
		public Label _lblBitNum_5;
		public Label _lblBitNum_4;
		public Label _lblBitNum_3;
		public Label _lblBitNum_2;
		public Label _lblBitNum_1;
		public Label _lblBitNum_0;
		public Label lblBitList;
		public Label lblInstruct;
		public Label lblDemoFunction;

		public Label[] lblBitNum;
		public Label[] lblBitVal;

		private MccDaq.MccBoard DaqBoard;
		const MccDaq.DigitalPortType PortNum = MccDaq.DigitalPortType.FirstPortA; //  set port to use
		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalIn; //  set direction of port to input


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

			//  configure FirstPortA for digital input
			//   Parameters:
			//     PortNum    :the input port
			//     Direction :sets the port for input or output
			ULStat = DaqBoard.DConfigPort(PortNum, Direction);
			

			lblBitNum = (new Label[]{_lblBitNum_0, _lblBitNum_1, _lblBitNum_2, _lblBitNum_3,
									_lblBitNum_4, _lblBitNum_5, _lblBitNum_6, _lblBitNum_7});
	        

			lblBitVal = (new Label[]{_lblBitVal_0, _lblBitVal_1, _lblBitVal_2, _lblBitVal_3,
									_lblBitVal_4, _lblBitVal_5, _lblBitVal_6, _lblBitVal_7});
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
			this.lblPortRead = new System.Windows.Forms.Label();
			this.lblPortsRead = new System.Windows.Forms.Label();
			this._lblBitVal_0 = new System.Windows.Forms.Label();
			this._lblBitVal_1 = new System.Windows.Forms.Label();
			this._lblBitVal_2 = new System.Windows.Forms.Label();
			this._lblBitVal_3 = new System.Windows.Forms.Label();
			this._lblBitVal_4 = new System.Windows.Forms.Label();
			this._lblBitVal_5 = new System.Windows.Forms.Label();
			this._lblBitVal_6 = new System.Windows.Forms.Label();
			this._lblBitVal_7 = new System.Windows.Forms.Label();
			this.lblBitsRead = new System.Windows.Forms.Label();
			this._lblBitNum_7 = new System.Windows.Forms.Label();
			this._lblBitNum_6 = new System.Windows.Forms.Label();
			this._lblBitNum_5 = new System.Windows.Forms.Label();
			this._lblBitNum_4 = new System.Windows.Forms.Label();
			this._lblBitNum_3 = new System.Windows.Forms.Label();
			this._lblBitNum_2 = new System.Windows.Forms.Label();
			this._lblBitNum_1 = new System.Windows.Forms.Label();
			this._lblBitNum_0 = new System.Windows.Forms.Label();
			this.lblBitList = new System.Windows.Forms.Label();
			this.lblInstruct = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.SuspendLayout();
			//
			// cmdStopRead
			//
			this.cmdStopRead.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopRead.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopRead.Location = new System.Drawing.Point(256, 192);
			this.cmdStopRead.Name = "cmdStopRead";
			this.cmdStopRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopRead.Size = new System.Drawing.Size(57, 33);
			this.cmdStopRead.TabIndex = 14;
			this.cmdStopRead.Text = "Quit";
			this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
			//
			// tmrReadInputs
			//
			this.tmrReadInputs.Enabled = true;
			this.tmrReadInputs.Interval = 500;
			this.tmrReadInputs.Tick += new System.EventHandler(this.tmrReadInputs_Tick);
			//
			// lblPortRead
			//
			this.lblPortRead.BackColor = System.Drawing.SystemColors.Window;
			this.lblPortRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPortRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPortRead.ForeColor = System.Drawing.Color.Blue;
			this.lblPortRead.Location = new System.Drawing.Point(136, 184);
			this.lblPortRead.Name = "lblPortRead";
			this.lblPortRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPortRead.Size = new System.Drawing.Size(33, 17);
			this.lblPortRead.TabIndex = 13;
			//
			// lblPortsRead
			//
			this.lblPortsRead.BackColor = System.Drawing.SystemColors.Window;
			this.lblPortsRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblPortsRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblPortsRead.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblPortsRead.Location = new System.Drawing.Point(24, 184);
			this.lblPortsRead.Name = "lblPortsRead";
			this.lblPortsRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblPortsRead.Size = new System.Drawing.Size(98, 17);
			this.lblPortsRead.TabIndex = 12;
			this.lblPortsRead.Text = "Port value read:";
			this.lblPortsRead.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblBitVal_0
			//
			this._lblBitVal_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_0.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_0.Location = new System.Drawing.Point(296, 136);
			this._lblBitVal_0.Name = "_lblBitVal_0";
			this._lblBitVal_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_0.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_0.TabIndex = 3;
			this._lblBitVal_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_1
			//
			this._lblBitVal_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_1.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_1.Location = new System.Drawing.Point(272, 136);
			this._lblBitVal_1.Name = "_lblBitVal_1";
			this._lblBitVal_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_1.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_1.TabIndex = 4;
			this._lblBitVal_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_2
			//
			this._lblBitVal_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_2.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_2.Location = new System.Drawing.Point(248, 136);
			this._lblBitVal_2.Name = "_lblBitVal_2";
			this._lblBitVal_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_2.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_2.TabIndex = 5;
			this._lblBitVal_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_3
			//
			this._lblBitVal_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_3.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_3.Location = new System.Drawing.Point(224, 136);
			this._lblBitVal_3.Name = "_lblBitVal_3";
			this._lblBitVal_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_3.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_3.TabIndex = 6;
			this._lblBitVal_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_4
			//
			this._lblBitVal_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_4.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_4.Location = new System.Drawing.Point(200, 136);
			this._lblBitVal_4.Name = "_lblBitVal_4";
			this._lblBitVal_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_4.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_4.TabIndex = 7;
			this._lblBitVal_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_5
			//
			this._lblBitVal_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_5.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_5.Location = new System.Drawing.Point(176, 136);
			this._lblBitVal_5.Name = "_lblBitVal_5";
			this._lblBitVal_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_5.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_5.TabIndex = 8;
			this._lblBitVal_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_6
			//
			this._lblBitVal_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_6.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_6.Location = new System.Drawing.Point(152, 136);
			this._lblBitVal_6.Name = "_lblBitVal_6";
			this._lblBitVal_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_6.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_6.TabIndex = 9;
			this._lblBitVal_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitVal_7
			//
			this._lblBitVal_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitVal_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitVal_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitVal_7.ForeColor = System.Drawing.Color.Blue;
			this._lblBitVal_7.Location = new System.Drawing.Point(128, 136);
			this._lblBitVal_7.Name = "_lblBitVal_7";
			this._lblBitVal_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitVal_7.Size = new System.Drawing.Size(17, 17);
			this._lblBitVal_7.TabIndex = 10;
			this._lblBitVal_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblBitsRead
			//
			this.lblBitsRead.BackColor = System.Drawing.SystemColors.Window;
			this.lblBitsRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblBitsRead.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblBitsRead.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblBitsRead.Location = new System.Drawing.Point(24, 136);
			this.lblBitsRead.Name = "lblBitsRead";
			this.lblBitsRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblBitsRead.Size = new System.Drawing.Size(97, 17);
			this.lblBitsRead.TabIndex = 11;
			this.lblBitsRead.Text = "Bit values read:";
			this.lblBitsRead.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// _lblBitNum_7
			//
			this._lblBitNum_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_7.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_7.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_7.Location = new System.Drawing.Point(296, 112);
			this._lblBitNum_7.Name = "_lblBitNum_7";
			this._lblBitNum_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_7.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_7.TabIndex = 22;
			this._lblBitNum_7.Text = "0";
			this._lblBitNum_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_6
			//
			this._lblBitNum_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_6.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_6.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_6.Location = new System.Drawing.Point(272, 112);
			this._lblBitNum_6.Name = "_lblBitNum_6";
			this._lblBitNum_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_6.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_6.TabIndex = 21;
			this._lblBitNum_6.Text = "1";
			this._lblBitNum_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_5
			//
			this._lblBitNum_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_5.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_5.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_5.Location = new System.Drawing.Point(248, 112);
			this._lblBitNum_5.Name = "_lblBitNum_5";
			this._lblBitNum_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_5.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_5.TabIndex = 20;
			this._lblBitNum_5.Text = "2";
			this._lblBitNum_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_4
			//
			this._lblBitNum_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_4.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_4.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_4.Location = new System.Drawing.Point(224, 112);
			this._lblBitNum_4.Name = "_lblBitNum_4";
			this._lblBitNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_4.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_4.TabIndex = 19;
			this._lblBitNum_4.Text = "3";
			this._lblBitNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_3
			//
			this._lblBitNum_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_3.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_3.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_3.Location = new System.Drawing.Point(200, 112);
			this._lblBitNum_3.Name = "_lblBitNum_3";
			this._lblBitNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_3.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_3.TabIndex = 18;
			this._lblBitNum_3.Text = "4";
			this._lblBitNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_2
			//
			this._lblBitNum_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_2.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_2.Location = new System.Drawing.Point(176, 112);
			this._lblBitNum_2.Name = "_lblBitNum_2";
			this._lblBitNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_2.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_2.TabIndex = 17;
			this._lblBitNum_2.Text = "5";
			this._lblBitNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_1
			//
			this._lblBitNum_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_1.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_1.Location = new System.Drawing.Point(152, 112);
			this._lblBitNum_1.Name = "_lblBitNum_1";
			this._lblBitNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_1.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_1.TabIndex = 16;
			this._lblBitNum_1.Text = "6";
			this._lblBitNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// _lblBitNum_0
			//
			this._lblBitNum_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblBitNum_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblBitNum_0.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblBitNum_0.ForeColor = System.Drawing.SystemColors.WindowText;
			this._lblBitNum_0.Location = new System.Drawing.Point(128, 112);
			this._lblBitNum_0.Name = "_lblBitNum_0";
			this._lblBitNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblBitNum_0.Size = new System.Drawing.Size(17, 17);
			this._lblBitNum_0.TabIndex = 15;
			this._lblBitNum_0.Text = "7";
			this._lblBitNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// lblBitList
			//
			this.lblBitList.BackColor = System.Drawing.SystemColors.Window;
			this.lblBitList.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblBitList.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblBitList.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblBitList.Location = new System.Drawing.Point(8, 112);
			this.lblBitList.Name = "lblBitList";
			this.lblBitList.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblBitList.Size = new System.Drawing.Size(113, 17);
			this.lblBitList.TabIndex = 2;
			this.lblBitList.Text = "The first 7 bits are:";
			this.lblBitList.TextAlign = System.Drawing.ContentAlignment.TopRight;
			//
			// lblInstruct
			//
			this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
			this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblInstruct.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblInstruct.ForeColor = System.Drawing.Color.Red;
			this.lblInstruct.Location = new System.Drawing.Point(32, 56);
			this.lblInstruct.Name = "lblInstruct";
			this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInstruct.Size = new System.Drawing.Size(265, 33);
			this.lblInstruct.TabIndex = 1;
			this.lblInstruct.Text = "You may change a bit by applying a TTL high or TTL low to digital inputs on FirstPortA.";
			//
			// lblDemoFunction
			//
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(32, 16);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(265, 25);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DIn()";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			//
			// frmDigIn
			//
			this.AcceptButton = this.cmdStopRead;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(339, 242);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdStopRead, this.lblPortRead, this.lblPortsRead, this._lblBitVal_0, this._lblBitVal_1, this._lblBitVal_2, this._lblBitVal_3, this._lblBitVal_4, this._lblBitVal_5, this._lblBitVal_6, this._lblBitVal_7, this.lblBitsRead, this._lblBitNum_7, this._lblBitNum_6, this._lblBitNum_5, this._lblBitNum_4, this._lblBitNum_3, this._lblBitNum_2, this._lblBitNum_1, this._lblBitNum_0, this.lblBitList, this.lblInstruct, this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(7, 103);
			this.Name = "frmDigIn";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Digital Input";
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
	
			//  read FirstPortA digital input and display

			//  Parameters:
			//    PortNum    :the input port
			//    DataValue  :the value read from the port
			short DataValue = 0;
			MccDaq.ErrorInfo ULStat = DaqBoard.DIn( PortNum, out DataValue);

			//  display the value collected from the port
			lblPortRead.Text = DataValue.ToString("0");

			//  parse DataValue into bit values to indicate on/off status
			for (int i=0; i<=7; ++i)
			{
				if ((DataValue & (1<<i)) != 0)
					lblBitVal[i].Text = "1";	
				else
					lblBitVal[i].Text = "0";
			}

			tmrReadInputs.Start();
		}

	}
}