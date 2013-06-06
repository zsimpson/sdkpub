/*M///////////////////////////////////////////////////////////////////////////////////////
//  
//                      INTEL CORPORATION PROPRIETARY INFORMATION              
//         This software is supplied under the terms of a license agreement or 
//         nondisclosure agreement with Intel Corporation and may not be copied
//         or disclosed except in accordance with the terms of that agreement. 
//               Copyright (c) 1999 Intel Corporation. All Rights Reserved.    
//  
//    RCS:
//       Source:    rd_rle.cpp$
//       $Revision: 1.1 $
//      Purpose: 
//      Contents:
//      Authors: Vadim Pisarevsky
//  
//M*/

#include "rd_rle.h"
#include <assert.h>
#include <string.h>

/************************ Common functions *****************************/

static byte* fill_uni( byte* data, byte* line_end, int width3, int delta, 
                       int x_shift3, int y_shift, palette_entry clr, int color )
{
    int new_x3 = (data - (line_end - width3)) + x_shift3;
    byte gr_val = 0;
    if( !color )
    {
        cvt_bgr_to_gray( (byte*)&clr, &gr_val, 1 );
    }

    for(;;)
    {
        if( color )
        {
            for( byte* end = y_shift == 0 ? (line_end - width3) + new_x3 : line_end;
                 data < end; data += 3 )
            {
                WRITE_PIX( data, clr );
            }
        }
        else
        {
            for( byte* end = y_shift == 0 ? (line_end - width3) + new_x3 : line_end;
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


static byte* fill_row32( byte* data, byte* src, int len )
{
    for( byte* end = data + len*3; (data += 3) < end; src += 4 )
    {
        *((palette_entry*)(data-3)) = *((palette_entry*)src);
    }
    palette_entry clr = *((palette_entry*)src);
    WRITE_PIX( data - 3, clr );
    return data;
}


static byte* fill_color_row8( byte* data, byte* indices, int len, palette_entry* palette )
{
    byte* end = data + len*3;
    while( (data += 3) < end )
    {
        *((palette_entry*)(data-3)) = palette[*indices++];
    }
    palette_entry clr = palette[indices[0]];
    WRITE_PIX( data - 3, clr );
    return data;
}
                       

static byte* fill_gray_row8( byte* data, byte* indices, int len, byte* palette )
{
    int i;
    for( i = 0; i < len; i++ )
    {
        data[i] = palette[indices[i]];
    }
    return data + len;
}


static byte* fill_color_row4( byte* data, byte* indices, int len, palette_entry* palette )
{
    byte* end = data + len*3;

    while( (data += 6) < end )
    {
        int idx = *indices++;
        *((palette_entry*)(data-6)) = palette[idx >> 4];
        *((palette_entry*)(data-3)) = palette[idx & 15];
    }

    int idx = indices[0];
    palette_entry clr = palette[idx >> 4];
    WRITE_PIX( data - 6, clr );

    if( data == end )
    {
        clr = palette[idx & 15];
        WRITE_PIX( data - 3, clr );
    }
    return end;
}


static byte* fill_gray_row4( byte* data, byte* indices, int len, byte* palette )
{
    byte* end = data + len;
    while( (data += 2) < end )
    {
        int idx = *indices++;
        data[-2] = palette[idx >> 4];
        data[-1] = palette[idx & 15];
    }

    int idx = indices[0];
    byte clr = palette[idx >> 4];
    data[-2] = clr;

    if( data == end )
    {
        clr = palette[idx & 15];
        data[-1] = clr;
    }
    return end;
}


static byte* fill_row1( byte* data, byte* indices, int len, palette_entry* palette )
{
    byte* end = data + len*3;
    long  clr0 = ((long*)palette)[0];
    long  clr1 = ((long*)palette)[1] ^ clr0;

    while( (data += 24) < end )
    {
        int idx = *indices++;
        *((long*)(data -24)) = (clr1 & (idx & 128 ? -1 : 0)) ^ clr0;
        *((long*)(data -21)) = (clr1 & (idx & 64 ? -1 : 0)) ^ clr0;
        *((long*)(data -18)) = (clr1 & (idx & 32 ? -1 : 0)) ^ clr0;
        *((long*)(data -15)) = (clr1 & (idx & 16 ? -1 : 0)) ^ clr0;
        *((long*)(data -12)) = (clr1 & (idx & 8 ? -1 : 0)) ^ clr0;
        *((long*)(data - 9)) = (clr1 & (idx & 4 ? -1 : 0)) ^ clr0;
        *((long*)(data - 6)) = (clr1 & (idx & 2 ? -1 : 0)) ^ clr0;
        *((long*)(data - 3)) = (clr1 & (idx & 1 ? -1 : 0)) ^ clr0;
    }
    
    int idx = indices[0] << 24;
    for( data -= 24; data < end; data += 3, idx += idx )
    {
        palette_entry clr = palette[idx < 0];
        WRITE_PIX( data, clr );
    }

    return data;
}


/************************ BMP reader *****************************/

grfmt_bmp_reader::grfmt_bmp_reader()
{
    m_sign_len = 2;
    m_signature ="BM";
    m_description = "Windows bitmap (*.bmp;*.dib)";
    m_offset = -1;
    m_width = m_height = -1;
}



int  grfmt_bmp_reader::get_color()
{
    return m_bpp > 8 ? 1 : -1;
}


void  grfmt_bmp_reader::close()
{
    m_strm.close();
}


bool  grfmt_bmp_reader::read_header()
{
    bool result = false;
    
    assert( strlen(m_filename) != 0 );
    if( !m_strm.open( m_filename )) return false;

    try
    {
        m_strm.skeep( 10 );
        m_offset = m_strm.get_dword();

        int  size = m_strm.get_dword();

        if( size >= 36 )
        {
            m_width  = m_strm.get_dword();
            m_height = m_strm.get_dword();
            m_bpp    = m_strm.get_dword() >> 16;
            m_rle_code = m_strm.get_dword();
            m_strm.skeep(12);
            int clrused = m_strm.get_dword();
            m_strm.skeep( size - 36 );

            if( m_width > 0 && m_height > 0 &&
             (((m_bpp == 1 || m_bpp == 4 || m_bpp == 8 || 
                m_bpp == 24 || m_bpp == 32 ) && m_rle_code == 0) || 
               (m_bpp == 4 && m_rle_code == 2) || (m_bpp == 8 && m_rle_code == 1))) 
            {
                if( m_bpp <= 8 )
                {
                    memset( m_palette, 0, sizeof(m_palette));
                    m_strm.get_bytes( m_palette, (clrused == 0? 1<<m_bpp : clrused)*4 );
                }
                result = true;
            }
        }
        else if( size == 12 )
        {
            m_width  = m_strm.get_word();
            m_height = m_strm.get_word();
            m_bpp    = m_strm.get_dword() >> 16;
            m_rle_code = 0;

            if( m_width > 0 && m_height > 0 &&
               (m_bpp == 1 || m_bpp == 4 || m_bpp == 8 ||
                m_bpp == 24 || m_bpp == 32 )) 
            {
                if( m_bpp <= 8 )
                {
                    byte buffer[256*3];
                    int j, clrused = 1 << m_bpp;
                    m_strm.get_bytes( buffer, clrused*3 );
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
        m_strm.close();
    }
    return result;
}

bool  grfmt_bmp_reader::read_data( byte* data, int pitch, int color )
{
    const int buffer_size = 1 << 12;
    byte  buffer[buffer_size];
    byte  bgr_buffer[buffer_size];
    byte  gray_palette[256];
    bool  result = false;
    byte* src = buffer;
    byte* bgr = bgr_buffer;
    int   src_pitch = ((m_width*m_bpp + 7)/8 + 3) & -4;
    int   nch = color ? 3 : 1;
    int   width3 = m_width*nch;
    int   delta  = -(width3 + pitch);
    int   y;

    if( m_offset < 0 || !m_strm.is_opened())
        return false;
    
    data += (m_height - 1)*pitch;

    if( m_bpp != 24 )
    {
        if( src_pitch+32 > buffer_size ) src = new byte[src_pitch+32];
    }

    if( !color )
    {
        if( m_bpp <= 8 )
        {
            cvt_palette_to_gray( m_palette, gray_palette, 1 << m_bpp );
        }
        if( m_width*3 + 32 > buffer_size ) bgr = new byte[m_width*3 + 32];
    }
    
    try
    {
        m_strm.set_pos( m_offset );
        
        switch( m_bpp )
        {
        /************************* 1 BPP ************************/
        case 1:
            for( y = 0; y < m_height; y++, data -= pitch )
            {
                m_strm.get_bytes( src, src_pitch );
                fill_row1( color ? data : bgr, src, m_width, m_palette );
                if( !color ) cvt_bgr_to_gray( bgr, data, m_width );
            }
            result = true;
            break;
        
        /************************* 4 BPP ************************/
        case 4:
            if( m_rle_code == 0 )
            {
                for( y = 0; y < m_height; y++, data -= pitch )
                {
                    m_strm.get_bytes( src, src_pitch );
                    if( color )
                        fill_color_row4( data, src, m_width, m_palette );
                    else
                        fill_gray_row4( data, src, m_width, gray_palette );
                }
                result = true;
            }
            else if( m_rle_code == 2 ) // rle4 compression
            {
                byte* line_end = data + width3;
                y = 0;

                for(;;)
                {
                    int code = m_strm.get_word();
                    int len = code & 255;
                    code >>= 8;
                    if( len != 0 ) // encoded mode
                    {
                        palette_entry clr[2];
                        int t = 0;
                        clr[0] = m_palette[code >> 4];
                        clr[1] = m_palette[code & 15];
                        byte* end = data + len*nch;
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
                                cvt_bgr_to_gray( bgr, data, 1 );
                            }
                            t ^= 1;
                        }
                        while( (data += nch) < end );
                    }
                    else if( code > 2 ) // absolute mode
                    {
                        if( data + code*nch > line_end ) goto decode_rle4_bad;
                        m_strm.get_bytes( src, (((code + 1)>>1) + 1) & -2 );
                        if( color )
                            data = fill_color_row4( data, src, code, m_palette );
                        else
                            data = fill_gray_row4( data, src, code, gray_palette );
                    }
                    else
                    {
                        if( code == 0 ) // line end
                        {
                            if( data < line_end )
                            {
                                fill_uni( data, line_end, width3, delta, 
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
                            int x_shift3 = m_strm.get_byte()*nch;
                            int y_shift = m_strm.get_byte();

                            if( (y += y_shift) >= m_height ||
                                data + x_shift3 > line_end ) goto decode_rle4_bad;
                            
                            data = fill_uni( data, line_end, width3, delta, 
                                             x_shift3, y_shift, m_palette[0], color );
                            line_end -= pitch*y_shift;
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
                for( y = 0; y < m_height; y++, data -= pitch )
                {
                    m_strm.get_bytes( src, src_pitch );
                    if( color )
                        fill_color_row8( data, src, m_width, m_palette );
                    else
                        fill_gray_row8( data, src, m_width, gray_palette );
                }
                result = true;
            }
            else if( m_rle_code == 1 ) // rle8 compression
            {
                byte* line_end = data + width3;
                y = 0;

                for(;;)
                {
                    int code = m_strm.get_word();
                    int len = code & 255;
                    code >>= 8;
                    if( len != 0 ) // encoded mode
                    {
                        len *= nch;
                        if( data + len > line_end ) goto decode_rle8_bad;
                        data = fill_uni( data, line_end, width3, delta, 
                                         len, 0, m_palette[code], color );
                    }
                    else if( code > 2 ) // absolute mode
                    {
                        int code3 = code*nch;
                        if( data + code3 > line_end ) goto decode_rle8_bad;
                        m_strm.get_bytes( src, (code + 1) & -2 );
                        if( color )
                            data = fill_color_row8( data, src, code, m_palette );
                        else
                            data = fill_gray_row8( data, src, code, gray_palette );
                    }
                    else
                    {
                        if( code == 0 ) // line end
                        {
                            if( data < line_end )
                            {
                                fill_uni( data, line_end, width3, delta, 
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
                            int x_shift3 = m_strm.get_byte()*nch;
                            int y_shift = m_strm.get_byte();

                            if( (y += y_shift) >= m_height ||
                                data + x_shift3 > line_end ) goto decode_rle8_bad;

                            data = fill_uni( data, line_end, width3, delta, 
                                             x_shift3, y_shift, m_palette[0], color );
                            line_end -= pitch*y_shift;
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
            for( y = 0; y < m_height; y++, data -= pitch )
            {
                m_strm.get_bytes( color ? data : bgr, src_pitch );
                if( !color ) cvt_bgr_to_gray( bgr, data, m_width );
            }
            result = true;
            break;
        /************************* 32 BPP ************************/
        case 32:
            for( y = 0; y < m_height; y++, data -= pitch )
            {
                m_strm.get_bytes( src, src_pitch );
                fill_row32( color ? data : bgr, src, m_width );
                if( !color ) cvt_bgr_to_gray( bgr, data, m_width );
            }
            result = true;
            break;
        }
    }
    catch( int )
    {
    }

    if( src != buffer ) delete src; 
    if( bgr != bgr_buffer ) delete bgr;
    return true;
}

/************************ Sun raster reader (very simple) *****************************/

grfmt_sun_raster_reader::grfmt_sun_raster_reader()
{
    m_sign_len = 4;
    m_signature ="\x59\xA6\x6A\x95";
    m_description = "Sun raster files (*.sr)";
    m_offset = -1;
    m_width = m_height = -1;
}


void  grfmt_sun_raster_reader::close()
{
    m_strm.close();
}


bool  grfmt_sun_raster_reader::read_header()
{
    bool result = false;
    
    assert( strlen(m_filename) != 0 );
    if( !m_strm.open( m_filename )) return false;

    try
    {
        m_strm.skeep( 4 );
        m_width  = m_strm.get_dword();
        m_height = m_strm.get_dword();
        m_bpp    = m_strm.get_dword();
        m_strm.skeep( 4 );
        int type = m_strm.get_dword();
        m_strm.skeep( 8 );

        if( m_width > 0 && m_height > 0 && m_bpp == 24 && (type == 1 || type == 0))
        {
            m_offset = 32;
            result = true;
        }
    }
    catch( int )
    {
    }

    if( !result )
    {
        m_offset = -1;
        m_width = m_height = -1;
        m_strm.close();
    }
    return result;
}


int  grfmt_sun_raster_reader::get_color()
{
    return m_bpp > 8 ? 1 : 0;
}


bool  grfmt_sun_raster_reader::read_data( byte* data, int pitch, int color )
{
    const int buffer_size = 1 << 12;
    byte  bgr_buffer[buffer_size];
    byte* bgr = bgr_buffer;
    bool  result = false;
    int   src_pitch = ((m_width*m_bpp + 7)/8 + 1) & -2;
    int   y;

    if( m_offset < 0 || !m_strm.is_opened() )
        return false;
    
    if( !color )
    {
        if( m_width*3 + 32 > buffer_size ) bgr = new byte[m_width*3 + 32];        
    }

    try
    {
        m_strm.set_pos( m_offset );
        
        switch( m_bpp )
        {
        /************************* 24 BPP ************************/
        case 24:
            for( y = 0; y < m_height; y++, data += pitch )
            {
                m_strm.get_bytes( color ? data : bgr, src_pitch );
                if( !color ) cvt_bgr_to_gray( bgr, data, m_width );
            }
            result = true;
            break;
        }
    }
    catch( int )
    {
    }

    if( bgr != bgr_buffer ) delete bgr;

    return true;
}
