using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace ULLOG04
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private MccDaq.ErrorInfo m_ErrorInfo;
		private string m_SrcFilename;
		private MccDaq.FieldDelimiter m_Delimiter;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.RadioButton rbSemiColon;
		private System.Windows.Forms.RadioButton rbComma;
		private System.Windows.Forms.RadioButton rbSpace;
		private System.Windows.Forms.RadioButton rbTab;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnBrowse;
		private System.Windows.Forms.TextBox tbFilename;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Form1()
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
			m_ErrorInfo = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);

			rbComma.Checked = true;
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
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.rbTab = new System.Windows.Forms.RadioButton();
			this.rbSpace = new System.Windows.Forms.RadioButton();
			this.rbSemiColon = new System.Windows.Forms.RadioButton();
			this.rbComma = new System.Windows.Forms.RadioButton();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.tbFilename = new System.Windows.Forms.TextBox();
			this.btnBrowse = new System.Windows.Forms.Button();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.rbTab);
			this.groupBox2.Controls.Add(this.rbSpace);
			this.groupBox2.Controls.Add(this.rbSemiColon);
			this.groupBox2.Controls.Add(this.rbComma);
			this.groupBox2.Location = new System.Drawing.Point(16, 16);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(192, 80);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Delimiter";
			// 
			// rbTab
			// 
			this.rbTab.Location = new System.Drawing.Point(104, 48);
			this.rbTab.Name = "rbTab";
			this.rbTab.Size = new System.Drawing.Size(80, 24);
			this.rbTab.TabIndex = 3;
			this.rbTab.Text = "Tab";
			this.rbTab.Click += new System.EventHandler(this.OnButtonClick_Delimiter);
			// 
			// rbSpace
			// 
			this.rbSpace.Location = new System.Drawing.Point(104, 24);
			this.rbSpace.Name = "rbSpace";
			this.rbSpace.Size = new System.Drawing.Size(80, 24);
			this.rbSpace.TabIndex = 2;
			this.rbSpace.Text = "Space";
			this.rbSpace.Click += new System.EventHandler(this.OnButtonClick_Delimiter);
			// 
			// rbSemiColon
			// 
			this.rbSemiColon.Location = new System.Drawing.Point(16, 48);
			this.rbSemiColon.Name = "rbSemiColon";
			this.rbSemiColon.Size = new System.Drawing.Size(80, 24);
			this.rbSemiColon.TabIndex = 1;
			this.rbSemiColon.Text = "Semicolon";
			this.rbSemiColon.Click += new System.EventHandler(this.OnButtonClick_Delimiter);
			// 
			// rbComma
			// 
			this.rbComma.Location = new System.Drawing.Point(16, 24);
			this.rbComma.Name = "rbComma";
			this.rbComma.Size = new System.Drawing.Size(80, 24);
			this.rbComma.TabIndex = 0;
			this.rbComma.Text = "Comma";
			this.rbComma.Click += new System.EventHandler(this.OnButtonClick_Delimiter);
			// 
			// btnOK
			// 
			this.btnOK.Enabled = false;
			this.btnOK.Location = new System.Drawing.Point(87, 160);
			this.btnOK.Name = "btnOK";
			this.btnOK.TabIndex = 2;
			this.btnOK.Text = "OK";
			this.btnOK.Click += new System.EventHandler(this.OnButtonClick_OK);
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(183, 160);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.TabIndex = 3;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.Click += new System.EventHandler(this.OnButtonClick_Cancel);
			// 
			// tbFilename
			// 
			this.tbFilename.Location = new System.Drawing.Point(16, 120);
			this.tbFilename.Name = "tbFilename";
			this.tbFilename.Size = new System.Drawing.Size(192, 20);
			this.tbFilename.TabIndex = 4;
			this.tbFilename.Text = "";
			// 
			// btnBrowse
			// 
			this.btnBrowse.Location = new System.Drawing.Point(256, 120);
			this.btnBrowse.Name = "btnBrowse";
			this.btnBrowse.TabIndex = 5;
			this.btnBrowse.Text = "Browse";
			this.btnBrowse.Click += new System.EventHandler(this.OnButtonClick_Browse);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(344, 197);
			this.Controls.Add(this.btnBrowse);
			this.Controls.Add(this.tbFilename);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.Controls.Add(this.groupBox2);
			this.Name = "Form1";
			this.Text = "Form1";
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void OnButtonClick_Browse(object sender, System.EventArgs e)
		{
			OpenFileDialog fileDlg = new OpenFileDialog();

			fileDlg.InitialDirectory = "c:\\" ;
			fileDlg.Filter = "binary files (*.bin)|*.bin|All files (*.*)|*.*" ;
			fileDlg.FilterIndex = 1 ;
			fileDlg.RestoreDirectory = true ;

			if(fileDlg.ShowDialog() == DialogResult.OK)
			{
				m_SrcFilename = fileDlg.FileName;
			}

			tbFilename.Text = m_SrcFilename;
			btnOK.Enabled = true;
		}

		private void OnButtonClick_Delimiter(object sender, System.EventArgs e)
		{
			if (rbComma.Checked == true)
				m_Delimiter = MccDaq.FieldDelimiter.Comma;
			else if (rbSemiColon.Checked == true)
				m_Delimiter = MccDaq.FieldDelimiter.Semicolon;
			else if (rbSpace.Checked == true)
				m_Delimiter = MccDaq.FieldDelimiter.Space;
			else if (rbTab.Checked == true)
				m_Delimiter = MccDaq.FieldDelimiter.Tab;
		}


		private void OnButtonClick_Cancel(object sender, System.EventArgs e)
		{
			Close();
		}

		private void OnButtonClick_OK(object sender, System.EventArgs e)
		{
			// create an instance of the data logger
			MccDaq.DataLogger logger = new MccDaq.DataLogger(m_SrcFilename);

			//  Get the sample info for the first file in the directory
			//   Parameters:
			//     sampleInterval					 :receives the sample interval (time between samples)
			//     sampleCount						 :receives the sample count
			//	   startDate						 :receives the start date
			//	   startTime						 :receives the start time
			int	sampleInterval = 0;
			int	sampleCount = 0;
			int	startDate = 0;
			int startTime = 0;
			m_ErrorInfo = logger.GetSampleInfo(ref sampleInterval, ref sampleCount, ref startDate, ref startTime);

			// get the destination path from the source file name
			int index = m_SrcFilename.LastIndexOf(".");
			string m_DestFilename = m_SrcFilename.Substring(0, index+1) + "csv";

			//  convert the file
			//   Parameters:
			//     m_DestFilename					 :destination file
			//     startSample						 :first sample to convert
			//     sampleCount						 :number of samples to convert
			//	   m_Delimiter						 :field seperator
			int startSample = 0;
			if (m_ErrorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				m_ErrorInfo = logger.ConvertFile(m_DestFilename, startSample, sampleCount, m_Delimiter);
			}

			
			if (m_ErrorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				MessageBox.Show(m_ErrorInfo.Message);
				return;
			}
		}
	}
}
