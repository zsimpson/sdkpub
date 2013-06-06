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
//M*/// HawkView.h : interface of the CHawkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HAWKVIEW_H__6FFD53B1_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
#define AFX_HAWKVIEW_H__6FFD53B1_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lexer.h"

typedef struct _ColorScheme
{
    HBRUSH  bkBrush;    // brush used for background
    int     background; // background color
    int     selbk;      // selection background
    int     selfk;      // selection foreground
    int     clr[10];    //  TOKEN_NORMAL  = 0,
                        //  TOKEN_COMMENT = 1,
                        //  TOKEN_STRING  = 2,
                        //  TOKEN_KEYWORD = 3,
                        //  TOKEN_NUMBER  = 4,
} ColorScheme;

class CHawkView : public CEditView
{
protected: // create from serialization only
	CHawkView();
	DECLARE_DYNCREATE(CHawkView)

// Attributes
public:
	CHawkDoc* GetDocument();
    static HFONT     hFont;
    static HDC       hMemDC;
    static HGDIOBJ   hOldBmp;
    int       cTokens;
    int       maxTokens;
    Token*    Tokens;
    char*     TextBuffer;
    const int MaxTextBuffer;
    HACCEL    hAccelTable;
    const int TAB_SIZE;
    const int LINE_BUF_SIZE;
    char*      Line;
    char*      Space;
    int       Disable_Update;
    static ColorScheme Scheme;

// Operations
public:
    BOOL   Customize();
    int    ScanTextBuffer( char* text, Token* tokens, int max_tokens );
    void   RenderHighlightedText( BOOL update = FALSE );
    POINT  GetCoord( HWND hEdit, int pos );
    POINT  GetCursorPos();
    void   GoToLine( int line );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHawkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTip();
	void UpdateCursorPos();
	CString GetText();
	CEdit& m_edit;
	virtual ~CHawkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHawkView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnChange();
    afx_msg HBRUSH CtlColor( CDC* pDC, UINT nCtlColor );
	afx_msg void OnUntab();
	afx_msg void OnGoHome();
	afx_msg void OnGotoLine();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static int m_instanceCount;
};

#ifndef _DEBUG  // debug version in HawkView.cpp
inline CHawkDoc* CHawkView::GetDocument()
   { return (CHawkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HAWKVIEW_H__6FFD53B1_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
