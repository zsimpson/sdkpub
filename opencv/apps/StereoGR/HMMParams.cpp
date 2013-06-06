// HMMParams.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "HMMParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMMParams property page

IMPLEMENT_DYNCREATE(CHMMParams, CPropertyPage)

CHMMParams::CHMMParams() : CPropertyPage(CHMMParams::IDD)
{
	//{{AFX_DATA_INIT(CHMMParams)
	m_num_mix = 6;
	m_num_states = 5;
	//}}AFX_DATA_INIT
}

CHMMParams::~CHMMParams()
{
}

void CHMMParams::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHMMParams)
	DDX_Text(pDX, IDC_NUM_MIX, m_num_mix);
	DDV_MinMaxInt(pDX, m_num_mix, 1, 10);
	DDX_Text(pDX, IDC_NUM_STATE, m_num_states);
	DDV_MinMaxInt(pDX, m_num_states, 2, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHMMParams, CPropertyPage)
	//{{AFX_MSG_MAP(CHMMParams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMMParams message handlers
