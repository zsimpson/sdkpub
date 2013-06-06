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
//M*/// LkDemoView.h : interface of the CLkDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LKDEMOVIEW_H__8B58AF1D_4618_49AF_90B9_E3113535D759__INCLUDED_)
#define AFX_LKDEMOVIEW_H__8B58AF1D_4618_49AF_90B9_E3113535D759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Camera.h"
#include "LkDemoDoc.h"
#include "LkTracker.h"

class CLkDemoView : public CView
{
protected: // create from serialization only
	CLkDemoView();
	DECLARE_DYNCREATE(CLkDemoView)

// Attributes
public:
    CLkDemoDoc* GetDocument() { return (CLkDemoDoc*)m_pDocument; };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLkDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLkDemoView();
    bool IsCaptureEnabled() { m_camera.IsInitialized(); }
    void CheckUpdate();
    CCamera& Camera() { return m_camera; }
    void  StartTracking();
    void  StopTracking();
    void  TrackFeatures();
    bool  IsTracked() { return m_track; }
    bool  IsNightMode() { return m_night_mode; }
    void  SetNightMode( bool night_mode ) { m_night_mode = night_mode; }
    int   FindPoint( CPoint pt );
    CPoint ConvertScreenToImage( CPoint point );
    
protected:
    CCamera m_camera;
    CImage m_canvas;
    CImage m_gray;
    CLkTracker m_tracker;
    bool  m_track;
    bool  m_night_mode;
    int   m_moved_idx;
    CPoint m_moved_point;

// Generated message map functions
protected:
	//{{AFX_MSG(CLkDemoView)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LKDEMOVIEW_H__8B58AF1D_4618_49AF_90B9_E3113535D759__INCLUDED_)
