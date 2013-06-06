/*********************************************************************
*
* Example program: 
*    SCC_A10.c
*
* Description: 
*    Use the SCC-A10 module with an E-series device to measure a
*     voltage signal attenuated by a factor of 10. (Requires an SCC
*     carrier, such as the SC-2345, and the SCC-A10 signal conditioning
*     component)
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    BUF, 1CH, SYNC, INTTIM, ESER
*
* List of key parameters: 
*    lTimeout, iInputMode, iInputRange, iPolarity, dSampRate
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Timeout_Config, NIDAQErrorHandler, AI_Configure, DAQ_Op,
*     DAQ_VScale, NIDAQMean, NIDAQPlotWaveform
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect the signal to the SCC-A10 in the channel 0 slot.
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
    i32 lTimeout = 180;
    i16 iInputMode = 2;
    i16 iInputRange = 20;
    i16 iPolarity = 0;
    i16 iDriveAIS = 0;
    i16 iChan = 0;
    i16 iGain = 1;
    f64 dSampRate = 300.0;
    u32 ulCount = 30;
    f64 dGainAdjust = 1.0;
    f64 dOffset = 0.0;
    static i16 piBuffer[30] = {0};
    static f64 pdVoltBuffer[30] = {0.0};
    f64 dAvgVoltage = 0.0;
    i16 iIgnoreWarning = 0;

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the DAQ_Op call. */
    

    iStatus = Timeout_Config(iDevice, lTimeout);

    iRetVal = NIDAQErrorHandler(iStatus, "Timeout_Config",
     iIgnoreWarning);

    iStatus = AI_Configure(iDevice, iChan, iInputMode, iInputRange,
     iPolarity, iDriveAIS);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_Configure",
     iIgnoreWarning);

    /* Acquire data from a single channel. */

    iStatus = DAQ_Op(iDevice, iChan, iGain, piBuffer, ulCount,
     dSampRate);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Op", iIgnoreWarning);
    

    /* The attenuation on the SCC-A10 is compensated internally in
     DAQ_VScale, provided that you have configured your SCC-A10 in the
     NI-DAQ Configuration Utility. If you have not configured your SCC-A10
     in the NI-DAQ Configuration Utility, the scaled data will be off by a
     factor of 10. */

    iStatus = DAQ_VScale(iDevice, iChan, iGain, dGainAdjust, dOffset,
     ulCount, piBuffer, pdVoltBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale",
     iIgnoreWarning);

    iRetVal = NIDAQMean(pdVoltBuffer, ulCount, WFM_DATA_F64,
     &dAvgVoltage);

    printf(" The plot shows all channel data in order.\n");

    /* Plot acquired data */

    iRetVal = NIDAQPlotWaveform(pdVoltBuffer, ulCount, WFM_DATA_F64);
    

    printf(" The average voltage reading is %lf V.\n", dAvgVoltage);

    /* Disable timeouts. */

    iStatus = Timeout_Config(iDevice, -1);


}

/* End of program */
