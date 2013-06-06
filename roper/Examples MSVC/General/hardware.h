// hardware.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// hardware dialog

class hardware : public CDialog
{


// Construction
public:
	hardware(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(hardware)
	enum { IDD = IDD_HARDWARE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(hardware)
	public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int interfacetype;
	int ccdtype;
	int controltype;
	int ioaddtype;
	int interrupttype;
	int adctype;
	int readouttype;
	int controller_ok;
    int versiontype;        // controller version
	
	/* for defaults */
	double expos;

    CComboBox& Controller_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_CONTROL ); }
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
	CButton& IRQ_FTRadio()
        { return *(CButton*)GetDlgItem( IDC_FT ); }
	CButton& IRQ_FullRadio()
        { return *(CButton*)GetDlgItem( IDC_FULL ); }
    CComboBox& ControlVer_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_CONTROLVER ); }

	void SetComboCurSel(
				CComboBox *pComboCtrl,
				int CurrentValue
				);

	void SetDefaults ( );
	// Generated message map functions
	//{{AFX_MSG(hardware)
	afx_msg void OnSlow();
	virtual void OnOK();
	afx_msg void OnFast();
	afx_msg void OnSelchangeInterface();
	afx_msg void OnSelchangeControl();
	afx_msg void OnSelchangeCcd();
	afx_msg void OnSelchangeIoadd();
	afx_msg void OnSelchangeInterrupt();
	afx_msg void OnFt();
	afx_msg void OnFull();
	afx_msg void OnSelchangeControlver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
