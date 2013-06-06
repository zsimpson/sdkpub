/*   PI controller DLLs external defintion fuctions for Variables.
*    workfile:   s:\xsma\xdll\pivarfcn.h
*    $Logfile: /WinX32 V2.4/INCLUDE/pivarfcn.h $
*       $Date: 2/08/99 3:12p $
******************************************************************
*
*       pivarfcn.h
*
******************************************************************
*
*  contains the Declarations for variable functions 
*
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 2/08/99 3:12p $
*
******************************************************************
*
*  $Log: /WinX32 V2.4/INCLUDE/pivarfcn.h $
*  
*  13    2/08/99 3:12p Bob
*  Added RS_ to types ...
*  
*  12    1/30/99 1:20p Bob
*  Added RS_ 
*  
*  8     9/17/97 2:36p Charlie
*  added comments
*  
*  7     2/13/97 7:16p Charlie
*  Added shells for Save and Restore (and clear) controller states.
*  
*  6     2/04/97 6:59a Dan
*  completed implementation of 'PICM_GetEnumString' & 'PICM_GetResID'
*  
*  5     1/28/97 3:51p Charlie
*  More IsAvail and GetEnumParam additions.
*  
*  4     1/24/97 8:15p Charlie
*  
*  3     1/20/97 9:51a Charlie
*  Added new functions isavail, and support functions to determine what is
*  supported by a certain hardware.
*  
*  2     7/18/96 2:02p Dan
*  
*  1     6/14/96 11:43a Charlie
*  PI setparam enums.
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
/*                  LEVEL 3 DLLs  PI variables.                */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set/Get_Xparam.                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* MLM-----------------------SetParam/GetParam stuff------------------------*/
/****************************************************************************/
PREHEAD enum CM_ERR PISTDAPI PICM_CMGetDoubleParam(enum CM_CMD param,
                                                   double *value);
PREHEAD enum CM_ERR PISTDAPI PICM_CMGetLongParam(enum CM_CMD param,
                                                 long *value);
PREHEAD enum CM_ERR PISTDAPI PICM_CMSetDoubleParam(enum CM_CMD param,
                                                   double value);
PREHEAD enum CM_ERR PISTDAPI PICM_CMSetLongParam(enum CM_CMD param,
                                                 long value);
PREHEAD enum CM_ERR PISTDAPI PICM_CMGetString(enum CM_STRINGS cmd,
                                              char far * lpszRStr);
PREHEAD enum CM_ERR PISTDAPI PICM_CMSetString(enum CM_STRINGS cmd,
                                              char far * lpszRStr);
/* MLM----------------------SetParam/GetParam stuff----end-------------------*/
/*****************************************************************************/

/* The IsAvail function returns non-zero if feature is available for controller object,    */
/* otherwise it returns 0 (not available).                                        		   */
PREHEAD RS_UINT32 PISTDAPI PICM_IsAvail(enum CM_CMD cmd,
							         struct VALID_RANGE *MinMaxDefault);

/* GetEnumParam is given an index and returns the enumerated value for that index as a     */
/* parameter, it also returns TRUE from the fucntion if there was a value associated with  */
/* the enumerated value, if no value found or illegal cmd/index was sent then FALSE returned*/
/* For example if there are 3 valid items for the controller and you pass the index 1-3 the*/
/* value returned will be TRUE and the enumerated value that is supported will be returned */
/* as a parameter, if you pass 4 or greater then FALSE (0)  will be returned by the function*/
PREHEAD RS_UINT32 PISTDAPI PICM_GetEnumParam(enum CM_CMD cmd, RS_UINT32 index, RS_INT32 *enumvalue);

/* GetEnumString : given a enumerated value (gotton from GetEnumParam) and   */
/* an ID this function returns the string associated with the two as a       */
/* param, for example the ID might be ADC_TYPE and the Enum might be ADC500, */
/* then the string would be "500 Khz".  The return value of the function is  */
/* False (0) if no string could be returned.                                 */
PREHEAD RS_UINT16 PISTDAPI PICM_GetEnumString( enum CM_CMD cmd,
                                            RS_UINT32 enumvalue,
		 				  				    char *RetString,
		 				  				    RS_UINT32 StringSize );

/* GetResID : simalar to GetEnumString except instead of returning a string  */
/* it returns the resource ID.  The return value of the function is          */
/* False (0) if no resource ID could be returned.                            */
PREHEAD RS_UINT16 PISTDAPI PICM_GetResID( enum CM_CMD cmd,
                                       RS_UINT32 enumvalue,
                                       RS_UINT32 *ResourceID );
	

/* The next three functions should be used together, The Functions Save_State*/
/* saves some given state, then if the user wishes to restore the state he   */
/* calls restore_state, otherwise if he is satisfied with his changes to the */
/* state he calles clear_state.												 */

/* PICM_Save_State : Save the selected controller state. Returns True if     */
/* legal state to save.														 */
PREHEAD int PISTDAPI PICM_Save_State  (int StateToSave);	/* State to Save.*/

/* PICM_Restore_State : Restore the selected controller state. Returns True  */
/* if state restored correctly otherwise False. If False then status_code    */
/* should be looked at to determine what failed.							 */
/*			RESTR_OK            : Restore worked.							 */
/*			RESTR_INVALID_STATE : State given to restore doesn't exist.		 */
/*			RESTR_FAILED        : A failure occured during restoring.		 */
/*			RESTR_NOT_SAVED     : Restore state was not previously saved.	 */
PREHEAD int PISTDAPI PICM_Restore_State 
(int StateToSave,			/* State to Save.     								*/
 int *status_code);			/* if function returns False, then status describes */
 							/* what failed. 									*/

/* PICM_Clear_State : Clear the selected controller state.		*/
PREHEAD int PISTDAPI PICM_Clear_State (int StateToClear);


/*
        end of pivarfcn.h
*********************************************************************
*/
