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
//M*/// StereoGRDoc.cpp : implementation of the CStereoGRDoc class
//

#include "stdafx.h"
#include "StereoGR.h"

#include "StereoGRDoc.h"
#include "PGControl.h"
#include "PTGrey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CStereoGRDoc

IMPLEMENT_DYNCREATE(CStereoGRDoc, CDocument)

BEGIN_MESSAGE_MAP(CStereoGRDoc, CDocument)
	//{{AFX_MSG_MAP(CStereoGRDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStereoGRDoc construction/destruction

CStereoGRDoc::CStereoGRDoc()
{
    CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
    m_docType = app->GetDocType();
}

CStereoGRDoc::~CStereoGRDoc()
{
    PTGreySelectDataType(m_docType, 0);
}

BOOL CStereoGRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStereoGRDoc serialization

void CStereoGRDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStereoGRDoc diagnostics

#ifdef _DEBUG
void CStereoGRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStereoGRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStereoGRDoc commands

void CStereoGRDoc::SetDocType(int docType)
{
    m_docType = docType;
    if(IS_PTGREY_DATATYPE(docType))
        SetTitle(PT_IMAGE_NAME(docType));
    else
        switch(docType)
		{
		case GR_MASK_VIEW:
			SetTitle("Mask view");
			break;

		case GR_MAGICCUBE:
			SetTitle("3D view");
			break;
		}

}

void CStereoGRDoc::Initialize()
{
    SetDocType(m_docType);
    if(IS_PTGREY_DATATYPE(m_docType))
        PTGreySelectDataType(m_docType, 1);
}

int CStereoGRDoc::GetDocType()
{
    return m_docType;
}

BOOL CStereoGRDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	return FALSE;	
	return CDocument::CanCloseFrame(pFrame);
}
