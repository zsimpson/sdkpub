/*********************************************************************
*
* Example program: 
*    Calibrate_Eseries.c
*
* Description: 
*    Calibrate an E-series board using internal voltage reference
*     (SELF_CALIBRATE) and store calibration constants in
*     USER_EEPROM_AREA. (E-series only)  This example also takes
*     measurements over 50/60Hz sinewave periods and averages the data
*     before and after calibration, so you can compare.
*
* Example Category: 
*    CALIB
*
* Example Task Types: 
*    ESER, BUF, 1CH, SYNC, INTTIM
*
* List of key parameters: 
*    piBuffer, dSampRate, ulCalOp, ulSetOfCalConst
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    DAQ_Op, NIDAQErrorHandler, NIDAQMean, Calibrate_E_Series
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Ground the inputs to AI channel 1.  If the device is in
*     differential mode, tie both the + and - inputs to AIGND. If the
*     device is in single-ended mode, tie the input to AIGND.
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
    i16 iChan = 1;
    i16 iGain = 1;
    static i16 piBuffer[600] = {0};
    u32 ulCount = 100;
    f64 dSampRate = 600.0;
    u32 ulCalOp = ND_SELF_CALIBRATE;
    u32 ulSetOfCalConst = ND_USER_EEPROM_AREA;
    f64 dMean = 0.0;
    i16 iIgnoreWarning = 1;

    /* Acquire data before calibration. */

    printf(" ...\n");

    printf(" Measuring offset at AI channel %d before calibration.\n", iChan);

    printf(" NOTE: Make sure the inputs are grounded.\n");

    iStatus = DAQ_Op(iDevice, iChan, iGain, piBuffer, ulCount,
     dSampRate);

    iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Op", iIgnoreWarning);
    

    iRetVal = NIDAQMean(piBuffer, ulCount, WFM_DATA_I16, &dMean);

    printf(" The offset at AI channel %d before calibration is %lf ADC units binary.\n", iChan, dMean);

    /* Calibrate E-series device. */

    printf(" ...Starting E-series calibration...this may take a while.\n");

    iStatus = Calibrate_E_Series(iDevice, ulCalOp, ulSetOfCalConst,
     0.0);

    iRetVal = NIDAQErrorHandler(iStatus, "Calibrate_E_Series",
     iIgnoreWarning);

    if (iStatus == 0) {


        printf(" ...E-series calibration completed!\n");

        /* Acquire data AFTER calibration. */

        printf(" Measuring offset at AI channel %d AFTER calibration.\n", iChan);

        printf(" NOTE: Make sure the inputs are grounded.\n");

        iStatus = DAQ_Op(iDevice, iChan, iGain, piBuffer, ulCount,
         dSampRate);

        iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Op",
         iIgnoreWarning);

        iRetVal = NIDAQMean(piBuffer, ulCount, WFM_DATA_I16, &dMean);
        

        printf(" The offset at AI channel %d AFTER calibration is %lf ADC units binary.\n", iChan, dMean);

    }
    else {

        printf(" An error occurred during calibration. Please check errors.\n");

    }



}

/* End of program */
