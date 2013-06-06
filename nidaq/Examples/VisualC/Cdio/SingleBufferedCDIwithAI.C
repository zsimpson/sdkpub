/*********************************************************************
*
* Example program: 
*    SingleBufferedCDIwithAI.c
*
* Description: 
*    Correlates a single buffer of digital input with analog input.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    BUF, NCH, INTTIM
*
* List of key parameters: 
*    ulCount, iAIChan, dSampRate, iDIReqSource
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, DIG_Grp_Config, DIG_Grp_Mode,
*     DIG_Block_PG_Config, DAQ_Rate, DIG_Block_In, DAQ_Start,
*     DAQ_Check, NIDAQYield, DAQ_VScale, DAQ_Clear, NIDAQPlotWaveform
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital input signals to pins DIO0-7. Connect the
*     ground reference to the DIG GND pin. Connect your analog signal
*     to the AI channel 0 I/O pin. (please refer to your hardware user
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
    i16 iPGmodeOn = 1;
    u32 ulCount = 1000;
    i16 iLineCount = 0;
    i16 iGroupSize = 1;
    i16 iPort = 0;
    i16 iNumLines = 8;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;
    i16 iAIChan = 0;
    i16 iGain = 1;
    f64 dSampRate = 1000;
    i16 iAIUnits = 0;
    i16 iSampTB = 0;
    u16 uSampInt = 0;
    static i16 piAIBuffer[1000] = {0};
    static f64 pdAIVoltBuffer[1000] = {0};
    i16 iDAQStopped = 0;
    u32 ulPtsTfr = 0;
    f64 dGainAdjust = 1.0;
    f64 dOffset = 0.0;
    static i16 iDIBuffer[500] = {0};
    i16 iDIGroup = 1;
    i16 iDIReqSource = 9;
    i16 iInLineDirection = 4;
    i16 iInGroupDirection = 0;
    i16 iDIEdge = 0;

    /* Configure the digital lines for the correct direction. */

    while (iLineCount < iNumLines) {


        iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
         iInLineDirection);

        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Line_Config",
         iIgnoreWarning);

        ++iLineCount;

    }


    /* Configure Digital Input */

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, iGroupSize, iPort,
     iInGroupDirection);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Mode(iDevice, iDIGroup, 0, iDIEdge, 0, 0, 0);
    

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Mode",
     iIgnoreWarning);

    /* Correlate the input to the Analog Input Scan Clock. */

    iStatus = DIG_Block_PG_Config(iDevice, iDIGroup, iPGmodeOn,
     iDIReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    /* Configure Analog Input */

    iStatus = DAQ_Rate(dSampRate, iAIUnits, &iSampTB, &uSampInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Rate", iIgnoreWarning);
    

    /* Start acquiring data. */

    iStatus = DIG_Block_In(iDevice, iDIGroup, iDIBuffer, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_In",
     iIgnoreWarning);

    iStatus = DAQ_Start(iDevice, iAIChan, iGain, piAIBuffer, ulCount,
     iSampTB, uSampInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Start", iIgnoreWarning);
    

    while ((iDAQStopped != 1) && (iStatus == 0)) {


        /* Loop until the acquisition is complete.  HINT: You can be
         doing other foreground tasks during this time. */

        iStatus = DAQ_Check(iDevice, &iDAQStopped, &ulPtsTfr);

        iRetVal = NIDAQYield(iYieldON);

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Check", iIgnoreWarning);
    

    iStatus = DAQ_VScale(iDevice, iAIChan, iGain, dGainAdjust,
     dOffset, ulCount, piAIBuffer, pdAIVoltBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale",
     iIgnoreWarning);

    /* Clear all operations and reset the board to its default state
     */

    iStatus = DAQ_Clear(iDevice);

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);

    printf(" Digital data available in iDIBuffer.\n");

    printf(" Analog data available in pdAIVoltBuffer.\n");

    iRetVal = NIDAQPlotWaveform(pdAIVoltBuffer, ulCount,
     WFM_DATA_F64);


}

/* End of program */
