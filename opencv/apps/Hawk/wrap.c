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
//M*/#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "malloc.h"
#include "math.h"
#include "eic.h"
#include "wrap.h"

#pragma warning(disable:4716)
float get_float(void)
{
}

double get_double(void)
{
}
#pragma warning(default:4716)

/*
    Calculates size of stack frame given information about function parameters.

    argi - argument info.
       
       argi[0] - number of arguments
       argi[1] - type of returned value.
       argi[2] - type of first argument
       argi[3] - type of second argument
       ...

    argi[j] is either one of EICEX_TYPE_DOUBLE, EICEX_TYPE_FLOAT ... EIC_TYPE_QWORD or
            EICEX_TYPE_STRUCT + <size_of_struct>

    returns size of stack frame in bytes
*/
int  stack_size( int* argi )
{
    int i, count = argi[0];
    int size = argi[1] & EICEX_TYPE_SIZEMASK;

    size = size <= EICEX_TYPE_QWORD && (size & (size - 1)) == 0 ?
           0 : (4|EICEX_RETADDR);

    for( i = 0; i < count; i++ )
    {
        int elsize = argi[i+2];
        size += ((elsize & EICEX_TYPE_SIZEMASK) + 3) & -4;
    }

    return size;
}


/*
    f - pointer to called function.
    argi - argument info.
       
       argi[0] - total size of stack frame for parameters.
                 it can be retrieved via stack_size function
       argi[1] - number of arguments
       argi[2] - type of returned value
       argi[3] - type of first argument
       argi[4] - type of second argument
       ...

    args - pointer to the first argument

    retbuf - where to put function result.
*/
void uni_wrap( stub_f f, int* argi, char* args, int* nsparams, void* retbuf )
{
    int i, count = argi[1];
    int size = argi[0] & (EICEX_RETADDR - 1);
    int64 intbuf;
    char* buffer = alloca( size );

    {
        int j = 0;

        if( argi[0] & EICEX_RETADDR )
        {
            *((void**)(buffer + j)) = retbuf;
            j += 4;
        }

        for( i = 0; i < count; i++ )
        {
            int argtype = argi[i + 3];
            int argsize = ((argtype & EICEX_TYPE_SIZEMASK) + 3) & -4;
            memcpy( buffer + j, get_arg( args, argtype, argsize, nsparams ),
                    argtype & EICEX_TYPE_SIZEMASK );
            j += argsize;
            args = next_arg( args, argtype, argsize, nsparams );
        }
        assert( j == size );
    }

    intbuf = f();

    if( argi[2] == EICEX_TYPE_FLOAT )
    {
        *(float*)&intbuf = get_float();
    }
    else if( argi[2] == EICEX_TYPE_DOUBLE )
    {
        *(double*)&intbuf = get_double();
    }
    
    if( !(argi[0] & EICEX_RETADDR))
    {
        memcpy( retbuf, &intbuf, argi[2] & EICEX_TYPE_SIZEMASK );
    }
    else if( (void*)(int)intbuf != retbuf )
    {
        memcpy( retbuf, (void*)(int)intbuf, argi[2] & EICEX_TYPE_SIZEMASK );
    }
}

static char* get_arg( char* args, int argtype, int argsize, int* nsparams )
{
    int idx = nsparams[0] + 1;
    if(nsparams[idx])
        return ((AR_t*)args)->v.p.p;
    else
        return args;
}

static char* next_arg( char* args, int argtype, int argsize, int* nsparams )
{
    nsparams[0]++;
    return args - sizeof(AR_t);
}
