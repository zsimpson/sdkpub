/*********************************************************************
*
* Example program: 
*    8253eventCount.c
*
* Description: 
*    Counts the number of digital pulses (or events, Mode 0) going into
*     the clock input of counter 1, ten times (for devices with the
*     8253 interval counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT
*
* List of key parameters: 
*    iCtr, iMode
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    ICTR_Setup, NIDAQErrorHandler, ICTR_Read, NIDAQDelay, NIDAQYield,
*     ICTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse train to the CLK1 or CLKB1pin. Connect
*     the ground reference to the DIG GND pin. You can gate the count
*     if you connect a digital signal to GATE1 or GATB1.  A logic 'low'
*     would halt counting, and a logic 'high' would continue counting.
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
    i16 iMode = 0;
    u16 uCount = 0;
    i16 iBinBCD = 1;
    i16 iNumReads = 10;
    i16 iLoopCount = 0;
    i16 iIgnoreWarnings = 0;
    i16 iYieldON = 1;

    /* Setup the counter for mode 0. */

    iStatus = ICTR_Setup(iDevice, iCtr, iMode, uCount, iBinBCD);

    iRetVal = NIDAQErrorHandler(iStatus, "ICTR_Setup",
     iIgnoreWarnings);

    /* The counter doesn't load its count until the first clock pulse,
     so your first reading may be off. */

    while ((iLoopCount < iNumReads) && (iStatus == 0)) {


        iStatus = ICTR_Read(iDevice, iCtr, &uCount);

        if (iStatus == 0) {


            printf(" The reading from counter %d is %u\n", iCtr, uCount);

            ++iLoopCount;

            iRetVal = NIDAQDelay(1.0);

        }


        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "ICTR_Read",
     iIgnoreWarnings);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counter to initial state. */

    iStatus = ICTR_Reset(iDevice, iCtr, 0);


}

/* End of program */
