/*********************************************************************
*
* Example program: 
*    DIoneGroupHandshake.c
*
* Description: 
*    Inputs digital data from a group of two digital ports upon a
*     handshaking signal. (for DIO-32 series devices)
*
* Example Category: 
*    DI
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
*    DIG_Grp_Config, NIDAQErrorHandler, DIG_Grp_Status, NIDAQYield,
*     DIG_In_Grp
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital signals to ports 0 and 1. Connect the ground
*     reference to the 'digital ground' pin. Connect the handshaking
*     signal to the appropriate handshaking I/O pin (please refer to
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
    i16 iGroup = 1;
    i16 iGroupSize = 2;
    i16 iPort = 0;
    i16 iDir = 0;
    i16 iLatched = 0;
    i16 iGroupPattern = 0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    /* Configure group of ports as input, with handshaking. */

    iStatus = DIG_Grp_Config(iDevice, iGroup, iGroupSize, iPort,
     iDir);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);

    printf(" Apply your handshaking signal to the appropriate handshaking I/O pin for input.\n");

    /* Loop until data is latched in. */

    while ((iLatched == 0) && (iStatus == 0)) {


        iStatus = DIG_Grp_Status(iDevice, iGroup, &iLatched);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Status",
     iIgnoreWarning);

    iStatus = DIG_In_Grp(iDevice, iGroup, &iGroupPattern);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_In_Grp",
     iIgnoreWarning);

    printf(" The digital pattern on group %d is (DECIMAL) %d\n", iGroup, iGroupPattern);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Unconfigure group. */

    iStatus = DIG_Grp_Config(iDevice, iGroup, 0, 0, 0);


}

/* End of program */
