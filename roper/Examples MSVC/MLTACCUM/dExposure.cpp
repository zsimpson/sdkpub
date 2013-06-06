// dExposure.cpp : implementation file
//

#include "stdafx.h"
#include "mltaccum.h"
#include "dExposure.h"
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
// CdExposure dialog


CdExposure::CdExposure(CWnd* pParent /*=NULL*/)
	: CDialog(CdExposure::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdExposure)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdExposure::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdExposure)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdExposure, CDialog)
	//{{AFX_MSG_MAP(CdExposure)
	ON_EN_CHANGE(IDC_EXPOSRDOUT, OnChangeExposrdout)
	ON_EN_CHANGE(IDC_FRAMESRDOUT, OnChangeFramesrdout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdExposure message handlers

BOOL CdExposure::OnInitDialog()
{
            // Load limits into sliders    
    CString DisplayText;

	ExposUnits = 3;

	ReadDefaults( &Exposure, &numframes, &controltype,
					&ccdtype, &interfacetype, &iodatatype, &interruptype,
					&adctype, &readouttype, &versiontype );


    SetExposSliderRange( ExposUnits, &expos_factor, &Roundoff, 
						&max_slide, &ExposSlide() );
    SetExposSliderPos( &Exposure, expos_factor, Roundoff, 
						max_slide, &ExposSlide() );

    DisplayText.Format( "%g", Exposure );
    SetDlgItemText( IDC_EXPOSRDOUT, DisplayText );

    DisplayText.Format( "%d", numframes );
    SetDlgItemText( IDC_FRAMESRDOUT, DisplayText );


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnHScroll
//
/////////////////////////////////////////////////////////////////////////////

void CdExposure::OnHScroll
    (
    UINT        /* nSBCode */,          // Get rid of compiler warnings
    UINT        /* nPos */,             // Get rid of compiler warnings
    CScrollBar* pScrollBar
    )
{
    INT     SliderID;
    INT     SlidePos;
    CString DisplayText;

    CSliderCtrl *pSlider = (CSliderCtrl *)pScrollBar;

    SliderID = pSlider->GetDlgCtrlID();
    SlidePos = pSlider->GetPos();

    if( SliderID == IDC_EXPOSURE )
    {
            // Set the new value in the edit box
            // Note: Exposure is not set until SET button is hit
        Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
        DisplayText.Format( "%g", Exposure );
        SetDlgItemText( IDC_EXPOSRDOUT, DisplayText );
    }
}

void CdExposure::OnChangeExposrdout() 
{
CString temp_str;
    SHORT   num_chars;
    double  tmp_expos;

    num_chars = (SHORT)GetDlgItemText( IDC_EXPOSRDOUT, temp_str );

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

//sets the number of frames to be collected
////////////////////////////////////////////
void CdExposure::OnChangeFramesrdout() 
{
	CString temp_str;
    SHORT   num_chars;
    double  tmp_frames;

    num_chars = (SHORT)GetDlgItemText( IDC_FRAMESRDOUT, temp_str );

    if( num_chars > 0 )
    {
        char *end_str;

        tmp_frames = strtod( temp_str, &end_str );

        numframes = (int)tmp_frames;
               
    }
    else
    {
        numframes = 1;
       		
    }
}

void CdExposure::OnOK() 
{
	int controller_ok;
	unsigned int error_code;

	controller_ok = PICM_SetExposure((double)Exposure, &error_code);
	
	WriteDefaults( Exposure,numframes, controltype,
			ccdtype, interfacetype, iodatatype, interruptype,
			adctype, readouttype, versiontype );


	CDialog::OnOK();
}
