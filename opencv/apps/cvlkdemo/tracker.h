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

#ifndef _TRACKER_H_
#define _TRACKER_H_

#include "cv.h"
#include "highgui.h"

#include <vector>
using namespace std;

typedef vector<CvPoint2D32f> PointArray;
typedef vector<char> StatusArray;

class CLkTracker
{
public:    
    
    CLkTracker();
    ~CLkTracker();

    void Initialize( CImage& image, int max_features,
                     double quality, double min_distance );

    void PushFrame( CImage& img );
    
    const PointArray& GetPoints() const 
    {
        return m_features[m_idx]; 
    }
    const StatusArray& GetStatus() const { return m_status; }

    int   GetCount() { return m_count; }
    void  MovePoint( int index, CvPoint point, CImage& image );
    void  RemovePoint( int index );
    void  AddPoint( CvPoint point, CImage& image );

public:

    CImage  m_frame[2];
    CImage  m_pyr[2];
    CImage  m_temp[2];
    int     m_count;
    int     m_init;
    int     m_idx;
    int     m_tracked;
    int     m_moved_idx;

    CvPoint2D32f AdjustPoint( CvPoint pt, CImage& image );

    PointArray m_features[2];
    PointArray m_matrices;
    StatusArray m_status;
};

#endif /* _TRACKER_H_ */
