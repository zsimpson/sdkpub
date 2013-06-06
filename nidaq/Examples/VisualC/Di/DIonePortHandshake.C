/*********************************************************************
*
* Example program: 
*    DIonePortHandshake.c
*
* Description: 
*    Inputs digital data from a single digital port upon a handshaking
*     signal. Please note that some DAQ devices have predetermined port
*     directions for each digital port.
*
* Example Category: 
*    DI
*
* Example Task Types: 
*    1PT, 1CH, HANDSHK
*
* List of key parameters: 
*    iMode, iDir, iLatched
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Prt_Config, NIDAQErrorHandler, DIG_Prt_Status, NIDAQYield,
*     DIG_In_Prt
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital signals to port 0. Connect the ground
*     reference to the DIG GND pin. Connect the handshaking signal to
*     the appropriate handshaking I/O pin (please refer to your
*     hardware user manual for details)
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
    i16 iMode = 1;
    i16 iDir = 0;
    i32 iPattern = 0;
    i16 iLatched = 0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    /* Configure port as input, handshaking (latched mode). */

    iStatus = DIG_Prt_Config(iDevice, iPort, iMode, iDir);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Prt_Config",
     iIgnoreWarning);

    printf(" Apply your handshaking signal to the appropriate handshaking I/O pin for input.\n");

    /* Loop until data is latched in. */

    while ((iLatched == 0) && (iStatus == 0)) {


        iStatus = DIG_Prt_Status(iDevice, iPort, &iLatched);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Prt_Status",
     iIgnoreWarning);

    iStatus = DIG_In_Prt(iDevice, iPort, &iPattern);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_In_Prt",
     iIgnoreWarning);

    printf(" The digital pattern on port %d is (DECIMAL) %ld\n", iPort, iPattern);


}

/* End of program */
