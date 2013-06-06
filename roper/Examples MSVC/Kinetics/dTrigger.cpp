// dTrigger.cpp : implementation file
//

#include "stdafx.h"
#include "platform.h"
#include "Kinetics.h"
#include "dTrigger.h"
#include "exposslider.h"
#include "cheader.h"
#include "initexp.h"

extern "C"
{
    #define PIXCM 1
    #include "platform.h"
    #include "pikindef.h"
    #include "pikinfcn.h"
    #include "piimgfcn.h"
    #include "pigendef.h"
    #include "pigenfcn.h"
    #include "pionlfcn.h"
    #include "pitimdef.h"
    #include "pitimfcn.h"
	#include "pivardef.h"
	#include "pivarfcn.h"
}

HANDLE Test_WriteTestFile
(
 char     *runfile,                /* data file to write to. */
 void huge *big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel            /* size of a pixel in bytes */
  );

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdTrigger dialog


CdTrigger::CdTrigger(CWnd* pParent /*=NULL*/)
	: CDialog(CdTrigger::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdTrigger)
	m_TempStatusText = _T("");
	//}}AFX_DATA_INIT
}


void CdTrigger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdTrigger)
	DDX_Control(pDX, IDC_RUN, m_RunButton);
	DDX_Text(pDX, IDC_TEMPSTATUS_TEXT, m_TempStatusText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdTrigger, CDialog)
	//{{AFX_MSG_MAP(CdTrigger)
   	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EXPOSEDIT, OnChangeExposedit)
	ON_CBN_SELCHANGE(IDC_TRIGGERCOMBO, OnSelchangeTriggercombo)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdTrigger message handlers
BOOL CdTrigger::OnInitDialog()
{
            // Load limits into sliders    
    CString DisplayText;
    int collection;

   	CDialog::OnInitDialog();
	ExposUnits = 3;

	Trigger_ComboBox().SetItemData(0,	KINETICS_NO_TRIGGER);
	Trigger_ComboBox().SetItemData(1,	KINETICS_SINGLE);
	Trigger_ComboBox().SetItemData(2,	KINETICS_MULTIPLE);

    SetExposSliderRange( ExposUnits, &expos_factor, &Roundoff, 
						&max_slide, &ExposSlide() );
    SetExposSliderPos( &Exposure, expos_factor, Roundoff, 
						max_slide, &ExposSlide() );
    SetDefaults();

    /* Set up for Kinetics */
    if (triggertype == KINETICS_NO_TRIGGER)
        collection = CTRL_KINETICS_NO_TRIGGER;
    else if(triggertype == KINETICS_SINGLE)
        collection = CTRL_KINETICS_SINGLE;
    else if(triggertype == KINETICS_MULTIPLE)
        collection = CTRL_KINETICS_MULTIPLE;

    PICM_CMSetLongParam(CMP_TIMING_MODE,collection);
    PICM_CMSetLongParam(CMP_KINETICS_WINDOWSIZE, 64);
    PICM_Set_Current_VTCLK(4);

    /* displaying the exposure in edit box */
    DisplayText.Format( "%g", Exposure );
    SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CdTrigger::OnHScroll
//
/////////////////////////////////////////////////////////////////////////////

void CdTrigger::OnHScroll
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

    if( SliderID == IDC_EXPOSSLIDE )
    {
        Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
        DisplayText.Format( "%g", Exposure );
        SetDlgItemText( IDC_EXPOSEDIT, DisplayText );
    }
    
}

void CdTrigger::OnChangeExposedit() 
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

void CdTrigger::OnSelchangeTriggercombo() 
{
	int triggermode;
    int collection;

	triggermode = ((CComboBox*)GetDlgItem(IDC_TRIGGERCOMBO))->GetCurSel();
	switch (triggermode)
		{
		case 0:					// Free Run
			triggertype = KINETICS_NO_TRIGGER;
			break;
		case 1:					// Single Trigger
			triggertype = KINETICS_SINGLE;
			break;
		case 2:					// Multiple Trigger
			triggertype = KINETICS_MULTIPLE;
			break;
        }

    /* set up collection mode */
    if (triggertype == KINETICS_NO_TRIGGER)
        collection = CTRL_KINETICS_NO_TRIGGER;
    else if(triggertype == KINETICS_SINGLE)
        collection = CTRL_KINETICS_SINGLE;
    else if(triggertype == KINETICS_MULTIPLE)
        collection = CTRL_KINETICS_MULTIPLE;

    if (initialize_flag)
    {
        PICM_Stop_controller();
        PICM_CMSetLongParam(CMP_TIMING_MODE,collection);
        PICM_CMSetLongParam(CMP_KINETICS_WINDOWSIZE,64);
        PICM_Start_controller();
    }
    else
    {
        PICM_CMSetLongParam(CMP_TIMING_MODE,collection);
        PICM_CMSetLongParam(CMP_KINETICS_WINDOWSIZE, 64);
    }	
}

void CdTrigger::OnRun() 
{
	long buffer_size;
    long tempstatus;
    static HANDLE hglb;
	static void *lpvBuffer;
    int done_flag;
    unsigned int status;

    // disable button
    m_RunButton.EnableWindow(FALSE);

    PICM_Set_Temperature(-5.0);
    m_TempStatusText = "Wait for TempLock";
    UpdateData(FALSE);

    // set exposure
    PICM_SetExposure(Exposure, &error_code);

    // set up cleans - needs to be more dynamic
    PICM_CMSetLongParam(CMP_NUMBER_OF_CLEANS,1);
    PICM_CMSetLongParam(CMP_NUM_OF_STRIPS_PER_CLN,512);

    /* allocate buffer for system */
    buffer_size = PICM_SizeNeedToAllocate();
    hglb = GlobalAlloc(GPTR, buffer_size );
    lpvBuffer = (void huge*) GlobalLock(hglb);

    // set edge trigger for single/multiple trigger
    PICM_CMSetLongParam( CMP_EDGE_TRIGGER ,EDGE_TRIGGER_NEG);

    controller_ok = PICM_Initialize_System( 
                                        lpvBuffer,
                                        &error_code);

    if (controller_ok)
    {
        // always wait for temperature to lock after a "PICM_Initialize_System"
        PICM_CMGetLongParam(CMP_TEMP_STATUS, &tempstatus);
        while( !tempstatus )
        {
            PICM_CMGetLongParam(CMP_TEMP_STATUS, &tempstatus);
        }
        m_TempStatusText = "";
        UpdateData(FALSE);

        PICM_Start_controller();
        done_flag = FALSE;
        initialize_flag = TRUE;
        while (!done_flag)
            done_flag = PICM_ChkData(&status);

        if (status & DONEDCOK)
        {
            /*  Write Test File  */
            Test_WriteTestFile( "test.spe", lpvBuffer, 2 );
            
            MessageBox ("Data has been Collected!",
                        "Collection",
                         MB_OK | MB_ICONEXCLAMATION );
        }
        else /* error in data collection */
        {
            MessageBox ("Error in Collection",
                        "Collection",
                        MB_OK | MB_ICONEXCLAMATION );
        }

        PICM_Stop_controller();
    }
    else
        MessageBox ( "Controller could not Initialize.",
                     "Initialization Error",
                     MB_OK | MB_ICONEXCLAMATION );

    GlobalFree(hglb);

    // enable button
    m_RunButton.EnableWindow(TRUE);


}

void CdTrigger::OnOK() 
{
	WriteDefaults( nvram, Exposure, triggertype, ccdtype, interfacetype, 
            ioaddtype, interrupttype,
			adctype );

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

void CdTrigger::OnCancel() 
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

void CdTrigger::SetComboCurSel(
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

void CdTrigger::SetDefaults( )
{
	ReadDefaults( &nvram, &Exposure, &triggertype, &ccdtype, &interfacetype, 
                    &ioaddtype, &interrupttype,
					&adctype );
	
    initialize_flag = FALSE;
	SetComboCurSel(&Trigger_ComboBox(), triggertype);
}

/*****************************************************************
*
*		Test_WriteTestFile
*
*		Description:	Opens a file to write to.  Also writes
*						the header for that file.
*
*****************************************************************/

HANDLE Test_WriteTestFile
(
 char		*runfile,               /* data file to write to. */
 void huge	*big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel             /* size of a pixel in bytes */
)

{
	DWORD BytesToWrite = 4100;
	LPDWORD BytesWritten;
	DWORD temp;

    HANDLE fileptr = NULL;				   /* pointer to file		 */
    CSMAHead * header;

	BytesWritten = &temp;
    fileptr = CreateFile( runfile,
						  GENERIC_WRITE,
						  FILE_SHARE_WRITE,
						  0,
						  CREATE_ALWAYS,
						  FILE_ATTRIBUTE_NORMAL,
						  0);

    header = new CSMAHead;
    memset( header, 0, 4100 );
    /*  fill in some of the header  */
    header->noscan = -1;
    
	header->datatype = 3;  //unsigned integer
    
	header->ydim		= PICM_Get_pixeldimension_y();
    /* if multiple frame, * frameNum */
	header->lnoscan		= header->ydim;  
	header->xdim		= PICM_Get_pixeldimension_x();
    header->scramble = 1;
    header->lastvalue   = 0x5555;
	header->WinView_id  = 0x1234567;
	header->file_header_ver = HEADER_VERSION;
   
    /*  write CSMA HEADER to Output File  */
	WriteFile ( fileptr,
				(LPCVOID) header,
				BytesToWrite,
				BytesWritten,
				0);

    /*  release Header Memory  */
    delete ( header ); 

	/*  Generate a TEST CSMA DATA file  */
    LPCVOID address;

	BytesWritten = &temp;

    /*  write data to Output File  */
    address = (LPCVOID)big_buffer;

	BytesToWrite =	(long)PICM_Get_pixeldimension_x() * 
					(long)byte_size_of_pixel * 
					(long)PICM_Get_pixeldimension_y();

	WriteFile ( fileptr,
				address,
				BytesToWrite,
				BytesWritten,
				0);

    CloseHandle( fileptr );

	return fileptr;
}

tagCSMAHEAD::tagCSMAHEAD()
{
  WinView_id = 0x1234567; // magic number should be a const def.
  file_header_ver = (float)HEADER_VERSION;
}
