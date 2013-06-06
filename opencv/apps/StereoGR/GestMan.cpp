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
//M*/// GestRec.cpp : implementation file
//

#include "stdafx.h"
#include "stereogr.h"
#include "GestMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGestRec dialog


CGestRec::CGestRec(CWnd* pParent /*=NULL*/)
	: CDialog(CGestRec::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGestRec)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGestRec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGestRec)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGestRec, CDialog)
	//{{AFX_MSG_MAP(CGestRec)
	ON_BN_CLICKED(IDC_RTRAIN, OnRtrain)
	ON_BN_CLICKED(IDC_RRECO, OnRreco)
	ON_LBN_SELCHANGE(IDC_GESTLIST, OnSelchangeGestlist)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RNOTHING, OnRnothing)
	ON_BN_CLICKED(IDC_BCLEARGEST, OnBcleargest)
	ON_BN_CLICKED(IDC_BSAVEGEST, OnBsavegest)
	ON_BN_CLICKED(IDC_BLOADGEST, OnBloadgest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGestRec message handlers

void CGestRec::OnRtrain() 
{
    STEREOGRAPP(app);
    app->m_findHand.SetTask(GR_TRAIN);
}

void CGestRec::OnRreco() 
{
    STEREOGRAPP(app);
    app->m_findHand.SetTask(GR_RECOGNIZE);
}

void CGestRec::OnSelchangeGestlist() 
{
    STEREOGRAPP(app);
    CListBox* pList = (CListBox*)GetDlgItem(IDC_GESTLIST);
    int sel = pList->GetCurSel();
    string buffer("", pList->GetTextLen(sel));
    pList->GetText(sel, buffer.begin());
    app->m_findHand.SetGestureName(buffer);
}

BOOL CGestRec::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CListBox* pList = (CListBox*)GetDlgItem(IDC_GESTLIST);
    pList->AddString("Ok");
    pList->AddString("Open");
    pList->AddString("Three");
    pList->AddString("Peace");
    pList->AddString("Point");
    pList->AddString("Thumb");
    pList->SetCurSel(0);

    CButton* pTrain = (CButton*)GetDlgItem(IDC_RTRAIN);
    pTrain->SetCheck(1);
    STEREOGRAPP(app);
    app->m_findHand.SetTask(GR_TRAIN);
    string buffer("", pList->GetTextLen(0));
    pList->GetText(0, buffer.begin());
    app->m_findHand.SetGestureName(buffer);

    ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGestRec::OnClose() 
{
    STEREOGRAPP(app);
    app->m_findHand.SetTask(GR_NOTHING);
    	
	CDialog::OnClose();
}

void CGestRec::UpdateStatus()
{
    STEREOGRAPP(app);
    int task = app->m_findHand.m_task;
    CStatic* pStatus = (CStatic*)GetDlgItem(IDC_GRINFO);
    CListBox* pList = (CListBox*)GetDlgItem(IDC_GESTLIST);
    int current = pList->GetCurSel();
    string recognized = app->m_findHand.GetRecognizedName();
    CString info;

    pList->GetText(current, info);
    string str = LPCTSTR(info);
    app->m_findHand.SetGestureName(str);

    switch(task)
    {
    case GR_TRAIN:
        if(!app->m_findHand.m_isCovMatCalculated[current])
            info.Format("Collected %d samples for training...", app->m_findHand.m_features[current].size());
        else
            info.Format("Collected all samples.");
        break;

    case GR_RECOGNIZE:
        if(recognized.empty())
        {
            info.Format("Not recognized.");
        }
        else
        {
            info.Format("Recognized as \"%s\".", recognized.c_str());
        }
        break;

    case GR_NOTHING:
        info = "Do nothing";
    }

    pStatus->SetWindowText(info);
    pStatus->Invalidate();
    pStatus->UpdateWindow();
    RECT rect;
    pStatus->GetWindowRect(&rect);
    ScreenToClient(&rect);
    InvalidateRect(&rect);
    UpdateWindow();
    ASSERT(iplGetErrStatus() >= 0);
}

void CGestRec::OnRnothing() 
{
    STEREOGRAPP(app)
    app->m_findHand.SetTask(GR_NOTHING);
}

void CGestRec::OnBcleargest() 
{
    CListBox* pList = (CListBox*)GetDlgItem(IDC_GESTLIST);
    int index = pList->GetCurSel();
    CString str;
    pList->GetText(index, str);
    string buffer = LPCTSTR(str);
    STEREOGRAPP(app)
    app->m_findHand.ClearGesture(buffer);
}

void CGestRec::OnBsavegest() 
{
    CFileDialog dlg(FALSE, 0, 0, OFN_OVERWRITEPROMPT, "Statis training set (*.pos)|*.pos");
    if(dlg.DoModal() == IDOK)
    {
        STEREOGRAPP(app)
        app->m_findHand.SaveGestures(dlg.GetPathName());
    }
}

void CGestRec::OnBloadgest() 
{
    CFileDialog dlg(TRUE, 0, 0, 0, "Statis training set (*.pos)|*.pos");
	if(dlg.DoModal() == IDOK)
    {
        STEREOGRAPP(app)
        app->m_findHand.LoadGestures(dlg.GetPathName());
    }
}
