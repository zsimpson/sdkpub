// ==============================================================================
//
//  File:                         ULDI02.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DBitIn()
//
//  Purpose:                      Reads the status of single digital input bit.
//
//Demonstration:                  Configures the first configurable
//                                port (usually FIRSTPORTA) for input and
//                                reads the bit value on the port. Unstable bit
//                                values are due to the nature of
//                                the input ports when left floating.
//
//  Other Library Calls:          MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have a digital input port.
//                                Digital value on an input channel.
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

namespace ULDI02
{
	public class frmDigIn : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStopRead;
		public Timer tmrReadInputs;
		public Label _lblShowBitVal_0;
		public Label _lblShowBitVal_1;
		public Label _lblShowBitVal_2;
		public Label _lblShowBitVal_3;
		public Label _lblShowBitVal_4;
		public Label _lblShowBitVal_5;
		public Label _lblShowBitVal_6;
		public Label _lblShowBitVal_7;
		public Label lblBitVal;
		public Label _lblShowBitNum_7;
		public Label _lblShowBitNum_6;
		public Label _lblShowBitNum_5;
		public Label _lblShowBitNum_4;
		public Label _lblShowBitNum_3;
		public Label _lblShowBitNum_2;
		public Label _lblShowBitNum_1;
		public Label _lblShowBitNum_0;
		public Label lblBitNum;
		public Label lblInstruct;
		public Label lblDemoFunction;

		public Label[] lblShowBitNum;
		public Label[] lblShowBitVal;

		private MccDaq.MccBoard DaqBoard;
		private MccDaq.DigitalPortType PortNum;
	    private short FirstBit;
        private short MaxBits;

		const MccDaq.DigitalPortDirection Direction = MccDaq.DigitalPortDirection.DigitalIn; //  program port for input mode

		public frmDigIn()
		{
	        
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			lblShowBitNum = (new Label[]{_lblShowBitNum_0, _lblShowBitNum_1, _lblShowBitNum_2, _lblShowBitNum_3,
										_lblShowBitNum_4, _lblShowBitNum_5, _lblShowBitNum_6, _lblShowBitNum_7});
	        
			lblShowBitVal = (new Label[]{_lblShowBitVal_0, _lblShowBitVal_1, _lblShowBitVal_2, _lblShowBitVal_3,
										_lblShowBitVal_4, _lblShowBitVal_5, _lblShowBitVal_6, _lblShowBitVal_7});

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
                MaxBits = 8;
				break;

			  case (int) MccDaq.DigitalPortType.FirstPortB:
                FirstBit = 8;
                MaxBits = 8;
				break;

			  case (int) MccDaq.DigitalPortType.FirstPortCL:
                FirstBit = 16; 
                MaxBits = 8;
				break;

			  case (int) MccDaq.DigitalPortType.FirstPortCH:
                FirstBit = 20;
                MaxBits = 4;
				break;

			  default:
                FirstBit = 0;
				MaxBits = 8;
				break;
			}

			//  configure the first port for digital input
			//   Parameters:
			//     PortNum    :the input port
			//     Direction  :sets the port for input or output
		    
		    PortNum = (MccDaq.DigitalPortType) FirstPort;
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
		  this.cmdStopRead = new System.Windows.Forms.Button();
		  this.tmrReadInputs = new System.Windows.Forms.Timer(this.components);
		  this._lblShowBitVal_0 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_1 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_2 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_3 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_4 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_5 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_6 = new System.Windows.Forms.Label();
		  this._lblShowBitVal_7 = new System.Windows.Forms.Label();
		  this.lblBitVal = new System.Windows.Forms.Label();
		  this._lblShowBitNum_7 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_6 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_5 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_4 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_3 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_2 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_1 = new System.Windows.Forms.Label();
		  this._lblShowBitNum_0 = new System.Windows.Forms.Label();
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
		  this.cmdStopRead.TabIndex = 20;
		  this.cmdStopRead.Text = "Quit";
		  this.cmdStopRead.Click += new System.EventHandler(this.cmdStopRead_Click);
		  // 
		  // tmrReadInputs
		  // 
		  this.tmrReadInputs.Enabled = true;
		  this.tmrReadInputs.Interval = 200;
		  this.tmrReadInputs.Tick += new System.EventHandler(this.tmrReadInputs_Tick);
		  // 
		  // _lblShowBitVal_0
		  // 
		  this._lblShowBitVal_0.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_0.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_0.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_0.Location = new System.Drawing.Point(288, 144);
		  this._lblShowBitVal_0.Name = "_lblShowBitVal_0";
		  this._lblShowBitVal_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_0.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_0.TabIndex = 1;
		  this._lblShowBitVal_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_1
		  // 
		  this._lblShowBitVal_1.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_1.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_1.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_1.Location = new System.Drawing.Point(264, 144);
		  this._lblShowBitVal_1.Name = "_lblShowBitVal_1";
		  this._lblShowBitVal_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_1.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_1.TabIndex = 2;
		  this._lblShowBitVal_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_2
		  // 
		  this._lblShowBitVal_2.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_2.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_2.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_2.Location = new System.Drawing.Point(240, 144);
		  this._lblShowBitVal_2.Name = "_lblShowBitVal_2";
		  this._lblShowBitVal_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_2.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_2.TabIndex = 3;
		  this._lblShowBitVal_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_3
		  // 
		  this._lblShowBitVal_3.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_3.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_3.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_3.Location = new System.Drawing.Point(216, 144);
		  this._lblShowBitVal_3.Name = "_lblShowBitVal_3";
		  this._lblShowBitVal_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_3.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_3.TabIndex = 4;
		  this._lblShowBitVal_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_4
		  // 
		  this._lblShowBitVal_4.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_4.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_4.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_4.Location = new System.Drawing.Point(168, 144);
		  this._lblShowBitVal_4.Name = "_lblShowBitVal_4";
		  this._lblShowBitVal_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_4.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_4.TabIndex = 5;
		  this._lblShowBitVal_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_5
		  // 
		  this._lblShowBitVal_5.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_5.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_5.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_5.Location = new System.Drawing.Point(144, 144);
		  this._lblShowBitVal_5.Name = "_lblShowBitVal_5";
		  this._lblShowBitVal_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_5.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_5.TabIndex = 6;
		  this._lblShowBitVal_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_6
		  // 
		  this._lblShowBitVal_6.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_6.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_6.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_6.Location = new System.Drawing.Point(120, 144);
		  this._lblShowBitVal_6.Name = "_lblShowBitVal_6";
		  this._lblShowBitVal_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_6.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_6.TabIndex = 7;
		  this._lblShowBitVal_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitVal_7
		  // 
		  this._lblShowBitVal_7.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitVal_7.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitVal_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitVal_7.ForeColor = System.Drawing.Color.Blue;
		  this._lblShowBitVal_7.Location = new System.Drawing.Point(96, 144);
		  this._lblShowBitVal_7.Name = "_lblShowBitVal_7";
		  this._lblShowBitVal_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitVal_7.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitVal_7.TabIndex = 0;
		  this._lblShowBitVal_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // lblBitVal
		  // 
		  this.lblBitVal.BackColor = System.Drawing.SystemColors.Window;
		  this.lblBitVal.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblBitVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblBitVal.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblBitVal.Location = new System.Drawing.Point(16, 144);
		  this.lblBitVal.Name = "lblBitVal";
		  this.lblBitVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblBitVal.Size = new System.Drawing.Size(65, 17);
		  this.lblBitVal.TabIndex = 8;
		  this.lblBitVal.Text = "Bit Value:";
		  this.lblBitVal.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // _lblShowBitNum_7
		  // 
		  this._lblShowBitNum_7.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_7.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_7.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_7.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_7.Location = new System.Drawing.Point(288, 120);
		  this._lblShowBitNum_7.Name = "_lblShowBitNum_7";
		  this._lblShowBitNum_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_7.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_7.TabIndex = 17;
		  this._lblShowBitNum_7.Text = "0";
		  this._lblShowBitNum_7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_6
		  // 
		  this._lblShowBitNum_6.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_6.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_6.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_6.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_6.Location = new System.Drawing.Point(264, 120);
		  this._lblShowBitNum_6.Name = "_lblShowBitNum_6";
		  this._lblShowBitNum_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_6.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_6.TabIndex = 16;
		  this._lblShowBitNum_6.Text = "1";
		  this._lblShowBitNum_6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_5
		  // 
		  this._lblShowBitNum_5.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_5.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_5.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_5.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_5.Location = new System.Drawing.Point(240, 120);
		  this._lblShowBitNum_5.Name = "_lblShowBitNum_5";
		  this._lblShowBitNum_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_5.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_5.TabIndex = 15;
		  this._lblShowBitNum_5.Text = "2";
		  this._lblShowBitNum_5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_4
		  // 
		  this._lblShowBitNum_4.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_4.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_4.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_4.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_4.Location = new System.Drawing.Point(216, 120);
		  this._lblShowBitNum_4.Name = "_lblShowBitNum_4";
		  this._lblShowBitNum_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_4.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_4.TabIndex = 14;
		  this._lblShowBitNum_4.Text = "3";
		  this._lblShowBitNum_4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_3
		  // 
		  this._lblShowBitNum_3.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_3.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_3.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_3.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_3.Location = new System.Drawing.Point(168, 120);
		  this._lblShowBitNum_3.Name = "_lblShowBitNum_3";
		  this._lblShowBitNum_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_3.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_3.TabIndex = 13;
		  this._lblShowBitNum_3.Text = "4";
		  this._lblShowBitNum_3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_2
		  // 
		  this._lblShowBitNum_2.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_2.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_2.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_2.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_2.Location = new System.Drawing.Point(144, 120);
		  this._lblShowBitNum_2.Name = "_lblShowBitNum_2";
		  this._lblShowBitNum_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_2.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_2.TabIndex = 12;
		  this._lblShowBitNum_2.Text = "5";
		  this._lblShowBitNum_2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_1
		  // 
		  this._lblShowBitNum_1.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_1.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_1.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_1.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_1.Location = new System.Drawing.Point(120, 120);
		  this._lblShowBitNum_1.Name = "_lblShowBitNum_1";
		  this._lblShowBitNum_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_1.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_1.TabIndex = 11;
		  this._lblShowBitNum_1.Text = "6";
		  this._lblShowBitNum_1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // _lblShowBitNum_0
		  // 
		  this._lblShowBitNum_0.BackColor = System.Drawing.SystemColors.Window;
		  this._lblShowBitNum_0.Cursor = System.Windows.Forms.Cursors.Default;
		  this._lblShowBitNum_0.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this._lblShowBitNum_0.ForeColor = System.Drawing.SystemColors.WindowText;
		  this._lblShowBitNum_0.Location = new System.Drawing.Point(96, 120);
		  this._lblShowBitNum_0.Name = "_lblShowBitNum_0";
		  this._lblShowBitNum_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this._lblShowBitNum_0.Size = new System.Drawing.Size(17, 17);
		  this._lblShowBitNum_0.TabIndex = 10;
		  this._lblShowBitNum_0.Text = "7";
		  this._lblShowBitNum_0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		  // 
		  // lblBitNum
		  // 
		  this.lblBitNum.BackColor = System.Drawing.SystemColors.Window;
		  this.lblBitNum.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblBitNum.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblBitNum.ForeColor = System.Drawing.SystemColors.WindowText;
		  this.lblBitNum.Location = new System.Drawing.Point(8, 120);
		  this.lblBitNum.Name = "lblBitNum";
		  this.lblBitNum.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblBitNum.Size = new System.Drawing.Size(73, 17);
		  this.lblBitNum.TabIndex = 9;
		  this.lblBitNum.Text = "Bit Number:";
		  this.lblBitNum.TextAlign = System.Drawing.ContentAlignment.TopRight;
		  // 
		  // lblInstruct
		  // 
		  this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
		  this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
		  this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		  this.lblInstruct.ForeColor = System.Drawing.Color.Red;
		  this.lblInstruct.Location = new System.Drawing.Point(64, 56);
		  this.lblInstruct.Name = "lblInstruct";
		  this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
		  this.lblInstruct.Size = new System.Drawing.Size(209, 33);
		  this.lblInstruct.TabIndex = 19;
		  this.lblInstruct.Text = "Input a TTL logic level at the first port inputs to change Bit Value:";
		  this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
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
		  this.lblDemoFunction.Size = new System.Drawing.Size(297, 25);
		  this.lblDemoFunction.TabIndex = 18;
		  this.lblDemoFunction.Text = "Demonstration of Mccdaq.MccBoard.DBitIn()";
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
																	  this._lblShowBitVal_0,
																	  this._lblShowBitVal_1,
																	  this._lblShowBitVal_2,
																	  this._lblShowBitVal_3,
																	  this._lblShowBitVal_4,
																	  this._lblShowBitVal_5,
																	  this._lblShowBitVal_6,
																	  this._lblShowBitVal_7,
																	  this.lblBitVal,
																	  this._lblShowBitNum_7,
																	  this._lblShowBitNum_6,
																	  this._lblShowBitNum_5,
																	  this._lblShowBitNum_4,
																	  this._lblShowBitNum_3,
																	  this._lblShowBitNum_2,
																	  this._lblShowBitNum_1,
																	  this._lblShowBitNum_0,
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
			MccDaq.DigitalPortType PortType;
		
			MccDaq.DigitalLogicState BitValue;
			int BitNum;
			MccDaq.ErrorInfo ULStat;
			for (short i=0; i<MaxBits; ++i)
			{
			   // For boards whose first port is not FIRSTPORTA (such as the USB-ERB08
			   // and the USB-SSR08) offset the BitNum by FirstBit

			   if (PortNum == MccDaq.DigitalPortType.AuxPort)
				 PortType = MccDaq.DigitalPortType.AuxPort;
			   else
				 PortType = MccDaq.DigitalPortType.FirstPortA;
			
				//  read the bits of FirstPortA digital input and display

				//   Parameters:
				//     PortType    :the type of port
				//     BitNum     :the number of the bit to read from the port
				//     BitValue   :the value read from the port
				BitNum = i;
	            
				ULStat = DaqBoard.DBitIn( PortType, FirstBit + BitNum, out BitValue);
	            
				lblShowBitVal[i].Text = Convert.ToInt32(BitValue).ToString("0");
			}
	      
			tmrReadInputs.Start();
		}

	}
}