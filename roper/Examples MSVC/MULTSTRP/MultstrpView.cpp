// MultstrpView.cpp : implementation of the CMultstrpView class
//

#include "stdafx.h"
#include "Multstrp.h"

#include "MultstrpDoc.h"
#include "MultstrpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultstrpView

IMPLEMENT_DYNCREATE(CMultstrpView, CView)

BEGIN_MESSAGE_MAP(CMultstrpView, CView)
	//{{AFX_MSG_MAP(CMultstrpView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultstrpView construction/destruction

CMultstrpView::CMultstrpView()
{
	// TODO: add construction code here

}

CMultstrpView::~CMultstrpView()
{
}

BOOL CMultstrpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMultstrpView drawing

void CMultstrpView::OnDraw(CDC* pDC)
{
	CMultstrpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMultstrpView diagnostics

#ifdef _DEBUG
void CMultstrpView::AssertValid() const
{
	CView::AssertValid();
}

void CMultstrpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultstrpDoc* CMultstrpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultstrpDoc)));
	return (CMultstrpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultstrpView message handlers
