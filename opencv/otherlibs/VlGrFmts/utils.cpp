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

#include <assert.h>
#include "utils.h"

#define  SCALE  8
#define  cR  (int)(0.299*(1 << SCALE) + 0.5)
#define  cG  (int)(0.587*(1 << SCALE) + 0.5)
#define  cB  (int)(0.114*(1 << SCALE) + 0.5)

void CvtBGRToGray( const uchar* bgr, uchar* gray, int len )
{
    int i;
    for( i = 0; i < len; i++, bgr += 3 )
    {
        int t = descale( bgr[0]*cB + bgr[1]*cG + bgr[2]*cR, SCALE );
        gray[i] = saturate( t );
    }
}


void CvtRGBToGray( const uchar* rgb, uchar* gray, int len )
{
    int i;
    for( i = 0; i < len; i++, rgb += 3 )
    {
        int t = descale( rgb[2]*cB + rgb[1]*cG + rgb[0]*cR, SCALE );
        gray[i] = saturate( t );
    }
}


void CvtRGBToBGR( const uchar* rgb, uchar* bgr, int len )
{
    int i;

    len *= 3;
    for( i = 0; i < len; i++, rgb += 3, bgr += 3 )
    {
        uchar b, g, r;
        r = rgb[0];
        g = rgb[1];
        b = rgb[2];
        bgr[0] = b;
        bgr[1] = g;
        bgr[2] = r;
    }
}


void CvtPaletteToGray( const PaletteEntry* palette, uchar* grayPalette, int entries )
{
    int i;
    for( i = 0; i < entries; i++ )
    {
        CvtBGRToGray( (uchar*)(palette + i), grayPalette + i, 1 );
    }
}


void  FillGrayPalette( PaletteEntry* palette, int bpp )
{
    int i, length = 1 << bpp, shift = 8 - bpp;

    assert( shift >= 0 );

    for( i = 0; i < length; i++ )
    {
        palette[i].b = palette[i].g = palette[i].r = (uchar)(i << shift);
        palette[i].a = 0;
    }
}

void CalcShifts( uchar* data, uchar* line_end, int width3,
                 int y, int height, int& x_shift3, int& y_shift )
{
    int x3 = data - (line_end - width3);
    int new_x3 = x3 + x_shift3;
    
    y_shift = new_x3 / width3;
    new_x3 -= y_shift * width3;

    x_shift3 = new_x3 - x3;

    if( y + y_shift >= height )
    {
        if( y + y_shift > height )
            y_shift = height - y;
        if( width3 - (line_end - data) + x_shift3 > 0 )
            x_shift3 = (line_end - data) - width3;
    }
}


uchar* FillUni( uchar* data, uchar* line_end, int width3, int delta, 
                       int x_shift3, int y_shift, PaletteEntry clr, int color )
{
    int new_x3 = (data - (line_end - width3)) + x_shift3;
    uchar gr_val = 0;

    if( y_shift < 0 ) // calculate y_shift
    {
        y_shift = new_x3 / width3;
        new_x3 -= y_shift * width3;
    }

    if( !color )
    {
        CvtBGRToGray( (uchar*)&clr, &gr_val, 1 );
    }

    for(;;)
    {
        if( color )
        {
            for( uchar* end = y_shift == 0 ? (line_end - width3) + new_x3 : line_end;
                 data < end; data += 3 )
            {
                WRITE_PIX( data, clr );
            }
        }
        else
        {
            for( uchar* end = y_shift == 0 ? (line_end - width3) + new_x3 : line_end;
                 data < end; data++ )
            {
                *data = gr_val;
            }
        }
        if( y_shift == 0 ) break;
        data = line_end + delta;
        line_end = data + width3;
    }
    return data;
}


uchar* FillRow32( uchar* data, uchar* src, int len )
{
    for( uchar* end = data + len*3; (data += 3) < end; src += 4 )
    {
        *((PaletteEntry*)(data-3)) = *((PaletteEntry*)src);
    }
    PaletteEntry clr = *((PaletteEntry*)src);
    WRITE_PIX( data - 3, clr );
    return data;
}


uchar* FillColorRow8( uchar* data, uchar* indices, int len, PaletteEntry* palette )
{
    uchar* end = data + len*3;
    while( (data += 3) < end )
    {
        *((PaletteEntry*)(data-3)) = palette[*indices++];
    }
    PaletteEntry clr = palette[indices[0]];
    WRITE_PIX( data - 3, clr );
    return data;
}
                       

uchar* FillGrayRow8( uchar* data, uchar* indices, int len, uchar* palette )
{
    int i;
    for( i = 0; i < len; i++ )
    {
        data[i] = palette[indices[i]];
    }
    return data + len;
}


uchar* FillColorRow4( uchar* data, uchar* indices, int len, PaletteEntry* palette )
{
    uchar* end = data + len*3;

    while( (data += 6) < end )
    {
        int idx = *indices++;
        *((PaletteEntry*)(data-6)) = palette[idx >> 4];
        *((PaletteEntry*)(data-3)) = palette[idx & 15];
    }

    int idx = indices[0];
    PaletteEntry clr = palette[idx >> 4];
    WRITE_PIX( data - 6, clr );

    if( data == end )
    {
        clr = palette[idx & 15];
        WRITE_PIX( data - 3, clr );
    }
    return end;
}


uchar* FillGrayRow4( uchar* data, uchar* indices, int len, uchar* palette )
{
    uchar* end = data + len;
    while( (data += 2) < end )
    {
        int idx = *indices++;
        data[-2] = palette[idx >> 4];
        data[-1] = palette[idx & 15];
    }

    int idx = indices[0];
    uchar clr = palette[idx >> 4];
    data[-2] = clr;

    if( data == end )
    {
        clr = palette[idx & 15];
        data[-1] = clr;
    }
    return end;
}


uchar* FillColorRow1( uchar* data, uchar* indices, int len, PaletteEntry* palette )
{
    uchar* end = data + len*3;

    while( (data += 24) < end )
    {
        int idx = *indices++;
        *((PaletteEntry*)(data - 24)) = palette[(idx & 128) != 0];
        *((PaletteEntry*)(data - 21)) = palette[(idx & 64) != 0];
        *((PaletteEntry*)(data - 18)) = palette[(idx & 32) != 0];
        *((PaletteEntry*)(data - 15)) = palette[(idx & 16) != 0];
        *((PaletteEntry*)(data - 12)) = palette[(idx & 8) != 0];
        *((PaletteEntry*)(data - 9)) = palette[(idx & 4) != 0];
        *((PaletteEntry*)(data - 6)) = palette[(idx & 2) != 0];
        *((PaletteEntry*)(data - 3)) = palette[(idx & 1) != 0];
    }
    
    int idx = indices[0] << 24;
    for( data -= 24; data < end; data += 3, idx += idx )
    {
        PaletteEntry clr = palette[idx < 0];
        WRITE_PIX( data, clr );
    }

    return data;
}


uchar* FillGrayRow1( uchar* data, uchar* indices, int len, uchar* palette )
{
    uchar* end = data + len;

    while( (data += 8) < end )
    {
        int idx = *indices++;
        *((uchar*)(data - 8)) = palette[(idx & 128) != 0];
        *((uchar*)(data - 7)) = palette[(idx & 64) != 0];
        *((uchar*)(data - 6)) = palette[(idx & 32) != 0];
        *((uchar*)(data - 5)) = palette[(idx & 16) != 0];
        *((uchar*)(data - 4)) = palette[(idx & 8) != 0];
        *((uchar*)(data - 3)) = palette[(idx & 4) != 0];
        *((uchar*)(data - 2)) = palette[(idx & 2) != 0];
        *((uchar*)(data - 1)) = palette[(idx & 1) != 0];
    }
    
    int idx = indices[0] << 24;
    for( data -= 8; data < end; data++, idx += idx )
    {
        data[0] = palette[idx < 0];
    }

    return data;
}

