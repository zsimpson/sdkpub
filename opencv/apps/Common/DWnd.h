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
//M*/// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DWND_H__36BABB11_EBA3_11D3_A294_00105A717188__INCLUDED_)
#define AFX_DWND_H__36BABB11_EBA3_11D3_A294_00105A717188__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DWnd.h : header file
//
#include "Image.h"

/////////////////////////////////////////////////////////////////////////////
// CDWnd window

class CDWnd : public CWnd
{
// Construction
public:
	CDWnd();

// Attributes
public:
    double m_IWK[2];
    double m_WIK[2];

// Operations
public:
    CWnd* m_FatherWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDWnd();

  /* interface */
    BOOL       CreateWnd( CWnd* pParent, 
                          char* pName   = "Data", 
                          long  lWidth  = 320, 
                          long  lHeight = 240,
                          long  lBPP    = 24 );
    void       DrawIplImage( IplImage* pImage, BOOL bSetChannelNumber = TRUE );
    void       Invalidate( BOOL bErase = TRUE )
                    {if(::IsWindow(m_hWnd))CWnd::Invalidate( bErase );}
    CDC*       GetDC(){return ::IsWindow(m_hWnd) ? CWnd::GetDC() : NULL;}
    HDC        GetMemHDC() {return ::IsWindow(m_hWnd) ? m_Image.GetDC() : NULL;}
    IplImage*  GetImage() {return m_Image.GetImage();}
    CImage     m_Image;
    virtual BOOL ReDraw( CDC *pDC = NULL );
    BOOL       DrawToHDC( HDC hDCDst, RECT* pDstRect = NULL );

  // Generated message map functions
protected:


  //{{AFX_MSG(CDWnd)
	afx_msg void OnPaint();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWND_H__36BABB11_EBA3_11D3_A294_00105A717188__INCLUDED_)

/* End of file. */
