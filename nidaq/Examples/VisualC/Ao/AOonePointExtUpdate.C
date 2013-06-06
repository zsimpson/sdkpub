/*********************************************************************
*
* Example program: 
*    AOonePointExtUpdate.c
*
* Description: 
*    Output one channel from one analog output channel, using external
*     timing
*
* Example Category: 
*    AO
*
* Example Task Types: 
*    1PT, 1CH, EXTTIM
*
* List of key parameters: 
*    iUpdateModeEXT
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    AO_VWrite, AO_Configure, NIDAQErrorHandler, NIDAQWaitForKey
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output signal will be available at AO channel 0. The
*     default analog output mode for the DAQ device will be used. Also,
*     connect a digital pulse to the 'external update' pin.
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
    i16 iOutputPolarity = 0;
    i16 iIntOrExtRef = 0;
    i16 iUpdateModeEXT = 2;
    i16 iUpdateModeINT = 0;
    f64 dRefVolts = 10.0;
    f64 dVoltage = 2.5;
    i16 iIgnoreWarning = 0;

    /* For best results, look at the output with a scope. */

    /* Set output at 0 volts. */

    iStatus = AO_VWrite(iDevice, iChan, 0.0);

    /* Configure for bipolar mode, internal reference, and external
     updates. (The 'dRefVolts' is ignored since this is internally
     referenced.) */

    iStatus = AO_Configure(iDevice, iChan, iOutputPolarity,
     iIntOrExtRef, dRefVolts, iUpdateModeEXT);

    iRetVal = NIDAQErrorHandler(iStatus,
     "AO_Configure/ExternalUpdate", iIgnoreWarning);

    printf(" Apply the 'external update' pulse to output %lf volts and hit any key.\n", dVoltage);

    iStatus = AO_VWrite(iDevice, iChan, dVoltage);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_VWrite", iIgnoreWarning);
    

    iRetVal = NIDAQWaitForKey(0.0);

    printf(" Did you see the voltage appear on analog output channel %d ?\n", iChan);

    /* Don't check for errors on purose. */

    /* Set update mode back to initial state. */

    iStatus = AO_Configure(iDevice, iChan, iOutputPolarity,
     iIntOrExtRef, dRefVolts, iUpdateModeINT);


}

/* End of program */
