using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;
using System.Diagnostics;

/* ULEV01.CS================================================================

File:                         ULEV01.CS

Library Call Demonstrated:    MccBoard.EnableEvent - OnExternalInterrupt
										MccBoard.DisableEvent()

Purpose:             Generates an event for each pulse set at a
							digital or counter External Interrupt pin,
							and reads the digital input at FirstPortA
							every _updateSize interrupts.


Demonstration:			Shows how to enable and respond to events.

Other Library Calls:   ErrHandling()
							  MccBoard.DConfigPort()
							  MccBoard.DIn()

Special Requirements:  Board 0 must have an external interrupt pin
							  and support the OnExternalInterrupt event.


(c) Copyright 2001-2002, Measurement Computing Corp.
All rights reserved.
==========================================================================*/

namespace ULEV01
{
	/// <summary>
	///    To use member functions of the Form as MccDaq event handlers, we
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

	public class frmEventDisplay : System.Windows.Forms.Form
	{
		public System.Windows.Forms.Button cmdDisableEvent;
		public System.Windows.Forms.Button cmdEnableEvent;
		public System.Windows.Forms.Label Label4;
		public System.Windows.Forms.Label Label3;
		public System.Windows.Forms.Label Label2;
		public System.Windows.Forms.Label label1;
		public System.Windows.Forms.Label lblInterruptsMissed;
		public System.Windows.Forms.Label lblDigitalIn;
		public System.Windows.Forms.Label lblEventCount;
		public System.Windows.Forms.Label lblInterruptCount;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public MccDaq.MccBoard DaqBoard = new MccDaq.MccBoard(0);
		public uint _eventCount = 0;
		public uint _intCount = 0;
		public MccDaq.DigitalPortType _digPort = MccDaq.DigitalPortType.FirstPortA;
		const uint _updateSize = 10;

		public TUserData _userData;
		public IntPtr   _ptrUserData;
		public MccDaq.EventCallback _ptrMyCallback;


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
			
       
			//configure the digital port for input
			ULStat =DaqBoard.DConfigPort(this._digPort, MccDaq.DigitalPortDirection.DigitalIn);

			//store a reference to this instance in the TUserData struct
			_userData.ThisObj = this;

			//get a pointer to the TUserData struct to pass to EnableEvent
			_ptrUserData = Marshal.AllocCoTaskMem(Marshal.SizeOf(_userData));
			Marshal.StructureToPtr(_userData, _ptrUserData, false);

			//get pointers to the event handlers to be called...
			_ptrMyCallback = new MccDaq.EventCallback(MyCallback);
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				// Remove any active event handlers & free the unmanaged resouces
				DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes);
				Marshal.FreeCoTaskMem(_ptrUserData);

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
			this.cmdDisableEvent = new System.Windows.Forms.Button();
			this.cmdEnableEvent = new System.Windows.Forms.Button();
			this.Label4 = new System.Windows.Forms.Label();
			this.Label3 = new System.Windows.Forms.Label();
			this.Label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.lblInterruptsMissed = new System.Windows.Forms.Label();
			this.lblDigitalIn = new System.Windows.Forms.Label();
			this.lblEventCount = new System.Windows.Forms.Label();
			this.lblInterruptCount = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// cmdDisableEvent
			// 
			this.cmdDisableEvent.BackColor = System.Drawing.SystemColors.Control;
			this.cmdDisableEvent.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdDisableEvent.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdDisableEvent.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdDisableEvent.Location = new System.Drawing.Point(8, 64);
			this.cmdDisableEvent.Name = "cmdDisableEvent";
			this.cmdDisableEvent.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdDisableEvent.Size = new System.Drawing.Size(139, 47);
			this.cmdDisableEvent.TabIndex = 14;
			this.cmdDisableEvent.Text = "DisableEvent";
			this.cmdDisableEvent.Click += new System.EventHandler(this.cmdDisableEvent_Click);
			// 
			// cmdEnableEvent
			// 
			this.cmdEnableEvent.BackColor = System.Drawing.SystemColors.Control;
			this.cmdEnableEvent.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdEnableEvent.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdEnableEvent.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdEnableEvent.Location = new System.Drawing.Point(8, 8);
			this.cmdEnableEvent.Name = "cmdEnableEvent";
			this.cmdEnableEvent.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.cmdEnableEvent.Size = new System.Drawing.Size(139, 47);
			this.cmdEnableEvent.TabIndex = 13;
			this.cmdEnableEvent.Text = "EnableEvent";
			this.cmdEnableEvent.Click += new System.EventHandler(this.cmdEnableEvent_Click);
			// 
			// Label4
			// 
			this.Label4.AutoSize = true;
			this.Label4.BackColor = System.Drawing.SystemColors.Control;
			this.Label4.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label4.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Label4.ForeColor = System.Drawing.SystemColors.ControlText;
			this.Label4.Location = new System.Drawing.Point(160, 88);
			this.Label4.Name = "Label4";
			this.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label4.Size = new System.Drawing.Size(73, 13);
			this.Label4.TabIndex = 19;
			this.Label4.Text = "Digital Input:";
			// 
			// Label3
			// 
			this.Label3.AutoSize = true;
			this.Label3.BackColor = System.Drawing.SystemColors.Control;
			this.Label3.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label3.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Label3.ForeColor = System.Drawing.SystemColors.ControlText;
			this.Label3.Location = new System.Drawing.Point(168, 56);
			this.Label3.Name = "Label3";
			this.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label3.Size = new System.Drawing.Size(68, 13);
			this.Label3.TabIndex = 18;
			this.Label3.Text = "INT Missed:";
			this.Label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// Label2
			// 
			this.Label2.AutoSize = true;
			this.Label2.BackColor = System.Drawing.SystemColors.Control;
			this.Label2.Cursor = System.Windows.Forms.Cursors.Default;
			this.Label2.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Label2.ForeColor = System.Drawing.SystemColors.ControlText;
			this.Label2.Location = new System.Drawing.Point(160, 36);
			this.Label2.Name = "Label2";
			this.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Label2.Size = new System.Drawing.Size(75, 13);
			this.Label2.TabIndex = 17;
			this.Label2.Text = "Event Count:";
			this.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.BackColor = System.Drawing.SystemColors.Control;
			this.label1.Cursor = System.Windows.Forms.Cursors.Default;
			this.label1.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label1.ForeColor = System.Drawing.SystemColors.ControlText;
			this.label1.Location = new System.Drawing.Point(176, 16);
			this.label1.Name = "label1";
			this.label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.label1.Size = new System.Drawing.Size(62, 13);
			this.label1.TabIndex = 16;
			this.label1.Text = "INT Count:";
			this.label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblInterruptsMissed
			// 
			this.lblInterruptsMissed.BackColor = System.Drawing.SystemColors.Control;
			this.lblInterruptsMissed.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblInterruptsMissed.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblInterruptsMissed.ForeColor = System.Drawing.Color.Blue;
			this.lblInterruptsMissed.Location = new System.Drawing.Point(240, 56);
			this.lblInterruptsMissed.Name = "lblInterruptsMissed";
			this.lblInterruptsMissed.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInterruptsMissed.Size = new System.Drawing.Size(121, 19);
			this.lblInterruptsMissed.TabIndex = 15;
			this.lblInterruptsMissed.Text = "0";
			// 
			// lblDigitalIn
			// 
			this.lblDigitalIn.BackColor = System.Drawing.SystemColors.Control;
			this.lblDigitalIn.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDigitalIn.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDigitalIn.ForeColor = System.Drawing.Color.Blue;
			this.lblDigitalIn.Location = new System.Drawing.Point(240, 88);
			this.lblDigitalIn.Name = "lblDigitalIn";
			this.lblDigitalIn.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDigitalIn.Size = new System.Drawing.Size(121, 19);
			this.lblDigitalIn.TabIndex = 12;
			this.lblDigitalIn.Text = "NA";
			// 
			// lblEventCount
			// 
			this.lblEventCount.BackColor = System.Drawing.SystemColors.Control;
			this.lblEventCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblEventCount.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblEventCount.ForeColor = System.Drawing.Color.Blue;
			this.lblEventCount.Location = new System.Drawing.Point(240, 36);
			this.lblEventCount.Name = "lblEventCount";
			this.lblEventCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblEventCount.Size = new System.Drawing.Size(121, 19);
			this.lblEventCount.TabIndex = 11;
			this.lblEventCount.Text = "0";
			// 
			// lblInterruptCount
			// 
			this.lblInterruptCount.BackColor = System.Drawing.SystemColors.Control;
			this.lblInterruptCount.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblInterruptCount.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblInterruptCount.ForeColor = System.Drawing.Color.Blue;
			this.lblInterruptCount.Location = new System.Drawing.Point(240, 16);
			this.lblInterruptCount.Name = "lblInterruptCount";
			this.lblInterruptCount.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInterruptCount.Size = new System.Drawing.Size(121, 19);
			this.lblInterruptCount.TabIndex = 10;
			this.lblInterruptCount.Text = "0";
			// 
			// frmEventDisplay
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(408, 133);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cmdDisableEvent,
																		  this.cmdEnableEvent,
																		  this.Label4,
																		  this.Label3,
																		  this.Label2,
																		  this.label1,
																		  this.lblInterruptsMissed,
																		  this.lblDigitalIn,
																		  this.lblEventCount,
																		  this.lblInterruptCount});
			this.Name = "frmEventDisplay";
			this.Text = "Universal Library ULEV01";
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

		public static void MyCallback(int bd, MccDaq.EventType et, uint interruptCount, IntPtr pUserData)
		{
			//MyCallback is a static member function. So, we must do some work to get the reference
			// to this object. Recall that we passed in a pointer to a struct that wrapped the 
			// class reference as UserData.
			TUserData userStruct = (TUserData)Marshal.PtrToStructure(pUserData,typeof(TUserData));
			frmEventDisplay ThisObj = (frmEventDisplay)userStruct.ThisObj;
		
			ThisObj._eventCount++;

			// these updates below are "expensive"; so, only do them every 
			//  _updateSize interrupts.
			if (interruptCount >= ThisObj._intCount + _updateSize)
			{
				ThisObj._intCount = interruptCount;

				//read the digital 
				ushort digVal = 0;
				MccDaq.ErrorInfo ULStat = ThisObj.DaqBoard.DIn(MccDaq.DigitalPortType.FirstPortA, out digVal);
				if (ULStat.Value != MccDaq.ErrorInfo.ErrorCode.NoErrors)
					ThisObj.DaqBoard.DisableEvent(MccDaq.EventType.AllEventTypes);

				ThisObj.lblInterruptCount.Text = Convert.ToString(ThisObj._intCount);
				ThisObj.lblEventCount.Text = Convert.ToString(ThisObj._eventCount);
				ThisObj.lblInterruptsMissed.Text = (ThisObj._intCount - ThisObj._eventCount).ToString();
				ThisObj.lblDigitalIn.Text = "0x"+digVal.ToString("x2");
			}
		}

		private void cmdEnableEvent_Click(object sender, System.EventArgs e)
		{
			/// Enable and connect one or more event types to a single user callback
			/// function using MccDaq.MccBoard.EnableEvent().
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
		
			MccDaq.EventType eventType = MccDaq.EventType.OnExternalInterrupt;
			uint eventSize = 0;			// not used for OnExternalInterrupt
			MccDaq.ErrorInfo ULStat = DaqBoard.EnableEvent(eventType, eventSize, _ptrMyCallback, _ptrUserData);
		
			if (ULStat.Value == MccDaq.ErrorInfo.ErrorCode.NoErrors)
			{
				this._eventCount = 0;
				this._intCount = 0;
				this.lblEventCount.Text = _eventCount.ToString();
				this.lblInterruptsMissed.Text = "0";
				this.lblInterruptCount.Text = "0";

				this.lblDigitalIn.Text = "NA";
			}
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
	}
}
