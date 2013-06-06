/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/// StereoGR.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "StereoGR.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "StereoGRDoc.h"
#include "StereoGRView.h"
#include "PTOffline.h"
#include "PTOptions.h"
#include "HMMParams.h" 
#include "float.h"
#include "direct.h"
#include <io.h>

#include <digiclops.h>
#include <triclops.h>
#include "PGControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStereoGRApp

BEGIN_MESSAGE_MAP(CStereoGRApp, CWinApp)
	//{{AFX_MSG_MAP(CStereoGRApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_PT_PROP, OnPtProp)
	ON_COMMAND(ID_PT_WHITEBALANCE, OnPtWhitebalance)
	ON_COMMAND(ID_PTOFFLINE, OnPtoffline)
	ON_COMMAND(ID_CAPTURE_BACK, OnCaptureBack)
	ON_COMMAND(ID_RUNGESTREC, OnRungestrec)
	ON_COMMAND(ID_SETTINGS, OnSettings)
	ON_COMMAND(ID_TRAIN, OnTrain)
	ON_COMMAND(ID_SAVE_DGPARAMS, OnSaveDynamicGestures)
	ON_COMMAND(ID_LOAD_DGPARAMS, OnLoadDynamicGestures)
	ON_COMMAND(ID_SAVE_BASE, OnSaveBase)
	ON_COMMAND(ID_LOAD_BASE, OnLoadBase)
	ON_COMMAND(ID_RECOG_FILE_DG, OnRecogFileDg)
	ON_COMMAND(ID_DELETE_HMM, OnDeleteHmm)
	ON_COMMAND(ID_REMOVE_ALL_DG, OnRemoveAllDg)
	ON_UPDATE_COMMAND_UI(ID_RUNGESTREC, OnUpdateRungestrec)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

IPLStatus __stdcall _iplErrorHandler(IPLStatus status, const char* func, const char* context, 
                            const char* file, int line);

/////////////////////////////////////////////////////////////////////////////
// CStereoGRApp construction

CStereoGRApp::CStereoGRApp()
{
    InitModulePath();
    memset(m_viewIds, 0, sizeof(m_viewIds));
    memset(m_views, 0, sizeof(m_viewIds));

    // Initialize IPL
    iplRedirectError(_iplErrorHandler);

   
    m_findHand.m_dynamicGesture = 0;//m_dgProp->IsSaveToFile();
    m_findHand.m_path = m_modulePath;
    m_findHand.m_dGestureName = "";//m_dgProp->GetGestureName();

    m_ptOptions = 0;
    m_grOptions = 0;
    m_hmmParams = 0;
    m_dgStat    = 0;

    m_doRecog = FALSE;

	POINT p = {-1, -1};
	for(int i = 0; i < VIEWS_COUNT; i++)
	{
		m_TopLefts.push_back(p);
		m_TopLefts3D.push_back(p);
	}

	m_isClosingView = FALSE;	
}

CStereoGRApp::~CStereoGRApp()
{
    delete m_ptOptions;
    delete m_grOptions;
    delete m_hmmParams;
    delete m_dgStat;
	delete m_dgProp;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStereoGRApp object

CStereoGRApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStereoGRApp initialization

BOOL CStereoGRApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_STEREOTYPE,
		RUNTIME_CLASS(CStereoGRDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CStereoGRView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

    CStatusBar* bar = pMainFrame->GetStatusBar();
    bar->SetPaneText(0, "Initializing the camera...");
    // Initialize the camera
	CString config;
	while(1)
	{
		config = GetProfileString("Settings\\PTGrey", "Config");
		_finddata_t filedata;
		if(config.IsEmpty() || _findfirst(LPCTSTR(config), &filedata) == -1)
		{
			CFileDialog dlg(TRUE, "", "config");
			AfxMessageBox("For the first run please enter the name of \nthe configuration file of your PointGrey camera.");
			if(dlg.DoModal() != IDOK)
			{
				AfxMessageBox("The configuration file is required for stereo processing.\nPlease contact your camera supplier to obtain the file for your camera.");
				return FALSE;
			}

			WriteProfileString("Settings\\PTGrey", "Config", LPCTSTR(dlg.GetPathName()));
		}
		else
		{
			break;
		}
	}
	PTGreySetConfigFileName(LPCTSTR(config));
	
    int rawres = 0, stereores = 0;
    rawres = GetProfileInt("Settings\\PTGrey", "Raw resolution", rawres);
    PTGreySetProperty("RawResolution", &rawres);
    stereores = GetProfileInt("Settings\\PTGrey", "Stereo resolution", stereores);
    PTGreySetProperty("StereoResolution", &stereores);
    BOOL ret = PTGreyInitCamera();
    if(!ret)
    {
        AfxMessageBox(PTGreyGetErrorMessage());
		return FALSE;
    }
    else
	{
		// Load camera and application settings
        LoadSettings();
	}

	// Automatically capture background
	OnCaptureBack();

    //set hmm parameters 
    m_dgServer.SetHMMParams( m_hmmParams->m_num_states, m_hmmParams->m_num_mix );

	// Assign an affinity mask to the current thread
    int e = SetThreadAffinityMask(GetCurrentThread(), 1);

    bar->SetPaneText(0, "Ready");
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CStereoGRApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CStereoGRApp message handlers


int CStereoGRApp::GetDocType()
{
    return m_docType;
}

void CStereoGRApp::OnFileNew() 
{
    if(m_docType >= VIEWS_COUNT)
        return;
    
    CWinApp::OnFileNew();
    m_docType++;
}

void CStereoGRApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_docType < PG_IMAGE_MAX);	
}

void CStereoGRApp::SetDocType(int docType)
{
    m_docType = docType;
}

void CStereoGRApp::OnPtProp() 
{
    PTGreyShowPropertyPage();
}

void CStereoGRApp::OnPtWhitebalance() 
{
    PTGreyShowWhiteBalance();
}

void CStereoGRApp::OnPtoffline() 
{
    CStatusBar* bar = ((CMainFrame*)AfxGetMainWnd())->GetStatusBar();
    CPTOffline dlg;
    dlg.m_strSaveFile = m_modulePath;
    dlg.SetFramesCount(30);
    if(dlg.DoModal() == IDOK)
    {
        int framesCount = dlg.GetFrameCount();
        // Start collecting frames...
        PTGreySetTriclopsInputBuffer(framesCount);
        while(1)
        {
            int count = PTGreyGetFrameNumber();
            if(count < 0)
                // Finished collecting frames
                break;

            CString str;
            str.Format("Collected frame %d of %d...", count, framesCount);
            bar->SetPaneText(0, str);
            Sleep(10);
        }
        TriclopsInput* buffer = (TriclopsInput*)PTGreyGetTriclopsBuffer();

        // Process the frames...
        PTGreyFreezeData(INFINITE);
        bar->SetPaneText(0, "Processing the frames...");
        PTGreyProcessFrames(PTGreyGetTriclopsBuffer(), framesCount, dlg.m_strSaveFile);
        bar->SetPaneText(0, "Ready");
        PTGreyUnFreezeData();

        // Freeing the memory...
        PTGreySetTriclopsInputBuffer(0);
    }
}

void CStereoGRApp::InitModulePath()
{
    char buffer[_MAX_PATH];
    char drive[_MAX_DRIVE];
    char path[_MAX_PATH];
    GetModuleFileName(0, buffer, _MAX_PATH);

    _splitpath(buffer, drive, path, 0, 0);
    m_modulePath = CString(drive) + path;
}


void CStereoGRApp::OnCaptureBack() 
{
    PTGreySelectDataType(PT_BACKGROUND_IMAGE, 1);	
}

void CStereoGRApp::Process()
{
    ASSERT(iplGetErrStatus() >= 0);
    ValidateData();
    // Lock the data
    PTGreyFreezeData(INFINITE);

    if(!m_viewIds[PT_POINTCLOUD_IMAGE])
    {
        PTGreyUnFreezeData();
        return; // Do not run the algorithm
    }
    
    // Set FindHand object properties
	m_findHand.m_dGestureName = m_dgProp->GetGestureName();
	m_findHand.m_dynamicGesture = m_dgProp->IsCollectGesture();
    m_findHand.SetPointBuffer((CvPoint3D32f*)PTGreyGetDataPointer(PT_POINTCLOUD_IMAGE));
    m_findHand.m_pointCount = PTGreyGetPointCount();
	TRACE("\n%d", m_findHand.m_pointCount);
    m_findHand.m_inputImage = GetImage(PT_RIGHT_RAW_IMAGE);
    iplDeallocate(m_findHand.m_disparityImage, IPL_IMAGE_ALL);
    m_findHand.m_disparityImage = iplCloneImage(GetView(PT_DISPARITY_OBJ_IMAGE)->GetRecipient());
	iplCopy(GetView(PT_DISPARITY_IMAGE)->GetRecipient(), m_findHand.m_disparityImage);

    if(m_findHand.m_outputImage)
    {
        m_findHand.m_outputImage->roi = 0;
        cvReleaseImage(&m_findHand.m_outputImage); // Release and null it.
    }
    BOOL ret = m_findHand.FitLine();
    ASSERT(iplGetErrStatus() >= 0);
    if(ret)
	{
        //if all ok with finding hand increase hand sequence size
        if(m_findHand.m_dynamicGesture) m_findHand.m_dgFrameFound = TRUE;  
		m_findHand.StoreDynGesture(0, PTGreyGetTime());
//		m_findHand.FindHand(FALSE);
	}        
    // Use output image as a mask to the right raw image
    IplImage* image = m_findHand.m_outputImage;
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	frame->GetStatusBar()->SetPaneText(1, "");
    IplImage* srcImage = GetImage(PT_RIGHT_RAW_IMAGE);
	int width = PTGreyGetWidth(PT_RIGHT_RAW_IMAGE);
	int height = PTGreyGetHeight(PT_RIGHT_RAW_IMAGE);
	int swidth = PTGreyGetWidth(PT_DISPARITY_IMAGE);
	int sheight = PTGreyGetHeight(PT_DISPARITY_IMAGE);
	int maxdisp;
	PTGreyGetProperty("MaxDisparity", &maxdisp);

	CvPoint valid_size = cvPoint(width*(swidth - maxdisp/2)/swidth,
			height*(sheight - maxdisp/2)/sheight);

//    Segment();
    if(!ret/*!image*/)
	{
        ValidateData(FALSE);
		cvRectangle(srcImage, cvPoint(0, 0), valid_size, CV_RGB(255, 0, 0), 1);
	}
	else
    {
        ValidateData(FALSE);
		cvRectangle(srcImage, cvPoint(0, 0), valid_size, CV_RGB(0, 255, 0), 1);
/*        iplThreshold(image, image, 1);
        if(srcImage)
        {
            srcImage->roi = iplCreateROI(0, 0, 0, image->width, image->height);
            image->roi = iplCreateROI(1, 0, 0, image->width, image->height);
            
            for(int i = 0; i < 3; i++)
            {
                srcImage->roi->coi = i + 1;
                iplAnd(srcImage, image, srcImage);
            }
            iplDeleteROI(srcImage->roi);
            iplDeleteROI(image->roi);
        }
		CString str;
		str.Format("%d", m_findHand.m_DefectsDepth.size());

		if(m_findHand.m_convexDefCount !=0 )
		{
			CString def;
			for (int i=0;i<m_findHand.m_DefectsDepth.size();i++)
			{
				def.Format(" %4.1f", m_findHand.m_DefectsDepth[i]);
				str+=def;
			}

		}
		frame->GetStatusBar()->SetPaneText(1, LPCTSTR(str));*/
    }

    //********************Dynamic gestures section*********************** /
    
    //ask findHandCtl if it has collected gesture
    if ( m_findHand.IsGestureFixed() && m_findHand.m_dynamicGesture )
    {
		CDynGesture  local_gesture(m_hmmParams->m_num_states, m_hmmParams->m_num_mix);
		CDynGesture* gesture = NULL;

		if (!m_doRecog) //collecting gestures
        {
			//training stage 
            gesture = m_dgServer.FindGesture( m_findHand.m_dGestureName.c_str() );
        
            if ( !gesture )  //add new gesture to server
            {
                gesture = m_dgServer.AddGesture( m_findHand.m_dGestureName.c_str() );
            }
		}
		else
		{
			gesture = &local_gesture;
		}

        //add collected params to gesture
		gesture->AddParams( m_findHand.m_geomParams );

        if (m_doRecog) //recognizing gestures
        {	
			float likelihood[10] = { -FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX,
                                     -FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX };
            
            //convert params to observations form
            gesture->ExtractObservations();  
            
            //recognize
            int recognized_gesture = m_dgServer.RecognizeDynGesture( gesture, likelihood );
			if(recognized_gesture >= 0)
			{
				CString gesture_name = m_dgServer.GetGesture( recognized_gesture )->GetName();
				CStereoGRView* pView = GetView(GR_MAGICCUBE);
				
				if(gesture_name.CompareNoCase("rotate_left") == 0)
				{
					pView->RotateAzim(-1);
				}
				else if(gesture_name.CompareNoCase("rotate_right") == 0)
				{
					pView->RotateAzim(+1);
				}
				else if(gesture_name.CompareNoCase("rotate_counterclockwise") == 0)
				{
					pView->RotateIncl(-1);
				}
				else if(gesture_name.CompareNoCase("rotate_clockwise") == 0)
				{
					pView->RotateIncl(+1);
				}
				else if(gesture_name.CompareNoCase("zoom_in") == 0)
				{
					pView->Translate(-0.1f);
				}
				else if(gesture_name.CompareNoCase("zoom_out") == 0)
				{
					pView->Translate(+0.1f);
				}
				else if(gesture_name.CompareNoCase("close") == 0)
				{
					CloseView(GR_MAGICCUBE);
				}
				else if(gesture_name.CompareNoCase("reset") == 0)
				{
					pView->InitModel();
				}
				

				//ASSERT( likelihood[0] <= 0 );
            
				//write result to status bar
				CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
				frame->GetStatusBar()->SetPaneText(2, "");
				CString RecogResult;
				RecogResult.Format("Recognized %s, likelihood %f",
					m_dgServer.GetGesture( recognized_gesture )->GetName(), likelihood[0] );				
				frame->GetStatusBar()->SetPaneText(2, RecogResult);   	
			}
        }
        
        m_findHand.ReleaseFixedGesture();
    }
    /*****************************************************************/


    ASSERT(iplGetErrStatus() >= 0);
    if(::IsWindow(m_gestRec.m_hWnd))
    {
        m_gestRec.UpdateStatus();
    }
    ASSERT(iplGetErrStatus() >= 0);

    PTGreyUnFreezeData();    
}

void CStereoGRApp::OpenView(int dataType)
{
    // Check if the view alredy exists...
    if(m_views[dataType])
        return;

    SetDocType(dataType);
    OnFileNew();
    switch(dataType)
    {
    case PT_DISPARITY_OBJ_IMAGE:
        OpenView(PT_RIGHT_RAW_IMAGE);
        OpenView(PT_DISPARITY_IMAGE);
        break;

    case PT_POINTCLOUD_IMAGE:
        OpenView(PT_DISPARITY_OBJ_IMAGE);
        break;

	case GR_MAGICCUBE:
		OpenView(PT_POINTCLOUD_IMAGE);
		OpenView(PT_LEFT_RAW_IMAGE);
		OpenView(PT_TOP_RAW_IMAGE);
		break;
    }
}

void CStereoGRApp::SetView(int dataType, CStereoGRView *pView)
{
    m_views[dataType] = pView;
    m_viewIds[dataType] = 1;
}

void CStereoGRApp::CloseView(int dataType)
{
	PTGreyFreezeData(INFINITE);
	m_isClosingView++;
	switch(dataType)
	{
	case PT_POINTCLOUD_IMAGE:
	case PT_LEFT_RAW_IMAGE:
	case PT_TOP_RAW_IMAGE:
		CloseView(GR_MAGICCUBE);
		break;

	case PT_DISPARITY_OBJ_IMAGE:
		CloseView(PT_POINTCLOUD_IMAGE);
		break;

	case PT_RIGHT_RAW_IMAGE:
	case PT_DISPARITY_IMAGE:
		CloseView(PT_DISPARITY_OBJ_IMAGE);
		break;
	}

    ASSERT(dataType >= 0 && dataType < VIEWS_COUNT);
    if(m_views[dataType])
    {
        m_views[dataType]->GetParent()->DestroyWindow();
        m_viewIds[dataType] = 0;
    }
	m_isClosingView--;
    PTGreyUnFreezeData();
}

IPLStatus __stdcall _iplErrorHandler(IPLStatus status, const char* func, const char* context, 
                            const char* file, int line)
{
    if(status != -10)
        ASSERT(0);
    return IPL_StsOk;
}

void CStereoGRApp::Update()
{
    if(!PTGreyFreezeData(INFINITE))
        return;

    int e = iplGetErrStatus();
    ASSERT(e >= 0);
    // Retrieve the data
    for(int i = 0; i < VIEWS_COUNT; i++)
    {
        CStereoGRView* pView = GetView(i);
        if(pView)
            pView->UpdateData();
    }
    // Run algorithms on the data
    Process();
    PTGreyUnFreezeData();

    // Render the results
    for(i = 0; i < VIEWS_COUNT; i++)
    {
        CStereoGRView* pView = GetView(i);
        if(pView)
            pView->UpdateView();
    }
    ASSERT(iplGetErrStatus() >= 0);
}

IplImage* CStereoGRApp::GetImage(int dataType)
{
    if(!m_views[dataType])
        return 0;

    return m_views[dataType]->GetImage();
}

/*void CStereoGRApp::SetImage(int dataType, IplImage *image, BOOL copy)
{
    if(!m_views[dataType])
        return;

    m_views[dataType]->SetImage(image, copy);
}*/

void CStereoGRApp::OnRungestrec() 
{
    m_gestRec.DoModal();	
}

void CStereoGRApp::ValidateData(BOOL flag)
{
    m_isNewData = flag;
}

BOOL CStereoGRApp::IsNewData()
{
    return m_isNewData;
}


void CStereoGRApp::OnTrain() 
{       
    m_dgServer.TrainAllGestures();
}


void CStereoGRApp::OnSettings()
{
    CPropertySheet sheet;
    sheet.AddPage(m_ptOptions);
    sheet.AddPage(m_grOptions);
    sheet.AddPage(m_hmmParams);
    sheet.AddPage(m_dgProp);
    sheet.AddPage(m_dgStat);

    // Load PointGrey options
    int rawres, stereores;
    PTGreyGetProperty("StereoResolution", &stereores);
    m_ptOptions->m_stereoRes = stereores;
    PTGreyGetProperty("RawResolution", &rawres);
    m_ptOptions->m_rawRes = rawres;
    PTGreyGetProperty("MinDisparity", &m_ptOptions->m_minDisp);
    PTGreyGetProperty("MaxDisparity", &m_ptOptions->m_maxDisp);
    PTGreyGetProperty("DisparityThreshold", &m_ptOptions->m_dispThresh);
    PTGreyGetProperty("DifferenceThreshold", &m_ptOptions->m_diffThresh);
    PTGreyGetProperty("DepthThreshold", &m_ptOptions->m_depthThresh);
    PTGreyGetProperty("ContourProcessing", &m_ptOptions->m_checkContours);

    // Load StereoGR options
    m_grOptions->m_maskImprove = m_findHand.m_maskImprovigFlag;
    m_grOptions->m_frameCount = m_findHand.m_trainFrameCount;
    m_grOptions->m_segThresh = m_findHand.m_segThresh;

    if(sheet.DoModal() == IDOK)
    {
        // Save PointGrey options
        PTGreyFreezeData(INFINITE);
        if(rawres != m_ptOptions->m_rawRes || stereores != m_ptOptions->m_stereoRes)
        {
            // The resolution has changed...
            WriteProfileInt("Settings\\PTGrey", "Raw resolution", m_ptOptions->m_rawRes);
            WriteProfileInt("Settings\\PTGrey", "Stereo resolution", m_ptOptions->m_stereoRes);
            AfxMessageBox("The resolution change will not take effect until application restart.");
        }
        PTGreySetProperty("MinDisparity", &m_ptOptions->m_minDisp);
        PTGreySetProperty("MaxDisparity", &m_ptOptions->m_maxDisp);
        PTGreySetProperty("DisparityThreshold", &m_ptOptions->m_dispThresh);
        PTGreySetProperty("DifferenceThreshold", &m_ptOptions->m_diffThresh);
        PTGreySetProperty("DepthThreshold", &m_ptOptions->m_depthThresh);
        PTGreySetProperty("ContourProcessing", &m_ptOptions->m_checkContours);
        PTGreyUnFreezeData();

        // Save StereoGR options
        m_findHand.m_maskImprovigFlag = m_grOptions->m_maskImprove;
        m_findHand.m_trainFrameCount = m_grOptions->m_frameCount;
        m_findHand.m_segThresh = m_grOptions->m_segThresh;

        //change HMM parameters of gestures
        
        m_dgServer.SetHMMParams( m_hmmParams->m_num_states, m_hmmParams->m_num_mix );
        
		m_findHand.m_dGestureName = m_dgProp->GetGestureName();
		m_findHand.m_dynamicGesture = m_dgProp->IsCollectGesture();
		m_findHand.m_saveDynGest =  m_dgProp->IsSaveToFile();
		m_findHand.m_path = m_dgProp->GetSavePath();
    }
}


void CStereoGRApp::OnSaveDynamicGestures() 
{
	int numgest = m_dgServer.GetNumGestures();
    for( int i = 0; i < numgest; i++ )
    {
        CDynGesture* gesture = m_dgServer.GetGesture( i );
        CString path = gesture->GetName();
        gesture->SaveParams( path );
    }
    // TODO: Add your command handler code here
}

CStereoGRApp::LoadSettings()
{
	// Create property pages    
	CreatePropertyPages();
    // Load the PTGrey settings
    char * _settings[] = {
        "CameraBrightness",
        "CameraIris",
        "CameraExposure",
        "MinDisparity",
        "MaxDisparity",
        "DisparityThreshold",
        "DifferenceThreshold",
        "DepthThreshold"
    };

    for(int i = 0; i < sizeof(_settings)/sizeof(char*); i++)
    {
        int value;
        PTGreyGetProperty(_settings[i], &value);
        value = GetProfileInt("Settings\\PTGrey", _settings[i], value);
        PTGreySetProperty(_settings[i], &value);
    }

    // Load the StereoGR settings
    m_findHand.m_segThresh = GetProfileInt("Settings\\PTGrey", "Segmentation threshold", m_findHand.m_segThresh);
    m_findHand.m_trainFrameCount = GetProfileInt("Settings\\PTGrey", "Train framecount", 
        m_findHand.m_trainFrameCount);
    m_findHand.m_maskImprovigFlag = GetProfileInt("Settings\\PTGrey", "Improve mask", 
        m_findHand.m_maskImprovigFlag);

    // Load HMM settings
    m_hmmParams->m_num_states = GetProfileInt("Settings\\HMM", "Number of states", 5);
    m_hmmParams->m_num_mix = GetProfileInt("Settings\\HMM", "Number of mixtures", 3);

	// Load StereoGR parameters

	RECT mainView;
	mainView.left = GetProfileInt("Settings\\StereoGR", "left", 0);
	mainView.top = GetProfileInt("Settings\\StereoGR", "top", 0);
	mainView.right = mainView.left + GetProfileInt("Settings\\StereoGR", "width", 800);
	mainView.bottom = mainView.top + GetProfileInt("Settings\\StereoGR", "height", 600);
	AfxGetMainWnd()->MoveWindow(&mainView);

	for(i = 0; i < VIEWS_COUNT; i++)
	{
		CString str;
		str.Format("Settings\\StereoGR\\View%d", i);
		POINT view;

		view.x = GetProfileInt(LPCTSTR(str), "left", 0);
		view.y = GetProfileInt(LPCTSTR(str), "top", 0);

		m_TopLefts[i] = view;
	
		if(i == PT_POINTCLOUD_IMAGE || i == GR_MAGICCUBE)
		{
			str.Format("Settings\\StereoGR\\View%d_3d", i);
			POINT view;

			view.x = GetProfileInt(LPCTSTR(str), "left", 0);
			view.y = GetProfileInt(LPCTSTR(str), "top", 0);

			m_TopLefts3D[i] = view;
		}
	}

    m_dgProp->m_savePath = m_modulePath;
    return TRUE;
}

CStereoGRApp::SaveSettings()
{
    // Load the PTGrey settings
    char * _settings[] = {
        "CameraBrightness",
        "CameraIris",
        "CameraExposure",
        "MinDisparity",
        "MaxDisparity",
        "DisparityThreshold",
        "DifferenceThreshold",
        "DepthThreshold"
    };

    for(int i = 0; i < sizeof(_settings)/sizeof(char*); i++)
    {
        int value;
        PTGreyGetProperty(_settings[i], &value);
        WriteProfileInt("Settings\\PTGrey", _settings[i], value);
    }

    // Load the StereoGR settings
    WriteProfileInt("Settings\\PTGrey", "Segmentation threshold", m_findHand.m_segThresh);
    WriteProfileInt("Settings\\PTGrey", "Train framecount", m_findHand.m_trainFrameCount);
    WriteProfileInt("Settings\\PTGrey", "Improve mask", m_findHand.m_maskImprovigFlag);

    // Load HMM settings
    WriteProfileInt( "Settings\\HMM", "Number of states", m_hmmParams->m_num_states );
    WriteProfileInt( "Settings\\HMM", "Number of mixtures", m_hmmParams->m_num_mix );

	// Saving the views positions

	RECT mainRect;
	AfxGetMainWnd()->GetWindowRect(&mainRect);
	WriteProfileInt("Settings\\StereoGR", "left", mainRect.left);
	WriteProfileInt("Settings\\StereoGR", "top", mainRect.top);
	WriteProfileInt("Settings\\StereoGR", "width", mainRect.right - mainRect.left);
	WriteProfileInt("Settings\\StereoGR", "height", mainRect.bottom - mainRect.top);

    
    return TRUE;
}

int CStereoGRApp::ExitInstance() 
{
//    SaveSettings();	
	int ret = CWinApp::ExitInstance();
	PTGreyExitCamera(2);
	return ret;
}


void CStereoGRApp::OnLoadDynamicGestures() 
{
    int numgest = 6;
    char* names[6] = { "Rotate left", "Rotate right", "Move up", 
                       "Move down", "Zoom out", "Zoom in" };

    for( int i = 0; i < numgest; i++ )
    {
        CDynGesture* gesture = new CDynGesture(m_hmmParams->m_num_states, m_hmmParams->m_num_mix );
        CString path = names[i];
        if ( gesture->LoadParams( path ) )
        {
             gesture->SetName( path );
             //add to dgServer
             m_dgServer.AddGesture( gesture );
        }
        else delete gesture;  
    }
}

void CStereoGRApp::OnSaveBase() 
{
    CFileDialog dlg( FALSE, 0, 0, /*OFN_ALLOWMULTISELECT | */OFN_ENABLESIZING |
                     OFN_EXPLORER,
                     "Dynamic Gesture base (*.txt) |*.txt|", 0 );
    
    if ( dlg.DoModal() == IDOK )
    {           
        m_dgServer.SaveGestureBase( dlg.GetFileName() );
    }
	// TODO: Add your command handler code here	
}

void CStereoGRApp::OnLoadBase() 
{
    CFileDialog dlg( TRUE, 0, 0, /*OFN_ALLOWMULTISELECT | */OFN_ENABLESIZING |
                     OFN_EXPLORER,
                     "Dynamic Gesture base (*.txt) |*.txt|", 0 );
    
    if ( dlg.DoModal() == IDOK )
    {
        m_dgServer.LoadGestureBase( dlg.GetFileName() );
    }
}

void CStereoGRApp::OnRecogFileDg() 
{
	// TODO: Add your command handler code here
    CFileDialog dlg( TRUE, 0, 0, /*OFN_ALLOWMULTISELECT | */OFN_ENABLESIZING |
                     OFN_EXPLORER | OFN_FILEMUSTEXIST,
                     "Dynamic Gesture observations (*.obs) |*.obs|", 0 );

    if ( dlg.DoModal()== IDOK )
    {
        float likelihood[10] = {-1, -1, -1, -1, -1, 
                              -1, -1, -1, -1, -1 };

        CDynGesture gesture(m_hmmParams->m_num_states, m_hmmParams->m_num_mix );
        gesture.LoadSequence( dlg.GetFileName() );
        gesture.ExtractObservations();

        m_dgServer.TrainAllGestures();

        int rg = m_dgServer.RecognizeDynGesture( &gesture, likelihood );

        //write result to status bar
		CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	    frame->GetStatusBar()->SetPaneText(2, "");
		CString RecogResult;
		RecogResult.Format("Recognized %s likelihood %f", 
            m_dgServer.GetGesture( rg )->GetName(), likelihood[0] );				
	    frame->GetStatusBar()->SetPaneText(2, RecogResult); 
    }
}




void CStereoGRApp::OnDeleteHmm() 
{
    m_dgServer.DeleteHMMInfo();
	// TODO: Add your command handler code here
	
}

void CStereoGRApp::OnRemoveAllDg() 
{
	m_dgServer.CleanAll();// TODO: Add your command handler code here
	
}


void CStereoGRApp::Zoom()
{
	
}


void CStereoGRApp::CreatePropertyPages()
{
    m_hmmParams = new CHMMParams;
    m_ptOptions = new CPTOptions;
    m_grOptions = new CGROptions;
    m_dgStat = new CDGStat;
	m_dgProp = new CDGProp;
}

void CStereoGRApp::OnUpdateRungestrec(CCmdUI* pCmdUI) 
{
	// This feature is disabled in the current release
	pCmdUI->Enable(FALSE);
}
