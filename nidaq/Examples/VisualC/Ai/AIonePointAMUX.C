/*********************************************************************
*
* Example program: 
*    AIonePointAMUX.c
*
* Description: 
*    Read a set of channels from an AMUX-64T
*
* Example Category: 
*    AI
*
* Example Task Types: 
*    1PT, NCH, IMMED
*
* List of key parameters: 
*    iNumMuxBrds, iChan
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    AI_Mux_Config, NIDAQErrorHandler, AI_VRead
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your analog signal to AI channel 1 of the AMUX-64T. This
*     program is configured for use with only one AMUX-64T. The default
*     analog input mode for the DAQ device will be used.
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
    i16 iNumMuxBrds = 1;
    i16 iChan = 1;
    i16 iGain = 1;
    f64 dVoltage = 0.0;
    i16 iIgnoreWarning = 0;

    /* This configures the DAQ device for use with one AMUX-64T. */
    

    iStatus = AI_Mux_Config(iDevice, iNumMuxBrds);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_MUX_Config",
     iIgnoreWarning);

    /* NOTE: If you have a device with more than 16 AI channels, make
     sure you call the MIO_Config function and set the 'useAMUX' paramter
     to 1 at this point. */

    /* The 'iChan' here refers to the channels on the AMUX-64T. */

    iStatus = AI_VRead(iDevice, iChan, iGain, &dVoltage);

    iRetVal = NIDAQErrorHandler(iStatus, "AI_VRead", iIgnoreWarning);
    

    /* CLEANUP - Don't check for errors on purpose. */

    /* NOTE: If you have a device with more than 16 AI channels, make
     sure you call the MIO_Config function and reset the 'useAMUX'
     paramter to 0 at this point. */

    /* Reset number of AMUX boards. */

    iStatus = AI_Mux_Config(iDevice, 0);

    printf(" The voltage at AMUX AI channel %d is %lf volts.\n", iChan, dVoltage);


}

/* End of program */
