/*********************************************************************
*
* Example program: 
*    DOoneGroupHandshake.c
*
* Description: 
*    Outputs digital data from a group of two digital ports upon a
*     handshaking signal
*
* Example Category: 
*    DO
*
* Example Task Types: 
*    1PT, NCH, HANDSHK
*
* List of key parameters: 
*    iGroup, iGroupSize, iDir, iLatched
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Grp_Config, NIDAQErrorHandler, DIG_Out_Grp, DIG_Grp_Status,
*     NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital signals will be on ports 0 and 1. Connect the ground
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
    i16 iGroup = 1;
    i16 iGroupSize = 2;
    i16 iPort = 0;
    i16 iDir = 1;
    i16 iLatched = 0;
    i16 iGroupPattern = 257;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    /* Configure group of ports as output, with handshaking. */

    iStatus = DIG_Grp_Config(iDevice, iGroup, iGroupSize, iPort,
     iDir);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);

    /* Output data first, then wait for handshaking signal. This will
     turn on line 0 on both ports 0 and 1. */

    iStatus = DIG_Out_Grp(iDevice, iGroup, iGroupPattern);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Out_Grp",
     iIgnoreWarning);

    /* On the DIO-32HS, 'iLatched' is viewed from the perspective of
     its FIFO.  If the FIFO is ready to take more data for output, this
     function will return 'latched', however, the actual handshaking
     signal may not have arrived by that time. */

    printf(" Apply your handshaking signal to the appropriate handshaking I/O pin for output.\n");

    /* Loop until data is latched out. */

    while ((iLatched == 0) && (iStatus == 0)) {


        iStatus = DIG_Grp_Status(iDevice, iGroup, &iLatched);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Status",
     iIgnoreWarning);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Unconfigure group. */

    iStatus = DIG_Grp_Config(iDevice, iGroup, 0, 0, 0);

    printf(" The digital pattern has been latched out.\n");


}

/* End of program */
