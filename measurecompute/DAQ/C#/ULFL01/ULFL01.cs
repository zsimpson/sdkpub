// ==============================================================================
//
//  File:                         ULFL01.CS
//
//  Library Call Demonstrated:    LED Functions
//                                Mccdaq.MccBoard.FlashLED()
//
//  Purpose:                      Operate the LED.
//
//  Demonstration:                Flashes onboard LED for visual identification
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have an external LED,
//                                such as the miniLAB 1008 and PMD-1208LS.
//
// ==============================================================================
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace ULFL01
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmLEDTest : Form
	{
		private Button btnFlash;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private Container components = null;
		private MccDaq.MccBoard DaqBoard;

		public frmLEDTest()
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
			DaqBoard = new MccDaq.MccBoard(0);
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

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.btnFlash = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btnFlash
			// 
			this.btnFlash.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.btnFlash.Location = new System.Drawing.Point(128, 64);
			this.btnFlash.Name = "btnFlash";
			this.btnFlash.Size = new System.Drawing.Size(96, 48);
			this.btnFlash.TabIndex = 0;
			this.btnFlash.Text = "Flash LED";
			this.btnFlash.Click += new System.EventHandler(this.btnFlash_Click);
			// 
			// frmLEDTest
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(344, 205);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnFlash});
			this.Name = "frmLEDTest";
			this.Text = "Universal Library LED Test";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmLEDTest());
		}

		private void btnFlash_Click(object sender, System.EventArgs e)
		{
			//Flash the LED
			MccDaq.ErrorInfo ULStat = DaqBoard.FlashLED();
		}
	}
}
