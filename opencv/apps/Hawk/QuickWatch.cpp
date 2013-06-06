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
//M*/// QuickWatch.cpp : implementation file
//

#include "stdafx.h"
#include "hawk.h"
#include "QuickWatch.h"

extern "C"
{
#include "CVEiCL\EiC\src\typemod.h"
//#include "CVEiCL\EiC\src\datastruct.h"
#include "CVEiCL\EiC\src\global.h"
#include "CVEiCL\EiC\src\func.h"
    
symentry_t* EiC_lookup(char, const char*);
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuickWatch dialog


CQuickWatch::CQuickWatch(CWnd* pParent /*=NULL*/)
	: CDialog(CQuickWatch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuickWatch)
	m_value = _T("");
	m_variable = _T("");
	//}}AFX_DATA_INIT
}


void CQuickWatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuickWatch)
	DDX_Text(pDX, IDC_QWVALUE, m_value);
	DDX_Text(pDX, IDC_QWVARIABLE, m_variable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuickWatch, CDialog)
	//{{AFX_MSG_MAP(CQuickWatch)
	ON_BN_CLICKED(ID_QWCALC, OnQwcalc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickWatch message handlers

void CQuickWatch::OnQwcalc() 
{
    UpdateData(TRUE);
    if(m_variable.IsEmpty())	
    {
        return;
    }

    symentry_t* sym = EiC_lookup(1, LPCTSTR(m_variable));
    if(!sym || !sym->type)
    {
        m_value.Format("Symbol not found...");
    }
    else
    {
        switch(sym->type->obj)
        {
        case t_short:
        case t_int:
        case t_long:
            m_value.Format("%d", EiC_ENV->AR[sym->val.ival].v.ival);
            break;

        case t_uint:
        case t_ulong:    
        case t_ushort:
        case t_enum:
            m_value.Format("%u", EiC_ENV->AR[sym->val.ival].v.uival);
            break;

        case t_char:
        case t_uchar:
            m_value.Format("%c", EiC_ENV->AR[sym->val.ival].v.cval);
            break;

        case t_float:
            m_value.Format("%f", EiC_ENV->AR[sym->val.ival].v.dval);
            break;

        case t_double:
            m_value.Format("%e", EiC_ENV->AR[sym->val.ival].v.dval);
            break;

        case t_pointer:
            m_value.Format("0x%p", EiC_ENV->AR[sym->val.ival].v.p.p);
            break;

        default:
            m_value.Format("Can't display symbol value...");
            break;

        }
    }

    UpdateData(FALSE);

    GetDlgItem(IDC_QWVARIABLE)->SetFocus();
}

BOOL CQuickWatch::OnInitDialog() 
{
	CDialog::OnInitDialog();

    GetDlgItem(IDC_QWVARIABLE)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
