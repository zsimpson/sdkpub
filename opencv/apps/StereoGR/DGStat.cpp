// DGStat.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "DGStat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDGStat property page

IMPLEMENT_DYNCREATE(CDGStat, CPropertyPage)

CDGStat::CDGStat() : CPropertyPage(CDGStat::IDD)
{
	//{{AFX_DATA_INIT(CDGStat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDGStat::~CDGStat()
{
}

void CDGStat::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDGStat)
	DDX_Control(pDX, IDC_DGSTAT_LIST, m_name_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDGStat, CPropertyPage)
	//{{AFX_MSG_MAP(CDGStat)
	ON_LBN_SELCHANGE(IDC_DGSTAT_LIST, OnSelchangeDgstatList)
	ON_BN_CLICKED(IDC_DELETE_DG, OnDeleteDg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDGStat message handlers

void CDGStat::OnSelchangeDgstatList() 
{
    CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
    CDynGestServer& server = app->m_dgServer;

    if ( m_name_list.GetCurSel() >= 0 )
    {
        CString name;
        m_name_list.GetText(m_name_list.GetCurSel(), name );
    
        CDynGesture* gesture = server.FindGesture( name );
        if ( gesture )
        {
            CString str;
            str.Format( "%d", gesture->GetSeqNumber() );
            GetDlgItem( IDC_DGSTAT_NUMSEQ )->SetWindowText(str);

            str.Format( "%s", gesture->m_trained ? "YES" : "NO" );
            GetDlgItem( IDC_DGSTAT_TRAINED )->SetWindowText(str);
        }
    }
    else
    {
        GetDlgItem( IDC_DGSTAT_NUMSEQ )->SetWindowText("");
        GetDlgItem( IDC_DGSTAT_TRAINED )->SetWindowText("");
    }
	// TODO: Add your control notification handler code here
}

BOOL CDGStat::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	Update();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDGStat::OnDeleteDg() 
{
	CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
    CDynGestServer& server = app->m_dgServer;

    if ( m_name_list.GetCurSel() >= 0 )
    {
        CString name;
        m_name_list.GetText(m_name_list.GetCurSel(), name );

        if ( server.RemoveGesture( name ) )
        {
            m_name_list.DeleteString( m_name_list.GetCurSel() );
        }
        m_name_list.SetCurSel(0);
        OnSelchangeDgstatList();
    }
}

void CDGStat::Update()
{
    CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
    CDynGestServer& server = app->m_dgServer;

	// Clean up the list box
	for(int i = 0; i < m_name_list.GetCount(); i++)
	{
		m_name_list.DeleteString(i);
	}
	
    for(i = 0; i < server.GetNumGestures(); i++ )
    {
        CString name = server.GetGesture(i)->GetName();
        m_name_list.AddString( name );
    }           

    m_name_list.SetCurSel(0);
    OnSelchangeDgstatList();
}

BOOL CDGStat::OnSetActive() 
{
	Update();	
	return CPropertyPage::OnSetActive();
}
