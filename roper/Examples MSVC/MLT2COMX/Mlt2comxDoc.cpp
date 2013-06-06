// Mlt2comxDoc.cpp : implementation of the CMlt2comxDoc class
//

#include "stdafx.h"
#include "Mlt2comx.h"

#include "Mlt2comxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxDoc

IMPLEMENT_DYNCREATE(CMlt2comxDoc, CDocument)

BEGIN_MESSAGE_MAP(CMlt2comxDoc, CDocument)
	//{{AFX_MSG_MAP(CMlt2comxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxDoc construction/destruction

CMlt2comxDoc::CMlt2comxDoc()
{
	// TODO: add one-time construction code here

}

CMlt2comxDoc::~CMlt2comxDoc()
{
}

BOOL CMlt2comxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxDoc serialization

void CMlt2comxDoc::Serialize(CArchive& ar)
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
// CMlt2comxDoc diagnostics

#ifdef _DEBUG
void CMlt2comxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMlt2comxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxDoc commands
