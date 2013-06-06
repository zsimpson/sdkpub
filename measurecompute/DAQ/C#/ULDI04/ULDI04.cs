// ==============================================================================
//
//  File:                         ULDI04.CS
//
//  Library Call Demonstrated:    MccDaq.MccBoard.DIn()
//
//  Purpose:                      Reads a value from MccDaq.DigitalPortType.AuxPort.
//
//  Demonstration:                Select number of bits and read
//                                    MccDaq.DigitalPortType.AuxPort.
//
//  Other Library Calls:          MccDaq.MccService.ErrHandling()
//								  MccDaq.MccBoard.DConfigPort()
//                                MccDaq.MccBoard.DioConfig.GetDevType()
//                                MccDaq.MccBoard.DioConfig.GetDInMask()
//                                MccDaq.MccBoard.DioConfig.GetDOutMask()
//
//  Special Requirements:         Board 0 must have a digital port.
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

namespace ULDI04
{
    public class frmDigAuxIn : System.Windows.Forms.Form
    {
     
        // Required by the Windows Form Designer
        private System.ComponentModel.IContainer components;

        public ToolTip ToolTip1;
        public Button cmdEndProgram;
        public Timer tmrReadInputs;
        public Label lblShowPortVal;
        public Label lblPortVal;
        public Label lblInstruct;
        public Label lblDemoFunction;

        private MccDaq.MccBoard DaqBoard;
        const MccDaq.DigitalPortType PortNum = MccDaq.DigitalPortType.AuxPort; //  set type of port to auxilliary


        public frmDigAuxIn()
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

            // Determine if board has AuxPort 
            //Parameters:
            //  devNum      : 0-based digital device index
            //  portType    : return value for type of device
            int devNum =0;  //AuxPort is the 0th digital device, if present
            int portType = 0;
            DaqBoard.DioConfig.GetDevType(devNum, out portType);
            if (portType != (int)MccDaq.DigitalPortType.AuxPort)
            {
                // this board doesn't have an AuxPort!
                Application.Exit();
            }

            // Check if AuxPort needs configuring 
            // Parameters:
            //     devNum      : 0-based digital device index
            //      mask    : bitmask indicating corresponding bit is in respecitve direction
            int inmask=0, outmask=0;
            DaqBoard.DioConfig.GetDInMask(devNum, out inmask);
            DaqBoard.DioConfig.GetDOutMask(devNum, out outmask);
            // only non-configurable AuxPorts have overlapping input and output masks
            if (0 == (inmask & outmask))
            {
                DaqBoard.DConfigPort(PortNum, MccDaq.DigitalPortDirection.DigitalIn);
            }

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
            this.cmdEndProgram = new System.Windows.Forms.Button();
            this.tmrReadInputs = new System.Windows.Forms.Timer(this.components);
            this.lblShowPortVal = new System.Windows.Forms.Label();
            this.lblPortVal = new System.Windows.Forms.Label();
            this.lblInstruct = new System.Windows.Forms.Label();
            this.lblDemoFunction = new System.Windows.Forms.Label();
            this.SuspendLayout();
            //
            // cmdEndProgram
            //
            this.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control;
            this.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default;
            this.cmdEndProgram.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText;
            this.cmdEndProgram.Location = new System.Drawing.Point(256, 200);
            this.cmdEndProgram.Name = "cmdEndProgram";
            this.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.cmdEndProgram.Size = new System.Drawing.Size(57, 33);
            this.cmdEndProgram.TabIndex = 3;
            this.cmdEndProgram.Text = "Quit";
            this.cmdEndProgram.Click += new System.EventHandler(this.cmdEndProgram_Click);
            //
            // tmrReadInputs
            //
            this.tmrReadInputs.Enabled = true;
            this.tmrReadInputs.Interval = 200;
            this.tmrReadInputs.Tick += new System.EventHandler(this.tmrReadInputs_Tick);
            //
            // lblShowPortVal
            //
            this.lblShowPortVal.BackColor = System.Drawing.SystemColors.Window;
            this.lblShowPortVal.Cursor = System.Windows.Forms.Cursors.Default;
            this.lblShowPortVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblShowPortVal.ForeColor = System.Drawing.Color.Blue;
            this.lblShowPortVal.Location = new System.Drawing.Point(272, 152);
            this.lblShowPortVal.Name = "lblShowPortVal";
            this.lblShowPortVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblShowPortVal.Size = new System.Drawing.Size(33, 17);
            this.lblShowPortVal.TabIndex = 2;
            //
            // lblPortVal
            //
            this.lblPortVal.BackColor = System.Drawing.SystemColors.Window;
            this.lblPortVal.Cursor = System.Windows.Forms.Cursors.Default;
            this.lblPortVal.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblPortVal.ForeColor = System.Drawing.SystemColors.WindowText;
            this.lblPortVal.Location = new System.Drawing.Point(48, 152);
            this.lblPortVal.Name = "lblPortVal";
            this.lblPortVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblPortVal.Size = new System.Drawing.Size(209, 17);
            this.lblPortVal.TabIndex = 1;
            //
            // lblInstruct
            //
            this.lblInstruct.BackColor = System.Drawing.SystemColors.Window;
            this.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default;
            this.lblInstruct.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblInstruct.ForeColor = System.Drawing.Color.Red;
            this.lblInstruct.Location = new System.Drawing.Point(48, 72);
            this.lblInstruct.Name = "lblInstruct";
            this.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblInstruct.Size = new System.Drawing.Size(233, 33);
            this.lblInstruct.TabIndex = 4;
            this.lblInstruct.Text = "Input a TTL high or low level to auxillary digital inputs to change Data Value.";
            this.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // lblDemoFunction
            //
            this.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window;
            this.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default;
            this.lblDemoFunction.Font = new System.Drawing.Font("Arial", 8.0F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText;
            this.lblDemoFunction.Location = new System.Drawing.Point(40, 16);
            this.lblDemoFunction.Name = "lblDemoFunction";
            this.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblDemoFunction.Size = new System.Drawing.Size(241, 41);
            this.lblDemoFunction.TabIndex = 0;
            this.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DIn() and AuxPort";
            this.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // frmDigAuxIn
            //
            this.AcceptButton = this.cmdEndProgram;
            this.AutoScaleBaseSize = new System.Drawing.Size(6, 13);
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(331, 246);
            this.Controls.AddRange(new System.Windows.Forms.Control[] {this.cmdEndProgram, this.lblShowPortVal, this.lblPortVal, this.lblInstruct, this.lblDemoFunction});
            this.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.SystemColors.WindowText;
            this.Location = new System.Drawing.Point(7, 103);
            this.Name = "frmDigAuxIn";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Universal Library Digital In (AUXPORT)";
            this.ResumeLayout(false);

        }

    #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() 
        {
            Application.Run(new frmDigAuxIn());
        }
        
        
        private void cmdEndProgram_Click(object eventSender, System.EventArgs eventArgs) /* Handles cmdEndProgram.Click */
        {
            Application.Exit();
        }


        private void tmrReadInputs_Tick(object eventSender, System.EventArgs eventArgs) /* Handles tmrReadInputs.Tick */
        {
            tmrReadInputs.Stop();

            ushort DataValue;
            MccDaq.ErrorInfo ULStat = DaqBoard.DIn( PortNum, out DataValue);

            lblPortVal.Text = "Value read at auxillary digital inputs:";
            lblShowPortVal.Text = DataValue.ToString("0");
          
            tmrReadInputs.Start();
        }

    }
}