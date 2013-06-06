// mltaccumDoc.cpp : implementation of the CMltaccumDoc class
//

#include "stdafx.h"
#include "mltaccum.h"

#include "mltaccumDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltaccumDoc

IMPLEMENT_DYNCREATE(CMltaccumDoc, CDocument)

BEGIN_MESSAGE_MAP(CMltaccumDoc, CDocument)
	//{{AFX_MSG_MAP(CMltaccumDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltaccumDoc construction/destruction

CMltaccumDoc::CMltaccumDoc()
{
	// TODO: add one-time construction code here

}

CMltaccumDoc::~CMltaccumDoc()
{
}

BOOL CMltaccumDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMltaccumDoc serialization

void CMltaccumDoc::Serialize(CArchive& ar)
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
// CMltaccumDoc diagnostics

#ifdef _DEBUG
void CMltaccumDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMltaccumDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMltaccumDoc commands
