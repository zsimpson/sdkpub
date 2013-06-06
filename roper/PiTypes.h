/* PItypes.h : type definitions and system constants for WinX/32
*
*
*   This revision:  $Revision: 30 $
*   Last check-in   $Date: 5/01/02 11:49a $
*   Last changes by $Author: Croberts $
*   Changes:
*   $Log: /WinX32 V2.5/INCLUDE/PiTypes.h $
*  
*  30    5/01/02 11:49a Croberts
*  Added X_CHAR_PTR for strings.
*  
*  29    5/05/00 7:45a Terry
*  Add  APP_WINXTEST
*  
*  28    7/14/99 10:18a Bob
*  cleaned up data types..
*  
*  26    11/16/98 9:23a Maynard
*  Fix error in NO_MIDL_PARAM definition
*  
*  25    11/13/98 6:13p Maynard
*  Make MIDL_PARAM and NO_MIDL_PARAM macro defs here consistent with
*  previous defs in other headers (these defs should really be in stdafx.h
*  to be global)
*  
*  21    10/22/97 8:09a Dan
*  implemented MACROS for cleaner usage on MIDL compiler stuff
*  
*  20    9/05/97 11:59a Dan
*  moved Calibration definitions to "calibtypes.h"
*  moved Display & Palette definitions to "disptypes.h"
*  
*  19    9/02/97 1:56p Dan
*  updated emun DATATYPE for VisualUserInterFace typelibrary
*  
*  18    8/12/97 1:56p Dan
*  added conditional code for MIDL compilier
*      TypeLibrary for VisualBasic shows only 'enum DATATYPE'
*  
*  17    5/15/97 4:03p Maynard
*  Add PS_HIST palette shape (simpler variety of PS_GAUSS)
*  
*  16    5/15/97 2:39p Maynard
*  Make separate PALETTE_SHAPE and PALETTE_TYPE enums.
*  
*  15    5/02/97 4:06p Maynard
*  Give the DATA structure a type tag so we can forward reference pointers
*  to it
*  
*  14    4/15/97 12:36a Maynard
*  Rename and add to PALETTE_TYPES
*  
*  13    3/28/97 12:48p Baker
*  Added "enum" to CALIB_USAGE for c compilers
*  
*  12    3/28/97 8:45a Baker
*  Added m_wavecal_usage_flag to CALIBRATION.
*  
*  11    2/19/97 5:23p Baker
*  Replaced enum PANE_TYPE with enum PICTURE_TYPE for WINX_IMAGE's, etc
*  (there were two enums for the same thing, one here and one in
*  grafcon.h).  Added members PT_MONOand PT_FCOLOR to enum PALETTE_TYPE;
*  it now also replaces enumPAL_TYPE from cdib.h.
*  
*  10    1/30/97 9:57p Charlie
*  Added X_BOOL type.
*  
*  9     1/24/97 8:13p Charlie
*  Added X_ (enum and no type) types for IsAvail functions
*  
*  8     10/31/96 3:40p Dan
*  implemented DATATYPE enums X_SHORT & X_UNSIGNED_SHORT
*  once implementation of these datatype are underway, the DATATYPE
*     enum must be updated
*  
*  7     10/28/96 2:44p Dan
*  in DATA structure, changed from SHORT to UINT datatype variables that
*  can exceed SHORT
*  modified the MIN/MAX definitions to use MSVC's definitions
*  
*  6     10/15/96 1:21p Terry
*  define application types as enum
*  
*  5     10/10/96 9:30a Baker
*  Corrected bad bug in last version.
*  
*  4     10/10/96 9:11a Baker
*  Added some enums for cursor and image/graphs.
*  
*  3     9/09/96 2:56p Baker
*  Added enum CALIB_USAGE to replace #defines in calibrat.h for
*  m_calib_usage_flag  in grafstate.h.  
*  
*  2     8/21/96 4:43p Maynard
*  add silly temp typecast for PXDATA
*  
*  1     8/17/96 7:23p Maynard
*  
*/
/////////////////////////////////////////////////////////////////////////////

#ifndef PITYPES_H
#define PITYPES_H

// MACROS (streamline MIDL compiler usage)
#ifdef __midl
  #define MIDL_PARAM(Param, Desc)\
    [helpstring(Desc)] Param
  #define HIDE_MIDL_PARAM(Param, Desc)\
    [hidden, helpstring(Desc)] Param
  #define NO_MIDL_PARAM(Param, Desc)\
    [hidden, restricted, helpstring(Desc)] Param
#else
  #define MIDL_PARAM(Param, Desc) Param
  #define HIDE_MIDL_PARAM(Param, Desc) Param
  #define NO_MIDL_PARAM(Param, Desc) Param
#endif

#ifndef __cplusplus            /* disable warnings for: */
                               /* single line comment */
                               /* unref'd formal param */
                               /* struct def in () e.g. func(struct *s) (bad form) */
                               /* nameless struct/union */
                               /* bitfields other than int */
                               /* benign typdef redefinition */
                               /* assignment in conditional */
#pragma warning(disable: 4001 4100 4115 4201 4214 4209 4706) 
#endif

#ifndef __midl  // skip if TypeLibrary being defined
#include <limits.h>
#include <float.h>


// Define a value for each application type which is stored in the file header
// and may be used elsewhere also.
enum APP_TYPE
{
    APP_UNKNOWN = 0,
    APP_WINVIEW,
    APP_WINSPEC,
    APP_WINLITE,
    APP_WINXTEST
};
#endif

/* Type definition of an internal  data transfer structure: */

/* datatype definition for binary data, see DATA structure */
typedef enum DATATYPE
{
  NO_MIDL_PARAM(X_UNKNOWN,    "") = 0,
  MIDL_PARAM(X_SHORT,         "16 bit Integer" ) = 1,
  MIDL_PARAM(X_LONG,          "32 bit Integer") = 2,
  MIDL_PARAM(X_FLOAT,         "32 bit Single Precision Floating Point") = 3,
  MIDL_PARAM(X_DOUBLE,        "64 bit Double Precision Floating Point" )  = 4,
  MIDL_PARAM(X_BYTE,          "8 bit") = 5,
  MIDL_PARAM(X_UINT16,        "16 bit unsigned")  = 6,  // rename to X_UNSIGNED_SHORT later
  NO_MIDL_PARAM(X_ULONG ,     "32 bit unsigned") = 7,
  NO_MIDL_PARAM(X_LASTTYPE,   "") = 8,
  NO_MIDL_PARAM(X_ENUM,       "") = 9,
  NO_MIDL_PARAM(X_NODATATYPE, "") = 10, // used by IsAvail to specify no data type
  MIDL_PARAM(X_BOOL,          "Boolean") = 11,
  MIDL_PARAM(X_CHAR_PTR,      "string") = 13,
//********** PLACE NEW DATA TYPE ABOVE THIS LINE ***************//
//**************************************************************//
//**************************************************************//
#ifndef __midl  // skip if TypeLibrary being defined
    X_INT            = X_SHORT,
    X_UNSIGNED_INT   = X_UINT16,
    X_UNSIGNED_SHORT = X_UNSIGNED_INT,
    X_USHORT         = X_UNSIGNED_SHORT,    // shorten datatype name
    X_UNSIGNED_LONG  = X_ULONG,             // shorten datatype name      
    X_UINT32         = X_UNSIGNED_LONG,     // shorten datatype name      
#endif
} DATATYPE;


#ifndef __midl  // skip if TypeLibrary being defined

typedef struct DATA
{
  void *address;    /* pointer to binary data stream */
  RS_UINT32  x_length;  /* x dimension */
  RS_UINT32  y_length;  /* y dimension */
  RS_UINT32  z_length;  /* z dimension */

  enum  DATATYPE  datatype;  /* SHORT, long double,... */
  RS_INT16 datalength;/* size of data element */
  RS_UINT32  x_start;   /* start location */
  RS_UINT32  y_start;   /* start location */
  RS_UINT32  z_start;   /* start location (current frame number) */

  RS_INT16 sourcecomp;/* number of source compensation pixels/scan */
  RS_INT16 scrambled; /* flag to show if data is scambled=1 or not = 0 */
  void *fileslot;  /* link to the original file slot */
  void *block;     /* link to the original data block */
} DATA;

typedef void *PXDATA;

// Holdover from XVT used by PIXCMIF
typedef struct{
    short top;
    short left;
    short bottom;
    short right;
    } RCT;

/* XSMA integer format rectangle */
typedef struct{
    int top;
    int left;
    int bottom;
    int right;
    } IRCT;

/* XSMA double format rectangle */
typedef struct{
    double top;
    double left;
    double bottom;
    double right;
    } DRCT;

/*---------------------------------------------------------------*/

#if !defined (UNDEFINED)
#define UNDEFINED     -1
#endif

#if !defined (ON)
#define ON 1
#endif

#if !defined (OFF)
#define OFF 0
#endif

#if !defined (TRUE)
#define TRUE 1
#endif

#if !defined (FALSE)
#define FALSE 0
#endif

#define MAXLABEL_LEN 40      /* maximum number of CHARs for axis labels */
/* attention : never increase above 40 because of session file (dataman.c) */

/* max. length of a filename including drive and path */
#define MAX_PATH_LEN 100
/* attention : never increase above 100 because of session file (dataman.c) */

/* max length of program name */
#define MAX_PROGRAM_NAME 20

/* maximum resolution/dimension definition for images and graphs */
#define MAX_X_RESOLUTION   4098 /* currently only up to 3072 * .... */
#define MAX_Y_RESOLUTION   4098 /* currently only up to .... * 3072 */

/* maximum CHARacters per line in prSHORT window */
#define STATUS_MAXCHAR    120

/* definition of MIN and MAX of all data types */
/* These numubers are defined in LIMITS.H & FLOAT.H */

#define MIN_CHAR           SCHAR_MIN          /* MIN of type CHAR*/
#define MAX_CHAR           SCHAR_MAX          /* MAX of type CHAR*/
#define MIN_UNSIGNED_CHAR  0                  /* MIN of type UNSIGNED CHAR*/
#define MAX_UNSIGNED_CHAR  UCHAR_MAX          /* MAX of type UNSIGNED CHAR*/

#define MIN_SHORT          (-32768)           /* MIN of type SHORT*/
#define MAX_SHORT          32767              /* MAX of type SHORT*/
#define MIN_USHORT         0                  /* MIN of type UNSIGNED SHORT*/
#define MAX_USHORT         65535              /* MAX of type UNSIGNED SHORT*/

#define MIN_INT            INT_MIN            /* MIN of type INT*/
#define MAX_INT            INT_MAX            /* MAX of type INT*/
#define MIN_UNSIGNED_INT   0                  /* MIN of type UNSIGNED INT*/
#define MAX_UNSIGNED_INT   UINT_MAX           /* MAX of type UNSIGNED INT*/

#define MIN_LONG           LONG_MIN           /* MIN of type LONG*/
#define MAX_LONG           LONG_MAX           /* MAX of type LONG*/
#define MIN_UNSIGNED_LONG  0                  /* MIN of UNSIGNED LONG*/
#define MAX_UNSIGNED_LONG  ULONG_MAX          /* MAX of UNSIGNED LONG*/

#define POS_MIN_FLOAT      FLT_MIN            /* positive MIN of FLOAT*/
/*      NEG_MIN_FLOAT      (-1.175494351e-38) // negative MIN of FLOAT*/
#define POS_MAX_FLOAT      FLT_MAX            /* MAX of type FLOAT*/
#define NEG_MAX_FLOAT      (-3.402823466e38)  /* negative MAX of FLOAT*/

#define POS_MIN_DOUBLE     DBL_MIN            /* positive MIN of DOUBLE*/
/*      NEG_MIN_DOUBLE     (-2.2250738585072014e-308)// positive MIN of DOUBLE*/
#define POS_MAX_DOUBLE     DBL_MAX            /* MAX of type DOUBLE*/
#define NEG_MAX_DOUBLE     (-1.7976931348623158e308) /* negative MAX of DOUBLE*/

#endif // __midl

#ifdef MIDL_PARAM
#undef MIDL_PARAM 
#undef HIDE_MIDL_PARAM
#endif

#endif


/*  end of PITYPES.H*/
