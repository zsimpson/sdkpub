/*********************************************************************
*
* Example program: 
*    SCXI_AIonePoint.c
*
* Description: 
*    Read one channel, one point at a time, immediately from an SCXI
*     analog input module.  This example can easily be extended to be
*     useable with an SCXI-1140 module, utilizing the Track-and-Hold
*     capabilities.
*
* Example Category: 
*    SCXI
*
* Example Task Types: 
*    1PT, 1CH, IMMED
*
* List of key parameters: 
*    iOnDevChan, iChassisID, iModuleSlot, iModuleChan
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    SCXI_Load_Config, NIDAQErrorHandler, SCXI_Single_Chan_Setup,
*     NIDAQDelay, AI_Read, SCXI_Scale
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signal to channel 0 of your SCXI module in
*     chassis 1, slot 1.  Make sure the connection to your DAQ device
*     is setup correctly.
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
    i16 iOnDevChan = 0;
    i16 iOnDevGain = 1;
    i16 iReading = 0;
    i16 iChassisID = 1;
    i16 iModuleSlot = 1;
    i16 iModuleChan = 0;
    f64 dSCXIgain = 1.0;
    f64 dTermBlockGain = 1.0;
    f64 dSCXIvoltage = 0.0;
    i16 iIgnoreWarning = 0;

    iStatus = SCXI_Load_Config(iChassisID);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Load_Config",
     iIgnoreWarning);

    /* Specify SCXI module and channel to sample. */

    iStatus = SCXI_Single_Chan_Setup(iChassisID, iModuleSlot,
     iModuleChan, iDevice);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Single_Chan_Setup",
     iIgnoreWarning);

    /* You can call SCXI_Set_Gain before AI_Read to change the gain on
     the SCXI module or SCXI channel, depending on what the module allows.
      Otherwise, SCXIgain is assumed to be 1.0. */

    /* Some modules require that you call SCXI_Get_Status after
     changing gain but before taking a reading to make sure the gain has
     switched.  The delay call below should then be replaced with
     SCXI_Get_Status. */

    iRetVal = NIDAQDelay(1.0);

    /* If you are using an SCXI-1140 module, call
     SCXI_Track_Hold_Control to put the module in 'Hold' mode at this
     point. */

    iStatus = AI_Read(iDevice, iOnDevChan, iOnDevGain, &iReading);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_Read", iIgnoreWarning);
    

    /* If you are using an SCXI-1140 module, call
     SCXI_Track_Hold_Control to put the module in 'Track' mode at this
     point. */

    /* If you call SCXI_Set_Gain before AI_Read, make sure to change
     the 'dSCXIgain' in SCXI_Scale. */

    iStatus = SCXI_Scale(iChassisID, iModuleSlot, iModuleChan,
     dSCXIgain, dTermBlockGain, iDevice, iOnDevChan, iOnDevGain, 1,
     &iReading, &dSCXIvoltage);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Scale",
     iIgnoreWarning);

    printf(" The SCXI voltage is %lf volts.\n", dSCXIvoltage);


}

/* End of program */
