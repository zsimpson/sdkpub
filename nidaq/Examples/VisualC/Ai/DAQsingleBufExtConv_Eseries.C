/*********************************************************************
*
* Example program: 
*    DAQsingleBufExtConv_Eseries.c
*
* Description: 
*    Read a waveform from one analog input channel using external
*     sample timing (uses low-level NI-DAQ functions, for E-series
*     devices)
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    BUF, 1CH, BURST, EXTTIM, ASYNC, INTTRIG, ESER
*
* List of key parameters: 
*    iExtConv, iSampTB
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Select_Signal, NIDAQErrorHandler, DAQ_Config, DAQ_Start,
*     DAQ_Check, NIDAQYield, DAQ_VScale, DAQ_Clear, NIDAQPlotWaveform
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signal to AI channel 1. The default analog
*     input mode for the DAQ device will be used. Also, connect a
*     digital pulse (falling edge) to the PFI2/CONVERT* pin.
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
    i16 iExtConv = 1;
    i16 iGain = 1;
    u32 ulCount = 100;
    f64 dGainAdjust = 1.0;
    f64 dOffset = 0.0;
    i16 iSampTB = 0;
    u16 uSampInt = 0;
    static i16 piBuffer[100] = {0};
    static f64 pdVoltBuffer[100] = {0.0};
    i16 iDAQstopped = 0;
    u32 ulRetrieved = 0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    /* Setup for external conversions into PFI2 with iExtConv = 1. */
    

    iStatus = Select_Signal(iDevice, ND_IN_CONVERT, ND_PFI_2,
     ND_HIGH_TO_LOW);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal",
     iIgnoreWarning);

    iStatus = DAQ_Config(iDevice, iStartTrig, iExtConv);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Config",
     iIgnoreWarning);

    /* Instead of calling DAQ_Rate, let iSampTB be 0. */

    /* Acquire data from a single channel */

    iStatus = DAQ_Start(iDevice, iChan, iGain, piBuffer, ulCount,
     iSampTB, uSampInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Start", iIgnoreWarning);
    

    printf(" Apply your external conversion clock signal to PFI2.\n");

    while ((iDAQstopped != 1) && (iStatus == 0)) {


        /* Loop until all acquisition is complete.  HINT: You can be
         doing other foreground tasks during this time. */

        iStatus = DAQ_Check(iDevice, &iDAQstopped, &ulRetrieved);
        

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Check", iIgnoreWarning);
    

    iStatus = DAQ_VScale(iDevice, iChan, iGain, dGainAdjust, dOffset,
     ulCount, piBuffer, pdVoltBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale",
     iIgnoreWarning);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Set sample timing back to initial state. */

    iStatus = DAQ_Config(iDevice, 0, 0);

    /* Set PFI line back to initial state. */

    iStatus = Select_Signal(iDevice, ND_IN_CONVERT, ND_INTERNAL_TIMER,
     ND_LOW_TO_HIGH);

    DAQ_Clear(iDevice);

    /* Plot acquired data */

    iRetVal = NIDAQPlotWaveform(pdVoltBuffer, ulCount, WFM_DATA_F64);
    

    printf(" The data is available in 'pdVoltBuffer'.\n");


}

/* End of program */
