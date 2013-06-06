// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnExperimentHardwaresetup();
	afx_msg void OnExperimentExperimentsetup();
	afx_msg void OnUpdateHardwareUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExSetupUpdate(CCmdUI* pCmdUI);
	afx_msg void OnExperimentAcquireexperiment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
// MenuItem Enable Flags
public:
	static BOOL m_efID_EXPERIMENT_EXPERSETUP;
	static BOOL m_efID_EXPERIMENT_ACQUIRE;
};

/////////////////////////////////////////////////////////////////////////////
