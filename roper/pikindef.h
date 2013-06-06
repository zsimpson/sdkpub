/*   PI controller kinetics DLLs external defintion and define file 
*    workfile:   s:\xsma\xdll\pikindef.h
*    $Logfile: /WinX32 V2.0/PRODUCT/INCLUDES/pikindef.h $
*       $Date: 7/18/96 2:02p $
******************************************************************
*
*       pikindef.h
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
*  $Author: Dan $    $Date: 7/18/96 2:02p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/PRODUCT/INCLUDES/pikindef.h $
*  
*  2     7/18/96 2:02p Dan
 * 
 * 1     2/05/96 12:51p Charlie
 * Kinetics def file.
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

/* definitions of enumeration types */

/* ########################################################### */
/*                  LEVEL 2 DLLs                               */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*          PICM_Set_Kinetics_TriggerMode              */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Controller Kinetics functions                       */
/* to use no trigger set timing mode to freerun and set kintetics trigger to */
/* NO_TRIGGER. To use either single or multiple trigger set the timing mode  */
/* to CTRL_EXTSYNC, and then set kinetics trigger to desired value.          */
enum Kinetics_Trigger_Values
{
    KINETICS_NO_TRIGGER=0,
    KINETICS_SINGLE,
    KINETICS_MULTIPLE
};


/*
        end of pikindef.h
*********************************************************************
*/
