/*********************************************************************
*
* Example program: 
*    9513eventCount.c
*
* Description: 
*    Counts the number of digital pulses (or events) going into the
*     clock input of counter 1 in a loop (for devices with the Am9513
*     counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT
*
* List of key parameters: 
*    iCtr, iEdgeMode, iTimeBase
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    CTR_Config, NIDAQErrorHandler, CTR_EvCount, CTR_EvRead,
*     NIDAQDelay, NIDAQYield, CTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse train to the SOURCE1 pin. Connect the
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
    i16 iTimeBase = 6;
    i16 iCont = 0;
    i16 iNumReads = 10;
    i16 iLoopCount = 0;
    i16 iOverFlow = 0;
    u16 uCount = 0;
    i16 iIgnoreWarnings = 0;
    i16 iYieldON = 1;

    /* Setup counter for counting rising edges (no gating). */

    iStatus = CTR_Config(iDevice, iCtr, iEdgeMode, iGateMode,
     iOutType, iOutPolarity);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Config",
     iIgnoreWarnings);

    /* Setup counter to do event counting from SOURCE1, and don't
     allow rollovers. */

    iStatus = CTR_EvCount(iDevice, iCtr, iTimeBase, iCont);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_EvCount",
     iIgnoreWarnings);

    while ((iLoopCount < iNumReads) && (iStatus == 0)) {


        iStatus = CTR_EvRead(iDevice, iCtr, &iOverFlow, &uCount);
        

        if (iStatus == 0) {


            printf(" The reading from counter %d is %u\n", iCtr, uCount);

            ++iLoopCount;

            iRetVal = NIDAQDelay(1.0);

        }


        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "CTR_EvRead",
     iIgnoreWarnings);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counter to initial state. */

    iStatus = CTR_Reset(iDevice, iCtr, 0);


}

/* End of program */
