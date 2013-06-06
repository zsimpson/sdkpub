using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;
using System.Diagnostics;

/* ULEV02.CS================================================================

File:                         ULEV01.CS

Library Call Demonstrated:    MccBoard.EnableEvent - OnDataAvailable, OnEndOfAiScan,
													 and OnScanError
							  MccBoard.DisableEvent()

Purpose:                      Scans a single channel and displays the latest
                              sample acquired every EventSize or more samples.
							  Also updates the latest sample upon scan completion
                              or end. Fatal errors such as OVERRUN errors, cause
                              the scan to be aborted.


Demonstration:                Shows how to enable and respond to events.

Other Library Calls:          ErrHandling()
							  MccBoard.AInScan()

Special Requirements:         Board 0 must support event handling and have
                              paced analog inputs.

(c) Copyright 2001-2002, Measurement Computing Corp.
All rights reserved.
==========================================================================*/

namespace ULEV02
{
   /// <summary>
   ///	  To use member functions of the Form as MccDaq event handlers, we
   ///    must declare them as static member functions. However, static 
   ///    member functions are not associated with any class instance. 
   ///    So, we send a reference to 'this' class instance through the 
   ///    UserData parameter; but classes are reference types, which cannot
   ///    be directly converted to pointers to be passed in as UserData. 
   ///    Instead, we must wrap the class reference in a value type, such as
   ///    a 'struct', before converting to a pointer. TUserData is a value
   ///    type structure that simply wraps the class reference.
   /// </summary>
   /// 
   public struct TUserData
   {
      public object ThisObj;
   }
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmEventDisplay : System.Windows.Forms.Form
	{
      public System.Windows.Forms.Button cmdStop;
      public System.Windows.Forms.Button cmdStart;
      public System.Windows.Forms.Button cmdDisableEvent;
      public System.Windows.Forms.Button cmdEnableEvent;
      public System.Windows.Forms.CheckBox chkAutoRestart;
      public System.Windows.Forms.Label Label4;
      public System.Windows.Forms.Label Label3;
      public System.Windows.Forms.Label Label2;
      public System.Windows.Forms.Label Label1;
      public System.Windows.Forms.Label lblLatestSample;
      public System.Windows.Forms.Label lblStatus;
      public System.Windows.Forms.Label lblSampleCount;
      private System.Windows.Forms.NumericUpDown EventSize;


      public MccDaq.MccBoard DaqBoard = new MccDaq.MccBoard(0);
      public int TotalCount = 2000;
      public int DesiredRate = 200;
      public MccDaq.Range Range = MccDaq.Range.Bip5Volts;
      public MccDaq.ScanOptions Options = MccDaq.ScanOptions.Background 
                                              | MccDaq.ScanOptions.ConvertData;
      public int hBuffer;


      public TUserData _userData;
      public IntPtr   _ptrUserData;
      public MccDaq.EventCallback _ptrMyCallback;
      public MccDaq.EventCallback _ptrOnScanError;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public frmEventDisplay()
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

			// Allocate buffer to hold data...
			hBuffer = MccDaq.MccService.WinBufAlloc(TotalCount);
			if (hBuffer==0) throw(new OutOfMemoryException("Insufficient memory."));
       
			//store a reference to this instance in the TUserData struct
			_userData.ThisObj = this;

			//get a pointer to the TUserData struct to pass to EnableEvent
			_ptrUserData = Marshal.AllocCoTaskMem(Marshal.SizeOf(_userData));
			Marshal.StructureToPtr(_userData, _ptrUserData, false);

			//get pointers to the event handlers to be called...
			_ptrMyCallback = new MccDaq.EventCallback(MyCallback);
			_ptrOnScanError = new MccDaq.EventCallback(OnScanError);

		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				// Stop any active background operations. No background operations
				//   can be active while disabling event handlers.
				DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);

				// Remove any active event handlers & free the unmanaged resouces
				DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes);
				Marshal.FreeCoTaskMem(_ptrUserData);

				//finally, free the data buffer
				if (hBuffer!=0)
					MccDaq.MccService.WinBufFree(hBuffer);   
        		hBuffer = 0;

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
         this.cmdStop = new System.Windows.Forms.Button();
         this.cmdStart = new System.Windows.Forms.Button();
         this.cmdDisableEvent = new System.Windows.Forms.Button();
         this.cmdEnableEvent = new System.Windows.Forms.Button();
         this.chkAutoRestart = new System.Windows.Forms.CheckBox();
         this.Label4 = new System.Windows.Forms.Label();
         this.Label3 = new System.Windows.Forms.Label();
         this.Label2 = new System.Windows.Forms.Label();
         this.Label1 = new System.Windows.Forms.Label();
         this.lblLatestSample = new System.Windows.Forms.Label();
         this.lblStatus = new System.Windows.Forms.Label();
         this.lblSampleCount = new System.Windows.Forms.Label();
         this.EventSize = new System.Windows.Forms.NumericUpDown();
         ((System.ComponentModel.ISupportInitialize)(this.EventSize)).BeginInit();
         this.SuspendLayout();
         // 
         // cmdStop
         // 
         this.cmdStop.BackColor = System.Drawing.SystemColors.Control;
         this.cmdStop.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdStop.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdStop.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdStop.Location = new System.Drawing.Point(16, 136);
         this.cmdStop.Name = "cmdStop";
         this.cmdStop.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdStop.Size = new System.Drawing.Size(115, 33);
         this.cmdStop.TabIndex = 11;
         this.cmdStop.Text = "Stop";
         this.cmdStop.Click += new System.EventHandler(this.cmdStop_Click);
         // 
         // cmdStart
         // 
         this.cmdStart.BackColor = System.Drawing.SystemColors.Control;
         this.cmdStart.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdStart.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdStart.Location = new System.Drawing.Point(16, 104);
         this.cmdStart.Name = "cmdStart";
         this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdStart.Size = new System.Drawing.Size(115, 33);
         this.cmdStart.TabIndex = 10;
         this.cmdStart.Text = "Start";
         this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
         // 
         // cmdDisableEvent
         // 
         this.cmdDisableEvent.BackColor = System.Drawing.SystemColors.Control;
         this.cmdDisableEvent.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdDisableEvent.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdDisableEvent.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdDisableEvent.Location = new System.Drawing.Point(16, 56);
         this.cmdDisableEvent.Name = "cmdDisableEvent";
         this.cmdDisableEvent.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdDisableEvent.Size = new System.Drawing.Size(115, 33);
         this.cmdDisableEvent.TabIndex = 9;
         this.cmdDisableEvent.Text = "DisableEvent";
         this.cmdDisableEvent.Click += new System.EventHandler(this.cmdDisableEvent_Click);
         // 
         // cmdEnableEvent
         // 
         this.cmdEnableEvent.BackColor = System.Drawing.SystemColors.Control;
         this.cmdEnableEvent.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdEnableEvent.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdEnableEvent.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdEnableEvent.Location = new System.Drawing.Point(16, 24);
         this.cmdEnableEvent.Name = "cmdEnableEvent";
         this.cmdEnableEvent.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdEnableEvent.Size = new System.Drawing.Size(115, 33);
         this.cmdEnableEvent.TabIndex = 8;
         this.cmdEnableEvent.Text = "EnableEvent";
         this.cmdEnableEvent.Click += new System.EventHandler(this.cmdEnableEvent_Click);
         // 
         // chkAutoRestart
         // 
         this.chkAutoRestart.BackColor = System.Drawing.SystemColors.Control;
         this.chkAutoRestart.Cursor = System.Windows.Forms.Cursors.Default;
         this.chkAutoRestart.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.chkAutoRestart.ForeColor = System.Drawing.SystemColors.ControlText;
         this.chkAutoRestart.Location = new System.Drawing.Point(216, 128);
         this.chkAutoRestart.Name = "chkAutoRestart";
         this.chkAutoRestart.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.chkAutoRestart.Size = new System.Drawing.Size(95, 21);
         this.chkAutoRestart.TabIndex = 13;
         this.chkAutoRestart.Text = "Auto Restart";
         // 
         // Label4
         // 
         this.Label4.BackColor = System.Drawing.SystemColors.Control;
         this.Label4.Cursor = System.Windows.Forms.Cursors.Default;
         this.Label4.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Label4.ForeColor = System.Drawing.SystemColors.ControlText;
         this.Label4.Location = new System.Drawing.Point(152, 24);
         this.Label4.Name = "Label4";
         this.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.Label4.Size = new System.Drawing.Size(89, 21);
         this.Label4.TabIndex = 20;
         this.Label4.Text = "Event Size:";
         this.Label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // Label3
         // 
         this.Label3.BackColor = System.Drawing.SystemColors.Control;
         this.Label3.Cursor = System.Windows.Forms.Cursors.Default;
         this.Label3.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Label3.ForeColor = System.Drawing.SystemColors.ControlText;
         this.Label3.Location = new System.Drawing.Point(152, 96);
         this.Label3.Name = "Label3";
         this.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.Label3.Size = new System.Drawing.Size(89, 21);
         this.Label3.TabIndex = 19;
         this.Label3.Text = "Latest Sample:";
         this.Label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // Label2
         // 
         this.Label2.BackColor = System.Drawing.SystemColors.Control;
         this.Label2.Cursor = System.Windows.Forms.Cursors.Default;
         this.Label2.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Label2.ForeColor = System.Drawing.SystemColors.ControlText;
         this.Label2.Location = new System.Drawing.Point(152, 72);
         this.Label2.Name = "Label2";
         this.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.Label2.Size = new System.Drawing.Size(89, 21);
         this.Label2.TabIndex = 18;
         this.Label2.Text = "Total Count:";
         this.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // Label1
         // 
         this.Label1.BackColor = System.Drawing.SystemColors.Control;
         this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
         this.Label1.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Label1.ForeColor = System.Drawing.SystemColors.ControlText;
         this.Label1.Location = new System.Drawing.Point(152, 48);
         this.Label1.Name = "Label1";
         this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.Label1.Size = new System.Drawing.Size(89, 21);
         this.Label1.TabIndex = 17;
         this.Label1.Text = "Status:";
         this.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // lblLatestSample
         // 
         this.lblLatestSample.BackColor = System.Drawing.SystemColors.Control;
         this.lblLatestSample.Cursor = System.Windows.Forms.Cursors.Default;
         this.lblLatestSample.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.lblLatestSample.ForeColor = System.Drawing.Color.Blue;
         this.lblLatestSample.Location = new System.Drawing.Point(248, 96);
         this.lblLatestSample.Name = "lblLatestSample";
         this.lblLatestSample.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.lblLatestSample.Size = new System.Drawing.Size(141, 21);
         this.lblLatestSample.TabIndex = 16;
         this.lblLatestSample.Text = "NA";
         // 
         // lblStatus
         // 
         this.lblStatus.BackColor = System.Drawing.SystemColors.Control;
         this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
         this.lblStatus.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.lblStatus.ForeColor = System.Drawing.Color.Blue;
         this.lblStatus.Location = new System.Drawing.Point(248, 48);
         this.lblStatus.Name = "lblStatus";
         this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.lblStatus.Size = new System.Drawing.Size(141, 21);
         this.lblStatus.TabIndex = 15;
         this.lblStatus.Text = "IDLE";
         // 
         // lblSampleCount
         // 
         this.lblSampleCount.BackColor = System.Drawing.SystemColors.Control;
         this.lblSampleCount.Cursor = System.Windows.Forms.Cursors.Default;
         this.lblSampleCount.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.lblSampleCount.ForeColor = System.Drawing.Color.Blue;
         this.lblSampleCount.Location = new System.Drawing.Point(248, 72);
         this.lblSampleCount.Name = "lblSampleCount";
         this.lblSampleCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.lblSampleCount.Size = new System.Drawing.Size(141, 21);
         this.lblSampleCount.TabIndex = 14;
         this.lblSampleCount.Text = "0";
         // 
         // EventSize
         // 
         this.EventSize.Increment = new System.Decimal(new int[] {
                                                                    100,
                                                                    0,
                                                                    0,
                                                                    0});
         this.EventSize.Location = new System.Drawing.Point(248, 24);
         this.EventSize.Maximum = new System.Decimal(new int[] {
                                                                  2000,
                                                                  0,
                                                                  0,
                                                                  0});
         this.EventSize.Name = "EventSize";
         this.EventSize.Size = new System.Drawing.Size(144, 20);
         this.EventSize.TabIndex = 22;
         this.EventSize.Value = new System.Decimal(new int[] {
                                                                100,
                                                                0,
                                                                0,
                                                                0});
         // 
         // frmEventDisplay
         // 
         this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
         this.ClientSize = new System.Drawing.Size(440, 197);
         this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                      this.EventSize,
                                                                      this.chkAutoRestart,
                                                                      this.Label4,
                                                                      this.Label3,
                                                                      this.Label2,
                                                                      this.Label1,
                                                                      this.lblLatestSample,
                                                                      this.lblStatus,
                                                                      this.lblSampleCount,
                                                                      this.cmdStop,
                                                                      this.cmdStart,
                                                                      this.cmdDisableEvent,
                                                                      this.cmdEnableEvent});
         this.Name = "frmEventDisplay";
         this.Text = "Universal Library ULEV02";
         ((System.ComponentModel.ISupportInitialize)(this.EventSize)).EndInit();
         this.ResumeLayout(false);

      }
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmEventDisplay());
		}

      
      public static void MyCallback(int bd, MccDaq.EventType et, uint sampleCount, IntPtr pUserData)
      {
		  //MyCallback is a static member function. So, we must do some work to get the reference
		  // to this object. Recall that we passed in a pointer to a struct that wrapped the 
		  // class reference as UserData.
         TUserData userStruct = (TUserData)Marshal.PtrToStructure(pUserData,typeof(TUserData));
         frmEventDisplay ThisObj = (frmEventDisplay)userStruct.ThisObj;
         
		  //Calculate the index of the latest sample in the buffer. 
         int sampleIdx = ((int)sampleCount-1) % ThisObj.TotalCount;
         ushort rawData;
         float voltData;

		  //Retrieve the latest sample and convert it to engineering units.
         MccDaq.MccService.WinBufToArray(ThisObj.hBuffer, out rawData, (int)sampleIdx, 1);
         ThisObj.DaqBoard.ToEngUnits(ThisObj.Range, rawData, out voltData);

         // Update display values.
         ThisObj.lblSampleCount.Text = sampleCount.ToString();
         ThisObj.lblLatestSample.Text = voltData.ToString("F4")+" V";
         ThisObj.lblStatus.Text = "RUNNING";

         if (et==MccDaq.EventType.OnEndOfAiScan)
         {
			 //If the event is the end of acquisition, release the resources in preparation for
			 //  the next scan.
            ThisObj.DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
            
            if (ThisObj.chkAutoRestart.Checked)
            {
               int rate = ThisObj.DesiredRate;

               ThisObj.DaqBoard.AInScan(0, 0, ThisObj.TotalCount, ref rate, ThisObj.Range, ThisObj.hBuffer, ThisObj.Options);
            }
            else
            {
               ThisObj.lblStatus.Text = "IDLE";
            }
         }
      }
   
      public static void OnScanError(int bd, MccDaq.EventType et, uint scanError, IntPtr pdata)
      {
		  //OnScanError is a static member function. So, we must do some work to get the reference
		  // to this object. Recall that we passed in a pointer to a struct that wrapped the 
		  // class reference as UserData...
         TUserData thisStruct = (TUserData)Marshal.PtrToStructure(pdata,typeof(TUserData));
         frmEventDisplay ThisObj = (frmEventDisplay)thisStruct.ThisObj;

         ThisObj.DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
		 
		 // Reset the chkAutoRestart such that the 'OnEndOfAiScan' event does
		 //not automatically start a new scan
         ThisObj.chkAutoRestart.Checked = false;
      }

      private void cmdEnableEvent_Click(object sender, System.EventArgs e)
      {
        /// Enable and connect one or more event types to a single user callback
        /// function using MccDaq.MccBoard.EnableEvent().
        ///
        /// If we want to attach a single callback function to more than one event
        /// type, we can do it in a single call to MccDaq.MccBoard.EnableEvent, or we can do this in
        /// separate calls for each event type. The main disadvantage of doing this in a
        /// single call is that if the call generates an error, we will not know which
        /// event type caused the error. In addition, the same error condition could
        /// generate multiple error messages.
        ///
        /// Parameters:
        ///   eventType   :the condition that will cause an event to fire
        ///   eventSize   :only used for MccDaq.EventType.OnDataAvailable to determine how
        ///               many samples to collect before firing an event
        ///   _ptrMyCallback : a pointer to the user function or event handler
        ///                     to call when above event type occurs. Note that the handler
        ///						can be a delegate or a static member function. Here, we use
        ///						a pointer to a static member function.
        ///                         
        ///   _ptrUserData  : a pointer to a value type that will be used within the event 
        ///					   handler. Since our handler is a static member function which
        ///					   does NOT include a reference to this class instance, we're
        ///					   sending the pointer to a struct that holds a reference to the class.
		
         MccDaq.EventType eventType = MccDaq.EventType.OnDataAvailable; 
         eventType |= MccDaq.EventType.OnEndOfAiScan;

         uint eventSize = (uint)this.EventSize.Value;
         MccDaq.ErrorInfo ULStat = DaqBoard.EnableEvent(eventType, eventSize, _ptrMyCallback, _ptrUserData);

         eventType = MccDaq.EventType.OnScanError;
         ULStat = DaqBoard.EnableEvent(eventType, 0, _ptrOnScanError, _ptrUserData);

      }

      private void cmdDisableEvent_Click(object sender, System.EventArgs e)
      {
		 //Disable and disconnect all event types with MccBoard.DisableEvent()
	     //
		 //Since disabling events that were never enabled is harmless,
		 //we can disable all the events at once.
		 //
		 //Parameters:
     	 //		EventType.AllEventTypes  :all event types will be disabled
         DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes);
      }

      private void cmdStart_Click(object sender, System.EventArgs e)
	  {
		 //Start input scan with  MccBoard.AInScan
	     int rate = DesiredRate;
         DaqBoard.AInScan(0, 0, TotalCount, ref rate, Range, hBuffer, Options);
      }

      private void cmdStop_Click(object sender, System.EventArgs e)
      {

         this.chkAutoRestart.Checked = false;
         DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
      }
	}
}
