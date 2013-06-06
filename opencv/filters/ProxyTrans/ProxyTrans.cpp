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
#include <windows.h>
//#include <afxwin.h>
#include <streams.h>
#include <initguid.h>
#include <olectl.h>
//#include <assert.h>
#if (1100 > _MSC_VER)
#include <olectlid.h>
#endif
//#include "IppCV.h"
#include "CV.h"
#include "iProxyTrans.h"
#include "ProxyTransprop.h"
#include "ProxyTrans.h"
#include "ProxyTransuids.h"

#define SafeRelease(p) { if( (p) != 0 ) { (p)->Release(); (p)= 0; } }
#define WM_GRAPHNOTIFY  WM_USER+13

//
// TODO: // Place the filter description here
//

// Files
//
// ProxyTransprop.cpp         Property page implementation
// ProxyTransprop.h           Class definition for the property page
// ProxyTransprop.rc          Dialog box template for the property page
// ProxyTrans.cpp             Main filter class implementation
// ProxyTrans.def             What APIs we import and export from this DLL
// ProxyTrans.h               Class definition for the filter
// ProxyTransuids.h           The filter CLSIDs
// iProxyTrans.h              Defines the custom filter interface
// resource.h               Resource file


// setup data
const AMOVIESETUP_MEDIATYPE sudPinTypes =
{
    &MEDIATYPE_Video,       // Major type
    &MEDIASUBTYPE_NULL      // Minor type
};

const AMOVIESETUP_PIN psudPins[] =
{
    {
        L"Input",           // String pin name
        FALSE,              // Is it rendered
        FALSE,              // Is it an output
        FALSE,              // Allowed none
        FALSE,              // Allowed many
        &CLSID_NULL,        // Connects to filter
        L"Output",          // Connects to pin
        1,                  // Number of types
        &sudPinTypes },     // The pin details
      { L"Output",          // String pin name
        FALSE,              // Is it rendered
        TRUE,               // Is it an output
        FALSE,              // Allowed none
        FALSE,              // Allowed many
        &CLSID_NULL,        // Connects to filter
        L"Input",           // Connects to pin
        1,                  // Number of types
        &sudPinTypes        // The pin details
    }
};


const AMOVIESETUP_FILTER sudProxyTransform =
{
    &CLSID_ProxyTransform,        // Filter CLSID
    L"ProxyTrans",                    // Filter name
    MERIT_DO_NOT_USE,               // Its merit
    2,                              // Number of pins
    psudPins                        // Pin details
};


// List of class IDs and creator functions for the class factory. This
// provides the link between the OLE entry point in the DLL and an object
// being created. The class factory will call the static CreateInstance

CFactoryTemplate g_Templates[2] = {

    { L"ProxyTrans"
    , &CLSID_ProxyTransform
    , ProxyTransform::CreateInstance
    , NULL
    , &sudProxyTransform }
  ,
    { L"ProxyTrans Property Page"
    , &CLSID_ProxyTransformPropertyPage
    , ProxyTransformProperties::CreateInstance }
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);



//
// Constructor
//
ProxyTransform::ProxyTransform(TCHAR *tszName,LPUNKNOWN punk,HRESULT *phr) :
    CTransInPlaceFilter(tszName, punk, CLSID_ProxyTransform,phr),
    m_transform(NULL),
    m_SourceFilter(0), m_FilterGraph(0), m_GraphBuilder(0),
    m_MediaControl(0), m_MediaEventEx(0), m_VideoWindow(0), m_ProxyTrans(0),
    m_isDSRunning(0)
{
    ASSERT(tszName);
    ASSERT(phr);
} // ProxyTransform


//
// CreateInstance
//
// Provide the way for COM to create a ProxyTransform object
//
CUnknown * WINAPI ProxyTransform::CreateInstance(LPUNKNOWN punk, HRESULT *phr) {

    ProxyTransform *pNewObject = new ProxyTransform("ProxyTrans", punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;

} // CreateInstance


//
// NonDelegatingQueryInterface
//
// Reveals IProxyTransform and ISpecifyPropertyPages
//
STDMETHODIMP ProxyTransform::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
    CheckPointer(ppv,E_POINTER);

    if (riid == IID_IProxyTransform) {
        return GetInterface((IProxyTransform *) this, ppv);
    } else if (riid == IID_ISpecifyPropertyPages) {
        return GetInterface((ISpecifyPropertyPages *) this, ppv);
    } else {
        return CTransInPlaceFilter::NonDelegatingQueryInterface(riid, ppv);
    }

} // NonDelegatingQueryInterface


//
// Transform
// Transform the  sample 'in place'
//
HRESULT ProxyTransform::Transform(IMediaSample *pMediaSample)
{
    BYTE*    pData;
    IplImage image;
    
    pMediaSample->GetPointer(&pData);
    
    AM_MEDIA_TYPE* pType = &m_pInput->CurrentMediaType();
    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) pType->pbFormat;
    
    if(pvi->bmiHeader.biBitCount != 24)
    {
        return NOERROR;
    }

    // Get the image properties from the BITMAPINFOHEADER
    int cxImage    = pvi->bmiHeader.biWidth;
    int cyImage    = abs(pvi->bmiHeader.biHeight);
    int stride     = (cxImage * sizeof( RGBTRIPLE ) + 3) & -4;

    // Initialize image header
    cvInitImageHeader( &image, cvSize(cxImage, cyImage), 8, 3, IPL_ORIGIN_BL, 4, 1 );
    image.widthStep = stride;
    // Copy the data
/*    if(1/*pvi->bmiHeader.biHeight < 0)
    {*/
        cvSetImageData( &image, pData, stride );
/*    }
    else
    {
        int i;
        image.imageData = (char*)malloc(image.widthStep*cyImage);
        for(i = 0; i < cyImage; i++)
            memcpy(image.imageData + i*image.widthStep, pData + (cyImage - 1 - i)*stride, cxImage*3);
    }*/
    
    if(m_transform)
    {
        (*m_transform)(&image);
    }

/*    if(0/*pvi->bmiHeader.biHeight > 0)
    {
        free(image.imageData);
    }*/
    
    return NOERROR;
} // Transform


//
// CheckInputType
//
// Check the input type is OK, return an error otherwise
//
HRESULT ProxyTransform::CheckInputType(const CMediaType *mtIn)
{
    // Check this is a VIDEOINFO type

    if (*mtIn->FormatType() != FORMAT_VideoInfo)
    {
        return E_INVALIDARG;
    }

    VIDEOINFO* vi = (VIDEOINFO*)mtIn->Format();
    if(vi->bmiHeader.biBitCount != 24)
    {
        return E_INVALIDARG;
    }


    return NOERROR;

} // CheckInputType



// CheckTransform
//
// To be able to transform the formats must be identical
//

HRESULT ProxyTransform::CheckTransform(const CMediaType *mtIn,const CMediaType *mtOut)
{
    HRESULT hr;
    if (FAILED(hr = CheckInputType(mtIn))) {
    return hr;
    }

    // format must be a VIDEOINFOHEADER
    if (*mtOut->FormatType() != FORMAT_VideoInfo) {
    return E_INVALIDARG;
    }
    
    // formats must be big enough 
    if (mtIn->FormatLength() < sizeof(VIDEOINFOHEADER) ||
    mtOut->FormatLength() < sizeof(VIDEOINFOHEADER))
    return E_INVALIDARG;
    
    VIDEOINFO *pInput = (VIDEOINFO *) mtIn->Format();
    VIDEOINFO *pOutput = (VIDEOINFO *) mtOut->Format();
    if (memcmp(&pInput->bmiHeader,&pOutput->bmiHeader,sizeof(BITMAPINFOHEADER)) == 0) {
    return NOERROR;
    }

    return E_INVALIDARG;
} // CheckTransform


//
// DecideBufferSize
//
// Tell the output pin's allocator what size buffers we
// require. Can only do this when the input is connected
//
HRESULT ProxyTransform::DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
{
    // Is the input pin connected

    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    ASSERT(pAlloc);
    ASSERT(pProperties);
    return NOERROR;

} // DecideBufferSize


//
// GetMediaType
//
// I support one type, namely the type of the input pin
// We must be connected to support the single output type
//
HRESULT ProxyTransform::GetMediaType(int iPosition, CMediaType *pMediaType)
{
    // Is the input pin connected

    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    // This should never happen

    if (iPosition < 0) {
        return E_INVALIDARG;
    }

    // Do we have more items to offer

    if (iPosition > 0) {
        return VFW_S_NO_MORE_ITEMS;
    }

    *pMediaType = m_pInput->CurrentMediaType();
    return NOERROR;

} // GetMediaType

//
// get_Param
//
// Return the current Param
//
//DEL STDMETHODIMP ProxyTransform::get_Param(long* lParam)
//DEL {
//DEL     CAutoLock cAutoLock(&m_ProxyTransformLock);
//DEL     *lParam= m_lParam;
//DEL     return NOERROR;
//DEL } // get_Param

//
// set_Param
//
// Sets the Param
//
STDMETHODIMP ProxyTransform::set_transform(void (__cdecl *transform)(void*),
                                           void (__cdecl **old_transform)(void*))
{
    CAutoLock cAutoLock(&m_ProxyTransformLock);
    if(old_transform) *old_transform = m_transform;
    m_transform = transform;
    return NOERROR;
} // set_transform


STDMETHODIMP ProxyTransform::SetCallBack(void (__cdecl *transform)(void*),
                                         void (__cdecl **old_transform)(void*))
{
    return set_transform(transform, old_transform);
} // set_transform


STDMETHODIMP ProxyTransform::CreateCamera()
{
    ICreateDevEnum* pCreateDevEnum = 0;
    IEnumMoniker*   pEnumMon = 0;
    IMoniker*       pMon = 0;
    ULONG           cFetched = 0;
    
    SafeRelease( m_SourceFilter );
    
    if(FAILED(CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                      IID_ICreateDevEnum, (void**)&pCreateDevEnum )))
    {
        return FALSE;
    }
    
    ASSERT(pCreateDevEnum);
    /* Create capture device */
    if(FAILED(pCreateDevEnum->CreateClassEnumerator( 
                CLSID_VideoInputDeviceCategory, &pEnumMon, 0)) || !pEnumMon)
    {
        SafeRelease(pCreateDevEnum);
        return FALSE;
    }

    ASSERT(pEnumMon);
    if(SUCCEEDED( pEnumMon->Next(1, &pMon, &cFetched)) && cFetched == 1 && pMon)
    {
        ASSERT(pMon);
        pMon->BindToObject(0, 0, IID_IBaseFilter, (void **)&m_SourceFilter );
        if(!m_SourceFilter)
        {
            SafeRelease(pCreateDevEnum);
            SafeRelease(pEnumMon);
            return FALSE;
        }
        FILTER_INFO info;
        m_SourceFilter->QueryFilterInfo(&info);
    }
    else
    {
        SafeRelease(pCreateDevEnum);
        SafeRelease(pEnumMon);
        return FALSE;
    }

    // Create a proxy transform filter to enable scripts process images
    if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IProxyTransform, (void**)&m_ProxyTrans)))
    {
        SafeRelease(pCreateDevEnum);
        SafeRelease(pEnumMon);
        SafeRelease(m_SourceFilter);
        return FALSE;
    }


    SafeRelease( pMon );
    SafeRelease( pEnumMon );
    SafeRelease( pCreateDevEnum );

    return TRUE;
}


static IPin* get_pin( IBaseFilter* pFilter, PIN_DIRECTION dir )
{
    IEnumPins*  pEnumPins = 0;
    IPin*       pPin = 0;

    if( pFilter )
    {
        pFilter->EnumPins( &pEnumPins );
        if( pEnumPins != 0 )
        {
            for(;;)
            {
                ULONG  cFetched = 0;
                PIN_DIRECTION pinDir = PIN_DIRECTION(-1); 
                pPin = 0;

                pEnumPins->Next( 1, &pPin, &cFetched );
                if( cFetched == 1 && pPin != 0 )
                {
                    pPin->QueryDirection( &pinDir );
                    if( pinDir == dir ) break;
                    pPin->Release();
                }
                else if(cFetched == 0)
                {
                    return 0;
                }
            }
            pEnumPins->Release();
        }
    }

    return pPin;
}


STDMETHODIMP ProxyTransform::CreateFilterGraph()
{
    
    if(FAILED(CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                      IID_IGraphBuilder, (void **)&m_GraphBuilder )))
    {
        SafeRelease(m_GraphBuilder);
        return FALSE;
    }

    ASSERT(m_GraphBuilder);
    m_GraphBuilder->QueryInterface(IID_IMediaControl,(void**)&m_MediaControl);
    m_GraphBuilder->QueryInterface(IID_IMediaEventEx,(void**)&m_MediaEventEx);
    m_GraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_VideoWindow);
    m_GraphBuilder->QueryInterface(IID_IFilterGraph, (void**)&m_FilterGraph);

    IBaseFilter* pProxyTrans = 0;
    m_ProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pProxyTrans);

/*    if( m_MediaEventEx )
    {
        // Have the graph signal event via window callbacks for performance
        m_MediaEventEx->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
    }*/

    /* link filters */
    if( m_FilterGraph )
    {
        HRESULT hr;
        IPin* pSourceOut    = get_pin( m_SourceFilter, PINDIR_OUTPUT );

        IPin* pProxyTransIn     = get_pin( pProxyTrans, PINDIR_INPUT );
        IPin* pProxyTransOut    = get_pin( pProxyTrans, PINDIR_OUTPUT );
    
        if( pSourceOut && pProxyTransIn && pProxyTransOut )
        {
            hr = m_FilterGraph->AddFilter( m_SourceFilter, L"Video Source" );
            hr = m_FilterGraph->AddFilter( pProxyTrans, L"Script processing");
            hr = m_GraphBuilder->Connect(pSourceOut, pProxyTransIn);
            hr = m_GraphBuilder->Render( pProxyTransOut );
            AM_MEDIA_TYPE amt;
            pSourceOut->ConnectionMediaType(&amt);
            pProxyTransOut->ConnectionMediaType(&amt);
            VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)amt.pbFormat;
            if(!vih || vih->bmiHeader.biBitCount != 24)
            {
                SafeRelease( pSourceOut );
                SafeRelease( pProxyTransIn );
                SafeRelease( pProxyTransOut );
                return FALSE;
            }
        }

        SafeRelease( pSourceOut );
        SafeRelease( pProxyTransIn );
        SafeRelease( pProxyTransOut );
    }
    return TRUE;
}


STDMETHODIMP ProxyTransform::InitGraph()
{
    // Initialize DirectShow
    CoInitialize(0);
    if(CreateCamera() && CreateFilterGraph())
    {
        //Camera video source is available
        m_DSOn = TRUE;
    }
    else
    {
        m_DSOn = FALSE;
    }

    return NOERROR;
}


STDMETHODIMP ProxyTransform::StopGraph()
{
    if( m_MediaControl )
    {
        m_MediaControl->StopWhenReady();
        m_VideoWindow->put_Visible(OAFALSE);
        m_VideoWindow->put_Owner(NULL);
        m_VideoWindow->put_MessageDrain(0);
        m_isDSRunning = FALSE;
    }
    return NOERROR;
}

STDMETHODIMP ProxyTransform::StartGraph(HWND hWnd)
{
    if( m_MediaControl )
    {
        m_VideoWindow->put_Owner((OAHWND)hWnd);
        long flags;
        m_MediaEventEx->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
        m_MediaEventEx->SetNotifyFlags(0x00);
        m_MediaEventEx->CancelDefaultHandling(EC_COMPLETE);
        m_VideoWindow->get_WindowStyle(&flags);
        m_VideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
        m_VideoWindow->put_MessageDrain((OAHWND)hWnd);

        SetVideoWindowSize(hWnd); 
        m_MediaControl->Run();
        m_isDSRunning = TRUE;
    }
    return NOERROR;
}

STDMETHODIMP ProxyTransform::SetVideoWindowSize(HWND hWnd) 
{
    RECT rc;
    GetVideoWindowSize(hWnd, &rc);
    if( m_VideoWindow )
    {
        m_VideoWindow->SetWindowPosition( rc.left, rc.top, rc.right, rc.bottom );
    }
    return NOERROR;
}

STDMETHODIMP ProxyTransform::GetVideoWindowSize(HWND hWnd, RECT* rect) 
{
    RECT rc = {0, 0, 0, 0};
    if(hWnd)
    {
//        int width, height;
//        GetScaleFactor( width, height );

        ::GetClientRect( hWnd, &rc );

//        rc.right  = rc.right * width / 100;
//        rc.bottom = rc.bottom * height / 100;
    }
    *rect = rc;

    return NOERROR;
}


//
// set_Default
//
// Sets the Param to the Default Value
//
//DEL STDMETHODIMP ProxyTransform::set_Default()
//DEL {
//DEL     CAutoLock cAutoLock(&m_ProxyTransformLock);
//DEL     m_lParam=m_lDefault ;
//DEL     return NOERROR;
//DEL } // set_Default






//
// GetPages
//
// This is the sole member of ISpecifyPropertyPages
// Returns the clsid's of the property pages we support
//

STDMETHODIMP ProxyTransform::GetPages(CAUUID *pPages)
{
    pPages->cElems = 1;
    pPages->pElems = (GUID *) CoTaskMemAlloc(sizeof(GUID));
    if (pPages->pElems == NULL) {
        return E_OUTOFMEMORY;
    }
    *(pPages->pElems) = CLSID_ProxyTransformPropertyPage;
    return NOERROR;

} // GetPages



//
// DllRegisterServer
//
// Handle registration of this filter
//
STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2( TRUE );

} // DllRegisterServer


//
// DllUnregisterServer
//
STDAPI DllUnregisterServer()
{
   return AMovieDllRegisterServer2( FALSE );

} // DllUnregisterServer

#if 0
int GetCameraList(CvCamera** cams)
{
    UnInitialize();
    num = 0;

    for( int wIndex = 0; wIndex < 10; wIndex++ ) 
    {
        memset(&cameras[num].m_Caps, 0, sizeof(cameras[num].m_Caps));
        if( capGetDriverDescription( wIndex, cameras[num].m_DeviceName,
            sizeof (cameras[num].m_DeviceName),
            cameras[num].m_DeviceVersion, sizeof (cameras[num].m_DeviceVersion))) 
        {
            cameras[num].m_CaptureWindow = capCreateCaptureWindow( 0, 0, 0, 0, 1, 1, 0, 0);
            if( capDriverConnect(cameras[num].m_CaptureWindow, wIndex))
            {
                DWORD threadId;

                capPreviewRate(cameras[num].m_CaptureWindow, 66);  // rate, in milliseconds
                memset(&cameras[num].m_Caps, 0, sizeof(cameras[num].m_Caps));
                capDriverGetCaps( cameras[num].m_CaptureWindow,
                                  &cameras[num].m_Caps, sizeof(cameras[num].m_Caps));
                cameras[num].m_ThreadId = CreateThread( 0, 0, CameraCallBack,
                                                        (void*)num, CREATE_SUSPENDED,
                                                        &threadId );
                capSetUserData( cameras[num].m_CaptureWindow, (long)num );
                capSetCallbackOnFrame( cameras[num].m_CaptureWindow, FrameCallbackProc ); 

                num++;
            }
        }
    }

    if(cams) *cams = cameras;

    return num;
}


int GetVideoFormat(int camera, BITMAPINFO* video_format, int size)
{
    if(camera > num ||
       !cameras[camera].m_CaptureWindow ||
       !cameras[camera].m_Caps.fHasDlgVideoSource) return 0;
    return capGetVideoFormat(cameras[camera].m_CaptureWindow, video_format, size);
}


int SetVideoFormat(int camera, int width, int height, int format)
{
    if(camera > num) return 0;

    BITMAPINFO bmi;
    
    memset( &bmi.bmiHeader, 0, sizeof(bmi.bmiHeader));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biBitCount = (unsigned short)(format == 0 ? 24 : 12);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = format;
    bmi.bmiHeader.biSizeImage = ((bmi.bmiHeader.biWidth*
                                  bmi.bmiHeader.biBitCount/8 + 3)&-4)*
                                  bmi.bmiHeader.biHeight;
    memset( &bmi.bmiColors, 0, sizeof(bmi.bmiColors) );
    return capSetVideoFormat( cameras[camera].m_CaptureWindow, &bmi, sizeof(bmi)-4);
}
#endif

static IProxyTransform* ProxyTrans = 0;

int Initialize()
{
    CoInitialize(0);
    if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IProxyTransform, (void**)&ProxyTrans)))
        return 0;

    ProxyTrans->InitGraph();
    return 1;
}


int UnInitialize()
{
    return 1;
}

/*
int VideoFormatDlg(int camera)
{
    if(camera > num ||
       !cameras[camera].m_CaptureWindow ||
       !cameras[camera].m_Caps.fHasDlgVideoFormat) return 0;
    return capDlgVideoFormat( cameras[camera].m_CaptureWindow);
}


int VideoSourceDlg(int camera)
{
    if(camera > num ||
       !cameras[camera].m_CaptureWindow ||
       !cameras[camera].m_Caps.fHasDlgVideoSource) return 0;
    return capDlgVideoSource( cameras[camera].m_CaptureWindow);
}
*/

int RunCamera(int camera, HWND wnd)
{
    if(ProxyTrans) return ProxyTrans->StartGraph(wnd);
    else return 0;
}


int StopCamera(int camera)
{
    if(ProxyTrans) return ProxyTrans->StopGraph();
    else return 0;
}


int SetCallBack( int camera,
                 void (*transform)(void*),
                 void (**old_transform)(void*) )
{
    if(ProxyTrans) return ProxyTrans->SetCallBack(transform, old_transform);
    else return 0;
}
