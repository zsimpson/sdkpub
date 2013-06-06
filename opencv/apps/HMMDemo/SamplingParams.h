#if !defined(AFX_SAMPLINGPARAMS_H__A2A6E584_4D77_484D_8F10_EE88ABC4EC53__INCLUDED_)
#define AFX_SAMPLINGPARAMS_H__A2A6E584_4D77_484D_8F10_EE88ABC4EC53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SamplingParams.h : header file
//

#include "Cv.h"

/////////////////////////////////////////////////////////////////////////////
// CSamplingParams dialog

class CSamplingParams : public CPropertyPage
{
	DECLARE_DYNCREATE(CSamplingParams)

// Construction
public:
	CSamplingParams();
	~CSamplingParams();

// Dialog Data
	//{{AFX_DATA(CSamplingParams)
	enum { IDD = IDD_OBS_PARAMS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSamplingParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSamplingParams)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    CvSize m_delta;
    CvSize m_obsSize;
    CvSize m_dctSize;     

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLINGPARAMS_H__A2A6E584_4D77_484D_8F10_EE88ABC4EC53__INCLUDED_)
