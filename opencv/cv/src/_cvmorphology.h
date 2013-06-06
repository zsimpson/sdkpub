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

#ifndef _CVMORPHOLOGY_H_
#define _CVMORPHOLOGY_H_

#include "_cvConvert.h"

/* type of structuring element */
typedef struct
{
    int      step;
    char*    top;
    char*    bottom;
    int      left;
    int      xa, xb; /* area where the */
    int      ya, yb; /* element is not in the image entirely. */
    int      y1, y2; /* area where the intersection of element and image is empty. */
    int      invert; /* area inversion flag */
    int      ya1;    /* how many lines of the kernel are active at first */
    int      rows, cols;
    char*    rect_buffer; /* temporary buffer for "rectangular element" morphology */
    CvElementShape shape;
    CvSize  size;
}
_CvMorphKernel;


#define _CV_MORPH_FUNC( name )              \
        void name( _CvRingBuffer*  src_rb,  \
                   _CvRingBuffer*  mid_rb,  \
                   _CvRingBuffer*  dst_rb,  \
                   _CvMorphKernel* ker,     \
                   int y, int dl )

typedef _CV_MORPH_FUNC( (*_CvMorphFunc) );

typedef struct
{
    int    datatype;
    int    channels;

    char*  src;
    char*  dst;
    int    src_step;
    int    dst_step;

    int    delta_lines;
    int    buf_size;
    int    allocated;

    char*  buffer;
   
    _CvRingBuffer   src_rb[4];
    _CvRingBuffer   dst_rb[3];
    _CvRingBuffer   mid_rb[3];

    _CvMorphKernel  ker;

    _CvMorphFunc    mop;
    icvCvtPixToPlaneFunc pxpl;
    icvCvtPlaneToPixFunc plpx;
}
_CvMorphState;

/* universal initialization function */
CvStatus  icvInitMorphology(
                  int   datatype,
                  int   channels,
                  int   is_erode,
                  char* src, int  src_step,
                  char* dst, int  dst_step,
                  CvSize size,
                  CvConvKernel* B,
                  _CvMorphState* st,
                  char* local_buffer,
                  int   local_buffer_size,
                  int   delta_lines );

void icvFreeMorphology( _CvMorphState* st );

#endif/*_CVMORPHOLOGY_H_*/

/* End of file. */
