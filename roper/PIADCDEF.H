/*   PI controller ADC DLLs external defintion and define file 
*    $Logfile: /WinX32 V2.5/INCLUDE/PIADCDEF.H $
*       $Date: 2/12/03 2:27p $
******************************************************************
*
*       piadcdef.h
*
******************************************************************
*
*  contains the Declarations & Enumerators for the simple dll
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Hgrannis $    $Date: 2/12/03 2:27p $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/PIADCDEF.H $
*  
*  13    2/12/03 2:27p Hgrannis
*  Added Tucson supported adc speeds.
*  
*  12    1/29/01 11:26a Dan
*  Implemented 2MHz Speed, used the unused 2.5 stuff
*  
*  9     9/22/98 3:34p Charlie
*  Added gain 5
*  
*  6     10/27/97 12:14p Charlie
*  Added unknown types for enums.
*  
*  5     1/26/97 12:01p Charlie
*  added ADC_FAST and ADC_SLOW.
*  
*  4     7/18/96 2:02p Dan
*  
*  3     7/17/96 2:28p Terry
*  Add #ifdef to prevent duplication of header
 * 
 * 2     10/16/95 9:46a Dan
 * Moved from $/WinX/PRODUCT/COMMON
 * 
 * 1     10/13/95 3:28p Admin
 * Latest source from PVCS
*  
*
*
******************************************************************
*/

#if !defined PIADCDEF_H
#define      PIADCDEF_H     /* define indicates that include is done now */
                            /* allows multiple includes */

/*
******************************************************************************
        include files
*/

/*
******************************************************************************
        defines
*/

/* definitions of enumeration types */

/* ########################################################### */
/*                  LEVEL 2 DLLs                               */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_controller_ad_converter           */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Controller AD converter                             */
/* int PICM_Set_controller_ad_converter(int converter);*/
/* int PICM_Get_controller_ad_converter(void);         */

/* Analog to Digital Converter type */
enum ADConverter_Type
{
    UNKNOWNADConverter = 0,
    Slow16BitsADConverter = 1,
    Fast12BitsADConverter,
    Fast16BitsADConverter,
    Slow14BitsADConverter,
    Slow15BitsADConverter,
    Slow12BitsADConverter,  /* PentaMax (slow relative)                     */
    Slow18BitsADConverter,  /* ST130 and OMA4 only                          */
    FAST_ADC,               /* Use this to select fast adc, use resolution  */
                            /* to select bits.                              */
    SLOW_ADC                /* Use this to select slow adc, use resolution  */
                            /* to select bits.                              */
};


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_Set_controller_speed               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* controller timebase in Hz freq                      */
/* int PICM_Set_controller_speed(int freq);            */
/* int PICM_Get_controller_speed(void);                */

/* Controller speed (ADC rate) */
enum ctrl_speed
{   ADCUNKNOWNSPEED=0,/* 115/116/120/121/1000   130/135/138  131 */
    ADC25KHz = 1,     /*                          x   x   x       */
    ADC30KHz,         /*   x       x                              */
    ADC33KHz,         /*       x       x   x                      */
    ADC50KHz,         /*       x       x   x      x   x   x       */
    ADC60KHz,         /*   x       x                              */
    ADC100KHz,        /*   x   x   x   x   x      x   x   x       */
    ADC150KHz,        /*                                  x   x   */
    ADC200KHz,        /*       x       x   x      x   x   x       */
    ADC430KHz,        /*                                  x       */
    ADC500KHz,        /*                                  x       */
    ADC1MHz,          /*                                  x   f   */
    ADC2MHz,          /*                                  x   x   */
    ADC5MHz,          /*                                  x   f   */
    ADC40KHz,
    ADC333KHz,
    ADC700KHz,
    ADC1400KHz,
    ADC3MHz,
    ADC10MHz,
    ADC20MHz
};

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*            PICM_Get_possible_speeds                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* return int that has ORed in all possible controller speeds. */
/* int PICM_Get_possible_speeds(void);                         */

/*----- Controller ADC speed rate support.                               */
enum ADC_support_speed        /*         PDA                  CCD        */
{                             /* 115/116/120/121/1000   130/135/138 131  */
    SPRT25KHz  = 0x0001,      /*                         x   x   x       */
    SPRT30KHz  = 0x0002,      /*  x       x                              */
    SPRT33KHz  = 0x0004,      /*      x       x   x                      */
    SPRT50KHz  = 0x0008,      /*      x       x   x      x   x   x       */
    SPRT60KHz  = 0x0010,      /*  x       x                              */
    SPRT100KHz = 0x0020,      /*  x   x   x   x   x      x   x   x       */
    SPRT150KHz = 0x0040,      /*                                 x   x   */
    SPRT200KHz = 0x0080,      /*      x       x   x      x   x   x       */
    SPRT430KHz = 0x0100,      /*                                 x       */
    SPRT500KHz = 0x0200,      /*                                 x       */
    SPRT1MHz   = 0x0400,      /*                                 x   f   */
    SPRT2MHz   = 0x0800,      /*                                 x   x   */
    SPRT5MHz   = 0x1000       /*                                 x   f   */
};


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_controller_adc_resolution         */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Set the ADC resolution of the ADC-converter (i.e. 12 bits).             */
/* int PICM_Set_controller_adc_resolution(int adc_res);                    */
/* Get the ADC resolution set.                                             */
/* int PICM_Get_controller_adc_resolution(void);                           */

/* ADC resolution */
enum ADC_resolution
{
    UNKNOWN=0,
    ADC12BITS,
    ADC14BITS,
    ADC15BITS,
    ADC16BITS,
    ADC18BITS 
};

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_Set_data_clip                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*      Set/Get the EN15BIT in MNMXCTL byte.                               */
/*      The second parameter, mode, should be either TRUE for set or FALSE */
/*      for reset.  When it is set, 16 bits ADC date will be clipped to 15 */
/*      bit ADC data. This is currently only in the ST138.                 */
/* int PICM_Set_data_clip(int mode);                                       */
/* int PICM_Get_data_clip(void);                                           */

/* Data clip enumarted type, good only for taxi st138 systems. */
enum clip_selections
{
    BA_NO_CLIP = 0,
    BA_CLIP1_LSB,
    BA_CLIP2_LSB,
    BA_CLIP1_MSB,
    BA_CLIP2_MSB,
    BA_CLIP_MSB_LSB
};



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_Gain_Multiplier               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*  Set/Get ADC Gain_Multiplier                        */
/* This is used with a 12 bit converter.               */
/* int PICM_Set_Gain_Multiplier(int value);            */
/* int PICM_Get_Gain_Multiplier(void);                 */

/*  Controller Gain enumerated type -- ST138  */
enum gain_selections
{
    GAIN_NOT_AVAILABLE = -1,    /*  Dialog use only               */
    GAIN_MULT_X1 = 1,           /*  times 1  st138 or st133       */
    GAIN_MULT_X4,               /*  times 4  st138                */
    GAMMA,                      /* fast mode only PentaMax        */
    AGC,                        /* fast mode only PentaMax        */
    GAIN1,                      /* PentaMax                       */
    GAIN2,                      /* PentaMax                       */
    GAIN3,                      /* PentaMax default for fast ADC  */
    GAIN4,                      /* PentaMax                       */
    GAIN_MULT_X5                /* times 5 st133 1Mhz 226 brd.    */
};

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_ADC_Data                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Set the speed (use ctrl_speed), adc (use ADC_CONVERTER), resolution */
/* (use ADC_resolution), bit_adjust (clipping use clip_selections),    */
/* and gain (use gain_selections).                                     */

enum ADC_CONVERTER
{
    ADC_UNKNOWN_CONVERTER = 0,
    ADC_SLOW = 1,
    ADC_FAST
};
/* errors returned by PICM_Set_ADC_Data */
#define ILLEGAL_SPEED      0x01   /* unable to select user speed.   */
#define ILLEGAL_ADC        0x02   /* unable to select user ADC.     */
#define ILLEGAL_RESOLUTION 0x03   /* unable to set user resolution. */
#define ILLEGAL_CLIP       0x04   /* unable to set user clip.       */
#define ILLEGAL_GAIN       0x05   /* unable to set user gain.       */


#endif

/*
        end of piadcdef.h
*********************************************************************
*/
