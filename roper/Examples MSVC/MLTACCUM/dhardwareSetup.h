// dHardwareSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HardwareSetup dialog

class HardwareSetup : public CDialog
{
// Construction
public:
	HardwareSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(HardwareSetup)
	enum { IDD = IDD_HARDWARE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HardwareSetup)
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
    int versiontype;

		/* for defaults */
	int numframes;
	double expos;

	CComboBox& Controller_ComboBox()
		{ return *(CComboBox*)GetDlgItem( IDC_CONTROL ); }
	CComboBox& ControlVer_ComboBox()
		{ return *(CComboBox*)GetDlgItem( IDC_CONTROLVER ); }
	
	CComboBox& Detector_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_CCD ); }
	CComboBox& Interface_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_INTERFACE ); }
	CComboBox& IOAddress_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_IOADDR ); }
	CComboBox& IRQ_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_INTERUPT ); }
	CButton& IRQ_FastRadio()
        { return *(CButton*)GetDlgItem( IDC_ADCFAST ); }
	CButton& IRQ_SlowRadio()
        { return *(CButton*)GetDlgItem( IDC_ADCSLOW ); }
	CButton& IRQ_FTRadio()
        { return *(CButton*)GetDlgItem( IDC_FRAMETRANSFER ); }
	CButton& IRQ_FullRadio()
        { return *(CButton*)GetDlgItem( IDC_FULLFRAME ); }

	void SetComboCurSel(
				CComboBox *pComboCtrl,
				int CurrentValue
				);

	void SetDefaults ( );
	// Generated message map functions
	//{{AFX_MSG(HardwareSetup)
		afx_msg void OnSelchangeControl();
	afx_msg void OnAdcfast();
	afx_msg void OnAdcslow();
	afx_msg void OnFullframe();
	afx_msg void OnFrametransfer();
	afx_msg void OnSelchangeCcd2();
	afx_msg void OnSelchangeInterface();
	afx_msg void OnSelchangeIoaddr();
	afx_msg void OnSelchangeInterupt();
	virtual void OnOK();
	afx_msg void OnSelchangeControlver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
