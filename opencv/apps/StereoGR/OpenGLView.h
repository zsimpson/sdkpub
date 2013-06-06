// OpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__8E83909C_3A90_11D1_AB25_000000000000__INCLUDED_)
#define AFX_OPENGLVIEW_H__8E83909C_3A90_11D1_AB25_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <gl\gl.h>

class COpenGLView : public CView
{
protected: // create from serialization only
  COpenGLView();
  DECLARE_DYNCREATE(COpenGLView)

// Attributes
protected:
  GLint m_width;  // ширина окна OpenGL
  GLint m_height; // высота окна OpenGL
  POINT m_mousePosition;
  GLdouble m_translate[3];
  GLdouble m_rotate[16];


public:
  CDocument* GetDocument();

// Operations
public:

protected:
  CClientDC  *m_pDC;

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(COpenGLView)
  public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual void DrawScene(CDC* pDC = 0);
  void InitCameraPosition();
  void SetOwnContext();
  void TrackBall(CPoint last, CPoint init, double& angle, double& x, double& y, double& z);
  void Swap();
  void EndScene();
  void BeginScene();
  virtual ~COpenGLView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  BOOL SetPixelFormat(HDC hdc);
  BOOL CreateGLContext(HDC hdc);

// Generated message map functions
protected:
  int InitOpenGL();
  //{{AFX_MSG(COpenGLView)
  afx_msg void OnDestroy();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
private:
  HGLRC m_hrc;
};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline CDocument* COpenGLView::GetDocument()
   { return (CDocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLVIEW_H__8E83909C_3A90_11D1_AB25_000000000000__INCLUDED_)