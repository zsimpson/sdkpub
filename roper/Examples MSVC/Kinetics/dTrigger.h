// dTrigger.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdTrigger dialog

class CdTrigger : public CDialog
{
// Construction
public:
	CdTrigger(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdTrigger)
	enum { IDD = IDD_ACQUIRE };
	CButton	m_RunButton;
	CString	m_TempStatusText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdTrigger)
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
    int triggertype;
    int initialize_flag;
    int controller_ok;
    unsigned int error_code;

	/* for defaults */
	BOOL nvram;						/* Use NVRAM as default */
	int interfacetype;				/* interface type	*/
	int ccdtype;					/* detecter type	*/
	int controltype;				/* controller		*/
	int ioaddtype;					/* i/o address		*/
	int interrupttype;				/* interrupt level	*/
	int adctype;					/* fast/slow ADC	*/

    CSliderCtrl& ExposSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_EXPOSSLIDE ); }
	CComboBox& Trigger_ComboBox()
        { return *(CComboBox*)GetDlgItem( IDC_TRIGGERCOMBO ); }

	void SetComboCurSel(
				CComboBox *pComboCtrl,
				int CurrentValue
				);

	void SetDefaults ( );

	// Generated message map functions
	//{{AFX_MSG(CdTrigger)
   	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeExposedit();
	afx_msg void OnSelchangeTriggercombo();
	afx_msg void OnRun();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
