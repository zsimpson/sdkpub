/*********************************************************************
*
* Example program: 
*    STCgenerateSquareWave.c
*
* Description: 
*    Generates a 1kHz square wave (digital pulse train) using general
*     purpose counter 0 and an internal 100kHz timebase. (for devices
*     with the DAQ-STC counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PLSTRN
*
* List of key parameters: 
*    ulGpctrNum, ulGpctrOutput, ulLOWcount, ulHIGHcount
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, Select_Signal, NIDAQWaitForKey
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulse train will be on the OUT pin of your counter.
*     Connect the ground reference to the DIG GND pin.
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
    u32 ulGpctrOutput = ND_GPCTR0_OUTPUT;
    u32 ulLOWcount = 50;
    u32 ulHIGHcount = 50;
    i16 iIgnoreWarning = 0;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_PULSE_TRAIN_GNR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_100_KHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_COUNT_1,
     ulLOWcount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/COUNT1", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_COUNT_2,
     ulHIGHcount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning);

    /* To output a counter pulse, you must call Select_Signal. */

    iStatus = Select_Signal(iDevice, ulGpctrOutput, ulGpctrOutput,
     ND_LOW_TO_HIGH);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal/GpctrOutput",
     iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    printf(" Square wave generation started...\n");

    /* HINT: If you don't see pulses at GPCTR0_OUTPUT, check your
     connections. */

    printf(" Hit any key to stop.\n");

    iRetVal = NIDAQWaitForKey(0.0);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    /* Disconnect GPCTR0_OUTPUT. */

    /* Note that the following Select_Signal call will cause the
     output to be high impedance which will most likely bring the logic
     level HIGH if there is a pull-up resistor on this pin. (Check your
     hardware user manual.)  If you do not want this behavior, comment out
     the next line. */

    iStatus = Select_Signal(iDevice, ND_GPCTR0_OUTPUT, ND_NONE,
     ND_DONT_CARE);

    printf(" Square wave generation done!\n");


}

/* End of program */
