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
#include "_cvwrap.h"

#define _CV_SQRT_MAGIC  0xbe6f0000

#define _CV_ATAN_CF0  (-15.8131890796f)
#define _CV_ATAN_CF1  (61.0941945596f)
#define _CV_ATAN_CF2  (-0.140500406322f)

static const float icvAtanTab[8] = { 0.f + _CV_ATAN_CF2, 90.f - _CV_ATAN_CF2,
    180.f - _CV_ATAN_CF2, 90.f + _CV_ATAN_CF2,
    360.f - _CV_ATAN_CF2, 270.f + _CV_ATAN_CF2,
    180.f + _CV_ATAN_CF2, 270.f - _CV_ATAN_CF2
};

static const int icvAtanSign[8] =

    { 0, 0x80000000, 0x80000000, 0, 0x80000000, 0, 0, 0x80000000 };

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvFastAcrtan32f
//    Purpose: fast inaccurate arctangent approximation
//    Context:
//    Parameters:
//      y - ordinate
//      x - abscissa
//    Returns:
//      The angle of vector (x,y) in degrees (0°..360°).
//    Notes:
//      if x == 0 && y == 0 -> result is 0 too.
//      Current version accurancy: ~0.14°
//F*/
float
icvFastArctan32f( float y, float x )
{
    int ix = *((int *) &x), iy = *((int *) &y);
    int ygx, idx = (ix < 0) * 2 + (iy < 0) * 4;

    ix &= 0x7fffffff;
    iy &= 0x7fffffff;

    ygx = (iy <= ix) - 1;
    idx -= ygx;

    idx &= ((ix == 0) - 1) | ((iy == 0) - 1);

    /* swap ix and iy if ix < iy */
    ix ^= iy & ygx;
    iy ^= ix & ygx;
    ix ^= iy & ygx;
    iy ^= icvAtanSign[idx];

    /* set ix to non zero */
    ix |= 1;

    {
        double z = *((float *) &iy) / *((float *) &ix);

        return ( float ) ((_CV_ATAN_CF0 * fabs( z ) + _CV_ATAN_CF1) * z + icvAtanTab[idx]);
    }
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbFastAcrtan32f
//    Purpose: fast inaccurate arctangent approximation (processes whole vector)
//    Context:
//    Parameters:
//      y     - ordinate vector
//      x     - abscissa vector
//      angle - resultant vector
//      len   - vectors length
//    Returns:
//      CV_OK or CV_BADFACTOR_ERR if x or y or angle pointers are NULL or
//      len is negative.
//    Notes:
//      if x[i] == 0 && y[i] == 0 for some i -> angle[i] is 0 too.
//      Current version accurancy: ~0.14°
//F*/
IPCVAPI_IMPL( CvStatus, icvbFastArctan_32f, (const float *y, const float *x, float *angle,
                                             int len) )
{
    int i;

    if( !(y && x && angle && len >= 0) )
        return CV_BADFACTOR_ERR;

    /* unrolled by 4 loop */
    for( i = 4; i <= len; i += 4 )
    {
        int j, idx[4];
        float xf[4], yf[4];
        double d = 1.;

        /* calc numerators and denominators */
        for( j = 0; j < 4; j++ )
        {
            int ix = *((int *) &x[i + j - 4]), iy = *((int *) &y[i + j - 4]);
            int ygx, k = (ix < 0) * 2 + (iy < 0) * 4;

            ix &= 0x7fffffff;
            iy &= 0x7fffffff;

            ygx = (iy <= ix) - 1;
            k -= ygx;

            k &= ((ix == 0) - 1) | ((iy == 0) - 1);

            /* swap ix and iy if ix < iy */
            ix ^= iy & ygx;
            iy ^= ix & ygx;
            ix ^= iy & ygx;
            iy ^= icvAtanSign[k];

            /* ix = ix != 0 ? ix : 1.f */
            ix = ((ix ^ CV_1F) & ((ix == 0) - 1)) ^ CV_1F;
            idx[j] = k;
            yf[j] = *(float *) &iy;
            d *= (xf[j] = *(float *) &ix);
        }

        d = 1. / d;

        {
            double b = xf[2] * xf[3], a = xf[0] * xf[1];

            float z0 = (float) (yf[0] * xf[1] * b * d);
            float z1 = (float) (yf[1] * xf[0] * b * d);
            float z2 = (float) (yf[2] * xf[3] * a * d);
            float z3 = (float) (yf[3] * xf[2] * a * d);

            z0 =
                (float) ((_CV_ATAN_CF0 * fabs( z0 ) + _CV_ATAN_CF1) * z0 + icvAtanTab[idx[0]]);
            z1 =
                (float) ((_CV_ATAN_CF0 * fabs( z1 ) + _CV_ATAN_CF1) * z1 + icvAtanTab[idx[1]]);
            z2 =
                (float) ((_CV_ATAN_CF0 * fabs( z2 ) + _CV_ATAN_CF1) * z2 + icvAtanTab[idx[2]]);
            z3 =
                (float) ((_CV_ATAN_CF0 * fabs( z3 ) + _CV_ATAN_CF1) * z3 + icvAtanTab[idx[3]]);

            angle[i - 4] = z0;
            angle[i - 3] = z1;
            angle[i - 2] = z2;
            angle[i - 1] = z3;
        }
    }

    /* process the rest */
    for( i -= 4; i < len; i++ )
    {
        angle[i] = icvFastArctan32f( y[i], x[i] );
    }
    return CV_OK;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbInvSqrt_32f
//    Purpose: block version of icvInvSqrt32f
//    Context:
//    Parameters:
//      src - source vector
//      dst - destination vector
//      len - vectors length
//    Returns:
//      CV_OK or CV_BADFACTOR_ERR if some pointers are NULL or len < 0
//    Notes:
//F*/
IPCVAPI_IMPL( CvStatus, icvbInvSqrt_32f, (const float *src, float *dst, int len) )
{
    int i;

    if( !(src && dst && len >= 0) )
        return CV_BADFACTOR_ERR;

    /* unrolled by 4 loop */
    for( i = 4; i <= len; i += 4 )
    {
        float x0, y0, val0 = src[i - 4],
            x1, y1, val1 = src[i - 3], x2, y2, val2 = src[i - 2], x3, y3, val3 = src[i - 1];

        *((unsigned *) &x0) = (_CV_SQRT_MAGIC - *((unsigned *) &val0)) >> 1;
        *((unsigned *) &x1) = (_CV_SQRT_MAGIC - *((unsigned *) &val1)) >> 1;
        *((unsigned *) &x2) = (_CV_SQRT_MAGIC - *((unsigned *) &val2)) >> 1;
        *((unsigned *) &x3) = (_CV_SQRT_MAGIC - *((unsigned *) &val3)) >> 1;
        y0 = val0 * 0.5f;
        y1 = val1 * 0.5f;
        y2 = val2 * 0.5f;
        y3 = val3 * 0.5f;
        x0 *= 1.5f - y0 * x0 * x0;
        x1 *= 1.5f - y1 * x1 * x1;
        x2 *= 1.5f - y2 * x2 * x2;
        x3 *= 1.5f - y3 * x3 * x3;
        x0 *= 1.5f - y0 * x0 * x0;
        x1 *= 1.5f - y1 * x1 * x1;
        x2 *= 1.5f - y2 * x2 * x2;
        x3 *= 1.5f - y3 * x3 * x3;
        dst[i - 4] = x0;
        dst[i - 3] = x1;
        dst[i - 2] = x2;
        dst[i - 1] = x3;
    }

    for( i -= 4; i < len; i++ )
    {
        dst[i] = cvInvSqrt( src[i] );
    }
    return CV_OK;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbSqrt_32f
//    Purpose: block version of icvSqrt32f
//    Context:
//    Parameters:
//      src - source vector
//      dst - destination vector
//      len - vectors length
//    Returns:
//      CV_OK or CV_BADFACTOR_ERR if some pointers are NULL or len < 0
//    Notes:
//F*/
IPCVAPI_IMPL( CvStatus, icvbSqrt_32f, (const float *src, float *dst, int len) )
{
    int i;

    if( !(src && dst && len >= 0) )
        return CV_BADFACTOR_ERR;

    src += len;
    dst += len;

    /* unrolled by 4 loop */
    for( i = -len + 4; i <= 0; i += 4 )
    {
        float x0, y0, val0 = src[i - 4],
            x1, y1, val1 = src[i - 3], x2, y2, val2 = src[i - 2], x3, y3, val3 = src[i - 1];

        *((unsigned *) &x0) = (_CV_SQRT_MAGIC - *((unsigned *) &val0)) >> 1;
        *((unsigned *) &x1) = (_CV_SQRT_MAGIC - *((unsigned *) &val1)) >> 1;
        *((unsigned *) &x2) = (_CV_SQRT_MAGIC - *((unsigned *) &val2)) >> 1;
        *((unsigned *) &x3) = (_CV_SQRT_MAGIC - *((unsigned *) &val3)) >> 1;
        y0 = val0 * 0.5f;
        y1 = val1 * 0.5f;
        y2 = val2 * 0.5f;
        y3 = val3 * 0.5f;
        x0 *= 1.5f - y0 * x0 * x0;
        x1 *= 1.5f - y1 * x1 * x1;
        x2 *= 1.5f - y2 * x2 * x2;
        x3 *= 1.5f - y3 * x3 * x3;
        x0 *= val0 * (1.5f - y0 * x0 * x0);
        x1 *= val1 * (1.5f - y1 * x1 * x1);
        x2 *= val2 * (1.5f - y2 * x2 * x2);
        x3 *= val3 * (1.5f - y3 * x3 * x3);
        dst[i - 4] = x0;
        dst[i - 3] = x1;
        dst[i - 2] = x2;
        dst[i - 1] = x3;
    }

    for( i -= 4; i < 0; i++ )
    {
        dst[i] = cvSqrt( src[i] );
    }
    return CV_OK;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbFastAcrtan32f
//    Purpose: fast inaccurate arctangent approximation (processes whole vector)
//    Context:
//    Parameters:
//      x       - abscissas vector
//      y       - ordinates vector
//      mag     - magnitudes vector
//      angle   - angles vector
//      length  - vectors length
//    Returns:
//      CV_OK or CV_BADFACTOR_ERR if x or y or angle pointers are NULL or
//      len is negative.
//    Notes:
//      if x[i] == 0 && y[i] == 0 for some i -> angle[i] is 0 too.
//      Current version accuracy: ~0.3°
//F*/
static CvStatus
icvbMagnitude32f( const float *x, const float *y, float *mag, int length )
{
    int i;

    if( !(x && y && mag && length >= 0) )
        return CV_BADFACTOR_ERR;

    for( i = 0; i <= length - 4; i += 4 )
    {
        float x0 = x[i], y0 = y[i];
        float x1 = x[i + 1], y1 = y[i + 1];

        x0 = x0 * x0 + y0 * y0;
        x1 = x1 * x1 + y1 * y1;
        mag[i] = x0;
        mag[i + 1] = x1;
        x0 = x[i + 2], y0 = y[i + 2];
        x1 = x[i + 3], y1 = y[i + 3];
        x0 = x0 * x0 + y0 * y0;
        x1 = x1 * x1 + y1 * y1;
        mag[i + 2] = x0;
        mag[i + 3] = x1;
    }

    for( ; i < length; i++ )
    {
        mag[i] = x[i] * x[i] + y[i] * y[i];
    }

    return icvbSqrt_32f( mag, mag, length );
}


IPCVAPI_IMPL( CvStatus, icvbCartToPolar32f, (const float *x, const float *y, float *mag,
                                             float *phase, int length) )
{
    if( !(x && y && mag && phase && phase != mag && phase != x && phase != y && length >= 0) )
        return CV_BADFACTOR_ERR;

    icvbFastArctan_32f( y, x, phase, length );
    icvbMagnitude32f( x, y, mag, length );

    return CV_OK;
}


/* calculates 1/sqrt(val) */
double
icvInvSqrt64d( double arg )
{
    double x, y;
    float t = (float) arg;

    *((unsigned *) &t) = (_CV_SQRT_MAGIC - *((unsigned *) &t)) >> 1;
    y = arg * 0.5;
    x = t;
    x *= 1.5 - y * x * x;
    x *= 1.5 - y * x * x;
    x *= 1.5 - y * x * x;
    x *= 1.5 - y * x * x;
    return x;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbRecip_32f
//    Purpose: calculates reciprocal value for each element of the input vector
//    Context:
//    Parameters:
//      x       - input vector
//      y       - output vector
//      n       - number of elements
//    Returns:
//      CV_OK or error code
//    Notes:
//      Special values are not handled.
//F*/
CvStatus
icvbRecip_32f( const float *x, float *y, int n )
{
    int i = 0;

    if( !x || !y )
        return CV_NULLPTR_ERR;
    if( n <= 0 )
        return CV_BADSIZE_ERR;

    /* unrolled by 4 loop */
#if 1
    for( i = 0; i <= n - 4; i += 4 )
    {
        double d;

        int ix = ((const int *) x)[i];

        ix = ((ix ^ CV_1F) & ((ix == 0) - 1)) ^ CV_1F;
        d = *((float *) &ix);
        ix = ((const int *) x)[i + 1];
        ix = ((ix ^ CV_1F) & ((ix == 0) - 1)) ^ CV_1F;
        d *= *((float *) &ix);
        ix = ((const int *) x)[i + 2];
        ix = ((ix ^ CV_1F) & ((ix == 0) - 1)) ^ CV_1F;
        d *= *((float *) &ix);
        ix = ((const int *) x)[i + 3];
        ix = ((ix ^ CV_1F) & ((ix == 0) - 1)) ^ CV_1F;
        d *= *((float *) &ix);

        d = 1. / d;

        {
            double b = x[i + 2] * x[i + 3], a = x[i + 0] * x[i + 1];

            float z0 = (float) (x[i + 1] * b * d);
            float z1 = (float) (x[i + 0] * b * d);
            float z2 = (float) (x[i + 3] * a * d);
            float z3 = (float) (x[i + 2] * a * d);

            y[i] = z0;
            y[i + 1] = z1;
            y[i + 2] = z2;
            y[i + 3] = z3;
        }
    }
#endif
    /* process the rest */
    for( ; i < n; i++ )
        y[i] = 1 / x[i];
    return CV_OK;
}


/****************************************************************************************\
*                          Fast exponent & logarithm                                     *
\****************************************************************************************/

typedef union
{
    int i[2];
    double d;
}
DBLINT;

/* uncomment these defines to get more precise, but slower functions */
#define EXP_QUADRATIC
#define LOG_QUADRATIC

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbExp_32f64f
//    Purpose: fast exponent approximation (processes whole vector)
//    Context:
//    Parameters:
//      x       - input (single-precision) vector
//      y       - output (double-precision) vector
//      n       - number of elements
//    Returns:
//      CV_OK or error code
//    Notes:
//      Accuracy: 6e-9 - quadratic interpolation
//                7e-6 - linear interpolation
//      Special values and overflow are not handled.
//F*/
IPCVAPI_IMPL( CvStatus, icvbExp_32f64f, ( const float *x, double *y, int n ) )
{
#define SCALE 6
#define MASK  (1 << SCALE) - 1

#ifndef  EXP_QUADRATIC
#define  A0  .69315056826685732473000126160832
    static const double A2 = 1.0000073311431372711425273293876 / A0;
#else
#define  A0  .24022724076490209425587077357165
    static const double A1 = .69314972133943456380213536900876 / A0;
    static const double A2 = .99999999999104240633309196177833 / A0;
#endif

    static const double log_e = 1.4426950408889634073599246810019;
    static const double delta = 3. * ((int64) 1 << (52 - 1 - SCALE));

    static const double tab[] = {
        1.0 * A0,
        1.0108892860517004600204097905619 * A0,
        1.0218971486541166782344801347833 * A0,
        1.0330248790212284225001082839705 * A0,
        1.0442737824274138403219664787399 * A0,
        1.0556451783605571588083413251529 * A0,
        1.0671404006768236181695211209928 * A0,
        1.0787607977571197937406800374385 * A0,
        1.0905077326652576592070106557607 * A0,
        1.1023825833078409435564142094256 * A0,
        1.1143867425958925363088129569196 * A0,
        1.126521618608241899794798643787 * A0,
        1.1387886347566916537038302838415 * A0,
        1.151189229952982705817759635202 * A0,
        1.1637248587775775138135735990922 * A0,
        1.1763969916502812762846457284838 * A0,
        1.1892071150027210667174999705605 * A0,
        1.2021567314527031420963969574978 * A0,
        1.2152473599804688781165202513388 * A0,
        1.2284805361068700056940089577928 * A0,
        1.2418578120734840485936774687266 * A0,
        1.2553807570246910895793906574423 * A0,
        1.2690509571917332225544190810323 * A0,
        1.2828700160787782807266697810215 * A0,
        1.2968395546510096659337541177925 * A0,
        1.3109612115247643419229917863308 * A0,
        1.3252366431597412946295370954987 * A0,
        1.3396675240533030053600306697244 * A0,
        1.3542555469368927282980147401407 * A0,
        1.3690024229745906119296011329822 * A0,
        1.3839098819638319548726595272652 * A0,
        1.3989796725383111402095281367152 * A0,
        1.4142135623730950488016887242097 * A0,
        1.4296133383919700112350657782751 * A0,
        1.4451808069770466200370062414717 * A0,
        1.4609177941806469886513028903106 * A0,
        1.476826145939499311386907480374 * A0,
        1.4929077282912648492006435314867 * A0,
        1.5091644275934227397660195510332 * A0,
        1.5255981507445383068512536895169 * A0,
        1.5422108254079408236122918620907 * A0,
        1.5590044002378369670337280894749 * A0,
        1.5759808451078864864552701601819 * A0,
        1.5931421513422668979372486431191 * A0,
        1.6104903319492543081795206673574 * A0,
        1.628027421857347766848218522014 * A0,
        1.6457554781539648445187567247258 * A0,
        1.6636765803267364350463364569764 * A0,
        1.6817928305074290860622509524664 * A0,
        1.7001063537185234695013625734975 * A0,
        1.7186192981224779156293443764563 * A0,
        1.7373338352737062489942020818722 * A0,
        1.7562521603732994831121606193753 * A0,
        1.7753764925265212525505592001993 * A0,
        1.7947090750031071864277032421278 * A0,
        1.8142521755003987562498346003623 * A0,
        1.8340080864093424634870831895883 * A0,
        1.8539791250833855683924530703377 * A0,
        1.8741676341102999013299989499544 * A0,
        1.8945759815869656413402186534269 * A0,
        1.9152065613971472938726112702958 * A0,
        1.9360617934922944505980559045667 * A0,
        1.9571441241754002690183222516269 * A0,
        1.9784560263879509682582499181312 * A0,
    };

    int i = 0;

#ifndef EXP_QUADRATIC
#define EXP_POLY(x)  ((x) + A2)
#else
#define EXP_POLY(x)  ((A1 + (x))*(x) + A2)
#endif

    DBLINT buf[4];

    if( !x || !y )
        return CV_NULLPTR_ERR;
    if( n <= 0 )
        return CV_BADSIZE_ERR;

    buf[0].i[0] = buf[1].i[0] = buf[2].i[0] = buf[3].i[0] = 0;

#if 1
    for( i = 0; i <= n - 4; i += 4 )
    {
        double x0 = x[i] * log_e;
        double x1 = x[i + 1] * log_e;
        double x2 = x[i + 2] * log_e;
        double x3 = x[i + 3] * log_e;

        double y0 = x0 + delta;
        double y1 = x1 + delta;
        double y2 = x2 + delta;
        double y3 = x3 + delta;

        int val0, val1, val2, val3, t;

        val0 = *(int *) &y0;
        val1 = *(int *) &y1;
        val2 = *(int *) &y2;
        val3 = *(int *) &y3;

        x0 -= (y0 - delta);
        x1 -= (y1 - delta);
        x2 -= (y2 - delta);
        x3 -= (y3 - delta);

        t = (val0 >> 6) + 1023;
        t &= (t < 0) - 1;
        buf[0].i[1] = t << 20;

        t = (val1 >> 6) + 1023;
        t &= (t < 0) - 1;
        buf[1].i[1] = t << 20;

        t = (val2 >> 6) + 1023;
        t &= (t < 0) - 1;
        buf[2].i[1] = t << 20;

        t = (val3 >> 6) + 1023;
        t &= (t < 0) - 1;
        buf[3].i[1] = t << 20;

        y0 = buf[0].d * tab[val0 & 63];
        y1 = buf[1].d * tab[val1 & 63];
        y2 = buf[2].d * tab[val2 & 63];
        y3 = buf[3].d * tab[val3 & 63];

        y0 *= EXP_POLY( x0 );
        y1 *= EXP_POLY( x1 );
        y2 *= EXP_POLY( x2 );
        y3 *= EXP_POLY( x3 );

        y[i] = y0;
        y[i + 1] = y1;
        y[i + 2] = y2;
        y[i + 3] = y3;
    }
#endif

    for( ; i < n; i++ )
    {
        double x0 = x[i] * log_e;
        double y0 = x0 + delta;
        int val0 = *(int *) &y0, t;

        t = (val0 >> 6) + 1023;
        t &= (t < 0) - 1;

        buf[0].i[1] = t << 20;
        x0 -= (y0 - delta);

        y0 = buf[0].d * tab[val0 & 63];
        y0 *= EXP_POLY( x0 );
        y[i] = y0;
    }
    return CV_OK;
#undef SCALE
#undef MASK
#undef A0
#undef QUADRATIC
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvbLog_64f32f
//    Purpose: fast logarithm approximation (processes whole vector)
//    Context:
//    Parameters:
//      x       - input (single-precision) vector
//      y       - output (double-precision) vector
//      n       - number of elements
//    Returns:
//      CV_OK or error code
//    Notes:
//      Accuracy: 2e-7 - quadratic interpolation
//                1e-5 - linear interpolation
//      Special values and overflow are not handled.
//F*/
IPCVAPI_IMPL( CvStatus, icvbLog_64f32f, ( const double *x, float *y, int n ) )
{
#define SCALE  7
#define MASK   ((1 << SCALE) - 1)
#define MASK2  ~((MASK << (20 - SCALE))|0xC0000000)

#ifdef LOG_QUADRATIC
    static const double A0 = -.49612121419342424566874297727935;
    static const double A1 = .99998866677172221831639439943860;

#define A2  .49093640522417114994644401831e-8
#else
    static const double A0 = .99611397658303346527525120782531;

#define A2  .37851036824604637020214530186e-5
#endif

    static const double ln_2 = 0.69314718055994530941723212145818;

    static const double tab[] = {
        0 + A2, 1.,
        .007782140442054948947463 + A2, .992248062015503875968992,
        .015504186535965254150854 + A2, .984615384615384615384615,
        .023167059281534378228799 + A2, .977099236641221374045802,
        .030771658666753688371028 + A2, .969696969696969696969697,
        .038318864302136599193755 + A2, .962406015037593984962406,
        .045809536031294203166679 + A2, .955223880597014925373134,
        .053244514518812282865870 + A2, .948148148148148148148148,
        .060624621816434842580606 + A2, .941176470588235294117647,
        .067950661908507749394565 + A2, .934306569343065693430657,
        .075223421237587525698605 + A2, .927536231884057971014493,
        .082443669211074591268160 + A2, .920863309352517985611511,
        .089612158689687132619952 + A2, .914285714285714285714286,
        .096729626458551112295571 + A2, .907801418439716312056738,
        .103796793681643564826062 + A2, .901408450704225352112676,
        .110814366340290114194806 + A2, .895104895104895104895105,
        .117783035656383454538794 + A2, .888888888888888888888889,
        .124703478500957235863407 + A2, .882758620689655172413793,
        .131576357788719272588716 + A2, .876712328767123287671233,
        .138402322859119135685326 + A2, .870748299319727891156463,
        .145182009844497897281935 + A2, .864864864864864864864865,
        .151916042025841975071803 + A2, .859060402684563758389262,
        .158605030176638584093371 + A2, .853333333333333333333333,
        .165249572895307162875611 + A2, .847682119205298013245033,
        .171850256926659222340099 + A2, .842105263157894736842105,
        .178407657472818297119400 + A2, .836601307189542483660131,
        .184922338494011992663904 + A2, .831168831168831168831169,
        .191394852999629454609299 + A2, .825806451612903225806452,
        .197825743329919880362572 + A2, .820512820512820512820513,
        .204215541428690891503820 + A2, .815286624203821656050955,
        .210564769107349637669553 + A2, .810126582278481012658228,
        .216873938300614359619090 + A2, .805031446540880503144654,
        .223143551314209755766295 + A2, .800000000000000000000000,
        .229374101064845829991481 + A2, .795031055900621118012422,
        .235566071312766909077588 + A2, .790123456790123456790123,
        .241719936887145168144308 + A2, .785276073619631901840491,
        .247836163904581256780603 + A2, .780487804878048780487805,
        .253915209980963444137323 + A2, .775757575757575757575758,
        .259957524436926066972079 + A2, .771084337349397590361446,
        .265963548497137941339126 + A2, .766467065868263473053892,
        .271933715483641758831669 + A2, .761904761904761904761905,
        .277868451003456306186350 + A2, .757396449704142011834320,
        .283768173130644598346901 + A2, .752941176470588235294118,
        .289633292583042676878893 + A2, .748538011695906432748538,
        .295464212893835876386682 + A2, .744186046511627906976744,
        .301261330578161781012876 + A2, .739884393063583815028902,
        .307025035294911862075125 + A2, .735632183908045977011494,
        .312755710003896888386247 + A2, .731428571428571428571429,
        .318453731118534615810247 + A2, .727272727272727272727273,
        .324119468654211976090671 + A2, .723163841807909604519774,
        .329753286372467981814423 + A2, .719101123595505617977528,
        .335355541921137830257180 + A2, .715083798882681564245810,
        .340926586970593210305089 + A2, .711111111111111111111111,
        .346466767346208580918462 + A2, .707182320441988950276243,
        .351976423157178184655447 + A2, .703296703296703296703297,
        .357455888921803774226009 + A2, .699453551912568306010929,
        .362905493689368453137824 + A2, .695652173913043478260870,
        .368325561158707653048230 + A2, .691891891891891891891892,
        .373716409793584080821017 + A2, .688172043010752688172043,
        .379078352934969458390853 + A2, .684491978609625668449198,
        .384411698910332039734790 + A2, .680851063829787234042553,
        .389716751140025213370464 + A2, .677248677248677248677249,
        .394993808240868978106394 + A2, .673684210526315789473684,
        .400243164127012706929325 + A2, .670157068062827225130890,
        .405465108108164381978013 + A2, .666666666666666666666667,
        .410659924985268385934306 + A2, .663212435233160621761658,
        .415827895143710965613329 + A2, .659793814432989690721649,
        .420969294644129636128867 + A2, .656410256410256410256410,
        .426084395310900063124545 + A2, .653061224489795918367347,
        .431173464818371340859172 + A2, .649746192893401015228426,
        .436236766774918070349041 + A2, .646464646464646464646465,
        .441274560804875229489496 + A2, .643216080402010050251256,
        .446287102628419511532590 + A2, .640000000000000000000000,
        .451274644139458585144692 + A2, .636815920398009950248756,
        .456237433481587594380806 + A2, .633663366336633663366337,
        .461175715122170166368000 + A2, .630541871921182266009852,
        .466089729924599224558619 + A2, .627450980392156862745098,
        .470979715218791012546898 + A2, .624390243902439024390244,
        .475845904869963914265210 + A2, .621359223300970873786408,
        .480688529345751907676618 + A2, .618357487922705314009662,
        .485507815781700807801791 + A2, .615384615384615384615385,
        .490303988045193838150346 + A2, .612440191387559808612440,
        .495077266797851514597965 + A2, .609523809523809523809524,
        .499827869556449329821331 + A2, .606635071090047393364929,
        .504556010752395287058309 + A2, .603773584905660377358491,
        .509261901789807946804075 + A2, .600938967136150234741784,
        .513945751102234316801006 + A2, .598130841121495327102804,
        .518607764208045632152977 + A2, .595348837209302325581395,
        .523248143764547836516807 + A2, .592592592592592592592593,
        .527867089620842385113892 + A2, .589861751152073732718894,
        .532464798869471843873924 + A2, .587155963302752293577982,
        .537041465896883654566729 + A2, .584474885844748858447489,
        .541597282432744371576542 + A2, .581818181818181818181818,
        .546132437598135650382397 + A2, .579185520361990950226244,
        .550647117952662279259948 + A2, .576576576576576576576577,
        .555141507540501592715480 + A2, .573991031390134529147982,
        .559615787935422686270889 + A2, .571428571428571428571429,
        .564070138284802966071384 + A2, .568888888888888888888889,
        .568504735352668712078739 + A2, .566371681415929203539823,
        .572919753561785509092757 + A2, .563876651982378854625551,
        .577315365034823604318112 + A2, .561403508771929824561404,
        .581691739634622482520611 + A2, .558951965065502183406114,
        .586049045003578208904119 + A2, .556521739130434782608696,
        .590387446602176374641917 + A2, .554112554112554112554113,
        .594707107746692789514344 + A2, .551724137931034482758621,
        .599008189646083399381600 + A2, .549356223175965665236052,
        .603290851438084262340585 + A2, .547008547008547008547009,
        .607555250224541795501085 + A2, .544680851063829787234043,
        .611801541105992903529890 + A2, .542372881355932203389831,
        .616029877215514019647566 + A2, .540084388185654008438819,
        .620240409751857528851495 + A2, .537815126050420168067227,
        .624433288011893501042539 + A2, .535564853556485355648536,
        .628608659422374137744308 + A2, .533333333333333333333333,
        .632766669571037829545786 + A2, .531120331950207468879668,
        .636907462237069231620494 + A2, .528925619834710743801653,
        .641031179420931291055601 + A2, .526748971193415637860082,
        .645137961373584701665229 + A2, .524590163934426229508197,
        .649227946625109818890840 + A2, .522448979591836734693878,
        .653301272012745638758616 + A2, .520325203252032520325203,
        .657358072708360030141890 + A2, .518218623481781376518219,
        .661398482245365008260236 + A2, .516129032258064516129032,
        .665422632545090448950093 + A2, .514056224899598393574297,
        .669430653942629267298885 + A2, .512000000000000000000000,
        .673422675212166720297960 + A2, .509960159362549800796813,
        .677398823591806140809683 + A2, .507936507936507936507937,
        .681359224807903068948072 + A2, .505928853754940711462451,
        .685304003098919416544048 + A2, .503937007874015748031496,
        .689233281238808980324914 + A2, .501960784313725490196078,
        .693147180559945309417232 + A2, .500000000000000000000000
    };

    int i = 0;
    DBLINT buf[4];
    DBLINT *X = (DBLINT *) x;

#ifdef LOG_QUADRATIC
#define LOG_POLY(x) (A0*(x) + A1)*(x)
#else
#define LOG_POLY(x) (A0*(x))
#endif

#define TRANSLATE(x,h) (((x) - 1.)*tab[(h)+1])

    if( !x || !y )
        return CV_NULLPTR_ERR;
    if( n <= 0 )
        return CV_BADSIZE_ERR;

#if 1
    for( i = 0; i <= n - 4; i += 4 )
    {
        double x0, x1, x2, x3;
        double y0, y1, y2, y3;
        int h0, h1, h2, h3;

        h0 = X[i].i[0];
        h1 = X[i + 1].i[0];
        h2 = X[i + 2].i[0];
        h3 = X[i + 3].i[0];
        buf[0].i[0] = h0;
        buf[1].i[0] = h1;
        buf[2].i[0] = h2;
        buf[3].i[0] = h3;

        h0 = X[i].i[1];
        h1 = X[i + 1].i[1];
        buf[0].i[1] = (h0 | (1023 << 20)) & MASK2;
        buf[1].i[1] = (h1 | (1023 << 20)) & MASK2;

        y0 = (((h0 >> 20) & 0x7ff) - 1023) * ln_2;
        y1 = (((h1 >> 20) & 0x7ff) - 1023) * ln_2;

        h0 = (h0 >> (20 - SCALE - 1)) & MASK * 2;
        h1 = (h1 >> (20 - SCALE - 1)) & MASK * 2;

        y0 += tab[h0];
        y1 += tab[h1];

        h2 = X[i + 2].i[1];
        h3 = X[i + 3].i[1];

        x0 = TRANSLATE( buf[0].d, h0 );
        x1 = TRANSLATE( buf[1].d, h1 );

        buf[2].i[1] = (h2 | (1023 << 20)) & MASK2;
        buf[3].i[1] = (h3 | (1023 << 20)) & MASK2;

        y0 += LOG_POLY( x0 );
        y1 += LOG_POLY( x1 );

        y2 = (((h2 >> 20) & 0x7ff) - 1023) * ln_2;
        y3 = (((h3 >> 20) & 0x7ff) - 1023) * ln_2;

        y[i] = (float) y0;
        y[i + 1] = (float) y1;

        h2 = (h2 >> (20 - SCALE - 1)) & MASK * 2;
        h3 = (h3 >> (20 - SCALE - 1)) & MASK * 2;

        y2 += tab[h2];
        y3 += tab[h3];

        x2 = TRANSLATE( buf[2].d, h2 );
        x3 = TRANSLATE( buf[3].d, h3 );

        y2 += LOG_POLY( x2 );
        y3 += LOG_POLY( x3 );

        y[i + 2] = (float) y2;
        y[i + 3] = (float) y3;
    }
#endif

    for( ; i < n; i++ )
    {
        int h0 = X[i].i[1];
        double x0, y0 = (((h0 >> 20) & 0x7ff) - 1023) * ln_2;

        buf[0].i[1] = (h0 | (1023 << 20)) & MASK2;
        buf[0].i[0] = X[i].i[0];
        h0 = (h0 >> (20 - SCALE - 1)) & MASK * 2;

        y0 += tab[h0];
        x0 = TRANSLATE( buf[0].d, h0 );
        y0 += LOG_POLY( x0 );

        y[i] = (float) y0;
    }

    return CV_OK;

#undef SCALE
#undef MASK
#undef MASK2
#undef A2
}



IPCVAPI_IMPL( CvStatus, icvCheckArray_32f_C1R, ( const float* src, int srcstep,
                                                 CvSize size, int flags,
                                                 double min_val, double max_val ))
{
    int a, b;
    
    if( !src )
        return CV_NULLPTR_ERR;

    if( size.width <= 0 || size.height <= 0 )
        return CV_BADSIZE_ERR;

    if( flags & CV_CHECK_RANGE )
    {
        (float&)a = (float)min_val;
        (float&)b = (float)max_val;
    }
    else
    {
        (float&)a = -FLT_MAX;
        (float&)b = FLT_MAX;
    }

    a = CV_TOGGLE_FLT(a);
    b = CV_TOGGLE_FLT(b);

    for( ; size.height--; (char*&)src += srcstep )
    {
        int i;
        for( i = 0; i < size.width; i++ )
        {
            int val = ((int*)src)[i];

            val = CV_TOGGLE_FLT(val);

            if( val < a || val >= b )
                return CV_BADRANGE_ERR;
        }
    }

    return CV_OK;
}


IPCVAPI_IMPL( CvStatus,  icvCheckArray_64f_C1R, ( const double* src, int srcstep,
                                                  CvSize size, int flags,
                                                  double min_val, double max_val ))
{
    int64 a, b;
    
    if( !src )
        return CV_NULLPTR_ERR;

    if( size.width <= 0 || size.height <= 0 )
        return CV_BADSIZE_ERR;

    if( flags & CV_CHECK_RANGE )
    {
        (double&)a = min_val;
        (double&)b = max_val;
    }
    else
    {
        (double&)a = -DBL_MAX;
        (double&)b = DBL_MAX;
    }

    a = CV_TOGGLE_DBL(a);
    b = CV_TOGGLE_DBL(b);

    for( ; size.height--; (char*&)src += srcstep )
    {
        int i;
        for( i = 0; i < size.width; i++ )
        {
            int64 val = ((int64*)src)[i];

            val = CV_TOGGLE_DBL(val);

            if( val < a || val >= b )
                return CV_BADRANGE_ERR;
        }
    }

    return CV_OK;
}


CV_IMPL  int  cvCheckArr( const CvArr* arr, int flags,
                          double minVal, double maxVal )
{
    int result = 0;

    CV_FUNCNAME( "cvCheckArr" );

    __BEGIN__;

    if( arr )
    {
        CvStatus status = CV_OK;
        CvMat stub, *mat = (CvMat*)arr;
        int type;
        CvSize size;

        if( !CV_IS_ARR( mat ))
            CV_CALL( mat = cvGetMat( mat, &stub ));

        type = CV_ARR_TYPE( mat->type );
        size = icvGetMatSize( mat );

        size.width *= CV_ARR_CN( type );

        if( CV_IS_ARR_CONT( mat->type ))
        {
            size.width *= size.height;
            size.height = 1;
        }

        if( CV_ARR_DEPTH(type) == CV_32F )
        {
            status = icvCheckArray_32f_C1R( mat->data.fl, mat->step, size,
                                            flags, minVal, maxVal );
        }
        else if( CV_ARR_DEPTH(type) == CV_64F )
        {
            status = icvCheckArray_64f_C1R( mat->data.db, mat->step, size,
                                            flags, minVal, maxVal );
        }
        else
        {
            CV_ERROR( CV_StsUnsupportedFormat, "" );
        }

        if( status < 0 )  
        {
            if( status != CV_BADRANGE_ERR || !(flags & CV_CHECK_QUIET))
                CV_ERROR_FROM_STATUS( status );

            result = 0;
        }
    }

    result = 1;

    __END__;

    return result;
}


/* End of file. */
