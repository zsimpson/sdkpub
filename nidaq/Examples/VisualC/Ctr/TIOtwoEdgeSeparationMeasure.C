/*********************************************************************
*
* Example program: 
*    TIOtwoEdgeSeparationMeasure.c
*
* Description: 
*    Counts the number of digital pulses (or events) between two
*     independent gate pulses (gate and auxiliary line) using an
*     internal 100kHz timebase (for NI-TIO based devices)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulCount, ulArmed, ulTCReached
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, GPCTR_Watch, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital START pulse to the default AUXILIARY line
*     (PFI 37 for 660x devices) and your digital STOP pulse to default
*     GATE pin (PFI 38 for 660x devices). Connect the ground reference
*     to the DIG GND pin.
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
    u32 ulGpctrNum = ND_COUNTER_0;
    u32 ulCount = 0;
    i16 iLoopCount = 10;
    u32 ulInitCount = 0;
    u32 ulArmed = ND_YES;
    u32 ulTCReached = ND_NO;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    /* Setup for a two-signal (non-buffered) edge separation
     measurement application. */

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_TWO_SIGNAL_EDGE_SEPARATION_MSR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    /* If you want to use a different GPCTR source, change the last
     parameter in the following function. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_100_KHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    /* Setup the START pulse input.  You must change the last
     parameter if you use a counter other than 0. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_AUX_LINE,
     ND_PFI_37);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/AUXLINE", iIgnoreWarning);

    /* Setup the STOP pulse input. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ND_DEFAULT_PFI_LINE);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulInitCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    printf(" Apply your digital START pulse to PFI 37.\n");

    printf(" And then apply your digital STOP pulse to PFI 38.\n");

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    /* Loop until 'ulGpctrNum' is no longer armed. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_ARMED,
         &ulArmed);

        iRetVal = NIDAQYield(iYieldON);

    } while ((ulArmed == ND_YES) && (iStatus == 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/ARMED",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_COUNT, &ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/COUNT",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_TC_REACHED,
     &ulTCReached);

    if (ulTCReached == ND_YES) {


        printf(" Counter reached terminal count! - The count may be incorrect.\n");

    }
    else {

        printf(" The period in between the two gate pulses (in 10uSec ticks) was %lu\n", ulCount);

    }


    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);


}

/* End of program */
