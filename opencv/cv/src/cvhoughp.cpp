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

#define _HOUGH_SIN_TABLE

#define _sin(x) ((((((a6*(x) + a5)*(x) + a4)*(x) + a3)*(x) + a2)*(x) + a1)*(x) + a0)

CV_FORCE_INLINE float
_cos( float x )
{
    float temp = Pi * 0.5f - x;

    return _sin( temp );
}


IPCVAPI_IMPL( int, icvHoughLinesP_8uC1R, (uchar * image_src,
                                          int step, CvSize size,
                                          float rho,
                                          float theta,
                                          int threshold,
                                          int lineLength,
                                          int lineGap, int *lines, int linesNumber) )
{
#define _POINT(row, column)\
    (image_src[(row)*step+(column)])

    static const int magic = 0x59C00000;
    double floorTemp;

#define _Floor(x) ((floorTemp = ((x) - 0.4999999) + *((float*)&magic),*((int*)&floorTemp)))

#define floor _Floor

    int *map;
    int rn, tn;                 /* number of rho and theta discrete values */

/*#define ROUNDR(x) (x - (float)floor(x) < 0.5f) ? (int)floor(x) : \
                                ((int)floor(x) + 1 < rn) ? (int)floor(x) + 1 : rn - 1*/
#define ROUNDR(x) _Floor(x)

/*#define ROUNDT(x) (x - (float)floor(x) < 0.5f) ? (int)floor(x) : \
                                ((int)floor(x) + 1 < tn) ? (int)floor(x) + 1 : 0*/
#define ROUNDT(x) _Floor(x)

    int *iaccum = 0;
    uchar *caccum = 0;
    int imaccum;
    uchar cmaccum;

    int *x = 0;
    int *y = 0;

    int index, i;
    int ri, ri1, ti, ti1, ti0;
    int halftn;
    int row, col;
    float r, t;                 /* Current rho and theta */
    float rv;                   /* Some temporary rho value */
    float irho;
    float itheta;

    int lines_found = 0;

    int w = size.width;
    int h = size.height;

    int fn = 0;
    float xc, yc;

    const float d2r = Pi / 180;

    int fpn = 0;

#ifdef _PHOUGH_SIN_TABLE
    float *sinTable;
#endif

    if( linesNumber == 0 )
        return 0;
    if( rho <= 0 )
        return 0;
    if( theta <= 0 )
        return 0;

    irho = 1 / rho;
    itheta = 1 / theta;

    rn = (int) floor( sqrt( w * w + h * h ) * irho );
    tn = (int) floor( 2 * Pi * itheta );
    halftn = (int) floor( Pi * itheta );

    /* Allocating memory for the accumulator ad initializing it */
    if( threshold > 255 )
    {
        iaccum = (int *) icvAlloc( rn * tn * sizeof( int ));
        memset( iaccum, 0, rn * tn * sizeof( int ));
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
    map = (int *) icvAlloc( w * h * sizeof( int ));
    memset( map, -1, w * h * sizeof( int ));

#ifdef _PHOUGH_SIN_TABLE
    sinTable = (float *) icvAlloc( tn * sizeof( float ));

    for( ti = 0; ti < tn; ti++ )
    {
        sinTable[ti] = _sin( ti * theta );
    }
#endif

    index = 0;
    for( row = 0; row < h; row++ )
    {
        for( col = 0; col < w; col++ )
        {
            if( _POINT( row, col ))
            {
                x[index] = col;
                y[index] = row;
                map[row * w + col] = index;
                index++;
            }
        }
    }


    /* Starting Hough Transform */

    srand( (unsigned) 1e3 * time( NULL ));      /* Initializing random counter */
    while( fn != 0 )
    {
        int temp;
        int index0;
        int cl;                 /* Counter of length of lines of feature pixels */
        int cg;                 /* Counter of gaps length in lines of feature pixels */
        float dx = 1.0f, dy = 0.0f, ax, ay;
        float msx = 0, msy = 0, mex = 0, mey = 0, mdx = 1.0f, mdy = 0.0f;
        int ml;

        /* The x, y and length of a line (remember the maximum length) */
        float curx = 0, cury = 0;
        int ox, oy;             /* Rounded ax and ay */

#define _EXCHANGE(x1, x2) temp = x1;x1 = x2;x2 = temp


        /* Select a pixel randomly */
        index0 = rand() % fn;
        /* Remove the pixel from the feature points set */
        if( index0 != fn - 1 )
        {
            /* Exchange the point with the last one */
            _EXCHANGE( x[index0], x[fn - 1] );
            _EXCHANGE( y[index0], y[fn - 1] );
            _EXCHANGE( map[y[index0] * w + x[index0]], map[y[fn - 1] * w + x[fn - 1]] );
        }

        fn--;
        fpn++;

        yc = (float) y[fn] + 0.5f;
        xc = (float) x[fn] + 0.5f;


        /* Update the accumulator */
        t = (float) fabs( icvFastArctan32f( yc, xc ) * d2r );
        r = (float) sqrt( xc * xc + yc * yc );
        ti0 = ROUNDT( t * itheta );

        /* ti1 = 0 */
        if( threshold > 255 )
        {
            rv = 0.0f;
            ri1 = 0;
            i = ti0;
            iaccum[i]++;
            imaccum = iaccum[i];
            ri = ri1;
            ti = ti0;
            for( ti1 = 1; ti1 < halftn; ti1++ )
            {
#ifdef _PHOUGH_SIN_TABLE
                rv = r * sinTable[ti1];
                                     /*_sin(ti1*theta);*/
#else
                rv = r * _sin( ti1 * theta );
#endif
                ri1 = ROUNDR( rv * irho );
                i = ri1 * tn + ti1 + ti0;
                iaccum[i]++;
                if( imaccum < iaccum[i] )
                {
                    imaccum = iaccum[i];
                    ri = ri1;
                    ti = ti1 + ti0;
                }
            }

            r = ri * rho + rho / 2;
            t = ti * theta + theta / 2;

            if( iaccum[ri * tn + ti] < threshold )
            {
                continue;
            }

            /* Unvote all the pixels from the detected line */
            iaccum[ri * tn + ti] = 0;
        }
        else
        {
            rv = 0.0f;
            ri1 = 0;
            i = ti0;
            caccum[i]++;
            cmaccum = caccum[i];
            ri = ri1;
            ti = ti0;
            for( ti1 = 1; ti1 < halftn; ti1++ )
            {
#ifdef _PHOUGH_SIN_TABLE
                rv = r * sinTable[ti1];
                                     /*_sin(ti1*theta);*/
#else
                rv = r * _sin( ti1 * theta );
#endif
                ri1 = ROUNDR( rv * irho );
                i = ri1 * tn + ti1 + ti0;
                caccum[i]++;
                if( cmaccum < caccum[i] )
                {
                    cmaccum = caccum[i];
                    ri = ri1;
                    ti = ti1 + ti0;
                }
            }

            r = ri * rho + rho / 2;
            t = ti * theta + theta / 2;

            if( caccum[ri * tn + ti] < threshold )
            {
                continue;
            }

            /* Unvote all the pixels from the detected line */
            caccum[ri * tn + ti] = 0;
        }



        /* Find a longest segment representing the line */
        /* Use an algorithm like Bresenheim one        */

        ml = 0;

        for( i = 0; i < 7; i++ )
        {
            switch (i)
            {
            case 0:
                break;

            case 1:
                r = ri * rho;
                t = ti * theta - halfPi + 0.1f * theta;
                break;

            case 2:
                r = ri * rho;
                t = (ti + 1) * theta - halfPi - 0.1f * theta;
                break;

            case 3:
                r = (ri + 1) * rho - 0.1f * rho;
                t = ti * theta - halfPi + 0.1f * theta;
                break;

            case 4:
                r = (ri + 1) * rho - 0.1f * rho;
                t = (ti + 1) * theta - halfPi - 0.1f * theta;
                break;

            case 5:
                r = ri * rho + 0.1f * rho;
                t = ti * theta - halfPi + 0.5f * theta;
                break;

            case 6:
                r = (ri + 1) * rho - 0.1f * rho;
                t = ti * theta - halfPi + 0.5f * theta;
                break;

            }

            if( t > Pi )
            {
                t = t - 2 * Pi;
            }

            if( t >= 0 )
            {
                if( t <= Pi / 2 )
                {
                    dx = -(float) sin( t );
                    dy = (float) cos( t );

                    if( r < (w - 1) * fabs( dy ))
                    {
                        ax = (float) floor( r / dy ) + 0.5f;
                        ay = 0.5f;
                    }
                    else
                    {
                        ax = (float) w - 0.5f;
                        ay = (float) floor( (r - (w - 1) * dy) / (float) fabs( dx )) + 0.5f;
                    }
                }
                else
                {
                    /* Pi/2 < t < Pi */
                    dx = (float) sin( t );
                    dy = -(float) cos( t );

                    ax = 0.5f;
                    ay = (float) floor( r / dx ) + 0.5f;
                }
            }
            else
            {
                /* -Pi/2 < t < 0 */
                dx = -(float) sin( t );
                dy = (float) cos( t );
                ax = (float) floor( r / dy ) + 0.5f;
                ay = 0.5f;
            }

            cl = 0;
            cg = 0;

            ox = (int) floor( ax );
            oy = (int) floor( ay );
            while( ox >= 0 && ox < w && oy >= 0 && oy < h )
            {
                if( _POINT( oy, ox ))
                {
                    if( cl == 0 )
                    {
                        /* A line has started */
                        curx = ax;
                        cury = ay;
                    }

                    cl++;
                    cg = 0;     /* No gaps so far */
                }
                else if( cl )
                {
                    if( ++cg > lineGap )
                    {
                        /* This is not a gap, the line has finished */
                        /* Let us remember it's parameters */
                        if( ml < cl )
                        {
                            msx = curx;
                            msy = cury;
                            mex = ax;
                            mey = ay;
                            mdx = dx;
                            mdy = dy;
                            ml = cl;
                        }
                        cl = 0;
                        cg = 0;
                    }
                }

                ax += dx;
                ay += dy;
                ox = (int) floor( ax );
                oy = (int) floor( ay );
            }

            /* The last line if there was any... */
            if( ml < cl )
            {
                msx = curx;
                msy = cury;
                mex = ax;
                mey = ay;
                mdx = dx;
                mdy = dy;
                ml = cl;
            }
        }

        if( ml == 0 )
        {
            // no line...
            continue;
        }

        /* Now let's remove all the pixels in the segment from the input image */
        cl = 0;
        cg = 0;
        ax = msx;
        ay = msy;
        ox = (int) floor( msx );
        oy = (int) floor( msy );
        while( (ox != (int) floor( mex ) || oy != (int) floor( mey )) && fn > 0 )
        {
            image_src[oy * step + ox] = 0;
            index0 = map[oy * w + ox];
            if( index0 != -1 )
            {
                if( index0 != fn - 1 )
                {
                    /* Exchange the point with the last one */
                    _EXCHANGE( x[index0], x[fn - 1] );
                    _EXCHANGE( y[index0], y[fn - 1] );
                    _EXCHANGE( map[y[index0] * w + x[index0]],
                               map[y[fn - 1] * w + x[fn - 1]] );
                }
                fn--;
            }

            ax += mdx;
            ay += mdy;
            ox = (int) floor( ax );
            oy = (int) floor( ay );
        }

        if( ml >= lineLength )
        {
            lines[lines_found * 4] = (int) floor( msx );
            lines[lines_found * 4 + 1] = (int) floor( msy );
            lines[lines_found * 4 + 2] = (int) floor( mex );
            lines[lines_found * 4 + 3] = (int) floor( mey );
            lines_found += 1;

            if( linesNumber <= lines_found || fn == 0 )
            {
                icvFree( &x );
                icvFree( &y );
                icvFree( &map );
#ifdef _PHOUGH_SIN_TABLE
                icvFree( &sinTable );
#endif
                icvFree( &iaccum );
                icvFree( &caccum );
                return lines_found;
            }

        }
    }

    icvFree( &x );
    icvFree( &y );
    icvFree( &map );
#ifdef _PHOUGH_SIN_TABLE
    icvFree( &sinTable );
#endif
    icvFree( &iaccum );
    icvFree( &caccum );
    return lines_found;
}
