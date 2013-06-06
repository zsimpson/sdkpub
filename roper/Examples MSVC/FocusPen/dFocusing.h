// dFocusing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdFocusing dialog

class CdFocusing : public CDialog
{

// Construction
public:
	CdFocusing(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdFocusing)
	enum { IDD = IDD_FOCUS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdFocusing)
   	public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int ExposUnits;
	int expos_factor, max_slide;
	double Roundoff;
	double Exposure;
    int luttype;
    int initialize_flag;
    int controller_ok;
    unsigned int error_code;

	/* for defaults */
	int interfacetype;				/* interface type	*/
	int ccdtype;					/* detecter type	*/
	int controltype;				/* controller		*/
	int ioaddtype;					/* i/o address		*/
	int interrupttype;				/* interrupt level	*/
	int adctype;					/* fast/slow ADC	*/
	int readouttype;				/* full frame/ FT	*/
    int versiontype;                /* controller version */

    CSliderCtrl& ExposSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_EXPOSSLIDE ); }
	CComboBox& LUT_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_LUTCOMBO ); }

	void SetComboCurSel(
				CComboBox *pComboCtrl,
				int CurrentValue
				);

	void SetDefaults ( );
	// Generated message map functions
	//{{AFX_MSG(CdFocusing)
   	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeLutcombo();
	afx_msg void OnChangeExposedit();
	virtual void OnOK();
	afx_msg void OnRun();
	virtual void OnCancel();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
