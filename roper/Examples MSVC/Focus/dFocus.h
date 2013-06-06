// dFocus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdFocus dialog

class CdFocus : public CDialog
{
protected:
	int ExposUnits;							/* Seconds						*/
	int expos_factor, max_slide;			/* Maximum slider				*/
	double Roundoff;
	double Exposure;						/* Exposure in seconds			*/
	int offset;								/* Offset						*/
	int bitadjust;							/* Bin adjust					*/
	int initialize_flag;					/* TRUE/FALSE				*/
	double exp_temp;
	int pat_temp;
	int focustype;
	int pantype;
	int zoom;

	unsigned int error_code;				/* error codes returned to this */
	int controller_ok;						/* controller downloaded		*/

	/* for defaults */
	int interfacetype;				/* interface type	*/
	int ccdtype;					/* detecter type	*/
	int controltype;				/* controller		*/
	int ioaddtype;					/* i/o address		*/
	int interrupttype;				/* interrupt level	*/
	int adctype;					/* fast/slow ADC	*/
	int readouttype;				/* full frame/ FT	*/
    int versiontype;                /* controller version type */

// Construction
public:
	CdFocus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdFocus)
	enum { IDD = IDD_FOCUS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdFocus)
	public:
    virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSliderCtrl& ExposSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_EXPOSSLIDE ); }
	CSliderCtrl& OffsetSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_OFFSETSLIDE ); }
	CSliderCtrl& BinSlide()
    { return *(CSliderCtrl*)GetDlgItem( IDC_BINSLIDE ); }
	CButton& IRQ_X1Radio()
        { return *(CButton*)GetDlgItem( IDC_X1 ); }
	CButton& IRQ_X2Radio()
        { return *(CButton*)GetDlgItem( IDC_X2 ); }
	CButton& IRQ_X4Radio()
        { return *(CButton*)GetDlgItem( IDC_X4 ); }
	CButton& IRQ_TLRadio()
        { return *(CButton*)GetDlgItem( IDC_TLP ); }
	CButton& IRQ_TCRadio()
        { return *(CButton*)GetDlgItem( IDC_TCP ); }
	CButton& IRQ_TRRadio()
        { return *(CButton*)GetDlgItem( IDC_TRP ); }
	CButton& IRQ_CLRadio()
        { return *(CButton*)GetDlgItem( IDC_MLP ); }
	CButton& IRQ_CCRadio()
        { return *(CButton*)GetDlgItem( IDC_MCP ); }
	CButton& IRQ_CRRadio()
        { return *(CButton*)GetDlgItem( IDC_MRP ); }
	CButton& IRQ_BLRadio()
        { return *(CButton*)GetDlgItem( IDC_BLP ); }
	CButton& IRQ_BCRadio()
        { return *(CButton*)GetDlgItem( IDC_BCP ); }
	CButton& IRQ_BRRadio()
        { return *(CButton*)GetDlgItem( IDC_BRP ); }
	CButton& IRQ_BinRadio()
        { return *(CButton*)GetDlgItem( IDC_BIN ); }
	CButton& IRQ_DecimateRadio()
        { return *(CButton*)GetDlgItem( IDC_DECIMATE ); }
	// Generated message map functions
	//{{AFX_MSG(CdFocus)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeExposedit();
	virtual void OnOK();
	afx_msg void OnRun();
	afx_msg void OnStop();
	afx_msg void OnBin();
	afx_msg void OnX1();
	afx_msg void OnX2();
	afx_msg void OnTcp();
	afx_msg void OnTlp();
	afx_msg void OnTrp();
	afx_msg void OnBcp();
	afx_msg void OnBlp();
	afx_msg void OnBrp();
	afx_msg void OnMcp();
	afx_msg void OnMlp();
	afx_msg void OnMrp();
	afx_msg void OnDecimate();
	afx_msg void OnX4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
