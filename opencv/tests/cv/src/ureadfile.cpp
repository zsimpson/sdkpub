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
#include "cvtest.h"

/* BMP Header structure */
typedef struct _atsBMPHeader
{
    /*unsigned short bfType;*/
    long           bfSize,
                   bfReserved,
                   bfOffBits,
                   biSize,
                   biWidth,
                   biHeight;
    unsigned short biPlanes,
                   biBitCount;
    long           biCompression,
                   biSizeImage,
                   biXPelsPerMeter,
                   biYPelsPerMeter,
                   biClrUsed,
                   biClrImportant;
} atsBMPHeader;


IplImage* atsCreateImageFromFile( const char* filename )
{   
    char  fname[1000];
    char *ext;

    IplImage* img = 0;
    FILE* file;
    
    ext = strrchr( filename, '.' );
    
    if( !ext || (strcmp( ext, ".BMP" ) && strcmp( ext, ".bmp" )))
    {
        strcpy( fname, filename );
        strcat( fname, ".bmp" );
        filename = fname;
    }

    file = fopen( filename, "rb" );

    if( file )
    {
        char  bmp_sign[] = "BM\0";
        atsBMPHeader header;

        /* check BMP signature */
        if( fread( bmp_sign, 2, 1, file ) && !strcmp( bmp_sign, "BM" ))
        {
            /* read header information */
            fread( &header, sizeof(header), 1, file );

            if( header.biSize >= 40 && header.biCompression == 0 &&
                (header.biBitCount == 8 || header.biBitCount == 24))
            {
                int nch = header.biBitCount / 8;
                int i, row_length = (header.biWidth * nch + 3) & -4;

                fseek( file, header.bfOffBits, 0 );

                img = atsCreateImage( header.biWidth, header.biHeight,
                                      IPL_DEPTH_8U, nch, 0 );

                strncpy( img->colorModel, nch == 3 ? "RGB" : "GRAY", 4 );
                strncpy( img->channelSeq, nch == 3 ? "BGR" : "GRAY", 4 );

                for( i = 0; i < header.biHeight; i++ )
                {
                    fread( img->imageData + (img->height - i - 1)*img->widthStep,
                           row_length, 1, file );
                }
            }
        }

        fclose( file );
    }
    
    return img;
}    

/* End of file. */

