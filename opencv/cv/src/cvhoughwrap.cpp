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
#include "_cvwrap.h"

/* Wrapper function for standard hough transform */
CV_IMPL int
cvHoughLines( IplImage * src, double rho, double theta, int threshold,
              float *lines, int linesNumber )
{
    int ret = -1;

    CV_FUNCNAME( "cvHoughLines" );

    __BEGIN__;
    uchar *src_data = 0;
    CvSize src_size;
    int src_step;

    CV_CALL( CV_CHECK_IMAGE( src ));

    if( src->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, "Source image must have only one channel." );

    if( src->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, "Wrong depth of source image." );

    cvGetImageRawData( src, &src_data, &src_step, &src_size );

    ret = icvHoughLines_8uC1R( src_data, src_step, src_size, (float) rho, (float) theta,
                                threshold, lines, linesNumber );
    if( ret < 0 )
        CV_ERROR( IPL_StsBadArg, "Bad argument." );

    __END__;
    
    return ret;    
}

CV_IMPL int
cvHoughLinesP( IplImage * src, double rho, double theta, int threshold,
               int lineLength, int lineGap, int *lines, int linesNumber )
{
    int ret = -1;

    __BEGIN__;
    uchar *src_data = 0;
    CvSize src_size;
    int src_step;

    CV_FUNCNAME( "cvHoughLinesP" );

    CV_CALL( CV_CHECK_IMAGE( src ));

    if( src->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, "Source image must have only one channel." );

    if( src->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, "Wrong depth of source image." );

    cvGetImageRawData( src, &src_data, &src_step, &src_size );

    ret = icvHoughLinesP_8uC1R( src_data, src_step, src_size, (float) rho, (float) theta,
                                 threshold, lineLength, lineGap, lines, linesNumber );
    if( ret < 0 )
        CV_ERROR( IPL_StsBadArg, "Bad argument." );

    __END__;
    return ret;    
}


CV_IMPL int
cvHoughLinesSDiv( IplImage * image,
                  double rho, int srn, double theta, int stn,
                  int threshold, float *lines, int lines_number )
{
    int ret = -1;

    CV_FUNCNAME( "cvHoughLinesSDiv" );

    __BEGIN__;

    if( image->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );

    if( image->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, "input image has more than one channel" );

    uchar *data;
    CvSize size;
    int step;

    cvGetImageRawData( image, &data, &step, &size );

    ret = icvHoughLinesSDiv_8uC1R( data, step, size, (float) rho, srn,
                                    (float) theta, stn, threshold, lines, lines_number );
    if( ret < 0 )
        CV_ERROR( IPL_StsBadArg, "Bad argument." );

    __END__;
    
    return ret;    
}

/* End of file. */
