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

#ifndef __ISYNCFILTER_H__

#define __ISYNCFILTER_H__

#ifdef __cplusplus
extern "C" {
#endif

// {ECEC07A3-E3ED-4f11-BD48-5773F84778B3}
DEFINE_GUID(IID_ISyncFilter, 
0xecec07a3, 0xe3ed, 0x4f11, 0xbd, 0x48, 0x57, 0x73, 0xf8, 0x47, 0x78, 0xb3);


DECLARE_INTERFACE_(ISyncFilter, IUnknown)
{
    STDMETHOD(SetCallBack) (THIS_
             void (__cdecl *callback)(void*, void*)       // Change to the param
             ) PURE;

};


#ifdef __cplusplus
}
#endif

#endif //__ICVSYNC_H__