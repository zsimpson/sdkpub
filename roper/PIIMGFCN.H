/*   PI controller imaging DLLs external defintion 
*    workfile:   s:\xsma\xdll\piimgfcn.h
*    $Logfile: /WinX32 V2.0/INCLUDE/PIIMGFCN.H $
*       $Date: 11/08/96 9:12a $
******************************************************************
*
*       piimgfcn.h
*
******************************************************************
*
*  contains the Declarations for the simple imaging dll
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
*  $Log: /WinX32 V2.0/INCLUDE/PIIMGFCN.H $
*  
*  2     11/08/96 9:12a Bob
*  
*  1     11/07/96 3:04p Charlie
*  
*     Rev 1.0   18 Nov 1994 13:14:40   CGR
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
/*                  LEVEL 1 DLLs  IMAGING                      */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES                  */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                    PICM_SetROI                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Set ROI for image, If this function is not called full image is default. */
/* this allows a sub-region and/or a grouped/binned image to be collected.  */
PREHEAD int PISTDAPI PICM_SetROI
(
 int startx,            /* 1st pixel of ROI in x dir. (note starts at 1) */
 int starty,            /* 1st pixel of ROI in y dir. (note starts at 1) */
 int endx,              /* last pixel of ROI in x dir.                   */
 int endy,              /* last pixel of ROI in y dir.                   */
 int groupx,            /* amount to bin/group x data.                   */
 int groupy,            /* amount to bin/group y data.                   */
 unsigned int *error_code/* Error code, used if function returs false.   */
 );


/*
        end of pigenfcn.h
*********************************************************************
*/
