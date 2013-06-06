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
//M*/// InfoDialogs.cpp : implementation file
//

#include "stdafx.h"
#include "HMMDemo.h"
#include "InfoDialogs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonName dialog


CPersonName::CPersonName( CFaceBase& base, CWnd* pParent /*=NULL*/)
    : CDialog(CPersonName::IDD, pParent), m_base(base)
{
    //{{AFX_DATA_INIT(CPersonName)
    //}}AFX_DATA_INIT
}


void CPersonName::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPersonName)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPersonName, CDialog)
    //{{AFX_MSG_MAP(CPersonName)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonName message handlers

BOOL CPersonName::OnInitDialog() 
{
    CDialog::OnInitDialog();

    CComboBox* combo = (CComboBox*)GetDlgItem( IDC_PERSON_LIST );
    if( combo )
    {
        CPersonList& list = m_base.GetPersonList();
        POSITION pos = list.GetHeadPosition();

        while( pos )
        {
            CPerson* person = list.GetNext( pos );
            combo->AddString( person->GetName() );
        }
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CPersonName::OnOK() 
{
    GetDlgItemText( IDC_PERSON_LIST, m_person_name );
    CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CBaseInfo dialog


CBaseInfo::CBaseInfo(CFaceBase& base, CWnd* pParent /*=NULL*/)
    : CDialog(CBaseInfo::IDD, pParent), m_base(base)
{
    //{{AFX_DATA_INIT(CBaseInfo)
    //}}AFX_DATA_INIT
}


void CBaseInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CBaseInfo)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseInfo, CDialog)
    //{{AFX_MSG_MAP(CBaseInfo)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseInfo message handlers


BOOL CBaseInfo::OnInitDialog() 
{
    CDialog::OnInitDialog();

    m_filename = m_base.GetFileName();
    m_basename = m_base.GetName();

    GetDlgItem(IDC_FILENAME)->SetWindowText( m_filename );
    GetDlgItem(IDC_BASENAME)->SetWindowText( m_basename );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseInfo::OnBrowse() 
{
    CFileDialog dlg( FALSE, "txt", 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                     "Text files (*.txt)|*.txt||", this );
    if( dlg.DoModal())
    {
        GetDlgItem(IDC_FILENAME)->SetWindowText( dlg.GetPathName());
    }
}

void CBaseInfo::OnOK() 
{
	GetDlgItem(IDC_FILENAME)->GetWindowText( m_filename );
    GetDlgItem(IDC_BASENAME)->GetWindowText( m_basename );
    CDialog::OnOK();
}
