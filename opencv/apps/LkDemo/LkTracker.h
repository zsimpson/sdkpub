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
//M*/#pragma once

#include "CV.h"
#include "highgui.h"

typedef CArray<CvPoint2D32f,CvPoint2D32f> CPointArray;
typedef CArray<char,char> CStatusArray;

class CLkTracker
{
public:    
    
    CLkTracker();
    ~CLkTracker();

    void Initialize( CImage& image, int max_features,
                     double quality, double min_distance );

    void PushFrame( CImage& img );
    
    const CPointArray& GetPoints() const { return m_features[m_idx]; }
    const CStatusArray& GetStatus() const { return m_status; }

    int   GetCount() { return m_count; }
    void  MovePoint( int index, CPoint point, CImage& image );
    void  RemovePoint( int index );
    void  AddPoint( CPoint point, CImage& image );

protected:

    CImage  m_frame[2];
    CImage  m_pyr[2];
    CImage  m_temp[2];
    int     m_count;
    int     m_idx;
    int     m_tracked;
    int     m_moved_idx;

    CvPoint2D32f AdjustPoint( CPoint pt, CImage& image );

    CPointArray m_features[2];
    CPointArray m_matrices;
    CStatusArray m_status;
};


