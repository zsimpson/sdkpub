// dHardware.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdHardware dialog

class CdHardware : public CDialog
{
// Construction
public:
	CdHardware(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdHardware)
	enum { IDD = IDD_HARDWARE };
	CComboBox	m_IOADD_ComboBox;
	CComboBox	m_INTERRUPT_ComboBox;
	CComboBox	m_INTERFACE_ComboBox;
	CButton	m_SLOW_Button;
	CComboBox	m_CCD_ComboBox;
	BOOL nvram;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdHardware)
    public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int interfacetype;
	int ccdtype;
	int ioaddtype;
	int interrupttype;
	int adctype;
	int controller_ok;
	
	/* for defaults */
	double expos;
    int triggertype;

	CComboBox& Detector_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_CCD ); }
	CComboBox& Interface_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_INTERFACE ); }
	CComboBox& IOAddress_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_IOADD ); }
	CComboBox& IRQ_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_INTERRUPT ); }
	CButton& IRQ_FastRadio()
        { return *(CButton*)GetDlgItem( IDC_FAST ); }
	CButton& IRQ_SlowRadio()
        { return *(CButton*)GetDlgItem( IDC_SLOW ); }

    void SetComboCurSel(
				CComboBox *pComboCtrl,
				int CurrentValue
				);

	void SetDefaults ( );

	// Generated message map functions
	//{{AFX_MSG(CdHardware)
	afx_msg void OnSlow();
	afx_msg void OnFast();
	afx_msg void OnSelchangeCcd();
	afx_msg void OnSelchangeInterface();
	afx_msg void OnSelchangeIoadd();
	afx_msg void OnSelchangeInterrupt();
	virtual void OnOK();
	afx_msg void OnNvramChk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
