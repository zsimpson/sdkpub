/*********************************************************************
*
* Example program: 
*    WFMsingleBufExtUpdate_Eseries.c
*
* Description: 
*    Output a waveform from one analog output channel, using external
*     timing (uses low-level NI-DAQ functions, for E-series)
*
* Example Category: 
*    AO
*
* Example Task Types: 
*    BUF, 1CH, BURST, ASYNC, EXTTIM, INTTRIG, ESER
*
* List of key parameters: 
*    iGroup, ulIterations, iUpdateTB, iWFMstopped, iOpSTART, iOpCLEAR
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    NIDAQMakeBuffer, WFM_Group_Setup, NIDAQErrorHandler, WFM_Scale,
*     WFM_Load, WFM_ClockRate, Select_Signal, WFM_Group_Control,
*     WFM_Check, NIDAQYield, AO_VWrite
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output signal will be available at AO channel 0. The
*     default analog output mode for the DAQ device will be used. Also,
*     connect a digital pulse train to the PFI5/UPDATE* pin.
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
    i16 iNumChans = 1;
    i16 iChan = 0;
    static i16 piChanVect[1] = {0};
    i16 iGroup = 1;
    static f64 pdBuffer[5000] = {0};
    static i16 piBuffer[5000] = {0};
    u32 ulCount = 5000;
    u32 ulIterations = 1;
    i16 iFIFOMode = 0;
    i16 iDelayMode = 0;
    i16 iUpdateTB = 0;
    u32 ulUpdateInt = 0;
    i16 iWhichClock = 0;
    i16 iUnits = 0;
    i16 iWFMstopped = 0;
    u32 ulItersDone = 0;
    u32 ulPtsDone = 0;
    i16 iOpSTART = 1;
    i16 iOpCLEAR = 0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = NIDAQMakeBuffer(pdBuffer, ulCount, WFM_DATA_F64);

    if (iStatus == 0) {


        /* If buffer was made correctly, then output it. */

        iStatus = WFM_Group_Setup(iDevice, iNumChans, piChanVect,
         iGroup);

        iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Setup",
         iIgnoreWarning);

        iStatus = WFM_Scale(iDevice, iChan, ulCount, 1.0, pdBuffer,
         piBuffer);

        iRetVal = NIDAQErrorHandler(iStatus, "WFM_Scale",
         iIgnoreWarning);

        iStatus = WFM_Load(iDevice, iNumChans, piChanVect, piBuffer,
         ulCount, ulIterations, iFIFOMode);

        iRetVal = NIDAQErrorHandler(iStatus, "WFM_Load",
         iIgnoreWarning);

        /* Instead of calling WFM_Rate, just let iUpdateTB be 0 for
         external update timing. */

        iStatus = WFM_ClockRate(iDevice, iGroup, iWhichClock,
         iUpdateTB, ulUpdateInt, iDelayMode);

        iRetVal = NIDAQErrorHandler(iStatus, "WFM_ClockRate",
         iIgnoreWarning);

        /* Setup PFI lines for external updates. (PFI5 is setup by
         default in WFM_ClockRate) */

        iStatus = Select_Signal(iDevice, ND_OUT_UPDATE, ND_PFI_5,
         ND_HIGH_TO_LOW);

        iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal",
         iIgnoreWarning);

        printf(" Apply your external update clock signal to PFI5 to output the waveform.\n");

        iStatus = WFM_Group_Control(iDevice, iGroup, iOpSTART);
        

        iRetVal = NIDAQErrorHandler(iStatus,
         "WFM_Group_Control/START", iIgnoreWarning);

        while ((iWFMstopped == 0) && (iStatus == 0)) {


            iStatus = WFM_Check(iDevice, iChan, &iWFMstopped,
             &ulItersDone, &ulPtsDone);

            iRetVal = NIDAQYield(iYieldON);

        }


        iRetVal = NIDAQErrorHandler(iStatus, "WFM_Check",
         iIgnoreWarning);

        /* CLEANUP - Don't check for errors on purpose. */

        /* Set group back to initial state. */

        iStatus = WFM_Group_Control(iDevice, iGroup, iOpCLEAR);
        

        /* Set output at 0 volts. */

        iStatus = AO_VWrite(iDevice, iChan, 0.0);

        /* Set PFI line back to initial state. */

        iStatus = Select_Signal(iDevice, ND_OUT_UPDATE,
         ND_INTERNAL_TIMER, ND_LOW_TO_HIGH);

        printf(" The waveform generation is done!\n");

    }
    else {

        printf(" The buffer was not made correctly. Check the parameters for NIDAQMakeBuffer.\n");

    }



}

/* End of program */
