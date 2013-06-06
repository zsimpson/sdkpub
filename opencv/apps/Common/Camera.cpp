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
//M*/// Camera.cpp: implementation of the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera.h"
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{
    m_capWnd = 0;
    m_isRunning = false;
}

CCamera::~CCamera()
{
    Uninitialize();
}

/* conversion YUV->RGB */
#define TWIST_BITS 12
#define TAP(x) ((int)((x)*(1<<TWIST_BITS) + 0.5 ))

static const int YUV2RGB[] = 
{
    TAP(1.1644), TAP(1.596), TAP(    0), -TAP(222.9184),
    TAP(1.1644),-TAP(0.815),-TAP( 0.39),  TAP(135.6096),
    TAP(1.1644), TAP(0),     TAP(2.016), -TAP(276.6784)
};

#define PROCESS_UV( uv_ofs, r0, g0, b0 )                                       \
    b0 = U[uv_ofs]*YUV2RGB[1+4*0] +           /* 0 + */        YUV2RGB[3+4*0]; \
    g0 = U[uv_ofs]*YUV2RGB[1+4*1] + V[uv_ofs]*YUV2RGB[2+4*1] + YUV2RGB[3+4*1]; \
    r0 =      /*  0 + */            V[uv_ofs]*YUV2RGB[2+4*2] + YUV2RGB[3+4*2];

#define PROCESS_Y( y_ofs, r, g, b, r0, g0, b0 ) \
    r = Y[y_ofs]*YUV2RGB[0+4*0];                \
    b = (r + b0) >> TWIST_BITS;                 \
    g = (r + g0) >> TWIST_BITS;                 \
    r = (r + r0) >> TWIST_BITS;

#define SATURATE(x) (BYTE)(!((x)&~255)?(x):~((x)>>31))

#define SAVE_RGB(ofs,r,g,b)     \
    BGR[(ofs)]   = SATURATE(b); \
    BGR[(ofs)+1] = SATURATE(g); \
    BGR[(ofs)+2] = SATURATE(r);


static void ConvertYUV420_TO_BGR( int width, int height,
                                  BYTE* Y, BYTE* U, BYTE* V,
                                  BYTE* BGR, int bgrStep )
{
    int  i, j;
    assert( ((width|height)&7) == 0 );

    int delta = bgrStep - width*3;
    width /= 2;

    for( i = 0; i < height; i += 2, Y += 4*width,
                                    U += width, V += width,
                                    BGR += delta + bgrStep )
    {
        for( j = 0; j < width; j++, BGR += 6 )
        {
            int r0, g0, b0, r, g, b;

            PROCESS_UV( j, r0, g0, b0 );
            
            PROCESS_Y( j*2, r, g, b, r0, g0, b0 );
            SAVE_RGB( 0, r, g, b );

            PROCESS_Y( j*2 + 1, r, g, b, r0, g0, b0 );
            SAVE_RGB( 3, r, g, b );

            PROCESS_Y( j*2 + width*2, r, g, b, r0, g0, b0 );
            SAVE_RGB( bgrStep, r, g, b );

            PROCESS_Y( j*2 + width*2 + 1, r, g, b, r0, g0, b0 );
            SAVE_RGB( bgrStep + 3, r, g, b );
        }
    }
}


static void CopyBGR_TO_BGR( int width, int height, BYTE* srcBGR, int srcStep,
                            BYTE* dstBGR, int dstStep )
{
    int i;

    for( i = 0; i < height; i++, srcBGR += srcStep, dstBGR += dstStep )
    {
        memcpy( dstBGR, srcBGR, width*3 );            
    }
}


void CCamera::UpdateParent( bool whole )
{
    HWND parent = GetParent( m_capWnd );
    RECT r = { 0, 0, 0, 0 };
    IplImage* img = m_frame.GetImage();

    if( img )
    {
        r.right = img->width;
        r.bottom = img->height;
    }
    
    InvalidateRect( parent, whole ? 0 : &r, whole );
    UpdateWindow( parent );
}

// Wrapper for frame callback
void CCamera::OnFrame( BYTE* data, int width, int height, int format, int bpp )
{
    const int mirror = 1;

    if( m_isRunning )
    {
        BYTE *BGR;
        int bgrStep;
        IplImage* img;
        bool refresh = width != m_frame.Width() || height != m_frame.Height();
    
        /* check if need reallocate image */
        m_frame.Create( width, height, 24 );

        img = m_frame.GetImage();

        BGR = (BYTE*)(img->imageData);
        bgrStep = img->widthStep;

        if( format == MAKEFOURCC('Y','V','1','2') || format == MAKEFOURCC('I','4','2','0'))
        {
            BYTE *Y = data,
                 *U = Y + width*height,
                 *V = U + width*height/4;

            ConvertYUV420_TO_BGR( width, height, Y, U, V, BGR, bgrStep );
        }
        else if( format == 0 && bpp == 24 )
        {
            int step = (width*3 + 3) & -4;

            if( mirror )
            {
                BGR += bgrStep*(height - 1);
                bgrStep = -bgrStep;
            }

            CopyBGR_TO_BGR( width, height, data, step, BGR, bgrStep );
        }

        UpdateParent( refresh );
    }
}

// Frame callback
LRESULT PASCAL FrameCallbackProc( HWND hWnd, VIDEOHDR* hdr ) 
{ 
    BITMAPINFO vfmt;
    int sz;

    if (!hWnd) return FALSE;

    sz = capGetVideoFormat( hWnd, &vfmt, sizeof(vfmt));
    
    if( hdr && hdr->lpData && sz != 0 )
    {
        int width = vfmt.bmiHeader.biWidth;
        int height = vfmt.bmiHeader.biHeight;
        int format = vfmt.bmiHeader.biCompression;
        int bpp = vfmt.bmiHeader.biBitCount;
        BYTE* data = (BYTE*)(hdr->lpData);

        CCamera* camera_obj = (CCamera*)capGetUserData(hWnd);
        if( camera_obj )
        {
            camera_obj->OnFrame( data, width, height, format, bpp );
        }
    }

    return (LRESULT) TRUE; 
} 


// Initialize camera input
bool  CCamera::Initialize( int width, int height, int format, HWND parent, int wIndex )
{
    char szDeviceName[80];
    char szDeviceVersion[80];
    HWND hWndC = 0;
    
    if( (unsigned)wIndex < 10 )
        goto init_camera;

    for( wIndex = 0; wIndex < 10; wIndex++ ) 
    {
init_camera:        
        if( capGetDriverDescription( wIndex, szDeviceName, 
            sizeof (szDeviceName), szDeviceVersion, 
            sizeof (szDeviceVersion))) 
        {
            hWndC = capCreateCaptureWindow ( "My Own Capture Window", 
                  WS_CHILD | WS_VISIBLE , 0, 0, 160, 120, parent, 0);

            if( capDriverConnect (hWndC, wIndex))
            {
                BITMAPINFO bmi;
 
                //capPreviewRate(hWndC, 66);  // rate, in milliseconds
                memset( &bmi.bmiHeader, 0, sizeof(bmi.bmiHeader));
                bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
                bmi.bmiHeader.biBitCount = format == 0 ? 24 : 12;
                bmi.bmiHeader.biWidth = width;
                bmi.bmiHeader.biHeight = height;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biCompression = format;
                bmi.bmiHeader.biSizeImage = ((bmi.bmiHeader.biWidth*
                                              bmi.bmiHeader.biBitCount/8 + 3)&-4)*
                                              bmi.bmiHeader.biHeight;
                if( format == -1 || capSetVideoFormat( hWndC, &bmi, sizeof(bmi)-4)) break;
                capDriverDisconnect( hWndC );
            }
            DestroyWindow( hWndC );
            hWndC = 0;
        }
    }
    
    if( hWndC )
    {
        m_capWnd = hWndC;
        
        memset( &m_caps, 0, sizeof(m_caps));
        capDriverGetCaps( hWndC, &m_caps, sizeof(m_caps));
        capSetUserData( hWndC, (long)this );
        capSetCallbackOnFrame( m_capWnd, FrameCallbackProc ); 
        ::MoveWindow( m_capWnd, 0, 0, 1, 1, TRUE );
        CAPTUREPARMS p;
        capCaptureGetSetup(hWndC,&p,sizeof(CAPTUREPARMS));
        p.dwRequestMicroSecPerFrame = 1;
        capCaptureSetSetup(hWndC,&p,sizeof(CAPTUREPARMS));
        capPreviewScale(hWndC,FALSE);
        capPreviewRate(hWndC,1);
    }
    return m_capWnd != 0;
}


// Uninitialize camera input
void  CCamera::Uninitialize()
{
    Stop();
    capSetCallbackOnFrame( m_capWnd, NULL ); 
    capDriverDisconnect( m_capWnd );
    DestroyWindow( m_capWnd );
}

// Start capture
void  CCamera::Start()
{
    if( m_capWnd )
    {
        m_isRunning = true;
    }
}

// Stop capture
void  CCamera::Stop()
{
    if( m_capWnd )
    {
        m_isRunning = false;
    }
}


void  CCamera::VideoFormatDlg()
{
    if( m_capWnd && m_caps.fHasDlgVideoFormat )
    {
        capDlgVideoFormat( m_capWnd );
    }
}


void  CCamera::VideoSourceDlg()
{
    if( m_capWnd && m_caps.fHasDlgVideoSource )
    {
        capDlgVideoSource( m_capWnd );
    }
}
