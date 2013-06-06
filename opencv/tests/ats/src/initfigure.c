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

#include "ats.h"

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsbInitEllipse
//    Purpose: filling the source 2D array by constant value
//    Context:
//    Parameters:
//      Src - source array
//      width - width of source array
//      height - height of source array
//      step - width step
//      x, y - center of ellipse
//      major - major axis of ellipse
//      minor - minor axis of ellipse
//      orientation - orientation of ellipse
//      value - the constant value which will be set within elipse
//    Returns:
//    Notes:
//      orientation is the angle from horisontal clockwise
//F*/
void atsbInitEllipse( uchar* Src,
                      int    width,
                      int    height,
                      int    step,
                      int    x,
                      int    y,
                      int    major,
                      int    minor,
                      float  orientation,
                      uchar  value )
{
    /* Some variables */
    int   i, j;
    float cx, cy;

    /* Filling */
    for( i = 0; i < height; i++ )
    {
        for( j = 0; j < width; j++ )
        {
            cx =  (float)((j - x) * cos( orientation ) + (i - y) * sin( orientation ));
            cy = (float)(-(j - x) * sin( orientation ) + (i - y) * cos( orientation ));
            if( (cx * cx) / (major * major) + (cy * cy) / (minor * minor) <= 1.0f )
                Src[j] = value;
            else Src[j] = 0;
        }
        Src += step;
    }
} /* atsbInitEllipse */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsfInitEllipse
//    Purpose: filling the source 2D array by constant value
//    Context:
//    Parameters:
//      Src - source array
//      width - width of source array
//      height - height of source array
//      step - width step
//      x, y - center of ellipse
//      major - major axis of ellipse
//      minor - minor axis of ellipse
//      orientation - orientation of ellipse
//      value - the constant value which will be set within elipse
//    Returns:
//    Notes:
//      orientation is the angle from horisontal clockwise
//F*/
void atsfInitEllipse( float* Src,
                      int    width,
                      int    height,
                      int    step,
                      int    x,
                      int    y,
                      int    major,
                      int    minor,
                      float  orientation,
                      float  value )
{
    /* Some variables */
    int   i, j;
    float cx, cy;

    /* Filling */
    for( i = 0; i < height; i++ )
    {
        for( j = 0; j < width; j++ )
        {
            cx =  (float)((j - x) * cos( orientation ) + (i - y) * sin( orientation ));
            cy = (float)(-(j - x) * sin( orientation ) + (i - y) * cos( orientation ));
            if( (cx * cx) / (major * major) + (cy * cy) / (minor * minor) <= 1.0f )
                Src[j] = value;
            else Src[j] = 0;
        }
        Src = (float*)((long)Src + step);
    }
} /* atsfInitEllipse */


/* End of file. */
