/*
//
//               INTeL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//
//  Purpose: Short subset of Windows* definitions
//
*/

#if !defined (__IPLWIND_H__) && !defined (_WINDOWS_)
#define __IPLWIND_H__

#ifdef __cplusplus
extern "C" {
#endif
    
#if !defined _WINGDI_
    
    typedef unsigned long  DWORD;
    typedef unsigned short WORD;
    typedef          long  LONG;

#if !defined( _VXWORKS )
    typedef          int    BOOL;
    typedef unsigned int    UINT;
    typedef void            VOID;
#endif

    typedef unsigned char   BYTE;
    typedef float           FLOAT;
    typedef FLOAT          *PFLOAT;
    typedef void           *LPVOID;
    typedef int             INT;
    typedef void           *HWND;
    typedef char            CHAR;
    typedef       CHAR     *LPSTR;
    typedef const CHAR     *LPCSTR;
    typedef void           *PVOID;
    typedef PVOID           HANDLE;
    typedef HANDLE          HINSTANCE;
    typedef HANDLE          HLOCAL;
    typedef char*           PSTR;
    
  #if !defined( NULL)
    #define NULL            0
  #endif
    

  typedef struct tagBITMAPINFOHEADER{
      DWORD      biSize;
      LONG       biWidth;
      LONG       biHeight;
      WORD       biPlanes;
      WORD       biBitCount;
      DWORD      biCompression;
      DWORD      biSizeImage;
      LONG       biXPelsPerMeter;
      LONG       biYPelsPerMeter;
      DWORD      biClrUsed;
      DWORD      biClrImportant;
  } BITMAPINFOHEADER;
  
  typedef BITMAPINFOHEADER* LPBITMAPINFOHEADER;

#endif
    
#define TLS_OUT_OF_INDEXES (DWORD)0xFFFFFFFF
    
#define WINAPI      __STDCALL
#define WINAPIV     __CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  __STDCALL
#define PASCAL      __STDCALL
#define CONST       const

#if defined (_WIN32)     /* _WIN32 */
  #define WINBASEAPI  __declspec(dllimport)
  #define WINUSERAPI  __declspec(dllimport)
#else       /* _WIN32 */
  #define WINBASEAPI
  #define WINUSERAPI
#endif      /* _WIN32 */
    
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
    
#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
    
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L
    
#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7
    
#define DLL_PROCESS_ATTACH          1
#define DLL_THREAD_ATTACH           2
#define DLL_THREAD_DETACH           3
#define DLL_PROCESS_DETACH          0
    
#define LMEM_FIXED          0x0000
    /*
    #define LMEM_MOVEABLE       0x0002
    #define LMEM_NOCOMPACT      0x0010
    #define LMEM_NODISCARD      0x0020
    */
#define LMEM_ZEROINIT       0x0040
    /*
    #define LMEM_MODIFY         0x0080
    #define LMEM_DISCARDABLE    0x0F00
    #define LMEM_VALID_FLAGS    0x0F72
    #define LMEM_INVALID_HANDLE 0x8000
    
    #define LHND                (LMEM_MOVEABLE | LMEM_ZEROINIT)
    */
    
#define LPTR                (LMEM_FIXED | LMEM_ZEROINIT)

  #if defined( _WIN32 )    /* _WIN32 */
    WINBASEAPI DWORD  WINAPI  GetVersion   (void);
    WINBASEAPI DWORD  WINAPI  TlsAlloc     (void);
    WINBASEAPI LPVOID WINAPI  TlsGetValue  (DWORD  dwTlsIndex);
    WINBASEAPI BOOL   WINAPI  TlsSetValue  (DWORD  dwTlsIndex,LPVOID lpTlsValue);
    WINBASEAPI BOOL   WINAPI  TlsFree      (DWORD  dwTlsIndex);
    WINBASEAPI VOID   WINAPI  FatalAppExitA(UINT   uAction,LPCSTR lpMessageText);
    WINUSERAPI int    WINAPIV wsprintfA    (LPSTR  a, LPCSTR b, ...);
    WINBASEAPI HLOCAL WINAPI  LocalAlloc   (UINT   uFlags,UINT uBytes );
    WINBASEAPI HLOCAL WINAPI  LocalFree    (HLOCAL hMem );
    WINUSERAPI int    WINAPI  MessageBoxA  (HWND   hWnd,     LPCSTR  lpText,
                                            LPCSTR lpCaption,UINT    uType);
    
    # define MessageBox    MessageBoxA
    # define FatalAppExit  FatalAppExitA
    # define wsprintf      wsprintfA
  #endif    /* _WIN32 */
    
/* --- cy -- defines for DIB conversion functions ------------------------- */
    
    typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
    } RGBQUAD;
    
    typedef DWORD COLORREF;

    typedef struct tagBITMAPINFO {
       BITMAPINFOHEADER bmiHeader; 
       RGBQUAD          bmiColors[1]; 
    } BITMAPINFO; 

    typedef struct tagRGBTRIPLE { /* rgbt */
       BYTE rgbtBlue;
       BYTE rgbtGreen; 
       BYTE rgbtRed;
    } RGBTRIPLE; 
    
#define RGB(r,g,b)     \
    ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
    
#define  BI_RGB           0
#define  BI_RLE8          1
#define  BI_RLE4          2
#define  BI_BITFIELDS     3
    
    /* ---cs ------------------------------------------------------------------ */
    
#if defined( _WIN32 )   /* _WIN32 */
   #define STATUS_WAIT_0                    ((DWORD   )0x00000000L)
   #define STATUS_ABANDONED_WAIT_0          ((DWORD   )0x00000080L)
   #define STATUS_USER_APC                  ((DWORD   )0x000000C0L)
   #define STATUS_TIMEOUT                   ((DWORD   )0x00000102L)
   #define STATUS_PENDING                   ((DWORD   )0x00000103L)
   #define STATUS_SEGMENT_NOTIFICATION      ((DWORD   )0x40000005L)
   #define STATUS_GUARD_PAGE_VIOLATION      ((DWORD   )0x80000001L)
   #define STATUS_DATATYPE_MISALIGNMENT     ((DWORD   )0x80000002L)
   #define STATUS_BREAKPOINT                ((DWORD   )0x80000003L)
   #define STATUS_SINGLE_STEP               ((DWORD   )0x80000004L)
   #define STATUS_ACCESS_VIOLATION          ((DWORD   )0xC0000005L)
   #define STATUS_IN_PAGE_ERROR             ((DWORD   )0xC0000006L)
   #define STATUS_NO_MEMORY                 ((DWORD   )0xC0000017L)
   #define STATUS_ILLEGAL_INSTRUCTION       ((DWORD   )0xC000001DL)
   #define STATUS_NONCONTINUABLE_EXCEPTION  ((DWORD   )0xC0000025L)
   #define STATUS_INVALID_DISPOSITION       ((DWORD   )0xC0000026L)
   #define STATUS_ARRAY_BOUNDS_EXCEEDED     ((DWORD   )0xC000008CL)
   #define STATUS_FLOAT_DENORMAL_OPERAND    ((DWORD   )0xC000008DL)
   #define STATUS_FLOAT_DIVIDE_BY_ZERO      ((DWORD   )0xC000008EL)
   #define STATUS_FLOAT_INEXACT_RESULT      ((DWORD   )0xC000008FL)
   #define STATUS_FLOAT_INVALID_OPERATION   ((DWORD   )0xC0000090L)
   #define STATUS_FLOAT_OVERFLOW            ((DWORD   )0xC0000091L)
   #define STATUS_FLOAT_STACK_CHECK         ((DWORD   )0xC0000092L)
   #define STATUS_FLOAT_UNDERFLOW           ((DWORD   )0xC0000093L)
   #define STATUS_INTEGER_DIVIDE_BY_ZERO    ((DWORD   )0xC0000094L)
   #define STATUS_INTEGER_OVERFLOW          ((DWORD   )0xC0000095L)
   #define STATUS_PRIVILEGED_INSTRUCTION    ((DWORD   )0xC0000096L)
   #define STATUS_STACK_OVERFLOW            ((DWORD   )0xC00000FDL)
   #define STATUS_CONTROL_C_EXIT            ((DWORD   )0xC000013AL)
       
   #define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
   #define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
   #define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
   #define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
   #define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
   #define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
   #define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
   #define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
   #define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
   #define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
   #define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
   #define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
   #define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
   #define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
   #define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
   #define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
   #define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
   #define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
   #define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
   #define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
   #define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
       
   #define EXCEPTION_NONCONTINUABLE 0x1    /* Noncontinuable exception*/
       
   #define EXCEPTION_EXECUTE_HANDLER       1
   #define EXCEPTION_CONTINUE_SEARCH       0
   #define EXCEPTION_CONTINUE_EXECUTION    -1
       
   #define GetExceptionCode            _exception_code
   #define GetExceptionInformation     (struct _EXCEPTION_POINTERS *)_exception_info
       
   unsigned long __CDECL _exception_code(void);
   void *        __CDECL _exception_info(void);
#endif   /* _WIN32 */
    
    typedef struct _FLOATING_SAVE_AREA {
        DWORD   ControlWord;
        DWORD   StatusWord;
        DWORD   TagWord;
        DWORD   ErrorOffset;
        DWORD   ErrorSelector;
        DWORD   DataOffset;
        DWORD   DataSelector;
        BYTE    RegisterArea[80];
        DWORD   Cr0NpxState;
    } FLOATING_SAVE_AREA;
    
    typedef FLOATING_SAVE_AREA *PFLOATING_SAVE_AREA;
    
    typedef struct _CONTEXT {
    /*
    The flags values within this flag control the contents of
    a CONTEXT record.
    */
        
        DWORD ContextFlags;
        /*
        This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
        set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
        included in CONTEXT_FULL.
        */
        DWORD   Dr0;
        DWORD   Dr1;
        DWORD   Dr2;
        DWORD   Dr3;
        DWORD   Dr6;
        DWORD   Dr7;
        /*
        This section is specified/returned if the
        ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
        */
        FLOATING_SAVE_AREA FloatSave;
        
        /*
        This section is specified/returned if the
        ContextFlags word contians the flag CONTEXT_SEGMENTS.
        */
        DWORD   SegGs;
        DWORD   SegFs;
        DWORD   SegEs;
        DWORD   SegDs;
        
        /*
        This section is specified/returned if the
        ContextFlags word contians the flag CONTEXT_INTEGER.
        */
        DWORD   Edi;
        DWORD   Esi;
        DWORD   Ebx;
        DWORD   Edx;
        DWORD   Ecx;
        DWORD   Eax;
        
        /*
        This section is specified/returned if the
        ContextFlags word contians the flag CONTEXT_CONTROL.
        */
        DWORD   Ebp;
        DWORD   Eip;
        DWORD   SegCs;              /* MUST BE SANITIZED */
        DWORD   EFlags;             /* MUST BE SANITIZED */
        DWORD   Esp;
        DWORD   SegSs;
        
    } CONTEXT;
    
    typedef CONTEXT *PCONTEXT;
    
    typedef struct _EXCEPTION_RECORD {
        
        DWORD  ExceptionCode;
        DWORD  ExceptionFlags;
        struct _EXCEPTION_RECORD *ExceptionRecord;
        PVOID  ExceptionAddress;
        DWORD  NumberParameters;
        DWORD  ExceptionInformation[15];
        
    } EXCEPTION_RECORD;
    
    typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;
    
    typedef struct _EXCEPTION_POINTERS {
        PEXCEPTION_RECORD ExceptionRecord;
        PCONTEXT          ContextRecord;
    } EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
    
    WINBASEAPI VOID WINAPI RaiseException(
        DWORD dwExceptionCode,
        DWORD dwExceptionFlags,
        DWORD nNumberOfArguments,
        CONST DWORD *lpArguments
        );
    
/* -------------------------------------------------------------------------*/
    
#ifdef __cplusplus
}
#endif

#endif /* __IPLWIND_H__ */
