/*********************************************************************
*
* Example program: 
*    DOoneLine.c
*
* Description: 
*    Outputs digital data from a single digital line
*
* Example Category: 
*    DO
*
* Example Task Types: 
*    1PT, 1CH, IMMED
*
* List of key parameters: 
*    iPort, iLine, iDir
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, DIG_Out_Line, NIDAQWaitForKey
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital signal will be on port 0, line 0. Connect the ground
*     reference to the DIG GND pin.
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
    i16 iPort = 0;
    i16 iLine = 0;
    i16 iDir = 1;
    i16 iStateON = 1;
    i16 iStateOFF = 0;
    i16 iIgnoreWarning = 0;

    /* Configure line as output. */

    /* NOTE: Some devices do not support DIG_Line_Config.  Use
     DIG_Prt_Config instead. */

    iStatus = DIG_Line_Config(iDevice, iPort, iLine, iDir);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
     iIgnoreWarning);

    printf(" The digital state on port %d line %d is set to %d\n", iPort, iLine, iStateON);

    iStatus = DIG_Out_Line(iDevice, iPort, iLine, iStateON);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Out_Line",
     iIgnoreWarning);

    printf(" Hit any key to change it to %d\n", iStateOFF);

    iRetVal = NIDAQWaitForKey(0.0);

    printf(" The digital state on port %d line %d is set to %d\n", iPort, iLine, iStateOFF);

    iStatus = DIG_Out_Line(iDevice, iPort, iLine, iStateOFF);


}

/* End of program */
