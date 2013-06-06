using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace ULLOG03
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		public const int MAX_PATH = 260;
		private string m_Path = "..\\..\\..\\..";

		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.ListBox lbData;
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


			// create an instance of the data logger
			MccDaq.DataLogger logger = new MccDaq.DataLogger(filename);


			//  Set the preferences 
			//    Parameters
			//      timeFormat					  :specifies times are 12 or 24 hour format
			//      timeZone					  :specifies local time of GMT
			//      units						  :specifies Fahrenheit, Celsius, or Kelvin
			MccDaq.TimeFormat	timeFormat = MccDaq.TimeFormat.TwelveHour;
			MccDaq.TimeZone		timeZone = MccDaq.TimeZone.Local;
			MccDaq.TempScale	units = MccDaq.TempScale.Fahrenheit;
			logger.SetPreferences(timeFormat, timeZone, units);
	

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
			}


			//  Get the ANALOG channel count for the first file in the directory
			//   Parameters:
			//	   aiChannelCount					:receives the number of AI chennels logged
			int	aiChannelCount = 0;
			float [] aiChannelData = null;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetAIChannelCount(ref aiChannelCount);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					aiChannelData = new float [sampleCount * aiChannelCount];
				}
			}


			//  Get the CJC info for the first file in the directory
			//   Parameters:
			//	   cjcChannelCount					:receives the number of CJC chennels logged
			int	cjcChannelCount = 0;
			float [] cjcChannelData = null;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetCJCInfo( ref cjcChannelCount);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					cjcChannelData = new float [sampleCount * cjcChannelCount];
				}
			}


			//  Get the DIO info for the first file in the directory
			//   Parameters:
			//	   dioChannelCount					:receives the number of DIO chennels logged
			int	dioChannelCount = 0;
			int [] dioChannelData = null;
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.GetDIOInfo(ref dioChannelCount);
				if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
				{
					dioChannelData = new int [sampleCount * dioChannelCount];
				}
			}


			//  Read the time tag information
			//   Parameters:
			//	   startSample						:first sample to read
			//	   sampleCount						:number of samples to read
			//     dateTags							:receives the date tag information
			//     timeTags							:receives the time tag information
			int startSample = 0;
			int [] dateTags = new int [sampleCount];
			int [] timeTags = new int [sampleCount];
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.ReadTimeTags(startSample, sampleCount, ref dateTags, ref timeTags);
			}


			//  Read the Analog data
			//   Parameters:
			//	   startSample						:first sample to read
			//	   sampleCount						:number of samples to read
			//     aiChannelData					:receives the analog data
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.ReadAIChannels(startSample, sampleCount, ref aiChannelData);
			}


			//  Read the CJC data
			//   Parameters:
			//	   startSample						:first sample to read
			//	   sampleCount						:number of samples to read
			//     cjcChannelData					:receives the cjc data
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.ReadCJCChannels(startSample, sampleCount, ref cjcChannelData);
			}


			//  Read the DIO data
			//   Parameters:
			//	   startSample						:first sample to read
			//	   sampleCount						:number of samples to read
			//     dioChannelData					:receives the dio data
			if (errorInfo.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				errorInfo = logger.ReadDIOChannels(startSample, sampleCount, ref dioChannelData);
			}


			// display the data in teh list box
			string	displayStr;
			string	dateStr;
			string	timeStr;
			string	postfix;
			int		index;

			for (int i=0; i<sampleCount; i++)
			{
				int		date = dateTags[i];
				int		time = timeTags[i];

				int day = date & 0xff;
				int month = (date>>8) & 0xff;
				int year = (date>>16) & 0xffff;
				dateStr = month.ToString() + "/" + day.ToString() + "/" + year.ToString();

				switch ((time >> 24) & 0xff)
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
				int hours = (time>>16) & 0xff;
				int minutes = (time>>8) & 0xff;
				int seconds = (time) & 0xff;
				timeStr = hours.ToString() + ":" + minutes.ToString() + ":" + seconds.ToString() + ":" + postfix;

				displayStr = dateStr + "  " + timeStr;

				if (aiChannelCount > 0)
				{
					index = i * aiChannelCount;
					for (int j=0; j<aiChannelCount; j++)
					{
						displayStr += "\t\t" + aiChannelData[index++].ToString();
					}
				}

				if (cjcChannelCount > 0)
				{
					index = i * cjcChannelCount;
					for (int j=0; j<cjcChannelCount; j++)
					{
						displayStr += "\t\t" + cjcChannelData[index++].ToString();
					}
				}

				if (dioChannelCount > 0)
				{
					index = i * dioChannelCount;
					for (int j=0; j<dioChannelCount; j++)
					{
						displayStr += "\t" + dioChannelData[index++].ToString();
					}
				}

				lbData.Items.Add(displayStr);
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
			this.lbData = new System.Windows.Forms.ListBox();
			this.btnOK = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lbData
			// 
			this.lbData.Location = new System.Drawing.Point(8, 8);
			this.lbData.Name = "lbData";
			this.lbData.Size = new System.Drawing.Size(944, 355);
			this.lbData.TabIndex = 0;
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point(443, 384);
			this.btnOK.Name = "btnOK";
			this.btnOK.TabIndex = 1;
			this.btnOK.Text = "OK";
			this.btnOK.Click += new System.EventHandler(this.OnButtonClick_OK);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(960, 421);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnOK,
																		  this.lbData});
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
