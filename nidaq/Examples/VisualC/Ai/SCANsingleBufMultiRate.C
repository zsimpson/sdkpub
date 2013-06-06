/*********************************************************************
*
* Example program: 
*    SCANsingleBufMultiRate.c
*
* Description: 
*    Read a waveform from three analog input channels at per-channel
*     scan rate divisors of 1:2:4:8 (uses low-level NI-DAQ functions)
*     NOTE: There are quite a few hardware limitations depending on
*     devices when using this example.  Refer to the description for
*     the SCAN_Sequence_Setup function for details.
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    BUF, NCH, BURST, INTTIM, ASYNC, INTTRIG
*
* List of key parameters: 
*    lTimeout, dSampRate, dScanRate, piScanRateDivVect,
*     pulSampsPerChanVect
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    SCAN_Sequence_Setup, NIDAQErrorHandler, SCAN_Sequence_Retrieve,
*     DAQ_Rate, SCAN_Start, DAQ_Check, SCAN_Sequence_Demux, DAQ_VScale,
*     NIDAQPlotWaveform, DAQ_Clear
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signals to AI channels 1,2,3 and 4. The
*     default analog input mode for the DAQ device will be used.
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
    i32 lTimeout = 180;
    i16 iNumMUXBrds = 0;
    i16 iNumChans = 4;
    i16 iChan = 1;
    i16 iGain = 1;
    f64 dSampRate = 20000.0;
    f64 dScanRate = 1000.0;
    i16 iSampTB = 0;
    u16 uSampInt = 0;
    i16 iScanTB = 0;
    u16 uScanInt = 0;
    u32 ulCount = 480;
    f64 dGainAdjust = 1.0;
    f64 dOffset = 0.0;
    static i16 piChanVect[4] = {1, 2, 3, 4};
    static i16 piGainVect[4] = {1, 1, 1, 1};
    static i16 piScanRateDivVect[4] = {1, 2, 4, 8};
    static i16 piScanSeqVect[512] = {0};
    static u32 pulSampsPerChanVect[4] = {0};
    i16 iScansPerSeq = 0;
    i16 iSampsPerSeq = 0;
    i16 iDAQstopped = 0;
    u32 ulNumPtsAcquired = 0;
    static i16 piBuffer[1000] = {0};
    static f64 pdVoltBuffer[1000] = {0.0};
    i16 iIgnoreWarning = 0;

    /* HINT: if you want to change the parameters for this example,
     please make sure that (1) the size of 'piScanSeqVect' is at least
     'iSampsPerSeq', (2) 'ulCount' must be a multiple of 'iSampsPerSeq'.
     The size of 'piScanSeqVect' has been set to 512 in this example to
     accommodate the MuxGain memory on most DAQ devices. */
    

    /* Setup for multiple rate scanning. */

    iStatus = SCAN_Sequence_Setup(iDevice, iNumChans, piChanVect,
     piGainVect, piScanRateDivVect, &iScansPerSeq, &iSampsPerSeq);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Sequence_Setup",
     iIgnoreWarning);

    /* Obtain the scan sequence vector sometime before de-multiplexing
     acquired data. */

    iStatus = SCAN_Sequence_Retrieve(iDevice, iSampsPerSeq,
     piScanSeqVect);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Sequence_Retrieve",
     iIgnoreWarning);

    iStatus = DAQ_Rate(dSampRate, 0, &iSampTB, &uSampInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Rate/SampRate",
     iIgnoreWarning);

    iStatus = DAQ_Rate(dScanRate, 0, &iScanTB, &uScanInt);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Rate/ScanRate",
     iIgnoreWarning);

    /* Acquire data from multiple channels using interval scanning
     (both 'dSampRate' and 'dScanRate' are non-zero. NOTE: 'ulCount' must
     be an integer multiple of 'iSampsPerSeq'. */

    iStatus = SCAN_Start(iDevice, piBuffer, ulCount, iSampTB,
     uSampInt, iScanTB, uScanInt);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Start",
     iIgnoreWarning);

    while ((iDAQstopped == 0) && (iStatus == 0)) {


        iStatus = DAQ_Check(iDevice, &iDAQstopped, &ulNumPtsAcquired);
        

    }


    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Check", iIgnoreWarning);
    

    /* Demultiplex (re-order) acquired data. */

    iStatus = SCAN_Sequence_Demux(iNumChans, piChanVect, ulCount,
     piBuffer, iSampsPerSeq, piScanSeqVect, pulSampsPerChanVect);

    iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Sequence_Demux",
     iIgnoreWarning);

    /* If you have different gains for each channel, you must call
     this for each channel as well.  The SCAN_Sequence_Demux function
     gives information that will help you with scaling.  The
     'pulSampsPerChanVector' array gives a hint as to how the data from
     each scan is arranged. In this particular example of 4 channels
     (1,2,3,4) with scan rate divisors of 1, 2, 4, and 8, the
     'pulSampsPerChanVector' array will contain the values 8, 4, 2, and 1.
     That indicates that the first 8 samples are from chan 1, the next 4
     samples are from chan 2, the next 2 samples are from chan 3, and the
     last sample is from chan 4.  Refer to the SCAN_Sequence_Demux
     function description for more details. */

    iStatus = DAQ_VScale(iDevice, iChan, iGain, dGainAdjust, dOffset,
     ulCount, piBuffer, pdVoltBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale",
     iIgnoreWarning);

    printf(" The plot shows all channel data in order.\n");

    /* Plot acquired data */

    iRetVal = NIDAQPlotWaveform(pdVoltBuffer, ulCount, WFM_DATA_F64);
    

    printf(" The data is available in 'pdVoltBuffer'.\n");

    /* CLEANUP - Don't check for errors on purpose. */

    iStatus = DAQ_Clear(iDevice);


}

/* End of program */
