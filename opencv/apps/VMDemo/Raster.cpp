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
//M*/// RasterDoc.cpp : implementation file
//

#include "stdafx.h"
#include "Raster.h"

 
/////////////////////////////////////////////////////////////////////////////
// CRaster

/*======================================================================================*/

CRaster::CRaster()
{
    imgDataSave     = NULL;
    imgData         = NULL;
    imgInfo         = NULL;
    pal             = NULL;

    XDest           = 0;
    YDest           = 0;
    DestWidth       = 0;
    DestHeight      = 0;
    XSrc            = 0;
    YSrc            = 0;
    SrcWidth        = 0;
    SrcHeight       = 0;

    fileName        = "Default.bmp";
    flag            = 0;
}/* CRaster::CRaster */


/*======================================================================================*/

CRaster::~CRaster()
{
    DeleteAllData();
}/* CRaster::~CRaster */


/*======================================================================================*/

int CRaster::CreateRaster(DWORD width, DWORD height, int bitPerPixel)
{
    DWORD               numColor;
    LOGPALETTE          *logPal;
    switch(bitPerPixel) {
    case 1:
        shiftPixel  = (width + 7) / 8;
        break;
    case 4:
        shiftPixel  = (width + 1) / 2;
        break;
    case 8:
        shiftPixel  = width;
        break;
    case 24:
        shiftPixel  = width * 3;
        break;
    default:
        return -1;
    }/* switch */

    if(flag) {
        DeleteAllData();
    }/* if */

    numColor = 1 << bitPerPixel;

    if(	bitPerPixel == 1 ||
        bitPerPixel == 4 ||
        bitPerPixel == 8) { // type of bitmap

        imgInfo = (BITMAPINFO*)malloc(  sizeof(BITMAPINFO) 
                                        + sizeof(RGBQUAD) * numColor);
    // Create Palette for 1<<bitCount colors
        pal     = new CPalette();
        logPal  = (LOGPALETTE*)calloc(  1, sizeof(LOGPALETTE) 
                                        + sizeof(PALETTEENTRY) * numColor);
        logPal->palVersion      = 0x300;
        logPal->palNumEntries   = (WORD)numColor;

        for(DWORD Index = 0; Index < numColor; Index++) {
            logPal->palPalEntry[Index].peRed    = (BYTE)Index;
            logPal->palPalEntry[Index].peGreen  = (BYTE)Index;
            logPal->palPalEntry[Index].peBlue   = (BYTE)Index;
        }/* for */

        pal->CreatePalette(logPal);
        free(logPal);
    } else
        if( bitPerPixel == 24 ) {
            imgInfo = (BITMAPINFO*)malloc(  sizeof(BITMAPINFO) 
                                            + sizeof(RGBQUAD));
    }/* if */

    sizeString  = (shiftPixel + 3) / 4 * 4; // Attention !!! divided 4 !!!;

    imgInfo = (BITMAPINFO*)calloc(  sizeof(BITMAPINFO) + sizeof(RGBQUAD), 1);
    imgInfo->bmiHeader.biSize           = sizeof(BITMAPINFOHEADER);
    imgInfo->bmiHeader.biWidth          = width;
    imgInfo->bmiHeader.biHeight         = -(int)(height);
    imgInfo->bmiHeader.biPlanes         = 1;
    imgInfo->bmiHeader.biBitCount       = WORD(bitPerPixel);
    imgInfo->bmiHeader.biCompression    = BI_RGB;
    imgInfo->bmiHeader.biSizeImage      = sizeString*height;

    imgDataSave     = new BYTE[sizeString*height];
    imgData         = new BYTE[sizeString*height];

    return 1;
}/* CRaster::CreateRaster */


/*======================================================================================*/

int CRaster::UpdateImage(BYTE* imgSrc)
{
    BYTE* imgDst = imgData;
    if(!imgSrc){
        imgSrc = imgDataSave;
    }/* if */

    for(DWORD index = 0; index < (DWORD)abs(imgInfo->bmiHeader.biHeight); index++){
        memcpy( imgDst, imgSrc, shiftPixel);
        imgDst  +=  sizeString;
        imgSrc  +=  sizeString;
    }/* for */
    return 1;
}/* CRaster::UpdateImage */


/*======================================================================================*/

int CRaster::LoadBMP(const char* cfileName)
{
    CFile   file;
    BITMAPFILEHEADER    fileHeader;
    BITMAPINFOHEADER    infoHeader;
    DWORD               width, height;

    LOGPALETTE          *logPal;

    DWORD               Index;
    WORD                bitCount;
    BYTE*               tempImage;

    if(flag) {
        DeleteAllData();
    }/* if */

    if(file.Open(cfileName, CFile::modeRead, NULL) == 0)
        return -1;

    fileName    = cfileName; 

    file.Read(&fileHeader, sizeof(BITMAPFILEHEADER));
    if(fileHeader.bfType != 0x4d42) {
        file.Close();
        return -1;
    } /* if... it's not BMP */

// Load bitmap info
    file.Read(&infoHeader, sizeof(BITMAPINFOHEADER));
    bitCount    = infoHeader.biBitCount;
    if(infoHeader.biCompression != BI_RGB ) {
        file.Close();
        return -2;
    }/* if */
    if( bitCount == 1 ||
        bitCount == 4 ||
        bitCount == 8) { // type of bitmap

        DWORD numColor = infoHeader.biClrUsed;
        if(numColor == 0) {
            numColor = 1<<bitCount;
        }

        imgInfo = (BITMAPINFO*)malloc(  sizeof(BITMAPINFO) 
                                        + sizeof(RGBQUAD) * (1<<bitCount));
        file.Read(imgInfo->bmiColors, sizeof(RGBQUAD) * numColor);

    // Create Palette for 1<<bitCount colors
        pal     = new CPalette();
        logPal  = (LOGPALETTE*)
                    calloc( 1,  sizeof(LOGPALETTE) 
                                    + sizeof(PALETTEENTRY) * (1<<bitCount));

        logPal->palVersion      = 0x300;
        logPal->palNumEntries   = BYTE(1<<bitCount);

        for(Index = 0; Index < numColor; Index++) {

            logPal->palPalEntry[Index].peRed    =
                imgInfo->bmiColors[Index].rgbRed;

            logPal->palPalEntry[Index].peGreen	=
                imgInfo->bmiColors[Index].rgbGreen;

            logPal->palPalEntry[Index].peBlue   =
                imgInfo->bmiColors[Index].rgbBlue;
        }/* for */

        pal->CreatePalette(logPal);
        free(logPal);
    } else if(  bitCount == 24 ) {
        imgInfo = (BITMAPINFO*)malloc(  sizeof(BITMAPINFO) 
                                        + sizeof(RGBQUAD));
    } else {
        file.Close();
        return -2;
    } /* if... not support BMP */

    imgInfo->bmiHeader	= infoHeader;

// Load image data
    width   = imgInfo->bmiHeader.biWidth;
    height  = abs(imgInfo->bmiHeader.biHeight);

    switch(bitCount) {
    case 1:
        shiftPixel  = (width + 7) / 8;
        break;
    case 4:
        shiftPixel  = (width + 1) / 2;
        break;
    case 8:
        shiftPixel  = width;
        break;
    case 24:
        shiftPixel  = width * 3;
        break;
    }/* switch */

    DestWidth   = width;
    DestHeight  = height;
    SrcWidth    = width;
    SrcHeight   = height;

    sizeString  = (shiftPixel + 3) / 4 * 4;	// Attention !!! divided 4 !!!;

    tempImage       = new BYTE[sizeString*height];
    imgData         = new BYTE[sizeString*height];
    imgDataSave     = tempImage;

    for(Index = 0; Index < height; Index++) {
        file.Read(tempImage, sizeString);
        tempImage+=sizeString;
    }/* for */

    imgInfo->bmiHeader.biHeight = -abs(imgInfo->bmiHeader.biHeight);

    UpdateImage(0);
    flag    = 1;
    file.Close();
    return 1;
}/* CRaster::LoadBMP */


/*======================================================================================*/

int CRaster::Draw(CDC* pDC) 
{
    HDC         hDC;
    CPalette*   oldPal;

    oldPal  = 0;
    hDC     =   pDC->m_hDC;
    if(pal) {
        oldPal  =   pDC->SelectPalette(pal, TRUE);
    }/* if */

    pDC->SetStretchBltMode(COLORONCOLOR);

    StretchDIBits(  hDC, 
                    XDest,          YDest, 
                    DestWidth,      DestHeight,
                    XSrc,           YSrc,
                    SrcWidth,       SrcHeight,
                    imgData,        imgInfo,
                    DIB_RGB_COLORS, SRCCOPY);

    if(pal) {
        pDC->SelectPalette(oldPal, TRUE);
    }/* if */

    return 1;
}/* CRaster::Draw */


/*======================================================================================*/
int CRaster::Draw(CDC* pDC, RECT , RECT) 
{
    HDC         hDC;
    CPalette*   oldPal;

    oldPal  = 0;

    hDC     =   pDC->m_hDC;
    if(pal) {
        oldPal  =   pDC->SelectPalette(pal, TRUE);
    }/* if */

    pDC->SetStretchBltMode(COLORONCOLOR);

    StretchDIBits(  hDC, 
                    XDest,          YDest, 
                    DestWidth,      DestHeight,
                    XSrc,           YSrc,
                    SrcWidth,       SrcHeight,
                    imgData,        imgInfo,
                    DIB_RGB_COLORS, SRCCOPY);

    if(pal) {
        pDC->SelectPalette(oldPal, TRUE);
    }/* if */

    return 1;
}/* CRaster::Draw */


/*======================================================================================*/

int CRaster::Draw(CDC* pDC, SIZE dstSize) 
{
    HDC         hDC;
    CPalette*   oldPal;

    oldPal  = 0;

    hDC     =   pDC->m_hDC;
    if(pal) {
        oldPal  =   pDC->SelectPalette(pal, TRUE);
    }/* if */

    pDC->SetStretchBltMode(COLORONCOLOR);

    ::StretchDIBits(  hDC, 
                    0,          0, 
                    dstSize.cx,     dstSize.cy,
                    0,          0,
                    GetWidth(),     GetHeight(),
                    imgData,        imgInfo,
                    DIB_RGB_COLORS, SRCCOPY);

    if(pal) {
        pDC->SelectPalette(oldPal, TRUE);
    }/* if */

    return 1;
}/* CRaster::Draw */


/*======================================================================================*/

int CRaster::Draw(CDC* pDC, POINT point,SIZE size) 
{
    HDC         hDC;
    CPalette*   oldPal;

    oldPal  = 0;

    hDC     =   pDC->m_hDC;
    if(pal) {
        oldPal  =   pDC->SelectPalette(pal, TRUE);
    }/* if */

    pDC->SetStretchBltMode(COLORONCOLOR);

    StretchDIBits(  hDC, 
                    point.x,        point.y, 
                    size.cx,        size.cy,
                    XSrc,           YSrc,
                    SrcWidth,       SrcHeight,
                    imgData,        imgInfo,
                    DIB_RGB_COLORS, SRCCOPY);

    if(pal) {
        pDC->SelectPalette(oldPal, TRUE);
    }/* if */

    return 1;
}/* CRaster::Draw */


/*======================================================================================*/

void CRaster::DeleteAllData()
{
    if(imgData)
        delete imgData;

    if(imgDataSave)
        delete imgDataSave;

    if(imgInfo)
        free(imgInfo);

    if(pal)
        delete pal;

    imgData         = NULL;
    imgDataSave     = NULL;
    imgInfo         = NULL;
    pal             = NULL;
    flag            = 0;
}/* CRaster::DeleteAllData */


/*======================================================================================*/

unsigned long CRaster::GetWidth()
{
    return imgInfo->bmiHeader.biWidth;
}/* CRaster::GetWidth */


/*======================================================================================*/

unsigned long CRaster::GetHeight()
{
    return abs(imgInfo->bmiHeader.biHeight);
}/* CRaster::GetHeight */


/*======================================================================================*/

unsigned long CRaster::GetSizeString()
{
    return sizeString;
}/* CRaster::GetSizeString */


/*======================================================================================*/

BYTE* CRaster::GetImage()
{
    return imgData;
}/* CRaster::GetImage */


/*======================================================================================*/

int CRaster::GetNumBitPerPixel()
{
    return imgInfo->bmiHeader.biBitCount;
}/* CRaster::GetNumBitPerPixel */


/*======================================================================================*/

BITMAPINFO* CRaster::GetBitmapInfo()
{
    return imgInfo;
}/* CRaster::GetBitmapInfo */


/*======================================================================================*/
