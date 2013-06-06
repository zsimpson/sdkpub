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
#include <float.h>

/* Testing parameters */
static char* func_names[] =
{
    "cvbFastArctan",
    "cvbSqrt",
    "cvbInvSqrt",
    "cvbCartToPolar",
    "cvbReciprocal",
    "cvbFastLog",
    "cvbFastExp"
};

static char* test_desc = "Measure mathematical functions accuracy";

static double angle_step;
static double r_factor, r_delta, r_limit;
static int    exp_step, mant_step;
static int    log_exp_step;
static int64  log_mant_step;
static int    exp_exp_max, exp_mant_step;
static int    init_atan_params = 0;
static int    init_sqrt_params = 0;
static int    init_log_params = 0;
static int    init_exp_params = 0;

static void read_atan_params( void )
{
    if( !init_atan_params )
    {
        /* Reading test-parameters */
        trsdRead( &r_factor, "3", "Radius multiplier" );
        trsdRead( &r_delta, ".01", "Radius increment" );
        trsdRead( &r_limit,"100000", "Radius limit" );
        trsdRead( &angle_step, "0.01", "Angle step (degree)" );
        init_atan_params = 1;
    }
}


static void read_sqrt_params( void )
{
    if( !init_sqrt_params )
    {
        /* Reading test-parameters */
        trsiRead( &mant_step, "16", "Mantissa step" );
        trsiRead( &exp_step, "80", "Exponent step" );
        init_sqrt_params = 1;
    }
}


static void read_log_params( void )
{
    if( !init_log_params )
    {
        int log_mant_step_scale = 0;
        /* Reading test-parameters */
        trsiRead( &log_mant_step_scale, "40", "Mantissa step" );
        log_mant_step = (int64)1 << log_mant_step_scale;
        trsiRead( &log_exp_step, "40", "Exponent step" );
        init_log_params = 1;
    }
}


static void read_exp_params( void )
{
    if( !init_exp_params )
    {
        /* Reading test-parameters */
        trsiRead( &exp_mant_step, "1024", "Mantissa step" );
        trsiRead( &exp_exp_max, "12", "Maximal exponent range" );
        init_exp_params = 1;
    }
}


static int test_arctan( void )
{
    const double success_error_level = 4e-1;

    /* position where the maximum error occured */
    double  merr_angle = 0,
            merr_bangle = 0,
            merr_y = 0, merr_x = 0,
            merr_by = 0, merr_bx = 0;
    unsigned seed = atsGetSeed();

    /* test parameters */
    double  angle = 0, radius = 0;
    double  max_err = 0.;  /* maximum scalar error */
    double  max_berr = 0.; /* maximum vector error */
    int     code = 0;
    int     i, j, k;
    int     phi = 0, r = 0, total = 0;
    float*  data_y = 0;
    float*  data_x = 0;
    float*  angles = 0;
    float*  result = 0;
    AtsRandState state;

    read_atan_params();

    for( angle = 0; angle <= 360; angle += angle_step, phi++ );
    for( radius = 0; radius <= r_limit; radius = radius*r_factor + r_delta, r++ );
    total = phi*r;

    data_y = (float*)icvAlloc( total*sizeof(float) );
    data_x = (float*)icvAlloc( total*sizeof(float) );
    angles = (float*)icvAlloc( total*sizeof(float) );
    result = (float*)icvAlloc( total*sizeof(float) );

    /* scalar function test */

    for( i = 0, k = 0, radius = 0; i < r; i++, radius = radius*r_factor + r_delta )
    {
        for( j = 0, angle = 0; j < phi; j++, angle += angle_step, k++ )
        {
            double a = angle * (IPL_PI/180);
            double x = radius* cos( a );
            double y = radius* sin( a );
            double angle1 = x != 0 || y != 0 ? angle : 0;

            /*a = ippiFastArctan32f( (float)y, (float)x );
            diff = atsCompareAngles( a, angle1 );
            if( diff > max_err )
            {
                max_err = diff;
                merr_angle = angle1;
                merr_y = y;
                merr_x = x;
                if( max_err > success_error_level )
                {
                    code = -1;
                    goto test_exit;
                }
            }*/

            data_y[k] = (float)y;
            data_x[k] = (float)x;
            angles[k] = (float)angle1;
        }
    }

    /* vector function test */

    /* shuffle data */
    atsRandInit( &state, 0, total, seed );

    for( i = 0; i < total/2; i++ )
    {
        int i0 = atsRand32s( &state );
        int i1 = atsRand32s( &state );

        float temp;

        ATS_SWAP( data_y[i0], data_y[i1], temp );
        ATS_SWAP( data_x[i0], data_x[i1], temp );
        ATS_SWAP( angles[i0], angles[i1], temp );
    }

    cvbFastArctan( data_y, data_x, result, total );

    for( i = 0; i < total; i++ )
    {
        double err = atsCompareAngles( result[i], angles[i] );
        if( err > max_berr )
        {
            max_berr = err;
            merr_bangle = angles[i];
            merr_by = data_y[i];
            merr_bx = data_x[i];

            if( max_berr > success_error_level )
            {
                code = -3;
                goto test_exit;
            }
        }
    }

test_exit:

    icvFree( &data_y );
    icvFree( &data_x );
    icvFree( &angles );
    icvFree( &result );

    if( code != -2 )
    {
        trsWrite( ATS_LST, "max scalar err: %g at angle %g, y %g, x %g\n"
                           "max vector err: %g at angle %g, y %g, x %g, seed %08x",
                           max_err, merr_angle, merr_y, merr_x,
                           max_berr, merr_bangle, merr_by, merr_bx, seed );

        return max_err <= success_error_level &&
               max_berr <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
               max_err > success_error_level ?
            trsResult( TRS_FAIL, "Bad scalar accuracy" ) :
            trsResult( TRS_FAIL, "Bad vector accuracy" ) ;
    }
    else
    {
        return trsResult( TRS_FAIL, "Vector function returns error code" );
    }
}


static int test_sqrt( void* arg )
{
    const double success_error_level = 1e-5;
    const int exp_max = 255;
    const int mbits = 23;
    int   inv = (int)arg;

    /* position where the maximum error occured */
    double  merr_x = 0, merr_bx = 0;

    unsigned seed = atsGetSeed();

    /* test parameters */
    int     exp = 0, mant = 0;
    double  max_err = 0.;  /* maximum scalar error */
    double  max_berr = 0.; /* maximum vector error */
    int     code = 0;
    int     k;
    int     i = 0, m = 0, e = 0, total = 0;
    float*  data_x   = 0;
    float*  std_sqrt = 0;
    float*  result   = 0;
    AtsRandState state;

    read_sqrt_params();

    for( mant = 0; mant < (1<<mbits); mant += mant_step, m++ );
    for( exp = inv; exp < exp_max; exp += exp_step, e++ );
    total = m*e;

    data_x   = (float*)icvAlloc( total*sizeof(float) );
    std_sqrt = (float*)icvAlloc( total*sizeof(float) );
    result   = (float*)icvAlloc( total*sizeof(float) );

    /* scalar function test */
    for( exp = inv, k = 0; exp < exp_max; exp += exp_step )
    {
        for( mant = 0; mant < (1<<mbits); mant += mant_step, k++ )
        {
            float x;
            float std, fast;
            double err;

            *((unsigned*)&x) = (exp << mbits) | mant;

            if( !inv )
            {
                std = (float)sqrt(x);
                fast = cvSqrt(x);
            }
            else
            {
                std = (float)(1./sqrt(x));
                fast = cvInvSqrt(x);
            }

            err = fabs( std - fast )/(std + 1e-10);
            if( err > max_err )
            {
                max_err = err;
                merr_x = x;
                if( max_err > success_error_level )
                {
                    code = -1;
                    goto test_exit;
                }
            }

            data_x[k] = x;
            std_sqrt[k] = std;
        }
    }

    /* vector function test */

    /* shuffle data */
    atsRandInit( &state, 0, total, seed );

    for( i = 0; i < total/2; i++ )
    {
        int i0 = atsRand32s( &state );
        int i1 = atsRand32s( &state );

        float temp;

        ATS_SWAP( data_x[i0], data_x[i1], temp );
        ATS_SWAP( std_sqrt[i0], std_sqrt[i1], temp );
    }

    if( inv )
        cvbInvSqrt( data_x, result, total );
    else
        cvbSqrt( data_x, result, total );

    for( i = 0; i < total; i++ )
    {
        double err = fabs(result[i] - std_sqrt[i])/(std_sqrt[i] + 1e-10);
        if( err > max_berr )
        {
            max_berr = err;
            merr_bx = data_x[i];

            if( max_berr > success_error_level )
            {
                code = -3;
                goto test_exit;
            }
        }
    }

test_exit:

    icvFree( &data_x );
    icvFree( &std_sqrt );
    icvFree( &result );

    if( code != -2 )
    {
        trsWrite( ATS_LST, "max scalar err: %g at x = %g\n"
                           "max vector err: %g at x = %g, seed %08x",
                           max_err, merr_x,
                           max_berr, merr_bx, seed );

        return max_err <= success_error_level &&
               max_berr <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
               max_err > success_error_level ?
            trsResult( TRS_FAIL, "Bad scalar accuracy" ) :
            trsResult( TRS_FAIL, "Bad vector accuracy" ) ;
    }
    else
    {
        return trsResult( TRS_FAIL, "Vector function returns error code" );
    }
}

static int test_cart_to_polar( void )
{
    const double success_mag_error_level = 1e-5,
                 success_phase_error_level = 4e-1;

    /* position where the maximum error occured */
    double  mm_err_y = 0, mm_err_x = 0,
            mm_err_by = 0, mm_err_bx = 0;

    double  mp_err_y = 0, mp_err_x = 0,
            mp_err_by = 0, mp_err_bx = 0;

    unsigned seed = atsGetSeed();

    /* test parameters */
    double  angle = 0, radius = 0;
    double  max_mag_err = 0.;  /* maximum scalar magnitude error */
    double  max_mag_berr = 0.; /* maximum vector magnitude error */
    double  max_phase_err = 0.;  /* maximum scalar phase error */
    double  max_phase_berr = 0.; /* maximum vector phase error */
    int     code = 0;
    int     i, j, k;
    int     phi = 0, r = 0, total = 0;
    float*  data_y = 0;
    float*  data_x = 0;
    float*  std_phase = 0;
    float*  std_mag = 0;
    float*  fast_phase = 0;
    float*  fast_mag = 0;
    AtsRandState state;

    read_atan_params();

    for( angle = 0; angle <= 360; angle += angle_step, phi++ );
    for( radius = 0; radius <= r_limit; radius = radius*r_factor + r_delta, r++ );
    total = phi*r;

    data_y = (float*)icvAlloc( total*sizeof(float) );
    data_x = (float*)icvAlloc( total*sizeof(float) );
    std_phase = (float*)icvAlloc( total*sizeof(float) );
    std_mag = (float*)icvAlloc( total*sizeof(float) );
    fast_phase = (float*)icvAlloc( total*sizeof(float) );
    fast_mag = (float*)icvAlloc( total*sizeof(float) );

    /* scalar function test */

    for( i = 0, k = 0, radius = 0; i < r; i++, radius = radius*r_factor + r_delta )
    {
        for( j = 0, angle = 0; j < phi; j++, angle += angle_step, k++ )
        {
            double a = angle * (IPL_PI/180);
            double x = radius* cos( a );
            double y = radius* sin( a );
            double angle1 = x != 0 || y != 0 ? angle : 0;

            /*
            cvCartToPolar32f( (float)x, (float)y, &fm, &fp );
            err = atsCompareAngles( fp, angle1 );
            if( err > max_phase_err )
            {
                max_phase_err = err;
                mp_err_y = y;
                mp_err_x = x;
                if( max_phase_err > success_phase_error_level )
                {
                    code = -1;
                    goto test_exit;
                }
            }

            err = fabs( fm - radius )/(radius + 1e-15);
            if( err > max_mag_err )
            {
                max_mag_err = err;
                mm_err_x = x;
                mm_err_y = y;
                if( max_mag_err > success_mag_error_level )
                {
                    code = -2;
                    goto test_exit;
                }
            }
            */
            data_y[k] = (float)y;
            data_x[k] = (float)x;
            std_phase[k] = (float)angle1;
            std_mag[k] = (float)radius;
        }
    }

    /* vector function test */

    /* shuffle data */
    atsRandInit( &state, 0, total, seed );

    for( i = 0; i < total/2; i++ )
    {
        int i0 = atsRand32s( &state );
        int i1 = atsRand32s( &state );

        float temp;

        ATS_SWAP( data_y[i0], data_y[i1], temp );
        ATS_SWAP( data_x[i0], data_x[i1], temp );
        ATS_SWAP( std_phase[i0], std_phase[i1], temp );
        ATS_SWAP( std_mag[i0], std_mag[i1], temp );
    }

    cvbCartToPolar( data_x, data_y, fast_mag, fast_phase, total );

    for( i = 0; i < total; i++ )
    {
        double err = atsCompareAngles( std_phase[i], fast_phase[i] );
        if( err > max_phase_berr )
        {
            max_phase_berr = err;
            mp_err_by = data_y[i];
            mp_err_bx = data_x[i];

            if( max_phase_berr > success_phase_error_level )
            {
                code = -4;
                goto test_exit;
            }
        }
        err = fabs( fast_mag[i] - std_mag[i] )/(std_mag[i] + 1e-15);
        if( err > max_mag_berr )
        {
            max_mag_berr = err;
            mm_err_by = data_y[i];
            mm_err_bx = data_x[i];
            if( max_mag_berr > success_mag_error_level )
            {
                code = -5;
                goto test_exit;
            }
        }
    }

test_exit:

    icvFree( &data_y );
    icvFree( &data_x );
    icvFree( &std_mag );
    icvFree( &fast_mag );
    icvFree( &std_phase );
    icvFree( &fast_phase );

    if( code != -3 )
    {
        trsWrite( ATS_LST, "phase:\nmax scalar err: %g at y %g, x %g\n"
                           "max vector err: %g at y %g, x %g, seed %08x\n",
                           max_phase_err, mp_err_y, mp_err_x,
                           max_phase_berr, mp_err_by, mp_err_bx, seed );

        trsWrite( ATS_LST, "magnitude:\nmax scalar err: %g at y %g, x %g\n"
                           "max vector err: %g at y %g, x %g, seed %08x",
                           max_mag_err, mm_err_y, mm_err_x,
                           max_mag_berr, mm_err_by, mm_err_bx, seed );

        return max_phase_err <= success_phase_error_level &&
               max_mag_err <= success_mag_error_level &&
               max_phase_berr <= success_phase_error_level &&
               max_mag_berr <= success_mag_error_level ?
            trsResult( TRS_OK, "No errors" ) :
               max_mag_err > success_mag_error_level ||
               max_phase_err > success_phase_error_level ?
            trsResult( TRS_FAIL, "Bad scalar accuracy" ) :
            trsResult( TRS_FAIL, "Bad vector accuracy" ) ;
    }
    else
    {
        return trsResult( TRS_FAIL, "Vector function returns error code" );
    }
}


static int test_recip( void )
{
    double success_error_level = 1e-6;
    const int mbits = 23;
    const int exp_max = 255;

    /* position where the maximum error occured */
    double merr_bx = 0;

    unsigned seed = atsGetSeed();

    /* test parameters */
    int     exp = 0, mant = 0;
    double  max_berr = 0.; /* maximum vector error */
    int     code = 0;
    int     k;
    int     i = 0, m = 0, e = 0, total = 0;
    float*  data_x   = 0;
    float*  std      = 0;
    float*  result   = 0;
    AtsRandState state;

    read_sqrt_params();

    for( mant = 0; mant < (1<<mbits); mant += mant_step, m++ );
    for( exp = 1; exp < exp_max; exp += exp_step, e++ );
    total = m*e;

    data_x  = (float*)icvAlloc( total*sizeof(data_x[0]) );
    std     = (float*)icvAlloc( total*sizeof(std[0]) );
    result  = (float*)icvAlloc( total*sizeof(result[0]) );

    /* scalar function test */
    for( exp = 1, k = 0; exp < exp_max; exp += exp_step )
    {
        for( mant = 0; mant < (1<<mbits); mant += mant_step, k++ )
        {
            float x;

            *((unsigned*)&x) = (exp << mbits) | mant;

            data_x[k] = x;
            std[k] = 1.f/x;
        }
    }

    /* vector function test */

    /* shuffle data */
    atsRandInit( &state, 0, total, seed );

    for( i = 0; i < total/2; i++ )
    {
        int i0 = atsRand32s( &state );
        int i1 = atsRand32s( &state );

        float temp;

        ATS_SWAP( data_x[i0], data_x[i1], temp );
        ATS_SWAP( std[i0], std[i1], temp );
    }

    cvbReciprocal( data_x, result, total );

    for( i = 0; i < total; i++ )
    {
        double err = fabs(result[i] - std[i])/(std[i] + DBL_EPSILON);
        if( err > max_berr )
        {
            max_berr = err;
            merr_bx = data_x[i];

            if( max_berr > success_error_level )
            {
                code = -3;
                goto test_exit;
            }
        }
    }

test_exit:

    icvFree( &data_x );
    icvFree( &std );
    icvFree( &result );

    if( code != -2 )
    {
        trsWrite( ATS_LST, "max vector err: %g at x = %g, seed %08x",
                           max_berr, merr_bx, seed );

        return max_berr <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" ) ;
    }
    else
    {
        return trsResult( TRS_FAIL, "Vector function returns error code" );
    }
}


static int test_log( void )
{
    const double success_error_level = 1e-6;
    const int mbits = 52;
    const int exp_max = 2047;

    /* position where the maximum error occured */
    double  merr_bx = 0;

    unsigned seed = atsGetSeed();

    /* test parameters */
    int64   mant_step;
    int     exp_step;
    int     exp = 0;
    int64   mant = 0;
    double  max_berr = 0.; /* maximum vector error */
    int     code = 0;
    int     k;
    int     i = 0, m = 0, e = 0, total = 0;
    double* data_x  = 0;
    float*  std     = 0;
    float*  result  = 0;
    AtsRandState state;

    read_log_params();

    mant_step = log_mant_step;
    exp_step = log_exp_step;

    for( mant = 0; mant < ((int64)1<<mbits); mant += mant_step, m++ );
    for( exp = 1; exp < exp_max; exp += exp_step, e++ );
    total = m*e;

    data_x  = (double*)icvAlloc( total*sizeof(data_x[0]) );
    std     = (float*)icvAlloc( total*sizeof(std[0]) );
    result  = (float*)icvAlloc( total*sizeof(result[0]) );

    /* scalar function test */
    for( exp = 1, k = 0; exp < exp_max; exp += exp_step )
    {
        for( mant = 0; mant < ((int64)1<<mbits); mant += mant_step, k++ )
        {
            double x;

            *((int64*)&x) = ((int64)exp << mbits) | mant;

            data_x[k] = x;
            std[k] = (float)log(x);
        }
    }

    /* vector function test */

    /* shuffle data */
    atsRandInit( &state, 0, total, seed );

    for( i = 0; i < total/2; i++ )
    {
        int i0 = atsRand32s( &state );
        int i1 = atsRand32s( &state );

        float temp;
        double dtemp;

        ATS_SWAP( data_x[i0], data_x[i1], dtemp );
        ATS_SWAP( std[i0], std[i1], temp );
    }

    cvbFastLog( data_x, result, total );

    for( i = 0; i < total; i++ )
    {
        double err = fabs(result[i] - std[i])/(std[i] + DBL_EPSILON);
        if( err > max_berr )
        {
            max_berr = err;
            merr_bx = data_x[i];

            if( max_berr > success_error_level )
            {
                code = -3;
                goto test_exit;
            }
        }
    }

test_exit:

    icvFree( &data_x );
    icvFree( &std );
    icvFree( &result );

    if( code != -2 )
    {
        trsWrite( ATS_LST, "max vector err: %g at x = %g, seed %08x",
                           max_berr, merr_bx, seed );

        return max_berr <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" ) ;
    }
    else
    {
        return trsResult( TRS_FAIL, "Vector function returns error code" );
    }
}



static int test_exp( void )
{
    const double success_error_level = 1e-5;
    const int mbits = 23;

    /* position where the maximum error occured */
    double  merr_bx = 0;

    unsigned seed = atsGetSeed();

    /* test parameters */
    int     mant_step = 0;
    int     exp_max = 0;
    int     _exp = 0;
    int     mant = 0;
    double  max_berr = 0.; /* maximum vector error */
    int     code = 0;
    int     k;
    int     i = 0, m = 0, e = 0, total = 0;
    float*  data_x  = 0;
    double* std     = 0;
    double* result  = 0;
    AtsRandState state;

    read_exp_params();

    mant_step = exp_mant_step;
    exp_max = exp_exp_max;

    for( mant = 0; mant < ((int64)1<<mbits); mant += mant_step, m++ );
    for( _exp = 127 - exp_max; _exp <= 127 + exp_max; _exp++, e++ );
    total = m*e;

    data_x  = (float*)icvAlloc( total*sizeof(data_x[0]) );
    std     = (double*)icvAlloc( total*sizeof(std[0]) );
    result  = (double*)icvAlloc( total*sizeof(result[0]) );

    /* scalar function test */
    for( _exp = 127 - exp_max, k = 0; _exp <= 127 + exp_max; _exp++ )
    {
        for( mant = 0; mant < ((int64)1<<mbits); mant += mant_step, k++ )
        {
            float x;

            *((int*)&x) = (_exp << mbits) | mant;

            data_x[k] = x;
            std[k] = exp(x);
        }
    }

    /* vector function test */

    /* shuffle data */
    atsRandInit( &state, 0, total, seed );

    for( i = 0; i < total/2; i++ )
    {
        int i0 = atsRand32s( &state );
        int i1 = atsRand32s( &state );

        float temp;
        double dtemp;

        ATS_SWAP( data_x[i0], data_x[i1], temp );
        ATS_SWAP( std[i0], std[i1], dtemp );
    }

    cvbFastExp( data_x, result, total );

    for( i = 0; i < total; i++ )
    {
        double err = fabs(result[i] - std[i])/(std[i] + DBL_EPSILON);
        if( err > max_berr )
        {
            max_berr = err;
            merr_bx = data_x[i];

            if( max_berr > success_error_level )
            {
                code = -3;
                goto test_exit;
            }
        }
    }

test_exit:

    icvFree( &data_x );
    icvFree( &std );
    icvFree( &result );

    if( code != -2 )
    {
        trsWrite( ATS_LST, "max vector err: %g at x = %g, seed %08x",
                           max_berr, merr_bx, seed );

        return max_berr <= success_error_level ?
            trsResult( TRS_OK, "No errors" ) :
            trsResult( TRS_FAIL, "Bad accuracy" ) ;
    }
    else
    {
        return trsResult( TRS_FAIL, "Vector function returns error code" );
    }
}


#define SQRT_32F      0
#define INV_SQRT_32F  1

void InitAMathUtils( void )
{
    /* Registering test functions */
    trsReg( func_names[0], test_desc, atsAlgoClass, test_arctan );
    trsRegArg( func_names[1], test_desc, atsAlgoClass, test_sqrt, SQRT_32F );
    trsRegArg( func_names[2], test_desc, atsAlgoClass, test_sqrt, INV_SQRT_32F );
    trsReg( func_names[3], test_desc, atsAlgoClass, test_cart_to_polar );
    trsReg( func_names[4], test_desc, atsAlgoClass, test_recip );
    trsReg( func_names[5], test_desc, atsAlgoClass, test_log );
    trsReg( func_names[6], test_desc, atsAlgoClass, test_exp );

} /* InitAMathUtils */

/* End of file. */


