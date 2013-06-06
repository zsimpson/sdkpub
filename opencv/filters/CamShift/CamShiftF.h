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

#pragma once

#include "CV.hpp"

class CCamShiftF : public CTransformFilter,
            public ICamShift,
            public ISpecifyPropertyPages
{

public:

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    // Reveals ICamShift & ISpecifyPropertyPages
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pIn, IMediaSample *pOut);
    HRESULT CheckInputType(const CMediaType *mtIn);
    HRESULT CheckTransform(const CMediaType *mtIn,const CMediaType *mtOut);
    HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
    HRESULT DecideBufferSize(IMemAllocator *pAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);

    // ICamShift methods

    STDMETHODIMP SetParams( CvCamShiftParams* params );
    STDMETHODIMP GetParams( CvCamShiftParams* params );

    STDMETHODIMP StartTracking();
    STDMETHODIMP StopTracking();

    // ISpecifyPropertyPages method

    STDMETHODIMP GetPages(CAUUID *pPages);

private:

    // Constructor
    CCamShiftF(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
    void  CheckBackProject( CvImage* image );
    void  ApplyCamShift( CvImage* image, bool initialize );
    void  DrawCross( CvImage* image );

    // Look after the transformation of media samples
    BOOL CanChangeCamShiftLevel(const CMediaType *pMediaType) const;
    HRESULT Copy(IMediaSample *pSource, IMediaSample *pDest) const;
    HRESULT Transform(IMediaSample *pMediaSample);

    // Non interface locking critical section
    CCritSec m_CamShiftLock;
    CvCamShiftTracker m_cCamShift;
    CvCamShiftParams m_params;

    CvRect m_object;
    bool IsTracking;
    bool IsInit;

}; // CCamShift


/* End of file. */
