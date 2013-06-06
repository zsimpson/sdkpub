/*********************************************************************
*
* Example program: 
*    STCsinglePulseWidthMeasure.c
*
* Description: 
*    Measures the pulse width of a single digital pulse using general
*     purpose counter 0 (for devices with the DAQ-STC counter/timer.)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PLSWM, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulCount, ulArmed
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
*    Connect your single digital pulse signal to the GATE pin of your
*     counter. Connect the ground reference to the DIG GND pin.
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
    u32 ulArmed = ND_YES;
    u32 ulTCReached = ND_NO;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    /* NOTE: The ND_SINGLE_PULSE_WIDTH_MSR application should be used
     in the context of a single pulse. The GPCTR_Program function requires
     the starting state of the pulse to be expected, or else you will get
     a 'gateSignalError'. For more information, see the description of
     GPCTR_Set_Application under the ND_SINGLE_PULSE_WIDTH_MSR appliation.
     */

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_SINGLE_PULSE_WIDTH_MSR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_100_KHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ND_DEFAULT_PFI_LINE);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    printf(" Apply your digital pulse to the GATE of the counter now.\n");

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    /* Loop until 'ulGpctrNum' is no longer armed. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_ARMED,
         &ulArmed);

        iRetVal = NIDAQYield(iYieldON);

    } while ((ulArmed == ND_YES) && (iStatus == 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/ND_ARMED",
     iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_DISARM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/DISARM",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_COUNT, &ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/COUNT",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_TC_REACHED,
     &ulTCReached);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/TC_REACHED",
     iIgnoreWarning);

    if (ulTCReached == ND_YES) {


        printf(" Counter reached terminal count! - The count may be incorrect.\n");

    }
    else {

        printf(" The duration of the HIGH period in 10uSec ticks was %lu\n", ulCount);

    }


    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);


}

/* End of program */
