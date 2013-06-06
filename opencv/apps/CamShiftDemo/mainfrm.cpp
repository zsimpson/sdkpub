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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "streams.h"

#include "CamShiftDemo.h"
#include "objbase.h"
#include "initguid.h"
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
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_COMMAND(ID_CAMERA, OnCamera )
    ON_COMMAND(ID_BALL, OnBall )
    ON_COMMAND(ID_FILE, OnFile)
    ON_COMMAND(ID_PLAYPAUSE, OnPlayPause)
    ON_UPDATE_COMMAND_UI(ID_CAMERA, OnUpdateCamera )
    ON_UPDATE_COMMAND_UI(ID_BALL, OnUpdateBall )
    ON_UPDATE_COMMAND_UI(ID_FILE, OnUpdateFile )
	ON_UPDATE_COMMAND_UI(ID_PLAYPAUSE, OnUpdatePlayPause)
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
    m_GraphBuilder  = 0;
    m_FilterGraph   = 0;
    m_MediaControl  = 0;
    m_MediaEventEx  = 0;
    m_VideoWindow   = 0;
    m_SourceFilter = 0;
    
    m_CamShift      = 0;
    m_CamShiftProp  = 0;

    m_input = -1;

    m_src_rect = CRect(0,0,0,0);
}

CMainFrame::~CMainFrame()
{
}


static IPin* get_pin( IBaseFilter* pFilter, PIN_DIRECTION dir )
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
                if( cFetched == 0 || pPin == 0 ) break;

                pPin->QueryDirection( &pinDir );
                if( pinDir == dir ) break;
                pPin->Release();
            }
            pEnumPins->Release();
        }
    }

    return pPin;
}

static void show_prop_page( IBaseFilter* pFilter, const WCHAR* name )
{
    if( pFilter )
    {
        ISpecifyPropertyPages* pispp = 0;
        pFilter->QueryInterface( IID_ISpecifyPropertyPages, (void **)&pispp);
        if( pispp )
        {
            CAUUID caGUID;

            if( SUCCEEDED( pispp->GetPages( &caGUID )))
            {
                OleCreatePropertyFrame(
                    0, 0, 0,
                    name,                 // Caption for the dialog box
                    1,                    // Number of filters
                    (IUnknown**)&pFilter, // Pointer to the filter whose property 
                    caGUID.cElems,
                    caGUID.pElems,
                    0, 0, 0 );
            }
            SafeRelease( pispp );
        }
    }
}


bool CMainFrame::CreateCamShift()
{
    CoCreateInstance( CLSID_CamShift, NULL, CLSCTX_INPROC_SERVER, 
                      IID_IBaseFilter, (void**)&m_CamShift );
    if( m_CamShift )
    {
        m_CamShift->QueryInterface(IID_ICamShift,(void**)&m_CamShiftProp);
    }

    if( m_CamShiftProp == 0)
    {
        SafeRelease( m_CamShift );
    }
    
    return m_CamShiftProp != 0;
}


bool CMainFrame::CreateCamera( int idx )
{
    ICreateDevEnum* pCreateDevEnum = 0;
    IEnumMoniker*   pEnumMon = 0;
    ULONG           cFetched = 0;
    
    SafeRelease( m_SourceFilter );
    
    CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                      IID_ICreateDevEnum, (void**)&pCreateDevEnum );
    
    /* Create capture device */
    if( pCreateDevEnum )
    {
        IMoniker* pMon = 0;
        pCreateDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEnumMon, 0);
        
        if( idx > 0 )
            pEnumMon->Skip( idx );

        if( pEnumMon && SUCCEEDED( pEnumMon->Next(1, &pMon, &cFetched)) && cFetched == 1 )
        {
            pMon->BindToObject(0, 0, IID_IBaseFilter, (void **)&m_SourceFilter );
            SafeRelease( pMon );
        }
        SafeRelease( pEnumMon );
        SafeRelease( pCreateDevEnum );
    }

    return m_SourceFilter != 0;
}


static const GUID CLSID_BouncingBall = 
{0xFD501041,0x8EBE,0x11CE, {0x81, 0x83, 0x00, 0xAA, 0x00, 0x57, 0x7D, 0xA1 }};

/*static const GUID CLSID_AsyncFile = 
{0xE436EBB5,0x524F,0x11CE,{0x9F,0x53,0x00,0x20,0xAF,0x0B,0xA7,0x70}};*/

static const GUID CLSID_ColorSpaceConverter = 
{0x1643E180,0x90F5,0x11CE, {0x97, 0xD5, 0x00, 0xAA, 0x00, 0x55, 0x59, 0x5A }};

void CMainFrame::CreateBouncingBall()
{
    SafeRelease( m_SourceFilter );
    
    CoCreateInstance( CLSID_BouncingBall, NULL, CLSCTX_INPROC_SERVER, 
                      IID_IBaseFilter, (void **)&m_SourceFilter );
}

/* Create filter graph */
bool CMainFrame::CreateFilterGraph()
{
    HRESULT hr = S_OK;

    /* create graph objects */
    if( m_CamShiftProp != 0 )
    {
        CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                          IID_IGraphBuilder, (void **)&m_GraphBuilder );

        if( m_GraphBuilder != 0 )
        {
            m_GraphBuilder->QueryInterface(IID_IMediaControl,(void**)&m_MediaControl);
            m_GraphBuilder->QueryInterface(IID_IMediaEventEx,(void**)&m_MediaEventEx);
            m_GraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_VideoWindow );
            m_GraphBuilder->QueryInterface(IID_IFilterGraph, (void**)&m_FilterGraph);

            if( m_MediaEventEx )
            {
                // Have the graph signal event via window callbacks for performance
                m_MediaEventEx->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
            }
        }
    }

    /* link filters */
    if( m_FilterGraph )
    {
        if( m_input == 2 )
        {
            WCHAR wname[1000] = L"";
            CFileDialog open_dlg( true, 0, 0, OFN_FILEMUSTEXIST, "All files|*.*||", this );
    
            if( open_dlg.DoModal() )
            {
                CString str = open_dlg.GetPathName();
                if( str.GetLength() > 0 )
                {
                    MultiByteToWideChar( CP_ACP, 0, str, -1, wname, sizeof(wname)/2 );
                    m_FilterGraph->AddFilter( m_CamShift, L"CamShift" );
                    m_GraphBuilder->RenderFile( wname, 0 );
                }
            }
        }
        else if( m_SourceFilter )
        {
            hr = m_FilterGraph->AddFilter( m_SourceFilter, L"Video Source" );

            /*if( SUCCEEDED(hr))
                hr = m_SourceFilter->JoinFilterGraph( m_FilterGraph, L"Video Source" );*/

            IPin* pSourceOut    = get_pin( m_SourceFilter, PINDIR_OUTPUT );
            IPin* pCamShiftIn   = get_pin( m_CamShift, PINDIR_INPUT );
            IPin* pCamShiftOut  = get_pin( m_CamShift, PINDIR_OUTPUT );

            if( SUCCEEDED(hr))
                hr = m_FilterGraph->AddFilter( m_CamShift, L"CamShift" );

            if( SUCCEEDED(hr))
                hr = m_GraphBuilder->Connect( pSourceOut, pCamShiftIn );

            if( SUCCEEDED(hr))
                hr = m_GraphBuilder->Render( pCamShiftOut );

            SafeRelease( pSourceOut );
            SafeRelease( pCamShiftIn );
            SafeRelease( pCamShiftOut );

            if( FAILED(hr))
                DestroyFilterGraph();
        }
    }

    return m_FilterGraph != 0 && hr >= 0;
}


void CMainFrame::ClearFilterGraph()
{
    if( m_FilterGraph )
    {
        IEnumFilters* pEnumFilters = 0;
        m_FilterGraph->EnumFilters( &pEnumFilters );

        if( pEnumFilters )
        {
            IBaseFilter* pFilter = 0;
            ULONG cFetched = 0;
            while( pEnumFilters->Next( 1, &pFilter, &cFetched ) == S_OK && pFilter != 0 )
            {
                m_FilterGraph->RemoveFilter( pFilter );
                SafeRelease( pFilter );
                cFetched = 0;
            }
            SafeRelease( pEnumFilters );
        }
    }
}


// Destroy DirectShow Filter Graph
void CMainFrame::DestroyFilterGraph()
{
    StopGraph();
    ClearFilterGraph();
    
    SafeRelease( m_VideoWindow  );
    SafeRelease( m_FilterGraph );
    SafeRelease( m_GraphBuilder );
    SafeRelease( m_MediaControl );
    SafeRelease( m_MediaEventEx );
    SafeRelease( m_SourceFilter );
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
    
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    m_wndBar.Create( this, IDD_BAR,CBRS_BOTTOM, IDC_BAR );

    CoInitialize(0);

    if( !CreateCamShift())
    {
        MessageBox("Can't create CamShift filter");
        return -1;
    }
    
    // Initialize sliders
    CSliderCtrl* threshold = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_THRESHOLD);
    CSliderCtrl* bins      = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_BINS);
    CSliderCtrl* smin      = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_SMIN);
    CSliderCtrl* vmin      = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_VMIN);
    CSliderCtrl* vmax      = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_VMAX);
    CSliderCtrl* wndWidth  = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_WIN_WIDTH);
    CSliderCtrl* wndHeight = (CSliderCtrl*)m_wndBar.GetDlgItem(IDC_WIN_HEIGHT);

    CvCamShiftParams params;
    m_CamShiftProp->GetParams( &params );

    smin->SetRange( 0, 255 );
    vmin->SetRange( 0, 255 );
    vmax->SetRange( 0, 255 );
    threshold->SetRange( 0, 255 );
    threshold->SetTicFreq( 16 );
    bins->SetRange( 2, 255 );
    bins->SetTicFreq( 10 );
    
    m_wndBar.WriteParamsToControls( params );


    wndWidth->SetRange( 10, 100 );
    wndHeight->SetRange( 10, 100 );
    wndWidth->SetPos( 100 );
    wndHeight->SetPos( 100 );

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnDestroy() 
{
    DestroyFilterGraph();

    SafeRelease( m_FilterGraph );
    SafeRelease( m_CamShift );
    SafeRelease( m_CamShiftProp );
    SafeRelease( m_SourceFilter );

    CoUninitialize();
    CFrameWnd::OnDestroy();
}

void CMainFrame::StartGraph() 
{
    if( m_MediaControl )
    {
        CWnd* av = GetActiveView();

        m_VideoWindow->put_Owner((OAHWND)av->m_hWnd);
        m_VideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);
        m_VideoWindow->put_MessageDrain((OAHWND)av->m_hWnd);
        //m_CamShiftProp->StartTracking();

        SetVideoWindowSize(); 
        m_MediaControl->Run();
    }
}

void CMainFrame::StopGraph() 
{
    if( m_CamShiftProp ) m_CamShiftProp->StopTracking();
    if( m_MediaControl )
    {
        m_MediaControl->Stop();
        m_VideoWindow->put_Visible(OAFALSE);
        m_VideoWindow->put_Owner(NULL);
        m_VideoWindow->put_MessageDrain(0);
    }
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
    CFrameWnd::OnSize(nType, cx, cy);
    SetVideoWindowSize();
}


CRect  CMainFrame::StartTrackerInit()
{
    CRect r( 0, 0, 320, 240 );
    if( m_MediaControl )
    {
        AM_MEDIA_TYPE am;
        OAFilterState fs = State_Stopped;
        m_MediaControl->GetState( 0, &fs );

        if( fs == State_Running )
        {
            if( m_input != 0 )
                m_MediaControl->Pause();
            else
                m_MediaControl->Stop();
        }
        
        IPin* pCamShiftIn = get_pin( m_CamShift, PINDIR_INPUT );
        pCamShiftIn->ConnectionMediaType( &am );

        if( am.pbFormat )
        {
            r.right  = ((VIDEOINFOHEADER*)am.pbFormat)->bmiHeader.biWidth;
            r.bottom = ((VIDEOINFOHEADER*)am.pbFormat)->bmiHeader.biHeight;
            r.bottom = abs( r.bottom );
        }
        else
        {
            r.SetRect(0,0,0,0);
        }

        pCamShiftIn->Release();
    }

    m_src_rect = r;

    return r;
}


void  CMainFrame::EndTrackerInit( CRect r )
{
    if( m_MediaControl && m_CamShiftProp &&
        !r.IsRectEmpty() && !m_src_rect.IsRectEmpty())
    {
        CvCamShiftParams params;
        m_wndBar.ReadParamsFromControls( params );

        params.x = ((float)r.left)/MAX(m_src_rect.Width(),1);
        params.y = ((float)r.top)/MAX(m_src_rect.Height(),1);
        params.width = ((float)r.Width())/MAX(m_src_rect.Width(),1);
        params.height = ((float)r.Height())/MAX(m_src_rect.Height(),1);

        m_CamShiftProp->SetParams( &params ); 
        if( !r.IsRectEmpty() )
            m_CamShiftProp->StartTracking();
        else
            m_CamShiftProp->StopTracking();

        m_MediaControl->Run();
    }
}

void  CMainFrame::OnCamera()
{
    m_input = 0;
    ChangeSource();
}

void CMainFrame::OnUpdateCamera(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck( m_input == 0 );
}


void  CMainFrame::OnBall()
{
    m_input = 1;
    ChangeSource();
}

void CMainFrame::OnUpdateBall(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck( m_input == 1 );
}

void CMainFrame::OnFile() 
{
    m_input = 2;
    ChangeSource();
}


void CMainFrame::OnUpdateFile(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck( m_input == 2 );
}

void CMainFrame::ChangeSource()
{
    StopGraph();
    DestroyFilterGraph();

    if( m_input < 2 )
    {
        switch( m_input )
        {
        case 0: /* camera */ CreateCamera();
            break;
        default: /* ball */ CreateBouncingBall();
            break;
        }

        if( m_SourceFilter == 0 )
        {
            m_input = -1;
            return;
        }
    }

    if( !CreateFilterGraph() && m_input == 0 )
    {
        for( int i = 1; i <= 10; i++ )
        {
            CreateCamera(i);
            if( CreateFilterGraph())
                break;
        }
    }

    if( m_SourceFilter )
        show_prop_page( m_SourceFilter, L"Video Source Properties" );

    StartGraph();
}


void CMainFrame::OnPlayPause() 
{
    if( m_MediaControl )
    {
        OAFilterState fs = State_Stopped;
        if( m_MediaControl->GetState( 0, &fs ) == S_OK )
        {
            if( fs == State_Running )
                m_MediaControl->Pause();
            else if( fs == State_Paused )
                m_MediaControl->Run();
        }
    }
}


void CMainFrame::OnUpdatePlayPause(CCmdUI* pCmdUI) 
{
    OAFilterState fs = State_Stopped;
    if( m_MediaControl )
    {
        m_MediaControl->GetState( 0, &fs );
    }
    pCmdUI->SetCheck( fs == State_Running );
    pCmdUI->Enable( fs == State_Running || fs == State_Paused );
}


void CMainFrame::GetScaleFactor( int& sx, int &sy )
{
    sx = ((CSliderCtrl*)m_wndBar.GetDlgItem(IDC_WIN_WIDTH))->GetPos();
    sy = ((CSliderCtrl*)m_wndBar.GetDlgItem(IDC_WIN_HEIGHT))->GetPos();
}

CRect CMainFrame::GetVideoWindowSize() 
{
    CWnd* av = GetActiveView();
    CRect rc;
    if( av )
    {
        int width, height;
        GetScaleFactor( width, height );

        av->GetClientRect( &rc );

        rc.right  = rc.right * width / 100;
        rc.bottom = rc.bottom * height / 100;
    }

    return rc;
}


void CMainFrame::SetVideoWindowSize() 
{
    CRect rc = GetVideoWindowSize();
    if( m_VideoWindow )
    {
        m_VideoWindow->SetWindowPosition( rc.left, rc.top, rc.right, rc.bottom );
    }
}


/////////////////////////////////////////////////////////////////////////////
// CBar dialog


CBar::CBar() : CDialogBar()
{
	//{{AFX_DATA_INIT(CBar)
	m_Threshold = 0;
	m_Smin = 0;
    m_Vmax = 0;
	m_Vmin = 0;
	m_Bins = 0;
    m_ShowPicture = TRUE;
    m_ShowBackProject = FALSE;
    m_ShowHistogram = FALSE;
	//}}AFX_DATA_INIT
}


void CBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBar)
	DDX_Check(pDX,  IDC_PICTURE, m_ShowPicture );
    DDX_Check(pDX,  IDC_BACKPROJECT, m_ShowBackProject );
    DDX_Check(pDX,  IDC_HISTOGRAM, m_ShowHistogram );
    DDX_Slider(pDX, IDC_SMIN, m_Smin);
	DDX_Slider(pDX, IDC_THRESHOLD, m_Threshold);
	DDX_Slider(pDX, IDC_VMAX, m_Vmax);
	DDX_Slider(pDX, IDC_VMIN, m_Vmin);
	DDX_Slider(pDX, IDC_BINS, m_Bins);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBar, CDialogBar)
	//{{AFX_MSG_MAP(CBar)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_PICTURE, OnPicture)
	ON_BN_CLICKED(IDC_BACKPROJECT, OnBackProject)
	ON_BN_CLICKED(IDC_HISTOGRAM, OnHistogram)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBar message handlers

void CBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    int  code = pScrollBar->GetDlgCtrlID();
    CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();

    UpdateData(1);
    
    switch( code )
    {
    case IDC_SMIN:
    case IDC_VMIN:
    case IDC_VMAX:
    case IDC_THRESHOLD:
    case IDC_BINS:
        if( mainframe->m_CamShiftProp )
        {
            CvCamShiftParams params;
            mainframe->m_CamShiftProp->GetParams( &params );
            int bins = params.bins;
            ReadParamsFromControls( params );
            mainframe->m_CamShiftProp->SetParams( &params );
            if( bins != params.bins )
            {
                mainframe->m_CamShiftProp->StartTracking();
            }
        }
        break;
    case IDC_WIN_WIDTH:
    case IDC_WIN_HEIGHT:
        mainframe->SetVideoWindowSize();
        break;
    default:
        ASSERT(0);
    }
}

void CBar::OnPicture() 
{
    UpdateData(1);
    CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
    if( mainframe->m_CamShiftProp )
    {
        CvCamShiftParams params;
        mainframe->m_CamShiftProp->GetParams( &params );
        params.view = 0;
        mainframe->m_CamShiftProp->SetParams( &params );
    }
}

void CBar::OnBackProject() 
{
    UpdateData(1);
    CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
    if( mainframe->m_CamShiftProp )
    {
        CvCamShiftParams params;
        mainframe->m_CamShiftProp->GetParams( &params );
        params.view = 1;
        mainframe->m_CamShiftProp->SetParams( &params );
    }
}

void CBar::OnHistogram() 
{
    UpdateData(1);
    CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
    if( mainframe->m_CamShiftProp )
    {
        CvCamShiftParams params;
        mainframe->m_CamShiftProp->GetParams( &params );
        params.view = 2;
        mainframe->m_CamShiftProp->SetParams( &params );
    }
}


CBar::ReadParamsFromControls( CvCamShiftParams& params )
{
    CSliderCtrl* threshold = (CSliderCtrl*)GetDlgItem(IDC_THRESHOLD);
    CSliderCtrl* bins      = (CSliderCtrl*)GetDlgItem(IDC_BINS);
    CSliderCtrl* smin      = (CSliderCtrl*)GetDlgItem(IDC_SMIN);
    CSliderCtrl* vmin      = (CSliderCtrl*)GetDlgItem(IDC_VMIN);
    CSliderCtrl* vmax      = (CSliderCtrl*)GetDlgItem(IDC_VMAX);
    params.view = ((CButton*)GetDlgItem(IDC_PICTURE))->GetCheck() ? 0 :
                  ((CButton*)GetDlgItem(IDC_BACKPROJECT))->GetCheck() ? 1 : 2;
    
    params.Smin = smin->GetPos();
    params.Vmin = vmin->GetPos();
    params.Vmax = vmax->GetPos();

    params.threshold = threshold->GetPos();

    params.bins = bins->GetPos();
}


CBar::WriteParamsToControls( CvCamShiftParams& params )
{
    CSliderCtrl* threshold = (CSliderCtrl*)GetDlgItem(IDC_THRESHOLD);
    CSliderCtrl* bins      = (CSliderCtrl*)GetDlgItem(IDC_BINS);
    CSliderCtrl* smin      = (CSliderCtrl*)GetDlgItem(IDC_SMIN);
    CSliderCtrl* vmin      = (CSliderCtrl*)GetDlgItem(IDC_VMIN);
    CSliderCtrl* vmax      = (CSliderCtrl*)GetDlgItem(IDC_VMAX);
    
    smin->SetPos( params.Smin );

    vmin->SetRange( 0, 255 );
    vmin->SetPos( params.Vmin );

    vmax->SetRange( 0, 255 );
    vmax->SetPos( params.Vmax );

    threshold->SetRange( 0, 255 );
    threshold->SetPos( params.threshold );
    threshold->SetTicFreq( 16 );

    bins->SetRange( 2, 255 );
    bins->SetPos( params.bins );
    bins->SetTicFreq( 10 );

    ((CButton*)GetDlgItem(IDC_PICTURE))->SetCheck( params.view == 0 );
    ((CButton*)GetDlgItem(IDC_BACKPROJECT))->SetCheck( params.view == 1 );
    ((CButton*)GetDlgItem(IDC_HISTOGRAM))->SetCheck( params.view == 2 );
}

