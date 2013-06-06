/*****************************************************************************/
/*  hp871x.cpp                                                                */
/*  Copyright (C) 1998 Hewlett-Packard Company                               */
/*---------------------------------------------------------------------------*/
/*  Driver for hp871x, $instrument desc$                                     */
/*  Driver Version: A.01.00                                                  */
/*---------------------------------------------------------------------------*/
/*  This driver is compatible with the following VXIplug&play standards:     */
/*    WIN32 System Framework revision 4.0                                    */
/*    VISA revision 1.0 (does not work with VTL)                             */
/*****************************************************************************/

#define hp871x_REV_CODE    "A.01.00"  /* Driver Revision 10/23/98                    */

/*****************************************************************************/
/* Exactly one of the following must be defined for the program to           */
/*   compile correctly.                                                      */
/*                                                                           */
/* #define __hpux          (for compilation for HP-UX)                       */
/* #define WIN32           (for compilation for 32-bit Windows)              */
/*                                                                           */
/* In addition, if WIN32 is defined, _CVI_ may also be defined to indicate   */
/*   that the program is being compiled under LabWindows CVI 4.0 or          */
/*   greater.                                                                */
/*****************************************************************************/

/*****************************************************************************/
/* The following defines are intended to provide OS compatibility among      */
/*   Windows 32-bit and HP-UX C compilers.                                   */
/*****************************************************************************/

#ifdef __hpux
#define _fcvt    fcvt
#endif

#define _huge

/*****************************************************************************/

#include <stdlib.h>           /* prototype for malloc()  */
#include <string.h>           /* prototype for strcpy()  */
#include <stdio.h>            /* prototype for sprintf() */
#include <math.h>             /* prototype for pow()     */

#ifdef __hpux
#define _INCLUDE_HPUX_SOURCE                    USUALLY NEEDED
#define _INCLUDE_XOPEN_SOURCE_EXTENDED          USUALLY NEEDED
#include <sys/time.h>
#else
#include <windows.h>
#endif
#include <iostream.h>
#include <winbase.h>
#include <time.h>
#include "visa.h"
#include "871x_Cpp.h"

#define hp871x_ERR_MSG_LENGTH 256   /* size of error message buffer     */
#define ZERO_DELAY          0       /* Number of milliseconds to delay. */
                                    /*   See doDelay function.          */


/*****************************************************************************/
/*  The string below is used to do the instrument identification in the      */
/*    init routine.  The string matches the first part of the instrument's   */
/*    response to it's *IDN? command.                                        */
/*****************************************************************************/
/*  DEVELOPER:                                                               */
/*  This string should match the instrument's model, but should not attempt  */
/*    to match firmware revision as a rule.  For instance, suppose the       */
/*    instrument responds to *IDN? with                                      */
/*          HEWLETT-PACKARD, 83475B, rev A.01.14                             */
/*    The appropriate IDN_STRING would be                                    */
/*          HEWLETT-PACKARD, 83475                                           */
/*    or                                                                     */
/*          HEWLETT-PACKARD, 83475B                                          */
/*    depending on how similar letter revisions of the instrument are.       */
/*****************************************************************************/

#define hp8711A_IDN_STRING  "HEWLETT-PACKARD,8711A"
#define hp8711B_IDN_STRING  "HEWLETT-PACKARD,8711B"
#define hp8711C_IDN_STRING  "HEWLETT-PACKARD,8711C"
#define hp8712B_IDN_STRING  "HEWLETT-PACKARD,8712B"
#define hp8712C_IDN_STRING  "HEWLETT-PACKARD,8712C"
#define hp8713B_IDN_STRING  "HEWLETT-PACKARD,8713B"
#define hp8713C_IDN_STRING  "HEWLETT-PACKARD,8713C"
#define hp8714B_IDN_STRING  "HEWLETT-PACKARD,8714B"
#define hp8714C_IDN_STRING  "HEWLETT-PACKARD,8714C"

/* The below models are not yet fully supported in this driver revision  */
/* but are provided for demo and testing purposes only.  Use version	 */
/* A.02.00 or above of this driver for full compatibility with these	 */
/* analyzers.															 */	

#define hp8712ES_IDN_STRING  "HEWLETT-PACKARD,8712ES"
#define hp8712ET_IDN_STRING  "HEWLETT-PACKARD,8712ET"
#define hp8714ES_IDN_STRING  "HEWLETT-PACKARD,8714ES"
#define hp8714ET_IDN_STRING  "HEWLETT-PACKARD,8714ET"

/*****************************************************************************/
/*  VISA Globals data structure.                                             */
/*  It is desirable to store global variables in VISA rather than the        */
/*    driver.  This avoids having any state variables in the driver.  This   */
/*    structure defines the driver's global data.  Memory is allocated to    */
/*    this structure in the init function, which passes the pointer to VISA, */
/*    and every function which follows retrieves a pointer to it.            */
/*****************************************************************************/
/*  DEVELOPER:                                                               */
/*  Add additional globals under the "Instrument Specific" section.          */
/*  In driver functions,  The globals can then be referred to via the        */
/*  thisPtr pointer to the globals which is retrieved by the GET_GLOBALS     */
/*  macro.  GET_GLOBALS must be executed in each driver function before      */
/*  any references to thisPtr are made.                                      */
/*****************************************************************************/

struct hp871x_globals
{
    ViStatus     errNumber;
    char         errMessage[160];

    ViBoolean    errQueryDetect;

    ViInt32      dTime;

    ViUInt16     interfaceType;
	
        
        /**************************/
        /*  Instrument Specific   */
        /**************************/

	char        funcName[30];
};


/*****************************************************************************/
/*  Driver Message Strings.                                                  */
/*****************************************************************************/
/*  DEVELOPER:                                                               */
/*  Add instrument or instrument driver specific message to the bottom of    */
/*  list.                                                                    */
/*****************************************************************************/

#define hp871x_MSG_VI_OPEN_ERR            "vi was zero.  Was the hp871x_init() successful?"
#define hp871x_MSG_CONDITION              "condition"
#define hp871x_MSG_EVENT                  "event"	
#define hp871x_MSG_EVENT_HDLR_INSTALLED   "event handler is already installed for event happening"
#define hp871x_MSG_EVENT_HDLR_INST2       "Only 1 handler can be installed at a time."	
#define hp871x_MSG_INVALID_HAPPENING      "is not a valid happening."
#define hp871x_MSG_NOT_QUERIABLE          "is not queriable."	
#define hp871x_MSG_INVALID_STATUS         "Parameter 2 is invalid in function hp871x_error_message()."
#define hp871x_MSG_INVALID_STATUS_VALUE   "is not a valid viStatus value."
#define hp871x_MSG_INVALID_VI             "Parameter 1 is invalid in function hp871x_error_message()."  \
                                        "  Using an inactive ViSession may cause this error."	\
                                        "  Was the instrument driver closed prematurely?"
#define hp871x_MSG_NO_ERRORS              "No Errors"
#define hp871x_MSG_SELF_TEST_FAILED       "Self test failed." 	
#define hp871x_MSG_SELF_TEST_PASSED       "Self test passed."

#define hp871x_MSG_BOOLEAN                "Expected 0 or 1; Got %hd"
#define hp871x_MSG_REAL                   "Expected %lg to %lg; Got %lg"
#define hp871x_MSG_INT                    "Expected %hd to %hd; Got %hd"
#define hp871x_MSG_LONG                   "Expected %ld to %ld; Got %ld"
#define hp871x_MSG_LOOKUP                 "Error converting string response to integer"
#define hp871x_MSG_NO_MATCH               "Could not match request to valid choices!"
#define hp871x_MSG_MASS_STORAGE           "Error while accessing mass storage device"
#define hp871x_MSG_MEAS_CONFLICT          "Data/Parameters provided conflicts with measurement type or configuration"
#define hp871x_MSG_READ_MATCH             "Data/Value received does not match expected choices; or parameter value is not valid"
#define hp871x_MSG_PROG_LOAD              "Error (or syntax error) occured while loading program"
#define hp871x_MSG_FILE_NOT_FOUND         "Specified filename was not found.  Please check spelling and location of file"
#define hp871x_MSG_INVALID_CHANNEL        "Channel must equal 1 or 2"
#define hp871x_MSG_CHANNEL_OFF			  "Requested operation requires specified channel to be on"


#define VI_ERROR_PARAMETER1_MSG           "Parameter 1 is invalid"
#define VI_ERROR_PARAMETER2_MSG           "Parameter 2 is invalid"
#define VI_ERROR_PARAMETER3_MSG           "Parameter 3 is invalid"
#define VI_ERROR_PARAMETER4_MSG           "Parameter 4 is invalid"
#define VI_ERROR_PARAMETER5_MSG           "Parameter 5 is invalid"
#define VI_ERROR_PARAMETER6_MSG           "Parameter 6 is invalid"
#define VI_ERROR_PARAMETER7_MSG           "Parameter 7 is invalid"
#define VI_ERROR_PARAMETER8_MSG           "Parameter 8 is invalid"
#define VI_ERROR_PARAMETER9_MSG           "Parameter 9 is invalid"
#define VI_ERROR_PARAMETER10_MSG          "Parameter 10 is invalid"
#define VI_ERROR_PARAMETER11_MSG          "Parameter 11 is invalid"
#define VI_ERROR_PARAMETER12_MSG          "Parameter 12 is invalid"
#define VI_ERROR_PARAMETER13_MSG          "Parameter 13 is invalid"
#define VI_ERROR_PARAMETER14_MSG          "Parameter 14 is invalid"
#define VI_ERROR_PARAMETER15_MSG          "Parameter 15 is invalid"
#define VI_ERROR_PARAMETER16_MSG          "Parameter 16 is invalid"
#define VI_ERROR_PARAMETER17_MSG          "Parameter 17 is invalid"
#define VI_ERROR_PARAMETER18_MSG          "Parameter 18 is invalid"
#define VI_ERROR_FAIL_ID_QUERY_MSG        "Instrument IDN does not match."

#define INSTR_ERROR_INV_SESSION_MSG       "ViSession (parameter 1) was not created by this driver"
#define INSTR_ERROR_NULL_PTR_MSG          "NULL pointer detected"
#define INSTR_ERROR_RESET_FAILED_MSG      "reset failed"
#define INSTR_ERROR_UNEXPECTED_MSG        "An unexpected error occurred"
#define INSTR_ERROR_DETECTED_MSG          "Instrument Error Detected, call hp871x_error_query()."
#define INSTR_ERROR_LOOKUP_MSG            "String not found in table"
#define INSTR_ERROR_NO_LAST_COMMA         "no last comma found in IDN string"


/*****************************************************************************/
/*  Error table structure.                                                   */
/*    The first element of the table is the error number, the second is the  */
/*    error message.  Error numbers in the "VISA Generic" section of the     */
/*    table are defined in the VISA header files.  Error numbers in the      */
/*    "Instrument Specific" section are defined in the driver header file.   */
/*    All of the error messages are defined above.                           */
/*****************************************************************************/
/*  DEVELOPER:                                                               */
/*  Add instrument or instrument driver specific numbers to the driver       */
/*    header file.                                                           */
/*  Add instrument or instrument driver specific messages to the bottom of   */
/*    messages listed above.                                                 */
/*  Add instrument specific table entries to the "Instrument Specific"       */
/*    section of the table below.                                            */
/*****************************************************************************/

struct instrErrStruct
{
	ViStatus errStatus;
	ViString errMessage;
};

const static struct instrErrStruct instrErrMsgTable[] =
{
        /**************************/
        /*  Template Messages     */
        /**************************/

    { VI_ERROR_FAIL_ID_QUERY,             VI_ERROR_FAIL_ID_QUERY_MSG },
    { VI_ERROR_PARAMETER1,                VI_ERROR_PARAMETER1_MSG },
    { VI_ERROR_PARAMETER2,                VI_ERROR_PARAMETER2_MSG },
    { VI_ERROR_PARAMETER3,                VI_ERROR_PARAMETER3_MSG },
    { VI_ERROR_PARAMETER4,                VI_ERROR_PARAMETER4_MSG },
    { VI_ERROR_PARAMETER5,                VI_ERROR_PARAMETER5_MSG },
    { VI_ERROR_PARAMETER6,                VI_ERROR_PARAMETER6_MSG },
    { VI_ERROR_PARAMETER7,                VI_ERROR_PARAMETER7_MSG },
    { VI_ERROR_PARAMETER8,                VI_ERROR_PARAMETER8_MSG },
    { hp871x_INSTR_ERROR_PARAMETER9,      VI_ERROR_PARAMETER9_MSG },
    { hp871x_INSTR_ERROR_PARAMETER10,     VI_ERROR_PARAMETER10_MSG },
    { hp871x_INSTR_ERROR_PARAMETER11,     VI_ERROR_PARAMETER11_MSG },
    { hp871x_INSTR_ERROR_PARAMETER12,     VI_ERROR_PARAMETER12_MSG },
    { hp871x_INSTR_ERROR_PARAMETER13,     VI_ERROR_PARAMETER13_MSG },
    { hp871x_INSTR_ERROR_PARAMETER14,     VI_ERROR_PARAMETER14_MSG },
    { hp871x_INSTR_ERROR_PARAMETER15,     VI_ERROR_PARAMETER15_MSG },
    { hp871x_INSTR_ERROR_PARAMETER16,     VI_ERROR_PARAMETER16_MSG },
    { hp871x_INSTR_ERROR_PARAMETER17,     VI_ERROR_PARAMETER17_MSG },
    { hp871x_INSTR_ERROR_PARAMETER18,     VI_ERROR_PARAMETER18_MSG },
    { hp871x_INSTR_ERROR_INV_SESSION,     INSTR_ERROR_INV_SESSION_MSG },
    { hp871x_INSTR_ERROR_NULL_PTR,        INSTR_ERROR_NULL_PTR_MSG },
    { hp871x_INSTR_ERROR_RESET_FAILED,    INSTR_ERROR_RESET_FAILED_MSG },
    { hp871x_INSTR_ERROR_UNEXPECTED,      INSTR_ERROR_UNEXPECTED_MSG },
    { hp871x_INSTR_ERROR_DETECTED,        INSTR_ERROR_DETECTED_MSG },
    { hp871x_INSTR_ERROR_LOOKUP,          INSTR_ERROR_LOOKUP_MSG },
    { hp871x_INSTR_NO_LAST_COMMA,         INSTR_ERROR_NO_LAST_COMMA }, 

        /**************************/
        /*  Instrument Specific   */
        /**************************/

	{ hp871x_NO_MATCH_ERROR,              hp871x_MSG_NO_MATCH }, 
	{ hp871x_MASS_STORAGE_ERROR,          hp871x_MSG_MASS_STORAGE},
	{ hp871x_MEAS_CONFLICT_ERROR,         hp871x_MSG_MEAS_CONFLICT},
	{ hp871x_READ_MATCH_ERROR,            hp871x_MSG_READ_MATCH},
	{ hp871x_PROG_LOAD_ERROR,             hp871x_MSG_PROG_LOAD},
	{ hp871x_FILE_NOT_FOUND_ERROR,        hp871x_MSG_FILE_NOT_FOUND},
	{ hp871x_INVALID_CHANNEL_ERROR,       hp871x_MSG_INVALID_CHANNEL},
	{ hp871x_CHANNEL_OFF_ERROR,			  hp871x_MSG_CHANNEL_OFF}
};


/*****************************************************************************/
/*****************************************************************************/
/********************                                     ********************/
/**********                                                         **********/
/****                   SUPPORTING MACROS AND FUNCTIONS                   ****/
/**                                                                         **/
/**-------------------------------------------------------------------------**/
/**     These macros and functions are not exposed to the user, but         **/
/**     are used by other functions in the driver.                          **/
/****                                                                     ****/
/**********                                                         **********/
/********************                                     ********************/
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
/*  SWAP MACROS                                                              */
/*****************************************************************************/
/*  Reorders bytes where instrument byte ordering of integers and reals      */
/*    differs from the computing framework.                                  */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    dest                                                                   */
/*      The number to be reordered.  The reordered result is also stored in  */
/*      this variable on completion.                                         */
/*****************************************************************************/
/*  DEVELOPER:                                                               */
/*  You can remove the SWAP macros if you do not have block IO (arbitrary    */
/*  block) if you do then you must also remove the routines that use them    */
/*  (_cmd_arr... functions)                                                  */
/*****************************************************************************/

#define SWAP_FLOAT64(dest)                                         \
 { unsigned char    src[8];                                        \
      *((double *)src) = *((double *)dest);                        \
      ((unsigned char *)(dest))[0] =  ((unsigned char*)(src))[7];  \
      ((unsigned char *)(dest))[1] =  ((unsigned char*)(src))[6];  \
      ((unsigned char *)(dest))[2] =  ((unsigned char*)(src))[5];  \
      ((unsigned char *)(dest))[3] =  ((unsigned char*)(src))[4];  \
      ((unsigned char *)(dest))[4] =  ((unsigned char*)(src))[3];  \
      ((unsigned char *)(dest))[5] =  ((unsigned char*)(src))[2];  \
      ((unsigned char *)(dest))[6] =  ((unsigned char*)(src))[1];  \
      ((unsigned char *)(dest))[7] =  ((unsigned char*)(src))[0];  \
 }

#define SWAP_32(dest)                                              \
 { unsigned char    src[4];                                        \
      *((long *)src) = *((long *)dest);                            \
      ((unsigned char *)(dest))[0] =  ((unsigned char*)(src))[3];  \
      ((unsigned char *)(dest))[1] =  ((unsigned char*)(src))[2];  \
      ((unsigned char *)(dest))[2] =  ((unsigned char*)(src))[1];  \
      ((unsigned char *)(dest))[3] =  ((unsigned char*)(src))[0];  \
 }

#define SWAP_16(dest)                                              \
 { unsigned char    src[2];                                        \
      *((int *)src) = *((int *)dest);                              \
      ((unsigned char *)(dest))[0] =  ((unsigned char*)(src))[1];  \
      ((unsigned char *)(dest))[1] =  ((unsigned char*)(src))[0];  \
 }


/*****************************************************************************/
/*  MACRO GET_GLOBALS                                                        */
/*****************************************************************************/
/*  Returns a pointer to the VISA globals storage.  This storage was         */
/*    allocated in init, but it is turned over to VISA to avoid holding      */
/*    state variables in the driver.                                         */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession            instrumentHandle                                  */
/*      The instrument's VISA address.                                       */
/*    struct hp871x_globals  *thisPtr                                        */
/*      A pointer to the VISA globals storage                                */
/*    funcname                                                               */
/*      The name of the function to be stored with the context dependent     */
/*      error information.                                                   */
/*****************************************************************************/

#define GET_GLOBALS(instrumentHandle,thisPtr)                                \
{                                                                            \
    errStatus = viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA,          \
                                                      (ViAddr) &thisPtr);    \
    if (errStatus < VI_SUCCESS)                                              \
        return errStatus;                                                    \
}


/*****************************************************************************/
/*  DELAY Functions                                                          */
/*  setDelay (located prior to init function) sets the delay time for the    */
/*    instrument.                                                            */
/*  doDelay uses delay time to slow down the driver after a read request.    */
/*---------------------------------------------------------------------------*/
/*  In some SCPI instruments, the instrument cannot change its state to      */
/*    'processing a read request' fast enough to keep another request        */
/*    from getting through to the instrument.  By setting a short delay      */
/*    (less than 100 microseconds should be sufficient) after each read,     */
/*    the driver will wait a sufficient amount of time before attempting     */
/*    to send the next string to the instrument.                             */
/*  DO NOT document these function in the fp file or the help file.  They    */
/*    are intended to address problems in specific instruments, problems     */
/*    that may only appear on faster CPU's.  They are designed so that the   */
/*    problem can be addressed quickly in the field once it is identified.   */
/*  If the problem is identified by driver developers, a 100 ms delay        */
/*    should be set in the hp871x_init function.  The template version of    */
/*    init currently sets the delay to 0.                                    */
/*****************************************************************************/

/*****************************************************************************/
static void doDelay(
        ViInt32 delayTime)
/*****************************************************************************/
/*  Delays execution for a specified number of microseconds.                 */
/*  Platform   Code    Tick Resolution  Tick Increment  Call Overhead        */
/*   WIN32     32-bit  CPU dependent    CPU dependent   0-20 us              */
/*   HP-UX     32-bit  1 us             CPU dependent   0-20 us              */
/*  PARAMETERS                                                               */
/*    long           delayTime (in)                                          */
/*      The number of micro-seconds to delay before proceeding.              */
/*****************************************************************************/

{
long   ticksToCount;

        /*************************************************************/
        /*  WIN32 Version                                            */
        /*  WIN32 increments depend on the hardware.  If high-       */
        /*    frequency counting isn't supported, revert to common   */
        /*    standard functions (same as WIN16).                    */
        /*  The call overhead to execute doDelay if high-frequency   */
        /*    is supported is about 25-30 micro-seconds.             */
        /*  The call overhead to execute doDelay if high-frequency   */
        /*    is -NOT- supported is ~10 milli-seconds on             */
        /*    Windows 95 & NT.                                       */
        /*************************************************************/
#ifdef WIN32

#ifdef _CVI_
#else
__int64  ticksPerSecond;
__int64  startTicks;
__int64  nowTicks;
#endif
DWORD    msTicks;

if (delayTime == 0)
    return;

#ifdef _CVI_
#else
if (QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond))
{
    ticksToCount = (long)((ticksPerSecond/1E6)*delayTime) + 1;
    QueryPerformanceCounter((LARGE_INTEGER *)&nowTicks);
    startTicks = nowTicks;
    while (nowTicks - startTicks < (DWORD)ticksToCount)
        QueryPerformanceCounter((LARGE_INTEGER *)&nowTicks);
}
else
#endif
{
    ticksToCount = (long)((1E3/1E6)*delayTime) + 1;
    msTicks = GetTickCount();
    while (GetTickCount() - msTicks < (DWORD)ticksToCount) ;
}

#endif

        /*************************************************************/
        /*  HP-UX Version                                            */
        /*  HP-UX counts in 1 micro-second increments.               */
        /*  The call overhead to execute doDelay on HP-UX is about   */
        /*    15-20 micro-seconds.                                   */
        /*************************************************************/
#ifdef __hpux

struct timeval t0, t1;

if (delayTime == 0)
    return;

/* printf("doDelay delaying %ld\n", ticks);  */ 
gettimeofday(&t0, NULL);
t0.tv_usec += delayTime;
t0.tv_sec += t0.tv_usec / 1000000;
t0.tv_usec = t0.tv_usec % 1000000;

gettimeofday(&t1, NULL);
while (t1.tv_sec < t0.tv_sec)
    gettimeofday(&t1, NULL);

if (t1.tv_sec > t0.tv_sec) return; /* get out quick if past delay time */

while (t1.tv_usec < t0.tv_usec)
    gettimeofday(&t1, NULL);

#endif

return;
}        /* ----- end of function ----- */


/*****************************************************************************/
static ViStatus delayVScanf(
        ViSession  instrumentHandle,
        ViString   scanFmt,
        ... ) 
/*****************************************************************************/
/*  Same as viVScanf, but with a delay added if necessary.                   */
/*                                                                           */
/*  PARAMETERS (same as viVScanf)                                            */
/*    ViSession   instrumentHandle (in)                                      */
/*    ViString    scanFmt (in)                                               */
/*    ...                                                                    */
/*****************************************************************************/

{
ViStatus  errStatus;
va_list   va;
struct hp871x_globals *thisPtr;
   
if ((errStatus = viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA,
                                             (ViAddr) &thisPtr)) < VI_SUCCESS)
    return errStatus;

va_start(va, scanFmt);
errStatus = viVScanf(instrumentHandle, scanFmt, va);
va_end(va);

if (thisPtr->dTime > 0)
    doDelay(thisPtr->dTime);

return errStatus;
}        /* ----- end of function ----- */



/*****************************************************************************/
static ViStatus delayVPrintf(
        ViSession  instrumentHandle,
       	ViString   printFmt,
        ...) 
/*****************************************************************************/
/*  Same as viVPrintf, but with a delay added if necessary.                  */
/*                                                                           */
/*  PARAMETERS (same as viVPrintf)                                           */
/*    ViSession   instrumentHandle (in)                                      */
/*    ViString    printFmt (in)                                              */
/*    ...                                                                    */
/*****************************************************************************/

{
ViStatus  errStatus;
va_list   va;
struct hp871x_globals *thisPtr;
   
if ((errStatus = viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA,
                                             (ViAddr) &thisPtr)) < VI_SUCCESS)
    return errStatus;

va_start(va, printFmt);
errStatus = viVPrintf(instrumentHandle, printFmt, va);
va_end(va);

if (thisPtr->dTime > 0)
    doDelay(thisPtr->dTime);

return errStatus;
}        /* ----- end of function ----- */


/*****************************************************************************/
static ViStatus delayVQueryf(
        ViSession  instrumentHandle,
        ViString   printFmt,
        ViString   scanFmt,
        ... ) 
/*****************************************************************************/
/*  Same as viVQueryf, but with a delay added if necessary.                  */
/*                                                                           */
/*  PARAMETERS (same as viVQueryf)                                           */
/*    ViSession   instrumentHandle (in)                                      */
/*    ViString    printFmt (in)                                              */
/*    ViString    scanFmt (in)                                               */
/*    ...                                                                    */
/*****************************************************************************/

{
ViStatus  errStatus;
va_list   va;
struct hp871x_globals *thisPtr;
   
if ((errStatus = viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA,
                                             (ViAddr) &thisPtr)) < VI_SUCCESS)
    return errStatus;

va_start(va, scanFmt);
errStatus = viVQueryf(instrumentHandle, printFmt, scanFmt, va);
va_end(va);

if (thisPtr->dTime > 0)
    doDelay(thisPtr->dTime);

return errStatus;
}        /* ----- end of function ----- */


/*****************************************************************************/
static ViStatus delayRead(
        ViSession  instrumentHandle,
        ViPBuf     buf,
        ViUInt32   cnt,
        ViPUInt32  retCnt) 
/*****************************************************************************/
/*  Same as viRead, but with a delay added if necessary.                     */
/*                                                                           */
/*  PARAMETERS (same as viRead)                                              */
/*    ViSession   instrumentHandle (in)                                      */
/*    ViPBuf      buf (in/out)                                               */
/*    ViUInt32    cnt (in)                                                   */
/*    ViPUInt32   retCnt (in)                                                */
/*****************************************************************************/

{
ViStatus  errStatus;
struct hp871x_globals *thisPtr;
   
if ((errStatus = viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA,
                                             (ViAddr) &thisPtr)) < VI_SUCCESS)
    return errStatus;

errStatus = viRead(instrumentHandle, buf, cnt, retCnt);

if (thisPtr->dTime > 0)
    doDelay(thisPtr->dTime);

return errStatus;
}        /* ----- end of function ----- */


/*****************************************************************************/
static ViStatus statusUpdate(
        ViSession  instrumentHandle,
        struct     hp871x_globals *thisPtr,
        ViStatus   s ) 
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession              instrumentHandle (in)                           */
/*    struct hp871x_globals *thisPtr (in)                                    */
/*      A pointer to the VISA globals for this VISA session                  */
/*    ViStatus               s (in)                                          */
/*      A driver error return code.                                          */
/*****************************************************************************/

{   
ViStatus  errStatus;
ViInt16   eventQ;

if (thisPtr)
    thisPtr->errNumber = s;

        /*************************************************************/
        /*  If error query detect is set on and the instrument       */
        /*    has not timed out, then ...                            */
        /*  Read the ESR byte into eventQ and check the error bits   */
        /*                                                           */
        /*  Potential ESR byte errors are 0x04 (Query Error),        */
        /*    0x08 (Device Dependent Error), 0x10 (Execution Error), */
        /*    and 0x20 (Command Error).                              */
        /*************************************************************/

if (thisPtr && thisPtr->errQueryDetect && s != VI_ERROR_TMO)
{   
    if ((errStatus = delayVQueryf(instrumentHandle, "*ESR?\n", "%hd%*t",
                                                       &eventQ)) < VI_SUCCESS)
        return VI_ERROR_SYSTEM_ERROR;

    if( (0x04  | 0x08  | 0x10  | 0x20) & eventQ )
        return hp871x_INSTR_ERROR_DETECTED;
}

return s;
}        /* ----- end of function ----- */


/*****************************************************************************/
/*  MACRO CHK_BOOLEAN                                                        */
/*****************************************************************************/
/*  Ref chk_boolean for info.                                                */
/*****************************************************************************/

#define CHK_BOOLEAN(chk_val, err)                          \
if (chk_boolean(thisPtr, chk_val))                         \
   {                                                       \
    thisPtr->errNumber = err;                                \
    return err;                                            \
   }


/*****************************************************************************/
static ViBoolean chk_boolean(
        struct     hp871x_globals *thisPtr,
        ViBoolean  chk_val)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    struct hp871x_globals *thisPtr (in)                                    */
/*      A pointer to the VISA globals for this VISA session                  */
/*    ViBoolean              chk_val (in)                                    */
/*      Check this value to make sure it is a legal Boolean.                 */
/*****************************************************************************/

{
ViChar message[hp871x_ERR_MSG_LENGTH];

if ( (chk_val != VI_TRUE) && (chk_val != VI_FALSE) )
{
    sprintf(message, hp871x_MSG_BOOLEAN, chk_val);	
    strcpy(thisPtr->errMessage, message);				
    return VI_TRUE;
}

return VI_FALSE;
}        /* ----- end of function ----- */


/*****************************************************************************/
/*  MACRO CHK_REAL_RANGE                                                     */
/*****************************************************************************/
/*  Ref chk_real_range for info.                                             */
/*****************************************************************************/

#define CHK_REAL_RANGE(chk_val, min, max, err)             \
if (chk_real_range(thisPtr, chk_val, min, max))            \
   {                                                       \
    thisPtr->errNumber = err;                                \
    return err;                                            \
   }


/*****************************************************************************/
static ViBoolean chk_real_range( 
        struct    hp871x_globals *thisPtr,
        ViReal64  chk_val,
        ViReal64  min,
        ViReal64  max)
/*****************************************************************************/
/*  Tests to see if a ViReal64 is in range.                                  */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    struct hp871x_globals *thisPtr (in)                                    */
/*      A pointer to the VISA globals for this VISA session                  */
/*    ViReal64             chk_val (in)                                      */
/*      The value to be checked.                                             */
/*    ViReal64             min (in)                                          */
/*      The bottom of the range.                                             */
/*    ViReal64             max (in)                                          */
/*      The top of the range.                                                */
/*****************************************************************************/

{
ViChar message[hp871x_ERR_MSG_LENGTH];

if ( (chk_val < min) || (chk_val > max) )  			
{								
    sprintf(message, hp871x_MSG_REAL, min, max, chk_val);	
    strcpy(thisPtr->errMessage, message);
    return VI_TRUE;
}

return VI_FALSE;
}        /* ----- end of function ----- */ 
 
  
/*****************************************************************************/
/*  MACRO CHK_INT_RANGE                                                      */
/*****************************************************************************/
/*  Ref chk_int_range for info.                                              */
/*****************************************************************************/

#define CHK_INT_RANGE(chk_val, min, max, err)              \
if (chk_int_range(thisPtr, chk_val, min, max) )            \
   {                                                       \
    thisPtr->errNumber = err;                                \
    return err;                                            \
   }


/*****************************************************************************/
static ViBoolean chk_int_range( 
        struct   hp871x_globals *thisPtr,
        ViInt16  chk_val,
        ViInt16  min,
        ViInt16  max)
/*****************************************************************************/
/*  Tests to see if a ViInt16 is in range.                                   */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    struct hp871x_globals *thisPtr (in)                                    */
/*      A pointer to the VISA globals for this VISA session                  */
/*    ViInt16              chk_val (in)                                      */
/*      The value to be checked.                                             */
/*    ViInt16              min (in)                                          */
/*      The bottom of the range.                                             */
/*    ViInt16              max (in)                                          */
/*      The top of the range.                                                */
/*****************************************************************************/

{
ViChar message[hp871x_ERR_MSG_LENGTH];

if ( (chk_val < min) || (chk_val > max) )  			
{								
    sprintf(message, hp871x_MSG_INT, min, max, chk_val);	
    strcpy(thisPtr->errMessage, message);
    return VI_TRUE;
}

return VI_FALSE;
}        /* ----- end of function ----- */ 
   
   
/*****************************************************************************/
/*  MACRO CHK_LONG_RANGE                                                     */
/*****************************************************************************/
/*  Ref chk_long_range for info.                                             */
/*****************************************************************************/

#define CHK_LONG_RANGE(chk_val, min, max, err)             \
if (chk_long_range(thisPtr, chk_val, min, max))            \
   {                                                       \
    thisPtr->errNumber = err;                                \
    return err;                                            \
   }


/*****************************************************************************/
static ViBoolean chk_long_range( 
        struct  hp871x_globals *thisPtr,
        ViInt32 chk_val,
        ViInt32 min,
        ViInt32 max)
/*****************************************************************************/
/*  Tests to see if a ViInt32 is in range.                                   */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    struct hp871x_globals *thisPtr (in)                                    */
/*      A pointer to the VISA globals for this VISA session                  */
/*    ViInt32              chk_val (in)                                       */
/*      The value to be checked.                                             */
/*    ViInt32              min (in)                                          */
/*      The bottom of the range.                                             */
/*    ViInt32              max (in)                                          */
/*      The top of the range.                                                */
/*****************************************************************************/

{
ViChar message[hp871x_ERR_MSG_LENGTH];

if ( (chk_val < min) || (chk_val > max) )  			
{								
    sprintf(message, hp871x_MSG_LONG, min, max, chk_val);	
    strcpy(thisPtr->errMessage, message);
    return VI_TRUE;
}

return VI_FALSE;
}        /* ----- end of function ----- */ 
   
   
/*****************************************************************************/
/*  MACRO CHK_ENUM                                                           */
/*****************************************************************************/
/*  Ref chk_enum for info.                                                   */
/*****************************************************************************/

#define CHK_ENUM( chk_val, limit, err )                    \
if (chk_enum( thisPtr, chk_val, limit) )                   \
   {                                                       \
    thisPtr->errNumber = err;                                \
    return err;                                            \
   }


/*****************************************************************************/
static ViBoolean chk_enum (
        struct hp871x_globals *thisPtr,
        ViInt16 chk_val,
        ViInt16 limit)
/*****************************************************************************/
/* Chk_enum searches for a string in an array of strings.  It is used by     */
/* the CHK_ENUM macro                                                        */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    struct hp871x_globals *thisPtr (in)                                    */
/*      A pointer to the VISA globals for this VISA session                  */
/*    ViInt16              chk_val (in)                                      */
/*      The value to be checked.                                             */
/*    ViInt16              limit (in)                                        */
/*      The upper limit of the enumeration values.                           */
/*****************************************************************************/

{
ViChar message[hp871x_ERR_MSG_LENGTH];

if ( ( chk_val < 0 ) || (chk_val > limit) )  			
{								
    sprintf(message, hp871x_MSG_INT, 0, limit, chk_val);	
    strcpy(thisPtr->errMessage, message);
    return VI_TRUE;
}

return VI_FALSE;
}        /* ----- end of function ----- */


/*****************************************************************************/
static ViStatus _VI_FUNC setDelay (
        ViSession  instrumentHandle,
        ViInt32    delayTime)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViInt32    delayTime (in)                                              */
/*      The delayTime in microseconds.  Must be between 0 and 1,000.  In     */
/*      practice, should never be set higher than 100.                       */
/*****************************************************************************/

{
ViStatus errStatus;
struct hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

CHK_LONG_RANGE(delayTime, 0L, 1000L, VI_ERROR_PARAMETER2);

thisPtr->dTime = delayTime;

thisPtr->errNumber = VI_SUCCESS;
return VI_SUCCESS;
}        /* ----- end of function ----- */


/*****************************************************************************/
static ViStatus _VI_FUNC initError(
        ViSession  vi,
        ViSession  defRM,
        ViStatus   errStatus)
/*****************************************************************************/
/*  This function is only called from hp871x_init.                           */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession      vi (in)                                                 */
/*      Instrument Handle returned by viOpen.                                */
/*    ViSession      defRM (in)                                              */
/*      Resource Manager handle from viOpen.                                 */
/*    ViStatus       errStatus (in)                                          */
/*      A driver error return code.                                          */
/*****************************************************************************/

{
viClose(vi);
viClose(defRM);
vi=VI_NULL;
return errStatus;
}        /* ----- end of function ----- */


/*****************************************************************************/
/*****************************************************************************/
/********************                                     ********************/
/**********                                                         **********/
/****                          DRIVER FUNCTIONS                           ****/
/**                                                                         **/
/**-------------------------------------------------------------------------**/
/**     The functions which are exposed to the driver user start here.      **/
/**     They are in the following order:                                    **/
/**        VPP required functions.                                          **/
/**        HP required utility functions                                    **/
/**        HP passthrough functions                                         **/
/**        Instrument specific functions                                    **/
/****                                                                     ****/
/**********                                                         **********/
/********************                                     ********************/
/*****************************************************************************/
/*****************************************************************************/




/*****************************************************************************/
ViStatus _VI_FUNC hp871x_init(
        ViRsrc resourceName,
        ViBoolean IDQuery,
        ViBoolean resetDevice,
        ViPSession instrumentHandle)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession      resourceName (in)                                       */
/*      The instrument's VISA address.                                       */
/*      GPIB Example: "GPIB0::20::INSTR"                                     */
/*    ViBoolean      IDQuery (in)                                            */
/*      If VI_TRUE, validate instrument identity                             */
/*    ViBoolean      resetDevice (in)                                        */
/*      If VI_TRUE, perform an instrument reset                              */
/*    ViPSession     instrumentHandle (out)                                  */
/*      Pointer to Instrument Handle.  Returns VI_NULL if the init fails.    */
/*****************************************************************************/

{
struct     hp871x_globals *thisPtr;
ViStatus   errStatus;
ViSession  defRM;
ViChar     idn_buf[256];

*instrumentHandle = VI_NULL;

        /*************************************************************/
        /* Find the Default Resource Manager.  Potential errors are  */
        /*   VI_ERROR_SYSTEM_ERROR, VI_ERROR_ALLOC                   */
        /*************************************************************/

if ((errStatus = viOpenDefaultRM(&defRM)) < VI_SUCCESS)
    return errStatus;

        /*************************************************************/
        /* Open a session to the instrument.  Potential errors are   */
        /*   VI_ERROR_NSUP_OPER, VI_ERROR_INV_RSRC_NAME,             */
        /*   VI_ERROR_INV_ACC_MODE, VI_ERROR_RSRC_NFOUND,            */
        /*   VI_ERROR_ALLOC                                          */
        /*************************************************************/

if ((errStatus = viOpen(defRM, resourceName, VI_NULL, VI_NULL,
                                              instrumentHandle)) < VI_SUCCESS)
{
    viClose(defRM);
    *instrumentHandle=VI_NULL;
    return errStatus;
}

        /*************************************************************/
        /* Allocate global memory for the session.  Inititalize the  */
        /*   memory.  Note that viSetAttribute should never fail,    */
        /*   as all of it's input conditions are satisfied.          */
        /*************************************************************/

if ((thisPtr =
         (struct hp871x_globals *)malloc(sizeof(struct hp871x_globals))) == 0)
{
    viClose(*instrumentHandle);
    viClose(defRM);
    *instrumentHandle=VI_NULL;
    return VI_ERROR_ALLOC;
}

if ((errStatus = viSetAttribute(*instrumentHandle, VI_ATTR_USER_DATA,
                                          (ViAttrState)thisPtr)) < VI_SUCCESS)
{
    viClose(*instrumentHandle);
    viClose(defRM);
    *instrumentHandle=VI_NULL;
    return errStatus;
}

        /*************************************************************/
        /* Set initial values of variables in global memory.         */
        /*************************************************************/

thisPtr->errNumber = VI_SUCCESS;
thisPtr->errMessage[0] = 0;
thisPtr->errQueryDetect = VI_FALSE;
thisPtr->dTime = 0;
//Instrument specific initializations


if ((errStatus = viGetAttribute(*instrumentHandle, VI_ATTR_INTF_TYPE,
                                       &thisPtr->interfaceType)) < VI_SUCCESS)
    return initError(*instrumentHandle, defRM, errStatus);


        /*************************************************************/
        /* Reset the instrument if so instructed.                    */
        /*   GPIB reset includes a 488.2 device clear.               */
        /*************************************************************/

if( VI_TRUE == resetDevice ) 
{
    if (thisPtr->interfaceType == VI_INTF_GPIB)
        if (viClear(*instrumentHandle) <  VI_SUCCESS)
            return initError(*instrumentHandle, defRM,
                                             hp871x_INSTR_ERROR_RESET_FAILED);

    if (hp871x_reset(*instrumentHandle) <  VI_SUCCESS)
        return initError(*instrumentHandle, defRM,
                                             hp871x_INSTR_ERROR_RESET_FAILED);
}

        /*************************************************************/
        /* Validate the instrument's identity.                       */
        /*************************************************************/

if( VI_TRUE == IDQuery ) 
	{
    if (thisPtr->interfaceType == VI_INTF_GPIB)
        if (viClear(*instrumentHandle) <  VI_SUCCESS)
            return initError(*instrumentHandle, defRM, VI_ERROR_FAIL_ID_QUERY);

    
		
   if ((viPrintf(*instrumentHandle, "*IDN?\n") < VI_SUCCESS )   
        || (delayVScanf(*instrumentHandle, "\"%t\n", idn_buf) < VI_SUCCESS )
        || ((strncmp(idn_buf, hp8711A_IDN_STRING, strlen(hp8711A_IDN_STRING))) 
			&& (strncmp(idn_buf, hp8711B_IDN_STRING, strlen(hp8711B_IDN_STRING)))
			&& (strncmp(idn_buf, hp8712B_IDN_STRING, strlen(hp8712B_IDN_STRING)))
			&& (strncmp(idn_buf, hp8713B_IDN_STRING, strlen(hp8713B_IDN_STRING)))
			&& (strncmp(idn_buf, hp8714B_IDN_STRING, strlen(hp8714B_IDN_STRING)))
			&& (strncmp(idn_buf, hp8711C_IDN_STRING, strlen(hp8711C_IDN_STRING)))
			&& (strncmp(idn_buf, hp8712C_IDN_STRING, strlen(hp8712C_IDN_STRING)))
			&& (strncmp(idn_buf, hp8713C_IDN_STRING, strlen(hp8713C_IDN_STRING)))
			&& (strncmp(idn_buf, hp8714C_IDN_STRING, strlen(hp8714C_IDN_STRING)))
			&& (strncmp(idn_buf, hp8712ES_IDN_STRING, strlen(hp8712ES_IDN_STRING)))
			&& (strncmp(idn_buf, hp8712ET_IDN_STRING, strlen(hp8712ET_IDN_STRING)))
			&& (strncmp(idn_buf, hp8714ES_IDN_STRING, strlen(hp8714ES_IDN_STRING)))
			&& (strncmp(idn_buf, hp8714ET_IDN_STRING, strlen(hp8714ET_IDN_STRING)))))
		return initError(*instrumentHandle, defRM, VI_ERROR_FAIL_ID_QUERY);
			
	}
if ((errStatus=hp871x_timeOut(*instrumentHandle, 10000)) < VI_SUCCESS)
    return statusUpdate(*instrumentHandle, thisPtr, errStatus);

return statusUpdate(*instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_close( 
        ViSession instrumentHandle)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession      instrumentHandle (in)                                   */
/*      Instrument Handle returned from hp871x_init()                        */
/*****************************************************************************/

{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViSession defRM;

GET_GLOBALS(instrumentHandle, thisPtr)

        /*************************************************************/
        /* Retrieve Resource Management session, free global memory  */
        /*   for the session (if it exists), and close the vi and    */
        /*   RM sessions.                                            */
        /*************************************************************/

if ((errStatus = viGetAttribute(instrumentHandle, VI_ATTR_RM_SESSION, &defRM))
                                                                 < VI_SUCCESS)
{
    thisPtr->errNumber = errStatus;
    return errStatus;
}

if (thisPtr)		
    free(thisPtr);

return viClose(defRM);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_reset( 
        ViSession instrumentHandle)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession      instrumentHandle (in)                                   */
/*      Instrument Handle returned from hp871x_init()                        */
/*****************************************************************************/

{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 timeout;


GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus=hp871x_timeOut_Q(instrumentHandle, &timeout)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);//Get cur tmo value

if ((errStatus=hp871x_timeOut(instrumentHandle, 10000)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);// 871xA/B need ~8 sec

if ((errStatus = hp871x_outputf(instrumentHandle, 2,"*RST")) < VI_SUCCESS)
	{
	hp871x_timeOut(instrumentHandle, timeout);
	return statusUpdate(instrumentHandle, thisPtr, errStatus);
	}

hp871x_timeOut(instrumentHandle, timeout); //Reset original tmo value
return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_self_test(
        ViSession instrumentHandle,
        ViPInt32  selfTestResult,
        ViPString selfTestMessage)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession   instrumentHandle (in)                                      */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32    selfTestResult (out)                                       */
/*      Self-test result                                                     */
/*    ViPString   selfTestMessage[] (out)                                    */
/*      Self-test status message string, limited to 256 characters.          */
/*****************************************************************************/

{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

*selfTestResult = -1; 
selfTestMessage[0] = 0; 

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle, "*TST?\n", "%d%*t",
                                                selfTestResult)) < VI_SUCCESS)
{
    *selfTestResult = -1; 
    return statusUpdate(instrumentHandle, thisPtr, errStatus);
}

switch( *selfTestResult)
{
    case 0:
        sprintf(selfTestMessage, hp871x_MSG_SELF_TEST_PASSED);
        break;

        /*************************************************************/
        /* DEVELOPER:  Add instrument specific self-test error       */
        /*   codes and messages here.                                */
        /*************************************************************/

    default:
        sprintf(selfTestMessage, hp871x_MSG_SELF_TEST_FAILED);
        break;
}

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_error_query(
        ViSession  instrumentHandle,
        ViPInt32   errorCode,
        ViPString  errorMessage)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession    instrumentHandle (in)                                     */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32     errorCode (out)                                           */
/*      An instrument error code                                             */
/*    ViPString    errorMessage[] (out)                                      */
/*      Instrument error message string, limited to 256 characters.          */
/*****************************************************************************/

{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

*errorCode = -1; 
errorMessage[0] = 0; 

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf( instrumentHandle, "SYST:ERR?\n", "%ld,%t",
                                       errorCode, errorMessage)) < VI_SUCCESS)
{
    *errorCode = -1; 
    errorMessage[0] = 0; 
    return statusUpdate(instrumentHandle, thisPtr, errStatus);
}

	/* get rid of extra LF at the end of the error_message */
errorMessage[strlen(errorMessage)-1] = 0;

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_error_message(
        ViSession  instrumentHandle,
        ViStatus   statusCode,
        ViPString  message)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession   instrumentHandle (in)                                      */
/*      Instrument Handle returned from hp871x_init()                        */
/*      May be VI_NULL for this function                                     */
/*    ViStatus    statusCode (in)                                            */
/*      The error return value from an instrument driver function            */
/*    ViPString   message[] (out)                                            */
/*      Error message string.  This is limited to 256 characters.            */
/*****************************************************************************/

{
struct    hp871x_globals *thisPtr;
ViStatus  errStatus;  
ViInt32   idx;

message[0] = 0;

thisPtr = NULL;
if (instrumentHandle != VI_NULL)
    GET_GLOBALS(instrumentHandle, thisPtr)

if (statusCode == VI_SUCCESS)
{
    sprintf(message, hp871x_MSG_NO_ERRORS);
    thisPtr->errNumber = VI_SUCCESS;
    return VI_SUCCESS;
}

        /*************************************************************/
        /* Search the error message table to see if the error is in  */
        /*   that table.  If it is, copy the corresponding error     */
        /*   message to the output error message.  If context        */
        /*   dependent error messages are being used, append the     */
        /*   context dependent information to the message.           */
        /* If the error is found in the table, exit the routine      */
        /*   successfully.                                           */
        /*************************************************************/

for (idx=0; idx < (sizeof instrErrMsgTable / 
	           sizeof(struct instrErrStruct)); idx++)
{
    if (instrErrMsgTable[idx].errStatus == statusCode)
    {
        if ((thisPtr) && (thisPtr->errNumber == statusCode))
        {
            sprintf(message, "%s;  %s",
                    instrErrMsgTable[idx].errMessage,
                    thisPtr->errMessage);
        }
        else
            strcpy(message, instrErrMsgTable[idx].errMessage);
        
        thisPtr->errNumber = VI_SUCCESS;
        return VI_SUCCESS;
    }
}

        /*************************************************************/
        /* Check to see if the error is a VTL/VISA error number      */
        /*   using viStatusDesc, which will also return the error    */
        /*   message.  If context dependent error messages are       */
        /*   used, append the context dependent information to the   */
        /*   message.                                                */
        /* If the error is found in the table, exit the routine      */
        /*   successfully.                                           */
        /*************************************************************/

errStatus = viStatusDesc(instrumentHandle, statusCode, message);
if (errStatus == VI_SUCCESS)
{
    if( (thisPtr) && (thisPtr->errNumber == statusCode))
    {
        strcat(message, ";  ");
        strcat(message, thisPtr->errMessage);
    }

    thisPtr->errNumber = VI_SUCCESS;
    return VI_SUCCESS;
}

        /*************************************************************/
        /*   At this point vi is either INVALID or VI_NULL           */
        /*************************************************************/

if (instrumentHandle == VI_NULL)
{
    strcpy(message, hp871x_MSG_VI_OPEN_ERR);
    thisPtr->errNumber = VI_SUCCESS;
    return VI_SUCCESS;
} 

sprintf(message, hp871x_MSG_INVALID_STATUS "  %ld"
	  hp871x_MSG_INVALID_STATUS_VALUE, (long)statusCode);
	
thisPtr->errNumber = VI_ERROR_PARAMETER2;
return VI_ERROR_PARAMETER2;
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_revision_query(
        ViSession    instrumentHandle,
        ViPString    instrumentDriverRevision,
        ViPString    firmwareRevision)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession    instrumentHandle (in)                                     */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPString    instrumentDriverRevision[] (out)                          */
/*      Instrument driver revision.  This is limited to 256 characters.      */
/*    ViPString    firmwareRevision[] (out)                                  */
/*      Instrument firmware revision.  This is limited to 256 characters.    */
/*****************************************************************************/

{
struct    hp871x_globals *thisPtr;
ViStatus  errStatus;
ViChar    temp_str1[256];         /* temp hold for instr rev string */
ViChar   *last_comma;             /* last comma in *IDN string */
	
GET_GLOBALS(instrumentHandle, thisPtr)

instrumentDriverRevision[0] = 0; 
firmwareRevision[0] = 0; 

sprintf(instrumentDriverRevision, "%s", hp871x_REV_CODE);

        /*************************************************************/
        /* In the standard c template, the scan format string is     */
        /*   "%t%*t".  This removes white space from the end of the  */
        /*   returned string, but doesn't work if there are          */
        /*   embedded spaces in the returned string.  I used this    */
        /*   format string and resorted to stripping off spaces and  */
        /*   spaces and trailing non-printing characters below.      */
        /*************************************************************/

if ((errStatus = delayVQueryf( instrumentHandle, "*IDN?\n", "%t", temp_str1))
                                                                 < VI_SUCCESS)
{
    instrumentDriverRevision[0] = 0; 
    firmwareRevision[0]  = 0; 
    return statusUpdate(instrumentHandle, thisPtr, errStatus); 
}
    
        /*************************************************************/
        /* error and exit if last comma not found                    */
        /*************************************************************/

last_comma = strrchr(temp_str1,',');

if (!last_comma) 
{
    firmwareRevision[0] = 0;
    strcpy(thisPtr->errMessage, INSTR_ERROR_NO_LAST_COMMA);
    thisPtr->errNumber = hp871x_INSTR_NO_LAST_COMMA;
    return hp871x_INSTR_NO_LAST_COMMA; 
}

        /*************************************************************/
        /* The next statement assumes that the firmware revision of  */
        /*   the instrument follows the last comma/space pair.       */
        /*************************************************************/
        /* JMH Note: eliminate the comma at the end of the line.     */
        /*************************************************************/

strcpy(firmwareRevision, last_comma+1);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS); 
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_timeOut (
        ViSession  instrumentHandle,
        ViInt32    setTimeOut)
/*****************************************************************************/
/*  Sets the current setting of the driver timeout value of the instrument   */
/*  in milliseconds.                                                         */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViInt32    setTimeOut (in)                                             */
/*      The period of time which VISA will allow an instrument command to    */
/*      wait before stopping it's execution.                                 */
/*****************************************************************************/

{
ViStatus errStatus = 0;
struct hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

CHK_LONG_RANGE(setTimeOut, hp871x_TIMEOUT_MIN,
                                     hp871x_TIMEOUT_MAX, VI_ERROR_PARAMETER2);

if ((errStatus = viSetAttribute(instrumentHandle, VI_ATTR_TMO_VALUE,
                                                    setTimeOut)) < VI_SUCCESS)
{
    thisPtr->errNumber = errStatus;
    return errStatus;
}

thisPtr->errNumber = VI_SUCCESS;
return VI_SUCCESS;
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_timeOut_Q (
        ViSession  instrumentHandle,
        ViPInt32   timeOut)
/*****************************************************************************/
/*  Returns the current setting of the timeout value of the instrument in    */
/*  milliseconds.                                                            */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32   timeOut (out)                                               */
/*      The period of time which VISA will allow an instrument command to    */
/*      wait before stopping it's execution.                                 */
/*****************************************************************************/

{
ViStatus errStatus = 0;
struct hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = viGetAttribute(instrumentHandle, VI_ATTR_TMO_VALUE,
                                                       timeOut)) < VI_SUCCESS)
{
    thisPtr->errNumber = errStatus;
    return errStatus;
}

thisPtr->errNumber = VI_SUCCESS;
return VI_SUCCESS;
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_errorQueryDetect( 
        ViSession  instrumentHandle,
        ViBoolean  setErrorQueryDetect)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViBoolean  setErrorQueryDetect (in)                                    */
/*      Enables (VI_TRUE) or disables (VI_FALSE) automatic instrument error  */
/*      querying                                                             */
/*****************************************************************************/

{
ViStatus errStatus = 0;
struct hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

CHK_BOOLEAN(setErrorQueryDetect, VI_ERROR_PARAMETER2);

thisPtr->errQueryDetect = setErrorQueryDetect;

thisPtr->errNumber = VI_SUCCESS;
return VI_SUCCESS;
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_errorQueryDetect_Q( 
        ViSession   instrumentHandle,
        ViPBoolean  errorQueryDetect)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession   instrumentHandle (in)                                      */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPBoolean  errorQueryDetect (out)                                     */
/*      Equals VI_TRUE if automatic instrument error querying is being       */
/*      being performed.                                                     */
/*****************************************************************************/

{
ViStatus errStatus = 0;
struct hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

*errorQueryDetect = thisPtr->errQueryDetect;

thisPtr->errNumber = VI_SUCCESS;
return VI_SUCCESS;
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_dcl( 
        ViSession  instrumentHandle)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession instrumentHandle (in)                                        */
/*      Instrument Handle returned from hp871x_init()                        */
/*****************************************************************************/

{
ViStatus errStatus = 0;
struct hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

if (thisPtr->interfaceType == VI_INTF_GPIB)
    if ((errStatus = viClear(instrumentHandle)) < VI_SUCCESS)
        return statusUpdate( instrumentHandle, thisPtr, errStatus);	

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

 
/*****************************************************************************/
ViStatus _VI_FUNC hp871x_opc_Q(
        ViSession   instrumentHandle,
        ViPBoolean  instrumentReady)
/*****************************************************************************/
/*  Sends an *OPC? command to the instrument and returns VI_TRUE when all    */
/*  pending operations are complete.                                         */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession   instrumentHandle (in)                                      */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViPBoolean  instrumentReady (out)                                      */
/*      Returns VI_TRUE when pending operations are complete.                */
/*****************************************************************************/

{
ViStatus errStatus;
struct hp871x_globals *thisPtr;
   
GET_GLOBALS(instrumentHandle, thisPtr)

thisPtr->dTime = 200;

if ((errStatus = delayVQueryf(instrumentHandle, "*OPC?\n", "%hd%*t",
                                               instrumentReady)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);
/*
if ((errStatus = delayVPrintf(instrumentHandle,"*OPC?\n")) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

if ((errStatus = delayVScanf(instrumentHandle, "%hd%*t",
                                               instrumentReady)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);
*/

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */ 


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_readStatusByte_Q(
        ViSession  instrumentHandle,
        ViPInt32   statusByte)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession instrumentHandle (in)                                        */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32  statusByte (out)                                             */
/*      Returns the contents of the status byte                              */
/*****************************************************************************/

{
ViStatus  errStatus = 0;
ViUInt16 stb;
struct    hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = viReadSTB(instrumentHandle, &stb)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus );
*statusByte = (ViUInt16)stb;

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_operEvent_Q(
        ViSession  instrumentHandle,
        ViPInt32   operationEventRegister)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession vi (in)                                                      */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32  operationEventRegister (out)                                 */
/*      Returns the contents of the operation event register                 */
/*****************************************************************************/

{
ViStatus  errStatus;
struct    hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle,"STAT:OPER:EVEN?\n", "%i%*t",
                                        operationEventRegister)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_operCond_Q(
        ViSession instrumentHandle,
        ViPInt32 operationConditionRegister)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession instrumentHandle (in)                                        */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32  operationConditionRegister (out)                             */
/*      Returns the contents of the operation condition register             */
/*****************************************************************************/

{
ViStatus   errStatus;
struct     hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle, "STAT:OPER:COND?\n", "%i%*t",
                                    operationConditionRegister)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_quesEvent_Q(
        ViSession instrumentHandle,
        ViPInt32  questionableEventRegister)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession instrumentHandle (in)                                        */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32  questionableEventRegister (out)                              */
/*      Returns the contents of the questionable event register              */
/*****************************************************************************/

{
ViStatus  errStatus;
struct    hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle, "STAT:QUES:EVEN?\n", "%i%*t",
                                     questionableEventRegister)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS );
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_quesCond_Q(
        ViSession instrumentHandle,
        ViPInt32  questionableConditionRegister)
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession instrumentHandle (in)                                        */
/*      Instrument Handle returned from hp871x_init()                        */
/*    ViPInt32  questionableConditionRegister (out)                          */
/*      Returns the contents of the questionable condition register          */
/*****************************************************************************/
 
{
ViStatus  errStatus;
struct    hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)
 
if ((errStatus = delayVQueryf(instrumentHandle, "STAT:QUES:COND?\n", "%i%*t",
                                 questionableConditionRegister)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmd( 
        ViSession instrumentHandle,
        ViString  sendStringCommand)
/*****************************************************************************/
/*  Send a scpi command, it does not look for a response                     */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession     instrumentHandle (in)                                    */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString      sendStringCommand (in)                                   */
/*      The SCPI command string to be sent to the instrument                 */
/*****************************************************************************/

{
ViStatus errStatus;
struct   hp871x_globals *thisPtr;

GET_GLOBALS(instrumentHandle, thisPtr)

errStatus = delayVPrintf(instrumentHandle,"%s\n", sendStringCommand);
   
return statusUpdate(instrumentHandle, thisPtr, errStatus);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmdString_Q(
        ViSession       instrumentHandle,
        ViString        queryStringCommand,
        ViInt32         stringSize,
        ViChar _VI_FAR  stringResult[] )
/*****************************************************************************/
/*  PARAMETERS                                                               */
/*    ViSession       instrumentHandle (in)                                  */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString        queryStringCommand (in)                                */
/*      The SCPI command string to be sent to the instrument                 */
/*    ViInt32         stringSize (in)                                        */
/*      The size of the char array (result) passed to the function to hold   */
/*      the string returned by the instrument                                */
/*    ViChar _VI_FAR  stringResult[] (out)                                   */
/*      The string returned by the instrument                                */
/*****************************************************************************/

{
ViStatus  errStatus;
struct    hp871x_globals *thisPtr;
int       sz;

GET_GLOBALS(instrumentHandle, thisPtr)

        /* Command strings must have at least one non-null character */
if(stringSize < 2)
   {
    thisPtr->errNumber = VI_ERROR_PARAMETER2;
    return VI_ERROR_PARAMETER2;
   }

sz = (int)stringSize;
if ((errStatus = delayVQueryf(instrumentHandle, "%s\n", "%#t",
                         queryStringCommand, &sz, stringResult)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);
stringResult[sz]='\0';
      
return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */ 


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmdInt(
        ViSession  instrumentHandle,
        ViString   sendIntegerCommand,
        ViInt32    sendInteger )
/*****************************************************************************/
/*  Sends an instrument command which takes a single integer parameter.      */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString   sendIntegerCommand (in)                                     */
/*      The instrument command string to be sent to the instrument.          */
/*    ViPInt32   sendInteger (in)                                            */
/*      The integer sent to the instrument at the end of the instrument      */
/*      command.  Can be ViInt16 or ViInt32.                                 */
/*****************************************************************************/

{  
ViStatus errStatus;
struct hp871x_globals *thisPtr;
   
GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVPrintf(instrumentHandle, "%s %ld\n", sendIntegerCommand,
                                                   sendInteger)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */ 


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmdInt16_Q(
        ViSession  instrumentHandle,
        ViString   queryI16Command,
        ViPInt16   i16Result)
/*****************************************************************************/
/*  Sends scpi command and waits for a response that must be representable   */
/*    as an int16.  A non numeric instrument response returns zero in        */
/*    result.                                                                */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString   queryI16Command (in)                                        */
/*      The SCPI command string to be sent to the instrument.                */
/*    ViPInt16   i16Result (out)                                             */
/*      The integer returned from the instrument.                            */
/*****************************************************************************/

{
ViStatus errStatus;
struct   hp871x_globals *thisPtr;
   
GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle, "%s\n", "%hd%*t",
                                    queryI16Command, i16Result)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */ 


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmdInt32_Q(
        ViSession instrumentHandle,
        ViString  queryI32Command,
        ViPInt32  i32Result)
/*****************************************************************************/
/*  Sends scpi command and waits for a response that must be representable   */
/*    as an int32.  A non numeric instrument response returns zero in        */
/*    result.                                                                */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString   queryI32Command (in)                                        */
/*      The SCPI command string to be sent to the instrument.                */
/*    ViPInt32   i32Result (out)                                             */
/*      The integer returned from the instrument.                            */
/*****************************************************************************/

{  
ViStatus  errStatus;
struct    hp871x_globals *thisPtr;
   
GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle, "%s\n", "%ld%*t",
                                    queryI32Command, i32Result)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);
        
return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */ 

	
/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmdReal(
        ViSession  instrumentHandle,
        ViString   sendRealCommand,
        ViReal64   sendReal )
/*****************************************************************************/
/*  Sends an instrument command which takes a single real parameter.         */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString   sendRealCommand (in)                                        */
/*      The instrument command string to be sent to the instrument.          */
/*    ViReal64   sendReal (in)                                               */
/*      The real number sent to the instrument at the end of the instrument  */
/*      command.  Can be ViReal32 or ViReal64.                               */
/*****************************************************************************/

{
ViStatus errStatus;
struct   hp871x_globals *thisPtr;
   
GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVPrintf(instrumentHandle, "%s %g\n", sendRealCommand,
                                                     sendReal )) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
ViStatus _VI_FUNC hp871x_cmdReal64_Q(
    ViSession  instrumentHandle,
    ViString   queryRealCommand,
    ViPReal64  realResult)
/*****************************************************************************/
/*  Sends scpi command and waits for a response that must be representable   */
/*    as an real64.  A non numeric instrument response returns zero in       */
/*    result, in case of underflow undefined.                                */
/*                                                                           */
/*  PARAMETERS                                                               */
/*    ViSession  instrumentHandle (in)                                       */
/*      Instrument handle returned from hp871x_init()                        */
/*    ViString   queryRealCommand (in)                                       */
/*      The SCPI command string to be sent to the instrument.                */
/*    ViPReal64  realResult (out)                                            */
/*      The real returned from the instrument.                               */
/*****************************************************************************/

{   
ViStatus  errStatus;
struct    hp871x_globals *thisPtr;
   
GET_GLOBALS(instrumentHandle, thisPtr)

if ((errStatus = delayVQueryf(instrumentHandle, "%s\n", "%lg%*t",
                                  queryRealCommand, realResult)) < VI_SUCCESS)
    return statusUpdate(instrumentHandle, thisPtr, errStatus);

return statusUpdate(instrumentHandle, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */ 


                                                                        
/*************************************************************************
 ****************** start of instr specific functions ********************
 *************************************************************************/

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_preset
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE :  This will preset the analyzer and wait for completion of preset.
 *            Default is a normal preset.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  (OPTIONAL; Not allowed on 8711A & 871xB!)
 * IN        If this parameter is not used, a normal preset is performed.  If 
 *			 preset type = "factory" (case insensitive) then a preset is performed
 *           and the power level and preset power level are both set to 0 dBm.
 *           
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *           
 * LIMITATIONS: "FACTORY" preset not allowed on 8711A and 871xB.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_preset( 
        ViSession vi, 
		ViString request)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
GET_GLOBALS(vi, thisPtr)
ViInt32 choice;
strcpy(thisPtr->funcName, "hp871x_preset");

const ViInt32 size = 2;
ViString req[size]= {"FACTORY", "DEFAULT"
					};


if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if ((errStatus = hp871x_outputf(vi, 2, "SYST:PRES")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);

if (choice==0) //Factory preset; 871xC and later only
	{
	if ((errStatus = hp871x_outputf(vi, 1, "SOUR:POW:PRES 0")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = hp871x_outputf(vi, 2, "SOUR1:POW 0")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = hp871x_outputf(vi, 2, "SENS2:CORR:CSET:SEL DEF")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	errStatus = hp871x_outputf(vi, 2, "SENS1:CORR:CSET:SEL DEF");
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
} /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_power
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE :  Sets or returns current power level (in dBm ONLY!)  
 *			  Sets or returns current preset power level (in dBm ONLY!) 
 *            Also allows user to turn on/off/query RF power status
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViReal64 power.  
 * IN        Contains the power level in dBm to be set.  
 *
 * PARAM 3 : ViString request (OPTIONAL, default="LEVEL"). Other choices   
 * IN        are shown below. 
 *			 
 * PARAM 4 : ViInt32 channel. (OPTIONAL, default=1). Usually not needed.
 * IN        Indicates channel number (1 or 2)   
 *
 * PARAM 5 : ViInt32 cur_power. (OPTIONAL)   Contains queried power
 * OUT       level or RF status (1=ON 0=OFF)    
 *           
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: "PRESET"  power level not allowed on 8711A and 871xB.
 * 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_power( 
        ViSession vi, 
		ViReal64 power,
		ViString request,
		ViInt32 channel,
		ViPReal64 cur_power)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
ViInt32 choice;
strcpy(thisPtr->funcName, "hp871x_power");

const ViInt32 size = 13;
ViString req[size]= {"?", "LEVEL?", "LVL?", "LVL", "LEVEL", "PRESET", "PRESET?",
					 "RF_ON", "ON", "RF_OFF", "OFF", "RF?", "STATUS?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

 switch (choice)
{
	case 0: case 1: case 2://Read Power Level
		if ((errStatus = viPrintf(vi, "SOUR%i:POW?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_power);
		break;
	case 3: case 4: //Set Power Level
		errStatus = viPrintf(vi, "SOUR%i:POW %lf;*WAI\n",channel,power);
		Sleep(10);
 		break;
	case 5: //Set Preset power Level
		errStatus = viPrintf(vi, "SOUR:POW:PRES %lf;*WAI\n",power);
		break;
	case 6: //Read Preset Power Level
		if ((errStatus = viPrintf(vi, "SOUR:POW:PRES?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_power);
		break;
	case 7: case 8://Set RF ON
		errStatus = viPrintf(vi, "OUTP:STAT ON;*WAI\n");
		break;
	case 9: case 10://Set RF OFF
		errStatus = viPrintf(vi, "OUTP:STAT OFF;*WAI\n");
		break;
	case 11: case 12: //Read RF ON/OFF status
		if ((errStatus = viPrintf(vi, "OUTP:STAT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_power);
		break;

}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_frequency
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE :  Sets or returns current start/stop or CW/dF frequencies   
 *            If dF is 0 then sets analyzer to CW.  All freqs in Hz only!
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViReal64 freq1. 
 * IN        Contains the Start or CW freq to be set.  
 *
 * PARAM 3 : ViReal64 freq2.  
 * IN        Contains the Stop or dF freq to be set.  
 *
 * PARAM 4 : ViString request. (OPTIONAL, default="S/S" "start/stop"). Other choice   
 * IN        is CW.   "?" indicates query. 
 *			 
 * PARAM 5 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 * PARAM 6 : ViReal64 cur_freq1. (OPTIONAL)
 * OUT       Contains the current Start or CW freq.  
 *
 * PARAM 7 : ViReal64 cur_freq2.  (OPTIONAL)
 * OUT       Contains the current Stop or dF freq.  
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 * 
 *---------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_frequency( 
        ViSession vi, 
		ViReal64 freq1,
		ViReal64 freq2,
		ViString request,
		ViInt32 channel,
		ViPReal64 cur_freq1,
		ViPReal64 cur_freq2)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_frequency");

ViInt32 choice;
const ViInt32 size = 8;
ViString req[size]= {"S/S", "START/STOP", "START_STOP", "S/S?", "START/STOP?",
					 "START_STOP?","CW", "CW?" 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

 switch (choice)
{
	case 0: case 1: case 2://Set Start/Stop
	   	if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE SSTOP;:SENS%i:FREQ:STAR %lf;*WAI\n",channel,channel,freq1)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = viPrintf(vi, "SENS%i:FREQ:STOP %lf;*WAI\n",channel,freq2)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 3: case 4: case 5: //Read Start/Stop frequencies
   		if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE SSTOP;:SENS%i:FREQ:STAR?\n",channel,channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_freq1)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = viPrintf(vi, "SENS%i:FREQ:STOP?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_freq2)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 6: //Set CW/dF frequencies
		if (freq2 == 0)
		{
			if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE CW;:SENS%i:FREQ:SPAN 0;*WAI\n",channel,channel)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
			if ((errStatus = viPrintf(vi, "SENS%i:FREQ:CENT %lf;*WAI\n",channel,freq1)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
		else
		{
   			if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE CSPAN;:SENS%i:FREQ:CENT %lf;*WAI\n",channel,channel,freq1)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
			if ((errStatus = viPrintf(vi, "SENS%i:FREQ:SPAN %lf;*WAI\n",channel,freq2)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
		break;
	case 7: //Read CW/dF frequencies
	   	if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE CSPAN;:SENS%i:FREQ:CENT?\n",channel,channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_freq1)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = viPrintf(vi, "SENS%i:FREQ:SPAN?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_freq2)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
}
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_points
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns current # of points  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViPInt32 points.  
 * IN        Number of points to be set    
 *
 * PARAM 3 : ViString request. (OPTIONAL, default="SET"). 
 * IN        Other choice is "?" or "POINTS?"
 *
 * PARAM 4 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *
 * PARAM 5 : ViPInt32 cur_points. (OPTIONAL) 
 * OUT       Indicates current number of points used 
 *
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: <101 points not supported on early 8711A firmware revisions.
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_points( 
        ViSession vi, 
		ViInt32 points,
		ViString request,
		ViInt32 channel,
		ViPInt32 cur_points)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_points");
ViInt32 choice;

const ViInt32 size = 3;
ViString req[size]= {"?", "POINTS?", "SET"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);


switch (choice)
{	case 0: case 1://Query
   		if ((errStatus = viPrintf(vi, "SENS%i:SWE:POIN?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%i\n", cur_points)) < VI_SUCCESS)
			 return statusUpdate(vi, thisPtr, errStatus);
		break;

	case 2://Set # of Points
		if ((errStatus = viPrintf(vi, "SENS%i:SWE:POIN %i;*WAI\n",channel,points)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
}
	
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_average
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns current averaging factor or status (ON/OFF) or
 *           restarts averaging.  Setting any nonzero avg factor turns averaging 
 *           on.  Setting avg factor of 0 turns averaging off.  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViInt32 avg_set.
 * IN        Averaging Factor to be set (or ON/OFF indicator: 0=OFF, 1=ON)
 *
 * PARAM 3 : ViString request. (OPTIONAL, default="FACTOR"). Other choice is
 * IN   	 RESTART.  Averaging "FACTOR?" and "STATUS?" (ON/OFF) can be queried.
 *
 * PARAM 4 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *
 * PARAM 5 : ViPInt32 cur_value. (OPTIONAL) 
 * OUT       Indicates current avg factor (or ON/OFF status 0=OFF, 1=ON)  
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_average( 
        ViSession vi, 
		ViInt32 avg_set,
		ViString request,
		ViInt32 channel,
		ViPInt32 cur_avg)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_average");

ViInt32 choice;
const ViInt32 size = 5;
ViString req[size]= {"FACTOR", "RESTART", "?", "FACTOR?", "STATUS?" 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

if ((errStatus = viFlush(vi,VI_READ_BUF_DISCARD)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

switch (choice)
{
	case 0: //Set Averaging or turn off
	   	if (avg_set == 0) 
		{
			if ((errStatus = viPrintf(vi, "SENS%i:AVER OFF;*WAI\n",channel)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
		else
		{
   			if ((errStatus = viPrintf(vi, "SENS%i:AVER:COUN %i;*WAI\n",channel,avg_set)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
			if ((errStatus = viPrintf(vi, "SENS%i:AVER ON;*WAI\n",channel)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
		break;
	case 1://Restart averaging
		if ((errStatus = viPrintf(vi, "SENS%i:AVER:CLE;*WAI\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 2: case 3:
		if ((errStatus = viPrintf(vi, "SENS%i:AVER:COUN?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%i\n", cur_avg)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 4:
		if ((errStatus = viPrintf(vi, "SENS%i:AVER?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%i\n", cur_avg)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
}
   
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_trigger
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets sweep trigger mode 
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString request.  Sets trigger mode. Choices are SINGLE
 *			 CONTINUOUS, HOLD, IMMEDIATE.  Mode can also be queried.
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *			 
 * PARAM 4 : ViPInt32 trig_status. (OPTIONAL) 
 * OUT       Indicates if trigger continuous is active (0=NO; 1=Yes)  
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_trigger( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPInt32 trig_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_trigger");
const ViInt32 size = 8;
ViInt32 trig;
ViString req[size]= {"SINGLE", "HOLD", "CONT", "CONTINUOUS", "IMM", "IMMEDIATE", 
					 "?", "STATUS?" 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

if ((errStatus = viFlush(vi,VI_READ_BUF_DISCARD)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

switch (choice)
{
	case 0: //Single
		if ((errStatus = hp871x_checkChanStatus(vi,channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	    errStatus = hp871x_outputf(vi, 3, "ABOR;:INIT%i:CONT OFF;:INIT%i",channel,channel);
		break;
	case 1: //Hold
		errStatus = viPrintf(vi, "ABOR;:INIT%i:CONT OFF;*WAI\n",channel);
		break;
	case 2: case 3: //CONT
		errStatus = viPrintf(vi, "ABOR;:INIT%i:CONT ON;*WAI\n",channel);
		break;
	case 4: case 5: //IMMEDIATE
		if ((errStatus = hp871x_checkChanStatus(vi,channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);		
		//First, see if in hold mode
		if ((errStatus = viPrintf(vi, ":INIT%i:CONT?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%i\n", &trig)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if (trig) //if in continuous mode, place in hold mode
			if ((errStatus = viPrintf(vi, "ABOR;:INIT%i:CONT OFF;*WAI\n",channel)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
	    errStatus = hp871x_outputf(vi, 3, ":INIT%i",channel);
		break;
	case 6: case 7: //Status?
	   	if ((errStatus = viPrintf(vi, ":INIT%i:CONT?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", trig_status);
		break;
}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_measure
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or Reads current measurement type
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString request. Contains requested measurement type or "?" 
 * IN		 if query.
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *			 
 * PARAM 4 : ViPString cur_meas. Contains current measurement type
 * OUT
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Some choices are option dependent (e.g. "FAULT" requires Opt 100).
 * 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_measure( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPString cur_meas)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

ViInt32 choice=0;
ViInt32 index=0;
char code[100],det_mode[15];
char *token;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_measure");
char selection[40];
const ViInt32 size = 32;
ViString req[size]={det_mode};  //reserve 15 char space

ViString meas[size][2]= {"A" ,  "XFR:POW 1';DET NBAN",
						 "B" ,  "XFR:POW 2';DET NBAN",
						 "R" ,  "XFR:POW 0';DET NBAN",
						"A/R" , "XFR:POW:RAT 1, 0';DET NBAN",
						"B/R" , "XFR:POW:RAT 2, 0';DET NBAN", 
						 "B*" , "XFR:POW 2';DET BBAN",
						 "R*" , "XFR:POW 0';DET BBAN",
					  "B*/R*" , "XFR:POW:RAT 2, 0';DET BBAN",
						 "X" ,  "XFR:POW 11';DET BBAN",
						 "Y" ,  "XFR:POW 12';DET BBAN",
					    "X/Y" , "XFR:POW:RAT 11, 12';DET BBAN",
						"Y/X" , "XFR:POW:RAT 12, 11';DET BBAN", 
						"Y/R*", "XFR:POW:RAT 12, 0';DET BBAN", 
						 "AUX", "XFR:VOLT';DET NBAN",
					  "FAULT" , "FLOC 1, 0';DET NBAN",
					    "SRL" , "SRL 1, 0';DET NBAN",
					"AM_DELAY", "XFR:GDEL:RAT 12, 11';DET BBAN",
						"S11",  "XFR:POW:RAT 1, 0';DET NBAN", // same as "XFR:S 1,1';DET NBAN"
						"S11",  "XFR:S 1,1';DET NBAN", // needed for reading of meas selection
						"S12",  "XFR:S 1,2';DET NBAN",
						"S21",  "XFR:POW:RAT 2, 0';DET NBAN", // same as "XFR:S 2,1';DET NBAN"
						"S21",	"XFR:S 2,1';DET NBAN", // needed for reading of meas selection
						"S22",  "XFR:S 2,2';DET NBAN",
				  "FAULT_REV",  "FLOC 21, 20';DET NBAN",
					"SRL_REV",  "SRL 21, 20';DET NBAN",
					  "A_REV" , "XFR:POW 21';DET NBAN",
					  "B_REV" , "XFR:POW 22';DET NBAN",
					  "R_REV" , "XFR:POW 20';DET NBAN",
				"TRANSMISSION", "XFR:POW:RAT 2, 0';DET NBAN", 
					   "TRANS", "XFR:POW:RAT 2, 0';DET NBAN",
				  "REFLECTION", "XFR:POW:RAT 1, 0';DET NBAN",
				        "REFL", "XFR:POW:RAT 1, 0';DET NBAN",
};


if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);
strip(request,selection);

if (strcmpi(selection, "?")) //  NOT a query!, Set Meas type
{ 
	for (index=0;  index<size; index++) //Copy to single dimensions array
		 req[index]= meas[index][0];
	if(getChoice(vi,request,size,req,&choice)) 
		return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
	if ((errStatus = hp871x_outputf(vi, 2, "SENS%i:FUNC '%s", channel, meas[choice][1])) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
}
else  //Read Meas Type
{
	if ((errStatus = viPrintf(vi, "SENS%i:FUNC?\n",channel)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = delayVScanf(vi, "%t\n", code)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	token = strtok(code, "\"");
	if ((errStatus = viPrintf(vi, "SENS%i:DET?\n",channel)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = delayVScanf(vi, "%s\n", det_mode)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	strcat(token, "';DET ");
	strcat(token, det_mode);
	
	while (strcmp(token, meas[choice][1]))
	{
		choice++;
		if (choice==size)
			return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR );
	}
	strcpy(cur_meas, meas[choice][0]);
}
  return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_channel
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Turn channel on/off or reads channel status  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViInt32 channel.  
 * IN        Channel number (1 or 2)    
 *
 * PARAM 3 : ViString request. (OPTIONAL, default="ON"). 
 * IN		 Other choices are "OFF", "ACTIVE?" or "STATUS?"
 *
 * PARAM 4 : ViPInt32 chan_status. Contains chan status info:  0=Off; 1=On
 * OUT
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: The active channel can only be determined on the 871xE.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_channel( 
        ViSession vi, 
		ViInt32 channel,
		ViString request,
		ViPInt32 chan_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_channel");

ViInt32 choice;

const ViInt32 size = 5;
ViString req[size]= {"OFF", "ON", "?", "STATUS?" ,"ACTIVE?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
{
	case 0: // Off
		errStatus = viPrintf(vi, "SENS%i:STAT OFF;*WAI\n",channel);
		break;
	case 1: // On
		errStatus = viPrintf(vi, "SENS%i:STAT ON;*WAI\n",channel);
		break;
	case 2: case 3://  Status?
	   	if ((errStatus = viPrintf(vi, "SENS%i:STAT?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", chan_status);
		break;
	case 4: // Active?
	   	if ((errStatus = viPrintf(vi, "SENS%i:ACT?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", chan_status);
		break;
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_bandwidth
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE :  Sets or returns current bandwidth  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViReal64 bandwidth. 
 * IN        Contains the bandwidth in Hz.  
 *            
 * PARAM 2 : ViString request. (OPTIONAL, default = "SET"  Other choice is "?".  
 * IN        
 *			 
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 * PARAM 4 : ViReal64 cur_bw. (OPTIONAL) 
 * OUT       Contains queried bandwidth in Hz   
 *           
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *           
 * LIMITATIONS: Some BW values are not valid on some revisions.  No error
 *              is reported, closest valid BW will be used by analyzer.
 * 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_bandwidth( 
        ViSession vi, 
		ViReal64 bandwidth,
		ViString request,
		ViInt32 channel,
		ViPReal64 cur_bw)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_bandwidth");
ViInt32 choice;

const ViInt32 size = 2;
ViString req[size]= { "SET", "?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

if ((errStatus = viFlush(vi,VI_READ_BUF_DISCARD)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

switch (choice)
{	case 0://Set Bandwidth
		if ((errStatus = viPrintf(vi, "SENS%i:BWID %lf;*WAI\n",channel,bandwidth)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 1://Query
   		if ((errStatus = viPrintf(vi, "SENS%i:BWID?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_bw)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
}
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_scale
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns current Scale Factor, Position, Ref Level, Elec Delay, 
 *			 or Phase Offset. If scale factor is 0, then an Autoscale is done  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViReal64 value.
 * IN        Scale/posn/ref/delay/phase value to set
 *
 * PARAM 3 : ViString request. (OPTIONAL, default="SCALE"). Other choices 
 * IN		 are shown below.  All except AUTOSCALE can be queried (?)
 *
 * PARAM 4 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *
 * PARAM 5 : ViPReal64 cur_value. (OPTIONAL) 
 * OUT       Indicates current value used  
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Phase and Delay require phase capable analyzer model.
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_scale( 
        ViSession vi, 
		ViReal64 value,
		ViString request,
		ViInt32 channel,
		ViPReal64 cur_value)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_scale");

ViInt32 choice;
const ViInt32 size = 19;
ViString req[size]= {"SCALE", "POSN", "POSITION", "REF", "REFERENCE", "AUTO", 
					 "AUTOSCALE", "?", "SCALE?", "POSN?", "POSITION?", "REF?", 
					 "REFERENCE?" ,"DELAY", "DELAY?", "PHASE", "PHASE_OFFSET",
					 "PHASE?", "PHASE_OFFSET?"
				 	};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

 switch (choice)
{
	case 0: //Set Scale value
		if (value == 0) 
			errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:AUTO ONCE;*WAI\n",channel);
		else 
   			errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:PDIV %lf;*WAI\n",channel,value);
		break;
	case 1: case 2: //Set Position (must be from 0 to 10)
		errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:RPOS %lf;*WAI\n",channel,value);
		break;
	case 3: case 4: //Set Reference Level
		errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:RLEV %lf;*WAI\n",channel,value);
		break;
	case 5: case 6: //AutoScale
		errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:AUTO ONCE;*WAI\n",channel);
		break;

	case 7: case 8: //Read Scale value
		if ((errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:PDIV?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_value);
		break;
	case 9: case 10: //Read Position
	   	if ((errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:RPOS?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_value);
		break;
	case 11: case 12: //Read Ref Level
   		if ((errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:RLEV?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_value);
		break;
	case 13: //Elec Delay	
		errStatus = viPrintf(vi, "SENS%i:CORR:EDEL:TIME %.12lf;*WAI\n",channel,value);
		break;
 	case 14: //Read Elec Delay
   		if ((errStatus = viPrintf(vi, "SENS%i:CORR:EDEL:TIME?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_value);
		break;
	case 15: case 16: //Set Phase Offset
		errStatus = viPrintf(vi, "SENS%i:CORR:OFFS:PHASE %lf;*WAI\n",channel,value);
		break;
	case 17: case 18: //Read Phase Offset
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:OFFS:PHASE?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_value);
		break;
}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_format
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or reads measurement display format.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString request.  Contains requested format type or "?" query.
 * IN
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *			 
 * PARAM 4 : ViPString cur_format. (OPTIONAL) Contains current format type.
 * OUT
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Phase and Delay require phase capable analyzer model.
 *           
 *-----------------------------------------------------------------------------
 */
 ViStatus _VI_FUNC hp871x_format( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPString cur_format)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_format");

ViInt32 choice=0;
ViInt32 index;
char code[50];
char dummy[15];
const ViInt32 size = 13;
ViString req[size]={dummy};  //reserve 15 char space
char selection[40];

ViString meas[size][2]= {"LOG" , "MLOG",
						 "LIN" , "MLIN",
						 "SWR" , "SWR",
					   "DELAY" , "GDEL",
					   "PHASE" , "PHAS", 
					   "SMITH" , "SMIT",
					   "POLAR" , "POL",
					    "REAL" , "REAL",
						"IMAG" , "IMAG",
				   "IMPEDANCE" , "MIMP",
					  "LINEAR" , "MLIN",
					    "VSWR" , "SWR",
						 "IMP" , "MIMP",
};

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);
strip(request,selection);
if (strcmpi(selection, "?")) //  NOT a query!, Set format type
{ 
	for (index=0;  index<size; index++) // Copy to single dimension array
		 req[index]= meas[index][0];
	if(getChoice(vi,request,size,req,&choice)) 
		return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

	if ((errStatus = hp871x_outputf(vi, 2, "CALC%i:FORM %s", channel, meas[choice][1])) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);

}
else //Read Format Type
{
	if ((errStatus = viPrintf(vi, "CALC%i:FORM?\n",channel)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = delayVScanf(vi, "%s\n", code)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);

	while (strcmp(code, meas[choice][1]))
	{
		choice++;
		if (choice==size)
			return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR);
	}
	strcpy(cur_format, meas[choice][0]);
}
  return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_sweepTime
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns current sweep time or sweep time mode (AUTO/MANUAL).  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViReal64 swptime.
 * IN        Sweep time to set. Setting a nonzero sweep time sets analyzer to 
 *           manual mode.  Setting sweep time to 0 will activate auto mode.  
 *
 * PARAM 3 : ViString request. (OPTIONAL, default="SET"). Other choices are
 * IN   	 ? or AUTO or AUTO?. 
 *
 * PARAM 4 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *
 * PARAM 5 : ViPReal64 cur_sweep. (OPTIONAL) 
 * OUT       Indicates current sweep time or sweep time mode (AUTO=1, MANUAL=0). 
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_sweepTime( 
        ViSession vi, 
		ViReal64 swptime,
		ViString request,
		ViInt32 channel,
		ViPReal64 cur_sweep)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_sweepTime");

ViInt32 choice;
const ViInt32 size = 10;
ViString req[size]= {"SET", "TIME", "SWEEPTIME", "AUTO", "MAN", "MANUAL", "?", "TIME?", 
					 "SWEEPTIME?", "AUTO?" 
				 	};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	case 0: case 1: case 2: //Set Sweep time
		if (swptime == 0) 
				errStatus = viPrintf(vi, "SENS%i:SWE:TIME:AUTO ON;*WAI\n",channel);
		else
   			errStatus = viPrintf(vi, "SENS%i:SWE:TIME %lf;*WAI\n",channel,swptime);
		break;
	case 3://Set Auto sweep mode on
		errStatus = viPrintf(vi, "SENS%i:SWE:TIME:AUTO ON;*WAI\n",channel);
		break;
	case 4: case 5://Set Auto sweep mode off
		errStatus = viPrintf(vi, "SENS%i:SWE:TIME:AUTO OFF;*WAI\n",channel);
		break;
	case 6: case 7: case 8: //Read Sweep time
	   	if ((errStatus = viPrintf(vi, "SENS%i:SWE:TIME?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_sweep);
		break;
	case 9://Read Sweep time mode
	   	if ((errStatus = viPrintf(vi, "SENS%i:SWE:TIME:AUTO?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_sweep);
		break;
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_sweepAlt
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns alternate sweep status (ON/OFF).  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. Must be ON, OFF, or ?
 *
 * PARAM 3 : ViPInt32 swpAlt_status.  OPTIONAL  
 * OUT       Returns 1 for Alt Sweep ON, 0 for OFF    
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_sweepAlt( 
        ViSession vi, 
		ViString request,
		ViPInt32 swpAlt_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
char stat[20];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_sweepAlt");

ViInt32 choice;

const ViInt32 size = 3;
ViString req[size]= {"ON", "OFF", "?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if ((errStatus = viFlush(vi,VI_READ_BUF_DISCARD)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

switch (choice)
	{
	case 0:
	   errStatus = viPrintf(vi, "SENS:COUP NONE;*WAI\n");
	   break;
	case 1: //Off
		errStatus = viPrintf(vi, "SENS:COUP ALL;*WAI\n");
		break;
	case 2: //?
		if ((errStatus = viPrintf(vi, "SENS:COUP?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", stat);
		*swpAlt_status =abs(strcmpi(stat, "ALL"));
		break;
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_powerSweep
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns power sweep ON/OFF status, start/stop levels or 
 *           power range.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. Valid choices are ON, OFF, S/S, RANGE, STATUS.
 * IN   	 All except ON/OFF can be queried. 
 *
 * PARAM 3 : ViReal64 pwrSwp_val1.  OPTIONAL, default=0
 * IN        Start Value to be set
 *
 * PARAM 4 : ViReal64 pwrSwp_val2. OPTIONAL, default=0
 * IN        Stop Value to be set
 *
 * PARAM 5 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *
 * PARAM 6 : ViPInt32 cur_pwrSwp1. (OPTIONAL) 
 * OUT       When request is a query, returns current power sweep
 *           status (1=ON, 0=OFF), power range, or Start power
 *           level. 
 *
 * PARAM 7 : ViPInt32 cur_pwrSwp2. (OPTIONAL) 
 * OUT       When request is a query, returns Stop power level.  
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_powerSweep( 
        ViSession vi, 
		ViString request,
		ViReal64 pwrSwp_val1,
		ViReal64 pwrSwp_val2,
		ViInt32 channel,
		ViPReal64 cur_pwrSwp1,
		ViPReal64 cur_pwrSwp2)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
char range[20];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_powerSweep");

ViInt32 choice;
const ViInt32 size = 10;
ViString req[size]= {"ON", "OFF", "S/S", "START/STOP", "RANGE", "?", "STATUS?", 
					 "S/S?", "START/STOP?", "RANGE?" 
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	case 0: //Set power sweep on
		errStatus = viPrintf(vi, "POW%i:MODE SWEEP;*WAI\n", channel);
		break;
	case 1:  //Set power sweep off
		errStatus = viPrintf(vi, "POW%i:MODE FIXED;*WAI\n", channel);
		break;
	case 2: case 3://Set Power Sweep Start/Stop
		if ((errStatus = viPrintf(vi, "SOUR%i:POW:STAR %lf;*WAI\n",channel, pwrSwp_val1)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = viPrintf(vi, "SOUR%i:POW:STOP %lf;*WAI\n",channel, pwrSwp_val2);
		break;
	case 4: //Set Power Sweep Range
		sprintf(range, "ATT%.0lf",pwrSwp_val1);
		errStatus = viPrintf(vi, "SOUR%i:POW:RANG %s;*WAI\n",channel, range);
		break;
	case 5: case 6://Read Power Sweep Status
		if ((errStatus = viPrintf(vi, "POW%i:MODE?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_pwrSwp1);
		break;
	case 7: //Read Power Start/Stop
		if ((errStatus = viPrintf(vi, "SOUR%i:POW:STAR?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_pwrSwp1)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = viPrintf(vi, "SOUR%i:POW:STOP?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_pwrSwp2);
		break;
	case 8://Read Power Stop Value
		if ((errStatus = viPrintf(vi, "SOUR%i:POW:STOP?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_pwrSwp1);
		break;
	case 9: //Read Power Range Value
		if ((errStatus = viPrintf(vi, "SOUR%i:POW:RANGE?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", range);
		*cur_pwrSwp1= atof(strtok(range, "ATT"));
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_markerSet
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE :  Sets active marker   
 *            
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. (OPTIONAL, default="ON"). Other choices are   
 * IN        SET, MIN, MAX, OFF, POINT, MINLEFT, etc. (see code below). 
 *
 * PARAM 3 : ViInt32 marker. (OPTIONAL, default = 1)
 * IN        Contains the marker number  (1-8)  
 *
 * PARAM 4 : ViReal64 mkr_val. (OPTIONAL) Contains the frequency (or point value,  
 * IN        target, or power value if in power sweep) to be set.
 *
 * PARAM 5 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 * 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_markerSet( 
        ViSession vi, 
		ViString request,
		ViInt32 marker,
		ViReal64 mkr_val,
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_markerSet");

ViInt32 choice;
char selection[40];
const ViInt32 size = 28;
ViString req[size]= {"ON","OFF", "SET", "FREQ", "FREQUENCY", "POINT", "MIN", "MINIMUM", 
					 "MAX", "MAXIMUM", "MINLEFT", "MINRIGHT","MAXLEFT", "MAXRIGHT", 
					 "ALL_OFF", "BANDWIDTH", "DELTA_ON", "DELTA_OFF", "STATISTICS", 
					 "FLATNESS", "FST", "TO_CENTER", "TO_REF", "TO_REFERENCE", 
					 "TO_DELAY", "SET_ABS", "TRACK_ON", "TRACK_OFF"
};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);
strip(request, selection);


switch (choice)
	{
	case 0: //ON 
		errStatus = viPrintf(vi, "CALC%i:MARK%i:STAT ON;*WAI\n",channel,marker);
		break;
	case 1: //OFF
		errStatus = viPrintf(vi, "CALC%i:MARK%i:STAT OFF;*WAI\n",channel,marker);
		break;
	case 2: case 3: case 4: //SET	
	  	errStatus = viPrintf(vi, "CALC%i:MARK%i:X %lf;*WAI\n",channel,marker,mkr_val);
		break;
	case 5: //POINT
	  	errStatus = viPrintf(vi, "CALC%i:MARK%i:POIN %lf;*WAI\n",channel,marker,mkr_val);
		break;
	case 6:  case 7: //MIN
	  	errStatus = viPrintf(vi, "CALC%i:MARK%i:MIN;*WAI\n",channel,marker);
		break;
	case 8: case 9: //MAX
	   	errStatus = viPrintf(vi, "CALC%i:MARK%i:MAX;*WAI\n",channel,marker);
		break;
	case 10: //MINLEFT
		errStatus = viPrintf(vi, "CALC%i:MARK%i:MIN:LEFT;*WAI\n",channel,marker);
		break;
	case 11: //MINRIGHT
		errStatus = viPrintf(vi, "CALC%i:MARK%i:MIN:RIGH;*WAI\n",channel,marker);
		break;
	case 12: //MAXLEFT
		errStatus = viPrintf(vi, "CALC%i:MARK%i:MAX:LEFT;*WAI\n",channel,marker);
		break;
	case 13: //MAXRIGHT
		errStatus = viPrintf(vi, "CALC%i:MARK%i:MAX:RIGH;*WAI\n",channel,marker);
		break;
	case 14: //ALL OFF
		errStatus = viPrintf(vi, "CALC%i:MARK:AOFF;*WAI\n",channel);
		break;
	case 15: //BANDWIDTH
		errStatus = viPrintf(vi, "CALC%i:MARK:BWID %lf;*WAI\n",channel, mkr_val);
		break;
	case 16: //DELTA ON
		errStatus = viPrintf(vi, "CALC%i:MARK:MODE REL;*WAI\n",channel);
		break;
	case 17: //DELTA OFF
		errStatus = viPrintf(vi, "CALC%i:MARK:MODE ABS;*WAI\n",channel);
		break;
	case 18: case 19: case 20:// Math Functions
		errStatus = viPrintf(vi, "CALC%i:MARK:FUNC %s;*WAI\n",channel,selection);
		break;
	case 21: // Marker to Center
		errStatus = viPrintf(vi, "SENS%i:FREQ:CENT (CALC%i:MARK%i:X:ABS?);*WAI\n",channel,channel,marker);
		break;
	case 22: case 23: // Marker to Reference
		errStatus = viPrintf(vi, "DISP:WIND%i:TRAC:Y:RLEV (CALC%i:MARK%i:Y?);*WAI\n",channel,channel,marker);
		break;
	case 24: // Marker to Elec Delay
		errStatus = viPrintf(vi, "SENS%i:CORR:EDEL:TIME (CALC%i:MARK%i:GDEL?);*WAI\n",channel,channel,marker);
		break;
	case 25: //SET ABS	
	  	errStatus = viPrintf(vi, "CALC%i:MARK%i:X:ABS %lf;*WAI\n",channel,marker,mkr_val);
		break;
	case 26: //TRACK ON
		errStatus = viPrintf(vi, "CALC%i:MARK:FUNC:TRAC ON;*WAI\n",channel);
		break;
	case 27: //TRACK OFF
		errStatus = viPrintf(vi, "CALC%i:MARK:FUNC:TRAC OFF;*WAI\n",channel);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_markerRead
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE :  Reads active marker or marker function   
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViPReal64 mkr_result. Contains specified marker result  
 * OUT        
 *            
 * PARAM 3 : ViString request. (OPTIONAL, default="AMPL"). Other choices are   
 * IN        DELAY, INDUCTANCE, PHASE, etc. (see code below). 
 *
 * PARAM 4 : ViInt32 marker. (OPTIONAL, default = 1)
 * IN        Contains the marker number  (1-8)  
 *
 * PARAM 5 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 * PARAM 6-8: ViPReal64 mkr_result2, 3, & 4. (OPTIONAL) 
 * OUT        Contains more marker results for Marker Math Functions   
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Phase and Delay require proper model number analyzer.
 *				For marker math Filter Stats (FST), mkr_result4 will always be 0.
 * 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_markerRead( 
        ViSession vi, 
		ViPReal64 mkr_result,
		ViString request,
		ViInt32 marker,
		ViInt32 channel,
		ViPReal64 mkr_result2,
		ViPReal64 mkr_result3,
		ViPReal64 mkr_result4)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_markerRead");

ViInt32 choice;
char selection[40];
const ViInt32 size = 13;
ViString req[size]= {"AMPL?", "AMPLITUDE?", "POSITION?", "POSN?", "REF_X?", "REF_Y?", 
					 "INDUCTANCE?", "REACTANCE?", "RESISTANCE?", "PHASE?", "MAGNITUDE?", 
					 "DELAY?",   "FUNCTION?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

*mkr_result4=0;// default for filter Stats 
strip(request, selection);

switch (choice)
	{
	case 0: case 1: //AMPLITUDE
		if ((errStatus = viPrintf(vi, "CALC%i:MARK%i:Y?;*WAI\n",channel,marker)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", mkr_result);
		break;
	case 2: case 3: //POSITION
		if ((errStatus = viPrintf(vi, "CALC%i:MARK%i:X?;*WAI\n",channel,marker)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", mkr_result);
		break;
	case 4: //REF X
		if ((errStatus = viPrintf(vi, "CALC%i:MARK:REF:X?;*WAI\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", mkr_result);
		break;
	case 5: //REF Y
		if ((errStatus = viPrintf(vi, "CALC%i:MARK:REF:Y?;*WAI\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", mkr_result);
		break;
	case 6: case 7: case 8: case 9: case 10://polar and smith markers
		if ((errStatus = viPrintf(vi, "CALC%i:MARK%i:Y:%s;*WAI\n",channel, marker, selection)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", mkr_result);
		break;
	case 11: //GROUP DELAY
		if ((errStatus = viPrintf(vi, "CALC%i:MARK%i:GDEL?;*WAI\n",channel, marker)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", mkr_result);
		break;
	case 12://FUNCTION
		if ((errStatus = viPrintf(vi, "CALC%i:MARK:FUNC:RES?;*WAI\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf,%lf,%lf,%lf\n", mkr_result, mkr_result2, mkr_result3, mkr_result4);
		break;
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_screen
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Set or read split display, IBASIC display, or expand mode)  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  See below for choices
 * IN
 *
 * PARAM 3 : ViPString screen_status. (OPTIONAL)  
 * OUT       Returns current status  
 * 
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_screen( 
        ViSession vi, 
		ViString request,
		ViPString screen_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_screen");


ViInt32 choice;
char selection[40];
const ViInt32 size = 13;
ViString req[size]= {"SPLIT_ON", "SPLIT", "SPLIT_OFF", "SPLIT?", 
					 "IBASIC_OFF", "FULL", "UPPER", "LOWER", "IBASIC?", 
					 "EXPAND_ON", "EXPAND", "EXPAND_OFF", "EXPAND?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

strip(request, selection);

switch (choice)
	{
case 0: case 1://Split ON
		errStatus = viPrintf(vi, "DISP:FORM ULOW;*WAI\n");
		break;
	case 2://Split Off
		errStatus = viPrintf(vi, "DISP:FORM SING;*WAI\n");
		break;
	case 3: //Split?
		if ((errStatus = viPrintf(vi, "DISP:FORM?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", screen_status);
		if (!(strcmp(screen_status, "ULOW")))  strcpy(screen_status,"ON");
		if (!(strcmp(screen_status, "SING")))  strcpy(screen_status,"OFF");
		break;
	case 4:	//IBASIC Off
		if ((errStatus = viPrintf(vi, "DISP:PROG:MODE OFF;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 5: case 6: case 7: //full, upper, lower
	   	if ((errStatus = viPrintf(vi, "DISP:PROG:MODE %s;*WAI\n", selection)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 8: //IBASIC?
		if ((errStatus = viPrintf(vi, "DISP:PROG:MODE?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%s\n", screen_status)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if (!(strcmp(screen_status, "LOW")))  strcpy(screen_status,"LOWER");
		if (!(strcmp(screen_status, "UPP")))  strcpy(screen_status,"UPPER");
		break;
	case 9:  case 10://Expand_ON
		errStatus = viPrintf(vi, "DISP:FORM:EXPAND ON;*WAI\n");
		break;
	case 11:  //Expand_OFF
		errStatus = viPrintf(vi, "DISP:FORM:EXPAND OFF;*WAI\n");
		break;
	case 12: //Expand?
		if ((errStatus = viPrintf(vi, "DISP:FORM:EXPAND?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", screen_status);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */



/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_triggerSource
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Set or read trigger source  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  Must be INTERNAL, SWEEP, POINT or ?
 * IN
 *
 * PARAM 3 : ViPString trig_status.  Returns current trigger source mode  
 * OUT           
 * *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_triggerSource( 
        ViSession vi, 
		ViString request,
		ViPString trig_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
char stat1[10];
char stat2[10];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_triggerSource");

ViInt32 choice;
const ViInt32 size = 5;
ViString req[size]= {"?","INTERNAL", "INT", "SWEEP", "POINT" 
				 	};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0: // Read Trigger Source
		if ((errStatus = viPrintf(vi, "TRIG:SOUR?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%s\n", stat1)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = viPrintf(vi, "SENS:SWE:TRIG:SOUR?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", stat2);
		if ((!(strcmp(stat1, "IMM"))) && (!(strcmp(stat2, "IMM"))))
			strcpy(trig_status,"INTERNAL");
		if ((!(strcmp(stat1, "EXT"))) && (!(strcmp(stat2, "EXT"))))
			strcpy(trig_status,"POINT");
		if ((!(strcmp(stat1, "EXT"))) && (!(strcmp(stat2, "IMM"))))
			strcpy(trig_status,"SWEEP");
		break;
	case 1: case 2: //Internal
	   	errStatus = viPrintf(vi, "TRIG:SOUR IMM;:SENS:SWE:TRIG:SOUR IMM;*WAI\n");
		break;
	case 3: //Sweep
		errStatus = viPrintf(vi, "TRIG:SOUR EXT;:SENS:SWE:TRIG:SOUR IMM;*WAI\n");
		break;
	case 4:  //Point
	  	errStatus = viPrintf(vi, "TRIG:SOUR EXT;:SENS:SWE:TRIG:SOUR EXT;*WAI\n");
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_display
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets various display options   
 *            
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  Choices are NORMALIZE, DATA,  
 * IN        DATA TO MEM, MEMORY, etc. (see code below). 
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 * 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_display( 
        ViSession vi, 
		ViString request,
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_display");
ViInt32 choice;

const ViInt32 size = 11;
ViString req[size]= {"NORMALIZE", "NORM", "DATA", "DATA_TO_MEM", "D2M", "MEMORY", "MEM", 
					 "DATA/MEM", "D/M", "DATA&MEM", "D&M" 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
{
case 0: case 1: //NORMALIZE
	errStatus = viPrintf(vi, "TRAC CH%iSMEM,CH%iSDATA;:CALC%i:MATH (IMPL/CH%iSMEM);:DISP:WIND%i:TRAC1 ON;TRAC2 OFF;*WAI\n",channel,channel,channel,channel,channel);
	break;
case 2: //DATA
	errStatus = viPrintf(vi, "CALC%i:MATH (IMPL);:DISP:WIND%i:TRAC1 ON;TRAC2 OFF;*WAI\n",channel,channel);
	break;
case 3: case 4: //DATA TO MEMORY
	errStatus = viPrintf(vi, "TRAC CH%iSMEM,CH%iSDATA;*WAI\n",channel,channel);
	break;
case 5: case 6: //MEMORY
	errStatus = viPrintf(vi, "DISP:WIND%i:TRAC1 OFF;TRAC2 ON;*WAI\n",channel);
	break;
case 7: case 8: //DATA/MEMORY
	errStatus = viPrintf(vi, "CALC%i:MATH (IMPL/CH%iSMEM);:DISP:WIND%i:TRAC1 ON;TRAC2 OFF;*WAI\n",channel,channel,channel);
	break;
case 9: case 10: //DATA AND MEMORY
	errStatus = viPrintf(vi, "CALC%i:MATH (IMPL);:DISP:WIND%i:TRAC1 ON;TRAC2 ON;*WAI\n",channel,channel);
	break;


}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_message
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets various message display options.  Displays user message   
 *           in message box.
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. (OPTIONAL; default is CLEAR) 
 *			 Choices are ON, OFF, ALL OFF, CLEAR, SHOW, SHOW3/5/8. 
 *			 SHOW, by itself, will display msg until cleared.  SHOW3  
 *			 displays msg for about 3 seconds, SHOW5 about 5 sec, etc.
 *
 * PARAM 3 : ViString msg. Contains desired message to be displayed  
 * IN       
 *
 * PARAM 4 : ViPInt32 msg_status. (OPTIONAL) 
 * OUT       Indicates current message state (ON=1, 0=OFF)  
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_message( 
        ViSession vi, 
		ViString request,
		ViString msg,
		ViPInt32 msg_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_message");
ViInt32 choice;
char selection[40];
const ViInt32 size = 12;
ViString req[size]= {"?", "ON", "OFF", "ALL_OFF", "CLEAR", "SHOW", "SHOW3", "SHORT", 
					 "SHOW5", "MEDIUM", "SHOW8", "LONG" 
};



if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if (choice ==0)
{
	if ((errStatus = viPrintf(vi, "DISP:ANN:MESS:STAT?;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	errStatus = delayVScanf(vi, "%i\n", msg_status);
}
else
{
	wordWrap(msg);// modify msg to perform word wrap
	strip(request, selection);
	switch (choice)
		{
		case 1: case 2:
			errStatus = viPrintf(vi, "DISP:ANN:MESS:STAT %s;*WAI\n", selection);
			break;
		case 3: 
			errStatus = viPrintf(vi, "DISP:ANN:MESS:AOFF;*WAI\n");
			break;
		case 4:
			errStatus = viPrintf(vi, "DISP:ANN:MESS:CLE;*WAI\n");
			break;
		case 5:
			errStatus = viPrintf(vi, "DISP:ANN:MESS:DATA '%s',NONE;*WAI\n", msg);
			break;
		case 6: case 7:
			errStatus = viPrintf(vi, "DISP:ANN:MESS:DATA '%s',SHORT;*WAI\n", msg);
			break;
		case 8: case 9:
			errStatus = viPrintf(vi, "DISP:ANN:MESS:DATA '%s',MEDIUM;*WAI\n", msg);
			break;
		case 10: case 11:
			errStatus = viPrintf(vi, "DISP:ANN:MESS:DATA '%s',LONG;*WAI\n", msg);
			break;
		}
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : wordWrap
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Perform word wrap on the variable msg at 45 char or closest space 
 *			 before 45 by inserting cr/lf at appropriate space.   
 *
 * PARAM 1 : ViPString msg
 * IN/OUT    msg to be modified for wordwrap.
 *            
/*****************************************************************************/
// definition of string processing function
int wordWrap(ViPString msg)
{
   #define WIDTH 45
   #define NO_SPACE -1
   char msgcopy[1024] = "";
   char *tokenPtr;
   size_t fieldEnd = WIDTH, noSpaceWidth, spacePos = NO_SPACE;

   if (strlen(msg) <= fieldEnd)
      return 0;
   else
   {
      tokenPtr = strtok(msg, "\n");
      while (tokenPtr != NULL)
      {
         while (strlen(tokenPtr) >= fieldEnd)
         {
            noSpaceWidth = strcspn(tokenPtr, " ");
            while (noSpaceWidth < fieldEnd) 
            {
               if (noSpaceWidth < strlen(tokenPtr))
               {
                  spacePos = noSpaceWidth;
                  *(tokenPtr+spacePos) = '\a';
               }
               noSpaceWidth = strcspn(tokenPtr, " ");
            } 
            if (spacePos != NO_SPACE)
            {
               *(tokenPtr+spacePos) = '\0';
               strcat(msgcopy, tokenPtr);
               strcat(msgcopy, "\n");
			   tokenPtr = tokenPtr + spacePos + 1;
               spacePos = NO_SPACE;
            }
            else
               fieldEnd += WIDTH;
         } 
         strcat(msgcopy, tokenPtr);
         strcat(msgcopy, "\n");
         tokenPtr = strtok(NULL, "\n");
      }
   }
   while (strcspn(msgcopy, "\a") < strlen(msgcopy))
   {
      spacePos = strcspn(msgcopy, "\a");
      *(msgcopy+spacePos) = ' ';
   }
   strcpy(msg, msgcopy);
   return 0;
}   /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_spurAvoid
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or Reads Spur Avoid feature  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. Must be AVOID, DITHER, NONE, OFF, ON or ?
 *
 * PARAM 3 : ViPString spur_status.  OPTIONAL  Returns current state. 
 * OUT       Returns NONE, DITHER, or AVOID    
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_spurAvoid( 
        ViSession vi, 
		ViString request,
		ViPString spur_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
ViInt32 stat;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_spurAvoid");

const ViInt32 size = 6;
ViString req[size]= {"?", "OFF", "NONE", "DITHER", "AVOID", "ON"
};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if (choice ==0)
{
	if ((errStatus = viPrintf(vi, "DIAG:SPUR:METH?;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	errStatus = delayVScanf(vi, "%i\n", &stat);
	strcpy(spur_status, req[stat+2]);
}
else
{
	switch (choice)
	{
	case 1: case 2:
		errStatus = viPrintf(vi, "DIAG:SPUR:METH NONE;*WAI\n");
		break;
	case 3: 
		errStatus = viPrintf(vi, "DIAG:SPUR:METH DITHER;*WAI\n");
		break;
	case 4: case 5: 
		errStatus = viPrintf(vi, "DIAG:SPUR:METH AVOID;*WAI\n");
		break;
	}
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_softkey
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets Softkeys #1 through 7; One-at-a-time or all at once  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString key. OPTIONAL.  Contains individual key label (20 chr max), 
 * IN		 or all keys separated by "|".  If not specified; erases all softkeys.
 *
 * PARAM 3 : ViInt32 sfky_number.  (OPTIONAL)  Softkey number if setting only one   
 * IN        softkey label 
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Only 7 softkeys are available!
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_softkey( 
        ViSession vi, 
		ViString key,
		ViInt32 sfky_number)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

char parse[256];
ViInt32 not_done, index = 0;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_softkey");

switch (sfky_number)
	{
	case 0: // Erase All or Do all Softkeys
	if (!strcmp(key, "ERASE_SOFTKEYS"))
	  	{
		for (index = 1; index<=7; index++)
			errStatus = viPrintf(vi, "DISP:MENU:KEY%i '';*WAI\n",index);
		break;
		}
	else
		{
		do
			{ 
			errStatus = hp871x_stringParse(vi, key, parse, &not_done,"|");
			index++;
			if (!(strlen(parse) ==0))
				errStatus = viPrintf(vi, "DISP:MENU:KEY%i '%s';*WAI\n",index, parse);
			}
			while (not_done);
		break;
		}
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: // Do one softkey only
		errStatus = viPrintf(vi, "DISP:MENU:KEY%i '%s';*WAI\n",sfky_number, key);
		break;
	default:
		return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR);
		break;
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_refOscillator
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Set or read reference oscillator source  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. Choices are INT, EXT, or ?
 * IN
 *
 * PARAM 3 : ViPInt32 refOsc_status OPTIONAL (1=External, 0=Internal)  
 * OUT           
 * *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_refOscillator( 
        ViSession vi, 
		ViString request,
		ViPInt32 refOsc_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
char stat[20];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_refOscillator");
ViInt32 choice;

const ViInt32 size = 5;
ViString req[size]= {"?", "INT", "INTERNAL", "EXT", "EXTERNAL" 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0: //?
		if ((errStatus = viPrintf(vi, "SENS:ROSC:SOUR?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", stat);
		*refOsc_status =abs(strcmpi(stat, "INT"));
		break;
	case 1: case 2: //Internal
		errStatus = viPrintf(vi, "SENS:ROSC:SOUR INT;*WAI\n");
		break;
	case 3: case 4: //External
		errStatus = viPrintf(vi, "SENS:ROSC:SOUR EXT;*WAI\n");
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_title
 *-----------------------------------------------------------------------------
 * 
 *PURPOSE : Sets title (or clock time) to either of the two title
 *          lines on the analyzer display; sets or reads title
 *          ON/OFF status, or turns clock display off. 
 * 
 *PARAM 1 : ViSession vi.
 *IN        Instrument Handle returned from hp871x_init().
 *            
 *PARAM 2 : ViString request.  See choices in code below.
 *IN        
 *
 *PARAM 3 : ViString title.
 *IN        Title to be shown on the analyzer display.  Default =
 *          "Not Specified".
 *
 *PARAM 4 : ViPInt32 title_status.  
 *OUT       When request is a query, returns 1 if title is
 *          currently being displayed, 0 if not.    
 *
 *Note:  The clock time cannot be displayed on both title lines
 *       simultaneously.         
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_title( 
        ViSession vi, 
		ViString request,
		ViString title,
		ViPInt32 title_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
char selection[40];
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_title");

const ViInt32 size = 9;
ViString req[size]= {"?", "ON", "OFF", "TITLE1", "TITLE2", "CLOCK0", "CLOCK_OFF",
					"CLOCK1", "CLOCK2"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0://?
		if ((errStatus = viPrintf(vi, "DISP:ANN:TITL:STAT?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", title_status);
		break;
	case 1: case 2://ON/OFF
		errStatus = viPrintf(vi, "DISP:ANN:TITL:STAT %s;*WAI\n", selection);
		break;
	case 3: case 4: // Line 1 or line 2
		errStatus = viPrintf(vi, "DISP:ANN:%s:DATA '%s';*WAI\n", selection,title);
		break;
	case 5: case 6://Clock OFF
		errStatus = viPrintf(vi, "DISP:ANN:CLOC:MODE OFF;*WAI\n");
		break;
	case 7: //Clock 1
		errStatus = viPrintf(vi, "DISP:ANN:CLOC:MODE LINE1;*WAI\n");
		break;
	case 8: //Clock 2
		errStatus = viPrintf(vi, "DISP:ANN:CLOC:MODE LINE2;*WAI\n");
			break;
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_keyQueue
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets up key queue parameters.  Used for reading keystroke inputs.
 *			 See also keyRead.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. (OPTIONAL Default = CLEAR) 
 * IN		 Other choices are shown in code below.
 *
 * PARAM 3 : ViPInt32 queue_status.  (OPTIONAL) Returns queue state, max count,
 * OUT       or current count. 
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_keyQueue( 
        ViSession vi, 
		ViString request,
		ViPInt32 queue_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_keyQueue");
ViInt32 choice;
char selection[40];
const ViInt32 size = 8;
ViString req[size]= {"?", "QUEUE?", "COUNT?", "ON", "OFF", "CLEAR",   
					 "MAX?", "MAXIMUM?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
strip(request, selection);

switch (choice)
{
case 0: case 1: // Read Queue Status
    if ((errStatus = viPrintf(vi, "SYST:KEY:QUE:STAT?;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	errStatus = delayVScanf(vi, "%i\n", queue_status);
	break;
case 2: // Read Current Count
    if ((errStatus = viPrintf(vi, "SYST:KEY:QUE:COUN?;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	errStatus = delayVScanf(vi, "%i\n", queue_status);
	break;
case 3: case 4: // Turn on/off queue
	errStatus = viPrintf(vi, "SYST:KEY:QUE:STAT %s;*WAI\n",selection);
	break;
case 5: // Clear Queue
	errStatus = viPrintf(vi, "SYST:KEY:QUE:CLE;*WAI\n");
	break;
case 6: case 7: // Read Max Queue 
    if ((errStatus = viPrintf(vi, "SYST:KEY:QUE:MAX?;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	errStatus = delayVScanf(vi, "%i\n", queue_status);
	break;
}	
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_keyRead
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Reads Front Panel Keypress/RPG or Ext Keyboard  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViPString keytype. Returns NONE, RPG, KEY or ASC
 * OUT		 
 *
 * PARAM 3 : ViPInt32 keycode. Returns key pressed or or RPG count
 * OUT        
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_keyRead( 
        ViSession vi, 
		ViPString keytype,
		ViPInt32 keycode)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
char keytemp[6]="";

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_keyRead");


 if ((errStatus = viPrintf(vi, "SYST:KEY:TYPE?\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
 if ((errStatus = delayVScanf(vi, "%s\n", keytype)) < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);

 if (!(strcmp(keytype,"NONE"))) 
	return statusUpdate(vi, thisPtr, VI_SUCCESS);//Exit here if NONE

 
 if ((errStatus = viPrintf(vi, "SYST:KEY:VAL?\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
 if ((errStatus = delayVScanf(vi, "%i\n", keycode)) < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);


return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_autozero
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Turn broadband detector Autozero On/Off.  Performing a zero ONCE
 *			 turns off Autozero
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. (OPTIONAL Default=ONCE). 
 * IN		 Others are ON, OFF, AUTOZERO or ?
 *
 * PARAM 3 : ViPInt32 az_status.  OPTIONAL  
 * OUT       Returns 1 for AutoZero ON, 0 for OFF    
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_autozero( 
        ViSession vi, 
		ViString request,
		ViPInt32 az_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_autozero");
ViInt32 choice;
char selection[40];
const ViInt32 size = 5;
ViString req[size]= {"ONCE", "ON", "OFF", "?", "AUTOZERO?" 
};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0: case 1: case 2://
		errStatus = hp871x_outputf(vi, 2, "CAL:ZERO:AUTO %s", selection);
		break;
	case 3: case 4://?
		if ((errStatus = viPrintf(vi, "CAL:ZERO:AUTO?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", az_status);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_calkit
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Selects cal kit to be used
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString request. Cal Kit type (see codes below). 
 * IN		 
 *
 * PARAM 3 : ViInt32 port_num. OPTIONAL Port number. 
 * IN		 Used only on 8712E/14E or above.
 *
 * PARAM 3 : ViPString cur_kit. Contains current kit selected
 * OUT
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_calkit( 
        ViSession vi, 
		ViString request,
		ViInt32 port_num,
		ViPString cur_kit)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

char output[100];
ViInt32 choice = 0;
ViInt32 index;
char code[100], rev[15];
char *token;
ViReal64 rev_value;
char selection[40];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_calkit");

const ViInt32 size = 9;
ViString req[size];

ViString meas[size][2]= {"N50F" , "COAX,7MM,TYPE-N,50,FEMALE",
						 "N50M" , "COAX,7MM,TYPE-N,50,MALE",
						  "3.5" , "COAX,3.5MM,APC-3.5,50,IMPLIED",
						 "USER" , "USER,IMPLIED,IMPLIED,IMPLIED,IMPLIED",
						 "USER2", "USER2,IMPLIED,IMPLIED,IMPLIED,IMPLIED",
						 "N75F" , "COAX,7MM,TYPE-N,75,FEMALE",
						 "N75M" , "COAX,7MM,TYPE-N,75,MALE",
						  "F75" , "COAX,7MM,TYPE-F,75,IMPLIED",
						 "APC-7", "COAX.7MM,APC-7,50,IMPLIED"
						};
if ((errStatus = hp871x_readID(vi, rev, "REV_VALUE?", &rev_value)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
if (port_num<1) port_num=1;
strip(request,selection);
if (strcmpi(selection, "?")) //  NOT a query!, set cal kit type
	{ 
	for (index=0;  index<size; index++) //Copy to single dimension array
		 req[index]= meas[index][0];
	if(getChoice(vi,request,size,req,&choice)) 
		return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

	if (rev_value<4.9) // 871xA/B/C	
		{
		sprintf(output, "SENS:CORR:COLL:CKIT '%s'", meas[choice][1]);
		if ((errStatus = viPrintf(vi, "%s\n",output)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		}
	else //871xE
		{	
		sprintf(output, "SENS:CORR:COLL:CKIT:PORT%i '%s'", port_num, meas[choice][1]);
		if ((errStatus = viPrintf(vi, "%s\n",output)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		}
	}
else // Read Kit Type
{
	if (rev_value<5) // 871xA/B/C	
	{	if ((errStatus = viPrintf(vi, "SENS:CORR:COLL:CKIT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	}
	else
	{	if ((errStatus = viPrintf(vi, "SENS:CORR:COLL:CKIT:PORT%i?\n", port_num)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	}
	if ((errStatus = delayVScanf(vi, "%t\n", code)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	token = strtok(code, "\"");
	while (strcmp(token, meas[choice][1]))
		{
		choice++;
		if (choice==size)
			return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR );
		}
	strcpy(cur_kit, meas[choice][0]);
	}
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_calMeasure
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Performs the actual calibration using a specific type of standard   
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  See code below for choices.  
 * IN         
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */

ViStatus _VI_FUNC hp871x_calMeasure( 
        ViSession vi, 
		ViString request,
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_calMeasure");
ViInt32 choice;

const ViInt32 size = 21;
ViString req[size]= {"1", "STANDARD_1", "STAN1", "2", "STANDARD_2", "STAN2",
					 "3", "STANDARD_3", "STAN3", "4", "STANDARD_4", "STAN4",
					 "5", "STANDARD_5", "STAN5", "6", "STANDARD_6", "STAN6",
					 "7", "STANDARD_7", "STAN7"	
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

if ((errStatus = hp871x_checkChanStatus(vi,channel)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);


 switch (choice)
	{
	case 0: case 1: case 2://STAN1
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN1",channel);
		break;
	case 3: case 4: case 5: //STAN2
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN2",channel);
		break;
	case 6: case 7: case 8: //STAN3
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN3",channel);
		break;
	case 9: case 10: case 11://STAN4
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN4",channel);
		break;
	case 12: case 13: case 14://STAN5
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN5",channel);
		break;
	case 15: case 16: case 17: //STAN6
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN6",channel);
		break;
	case 18: case 19: case 20: //STAN7
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN7",channel);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_calType
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Chooses the Type of Cal (resp, refl, etc.)   
 *            
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. For choices, see code below.  
 * IN         
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Enhanced cal not valid on 8711A/871xB.
 * 
 *-----------------------------------------------------------------------------
 */
 
ViStatus _VI_FUNC hp871x_calType( 
        ViSession vi, 
		ViString request,
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_calType");
ViInt32 choice;

const ViInt32 size = 15;
ViString req[size]= {"RESPONSE", "RESP", "THRU", "THROUGH", "RESPONSE_&_ISOLATION", 
					 "RESP_&_ISOL", "R&I", "ENHANCED_RESPONSE", "ENH_RESP","ENHANCED", 
					 "REFLECTION","REFL", "TWOPORT", "NORMALIZE", "NORM" 					 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

 switch (choice)
{
	case 0: case 1: case 2: case 3: //Response
		errStatus = viPrintf(vi, "SENS%i:CORR:COLL:METH TRAN1;*WAI\n",channel);
		break;
	case 4: case 5: case 6://Response & Isolation
		errStatus = viPrintf(vi, "SENS%i:CORR:COLL:METH TRAN2;*WAI\n",channel);
		break;
	case 7: case 8: case 9: //Enhanced Response 
		errStatus = viPrintf(vi, "SENS%i:CORR:COLL:METH TRAN3;*WAI\n",channel);
		break;
	case 10: case 11: //Reflection
		errStatus = viPrintf(vi, "SENS%i:CORR:COLL:METH REFL3;*WAI\n",channel);
		break;
	case 12: //Two-port
		errStatus = viPrintf(vi, "SENS%i:CORR:COLL:METH TWOPORT;*WAI\n",channel);
		break;
	case 13: case 14: //NORMALIZE
		errStatus = hp871x_outputf(vi, 2, "TRAC CH%iSMEM,CH%iSDATA;:CALC%i:MATH (IMPL/CH%iSMEM);:DISP:WIND%i:TRAC1 ON;TRAC2 OFF",channel,channel,channel,channel,channel);
		break;
 }

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_calControl
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Performs various calibration duties   
 *            
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  See code below for choices.
 * IN        
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)
 *
 * PARAM 4 : ViPString cal_type.  (OPTIONAL)  Contains current 
 * OUT       Cal Type (FULL,USER,DEFAULT)
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * 
 *-----------------------------------------------------------------------------
 */
 
ViStatus _VI_FUNC hp871x_calControl( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPString cal_type)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_calControl");
ViInt32 choice;
char selection[40];
const ViInt32 size = 27;
ViString req[size]= { "TYPE?", "FULL", "FULL_BAND", "USER", "USER_DEFINED", "DEFAULT", 
					 "SAVE", "ABORT", "ON", "OFF", "STATUS?", "CLASS?", "DEF1", "DEFAULT1", 
					 "DEF2", "DEFAULT2", "REFL3", "REFLECTION3", "TRAN1", "TRANSMISSION1",
					 "TRAN2", "TRANSMISSION2", "TRAN3", "TRANSMISSION3", "TEST1", "TESTSET1",
					 "TWOPORT"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0:
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:CSET:SEL?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", cal_type);
		if (!(strcmp(cal_type, "DEF")))  strcpy(cal_type,"DEFAULT");
		break;
	case 1: case 2: //FULL
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:COLL:IST:AUTO ON",channel);
		break;
	case 3: case 4: //USER DEFINED
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:COLL:IST:AUTO OFF",channel);
		break;
	case 5: //DEFAULT
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:CSET:SEL DEF",channel);
		break;
	case 6: //SAVE
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:COLL:SAVE",channel);
		break;
	case 7: //ABORT
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:COLL:ABORT",channel);
		break;
	case 8: case 9: // Cal On/Off
		errStatus = hp871x_outputf(vi, 1, "SENS%i:CORR:STAT %s", channel, selection);
		break;
	case 10: //Status?
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:ANN?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "\"%t\n", cal_type);
		cal_type[strlen(cal_type)-2] = '\0'; //overwrite last quote and LF character
		if (!(strcmp(cal_type, "C ")))  strcpy(cal_type,"C"); //remove space
		break;
	case 11: //Class?
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:CLAS?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", cal_type);
		break;
	default: //Class set
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:CLAS %s",channel, selection);
		break;

}
		
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_aperture
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns current Group Delay aperture in % or Freq Span 
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViReal64 aperture.  Values =<100 assume % of sweep.
 * IN        Values >100 assume span in Hz.
 *
 * PARAM 2 : ViString request. (OPTIONAL, default="SET"). Other choices are 
 * IN   	 "%?" or "SPAN?". 
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)  
 *
 * PARAM 4 : ViPReal64 cur_aperture (OPTIONAL) 
 * OUT       Indicates current aper value in %, or span in Hz. 
 *
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Aperture requires phase capable analyzer model.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_aperture( 
        ViSession vi,
		ViReal64 aperture,
		ViString request,
		ViInt32 channel,
		ViPReal64 cur_aperture)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_aperture");
ViInt32 choice;

const ViInt32 size = 5;
ViString req[size]= {"SET", "%?", "?", "PERCENT?", "SPAN?"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	case 0://Set Aperture
		if (aperture <= 100) 
		{
			if ((errStatus = viPrintf(vi, "CALC%i:GDAP:APER %lf;*WAI\n",channel, aperture/100)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
		else
		{
   			if ((errStatus = viPrintf(vi, "CALC%i:GDAP:SPAN %lf;*WAI\n",channel,aperture)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
		break;
	case 1: case 2: case 3://Read Percent
		if ((errStatus = viPrintf(vi, "CALC%i:GDAP:APER?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_aperture)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		*cur_aperture= (*cur_aperture * 100);
		break;
	case 4://Read Aperture SPAN
 		if ((errStatus = viPrintf(vi, "CALC%i:GDAP:SPAN?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", cur_aperture)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	}
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_takeSweep
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Takes specified number of sweeps or determines best number of 
 *			 sweeps to take, then takes them.   
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViInt32 sweeps. (OPTIONAL default=0) If not specified (0), takes  
 * IN        1 or more sweeps depending upon avg on/off and averaging factor.  
 *			 
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_takeSweep( 
        ViSession vi, 
		ViInt32 sweeps)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 alt_swp, swp, dummy=0;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_takeSweep");

ViInt32 index,chan;
ViInt32 avg_factor[3], avg_on[3],max_swps[3]; // dummy=0, Ch1=1, Ch2=2


// Find if Alt Sweep  1=AltSwpOn   0=Normal

if ((errStatus = hp871x_sweepAlt(vi, "?", &alt_swp)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

max_swps[1] = __max(sweeps, 1);
max_swps[2] = __max(sweeps, 1);

if (sweeps == 0) // sweeps not specified
	{
	for (chan = 1; chan<=2; chan++) //Find avg on each ch
		{	
	    if ((errStatus = hp871x_average(vi, dummy, "STATUS?", chan, &avg_on[chan])) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = hp871x_average(vi, dummy, "FACTOR?", chan, &avg_factor[chan])) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if (avg_on[chan] ==1)
			max_swps[chan] = avg_factor[chan]*3/2; //take 1.5*avg for best settling
		}
	}

// Abort all sweeps
if ((errStatus = viPrintf(vi, "ABOR;*WAI\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);


if (alt_swp == 1)
	{
	for (chan = 1; chan<=2; chan++)
		{
		if ((errStatus = viPrintf(vi, "INIT%i:CONT OFF;*WAI\n", chan)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		for (index = 0; index<=max_swps[chan]; index++)
			if ((errStatus = hp871x_outputf(vi, 3,":INIT%i", chan)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		}
	}
else
	{  
	swp = __max(max_swps[1], max_swps[2]);
	if ((errStatus = viPrintf(vi, "INIT:CONT OFF;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	for (index = 0; index<swp; index++)
		if ((errStatus = hp871x_outputf(vi, 3,":INIT")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	}

return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_traceRead
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : This function reads trace data or calibration data 
 
 *
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 * 
 * PARAM 2 : ViReal64 _VI_FAR trace[].
 * OUT       64 bit Real array to receive the data values.
 *           
 * PARAM 3 : ViString request. OPTIONAL; Default= FDATA (Formatted data)
 * IN        
 * 
 * PARAM 4 : ViInt32 channel. OPTIONAL; default=1
 * IN        
 * 
 * PARAM 5 : ViReal64 _VI_FAR trace2[].
 * OUT       64 bit Real array to receive imaginary or phase data values for 
 *			 those requests that require two data arrays.
 * 
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */

 ViStatus _VI_FUNC hp871x_traceRead( 
        ViSession vi, 
		ViReal64 _VI_FAR trace[],
		ViString request,		
		ViInt32 channel,
		ViReal64 _VI_FAR trace2[])
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_traceRead");

ViInt32  choice, index, dimension=1;
const ViInt32 dummy =0;
char format[11];
ViInt32   ArrSize, nbytes;
char      lc[100];
ViUInt32  cnt;
char      _huge *Array;
ViReal32 trace_temp[3202];

const ViInt32 size = 19;
ViString req[size]= {"FDATA?", "FMEM?", "R&I?", "R&I_MEM?", "A_RAW?", "B_RAW?", "R_RAW?",
					 "CORR1?", "CORR2?", "CORR3?", "CORR4?","CORR5?", "CORR6?", "CORR7?", 
					 "CORR8?","CORR9?", "CORR10?", "CORR11?", "CORR12?"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

if ((errStatus = hp871x_format(vi, "?", channel, format)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

if ((!strcmp(format, "POLAR")) || (!strcmp(format, "SMITH")) || (choice>1))
    dimension =2;
 
if ((dimension == 2) && (trace2==0))// 2nd array not passed
	return statusUpdate(vi, thisPtr, hp871x_MEAS_CONFLICT_ERROR);

if ((errStatus = viPrintf(vi, "FORM:BORD SWAP;:FORM:DATA REAL,32;*WAI\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);


switch (choice)
	{ 
	case 0://Formatted Data
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iFDATA\n", channel);
		break;
	case 1://Formatted Memory
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iFMEM\n", channel);
		break;
	case 2://Unformatted Data
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iSDATA\n", channel);
		break;
	case 3://Unformatted Memory
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iSMEM\n", channel);
		break;
	case 4://Raw A
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iAFWD\n", channel);
		break;
	case 5://Raw B
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iBFWD\n", channel);
		break;
	case 6://Raw R
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iRFWD\n", channel);
		break;
	case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18://CORR 1-12
		errStatus = viPrintf(vi, "TRAC:DATA? CH%iSCORR%i\n", channel, choice-6);
		break;
	}
	
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);

if ((errStatus = delayRead(vi, (ViPBuf)lc, 2, &cnt)) < VI_SUCCESS)
   return statusUpdate(vi, thisPtr, errStatus);

lc[2]='\0';
nbytes = atoi(lc+1);

if ((errStatus = delayRead(vi, (ViPBuf)lc, nbytes, &cnt)) < VI_SUCCESS)
   return statusUpdate(vi, thisPtr, errStatus);

lc[cnt]='\0';
ArrSize = atol(lc);

Array = (char *)malloc(ArrSize+1); //extra char for linefeed at end
if (!Array)
   {
    thisPtr->errNumber = VI_ERROR_ALLOC;
    return VI_ERROR_ALLOC;
   }

if ((errStatus = delayRead(vi, (ViPBuf)Array, ArrSize+1, &cnt)) < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
     
if (cnt != (unsigned)(ArrSize+1)) 
	return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR);

ArrSize = ArrSize/sizeof(ViReal32);
memcpy(trace_temp, Array, (size_t)ArrSize*sizeof(ViReal32));

if (dimension ==1)
	for (index=0;  index<ArrSize ;index++)   // loop through data points
		trace[index] = trace_temp[index];
else
	{	
	for (index=0;  index<ArrSize/2 ;index++) 
		{
		trace[index] = trace_temp[2*index];
		trace2[index] = trace_temp[2*index+1];
		}
	if (choice<2) // convert to mag/Phase
		RI_to_MagPhase(ArrSize/2, trace, trace2);
	}

free(Array);
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}          /* ----- end of function ----- */
 

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_traceAvgRead
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Reads an entire trace and averages all points into one value. 
 *			 Normally used for magnitude CW traces only (Lin or LOG).
 *           Does not take the sweeps...use takeSweep for that.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViPReal64 avg_value.  Returned avg of entire trace. Either Log 
 * IN        or Lin is returned depending upon current meas setting.  
 *			 
 * PARAM 3 : ViInt32 channel. OPTIONAL; default=1
 * IN        
 * 
 *           
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_traceAvgRead( 
        ViSession vi, 
		ViPReal64 trace_avg,
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 log_format,points, index, dummy=0;
char format[15];
ViReal64 array[1601];
ViReal64 sum = 0;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_traceAvgRead");

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

// Find if Lin or LOG mode
if ((errStatus = hp871x_format(vi, "?", channel, format)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
// Exit with error if not Lin or Log
if ((strcmp(format, "LIN")) && (strcmp(format, "LOG")))
	return statusUpdate(vi, thisPtr, hp871x_MEAS_CONFLICT_ERROR); 
log_format = abs(strcmp(format, "LIN")); 
   
//Find # of Points
if ((errStatus = hp871x_points(vi, dummy, "?", channel, &points)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

if ((errStatus = hp871x_traceRead(vi, array)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

if (log_format) // convert to LIN here if LOG;
	for (index=0;index<points;index++) 
	  	array[index] = pow(10, (array[index]/20));

//Sum all
for (index=0;index<points;index++) 
  	sum = sum + array[index];
*trace_avg= sum/points;

if (log_format) // convert back to LOG here;
	*trace_avg = (20.0 * log10(*trace_avg));

return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */



/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_userTTL
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or Reads User TTL function  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. Must be KEY, DEFAULT, SWEEP or ?
 *
 * PARAM 3 : ViPString TTL_status.  OPTIONAL  
 * OUT       Returns KEY, DEFAULT, or SWEEP    
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: SWEEP is not valid on 8711A and 871xB.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_userTTL( 
        ViSession vi, 
		ViString request,
		ViPString TTL_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, old=0, stat;
char model[15];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_userTTL");
char selection[40];
const ViInt32 size = 5;
ViString req[size]= {"?", "DEFAULT", "DEF", "KEY", "SWEEP"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if ((errStatus = hp871x_readID(vi, model)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
strip(request, selection);

if ((!strcmp(model, "8711A")) || (!strcmp(model, "8711B")) || (!strcmp(model, "8712B")) || (!strcmp(model, "8713B")) || (!strcmp(model, "8714B")) )
	old=1;

if (!old) // 871xC and above
	{
	if (choice ==0) //Then Query
		{
		if ((errStatus = viPrintf(vi, "SYST:COMM:TTL:USER:FEED?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", TTL_status);
		if (!(strcmp(TTL_status, "DEF")))  strcpy(TTL_status,"DEFAULT");
		if (!(strcmp(TTL_status, "SWE")))  strcpy(TTL_status,"SWEEP");
		}
	else
		errStatus = viPrintf(vi, "SYST:COMM:TTL:USER:FEED %s;*WAI\n", selection);
	}
else  // 8711A and 871xB  
	{
	if (choice ==0) //Then Query
		{
		strcpy(TTL_status,"DEFAULT");
		if ((errStatus = viPrintf(vi, "SYST:COMM:TTL:USER:FEED:KEY?;*WAI\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", &stat);
		if (stat==1)  strcpy(TTL_status,"KEY");
		}
	else
		{
		switch (choice)
			{ 
			case 1: case 2: //def or ON 
				errStatus = viPrintf(vi, "SYST:COMM:TTL:USER:FEED:KEY OFF;*WAI\n");
				break;
			case 3:  //auto step key or ON 
				errStatus = viPrintf(vi, "SYST:COMM:TTL:USER:FEED:KEY ON;*WAI\n");
				break;
			case 4:  // Not Supported  ERROR!
				return statusUpdate(vi, thisPtr, hp871x_MEAS_CONFLICT_ERROR);
				break;
			}
		}
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : RI_to_MagPhase
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Converts Real & Imag pairs to Magnitude and Phase pairs
 *           All array sizes must be identical
 *
 * PARAM 1 : int points.  Number of elements in each array
 *
 * PARAM 2 : double *val_1.  Array of real numbers in; Array of 
 * IN/OUT    magnitude numbers out.        
 *            
 * PARAM 3 : double *val_2.  Array of imag numbers in; Array of 
 * IN/OUT    phase numbers out.        
 *            
 * RETURNS : 0 when passed
 * 
/****************************************************************************/

int RI_to_MagPhase(int points,
				    double *val_1,
				    double *val_2)
{
const double PI = 3.1415926536;
double real, imag, rad; //real, imaginary, radians

for (int index=0; index<points; index++)
	{
    real= *(val_1 + index);
	imag= *(val_2 + index);
	if (real==0)
		{
		if (imag<0) rad = -PI/2.0;
		if (imag>0) rad = PI/2.0;
		if (imag==0) rad = 0;
		}
	else
		{
		rad = atan(imag/real);
		if ((real<0) && (imag<0)) rad = rad -PI;
		if ((real<0) && (imag>0)) rad = rad +PI;
		if ((real<0) && (imag==0)) rad = PI;
		}
	*(val_2 +index) = rad*180/PI; //degrees
	*(val_1 +index) = sqrt(real*real+imag*imag); //magnitude
	}
return 0;
}      /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : MagPhase_to_RI
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Converts Magnitude and Phase pairs to Real & Imag pairs 
 *           All array sizes must be identical
 *
 * PARAM 1 : int points.  Number of elements in each array
 *
 * PARAM 2 : double *val_1.  Array of real numbers in; Array of 
 * IN/OUT    magnitude numbers out.        
 *            
 * PARAM 3 : double *val_2.  Array of imag numbers in; Array of 
 * IN/OUT    phase numbers out.        
 *            
 * RETURNS : 0 when passed
 * 
/****************************************************************************/

int MagPhase_to_RI(int points,
				    double *val_1,
				    double *val_2)
{
const double PI = 3.1415926536;
double magn, phase, rad; //magnitude, phase, radians

for (int index=0; index<points; index++)
{
    magn= *(val_1 + index);
	phase= *(val_2 + index);
	
	rad = phase* PI/180.0;
	*(val_2 +index) = magn*sin(rad); //IMAG
	*(val_1 +index) = magn*cos(rad); //REAL
}
return 0;
}      /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_Z0
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or reads System or Smith chart nominal impedance  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViReal64 impedance.  Contains Impedance desired (in ohms) 
 * IN           
 *
 * PARAM 2 : ViString request. OPTIONAL.  Default=SYSTEM  See below for others
 *
 * PARAM 4 : ViPReal64 cur_imp.  OPTIONAL  
 * OUT       Contains current system, or Smith Chart, nominal impedance    
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *
 * NOTE:      SYSTEM impedance overrides Smith impedance.  i.e. It sets both!
 *			  SYSTEM is only valid on 871xC rev 4.03 or above
 *           
 * LIMITATIONS: SYSTEM not valid on 8711A or 871xB or 871xC Rev<4.03.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_Z0( 
        ViSession vi, 
		ViReal64 impedance,
		ViString request,
		ViPReal64 cur_imp)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
ViReal64 stat;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_Z0");

const ViInt32 size = 6;
ViString req[size]= {"SYSTEM", "SYST", "SMITH", "?", "SYSTEM?", "SMITH?"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{ 
	case 0: case 1://System Imp
		if (impedance == 50) 
			errStatus = viPrintf(vi, "SENS:CORR:IMP:INP:MAGN:SEL Z0_50;*WAI\n");
		else if (impedance == 75) 
			errStatus = viPrintf(vi, "SENS:CORR:IMP:INP:MAGN:SEL Z0_75;*WAI\n");
		else
			return statusUpdate(vi, thisPtr, hp871x_MEAS_CONFLICT_ERROR);
		break;
	case 2: //SMITH Imp
		errStatus = viPrintf(vi, "SENS:CORR:IMP:INP:MAGN %lf OHM;*WAI\n", impedance);
		break;
	case 3: case 4: // Query System Imp
		if ((errStatus = viPrintf(vi, "SENS:CORR:IMP:INP:MAGN:SEL?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", &stat);
		*cur_imp = 50 + (25*stat);
		break;
	case 5: // Query Smith Imp
		if ((errStatus = viPrintf(vi, "SENS:CORR:IMP:INP:MAGN?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_imp);
		break;
	}
	
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_labelsFreq
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets X-axis status, resolution or enables secure mode.
 *			 Reads label status. See also labelsUser
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  See code for choices
 *
 * PARAM 3 : ViInt32 channel. OPTIONAL; default=1
 * IN        
 *
 * PARAM 4 : ViPInt32 lblFreq_status.  OPTIONAL  
 * OUT       Returns status (1=ON, 0=OFF) of requested parameter     
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_labelsFreq( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPInt32 lblFreq_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
char selection[40];
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_labelsFreq");

const ViInt32 size = 11;
ViString req[size]= {"?", "STATUS?", "ON", "OFF", "MHZ", "KHZ", "HZ", "PRIVATE",
					"S/S", "CW", "CSPAN"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0: case 1:
		if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ:STAT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", lblFreq_status);
		break;
	case 2: case 3://ON/OFF
		errStatus = viPrintf(vi, "DISP:ANN:FREQ:STAT %s;*WAI\n", selection);
		break;
	case 4: case 5: case 6: // Resolution
		errStatus = viPrintf(vi, "DISP:ANN:FREQ:RES %s;*WAI\n", selection);
		break;
	case 7://Private
		errStatus = viPrintf(vi, "DIAG:ANN:FREQ:PERC;*WAI\n");
		break;
	case 8: // S/S
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE SSTOP;*WAI\n", channel);
		break;
	case 9: case 10: //CSPAN or CW
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:MODE %s;*WAI\n", channel, selection);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_labelsUser
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets User defined x-axis labels, units and title.
 *			 Reads user label status. See also labelsFreq
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. See code below for choices
 * IN
 *
 * PARAM 3 : ViReal64  lbl_value.  Contains numeric data for request
 * IN
 *
 * PARAM 4 : ViString label. OPTIONAL  String data for request
 * IN
 *
 * PARAM 5 : ViInt32 channel OPTIONAL; default=1
 * IN        
 * 
 * PARAM 6 : ViPInt32 lblUser_status.  OPTIONAL  
 * OUT       Returns status (1=ON, 0=OFF) of User labels     
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_labelsUser( 
        ViSession vi, 
		ViString request,
		ViReal64 lbl_value,
		ViString label,
		ViInt32 channel,
		ViPInt32 lblUser_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
char rev[15];
ViReal64 rev_value;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_labelsUser");

const ViInt32 size = 11;
ViString req[size]= {"?", "STATUS?", "ON", "OFF", "LABEL", "SUFFIX", "UNITS", "START", "LEFT",
					 "STOP", "RIGHT"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	case 0: case 1:
		if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:STAT?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", lblUser_status);
		break;
	case 2: //ON
		if ((errStatus = hp871x_readID(vi, rev, "REV_VALUE?", &rev_value)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if (rev_value >=4.0)//turn on annot for 871xC or above
			if ((errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:STAT ON;*WAI\n", channel)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:STAT ON;*WAI\n", channel);
		break;
	case 3: //OFF
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:STAT OFF;*WAI\n", channel);
		break;
	case 4:  // Label (Title)
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:LABEL:DATA '%s';*WAI\n", channel, label);
		break;
	case 5: case 6://Suffix 
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:SUFFIX:DATA '%s';*WAI\n",channel, label);
		break;
	case 7: case 8: // Start
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:START %lf;*WAI\n", channel, lbl_value);
		break;
	case 9: case 10: //Stop
		errStatus = viPrintf(vi, "DISP:ANN:FREQ%i:USER:STOP %lf;*WAI\n", channel, lbl_value);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_extensions
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets/reads port extensions state and values.
 *			 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. See code for choices
 *
 * PARAM 3 : ViReal64 value. OPTIONAL Contains port extension value in seconds
 *
 * PARAM 4 : ViPReal64 cur_value.  OPTIONAL  Returns status (1=ON, 0=OFF) 
 * OUT       of requested parameter or returns value of requested parameter.     
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_extensions( 
        ViSession vi, 
		ViString request,
		ViReal64 value,
		ViPReal64 cur_extension)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
char selection[40];
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_extensions");

const ViInt32 size = 14;
ViString req[size]= {"?", "STATUS?", "ON", "OFF", "REFLECTION", "REFL",  "REFLECTION?", "REFL?",
					 "TRANS", "TRANSMISSION",	"TRANS?", "TRANSMISSION?", "VELOCITY", "VELOCITY?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0: case 1:
		if ((errStatus = viPrintf(vi, "SENS:CORR:EXT:STAT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_extension);
		break;
	case 2: case 3: //ON/OFF
		errStatus = viPrintf(vi, "SENS:CORR:EXT:STAT %s;*WAI\n", selection);
		break;
	case 4: case 5://REFL
		errStatus = viPrintf(vi, "SENS:CORR:EXT:REFL:TIME %.12lf;*WAI\n", value);
		break;
	case 6: case 7: //REFL?
		if ((errStatus = viPrintf(vi, "SENS:CORR:EXT:REFL:TIME?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_extension);
		break;
	case 8: case 9://
		errStatus = viPrintf(vi, "SENS:CORR:EXT:TRAN:TIME %.12lf;*WAI\n", value);
		break;
	case 10: case 11:
		if ((errStatus = viPrintf(vi, "SENS:CORR:EXT:TRAN:TIME?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_extension);
		break;
	case 12: // Rel Velocity
		errStatus = viPrintf(vi, "SENS:CORR:RVEL:COAX %lf;*WAI\n", value);
		break;
	case 13: //Rel Velocity?:
		if ((errStatus = viPrintf(vi, "SENS:CORR:RVEL:COAX?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_extension);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_faultSetup
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets/reads various fault location parameters.
 *			 See also faultCal and faultMeas
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  See code for choices
 * IN
 *
 * PARAM 3 : ViInt32 channel.  OPTIONAL; default=1
 * IN
 *
 * PARAM 4 : ViPString cur_fltSetup.  OPTIONAL  
 * OUT       Returns status of requested parameter     
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Fault Location requires Opt 100.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_faultSetup( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPString cur_fltSetup)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, stat=0;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_faultSetup");

const ViInt32 size = 14;
ViString req[size]= {"FEET", "METERS", "METRES", "MIN", "MINIMUM", "MEDIUM", "MED",
					  "MAXIMUM", "MAX", "LOWPASS", "BANDPASS", "UNITS?", "WINDOW?", "MODE?"  
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	case 0: //FEET
		errStatus = viPrintf(vi, "SENS%i:DIST:UNITS FEET;*WAI\n", channel);
		break;
	case 1: case 2://Meters
		errStatus = viPrintf(vi, "SENS%i:DIST:UNITS METERS;*WAI\n", channel);
		break;
	case 3: case 4: //Window Min
		errStatus = viPrintf(vi, "SENS%i:WIND:TYPE RECT;*WAI\n", channel);
		break;
	case 5: case 6: //Window Med
		errStatus = viPrintf(vi, "SENS%i:WIND:TYPE HAMM;*WAI\n", channel);
		break;
	case 7: case 8: //Window Max
		errStatus = viPrintf(vi, "SENS%i:WIND:TYPE KBES;*WAI\n", channel);
		break;
	case 9: //Mode Lowpass
		errStatus = viPrintf(vi, "SENS%i:FREQ:MODE LOWP;*WAI\n", channel);
		break;
	case 10: //Mode Bandpass
		errStatus = viPrintf(vi, "SENS%i:FREQ:MODE CENT;*WAI\n", channel);
		break;
	case 11: //Units?
		if ((errStatus = viPrintf(vi, "SENS%i:DIST:UNIT?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", &stat);
		strcpy(cur_fltSetup, "METERS");
		if (stat) strcpy(cur_fltSetup, "FEET");
		break;
	case 12: //Window?
		if ((errStatus = viPrintf(vi, "SENS%i:WIND:TYPE?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", &stat);
		strcpy(cur_fltSetup, "MINIMUM");
		if (stat==1) strcpy(cur_fltSetup, "MEDIUM");
		if (stat==2) strcpy(cur_fltSetup, "MAXIMUM");
		break;
	case 13: //Mode?
		if ((errStatus = viPrintf(vi, "SENS%i:FREQ:MODE?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", &stat);
		strcpy(cur_fltSetup, "LOWPASS");
		if (stat) strcpy(cur_fltSetup, "BANDPASS");
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_faultMeas
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets/reads various fault stimulus parameters.
 *			 See also faultCal and faultSetup
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. See code for choices
 * IN
 *
 * PARAM 3 : ViReal64 fltMeas_value.  Contains data for request
 * IN
 *
 * PARAM 4 : ViInt32 channel. OPTIONAL; default=1
 * IN
 *
 * PARAM 5 : ViPReal64 cur_fltMeas.  OPTIONAL  
 * OUT       Returns value of requested parameter     
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Fault Location requires Opt 100.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_faultMeas( 
        ViSession vi, 
		ViString request,
		ViReal64 fltMeas_value,
		ViInt32 channel,
		ViPReal64 cur_fltMeas)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_faultMeas");

const ViInt32 size = 8;
ViString req[size]= {"START", "STOP", "CENTER", "MAXSPAN", "START?", "STOP?", 
					 "CENTER?", "MAXSPAN?" 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);


switch (choice)
	{
	case 0: //START
		errStatus = viPrintf(vi, "SENS%i:DIST:STAR %lf;*WAI\n", channel, fltMeas_value);
		break;
	case 1: //STOP
		errStatus = viPrintf(vi, "SENS%i:DIST:STOP %lf;*WAI\n", channel, fltMeas_value);
		break;
	case 2: //CENTER
		errStatus = viPrintf(vi, "SENS%i:FREQ:CENT %lf;*WAI\n", channel, fltMeas_value);
		break;
	case 3: //MAXSPAN
		errStatus = viPrintf(vi, "SENS%i:FREQ:MODE CENT;:SENS%i:FREQ:SPAN:MAX %lf;*WAI\n", channel, channel, fltMeas_value);
		break;
	case 4: //Start?
		if ((errStatus = viPrintf(vi, "SENS%i:DIST:STAR?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltMeas);
		break;
	case 5: //Stop?
		if ((errStatus = viPrintf(vi, "SENS%i:DIST:STOP?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltMeas);
		break;
	case 6: //Center?
		if ((errStatus = viPrintf(vi, "SENS%i:FREQ:CENT?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltMeas);
		break;
	case 7://MaxSpan?
		if ((errStatus = viPrintf(vi, "SENS%i:FREQ:SPAN:MAX?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltMeas);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_faultCal
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets/reads various fault Calibration parameters.
 *			 See also faultMeas and faultSetup
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. See code for choices
 * IN
 *
 * PARAM 3 : ViReal64 fltCal_value.  Contains data for request
 * IN
 *
 * PARAM 4 : ViInt32 channel.  OPTIONAL; default=1
 * IN 
 *
 * PARAM 5 : ViPReal64 cur_fltCal.  OPTIONAL  
 * OUT       Returns value of requested parameter     
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * Note:   Connector length must always be in Meters; not Feet!           
 * LIMITATIONS: Fault Location requires Opt 100.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_faultCal( 
        ViSession vi, 
		ViString request,
		ViReal64 fltCal_value,
		ViInt32 channel,
		ViPReal64 cur_fltCal)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_faultCal");

const ViInt32 size = 13;
ViString req[size]= {"VELOCITY", "VELOCITY?","LOSS", "LOSS?", "CAL_LENGTH", "CAL_LENGTH?", 
					 "MEASURE",	"MULTIPEAK", "MULTIPEAK?", "THRESHOLD", "THRESHOLD?",
					 "CONN_LENGTH", "CONN_LENGTH?" 				   
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	
	case 0: // Rel Velocity
		errStatus = viPrintf(vi, "SENS:CORR:RVEL:COAX %lf;*WAI\n", fltCal_value);
		break;
	case 1: //Rel Velocity?:
		if ((errStatus = viPrintf(vi, "SENS:CORR:RVEL:COAX?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltCal);
		break;
	case 2: // Loss
		errStatus = viPrintf(vi, "SENS%i:CORR:LOSS:COAX %lf;*WAI\n", channel, fltCal_value);
		break;
	case 3: //Loss?:
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:LOSS:COAX?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltCal);
		break;
	case 4: // Length
		errStatus = viPrintf(vi, "SENS%i:CORR:LENG:COAX %lf;*WAI\n", channel, fltCal_value);
		break;
	case 5: // Length?:
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:LENG:COAX?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltCal);
		break;
	case 6: // Measure  Watch out for Timeouts!
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:RVEL:IMM", channel);
		break;
	case 7: // Multipeak
		errStatus = viPrintf(vi, "SENS%i:CORR:PEAK:COAX:STAT %lf;*WAI\n", channel, fltCal_value);
		break;
	case 8: // Multipeak?
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:PEAK:COAX:STAT?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltCal);
		break;
	case 9: // Threshold
		errStatus = viPrintf(vi, "SENS%i:CORR:THR:COAX %lf;*WAI\n", channel, fltCal_value);
		break;
	case 10: // Threshold?
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:THR:COAX?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltCal);
		break;
	case 11: // Conn Length
		errStatus = viPrintf(vi, "SENS%i:CORR:LENG:CONN %lf;*WAI\n", channel, fltCal_value);
		break;
	case 12: // Conn Length?
		if ((errStatus = viPrintf(vi, "SENS%i:CORR:LENG:CONN?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_fltCal);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_traceWrite
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : This function writes (puts) trace or calibration data to the
 *           analyzer 
 *
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 * 
 * PARAM 2 : ViReal64 _VI_FAR trace[] trace.
 * OUT       64 bit Real array that contains the data to be written.
 *           
 * PARAM 3 : ViString request. OPTIONAL; default=FDATA (Formatted data)
 * IN        Selects type of data array to be written; see choices in code below.
 * 
 * PARAM 4 : ViInt32 channel. OPTIONAL; default=1
 * IN 
 *
 * PARAM 5 : ViReal64 _VI_FAR trace[] trace2.
 * OUT       64 bit Real array that contains either the imaginary or phase data
 *			 to be written in those cases that require two arrays.
 * 
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */

 ViStatus _VI_FUNC hp871x_traceWrite( 
        ViSession vi, 
		ViReal64 _VI_FAR trace[],
		ViString request,		
		ViInt32 channel,
		ViReal64 _VI_FAR trace2[])
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32  dimension, choice, index, points, cmdbytes;
const ViInt32 dummy =0;
char format[11], digits[10], header[10], output[12900];
ViInt32   ArrSize;
ViUInt32  cnt;
ViReal32 trace_temp[3202];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_traceWrite");

const ViInt32 size = 19;
ViString req[size]= {"FDATA", "FMEM", "R&I", "R&I_MEM", "A_RAW", "B_RAW", "R_RAW",
					 "CORR1", "CORR2", "CORR3", "CORR4","CORR5", "CORR6", "CORR7", 
					 "CORR8", "CORR9", "CORR10", "CORR11", "CORR12"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

//errStatus = viPrintf(vi, "*cls\n");

//Find # of Points
if ((errStatus = hp871x_points(vi, dummy, "?", channel, &points)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

//Read format
if ((errStatus = hp871x_format(vi, "?", channel, format)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

dimension = 1;
if ((!strcmp(format, "POLAR")) || (!strcmp(format, "SMITH")) || (choice>1))
    dimension =2;
 
if ((dimension == 2) && (trace2==0))// 2nd array not passed
	return statusUpdate(vi, thisPtr, hp871x_MEAS_CONFLICT_ERROR);

if ((errStatus = viPrintf(vi, "FORM:BORD SWAP;:FORM:DATA REAL,32;*WAI\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

switch (choice)
	{ 
	case 0://Formatted Data
		sprintf(output, "TRAC:DATA CH%iFDATA, ", channel);
		break;
	case 1://Formatted Memory
		sprintf(output, "TRAC:DATA CH%iFMEM,", channel);
		break;
	case 2://Unformatted Data
		sprintf(output, "TRAC:DATA CH%iSDATA, ", channel);
		break;
	case 3://Unformatted Memory
		sprintf(output, "TRAC:DATA CH%iSMEM, ", channel);
		break;
	case 4://Raw A
		sprintf(output, "TRAC:DATA CH%iAFWD, ", channel);
		break;
	case 5://Raw B
		sprintf(output, "TRAC:DATA CH%iBFWD, ", channel);
		break;
	case 6://Raw R
		sprintf(output, "TRAC:DATA CH%iRFWD, ", channel);
		break;
	case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18://CORR 1-12
		sprintf(output, "TRAC:DATA CH%iS%s,", channel, req[choice]);
		break;
	}	

if (dimension ==1)
	{
	ArrSize= points*4; //1 dim Real32
	for (index=0;  index<points ;index++)   // loop through data points
		 trace_temp[index] = (float)trace[index];
	}
else
	{
	if (choice<2) // Formatted; Convert to R&I
		MagPhase_to_RI(points, trace, trace2);
	ArrSize= points*8; //2 dim Real32
	for (index=0;  index<points; index++) 
		{
		 trace_temp[2*index] = (float)trace[index];
		 trace_temp[2*index+1] = (float)trace2[index];
		}
	}
sprintf(digits, "%i", ArrSize);
sprintf(header , "#%i%s",strlen(digits),digits);
strcat(output,header);
cmdbytes = strlen(output);
memcpy(output+cmdbytes, trace_temp, (size_t)ArrSize);
memcpy(output+cmdbytes+ArrSize, "\r\n", 2);//Adds CR/LF
//Write Trace Data
if ((errStatus = viWrite(vi, (ViPBuf)output, ArrSize + cmdbytes + 2, &cnt)) < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
     
if (cnt != (unsigned)(ArrSize + cmdbytes + 2))
		return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR);

return statusUpdate(vi, thisPtr, VI_SUCCESS);
}          /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_multiport
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets/reads ports on multiport test set.  Also sets and reads various 
 *			 multiport parameters. 
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. See code below for choices
 *
 * PARAM 3 : ViInt32 mp1. OPTIONAL; Default= 1.  Typically, this is the Refl port 
 *			 setting.  May also contain selfcal status or selfcal timer value in minutes.
 *
 * PARAM 4 : ViInt32 mp2. OPTIONAL; Default= 2.  This is the Trans port setting 
 *
 * PARAM 5 : ViInt32 channel. OPTIONAL; Default=1
 * IN        
 * 
 * PARAM 6 : ViPInt32 cur_mp1. OPTIONAL  Returns value of requested parameter
 * OUT		 Status, timer value in minutes, or REFL port number.
 *
 * PARAM 7 : ViPInt32 cur_mp2. OPTIONAL  Returns TRANS port number
 * OUT		 
 *            
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *
 * LIMITATIONS: Requires 871xC with firmware rev C.04.51 or above to function.
 *              Timer value is integer value in minutes! 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_multiport( 
        ViSession vi, 
		ViString request,
		ViInt32 mp1,
		ViInt32 mp2,
		ViInt32 channel,
		ViPInt32 cur_mp1,
		ViPInt32 cur_mp2)
		
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
ViReal64 timer;
char selection[40];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_multiport");

const ViInt32 size = 15;
ViString req[size]= {"SELFCAL_ON", "SELFCAL_OFF", "SELFCAL?", "ONCE", "CAL_ALL", 
					"PORTS", "PORT", "PORTS?", "PORT?", "TIMER", "TIMER?", "ON", 
					"OFF", "STATUS?","MAXPORTS?"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0: //SelfCal ON
		errStatus = hp871x_outputf(vi, 2, "CAL:SELF ON");
		break;
	case 1: //SelfCal OFF
		errStatus = hp871x_outputf(vi, 2, "CAL:SELF OFF");
		break;
	case 2: //SelfCal?
		if ((errStatus = viPrintf(vi, "CAL:SELF?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_mp1);
		break;
	case 3: //SelfCal ONCE; disables auto SelfCal
		errStatus = hp871x_outputf(vi, 2, "CAL:SELF ONCE");
		break;
	case 4: //Cal All
		errStatus = hp871x_outputf(vi, 2, "CAL:SELF:ALL");
		break;
	case 5: case 6:// Ports
		errStatus = hp871x_outputf(vi, 2, "ROUT%i:PATH:DEF:PORT %i,%i", channel, mp1, mp2);
		break;
	case 7: case 8:// Ports?
		if ((errStatus = viPrintf(vi, "ROUT%i:PATH:DEF:PORT?\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i,%i\n", cur_mp1, cur_mp2);
		break;
	case 9: //Timer  (in minutes)
		errStatus = viPrintf(vi, "CAL:SELF:TIMER %i;*WAI\n", mp1);
		break;
	case 10: //Timer? (in minutes)
		if ((errStatus = viPrintf(vi, "CAL:SELF:TIMER?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", &timer);
		*cur_mp1= (int)timer;
		break;
	case 11: case 12: // State On/Off
		errStatus = viPrintf(vi, "CONT:MULT:STAT %s;*WAI\n", selection);
		break;
	case 13: // Status?
		if ((errStatus = viPrintf(vi, "CONT:MULT:STAT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_mp1);
		break;
	case 14: // MaxPorts?
		if ((errStatus = viPrintf(vi, "DIAG:MED:EEPR:PORT:COUN?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_mp1);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_print
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets various printer related parameters.
 *			 Also prints
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. OPTIONAL, Default=PRINT. See code for choices
 * IN
 *
 * PARAM 3 : ViInt32 data.  OPTIONAL  Contains data for request; see code
 * IN
 * 
 * PARAM 4 : ViPString cur_print.  OPTIONAL  
 * OUT       Returns current Language or Port selection     
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * Note   :  If DESTINATION is selected, the data string MUST have TWO components
 *           separated by a comma.  First MUST be the language; second is the port.
 *           Only certain combinations are valid; no error checking is done!
 *           Example: ...print(vi, "DEST", "PCL5,LAN")
 *           
 * LIMITATIONS: LAN, PCL5 and some other choices, require 871xC.
 *----------------------------------------------------------------------------*/
 
ViStatus _VI_FUNC hp871x_print( 
        ViSession vi, 
		ViString request,
		ViString data,
		ViPString cur_print)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, stat=0, idx=0, sel=0, dummy=0;
char cur_lang[10], lang[10], port[10];
char ptr_dev[]="1", dmy_string[15];
ViReal64 rev_value;


GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_print");

const ViInt32 size = 16;
ViString req[size]= {"PRINT","ADDR", "ADDRESS", "DESTINATION", "DEST", "LANG?", 
					 "LANGUAGE?", "PORT?", "ABORT", "COLOR", "ORIENTATION", 
					 "MODE", "RESOLUTION", "RES", "FORMFEED", "FF" 
					};

const ViInt32 sz = 19;
ViString dat[sz]= {  "ON", "OFF", "NORM", "NORMAL", "GRAPH", "MARKER",
					 "LIST", "ISET", "PORTRAIT", "LANDSCAPE", "LAND", 
					 "75", "90", "96", "100", "150", "180", "300", "600"
	 				};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

data = _strupr(data);

if (choice>8)  //read port and lang and check data string for match
{
	ViString lang[5]={"PCX", "PCL", "HPGL", "PCL5", "EPS"};
	if ((errStatus = viPrintf(vi, "HCOP:DEV:LANG?\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = delayVScanf(vi, "%s\n", cur_lang)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if (!strcmp(cur_lang, "HPGL"))  strcpy(ptr_dev,"2");
	if (!strcmp(cur_lang, "PCL5"))  strcpy(ptr_dev,"3");
	if (!strcmp(cur_lang, "PCX"))  strcpy(ptr_dev,"\0");	

	if(getChoice(vi,data,sz,dat,&idx)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
}

switch (choice)
	{
	case 0: //Print NOW! 
		errStatus = viPrintf(vi, "HCOP:IMM;*WAI\n");
		break;
	case 1: case 2://address
		if (strlen(data) < 4) //assume HPIB address
			errStatus = viPrintf(vi, "SYST:COMM:GPIB:HCOP:ADDR %s;*WAI\n", data);
		else
			errStatus = viPrintf(vi, "SYST:COMM:LAN:PRIN:HOST '%s';*WAI\n", data);
		break;
	case 3: case 4://DESTINATION
		errStatus = hp871x_stringParse(vi, data, lang, &dummy);
		errStatus = hp871x_stringParse(vi, data, port, &dummy);
		if (!strcmp(port, "HPIB")) 	strcpy(port,"GPIB");
		if (!strcmp(port, "DISK")) 	strcpy(port,"MMEM");
		if (!strcmp(port, "NONVOL")) strcpy(port,"NVR");
		if (!strcmp(port, "PARALLEL")) 	strcpy(port,"CENT");
		errStatus = viPrintf(vi, "HCOP:DEV:LANG %s;PORT %s;*WAI\n", lang,port);
		break;
	case 5: case 6: // Read Language
		if ((errStatus = viPrintf(vi, "HCOP:DEV:LANG?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", cur_print);
		break;
	case 7: // Read Port
		if ((errStatus = viPrintf(vi, "HCOP:DEV:PORT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", cur_print);
		if (!strcmp(cur_print, "MMEM")) strcpy(cur_print,"DISK");
		if (!strcmp(cur_print, "NVR"))  strcpy(cur_print,"NONVOL");
		if (!strcmp(cur_print, "GPIB")) strcpy(cur_print,"HPIB");
		if (!strcmp(cur_print, "CENT")) strcpy(cur_print,"PARALLEL");
		if (!strcmp(cur_print, "SER")) 	strcpy(cur_print,"SERIAL");
		break;
	case 8: //Abort 
		errStatus = viPrintf(vi, "HCOP:ABORT;*WAI\n");
		break;
	case 9: //Color 
		errStatus = viPrintf(vi, "HCOP:DEV%s:COL %s;*WAI\n",ptr_dev, data);
		break;
	case 10:  //Orientation 
		if ((errStatus = hp871x_readID(vi, dmy_string, "REV_VALUE?",&rev_value)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus); 
		if (rev_value <4) //8711A or 871xB
			errStatus = viPrintf(vi, "HCOP:PAGE:ORI %s;*WAI\n", data);
		else
			errStatus = viPrintf(vi, "HCOP:DEV%s:PAGE:ORI %s;*WAI\n",ptr_dev, data);
		break;
	case 11:  //Mode
		if ((!strcmp(data, "NORMAL")) || (!strcmp(data, "NORM")))
			strcpy(data,"GMAR");
		errStatus = viPrintf(vi, "HCOP:DEV%s:MODE %s;*WAI\n",ptr_dev, data);
		break;
	case 12: case 13://Resolution 
		errStatus = viPrintf(vi, "HCOP:DEV%s:RES %s;*WAI\n",ptr_dev, data);
		break;
	case 14: case 15://FormFeed 
		errStatus = viPrintf(vi, "HCOP:ITEM%s:FFE:STAT %s;*WAI\n",ptr_dev, data);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}    
    /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_limits
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets various limit line parameters. To set actual limits see limitSet.
 *			 Reads pass/fail results from limit test.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. See code for choices
 * IN
 *
 * PARAM 3 : ViInt32 channel. OPTIONAL; default=1
 * IN        
 *
 * PARAM 4 : ViPInt32 limit_status. OPTIONAL. Contains limit test data (see note below)
 * OUT		 or current test on/off status.
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *
 * Note:     When testing limit condition (Pass/Fail), Returns 0 if both channels
 *			 pass, 1 if ch1 fails, 2 if ch2 fails and 3 if both fail. 
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_limits( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPInt32 limit_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
ViUInt16  res;
ViString type[2]= {"LMIN", "LMAX"};
 
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_limits");

const ViInt32 size = 14;
ViString req[size]= {"LIMITS_OFF", "LIMITS_ON", "STATUS?", "TEST?", "DISPLAY_ON", 
					"DISPLAY_OFF", "TEXT_ON", "TEXT_OFF", "ICON_ON", "ICON_OFF",  
					"FAIL?", "RESULT?", "RESULTS?", "DELETE"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

switch (choice)
	{
	case 0: // Limits Off
		errStatus = viPrintf(vi, "CALC%i:LIM:STAT OFF;*WAI\n", channel);
		break;
	case 1: // Limits On
		errStatus = viPrintf(vi, "CALC%i:LIM:STAT ON;*WAI\n", channel);
		break;
	case 2: case 3:// status?
		if ((errStatus = viPrintf(vi, "CALC%i:LIM:STAT?\n",channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", limit_status);
		break;
	case 4: //Display On
		errStatus = viPrintf(vi, "CALC%i:LIM:DISP ON;*WAI\n", channel);
		break;
	case 5: //Display Off
		errStatus = viPrintf(vi, "CALC%i:LIM:DISP OFF;*WAI\n", channel);
		break;
	case 6: //Text on
		errStatus = viPrintf(vi, "DISP:ANN:LIM:ICON%i:TEXT ON;*WAI\n", channel);
		break;
	case 7: //Text off
		errStatus = viPrintf(vi, "DISP:ANN:LIM:ICON%i:TEXT OFF;*WAI\n", channel);
		break;
	case 8: //Icon On
		errStatus = viPrintf(vi, "DISP:ANN:LIM:ICON%i:FLAG ON;*WAI\n", channel);
		break;
	case 9: //Icon Off
		errStatus = viPrintf(vi, "DISP:ANN:LIM:ICON%i:FLAG OFF;*WAI\n", channel);
		break;
	case 10: case 11: case 12: //Read Results
		if ((errStatus = viPrintf(vi, "STAT:QUES:LIM:COND?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", &res);
		*limit_status = res & 3; //And w/mask to only look at ch1 and ch2 condition
		break;
	case 13:// Delete
		errStatus = viPrintf(vi, "CALC%i:LIM:SEGM:AOFF;*WAI\n",channel);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_limitSet
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets actual limits lines or points, and displays them.
 *			 
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViInt32 segments.  Number of segments to be set (1 to 12)
 *
 * PARAM 3 : ViReal64 _VI_FAR limits[].  64 bit Real one-dimensional array for limits. 
 * IN        [1-12 segments; 5 input values per segment]
 *           FORMAT:  [ 0|1, Xstart, Xstop, Ystart, Ystop ]  where 0/1 is
 *           0 for MIN Limit and 1 = MAX Limit.  Repeated X number of times
 *           where X equals the number of segments. If Xstop = 0 then assumes a
 *			 a point limit, in which case, Ystop is also ignored
 * 
 * PARAM 4 : ViInt32 channel OPTIONAL; default=1
 * IN        
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_limitSet( 
        ViSession vi, 
		ViInt32 segments,
		ViReal64 _VI_FAR limits[],
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 seg, elem, limnum, pointlimit;
ViReal64 pwr_swp, dummy=0;
ViString l_type[2]= {"LMIN", "LMAX"};
ViString p_type[2]= {"PMIN", "PMAX"};
char limtype[5], meas[14];
char func[10]= "FREQ";
 
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_limitSet");

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

//First, erase any existing lines
if ((errStatus = viPrintf(vi, "CALC%i:LIM:SEGM:AOFF;*WAI\n",channel)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

//Get sweep mode
if ((errStatus = hp871x_powerSweep(vi, "?",0, 0,channel, &pwr_swp, &dummy)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
if (pwr_swp == 1)  strcpy(func,"POW");
if ((errStatus = hp871x_measure(vi, "?",channel, meas)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
if (!strcmp(meas, "FAULT")) strcpy(func,"DIST");
	
for (seg=1;seg<=segments;seg++)  
	{
	elem = seg-1;
	limnum= (int) limits[elem*5];
	pointlimit= 0;
	if (limits[elem*5 +2] == 0) //then stop=0; use point limit
		{strcpy(limtype, p_type[limnum]);
		 pointlimit=1;
		}
	else
		strcpy(limtype, l_type[limnum]);
	
	if ((errStatus = viPrintf(vi, "CALC%i:LIM:SEGM%i:TYPE %s\n",channel, seg, limtype)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);

	if ((errStatus = viPrintf(vi, "CALC%i:LIM:SEGM%i:%s:STAR %lf\n",channel, seg, func, limits[elem*5+1])) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if (!pointlimit)
		if ((errStatus = viPrintf(vi, "CALC%i:LIM:SEGM%i:%s:STOP %lf\n",channel, seg, func, limits[elem*5+2])) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = viPrintf(vi, "CALC%i:LIM:SEGM%i:AMPL:STAR %lf\n",channel, seg, limits[elem*5+3])) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if (!pointlimit)
		if ((errStatus = viPrintf(vi, "CALC%i:LIM:SEGM%i:AMPL:STOP %lf\n",channel, seg, limits[elem*5+4])) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	}
//Turn on display of limit lines
if ((errStatus = viPrintf(vi, "CALC%i:LIM:DISP ON;*WAI\n", channel)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_softkeyBegin
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets User Begin Softkeys #1 through 7; One-at-a-time or all at once  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString key. OPTIONAL.  Contains individual key label (20 chr max), 
 * IN		 or all keys separated by "|".  If not specified; erases all softkeys.
 *
 * PARAM 3 : ViInt32 key_number.  (OPTIONAL)  Softkey number if setting only one   
 * IN        softkey label 
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Only 7 softkeys are available!
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_softkeyBegin( 
        ViSession vi, 
		ViString key,
		ViInt32 key_number)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

char parse[256];
ViInt32 not_done, index = 0;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_softkeyBegin");

switch (key_number)
	{
	case 0: // Erase All or Do all Softkeys
	if (!strcmp(key, "ERASE_SOFTKEYS"))
	  	{
		for (index = 1; index<=7; index++)
			errStatus = viPrintf(vi, "DISP:MENU2:KEY%i '';*WAI\n",index);
		break;
		}
	else
		{
		do
			{ 
			errStatus = hp871x_stringParse(vi, key, parse, &not_done,"|");
			index++;
			if (!(strlen(parse) ==0))
				errStatus = viPrintf(vi, "DISP:MENU2:KEY%i '%s';*WAI\n",index, parse);
			}
			while (not_done);
		break;
		}
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: // Do one softkey only
		errStatus = viPrintf(vi, "DISP:MENU2:KEY%i '%s';*WAI\n", key_number, key);
		break;
	default:
		return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR);
		break;
	}
	
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_dataport
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Write/Reads to/from Parallel/Serial/user/limit ports
 *           Also reads Centronics Status lines.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViInt32 port_data.  1 or 8-bit data to write; depending upon port
 * IN
 *
 * PARAM 3 : ViString request.  Selects desired Port.  "?" reads
 * IN       
 *			 
 * PARAM 4 : ViPInt32 cur_data. (OPTIONAL) Data read from analyzer
 * OUT         
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_dataPorts( 
        ViSession vi,
		ViInt32 port_data,
		ViString request,
		ViPInt32 cur_data)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_dataPorts");
ViInt32 choice;

const ViInt32 size = 11;
ViString req[size]= {"CENTRONICS",  "PARALLEL",  "SERIAL",  "USER",  "LIMIT",  
					 "CENTRONICS?", "PARALLEL?", "SERIAL?", "USER?", "LIMIT?",
					 "STATUS?"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0: case 1://Parallel 
	   	errStatus = viPrintf(vi, "DIAG:PORT:WRITE 15,3, %i;*WAI\n", port_data);
		break;
	case 2: //Serial
		errStatus = viPrintf(vi, "DIAG:PORT:WRITE 9,0, %i;*WAI\n", port_data);
		break;
	case 3: //USER
		errStatus = viPrintf(vi, "DIAG:PORT:WRITE 15,1, %i;*WAI\n", port_data);
		break;
	case 4: //Limit
		errStatus = viPrintf(vi, "DIAG:PORT:WRITE 15,2, %i;*WAI\n", port_data);
		break;

//Read Ports
	case 5: case 6://Parallel 
	   	if ((errStatus = viPrintf(vi, "DIAG:PORT:READ? 15,0\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_data);
		break;
	case 7: //Serial?
	   	if ((errStatus = viPrintf(vi, "DIAG:PORT:READ? 9,0\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_data);
		break;
	case 8: //USER
	   	if ((errStatus = viPrintf(vi, "DIAG:PORT:READ? 15,1\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_data);
		break;
	case 9: //Limit
	   	if ((errStatus = viPrintf(vi, "DIAG:PORT:READ? 15,2\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_data);
		break;	
	case 10: //Status of Parallel port 
	   	if ((errStatus = viPrintf(vi, "DIAG:PORT:READ? 15,10\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", cur_data);
		break;
	}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_beep
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Produces beep on analyzer using various tones.  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. OPTIONAL; Default= Default
 * IN		 See list below for selections
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_beep( 
        ViSession vi, 
		ViString request)
{

struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, index;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_beep");

const ViInt32 size = 8;
ViString req[size]= {"DEFAULT", "PROMPT", "DOUBLE", "ERROR", "FATAL",
					 "CHIRP", "OK", "ALERT"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0: 
		errStatus = viPrintf(vi, "SYST:BEEP;*WAI\n");
		break;
	case 1: //Prompt
		errStatus = viPrintf(vi, "SYST:BEEP 300,.1;*WAI\n");
		break;
	case 2: //Double
		errStatus = viPrintf(vi, "SYST:BEEP 600,.1;*WAI\n");
		Sleep(150);
		errStatus = viPrintf(vi, "SYST:BEEP 600,.1;*WAI\n");
		break;
	case 3://Error
		errStatus = viPrintf(vi, "SYST:BEEP 2000,.1;*WAI\n");
		break;
	case 4://Fatal
		errStatus = viPrintf(vi, "SYST:BEEP 1900,.5;*WAI\n");
		break;
	case 5://chirp
		errStatus = viPrintf(vi, "SYST:BEEP 2100,.01;*WAI\n");
		break;
	case 6: //OK
		errStatus = viPrintf(vi, "SYST:BEEP 1800,.1;*WAI\n");
		Sleep(50);
		errStatus = viPrintf(vi, "SYST:BEEP 300,.1;*WAI\n");
		break;
	case 7:// Alert
		for (index=0;  index<4; index++) 
			{	
			errStatus = viPrintf(vi, "SYST:BEEP 1850,.08;*WAI\n");
			Sleep(150);
			}
		break;
}

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : int getChoice
 *-----------------------------------------------------------------------------
 * PURPOSE : Finds match for request in array: arr.  
 *            
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 * PARAM 2 : ViString request.  String to be searched for
 * IN		  
 * PARAM 3 : ViInt32 size.  Total # of possible choices (# of array elements)
 * IN        
 * PARAM 4 : ViString arr[].  String Array of all possible choices
 * IN        
 * PARAM 5 : ViPInt32 choice.  Returns choice number (position in array)
 * OUT        
 * 
 * RETURN  : O if request is found within array of choices;  1 if not found.
 *-----------------------------------------------------------------------------
 */

int getChoice(
       ViSession vi, 
	   ViString request,
	   ViInt32 size,
	   ViString arr[],
	   ViPInt32 choice)
{			   
ViInt32 index = 0; 
ViChar message[hp871x_ERR_MSG_LENGTH];
ViChar req[80];
struct hp871x_globals *thisPtr;

ViStatus errStatus;
GET_GLOBALS(vi, thisPtr)

strcpy(req,request);
_strupr(req);
if (req[0]=='\"')  
	strcpy(req, req+1);  // remove first quote if any
if (req[strlen(req)-1] == '\"')  
	req[strlen(req)-1] = '\0'; // overwrite last quote if any

while (strcmp(req, arr[index]))
{
	index++;
	if (index==size)
	{
	   sprintf(message, "Request=`%s';  Function=%s", req, thisPtr->funcName);
	   strcpy(thisPtr->errMessage, message);
	   return 1;
	}
}
*choice= index;

return 0;
}			 /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : int checkChannel
 *-----------------------------------------------------------------------------
 * PURPOSE : Checks channel number for valid input.  Must equal 1 or 2 only.  
 *            
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 * PARAM 2 : ViInt32 channel.  Channel number to be tested
 * IN
 * RETURNS : 0 if channel= 1 or 2; 1 if not
 *-----------------------------------------------------------------------------
 */

int checkChannel(
       ViSession vi, 
	   ViInt32 channel)
{			   

ViChar message[hp871x_ERR_MSG_LENGTH];

struct hp871x_globals *thisPtr;
ViStatus errStatus;
GET_GLOBALS(vi, thisPtr)

if((channel !=1) && (channel !=2)) 
	{
	   sprintf(message, "Ch requested= %i; Function= %s", channel, thisPtr->funcName);
	   strcpy(thisPtr->errMessage, message);
	   return 1;
	}
return 0;
}			 /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_memory
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Performs various mass storage functions and housekeeping.  
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString request.  See code below for choices
 * IN		 
 *            
 * PARAM 3 : ViString name.  OPTIONAL  Contains file name or directory name to 
 * IN		 be operated on.
 *
 * PARAM 4 : ViString dest.  OPTIONAL  Contains the destination filename
 * IN		 for move or copy. 
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Some functions take a while. Use long timeouts, especially for floppy.  
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_memory( 
        ViSession vi, 
		ViString request,
		ViString name,
		ViString dest)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, errnum=0;
const int numchars = 2;           // number of characters in header (#0)
const ViUInt32 max_sz = 1500000;  // Enough for 1 full floppy plus some
ViUInt32 index, retCount;
char header[numchars], *file_buf;
FILE *file_ptr;
//char errmsg[250];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_memory");

const ViInt32 size = 19;
ViString req[size]= {"CD", "COPY", "DEL", "DELETE", "INIT_MEM", "INIT_DISK",
					 "MKDIR", "RMDIR",  "RENAME", "MOVE", "CD..", "UP",
					 "RAM", "NONVOL", "MEM", "DISK", "INT", "TO_RFNA", "FROM_RFNA"
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if ((errStatus = viPrintf(vi, "*CLS\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

switch (choice)
	{
	case 0://Change Dir 
		errStatus = hp871x_outputf(vi, 2,  "MMEM:CDIR '%s'", name);
		break;
	case 1: //Copy
		errStatus = hp871x_outputf(vi, 2,  "MMEM:COPY '%s','%s'", name, dest);
		break;
	case 2: case 3:// Delete
		errStatus = hp871x_outputf(vi, 2, "MMEM:DEL '%s'", name);
		break;
	case 4://Initialize MEM 
		errStatus = hp871x_outputf(vi, 2, "MMEM:INIT 'MEM:'");
		break;
	case 5://Initialize Disk 
		errStatus = hp871x_outputf(vi, 2, "MMEM:INIT 'INT:'");
		Sleep(5000);// requires 140 seconds!
		break;
	case 6://Make Dir
		errStatus = hp871x_outputf(vi, 2, "MMEM:MDIR '%s'", name);
		break;
	case 7://Remove Dir
		errStatus = hp871x_outputf(vi, 2,  "MMEM:RDIR '%s'", name);
		break;
	case 8: case 9://MOVE
		errStatus = hp871x_outputf(vi, 2,  "MMEM:MOVE '%s','%s'", name, dest);
		break;
	case 10: case 11://Change Dir up one 
		errStatus = hp871x_outputf(vi, 2,  "MMEM:CDIR '..'");
		break;
	case 12://RAM
		errStatus = hp871x_outputf(vi, 2,  "MMEM:MSIS 'RAM:'");
		break;
	case 13: case 14://NON-VOL
		errStatus = hp871x_outputf(vi, 2,  "MMEM:MSIS 'MEM:'");
		break;
	case 15: case 16://Floppy disk
		errStatus = hp871x_outputf(vi, 2, "MMEM:MSIS 'INT:'");
		break;
	case 17://To Network Analyzer from PC
		// Suppress EOI from being set at end of viWrite below
		if ((errStatus = viSetAttribute(vi, VI_ATTR_SEND_END_EN, VI_FALSE)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// Allocate a memory buffer to receive the file
		file_buf = new char[max_sz];
		sprintf(file_buf, "MMEM:TRAN '%s',#0", dest);
		// Send SCPI command preparing the instrument to receive the file
		if ((errStatus = viWrite(vi, (ViBuf)file_buf, (ViUInt32)strlen(file_buf), &retCount)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// Re-enable EOI
		if ((errStatus = viSetAttribute(vi, VI_ATTR_SEND_END_EN, VI_TRUE)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// Open file and get a pointer to it
        file_ptr = fopen(name, "rb");
		// Read the file into the memory buffer, index = number of bytes in file
        index = (ViUInt32)fread(file_buf, sizeof(char), (size_t)max_sz, file_ptr);
		// Terminate the buffer with a linefeed
		file_buf[index] = '\n';
		// Output the buffer to the instrument
		if ((errStatus = viWrite(vi, (ViBuf)file_buf, index + 1, &retCount)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// cleanup
		delete [] file_buf;
		fclose(file_ptr);
		break;
	case 18://From Network Analyzer to PC
		// Send SCPI command to have the instrument output the file
		if ((errStatus = viPrintf(vi, "MMEM:TRAN? '%s'\n", name)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// Read in the #0 header
		if ((errStatus = viScanf(vi, "%#c", &numchars, header)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// Open new file on PC for writing and get a pointer to it
        file_ptr = fopen(dest, "wb");
		// Allocate a memory buffer to receive the file
		file_buf = new char[max_sz];
		// Initialize the entire buffer with null characters
		memset(file_buf, (int)'\0', (size_t)max_sz);
		// Read into the memory buffer from the instrument until EOI is encountered
	    if ((errStatus = viScanf(vi, "%t", file_buf)) < VI_SUCCESS)
            return statusUpdate(vi, thisPtr, errStatus);
		// Find the linefeed which is the last byte sent by the instrument
		index = max_sz - 1;
		while (file_buf[index] != '\n') 
			index--;
		// Write the buffer (except last linefeed of course) to the file
        fwrite(file_buf, sizeof(char), (size_t)index, file_ptr);
		// cleanup
		delete [] file_buf;
		fclose(file_ptr);
		break;
	}
// Leave mass storage error checking up to customer!

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_save
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Saves instrument state or ASCII list from channel 1 or 2 to default 
 *			 drive (unless otherwise specified).  
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString save_name.  Contains file name to be stored. File name may  
 * IN		 contain drive specifier prefix(MEM: RAM: or INT:) 
 *            
 * PARAM 3 : ViString request. OPTIONAL; Default= STATE.  Other choices are  
 * IN		 LIST1 and LIST2.
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_save( 
        ViSession vi, 
		ViString save_name,
		ViString request)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_save");

const ViInt32 size = 3;
ViString req[size]= {  "LIST1", "LIST2", "STATE"
					}; 

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0:// save trace1
		errStatus = hp871x_outputf(vi, 2,  "MMEM:STOR:TRAC CH1FDATA,'%s'", save_name);
		break;
	case 1:// save trace2
		errStatus = hp871x_outputf(vi, 2, "MMEM:STOR:TRAC CH2FDATA,'%s'", save_name);
		break;
	case 2:// save state
		errStatus = hp871x_outputf(vi, 2, "MMEM:STOR:STAT 1,'%s'", save_name);
		break;
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_recall
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Recalls instrument state from default drive unless otherwise specified. 
 *			 Also set/reads Fast Recall function. 
 *
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString name.  Contains file name to load, or "ON"/"OFF" if
 * IN		 setting Fast Recall.  File name may contain drive specifier 
 *			 prefix (MEM: RAM: or INT:) 
 *            
 * PARAM 3 : ViString request. OPTIONAL  Default = "RECALL"  Other choices are  
 * IN		 FAST and FAST?
 *
 * PARAM 4 : ViPInt32 cur_status.  Contains status (1=ON or 0=OFF) of Fast Recall. 
 * OUT		  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_recall( 
        ViSession vi, 
		ViString recall_name,
		ViString request,
		ViPInt32 recall_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_recall");

const ViInt32 size = 5;
ViString req[size]= { "RECALL", "FAST_ON", "FAST_OFF", "FAST?", "?"
					}; 

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);


switch (choice)
	{
	case 0: //Recall
		errStatus = hp871x_outputf(vi, 2,  "MMEM:LOAD:STAT 1,'%s'", recall_name);
		break;
	case 1:// FastRecall ON
		errStatus = viPrintf(vi, "DISP:MENU:REC:FAST:STAT ON;*WAI\n");
		break;
	case 2:// FastRecall OFF
		errStatus = viPrintf(vi, "DISP:MENU:REC:FAST:STAT OFF;*WAI\n");
		break;
	case 3: case 4:// Query fast on/off
		if ((errStatus = viPrintf(vi, "DISP:MENU:REC:FAST:STAT?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", recall_status);
		break;
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */



/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_dir
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Performs catalog on default or selected drive.   
 *           See also:  dirInfo
 *
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViPInt32 files.  Total number of entries found.  Entries also  
 * OUT		 include any directories found.
 *
 * PARAM 3 : ViPString dir.  String returned containing all entries found, separated 
 * OUT		 by commas (,).
 *
 * PARAM 4 : ViString drive. OPTIONAL; Default= "DEFAULT"
 * IN		 Selects drive to be cataloged.  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Does not function on 8711A or 871xB.
 *				Operations on floppy disk take a long time! Use long timeouts!
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_dir(
		   ViSession vi,
		   ViPInt32 files,
		   ViPString dir,
		   ViString drive)
 
{
struct hp871x_globals *thisPtr;

ViStatus errStatus;
ViInt32 choice, opc=0, index=0;
char temp[15], dev[10], first_char=' ';

GET_GLOBALS(vi, thisPtr)

const ViInt32 size = 6;
ViString req[size]= {"DEFAULT", "DISK", "INT", 
					 "NONVOL", "MEM", "RAM"
					}; 

if(getChoice(vi,drive,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

strcpy(dir, ""); //clear dir
*files = -1;

switch (choice)
	{
	case 0: //default dir
		strcpy(dev, "");
		break;
	case 1: case 2://Floppy Disk
		strcpy(dev, " 'INT:'");
		break;
	case 3: case 4://Non-Vol
		strcpy(dev, " 'MEM:'");
		break;
	case 5://RAM
		strcpy(dev, " 'RAM:'");
		break;
	}
if ((errStatus = viPrintf(vi, "MMEM:CAT?%s\n",dev)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
if ((errStatus = delayVScanf(vi, "%c", &first_char)) < VI_SUCCESS) //Check 1st char for lf; indicates no disc installed
	return statusUpdate(vi, thisPtr, errStatus);
if (first_char == '\n') return statusUpdate(vi, thisPtr, VI_SUCCESS);

if ((errStatus = delayVScanf(vi, "%s\n", temp)) < VI_SUCCESS) //throw away first (parent) entry
	return statusUpdate(vi, thisPtr, errStatus);

while (VI_TRUE) 
	{	
		errStatus = delayVScanf(vi, "%s\n", temp);
		if (!strcmp(temp,"\"")) break;
		strcat(dir, temp);
		strcat(dir, ",");
		index++;
	}

*files = index;
dir[strlen(dir)-1] = '\0'; //overwrite last ',' character

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_dirInfo
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Reads more detailed information on specified filename or    
 *           directory.  See also:  hp871x_dir
 *
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString info_name. Filename (or directory) to obtain info on.
 * IN
 *            
 * PARAM 3 : ViPString info.  Requested info (type, size, date) 58 chars.  
 * OUT		 
 *
 * PARAM 4 : ViString drive.  OPTIONAL, Drive location if not default. 
 * IN		  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Does not function on 8711A or 871xB.
 *				Operations on floppy disk take a long time! Use long timeouts!
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_dirInfo(
		   ViSession vi,
		   ViString info_name,
		   ViPString info,
		   ViString drive)
		 
{
struct hp871x_globals *thisPtr;

ViStatus errStatus;
ViInt32 choice;
char name[20], dev[10];
int  ch = ':';
char *pdest;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_dirInfo");

const ViInt32 size = 6;
ViString req[size]= { "DEFAULT", "DISK", "INT", 
					  "NONVOL", "MEM", "RAM"
					}; 

if(getChoice(vi,drive,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0://default drive
		strcpy(dev, "");
		break;
	case 1: case 2://Floppy Disk
		strcpy(dev, "INT:");
		break;
	case 3: case 4://Non-Vol
		strcpy(dev, "MEM:");
		break;
	case 5://RAM
		strcpy(dev, "RAM:");
		break;
	}
pdest = strchr(info_name, ch);
if (pdest!=NULL) 
	 strcpy(name, info_name);
else 
	 sprintf(name, "%s%s", dev, info_name);

if ((errStatus = viPrintf(vi, "MMEM:FILE:INFO? '%s'\n",name)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
errStatus = delayVScanf(vi, "%t\n", info);
strcpy(info,strtok(info, "\""));//Remove last quote
if (strlen(info) <5)			//If non-existent, return null
    strcpy(info,"\0");

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_clock  (YEAR 2000 COMPLIANT!)
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Performs various clock (time/date) functions.  Also allows user to  
 *			 synce analyzer time to computers time.
 *
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *
 * PARAM 2 : ViString request.  Selects desired action; see code below for choices  
 * IN		 
 *
 * PARAM 3 : ViString clock_data.  OPTIONAL Contains time to be set in 23,59,59 format,
 * IN		 or date to be set in 1999,12,31 format.
 *            
 * PARAM 4 : ViPString cur_clock. OPTIONAL  Returned time/date in above format 
 * OUT		  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_clock(
		   ViSession vi,
		   ViString request,
		   ViString clock_data,
		   ViPString cur_clock)
		 
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, int1, int2, int3;
char settime[20], setdate[20];
char selection[40];
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_clock");

struct tm *newtime;
time_t aclock;

const ViInt32 size = 11;
ViString req[size]= { "YMD", "MDY", "DMY", "ALPHA", "NUM", "NUMERIC", "DATE",
					  "TIME", "DATE?", "TIME?", "SYNC" }; 

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0: case 1: case 2://format
		errStatus = viPrintf(vi, "DISP:ANN:CLOC:DATE:FORM %s;*WAI\n", selection);
		break;
	case 3: case 4: case 5:// Mode
		errStatus = viPrintf(vi, "DISP:ANN:CLOC:DATE:MODE %s;*WAI\n", selection);
		break;
	case 6: //DATE
		errStatus = viPrintf(vi, "SYST:DATE %s;*WAI\n", clock_data);
		break;
	case 7: //Time
		errStatus = viPrintf(vi, "SYST:TIME %s;*WAI\n", clock_data);
		break;
	case 8: //DATE?
		if ((errStatus = viPrintf(vi, "SYST:DATE?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i,%i,%i\n", &int1, &int2, &int3);
		sprintf(cur_clock, "%i,%i,%i", int1, int2, int3);
		break;
	case 9: //Time?
		if ((errStatus = viPrintf(vi, "SYST:TIME?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%hi,%hi,%hi\n", &int1, &int2, &int3);
		sprintf(cur_clock, "%hi,%hi,%hi", int1, int2, int3);
		break;
	case 10: //sync analyzer to Computer's clock
		time( &aclock );                 // Get time in seconds 
		newtime = localtime( &aclock );  // Convert time to struct tm form 
		sprintf(settime, "%i,%i,%i",newtime->tm_hour, newtime->tm_min,newtime->tm_sec);
		sprintf(setdate, "%i,%i,%i",(newtime->tm_year)+1900, (newtime->tm_mon)+1,newtime->tm_mday);
		if ((errStatus = viPrintf(vi, "SYST:DATE %s;*WAI\n", setdate)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = viPrintf(vi, "SYST:TIME %s;*WAI\n", settime);
		break;
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_progControl
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Performs various program control functions and houskeeping.  
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. 
 * IN		 See list below for selections
 *
 * PARAM 3 : ViString command.  OPTIONAL  IBASIC command to be sent. 
 * IN		  
 *
 * PARAM 4 : ViPString prog_status.  Returns result of current program state 
 * OUT	      		  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *   
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_progControl( 
        ViSession vi, 
		ViString request,
		ViString command,
		ViPString prog_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
char selection[40];
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_progControl");

const ViInt32 size = 10;
ViString req[size]= { "DEL", "DELETE", "COMMAND", "STOP", "PAUSE", "RUN", 
					  "CONTINUE", "CONT",  "WAIT", "STATE?"
					}; 


if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);
strip(request, selection);

switch (choice)
	{
	case 0: case 1://Delete
		errStatus = viPrintf(vi, "PROG:DEL:ALL;*WAI\n");
		break;
	case 2: //Command
		errStatus = viPrintf(vi, "PROG:EXEC '%s';*WAI\n", command);
		break;
	case 3: case 4: case 5: case 6: case 7:// Stop, Pause, Run, Cont.
		errStatus = viPrintf(vi, "PROG:STAT %s;*WAI\n", selection);
		break;
	case 8://Wait
		errStatus = hp871x_outputf(vi, 2,  "PROG:WAIT");
		break;
	case 9:// State?
		if ((errStatus = viPrintf(vi, "PROG:STATE?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%s\n", prog_status);
		if (!(strcmp(prog_status, "PAUS")))  strcpy(prog_status,"PAUSE");
		break;
	
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_progVariable
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Allows user to set/read both string and numeric variables 
 *			 from an internal IBASIC program.
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString name.  Variable name; append "?" if it is to be queried. 
 * IN		  
 *
 * PARAM 3 : ViString str_data.  Data to be input to string variable 'name'  
 * IN	 	  
 *
 * PARAM 4 : ViPString cur_str. OPTIONAL  Current contents of string variable 'name' 
 * OUT	     
 *
 * PARAM 5 : ViReal64 number_data.  OPTIONAL Numeric value to be input to variable 'name' 
 * IN	     	  
 *
 * PARAM 6 : ViPReal64  cur_number.  OPTIONAL  Current contents of variable 'name' 
 * OUT	      named in data		  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *   
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_progVariable( 
        ViSession vi, 
		ViString name,
		ViString str_data,
		ViPString cur_str,
		ViReal64 number_data,
		ViPReal64 cur_number)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, query, string;
char temp[30], temp1[30], temp2[30], q_name[30] ;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_progVariable");

strcpy(temp1, name);
strcpy(temp2, name);
hp871x_stringParse(vi, temp1, temp, &string, "$"); // determine if string variable
hp871x_stringParse(vi, temp2, q_name, &query, "?");  // determine if query & strip off '?'
choice = string +(2*query);

printf("Choice=%i\n",choice);

switch (choice)

	{
	case 0:// Number
		errStatus = viPrintf(vi, "PROG:NUMB '%s',%lf;*WAI\n", name, number_data);
		break;
	case 1:// String
		errStatus = viPrintf(vi, "PROG:STR '%s','%s';*WAI\n", name, str_data);
		break;
	case 2:// Number?
		if ((errStatus = viPrintf(vi, "PROG:NUMB? '%s'\n", q_name)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%lf\n", cur_number);
		break;
	case 3:// String?

		if ((errStatus = viPrintf(vi, "PROG:STR? '%s'\n", q_name)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "\"%t\n", cur_str); //suppress first quote
		cur_str[strlen(cur_str)-2] = '\0'; //overwrite last quote and LF character
		break;


}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_progLoad
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Transfers IBASIC program from computer file to Analyzer  
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString progfile. Name of file containing the ASCII IBASIC code.
 * IN		 Filename usually must include full path name. 
 *			 e.g.  C:\ibasic\hp871x\meas_amp.txt
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 * 
 * LIMITATIONS: Program file is assumed to be in ASCII text.
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_progLoad( 
        ViSession vi, 
		ViString progfile)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus=0;
const int maxchars = 250;
char temp[maxchars + 3], errmsg[256];
ViInt32 errnum;
FILE* infile;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_progLoad");

if ((errStatus = viPrintf(vi, "*CLS;PROG:DEL:ALL\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
Sleep(200);//May not be necessary


//return statusUpdate(vi, thisPtr, errStatus);

if ((errStatus = viPrintf(vi, "PROG:DEF #0")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

infile = fopen(progfile, "r");
if (infile == NULL)
	return statusUpdate(vi, thisPtr, hp871x_FILE_NOT_FOUND_ERROR);

while (getLine(temp, maxchars, infile))
	{
	if (temp[0] != '\0')
		if ((errStatus = viPrintf(vi, "%s", temp)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
	}
	
fclose(infile);

if ((errStatus = viPrintf(vi, "\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

hp871x_error_query(vi,&errnum, errmsg);

if (errnum !=0) //Program Load Error
{	 sprintf(thisPtr->errMessage, "HP 871x ERR# %i",errnum);
	 return statusUpdate(vi,thisPtr,hp871x_PROG_LOAD_ERROR);
}
else	
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : int getLine
 *-----------------------------------------------------------------------------
 * PURPOSE : Reads an entire line of characters (including whitespace chars) 
 *           into a string until a carriage return or end-of-file (EOF) is 
 *           encountered, or until the maximum specified number of characters 
 *           is read.  The string is then terminated with a CR/LF pair.
 *            
 * PARAM 1 : char *s.  Pointer to string which will receive the characters.
 * OUT        
 * PARAM 2 : int maxchars. Maximum number of characters to read into the string.
 * IN        
 * PARAM 3 : FILE *f.  Stream pointer (handle) to the file to read the data from.
 * IN        
 * 
 * RETURN  : 1 : No error.  
 *           0 : Indicates end-of-file.
 *-----------------------------------------------------------------------------
 */
int getLine(char *s, int maxchars, FILE *f)
{

  #define CR 13	
  #define LF 10	

  register int i=1;
  
  s[0] = (char)fgetc(f);
  if ((s[0] == LF) || (s[0] == CR))
  {
    s[0] = '\0';
    return 1;
  }
  else if (feof(f))
  return 0;

  while(1)
  {
     s[i] = (char)fgetc(f);
 	 if  (s[i] == LF)
     { s[i + 1] = '\0';
       return 1;
     }

	 else if  (s[i] == CR)
     {  s[i] == LF;
		s[i + 1] = '\0';
        return 1;
     }

	 else if (i == maxchars - 1)
     {
	   s[i + 1] = LF;
	   s[i + 2] = '\0';
       return 1;
     }

	 else if (feof(f))
     {
	   s[i] = LF;
	   s[i + 1] = '\0';
       return 1;
     }

     ++i;
  }
}			 /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_outputf
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : General purpose output that allows user to select output mode, set
 *           up various implementation of OPC, and append proper termination
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViInt32 opc_mode. Sets OPC mode; see below for choices
 * IN		  
 *            
 * PARAM 3 : ViString fmtStr, ...   Output string; variable # of parameters 
 * IN		  
 *
 *
 * RETURN  :  VI_SUCCESS:No error. Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_outputf(
        ViSession  vi,
		ViInt32 opc_mode,
		ViString fmtStr,
        ...) 
{
ViStatus  errStatus;
va_list   va;
struct hp871x_globals *thisPtr;
char printFmt[1024];
ViInt32 esr, opc=0;
GET_GLOBALS(vi, thisPtr)
   
if ((errStatus = viGetAttribute(vi, VI_ATTR_USER_DATA,(ViAddr) &thisPtr)) < VI_SUCCESS)
    return errStatus;

if ((errStatus = viFlush(vi,VI_READ_BUF_DISCARD)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

strcpy(printFmt, fmtStr);
va_start(va, fmtStr);
switch (opc_mode)
{
	case 0: // Append "\n" only
		strcat(printFmt, "\n");
		errStatus = viVPrintf(vi, printFmt, va);
		if (thisPtr->dTime > 0)
			 doDelay(thisPtr->dTime);
		break;
	case 1: // Append ";*WAI\n"
		strcat(printFmt, ";*WAI\n");
		errStatus = viVPrintf(vi, printFmt, va);
		if (thisPtr->dTime > 0)
			 doDelay(thisPtr->dTime);
		break;
	case 2: // Append ";*OPC?\n" and then enter opc
		strcat(printFmt, ";*OPC?\n");
		if ((errStatus = viVPrintf(vi, printFmt, va)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if (thisPtr->dTime > 0)
			doDelay(thisPtr->dTime);
		errStatus = delayVScanf(vi, "%i\n", &opc);
		break;
	case 3:// Append ";*OPC\n" and then look for ESR bit
		if ((errStatus = viPrintf(vi, "*CLS\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		strcat(printFmt, ";*OPC\n");
		if ((errStatus = viVPrintf(vi, printFmt, va)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if (thisPtr->dTime > 0)
			 doDelay(thisPtr->dTime);
		do
		{
			Sleep(25);// wait 25 ms between checks
			if ((errStatus = viPrintf(vi, "*ESR?\n")) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
			Sleep(25);// wait another 25 ms
			
			if ((errStatus = delayVScanf(vi, "%i\n", &esr)) < VI_SUCCESS)
				return statusUpdate(vi, thisPtr, errStatus);
			opc = esr & 1; // Logical AND w/mask (1) to only look at bit 0
		} while (!opc);
		break;
	case 4: //Append nothing
		errStatus = viVPrintf(vi, printFmt, va);
		if (thisPtr->dTime > 0)
			 doDelay(thisPtr->dTime);
		break;
	default:
		return statusUpdate(vi, thisPtr, hp871x_READ_MATCH_ERROR);
		break;
}
va_end(va);

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_doCal
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Chooses type of Cal, does it and saves it. Requires user
 *			 intervention from front panel of 871x.
 *            
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request.  Selects cal type; see code for choices.  
 * IN         
 *
 * PARAM 3 : ViInt32 abort. Value of 1 indicates user aborted cal  
 * IN         
 *
 * PARAM 4 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 * PARAM 5 : ViString prompt. (OPTIONAL, default="") 
 * IN        Allows user to specify first prompt (only) for cal  
 *
 *           
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 * LIMITATIONS: Enhanced Resp not valid on 8711A and 871xB!
 * 
 *-----------------------------------------------------------------------------
 */
 
ViStatus _VI_FUNC hp871x_doCal( 
        ViSession vi, 
		ViString request,
		ViPInt32 abortcal,
		ViInt32 channel,
		ViString prompt)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice, keycode,deflt_flg=0, stan, fp, kb, standards;
char msg[512], keytype[]="NONE", method[10];

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_doCal");

const ViInt32 size = 13;
ViString req[size]= {"RESPONSE", "RESP", "THRU", "THROUGH", "RESPONSE_&_ISOLATION", 
					 "RESP_&_ISOL", "R&I", "ENHANCED_RESPONSE", "ENH_RESP","ENHANCED",
					 "REFLECTION","REFL", "TWOPORT"  					 
					};

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if(checkChannel(vi,channel)) 
	return statusUpdate(vi,thisPtr,hp871x_INVALID_CHANNEL_ERROR);

if ((errStatus = hp871x_checkChanStatus(vi,channel)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);


if (!strcmp(prompt,""))
	deflt_flg = 1; //set default flag
else
{	errStatus = hp871x_message(vi,"OFF" );
    strcpy(msg,prompt);
}

//setup initializations
errStatus= hp871x_softkey(vi);
errStatus= hp871x_keyQueue(vi, "CLEAR");
errStatus= hp871x_keyQueue(vi, "OFF");
errStatus= hp871x_softkey(vi, "  Measure Standard",1);
errStatus= hp871x_softkey(vi, "    Abort Cal",6); 

switch (choice)
{
	case 0: case 1: case 2: case 3: //Response
		strcpy(method, "TRAN1");
		standards = 1;
		break;
	case 4: case 5: case 6://Response & Isolation
		strcpy(method, "TRAN2");
		standards = 2;
		break;
	case 7: case 8: case 9://Enhanced Response 		
		strcpy(method, "TRAN3");
		standards = 4;
		break;
	case 10: case 11: //Reflection
		strcpy(method, "REFL3");
		standards = 3;
		break;
	case 12: // Two Port
		strcpy(method, "TWOP");
		standards = 7;
		break;
}
*abortcal = 0;
errStatus = viPrintf(vi, "SENS%i:CORR:COLL:METH %s;*WAI\n",channel, method);
errStatus = hp871x_message(vi,"ON" );
if (!deflt_flg)
	errStatus = hp871x_message(vi,"SHOW" , msg);
for (stan=1;  stan<standards+1; stan++) 	
	{
	errStatus = hp871x_beep(vi, "prompt");
	do 
		{ 
		if ((errStatus= hp871x_keyRead(vi, keytype, &keycode)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		fp= !strcmp(keytype,"KEY");
		kb= !strcmp(keytype,"ASC");
		Sleep(250);
		}
	while (!((fp && (keycode==0)) || (kb && (keycode==128)))  && !((fp && (keycode==5)) || (kb && (keycode==133))));
	if ((keycode==5) || (keycode==133)) //abort
		{
		errStatus = hp871x_outputf(vi, 2, "SENS%i:CORR:COLL:ABORT",channel);
		errStatus = hp871x_softkey(vi);
		*abortcal =1;
		return VI_SUCCESS;
		}
	else
		errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:ACQ STAN%i",channel,stan);
	}

errStatus = hp871x_outputf(vi, 3, "SENS%i:CORR:COLL:SAVE",channel); //Save cal

// cleanup
errStatus= hp871x_softkey(vi); //Clear softkey
errStatus = hp871x_message(vi,"CLEAR" );//Clear message

if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */


/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_readID
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Reads analyzer model number or other info.    
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViPString cur_ID. Contain desired parameter
 * OUT		 
 *
 * PARAM 3 : ViString request. OPTIONAL, Default = "MODEL?"
 * IN        Other choices are "SERIAL?", "REVISION?", "REV_VALUE?" 
 *
 * PARAM 4 : ViPReal64  ID_Status. OPTIONAL, Default = 0
 * OUT        Returns real version 
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_readID( 
        ViSession vi, 
		ViPString cur_ID,
		ViString request,
		ViPReal64 ID_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
char id[100], sn[15], model[15], rev[15], hp[15], options[100];
ViInt32 choice, dummy;
char *token, *token2;



GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_readID");

const ViInt32 size = 17;
ViString req[size]= { "MODEL?", "SERIAL?", "S/N?", "REVISION?", "REV?", 
					  "REV_VALUE?", "MINFREQ?", "MAXFREQ?", "MP_ID?", 
					  "ATTEN?", "LAN?", "FAULT?", "SRL?", "50?", "75?",
					  "IBASIC?", "AM?", 
					 }; 

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

if ((errStatus = viPrintf(vi, "*IDN?;*WAI\n")) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);
if ((errStatus = delayVScanf(vi, "%s\n", id)) < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);

if (choice>8) //only do if needed for option choice
	{
	if ((errStatus = viPrintf(vi, "*OPT?;*WAI\n")) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	if ((errStatus = delayVScanf(vi, "%s\n", options)) < VI_SUCCESS)
		return statusUpdate(vi, thisPtr, errStatus);
	*ID_status = 0; //init to No
	}
 
errStatus = hp871x_stringParse(vi, id, hp, &dummy);//not needed 
errStatus = hp871x_stringParse(vi, id, model, &dummy);
errStatus = hp871x_stringParse(vi, id, sn, &dummy);
errStatus = hp871x_stringParse(vi, id, rev, &dummy);
rev[strlen(rev)-1]='\0';  //remove last quote from rev
	
switch (choice)
	{ 
	case 0: // Model
		strcpy(cur_ID, model);
		break;
	case 1: case 2: // Serial #
		strcpy(cur_ID, sn);
		break;
	case 3: case 4: // Revision
		strcpy(cur_ID, rev);
		break;
	case 5: // rev value
		strcpy(cur_ID, rev);
		*ID_status =atof(rev+2); // strip alpha char; convert to real
		break;
	case 6: // min freq
		if ((errStatus = viPrintf(vi, "SENS:FREQ:STAR? MIN\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", ID_status)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 7: // max freq
		if ((errStatus = viPrintf(vi, "SENS:FREQ:STOP? MAX\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "%lf\n", ID_status)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		break;
	case 8: // Multiport ID
		if ((errStatus = viPrintf(vi, "DIAG:MED:EEPR:IDEN?\n")) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		if ((errStatus = delayVScanf(vi, "\"%t\n", cur_ID)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		cur_ID[strlen(cur_ID)-2] = '\0'; //overwrite last quote and LF character
		break;
	case 9: // Atten?
		token = strstr(options, "1E1");
		*ID_status = !(token== NULL);
		token2 = strstr(model, "S");
		if (!(token2==NULL)) *ID_status=1;
		break;
	case 10: // LAN?
		token = strstr(options, "1F7");
		*ID_status = !(token== NULL);
		token2 = strstr(model, "E");
		if (!(token2==NULL)) *ID_status=1;
		break;
	case 11: case 12: // Fault / SRL?
		token = strstr(options, "100");
		*ID_status = !(token== NULL);
		break;
	case 13: // 50 ohms?
		token = strstr(options, "1EC");
		*ID_status = (token== NULL);
		break;
	case 14: // 75 ohms?
		token = strstr(options, "1EC");
		*ID_status = !(token== NULL);
		break;
	case 15: // IBASIC?
		token = strstr(options, "1C2");
		*ID_status = !(token== NULL);
		token2 = strstr(model, "E");
		if (!(token2==NULL)) *ID_status=1;
		break;
	case 16: // AM Delay?
		token = strstr(options, "1DA");
		token2 = strstr(options, "1DB");
		if  (!((token==NULL) && (token2==NULL))) *ID_status =1;
		break;
}		

return statusUpdate(vi, thisPtr, VI_SUCCESS);
}		/* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_saveDefine
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Defines the contents of an instrument state.  
 * 
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. 
 * IN		 See list below for selections
 *
 * PARAM 3 : ViString status.  Contains "ON" or "OFF" for CORR, ISTATE or TRACE. . 
 * IN		 Contains list format type (Touchstone or Lotus123) if request = "FORMAT" 
 *
 * PARAM 4 : ViPInt32 cur_status.  Contains status (1=ON or 0=OFF) of requested function. 
 * OUT		  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_saveDefine( 
        ViSession vi,
		ViString request,
		ViString define,
		ViPInt32 define_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;
ViInt32 choice;
char selection[40], def_strip[15];
GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_saveDefine");

const ViInt32 size = 7;
ViString req[size]= { "CORR", "ISTATE", "TRACE", "FORMAT", 
					  "CORR?", "ISTATE?", "TRACE?"
					}; 

if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

strip(define, def_strip);
if (choice <=2) //Only valid choices are on/off
	 if ((strcmpi(def_strip, "ON")) && (strcmpi(def_strip, "OFF")))
		return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

strip(request, selection);

switch (choice)
	{
	case 0: //Corr
		errStatus = viPrintf(vi, "MMEM:STOR:STAT:CORR %s;*WAI\n", def_strip);
		break;
	case 1: //ISTATE
		errStatus = viPrintf(vi, "MMEM:STOR:STAT:IST %s;*WAI\n", def_strip);
		break;
	case 2: //TRACE
		errStatus = viPrintf(vi, "MMEM:STOR:STAT:TRAC %s;*WAI\n", def_strip);
		break;
	case 3://Format  Valid choices for status are 'LOTus123" or TOUChstone
		errStatus = viPrintf(vi, "MMEM:STOR:TRAC:FORM %s;*WAI\n", def_strip);	
		break;
	case 4: case 5: case 6:// read status
		if ((errStatus = viPrintf(vi, "MMEM:STOR:STAT:%s\n", selection)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", define_status);
		break;
}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);

}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : hp871x_stringParse
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Parses any string. Requires a one-character delimiter (default= comma)
 *           Not a real Visa function in that no instrument calls are made.
 *
 * PARAM 1 : ViSession vi
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString in_out. String to be parsed; returns remains of string
 * IN/OUT	 after parsing	 
 *
 * PARAM 3 : ViString parsed.  Contains string parsed. 
 * OUT		  
 *
 * PARAM 4 : ViPInt32 not_done.  Returns 0 when last of string is parsed; 1 otherwise. 
 * OUT		  
 *
 * PARAM 4 : ViString  delimiter.  OPTIONAL; Default = "," (comma)
 * IN        Specifies a ONE char delimiter. 
 * 	  
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
* 
/****************************************************************************/

ViStatus _VI_FUNC hp871x_stringParse(
				   ViSession vi,
                   ViChar _VI_FAR in_out[],
				   ViPString parsed,
				   ViPInt32 not_done,
				   ViString delimiter)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_stringParse");

size_t p_len;
char *inp2;
const size_t size= strlen(in_out)+1;// +1 to account for NULL
char *input = new char[size];
	
strcpy(input,in_out);
strcpy(parsed,"\0");

p_len =strcspn(in_out, delimiter);
*(in_out+p_len)='\0';//NULL
strcpy(parsed,in_out);

if (!(strcmp(input,parsed))) //then done parsing
	{
		inp2=input+p_len;
 		strcpy(in_out,inp2);
  		delete input;
		*not_done= 0;
	}
else 
	{
		inp2=input+p_len+1;
 		strcpy(in_out,inp2);
   		delete input;
		*not_done= 1;
	}
return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_sweepStep
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Sets or returns stepped sweep status (ON/OFF).  
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViString request. Must be ON, OFF, or ?
 *
 * PARAM 3 : ViInt32 channel. (OPTIONAL, default=1) 
 * IN        Indicates channel number (1 or 2)   
 *
 * PARAM 4 : ViPInt32 step_status.  OPTIONAL  
 * OUT       Returns 1 for stepped Sweep ON; 0 for OFF    
 *
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *
 * Note: For 871xE and above only!           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_sweepStep( 
        ViSession vi, 
		ViString request,
		ViInt32 channel,
		ViPInt32 step_status)
{
struct hp871x_globals *thisPtr;
ViStatus errStatus;

GET_GLOBALS(vi, thisPtr)
strcpy(thisPtr->funcName, "hp871x_sweepStep");

ViInt32 choice;

const ViInt32 size = 3;
ViString req[size]= {"OFF", "ON", "?"
					};
if(getChoice(vi,request,size,req,&choice)) 
	return statusUpdate(vi,thisPtr,hp871x_NO_MATCH_ERROR);

switch (choice)
	{
	case 0: //Off
	   errStatus = viPrintf(vi, "SENS%i:SWE:GEN ANALOG;*WAI\n", channel);
	   break;
	case 1: //On
		errStatus = viPrintf(vi, "SENS%i:SWE:GEN STEPPED;*WAI\n", channel);
		break;
	case 2: //?
		if ((errStatus = viPrintf(vi, "SENS%i:SWE:GEN?;*WAI\n", channel)) < VI_SUCCESS)
			return statusUpdate(vi, thisPtr, errStatus);
		errStatus = delayVScanf(vi, "%i\n", step_status);
		break;
	}
if (errStatus < VI_SUCCESS)
    return statusUpdate(vi, thisPtr, errStatus);
else
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
}        /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : int strip
 *-----------------------------------------------------------------------------
 * PURPOSE : Strips any leading/trailing quotes.  
 *            
 * PARAM 1 : ViString request.  String to be stripped
 * IN		  
 * PARAM 2 : ViPString selection.  Stripped String
 * OUT		  
 *-----------------------------------------------------------------------------
 */

int strip(ViString request,
		  ViPString selection)
	   
{			   
strcpy(selection,request);

if (selection[0]=='\"')  
	strcpy(selection, selection+1);  // remove first quote if any
if (selection[strlen(selection)-1] == '\"')  
	selection[strlen(selection)-1] = '\0'; // overwrite last quote if any

return 0;
}			 /* ----- end of function ----- */

/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * FUNC    : ViStatus _VI_FUNC hp871x_checkChanStatus
 *-----------------------------------------------------------------------------
 * 
 * PURPOSE : Checks to make sure specified channel is on. If not, generate 
 *			 Error.  Only used for some sweep related functions.
 * 
 * PARAM 1 : ViSession vi.
 * IN        Instrument Handle returned from hp871x_init().
 *            
 * PARAM 2 : ViInt32 channel. Contain channel to be checked
 * IN		 
 *
 * RETURN  :  VI_SUCCESS:No error.Non VI_SUCCESS:Indicates error condition.
 *            To determine error message, pass the return value to routine
 *            "hp871x_error_message"
 *           
 *-----------------------------------------------------------------------------
 */
ViStatus _VI_FUNC hp871x_checkChanStatus( 
        ViSession vi, 
		ViInt32 channel)
{
struct hp871x_globals *thisPtr;
ViChar message[hp871x_ERR_MSG_LENGTH];
ViStatus errStatus;
ViInt32 chan_status;


GET_GLOBALS(vi, thisPtr)

if ((errStatus = viPrintf(vi, "SENS%i:STAT?\n",channel)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

if ((errStatus = delayVScanf(vi, "%i\n", &chan_status)) < VI_SUCCESS)
	return statusUpdate(vi, thisPtr, errStatus);

if (chan_status) 
	return statusUpdate(vi, thisPtr, VI_SUCCESS);
//Error condition below here

sprintf(message, "Function=%s;  Channel=%i.", thisPtr->funcName, channel);
strcpy(thisPtr->errMessage, message);

return statusUpdate(vi,thisPtr,hp871x_CHANNEL_OFF_ERROR);


}		/* ----- end of function ----- */
