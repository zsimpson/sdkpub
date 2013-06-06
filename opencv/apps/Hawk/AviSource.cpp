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
//M*/// AviSource.cpp
#include "stdafx.h"
#include "Hawk.h"
#include <mmsystem.h>
#include <streams.h>
#include "convert.h"
extern "C"
{
#include <HighGUI.h>
}

#include <iProxyTrans.h>
#include <ProxyTransuids.h>

#define SafeRelease(p) { if( (p) != 0 ) { (p)->Release(); (p)= 0; } }
#define WM_GRAPHNOTIFY  WM_USER+13

IPin* get_pin( IBaseFilter* pFilter, PIN_DIRECTION dir );

template<> void AFXAPI DestructElements<IUnknown*> (IUnknown** pElements, int nCount);

void AFXAPI DestructElements(IUnknown** elements, int count)
{
    for(int i = 0; i < count; i++)
    {
        SafeRelease(elements[i]);
    }
};

int play_avi(char* filename, char* windowname, void (*callback)(IPLIMAGE))
{
    if(!filename || !windowname)
    {
        return -1;
    }

    // get the full file path
    char drive[_MAX_DRIVE];
    char path[_MAX_DIR];
    char fpath[_MAX_PATH];
    char fname[_MAX_FNAME];
    char fext[_MAX_EXT];
    char fullname[_MAX_PATH];
    LPSTR f;
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    const CStringArray& search_path = app->GetVideoPath();

    _splitpath(filename, drive, path, fname, fext);
    strcpy(fpath, drive);
    strcat(fpath, path);
    DWORD found = SearchPath(fpath, fname, fext, _MAX_PATH, fullname, &f);
    if(!found)
    {
        found = SearchPath(NULL, fname, fext, _MAX_PATH, fullname, &f);
        if(!found)
        {
            for(int i = 0; i < search_path.GetSize(); i++)
            {
                if(found = SearchPath(search_path[i], fname, fext, _MAX_PATH, fullname, &f))
                {
                    break;
                }
            }

            if(!found)
            {
                return -1;
            }
        }
    }

    HWND hwnd;
    HRESULT hres;
    IGraphBuilder *pigb  = NULL;
    IMediaControl *pimc  = NULL;
    IMediaEventEx *pimex = NULL;
    IVideoWindow  *pivw  = NULL;
    IProxyTransform* pipt = NULL;
    IBaseFilter* pias = NULL;
    CArray<IUnknown*, IUnknown*> interfaces;

    // Initialize COM
    if(FAILED(CoInitialize(0)))
    {
        return -1;
    };


    if(FAILED(CoCreateInstance(CLSID_FilterGraph,
    NULL,
    CLSCTX_INPROC_SERVER,
    IID_IGraphBuilder,
    (void **)&pigb)))
    {
        return -1;
    }
    
    pigb->QueryInterface(IID_IMediaControl, (void **)&pimc);
    pigb->QueryInterface(IID_IMediaEventEx, (void **)&pimex);
    pigb->QueryInterface(IID_IVideoWindow, (void **)&pivw);
    ASSERT(pimc);
    ASSERT(pimex);
    ASSERT(pivw);

    interfaces.Add(pigb);
    interfaces.Add(pimc);
    interfaces.Add(pimex);
    interfaces.Add(pivw);

    BSTR wstr = CString(fullname).AllocSysString();
    hres = pigb->RenderFile(wstr, 0);
    ::SysFreeString(wstr);
    if(FAILED(hres))
    {
        return -1;
    }

    // Find the last filter:
    IEnumFilters* pief = NULL;
    hres = pigb->EnumFilters(&pief);
    ASSERT(SUCCEEDED(hres) && pief);
    interfaces.Add(pief);
    // Find the last filter
    IBaseFilter* pRenderer = NULL;
    IBaseFilter* pRenderSource = NULL;
    IBaseFilter* pibf = NULL;
    IPin* pSourceOut = NULL;
    IPin* pRenderIn = NULL;

    ULONG cf = 1;
    // The filter without the output pin should be a renderer, 
    // and the filter before the renderer - the source of images...
    while(cf)
    {
        pief->Next(1, &pibf, &cf);
        IPin* pOut = get_pin(pibf, PINDIR_OUTPUT);
        if(!pOut)
        {
            // This is the renderer...
            pRenderIn = get_pin(pibf, PINDIR_INPUT);
            pRenderIn->ConnectedTo(&pSourceOut);
            ASSERT(pSourceOut);

            SafeRelease(pibf);
            interfaces.Add(pRenderIn);
            interfaces.Add(pSourceOut);
            break;
        }

        SafeRelease(pibf);
    }

    if(!pSourceOut || !pRenderIn)
    {
        return -1;
    }

    // Create a proxy transform filter
    if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
				IID_IProxyTransform, (void**)&pipt)) || !pipt)
    {
        return -1;
    }

    interfaces.Add(pipt);

    IBaseFilter* pProxyFilter = NULL;
    pipt->QueryInterface(IID_IBaseFilter, (void**)&pProxyFilter);
    ASSERT(pProxyFilter);
    IPin* pProxyOut = get_pin(pProxyFilter, PINDIR_OUTPUT);
    IPin* pProxyIn = get_pin(pProxyFilter, PINDIR_INPUT);
    ASSERT(pProxyOut && pProxyIn);

    interfaces.Add(pProxyFilter);
    interfaces.Add(pProxyOut);
    interfaces.Add(pProxyIn);

    // Set the proxy callback
    pipt->set_transform((void(*)(void*))callback, 0);

    // Add the proxy transform filter to the graph...
    hres = pigb->AddFilter(pProxyFilter, L"Proxy Transform");
    ASSERT(SUCCEEDED(hres));

    // Insert the proxy transfor filter...
    hres = pigb->Disconnect(pSourceOut);
    ASSERT(SUCCEEDED(hres));
    hres = pigb->Disconnect(pRenderIn);
    ASSERT(SUCCEEDED(hres));

    hres = pigb->Connect(pSourceOut, pProxyIn);
    ASSERT(SUCCEEDED(hres));
    hres = pigb->Connect(pProxyOut, pRenderIn);
    ASSERT(SUCCEEDED(hres));
    hres = pigb->Connect(pSourceOut, pProxyIn);
    ASSERT(SUCCEEDED(hres));

    BOOL needDestroy = FALSE;
    if(windowname)
    {
        // Find/create and attach the HighGUI window to the DS renderer
        hwnd = get_hwnd_byname(windowname);
        if(!hwnd)
        {
            int error = named_window((char*)windowname, 0);
            if(error == HG_INITFAILED)
            {
#ifdef _DEBUG
                CString str = "Can't initialize graphic library. \nPossible can't find cvlgrfmtsd.dll";
#else
                CString str = "Can't initialize graphic library. \nPossible can't find cvlgrfmts.dll";
#endif // _DEBUG
                AfxMessageBox(LPCTSTR(str));
                return -1;
            }
            hwnd = get_hwnd_byname(windowname);
            needDestroy = TRUE;
        }

        pimex->SetNotifyWindow((OAHWND)hwnd, WM_GRAPHNOTIFY, 0);
        pimex->SetNotifyFlags(0x00);
        pimex->CancelDefaultHandling(EC_COMPLETE);

        pivw->put_Owner((OAHWND)hwnd);
    	long flags;
    	pivw->get_WindowStyle(&flags);
        pivw->put_WindowStyle( flags &(~WS_CAPTION) | WS_CHILD/*|WS_CLIPSIBLINGS|WS_CLIPCHILDREN*/);
        pivw->put_MessageDrain((OAHWND)hwnd);
        CRect rc;
        ::GetClientRect(hwnd, &rc);
        pivw->SetWindowPosition( rc.left, rc.top, rc.right, rc.bottom );
    }
    else
    {
        pivw->put_WindowState(SW_HIDE);
        pivw->put_AutoShow(OAFALSE);
    }

    pimc->Run();

    // Wait for operation completion...
    while(1)
    {
        long evCode;
        MSG message;
        GetMessage(&message, NULL, 0, 0);
        if(message.message == WM_GRAPHNOTIFY)
        {
            long param1, param2;
            // Check for completion:
            hres = pimex->GetEvent(&evCode, &param1, &param2, 0);
            pimex->FreeEventParams(evCode, param1, param2);
            if(evCode == EC_COMPLETE)
            {
                break;
            }
            evCode = 0;
            hres = pimex->WaitForCompletion(0, &evCode);
//            if(hres == S_OK)
//            {
//                break;
//            }
//            OAFilterState state;
//            hres = pimc->GetState(INFINITE, &state);
            
        }

        TranslateMessage(&message);
        DispatchMessage(&message);

        if(!get_hwnd_byname(windowname))
        {
            // The avi window has been destroyed...
            OAFilterState state;
            hres = pimc->GetState(INFINITE, &state);
            hres = pimc->Pause();
            hres = pimc->GetState(INFINITE, &state);
            hres = pimc->Stop();
            hres = pimc->GetState(INFINITE, &state);
            ASSERT(state == State_Stopped);
            break;
        }
    }

    if(needDestroy)
    {
        destroy_window(windowname);
    }

    return 0;
}