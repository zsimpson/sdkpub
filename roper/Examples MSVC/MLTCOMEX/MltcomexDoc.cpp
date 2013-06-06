// MltcomexDoc.cpp : implementation of the CMltcomexDoc class
//

#include "stdafx.h"
#include "Mltcomex.h"

#include "MltcomexDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltcomexDoc

IMPLEMENT_DYNCREATE(CMltcomexDoc, CDocument)

BEGIN_MESSAGE_MAP(CMltcomexDoc, CDocument)
	//{{AFX_MSG_MAP(CMltcomexDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltcomexDoc construction/destruction

CMltcomexDoc::CMltcomexDoc()
{
	// TODO: add one-time construction code here

}

CMltcomexDoc::~CMltcomexDoc()
{
}

BOOL CMltcomexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMltcomexDoc serialization

void CMltcomexDoc::Serialize(CArchive& ar)
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
// CMltcomexDoc diagnostics

#ifdef _DEBUG
void CMltcomexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMltcomexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMltcomexDoc commands
