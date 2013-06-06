/*********************************************************************
*
* Example program: 
*    AOonePoint.c
*
* Description: 
*    Output one channel, one point at a time, immediately (first output
*     2.5 volts, then after a key press, 0 volts)
*
* Example Category: 
*    AO
*
* Example Task Types: 
*    1PT, 1CH, IMMED, INTTIM
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
*    NIDAQWaitForKey, AO_VWrite, NIDAQErrorHandler
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output signal will be available at AO channel 0. The
*     default analog output mode for the DAQ device will be used.
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
    i16 iChan = 0;
    f64 dVoltage1 = 2.5;
    f64 dVoltage2 = 0.0;
    i16 iIgnoreWarning = 0;

    /* For best results, look at the output with a scope. */

    /* First output 'dVoltage1' volts. */

    printf(" Hit any key to output %lf volts.\n", dVoltage1);

    iRetVal = NIDAQWaitForKey(0.0);

    iStatus = AO_VWrite(iDevice, iChan, dVoltage1);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_VWrite", iIgnoreWarning);
    

    /* Then output 'dVoltage2' volts. */

    printf(" Hit any key to output %lf volts.\n", dVoltage2);

    iRetVal = NIDAQWaitForKey(0.0);

    iStatus = AO_VWrite(iDevice, iChan, dVoltage2);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_VWrite", iIgnoreWarning);
    


}

/* End of program */
