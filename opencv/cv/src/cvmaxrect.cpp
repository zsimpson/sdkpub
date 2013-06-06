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


IPCVAPI_IMPL( CvStatus, icvMaxRect, (CvRect * rect1, CvRect * rect2, CvRect * max_rect) )
{
    int curx, cury, maxx, maxy;


    if( rect1 == NULL || rect2 == NULL || max_rect == NULL )
        return CV_NULLPTR_ERR;
    else
    {
        *max_rect = *rect1;
        maxx = max_rect->x + max_rect->width;
        maxy = max_rect->y + max_rect->height;
        curx = rect2->x + rect2->width;
        cury = rect2->y + rect2->height;

        if( max_rect->x > rect2->x )
            max_rect->x = rect2->x;
        if( max_rect->y > rect2->y )
            max_rect->y = rect2->y;

        if( maxx < curx )
            max_rect->width = curx - max_rect->x;
        else
            max_rect->width = maxx - max_rect->x;
        if( maxy < cury )
            max_rect->height = cury - max_rect->y;
        else
            max_rect->height = maxy - max_rect->y;
    }
    return CV_OK;
}
