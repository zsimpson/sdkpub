/*********************************************************************
*
* Example program: 
*    DAQsingleBufToDisk.c
*
* Description: 
*    Read a waveform from one analog input channel and store the binary
*     data to a file (DAQdata.DAT) (uses high-level NI-DAQ functions)
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    BUF, 1CH, BURST, INTTIM, SYNC, INTTRIG, DISK
*
* List of key parameters: 
*    strFilename
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    Timeout_Config, NIDAQErrorHandler, DAQ_to_Disk
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signal to AI channel 1. The default analog
*     input mode for the DAQ device will be used.
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
    i16 iChan = 1;
    i16 iGain = 1;
    f64 dSampRate = 1000.0;
    u32 ulCount = 1000;
    char* strFilename = "DAQdata.DAT";
    i16 iIgnoreWarning = 0;

    /* This sets a timeout limit (#Sec * 18ticks/Sec) so that if there
     is something wrong, the program won't hang on the DAQ_to_Disk call.
     */

    iStatus = Timeout_Config(iDevice, lTimeout);

    iRetVal = NIDAQErrorHandler(iStatus, "Timeout_Config",
     iIgnoreWarning);

    /* Acquire data from a single channel and store to disk. The data
     is stored in 16-bit little endian binary form. You can make your own
     file I/O calls to read them, or use the WFMfrDisk program to output
     the same data. */

    /* HINT: If you are using a Lab or 1200 series device, replace
     this function with Lab_ISCAN_to_Disk. */

    iStatus = DAQ_to_Disk(iDevice, iChan, iGain, strFilename, ulCount,
     dSampRate, 0);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_to_Disk",
     iIgnoreWarning);

    if (iStatus == 0) {


        printf(" Acquired data successfully stored to file: %s\n", strFilename);

    }


    /* Disable timeouts. */

    iStatus = Timeout_Config(iDevice, -1);


}

/* End of program */
