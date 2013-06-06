// FocusPenDoc.cpp : implementation of the CFocusPenDoc class
//

#include "stdafx.h"
#include "FocusPen.h"

#include "FocusPenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFocusPenDoc

IMPLEMENT_DYNCREATE(CFocusPenDoc, CDocument)

BEGIN_MESSAGE_MAP(CFocusPenDoc, CDocument)
	//{{AFX_MSG_MAP(CFocusPenDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusPenDoc construction/destruction

CFocusPenDoc::CFocusPenDoc()
{
	// TODO: add one-time construction code here

}

CFocusPenDoc::~CFocusPenDoc()
{
}

BOOL CFocusPenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFocusPenDoc serialization

void CFocusPenDoc::Serialize(CArchive& ar)
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
// CFocusPenDoc diagnostics

#ifdef _DEBUG
void CFocusPenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFocusPenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFocusPenDoc commands
