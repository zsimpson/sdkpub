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
#if (1100 > _MSC_VER)
#include <olectlid.h>
#endif
#include "iKalman.h"
#include "Kalmanprop.h"
#include "Kalman.h"
#include "Kalmanuids.h"

// setup data
const AMOVIESETUP_MEDIATYPE sudPinTypes =
{
    &MEDIATYPE_Video,       // Major type
    &MEDIASUBTYPE_RGB24      // Minor type
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


const AMOVIESETUP_FILTER sudCKalmTrack =
{
    &CLSID_CKalmTrack,        // Filter CLSID
    L"Kalman",                    // Filter name
    MERIT_DO_NOT_USE,               // Its merit
    2,                              // Number of pins
    psudPins                        // Pin details
};


// List of class IDs and creator functions for the class factory. This
// provides the link between the OLE entry point in the DLL and an object
// being created. The class factory will call the static CreateInstance

CFactoryTemplate g_Templates[2] = {

    { L"Kalman"
    , &CLSID_CKalmTrack
    , CKalmTrack::CreateInstance
    , NULL
    , &sudCKalmTrack }
  ,
    { L"Kalman Property Page"
    , &CLSID_CKalmTrackPropertyPage
    , CKalmTrackProperties::CreateInstance }
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);



//
// Constructor
//
CKalmTrack::CKalmTrack(TCHAR *tszName,LPUNKNOWN punk,HRESULT *phr) :
    CTransInPlaceFilter(tszName, punk, CLSID_CKalmTrack,phr)    
   
{
    m_params.x = 0.4f; 
    m_params.y = 0.3f;
    m_params.width = 0.2f;
    m_params.height = 0.3f;

    m_params.Smin = 20;
    m_params.Vmin = 40;
    m_params.view = 0;

    IsTracking = false;
    IsInit =false;
	Kalman = cvCreateKalman(4,4);
	CvMat Dyn = cvMat(4,4,CV_MAT4x4_32F,Kalman->DynamMatr);
	CvMat Mes = cvMat(4,4,CV_MAT4x4_32F,Kalman->MeasurementMatr);
	CvMat PNC = cvMat(4,4,CV_MAT4x4_32F,Kalman->PNCovariance);
	CvMat MNC = cvMat(4,4,CV_MAT4x4_32F,Kalman->MNCovariance);
	CvMat PriErr = cvMat(4,4,CV_MAT4x4_32F,Kalman->PriorErrorCovariance);
	CvMat PostErr = cvMat(4,4,CV_MAT4x4_32F,Kalman->PosterErrorCovariance);
	CvMat PriState = cvMat(4,1,CV_MAT4x1_32F,Kalman->PriorState);
	cvmSetIdentity(&PNC);
	cvmSetIdentity(&PriErr);
	cvmSetIdentity(&PostErr);
	cvmSetZero(&MNC);
	cvmSetZero(&PriState);
    cvmSetIdentity(&Dyn);
    cvmSet(&Dyn,0,1,0.9f);
    cvmSet(&Dyn,2,3,0.9f);
    cvmSetIdentity(&Mes);
	MVect = cvMat(4,1,CV_MAT4x1_32F,Measurement);
	ASSERT(tszName);
    ASSERT(phr);
} // CKalmTrack

//Destructor
CKalmTrack::~CKalmTrack()
{
	cvReleaseKalman(&Kalman);
}//~CKalmTrack

//
// CreateInstance
//
// Provide the way for COM to create a CKalmTrack object
//
CUnknown * WINAPI CKalmTrack::CreateInstance(LPUNKNOWN punk, HRESULT *phr) {

    CKalmTrack *pNewObject = new CKalmTrack(NAME("Kalman"), punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;

} // CreateInstance


//
// NonDelegatingQueryInterface
//
// Reveals ICKalmTrack and ISpecifyPropertyPages
//
STDMETHODIMP CKalmTrack::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
    CheckPointer(ppv,E_POINTER);

    if (riid == IID_ICKalmTrack) {
        return GetInterface((ICKalmTrack *) this, ppv);
    } else if (riid == IID_ISpecifyPropertyPages) {
        return GetInterface((ISpecifyPropertyPages *) this, ppv);
    } else {
        return CTransInPlaceFilter::NonDelegatingQueryInterface(riid, ppv);
    }

} // NonDelegatingQueryInterface


void  CKalmTrack::ApplyCamShift( CvImage* image, bool initialize )
{
    CvSize size;
    int bins = 20;

    m_cCamShift.set_hist_dims( 1, &bins );
    m_cCamShift.set_thresh( 0, 1, 180 );
    m_cCamShift.set_min_ch_val( 1, m_params.Smin );
    m_cCamShift.set_max_ch_val( 1, 255 );
    m_cCamShift.set_min_ch_val( 2, m_params.Vmin );
    m_cCamShift.set_max_ch_val( 2, 255 );
    
    cvGetImageRawData( image, 0, 0, &size );

    if( m_object.x < 0 ) m_object.x = 0;
    if( m_object.x > size.width - m_object.width - 1 )
        m_object.x = size.width - m_object.width - 1;

    if( m_object.y < 0 ) m_object.y = 0;
    if( m_object.y > size.height - m_object.height - 1 )
        m_object.y = size.height - m_object.height - 1;

    m_cCamShift.set_window(m_object);
    
    if( initialize )
    {
        m_cCamShift.reset_histogram();
        m_cCamShift.update_histogram( image );
    }

    m_cCamShift.track_object( image );
    m_object = m_cCamShift.get_window();

    Measurement[0] = (float)m_object.x + m_object.width*0.5f;
    Measurement[1] = initialize ? 0 : Measurement[0] - m_Old.x;
    Measurement[2] = (float)m_object.y + m_object.height*0.5f;
    Measurement[3] = initialize ? 0 : Measurement[2] - m_Old.y;

    m_Old.x = cvRound( Measurement[0] );
    m_Old.y = cvRound( Measurement[2] );
    cvKalmanUpdateByMeasurement(Kalman,&MVect);
}


void  CKalmTrack::CheckBackProject( CvImage* image )
{
    if( m_params.view != 0 )
    {
        IplImage* src = m_cCamShift.get_back_project();
        if( src && src->imageData && image )
        {
            cvCvtColor( src, image, CV_GRAY2BGR );
        }
    }
}

//
// Transform
// Transform the  sample 'in place'
//
HRESULT CKalmTrack::Transform(IMediaSample *pSample)
{
    BYTE*   pData;
    CvImage image;
    
    pSample->GetPointer(&pData);
    
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
        cvKalmanUpdateByTime(Kalman);
        m_object.x = cvRound( Kalman->PriorState[0]-m_object.width*0.5);
        m_object.y = cvRound( Kalman->PriorState[2]-m_object.height*0.5 );
        
        ApplyCamShift( &image, false );

        CheckBackProject( &image );

        cvRectangle( &image,
                     cvPoint( m_object.x, m_object.y ),
                     cvPoint( m_object.x + m_object.width, m_object.y + m_object.height ),
                     -1, 1 );

        Rectang(&image,m_Indicat1,-1);
        m_X.x = 10;
        m_X.y = 10;
        m_X.width=50*m_Old.x/size.width;
        m_X.height =10;
        Rectang(&image,m_X,CV_RGB(0,0,255));
        m_Y.x = 10;
        m_Y.y = 10;
        m_Y.width=10;
        m_Y.height = 50*m_Old.y/size.height;
        Rectang(&image,m_Y,CV_RGB(255,0,0));
        m_Indicat2.x = 0; 
        m_Indicat2.y = size.height-50;
        m_Indicat2.width = 50;
        m_Indicat2.height = 50;
        Rectang(&image,m_Indicat2,-1);
        float Norm = cvSqrt(Measurement[1]*Measurement[1]+Measurement[3]*Measurement[3]);
        int VXNorm = (fabs(Measurement[1])>5)?(int)(12*Measurement[1]/Norm):0;
        int VYNorm = (fabs(Measurement[3])>5)?(int)(12*Measurement[3]/Norm):0;
        CvPoint pp1 = {25,size.height-25};
        CvPoint pp2 = {25+VXNorm,size.height-25+VYNorm};
        cvLine(&image,pp1,pp2,CV_RGB(0,0,0),3);
        /*CvPoint pp1 = {25,size.height-25};
        double angle = atan2( Measurement[3], Measurement[1] );
        CvPoint pp2 = {cvRound(25+12*cos(angle)),cvRound(size.height-25-12*sin(angle))};
        cvLine(&image,pp1,pp2,0,3);*/
    }

    cvSetImageData( &image, 0, 0 );

    return NOERROR;
} // Transform


//
// CheckInputType
//
// Check the input type is OK, return an error otherwise
//
HRESULT CKalmTrack::CheckInputType(const CMediaType *mtIn)
{
    // Check this is a VIDEOINFO type

    if (*mtIn->FormatType() != FORMAT_VideoInfo)
    {
        
    }
    if ((IsEqualGUID(*mtIn->Type(), MEDIATYPE_Video))
        && (IsEqualGUID(*mtIn->Subtype(), MEDIASUBTYPE_RGB24)))return NOERROR;
    return E_INVALIDARG;
   

} // CheckInputType



// CheckTransform
//
// To be able to transform the formats must be identical
//

HRESULT CKalmTrack::CheckTransform(const CMediaType *mtIn,const CMediaType *mtOut)
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
HRESULT CKalmTrack::DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
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
HRESULT CKalmTrack::GetMediaType(int iPosition, CMediaType *pMediaType)
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


STDMETHODIMP CKalmTrack::GetState(bool* State)
{
    *State = IsTracking;    
    return NOERROR;
}


STDMETHODIMP CKalmTrack::SetParams(CvKalmanParams* params)
{
    CAutoLock cAutoLock(&m_cKalmTrackLock);
    
    if( params )
    {
        m_params = *params; 
    }

    return NOERROR;
}


STDMETHODIMP CKalmTrack::GetParams(CvKalmanParams* params)
{
    if( params )
    {
        *params = m_params; 
    }

    return NOERROR;
}


STDMETHODIMP CKalmTrack::StartTracking()
{
    CAutoLock cAutoLock(&m_cKalmTrackLock);
    IsTracking = false;
    IsInit = true; 
    return NOERROR;
}

STDMETHODIMP CKalmTrack::StopTracking()
{
    CAutoLock cAutoLock(&m_cKalmTrackLock);
    
    IsTracking = false;
    IsInit = false;
    return NOERROR;
}


//
// GetPages
//
// This is the sole member of ISpecifyPropertyPages
// Returns the clsid's of the property pages we support
//

STDMETHODIMP CKalmTrack::GetPages(CAUUID *pPages)
{
    pPages->cElems = 1;
    pPages->pElems = (GUID *) CoTaskMemAlloc(sizeof(GUID));
    if (pPages->pElems == NULL) {
        return E_OUTOFMEMORY;
    }
    *(pPages->pElems) = CLSID_CKalmTrackPropertyPage;
    return NOERROR;

} // GetPages


CKalmTrack::Rectang(IplImage* img,CvRect Rect, int color)
{
    for( int j = 0; j < Rect.height; j++ )
    {
        CvPoint p1={Rect.x,Rect.y+j};
        CvPoint p2={Rect.x+Rect.width,Rect.y+j};
        cvLine(img,p1,p2,color);
    }
}


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
