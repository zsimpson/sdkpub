/*   PI controller DLLs external defintion skipping operations.
*    workfile:   s:\xsma\xdll\pimaxfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/pifcsfcn.h $
*       $Date: 4/14/97 3:48p $
******************************************************************
*
*       pimaxfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll skipping operations
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Charlie $    $Date: 4/14/97 3:48p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/pifcsfcn.h $
*  
*  3     4/14/97 3:48p Charlie
*  Took out temperature functions and put them in pigenfcn.h since
*  everybody who has a st133/MicroMax will need to call them.
*  
*  2     7/18/96 2:02p Dan
*  
*  1     6/05/96 10:37a Charlie
*  Focus routines for easydll.
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
/*                  LEVEL 2 DLLs  PentaMax  OPERATIONS.         */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_RS170_enable                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD     int PISTDAPI PICM_Set_RS170_enable(int mode);
PREHEAD     int PISTDAPI PICM_Get_RS170_enable(void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Easy_Focusing                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*  Easy Focusing Calculations & Sets  */
PREHEAD int PISTDAPI PICM_Easy_Focusing( int focus_type,
                                       double nominal_exposure,
                                       int zoom,
                                       int pan,
                                       double *actual_exposure,
                                       int *zoompattern,
                                       unsigned int *error_code );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_RS170_bits_shifted            */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* int STDAPICALLTYPE PICM_Set_RS170_bits_shifted(  ); */
/* ST133 (MicroMax) Only.                              */
    /* Set and Get controller RS170 bits to shift (so far only st133) */
PREHEAD     int PISTDAPI PICM_Get_RS170_bits_shifted(void);
PREHEAD     int PISTDAPI PICM_Set_RS170_bits_shifted(int BitAdjust);  

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_RS170_offset                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* ST133 (MicroMax) Only.                              */
    /* Set and Get controller RS170 offset (so far only st133) */
PREHEAD     int PISTDAPI PICM_Get_RS170_offset(void);
PREHEAD     int PISTDAPI PICM_Set_RS170_offset(int offset);
    




/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Initialize_RS170                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Initialize_RS170
(
 unsigned int *error_code /* Error code, used if function returs false.    */
 );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_lut_type                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Set_lut_type(int scaling_type);
PREHEAD int PISTDAPI PICM_Get_lut_type(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_lookuptable                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD void PISTDAPI PICM_Set_lookuptable( unsigned char *lut_data);
PREHEAD unsigned char * PISTDAPI PICM_Get_lookuptable( unsigned char *lut_data);

/*
        end of pifcsfcn.h
*********************************************************************
*/
