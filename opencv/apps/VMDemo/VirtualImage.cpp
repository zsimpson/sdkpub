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
//M*/// VirtualImage.cpp : implementation file
//

#include "stdafx.h"
#include "VMDemo.h"
#include "VirtualImage.h"
#include "raster.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVirtualImage

CVirtualImage::CVirtualImage()
//	: CDialog(CVirtualImage::IDD, NULL)
{
    HoughLines = 0;
    numHoughLines = 0;
	rasterImage = 0;
    showScanlines = false;
}

/*======================================================================================*/

CVirtualImage::~CVirtualImage()
{
}

/*======================================================================================*/

BEGIN_MESSAGE_MAP(CVirtualImage, CWnd)
    //{{AFX_MSG_MAP(CVirtualImage)
    ON_WM_PAINT()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVirtualImage message handlers

void CVirtualImage::OnPaint() 
{
    CPaintDC dc(this); // device context for painting

    RECT rect;

    GetClientRect(&rect);

    SIZE    size;
    int     n;
    int     x1,y1,x2,y2;
    size.cx = rect.right    - rect.left;
    size.cy = rect.bottom   - rect.top;

    if (rasterImage != 0 ) {
        if (rasterImage->GetImage() != 0)
            rasterImage->Draw(&dc,size);
        else {
            dc.Rectangle(&rect);
        }
    }
    else {
        dc.Rectangle(&rect);
    }

    if (*numScanlines>0 && showScanlines ) {
        CPen pen(PS_SOLID,1,RGB(255,0,0));
        dc.SelectObject(&pen);

        float wf = (float)(rasterImage->GetWidth()-1);
        float hf = (float)(rasterImage->GetHeight()-1);

        for (n = 0; n < *numScanlines; n +=10) {

            x1 = (*Scanlines)[n * 4    ];
            y1 = (*Scanlines)[n * 4 + 1];
            x2 = (*Scanlines)[n * 4 + 2];
            y2 = (*Scanlines)[n * 4 + 3];

            x1 = (int)(x1*size.cx/wf);
            y1 = (int)(y1*size.cy/hf);
            x2 = (int)(x2*size.cx/wf);
            y2 = (int)(y2*size.cy/hf);

            dc.MoveTo(x1,y1);
            dc.LineTo(x2,y2);
        }
    }

    if (HoughLines!=0) {
        int n;
        int w,h;
        int xp[2],yp[2];
        float wf,hf;
        float a,b,c;
        float x,y;
        int currPoint;
        currPoint = 0;
        for(n = 0; n < *numHoughLines; n++) {

            currPoint = 0;
            w = rasterImage->GetWidth();
            h = rasterImage->GetHeight();

            a = (float)(cos((*HoughLines)[n*2+1]));
            b = (float)(sin((*HoughLines)[n*2+1]));
            c = (float)((*HoughLines)[n*2]);


            wf = (float)(w-1);
            hf = (float)(h-1);
            
            /* 1,3 */
            if (b != 0) {

                /* 1 */
                x = 0;
                y = (c/b);
                if (y>=0 && y<=wf) {
                    xp[currPoint] = (int)x;
                    yp[currPoint] = (int)y;
                    currPoint++;
                }

                /* 3 */
                x = wf;
                y=(c-a*wf)/b;
                if (y>=0 && y<=wf) {
                    if (currPoint==0) {
                        xp[currPoint] = (int)x;
                        yp[currPoint] = (int)y;
                        currPoint++;
                    } else {
                        if (x!=xp[0] || y != yp[0] ) {
                            xp[currPoint] = (int)x;
                            yp[currPoint] = (int)y;
                            currPoint++;
                        }
                    }
                }
            }

            /* 2,4 */
            if (a != 0) {

                /* 2 */
                y = 0;
                x = (c/a);
                if (x>=0 && x<=hf && currPoint < 2) {
                    if (currPoint==0) {
                        xp[currPoint] = (int)x;
                        yp[currPoint] = (int)y;
                        currPoint++;
                    } else {
                        if (x!=xp[0] || y != yp[0] ) {
                            xp[currPoint] = (int)x;
                            yp[currPoint] = (int)y;
                            currPoint++;
                        }
                    }
                }

                /* 4 */
                y = hf;
                x=(c-b*hf)/a;
                if (x>=0 && x<=hf && currPoint < 2) {
                    if (currPoint==0) {
                        xp[currPoint] = (int)x;
                        yp[currPoint] = (int)y;
                        currPoint++;
                    } else {
                        if (x!=xp[0] || y != yp[0] ) {
                            xp[currPoint] = (int)x;
                            yp[currPoint] = (int)y;
                            currPoint++;
                        }
                    }
                }
            }

            if (currPoint == 2) {
                x1 = (int)(xp[0]*size.cx/wf);
                y1 = (int)(yp[0]*size.cy/hf);
                x2 = (int)(xp[1]*size.cx/wf);
                y2 = (int)(yp[1]*size.cy/hf);
                dc.MoveTo(x1,y1);
                dc.LineTo(x2,y2);

            }
        }
    }
    return;

}


/*======================================================================================*/

void CVirtualImage::OnSize(UINT nType, int cx, int cy) 
{
    CWnd::OnSize(nType, cx, cy);

    Invalidate();
}


/*======================================================================================*/

int CVirtualImage::SetRasterImage(CRaster *newRasterImage)
{
    rasterImage = newRasterImage;
    Invalidate();
    return 0;
}

/*======================================================================================*/

void CVirtualImage::SetScanlines(int **scan,int *numScan)
{
    Scanlines       = scan;
    numScanlines    = numScan;
}
