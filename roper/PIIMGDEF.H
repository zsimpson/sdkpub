/*   PI controller DLLs external defintion and define file 
*    $Logfile: /WinX32 V2.0/PRODUCT/INCLUDES/PIIMGDEF.H $
*       $Date: 7/18/96 2:02p $
******************************************************************
*
*       piimgdef.h
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
*  $Log: /WinX32 V2.0/PRODUCT/INCLUDES/PIIMGDEF.H $
*  
*  3     7/18/96 2:02p Dan
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
/*                  LEVEL 1 DLLs      IMAGING                  */
/* EASY CONTROLLER DLLS : FUNCTION PROTOTYPES, ENUMERATED TYPE */
/* AND ERRORS CODES USED.                                      */
/* ########################################################### */

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/*                    PICM_SetROI                      */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* Set ROI for image, If this function is not called full image is default.  */
/* this allows a sub-region and/or a grouped/binned image to be collected.   */
/* int PICM_SetROI                                                           */
/*   int startx,              :: 1st pixel of ROI in x dir.(note starts at 1)*/
/*   int starty,              :: 1st pixel of ROI in y dir.(note starts at 1)*/
/*   int endx,                :: last pixel of ROI in x dir.                 */
/*   int endy,                :: last pixel of ROI in y dir.                 */
/*   int groupx,              :: amount to bin/group x data.                 */
/*   int groupy,              :: amount to bin/group y data.                 */
/*   unsigned int *error_code :: Error code, used if function returs false.  */

/* ####################################### */
/* ##### ERROR CODES for PICM_SetROI ##### */
/* ####################################### */

#define CONTROLLER_SETUP_WRONG 0x0001 /* Got error in getting info from     */
                                      /* controller, check to see if        */
                                      /* previous initialize/create commands*/
                                      /* executed without error. Note : ROI */
                                      /* not set.                           */

/* The following 4 messages are for illegal values for ROI, the function    */
/* PICM_SetROI will try to correct, but user should check code.             */
#define STARTX_ILLEGAL         0x0004
#define STARTY_ILLEGAL         0x0002 
#define ENDY_ILLEGAL           0x0008
#define ENDX_ILLEGAL           0x0010

/* the following 2 warnings are start and end values where reversed. The  */
/* function swapped start end but code should be checked.                 */
#define X_VALUES_SWAPPED       0x0020
#define Y_VALUES_SWAPPED       0x0040

/* The following 2 errors are for illegal group/bin sizes.                */
#define GROUPSIZE_X_ERROR      0x0080
#define GROUPSIZE_Y_ERROR      0x0100



#define ROI_ERROR              0x0200 /* The ROI defined was not accepted   */
                                      /* by controller object. Check ROI    */
                                      /* values make sure valued for CCD    */
                                      /* and controller.                    */


/*
        end of piimgdef.h
*********************************************************************
*/
