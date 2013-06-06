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
void __fl2db( float* fl, double* db, int n )
{
    int i;
    for( i=0; i<n; i++ ) db[i] = (double)fl[i];
}

double __DotProduct( double* a1, double* a2, int n )
{
    int i;
    double dp = 0;
    for( i=0; i<n; i++ ) dp += a1[i]*a2[i];
    return dp;
}

void __CrossProduct( double* a, double* b, double* res )
{
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

double __Trace( double* a, int ny, int nx )
{
    int i, n = nx;
    double t = 0;
    if( ny < nx )  n=ny;
    for( i=0; i<n; i++, a+=(nx+1) ) t += *a;
    return t;
}

void __MulTrans( double* src, double* dst, int ny, int nx, int k )
{
    int i, j, l;

    if( k==0 )
    {
        for( i=0; i<ny; i++ )
            for( j=0; j<ny; j++ )
            {
                double w = 0;
                for( l=0; l<nx; l++ )  w += src[i*nx+l] * src[j*nx+l];
                dst[i*ny+j] = w;
            }
    }

    else

    {
        for( i=0; i<nx; i++ )
            for( j=0; j<nx; j++ )
            {
                double w = 0;
                for( l=0; l<ny; l++ )  w += src[l*nx+i] * src[l*nx+j];
                dst[i*nx+j] = w;
            }
    }

}

double __Det( double* a, int n )
{
    int i, ii, j, iin;
    double det = 1.0e0, eps0 = 1.0e-40, norm = 0, eps;

    if( n==0 ) return 0;
    if( n==1 ) return *a;
    if( n==2 ) return a[0]*a[3] - a[1]*a[2];

    for( i=0; i<n*n; i++ ) norm += fabs( a[i] );

    norm /= n*n;
    eps   = eps0*norm;

    for( i=0; i<n-1; i++ )
    {
        double w0;
        int     in = i*n;
        double max = fabs( a[in+i] );
        int   jmax = i;

        for( j=i+1; j<n; j++ )
        {
            double m = fabs(a[j*n+i]);
            if( m > max )
            {
                max  = m;
                jmax = j;
            }
        }

        if( max < eps ) return 0.0;

        if( jmax > i )
        {
            jmax *= n;

            for( j=i; j<n; j++ )
            {
                double b  = a[in+j];
                a[in+j]   = a[jmax+j];
                a[jmax+j] = b;
            }

            det = -det;
        }

        w0 = 1.0e0 / a[in+i];
        for( ii=i+1, iin=(i+1)*n; ii<n; ii++, iin+=n )
        {
            if( a[iin+i] )
            {
                double w = -a[iin+i]*w0;
                for( j=i+1; j<n; j++ )  a[iin+j] += w*a[in+j];
            }
        }
    }


    for( i=0; i<n; i++, a+=n+1 ) det *= *a;

    return det;
}

