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
#include "_cvgeom.h"


/* Projects every point in the array points3D on the plane given by the index -- yz for 0, 
   zx for 1 and xy for 2. If swap flag is set to nonzero, then the coordinates exchange places, 
   that is planes zy, xz, yx correspondingly. */
CvStatus
icvProject3D( CvPoint3D32f * points3D, int count, CvPoint2D32f * points2D,
              int index1, int index2 )
{
    int i;
    float *f3D = (float *) points3D;
    float *f2D = (float *) points2D;

    if( !points3D || !points2D )
    {
        return CV_NULLPTR_ERR;
    }

    if( count <= 0 )
    {
        return CV_BADFACTOR_ERR;
    }

    if( index1 < 0 || index1 > 2 || index2 < 0 || index2 > 2 )
    {
        return CV_BADFACTOR_ERR;
    }

    for( i = 0; i < count; i++ )
    {
        f2D[2 * i] = f3D[3 * i + index1];
        f2D[2 * i + 1] = f3D[3 * i + index2];
    }


    return CV_NO_ERR;
}
