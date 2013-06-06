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

#include "cvtest.h"

/*#include <windows.h>*/
#ifdef WIN32

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>

static char* funcs[] =
{
    "cvLine",
    "cvLineAA",
    "cvEllipse",
    "cvEllipseAA"
};

static char *test_desc = "Comparing with the simple algorithm";

#define DRAW_LINE          0
#define DRAW_LINEAA        1
#define DRAW_ELLIPSE       2
#define DRAW_ELLIPSEAA     3

/* actual parameters */
static int  test_iters = 0;
static int  min_img_size = 0;
static int  max_img_size = 0;

/* which tests have to run */
static int fn_l = 0, fn_h = ATS_DIM(funcs)-1,
           ch_l = 0, ch_h = 1;

static int init_drawing_params = 0;

static void read_drawing_params( void )
{
    if( !init_drawing_params )
    {
        int func, channels;

        /* Determine which tests are needed to run */
        trsCaseRead( &func, "/a/l/la/e/ea", "a",
                     "Function type: \n"
                     "a  - all\n"
                     "l  - line\n"
                     "la - antialiased line\n"
                     "e  - ellipse\n"
                     "ea - antialiased ellipse\n");
        if( func != 0 ) fn_l = fn_h = func - 1;

        trsCaseRead( &channels, "/a/1/3", "a", "a - all, 1 - single channel, 3 - three channels" );
        if( channels != 0 ) ch_l = ch_h = channels - 1;

        /* read tests params */
        trsiRead( &min_img_size, "3", "minimal image size (size is choosen randomly)" );
        trsiRead( &max_img_size, "300", "maximal image size (size is choosen randomly)" );
        trsiRead( &test_iters, "1000", "number of figures" );

        init_drawing_params = 1;
    }
}


/* ///////////////////// drawing_test ///////////////////////// */
static int drawing_test( void* arg )
{
    const double success_error_level = 20;
    const double min_A = 1e-2, max_A = 1e2;
    const double min_e = 0, max_e = 3;
    const int e_flt_bits = 5;
    const double min_arc = -1000, max_arc = 1000;
    const int  min_color = 50;
    const int  depth = IPL_DEPTH_8U;
    const double max_el_size = 2000;

    const int  iter = -1;

    int   param    = (int)arg;
    int   func     = param>> 1;
    int   channels = param & 1;
    int   antialiased = func == 1 || func == 3;
    int   img_alloc_size;

    int   seed = atsGetSeed();

    /* position where the maximum error occured */
    int   merr_iter = 0;

    /* test parameters */
    int     i = 0;
    double  max_err = 0.;
    int     code = TRS_OK;

    IplROI       roi, roi3;
    IplImage    *img, *img2, *img3;
    AtsRandState rng_state;

    //CvPoint wnd_org = { 100, 100 };
    //CvSize  wnd_size = { 800, 800 };
    //CvPoint dst_org = { 0, 0 };
    //int window = 0;

    atsRandInit( &rng_state, 0, 1, seed );

    read_drawing_params();

    img_alloc_size = max_img_size;

    if( !(ATS_RANGE( func, fn_l, fn_h+1 ) &&
          ATS_RANGE( channels, ch_l, ch_h+1 ))) return TRS_UNDEF;

    channels = channels*2 + 1;

    img  = atsCreateImage( img_alloc_size, img_alloc_size, depth, channels, 0 );
    img2 = atsCreateImage( img_alloc_size, img_alloc_size, depth, channels, 0 );
    img3 = atsCreateImage( img_alloc_size, img_alloc_size, depth, channels, 0 );

    roi.coi = 0;
    roi.xOffset = roi.yOffset = 0;
    roi3.coi = 0;

    img->roi = img2->roi = img3->roi = &roi;

    for( i = 0; i <= test_iters; i++ )
    {
        double err0, err1;
        int  w = 0, h = 0;
        int  xc = 0, yc = 0, xe = 0, ye = 0;
        int  color, std_color;
        int  dilate_size;
        CvStatus  result = CV_OK;
        IplImage* img0 = i == iter ? img : img2;

        /* generate image size */
        atsRandSetBounds( &rng_state, min_img_size, max_img_size + 1 );
        w = atsRand32s( &rng_state );
        h = atsRand32s( &rng_state );

        /* generate two random points */
        atsRandSetBounds( &rng_state, -w/2, w*3/2 + 1 );
        xc = atsRand32s( &rng_state );
        xe = atsRand32s( &rng_state );

        atsRandSetBounds( &rng_state, -h/2, h*3/2 + 1 );
        yc = atsRand32s( &rng_state );
        ye = atsRand32s( &rng_state );

        /* generate random color */
        atsRandSetBounds( &rng_state, min_color, 256 );
        color = atsRand32s( &rng_state );
        color |= atsRand32s( &rng_state ) << 8;
        color |= atsRand32s( &rng_state ) << 16;

        std_color = color;

        if( i == iter )
        {
            std_color = 0xffffff;
            color = 0x808080;
            w = h = 300;
        }

        roi.width = w;
        roi.height = h;

        iplSet( img, 0 );
        iplSet( img2, 0 );
        iplSet( img3, 0 );

        if( func <= DRAW_LINEAA )
        {
            CvPoint pt1, pt2;

            pt1.x = xc;
            pt1.y = yc;

            pt2.x = xe;
            pt2.y = ye;

            atsDrawLine( img0, (float)xc, (float)yc, (float)xe, (float)ye, std_color );

#if 0
            if( i == iter )
            {
                window = atsCreateWindow( "proba", wnd_org, wnd_size );
                atsDisplayImage( img, window, dst_org, wnd_size );
            }
#endif

            if( !antialiased )
                cvLine( img, pt1, pt2, color );
            else
                cvLineAA( img, pt1, pt2, color );
        }
        else
        {
            double mag, e;
            int    angle;
            int    arc0, arc1;

            /* get random eccentricity (e) and A parameters */
            atsRandSetBounds( &rng_state, min_A, max_A );
            mag = atsRand32f( &rng_state );
            atsRandSetBounds( &rng_state, min_e, max_e );
            e = atsRand32f( &rng_state );
            atsRandSetFloatBits( &rng_state, e_flt_bits );

            /* get integer-value random angles in degrees */
            atsRandSetBounds( &rng_state, min_arc, max_arc );

            angle = atsRand32s( &rng_state );
            arc0  = atsRand32s( &rng_state );
            arc1  = atsRand32s( &rng_state );

            if( e >= 0.9 ) e = 0.9/(0.1 + e);

            if( i < iter ) continue;

            //if( func <= DRAW_ELLIPSEAA )
            {
                double a, b;
                CvSize el_size;
                CvPoint center;

                center.x = xc;
                center.y = yc;

                a = mag/(1. - e*e);
                b = sqrt(mag*a);

                if( a > max_el_size ) a = max_el_size;
                if( b > max_el_size ) b = max_el_size;

                el_size.width  = cvRound(a);
                el_size.height = cvRound(b);

                if( !antialiased )
                    cvEllipse( img, center, el_size, angle, arc0, arc1, color, 1 );
                else
                    cvEllipseAA( img, center, el_size, angle, arc0, arc1, color, 0 );

#if 0
                if( i == iter )
                {
                    window = atsCreateWindow( "proba", wnd_org, wnd_size );
                    atsDisplayImage( img, window, dst_org, wnd_size );
                }
#endif

                atsDrawEllipse( img0, (float)center.x, (float)center.y,
                                (float)el_size.width, (float)el_size.height,
                                (float)angle, (float)arc0, (float)arc1, std_color );
            }
            /*else
            {
                double A, B, C, D, E;
                CvPoint pt1, pt2;

                if( atsCalcQuadricCoeffs( xc, yc, mag, e, angle, arc0, arc1,
                                          &A, &B, &C, &D, &E, &pt2, &pt1 ) < 0 ) continue;


                result = atsConic( img, cvRound(A), cvRound(B), cvRound(C),
                                   cvRound(D), cvRound(E),
                                   pt1, pt2, color, 0 ) >= 0 ? 0 : -1;

                if( i == iter )
                {
                    window = atsCreateWindow( "proba", wnd_org, wnd_size );
                    atsDisplayImage( img, window, dst_org, wnd_size );
                }

                atsDrawConic( img0, (float)xc, (float)yc, (float)mag, (float)e,
                          (float)angle, (float)arc0, (float)arc1, std_color );
            }*/
        }

        if( result < 0 )
        {
            code = TRS_FAIL;
            goto test_exit;
        }

        /*
        if( i == iter )
        {
            Sleep(3000);
            atsDisplayImage( img, window, dst_org, wnd_size );
            Sleep(3000);
            atsDestroyWindow( window );
            window = 0;
        }
        */

        if( antialiased )
        {
            int c;
            iplThreshold( img, img, 1 );
            for( c = 1; c <= channels; c++ )
            {
                int val = (color >> 8*(c-1)) & 0xff;
                roi.coi = c;
                iplSubtractS( img, img, 255 - val, 0 );
            }
            roi.coi = 0;
        }

        dilate_size = 3;

        /* check that ats_func_result is in dilate(ippi_func_result) */
        iplMaxFilter( img, img3, dilate_size, dilate_size, dilate_size/2, dilate_size/2 );
        iplSubtract( img2, img3, img3 );
        iplThreshold( img3, img3, 1 );
        roi3.xOffset = roi3.yOffset = 1 + antialiased*2;
        roi3.width = w - (1 + antialiased*2)*2;
        roi3.height = h - (1 + antialiased*2)*2;
        if( roi3.width <= 0 || roi3.height <= 0 ) continue;

        img3->roi = &roi3;
        err0 = iplNorm( img3, 0, IPL_L1 )/(255*channels);

        dilate_size += antialiased*2;

        /* check that ippi_func_result is in dilate(ats_func_result) */

        img3->roi = &roi;
        iplMaxFilter( img2, img3, dilate_size, dilate_size, dilate_size/2, dilate_size/2 );
        iplSubtract( img, img3, img3 );
        iplThreshold( img3, img3, 1 );

        img3->roi = &roi3;
        err1 = iplNorm( img3, 0, IPL_L1 )/(255*channels);
        img3->roi = &roi;

        err0 = MAX( err0, err1 );

        if( err0 > max_err )
        {
            merr_iter = i;
            max_err   = err0;
            if( max_err > success_error_level ) goto test_exit;
        }
    } /* end of test loop */

test_exit:

    img->roi = img2->roi = img3->roi = 0;
    atsReleaseImage( img );
    atsReleaseImage( img2 );
    atsReleaseImage( img3 );

    //if( code == TRS_OK )
    {
        trsWrite( ATS_LST, "Max err is %g at iter = %d, seed = %08x",
                           max_err, merr_iter, seed );

        return max_err <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" );
    }
    /*else
    {
        trsWrite( ATS_LST, "Fatal error at iter = %d, seed = %08x", i, seed );
        return trsResult( TRS_FAIL, "Function returns error code" );
    }*/
}

#define LINE_8U_C1         0
#define LINE_8U_C3         1
#define LINEAA_8U_C1       2
#define LINEAA_8U_C3       3
#define ELLIPSE_8U_C1      4
#define ELLIPSE_8U_C3      5
#define ELLIPSEAA_8U_C1    6
#define ELLIPSEAA_8U_C3    7

void InitADrawing( void )
{
    /* Register test functions */
    trsRegArg( funcs[0], test_desc, atsAlgoClass, drawing_test, LINE_8U_C1 );
    trsRegArg( funcs[0], test_desc, atsAlgoClass, drawing_test, LINE_8U_C3 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, drawing_test, LINEAA_8U_C1 );
    trsRegArg( funcs[1], test_desc, atsAlgoClass, drawing_test, LINEAA_8U_C3 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, drawing_test, ELLIPSE_8U_C1 );
    trsRegArg( funcs[2], test_desc, atsAlgoClass, drawing_test, ELLIPSE_8U_C3 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, drawing_test, ELLIPSEAA_8U_C1 );
    trsRegArg( funcs[3], test_desc, atsAlgoClass, drawing_test, ELLIPSEAA_8U_C3 );
}
/* InitADrawing */
#else
void InitADrawing( void )
{
}
#endif

/* End of file. */
