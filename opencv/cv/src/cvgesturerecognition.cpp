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


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     cvCalcImageHomography
//    Purpose:  calculates the cooficients of the homography matrix
//    Context:   
//    Parameters: 
//      line   - pointer to the input 3D-line
//      center - pointer to the input hand center
//      intrinsic - intrinsic camera parameters matrix
//      homography - result homography matrix
//      
//    Notes:
//F*/
CV_IMPL void
cvCalcImageHomography( float *line, CvPoint3D32f * center,
                       float intrinsic[3][3], float homography[3][3] )
{
    CV_FUNCNAME( "cvCalcImageHomography" );
    __BEGIN__;

    IPPI_CALL( icvCalcImageHomography( line, center, intrinsic, homography ));

    __CLEANUP__;
    __END__;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     cvCreateHandMask
//    Purpose:  creates hand mask image
//    Context:   
//    Parameters: 
//      numbers - pointer to the input sequence of the point's indexes inside
//                hand region                
//      img_mask - pointer to the result mask image 
//      roi      - result hand mask ROI 
//      
//    Notes:
//F*/
CV_IMPL void
cvCreateHandMask( CvSeq * numbers, IplImage * img_mask, CvRect * roi )
{
    uchar *img_mask_data = 0;
    int img_mask_step = 0;
    CvSize img_mask_size;

    CV_FUNCNAME( "cvCreateHandMask" );

    __BEGIN__;

    CV_CALL( CV_CHECK_IMAGE( img_mask ));

    if( img_mask->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );

    if( img_mask->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, "output image have wrong number of channels" );

    cvGetImageRawData( img_mask, &img_mask_data, &img_mask_step, &img_mask_size );

    IPPI_CALL( icvCreateHandMask8uC1R( numbers, img_mask_data,
                                        img_mask_step, img_mask_size, roi ));

    __CLEANUP__;
    __END__;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     cvCalcProbDensity
//    Purpose:  calculates hand mask probability density
//    Context:   
//    Parameters: 
//      hist      - pointer to the input image histogram
//      hist_mask - pointer to the input image mask histogram
//      hist_dens - pointer to the result probability density histogram
//      
//    Notes:
//F*/
CV_IMPL void
cvCalcProbDensity( CvHistogram * hist, CvHistogram * hist_mask, CvHistogram * hist_dens )
{
    CV_FUNCNAME( "cvCalcProbDensity" );

    __BEGIN__;

    IPPI_CALL( icvCalcProbDensity( hist, hist_mask, hist_dens ));

    __CLEANUP__;
    __END__;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     cvMaxRect
//    Purpose:  calculates maximum rectangle
//    Context:   
//    Parameters: 
//      rect1      - pointer to the first input rectangle
//      rect2      - pointer to the second input rectangle
//      max_rect   - pointer to the result maximum rectangle
//      
//    Notes:
//F*/
CV_IMPL void
cvMaxRect( CvRect * rect1, CvRect * rect2, CvRect * max_rect )
{
    CV_FUNCNAME( "cvMaxRect" );

    __BEGIN__;

    IPPI_CALL( icvMaxRect( rect1, rect2, max_rect ));

    __CLEANUP__;
    __END__;
}
