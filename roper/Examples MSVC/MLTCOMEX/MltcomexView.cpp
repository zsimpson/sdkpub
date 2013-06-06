// MltcomexView.cpp : implementation of the CMltcomexView class
//

#include "stdafx.h"
#include "Mltcomex.h"

#include "MltcomexDoc.h"
#include "MltcomexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltcomexView

IMPLEMENT_DYNCREATE(CMltcomexView, CView)

BEGIN_MESSAGE_MAP(CMltcomexView, CView)
	//{{AFX_MSG_MAP(CMltcomexView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltcomexView construction/destruction

CMltcomexView::CMltcomexView()
{
	// TODO: add construction code here

}

CMltcomexView::~CMltcomexView()
{
}

BOOL CMltcomexView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMltcomexView drawing

void CMltcomexView::OnDraw(CDC* pDC)
{
	CMltcomexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMltcomexView diagnostics

#ifdef _DEBUG
void CMltcomexView::AssertValid() const
{
	CView::AssertValid();
}

void CMltcomexView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMltcomexDoc* CMltcomexView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMltcomexDoc)));
	return (CMltcomexDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMltcomexView message handlers
