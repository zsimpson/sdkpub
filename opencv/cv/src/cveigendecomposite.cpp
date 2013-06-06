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
//    Name: icvCalcDecompCoeff_8u32fR
//    Purpose: The function calculates one decomposition coefficient of input object
//             using previously calculated eigen object and the mean (averaged) object
//    Context:
//    Parameters:  obj     - input object
//                 objStep - its step (in bytes)
//                 eigObj  - pointer to eigen object
//                 eigStep - its step (in bytes)
//                 avg     - pointer to averaged object
//                 avgStep - its step (in bytes)
//                 size    - ROI size of each source object
//
//    Returns: decomposition coefficient value or large negative value (if error)
//
//    Notes:
//F*/
IPCVAPI_IMPL( float, icvCalcDecompCoeff_8u32fR, (uchar * obj,
                                                 int objStep,
                                                 float *eigObj,
                                                 int eigStep,
                                                 float *avg, int avgStep, CvSize size) )
{
    int i, k;
    float w = 0.0f;

    if( size.width > objStep || 4 * size.width > eigStep
        || 4 * size.width > avgStep || size.height < 1 )
        return -1.0e30f;
    if( obj == NULL || eigObj == NULL || avg == NULL )
        return -1.0e30f;

    eigStep /= 4;
    avgStep /= 4;

    if( size.width == objStep && size.width == eigStep && size.width == avgStep )
    {
        size.width *= size.height;
        size.height = 1;
        objStep = eigStep = avgStep = size.width;
    }

    for( i = 0; i < size.height; i++, obj += objStep, eigObj += eigStep, avg += avgStep )
    {
        for( k = 0; k < size.width - 4; k += 4 )
        {
            float o = (float) obj[k];
            float e = eigObj[k];
            float a = avg[k];

            w += e * (o - a);
            o = (float) obj[k + 1];
            e = eigObj[k + 1];
            a = avg[k + 1];
            w += e * (o - a);
            o = (float) obj[k + 2];
            e = eigObj[k + 2];
            a = avg[k + 2];
            w += e * (o - a);
            o = (float) obj[k + 3];
            e = eigObj[k + 3];
            a = avg[k + 3];
            w += e * (o - a);
        }
        for( ; k < size.width; k++ )
            w += eigObj[k] * ((float) obj[k] - avg[k]);
    }

    return w;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Names: icvEigenDecomposite_8u32fR
//    Purpose: The function calculates all decomposition coefficients for input object
//             using previously calculated eigen objects basis and the mean (averaged)
//             object
//    Context:
//    Parameters:  obj         - input object
//                 objStep     - its step (in bytes)
//                 nEigObjs    - number of eigen objects
//                 eigInput    - pointer either to array of pointers to eigen objects
//                               or to read callback function (depending on ioFlags)
//                 eigStep     - eigen objects step (in bytes)
//                 ioFlags     - input/output flags
//                 iserData    - pointer to the structure which contains all necessary
//                               data for the callback function
//                 avg         - pointer to averaged object
//                 avgStep     - its step (in bytes)
//                 size        - ROI size of each source object
//                 coeffs      - calculated coefficients (output data)
//
//    Returns: icv status
//
//    Notes:   see notes for icvCalcEigenObjects_8u32fR function
//F*/
IPCVAPI_IMPL( CvStatus, icvEigenDecomposite_8u32fR, (uchar * obj,
                                                     int objStep,
                                                     int nEigObjs,
                                                     void *eigInput,
                                                     int eigStep,
                                                     int ioFlags,
                                                     void *userData,
                                                     float *avg,
                                                     int avgStep, CvSize size, float *coeffs) )
{
    int i;

    if( nEigObjs < 2 )
        return CV_BADFACTOR_ERR;
    if( ioFlags < 0 || ioFlags > 1 )
        return CV_BADFACTOR_ERR;
    if( size.width > objStep || 4 * size.width > eigStep ||
        4 * size.width > avgStep || size.height < 1 )
        return CV_BADSIZE_ERR;
    if( obj == NULL || eigInput == NULL || coeffs == NULL || avg == NULL )
        return CV_NULLPTR_ERR;
    if( !ioFlags )
        for( i = 0; i < nEigObjs; i++ )
            if( ((uchar **) eigInput)[i] == NULL )
                return CV_NULLPTR_ERR;

    if( ioFlags )               /* callback */

    {
        float *buffer;
        CvCallback read_callback = ((CvInput *) & eigInput)->callback;

        eigStep = 4 * size.width;

        /* memory allocation */
        buffer = (float *) icvAlloc( sizeof( float ) * size.width * size.height );

        if( buffer == NULL )
            return CV_OUTOFMEM_ERR;

        for( i = 0; i < nEigObjs; i++ )
        {
            float w;
            CvStatus r = read_callback( i, (void *) buffer, userData );

            if( r )
            {
                icvFree( (void **) &buffer );
                return r;
            }
            w = icvCalcDecompCoeff_8u32fR( obj, objStep, buffer,
                                            eigStep, avg, avgStep, size );
            if( w < -1.0e29f )
            {
                icvFree( (void **) &buffer );
                return CV_NOTDEFINED_ERR;
            }
            coeffs[i] = w;
        }
        icvFree( (void **) &buffer );
    }

    else
        /* no callback */
        for( i = 0; i < nEigObjs; i++ )
        {
            float w = icvCalcDecompCoeff_8u32fR( obj, objStep, ((float **) eigInput)[i],
                                                  eigStep, avg, avgStep, size );

            if( w < -1.0e29f )
                return CV_NOTDEFINED_ERR;
            coeffs[i] = w;
        }

    return CV_NO_ERR;
}


/*  End  of  file  */
