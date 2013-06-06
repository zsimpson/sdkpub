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
// This class implements the property page for the CamShift filter

// This class implements the property page for the CCondens filter
#include <stdio.h>
#include <streams.h>
#include <commctrl.h>
#include <olectl.h>
#include <memory.h>
#include "resource.h"
#include "iCamShift.h"
#include "CamShiftF.h"
#include "CamShiftProp.h"
#include "CamShiftUIDs.h"

//
// CreateInstance
//
// This goes in the factory template table to create new filter instances
//

//
// CreateInstance
//
// This goes in the factory template table to create new filter instances
//
CUnknown * WINAPI CCamShiftProperties::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    CUnknown *punk = new CCamShiftProperties(lpunk, phr);
    if (punk == NULL) {
    *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


void CCamShiftProperties::InitSlider( int id, int lower, int upper, int tic_freq )
{
    HWND slider = GetDlgItem( m_hWnd, id );
    if( slider )
    {
        SendMessage( slider, TBM_SETRANGE, TRUE, MAKELONG(lower, upper) );

        if( tic_freq > 0 )
        {
            SendMessage( slider, TBM_SETTICFREQ, tic_freq, 0 );
        }
    }
}


void CCamShiftProperties::SetSliderPos( int id, int pos )
{
    HWND slider = GetDlgItem( m_hWnd, id );
    if( slider )
    {
        SendMessage( slider, TBM_SETPOS, TRUE, pos );
    }
}


int CCamShiftProperties::GetSliderPos( int id )
{
    HWND slider = GetDlgItem( m_hWnd, id );
    int pos = 0;

    if( slider )
    {
        pos = SendMessage( slider, TBM_GETPOS, 0, 0 );
    }

    return pos;
}


void CCamShiftProperties::ReadParamsFromControls()
{
    m_params.x = ((float)GetSliderPos( IDC_WIN_LEFT ))/SLIDER_MAX;
    m_params.y = ((float)GetSliderPos( IDC_WIN_TOP ))/SLIDER_MAX;
    m_params.width = ((float)GetSliderPos( IDC_WIN_WIDTH ))/SLIDER_MAX;
    m_params.height = ((float)GetSliderPos( IDC_WIN_HEIGHT ))/SLIDER_MAX;

    m_params.Smin = GetSliderPos( IDC_S_MIN );
    m_params.Vmin = GetSliderPos( IDC_V_MIN );

    //m_params.nSamples = GetSliderPos( IDC_SLIDERS_NUM );

    m_params.view = IsDlgButtonChecked( m_hWnd, IDC_BACKPR );
}


void CCamShiftProperties::WriteParamsToControls()
{
    SetSliderPos( IDC_WIN_LEFT, cvRound( m_params.x * SLIDER_MAX ));
    SetSliderPos( IDC_WIN_TOP,  cvRound( m_params.y * SLIDER_MAX ));
    SetSliderPos( IDC_WIN_WIDTH, cvRound( m_params.width * SLIDER_MAX ));
    SetSliderPos( IDC_WIN_HEIGHT, cvRound( m_params.height * SLIDER_MAX ));
    
    SetSliderPos( IDC_S_MIN, m_params.Smin );
    SetSliderPos( IDC_V_MIN, m_params.Vmin );

    //SetSliderPos( IDC_SAMPLES_NUM, m_params.nSamples );

    CheckRadioButton( m_hWnd, IDC_NORMAL, IDC_BACKPR, m_params.view + IDC_NORMAL );
}

//
// Constructor
//
CCamShiftProperties::CCamShiftProperties(LPUNKNOWN pUnk, HRESULT *phr) :
    CBasePropertyPage(NAME("CamShift Property Page"),pUnk,
                      IDD_CAMSHIFTPROP,
                      IDS_TITLE),
    m_pCamShift(NULL)
{
    m_hWnd = 0;
} // (Constructor)


//
// SetDirty
//
// Sets m_bDirty and notifies the property page site of the change
//
void CCamShiftProperties::SetDirty()
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
BOOL CCamShiftProperties::OnReceiveMessage( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {        
        case WM_INITDIALOG:
            m_hWnd = hwnd;
            
            InitSlider( IDC_WIN_LEFT, 0, 1000, 0 );
            InitSlider( IDC_WIN_TOP, 0, 1000, 0 );
            InitSlider( IDC_WIN_WIDTH, 0, 1000, 0 );
            InitSlider( IDC_WIN_HEIGHT, 0, 1000, 0 );

            InitSlider( IDC_S_MIN, 0, 255, 5 );
            InitSlider( IDC_V_MIN, 0, 255, 5 );

            //InitSlider( IDC_SAMPLES_NUM, 16, 256, 16 );

            WriteParamsToControls();
            break;
        
        case WM_HSCROLL:
            OnApplyChanges();
            break;
        
        case WM_COMMAND:

            OnApplyChanges();
            if(LOWORD(wParam) == IDC_START)
            {
                m_pCamShift->StartTracking();
            }
            else if (LOWORD(wParam) == IDC_STOP)
            {
                m_pCamShift->StopTracking();
            }
            break;
    }
    return CBasePropertyPage::OnReceiveMessage(hwnd,uMsg,wParam,lParam);
} // OnReceiveMessage


//
// OnConnect
//
// Called when the property page connects to a filter
//
HRESULT CCamShiftProperties::OnConnect(IUnknown *pUnknown)
{
    ASSERT(m_pCamShift == NULL);

    HRESULT hr = pUnknown->QueryInterface(IID_ICamShift, (void **) &m_pCamShift);
    if (FAILED(hr)) {
        return E_NOINTERFACE;
    }

    ASSERT(m_pCamShift);
    m_pCamShift->GetParams(&m_params);
   
    return NOERROR;

} // OnConnect


//
// OnDisconnect
//
// Called when we're disconnected from a filter
//
HRESULT CCamShiftProperties::OnDisconnect()
{
    // Release of Interface after setting the appropriate contrast value

    if (m_pCamShift == NULL) {
        return E_UNEXPECTED;
    }
    OnApplyChanges();
    m_pCamShift->Release();
    m_pCamShift = NULL;
    return NOERROR;

} // OnDisconnect


//
// OnDeactivate
//
// We are being deactivated
//
HRESULT CCamShiftProperties::OnDeactivate(void)
{
    return NOERROR;

} // OnDeactivate


//
// OnApplyChanges
//
// Changes made should be kept. Change the  variable
//
HRESULT CCamShiftProperties::OnApplyChanges()
{
    ReadParamsFromControls();
    m_pCamShift->SetParams(&m_params);

    m_bDirty = FALSE;
    return(NOERROR);

} // OnApplyChanges

/* End of file. */
