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
#include <streams.h>
#include <initguid.h>
#include <olectl.h>
#include <math.h>
#if (1100 > _MSC_VER)
#include <olectlid.h>
#endif
#include <assert.h>
#include "CamShiftUIDs.h"
#include "CV.hpp"
#include "iCamShift.h"
#include "CamShiftProp.h"
#include "CamShiftF.h"
#include "resource.h"

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


const AMOVIESETUP_FILTER sudCamShift =
{
    &CLSID_CamShift,        // Filter CLSID
    L"CamShift",            // Filter name
    MERIT_DO_NOT_USE,       // Its merit
    2,                      // Number of pins
    psudPins                // Pin details
};


// List of class IDs and creator functions for the class factory. This
// provides the link between the OLE entry point in the DLL and an object
// being created. The class factory will call the static CreateInstance

CFactoryTemplate g_Templates[2] = {

    { L"CamShift"
    , &CLSID_CamShift
    , CCamShiftF::CreateInstance
    , NULL
    , &sudCamShift }
  ,
    { L"CamShift Property Page"
    , &CLSID_CamShiftPropertyPage
    , CCamShiftProperties::CreateInstance }
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);


//
// Constructor
//
CCamShiftF::CCamShiftF(TCHAR *tszName,LPUNKNOWN punk,HRESULT *phr) :
    CTransformFilter(tszName, punk, CLSID_CamShift)
{
    m_params.x = 0.4f; 
    m_params.y = 0.3f;
    m_params.width = 0.2f;
    m_params.height = 0.3f;

    m_params.Smin = 20;
    m_params.Vmin = 40;
    m_params.Vmax = 255;
    m_params.bins = 20;
    m_params.view = 0;
    m_params.threshold = 0;

    IsTracking = false;
    IsInit = false;
} // CamShift


//
// CreateInstance
//
// Provide the way for COM to create a CCamShift object
//
CUnknown * WINAPI CCamShiftF::CreateInstance(LPUNKNOWN punk, HRESULT *phr) {

    CCamShiftF *pNewObject = new CCamShiftF(NAME("CamShift"), punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;

} // CreateInstance


//
// NonDelegatingQueryInterface
//
// Reveals ICamShift and ISpecifyPropertyPages
//
STDMETHODIMP CCamShiftF::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
    CheckPointer(ppv,E_POINTER);

    if (riid == IID_ICamShift) {
        return GetInterface((ICamShift *) this, ppv);
    } else if (riid == IID_ISpecifyPropertyPages) {
        return GetInterface((ISpecifyPropertyPages *) this, ppv);
    } else {
        return CTransformFilter::NonDelegatingQueryInterface(riid, ppv);
    }

} // NonDelegatingQueryInterface


//
// Transform
//
// Copy the input sample into the output sample
// Then transform the output sample 'in place'
//
HRESULT CCamShiftF::Transform(IMediaSample *pIn, IMediaSample *pOut)
{
    HRESULT hr = Copy(pIn, pOut);
    if (FAILED(hr)) {
        return hr;
    }
    return Transform(pOut);

} // Transform


//
// Copy
//
// Make destination an identical copy of source
//
HRESULT CCamShiftF::Copy(IMediaSample *pSource, IMediaSample *pDest) const
{
    // Copy the sample data

    BYTE *pSourceBuffer, *pDestBuffer;
    long lSourceSize = pSource->GetActualDataLength();
    long lDestSize	= pDest->GetSize();

    ASSERT(lDestSize >= lSourceSize);

    pSource->GetPointer(&pSourceBuffer);
    pDest->GetPointer(&pDestBuffer);

    CopyMemory( (PVOID) pDestBuffer,(PVOID) pSourceBuffer,lSourceSize);

    // Copy the sample times

    REFERENCE_TIME TimeStart, TimeEnd;
    if (NOERROR == pSource->GetTime(&TimeStart, &TimeEnd)) {
        pDest->SetTime(&TimeStart, &TimeEnd);
    }

    LONGLONG MediaStart, MediaEnd;
    if (pSource->GetMediaTime(&MediaStart,&MediaEnd) == NOERROR) {
        pDest->SetMediaTime(&MediaStart,&MediaEnd);
    }

    // Copy the Sync point property

    HRESULT hr = pSource->IsSyncPoint();
    if (hr == S_OK) {
        pDest->SetSyncPoint(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetSyncPoint(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // Copy the media type

    AM_MEDIA_TYPE *pMediaType;
    pSource->GetMediaType(&pMediaType);
    pDest->SetMediaType(pMediaType);
    DeleteMediaType(pMediaType);

    // Copy the preroll property

    hr = pSource->IsPreroll();
    if (hr == S_OK) {
        pDest->SetPreroll(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetPreroll(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // Copy the discontinuity property

    hr = pSource->IsDiscontinuity();
    if (hr == S_OK) {
	pDest->SetDiscontinuity(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetDiscontinuity(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // Copy the actual data length

    long lDataLength = pSource->GetActualDataLength();
    pDest->SetActualDataLength(lDataLength);
    return NOERROR;

} // Copy


void  CCamShiftF::ApplyCamShift( CvImage* image, bool initialize )
{
    CvSize size;
    int bins = m_params.bins;

    m_cCamShift.set_hist_dims( 1, &bins );
    m_cCamShift.set_thresh( 0, 1, 180 );
    m_cCamShift.set_threshold( 0 );
    m_cCamShift.set_min_ch_val( 1, m_params.Smin );
    m_cCamShift.set_max_ch_val( 1, 255 );
    m_cCamShift.set_min_ch_val( 2, m_params.Vmin );
    m_cCamShift.set_max_ch_val( 2, m_params.Vmax );
    
    cvGetImageRawData( image, 0, 0, &size );

    if( m_object.x < 0 ) m_object.x = 0;
    if( m_object.x > size.width - m_object.width - 1 )
        m_object.x = MAX(0, size.width - m_object.width - 1);

    if( m_object.y < 0 ) m_object.y = 0;
    if( m_object.y > size.height - m_object.height - 1 )
        m_object.y = MAX(0, size.height - m_object.height - 1);

    if( m_object.width > size.width - m_object.x )
        m_object.width = MIN(size.width, size.width - m_object.x);

    if( m_object.height > size.height - m_object.y )
        m_object.height = MIN(size.height, size.height - m_object.y);

    m_cCamShift.set_window(m_object);
    
    if( initialize )
    {
        m_cCamShift.reset_histogram();
        m_cCamShift.update_histogram( image );
    }

    m_cCamShift.track_object( image );
    m_object = m_cCamShift.get_window();
}


void  CCamShiftF::CheckBackProject( CvImage* image )
{
    if( m_params.view == 1 )
    {
        IplImage* src = m_cCamShift.get_back_project();
        if( src && src->imageData && image )
        {
            cvCvtColor( src, image, CV_GRAY2BGR );
        }
    }
    else if( m_params.view == 2 && IsTracking )
    {
        int i, dims;
        CvSize size;

        m_cCamShift.get_hist_dims( &dims );
        cvGetImageRawData( image, 0, 0, &size );

        for( i = 0; i < dims; i++ )
        {
            int val = m_cCamShift.query(i);
            CvPoint p[4];

            p[0].x = p[1].x = i*size.width/(2*dims);
            p[2].x = p[3].x = (i+1)*size.width/(2*dims);

            p[1].y = p[2].y = 0;
            p[0].y = p[3].y = (val*size.height)/(3*255);

            cvFillConvexPoly( image, p, 4, CV_RGB(255,0,0));
        }
    }
}


void  CCamShiftF::DrawCross( CvImage* image )
{
    float cs = (float)cos( m_cCamShift.get_orientation() );
    float sn = (float)sin( m_cCamShift.get_orientation() );
    
    int x = m_object.x + m_object.width / 2;
    int y = m_object.y + m_object.height / 2;
    
    CvPoint p1 = {(int)(x + m_cCamShift.get_length() * cs / 2),
        (int)(y + m_cCamShift.get_length() * sn / 2)};
    CvPoint p2 = {(int)(x - m_cCamShift.get_length() * cs / 2),
        (int)(y - m_cCamShift.get_length() * sn / 2)};
    CvPoint p3 = {(int)(x + m_cCamShift.get_width() * sn / 2),
        (int)(y - m_cCamShift.get_width() * cs / 2)};
    CvPoint p4 = {(int)(x - m_cCamShift.get_width() * sn / 2),
        (int)(y + m_cCamShift.get_width() * cs / 2)};
    cvLine( image, p1, p2, CV_RGB(255,255,255) );
    cvLine( image, p4, p3, CV_RGB(255,255,255) );
}


//
// Transform
//
// 'In place' adjust the CamShift of this sample
//
HRESULT CCamShiftF::Transform(IMediaSample *pMediaSample)
{
    BYTE*   pData;
    CvImage image;
    
    pMediaSample->GetPointer(&pData);
    
    AM_MEDIA_TYPE* pType = &m_pInput->CurrentMediaType();
    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) pType->pbFormat;
    
    // Get the image properties from the BITMAPINFOHEADER
    CvSize size = cvSize( pvi->bmiHeader.biWidth, pvi->bmiHeader.biHeight );
    int stride = (size.width * 3 + 3) & -4;

    cvInitImageHeader( &image, size, IPL_DEPTH_8U, 3, IPL_ORIGIN_TL, 4, 1 );
    cvSetImageData( &image, pData,stride );

    if(IsTracking == false)
    {
        if(IsInit == false)
        {
            CvPoint p1, p2;
            // Draw box
            p1.x = cvRound( size.width * m_params.x );
            p1.y = cvRound( size.height * m_params.y );

            p2.x = cvRound( size.width * (m_params.x + m_params.width));
            p2.y = cvRound( size.height * (m_params.y + m_params.height));

            CheckBackProject( &image );

            cvRectangle( &image, p1, p2, -1, 1 );
        }
        else 
        {
            m_object.x = cvRound( size.width * m_params.x );
            m_object.y = cvRound( size.height * m_params.y );
            m_object.width = cvRound( size.width * m_params.width );
            m_object.height = cvRound( size.height * m_params.height );

            ApplyCamShift( &image, true );
            CheckBackProject( &image );
            
            IsTracking = true;
        }
    }
    else
    {
        ApplyCamShift( &image, false );
        CheckBackProject( &image );

        DrawCross( &image );
    }

    cvSetImageData( &image, 0, 0 );
    return NOERROR;
} // Transform


//
// CheckInputType
//
// Check the input type is OK, return an error otherwise
//
HRESULT CCamShiftF::CheckInputType(const CMediaType *mtIn)
{
    // Check this is a VIDEOINFO type

    if (*mtIn->FormatType() != FORMAT_VideoInfo) {
        return E_INVALIDARG;
    }

    // Is this a palettised format

    if (CanChangeCamShiftLevel(mtIn)) {
    	return NOERROR;
    }
    return E_FAIL;

} // CheckInputType


//
// CheckTransform
//
// To be able to transform the formats must be identical
//
HRESULT CCamShiftF::CheckTransform(const CMediaType *mtIn,const CMediaType *mtOut)
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
HRESULT CCamShiftF::DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
{
    // Is the input pin connected

    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    ASSERT(pAlloc);
    ASSERT(pProperties);
    HRESULT hr = NOERROR;

    pProperties->cBuffers = 1;
    pProperties->cbBuffer = m_pInput->CurrentMediaType().GetSampleSize();

    ASSERT(pProperties->cbBuffer);

    // If we don't have fixed sized samples we must guess some size

    if (!m_pInput->CurrentMediaType().bFixedSizeSamples) {
        if (pProperties->cbBuffer < 100000) {
            // nothing more than a guess!!
            pProperties->cbBuffer = 100000;
        }
    }

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);
    if (FAILED(hr)) {
        return hr;
    }

    ASSERT( Actual.cBuffers == 1 );

    if (pProperties->cBuffers > Actual.cBuffers ||
            pProperties->cbBuffer > Actual.cbBuffer) {
                return E_FAIL;
    }
    return NOERROR;

} // DecideBufferSize


//
// GetMediaType
//
// I support one type, namely the type of the input pin
// We must be connected to support the single output type
//
HRESULT CCamShiftF::GetMediaType(int iPosition, CMediaType *pMediaType)
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
// GetPages
//
// This is the sole member of ISpecifyPropertyPages
// Returns the clsid's of the property pages we support
//
STDMETHODIMP CCamShiftF::GetPages(CAUUID *pPages)
{
    pPages->cElems = 1;
    pPages->pElems = (GUID *) CoTaskMemAlloc(sizeof(GUID));
    if (pPages->pElems == NULL) {
        return E_OUTOFMEMORY;
    }
    *(pPages->pElems) = CLSID_CamShiftPropertyPage;
    return NOERROR;

} // GetPages


STDMETHODIMP CCamShiftF::GetParams( CvCamShiftParams* params )
{
    if( params )
    {
        *params = m_params;
    }
    return NOERROR;
}


STDMETHODIMP CCamShiftF::SetParams( CvCamShiftParams* params )
{
    CAutoLock cAutoLock(&m_CamShiftLock);
    if( params )
    {
        m_params = *params;
    }
    return NOERROR;
}



STDMETHODIMP CCamShiftF::StartTracking()
{
    CAutoLock cAutoLock(&m_CamShiftLock);
    IsInit = true;
    IsTracking = false;
    return NOERROR;
}

STDMETHODIMP CCamShiftF::StopTracking()
{
    CAutoLock cAutoLock(&m_CamShiftLock);
    IsInit = IsTracking = false;
    return NOERROR;
}

//
// CanChangeCamShiftLevel
//
// Check if this is a paletised format
//
BOOL CCamShiftF::CanChangeCamShiftLevel(const CMediaType *pMediaType) const
{
    if ((IsEqualGUID(*pMediaType->Type(), MEDIATYPE_Video))
        && (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB24))) {

        // I think I can process this format (8 bit palettised)
        // So do a quick sanity check on the palette information

        VIDEOINFO *pvi = (VIDEOINFO *) pMediaType->Format();
        return (pvi->bmiHeader.biBitCount == 24);

    } else {
        return FALSE;
    }
} // CanChangeCamShiftLevel



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

/* End of file. */
