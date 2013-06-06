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
#include "StereoGR.h"

#include "MainFrm.h"
#include "StereoGRDoc.h"
#include "StereoGRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_DGRECOG, OnDgRecog)
	ON_UPDATE_COMMAND_UI(ID_DGRECOG, OnUpdateDgrecog)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_isTimerStarted = FALSE;
    m_drawCount = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

    ShowControlBar(&m_wndToolBar, SW_SHOW, FALSE);
    ShowControlBar(&m_wndDlgBar, SW_HIDE, FALSE);

    m_menu.LoadMenu(IDR_STEREOTYPE);
    SetMenu(&m_menu);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


CStatusBar* CMainFrame::GetStatusBar()
{
    return &m_wndStatusBar;
}

void CMainFrame::AddView(CStereoGRView *pView)
{
    int id = pView->GetDocument()->GetDocType();
    STEREOGRAPP(app)
    app->SetView(id, pView);
    if(!m_isTimerStarted)
    {
        SetTimer(1, 1, 0);
        m_isTimerStarted = TRUE;
    }

    m_drawCount = 0;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
    Update();
	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::Update()
{
    /* Count the frame rate */
    float fps = CountRate();
    CString str;
    str.Format("%.1f frames per second", fps);
	// This feature is disabled in the current release
//    m_wndStatusBar.SetPaneText(0, LPCTSTR(str));

    STEREOGRAPP(app)
    app->Update();
}

void CMainFrame::RemoveView(CStereoGRView *pView)
{
    int id = pView->GetDocument()->GetDocType();
    STEREOGRAPP(app);
    app->SetView(id, 0);
    int* viewIds = app->GetViewIDs();
    viewIds[id] = 0;

    m_drawCount = 0;
}

void CMainFrame::InitializeMenu()
{
    CMenu* pMenu = GetMenu();
    pMenu = pMenu->GetSubMenu(1);
//    pMenu->InsertMenu(0, MF_BYPOSITION | MF_STRING, 1100, "Test");
}


BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
    int* viewIds = app->GetViewIDs();
    if(pHandlerInfo == 0)
    {
        if(nID >= ID_VIEW1 && nID <= ID_VIEW12)
        {
            int id = nID - ID_VIEW1;
            if(nCode == CN_COMMAND)
            {
                viewIds[id] = !viewIds[id];
                CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
                if(viewIds[id])
                {
                    app->OpenView(id);
                }
                else
                {
                    app->CloseView(id);
                }
                return TRUE;
            }
            else if(nCode == CN_UPDATE_COMMAND_UI)
            {
                CCmdUI* pCmdUI = (CCmdUI*)pExtra;
                if((nID >= ID_VIEW1 && nID <= ID_VIEW6) || nID == ID_VIEW8 || (nID >= ID_VIEW10 && nID <= ID_VIEW12))
                {
                    pCmdUI->Enable();
                    pCmdUI->SetCheck(viewIds[id]);
                }
                else
                {
                    pCmdUI->Enable(FALSE);
                }
                return TRUE;
            }

        }
    }

	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


float CMainFrame::CountRate()
{
    if(!m_drawCount)
    {
        m_time = GetTickCount();
        m_drawCount++;
        return 0;
    }
    
    long time = GetTickCount();
    if(time == m_time)
    {
        return 0;
    }

    float fps = 1000.0f*m_drawCount/(GetTickCount() - m_time);
    m_drawCount++;

    return fps;
}

void CMainFrame::OnDgRecog() 
{
     CStereoGRApp* app = ((CStereoGRApp*)AfxGetApp());

     app->m_doRecog = !app->m_doRecog;

     //CButton* pbut = (CButton*)GetDlgItem( ID_DGRECOG );
     //pbut->SetCheck( app->m_doRecog );  

	// TODO: Add your command handler code here                      	
}

void CMainFrame::OnUpdateDgrecog(CCmdUI* pCmdUI) 
{
    CStereoGRApp* app = ((CStereoGRApp*)AfxGetApp());

    //CButton* pbut = (CButton*)pCmdUI;
    pCmdUI->SetCheck( app->m_doRecog );  
    
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnClose() 
{
	STEREOGRAPP(app)

	for(int i = 0; i < VIEWS_COUNT; i++)
	{
		if(app->GetView(i) == 0)
			continue;

		CString str;
		str.Format("Settings\\StereoGR\\View%d", i);
		int x = 0, y = 0;
		RECT viewRect;
		RECT clientRect;
		GetClRect(&clientRect);
		ClientToScreen(&clientRect);
		app->GetView(i)->GetParent()->GetWindowRect(&viewRect);
		x = viewRect.left - clientRect.left;
		y = viewRect.top - clientRect.top;
		app->WriteProfileInt(LPCTSTR(str), "left", x);
		app->WriteProfileInt(LPCTSTR(str), "top", y);
	}
		
	app->SaveSettings();
	CMDIFrameWnd::OnClose();
}

BOOL CMainFrame::DestroyWindow() 
{
	
	
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::GetClRect( LPRECT lpRect ) const
{
	CWnd::GetWindowRect(lpRect);
	CRect toolbarRect;
	m_wndToolBar.GetWindowRect(&toolbarRect);
	lpRect->top += toolbarRect.Size().cy;
}
