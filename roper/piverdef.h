/*   title   :  Get DLL Version definitions
*
*    $Logfile: /WinX32 V2.5/INCLUDE/piverdef.h $
*       $Date: 6/18/03 15:21 $
******************************************************************************
*
*
*
*
*       piverdef.h
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
*  $Author: Skatsumata $                     $Date: 6/18/03 15:21 $
*
******************************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/piverdef.h $
*  
*  21    6/18/03 15:21 Skatsumata
*  Added PI133B2.DAT version
*  
*  20    12/17/99 10:49a Terry
*  Another interim check-in on the road to generic spectrometers
*  
*  19    12/02/99 3:20p Terry
*  Intermediate point in Generic Spectrograph project to allow other work
*  to go on
*  
*  18    7/19/99 2:02p Bob
*  Added Version Info to pichipdb.dll
*  
*  15    8/03/98 11:29a Dan
*  added LIBTIFF
*  
*  13    5/07/98 10:20a Dan
*  added NVRAM definitions to enum PI_DLL_VERSION
*  
*  11    12/05/97 1:53p Dan
*  implemented PITG definitions
*  
*  10    11/11/97 1:26p Terry
*  Add PISPEC Version defines
*  
*  9     11/11/97 9:08a Bob
*  added 5 megahertz data file
*  
*  8     11/10/97 12:58p Bob
*  Added Version info for PISCC and PIIP
*  
*  6     6/02/97 2:42p Dan
*  documentation changes
*  
*  5     7/18/96 2:02p Dan
*  
*  4     6/06/96 1:56p Dan
*  updated supported comments
*  
*  3     6/05/96 1:58p Dan
*  renamed enum PIXCM_VERSION to PI_DLL_VERSION
*  added to enum PI_DLL_VERSION other DLLs
* 
* 2     3/08/96 11:20a Dan
* implemented additional V1.4 changes
* 
*       3/07/96 10:14a Dan
* added PI133_DLL_VERSION to enum
* 
* 1     3/08/96 8:32a Dan
* implemented V1.4 changes
* 
*       3/06/96 5:11p Dan
* implementing 'PICM_Get_DLLVersionString'
*
*
******************************************************************************
*/

#if !defined  PIVERDEF_H
#define       PIVERDEF_H

/*
******************************************************************************
        include files
*/


/*
******************************************************************************
        defines
*/

/*  enum table for PICM_Get_DLLVersionString  */
/*                 PIPP_Get_DLLVersionString  */
/*                 PIDC_Get_DLLVersionString  */
/*                 PIDP_Get_DLLVersionString  */
/*                 PIPCI_Get_DLLVersionString */
enum PI_DLL_VERSION             /*  supported by function prefix:    */
{                               /* PICM | PIPP | PIDC | PIDP | PIIP  */
    PIXCM_PRODUCT_VERSION = 1,  /*  YES |      |      |      |       */
    PIXCM_DLL_VERSION,          /*  YES |      |      |      |       */
    PIXCMTXT_DLL_VERSION,       /*  YES |      |      |      |       */
    PI133_DLL_VERSION,          /*  YES |      |      |      |       */
    PI133_DATA_VERSION,         /*  YES |      |      |      |       */
    PIDC_PRODUCT_VERSION,       /*      |      |  YES |      |       */
    PIDC_DLL_VERSION,           /*      |      |  YES |      |       */
    PIDP_PRODUCT_VERSION,       /*      |      |      |  YES |       */
    PIDP_DLL_VERSION,           /*      |      |      |  YES |       */
    PIPP_PRODUCT_VERSION,       /*  YES |  YES |      |      |       */
    PIPP_DLL_VERSION,           /*  YES |  YES |      |      |       */
    PIIP_PRODUCT_VERSION,       /*      |      |      |      |  YES  */
    PIIP_DLL_VERSION,           /*      |      |      |      |  YES  */
    PISCC_PRODUCT_VERSION,      /*  YES |      |      |      |       */
    PISCC_DLL_VERSION,          /*  YES |      |      |      |       */
    PI133_DATA5MEG_VERSION,     /*      |      |      |      |       */
    PISPEC_PRODUCT_VERSION,     /*      |      |      |      |       */
    PISPEC_DLL_VERSION,         /*      |      |      |      |       */
    PITG_PRODUCT_VERSION,       /*      |      |      |      |       */
    PITG_DLL_VERSION,           /*      |      |      |      |       */
    NVRAM_PRODUCT_VERSION,      /*      |      |      |      |       */
    NVRAM_DLL_VERSION,          /*      |      |      |      |       */
    LIBTIFF_PRODUCT_VERSION,    /*      |      |      |      |       */
    LIBTIFF_DLL_VERSION,        /*      |      |      |      |       */
    PICHIPDB_PRODUCT_VERSION,   /*      |      |      |      |       */
    PICHIPDB_DLL_VERSION,       /*      |      |      |      |       */
    SPECT_PRODUCT_VERSION,      /*      |      |      |      |       */
    SPECT_DLL_VERSION,          /*      |      |      |      |       */
    PI133_DATA2M_VERSION        
};

/*
******************************************************************************
        function prototypes
*/

#endif

/*
        end of piverdef.h
******************************************************************************
*/
