/*   PI controller ADC DLLs external defintion 
*    workfile:   s:\xsma\xdll\piadcfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/PIADCFCN.H $
*       $Date: 11/08/96 9:12a $
******************************************************************
*
*       piadcfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 11/08/96 9:12a $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/PIADCFCN.H $
*  
*  2     11/08/96 9:12a Bob
*  
*  1     11/08/96 8:19a Charlie
*  
*
*
*
******************************************************************
*/


/*
******************************************************************************
        include files
*/

/*
******************************************************************************
        defines
*/


/* ########################################################### */
/*                  LEVEL 2 DLLs                               */
/* EASY CONTROLLER DLLS : ADC FUNCTION PROTOTYPES              */
/* ########################################################### */



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_controller_ad_converter           */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Controller AD converter                                         */
/* See enum type in piadcdef.h called ADConverter_Type for values. */
PREHEAD int PISTDAPI PICM_Set_controller_ad_converter(int converter);
PREHEAD int PISTDAPI PICM_Get_controller_ad_converter(void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_Set_controller_speed               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* controller timebase in Hz freq                              */
/* See piadcdef.h ctrl_speed for legal values.                 */
PREHEAD int PISTDAPI PICM_Set_controller_speed(int freq); 
PREHEAD int PISTDAPI PICM_Get_controller_speed(void);     

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*            PICM_Get_possible_speeds                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* return int that has ORed in all possible controller speeds. */
/* See piadcdef.h ADC_support_speed for values returned.       */
PREHEAD int PISTDAPI PICM_Get_possible_speeds(void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_controller_adc_resolution         */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Set the ADC resolution of the ADC-converter (i.e. 12 bits). */
/* See enumerated type in piadcdef.h ADC_resolution.           */
PREHEAD int PISTDAPI PICM_Set_controller_adc_resolution(int adc_res);
/* Get the ADC resolution set.                                             */
PREHEAD int PISTDAPI PICM_Get_controller_adc_resolution(void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Set_data_clip                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*      Set/Get the EN15BIT in MNMXCTL byte.                               */
/*      The second parameter, mode, should be either TRUE for set or FALSE */
/*      for reset.  When it is set, 16 bits ADC date will be clipped to 15 */
/*      bit ADC data. This is currently only in the ST138.                 */
/*      See piadcdef.h clip_selections for legal values.                   */
PREHEAD int PISTDAPI PICM_Set_data_clip(int mode);
PREHEAD int PISTDAPI PICM_Get_data_clip(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                PICM_Set_Gain_Mult_Avail             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*  Set/Get ADC Gain_Multiplier_Available flag  */
PREHEAD int PISTDAPI PICM_Set_Gain_Mult_Avail(int flag);
PREHEAD int PISTDAPI PICM_Get_Gain_Mult_Avail(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_Gain_Multiplier               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*  Set/Get ADC Gain_Multiplier                   */
/* see piadcdef.h gain_selection for legal values */
PREHEAD int PISTDAPI PICM_Set_Gain_Multiplier(int value);
PREHEAD int PISTDAPI PICM_Get_Gain_Multiplier(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_ADC_Data                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Set_ADC_Data
(
 int speed,                       /* speed to run ADC at.                 */
 int adc,                         /* whether to use the fast or slow ADC  */
 int resolution,                  /* Bit resolution to run ADC.           */
 int bit_adjust,                  /* bit adjust if run 16 bit as 15 or 14 */
 int gain,                        /* Gain if 12 bits or PentaMax          */
 int *error_code                  /* error code for this function.        */
 );

/*
        end of piadcfcn.h
*********************************************************************
*/
