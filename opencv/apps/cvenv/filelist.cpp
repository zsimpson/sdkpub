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

/* this file contains platform-depended code (parse dll, */
/* getting file list e.t.c.)                             */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eic.h"
#include "filelist.h"

#undef malloc
#undef realloc
#undef free

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

char* GetPathFromModuleName( char* modulename )
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


/* path - path to module (in)       */
/* headers - array of headers (out) */
/* libs - array of libs (out)       */
int GetFileList( char* path, char*** headers,  int* header_num,
                             char*** headpath, int* headpath_num,
                             char*** libs,     int* lib_num )
{
    if( !path )
        return -1;

    if( libs )
        *libs = 0;
    if( lib_num )
        *lib_num = 0;
    if( headpath_num )
        *headpath_num = 0;

    char init[1000];
    char root[1000];
    strcpy( init, path );

    /* adding last '/' if needed */
    int len = strlen( init );
    if( len )
    {
        if( len && init[len - 1] != '\\' && init[len - 1] != '/' )
            strcat( init, "/" );
    }
    else
        strcpy( init, "/" );
    strcpy( root, init );

#ifdef WIN32
    strcat( init, "plugins.cfg" );
#else
    strcat( init, "plugins.conf" );
#endif

    int    nlp = 0;
    int    nip = 0;
    int    nl  = 0;
    int    ni  = 0;

    /* open config file */
    FILE* cfg = fopen( init, "rb" );
    if( cfg )
    {
        /* reading */
        fseek( cfg, 0, SEEK_END );
        int size = ftell( cfg );
        fseek( cfg, 0, SEEK_SET );

        char* buffer = (char*)malloc( size + 2 );
        fread( buffer, 1, size, cfg );
        buffer[size] = 0;

        /* parsing */
        char** lpath = (char**)malloc( 1 );
        char** ipath = (char**)malloc( 1 );
        char** incl  = (char**)malloc( 1 );
        char** lib   = (char**)malloc( 1 );
        char   what[100];
        char   where[1000];

        int    i;
        for( i = 0; i < size; )
        {
            /* get string */
            int j;
            for( j = i; buffer[j] <= ' ' && j < size; j++ );
            i = j;
            if( i >= size )
                break;
            for( j = i; buffer[j] != 0xa && buffer[j] != 0xd && j < size; j++ );
            buffer[j] = 0;

            if( buffer[i] == '#' )
            {
                i = j;
                continue;
            }

            what[0] = 0;
            where[0] = 0;
            sscanf( buffer + i, "%s %s", what, where );
            if( !strcmp( what, "include" ) )
            {
                incl = (char**)realloc( incl, sizeof( *incl ) * (ni + 1) );
                incl[ni] = (char*)malloc( strlen( where ) + 1 );
                strcpy( incl[ni], where );
                ni++;
            }
            else if( !strcmp( what, "incpath" ) )
            {
                ipath = (char**)realloc( ipath, sizeof( *ipath ) * (nip + 1) );
                ipath[nip] = (char*)malloc( strlen( root ) + strlen( where ) + 1 );
                ipath[nip][0] = 0;
    #ifdef WIN32
                if( where[1] != ':' )
    #else
                if( where[0] != '/' )
    #endif
                    strcpy( ipath[nip], root );
                strcat( ipath[nip], where );
                nip++;
            }
            else if( !strcmp( what, "libpath" ) )
            {
                lpath = (char**)realloc( lpath, sizeof( *lpath ) * (nlp + 1) );
                lpath[nlp] = (char*)malloc( strlen( root ) + strlen( where ) + 1 );
                lpath[nlp][0] = 0;
    #ifdef WIN32
                if( where[1] != ':' )
    #else
                if( where[0] != '/' )
    #endif
                    strcpy( lpath[nlp], root );
                strcat( lpath[nlp], where );
                nlp++;
            }
            else if( !strcmp( what, "library" ) )
            {
                int found = 0;
    #ifdef WIN32
                if( where[1] != ':' )
    #else
                if( where[0] != '/' )
    #endif
                    for( int i = 0; i < nlp; i++ )
                    {
                        char findlib[1000];
                        strcpy( findlib, lpath[i] );
                        strcat( findlib, "/" );
                        strcat( findlib, where );
                        FILE* lb = fopen( findlib, "rb" );
                        if( lb )
                        {
                            lib = (char**)realloc( lib, sizeof( *lib ) * (nl + 1) );
                            lib[nl] = (char*)malloc( strlen( findlib ) + 1 );
                            strcpy( lib[nl], findlib );
                            nl++;
                            fclose( lb );
                            found = 1;
                            break;
                        }
                    }
                else
                {
                    FILE* lb = fopen( where, "rb" );
                    if( lb )
                    {
                        lib = (char**)realloc( lib, sizeof( *lib ) * (nl + 1) );
                        lib[nl] = (char*)malloc( strlen( where ) + 1 );
                        strcpy( lib[nl], where );
                        nl++;
                        fclose( lb );
                        found = 1;
                        break;
                    }
                }
                if( !found )
                {
                    char tmp[1000];
                    sprintf( tmp, "Library %s hasn't been found\n", where );
                    ErrorOutput( tmp );
                }
            }

            i = j;
        }

        if( headers && ni )
            *headers = incl;
        else
        {
            for( int i = 0; i < nip; i++ )
                free( incl[i] );
            free( incl );
        }

        if( libs && nl )
            *libs = lib;
        else
        {
            for( int i = 0; i < nl; i++ )
                free( lib[i] );
            free( lib );
        }

        if( headpath && nip )
            *headpath = ipath;
        else
        {
            for( int i = 0; i < nip; i++ )
                free( ipath[i] );
            free( ipath );
        }

        for( i = 0; i < nlp; i++ )
            free( lpath[i] );
        free( lpath );

        fclose( cfg );
        free( buffer );
    }
    if( header_num )
        *header_num = ni;
    if( headpath_num )
        *headpath_num = nip;
    if( lib_num )
        *lib_num = nl;

    return 0;
}


#define MakePtr(cast,ptr,addValue) (cast)((DWORD)(ptr)+(DWORD)(addValue))

static int GetExportList( char* filename, char*** names )
{
#ifdef WIN32
    HANDLE file = CreateFile( filename,
                              GENERIC_READ,
                              FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                              0,
                              OPEN_EXISTING,
                              0,
                              0 );

    if( file == INVALID_HANDLE_VALUE )
        return 0;

    unsigned long filesize;
    unsigned long read;
    char* buffer = (char*)malloc( filesize = SetFilePointer( file, 0, 0, FILE_END ) );
    SetFilePointer( file, 0, 0, FILE_BEGIN );
    BOOL res = ReadFile( file, buffer, filesize, &read, 0 );
    CloseHandle( file );
    if( !res )
    {
        free( buffer );
        return 0;
    }

    PIMAGE_EXPORT_DIRECTORY exportDir;
    PIMAGE_SECTION_HEADER header;
    PIMAGE_NT_HEADERS pNTHeader;
    PIMAGE_DOS_HEADER pDosHdr;
    int delta;
    int i;
    char** name;
    unsigned int exportsStartRVA, exportsEndRVA;
    unsigned int base;
    char* pfile;
    int num;

    pfile = buffer;

    pDosHdr = (PIMAGE_DOS_HEADER)pfile;
    base = (DWORD)pfile;

    pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
                        pfile,pDosHdr->e_lfanew);

    exportsStartRVA =
        pNTHeader->OptionalHeader.DataDirectory
        [IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;


    exportsEndRVA = exportsStartRVA + pNTHeader->OptionalHeader.DataDirectory
        [IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

    // Get the IMAGE_SECTION_HEADER that contains the exports.  This is
    // usually the .edata section, but doesn't have to be.
    
    PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);
    
    header = 0;
    
    for ( i=0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++ )
    {
        // Is the RVA within this section?
        if ( (exportsStartRVA >= section->VirtualAddress) &&
            (exportsStartRVA < (section->VirtualAddress + section->Misc.VirtualSize)))
            header =  section;
    }
    
    if ( !header )
    {
        printf( "No Exports Table Found\n" );
        free( buffer );
        return 0;
    }
    
    delta = (INT)(header->VirtualAddress - header->PointerToRawData);
    exportDir = MakePtr(PIMAGE_EXPORT_DIRECTORY, base,
        exportsStartRVA - delta);
    
    name = (PSTR *)((DWORD)exportDir->AddressOfNames - delta + base);
    
    exportDir = MakePtr(PIMAGE_EXPORT_DIRECTORY, base,
        exportsStartRVA - delta);
    
    *names = (char**)malloc( (exportDir->NumberOfNames + 1) * sizeof(char*) );
    
    for ( unsigned int j = 0; j < exportDir->NumberOfNames; j++ )
    {
        (*names)[j] = (char*)malloc( strlen( name[j] - delta + base ) + 1 );
        strcpy( (*names)[j], name[j] - delta + base );
    }
    
    num = exportDir->NumberOfNames;
    free( buffer );
    
    return num;
#else
    char* command = (char*)malloc( strlen( filename ) + 100 );
    strcat( strcat( strcpy( command, "nm " ), filename ), " | grep \" T \"" );
    FILE* exp = popen( command, "r" );
    int r;
    int size = 0;
    char buffer[1000];
    char* file = (char*)malloc( 1 );
    while( (r = fread( buffer, 1, 1000, exp ) ) > 0 )
    {
        file = (char*)realloc( file, size + r );
        memcpy( file + size, buffer, r );
        size += r;
    }
    pclose( exp );

    (*names) = (char**)malloc( 1 );
    int num = 0;
        
    for( int i = 0; i < size; )
    {
        /* get string */
        int j;
        for( j = i; file[j] <= ' ' && j < size; j++ );
        i = j;
        if( i >= size )
            break;
        for( j = i; file[j] != 0xa && file[j] != 0xd && j < size; j++ );
        file[j] = 0;

        char entry[1000];
        char type[1000];
        char name[1000];

        sscanf( file + i, "%s %s %s", entry, type, name );
        (*names) = (char**)realloc( *names, sizeof(**names) * (num + 1) );
        (*names)[num] = (char*)malloc( strlen( name ) + 1 );
        strcpy( (*names)[num], name );
//        printf( "%s\n", (*names)[num] );
        num++;
        i = j;
    }
    free( file );
    return num;
#endif
}

int AddLibrary( char* path )
{
#ifdef WIN32
    HMODULE lib;
#else
    void*   lib;
#endif
    int funcs;
    char** exports;

    if( (funcs = GetExportList( path, &exports )) == 0 )
    {
        return -1;
    }

#ifdef WIN32
    if( (lib = LoadLibrary( path )) == 0 )
#else
    if( (lib = dlopen( path, RTLD_LAZY )) == 0 )
#endif
        return -1;

    for( int i = 0; i < funcs; i++ )
    {
#ifdef WIN32
        void* func = GetProcAddress( lib, exports[i] );
#else
        void* func = dlsym( lib, exports[i] );
#endif
        if( func )
            AddExternFunction( func, exports[i] );
        free( exports[i] );
    }

    //AddWrappers();

    free( exports );

    return 0;
}

//-----------------------------------------------------------------------------

extern "C" int _eicUprintf(int (*output)(...), char **arg, char *fmt, arg_list ap);
extern "C" int _eicUscanf (int (*input)(...) , int (*uget)(...) ,
                           char **arg, const char *fmt, arg_list ap);
extern "C" int charout_(int c, char *buf);
extern "C" int charin_(char *buf);
extern "C" int charback_(int ch, char **buf);
typedef int(*put_t)(...);
//typedef int(*put0_t)();
#ifdef WIN32
static HANDLE g_hWritePipe = 0;
static HANDLE g_hErrorPipe = 0;
static HANDLE g_hInputPipe = 0;
#else
static int g_hWritePipe = 0;
static int g_hErrorPipe = 0;
static int g_hInputPipe = 0;
#endif

static VaL output_printf( )
{
    VaL val;
    val_t v;
    unsigned long num;
    arg_list ag = getargs();

    char* g_pchBuf = (char*) malloc( 0xF000 );
    memset( g_pchBuf, 0, 0xF000 );
    char* fmt = (char*) nextarg(ag,ptr_t).p;

    v.ival = val.ival = _eicUprintf((put_t)charout_, &g_pchBuf, fmt, ag);

    
    //console outout//v.ival = val.ival = _eicUprintf((put_t)fputc,stdout,fmt,ag);
    
    if( g_hWritePipe )
#ifdef WIN32
        WriteFile(g_hWritePipe,
                  (LPCVOID) g_pchBuf,
                  val.ival,
                  &num,
                  NULL);
#else
    write( g_hWritePipe, g_pchBuf, val.ival );
#endif
    else
        printf( "%s", g_pchBuf );

    free( g_pchBuf );
    return val;
}

static VaL input_scanf()
{
    VaL val;
    val_t v;
    unsigned long num;
    arg_list ag = getargs();

    char* g_pchBuf = (char*)malloc( 0xF000 );
    char* _pchBuf = g_pchBuf;
    memset( g_pchBuf, 0, 0xF000 );

    if( g_hInputPipe )
#ifdef WIN32
    {
        ReadFile(g_hInputPipe,
                  (LPVOID) g_pchBuf,
                  255,
                  &num,
                  NULL);
    
        g_pchBuf[num] = '\n';
    
        WriteFile(g_hWritePipe,
                  (LPVOID) g_pchBuf,
                  num+1,
                  &num,
                  NULL);
    }
#else
    num = read( g_hInputPipe, g_pchBuf, 255 );
#endif
    else
        scanf( "%s%n", g_pchBuf, &num );

    char* fmt = (char*) nextarg(ag,ptr_t).p;
    v.ival = val.ival = _eicUscanf ((put_t)charin_ ,
                                   (put_t)charback_, &g_pchBuf, fmt, ag);
    //console input//v.ival = _eicUscanf((put_t)fgetc,(put_t)ungetc,stdin,fmt,ag);
    
    free( _pchBuf );
    return val;
}

void ErrorOutput(char *msg)
{
    unsigned long num;
    unsigned long size = strlen( msg );

    if( g_hErrorPipe )
#ifdef WIN32
    {
        if( g_hWritePipe )
            WriteFile(g_hWritePipe,
                      (LPCVOID) msg,
                      size,
                      &num,
                      NULL);
        else
            printf( msg );

        WriteFile(g_hErrorPipe,
                  (LPCVOID) msg,
                  size,
                  &num,
                  NULL);
    }
#else
    {
        if( g_hWritePipe )
            write( g_hWritePipe, msg, size );
        else
            printf( msg );
        write( g_hErrorPipe, msg, size );
    }
#endif
    else
        printf( "%s", msg );

}

void _printf(char *msg)
{
    printf(msg);
}

void InitIO( char* output, char* errors, char* input )
{
    if( input )
        sscanf( input, "%d", &g_hInputPipe );
    else
        g_hInputPipe = 0;
    EiC_add_builtinfunc( "scanf", input_scanf );

    if( output )
        sscanf( output, "%d", &g_hWritePipe );
    else
        g_hWritePipe = 0;
    EiC_add_builtinfunc( "printf", output_printf );

    if( errors ) {
        sscanf( errors, "%d", &g_hErrorPipe );
        EiC_setMessageDisplay(ErrorOutput);
    }
    else
    {
        EiC_setMessageDisplay(_printf);
        g_hErrorPipe = 0;
    }
}
