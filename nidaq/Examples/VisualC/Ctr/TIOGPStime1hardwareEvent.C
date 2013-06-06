/*********************************************************************
*
* Example program: 
*    TIOGPStime1hardwareEvent.c
*
* Description: 
*    This example measures time, using a real time clock found in the
*     6608 timing devices.  By default, the real time clock increments
*     based upon the internal 20 Mhz clock.  Also, the real time clock
*     can be synchronized by a IRIG-B (TTL standards B000, B001, B002,
*     and B003 only) or a pulse per second (PPS) signal by attaching
*     the synchronization signal to the synchronization line of the
*     real time clock.The current time of the real time clock is read
*     upon a hardware signal on the gate pin.
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    TIMING
*
* List of key parameters: 
*    iDevice, ulGpctrNum, ulGpctrSynchronizationLine, ulGpctrGate,
*     ulInitialSeconds, ulSeconds, ulNanoSeconds
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, NIDAQDelay, GPCTR_Watch
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect the ground reference to the 'digital ground' pin. Apply
*     the GATE signal to PFI 7.  Apply the synchronization source to
*     PFI 6.
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
    u32 ulGpctrNum = ND_CLOCK_0;
    u32 ulGpctrSynchronizationLine = ND_PFI_6;
    u32 ulGpctrGate = ND_PFI_7;
    u32 ulInitialSeconds = 0;
    i16 iIgnoreWarning = 0;
    u32 ulSeconds = 0;
    u32 ulNanoSeconds = 0;
    u32 ulArmed = ND_YES;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_SINGLE_TIME_MSR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    /* To use a different GPCTR gate, change the ulGpctrGate variable
     in the variable declarations. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ulGpctrGate);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    /* To change the synchronization line, change the
     ulGpctrSynchronizationLine variable in the variable declarations. */
    

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_SYNCHRONIZATION_LINE, ulGpctrSynchronizationLine);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SYNCHRONIZATION", iIgnoreWarning);

    /* To use a different GPCTR synchronization method, change the
     last parameter in the following function. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_SYNCHRONIZATION_METHOD, ND_IRIG_B);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SYNCHRONIZATION_METHOD", iIgnoreWarning);

    /* To use the time previously stored in the real time clock,
     change the ND_INITIAL_SECONDS_ENABLE parameter to ND_NO */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_SECONDS_ENABLE, ND_YES);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITIAL_SECONDS_ENABLE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_SECONDS, ulInitialSeconds);

    /* NOTE - It is only necessary to program the initial seconds if
     you are not using IRIG synchronization. In the IRIG synchronization
     case the real time clock will recieve its time information from the
     data stream. */

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITIAL_SECONDS", iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    /* Delay for two seconds to ensure the clock is synchronized. */
    

    NIDAQDelay(2);

    printf(" Time 1 Hardware Event started...\n");

    printf(" Apply your gating pulse to PFI 7 now.\n");

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_ARMED,
         &ulArmed);

        iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/ARMED",
         iIgnoreWarning);

    } while ((ulArmed == ND_YES) && (iStatus == 0));


    /* print the resulting time */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_SNAPSHOT);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/SNAPSHOT",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_SECONDS,
     &ulSeconds);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/SECONDS",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_NANO_SECONDS,
     &ulNanoSeconds);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/NANO_SECONDS",
     iIgnoreWarning);

    printf(" Hardware trigger occurred at time %lu seconds and %lu nanoseconds.\n", ulSeconds, ulNanoSeconds);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    printf(" Time 1 Event with Hardware Precision done!\n");


}

/* End of program */
