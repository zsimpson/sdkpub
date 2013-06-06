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

#ifdef __cplusplus

class ProxyTransform : public CTransInPlaceFilter,
          public IProxyTransform,
          public ISpecifyPropertyPages
{

public:
    
    // Constructor
    ProxyTransform ( TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    // Reveals ProxyTransform & ISpecifyPropertyPages
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);
    HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
    HRESULT DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties);
    HRESULT CheckTransform(const CMediaType *mtIn,const CMediaType *mtOut);

    // IProxyTransform methods

    STDMETHODIMP set_transform(void (__cdecl *transform)(void*),
                               void (__cdecl **old_transform)(void*));
    STDMETHODIMP SetCallBack(void (__cdecl *transform)(void*),
                             void (__cdecl **old_transform)(void*));
    STDMETHODIMP CreateCamera(void);
    STDMETHODIMP CreateFilterGraph(void);
    STDMETHODIMP InitGraph(void);

    STDMETHODIMP StopGraph(void);
    STDMETHODIMP StartGraph(HWND wnd);
  
    STDMETHODIMP SetVideoWindowSize(HWND hWnd);
    STDMETHODIMP GetVideoWindowSize(HWND hWnd, RECT* rect);
    // ISpecifyPropertyPages method

    STDMETHODIMP GetPages(CAUUID *pPages);

private:
      

    // Non interface locking critical section
    CCritSec         m_ProxyTransformLock;
    void             (*m_transform)(void*); 
    IBaseFilter*     m_SourceFilter;
    IProxyTransform* m_ProxyTrans;
    IGraphBuilder*   m_GraphBuilder;
    IMediaControl*   m_MediaControl;
    IVideoWindow*    m_VideoWindow;
    IFilterGraph*    m_FilterGraph;
    IMediaEventEx*   m_MediaEventEx;
    BOOL             m_DSOn;
    BOOL             m_isDSRunning;

}; // ProxyTransform

#ifdef CVCAM_EXPORTS
    #define CVCAMAPI(type,name,arg) extern "C" __declspec(dllexport) type name arg;
#else
    #define CVCAMAPI(type,name,arg) extern "C" __declspec(dllimport) type name arg;
#endif

#else
#ifdef CVCAM_EXPORTS
    #define CVCAMAPI(type,name,arg) __declspec(dllexport) type name arg;
#else
    #define CVCAMAPI(type,name,arg) __declspec(dllimport) type name arg;
#endif

#endif //__cplusplus

CVCAMAPI(int, Initialize, ())
CVCAMAPI(int, UnInitialize, ())
CVCAMAPI(int, RunCamera, (int camera, HWND wnd))
CVCAMAPI(int, StopCamera, (int camera))
CVCAMAPI(int, SetCallBack, ( int camera,
                             void (*transform)(void*),
                             void (**old_transform)(void*)))
