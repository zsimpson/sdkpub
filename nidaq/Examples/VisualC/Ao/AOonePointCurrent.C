/*********************************************************************
*
* Example program: 
*    AOonePointCurrent.c
*
* Description: 
*    Output one channel, one current value point at a time, immediately
*     (first output 5mA then 0A)
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
*    AO_Change_Parameter, NIDAQErrorHandler, NIDAQWaitForKey, AO_VWrite
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output current signal will be available at AO current
*     channel 0.  Please note that on some devices, the current output
*     and the voltage output may be on different I/O connector pins.
*     Also, some devices may require an external power source to drive
*     the current.
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
    f64 dCurrent1 = 5.0;
    f64 dCurrent2 = 0.0;
    i16 iIgnoreWarning = 0;

    /* IMPORTANT... For the 6704 devices, set 'iChan' to any channel
     between 16 and 31. For the VXI-AO-48XDC, set 'iChan' to any channel
     between 0 and 47. Please refer to the hardware user manual for more
     information. */

    /* Change output type to current. */

    iStatus = AO_Change_Parameter(iDevice, iChan, ND_OUTPUT_TYPE,
     ND_CURRENT_OUTPUT);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_Change_Parameter",
     iIgnoreWarning);

    /* For best results, look at the output with an ammeter. */

    /* First output 'dCurrent1' mA. */

    printf(" Hit any key to output %lf mA.\n", dCurrent1);

    iRetVal = NIDAQWaitForKey(0.0);

    /* For AO-2DC devices, the current value must be in units of Amps,
     and for AO-6/10 devices, the current value must be the voltage value
     that will produce the desired current (given the external supply and
     shunt resistor). */

    iStatus = AO_VWrite(iDevice, iChan, dCurrent1);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_VWrite", iIgnoreWarning);
    

    /* Then output 'dCurrent2' mA. */

    printf(" Hit any key to output %lf mA.\n", dCurrent2);

    iRetVal = NIDAQWaitForKey(0.0);

    iStatus = AO_VWrite(iDevice, iChan, dCurrent2);

    iRetVal = NIDAQErrorHandler(iStatus, "AO_VWrite", iIgnoreWarning);
    

    /* Change output type back to voltage. (Ignore errors) */

    iStatus = AO_Change_Parameter(iDevice, iChan, ND_OUTPUT_TYPE,
     ND_VOLTAGE_OUTPUT);


}

/* End of program */
