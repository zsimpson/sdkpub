// Mlt2comxView.h : interface of the CMlt2comxView class
//
/////////////////////////////////////////////////////////////////////////////

class CMlt2comxView : public CView
{
protected: // create from serialization only
	CMlt2comxView();
	DECLARE_DYNCREATE(CMlt2comxView)

// Attributes
public:
	CMlt2comxDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlt2comxView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMlt2comxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMlt2comxView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Mlt2comxView.cpp
inline CMlt2comxDoc* CMlt2comxView::GetDocument()
   { return (CMlt2comxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
