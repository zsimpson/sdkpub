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
//M*/// DGProp.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "DGProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDGProp dialog


IMPLEMENT_DYNCREATE(CDGProp, CPropertyPage)

CDGProp::CDGProp(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CDGProp::IDD)
{
	//{{AFX_DATA_INIT(CDGProp)
	m_dgName = _T("Move down");
	m_isSaveToFile = FALSE;
	m_savePath = _T("");
	m_isCollectGesture = FALSE;
	//}}AFX_DATA_INIT
}


void CDGProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDGProp)
	DDX_CBString(pDX, IDC_DGNAME, m_dgName);
	DDX_Check(pDX, IDC_DGSAVE, m_isSaveToFile);
	DDX_Text(pDX, IDC_ESAVEPATH, m_savePath);
	DDX_Check(pDX, IDC_DGCOLLECT, m_isCollectGesture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDGProp, CPropertyPage)
	//{{AFX_MSG_MAP(CDGProp)
	ON_BN_CLICKED(IDC_DGCOLLECT, OnDgcollect)
	ON_CBN_EDITCHANGE(IDC_DGNAME, OnEditchangeDgname)
	ON_CBN_SELENDOK(IDC_DGNAME, OnSelendokDgname)
	ON_CBN_CLOSEUP(IDC_DGNAME, OnCloseupDgname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDGProp message handlers

BOOL CDGProp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    CComboBox* box = (CComboBox*)GetDlgItem(IDC_DGNAME);

    box->SetCurSel(0);

    ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CDGProp::GetGestureName()
{
    return m_dgName;
}

BOOL CDGProp::IsSaveToFile()
{
    return m_isSaveToFile;
}

CString CDGProp::GetSavePath()
{
    return m_savePath;
}

void CDGProp::OnDgcollect() 
{
	UpdateData(TRUE);
}

void CDGProp::OnEditchangeDgname() 
{
	UpdateData(TRUE);	
}

void CDGProp::OnSelendokDgname() 
{
	UpdateData(TRUE);	
}

void CDGProp::OnCloseupDgname() 
{
	UpdateData(TRUE);	
	CComboBox* box = (CComboBox*)GetDlgItem(IDC_DGNAME);
	int i = box->GetCurSel();
	box->GetLBText(i, m_dgName);
}
