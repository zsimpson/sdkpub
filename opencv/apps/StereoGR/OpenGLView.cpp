// OpenGLView.cpp : implementation of the COpenGLView class
//

#include "stdafx.h"
#include "OpenGLView.h"
#include <math.h>

typedef struct _Point3d
{
  double x, y, z;
} Point3d;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define vector_length(a)    sqrt(a.x*a.x+a.y*a.y+a.z*a.z)
#define scalar_product(a,b)    (a.x*b.x+a.y*b.y+a.z*b.z)
#define vector_angle(a,b)    (acos(scalar_product(a,b))*180./3.1415926535)
#define vector_product_x(a,b)  (a.y*b.z-a.z*b.y)
#define vector_product_y(a,b)  (a.z*b.x-a.x*b.z)
#define vector_product_z(a,b)  (a.x*b.y-a.y*b.x)
#define vector_product(a,b,c)  c.x=vector_product_x(a,b);c.y=vector_product_y(a,b);c.z=vector_product_z(a,b)
#define sub_vector(a,b,c)    c.x=a.x-b.x;c.y=a.y-b.y;c.z=a.z-b.z
#define add_vector(a,b,c)    c.x=a.x+b.x;c.y=a.y+b.y;c.z=a.z+b.z

#define normalize_vector(a)    {float len;len=(float)vector_length(a);if(len>0){a.x /= len;a.y /= len;a.z /= len;}}

#define vector_lengthV(a)    sqrt(a->x*a->x+a->y*a->y+a->z*a->z)
#define normalize_vectorV(a)  {float len;len=(float)vector_lengthV(a);if(len>0){a->x /= len;a->y /= len;a->z /= len;}}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
  //{{AFX_MSG_MAP(COpenGLView)
  ON_WM_DESTROY()
  ON_WM_SIZE()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONDOWN()
  ON_WM_CREATE()
  //}}AFX_MSG_MAP
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView() : m_pDC(0)
{
  InitCameraPosition();
}

COpenGLView::~COpenGLView()
{
//  delete m_pDC;
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
  // OpenGL требует наличия стилей WS_CLIPCHILDREN и WS_CLIPSIBLINGS
  cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

  return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView printing

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
  // default preparation
  return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
  CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CDocument* COpenGLView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));
  return (CDocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

int COpenGLView::InitOpenGL()
{
// Формируем контекст рабочей области
  m_pDC = new CClientDC(this);
  ASSERT(m_pDC != NULL);

// Получаем дескриптор контекста устройства
  HDC hdc = m_pDC->GetSafeHdc();

// Устанавливаем формат пикселей
  if (SetPixelFormat(hdc)==FALSE)
    return -1;

// Создаем и делаем текущим контекст воспроизведения
  if (CreateGLContext(hdc)==FALSE)
    return -1;

  return 0;
}

void COpenGLView::OnDestroy()
{
  // Получаем текущий контекст воспроизведения
  HGLRC  hrc = ::wglGetCurrentContext();

// Перед удалением он не должен быть текущим
  ::wglMakeCurrent(NULL,  NULL);

// Удаляем контекст воспроизведения
  if (hrc)
    ::wglDeleteContext(hrc);

// Удаляем контекст рабочей области
  if (m_pDC)
    delete m_pDC;

  CView::OnDestroy();
}

BOOL COpenGLView::SetPixelFormat(HDC hdc)
{
 // Заполняем поля структуры
  static PIXELFORMATDESCRIPTOR pfd =   {
    sizeof(PIXELFORMATDESCRIPTOR),  // размер структуры
    1,                              // номер версии
    PFD_DRAW_TO_WINDOW   |          // поддержка вывода в окно
    PFD_SUPPORT_OPENGL   |          // поддержка OpenGL
    PFD_DOUBLEBUFFER,               // двойная буферизация
    PFD_TYPE_RGBA,         // цвета в режиме RGBA
    24,                    // 24-разряда на цвет
    0, 0, 0, 0, 0, 0,      // биты цвета игнорируются
    0,                     // не используется альфа параметр
    0,                     // смещение цветов игнорируются
    0,                     // буфер аккумулятора не используется
    0, 0, 0, 0,            // биты аккумулятора игнорируются
    32,                    // 32-разрядный буфер глубины
    0,                     // буфер трафарета не используется
    0,                     // вспомогательный буфер не используется
    PFD_MAIN_PLANE,        // основной слой
    0,                     // зарезервирован
    0, 0, 0                // маски слоя игнорируются
  };

  int pixelFormat;

// Поддерживает ли система необходимый формат пикселей?
  if((pixelFormat = ::ChoosePixelFormat(hdc, &pfd)) == 0){
    MessageBox("С заданным форматом пикселей работать нельзя");
    return FALSE;
  }

  if (::SetPixelFormat(hdc, pixelFormat, &pfd) == FALSE)
    {
      MessageBox("Ошибка при выполнении SetPixelFormat");
      return FALSE;
    }

  return TRUE;
}

BOOL COpenGLView::CreateGLContext(HDC hdc)
{

// Создаем контекст воспроизведения
  if((m_hrc = ::wglCreateContext(hdc)) == NULL)
    return FALSE;

// Делаем контекст воспроизведения текущим
  if(::wglMakeCurrent(hdc, m_hrc) == FALSE)
    return FALSE;

  return TRUE;
}

void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
  CView::OnSize(nType, cx, cy);

  m_width = cx;
  m_height = cy;
  SetOwnContext();
  glViewport(0, 0, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
  CDocument* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
}

void COpenGLView::BeginScene()
{
  SetOwnContext();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void COpenGLView::EndScene()
{
  Swap();
}

void COpenGLView::Swap()
{
   if (m_pDC)
    SwapBuffers(m_pDC->m_hDC);
}

void COpenGLView::TrackBall(CPoint last, CPoint init, double& angle, double& x, double& y, double& z)
{
  Point3d  end, start, out;
  double    sum, len, norm;
  double pi = 3.1415926535;

  norm = (double)__min(m_width, m_height);

  start.x = (2*init.x-m_width)/norm;
  start.y = (m_height-2.*init.y)/norm;
  sum = start.x*start.x + start.y*start.y;
  if (sum < 1.)  start.z = sqrt(1 - sum);
  else      start.z = 0.;

  end.x = (2.*last.x-m_width)/norm;
  end.y = (m_height-2.*last.y)/norm;
  sum = end.x*end.x + end.y*end.y;
  if (sum < 1.)  end.z = sqrt(1 - sum);
  else      end.z = 0.;

    ASSERT(vector_length(start)*vector_length(end)>1.0e-30);
  angle = scalar_product(start,end)/(vector_length(start)*vector_length(end));

    if (angle<=-1) angle = -0.99999;
    if (angle>=1) angle = 0.99999;

    angle = acos(angle)*180./pi;
  out.x = vector_product_x(start,end);
  out.y = vector_product_y(start,end);
  out.z = vector_product_z(start,end);

  len = vector_length(out);
  if (len != 0.) {
    out.x /= len;
    out.y /= len;
    out.z /= len;
  }

  x = out.x;
  y = out.y;
  z = out.z;
}

void COpenGLView::SetOwnContext()
{
  if (!m_hrc)
    return;

  if (m_pDC) {
    delete m_pDC;
    m_pDC = NULL;
  }

  m_pDC = new CClientDC(this);

  if (wglMakeCurrent(m_pDC->m_hDC, m_hrc))
    return;

//error handler

  return;
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
    SetOwnContext();
    if(nFlags & MK_LBUTTON)
    {
    if(nFlags & MK_SHIFT)
    {
      /* Track translation */
      double x = point.x - m_mousePosition.x;
      double y = point.y - m_mousePosition.y;
      x /= m_width/2;
      y /= m_height/2;
      m_translate[0] += x;
      m_translate[1] += y;

      m_mousePosition = point;
    }
    else
    {
      /* Track rotation */
          double x, y, z, angle;

          TrackBall(point, m_mousePosition, angle, x, y, z);
          m_mousePosition = point;

          glMatrixMode(GL_MODELVIEW);
          glPushMatrix();
          glLoadIdentity();
          glRotated(angle, x, y, z);
          glMultMatrixd(m_rotate);
          glGetDoublev(GL_MODELVIEW_MATRIX, m_rotate);
          glPopMatrix();
    }
    }

  DrawScene();

  CView::OnMouseMove(nFlags, point);
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
  m_mousePosition = point;
  CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::InitCameraPosition()
{
  for(int i = 0; i < 16; i++)
    m_rotate[i] = GLdouble(i/4 == i%4);
  for(i = 0; i < 3; i++)
    m_translate[i] = 0;
}

void COpenGLView::DrawScene(CDC* pDC)
{
}