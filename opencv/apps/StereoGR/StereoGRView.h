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
//M*/// StereoGRView.h : interface of the CStereoGRView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEREOGRVIEW_H__0603BB32_3287_4D21_ADCE_7B314B91C460__INCLUDED_)
#define AFX_STEREOGRVIEW_H__0603BB32_3287_4D21_ADCE_7B314B91C460__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PTGrey.h"
#include "OpenGLView.h"
#include "cv.h"

#include <vector>
using namespace std;

class CStereoGRView : public COpenGLView
{
protected: // create from serialization only
	CStereoGRView();
	DECLARE_DYNCREATE(CStereoGRView)

// Attributes
public:
	CStereoGRDoc* GetDocument();


// Operations
public:

    void Update();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStereoGRView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitModel();
	void Translate(float val);
	void RotateIncl(float val);
	void RotateAzim(float val);
	void RetrievePointCloud();
	void DrawScene(CDC* pDC = 0);
	void InitMagicCube();
	void OnDrawMagicCube();
	void UpdatePosition();
	void DefaultView();
	void DefaultData();
	BOOL RetrieveUserImage();
	BOOL IsNewData();
	IplImage* GetRecipient();
//	void SetImage(IplImage* image, BOOL copy = FALSE);
	IplImage* GetImage();
	void UpdateView();
	void UpdateData();
	BOOL RetrieveImage();
	void UpdateParams();
	virtual ~CStereoGRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void OnDrawPointCloud();
	void OnDrawImage(CDC* pDC);
	//{{AFX_MSG(CStereoGRView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	vector<float> m_points;
	BOOL m_wasInitialized;
	void ScaleTextures(int width, int height, const void** bits, int count);
	void InitTexture(int width, int height);
	void ProcessImage();
	void InitGL();
	HBITMAP m_bitmap;
	int m_pixelSize;
	IplImage* m_recipient;
	IplImage* m_auxImage;
	IplImage* m_image;

	void* m_texture[3];
	int m_tex_width;
	int m_tex_height;
	IplImage* m_planes[3];
	float m_dist;
	float m_incl;
	float m_azim;
	float m_distInc;
	float m_inclInc;
	float m_azimInc;
};

#ifndef _DEBUG  // debug version in StereoGRView.cpp
inline CStereoGRDoc* CStereoGRView::GetDocument()
   { return (CStereoGRDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEREOGRVIEW_H__0603BB32_3287_4D21_ADCE_7B314B91C460__INCLUDED_)
