// KineticsView.h : interface of the CKineticsView class
//
/////////////////////////////////////////////////////////////////////////////

class CKineticsView : public CView
{
protected: // create from serialization only
	CKineticsView();
	DECLARE_DYNCREATE(CKineticsView)

// Attributes
public:
	CKineticsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKineticsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKineticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKineticsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in KineticsView.cpp
inline CKineticsDoc* CKineticsView::GetDocument()
   { return (CKineticsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
