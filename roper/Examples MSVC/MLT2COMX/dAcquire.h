// dAcquire.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdAcquire dialog

class CdAcquire : public CDialog
{
// Construction

protected:

public:
	CdAcquire(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdAcquire)
	enum { IDD = IDD_ACQUIRE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdAcquire)	public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CdAcquire)
	afx_msg void OnRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
