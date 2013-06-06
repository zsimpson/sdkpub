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
//M*/// PTOptions.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "PTOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTOptions property page

IMPLEMENT_DYNCREATE(CPTOptions, CPropertyPage)

CPTOptions::CPTOptions() : CPropertyPage(CPTOptions::IDD)
{
	//{{AFX_DATA_INIT(CPTOptions)
	m_checkContours = FALSE;
	m_depthThresh = 0.0f;
	m_diffThresh = 0.0f;
	m_dispThresh = 0.0f;
    m_rawRes = 0;
    m_stereoRes = 0;
	m_maxDisp = 0;
	m_minDisp = 0;
	//}}AFX_DATA_INIT
}

CPTOptions::~CPTOptions()
{
}

void CPTOptions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPTOptions)
	DDX_Check(pDX, IDC_CHECKCONTOUR, m_checkContours);
	DDX_Text(pDX, IDC_DEPTHTHRESH, m_depthThresh);
	DDX_Text(pDX, IDC_DIFFTHRESH, m_diffThresh);
	DDX_Text(pDX, IDC_DISPHRESH, m_dispThresh);
	DDX_Text(pDX, IDC_PTMAXDISP, m_maxDisp);
	DDX_Text(pDX, IDC_PTMINDISP, m_minDisp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPTOptions, CPropertyPage)
	//{{AFX_MSG_MAP(CPTOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTOptions message handlers

#define GET_CONTROL(t, o, r) t* o = (t*)GetDlgItem((r));
BOOL CPTOptions::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    GET_CONTROL(CComboBox, pStereoRes, IDC_PTSTEREORES);
    GET_CONTROL(CComboBox, pRawRes, IDC_PTRAWRES);

    pStereoRes->SetCurSel(m_stereoRes);
    pRawRes->SetCurSel(m_rawRes);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPTOptions::OnOK() 
{
    GET_CONTROL(CComboBox, pStereoRes, IDC_PTSTEREORES);
    GET_CONTROL(CComboBox, pRawRes, IDC_PTRAWRES);

    m_stereoRes = pStereoRes->GetCurSel();
    m_rawRes = pRawRes->GetCurSel();
    	
	CPropertyPage::OnOK();
}
