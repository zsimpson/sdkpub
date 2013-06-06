/*********************************************************************
*
* Example program: 
*    AIonePointExtConv_Eseries.c
*
* Description: 
*    Read one channel, one point at a time, using external timing (for
*     E-series devices)
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    1PT, 1CH, EXTTIM, ESER
*
* List of key parameters: 
*    iChan, iReadingAvail
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    AI_Clear, NIDAQErrorHandler, Select_Signal, AI_Setup, AI_Check,
*     NIDAQYield, AI_VScale
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
    i16 iGain = 1;
    f64 dVoltage = 0.0;
    i16 iReadingAvail = 0;
    i16 iReading = 0;
    f64 dGainAdjust = 1.0;
    f64 dOffset = 0.0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    /* This clears the AI FIFO. */

    iStatus = AI_Clear(iDevice);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_Clear", iIgnoreWarning);
    

    iStatus = Select_Signal(iDevice, ND_IN_CONVERT, ND_PFI_2,
     ND_HIGH_TO_LOW);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal",
     iIgnoreWarning);

    /* Setup for external conversions. */

    iStatus = AI_Setup(iDevice, iChan, iGain);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_Setup", iIgnoreWarning);
    

    printf(" Apply a pulse to the 'external conversion' pin when ready to read a voltage.\n");

    while ((iReadingAvail != 1) && (iStatus == 0)) {


        /* Wait until reading is available. */

        iStatus = AI_Check(iDevice, &iReadingAvail, &iReading);
        

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "AI_Check", iIgnoreWarning);
    

    iStatus = AI_VScale(iDevice, iChan, iGain, dGainAdjust, dOffset,
     iReading, &dVoltage);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_VScale", iIgnoreWarning);
    

    /* Set PFI line back to initial state. */

    iStatus = Select_Signal(iDevice, ND_IN_CONVERT, ND_INTERNAL_TIMER,
     ND_LOW_TO_HIGH);

    printf(" The voltage at AI channel %d is %lf volts.\n", iChan, dVoltage);


}

/* End of program */
