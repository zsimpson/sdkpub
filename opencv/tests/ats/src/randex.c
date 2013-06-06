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

/* get seed using processor tick counter */
unsigned  atsGetSeed( void )
{
    int64 seed64 = atsGetTickCount();
    return ((unsigned)(seed64 >> 32))|((unsigned)seed64);
}

static int calc_shift( unsigned val )
{
    int i = 0;
    for( i = 0; i <= 31 && !(val & (0x80000000 >> i)); i++ );
    return i+1;
}

/* will generate random numbers in [lower,upper) */
void  atsRandSetBounds( AtsRandState* state, double lower, double upper )
{
    state->fb = (float)(lower - (state->fa = (float)(upper - lower)));
    state->ia = cvRound( upper - lower );
    state->ib = cvRound( lower );
    /* shift = <ia is power of 2> ? calc_shift( ia ) : 0; */
    state->shift = (state->ia & (state->ia - 1)) == 0 ? calc_shift(state->ia) : 0;
    if( state->shift == 32 ) state->shift = 0;
    state->mask = -1;
}


/* will generate random numbers in [lower,upper) */
void  atsRandInit( AtsRandState* state, double lower, double upper, unsigned seed )
{
    state->seed = seed;
    atsRandSetBounds( state, lower, upper );
}

void atsRandSetFloatBits( AtsRandState* state, int bits )
{
    state->mask = -(1 << (23 - bits));
}

/* Super-Duper generator */
#define ATS_LCG_A   69069
#define ATS_LCG_B   1

#define ATS_RNG_NEXT( seed )   ((seed)*ATS_LCG_A + ATS_LCG_B)

float  atsRand32f( AtsRandState* state )
{
    float res = 0.f;
    if( state )
    {
        unsigned seed = ATS_RNG_NEXT( state->seed );
        *((unsigned*)&res) = ((seed >> 9) | 0x3f800000) & state->mask;
        state->seed = seed;
        res = res*state->fa + state->fb;
    }
    return res;
}


void  atsbRand32f( AtsRandState* state, float* vect, int len )
{
    int i, mask;
    unsigned seed;
    float fa, fb;

    seed = state->seed;
    fa = state->fa;
    fb = state->fb;
    mask = state->mask;

    for( i = 0; i < len; i++ )
    {
        float res;
        seed = ATS_RNG_NEXT( seed );
        *((unsigned*)&res) = ((seed >> 9) | 0x3f800000) & mask;
        vect[i] = res*fa + fb;
    }

    state->seed = seed;
}

void  atsbRand64d( AtsRandState* state, double* vect, int len )
{
    int i, mask;
    unsigned seed;
    float fa, fb;

    seed = state->seed;
    fa = state->fa;
    fb = state->fb;
    mask = state->mask;

    for( i = 0; i < len; i++ )
    {
        float res;
        seed = ATS_RNG_NEXT( seed );
        *((unsigned*)&res) = ((seed >> 9) | 0x3f800000) & mask;
        vect[i] =(double)(res*fa + fb);
    }

    state->seed = seed;
}


int  atsRand32s( AtsRandState* state )
{
    int res = 0;
    if( state )
    {
        unsigned seed = ATS_RNG_NEXT( state->seed );
        int shift = state->shift;
        if( !shift )
            res = (seed >> 3) % state->ia + state->ib;
        else
            res = (seed >> state->shift) + state->ib;

        state->seed = seed;
    }
    return res;
}


int  atsRandPlain32s( AtsRandState* state )
{
    assert( state );
    state->seed = ATS_RNG_NEXT( state->seed );
    return state->seed >> 1;
}


float  atsRandPlane32f( AtsRandState* state )
{
    int temp;
    assert( state );
    temp = ((state->seed = ATS_RNG_NEXT( state->seed )) >> 9) | 0x3f800000;
    return *((float*)&temp) - 1.f;
}


void  atsbRand32s( AtsRandState* state, int* vect, int len )
{
    int i;
    unsigned seed;
    int ia, ib, shift;

    seed = state->seed;
    ia = state->ia;
    ib = state->ib;
    shift = state->shift;

    if( !shift )
        for( i = 0; i < len; i++ )
        {
            seed = ATS_RNG_NEXT( seed );
            vect[i] = ((seed >> 3) % ia) + ib;
        }
    else
        for( i = 0; i < len; i++ )
        {
            seed = ATS_RNG_NEXT( seed );
            vect[i] = (seed >> shift) + ib;
        }

    state->seed = seed;
}


void  atsbRand16s( AtsRandState* state, short* vect, int len )
{
    int i;
    unsigned seed;
    int ia, ib, shift;

    seed = state->seed;
    ia = state->ia;
    ib = state->ib;
    shift = state->shift;

    if( !shift )
        for( i = 0; i < len; i++ )
        {
            seed = ATS_RNG_NEXT( seed );
            vect[i] = (short)(((seed >> 3) % ia) + ib);
        }
    else
        for( i = 0; i < len; i++ )
        {
            seed = ATS_RNG_NEXT( seed );
            vect[i] = (short)((seed >> shift) + ib);
        }

    state->seed = seed;
}


void  atsbRand8u( AtsRandState* state, uchar* vect, int len )
{
    int i;
    unsigned seed;
    int ia, ib, shift;

    seed = state->seed;
    ia = state->ia;
    ib = state->ib;
    shift = state->shift;

    if( !shift )
        for( i = 0; i < len; i++ )
        {
            seed = ATS_RNG_NEXT( seed );
            vect[i] = (uchar)(((seed >> 3) % ia) + ib);
        }
    else
        for( i = 0; i < len; i++ )
        {
            seed = ATS_RNG_NEXT( seed );
            vect[i] = (uchar)((seed >> shift) + ib);
        }

    state->seed = seed;
}


void  atsbRand8s( AtsRandState* state, char* vect, int len )
{
    atsbRand8u( state, (uchar*)vect, len );
}

/* End of file. */
