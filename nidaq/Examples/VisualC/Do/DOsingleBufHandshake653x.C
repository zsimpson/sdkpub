/*********************************************************************
*
* Example program: 
*    DOsingleBufHandshake653x.c
*
* Description: 
*    Outputs digital data into a buffer from a group of two digital
*     ports using hanshaking (for DIO-32 series devices)
*
* Example Category: 
*    DO
*
* Example Task Types: 
*    BUF, NCH, HANDSHK, BURST, ASYNC
*
* List of key parameters: 
*    iGroup, iGroupSize, iDir, iSignal, iEdge, iReqPol, iAckPol,
*     iAckDelayTime, ulCount, ulRemaining
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    NIDAQMakeBuffer, DIG_Grp_Config, NIDAQErrorHandler, DIG_Grp_Mode,
*     DIG_Block_Out, DIG_Block_Check, NIDAQYield, DIG_Block_Clear
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
    i16 iSignal = 1;
    i16 iEdge = 0;
    i16 iReqPol = 0;
    i16 iAckPol = 0;
    i16 iAckDelayTime = 0;
    static i16 piBuffer[100] = {0};
    u32 ulCount = 100;
    u32 ulRemaining = 1;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = NIDAQMakeBuffer(piBuffer, ulCount, WFM_DATA_I16);

    if (iStatus == 0) {


        /* Configure group of ports as output, with handshaking. */
        

        iStatus = DIG_Grp_Config(iDevice, iGroup, iGroupSize, iPort,
         iDir);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
         iIgnoreWarning);

        /* Configure handshaking parameters for pulsed, leading edge,
         active high request and acknowledge with no delay */
        

        iStatus = DIG_Grp_Mode(iDevice, iGroup, iSignal, iEdge,
         iReqPol, iAckPol, iAckDelayTime);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Mode",
         iIgnoreWarning);

        /* You may want to call 'Align_DMA_Buffer' at this point if
         you have a buffer larger than 4kBytes in size and if your handshaking
         signals occur at intervals faster than 50us. */
        

        /* Start the handshaked buffered output of 100 "items". */
        

        iStatus = DIG_Block_Out(iDevice, iGroup, piBuffer, ulCount);
        

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
         iIgnoreWarning);

        printf(" Apply your handshaking signals to the appropriate handshaking I/O pins.\n");

        while ((ulRemaining != 0) && (iStatus == 0)) {


            iStatus = DIG_Block_Check(iDevice, iGroup, &ulRemaining);
            

            iRetVal = NIDAQYield(iYieldON);

        }


        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Check",
         iIgnoreWarning);

        /* CLEANUP - Don't check for errors on purpose. */

        /* Clear the block operation. */

        iStatus = DIG_Block_Clear(iDevice, iGroup);

        /* Unconfigure group. */

        iStatus = DIG_Grp_Config(iDevice, iGroup, 0, 0, 0);

        printf(" Digital handshaked buffered output is done!\n");

    }
    else {

        printf(" The buffer was not made correctly. Check the parameters for NIDAQMakeBuffer.\n");

    }



}

/* End of program */
