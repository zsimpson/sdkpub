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
#include <string.h>

#include "grfmt_jpeg.h"

//////////////////////  JPEG-oriented two-level bitstream ////////////////////////

RMJpegBitStream::RMJpegBitStream()
{
}

RMJpegBitStream::~RMJpegBitStream()
{
}


bool  RMJpegBitStream::Open( const char* filename )
{
    Close();
    Allocate();
    
    m_is_opened = m_low_strm.Open( filename );
    if( m_is_opened ) SetPos(0);
    return m_is_opened;
}


void  RMJpegBitStream::Close()
{
    m_low_strm.Close();
    m_is_opened = false;
}


void  RMJpegBitStream::ReadBlock()
{
    uchar* end = m_start + m_block_size;
    uchar* current = m_start;

    try
    {
        int sz = m_unGetsize;
        memmove( current - sz, m_end - sz, sz );
        while( current < end )
        {
            int val = m_low_strm.GetByte();
            if( val != 0xff )
            {
                *current++ = (uchar)val;
            }
            else
            {
                val = m_low_strm.GetByte();
                if( val == 0 )
                    *current++ = 0xFF;
                else if( !(0xD0 <= val && val <= 0xD7) )
                {
                    m_low_strm.SetPos( m_low_strm.GetPos() - 2 );
                    goto fetch_end;
                }
            }
        }
fetch_end: ;
    }
    catch( int )
    {
        if( current == m_start ) throw;       
    }
    m_current = m_start;
    m_end = m_start + (((current - m_start) + 3) & -4);
    bs_bswap_block( m_start, m_end );
}


void  RMJpegBitStream::Flush()
{
    m_end = m_start + m_block_size;
    m_current = m_end - 4;
    m_bit_idx = 0;
}

void  RMJpegBitStream::AlignOnByte()
{
    m_bit_idx &= -8;
}

int  RMJpegBitStream::FindMarker()
{
    int code = m_low_strm.GetWord();
    while( (code & 0xFF00) != 0xFF00 || (code == 0xFFFF || code == 0xFF00 ))
    {
        code = ((code&255) << 8) | m_low_strm.GetByte();
    }
    return code;
}


/****************************** JPEG (JFIF) reader ***************************/

// zigzag & IDCT prescaling (AAN algorithm) tables
static const uchar zigzag[] =
{
  0,  8,  1,  2,  9, 16, 24, 17, 10,  3,  4, 11, 18, 25, 32, 40,
 33, 26, 19, 12,  5,  6, 13, 20, 27, 34, 41, 48, 56, 49, 42, 35,
 28, 21, 14,  7, 15, 22, 29, 36, 43, 50, 57, 58, 51, 44, 37, 30,
 23, 31, 38, 45, 52, 59, 60, 53, 46, 39, 47, 54, 61, 62, 55, 63,
 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
};

const int idct_prescale[] =
{
  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
  22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
  21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
  19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
  12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
   8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
   4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247
};

#define fixb       8
#define fix(x, n)  (int)((x)*(1 << (n)) + .5)

#define C1_082  fix( 1.082392200, fixb )
#define C1_414  fix( 1.414213562, fixb )
#define C1_847  fix( 1.847759065, fixb )
#define C2_613  fix( 2.613125930, fixb )

#define fixc       10
#define b_cb       fix( 1.772, fixc )
#define g_cb      -fix( 0.34414, fixc )
#define g_cr      -fix( 0.71414, fixc )
#define r_cr       fix( 1.402, fixc )

// IDCT without prescaling
static void aan_idct8x8( int* src, int *dst, int step )
{
    int   workspace[64], *work = workspace;
    int   i;

    /* Pass 1: process rows */
    for( i = 8; i > 0; i--, src += 8, work += 8 )
    {
        /* Odd part */
        int  x0 = src[5], x1 = src[3];
        int  x2 = src[1], x3 = src[7];

        int  x4 = x0 + x1; x0 -= x1;

        x1 = x2 + x3; x2 -= x3;
        x3 = x1 + x4; x1 -= x4;

        x4 = (x0 + x2)*C1_847;
        x0 = descale( x4 - x0*C2_613, fixb);
        x2 = descale( x2*C1_082 - x4, fixb);
        x1 = descale( x1*C1_414, fixb);

        x0 -= x3;
        x1 -= x0;
        x2 += x1;

        work[7] = x3; work[6] = x0;
        work[5] = x1; work[4] = x2;

        x2 = src[2]; x3 = src[6];
        x0 = src[0]; x1 = src[4];

        x4 = x2 + x3;
        x2 = descale((x2-x3)*C1_414, fixb) - x4;

        x3 = x0 + x1; x0 -= x1;
        x1 = x3 + x4; x3 -= x4;
        x4 = x0 + x2; x0 -= x2;

        x2 = work[7];
        x1 -= x2; x2 = 2*x2 + x1;
        work[7] = x1; work[0] = x2;

        x2 = work[6];
        x1 = x4 + x2; x4 -= x2;
        work[1] = x1; work[6] = x4;

        x1 = work[5]; x2 = work[4];
        x4 = x0 + x1; x0 -= x1;
        x1 = x3 + x2; x3 -= x2;

        work[2] = x4; work[5] = x0;
        work[3] = x3; work[4] = x1;
    }

    /* Pass 2: process columns */
    work = workspace;
    for( i = 8; i > 0; i--, dst+=step, work++ )
    {
        /* Odd part */
        int  x0 = work[8*5], x1 = work[8*3];
        int  x2 = work[8*1], x3 = work[8*7];

        int  x4 = x0 + x1; x0 -= x1;
        x1 = x2 + x3; x2 -= x3;
        x3 = x1 + x4; x1 -= x4;

        x4 = (x0 + x2)*C1_847;
        x0 = descale( x4 - x0*C2_613, fixb);
        x2 = descale( x2*C1_082 - x4, fixb);
        x1 = descale( x1*C1_414, fixb);

        x0 -= x3;
        x1 -= x0;
        x2 += x1;

        dst[7] = x3; dst[6] = x0;
        dst[5] = x1; dst[4] = x2;

        x2 = work[8*2]; x3 = work[8*6];
        x0 = work[8*0]; x1 = work[8*4];

        x4 = x2 + x3;
        x2 = descale((x2-x3)*C1_414, fixb) - x4;

        x3 = x0 + x1; x0 -= x1;
        x1 = x3 + x4; x3 -= x4;
        x4 = x0 + x2; x0 -= x2;

        x2 = dst[7];
        x1 -= x2; x2 = 2*x2 + x1;
        x1 = descale(x1,3);
        x2 = descale(x2,3);

        dst[7] = x1; dst[0] = x2;

        x2 = dst[6];
        x1 = descale(x4 + x2,3);
        x4 = descale(x4 - x2,3);
        dst[1] = x1; dst[6] = x4;

        x1 = dst[5]; x2 = dst[4];

        x4 = descale(x0 + x1,3);
        x0 = descale(x0 - x1,3);
        x1 = descale(x3 + x2,3);
        x3 = descale(x3 - x2,3);
       
        dst[2] = x4; dst[5] = x0;
        dst[3] = x3; dst[4] = x1;
    }
}


static const int max_dec_htable_size = 1 << 12;
static const int first_table_bits = 9;

GrFmtJpegReader::GrFmtJpegReader()
{
    m_sign_len = 3;
    m_signature ="\xFF\xD8\xFF";
    m_description = "JFIF files (*.jpeg;*.jpg;*.jpe)";
    m_planes= -1;
    m_offset= -1;

    int i;
    for( i = 0; i < 4; i++ )
    {
        m_td[i] = new short[max_dec_htable_size];
        m_ta[i] = new short[max_dec_htable_size];
    }
}


GrFmtJpegReader::~GrFmtJpegReader()
{
    for( int i = 0; i < 4; i++ )
    {
        delete m_td[i];
        m_td[i] = 0;
        delete m_ta[i];
        m_ta[i] = 0;
    }
}


int  GrFmtJpegReader::GetColor()
{
    return m_planes == 3;
}

void  GrFmtJpegReader::Close()
{
    m_strm.Close();
}

bool GrFmtJpegReader::ReadHeader()
{
    char buffer[16];
    int  i;
    bool result = false, is_jfif = false, is_sof = false, 
         is_qt = false, is_ht = false, is_sos = false;
    
    assert( strlen(m_filename) != 0 );
    if( !m_strm.Open( m_filename )) return false;

    memset( m_is_tq, 0, sizeof(m_is_tq));
    memset( m_is_td, 0, sizeof(m_is_td));
    memset( m_is_ta, 0, sizeof(m_is_ta));
    m_MCUs = 0;

    try
    {
        RMByteStream& lstrm = m_strm.m_low_strm;
        
        lstrm.Skip( 2 ); // skip SOI marker
        
        for(;;)
        {
            int marker = m_strm.FindMarker() & 255;

            // check for standalone markers
            if( marker != 0xD8 /* SOI */ && marker != 0xD9 /* EOI */ &&
                marker != 0x01 /* TEM */ && !( 0xD0 <= marker && marker <= 0xD7 ))
            {
                int pos    = lstrm.GetPos();
                int length = lstrm.GetWord();
            
                switch( marker )
                {
                case 0xE0: // APP0
                    lstrm.GetBytes( buffer, 5 );
                    if( strcmp(buffer, "JFIF") == 0 ) // JFIF identification
                    {
                        m_version = lstrm.GetWord();
                        is_jfif = true;
                    }
                    break;

                case 0xC0: // SOF0
                    m_precision = lstrm.GetByte();
                    m_height = lstrm.GetWord();
                    m_width = lstrm.GetWord();
                    m_planes = lstrm.GetByte();

                    if( m_width == 0 || m_height == 0 || // DNL not supported
                       (m_planes != 1 && m_planes != 3)) goto parsing_end;
                
                    memset( m_ci, -1, sizeof(m_ci));

                    for( i = 0; i < m_planes; i++ )
                    {
                        int idx = lstrm.GetByte();

                        if( idx < 1 || idx > m_planes ) // wrong index
                        {
                            idx = i+1; // hack
                        }
                        cmp_info& ci = m_ci[idx-1];
                        
                        if( ci.tq > 0 /* duplicated description */) goto parsing_end;

                        ci.h = (char)lstrm.GetByte();
                        ci.v = (char)(ci.h & 15);
                        ci.h >>= 4;
                        ci.tq = (char)lstrm.GetByte();
                        if( !((ci.h == 1 || ci.h == 2 || ci.h == 4) &&
                              (ci.v == 1 || ci.v == 2 || ci.v == 4) &&
                              ci.tq < 3) ||
                            // chroma mcu-parts should have equal sizes and
                            // be non greater then luma sizes
                            !( i != 2 || (ci.h == m_ci[1].h && ci.v == m_ci[1].v &&
                                          ci.h <= m_ci[0].h && ci.v <= m_ci[0].v)))
                            goto parsing_end;
                    }
                    is_sof = true;
                    m_type = marker - 0xC0;
                    break;

                case 0xDB: // DQT
                    if( !load_quant_tables( length )) goto parsing_end;
                    is_qt = true;
                    break;

                case 0xC4: // DHT
                    if( !load_huffman_tables( length )) goto parsing_end;
                    is_ht = true;
                    break;

                case 0xDA: // SOS
                    is_sos = true;
                    m_offset = pos - 2;
                    goto parsing_end;

                case 0xDD: // DRI
                    m_MCUs = lstrm.GetWord();
                    break;
                }
                lstrm.SetPos( pos + length );
            }
        }
parsing_end: ;
    }
    catch( int )
    {
    }

    result = is_jfif && is_sof && is_qt && is_ht && is_sos;
    if( !result )
    {
        m_width = m_height = -1;
        m_offset = -1;
        m_strm.Close();
    }
    return result;
}


bool GrFmtJpegReader::load_quant_tables( int length )
{
    uchar buffer[128];
    int  i, tq_size;
    
    RMByteStream& lstrm = m_strm.m_low_strm;
    length -= 2;

    while( length > 0 )
    {
        int tq = lstrm.GetByte();
        int size = tq >> 4;
        tq &= 15;

        tq_size = (64<<size) + 1; 
        if( tq > 3 || size > 1 || length < tq_size ) return false;
        length -= tq_size;

        lstrm.GetBytes( buffer, tq_size - 1 );
        
        if( size == 0 ) // 8 bit quant factors
        {
            for( i = 0; i < 64; i++ )
            {
                int idx = zigzag[i];
                m_tq[tq][idx] = buffer[i] * idct_prescale[idx];
            }
        }
        else // 16 bit quant factors
        {
            for( i = 0; i < 64; i++ )
            {
                int idx = zigzag[i];
                m_tq[tq][idx] = ((unsigned short*)buffer)[i] * 
                                idct_prescale[idx];
            }
        }
        m_is_tq[tq] = true;
    }

    return true;
}


bool GrFmtJpegReader::load_huffman_tables( int length )
{
    const int max_bits = 16;
    uchar buffer[1024];
    int  buffer2[1024];

    int  i, ht_size;
    RMByteStream& lstrm = m_strm.m_low_strm;
    length -= 2;

    while( length > 0 )
    {
        int t = lstrm.GetByte();
        int hclass = t >> 4;
        t &= 15;

        if( t > 3 || hclass > 1 || length < 17 ) return false;
        length -= 17;

        lstrm.GetBytes( buffer, max_bits );
        for( i = 0, ht_size = 0; i < max_bits; i++ ) ht_size += buffer[i];

        if( length < ht_size ) return false;
        length -= ht_size;

        lstrm.GetBytes( buffer + max_bits, ht_size );
        
        if( !::bs_create_decode_huffman_table( 
                  ::bs_create_source_huffman_table( 
                        buffer, buffer2, max_bits, first_table_bits ),
                        hclass == 0 ? m_td[t] : m_ta[t], 
                        max_dec_htable_size )) return false;
        if( hclass == 0 )
            m_is_td[t] = true;
        else
            m_is_ta[t] = true;
    }
    return true;
}


bool GrFmtJpegReader::ReadData( uchar* data, int step, int color )
{
    if( m_offset < 0 || !m_strm.IsOpened())
        return false;

    if( m_precision == 8 )
    {
        for( int i = 0; i < 4; i++ )
            if( m_is_tq[i] )
            {
                for( int j = 0; j < 64; j++ )
                {
                    m_tq[i][j] <<= 4;
                }
            }
    }

    try
    {
        RMByteStream& lstrm = m_strm.m_low_strm;
        lstrm.SetPos( m_offset );

        for(;;)
        {
            int marker = m_strm.FindMarker() & 255;

            if( marker == 0xD8 /* SOI */ || marker == 0xD9 /* EOI */ )
                goto decoding_end;

            // check for standalone markers
            if( marker != 0x01 /* TEM */ && !( 0xD0 <= marker && marker <= 0xD7 ))
            {
                int pos    = lstrm.GetPos();
                int length = lstrm.GetWord();
            
                switch( marker )
                {
                case 0xC4: // DHT
                    if( !load_huffman_tables( length )) goto decoding_end;
                    break;

                case 0xDA: // SOS
                    // read scan header
                    {
                        int idx[3] = { -1, -1, -1 };
                        int i, ns = lstrm.GetByte();
                        int sum = 0, a; // spectral selection & approximation

                        if( ns != m_planes ) goto decoding_end;
                        for( i = 0; i < ns; i++ )
                        {
                            int td, ta, c = lstrm.GetByte() - 1;
                            if( c < 0 || m_planes <= c )
                            {
                                c = i; // hack
                            }
                            
                            if( idx[c] != -1 ) goto decoding_end;
                            idx[i] = c;
                            td = lstrm.GetByte();
                            ta = td & 15;
                            td >>= 4;
                            if( !(ta <= 3 && m_is_ta[ta] && 
                                  td <= 3 && m_is_td[td] &&
                                  m_is_tq[m_ci[c].tq]) )
                                goto decoding_end;

                            m_ci[c].td = (char)td;
                            m_ci[c].ta = (char)ta;

                            sum += m_ci[c].h*m_ci[c].v;
                        }

                        if( sum > 10 ) goto decoding_end;

                        m_ss = lstrm.GetByte();
                        m_se = lstrm.GetByte();

                        a = lstrm.GetByte();
                        m_al = a & 15;
                        m_ah = a >> 4;

                        ProcessScan( idx, ns, data, step, color );
                        goto decoding_end; // only single scan case is supported now
                    }

                    //m_offset = pos - 2;
                    //break;

                case 0xDD: // DRI
                    m_MCUs = lstrm.GetWord();
                    break;
                }
                
                if( marker != 0xDA ) lstrm.SetPos( pos + length );
            }
        }
decoding_end: ;
    }
    catch( int )
    {
    }
    return true;
}


void  GrFmtJpegReader::ResetDecoder()
{
    m_ci[0].dc_pred = m_ci[1].dc_pred = m_ci[2].dc_pred = 0; 
}

void  GrFmtJpegReader::ProcessScan( int* idx, int ns, uchar* data, int step, int color )
{
    int   i, s = 0, mcu, x1 = 0, y1 = 0;
    int   temp[64];
    int   blocks[10][64];
    int   pos[3], h[3], v[3];
    int   x_shift = 0, y_shift = 0;
    int   nch = color ? 3 : 1;

    assert( ns == m_planes && m_ss == 0 && m_se == 63 &&
            m_al == 0 && m_ah == 0 ); // sequental & single scan

    assert( idx[0] == 0 && (ns ==1 || (idx[1] == 1 && idx[2] == 2)));

    for( i = 0; i < ns; i++ )
    {
        int c = idx[i];
        h[c] = m_ci[c].h*8;
        v[c] = m_ci[c].v*8;
        pos[c] = s >> 6;
        s += h[c]*v[c];
    }

    if( ns == 3 )
    {
        x_shift = h[0]/(h[1]*2);
        y_shift = v[0]/(v[1]*2);
    }

    m_strm.Flush();
    ResetDecoder();

    for( mcu = 0;; mcu++ )
    {
        int  x2, y2, x, y;
        int* cmp;
        uchar* data1;
        
        if( mcu == m_MCUs && m_MCUs != 0 )
        {
            ResetDecoder();
            m_strm.AlignOnByte();
            mcu = 0;
        }

        // Get mcu
        for( i = 0; i < ns; i++ )
        {
            int  c = idx[i];
            cmp = blocks[pos[c]];
            for( y = 0; y < v[c]; y += 8, cmp += h[c]*8 )
                for( x = 0; x < h[c]; x += 8 )
                {
                    GetBlock( temp, c );
                    if( i < (color ? 3 : 1))
                    {
                        aan_idct8x8( temp, cmp + x, h[c] );
                    }
                }
        }

        y2 = v[0];
        x2 = h[0];

        if( y1 + y2 > m_height ) y2 = m_height - y1;
        if( x1 + x2 > m_width ) x2 = m_width - x1;

        cmp = blocks[0];
        data1 = data + x1*nch;

        if( ns == 1 )
            for( y = 0; y < y2; y++, data1 += step, cmp += h[0] )
            {
                if( color )
                {
                    for( x = 0; x < x2; x++ )
                    {
                        int val = descale( cmp[x] + 128*4, 2 );
                        data1[x*3] = data1[x*3 + 1] = data1[x*3 + 2] = saturate( val );
                    }
                }
                else
                {
                    for( x = 0; x < x2; x++ )
                    {
                        int val = descale( cmp[x] + 128*4, 2 );
                        data1[x] = saturate( val );
                    }
                }
            }
        else
        {
            for( y = 0; y < y2; y++, data1 += step, cmp += h[0] )
            {
                if( color )
                {
                    int  shift = h[1]*(y >> y_shift);
                    int* cmpCb = blocks[pos[1]] + shift; 
                    int* cmpCr = blocks[pos[2]] + shift;
                    for( x = 0; x < x2; x++ )
                    {
                        int Y  = (cmp[x] + 128*4) << fixc;
                        int Cb = cmpCb[x >> x_shift];
                        int Cr = cmpCr[x >> x_shift];
                        int t = (Y + Cb*b_cb) >> (fixc + 2);
                        data1[x*3] = saturate(t);
                        t = (Y + Cb*g_cb + Cr*g_cr) >> (fixc + 2);
                        data1[x*3 + 1] = saturate(t);
                        t = (Y + Cr*r_cr) >> (fixc + 2);
                        data1[x*3 + 2] = saturate(t);
                    }
                }
                else
                {
                    for( x = 0; x < x2; x++ )
                    {
                        int val = descale( cmp[x] + 128*4, 2 );
                        data1[x] = saturate(val);
                    }
                }
            }
        }

        x1 += h[0];
        if( x1 >= m_width )
        {
            x1 = 0;
            y1 += v[0];
            data += v[0]*step;
            if( y1 >= m_height ) break;
        }
    }
}


void  GrFmtJpegReader::GetBlock( int* block, int c )
{
    memset( block, 0, 64*sizeof(block[0]) );

    assert( 0 <= c && c < 3 );
    const short* td = m_td[m_ci[c].td];
    const short* ta = m_ta[m_ci[c].ta];
    const int* tq = m_tq[m_ci[c].tq];

    // Get DC coefficient
    int i = 0, cat  = m_strm.GetHuff( td );
    int mask = bs_bits_masks[cat];
    int val  = m_strm.Get( cat );

    val -= (val*2 <= mask ? mask : 0);
    m_ci[c].dc_pred = val += m_ci[c].dc_pred;
    
    block[0] = (val * tq[0]) >> 16;

    // Get AC coeffs
    for(;;)
    {
        cat = m_strm.GetHuff( ta );
        if( cat == 0 ) break; // end of block

        i += (cat >> 4) + 1;
        cat &= 15;
        mask = bs_bits_masks[cat];
        val  = m_strm.Get( cat );
        cat  = zigzag[i];
        val -= (val*2 <= mask ? mask : 0);
        block[cat] = (val * tq[cat]) >> 16;
        assert( i <= 63 );
        if( i >= 63 ) break;
    }
}
