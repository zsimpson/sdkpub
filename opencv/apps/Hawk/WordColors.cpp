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
//M*/// WordColors.cpp : implementation file
//

#include "stdafx.h"
#include "hawk.h"
#include "stdafx.h"
#include "Hawk.h"
#include "MainFrm.h"

#include "HawkDoc.h"
#include "HawkView.h"
#include "GotoLine.h"
#include "WordColors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordColors dialog


CWordColors::CWordColors(CWnd* pParent /*=NULL*/)
	: CDialog(CWordColors::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWordColors)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWordColors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordColors)
	DDX_Control(pDX, IDC_SAMPLE, m_Sample);
	DDX_Control(pDX, IDC_KEYWORDS, m_KeyWords);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWordColors, CDialog)
	//{{AFX_MSG_MAP(CWordColors)
	ON_LBN_SELCHANGE(IDC_KEYWORDS, OnSelchangeKeywords)
	ON_BN_CLICKED(IDC_FOREGROUND, OnForeground)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordColors message handlers

BOOL CWordColors::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_KeyWords.AddString("Selection Background");
    m_KeyWords.AddString("Selection Foreground");
    m_KeyWords.AddString("Background");
    m_KeyWords.AddString("Normal");
    m_KeyWords.AddString("Comment");
    m_KeyWords.AddString("String");
    m_KeyWords.AddString("KeyWord");
    m_KeyWords.AddString("Number");

    m_KeyWords.SetCurSel(0);
    OnSelchangeKeywords();
    m_Sample.SetWindowText("Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample "
                           "Sample Sample Sample Sample Sample Sample Sample Sample ");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

ColorScheme CWordColors::DoModal(ColorScheme scheme)
{
    m_Colors = scheme;
    if(CDialog::DoModal() == IDOK)
    {
        m_Colors.bkBrush = (HBRUSH)CreateSolidBrush( m_Colors.background );

        CHawkApp* app = (CHawkApp*)AfxGetApp();
        app->WriteProfileInt("Configuration", "background", m_Colors.background);
        app->WriteProfileInt("Configuration", "TOKEN_NORMAL", m_Colors.clr[TOKEN_NORMAL]);
        app->WriteProfileInt("Configuration", "TOKEN_KEYWORD", m_Colors.clr[TOKEN_KEYWORD]);
        app->WriteProfileInt("Configuration", "TOKEN_COMMENT", m_Colors.clr[TOKEN_COMMENT]);
        app->WriteProfileInt("Configuration", "TOKEN_NUMBER", m_Colors.clr[TOKEN_NUMBER]);
        app->WriteProfileInt("Configuration", "TOKEN_STRING", m_Colors.clr[TOKEN_STRING]);
        app->WriteProfileInt("Configuration", "selbk", m_Colors.selbk);
        app->WriteProfileInt("Configuration", "selfk", m_Colors.selfk);
        return m_Colors;
    }
    else return scheme;
}

void CWordColors::OnSelchangeKeywords() 
{
	// TODO: Add your control notification handler code here
    switch(m_KeyWords.GetCurSel())
    {
    case 0:
        m_Color = (COLORREF*)&m_Colors.selbk;
        m_Background = m_Colors.selbk;
        m_Foreground = m_Colors.selfk;
        m_Entry = "selbk";
        break;
    case 1:
        m_Color = (COLORREF*)&m_Colors.selfk;
        m_Background = m_Colors.selbk;
        m_Foreground = m_Colors.selfk;
        m_Entry = "selfk";
        break;
    case 2:
        m_Color = (COLORREF*)&m_Colors.background;
        m_Background = m_Foreground = m_Colors.background;
        m_Entry = "background";
        break;
    case 3:
        m_Color = (COLORREF*)&m_Colors.clr[TOKEN_NORMAL];
        m_Background = m_Colors.background;
        m_Foreground = m_Colors.clr[0];
        m_Entry = "TOKEN_NORMAL";
        break;
    case 4:
        m_Color = (COLORREF*)&m_Colors.clr[TOKEN_COMMENT];
        m_Background = m_Colors.background;
        m_Foreground = m_Colors.clr[1];
        m_Entry = "TOKEN_COMMENT";
        break;
    case 5:
        m_Color = (COLORREF*)&m_Colors.clr[TOKEN_STRING];
        m_Background = m_Colors.background;
        m_Foreground = m_Colors.clr[2];
        m_Entry = "TOKEN_STRING";
        break;
    case 6:
        m_Color = (COLORREF*)&m_Colors.clr[TOKEN_KEYWORD];
        m_Background = m_Colors.background;
        m_Foreground = m_Colors.clr[3];
        m_Entry = "TOKEN_KEYWORD";
        break;
    case 7:
        m_Color = (COLORREF*)&m_Colors.clr[TOKEN_NUMBER];
        m_Background = m_Colors.background;
        m_Foreground = m_Colors.clr[4];
        m_Entry = "TOKEN_NUMBER";
        break;
    }
    m_Sample.RedrawWindow();
}

void CWordColors::OnForeground() 
{
	// TODO: Add your control notification handler code here
    static COLORREF colors[16];
    CHOOSECOLOR cl = {sizeof(cl), AfxGetMainWnd()->m_hWnd, 0, *m_Color, colors,
                      CC_RGBINIT, 0, 0, 0};
    BOOL res = ChooseColor(&cl);
    if(res) *m_Color = cl.rgbResult;
    OnSelchangeKeywords();
}

HBRUSH CWordColors::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
    if(pWnd->m_hWnd == m_Sample.m_hWnd)
    {
        pDC->SetTextColor(m_Foreground);
        pDC->SetBkColor(m_Background);
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
