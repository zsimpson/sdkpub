/*********************************************************************
*
* Example program: 
*    DoubleBufferedCDIOwithAIO.c
*
* Description: 
*    Continuously correlates digital input with analog input and
*     digital output with analog output.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    BUF, NCH, INTTIM, CONT, ASYNC
*
* List of key parameters: 
*    ulCount, ulHalfCount, iHalfBufsToRead, iAIChan, dSampRate,
*     iAOChan, dUpdateRate, iDIReqSource, iDOReqSource, iNumOutputLines
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Timeout_Config, NIDAQErrorHandler, DIG_Line_Config,
*     NIDAQMakeBuffer, DIG_Grp_Config, DIG_Grp_Mode,
*     DIG_Block_PG_Config, DIG_DB_Config, Set_DAQ_Device_Info,
*     WFM_DB_Config, WFM_Group_Setup, WFM_Scale, WFM_Load, WFM_Rate,
*     WFM_ClockRate, DAQ_Rate, DAQ_DB_Config, DIG_Block_Out,
*     DIG_Block_In, WFM_Group_Control, DAQ_Start, DAQ_DB_HalfReady,
*     DAQ_DB_Transfer, DIG_DB_HalfReady, DIG_DB_Transfer, NIDAQYield,
*     DAQ_Clear, AO_VWrite
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital input signals to pins DIO4, DIO5, DIO6, and
*     DIO7 . The digital output signals will be available at pins DIO0,
*     DIO1, DIO2, and DIO3. Connect the ground reference to the DIG GND
*     pin. The analog output signal will be available at AO channel 0.
*     Connect your analog signals to the AI channel 0 I/O pin. (please
*     refer to your hardware user manual for details)
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
    i16 iDBmodeON = 1;
    i16 iDBmodeOFF = 0;
    i16 iPGmodeOn = 1;
    u32 ulCount = 1000;
    u32 ulHalfCount = 500;
    i16 iLoopCount = 0;
    i16 iLineCount = 0;
    i16 iHalfBufsToRead = 20;
    i16 iGroupSize = 1;
    i16 iPort = 0;
    i16 iNumLines = 8;
    i16 iRegenAllowed = 0;
    i16 iNoRegen = 1;
    i16 iPartialTransferAllowed = 1;
    i16 iNoPartialTransfer = 0;
    i16 iIgnoreWarning = 0;
    i32 lTimeout = 180;
    i16 iYieldON = 1;
    i16 iAIChan = 0;
    i16 iGain = 1;
    f64 dSampRate = 1000;
    i16 iAIUnits = 0;
    i16 iSampTB = 0;
    u16 uSampInt = 0;
    static i16 piAIBuffer[1000] = {0};
    static i16 piAIHalfBuffer[500] = {0};
    i16 iHalfReady = 0;
    i16 iDAQStopped = 0;
    u32 ulPtsTfr = 0;
    i16 iGroup = 1;
    i16 iNumChans = 1;
    i16 iAOChan = 0;
    f64 dUpdateRate = 1000;
    i16 iAOUnits = 0;
    i16 iUpdateTB = 0;
    u32 ulUpdateInt = 0;
    i16 iWhichClock = 0;
    i16 iDelayMode = 0;
    static i16 piAOChanVect[1] = {0};
    static f64 pdAOBuffer[1000] = {0};
    static i16 piAOBuffer[1000] = {0};
    u32 ulIterations = 0;
    i16 iFIFOMode = 0;
    i16 iOpSTART = 1;
    i16 iOpCLEAR = 0;
    static i16 iDIBuffer[500] = {0};
    static i16 iDIHalfBuffer[250] = {0};
    i16 iDIGroup = 1;
    i16 iDIReqSource = 9;
    i16 iInLineDirection = 4;
    i16 iInGroupDirection = 0;
    i16 iDIEdge = 0;
    static i16 iDOBuffer[500] = {0};
    i16 iDOGroup = 2;
    i16 iDOReqSource = 10;
    i16 iOutLineDirection = 5;
    i16 iOutGroupDirection = 1;
    i16 iDOEdge = 0;
    i16 iNumOutputLines = 4;

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the DAQ_DB_Transfer or
     DIG_DB_Transfer call. */

    iStatus = Timeout_Config(iDevice, lTimeout);

    iRetVal = NIDAQErrorHandler(iStatus, "Timeout_Config",
     iIgnoreWarning);

    /* Configure the digital lines for the correct direction.  Lines
     0-3 will be output lines and 4-7 input lines. */

    while (iLineCount < iNumLines) {


        if (iLineCount < iNumOutputLines) {


            iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
             iOutLineDirection);

        }
        else {

            iStatus = DIG_Line_Config(iDevice, iPort, iLineCount,
             iInLineDirection);

        }


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

    /* The buffer will be written once and then regenerated. */

    iStatus = DIG_DB_Config(iDevice, iDOGroup, iDBmodeON,
     iRegenAllowed, iNoPartialTransfer);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_DB_Config",
     iIgnoreWarning);

    /* Since there are only 3 DMA channels available for a board and
     we are doing analog input, analog output, digital input, and digital
     output, one of the operations must be set to perform transfers by
     interrupts. */

    iStatus = Set_DAQ_Device_Info(iDevice, ND_DATA_XFER_MODE_DIO_GR2,
     ND_INTERRUPTS);

    iRetVal = NIDAQErrorHandler(iStatus, "Set_DAQ_Device_Info",
     iIgnoreWarning);

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

    iStatus = DIG_DB_Config(iDevice, iDIGroup, iDBmodeON, iNoRegen,
     iNoPartialTransfer);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_DB_Config",
     iIgnoreWarning);

    /* Configure Analog Output */

    iStatus = NIDAQMakeBuffer(pdAOBuffer, ulCount, WFM_DATA_F64);

    iRetVal = NIDAQErrorHandler(iStatus, "NIDAQMakeBuffer",
     iIgnoreWarning);

    iStatus = WFM_DB_Config(iDevice, iNumChans, piAOChanVect,
     iDBmodeON, iRegenAllowed, iNoPartialTransfer);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_DB_Config",
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

    /* Configure Analog Input */

    iStatus = DAQ_Rate(dSampRate, iAIUnits, &iSampTB, &uSampInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Rate", iIgnoreWarning);
    

    iStatus = DAQ_DB_Config(iDevice, iDBmodeON);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_Config",
     iIgnoreWarning);

    /* Start acquiring and generating data. */

    iStatus = DIG_Block_Out(iDevice, iDOGroup, iDOBuffer, ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
     iIgnoreWarning);

    iStatus = DIG_Block_In(iDevice, iDIGroup, iDIBuffer, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_In",
     iIgnoreWarning);

    iStatus = WFM_Group_Control(iDevice, iGroup, iOpSTART);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Control",
     iIgnoreWarning);

    printf(" Continuous generations have started.\n");

    iStatus = DAQ_Start(iDevice, iAIChan, iGain, piAIBuffer, ulCount,
     iSampTB, uSampInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Start", iIgnoreWarning);
    

    printf(" Continuous acquisitions have started.\n");

    /* Loop until 'iHalfBufsToRead' half buffers are acquired. HINT:
     You can be doing other foreground tasks during this time. */
    

    printf(" HINT: You can add your own graphing calls in the while loop.\n");

    while ((iLoopCount < iHalfBufsToRead) && (iStatus == 0)) {

        

        iStatus = DAQ_DB_HalfReady(iDevice, &iHalfReady,
         &iDAQStopped);

        if ((iHalfReady == 1) && (iStatus == 0)) {


            iStatus = DAQ_DB_Transfer(iDevice, piAIHalfBuffer,
             &ulPtsTfr, &iDAQStopped);

            iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_Transfer",
             0);

            ++iLoopCount;;

            printf(" %d Half buffers acquired.\n", iLoopCount);

        }
        else {

            iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_HalfReady",
             0);

        }


        iStatus = DIG_DB_HalfReady(iDevice, iDIGroup, &iHalfReady);
        

        if ((iHalfReady == 1) && (iStatus == 0)) {


            iStatus = DIG_DB_Transfer(iDevice, iDIGroup,
             iDIHalfBuffer, ulHalfCount);

            iRetVal = NIDAQErrorHandler(iStatus, "DIG_DB_Transfer",
             0);

        }
        else {

            iRetVal = NIDAQErrorHandler(iStatus, "DIG_DB_HalfReady",
             0);

        }


        iRetVal = NIDAQYield(iYieldON);

    }


    printf(" Continuous acquisitions are done.\n");

    /* Clear all operations and reset the board to its default state
     */

    iStatus = DAQ_Clear(iDevice);

    iStatus = DAQ_DB_Config(iDevice, iDBmodeOFF);

    iStatus = WFM_Group_Control(iDevice, iGroup, iOpCLEAR);

    iStatus = WFM_DB_Config(iDevice, iNumChans, piAOChanVect,
     iDBmodeOFF, 0, 0);

    iStatus = AO_VWrite(iDevice, iAOChan, 0.0);

    iStatus = DIG_Grp_Config(iDevice, iDOGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);

    /* Disable timeouts */

    iStatus = Timeout_Config(iDevice, -1);


}

/* End of program */
