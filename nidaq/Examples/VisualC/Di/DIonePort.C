/*********************************************************************
*
* Example program: 
*    DIonePort.c
*
* Description: 
*    Inputs digital data from a single digital port. Please note that
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
*    iMode, iDir
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Prt_Config, NIDAQErrorHandler, DIG_In_Prt
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital signals to port 0. Connect the ground
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
    i16 iMode = 0;
    i16 iDir = 0;
    i32 iPattern = 0;
    i16 iIgnoreWarning = 0;

    /* Configure port as input, no handshaking. */

    iStatus = DIG_Prt_Config(iDevice, iPort, iMode, iDir);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Prt_Config",
     iIgnoreWarning);

    iStatus = DIG_In_Prt(iDevice, iPort, &iPattern);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_In_Prt",
     iIgnoreWarning);

    printf(" The digital pattern on port %d is (DECIMAL) %ld\n", iPort, iPattern);


}

/* End of program */
