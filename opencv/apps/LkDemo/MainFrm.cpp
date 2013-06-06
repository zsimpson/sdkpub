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
//M*/// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LkDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_CAPTURE, OnUpdateCapture)
    ON_COMMAND(ID_CAPTURE, OnCapture)
	ON_COMMAND(ID_TRACK, OnTrack)
	ON_UPDATE_COMMAND_UI(ID_TRACK, OnUpdateTrack)
	ON_COMMAND(ID_NIGHTMODE, OnNightmode)
	ON_UPDATE_COMMAND_UI(ID_NIGHTMODE, OnUpdateNightmode)
	ON_COMMAND(ID_CAPOPTIONS, OnCapOptions)
    ON_COMMAND(ID_CAPFORMAT, OnVideoFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

CLkDemoView* CMainFrame::GetCameraView()
{
    return (CLkDemoView*)GetActiveView();
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateCapture(CCmdUI* pCmdUI) 
{
    CLkDemoView* view = GetCameraView();
    bool enable = false;
    bool press = false;

    if( view )
    {
        enable = view->Camera().IsInitialized();
        press = view->Camera().IsRunning();
    }

    pCmdUI->Enable( enable );
    pCmdUI->SetCheck( press );
}

void CMainFrame::OnCapture() 
{
    CLkDemoView* view = GetCameraView();

    if( view && view->Camera().IsInitialized())
    {
        if( view->Camera().IsRunning())
        {
            view->Camera().Stop();
        }
        else
        {
            view->Camera().Start();
        }
    }    
}

void CMainFrame::OnTrack() 
{
    CLkDemoView* view = GetCameraView();

    if( view && view->Camera().IsInitialized())
    {
        if( view->IsTracked())
        {
            view->StopTracking();
        }
        else
        {
            view->StartTracking();
        }
    }
}

void CMainFrame::OnUpdateTrack(CCmdUI* pCmdUI) 
{
    bool enable = false;
    bool press = false;
    CLkDemoView* view = GetCameraView();

    if( view && view->Camera().IsInitialized())
    {
        enable = true;
        press = view->IsTracked();
    }

    pCmdUI->Enable( enable );
    pCmdUI->SetCheck( press );
}

void CMainFrame::OnNightmode() 
{
    CLkDemoView* view = GetCameraView();

    if( view )
    {
        view->SetNightMode( !view->IsNightMode() );
    }
}

void CMainFrame::OnUpdateNightmode(CCmdUI* pCmdUI) 
{
    bool enable = false;
    bool press = false;
    CLkDemoView* view = GetCameraView();

    if( view )
    {
        enable = view->IsTracked();
        press = enable && view->IsNightMode();
    }

    pCmdUI->Enable( enable );
    pCmdUI->SetCheck( press );
}


void CMainFrame::OnCapOptions() 
{
    CLkDemoView* view = GetCameraView();

    if( view )
    {
        view->Camera().VideoSourceDlg();
        view->InvalidateRect(0);
    }
}


void CMainFrame::OnVideoFormat() 
{
    CLkDemoView* view = GetCameraView();

    if( view )
    {
        view->Camera().VideoFormatDlg();
        view->InvalidateRect(0);
    }
}
