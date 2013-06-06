/*   PI controller DLLs external defintion 
*    workfile:   s:\xsma\xdll\pigenfcn.h
*    $Logfile: /WinX32 V2.4/INCLUDE/pigenfcn.h $
*       $Date: 2/09/99 1:09p $
******************************************************************
*
*       pigenfcn.h
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
*  $Author: Charlie $    $Date: 2/09/99 1:09p $
*
******************************************************************
*
*  $Log: /WinX32 V2.4/INCLUDE/pigenfcn.h $
*  
*  20    2/09/99 1:09p Charlie
*  Replaced  old data type constants with new RS_
*  
*  18    7/20/98 12:33p Bob
*  Prototypes for PICM_GetChannelOffset and Gain...
*  
*  17    5/22/98 3:23p Bob
*  Added 2 Functions SetChannelGain and SetChannelOffset...
*  
*  16    5/21/98 3:21p Bob
*  For Some reason ChkCopyData was missing a parameter in the function
*  prototype...
*  
*  14    5/07/98 10:26a Charlie
*  Moved PICM_LockCurrentFrame and Unlock to PIGENFCN.H
*  
*  12    12/09/97 10:10a Charlie
*  Added initialize interface as export.
*  
*  11    9/22/97 10:07a Charlie
*   added PICM_Start_interface for snap ins
*  
*  10    9/17/97 2:35p Charlie
*  Added comments
*  
*  9     9/02/97 6:26p Charlie
*  added  PICM_HookWinXController to hook WinX to easy DLLs.
*  
*  8     4/14/97 3:48p Charlie
*  Moved temperature functions from pifcsfcn.h to this file. 
*  
*  7     3/11/97 11:09a Bob
*  Added Prototype for PICM_Set_EasyDLL_DC enums for this function were
*  already in pigendef.h.
*  
*  6     2/07/97 11:41a Charlie
*  Merged K.C.s new stuff.
*  
*  5     7/18/96 2:02p Dan
*  
*  4     6/06/96 11:52a Charlie
*  Added inuse functions.
*  
*  3     6/03/96 11:00p Charlie
*  Made controller_version functions use prehead and pistdapi.
*  
*  2     5/24/96 11:14a Charlie
*  Added set and get controller version.
*  
*  1     4/23/96 3:40p Charlie
*  
*     Rev 1.0   16 Nov 1994 16:27:34   CGR
*  Initial revision.
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
/*                  LEVEL 1 DLLs                               */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_CreateController               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Create and Initialize controller object. Set some defaults. MUST be 1ST  */
/* function called.                                                         */
PREHEAD int PISTDAPI PICM_CreateController
(
 int Controller_type,       /* controller to create, see ctrl_type          */
 int Detector_type,         /* CCD/PDA to run, see ctrl_CCD_sensor          */
 int Data_Collection_Mode,  /* Data collection mode, see sensorReadoutMode  */
 int application_type,      /* type of application, see Application_Type    */
 unsigned int *error_code   /* Erro code if, used if function returs false. */
 );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*             PICM_SetInterfaceCard                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Set type of PC PI-interface card used. This will also set the ADC     */
/* defaults, for ST138 it will read what is available and set to fastest */
/* ADC available.                                                        */
PREHEAD int PISTDAPI PICM_SetInterfaceCard
(
 int Interface_Card,     /* Interface card, see interfaceType enum       */
 unsigned int Base_Address,/* base address of interface card, not used eisa*/
 int Card_interrrupt,    /* Interrupt to use, see interrupt_channel enum */
 unsigned int *error_code/* Error code, used if function returs false.   */
 );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Initialize_System                */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function down loads all information to controller It sets up the    */
/* dma buffers, ring buffer, and the users buffer. It Also hooks in the     */
/* interrupt routine used by data collection. All special settings (i.e     */
/* exposure, ROIs, etc) should be done before calling this function.        */
PREHEAD int PISTDAPI PICM_Initialize_System
(
 void huge* big_buffer,   /* Users data buffer, Data collected stored here */
 unsigned int *error_code/* Error code, used if function returs false.   */
 );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                  PICM_SetExposure                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Set the camera exposure in seconds.                                     */
PREHEAD int PISTDAPI PICM_SetExposure
(
 double exposure,          /* exposure time in seconds                     */
 unsigned int *error_code  /* Error code, used if function returs false.   */
);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_ChkCopyData                    */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This routine calls PICM_ChkData to check for frame data. If data has    */
/* been successfully collected, it will copy the data to a buffer dptr     */
/* provided by caller.                                                     */
PREHEAD int PISTDAPI PICM_ChkCopyData
(
 unsigned int *status_code,  /* status code                           */
 short *dptr,
 long linewidth
);



/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                 PICM_ChkData                        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This routine checks if data has been collected. It returns TRUE if      */
/* either data has been successfully collected or if an error has occured. */
/* If data has been collected ok the status will set DONEDCOK (DONE Data   */
/* Collection OK) bit, otherwise check other bits for error see CTRL_STATUS*/
PREHEAD int PISTDAPI PICM_ChkData
(
 unsigned int *status_code   /* status code                           */
);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*            PICM_SizeNeedToAllocate                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function returns the amount of memory the user should allocate to */
/* hold all of his data. NOTE : must have controller DLLs created after   */
/* 10/10/94 to use this function.                                         */
/* This function returns size needed for user buffer.                     */
PREHEAD long PISTDAPI PICM_SizeNeedToAllocate (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                   PICM_CleanUp                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* This function should be called when data collection is complete (either */
/* through a successful data collection or an error condition).            */
/* This function deallocates all data collection buffers and unhooks the   */
/* data collection interrupt routine.                                      */
PREHEAD int PISTDAPI PICM_CleanUp (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Start_controller                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*  Startup Controller to acquire data  */
PREHEAD int PISTDAPI PICM_Start_controller(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Stop_controller                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*  Stops Controller from collecting data              */
PREHEAD int PISTDAPI PICM_Stop_controller(void);


/* ######################################################################## */
/* The following functions are extras, they don't need to be called but may */
/* be useful.                                                               */
/* ######################################################################## */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_sensor_x                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Get x dimension of chip.                            */
PREHEAD int PISTDAPI PICM_Get_sensor_x(void);  

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_sensor_y                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Get y dimension of chip                             */
PREHEAD int PISTDAPI PICM_Get_sensor_y(void);     

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_pixeldimension_x             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* read minimum x,y dimension for this access pattern  */
/* accessable pixel area: x value                      */
/* This is the actual x dimension of data coming back  */
/* from the controller. This function takes into account*/
/* ROIs and binning in the x and y dimension.          */
PREHEAD int PISTDAPI PICM_Get_pixeldimension_x(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_pixeldimension_y             */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* accessable pixel area: y value                      */
/* This is the actual y dimension of data coming back  */
/* from the controller. This function takes into account*/
/* ROIs and binning in the x and y dimension.          */
PREHEAD int PISTDAPI PICM_Get_pixeldimension_y(void);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_TTL_pattern                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Send bit pattern to controller TTL_out port */
/* this is supported by the ST12x, ST130, ST138, and ST133 controllers. */
PREHEAD int PISTDAPI PICM_Set_TTL_pattern (int pattern);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Get_TTL_pattern                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* this is supported by the ST12x, ST130, ST138, and ST133 controllers. */
/* Read bit pattern from controller TTL_in port */
PREHEAD int PISTDAPI PICM_Get_TTL_pattern(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_Fast_ADC                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function will set the fast ADC avaiable in controller. If */
/* controller only has one adc it will set it.                    */ 
PREHEAD int PISTDAPI PICM_Set_Fast_ADC(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_Slow_ADC                     */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function will set the slow ADC avaiable in controller. If */
/* controller only has one adc it will set it.                    */ 
PREHEAD int PISTDAPI PICM_Set_Slow_ADC(void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_controller_version           */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD int PISTDAPI PICM_Set_controller_version( int cversion );
PREHEAD int PISTDAPI PICM_Get_controller_version( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_InUse                        */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This function is set by winView, if flag is set winview. */
/* will give error message and not run. Winview will also   */
/* set this flag, so user can check flag it see if winview  */
/* is running.                                              */
PREHEAD int PISTDAPI PICM_Get_InUse( void );
PREHEAD int PISTDAPI PICM_Set_InUse( int flag );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_EasyDLL_DC                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Sets data acquisition mode to nframe versus last    */
/* (most recent frame) mode							   */
PREHEAD int PISTDAPI PICM_Set_EasyDLL_DC(int mode );



/* ST133 & MicroMax only functions. */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Set_Temperature                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This sets temperature for the detector (only supported by ST133 */
/* and VICCD).                                                     */
PREHEAD     int PISTDAPI PICM_Set_Temperature( double temperature );
PREHEAD     double PISTDAPI PICM_Get_Temperature( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Get_Temperature_Status            */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* This returns if the detector temperature is locked.             */
PREHEAD     int PISTDAPI PICM_Get_Temperature_Status( void );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Get_Actual_Temperature            */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Get the current temperature setting, there is some  */
/* read error, so you should use the temperature status*/
/* to make sure it is locked.                          */ 
PREHEAD double PISTDAPI PICM_Get_Actual_Temperature(void);


/* ################################################### */
/* CAN ONLY BE USED WITH USER WINX DLL, NOT EASY DLL   */
/* ################################################### */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_HookWinXController                */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Hook controller object used by WinX to Easy Easy Dlls.*/
/* This should only be used by user DLL called by WinX.	 */					   
PREHEAD unsigned int PISTDAPI PICM_HookWinXController (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_Start_interface                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Get interface card set for data collection. The     */
/* controller must be initialized 1st.                 */
PREHEAD unsigned int PISTDAPI PICM_Start_interface (void);
PREHEAD int PISTDAPI PICM_Initialize_interface( void );


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              PICM_LockCurrentFrame                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* These functions can be called instead of chkdata. These routines get the */
/* linear address of frame available in our data collection ring buffer.    */
PREHEAD int PISTDAPI PICM_LockCurrentFrame(void **directaddress, unsigned long *size, unsigned int *status);
PREHEAD int PISTDAPI PICM_UnlockCurrentFrame( void );

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*              Gains And Offsets	                   */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
PREHEAD RS_UINT32 PISTDAPI PICM_SetChannelOffset( RS_UINT32 channel, RS_UINT32 value );
PREHEAD RS_UINT32 PISTDAPI PICM_SetChannelGain( RS_UINT32 channel, RS_UINT32 value );

PREHEAD RS_UINT32 PISTDAPI PICM_GetChannelGain( RS_UINT32 channel);
PREHEAD RS_UINT32 PISTDAPI PICM_GetChannelOffset( RS_UINT32 channel);



/*
        end of pigenfcn.h
*********************************************************************
*/
