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
//    Name: icvCalcCovarMatrix_8u32f, icvCalcCovarMatrix_32f
//    Purpose: The function calculates a covariance matrix for a group of input objects
//             (images, vectors, etc.)
//    Context:
//    Parameters:  nObjects    - number of source objects
//                 objects     - array of pointers to the source objects
//                 avg         - pointer to averaged object
//                 length      - number of elements in each source and averaged objects
//                 covarMatrix - covariance matrix (output parameter; must be allocated
//                               before call)
//
//    Returns: CVM_NO_ERR or error code
//
//    Notes:   
//F*/
IPCVAPI_IMPL( CvStatus, icvCalcCovarMatrix_8u32f, (int nObjects,
                                                   uchar ** objects,
                                                   float *avg,
                                                   int length, float *covarMatrix) )
{
    int i, j;

    if( nObjects < 2 || length < 2 )
        return CV_BADFACTOR_ERR;
    if( objects == NULL || avg == NULL || covarMatrix == NULL )
        return CV_NULLPTR_ERR;

    for( i = 0; i < nObjects; i++ )
    {
        unsigned char *bu1 = objects[i];

        for( j = i; j < nObjects; j++ )
        {
            int ij = i * nObjects + j, k;
            float w = 0.f;
            unsigned char *bu2 = objects[j];

            for( k = 0; k < length - 3; k += 4 )
            {
                float f = avg[k];
                unsigned char u1 = bu1[k];
                unsigned char u2 = bu2[k];

                w += (u1 - f) * (u2 - f);
                f = avg[k + 1];
                u1 = bu1[k + 1];
                u2 = bu2[k + 1];
                w += (u1 - f) * (u2 - f);
                f = avg[k + 2];
                u1 = bu1[k + 2];
                u2 = bu2[k + 2];
                w += (u1 - f) * (u2 - f);
                f = avg[k + 3];
                u1 = bu1[k + 3];
                u2 = bu2[k + 3];
                w += (u1 - f) * (u2 - f);
            }
            for( ; k < length; k++ )
            {
                float f = avg[k];
                unsigned char u1 = bu1[k];
                unsigned char u2 = bu2[k];

                w += (u1 - f) * (u2 - f);
            }

            covarMatrix[ij] = w;
            ij = j * nObjects + i;
            covarMatrix[ij] = w;
        }
    }

    return CV_NO_ERR;
}

/*------------------------ end of icvCalcCovarMatrix_8u32f ----------------------------*/

/* //////////////////////=--  Name: icvCalcCovarMatrix_32f  --=/////////////////////// */

IPCVAPI_IMPL( CvStatus, icvCalcCovarMatrix_32f, (int nObjects,
                                                 float **objects,
                                                 float *avg, int length, float *covarMatrix) )
{
    int i, j;

    if( nObjects < 2 || length < 2 )
        return CV_BADFACTOR_ERR;
    if( objects == NULL || avg == NULL || covarMatrix == NULL )
        return CV_NULLPTR_ERR;

    for( i = 0; i < nObjects; i++ )
    {
        float *bu1 = objects[i];

        for( j = i; j < nObjects; j++ )
        {
            int ij = i * nObjects + j, k;
            float w = 0.f;
            float *bu2 = objects[j];

            for( k = 0; k < length - 3; k += 4 )
            {
                float f = avg[k];
                float u1 = bu1[k];
                float u2 = bu2[k];

                w += (u1 - f) * (u2 - f);
                f = avg[k + 1];
                u1 = bu1[k + 1];
                u2 = bu2[k + 1];
                w += (u1 - f) * (u2 - f);
                f = avg[k + 2];
                u1 = bu1[k + 2];
                u2 = bu2[k + 2];
                w += (u1 - f) * (u2 - f);
                f = avg[k + 3];
                u1 = bu1[k + 3];
                u2 = bu2[k + 3];
                w += (u1 - f) * (u2 - f);
            }
            for( ; k < length; k++ )
            {
                float f = avg[k];
                float u1 = bu1[k];
                float u2 = bu2[k];

                w += (u1 - f) * (u2 - f);
            }

            covarMatrix[ij] = w;
            ij = j * nObjects + i;
            covarMatrix[ij] = w;
        }
    }

    return CV_NO_ERR;
}

/*--------------------- end of icvCalcCovarMatrix_32f -------------------------------*/

/*  End  of  file  */
