using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace ULLOG01
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		public const int MAX_PATH = 260;
		private string m_Path = "..\\..\\..\\..";
		private const int m_FileNumber = 0;

		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnFirstFile;
		private System.Windows.Forms.Button btnNextFile;
		private System.Windows.Forms.Button btnFileNumber;
		private System.Windows.Forms.Button btnAllFiles;
		private System.Windows.Forms.ListBox lbFileList;
		private System.Windows.Forms.Label lblComment;
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
			MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);
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
			this.btnFirstFile = new System.Windows.Forms.Button();
			this.btnNextFile = new System.Windows.Forms.Button();
			this.btnFileNumber = new System.Windows.Forms.Button();
			this.btnAllFiles = new System.Windows.Forms.Button();
			this.lbFileList = new System.Windows.Forms.ListBox();
			this.btnOK = new System.Windows.Forms.Button();
			this.lblComment = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// btnFirstFile
			// 
			this.btnFirstFile.Location = new System.Drawing.Point(16, 24);
			this.btnFirstFile.Name = "btnFirstFile";
			this.btnFirstFile.TabIndex = 0;
			this.btnFirstFile.Text = "First File";
			this.btnFirstFile.Click += new System.EventHandler(this.OnButtonClick_FirstFile);
			// 
			// btnNextFile
			// 
			this.btnNextFile.Location = new System.Drawing.Point(16, 56);
			this.btnNextFile.Name = "btnNextFile";
			this.btnNextFile.TabIndex = 1;
			this.btnNextFile.Text = "Next File";
			this.btnNextFile.Click += new System.EventHandler(this.OnButtonClick_NextFile);
			// 
			// btnFileNumber
			// 
			this.btnFileNumber.Location = new System.Drawing.Point(16, 88);
			this.btnFileNumber.Name = "btnFileNumber";
			this.btnFileNumber.TabIndex = 2;
			this.btnFileNumber.Text = "File Number";
			this.btnFileNumber.Click += new System.EventHandler(this.OnButtonClick_FileNumber);
			// 
			// btnAllFiles
			// 
			this.btnAllFiles.Location = new System.Drawing.Point(16, 120);
			this.btnAllFiles.Name = "btnAllFiles";
			this.btnAllFiles.TabIndex = 3;
			this.btnAllFiles.Text = "All Files";
			this.btnAllFiles.Click += new System.EventHandler(this.OnButtonClick_AllFiles);
			// 
			// lbFileList
			// 
			this.lbFileList.Location = new System.Drawing.Point(112, 24);
			this.lbFileList.Name = "lbFileList";
			this.lbFileList.Size = new System.Drawing.Size(232, 121);
			this.lbFileList.TabIndex = 4;
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point(368, 24);
			this.btnOK.Name = "btnOK";
			this.btnOK.TabIndex = 5;
			this.btnOK.Text = "OK";
			this.btnOK.Click += new System.EventHandler(this.OnButtonClick_OK);
			// 
			// lblComment
			// 
			this.lblComment.Location = new System.Drawing.Point(24, 168);
			this.lblComment.Name = "lblComment";
			this.lblComment.Size = new System.Drawing.Size(424, 23);
			this.lblComment.TabIndex = 6;
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(456, 205);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.lblComment,
																		  this.btnOK,
																		  this.lbFileList,
																		  this.btnAllFiles,
																		  this.btnFileNumber,
																		  this.btnNextFile,
																		  this.btnFirstFile});
			this.Name = "Form1";
			this.Text = "Form1";
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

		private void OnButtonClick_OK(object sender, System.EventArgs e)
		{
			Close();
		}

		private void OnButtonClick_FirstFile(object sender, System.EventArgs e)
		{
			string				filename = new string('\0', MAX_PATH);
			MccDaq.ErrorInfo	errorInfo;

			lblComment.Text = "Get first file from directory " + m_Path;

			//  Get the first file in the directory
			//   Parameters:
			//     MccDaq.GetFileOptions.GetFirst :first file
			//     m_Path						  :path to search
			//	   filename						  :receives name of file
			errorInfo = MccDaq.DataLogger.GetFileName((int)MccDaq.GetFileOptions.GetFirst, ref m_Path, ref filename);
			string newpath = filename.TrimEnd('\0');
			string absolutePath = Path.GetFullPath(newpath);

			if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
				MessageBox.Show(errorInfo.Message);
			else
			{
				lbFileList.Items.Clear();
				lbFileList.Items.Add(absolutePath);
			}
		}

		private void OnButtonClick_NextFile(object sender, System.EventArgs e)
		{
			string				filename = new string('\0', MAX_PATH);
			MccDaq.ErrorInfo	errorInfo;

			lblComment.Text = "Get next file from directory " + m_Path;

			//  Get the next file in the directory
			//   Parameters:
			//     MccDaq.GetFileOptions.GetNext :next file
			//     m_Path						  :path to search
			//	   filename						  :receives name of file
			errorInfo = MccDaq.DataLogger.GetFileName((int)MccDaq.GetFileOptions.GetNext, ref m_Path, ref filename);
			string newpath = filename.TrimEnd('\0');
			string absolutePath = Path.GetFullPath(newpath);

			if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
				MessageBox.Show(errorInfo.Message);
			else
				lbFileList.Items.Add(absolutePath);
		}

		private void OnButtonClick_FileNumber(object sender, System.EventArgs e)
		{
			string				filename = new string('\0', MAX_PATH);
			MccDaq.ErrorInfo	errorInfo;

			lblComment.Text = "Get file number " + m_FileNumber + " from directory " + m_Path;

			//  Get the Nth file in the directory
			//   Parameters:
			//     m_FileNumber					  :Nth file in the directory 
			//     m_Path						  :path to search
			//	   filename						  :receives name of file
			errorInfo = MccDaq.DataLogger.GetFileName(m_FileNumber,  ref m_Path, ref filename);
			string newpath = filename.TrimEnd('\0');
			string absolutePath = Path.GetFullPath(newpath);

			if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
				MessageBox.Show(errorInfo.Message);
			else
				lbFileList.Items.Add(absolutePath);
		}

		private void OnButtonClick_AllFiles(object sender, System.EventArgs e)
		{
			string				filename = new string('\0', MAX_PATH);
			MccDaq.ErrorInfo	errorInfo;

			lblComment.Text = "Get all files from directory " + Path.GetFullPath(m_Path);

			//  Get the first file in the directory
			//   Parameters:
			//     MccDaq.GetFileOptions.GetFirst :first file
			//     m_Path						  :path to search
			//	   filename						  :receives name of file
			errorInfo = MccDaq.DataLogger.GetFileName((int)MccDaq.GetFileOptions.GetFirst, ref m_Path, ref filename);
			string newpath = filename.TrimEnd('\0');
			string absolutePath = Path.GetFullPath(newpath);

			if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				MessageBox.Show(errorInfo.Message);
				return;
			}
			else
			{
				lbFileList.Items.Clear();
				lbFileList.Items.Add(absolutePath);
			}

			while (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoMoreFiles)
			{
				//  Get the next file in the directory
				//   Parameters:
				//     MccDaq.GetFileOptions.GetNext :next file
				//     m_Path						  :path to search
				//	   filename						  :receives name of file
				errorInfo = MccDaq.DataLogger.GetFileName((int)MccDaq.GetFileOptions.GetNext, ref m_Path, ref filename);
				newpath = filename.TrimEnd('\0');
				absolutePath = Path.GetFullPath(newpath);

				if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoMoreFiles)
					{
						MessageBox.Show(errorInfo.Message);
						return;
					}
				}
				else
					lbFileList.Items.Add(absolutePath);
			}
		}
	}
}
