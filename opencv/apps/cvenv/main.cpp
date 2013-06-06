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
#include "stdlib.h"
#include "string.h"
#include "eic.h"
#include "stdClib/stdClib2eic.h" 
#include "preproc.h"
#include "filelist.h"
#include "initeic.h"
#include "func.h"

extern "C" void stdClib();
extern "C" int ScriptMode;

#undef malloc
#undef free

#define str(x)  #x
#define xstr(x) str(x)

#ifdef WIN32
int  main(int argc, char ** argv)
#else
int  main_seance( int argc, char** argv )
#endif
{
    EiC_init_EiC();

    ScriptMode = 1;

    stdClib();

    int  i;
    char* _argv[3] = {0, 0, 0};
    for( i = 0; i < argc - 2; i++ )
        _argv[i] = argv[i + 2];

    InitIO( _argv[0], _argv[1], _argv[2] );

    dodefine("_EiC");
    dodefine((char*)&(xstr(PLATFORM)[1]));

    InitEiC();

    char** headers;
    int    hn;
    char** header_path;
    int    hnp;
    char** libs;
    int    ln;

    char* path = GetPathFromModuleName( argv[0] );

    char temp[1000];

    /* find all headers & libs in plugin directory */
    strcpy( temp, path );
    GetFileList( temp, &headers, &hn, &header_path, &hnp, &libs, &ln );

    /* include path */
    for( i = 0; i < hnp; i++ )
    {
        strcat( strcpy( temp, ":-I " ), header_path[i] );
        EiC_parseString( temp );
        free( header_path[i] );
    }
    if( hnp )
        free( header_path );
    
    /* including headers */
    for( i = 0; i < hn; i++ )
    {
        strcat( strcat( strcpy( temp, "#include <" ), headers[i]), ">" );
        EiC_parseString( temp );
        free( headers[i] );
    }
    if( hn )
        free( headers );

    /* adding library */
    for( i = 0; i < ln; i++ )
    {
        AddLibrary( libs[i] );
        free( libs[i] );
    }
    if( ln )
        free( libs );

#ifndef WIN32
    strcpy( temp, getenv("HOME" ) );
    strcat( temp, "/.cvenv/" );
    GetFileList( temp, &headers, &hn, &header_path, &hnp, &libs, &ln );

    /* include path */
    for( i = 0; i < hnp; i++ )
    {
        strcat( strcpy( temp, ":-I " ), header_path[i] );
        EiC_parseString( temp );
        free( header_path[i] );
    }
    if( hnp )
        free( header_path );
    
    /* including headers */
    for( i = 0; i < hn; i++ )
    {
        strcat( strcat( strcpy( temp, "#include <" ), headers[i]), ">" );
        EiC_parseString( temp );
        free( headers[i] );
    }
    if( hn )
        free( headers );

    /* adding library */
    for( i = 0; i < ln; i++ )
    {
        AddLibrary( libs[i] );
        free( libs[i] );
    }
    if( ln )
        free( libs );
#endif

    EiC_startEiC(argc, argv);

    free( path );

    return 0;
}
