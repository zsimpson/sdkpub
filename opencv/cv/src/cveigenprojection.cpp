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

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Names: icvEigenProjection_8u32fR
//    Purpose: The function calculates object projection to the eigen sub-space (restores
//             an object) using previously calculated eigen objects basis, mean (averaged)
//             object and decomposition coefficients of the restored object
//    Context:
//    Parameters:  nEigObjs - number of eigen objects
//                 eigens  - array of pointers to eigen objects
//                 eigStep  - eigen objects step (in bytes)
//                 coeffs   - previousely calculated decomposition coefficients
//                 avg      - pointer to averaged object
//                 avgStep  - its step (in bytes)
//                 rest     - pointer to restored object
//                 restStep - its step (in bytes)
//                 size     - ROI size of each object
//
//    Returns: CV status
//
//    Notes:
//F*/
IPCVAPI_IMPL( CvStatus, icvEigenProjection_8u32fR, (int nEigObjs,
                                                    void *eigInput,
                                                    int eigStep,
                                                    int ioFlags,
                                                    void *userData,
                                                    float *coeffs,
                                                    float *avg,
                                                    int avgStep,
                                                    uchar * rest, int restStep, CvSize size) )
{
    int i, j, k;
    float *buf;
    float *buffer = NULL;
    float *b;
    CvCallback read_callback = ((CvInput *) & eigInput)->callback;

    if( size.width > avgStep || 4 * size.width > eigStep || size.height < 1 )
        return CV_BADSIZE_ERR;
    if( rest == NULL || eigInput == NULL || avg == NULL || coeffs == NULL )
        return CV_NULLPTR_ERR;
    if( ioFlags < 0 || ioFlags > 1 )
        return CV_BADFACTOR_ERR;
    if( !ioFlags )
        for( i = 0; i < nEigObjs; i++ )
            if( ((uchar **) eigInput)[i] == NULL )
                return CV_NULLPTR_ERR;
    eigStep /= 4;
    avgStep /= 4;

    if( size.width == restStep && size.width == eigStep && size.width == avgStep )
    {
        size.width *= size.height;
        size.height = 1;
        restStep = eigStep = avgStep = size.width;
    }

    buf = (float *) icvAlloc( sizeof( float ) * size.width * size.height );

    if( buf == NULL )
        return CV_OUTOFMEM_ERR;
    b = buf;
    for( i = 0; i < size.height; i++, avg += avgStep, b += size.width )
        for( j = 0; j < size.width; j++ )
            b[j] = avg[j];

    if( ioFlags )
    {
        buffer = (float *) icvAlloc( sizeof( float ) * size.width * size.height );

        if( buffer == NULL )
        {
            icvFree( (void **) &buf );
            return CV_OUTOFMEM_ERR;
        }
        eigStep = size.width;
    }

    for( k = 0; k < nEigObjs; k++ )
    {
        float *e = ioFlags ? buffer : ((float **) eigInput)[k];
        float c = coeffs[k];

        if( ioFlags )           /* read eigen object */
        {
            CvStatus r = read_callback( k, (void *) buffer, userData );

            if( r )
            {
                icvFree( (void **) &buf );
                icvFree( (void **) &buffer );
                return r;
            }
        }

        b = buf;
        for( i = 0; i < size.height; i++, e += eigStep, b += size.width )
        {
            for( j = 0; j < size.width - 3; j += 4 )
            {
                float b0 = c * e[j];
                float b1 = c * e[j + 1];
                float b2 = c * e[j + 2];
                float b3 = c * e[j + 3];

                b[j] += b0;
                b[j + 1] += b1;
                b[j + 2] += b2;
                b[j + 3] += b3;
            }
            for( ; j < size.width; j++ )
                b[j] += c * e[j];
        }
    }

    b = buf;
    for( i = 0; i < size.height; i++, avg += avgStep, b += size.width, rest += restStep )
        for( j = 0; j < size.width; j++ )
        {
            int w = cvRound( b[j] );

            w = !(w & ~255) ? w : w < 0 ? 0 : 255;
            rest[j] = (uchar) w;
        }

    icvFree( (void **) &buf );
    if( ioFlags )
        icvFree( (void **) &buffer );
    return CV_NO_ERR;
}

/*   End  of  file   */
