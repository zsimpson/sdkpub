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
//M*/// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__A499AE7A_13AB_4297_AE1E_25B23734F6FA__INCLUDED_)
#define AFX_CAMERA_H__A499AE7A_13AB_4297_AE1E_25B23734F6FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "highgui.h"
#include <vfw.h>

class CCamera  
{
protected:
    CImage m_frame;
    HWND   m_capWnd;
    bool   m_isRunning;
    CAPDRIVERCAPS m_caps;

public:
    CImage& GetFrame() { return m_frame; }
    CCamera();
	virtual ~CCamera();
    
    bool  IsInitialized() { return m_capWnd != 0; };
    bool  IsRunning() { return m_isRunning; };

    virtual void  OnFrame( BYTE* data, int width, int height, int format, int bpp );
    bool  Initialize( int width, int height, int format, HWND parent, int camIndex=-1 );
    void  Uninitialize();

    void  ClearRect();
    void  Start();
    void  Stop();
    void  VideoFormatDlg();
    void  VideoSourceDlg();
    void  UpdateParent( bool whole );
};

#endif // !defined(AFX_CAMERA_H__A499AE7A_13AB_4297_AE1E_25B23734F6FA__INCLUDED_)
