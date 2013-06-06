/*********************************************************************
*
* Example program: 
*    CDISinglePointClockedByCounter.c
*
* Description: 
*    Reads digital data from the input FIFO one point at a time at a
*     rate of 100 Hz.  The 100 Hz clock used here is supplied by
*     general purpose counter 0.
*
* Example Category: 
*    CDIO
*
* Example Task Types: 
*    1PT, NCH
*
* List of key parameters: 
*    ulCount, iDIReqSource, ulGpctrNum, ulGpctrOutput, ulLOWcount,
*     ulHIGHcount
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DIG_Line_Config, NIDAQErrorHandler, DIG_Grp_Config, DIG_Grp_Mode,
*     DIG_Block_PG_Config, Select_Signal, GPCTR_Control,
*     GPCTR_Set_Application, GPCTR_Change_Parameter, DIG_Grp_Status,
*     DIG_In_Grp
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital input signals to pins DIO0-7. Connect the
*     ground reference to the DIG GND pin. (please refer to your
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
    u32 ulCount = 500;
    u32 ulLoopCount = 0;
    i16 iLineCount = 0;
    i16 iGroupSize = 1;
    i16 iPort = 0;
    i16 iNumLines = 8;
    i16 iIgnoreWarning = 0;
    i16 iReady = 0;
    i16 iPGmodeOn = 1;
    i16 iDIGroup = 1;
    i16 iDIReqSource = 3;
    i16 iInLineDirection = 4;
    i16 iInGroupDirection = 0;
    i16 iDIEdge = 0;
    i16 iDataPoint = 0;
    u32 ulGpctrNum = ND_COUNTER_0;
    u32 ulGpctrOutput = ND_GPCTR0_OUTPUT;
    u32 ulLOWcount = 500;
    u32 ulHIGHcount = 500;

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

    /* Correlate the input to the signal coming across the RTSI 0
     line. */

    iStatus = DIG_Block_PG_Config(iDevice, iDIGroup, iPGmodeOn,
     iDIReqSource, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "Dig_Block_PG_Config",
     iIgnoreWarning);

    /* Route the output of GPCTR0 to RTSI 0 */

    iStatus = Select_Signal(iDevice, ND_RTSI_0, ND_GPCTR0_OUTPUT,
     ND_DONT_CARE);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal",
     iIgnoreWarning);

    /* Setup counter 0 to output a 100 Hz square wave. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_PULSE_TRAIN_GNR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_100_KHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_COUNT_1,
     ulLOWcount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/COUNT1", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_COUNT_2,
     ulHIGHcount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning);

    /* To output a counter pulse, you must call Select_Signal. */

    iStatus = Select_Signal(iDevice, ulGpctrOutput, ulGpctrOutput,
     ND_LOW_TO_HIGH);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal/GpctrOutput",
     iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    printf(" Square wave generation started...\n");

    /* Input ulCount number of points. */

    while ((ulLoopCount < ulCount) && (iStatus == 0)) {


        iStatus = DIG_Grp_Status(iDevice, iDIGroup, &iReady);

        if ((iReady == 1) && (iStatus == 0)) {


            iStatus = DIG_In_Grp(iDevice, iDIGroup, &iDataPoint);
            

            iRetVal = NIDAQErrorHandler(iStatus, "DIG_In_Grp", 0);
            

            ++ulLoopCount;;

        }


        iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Status", 0);
        

    }


    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    /* Disconnect GPCTR0_OUTPUT. */

    iStatus = Select_Signal(iDevice, ND_GPCTR0_OUTPUT, ND_NONE,
     ND_DONT_CARE);

    /* Remove any signal from RTSI 0. */

    iStatus = Select_Signal(iDevice, ND_RTSI_0, ND_NONE,
     ND_DONT_CARE);

    iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal",
     iIgnoreWarning);

    /* Clear all operations and reset the board to its default state
     */

    iStatus = DIG_Grp_Config(iDevice, iDIGroup, 0, 0, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Grp_Config",
     iIgnoreWarning);


}

/* End of program */
