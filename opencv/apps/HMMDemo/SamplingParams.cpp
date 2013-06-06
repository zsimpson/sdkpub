// SamplingParams.cpp : implementation file
//

#include "stdafx.h"
#include "hmmdemo.h"
#include "SamplingParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSamplingParams property page

IMPLEMENT_DYNCREATE(CSamplingParams, CPropertyPage)

CSamplingParams::CSamplingParams() : CPropertyPage(CSamplingParams::IDD)
{
	//{{AFX_DATA_INIT(CSamplingParams)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_delta = cvSize( 4, 4 );
    m_obsSize = cvSize( 3, 3 );
    m_dctSize = cvSize( 12, 12 );

}

CSamplingParams::~CSamplingParams()
{
}

void CSamplingParams::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSamplingParams)
		DDX_Text(pDX, IDC_DCT_WIDTH, m_dctSize.width);
        DDX_Text(pDX, IDC_DCT_HEIGHT, m_dctSize.height);
        DDX_Text(pDX, IDC_DELTA_WIDTH, m_delta.width);
        DDX_Text(pDX, IDC_DELTA_HEIGHT, m_delta.height);
        DDX_Text(pDX, IDC_OBS_WIDTH, m_obsSize.width);
        DDX_Text(pDX, IDC_OBS_HEIGHT, m_obsSize.height);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSamplingParams, CPropertyPage)
	//{{AFX_MSG_MAP(CSamplingParams)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSamplingParams message handlers

BOOL CSamplingParams::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
