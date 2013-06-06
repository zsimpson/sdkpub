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
#include "Hawk.h"

#include "MainFrm.h"
#include "HawkDoc.h"
#include "ProxyTransuids.h"

extern "C"
{
#include <HighGUI.h>
#include <eic.h>
}


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_GRAPHNOTIFY  WM_USER+13

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIDEO_PP, OnVideoPp)
	ON_UPDATE_COMMAND_UI(ID_VIDEO_PP, OnUpdateVideoPp)
	ON_COMMAND(ID_PIN_PP, OnPinPp)
	ON_UPDATE_COMMAND_UI(ID_PIN_PP, OnUpdatePinPp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,           // x-coordinate of the cursor
	ID_SEPARATOR,           // y-coordinate of the cursor
//	ID_SEPARATOR,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() : m_SourceFilter(0), m_FilterGraph(0), m_GraphBuilder(0),
							m_MediaControl(0), m_MediaEventEx(0), m_VideoWindow(0), m_ProxyTrans(0),
                            m_isIntRun(FALSE), m_isDSRunning(0), m_pRunDoc(0)
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_eicToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_eicToolBar.LoadToolBar(IDR_EICTOOLBAR))
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

    // Setup the status bar
    m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, 20);
    m_wndStatusBar.SetPaneInfo(2, ID_SEPARATOR, SBPS_NORMAL, 20);
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_eicToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_eicToolBar);

	// Initialize DirectShow
	CoInitialize(0);
	if(CreateCamera() && CreateFilterGraph())
	{
        //Camera video source is available
		m_DSOn = TRUE;
	}
	else
	{
		m_DSOn = FALSE;
	}

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

IPin* get_pin( IBaseFilter* pFilter, PIN_DIRECTION dir )
{
    IEnumPins*  pEnumPins = 0;
    IPin*       pPin = 0;

    if( pFilter )
    {
        pFilter->EnumPins( &pEnumPins );
        if( pEnumPins != 0 )
        {
            for(;;)
            {
                ULONG  cFetched = 0;
                PIN_DIRECTION pinDir = PIN_DIRECTION(-1); 
                pPin = 0;

                pEnumPins->Next( 1, &pPin, &cFetched );
                if( cFetched == 1 && pPin != 0 )
                {
                    pPin->QueryDirection( &pinDir );
                    if( pinDir == dir ) break;
                    pPin->Release();
                }
                else if(cFetched == 0)
                {
                    return 0;
                }
            }
            pEnumPins->Release();
        }
    }

    return pPin;
}

BOOL CMainFrame::CreateCamera()
{
    ICreateDevEnum* pCreateDevEnum = 0;
    IEnumMoniker*   pEnumMon = 0;
    IMoniker*       pMon = 0;
    ULONG           cFetched = 0;
    
    SafeRelease( m_SourceFilter );
    
    if(FAILED(CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                      IID_ICreateDevEnum, (void**)&pCreateDevEnum )))
	{
		return FALSE;
	}
    
	ASSERT(pCreateDevEnum);
    /* Create capture device */
	if(FAILED(pCreateDevEnum->CreateClassEnumerator( 
				CLSID_VideoInputDeviceCategory, &pEnumMon, 0)) || !pEnumMon)
	{
		SafeRelease(pCreateDevEnum);
		return FALSE;
	}

	ASSERT(pEnumMon);
    if(SUCCEEDED( pEnumMon->Next(1, &pMon, &cFetched)) && cFetched == 1 && pMon)
    {
        ASSERT(pMon);
        pMon->BindToObject(0, 0, IID_IBaseFilter, (void **)&m_SourceFilter );
        if(!m_SourceFilter)
        {
    		SafeRelease(pCreateDevEnum);
    		SafeRelease(pEnumMon);
    		return FALSE;
        }
		FILTER_INFO info;
		m_SourceFilter->QueryFilterInfo(&info);
    }
	else
	{
		SafeRelease(pCreateDevEnum);
		SafeRelease(pEnumMon);
		return FALSE;
	}

	// Create a proxy transform filter to enable scripts process images
	if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
					IID_IProxyTransform, (void**)&m_ProxyTrans)))
	{
		SafeRelease(pCreateDevEnum);
		SafeRelease(pEnumMon);
		SafeRelease(m_SourceFilter);
		return FALSE;
	}


    SafeRelease( pMon );
    SafeRelease( pEnumMon );
    SafeRelease( pCreateDevEnum );

	return TRUE;
}


BOOL CMainFrame::CreateFilterGraph()
{
    
    if(FAILED(CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                      IID_IGraphBuilder, (void **)&m_GraphBuilder )))
	{
		SafeRelease(m_GraphBuilder);
		return FALSE;
	}

	ASSERT(m_GraphBuilder);
    m_GraphBuilder->QueryInterface(IID_IMediaControl,(void**)&m_MediaControl);
    m_GraphBuilder->QueryInterface(IID_IMediaEventEx,(void**)&m_MediaEventEx);
    m_GraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_VideoWindow);
    m_GraphBuilder->QueryInterface(IID_IFilterGraph, (void**)&m_FilterGraph);

	IBaseFilter* pProxyTrans = 0;
	m_ProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pProxyTrans);

/*    if( m_MediaEventEx )
    {
        // Have the graph signal event via window callbacks for performance
        m_MediaEventEx->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
    }*/

    /* link filters */
    if( m_FilterGraph )
    {
        HRESULT hr;

        hr = m_FilterGraph->AddFilter( m_SourceFilter, L"Video Source" );

        IPin* pSourceOut    = get_pin( m_SourceFilter, PINDIR_OUTPUT );

		IPin* pProxyTransIn		= get_pin( pProxyTrans, PINDIR_INPUT );
		IPin* pProxyTransOut	= get_pin( pProxyTrans, PINDIR_OUTPUT );
    
        if( pSourceOut && pProxyTransIn && pProxyTransOut )
        {
    	    hr = m_FilterGraph->AddFilter( pProxyTrans, L"Script processing");
            hr = m_GraphBuilder->Connect(pSourceOut, pProxyTransIn);
            hr = m_GraphBuilder->Render( pProxyTransOut );
		    AM_MEDIA_TYPE amt;
		    pSourceOut->ConnectionMediaType(&amt);
		    pProxyTransOut->ConnectionMediaType(&amt);
		    VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)amt.pbFormat;
		    if(!vih || vih->bmiHeader.biBitCount != 24)
		    {
                SafeRelease( pSourceOut );
                SafeRelease( pProxyTransIn );
                SafeRelease( pProxyTransOut );
			    return FALSE;
		    }
        }

        SafeRelease( pSourceOut );
        SafeRelease( pProxyTransIn );
        SafeRelease( pProxyTransOut );
    }
    return TRUE;
}


void CMainFrame::StartGraph(CWnd* pWnd) 
{
    if( m_MediaControl )
    {
        m_VideoWindow->put_Owner((OAHWND)pWnd->m_hWnd);
		long flags;
		m_VideoWindow->get_WindowStyle(&flags);
        m_VideoWindow->put_WindowStyle( flags | WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);
//        m_VideoWindow->put_MessageDrain((OAHWND)pWnd->m_hWnd);
//        m_CamShiftProp->SetDrawBox(false);

        SetVideoWindowSize(pWnd->m_hWnd); 
        m_MediaControl->Run();
        m_isDSRunning = TRUE;
    }
}

void CMainFrame::SetVideoWindowSize(HWND hWnd) 
{
    CRect rc = GetVideoWindowSize(hWnd);
    if( m_VideoWindow )
    {
        m_VideoWindow->SetWindowPosition( rc.left, rc.top, rc.right, rc.bottom );
    }
}

CRect CMainFrame::GetVideoWindowSize(HWND hWnd) 
{
    CRect rc;
    if(hWnd)
    {
//        int width, height;
//        GetScaleFactor( width, height );

        ::GetClientRect( hWnd, &rc );

//        rc.right  = rc.right * width / 100;
//        rc.bottom = rc.bottom * height / 100;
    }

    return rc;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


CStatusBar* CMainFrame::GetStatusBar()
{
    return &m_wndStatusBar;
}

BOOL CMainFrame::IsDirectShowOn()
{
	return m_DSOn;
}

void CMainFrame::SetTransformCallback(void (__cdecl *cb)(void *))
{
	m_ProxyTrans->set_transform(cb, 0);
}

void CMainFrame::StopGraph()
{
	if( m_MediaControl )
    {
        m_MediaControl->StopWhenReady();
        m_VideoWindow->put_Visible(OAFALSE);
        m_VideoWindow->put_Owner(NULL);
        m_VideoWindow->put_MessageDrain(0);
        m_isDSRunning = FALSE;
    }
}

void CMainFrame::StartGraph(HWND hWnd)
{
    if( m_MediaControl )
    {
        m_VideoWindow->put_Owner((OAHWND)hWnd);
		long flags;
        m_MediaEventEx->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
        m_MediaEventEx->SetNotifyFlags(0x00);
        m_MediaEventEx->CancelDefaultHandling(EC_COMPLETE);
		m_VideoWindow->get_WindowStyle(&flags);
        m_VideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
        m_VideoWindow->put_MessageDrain((OAHWND)hWnd);

        SetVideoWindowSize(hWnd); 
        m_MediaControl->Run();
        m_isDSRunning = TRUE;
    }
}

void CMainFrame::OnClose() 
{
    // Wait while all interpreters stop
/*    if(IsIntRun())
    {
//        destroy_all();
        m_isInt
        PostMessage(WM_CLOSE);
        return;
    }*/

    CHawkApp* app = (CHawkApp*)AfxGetApp();
    app->CloseEiCHandles();
    if(m_pRunDoc)
    {
        if(WaitForSingleObject(m_pRunDoc->m_hScriptExec, 0) == WAIT_TIMEOUT)
        {
            //TerminateThread(m_pRunDoc->m_hScriptExec, 0);
            int f = TerminateThread(m_pRunDoc->m_hScriptExec, 0);
        }
        if(WaitForSingleObject(m_pRunDoc->m_hThread, 0) == WAIT_TIMEOUT)
        {
            //TerminateThread(m_pRunDoc->m_hThread, 0);
            int f = TerminateThread(m_pRunDoc->m_hThread, 0);
        }
    }    
    destroy_all();
	CMDIFrameWnd::OnClose();
}

BOOL CMainFrame::IsIntRun()
{
    return m_isIntRun;
}

void CMainFrame::SetIntRun(BOOL isRun)
{
    m_isIntRun = isRun;
}

void CMainFrame::OnVideoPp() 
{
    CAUUID uuID;
    ISpecifyPropertyPages* pspp = 0;
    m_SourceFilter->QueryInterface(IID_ISpecifyPropertyPages, (void**)&pspp);
    if(!pspp)
    {
        return;
    }

    pspp->GetPages(&uuID);
    SafeRelease(pspp);

    OleCreatePropertyFrame(NULL, 0, 0, L"Video Source", 1, 
        (IUnknown**)&m_SourceFilter, uuID.cElems, uuID.pElems,
        0, 0, NULL);
}

void CMainFrame::OnUpdateVideoPp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsDirectShowOn());
}

void CMainFrame::SetDocRun(CHawkDoc *pDoc)
{
    m_pRunDoc = pDoc;
}

static int __cdecl DS_ON_SIZE(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, int* ret)
{
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	if(hWnd == frame->GetDSHWND() && msg == WM_SIZE)
	{
		frame->SetVideoWindowSize(hWnd);
	}
	*ret = 0;
	return 0;
}

void CMainFrame::RunDS(void(*cb)(void*), BOOL ret)
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    char *wndName = "DirectShow";
    named_window(wndName, 0);
    m_DSWnd = get_hwnd_byname(wndName);
    SetTransformCallback(cb);
    set_postprocess_func(DS_ON_SIZE);
    StartGraph(m_DSWnd);

    if(!ret)
    {
        MSG message;
        /* Organize message processing... */
        while(IsDSRunning())
        {
            Sleep(10);
            if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            };

            if(!get_hwnd_byname("DirectShow"))
            {
                // The ds window has been destroyed...
    /*            OAFilterState state;
                hres = pimc->GetState(INFINITE, &state);
                hres = pimc->Pause();
                hres = pimc->GetState(INFINITE, &state);
                hres = pimc->Stop();
                hres = pimc->GetState(INFINITE, &state);
                ASSERT(state == State_Stopped);*/
                StopGraph();
                break;
            }
        }
    }
}

void CMainFrame::OnPinPp() 
{
    //Find the output pit that is connected to the next filter...
    CAUUID uuID;
    ISpecifyPropertyPages* pspp = 0;
    IPin* pPin = get_pin(m_SourceFilter, PINDIR_OUTPUT);
    pPin->QueryInterface(IID_ISpecifyPropertyPages, (void**)&pspp);
    if(!pspp)
    {
        return;
    }

    pspp->GetPages(&uuID);
    SafeRelease(pspp);

    /* Disconnect the pin to enable possible changes in the output format... */
    pPin->Disconnect();
    IBaseFilter* pFilter;
    m_ProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pFilter);
    IPin* pProxyPin = get_pin(pFilter, PINDIR_INPUT);
    pProxyPin->Disconnect();
    OleCreatePropertyFrame(NULL, 0, 0, L"Video Source", 1, 
        (IUnknown**)&pPin, uuID.cElems, uuID.pElems,
        0, 0, NULL);
    m_GraphBuilder->Connect(pPin, pProxyPin);
}

void CMainFrame::OnUpdatePinPp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsDirectShowOn());
}

HWND CMainFrame::GetDSHWND()
{
    return m_DSWnd;
}
