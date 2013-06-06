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
//M*/// HMMDemo.h : main header file for the HMMDEMO application
//

#if !defined(AFX_HMMDEMO_H__B596EB47_5043_4376_923B_701FBD3CD8F0__INCLUDED_)
#define AFX_HMMDEMO_H__B596EB47_5043_4376_923B_701FBD3CD8F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "HMMParams.h"	// Added by ClassView
#include "SamplingParams.h"	
#include "MiscParams.h"	


/////////////////////////////////////////////////////////////////////////////
// CHMMDemoApp:
// See HMMDemo.cpp for the implementation of this class
//

class CHMMDemoApp : public CWinApp
{
public:
	void SaveSettings();

	CHMMDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMMDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHMMDemoApp)
	afx_msg void OnAppAbout();
    afx_msg void OnFileOpen();
	afx_msg void OnSaveConfig();
	afx_msg void OnLoadConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	
public:
	int LoadConfig(const char* filename, bool synchronize_base );
    int SaveConfig(const char* filename ); 
    void OnSettings();
    CHMMParams* m_dlgHMMParams;
    CSamplingParams* m_dlgSamplingParams;
    CMiscParams* m_dlgMiscParams;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMMDEMO_H__B596EB47_5043_4376_923B_701FBD3CD8F0__INCLUDED_)
