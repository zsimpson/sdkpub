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

#include "cvtest.h"

#ifdef WIN32
#include <windows.h>
#include <math.h>
#include <assert.h>

static const char* ATS_WND_CLASS = "ATS_Window_Class";


static LRESULT CALLBACK AtsWindowProc(
  HWND hwnd,      /* handle to window */
  UINT uMsg,      /* message identifier */
  WPARAM wParam,  /* first message parameter */
  LPARAM lParam   /* second message parameter */
)
{
    return DefWindowProc( hwnd, uMsg, wParam, lParam );
}



int atsCreateWindow( const char* name, CvPoint wnd_org, CvSize wnd_size )
{
    WNDCLASS wcl;

    wcl.style = CS_NOCLOSE;
    wcl.lpfnWndProc = AtsWindowProc;
    wcl.cbClsExtra = wcl.cbWndExtra = 0;
    wcl.hInstance = GetModuleHandle(0);
    wcl.hIcon = (HICON)LoadImage( 0, (LPCTSTR)IDI_WINLOGO, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE );
    wcl.hCursor = (HICON)LoadImage( 0, (LPCTSTR)IDC_CROSS, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE );
    wcl.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wcl.lpszMenuName = 0;
    wcl.lpszClassName = ATS_WND_CLASS;

    RegisterClass( &wcl );

    return  (int)CreateWindow(
        wcl.lpszClassName, name,
        WS_POPUP | WS_CAPTION | WS_VISIBLE,
        wnd_org.x, wnd_org.y, wnd_size.width, wnd_size.height,
        0, 0, wcl.hInstance, 0 );
}


/* displays (8u/8s)C1/C3/AC4 image */
void  atsDisplayImage( IplImage* img, int window, CvPoint dst_org, CvSize dst_size )
{
    uchar storage[sizeof(BITMAPINFOHEADER) + 256*4];
    BITMAPINFOHEADER*  bmih = (BITMAPINFOHEADER*)storage;

    char* src_data = 0;
    char* dst_data = 0;
    CvSize src_size;
    int   src_step = 0;
    int   channels = 0, depth = 0, bt_pix = 0;
    HBITMAP hbmp = 0;
    HDC     hdc = 0, dstdc = 0;

    atsGetImageInfo( img, (void**)&src_data, &src_step, &src_size, &depth, &channels, &bt_pix );

    assert( depth == IPL_DEPTH_8U || depth == IPL_DEPTH_8S );
    assert( channels == 1 || channels == 3 || channels == 4 );

    bmih->biSize = sizeof(*bmih);
    bmih->biWidth = src_size.width;
    bmih->biHeight = -src_size.height;
    bmih->biPlanes = 1;
    bmih->biBitCount = (unsigned short)(bt_pix*8);
    bmih->biCompression = BI_RGB;
    bmih->biSizeImage = 0;
    bmih->biXPelsPerMeter = 0;
    bmih->biYPelsPerMeter = 0;
    bmih->biClrUsed = 0;
    bmih->biClrImportant = 0;

    if( channels == 1 )
    {
        int i, delta = (depth == IPL_DEPTH_8S)*128;
        RGBQUAD* palette = (RGBQUAD*)(storage + sizeof(BITMAPINFOHEADER));

        for( i = 0; i < 256; i++ )
            palette[i].rgbBlue = palette[i].rgbRed =
            palette[i].rgbGreen = (uchar)(i + delta);
    }

    hdc = CreateCompatibleDC(0);
    hbmp = CreateDIBSection( hdc, (BITMAPINFO*)bmih, DIB_RGB_COLORS, (void**)&dst_data, 0, 0 );

    dstdc = GetDC( (HWND)window );

    if( hbmp && dstdc )
    {
        HGDIOBJ hold = SelectObject( hdc, hbmp );
        int  dst_step = (src_size.width*bt_pix + 3) & -4;
        int  y;

        /* convert source image to RGB24 */
        for( y = 0; y < src_size.height; y++, src_data += src_step, dst_data += dst_step )
        {
            memcpy( dst_data, src_data, dst_step );
        }
#if 0
        if( depth == IPL_DEPTH_8U ) /* 8u */
        {
            switch( channels )
            {
            case 1:
                for( x = 0; x < src_size.width; x++ )
                {
                    dst_data[x*3] = dst_data[x*3+1] =
                        dst_data[x*3+2] = ((uchar*)src_data)[x];
                }
                break;
            case 3:
                memcpy( dst_data, src_data, src_size.width*3 );
                break;
            default: /* 4 */
                for( x = 0; x < src_size.width; x++ )
                {
                    dst_data[x*3] = ((uchar*)src_data)[x*4];
                    dst_data[x*3 + 1] = ((uchar*)src_data)[x*4 + 1];
                    dst_data[x*3 + 2] = ((uchar*)src_data)[x*4 + 2];
                }
                break;
            }
        }
        else /* 8s */
        {
            switch( channels )
            {
            case 1:
                for( x = 0; x < src_size.width; x++ )
                {
                    dst_data[x*3] = dst_data[x*3+1] =
                        dst_data[x*3+2] = ((uchar*)src_data)[x];
                }
                break;
            case 3:
                memcpy( dst_data, src_data, src_size.width*3 );
                break;
            default: /* 4 */
                for( x = 0; x < src_size.width; x++ )
                {
                    dst_data[x*3] = ((uchar*)src_data)[x*4];
                    dst_data[x*3 + 1] = ((uchar*)src_data)[x*4 + 1];
                    dst_data[x*3 + 2] = ((uchar*)src_data)[x*4 + 2];
                }
                break;
            }
        }
#endif

        SetStretchBltMode( dstdc, COLORONCOLOR );
        StretchBlt( dstdc, dst_org.x, dst_org.y, dst_size.width, dst_size.height,
                    hdc, 0, 0, src_size.width, src_size.height, SRCCOPY );
        SelectObject( hdc, hold );
    }

    if( hbmp ) DeleteObject( hbmp );
    if( hdc ) DeleteDC( hdc );
    if( dstdc ) ReleaseDC( (HWND)window, dstdc );
}


void  atsDestroyWindow( int window )
{
    DestroyWindow( (HWND)window );
}

#endif

