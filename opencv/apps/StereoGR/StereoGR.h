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
//M*/// StereoGR.h : main header file for the STEREOGR application
//

#if !defined(AFX_STEREOGR_H__2B3C951D_D27D_4C2E_983A_8EC824753946__INCLUDED_)
#define AFX_STEREOGR_H__2B3C951D_D27D_4C2E_983A_8EC824753946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "DGProp.h"	
#include "FindHandCtl.h"
#include "GestMan.h"	
#include "PGControl.h"
#include "PTOptions.h"
#include "HMMParams.h"
#include "DGStat.h"
#include "GROptions.h"
#include "DynGestServer.h"
	

/////////////////////////////////////////////////////////////////////////////
// CStereoGRApp:
// See StereoGR.cpp for the implementation of this class
//
#define VIEWS_COUNT ID_VIEW12 - ID_VIEW1 + 1
#define IS_PTGREY_DATATYPE(x) ((x) >= 0 && (x) < PG_IMAGE_MAX)
#define GR_MASK_VIEW PT_POINTCLOUD_IMAGE + 1
#define GR_MAGICCUBE GR_MASK_VIEW + 1

class CStereoGRView;
class CStereoGRApp : public CWinApp
{
private:
	BOOL m_isNewData;
	CGestRec m_gestRec;
	CDGProp* m_dgProp;
    CStereoGRView* m_views[VIEWS_COUNT];
    int m_viewIds[VIEWS_COUNT];
	CString m_modulePath;
	int m_docType;

	void InitModulePath();
	void CreatePropertyPages();
    

    
public:
	BOOL m_isClosingView;
	void Zoom();
	void Segment();
	HANDLE m_glThread;
	vector<POINT> m_TopLefts;
	vector<POINT> m_TopLefts3D;
    CDynGestServer m_dgServer;

	CGROptions* m_grOptions;
	CPTOptions* m_ptOptions;
    CHMMParams* m_hmmParams;
    CDGStat*    m_dgStat;

    BOOL LoadSettings();
    BOOL SaveSettings();
	BOOL IsNewData();
	void ValidateData(BOOL flag = TRUE);
	BOOL m_doRecog;
//	void SetImage(int dataType, IplImage* image, BOOL copy = FALSE);
	IplImage* GetImage(int dataType);
	void Update();
	void CloseView(int dataType);
	void SetView(int dataType, CStereoGRView* pView);
    CStereoGRView* GetView(int dataType) const {return m_views[dataType];};
    int* GetViewIDs() const {return (int*)m_viewIds;};
	void OpenView(int dataType);
	void Process();
    CFindHandCtrl m_findHand;
	void SetDocType(int docType);
	int GetDocType();
	CStereoGRApp();
    ~CStereoGRApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStereoGRApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CStereoGRApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnView();
	afx_msg void OnPtProp();
	afx_msg void OnPtWhitebalance();
	afx_msg void OnPtoffline();
	afx_msg void OnCaptureBack();
	afx_msg void OnRungestrec();
	afx_msg void OnSettings();
	afx_msg void OnTrain();
	afx_msg void OnSaveDynamicGestures();
	afx_msg void OnLoadDynamicGestures();
	afx_msg void OnSaveBase();
	afx_msg void OnLoadBase();
	afx_msg void OnRecogFileDg();
	afx_msg void OnDeleteHmm();
	afx_msg void OnRemoveAllDg();
	afx_msg void OnUpdateRungestrec(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define STEREOGRAPP(x) CStereoGRApp* (x) = (CStereoGRApp*)AfxGetApp();

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEREOGR_H__2B3C951D_D27D_4C2E_983A_8EC824753946__INCLUDED_)
