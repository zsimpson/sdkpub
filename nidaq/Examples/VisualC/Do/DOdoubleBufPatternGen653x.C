/*********************************************************************
*
* Example program: 
*    DOdoubleBufPatternGen653x.c
*
* Description: 
*    Outputs digital data continuously into a buffer from a group of
*     two digital ports using internal timing (pattern generation, for
*     DIO-32 series devices)
*
* Example Category: 
*    DO
*
* Example Task Types: 
*    BUF, NCH, INTTIM, CONT, ASYNC
*
* List of key parameters: 
*    iGroup, iGroupSize, iDir, iDBModeON, iOldDataStop, ulCount,
*     iHalfReady, ulBufferSize, iResource, iIgnoreWarning, ulAlignIndex
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Timeout_Config, NIDAQErrorHandler, NIDAQMakeBuffer,
*     DIG_Grp_Config, DIG_Block_PG_Config, DIG_DB_Config,
*     Align_DMA_Buffer, DIG_Block_Out, DIG_DB_HalfReady,
*     DIG_DB_Transfer, NIDAQYield, DIG_Block_Clear
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital signals will be on ports 0 and 1. Connect the ground
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
    i16 iGroup = 1;
    i16 iGroupSize = 2;
    i16 iPort = 0;
    i16 iDir = 1;
    i16 iPgConfig = 1;
    i16 iReqSource = 0;
    i16 iPgTB = 4;
    i16 iReqInt = 10;
    i16 iExtGate = 0;
    i16 iDBModeON = 1;
    i16 iDBModeOFF = 0;
    i16 iOldDataStop = 1;
    i16 iPartialTransfer = 0;
    static i16 piBuffer[400] = {0};
    static i16 piHalfBuffer[100] = {0};
    u32 ulCount = 200;
    i16 iHalfReady = 0;
    u32 ulPtsTfr = 100;
    i16 iLoopCount = 0;
    i16 iHalfBufsToRead = 10;
    u32 ulBufferSize = 400;
    i16 iResource = 11;
    i16 iIgnoreWarning = 1;
    u32 ulAlignIndex = 0;
    i32 lTimeout = 180;
    i16 iYieldON = 1;

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the DIG_DB_Transfer
     call. */

    iStatus = Timeout_Config(iDevice, lTimeout);

    iRetVal = NIDAQErrorHandler(iStatus, "Timeout_Config",
     iIgnoreWarning);

    iStatus = NIDAQMakeBuffer(piBuffer, ulCount, WFM_DATA_I16);

    if (iStatus == 0) {


        /* Configure group of ports as output, with handshaking. */
        

        iStatus = DIG_Grp_Config(iDevice, iGroup, iGroupSize, iPort,
         iDir);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
         iIgnoreWarning);

        /* Configure internally timed pattern generation with timebase
         4, interval 10, and no external gating. */

        iStatus = DIG_Block_PG_Config(iDevice, iGroup, iPgConfig,
         iReqSource, iPgTB, iReqInt, iExtGate);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_PG_Config",
         iIgnoreWarning);

        /* Turn ON software double-buffered mode, with half-buffer
         overwrite protection (iOldDataStop). */

        iStatus = DIG_DB_Config(iDevice, iGroup, iDBModeON,
         iOldDataStop, iPartialTransfer);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_DB_Config",
         iIgnoreWarning);

        /* Align the DMA buffer so that it does not cross a page
         boundary for AT bus computers. (It is a good idea to keep your
         buffers smaller than 4kBytes in size.) NOTE: If you change 'iGroup'
         or 'iGroupSize', make sure 'iResource' is changed accordingly. */
        

        /* The alignment is only needed on the generation buffer,
         since the write buffer gets filled up with DIG_DB_Transfer is called.
         Also, please note that piBuffer is actually twice as large as needed,
         due to a possible alignment. */
        

        iStatus = Align_DMA_Buffer(iDevice, iResource, piBuffer,
         ulCount, ulBufferSize, &ulAlignIndex);

        iRetVal = NIDAQErrorHandler(iStatus, "Align_DMA_Buffer",
         iIgnoreWarning);

        /* Start the double-buffered pattern generation output. The
         'piBuffer' here is the circular acquisition buffer. */
        

        iStatus = DIG_Block_Out(iDevice, iGroup, piBuffer, ulCount);
        

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
         iIgnoreWarning);

        /* Write 10 half-buffers.  Normally, 'piHalfBuffer' here would
         be updated with the latest data, but the first half of the buffer is
         used to ensure the simplicity of the source code. */
        

        while ((iLoopCount < iHalfBufsToRead) && (iStatus == 0)) {

            

            iStatus = DIG_DB_HalfReady(iDevice, iGroup, &iHalfReady);
            

            if (iStatus >= 0) {


                if (iHalfReady == 1) {


                    /* Half-buffer of data will be placed in
                     'piHalfBuffer'. */

                    iStatus = DIG_DB_Transfer(iDevice, iGroup,
                     piHalfBuffer, ulPtsTfr);
                    

                    iRetVal = NIDAQErrorHandler(iStatus,
                     "DIG_DB_Transfer", iIgnoreWarning);
                    

                    ++iLoopCount;

                    printf(" %d Half buffers generated.\n", iLoopCount);

                }


            }
            else {

                iRetVal = NIDAQErrorHandler(iStatus,
                 "DIG_DB_HalfReady", iIgnoreWarning);

            }


            iRetVal = NIDAQYield(iYieldON);

        }


        printf(" All 10 half-buffers done!\n");

        /* CLEANUP - Don't check for errors on purpose. */

        /* Clear the block operation. */

        iStatus = DIG_Block_Clear(iDevice, iGroup);

        /* Turn off DB mode for device. */

        iStatus = DIG_DB_Config(iDevice, iGroup, iDBModeOFF,
         iOldDataStop, iPartialTransfer);

        /* Unconfigure group. */

        iStatus = DIG_Grp_Config(iDevice, iGroup, 0, 0, 0);

        printf(" Digital double-buffered pattern generation output is done!\n");

    }
    else {

        printf(" The buffer was not made correctly. Check the parameters for NIDAQMakeBuffer.\n");

    }


    /* Disable timeouts. */

    iStatus = Timeout_Config(iDevice, -1);


}

/* End of program */
