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
// A custom interface to allow the user to adjust the CamShift level.

#pragma once

#include "CV.h"


typedef struct _CvCamShiftParams
{
    float x, y, width, height; /* relative position of object window */
    int   Smin, Vmin, Vmax;
    int   threshold;
    int   bins;
    int   view;
}
CvCamShiftParams;

#ifdef __cplusplus
extern "C" {
#endif

    // {A515A466-199E-11d3-9893-009027350DE4}
    DEFINE_GUID(IID_ICamShift,
    0xa515a466, 0x199e, 0x11d3, 0x98, 0x93, 0x0, 0x90, 0x27, 0x35, 0xd, 0xe4);


    DECLARE_INTERFACE_(ICamShift, IUnknown)
    {
        STDMETHOD(GetParams) (THIS_
            CvCamShiftParams* params
        ) PURE;

        STDMETHOD(SetParams) (THIS_
            CvCamShiftParams* params
        ) PURE;
   
        STDMETHOD(StartTracking)(THIS) PURE;
        STDMETHOD(StopTracking)(THIS) PURE;
    };

#ifdef __cplusplus
}
#endif


/* End of file. */
