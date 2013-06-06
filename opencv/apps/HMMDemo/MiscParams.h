#if !defined(AFX_MISCPARAMS_H__6D476418_B4C1_499A_BA4F_B49A0938741E__INCLUDED_)
#define AFX_MISCPARAMS_H__6D476418_B4C1_499A_BA4F_B49A0938741E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiscParams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMiscParams dialog

class CMiscParams : public CPropertyPage
{
	DECLARE_DYNCREATE(CMiscParams)

// Construction
public:
	CMiscParams();
	~CMiscParams();

// Dialog Data
	//{{AFX_DATA(CMiscParams)
	enum { IDD = IDD_MISC_PARAM_DLG };
	int		m_FixedWidth;
	int		m_FixedHeight;
	BOOL	m_useHeight;
	BOOL	m_useWidth;
	BOOL	m_SuppressIntensity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMiscParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMiscParams)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISCPARAMS_H__6D476418_B4C1_499A_BA4F_B49A0938741E__INCLUDED_)
