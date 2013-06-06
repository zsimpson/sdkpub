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
//    Name: icvCalcCovarMatrixEx_8u32fR
//    Purpose: The function calculates a covariance matrix for a group of input objects
//             (images, vectors, etc.). ROI supported.
//    Context:
//    Parameters:  nObjects    - number of source objects
//                 objects     - array of pointers to ROIs of the source objects
//                 imgStep     - full width of each source object row in bytes
//                 avg         - pointer to averaged object
//                 avgStep     - full width of averaged object row in bytes
//                 size        - ROI size of each source and averaged objects
//                 covarMatrix - covariance matrix (output parameter; must be allocated
//                               before call)
//
//    Returns: CV_NO_ERR or error code
//
//    Notes:   
//F*/

IPCVAPI_IMPL( CvStatus, icvCalcCovarMatrixEx_8u32fR, (int nObjects,
                                                      void *input,
                                                      int objStep1,
                                                      int ioFlags,
                                                      int ioBufSize,
                                                      uchar * buffer,
                                                      void *userData,
                                                      float *avg,
                                                      int avgStep,
                                                      CvSize size, float *covarMatrix) )
{
    int objStep = objStep1;

    /* ---- TEST OF PARAMETERS ---- */

    if( nObjects < 2 )
        return CV_BADFACTOR_ERR;
    if( ioFlags < 0 || ioFlags > 3 )
        return CV_BADFACTOR_ERR;
    if( ioFlags && ioBufSize < 1024 )
        return CV_BADFACTOR_ERR;
    if( ioFlags && buffer == NULL )
        return CV_NULLPTR_ERR;
    if( input == NULL || avg == NULL || covarMatrix == NULL )
        return CV_NULLPTR_ERR;
    if( size.width > objStep || 4 * size.width > avgStep || size.height < 1 )
        return CV_BADSIZE_ERR;

    avgStep /= 4;

    if( ioFlags & CV_EIGOBJ_INPUT_CALLBACK )    /* ==== USE INPUT CALLBACK ==== */
    {
        int nio, ngr, igr, n = size.width * size.height, mm = 0;
        CvCallback read_callback = ((CvInput *) & input)->callback;
        uchar *buffer2;

        objStep = n;
        nio = ioBufSize / n;    /* number of objects in buffer */
        ngr = nObjects / nio;   /* number of io groups */
        if( nObjects % nio )
            mm = 1;
        ngr += mm;

        buffer2 = (uchar *) icvAlloc( sizeof( uchar ) * n );
        if( buffer2 == NULL )
            return CV_OUTOFMEM_ERR;

        for( igr = 0; igr < ngr; igr++ )
        {
            int k, l;
            int io, jo, imin = igr * nio, imax = imin + nio;
            uchar *bu1 = buffer, *bu2;

            if( imax > nObjects )
                imax = nObjects;

            /* read igr group */
            for( io = imin; io < imax; io++, bu1 += n )
            {
                CvStatus r;

                r = read_callback( io, (void *) bu1, userData );
                if( r )
                    return r;
            }

            /* diagonal square calc */
            bu1 = buffer;
            for( io = imin; io < imax; io++, bu1 += n )
            {
                bu2 = bu1;
                for( jo = io; jo < imax; jo++, bu2 += n )
                {
                    float w = 0.f;
                    float *fu = avg;
                    int ij = 0;

                    for( k = 0; k < size.height; k++, fu += avgStep )
                        for( l = 0; l < size.width; l++, ij++ )
                        {
                            float f = fu[l], u1 = bu1[ij], u2 = bu2[ij];

                            w += (u1 - f) * (u2 - f);
                        }
                    covarMatrix[io * nObjects + jo] = covarMatrix[jo * nObjects + io] = w;
                }
            }

            /* non-diagonal elements calc */
            for( jo = imax; jo < nObjects; jo++ )
            {
                CvStatus r;

                bu1 = buffer;
                bu2 = buffer2;

                /* read jo object */
                r = read_callback( jo, (void *) bu2, userData );
                if( r )
                    return r;

                for( io = imin; io < imax; io++, bu1 += n )
                {
                    float w = 0.f;
                    float *fu = avg;
                    int ij = 0;

                    for( k = 0; k < size.height; k++, fu += avgStep )
                    {
                        for( l = 0; l < size.width - 3; l += 4, ij += 4 )
                        {
                            float f = fu[l];
                            uchar u1 = bu1[ij];
                            uchar u2 = bu2[ij];

                            w += (u1 - f) * (u2 - f);
                            f = fu[l + 1];
                            u1 = bu1[ij + 1];
                            u2 = bu2[ij + 1];
                            w += (u1 - f) * (u2 - f);
                            f = fu[l + 2];
                            u1 = bu1[ij + 2];
                            u2 = bu2[ij + 2];
                            w += (u1 - f) * (u2 - f);
                            f = fu[l + 3];
                            u1 = bu1[ij + 3];
                            u2 = bu2[ij + 3];
                            w += (u1 - f) * (u2 - f);
                        }
                        for( ; l < size.width; l++, ij++ )
                        {
                            float f = fu[l], u1 = bu1[ij], u2 = bu2[ij];

                            w += (u1 - f) * (u2 - f);
                        }
                    }
                    covarMatrix[io * nObjects + jo] = covarMatrix[jo * nObjects + io] = w;
                }
            }
        }                       /* igr */

        icvFree( (void **) &buffer2 );
    }                           /* if() */

    else
        /* ==== NOT USE INPUT CALLBACK ==== */
    {
        int i, j;
        uchar **objects = (uchar **) (((CvInput *) & input)->data);

        for( i = 0; i < nObjects; i++ )
        {
            uchar *bu = objects[i];

            for( j = i; j < nObjects; j++ )
            {
                int k, l;
                float w = 0.f;
                float *a = avg;
                uchar *bu1 = bu;
                uchar *bu2 = objects[j];

                for( k = 0; k < size.height;
                     k++, bu1 += objStep, bu2 += objStep, a += avgStep )
                {
                    for( l = 0; l < size.width - 3; l += 4 )
                    {
                        float f = a[l];
                        uchar u1 = bu1[l];
                        uchar u2 = bu2[l];

                        w += (u1 - f) * (u2 - f);
                        f = a[l + 1];
                        u1 = bu1[l + 1];
                        u2 = bu2[l + 1];
                        w += (u1 - f) * (u2 - f);
                        f = a[l + 2];
                        u1 = bu1[l + 2];
                        u2 = bu2[l + 2];
                        w += (u1 - f) * (u2 - f);
                        f = a[l + 3];
                        u1 = bu1[l + 3];
                        u2 = bu2[l + 3];
                        w += (u1 - f) * (u2 - f);
                    }
                    for( ; l < size.width; l++ )
                    {
                        float f = a[l];
                        uchar u1 = bu1[l];
                        uchar u2 = bu2[l];

                        w += (u1 - f) * (u2 - f);
                    }
                }

                covarMatrix[i * nObjects + j] = covarMatrix[j * nObjects + i] = w;
            }
        }
    }                           /* else */

    return CV_NO_ERR;
}

/*======================== end of icvCalcCovarMatrixEx_8u32fR ===========================*/

/*  End  of  file  */
