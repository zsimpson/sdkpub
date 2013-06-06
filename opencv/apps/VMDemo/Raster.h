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
//M*/#ifndef __RASTER_H_
#define __RASTER_H_

/////////////////////////////////////////////////////////////////////////////
// CRaster document

class CRaster
{
// constructor & destructor
public:
    CRaster();
    ~CRaster();
// members
public:
    BYTE* GetImage();
    int UpdateImage(BYTE* img);
    int CreateRaster(DWORD width, DWORD height, int bitPerPixel);
// members varible
    CString             fileName;
// Implementation method
    int GetNumBitPerPixel();
    unsigned long GetSizeString();
    unsigned long GetHeight();
    unsigned long GetWidth();

    int LoadBMP(const char* cfileName);
    int Draw(CDC* pDC, RECT srcRect, RECT winRect);
    int Draw(CDC* pDC, POINT point,SIZE size);
    int Draw(CDC* pDC);
    int Draw(CDC* pDC, SIZE dstSize);

private:
// members varible
    CPalette*           pal;
    BITMAPINFO*         imgInfo;
    DWORD               flag;
    DWORD               shiftPixel;
    BYTE*               imgDataSave;
    BYTE*               imgData;
    // Data for BMP save
    unsigned long       sizeString;

// Data for drawing // MY
public:
    BITMAPINFO* GetBitmapInfo();
    int     XDest;      // x-coordinate of upper-left corner of dest. rect. 
    int     YDest;      // y-coordinate of upper-left corner of dest. rect. 
    int     DestWidth;  // width of destination rectangle 
    int     DestHeight; // height of destination rectangle 
    int     XSrc;       // x-coordinate of upper-left corner of source rect. 
    int     YSrc;       // y-coordinate of upper-left corner of source rect. 
    int     SrcWidth;   // width of source rectangle 
    int     SrcHeight;  // height of source rectangle 


// Implementation method
    void DeleteAllData();
};

#endif // __RASTER_H_
//end file
