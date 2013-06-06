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
//M*/// VMDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VMDemo.h"
#include "VMDemoDlg.h"
#include "raster.h"
#include <assert.h>
#include "resource.h"

#include "CV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/*======================================================================================*/

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}


/*======================================================================================*/

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}


/*======================================================================================*/

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVMDemoDlg dialog

CVMDemoDlg::CVMDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CVMDemoDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CVMDemoDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    numScanlines    = 0;
    RasterLeft      = new CRaster;
    RasterRight     = new CRaster;
    RasterResult    = new CRaster;

    HaveMorph       =   false;

    scanlines_1		= 0;
    scanlines_2		= 0;
    scanlines_a		= 0;

    lens_1          = 0;
    lens_2          = 0;
    morph_lens      = 0;

    runs_1          = 0;
    runs_2          = 0;

    buffer_1        = 0;
    buffer_2        = 0;
    morph_buffer    = 0;

    num_runs_1      = 0;
    num_runs_2      = 0;

    corr_1          = 0;
    corr_2          = 0;


    prevpos         = -100;

    CanMorph        = false;

}


/*======================================================================================*/

void CVMDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CVMDemoDlg)
	DDX_Control(pDX, IDC_SHOWSCANLINES, m_showscanlines);
    DDX_Control(pDX, IDC_IMAGESIZE, m_imagesize);
    DDX_Control(pDX, IDC_CAMERAPOS, m_camerapos);
	//}}AFX_DATA_MAP
}


/*======================================================================================*/

BEGIN_MESSAGE_MAP(CVMDemoDlg, CDialog)
    //{{AFX_MSG_MAP(CVMDemoDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_OPENPROJECT, OnOpenproject)
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_ORIGINALSIZE, OnOriginalsize)
    ON_BN_CLICKED(IDC_MAKEMORPHING, OnMakemorphing)
	ON_BN_CLICKED(IDC_SHOWSCANLINES, OnShowscanlines)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVMDemoDlg message handlers

BOOL CVMDemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here

    //////////////
    RightImage  = 0;
    LeftImage   = 0;

    RECT rect;

    rect.left   = 70;
    rect.top    = 10;
    rect.right  = 200;
    rect.bottom = 300;

    CString className;
    className   = AfxRegisterWndClass(NULL);

    LeftImage   = 0;
    RightImage  = 0;
    ResultImage = 0;

    LeftImage   = new CVirtualImage;

    LeftImage   ->CreateEx( WS_EX_OVERLAPPEDWINDOW,
                            className,
                            "Left Base Image",
                            WS_VISIBLE | WS_OVERLAPPED |WS_THICKFRAME,
                            rect,
                            NULL,
                            0);

    RightImage	= new CVirtualImage;

    RightImage	->CreateEx( WS_EX_OVERLAPPEDWINDOW,
                            className,
                            "Right Base Image",
                            WS_VISIBLE | WS_OVERLAPPED |WS_THICKFRAME,
                            rect,
                            NULL,
                            0);



////
    ResultImage	= new CVirtualImage;

    ResultImage	->CreateEx( WS_EX_OVERLAPPEDWINDOW,
                            className,
                            "Virtual Image",
                            WS_VISIBLE | WS_OVERLAPPED |WS_THICKFRAME,
                            rect,
                            NULL,
                            0);

    LeftImage   -> SetScanlines(&scanlines_2,&numScanlines);
    LeftImage   -> SetRasterImage(RasterLeft);
    LeftImage   -> ShowWindow(SW_SHOW);

    RightImage  -> SetScanlines(&scanlines_1,&numScanlines);
    RightImage  -> SetRasterImage(RasterRight);
    RightImage  -> ShowWindow(SW_SHOW);

    ResultImage -> SetScanlines(&scanlines_a,&numScanlines);
    ResultImage -> SetRasterImage(RasterResult);
    ResultImage -> ShowWindow(SW_SHOW);


    SetWindowsToTop();

    m_camerapos.SetRange(0,300);// ition.SetScrollRange(0,300);

    m_imagesize.SetWindowText("");

    return TRUE;  // return TRUE  unless you set the focus to a control
}


/*======================================================================================*/

void CVMDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}


/*======================================================================================*/

void CVMDemoDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}


/*======================================================================================*/

HCURSOR CVMDemoDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}


/*======================================================================================*/

void CVMDemoDlg::OnOpenproject()
{
    SetWindowsToTop();

    CFileDialog filedialog(
                            TRUE,// Open Dialog
                            NULL,//Default extension
                            NULL,//Initial file name
                            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Flag
                            "Project Files (*.ini;*.cpj)|*.ini;*.cpj|All Files (*.*)|*.*|");//Fiter

    if (filedialog.DoModal()==IDOK) {
        CString projectName=filedialog.GetPathName();

        //char path_buffer[_MAX_PATH];
        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];

        _splitpath(projectName,drive,dir,fname,ext );

        if (stricmp(ext,".cpj") == 0)
        {
            useScanlines = 1;
        }
        else
        {
            useScanlines = 0;
        }

        CString projname;


        long numPicts;
        
        numPicts = ::GetPrivateProfileInt(    "Project",
                                            "NumberOfPicturePairs",
                                            0,
                                            projectName);

        if (numPicts > 0) {

    
        /* Load Left Image */
            char    buff[_MAX_PATH];
            ::GetPrivateProfileString(  "Pair1",
                                        "Image1",
                                        "",
                                        buff,
                                        MAX_PATH,
                                        projectName );

            RasterLeft  ->LoadBMP(buff);
            {// Flip the Image
                char    *tmpBuff;
                int     step,h,w,y;
                char    *src;
                char    *dest;

                step    = RasterLeft->GetSizeString();
                h       = RasterLeft->GetHeight();
                w       = RasterLeft->GetWidth();

                src = (char*)(RasterLeft->GetImage());
                dest = src + step * (h - 1);

                tmpBuff = (char*)calloc(step,1);

                for (y = 0; y < h/2; y++) {
                    memcpy(tmpBuff,src,step);
                    memcpy(src,dest,step);
                    memcpy(dest,tmpBuff,step);

                    src     += step;
                    dest    -= step;
                }

                free(tmpBuff);
            }

            LeftImage   ->Invalidate();



            ::GetPrivateProfileString(  "Pair1",
                                        "Image2",
                                        "",
                                        buff,
                                        MAX_PATH,
                                        projectName );

            RasterRight ->LoadBMP(buff) ;
            {// Flip the Image
                char    *tmpBuff;
                int     step,h,w,y;
                char    *src;
                char    *dest;

                step    = RasterRight->GetSizeString();
                h       = RasterRight->GetHeight();
                w       = RasterRight->GetWidth();

                src = (char*)(RasterRight->GetImage());
                dest = src + step * (h - 1);

                tmpBuff = (char*)calloc(step,1);

                for (y = 0; y < h/2; y++) {
                    memcpy(tmpBuff,src,step);
                    memcpy(src,dest,step);
                    memcpy(dest,tmpBuff,step);

                    src     += step;
                    dest    -= step;
                }

                free(tmpBuff);
            }
        
            RightImage  ->Invalidate();


        if (    (RasterLeft -> GetWidth()	!= RasterRight -> GetWidth()) ||
                (RasterLeft -> GetHeight()	!= RasterRight -> GetHeight())
                ) {
            CanMorph	= false;
            m_imagesize.SetWindowText("");

        } else {
            CanMorph	= true;
            char st[300];
            sprintf(st,"%dx%d",RasterLeft -> GetWidth(),RasterLeft -> GetHeight());
            m_imagesize.SetWindowText(st);


            RasterResult	-> CreateRaster(    RasterLeft -> GetWidth(),
                                                RasterLeft -> GetHeight(),
                                                24);

            ResultImage		-> Invalidate();
        }



        /* Read Fundamental matrix */

        char strf[102];

        ::GetPrivateProfileString(  "FundMatrix","F[0][0]","0.0",strf,100,projectName);
        FundMatrix.m[0][0] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[0][1]","0.0",strf,100,projectName);
        FundMatrix.m[0][1] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[0][2]","0.0",strf,100,projectName);
        FundMatrix.m[0][2] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[1][0]","0.0",strf,100,projectName);
        FundMatrix.m[1][0] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[1][1]","0.0",strf,100,projectName);
        FundMatrix.m[1][1] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[1][2]","0.0",strf,100,projectName);
        FundMatrix.m[1][2] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[2][0]","0.0",strf,100,projectName);
        FundMatrix.m[2][0] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[2][1]","0.0",strf,100,projectName);
        FundMatrix.m[2][1] = (float)atof(strf);

        ::GetPrivateProfileString(  "FundMatrix","F[2][2]","0.0",strf,100,projectName);
        FundMatrix.m[2][2] = (float)atof(strf);




        /////////////////////////////


        FreeMemory();
        AllocMemory();
        HaveMorph   = false;



        }/* in project > 0 pictures*/
    }/* if dialog */

}


/*======================================================================================*/

void CVMDemoDlg::SetWindowsToTop()
{
    CDC *dc;
    dc      = GetDC();

    int width,height;

    width   = GetDeviceCaps( dc->m_hDC, HORZRES);
    height  = GetDeviceCaps( dc->m_hDC, VERTRES);

    ReleaseDC(dc);

    LeftImage   -> MoveWindow(0, 0, width / 3, height / 3);
    ResultImage -> MoveWindow(width / 3, 0, width / 3, height / 3);
    RightImage  -> MoveWindow(width - width / 3, 0, width / 3,height / 3);
}


/*======================================================================================*/

void CVMDemoDlg::OnMakemorphing()
{
    if (CanMorph) {
        CvSize imgsize;
        CvMatrix3  matrix;

        IplImage* image1;
        CvSize    size1;
        
        IplImage* image2;
        CvSize    size2;

        IplImage* imageRes;
        CvSize    sizeRes;

        image1   = cvCreateImageHeader( cvSize(1,1), 8, 3 );
        image2   = cvCreateImageHeader( cvSize(1,1), 8, 3 );
        imageRes = cvCreateImageHeader( cvSize(1,1), 8, 3 );


        size1.width   = RasterLeft->GetWidth();
        size1.height  = RasterLeft->GetHeight();

        size2.width   = RasterRight->GetWidth();
        size2.height  = RasterRight->GetHeight();

        sizeRes.width   = RasterRight->GetWidth();
        sizeRes.height  = RasterRight->GetHeight();

        cvInitImageHeader(  image1,
                            size1,
                            8,
                            3,
                            0,
                            4,
                            0);
        
        cvSetImageData( image1,
                        RasterLeft->GetImage(),
                        RasterLeft->GetSizeString() ); 
        
        cvInitImageHeader(  image2,
                            size2,
                            8,
                            3,
                            0,
                            4,
                            0);
        
        cvSetImageData( image2,
                        RasterRight->GetImage(),
                        RasterRight->GetSizeString() ); 

        cvInitImageHeader(  imageRes,
                            sizeRes,
                            8,
                            3,
                            0,
                            4,
                            0);
        
        cvSetImageData( imageRes,
                        RasterResult->GetImage(),
                        RasterResult->GetSizeString() ); 

        imgsize.width   = RasterLeft->GetWidth();
        imgsize.height  = RasterLeft->GetHeight();


        float pos = float(m_camerapos.GetPos());
        pos = pos / (m_camerapos.GetRangeMax() - m_camerapos.GetRangeMin());

        float alpha = pos;

        matrix = FundMatrix;

        m_morpher.SetPan( alpha );

//#define SCANLINE_VARIANT 1

        if( useScanlines == 1 )
        {
//#if SCANLINE_VARIANT
        cvMakeScanlines(    &matrix,
                                    imgsize,
                                    0,
                                    0,
                                    0,
                                    0,
                                    &numScanlines);
        }
//#endif

        if (!HaveMorph) {

        if( useScanlines == 1 )
        {
//#if SCANLINE_VARIANT
            cvMakeScanlines(    &matrix,
                                        imgsize,
                                        scanlines_1,
                                        scanlines_2,
                                        lens_1,
                                        lens_2,
                                        &numScanlines);
            /* Prewarp first image */
            cvPreWarpImage( numScanlines,
                                        image1,
                                        buffer_1,
                                        lens_1,
                                        scanlines_1);
            

            /* Prewarp second image */
            cvPreWarpImage( numScanlines,
                                        image2,
                                        buffer_2,
                                        lens_2,
                                        scanlines_2);
            

            /* Create Runs on first Image */
            cvFindRuns(          numScanlines,
                                        buffer_1,   /* prewarp image				*/
                                        buffer_2,
                                        lens_1,     /* prewarp line lens in pixels	*/
                                        lens_2,
                                        runs_1,     /* first runs					*/
                                        runs_2,
                                        num_runs_1, /* number of first runs			*/
                                        num_runs_2);

            cvDynamicCorrespondMulti(
                                                numScanlines,         // number of scanlines
                                                runs_1,         // s0|w0|s1|w1|...
                                                num_runs_1,    // numbers of runs
                                                runs_2,
                                                num_runs_2,
                                                corr_1,    // s0'|e0'|s1'|e1'|...

                                                        corr_2 );
        }
        else
        {
//#else
            #ifndef PIXELTOPIXEL
            m_morpher.SetPointCount( 200 );
            #endif
            m_morpher.SetLeftImage( image1 );
            m_morpher.SetRightImage( image2 );
//#endif
        }
            HaveMorph   = true;

        }

        if( useScanlines == 1 )
        {
//#if SCANLINE_VARIANT
        cvMakeAlphaScanlines(    scanlines_1,
                                        scanlines_2,
                                        scanlines_a,
                                        morph_lens,
                                        numScanlines,
                                        alpha);


        cvMorphEpilinesMulti(
                        numScanlines,       /* number of lines                              */
                        buffer_1,       /* raster epilines from the first image         */
                        lens_1,         /* number of pixel in first line                */
                        buffer_2,       /* raster epilines from the second image        */
                        lens_2,         /* number of pixel in second line               */
                        morph_buffer,   /* raster epiline from the destination image    */
                                        /* (it's an output parameter)                   */
                        morph_lens,     /* numbers of pixel in output line              */
                        alpha,          /* relative position of camera                  */
                        runs_1,         /* first sequence of runs                       */
                        num_runs_1,     /* it's length                                  */
                        runs_2,         /* second sequence of runs                      */
                        num_runs_2,     /*                                              */
                        corr_1,         /* correspond information for the 1st seq       */
                        corr_2);        /* correspond information for the 2nd seq       */
        


        memset(RasterResult->GetImage(),0,imgsize.width * imgsize.height*3);

        cvPostWarpImage(
                    numScanlines,                       /* number of scanlines  */
                    morph_buffer,                   /* source buffers       */
                    morph_lens,                     /* lens of buffers      */
                    imageRes,       /* dest image           */
                    scanlines_a                     /* scanline             */
            );
        
        cvDeleteMoire(  imageRes);
        }
        else
        {
//#else
        m_morpher.SetPan( alpha );
        {
            IplImage* img = m_morpher.GetVirtualImage();
            //IplImage* img = m_morpher.GetDisparityImage(); // if disparity image needed
            //iplCopy( m_morpher.GetVirtualImage(), imageRes );
            cvCopy( img, imageRes );
        }
//#endif
        }
        ResultImage->RedrawWindow();

        cvReleaseImageHeader(&image1);
        cvReleaseImageHeader(&image2);
        cvReleaseImageHeader(&imageRes);
    }/* if CanMorph */
}


/*======================================================================================*/

CVMDemoDlg::~CVMDemoDlg()
{
    if (RasterLeft      != 0)   delete RasterLeft;
    if (RasterRight     != 0)   delete RasterRight;
    if (RasterResult    != 0)   delete RasterResult;
    if (LeftImage       != 0)   delete LeftImage;
    if (RightImage      != 0)   delete RightImage;
    if (ResultImage     != 0)   delete ResultImage;
    FreeMemory();
}


/*======================================================================================*/

void CVMDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (
        ((CSliderCtrl*)(pScrollBar) == &m_camerapos)
        ) {
        if (abs(prevpos - m_camerapos.GetPos())>4 ) {

            OnMakemorphing();
        }
    }
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


/*======================================================================================*/

void CVMDemoDlg::OnOriginalsize()
{
    SetWindowsToTop();
}


/*======================================================================================*/

void CVMDemoDlg::FreeMemory()
{

    if (scanlines_1     != 0)   free (scanlines_1);
    if (scanlines_2     != 0)   free (scanlines_2);
    if (scanlines_a     != 0)   free (scanlines_a);

    if (lens_1          != 0)   free (lens_1);
    if (lens_2          != 0)   free (lens_2);
    if (morph_lens      != 0)   free (morph_lens);

    if (buffer_1        != 0)   free (buffer_1);
    if (buffer_2        != 0)   free (buffer_2);
    if (morph_buffer    != 0)   free (morph_buffer);

    if (runs_1          != 0)   free (runs_1);
    if (runs_2          != 0)   free (runs_2);

    if (corr_1          != 0)   free (corr_1);
    if (corr_2          != 0)   free (corr_2);

    if (num_runs_1      != 0)   free (num_runs_1);
    if (num_runs_2      != 0)   free (num_runs_2);


    scanlines_1     = 0;
    scanlines_2     = 0;
    scanlines_a     = 0;

    lens_1          = 0;
    lens_2          = 0;
    morph_lens      = 0;

    runs_1          = 0;
    runs_2          = 0;

    buffer_1        = 0;
    buffer_2        = 0;
    morph_buffer    = 0;

    num_runs_1      = 0;
    num_runs_2      = 0;

    corr_1          = 0;
    corr_2          = 0;

}


/*======================================================================================*/

void CVMDemoDlg::AllocMemory()
{
    CvSize     imgsize;

    imgsize.width   = RasterLeft->GetWidth()*3;
    imgsize.height  = RasterLeft->GetHeight()*3;

    int numlines;

    cvMakeScanlines(     0,
                                imgsize,
                                0,
                                0,
                                0,
                                0,
                                &numlines);

    numlines=2400;
    scanlines_1     = (int*)(calloc( numlines * 2, sizeof(int) * 4));
    scanlines_2     = (int*)(calloc( numlines * 2, sizeof(int) * 4));
    scanlines_a     = (int*)(calloc( numlines * 2, sizeof(int) * 4));

    lens_1          = (int*)(calloc( numlines * 2, sizeof(int)*4));
    lens_2          = (int*)(calloc( numlines * 2, sizeof(int)*4));
    morph_lens      = (int*)(calloc( numlines * 2, sizeof(int)*4));

    buffer_1        =
        (uchar*)(malloc(imgsize.width * (imgsize.height+1) * 3 * sizeof(uchar)));

    buffer_2        =
        (uchar*)(malloc(imgsize.width * (imgsize.height+1) * 3 * sizeof(uchar)));

    morph_buffer    =
        (uchar*)(calloc(imgsize.width * (imgsize.height+1), 3 * sizeof(uchar)));

    runs_1          = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));
    runs_2          = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));

    corr_1          = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));
    corr_2          = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));

    num_runs_1      = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));
    num_runs_2      = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));

}

/*======================================================================================*/

void CVMDemoDlg::OnShowscanlines() 
{
    bool canshow = (m_showscanlines.GetCheck()==1);
    LeftImage    ->showScanlines = canshow;
    RightImage   ->showScanlines = canshow;
    ResultImage ->showScanlines = canshow;

    LeftImage    ->Invalidate();
    RightImage   ->Invalidate();
    ResultImage ->Invalidate();

    // TODO: Add your control notification handler code here
	
}
