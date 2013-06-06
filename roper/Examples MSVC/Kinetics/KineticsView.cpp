// KineticsView.cpp : implementation of the CKineticsView class
//

#include "stdafx.h"
#include "Kinetics.h"

#include "KineticsDoc.h"
#include "KineticsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKineticsView

IMPLEMENT_DYNCREATE(CKineticsView, CView)

BEGIN_MESSAGE_MAP(CKineticsView, CView)
	//{{AFX_MSG_MAP(CKineticsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKineticsView construction/destruction

CKineticsView::CKineticsView()
{
	// TODO: add construction code here

}

CKineticsView::~CKineticsView()
{
}

BOOL CKineticsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKineticsView drawing

void CKineticsView::OnDraw(CDC* pDC)
{
	CKineticsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CKineticsView diagnostics

#ifdef _DEBUG
void CKineticsView::AssertValid() const
{
	CView::AssertValid();
}

void CKineticsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKineticsDoc* CKineticsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKineticsDoc)));
	return (CKineticsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKineticsView message handlers
