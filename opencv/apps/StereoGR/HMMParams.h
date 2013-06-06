#if !defined(AFX_HMMPARAMS_H__C161F026_5331_4346_800B_EB1F2165E09D__INCLUDED_)
#define AFX_HMMPARAMS_H__C161F026_5331_4346_800B_EB1F2165E09D__INCLUDED_

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
	enum { IDD = IDD_HMM_SETTINGS };
	int		m_num_mix;
	int		m_num_states;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHMMParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHMMParams)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMMPARAMS_H__C161F026_5331_4346_800B_EB1F2165E09D__INCLUDED_)
