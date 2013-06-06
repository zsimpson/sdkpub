/*********************************************************************
*
* Example program: 
*    9513generateSinglePulse.c
*
* Description: 
*    Generates a single digital pulse 1 ms LOW and 100 ms HIGH using
*     counter 1 and an internal timebase (for devices with the Am9513
*     counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PULSTRN, INTTIM
*
* List of key parameters: 
*    iOutType, iTimeBase, uDelay, uPulseWidth
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    CTR_Config, NIDAQErrorHandler, CTR_Pulse, NIDAQDelay, CTR_State,
*     NIDAQYield, CTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulse will be on the OUT1 pin. Connect the ground
*     reference to the DIG GND pin.
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
    i16 iCtr = 1;
    i16 iEdgeMode = 0;
    i16 iGateMode = 0;
    i16 iOutType = 0;
    i16 iOutPolarity = 0;
    i16 iTimeBase = 3;
    u16 uDelay = 10;
    u16 uPulseWidth = 1000;
    i16 iOutState = 1;
    i16 iIgnoreWarnings = 0;
    i16 iYieldON = 1;

    /* Setup counter for counting rising edges with no gating. */

    iStatus = CTR_Config(iDevice, iCtr, iEdgeMode, iGateMode,
     iOutType, iOutPolarity);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Config",
     iIgnoreWarnings);

    /* Output a 1 sec logic HIGH pulse from counter. */

    iStatus = CTR_Pulse(iDevice, iCtr, iTimeBase, uDelay,
     uPulseWidth);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Pulse",
     iIgnoreWarnings);

    /* The delay here is to ensure that the first time CTR_State is
     called, it will sense a HIGH state. Some faster computers may get to
     the CTR_State call while the output pulse is still low. */

    iRetVal = NIDAQDelay(0.05);

    printf(" Wait until the output of counter goes LOW.\n");

    while ((iOutState != 0) && (iStatus == 0)) {


        iStatus = CTR_State(iDevice, iCtr, &iOutState);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "CTR_State",
     iIgnoreWarnings);

    printf(" The counter pulse has been generated.\n");

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counter to initial state. */

    iStatus = CTR_Reset(iDevice, iCtr, 0);


}

/* End of program */
