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
#include "isyncfilter.h"

template <class T> class SafePointer
{
    protected:
    T* m_pointer;

    public:
    SafePointer() : m_pointer(0) {};
    SafePointer(T* pointer) {m_pointer = pointer;};
    SafePointer(const SafePointer& p) 
    {
        m_pointer = p.m_pointer;
        if(m_pointer)
        {
            m_pointer->AddRef();
        }
    };
    ~SafePointer() 
    {
        if(m_pointer) 
        {
            m_pointer->Release();
            m_pointer = NULL;
        }//if(m_pointer)

    };

    T* value() {return m_pointer;};
    T* operator ->() {return m_pointer;};
    T** operator &() 
    {
        if(m_pointer) 
        {
            m_pointer->Release();
            m_pointer = NULL;
        }//if(m_pointer)

        return &m_pointer;
    };
    void operator =(T* pointer) 
    {
        if(m_pointer) m_pointer->Release();
        m_pointer = pointer;
    };
    int is_valid() {return int(m_pointer);};
    //int operator() (void ){return int(m_pointer);}
};

////////////////////////////////////////////
class cvSyncInputPin : public CBaseInputPin
{
friend class SyncFilter;
friend class cvSyncOutputPin;

public:
//  HRESULT Active();
    HRESULT Inactive();
    ~cvSyncInputPin();
    STDMETHOD(NotifyAllocator)(IMemAllocator *pAllocator, BOOL bReadOnly);
    STDMETHOD(Receive)(IMediaSample *pSample);
    STDMETHODIMP NewSegment(REFERENCE_TIME tStart,
                                 REFERENCE_TIME tStop,
                                 double dRate);
    STDMETHODIMP EndOfStream();
    STDMETHODIMP EndFlush();
    HRESULT CompleteConnect(IPin *pReceivePin);
    HRESULT BreakConnect();
    STDMETHODIMP BeginFlush(void);
    
    cvSyncInputPin(TCHAR *pObjectName,
                   SyncFilter *pFilter,
                   CCritSec *pLock,
                   HRESULT* hr,
                   LPCWSTR pName
                   ):CBaseInputPin(pObjectName,
                                   (CBaseFilter*)pFilter,
                                   pLock,
                                   hr,
                                   pName), m_pFilter(pFilter), m_pSample(NULL),
                                   m_pVSC(NULL), m_pAllocator(NULL)
                                   
    {
        CBaseInputPin::m_pAllocator=NULL;
    };

    HRESULT CheckMediaType(const CMediaType* pmt)
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

private:
    SafePointer<IAMStreamConfig> m_pVSC;
    SafePointer<IMediaSample> m_pSample;
    SyncFilter* m_pFilter;
    
    cvSyncOutputPin* m_op;
    IMemAllocator* m_pAllocator;
    
//    SafePointer<IMemAllocator> m_pAlloc;
};

class cvSyncOutputPin : public CBaseOutputPin
{
    friend class SyncFilter;
    friend class cvSyncInputPin;
public:
    //static CCritSec m_Lock;
    HRESULT Inactive();
    HRESULT DeliverEndOfStream();
    HRESULT DeliverEndFlush();
    STDMETHOD(EnumMediaTypes)(IEnumMediaTypes **ppEnum);
    HRESULT SetMediaType(const CMediaType *pmt);
//  STDMETHOD(Notify)(IBaseFilter *pSender, Quality q);
    HRESULT DeliverNewSegment(REFERENCE_TIME tStart,REFERENCE_TIME tStop,double dRate);
    HRESULT DeliverBeginFlush();
    HRESULT Deliver(IMediaSample *pMediaSample);
    HRESULT DecideAllocator(IMemInputPin *pPin, IMemAllocator **ppAlloc);
    HRESULT CompleteConnect(IPin *pReceivePin);
    
    COutputQueue* m_pOutputQueue;

    HRESULT Active();

    cvSyncOutputPin(TCHAR *pObjectName,
                   CBaseFilter *pFilter,
                   CCritSec *pLock,
                   HRESULT* hr,
                   LPCWSTR pName
                   ):CBaseOutputPin(pObjectName,
                                   pFilter,
                                   pLock,
                                   hr,
                                   pName)
    {
    
    };

    HRESULT CheckMediaType(const CMediaType* pmt);
    

    HRESULT DecideBufferSize( IMemAllocator *pAlloc
                               , ALLOCATOR_PROPERTIES *pProperties
                             )
    {
        return NOERROR;
    };

    cvSyncInputPin* m_ip;
};



class SyncFilter  : public CBaseFilter, public ISyncFilter
{

friend class cvSyncOutputPin;
friend class cvSyncInputPin;

public:
    HRESULT Transform(IMediaSample* pims1, IMediaSample* pims2);
    
    STDMETHOD(NonDelegatingQueryInterface)(REFIID riid, void **ppv);

    STDMETHOD(SetCallBack)( void (__cdecl*func)(void*, void*) );
    
    STDMETHOD(Run)(REFERENCE_TIME tStart);

    STDMETHOD(Pause)();
    
    STDMETHOD(Stop)();
    
    HRESULT Receive();
    

    SyncFilter(TCHAR* tszName, LPUNKNOWN punk, HRESULT* phr);
    
    static CUnknown* WINAPI CreateInstance(LPUNKNOWN punk, HRESULT 
    *phr);
    
    DECLARE_IUNKNOWN;

    int GetPinCount(void);

    CBasePin* GetPin(int n);

    //HRESULT CheckMediaType(const CMediaType* pmt);

    ~SyncFilter();
    
protected:
    CCritSec m_csFilter;
    HRESULT  m_hr;
    
    cvSyncInputPin* m_ip1;
    cvSyncInputPin* m_ip2;


    cvSyncOutputPin* m_op1;
    cvSyncOutputPin* m_op2;
    void        (__cdecl *m_callback)(void*, void*);

};