/*********************************************************************
*
* Example program: 
*    SingleBufferedCDOwithAO.c
*
* Description: 
*    Correlates a buffer of digital output with analog output.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    BUF, NCH, INTTIM, BURST, ASYNC
*
* List of key parameters: 
*    ulCount, iNumLines, iAOChan, dUpdateRate, iDOReqSource
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, NIDAQMakeBuffer,
*     DIG_Grp_Config, DIG_Grp_Mode, DIG_Block_PG_Config,
*     WFM_Group_Setup, WFM_Scale, WFM_Load, WFM_Rate, WFM_ClockRate,
*     DIG_Block_Out, WFM_Group_Control, WFM_Check, NIDAQYield,
*     AO_VWrite
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The digital output signals will be available at pins DIO0-DIO7.
*     Connect the ground reference to the DIG GND pin. The analog
*     output signal will be available at AO channel 0. (please refer to
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
    i16 iPGmodeOn = 1;
    u32 ulCount = 4096;
    i16 iLineCount = 0;
    i16 iGroupSize = 1;
    i16 iPort = 0;
    i16 iNumLines = 8;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;
    i16 iGroup = 1;
    i16 iNumChans = 1;
    i16 iAOChan = 0;
    f64 dUpdateRate = 1000;
    i16 iAOUnits = 0;
    i16 iUpdateTB = 0;
    u32 ulUpdateInt = 0;
    i16 iWhichClock = 0;
    i16 iDelayMode = 0;
    i16 iHalfReady = 0;
    static i16 piAOChanVect[1] = {0};
    static f64 pdAOBuffer[4096] = {0};
    static i16 piAOBuffer[4096] = {0};
    u32 ulIterations = 1;
    i16 iFIFOMode = 0;
    i16 iOpSTART = 1;
    i16 iOpCLEAR = 0;
    i16 iWFMStopped = 0;
    u32 ulItersDone = 0;
    u32 ulPtsDone = 0;
    static i16 iDOBuffer[2048] = {0};
    i16 iDOGroup = 2;
    i16 iDOReqSource = 10;
    i16 iOutLineDirection = 5;
    i16 iOutGroupDirection = 1;
    i16 iDOEdge = 0;

    /* Configure the digital lines for the correct direction. */

    while (iLineCount < iNumLines) {


        iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
         iOutLineDirection);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
         iIgnoreWarning);

        ++iLineCount;

    }


    /* Configure Digital Output */

    /* Create a sawtooth waveform. */

    iStatus = NIDAQMakeBuffer(iDOBuffer, ulCount, WFM_DATA_U8);

    iRetVal = NIDAQErrorHandler(iStatus, "NIDAQMakeBuffer",
     iIgnoreWarning);

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, iGroupSize, iPort,
     iOutGroupDirection);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Mode(iDevice, iDOGroup, 0, iDOEdge, 0, 0, 0);
    

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Mode",
     iIgnoreWarning);

    /* Correlate the output to the Analog Output Update clock. */

    iStatus = DIG_Block_PG_Config(iDevice, iDOGroup, iPGmodeOn,
     iDOReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    /* Configure Analog Output */

    iStatus = NIDAQMakeBuffer(pdAOBuffer, ulCount, WFM_DATA_F64);

    iRetVal = NIDAQErrorHandler(iStatus, "NIDAQMakeBuffer",
     iIgnoreWarning);

    iStatus = WFM_Group_Setup(iDevice, iNumChans, piAOChanVect,
     iGroup);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Setup",
     iIgnoreWarning);

    iStatus = WFM_Scale(iDevice, iAOChan, ulCount, 1.0, pdAOBuffer,
     piAOBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Scale", iIgnoreWarning);
    

    iStatus = WFM_Load(iDevice, iNumChans, piAOChanVect, piAOBuffer,
     ulCount, ulIterations, iFIFOMode);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Load", iIgnoreWarning);
    

    iStatus = WFM_Rate(dUpdateRate, iAOUnits, &iUpdateTB,
     &ulUpdateInt);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Rate", iIgnoreWarning);
    

    iStatus = WFM_ClockRate(iDevice, iGroup, iWhichClock, iUpdateTB,
     ulUpdateInt, iDelayMode);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_ClockRate",
     iIgnoreWarning);

    printf(" The digital and analog waveforms should be output at a rate of %lf updates/sec.\n", dUpdateRate);

    /* Start generating data. */

    iStatus = DIG_Block_Out(iDevice, iDOGroup, iDOBuffer, ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
     iIgnoreWarning);

    iStatus = WFM_Group_Control(iDevice, iGroup, iOpSTART);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Control",
     iIgnoreWarning);

    while ((iWFMStopped == 0) && (iStatus == 0)) {


        iStatus = WFM_Check(iDevice, iAOChan, &iWFMStopped,
         &ulItersDone, &ulPtsDone);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Check", iIgnoreWarning);
    

    /* Clear all operations and reset the board to its default state
     */

    iStatus = WFM_Group_Control(iDevice, iGroup, iOpCLEAR);

    iStatus = AO_VWrite(iDevice, iAOChan, 0.0);

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);


}

/* End of program */
