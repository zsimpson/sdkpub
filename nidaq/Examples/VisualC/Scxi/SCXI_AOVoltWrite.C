/*********************************************************************
*
* Example program: 
*    SCXI_AOVoltWrite.c
*
* Description: 
*    Output a single analog voltage from an SCXI analog output module,
*     immediately (5 Volts, then 0 volts)
*
* Example Category: 
*    SCXI
*
* Example Task Types: 
*    1PT, 1CH, IMMED
*
* List of key parameters: 
*    iChassisID, iModuleSlot, iChan, iOpCode, iRangeCode
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    SCXI_Load_Config, NIDAQErrorHandler, SCXI_AO_Write
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your analog output voltage signal will be on channel 0 of the SCXI
*     analog output module in chassis 1, slot 1.  Connect your ground
*     reference as well. Make sure the connection to your DAQ device is
*     setup correctly.
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
    i16 iChassisID = 1;
    i16 iModuleSlot = 1;
    i16 iChan = 0;
    i16 iOpCode = 0;
    i16 iRangeCode = 2;
    f64 dVoltData1 = 5.0;
    f64 dVoltData2 = 0.0;
    i16 iBinWritten = 0;
    i16 iIgnoreWarning = 0;

    iStatus = SCXI_Load_Config(iChassisID);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Load_Config",
     iIgnoreWarning);

    /* First, set the voltage to dVoltData1. */

    iStatus = SCXI_AO_Write(iChassisID, iModuleSlot, iChan, iOpCode,
     iRangeCode, dVoltData1, 0, &iBinWritten);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_AO_Write",
     iIgnoreWarning);

    /* Then, set the voltage to dVoltData2. */

    iStatus = SCXI_AO_Write(iChassisID, iModuleSlot, iChan, iOpCode,
     iRangeCode, dVoltData2, 0, &iBinWritten);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_AO_Write",
     iIgnoreWarning);


}

/* End of program */
