// PPWvExSet.cpp : WinX experiment setup property pages and sheet
//
//////////////////////////////////////////////////////////////////////////
//   This revision:  $Revision: 2 $
//   Last check-in   $Date: 4/08/97 12:49p $
//   Last changes by $Author: Tim $
//   Changes:
/*   $Log: /EasyDLL95/Examples/General/ppwvexset.cpp $
*  
*  2     4/08/97 12:49p Tim
*  added controller version to hardware dialog
*  
*  1     1/16/97 1:54p Jenn
*  
*  22    9/20/96 3:59p Terry
*  Change CWinviewDoc to CWinxDoc, CWinviewApp to CWinxApp and #include
*  "winview.h" to #include "winxapp.h"
*  
*  21    9/19/96 1:57p Terry
*  Correct how the PixelAccess flag is setup durng Upload
*  
*  20    9/16/96 6:48a Terry
*  Add pseudo-real slider control for exposure time
*  
*  19    9/06/96 12:29p Terry
*  Fix problems with dialog not using current data for some items
*  (may still be broken for cosmic threshold)
*  
*  18    8/30/96 12:51p Terry
*  Added call to Run_WinX_Application for RUN button
*  
*  17    8/28/96 4:38p Terry
*  Move the ConvertTime() function to ControlUtilities.cpp
*  
*  16    8/26/96 11:05a Terry
*  Fix limits and direction of Num Images & Num Accums
*  
*  15    8/26/96 10:21a Terry
*  Using doc.h now so can't use DEFAULT_TYPE & CSMA_DATA in same switch
*  
*  14    8/26/96 10:06a Terry
*  Continue with getting "Run" to work...
*  
*  13    8/23/96 3:46p Terry
*  Ready for integration with a real controller object
*  
*  12    8/21/96 3:13p Terry
*  Incremental...
*  
*  11    8/20/96 4:16p Terry
*  Should be ready for hook-up to a real controller object
*  
*  10    8/16/96 3:50p Terry
*  Another incremental version...
*  
*  9     8/16/96 10:11a Terry
*  Pretty much done except for getting PIXCM resources and the get/set of
*  the controller object.
*  
*  8     8/15/96 4:44p Terry
*  Incremental save...
*  
*  7     8/13/96 3:03p Terry
*  Another intermediate version...should compile & run
*  
*  6     8/06/96 5:45p Terry
*  Intermediate version...will not link...
*  
*  5     8/04/96 12:09p Terry
*  In work: Adding code behind the ExpSetup dialogs
*  
*  4     8/01/96 11:46a Maynard
*  
*  3     7/30/96 8:12p Maynard
*  
*  2     7/23/96 6:06p Maynard
*  Add VCS info tags
*/  
///////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <stdlib.h>
#include "platform.h"
#include "winxapp.h"
#include "PPWvExSet.h"
#include "winxtext.h"
#include "pixcmtxt.h"
#include "pixcmdll.h"           // For define of CMRESOURCE
#include "wxstring.h"
#include "pitypes.h"
////#if 1
////#include "dataman.h"
////#endif
#include "doc.h"
#include "cmenum.h"
#include "contrman.h"           // For CONTROLLER define
#include "errutil.h"            // For Get_resource_value() prototype
#include "hwdwnlds.h"           // For Experiment_setup_download()
#include "storutil.h"           // For Xalloc & Xfree prototypes
#include "dlgwvpixeldef.h"
#include "controlutilities.h"
#include "winxmenu.h"           // For Run_WinX_Application()


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif

////////// TVR:
////////// The strings below need to somehow be moved to resources
////////// or some kind of BuildFilter function should be found or
////////// created.  I have not been able to get the embedded NULL
////////// in the resource or the double NULL ending.
static CHAR *SpeFileType  = "PI's WinX (*.SPE)\0*.SPE\0\0";
static CHAR *SpeExt       = ".SPE";
static CHAR *BlemFileType = "PI's Blemish File (*.BLE)\0*.BLE\0\0";
static CHAR *BlemExt      = ".BLE";

////////// TVR: MORE STRINGS TO MOVE TO RESOURCES...
static CHAR *BackName         = "Background Subtraction File Name";
static CHAR *FlatName         = "FlatField File Name";
static CHAR *BlemName         = "Blemish Removal File Name";
static CHAR *RunButtonName    = "Run";
static CHAR *BackFileMsg      = "Background File ";
static CHAR *FlatFieldFileMsg = "FlatField File ";
static CHAR *BlemishFileMsg   = "Blemish File ";
static CHAR *NotExistMsg      = " Does Not Exist!";
static CHAR *Gstring          = "%g";
static CHAR *Dstring          = "%d";
static CHAR *PixDefFormat     = "X: %d  Y: %d";


////////// TVR: Make these accessable to all other functions?????
//////////  DUPLICATE LIVES IN PPWVRUNAS.CPP - UNTIL A GENERAL ONE EXISTS...
static BOOL GetOpenFileNameAndPathSPE( SHORT FileType, CHAR *Name, CHAR *Path,
                                       CHAR *title, HWND hwnd );

static void Do_PixDef_Dlg( void );

static BOOL upload_done = FALSE;
static int expos_factor, max_slide;
static double Roundoff;


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::CPSWvExSet - By ID
//
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CPSWvExSet, CPropertySheet)

CPSWvExSet::CPSWvExSet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
  m_pBtnRun = 0;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::CPSWvExSet - By String
//
/////////////////////////////////////////////////////////////////////////////

CPSWvExSet::CPSWvExSet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
  m_pBtnRun = 0;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::~CPSWvExSet
//
/////////////////////////////////////////////////////////////////////////////

CPSWvExSet::~CPSWvExSet()
{
    if (m_pBtnRun)
        delete m_pBtnRun;

    upload_done = FALSE;  // Reset static flag for next time
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET MESSAGE MAP
//
//              CPSWvExSet
//
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPSWvExSet, CPropertySheet)
    //{{AFX_MSG_MAP(CPSWvExSet)
    ON_COMMAND( IDOK,       OnApplyNow )
    ON_COMMAND( IDCANCEL,   OnCancel   )
    ON_COMMAND( IDC_CUSTOM, OnRun      )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::OnInitDialog
//
//  This function will Add the RUN button and disable
//  the "Apply" button.
//  It will then upload all the protected data from the
//  current controller object.
//
/////////////////////////////////////////////////////////////////////////////

BOOL CPSWvExSet::OnInitDialog() 
{
    BOOL bRetval =  CPropertySheet::OnInitDialog();

        // Add a custom buttom to the left of the OK button
    CRect rectOK, rectCancel;

    GetDlgItem( IDOK )->GetWindowRect( &rectOK );
    GetDlgItem( IDCANCEL )->GetWindowRect( &rectCancel );

    INT nMoveX = rectCancel.TopLeft().x - rectOK.BottomRight().x;

    rectOK.OffsetRect( -( rectOK.Width() + nMoveX ), 0 );

    ScreenToClient( &rectOK );

    m_pBtnRun = new CButton;

    DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_TABSTOP;

    m_pBtnRun->Create( RunButtonName, dwStyle, rectOK, this, IDC_CUSTOM );
    m_pBtnRun->SetFont( GetDlgItem( IDOK )->GetFont() );

    return bRetval;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::OnCancel
//
/////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::OnCancel()
{
    DestroyPatternList();   // Deallocate all patterns

    Default();
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::OnApplyNow
//
//  This function is called from the OK button.
//  It will download all the protected data to the
//  current controller object and then exit the dialog.
//
/////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::OnApplyNow()
{
    DownloadSettings();  // Put protected data into current controller

    DestroyPatternList();

    Default();          // Make sure the message is processed

        // Change "Cancel" button to "Close"
    SendMessage( PSM_CANCELTOCLOSE );
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::OnRun
//
//  This function is called from the RUN button.
//  It will download all the protected data to the
//  current controller object, start the data
//  collection process and then exit the dialog.
//
/////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::OnRun() 
{
    DownloadSettings();  // Put protected data into current controller

    DestroyPatternList();

    EndDialog( IDOK );

    Run_WinX_Application();
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::UploadSettings
//
//  Set the protected data in the CSPExpSet Property Sheet
//  based on the current controller settings.
//  If there is no current controller, set defaults even
//  though we should not be able to get here in that case.
//
//////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::UploadSettings()
{
    CONTROLLER *controller;

    if( upload_done == FALSE )
    {
        controller = Get_Current_Controller();
    
        if( controller )
        {
            SHORT store_strobe, shutter_preopen;
            BOOL  dummy;
            CPPWvExSetM AdvancedPage;
            PATTERN_LINK **more_patterns;
            IRCT  irect;
            BOOL  UseXbin, UseYbin;
            BOOL  Only1pattern, Done;

            Exposure            =  controller->Get_actualexposure( controller );
            ExposUnits          =  (SHORT)controller->Get_ExpoTimeUnit( controller );
            Max_Expos           =  controller->Get_maxexposure( controller );
            Expos_Res           =  controller->Inq_Exposure_Resolution( controller, TimeUnit_USEC );
            Synchronous         = !controller->Get_async_sequentials( controller );
            HWAccumAvail        =  controller->Get_HW_present_flag( controller );
            if( HWAccumAvail )
                HWAccum         =  controller->Get_HW_accum_flag( controller );
            else
                HWAccum         =  FALSE;
            NumRuns             =  controller->Get_sequentials( controller );
            if( NumRuns < 1 )
                NumRuns = 1;
            NumAccums           =  controller->Get_accumuls( controller );
            if( NumAccums < 1 )
                NumAccums = 1;
            NumCleans           =  (SHORT)controller->Get_cleanscans( controller );
            TimingMode          =  (SHORT)controller->Get_acqmode( controller );
            KineticsTriggerMode =  (SHORT)controller->Get_Kinetics_TriggerMode( controller );
            SensorMode          =  (SHORT)controller->Get_ContSetup_sensorMode( controller );
            AdvancedPage.Decode_timing_mode( TimingMode,
                                             &dummy,
                                             &store_strobe,
                                             &dummy,
                                             &shutter_preopen );
            StoreStrobe         =  store_strobe;
            ShutterPreOpen      =  shutter_preopen;
            ShutterControl      =  (SHORT)controller->Get_shuttermode( controller );
            UseBackFile         =  controller->Get_ExpSetup_background( controller );
            BackFileName        =  controller->Get_darkname( controller );
            UseFlatFieldFile    =  controller->Get_ExpSetup_flatfield( controller );
            FlatFieldFileName   =  controller->Get_flatfieldname( controller );
            UseBlemishFile      =  controller->Get_ExpSetup_blemish( controller );
            BlemishFileName     =  controller->Get_blemishname( controller );
            if( controller->Get_ExpSetup_tm_cosmic( controller ) == TRUE )
                CosmicRayType   =  2;     // Temporal
            else if( controller->Get_ExpSetup_sp_cosmic( controller ) == TRUE )
                CosmicRayType   =  1;     // Spatial
            else
                CosmicRayType   =  0;     // OFF
            CosmicGrass         =  controller->Get_Cosmic_Grass( controller );
            CosmicThreshold     =  controller->Get_Cosmic_Sensitivity( controller );
            SoftwareBinFlag     =  controller->Get_ExpSetup_softbin( controller );
            X_Max               =  controller->Get_sensor_x( controller );
            Y_Max               =  controller->Get_sensor_y( controller );

            UseXbin = controller->Get_use_accesspattern_x( controller );
            UseYbin = controller->Get_use_accesspattern_y( controller );

				// Set flag if either binning is used
			PixelAccessFlag = UseXbin | UseYbin;

                // If BOTH are OFF, use FULL IMAGE SIZE
            if( ( UseYbin == FALSE ) && ( UseYbin == FALSE ) )
            {
                X_Binned = X_Max;
                Y_Binned = Y_Max;
                Only1pattern = TRUE;
            }
            else
            {
                X_Binned = controller->Get_binned_x( controller );
                Y_Binned = controller->Get_binned_y( controller );
                Only1pattern = FALSE;
            }

            Pattern_Head  = NULL;           // So it's NULL if no patterns
            more_patterns = &Pattern_Head;
            Num_Patterns  = 0;

            Done = FALSE;

            while( ( Done == FALSE ) &&
                   controller->Get_random_access_rect( controller, &irect,
                                                       Num_Patterns + 1 ) )
            {
                if( Only1pattern == TRUE )
                    Done = TRUE;

                Num_Patterns++;

                    // Allocate space and save all patterns
                *more_patterns =
                        (PATTERN_LINK *)Xalloc( sizeof( PATTERN_LINK ), 696 );

                controller->Get_random_access_rect( controller, &irect, Num_Patterns );

                (*more_patterns)->xstart = irect.left;
                (*more_patterns)->xend   = irect.right;
                (*more_patterns)->xgroup = controller->Get_random_groupsize_x(
                                                                 controller,
                                                                 Num_Patterns );
                (*more_patterns)->ystart = irect.top;
                (*more_patterns)->yend   = irect.bottom;
                (*more_patterns)->ygroup = controller->Get_random_groupsize_y(
                                                                 controller,
                                                                 Num_Patterns );
                (*more_patterns)->next   = NULL;

                more_patterns = &(*more_patterns)->next; /* Ready for another */
            }
        }
        else
        {
              // Set defaults...
              //  (even though we should never get here)
            Exposure            = 0.0;
            ExposUnits          = TimeUnit_MSEC;
            Max_Expos           = HIGH_MSEC;
            Expos_Res           = 0.0;
            Synchronous         = FALSE;
            HWAccumAvail        = FALSE;
            HWAccum             = FALSE;
            NumRuns             = 1;
            NumAccums           = 1;
            NumCleans           = 0;
            TimingMode          = CTRL_FREERUN;
            SensorMode          = 0;
            KineticsTriggerMode = 0;
            StoreStrobe         = FALSE;
            ShutterPreOpen      = FALSE;
            ShutterControl      = SHUTTER_NORMAL;
            UseBackFile         = FALSE;
            BackFileName.Empty();
            UseFlatFieldFile    = FALSE;
            FlatFieldFileName.Empty();
            UseBlemishFile      = FALSE;
            BlemishFileName.Empty();
            CosmicRayType       = 0;      // OFF
            CosmicThreshold     = 50.;    // Arbitrary
            CosmicGrass         = 0.25;   // Arbitrary
            PixelAccessFlag     = FALSE;
            SoftwareBinFlag     = FALSE;
            X_Max               = MAX_INT;
            Y_Max               = MAX_INT;
            X_Binned            = MAX_INT;
            Y_Binned            = MAX_INT;

            Pattern_Head = NULL;
            Num_Patterns = 0;
        }

        upload_done = TRUE;   // Don't do this again
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::DownloadSettings
//
//  Collect the data from the dialog, load it into the current
//  controller BUT don't start the run.  Exit the dialog.
//
//////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::DownloadSettings()
{
    SHORT cosmic_sp, cosmic_tm;
                    // DOWNLOAD PATTERNS HERE FIRST !!!

    CONTROLLER *controller;

    controller = Get_Current_Controller();
    
    if( controller )
    {
        IRCT pattern_rect;
        BOOL first_pattern = TRUE;
        PATTERN_LINK **Next_pattern;
            
                        // Load the access patterns
        Next_pattern = &Pattern_Head;

        while( *Next_pattern != NULL )
        {
            if( first_pattern == TRUE )
            {
                    // First clear out all current patterns
                controller->Clear_accesspattern( controller );

                controller->Set_groupsize_x( controller, (*Next_pattern)->xgroup );
                controller->Set_groupsize_y( controller, (*Next_pattern)->ygroup );

                    // Set flags that there is at least 1 pattern
                controller->Set_use_accesspattern_x( controller, PixelAccessFlag );
                controller->Set_use_accesspattern_y( controller, PixelAccessFlag );

                first_pattern = FALSE;      // Don't do this again
            }
            
                // Load the IRCT structure
            pattern_rect.top    = (*Next_pattern)->ystart;
            pattern_rect.left   = (*Next_pattern)->xstart;
            pattern_rect.bottom = (*Next_pattern)->yend;
            pattern_rect.right  = (*Next_pattern)->xend;

                // Load it into the controller object
            controller->Set_image_access_rect( controller, &pattern_rect );

            Next_pattern = &(*Next_pattern)->next;       // Look for next one

        }                        // END while( *Next_pattern != NULL )
    }                            // END if( controller )

    switch( CosmicRayType )
    {
        case 0:               // OFF
            cosmic_sp = 0;
            cosmic_tm = 0;
            break;

        case 1:               // Temporal
            cosmic_sp = 0;
            cosmic_tm = 1;
            break;

        case 2:               // Spatial
            cosmic_sp = 1;
            cosmic_tm = 0;
            break;
    }

       // Set up timing mode based on StoreStrobe, ShutterPreopen and Kinetics
    Encode_Timing_Mode();

    Experiment_setup_download( Exposure,
                               ExposUnits,
                               FALSE,
                               Synchronous,
                               NumRuns,
                               NumAccums,
                               NumCleans,
                               TimingMode,
                               KineticsTriggerMode,
                               ShutterControl,
                               UseBackFile,
                               (char *)(LPCSTR)BackFileName,
                               0,               // NOT_DEFINED
                               UseFlatFieldFile,
                               (char *)(LPCSTR)FlatFieldFileName,
                               0,               // NOT_DEFINED
                               PixelAccessFlag,
                               0,       // ystart   // Patterns Defined Above...
                               0,       // xstart
                               0,       // yend
                               0,       // xend
                               0,       // xgroup
                               0,       // ygroup
                               HWAccum,
                               UseBlemishFile,
                               (char *)(LPCSTR)BlemishFileName,
                               cosmic_sp,   
                               (float)CosmicThreshold,
                               (float)CosmicGrass,
                               cosmic_tm,
                               SoftwareBinFlag,
                               TRUE                     // always INIT!
                               );    

}


/////////////////////////////////////////////////////////////////////////////
//
//  PROPERTY SHEET FUNCTION:
//
//              CPSWvExSet::Encode_Timing_Mode
//
//  This function will prepare the timing mode variable for
//  downloading to the controller object by encoding the
//  timing mode chosen, the store strobe and the shutter
//  preopen values and storing the result in the TimingMode.
//
//////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::Encode_Timing_Mode()
{
        // If Kinetics Mode, set Kinetics Trigger & Timing Mode
    if( SensorMode == ROM_KINETICS )
    {
        KineticsTriggerMode = TimingMode;

        if( KineticsTriggerMode == KINETICS_NO_TRIGGER )
            TimingMode = CTRL_FREERUN;
        else
            TimingMode = CTRL_EXTSYNC;
    }
    else
    {
        switch( TimingMode )
        {
            case CTRL_FREERUN:
                if( StoreStrobe == FALSE )
                    TimingMode = CTRL_FREERUN;
                else
                    TimingMode = CTRL_FR_STORE_TRIG;
                break;

            case CTRL_LINESYNC:            // Here for completeness
                TimingMode = CTRL_LINESYNC;
                break;

            case CTRL_EXTSYNC:
                switch( StoreStrobe )
                {
                    case FALSE:
                        if( ShutterPreOpen == FALSE )
                            TimingMode = CTRL_EXTSYNC_NORMAL;
                        else
                            TimingMode = CTRL_EXTSYNC_PREOPEN;
                        break;

                    case TRUE:
                        if( ShutterPreOpen == FALSE )
                            TimingMode = CTRL_SN_STORE_TRIG;
                        else
                            TimingMode = CTRL_SP_STORE_TRIG;
                        break;
                }
            break;

            case CTRL_EXTTRIG:
                switch( StoreStrobe )
                {
                    case FALSE:
                        if( ShutterPreOpen == FALSE )
                            TimingMode = CTRL_EXTTRIG_NORMAL;
                        else
                            TimingMode = CTRL_EXTTRIG_PREOPEN;
                        break;

                    case TRUE:
                        if( ShutterPreOpen == FALSE )
                            TimingMode = CTRL_TN_STORE_TRIG;
                        else
                            TimingMode = CTRL_TP_STORE_TRIG;
                        break;
                }
                break;

            case CTRL_EXTSHUTTER_CONTROL:  // Here for completeness
                TimingMode = CTRL_EXTSHUTTER_CONTROL;

            default:
                TimingMode = CTRL_FREERUN;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
// CPSWvExSet::DestroyPatternList
//
/////////////////////////////////////////////////////////////////////////////

void CPSWvExSet::DestroyPatternList()
{
    PATTERN_LINK *more_patterns, *this_pattern;

    more_patterns = Pattern_Head;

    while( more_patterns != NULL )
    {
        this_pattern  = more_patterns;       // Save current address

        more_patterns = more_patterns->next; // Point to next one

        Xfree( this_pattern );               // Free current structure
    }

    Pattern_Head = NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// CPSWvExSet::Set_Binning_Sizes
//
/////////////////////////////////////////////////////////////////////////////

//void CPSWvExSet::Set_Binning_Sizes()
//{
//  if (controller->ExpSetupStatus & SOFTWARE_BINNING_BIT)
//    {
//    if (controller->image_mapping & IMAGE_ROTATE)
//                                /* if rotate take y dimension for x.       */
//      Get_Dim_Raw_Dat(controller->use_access_pattern_y,
//                      controller->numberOfImageLine,
//                      controller->ascend_y_image_hd,
//                      &numberOfX,
//                      Y_DIM,
//                      FALSE);   /* Flag no software binning. */
//    else
//      Get_Dim_Raw_Dat(controller->use_access_pattern_x,
//                      controller->numberOfImageStripe,
//                      controller->ascend_x_image_hd,
//                      &numberOfX,
//                      X_DIM,
//                      FALSE);
//    }
//  else                        /* Else, use the possibly overlaid function. */
//    numberOfX = controller->Get_pixeldimension_x(controller);
//
//
//  
//    PATTERN_LINK **more_patterns;
//    SHORT num_done = 0;
//    SHORT xstart, xend, xgroup;
//    SHORT ystart, yend, ygroup;
//    INT   Old_ROI_end, ROI_start, ROI_end, binning;
//    INT   X_size = 0, Y_size = 0;
//
//    more_patterns = &Pattern_Head;
//
//            // Loop through ALL patterns & count 'em up
//    while( *more_patterns != NULL )
//    {
//        num_done++;
//
//        xstart = (*more_patterns)->xstart;
//        xend   = (*more_patterns)->xend;
//        xgroup = (*more_patterns)->xgroup;
//
//        ystart = (*more_patterns)->ystart;
//        yend   = (*more_patterns)->yend;
//        ygroup = (*more_patterns)->ygroup;
//
//
//        more_patterns = &(*more_patterns)->next;        // Go get another
//
//        Old_ROI_end = -1;
//
//        if( dir_flag == Y_DIM )
//        {
//            ROI_start = ystart;
//            ROI_end   = yend;
//            binning   = sw_binning ? 1 : ygroup;
//        }
//        else
//        {
//            ROI_start = xstart;
//            ROI_end   = xend;
//            binning   = sw_binning ? 1 : xgroup;
//        }
//
//          if( ROI_end > Old_ROI_end )
//          {
//                          /* make sure we don't program same point */
//                          /* multiple times.                       */
//              if (ROI_start <= Old_ROI_end)
//                  ROI_start = Old_ROI_end + 1;
//
//                          /*--- Add the Region Of Interest */
//              valid_cntr  += (ROI_end - ROI_start + 1) / binning;
//
//          }               /* Update Old_ROI_end */
//          Old_ROI_end = ROI_end;
//      }             /* end while still more in linked list */
//  } /* end if-else */
//                          /* Update the super line counts */
//  *numberOfPixels = valid_cntr;
//
//}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::CPPWvExSet()
//
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPPWvExSet, CPropertyPage)

CPPWvExSet::CPPWvExSet() : CPropertyPage(CPPWvExSet::IDD)
{
    //{{AFX_DATA_INIT(CPPWvExSet)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::~CPPWvExSet()
//
/////////////////////////////////////////////////////////////////////////////

CPPWvExSet::~CPPWvExSet()
{
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::DoDataExchange
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPPWvExSet)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE MESSAGE MAP
//
//              CPPWvExSet
//
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPPWvExSet, CPropertyPage)
    //{{AFX_MSG_MAP(CPPWvExSet)
    ON_WM_HSCROLL()         // Handles ALL Slider controls
    ON_EN_CHANGE(     IDC_ETEDIT,   OnChangeEtedit     )
    ON_CBN_SELCHANGE( IDC_ETUNITS,  OnSelchangeEtunits )
    ON_BN_CLICKED(    IDC_PDCHECK,  OnPdcheck          )
    ON_BN_CLICKED(    IDC_PDBUTTON, OnPdbutton         )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnHScroll
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::OnHScroll
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

    if( SliderID == IDC_EXPOS_SLIDER )
    {
            // Set the new value in the edit box
            // Note: Exposure is not set until SET button is hit
        PropSheet().Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
        DisplayText.Format( Gstring, PropSheet().Exposure );
        SetDlgItemText( IDC_ETEDIT, DisplayText );
    }

    if( nPos || nSBCode );           // Get rid of compiler warnings
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSet::OnInitDialog() 
{
    double  expos_res;
    SHORT   list_index, offset, idx, resource_id;
    CHAR    tmpbuffer[MAX_PATH_LEN];  // For RESOURCE
    CString CStrExpos;

        // Load protected data from the current controller
    PropSheet().UploadSettings();

          // Load Exposure Time Units Combo Box
          //   TimeUnit_USEC = 1, TimeUnit_MSEC = 2,
          //   TimeUnit_SEC  = 3, TimeUnit_MIN  = 4,
          //   TimeUnit_HOUR = 5

            // Include USEC only if supported by controller
    expos_res = PropSheet().Expos_Res;

    if( expos_res == 0.0 )
    {
        offset = 1;         // Start at 2nd string ID
        idx    = 2;         // Start after USEC
    }
    else
    {
        offset = 0;         // No offset in string ID
        idx    = 1;         // USEC is 1
    }

    for( resource_id  = XPI_EXPTIME_UNIT_START + offset;
         resource_id <= XPI_EXPTIME_UNIT_END;
         resource_id++, idx++ )
    {
              // Get the string from resource
        RESOURCE( resource_id );

              // Add the string and get back an index (position)
        list_index = (SHORT)ETunits_ComboBox().AddString( tmpbuffer );

              // Set the data item for this string
        ETunits_ComboBox().SetItemData( list_index, idx );
    }

              // Now set the current units as selected
              // Also set the static variable so we know what to convert
              // FROM when units are changed. (selection # is 0 based)
    ETunits_ComboBox().SetCurSel( PropSheet().ExposUnits - offset - 1 );
  
            // Display the current exposure
    CStrExpos.Format( Gstring, PropSheet().Exposure );
    SetDlgItemText( IDC_ETEDIT, CStrExpos );

            // Load limits into sliders
    SetExposSliderRange( PropSheet().ExposUnits, &expos_factor, &Roundoff,
                         &max_slide, &Expos_Slider() );
    SetExposSliderPos( &PropSheet().Exposure, expos_factor, Roundoff,
                       max_slide, &Expos_Slider() );

            // Set the pixel access flag & enable/disable button
    PixDef_CheckBox().SetCheck( PropSheet().PixelAccessFlag );
    OnPdcheck();

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnSetActive
//
//  This function will recopy the data which may
//  have been changed from within the Advanced page.
//
/////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSet::OnSetActive()
{
    CString CStrExpos;
    SHORT   current_value;
    INT     num_items, idx;

    CStrExpos.Format( Gstring, PropSheet().Exposure );
    SetDlgItemText( IDC_ETEDIT, CStrExpos );

    current_value = PropSheet().ExposUnits;

        // Find which item's ID is the same as the current value
    num_items = ETunits_ComboBox().GetCount();
    for( idx = 0; idx < num_items; idx++ )
        if( (SHORT)ETunits_ComboBox().GetItemData( idx ) == current_value )
            ETunits_ComboBox().SetCurSel( idx );

    PixDef_CheckBox().SetCheck( PropSheet().PixelAccessFlag );
    OnPdcheck();

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnChangeEtedit
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::OnChangeEtedit()
{
    CString temp_str;
    SHORT   num_chars;
    double  tmp_expos;

    num_chars = (SHORT)GetDlgItemText( IDC_ETEDIT, temp_str );

    if( num_chars > 0 )
    {
        char *end_str;

        tmp_expos = strtod( temp_str, &end_str );

           // Will fail if decimal is the first char so allow it to pass
        if( ( *end_str != 0 ) && ( *end_str != '.' ) )
        {
            Error_report( X_ERROR, XR_MSG_INVALID_INP, NULL );
        }
        else
        {
            PropSheet().Exposure = tmp_expos;
            SetExposSliderPos( &PropSheet().Exposure, expos_factor, Roundoff,
                               max_slide, &Expos_Slider() );
        }
    }
    else
    {
        PropSheet().Exposure = 0.0;
        SetExposSliderPos( &PropSheet().Exposure, expos_factor, Roundoff,
                           max_slide, &Expos_Slider() );
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnSelchangeEtunits
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::OnSelchangeEtunits()
{
    SHORT   list_idx, new_units, num_chars;
    CString exposure_str;
    double  exposure, new_exposure;
    double  min_change, line_change, page_change, max_value;
    CString CStrExpos;

        // First, find out what units were selected
    list_idx  = (SHORT)ETunits_ComboBox().GetCurSel();
    new_units = (SHORT)ETunits_ComboBox().GetItemData( list_idx );

        // Now, get the current exposure time
    num_chars = (SHORT)GetDlgItemText( IDC_ETEDIT, exposure_str );

    if( num_chars > 0 )
    {
        exposure = strtod( exposure_str, NULL );

            // Convert the current exposure to the new units
        new_exposure = ConvertTime( exposure,
                                    PropSheet().ExposUnits, new_units,
                                    &min_change, &line_change,
                                    &page_change, &max_value,
                                    PropSheet().Expos_Res,
                                    PropSheet().Max_Expos );

        CStrExpos.Format( Gstring, new_exposure );
        SetDlgItemText( IDC_ETEDIT,  CStrExpos );

        SetExposSliderRange( new_units, &expos_factor, &Roundoff,
                             &max_slide, &Expos_Slider() );
        SetExposSliderPos( &new_exposure, expos_factor, Roundoff,
                           max_slide, &Expos_Slider() );

        PropSheet().ExposUnits = new_units;
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnPdcheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::OnPdcheck()
{
    SHORT check_value;
    CONTROLLER *controller;

    check_value = (SHORT)PixDef_CheckBox().GetCheck();

    PropSheet().PixelAccessFlag = check_value;

       // DISABLE or ENABLE control for Pixel Definition
    PixDef_Button().EnableWindow( check_value );

    controller = Get_Current_Controller();

    if( controller )
    {
            // Set controller use of access pattern
        controller->Set_use_accesspattern_x( controller, check_value );
        controller->Set_use_accesspattern_y( controller, check_value );
    }

        // FALSE = Display FULL Chip Dims, TRUE = Display ACCESSED Chip Dims
    Set_access_pattern_txt( check_value );    
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::OnPdbutton
//
//  This function is called if the Pixel Definition Button
//  is hit in either the basic property page.  It will call
//  Do_PixDef_Dlg() to display the Modal dialog 
//  for pixel definition.  The dialog will handle all error checking
//  and store any patterns.
//  This function will then access the current controller patterns
//  and display the image size (X/Y) in the IDC_PDSIZE_TXT text box.
//
//////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::OnPdbutton()
{
    Do_PixDef_Dlg();

        // Set the X & Y binning sizes & then display them
////    Set_Binning_Sizes();
    
    Set_access_pattern_txt( TRUE );     // Display binned values
}


/////////////////////////////////////////////////////////////////////////////
//
//  BASIC PAGE FUNCTION:
//
//              CPPWvExSet::Set_access_pattern_txt
//
//  These functions will display FULL or ACCESSED Chip Dimensions
//  in the Pixel Definition Text Box (to right of PixDef Button)
//  There is an implementation for each dialog in the property sheet.
//  This should be fixed when possible.,..
//
//////////////////////////////////////////////////////////////////////////////

void CPPWvExSet::Set_access_pattern_txt
    (
    SHORT flag    // TRUE = Show Accessed Dims, FALSE = Show FULL Dims
    )
{
    CString Pix_Def_text;
    INT x_size, y_size;

    if( flag == TRUE )
    {
        x_size = PropSheet().X_Binned;
        y_size = PropSheet().Y_Binned;
    }
    else
    {
        x_size = PropSheet().X_Max;
        y_size = PropSheet().Y_Max;
    }

    Pix_Def_text.Format( PixDefFormat, x_size, y_size );

    SetDlgItemText( IDC_PDSIZE_TXT, Pix_Def_text );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::CPPWvExSetM
//
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPPWvExSetM, CPropertyPage)

CPPWvExSetM::CPPWvExSetM() : CPropertyPage(CPPWvExSetM::IDD)
{
    //{{AFX_DATA_INIT(CPPWvExSetM)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::~CPPWvExSetM
//
/////////////////////////////////////////////////////////////////////////////

CPPWvExSetM::~CPPWvExSetM()
{
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::DoDataExchange
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPPWvExSetM)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE MESSAGE MAP
//
//              CPPWvExSetM
//
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPPWvExSetM, CPropertyPage)
    //{{AFX_MSG_MAP(CPPWvExSetM)
    ON_EN_CHANGE(     IDC_ETEDITM,            OnChangeEtedit            )
    ON_CBN_SELCHANGE( IDC_ETUNITSM,           OnSelchangeEtunits        )
    ON_BN_CLICKED(    IDC_SYNC_CHK,           OnSyncChk                 )
    ON_BN_CLICKED(    IDC_HWACCUM_CHK,        OnHwaccumChk              )
    ON_EN_CHANGE(     IDC_NUMSHOTS_EDIT,      OnChangeNumshotsEdit      )
    ON_EN_CHANGE(     IDC_NUMACCUMS_EDIT,     OnChangeNumaccumsEdit     )
    ON_EN_CHANGE(     IDC_CLEANS_EDIT,        OnChangeCleansEdit        )
    ON_CBN_SELCHANGE( IDC_TIMINGMODE_CB,      OnSelchangeTimingmodeCb   )
    ON_BN_CLICKED(    IDC_STORESTROBE_CHK,    OnStorestrobeChk          )
    ON_CBN_SELCHANGE( IDC_SHUTTERCNTRL_CB,    OnSelchangeShuttercntrlCb )
    ON_BN_CLICKED(    IDC_PREOPEN_CHECK,      OnPreopenCheck            )
    ON_BN_CLICKED(    IDC_BKGD_CHECK,         OnBkgdCheck               )
    ON_MESSAGE(       WM_BACKEDIT_LOSTFOCUS,  OnBackEditLostFocus       )
    ON_EN_KILLFOCUS(  IDC_BKGDFILE_EDIT,      OnKillfocusBackNameEd     )
    ON_BN_CLICKED(    IDC_BKGDFILE_BUTTON,    OnBkgdfileButton          )
    ON_BN_CLICKED(    IDC_FLATFLD_CHECK,      OnFlatfldCheck            )
    ON_MESSAGE(       WM_FLATEDIT_LOSTFOCUS,  OnFlatEditLostFocus       )
    ON_EN_KILLFOCUS(  IDC_FLATFLDFILE_EDIT,   OnKillfocusFlatNameEd     )
    ON_BN_CLICKED(    IDC_FLATFLDFILE_BUTTON, OnFlatfldfileButton       )
    ON_BN_CLICKED(    IDC_BLEMISH_CHECK,      OnBlemishCheck            )
    ON_MESSAGE(       WM_BLEMEDIT_LOSTFOCUS,  OnBlemEditLostFocus       )
    ON_EN_KILLFOCUS(  IDC_BLEMISHFILE_EDIT,   OnKillfocusBlemNameEd     )
    ON_BN_CLICKED(    IDC_BLEMISHFILE_BUTTON, OnBlemishfileButton       )
    ON_BN_CLICKED(    IDC_COSMIC_TEMPORAL_RB, OnCosmicTemporalRb        )
    ON_BN_CLICKED(    IDC_COSMIC_SPATIAL_RB,  OnCosmicSpatialRb         )
    ON_BN_CLICKED(    IDC_COSMIC_OFF_RB,      OnCosmicOffRb             )
    ON_EN_CHANGE(     IDC_COSMIC_THRESH_EDIT, OnChangeCosmicThreshEdit  )
    ON_BN_CLICKED(    IDC_PDCHECKM,           OnPdcheck                 )
    ON_BN_CLICKED(    IDC_PDBUTTONM,          OnPdbutton                )
    ON_BN_CLICKED(    IDC_SOFTBIN_CHECK,      OnSoftbinCheck            )
    ON_WM_HSCROLL()     // Handles The Exposure Slider Control
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSetM::OnInitDialog() 
{
    double  expos_res;
    SHORT   store_strobe, shutter_preopen;
    BOOL    store_strobe_avail, shutter_preopen_avail;
    SHORT   list_index, offset, idx, resource_id;
    CHAR    tmpbuffer[MAX_PATH_LEN];    // For RESOURCE
    CHAR    drive[_MAX_DRIVE];
    CHAR    dir[_MAX_DIR];
    CHAR    fname[_MAX_FNAME];
    CHAR    ext[_MAX_EXT];
    CString path;
    BOOL    temporal_flag;
    BOOL    spatial_flag;
    BOOL    off_flag;
    CString CStrReal;

        // Load protected data from the current controller
    PropSheet().UploadSettings();

        // Set up an accelerator array for use by several spin buttons
        // Changes increment every 5 seconds to from 1 to 10 and 100
        // (Do this BEFORE setting the defaults in the dialog)
    UDACCEL AccelArray[3] = { { 0, 1 }, { 5, 10 }, { 10, 100 } };

      // Set up the number of images/spectra spin button
          // Set the acceleration & Range
    NumShots_Spin().SetAccel( 3, &AccelArray[0] );
    NumShots_Spin().SetRange( 1, UD_MAXVAL );

      // Set up the number of accumulations spin button
          // Set the acceleration & Range
    NumAccums_Spin().SetAccel( 3, &AccelArray[0] );
    NumAccums_Spin().SetRange( 1, UD_MAXVAL );

      // Set up the number of cleans spin button
          // Set the acceleration & Range
    NumCleans_Spin().SetAccel( 3, &AccelArray[0] );
    NumCleans_Spin().SetRange( 0, 1000 );

      // Set up the threshold % spin button
          // Set the acceleration & Range
    CosThresh_Spin().SetAccel( 3, &AccelArray[0] );
    CosThresh_Spin().SetRange( 0, 100 );

      // Display the correct text for number of images/spectra
    CWXString WinXResource;

    if( (SHORT)Get_resource_value( I_AM_WINSPEC ) )
        WinXResource.LoadString( XPI_NUM_OF_SPECTRA );
    else
        WinXResource.LoadString( XPI_NUM_OF_IMAGES );

    SetDlgItemText( IDC_NUMSHOTS_TXT, WinXResource );

       // Load dialog with current values from Property Sheet data

          // Load timing mode combo box with choices
          // and set current timing mode as selected
    Setup_timing_mode( PropSheet().TimingMode,
                       &store_strobe_avail,
                       &store_strobe,
                       &shutter_preopen_avail,
                       &shutter_preopen );

          // Set the store strobe & shutter pre-open values
          // They are NOT saved directly in the controller object
          // but are derived from the timing mode.

    if( store_strobe_avail == FALSE )
        store_strobe = FALSE;
    StoreStrobe_CheckBox().SetCheck( store_strobe );
    StoreStrobe_CheckBox().EnableWindow( store_strobe_avail );
    PropSheet().StoreStrobe = store_strobe;  // Set data in the class

    if( shutter_preopen_avail == FALSE )
        shutter_preopen = FALSE;
    ShutterPreOpen_CheckBox().SetCheck( shutter_preopen );
    ShutterPreOpen_CheckBox().EnableWindow( shutter_preopen_avail );
    PropSheet().ShutterPreOpen = shutter_preopen;

          // Load Exposure Time Units Combo Box
          //   TimeUnit_USEC = 1, TimeUnit_MSEC = 2,
          //   TimeUnit_SEC  = 3, TimeUnit_MIN  = 4,
          //   TimeUnit_HOUR = 5

            // Include USEC only if supported by controller
    expos_res = PropSheet().Expos_Res;

    if( expos_res == 0.0 )
    {
        offset = 1;         // Start at 2nd string ID
        idx    = 2;         // Start after USEC
    }
    else
    {
        offset = 0;         // No offset in string ID
        idx    = 1;         // USEC is 1
    }

    for( resource_id  = XPI_EXPTIME_UNIT_START + offset;
         resource_id <= XPI_EXPTIME_UNIT_END;
         resource_id++, idx++ )
    {
              // Get the string from resource
        RESOURCE( resource_id );

              // Add the string and get back an index (position)
        list_index = (SHORT)ETunits_ComboBox().AddString( tmpbuffer );

              // Set the data item for this string
        ETunits_ComboBox().SetItemData( list_index, idx );
    }

              // Now set the current units as selected
              // Also set the static variable so we know what to
              // convert FROM when units are changed.
              // (selection # is 0 based)
    ETunits_ComboBox().SetCurSel( PropSheet().ExposUnits - offset - 1 );

            // Set the range on the exposure edit box based on
            // the current units.
    CStrReal.Format( Gstring, PropSheet().Exposure );
    SetDlgItemText( IDC_ETEDITM, CStrReal );

            // Load limits into sliders
    SetExposSliderRange( PropSheet().ExposUnits, &expos_factor, &Roundoff,
                         &max_slide, &Expos_Slider() );
    SetExposSliderPos( &PropSheet().Exposure, expos_factor, Roundoff,
                       max_slide, &Expos_Slider() );

        // Load the strings & ids for the shutter control combo box
        // SHUTTER_NORMAL = 1, SHUTTER_CLOSE = 2,
        // SHUTTER_DISABLED_OPEN = 3
    idx = 1;
    for( resource_id  = X_SHUTTERMODE_LBL_START;
         resource_id <= X_SHUTTERMODE_LBL_END;
         resource_id++, idx++ )
    {
              // Get the string from resource
        RESOURCE( resource_id );

              // Add the string and get back an index (position)
        list_index = (SHORT)ShutterControl_ComboBox().AddString( tmpbuffer );

              // Set the data item for this string
        ShutterControl_ComboBox().SetItemData( list_index, idx );
    }
        // Set the current units as defined in the controller
        // (selection # is 0 based)
    ShutterControl_ComboBox().SetCurSel( PropSheet().ShutterControl - 1 );

        // Set the HW Accum check box (enabled only if HW Accum available)
    HWAccum_CheckBox().SetCheck( PropSheet().HWAccum );
    HWAccum_CheckBox().EnableWindow( PropSheet().HWAccumAvail );

        // Set synchronous flag as defined in controller
    Synchronous_CheckBox().SetCheck( PropSheet().Synchronous );

        // Set number of Images/Spectra as defined in controller
    NumShots_Spin().SetPos( PropSheet().NumRuns );
    NumShots_Spin().SetBuddy( (CWnd*)GetDlgItem( IDC_NUMSHOTS_EDIT ) );
    SetDlgItemInt( IDC_NUMSHOTS_EDIT, PropSheet().NumRuns, TRUE );

        // Set number of Accumulations as defined in controller
    NumAccums_Spin().SetPos( PropSheet().NumAccums );
    NumAccums_Spin().SetBuddy( (CWnd*)GetDlgItem( IDC_NUMACCUMS_EDIT ) );
    SetDlgItemInt( IDC_NUMACCUMS_EDIT, PropSheet().NumAccums, TRUE );

        // Set number of Cleans as defined in controller
    NumCleans_Spin().SetPos( PropSheet().NumCleans );
    NumCleans_Spin().SetBuddy( (CWnd*)GetDlgItem( IDC_CLEANS_EDIT ) );
    SetDlgItemInt( IDC_CLEANS_EDIT, PropSheet().NumCleans, TRUE );

        // Set Background File and flag based on file's existence
    if( PropSheet().BackFileName.IsEmpty() )
    {
        PropSheet().UseBackFile = FALSE;
    }
    else
    {
            // A name exists, so split off the and & path and display them
        _splitpath( PropSheet().BackFileName, drive, dir, fname, ext );
        CString FullName = fname;
        FullName += ext;
        SetDlgItemText( IDC_BKGDFILE_EDIT, FullName );
        path  = drive;
        path += dir;
        SetDlgItemText( IDC_BKGDFILEPATH_TXT, path );

        if( CFileFind().FindFile( PropSheet().BackFileName, 0 ) )
        {
            PropSheet().UseBackFile = TRUE;
        }
        else
        {
            CString ErrorMessage = BackFileMsg +
                                   PropSheet().BackFileName + NotExistMsg;
            Error_report( X_INFORMATION, LOCAL_STRING, (void *)(LPCSTR)ErrorMessage );
            PropSheet().UseBackFile = FALSE;
        }
    }
    BkGrnd_CheckBox().SetCheck( PropSheet().UseBackFile );
    OnBkgdCheck();

            // Set FlatField File and flag based on file's existence
    if( PropSheet().FlatFieldFileName.IsEmpty() )
    {
        PropSheet().UseFlatFieldFile = FALSE;
    }
    else
    {
            // A name exists, so split off the and & path and display them
        _splitpath( PropSheet().FlatFieldFileName, drive, dir, fname, ext );
        CString FullName = fname;
        FullName += ext;
        SetDlgItemText( IDC_FLATFLDFILE_EDIT, FullName );
        path  = drive;
        path += dir;
        SetDlgItemText( IDC_FLATFLDFILEPATH_TXT, path );

        if( CFileFind().FindFile( PropSheet().FlatFieldFileName, 0 ) )
        {
            PropSheet().UseFlatFieldFile = TRUE;
        }
        else
        {
            CString ErrorMessage = FlatFieldFileMsg +
                                   PropSheet().FlatFieldFileName + NotExistMsg;
            Error_report( X_INFORMATION, LOCAL_STRING, (void *)(LPCSTR)ErrorMessage );
            PropSheet().UseFlatFieldFile = FALSE;
        }
    }
    FlatFld_CheckBox().SetCheck( PropSheet().UseFlatFieldFile );
    OnFlatfldCheck();

            // Set Blemish File and flag based on file's existence
    if( PropSheet().BlemishFileName.IsEmpty() )
    {
        PropSheet().UseBlemishFile = FALSE;
    }
    else
    {
            // A name exists, so split off the and & path and display them
        _splitpath( PropSheet().BlemishFileName, drive, dir, fname, ext );
        CString FullName = fname;
        FullName += ext;
        SetDlgItemText( IDC_BLEMISHFILE_EDIT, FullName );
        path  = drive;
        path += dir;
        SetDlgItemText( IDC_BLEMISHFILEPATH_TXT, path );

        if( CFileFind().FindFile( PropSheet().BlemishFileName, 0 ) )
        {
            PropSheet().UseBlemishFile = TRUE;
        }
        else
        {
            CString ErrorMessage = BlemishFileMsg +
                                   PropSheet().BlemishFileName + NotExistMsg;
            Error_report( X_INFORMATION, LOCAL_STRING, (void *)(LPCSTR)ErrorMessage );
            PropSheet().UseBlemishFile = FALSE;
        }
    }
    BlemFile_CheckBox().SetCheck( PropSheet().UseBlemishFile );
    OnBlemishCheck();

        // Set the pixel access flag & enable/disable button
    PixDef_CheckBox().SetCheck( PropSheet().PixelAccessFlag );
    OnPdcheck();

    switch( PropSheet().CosmicRayType )
    {
        case 1:                     // Temporal
            temporal_flag = TRUE;
            spatial_flag  = FALSE;
            off_flag      = FALSE;
            break;

        case 2:                     // Spatial
            temporal_flag = FALSE;
            spatial_flag  = TRUE;
            off_flag      = FALSE;
            break;

        default:                    // Off & Default
            temporal_flag = FALSE;
            spatial_flag  = FALSE;
            off_flag      = TRUE;
    }
    Cosmic_Temporal_RB().SetCheck( temporal_flag );
    Cosmic_Spatial_RB().SetCheck( spatial_flag );
    Cosmic_Off_RB().SetCheck( off_flag );
    
       // Enable cosmic threshold only if spatial
    CosmicThreshEnableDisable( spatial_flag );

    CosThresh_Spin().SetPos( (int)PropSheet().CosmicThreshold );
    CosThresh_Spin().SetBuddy( (CWnd*)GetDlgItem( IDC_COSMIC_THRESH_EDIT ) );
    CStrReal.Format( Gstring, PropSheet().CosmicThreshold );
    SetDlgItemText( IDC_COSMIC_THRESH_EDIT, CStrReal );

       // Set the software binning checkbox
    SoftwareBin_CheckBox().SetCheck( PropSheet().SoftwareBinFlag );

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnSetActive
//
//  This function will recopy the data which may
//  have been changed from within the Basic page.
//
/////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSetM::OnSetActive()
{
    CString CStrExpos;
    SHORT   current_value;
    INT     num_items, idx;

    CStrExpos.Format( Gstring, PropSheet().Exposure );
    SetDlgItemText( IDC_ETEDITM, CStrExpos );

    current_value = PropSheet().ExposUnits;

        // Find which item's ID is the same as the current value
    num_items = ETunits_ComboBox().GetCount();
    for( idx = 0; idx < num_items; idx++ )
        if( (SHORT)ETunits_ComboBox().GetItemData( idx ) == current_value )
            ETunits_ComboBox().SetCurSel( idx );

    PixDef_CheckBox().SetCheck( PropSheet().PixelAccessFlag );
    OnPdcheck();

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//      CPPWvExSetM::OnHScroll
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnHScroll
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

    if( SliderID == IDC_EXPOS_SLIDERM )
    {
            // Set the new value in the edit box
            // Note: Exposure is not set until SET button is hit
        PropSheet().Exposure = ( (double)SlidePos ) / ( (double)expos_factor );
        DisplayText.Format( Gstring, PropSheet().Exposure );
        SetDlgItemText( IDC_ETEDITM, DisplayText );
    }

    if( nPos || nSBCode );           // Get rid of compiler warnings
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnChangeEtedit
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnChangeEtedit() 
{
    CString temp_str;
    SHORT   num_chars;
    double  tmp_expos;

    num_chars = (SHORT)GetDlgItemText( IDC_ETEDITM, temp_str );

    if( num_chars > 0 )
    {
        CHAR *end_str;

        tmp_expos = strtod( temp_str, &end_str );

           // Will fail if decimal is the first char so allow it to pass
        if( ( *end_str != 0 ) && ( *end_str != '.' ) )
            Error_report( X_ERROR, XR_MSG_INVALID_INP, NULL );
        else
        {
            PropSheet().Exposure = tmp_expos;
            SetExposSliderPos( &PropSheet().Exposure, expos_factor, Roundoff,
                               max_slide, &Expos_Slider() );
        }
    }
    else
    {
        PropSheet().Exposure = 0.0;
        SetExposSliderPos( &PropSheet().Exposure, expos_factor, Roundoff,
                           max_slide, &Expos_Slider() );
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnSelchangeEtunits
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnSelchangeEtunits()
{
    SHORT   list_idx, new_units, num_chars;
    double  exposure, new_exposure;
    double  min_change, line_change, page_change, max_value;
    CString exposure_str;
    CString CStrExpos;

        // First, find out what units were selected
    list_idx  = (SHORT)ETunits_ComboBox().GetCurSel();
    new_units = (SHORT)ETunits_ComboBox().GetItemData( list_idx );

        // Now, get the current exposure time
    num_chars = (SHORT)GetDlgItemText( IDC_ETEDITM, exposure_str );

    if( num_chars > 0 )
    {
        exposure = strtod( exposure_str, NULL );

            // Convert the current exposure to the new units
        new_exposure = ConvertTime( exposure,
                                    PropSheet().ExposUnits, new_units,
                                    &min_change, &line_change,
                                    &page_change, &max_value,
                                    PropSheet().Expos_Res,
                                    PropSheet().Max_Expos );

        CStrExpos.Format( Gstring, new_exposure );
        SetDlgItemText( IDC_ETEDITM, CStrExpos );

        SetExposSliderRange( new_units, &expos_factor, &Roundoff,
                             &max_slide, &Expos_Slider() );
        SetExposSliderPos( &new_exposure, expos_factor, Roundoff,
                           max_slide, &Expos_Slider() );

        PropSheet().ExposUnits = new_units;

            // Set the new range based on the units chosen
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnSyncChk
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnSyncChk()
{
    PropSheet().Synchronous = Synchronous_CheckBox().GetCheck();
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnHwaccumChk
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnHwaccumChk()
{
    PropSheet().Synchronous = HWAccum_CheckBox().GetCheck();
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnChangeNumshotsEdit
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnChangeNumshotsEdit()
{
    BOOL error_flag;
    INT  numruns;

    numruns = GetDlgItemInt( IDC_NUMSHOTS_EDIT, &error_flag, TRUE );

    if( error_flag != 0 )
        PropSheet().NumRuns = numruns;
    else
        Error_report( X_ERROR, XR_MSG_INVALID_INP, NULL );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnChangeNumaccumsEdit
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnChangeNumaccumsEdit()
{
    BOOL error_flag;
    INT  numaccums;

    numaccums = GetDlgItemInt( IDC_NUMACCUMS_EDIT, &error_flag, FALSE );

    if( error_flag != 0 )
        PropSheet().NumAccums = numaccums;
    else
        Error_report( X_ERROR, XR_MSG_INVALID_INP, NULL );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnChangeCleansEdit
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnChangeCleansEdit()
{
    BOOL  error_flag;
    SHORT numcleans;

    numcleans = (SHORT)GetDlgItemInt( IDC_CLEANS_EDIT, &error_flag, TRUE );

    if( error_flag != 0 )
        PropSheet().NumCleans = numcleans;
    else
        Error_report( X_ERROR, XR_MSG_INVALID_INP, NULL );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnSelchangeTimingmodeCb
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnSelchangeTimingmodeCb()
{
    SHORT timing;                 // Current Timing Mode "code" value
    BOOL  store_strobe_avail;     // Flag set if store strobe possible
    SHORT store_strobe;           // Value returned based on Timing Mode above
    BOOL  shutter_preopen_avail;  // Flag set if shutter preopen possible
    SHORT shutter_preopen;        // Value returned based on Timing Mode above
    SHORT list_index;

    list_index = (SHORT)TimingMode_ComboBox().GetCurSel();

    if( list_index != CB_ERR )
    {
        timing = (SHORT)TimingMode_ComboBox().GetItemData( list_index );

        if( timing != CB_ERR )
        {
            PropSheet().TimingMode = timing;

            Decode_timing_mode( timing,
                                &store_strobe_avail,    &store_strobe,
                                &shutter_preopen_avail, &shutter_preopen );

            if( ( PropSheet().SensorMode == ROM_KINETICS) &&
                ( timing == KINETICS_NO_TRIGGER ) )
                shutter_preopen_avail = FALSE;

            if( store_strobe_avail == FALSE )
                store_strobe = FALSE;
            StoreStrobe_CheckBox().SetCheck( store_strobe );
            StoreStrobe_CheckBox().EnableWindow( store_strobe_avail );
            PropSheet().StoreStrobe = store_strobe;

            if( shutter_preopen_avail == FALSE )
                shutter_preopen = FALSE;
            ShutterPreOpen_CheckBox().SetCheck( shutter_preopen );
            ShutterPreOpen_CheckBox().EnableWindow( shutter_preopen_avail );
            PropSheet().ShutterPreOpen = shutter_preopen;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnStorestrobeChk
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnStorestrobeChk()
{
    PropSheet().StoreStrobe = StoreStrobe_CheckBox().GetCheck();
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnSelchangeShuttercntrlCb
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnSelchangeShuttercntrlCb()
{
    SHORT list_index, ShutterCtrl;

    list_index = (SHORT)TimingMode_ComboBox().GetCurSel();

    if( list_index != CB_ERR )
    {
        ShutterCtrl = (SHORT)ShutterControl_ComboBox().GetItemData(list_index);

        if( ShutterCtrl != CB_ERR )
        {
            PropSheet().ShutterControl = ShutterCtrl;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnPreopenCheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnPreopenCheck()
{
    PropSheet().ShutterPreOpen = ShutterPreOpen_CheckBox().GetCheck();
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnBkgdCheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnBkgdCheck()
{
    SHORT check_value;
    
    check_value = (SHORT)BkGrnd_CheckBox().GetCheck();

       // DISABLE or ENABLE controls and texts for Background Subtraction
    BkGrnd_EditBox().EnableWindow( check_value );
    BkGrnd_Button().EnableWindow( check_value );
    BkGrnd_PathText().EnableWindow( check_value );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnKillfocusBackNameEd
//
//      This function is called whenever the focus is changed from the edit
//      box for the Background Subtraction File.  However, since Windows is
//      in-between states during processing of the KILLFOCUS message
//      (who has the focus?) just post a message and do the checking and
//      handling later when things have settled down.
//
////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnKillfocusBackNameEd()
{
    PostMessage( WM_BACKEDIT_LOSTFOCUS, 0, 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnBackEditLostFocus
//
//      This function is called whenever the focus is changed from the edit
//      box for the Background File Name.
//
//      The route to here is roundabout due to Windows' being in-between
//      states during KILLFOCUS - see note in OnKillfocusBackNameEd().
//
////////////////////////////////////////////////////////////////////////////

afx_msg LONG CPPWvExSetM::OnBackEditLostFocus( UINT id, LONG )
{
            // If anything has changed...

    if( BkGrnd_EditBox().GetModify() != FALSE )
    {
        SHORT   num_chars;
        CString Edit_text;
        CString Path, Name;

            // Get value of edit box as a text string
        num_chars = (SHORT)GetDlgItemText( IDC_BKGDFILE_EDIT, Edit_text );

            // If there is at least 1 character, use it
        if( num_chars >= 1 )
        {
            CHAR drive[_MAX_DRIVE];
            CHAR dir[_MAX_DIR];
            CHAR fname[_MAX_FNAME];
            CHAR ext[_MAX_EXT];

                // A name exists, so split off the and & path and display them
            _splitpath( Edit_text, drive, dir, fname, ext );
            CString FullName = fname;
            FullName += SpeExt;
            SetDlgItemText( IDC_BKGDFILE_EDIT, FullName );
            Path  = drive;
            Path += dir;
                    // If no path in edit name, use the one
                    // already displayed.  Otherwise, reset
                    // the displayed path to the new one.
            if( Path.IsEmpty() )
                GetDlgItemText( IDC_BKGDFILEPATH_TXT, Path );
            else
                SetDlgItemText( IDC_BKGDFILEPATH_TXT, Path );

            PropSheet().BackFileName = ( Path + FullName );

            if( CFileFind().FindFile( PropSheet().BackFileName, 0 ) == FALSE )
            {
                CString ErrorMessage = BackFileMsg +
                                       PropSheet().BackFileName + NotExistMsg;
                Error_report( X_INFORMATION, LOCAL_STRING, (void *)(LPCSTR)ErrorMessage );
            }
        }
        else
        {
                // It's empty, so clear the data & the path
            PropSheet().BackFileName.Empty();
            Path.Empty();
            SetDlgItemText( IDC_BKGDFILEPATH_TXT, Path );
        }
    }

    return( 0 );

    if( id );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnKillfocusFlatNameEd
//
//      This function is called whenever the focus is changed from the edit
//      box for the Flatfield Subtraction File.  However, since Windows is
//      in-between states during processing of the KILLFOCUS message
//      (who has the focus?) just post a message and do the checking and
//      handling later when things have settled down.
//
////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnKillfocusFlatNameEd()
{
    PostMessage( WM_FLATEDIT_LOSTFOCUS, 0, 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnFlatEditLostFocus
//
//      This function is called whenever the focus is changed from the edit
//      box for the Background File Name.
//
//      The route to here is roundabout due to Windows' being in-between
//      states during KILLFOCUS - see note in OnKillfocusFlatNameEd().
//
////////////////////////////////////////////////////////////////////////////

afx_msg LONG CPPWvExSetM::OnFlatEditLostFocus( UINT id, LONG )
{
            // If anything has changed...

    if( FlatFld_EditBox().GetModify() != FALSE )
    {
        SHORT   num_chars;
        CString Edit_text;
        CString Path, Name;

            // Get value of edit box as a text string
        num_chars = (SHORT)GetDlgItemText( IDC_FLATFLDFILE_EDIT, Edit_text );

            // If there is at least 1 character, use it
        if( num_chars >= 1 )
        {
            CHAR drive[_MAX_DRIVE];
            CHAR dir[_MAX_DIR];
            CHAR fname[_MAX_FNAME];
            CHAR ext[_MAX_EXT];

                // A name exists, so split off the and & path and display them
            _splitpath( Edit_text, drive, dir, fname, ext );
            CString FullName = fname;
            FullName += SpeExt;
            SetDlgItemText( IDC_FLATFLDFILE_EDIT, FullName );
            Path  = drive;
            Path += dir;
                    // If no path in edit name, use the one
                    // already displayed.  Otherwise, reset
                    // the displayed path to the new one.
            if( Path.IsEmpty() )
                GetDlgItemText( IDC_FLATFLDFILEPATH_TXT, Path );
            else
                SetDlgItemText( IDC_FLATFLDFILEPATH_TXT, Path );

            PropSheet().FlatFieldFileName = ( Path + FullName );

            if( CFileFind().FindFile( PropSheet().FlatFieldFileName,0)==FALSE)
            {
                CString ErrorMessage = FlatFieldFileMsg +
                                       PropSheet().FlatFieldFileName + NotExistMsg;
                Error_report( X_INFORMATION, LOCAL_STRING, (void *)(LPCSTR)ErrorMessage );
            }
        }
        else
        {
                // It's empty, so clear the data & the path
            PropSheet().BackFileName.Empty();
            Path.Empty();
            SetDlgItemText( IDC_FLATFLDFILEPATH_TXT, Path );
        }
    }

    return( 0 );

    if( id );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnKillfocusBlemNameEd
//
//      This function is called whenever the focus is changed from the edit
//      box for the Background Subtraction File.  However, since Windows is
//      in-between states during processing of the KILLFOCUS message
//      (who has the focus?) just post a message and do the checking and
//      handling later when things have settled down.
//
////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnKillfocusBlemNameEd()
{
    PostMessage( WM_BLEMEDIT_LOSTFOCUS, 0, 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnBlemEditLostFocus
//
//      This function is called whenever the focus is changed from the edit
//      box for the Background File Name.
//
//      The route to here is roundabout due to Windows' being in-between
//      states during KILLFOCUS - see note in OnKillfocusBlemNameEd().
//
////////////////////////////////////////////////////////////////////////////

afx_msg LONG CPPWvExSetM::OnBlemEditLostFocus( UINT id, LONG )
{
            // If anything has changed...

    if( BlemFile_EditBox().GetModify() != FALSE )
    {
        SHORT   num_chars;
        CString Edit_text;
        CString Path, Name;

            // Get value of edit box as a text string
        num_chars = (SHORT)GetDlgItemText( IDC_BLEMISHFILE_EDIT, Edit_text );

            // If there is at least 1 character, use it
        if( num_chars >= 1 )
        {
            CHAR drive[_MAX_DRIVE];
            CHAR dir[_MAX_DIR];
            CHAR fname[_MAX_FNAME];
            CHAR ext[_MAX_EXT];

                // A name exists, so split off the and & path and display them
            _splitpath( Edit_text, drive, dir, fname, ext );
            CString FullName = fname;
            FullName += BlemExt;
            SetDlgItemText( IDC_BLEMISHFILE_EDIT, FullName );
            Path  = drive;
            Path += dir;
                    // If no path in edit name, use the one
                    // already displayed.  Otherwise, reset
                    // the displayed path to the new one.
            if( Path.IsEmpty() )
                GetDlgItemText( IDC_BLEMISHFILEPATH_TXT, Path );
            else
                SetDlgItemText( IDC_BLEMISHFILEPATH_TXT, Path );

            PropSheet().BlemishFileName = ( Path + FullName );

            if( CFileFind().FindFile( PropSheet().BlemishFileName, 0 ) == FALSE )
            {
                CString ErrorMessage = BlemishFileMsg +
                                       PropSheet().BlemishFileName + NotExistMsg;
                Error_report( X_INFORMATION, LOCAL_STRING, (void *)(LPCSTR)ErrorMessage );
            }
        }
        else
        {
                // It's empty, so clear the data & the path
            PropSheet().BlemishFileName.Empty();
            Path.Empty();
            SetDlgItemText( IDC_BLEMISHFILEPATH_TXT, Path );
        }
    }

    return( 0 );

    if( id );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnBkgdfileButton
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnBkgdfileButton()
{
///// Has MAX_PATH_LEN been updated to be at least 256???
    CHAR Name[256];
    CHAR Path[256];
//////// THIS SHOULD BE A RESOURCE!!!
    CHAR *Title = BackName;

    if( GetOpenFileNameAndPathSPE( DEFAULT_TYPE,
                                   Name, Path, Title, GetSafeHwnd() ) == TRUE )
    {
        SHORT OK_to_use = TRUE;

///////// Check file for compatable strip/frame size with the current setup

                // If OK, load name and path into dialog
        if( OK_to_use )
        {
            SetDlgItemText( IDC_BKGDFILE_EDIT, Name );
            SetDlgItemText( IDC_BKGDFILEPATH_TXT, Path );
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnFlatfldCheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnFlatfldCheck() 
{
    SHORT check_value;
    
    check_value = (SHORT)FlatFld_CheckBox().GetCheck();

      // DISABLE or ENABLE controls and texts for Flatfield Correction
    FlatFld_EditBox().EnableWindow( check_value );
    FlatFld_Button().EnableWindow( check_value );
    FlatFld_PathText().EnableWindow( check_value );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnFlatfldfileButton
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnFlatfldfileButton()
{
///// Has MAX_PATH_LEN been updated to be at least 256???
    CHAR Name[256];
    CHAR Path[256];
//////// THIS SHOULD BE A RESOURCE!!!
    CHAR *Title = FlatName;

    if( GetOpenFileNameAndPathSPE( DEFAULT_TYPE, Name, Path, Title, GetSafeHwnd() ) == TRUE )
    {
        SHORT OK_to_use = TRUE;

///////// Check file for compatable strip/frame size with the current setup

                // If OK, load name and path into dialog
        if( OK_to_use )
        {
            SetDlgItemText( IDC_FLATFLDFILE_EDIT, Name );
            SetDlgItemText( IDC_FLATFLDFILEPATH_TXT, Path );
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnBlemishCheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnBlemishCheck()
{
    SHORT check_value;
    
    check_value = (SHORT)BlemFile_CheckBox().GetCheck();

      // DISABLE or ENABLE controls and texts for Blemish Correction
    BlemFile_EditBox().EnableWindow( check_value );
    BlemFile_Button().EnableWindow( check_value );
    BlemFile_PathText().EnableWindow( check_value );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnBlemishfileButton
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnBlemishfileButton()
{
///// Has MAX_PATH_LEN been updated to be at least 256???
    CHAR Name[256];
    CHAR Path[256];
//////// THIS SHOULD BE A RESOURCE!!!
    CHAR *Title = BlemName;

    if( GetOpenFileNameAndPathSPE( BLEMISH_DATA, Name, Path, Title,
                                   GetSafeHwnd() ) == TRUE )
    {
        SHORT OK_to_use = TRUE;

///////// Check file for compatable strip/frame size with the current setup

                // If OK, load name and path into dialog
        if( OK_to_use )
        {
            SetDlgItemText( IDC_BLEMISHFILE_EDIT, Name );
            SetDlgItemText( IDC_BLEMISHFILEPATH_TXT, Path );
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnCosmicSpatialRb
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnCosmicSpatialRb()
{
    CosmicThreshEnableDisable( TRUE );     // Enable Threshold Stuff
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnCosmicOffRb
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnCosmicOffRb()
{
    CosmicThreshEnableDisable( FALSE );     // Disable Threshold Stuff
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnCosmicTemporalRb
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnCosmicTemporalRb()
{
    CosmicThreshEnableDisable( FALSE );     // Disable Threshold Stuff
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnChangeCosmicThreshEdit
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnChangeCosmicThreshEdit()
{
    CString exposure_str;
    SHORT   num_chars;

    num_chars = (SHORT)GetDlgItemText( IDC_COSMIC_THRESH_EDIT, exposure_str );

    if( num_chars > 0 )
    {
        CHAR *error_str;

        PropSheet().CosmicThreshold = strtod( exposure_str, &error_str );

        if( *error_str != 0 )
            Error_report( X_ERROR, XR_MSG_INVALID_INP, NULL );
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::CosmicThreshEnableDisable
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::CosmicThreshEnableDisable
    (
    BOOL flag
    )
{
    CosThresh_Text().EnableWindow(    flag );
    CosThresh_EditBox().EnableWindow( flag );
    CosThresh_Spin().EnableWindow(    flag );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnPdcheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnPdcheck()
{
    SHORT check_value;
    CONTROLLER *controller;

    check_value = (SHORT)PixDef_CheckBox().GetCheck();

    PropSheet().PixelAccessFlag = check_value;

       // DISABLE or ENABLE control for Pixel Definition
    PixDef_Button().EnableWindow( check_value );

    controller = Get_Current_Controller();

    if( controller )
    {
            // Turn OFF controller use of access pattern
        controller->Set_use_accesspattern_x( controller, check_value );
        controller->Set_use_accesspattern_y( controller, check_value );
    }

      // TRUE = Display FULL Chip Dims, FALSE = Display ACCESSED Chip Dims
    Set_access_pattern_txt( check_value );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnSoftbinCheck
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnSoftbinCheck()
{
    PropSheet().SoftwareBinFlag = SoftwareBin_CheckBox().GetCheck();
}


//////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Setup_timing_mode
//
//  This function will set up the timing mode list box based
//  on the current controller type.
//
//  NOTE: The internal timing mode value passed is based on
//        three items: the actual timing mode, the store strobe value
//        and the shutter preopen value.  This function will
//        decode the internal timing mode and return the current
//        store strobe and shutter preopen values.  It will also
//        set flags for the availability of the store strobe and
//        shutter preopen with this timing mode.
//
//////////////////////////////////////////////////////////////////////////////

SHORT CPPWvExSetM::Setup_timing_mode
    (
    SHORT timing,                 // Current Timing Mode "code" value
    BOOL  *store_strobe_avail,    // Flag set if store strobe possible
    SHORT *store_strobe,          // Value returned based on Timing Mode above
    BOOL  *shutter_preopen_avail, // Flag set if shutter preopen possible
    SHORT *shutter_preopen        // Value returned based on Timing Mode above
    )
{
    SHORT controller_type;
    SHORT res_id, idx;
    SHORT sensormode;
    SHORT temp_timing_mode;
    SHORT valid = TRUE;
    CONTROLLER *controller;

    if( !( controller = Get_Current_Controller() ) )
    {
//////////// PUT THIS BACK ????
////////////        Error_report( X_ERROR, XR_AQUIS_NO_CONTROLLER, NULL );

            // Set some defaults for return
        temp_timing_mode       = CTRL_FREERUN;
        *store_strobe_avail    = TRUE;
        *store_strobe          = FALSE;
        *shutter_preopen_avail = FALSE;
        *shutter_preopen       = FALSE;
    }
    else
    {
        /******************************************************************/
        /******************************************************************/
        /******************************************************************/
        /******                                                      ******/
        /******                     IMPORTANT!!                      ******/
        /******                                                      ******/
        /******  If ANYTHING is changed in here, the change MUST     ******/
        /******  ALSO be made in FILEINFO.C/Decode_timing_mode()     ******/
        /******  which displays the timing mode as stored in a       ******/
        /******  file's header.                                      ******/
        /******                                                      ******/
        /******                                                      ******/
        /******************************************************************/
        /******************************************************************/
        /******************************************************************/

            // Set up options available based on the current Timing Mode
            // Store strobe and shutter pre-open depend on the timing mode
            // Note that some timing modes are changed from old style codes
            // to new style codes

        temp_timing_mode = Decode_timing_mode( timing,
                                               store_strobe_avail,
                                               store_strobe,
                                               shutter_preopen_avail,
                                               shutter_preopen );

            // Get the controller type for use below...
        controller_type = (SHORT)controller->Get_controller_type( controller );

            // KINETICS has its own Trigger Mode selection texts
            // depending upon which sensormode is set.

        sensormode = (SHORT)controller->Get_ContSetup_sensorMode(controller);
        PropSheet().SensorMode = sensormode;

        if( sensormode == ROM_KINETICS )
        {
            SHORT idx, item_id;

            for( res_id  = XPI_EXP_K_TIMING_START, idx = 0;
                 res_id <= XPI_EXP_K_TIMING_END;
                 res_id++ )
            {
                    // Set the Timing Mode string & value
                  //// THIS NEEDS TO BE FIXED SO IT WORKS IN THE LOOP
                switch( idx )
                {
                    case 0:
                        item_id = KINETICS_NO_TRIGGER;
                        break;

                    case 1:
                        item_id = KINETICS_SINGLE;
                        break;

                    case 2:
                        item_id = KINETICS_MULTIPLE;
                        break;
                }

                Load_TimingMode_Item( res_id, item_id );

                idx++;
            }

                // Get the timing mode to be set based on the kinetics trigger
            temp_timing_mode = (SHORT)controller->Get_Kinetics_TriggerMode( controller );

        }
        else if( controller_type == DC131 )
        {
                  // Set timing modes specific to the DC131 (PentaMax)
            for( res_id  = XPI_DC131_TIMING_START, idx = 0;
                 res_id <= XPI_DC131_TIMING_END;
                 res_id++ )
            {
                    // Get the Timing Mode binary value
////// TVR: THIS MUST BE FIXED TO BE DYNAMIC  !!!
                switch( idx )
                {
                    case 0:
                        temp_timing_mode = CTRL_FREERUN;
                        break;
                    case 1:
                        temp_timing_mode = CTRL_EXTSYNC;
                        break;
                    case 2:
                        temp_timing_mode = CTRL_EXTSHUTTER_CONTROL;
                        break;
                }

                Load_TimingMode_Item( res_id, temp_timing_mode );

                idx++;
            }
        }
        else
        {
            if( controller_type != OMA4 )
            {
                    // Just do the first 3 the easy way
                for( res_id  = XPI_EXP_TIMING_START;
                     res_id <= XPI_EXP_TIMING_END;
                     res_id++ )
                {
                    // Get the Timing Mode binary value
////// TVR: THIS MUST BE FIXED TO BE DYNAMIC !!!
                switch( idx )
                {
                    case 0:
                        temp_timing_mode = CTRL_FREERUN;
                        break;
                    case 1:
                        temp_timing_mode = CTRL_LINESYNC;
                        break;
                    case 2:
                        temp_timing_mode = CTRL_EXTSYNC;
                        break;
                }

                Load_TimingMode_Item( res_id, temp_timing_mode );

                idx++;
                }

                    //  check if controller really supports "External Trigger"
                    //  and set the string to the correct terminology
                if( ( controller_type == ST121 ) ||
                    ( controller_type == ST116 ) ||
                    ( controller_type == OMA3  )    )
                {
                    res_id = XPI_EXP_TIMING_EXT_TRIGGER;
                }
                else
                {
                    res_id = XPI_EXP_TIMING_CONT_CLEANS;
                }
                
                Load_TimingMode_Item( res_id, CTRL_EXTTRIG );

            }            // END if( controller_type != OMA4 )
            else
            {
                        // Do the OMA4 setup
                Load_TimingMode_Item( XPI_EXP_TIMING_FREERUN,     CTRL_FREERUN );

                Load_TimingMode_Item( XPI_EXP_TIMING_EXTSYNC,     CTRL_EXTSYNC );

                Load_TimingMode_Item( XPI_EXP_TIMING_EXT_TRIGGER, CTRL_EXTTRIG );

                *shutter_preopen = FALSE;
            }

                // Now check for ST120_Tx -- enable/disable FREERUN/EXTTRIG
            switch( controller_type )
            {
                case ST120_T1:
                case ST120_T2:      // External Trigger NOT ALLOWED
                    if( temp_timing_mode == CTRL_EXTTRIG )
                        temp_timing_mode = CTRL_FREERUN;

                    Delete_TimingMode( CTRL_EXTTRIG );
                    break;

                case OMA4:
                case ST121:
                case ST116:
                case OMA3:
                    break;      // Do nothing

                default:        // Line Sync NOT ALLOWED
                    if( temp_timing_mode == CTRL_LINESYNC )
                        temp_timing_mode = CTRL_FREERUN;
                    Delete_TimingMode( CTRL_LINESYNC );
                    break;
            }

        }

        Select_TimingMode( temp_timing_mode );
    }

    return( valid );

}                           //  END Setup_timing_mode()


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Decode_timing_mode
//
/////////////////////////////////////////////////////////////////////////////

SHORT CPPWvExSetM::Decode_timing_mode
    (
    SHORT timing,                 // Current Timing Mode "code" value
    BOOL  *store_strobe_avail,    // Flag set if store strobe possible
    SHORT *store_strobe,          // Value returned based on Timing Mode above
    BOOL  *shutter_preopen_avail, // Flag set if shutter preopen possible
    SHORT *shutter_preopen        // Value returned based on Timing Mode above
    )
{
    SHORT temp_timing_mode;

    switch( timing )
    {
        case CTRL_FREERUN:
            temp_timing_mode       = CTRL_FREERUN;
            *store_strobe          = FALSE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = FALSE;
            break;

        case CTRL_FR_STORE_TRIG:
            temp_timing_mode       = CTRL_FREERUN;
            *store_strobe          = TRUE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = FALSE;
            break;

        case CTRL_LINESYNC:
            temp_timing_mode       = CTRL_LINESYNC;
            *store_strobe          = FALSE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = FALSE;
            *shutter_preopen_avail = FALSE;
            break;

        case CTRL_EXTSYNC:
        case CTRL_EXTSYNC_NORMAL :
            temp_timing_mode       = CTRL_EXTSYNC;
            *store_strobe          = FALSE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_EXTSYNC_PREOPEN:
            temp_timing_mode       = CTRL_EXTSYNC;
            *store_strobe          = FALSE;
            *shutter_preopen       = TRUE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_SN_STORE_TRIG:
            temp_timing_mode       = CTRL_EXTSYNC;
            *store_strobe          = TRUE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_SP_STORE_TRIG:
            temp_timing_mode       = CTRL_EXTSYNC;
            *store_strobe          = TRUE;
            *shutter_preopen       = TRUE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_EXTTRIG:
        case CTRL_EXTTRIG_NORMAL :
            temp_timing_mode       = CTRL_EXTTRIG;
            *store_strobe          = FALSE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_EXTTRIG_PREOPEN:
            temp_timing_mode       = CTRL_EXTTRIG;
            *store_strobe          = FALSE;
            *shutter_preopen       = TRUE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_TN_STORE_TRIG:
            temp_timing_mode       = CTRL_EXTTRIG;
            *store_strobe          = TRUE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_TP_STORE_TRIG:
            temp_timing_mode       = CTRL_EXTTRIG;
            *store_strobe          = TRUE;
            *shutter_preopen       = TRUE;
            *store_strobe_avail    = TRUE;
            *shutter_preopen_avail = TRUE;
            break;

        case CTRL_EXTSHUTTER_CONTROL:
            temp_timing_mode       = CTRL_EXTSHUTTER_CONTROL;
            *store_strobe          = FALSE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = FALSE;
            *shutter_preopen_avail = FALSE;
            break;

        default:
            temp_timing_mode       = CTRL_FREERUN;
            *store_strobe          = FALSE;
            *shutter_preopen       = FALSE;
            *store_strobe_avail    = FALSE;
            *shutter_preopen_avail = FALSE;
            break;
    }                       // END switch( timing )

    return( temp_timing_mode );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Load_TimingMode_Item
//
//   This function will load a string and item_data value into the timing mode
//   combo box.
//
//////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::Load_TimingMode_Item
    (
    SHORT resource_id,   // ID of resource string to use
    DWORD item_data      // Data item to associate with string
    )
{
    SHORT list_index;
    CHAR  tmpbuffer[MAX_PATH_LEN];

        // Get the string from resource
    CMRESOURCE( resource_id );

        // Add the string and get back an index (position)
    list_index = (SHORT)TimingMode_ComboBox().AddString( tmpbuffer );

        // Set the data item for this string
    TimingMode_ComboBox().SetItemData( list_index, item_data );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Select_TimingMode
//
//   This function will set the selected timing mode based on the
//   BINARY timing mode value.  It will attempt to match this value
//   with one of the item_data values set in the combo box.  If a
//   match is found, the string for that item will be selected.
//
//   Returns:   TRUE  = a match was found and the item was selected
//              FALSE = no match was found, any selection is cleared
//
//////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSetM::Select_TimingMode
    (
    SHORT timing_mode         // BINARY timing mode value (as used internally)
    )
{
    SHORT num_idx, id_idx, list_id;
    BOOL  item_found = FALSE;

    num_idx = (SHORT)TimingMode_ComboBox().GetCount();

    for( id_idx = 0; ( id_idx < num_idx ) && ( item_found == FALSE ); id_idx++)
    {
                // Get an item's data
        list_id = (SHORT)TimingMode_ComboBox().GetItemData( id_idx );

                // Check for match with parameter - if so, set it
        if( timing_mode == list_id )
        {
            TimingMode_ComboBox().SetCurSel( id_idx );
            item_found = TRUE;
        }
    }

        // If no match, show no selection made
    if( item_found == FALSE )
        TimingMode_ComboBox().Clear();

    return( item_found );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Delete_TimingMode
//
//   This function will set the DELETE timing mode based on the
//   BINARY timing mode value.  It will attempt to match this value
//   with one of the item_data values set in the combo box.  If a
//   match is found, the string for that item will be deleted.
//
//   Returns:   TRUE  = a match was found and the item was deleted
//              FALSE = no match was found, nothing was done
//
//////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSetM::Delete_TimingMode
    (
    SHORT timing_mode         // BINARY timing mode value (as used internally)
    )
{
    SHORT num_idx, id_idx, list_id;
    BOOL  item_found = FALSE;

    num_idx = (SHORT)TimingMode_ComboBox().GetCount();

    for( id_idx = 0; ( id_idx < num_idx ) && ( item_found == FALSE ); id_idx++)
    {
                // Get an item's data
        list_id = (SHORT)TimingMode_ComboBox().GetItemData( id_idx );

                // Check for match with parameter - if so, set it
        if( timing_mode == list_id )
        {
            TimingMode_ComboBox().DeleteString( id_idx );
            item_found = TRUE;
        }
    }

    return( item_found );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Delete_TimingMode_Str
//
//   This function will delete the timing mode based on the STRING timing
//   mode as it is displayed in the dialog.  It will attempt to match this
//   string with one of those existing in the combo box.  If a match is
//   found, the string will be deleted.
//
//   Returns:   TRUE  = a match was found and the string was deleted
//              FALSE = no match was found, nothing was done
//
//////////////////////////////////////////////////////////////////////////////

BOOL CPPWvExSetM::Delete_TimingMode_Str
    (
    CHAR *timing_mode_str         // STRING timing mode value (as DISPLAYED in dialog)
    )
{
    USHORT list_idx;
    BOOL   item_found;

    list_idx =
       (USHORT)TimingMode_ComboBox().FindStringExact( -1, timing_mode_str );

    if( list_idx != CB_ERR )
    {
        TimingMode_ComboBox().DeleteString( list_idx );
        item_found = TRUE;
    }
    else
    {
            // If no match, show no selection made
        TimingMode_ComboBox().Clear();
        item_found = FALSE;
    }

    return( item_found );
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnCancel
//
//  If CANCEL hit, don't do anything to the data in the dialog, just exit
//
//////////////////////////////////////////////////////////////////////////////

//void CPPWvExSetM::OnCancel()
//{
//	CPropertyPage::OnCancel();
//}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::OnPdbutton()
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::OnPdbutton()
{
    Do_PixDef_Dlg();

    Set_access_pattern_txt( TRUE );     // Display binned values
}


/////////////////////////////////////////////////////////////////////////////
//
//  ADVANCED PAGE FUNCTION:
//
//              CPPWvExSetM::Set_access_pattern_txt
//
/////////////////////////////////////////////////////////////////////////////

void CPPWvExSetM::Set_access_pattern_txt
    (
    SHORT flag    // TRUE = Show Accessed Dims, FALSE = Show FULL Dims
    )
{
    CHAR pix_def_text[50];
    INT  x_size, y_size;
    CONTROLLER *controller;

    controller = Get_Current_Controller();

    if( controller )
    {
        if( flag == TRUE )
        {
            x_size = controller->Get_binned_x( controller );
            y_size = controller->Get_binned_y( controller );
        }
        else
        {
            x_size = controller->Get_sensor_x( controller );
            y_size = controller->Get_sensor_y( controller );
        }

        sprintf( pix_def_text, "X: %d  Y: %d", x_size, y_size );

        SetDlgItemText( IDC_PDSIZE_TXT, pix_def_text );
    }
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////////                                                              ////////
////////                                                              ////////
////////                    STATIC FUNCTIONS                          ////////
////////                                                              ////////
////////                                                              ////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//
//  This function will implement the OPEN FILE common dialog for .SPE
//  experiment files ONLY and (if OK) return the file name and path chosen.
//
//////////////////////////////////////////////////////////////////////////////

static BOOL GetOpenFileNameAndPathSPE
    (
    SHORT FileType,      // Type of file (.SPE, .BLE)
    CHAR  *Name,         // Name chosen (returned)
    CHAR  *Path,         // Path chosen (returned)
    CHAR  *title,        // Title for Common Dialog
    HWND  hwnd           // Handle of calling dialog
    )
{
    OPENFILENAME OpenFileStruct;
///// Has MAX_PATH_LEN been updated to be at least 256???
    CHAR FileNameAndExt[256];
    CHAR FullFileName[256];
    SHORT  err, dlg_ret;
    SHORT  ret_val = FALSE;
    CHAR *DefaultFileType;
    CHAR *DefaultExt;

    FileNameAndExt[0] = '\0';   // No default File Name
    FullFileName[0]   = '\0';   // No default Full File Name

    switch( FileType )
    {
        case BLEMISH_DATA:
            DefaultFileType = BlemFileType;
            DefaultExt      = BlemExt;
            break;

        case CSMA_DATA:
            DefaultFileType = SpeFileType;
            DefaultExt      = SpeExt;
            break;
    }

    OpenFileStruct.lStructSize       = (sizeof( OPENFILENAME ) );
    OpenFileStruct.hwndOwner         = hwnd;
    OpenFileStruct.lpstrFilter       = DefaultFileType;
    OpenFileStruct.lpstrCustomFilter = NULL;
    OpenFileStruct.nFilterIndex      = 1;
    OpenFileStruct.lpstrFile         = FullFileName;
    OpenFileStruct.nMaxFile          = 256;
    OpenFileStruct.lpstrFileTitle    = FileNameAndExt; 
    OpenFileStruct.nMaxFileTitle     = 256;
    OpenFileStruct.lpstrInitialDir   = NULL;
    OpenFileStruct.lpstrTitle        = title;
    OpenFileStruct.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    OpenFileStruct.lpstrDefExt       = DefaultExt;

    // Bring up the common dialog box for file name input
    dlg_ret = (SHORT)GetOpenFileName( &OpenFileStruct );

    if( dlg_ret == TRUE )
    {
                // Get the new file information
        strcpy( Name, FileNameAndExt );
        strncpy( Path, FullFileName, OpenFileStruct.nFileOffset );
        Path[OpenFileStruct.nFileOffset] = '\0';
        ret_val = TRUE;
    }
    else
    {
            // For debugging purposes
        err = (SHORT)CommDlgExtendedError();
    }

    return( ret_val );
}


//////////////////////////////////////////////////////////////////////////////
//
//  This function will cause the Modal dialog for pixel definition to
//  be displayed.  Once all the information is entered the user will
//  close the dialog either via OK or Cancel. The subdialog will handle
//  all the error checking and saving of the pattern information.
//
//////////////////////////////////////////////////////////////////////////////

static void Do_PixDef_Dlg()
{
    CDlgWvPixelDef *PixDefDlg = new CDlgWvPixelDef();

    if( PixDefDlg->DoModal() == -1 )
    {
        TRACE( "Error Creating Pixel Definition Dialog!" );
    }

    delete PixDefDlg;
}
