/*********************************************************************
*
* Example program: 
*    9513generateFreqOut.c
*
* Description: 
*    Generates a square wave (digital pulse train) with 1kHz frequency
*     (fixed 50% duty cycle) using the 4-bit frequency divider, FOUT,
*     and an internal timebase (for devices with the Am9513
*     counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PULSTRN, INTTIM
*
* List of key parameters: 
*    iModeON, iTimeBase, iDivision
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    CTR_FOUT_Config, NIDAQErrorHandler, NIDAQWaitForKey
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulse train will be on the FOUT (or FOUT1, if using
*     TIO-10) pin. Connect the ground reference to the DIG GND pin.
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
    i16 iFOUTport = 1;
    i16 iModeON = 1;
    i16 iModeOFF = 0;
    i16 iTimeBase = 4;
    i16 iDivision = 1;
    i16 iIgnoreWarnings = 0;

    /* Start FOUT square wave. */

    iStatus = CTR_FOUT_Config(iDevice, iFOUTport, iModeON, iTimeBase,
     iDivision);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_FOUT_Config",
     iIgnoreWarnings);

    printf(" Hit any key to stop the squarewave.\n");

    iRetVal = NIDAQWaitForKey(0.0);

    printf(" FOUT square wave generation done!\n");

    /* CLEANUP - Don't check for errors on purpose. */

    /* Turn off FOUT square wave. */

    iStatus = CTR_FOUT_Config(iDevice, iFOUTport, iModeOFF, iTimeBase,
     iDivision);


}

/* End of program */
