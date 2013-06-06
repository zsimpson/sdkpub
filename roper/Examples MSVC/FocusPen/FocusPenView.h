// FocusPenView.h : interface of the CFocusPenView class
//
/////////////////////////////////////////////////////////////////////////////

class CFocusPenView : public CView
{
protected: // create from serialization only
	CFocusPenView();
	DECLARE_DYNCREATE(CFocusPenView)

// Attributes
public:
	CFocusPenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusPenView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFocusPenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFocusPenView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FocusPenView.cpp
inline CFocusPenDoc* CFocusPenView::GetDocument()
   { return (CFocusPenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
