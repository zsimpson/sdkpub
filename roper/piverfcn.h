/*   title   :  Get DLL Version function prototypes
*
*    $Logfile: /WinX32 V2.5/INCLUDE/piverfcn.h $
*       $Date: 4/10/03 11:04a $
******************************************************************************
*
*
*
*
*       piverfcn.h
*
*
*
*
******************************************************************************
*
*
*
*
*                               written by djk
*
*
******************************************************************************
*
*  last changes done by:
*
*  $Author: Hgrannis $                     $Date: 4/10/03 11:04a $
*
******************************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/piverfcn.h $
*  
*  19    4/10/03 11:04a Hgrannis
*  Make dat file version function const correct.
*  
*  18    6/15/00 8:23a Bob
*  Changes for Pvcam into Winview and Dynamic Contrman...
*  
*  16    2/08/99 11:54a Charlie
*  Fixed definition for pixcmtxt dll.
*  
*  15    1/30/99 1:20p Bob
*  Added RS_ 
*  
*  12    1/21/98 5:18p Maynard
*  Change declarations of PIPP_Get_DLLVersion and
*  PIPP_Get_DLLVersionString to agree with the definitions in the .c file
*  - i.e., use INT32 and INT8 instead of long and char types.
*  
*  10    12/02/97 4:23p Charlie
*  Fixed pre head defines
*  
*  9     11/11/97 11:12a Bob
*  added get data prototype
*  
*  8     11/10/97 12:58p Bob
*  Added Version info for PISCC and PIIP
*  
*  7     6/03/97 11:14a Bob
*  Added Functions For Getting Versions From PIXCMTXT, PI133
*  
*  6     7/18/96 2:02p Dan
*  
*  5     6/06/96 1:53p Dan
*  changed 'version' parameter from unsigned long to long
*  
*  4     6/05/96 3:06p Dan
*  added function prototypes for '(DLL?)_Get_DLLVersion'
*  
*  3     6/05/96 1:22p Dan
*  added function prototype 'PIDC_Get_DLLVersionString'
*  added function prototype 'PIDP_Get_DLLVersionString'
*  added function prototype 'PIPCI_Get_DLLVersionString'
*  
*  2     6/05/96 11:09a Dan
*  added function prototype 'PIPP_Get_DLLVersionString'
* 
* 1     3/08/96 8:32a Dan
* implemented V1.4 changes
* 
* 1     3/06/96 5:11p Dan
* implementing 'PICM_Get_DLLVersionString'
*
*
******************************************************************************
*/

#if !defined  PIVERFCN_H
#define       PIVERFCN_H

/*
******************************************************************************
        include files
*/


/*
******************************************************************************
        defines
*/

/*
******************************************************************************
        function prototypes
*/

/*  get DLL version string (see PIVERDEF.H for definitions) */

/*  PIXCM Family Versions  */
PREHEAD int PISTDAPI PICM_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                char *buffer );
PREHEAD int PISTDAPI PICM_Get_DLLVersion( enum PI_DLL_VERSION param,
                                          long *version );

/*  PIPP Family Versions  */
PIPP_PREHEAD RS_INT32 PISTDAPI PIPP_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                     RS_INT8 *buffer );
PIPP_PREHEAD RS_INT32 PISTDAPI PIPP_Get_DLLVersion( enum PI_DLL_VERSION param,
                                               RS_INT32 *version );

/*  PIDC Family Versions  */
PREHEAD int PISTDAPI PIDC_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                char *buffer );
PREHEAD int PISTDAPI PIDC_Get_DLLVersion( enum PI_DLL_VERSION param,
                                          long *version );

/*  PIDP Family Versions  */
PREHEAD int PISTDAPI PIDP_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                char *buffer );
PREHEAD int PISTDAPI PIDP_Get_DLLVersion( enum PI_DLL_VERSION param,
                                          long *version );

/*  PIPCI Family Versions  */
PREHEAD int PISTDAPI PIPCI_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                 char *buffer );
PREHEAD int PISTDAPI PIPCI_Get_DLLVersion( enum PI_DLL_VERSION param,
                                           long *version );

/* PIXCMTXT Family Versions */
PITXT_PREHEAD RS_INT32  PISTDAPI   PIXCMTXT_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                char *buffer );
PITXT_PREHEAD RS_INT32  PISTDAPI   PIXCMTXT_Get_DLLVersion( enum PI_DLL_VERSION param,
                                          RS_INT32 *version );

/* PI133 Family Versions */
PI133_PREHEAD int  PISTDAPI   PI133_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                    char *buffer );
PI133_PREHEAD int  PISTDAPI   PI133_Get_DLLVersion( enum PI_DLL_VERSION param,
                                              long *version );

PI133_PREHEAD int PISTDAPI PI133_Get_DataFileVersion( const char *Filename,
													 RS_INT16 *Major,
													 RS_INT16 *Minor );

PISCC_PREHEAD RS_INT32 PISTDAPI PISCC_Get_DLLVersionString( enum PI_DLL_VERSION param,
                                                char *buffer );

PISCC_PREHEAD RS_INT32 PISTDAPI PISCC_Get_DLLVersion( enum PI_DLL_VERSION param,
                                          long *version );

#endif

/*  end of piverfcn.h  */