/*M///////////////////////////////////////////////////////////////////////////////////////
//  
//                      INTEL CORPORATION PROPRIETARY INFORMATION              
//         This software is supplied under the terms of a license agreement or 
//         nondisclosure agreement with Intel Corporation and may not be copied
//         or disclosed except in accordance with the terms of that agreement. 
//               Copyright (c) 1999 Intel Corporation. All Rights Reserved.    
//  
//    RCS:
//       Source:    grfmt.cpp$
//       $Revision: 1.1 $
//      Purpose: 
//      Contents:
//      Authors: Vadim Pisarevsky
//  
//M*/

#include <assert.h>
#include <string.h>

#include "grfmt.h"
#include "bitstrm.h"

///////////////////// graphics_format_reader //////////////////////////

graphics_format_reader::graphics_format_reader()
{
    m_width = m_height = -1;
    m_sign_len    = 0;
    m_signature   = 0;
    m_description = 0;
    m_filename[0] ='\0';
}


void  graphics_format_reader::set_file( const char* filename )
{
    assert( filename != 0 && strlen(filename) < sizeof(m_filename) );
    strcpy( m_filename, filename );
}


bool  graphics_format_reader::check_format( const char* signature )
{
    assert( signature != 0 );
    return memcmp( m_signature, signature, m_sign_len ) == 0;
}


///////////////////// graphics_format_reader_list //////////////////////////

graphics_format_readers_list::graphics_format_readers_list()
{
    m_readers = 0;
    remove_all_readers();
}


graphics_format_readers_list::~graphics_format_readers_list()
{
    remove_all_readers();
}


void  graphics_format_readers_list::remove_all_readers()
{
    if( m_readers )
    {
        for( int i = 0; i < m_cur_readers; i++ ) delete m_readers[i];
        delete m_readers;
    }
    m_readers = 0;
    m_max_readers = m_cur_readers = 0;
}


void  graphics_format_readers_list::add_reader( graphics_format_reader* reader )
{
    assert( reader != 0 );
    if( m_cur_readers == m_max_readers )
    {
        // reallocate the readers pointers storage
        int new_max_readers = 2*m_max_readers;
        if( new_max_readers < 16 ) new_max_readers = 16;

        graphics_format_reader** new_readers = 
            new graphics_format_reader*[new_max_readers];

        for( int i = 0; i < m_cur_readers; i++ ) new_readers[i] = m_readers[i];

        delete m_readers;
        m_readers = new_readers;
        m_max_readers = new_max_readers;
    }

    m_readers[m_cur_readers++] = reader;
}


list_position*  graphics_format_readers_list::get_first_reader_pos()
{
    return (list_position*)m_readers;
}


graphics_format_reader* graphics_format_readers_list::
    get_next_reader( list_position*& pos )
{
    graphics_format_reader* reader = 0;
    graphics_format_reader** temp = (graphics_format_reader**)pos;

    assert( temp == 0 || (m_readers <= temp && temp < m_readers + m_cur_readers));
    if( temp )
    {
        reader = *temp++;
        pos = (list_position*)(temp < m_readers + m_cur_readers ? temp : 0);
    }
    return reader;
}


graphics_format_reader* graphics_format_readers_list::
    find_reader( const char* filename )
{
    int    i;
    FILE*  f = fopen( filename, "rb" );
    char   signature[4096];
    int    sign_len = 0;
    graphics_format_reader* reader = 0;

    if( f )
    {
        for( i = 0; i < m_cur_readers; i++ )
        {
            int temp = m_readers[i]->get_signature_length();
            if( temp > sign_len ) sign_len = temp;
        }

        assert( sign_len <= sizeof(signature) );

        sign_len = fread( signature, 1, sign_len, f );
        fclose(f);

        for( i = 0; i < m_cur_readers; i++ )
        {
            int temp = m_readers[i]->get_signature_length();
            if( temp <= sign_len && m_readers[i]->check_format(signature))
            {
                reader = m_readers[i];
                break;
            }
        }
    }

    return reader;
}

int  graphics_format_readers_list::get_filters_string( char* buffer, int maxlen )
{
    buffer, maxlen;
    return 0;
}


void cvt_bgr_to_gray( byte* bgr, byte* gray, int len )
{
#define  SCALE  8
#define  cR  (int)(0.299*(1 << SCALE) + 0.5)
#define  cG  (int)(0.587*(1 << SCALE) + 0.5)
#define  cB  (int)(0.114*(1 << SCALE) + 0.5)
    int i;
    for( i = 0; i < len; i++, bgr += 3 )
    {
        int t = descale( bgr[0]*cB + bgr[1]*cG + bgr[2]*cR, SCALE );
        gray[i] = saturate( t );
    }
}

void cvt_palette_to_gray( palette_entry* palette, byte* gray_palette, int entries )
{
    int i;
    for( i = 0; i < entries; i++ )
    {
        cvt_bgr_to_gray( (byte*)(palette + i), gray_palette + i, 1 );
    }
}

