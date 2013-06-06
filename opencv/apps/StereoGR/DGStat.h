#if !defined(AFX_DGSTAT_H__43F2CA54_96FE_48FC_B85A_A1B380F66C58__INCLUDED_)
#define AFX_DGSTAT_H__43F2CA54_96FE_48FC_B85A_A1B380F66C58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DGStat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDGStat dialog

class CDGStat : public CPropertyPage
{
	DECLARE_DYNCREATE(CDGStat)

// Construction
public:
	void Update();
	CDGStat();
	~CDGStat();

// Dialog Data
	//{{AFX_DATA(CDGStat)
	enum { IDD = IDD_GEST_STAT };
	CListBox	m_name_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDGStat)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDGStat)
	afx_msg void OnSelchangeDgstatList();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteDg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DGSTAT_H__43F2CA54_96FE_48FC_B85A_A1B380F66C58__INCLUDED_)
