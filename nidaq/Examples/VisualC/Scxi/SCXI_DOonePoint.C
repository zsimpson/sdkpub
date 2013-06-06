/*********************************************************************
*
* Example program: 
*    SCXI_DOonePoint.c
*
* Description: 
*    Outputs a HIGH(ON) and LOW(OFF) to a single digital line/relay on
*     an SCXI digital output module, immediately
*
* Example Category: 
*    SCXI
*
* Example Task Types: 
*    1PT, 1CH, IMMED
*
* List of key parameters: 
*    iChassisID, iModuleSlot, iChan
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    SCXI_Load_Config, NIDAQErrorHandler, SCXI_Set_State, NIDAQDelay
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital signal will be on channel 0 of the SCXI digital
*     output module in chassis 1, slot 1. Connect your ground reference
*     as well. Make sure the connection to your DAQ device is setup
*     correctly. Note that some digital input modules may require an
*     external voltage source for Vcc.
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
    i16 iPort = 0;
    i16 iChan = 0;
    u32 ulDataON = 1;
    u32 ulDataOFF = 0;
    i16 iIgnoreWarning = 0;

    iStatus = SCXI_Load_Config(iChassisID);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Load_Config",
     iIgnoreWarning);

    /* Toggle the state of the digital line.  If you set 'iChan' to
     -1, you can set the entire port. */

    iStatus = SCXI_Set_State(iChassisID, iModuleSlot, iPort, iChan,
     ulDataON);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Set_State",
     iIgnoreWarning);

    /* Wait 1 sec (for slower modules). */

    iRetVal = NIDAQDelay(1.0);

    iStatus = SCXI_Set_State(iChassisID, iModuleSlot, iPort, iChan,
     ulDataOFF);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Set_State",
     iIgnoreWarning);


}

/* End of program */
