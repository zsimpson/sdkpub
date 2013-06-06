/*********************************************************************
*
* Example program: 
*    SCXI_DIonePoint.c
*
* Description: 
*    Reads the state of a single digital line/relay on an SCXI digital
*     input module, immediately
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
*    SCXI_Load_Config, NIDAQErrorHandler, SCXI_Get_State
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital signal to the SCXI digital input module in
*     chassis 1, slot 1.  Connect your ground reference as well.  Make
*     sure the connection to your DAQ device is setup correctly.  Note
*     that some digital input modules may require an external voltage
*     source for Vcc.
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
    u32 ulData = 0;
    i16 iIgnoreWarning = 0;

    iStatus = SCXI_Load_Config(iChassisID);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Load_Config",
     iIgnoreWarning);

    /* Get the state of the digital line.  If you set 'iChan' to -1,
     you can read the entire port. */

    iStatus = SCXI_Get_State(iChassisID, iModuleSlot, iPort, iChan,
     &ulData);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Get_State",
     iIgnoreWarning);

    printf(" Data at line %d is %lu\n", iChan, ulData);


}

/* End of program */
