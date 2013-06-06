// dExSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdExSetup dialog

class CdExSetup : public CDialog
{

protected:
	int ExposUnits;							/* Seconds						*/
	int expos_factor, max_slide;			/* Maximum slider				*/
	double Roundoff;
	double Exposure;						/* Exposure in seconds			*/
	int initialize_flag;					/* TRUE/FALSE				*/
	double exp_temp;
	int pat_temp;
	unsigned int error_code;				/* error codes returned to this */
	int controller_ok;						/* controller downloaded		*/
	int xstart, ystart;						/* roi start */
	int xend, yend;							/* roi end   */

	/* for defaults */
	int interfacetype;				/* interface type	*/
	int ccdtype;					/* detecter type	*/
	int controltype;				/* controller		*/
	int ioaddtype;					/* i/o address		*/
	int interrupttype;				/* interrupt level	*/
	int adctype;					/* fast/slow ADC	*/
	int readouttype;				/* full frame/ FT	*/
    int versiontype;                /* controller version */

// Construction
public:
	CdExSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdExSetup)
	enum { IDD = IDD_EXPERIMENT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdExSetup)
	public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSliderCtrl& ExposSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_EXPOSSLIDE ); }	// Generated message map functions
	//{{AFX_MSG(CdExSetup)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeExposedit();
	virtual void OnOK();
	afx_msg void OnChangeYstart();
	afx_msg void OnChangeXend();
	afx_msg void OnChangeYend();
	afx_msg void OnChangeXstart();
	//}}AFX_MSG

	
	DECLARE_MESSAGE_MAP()

};
