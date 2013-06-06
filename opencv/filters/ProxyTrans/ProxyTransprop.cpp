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
//M*/

// This class implements the property page for the ProxyTransform filter

#pragma warning( disable: 4201 )
#include <streams.h>
#include <commctrl.h>
#include <olectl.h>
#include <memory.h>
#include "resource.h"
#include "iProxyTrans.h"
#include "ProxyTrans.h"
#include "ProxyTransprop.h"
#include "ProxyTransuids.h"

//
// CreateInstance
//
// This goes in the factory template table to create new filter instances
//
const signed char MaxLevel = 127;
const signed char MinLevel = -128;

CUnknown * WINAPI ProxyTransformProperties::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    CUnknown *punk = new ProxyTransformProperties(lpunk, phr);
    if (punk == NULL) {
	*phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//
// Constructor
//
ProxyTransformProperties::ProxyTransformProperties(LPUNKNOWN pUnk, HRESULT *phr) :
    CBasePropertyPage(NAME("ProxyTrans Property Page"),pUnk,
                      IDD_ProxyTransformPROP,
                      IDS_TITLE),
    m_pProxyTransform(NULL)
{
    InitCommonControls();
} // (Constructor)


//
// SetDirty
//
// Sets m_bDirty and notifies the property page site of the change
//
void ProxyTransformProperties::SetDirty()
{
    m_bDirty = TRUE;
    if (m_pPageSite) {
        m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
    }

} // SetDirty


//
// OnReceiveMessage
//
// Virtual method called by base class with Window messages
//
BOOL ProxyTransformProperties::OnReceiveMessage(HWND hwnd,
                                                  UINT uMsg,
                                                  WPARAM wParam,
                                                  LPARAM lParam)
{
    switch (uMsg)
    {        
        case WM_INITDIALOG:
        {
        return (LRESULT) 1;
        }
        case WM_VSCROLL:
        {
        return (LRESULT) 1;
        }

        case WM_COMMAND:
        {
            return (LRESULT) 1;
        }

        case WM_DESTROY:
        {
        return (LRESULT) 1;
        }
    }
    return CBasePropertyPage::OnReceiveMessage(hwnd,uMsg,wParam,lParam);

} // OnReceiveMessage


//
// OnConnect
//
// Called when the property page connects to a filter
//
HRESULT ProxyTransformProperties::OnConnect(IUnknown *pUnknown)
{
    ASSERT(m_pProxyTransform == NULL);

    HRESULT hr = pUnknown->QueryInterface(IID_IProxyTransform, (void **) &m_pProxyTransform);
    if (FAILED(hr)) {
        return E_NOINTERFACE;
    }

    ASSERT(m_pProxyTransform);

    return NOERROR;

} // OnConnect


//
// OnDisconnect
//
// Called when we're disconnected from a filter
//
HRESULT ProxyTransformProperties::OnDisconnect()
{
    // Release of Interface after setting the parameters

    if (m_pProxyTransform == NULL) {
        return E_UNEXPECTED;
    }
    m_pProxyTransform->Release();
    m_pProxyTransform = NULL;
    return NOERROR;

} // OnDisconnect


//
// OnDeactivate
//
// We are being deactivated
//
HRESULT ProxyTransformProperties::OnDeactivate(void)
{
    return NOERROR;

} // OnDeactivate


//
// OnApplyChanges
//
// Changes made should be kept. Change the  variable
//
HRESULT ProxyTransformProperties::OnApplyChanges()
{
    m_bDirty = FALSE;
    return(NOERROR);

} // OnApplyChanges