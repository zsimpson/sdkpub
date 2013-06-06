/*   PI Event Functions
*    workfile:   
*    $Logfile: /WinX32 V2.0/INCLUDE/pievtfcn.h $
*       $Date: 9/07/96 12:15p $
******************************************************************
*
*       pievtfcn.h
*
******************************************************************
*
*  contains the Declarations for variable functions
*  dealing with Win32 Events... 
*
*                               written by R.C.B
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Bob $    $Date: 9/07/96 12:15p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/pievtfcn.h $
*  
*  1     9/07/96 12:15p Bob
*  user events from easy dll's new for 95
*  
*
*
******************************************************************
*/
PREHEAD HANDLE PISTDAPI PICM_SetUserEvent(	int sec,			/* Security attributes */
							BOOL bManual,		/* Manual Reset Flag   */
							BOOL bInitial,		/* Initial State	   */
							LPCSTR name,		/* Event name		   */
							int number);		/* Number of Frames	   */