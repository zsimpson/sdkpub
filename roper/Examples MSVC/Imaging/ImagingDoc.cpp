// ImagingDoc.cpp : implementation of the CImagingDoc class
//

#include "stdafx.h"
#include "Imaging.h"

#include "ImagingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagingDoc

IMPLEMENT_DYNCREATE(CImagingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImagingDoc, CDocument)
	//{{AFX_MSG_MAP(CImagingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagingDoc construction/destruction

CImagingDoc::CImagingDoc()
{
	// TODO: add one-time construction code here

}

CImagingDoc::~CImagingDoc()
{
}

BOOL CImagingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CImagingDoc serialization

void CImagingDoc::Serialize(CArchive& ar)
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
// CImagingDoc diagnostics

#ifdef _DEBUG
void CImagingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImagingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImagingDoc commands
