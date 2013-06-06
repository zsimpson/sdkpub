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
//M*/#if !defined(AFX_IMAGEBASEVIEW_H__9391157C_5B0A_4F8F_832F_51B7306FCC2A__INCLUDED_)
#define AFX_IMAGEBASEVIEW_H__9391157C_5B0A_4F8F_832F_51B7306FCC2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageBaseView.h : header file
//

#include "HMMDemoDoc.h"

#define VIEW_PERSON 1
#define VIEW_BASE   2

/////////////////////////////////////////////////////////////////////////////
// CImageBaseView view

class CImageBaseView : public CScrollView
{
protected:
	CImageBaseView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CImageBaseView)

// Attributes
public:

// Operations
public:
	int GetMode();
    CHMMDemoDoc* GetDocument() { return (CHMMDemoDoc*)m_pDocument; };
    enum { ZOOM_MIN = -2, ZOOM_MAX = 4 };

    void  Zoom( bool zoom_in = true );
    void  SwitchMode( int index, bool to_personal );
    int   GetPersonIndex() { return m_index; };
    int   GetActive() { return m_active; };
    void  ResetActive() { m_active = -1; };
    void  RefreshView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageBaseView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CImageBaseView();
    void    RecalcPictureSize();
    CRect   GetRectByIndex( int index );
    int     GetIndexByPoint( CPoint pt );

    CImage  m_canvas;
    CImage  m_rgbcanvas;

    SIZE    m_base_size;
    SIZE    m_pic_size;
    SIZE    m_pic_delta;
    SIZE    m_margin;

    int     m_log_shift;
    int     m_index;
    int     m_active;

    int     m_view_mode;//VIEW_PERSON or VIEW_BASE

    HPEN    m_pen;

    int     m_count, m_nx, m_ny;

	// Generated message map functions
	//{{AFX_MSG(CImageBaseView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBASEVIEW_H__9391157C_5B0A_4F8F_832F_51B7306FCC2A__INCLUDED_)
