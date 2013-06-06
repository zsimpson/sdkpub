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

#define WM_GRAPHNOTIFY  WM_USER+13


#include <objbase.h>
#include <streams.h>
#include "iProxyTrans.h"
#include "ProxyTransuids.h"
#include "highgui.h"
#include "cvcamavi.h"

IPin* get_pin( IBaseFilter* pFilter, PIN_DIRECTION dir );
HWND _cvcamCreateWindow();

const int FRAMES_FORMAT = 0;
const int TIME_FORMAT = 1;


cvcamSourceFile::cvcamSourceFile(const char* file , void (*callback)(void*) ):
Iusecom(),
m_pGraph(NULL),
m_pMediaControl(NULL),
m_pEvent(NULL),
m_pVideoWindow(NULL),
m_pPin(NULL),
m_pBasicVideo(NULL),
m_pSFilter(NULL),
m_pProxyTrans(NULL),
m_pSourceOut(NULL),
m_pProxyIn(NULL),
m_pProxyOut(NULL),
m_pEnumPins(NULL),
m_pProxyBase(NULL),
m_file(),
m_pcallback(NULL),
m_width(0),
m_height(0),
IsValid(true),
m_hr(),
m_hWnd(NULL),
m_pMediaSeeking(NULL)

{
    try
    {
    
    //Get the file
    if (file) 
    {
        m_file = file;
    }
    else
    {
        char path[256];
        memset(path,0,256);

        OPENFILENAME fn;
        
        fn.lStructSize = sizeof(OPENFILENAME);
        fn.hwndOwner = NULL;
        fn.lpstrFilter = NULL;
        fn.lpstrFile = path;
        fn.nMaxFile = 256;
        fn.lpstrFileTitle = NULL;
        fn.lpstrInitialDir = NULL;
        fn.lpstrTitle = NULL;
        fn.Flags = NULL;
        fn.lpstrDefExt = "avi";
        fn.hInstance = DLLhinst;
        fn.lpfnHook = NULL;
        fn.lpstrCustomFilter = NULL;
        fn.lCustData = NULL;
        
        
        if(!GetOpenFileName(&fn))
            throw 1;

        m_file = path;
       
    }//else after if(file)

    // Create the filter graph manager and query for interfaces.
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
        IID_IGraphBuilder, (void **)&m_pGraph);
    
    // Build the graph.
    wchar_t wpath[256];
    mbstowcs(wpath, m_file.c_str(), strlen(m_file.c_str())+1);
    
    
    m_hr = m_pGraph->AddSourceFilter(wpath,L"source",&m_pSFilter);
    
    
    // Create a proxy transform filter 
    if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
        IID_IProxyTransform, (void**)&m_pProxyTrans)))
    {
        throw 1;
    }
    
    //set callback
    m_hr = m_pProxyTrans->set_transform((void(__cdecl*)(void*))m_pcallback, 0);
    
    //Get Source output pin
    m_hr = m_pSFilter->EnumPins(&m_pEnumPins);
    
    unsigned long fetched(0);
    m_hr = m_pEnumPins->Next(1,&m_pSourceOut,&fetched);
    if(!fetched)
        throw 1 ;
    
    m_pEnumPins = NULL;
    
    //Put ProxyTrans into graph
    m_hr = m_pProxyTrans->QueryInterface(IID_IBaseFilter,(void**)&m_pProxyBase);
    m_hr = m_pGraph->AddFilter(m_pProxyBase.value(),L"proxy");
    
    //Get ProxyTrans Pins
    m_pProxyIn = get_pin( m_pProxyBase.value(), PINDIR_INPUT );
    m_pProxyOut= get_pin( m_pProxyBase.value(), PINDIR_OUTPUT );
    
    m_hr = m_pGraph->Connect(m_pSourceOut.value(),m_pProxyIn.value());
    
    m_hr = m_pGraph->Render(m_pProxyOut.value());
    
    
    
    //Gain additional interfaces
    m_hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl);
    m_hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (void **)&m_pEvent);
    m_hr = m_pGraph->QueryInterface(IID_IVideoWindow, (void **)&m_pVideoWindow);
    m_hr = m_pGraph->QueryInterface(IID_IMediaSeeking, (void**)&m_pMediaSeeking);
    
    if(!m_pMediaControl.is_valid() ||!m_pEvent.is_valid() ||!m_pVideoWindow.is_valid())
        throw 1;
    


}//try
catch (...) 
{
    IsValid = false;
    return;
}//catch




}//cvcamSourceFile()


bool cvcamSourceFile::IsRunning()
{
    long evCode;
    
    HRESULT hr = m_pEvent->WaitForCompletion(0, &evCode);
    
    if(SUCCEEDED(hr))
    {
        if(!evCode)
            return true;
    }
    
    return false;
}

HRESULT cvcamSourceFile::SetWindow(const HWND window)
{
    
    
    if(IsRunning())
        return E_FAIL;
        
    m_hWnd = window;
    
    if (!m_hWnd) 
    {
        m_hWnd = _cvcamCreateWindow();  
    }

    return S_OK;
    
   
}

HRESULT cvcamSourceFile::Start()
{
    try
    {
    
    if (IsRunning())
    {
        return NOERROR;
    }

    //Set up the window
    
    m_hr = m_pVideoWindow->put_Owner((OAHWND)m_hWnd);
    long flags;
    m_hr = m_pEvent->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
    m_hr = m_pEvent->SetNotifyFlags(0x00);
    m_hr = m_pEvent->CancelDefaultHandling(EC_COMPLETE);
    m_hr = m_pVideoWindow->get_WindowStyle(&flags);
    m_hr = m_pVideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
    m_hr = m_pVideoWindow->put_MessageDrain((OAHWND)m_hWnd);

    // Get the rectangle dimensions and resize the client window
    m_hr = m_pGraph->QueryInterface(IID_IBasicVideo,(void**)&m_pBasicVideo);
     
    long left, top, w, h;
    m_pBasicVideo->GetSourcePosition(&left, &top,&w,&h);
    m_pBasicVideo->SetDestinationPosition(0, 0, m_width?m_width:w, m_height?m_height:h);
    m_pVideoWindow->SetWindowPosition(0,0,m_width?m_width:w,m_height?m_height:h);
    const char* name = get_name_byhwnd(m_hWnd);
    resize(name, m_width?m_width:w, m_height?m_height:h);
        
        
    
    // Run the graph.
    m_hr = m_pMediaControl->Run();
    
    return S_OK;
    
    }//try
    catch(HrExeption exp)
    {
        return exp.hr;
    }//catch

}

HRESULT cvcamSourceFile::Stop()
{
    if( m_pMediaControl.is_valid() )
    {
        OAFilterState fs;
        m_pMediaControl->GetState(0,&fs);
        if(fs == State_Stopped)
            return NOERROR;
        
        
        m_pMediaControl->StopWhenReady();
        
        
        
        if(m_pVideoWindow.is_valid() )
        {
            m_pVideoWindow->put_Visible(OAFALSE);
            m_pVideoWindow->put_Owner(NULL);
            m_pVideoWindow->put_MessageDrain(0);
        }
    }           
return S_OK;
}

HRESULT cvcamSourceFile::Pause()
{
    if( m_pMediaControl.is_valid() )
    {
        OAFilterState fs;
        m_pMediaControl->GetState(0,&fs);
        if(fs == State_Stopped)
            return S_OK;
        m_pMediaControl->Pause();
    }	
    
    
    
    return S_OK;
}

HRESULT cvcamSourceFile::Resume()
{
    if( m_pMediaControl.is_valid() )
    {
        OAFilterState fs;
        m_pMediaControl->GetState(0,&fs);
        if(fs == State_Stopped)
            return S_OK;
        
        m_pMediaControl->Run();
    }
    
    
    return S_OK;
}

HRESULT cvcamSourceFile::SetCallBack(void (__cdecl *callback)(void *))
{
    if(IsRunning())
        return E_FAIL;

    m_pcallback = callback;
    
    m_pProxyTrans->set_transform((void(__cdecl*)(void*))m_pcallback, 0);

    return S_OK;
}

HRESULT cvcamSourceFile::SetHeight(const int height)
{
    m_height = height;

    return S_OK;
}

HRESULT cvcamSourceFile::SetWidth(const int width)
{
    m_width = width;

    return S_OK;
}

HRESULT cvcamSourceFile::WaitForCompletion()
{
    long evCode;

    return m_pEvent->WaitForCompletion(INFINITE, &evCode);

}

HRESULT cvcamSourceFile::SetTimeFormat(const int format)
{
    if (format == FRAMES_FORMAT) 
    {
        return m_pMediaSeeking->SetTimeFormat(&TIME_FORMAT_FRAME );
    }else
    if (format == TIME_FORMAT) 
        
    {
        
        return m_pMediaSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
    }else
        return E_FAIL;
}

HRESULT cvcamSourceFile::GetDuration(LONGLONG *pDuration)
{
    return m_pMediaSeeking->GetDuration(pDuration);
}

HRESULT cvcamSourceFile::GetCurrentPosition(LONGLONG *pCurrent)
{
    
    return m_pMediaSeeking->GetCurrentPosition(pCurrent);
}

HRESULT cvcamSourceFile::SetPosition(LONGLONG *pCurrent)
{

    return m_pMediaSeeking->SetPositions(pCurrent,AM_SEEKING_AbsolutePositioning,NULL,
                                                            AM_SEEKING_NoPositioning);
}
