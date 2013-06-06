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

#include "stdafx.h"
#include "LkDemo.h"
#include <math.h>

#include "LkDemoDoc.h"
#include "LkDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLkDemoView

IMPLEMENT_DYNCREATE(CLkDemoView, CView)

BEGIN_MESSAGE_MAP(CLkDemoView, CView)
	//{{AFX_MSG_MAP(CLkDemoView)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
  	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLkDemoView construction/destruction

CLkDemoView::CLkDemoView()
{
    m_canvas.Create( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 24 );
    m_track = false;
    m_night_mode = false;
    m_moved_idx = -1;
}

CLkDemoView::~CLkDemoView()
{
}

BOOL CLkDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLkDemoView drawing

void CLkDemoView::OnDraw(CDC* pDC)
{
    CLkDemoDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    IplImage* img = m_camera.GetFrame().GetImage();
    if( img )
    {
        HDC dstDC = ::GetDC( m_hWnd );

        TrackFeatures();

        CRect sr, dr;
        GetClientRect( &dr );
        IplImage* dst_img = m_canvas.GetImage();
        cvSetImageROI( dst_img, cvRect( dr.left, dr.top, dr.Width(), dr.Height()));
        
        if( !m_night_mode )
        {
            cvResize( img, dst_img, CV_INTER_LINEAR );
        }
        else
        {
            cvZero( dst_img );
        }

        int i, count = m_tracker.GetCount();
        const CPointArray& array = m_tracker.GetPoints();
        double kx = ((double)dr.Width())/(img->width + 0.001);
        double ky = ((double)dr.Height())/(img->height + 0.001);

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
        
        if( m_track )
        {
            m_track = count > 0;
        }

        m_canvas.Show( dstDC, 0, 0, dr.Width(), dr.Height(), 0, 0 );

        ::ReleaseDC( m_hWnd, dstDC );
    }
    else
    {
        CRect r;
        pDC->GetClipBox(&r);
        pDC->FillSolidRect( r.left, r.top, r.Width(), r.Height(), RGB(0,0,0));
    }
}

/////////////////////////////////////////////////////////////////////////////
// CLkDemoView message handlers

void CLkDemoView::OnInitialUpdate() 
{
    CView::OnInitialUpdate();

    if( m_camera.Initialize( 320, 240, -1, m_hWnd ) == 0 )
    {
        MessageBox("Can't initialize camera. Try to change format","Error", MB_OK|MB_ICONERROR );
    }
    Camera().Start();
}

void CLkDemoView::OnDestroy() 
{
    m_camera.Uninitialize();
    CView::OnDestroy();
}

void CLkDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
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


void CLkDemoView::OnRButtonDown(UINT nFlags, CPoint point) 
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


void CLkDemoView::OnLButtonUp(UINT nFlags, CPoint point) 
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


void CLkDemoView::OnMouseMove(UINT nFlags, CPoint point) 
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
}


void CLkDemoView::CheckUpdate()
{
    InvalidateRect( 0, FALSE);
}

BOOL CLkDemoView::OnEraseBkgnd(CDC* pDC) 
{
    return TRUE;
}


void  CLkDemoView::StartTracking()
{
    double quality = 0.01;
    double min_distance = 10;
    int max_features = 300;
    if( m_camera.IsInitialized())
    {
        m_track = true;
        m_tracker.Initialize( m_camera.GetFrame(), max_features, quality, min_distance );
    }
}


void  CLkDemoView::StopTracking()
{
    m_track = false;
}


void  CLkDemoView::TrackFeatures()
{
    if( m_track && m_camera.IsInitialized() && m_camera.IsRunning() )
    {
        CImage& src = m_camera.GetFrame();
        m_gray.Create( src.Width(), src.Height(), 8 );
        m_gray.CopyOf( src, 0 );
        m_tracker.PushFrame( m_gray );
    }
}


int  CLkDemoView::FindPoint( CPoint pt )
{
    int i, count = m_tracker.GetCount();
    double min_dist = 6;
    int min_idx = -1;
    const CPointArray& array = m_tracker.GetPoints();

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


CPoint CLkDemoView::ConvertScreenToImage( CPoint point )
{
    CRect rect;
    GetClientRect( &rect );

    point.x = point.x * m_gray.Width()/MAX(rect.Width(),1);
    point.y = point.y * m_gray.Height()/MAX(rect.Height(),1);

    return point;
}

/*void CLkDemoView::OnLButtonDblClk(UINT nFlags, CPoint point) 
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
