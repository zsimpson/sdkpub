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

#include "ats.h"

static char test_data_path[1000];

void atsInitModuleTestData( char* module, char* path_from_module )
{
    int i;
    for( i = strlen( module ); i >= 0 && module[i] != '/' && module[i] != '\\'; i-- );
    strcpy( test_data_path, module );
    strcpy( test_data_path + i + 1, path_from_module );
    strcat( test_data_path, "/" );
    //strcpy( test_data_path, "F:/Users/Neo/opencv/tests/cv/testdata/" );
}

char* atsGetTestDataPath( char* buffer, char* folder, char* filename, char* extention )
{
    assert( buffer );

    strcpy( buffer, test_data_path );
    if( folder )
    {
        strcat( buffer, folder );
        strcat( buffer, "/" );
    }
    if( filename )
    {
        strcat( buffer, filename );
        if( extention )
        {
            if( *extention != '.' )
                strcat( buffer, "." );
            strcat( buffer, extention );
        }
    }
    return buffer;
}

#define ARG_STR "-lib"

int atsLoadPrimitives( int argc, char** argv )
{
    char  param[1000] = "";
    char  value[100];
    char* sub;
    int   i;
    int   loaded;

    for( i = 1; i < argc; i++ )
        strcat( param, argv[i] );

    sub = strstr( param, "-lib" );
    if( !sub )
        return 0;

    sscanf( sub, ARG_STR " %s", value );
    printf( "loading library %s\n", value );

    /* removing arguments ARG_STR " ..." from arg list */
    for( i = 1; i < argc; i++ )
    {
        sub = strstr( argv[i], ARG_STR );
        if( sub )
        {
            memset( sub, ' ', strlen( ARG_STR ) );
            break;
        }
    }
    for( ; i < argc; i++ )
    {
        sub = strstr( argv[i], value );
        if( sub )
        {
            memset( sub, ' ', strlen( value ) );
            break;
        }
    }

    loaded = cvLoadPrimitives( value );

    if( !(loaded & 1) )
        printf( "ippcv hadn't been loaded\n" );
    if( !(loaded & 2) )
        printf( "optcv hadn't been loaded\n" );

    if( !loaded )
    {
        printf( "can't load primitives. optimization disabled\n" );
        return -1;
    }
    return loaded;
}

