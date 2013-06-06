/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/// HawkView.cpp : implementation of the CHawkView class
//

#include "stdafx.h"
#include "Hawk.h"
#include "MainFrm.h"

#include "HawkDoc.h"
#include "HawkView.h"
#include "GotoLine.h"

#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include "resource.h"

#include "windowsx.h"
#ifdef SubclassWindow
#undef SubclassWindow
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Foward declarations of functions included in this code module:
LRESULT CALLBACK	GoToLineProc(HWND, UINT, WPARAM, LPARAM);
HGDIOBJ  CreateDIB( int width, int height, HDC dc );

/////////////////////////////////////////////////////////////////////////////
// CHawkView

IMPLEMENT_DYNCREATE(CHawkView, CEditView)

BEGIN_MESSAGE_MAP(CHawkView, CEditView)
	//{{AFX_MSG_MAP(CHawkView)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
    ON_WM_CTLCOLOR_REFLECT()
	ON_COMMAND(ID_UNTAB, OnUntab)
	ON_COMMAND(ID_GO_HOME, OnGoHome)
	ON_COMMAND(ID_GOTO_LINE, OnGotoLine)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHawkView construction/destruction

int CHawkView::m_instanceCount = 0;
HFONT     CHawkView::hFont = NULL;
HDC       CHawkView::hMemDC = NULL;
HGDIOBJ   CHawkView::hOldBmp = NULL;
ColorScheme CHawkView::Scheme;

CHawkView::CHawkView() : m_edit(GetEditCtrl()), MaxTextBuffer(1 << 17), 
                                LINE_BUF_SIZE(1000), TAB_SIZE(4)
{
    Line = new char[LINE_BUF_SIZE];
    Space = new char[LINE_BUF_SIZE];
   
    cTokens = 0;
    maxTokens = (1 << 17)/sizeof(Token);
    Tokens = (Token*)malloc( maxTokens * sizeof(Token) );
    TextBuffer = (char*)malloc( MaxTextBuffer );
    Disable_Update = 0;


    if(!m_instanceCount)
    {
        CHawkApp* app = (CHawkApp*)AfxGetApp();

        Scheme.background = app->GetProfileInt("Configuration", "background", RGB(200,220,230));
        Scheme.clr[TOKEN_NORMAL]  = app->GetProfileInt("Configuration", "TOKEN_NORMAL", RGB(0,0,0));
        Scheme.clr[TOKEN_KEYWORD] = app->GetProfileInt("Configuration", "TOKEN_KEYWORD", RGB(0,0,150));
        Scheme.clr[TOKEN_COMMENT] = app->GetProfileInt("Configuration", "TOKEN_COMMENT", RGB(0,150,0));
        Scheme.clr[TOKEN_NUMBER]  = app->GetProfileInt("Configuration", "TOKEN_NUMBER", RGB(150,100,0));
        Scheme.clr[TOKEN_STRING]  = app->GetProfileInt("Configuration", "TOKEN_STRING", RGB(200,50,0));
        Scheme.selbk = app->GetProfileInt("Configuration", "selbk", RGB(150,150,150));
        Scheme.selfk = app->GetProfileInt("Configuration", "selfk", RGB(0,0,0));
        Scheme.bkBrush = (HBRUSH)CreateSolidBrush( Scheme.background );
        hFont = CreateFont( 0, // Height
                            0, // Width
                            0, // Escapement
                            0, // Orientation
                            FW_NORMAL, // Boldness
                            0, // Italic
                            0, // Underline
                            0, // Strikeout
                            DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_MODERN,
                            "Courier" );
        hMemDC = CreateCompatibleDC( 0 );
        hOldBmp = CreateDIB( GetSystemMetrics( SM_CXSCREEN ),
                             GetSystemMetrics( SM_CYSCREEN ), hMemDC );
        SelectObject( hMemDC, hFont );
    }

    m_instanceCount++;
}


CHawkView::~CHawkView()
{
    ASSERT(m_instanceCount > 0);
    m_instanceCount--;
    if(!m_instanceCount)
    {
        DeleteObject( SelectObject( hMemDC, hOldBmp ));
        DeleteDC( hMemDC );
        DeleteObject( hFont );
    }
    
    free( Line );
    free( Space );
    free( TextBuffer );
    free( Tokens );

}


BOOL CHawkView::Customize()
{
    HWND hEdit = m_hWnd;
    SetWindowFont( hEdit, hFont, 0 );
    int tab_size = TAB_SIZE * 4;
    Edit_SetTabStops( hEdit, 1, &tab_size );
    Edit_LimitText( hEdit, 0xffff );
    Edit_FmtLines( hEdit, 1 );
    return TRUE;
}

BOOL CHawkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHawkView drawing
void CHawkView::OnDraw(CDC* pDC)
{
	CHawkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHawkView printing

BOOL CHawkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHawkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHawkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHawkView diagnostics

#ifdef _DEBUG
void CHawkView::AssertValid() const
{
	CEditView::AssertValid();
}

void CHawkView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CHawkDoc* CHawkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHawkDoc)));
	return (CHawkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHawkView message handlers

int CHawkView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

    Customize();
    return 0;
}

CString CHawkView::GetText()
{
    int length = GetBufferLength() + 1;
    char* buffer = new char[length];
    m_edit.GetWindowText(buffer, length);
    CString text = CString(buffer);
    delete buffer;
    return text;
}

void CHawkView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
    UpdateCursorPos();
}

void CHawkView::UpdateCursorPos()
{
    CStatusBar* pBar = ((CMainFrame*)AfxGetMainWnd())->GetStatusBar();
    CString str;
    POINT pt = GetCursorPos();
    str.Format("%d", pt.x + 1);
    pBar->SetPaneText(1, LPCTSTR(str));
    str.Format("%d", pt.y + 1);
    pBar->SetPaneText(2, LPCTSTR(str));

    SetTimer(1, 500, 0); // Update the syntax tip
}

void CHawkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    UpdateCursorPos();
    
	CEditView::OnLButtonDown(nFlags, point);
}

void CHawkView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    CHawkApp* pApp = (CHawkApp*)AfxGetApp();
    CMenu* pMenu = pApp->GetContextMenu();

    pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, pWnd);
}

BOOL CHawkView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    if(HIWORD(wParam))
    {
        int index = HIWORD(wParam) - 1;
        CHawkApp* pApp = (CHawkApp*)AfxGetApp();
        CFuncDialog* pDlg = pApp->GetFuncDialog(index);
        pDlg->SetItems(pApp->GetFunctions(index));
        if(pDlg->DoModal() == IDOK)
        {
            CString str = pDlg->GetCurrentItem();
            int p1, p2;
            m_edit.GetSel(p1, p2);
            m_edit.ReplaceSel(LPCTSTR(str), TRUE);
        }
    }

	return CEditView::OnCommand(wParam, lParam);
}

LRESULT CHawkView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    LRESULT code = 0;
    POINT   pt;
    HWND hEdit = m_hWnd;
    switch (message) 
    {
    case WM_SETFOCUS:
        {
            POINT pt;
            SIZE  sz;
            code = CEditView::WindowProc( message, wParam, lParam);
            ::GetCaretPos( &pt );
            ::DestroyCaret();
            GetTextExtentPoint32( hMemDC, "A", 1, &sz );
            ::CreateCaret( hEdit, 0, 2, sz.cy );
            ::SetCaretPos( pt.x, pt.y );
            ::ShowCaret( hEdit );
        }
        break;
    case WM_CHAR:
        if( (TCHAR)wParam == '\t' )
        {
            DWORD sel = Edit_GetSel(hEdit);
            int sel_start = LOWORD( sel );
            int sel_end = HIWORD( sel );

            if( sel_start != sel_end )
            {
                int i, line_start, line_end;
                ++Disable_Update;

                if( sel_start > sel_end )
                {
                    int t = sel_start;
                    sel_start = sel_end;
                    sel_end = t;
                }

                line_start = Edit_LineFromChar( hEdit, sel_start );
                line_end   = Edit_LineFromChar( hEdit, sel_end );

                for( i = line_start; i < line_end; i++ )
                {
                    int idx = Edit_LineIndex( hEdit, i );
                    Space[TAB_SIZE] = '\0';
                    Edit_SetSel( hEdit, idx, idx );
                    Edit_ReplaceSel( hEdit, Space );
                    Space[TAB_SIZE] = ' ';
                }
                Edit_SetSel( hEdit, sel_start, sel_end + (line_end - line_start)*TAB_SIZE );
                --Disable_Update;
                RenderHighlightedText(TRUE);
                break;
            }
        }
        pt = GetCursorPos();
        code = CEditView::WindowProc( message, wParam, lParam);
        if( (TCHAR)wParam == '\r' || (TCHAR)wParam == '\t' )
        {
            DWORD sel = Edit_GetSel(hEdit);
            int sel_start = LOWORD( sel );
            int sel_end = HIWORD( sel );
            if( sel_start == sel_end )
            {
                int line = Edit_LineFromChar( hEdit, sel_end ), cnt = 0;
                Disable_Update++;
                
                if( (TCHAR)wParam == '\r' && line > 0 )
                {
                    int pos = 0;
                    int line_len = Edit_GetLine( hEdit, line - 1, Line, LINE_BUF_SIZE );
                    Line[line_len] = '\0';
                    while( isspace( Line[pos] ))
                    {
                        cnt = Line[pos] == '\t' ? ((cnt + TAB_SIZE) & -TAB_SIZE) : cnt + 1;
                        pos++;
                    }
                }
                else if( (TCHAR)wParam == '\t' )
                {
                    cnt = ((pt.x + TAB_SIZE) & -TAB_SIZE) - pt.x;
                    Edit_SetSel( hEdit, sel_end-1, sel_end );
                    Edit_ReplaceSel( hEdit, "");
                }

                if( cnt > 0 )
                {
                    Space[cnt] = '\0';
                    ::SendMessage( hEdit, EM_REPLACESEL, 1L, (LPARAM)Space );
                    Space[cnt] = ' ';
                }
                --Disable_Update;
                RenderHighlightedText( TRUE );
            }
        }
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_KEYDOWN:
        {
            DWORD sel = Edit_GetSel( hEdit );
            int line0 = Edit_GetFirstVisibleLine( hEdit );
            int sel_start0 = LOWORD( sel );
            int sel_end0 = HIWORD( sel );
            if( wParam == VK_HOME && sel_start0 == sel_end0 )
            {
                int  line_start = Edit_LineFromChar( hEdit, sel_start0 );
                int  pos = 0; 
                Edit_GetLine( hEdit, line_start, Line, LINE_BUF_SIZE );
                line_start = Edit_LineIndex( hEdit, line_start );
                while( isspace(Line[pos])) pos++;
                if( line_start + pos != sel_start0 )
                {
                    Edit_SetSel( hEdit, line_start + pos, line_start + pos );
                }
                else
                {
                    Edit_SetSel( hEdit, line_start, line_start );
                }
                Edit_ScrollCaret( hEdit );
            }
            else
            {
                code = CEditView::WindowProc( message, wParam, lParam);
                sel = Edit_GetSel( hEdit );
                int sel_start1 = LOWORD( sel );
                int sel_end1 = HIWORD( sel );

                if( ((int)wParam == VK_PRIOR || (int)wParam == VK_NEXT) && 
                    Edit_GetFirstVisibleLine( hEdit ) == line0 )
                {
                    int new_pos = wParam == VK_PRIOR ? 0 : ::Edit_GetTextLength( hEdit );
                    if( sel_start1 != sel_end1 )
                    {
                        if( (int)wParam == VK_PRIOR )
                            sel_start1 = new_pos;
                        else
                            sel_end1 = new_pos;
                    }
                    else
                    {
                        sel_start1 = sel_end1 = new_pos;
                    }

                    Edit_SetSel( hEdit, sel_start1, sel_end1 );
                    Edit_ScrollCaret( hEdit );
                }

                if( (sel_start0 != sel_start1 || sel_end0 != sel_end1) && 
                    abs(sel_end0 - sel_start0) + abs(sel_end1 - sel_start1) > 0)
                {
                    RenderHighlightedText();
                }
            }
            UpdateCursorPos();
        }
        break;
    case WM_MOUSEMOVE:
        {
            DWORD sel = Edit_GetSel( hEdit );
            int sel_start0 = LOWORD( sel );
            int sel_end0 = HIWORD( sel );
            code = CEditView::WindowProc( message, wParam, lParam);
            sel = Edit_GetSel( hEdit );
            int sel_start1 = LOWORD( sel );
            int sel_end1 = HIWORD( sel );
            if( sel_start0 != sel_start1 || sel_end0 != sel_end1 )
            {
                RenderHighlightedText();
            }
            UpdateCursorPos();
        }
        break;
    case WM_LBUTTONUP:
        code = CEditView::WindowProc( message, wParam, lParam);
        RenderHighlightedText();
        break;
    case WM_PAINT:
        {
            CPaintDC dc(this);
            RenderHighlightedText();
        }
        break;
    default:
        return CEditView::WindowProc(message, wParam, lParam);
    }
    return code;
}
//
//LRESULT CALLBACK GoToLineProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    lParam;
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        {
//            int upper = Edit_GetLineCount( hEdit );
//            SendDlgItemMessage( hDlg, IDC_LINESPIN, UDM_SETRANGE, 0, MAKELONG( upper, 1));
//            Edit_SetSel( GetDlgItem( hDlg, IDC_LINETEXT ), 0, -1 );
//            SetFocus( GetDlgItem( hDlg, IDC_LINETEXT ));
//            break;
//        }
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
//        {
//            int val = GetDlgItemInt( hDlg, IDC_LINETEXT, 0, 0 );
//            EndDialog(hDlg, LOWORD(val));
//            return TRUE;
//        }
//        break;
//    }
//    return FALSE;
//}


HGDIOBJ  CreateDIB( int width, int height, HDC dc )
{
    BITMAPINFO bmi;
    HBITMAP hbmp;
    void* data;

    memset( &bmi.bmiHeader, 0, sizeof(bmi.bmiHeader));

    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 16;
    bmi.bmiHeader.biCompression = BI_RGB;

    hbmp = CreateDIBSection( dc, &bmi, DIB_RGB_COLORS, &data, 0, 0 ); 
    return SelectObject( dc, hbmp ); 
}


int CHawkView::ScanTextBuffer( char* text, Token* tokens, int max_tokens )
{
    Lexer lexer;
    Token prev_token, token;
    Token* tokens0 = tokens;

    max_tokens;

    InitLexer( &lexer, text );
    GetToken( &lexer, &prev_token );
    lexer.pos = 0;

    for(;;)
    {
        GetToken( &lexer, &token );
        if( token.type != prev_token.type )
        {
            *tokens++ = prev_token;
            prev_token = token;
        }
        if( token.type == TOKEN_END ) break;
    }
    return tokens - tokens0;
}

void CHawkView::RenderHighlightedText( BOOL update )
{
    HWND  hEdit = m_hWnd;
    HDC   hScreenDC = ::GetDC(hEdit);
    RECT  rect;
    SIZE  size;
    POINT pt;
    char* text = TextBuffer;
    int   fst_char, fst_line;
    int   t;
    int   cChars = ::Edit_GetTextLength( hEdit );
    int   offset = 0;
    ColorScheme* scheme = &Scheme;

    if( Disable_Update ) return;
    
    memset( Space, ' ', LINE_BUF_SIZE );
    
    text = TextBuffer;
    if( update )
    {
        cChars = ::GetWindowText( hEdit, text, 0xffff );
        cTokens = ScanTextBuffer( text, Tokens, maxTokens );
    }
    fst_line = Edit_GetFirstVisibleLine( hEdit );
    fst_char = Edit_LineIndex( hEdit, fst_line );
    
    t = 0;
    if( Tokens[t].start < fst_char || cTokens < 2 )
    {
        int  right = cTokens;
        while( right - t > 1 )
        {
            int m = (right + t)>>1;
            if( Tokens[m].start <= fst_char )
                t = m;                                
            else
                right = m;
        }
    }

    ::GetCaretPos( &pt );
    ::HideCaret( hEdit );
    ::GetClientRect( hEdit, &rect );
    FillRect( hMemDC, &rect, scheme->bkBrush );
    GetTextExtentPoint32( hMemDC, "A", 1, &size );
    SetBkColor( hMemDC, scheme->background );

    if( cChars > 0 && cTokens > 0 && t < cTokens )
    {
        int   lines = (rect.bottom + size.cy - 1)/(size.cy > 1 ? size.cy : 1);
        int   x = 0, y = 0;
        int   pos = fst_char;
        int   line_start = fst_char;
        DWORD sel = Edit_GetSel( hEdit );
        int   sel_start = LOWORD( sel );
        int   sel_end = HIWORD( sel );
        offset = GetScrollPos( SB_HORZ );

        ::SetTextColor( hMemDC, Scheme.clr[Tokens[t].type]);

        for( ;; )
        {
            int start_pos = pos;
            int end_pos = t+1 < cTokens ? Tokens[t+1].start : cChars;
            while( pos < end_pos && text[pos] != '\r' && text[pos] != '\t' ) pos++;

            if( pos > start_pos )
            {
                ::TextOut( hMemDC, x * size.cx - offset, y * size.cy,
                           text + start_pos, pos - start_pos );
                x += pos - start_pos;
            }

            if( text[pos] == '\r' || pos == cChars )
            {
                if( sel_start < pos && line_start < sel_end )
                {
                    int start, end;
                    ::SetBkColor( hMemDC, Scheme.selbk );
                    ::SetTextColor( hMemDC, Scheme.selfk );
                    start = sel_start > line_start ? sel_start : line_start;
                    end = sel_end < pos ? sel_end : pos;
                    if( end > start )
                    {
                        int i, xx = 0;
                        int output_count = 0;
                        for( i = line_start; i < start; i++ )
                        {
                            xx = text[i] == '\t' ? (xx + TAB_SIZE) & -TAB_SIZE : xx + 1;
                        }

                        for( ; i < end; i++ )
                        {
                            if( text[i] == '\t' )
                            {
                                int cnt = ((xx + output_count + TAB_SIZE) & -TAB_SIZE) - 
                                           (xx + output_count);
                                memset( Line + output_count, ' ', cnt );
                                output_count += cnt;
                            }
                            else
                            {
                                Line[output_count++] = text[i];
                            }
                        }
                        ::TextOut( hMemDC, xx*size.cx - offset,
                                   y*size.cy, Line, output_count );
                    }
                    if( pos < sel_end )
                    {
                        ::TextOut( hMemDC, x*size.cx - offset,
                                   y*size.cy, Space, 200 );
                    }
                    ::SetBkColor( hMemDC, Scheme.background );
                    ::SetTextColor( hMemDC, Scheme.clr[Tokens[t].type] );
                }
                x = 0;
                y++;
                if( y >= lines ) break;
                pos += 2;
                line_start = pos;
            }
            
            if( text[pos] == '\t' )
            {
                x = (x + TAB_SIZE) & -TAB_SIZE;
                pos++;
            }

            if( pos >= end_pos )
            {
                if( pos >= cChars ) break;
                t++;
                ::SetTextColor( hMemDC, Scheme.clr[Tokens[t].type]);
            }
        }
    }

    BitBlt( hScreenDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY );
    ::ReleaseDC( hEdit, hScreenDC );
    ::ShowCaret( hEdit );
    UpdateCursorPos();
}



POINT CHawkView::GetCoord( HWND hEdit, int pos )
{
    POINT pt;
    int   i, line_start;
    pt.x = 0;
    pt.y = Edit_LineFromChar( hEdit, pos );
    line_start = Edit_LineIndex( hEdit, pt.y );
    Edit_GetLine( hEdit, pt.y, Line, LINE_BUF_SIZE );

    for( i = 0; line_start + i < pos; i++ )
    {
        pt.x = Line[i] != '\t' ? pt.x + 1 : (pt.x + TAB_SIZE) & -TAB_SIZE;
    }

    return pt;
}


POINT CHawkView::GetCursorPos()
{
    DWORD sel = Edit_GetSel( m_hWnd );
    return  GetCoord( m_hWnd, HIWORD( sel ));
}


void CHawkView::GoToLine( int line )
{
    HWND hEdit = m_hWnd; 
    int  count = Edit_GetLineCount( hEdit );
    int  ln_idx;

    if( --line < 0 ) line = 0;
    if( line >= count ) line = count - 1;
    ln_idx = Edit_LineIndex( hEdit, line );
    Edit_SetSel( hEdit, ln_idx, ln_idx );
    ::SetFocus( hEdit );
    Edit_ScrollCaret( hEdit );
}


void CHawkView::OnChange() 
{
    GetDocument()->SetModifiedFlag();
    RenderHighlightedText(TRUE);
}

HBRUSH CHawkView::CtlColor( CDC* pDC, UINT nCtlColor )
{
    pDC->SetTextColor( Scheme.clr[TOKEN_NORMAL]);
    pDC->SetBkColor( Scheme.background );
    return Scheme.bkBrush;
}

void CHawkView::OnUntab() 
{
    HWND hEdit = m_hWnd;
    DWORD sel = Edit_GetSel(hEdit);
    int sel_start = LOWORD( sel );
    int sel_end = HIWORD( sel );
    if( sel_start != sel_end )
    {
        int i, line_start, line_end;
        ++Disable_Update;

        if( sel_start > sel_end )
        {
            int t = sel_start;
            sel_start = sel_end;
            sel_end = t;
        }

        line_start = Edit_LineFromChar( hEdit, sel_start );
        line_end   = Edit_LineFromChar( hEdit, sel_end );

        for( i = line_start; i < line_end; i++ )
        {
            int j, idx = Edit_LineIndex( hEdit, i );
            Edit_GetLine( hEdit, i, Line, LINE_BUF_SIZE );
            for( j = 0; j < TAB_SIZE; j++ )
            {
                if( Line[j] != ' ' )
                {
                    j += Line[j] == '\t';
                    break;
                }
            }
            Edit_SetSel( hEdit, idx, idx + j );
            Edit_ReplaceSel( hEdit, "" ); 
            sel_end -= j;
        }
        Edit_SetSel( hEdit, sel_start, sel_end );
        --Disable_Update;
        RenderHighlightedText( TRUE );
    }
}

void CHawkView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    RenderHighlightedText(TRUE);
}

void CHawkView::OnGoHome() 
{
    Edit_SetSel( m_hWnd, 0, 0 );
    Edit_ScrollCaret( m_hWnd );
}

void CHawkView::OnGotoLine() 
{
    int sel1, sel2;
    m_edit.GetSel(sel1,sel2);
    CGotoLine dlg(Edit_GetLineCount( m_hWnd ),Edit_LineFromChar(m_hWnd,sel2)+1, this);

    if(dlg.DoModal() == IDOK)
    {
        int line = dlg.m_line;
        GoToLine( line );
    }
}

void CHawkView::OnTimer(UINT nIDEvent) 
{
    UpdateTip();
    KillTimer(1);
	CEditView::OnTimer(nIDEvent);
}

void CHawkView::UpdateTip()
{
    CEdit& edit = GetEditCtrl();
    int s1, s2, s;
    edit.GetSel(s1, s2);
    if(s1 != s2)
        return; // Selection is active
    s = s1;

    CString strtext = GetText();
    const unsigned char* text = (const unsigned char*)LPCTSTR(strtext);
    int length = GetBufferLength();
    if(!length)
        return;
    for(; s1 < length; s1++)
        if(!((text[s1] >= 'A' && text[s1] <= 'Z') || 
                (text[s1] >= 'a' && text[s1] <= 'z') ||
                (text[s1] >= '0' && text[s1] <= '9') ||
                text[s1] == '_'))
            break;
    for(; s2 >= 0; s2--)
        if(!((text[s2] >= 'A' && text[s2] <= 'Z') || 
                (text[s2] >= 'a' && text[s2] <= 'z') ||
                (text[s2] >= '0' && text[s2] <= '9') ||
                text[s2] == '_'))
            break;

    int tokenLength = s1 - s2 - 1;
    if(tokenLength <= 0)
        return; // Nothing to update
    char* token = new char[tokenLength + 1];
    memcpy(token, &text[s2 + 1], tokenLength);
    token[tokenLength] = 0;

    CHawkApp* app = (CHawkApp*)AfxGetApp();
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    CString tip = app->GenDecl(token);
    if(!tip.IsEmpty())
        frame->GetStatusBar()->SetPaneText(0, LPCTSTR(tip));
    delete token;
}
