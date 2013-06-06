// FocusView.cpp : implementation of the CFocusView class
//

#include "stdafx.h"
#include "Focus.h"

#include "FocusDoc.h"
#include "FocusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFocusView

IMPLEMENT_DYNCREATE(CFocusView, CView)

BEGIN_MESSAGE_MAP(CFocusView, CView)
	//{{AFX_MSG_MAP(CFocusView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusView construction/destruction

CFocusView::CFocusView()
{
	// TODO: add construction code here

}

CFocusView::~CFocusView()
{
}

BOOL CFocusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFocusView drawing

void CFocusView::OnDraw(CDC* pDC)
{
	CFocusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFocusView printing

BOOL CFocusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFocusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFocusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFocusView diagnostics

#ifdef _DEBUG
void CFocusView::AssertValid() const
{
	CView::AssertValid();
}

void CFocusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFocusDoc* CFocusView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFocusDoc)));
	return (CFocusDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFocusView message handlers
