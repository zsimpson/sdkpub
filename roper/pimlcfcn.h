/*   PI controller DLLs external defintion 
*    $Logfile: /WinX32 V2.0/PRODUCT/INCLUDES/pimlcfcn.h $
*       $Date: 7/18/96 2:02p $
******************************************************************
*
*       pimlcfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple dll for multiple controllers
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
*  $Log: /WinX32 V2.0/PRODUCT/INCLUDES/pimlcfcn.h $
*  
*  2     7/18/96 2:02p Dan
*  
*  1     7/11/96 9:37p Charlie
*  New file for multiple controller systems.
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
/*                  LEVEL 5 DLLs                               */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_PICM_CreateController_All        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_CreateController_All
(
 int Controller_type,       /* controller to create, see ctrl_type          */
 int Detector_type,         /* CCD/PDA to run, see ctrl_CCD_sensor          */
 int Data_Collection_Mode,  /* Data collection mode, see sensorReadoutMode  */
 int application_type,      /* type of application, see Application_Type    */
 int number_of_controllers, /* number of controllers in experiment.         */
 unsigned int *error_code   /* Erro code if, used if function returs false. */
 );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_Controller_Mult              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI  PICM_Set_Controller_Mult( int new_ctr, int *error_code );



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Stop_controller_All              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Stop_controller_All( void );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Start_controller_All             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Start_controller_All( void );



/*
        end of pimlcfcn.h
*********************************************************************
*/
