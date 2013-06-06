/*M///////////////////////////////////////////////////////////////////////////////////////
//  
//                      INTEL CORPORATION PROPRIETARY INFORMATION              
//         This software is supplied under the terms of a license agreement or 
//         nondisclosure agreement with Intel Corporation and may not be copied
//         or disclosed except in accordance with the terms of that agreement. 
//               Copyright (c) 1999 Intel Corporation. All Rights Reserved.    
//  
//    RCS:
//       Source:    rd_jpeg.h$
//       $Revision: 1.1 $
//      Purpose: 
//      Contents:
//      Authors: Vadim Pisarevsky
//  
//M*/

#pragma once

#include "grfmt.h"
#include "bitstrm.h"

class rm_jpeg_bit_stream : public rm_bit_stream
{
public:
    rm_byte_stream  m_low_strm;
    
    rm_jpeg_bit_stream();
    ~rm_jpeg_bit_stream();

    virtual bool  open( const char* filename );
    virtual void  close();

    void  flush(); // flushes high-level bit stream
    void  align_on_byte();
    int   find_marker();

protected:
    virtual void  read_block();
};


//////////////////// JPEG reader /////////////////////

class grfmt_jpeg_reader : public graphics_format_reader
{
public:
    
    grfmt_jpeg_reader();
    ~grfmt_jpeg_reader();

    int   get_color();
    bool  read_header();
    bool  read_data( byte* data, int pitch, int color );
    void  close();

protected:

    int   m_offset; // offset of first scan
    int   m_version; // JFIF version
    int   m_planes; // 3 (YCrCb) or 1 (Gray)
    int   m_precision; // 8 or 12-bit per sample
    int   m_type; // SOF type
    int   m_MCUs; // MCUs in restart interval
    int   m_ss, m_se, m_ah, m_al; // progressive JPEG parameters
    
    // information about each component
    struct cmp_info
    {
        char h;  // horizontal sampling factor
        char v;  // vertical   sampling factor
        char tq; // quantization table index
        char td, ta; // DC & AC huffman tables
        int  dc_pred; // DC predictor
    };
    
    cmp_info m_ci[3];

    int     m_tq[4][64];
    bool    m_is_tq[4];
    
    short*  m_td[4];
    bool    m_is_td[4];
    
    short*  m_ta[4];
    bool    m_is_ta[4];
    
    rm_jpeg_bit_stream   m_strm;

protected:

    bool  load_quant_tables( int length );
    bool  load_huffman_tables( int length );
    void  process_scan( int* idx, int ns, byte* data, int pitch, int color );
    void  reset_decoder();
    void  get_block( int* block, int c );
};
