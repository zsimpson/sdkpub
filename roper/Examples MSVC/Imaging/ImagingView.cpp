// ImagingView.cpp : implementation of the CImagingView class
//

#include "stdafx.h"
#include "Imaging.h"

#include "ImagingDoc.h"
#include "ImagingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagingView

IMPLEMENT_DYNCREATE(CImagingView, CView)

BEGIN_MESSAGE_MAP(CImagingView, CView)
	//{{AFX_MSG_MAP(CImagingView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagingView construction/destruction

CImagingView::CImagingView()
{
	// TODO: add construction code here

}

CImagingView::~CImagingView()
{
}

BOOL CImagingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImagingView drawing

void CImagingView::OnDraw(CDC* pDC)
{
	CImagingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CImagingView printing

BOOL CImagingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImagingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImagingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImagingView diagnostics

#ifdef _DEBUG
void CImagingView::AssertValid() const
{
	CView::AssertValid();
}

void CImagingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImagingDoc* CImagingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagingDoc)));
	return (CImagingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImagingView message handlers
