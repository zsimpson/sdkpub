// PItypes.h : type definitions and system constants for WinX/#@
//
/////////////////////////////////////////////////////////////////////////////
//   This revision:  $Revision: 1 $
//   Last check-in   $Date: 4/10/97 2:35p $
//   Last changes by $Author: Tim $
//   Changes:
/*   $Log: /EasyDLL95/Examples/Mltaccum/PiTypes.h $
*  
*  1     4/10/97 2:35p Tim
*  needed in project
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

#include <limits.h>
#include <float.h>

// Define a value for each application type which is stored in the file header
// and may be used elsewhere also.
enum APP_TYPE
{
    APP_UNKNOWN = 0,
    APP_WINVIEW,
    APP_WINSPEC,
    APP_WINLITE
};


/* Type definition of an internal  data transfer structure: */

/* datatype definition for binary data, see DATA structure */
enum DATATYPE
{
    X_UNKNOWN = 0,
    X_INT,				// rename to X_SHORT later (16bit signed)
    X_LONG,
    X_FLOAT,
    X_DOUBLE,
    X_BYTE,
    X_UNSIGNED_INT,		// rename to X_UNSIGNED_SHORT later	(16 bit unsigned)
    X_UNSIGNED_LONG,
    X_LASTTYPE,
//PI:DJK --> temp until X_INT 32bit is implemented
	X_SHORT = X_INT,
//PI:DJK --> temp until X_UNSIGNED_INT 32bit is implemented
	X_UNSIGNED_SHORT = X_UNSIGNED_INT,
    X_ENUM,              /* Used as information of data type in IsAvail functions.  */
    X_NODATATYPE,        /* used by IsAvail to specify no data type.                */
    X_BOOL               /* Boolean type (TRUE or FALSE).                           */
};

typedef struct
{
  void *address;    /* pointer to binary data stream */
  UINT  x_length;  /* x dimension */
  UINT  y_length;  /* y dimension */
  UINT  z_length;  /* z dimension */

  enum  DATATYPE  datatype;  /* SHORT, long double,... */
  SHORT datalength;/* size of data element */
  UINT  x_start;   /* start location */
  UINT  y_start;   /* start location */
  UINT  z_start;   /* start location (current frame number) */

  SHORT sourcecomp;/* number of source compensation pixels/scan */
  SHORT scrambled; /* flag to show if data is scambled=1 or not = 0 */
  void *fileslot;  /* link to the original file slot */
  void *block;     /* link to the original data block */
} DATA;

typedef void *PXDATA;

/*   xsma's calibration structure for x, y or z dimension  */
#define MAX_CAL_ORDER   5   /* current maximum order for polynom fits */
#define MAX_CAL_PIXEL   10  /* current number of calibration points */

enum XCALIBUNIT         /* definition of the calibration units */
{
    XW_NONE = 0,        /* error case */
    XW_SYSTEM,          /* relativ system units like channels,strips,frames... */
    XW_DATA,            /* absolut units including offset and linear factor */
    XW_POLYNOM,         /* polynomial calibration of user units */
    XW_WAVELENGTH,      /* polynomial calibration ofwavelength */
                        /* special types recalculated out of wavelength: */
    XW_ABSWAVENUM,      /*      wavenumber units */
    XW_RELWAVENUM,      /*      relative wavenumber units */
    XW_EVOLTS,          /*      electron volts */

    XW_XDUNITEND
};

enum CALIB_USAGE         /* definition of the calibration units */
{
    CALIB_USAGE_NONE = 0,        /* error case */
    CALIB_AUTO_SPECTRO,
    CALIB_MANUAL,
    CALIB_OFF,         
    CALIB_USAGE_END
};

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

typedef struct
{
  double offset;      /* offset for absolut data scaling */
  double factor;      /* factor for absolut data scaling */
  enum XCALIBUNIT current_unit;  /* selected scaling unit */
  CHAR reserved1;     /* reserved */
  CHAR string[40];    /* special string for scaling */
  CHAR reserved2[40]; /* reserved */
  BOOL calib_valid;   /* flag if calibration values are valid (TRUE/FALSE) */
  enum XCALIBUNIT input_unit;    /* shows the current input units of the "calib_value" */
                      /* see enum XCALIBUNIT */
  enum XCALIBUNIT polynom_unit;  /* shows which UNIT is linear in scaling and used */
                      /* in the "polynom_coeff" (see enum XCALIBUNIT) */
  CHAR polynom_order; /* ORDER of POLYNOM for calibration */
  CHAR calib_count;   /* number of valid calibration data pairs of */
                      /* "pixel_position" and "calib_value" */

  double pixel_position[MAX_CAL_PIXEL];   /* pixel LOCATION of calibration data */
  double calib_value[MAX_CAL_PIXEL];      /* calibration VALUE at above position */
  double polynom_coeff[MAX_CAL_ORDER+1];  /*  polynom COEFFICIENTS in wavelength/number */
  double laser_position;  /* laser wavenumber for relativ wavenumbers only */
  CHAR reserved3;     /* reserved */
  BYTE new_calib_flag;  /* If NOT 200, use defaults for below */
  CHAR calib_label[81];    /* Calibration label                  */
  CHAR expansion[87];      /* Expansion area                     */
} CALIBRATION;

/*---------------------------------------------------------------*/

enum PICTURE_TYPE
{
    WINX_NULL = 0,    // no window
    WINX_GRAPH,       // window with a single curve
    WINX_MULTIGRAPH,  // window with more than one graph
    WINX_3D_GRAPH,    // pseudo-3d window
    WINX_IMAGE,       // image with all features and full data
    WINX_MOVIE,       // image with limited features and 8 bit data

    WINX_TEXT,        // text window
    WINX_INFO,        // window with cursor value information
    WINX_STATUS,      // window with running experiment information

    WINX_GRAPHTYPE,   // window with one or more GRAPHS
    WINX_IMAGETYPE,   // window with IMAGE or MOVIE,...
    WINX_END          // indicates end of enum
};

enum PALETTE_TYPE     // type of color palette
{
  PT_MONO = 0,
  PT_FCOLOR,
  LINEAR_PALETTE,     // linear sequence of colors
  LOG_PALETTE         // logarithmic sequence of colors
};

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

#define MIN_CHAR           SCHAR_MIN          // MIN of type CHAR
#define MAX_CHAR           SCHAR_MAX          // MAX of type CHAR
#define MIN_UNSIGNED_CHAR  0                  // MIN of type UNSIGNED CHAR
#define MAX_UNSIGNED_CHAR  UCHAR_MAX          // MAX of type UNSIGNED CHAR

#define MIN_SHORT          (-32768)           // MIN of type SHORT
#define MAX_SHORT          32767              // MAX of type SHORT
#define MIN_USHORT         0                  // MIN of type UNSIGNED SHORT
#define MAX_USHORT         65535              // MAX of type UNSIGNED SHORT

#define MIN_INT            INT_MIN            // MIN of type INT
#define MAX_INT            INT_MAX            // MAX of type INT
#define MIN_UNSIGNED_INT   0                  // MIN of type UNSIGNED INT
#define MAX_UNSIGNED_INT   UINT_MAX           // MAX of type UNSIGNED INT

#define MIN_LONG           LONG_MIN           // MIN of type LONG
#define MAX_LONG           LONG_MAX           // MAX of type LONG
#define MIN_UNSIGNED_LONG  0                  // MIN of UNSIGNED LONG
#define MAX_UNSIGNED_LONG  ULONG_MAX          // MAX of UNSIGNED LONG

#define POS_MIN_FLOAT      FLT_MIN            // positive MIN of FLOAT
//      NEG_MIN_FLOAT      (-1.175494351e-38) // negative MIN of FLOAT
#define POS_MAX_FLOAT      FLT_MAX            // MAX of type FLOAT
#define NEG_MAX_FLOAT      (-3.402823466e38)  // negative MAX of FLOAT

#define POS_MIN_DOUBLE     DBL_MIN            // positive MIN of DOUBLE
//      NEG_MIN_DOUBLE     (-2.2250738585072014e-308)// positive MIN of DOUBLE
#define POS_MAX_DOUBLE     DBL_MAX            // MAX of type DOUBLE
#define NEG_MAX_DOUBLE     (-1.7976931348623158e308) // negative MAX of DOUBLE

#endif

//  end of PITYPES.H
