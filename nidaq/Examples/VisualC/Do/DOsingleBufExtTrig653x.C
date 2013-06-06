/*********************************************************************
*
* Example program: 
*    DOsingleBufExtTrig653x.c
*
* Description: 
*    Outputs digital data from a buffer to a group of two digital ports
*     upon a digital start trigger, using internal timing (for DIO-32HS
*     devices)
*
* Example Category: 
*    DO
*
* Example Task Types: 
*    BUF, NCH, HANDSHK, EXTTRIG, ASYNC
*
* List of key parameters: 
*    iGroup, iGroupSize, iDir, iStartTrigON, ulCount, ulBufferSize,
*     iResource, ulRemaining, ulAlignIndex
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    NIDAQMakeBuffer, DIG_Grp_Config, NIDAQErrorHandler,
*     DIG_Block_PG_Config, DIG_Trigger_Config, Align_DMA_Buffer,
*     DIG_Block_Out, DIG_Block_Check, NIDAQYield, DIG_Block_Clear,
*     NIDAQPlotWaveform
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital signals will be on ports 0 and 1. Connect the ground
*     reference to the DIG GND pin. Connect the digital trigger signal
*     to the 'start trigger' pin (please refer to your hardware user
*     manual for details)
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
    i16 iPgConfig = 1;
    i16 iReqSource = 0;
    i16 iPgTB = 3;
    i16 iReqInt = 10;
    i16 iExtGate = 0;
    i16 iStartTrigON = 1;
    i16 iStartTrigOFF = 0;
    i16 iStartPol = 0;
    i16 iStopTrig = 0;
    i16 iStopPol = 0;
    u32 ulPtsAfterStopTrig = 0;
    u32 ulPattern = 0;
    u32 ulPatternMask = 0;
    static i16 piBuffer[200] = {0};
    u32 ulCount = 100;
    u32 ulBufferSize = 200;
    i16 iResource = 11;
    u32 ulRemaining = 1;
    u32 ulAlignIndex = 0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = NIDAQMakeBuffer(piBuffer, ulCount, WFM_DATA_I16);

    if (iStatus == 0) {


        /* Configure group of ports as output, with handshaking. */
        

        iStatus = DIG_Grp_Config(iDevice, iGroup, iGroupSize, iPort,
         iDir);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
         iIgnoreWarning);

        /* Configure internally timed pattern generation with timebase
         3, interval 10, and no external gating. */

        iStatus = DIG_Block_PG_Config(iDevice, iGroup, iPgConfig,
         iReqSource, iPgTB, iReqInt, iExtGate);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_PG_Config",
         iIgnoreWarning);

        /* Configure for digital start trigger. */

        iStatus = DIG_Trigger_Config(iDevice, iGroup, iStartTrigON,
         iStartPol, iStopTrig, iStopPol, ulPtsAfterStopTrig, ulPattern,
         ulPatternMask);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Trigger_Config",
         iIgnoreWarning);

        /* Align the DMA buffer so that it does not cross a page
         boundary for AT bus computers. (It is a good idea to keep your
         buffers smaller than 4kBytes in size.) NOTE: If you change 'iGroup'
         or 'iGroupSize', make sure 'iResource' is changed accordingly. */
        

        iStatus = Align_DMA_Buffer(iDevice, iResource, piBuffer,
         ulCount, ulBufferSize, &ulAlignIndex);

        iRetVal = NIDAQErrorHandler(iStatus, "Align_DMA_Buffer",
         iIgnoreWarning);

        /* Start the pattern generation output of 100 "items" upon the
         digital start trigger. */

        iStatus = DIG_Block_Out(iDevice, iGroup, piBuffer, ulCount);
        

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
         iIgnoreWarning);

        printf(" Apply the digital trigger to the 'start trigger' pin to start the operation.\n");

        while ((ulRemaining != 0) && (iStatus == 0)) {


            iStatus = DIG_Block_Check(iDevice, iGroup, &ulRemaining);
            

            iRetVal = NIDAQYield(iYieldON);

        }


        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Check",
         iIgnoreWarning);

        /* CLEANUP - Don't check for errors on purpose. */

        /* Set trigger mode to initial state. */

        iStatus = DIG_Trigger_Config(iDevice, iGroup, iStartTrigOFF,
         iStartPol, iStopTrig, iStopPol, ulPtsAfterStopTrig, ulPattern,
         ulPatternMask);

        /* Clear the block operation. */

        iStatus = DIG_Block_Clear(iDevice, iGroup);

        /* Unconfigure group. */

        iStatus = DIG_Grp_Config(iDevice, iGroup, 0, 0, 0);

        iStatus = NIDAQPlotWaveform(piBuffer, ulCount, WFM_DATA_I16);
        

        printf(" The data is available in 'piBuffer'.\n");

        if (iStatus == 0) {


            printf(" Digital pattern generation output with digital start trigger is done!\n");

        }


    }
    else {

        printf(" The buffer was not made correctly. Check the parameters for NIDAQMakeBuffer.\n");

    }



}

/* End of program */
