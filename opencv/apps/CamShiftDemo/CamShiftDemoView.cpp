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
// CamShiftDemoView.cpp : implementation of the CCamShiftDemoView class
//

#include "math.h"
#include "stdafx.h"
#include "CamShiftDemo.h"

#include "CamShiftDemoDoc.h"
#include "CamShiftDemoView.h"

#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamShiftDemoView

IMPLEMENT_DYNCREATE(CCamShiftDemoView, CView)

BEGIN_MESSAGE_MAP(CCamShiftDemoView, CView)
	//{{AFX_MSG_MAP(CCamShiftDemoView)
	ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamShiftDemoView construction/destruction

CCamShiftDemoView::CCamShiftDemoView()
{
	// TODO: add construction code here

}

CCamShiftDemoView::~CCamShiftDemoView()
{
}

BOOL CCamShiftDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCamShiftDemoView drawing

void CCamShiftDemoView::OnDraw(CDC* pDC)
{
	CCamShiftDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCamShiftDemoView diagnostics

#ifdef _DEBUG
void CCamShiftDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCamShiftDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCamShiftDemoDoc* CCamShiftDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCamShiftDemoDoc)));
	return (CCamShiftDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCamShiftDemoView message handlers

BOOL CCamShiftDemoView::OnEraseBkgnd(CDC* pDC) 
{
    CRect r;
    pDC->GetClipBox( &r );
    pDC->FillSolidRect( &r, RGB(0,0,100));
    return TRUE;
}


void CCamShiftDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    int w = 320;
    int h = 240;
    
    CMainFrame*  frame = (CMainFrame*)AfxGetMainWnd();
    CRect  rect = CRect( 0, 0, 0, 0 );
    CRectTracker  tracker;

    CRect srcRect = frame->StartTrackerInit();
    w = srcRect.Width();
    h = srcRect.Height();

    /* recalc rect position according to "bottom-origin" and scale it */ 
    if( tracker.TrackRubberBand( this, point ))
    {
        CRect all;
        int sx, sy;

        frame->GetScaleFactor( sx, sy );
        GetClientRect( &all );
        tracker.GetTrueRect( &rect );
        
        rect.SetRect( rect.left*w*100/(sx*all.Width()), 
                      (all.bottom - rect.bottom*100/sy)*h/all.Height(),
                      rect.right*w*100/(sx*all.Width()),
                      (all.bottom - rect.top*100/sy)*h/all.Height());
    }
    frame->EndTrackerInit( rect );
}

/* End of file. */
