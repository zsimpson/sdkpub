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
//M*/

//
// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Image.h"
#include "vlgrfmts.h"
#include "cv.h"
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage()
{
    Clear();
}

void CImage::Clear()
{ 
    memset( &m_img, 0, sizeof(m_img));

    m_memDC = 0; 
    m_old = 0;
}

void CImage::Destroy()
{
    if( m_memDC )
    {
        DeleteObject( SelectObject( m_memDC, m_old ));
        DeleteDC( m_memDC );
    }
    Clear();
}

CImage::~CImage()
{
    Destroy();
}


void  FillBitmapInfo( BITMAPINFO* bmi, int width, int height, int bpp )
{
    assert( bmi && width > 0 && height > 0 &&
            (bpp == 8 || bpp == 24 || bpp == 32) );

    BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

    memset( bmih, 0, sizeof(*bmih));
    bmih->biSize   = sizeof(BITMAPINFOHEADER); 
    bmih->biWidth  = width;
    bmih->biHeight = -abs(height);
    bmih->biPlanes = 1; 
    bmih->biBitCount = bpp;
    bmih->biCompression = BI_RGB;

    if( bpp == 8 )
    {
        RGBQUAD* palette = bmi->bmiColors;
        int i;
        for( i = 0; i < 256; i++ )
        {
            palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
            palette[i].rgbReserved = 0;
        }
    }
}


bool  CImage::Create( int w, int h, int bpp )
{
    char buffer[sizeof(BITMAPINFOHEADER) + 1024];
    BITMAPINFO* bmi = (BITMAPINFO*)buffer;
    void* data = 0;
    int new_step = (w*(bpp/8) + 3) & -4;
    
    assert( bpp == 8 || bpp == 24 || bpp == 32 );

    if( (m_img.depth & 255)*m_img.nChannels == bpp && 
        m_img.width == w && m_img.height == h )
    {
        return true;
    }

    Destroy();
    
    m_memDC = CreateCompatibleDC(0);
    FillBitmapInfo( bmi, w, h, bpp );

    HBITMAP hbmp = CreateDIBSection( m_memDC, bmi, DIB_RGB_COLORS, &data, 0, 0 );
    if( !hbmp )
    {
        DeleteDC( m_memDC );
        m_memDC = 0;
    }
    else
    {
        BITMAP bmp;
        m_old = SelectObject( m_memDC, hbmp );

        GetObject( hbmp, sizeof(bmp), &bmp );

        /* prepare IPL header */
        memset( &m_img, 0, sizeof(m_img));
        m_img.nSize = sizeof( m_img );
        m_img.nChannels = bpp/8;
        m_img.depth = IPL_DEPTH_8U;
        strncpy( m_img.colorModel, bpp > 8 ? "RGB\0" : "GRAY", 4 );
        strncpy( m_img.channelSeq, bpp > 8 ? "BGR\0" : "GRAY", 4 );
        m_img.align = 4;
        m_img.width = w;
        m_img.height = abs(h);
        m_img.roi  = 0;
        m_img.widthStep = (w*(bpp/8) + 3)& -4;
        m_img.imageSize = m_img.widthStep*m_img.height;
        m_img.imageData = m_img.imageDataOrigin = (char*)bmp.bmBits;

        //iplSetBorderMode( &m_img, IPL_BORDER_REPLICATE, IPL_SIDE_ALL, 0 ); 
    }
    return m_old != 0;
}


void  CImage::CopyOf( CImage& image, int desired_color )
{
    IplImage* img = image.GetImage();
    if( img )
    {
        CopyOf( img, desired_color );
    }
}

void  CImage::CopyOf( IplImage* img, int desired_color )
{
    if( img )
    {
        int color = desired_color;
        if( color < 0 ) color = img->nChannels > 1;
        Create( iplWidth( img ), iplHeight( img ), color ? 24 : 8 );
        if( m_img.nChannels == img->nChannels )
        {
            if( img->origin != m_img.origin )
            {
                long OldOrg = img->origin;
                img->origin = m_img.origin;
                cvMirror( img, &m_img, 0 );
                img->origin = OldOrg;
            }
            else
            {
                cvCopy( img, &m_img );
            }
        }
        else
        {
            CImage tmp_image;
            
            tmp_image.Create( m_img.width, m_img.height, img->nChannels*8 );

            IplImage* tmp_img = tmp_image.GetImage();
            if( img->origin != m_img.origin )
            {
                long OldOrg = img->origin;
                img->origin = tmp_img->origin;
                cvMirror( img, tmp_img, 0 );
                img->origin = OldOrg;
            }
            else
            {
                cvCopy( img, tmp_img );
            }

            if( color )
                cvCvtColor( tmp_img, &m_img, CV_GRAY2BGR );
            else
                cvCvtColor( tmp_img, &m_img, CV_BGR2GRAY );
        }
    }
}

#if 0
static HINSTANCE hdll = 0;
static int (__cdecl *gr_fmt_find_filter)( const char* file_name ) = 0; 
static int (__cdecl *gr_fmt_read_header)( int filter, int* width, int* height, int* color ) = 0;
static int (__cdecl *gr_fmt_read_data)( int filter, void* data, int pitch, int color ) = 0;
static int (__cdecl *gr_fmt_close_filter)( int filter ) = 0;
static int (__cdecl *gr_fmt_write_image)( void* data, int pitch,
                                          int width, int height, int color,
                                          const char* filename, const char* format ) = 0;

bool  LoadGrFmtLib()
{
    if( hdll != 0 ) return true;

    // load image formats dll
    hdll = LoadLibrary( "vlgrfmts.dll");
    if( !hdll ) return false;

    (FARPROC&)gr_fmt_find_filter = GetProcAddress( hdll, "gr_fmt_find_filter" );
    (FARPROC&)gr_fmt_read_header = GetProcAddress( hdll, "gr_fmt_read_header" );
    (FARPROC&)gr_fmt_read_data   = GetProcAddress( hdll, "gr_fmt_read_data" );
    (FARPROC&)gr_fmt_close_filter= GetProcAddress( hdll, "gr_fmt_close_filter" );
    (FARPROC&)gr_fmt_write_image = GetProcAddress( hdll, "gr_fmt_write_image" );

    if( !gr_fmt_find_filter || !gr_fmt_read_header || !gr_fmt_read_data )
    {
        FreeLibrary( hdll );
        hdll = 0;
        return false;
    }
    return true;
}
#endif

bool  CImage::Load( const char* filename, int desired_color )
{
    int filter = 0;
    int width = 0, height = 0;
    bool result = false;
    int color = 0;
    
    if( gr_fmt_find_filter == 0 ) return false;

    if( !(filter = gr_fmt_find_filter( filename ))) goto exit;
    if( !gr_fmt_read_header( filter, &width, &height, &color )) goto exit;

    color = desired_color >= 0 ? desired_color : color > 0;
    
    Create( width, height, color ? 24 : 8);
    if( m_memDC == 0 ) goto exit;

    result = gr_fmt_read_data( filter, m_img.imageData, m_img.widthStep, color ) != 0;
exit:
    gr_fmt_close_filter( filter );
    return result;
}



bool  CImage::LoadRect( const char* filename,
                        int desired_color, RECT r )
{
    int filter = 0;
    int width = 0, height = 0;
    bool result = false;
    int color = 0;
    int r_width = r.right - r.left;
    int r_height = r.bottom - r.top;
    int tmp_step = 0;
    char* tmp = 0;
    
    if( r_width < 0 || r_height < 0 ) return false;
    if( gr_fmt_find_filter == 0 ) return false;

    if( !(filter = gr_fmt_find_filter( filename ))) goto exit;
    if( !gr_fmt_read_header( filter, &width, &height, &color )) goto exit;

    if( r_width == 0 || r_height == 0 )
    {
        r_width = width;
        r_height = height;
    }

    if( (unsigned)r.left >= (unsigned)width ||
        (unsigned)r.top >= (unsigned)height ||
        (unsigned)r.right >= (unsigned)width ||
        (unsigned)r.bottom >= (unsigned)height ) goto exit;

    color = desired_color >= 0 ? desired_color : color > 0;
    
    Create( r_width, r_height, color ? 24 : 8);
    if( m_memDC == 0 ) goto exit;

    if( r.left == 0 && r.top == 0 &&
        (r_width == 0 || r_width == width) &&
        (r_height == 0 || r_height == height))
    {
        tmp = m_img.imageData;
        tmp_step = m_img.widthStep;
    }
    else
    {
        tmp_step = (width*m_img.nChannels + 3) & -4;
        tmp = (char*)malloc( tmp_step * height );
        if( !tmp ) goto exit;
    }

    result = gr_fmt_read_data( filter, tmp, tmp_step, color ) != 0;

    if( result && tmp != m_img.imageData )
    {
        int y;
        for( y = 0; y < r_height; y++ )
        {
            memcpy( m_img.imageData + y*m_img.widthStep,
                    tmp + (r.top + y)*tmp_step + r.left*m_img.nChannels,
                    r_width * m_img.nChannels );
        }
    }

exit:
    gr_fmt_close_filter( filter );
    if( tmp != 0 && tmp != m_img.imageData ) free( tmp );
    return result;
}


bool  CImage::Save( const char* filename )
{
    if( !m_memDC || (m_img.nChannels != 3 && m_img.nChannels != 1) ||
        m_img.depth != IPL_DEPTH_8U ) return false;

    return gr_fmt_write_image( m_img.imageData, m_img.widthStep,
                               iplWidth( &m_img ), iplHeight( &m_img ),
                               m_img.nChannels == 3, filename, "BMP" ) != 0;
}


IplImage* CImage::GetImage()
{
    return m_memDC != 0 ? &m_img : 0;
}


HDC  CImage::GetDC()
{
    return m_memDC;
}


void CImage::Show( HDC dc, int x, int y, int w, int h, int from_x, int from_y )
{
    if( m_img.width > 0 )
    {
        uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
        BITMAPINFO* bmi = (BITMAPINFO*)buffer;
        int bmp_w = Width();
        int bmp_h = Height();

        FillBitmapInfo( bmi, bmp_w, bmp_h, m_img.nChannels*8 );

        int sw = MAX( MIN( bmp_w - from_x, w ), 0 );
        int sh = MAX( MIN( bmp_h - from_y, h ), 0 );

        int res = SetDIBitsToDevice(
              dc,                        // handle to DC
              x,                         // x-coord of destination upper-left corner
              y,                         // y-coord of destination upper-left corner 
              sw,                        // source rectangle width
              sh,                        // source rectangle height
              from_x,                    // x-coord of source lower-left corner
              from_y,                    // y-coord of source lower-left corner
              from_y,                    // first scan line in array
              sh,                        // number of scan lines
              m_img.imageData + from_y*m_img.widthStep/* +
              from_x*m_img.nChannels*/,    // array of DIB bits
              (BITMAPINFO*)bmi,          // bitmap information
              DIB_RGB_COLORS );          // RGB or palette indexes
    }
}

void  CImage::Fill( COLORREF color )
{
    if( m_memDC )
    {
        HBRUSH br = CreateSolidBrush( color );
        RECT rect;
        GetClipBox( m_memDC, &rect );
        FillRect( m_memDC, &rect, br );
        DeleteObject( br );
    }
}

void  CImage::DrawToHDC( HDC hDCDst, RECT* pDstRect ) 
{
    HDC hDCSrc = GetDC();

    if( pDstRect == NULL ) return;
    if( hDCDst == NULL ) return;
    if( hDCSrc == NULL ) return;

    if( Width() > pDstRect->right - pDstRect->left )
    {
        SetStretchBltMode(
               hDCDst,           // handle to device context
               HALFTONE );
    }
    else
    {
        SetStretchBltMode(
               hDCDst,           // handle to device context
               COLORONCOLOR );
    }

    ::StretchBlt( 
        hDCDst,
        pDstRect->left, pDstRect->top,
        pDstRect->right - pDstRect->left, pDstRect->bottom - pDstRect->top,
        hDCSrc,
        m_img.roi ? m_img.roi->xOffset:0 ,
        m_img.roi ? m_img.roi->yOffset:0,
        Width(),
        Height(),
        SRCCOPY );
}
