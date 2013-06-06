// dSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdSetup dialog

class CdSetup : public CDialog
{
// Construction
protected:
	
	int ExposUnits;
	int expos_factor, max_slide;
	double Roundoff;
	double Exposure;

	/* for defaults */
	int interfacetype;				/* interface type	*/
	int ccdtype;					/* detecter type	*/
	int controltype;				/* controller		*/
	int ioaddtype;					/* i/o address		*/
	int interrupttype;				/* interrupt level	*/
	int adctype;					/* fast/slow ADC	*/
	int readouttype;				/* full frame/ FT	*/
    int versiontype;                /* controller version number */

public:
	CdSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdSetup)
	enum { IDD = IDD_EXPERIMENT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdSetup)
    public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

    CSliderCtrl& ExposSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_EXPOSSLIDE ); }

	// Generated message map functions
	//{{AFX_MSG(CdSetup)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeExposedit();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
