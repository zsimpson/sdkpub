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
//M*/// PTOffline.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "PTOffline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTOffline dialog


CPTOffline::CPTOffline(CWnd* pParent /*=NULL*/)
	: CDialog(CPTOffline::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPTOffline)
	m_strValue = _T("");
	m_strSaveFile = _T("");
	//}}AFX_DATA_INIT
}


void CPTOffline::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPTOffline)
	DDX_Text(pDX, IDC_EDITFRAMESCOUNT, m_strValue);
	DDX_Text(pDX, IDC_EDITPTSAVEFILE, m_strSaveFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPTOffline, CDialog)
	//{{AFX_MSG_MAP(CPTOffline)
	ON_BN_CLICKED(IDC_BUTTON_BROWSESAVEFILE, OnButtonBrowsesavefile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTOffline message handlers

void CPTOffline::SetFramesCount(int count)
{
    m_strValue.Format("%d", count);
}

int CPTOffline::GetFrameCount() const
{
    return atoi(LPCTSTR(m_strValue));
}

BOOL CPTOffline::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    ShowWindow(SW_SHOW)	;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPTOffline::OnButtonBrowsesavefile() 
{
//    CFileDialog	dlg(TRUE, 0, 0, 0, 0, this);
//    if(dlg.DoModal() == IDOK)
//    {
//        CString fpath = dlg.GetPathName();
//        char drive[_MAX_DRIVE];
//        char path[_MAX_PATH];
//        _splitpath(LPCTSTR(fpath), drive, path, 0, 0);
//        m_strSaveFile = CString(drive) + path;
//        UpdateData(FALSE);
//    }
}
