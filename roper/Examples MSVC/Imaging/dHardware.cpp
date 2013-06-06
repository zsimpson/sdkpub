// dHardware.cpp : implementation file
//

#include "stdafx.h"
#include "Imaging.h"
#include "dHardware.h"
#include "MainFrm.h"
#include "initexp.h"

/* PI FILES */
extern "C" {
#define PIXCM 1
#include "platform.h"
#include "pigenfcn.h"
#include "pigendef.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdHardware dialog


CdHardware::CdHardware(CWnd* pParent /*=NULL*/)
	: CDialog(CdHardware::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdHardware)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdHardware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdHardware)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdHardware, CDialog)
	//{{AFX_MSG_MAP(CdHardware)
	ON_CBN_SELCHANGE(IDC_CONTROL, OnSelchangeControl)
	ON_CBN_SELCHANGE(IDC_INTERFACE, OnSelchangeInterface)
	ON_CBN_SELCHANGE(IDC_CCD, OnSelchangeCcd)
	ON_CBN_SELCHANGE(IDC_IOADD, OnSelchangeIoadd)
	ON_CBN_SELCHANGE(IDC_INTERRUPT, OnSelchangeInterrupt)
	ON_BN_CLICKED(IDC_SLOW, OnSlow)
	ON_BN_CLICKED(IDC_FAST, OnFast)
	ON_BN_CLICKED(IDC_FULL, OnFull)
	ON_BN_CLICKED(IDC_FT, OnFt)
	ON_BN_CLICKED(IDC_INTERLINE, OnInterline)
	ON_CBN_SELCHANGE(IDC_CONTROLVER, OnSelchangeControlver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdHardware message handlers

BOOL CdHardware::OnInitDialog()
{
	CDialog::OnInitDialog();

	Interface_ComboBox().SetItemData(0,	TAXI_Interface);
	Interface_ComboBox().SetItemData(1,	TAXI_TypeB_Interface);
	Interface_ComboBox().SetItemData(2,	PCI_COMPLEX_PC_Interface);

	Controller_ComboBox().SetItemData(0, ST130);
	Controller_ComboBox().SetItemData(1, ST138);
	Controller_ComboBox().SetItemData(2, DC131);
	Controller_ComboBox().SetItemData(3, ST133);
	Controller_ComboBox().SetItemData(4, ST133);
	Controller_ComboBox().SetItemData(5, ST133_5MHZ);

	Detector_ComboBox().SetItemData(0, EEV_256x1024_3ph);
	Detector_ComboBox().SetItemData(1, EEV_576x384_3ph);
	Detector_ComboBox().SetItemData(2, EEV_1152x298_3ph);
	Detector_ComboBox().SetItemData(3, EEV_1152x1242_3ph);
	Detector_ComboBox().SetItemData(4, EEV_256x1024_6ph);
	Detector_ComboBox().SetItemData(5, EEV_1024x512_FT);
	Detector_ComboBox().SetItemData(6, EEV_576x384_6ph);
	Detector_ComboBox().SetItemData(7, EEV_1152x298_6ph);
	Detector_ComboBox().SetItemData(8, EEV_1152x1242_6ph);
	Detector_ComboBox().SetItemData(9, EEV_256x1024_8ph);
	Detector_ComboBox().SetItemData(10, EEV_1152x770_3ph);
	Detector_ComboBox().SetItemData(11, EEV_1152x770_6ph);
	Detector_ComboBox().SetItemData(12, EEV_256x1024_6ph_CCD30);
    Detector_ComboBox().SetItemData(13, EEV_1024x1024_CCD47_10);
	Detector_ComboBox().SetItemData(14, HAM_64x1024);
	Detector_ComboBox().SetItemData(15, HAM_128x1024);
	Detector_ComboBox().SetItemData(16, HAM_256x1024);
	Detector_ComboBox().SetItemData(17, KDK_1024x1536);
	Detector_ComboBox().SetItemData(18, KDK_512x768);
	Detector_ComboBox().SetItemData(19, KDK_1035x1317);
	Detector_ComboBox().SetItemData(20, KDK_1024x1280);
	Detector_ComboBox().SetItemData(21, KDK_2044x2033);
	Detector_ComboBox().SetItemData(22, KDK_2048x3072);
	Detector_ComboBox().SetItemData(23, PID_330x1100_8phH);
	Detector_ComboBox().SetItemData(24, PID_532x1752);
	Detector_ComboBox().SetItemData(25, PID_330x1100_6phH);
	Detector_ComboBox().SetItemData(26, PID_240x330_MCT);
	Detector_ComboBox().SetItemData(27, PI_64x1024);
	Detector_ComboBox().SetItemData(28, PI_128x1024);
	Detector_ComboBox().SetItemData(29, PI_256x1024);
	Detector_ComboBox().SetItemData(30, RET_400x1200);
	Detector_ComboBox().SetItemData(31, RET_512x512);
	Detector_ComboBox().SetItemData(32, RET_1024x1024);
	Detector_ComboBox().SetItemData(33, RET_2048x2048);
	Detector_ComboBox().SetItemData(34, SIT_800x2000_B);
	Detector_ComboBox().SetItemData(35, SIT_800x2000_F);
	Detector_ComboBox().SetItemData(36, PI_800x1000_B);
	Detector_ComboBox().SetItemData(37, TEK_512x512_B_100ns);
	Detector_ComboBox().SetItemData(38, TEK_512x512_F_100ns);
	Detector_ComboBox().SetItemData(39, TEK_1024x1024_B_100ns);
	Detector_ComboBox().SetItemData(40, TEK_1024x1024_F_100ns);
	Detector_ComboBox().SetItemData(41, TEK_2048x2048);
	Detector_ComboBox().SetItemData(42, TEK_1024x1024_B_200ns);
	Detector_ComboBox().SetItemData(43, TEK_1024x1024_F_200ns);
	Detector_ComboBox().SetItemData(44, TEK_512x512_B_200ns);
	Detector_ComboBox().SetItemData(45, TEK_512x512_F_200ns);
	Detector_ComboBox().SetItemData(46, TEK_512x512D_B);
	Detector_ComboBox().SetItemData(47, TEK_512x512D_F);
	Detector_ComboBox().SetItemData(48, TEK_1024x1024_B_42usV);
	Detector_ComboBox().SetItemData(49, TEK_1024x1024D_B);
	Detector_ComboBox().SetItemData(50, TEK_1024x1024D_F);
	Detector_ComboBox().SetItemData(51, TEK_1024x1024D_B_T3);
	Detector_ComboBox().SetItemData(52, THM_576x384);
	Detector_ComboBox().SetItemData(53, THM_512x512);
	Detector_ComboBox().SetItemData(54, THM_256x1024);
	Detector_ComboBox().SetItemData(55, THM_2048x1024_FT);

	IOAddress_ComboBox().SetItemData(0, 0x700);
	IOAddress_ComboBox().SetItemData(1, 0x900);
	IOAddress_ComboBox().SetItemData(2, 0xA00);
	IOAddress_ComboBox().SetItemData(3, 0xB00);

	IRQ_ComboBox().SetItemData(0, CHANNEL_10);
	IRQ_ComboBox().SetItemData(1, CHANNEL_11);
	IRQ_ComboBox().SetItemData(2, CHANNEL_12);
	IRQ_ComboBox().SetItemData(3, CHANNEL_15);

	SetDefaults();

	return (TRUE);
}

void CdHardware::OnSelchangeControl() 
{
	int ctype;

	ctype = ((CComboBox*)GetDlgItem(IDC_CONTROL))->GetCurSel();
	switch (ctype)
	{
		case 0:					// ST130
			controltype = ST130;
			break;
		case 1:					// ST138
			controltype = ST138;
			break;
		case 2:					// PentaMax
			controltype = DC131;
			break;
		case 3:					// MicroMax
			controltype = ST133;
			break;
		case 4:					// SpectraMAX
			controltype = ST133;
			break;
		case 5:					// MicroMAX (5MHz)
			controltype = ST133_5MHZ;
	}	
}

void CdHardware::OnSelchangeInterface() 
{
	int itype;


	itype = ((CComboBox*)GetDlgItem(IDC_INTERFACE))->GetCurSel();
	switch (itype)
	{
		case 0:					// TAXI
			interfacetype = TAXI_Interface;
			break;
		case 1:					// TAXI Type B
			interfacetype = TAXI_TypeB_Interface;
			break;
		case 2:					// High Speed PCI
			interfacetype = PCI_COMPLEX_PC_Interface;
			break;
	}
	
}

void CdHardware::OnSelchangeCcd() 
{
	int detecttype;

	detecttype = ((CComboBox*)GetDlgItem(IDC_CCD))->GetCurSel();
	switch (detecttype)
	{
		case 0:					// EEV 256x1024 3-phase
			ccdtype = EEV_256x1024_3ph;
			break;
		case 1:					// EEV 576x384 3-phase
			ccdtype = EEV_576x384_3ph;
			break;
		case 2:					// EEV 1152x298 3-phase
			ccdtype = EEV_1152x298_3ph;
			break;
		case 3:					// EEV 1152x1242
			ccdtype = EEV_1152x1242_3ph;
			break;
		case 4:					// EEV 256x1024 6-phase
			ccdtype = EEV_256x1024_6ph;
			break;
		case 5:					// EEV 1024x512 FT
			ccdtype = EEV_1024x512_FT;
			break;
		case 6:					// EEV 576x384 6-phase
			ccdtype = EEV_576x384_6ph;
			break;
		case 7:					// EEV 1152x298 6-phase
			ccdtype = EEV_1152x298_6ph;
			break;
		case 8:					// EEV 1152x1242 6-phase
			ccdtype = EEV_1152x1242_6ph;
			break;
		case 9:					// EEV 256x1024 8-phase
			ccdtype = EEV_256x1024_8ph;
			break;
		case 10:				// EEV 1152x770 3-phase
			ccdtype = EEV_1152x770_3ph;
			break;
		case 11:				// EEV 1152x770 6-phase
			ccdtype = EEV_1152x770_6ph;
			break;
		case 12:				// EEV 256x1024 6-phase CCD30
			ccdtype = EEV_256x1024_6ph_CCD30;
			break;
		case 13:				// EEV 1024x1024 CCD47-10
			ccdtype = EEV_1024x1024_CCD47_10;
			break;
		case 14:				// HAMMA 64x1024
			ccdtype = HAM_64x1024;
			break;
		case 15:				// HAMMA 128x1024
			ccdtype = HAM_128x1024;
			break;
		case 16:				// HAMMA 256x1024
			ccdtype = HAM_256x1024;
			break;
		case 17:				// KODAK 1024x1536
			ccdtype = KDK_1024x1536;
			break;
		case 18:				// KODAK 512x768
			ccdtype = KDK_512x768;
			break;
		case 19:				// KODAK 1035x1317
			ccdtype = KDK_1035x1317;
			break;
		case 20:				// KODAK 1024x1280
			ccdtype = KDK_1024x1280;
			break;
		case 21:				// KODAK 2044x2033
			ccdtype = KDK_2044x2033;
			break;
		case 22:				// KODAK 2048x3072
			ccdtype = KDK_2048x3072;
			break;
		case 23:				// PI 330x1100 8-phase (horz)
			ccdtype = PID_330x1100_8phH;
			break;
		case 24:				// PI 532x1752
			ccdtype = PID_532x1752;
			break;
		case 25:				// PI 330x1100 6-phase
			ccdtype = PID_330x1100_6phH;
			break;
		case 26:				// PI 240x330 HgCdTe
			ccdtype = PID_240x330_MCT;
			break;
		case 27:				// PI 64x1024
			ccdtype = PI_64x1024;
			break;
		case 28:				// PI 128x1024
			ccdtype = PI_128x1024;
			break;
		case 29:				// PI 256x1024
			ccdtype = PI_256x1024;
			break;
		case 30:				// RET 400x1200
			ccdtype = RET_400x1200;
			break;
		case 31:				// RET 512x512
			ccdtype = RET_512x512;
			break;
		case 32:				// RET 1024x1024
			ccdtype = RET_1024x1024;
			break;
		case 33:				// RET 2048x2048
			ccdtype = RET_2048x2048;
			break;
		case 34:				// SIT 800x2000 Back Illm
			ccdtype = SIT_800x2000_B;
			break;
		case 35:				// SIT 800x2000 Front Illm
			ccdtype = SIT_800x2000_F;
			break;
		case 36:				// SIT 800x1000 Back
			ccdtype = PI_800x1000_B;
			break;
		case 37:				// TEK 512x512B [100ns]
			ccdtype = TEK_512x512_B_100ns;
			break;
		case 38:				// TEK 512x512F [100ns]
			ccdtype = TEK_512x512_F_100ns;
			break;
		case 39:				// TEK 1024x1024B [100ns]
			ccdtype = TEK_1024x1024_B_100ns;
			break;
		case 40:				// TEK 1024x1024F [100ns]
			ccdtype = TEK_1024x1024_F_100ns;
			break;
		case 41:				// TEK 2048x2048
			ccdtype = TEK_2048x2048;
			break;
		case 42:				// TEK 1024x1024B Illm
			ccdtype = TEK_1024x1024_B_200ns;
			break;
		case 43:				// TEK 1024x1024F Illm
			ccdtype = TEK_1024x1024_F_200ns;
			break;
		case 44:				// TEK 512x512B [200ns]
			ccdtype = TEK_512x512_B_200ns;
			break;
		case 45:				// TEK 512x512F [200ns]
			ccdtype = TEK_512x512_F_200ns;
			break;
		case 46:				// TEK 512x512D Back Illm
			ccdtype = TEK_512x512D_B;
			break;
		case 47:				// TEK 512x512D Front Illm
			ccdtype = TEK_512x512D_F;
			break;
		case 48:				// TEK 1024x1024B Back Illm 42usV
			ccdtype = TEK_1024x1024_B_42usV;
			break;
		case 49:				// TEK 1024x1024D Back Illm
			ccdtype = TEK_1024x1024D_B;
			break;
		case 50:				// TEK 1024x1024D Front Illm
			ccdtype = TEK_1024x1024D_F;
			break;
		case 51:				// TEK 1024x1024D Back Illm T3
			ccdtype = TEK_1024x1024D_B_T3;
			break;
		case 52:				// TH 576x384
			ccdtype = THM_576x384;
			break;
		case 53:				// TH 512x512
			ccdtype = THM_512x512;
			break;
		case 54:				// TH 256x1024
			ccdtype = THM_256x1024;
			break;
		case 55:				// TH THM_2048x1024FT
			ccdtype = THM_2048x1024_FT;
			break;
	}	
	
}

void CdHardware::OnSelchangeIoadd() 
{
	int iotype;

	iotype = ((CComboBox*)GetDlgItem(IDC_IOADD))->GetCurSel();
	switch (iotype)
	{
		case 0:					// 0x700
			ioaddtype = 0x700;
			break;
		case 1:					// 0x900
			ioaddtype = 0x900;
			break;
		case 2:					// 0xA00
			ioaddtype = 0xA00;
			break;
		case 3:					// 0xB00
			ioaddtype = 0xB00;
			break;
	}	
}

void CdHardware::OnSelchangeInterrupt() 
{
	int irqtype;

	irqtype = ((CComboBox*)GetDlgItem(IDC_INTERRUPT))->GetCurSel();
	switch (irqtype)
	{
		case 0:					// IRQ 10
			interrupttype = CHANNEL_10;
			break;
		case 1:					// IRQ 11
			interrupttype = CHANNEL_11;
			break;
		case 2:					// IRQ 12
			interrupttype = CHANNEL_12;
			break;
		case 3:					// IRQ 15
			interrupttype = CHANNEL_15;
			break;
	}	
}

void CdHardware::OnSlow() 
{
	adctype = 0;
}

void CdHardware::OnFast() 
{
	adctype = 1;	
}

void CdHardware::OnFull() 
{
	readouttype = ROM_FULL;	
}

void CdHardware::OnFt() 
{
	readouttype = ROM_FRAME_TRANSFER;
	
}

void CdHardware::OnInterline() 
{
	readouttype = ROM_INTERLINE;
	
}

void CdHardware::OnOK() 
{
 	unsigned int error_code = 0;
	int controller_ok;

    /* get the readout mode */
    if( IsDlgButtonChecked( IDC_FULL ) )
        readouttype = ROM_FULL;
    else if( IsDlgButtonChecked( IDC_FT ) )
        readouttype = ROM_FRAME_TRANSFER;
    else
        readouttype = ROM_INTERLINE;

	/* creates controller, assigns detector */
	controller_ok =  PICM_CreateController(controltype,
                                           ccdtype, 
                                           readouttype,
                                           APP_NORMAL_IMAGING,
                                           &error_code); 
	if (controller_ok)
	{
	
		PICM_Set_controller_version(versiontype);

		/* set up interface card */
		controller_ok = PICM_SetInterfaceCard(
						interfacetype,
						ioaddtype,
						interrupttype,
						&error_code);
		
		/* set up Fast or Slow ADC */
		if (adctype == 1)
			PICM_Set_Fast_ADC();
		else
			PICM_Set_Slow_ADC();
		
        MessageBox ( "Controller has been Downloaded",
                     "DownLoad",
                     MB_OK | MB_ICONEXCLAMATION );
			
			/* enables the menu item */
		CMainFrame::m_efID_EXPERIMENT_EXPERSETUP = TRUE;

	}	
	WriteDefaults( expos, xstart, ystart, xend, yend, controltype,
				ccdtype, interfacetype, ioaddtype, interrupttype,
				adctype, readouttype, versiontype );
	
	CDialog::OnOK();
}

void CdHardware::SetComboCurSel(
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

void CdHardware::SetDefaults( )
{
	ReadDefaults( &expos, &xstart, &ystart, &xend, &yend, &controltype,
					&ccdtype, &interfacetype, &ioaddtype, &interrupttype,
					&adctype, &readouttype, &versiontype );
	
	SetComboCurSel(&Controller_ComboBox(), controltype);
	SetComboCurSel(&Detector_ComboBox(), ccdtype);
	SetComboCurSel(&Interface_ComboBox(), interfacetype);
	SetComboCurSel(&IOAddress_ComboBox(), ioaddtype);
	SetComboCurSel(&IRQ_ComboBox(), interrupttype);
	SetComboCurSel(&ControlVer_ComboBox(), versiontype);

	if (adctype == 1)
		IRQ_FastRadio().SetCheck( TRUE );
	else 
		IRQ_SlowRadio().SetCheck( TRUE );

	if (readouttype == ROM_FRAME_TRANSFER)
		IRQ_FTRadio().SetCheck ( TRUE );
	else if (readouttype == ROM_INTERLINE)
		IRQ_InterlineRadio().SetCheck ( TRUE );
    else
		IRQ_FullRadio().SetCheck ( TRUE );
}


void CdHardware::OnSelchangeControlver() 
{
	int vertype;

	vertype = ((CComboBox*)GetDlgItem(IDC_CONTROLVER))->GetCurSel();
	switch (vertype)
	{
		case 0:					// version 1
			versiontype = 1;
			break;
		case 1:					// version 2
			versiontype = 2;
			break;
		case 2:					// version 3
			versiontype = 3;
			break;
		case 3:					// version 4
			versiontype = 4;
			break;
		case 4:					// version 5
			versiontype = 5;
			break;
	}	
	
}
