// MultstrpDoc.cpp : implementation of the CMultstrpDoc class
//

#include "stdafx.h"
#include "Multstrp.h"

#include "MultstrpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultstrpDoc

IMPLEMENT_DYNCREATE(CMultstrpDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultstrpDoc, CDocument)
	//{{AFX_MSG_MAP(CMultstrpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultstrpDoc construction/destruction

CMultstrpDoc::CMultstrpDoc()
{
	// TODO: add one-time construction code here

}

CMultstrpDoc::~CMultstrpDoc()
{
}

BOOL CMultstrpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMultstrpDoc serialization

void CMultstrpDoc::Serialize(CArchive& ar)
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
// CMultstrpDoc diagnostics

#ifdef _DEBUG
void CMultstrpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultstrpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultstrpDoc commands
