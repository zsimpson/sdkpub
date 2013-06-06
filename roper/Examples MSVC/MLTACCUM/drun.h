// drun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdrun dialog

class Cdrun : public CDialog
{
// Construction
public:
	Cdrun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdrun)
	enum { IDD = IDD_RUNDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdrun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int numframes;

	// Generated message map functions
	//{{AFX_MSG(Cdrun)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
