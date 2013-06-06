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

// LkDemoView.cpp : implementation of the CCsDemoView class

#include <math.h>
#include "csdemoview.h"


/////////////////////////////////////////////////////////////////////////////
// CCsDemoView

CCsDemoView::CCsDemoView()
{
    m_track = false;
    m_start = false;

    m_params.x = 0.4f; 
    m_params.y = 0.3f;
    m_params.width = 0.2f;
    m_params.height = 0.3f;
    
    m_params.Smin = 20;
    m_params.Vmin = 40;
    m_params.Vmax = 255;
    m_params.bins = 20;
    m_params.view = 0;
    m_params.threshold = 0;

    m_ImgSize.width=0; 
    m_ImgSize.height=0;
    m_VwSize.width=0; 
    m_VwSize.height=0;
}

CCsDemoView::~CCsDemoView()
{
}

CvSize CCsDemoView::SetVwSize (int w,int h)
{
    m_VwSize.width = w;
    m_VwSize.height = h;
    return m_VwSize;
}

CvSize CCsDemoView::GetVwSize ()
{
    return m_VwSize;
}

CvSize CCsDemoView::SetImgSize (int w,int h)
{
    m_ImgSize.width = w;
    m_ImgSize.height = h;
    return m_ImgSize;
}

CvSize CCsDemoView::GetImgSize ()
{
    return m_ImgSize;
}

CvPoint CCsDemoView::ConvertViewToImage( CvPoint point )
{
    point.x = point.x * m_ImgSize.width/m_VwSize.width;
    point.y = point.y * m_ImgSize.height/m_VwSize.height;
    
    return point;
}

CvPoint CCsDemoView::ConvertImageToView( CvPoint point )
{
    point.x = point.x * m_VwSize.width/m_ImgSize.width;
    point.y = point.y * m_VwSize.height/m_ImgSize.height;
    
    return point;
}
/////////////////////////////////////////////////////////////////////////////