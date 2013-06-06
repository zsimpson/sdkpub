using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace ULLOG02
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		public const int MAX_PATH = 260;
		private string m_Path = "..\\..\\..\\..";

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label13;
		private System.Windows.Forms.Label label15;
		private System.Windows.Forms.Label label17;
		private System.Windows.Forms.Label label19;
		private System.Windows.Forms.Label label21;
		private System.Windows.Forms.Label label23;
		private System.Windows.Forms.Label label25;
		private System.Windows.Forms.Label label26;
		private System.Windows.Forms.Label label27;
		private System.Windows.Forms.Label label29;
		private System.Windows.Forms.Label label28;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Label lblFilename;
		private System.Windows.Forms.Label lblFileVersion;
		private System.Windows.Forms.Label lblFileSize;
		private System.Windows.Forms.Label lblSampleInterval;
		private System.Windows.Forms.Label lblSampleCount;
		private System.Windows.Forms.Label lblStartDate;
		private System.Windows.Forms.Label lblStartTime;
		private System.Windows.Forms.Label lblChannelMask;
		private System.Windows.Forms.Label lblUnitMask;
		private System.Windows.Forms.Label lblAIChannelCount;
		private System.Windows.Forms.Label lblCJCChannelCount;
		private System.Windows.Forms.Label lblDIOChannelCount;
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
			MccDaq.ErrorInfo errorInfo = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);


			//  Get the first file in the directory
			//   Parameters:
			//     MccDaq.GetFileOptions.GetFirst :first file
			//     m_Path						  :path to search
			//	   filename						  :receives name of file
			string	filename = new string('\0', MAX_PATH);
			errorInfo = MccDaq.DataLogger.GetFileName((int)MccDaq.GetFileOptions.GetFirst, ref m_Path, ref filename);
			string newpath = filename.TrimEnd('\0');
			string absolutePath = Path.GetFullPath(newpath);
			
			// create an instance of the data logger
			MccDaq.DataLogger logger = new MccDaq.DataLogger(filename);


			//  Get the file info for the first file in the directory
			//   Parameters:
			//     filename						  :file to retrieve information from
			//     version						  :receives the version of the file
			//	   size							  :receives the size of file
			int	version = 0;
			int	size = 0;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetFileInfo(ref version, ref size);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					lblFilename.Text = absolutePath;
					lblFileVersion.Text = version.ToString();
					lblFileSize.Text = size.ToString();
				}
			}

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
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetSampleInfo(ref sampleInterval, ref sampleCount, ref startDate, ref startTime);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					lblSampleInterval.Text = sampleInterval.ToString();
					lblSampleCount.Text = sampleCount.ToString();

					int day = startDate & 0xff;
					int month = (startDate>>8) & 0xff;
					int year = (startDate>>16) & 0xffff;
					string dateStr = month.ToString() + "/" + day.ToString() + "/" + year.ToString();
					lblStartDate.Text = dateStr;

					string postfix;
					switch ((startTime >> 24) & 0xff)
					{
						case 0:
							postfix = " AM";
							break;
						case 1:
							postfix = " PM";
							break;
						case -1:
							postfix = "";
							break;
						default:
							postfix = "";
							break;
					}
					int hours = (startTime>>16) & 0xff;
					int minutes = (startTime>>8) & 0xff;
					int seconds = (startTime) & 0xff;
					string timeStr = hours.ToString() + ":" + minutes.ToString() + ":" + seconds.ToString() + ":" + postfix;
					lblStartTime.Text = timeStr;
				}
			}


			//  Get the ANALOG channel count for the first file in the directory
			//   Parameters:
			//     channelMask						:receives the channel mask to specify which channels were logged
			//     unitMask							:receives the unit mask to specify temp or raw data
			//	   aiChannelCount					:receives the number of AI chennels logged
			int	aiChannelCount = 0;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetAIChannelCount(ref aiChannelCount);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					lblAIChannelCount.Text = aiChannelCount.ToString();
				}
			}


			//  Get the ANALOG info for the first file in the directory
			//   Parameters:
			//     channelMask						:receives the channel mask to specify which channels were logged
			//     unitMask							:receives the unit mask to specify temp or raw data
			int []	channelNumbers;
			int []	units;

			channelNumbers = new int[aiChannelCount];
			units = new int[aiChannelCount];
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetAIInfo(ref channelNumbers, ref units);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					lblChannelMask.Text = "";
					lblUnitMask.Text = "";
					for (int i=0; i<aiChannelCount; i++)
					{
						lblChannelMask.Text += channelNumbers[i].ToString();

						if (units[i] == Convert.ToInt32(MccDaq.LoggerUnits.Raw))
							lblUnitMask.Text += "Raw";
						else
							lblUnitMask.Text += "Temperature";

						if (i < aiChannelCount - 1)
						{
							lblChannelMask.Text = lblChannelMask.Text + ", ";
							lblUnitMask.Text = lblUnitMask.Text + ", ";
						}
 					}
				}
			}


			//  Get the CJC info for the first file in the directory
			//   Parameters:
			//	   cjcChannelCount					:receives the number of CJC chennels logged
			int	cjcChannelCount = 0;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetCJCInfo( ref cjcChannelCount);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					lblCJCChannelCount.Text = cjcChannelCount.ToString();
				}
			}


			//  Get the DIO info for the first file in the directory
			//   Parameters:
			//	   dioChannelCount					:receives the number of DIO chennels logged
			int	dioChannelCount = 0;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetDIOInfo(ref dioChannelCount);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					lblDIOChannelCount.Text = dioChannelCount.ToString();
				}
			}

			if (errorInfo.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				MessageBox.Show(errorInfo.Message);
				return;
			}
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
			this.label1 = new System.Windows.Forms.Label();
			this.lblFilename = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.lblFileVersion = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.lblFileSize = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.lblSampleInterval = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.lblSampleCount = new System.Windows.Forms.Label();
			this.label11 = new System.Windows.Forms.Label();
			this.lblStartDate = new System.Windows.Forms.Label();
			this.label13 = new System.Windows.Forms.Label();
			this.lblStartTime = new System.Windows.Forms.Label();
			this.label15 = new System.Windows.Forms.Label();
			this.lblChannelMask = new System.Windows.Forms.Label();
			this.label17 = new System.Windows.Forms.Label();
			this.lblUnitMask = new System.Windows.Forms.Label();
			this.label19 = new System.Windows.Forms.Label();
			this.lblAIChannelCount = new System.Windows.Forms.Label();
			this.label21 = new System.Windows.Forms.Label();
			this.lblCJCChannelCount = new System.Windows.Forms.Label();
			this.label23 = new System.Windows.Forms.Label();
			this.lblDIOChannelCount = new System.Windows.Forms.Label();
			this.btnOK = new System.Windows.Forms.Button();
			this.label25 = new System.Windows.Forms.Label();
			this.label26 = new System.Windows.Forms.Label();
			this.label27 = new System.Windows.Forms.Label();
			this.label29 = new System.Windows.Forms.Label();
			this.label28 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(40, 96);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(104, 23);
			this.label1.TabIndex = 0;
			this.label1.Text = "Filename:";
			// 
			// lblFilename
			// 
			this.lblFilename.Location = new System.Drawing.Point(184, 96);
			this.lblFilename.Name = "lblFilename";
			this.lblFilename.Size = new System.Drawing.Size(552, 24);
			this.lblFilename.TabIndex = 1;
			this.lblFilename.Text = "label2";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(40, 48);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(104, 23);
			this.label3.TabIndex = 2;
			this.label3.Text = "File version:";
			// 
			// lblFileVersion
			// 
			this.lblFileVersion.Location = new System.Drawing.Point(184, 48);
			this.lblFileVersion.Name = "lblFileVersion";
			this.lblFileVersion.Size = new System.Drawing.Size(160, 23);
			this.lblFileVersion.TabIndex = 3;
			this.lblFileVersion.Text = "label4";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(40, 72);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(104, 23);
			this.label5.TabIndex = 4;
			this.label5.Text = "File size:";
			// 
			// lblFileSize
			// 
			this.lblFileSize.Location = new System.Drawing.Point(184, 72);
			this.lblFileSize.Name = "lblFileSize";
			this.lblFileSize.Size = new System.Drawing.Size(160, 23);
			this.lblFileSize.TabIndex = 5;
			this.lblFileSize.Text = "label6";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(40, 168);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(104, 23);
			this.label7.TabIndex = 6;
			this.label7.Text = "Sample interval:";
			// 
			// lblSampleInterval
			// 
			this.lblSampleInterval.Location = new System.Drawing.Point(184, 168);
			this.lblSampleInterval.Name = "lblSampleInterval";
			this.lblSampleInterval.Size = new System.Drawing.Size(160, 23);
			this.lblSampleInterval.TabIndex = 7;
			this.lblSampleInterval.Text = "label8";
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(40, 192);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(104, 23);
			this.label9.TabIndex = 8;
			this.label9.Text = "Sample count:";
			// 
			// lblSampleCount
			// 
			this.lblSampleCount.Location = new System.Drawing.Point(184, 192);
			this.lblSampleCount.Name = "lblSampleCount";
			this.lblSampleCount.Size = new System.Drawing.Size(160, 23);
			this.lblSampleCount.TabIndex = 9;
			this.lblSampleCount.Text = "label10";
			// 
			// label11
			// 
			this.label11.Location = new System.Drawing.Point(40, 216);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(104, 23);
			this.label11.TabIndex = 10;
			this.label11.Text = "Start date:";
			// 
			// lblStartDate
			// 
			this.lblStartDate.Location = new System.Drawing.Point(184, 216);
			this.lblStartDate.Name = "lblStartDate";
			this.lblStartDate.Size = new System.Drawing.Size(160, 23);
			this.lblStartDate.TabIndex = 11;
			this.lblStartDate.Text = "label12";
			// 
			// label13
			// 
			this.label13.Location = new System.Drawing.Point(40, 240);
			this.label13.Name = "label13";
			this.label13.Size = new System.Drawing.Size(104, 23);
			this.label13.TabIndex = 12;
			this.label13.Text = "Start time:";
			// 
			// lblStartTime
			// 
			this.lblStartTime.Location = new System.Drawing.Point(184, 240);
			this.lblStartTime.Name = "lblStartTime";
			this.lblStartTime.Size = new System.Drawing.Size(160, 23);
			this.lblStartTime.TabIndex = 13;
			this.lblStartTime.Text = "label14";
			// 
			// label15
			// 
			this.label15.Location = new System.Drawing.Point(40, 336);
			this.label15.Name = "label15";
			this.label15.Size = new System.Drawing.Size(104, 23);
			this.label15.TabIndex = 14;
			this.label15.Text = "Channel numbers:";
			// 
			// lblChannelMask
			// 
			this.lblChannelMask.Location = new System.Drawing.Point(184, 336);
			this.lblChannelMask.Name = "lblChannelMask";
			this.lblChannelMask.Size = new System.Drawing.Size(160, 23);
			this.lblChannelMask.TabIndex = 15;
			this.lblChannelMask.Text = "label16";
			// 
			// label17
			// 
			this.label17.Location = new System.Drawing.Point(40, 360);
			this.label17.Name = "label17";
			this.label17.Size = new System.Drawing.Size(104, 23);
			this.label17.TabIndex = 16;
			this.label17.Text = "Units:";
			// 
			// lblUnitMask
			// 
			this.lblUnitMask.Location = new System.Drawing.Point(184, 368);
			this.lblUnitMask.Name = "lblUnitMask";
			this.lblUnitMask.Size = new System.Drawing.Size(160, 64);
			this.lblUnitMask.TabIndex = 17;
			this.lblUnitMask.Text = "label18";
			// 
			// label19
			// 
			this.label19.Location = new System.Drawing.Point(40, 312);
			this.label19.Name = "label19";
			this.label19.Size = new System.Drawing.Size(104, 23);
			this.label19.TabIndex = 18;
			this.label19.Text = "AI channel count:";
			// 
			// lblAIChannelCount
			// 
			this.lblAIChannelCount.Location = new System.Drawing.Point(184, 312);
			this.lblAIChannelCount.Name = "lblAIChannelCount";
			this.lblAIChannelCount.Size = new System.Drawing.Size(160, 23);
			this.lblAIChannelCount.TabIndex = 19;
			this.lblAIChannelCount.Text = "label20";
			// 
			// label21
			// 
			this.label21.Location = new System.Drawing.Point(40, 472);
			this.label21.Name = "label21";
			this.label21.Size = new System.Drawing.Size(104, 23);
			this.label21.TabIndex = 20;
			this.label21.Text = "CJC channel count:";
			// 
			// lblCJCChannelCount
			// 
			this.lblCJCChannelCount.Location = new System.Drawing.Point(184, 472);
			this.lblCJCChannelCount.Name = "lblCJCChannelCount";
			this.lblCJCChannelCount.Size = new System.Drawing.Size(160, 23);
			this.lblCJCChannelCount.TabIndex = 21;
			this.lblCJCChannelCount.Text = "label22";
			// 
			// label23
			// 
			this.label23.Location = new System.Drawing.Point(40, 544);
			this.label23.Name = "label23";
			this.label23.Size = new System.Drawing.Size(104, 23);
			this.label23.TabIndex = 22;
			this.label23.Text = "DIO channel count:";
			// 
			// lblDIOChannelCount
			// 
			this.lblDIOChannelCount.Location = new System.Drawing.Point(184, 544);
			this.lblDIOChannelCount.Name = "lblDIOChannelCount";
			this.lblDIOChannelCount.Size = new System.Drawing.Size(160, 23);
			this.lblDIOChannelCount.TabIndex = 23;
			this.lblDIOChannelCount.Text = "label24";
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point(328, 576);
			this.btnOK.Name = "btnOK";
			this.btnOK.TabIndex = 24;
			this.btnOK.Text = "OK";
			this.btnOK.Click += new System.EventHandler(this.OnButtonClick_OK);
			// 
			// label25
			// 
			this.label25.Location = new System.Drawing.Point(8, 16);
			this.label25.Name = "label25";
			this.label25.Size = new System.Drawing.Size(136, 23);
			this.label25.TabIndex = 25;
			this.label25.Text = "Results of cbGetFileInfo";
			// 
			// label26
			// 
			this.label26.Location = new System.Drawing.Point(8, 136);
			this.label26.Name = "label26";
			this.label26.Size = new System.Drawing.Size(160, 23);
			this.label26.TabIndex = 26;
			this.label26.Text = "Results of cbGetSampleInfo";
			// 
			// label27
			// 
			this.label27.Location = new System.Drawing.Point(8, 280);
			this.label27.Name = "label27";
			this.label27.Size = new System.Drawing.Size(128, 23);
			this.label27.TabIndex = 27;
			this.label27.Text = "Results of cbGetAIInfo";
			// 
			// label29
			// 
			this.label29.Location = new System.Drawing.Point(8, 512);
			this.label29.Name = "label29";
			this.label29.Size = new System.Drawing.Size(128, 23);
			this.label29.TabIndex = 29;
			this.label29.Text = "Results of cbGetDIOInfo";
			// 
			// label28
			// 
			this.label28.Location = new System.Drawing.Point(8, 440);
			this.label28.Name = "label28";
			this.label28.Size = new System.Drawing.Size(136, 23);
			this.label28.TabIndex = 28;
			this.label28.Text = "Results of cbGetCJCInfo";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(744, 613);
			this.Controls.Add(this.label29);
			this.Controls.Add(this.label28);
			this.Controls.Add(this.label27);
			this.Controls.Add(this.label26);
			this.Controls.Add(this.label25);
			this.Controls.Add(this.btnOK);
			this.Controls.Add(this.lblDIOChannelCount);
			this.Controls.Add(this.label23);
			this.Controls.Add(this.lblCJCChannelCount);
			this.Controls.Add(this.label21);
			this.Controls.Add(this.lblAIChannelCount);
			this.Controls.Add(this.label19);
			this.Controls.Add(this.lblUnitMask);
			this.Controls.Add(this.label17);
			this.Controls.Add(this.lblChannelMask);
			this.Controls.Add(this.label15);
			this.Controls.Add(this.lblStartTime);
			this.Controls.Add(this.label13);
			this.Controls.Add(this.lblStartDate);
			this.Controls.Add(this.label11);
			this.Controls.Add(this.lblSampleCount);
			this.Controls.Add(this.label9);
			this.Controls.Add(this.lblSampleInterval);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.lblFileSize);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.lblFileVersion);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.lblFilename);
			this.Controls.Add(this.label1);
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
	}
}
