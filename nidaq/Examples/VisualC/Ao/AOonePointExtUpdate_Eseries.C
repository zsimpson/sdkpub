/*********************************************************************
*
* Example program: 
*    AOonePointExtUpdate_Eseries.c
*
* Description: 
*    Output one channel, one point at a time, using external timing
*     (for E-series devices)
*
* Example Category: 
*    AO
*
* Example Task Types: 
*    1PT, 1CH, EXTTIM, ESER
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
*    AO_VWrite, AO_Configure, NIDAQErrorHandler, Select_Signal,
*     NIDAQWaitForKey
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output signal will be available at AO channel 0. The
*     default analog output mode for the DAQ device will be used. Also,
*     connect a digital pulse to the PFI5/UPDATE* pin.
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

    /* Setup PFI line for external updates. (PFI5 is setup by default
     with AO_Configure.) */

    iStatus = Select_Signal(iDevice, ND_OUT_UPDATE, ND_PFI_5,
     ND_HIGH_TO_LOW);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal",
     iIgnoreWarning);

    printf(" Apply the 'external update' pulse to output %lf volts and hit any key.\n", dVoltage);

    iStatus = AO_VWrite(iDevice, iChan, dVoltage);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_VWrite", iIgnoreWarning);
    

    iRetVal = NIDAQWaitForKey(0.0);

    printf(" Did you see the voltage appear on analog output channel %d ?\n", iChan);

    /* Don't check for errors on purose. */

    /* Set update mode back to initial state. */

    iStatus = AO_Configure(iDevice, iChan, iOutputPolarity,
     iIntOrExtRef, dRefVolts, iUpdateModeINT);

    /* Set PFI line back to initial state. */

    iStatus = Select_Signal(iDevice, ND_OUT_UPDATE, ND_INTERNAL_TIMER,
     ND_LOW_TO_HIGH);


}

/* End of program */
