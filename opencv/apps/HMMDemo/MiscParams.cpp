// MiscParams.cpp : implementation file
//

#include "stdafx.h"
#include "hmmdemo.h"
#include "MiscParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiscParams property page

IMPLEMENT_DYNCREATE(CMiscParams, CPropertyPage)

CMiscParams::CMiscParams() : CPropertyPage(CMiscParams::IDD)
{
	//{{AFX_DATA_INIT(CMiscParams)
	m_FixedWidth = 0;
	m_FixedHeight = 0;
	m_useHeight = FALSE;
	m_useWidth = FALSE;
	m_SuppressIntensity = FALSE;
	//}}AFX_DATA_INIT
}

CMiscParams::~CMiscParams()
{
}

void CMiscParams::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiscParams)
	DDX_Text(pDX, IDC_FIX_WIDTH, m_FixedWidth);
	DDX_Text(pDX, IDC_FIX_HEIGHT, m_FixedHeight);
	DDX_Check(pDX, IDC_TO_HEIGHT, m_useHeight);
	DDX_Check(pDX, IDC_TO_WIDTH, m_useWidth);
	DDX_Check(pDX, IDC_SUPPRESS_INTENSITY, m_SuppressIntensity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMiscParams, CPropertyPage)
	//{{AFX_MSG_MAP(CMiscParams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiscParams message handlers
