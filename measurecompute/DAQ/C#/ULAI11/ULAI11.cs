// ==============================================================================
//
//  File:                         ULAI11.CS
//
//  Library Call Demonstrated:    Mccdaq.MccBoard.AIn()
//                                Mccdaq.MccBoard.ToEngUnits()
//
//  Purpose:                      Convert a raw data value to a voltage.
//
//  Demonstration:                Displays a voltage on a user-specified
//                                channel.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//
//  Special Requirements:         Board 0 must have an A/D converter.
//                                Analog signal on specified input channel.
//                                If you are using a 16 bit board, see the
//                                CONVERT RAW DATA VALUES section for the
//                                correct lines of code to be used.
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

namespace ULAI11
{
	public class frmManualConvert : System.Windows.Forms.Form
	{
		// Required by the Windows Form Designer
		private System.ComponentModel.IContainer components;

		public ToolTip ToolTip1;
		public Button cmdStartConvert;
		public Button cmdStopConvert;
		public RadioButton opt10VUni;
		public RadioButton opt10VBip;
		public RadioButton opt5VUni;
		public RadioButton opt5VBip;
		public GroupBox fraGainSel;
		public TextBox txtNumChan;
		public Label lblChanPrompt;
		public GroupBox fraChanSelect;
		public Timer tmrConvert;
		public Label lblShowCalcResults;
		public Label lblCalcResult;
		public Label lblShowData;
		public Label lblValueRead;
		public Label lblGainCodeVal;
		public Label lblGainCode;
		public Label lblMinVal;
		public Label lblFullScaleNeg;
		public Label lblMaxVal;
		public Label lblFullScalePos;
		public Label lblCVLabel;
		public Label lblGCLabel;
		public Label lblInstruct;
		public Label lblDemoFunction;

		private MccDaq.MccBoard DaqBoard;

		public frmManualConvert()
		{
			// This call is required by the Windows Form Designer.
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

			lblGainCode.Text = "BIP5VOLTS"; // initialize gain
			lblGainCodeVal.Text = MccDaq.Range.Bip5Volts.ToString("D");
			lblMinVal.Text = "-5";
			lblMaxVal.Text = "5";
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
			this.cmdStartConvert = new System.Windows.Forms.Button();
			this.cmdStopConvert = new System.Windows.Forms.Button();
			this.fraGainSel = new System.Windows.Forms.GroupBox();
			this.opt10VUni = new System.Windows.Forms.RadioButton();
			this.opt10VBip = new System.Windows.Forms.RadioButton();
			this.opt5VUni = new System.Windows.Forms.RadioButton();
			this.opt5VBip = new System.Windows.Forms.RadioButton();
			this.fraChanSelect = new System.Windows.Forms.GroupBox();
			this.txtNumChan = new System.Windows.Forms.TextBox();
			this.lblChanPrompt = new System.Windows.Forms.Label();
			this.tmrConvert = new System.Windows.Forms.Timer(this.components);
			this.lblShowCalcResults = new System.Windows.Forms.Label();
			this.lblCalcResult = new System.Windows.Forms.Label();
			this.lblShowData = new System.Windows.Forms.Label();
			this.lblValueRead = new System.Windows.Forms.Label();
			this.lblGainCodeVal = new System.Windows.Forms.Label();
			this.lblGainCode = new System.Windows.Forms.Label();
			this.lblMinVal = new System.Windows.Forms.Label();
			this.lblFullScaleNeg = new System.Windows.Forms.Label();
			this.lblMaxVal = new System.Windows.Forms.Label();
			this.lblFullScalePos = new System.Windows.Forms.Label();
			this.lblCVLabel = new System.Windows.Forms.Label();
			this.lblGCLabel = new System.Windows.Forms.Label();
			this.lblInstruct = new System.Windows.Forms.Label();
			this.lblDemoFunction = new System.Windows.Forms.Label();
			this.fraGainSel.SuspendLayout();
			this.fraChanSelect.SuspendLayout();
			this.SuspendLayout();
			// 
			// cmdStartConvert
			// 
			this.cmdStartConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStartConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStartConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStartConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStartConvert.Location = new System.Drawing.Point(352, 256);
			this.cmdStartConvert.Name = "cmdStartConvert";
			this.cmdStartConvert.Size = new System.Drawing.Size(52, 27);
			this.cmdStartConvert.TabIndex = 3;
			this.cmdStartConvert.Text = "Start";
			this.cmdStartConvert.Click += new System.EventHandler(this.cmdStartConvert_Click);
			// 
			// cmdStopConvert
			// 
			this.cmdStopConvert.BackColor = System.Drawing.SystemColors.Control;
			this.cmdStopConvert.Cursor = System.Windows.Forms.Cursors.Default;
			this.cmdStopConvert.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.cmdStopConvert.ForeColor = System.Drawing.SystemColors.ControlText;
			this.cmdStopConvert.Location = new System.Drawing.Point(352, 256);
			this.cmdStopConvert.Name = "cmdStopConvert";
			this.cmdStopConvert.Size = new System.Drawing.Size(52, 27);
			this.cmdStopConvert.TabIndex = 4;
			this.cmdStopConvert.Text = "Quit";
			this.cmdStopConvert.Visible = false;
			this.cmdStopConvert.Click += new System.EventHandler(this.cmdStopConvert_Click);
			// 
			// fraGainSel
			// 
			this.fraGainSel.BackColor = System.Drawing.SystemColors.Window;
			this.fraGainSel.Controls.AddRange(new System.Windows.Forms.Control[] {
																											this.opt10VUni,
																											this.opt10VBip,
																											this.opt5VUni,
																											this.opt5VBip});
			this.fraGainSel.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.fraGainSel.ForeColor = System.Drawing.SystemColors.WindowText;
			this.fraGainSel.Location = new System.Drawing.Point(208, 104);
			this.fraGainSel.Name = "fraGainSel";
			this.fraGainSel.Size = new System.Drawing.Size(217, 57);
			this.fraGainSel.TabIndex = 16;
			this.fraGainSel.TabStop = false;
			this.fraGainSel.Text = "Select Range";
			// 
			// opt10VUni
			// 
			this.opt10VUni.BackColor = System.Drawing.SystemColors.Window;
			this.opt10VUni.Cursor = System.Windows.Forms.Cursors.Default;
			this.opt10VUni.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.opt10VUni.ForeColor = System.Drawing.SystemColors.WindowText;
			this.opt10VUni.Location = new System.Drawing.Point(112, 32);
			this.opt10VUni.Name = "opt10VUni";
			this.opt10VUni.Size = new System.Drawing.Size(97, 17);
			this.opt10VUni.TabIndex = 20;
			this.opt10VUni.TabStop = true;
			this.opt10VUni.Text = "10V Unipolar";
			this.opt10VUni.CheckedChanged += new System.EventHandler(this.opt10VUni_CheckedChanged);
			// 
			// opt10VBip
			// 
			this.opt10VBip.BackColor = System.Drawing.SystemColors.Window;
			this.opt10VBip.Cursor = System.Windows.Forms.Cursors.Default;
			this.opt10VBip.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.opt10VBip.ForeColor = System.Drawing.SystemColors.WindowText;
			this.opt10VBip.Location = new System.Drawing.Point(16, 32);
			this.opt10VBip.Name = "opt10VBip";
			this.opt10VBip.Size = new System.Drawing.Size(89, 17);
			this.opt10VBip.TabIndex = 18;
			this.opt10VBip.TabStop = true;
			this.opt10VBip.Text = "10V Bipolar";
			this.opt10VBip.CheckedChanged += new System.EventHandler(this.opt10VBip_CheckedChanged);
			// 
			// opt5VUni
			// 
			this.opt5VUni.BackColor = System.Drawing.SystemColors.Window;
			this.opt5VUni.Cursor = System.Windows.Forms.Cursors.Default;
			this.opt5VUni.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.opt5VUni.ForeColor = System.Drawing.SystemColors.WindowText;
			this.opt5VUni.Location = new System.Drawing.Point(112, 16);
			this.opt5VUni.Name = "opt5VUni";
			this.opt5VUni.Size = new System.Drawing.Size(97, 17);
			this.opt5VUni.TabIndex = 19;
			this.opt5VUni.TabStop = true;
			this.opt5VUni.Text = "5V Unipolar";
			this.opt5VUni.CheckedChanged += new System.EventHandler(this.opt5VUni_CheckedChanged);
			// 
			// opt5VBip
			// 
			this.opt5VBip.BackColor = System.Drawing.SystemColors.Window;
			this.opt5VBip.Checked = true;
			this.opt5VBip.Cursor = System.Windows.Forms.Cursors.Default;
			this.opt5VBip.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.opt5VBip.ForeColor = System.Drawing.SystemColors.WindowText;
			this.opt5VBip.Location = new System.Drawing.Point(16, 16);
			this.opt5VBip.Name = "opt5VBip";
			this.opt5VBip.Size = new System.Drawing.Size(89, 17);
			this.opt5VBip.TabIndex = 17;
			this.opt5VBip.TabStop = true;
			this.opt5VBip.Text = "5V Bipolar";
			this.opt5VBip.CheckedChanged += new System.EventHandler(this.opt5VBip_CheckedChanged);
			// 
			// fraChanSelect
			// 
			this.fraChanSelect.BackColor = System.Drawing.SystemColors.Window;
			this.fraChanSelect.Controls.AddRange(new System.Windows.Forms.Control[] {
																												this.txtNumChan,
																												this.lblChanPrompt});
			this.fraChanSelect.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.fraChanSelect.ForeColor = System.Drawing.SystemColors.WindowText;
			this.fraChanSelect.Location = new System.Drawing.Point(8, 104);
			this.fraChanSelect.Name = "fraChanSelect";
			this.fraChanSelect.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.fraChanSelect.Size = new System.Drawing.Size(185, 57);
			this.fraChanSelect.TabIndex = 21;
			this.fraChanSelect.TabStop = false;
			this.fraChanSelect.Text = "Channel Select";
			// 
			// txtNumChan
			// 
			this.txtNumChan.AcceptsReturn = true;
			this.txtNumChan.AutoSize = false;
			this.txtNumChan.BackColor = System.Drawing.SystemColors.Window;
			this.txtNumChan.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.txtNumChan.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.txtNumChan.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.txtNumChan.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtNumChan.Location = new System.Drawing.Point(144, 24);
			this.txtNumChan.MaxLength = 0;
			this.txtNumChan.Name = "txtNumChan";
			this.txtNumChan.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.txtNumChan.Size = new System.Drawing.Size(25, 25);
			this.txtNumChan.TabIndex = 23;
			this.txtNumChan.Text = "0";
			// 
			// lblChanPrompt
			// 
			this.lblChanPrompt.BackColor = System.Drawing.SystemColors.Window;
			this.lblChanPrompt.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblChanPrompt.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblChanPrompt.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblChanPrompt.Location = new System.Drawing.Point(16, 24);
			this.lblChanPrompt.Name = "lblChanPrompt";
			this.lblChanPrompt.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblChanPrompt.Size = new System.Drawing.Size(121, 17);
			this.lblChanPrompt.TabIndex = 22;
			this.lblChanPrompt.Text = "Channel to display: ";
			this.lblChanPrompt.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// tmrConvert
			// 
			this.tmrConvert.Interval = 300;
			this.tmrConvert.Tick += new System.EventHandler(this.tmrConvert_Tick);
			// 
			// lblShowCalcResults
			// 
			this.lblShowCalcResults.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowCalcResults.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowCalcResults.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowCalcResults.ForeColor = System.Drawing.Color.Blue;
			this.lblShowCalcResults.Location = new System.Drawing.Point(224, 274);
			this.lblShowCalcResults.Name = "lblShowCalcResults";
			this.lblShowCalcResults.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowCalcResults.Size = new System.Drawing.Size(81, 17);
			this.lblShowCalcResults.TabIndex = 11;
			// 
			// lblCalcResult
			// 
			this.lblCalcResult.BackColor = System.Drawing.SystemColors.Window;
			this.lblCalcResult.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCalcResult.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblCalcResult.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCalcResult.Location = new System.Drawing.Point(8, 274);
			this.lblCalcResult.Name = "lblCalcResult";
			this.lblCalcResult.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCalcResult.Size = new System.Drawing.Size(209, 17);
			this.lblCalcResult.TabIndex = 10;
			this.lblCalcResult.Text = "Value after conversion to voltage:";
			this.lblCalcResult.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblShowData
			// 
			this.lblShowData.BackColor = System.Drawing.SystemColors.Window;
			this.lblShowData.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblShowData.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblShowData.ForeColor = System.Drawing.Color.Blue;
			this.lblShowData.Location = new System.Drawing.Point(224, 256);
			this.lblShowData.Name = "lblShowData";
			this.lblShowData.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblShowData.Size = new System.Drawing.Size(65, 17);
			this.lblShowData.TabIndex = 2;
			// 
			// lblValueRead
			// 
			this.lblValueRead.BackColor = System.Drawing.SystemColors.Window;
			this.lblValueRead.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblValueRead.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblValueRead.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblValueRead.Location = new System.Drawing.Point(8, 256);
			this.lblValueRead.Name = "lblValueRead";
			this.lblValueRead.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblValueRead.Size = new System.Drawing.Size(209, 17);
			this.lblValueRead.TabIndex = 1;
			this.lblValueRead.Text = "Value read from selected channel:";
			this.lblValueRead.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblGainCodeVal
			// 
			this.lblGainCodeVal.BackColor = System.Drawing.SystemColors.Window;
			this.lblGainCodeVal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblGainCodeVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblGainCodeVal.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblGainCodeVal.Location = new System.Drawing.Point(360, 208);
			this.lblGainCodeVal.Name = "lblGainCodeVal";
			this.lblGainCodeVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblGainCodeVal.Size = new System.Drawing.Size(33, 17);
			this.lblGainCodeVal.TabIndex = 7;
			this.lblGainCodeVal.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblGainCode
			// 
			this.lblGainCode.BackColor = System.Drawing.SystemColors.Window;
			this.lblGainCode.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblGainCode.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblGainCode.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblGainCode.Location = new System.Drawing.Point(240, 208);
			this.lblGainCode.Name = "lblGainCode";
			this.lblGainCode.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblGainCode.Size = new System.Drawing.Size(89, 17);
			this.lblGainCode.TabIndex = 6;
			this.lblGainCode.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblMinVal
			// 
			this.lblMinVal.BackColor = System.Drawing.SystemColors.Window;
			this.lblMinVal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblMinVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblMinVal.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblMinVal.Location = new System.Drawing.Point(176, 208);
			this.lblMinVal.Name = "lblMinVal";
			this.lblMinVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblMinVal.Size = new System.Drawing.Size(33, 17);
			this.lblMinVal.TabIndex = 8;
			this.lblMinVal.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblFullScaleNeg
			// 
			this.lblFullScaleNeg.BackColor = System.Drawing.SystemColors.Window;
			this.lblFullScaleNeg.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFullScaleNeg.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblFullScaleNeg.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFullScaleNeg.Location = new System.Drawing.Point(8, 208);
			this.lblFullScaleNeg.Name = "lblFullScaleNeg";
			this.lblFullScaleNeg.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFullScaleNeg.Size = new System.Drawing.Size(161, 17);
			this.lblFullScaleNeg.TabIndex = 13;
			this.lblFullScaleNeg.Text = "Negative full scale voltage:";
			this.lblFullScaleNeg.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblMaxVal
			// 
			this.lblMaxVal.BackColor = System.Drawing.SystemColors.Window;
			this.lblMaxVal.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblMaxVal.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblMaxVal.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblMaxVal.Location = new System.Drawing.Point(176, 192);
			this.lblMaxVal.Name = "lblMaxVal";
			this.lblMaxVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblMaxVal.Size = new System.Drawing.Size(33, 17);
			this.lblMaxVal.TabIndex = 9;
			this.lblMaxVal.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblFullScalePos
			// 
			this.lblFullScalePos.BackColor = System.Drawing.SystemColors.Window;
			this.lblFullScalePos.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblFullScalePos.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblFullScalePos.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblFullScalePos.Location = new System.Drawing.Point(8, 192);
			this.lblFullScalePos.Name = "lblFullScalePos";
			this.lblFullScalePos.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblFullScalePos.Size = new System.Drawing.Size(161, 17);
			this.lblFullScalePos.TabIndex = 12;
			this.lblFullScalePos.Text = "Positive full scale voltage:";
			this.lblFullScalePos.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// lblCVLabel
			// 
			this.lblCVLabel.BackColor = System.Drawing.SystemColors.Window;
			this.lblCVLabel.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblCVLabel.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblCVLabel.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblCVLabel.Location = new System.Drawing.Point(344, 184);
			this.lblCVLabel.Name = "lblCVLabel";
			this.lblCVLabel.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblCVLabel.Size = new System.Drawing.Size(81, 17);
			this.lblCVLabel.TabIndex = 15;
			this.lblCVLabel.Text = "Code Value";
			this.lblCVLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblGCLabel
			// 
			this.lblGCLabel.BackColor = System.Drawing.SystemColors.Window;
			this.lblGCLabel.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblGCLabel.Font = new System.Drawing.Font("Arial", 8.25F, (System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblGCLabel.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblGCLabel.Location = new System.Drawing.Point(248, 184);
			this.lblGCLabel.Name = "lblGCLabel";
			this.lblGCLabel.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblGCLabel.Size = new System.Drawing.Size(73, 17);
			this.lblGCLabel.TabIndex = 14;
			this.lblGCLabel.Text = "Range Code";
			this.lblGCLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// lblInstruct
			// 
			this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
			this.lblInstruct.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblInstruct.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblInstruct.ForeColor = System.Drawing.Color.Red;
			this.lblInstruct.Location = new System.Drawing.Point(16, 48);
			this.lblInstruct.Name = "lblInstruct";
			this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblInstruct.Size = new System.Drawing.Size(393, 41);
			this.lblInstruct.TabIndex = 5;
			this.lblInstruct.Text = "NOTE: Please be certain that the board you are using supports the gain you are ch" +
				"oosing and, if gain is not programmable, that the switches on the board are set " +
				"correctly.";
			// 
			// lblDemoFunction
			// 
			this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
			this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
			this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
			this.lblDemoFunction.Location = new System.Drawing.Point(8, 8);
			this.lblDemoFunction.Name = "lblDemoFunction";
			this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.lblDemoFunction.Size = new System.Drawing.Size(414, 17);
			this.lblDemoFunction.TabIndex = 0;
			this.lblDemoFunction.Text = "Demonstration of raw data conversion.";
			this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// frmManualConvert
			// 
			this.AcceptButton = this.cmdStartConvert;
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(433, 309);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																							 this.cmdStartConvert,
																							 this.cmdStopConvert,
																							 this.fraGainSel,
																							 this.fraChanSelect,
																							 this.lblShowCalcResults,
																							 this.lblCalcResult,
																							 this.lblShowData,
																							 this.lblValueRead,
																							 this.lblGainCodeVal,
																							 this.lblGainCode,
																							 this.lblMinVal,
																							 this.lblFullScaleNeg,
																							 this.lblMaxVal,
																							 this.lblFullScalePos,
																							 this.lblCVLabel,
																							 this.lblGCLabel,
																							 this.lblInstruct,
																							 this.lblDemoFunction});
			this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.ForeColor = System.Drawing.SystemColors.WindowText;
			this.Location = new System.Drawing.Point(110, 101);
			this.Name = "frmManualConvert";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Universal Library Analog Data Convert";
			this.fraGainSel.ResumeLayout(false);
			this.fraChanSelect.ResumeLayout(false);
			this.ResumeLayout(false);

		}

	#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmManualConvert());
		}
	    


		private void cmdStartConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStartConvert.Click */
		{
			tmrConvert.Enabled = true;
			cmdStartConvert.Visible = false;
			cmdStopConvert.Visible = true;
		}


		private void cmdStopConvert_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdStopConvert.Click */
		{
			tmrConvert.Enabled = false;
			Application.Exit();
		}



		private void opt10VBip_CheckedChanged(object eventSender, System.EventArgs eventArgs) /* Handles opt10VBip.CheckedChanged */
		{
			if (opt10VBip.Checked)
			{
				lblGainCode.Text = "BIP10VOLTS";
				lblGainCodeVal.Text = MccDaq.Range.Bip10Volts.ToString("D");
				lblMinVal.Text = "-10";
				lblMaxVal.Text = "10";
			}
		}


		private void opt10VUni_CheckedChanged(object eventSender, System.EventArgs eventArgs) /* Handles opt10VUni.CheckedChanged */
		{
			if (opt10VUni.Checked)
			{
				lblGainCode.Text = "UNI10VOLTS";
				lblGainCodeVal.Text = MccDaq.Range.Uni10Volts.ToString("D");
				lblMinVal.Text = "0";
				lblMaxVal.Text = "10";
			}
		}


		private void opt5VBip_CheckedChanged(object eventSender, System.EventArgs eventArgs) /* Handles opt5VBip.CheckedChanged */
		{
			if (opt5VBip.Checked)
			{
				lblGainCode.Text = "BIP5VOLTS";
				lblGainCodeVal.Text = MccDaq.Range.Bip5Volts.ToString("D");
				lblMinVal.Text = "-5";
				lblMaxVal.Text = "5";
			}
		}


		private void opt5VUni_CheckedChanged(object eventSender, System.EventArgs eventArgs) /* Handles opt5VUni.CheckedChanged */
		{
			if (opt5VUni.Checked)
			{
				lblGainCode.Text = "UNI5VOLTS";
				lblGainCodeVal.Text = MccDaq.Range.Uni5Volts.ToString("D");
				lblMinVal.Text = "0";
				lblMaxVal.Text = "5";
			}
		}


		private void tmrConvert_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrConvert.Tick */
		{
			float EngUnits;
			MccDaq.ErrorInfo ULStat;
			UInt16 DataValue;
			object MinVal;
			object MaxVal;
			MccDaq.Range Range;
			int Chan;

			
			tmrConvert.Stop();

			//  Parameters:
			//    Chan       :the input channel number
			//    Range       :the range for the board.
			//    DataValue  :the name for the value collected
			Chan = int.Parse(txtNumChan.Text);

			Range = (MccDaq.Range)(int.Parse(lblGainCodeVal.Text));

			ULStat = DaqBoard.AIn( Chan, Range, out DataValue);
			


			// ******* CONVERT RAW DATA VALUES TO VOLTAGES ********

			ULStat = DaqBoard.ToEngUnits( Range, DataValue, out EngUnits);

			lblShowData.Text = DataValue.ToString("D");
			lblShowCalcResults.Text = EngUnits.ToString("0.000") + " Volts";
			
			tmrConvert.Start();
		}

	}
}