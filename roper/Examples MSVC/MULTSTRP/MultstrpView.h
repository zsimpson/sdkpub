// MultstrpView.h : interface of the CMultstrpView class
//
/////////////////////////////////////////////////////////////////////////////

class CMultstrpView : public CView
{
protected: // create from serialization only
	CMultstrpView();
	DECLARE_DYNCREATE(CMultstrpView)

// Attributes
public:
	CMultstrpDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultstrpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultstrpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultstrpView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MultstrpView.cpp
inline CMultstrpDoc* CMultstrpView::GetDocument()
   { return (CMultstrpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
