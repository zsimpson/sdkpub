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

static int
icvDefaultBufferSize( void )
{
    return 10 * 1024 * 1024;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: icvCalcEigenObjects_8u32fR
//    Purpose: The function calculates an orthonormal eigen basis and a mean (averaged)
//             object for a group of input objects (images, vectors, etc.). ROI supported.
//    Context:
//    Parameters: nObjects  - number of source objects
//                input     - pointer either to array of pointers to input objects
//                            or to read callback function (depending on ioFlags)
//                imgStep   - full width of each source object row in bytes
//                output    - pointer either to array of pointers to output eigen objects
//                            or to write callback function (depending on ioFlags)
//                eigStep   - full width of each eigenobject row in bytes
//                size      - ROI size of each source object
//                ioFlags   - input/output flags (see Notes)
//                ioBufSize - input/output buffer size
//                userData  - pointer to the structure which contains all necessary
//                            data for the callback functions
//                calcLimit - determines the calculation finish conditions
//                avg       - pointer to averaged object (has the same size as ROI)
//                avgStep   - full width of averaged object row in bytes
//                eigVals   - pointer to corresponding eigenvalues (array of <nObjects>
//                            elements in descending order)
//
//    Returns: CV_NO_ERR or error code
//
//    Notes: 1. input/output data (that is, input objects and eigen ones) may either
//              be allocated in the RAM or be read from/written to the HDD (or any
//              other device) by read/write callback functions. It depends on the
//              value of ioFlags paramater, which may be the following:
//                  CV_EIGOBJ_NO_CALLBACK, or 0;
//                  CV_EIGOBJ_INPUT_CALLBACK;
//                  CV_EIGOBJ_OUTPUT_CALLBACK;
//                  CV_EIGOBJ_BOTH_CALLBACK, or
//                            CV_EIGOBJ_INPUT_CALLBACK | CV_EIGOBJ_OUTPUT_CALLBACK.
//              The callback functions as well as the user data structure must be
//              developed by the user.
//
//           2. If ioBufSize = 0, or it's too large, the function dermines buffer size
//              itself.
//
//           3. Depending on calcLimit parameter, calculations are finished either if
//              eigenfaces number comes up to certain value or the relation of the
//              current eigenvalue and the largest one comes down to certain value
//              (or any of the above conditions takes place). The calcLimit->type value
//              must be CV_TERMCRIT_NUMB, CV_TERMCRIT_EPS or
//              CV_TERMCRIT_NUMB | CV_TERMCRIT_EPS. The function returns the real
//              values calcLimit->maxIter and calcLimit->epsilon.
//
//           4. eigVals may be equal to NULL (if you don't need eigen values in further).
//
//F*/

IPCVAPI_IMPL( CvStatus, icvCalcEigenObjects_8u32fR, (int    nObjects,
                                                     void*  input,
                                                     int    objStep,
                                                     void*  output,
                                                     int    eigStep,
                                                     CvSize size,
                                                     int    ioFlags,
                                                     int    ioBufSize,
                                                     void*  userData,
                                                     CvTermCriteria* calcLimit,
                                                     float* avg,
                                                     int    avgStep, 
                                                     float  *eigVals) )
{
    int i, j, n, iev = 0, m1 = nObjects - 1, objStep1 = objStep, eigStep1 = eigStep / 4;
    CvSize objSize, eigSize, avgSize;
    float *c = 0;
    float *ev = 0;
    float *bf = 0;
    uchar *buf = 0;
    void *buffer = 0;
    float m = 1.0f / (float) nObjects;
    CvStatus r;

    if( m1 > calcLimit->maxIter && calcLimit->type != CV_TERMCRIT_EPS )
        m1 = calcLimit->maxIter;

    /* ---- TEST OF PARAMETERS ---- */

    if( nObjects < 2 )
        return CV_BADFACTOR_ERR;
    if( ioFlags < 0 || ioFlags > 3 )
        return CV_BADFACTOR_ERR;
    if( input == NULL || output == NULL || avg == NULL )
        return CV_NULLPTR_ERR;
    if( size.width > objStep || 4 * size.width > eigStep ||
        4 * size.width > avgStep || size.height < 1 )
        return CV_BADSIZE_ERR;
    if( !(ioFlags & CV_EIGOBJ_INPUT_CALLBACK) )
        for( i = 0; i < nObjects; i++ )
            if( ((uchar **) input)[i] == NULL )
                return CV_NULLPTR_ERR;
    if( !(ioFlags & CV_EIGOBJ_OUTPUT_CALLBACK) )
        for( i = 0; i < m1; i++ )
            if( ((float **) output)[i] == NULL )
                return CV_NULLPTR_ERR;

    avgStep /= 4;
    eigStep /= 4;

    if( objStep == size.width && eigStep == size.width && avgStep == size.width )
    {
        size.width *= size.height;
        size.height = 1;
        objStep = objStep1 = eigStep = eigStep1 = avgStep = size.width;
    }
    objSize = eigSize = avgSize = size;

    if( ioFlags & CV_EIGOBJ_INPUT_CALLBACK )
    {
        objSize.width *= objSize.height;
        objSize.height = 1;
        objStep = objSize.width;
        objStep1 = size.width;
    }

    if( ioFlags & CV_EIGOBJ_OUTPUT_CALLBACK )
    {
        eigSize.width *= eigSize.height;
        eigSize.height = 1;
        eigStep = eigSize.width;
        eigStep1 = size.width;
    }

    n = objSize.height * objSize.width * (ioFlags & CV_EIGOBJ_INPUT_CALLBACK) +
        2 * eigSize.height * eigSize.width * (ioFlags & CV_EIGOBJ_OUTPUT_CALLBACK);

    /* Buffer size determination */
    if( ioFlags )
    {
        int size = icvDefaultBufferSize();
        ioBufSize = MIN( size, n );
    }

    /* memory allocation (if necesseay) */

    if( ioFlags & CV_EIGOBJ_INPUT_CALLBACK )
    {
        buf = (uchar *) icvAlloc( sizeof( uchar ) * objSize.width );
        if( buf == NULL )
            return CV_OUTOFMEM_ERR;
    }

    if( ioFlags )
    {
        buffer = (void *) icvAlloc( ioBufSize );
        if( buffer == NULL )
        {
            if( buf )
                icvFree( (void **) &buf );
            return CV_OUTOFMEM_ERR;
        }
    }

    /* Calculation of averaged object */
    bf = avg;
    for( i = 0; i < avgSize.height; i++, bf += avgStep )
        for( j = 0; j < avgSize.width; j++ )
            bf[j] = 0.f;

    for( i = 0; i < nObjects; i++ )
    {
        int k, l;
        uchar *bu = (ioFlags & CV_EIGOBJ_INPUT_CALLBACK) ? buf : ((uchar **) input)[i];

        if( ioFlags & CV_EIGOBJ_INPUT_CALLBACK )
        {
            CvCallback read_callback = ((CvInput *) & input)->callback;

            r = read_callback( i, (void *) buf, userData );
            if( r )
            {
                if( buffer )
                    icvFree( (void **) &buffer );
                if( buf )
                    icvFree( (void **) &buf );
                return r;
            }
        }

        bf = avg;
        for( k = 0; k < avgSize.height; k++, bf += avgStep, bu += objStep1 )
            for( l = 0; l < avgSize.width; l++ )
                bf[l] += bu[l];
    }

    bf = avg;
    for( i = 0; i < avgSize.height; i++, bf += avgStep )
        for( j = 0; j < avgSize.width; j++ )
            bf[j] *= m;

    /* Calculation of covariance matrix */
    c = (float *) icvAlloc( sizeof( float ) * nObjects * nObjects );

    if( c == NULL )
    {
        if( buffer )
            icvFree( (void **) &buffer );
        if( buf )
            icvFree( (void **) &buf );
        return CV_OUTOFMEM_ERR;
    }

    r = icvCalcCovarMatrixEx_8u32fR( nObjects, input, objStep1, ioFlags, ioBufSize,
                                      (uchar *) buffer, userData, avg, 4 * avgStep, size, c );
    if( r )
    {
        icvFree( (void **) &c );
        if( buffer )
            icvFree( (void **) &buffer );
        if( buf )
            icvFree( (void **) &buf );
        return r;
    }

    /* Calculation of eigenvalues & eigenvectors */
    ev = (float *) icvAlloc( sizeof( float ) * nObjects * nObjects );

    if( ev == NULL )
    {
        icvFree( (void **) &c );
        if( buffer )
            icvFree( (void **) &buffer );
        if( buf )
            icvFree( (void **) &buf );
        return CV_OUTOFMEM_ERR;
    }

    if( eigVals == NULL )
    {
        eigVals = (float *) icvAlloc( sizeof( float ) * nObjects );

        if( eigVals == NULL )
        {
            icvFree( (void **) &c );
            icvFree( (void **) &ev );
            if( buffer )
                icvFree( (void **) &buffer );
            if( buf )
                icvFree( (void **) &buf );
            return CV_OUTOFMEM_ERR;
        }
        iev = 1;
    }

    r = icvJacobiEigens_32f( c, ev, eigVals, nObjects, 0.0f );
    icvFree( (void **) &c );
    if( r )
    {
        icvFree( (void **) &ev );
        if( buffer )
            icvFree( (void **) &buffer );
        if( buf )
            icvFree( (void **) &buf );
        if( iev )
            icvFree( (void **) &eigVals );
        return r;
    }

    /* Eigen objects number determination */
    if( calcLimit->type != CV_TERMCRIT_NUMB )
    {
        for( i = 0; i < m1; i++ )
            if( fabs( eigVals[i] / eigVals[0] ) < calcLimit->epsilon )
                break;
        m1 = calcLimit->maxIter = i;
    }
    else
        m1 = calcLimit->maxIter;
    calcLimit->epsilon = (float) fabs( eigVals[m1 - 1] / eigVals[0] );

    for( i = 0; i < m1; i++ )
        eigVals[i] = (float) (1.0 / sqrt( eigVals[i] ));

    /* ----------------- Calculation of eigenobjects ----------------------- */
    if( ioFlags & CV_EIGOBJ_OUTPUT_CALLBACK )
    {
        int nio, ngr, igr;

        nio = ioBufSize / (4 * eigSize.width);  /* number of eigen objects in buffer */
        ngr = m1 / nio;         /* number of io groups */
        if( nObjects % nio )
            ngr += 1;

        for( igr = 0; igr < ngr; igr++ )
        {
            int i, io, ie, imin = igr * nio, imax = imin + nio;

            if( imax > m1 )
                imax = m1;

            for( i = 0; i < eigSize.width * (imax - imin); i++ )
                ((float *) buffer)[i] = 0.f;

            for( io = 0; io < nObjects; io++ )
            {
                uchar *bu = ioFlags & CV_EIGOBJ_INPUT_CALLBACK ? buf : ((uchar **) input)[io];

                if( ioFlags & CV_EIGOBJ_INPUT_CALLBACK )
                {
                    CvCallback read_callback = ((CvInput *) & input)->callback;

                    r = read_callback( io, (void *) buf, userData );
                    if( r )
                    {
                        icvFree( (void **) &ev );
                        if( iev )
                            icvFree( (void **) &eigVals );
                        if( buffer )
                            icvFree( (void **) &buffer );
                        if( buf )
                            icvFree( (void **) &buf );
                        return r;
                    }
                }

                for( ie = imin; ie < imax; ie++ )
                {
                    int k, l;
                    uchar *bv = bu;
                    float e = ev[ie * nObjects + io] * eigVals[ie];
                    float *be = ((float *) buffer) + ((ie - imin) * eigStep);

                    bf = avg;
                    for( k = 0; k < size.height; k++, bv += objStep1,
                         bf += avgStep, be += eigStep1 )
                    {
                        for( l = 0; l < size.width - 3; l += 4 )
                        {
                            float f = bf[l];
                            uchar v = bv[l];

                            be[l] += e * (v - f);
                            f = bf[l + 1];
                            v = bv[l + 1];
                            be[l + 1] += e * (v - f);
                            f = bf[l + 2];
                            v = bv[l + 2];
                            be[l + 2] += e * (v - f);
                            f = bf[l + 3];
                            v = bv[l + 3];
                            be[l + 3] += e * (v - f);
                        }
                        for( ; l < size.width; l++ )
                            be[l] += e * (bv[l] - bf[l]);
                    }
                }
            }                   /* io */

            for( ie = imin; ie < imax; ie++ )   /* calculated eigen objects writting */
            {
                CvCallback write_callback = ((CvInput *) & output)->callback;
                float *be = ((float *) buffer) + ((ie - imin) * eigStep);

                r = write_callback( ie, (void *) be, userData );
                if( r )
                {
                    icvFree( (void **) &ev );
                    if( iev )
                        icvFree( (void **) &eigVals );
                    if( buffer )
                        icvFree( (void **) &buffer );
                    if( buf )
                        icvFree( (void **) &buf );
                    return r;
                }
            }
        }                       /* igr */
    }

    else
    {
        int k, p, l;

        for( i = 0; i < m1; i++ )       /* e.o. annulation */
        {
            float *be = ((float **) output)[i];

            for( p = 0; p < eigSize.height; p++, be += eigStep )
                for( l = 0; l < eigSize.width; l++ )
                    be[l] = 0.0f;
        }

        for( k = 0; k < nObjects; k++ )
        {
            uchar *bv = (ioFlags & CV_EIGOBJ_INPUT_CALLBACK) ? buf : ((uchar **) input)[k];

            if( ioFlags & CV_EIGOBJ_INPUT_CALLBACK )
            {
                CvCallback read_callback = ((CvInput *) & input)->callback;

                r = read_callback( k, (void *) buf, userData );
                if( r )
                {
                    icvFree( (void **) &ev );
                    if( iev )
                        icvFree( (void **) &eigVals );
                    if( buffer )
                        icvFree( (void **) &buffer );
                    if( buf )
                        icvFree( (void **) &buf );
                    return r;
                }
            }

            for( i = 0; i < m1; i++ )
            {
                float v = eigVals[i] * ev[i * nObjects + k];
                float *be = ((float **) output)[i];
                uchar *bu = bv;

                bf = avg;

                for( p = 0; p < size.height; p++, bu += objStep1,
                     bf += avgStep, be += eigStep1 )
                {
                    for( l = 0; l < size.width - 3; l += 4 )
                    {
                        float f = bf[l];
                        uchar u = bu[l];

                        be[l] += v * (u - f);
                        f = bf[l + 1];
                        u = bu[l + 1];
                        be[l + 1] += v * (u - f);
                        f = bf[l + 2];
                        u = bu[l + 2];
                        be[l + 2] += v * (u - f);
                        f = bf[l + 3];
                        u = bu[l + 3];
                        be[l + 3] += v * (u - f);
                    }
                    for( ; l < size.width; l++ )
                        be[l] += v * (bu[l] - bf[l]);
                }
            }                   /* i */
        }                       /* k */
    }                           /* else */

    icvFree( (void **) &ev );
    if( iev )
        icvFree( (void **) &eigVals );
    else
        for( i = 0; i < m1; i++ )
            eigVals[i] = 1.f / (eigVals[i] * eigVals[i]);
    if( buffer )
        icvFree( (void **) &buffer );
    if( buf )
        icvFree( (void **) &buf );
    return CV_NO_ERR;
}

/* --- End of icvCalcEigenObjects_8u32fR --- */

/*  End  of  file  */
