// FocusPenView.cpp : implementation of the CFocusPenView class
//

#include "stdafx.h"
#include "FocusPen.h"

#include "FocusPenDoc.h"
#include "FocusPenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFocusPenView

IMPLEMENT_DYNCREATE(CFocusPenView, CView)

BEGIN_MESSAGE_MAP(CFocusPenView, CView)
	//{{AFX_MSG_MAP(CFocusPenView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusPenView construction/destruction

CFocusPenView::CFocusPenView()
{
	// TODO: add construction code here

}

CFocusPenView::~CFocusPenView()
{
}

BOOL CFocusPenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFocusPenView drawing

void CFocusPenView::OnDraw(CDC* pDC)
{
	CFocusPenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFocusPenView diagnostics

#ifdef _DEBUG
void CFocusPenView::AssertValid() const
{
	CView::AssertValid();
}

void CFocusPenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFocusPenDoc* CFocusPenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFocusPenDoc)));
	return (CFocusPenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFocusPenView message handlers
