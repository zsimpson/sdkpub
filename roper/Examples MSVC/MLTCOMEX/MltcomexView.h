// MltcomexView.h : interface of the CMltcomexView class
//
/////////////////////////////////////////////////////////////////////////////

class CMltcomexView : public CView
{
protected: // create from serialization only
	CMltcomexView();
	DECLARE_DYNCREATE(CMltcomexView)

// Attributes
public:
	CMltcomexDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMltcomexView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMltcomexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMltcomexView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MltcomexView.cpp
inline CMltcomexDoc* CMltcomexView::GetDocument()
   { return (CMltcomexDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
