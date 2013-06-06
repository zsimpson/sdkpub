// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Imaging.h"

#include "MainFrm.h"
#include "dHardware.h"
#include "dExSetup.h"
#include "dAcquire.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CMainFrame::m_efID_EXPERIMENT_EXPERSETUP;
BOOL CMainFrame::m_efID_EXPERIMENT_ACQUIRE;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EXPERIMENT_HARDWARESETUP, OnExperimentHardwaresetup)
	ON_COMMAND(ID_EXPERIMENT_EXPERIMENTSETUP, OnExperimentExperimentsetup)
	ON_UPDATE_COMMAND_UI(ID_EXPERIMENT_EXPERIMENTSETUP, OnUpdateHardwareUpdate)
	ON_COMMAND(ID_EXPERIMENT_ACQUIREEXPERIMENT, OnExperimentAcquireexperiment)
	ON_UPDATE_COMMAND_UI(ID_EXPERIMENT_ACQUIREEXPERIMENT, OnUpdateExSetupUpdate)
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
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
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

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
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

void CMainFrame::OnExperimentHardwaresetup() 
{
	CdHardware * ptrhwdlg = new CdHardware;
	ptrhwdlg->DoModal();	
}

void CMainFrame::OnExperimentExperimentsetup() 
{
	CdExSetup * ptrexdlg = new CdExSetup;
	ptrexdlg->DoModal();
	
}

void CMainFrame::OnUpdateHardwareUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_efID_EXPERIMENT_EXPERSETUP);
}

void CMainFrame::OnUpdateExSetupUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_efID_EXPERIMENT_ACQUIRE);
}

void CMainFrame::OnExperimentAcquireexperiment() 
{
	CdAcquire * ptracdlg = new CdAcquire;
	ptracdlg->DoModal();	
}
