/*   PI common platform defines
*    $Logfile: /WinX32 V2.5/INCLUDE/platform.h $
*       $Date: 5/14/02 9:55a $
******************************************************************
*
*       platform.h
*
******************************************************************
*
*  contains the Declarations & Enumerators for the different
*  platforms.
*                               written by C.G.R.
*
******************************************************************
*
*  last changes done by:
*
*  $Author: Dtrent $    $Date: 5/14/02 9:55a $
*
******************************************************************
*
*  $Log: /WinX32 V2.5/INCLUDE/platform.h $
*  
*  43    5/14/02 9:55a Dtrent
*  Added additional definitions for Linux
*  
*  42    3/14/02 12:28p Dknouse
*  added define for PI_WINDOWS_ME
*  
*  41    7/05/01 2:29p Bob
*  For Linux and Mac.
*  
*  40    12/02/99 3:19p Terry
*  Add SPECTYPE
*  
*  39    11/17/99 9:04a Bob
*  
*  38    10/11/99 3:01p Bob
*  Update From 2.4 and Linux Merge...
*  
*  36    2/09/99 1:09p Charlie
*  Replaced  old data type constants with new RS_
*  
*  35    1/21/99 2:45p Dan
*  removed conditional around 2 of the RS_ typedefs
*  
*  34    12/04/98 9:34a Bob
*  added RS_ to most types, but still left old ones in for now, but they
*  must be removed once all is converted..
*  
*  33    11/09/98 9:02a Maynard
*  #ifdef out two #defs which are typedefs in VC++ 6.0 (all those #defs
*  should be typedefs anyway)
*  
*  31    9/17/98 6:57a Dan
*  added special Acton defines from dllvers.h
*  
*  30    98/09/14 11:08 Shige
*  Mod for Mac
*
*  29    9/09/98 10:43a Bob
*  Removed NULL 0 for macintosh...
*
*  28    98/08/25 12:45 Shige
*  Added PIPETYPE for Private Exam DLL
*
*  27    98/08/07 11:24 Shige
*  Added PIERTYPE for Error DLL
*  Clean up
*
*  26    5/21/98 3:19p Bob
*  Added DOUBLE for the macintosh...
*
*  25    5/13/98 12:28p Bob
*  Latest Merger From Macintosh....
*
*  23    2/17/98 11:07a Bob
*  Latest Merge From SGI
*
*  22    1/21/98 1:45p Bob
*  Added Stuff for SYSV  may change in future HANDLE, LPCSTR etc...
*
*  20    12/05/97 10:57a Dan
*  implemented PITG_PREHEAD
*
*  19    9/17/97 2:42p Charlie
*  added define and prehead types for basic
*
*  18    8/18/97 2:19p Terry
*  Add PISPECTYPE
*
*  17    3/01/97 10:48a Dan
*  implemented use of PIDP_PREHEAD
*  changed comment about building DLLs its a 1
*
*  16    2/11/97 9:05p Charlie
*  Put back PISTDAPI to __stdcall for Borland compiles it is needed. We
*  have to live with the warnings.
*
*  15    1/28/97 5:28p Jenn
*
*  13    1/23/97 4:38p Maynard
*  Don't include windows.h (again) ifdef XSMA
*
*  12    12/16/96 1:18p Terry
*  Shige made me do it...
*
*  11    11/01/96 11:46a Shige
*  Added Macintosh
*
*  10    8/15/96 5:22p Maynard
*  Disable some warnings for Win32 C compilation
*
*  9     7/24/96 2:26p Dan
*  added #define __far to WIN32 section
*
*
*  8     7/18/96 2:02p Dan
*
*  7     7/11/96 9:33p Charlie
*  Moved dos define.
*
*  6     6/06/96 11:50a Charlie
*  Added pipptype to defines for Win3.1
*
*  5     6/03/96 11:02p Charlie
*  Added more dos defines.
*
*  4     5/07/96 5:08p Maynard
*  Made idempotent (#define PLATFORM_INCLUDED)
*
*  3     4/23/96 11:57a Charlie
*  Added special defines for prehead and pistdapi for win32 and dlls.
*
*  2     4/09/96 1:56p Charlie
*  defined interrupt as blank for win32.
*
*  1     4/05/96 1:45p Charlie
*  Platform dependent defines.
*
*
*******************************************************************/


/*******************************************************************************
  Supported Platforms:

    _DOS
    MACOS
    SGI
    SYSV
    WIN31
    WIN32

  Applications:

    MACAPPL
    PI133TYPE
    PICMTXT
    PIDPTYPE
    PIPETYPE    : PI Private Exam Type to check a new DLL
    PIPPTYPE
    PISCCTYPE
    PISPECTYPE
    PITGTYPE
    PITXTTYPE
    PIXBMTYPE
    PIXCM
    PIXCMTYPE
    SPECTTYPE
    XSMA


  What is defined here:

    #define INT16
    #define INT32
    #define INT8
    #define UINT
    #define UINT16
    #define UINT32
    #define UINT8

    #define BOOL
    #define BYTE
    #define DOUBLE
    #define DWORD
    #define SHORT
    #define USHORT
    #define WORD

    #define __export
    #define __far
    #define __huge
    #define _far
    #define _near
    #define far
    #define FAR
    #define FARPROC
    #define HANDLE
    #define HGLOBAL
    #define HINSTANCE
    #define huge
    #define interrupt
    #define LPCSTR
    #define LPTSTR
    #define NULL
    #define PASCAL
    #define pascal
    #define PLOADDS

    #define PISTDAPI
    #define PIXCMHNDLE

    #define PREHEAD         : this is PIXCM!
    #define PI133_PREHEAD
    #define PIDP_PREHEAD
    #define PIPE_PREHEAD
    #define PIPP_PREHEAD
    #define PISCC_PREHEAD
    #define PISPEC_PREHEAD
    #define PITG_PREHEAD
    #define PITXT_PREHEAD
    #define PIXBM_PREHEAD


********************************************************************************/


/*******************************************************************************
        include files
********************************************************************************/

/*******************************************************************************
        defines
********************************************************************************/
#ifndef PLATFORM_INCLUDED
#define PLATFORM_INCLUDED

/* handle to controller object. */
#define PIXCMHNDLE long    /* may change by platform. */

/* For WDM, Windows 95, NT Style Driver need to know specific os */
#define PI_WINDOWS_95  1
#define PI_WINDOWS_98  2
#define PI_WINDOWS_NT4 3
#define PI_WINDOWS_NT5 4
#define PI_WINDOWS_ME  5

/*----- Basic Data Type definitions -------------------------------------------*/

#if defined(WIN32) || defined(WIN31) || defined(SYSV) || defined(MACOS) || defined(SGI) || defined(LINUX)


  typedef char              RS_INT8;
  typedef unsigned char     RS_UINT8;
  typedef short             RS_INT16;
  typedef unsigned short    RS_UINT16;
  typedef long              RS_INT32;
  typedef unsigned long     RS_UINT32;
  typedef char              RS_BOOL;
  typedef int               RS_INT;     /* Use when size doesn't matter (16/32/64) */
  typedef unsigned int      RS_UINT;    /* Use when size doesn't matter (16/32/64) */
  typedef double            RS_DOUBLE;
  typedef float             RS_FLOAT;   /* Use only when needed (i.e. sscanf ) */

#define RS_HANDLE long

  #if defined(SYSV) || defined(SGI) || defined(MACOS) || defined(LINUX)
    #define SHORT  int
    #define HANDLE long
    #define BOOL short
    #define LPTSTR char*
    #define LPCSTR char*
    #define LPCTSTR const char*
    #define HGLOBAL unsigned long
    #define DWORD unsigned long
    #define USHORT unsigned int
    #define DOUBLE double
  #endif

#endif


/*----- PREHEAD collections for WIN32 DLL -------------------------------------*/
#if defined(WIN32)

  /* PIPPTYPE = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PIPPTYPE)
    #define PIPP_PREHEAD __declspec( dllexport )
  #else
    #define PIPP_PREHEAD __declspec( dllimport )
  #endif /* end pipptype */

  /* PIXCMTYPE = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PIXCMTYPE)
    #define PREHEAD __declspec( dllexport )
  #else
    #define PREHEAD __declspec( dllimport )
  #endif  /* end PIXCMTYPE */

  /* PI133TYPE = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PI133TYPE)
    #define PI133_PREHEAD __declspec( dllexport )
  #else
    #define PI133_PREHEAD __declspec( dllimport )
  #endif  /* end PI133TYPE */

  /* PITXTTYPE = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PITXTTYPE)
    #define PITXT_PREHEAD __declspec( dllexport )
  #else
    #define PITXT_PREHEAD __declspec( dllimport )
  #endif  /* end PITXTTYPE */

  /* PIDPTYPE  = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PIDPTYPE)
    #define PIDP_PREHEAD __declspec( dllexport )
  #else
    #define PIDP_PREHEAD __declspec( dllimport )
  #endif

  /* PISPECTYPE  = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PISPECTYPE)
    #define PISPEC_PREHEAD __declspec( dllexport )
  #else
    #define PISPEC_PREHEAD __declspec( dllimport )
  #endif

  /* PIXBMTYPE = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PIXBMTYPE)
    #define PIXBM_PREHEAD __declspec( dllexport )
  #else
    #define PIXBM_PREHEAD __declspec( dllimport )
  #endif  /* end PIXCMTYPE */

  /* PITGTYPE  = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PITGTYPE)
    #define PITG_PREHEAD __declspec( dllexport )
  #else
    #define PITG_PREHEAD __declspec( dllimport )
  #endif

  /* PISCCTYPE  = 1 if building dll, 0 if outside program using dlls. */
  #if defined(PISCCTYPE)
    #define PISCC_PREHEAD __declspec( dllexport )
  #else
    #define PISCC_PREHEAD __declspec( dllimport )
  #endif

  /* #define PIERTYPE if building dll, do nothing if outside program using dlls. */
  #if defined(PIERTYPE)
    #define PIER_PREHEAD __declspec( dllexport )
  #else
    #define PIER_PREHEAD __declspec( dllimport )
  #endif

  /* PIPETYPE */
  #if defined(PIPETYPE)
    #define PIPE_PREHEAD __declspec( dllexport )
  #else
    #define PIPE_PREHEAD __declspec( dllimport )
  #endif

  /* SPECTTYPE = 1 if building dll, 0 if outside program using dlls. */
  #if defined(SPECTTYPE)
    #define SPECT_PREHEAD __declspec( dllexport )
  #else
    #define SPECT_PREHEAD __declspec( dllimport )
  #endif  /* end SPECTTYPE */



#else /* Other than WIN32, PREHEAD is empty */

  #define PREHEAD
  #define PI133_PREHEAD
  #define PIDP_PREHEAD
  #define PIER_PREHEAD
  #define PIPE_PREHEAD
  #define PIPP_PREHEAD
  #define PISCC_PREHEAD
  #define PISPEC_PREHEAD
  #define PITG_PREHEAD
  #define PITXT_PREHEAD
  #define PIXBM_PREHEAD
  #define SPECT_PREHEAD

#endif /* for PREHEAD collections */



/*----- DOS Specific definitions ----------------------------------------------*/

#if defined(_DOS)

  #define PLOADDS
  #define PISTDAPI
  #define NULL 0
  #define HINSTANCE long
  #define UINT unsigned int

  #ifndef FAR
    #define FAR _far
  #endif

  #define PASCAL
  #define BYTE char
  #define WORD unsigned int
  #define DWORD unsigned long
  #define FARPROC long *

#endif /* _DOS */


/*----- SYSV Specific definitions ---------------------------------------------*/

#if defined(SYSV) || defined(SGI) || defined(LINUX)

  #define PLOADDS
  #define PISTDAPI
  #define NULL 0
  #define HINSTANCE long
  #define UINT unsigned int

  #define huge
  #define far

  #define TRUE 1
  #define FALSE 0
#endif /* SYSV */


/*----- WIN32 Specific definitions --------------------------------------------*/

#if defined(WIN32)

  #define huge
  #define far
  #define interrupt
  #define _near
  #define _far
  #define __huge
  #define __far
  #define PLOADDS

  #ifndef __cplusplus
    #pragma warning(disable: 4001 4100 4115 4201 4214 4209 4706)
  #endif

  #ifndef XSMA
    #include <windows.h>
  #endif

  #define PISTDAPI __stdcall /* we need this for Borland to WORK!!! */


#endif /* WIN32 */


/*----- WIN31 Specific definitions --------------------------------------------*/

#if defined(WIN31)

  #if defined(XSMA) || defined(PIXCM) || defined(PICMTXT) || defined(PIPPTYPE)

    #include <windows.h>

    #define PISTDAPI _export FAR PASCAL
    #define PLOADDS pascal __loadds

  #endif

#endif /* WIN31 */


/*----- Macintosh Specific definitions ----------------------------------------*/

#if defined(MACOS) 

  #define PLOADDS
  #define PISTDAPI
  #define HINSTANCE long
  #define UINT unsigned int
  #define huge
  #define far
  #define interrupt
  #define _near
  #define _far
  #define __huge
  #define __far
  #define __export
  #define _cdecl
  #if !defined(MACAPPL) /* Mac has pascal key word! */
    #define pascal
  #endif

#endif /* MACOS */

/*----- Linux Specific definitions ----------------------------------------*/
#if defined(LINUX) 

  #define PLOADDS
  #define PISTDAPI
  #define HINSTANCE long
  #define UINT unsigned int
  #define huge
  #define far
  #define interrupt
  #define _near
  #define _far
  #define __huge
  #define __far
  #define __export
  #define _cdecl
  #define pascal
  #define __stdcall
  #define __cdecl
#endif /* LINUX  */

/*  special re-defines for use with Acton Special  */
#if defined(_WINSPEC) || defined(_ACTON)
#define _WINSPEC_X 1
#endif
#if defined(_WINSPEC) && !defined(_ACTON)
#define _WINSPEC_ONLY 1
#endif

#if defined(MACOS) || defined(LINUX)
	#define PIPPHNDLE RS_UINT32
#endif

#endif  /* PLATFORM_INCLUDED */

/**********************************************************************
        end of platform.h
**********************************************************************/
