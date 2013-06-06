/*M///////////////////////////////////////////////////////////////////////////////////////
//  
//                      INTEL CORPORATION PROPRIETARY INFORMATION              
//         This software is supplied under the terms of a license agreement or 
//         nondisclosure agreement with Intel Corporation and may not be copied
//         or disclosed except in accordance with the terms of that agreement. 
//               Copyright (c) 1999 Intel Corporation. All Rights Reserved.    
//  
//    RCS:
//       Source:    grfmt.h$
//       $Revision: 1.1 $
//      Purpose: 
//      Contents:
//      Authors: Vadim Pisarevsky
//  
//M*/

#pragma once

#pragma warning( disable: 4514 )
#pragma warning( disable: 4711 )

typedef unsigned char byte;

// graphics_format_reader interface
class  graphics_format_reader
{
public:
    
    graphics_format_reader();

    int           get_signature_length() { return m_sign_len; };
    const char*   get_description() { return m_description; };
    int           get_width()  { return m_width; };
    int           get_height() { return m_height; };
    
    virtual bool  check_format( const char* signature );
    void          set_file( const char* filename );

    virtual int   get_color() = 0;
    virtual bool  read_header() = 0;
    virtual bool  read_data( byte* data, int pitch, int color ) = 0;
    virtual void  close() = 0;

protected:
    int          m_width;       // width  of an image ( filled by read_header )
    int          m_height;      // height of an image ( filled by read_header )
    int          m_sign_len;    // length of the signature of the format
    const char*  m_signature;   // signature of the format
    const char*  m_description; // e.g: Graphics interchange format (*.GIF)
    char         m_filename[1000];
};


typedef struct {} list_position;

// list of <graphics_format_reader>s
class  graphics_format_readers_list
{
public:

    graphics_format_readers_list();
    ~graphics_format_readers_list();
    void                    remove_all_readers();
    void                    add_reader( graphics_format_reader* reader );
    int                     readers_count() { return m_cur_readers; };
    list_position*          get_first_reader_pos();
    graphics_format_reader* get_next_reader( list_position*& pos );
    graphics_format_reader* find_reader( const char* filename );
    int                     get_filters_string( char* buffer, int maxlen );

protected:

    graphics_format_reader** m_readers;
    int  m_max_readers;
    int  m_cur_readers;
};

struct palette_entry 
{
    unsigned char b,g,r,a;
};

#define WRITE_PIX( ptr, clr )     \
    (((byte*)(ptr))[0] = (clr).b, \
     ((byte*)(ptr))[1] = (clr).g, \
     ((byte*)(ptr))[2] = (clr).r)

#define  descale(x,n)  (((x) + (1 << ((n)-1))) >> (n))
#define  saturate(x)   (byte)(((x) & ~255) == 0 ? (x) : ~((x)>>31))

void  cvt_bgr_to_gray( byte* bgr, byte* gray, int len );
void  cvt_palette_to_gray( palette_entry* palette, byte* gray_palette, int entries );