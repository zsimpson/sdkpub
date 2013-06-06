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
//M*/// GROptions.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "GROptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGROptions property page

IMPLEMENT_DYNCREATE(CGROptions, CPropertyPage)

CGROptions::CGROptions() : CPropertyPage(CGROptions::IDD)
{
	//{{AFX_DATA_INIT(CGROptions)
	m_maskImprove = FALSE;
	m_segThresh = 0;
	m_frameCount = 0;
	//}}AFX_DATA_INIT
}

CGROptions::~CGROptions()
{
}

void CGROptions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGROptions)
	DDX_Check(pDX, IDC_MASKIMPROVE, m_maskImprove);
	DDX_Text(pDX, IDC_SEGTHRESH, m_segThresh);
	DDX_Text(pDX, IDC_SFRAMECOUNT, m_frameCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGROptions, CPropertyPage)
	//{{AFX_MSG_MAP(CGROptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGROptions message handlers
