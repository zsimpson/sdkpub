// ==============================================================================
//
// File:                         ULGT04.CS
//
// Library Call Demonstrated:     MccDaq.MccService.GetBoardName()
//
//
// Purpose:                      Prints a list of all boards installed in
//                               the system.  Prints a list of all supported
//                               boards.
//
// Other Library Calls:          MccDaq.MccService.ErrHandling()
//                               MccDaq.MccBoard.BoardName property
//                               MccDaq.GlobalConfig.NumBoards property
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

namespace ULGT04
{
	public class frmListBoards : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;
		public ToolTip ToolTip1;
		public Button cmdQuit;
		public Button cmdListSupported;
		public Button cmdListInstalled;
		public TextBox txtListBoards;
		private string LF = Environment.NewLine;

		private int MaxNumBoards = MccDaq.GlobalConfig.NumBoards;
	 
		public frmListBoards()
		{
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			//  Initiate error handling
			//   activating error handling will trap errors like
			//   bad channel numbers and non-configured conditions.
			//   Parameters:
			//     MccDaq.ErrorReporting.PrintAll  :all warnings and errors encountered will be printed
			//     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
			
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
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
		this.cmdQuit = new System.Windows.Forms.Button();
		this.cmdListSupported = new System.Windows.Forms.Button();
		this.cmdListInstalled = new System.Windows.Forms.Button();
		this.txtListBoards = new System.Windows.Forms.TextBox();
		this.SuspendLayout();
		// 
		// cmdQuit
		// 
		this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
		this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdQuit.Location = new System.Drawing.Point(232, 280);
		this.cmdQuit.Name = "cmdQuit";
		this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdQuit.Size = new System.Drawing.Size(65, 25);
		this.cmdQuit.TabIndex = 2;
		this.cmdQuit.Text = "&Quit";
		this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
		// 
		// cmdListSupported
		// 
		this.cmdListSupported.BackColor = System.Drawing.SystemColors.Control;
		this.cmdListSupported.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdListSupported.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdListSupported.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdListSupported.Location = new System.Drawing.Point(116, 280);
		this.cmdListSupported.Name = "cmdListSupported";
		this.cmdListSupported.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdListSupported.Size = new System.Drawing.Size(109, 25);
		this.cmdListSupported.TabIndex = 1;
		this.cmdListSupported.Text = "Supported Boards";
		this.cmdListSupported.Click += new System.EventHandler(this.cmdListSupported_Click);
		// 
		// cmdListInstalled
		// 
		this.cmdListInstalled.BackColor = System.Drawing.SystemColors.Control;
		this.cmdListInstalled.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdListInstalled.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdListInstalled.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdListInstalled.Location = new System.Drawing.Point(8, 280);
		this.cmdListInstalled.Name = "cmdListInstalled";
		this.cmdListInstalled.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdListInstalled.Size = new System.Drawing.Size(101, 25);
		this.cmdListInstalled.TabIndex = 0;
		this.cmdListInstalled.Text = "Installed Boards";
		this.cmdListInstalled.Click += new System.EventHandler(this.cmdListInstalled_Click);
		// 
		// txtListBoards
		// 
		this.txtListBoards.AcceptsReturn = true;
		this.txtListBoards.AutoSize = false;
		this.txtListBoards.BackColor = System.Drawing.SystemColors.Window;
		this.txtListBoards.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.txtListBoards.Cursor = System.Windows.Forms.Cursors.IBeam;
		this.txtListBoards.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.txtListBoards.ForeColor = System.Drawing.SystemColors.WindowText;
		this.txtListBoards.Location = new System.Drawing.Point(8, 8);
		this.txtListBoards.MaxLength = 0;
		this.txtListBoards.Multiline = true;
		this.txtListBoards.Name = "txtListBoards";
		this.txtListBoards.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.txtListBoards.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
		this.txtListBoards.Size = new System.Drawing.Size(289, 257);
		this.txtListBoards.TabIndex = 3;
		this.txtListBoards.Text = "";
		// 
		// frmListBoards
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(307, 316);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdQuit,
																		this.cmdListSupported,
																		this.cmdListInstalled,
																		this.txtListBoards});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmListBoards";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library List Boards";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmListBoards());
		}
	    	

		private void cmdListInstalled_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdListInstalled.Click */
		{
			// Get board type of each board currently installed
			txtListBoards.Text = "Currently installed boards:" + LF + LF;
			
			int typeVal;
			string BoardName;
			MccDaq.ErrorInfo ULStat;
			for (int BoardNum=0; BoardNum < MaxNumBoards; ++BoardNum)
			{
				MccDaq.MccBoard board = new MccDaq.MccBoard(BoardNum);
				ULStat = board.BoardConfig.GetBoardType(out typeVal);
				if (typeVal != 0)
				{
					//  Get the BoardName property from the MccBoard object
					BoardName = board.BoardName;
					BoardName = BoardName.TrimEnd(); // Drop the space characters
					BoardName = BoardName.Substring(0, BoardName.Length - 1);

					txtListBoards.Text += "Board #" + BoardNum.ToString("0") + " = " + BoardName + LF;
				}
			}

		}


		private void cmdListSupported_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdListSupported.Click */
		{
			txtListBoards.Text = "";
	
			// Get the first board type in list of supported boards
			// The first string in the boardlist is "! Supported"
			//BoardName = new string(' ', MccDaq.MccService.BoardNameLen);
			string BoardName = new string(' ', MccDaq.MccService.BoardNameLen);
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.GetBoardName(MccDaq.MccService.GetFirst, ref BoardName);
			BoardName = BoardName.TrimEnd(); // Drop the space characters
			BoardName = BoardName.Substring(0, BoardName.Length - 1);
			string BoardList = "The first string in the board name list is:" + LF + " '" + BoardName + "'" + LF + LF;

			// Get each consecutive board type in list
			do 
			{
				BoardName = new string(' ',MccDaq.MccService.BoardNameLen);

				ULStat = MccDaq.MccService.GetBoardName(MccDaq.MccService.GetNext, ref BoardName);
				BoardName = BoardName.TrimEnd(); // Drop the space characters
			//	BoardName = BoardName.Substring(0, BoardName.Length - 1);

				BoardList = BoardList + BoardName + LF;
			} while (BoardName.Length > 3);

			txtListBoards.Text = BoardList;

		}


		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdQuit.Click */
		{
			Application.Exit();
		}

	}
}