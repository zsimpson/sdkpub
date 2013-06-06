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
#include "convert.h"
#include <assert.h>
#include <string.h>

#define Assert assert

/* converting image from depths 8, 24, 32 to 8, 16, 24, 32 */

void icvvConvert( int w, int h, int src_s, int src_d, char* src,
                         int dst_s, int dst_d, char* dst )
{
    int x;
    int y;
    int x3;
    unsigned short val;
    unsigned short v1;
    unsigned short v2;
    unsigned short v3;
   
    Assert( w > 0 );
    Assert( h > 0 );
    Assert( src_s >= w * src_d / 8 );
    Assert( dst_s >= w * dst_d / 8 );
    Assert( src );
    Assert( dst );

    switch(src_d)
    {
        case 8:
            switch(dst_d)
            {
                case 8:
                    for( y = 0; y < h; y++, src += src_s, dst+= dst_s )
                        memcpy( dst, src, w );
                    break;
                case 16:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0; x < w; x++ )
                        {
                            val = (unsigned char)src[x];
                            *(unsigned short*)(dst + x * 2) = ((val & ~3) << 3) +
                                                               (val >> 3) +
                                                               ((val & ~7) << 8);
                        }
                    break;
                case 24:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0, x3 = 0; x < w; x++, x3 += 3 )
                            dst[x3] = dst[x3 + 1] = dst[x3 + 2] = src[x];
                    break;
                case 32:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0; x < w; x++ )
                        {
                            dst[x * 4] = dst[x * 4 + 1] = dst[x * 4 + 2] = src[x];
                            dst[x * 4 + 3] = 0;
                        }
                    break;
            }
            break;

        case 24:
            switch(dst_d)
            {
                case 8:
                    for( y = 0; y < h; y++, src += src_s, dst+= dst_s )
                        for(  x = 0, x3 = 0; x < w; x++, x3 += 3 )
                            dst[x] = (src[x3] + src[x3 + 1] + src[x3 + 2]) / 3;
                    break;
                case 16:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0, x3 = 0; x < w; x++, x3 += 3 )
                        {
                            v1 = (unsigned char)src[x3];
                            v2 = (unsigned char)src[x3 + 1];
                            v3 = (unsigned char)src[x3 + 2];
                            ((unsigned short*)(dst))[x] = (v1 >> 3) +
                                                         ((v2 & ~3) << 3) +
                                                         ((v3 & ~7) << 8);
                        }
                    break;
                case 24:
                    for( y = 0; y < h; y++, src += src_s, dst+= dst_s )
                        memcpy( dst, src, w * 3 );
                    break;
                case 32:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0, x3 = 0; x < w; x++, x3 += 3 )
                        {
                            dst[x * 4] = src[x3];
                            dst[x * 4 + 1] = src[x3 + 1];
                            dst[x * 4 + 2] = src[x3 + 2];
                            dst[x * 4 + 3] = 0;
                        }
                    break;
            }
            break;

        case 32:
            switch(dst_d)
            {
                case 8:
                    for( y = 0; y < h; y++, src += src_s, dst+= dst_s )
                        for( x = 0; x < w; x++ )
                            dst[x] = (src[x * 4] + src[x * 4 + 1] + src[x * 4 + 2]) / 3;
                    break;
                case 16:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0; x < w; x++ )
                        {
                            v1 = (unsigned char)src[x * 4];
                            v2 = (unsigned char)src[x * 4 + 1];
                            v3 = (unsigned char)src[x * 4 + 2];
                            ((unsigned short*)(dst))[x] = (v1 >> 3) + ((v2 & ~3) << 3) + ((v3 & ~7) << 8);
                        }
                    break;
                case 24:
                    for( y = 0; y < h; y++, src += src_s, dst += dst_s )
                        for( x = 0, x3 = 0; x < w; x++, x3 += 3 )
                        {
                            dst[x3]     = src[x * 4];
                            dst[x3 + 1] = src[x * 4 + 1];
                            dst[x3 + 2] = src[x * 4 + 2];
                        }
                    break;
                case 32:
                    for( y = 0; y < h; y++, src += src_s, dst+= dst_s )
                        memcpy( dst, src, w * 4 );
                    break;
            }
            break;

        default:
            return;
    }
}

