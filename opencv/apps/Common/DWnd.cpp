// DWnd.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CDWnd

CDWnd::CDWnd()
{
    m_FatherWnd = NULL;
    m_IWK[0] = m_IWK[1] = 0;
    m_WIK[0] = m_WIK[1] = 0;
}

CDWnd::~CDWnd()
{
}


BEGIN_MESSAGE_MAP(CDWnd, CWnd)
	//{{AFX_MSG_MAP(CDWnd)
	ON_WM_PAINT()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDWnd message handlers

BOOL CDWnd::CreateWnd(CWnd* pParent, 
                      char* pName,
                      long  lWidth,
                      long  lHeight,
                      long  lBPP )
{
    BOOL res = TRUE;
    RECT rect;

    rect.left = 0;
    rect.top = 0;
    rect.right = rect.left + lWidth;
    rect.bottom = rect.top + lHeight;

    res = CreateEx( WS_EX_CLIENTEDGE,
                  AfxRegisterWndClass( NULL ),
                  pName,
                  WS_VISIBLE | WS_TILEDWINDOW ,
                  rect, pParent, 0, NULL );
    if( !res ) return FALSE;

    m_Image.Create( rect.right, rect.bottom, lBPP );

    m_FatherWnd = pParent;
    return TRUE;
}

void CDWnd::DrawIplImage( IplImage* pImage, BOOL bSetChannelNumber )
{
    long CN = 3;
    IplImage* pDstImg = m_Image.GetImage();
    if( pImage == NULL ) return;
    if( pImage->depth != IPL_DEPTH_8U ) return;

    if( pDstImg != 0 ) CN = pDstImg->nChannels;
    if( bSetChannelNumber ) CN = pImage->nChannels;
    
    if( pDstImg == NULL ||
        pImage->width != pDstImg->width ||
        pImage->height != pDstImg->height ||
        (CN != pDstImg->nChannels) )
    {
        m_Image.Create( 
            pImage->width,
            pImage->height,
            CN * 8 );
        pDstImg = m_Image.GetImage();
    }

    if( pDstImg == NULL )  return;
    if( pImage->nChannels == pDstImg->nChannels )
    {
        m_Image.CopyOf( pImage );
    }
    else if( pImage->nChannels == 1 && pDstImg->nChannels == 3 )
    { /* gray to color */
        iplGrayToColor(pImage, pDstImg, 1, 1, 1);
    }
    else if( pImage->nChannels == 3 && pDstImg->nChannels == 1 )
    { /* color to gray */
        iplColorToGray( pImage, pDstImg );
    }
}

void CDWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    ReDraw();
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CDWnd::ReDraw( CDC *pDC ) 
{
  
    HDC hDCSrc;
    HDC hDCDst;

    BOOL bReleaseDC = FALSE;
    RECT rect;

    if( m_hWnd == NULL ) return FALSE;

    GetClientRect( &rect );

    if( pDC == NULL ) {pDC = GetDC();bReleaseDC = TRUE; }
    if( pDC == NULL ) return FALSE;

    hDCSrc = m_Image.GetDC();
    hDCDst = pDC->m_hDC;
    if( m_Image.Width() > rect.right - rect.left )
    {
	    SetStretchBltMode(
               hDCDst,           // handle to device context
               HALFTONE );
    }
    else
    {
	    SetStretchBltMode(
               hDCDst,           // handle to device context
               COLORONCOLOR );
    }

    ::StretchBlt( 
        hDCDst,
        rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        hDCSrc,
        0,0,
        m_Image.Width(),
        m_Image.Height(),
        SRCCOPY );

    m_IWK[0] = (double)(rect.right - rect.left) / m_Image.Width();
    m_IWK[1] = (double)(rect.bottom - rect.top) / m_Image.Height();
    m_WIK[0] = (double)m_Image.Width() / (rect.right - rect.left);
    m_WIK[1] = (double)m_Image.Height() / (rect.bottom - rect.top);

    if( bReleaseDC ) ReleaseDC( pDC );

    return TRUE;
}

BOOL CDWnd::DrawToHDC( HDC hDC, RECT* pDstRect ) 
{
  
    HDC hDCSrc;
    HDC hDCDst;

    RECT rect;

    if( m_hWnd == NULL ) return FALSE;

    if( pDstRect ) rect = *pDstRect;
    else GetClientRect( &rect );

    hDCSrc = m_Image.GetDC();
    hDCDst = hDC;
    if( m_Image.Width() > rect.right - rect.left )
    {
	    SetStretchBltMode(
               hDCDst,           // handle to device context
               HALFTONE );
    }
    else
    {
	    SetStretchBltMode(
               hDCDst,           // handle to device context
               COLORONCOLOR );
    }

    ::StretchBlt( 
        hDCDst,
        rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        hDCSrc,
        0,0,
        m_Image.Width(),
        m_Image.Height(),
        SRCCOPY );

    return TRUE;
}

void CDWnd::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CWnd::OnSizing(fwSide, pRect);
	
  // TODO: Add your message handler code here
	
}

void CDWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
    ReDraw();
}

void CDWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
    if( nChar == 115 && nFlags == 31 )
    {
        CString str;
        GetWindowText(str);
        str += ".bmp";
        m_Image.Save((LPCTSTR)str);
    }
	
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
