// FocusDoc.cpp : implementation of the CFocusDoc class
//

#include "stdafx.h"
#include "Focus.h"

#include "FocusDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFocusDoc

IMPLEMENT_DYNCREATE(CFocusDoc, CDocument)

BEGIN_MESSAGE_MAP(CFocusDoc, CDocument)
	//{{AFX_MSG_MAP(CFocusDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusDoc construction/destruction

CFocusDoc::CFocusDoc()
{
	// TODO: add one-time construction code here

}

CFocusDoc::~CFocusDoc()
{
}

BOOL CFocusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFocusDoc serialization

void CFocusDoc::Serialize(CArchive& ar)
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
// CFocusDoc diagnostics

#ifdef _DEBUG
void CFocusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFocusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFocusDoc commands
