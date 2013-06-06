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

#include <windows.h>

#include "vlgrfmts.h"
#include "grfmt_base.h"
#include "grfmt_bmp.h"
#include "grfmt_jpeg.h"
#include "grfmt_pxm.h"

static GrFmtReadersList* fmts_list = 0;

static void InitObjects()
{
    if( fmts_list == 0 )
    {
        fmts_list = new GrFmtReadersList;    
        fmts_list->AddReader( new GrFmtBmpReader() );
        fmts_list->AddReader( new GrFmtSunRasterReader() );
        fmts_list->AddReader( new GrFmtJpegReader() );
        fmts_list->AddReader( new GrFmtJpegReader() );
    }
}


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
    hModule, lpReserved, ul_reason_for_call; // unref. params
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            InitObjects();
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}

///////////////// API ///////////////////

DLL_API int gr_fmt_find_filter( const char* file_name )
{
    GrFmtReader* filter = fmts_list->FindReader( file_name );
    if( filter )
    {
        filter->SetFile( file_name );
    }
    return (int)filter;
}


DLL_API int gr_fmt_read_header( int filter, int* width, int* height, int* color )
{
    GrFmtReader* reader = (GrFmtReader*)filter;
    int result = 0;

    if( filter != 0 && width != 0 && height != 0 && reader->ReadHeader())
    {
        *width  = reader->GetWidth();
        *height = reader->GetHeight();
        if( color ) *color  = reader->GetColor();
        result = 1;
    }

    return result;
}


DLL_API int gr_fmt_read_data( int filter, void* data, int step, int color )
{
    GrFmtReader* reader = (GrFmtReader*)filter;
    int result = 0;

    if( filter != 0 && data != 0 && step != 0 && (color&~1) == 0 ||
        step >= ((reader->GetWidth()*(color ? 3 : 1) + 3) & -4))
    {
        result = reader->ReadData( (unsigned char*)data, step, color );
    }

    return result;
}

DLL_API int gr_fmt_close_filter( int filter )
{
    if( filter != 0 ) ((GrFmtReader*)filter)->Close();
    return 1;
}


DLL_API int gr_fmt_write_image( void* src_data, int src_pitch,
                                int width, int height, int color,
                                const char* filename, const char* format )
{
    int result = 0;
    FILE* f = 0;
    int bpp = color ? 24 : 8;
    int dst_pitch = (width*(bpp/8) + 3) & -4;

    if( strcmp( format, "bmp" ) && strcmp( format, "BMP" )) return 0;

    if( !src_data || width <= 0 || height <= 0 || (color&~1) ||
        dst_pitch > src_pitch || !filename ) return 0;
    
    f = fopen( filename, "wb" );
    if( f )
    {
        int bitmap_header_size = 40;
        int palette_size = color ? 0 : 1024;
        int header_size = (14 /* fileheader */ + bitmap_header_size +
                           palette_size + 3) & -4;
        char signature[2] = { 'B', 'M' };
        unsigned char palette[256*4];
        char* data = (char*)src_data;
        int file_header[] = { dst_pitch*height + header_size, 0, header_size };
        int bitmap_header[] = { bitmap_header_size, width, height,
                                1|(bpp << 16), 0, 0, 0, 0, 0, 0 };
        int i;

        fwrite( signature, 1, sizeof(signature), f );
        fwrite( file_header, 1, sizeof(file_header), f );
        fwrite( bitmap_header, 1, bitmap_header_size, f );

        if( !color )
        {
            for( i = 0; i < 256; i++ )
            {
                palette[i*4] = palette[i*4 + 1] = palette[i*4 + 2] = (unsigned char)i;
                palette[i*4 + 3] = 0;
            }
            fwrite( palette, 1, sizeof(palette), f );
        }

        // for alignment
        fwrite( signature, 1, sizeof(signature), f );
        
        data += src_pitch*(height - 1);
        for( i = height; i > 0; i--, data -= src_pitch )
        {
            fwrite( data, 1, dst_pitch, f );
        }
        fclose(f);
        result = 1;
    }
    return result;
}
