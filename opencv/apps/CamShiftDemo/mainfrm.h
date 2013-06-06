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

#if !defined(AFX_MAINFRM_H__A510D781_2548_11D3_8C73_00A0C998A94B__INCLUDED_)
#define AFX_MAINFRM_H__A510D781_2548_11D3_8C73_00A0C998A94B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "streams.h"
#include "iCamShift.h"
#include "CamShiftUIDs.h"

#define SafeRelease(p) { if( (p) != 0 ) { (p)->Release(); (p)= 0; } }
#define WM_GRAPHNOTIFY  WM_USER+13 


/////////////////////////////////////////////////////////////////////////////
// CBar dialog

class CBar : public CDialogBar
{
// Construction
public:
	CBar();   // standard constructor

    ReadParamsFromControls( CvCamShiftParams& params );
    WriteParamsToControls( CvCamShiftParams& params );

// Dialog Data
	//{{AFX_DATA(CBar)
	enum { IDD = IDD_BAR };
	int		m_Smin;
	int		m_Threshold;
	int		m_Vmax;
	int		m_Vmin;
	int		m_Bins;
    BOOL    m_ShowPicture;
    BOOL    m_ShowBackProject;
    BOOL    m_ShowHistogram;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBar)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPicture();
	afx_msg void OnBackProject();
	afx_msg void OnHistogram();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
    ICamShift*      m_CamShiftProp;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

    CRect           StartTrackerInit();
    void            EndTrackerInit( CRect r );
    void            UpdateThreshold();
    void            ChangeSource();
    void            StopGraph();
    void            StartGraph();
    bool            CreateFilterGraph();
    void            ClearFilterGraph();
    void            DestroyFilterGraph();
    bool            CreateCamShift();
    bool            CreateCamera( int idx=0 );
    void            CreateBouncingBall();
    void            SetVideoWindowSize();
    CRect           GetVideoWindowSize(); 
    void            GetScaleFactor( int& sx, int &sy );

protected:  // control bar embedded members
	CStatusBar      m_wndStatusBar;
	CToolBar        m_wndToolBar;
    CBar            m_wndBar;
    int             m_input;
    CRect           m_src_rect;
    
    // DirectShow interface pointers
    IGraphBuilder*  m_GraphBuilder;
    IMediaControl*  m_MediaControl;
    IVideoWindow*   m_VideoWindow;
    IFilterGraph*   m_FilterGraph;
    IMediaEventEx*  m_MediaEventEx;
    IBaseFilter*    m_SourceFilter;
    IBaseFilter*    m_CamShift;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnCamera();
	afx_msg void OnBall();
    afx_msg void OnFile();
    afx_msg void OnPlayPause();
    afx_msg void OnUpdateCamera(CCmdUI* pCmdUI);
    afx_msg void OnUpdateBall(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlayPause(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A510D781_2548_11D3_8C73_00A0C998A94B__INCLUDED_)
