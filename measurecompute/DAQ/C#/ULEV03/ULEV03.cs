using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;
using System.Diagnostics;

/*ULEV03================================================================

 File:                         ULEV03.CS

 Library Call Demonstrated:    MccBoard.EnableEvent - OnScanError
                                             - OnPretrigger
                                             - OnEndOfAiScan
                               MccBoard.DisableEvent()
                               MccBoard.APretrig()

 Purpose:                      Scans a single channel with APretrig and sets
                               digital outputs high upon first trigger event.
                               Upon scan completion, it displays immediate points
                               before and after the trigger. Fatal errors such as
                               OVERRUN errors, cause the scan to be aborted, but TOOFEW
                               errors are ignored.

 Demonstration:                Shows how to enable and respond to events.

 Other Library Calls:          ErrHandling()
                               MccBoard.DOut()

 Special Requirements:         Board 0 must support event handling, APretrig,
                               and DOut.


' (c) Copyright 2001-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================*/
namespace ULEV03
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
      public System.Windows.Forms.CheckBox chkAutoRestart;
      public System.Windows.Forms.Button cmdStop;
      public System.Windows.Forms.Button cmdStart;
      public System.Windows.Forms.Button cmdDisableEvent;
      public System.Windows.Forms.Button cmdEnableEvent;
      public System.Windows.Forms.Label Label2;
      public System.Windows.Forms.Label Label1;
      public System.Windows.Forms.Label lblPreCount;
      public System.Windows.Forms.Label lblStatus;
      public System.Windows.Forms.Label _lblPosttriggerData_9;
      public System.Windows.Forms.Label _lblPosttriggerData_8;
      public System.Windows.Forms.Label _lblPosttriggerData_7;
      public System.Windows.Forms.Label _lblPosttriggerData_6;
      public System.Windows.Forms.Label _lblPosttriggerData_5;
      public System.Windows.Forms.Label _lblPosttriggerData_4;
      public System.Windows.Forms.Label _lblPosttriggerData_3;
      public System.Windows.Forms.Label _lblPosttriggerData_2;
      public System.Windows.Forms.Label _lblPosttriggerData_1;
      public System.Windows.Forms.Label _lblPosttriggerData_0;
      public System.Windows.Forms.Label _lblPretriggerData_9;
      public System.Windows.Forms.Label _lblPretriggerData_8;
      public System.Windows.Forms.Label _lblPretriggerData_7;
      public System.Windows.Forms.Label _lblPretriggerData_6;
      public System.Windows.Forms.Label _lblPretriggerData_5;
      public System.Windows.Forms.Label _lblPretriggerData_4;
      public System.Windows.Forms.Label _lblPretriggerData_3;
      public System.Windows.Forms.Label _lblPretriggerData_2;
      public System.Windows.Forms.Label _lblPretriggerData_1;
      public System.Windows.Forms.Label _lblPretriggerData_0;
      public System.Windows.Forms.Label _lbl_19;
      public System.Windows.Forms.Label _lbl_18;
      public System.Windows.Forms.Label _lbl_17;
      public System.Windows.Forms.Label _lbl_16;
      public System.Windows.Forms.Label _lbl_15;
      public System.Windows.Forms.Label _lbl_14;
      public System.Windows.Forms.Label _lbl_13;
      public System.Windows.Forms.Label _lbl_12;
      public System.Windows.Forms.Label _lbl_11;
      public System.Windows.Forms.Label _lbl_10;
      public System.Windows.Forms.Label _lbl_9;
      public System.Windows.Forms.Label _lbl_8;
      public System.Windows.Forms.Label _lbl_7;
      public System.Windows.Forms.Label _lbl_6;
      public System.Windows.Forms.Label _lbl_5;
      public System.Windows.Forms.Label _lbl_4;
      public System.Windows.Forms.Label _lbl_3;
      public System.Windows.Forms.Label _lbl_2;
      public System.Windows.Forms.Label _lbl_1;
      public System.Windows.Forms.Label _lbl_0;

      public Label[] lblPostTriggerData;
      public Label[] lblPreTriggerData;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

      public MccDaq.MccBoard DaqBoard = new MccDaq.MccBoard(0);
	  const int Channel = 0;
      const int TotalCount = 5000;
      const int BufferSize = 5512; //we must be able to fit an integer multiple
                                    // of half-fifo worth of data in the buffer 
                                    // ...usually, adding 512 to TotalCount is sufficient
      public int PreCount   = 1000;
      public int ActualPreCount = 0;
      public int DesiredRate = 1000;
      public MccDaq.Range Range = MccDaq.Range.Bip5Volts;
      public MccDaq.ScanOptions Options = MccDaq.ScanOptions.Background;
      public int hBuffer;// = MccDaq.MccService.WinBufAlloc(TotalCount);
      public ushort[] Data = new ushort[BufferSize];
      public ushort[] ChanTags = new ushort[BufferSize];

      //public TDisplayStructure ThisDisplayStruct;
      //public IntPtr ThisStructPtr;
      public TUserData _userData;
      public IntPtr   _ptrUserData;
      public MccDaq.EventCallback _ptrMyCallback;
      public MccDaq.EventCallback _ptrOnScanError;


		public frmEventDisplay()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			// Put references to data labels into arrays for 
			//  easier access using indices.
			lblPostTriggerData = new Label[10];
			lblPostTriggerData.SetValue(_lblPosttriggerData_9, 9);
			lblPostTriggerData.SetValue(_lblPosttriggerData_8, 8);
			lblPostTriggerData.SetValue(_lblPosttriggerData_7, 7);
			lblPostTriggerData.SetValue(_lblPosttriggerData_6, 6);
			lblPostTriggerData.SetValue(_lblPosttriggerData_5, 5);
			lblPostTriggerData.SetValue(_lblPosttriggerData_4, 4);
			lblPostTriggerData.SetValue(_lblPosttriggerData_3, 3);
			lblPostTriggerData.SetValue(_lblPosttriggerData_2, 2);
			lblPostTriggerData.SetValue(_lblPosttriggerData_1, 1);
			lblPostTriggerData.SetValue(_lblPosttriggerData_0, 0);

			lblPreTriggerData = new Label[10];
			lblPreTriggerData.SetValue(_lblPretriggerData_9, 9);
			lblPreTriggerData.SetValue(_lblPretriggerData_8, 8);
			lblPreTriggerData.SetValue(_lblPretriggerData_7, 7);
			lblPreTriggerData.SetValue(_lblPretriggerData_6, 6);
			lblPreTriggerData.SetValue(_lblPretriggerData_5, 5);
			lblPreTriggerData.SetValue(_lblPretriggerData_4, 4);
			lblPreTriggerData.SetValue(_lblPretriggerData_3, 3);
			lblPreTriggerData.SetValue(_lblPretriggerData_2, 2);
			lblPreTriggerData.SetValue(_lblPretriggerData_1, 1);
			lblPreTriggerData.SetValue(_lblPretriggerData_0, 0);

     
         //  Initiate error handling
         //   activating error handling will trap errors like
         //   bad channel numbers and non-configured conditions.
         //   Parameters:
         //     MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
         //     MccDaq.ErrorHandling.StopAll   :if an error is encountered, the program will stop
         
         MccDaq.ErrorInfo ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll);

		 // Allocate buffer to hold data...
         hBuffer = MccDaq.MccService.WinBufAlloc(BufferSize);
       
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
            // stop any active background operations
            DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);

            // remove any active event handlers & free the unmanaged resouces
            DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes);
            Marshal.FreeCoTaskMem(_ptrUserData);

            //finally, free the data buffer
            if (hBuffer!=0)
               MccDaq.MccService.WinBufFree(hBuffer);
				
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
         this.chkAutoRestart = new System.Windows.Forms.CheckBox();
         this.cmdStop = new System.Windows.Forms.Button();
         this.cmdStart = new System.Windows.Forms.Button();
         this.cmdDisableEvent = new System.Windows.Forms.Button();
         this.cmdEnableEvent = new System.Windows.Forms.Button();
         this.Label2 = new System.Windows.Forms.Label();
         this.Label1 = new System.Windows.Forms.Label();
         this.lblPreCount = new System.Windows.Forms.Label();
         this.lblStatus = new System.Windows.Forms.Label();
         this._lblPosttriggerData_9 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_8 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_7 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_6 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_5 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_4 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_3 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_2 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_1 = new System.Windows.Forms.Label();
         this._lblPosttriggerData_0 = new System.Windows.Forms.Label();
         this._lblPretriggerData_9 = new System.Windows.Forms.Label();
         this._lblPretriggerData_8 = new System.Windows.Forms.Label();
         this._lblPretriggerData_7 = new System.Windows.Forms.Label();
         this._lblPretriggerData_6 = new System.Windows.Forms.Label();
         this._lblPretriggerData_5 = new System.Windows.Forms.Label();
         this._lblPretriggerData_4 = new System.Windows.Forms.Label();
         this._lblPretriggerData_3 = new System.Windows.Forms.Label();
         this._lblPretriggerData_2 = new System.Windows.Forms.Label();
         this._lblPretriggerData_1 = new System.Windows.Forms.Label();
         this._lblPretriggerData_0 = new System.Windows.Forms.Label();
         this._lbl_19 = new System.Windows.Forms.Label();
         this._lbl_18 = new System.Windows.Forms.Label();
         this._lbl_17 = new System.Windows.Forms.Label();
         this._lbl_16 = new System.Windows.Forms.Label();
         this._lbl_15 = new System.Windows.Forms.Label();
         this._lbl_14 = new System.Windows.Forms.Label();
         this._lbl_13 = new System.Windows.Forms.Label();
         this._lbl_12 = new System.Windows.Forms.Label();
         this._lbl_11 = new System.Windows.Forms.Label();
         this._lbl_10 = new System.Windows.Forms.Label();
         this._lbl_9 = new System.Windows.Forms.Label();
         this._lbl_8 = new System.Windows.Forms.Label();
         this._lbl_7 = new System.Windows.Forms.Label();
         this._lbl_6 = new System.Windows.Forms.Label();
         this._lbl_5 = new System.Windows.Forms.Label();
         this._lbl_4 = new System.Windows.Forms.Label();
         this._lbl_3 = new System.Windows.Forms.Label();
         this._lbl_2 = new System.Windows.Forms.Label();
         this._lbl_1 = new System.Windows.Forms.Label();
         this._lbl_0 = new System.Windows.Forms.Label();
         this.SuspendLayout();
         // 
         // chkAutoRestart
         // 
         this.chkAutoRestart.BackColor = System.Drawing.SystemColors.Control;
         this.chkAutoRestart.Cursor = System.Windows.Forms.Cursors.Default;
         this.chkAutoRestart.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.chkAutoRestart.ForeColor = System.Drawing.SystemColors.ControlText;
         this.chkAutoRestart.Location = new System.Drawing.Point(24, 224);
         this.chkAutoRestart.Name = "chkAutoRestart";
         this.chkAutoRestart.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.chkAutoRestart.Size = new System.Drawing.Size(95, 21);
         this.chkAutoRestart.TabIndex = 53;
         this.chkAutoRestart.Text = "Auto Restart";
         // 
         // cmdStop
         // 
         this.cmdStop.BackColor = System.Drawing.SystemColors.Control;
         this.cmdStop.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdStop.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdStop.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdStop.Location = new System.Drawing.Point(16, 128);
         this.cmdStop.Name = "cmdStop";
         this.cmdStop.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdStop.Size = new System.Drawing.Size(115, 33);
         this.cmdStop.TabIndex = 52;
         this.cmdStop.Text = "Stop";
         this.cmdStop.Click += new System.EventHandler(this.cmdStop_Click);
         // 
         // cmdStart
         // 
         this.cmdStart.BackColor = System.Drawing.SystemColors.Control;
         this.cmdStart.Cursor = System.Windows.Forms.Cursors.Default;
         this.cmdStart.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.cmdStart.ForeColor = System.Drawing.SystemColors.ControlText;
         this.cmdStart.Location = new System.Drawing.Point(16, 96);
         this.cmdStart.Name = "cmdStart";
         this.cmdStart.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.cmdStart.Size = new System.Drawing.Size(115, 33);
         this.cmdStart.TabIndex = 51;
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
         this.cmdDisableEvent.TabIndex = 50;
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
         this.cmdEnableEvent.TabIndex = 49;
         this.cmdEnableEvent.Text = "EnableEvent";
         this.cmdEnableEvent.Click += new System.EventHandler(this.cmdEnableEvent_Click);
         // 
         // Label2
         // 
         this.Label2.AutoSize = true;
         this.Label2.BackColor = System.Drawing.SystemColors.Control;
         this.Label2.Cursor = System.Windows.Forms.Cursors.Default;
         this.Label2.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Label2.ForeColor = System.Drawing.SystemColors.ControlText;
         this.Label2.Location = new System.Drawing.Point(8, 192);
         this.Label2.Name = "Label2";
         this.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.Label2.Size = new System.Drawing.Size(55, 13);
         this.Label2.TabIndex = 97;
         this.Label2.Text = "PreCount";
         this.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // Label1
         // 
         this.Label1.AutoSize = true;
         this.Label1.BackColor = System.Drawing.SystemColors.Control;
         this.Label1.Cursor = System.Windows.Forms.Cursors.Default;
         this.Label1.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Label1.ForeColor = System.Drawing.SystemColors.ControlText;
         this.Label1.Location = new System.Drawing.Point(24, 168);
         this.Label1.Name = "Label1";
         this.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.Label1.Size = new System.Drawing.Size(39, 13);
         this.Label1.TabIndex = 96;
         this.Label1.Text = "Satus:";
         this.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // lblPreCount
         // 
         this.lblPreCount.BackColor = System.Drawing.SystemColors.Control;
         this.lblPreCount.Cursor = System.Windows.Forms.Cursors.Default;
         this.lblPreCount.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.lblPreCount.ForeColor = System.Drawing.Color.Blue;
         this.lblPreCount.Location = new System.Drawing.Point(64, 192);
         this.lblPreCount.Name = "lblPreCount";
         this.lblPreCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.lblPreCount.Size = new System.Drawing.Size(77, 19);
         this.lblPreCount.TabIndex = 95;
         this.lblPreCount.Text = "NA";
         // 
         // lblStatus
         // 
         this.lblStatus.BackColor = System.Drawing.SystemColors.Control;
         this.lblStatus.Cursor = System.Windows.Forms.Cursors.Default;
         this.lblStatus.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.lblStatus.ForeColor = System.Drawing.Color.Blue;
         this.lblStatus.Location = new System.Drawing.Point(72, 165);
         this.lblStatus.Name = "lblStatus";
         this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this.lblStatus.Size = new System.Drawing.Size(64, 19);
         this.lblStatus.TabIndex = 94;
         this.lblStatus.Text = "IDLE";
         // 
         // _lblPosttriggerData_9
         // 
         this._lblPosttriggerData_9.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_9.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_9.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_9.Location = new System.Drawing.Point(360, 231);
         this._lblPosttriggerData_9.Name = "_lblPosttriggerData_9";
         this._lblPosttriggerData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_9.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_9.TabIndex = 93;
         // 
         // _lblPosttriggerData_8
         // 
         this._lblPosttriggerData_8.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_8.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_8.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_8.Location = new System.Drawing.Point(360, 208);
         this._lblPosttriggerData_8.Name = "_lblPosttriggerData_8";
         this._lblPosttriggerData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_8.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_8.TabIndex = 92;
         // 
         // _lblPosttriggerData_7
         // 
         this._lblPosttriggerData_7.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_7.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_7.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_7.Location = new System.Drawing.Point(360, 185);
         this._lblPosttriggerData_7.Name = "_lblPosttriggerData_7";
         this._lblPosttriggerData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_7.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_7.TabIndex = 91;
         // 
         // _lblPosttriggerData_6
         // 
         this._lblPosttriggerData_6.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_6.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_6.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_6.Location = new System.Drawing.Point(360, 162);
         this._lblPosttriggerData_6.Name = "_lblPosttriggerData_6";
         this._lblPosttriggerData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_6.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_6.TabIndex = 90;
         // 
         // _lblPosttriggerData_5
         // 
         this._lblPosttriggerData_5.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_5.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_5.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_5.Location = new System.Drawing.Point(360, 139);
         this._lblPosttriggerData_5.Name = "_lblPosttriggerData_5";
         this._lblPosttriggerData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_5.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_5.TabIndex = 89;
         // 
         // _lblPosttriggerData_4
         // 
         this._lblPosttriggerData_4.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_4.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_4.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_4.Location = new System.Drawing.Point(360, 116);
         this._lblPosttriggerData_4.Name = "_lblPosttriggerData_4";
         this._lblPosttriggerData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_4.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_4.TabIndex = 88;
         // 
         // _lblPosttriggerData_3
         // 
         this._lblPosttriggerData_3.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_3.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_3.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_3.Location = new System.Drawing.Point(360, 93);
         this._lblPosttriggerData_3.Name = "_lblPosttriggerData_3";
         this._lblPosttriggerData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_3.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_3.TabIndex = 87;
         // 
         // _lblPosttriggerData_2
         // 
         this._lblPosttriggerData_2.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_2.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_2.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_2.Location = new System.Drawing.Point(360, 70);
         this._lblPosttriggerData_2.Name = "_lblPosttriggerData_2";
         this._lblPosttriggerData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_2.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_2.TabIndex = 86;
         // 
         // _lblPosttriggerData_1
         // 
         this._lblPosttriggerData_1.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_1.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_1.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_1.Location = new System.Drawing.Point(360, 47);
         this._lblPosttriggerData_1.Name = "_lblPosttriggerData_1";
         this._lblPosttriggerData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_1.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_1.TabIndex = 85;
         // 
         // _lblPosttriggerData_0
         // 
         this._lblPosttriggerData_0.BackColor = System.Drawing.SystemColors.Control;
         this._lblPosttriggerData_0.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPosttriggerData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPosttriggerData_0.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPosttriggerData_0.Location = new System.Drawing.Point(360, 24);
         this._lblPosttriggerData_0.Name = "_lblPosttriggerData_0";
         this._lblPosttriggerData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPosttriggerData_0.Size = new System.Drawing.Size(63, 17);
         this._lblPosttriggerData_0.TabIndex = 84;
         // 
         // _lblPretriggerData_9
         // 
         this._lblPretriggerData_9.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_9.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_9.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_9.Location = new System.Drawing.Point(216, 231);
         this._lblPretriggerData_9.Name = "_lblPretriggerData_9";
         this._lblPretriggerData_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_9.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_9.TabIndex = 83;
         // 
         // _lblPretriggerData_8
         // 
         this._lblPretriggerData_8.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_8.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_8.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_8.Location = new System.Drawing.Point(216, 208);
         this._lblPretriggerData_8.Name = "_lblPretriggerData_8";
         this._lblPretriggerData_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_8.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_8.TabIndex = 82;
         // 
         // _lblPretriggerData_7
         // 
         this._lblPretriggerData_7.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_7.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_7.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_7.Location = new System.Drawing.Point(216, 185);
         this._lblPretriggerData_7.Name = "_lblPretriggerData_7";
         this._lblPretriggerData_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_7.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_7.TabIndex = 81;
         // 
         // _lblPretriggerData_6
         // 
         this._lblPretriggerData_6.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_6.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_6.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_6.Location = new System.Drawing.Point(216, 162);
         this._lblPretriggerData_6.Name = "_lblPretriggerData_6";
         this._lblPretriggerData_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_6.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_6.TabIndex = 80;
         // 
         // _lblPretriggerData_5
         // 
         this._lblPretriggerData_5.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_5.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_5.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_5.Location = new System.Drawing.Point(216, 139);
         this._lblPretriggerData_5.Name = "_lblPretriggerData_5";
         this._lblPretriggerData_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_5.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_5.TabIndex = 79;
         // 
         // _lblPretriggerData_4
         // 
         this._lblPretriggerData_4.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_4.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_4.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_4.Location = new System.Drawing.Point(216, 116);
         this._lblPretriggerData_4.Name = "_lblPretriggerData_4";
         this._lblPretriggerData_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_4.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_4.TabIndex = 78;
         // 
         // _lblPretriggerData_3
         // 
         this._lblPretriggerData_3.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_3.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_3.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_3.Location = new System.Drawing.Point(216, 93);
         this._lblPretriggerData_3.Name = "_lblPretriggerData_3";
         this._lblPretriggerData_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_3.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_3.TabIndex = 77;
         // 
         // _lblPretriggerData_2
         // 
         this._lblPretriggerData_2.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_2.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_2.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_2.Location = new System.Drawing.Point(216, 70);
         this._lblPretriggerData_2.Name = "_lblPretriggerData_2";
         this._lblPretriggerData_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_2.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_2.TabIndex = 76;
         // 
         // _lblPretriggerData_1
         // 
         this._lblPretriggerData_1.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_1.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_1.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_1.Location = new System.Drawing.Point(216, 47);
         this._lblPretriggerData_1.Name = "_lblPretriggerData_1";
         this._lblPretriggerData_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_1.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_1.TabIndex = 75;
         // 
         // _lblPretriggerData_0
         // 
         this._lblPretriggerData_0.BackColor = System.Drawing.SystemColors.Control;
         this._lblPretriggerData_0.Cursor = System.Windows.Forms.Cursors.Default;
         this._lblPretriggerData_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lblPretriggerData_0.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lblPretriggerData_0.Location = new System.Drawing.Point(216, 24);
         this._lblPretriggerData_0.Name = "_lblPretriggerData_0";
         this._lblPretriggerData_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lblPretriggerData_0.Size = new System.Drawing.Size(61, 19);
         this._lblPretriggerData_0.TabIndex = 74;
         // 
         // _lbl_19
         // 
         this._lbl_19.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_19.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_19.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_19.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_19.Location = new System.Drawing.Point(296, 231);
         this._lbl_19.Name = "_lbl_19";
         this._lbl_19.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_19.Size = new System.Drawing.Size(61, 17);
         this._lbl_19.TabIndex = 73;
         this._lbl_19.Text = "Trigger +9";
         // 
         // _lbl_18
         // 
         this._lbl_18.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_18.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_18.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_18.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_18.Location = new System.Drawing.Point(296, 208);
         this._lbl_18.Name = "_lbl_18";
         this._lbl_18.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_18.Size = new System.Drawing.Size(61, 17);
         this._lbl_18.TabIndex = 72;
         this._lbl_18.Text = "Trigger +8";
         // 
         // _lbl_17
         // 
         this._lbl_17.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_17.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_17.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_17.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_17.Location = new System.Drawing.Point(296, 185);
         this._lbl_17.Name = "_lbl_17";
         this._lbl_17.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_17.Size = new System.Drawing.Size(61, 17);
         this._lbl_17.TabIndex = 71;
         this._lbl_17.Text = "Trigger +7";
         // 
         // _lbl_16
         // 
         this._lbl_16.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_16.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_16.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_16.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_16.Location = new System.Drawing.Point(296, 162);
         this._lbl_16.Name = "_lbl_16";
         this._lbl_16.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_16.Size = new System.Drawing.Size(61, 17);
         this._lbl_16.TabIndex = 70;
         this._lbl_16.Text = "Trigger +6";
         // 
         // _lbl_15
         // 
         this._lbl_15.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_15.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_15.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_15.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_15.Location = new System.Drawing.Point(296, 139);
         this._lbl_15.Name = "_lbl_15";
         this._lbl_15.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_15.Size = new System.Drawing.Size(61, 17);
         this._lbl_15.TabIndex = 69;
         this._lbl_15.Text = "Trigger +5";
         // 
         // _lbl_14
         // 
         this._lbl_14.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_14.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_14.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_14.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_14.Location = new System.Drawing.Point(296, 116);
         this._lbl_14.Name = "_lbl_14";
         this._lbl_14.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_14.Size = new System.Drawing.Size(61, 17);
         this._lbl_14.TabIndex = 68;
         this._lbl_14.Text = "Trigger +4";
         // 
         // _lbl_13
         // 
         this._lbl_13.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_13.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_13.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_13.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_13.Location = new System.Drawing.Point(296, 93);
         this._lbl_13.Name = "_lbl_13";
         this._lbl_13.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_13.Size = new System.Drawing.Size(61, 17);
         this._lbl_13.TabIndex = 67;
         this._lbl_13.Text = "Trigger +3";
         // 
         // _lbl_12
         // 
         this._lbl_12.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_12.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_12.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_12.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_12.Location = new System.Drawing.Point(296, 70);
         this._lbl_12.Name = "_lbl_12";
         this._lbl_12.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_12.Size = new System.Drawing.Size(61, 17);
         this._lbl_12.TabIndex = 66;
         this._lbl_12.Text = "Trigger +2";
         // 
         // _lbl_11
         // 
         this._lbl_11.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_11.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_11.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_11.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_11.Location = new System.Drawing.Point(296, 47);
         this._lbl_11.Name = "_lbl_11";
         this._lbl_11.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_11.Size = new System.Drawing.Size(61, 17);
         this._lbl_11.TabIndex = 65;
         this._lbl_11.Text = "Trigger +1";
         // 
         // _lbl_10
         // 
         this._lbl_10.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_10.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_10.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_10.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_10.Location = new System.Drawing.Point(296, 24);
         this._lbl_10.Name = "_lbl_10";
         this._lbl_10.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_10.Size = new System.Drawing.Size(61, 17);
         this._lbl_10.TabIndex = 64;
         this._lbl_10.Text = "Trigger +0";
         // 
         // _lbl_9
         // 
         this._lbl_9.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_9.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_9.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_9.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_9.Location = new System.Drawing.Point(144, 231);
         this._lbl_9.Name = "_lbl_9";
         this._lbl_9.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_9.Size = new System.Drawing.Size(61, 17);
         this._lbl_9.TabIndex = 63;
         this._lbl_9.Text = "Trigger -1";
         // 
         // _lbl_8
         // 
         this._lbl_8.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_8.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_8.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_8.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_8.Location = new System.Drawing.Point(144, 208);
         this._lbl_8.Name = "_lbl_8";
         this._lbl_8.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_8.Size = new System.Drawing.Size(61, 17);
         this._lbl_8.TabIndex = 62;
         this._lbl_8.Text = "Trigger -2";
         // 
         // _lbl_7
         // 
         this._lbl_7.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_7.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_7.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_7.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_7.Location = new System.Drawing.Point(144, 185);
         this._lbl_7.Name = "_lbl_7";
         this._lbl_7.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_7.Size = new System.Drawing.Size(61, 17);
         this._lbl_7.TabIndex = 61;
         this._lbl_7.Text = "Trigger -3";
         // 
         // _lbl_6
         // 
         this._lbl_6.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_6.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_6.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_6.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_6.Location = new System.Drawing.Point(144, 162);
         this._lbl_6.Name = "_lbl_6";
         this._lbl_6.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_6.Size = new System.Drawing.Size(61, 17);
         this._lbl_6.TabIndex = 60;
         this._lbl_6.Text = "Trigger -4";
         // 
         // _lbl_5
         // 
         this._lbl_5.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_5.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_5.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_5.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_5.Location = new System.Drawing.Point(144, 139);
         this._lbl_5.Name = "_lbl_5";
         this._lbl_5.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_5.Size = new System.Drawing.Size(61, 17);
         this._lbl_5.TabIndex = 59;
         this._lbl_5.Text = "Trigger -5";
         // 
         // _lbl_4
         // 
         this._lbl_4.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_4.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_4.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_4.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_4.Location = new System.Drawing.Point(144, 116);
         this._lbl_4.Name = "_lbl_4";
         this._lbl_4.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_4.Size = new System.Drawing.Size(61, 17);
         this._lbl_4.TabIndex = 58;
         this._lbl_4.Text = "Trigger -6";
         // 
         // _lbl_3
         // 
         this._lbl_3.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_3.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_3.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_3.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_3.Location = new System.Drawing.Point(144, 93);
         this._lbl_3.Name = "_lbl_3";
         this._lbl_3.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_3.Size = new System.Drawing.Size(61, 17);
         this._lbl_3.TabIndex = 57;
         this._lbl_3.Text = "Trigger -7";
         // 
         // _lbl_2
         // 
         this._lbl_2.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_2.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_2.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_2.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_2.Location = new System.Drawing.Point(144, 70);
         this._lbl_2.Name = "_lbl_2";
         this._lbl_2.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_2.Size = new System.Drawing.Size(61, 17);
         this._lbl_2.TabIndex = 56;
         this._lbl_2.Text = "Trigger -8";
         // 
         // _lbl_1
         // 
         this._lbl_1.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_1.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_1.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_1.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_1.Location = new System.Drawing.Point(144, 47);
         this._lbl_1.Name = "_lbl_1";
         this._lbl_1.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_1.Size = new System.Drawing.Size(61, 17);
         this._lbl_1.TabIndex = 55;
         this._lbl_1.Text = "Trigger -9";
         // 
         // _lbl_0
         // 
         this._lbl_0.BackColor = System.Drawing.SystemColors.Control;
         this._lbl_0.Cursor = System.Windows.Forms.Cursors.Default;
         this._lbl_0.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this._lbl_0.ForeColor = System.Drawing.SystemColors.ControlText;
         this._lbl_0.Location = new System.Drawing.Point(144, 24);
         this._lbl_0.Name = "_lbl_0";
         this._lbl_0.RightToLeft = System.Windows.Forms.RightToLeft.No;
         this._lbl_0.Size = new System.Drawing.Size(61, 17);
         this._lbl_0.TabIndex = 54;
         this._lbl_0.Text = "Trigger -10";
         // 
         // frmEventDisplay
         // 
         this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
         this.ClientSize = new System.Drawing.Size(440, 269);
         this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                      this.chkAutoRestart,
                                                                      this.cmdStop,
                                                                      this.cmdStart,
                                                                      this.cmdDisableEvent,
                                                                      this.cmdEnableEvent,
                                                                      this.Label2,
                                                                      this.Label1,
                                                                      this.lblPreCount,
                                                                      this.lblStatus,
                                                                      this._lblPosttriggerData_9,
                                                                      this._lblPosttriggerData_8,
                                                                      this._lblPosttriggerData_7,
                                                                      this._lblPosttriggerData_6,
                                                                      this._lblPosttriggerData_5,
                                                                      this._lblPosttriggerData_4,
                                                                      this._lblPosttriggerData_3,
                                                                      this._lblPosttriggerData_2,
                                                                      this._lblPosttriggerData_1,
                                                                      this._lblPosttriggerData_0,
                                                                      this._lblPretriggerData_9,
                                                                      this._lblPretriggerData_8,
                                                                      this._lblPretriggerData_7,
                                                                      this._lblPretriggerData_6,
                                                                      this._lblPretriggerData_5,
                                                                      this._lblPretriggerData_4,
                                                                      this._lblPretriggerData_3,
                                                                      this._lblPretriggerData_2,
                                                                      this._lblPretriggerData_1,
                                                                      this._lblPretriggerData_0,
                                                                      this._lbl_19,
                                                                      this._lbl_18,
                                                                      this._lbl_17,
                                                                      this._lbl_16,
                                                                      this._lbl_15,
                                                                      this._lbl_14,
                                                                      this._lbl_13,
                                                                      this._lbl_12,
                                                                      this._lbl_11,
                                                                      this._lbl_10,
                                                                      this._lbl_9,
                                                                      this._lbl_8,
                                                                      this._lbl_7,
                                                                      this._lbl_6,
                                                                      this._lbl_5,
                                                                      this._lbl_4,
                                                                      this._lbl_3,
                                                                      this._lbl_2,
                                                                      this._lbl_1,
                                                                      this._lbl_0});
         this.Name = "frmEventDisplay";
         this.Text = "Universal Library ULEV03";
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


      public static void MyCallback(int bd, MccDaq.EventType et, uint sampleCount, IntPtr pdata)
      {
		 //MyCallback is a static member function. So, we must do some work to get the reference
		 // to this object. Recall that we passed in a pointer to a struct that wrapped the 
		 // class reference as UserData.
         TUserData userStruct = (TUserData)Marshal.PtrToStructure(pdata,typeof(TUserData));
         frmEventDisplay ThisObj = (frmEventDisplay)userStruct.ThisObj;

	     MccDaq.ErrorInfo ULStat;

         // update display values
         ThisObj.lblStatus.Text = "RUNNING";

         if (et==MccDaq.EventType.OnPretrigger)
         {
            // store actual number of pre-trigger samples collected
            ThisObj.ActualPreCount = (int)sampleCount;
            ThisObj.lblPreCount.Text = sampleCount.ToString();

            // signal external device that trigger has been detected
            ULStat = ThisObj.DaqBoard.DOut(MccDaq.DigitalPortType.AuxPort, 0xff);
         }
         else
         {
			
            // Give the library a chance to clean up
            ULStat = ThisObj.DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
            ThisObj.lblStatus.Text = "IDLE";

            //Deassert external device signal
            ULStat = ThisObj.DaqBoard.DOut(MccDaq.DigitalPortType.AuxPort, 0); 

            // Get the data and align it so that oldest data is first
            ULStat = MccDaq.MccService.WinBufToArray(ThisObj.hBuffer, out ThisObj.Data[0], 0, BufferSize - 1);
            ULStat = ThisObj.DaqBoard.AConvertPretrigData( ThisObj.ActualPreCount, TotalCount, ref ThisObj.Data[0], out ThisObj.ChanTags[0]);

		    float engData;
		    int PreTriggerIndex, PostTriggerIndex;
            // Update the Pre- and Post- Trigger data displays
            for(int offset=0; offset<10; ++offset)
            {
                // Determine the data index with respect to the trigger index
                PreTriggerIndex = ThisObj.ActualPreCount - 10 + offset;
                PostTriggerIndex = ThisObj.ActualPreCount + offset;

                // Avoid indexing invalid pretrigger data
               if (10 - offset < System.Convert.ToInt32(ThisObj.ActualPreCount)) 
               {
                  ULStat = ThisObj.DaqBoard.ToEngUnits(ThisObj.Range, ThisObj.Data[PreTriggerIndex], out engData);
                  ThisObj.lblPreTriggerData[offset].Text = engData.ToString("#0.0000") + "V";
               }
               else // this index doesn't point to valid data
                  ThisObj.lblPreTriggerData[offset].Text = "NA";
                

               ULStat = ThisObj.DaqBoard.ToEngUnits(ThisObj.Range, ThisObj.Data[PostTriggerIndex], out engData);
               ThisObj.lblPostTriggerData[offset].Text = engData.ToString("#0.0000") + "V";
            }


            if (ThisObj.chkAutoRestart.CheckState == CheckState.Checked) 
            {
               // Start a new scan
               int rate = ThisObj.DesiredRate;
			   int preCount = ThisObj.PreCount;
			   int count = TotalCount;

               int VarPreCount = ThisObj.PreCount;
               
               ULStat = ThisObj.DaqBoard.APretrig(Channel, Channel, ref preCount, ref count, ref rate, ThisObj.Range, ThisObj.hBuffer, ThisObj.Options);
               ThisObj.lblStatus.ForeColor = System.Drawing.ColorTranslator.FromOle(0x00ff0000);
               ThisObj.lblStatus.Text = "RUNNING";
               ThisObj.lblPreCount.Text = "NA";
            }

                  
         }
      }
   
      public static void OnScanError(int bd, MccDaq.EventType et, uint scanError, IntPtr pdata)
      {
		  //OnScanError is a static member function. So, we must do some work to get the reference
		  // to this object. Recall that we passed in a pointer to a struct that wrapped the 
		  // class reference as UserData.
		 TUserData thisStruct = (TUserData)Marshal.PtrToStructure(pdata,typeof(TUserData));
         frmEventDisplay ThisObj = (frmEventDisplay)thisStruct.ThisObj;

		  if ((MccDaq.ErrorInfo.ErrorCode)scanError!=MccDaq.ErrorInfo.ErrorCode.TooFew)
		  {
			  ThisObj.DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
			  ThisObj.chkAutoRestart.Checked = false;
		  }
      }

      private void cmdEnableEvent_Click(object sender, System.EventArgs e)
      {
         MccDaq.ErrorInfo ULStat;
         
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
         MccDaq.EventType eventType = MccDaq.EventType.OnPretrigger; 
         eventType |= MccDaq.EventType.OnEndOfAiScan;
         ULStat = DaqBoard.EnableEvent(eventType, 0, _ptrMyCallback, _ptrUserData);

         eventType = MccDaq.EventType.OnScanError;
         ULStat = DaqBoard.EnableEvent(eventType, 0, _ptrOnScanError, _ptrUserData);
      }

      private void cmdDisableEvent_Click(object sender, System.EventArgs e)
      {
         DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes);
      }

      private void cmdStart_Click(object sender, System.EventArgs e)
      {
         int rate = DesiredRate;
		 int count = TotalCount;
         DaqBoard.APretrig(Channel, Channel, ref PreCount, ref count, ref rate, Range, hBuffer, Options);
      
      
      }

      private void cmdStop_Click(object sender, System.EventArgs e)
      {
         this.chkAutoRestart.Checked = false;
         DaqBoard.StopBackground(MccDaq.FunctionType.AiFunction);
      }
	}
}
