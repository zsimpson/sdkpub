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
//M*/// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6FFD53AB_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
#define AFX_MAINFRM_H__6FFD53AB_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SafeRelease(p) { if( (p) != 0 ) { (p)->Release(); (p)= 0; } }
#define WM_GRAPHNOTIFY  WM_USER+13 

#include <streams.h>
#include <iProxyTrans.h>

class CHawkDoc;
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
    CHawkDoc* m_pRunDoc;

private:
    BOOL m_isDSRunning;
	BOOL m_DSOn;
	HWND m_DSWnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	HWND GetDSHWND();
    void RunDS(void (*cb)(void*), BOOL ret = TRUE);
    BOOL IsDSRunning() {return m_isDSRunning;}
	void SetDocRun(CHawkDoc* pDoc = NULL);
	void SetIntRun(BOOL isRun);
	BOOL IsIntRun();
	void StartGraph(HWND hWnd);
	void StopGraph();
	void SetTransformCallback(void (*cb)(void*));
	BOOL IsDirectShowOn();
	BOOL CreateCamera();	
	BOOL CreateFilterGraph();
	void StartGraph(CWnd* pWnd);
	void SetVideoWindowSize(HWND hWnd);
	CRect GetVideoWindowSize(HWND hWnd);
	CStatusBar* GetStatusBar();
    virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
    CToolBar    m_eicToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnVideoPp();
	afx_msg void OnUpdateVideoPp(CCmdUI* pCmdUI);
	afx_msg void OnPinPp();
	afx_msg void OnUpdatePinPp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_isIntRun;
	IProxyTransform* m_ProxyTrans;
	IBaseFilter* m_SourceFilter;
    IGraphBuilder*  m_GraphBuilder;
    IMediaControl*  m_MediaControl;
    IVideoWindow*   m_VideoWindow;
    IFilterGraph*   m_FilterGraph;
    IMediaEventEx*  m_MediaEventEx;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6FFD53AB_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
