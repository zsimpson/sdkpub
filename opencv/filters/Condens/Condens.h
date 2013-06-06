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
#include "CV.hpp"
class CCondens : public CTransInPlaceFilter,
		  public ICCondens,
		  public ISpecifyPropertyPages
{

public:
    
    // Constructor
    CCondens ( TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	// Destructor
	~CCondens();
    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    // Reveals CCondens & ISpecifyPropertyPages
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);
    HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
    HRESULT DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties);
    HRESULT CheckTransform(const CMediaType *mtIn,const CMediaType *mtOut);

    // ICCondens methods
	STDMETHODIMP GetParams( CvCondensParams* params);
    STDMETHODIMP SetParams( CvCondensParams* params);
    STDMETHODIMP GetState(bool* State);
    STDMETHODIMP StartTracking(void);
    STDMETHODIMP StopTracking(void); 
    // ISpecifyPropertyPages method

    STDMETHODIMP GetPages(CAUUID *pPages);

private:
      
    void  ApplyCamShift( CvImage* image, bool initialize );
    void  CheckBackProject( CvImage* image );


    // Non interface locking critical section
    CCritSec m_CCondensLock;
    float Dynam[16];
    float Measurement[4];
    bool IsInit;
    bool IsTracking;
    CvCamShiftTracker m_cCamShift; 
	CvConDensation* ConDens;
    CvCondensParams m_params;
    CvRect m_object;
    CvPoint m_Old;
    CvRect m_Indicat1;
    CvRect m_Indicat2;
    CvRect m_X;
    CvRect m_VX;
    CvRect m_Y;
    CvRect m_VY;
    long m_TrSize;
	int m_SamplesNum;
	float LBound[4];
	float UBound[4];
	float XCor;
	float VXCor;
	float YCor;
	float VYCor;
    Rectang(IplImage* img, CvRect Rect, int color); 
	CondProbDens(CvConDensation* CD,float* Measurement);

}; // CCondens
