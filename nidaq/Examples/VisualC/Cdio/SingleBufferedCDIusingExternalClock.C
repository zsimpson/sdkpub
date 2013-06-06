/*********************************************************************
*
* Example program: 
*    SingleBufferedCDIusingExternalClock.c
*
* Description: 
*    Reads a buffer of digital data from the digital input lines at the
*     rate of the external clock.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    BUF, NCH, EXTTIM, BURST
*
* List of key parameters: 
*    ulCount, iNumLines, iDIReqSource
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, DIG_Grp_Config, DIG_Grp_Mode,
*     DIG_Block_PG_Config, DIG_Block_In, DIG_Block_Check, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital signals to pins DIO0-7 Connect the ground
*     reference to the DIG GND pin. Connect the external clock signal
*     to the GPCTR0 Out pin. (please refer to your hardware user manual
*     for details)
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
    i16 iDBmodeON = 1;
    i16 iDBmodeOFF = 0;
    i16 iPGmodeOn = 1;
    u32 ulCount = 1000;
    i16 iLineCount = 0;
    i16 iGroupSize = 1;
    i16 iPort = 0;
    i16 iNumLines = 8;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;
    static i16 iDIBuffer[500] = {0};
    i16 iDIGroup = 1;
    i16 iDIReqSource = 1;
    i16 iInLineDirection = 4;
    i16 iInGroupDirection = 0;
    i16 iDIEdge = 0;
    u32 ulRemaining = 1;

    /* Configure the digital lines for the correct direction. */

    while (iLineCount < iNumLines) {


        iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
         iInLineDirection);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
         iIgnoreWarning);

        ++iLineCount;

    }


    /* Configure Digital Input */

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, iGroupSize, iPort,
     iInGroupDirection);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Mode(iDevice, iDIGroup, 0, iDIEdge, 0, 0, 0);
    

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Mode",
     iIgnoreWarning);

    /* Correlate the input to the external clock.  Note, you will not
     be able to use GPCTR0 for pulse train generation when using an
     external clock. */

    iStatus = DIG_Block_PG_Config(iDevice, iDIGroup, iPGmodeOn,
     iDIReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    /* Start acquiring data. */

    iStatus = DIG_Block_In(iDevice, iDIGroup, iDIBuffer, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_In",
     iIgnoreWarning);

    while ((ulRemaining > 0) && (iStatus == 0)) {


        /* Wait until the data is acquired. */

        iStatus = DIG_Block_Check(iDevice, iDIGroup, &ulRemaining);
        

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Check",
         iIgnoreWarning);

        iRetVal = NIDAQYield(iYieldON);

    }


    /* Clear all operations and reset the board to its default state
     */

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);

    printf(" Digital data available in iDIBuffer.\n");


}

/* End of program */
