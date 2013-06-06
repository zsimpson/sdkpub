// KineticsDoc.cpp : implementation of the CKineticsDoc class
//

#include "stdafx.h"
#include "Kinetics.h"

#include "KineticsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKineticsDoc

IMPLEMENT_DYNCREATE(CKineticsDoc, CDocument)

BEGIN_MESSAGE_MAP(CKineticsDoc, CDocument)
	//{{AFX_MSG_MAP(CKineticsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKineticsDoc construction/destruction

CKineticsDoc::CKineticsDoc()
{
	// TODO: add one-time construction code here

}

CKineticsDoc::~CKineticsDoc()
{
}

BOOL CKineticsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CKineticsDoc serialization

void CKineticsDoc::Serialize(CArchive& ar)
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
// CKineticsDoc diagnostics

#ifdef _DEBUG
void CKineticsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKineticsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKineticsDoc commands
