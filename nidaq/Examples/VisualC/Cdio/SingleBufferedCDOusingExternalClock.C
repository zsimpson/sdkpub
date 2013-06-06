/*********************************************************************
*
* Example program: 
*    SingleBufferedCDOusingExternalClock.c
*
* Description: 
*    Writes a buffer of digital data to the digital output lines at the
*     rate of the external clock.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    BUF, NCH, EXTTIM, BURST
*
* List of key parameters: 
*    ulCount, iNumLines, iDOReqSource
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, NIDAQMakeBuffer,
*     DIG_Grp_Config, DIG_Grp_Mode, DIG_Block_PG_Config, DIG_Block_Out,
*     DIG_Block_Check, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital output signals will be available at pins DIO0-DIO7.
*     Connect the ground reference to the DIG GND pin. Connect the
*     external clock signal to the GPCTR0 Out pin. (please refer to
*     your hardware user manual for details)
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
    static i16 iDOBuffer[500] = {0};
    i16 iDOGroup = 2;
    i16 iDOReqSource = 1;
    i16 iOutLineDirection = 5;
    i16 iOutGroupDirection = 1;
    i16 iDOEdge = 0;
    u32 ulRemaining = 1;

    /* Configure the digital lines for the correct direction. */

    while (iLineCount < iNumLines) {


        iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
         iOutLineDirection);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
         iIgnoreWarning);

        ++iLineCount;

    }


    /* Configure Digital Output */

    /* Create a sawtooth waveform. */

    iStatus = NIDAQMakeBuffer(iDOBuffer, ulCount, WFM_DATA_U8);

    iRetVal = NIDAQErrorHandler(iStatus, "NIDAQMakeBuffer",
     iIgnoreWarning);

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, iGroupSize, iPort,
     iOutGroupDirection);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Mode(iDevice, iDOGroup, 0, iDOEdge, 0, 0, 0);
    

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Mode",
     iIgnoreWarning);

    /* Correlate the output to the external clock.  Note, you will not
     be able to use GPCTR0 for pulse train generation when using an
     external clock. */

    iStatus = DIG_Block_PG_Config(iDevice, iDOGroup, iPGmodeOn,
     iDOReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    /* Start generating data. */

    iStatus = DIG_Block_Out(iDevice, iDOGroup, iDOBuffer, ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
     iIgnoreWarning);

    while ((ulRemaining > 0) && (iStatus == 0)) {


        /* Wait until the data is finished outputting. */

        iStatus = DIG_Block_Check(iDevice, iDOGroup, &ulRemaining);
        

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Check",
         iIgnoreWarning);

        iRetVal = NIDAQYield(iYieldON);

    }


    /* Clear all operations and reset the board to its default state
     */

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);


}

/* End of program */
