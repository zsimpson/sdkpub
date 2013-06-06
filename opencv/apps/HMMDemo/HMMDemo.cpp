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
//M*/// HMMDemo.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "HMMDemo.h"

#include "MainFrm.h"
#include "HMMDemoDoc.h"
#include "HMMDemoView.h"

#include "FaceBase.h"
#include "ContEHMM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMMDemoApp

BEGIN_MESSAGE_MAP(CHMMDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CHMMDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_SAVE_CONFIG, OnSaveConfig)
	ON_COMMAND(ID_LOAD_CONFIG, OnLoadConfig)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMMDemoApp construction

CHMMDemoApp::CHMMDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHMMDemoApp object

CHMMDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHMMDemoApp initialization

BOOL CHMMDemoApp::InitInstance()
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

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHMMDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHMMDemoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
    
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
    
    m_dlgHMMParams = new CHMMParams;
    m_dlgSamplingParams = new CSamplingParams;
    m_dlgMiscParams = new CMiscParams;

    //****************Load Settings (stored in registry)*************************************/
    CString states_string;  
    
    int numbers[8]; //maximum superstates is 7

    //read number of HMM states
    states_string = GetProfileString( "Settings\\HMM", "NumStates", "5 3 6 6 6 3" );
    
    //parse string
    sscanf( states_string, "%d %d %d %d %d %d %d %d", 
           &numbers[0], &numbers[1], &numbers[2], &numbers[3],
           &numbers[4], &numbers[5], &numbers[6], &numbers[7] );
            
        
    m_dlgHMMParams->m_States[0]  = numbers[0];
    for( int i = 0 ; i < m_dlgHMMParams->m_States[0] ; i++ )
    {
        m_dlgHMMParams->m_States[ i + 1 ] = numbers[i+1] ;
    }
    
    //read number of mixtures
    m_dlgHMMParams->m_NumMix = GetProfileInt("Settings\\HMM", "NumMix", 3 );
    
    //read sampling parameters (dctSize, obsSize, delta)
    
    m_dlgSamplingParams->m_dctSize.width = GetProfileInt("Settings\\Sampling", "WindowWidth", 12 );
    m_dlgSamplingParams->m_dctSize.height = GetProfileInt("Settings\\Sampling", "WindowHeight", 12 );

    m_dlgSamplingParams->m_obsSize.width = GetProfileInt("Settings\\Sampling", "DCTCoeffX", 3 );
    m_dlgSamplingParams->m_obsSize.height = GetProfileInt("Settings\\Sampling", "DCTCoeffY", 3 );

    m_dlgSamplingParams->m_delta.width = GetProfileInt("Settings\\Sampling", "DeltaX", 4 );
    m_dlgSamplingParams->m_delta.height = GetProfileInt("Settings\\Sampling", "DeltaY", 4 );
    
    //read scaling params
    m_dlgMiscParams->m_useWidth    = GetProfileInt("Settings\\Scaling", "UseFixedWidth", 0 );
    m_dlgMiscParams->m_FixedWidth  = GetProfileInt("Settings\\Scaling", "FixedWidth", 0 );
    m_dlgMiscParams->m_useHeight   = GetProfileInt("Settings\\Scaling", "UseFixedHeight", 0 );
    m_dlgMiscParams->m_FixedHeight = GetProfileInt("Settings\\Scaling", "FixedHeight", 0 );
   
    m_dlgMiscParams->m_SuppressIntensity = GetProfileInt("Settings\\Scaling", "SuppressIntensity", 1 );
   
    //*******************************End Loading Settings *************************************/
        
	return TRUE;
}

void CHMMDemoApp::SaveSettings()
{
    //****************Save Settings into registry)*************************************/
    CString states_string;
    
    //write number of states 
    states_string.Format("%d",  m_dlgHMMParams->m_States[0] );
    for( int i = 0 ; i < m_dlgHMMParams->m_States[0] ; i++ )
    {
        CString add;
        add.Format(" %d", m_dlgHMMParams->m_States[ i + 1 ] );
        states_string+= add;
    }
    //write number of HMM states
    WriteProfileString( "Settings\\HMM", "NumStates", states_string );
    
    //write number of mixtures
    WriteProfileInt("Settings\\HMM", "NumMix", m_dlgHMMParams->m_NumMix );
    
    //write sampling parameters (dctSize, obsSize, delta)
    WriteProfileInt("Settings\\Sampling", "WindowWidth" , m_dlgSamplingParams->m_dctSize.width );
    WriteProfileInt("Settings\\Sampling", "WindowHeight", m_dlgSamplingParams->m_dctSize.height );

    WriteProfileInt("Settings\\Sampling", "DCTCoeffX", m_dlgSamplingParams->m_obsSize.width );
    WriteProfileInt("Settings\\Sampling", "DCTCoeffY", m_dlgSamplingParams->m_obsSize.height );

    WriteProfileInt("Settings\\Sampling", "DeltaX", m_dlgSamplingParams->m_delta.width );
    WriteProfileInt("Settings\\Sampling", "DeltaY", m_dlgSamplingParams->m_delta.height );
    //*******************************End saving Settings *************************************/

    //write scaling params
    WriteProfileInt("Settings\\Scaling", "UseFixedWidth" , m_dlgMiscParams->m_useWidth );
    WriteProfileInt("Settings\\Scaling", "FixedWidth", m_dlgMiscParams->m_FixedWidth );

    WriteProfileInt("Settings\\Scaling", "UseFixedHeight", m_dlgMiscParams->m_useHeight);
    WriteProfileInt("Settings\\Scaling", "FixedHeight", m_dlgMiscParams->m_FixedHeight );

    WriteProfileInt("Settings\\Scaling", "SuppressIntensity", m_dlgMiscParams->m_SuppressIntensity );

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
void CHMMDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHMMDemoApp message handlers
// App command to run the dialog
void CHMMDemoApp::OnFileOpen()
{
	CFileDialog dlg( TRUE, 0, 0, OFN_ALLOWMULTISELECT | OFN_ENABLESIZING |
                     OFN_EXPLORER | OFN_FILEMUSTEXIST,
                     "Face Base Files (*.txt)|*.txt|"
                     "Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg|"
                     "All Files (*.*)|*.*||", 0 );
    int   buf_size = 1 << 15;
    char* buffer = (char*)malloc(buf_size + 100);

    dlg.m_ofn.lpstrFile = buffer;
    buffer[0] = '\0';
    dlg.m_ofn.nMaxFile = buf_size;
    int result = dlg.DoModal();

    if( result == IDOK )
    {
        POSITION pos = dlg.GetStartPosition();

        if( pos ) /* at least one image in the list */
        {
            CHMMDemoView* view = GetCameraView();
            
            view->SetImageList(0);          
            
            CStringList* imageList = new CStringList;

            while( pos )
            {
                imageList->AddTail( dlg.GetNextPathName(pos));
            }

            view->SetImageList( imageList );
            
            CWinApp::OpenDocumentFile( imageList->GetHead() );
        }
    }

    free( buffer );
}


void CHMMDemoApp::OnSettings() 
{
	CPropertySheet sheet;
    sheet.AddPage( m_dlgHMMParams );
    sheet.AddPage( m_dlgSamplingParams );
    sheet.AddPage( m_dlgMiscParams );     
    
    if(sheet.DoModal() == IDOK)
    {
        CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
        CHMMDemoDoc* doc = mainframe->GetCameraView()->GetDocument();
        CFaceBase& base = doc->GetFaceBase();

        base.SetParams( m_dlgSamplingParams->m_dctSize, 
                        m_dlgSamplingParams->m_obsSize,
                        m_dlgSamplingParams->m_delta,         
                        m_dlgHMMParams->m_States, 
                        m_dlgHMMParams->m_NumMix,
                        m_dlgMiscParams->m_useWidth,
                        m_dlgMiscParams->m_FixedWidth,
                        m_dlgMiscParams->m_useHeight, 
                        m_dlgMiscParams->m_FixedHeight,
                        m_dlgMiscParams->m_SuppressIntensity);                
    }

       
}

void CHMMDemoApp::OnSaveConfig() 
{
    CFileDialog dlg( FALSE, 0, 0, /*OFN_ALLOWMULTISELECT | */OFN_ENABLESIZING |
                     OFN_EXPLORER,
                     "Config file (*.txt) |*.txt|", 0 );
    

    if ( dlg.DoModal() == IDOK )
    {     
        int res = SaveConfig( dlg.GetFileName()  );
        ASSERT(res);
    }         
}
void CHMMDemoApp::OnLoadConfig() 
{
    CFileDialog dlg( TRUE, 0, 0, /*OFN_ALLOWMULTISELECT | */OFN_ENABLESIZING |
        OFN_EXPLORER,
        "Config file (*.txt) |*.txt|", 0 );
    
    
    if ( dlg.DoModal() == IDOK )
    {   
        int res = LoadConfig( dlg.GetFileName(), true ); 
        ASSERT( res );
        
    } 
}

int CHMMDemoApp::ExitInstance() 
{        
    SaveSettings();	
    return CWinApp::ExitInstance();
}

//loads config file without clearing base info
int CHMMDemoApp::LoadConfig(const char *filename, bool synchronize_base)
{
    CvSize dctSize, delta, obsSize;
    char str[128];
    int value;
    
    FILE* file = fopen( filename, "r" );
    if ( !file ) return 0; 
    
    //set initial values
     m_dlgMiscParams->m_useWidth = FALSE;
     m_dlgMiscParams->m_FixedWidth = 0;
     m_dlgMiscParams->m_useHeight = FALSE;
     m_dlgMiscParams->m_FixedHeight = 0;
     m_dlgMiscParams->m_SuppressIntensity = FALSE;
    
    while ( !feof(file) )
    {
        fscanf( file, "%s %d", str, &value );
        
        //here we allow config file to be not hard defined
        //Is it useful? - I don't know
        if ( strcmp( "WindowWidth", str ) == 0 )
        {
            dctSize.width = value;                
        }
        else if ( strcmp( "WindowHeight", str ) == 0 )
        {
            dctSize.height = value;
        }
        else if ( strcmp( "DeltaX", str ) == 0 )
        {
            delta.width = value;
        }
        else if ( strcmp( "DeltaY", str ) == 0 )
        {
            delta.height = value;
        }
        else if ( strcmp( "DCTcoeffX", str ) == 0 )
        {
            obsSize.width = value;
        }
        else if ( strcmp( "DCTcoeffY", str ) == 0 )
        {
            obsSize.height = value;
        }   
        else if ( strcmp( "SuperStates", str ) == 0 )
        {
            m_dlgHMMParams->m_States[0] = value;
        } 
        else if ( strcmp( "States", str ) == 0 )
        {
            //scan states
            ASSERT( m_dlgHMMParams->m_States[0] );//superstates must be already loaded
            m_dlgHMMParams->m_States[1] = value;
            for(int i = 1; i < m_dlgHMMParams->m_States[0]; i++ )
            {
                fscanf(file, "%d", &m_dlgHMMParams->m_States[i+1] );
            }
        }
        else if ( strcmp( "NumMixtures", str ) == 0 )
        {
            m_dlgHMMParams->m_NumMix = value;
        }               
        else if ( strcmp( "FIXED_WIDTH", str ) == 0 )
        {
            m_dlgMiscParams->m_useWidth = TRUE;
            m_dlgMiscParams->m_FixedWidth = value;
        }   
        else if ( strcmp( "FIXED_HEIGHT", str ) == 0 )
        {
            m_dlgMiscParams->m_useHeight = TRUE;
            m_dlgMiscParams->m_FixedHeight = value;
        }
        else if ( strcmp( "SUPPRESS_INTENSITY", str ) == 0 )
        {
            m_dlgMiscParams->m_SuppressIntensity = TRUE;
        }   
        else
        {
            //do nothing
        }
    }
    
    //check correctness of loaded file
    if ( (dctSize.width < obsSize.width)||
        (dctSize.height < obsSize.height) )
    {
        //error message 
        DoMessageBox( "Wrong parameters in config file\nNew parameters were not loaded", MB_OK|MB_ICONSTOP, 0 );
    }
    
    //initialize application variables
    m_dlgSamplingParams->m_dctSize = dctSize;
    m_dlgSamplingParams->m_obsSize = obsSize;
    m_dlgSamplingParams->m_delta = delta;  
    
    fclose( file ); 
    
    if (synchronize_base)
    {
        CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
        CHMMDemoDoc* doc = mainframe->GetCameraView()->GetDocument();
        CFaceBase& base = doc->GetFaceBase();

        return base.SetParams( //sampling params
                                m_dlgSamplingParams->m_dctSize, 
                                m_dlgSamplingParams->m_obsSize, 
                                m_dlgSamplingParams->m_delta,
                                //HMM params
                                m_dlgHMMParams->m_States, 
                                m_dlgHMMParams->m_NumMix,
                                //image scaling params
                                m_dlgMiscParams->m_useWidth,
                                m_dlgMiscParams->m_FixedWidth,
                                m_dlgMiscParams->m_useHeight, 
                                m_dlgMiscParams->m_FixedHeight,
                                //intensity suppression
                                m_dlgMiscParams->m_SuppressIntensity, 1 );
    }
    return 1;
}
int CHMMDemoApp::SaveConfig(const char* filename) 
{
        FILE* file = fopen( filename, "wt" );
        if (!file) { ASSERT(0); return 0; }

        fprintf( file, "***********Sampling params************\n" );
        fprintf( file, "WindowWidth  %d\n" ,  m_dlgSamplingParams->m_dctSize.width );
        fprintf( file, "WindowHeight %d\n",  m_dlgSamplingParams->m_dctSize.height );
        fprintf( file, "DeltaX %d\n" , m_dlgSamplingParams->m_delta.width );
        fprintf( file, "DeltaY %d\n",    m_dlgSamplingParams->m_delta.height );
        fprintf( file, "DCTcoeffX %d\n" , m_dlgSamplingParams->m_obsSize.width );
        fprintf( file, "DCTcoeffY %d\n",  m_dlgSamplingParams->m_obsSize.height ); 

        fprintf( file, "***************HMM params*************\n" );
        fprintf( file, "SuperStates %d\n",    m_dlgHMMParams->m_States[0] );
        fprintf( file, "States");
        for( int i = 0; i < m_dlgHMMParams->m_States[0]; i++ )
        {
            fprintf( file, " %d", m_dlgHMMParams->m_States[i+1] );
        }
        fprintf( file, "\n" );
        fprintf( file, "NumMixtures %d\n", m_dlgHMMParams->m_NumMix );

        fprintf( file, "***************Misc. params*************\n" );
        if( m_dlgMiscParams->m_useWidth )
            fprintf( file, "FIXED_WIDTH %d\n", m_dlgMiscParams->m_FixedWidth );
        if( m_dlgMiscParams->m_useHeight )
            fprintf( file, "FIXED_HEIGHT %d\n", m_dlgMiscParams->m_FixedHeight );
        if( m_dlgMiscParams->m_SuppressIntensity )
            fprintf( file, "SUPPRESS_INTENSITY %d\n", m_dlgMiscParams->m_SuppressIntensity );
        
        fclose( file );
   return 1;
}
