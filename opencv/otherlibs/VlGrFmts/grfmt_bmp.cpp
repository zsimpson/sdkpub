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

#include "grfmt_bmp.h"
#include <assert.h>
#include <string.h>

/************************ BMP reader *****************************/

GrFmtBmpReader::GrFmtBmpReader()
{
    m_sign_len = 2;
    m_signature ="BM";
    m_description = "Windows bitmap (*.bmp;*.dib)";
    m_offset = -1;
}


int  GrFmtBmpReader::GetColor()
{
    return m_bpp > 8 ? 1 : -1;
}


void  GrFmtBmpReader::Close()
{
    m_strm.Close();
}


bool  GrFmtBmpReader::ReadHeader()
{
    bool result = false;
    
    assert( strlen(m_filename) != 0 );
    if( !m_strm.Open( m_filename )) return false;

    try
    {
        m_strm.Skip( 10 );
        m_offset = m_strm.GetDWord();

        int  size = m_strm.GetDWord();

        if( size >= 36 )
        {
            m_width  = m_strm.GetDWord();
            m_height = m_strm.GetDWord();
            m_bpp    = m_strm.GetDWord() >> 16;
            m_rle_code = m_strm.GetDWord();
            m_strm.Skip(12);
            int clrused = m_strm.GetDWord();
            m_strm.Skip( size - 36 );

            if( m_width > 0 && m_height > 0 &&
             (((m_bpp == 1 || m_bpp == 4 || m_bpp == 8 || 
                m_bpp == 24 || m_bpp == 32 ) && m_rle_code == 0) || 
               (m_bpp == 4 && m_rle_code == 2) || (m_bpp == 8 && m_rle_code == 1))) 
            {
                if( m_bpp <= 8 )
                {
                    memset( m_palette, 0, sizeof(m_palette));
                    m_strm.GetBytes( m_palette, (clrused == 0? 1<<m_bpp : clrused)*4 );
                }
                result = true;
            }
        }
        else if( size == 12 )
        {
            m_width  = m_strm.GetWord();
            m_height = m_strm.GetWord();
            m_bpp    = m_strm.GetDWord() >> 16;
            m_rle_code = 0;

            if( m_width > 0 && m_height > 0 &&
               (m_bpp == 1 || m_bpp == 4 || m_bpp == 8 ||
                m_bpp == 24 || m_bpp == 32 )) 
            {
                if( m_bpp <= 8 )
                {
                    uchar buffer[256*3];
                    int j, clrused = 1 << m_bpp;
                    m_strm.GetBytes( buffer, clrused*3 );
                    for( j = 0; j < clrused; j++ )
                    {
                        m_palette[j].b = buffer[3*j+0];
                        m_palette[j].g = buffer[3*j+1];
                        m_palette[j].r = buffer[3*j+2];
                    }
                }
                result = true;
            }
        }
    }
    catch( int )
    {
    }

    if( !result )
    {
        m_offset = -1;
        m_width = m_height = -1;
        m_strm.Close();
    }
    return result;
}

bool  GrFmtBmpReader::ReadData( uchar* data, int step, int color )
{
    const  int buffer_size = 1 << 12;
    uchar  buffer[buffer_size];
    uchar  bgr_buffer[buffer_size];
    uchar  gray_palette[256];
    bool   result = false;
    uchar* src = buffer;
    uchar* bgr = bgr_buffer;
    int  src_pitch = ((m_width*m_bpp + 7)/8 + 3) & -4;
    int  nch = color ? 3 : 1;
    int  width3 = m_width*nch;
    int  delta  = -(width3 + step);
    int  y;

    if( m_offset < 0 || !m_strm.IsOpened())
        return false;
    
    data += (m_height - 1)*step;

    if( m_bpp != 24 )
    {
        if( src_pitch+32 > buffer_size ) src = new uchar[src_pitch+32];
    }

    if( !color )
    {
        if( m_bpp <= 8 )
        {
            CvtPaletteToGray( m_palette, gray_palette, 1 << m_bpp );
        }
        if( m_width*3 + 32 > buffer_size ) bgr = new uchar[m_width*3 + 32];
    }
    
    try
    {
        m_strm.SetPos( m_offset );
        
        switch( m_bpp )
        {
        /************************* 1 BPP ************************/
        case 1:
            for( y = 0; y < m_height; y++, data -= step )
            {
                m_strm.GetBytes( src, src_pitch );
                FillColorRow1( color ? data : bgr, src, m_width, m_palette );
                if( !color ) CvtBGRToGray( bgr, data, m_width );
            }
            result = true;
            break;
        
        /************************* 4 BPP ************************/
        case 4:
            if( m_rle_code == 0 )
            {
                for( y = 0; y < m_height; y++, data -= step )
                {
                    m_strm.GetBytes( src, src_pitch );
                    if( color )
                        FillColorRow4( data, src, m_width, m_palette );
                    else
                        FillGrayRow4( data, src, m_width, gray_palette );
                }
                result = true;
            }
            else if( m_rle_code == 2 ) // rle4 compression
            {
                uchar* line_end = data + width3;
                y = 0;

                for(;;)
                {
                    int code = m_strm.GetWord();
                    int len = code & 255;
                    code >>= 8;
                    if( len != 0 ) // encoded mode
                    {
                        PaletteEntry clr[2];
                        int t = 0;
                        clr[0] = m_palette[code >> 4];
                        clr[1] = m_palette[code & 15];
                        uchar* end = data + len*nch;
                        if( end > line_end ) goto decode_rle4_bad;
                        do
                        {
                            if( color )
                            {
                                WRITE_PIX( data, clr[t] );
                            }
                            else
                            {
                                WRITE_PIX( bgr, clr[t] );
                                CvtBGRToGray( bgr, data, 1 );
                            }
                            t ^= 1;
                        }
                        while( (data += nch) < end );
                    }
                    else if( code > 2 ) // absolute mode
                    {
                        if( data + code*nch > line_end ) goto decode_rle4_bad;
                        m_strm.GetBytes( src, (((code + 1)>>1) + 1) & -2 );
                        if( color )
                            data = FillColorRow4( data, src, code, m_palette );
                        else
                            data = FillGrayRow4( data, src, code, gray_palette );
                    }
                    else
                    {
                        if( code == 0 ) // line end
                        {
                            if( data < line_end )
                            {
                                FillUni( data, line_end, width3, delta, 
                                         line_end - data, 0, m_palette[0], color );
                            }
                            data = line_end + delta;
                            line_end = data + width3;
                            if( ++y == m_height ) goto decode_rle4_good;
                        }
                        else if( code == 1 ) // image end
                            goto decode_rle4_good;
                        else // delta
                        {
                            int x_shift3 = m_strm.GetByte()*nch;
                            int y_shift = m_strm.GetByte();

                            if( (y += y_shift) >= m_height ||
                                data + x_shift3 > line_end ) goto decode_rle4_bad;
                            
                            data = FillUni( data, line_end, width3, delta, 
                                             x_shift3, y_shift, m_palette[0], color );
                            line_end -= step*y_shift;
                        }
                    }
                }
decode_rle4_good:
                result = true;
decode_rle4_bad: ;
            }
            break;

        /************************* 8 BPP ************************/
        case 8:
            if( m_rle_code == 0 )
            {
                for( y = 0; y < m_height; y++, data -= step )
                {
                    m_strm.GetBytes( src, src_pitch );
                    if( color )
                        FillColorRow8( data, src, m_width, m_palette );
                    else
                        FillGrayRow8( data, src, m_width, gray_palette );
                }
                result = true;
            }
            else if( m_rle_code == 1 ) // rle8 compression
            {
                uchar* line_end = data + width3;
                y = 0;

                for(;;)
                {
                    int code = m_strm.GetWord();
                    int len = code & 255;
                    code >>= 8;
                    if( len != 0 ) // encoded mode
                    {
                        len *= nch;
                        if( data + len > line_end ) goto decode_rle8_bad;
                        data = FillUni( data, line_end, width3, delta, 
                                         len, 0, m_palette[code], color );
                    }
                    else if( code > 2 ) // absolute mode
                    {
                        int code3 = code*nch;
                        if( data + code3 > line_end ) goto decode_rle8_bad;
                        m_strm.GetBytes( src, (code + 1) & -2 );
                        if( color )
                            data = FillColorRow8( data, src, code, m_palette );
                        else
                            data = FillGrayRow8( data, src, code, gray_palette );
                    }
                    else
                    {
                        if( code == 0 ) // line end
                        {
                            if( data < line_end )
                            {
                                FillUni( data, line_end, width3, delta, 
                                          line_end - data, 0, m_palette[0], color );
                            }
                            data = line_end + delta;
                            line_end = data + width3;
                            if( ++y == m_height ) goto decode_rle8_good;
                        }
                        else if( code == 1 ) // image end
                            goto decode_rle8_good;
                        else // delta
                        {
                            int x_shift3 = m_strm.GetByte()*nch;
                            int y_shift = m_strm.GetByte();

                            if( (y += y_shift) >= m_height ||
                                data + x_shift3 > line_end ) goto decode_rle8_bad;

                            data = FillUni( data, line_end, width3, delta, 
                                             x_shift3, y_shift, m_palette[0], color );
                            line_end -= step*y_shift;
                        }
                    }
                }
decode_rle8_good:
                result = true;
decode_rle8_bad: ;
            }
            break;
        /************************* 24 BPP ************************/
        case 24:
            for( y = 0; y < m_height; y++, data -= step )
            {
                m_strm.GetBytes( color ? data : bgr, src_pitch );
                if( !color ) CvtBGRToGray( bgr, data, m_width );
            }
            result = true;
            break;
        /************************* 32 BPP ************************/
        case 32:
            for( y = 0; y < m_height; y++, data -= step )
            {
                m_strm.GetBytes( src, src_pitch );
                FillRow32( color ? data : bgr, src, m_width );
                if( !color ) CvtBGRToGray( bgr, data, m_width );
            }
            result = true;
            break;
        default:
            assert(0);
        }
    }
    catch( int )
    {
    }

    if( src != buffer ) delete src; 
    if( bgr != bgr_buffer ) delete bgr;
    return true;
}


/************************ Sun Raster reader *****************************/

GrFmtSunRasterReader::GrFmtSunRasterReader()
{
    m_sign_len = 4;
    m_signature ="\x59\xA6\x6A\x95";
    m_description = "Sun raster files (*.sr)";
    m_offset = -1;
}


void  GrFmtSunRasterReader::Close()
{
    m_strm.Close();
}


bool  GrFmtSunRasterReader::ReadHeader()
{
    bool result = false;
    
    assert( strlen(m_filename) != 0 );
    if( !m_strm.Open( m_filename )) return false;

    try
    {
        m_strm.Skip( 4 );
        m_width  = m_strm.GetDWord();
        m_height = m_strm.GetDWord();
        m_bpp    = m_strm.GetDWord();
        int palSize = 3*(1 << m_bpp);

        m_strm.Skip( 4 );
        m_type   = (SunRasType)m_strm.GetDWord();
        m_maptype = (SunRasMapType)m_strm.GetDWord();
        m_maplength = m_strm.GetDWord();

        if( m_width > 0 && m_height > 0 &&
            (m_bpp == 1 || m_bpp == 8 || m_bpp == 24 || m_bpp == 32) &&
            (m_type == RT_OLD || m_type == RT_STANDARD ||
             (m_type == RT_BYTE_ENCODED && m_bpp == 8) || m_type == RT_FORMAT_RGB) &&
            (m_maptype == RMT_NONE && m_maplength == 0 ||
             m_maptype == RMT_EQUAL_RGB && m_maplength == palSize && m_bpp <= 8))
        {
            if( m_maplength != 0 )
            {
                int readed;
                uchar buffer[256*3];

                m_strm.GetBytes( buffer, palSize, &readed );
                if( readed == palSize )
                {
                    int i;
                    palSize /= 3;

                    for( i = 0; i < palSize; i++ )
                    {
                        m_palette[i].b = buffer[i*3 + 2];
                        m_palette[i].g = buffer[i*3 + 1];
                        m_palette[i].r = buffer[i*3];
                        m_palette[i].a = 0;
                    }

                    m_offset = m_strm.GetPos();

                    assert( m_offset == 32 + m_maplength );
                    result = true;
                }
            }
            else
            {
                if( m_bpp <= 8 )
                    FillGrayPalette( m_palette, m_bpp );

                m_offset = m_strm.GetPos();

                assert( m_offset == 32 + m_maplength );
                result = true;
            }
        }
    }
    catch( int )
    {
    }

    if( !result )
    {
        m_offset = -1;
        m_width = m_height = -1;
        m_strm.Close();
    }
    return result;
}


int  GrFmtSunRasterReader::GetColor()
{
    return m_bpp > 8 || m_maptype == RMT_EQUAL_RGB ? 1 : 0;
}


bool  GrFmtSunRasterReader::ReadData( uchar* data, int step, int color )
{
    const  int buffer_size = 1 << 12;
    uchar  buffer[buffer_size];
    uchar  bgr_buffer[buffer_size];
    uchar  gray_palette[256];
    bool   result = false;
    uchar* src = buffer;
    uchar* bgr = bgr_buffer;
    int  src_pitch = ((m_width*m_bpp + 7)/8 + 3) & -4;
    int  nch = color ? 3 : 1;
    int  width3 = m_width*nch;
    int  delta = step - width3;
    int  y;

    if( m_offset < 0 || !m_strm.IsOpened())
        return false;
    
    if( src_pitch+32 > buffer_size )
        src = new uchar[src_pitch+32];

    if( m_width*3 + 32 > buffer_size )
        bgr = new uchar[m_width*3 + 32];

    if( !color && m_maptype == RMT_EQUAL_RGB )
        CvtPaletteToGray( m_palette, gray_palette, 1 << m_bpp );

    try
    {
        m_strm.SetPos( m_offset );
        
        switch( m_bpp )
        {
        /************************* 1 BPP ************************/
        case 1:
            for( y = 0; y < m_height; y++, data += step )
            {
                m_strm.GetBytes( src, src_pitch );
                FillColorRow1( color ? data : bgr, src, m_width, m_palette );
                if( !color ) CvtBGRToGray( bgr, data, m_width );
            }
            result = true;
            break;
        /************************* 8 BPP ************************/
        case 8:
            if( m_type != RT_BYTE_ENCODED )
            {
                for( y = 0; y < m_height; y++, data += step )
                {
                    m_strm.GetBytes( src, src_pitch );
                    if( color )
                        FillColorRow8( data, src, m_width, m_palette );
                    else
                        FillGrayRow8( data, src, m_width, gray_palette );
                }
                result = true;
            }
            else // RLE-encoded
            {
                uchar* line_end = data + width3;
                y = 0;

                for(;;)
                {
                    int max_count = line_end - data;
                    int code = 0, len = 0, len1;
                    uchar* tsrc = src;

                    do
                    {
                        code = m_strm.GetByte();
                        if( code == 0x80 )
                        {
                            len = m_strm.GetByte();
                            if( len != 0 ) break;
                        }
                        *tsrc++ = (uchar)code;
                    }
                    while( (max_count -= nch) > 0 );

                    len1 = tsrc - src;

                    if( len1 > 0 )
                    {
                        if( color )
                            FillColorRow8( data, src, len1, m_palette );
                        else
                            FillGrayRow8( data, src, len1, gray_palette );
                        data += len1*nch;
                    }

                    if( len > 0 ) // encoded mode
                    {
                        int y_shift = 0;
                        len = (len + 1)*nch;
                        code = m_strm.GetByte();

                        CalcShifts( data, line_end, width3, y, m_height, len, y_shift );

                        data = FillUni( data, line_end, width3, delta,
                                        len, y_shift, m_palette[code], color );
                        y += y_shift;
                        line_end += y_shift*step;
                    }

                    if( data == line_end )
                    {
                        data += delta;
                        line_end += step;
                        if( ++y >= m_height ) break;
                    }
                }

                result = true;
            }
            break;
        /************************* 24 BPP ************************/
        case 24:
            for( y = 0; y < m_height; y++, data += step )
            {
                m_strm.GetBytes( color ? data : bgr, src_pitch );

                if( color )
                {
                    if( m_type == RT_FORMAT_RGB )
                        CvtRGBToBGR( data, data, m_width );
                }
                else
                {
                    if( m_type == RT_FORMAT_RGB )
                        CvtRGBToGray( bgr, data, m_width );
                    else
                        CvtBGRToGray( bgr, data, m_width );
                }
            }
            result = true;
            break;
        /************************* 32 BPP ************************/
        case 32:
            for( y = 0; y < m_height; y++, data += step )
            {
                /* hack: a0 b0 g0 r0 a1 b1 g1 r1 ... are written to src + 3,
                   so when we look at src + 4, we see b0 g0 r0 x b1 g1 g1 x ... */
                m_strm.GetBytes( src + 3, src_pitch );
                FillRow32( color ? data : bgr, src + 4, m_width );
                
                if( color )
                {
                    if( m_type == RT_FORMAT_RGB )
                        CvtRGBToBGR( data, data, m_width );
                }
                else
                {
                    if( m_type == RT_FORMAT_RGB )
                        CvtRGBToGray( bgr, data, m_width );
                    else
                        CvtBGRToGray( bgr, data, m_width );
                }
            }
            result = true;
            break;
        default:
            assert(0);
        }
    }
    catch( int )
    {
    }

    if( src != buffer ) delete src; 
    if( bgr != bgr_buffer ) delete bgr;

    return true;
}
