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

#ifndef _BITSTRM_H_
#define _BITSTRM_H_

#include <stdio.h>

#define  LITTLE_ENDIAN  /* intel-like uchar order */
#ifndef  LITTLE_ENDIAN
    #define BIG_ENDIAN  /* motorolla-like uchar order */
#endif

#pragma warning( disable: 4711 )

#define  RBS_THROW_EOS    -123  /* <end of stream> exception code */
#define  RBS_THROW_FORB   -124  /* <forrbidden huffman code> exception code */
#define  RBS_HUFF_FORB    2047  /* forrbidden huffman code "value" */

typedef unsigned char uchar;

// class RBaseStream - base class for other reading streams.
class RBaseStream
{
public:
    //methods
    RBaseStream();
    ~RBaseStream();
    
    virtual bool  Open( const char* filename );
    virtual void  Close();
    void          SetBlockSize( int block_size, int unGetsize = 4 );
    bool          IsOpened();
    void          SetPos( int pos );
    int           GetPos();
    void          Skip( int bytes );
    
protected:
    
    uchar*   m_start;
    uchar*   m_end;
    uchar*   m_current;
    int     m_unGetsize;
    int     m_block_size;
    int     m_block_pos;
    FILE*   m_file;
    bool    m_is_opened;
    
    virtual void  ReadBlock();
    virtual void  Release();
    virtual void  Allocate();
};


// class RLByteStream - uchar-oriented stream.
// l in prefix means that the least significant uchar of a multi-uchar value goes first
class RLByteStream : public RBaseStream
{
public:
    int     GetByte();
    void    GetBytes( void* buffer, int length, int* readed = 0 );
    int     GetWord();
    int     GetDWord(); 
};

// class RMBitStream - uchar-oriented stream.
// m in prefix means that the most significant uchar of a multi-uchar value go first
class RMByteStream : public RLByteStream
{
public:
    int     GetWord();
    int     GetDWord(); 
};

// class RLBitStream - bit-oriented stream.
// l in prefix means that the least significant bit of a multi-bit value goes first
class RLBitStream : public RBaseStream
{
public:
    void    SetPos( int pos );
    int     GetPos();
    int     Get( int bits );
    int     Show( int bits );
    int     GetHuff( const short* table );
    void    Move( int shift );
    void    Skip( int bytes );
        
protected:
    int     m_bit_idx;
    virtual void  ReadBlock();
};

// class RMBitStream - bit-oriented stream.
// m in prefix means that the most significant bit of a multi-bit value goes first
class RMBitStream : public RLBitStream
{
public:
    void    SetPos( int pos );
    int     GetPos();
    int     Get( int bits );
    int     Show( int bits );
    int     GetHuff( const short* table );
    void    Move( int shift );
    void    Skip( int bytes );

protected:
    virtual void  ReadBlock();
};


int* bs_create_source_huffman_table( const uchar* src, int* dst, 
                                     int max_bits, int first_bits );
bool bs_create_decode_huffman_table( const int* src, short* dst, int max_size );
void bs_bswap_block( uchar *start, uchar *end );

extern unsigned long bs_bits_masks[];

#endif/*_BITSTRM_H_*/
