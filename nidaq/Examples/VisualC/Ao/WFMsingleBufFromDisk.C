/*********************************************************************
*
* Example program: 
*    WFMsingleBufFromDisk.c
*
* Description: 
*    Outputs a waveform from one analog output channel, using data on a
*     disk file (DAQdata.DAT). You can use the datafile from the
*     'DAQsingleBuftoDisk' example program. (uses high-level NI-DAQ
*     functions)
*
* Example Category: 
*    AO
*
* Example Task Types: 
*    BUF, 1CH, BURST, SYNC, INTTIM, INTTRIG, DISK
*
* List of key parameters: 
*    ulStartPt, ulEndPt, ulIterations
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Timeout_Config, NIDAQErrorHandler, WFM_from_Disk
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output signal will be available at AO channel 0. The
*     default analog output mode for the DAQ device will be used.
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
    i16 iNumChans = 1;
    static i16 piChanVect[1] = {0};
    char* strFilename = "DAQdata.dat";
    u32 ulStartPt = 1;
    u32 ulEndPt = 0;
    u32 ulIterations = 1;
    f64 dUpdateRate = 1000.0;
    i16 iIgnoreWarning = 0;
    i32 lTimeout = 180;

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the WFM_from_Disk call.
      You may want to change the value of lTimeout if your data file is
     large. */

    iStatus = Timeout_Config(iDevice, lTimeout);

    iRetVal = NIDAQErrorHandler(iStatus, "Timeout_Config",
     iIgnoreWarning);

    printf(" This program will read data from a file called DAQdata.dat.\n");

    printf(" It will output the waveform data at a rate of %lf updates/sec.\n", dUpdateRate);

    /* Generate data from the entire file, by setting ulEndPt to 0. */
    

    /* WARNING: Make sure you have the data file from the DAQtoDSK
     example program first! */

    iStatus = WFM_from_Disk(iDevice, iNumChans, piChanVect,
     strFilename, ulStartPt, ulEndPt, ulIterations, dUpdateRate);

    iRetVal = NIDAQErrorHandler(iStatus, "WFM_from_Disk",
     iIgnoreWarning);

    if (iStatus == 0) {


        printf(" The waveform generation is done!\n");

    }


    /* Disable timeouts. */

    iStatus = Timeout_Config(iDevice, -1);


}

/* End of program */
