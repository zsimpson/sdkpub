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

CV_IMPL CvSeq*
cvConvexityDefects( CvSeq * contour, CvSeq * convexhull,
                    CvMemStorage * storage )
{
    CvSeq* defects = 0;
    
    CV_FUNCNAME( "cvConvexityDefects" );

    __BEGIN__;

    IPPI_CALL( icvConvexityDefects( contour, convexhull, storage, &defects ));

    __CLEANUP__;
    __END__;

    return defects;
}


CV_IMPL void
cvConvexHull( CvPoint * points,
              int num_points, CvRect * bound_rect, int orientation, int *hull, int *hullsize )
{
    CV_FUNCNAME( "cvConvexHull" );

    __BEGIN__;

    IPPI_CALL( icvConvexHull( points, num_points, bound_rect, orientation, hull, hullsize ));
    __CLEANUP__;
    __END__;

}


CV_IMPL  CvSeq*
cvContourConvexHull( CvSeq *contour, int orientation, CvMemStorage *storage )
{
    CvSeq *hull = 0;

    CV_FUNCNAME( "cvContourConvexHull" );

    __BEGIN__;

    IPPI_CALL( icvContourConvexHull( contour, orientation, storage, &hull ));

    __CLEANUP__;
    __END__;

    return hull;
}


CV_IMPL void
cvConvexHullApprox( CvPoint * points,
                    int num_points,
                    CvRect * bound_rect,
                    int bandwidth, int orientation, int *hullpoints, int *hullsize )
{
    CV_FUNCNAME( "cvConvexHullApprox" );

    __BEGIN__;

    if( !points || !hullpoints || !hullsize )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( bandwidth < 1 )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    IPPI_CALL( icvConvexHull_Approx( points,
                                     num_points,
                                     bound_rect,
                                     bandwidth, orientation, hullpoints, hullsize ));

    __CLEANUP__;
    __END__;

}


CV_IMPL  CvSeq*
cvContourConvexHullApprox( CvSeq * sequence, int bandwidth,
                           int orientation, CvMemStorage * storage )
{
    CvSeq *hull = 0;
    
    CV_FUNCNAME( "cvContourConvexHullApprox" );

    __BEGIN__;

    /* check arguments */
    if( !sequence || !storage )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( bandwidth < 1 )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    if( orientation != CV_CLOCKWISE && orientation != CV_COUNTER_CLOCKWISE )
        CV_ERROR_FROM_STATUS( CV_BADFLAG_ERR );

    IPPI_CALL( icvConvexHull_Approx_Contour( sequence, bandwidth,
                                             orientation, storage, &hull ));
    __CLEANUP__;
    __END__;

    return hull;
}


CV_IMPL int
cvCheckContourConvexity( CvSeq *contour )
{
    int flag = 0;

    CV_FUNCNAME( "cvCheckContourConvexity" );

    __BEGIN__;

    if( !contour )
        CV_ERROR( IPL_BadDataPtr, "invalid input pointer " );

    flag = icvCheckContourConvexity( contour );
    if( flag < 0 ) //CvStatus
        CV_ERROR_FROM_STATUS( (CvStatus)flag );

    __CLEANUP__;
    __END__;

    return flag;
}


CV_IMPL void
cvProject3D( CvPoint3D32f * points3D, int count, CvPoint2D32f * points2D,
             int xIndx, int yIndx )
{
    CV_FUNCNAME( "cvProject3D" );

    __BEGIN__;

    if( points3D == 0 || points2D == 0 )
        CV_ERROR( IPL_BadDataPtr, "Null pointer." );

    if( count < 0 )
        CV_ERROR( IPL_StsBadArg, "Count must be positive." );

    if( xIndx < 0 || xIndx > 2 || yIndx < 0 || yIndx > 2 )
        CV_ERROR( IPL_StsBadArg, "Index value out of range." )
            IPPI_CALL( icvProject3D( points3D, count, points2D, xIndx, yIndx ));

    __CLEANUP__;
    __END__;
}


CV_IMPL void
cvMinAreaRect( CvPoint * points, int n,
               int left, int bottom, int right, int top,
               CvPoint2D32f * anchor, CvPoint2D32f * vect1, CvPoint2D32f * vect2 )
{
    CV_FUNCNAME( "cvMinAreaRect" );

    __BEGIN__;

    IPPI_CALL( icvMinAreaRect( points, n, left, bottom, right, top, anchor, vect1, vect2));

    __CLEANUP__;
    __END__; 
    
}


/* end of file */
