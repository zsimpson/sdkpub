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
// VMDemoDlg.h : header file
//
#include "VirtualImage.h"
#include "CV.h"
#if !defined(AFX_VMDEMODLG_H__51DFF934_1A5A_11D3_B4F3_00A0C9989E1D__INCLUDED_)
#define AFX_VMDEMODLG_H__51DFF934_1A5A_11D3_B4F3_00A0C9989E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>

#define PIXELTOPIXEL
/////////////////////////////////////////////////////////////////////////////
// CVMDemoDlg dialog

#include "SubdivMorpher.h"

class CVMDemoDlg : public CDialog
{
// Construction
public:
    void AllocMemory();
    void FreeMemory();
    ~CVMDemoDlg();
    void SetWindowsToTop();

    CRaster*	RasterLeft;
    CRaster*	RasterRight;
    CRaster*	RasterResult;

    CVirtualImage* RightImage;
    CVirtualImage* LeftImage;
    CVirtualImage* ResultImage;

    CArray <CPoint,CPoint> CorrPoints1;
    CArray <CPoint,CPoint> CorrPoints2;
    CvMatrix3  FundMatrix;

    int         numHoughLines;
    float*      HoughLines;

    bool    HaveMorph;
    int     numLines;

    int     numScanlines;
    int     useScanlines;


/* Memory */


    int*    scanlines_1;
    int*    scanlines_2;
    int*    scanlines_a;

    int*    lens_1;
    int*    lens_2;
    int*    morph_lens;

    int*    runs_1;
    int*    runs_2;

    uchar*  buffer_1;
    uchar*  buffer_2;
    uchar*  morph_buffer;

    int*    num_runs_1;
    int*    num_runs_2;

    int*    corr_1;
    int*    corr_2;

/*--Memory--*/

    int prevpos;

    CVMDemoDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
    //{{AFX_DATA(CVMDemoDlg)
	enum { IDD = IDD_VMDEMO_DIALOG };
	CButton	m_showscanlines;
    CEdit       m_imagesize;
    CSliderCtrl m_camerapos;
	//}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVMDemoDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
    BOOL  CanMorph;

    #ifndef PIXELTOPIXEL
    CCvSubdivMorpher m_morpher;
    #else
    CCvPixelToPixelMorpher m_morpher;
    #endif

    // Generated message map functions
    //{{AFX_MSG(CVMDemoDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnOpenproject();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnOriginalsize();
    afx_msg void OnMakemorphing();
	afx_msg void OnShowscanlines();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMDEMODLG_H__51DFF934_1A5A_11D3_B4F3_00A0C9989E1D__INCLUDED_)

/* End of file. */
