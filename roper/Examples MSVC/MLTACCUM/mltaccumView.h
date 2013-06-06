// mltaccumView.h : interface of the CMltaccumView class
//
/////////////////////////////////////////////////////////////////////////////

class CMltaccumView : public CView
{
protected: // create from serialization only
	CMltaccumView();
	DECLARE_DYNCREATE(CMltaccumView)

// Attributes
public:
	CMltaccumDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMltaccumView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMltaccumView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMltaccumView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mltaccumView.cpp
inline CMltaccumDoc* CMltaccumView::GetDocument()
   { return (CMltaccumDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
