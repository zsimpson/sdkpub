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
//M*/// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__B0C6A376_E412_4ADD_B1EA_7488350A7F5B__INCLUDED_)
#define AFX_IMAGE_H__B0C6A376_E412_4ADD_B1EA_7488350A7F5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ipl.h"

inline int iplWidth( IplImage* img )
{
    return !img ? 0 : !(img->roi) ? img->width : img->roi->width;
}

inline int iplHeight( IplImage* img )
{
    return !img ? 0 : !(img->roi) ? img->height : img->roi->height;
}

inline IplROI RectToROI( RECT rect )
{
    IplROI roi;
    roi.coi = 0;
    roi.xOffset = rect.left;
    roi.yOffset = rect.top;
    roi.width = rect.right - rect.left;
    roi.height = rect.bottom - rect.top;
    return roi;
}

inline RECT NormalizeRect( RECT r )
{
    if( r.left > r.right )
    {
        int t = r.left;
        r.left = r.right;
        r.right = t;
    }

    if( r.top > r.bottom )
    {
        int t = r.top;
        r.top = r.bottom;
        r.bottom = t;
    }

    return r;
}

class CImage  
{
public:
    CImage();
    ~CImage();
    
    /* Create image (BGR or grayscale) */
    bool  Create( int w, int h, int bpp );
    
    /* Load image from specified file */
    bool  Load( const char* filename, int desired_color );

    /* Load rectangle from the file */
    bool  LoadRect( const char* filename,
                    int desired_color, RECT r );
    
    /* Save entire image to specified file. */
    bool  Save( const char* filename );
    
    /* Get copy of input image ROI */
    void  CopyOf( CImage& image, int desired_color = -1 );
    void  CopyOf( IplImage* img, int desired_color = -1 );

    IplImage* GetImage();
    HDC   GetDC();
    void  Destroy(void);
    
    /* width and height of ROI */
    int   Width() { return iplWidth( &m_img ); };
    int   Height() { return iplHeight( &m_img ); };

    /* put part of bitmap to specified destination rectangle */
    void  Show( HDC dc, int x, int y, int w, int h, int from_x, int from_y );
    /* draw all bitmap to specified rectangl of DC */
    void  DrawToHDC( HDC hDCDst, RECT* pDstRect );

    void  Fill( COLORREF color );

protected:

    void      Clear(void);
    
    HDC       m_memDC;
    HGDIOBJ   m_old;
    IplImage  m_img;
};

bool  LoadGrFmtLib();
void  FillBitmapInfo( BITMAPINFO* bmi, int width, int height, int bpp );

#endif // !defined(AFX_IMAGE_H__B0C6A376_E412_4ADD_B1EA_7488350A7F5B__INCLUDED_)
