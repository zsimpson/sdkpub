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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define PROC_PX     0
#define PROC_M5     ((1<<23)|5) /* mmx */
#define PROC_M6     ((1<<15)|(1<<23)|6) /* cmov + mmx */
#define PROC_A6     ((1<<25)|PROC_M6)   /* --||-- + xmm */
#define PROC_W7     ((1<<26)|PROC_A6|(1<<3)|1)   /* --||-- + emm */

/*
   determine processor type
*/
static int
get_processor_type( void )
{
    int proc_type = PROC_PX;

    SYSTEM_INFO sys;
    GetSystemInfo( &sys );

    if( sys.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL &&
        sys.dwProcessorType == PROCESSOR_INTEL_PENTIUM )
    {
        int version = 0, features = 0, family = 0;

    #if _MSC_VER >= 1200 || defined __ICL || defined __BORLANDC__

        __asm
        {
            push ebx
            push esi
            push edi
            mov  eax, 1

    #ifndef __BORLANDC__
            _emit 0x0f
            _emit 0xa2
    #else
            db 0fh
            db 0a2h
    #endif
            pop edi
            pop esi
            pop ebx
            mov version, eax
            mov features, edx
        }

    #elif defined __GNUC__

        __asm__ __volatile__
        (
            "push %%ebx\n\t"    
            "push %%esi\n\t"
            "push %%edi\n\t"
            "movl $1, %%eax\n\t"
            "cpuid\n\t"
            "movl %%eax, %0\n\t"
            "movl %%edx, %1\n\t"
            "pop %%edi\n\t"
            "pop %%esi\n\t"
            "pop %%ebx\n\t"
            : "=a" (version),
              "=d" (features)
            :
        );

    #endif

        family = (version >> 8) & 15;
        if( family >= 5 && (features & (PROC_M6 & ~6)) != 0 ) /* Pentium II or higher */
        {
            proc_type = (features & PROC_W7 & -256) | family;
        }
    }

    return proc_type;
}


static const char*
get_flavor( const char* name )
{
    const char* ptr = strrchr( name, '.' );
    char buffer[3];
    assert( ptr != 0 );

    strncpy( buffer, ptr - 2, 2 );
    buffer[0] = (char)toupper(buffer[0]);
    buffer[1] = (char)toupper(buffer[1]);
    buffer[2] = '\0';

    if( !strcmp( buffer, "PL" ))
        return "Switcher";
    if( !strcmp( buffer, "W7" ))
        return "PIV-optimized";
    else if( !strcmp( buffer, "A6" ))
        return "PIII-optimized";
    else if( !strcmp( buffer, "M6" ))
        return "PII-optimized";
    else if( !strcmp( buffer, "M5" ))
        return "Pentium MMX-optimized";
    else if( !strcmp( buffer, "P6" ))
        return "Pentium Pro-optimized";
    else if( !strcmp( buffer, "P5" ))
        return "Pentium-optimized";
    else if( !strcmp( buffer, "PX" ))
        return "Generic IA32";
    else if( !strcmp( buffer, "IX" ))
        return "Generic IA64";
    else if( !strcmp( buffer, "I7" ))
        return "Itanium-optimized";
    else 
        return "UNKNOWN";
}

static const char*
tryLoadOpenCV( const char* name )
{
    HINSTANCE dll = LoadLibrary( name );

    if( dll )
    {
        if( GetProcAddress( dll, "cvAccMask" ) != 0 ) // alpha 3 had cvAccMask function
            return "alpha 3[.4]";
        if( GetProcAddress( dll, "cvAdd" ) == 0 ) // beta 1 did not have cvAdd function 
            return "beta 1.5";
        return "beta 2 or later";
    }

    return 0;
}

typedef struct _IPLLibVersion
{
    int major; /*e.g. 2 */
    int minor; /*e.g. 0 */
    int build; /*e.g. 1 */
    const char* Name; /*"ipl6l.lib","iplm5.dll"*/
    const char* Version; /*e.g."v2.00" */
    const char* InternalVersion; /*e.g. "[2.00.01.023,01/01/99]" */
    const char* BuildDate;/*e.g. "Jan199"*/
    const char* CallConv;
}
IPLLibVersion;

typedef const IPLLibVersion* (__stdcall* IplGetLibVersion)(void);

static char*
load_file( const char* name, int* _size )
{
    FILE* f = fopen( name, "rb" );
    int size = 0;
    char* buffer = 0;

    if( f )
    {
        fseek( f, 0, SEEK_END );
        size = ftell( f );
        fseek( f, 0, SEEK_SET );

        buffer = (char*)malloc( size );
        if( fread( buffer, 1, size, f ) != (unsigned)size )
        {
            free( buffer );
            buffer = 0;
            size = 0;
        }
        fclose( f );
    }

    if( _size )
        *_size = size;

    return buffer;
}


static int
find_signature( char* buffer, int size, const char* signature )
{
    char* ptr = buffer;
    int sig_length = strlen(signature);
    
    while( ptr < buffer + size )
    {
        ptr = (char*)memchr( ptr, signature[0], buffer + size - ptr );
        if( !ptr || buffer + size - ptr < sig_length )
        {
            ptr = 0;
            break;
        }
        
        if( !memcmp( ptr, signature, sig_length )) // found!
            break;
        ptr++;
    }

    return ptr != 0;
}


// convert date from string "/mm/dd/yyyy" or "mm/dd/yy" to time_t.
static time_t date( const char* str )
{
    tm t;
    int month, day, year;
    
    if( sscanf( str, "%d/%d/%d", &month, &day, &year ) != 3 )
        return 0;

    memset( &t, 0, sizeof(t));

    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - (year > 100 ? 1900 : 0);

    return mktime( &t );
}


static const char*
tryLoadIPL( const char* name )
{
    //time_t  ipl_2_1_date = date("01/01/2000");
    //time_t  ipl_2_2_date = date("01/20/2000");
    //time_t  ipl_2_5_date = date("10/09/2000");

    HINSTANCE dll;
    char* dotptr = strrchr( name, '.' );
    assert( dotptr != 0 );
    if( dotptr[-1] == 'l' || dotptr[-1] == 'L' ) // switcher
    {
        int size = 0;
        char* buffer = load_file( name, &size );
        const char* version = "";

        if( find_signature( buffer, size, "IPLW7.DLL" ))
            version = "2.5 or later";
        else if( find_signature( buffer, size, "iplNoiseImage" ))
            version = "2.2";
        else
            version = "2.1 or earlier";

        free( buffer );
        return version;
    }
    else
    {
        dll = LoadLibrary( name );

        if( dll ) // if it is not just a switcher, we can use iplGetLibVersion
        {
            IplGetLibVersion getLibVersion =
                (IplGetLibVersion)GetProcAddress(dll, "iplGetLibVersion");

            if( getLibVersion )
            {
                return getLibVersion()->InternalVersion;
            }
            else
                return "[ERROR - iplGetLibVersion could not be found]";
        }
        else
            return "[ERROR - dll could not be loaded]";
    }
}


static const char*
tryLoadIppCV( const char* /*name*/, _finddata_t* finddata )
{
    //
    // IppCV and OptCV: functionality is approximately the same,
    // so the function checks modification time of the DLL to determine its version.
    //
    time_t  ippcv_alpha_3_4 = date("01/01/2001");
    time_t  ippcv_beta_1_5 = date("06/01/2000");
    time_t  ippcv_beta_2 = date("01/10/2000");

    if( finddata->time_write < ippcv_alpha_3_4 )
        return "alpha 3.4";
    else if( finddata->time_write < ippcv_beta_1_5 )
        return "beta 1.5";
    else if( finddata->time_write < ippcv_beta_2 )
        return "beta 2";
    else
        return "beta 2+";
}


void scan_folder( char* folder, int length )
{
    _finddata_t finddata;
    int search_id;
    const char* version = 0;
    
    if( folder[length - 1] != '/' && folder[length - 1] != '\\' )

    {
        folder[length] = '\\';
        folder[++length] = '0';
    }

    // find OpenCV
    strcpy( folder + length, "cv.dll" );
    version = tryLoadOpenCV( folder );
    
    if( version != 0 )
    {
        printf("%s:\n\t OpenCV version %s\n", folder, version );
    }

    strcpy( folder + length, "cvd.dll" );
    version = tryLoadOpenCV( folder );
    
    if( version != 0 )
    {
        printf("%s:\n\t OpenCV (Debug) version %s\n", folder, version );
    }

    // find IPL
    strcpy( folder + length, "ipl*.dll" );
    search_id = _findfirst( folder, &finddata );

    if( search_id >= 0 )
    {
        do
        {
            strcpy( folder + length, finddata.name );
            version = tryLoadIPL( folder );

            if( version != 0 )
            {
                printf("%s:\n\t IPL %s version %s\n", folder, get_flavor( folder ),
                        version );
            }
        }
        while( _findnext( search_id, &finddata ) >= 0 );
    }

    // find IppCV
    strcpy( folder + length, "ippcv*.dll" );
    search_id = _findfirst( folder, &finddata );

    if( search_id >= 0 )
    {
        do
        {
            strcpy( folder + length, finddata.name );
            version = tryLoadIppCV( folder, &finddata );

            if( version != 0 )
            {
                printf("%s:\n\t IppCV %s version %s\n", folder, get_flavor( folder ),
                        version );
            }
        }
        while( _findnext( search_id, &finddata ) >= 0 );
    }

    // find OptCV
    strcpy( folder + length, "optcv*.dll" );
    search_id = _findfirst( folder, &finddata );

    if( search_id >= 0 )
    {
        do
        {
            strcpy( folder + length, finddata.name );
            version = tryLoadIppCV( folder, &finddata );

            if( version != 0 )
            {
                printf("%s:\n\t IppCV %s version %s\n", folder, get_flavor( folder ),
                        version );
            }
        }
        while( _findnext( search_id, &finddata ) >= 0 );
    }
}

int main( void )
{
    char* path = getenv( "PATH" );
    char* folder_start = path;
    char  folder[1024];
    int   proc_type = get_processor_type();

    printf("Processor: %s or compatible\n", proc_type == PROC_W7 ? "Pentium IV" :
                                            proc_type == PROC_A6 ? "Pentium III" :
                                            proc_type == PROC_M6 ? "Pentium II" :
                                            "Generic IA32 processor"  );

    for( ; *path != '\0'; path++ )
    {
        if( *path == ';' )
        {
            int length = path - folder_start;
            strncpy( folder, folder_start, length );
            folder[length] = '\0';
            //printf( "%s\n", buffer );
            scan_folder( folder, length );
            folder_start = path + 1;
        }
    }
   
    return 0;
}

/* End of file. */



