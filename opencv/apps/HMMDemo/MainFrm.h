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

#if !defined(AFX_MAINFRM_H__08FC8D46_DB62_4573_A129_5B4FE94720E5__INCLUDED_)
#define AFX_MAINFRM_H__08FC8D46_DB62_4573_A129_5B4FE94720E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HMMDemoDoc.h"
#include "HMMDemoView.h"
#include "ImageBaseView.h"
//#include "TestImageBaseView.h"


class CMainFrame : public CFrameWnd
{

protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainFrame)
    public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    protected:
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CMainFrame();

    CImageBaseView* GetImageBaseView();
    CHMMDemoView* GetCameraView();
    CStatusBar* GetStatusBar() { return &m_wndStatusBar; }
    void SetBusy( BOOL busy ) { m_busy = busy; }

protected:
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;
    CReBar      m_wndReBar;
    CSplitterWnd m_wndSplitter;
    //CDialogBar  m_wndDlgBar;

    BOOL m_busy; 

// Generated message map functions
protected:
    //{{AFX_MSG(CMainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnUpdateCapture(CCmdUI* pCmdUI);
    afx_msg void OnCapture();
    afx_msg void OnUpdateCapOptions(CCmdUI* pCmdUI);
    afx_msg void OnCapOptions();
    afx_msg void OnUpdateCapFormat(CCmdUI* pCmdUI);
    afx_msg void OnCapFormat();
    afx_msg void OnAddObj();
    afx_msg void OnUpdateAddObj(CCmdUI* pCmdUI);
    afx_msg void OnRemoveObj();
    afx_msg void OnUpdateRemoveObj(CCmdUI* pCmdUI);
    afx_msg void OnZoomIn();
    afx_msg void OnZoomOut();
	afx_msg void OnChangeBaseParams();
	afx_msg void OnTrain();
	afx_msg void OnUpdateTrain(CCmdUI* pCmdUI); 
    afx_msg void OnRecognize();
	afx_msg void OnUpdateRecog(CCmdUI* pCmdUI);
	afx_msg void OnSelectAll();
	afx_msg void OnDelHmm();
	afx_msg void OnAddTest();
	afx_msg void OnUpdateAddTest(CCmdUI* pCmdUI);
	afx_msg void OnTestFolder();
	afx_msg void OnRecobase();
	afx_msg void OnUpdateRecobase(CCmdUI* pCmdUI);
	afx_msg void OnSettings();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


inline CHMMDemoView* GetCameraView()
{
    CMainFrame* main_frame = (CMainFrame*)AfxGetMainWnd();
    return main_frame ? main_frame->GetCameraView() : 0;
}

inline CImageBaseView* GetImageBaseView()
{
    CMainFrame* main_frame = (CMainFrame*)AfxGetMainWnd();
    return main_frame ? main_frame->GetImageBaseView() : 0;
}

inline CHMMDemoDoc* GetHMMDoc()
{
    CMainFrame* main_frame = (CMainFrame*)AfxGetMainWnd();
    return main_frame ? ((CHMMDemoDoc*)main_frame->GetActiveDocument()) : 0;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__08FC8D46_DB62_4573_A129_5B4FE94720E5__INCLUDED_)
