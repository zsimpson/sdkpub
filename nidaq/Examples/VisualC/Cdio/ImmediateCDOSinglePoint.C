/*********************************************************************
*
* Example program: 
*    ImmediateCDOSinglePoint.c
*
* Description: 
*    Writes digital data immediately to the output lines using digital
*     group function calls.  For examples of performing the same task
*     using the STC chip, see the examples in the DO examples folder.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    1PT, NCH
*
* List of key parameters: 
*    ulCount
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, DIG_Grp_Config, DIG_Grp_Mode,
*     DIG_Grp_Status, DIG_Out_Grp, NIDAQDelay
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital output signals will be available at pins DIO0-7.
*     Connect the ground reference to the DIG GND pin. (please refer to
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
    u32 ulCount = 100;
    u32 ulLoopCount = 0;
    i16 iLineCount = 0;
    i16 iGroupSize = 1;
    i16 iPort = 0;
    i16 iNumLines = 8;
    i16 iIgnoreWarning = 0;
    i16 iReady = 0;
    i16 iDOGroup = 2;
    i16 iOutLineDirection = 5;
    i16 iOutGroupDirection = 1;
    i16 iDOEdge = 0;
    i16 iDataPoint = 0;

    /* Configure the digital lines for the correct direction. */

    while (iLineCount < iNumLines) {


        iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
         iOutLineDirection);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
         iIgnoreWarning);

        ++iLineCount;

    }


    /* Configure Digital Output */

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, iGroupSize, iPort,
     iOutGroupDirection);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Mode(iDevice, iDOGroup, 0, iDOEdge, 0, 0, 0);
    

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Mode",
     iIgnoreWarning);

    /* Call the DIG_Grp_Status function to enable digital operations.
     */

    iStatus = DIG_Grp_Status(iDevice, iDOGroup, &iReady);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Status", 0);

    /* Output ulCount number of points. */

    while ((ulLoopCount < ulCount) && (iStatus == 0)) {


        iStatus = DIG_Out_Grp(iDevice, iDOGroup, iDataPoint);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Out_Grp", 0);
        

        ++ulLoopCount;;

        ++iDataPoint;

        iStatus = NIDAQDelay(0.1);

    }


    /* Clear all operations and reset the board to its default state
     */

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);


}

/* End of program */
