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

#include "_cv.h"
#include "_cvlist.h"
#include "_cvutils.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>

static const float Pi = 3.1415926f;
static const float halfPi = 1.5707963f;
static const float a0 = -4.172325e-7f;  /*(-(float)0x7)/((float)0x1000000); */
static const float a1 = 1.000025f;      /*((float)0x1922253)/((float)0x1000000)*2/Pi; */
static const float a2 = -2.652905e-4f;  /*(-(float)0x2ae6)/((float)0x1000000)*4/(Pi*Pi); */
static const float a3 = -0.165624f;     /*(-(float)0xa45511)/((float)0x1000000)*8/(Pi*Pi*Pi); */
static const float a4 = -1.964532e-3f;  /*(-(float)0x30fd3)/((float)0x1000000)*16/(Pi*Pi*Pi*Pi); */
static const float a5 = 1.02575e-2f;    /*((float)0x191cac)/((float)0x1000000)*32/(Pi*Pi*Pi*Pi*Pi); */
static const float a6 = -9.580378e-4f;  /*(-(float)0x3af27)/((float)0x1000000)*64/(Pi*Pi*Pi*Pi*Pi*Pi); */

#define _sin(x) ((((((a6*(x) + a5)*(x) + a4)*(x) + a3)*(x) + a2)*(x) + a1)*(x) + a0)

CV_FORCE_INLINE float
_cos( float x )
{
    float temp = Pi * 0.5f - x;

    return _sin( temp );
}

typedef struct __index
{
    int value;
    float rho, theta;
}
_index;


#if _MSC_VER >= 1200
#pragma warning( disable: 4714 )
#endif

DECLARE_AND_IMPLEMENT_LIST( _index, h_ );

IPCVAPI_IMPL( int, icvHoughLinesSDiv_8uC1R, (uchar * image_src,
                                             int step, CvSize size,
                                             float rho,
                                             int srn,
                                             float theta,
                                             int stn,
                                             int threshold, float *lines, int lines_number) )
{

#define _POINT(row, column)\
    (image_src[(row)*step+(column)])


    int rn, tn;                 /* number of rho and theta discrete values */

    uchar *caccum = 0;
    uchar *mcaccum;
    uchar *buffer = NULL;

    int *x;
    int *y;

    int index, i;
    int ri, ti, ti1, ti0;
    int row, col;
    float r, t;                 /* Current rho and theta */
    float rv;                   /* Some temporary rho value */
    float irho;
    float itheta;
    float srho, stheta;
    float isrho, istheta;

    int lines_found = 0;

    int w = size.width;
    int h = size.height;

    int fn = 0;
    float xc, yc;

    const float d2r = Pi / 180;

    int sfn = srn * stn;
    int fi;
    int count;

    float *sinTable;
    int cmax = 0;

    _CVLIST *list;
    CVPOS pos;
    _index *pindex;
    _index vi;

    if( image_src == NULL )
    {
        return CV_NULLPTR_ERR;
    }

    if( size.width < 0 || size.height < 0 || size.width > step )
    {
        return CV_BADSIZE_ERR;
    }


    if( lines_number == 0 || rho <= 0 || theta <= 0 )
    {
        return CV_BADFACTOR_ERR;
    }

    irho = 1 / rho;
    itheta = 1 / theta;
    srho = rho / srn;
    stheta = theta / stn;
    isrho = 1 / srho;
    istheta = 1 / stheta;

    rn = (int) floor( sqrt( w * w + h * h ) * irho );
    tn = (int) floor( 2 * Pi * itheta );

    list = h_create_list__index( lines_number );
    vi.value = threshold;
    vi.rho = -1;
    h_add_head__index( list, &vi );

    /* Precalculating sin */
    sinTable = (float *) icvAlloc( 5 * tn * stn * sizeof( float ));

    for( index = 0; index < 5 * tn * stn; index++ )
    {
        sinTable[index] = (float) _cos( stheta * index * 0.2f );
    }

    /* Allocating memory for the accumulator ad initializing it */
    if( threshold > 255 )
    {
        return -1;
    }
    else
    {
        caccum = (uchar *) icvAlloc( rn * tn * sizeof( uchar ));
        memset( caccum, 0, rn * tn * sizeof( uchar ));
    }



    /* Counting all feature pixels */

    for( row = 0; row < h; row++ )
    {
        for( col = 0; col < w; col++ )
        {
            fn += !!_POINT( row, col );
        }
    }

    x = (int *) icvAlloc( fn * sizeof( int ));
    y = (int *) icvAlloc( fn * sizeof( int ));

    /* Full Hough Transform (it's accumulator update part) */
    fi = 0;
    if( threshold < 256 )
    {
        for( row = 0; row < h; row++ )
        {
            for( col = 0; col < w; col++ )
            {
                if( _POINT( row, col ))
                {
                    int halftn;
                    float r0;
                    float scale_factor;
                    int iprev = -1;
                    float phi, phi1;
                    float theta_it;     /* Value of theta for iterating */

                    /* Remember the feature point */
                    x[fi] = col;
                    y[fi] = row;
                    fi++;


                    yc = (float) row + 0.5f;
                    xc = (float) col + 0.5f;

                    /* Update the accumulator */
                    t = (float) fabs( icvFastArctan32f( yc, xc ) * d2r );
                    r = (float) sqrt( xc * xc + yc * yc );
                    r0 = r * irho;
                    ti0 = cvFloor( (t + Pi / 2) * itheta );

                    caccum[ti0]++;

                    theta_it = rho / r;
                    theta_it = theta_it < theta ? theta_it : theta;
                    scale_factor = theta_it * itheta;
                    halftn = (int) floor( Pi / theta_it );
                    for( ti1 = 1, phi = theta_it - Pi / 2, phi1 = (theta_it + t) * itheta;
                         ti1 < halftn; ti1++, phi += theta_it, phi1 += scale_factor )
                    {
                        rv = r0 * _cos( phi );
                        i = cvFloor( rv ) * tn + (int) cvFloor( phi1 );
                        assert( i >= 0 );
                        assert( i < rn * tn );
                        caccum[i] = (unsigned char) (caccum[i] + ((i ^ iprev) != 0));
                        iprev = i;
                        if( cmax < caccum[i] )
                            cmax = caccum[i];
                    }
                }
            }
        }
    }
    else
    {
        if( caccum )
            icvFree( &caccum );
        icvFree( &sinTable );
        icvFree( &x );
        icvFree( &y );
        return -1;
    }

    /* Starting additional analysis */

    count = 0;
    for( ri = 0; ri < rn; ri++ )
    {
        for( ti = 0; ti < tn; ti++ )
        {
            if( caccum[ri * tn + ti > threshold] )
            {
                count++;
            }
        }
    }

    if( count * 100 > rn * tn )
    {
        if( caccum )
            icvFree( &caccum );
        icvFree( &sinTable );
        icvFree( &x );
        icvFree( &y );
        return icvHoughLines_8uC1R( image_src, step, size, rho, theta,
                                     threshold, lines, lines_number );
    }

    buffer = (uchar *) icvAlloc( (srn * stn + 2) * sizeof( uchar ));
    mcaccum = buffer + 1;

    count = 0;
    for( ri = 0; ri < rn; ri++ )
    {
        for( ti = 0; ti < tn; ti++ )
        {
            if( caccum[ri * tn + ti] > threshold )
            {
                count++;
                memset( mcaccum, 0, sfn * sizeof( uchar ));

                for( index = 0; index < fn; index++ )
                {
                    int ti2;
                    float r0;

                    yc = (float) y[index] + 0.5f;
                    xc = (float) x[index] + 0.5f;


                    /* Update the accumulator */
                    t = (float) fabs( icvFastArctan32f( yc, xc ) * d2r );
                    r = (float) sqrt( xc * xc + yc * yc ) * isrho;
                    ti0 = cvFloor( (t + Pi * 0.5f) * istheta );
                    ti2 = (ti * stn - ti0) * 5;
                    r0 = (float) ri *srn;

                    for( ti1 = 0 /*, phi = ti*theta - Pi/2 - t */ ; ti1 < stn; ti1++, ti2 += 5
                         /*phi += stheta */  )
                    {
                        /*rv = r*_cos(phi) - r0; */
                        rv = r * sinTable[(int) (abs( ti2 ))] - r0;
                        i = cvFloor( rv ) * stn + ti1;

                        i = CV_IMAX( i, -1 );
                        i = CV_IMIN( i, sfn );
                        mcaccum[i]++;
                        assert( i >= -1 );
                        assert( i <= sfn );
                    }
                }

                /* Find peaks in maccum... */
                for( index = 0; index < sfn; index++ )
                {
                    i = 0;
                    pos = h_get_tail_pos__index( list );
                    if( h_get_prev__index( &pos )->value < mcaccum[index] )
                    {
                        vi.value = mcaccum[index];
                        vi.rho = index / stn * srho + ri * rho;
                        vi.theta = index % stn * stheta + ti * theta - halfPi;
                        while( h_is_pos__index( pos ))
                        {
                            if( h_get__index( pos )->value > mcaccum[index] )
                            {
                                h_insert_after__index( list, pos, &vi );
                                if( h_get_count__index( list ) > lines_number )
                                {
                                    h_remove_tail__index( list );
                                }
                                break;
                            }
                            h_get_prev__index( &pos );
                        }
                        if( !h_is_pos__index( pos ))
                        {
                            h_add_head__index( list, &vi );
                            if( h_get_count__index( list ) > lines_number )
                            {
                                h_remove_tail__index( list );
                            }
                        }
                    }
                }
            }
        }
    }

    lines_found = 0;
    pos = h_get_head_pos__index( list );
    if( h_get_count__index( list ) == 1 )
    {
        if( h_get__index( pos )->rho < 0 )
        {
            h_clear_list__index( list );
        }
    }
    else
    {
        while( h_is_pos__index( pos ))
        {
            pindex = h_get__index( pos );
            if( pindex->rho < 0 )
            {
                /* This should be the last element... */
                h_get_next__index( &pos );
                assert( !h_is_pos__index( pos ));
                break;
            }
            lines[2 * lines_found] = pindex->rho;
            lines[2 * lines_found + 1] = pindex->theta;
            lines_found++;
            h_get_next__index( &pos );
        }
    }

    h_destroy_list__index( list );

    icvFree( &sinTable );
    icvFree( &x );
    icvFree( &y );
    if( caccum )
        icvFree( &caccum );
    if( buffer )
    {
        icvFree( &buffer );
    }
    return lines_found;
}

/* End of file. */

