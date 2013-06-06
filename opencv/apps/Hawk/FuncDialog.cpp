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
//M*/// FuncDialog.cpp : implementation file
//

#include "stdafx.h"
#include "hawk.h"
#include "FuncDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFuncDialog dialog


CFuncDialog::CFuncDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFuncDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFuncDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFuncDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFuncDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFuncDialog, CDialog)
	//{{AFX_MSG_MAP(CFuncDialog)
	ON_LBN_SELCHANGE(IDC_FUNCLIST, OnSelchangeFunclist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFuncDialog message handlers

void CFuncDialog::SetModuleName(LPCTSTR name)
{
    m_moduleName = name;
    if(IsWindow(m_hWnd))
        UpdateModuleName();
}

BOOL CFuncDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    UpdateModuleName();
    UpdateItems();
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFuncDialog::SetItems(CStringArray* names)
{
    m_items = names;
}

CString CFuncDialog::GetCurrentItem()
{
    return m_current;
}

void CFuncDialog::UpdateModuleName()
{
    CStatic* pStatic = (CStatic*)GetDlgItem(IDC_FUNCSTATIC);
    pStatic->SetWindowText(m_moduleName);
}

void CFuncDialog::UpdateItems()
{
    CListBox* pList = (CListBox*)GetDlgItem(IDC_FUNCLIST);
    int count = pList->GetCount();

    for(int i = 0; i < m_items->GetSize(); i++)
    {
        int e = pList->AddString(m_items->GetData()[i]);
    }
    pList->SetCurSel(0);
    pList->UpdateWindow();
}

void CFuncDialog::OnOK() 
{
    CListBox* pList = (CListBox*)GetDlgItem(IDC_FUNCLIST);
    pList->GetText(pList->GetCurSel(), m_current);
	
	CDialog::OnOK();
}

void CFuncDialog::OnCancel() 
{
    m_current.Empty();	
	CDialog::OnCancel();
}

void CFuncDialog::OnSelchangeFunclist() 
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    CStatic* tip = (CStatic*)GetDlgItem(IDC_FUNCTIP);
    CListBox* pList = (CListBox*)GetDlgItem(IDC_FUNCLIST);
    CString current;
    pList->GetText(pList->GetCurSel(), current);

    current = app->GenDecl(current);
    tip->SetWindowText(current);
}
