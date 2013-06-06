// HMMParams.cpp : implementation file
//

#include "stdafx.h"
#include "hmmdemo.h"
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
    m_States[0] = 5;//superstate

    m_States[1] = 3;
    m_States[2] = 6;
    m_States[3] = 6;
    m_States[4] = 6;
    m_States[5] = 3;
    m_States[6] = 0;
    m_States[7] = 0;

	//{{AFX_DATA_INIT(CHMMParams)
	m_NumMix = 3;
	//}}AFX_DATA_INIT
}

CHMMParams::~CHMMParams()
{
}

void CHMMParams::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHMMParams)
    DDX_Text(pDX, IDC_NUMIX, m_NumMix);
    DDX_Text(pDX, IDC_EDIT1, m_States[1]);
    DDX_Text(pDX, IDC_EDIT2, m_States[2]);
    DDX_Text(pDX, IDC_EDIT3, m_States[3]);
    DDX_Text(pDX, IDC_EDIT4, m_States[4]);
    DDX_Text(pDX, IDC_EDIT5, m_States[5]);
    DDX_Text(pDX, IDC_EDIT6, m_States[6]);
    DDX_Text(pDX, IDC_EDIT7, m_States[7]);
	DDV_MinMaxInt(pDX, m_NumMix, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHMMParams, CPropertyPage)
	//{{AFX_MSG_MAP(CHMMParams)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMMParams message handlers

BOOL CHMMParams::OnInitDialog() 
{       
	CPropertyPage::OnInitDialog();
	
    //init check boxes
    for( int i = 0; i < 7; i++ )
    {
        BOOL enable  = i < m_States[0];
         ((CButton*)GetDlgItem( IDC_CHECK1 + i ))->SetCheck( enable );
         GetDlgItem( IDC_EDIT1 + i )->EnableWindow( enable );
    }     

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CHMMParams::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
    if ( (nID >= IDC_CHECK1) && (nID <= IDC_CHECK7) )
    {
        int offset =  nID - IDC_CHECK1;

        BOOL enable;
        enable = ((CButton*)GetDlgItem( nID ))->GetCheck();

        //enable all previous
        if (enable)
        {
            for( int i = 0 ; i <= offset; i++ )  
            {
                ((CButton*)GetDlgItem( IDC_CHECK1 + i ))->SetCheck( enable );
                GetDlgItem( IDC_EDIT1 + i )->EnableWindow( enable );
            }
            m_States[0] = offset+1;

        }
        else   //disable all consequtive
        {
            for( int i = offset ; i < 7; i++ )  
            {
                ((CButton*)GetDlgItem( IDC_CHECK1 + i ))->SetCheck( enable );
                GetDlgItem( IDC_EDIT1 + i )->EnableWindow( enable );
            }
            m_States[0] = offset;
        }
        

    }
	
	return CPropertyPage::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
