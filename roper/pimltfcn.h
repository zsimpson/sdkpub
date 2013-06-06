/*   PI controller DLLs external defintion 
*    workfile:   s:\xsma\xdll\pimltfcn.h
*    $Logfile: /WinX32 V2.0/PRODUCT/INCLUDES/pimltfcn.h $
*       $Date: 7/18/96 2:02p $
******************************************************************
*
*       pimltfcn.h
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
*  $Author: Dan $    $Date: 7/18/96 2:02p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/PRODUCT/INCLUDES/pimltfcn.h $
*  
*  2     7/18/96 2:02p Dan
*  
*  1     6/06/96 10:43p Charlie
*  multiple frame operations.
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
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_ResetUserBuffer                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function resets software counters and address of users buffer for */
/* data collection.                                                       */
PREHEAD void PISTDAPI PICM_ResetUserBuffer (void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_SetNewUserBuffer                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function allows user to use multiple buffers for data collection. */
PREHEAD int PISTDAPI PICM_SetNewUserBuffer
(
 void huge* big_buffer,   /* Users data buffer, Data collected stored here */
 unsigned int *error_code /* Error code, used if function returs false.    */
 );



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_sequentials                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* These two functions are currently only implemented for special frame */
/* transfer systems.                                                    */
/* number of synchronous sequential frames */
PREHEAD int PISTDAPI PICM_Set_sequentials(int sequential);
PREHEAD int PISTDAPI PICM_Get_sequentials(void);

/* 1 frame at a time (but multiple shots) operation */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Stop_1frame                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* 1 frame operations. */
/* use for auto-stop and PentaMax enable-disable modes */
PREHEAD int PISTDAPI PICM_Stop_1frame( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Start_1frame                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* 1 frame operations */
/* use for auto-stop and PentaMax enable-disable modes */
PREHEAD int PISTDAPI PICM_Start_1frame( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Xet_AutoStop                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* 0 - free run, 1 - stops after one frame, if st133 or DC131 1-255 will */
/* set hardware to collect that many frames and then automaticly stop.   */
    /* Set and Get for auto-stop setting. If set this will in hardware */
    /* automaticly stop the controller after collecting one frame. This */
    /* prevents the wierd double click of the shutter in Async mode. */
    /* This is passed a TRUE (non-zero) to enable and a FALSE (zero) to */
    /* disable. */
    /* This is only implemented on ST138s with an EPLD version of */
    /* U37 2060-0010 Rev 1.2 and above. */
PREHEAD     int PISTDAPI PICM_Set_AutoStop( int flag );
PREHEAD     int PISTDAPI PICM_Get_AutoStop( void );

/*
        end of pimltfcn.h
*********************************************************************
*/
