/*********************************************************************
*
* Example program: 
*    8253generateSquareWave.c
*
* Description: 
*    Generates a square wave (digital pulse train) from counter 0 (for
*     devices with the 8253 interval counter/timer)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PLSTRN
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
*    ICTR_Setup, NIDAQWaitForKey, ICTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulse train will be on the OUT0 or OUTB0 pin. Connect
*     the ground reference to the DIG GND pin. You can "gate" the pulse
*     train off if you connect a digital logic LOW signal to the GATE0
*     or GATB0 pin. NOTE: not all devices with the 8253 have a counter
*     0.
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
    i16 iCtr = 0;
    i16 iMode = 3;
    u16 uCount = 1000;
    i16 iBinBCD = 1;
    i16 iIgnoreWarnings = 0;

    /* Setup the counter for mode 3 - rate generator. Since counter 0
     has an internal timebase connected (either 1MHz or 2MHz depending on
     device), this will produce a square wave of the timebase divided by
     'uCount'. */

    iStatus = ICTR_Setup(iDevice, iCtr, iMode, uCount, iBinBCD);

    /* The square wave will be going on until either you reset the
     counter or unload the NI-DAQ library.  To reset the counter, call
     ICTR_Reset. */

    printf(" Hit any key to stop the squarewave.\n");

    iRetVal = NIDAQWaitForKey(0.0);

    printf(" Square wave generation done!\n");

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counter to initial state. */

    iStatus = ICTR_Reset(iDevice, iCtr, 0);


}

/* End of program */
