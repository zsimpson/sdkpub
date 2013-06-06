/*********************************************************************
*
* Example program: 
*    TIOcircularBufPositionMeasure.c
*
* Description: 
*    Counts the number of quadrature encoded digital pulses
*     continuously into a circular-buffer (or double-buffer) using a
*     general purpose counter 0 in a loop. Also accepts a Z-index pulse
*     so that the counter initializes automatically (for NI-TIO based
*     devices)
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulZIndexCount, pulBuffer, pulReadBuf, ulCount,
*     ulReadCount
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, Line_Change_Attribute,
*     GPCTR_Config_Buffer, GPCTR_Read_Buffer, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your encoder channel A signal to the default source pin
*     (PFI 39), the channel B signal to the default auxiliary line (PFI
*     37), and the Z-index pulse signal to the default gate pin (PFI
*     38). Connect a gating pulse train to the GATE pin of counter 1
*     (PFI_34). Also, connect the ground reference to the DIG GND pin.
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
    u32 ulGpctrNum = ND_COUNTER_0;
    u32 ulZIndexCount = 0;
    static u32 pulBuffer[100] = {0};
    static u32 pulReadBuf[50] = {0};
    u32 ulCount = 100;
    u32 ulReadCount = 50;
    i16 iLoopCount = 10;
    u32 ulInitCount = 0;
    u32 ulNumPtsToRead = 50;
    u32 ulNumPtsRead = 0;
    u32 ulReadOffset = 0;
    u32 ulTimeOut = 5;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET",
     iIgnoreWarning);

    /* Setup for a buffered position measurement application. */

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_BUFFERED_POSITION_MSR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    /* Setup the encoder type for Quadrature Encoder (X1) measurement.
     You can change this to X2 or X4 if you wish. */

    GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_ENCODER_TYPE,
     ND_QUADRATURE_ENCODER_X1);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/QUADRATURE_ENCODER_X1", iIgnoreWarning);

    /* Activate a Z-index pulse to reset the counter to an initial
     value, specified by 'ulZIndexCount' later. */

    GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_Z_INDEX_ACTIVE,
     ND_YES);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/Z_INDEX_PULSE", iIgnoreWarning);

    /* Specify the value that gets loaded when a Z-index pulse
     arrives. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_Z_INDEX_VALUE, ulZIndexCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/Z-INDEX_COUNT", iIgnoreWarning);

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulInitCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    /* Signals from quadrature encoders often have noise and glitches
     that result in measurement errors. Setup 5 usec filtering on each
     input from the quadrature encoder. */

    /* Setup filter for Channel A. */

    iStatus = Line_Change_Attribute(iDevice, ND_PFI_39,
     ND_LINE_FILTER, ND_5_MICROSECONDS);

    iRetVal = NIDAQErrorHandler(iStatus,
     "Line_Change_Attribute/ND_PFI_39", iIgnoreWarning);

    /* Setup filter for Channel B. */

    iStatus = Line_Change_Attribute(iDevice, ND_PFI_37,
     ND_LINE_FILTER, ND_5_MICROSECONDS);

    iRetVal = NIDAQErrorHandler(iStatus,
     "Line_Change_Attribute/ND_PFI_37", iIgnoreWarning);

    /* Setup filter for Z-index Channel. */

    iStatus = Line_Change_Attribute(iDevice, ND_PFI_38,
     ND_LINE_FILTER, ND_5_MICROSECONDS);

    iRetVal = NIDAQErrorHandler(iStatus,
     "Line_Change_Attribute/ND_PFI_38", iIgnoreWarning);

    /* Each time a pulse arrives in the gate, a new value will be
     latched into the counter and sent to the data buffer. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ND_PFI_34);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    /* Enable double-buffer mode. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_BUFFER_MODE, ND_DOUBLE);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/BUFFERMODE", iIgnoreWarning);

    iStatus = GPCTR_Config_Buffer(iDevice, ulGpctrNum, 0, ulCount,
     pulBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Config_Buffer",
     iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    printf(" Connect the encoder Channel A signal to PFI 39.\n");

    printf(" Connect the encoder Channel B signal to PFI 37.\n");

    printf(" Connect the Z-index signal to PFI 38.\n");

    printf(" Apply your gating pulse train to PFI 34.\n");

    /* Loop 10 times. */

    do {


        iStatus = GPCTR_Read_Buffer(iDevice, ulGpctrNum, ND_READ_MARK,
         ulReadOffset, ulNumPtsToRead, ulTimeOut, &ulNumPtsRead, pulReadBuf);
        

        --iLoopCount;

        printf(" %lu points read into buffer 'pulReadBuf' (loop count %d ).\n", ulNumPtsRead, iLoopCount);

        /* Print out the firt point in the buffer. */

        printf(" Current encoder position is at %ld\n", pulReadBuf[0]);

        iRetVal = NIDAQYield(iYieldON);

    } while ((iLoopCount > 0) && (iStatus >= 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Read_Buffer",
     iIgnoreWarning);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Clear filter settings. */

    iStatus = Line_Change_Attribute(iDevice, ND_PFI_39,
     ND_LINE_FILTER, ND_NONE);

    iStatus = Line_Change_Attribute(iDevice, ND_PFI_37,
     ND_LINE_FILTER, ND_NONE);

    iStatus = Line_Change_Attribute(iDevice, ND_PFI_38,
     ND_LINE_FILTER, ND_NONE);

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    printf(" Done with circular buffered position measurement!\n");


}

/* End of program */
