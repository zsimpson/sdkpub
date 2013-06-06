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
//M*/// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "Hawk.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLogView

IMPLEMENT_DYNCREATE(CLogView, CEditView)

CLogView::CLogView() : m_edit(GetEditCtrl()), m_logLength(30000)
{
}

CLogView::~CLogView()
{
}


BEGIN_MESSAGE_MAP(CLogView, CEditView)
	//{{AFX_MSG_MAP(CLogView)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView drawing

void CLogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLogView diagnostics

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CView::AssertValid();
}

void CLogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogView message handlers

int CLogView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_edit.SetReadOnly();	
	return 0;
}

int CLogView::AddLine(LPCTSTR strings)
{
	char	newstring[255];

	strcpy(newstring, "\r\n");
	if (strlen(strings)<252)
        strcat(newstring, strings);
    else 
        strncat(newstring, strings, 252);        


	int end = m_length;//m_edit.GetWindowTextLength();
    if(end + (int)strlen(strings) > m_logLength)
    {
        /* Delete the beginning to free the space */
        m_edit.SetSel(0, end + strlen(strings) - m_logLength);
        m_edit.ReplaceSel("");
    }

	if (end == 0) {
		m_edit.SetWindowText(strings);
		return 0;
	}

	int number_lines = m_edit.GetLineCount();
	int start = m_edit.LineIndex(number_lines-1);

	int len = m_edit.LineLength(end);
	if (len==0) {
		m_edit.SetSel(end, end+1);
		m_edit.ReplaceSel(strings);
		number_lines--;
	} else {
		m_edit.SetSel(end, end+1);
		m_edit.ReplaceSel(newstring);
	}

	return number_lines;
}

void CLogView::AddString(LPCTSTR _text)
{
    char* text = _strdup(_text);
    int index = 0, i = 0;
//    int length = m_edit.GetWindowTextLength();
    int length = m_length;
    int l = strlen(text);
    char* buffer = new char[strlen(text) + 2];
    char c;

    while(1)
    {
        while(text[i] != 0 && text[i] != 10 && text[i] != 13) i++;
        if(text[i] == 0)
        {
            length = ClearHead(strlen(&text[index]));
            m_edit.SetSel(length, length + 1);
            m_edit.ReplaceSel(&text[index]);
            break;
        }

        if(text[i] == 10)
        {
            if(text[i + 1] == 13)
            {
                text[i] = 13;
                text[i + 1] = 10;
                c = text[i + 2];
                text[i + 2] = 0;
                length = ClearHead(strlen(&text[index]));
                m_edit.SetSel(length, length + 1);
                m_edit.ReplaceSel(&text[index]);
                text[i + 2] = c;
                
                index = i + 2;
                i = index;
            }
            else
            {
                memcpy(buffer, &text[index], i - index);
                buffer[i - index] = 13;
                buffer[i - index + 1] = 10;
                buffer[i - index + 2] = 0;
                length = ClearHead(strlen(buffer));;
                m_edit.SetSel(length, length + 1);
                m_edit.ReplaceSel(buffer);

                index = i + 1;
                i = index;
            }
        }
        else
        {
            // text[i] == 13
            if(text[i + 1] == 10)
            {
                i = i + 2;
            }
            else
            {
                memcpy(buffer, &text[index], i - index);
                buffer[i - index] = 13;
                buffer[i - index + 1] = 10;
                buffer[i - index + 2] = 0;

                length = ClearHead(strlen(buffer));
                m_edit.SetSel(length, length + 1);
                m_edit.ReplaceSel(buffer);

                index = i + 1;
                i = index;
            }
        }
    }

    delete buffer;
    delete text;
}

int CLogView::ClearHead(int textLength)
{
    int length = m_length;//m_edit.GetWindowTextLength();
    if(length + textLength > m_logLength)
    {
        /* Delete the beginning to free the space */
        m_edit.SetSel(0, length + textLength - m_logLength);
//        m_edit.SetSel(0, -1);
        m_edit.ReplaceSel("");
    }

    return m_length;//m_edit.GetWindowTextLength();    
}

void CLogView::OnChange() 
{
    m_length = m_edit.GetWindowTextLength();
}
