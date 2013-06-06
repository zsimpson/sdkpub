// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "mltaccum.h"

#include "MainFrm.h"
#include "dExposure.h"
#include "drun.h"
#include "dHardwareSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	
BOOL CMainFrame::m_efID_EXPERIMENT_EXPOSURE;
BOOL CMainFrame::m_efID_EXPERIMENT_ACQUIRE;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EXPERIMENT_HARDWARE, OnExperimentHardware)
	ON_COMMAND(ID_EXPERIMENT_EXPOSURE, OnExperimentExposure)
	ON_COMMAND(ID_EXPERIMENT_ACQUIRE, OnExperimentAcquire)
	ON_UPDATE_COMMAND_UI(ID_EXPERIMENT_EXPOSURE, OnUpdateHardwareUpdate)
	ON_UPDATE_COMMAND_UI(ID_EXPERIMENT_ACQUIRE, OnUpdateHardwareUpdate)
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
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

void CMainFrame::OnExperimentHardware() 
{
	HardwareSetup * ptrhwdlg = new HardwareSetup;
	ptrhwdlg->DoModal();
		
}

void CMainFrame::OnExperimentExposure() 
{
CdExposure * ptrexdlg = new CdExposure;
	ptrexdlg->DoModal();
	
}

void CMainFrame::OnExperimentAcquire() 
{
	Cdrun * ptrrndlg = new Cdrun;
	ptrrndlg->DoModal();
	
}

void CMainFrame::OnUpdateHardwareUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_efID_EXPERIMENT_EXPOSURE);
	pCmdUI->Enable(m_efID_EXPERIMENT_ACQUIRE);
}