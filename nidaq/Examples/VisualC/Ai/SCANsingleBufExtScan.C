/*********************************************************************
*
* Example program: 
*    SCANsingleBufExtScan.c
*
* Description: 
*    Read a waveform from two analog input channels using external scan
*     interval timing but with internal sample timing (uses low-level
*     NI-DAQ functions)
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    BUF, NCH, BURST, EXTTIM, ASYNC, INTTRIG
*
* List of key parameters: 
*    iExtScan, iScanTB, uScanInt
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DAQ_Config, NIDAQErrorHandler, DAQ_Rate, SCAN_Setup, SCAN_Start,
*     DAQ_Check, NIDAQYield, SCAN_Demux, DAQ_VScale, DAQ_Clear,
*     NIDAQPlotWaveform
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signals to AI channels 1 and 2. The default
*     analog input mode for the DAQ device will be used. Also, connect
*     a digital pulse train to the 'external scan clock' pin. (NOTE:
*     This is NOT the pin labelled "SCANCLK" but instead is a counter
*     output pin.)
*
*    [For further I/O connection details, please refer to your hardware
*     User Manual.]
*
*    [For further details on how to run this example, please refer to
*     the NI-DAQ Examples On-Line Help (NIDAQEx.HLP).]
*
*********************************************************************/
/*
 * Includes: 
 */

#include "nidaqex.h"


/*
 * Main: 
 */

void main(void)
{
    /*
     * Local Variable Declarations: 
     */

    i16 iStatus = 0;
    i16 iRetVal = 0;
    i16 iDevice = 1;
    i16 iChan = 1;
    i16 iStartTrig = 0;
    i16 iExtScan = 2;
    i16 iGain = 1;
    f64 dSampRate = 1000.0;
    u32 ulCount = 200;
    f64 dGainAdjust = 1.0;
    f64 dOffset = 0.0;
    i16 iUnits = 0;
    i16 iSampTB = 0;
    u16 uSampInt = 0;
    i16 iScanTB = 0;
    u16 uScanInt = 0;
    static i16 piBuffer[200] = {0};
    static f64 pdVoltBuffer[200] = {0.0};
    i16 iDAQstopped = 0;
    u32 ulRetrieved = 0;
    i16 iNumChans = 2;
    static i16 piChanVect[2] = {1, 2};
    static i16 piGainVect[2] = {1, 1};
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    /* Setup for external scan timing with iExtScan = 2. */

    iStatus = DAQ_Config(iDevice, iStartTrig, iExtScan);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Config",
     iIgnoreWarning);

    /* Convert sample rate (S/sec) to appropriate timebase and sample
     interval values. (NOT scan interval values) */

    iStatus = DAQ_Rate(dSampRate, iUnits, &iSampTB, &uSampInt);

    iStatus = SCAN_Setup(iDevice, iNumChans, piChanVect, piGainVect);
    

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Setup",
     iIgnoreWarning);

    /* Acquire data */

    iStatus = SCAN_Start(iDevice, piBuffer, ulCount, iSampTB,
     uSampInt, iScanTB, uScanInt);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Start",
     iIgnoreWarning);

    printf(" Apply your external scan timing pulses to the 'external scan clock' pin.\n");

    while ((iDAQstopped != 1) && (iStatus == 0)) {


        /* Loop until all acquisition is complete.  HINT: You can be
         doing other foreground tasks during this time. */

        iStatus = DAQ_Check(iDevice, &iDAQstopped, &ulRetrieved);
        

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Check", iIgnoreWarning);
    

    iStatus = SCAN_Demux(piBuffer, ulCount, iNumChans, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Demux",
     iIgnoreWarning);

    iStatus = DAQ_VScale(iDevice, iChan, iGain, dGainAdjust, dOffset,
     ulCount, piBuffer, pdVoltBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale",
     iIgnoreWarning);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Set scan timing back to initial state. */

    iStatus = DAQ_Config(iDevice, 0, 0);

    iStatus = DAQ_Clear(iDevice);

    printf(" The plot shows Channel 1 data then Channel 2 data.\n");

    /* Plot acquired data */

    iRetVal = NIDAQPlotWaveform(pdVoltBuffer, ulCount, WFM_DATA_F64);
    

    printf(" The data is available in 'pdVoltBuffer'.\n");


}

/* End of program */
