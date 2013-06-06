/*********************************************************************
*
* Example program: 
*    DoubleBufferedCDIOusingExternalClock.c
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
*    ulCount, ulHalfCount, iHalfBufsToRead, iDIReqSource, iDOReqSource,
*     iNumOutputLines
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Timeout_Config, NIDAQErrorHandler, DIG_Line_Config,
*     NIDAQMakeBuffer, DIG_Grp_Config, DIG_Grp_Mode,
*     DIG_Block_PG_Config, DIG_DB_Config, DIG_Block_Out, DIG_Block_In,
*     DIG_DB_HalfReady, DIG_DB_Transfer, NIDAQYield
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
    u32 ulCount = 1024;
    u32 ulHalfCount = 512;
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
    i16 iHalfReady = 0;
    static i16 iDIBuffer[512] = {0};
    static i16 iDIHalfBuffer[256] = {0};
    i16 iDIGroup = 1;
    i16 iDIReqSource = 1;
    i16 iInLineDirection = 4;
    i16 iInGroupDirection = 0;
    i16 iDIEdge = 0;
    static i16 iDOBuffer[512] = {0};
    i16 iDOGroup = 2;
    i16 iDOReqSource = 1;
    i16 iOutLineDirection = 5;
    i16 iOutGroupDirection = 1;
    i16 iDOEdge = 0;
    i16 iNumOutputLines = 4;

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the DIG_DB_Transfer
     call. */

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

    /* Correlate the output to the external clock.  By default, the
     external clock is routed across RTSI 0.  If you wish to use another
     line besides RTSI 0, make a second call to the DIG_Block_PG_Config
     function specifying the the desired RTSI line in the reqSource
     parameter.  Also, when using one external clock in this manner, you
     will lose pulse train generation capabilities of GPCTR0. */
    

    iStatus = DIG_Block_PG_Config(iDevice, iDOGroup, iPGmodeOn,
     iDOReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    /* The buffer will be written once and then regenerated. */

    iStatus = DIG_DB_Config(iDevice, iDOGroup, iDBmodeON,
     iRegenAllowed, iNoPartialTransfer);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_DB_Config",
     iIgnoreWarning);

    /* Configure Digital Input */

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, iGroupSize, iPort,
     iInGroupDirection);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Config",
     iIgnoreWarning);

    iStatus = DIG_Grp_Mode(iDevice, iDIGroup, 0, iDIEdge, 0, 0, 0);
    

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Grp_Mode",
     iIgnoreWarning);

    /* Correlate the input to the external clock.  Note, in this
     example the same clock is used for both input and output.  If you
     want to use 2 seperate external clocks for input and output, you will
     need to route the 2 signals onto seperate RTSI lines through 2 of the
     3 GPCR0 pins (GPCTR0 Out, GPCTR0 Source, GPCTR0 Gate) using the
     Select_Signal function.  You will also need to pass the right
     parameter value for reqSource into the DIG_Block_PG_Config function
     so that the RTSI line used matches the one used in the Select_Signal
     function call.  When using 2 external clocks in this manner, you will
     lose all functionality of GPCTR0. */

    iStatus = DIG_Block_PG_Config(iDevice, iDIGroup, iPGmodeOn,
     iDIReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    iStatus = DIG_DB_Config(iDevice, iDIGroup, iDBmodeON, iNoRegen,
     iNoPartialTransfer);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_DB_Config",
     iIgnoreWarning);

    /* Start acquiring and generating data. */

    iStatus = DIG_Block_Out(iDevice, iDOGroup, iDOBuffer, ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_Out",
     iIgnoreWarning);

    iStatus = DIG_Block_In(iDevice, iDIGroup, iDIBuffer, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Block_In",
     iIgnoreWarning);

    printf(" Apply your external clock signal now.\n");

    /* Loop until 'iHalfBufsToRead' half buffers are acquired. HINT:
     You can be doing other foreground tasks during this time. */
    

    printf(" HINT: You can add your own graphing calls in the while loop.\n");

    while ((iLoopCount < iHalfBufsToRead) && (iStatus == 0)) {

        

        iStatus = DIG_DB_HalfReady(iDevice, iDIGroup, &iHalfReady);
        

        if ((iHalfReady == 1) && (iStatus == 0)) {


            iStatus = DIG_DB_Transfer(iDevice, iDIGroup,
             iDIHalfBuffer, ulHalfCount);

            iRetVal = NIDAQErrorHandler(iStatus, "DIG_DB_Transfer",
             0);

            ++iLoopCount;;

            printf(" %d Half buffers acquired.\n", iLoopCount);

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
