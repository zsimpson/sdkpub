/*********************************************************************
*
* Example program: 
*    9513generateSquareWave.c
*
* Description: 
*    Generates a square wave (digital pulse train) with 1kHz frequency
*     and 50% duty cycle using counter 1 and an internal timebase (for
*     devices with the Am9513 counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PULSTRN, INTTIM
*
* List of key parameters: 
*    iOutType, dFreq, dDutyCycle, iTimeBase, uPeriod1, uPeriod2
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    CTR_Config, NIDAQErrorHandler, CTR_Rate, CTR_Square,
*     NIDAQWaitForKey, CTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulse train will be on the OUT1 pin. Connect the
*     ground reference to the DIG GND pin.
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
    f64 dFreq = 1000.0;
    f64 dDutyCycle = 0.50;
    i16 iTimeBase = 0;
    u16 uPeriod1 = 0;
    u16 uPeriod2 = 0;
    i16 iIgnoreWarnings = 0;

    /* Setup counter for counting rising edges with no gating. */

    iStatus = CTR_Config(iDevice, iCtr, iEdgeMode, iGateMode,
     iOutType, iOutPolarity);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Config",
     iIgnoreWarnings);

    /* Determing timebase, period1 and period2. */

    iStatus = CTR_Rate(dFreq, dDutyCycle, &iTimeBase, &uPeriod1,
     &uPeriod2);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Rate", iIgnoreWarnings);
    

    /* Start square wave from counter. */

    iStatus = CTR_Square(iDevice, iCtr, iTimeBase, uPeriod1,
     uPeriod2);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Square",
     iIgnoreWarnings);

    printf(" Hit any key to stop the squarewave.\n");

    iRetVal = NIDAQWaitForKey(0.0);

    printf(" Square wave generation done!\n");

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counter to initial state. */

    iStatus = CTR_Reset(iDevice, iCtr, 0);


}

/* End of program */
