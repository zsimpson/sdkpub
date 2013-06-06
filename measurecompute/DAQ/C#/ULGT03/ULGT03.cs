// ==============================================================================
//
// File:                         ULGT03.CS
//
// Library Call Demonstrated:    MccDaq.MccBoard.BoardConfig property
//                               MccDaq.MccBoard.DioConfig  property
//                               MccDaq.MccBoard.ExpansionConfig property
//
// Purpose:                      Prints a list of all boards installed in
//                               the system and their base addresses.  Also
//                               prints the addresses of each digital and
//                               counter device on each board and any EXP
//                               boards that are connected to A/D channels.
//
// Other Library Calls:          MccDaq.MccBoard.GetBoardName()
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

namespace ULGT03
{
	public class frmInfoDisplay : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;
		public ToolTip ToolTip1;
		public Button cmdQuit;
		public Button cmdPrintInfo;
		public TextBox txtBoardInfo;

		private int CurrentBoard;
		private int MaxNumBoards, NumBoards; 
		private int[] NumADChans;
		private string BoardName;
		private string LF, Info;
	 

		public frmInfoDisplay()
		{    
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			LF = Environment.NewLine;

	        
			// Get the max number of boards installed in system
			MaxNumBoards = MccDaq.GlobalConfig.NumBoards;
			CurrentBoard = 0;
			txtBoardInfo.Text = LF + LF + LF + "        Click on 'Print Info' to display board information.";

			NumADChans = new int[MaxNumBoards];
			NumBoards = 0;
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
		this.cmdPrintInfo = new System.Windows.Forms.Button();
		this.txtBoardInfo = new System.Windows.Forms.TextBox();
		this.SuspendLayout();
		// 
		// cmdQuit
		// 
		this.cmdQuit.BackColor = System.Drawing.SystemColors.Control;
		this.cmdQuit.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdQuit.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdQuit.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdQuit.Location = new System.Drawing.Point(360, 304);
		this.cmdQuit.Name = "cmdQuit";
		this.cmdQuit.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdQuit.Size = new System.Drawing.Size(57, 25);
		this.cmdQuit.TabIndex = 1;
		this.cmdQuit.Text = "Quit";
		this.cmdQuit.Click += new System.EventHandler(this.cmdQuit_Click);
		// 
		// cmdPrintInfo
		// 
		this.cmdPrintInfo.BackColor = System.Drawing.SystemColors.Control;
		this.cmdPrintInfo.Cursor = System.Windows.Forms.Cursors.Default;
		this.cmdPrintInfo.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.cmdPrintInfo.ForeColor = System.Drawing.SystemColors.ControlText;
		this.cmdPrintInfo.Location = new System.Drawing.Point(160, 304);
		this.cmdPrintInfo.Name = "cmdPrintInfo";
		this.cmdPrintInfo.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.cmdPrintInfo.Size = new System.Drawing.Size(76, 26);
		this.cmdPrintInfo.TabIndex = 0;
		this.cmdPrintInfo.Text = "Print Info";
		this.cmdPrintInfo.Click += new System.EventHandler(this.cmdPrintInfo_Click);
		// 
		// txtBoardInfo
		// 
		this.txtBoardInfo.AcceptsReturn = true;
		this.txtBoardInfo.AutoSize = false;
		this.txtBoardInfo.BackColor = System.Drawing.SystemColors.Window;
		this.txtBoardInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		this.txtBoardInfo.Cursor = System.Windows.Forms.Cursors.IBeam;
		this.txtBoardInfo.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.txtBoardInfo.ForeColor = System.Drawing.SystemColors.WindowText;
		this.txtBoardInfo.Location = new System.Drawing.Point(16, 8);
		this.txtBoardInfo.MaxLength = 0;
		this.txtBoardInfo.Multiline = true;
		this.txtBoardInfo.Name = "txtBoardInfo";
		this.txtBoardInfo.RightToLeft = System.Windows.Forms.RightToLeft.No;
		this.txtBoardInfo.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
		this.txtBoardInfo.Size = new System.Drawing.Size(401, 289);
		this.txtBoardInfo.TabIndex = 2;
		this.txtBoardInfo.Text = "";
		this.txtBoardInfo.WordWrap = false;
		// 
		// frmInfoDisplay
		// 
		this.AcceptButton = this.cmdPrintInfo;
		this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
		this.BackColor = System.Drawing.SystemColors.Window;
		this.ClientSize = new System.Drawing.Size(432, 337);
		this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		this.cmdQuit,
																		this.cmdPrintInfo,
																		this.txtBoardInfo});
		this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
		this.ForeColor = System.Drawing.SystemColors.WindowText;
		this.Location = new System.Drawing.Point(7, 103);
		this.Name = "frmInfoDisplay";
		this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
		this.Text = "Universal Library Configuration Info";
		this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmInfoDisplay());
		}
	   

		private void cmdPrintInfo_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdPrintInfo.Click */
		{
			Info = "";
			while ((Info.Length < 1) && (CurrentBoard < MaxNumBoards))
			{
				MccDaq.MccBoard pCurrentBoard = new MccDaq.MccBoard(CurrentBoard);
				PrintGenInfo(pCurrentBoard);
				PrintADInfo(pCurrentBoard);
				PrintDAInfo(pCurrentBoard);
				PrintDigInfo(pCurrentBoard);
				PrintCtrInfo(pCurrentBoard);
				PrintExpInfo(pCurrentBoard);

				CurrentBoard = CurrentBoard + 1;
			}

			if (CurrentBoard > MaxNumBoards - 1)
			{
				if (NumBoards == 0)
				{
					Info = LF + LF + "        There are no boards installed."+LF+LF;
					Info +=			 "        You must run InstaCal to install the desired"+LF;
					Info +=			 "        boards before running this program."+LF;
				}
				else
				{
					Info =LF + LF + "        There are no additional boards installed."+LF;
				}
				cmdPrintInfo.Text = "Print Info";
				CurrentBoard = 0;
				NumBoards = 0;
			}
			else if (Info.Length > 0)
			{
				cmdPrintInfo.Text = "Print Next";
				NumBoards = NumBoards + 1;
			}
			txtBoardInfo.Text = Info;

		}


		private void cmdQuit_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdQuit.Click */
		{
			Application.Exit();
		}


		private void PrintADInfo(MccDaq.MccBoard pBoard)
		{
			int numADChans=0;
			MccDaq.ErrorInfo ULStat = pBoard.BoardConfig.GetNumAdChans(out numADChans);
	        
			NumADChans[pBoard.BoardNum] = numADChans;
			if (numADChans != 0) 
				Info += "     Number of A/D channels: " + numADChans.ToString("0") + LF ;

		}


		private void PrintCtrInfo(MccDaq.MccBoard pBoard)
		{
			// Get the number of counter devices for this board
	        int numCounters = 0;
			MccDaq.ErrorInfo ULStat = pBoard.BoardConfig.GetCiNumDevs(out numCounters);

			if (numCounters > 0) 
			Info += "      Counters : " + numCounters.ToString("0") + LF;

			if (Info.Length != 0) 
				Info += LF;
		}


		private void PrintDAInfo(MccDaq.MccBoard pBoard)
		{
			int numDAChans = 0;
			MccDaq.ErrorInfo ULStat = pBoard.BoardConfig.GetNumDaChans(out numDAChans);

			if (numDAChans > 0) 
				Info += "     Number of D/A channels: " + numDAChans.ToString("0") + LF;

		}


		private void PrintDigInfo(MccDaq.MccBoard pBoard)
		{
			// get the number of digital devices for this board
			int numDIPorts = 0;
			MccDaq.ErrorInfo ULStat = pBoard.BoardConfig.GetDiNumDevs(out numDIPorts);

			int numBits = 0;
			for (int portNum=0; portNum<numDIPorts; ++portNum)
			{
				// For each digital device, get the base address and number of bits
				numBits = 0;
				ULStat = pBoard.DioConfig.GetNumBits(portNum, out numBits);

				Info += "     Digital Device #" + portNum.ToString("0") + " : " + numBits.ToString("0") + " bits" + LF;
			}

		}


		private void PrintExpInfo(MccDaq.MccBoard pBoard)
		{
			//  Get the number of Exps attached to pBoard
	        int numEXPs = 0;
			MccDaq.ErrorInfo ULStat = pBoard.BoardConfig.GetNumExps(out numEXPs);

			int BoardType = 0;
			int ADChan1 = 0;
			int ADChan2 = 0;
			for (int expNum=0; expNum<numEXPs; ++expNum)
			{
				pBoard.ExpansionConfig.GetBoardType(expNum, out BoardType);
				pBoard.ExpansionConfig.GetMuxAdChan1(expNum, out ADChan1);

				if (BoardType == 770)
				{
					// it's a CIO-EXP32
					pBoard.ExpansionConfig.GetMuxAdChan2(expNum, out ADChan2);
					Info += "     A/D channels " + ADChan1.ToString("0") + " and " + ADChan2.ToString("0")+ " connected to EXP(devID=" +BoardType.ToString("0") + ")." + LF;
				}
				else
					Info += "     A/D channel " + ADChan1.ToString("0") + " connected to EXP(devID=" + BoardType.ToString("0") + ")." + LF;
				
			}

			if (Info.Length != 0) 
				Info += LF;

		}


		private void PrintGenInfo(MccDaq.MccBoard pBoard)
		{
			// Get board type of each board
			int BoardType = 0;
			MccDaq.ErrorInfo ULStat = pBoard.BoardConfig.GetBoardType(out BoardType);

			if (BoardType > 0) // If a board is installed
				{
				// Get the board's name
				BoardName = pBoard.BoardName;

				BoardName = BoardName.TrimEnd();		// Drop the space characters
				int StringSize = BoardName.Length - 1;  // Drop the null character at end of string
				
				BoardName = BoardName.Substring(0, StringSize);
				Info += "Board #" + pBoard.BoardNum.ToString("0") + " = " + BoardName +" at ";

				// Get the board's base address
				int baseAdr = 0;
				ULStat = pBoard.BoardConfig.GetBaseAdr(0, out baseAdr);

				Info += "Base Address = " + baseAdr.ToString("X") + " hex." + LF + LF;
			}

		}

	}
}