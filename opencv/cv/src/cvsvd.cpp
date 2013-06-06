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
#include <float.h>


/////////////////////////////////////////////////////////////////////////////////////////


static  void
icvGivens_64f( int n, double *x, double *y, double c, double s )
{
    int i;
    double cpd = c - s;
    double cmd = c + s;

    for( i = 0; i < n; i++ )
    {
        double t0 = x[i];
        double t1 = y[i];
        double t2 = c * (t0 + t1);

        x[i] = t2 - t1 * cpd;
        y[i] = t2 - t0 * cmd;
    }
}


static  void
icvMatrAXPY1_64f( int m, int n, double* x, int l, double* a, double* y )
{
    int i, j;

    for( i=0; i<m; i++, x+=l )
    {
        double s = a[i];

        for( j=0; j<n-5; j+=6 )
        {
            double t0 = y[j]   + s*x[j];
            double t1 = y[j+1] + s*x[j+1];
            y[j]   = t0;
            y[j+1] = t1;
            t0 = y[j+2] + s*x[j+2];
            t1 = y[j+3] + s*x[j+3];
            y[j+2] = t0;
            y[j+3] = t1;
            t0 = y[j+4] + s*x[j+4];
            t1 = y[j+5] + s*x[j+5];
            y[j+4] = t0;
            y[j+5] = t1;
        }

        for( ; j<n; j++ ) y[j] += s*x[j];
    }
}


static  void
icvMatrAXPY2_64f( int m, int n, double* x, int l, double* a, double* y )
{
    int i, j;

    for( i = 0; i < m; i++, y += l )
    {
        double s = a[i];

        for( j = 0; j < n - 5; j += 6 )
        {
            double t0 = y[j]   + s*x[j];
            double t1 = y[j+1] + s*x[j+1];
            y[j]   = t0;
            y[j+1] = t1;
            t0 = y[j+2] + s*x[j+2];
            t1 = y[j+3] + s*x[j+3];
            y[j+2] = t0;
            y[j+3] = t1;
            t0 = y[j+4] + s*x[j+4];
            t1 = y[j+5] + s*x[j+5];
            y[j+4] = t0;
            y[j+5] = t1;
        }

        for( ; j < n; j++ ) y[j] += s*x[j];
    }
}


static void
icvMatrAXPY3_64f( int m, int n, double* x, int l, double* y, double h )
{
    int i, j;

    for( i = 1; i < m; i++ )
    {
        double s = 0;

        y += l;

        for( j = 0; j < n - 5; j += 6 )
            s += x[j]  *y[j]   + x[j+1]*y[j+1] + x[j+2]*y[j+2] +
                 x[j+3]*y[j+3] + x[j+4]*y[j+4] + x[j+5]*y[j+5];

        for( ; j < n; j++ )  s += x[j]*y[j];

        s *= h;
        y[-1] = s*x[-1];

        for( j = 0; j < n - 5; j += 6 )
        {
            double t0 = y[j]   + s*x[j];
            double t1 = y[j+1] + s*x[j+1];
            y[j]   = t0;
            y[j+1] = t1;
            t0 = y[j+2] + s*x[j+2];
            t1 = y[j+3] + s*x[j+3];
            y[j+2] = t0;
            y[j+3] = t1;
            t0 = y[j+4] + s*x[j+4];
            t1 = y[j+5] + s*x[j+5];
            y[j+4] = t0;
            y[j+5] = t1;
        }

        for( ; j < n; j++ )
            y[j] += s*x[j];
    }
}



static  void
icvGivens_32f( int n, float *x, float *y, double c, double s )
{
    int i;
    double cpd = c - s;
    double cmd = c + s;

    for( i = 0; i < n; i++ )
    {
        double t0 = x[i];
        double t1 = y[i];
        double t2 = c * (t0 + t1);

        x[i] = (float)(t2 - t1 * cpd);
        y[i] = (float)(t2 - t0 * cmd);
    }
}


static  void
icvMatrAXPY1_32f( int m, int n, float* x, int l, float* a, float* y )
{
    int i, j;

    for( i = 0; i < m; i++, x += l )
    {
        double s = a[i];

        for( j=0; j<n-5; j+=6 )
        {
            double t0 = y[j]   + s*x[j];
            double t1 = y[j+1] + s*x[j+1];
            y[j]   = (float)t0;
            y[j+1] = (float)t1;
            t0 = y[j+2] + s*x[j+2];
            t1 = y[j+3] + s*x[j+3];
            y[j+2] = (float)t0;
            y[j+3] = (float)t1;
            t0 = y[j+4] + s*x[j+4];
            t1 = y[j+5] + s*x[j+5];
            y[j+4] = (float)t0;
            y[j+5] = (float)t1;
        }

        for( ; j < n; j++ )
            y[j] = (float)(y[j] + s*x[j]);
    }
}


static  void
icvMatrAXPY2_32f( int m, int n, float* x, int l, float* a, float* y )
{
    int i, j;

    for( i = 0; i < m; i++, y += l )
    {
        double s = a[i];

        for( j = 0; j < n - 5; j += 6 )
        {
            double t0 = y[j]   + s*x[j];
            double t1 = y[j+1] + s*x[j+1];
            y[j]   = (float)t0;
            y[j+1] = (float)t1;
            t0 = y[j+2] + s*x[j+2];
            t1 = y[j+3] + s*x[j+3];
            y[j+2] = (float)t0;
            y[j+3] = (float)t1;
            t0 = y[j+4] + s*x[j+4];
            t1 = y[j+5] + s*x[j+5];
            y[j+4] = (float)t0;
            y[j+5] = (float)t1;
        }

        for( ; j < n; j++ )
            y[j] = (float)(y[j] + s*x[j]);
    }
}


static void
icvMatrAXPY3_32f( int m, int n, float* x, int l, float* y, double h )
{
    int i, j;

    for( i = 1; i < m; i++ )
    {
        double s = 0;

        y += l;

        for( j = 0; j < n - 5; j += 6 )
            s += x[j]  *y[j]   + x[j+1]*y[j+1] + x[j+2]*y[j+2] +
                 x[j+3]*y[j+3] + x[j+4]*y[j+4] + x[j+5]*y[j+5];

        for( ; j < n; j++ )  s += x[j]*y[j];

        s *= h;
        y[-1] = (float)(s*x[-1]);

        for( j = 0; j < n - 5; j += 6 )
        {
            double t0 = y[j]   + s*x[j];
            double t1 = y[j+1] + s*x[j+1];
            y[j]   = (float)t0;
            y[j+1] = (float)t1;
            t0 = y[j+2] + s*x[j+2];
            t1 = y[j+3] + s*x[j+3];
            y[j+2] = (float)t0;
            y[j+3] = (float)t1;
            t0 = y[j+4] + s*x[j+4];
            t1 = y[j+5] + s*x[j+5];
            y[j+4] = (float)t0;
            y[j+5] = (float)t1;
        }

        for( ; j < n; j++ ) y[j] = (float)(y[j] + s*x[j]);
    }
}

static double
pythag( double a, double b )
{
    a = fabs( a );
    b = fabs( b );
    if( a > b )
    {
        b /= a;
        a *= sqrt( 1.0e0 + b * b );
    }
    else if( b != 0 )
    {
        a /= b;
        a = b * sqrt( 1.0e0 + a * a );
    }

    return a;
}

/****************************************************************************************/
/****************************************************************************************/

#define MAX_ITERS  30

static CvStatus
icvSVD_64f( double* a, int lda, double* w,
            double* u, int ldu, double* v, int ldv,
            CvSize size, double* buffer )
{
    double* e;
    double* temp;
    double *w1, *e1;
    double *hv;
    double ku0 = 0, kv0 = 0;
    double anorm = 0;
    double *a1 = a, *u0 = u, *v0 = v;
    double *u1, *v1;
    int ldu1, ldv1;
    double scale, h;
    int i, j, k, l;
    int n = size.width, m = size.height;
    int nm, m1, n1;
    int iters = 0;

    e = buffer;

    if( m >= n )
    {
        w1 = w;
        e1 = e + 1;
        nm = n;
    }
    else
    {
        w1 = e + 1;
        e1 = w;
        nm = m;
    }
    
    temp = buffer + nm;

    memset( w, 0, nm * sizeof( w[0] ));
    memset( e, 0, nm * sizeof( e[0] ));

    m1 = m;
    n1 = n;

    if( m < n )
        goto row_transform;

    for( ;; )
    {
        if( m1 == 0 )
            break;

        scale = h = 0;

        a = a1;
        hv = u ? u : w1;

        for( j = 0; j < m1; j++, a += lda )
        {
            double t = a[0];
            scale += fabs( hv[j] = t );
        }

        if( scale != 0 )
        {
            double f = 1./scale, g, s = 0;

            for( j = 0; j < m1; j++ )
            {
                double t = (hv[j] *= f);
                s += t * t;
            }

            g = sqrt( s );
            f = hv[0];
            if( f >= 0 )
                g = -g;
            hv[0] = f - g;
            h = 1. / (f * g - s);

            memset( temp, 0, n1 * sizeof( temp[0] ));

            a = a1;

            /* calc temp[0:n-i] = a[i:m,i:n]'*hv[0:m-i] */
            icvMatrAXPY1_64f( m1, n1 - 1, a + 1, lda, hv, temp + 1 );

            for( k = 1; k < n1; k++ ) temp[k] *= h;
            a = a1;

            /* modify a: a[i:m,i:n] = a[i:m,i:n] + hv[0:m-i]*temp[0:n-i]' */
            icvMatrAXPY2_64f( m1, n1 - 1, temp + 1, lda, hv, a + 1 );
            *w1++ = g*scale;
        }
        /* store -2/(hv'*hv) */
        if( u )
        {
            if( m1 == m )
                ku0 = h;
            else
                hv[-1] = h;
        }

        a1++;
        n1--;
        if( v )
            v += ldv + 1;

    row_transform:

        if( n1 == 0 )
            break;

        scale = h = 0;

        a = a1;
        hv = v ? v : e1;

        for( j = 0; j < n1; j++ )
        {
            double t = a[j];
            scale += fabs( hv[j] = t );
        }

        if( scale != 0 )
        {
            double f = 1./scale, g, s = 0;

            for( j = 0; j < n1; j++ )
            {
                double t = (hv[j] *= f);
                s += t * t;
            }

            g = sqrt( s );
            f = hv[0];
            if( f >= 0 )
                g = -g;
            hv[0] = f - g;
            h = 1. / (f * g - s);

            /* update a[i:m:i+1:n] = a[i:m,i+1:n] + (a[i:m,i+1:n]*hv[0:m-i])*... */
            icvMatrAXPY3_64f( m1, n1, hv, lda, a, h );

            *e1++ = g*scale;
        }

        /* store -2/(hv'*hv) */
        if( v )
        {
            if( n1 == n )
                kv0 = h;
            else
                hv[-1] = h;
        }

        a1 += lda;
        m1--;
        if( u )
            u += ldu + 1;
    }

    m1 -= m1 != 0;
    n1 -= n1 != 0;

    /* accumulate left transformations */
    if( u )
    {
        m1 = m - m1;
        u = u0 + m1 * ldu;
        for( i = m1; i < m; i++, u += ldu )
        {
            memset( u + m1, 0, (m - m1) * sizeof( u[0] ));
            u[i] = 1.;
        }

        for( i = m1 - 1; i >= 0; i-- )
        {
            double h, s;

            l = m - i;
            hv = u0 + (ldu + 1) * i;
            h = i == 0 ? ku0 : hv[-1];

            assert( h <= 0 );

            if( h != 0 )
            {
                u = hv;
                icvMatrAXPY3_64f( l, l-1, hv+1, ldu, u+1, h );

                s = hv[0] * h;
                for( k = 0; k < l; k++ ) hv[k] *= s;
                hv[0] += 1;
            }
            else
            {
                for( j = 1; j < l; j++ )
                    hv[j] = hv[j * ldu] = 0;
                hv[0] = 1;
            }
        }
        u = u0;
    }

    /* accumulate right transformations */
    if( v )
    {
        n1 = n - n1;
        v = v0 + n1 * ldv;
        for( i = n1; i < n; i++, v += ldv )
        {
            memset( v + n1, 0, (n - n1) * sizeof( v[0] ));
            v[i] = 1.;
        }

        for( i = n1 - 1; i >= 0; i-- )
        {
            double h, s;

            l = n - i;
            hv = v0 + (ldv + 1) * i;
            h = i == 0 ? kv0 : hv[-1];

            assert( h <= 0 );

            if( h != 0 )
            {
                v = hv;
                icvMatrAXPY3_64f( l, l-1, hv+1, ldv, v+1, h );

                s = hv[0] * h;
                for( k = 0; k < l; k++ ) hv[k] *= s;
                hv[0] += 1;
            }
            else
            {
                for( j = 1; j < l; j++ )
                    hv[j] = hv[j * ldv] = 0;
                hv[0] = 1;
            }
        }
        v = v0;
    }

    for( i = 0; i < nm; i++ )
    {
        double tnorm = fabs( w[i] ) + fabs( e[i] );

        if( anorm < tnorm )
            anorm = tnorm;
    }

    if( m >= n )
    {
        m1 = m;
        n1 = n;
        u1 = u;
        ldu1 = ldu;
        v1 = v;
        ldv1 = ldv;
    }
    else
    {
        m1 = n;
        n1 = m;
        u1 = v;
        ldu1 = ldv;
        v1 = u;
        ldv1 = ldu;
    }

    /* diagonalization of the bidiagonal form */
    for( k = nm - 1; k >= 0; k-- )
    {
        double z = 0;
        iters = 0;

        for( ;; )               /* do iterations */
        {
            double c, s, f, g, h, x, y;
            int flag = 0;

            /* test for splitting */
            for( l = k; l >= 0; l-- )
            {
                if( anorm + fabs( e[l] ) == anorm )
                {
                    flag = 1;
                    break;
                }
                assert( l > 0 );
                if( anorm + fabs( w[l - 1] ) == anorm )
                    break;
            }

            if( !flag )
            {
                c = 0;
                s = 1;

                for( i = l; i <= k; i++ )
                {
                    double f = s * e[i];

                    e[i] *= c;

                    if( anorm + fabs( f ) == anorm )
                        break;

                    g = w[i];
                    h = pythag( f, g );
                    w[i] = h;
                    c = g / h;
                    s = -f / h;

                    if( u1 )
                    {
                        icvGivens_64f( m1, u1 + ldu1 * (i - 1), u1 + ldu1 * i, c, s );
                    }
                }
            }

            z = w[k];
            if( l == k || iters++ == MAX_ITERS )
                break;

            /* shift from bottom 2x2 minor */
            x = w[l];
            y = w[k - 1];
            g = e[k - 1];
            h = e[k];
            f = 0.5 * (((g + z) / h) * ((g - z) / y) + y / h - h / y);
            g = pythag( f, 1 );
            if( f < 0 )
                g = -g;
            f = x - (z / x) * z + (h / x) * (y / (f + g) - h);
            /* next QR transformation */
            c = s = 1;

            for( i = l + 1; i <= k; i++ )
            {
                g = e[i];
                y = w[i];
                h = s * g;
                g *= c;
                z = pythag( f, h );
                e[i - 1] = z;
                c = f / z;
                s = h / z;
                f = x * c + g * s;
                g = -x * s + g * c;
                h = y * s;
                y *= c;

                if( v1 )
                {
                    icvGivens_64f( n1, v1 + ldv1 * (i - 1), v1 + ldv1 * i, c, s );
                }

                z = pythag( f, h );
                w[i - 1] = z;

                /* rotation can be arbitrary if z == 0 */
                if( z != 0 )
                {
                    c = f / z;
                    s = h / z;
                }
                f = c * g + s * y;
                x = -s * g + c * y;

                if( u1 )
                {
                    icvGivens_64f( m1, u1 + ldu1 * (i - 1), u1 + ldu1 * i, c, s );
                }
            }

            e[l] = 0;
            e[k] = f;
            w[k] = x;
        }                       /* end of iteration loop */

        if( iters > MAX_ITERS )
            break;

        if( z < 0 )
        {
            w[k] = -z;
            if( v )
            {
                for( j = 0; j < n; j++ )
                    v[j + k * ldv] = -v[j + k * ldv];
            }
        }
    }                           /* end of diagonalization loop */

    /* sort singular values */
    for( i = 0; i < nm; i++ )
    {
        k = i;
        for( j = i + 1; j < nm; j++ )
            if( w[k] < w[j] )
                k = j;

        if( k != i )
        {
            /* swap i & k values */
            double t = w[k];

            w[k] = w[i];
            w[i] = t;

            if( v )
            {
                for( j = 0; j < n; j++ )
                {
                    t = v[j + ldv * k];
                    v[j + ldv * k] = v[j + ldv * i];
                    v[j + ldv * i] = t;
                }
            }

            if( u )
            {
                for( j = 0; j < m; j++ )
                {
                    t = u[j + k * ldu];
                    u[j + ldu * k] = u[j + i * ldu];
                    u[j + ldu * i] = t;
                }
            }
        }
    }

    return CV_NO_ERR;
}



static CvStatus
icvSVD_32f( float* a, int lda, float* w,
            float* u, int ldu, float* v, int ldv,
            CvSize size, float* buffer )
{
    float* e;
    float* temp;
    float  *w1, *e1;
    float  *hv;
    double ku0 = 0, kv0 = 0;
    double anorm = 0;
    float  *a1 = a, *u0 = u, *v0 = v;
    float  *u1, *v1;
    int ldu1, ldv1;
    double scale, h;
    int i, j, k, l;
    int n = size.width, m = size.height;
    int nm, m1, n1;
    int iters = 0;

    e = buffer;

    if( m >= n )
    {
        w1 = w;
        e1 = e + 1;
        nm = n;
    }
    else
    {
        w1 = e + 1;
        e1 = w;
        nm = m;
    }
    
    temp = buffer + nm;

    memset( w, 0, nm * sizeof( w[0] ));
    memset( e, 0, nm * sizeof( e[0] ));

    m1 = m;
    n1 = n;

    if( m < n )
        goto row_transform;

    for( ;; )
    {
        if( m1 == 0 )
            break;

        scale = h = 0;

        a = a1;
        hv = u ? u : w1;

        for( j = 0; j < m1; j++, a += lda )
        {
            double t = a[0];
            hv[j] = (float)t;
            scale += fabs(t);
        }

        if( scale != 0 )
        {
            double f = 1./scale, g, s = 0;

            for( j = 0; j < m1; j++ )
            {
                double t = hv[j]*f;
                hv[j] = (float)t;
                s += t * t;
            }

            g = sqrt( s );
            f = hv[0];
            if( f >= 0 )
                g = -g;
            hv[0] = (float)(f - g);
            h = 1. / (f * g - s);

            memset( temp, 0, n1 * sizeof( temp[0] ));

            a = a1;

            /* calc temp[0:n-i] = a[i:m,i:n]'*hv[0:m-i] */
            icvMatrAXPY1_32f( m1, n1 - 1, a + 1, lda, hv, temp + 1 );

            for( k = 1; k < n1; k++ ) temp[k] = (float)(temp[k]*h);
            a = a1;

            /* modify a: a[i:m,i:n] = a[i:m,i:n] + hv[0:m-i]*temp[0:n-i]' */
            icvMatrAXPY2_32f( m1, n1 - 1, temp + 1, lda, hv, a + 1 );
            *w1++ = (float)(g*scale);
        }
        /* store -2/(hv'*hv) */
        if( u )
        {
            if( m1 == m )
                ku0 = h;
            else
                hv[-1] = (float)h;
        }

        a1++;
        n1--;
        if( v )
            v += ldv + 1;

    row_transform:

        if( n1 == 0 )
            break;

        scale = h = 0;

        a = a1;
        hv = v ? v : e1;

        for( j = 0; j < n1; j++ )
        {
            double t = a[j];
            hv[j] = (float)t;
            scale += fabs(t);
        }

        if( scale != 0 )
        {
            double f = 1./scale, g, s = 0;

            for( j = 0; j < n1; j++ )
            {
                double t = hv[j] * f;
                hv[j] = (float)t;
                s += t * t;
            }

            g = sqrt( s );
            f = hv[0];
            if( f >= 0 )
                g = -g;
            hv[0] = (float)(f - g);
            h = 1. / (f * g - s);

            /* update a[i:m:i+1:n] = a[i:m,i+1:n] + (a[i:m,i+1:n]*hv[0:m-i])*... */
            icvMatrAXPY3_32f( m1, n1, hv, lda, a, h );

            *e1++ = (float)(g*scale);
        }

        /* store -2/(hv'*hv) */
        if( v )
        {
            if( n1 == n )
                kv0 = h;
            else
                hv[-1] = (float)h;
        }

        a1 += lda;
        m1--;
        if( u )
            u += ldu + 1;
    }

    m1 -= m1 != 0;
    n1 -= n1 != 0;

    /* accumulate left transformations */
    if( u )
    {
        m1 = m - m1;
        u = u0 + m1 * ldu;
        for( i = m1; i < m; i++, u += ldu )
        {
            memset( u + m1, 0, (m - m1) * sizeof( u[0] ));
            u[i] = 1.;
        }

        for( i = m1 - 1; i >= 0; i-- )
        {
            double h, s;

            l = m - i;
            hv = u0 + (ldu + 1) * i;
            h = i == 0 ? ku0 : hv[-1];

            assert( h <= 0 );

            if( h != 0 )
            {
                u = hv;
                icvMatrAXPY3_32f( l, l-1, hv+1, ldu, u+1, h );

                s = hv[0] * h;
                for( k = 0; k < l; k++ )
                    hv[k] = (float)(hv[k]*s);
                hv[0] += 1;
            }
            else
            {
                for( j = 1; j < l; j++ )
                    hv[j] = hv[j * ldu] = 0;
                hv[0] = 1;
            }
        }
        u = u0;
    }

    /* accumulate right transformations */
    if( v )
    {
        n1 = n - n1;
        v = v0 + n1 * ldv;
        for( i = n1; i < n; i++, v += ldv )
        {
            memset( v + n1, 0, (n - n1) * sizeof( v[0] ));
            v[i] = 1.;
        }

        for( i = n1 - 1; i >= 0; i-- )
        {
            double h, s;

            l = n - i;
            hv = v0 + (ldv + 1) * i;
            h = i == 0 ? kv0 : hv[-1];

            assert( h <= 0 );

            if( h != 0 )
            {
                v = hv;
                icvMatrAXPY3_32f( l, l-1, hv+1, ldv, v+1, h );

                s = hv[0] * h;
                for( k = 0; k < l; k++ )
                    hv[k] = (float)(hv[k]*s);
                hv[0] += 1;
            }
            else
            {
                for( j = 1; j < l; j++ )
                    hv[j] = hv[j * ldv] = 0;
                hv[0] = 1;
            }
        }
        v = v0;
    }

    for( i = 0; i < nm; i++ )
    {
        double tnorm = fabs( w[i] ) + fabs( e[i] );

        if( anorm < tnorm )
            anorm = tnorm;
    }

    if( m >= n )
    {
        m1 = m;
        n1 = n;
        u1 = u;
        ldu1 = ldu;
        v1 = v;
        ldv1 = ldv;
    }
    else
    {
        m1 = n;
        n1 = m;
        u1 = v;
        ldu1 = ldv;
        v1 = u;
        ldv1 = ldu;
    }

    /* diagonalization of the bidiagonal form */
    for( k = nm - 1; k >= 0; k-- )
    {
        double z = 0;
        iters = 0;

        for( ;; )               /* do iterations */
        {
            double c, s, f, g, h, x, y;
            int flag = 0;

            /* test for splitting */
            for( l = k; l >= 0; l-- )
            {
                if( anorm + fabs( e[l] ) == anorm )
                {
                    flag = 1;
                    break;
                }
                assert( l > 0 );
                if( anorm + fabs( w[l - 1] ) == anorm )
                    break;
            }

            if( !flag )
            {
                c = 0;
                s = 1;

                for( i = l; i <= k; i++ )
                {
                    double f = s * e[i];
                    e[i] = (float)(e[i]*c);

                    if( anorm + fabs( f ) == anorm )
                        break;

                    g = w[i];
                    h = pythag( f, g );
                    w[i] = (float)h;
                    c = g / h;
                    s = -f / h;

                    if( u1 )
                    {
                        icvGivens_32f( m1, u1 + ldu1 * (i - 1), u1 + ldu1 * i, c, s );
                    }
                }
            }

            z = w[k];
            if( l == k || iters++ == MAX_ITERS )
                break;

            /* shift from bottom 2x2 minor */
            x = w[l];
            y = w[k - 1];
            g = e[k - 1];
            h = e[k];
            f = 0.5 * (((g + z) / h) * ((g - z) / y) + y / h - h / y);
            g = pythag( f, 1 );
            if( f < 0 )
                g = -g;
            f = x - (z / x) * z + (h / x) * (y / (f + g) - h);
            /* next QR transformation */
            c = s = 1;

            for( i = l + 1; i <= k; i++ )
            {
                g = e[i];
                y = w[i];
                h = s * g;
                g *= c;
                z = pythag( f, h );
                e[i - 1] = (float)z;
                c = f / z;
                s = h / z;
                f = x * c + g * s;
                g = -x * s + g * c;
                h = y * s;
                y *= c;

                if( v1 )
                {
                    icvGivens_32f( n1, v1 + ldv1 * (i - 1), v1 + ldv1 * i, c, s );
                }

                z = pythag( f, h );
                w[i - 1] = (float)z;

                /* rotation can be arbitrary if z == 0 */
                if( z != 0 )
                {
                    c = f / z;
                    s = h / z;
                }
                f = c * g + s * y;
                x = -s * g + c * y;

                if( u1 )
                {
                    icvGivens_32f( m1, u1 + ldu1 * (i - 1), u1 + ldu1 * i, c, s );
                }
            }

            e[l] = 0;
            e[k] = (float)f;
            w[k] = (float)x;
        }                       /* end of iteration loop */

        if( iters > MAX_ITERS )
            break;

        if( z < 0 )
        {
            w[k] = (float)(-z);
            if( v )
            {
                for( j = 0; j < n; j++ )
                    v[j + k * ldv] = -v[j + k * ldv];
            }
        }
    }                           /* end of diagonalization loop */

    /* sort singular values */
    for( i = 0; i < nm; i++ )
    {
        k = i;
        for( j = i + 1; j < nm; j++ )
            if( w[k] < w[j] )
                k = j;

        if( k != i )
        {
            /* swap i & k values */
            float t = w[k];

            w[k] = w[i];
            w[i] = t;

            if( v )
            {
                for( j = 0; j < n; j++ )
                {
                    t = v[j + ldv * k];
                    v[j + ldv * k] = v[j + ldv * i];
                    v[j + ldv * i] = t;
                }
            }

            if( u )
            {
                for( j = 0; j < m; j++ )
                {
                    t = u[j + k * ldu];
                    u[j + ldu * k] = u[j + i * ldu];
                    u[j + ldu * i] = t;
                }
            }
        }
    }

    return CV_NO_ERR;
}



CV_IMPL  void
cvSVD( CvArr* aarr, CvArr* warr, CvArr* uarr, CvArr* varr, int flags )
{
    uchar* buffer = 0;
    int local_alloc = 0;

    CV_FUNCNAME( "cvSVD" );

    __BEGIN__;

    CvMat astub, *a = (CvMat*)aarr;
    CvMat wstub, *w = (CvMat*)warr;
    CvMat ustub, *u = (CvMat*)uarr;
    CvMat vstub, *v = (CvMat*)varr;
    CvMat tmat;
    uchar* tw = 0;
    int type, nm, mn;
    int buf_size, pix_size;
    int t_svd = 0; // special case: a->rows < a->cols

    if( !CV_IS_ARR( a ))
        CV_CALL( a = cvGetMat( a, &astub ));

    if( !CV_IS_ARR( w ))
        CV_CALL( w = cvGetMat( w, &wstub ));

    if( !CV_ARE_TYPES_EQ( a, w ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    nm = MIN( a->width, a->height );
    mn = MAX( a->width, a->height );

    if( (w->width == 1 || w->height == 1) &&
        CV_IS_ARR_CONT( w->type ) && w->width*w->height == nm )
    {
        tw = w->data.ptr;
    }
    else if( !CV_ARE_SIZES_EQ( w, a ))
    {
        CV_ERROR( CV_StsBadSize, "W must be either continuous vector of "
                                 "size MIN(A->width,A->height) or matrix of "
                                 "the same size as A" );
    }

    if( u )
    {
        if( !CV_IS_ARR( u ))
            CV_CALL( u = cvGetMat( u, &ustub ));

        if( !CV_ARE_TYPES_EQ( a, u ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( u->width != u->height || u->height != a->height )
            CV_ERROR( CV_StsUnmatchedSizes, "U matrix must be square and have the same "
                                            "linear size as number of rows in A" );

        if( u->data.ptr == a->data.ptr )
            CV_ERROR( CV_StsBadArg, "U can not be equal A" );
    }
    else
    {
        u = &ustub;
        u->data.ptr = 0;
        u->step = 0;
    }

    if( v )
    {
        if( !CV_IS_ARR( v ))
            CV_CALL( v = cvGetMat( v, &vstub ));

        if( !CV_ARE_TYPES_EQ( a, v ))
            CV_ERROR( CV_StsUnmatchedFormats, "" );

        if( v->width != v->height || v->width != a->width )
            CV_ERROR( CV_StsUnmatchedSizes, "V matrix must be square and have the same "
                                            "linear size as number of columns in A" );

        if( v->data.ptr == a->data.ptr || v->data.ptr == u->data.ptr )
            CV_ERROR( CV_StsBadArg, "V can not be equal U or A" );
    }
    else
    {
        v = &vstub;
        v->data.ptr = 0;
        v->step = 0;
    }

    type = CV_ARR_TYPE( a->type );
    pix_size = icvPixSize[type];
    buf_size = nm*2 + mn;

    if( a->rows < a->cols )
    {
        CvMat* t;
        CV_SWAP( u, v, t );

        flags = (flags & CV_SVD_U_T ? CV_SVD_V_T : 0)|
                (flags & CV_SVD_V_T ? CV_SVD_U_T : 0);

        t_svd = 1;
    }

    if( !(flags & CV_SVD_MODIFY_A) )
        buf_size += a->width*a->height;

    buf_size *= pix_size;

    if( buf_size <= CV_MAX_LOCAL_SIZE )
    {
        buffer = (uchar*)alloca( buf_size );
        local_alloc = 1;
    }
    else
    {
        CV_CALL( buffer = (uchar*)cvAlloc( buf_size ));
    }
    
    if( !(flags & CV_SVD_MODIFY_A) )
    {
        if( !t_svd )
        {
            cvInitMatHeader( &tmat, a->height, a->width, type,
                             buffer + (nm*2 + mn)*pix_size );
            cvCopy( a, &tmat );
        }
        else
        {
            cvInitMatHeader( &tmat, a->width, a->height, type,
                             buffer + (nm*2 + mn)*pix_size );
            cvT( a, &tmat );
        }
        a = &tmat;
    }

    if( !tw )
        tw = buffer + (nm + mn)*pix_size;

    if( type == CV_32FC1 )
    {
        IPPI_CALL( icvSVD_32f( a->data.fl, a->step/sizeof(float), (float*)tw,
                               u->data.fl, u->step/sizeof(float),
                               v->data.fl, v->step/sizeof(float),
                               icvGetMatSize(a), (float*)buffer ));
    }
    else if( type == CV_64FC1 )
    {
        IPPI_CALL( icvSVD_64f( a->data.db, a->step/sizeof(double), (double*)tw,
                               u->data.db, u->step/sizeof(double),
                               v->data.db, v->step/sizeof(double),
                               icvGetMatSize(a), (double*)buffer ));
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "" );
    }

    if( tw != w->data.ptr )
    {
        cvSetZero( w );
        if( type == CV_32FC1 )
            for( int i = 0; i < nm; i++ )
                ((float*)(w->data.ptr + i*w->step))[i] = ((float*)tw)[i];
        else
            for( int i = 0; i < nm; i++ )
                ((double*)(w->data.ptr + i*w->step))[i] = ((double*)tw)[i];
    }

    if( u->data.ptr )
    {
        if( !(flags & CV_SVD_U_T))
            cvT( u, u );
        CV_CHECK_NANS( u );
    }

    if( v->data.ptr)
    {
        if( !(flags & CV_SVD_V_T))
            cvT( v, v );
        CV_CHECK_NANS( v );
    }

    CV_CHECK_NANS( w );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );
}


CV_IMPL  double
cvPseudoInv( CvArr* srcarr, CvArr* dstarr, int flags )
{
    uchar* buffer = 0;
    int local_alloc = 0;
    double condition_number = 0;

    CV_FUNCNAME( "cvPseudoInv" );

    __BEGIN__;

    CvMat astub, *a = (CvMat*)srcarr;
    CvMat bstub, *b = (CvMat*)dstarr;
    CvMat ustub, *u = &ustub;
    CvMat vstub, *v = &vstub;
    CvMat tmat;
    uchar* tw = 0;
    int type, n, m, nm, mn;
    int buf_size, pix_size;

    if( !CV_IS_ARR( a ))
        CV_CALL( a = cvGetMat( a, &astub ));

    if( !CV_IS_ARR( b ))
        CV_CALL( b = cvGetMat( b, &bstub ));

    if( !CV_ARE_TYPES_EQ( a, b ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    n = a->width;
    m = a->height;

    nm = MIN( n, m );
    mn = MAX( n, m );

    if( n != b->height || m != b->width )
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    type = CV_ARR_TYPE( a->type );
    pix_size = icvPixSize[type];

    buf_size = nm*2 + mn + m*mn + n*n;

    if( !(flags & CV_SVD_MODIFY_A) )
        buf_size += m*n;

    buf_size *= pix_size;

    if( buf_size <= CV_MAX_LOCAL_SIZE )
    {
        buffer = (uchar*)alloca( buf_size );
        local_alloc = 1;
    }
    else
    {
        CV_CALL( buffer = (uchar*)cvAlloc( buf_size ));
    }

    if( !(flags & CV_SVD_MODIFY_A) )
    {
        cvInitMatHeader( &tmat, a->height, a->width, type,
                         buffer + buf_size - n*m*pix_size );
        cvCopy( a, &tmat );
        a = &tmat;
    }

    tw = buffer + (nm + mn)*pix_size;

    cvInitMatHeader( u, m, m, type, tw + nm*pix_size );
    cvInitMatHeader( v, n, n, type, u->data.ptr + m*mn*pix_size );

    if( type == CV_32FC1 )
    {
        IPPI_CALL( icvSVD_32f( a->data.fl, a->step/sizeof(float), (float*)tw,
                               u->data.fl, u->step/sizeof(float),
                               v->data.fl, v->step/sizeof(float),
                               icvGetMatSize(a), (float*)buffer ));
    }
    else if( type == CV_64FC1 )
    {
        IPPI_CALL( icvSVD_64f( a->data.db, a->step/sizeof(double), (double*)tw,
                               u->data.db, u->step/sizeof(double),
                               v->data.db, v->step/sizeof(double),
                               icvGetMatSize(a), (double*)buffer ));
    }
    else
    {
        CV_ERROR( CV_StsUnsupportedFormat, "" );
    }

    cvT( v, v );
    cvGetRow( u, &tmat, 0 );

    if( type == CV_32FC1 )
    {
        for( int i = 0; i < nm; i++ )
        {
            double t = ((float*)tw)[i];
            tmat.data.ptr = u->data.ptr + i*u->step;
            t = t > FLT_EPSILON ? 1./t : 0;
            if( i == mn - 1 )
                condition_number = t != 0 ? ((float*)tw)[0]*t : DBL_MAX;
            cvScale( &tmat, &tmat, t );
        }
    }
    else
    {
        for( int i = 0; i < nm; i++ )
        {
            double t = ((double*)tw)[i];
            tmat.data.ptr = u->data.ptr + i*u->step;
            t = t > DBL_EPSILON ? 1./t : 0;
            if( i == mn - 1 )
                condition_number = t != 0 ? ((double*)tw)[0]*t : DBL_MAX;
            cvScale( &tmat, &tmat, t );
        }
    }

    u->height = n;
    if( n > m )
    {
        cvGetSubArr( u, &tmat, cvRect( 0, m, m, n - m ));
        cvSetZero( &tmat );
    }
    
    cvMatMulAdd( v, u, 0, b );

    CV_CHECK_NANS( b );

    __END__;

    if( buffer && !local_alloc )
        cvFree( (void**)&buffer );

    return condition_number;
}

/* End of file. */
