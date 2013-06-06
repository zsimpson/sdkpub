/*********************************************************************
*
* Example program: 
*    SCXI_FREQonePoint.c
*
* Description: 
*    Read one channel, one point at a time, immediately from an
*     SCXI-1126 frequency input module.  This example adds special
*     function calls to set input frequency range, cutoff frequency and
*     voltage threshold (2.1V for TTL). (Only for the SCXI-1126 module)
*
* Example Category: 
*    SCXI
*
* Example Task Types: 
*    BUF, 1CH, IMMED, FREQM
*
* List of key parameters: 
*    iOnDevChan, iChassisID, iModuleSlot, iModuleChan, dSCXIfreqRange,
*     dThreshHold, dHysteresis, iFilterMode, dFilterFreq
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    SCXI_Load_Config, NIDAQErrorHandler, SCXI_Single_Chan_Setup,
*     SCXI_Set_Gain, SCXI_Configure_Filter, SCXI_Set_Threshold, DAQ_Op,
*     SCXI_Scale, NIDAQPlotWaveform, NIDAQMean
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
    u32 ulCount = 100;
    static i16 piReadings[100] = {0};
    i16 iChassisID = 1;
    i16 iModuleSlot = 1;
    i16 iModuleChan = 0;
    f64 dSCXIfreqRange = 1000.0;
    f64 dTermBlockGain = 1.0;
    static f64 pdSCXIfrequencies[100] = {0.0};
    f64 dSCXIavgFrequency = 0.0;
    f64 dThreshHold = 2.1;
    f64 dHysteresis = 0.1;
    i16 iIgnoreWarning = 0;
    i16 iFilterMode = 1;
    f64 dFilterFreq = 1.0;
    u16 uCutoffDivDown = 0;
    u16 uOutClkDivDown = 0;
    f64 dActualFilterFreq = 0;
    f64 dSampRate = 1000.0;

    iStatus = SCXI_Load_Config(iChassisID);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Load_Config",
     iIgnoreWarning);

    /* Specify SCXI module and channel to sample. */

    iStatus = SCXI_Single_Chan_Setup(iChassisID, iModuleSlot,
     iModuleChan, iDevice);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Single_Chan_Setup",
     iIgnoreWarning);

    /* Specify input frequency range using SCXI_Set_Gain. */

    iStatus = SCXI_Set_Gain(iChassisID, iModuleSlot, iModuleChan,
     dSCXIfreqRange);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Set_Gain",
     iIgnoreWarning);

    /* Set up cutoff frequency for the filter on the freq-to-voltage
     module.  You can only use iFilterMode = 1. */

    iStatus = SCXI_Configure_Filter(iChassisID, iModuleSlot,
     iModuleChan, iFilterMode, dFilterFreq, uCutoffDivDown,
     uOutClkDivDown, &dActualFilterFreq);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Configure_Filter",
     iIgnoreWarning);

    /* Specify voltage threshold for freq-to-voltage converter. The
     threshold setting determines what the freq-to-voltage converter
     regards as another pulse. */

    iStatus = SCXI_Set_Threshold(iChassisID, iModuleSlot, iModuleChan,
     dThreshHold, dHysteresis);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Set_Threshold",
     iIgnoreWarning);

    /* Acquire data into binary array. */

    iStatus = DAQ_Op(iDevice, iOnDevChan, iOnDevGain, piReadings,
     ulCount, dSampRate);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Op", iIgnoreWarning);
    

    /* Scale binary data to frequency values. */

    iStatus = SCXI_Scale(iChassisID, iModuleSlot, iModuleChan,
     dSCXIfreqRange, dTermBlockGain, iDevice, iOnDevChan, iOnDevGain,
     ulCount, piReadings, pdSCXIfrequencies);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Scale",
     iIgnoreWarning);

    iRetVal = NIDAQPlotWaveform(pdSCXIfrequencies, ulCount,
     WFM_DATA_F64);

    NIDAQMean(pdSCXIfrequencies, ulCount, WFM_DATA_F64,
     &dSCXIavgFrequency);

    printf(" The average frequency is %lf Hz.\n", dSCXIavgFrequency);


}

/* End of program */
