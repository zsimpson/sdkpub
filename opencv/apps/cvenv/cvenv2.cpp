/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "tcl.h"
#include "tk.h"

#ifndef WIN32
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#endif

//#include <string>
//using namespace std;

#ifdef WIN32
#include <windows.h>

#define PIPESIZE 100

PROCESS_INFORMATION pi;

HANDLE g_hReadPipe = NULL;
HANDLE g_hWritePipe = NULL;
HANDLE g_hErrReadPipe = NULL;
HANDLE g_hErrWritePipe = NULL;
HANDLE g_hInputReadPipe = NULL;
HANDLE g_hInputWritePipe = NULL;

#else
static char home_path[200];
#endif

char cmd[300];
char* g_pchBuf = NULL;

void	MainEx(int argc, char **argv, Tcl_AppInitProc *pfappInitProc, Tcl_Interp *pintrp,
               char *pchfileName);
int		Tcl_AppInit(Tcl_Interp *pintrp);
void	Panic (Tcl_Interp * pintrp, const char * pch);
void    WishPanic TCL_VARARGS_DEF(char *,arg1);

#include "colorer.h"
#include "cvenv.h"

//string g_sCfgFile = "colors.cfg";

bool g_bNonStop = true;
bool g_bRun = false;

/*
 *----------------------------------------------------------------------
 *
 * Commands routines.
 *
 * Results:
 *  TCL_OK - if sucsess, or TCL_ERROR
 *
 *----------------------------------------------------------------------
 */

static char* module_path;

static char* GetPathFromModuleName( char* modulename )
{
    int i;
    if( !modulename )
        return 0;
#ifndef WIN32
    /* if module is link find real path */
    int  len;
    char real[1000];
    strcpy( real, modulename );
    while( (len = readlink( real, real, 1000 )) > 0 )
        real[len] = 0;
    char* path = (char*)malloc( strlen( real ) + 10 );
    strcpy( path, real );
#else
    char* path = (char*)malloc( strlen( modulename ) + 10 );
    strcpy( path, modulename );
#endif

    for( i = strlen( path ) - 1;
         i > 0 && path[i] != '\\' && path[i] != '/';
         i-- );

    if( i <= 0 )
    {
        path[0] = '.';
        i = 1;
    }

    path[i] = '/';
    path[i + 1] = 0;

#ifdef WIN32
    for( i = 0; i < (int)strlen( path ); i++ )
        if( path[i] == '\\' )
            path[i] = '/';
#endif

    return path;
}

int _LoadColors (ClientData cd, Tcl_Interp *pintrp,
    int argc, char **argv)
{
    
	char fn[300];
#ifdef WIN32
    strcat( strcpy( fn, module_path ), "/colors.tcl" );
#else
	strcat( strcpy( fn, home_path ), "/.cvenv/colors.tcl" );
#endif
    LoadColors( pintrp, fn );
    return TCL_OK;
}

int _SaveColors (ClientData cd, Tcl_Interp *pintrp,
    int argc, char **argv)
{
    char fn[300];
#ifdef WIN32
    strcat( strcpy( fn, module_path ), "/colors.tcl" );
#else
	strcat( strcpy( fn, home_path ), "/.cvenv" );
    mkdir( fn, 0700 );
    strcat( fn, "/colors.tcl" );
#endif
    SaveColors( pintrp, fn );
    return TCL_OK;
}

static int finished = 0;
static int started = 0;
static char* buffer = 0;
static char* errbuffer = 0;

#ifdef WIN32
CRITICAL_SECTION  mutex;

DWORD WINAPI ErrReaderFun (LPVOID pvParam)
{
    DWORD cchReadBuffer,cchErrReadBuffer,counter = 0;  /* number of bytes read or to be written */

    char * chErrReadBuffer = (char*)malloc( PIPESIZE + 1 );  /* pipe read buffer */

    while( ReadFile( g_hErrReadPipe, chErrReadBuffer, PIPESIZE, &cchErrReadBuffer, 0 ) )
    {
        counter++;
        chErrReadBuffer[cchErrReadBuffer] = 0;
        EnterCriticalSection( &mutex );
        if(!errbuffer)
        {
            errbuffer = (char*)malloc( strlen( chErrReadBuffer ) + 1 );
            strcpy( errbuffer, chErrReadBuffer );
        }
        else
        {
            errbuffer = (char*)realloc( errbuffer, strlen( errbuffer ) + strlen( chErrReadBuffer ) + 2 );
            strcat( errbuffer, chErrReadBuffer );
        }
        LeaveCriticalSection( &mutex );
    }

    free(chErrReadBuffer);
return 0;
}

DWORD WINAPI ReaderFun (LPVOID pvParam)
{
    char* comline = (char*)pvParam;
    
    //-----------------------------------------------------------------------
    BOOL bOk;  /* BOOL return code for APIs */
    
    DWORD cchReadBuffer,cchErrReadBuffer,counter = 0;  /* number of bytes read or to be written */
    STARTUPINFO si;  /* for CreateProcess call */
    SECURITY_ATTRIBUTES saPipe,saErrPipe;  /* security for anonymous pipe */
    DWORD  retCode;                     // Used to trap return codes.
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    /* set up the security attributes for the anonymous pipe */
    saPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
    saPipe.lpSecurityDescriptor = NULL;
    saErrPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
    saErrPipe.lpSecurityDescriptor = NULL;

    /* In order for the child to be able to write to the pipe, the handle */
    /* must be marked as inheritable by setting this flag: */
    saPipe.bInheritHandle = TRUE;
    saErrPipe.bInheritHandle = TRUE;
    //-----------------------------------------------------------------------
  
    bOk = CreatePipe(&g_hReadPipe,
                     &g_hWritePipe,
                     &saPipe,      
                     PIPESIZE);    
    
    if (!bOk)
    {
            retCode = GetLastError();
            printf("Reader: Can't create STDOUT pipe, Error #%d\n",GetLastError());
            return 0;
    }

    bOk = CreatePipe(&g_hErrReadPipe,
                     &g_hErrWritePipe,
                     &saErrPipe,
                     PIPESIZE);
    
    if (!bOk)
    {
            retCode = GetLastError();
            printf("Reader: Can't create STDERR pipe, Error #%d\n",GetLastError());
            return 0;
    }

    bOk = CreatePipe(&g_hInputReadPipe,
                     &g_hInputWritePipe,
                     &saErrPipe,
                     PIPESIZE);
    
    if (!bOk)
    {
            retCode = GetLastError();
            printf("Reader: Can't create STDIN pipe, Error #%d\n",GetLastError());
            return 0;
    }

    
    /* Set up the STARTUPINFO structure for the CreateProcess() call */
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);    
    //si.hStdError = si.hStdOutput = g_hWritePipe;
    //si.dwFlags = STARTF_USESTDHANDLES;
    
    //Out//
    //si.hStdOutput = g_hWritePipe; /* write end of the pipe */
    //si.dwFlags = STARTF_USESTDHANDLES;

    char buf[1000] ="";
    char ln[300];
    strcpy( buf, module_path );
    strcat( buf, comline );
    sprintf(ln," %u",g_hWritePipe);
    strcat( buf, ln );
    sprintf(ln," %u",g_hErrWritePipe);
    strcat( buf, ln );
    sprintf(ln," %u",g_hInputReadPipe);
    strcat( buf, ln );

    
    /* Now create the child process, inheriting handles */
    bOk = CreateProcess(NULL,       /* filename */
                        buf,        /* full command line for child */
                        NULL,       /* process security descriptor */
                        NULL,       /* thread security descriptor */
                        TRUE,       /* inherit handles? Also use if STARTF_USESTDHANDLES */
                        /*DETACHED_PROCESS*/0,          /* creation flags */ //Out// 0
                        NULL,       /* inherited environment address */
                        NULL,       /* startup dir; NULL = start in current */
                        &si,        /* pointer to startup info (input) */
                        &pi);       /* pointer to process info (output) */

    CloseHandle( g_hWritePipe ); g_hWritePipe = NULL;
    CloseHandle( g_hErrWritePipe ); g_hErrWritePipe = NULL;
    CloseHandle( g_hInputReadPipe ); g_hInputReadPipe = NULL;

    started = 1;
    
    char * chReadBuffer = (char*)malloc( PIPESIZE + 1 );  /* pipe read buffer */
    
    DWORD tid;
    CloseHandle(CreateThread(NULL, 0, ErrReaderFun,
                             NULL, 0, &tid));

    while( ReadFile( g_hReadPipe, chReadBuffer, PIPESIZE, &cchReadBuffer, 0 ) )
    {
        chReadBuffer[cchReadBuffer] = 0;
        EnterCriticalSection( &mutex );
        if(!buffer)
        {
            buffer = (char*)malloc( strlen( chReadBuffer ) + 1 );
            strcpy( buffer, chReadBuffer );
        }
        else
        {
            buffer = (char*)realloc( buffer, strlen( buffer ) + strlen( chReadBuffer ) + 2 );
            strcat( buffer, chReadBuffer );
        }
        LeaveCriticalSection( &mutex );
    }

    free(chReadBuffer);
    finished = 1;
    //--------------------------------------------------
    printf("ReaderID: I finish myself\n");
    //--------------------------------------------------

    return 0;
}
#else

char** global_argv;
int    global_argc;
int    main_seance( int argc, char** argv );

static pid_t child;
static pthread_mutex_t mutex;
static int fd[2];
static int err[2];
static int fdi[2];

static void* errrun_process( void* a )
{
    int nbytes;
    char buff[100];
    while( (nbytes = read( err[0], buff, sizeof(errbuffer) )) > 0 )
    {
        buff[nbytes] = 0;
        pthread_mutex_lock( &mutex );
        if( !errbuffer )
        {
            errbuffer = (char*)malloc( strlen( buff ) + 1 );
            errbuffer[0] = 0;
        }
        else
            errbuffer = (char*)realloc( errbuffer, strlen( errbuffer ) + strlen( buff ) + 2 );
        strcat( errbuffer, buff );
        pthread_mutex_unlock( &mutex );
    }
    
    close( err[0] );

    return 0;
}

static void* run_process( void* a )
{
    char* argv = (char*)a;
    // creating pipe for interproc communications
    pipe( fd );
    pipe( err );
    pipe( fdi );
    
    // creating child process
    if( (child = fork()) == -1 )
    {
        printf( "can't fork\n" );
        exit( 1 );
    }

    if( !child )
    {
        /* we are in child process */
        char pip[100];
        char errp[100];
        char pipi[100];
        sprintf( pip, "%d", fd[1] );
        sprintf( errp, "%d", err[1] );
        sprintf( pipi, "%d", fdi[0] );
        close( fd[0] );
        close( err[0] );
        close( fdi[1] );
        char* _argv[] = {global_argv[0], argv, pip, errp, pipi,0};
        main_seance( 5, _argv );
        close( fd[1] );
        close( err[1] );
        close( fdi[0] );
        exit( 0 );
    }
    else
    {
        // we are in parent process
        close( fd[1] );
        close( err[1] );
        close( fdi[0] );
        char buff[100];

        pthread_t thread;
        pthread_create( &thread, 0, errrun_process, 0 );
    
        int nbytes;
        while( (nbytes = read( fd[0], buff, sizeof(buffer) )) > 0 )
        {
            buff[nbytes] = 0;
            pthread_mutex_lock( &mutex );
            if( !buffer )
            {
                buffer = (char*)malloc( strlen( buff ) + 1 );
                buffer[0] = 0;
            }
            else
                buffer = (char*)realloc( buffer, strlen( buffer ) + strlen( buff ) + 2 );
            strcat( buffer, buff );
            pthread_mutex_unlock( &mutex );
        }

        close( fd[0] );
        finished = 1;
        wait( 0 );
    }
    
    return 0;
}
#endif

static char filename[1000];

int InputData (ClientData, Tcl_Interp *interp,
    int, char **argv)
{

#ifdef WIN32
    if (g_hInputWritePipe)
#else
    if( fdi[1] )
#endif
    {
        char* data =  Tcl_GetVar(interp, "CVEnv::inputdata", TCL_GLOBAL_ONLY);
            
        if (*data)
        {
            size_t len = strlen( data );
            unsigned long num;

#           ifdef WIN32
                WriteFile(g_hInputWritePipe,
                        (LPCVOID) data,
                        len,
                        &num,
                        NULL);
#           else
                write( fdi[1], data, len );
#           endif
        
        }
    }
    return TCL_OK;
}

int Execute_Command (ClientData, Tcl_Interp *interp,
    int, char **argv)
{
    Tcl_Eval(interp,
        "$CVEnv::tb.bbox3.b0 configure -state disable -relief link\n"
        "$CVEnv::tb.bbox3.b1 configure -state active -relief link\n"
        //"$CVEnv::tb.bbox3.b1 _leave\n"
        );

#ifdef WIN32
    DWORD tid;
    strcpy(cmd , "seance ");
    strcat(cmd, argv[1] );
    CloseHandle(CreateThread(NULL, 0, ReaderFun,
                             cmd, 0, &tid));
#else
    strcpy( filename, argv[1] );
    pthread_t thread;
    pthread_create( &thread, 0, run_process, filename );
#endif
    
    return TCL_OK;
}


int Stop_Command (ClientData, Tcl_Interp *interp, int, char**)
{   
    Tcl_Eval(interp,
        "$CVEnv::tb.bbox3.b1 configure -state disable -relief link\n"
        "$CVEnv::tb.bbox3.b0 configure -state active -relief link\n"
        //"$CVEnv::tb.bbox3.b0 _leave"
	    );

#ifdef WIN32
    if (TerminateProcess(pi.hProcess,1))
        return TCL_OK;
    else return TCL_ERROR;
#else
    if( kill( child, 9 ) )
    {
        printf( "kill error\n" );
    }
    return TCL_OK;
#endif
}

////////////////////////////////////////////////////////////////////////

/*
 *----------------------------------------------------------------------
 *
 * Commands_Init --	Commands initialisation routine.
 *
 * Results:
 *	TCL_OK - if sucsess, or TCL_ERROR
 *
 *----------------------------------------------------------------------
 */
int
Commands_Init(Tcl_Interp *interp)
{
    Tcl_CreateCommand (interp, "pExecute", Execute_Command,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pStop", Stop_Command,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pLoadColors", _LoadColors,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSaveColors", _SaveColors,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pParsebegin", ParseTextBegin,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pParseend", ParseTextEnd,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pInput", InputData,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);

    return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * MainEx -- Main program for Tk-based applications.
 *
 *----------------------------------------------------------------------
 */
void
MainEx( int argc, char** argv, Tcl_AppInitProc *appInitProc,
        Tcl_Interp *pintrp, char *fileName )
{
#ifndef WIN32
    global_argv = argv;
    global_argc = argc;
#endif

    int code;

    (*appInitProc)(pintrp);

    if ( Commands_Init(pintrp) != TCL_OK) 
        Panic (pintrp,"Can't initialise commands!");

    //if (!LoadColors(pintrp,string("colors.tcl")))
    //    Panic (pintrp,"Can't load config file!");
    
    char set_path[1000];
    strcat( strcat( strcpy( set_path, "set ::image_path \"" ), module_path ), "\"" );
    code = Tcl_Eval( pintrp, set_path );
    
	if (fileName != NULL) 
    {
        char  script[1000];
        strcat( strcat( strcpy( script, module_path ), "" ), fileName );
        code = Tcl_EvalFile(pintrp, script);
        if (code != TCL_OK)
            Panic (pintrp,"Evaluate file error!");
    }
    else Tcl_SourceRCFile(pintrp);

    Tcl_ResetResult(pintrp);
    
#ifdef WIN32
    InitializeCriticalSection( &mutex );
#else
    pthread_mutex_init( &mutex, 0 );
#endif
    
    while( Tk_GetNumMainWindows() > 0 )
    {
        while( Tcl_DoOneEvent( TCL_DONT_WAIT ) );
        
#ifdef WIN32
        EnterCriticalSection( &mutex );
#else
        pthread_mutex_lock( &mutex );
#endif
        if( buffer )
        {
            char* pchcom = (char*)malloc( strlen( buffer ) + 1000 );
            strcpy(pchcom , "set outputText \"");
            strcat(pchcom , (const char*)buffer);
            strcat(pchcom , "\"\n");
            //strcat(pchcom , "$CVEnv::outtx configure -state normal\n");
            strcat(pchcom , "$CVEnv::outtx insert end $outputText\n");
            //strcat(pchcom , "$CVEnv::outtx configure -state disabled\n");
            strcat(pchcom , "$CVEnv::outtx see \"end -1 lines\"\n");
            strcat(pchcom , "unset outputText\n");
            Tcl_Eval( pintrp, pchcom );
            free( pchcom );

            free( buffer );
            buffer = 0;
        }

        if( errbuffer )
        {
            char* pchcom = (char*)malloc( strlen( errbuffer ) + 1000 );
            strcpy(pchcom , "set errText \"");
            strcat(pchcom , (const char*)errbuffer);
            strcat(pchcom , "\"\n");
            //strcat(pchcom , "$CVEnv::outtx configure -state normal\n");
            strcat(pchcom , "$CVEnv::parsetx insert end $errText\n");
            //strcat(pchcom , "$CVEnv::outtx configure -state disabled\n");
            strcat(pchcom , "$CVEnv::parsetx see \"end -1 lines\"\n");
            strcat(pchcom , "unset errText\n");
            Tcl_Eval( pintrp, pchcom );
            free( pchcom );

            free( errbuffer );
            errbuffer = 0;
        }

        if( finished )
        {
            finished = 0;
            Tcl_Eval(pintrp,
                    "$CVEnv::tb.bbox3.b1 configure -state disable -relief link\n"
                    "$CVEnv::tb.bbox3.b0 configure -state active -relief link\n"
                    //"$CVEnv::tb.bbox3.b0 _leave"
	                );

#ifdef WIN32
            CloseHandle( g_hReadPipe ); g_hReadPipe = NULL;
            CloseHandle( g_hErrReadPipe ); g_hErrReadPipe = NULL;
            CloseHandle( g_hInputWritePipe ); g_hInputWritePipe = NULL;
#else
#endif
	    }
#ifdef WIN32
        LeaveCriticalSection( &mutex );
        Sleep( 1 );
#else
        pthread_mutex_unlock( &mutex );
        usleep( 100 );
#endif
    }
    Tcl_DeleteInterp(pintrp);
    return;
}


/*
 *----------------------------------------------------------------------
 *
 * WishPanic -- escape function.
 *
 *----------------------------------------------------------------------
 */

void WishPanic TCL_VARARGS_DEF(char *,arg1)
{
    va_list argList;
    char buf[1024];
    char *format;

    format = TCL_VARARGS_START(char *,arg1,argList);
    printf(buf, format, argList);
}

/*
 *----------------------------------------------------------------------
 *
 * Panic -- error output & exit function.
 *
 *----------------------------------------------------------------------
 */

void Panic (Tcl_Interp * pintrp, const char * pch)
{
    printf("Thread %P:",Tcl_GetCurrentThread());
	printf(pch);
	printf("\n    Reason:");
	printf(pintrp->result);
	printf("\n");

	Tcl_DeleteInterp(pintrp);
    Tcl_Exit(1);
}

/*
 *----------------------------------------------------------------------
 *
 * Tcl_AppInit -- Initialisation function.
 *
 *----------------------------------------------------------------------
 */

int Tcl_AppInit(Tcl_Interp *pintrp)
{

    if (Tcl_InitStubs(pintrp, TCL_VERSION, 1) == NULL)
        Panic (pintrp,"Tcl stub's initialisation failed!");
        
	if (Tcl_Init(pintrp) == TCL_ERROR)
	    Panic (pintrp,"Tcl's initialisation failed!");
	
    if (Tk_Init(pintrp) == TCL_ERROR)
        Panic (pintrp,"Tk's initialisation failed!");
// in unix disable multythread support
    return TCL_OK;
}

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    module_path = GetPathFromModuleName( argv[0] );

#ifndef WIN32
    if( argc == 2 )
        main_seance( argc, argv );

	char* hdir = getenv( "HOME" );
	if( hdir )
		strcpy( home_path, hdir );
#endif

    Tcl_Interp* g_pInterp = Tcl_CreateInterp();
	
	Tcl_SetPanicProc(WishPanic);
    Tcl_FindExecutable(argv[0]);

    MainEx(argc, argv, Tcl_AppInit, g_pInterp, "cvenv.tcl");

    Tcl_DeleteInterp(g_pInterp);

    return 0;
}

