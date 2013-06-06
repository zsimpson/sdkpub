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
//M*/// StereoGRView.cpp : implementation of the CStereoGRView class
//

#include "stdafx.h"
#include "StereoGR.h"
#include "MainFrm.h"

#include "StereoGRDoc.h"
#include "StereoGRView.h"
#include "ChildFrm.h"
#include "PGControl.h"
#include <math.h>
#include "cv.h"
#include <gl\glu.h>
#include "triclops.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IS_PTGREY_DOCTYPE IS_PTGREY_DATATYPE(GetDocument()->GetDocType())

/////////////////////////////////////////////////////////////////////////////
// CStereoGRView

IMPLEMENT_DYNCREATE(CStereoGRView, CView)

BEGIN_MESSAGE_MAP(CStereoGRView, COpenGLView)
	//{{AFX_MSG_MAP(CStereoGRView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStereoGRView construction/destruction

CStereoGRView::CStereoGRView()
{
    m_image = 0;
    m_auxImage = 0;
    m_recipient = 0;
    m_bitmap = 0;
	memset(m_texture, 0, 3*sizeof(void*));
	memset(m_planes, 0, 3*sizeof(IplImage*));

	m_dist = 0;
	m_azim = 0;
	m_incl = 0;
	m_distInc = 0;
	m_azimInc = 0;
	m_inclInc = 0;
}

CStereoGRView::~CStereoGRView()
{
    ((CMainFrame*)AfxGetMainWnd())->RemoveView(this);
    iplDeallocate(m_image, IPL_IMAGE_ALL);
    cvReleaseImageHeader(&m_recipient);
    if(m_bitmap)
        ::DeleteObject(m_bitmap);

	PTGreyUnFreezeData();

	for(int i = 0; i < 3; i++)
	{
		free(m_texture[i]);
		cvReleaseImage(&m_planes[i]);
	}
}

BOOL CStereoGRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStereoGRView drawing

void CStereoGRView::OnDraw(CDC* pDC)
{
    if(!m_wasInitialized)
        return;


#ifdef _GR_TRACE
    TRACE("OnDraw: time = %d\n", GetTickCount());
#endif
	CStereoGRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	DrawScene(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CStereoGRView printing

BOOL CStereoGRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStereoGRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStereoGRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStereoGRView diagnostics

#ifdef _DEBUG
void CStereoGRView::AssertValid() const
{
	CView::AssertValid();
}

void CStereoGRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStereoGRDoc* CStereoGRView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStereoGRDoc)));
	return (CStereoGRDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStereoGRView message handlers

void CStereoGRView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

    // Update the document
    GetDocument()->Initialize();

    
    // Now initialize the view
    UpdateParams();

    // Initialize the parent's data
    ((CChildFrame*)GetParent())->m_view = this;
    ((CMainFrame*)AfxGetMainWnd())->AddView(this);

    // Initialize OpenGL
    switch(GetDocument()->GetDocType())
    {
	case PT_POINTCLOUD_IMAGE:
	case GR_MAGICCUBE:
        InitGL();
		break;
    }

	UpdatePosition();

    m_wasInitialized = TRUE;
}

void CStereoGRView::UpdateParams()
{
	STEREOGRAPP(app)
    int dataType = GetDocument()->GetDocType();
    int width = PTGreyGetWidth(IS_PTGREY_DOCTYPE ? dataType : PT_RIGHT_RAW_IMAGE);
    int height = PTGreyGetHeight(IS_PTGREY_DOCTYPE ? dataType : PT_RIGHT_RAW_IMAGE);
    m_pixelSize = PTGreyGetPixelSize(IS_PTGREY_DOCTYPE ? dataType : 1);

    ((CChildFrame*)GetParent())->m_imageSize.cx = width;
    ((CChildFrame*)GetParent())->m_imageSize.cy = height;

    if(dataType != PT_POINTCLOUD_IMAGE)
    {
        m_image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
        m_recipient = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, m_pixelSize);
		if(m_pixelSize == 4)
			m_recipient->alphaChannel = 4;
    }

	/* Restoring the window size */
    CWnd* parent = GetParent();
    CRect client, window, mainRect;
    CSize newSize;
    parent->GetClientRect(&client);
    parent->GetWindowRect(&window);
	AfxGetMainWnd()->GetWindowRect(&mainRect);
	POINT tl = app->m_TopLefts[dataType];
	if(tl.x < 0 || tl.x > mainRect.Size().cx)
		tl.x = 0;
	if(tl.y < 0 || tl.y > mainRect.Size().cy)
		tl.y = 0;

    newSize = CSize(width, height) + window.Size() - client.Size();
//    parent->MoveWindow(tl.x, tl.y, newSize.cx, newSize.cy);
//    parent->ShowWindow(SW_SHOW);

    if(!IS_PTGREY_DOCTYPE)
    {
        iplSet(m_image, 0);
        Invalidate();
        UpdateWindow();
    }
}


BOOL CStereoGRView::RetrieveImage()
{
    if(!m_wasInitialized)
        return FALSE;

#ifdef _GR_TRACE
    TRACE("RetrieveImage: time = %d\n", GetTickCount());
#endif
    
    int dataType = GetDocument()->GetDocType();
    
    m_recipient->imageData = const_cast<char*>(PTGreyGetDataPointer(dataType));
    switch(m_pixelSize)
    {
    case 4:
        {
            // Convert the data
            for(int i = 0; i < 3; i++)
            {
                m_image->roi = iplCreateROI(i + 1, 0, 0, m_image->width, m_image->height);
                m_recipient->roi = m_image->roi;
                iplCopy(m_recipient, m_image);
                iplDeleteROI(m_image->roi);
            }
            m_image->roi = 0;
            m_recipient->roi = 0;
            break;
        }
        
    case 1:
        {
            int mind, maxd;
            PTGreyGetProperty("MinDisparity", &mind);
            PTGreyGetProperty("MaxDisparity", &maxd);

            int scale = (int)floor(255.0f/(maxd - mind));
            for(int i = 0; i < 3; i++)
            {
                m_image->roi = iplCreateROI(i + 1, 0, 0, m_image->width, m_image->height);
                m_recipient->roi = iplCreateROI(1, 0, 0, m_image->width, m_image->height);
                iplCopy(m_recipient, m_image);
                if(dataType == PT_DISPARITY_IMAGE)            
                {
                    // Rescale the image
                    iplMultiplyS(m_image, m_image, scale);
                }
                iplDeleteROI(m_image->roi);
                iplDeleteROI(m_recipient->roi);
            }
            m_image->roi = 0;
            m_recipient->roi = 0;

            break;
        }

    default:
        ASSERT(0);
        break;
    }

    return TRUE;
}

void CStereoGRView::OnSize(UINT nType, int cx, int cy) 
{
	
	CStereoGRDoc* pDoc = GetDocument();
	int docType = pDoc->GetDocType();
	if(docType == PT_POINTCLOUD_IMAGE || docType == GR_MAGICCUBE)
		COpenGLView::OnSize(nType, cx, cy);
	else
		CView::OnSize(nType, cx, cy);
	
    InvalidateRect(0, 0);	
    UpdateWindow();
}

BOOL CStereoGRView::OnEraseBkgnd(CDC* pDC) 
{
    return TRUE;
}

void CStereoGRView::Update() 
{
    if(IsNewData())
    {
        UpdateData();
        UpdateView();
        if(GetDocument()->GetDocType() == PT_DISPARITY_IMAGE)
            TRACE0("Updated the image\n");
    }
    else
    {
        DefaultData();
        DefaultView();
        if(GetDocument()->GetDocType() == PT_DISPARITY_IMAGE)
            TRACE0("The image did not change\n");
    }
}

int gl_frame_count = -1;

double camDist = 3, camAzim = 0, camIncl = 0/*-900*/, camX = 0, camY = -0.5;
int shifting = 0, xold, yold, WHICH_BUTTON_ON, DispCount = 0; 
double coneMinX = -0.5, coneMaxX =  0.5, coneMinY = -0.5, coneMaxY =  0.5, coneMaxZ =  1.0;
const MinCloudCount = 200;

void CStereoGRView::InitGL()
{
    // Make the GL window a child of the main frame...
	STEREOGRAPP(app)

	InitOpenGL();

	/* Initialize GL */
	CRect clientRect;
	GetClientRect(&clientRect);
	glViewport(0, 0, clientRect.Size().cx, clientRect.Size().cy);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	if(GetDocument()->GetDocType() == GR_MAGICCUBE)
	{
		/* initialize the model */
		InitMagicCube();
	}
}

void CStereoGRView::ProcessImage()
{
    int dataType = GetDocument()->GetDocType();
}

void CStereoGRView::UpdateData()
{
	int dataType = GetDocument()->GetDocType();
	if(dataType == PT_POINTCLOUD_IMAGE)
	{
		RetrievePointCloud();
	}
	else if(IS_PTGREY_DATATYPE(dataType))
    {
		RetrieveImage();
	}
	else
	{
        RetrieveUserImage();
    }
}

void CStereoGRView::UpdateView()
{
    InvalidateRect(0, 0);
    UpdateWindow();
}

IplImage* CStereoGRView::GetImage()
{
    return m_image;
}

IplImage* CStereoGRView::GetRecipient()
{
    return m_recipient;
}

BOOL CStereoGRView::IsNewData()
{
    int docType = GetDocument()->GetDocType();
    if(IS_PTGREY_DATATYPE(docType))
    {
        return PTGreyIsNewData(docType);
    }
    else
    {
        STEREOGRAPP(app)
        return app->IsNewData();
    }
}

BOOL CStereoGRView::RetrieveUserImage()
{
    int dataType = GetDocument()->GetDocType();
    switch(dataType)
    {
    case GR_MASK_VIEW:
        {
            STEREOGRAPP(app)
            IplImage* image = app->m_findHand.m_mask;
            if(image)
            {
                iplSet(m_image, 0);
                IplROI roi = {0, 0, 0, 0, 0};
                roi.width = image->width;
                roi.height = image->height;
                m_image->roi = &roi;
                for(int i = 0; i < 3; i++)
                {
                    roi.coi = i + 1;
                    iplCopy(image, m_image);
                }
                m_image->roi = 0;
            }
            else
                iplSet(m_image, 0);
        }
        break;
    }

    return TRUE;
}

void CStereoGRView::DefaultData()
{
    switch(GetDocument()->GetDocType())
    {
    case GR_MASK_VIEW:
        iplSet(m_image, 0);
        break;
    }
}

void CStereoGRView::DefaultView()
{
    UpdateView();
}

void CStereoGRView::UpdatePosition()
{
	STEREOGRAPP(app)
	int docType = GetDocument()->GetDocType();
    int width = PTGreyGetWidth(IS_PTGREY_DOCTYPE ? docType : PT_RIGHT_RAW_IMAGE);
    int height = PTGreyGetHeight(IS_PTGREY_DOCTYPE ? docType : PT_RIGHT_RAW_IMAGE);
	CView* view = app->GetView(docType);
	if(view)
	{
		CRect windowRect, clientRect, mainRect;
		CWnd* wnd = GetParent();
		wnd->GetWindowRect(&windowRect);
		wnd->GetClientRect(&clientRect);
		((CMainFrame*)AfxGetMainWnd())->GetClientRect(mainRect);
		CPoint tl = CPoint(app->m_TopLefts[docType]) + mainRect.TopLeft() - CPoint(4, 4);
		if(tl.x == -1)
			return;

		if(tl.x < 0 || tl.x > clientRect.Size().cx)
			tl.x = 0;
		if(tl.y < 0 || tl.y > clientRect.Size().cy)
			tl.y = 0;
		CSize windowSize = CSize(width, height) + windowRect.Size() - clientRect.Size();
		::MoveWindow(wnd->m_hWnd, tl.x, tl.y, windowSize.cx, windowSize.cy, TRUE);
	}
}

void CStereoGRView::OnDrawImage(CDC *pDC)
{
    if(!m_image)
    {
        return;
    }

    HDC hdc;
    hdc = ::CreateCompatibleDC(pDC->m_hDC);

    // Display the current image
    char buffer[sizeof(BITMAPINFO)];
    BITMAPINFO* binfo = (BITMAPINFO*)buffer;
    memset(binfo, 0, sizeof(BITMAPINFOHEADER));
    binfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    if(!m_bitmap)
    {
        // Create the bitmap

        BITMAPINFOHEADER* bih = &binfo->bmiHeader;
		bih->biBitCount = m_image->nChannels*8;
		bih->biWidth = m_image->width;
		bih->biHeight = m_image->height;
        bih->biPlanes = 1;
        bih->biCompression = BI_RGB;
        bih->biSizeImage = 0;
        
        m_bitmap = CreateDIBSection(hdc, binfo, 0, 0, 0, DIB_RGB_COLORS);
    }

    int colors = DIB_RGB_COLORS;
    
    ::SelectObject(hdc, m_bitmap);
	binfo->bmiHeader.biBitCount = 0;
	GetDIBits(hdc, m_bitmap, 0, 0, 0, binfo, colors);
    binfo->bmiHeader.biBitCount = 24;
    binfo->bmiHeader.biHeight = -abs(binfo->bmiHeader.biHeight);
    SetDIBits(hdc, m_bitmap, 0, m_image->height, m_image->imageData, binfo, colors);


    ::SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
    CRect client;
    GetClientRect(&client);
    ::StretchBlt(pDC->m_hDC, 0, 0, client.Size().cx, client.Size().cy, 
        hdc, 0, 0, m_image->width, m_image->height, SRCCOPY);
//    ::BitBlt(pDC->m_hDC, 0, 0, m_image->width, m_image->height, 
//        hdc, 0, 0, SRCCOPY);
    ::DeleteDC(hdc);
}

void CStereoGRView::OnDrawPointCloud()
{
	CvPoint3D32f *ZKeyBuffer; float v[6];
	BeginScene();
	glViewport(0, 0, m_width, m_height);

	// Setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ 45.0,	/* aspect ratio */ 1.0, /* Z near */ 1.0, /* Z far */ 1000.0);

	// position the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -camDist);
	glTranslated(m_translate[0], m_translate[1], m_translate[2]);
	glTranslated(0,0,-1.3);
	glMultMatrixd(m_rotate);
	glRotated(180, 0.0, 0.0, 1.0);

//    PTGreyFreezeData(INFINITE);
	ZKeyBuffer = (CvPoint3D32f*)m_points.begin();

	glColor3f(0,1,0);
    int pointCount = m_points.size()/3;

	int swidth = PTGreyGetWidth(PT_DISPARITY_IMAGE);
	int sheight = PTGreyGetHeight(PT_DISPARITY_IMAGE);
	glVertexPointer(3, GL_FLOAT, 0, ZKeyBuffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, pointCount);
/*
	glBegin(GL_POINTS);
	for(int i = 0; i < pointCount; i++)
	{
		glVertex3f(ZKeyBuffer[i].x, ZKeyBuffer[i].y, ZKeyBuffer[i].z);
	}
	glEnd();
*/

//    PTGreyUnFreezeData();
    
	if (pointCount > MinCloudCount) 
    {
        float* OpenGLLine = (float*)&((CStereoGRApp*)AfxGetApp())->m_findHand.m_line;
		// draw the line 
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
		v[0] = OpenGLLine[3] - OpenGLLine[0];
		v[1] = OpenGLLine[4] - OpenGLLine[1];
		v[2] = OpenGLLine[5] - OpenGLLine[2];
		v[3] = OpenGLLine[3] + OpenGLLine[0];
		v[4] = OpenGLLine[4] + OpenGLLine[1];
		v[5] = OpenGLLine[5] + OpenGLLine[2];
		glVertex3d(v[0], v[1], v[2]);			
		glVertex3d(v[3], v[4], v[5]);	
		glEnd();
	}
	
	// draw the viewing cone
	glColor3f(1,1,0); 
	// big square
	glBegin(GL_LINE_STRIP);
	glVertex3d(coneMinX, coneMinY, coneMaxZ);
	glVertex3d(coneMinX, coneMaxY, coneMaxZ);
	glVertex3d(coneMaxX, coneMaxY, coneMaxZ);
	glVertex3d(coneMaxX, coneMinY, coneMaxZ);

	// four lines
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(coneMinX, coneMinY, coneMaxZ);
	glVertex3d(0,0,0);
	glVertex3d(coneMinX, coneMaxY, coneMaxZ);
	glVertex3d(0,0,0);
	glVertex3d(coneMaxX, coneMaxY, coneMaxZ);
	glVertex3d(0,0,0);
	glVertex3d(coneMaxX, coneMinY, coneMaxZ);
	glEnd();

	glTranslated(0,0,1.3);

	EndScene();
}

void CStereoGRView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CStereoGRDoc* pDoc = GetDocument();
	int docType = pDoc->GetDocType();
	if(docType == PT_POINTCLOUD_IMAGE || docType == GR_MAGICCUBE)
		COpenGLView::OnMouseMove(nFlags, point);
	else
		CView::OnMouseMove(nFlags, point);
}


void CStereoGRView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	InitCameraPosition();	
	OnDrawPointCloud();
	COpenGLView::OnRButtonDblClk(nFlags, point);
}

void CStereoGRView::OnDrawMagicCube()
{
	bool is_texture = m_texture[0] ? true : false;
	STEREOGRAPP(app);
	SetOwnContext();
	glViewport(0, 0, m_width, m_height);

	IplImage* data[3];
	data[0] = app->GetView(PT_RIGHT_RAW_IMAGE)->GetImage();
	data[1] = app->GetView(PT_TOP_RAW_IMAGE)->GetImage();
	data[2] = app->GetView(PT_LEFT_RAW_IMAGE)->GetImage();
	int width = data[0]->width;
	int height = data[0]->height;
	const char* bits[3];
	for(int i = 0; i < 3; i++)
		bits[i] = data[i]->imageData;
	
	InitTexture(width, height);
	ScaleTextures(width, height, (const void**)bits, 3);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glShadeModel(GL_SMOOTH);

	BeginScene();
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ 45.0,	/* aspect ratio */ 1.0, /* Z near */ 1.0, /* Z far */ 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_azim += m_azimInc*10;
	m_incl += m_inclInc*10;
	m_dist += m_distInc;
	m_azimInc *= 0.95f;
	m_inclInc *= 0.95f;
	m_distInc *= 0.95f;
	glTranslated(0, 0, -m_dist);
	glTranslated(0, 0, -2);
	glRotated(m_azim, 0.0, 1.0, 0.0);
	glRotated(m_incl, 0.0, 0.0, 1.0);
	glMultMatrixd(m_rotate);

	if(!is_texture)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_tex_width, m_tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texture[0]);
	}
	else
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_tex_width, m_tex_height, GL_RGB, GL_UNSIGNED_BYTE, m_texture[0]);
	}
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	glTexCoord2f(0, 1);	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 1);	glVertex3f( 0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);	glVertex3f( 0.5,  0.5, -0.5);
	glTexCoord2f(0, 0);	glVertex3f(-0.5,  0.5, -0.5);

	glTexCoord2f(0, 1);	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);	glVertex3f( 0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);	glVertex3f( 0.5,  0.5, 0.5);
	glTexCoord2f(0, 0);	glVertex3f(-0.5,  0.5, 0.5);

	glEnd();
	
	if(!is_texture)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_tex_width, m_tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texture[1]);
	}
	else
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_tex_width, m_tex_height, GL_RGB, GL_UNSIGNED_BYTE, m_texture[1]);
	}
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	glTexCoord2f(0, 1);	glVertex3f(0.5, -0.5,  -0.5);
	glTexCoord2f(1, 1);	glVertex3f(0.5, -0.5,   0.5);
	glTexCoord2f(1, 0);	glVertex3f(0.5,  0.5,   0.5);
	glTexCoord2f(0, 0);	glVertex3f(0.5,  0.5,  -0.5);

	glTexCoord2f(0, 1);	glVertex3f(-0.5, -0.5,  -0.5);
	glTexCoord2f(1, 1);	glVertex3f(-0.5, -0.5,   0.5);
	glTexCoord2f(1, 0);	glVertex3f(-0.5,  0.5,   0.5);
	glTexCoord2f(0, 0);	glVertex3f(-0.5,  0.5,  -0.5);

	glEnd();

	if(!is_texture)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_tex_width, m_tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texture[2]);
	}
	else
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_tex_width, m_tex_height, GL_RGB, GL_UNSIGNED_BYTE, m_texture[2]);
	}
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	glTexCoord2f(0, 1);	glVertex3f(-0.5, 0.5,  -0.5);
	glTexCoord2f(1, 1);	glVertex3f(-0.5, 0.5,   0.5);
	glTexCoord2f(1, 0);	glVertex3f( 0.5, 0.5,   0.5);
	glTexCoord2f(0, 0);	glVertex3f( 0.5, 0.5,  -0.5);

	glTexCoord2f(0, 1);	glVertex3f(-0.5, -0.5,  -0.5);
	glTexCoord2f(1, 1);	glVertex3f(-0.5, -0.5,   0.5);
	glTexCoord2f(1, 0);	glVertex3f( 0.5, -0.5,   0.5);
	glTexCoord2f(0, 0);	glVertex3f( 0.5, -0.5,  -0.5);

	glEnd();
	EndScene();
}

void CStereoGRView::InitMagicCube()
{
	STEREOGRAPP(app);
	SetOwnContext();
}

void CStereoGRView::DrawScene(CDC* pDC)
{
	switch(GetDocument()->GetDocType())
	{
	case PT_POINTCLOUD_IMAGE:
		OnDrawPointCloud();
		break;
	case GR_MAGICCUBE:
		OnDrawMagicCube();
		break;

	default:
		OnDrawImage(pDC);
		break;
	}
}

void CStereoGRView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	STEREOGRAPP(app)
	CView::OnChar(nChar, nRepCnt, nFlags);
	
	COpenGLView::OnChar(nChar, nRepCnt, nFlags);
}

void CStereoGRView::InitTexture(int width, int height)
{
	if(m_texture[0])
		return;
	
	switch(width)
	{
	case 160:
		m_tex_width = 128;
		m_tex_height = 128;
		break;

	case 320:
		m_tex_width  = 256;
		m_tex_height = 256;
		break;

	case 640:
		m_tex_width = 512;
		m_tex_height = 512;
		break;
	}

	int pixel_count = m_tex_width*m_tex_height;
	for(int i = 0; i < 3; i++)
		m_texture[i] = malloc(3*pixel_count);
}


void CStereoGRView::ScaleTextures(int width, int height, const void** bits, int count)
{
	int pixel_count = m_tex_width*m_tex_height;
	IplImage* source = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, 3);
	IplImage* dest = cvCreateImageHeader(cvSize(m_tex_width, m_tex_height), IPL_DEPTH_8U, 3);

	if(!m_planes[0])
	{
		m_planes[0] = cvCreateImage(cvSize(m_tex_width, m_tex_height), IPL_DEPTH_8U, 1);
		m_planes[1] = cvCreateImage(cvSize(m_tex_width, m_tex_height), IPL_DEPTH_8U, 1);		
	}
	
	for(int i = 0; i < count; i++)
	{
		source->imageData = (char*)bits[i];
		dest->imageData = (char*)m_texture[i];

		iplSet(dest, 255);
		iplResize(source, dest, m_tex_width, width, m_tex_height, height, IPL_INTER_NN);

		dest->roi = iplCreateROI(1, 0, 0, m_tex_width, m_tex_height);
		iplCopy(dest, m_planes[0]);
		dest->roi->coi = 3;
		iplCopy(dest, m_planes[1]);
		iplCopy(m_planes[0], dest);
		dest->roi->coi = 1;
		iplCopy(m_planes[0], dest);
		iplDeleteROI(dest->roi);
		dest->roi = 0;
	}
	
	cvReleaseImageHeader(&source);
	cvReleaseImageHeader(&dest);
//	int e = gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE, bits, 
//		m_tex_width, m_tex_height*height/width, GL_UNSIGNED_BYTE, m_texture);
}

void CStereoGRView::RetrievePointCloud()
{
	m_points.clear();
	PTGreyFreezeData(INFINITE);

	int count = PTGreyGetPointCount();
	if(count > 0)
	{
		const float* points = (const float*)PTGreyGetDataPointer(PT_POINTCLOUD_IMAGE);
		m_points.insert(m_points.begin(), &points[0], &points[3*count - 1]);
	}
	PTGreyUnFreezeData();
}

void CStereoGRView::RotateAzim(float val)
{
	m_azimInc = val;
}

void CStereoGRView::RotateIncl(float val)
{
	m_inclInc = val;
}

void CStereoGRView::Translate(float val)
{
	m_distInc = val;
}

void CStereoGRView::InitModel()
{
	m_azimInc = 0;
	m_inclInc = 0;
	m_distInc = 0;

	m_azim = 0;
	m_incl = 0;
	m_dist = 0;
}

void CStereoGRView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == '7')	
	{
		InitModel();
		InitCameraPosition();
		OnDrawMagicCube();
	}
	COpenGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}
