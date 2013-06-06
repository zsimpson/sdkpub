// dExposure.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdExposure dialog

class CdExposure : public CDialog
{
// Construction
protected:
int ExposUnits;
int expos_factor, max_slide;
int numframes;  // number of frames in image
double Roundoff;
double Exposure;

// for defaults
int interfacetype;
int ccdtype;
int controltype;
int iodatatype;
int interruptype;
int adctype;
int readouttype;
int versiontype;


public:
	CdExposure(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdExposure)
	enum { IDD = IDD_EXPOS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdExposure)
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CSliderCtrl& ExposSlide()
	{ return *(CSliderCtrl*)GetDlgItem( IDC_EXPOSURE ); }
	
	// Generated message map functions
	//{{AFX_MSG(CdExposure)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeExposrdout();
	afx_msg void OnChangeFramesrdout();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
