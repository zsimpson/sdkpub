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

float*  atsReadMatrix( const char* filename, int* _m, int* _n )
{
    FILE* f = fopen( filename, "rt" );
    float* data = 0;
    double NaN = sqrt(-1);

    if( _m ) *_m = 0;
    if( _n ) *_n = 0;

    if( f )
    {
        int m = 0, n = 0, i;
        
        if( fscanf( f, "%d%d", &m, &n ) == 2 && m > 0 && n > 0 )
        {
            data = (float*)malloc( m*n*sizeof(data[0]));
            if( data )
            {
                for( i = 0; i < m*n; i++ )
                {
                    data[i] = (float)NaN;
                    if( fscanf( f, "%g", data + i ) != 1 )
                    {
                        fscanf( f, "%*s" );
                    }
                }
            }

            if( data )
            {
                if( _m ) *_m = m;
                if( _n ) *_n = n;
            }
        }
        fclose(f);
    }
    return data;
}


void  atsWriteMatrix( const char* filename, int m, int n, float* data )
{
    FILE* f = fopen( filename, "wt" );

    if( f )
    {
        int i, j;

        fprintf( f, "%5d%5d\n", m, n );

        for( i = 0; i < m; i++ )
        {
            for( j = 0; j < n; j++ )
            {
                fprintf( f, "%20.7f", data[i*n + j] ); 
            }
            fprintf( f, "\n" );
        }

        fclose(f);
    }
}

/* End of file. */
