// mltaccumView.cpp : implementation of the CMltaccumView class
//

#include "stdafx.h"
#include "mltaccum.h"

#include "mltaccumDoc.h"
#include "mltaccumView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltaccumView

IMPLEMENT_DYNCREATE(CMltaccumView, CView)

BEGIN_MESSAGE_MAP(CMltaccumView, CView)
	//{{AFX_MSG_MAP(CMltaccumView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltaccumView construction/destruction

CMltaccumView::CMltaccumView()
{
	// TODO: add construction code here

}

CMltaccumView::~CMltaccumView()
{
}

BOOL CMltaccumView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMltaccumView drawing

void CMltaccumView::OnDraw(CDC* pDC)
{
	CMltaccumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMltaccumView diagnostics

#ifdef _DEBUG
void CMltaccumView::AssertValid() const
{
	CView::AssertValid();
}

void CMltaccumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMltaccumDoc* CMltaccumView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMltaccumDoc)));
	return (CMltaccumDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMltaccumView message handlers
