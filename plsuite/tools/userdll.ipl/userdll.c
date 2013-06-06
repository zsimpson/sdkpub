/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1998-2000Intel Corporation. All Rights Reserved.
//
//
//  Purpose: Generate custom DLL
//
*M*/

/*====================================================================*/

#define DLLMAIN DllMain

/*****************************************************************
* This part of code is used to generate DLL function body
******************************************************************
*/
#ifdef USER_W32DLL

/* get all the function prototypes as in static library */
#ifdef IPL_W32DLL
#undef IPL_W32DLL
#endif

#include <windows.h>
#include "ipl.h"

/*---- Warning!!! Please don't modify this section -----*/
/*---- Begin section  ----*/
void* __cdecl iplGetContext (void);
void* __cdecl iplInitContext (void* Context);
int   __cdecl iplSizeOfContext(void);
/*---- End of section ----*/

#endif /* USER_W32DLL */

/*****************************************************************
* Getting all the ipl Library structure definition without API
******************************************************************
*/
#ifdef USER_W32PCS

static const char* LOAD_DLL_ERR = "Load IPLib error";

#include <windows.h>
#define IPLAPI(type,name,arg)
#include "ipl.h"

/* one function pointer variables for each function included */
#undef  IPLAPI
#define IPLAPI(type,name,arg) \
        static FARPROC *d##name;\
        __declspec(naked dllexport) void __stdcall name arg { __asm jmp d##name }

#define __USERLIST__
#include "UserDll.h"
#undef __USERLIST__



static int LoadFunctions(HMODULE hLibModule);

typedef struct _USER_Desc_t {
   FARPROC **FuncAdr;
   char     *FuncName;
} USER_Desc_t;

#undef IPLAPI
#define GETAPI(name) {&d##name,#name},
#define IPLAPI(type,name,arg) GETAPI(name)

#define __USERLIST__
static USER_Desc_t USER_Desc[] = {
#include "UserDll.h"
   {NULL, NULL}
};
#undef __USERLIST__

/* get the DLL names */
#define __USERNAME__
#include "UserDll.h"
#undef __USERNAME__


/* ======================================================================= */
/* === Dispatch using waterfall mechanism ================================ */
/* ======================================================================= */

/* Describe Intel CPUs and libraries */
typedef enum{CPU_PX=0, CPU_P6, CPU_M5, CPU_M6, CPU_A6, CPU_W7, CPU_NOMORE} cpu_enum;
typedef enum{DLL_PX=0, DLL_P6, DLL_M5, DLL_M6, DLL_A6, DLL_W7, DLL_NOMORE} dll_enum;

/* Names of the Intel libraries which can be loaded */
static const char* dllNames[DLL_NOMORE] = {
   DLLNAME(PX), DLLNAME(P6), DLLNAME(M5), DLLNAME(M6), DLLNAME(A6), DLLNAME(W7)
}; 

/// New cpu can use some libraries for old cpu
static const dll_enum dllUsage[][DLL_NOMORE+1] = {
   { DLL_PX, DLL_NOMORE },
   { DLL_P6, DLL_PX, DLL_NOMORE },
   { DLL_M5, DLL_PX, DLL_NOMORE },
   { DLL_M6, DLL_M5, DLL_P6, DLL_PX, DLL_NOMORE },
   { DLL_A6, DLL_M6, DLL_M5, DLL_P6, DLL_PX, DLL_NOMORE },
   { DLL_W7, DLL_A6, DLL_M6, DLL_M5, DLL_P6, DLL_PX, DLL_NOMORE }
};

typedef struct {
   int family;
   int stepping;
   int model;
   int type;
   int feature;
   int tlb;
   int cache;
   int mmx;
   int freq;
   int ssx;
   int wni;
} tstIntelCpuId;

extern int tst_has_cpuid( void );
extern void tst_get_pentium_ident( tstIntelCpuId* );

static cpu_enum GetProcessorId(void)
{
    tstIntelCpuId cpu;
    if( tst_has_cpuid() )
    {
        tst_get_pentium_ident( &cpu );

        if( 15 == cpu.family && cpu.wni ) return CPU_W7;
        if(  6 == cpu.family ) {
            if( cpu.ssx ) return CPU_A6;
            if( cpu.mmx ) return CPU_M6;
        }
        else if( 5 == cpu.family ) return cpu.mmx ? CPU_M5 : CPU_PX;
    }
    return CPU_PX;
}


/* //////////////////////////////////////////////////////////////////////
// Name:       smart_LoadLibrary
// Purpose:    try to load DLL library
// Context:    IPLib dispatcher of DLLs
// Returns:    instance of the loaded library or NULL
// Parameters: void
//
//  Notes:     
      Load library use "waterfall" mechanism
*/
static HINSTANCE smart_LoadLibrary(void) {

   HINSTANCE hLib = NULL;
   char buf[256] = "";
   int i;

   /* what cpu is here. In the worse case PX version is used */
   cpu_enum cpu = GetProcessorId();

   /* some processor could work with DLL for old cpus, get pointer to list */
   const dll_enum* dllList = dllUsage[ cpu ];

   /* always waterfall, try to load an other available DLL from the list */
   for( i=0; dllList[i] != DLL_NOMORE; i++ ) {
      /* try to load another library */
      if( NULL != (hLib = LoadLibrary( dllNames[ dllList[i] ] ))) 
         return hLib;                        /* SUCCESS EXIT */
   }

   /* if not found, then failed with error message */
   lstrcpy( buf, " No IPLib DLL was found in the Waterfall procedure" );
   MessageBeep( MB_ICONSTOP );
   MessageBox( 0, buf, LOAD_DLL_ERR, MB_ICONSTOP | MB_OK );
   return NULL;
}

/*****************************************************************
* DLL Main Entry Point, get function addresses at init
******************************************************************
*/

BOOL WINAPI DLLMAIN(HINSTANCE hinstDLL, DWORD fdwReason,
   LPVOID lpvReserved)
{
   static HMODULE  hLibModule = NULL;

   switch (fdwReason) {
      case DLL_PROCESS_ATTACH:
         hLibModule = smart_LoadLibrary();
         if( !hLibModule ) return FALSE;
         if( !LoadFunctions(hLibModule) ) return FALSE;
         break;
      case DLL_THREAD_ATTACH: break;
      case DLL_THREAD_DETACH: break;
      case DLL_PROCESS_DETACH:
         if (hLibModule) {
            FreeLibrary(hLibModule);
         }
         break;
      default:
         break;
   }
   return TRUE;
}

/*****************************************************************
* Find the function address for each function from respective
* processor specific DLLs
******************************************************************
*/
static int LoadOneFunction(HMODULE hLibModule,const void* func,
   char* funcname)
{
   FARPROC *funcadr=(FARPROC*)func;
   (*funcadr)=GetProcAddress(hLibModule,funcname);
   if (!(*funcadr)) {
      char msg[128];
      wsprintf(msg, "Unable to find function address %s\n", funcname);
      MessageBeep(MB_ICONSTOP);
      MessageBox(0, msg, LOAD_DLL_ERR, MB_ICONSTOP | MB_OK
         | MB_TASKMODAL);
      return FALSE;
   }
   return TRUE;
}

/*****************************************************************
* Called at DLL load time, get all the import entry address
* Loop through the table
******************************************************************
*/
static int LoadFunctions(HMODULE hLibModule)
{
   int i=0;
   while ((USER_Desc[i].FuncAdr) && (USER_Desc[i].FuncName)) {
      if (!LoadOneFunction(hLibModule, USER_Desc[i].FuncAdr, USER_Desc[i].FuncName))
         return 0;
      i++;
   }
   return TRUE;
}

#else  /* !USER_W32PCS */

/* get the DLL names */
#define __USERNAME__
#include "UserDll.h"
#undef __USERNAME__

#include <windows.h>

static DWORD s_dwTlsIndex = TLS_OUT_OF_INDEXES;

void* __cdecl iplGetContext() {

   void *pContext = TlsGetValue( s_dwTlsIndex );
   if( NULL == pContext )  {
      pContext = (LPVOID)LocalAlloc( LPTR, iplSizeOfContext() );
      if( NULL == pContext )
         FatalAppExit( 0,
               "Problem to allocate memory for TLS IPL context." );

      iplInitContext (pContext);
      TlsSetValue( s_dwTlsIndex, pContext );
   }
   return pContext;
}

BOOL WINAPI DLLMAIN(HINSTANCE hinstDLL,           /* DLL module handle        */
                        DWORD     fdwReason,      /* reason called            */
                        LPVOID    lpvReserved) {  /* reserved                 */

   void * pContext;

   switch (fdwReason) {

   case DLL_PROCESS_ATTACH:

      s_dwTlsIndex = TlsAlloc();
      if( s_dwTlsIndex == TLS_OUT_OF_INDEXES ) return FALSE;

      /* No break: Initialize the index for first thread. */
      /* The attached process creates a new thread. */

   case DLL_THREAD_ATTACH:

      pContext = (LPVOID)LocalAlloc( LPTR, iplSizeOfContext() );
      if( pContext == NULL) return FALSE;
      iplInitContext (pContext);
      TlsSetValue( s_dwTlsIndex, pContext );
      break;

   case DLL_THREAD_DETACH:

      if( s_dwTlsIndex != TLS_OUT_OF_INDEXES ) {
         pContext = TlsGetValue( s_dwTlsIndex );
         if( pContext != NULL ) LocalFree( (HLOCAL) pContext );
      }
      break;

   case DLL_PROCESS_DETACH:

      if( s_dwTlsIndex != TLS_OUT_OF_INDEXES ) {
         pContext = TlsGetValue( s_dwTlsIndex );
         if( pContext != NULL ) LocalFree( (HLOCAL) pContext );
         TlsFree( s_dwTlsIndex );
      }
      break;

    default:
        hinstDLL;
        lpvReserved;
        break;
   }
   return TRUE;
}

#endif /* USER_W32PCS  */
