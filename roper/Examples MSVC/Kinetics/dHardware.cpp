// dHardware.cpp : implementation file
//

#include "stdafx.h"
#include "Kinetics.h"
#include "dHardware.h"
#include "initexp.h"
#include "MainFrm.h"

/* PI FILES */
extern "C" {
#define PIXCM 1
#include "platform.h"
#include "pigenfcn.h"
#include "pigendef.h"
#include "pii2cfcn.h"
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
	//}}AFX_DATA_INIT
}


void CdHardware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdHardware)
	DDX_Control(pDX, IDC_IOADD, m_IOADD_ComboBox);
	DDX_Control(pDX, IDC_INTERRUPT, m_INTERRUPT_ComboBox);
	DDX_Control(pDX, IDC_INTERFACE, m_INTERFACE_ComboBox);
	DDX_Control(pDX, IDC_SLOW, m_SLOW_Button);
	DDX_Control(pDX, IDC_CCD, m_CCD_ComboBox);
	DDX_Check(pDX, IDC_NVRAM_CHK, nvram);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdHardware, CDialog)
	//{{AFX_MSG_MAP(CdHardware)
	ON_BN_CLICKED(IDC_SLOW, OnSlow)
	ON_BN_CLICKED(IDC_FAST, OnFast)
	ON_CBN_SELCHANGE(IDC_CCD, OnSelchangeCcd)
	ON_CBN_SELCHANGE(IDC_INTERFACE, OnSelchangeInterface)
	ON_CBN_SELCHANGE(IDC_IOADD, OnSelchangeIoadd)
	ON_CBN_SELCHANGE(IDC_INTERRUPT, OnSelchangeInterrupt)
	ON_BN_CLICKED(IDC_NVRAM_CHK, OnNvramChk)
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

// this should be dynamically created.. 

	Detector_ComboBox().SetItemData( 0, EEV_100x1340_B);
	Detector_ComboBox().SetItemData( 1, EEV_100x1340_F);
	Detector_ComboBox().SetItemData( 2, EEV_256x1024_3ph);
	Detector_ComboBox().SetItemData( 3, EEV_256x1024_6ph);
	Detector_ComboBox().SetItemData( 4, EEV_256x1024_6ph_CCD30);
	Detector_ComboBox().SetItemData( 5, EEV_256x1024_8ph);
	Detector_ComboBox().SetItemData( 6, EEV_400x1340_B);
	Detector_ComboBox().SetItemData( 7, EEV_400x1340_B_FT);
	Detector_ComboBox().SetItemData( 8, EEV_400x1340);
	Detector_ComboBox().SetItemData( 9, EEV_1024x512_FT);
	Detector_ComboBox().SetItemData(10, EEV_1024x512_FT_CCD57);
	Detector_ComboBox().SetItemData(11, EEV_512x2048_CCD42_10);
	Detector_ComboBox().SetItemData(12, EEV_576x384_3ph);
	Detector_ComboBox().SetItemData(13, EEV_576x384_6ph);
	Detector_ComboBox().SetItemData(14, EEV_700x1340_B);
	Detector_ComboBox().SetItemData(15, EEV_700x1340);
	Detector_ComboBox().SetItemData(16, EEV_1024x1024);
	Detector_ComboBox().SetItemData(17, EEV_1024x1024_CCD47_10);
	Detector_ComboBox().SetItemData(18, EEV_1024x1024_FT);
	Detector_ComboBox().SetItemData(19, EEV_2048x1024_FT_CCD47_20);
	Detector_ComboBox().SetItemData(20, EEV_1152x298_6ph);
	Detector_ComboBox().SetItemData(21, EEV_1152x298_3ph);
	Detector_ComboBox().SetItemData(22, EEV_1152x770_3ph);
	Detector_ComboBox().SetItemData(23, EEV_1152x770_6ph);
	Detector_ComboBox().SetItemData(24, EEV_1152x1242_3ph);
	Detector_ComboBox().SetItemData(25, EEV_1152x1242_6ph);
	Detector_ComboBox().SetItemData(26, EEV_1300x1340_B);
	Detector_ComboBox().SetItemData(27, EEV_1300x1340);
	Detector_ComboBox().SetItemData(28, HAM_64x1024);
	Detector_ComboBox().SetItemData(29, HAM_128x1024);
	Detector_ComboBox().SetItemData(30, HAM_256x1024);
	Detector_ComboBox().SetItemData(31, KDK_512x768);
	Detector_ComboBox().SetItemData(32, KDK_1024x1280);
	Detector_ComboBox().SetItemData(33, KDK_1024x1536);
	Detector_ComboBox().SetItemData(34, KDK_1035x1317);
	Detector_ComboBox().SetItemData(35, KDK_2044x2033);
	Detector_ComboBox().SetItemData(36, KDK_2048x3072);
	Detector_ComboBox().SetItemData(37, PI_64x1024);
	Detector_ComboBox().SetItemData(38, PI_128x1024);
	Detector_ComboBox().SetItemData(39, PID_240x330_MCT);
	Detector_ComboBox().SetItemData(40, PI_256x1024);
	Detector_ComboBox().SetItemData(41, PID_330x1100_6phH);
	Detector_ComboBox().SetItemData(42, PID_330x1100_8phH);
	Detector_ComboBox().SetItemData(43, PID_532x1752);
	Detector_ComboBox().SetItemData(44, PID_582x782);
	Detector_ComboBox().SetItemData(45, PI_800x1000_B);
	Detector_ComboBox().SetItemData(46, PID_1024x512_SFT);
	Detector_ComboBox().SetItemData(47, PID_1030x1300);
	Detector_ComboBox().SetItemData(48, PID_2500x600_B);
	Detector_ComboBox().SetItemData(49, PID_2500x600_F);
	Detector_ComboBox().SetItemData(50, RET_400x1200);
	Detector_ComboBox().SetItemData(51, RET_512x512);
	Detector_ComboBox().SetItemData(52, RET_1024x1024);
	Detector_ComboBox().SetItemData(53, RET_2048x2048);
	Detector_ComboBox().SetItemData(54, RSS_1024x1024);
	Detector_ComboBox().SetItemData(55, SIT_800x2000_B);
	Detector_ComboBox().SetItemData(56, SIT_800x2000_F);
	Detector_ComboBox().SetItemData(57, SIT_2048x2048_B);
	Detector_ComboBox().SetItemData(58, SIT_2048x2048_F);
	Detector_ComboBox().SetItemData(59, TEK_512x512_B_100ns);
	Detector_ComboBox().SetItemData(60, TEK_512x512_B_200ns);
	Detector_ComboBox().SetItemData(61, TEK_512x512D_B);
	Detector_ComboBox().SetItemData(62, TEK_512x512D_F);
	Detector_ComboBox().SetItemData(63, TEK_512x512_F_100ns);
	Detector_ComboBox().SetItemData(64, TEK_512x512_F_200ns);
	Detector_ComboBox().SetItemData(65, TEK_1024x1024_B_100ns);
	Detector_ComboBox().SetItemData(66, TEK_1024x1024_B_200ns);
	Detector_ComboBox().SetItemData(67, TEK_1024x1024_B_42usV);
	Detector_ComboBox().SetItemData(68, TEK_1024x1024D_B);
	Detector_ComboBox().SetItemData(69, TEK_1024x1024D_B_T3);
	Detector_ComboBox().SetItemData(70, TEK_1024x1024D_F);
	Detector_ComboBox().SetItemData(71, TEK_1024x1024_F_100ns);
	Detector_ComboBox().SetItemData(72, TEK_1024x1024_F_200ns);
	Detector_ComboBox().SetItemData(73, TEK_2048x2048);
	Detector_ComboBox().SetItemData(74, THM_256x1024);
	Detector_ComboBox().SetItemData(75, THM_512x512);
	Detector_ComboBox().SetItemData(76, THM_576x384);
	Detector_ComboBox().SetItemData(77, THM_2048x1024_FT);
	Detector_ComboBox().SetItemData(78, THM_2048x2048);

	IOAddress_ComboBox().SetItemData(0, 0x700);
	IOAddress_ComboBox().SetItemData(1, 0x900);
	IOAddress_ComboBox().SetItemData(2, 0xA00);
	IOAddress_ComboBox().SetItemData(3, 0xB00);

	IRQ_ComboBox().SetItemData(0, CHANNEL_10);
	IRQ_ComboBox().SetItemData(1, CHANNEL_11);
	IRQ_ComboBox().SetItemData(2, CHANNEL_12);
	IRQ_ComboBox().SetItemData(3, CHANNEL_15);

	SetDefaults();

    UpdateData(FALSE);

	return (TRUE);
}

void CdHardware::OnSlow() 
{
	adctype = 0;
	
}

void CdHardware::OnFast() 
{
	adctype = 1;
	
}

void CdHardware::OnSelchangeCcd() 
{
	int selection;

	selection = ((CComboBox*)GetDlgItem(IDC_CCD))->GetCurSel();
	ccdtype   = ((CComboBox*)GetDlgItem(IDC_CCD))->GetItemData(selection);	

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

void CdHardware::OnOK() 
{
 	unsigned int error_code = 0;
    RS_UINT32 error_code2;
	int controller_ok;

    // check if we are using NVRAM defaults
    if( nvram )
    {
        controller_ok = PICM_CreateControllerNvram(1, &error_code2);
        if( controller_ok )
        {
            MessageBox ( "NVRAM Load Completed",
                         "NVRAM Load",
                          MB_OK | MB_ICONEXCLAMATION );
            /*  setting menu items to become enabled */
		    CMainFrame::m_efID_EXPERIMENT_TRIGGERSETUP = TRUE;
        }
        else
        {
            MessageBox ( "ERROR in NVRAM Load",
                         "NVRAM Load",
                          MB_OK | MB_ICONEXCLAMATION );
        }
    }
    else
    {
	    /* creates controller, assigns detector */
	    controller_ok =  PICM_CreateController(ST133,
                                               ccdtype, 
                                               ROM_KINETICS,
                                               APP_NORMAL_IMAGING,
                                               &error_code); 
	    if (controller_ok)
	    {
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
		
		    if( (error_code != 0) || !controller_ok )
			{
			    PICM_CleanUp();
                controller_ok = FALSE;
                MessageBox ( "ERROR in Downloaded",
                             "DownLoad",
                             MB_OK | MB_ICONEXCLAMATION );
                /* clean up on error        */
                /*  release big buffer	*/

            }
            else
            {
                MessageBox ( "Controller has been Downloaded",
                             "DownLoad",
                             MB_OK | MB_ICONEXCLAMATION );
			
			    /*  setting menu items to become enabled */
			    CMainFrame::m_efID_EXPERIMENT_TRIGGERSETUP = TRUE;
			}
	    }
        
    }

	WriteDefaults( nvram, expos, triggertype, ccdtype, interfacetype, 
            ioaddtype, interrupttype,
			adctype );

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
	ReadDefaults( &nvram, &expos, &triggertype, &ccdtype, &interfacetype, 
                    &ioaddtype, &interrupttype,
					&adctype );
	
  	// set defaults only when NVRAM not being used
  	if( !nvram )
  	{
		SetComboCurSel(&Detector_ComboBox(), ccdtype);
		SetComboCurSel(&Interface_ComboBox(), interfacetype);
		SetComboCurSel(&IOAddress_ComboBox(), ioaddtype);
		SetComboCurSel(&IRQ_ComboBox(), interrupttype);

		if (adctype == 1)
			IRQ_FastRadio().SetCheck( TRUE );
		else 
			IRQ_SlowRadio().SetCheck( TRUE );
  	}

    m_SLOW_Button.EnableWindow(!nvram);
    m_CCD_ComboBox.EnableWindow(!nvram);
    m_IOADD_ComboBox.EnableWindow(!nvram);
    m_INTERRUPT_ComboBox.EnableWindow(!nvram);
    m_INTERFACE_ComboBox.EnableWindow(!nvram);
    
}

void CdHardware::OnNvramChk() 
{
    nvram = ~nvram;

    m_SLOW_Button.EnableWindow(~nvram);
    m_CCD_ComboBox.EnableWindow(~nvram);
    m_IOADD_ComboBox.EnableWindow(~nvram);
    m_INTERRUPT_ComboBox.EnableWindow(~nvram);
    m_INTERFACE_ComboBox.EnableWindow(~nvram);

    UpdateData(TRUE);

	
}
