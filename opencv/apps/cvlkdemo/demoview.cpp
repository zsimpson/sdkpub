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

// LkDemoView.cpp : implementation of the CLkDemoView class

#include <math.h>
#include "demoview.h"


/////////////////////////////////////////////////////////////////////////////
// CLkDemoView construction/destruction

CLkDemoView::CLkDemoView()
{
    //m_canvas.Create( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 24 );
    m_track = false;
    m_trackinit = false;
    m_night_mode = false;
    m_moved_idx = -1;
    m_started = false;
}

CLkDemoView::~CLkDemoView()
{
}

void CLkDemoView::SetSize (int w,int h)
{
    m_w = w;
    m_h = h;
}

CvPoint CLkDemoView::ConvertScreenToImage( CvPoint point )
{
    IplImage* img = m_gray.GetImage();
    if( img )
    {
        CvSize size = cvGetSize(img);
    
        point.x *= size.width/m_w;
        point.y *= size.height/m_h;
    }
    else
        point.x = point.y = 0;
    
    return point;
}

/////////////////////////////////////////////////////////////////////////////
// CLkDemoView drawing

/*void CLkDemoView::OnDraw(CDC* pDC)
{
    CLkDemoDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    IplImage* img = m_camera.GetFrame().GetImage();
    if( img )
    {
        HDC dstDC = ::GetDC( m_hWnd );
        HDC srcDC = m_canvas.GetDC();

        TrackFeatures();

        CRect sr, dr;
        GetClientRect( &dr );
        IplImage* dst_img = m_canvas.GetImage();
        IplROI roi = RectToROI( dr );
        dst_img->roi = &roi;
        
        if( !m_night_mode )
        {
            //iplResize( img, dst_img, roi.width, img->width, roi.height, img->height, 
            //           IPL_INTER_LINEAR );
            double a[2][3] =
            {
                {(double)roi.width/img->width, 0, 0},
                {0, (double)roi.height/img->height, 0}
            };
                            
            iplWarpAffine( img, dst_img, a, IPL_INTER_LINEAR );
        }
        else
        {
            iplSet( dst_img, 0 );
        }

        int i, count = m_tracker.GetCount();
        const CPointArray& array = m_tracker.GetPoints();
        double kx = ((double)roi.width)/(img->width + 0.001);
        double ky = ((double)roi.height)/(img->height + 0.001);

        for( i = 0; i < count; i++ )
        {
            CvPoint pt;
            int color;
            if( i != m_moved_idx )
            {
                pt = cvPoint( cvRound(array[i].x*kx), cvRound(array[i].y*ky));
                color = RGB(0,255,0);
            }
            else
            {
                pt = cvPoint( cvRound(m_moved_point.x*kx),
                              cvRound(m_moved_point.y*ky));
                color = RGB(255,0,0);
            }
            cvCircle( dst_img, pt, 3, color, CV_FILLED );
        }
        
        dst_img->roi = 0;

        if( m_track )
        {
            m_track = count > 0;
        }

        BitBlt( dstDC, 0, 0, dr.Width(), dr.Height(), m_canvas.GetDC(), 0, 0, SRCCOPY );

        ::ReleaseDC( m_hWnd, dstDC );
    }
    else
    {
        CRect r;
        pDC->GetClipBox(&r);
        pDC->FillSolidRect( r.left, r.top, r.Width(), r.Height(), RGB(0,0,0));
    }
}*/

/////////////////////////////////////////////////////////////////////////////
// CLkDemoView message handlers

/*void CLkDemoView::OnLButtonDown(UINT nFlags, CvPoint point) 
{
    CView::OnLButtonDown(nFlags, point);
    {
        point = ConvertScreenToImage(point);
        int index = FindPoint(point);
        if( index > 0 )
        {
            m_moved_idx = index;
            m_moved_point = point;
            CheckUpdate();
        }
        else if( m_gray.GetImage() )
        {
            m_tracker.AddPoint( point, m_gray );
        }
    }
}


void CLkDemoView::OnRButtonDown(UINT nFlags, CvPoint point) 
{
    CView::OnRButtonDown(nFlags, point);
    {
        point = ConvertScreenToImage(point);
        int index = FindPoint(point);
        if( index > 0 )
        {
            m_tracker.RemovePoint( index );
            CheckUpdate();
        }
    }
}


void CLkDemoView::OnLButtonUp(UINT nFlags, CvPoint point) 
{
    CView::OnLButtonUp(nFlags, point);
    {
        if( m_moved_idx > 0 && m_gray.GetImage() )
        {
            m_tracker.MovePoint( m_moved_idx, m_moved_point, m_gray );
            m_moved_idx = -1;
            CheckUpdate();
        }
    }
}


void CLkDemoView::OnMouseMove(UINT nFlags, CvPoint point) 
{
    CView::OnMouseMove(nFlags, point);
    if( nFlags & MK_LBUTTON )
    {
        if( m_moved_idx > 0 && m_gray.GetImage() )
        {
            m_moved_point = ConvertScreenToImage(point);
            CheckUpdate();
        }
    }
}*/

void  CLkDemoView::StartTracking(CImage& frame)
{
    double quality = 0.01;
    double min_distance = 10;
    int max_features = 300;
    
    m_track = true;
    m_tracker.Initialize( frame, max_features, quality, min_distance );
    
}

void  CLkDemoView::StopTracking()
{
    m_track = false;
    
}

void  CLkDemoView::TrackFeatures(CImage& frame)
{
    if( m_track )
    {
        m_gray.Create( frame.Width(), frame.Height(), 8 ,frame.GetImage()->origin);
        m_gray.CopyOf( frame, 0 );
        m_tracker.PushFrame( m_gray );
    }
}


int  CLkDemoView::FindPoint( CvPoint pt )
{
    int i, count = m_tracker.GetCount();
    double min_dist = 6;
    int min_idx = -1;
    const PointArray& array = m_tracker.GetPoints();

    for( i = 0; i < count; i++ )
    {
        CvPoint2D32f p1 = array[i];
        double d = fabs(pt.x - p1.x) + fabs(pt.y - p1.y); 
        if( d < min_dist )
        {
            min_dist = d;
            min_idx = i;
        }
    }

    return min_idx;
}


/*CvPoint CLkDemoView::ConvertScreenToImage( CvPoint point )
{
    CRect rect;
    GetClientRect( &rect );
    IplImage* img = m_gray.GetImage();

    point.x = point.x * iplWidth(img)/MAX(rect.Width(),1);
    point.y = point.y * iplHeight(img)/MAX(rect.Height(),1);

    return point;
}*/

/*void CLkDemoView::OnLButtonDblClk(UINT nFlags, CvPoint point) 
{
    CView::OnLButtonDblClk(nFlags, point);

    point = ConvertScreenToImage(point);
    int index = FindPoint( point );
    if( index >= 0 )
    {
        m_tracker.RemovePoint( index );
    }
    else if( m_gray.GetImage() )
    {
        m_tracker.AddPoint( point, m_gray );
    }
    CheckUpdate();
}*/
