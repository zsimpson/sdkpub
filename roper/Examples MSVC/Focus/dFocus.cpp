// dFocus.cpp : implementation file
//

#include "stdafx.h"
#include "Focus.h"
#include "dFocus.h"
#include "slider.h"
#include "initexp.h"

extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
#include "pimltfcn.h"
#include "piimgdef.h"
#include "piimgfcn.h"
#include "pitimdef.h"
#include "pitimfcn.h"
#include "pifcsdef.h"
#include "pifcsfcn.h"
#include "pionlfcn.h"
}

#define SKIP_Nth_ROW	0x01
int SetMultiple_ROIs(int Mode, int numberskip);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdFocus dialog


CdFocus::CdFocus(CWnd* pParent /*=NULL*/)
	: CDialog(CdFocus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdFocus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdFocus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdFocus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdFocus, CDialog)
	//{{AFX_MSG_MAP(CdFocus)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EXPOSEDIT, OnChangeExposedit)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_BIN, OnBin)
	ON_BN_CLICKED(IDC_DECIMATE, OnDecimate)
	ON_BN_CLICKED(IDC_X1, OnX1)
	ON_BN_CLICKED(IDC_X2, OnX2)
	ON_BN_CLICKED(IDC_TCP, OnTcp)
	ON_BN_CLICKED(IDC_TLP, OnTlp)
	ON_BN_CLICKED(IDC_TRP, OnTrp)
	ON_BN_CLICKED(IDC_BCP, OnBcp)
	ON_BN_CLICKED(IDC_BLP, OnBlp)
	ON_BN_CLICKED(IDC_BRP, OnBrp)
	ON_BN_CLICKED(IDC_MCP, OnMcp)
	ON_BN_CLICKED(IDC_MLP, OnMlp)
	ON_BN_CLICKED(IDC_MRP, OnMrp)
	ON_BN_CLICKED(IDC_X4, OnX4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdFocus message handlers

BOOL CdFocus::OnInitDialog()
{
            // Load limits into sliders
	ExposUnits = 3;							/* seconds				*/
	initialize_flag = FALSE;				/* init the flag		*/
    CString DisplayText;					/* String to Display	*/

	/* Initialize before download */
	ReadDefaults(&Exposure, &offset, &bitadjust, &controltype,
					&ccdtype, &interfacetype, &ioaddtype, &interrupttype,
					&adctype, &readouttype, &pantype, &zoom, &focustype, &versiontype );
    PICM_Set_EasyDLL_DC( EASYDLL_FOCUS_MODE );
    PICM_Set_AutoStop( 0 );
    PICM_Set_RS170_enable( TRUE );
    PICM_Set_Temperature( 0.0 );
    PICM_SetExposure( Exposure, &error_code );
    PICM_Set_RS170_bits_shifted( 7-bitadjust );
    PICM_Set_RS170_offset( offset );
    
    /* Initalize sliders */
    SetExposSliderRange( ExposUnits, &expos_factor, &Roundoff, 
						&max_slide, &ExposSlide() );
    SetExposSliderPos( &Exposure, expos_factor, Roundoff, 
						max_slide, &ExposSlide() );
	SetOffsetSliderRange( &max_slide, &OffsetSlide() );
	SetOffsetSliderPos( &offset, max_slide, &OffsetSlide () );
	SetBinSliderRange( &max_slide, &BinSlide() );
	SetBinSliderPos( &bitadjust, max_slide, &BinSlide() );

	switch (pantype)
	{
		case 1:
			pantype = PAN_TL;
			IRQ_TLRadio().SetCheck( TRUE );
			break;
		case 2:
			pantype = PAN_TC;
			IRQ_TCRadio().SetCheck( TRUE );
			break;
		case 3:
			pantype = PAN_TR;
			IRQ_TRRadio().SetCheck( TRUE );
			break;
		case 4:
			pantype = PAN_CL;
			IRQ_CLRadio().SetCheck( TRUE );
			break;
		case 5:
			pantype = PAN_CC;
			IRQ_CCRadio().SetCheck( TRUE );
			break;
		case 6:
			pantype = PAN_CR;
			IRQ_CRRadio().SetCheck( TRUE );
			break;
		case 7:
			pantype = PAN_BL;
			IRQ_BLRadio().SetCheck( TRUE );
			break;
		case 8:
			pantype = PAN_BC;
			IRQ_BCRadio().SetCheck( TRUE );
			break;
		case 9:
			pantype = PAN_BR;
			IRQ_BRRadio().SetCheck( TRUE );
			break;
	}

	if (zoom == 1)
	{
		zoom = ZX1;
		IRQ_X1Radio().SetCheck( TRUE );
	}
	else if (zoom == 2)
	{
		zoom = ZX2;
		IRQ_X2Radio().SetCheck( TRUE );
	}
	else
	{
		zoom = ZX4;
		IRQ_X4Radio().SetCheck( TRUE );
	}

	if (focustype == 2)
	{
		focustype = BINNING_FOCUS;
		IRQ_BinRadio().SetCheck( TRUE );
	}
	else
	{
		focustype = DECIMATION_FOCUS;
		IRQ_DecimateRadio().SetCheck( TRUE );
	}

	DisplayText.Format( "%g", Exposure );
	SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
	DisplayText.Format( "%d", offset );
	SetDlgItemText( IDC_OFFSETTEXT, DisplayText );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnHScroll
//
/////////////////////////////////////////////////////////////////////////////

void CdFocus::OnHScroll
    (
    UINT        nSBCode,
    UINT        nPos,
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
		case IDC_OFFSETSLIDE:
			offset = (int) SlidePos ;
			DisplayText.Format( "%d", offset );
			SetDlgItemText( IDC_OFFSETTEXT, DisplayText );
			break;
		case IDC_BINSLIDE:
			// No edit box for the bit adjust
			bitadjust = (int) SlidePos;
			break;
    }
	
	PICM_Set_Exposure_Online( (double) Exposure, ExposUnits);
	PICM_Set_RS170_offset(offset);
	PICM_Set_RS170_bits_shifted(7 - bitadjust);

    if( nPos || nSBCode );           // Get rid of compiler warnings
}

/////////////////////////////////////////////////////////////////
//
//				Change in the Exposure Edit Box
//
/////////////////////////////////////////////////////////////////

void CdFocus::OnChangeExposedit() 
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

void CdFocus::OnOK()
{
	if (initialize_flag)
	{
		/* Clean up when done.  */
		/*  release big buffer  */
		/*  stop controller		*/
		PICM_Stop_controller();
		initialize_flag = FALSE;
		CDialog::OnOK();
	}
	else    /* Down Load Not successful */
		CDialog::OnOK();

	/* write defaults */
	WriteDefaults( Exposure, offset, bitadjust, controltype,
				ccdtype, interfacetype, ioaddtype, interrupttype,
				adctype, readouttype, pantype, zoom, focustype, versiontype );
}

void CdFocus::OnRun()
{
    // initialize RS170 patterns and such...
    PICM_Initialize_RS170( &error_code );

    if( !error_code )
	{
		controller_ok = PICM_Easy_Focusing (focustype,
							 	Exposure,
								zoom,
								pantype,
								&exp_temp,
								&pat_temp,
								&error_code );
		if (controller_ok)
		{
			controller_ok = PICM_Start_controller();
		}
		else
		{
			MessageBox (
			 "Controller will not start.",
			 "Exit Button",
			  MB_OK | MB_ICONEXCLAMATION );
		}
	initialize_flag = TRUE;
	}
}

void CdFocus::OnStop() 
{
	if (initialize_flag)
	{
		/* Clean up when done.      */
		/*  release big buffer		*/
		/*  stop controller			*/
		PICM_Stop_controller();
		initialize_flag = FALSE;
	}
	else    /* Down Load Not successful */
	{
		MessageBox (
			"You must start the controller",
            "Exit Button",
            MB_OK | MB_ICONEXCLAMATION );
	}
}

void CdFocus::OnBin() 
{
	focustype = BINNING_FOCUS;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnDecimate() 
{
	focustype = DECIMATION_FOCUS;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnX1() 
{
	zoom = ZX1;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnX2() 
{
	zoom = ZX2;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnTcp() 
{
	pantype = PAN_TC;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnTlp() 
{
	pantype = PAN_TL;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnTrp() 
{
	pantype = PAN_TR;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnBcp() 
{
	pantype = PAN_BC;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnBlp() 
{
	pantype = PAN_BL;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnBrp() 
{
	pantype = PAN_BR;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnMcp() 
{
	pantype = PAN_CC;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnMlp() 
{
	pantype = PAN_CL;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnMrp() 
{
	pantype = PAN_CR;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}

void CdFocus::OnX4() 
{
	zoom = ZX4;
	PICM_Easy_Focusing (focustype,
						Exposure,
						zoom,
						pantype,
						&exp_temp,
						&pat_temp,
						&error_code );
}
