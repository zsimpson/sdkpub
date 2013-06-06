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
//M*/// HawkDoc.h : interface of the CHawkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HAWKDOC_H__6FFD53AF_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
#define AFX_HAWKDOC_H__6FFD53AF_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDSWnd;
class CHawkView;
class CLogView;
class CHawkDoc : public CDocument
{
friend unsigned long __stdcall _StopDS(void* doc);

protected: // create from serialization only
	CHawkDoc();
	DECLARE_DYNCREATE(CHawkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHawkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
    virtual BOOL IsModified();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_dsSimpleMode;
	HANDLE m_readMutex;
	BOOL IsRunning();
	void ClearTransformFunction();
	BOOL ParseTransformFunction();
	HANDLE m_hThread;
    HANDLE m_hScriptExec;
    HANDLE m_hScriptMutex;
    volatile BOOL m_execState;
	BOOL Initialize();
	CLogView* GetLogView();
	char* m_pScript;
	CStringArray m_parsedStrings;
	CHawkView* GetHawkView();
	virtual ~CHawkDoc();
	void ParseString();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHawkDoc)
	afx_msg void OnRun();
	afx_msg void OnUpdateRun(CCmdUI* pCmdUI);
	afx_msg void OnRunds();
	afx_msg void OnUpdateRunds(CCmdUI* pCmdUI);
	afx_msg void OnStopds();
	afx_msg void OnUpdateStopds(CCmdUI* pCmdUI);
	afx_msg void OnOptionsConfiguration();
   	afx_msg void OnOptionsColors();
	afx_msg void OnUpdateOptionsColors(CCmdUI* pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnEicQwatch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_tempName;
//	CDSWnd* m_DSWnd;
	CHawkView* m_pHawkView;
	CLogView* m_pLogView;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HAWKDOC_H__6FFD53AF_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
