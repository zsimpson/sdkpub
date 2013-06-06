/*********************************************************************
*
* Example program: 
*    DIoneLine.c
*
* Description: 
*    Inputs digital data from a single digital line. Please note that
*     some DAQ devices have predetermined port directions for each
*     digital port.
*
* Example Category: 
*    DI
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
*    DIG_Line_Config, NIDAQErrorHandler, DIG_In_Line
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital signal to port 0, line 0. Please note that
*     some DAQ devices have predetermined port directions for each
*     digital port. Connect the ground reference to the DIG GND pin.
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
    i16 iDir = 0;
    i16 iState = 0;
    i16 iIgnoreWarning = 0;

    /* Configure line as input. */

    /* NOTE: Some devices do not support DIG_Line_Config.  Use
     DIG_Prt_Config instead. */

    iStatus = DIG_Line_Config(iDevice, iPort, iLine, iDir);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
     iIgnoreWarning);

    iStatus = DIG_In_Line(iDevice, iPort, iLine, &iState);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_In_Line",
     iIgnoreWarning);

    printf(" The digital state on port %d line %d is %d\n", iPort, iLine, iState);


}

/* End of program */
