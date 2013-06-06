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

#include "CV.h"
#include <windows.h>
#include <streams.h>
#include <INITGUID.H>
#include <stdlib.h>
#include "syncfilter.h"
#include "syncfilteruids.h"
#include "isyncfilter.h"


const AMOVIESETUP_MEDIATYPE sudPinTypes = 
                    
{

  &MEDIATYPE_Video             // major type
, &MEDIASUBTYPE_NULL           // minor type

};       



const AMOVIESETUP_PIN sudpPins[] =
{
    {
        L"Input1",          // String pin name
        FALSE,              // Is it rendered
        FALSE,              // Is it an output
        FALSE,              // Allowed none
        FALSE,              // Allowed many
        &CLSID_NULL,        // Connects to filter
        L"Output1",         // Connects to pin
        1,                  // Number of types
        &sudPinTypes        // The pin details 
    },
       
    {
        L"Input2",          // String pin name
        FALSE,              // Is it rendered
        FALSE,              // Is it an output
        FALSE,              // Allowed none
        FALSE,              // Allowed many
        &CLSID_NULL,        // Connects to filter
        L"Output2",         // Connects to pin
        1,                  // Number of types
        &sudPinTypes        // The pin details 
    },
    { 
        L"Output1",         // String pin name
        TRUE,               // Is it rendered
        TRUE,               // Is it an output
        FALSE,              // Allowed none
        FALSE,              // Allowed many
        &CLSID_NULL,        // Connects to filter
        L"Input1",          // Connects to pin
        1,                  // Number of types
        &sudPinTypes        // The pin details
    },
    
    { 
        L"Output2",         // String pin name
        TRUE,               // Is it rendered
        TRUE,               // Is it an output
        FALSE,              // Allowed none
        FALSE,              // Allowed many
        &CLSID_NULL,        // Connects to filter
        L"Input2",          // Connects to pin
        1,                  // Number of types
        &sudPinTypes        // The pin details
    }
};

const AMOVIESETUP_FILTER  sudMyFilter = 

{ 
    &CLSID_SyncFilter                 // clsID
    , L"VideoSync Filter for OpenCV"  // strName
    , MERIT_DO_NOT_USE                // dwMerit
    , 2                               // nPins
    , sudpPins                        // lpPin
};               


SyncFilter::SyncFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr)
    :m_csFilter(), CBaseFilter(tszName, punk, &m_csFilter, CLSID_SyncFilter), m_callback(NULL)
    

{ 
    m_ip1 = new cvSyncInputPin(NAME ( "1-st input pin"),
                               this,
                               &m_csFilter,
                               &m_hr,
                               L"Input1");
    
    m_ip2 = new cvSyncInputPin(NAME ( "2-nd input pin"),
                               this,
                               &m_csFilter,
                               &m_hr,
                               L"Input2");

    m_op1 = new cvSyncOutputPin(NAME("1-st output pin"),
                               this,
                               &m_csFilter,
                               &m_hr,
                               L"Output1");

    m_op2 = new cvSyncOutputPin(NAME("2-nd output pin"),
                               this,
                               &m_csFilter,
                               &m_hr,
                               L"Output2");

    m_ip1->m_op = m_op1;
    m_ip2->m_op = m_op2;

    m_op1->m_ip = m_ip1;
    m_op2->m_ip = m_ip2;



}


CUnknown * WINAPI SyncFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{

    SyncFilter *pNewObject = new SyncFilter(NAME("VideoSync Filter for OpenCV"), 
                                                  punk, phr );
    
    if (pNewObject == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    
    return pNewObject;
} 

int SyncFilter::GetPinCount(void)
{

    return 4;
}

CBasePin* SyncFilter::GetPin(int n)
{

    if(n==0)
        return m_ip1;
    if(n==1)
        return m_ip2;
    if(n==2)
        return m_op1;
    if(n==3)
        return m_op2;

    return NULL;

}

HRESULT cvSyncOutputPin::CheckMediaType(const CMediaType* pmt)
    {
        
        // Check this is a VIDEOINFO type

        if (*pmt->FormatType() != FORMAT_VideoInfo)
        {
            return E_INVALIDARG;
        }

        
        VIDEOINFO* vi = (VIDEOINFO*)pmt->Format();
        if(vi->bmiHeader.biBitCount != 24)
        {
            return E_INVALIDARG;
        }


        return NOERROR;

        
    };


CFactoryTemplate g_Templates[]=
        
{   
    { L"SyncFilter"          
            , &CLSID_SyncFilter
            , SyncFilter::CreateInstance  // function called by class factory
            , NULL
            , &sudMyFilter }     // address of the AMOVIESETUP_FILTER structure,
                                 //   or NULL if no structure exists
};

int g_cTemplates = sizeof(g_Templates)/sizeof(g_Templates[0]);

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
 

SyncFilter::~SyncFilter()
{
    delete m_ip1;
    delete m_ip2;
    delete m_op1;
    delete m_op2;
}

HRESULT cvSyncInputPin::BeginFlush()
{
    CAutoLock lock_it(m_pLock);
    HRESULT hr = NOERROR;
    hr = m_op->DeliverBeginFlush();
    if (FAILED(hr))
        return hr;

    return CBaseInputPin::BeginFlush();

}

HRESULT cvSyncInputPin::BreakConnect()
{
    
    // Release any allocator that we are holding
    
    if(m_pAllocator)
    {
        m_pAllocator->Release();
    
        m_pAllocator = NULL;
    }
    
    
    return NOERROR;


}

HRESULT cvSyncInputPin::CompleteConnect(IPin *pReceivePin)
{
    
    
    HRESULT hr = CBaseInputPin::CompleteConnect(pReceivePin);
    
    if (FAILED(hr)) 
    {
        return hr;
    }

    if (m_op->m_Connected != NULL) 
    
    {
        if (m_mt != m_op->m_mt)
        
        m_pFilter->ReconnectPin(m_op, &m_mt);
    }
    else
    {
        m_op->m_mt = m_mt;
    
    }

    
       
    m_Connected->QueryInterface(IID_IAMStreamConfig,(void**)&m_pVSC);

    

    if(!(m_pVSC.is_valid()))
        return E_UNEXPECTED;
    
    return S_OK;



}

HRESULT cvSyncInputPin::EndFlush()
{
    CAutoLock lock_it(m_pLock);
    HRESULT hr = NOERROR;
    hr = m_op->DeliverEndFlush();
    if (FAILED(hr))
        return hr;

    return CBaseInputPin::EndFlush();

}

HRESULT cvSyncInputPin::EndOfStream()
{
    CAutoLock lock_it(m_pLock);
    HRESULT hr = NOERROR;
    
    hr = m_op->DeliverEndOfStream();
    if (FAILED(hr))
        return hr;

    return(NOERROR);


}

HRESULT cvSyncInputPin::NewSegment(REFERENCE_TIME tStart,
                                 REFERENCE_TIME tStop,
                                 double dRate)
{
    CAutoLock lock_it(m_pLock);
    HRESULT hr = NOERROR;
    hr = m_op->DeliverNewSegment(tStart, tStop, dRate);
    if (FAILED(hr))
        return hr;
    return CBaseInputPin::NewSegment(tStart, tStop, dRate);

}

STDMETHODIMP cvSyncInputPin::Receive(IMediaSample *pSample)
{
    CAutoLock lock_it(m_pLock);

    // Check that all is well with the base class
    
    if(m_pSample.value() == NULL)
    {
        m_pSample = pSample;
        m_pSample->AddRef();
    }

    HRESULT hr = NOERROR;
        
    hr = CBaseInputPin::Receive(pSample);
        
    if (hr != NOERROR)
        return hr;

    m_pFilter->Receive();

    return NOERROR;

}

STDMETHODIMP cvSyncInputPin::NotifyAllocator(IMemAllocator *pAllocator, BOOL bReadOnly)
{
    CAutoLock lock_it(m_pLock);
    if (pAllocator == NULL)
        return E_FAIL;

    // Free the old allocator if any
    if(m_pAllocator)
    {
        m_pAllocator->Release();
        m_pAllocator = NULL;
    }

    // Store away the new allocator
    
    pAllocator->AddRef();
    m_pAllocator = pAllocator;
    
    // Notify the base class about the allocator
    return CBaseInputPin::NotifyAllocator(pAllocator,bReadOnly);


}

HRESULT cvSyncOutputPin::Active()
{

    CAutoLock lock_it(m_pLock);
    //CAutoLock lock_it_to(m_ip->m_pFilter->m_pLock);
    HRESULT hr = NOERROR;

    // Make sure that the pin is connected
    if (m_Connected == NULL)
        return NOERROR;

    // Create the output queue if we have to
    if ((!(HIWORD(m_pOutputQueue))||(LOWORD(m_pOutputQueue))))
    {
        
        m_pOutputQueue = new COutputQueue(m_Connected, &hr, TRUE, FALSE);
        if (m_pOutputQueue == NULL)
            return E_OUTOFMEMORY;

        // Make sure that the constructor did not return any error
        if (FAILED(hr))
        {
            delete m_pOutputQueue;
            m_pOutputQueue = NULL;
            return hr;
        }
    }

    // Pass the call on to the base class
    CBaseOutputPin::Active();
    return NOERROR;

}

HRESULT cvSyncOutputPin::CompleteConnect(IPin *pReceivePin)
{
    CAutoLock lock_it(m_pLock);
    ASSERT(m_Connected == pReceivePin);
    HRESULT hr = NOERROR;

    hr = CBaseOutputPin::CompleteConnect(pReceivePin);
    if (FAILED(hr))
        return hr;

    // If the type is not the same as that stored for the input
    // pin then force the input pins peer to be reconnected

    if (m_mt != m_ip->m_mt)
    {
        hr = m_ip->m_pFilter->ReconnectPin(m_ip->m_Connected, &m_mt);
        
        if(FAILED(hr)) 
        {
            return hr;
        }
    }

    return NOERROR;
}

HRESULT cvSyncOutputPin::DecideAllocator(IMemInputPin *pPin, IMemAllocator **ppAlloc)
{
 
    ASSERT(m_ip->m_pAlloc != NULL);
    *ppAlloc = NULL;

    // Tell the pin about our allocator, set by the input pin.
    HRESULT hr = NOERROR;
    hr = pPin->NotifyAllocator(m_ip->m_pAllocator,FALSE);
    if (FAILED(hr))
        return hr;

    // Return the allocator
    *ppAlloc = m_ip->m_pAllocator;
    m_ip->m_pAllocator->AddRef();
    return NOERROR;

    //return NOERROR;

}

HRESULT cvSyncOutputPin::Deliver(IMediaSample *pMediaSample)
{
    CAutoLock lock_it(m_pLock);
    pMediaSample->AddRef();
    
    // Make sure that we have an output queue
    if (!((HIWORD(m_pOutputQueue))&&(LOWORD(m_pOutputQueue))))
        return NOERROR;
    //MessageBox(NULL,"we have queue","", MB_OK);
    
    
    HRESULT hr =m_pOutputQueue->Receive(pMediaSample); 


    return hr;


}

HRESULT cvSyncOutputPin::DeliverBeginFlush()
{

    // Make sure that we have an output queue
    if (!((HIWORD(m_pOutputQueue))&&(LOWORD(m_pOutputQueue))))
        return NOERROR;

    m_pOutputQueue->BeginFlush();
    return NOERROR;

}

HRESULT cvSyncOutputPin::DeliverNewSegment(REFERENCE_TIME tStart, REFERENCE_TIME tStop, double dRate)
{
    // Make sure that we have an output queue
    if (!((HIWORD(m_pOutputQueue))&&(LOWORD(m_pOutputQueue))))
        return NOERROR;

    m_pOutputQueue->NewSegment(tStart, tStop, dRate);
    return NOERROR;

}



HRESULT cvSyncOutputPin::SetMediaType(const CMediaType *pmt)
{
    // Make sure that we have an input connected
    if (m_ip->m_Connected == NULL)
        return VFW_E_NOT_CONNECTED;

    // Make sure that the base class likes it
    HRESULT hr = NOERROR;
    hr = CBaseOutputPin::SetMediaType(pmt);
    if (FAILED(hr))
        return hr;

    return NOERROR;

}

STDMETHODIMP cvSyncOutputPin::EnumMediaTypes(IEnumMediaTypes **ppEnum)
{
    CAutoLock lock_it(m_pLock);
    ASSERT(ppEnum);

    // Make sure that we are connected
    if (m_ip->m_Connected == NULL)
        return VFW_E_NOT_CONNECTED;

    // We will simply return the enumerator of our input pin's peer
    return m_ip->m_Connected->EnumMediaTypes(ppEnum);

}

HRESULT cvSyncOutputPin::DeliverEndFlush()
{
    // Make sure that we have an output queue
    if (!((HIWORD(m_pOutputQueue))&&(LOWORD(m_pOutputQueue))))
        return NOERROR;

    m_pOutputQueue->EndFlush();
    return NOERROR;

}

HRESULT cvSyncOutputPin::DeliverEndOfStream()
{
    // Make sure that we have an output queue
    if (!((HIWORD(m_pOutputQueue))&&(LOWORD(m_pOutputQueue))))
        return NOERROR;

    m_pOutputQueue->EOS();
     
    return NOERROR;
}

HRESULT cvSyncOutputPin::Inactive()
{
    CAutoLock lock_it(m_pLock);
    //CAutoLock lock_it_to(m_ip->m_pFilter->m_pLock);

    // Delete the output queus associated with the pin.
    if ((HIWORD(m_pOutputQueue))&&(LOWORD(m_pOutputQueue)))
    {
        //m_pOutputQueue->FreeSamples();
        
        delete m_pOutputQueue;
        m_pOutputQueue = NULL;
    }

    CBaseOutputPin::Inactive();
    
    return NOERROR;
}

cvSyncInputPin::~cvSyncInputPin()
{
        m_pVSC=NULL;
}

HRESULT SyncFilter::Receive()
{
    CAutoLock lock_it(m_pLock);
    
    if(!(m_ip1->m_pSample.is_valid()) || !(m_ip2->m_pSample.is_valid()))
        return NOERROR;
        
    REFERENCE_TIME te1,te2, ts1, ts2; //timestamps
    
    static REFERENCE_TIME MediaTime1, MediaTime2 = 1;

    HRESULT hr = NOERROR;

    hr = m_ip1->m_pSample->GetTime(&ts1, &te1);

    if FAILED(hr)
    {
        m_ip1->m_pSample=NULL;
        return hr;
    }
  
    hr = m_ip2->m_pSample->GetTime(&ts2,&te2);

    if FAILED(hr)
    {
        m_ip2->m_pSample=NULL;
        return hr;
    }
    

    REFERENCE_TIME dt = (ts1-ts2)>0?(ts1 - ts2):(ts2 - ts1);

    //if(dt <= ((__min((te1-ts1), (te2-ts2)))/2))
    {
        hr = m_ip1->m_pSample->SetMediaTime(&MediaTime1,&MediaTime2);
        if FAILED(hr)
        {
            m_ip1->m_pSample=NULL;
            return hr;
        }
        
        hr = m_ip2->m_pSample->SetMediaTime(&MediaTime1, &MediaTime2);

        if FAILED(hr)
        {
        
            m_ip1->m_pSample=NULL;
            return hr;
        }
        
        if(m_callback)
            Transform(m_ip1->m_pSample.value(), m_ip2->m_pSample.value());
        
        hr = m_op1->Deliver(m_ip1->m_pSample.value());
        if(FAILED(hr))
            m_ip1->m_pSample = NULL;
        
        hr = m_op2->Deliver(m_ip2->m_pSample.value());
        if(FAILED(hr))
            m_ip2->m_pSample = NULL;
        
       

        MediaTime1++;
        MediaTime2++;
        
        
        
        m_ip1->m_pSample = NULL;
        m_ip2->m_pSample = NULL;
        
        return NOERROR;
    }
    /*else
    {
        if(ts1<ts2)
        {
            (m_ip1->m_pSample) = NULL;
        }
        else
        {
            (m_ip2->m_pSample) = NULL;
        }//if(ts1<ts2)
    
    }//if(dt <= __min(atpf1, atpf2)/2)*/
    
    return NOERROR;
    
}

STDMETHODIMP SyncFilter::Stop()
{
    
    CAutoLock lock_it(m_pLock);
    
    CBaseFilter::Stop();
    m_State = State_Stopped;
    

    return NOERROR;
    
    
    m_ip1->Inactive();
    m_ip2->Inactive();
    
    
    
    m_op1->Inactive();
    m_op2->Inactive();

    
    
    

    m_State = State_Stopped;
    
    

    return NOERROR;

}

STDMETHODIMP SyncFilter::Pause()
{
    CAutoLock cObjectLock(m_pLock);
    
    
    HRESULT hr = CBaseFilter::Pause();

    
    if (m_ip1->IsConnected() == FALSE||m_ip2->IsConnected() == FALSE)
    {
        m_ip1->EndOfStream();
        m_ip2->EndOfStream();
    }

    
    
        m_ip1->m_pSample = NULL;
    

    
        m_ip2->m_pSample = NULL;
    
    
    return hr;

}

STDMETHODIMP SyncFilter::Run(REFERENCE_TIME tStart)
{
    CAutoLock cObjectLock(m_pLock);
    HRESULT hr = CBaseFilter::Run(tStart);

    if (m_ip1->IsConnected() == FALSE||m_ip2->IsConnected() == FALSE)
    {
        m_ip1->EndOfStream();
        m_ip2->EndOfStream();
    }
    return hr;


}

HRESULT cvSyncInputPin::Inactive()
{
    
    
       m_pSample = NULL;
    
    

    return CBaseInputPin::Inactive();

}

STDMETHODIMP SyncFilter::SetCallBack(void (__cdecl *func)(void *,void *))
{

    m_callback = func;
    return S_OK;
}

STDMETHODIMP SyncFilter::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{

    CheckPointer(ppv,E_POINTER);

    if (riid == IID_ISyncFilter) 
    {
        AddRef();
        return GetInterface((ISyncFilter *) this, ppv);
    }  
    else 
    {
        return CBaseFilter::NonDelegatingQueryInterface(riid, ppv);
    }

    
}

HRESULT SyncFilter::Transform(IMediaSample *pims1, IMediaSample *pims2)
{
    ASSERT(m_callback);

    BYTE*    pData1;
    IplImage image1;

    BYTE*    pData2;
    IplImage image2;

    pims1->GetPointer(&pData1);
    pims2->GetPointer(&pData2);

    AM_MEDIA_TYPE* pType1 = &m_ip1->m_mt;
    AM_MEDIA_TYPE* pType2 = &m_ip2->m_mt;

    VIDEOINFOHEADER *pvi1 = (VIDEOINFOHEADER *) pType1->pbFormat;
    VIDEOINFOHEADER *pvi2 = (VIDEOINFOHEADER *) pType2->pbFormat;
    
    if(pvi1->bmiHeader.biBitCount != 24)
    {
        return NOERROR;
    }

    if(pvi2->bmiHeader.biBitCount != 24)
    {
        return NOERROR;
    }

    int cxImage1    = pvi1->bmiHeader.biWidth;
    int cyImage1    = abs(pvi1->bmiHeader.biHeight);
    int stride1     = (cxImage1 * sizeof( RGBTRIPLE ) + 3) & -4;
    
    int cxImage2    = pvi2->bmiHeader.biWidth;
    int cyImage2    = abs(pvi2->bmiHeader.biHeight);
    int stride2     = (cxImage2 * sizeof( RGBTRIPLE ) + 3) & -4;

    // Initialize image header
    cvInitImageHeader( &image1, cvSize(cxImage1, cyImage1), 8, 3, IPL_ORIGIN_BL, 4, 1 );
    image1.widthStep = stride1;
    
    cvInitImageHeader( &image2, cvSize(cxImage2, cyImage2), 8, 3, IPL_ORIGIN_BL, 4, 1 );
    image2.widthStep = stride2;

    cvSetImageData( &image1, pData1, stride1 );
    cvSetImageData( &image2, pData2, stride2 );

    m_callback(&image1, &image2);

    return S_OK;
}


