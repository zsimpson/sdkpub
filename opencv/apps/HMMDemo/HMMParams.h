#if !defined(AFX_HMMPARAMS_H__068DCF75_4415_4660_BF6A_C2ABF9EDD7E6__INCLUDED_)
#define AFX_HMMPARAMS_H__068DCF75_4415_4660_BF6A_C2ABF9EDD7E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HMMParams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHMMParams dialog

class CHMMParams : public CPropertyPage
{
	DECLARE_DYNCREATE(CHMMParams)

// Construction
public:
	CHMMParams();
	~CHMMParams();

// Dialog Data
	//{{AFX_DATA(CHMMParams)
	enum { IDD = IDD_HMMPARAM_DLG };
	int		m_NumMix;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHMMParams)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHMMParams)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_States[8];
	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMMPARAMS_H__068DCF75_4415_4660_BF6A_C2ABF9EDD7E6__INCLUDED_)
