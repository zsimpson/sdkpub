// Mlt2comxView.cpp : implementation of the CMlt2comxView class
//

#include "stdafx.h"
#include "Mlt2comx.h"

#include "Mlt2comxDoc.h"
#include "Mlt2comxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxView

IMPLEMENT_DYNCREATE(CMlt2comxView, CView)

BEGIN_MESSAGE_MAP(CMlt2comxView, CView)
	//{{AFX_MSG_MAP(CMlt2comxView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxView construction/destruction

CMlt2comxView::CMlt2comxView()
{
	// TODO: add construction code here

}

CMlt2comxView::~CMlt2comxView()
{
}

BOOL CMlt2comxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxView drawing

void CMlt2comxView::OnDraw(CDC* pDC)
{
	CMlt2comxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxView diagnostics

#ifdef _DEBUG
void CMlt2comxView::AssertValid() const
{
	CView::AssertValid();
}

void CMlt2comxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMlt2comxDoc* CMlt2comxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMlt2comxDoc)));
	return (CMlt2comxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMlt2comxView message handlers
