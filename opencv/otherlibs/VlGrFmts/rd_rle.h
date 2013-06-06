/*M///////////////////////////////////////////////////////////////////////////////////////
//  
//                      INTEL CORPORATION PROPRIETARY INFORMATION              
//         This software is supplied under the terms of a license agreement or 
//         nondisclosure agreement with Intel Corporation and may not be copied
//         or disclosed except in accordance with the terms of that agreement. 
//               Copyright (c) 1999 Intel Corporation. All Rights Reserved.    
//  
//    RCS:
//       Source:    rd_rle.h$
//       $Revision: 1.1 $
//      Purpose: 
//      Contents:
//      Authors: Vadim Pisarevsky
//  
//M*/

#pragma once

#include "grfmt.h"
#include "bitstrm.h"

class grfmt_bmp_reader : public graphics_format_reader
{
public:
    
    grfmt_bmp_reader();
    ~grfmt_bmp_reader();
    
    int   get_color();
    bool  read_header();
    bool  read_data( byte* data, int pitch, int color );
    void  close();

protected:
    
    rl_byte_stream  m_strm;
    palette_entry   m_palette[256];
    int             m_bpp;
    int             m_offset;
    int             m_rle_code;
};

class grfmt_sun_raster_reader : public graphics_format_reader
{
public:
    grfmt_sun_raster_reader();
    ~grfmt_sun_raster_reader();

    int   get_color();
    bool  read_header();
    bool  read_data( byte* data, int pitch, int color );
    void  close();

protected:
    
    rm_byte_stream  m_strm;
    int             m_bpp;
    int             m_offset;
};