/*********************************************************************
*
* Example program: 
*    9513freqMeasure.c
*
* Description: 
*    Measures the frequency of a digital pulse train using counter 5
*     and a 1 second pulse generated from counter 1 (for devices with
*     the Am9513 counter/timer). See NOTE below about measuring
*     frequencies above 65535Hz.
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    FREQM, INTTIM
*
* List of key parameters: 
*    iCtr2, iGateMode2, iTimeBase1, iTimeBase2, uPulseWidth
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    CTR_Config, NIDAQErrorHandler, CTR_Period, CTR_Pulse, NIDAQDelay,
*     CTR_State, NIDAQYield, CTR_EvRead, CTR_Reset
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse train to the SOURCE5 pin. Also, connect
*     OUT1 to GATE5. Connect the ground reference to the DIG GND pin.
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
    i16 iCtr1 = 1;
    i16 iEdgeMode = 0;
    i16 iGateMode1 = 0;
    i16 iCtr2 = 5;
    i16 iGateMode2 = 1;
    i16 iOutType = 0;
    i16 iOutPolarity = 0;
    i16 iTimeBase1 = 3;
    i16 iTimeBase2 = 10;
    u16 uDelay = 3;
    u16 uPulseWidth = 10000;
    i16 iOutState1 = 1;
    i16 iOverFlow = 0;
    u16 uCount = 0;
    i16 iIgnoreWarnings = 0;
    i16 iYieldON = 1;

    /* Setup iCtr1 for counting rising edges with no gating. */

    iStatus = CTR_Config(iDevice, iCtr1, iEdgeMode, iGateMode1,
     iOutType, iOutPolarity);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Config/CTR1",
     iIgnoreWarnings);

    /* If you are using a PC-TIO-10 which as a hardwired 5MHz timebase
     connected to SOURCE5, you will need to use a counter other than
     counter 5 for 'iCtr2' and change 'iTimebase2' accordingly. */
    

    /* Setup iCtr2 for counting rising edges with level-HIGH gating.
     */

    iStatus = CTR_Config(iDevice, iCtr2, iEdgeMode, iGateMode2,
     iOutType, iOutPolarity);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Config/CTR2",
     iIgnoreWarnings);

    /* Setup iCtr2 to do period measurement using its SOURCE as
     timebase. */

    iStatus = CTR_Period(iDevice, iCtr2, iTimeBase2);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Period",
     iIgnoreWarnings);

    /* Output a 1 sec logic HIGH pulse from iCtr1. */

    iStatus = CTR_Pulse(iDevice, iCtr1, iTimeBase1, uDelay,
     uPulseWidth);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Pulse",
     iIgnoreWarnings);

    /* Make sure the first pulse has started, then the second pulse
     will occur after the first is completed. */

    iRetVal = NIDAQDelay(0.05);

    /* This second pulse is needed to move the data from the first
     pulse to the HOLD register where it can be read. */

    iStatus = CTR_Pulse(iDevice, iCtr1, iTimeBase1, uDelay,
     uPulseWidth);

    iRetVal = NIDAQErrorHandler(iStatus, "CTR_Pulse",
     iIgnoreWarnings);

    /* The delay here is to ensure that the first time CTR_State is
     called, it will sense a HIGH state. Some faster computers may get to
     the CTR_State call while the output pulse is still low. */

    iRetVal = NIDAQDelay(0.05);

    printf(" Wait until the output of iCtr1 goes LOW.\n");

    while ((iOutState1 != 0) && (iStatus == 0)) {


        iStatus = CTR_State(iDevice, iCtr1, &iOutState1);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "CTR_State",
     iIgnoreWarnings);

    printf(" Gate pulse should be complete - now read iCtr2.\n");

    /* NOTE: If you connect a signal with a frequency greater than
     65535Hz or get more than 65535 pulses during the read period, this
     will return incorrect data. If you want to read frequencies greater
     than 65535Hz, you can setup CTR_Pulse on iCtr1 to generate a pulse
     for a fraction of a second.  See HINT below. */

    iStatus = CTR_EvRead(iDevice, iCtr2, &iOverFlow, &uCount);

    if ((uCount >= 3) && (iStatus == 0)) {


        /* 'uCount' must be greater than 3 for valid count. the count
         corresponds to the number of microsecond ticks read by the counter
         while the gate was high. HINT: If you use a shorter gate pulse, you
         can measure the frequency with higher accuracy. The equation is:
         (freq in Hz) = (count) / (length of gate pulse in seconds). */
        

        printf(" The frequency is %u Hz.\n", uCount);

    }
    else {

        printf(" WARNING- The counter was read prematurely.\n");

    }


    iRetVal = NIDAQErrorHandler(iStatus, "CTR_EvRead",
     iIgnoreWarnings);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset counters to initial state. */

    iStatus = CTR_Reset(iDevice, iCtr1, 1);

    iStatus = CTR_Reset(iDevice, iCtr2, 1);


}

/* End of program */
