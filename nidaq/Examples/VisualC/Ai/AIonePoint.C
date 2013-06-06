/*********************************************************************
*
* Example program: 
*    AIonePoint.c
*
* Description: 
*    Read one channel, one point at a time, immediately
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    1PT, 1CH, IMMED
*
* List of key parameters: 
*    iChan
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    AI_VRead, NIDAQErrorHandler
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signal to AI channel 1. The default analog
*     input mode for the DAQ device will be used.
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
    i16 iIgnoreWarning = 0;

    iStatus = AI_VRead(iDevice, iChan, iGain, &dVoltage);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_VRead", iIgnoreWarning);
    

    if (iStatus == 0) {


        printf(" The voltage at AI channel %d is %lf volts.\n", iChan, dVoltage);

    }



}

/* End of program */
