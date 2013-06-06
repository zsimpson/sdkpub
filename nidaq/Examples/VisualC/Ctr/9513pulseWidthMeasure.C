/*********************************************************************
*
* Example program: 
*    9513pulseWidthMeasure.c
*
* Description: 
*    Measures the width of a single digital pulse using counter 1 and a
*     1MHz internal timebase (for devices with the Am9513
*     counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PLSWM, INTTIM
*
* List of key parameters: 
*    iCtr, iGateMode, iTimeBase
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    CTR_Config, NIDAQErrorHandler, CTR_Period, NIDAQDelay, CTR_EvRead,
*     CTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse to the GATE1 pin. Connect the ground
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
    i16 iGateMode = 1;
    i16 iOutType = 0;
    i16 iOutPolarity = 0;
    i16 iTimeBase = 1;
    i16 iOverFlow = 0;
    u16 uCount = 0;
    i16 iIgnoreWarnings = 0;

    /* Setup counter for counting rising edges with level-HIGH gating.
     */

    iStatus = CTR_Config(iDevice, iCtr, iEdgeMode, iGateMode,
     iOutType, iOutPolarity);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Config",
     iIgnoreWarnings);

    /* Setup counter to do period/pulse-width measurement using
     internal 1MHz timebase. */

    iStatus = CTR_Period(iDevice, iCtr, iTimeBase);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Period",
     iIgnoreWarnings);

    printf(" Wait 1 sec before reading the count value.\n");

    iRetVal = NIDAQDelay(1.0);

    iStatus = CTR_EvRead(iDevice, iCtr, &iOverFlow, &uCount);

    if ((uCount >= 3) && (iStatus == 0)) {


        printf(" The gate pulse was %u uSec long.\n", uCount);

    }
    else if (iOverFlow == 1) {


        printf(" An overflow occured. You may want to slow down the timebase or your gate pulse.\n");

    }
    else {

        /* 'uCount' must be greater than 3 for valid count. the count
         corresponds to the number of microsecond ticks read by the counter
         while the gate was high. */

        printf(" WARNING- The counter was read prematurely.\n");

    }


    iRetVal = NIDAQErrorHandler(iStatus, "CTR_EvRead",
     iIgnoreWarnings);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counter to initial state. */

    iStatus = CTR_Reset(iDevice, iCtr, 0);


}

/* End of program */
