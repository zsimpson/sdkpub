/*********************************************************************
*
* Example program: 
*    TIOeventCountWithPrescaling.c
*
* Description: 
*    Counts the number of digital pulses (or events) using a general
*     purpose counter 0 in a loop while using prescaling.  This is
*     useful for counting signals with frequencies faster than the
*     maximum internal timebase. (for NI-TIO based devices)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulLineNum, ulCount, ulPrescale
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Watch, GPCTR_Change_Parameter, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse train to the default source pin (PFI
*     39). Connect the ground reference to the DIG GND pin.
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
    u32 ulLineNum = ND_PFI_39;
    u32 ulCount = 0;
    u32 ulPrescale = 0;
    i32 ulTCReached = ND_NO;
    u32 iLoopCount = 100;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    /* Setup for a simple event counting application. */

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_SIMPLE_EVENT_CNT);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    /* Get the counter's maximum prescaling factor. */

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_MAX_PRESCALE,
     &ulPrescale);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/PRESCALE",
     iIgnoreWarning);

    /* Setup the counter's prescaling factor. Besides the max prescale
     factor, you can also use 1 and 2. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_PRESCALE_VALUE, ulPrescale);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/PRESCALE", iIgnoreWarning);

    /* Specify the source input. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ulLineNum);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    printf(" Apply your digital pulse train to PFI 39.\n");

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    /* Loop 100 times. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_COUNT,
         &ulCount);

        iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/COUNT",
         iIgnoreWarning);

        printf(" The current count is %lu x %lu\n", ulCount, ulPrescale);

        --iLoopCount;

        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_TC_REACHED,
         &ulTCReached);

        if (ulTCReached == ND_YES) {


            printf(" Counter reached terminal count! - The count may be incorrect.\n");

        }


        iRetVal = NIDAQYield(iYieldON);

    } while ((iLoopCount > 0) && (iStatus == 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch",
     iIgnoreWarning);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    printf(" Done with event counting with prescaling!!\n");


}

/* End of program */
