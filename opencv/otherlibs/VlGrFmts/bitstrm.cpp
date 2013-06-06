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
#include "bitstrm.h"

#define  BS_DEF_BLOCK_SIZE   (1<<15)

typedef unsigned long ulong;

ulong bs_bits_masks[] = {
    0,
    0x00000001, 0x00000003, 0x00000007, 0x0000000F,
    0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF,
    0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF,
    0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF,
    0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF,
    0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF,
    0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF,
    0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF
};

#define BSWAP(v)     ((v<<24)|((v&0xff00)<<8)|((v>>8)&0xff00)|(v>>24))

void bs_bswap_block( uchar *start, uchar *end )
{
    ulong* data = (ulong*)start;
    int    i, size = (end - start+3)/4;

    for( i = 0; i < size; i++ )
    {
        ulong temp = data[i];
        temp = BSWAP( temp );
        data[i] = temp;
    }
}


/////////////////////////  RBaseStream ////////////////////////////

bool  RBaseStream::IsOpened()
{ 
    return m_is_opened;
}

void  RBaseStream::Allocate()
{
    if( !m_start )
    {
        m_start = new uchar[m_block_size + m_unGetsize];
        m_start+= m_unGetsize;
    }
    m_end = m_start + m_block_size;
    m_current = m_end;
}


RBaseStream::RBaseStream()
{
    m_start  = m_end = m_current = 0;
    m_file   = 0;
    m_block_size = BS_DEF_BLOCK_SIZE;
    m_unGetsize = 4; // 32 bits
    m_is_opened  = false;
}


RBaseStream::~RBaseStream()
{
    Close();    // Close files
    Release();  // free  buffers
}


void  RBaseStream::ReadBlock()
{
    int readed;
    assert( m_file != 0 );

    // copy unget buffer
    if( m_start )
    {
        memcpy( m_start - m_unGetsize, m_end - m_unGetsize, m_unGetsize );
    }

    SetPos( GetPos() ); // normalize position

    fseek( m_file, m_block_pos, SEEK_SET );
    readed = fread( m_start, 1, m_block_size, m_file );
    m_end = m_start + readed;
    m_current   -= m_block_size;
    m_block_pos += m_block_size;

    if( readed == 0 || m_current >= m_end ) throw RBS_THROW_EOS;
}


bool  RBaseStream::Open( const char* filename )
{
    Close();
    Allocate();
    
    m_file = fopen( filename, "rb" );
    
    if( m_file )
    {
        m_is_opened = true;
        SetPos(0);
    }
    return m_file != 0;
}

void  RBaseStream::Close()
{
    if( m_file )
    {
        fclose( m_file );
        m_file = 0;
    }
    m_is_opened = false;
}


void  RBaseStream::Release()
{
    if( m_start )
    {
        delete (m_start - m_unGetsize);
    }
    m_start = m_end = m_current = 0;
}


void  RBaseStream::SetBlockSize( int block_size, int unGetsize )
{
    assert( unGetsize >= 0 && block_size > 0 &&
           (block_size & (block_size-1)) == 0 );

    if( m_start && block_size == m_block_size && unGetsize == m_unGetsize ) return;
    Release();
    m_block_size = block_size;
    m_unGetsize = unGetsize;
    Allocate();
}


void  RBaseStream::SetPos( int pos )
{
    int offset = pos & (m_block_size - 1);
    int block_pos = pos - offset;
    
    assert( IsOpened() && pos >= 0 );
    
    if( m_current < m_end && block_pos == m_block_pos - m_block_size )
    {
        m_current = m_start + offset;
    }
    else
    {
        m_block_pos = block_pos;
        m_current = m_start + m_block_size + offset;
    }
}


int  RBaseStream::GetPos()
{
    assert( IsOpened() );
    return m_block_pos - m_block_size + (m_current - m_start);
}

void  RBaseStream::Skip( int bytes )
{
    assert( bytes >= 0 );
    m_current += bytes;
}

/////////////////////////  RLByteStream ////////////////////////////

int  RLByteStream::GetByte()
{
    uchar *current = m_current;
    int   val;

    if( current >= m_end )
    {
        ReadBlock();
        current = m_current;
    }

    val = *((uchar*)current);
    m_current = current + 1;
    return val;
}


void  RLByteStream::GetBytes( void* buffer, int length, int* readed )
{
    uchar*  data = (uchar*)buffer;
    assert( length >= 0 );
    
    if( readed) *readed = 0;

    while( length > 0 )
    {
        int l;

        for(;;)
        {
            l = m_end - m_current;
            if( l > length ) l = length;
            if( l > 0 ) break;
            ReadBlock();
        }
        memcpy( data, m_current, l );
        m_current += l;
        length -= l;
        data += l;
        if( readed ) *readed += l;
    }
}


////////////  RLByteStream & RMByteStream <Get[d]word>s ////////////////

int  
#ifdef LITTLE_ENDIAN
    RLByteStream
#else
    RMByteStream
#endif
::GetWord()
{
    uchar *current = m_current;
    int   val;

    if( current+1 < m_end )
    {
        val = *((unsigned short*)current);
        m_current = current + 2;
    }
    else
    {
        val = GetByte();
        val|= GetByte() << 8;
    }
    return val;
}


int  
#ifdef BIG_ENDIAN
    RLByteStream
#else
    RMByteStream
#endif
::GetWord()
{
    uchar *current = m_current;
    int   val;

    if( current+1 < m_end )
    {
        val = *((unsigned short*)current);
        m_current = current + 2;
        val = (val >> 8)|((val & 255) << 8);
    }
    else
    {
        val = GetByte() << 8;
        val|= GetByte();
    }
    return val;
}


int  
#ifdef LITTLE_ENDIAN
    RLByteStream
#else
    RMByteStream
#endif
::GetDWord()
{
    uchar *current = m_current;
    int   val;

    if( current+3 < m_end )
    {
        val = *((int*)current);
        m_current = current + 4;
    }
    else
    {
        GetBytes( &val, 4 );
    }
    return val;
}

int  
#ifdef BIG_ENDIAN
    RLByteStream
#else
    RMByteStream
#endif
::GetDWord()
{
    uchar *current = m_current;
    int   val;

    if( current+3 < m_end )
    {
        val = *((int*)current);
        m_current = current + 4;
    }
    else
    {
        GetBytes( &val, 4 );
    }
    return BSWAP(val);
}


/////////////////////////  RLBitStream ////////////////////////////

void  RLBitStream::ReadBlock()
{
    RBaseStream::ReadBlock();
#ifdef  BIG_ENDIAN
    bs_bswap_block( m_start, m_end );
#endif
}


void  RLBitStream::SetPos( int pos )
{
    RBaseStream::SetPos(pos);
    int offset = m_current - m_end;
    m_current = m_end + (offset & -4);
    m_bit_idx = (offset&3)*8;
}


int  RLBitStream::GetPos()
{
    return RBaseStream::GetPos() + (m_bit_idx >> 3);
}


int  RLBitStream::Get( int bits )
{
    int    bit_idx     = m_bit_idx;
    int    new_bit_idx = bit_idx + bits;
    int    mask    = new_bit_idx >= 32 ? -1 : 0;
    ulong* current = (ulong*)m_current;

    if( (m_current = (uchar*)(current - mask)) >= m_end )
    {
        ReadBlock();
        current = ((ulong*)m_current) + mask;
    }
    m_bit_idx = new_bit_idx & 31;
    return ((current[0] >> bit_idx) |
           ((current[1] <<-bit_idx) & mask)) & bs_bits_masks[bits];
}

int  RLBitStream::Show( int bits )
{
    int    bit_idx = m_bit_idx;
    int    new_bit_idx = bit_idx + bits;
    int    mask    = new_bit_idx >= 32 ? -1 : 0;
    ulong* current = (ulong*)m_current;

    if( (uchar*)(current - mask) >= m_end )
    {
        ReadBlock();
        current = ((ulong*)m_current) + mask;
        m_current = (uchar*)current;
    }
    return ((current[0] >> bit_idx) |
           ((current[1] <<-bit_idx) & mask)) & bs_bits_masks[bits];
}


void  RLBitStream::Move( int shift )
{
    int new_bit_idx = m_bit_idx + shift;
    m_current += (new_bit_idx >> 5) << 2;
    m_bit_idx  = new_bit_idx & 31;
}


int  RLBitStream::GetHuff( const short* table )
{
    int  val;
    int  code_bits;

    for(;;)
    {
        int table_bits = table[0];
        val = table[Show(table_bits) + 2];
        code_bits = val & 15;
        val >>= 4;

        if( code_bits != 0 ) break;
        table += val*2;
        Move( table_bits );
    }

    Move( code_bits );
    if( val == RBS_HUFF_FORB ) throw RBS_THROW_FORB;

    return val;
}

void  RLBitStream::Skip( int bytes )
{
    Move( bytes*8 );
}

/////////////////////////  RMBitStream ////////////////////////////

void  RMBitStream::ReadBlock()
{
    RBaseStream::ReadBlock();
#ifdef  LITTLE_ENDIAN
    bs_bswap_block( m_start, m_end );
#endif
}


void  RMBitStream::SetPos( int pos )
{
    RBaseStream::SetPos(pos);
    int offset = m_current - m_end;
    m_current = m_end + ((offset - 1) & -4);
    m_bit_idx = (32 - (offset&3)*8) & 31;
}


int  RMBitStream::GetPos()
{
    return RBaseStream::GetPos() + ((32 - m_bit_idx) >> 3);
}


int  RMBitStream::Get( int bits )
{
    int    bit_idx = m_bit_idx - bits;
    int    mask    = bit_idx >> 31;
    ulong* current = ((ulong*)m_current) - mask;

    if( (m_current = (uchar*)current) >= m_end )
    {
        ReadBlock();
        current = (ulong*)m_current;
    }
    m_bit_idx = bit_idx &= 31;
    return (((current[-1] << -bit_idx) & mask)|
             (current[0] >> bit_idx)) & bs_bits_masks[bits];
}


int  RMBitStream::Show( int bits )
{
    int    bit_idx = m_bit_idx - bits;
    int    mask    = bit_idx >> 31;
    ulong* current = ((ulong*)m_current) - mask;

    if( ((uchar*)current) >= m_end )
    {
        m_current = (uchar*)current;
        ReadBlock();
        current = (ulong*)m_current;
        m_current -= 4;
    }
    return (((current[-1]<<-bit_idx) & mask)|
             (current[0] >> bit_idx)) & bs_bits_masks[bits];
}


int  RMBitStream::GetHuff( const short* table )
{
    int  val;
    int  code_bits;

    for(;;)
    {
        int table_bits = table[0];
        val = table[Show(table_bits) + 1];
        code_bits = val & 15;
        val >>= 4;

        if( code_bits != 0 ) break;
        table += val;
        Move( table_bits );
    }

    Move( code_bits );
    if( val == RBS_HUFF_FORB )
        throw RBS_THROW_FORB;

    return val;
}


void  RMBitStream::Move( int shift )
{
    int new_bit_idx = m_bit_idx - shift;
    m_current -= (new_bit_idx >> 5)<<2;
    m_bit_idx  = new_bit_idx & 31;
}


void  RMBitStream::Skip( int bytes )
{
    Move( bytes*8 );
}


static const int huff_val_shift = 20, huff_code_mask = (1 << huff_val_shift) - 1;

bool bs_create_decode_huffman_table( const int* src, short* table, int max_size )
{   
    const int forbidden_entry = (RBS_HUFF_FORB << 4)|1;
    int       first_bits = src[0];
    struct
    {
        int bits;
        int offset;
    }
    sub_tables[1 << 11];
    int  size = (1 << first_bits) + 1;
    int  i, k;
    
    /* calc bit depths of sub tables */
    memset( sub_tables, 0, (1 << first_bits)*sizeof(sub_tables[0]) );
    for( i = 1, k = 1; src[k] >= 0; i++ )
    {
        int code_count = src[k++];
        int sb = i - first_bits;
        
        if( sb <= 0 )
            k += code_count;
        else
            for( code_count += k; k < code_count; k++ )
            {
                int  code = src[k] & huff_code_mask;
                sub_tables[code >> sb].bits = sb;
            }
    }

    /* calc offsets of sub tables and whole size of table */
    for( i = 0; i < (1 << first_bits); i++ )
    {
        int b = sub_tables[i].bits;
        if( b > 0 )
        {
            b = 1 << b;
            sub_tables[i].offset = size;
            size += b + 1;
        }
    }

    if( size > max_size )
    {
        assert(0);
        return false;
    }

    /* fill first table and subtables with forbidden values */
    for( i = 0; i < size; i++ )
    {
        table[i] = (short)forbidden_entry;
    }

    /* write header of first table */
    table[0] = (short)first_bits;

    /* fill first table and sub tables */ 
    for( i = 1, k = 1; src[k] >= 0; i++ )
    {
        int code_count = src[k++];
        for( code_count += k; k < code_count; k++ )
        {
            int  table_bits= first_bits;
            int  code_bits = i;
            int  code = src[k] & huff_code_mask;
            int  val  = src[k] >>huff_val_shift;
            int  j, offset = 0;

            if( code_bits > table_bits )
            {
                int idx = code >> (code_bits -= table_bits);
                code &= (1 << code_bits) - 1;
                offset   = sub_tables[idx].offset;
                table_bits= sub_tables[idx].bits;
                /* write header of subtable */
                table[offset]  = (short)table_bits;
                /* write jump to subtable */
                table[idx + 1]= (short)(offset << 4);
            }
        
            table_bits -= code_bits;
            assert( table_bits >= 0 );
            val = (val << 4) | code_bits;
            offset += (code << table_bits) + 1;
        
            for( j = 0; j < (1 << table_bits); j++ )
            {
                assert( table[offset + j] == forbidden_entry );
                table[ offset + j ] = (short)val;
            }
        }
    }
    return true;
}

int*  bs_create_source_huffman_table( const uchar* src, int* dst,
                                      int max_bits, int first_bits )
{
    int   i, val_idx, code = 0;
    int*  table = dst;
    *dst++ = first_bits;
    for( i = 1, val_idx = max_bits; i <= max_bits; i++ )
    {
        int code_count = src[i - 1];
        dst[0] = code_count;
        code <<= 1;
        for( int k = 0; k < code_count; k++ )
        {
            dst[k + 1] = (src[val_idx + k] << huff_val_shift)|(code + k);
        }
        code += code_count;
        dst += code_count + 1;
        val_idx += code_count;
    }
    dst[0] = -1;
    return  table;
}
