/*********************************************************************
*
* Example program: 
*    SCXI_SCANsingleBuf.c
*
* Description: 
*    Read 4 channels at the SAME gain from an SCXI analog input module
*     into a buffer, using internal scan and sample timing. The DAQ
*     device must have a scan clock and a channel clock. NOTE: This
*     example is NOT suitable for the SCXI-1122 module, which uses a
*     relay multiplexer.  For the SCXI-1122 module, sample a buffer of
*     data on one channel, then call SCXI_Change_Chan to sample another
*     channel. Also, if you are using this example with an SCXI-1100,
*     make sure the filter setting is set to NO FILTER, so that the
*     signals can settle properly.
*
* Example Category: 
*    SCXI
*
* Example Task Types: 
*    BUF, NCH, INTTIM, SYNC
*
* List of key parameters: 
*    iNumModules, piModuleList, piNumChans, piStartChans, iMuxCtrON,
*     uCtrValue
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    SCXI_Load_Config, NIDAQErrorHandler, SCXI_SCAN_Setup,
*     Timeout_Config, SCXI_MuxCtr_Setup, SCAN_Op, SCAN_Demux,
*     SCXI_Scale, NIDAQPlotWaveform
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signals to channels 0 through 3 of your SCXI
*     module in chassis 1, slot 1. Make sure the connection to your DAQ
*     device is setup correctly.
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
    i16 iNumModules = 1;
    static i16 piModuleList[1] = {1};
    i16 iModuleSlot = 1;
    i16 iNumDevChans = 1;
    static i16 piNumChans[1] = {4};
    i16 iNumSCXIChans = 4;
    static i16 piStartChans[1] = {0};
    i16 iDevice = 1;
    i16 lTimeout = 180;
    i16 iMuxCtrON = 1;
    i16 iMuxCtrOFF = 0;
    i16 iScanDiv = 1;
    u16 uCtrValue = 4;
    i16 iOnDevChan = 0;
    i16 iOnDevGain = 1;
    static i16 piOnDevChan[1] = {0};
    static i16 piOnDevGain[1] = {1};
    static i16 piBuffer[100] = {0};
    i16 ulCount = 100;
    f64 dSampRate = 10000.0;
    f64 dScanRate = 1000.0;
    f64 dSCXIgain = 1.0;
    f64 dTermBlockGain = 1.0;
    static f64 pdVoltBuffer[100] = {0.0};
    i16 iIgnoreWarning = 0;

    iStatus = SCXI_Load_Config(iChassisID);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Load_Config",
     iIgnoreWarning);

    /* Setup hardware scanning on SCXI module. */

    /* NOTE: If you are using the SCXI-1140 module, you can call
     SCXI_Track_Hold_Setup at this point to setup the track-and-hold
     circuitry. */

    iStatus = SCXI_SCAN_Setup(iChassisID, iNumModules, piModuleList,
     piNumChans, piStartChans, iDevice, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_SCAN_Setup",
     iIgnoreWarning);

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the SCAN_Op call. */
    

    iStatus = Timeout_Config(iDevice, lTimeout);

    iRetVal = NIDAQErrorHandler(iStatus, "Timeout_Config",
     iIgnoreWarning);

    iStatus = SCXI_MuxCtr_Setup(iDevice, iMuxCtrON, iScanDiv,
     uCtrValue);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_MuxCtr_Setup",
     iIgnoreWarning);

    /* Scan_Op is called to perform 'interval scanning'. You must use
     a DAQ device that has a 'scan clock'. Some devices may require you to
     use Lab_ISCAN_Op instead. */

    iStatus = SCAN_Op(iDevice, iNumDevChans, piOnDevChan, piOnDevGain,
     piBuffer, ulCount, dSampRate, dScanRate);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Op", iIgnoreWarning);
    

    /* NOTE: If you are using the SCXI-1140 module, you can call
     SCXI_Track_Hold_Setup at this point to disable the track-and-hold
     circuitry. */

    iStatus = SCAN_Demux(piBuffer, ulCount, iNumSCXIChans, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Demux",
     iIgnoreWarning);

    /* Since all channels have the same gain, the SCXI_Scale is called
     for all channels.  If you have set different gains for different
     channels, then scale them one channel at a time. */

    iStatus = SCXI_Scale(iChassisID, iModuleSlot, 0, dSCXIgain,
     dTermBlockGain, iDevice, iOnDevChan, iOnDevGain, ulCount, piBuffer,
     pdVoltBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "SCXI_Scale",
     iIgnoreWarning);

    iStatus = SCXI_MuxCtr_Setup(iDevice, iMuxCtrOFF, 0, 0);

    iRetVal = NIDAQPlotWaveform(pdVoltBuffer, ulCount, WFM_DATA_F64);
    

    printf(" The data is available in 'pdVoltBuffer'.\n");

    /* Disable timeouts. */

    iStatus = Timeout_Config(iDevice, -1);


}

/* End of program */
