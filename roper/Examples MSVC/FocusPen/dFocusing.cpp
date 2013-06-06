// dFocusing.cpp : implementation file
//

#include "stdafx.h"
#include "FocusPen.h"
#include "dFocusing.h"
#include "exposslider.h"
#include "initexp.h"

extern "C"
{
    #define PIXCM 1
    #include "platform.h"
    #include "pifcsdef.h"
    #include "pifcsfcn.h"
    #include "piimgfcn.h"
    #include "pigendef.h"
    #include "pigenfcn.h"
    #include "pionlfcn.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdFocusing dialog


CdFocusing::CdFocusing(CWnd* pParent /*=NULL*/)
	: CDialog(CdFocusing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdFocusing)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdFocusing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdFocusing)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdFocusing, CDialog)
	//{{AFX_MSG_MAP(CdFocusing)
   	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_LUTCOMBO, OnSelchangeLutcombo)
	ON_EN_CHANGE(IDC_EXPOSEDIT, OnChangeExposedit)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_Stop, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdFocusing message handlers
BOOL CdFocusing::OnInitDialog()
{
            // Load limits into sliders    
    CString DisplayText;

   	CDialog::OnInitDialog();
	ExposUnits = 3;

	LUT_ComboBox().SetItemData(0,	LOOKUP_LINEAR);
	LUT_ComboBox().SetItemData(1,	LOOKUP_INVERSE_LINEAR);
	LUT_ComboBox().SetItemData(2,	LOOKUP_LOG);
	LUT_ComboBox().SetItemData(3,	LOOKUP_INVERSE_LOG);
	LUT_ComboBox().SetItemData(4,	LOOKUP_EXPONENTIAL);
	LUT_ComboBox().SetItemData(5,	LOOKUP_SQUARE);
	LUT_ComboBox().SetItemData(6,	LOOKUP_SQRT);
	LUT_ComboBox().SetItemData(7,	LOOKUP_GAMMA);
	LUT_ComboBox().SetItemData(8,	BIT_RANGE_0_64);
	LUT_ComboBox().SetItemData(9,	BIT_RANGE_0_128);
	LUT_ComboBox().SetItemData(10,	BIT_RANGE_0_256);
	LUT_ComboBox().SetItemData(11,	BIT_RANGE_2_512);
	LUT_ComboBox().SetItemData(12,	BIT_RANGE_4_1024);
	LUT_ComboBox().SetItemData(13,	BIT_RANGE_8_2048);
	LUT_ComboBox().SetItemData(14,	BIT_RANGE_16_4096);

    SetExposSliderRange( ExposUnits, &expos_factor, &Roundoff, 
						&max_slide, &ExposSlide() );
    SetExposSliderPos( &Exposure, expos_factor, Roundoff, 
						max_slide, &ExposSlide() );

    SetDefaults();
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

void CdFocusing::OnHScroll
    (
    UINT        nSBCode,
    UINT        nPos,
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
        Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
        DisplayText.Format( "%g", Exposure );
        SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
    }
    
	PICM_Set_Exposure_Online( (double) Exposure, ExposUnits);
    if( nPos || nSBCode );           // Get rid of compiler warnings
}

void CdFocusing::OnSelchangeLutcombo() 
{
	int luttable;

	luttable = ((CComboBox*)GetDlgItem(IDC_LUTCOMBO))->GetCurSel();
	switch (luttable)
		{
		case 0:					// 0x700
			luttype = LOOKUP_LINEAR;
			break;
		case 1:					// 0x900
			luttype = LOOKUP_INVERSE_LINEAR;
			break;
		case 2:					// 0xA00
			luttype = LOOKUP_LOG;
			break;
		case 3:					// 0xB00
			luttype = LOOKUP_INVERSE_LOG;
			break;
		case 4:					// 0xB00
			luttype = LOOKUP_EXPONENTIAL;
			break;
		case 5:					// 0xB00
			luttype = LOOKUP_SQUARE;
			break;
		case 6:					// 0xB00
			luttype = LOOKUP_SQRT;
			break;
		case 7:					// 0xB00
			luttype = LOOKUP_GAMMA;
			break;
		case 8:					// 0xB00
			luttype = BIT_RANGE_0_64;
			break;
		case 9:					// 0xB00
			luttype = BIT_RANGE_0_128;
			break;
		case 10:					// 0xB00
			luttype = BIT_RANGE_0_256;
			break;
		case 11:					// 0xB00
			luttype = BIT_RANGE_2_512;
			break;
		case 12:					// 0xB00
			luttype = BIT_RANGE_4_1024;
			break;
		case 13:					// 0xB00
			luttype = BIT_RANGE_8_2048;
			break;
		case 14:					// 0xB00
			luttype = BIT_RANGE_16_4096;
			break;
    }

    if (initialize_flag)
    {
        PICM_Stop_controller();
        PICM_Set_lut_type(luttype);
        PICM_Set_lookuptable(NULL);
        PICM_Start_controller();
    }
    else
    {
        PICM_Set_lut_type(luttype);
        PICM_Set_lookuptable(NULL);
    }
}

void CdFocusing::OnChangeExposedit() 
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
        
        if (tmp_expos<=1000)
            Exposure = tmp_expos;
        else 
        {
            Exposure = 1000;
            DisplayText.Format( "%g", Exposure );
            SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
        }

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

void CdFocusing::SetComboCurSel(
    CComboBox *pComboCtrl,
    int CurrentValue
    )
{
    int idx, count;
    BOOL DoneFlag;

              // Now set the current value as selected
    count = pComboCtrl->GetCount();

    for( idx = 0, DoneFlag = FALSE;
         idx < count && DoneFlag == FALSE;
         idx++ )
    {
        if( (int)pComboCtrl->GetItemData( idx ) == CurrentValue )
        {
            pComboCtrl->SetCurSel( idx );
            DoneFlag = TRUE;
        }
    }
}

void CdFocusing::SetDefaults( )
{
	ReadDefaults( &Exposure, &luttype, &ccdtype, &interfacetype, 
                    &ioaddtype, &interrupttype,
					&adctype, &readouttype, &versiontype );
	
    initialize_flag = FALSE;
	SetComboCurSel(&LUT_ComboBox(), luttype);
}

void CdFocusing::OnOK() 
{
	WriteDefaults( Exposure, luttype, ccdtype, interfacetype, 
            ioaddtype, interrupttype,
			adctype, readouttype, versiontype );

    /* Stop controller if it has not already been stopped */
	if (initialize_flag)
    {
		PICM_Stop_controller();
		initialize_flag = FALSE;
	    CDialog::OnOK();
    }
    else
	    CDialog::OnOK();
	
}

void CdFocusing::OnRun() 
{
    controller_ok = PICM_SetExposure(Exposure, &error_code);
    if (controller_ok)
    {

  	 controller_ok = PICM_SetROI( 1, 1,
                                PICM_Get_sensor_x(),
                                PICM_Get_sensor_y(),
                                1, 1,
                                &error_code);
                                   
     /* Initialize system (hardware and software). */
     if (controller_ok)
        controller_ok = PICM_Initialize_RS170(
                                            &error_code);
     if (controller_ok)
     {
          PICM_Start_controller();
          initialize_flag = TRUE;
     }
     else
        MessageBox ( "Controller could not Initialize.",
                     "Initialization Error",
                     MB_OK | MB_ICONEXCLAMATION );

    }
}

void CdFocusing::OnCancel() 
{
    /* Stop controller if it has not already been stopped */
	if (initialize_flag)
    {
		PICM_Stop_controller();
		initialize_flag = FALSE;
	    CDialog::OnCancel();
    }
    else
	    CDialog::OnCancel();
}

void CdFocusing::OnStop() 
{
	if (initialize_flag)
	{
		/*  stop controller and uninitialize */
		PICM_Stop_controller();
		initialize_flag = FALSE;
	}
	else    
    /* Down Load Not successful */
	{
		MessageBox (
			"You must start the controller",
            "Exit Button",
            MB_OK | MB_ICONEXCLAMATION );
	}

}
