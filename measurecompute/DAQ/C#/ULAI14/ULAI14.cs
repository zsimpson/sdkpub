// ==============================================================================
//
//  File:                         ULAI14.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.SetTrigger()
//
//  Purpose:                      Selects the Trigger source. This trigger is
//                                used to initiate A/D conversion using
//                                Mccdaq.MccBoard.AInScan(), with
//                                MccDaq.ScanOptions.ExtTrigger Option.
//
//  Demonstration:                Selects the trigger source
//                                Displays the analog input on up to eight channels.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have software selectable
//                                triggering source and type.
//                                Board 0 must have an A/D converter.
//                                Analog signals on up to eight input channels.
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

namespace ULAI14
{
	public class frmDataDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public TextBox txtHighChan;
		public Button cmdStopConvert;
		public Button cmdStart;
		public Label Label1;
		public Label _lblADData_7;
		public Label lblChan7;
		public Label _lblADData_3;
		public Label lblChan3;
		public Label _lblADData_6;
		public Label lblChan6;
		public Label _lblADData_2;
		public Label lblChan2;
		public Label _lblADData_5;
		public Label lblChan5;
		public Label _lblADData_1;
		public Label lblChan1;
		public Label _lblADData_4;
		public Label lblChan4;
		public Label _lblADData_0;
		public Label lblChan0;
		public Label lblDemoFunction;

		public Label[] lblADData;
	   
		const int NumPoints = 600; //  Number of data points to collect
		const int FirstPoint = 0; //  set first element in buffer to transfer to array

		private MccDaq.MccBoard DaqBoard;
		private int HighChan;
		private ushort[] ADData = new ushort[NumPoints]; // array to hold the input values
		private int MemHandle;				//  define a variable to contain the handle for
											//  memory allocated by Windows through MccDaq.MccService.WinBufAlloc()
		

		public frmDataDisplay()
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
			
			//  set aside memory to hold data
			MemHandle = MccDaq.MccService.WinBufAlloc(NumPoints); 
			

			lblADData = (new Label[]{_lblADData_0, _lblADData_1, _lblADData_2, _lblADData_3,
									_lblADData_4, _lblADData_5, _lblADData_6, _lblADData_7});

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

				if (MemHandle != 0 )
					MccDaq.MccService.WinBufFree(MemHandle);

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

		// System.Resources.ResourceManager resources = new System.Resources.ResourceManager(GetType(frmDataDisplay));
			this.components = new System.ComponentModel.Container();
			this.ToolTip1 = new System.Windows.Forms.ToolTip(components);
			this.ToolTip1.Active = true;
			this.txtHighChan = new System.Windows.Forms.TextBox();
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this.cmdStart = new System.Windows.Forms.Button();
			this.Label1 = new System.Windows.Forms.Label();
			this._lblADData_7 = new System.Windows.Forms.Label();
			this.lblChan7 = new System.Windows.Forms.Label();
			this._lblADData_3 = new System.Windows.Forms.Label();
			this.lblChan3 = new System.Windows.Forms.Label();
			this._lblADData_6 = new System.Windows.Forms.Label();
			this.lblChan6 = new System.Windows.Forms.Label();
			this._lblADData_2 = new System.Windows.Forms.Label();
			this.lblChan2 = new System.Windows.Forms.Label();
			this._lblADData_5 = new System.Windows.Forms.Label();
			this.lblChan5 = new System.Windows.Forms.Label();
			this._lblADData_1 = new System.Windows.Forms.Label();
			this.lblChan1 = new System.Windows.Forms.Label();
			this._lblADData_4 = new System.Windows.Forms.Label();
			this.lblChan4 = new System.Windows.Forms.Label();
			this._lblADData_0 = new System.Windows.Forms.Label();
			this.lblChan0 = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
		// 
		// frmDataDisplay
		// 
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.BackColor = System.Drawing.SystemColors.Window;
			this.Text = "Universal Library Analog Input Scan";
			this.ClientSize = new System.Drawing.Size(349, 232);
			this.Location = new System.Drawing.Point(189, 104);
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ForeColor = System.Drawing.Color.Blue;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
			this.ControlBox = true;
			this.Enabled = true;
			this.KeyPreview = false;
			this.MaximizeBox = true;
			this.MinimizeBox = true;
			this.Cursor = System.Windows.Forms.Cursors.Default;
			this.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.ShowInTaskbar = true;
			this.HelpButton = false;
			this.WindowState = System.Windows.Forms.FormWindowState.Normal;
			this.Name = "frmDataDisplay";
		// 
		// txtHighChan
		// 
			this.txtHighChan.AutoSize = false;
			this.txtHighChan.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.txtHighChan.Size = new System.Drawing.Size(25, 19);
			this.txtHighChan.Location = new System.Drawing.Point(216, 66);
			this.txtHighChan.TabIndex = 20;
			this.txtHighChan.Text = "3";
			this.txtHighChan.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtHighChan.AcceptsReturn = true;
			this.txtHighChan.BackColor = System.Drawing.SystemColors.Window;
			this.txtHighChan.CausesValidation = true;
			this.txtHighChan.Enabled = true;
			this.txtHighChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtHighChan.HideSelection = true;
			this.txtHighChan.ReadOnly = false;
			this.txtHighChan.MaxLength = 0;
			this.txtHighChan.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtHighChan.Multiline = false;
			this.txtHighChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtHighChan.ScrollBars = System.Windows.Forms.ScrollBars.None;
			this.txtHighChan.TabStop = true;
			this.txtHighChan.Visible = true;
			this.txtHighChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtHighChan.Name = "txtHighChan";
		// 
		// cmdStopConvert
		// 
			this.cmdStopConvert.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Size = new System.Drawing.Size(58, 26);
			this.cmdStopConvert.Location = new System.Drawing.Point(280, 192);
			this.cmdStopConvert.TabIndex = 17;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.CausesValidation = true;
			this.cmdStopConvert.Enabled = true;
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStopConvert.TabStop = true;
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
		// 
		// cmdStart
		// 
			this.cmdStart.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.cmdStart.Text = "Start";
			this.cmdStart.Size = new System.Drawing.Size(58, 26);
			this.cmdStart.Location = new System.Drawing.Point(208, 192);
			this.cmdStart.TabIndex = 18;
			this.cmdStart.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmdStart.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStart.CausesValidation = true;
			this.cmdStart.Enabled = true;
			this.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStart.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdStart.TabStop = true;
			this.cmdStart.Name = "cmdStart";
			this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);

			this.Label1.BackColor = System.Drawing.SystemColors.Window;
			this.Label1.Text = "Measure Channels 0 to ";
			this.Label1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Label1.Size = new System.Drawing.Size(137, 16);
			this.Label1.Location = new System.Drawing.Point(72, 66);
			this.Label1.TabIndex = 19;
			this.Label1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Label1.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.Label1.Enabled = true;
			this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label1.UseMnemonic = true;
			this.Label1.Visible = true;
			this.Label1.AutoSize = false;
			this.Label1.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.Label1.Name = "Label1";
			this._lblADData_7.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_7.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_7.Size = new System.Drawing.Size(65, 17);
			this._lblADData_7.Location = new System.Drawing.Point(264, 170);
			this._lblADData_7.TabIndex = 16;
			this._lblADData_7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_7.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_7.Enabled = true;
			this._lblADData_7.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_7.UseMnemonic = true;
			this._lblADData_7.Visible = true;
			this._lblADData_7.AutoSize = false;
			this._lblADData_7.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_7.Name = "_lblADData_7";
			this.lblChan7.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan7.Text = "Channel 7:";
			this.lblChan7.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan7.Size = new System.Drawing.Size(65, 17);
			this.lblChan7.Location = new System.Drawing.Point(192, 170);
			this.lblChan7.TabIndex = 8;
			this.lblChan7.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan7.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan7.Enabled = true;
			this.lblChan7.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan7.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan7.UseMnemonic = true;
			this.lblChan7.Visible = true;
			this.lblChan7.AutoSize = false;
			this.lblChan7.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan7.Name = "lblChan7";
			this._lblADData_3.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_3.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_3.Size = new System.Drawing.Size(65, 17);
			this._lblADData_3.Location = new System.Drawing.Point(96, 170);
			this._lblADData_3.TabIndex = 12;
			this._lblADData_3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_3.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_3.Enabled = true;
			this._lblADData_3.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_3.UseMnemonic = true;
			this._lblADData_3.Visible = true;
			this._lblADData_3.AutoSize = false;
			this._lblADData_3.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_3.Name = "_lblADData_3";
			this.lblChan3.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan3.Text = "Channel 3:";
			this.lblChan3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan3.Size = new System.Drawing.Size(65, 17);
			this.lblChan3.Location = new System.Drawing.Point(24, 170);
			this.lblChan3.TabIndex = 4;
			this.lblChan3.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan3.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan3.Enabled = true;
			this.lblChan3.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan3.UseMnemonic = true;
			this.lblChan3.Visible = true;
			this.lblChan3.AutoSize = false;
			this.lblChan3.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan3.Name = "lblChan3";
			this._lblADData_6.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_6.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_6.Size = new System.Drawing.Size(65, 17);
			this._lblADData_6.Location = new System.Drawing.Point(264, 145);
			this._lblADData_6.TabIndex = 15;
			this._lblADData_6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_6.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_6.Enabled = true;
			this._lblADData_6.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_6.UseMnemonic = true;
			this._lblADData_6.Visible = true;
			this._lblADData_6.AutoSize = false;
			this._lblADData_6.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_6.Name = "_lblADData_6";
			this.lblChan6.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan6.Text = "Channel 6:";
			this.lblChan6.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan6.Size = new System.Drawing.Size(65, 17);
			this.lblChan6.Location = new System.Drawing.Point(192, 145);
			this.lblChan6.TabIndex = 7;
			this.lblChan6.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan6.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan6.Enabled = true;
			this.lblChan6.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan6.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan6.UseMnemonic = true;
			this.lblChan6.Visible = true;
			this.lblChan6.AutoSize = false;
			this.lblChan6.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan6.Name = "lblChan6";
			this._lblADData_2.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_2.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_2.Size = new System.Drawing.Size(65, 17);
			this._lblADData_2.Location = new System.Drawing.Point(96, 145);
			this._lblADData_2.TabIndex = 11;
			this._lblADData_2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_2.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_2.Enabled = true;
			this._lblADData_2.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_2.UseMnemonic = true;
			this._lblADData_2.Visible = true;
			this._lblADData_2.AutoSize = false;
			this._lblADData_2.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_2.Name = "_lblADData_2";
			this.lblChan2.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan2.Text = "Channel 2:";
			this.lblChan2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan2.Size = new System.Drawing.Size(65, 17);
			this.lblChan2.Location = new System.Drawing.Point(24, 145);
			this.lblChan2.TabIndex = 3;
			this.lblChan2.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan2.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan2.Enabled = true;
			this.lblChan2.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan2.UseMnemonic = true;
			this.lblChan2.Visible = true;
			this.lblChan2.AutoSize = false;
			this.lblChan2.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan2.Name = "lblChan2";
			this._lblADData_5.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_5.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_5.Size = new System.Drawing.Size(65, 17);
			this._lblADData_5.Location = new System.Drawing.Point(264, 119);
			this._lblADData_5.TabIndex = 14;
			this._lblADData_5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_5.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_5.Enabled = true;
			this._lblADData_5.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_5.UseMnemonic = true;
			this._lblADData_5.Visible = true;
			this._lblADData_5.AutoSize = false;
			this._lblADData_5.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_5.Name = "_lblADData_5";
			this.lblChan5.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan5.Text = "Channel 5:";
			this.lblChan5.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan5.Size = new System.Drawing.Size(65, 17);
			this.lblChan5.Location = new System.Drawing.Point(192, 119);
			this.lblChan5.TabIndex = 6;
			this.lblChan5.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan5.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan5.Enabled = true;
			this.lblChan5.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan5.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan5.UseMnemonic = true;
			this.lblChan5.Visible = true;
			this.lblChan5.AutoSize = false;
			this.lblChan5.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan5.Name = "lblChan5";
			this._lblADData_1.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_1.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_1.Size = new System.Drawing.Size(65, 17);
			this._lblADData_1.Location = new System.Drawing.Point(96, 119);
			this._lblADData_1.TabIndex = 10;
			this._lblADData_1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_1.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_1.Enabled = true;
			this._lblADData_1.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_1.UseMnemonic = true;
			this._lblADData_1.Visible = true;
			this._lblADData_1.AutoSize = false;
			this._lblADData_1.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_1.Name = "_lblADData_1";
			this.lblChan1.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan1.Text = "Channel 1:";
			this.lblChan1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan1.Size = new System.Drawing.Size(65, 17);
			this.lblChan1.Location = new System.Drawing.Point(24, 119);
			this.lblChan1.TabIndex = 2;
			this.lblChan1.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan1.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan1.Enabled = true;
			this.lblChan1.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan1.UseMnemonic = true;
			this.lblChan1.Visible = true;
			this.lblChan1.AutoSize = false;
			this.lblChan1.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan1.Name = "lblChan1";
			this._lblADData_4.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_4.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_4.Size = new System.Drawing.Size(65, 17);
			this._lblADData_4.Location = new System.Drawing.Point(264, 94);
			this._lblADData_4.TabIndex = 13;
			this._lblADData_4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_4.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_4.Enabled = true;
			this._lblADData_4.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_4.UseMnemonic = true;
			this._lblADData_4.Visible = true;
			this._lblADData_4.AutoSize = false;
			this._lblADData_4.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_4.Name = "_lblADData_4";
			this.lblChan4.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan4.Text = "Channel 4:";
			this.lblChan4.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan4.Size = new System.Drawing.Size(65, 17);
			this.lblChan4.Location = new System.Drawing.Point(192, 94);
			this.lblChan4.TabIndex = 5;
			this.lblChan4.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan4.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan4.Enabled = true;
			this.lblChan4.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan4.UseMnemonic = true;
			this.lblChan4.Visible = true;
			this.lblChan4.AutoSize = false;
			this.lblChan4.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan4.Name = "lblChan4";
			this._lblADData_0.BackColor = System.Drawing.SystemColors.Window;
			this._lblADData_0.ForeColor = System.Drawing.Color.Blue;
			this._lblADData_0.Size = new System.Drawing.Size(65, 17);
			this._lblADData_0.Location = new System.Drawing.Point(96, 94);
			this._lblADData_0.TabIndex = 9;
			this._lblADData_0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblADData_0.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this._lblADData_0.Enabled = true;
			this._lblADData_0.Cursor = System.Windows.Forms.Cursors.Default;
			this._lblADData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this._lblADData_0.UseMnemonic = true;
			this._lblADData_0.Visible = true;
			this._lblADData_0.AutoSize = false;
			this._lblADData_0.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this._lblADData_0.Name = "_lblADData_0";
			this.lblChan0.BackColor = System.Drawing.SystemColors.Window;
			this.lblChan0.Text = "Channel 0:";
			this.lblChan0.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChan0.Size = new System.Drawing.Size(65, 17);
			this.lblChan0.Location = new System.Drawing.Point(24, 94);
			this.lblChan0.TabIndex = 1;
			this.lblChan0.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblChan0.TextAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lblChan0.Enabled = true;
			this.lblChan0.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChan0.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChan0.UseMnemonic = true;
			this.lblChan0.Visible = true;
			this.lblChan0.AutoSize = false;
			this.lblChan0.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblChan0.Name = "lblChan0";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.SetTrigger() ";
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Size = new System.Drawing.Size(337, 41);
			this.lblDemoFunction.Location = new System.Drawing.Point(8, 8);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblDemoFunction.Enabled = true;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.UseMnemonic = true;
			this.lblDemoFunction.Visible = true;
			this.lblDemoFunction.AutoSize = false;
			this.lblDemoFunction.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.Controls.Add(txtHighChan);
			this.Controls.Add(cmdStopConvert);
			this.Controls.Add(cmdStart);
			this.Controls.Add(Label1);
			this.Controls.Add(_lblADData_7);
			this.Controls.Add(lblChan7);
			this.Controls.Add(_lblADData_3);
			this.Controls.Add(lblChan3);
			this.Controls.Add(_lblADData_6);
			this.Controls.Add(lblChan6);
			this.Controls.Add(_lblADData_2);
			this.Controls.Add(lblChan2);
			this.Controls.Add(_lblADData_5);
			this.Controls.Add(lblChan5);
			this.Controls.Add(_lblADData_1);
			this.Controls.Add(lblChan1);
			this.Controls.Add(_lblADData_4);
			this.Controls.Add(lblChan4);
			this.Controls.Add(_lblADData_0);
			this.Controls.Add(lblChan0);
			this.Controls.Add(lblDemoFunction);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmDataDisplay());
		}
	    

		private void cmdStart_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStart.Click */
		{
			cmdStart.Enabled = false;

			//  Select the trigger source using Mccdaq.MccBoard.SetTrigger()
			//  Parameters:
			//    TrigType       :the type of triggering based on external trigger source
			//    LowThreshold   :Low threshold when the trigger input is analog
			//    HighThreshold  :High threshold when the trigger input is analog
			float highVal = 1.0F;
			MccDaq.Range Range = MccDaq.Range.Bip10Volts; // analog trigger range
			ushort HighThreshold=0;
			MccDaq.ErrorInfo ULStat = DaqBoard.FromEngUnits( Range, highVal, out HighThreshold);

			float lowVal = 0.1F;
			ushort LowThreshold = 0;
			ULStat = DaqBoard.FromEngUnits( Range, lowVal, out LowThreshold);

			MccDaq.TriggerType TrigType = MccDaq.TriggerType.TrigAbove;
			ULStat = DaqBoard.SetTrigger(TrigType, LowThreshold, HighThreshold);
			
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				//  Collect the values with MccDaq.MccBoard.AInScan()
				//  Parameters:
				//    LowChan    :the first channel of the scan
				//    HighChan   :the last channel of the scan
				//    Count      :the total number of A/D samples to collect
				//    Rate       :sample rate
				//    Range      :the range for the board
				//    MemHandle  :Handle for Windows buffer to store data in
				//    Options    :data collection options
				int LowChan = 0; //  first channel to acquire
				HighChan = int.Parse(txtHighChan.Text); //  last channel to acquire
				if (HighChan > 7) HighChan = 7;
				txtHighChan.Text = HighChan.ToString();

				int Count = NumPoints; //  total number of data points to collect
				int Rate = 390; //  per channel sampling rate ((samples per second) per channel)
				Range = MccDaq.Range.Bip5Volts; // set the range
				MccDaq.ScanOptions Options = MccDaq.ScanOptions.ConvertData  //  return data as 12-bit values
					| MccDaq.ScanOptions.ExtTrigger; 
				ULStat = DaqBoard.AInScan( LowChan, HighChan, Count, ref Rate, Range, MemHandle, Options);

				if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.BadRange) 
					MessageBox.Show( "Change the Range argument to one supported by this board.", "Unsupported Range", 0);
				

				//  Transfer the data from the memory buffer set up by Windows to an array
				ULStat = MccDaq.MccService.WinBufToArray( MemHandle, out ADData[0], FirstPoint, Count);
				

				for (int i=0; i<=HighChan; ++i)
					lblADData[i].Text = ADData[i].ToString("0");

				for (int j=HighChan + 1; j<=7; ++j)
					lblADData[j].Text = "";
			}
			cmdStart.Enabled = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			//  Free up memory for use by other programs
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.WinBufFree(MemHandle); 
			MemHandle = 0;

			Application.Exit();
		}

	}
}