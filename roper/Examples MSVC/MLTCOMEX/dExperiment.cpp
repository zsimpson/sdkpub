// dExperiment.cpp : implementation file
//

#include "stdafx.h"
#include "Mltcomex.h"
#include "dExperiment.h"
#include "exposslider.h"
#include "initexp.h"

extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdExperiment dialog


CdExperiment::CdExperiment(CWnd* pParent /*=NULL*/)
	: CDialog(CdExperiment::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdExperiment)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdExperiment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdExperiment)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdExperiment, CDialog)
	//{{AFX_MSG_MAP(CdExperiment)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EXPOSEDIT, OnChangeExposedit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdExperiment message handlers
BOOL CdExperiment::OnInitDialog()
{
            // Load limits into sliders    
    CString DisplayText;

	ExposUnits = 3;

	ReadDefaults( &Exposure, &controltype,
					&ccdtype, &interfacetype, &ioaddtype, &interrupttype,
					&adctype, &readouttype, &versiontype );


    SetExposSliderRange( ExposUnits, &expos_factor, &Roundoff, 
						&max_slide, &ExposSlide() );
    SetExposSliderPos( &Exposure, expos_factor, Roundoff, 
						max_slide, &ExposSlide() );

    DisplayText.Format( "%g", Exposure );
    SetDlgItemText( IDC_EXPOSEDIT, DisplayText );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnHScroll
//
/////////////////////////////////////////////////////////////////////////////

void CdExperiment::OnHScroll
    (
    UINT        /* nSBCode */,         // Get rid of compiler warnings
    UINT        /* nPos */,            // Get rid of compiler warnings
    CScrollBar* pScrollBar
    )
{
    INT     SliderID;
    INT     SlidePos;
    CString DisplayText;

    CSliderCtrl *pSlider = (CSliderCtrl *)pScrollBar;

    SliderID = pSlider->GetDlgCtrlID();
    SlidePos = pSlider->GetPos();

    if( SliderID == IDC_EXPOSSLIDE )
    {
            // Set the new value in the edit box
            // Note: Exposure is not set until SET button is hit
        Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
        DisplayText.Format( "%g", Exposure );
        SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
    }
}

/////////////////////////////////////////////////////////////////
//
//				Change in the Exposure Edit Box
//
//
/////////////////////////////////////////////////////////////////

void CdExperiment::OnChangeExposedit() 
{
    CString temp_str;
    SHORT   num_chars;
    double  tmp_expos;

    num_chars = (SHORT)GetDlgItemText( IDC_EXPOSEDIT, temp_str );

    if( num_chars > 0 )
    {
        char *end_str;

        tmp_expos = strtod( temp_str, &end_str );

        Exposure = tmp_expos;
        SetExposSliderPos( &Exposure, expos_factor, Roundoff,
                           max_slide, &ExposSlide() );
        
    }
    else
    {
        Exposure = 0.0;
        SetExposSliderPos( &Exposure, expos_factor, Roundoff,
                           max_slide, &ExposSlide() );
		
    }
}


void CdExperiment::OnOK() 
{
	int controller_ok;
	unsigned int error_code;

	controller_ok = PICM_SetExposure((double)Exposure, &error_code);
	
	WriteDefaults( Exposure, controltype,
			ccdtype, interfacetype, ioaddtype, interrupttype,
			adctype, readouttype, versiontype );

	CDialog::OnOK();
}
