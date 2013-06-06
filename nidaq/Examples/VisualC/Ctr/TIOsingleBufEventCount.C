/*********************************************************************
*
* Example program: 
*    TIOsingleBufEventCount.c
*
* Description: 
*    Counts the number of digital pulses (or events) in between gate
*     pulses into a single buffer using general purpose counter 0 (for
*     NI-TIO based devices)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT, BURST, INTTIM, BUF
*
* List of key parameters: 
*    ulGpctrNum, pulBuffer, ulCount, ulArmed, iGateFasterThanSource
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, GPCTR_Config_Buffer, GPCTR_Watch,
*     NIDAQYield, GPCTR_Read_Buffer
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse train to the GATE pin of your counter.
*     (PFI 38 for 660x devices) Connect the ground reference to the DIG
*     GND pin.
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
    static u32 pulBuffer[100] = {0};
    u32 ulCount = 100;
    u32 ulInitCount = 0;
    u32 ulArmed = ND_YES;
    i16 iGateFasterThanSource = 0;
    u32 ulNumPtsToRead = 100;
    u32 ulNumPtsRead = 0;
    u32 ulReadOffset = 0;
    u32 ulTimeOut = 5;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    /* Set up for a buffered event counting application. */

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_BUFFERED_EVENT_CNT);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    /* If you want to use a different GPCTR source, change the last
     parameter in the following function. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_100_KHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    /* Each time a pulse arrives in the gate, a new value will be
     latched into the counter and sent to the data buffer. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ND_DEFAULT_PFI_LINE);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulInitCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    /* Enable single-buffer mode. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_BUFFER_MODE, ND_SINGLE);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/BUFFERMODE", iIgnoreWarning);

    /* Turn on synchronous counting mode if gate is faster than
     source. */

    if (iGateFasterThanSource == 1) {


        iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
         ND_COUNTING_SYNCHRONOUS, ND_YES);

        iRetVal = NIDAQErrorHandler(iStatus,
         "GPCTR_Change_Parameter/SYNCHRONOUS COUNTING", iIgnoreWarning);
        

    }


    iStatus = GPCTR_Config_Buffer(iDevice, ulGpctrNum, 0, ulCount,
     pulBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Config_Buffer",
     iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    printf(" Apply your gating pulse train to the GATE of your counter now.\n");

    /* Loop until counter is no longer armed. */

    /* WARNING... Do NOT watch for ND_COUNT during a buffered
     operation. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_ARMED,
         &ulArmed);

        iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/ARMED",
         iIgnoreWarning);

        iRetVal = NIDAQYield(iYieldON);

    } while ((ulArmed == ND_YES) && (iStatus == 0));


    /* After the counter is unarmed, read the buffer from the
     beginning. */

    iStatus = GPCTR_Read_Buffer(iDevice, ulGpctrNum, ND_BUFFER_START,
     ulReadOffset, ulNumPtsToRead, ulTimeOut, &ulNumPtsRead, pulBuffer);
    

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Read_Buffer",
     iIgnoreWarning);

    printf(" %lu points read into buffer 'pulBuffer'.\n", ulNumPtsRead);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    printf(" GPCTR single buffered event counting done!\n");


}

/* End of program */
