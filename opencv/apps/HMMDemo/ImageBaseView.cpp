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
//M*/// ImageBaseView.cpp : implementation file
//

#include "stdafx.h"
#include "HMMDemo.h"
#include "ImageBaseView.h"
#include "HMMDemoDoc.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageBaseView

IMPLEMENT_DYNCREATE(CImageBaseView, CScrollView)

CImageBaseView::CImageBaseView()
{
    m_canvas.Create( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 8 );
    m_rgbcanvas.Create( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 24 );
    
    IplImage* rgb = m_rgbcanvas.GetImage();
    strcpy( rgb->colorModel, "RGB" );
    strcpy( rgb->channelSeq, "BGR" );

    IplImage* gray = m_canvas.GetImage();
    strncpy( gray->colorModel, "GRAY", 4 );
    strncpy( gray->channelSeq, "GRAY", 4 );


    m_base_size = CSize( 100, 120 );
    m_log_shift = 0;
    RecalcPictureSize();
    m_index = -1;
    m_active = -1;
    m_pen = CreatePen( PS_SOLID, 3, RGB(255,0,255));

    m_view_mode = 0;

    m_count = 0;
    m_nx = m_ny = 0;
}

CImageBaseView::~CImageBaseView()
{
    DeleteObject( m_pen );
}


BEGIN_MESSAGE_MAP(CImageBaseView, CScrollView)
    //{{AFX_MSG_MAP(CImageBaseView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageBaseView drawing

void  CImageBaseView::RefreshView()
{
    CHMMDemoDoc* doc = GetDocument();
    CSize virt_size = CSize( 10, 10 );

    if( doc )
    {
        CRect win_rect;
        if( m_index < 0 )
        {
            m_count = doc->GetFaceBase().GetPersonList().GetCount();
        }
        else
        {
            CPerson* person = doc->GetFaceBase().GetPerson( m_index );
            if( !person )
            {
                ASSERT(0);
                return;
            }
            m_count = person->GetImgList().GetCount();
        }

        GetClientRect( &win_rect );

        m_margin = CSize((m_pic_delta.cx - m_pic_size.cx)/2,
                         (m_pic_delta.cy - m_pic_size.cy)/2);

        m_nx = (win_rect.Width() - m_margin.cx +
                m_pic_delta.cx - m_pic_size.cx)/m_pic_delta.cx;

        m_nx = MAX( m_nx, 1 );

        if( m_nx != 0 )
        {
            m_ny = (m_count + m_nx - 1)/m_nx;
            virt_size.cx = win_rect.Width();
            virt_size.cy = MAX( m_ny, 1 )*m_pic_delta.cy;
        }
    }
    SetScrollSizes( MM_TEXT, virt_size );
    InvalidateRect(0);
}

void CImageBaseView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();
    m_count = m_nx = m_ny = 0;
    m_active = -1;
    m_index = -1;
    RefreshView();
}



void CImageBaseView::OnDraw(CDC* pDC)
{
    CHMMDemoDoc* doc = GetDocument();
    if( doc )
    {
        CFaceBase& base = doc->GetFaceBase();
        CRect win_rect;
        CSize win_size;
        int y_pos = GetScrollPosition().y;
        HDC dc;

        dc = ::GetDC( m_hWnd );

        GetClientRect( &win_rect );
        win_size = CSize( win_rect.Width(), win_rect.Height() );

        m_canvas.Fill( GetSysColor( COLOR_WINDOW ));
        base.Draw( m_index, m_canvas, win_size, y_pos, m_pic_size, m_pic_delta );
        
        if( m_canvas.GetImage() && m_rgbcanvas.GetImage() )
        {
            IplImage* src = m_canvas.GetImage();
            IplImage* dst = m_rgbcanvas.GetImage();
            CvRect sr = cvGetImageROI( src ), dr = cvGetImageROI( dst );

            cvSetImageROI( src, RectToCvRect( win_rect ));
            cvSetImageROI( dst, RectToCvRect( win_rect ));

            cvCvtColor( src, dst, CV_GRAY2BGR );
            cvSetImageROI( src, sr );
            cvSetImageROI( dst, dr );

            m_rgbcanvas.Show( dc, 0, 0, win_size.cx, win_size.cy, 0, 0 );
        }

        if( m_active >= 0 )
        {
            HGDIOBJ pen = SelectObject( dc, m_pen );
            CRect rect = GetRectByIndex( m_active );
            CPoint pt[5];

            pt[0] = CPoint( rect.left, rect.top - y_pos );
            pt[1] = CPoint( rect.right, rect.top - y_pos );
            pt[2] = CPoint( rect.right, rect.bottom - y_pos );
            pt[3] = CPoint( rect.left, rect.bottom - y_pos );
            pt[4] = pt[0];

            Polyline( dc, pt, 5 );
            SelectObject( dc, pen );
        }

        int trained_index = base.GetTrainedIndex(); 

        if( m_index >= 0 && trained_index >= 0 )
        {
            CRect rect = GetRectByIndex( trained_index );
            if( !rect.IsRectEmpty())
            {
                CPerson* person = base.GetPerson( m_index );
                ASSERT( person != 0 );

                CPersonImgList& list = person->GetImgList();
                CPersonImage* image = list.GetAt( list.FindIndex(trained_index));

                ASSERT( image != 0 );
                CRect sr, dr;
                image->CalcRect( win_size, rect.TopLeft(), m_pic_size, sr, dr );

                if( !sr.IsRectEmpty() && !dr.IsRectEmpty())
                {
                    SetStretchBltMode( dc, COLORONCOLOR );
                    base.GetTrainedImage().DrawToHDC( dc, &dr ); 
                }
            }
        }

        ::ReleaseDC( m_hWnd, dc );
    }
}

/////////////////////////////////////////////////////////////////////////////
// CImageBaseView message handlers

void  CImageBaseView::RecalcPictureSize()
{
    double scale = pow( sqrt(2), m_log_shift );
    m_pic_size.cx = (int)(m_base_size.cx*scale + 0.5);
    m_pic_size.cy = (int)(m_base_size.cy*scale + 0.5);
    m_pic_delta.cx = m_pic_size.cx*5/4;
    m_pic_delta.cy = m_pic_size.cy*5/4;
}

void  CImageBaseView::Zoom( bool zoom_in )
{
    if( zoom_in )
    {
        m_log_shift = MIN( ZOOM_MAX, m_log_shift + 1 );
    }
    else
    {
        m_log_shift = MAX( ZOOM_MIN, m_log_shift - 1 );
    }
    RecalcPictureSize();
    RefreshView();
    InvalidateRect(0);
}


void CImageBaseView::OnSize(UINT nType, int cx, int cy) 
{
    CScrollView::OnSize(nType, cx, cy);
    RefreshView();
}


BOOL CImageBaseView::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}


CRect CImageBaseView::GetRectByIndex( int index )
{
    CRect rect = CRect(0,0,0,0);
    if( (unsigned)index >= (unsigned)m_count ) return rect;

    rect.left = index % m_nx;
    rect.top = index / m_nx;

    rect.left = rect.left*m_pic_delta.cx + m_margin.cx;
    rect.top = rect.top*m_pic_delta.cy + m_margin.cy;

    rect.right = rect.left + m_pic_size.cx;
    rect.bottom = rect.top + m_pic_size.cy;

    return rect;
}


int  CImageBaseView::GetIndexByPoint( CPoint pt )
{
    int y_pos = GetScrollPosition().y;

    int x = (pt.x - m_margin.cx)/m_pic_delta.cx;
    int y = (pt.y + y_pos - m_margin.cy)/m_pic_delta.cy;
    int index;

    if( x >= m_nx || y >= m_ny ) return -1;

    if( pt.x > (x+1)*m_pic_delta.cx - m_margin.cx ||
        y_pos + pt.y > (y+1)*m_pic_delta.cy - m_margin.cy ) return -1;

    index = y*m_nx + x;
    if( index >= m_count ) return -1;

    return index;
}


void CImageBaseView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);

    int index = GetIndexByPoint( point );
    if( index >= 0 )
    {
        m_active = index;
    }
    InvalidateRect(0);
}


void CImageBaseView::SwitchMode( int index, bool to_personal )
{
    CHMMDemoDoc* doc = GetDocument();

    if( doc )
    {
        CPerson* person = doc->GetFaceBase().GetPerson( index );
        if( !person )
        {
            ASSERT(0);
            return;
        }
        if( to_personal )
        {
            person->LoadRest();
            m_index = index;
            m_active = -1;
            m_view_mode = VIEW_PERSON;
        }
        else
        {
            if( person->IsModified())
            {
                person->Save();
            }
            person->UnloadRest();
            m_index = -1;
            m_active = index;
            m_view_mode = VIEW_BASE;
        }
        RefreshView();
    }
}


void CImageBaseView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    CScrollView::OnLButtonDblClk(nFlags, point);

    int index = GetIndexByPoint( point );
    if( index >= 0 && m_index == -1 )
    {
        SwitchMode( index, true );
    }
    else if( index < 0 && m_index >= 0 )
    {
        SwitchMode( m_index, false );
    }
}

int CImageBaseView::GetMode()
{
    return m_view_mode;
}
