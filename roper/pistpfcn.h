/*   PI controller DLLs external defintion Multiple Strips 
*    workfile:   s:\xsma\xdll\pistpfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/pistpfcn.h $
*       $Date: 5/28/97 4:21p $
******************************************************************
*
*       pistpfcn.h
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
*  $Author: Rock $    $Date: 5/28/97 4:21p $
*
******************************************************************
*
*  $Log: /WinX32 V2.0/INCLUDE/pistpfcn.h $
*  
*  5     5/28/97 4:21p Rock
*  Added PICM_Generate sideeffects and get normalized roi function
*  prototypes.
*  
*  4     5/09/97 1:35p Bob
*  Added Generate Side Effects Prototype as Well as Get_normal_rois
*  
*  3     7/18/96 2:02p Dan
*  
*  2     6/06/96 12:01p Charlie
*  changed multroi from int to unsigned int.
*  
*  1     6/05/96 6:12p Charlie
*  multiple strip functions.
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
/*               PICM_SetROI_MultStrip                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* define multiple strips by calling this function multiple times, */
/* change index to defined new ROI.                                */
PREHEAD int PISTDAPI PICM_SetROI_MultiStrip
(
 int startx,            /* 1st pixel of ROI in x dir. (note starts at 1) */
 int starty,            /* 1st pixel of ROI in y dir. (note starts at 1) */
 int endx,              /* last pixel of ROI in x dir.                   */
 int endy,              /* last pixel of ROI in y dir.                   */
 int groupx,            /* amount to bin/group x data.                   */
 int groupy,            /* amount to bin/group y data.                   */
 int index,             /* index of strip 1-50.                          */
 unsigned int *error_code/* Error code, used if function returs false.   */
 );
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Set_MultStrip_Flag               */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Enable (1) multiple strips, or disable (0).         */
PREHEAD int PISTDAPI PICM_Set_MultStrip_Flag (int flag);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Clear_MultStrip                  */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Clear internal array of all ROIs.                   */
PREHEAD int PISTDAPI PICM_Clear_MultStrip (void);

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*               PICM_Download_MultROI                 */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* Down Load multiple ROIs to the system.              */
PREHEAD int PISTDAPI PICM_Download_MultROI (unsigned int *error_code);

/* Retrieve Normalized Rois */
PREHEAD IRCT* PISTDAPI PICM_Get_normal_rois(IRCT *irct,int *xbin, int *ybin, int index);

/* Force Side Effects to be generated */
PREHEAD int PISTDAPI PICM_Generate_sideeffects( void );

/*
        end of pistpfcn.h
*********************************************************************
*/
