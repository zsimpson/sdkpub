// dExSetup.cpp : implementation file
//

#include "stdafx.h"
#include "Imaging.h"
#include "dExSetup.h"
#include "slider.h"
#include "initexp.h"
#include "mainfrm.h"

extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
#include "pifcsfcn.h"
#include "pifcsdef.h"
#include "pimltfcn.h"
#include "piimgdef.h"
#include "piimgfcn.h"
#include "pitimdef.h"
#include "pitimfcn.h"
#include "pionlfcn.h"
#include "pifcsfcn.h"
#include "pifcsdef.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdExSetup dialog


CdExSetup::CdExSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CdExSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdExSetup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdExSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdExSetup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdExSetup, CDialog)
	//{{AFX_MSG_MAP(CdExSetup)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EXPOSEDIT, OnChangeExposedit)
	ON_EN_CHANGE(IDC_YSTART, OnChangeYstart)
	ON_EN_CHANGE(IDC_XEND, OnChangeXend)
	ON_EN_CHANGE(IDC_YEND, OnChangeYend)
	ON_EN_CHANGE(IDC_XSTART, OnChangeXstart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdExSetup message handlers

BOOL CdExSetup::OnInitDialog()
{
            // Load limits into sliders
	ExposUnits = 3;							/* seconds				*/
    CString DisplayText;					/* String to Display	*/

	/* Initialize before download */
	ReadDefaults(&Exposure, &xstart, &ystart, &xend, &yend, &controltype,
					&ccdtype, &interfacetype, &ioaddtype, &interrupttype,
					&adctype, &readouttype, &versiontype );
	PICM_Set_Temperature(-20.0);

	/* Initalize sliders */
    SetExposSliderRange( ExposUnits, &expos_factor, &Roundoff, 
						&max_slide, &ExposSlide() );
    SetExposSliderPos( &Exposure, expos_factor, Roundoff, 
						max_slide, &ExposSlide() );

	DisplayText.Format( "%g", Exposure );
	SetDlgItemText( IDC_EXPOSEDIT, DisplayText );

	DisplayText.Format( "%d", xstart );
	SetDlgItemText( IDC_XSTART, DisplayText );
	DisplayText.Format( "%d", ystart );
	SetDlgItemText( IDC_YSTART, DisplayText );
	DisplayText.Format( "%d", xend );
	SetDlgItemText( IDC_XEND, DisplayText );
	DisplayText.Format( "%d", yend );
	SetDlgItemText( IDC_YEND, DisplayText );


	return TRUE;
}

void CdExSetup::OnHScroll
    (
    UINT        /* nSBCode */,          // Get rid of compiler warnings
    UINT        /* nPos */,             // Get rid of compiler warnings
    CScrollBar* pScrollBar
    )
{
    INT     SliderID;
    INT     SlidePos;

    CSliderCtrl *pSlider = (CSliderCtrl *)pScrollBar;

    SliderID = pSlider->GetDlgCtrlID();
    SlidePos = pSlider->GetPos();
	CString DisplayText;					/* String to Display	*/
	
	switch (SliderID)
	{
		case IDC_EXPOSSLIDE:
            // Set the new value in the edit box
			Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
			DisplayText.Format( "%g", Exposure );
			SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
			break;
    }
	
	PICM_Set_Exposure_Online( (double) Exposure, ExposUnits);
}

/////////////////////////////////////////////////////////////////
//
//				Change in the Exposure Edit Box
//
/////////////////////////////////////////////////////////////////

void CdExSetup::OnChangeExposedit() 
{
    CString temp_str;
    SHORT   num_chars;
    double  tmp_expos;
	CString DisplayText;

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


void CdExSetup::OnOK()
{
	long buffer_size;
    static HANDLE hglb;
	static void *lpvBuffer;

	/* Set up exposure, bit adjust, offset, roi, before starting the controller */
	controller_ok = PICM_SetExposure(Exposure, &error_code);
	if (controller_ok)
	{
		controller_ok = PICM_SetROI( xstart, ystart,
                                     xend,
                                     yend,
                                     1, 1,
                                     &error_code);
		PICM_Set_AutoStop(1);
			PICM_Set_RS170_enable(TRUE);
		/* write defaults */
		WriteDefaults(Exposure, xstart, ystart, xend, yend, controltype,
				ccdtype, interfacetype, ioaddtype, interrupttype,
				adctype, readouttype, versiontype );
		
		buffer_size = PICM_SizeNeedToAllocate();
        hglb = GlobalAlloc(GPTR, buffer_size );
        lpvBuffer = (void*) GlobalLock(hglb);

		controller_ok = PICM_Initialize_System(
									lpvBuffer,
                                    &error_code);
	}
	CMainFrame::m_efID_EXPERIMENT_ACQUIRE = TRUE;
	CDialog::OnOK();
}

void CdExSetup::OnChangeYstart() 
{
	int num_chars;
	char *end_str;
    double tmp_roi;
	CString temp_str;
    CString DisplayText;					/* String to Display	*/


	num_chars = (SHORT)GetDlgItemText( IDC_YSTART, temp_str );

	tmp_roi = strtod( temp_str, &end_str );
    ystart = (int)tmp_roi;

	if (ystart>PICM_Get_sensor_y ())
	{
		ystart = PICM_Get_sensor_y () - 1;
		DisplayText.Format( "%d", ystart );
		SetDlgItemText( IDC_YSTART, DisplayText );
	}
	if (ystart<1)
	{
		ystart = 1;
		DisplayText.Format( "%d", ystart );
		SetDlgItemText( IDC_YSTART, DisplayText );
	}
}

void CdExSetup::OnChangeXend() 
{
	int num_chars;
	char *end_str;
    double tmp_roi;
	CString temp_str;
    CString DisplayText;					/* String to Display	*/


	num_chars = (SHORT)GetDlgItemText( IDC_XEND, temp_str );

	tmp_roi = strtod( temp_str, &end_str );
    xend = (int)tmp_roi;
	
	if (xend>PICM_Get_sensor_x ())
	{
		xend = PICM_Get_sensor_x ();
		DisplayText.Format( "%d", xend );
		SetDlgItemText( IDC_XEND, DisplayText );
	}
	if (xend<2)
	{
		xend = 2;
		DisplayText.Format( "%d", xend );
		SetDlgItemText( IDC_XEND, DisplayText );
	}
}

void CdExSetup::OnChangeYend() 
{
	int num_chars;
	char *end_str;
    double tmp_roi;
	CString temp_str;
    CString DisplayText;					/* String to Display	*/

	num_chars = (SHORT)GetDlgItemText( IDC_YEND, temp_str );

	tmp_roi = strtod( temp_str, &end_str );
    yend = (int)tmp_roi;	

	if (yend>PICM_Get_sensor_y ())
	{
		yend = PICM_Get_sensor_y ();
		DisplayText.Format( "%d", yend );
		SetDlgItemText( IDC_YEND, DisplayText );
	}
	else if (yend<2)
	{
		yend = 2;
		DisplayText.Format( "%d", yend );
		SetDlgItemText( IDC_YEND, DisplayText );
	}
}

void CdExSetup::OnChangeXstart() 
{
	int num_chars;
	char *end_str;
    double tmp_roi;
	CString temp_str;
    CString DisplayText;					/* String to Display	*/


	num_chars = (SHORT)GetDlgItemText( IDC_XSTART, temp_str );

	tmp_roi = strtod( temp_str, &end_str );
    xstart = (int)tmp_roi;	
	
	if (xstart>PICM_Get_sensor_x ())
	{
		xstart = PICM_Get_sensor_x () - 1;
		DisplayText.Format( "%d", xstart );
		SetDlgItemText( IDC_XSTART, DisplayText );
	}
	if (xstart<1)
	{
		xstart = 1;
		DisplayText.Format( "%d", xstart );
		SetDlgItemText( IDC_XSTART, DisplayText );
	}
}
